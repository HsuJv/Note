/*
 * msi.c
 * Copyright (C) 2019 by jovi Hsu(jv.hsu@outlook.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include <errno.h>
#include <fcntl.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "atom.h"
//#include "ipq_api.h"
#include "mem.h"
#include "msi.h"
#define PCRE2_CODE_UNIT_WIDTH 8
#define MSI_CHECK 0b1
#define MSI_TAIL 0b10
#include "pcre2.h"

#define NELEMS(x) ((sizeof(x)) / (sizeof((x)[0])))

#define strstr strStr

typedef struct _RuleList {
    struct _RuleHdr* ruleHdr;
    struct _RuleBody* ruleBody;
    struct _RuleList *prev, *next;
} RuleList, *pRuleList;

typedef struct _RuleHdr {
    MSI_PACKET_TYPE protocol;
    MSI_HOST_TYPE srcIp, dstIp;
    unsigned srcPort, dstPort;
    struct _RuleHdr *prev, *next;
    unsigned ref;
} RuleHdr, *pRuleHdr;

typedef struct _RuleBody {
    const char* msg;
    // Placeholder for other restricts
    unsigned ref;
} RuleBody, *pRuleBody;

typedef struct _RuleCntt {
    const char* content;
    struct _RuleHdr* ruleHdr;
    struct _RuleBody* ruleBody;
    struct _RuleCntt *prev, *next;
} RuleCntt, *pRuleCntt;

typedef struct _RulePcre {
    pcre2_code* pcre;
    struct _RuleHdr* ruleHdr;
    struct _RuleBody* ruleBody;
    struct _RulePcre *prev, *next;
} RulePcre, *pRulePcre;

static RuleList _gRuleList, *gRuleList = &_gRuleList;
static RuleHdr _gRuleHdr, *gRuleHdr = &_gRuleHdr;
static RuleCntt _gRuleCntt, *gRuleCntt = &_gRuleCntt;
static RulePcre _gRulePcre, *gRulePcre = &_gRulePcre;

static char gMsi[256][256];
static unsigned int gMinC = -1;
static const char* log_msg;

// declear forahead
static pRuleHdr addRuleHdr(RuleHdr rh);
static void deleteRuleHdr(pRuleHdr prh);
static void deleteRuleBody(pRuleBody prb);
static void addRuleHdrRef(pRuleHdr prh);
static void addRuleBodyRef(pRuleBody prb);
static pRuleCntt addRuleCntt(pRuleCntt prc, pRuleHdr prh, pRuleBody prb,
                             const char* c);
static void deleteRuleCntt(pRuleCntt prc);
static pRuleList addRuleList(pRuleList pr, pRuleHdr prh, pRuleBody prb);
// static void deleteRuleList(pRuleList pr);
static pRulePcre addRulePcre(PCRE2_SPTR cpcre, pRuleHdr prh, pRuleBody prb);
static void deleteRulePcre(pRulePcre prp);

static int is_blank(const char c) {
    return ('\r' == c) || ('\n' == c) || ('\t' == c) || (' ' == c);
}

// strstr use Sunday
static int strStr(const byte* target, const byte* pattern, int tlen, int plen) {
    int n = tlen;
    int m = plen;
    static int shift[256];

    memset(shift, 0, sizeof(shift));
    for (int i = 0; i < m; i++) {
        shift[pattern[i]] = m - i;
    }

    int s = 0;
    int j;
    while (s <= n - m) {
        j = 0;
        while (target[s + j] == pattern[j]) {
            j++;
            if (j >= m) {
                return s;
            }
        }
        if (!shift[target[s + m]])
            s += m + 1;
        else
            s += shift[target[s + m]];
    }
    return -1;
}

static pRuleHdr addRuleHdr(RuleHdr rh) {
    pRuleHdr prh = gRuleHdr;
    while (prh) {
        if (!memcmp(prh, &rh, (size_t) & (((pRuleHdr)0)->prev))) {
            return prh;  // finded
        }
        prh = prh->next;
    }

    // add new
    pRuleHdr ruleHdr = MALLOC(sizeof(RuleHdr));
    if (!ruleHdr) return NULL;
    memcpy(ruleHdr, &rh, (size_t) & (((pRuleHdr)0)->next));
    ruleHdr->next = gRuleHdr->next;
    ruleHdr->prev = gRuleHdr;
    if (gRuleHdr->next) gRuleHdr->next->prev = ruleHdr;
    gRuleHdr->next = ruleHdr;
    return ruleHdr;
}

static void deleteRuleHdr(pRuleHdr prh) {
    if (!prh) return;

    if (!prh->ref) return;
    prh->ref--;
    // if (!prh->ref) {
    //     if (prh->prev) prh->prev->next = prh->next;
    //     if (prh->next) prh->next->prev = prh->prev;
    //     FREE(prh);
    // }
}

static void deleteRuleBody(pRuleBody prb) {
    if (!prb) return;

    if (!prb->ref) return;
    prb->ref--;
    // if (!prb->ref) {
    //     FREE(prb);
    // }
}

static void addRuleHdrRef(pRuleHdr prh) {
    if (!prh) return;
    prh->ref++;
}

static void addRuleBodyRef(pRuleBody prb) {
    if (!prb) return;

    prb->ref++;
}

static pRuleCntt addRuleCntt(pRuleCntt prc, pRuleHdr prh, pRuleBody prb,
                             const char* c) {
    if (!prc || !prh || !prb) return NULL;

    prc->content = c;
    prc->ruleHdr = prh;
    prc->ruleBody = prb;
    prc->next = gRuleCntt->next;
    prc->prev = gRuleCntt;
    if (gRuleCntt->next) gRuleCntt->next->prev = prc;
    gRuleCntt->next = prc;

    return prc;
}

static void deleteRuleCntt(pRuleCntt prc) {
    if (!prc) return;

    if (prc->prev) prc->prev->next = prc->next;
    if (prc->next) prc->next->prev = prc->prev;
    FREE(prc);
}

static pRulePcre addRulePcre(PCRE2_SPTR cpcre, pRuleHdr prh, pRuleBody prb) {
    int errornumber;
    PCRE2_SIZE erroroffset;
    pRulePcre prp = MALLOC(sizeof(RulePcre));
    if (!prp) return NULL;

    prp->pcre = pcre2_compile(cpcre, PCRE2_ZERO_TERMINATED, 0, &errornumber,
                              &erroroffset, NULL);
    if (!prp->pcre) {
        PCRE2_UCHAR buffer[256];
        pcre2_get_error_message(errornumber, buffer, sizeof(buffer));
        fprintf(stderr, "PCRE2 compilation failed at offset %d: %s\n",
                (int)erroroffset, buffer);
        FREE(prp);
        return NULL;
    }

    prp->ruleHdr = prh;
    prp->ruleBody = prb;
    prp->next = gRulePcre->next;
    prp->prev = gRulePcre;
    if (gRulePcre->next) gRulePcre->next->prev = prp;
    gRulePcre->next = prp;
    return prp;
}

static void deleteRulePcre(pRulePcre prp) {
    if (!prp) return;

    if (prp->prev) prp->prev->next = prp->next;
    if (prp->next) prp->next->prev = prp->prev;
    pcre2_code_free(prp->pcre);
    FREE(prp);
}

static pRuleList addRuleList(pRuleList pr, pRuleHdr prh, pRuleBody prb) {
    if (!pr || !(prh || prb)) return NULL;

    pr->ruleHdr = prh;
    pr->ruleBody = prb;
    pr->next = gRuleList->next;
    pr->prev = gRuleList;
    if (gRuleList->next) gRuleList->next->prev = pr;
    gRuleList->next = pr;

    addRuleHdrRef(prh);
    addRuleBodyRef(prb);

    return pr;
}

// static void deleteRuleList(pRuleList pr) {
//     if (!pr) return;

//     if (pr->prev) pr->prev->next = pr->next;
//     if (pr->next) pr->next->prev = pr->prev;
//     if (pr->ruleBody) deleteRuleBody(pr->ruleBody);
//     if (pr->ruleHdr) deleteRuleHdr(pr->ruleHdr);
//     FREE(pr);
// }

static pRuleCntt parseContent(const char* str, pRuleHdr ruleHdr,
                              pRuleBody ruleBody) {
    int d;
    byte s[1024], *p = s;
    pRuleCntt ret = MALLOC(sizeof(RuleCntt));

    while ('\0' != *str) {
        while (*str && '|' != *str) {
            *p++ = *str++;
        }
        if (!*str) break;
        str++;
        while (sscanf(str, "%x", &d)) {
            *p++ = d;
            str += 2;
            if (' ' == *str)
                str++;
            else
                break;
        }
        str++;
        if (!*str) break;
    }
    *p = '\0';

    // if (p - s > 2) gMsi[s[0]][s[1]] = 1;
    for (byte* i = s; i + 1 < p; i++) {
        gMsi[*i][*(i + 1)] |= MSI_CHECK;
        if (i == p - 2) gMsi[*i][*(i + 1)] |= MSI_TAIL;
    }
    if (p - s < gMinC) gMinC = p - s;  // update gMinC

    return addRuleCntt(
        ret, ruleHdr, ruleBody,
        Atom_new((const char*)s,
                 p - s));  // use atom_new to avoid \0 is in the string
}

static int addRule(const char* line) {
    char direction[5];
    char action[20], protocol[20];
    char src_addr[20], dst_addr[20];
    char src_port[100], dst_port[100];
    char body[4096];

    pRuleHdr ruleHdr = NULL;
    pRuleBody ruleBody = NULL;
    pRuleList rule = NULL;

    while (is_blank(*line)) {
        line++;
    }
    if ('\0' == *line) return 0;

    RuleHdr rh;
    memset(&rh, 0, sizeof(RuleHdr));

    // Scan the header
    sscanf(line, "%s %s %s %s %s %s %s (%[^\n]\n", action, protocol, src_addr,
           src_port, direction, dst_addr, dst_port, body);

    if (Atom_string(protocol) == Atom_string("udp"))
        rh.protocol = PACKET_UDP;
    else if (Atom_string(protocol) == Atom_string("tcp"))
        rh.protocol = PACKET_TCP;
    else if (Atom_string(protocol) == Atom_string("icmp"))
        rh.protocol = PACKET_ICMP;
    else if (Atom_string(protocol) == Atom_string("ip"))
        rh.protocol = PACKET_ICMP;
    else
        goto exit;

    if (Atom_string(src_addr) == Atom_string("$HOME_NET"))
        rh.srcIp = HOST_HOME;
    else
        rh.srcIp = HOST_ENTERN;

    if (Atom_string(src_port) == Atom_string("any"))
        rh.srcPort = 0;
    else {
        rh.srcPort = atoi(src_port);
        if (!rh.srcPort) goto exit;
    }

    if (Atom_string(dst_addr) == Atom_string("$HOME_NET"))
        rh.dstIp = HOST_HOME;
    else
        rh.dstIp = HOST_ENTERN;

    if (Atom_string(dst_port) == Atom_string("any"))
        rh.dstPort = 0;
    else {
        rh.dstPort = atoi(dst_port);
        if (!rh.dstPort) goto exit;
    }
    ruleHdr = addRuleHdr(rh);
    if (!ruleHdr) goto exit;

    // Scan the body
    ruleBody = MALLOC(sizeof(RuleBody));
    if (!ruleBody) goto exit;

    memset(ruleBody, 0, sizeof(RuleBody));
    char* msg = body + strstr(body, "msg", strlen(body), 3);
    if (msg != body - 1) {
        char cmsg[1024];
        sscanf(msg, "msg:\"%[^\"]", cmsg);
        ruleBody->msg = Atom_string(cmsg);
    } else {
        // left NULL
    }

    char* cnttBase = body;
    int cnttOffset = strstr(cnttBase, "content", strlen(body), 7);
    while (-1 != cnttOffset) {
        char ccontent[1024];
        sscanf(cnttBase + cnttOffset, "content:\"%[^\"]", ccontent);
        parseContent(ccontent, ruleHdr, ruleBody);
        cnttBase += cnttOffset + strlen(ccontent);
        cnttOffset = strstr(cnttBase, "content", strlen(body), 7);
    }

    char* pcreBase = body;
    int pcreOffset = strstr(body, "pcre", strlen(body), 4);
    while (-1 != pcreOffset) {
        char cpcre[1024];
        sscanf(pcreBase + pcreOffset, "pcre:\"%[^\"]", cpcre);
        addRulePcre(cpcre, ruleHdr, ruleBody);
        pcreBase += pcreOffset + strlen(cpcre);
        pcreOffset = strstr(pcreBase, "pcre", strlen(body), 4);
    }

    // Add rule
    rule = MALLOC(sizeof(RuleList));
    if (!rule) goto exit;
    addRuleList(rule, ruleHdr, ruleBody);

    if (Atom_string(direction) == Atom_string("<>")) {
        rh.protocol = ruleHdr->protocol;
        rh.srcIp = ruleHdr->dstIp;
        rh.dstIp = ruleHdr->srcIp;
        rh.srcPort = ruleHdr->dstPort;
        rh.dstPort = ruleHdr->srcPort;

        ruleHdr = addRuleHdr(rh);
        pRuleList rule = MALLOC(sizeof(RuleList));
        if (!rule || !ruleHdr) goto exit;
        addRuleList(rule, ruleHdr, ruleBody);
    }

    return 0;

exit:

    return -1;
}

int ruleEntry(const char* ruleFile) {
    FILE* frule = fopen(ruleFile, "r");
    if (!frule) {
        fprintf(stderr, "Open rule file %s error", ruleFile);
        return -1;
    }
    char line[4096];
    while (fgets(line, 4096, frule)) {
        if ('#' == *line) continue;  // a commented line
        if (addRule(line) < 0) {
            // fprintf(stderr, "Add line error: %s", line);
        }
    };
    fclose(frule);
    return 0;
}

static int matchRuleCont(const byte* s, size_t len, MSI_PACKET_TYPE type) {
    if (len < gMinC) return 0;
    char sub[len + 1];
    memcpy(sub, s, len);
    sub[len] = 0;

    pRuleCntt prc = gRuleCntt->next;
    while (prc) {
        if (prc->ruleHdr->protocol != type) {
            prc = prc->next;
            continue;
        }
        if (!prc->ruleHdr->ref || !prc->ruleBody->ref) {
            prc = prc->next;
            continue;
        }
        const char* content = prc->content;
        if (content) {
            int alen = Atom_length(content);
            if (len >= alen && -1 != strstr(sub, content, len, alen)) {
                // matched a rule;
                log_msg = prc->ruleBody->msg;
                return 1;
            } else {
                // content do not match
            }
        }

        prc = prc->next;
    }
    return 0;
}

static int matchRulePcre(const byte* s, size_t len, MSI_PACKET_TYPE type) {
    pRulePcre prp = gRulePcre->next;

    while (prp) {
        if (prp->ruleHdr->protocol != type) {
            prp = prp->next;
            continue;
        }
        if (!prp->ruleHdr->ref || !prp->ruleBody->ref) {
            prp = prp->next;
            continue;
        }
        pcre2_code* re = prp->pcre;

        if (re) {
            // compile the pcre
            pcre2_match_data* match_data;
            int rc;

            match_data = pcre2_match_data_create_from_pattern(re, NULL);
            rc = pcre2_match(re, (PCRE2_SPTR)s, len, 0, 0, match_data, NULL);

            pcre2_match_data_free(match_data);

            if (rc < 0) {
                // do not match or match error
            } else {
                // matched a rule;
                log_msg = prp->ruleBody->msg;
                return 1;
            }
        }
        prp = prp->next;
    }
    return 0;
}

static void msiLogRst() { log_msg = NULL; }

int msiCheck(const byte* s, int max, MSI_PACKET_TYPE type) {
    if (max < gMinC) return 0;

    const byte *e = s, *delim = s + max;
    int ret = 0;
    msiLogRst();

    ret = matchRulePcre(s, max, type);

    while (!ret && e < delim) {
        while (e < delim && gMsi[*e][*(e + 1)])
            if (gMsi[*e][*(++e)] & MSI_TAIL)
                break;  // ends when e is in candidate
        e++;            // e points to the next
        size_t len = e - s;
        if (len > 1) {
            ret = matchRuleCont(s, len, type);
            if (gMsi[*(e - 1)][*e]) continue;
        }
        s = e;
    }

    return ret;
}

const char* msiLog() { return log_msg; }