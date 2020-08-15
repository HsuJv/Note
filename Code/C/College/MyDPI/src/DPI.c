/*
 * DPI.c
 * Copyright (C) 2019-2019 by jovi Hsu(jv.hsu@outlook.com)
 *
 * This file is modified from the OpenDPI, an open source deep packet inspection
 * library based on the PACE technology by ipoque GmbH, under the license of
 * LGLP
 *
 * This file is part of my bachelor's graduation project, which consists of some
 * open source projects and my own modification.
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
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/prctl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "pcap.h"
#include "util.h"

#ifdef __linux__
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/udp.h>
#include <netinet/ip6.h>
#else
#include "linux_compat.h"
#endif

#include "DPI.h"
#include "msi.h"
#include "tinyhttp.h"

#define RULE_FILE "snort3-community.rules"

// error
#define ERROR(format, ...) \
    fprintf(stderr, "%s (%d): " format, __FUNCTION__, __LINE__, ##__VA_ARGS__);

// stdarg.h
extern char *optarg;

// http - server
static int _shmid = -1;
static void *_shm = NULL;

// cli options
static char *_pcap_file = NULL;
static char *_eth_name = NULL;
static char _deep_inspection = 0;

// realtime process control
static volatile char on_process = 0;

// pcap
static char _pcap_error_buffer[PCAP_ERRBUF_SIZE];
static pcap_t *_pcap_handle = NULL;
static int _pcap_datalink_type = 0;

// detection
static struct ipoque_detection_module_struct *ipoque_struct = NULL;
static u32 detection_tick_resolution = 1000;
static char *prot_long_str[] = {IPOQUE_PROTOCOL_LONG_STRING};

// self-defined free and malloc
#define free FREE
#define malloc MALLOC
#define calloc CALLOC

#ifdef IPOQUE_ENABLE_DEBUG_MESSAGES
static char *prot_short_str[] = {IPOQUE_PROTOCOL_SHORT_STRING};

static IPOQUE_PROTOCOL_BITMASK debug_messages_bitmask;
#endif

// results
static u64 raw_packet_count = 0;
static u64 ip_packet_count = 0;
static u64 total_bytes = 0;
static u64 protocol_counter[IPOQUE_MAX_SUPPORTED_PROTOCOLS + 1];
static u64 protocol_counter_bytes[IPOQUE_MAX_SUPPORTED_PROTOCOLS + 1];

// real_time results
static u64 real_raw_packet_count = 0;
static u64 real_ip_packet_count = 0;
static u64 real_total_bytes = 0;
static u64 real_protocol_counter[IPOQUE_MAX_SUPPORTED_PROTOCOLS + 1];
static u64 real_protocol_counter_bytes[IPOQUE_MAX_SUPPORTED_PROTOCOLS + 1];

// id tracking

struct osdpi_ip_addr {
#ifdef IPOQUE_DETECTION_SUPPORT_IPV6
    u32 is_ip_v6;
#endif
    union {
        u32 ipv4;
#ifdef IPOQUE_DETECTION_SUPPORT_IPV6
        struct in6_addr ipv6;
#endif
    };
};

typedef struct osdpi_id {
    struct osdpi_ip_addr ip;
    struct ipoque_id_struct *ipoque_id;
} osdpi_id_t;

static u32 size_id_struct = 0;
#define MAX_OSDPI_IDS 50000
static struct osdpi_id *osdpi_ids;
static u32 osdpi_id_count = 0;

// flow tracking
typedef struct osdpi_flow {
    struct ipoque_unique_flow_ipv4_and_6_struct key;
    struct ipoque_flow_struct *ipoque_flow;

    // result only, not used for flow identification
    u32 detected_protocol;
} osdpi_flow_t;

static u32 size_flow_struct = 0;
#define MAX_OSDPI_FLOWS 200000
static struct osdpi_flow *osdpi_flows;
static u32 osdpi_flow_count = 0;

typedef enum _RUN_MODE {
    INVALID_MODE = -1,
    OFFLINE_MODE,
    REAL_TIME_MODE,
    SERVER_MODE,
} RUN_MODE;

static void terminateDetection(int exit_code);

#ifdef IPOQUE_ENABLE_DEBUG_MESSAGES
static int string_to_detection_bitmask(char *str,
                                       IPOQUE_PROTOCOL_BITMASK *dbm) {
    u32 a;
    u32 oldptr = 0;
    u32 ptr = 0;
    IPOQUE_BITMASK_RESET(*dbm);

    printf("Protocol parameter given: %s\n", str);

    if (strcmp(str, "all") == 0) {
        printf("Protocol parameter all parsed\n");
        IPOQUE_BITMASK_SET_ALL(*dbm);
        printf("Bitmask is: " IPOQUE_BITMASK_DEBUG_OUTPUT_BITMASK_STRING " \n",
               IPOQUE_BITMASK_DEBUG_OUTPUT_BITMASK_VALUE(*dbm));
        return 0;
    }
    // parse bitmask
    while (1) {
        if (str[ptr] == 0 || str[ptr] == ' ') {
            printf("Protocol parameter: parsed: %.*s,\n", ptr - oldptr,
                   &str[oldptr]);
            for (a = 1; a <= IPOQUE_MAX_SUPPORTED_PROTOCOLS; a++) {
                if (strlen(prot_short_str[a]) == (ptr - oldptr) &&
                    (memcmp(&str[oldptr], prot_short_str[a], ptr - oldptr) ==
                     0)) {
                    IPOQUE_ADD_PROTOCOL_TO_BITMASK(*dbm, a);
                    printf("Protocol parameter detected as protocol %s\n",
                           prot_long_str[a]);
                }
            }
            oldptr = ptr + 1;
            if (str[ptr] == 0) break;
        }
        ptr++;
    }
    return 0;
}
#endif

static void printUsage() {
    printf("Usage : DPI -o -f pcap_file_name\n");
    printf("         or -r -i eth_driver_name\n");
    printf("         or -s -i eth_driver_name -p port");
    printf("        use -d option to decide if deep inspection is on");
}

static int checkPcapDev(char *check_name) {
    if (!check_name) {
        ERROR("Nullptr is passed.\n");
        return 0;
    }

    if (0 != geteuid()) {
        // check privilege
        ERROR(
            "To listen the ethernet driver needs the administrator's "
            "privilege\n");
        terminateDetection(-1);
    }
    // check the eth name
    int finded_dev = 0;
    pcap_if_t *dev_list = NULL;
    pcap_if_t *dev = NULL;
    if (pcap_findalldevs(&dev_list, _pcap_error_buffer) < 0) {
        ERROR("error in pcap_findalldevs: %s\n.", _pcap_error_buffer);
        terminateDetection(-1);
    }

    dev = dev_list;
    for (; NULL != check_name && NULL != dev; dev = dev->next) {
        if (!strcasecmp(dev->name, check_name)) {
            finded_dev = 1;
            break;
        }
    }

    if (!dev_list) {
        pcap_freealldevs(dev_list);
    }

    return finded_dev;
}

static int parseOptions(int argc, char **argv) {
    int opt;
    int server_port = 0;
    RUN_MODE ret = INVALID_MODE;

#ifdef IPOQUE_ENABLE_DEBUG_MESSAGES
    IPOQUE_BITMASK_SET_ALL(debug_messages_bitmask);
#endif

    while (INVALID_MODE == ret && (opt = getopt(argc, argv, "osr")) != EOF) {
        switch (opt) {
            case 'o':
                ret = OFFLINE_MODE;
                break;
            case 's':
                ret = SERVER_MODE;
                break;
            case 'r':
                ret = REAL_TIME_MODE;
                break;
        }
    }

    // get the ethernet driver and the port
    while ((opt = getopt(argc, argv, "p:i:ef:d")) != EOF) {
        switch (opt) {
            case 'e':
#ifdef IPOQUE_ENABLE_DEBUG_MESSAGES
                // set debug logging bitmask to all protocols
                if (string_to_detection_bitmask(optarg,
                                                &debug_messages_bitmask) != 0) {
                    ERROR("ERROR option -e needs a valid list of protocols");
                    terminateDetection(-1);
                }

                printf(
                    "debug messages Bitmask "
                    "is: " IPOQUE_BITMASK_DEBUG_OUTPUT_BITMASK_STRING "\n",
                    IPOQUE_BITMASK_DEBUG_OUTPUT_BITMASK_VALUE(
                        debug_messages_bitmask));

#else
                ERROR("ERROR: option -e : DEBUG MESSAGES DEACTIVATED\n");
                terminateDetection(-1);
#endif
                break;
            case 'p':
                server_port = atoi(optarg);
                break;
            case 'i':
                _eth_name = optarg;
                break;
            case 'f':
                _pcap_file = optarg;
                break;
            case 'd':
                _deep_inspection = 1;
        }
    }

    if (ret == OFFLINE_MODE) {
        if (_pcap_file == NULL || strcmp(_pcap_file, "") == 0) {
            // check parameters
            ERROR(
                "no pcap file path provided; use option -f with the path to a "
                "valid pcap file\n");
            terminateDetection(-1);
        }
    } else if (ret == REAL_TIME_MODE) {
        if (!checkPcapDev(_eth_name)) {
            ERROR(
                "error in find relative ethernet driver, pls check the "
                "name.\n");
            terminateDetection(-1);
        }
    } else if (ret == SERVER_MODE) {
        if (!checkPcapDev(_eth_name)) {
            ERROR(
                "error in find relative ethernet driver, pls check the "
                "name.\n");
            terminateDetection(-1);
        }

        // start the http server
        pthread_t tid;
        pthread_create(&tid, NULL, runHttpdBkg, &server_port);
    } else {
        printUsage();
        terminateDetection(-1);
    }
    return ret;
}

static void debug_printf(u32 protocol, void *id_struct,
                         ipq_log_level_t log_level, const char *format, ...) {
#ifdef IPOQUE_ENABLE_DEBUG_MESSAGES
    if (IPOQUE_COMPARE_PROTOCOL_TO_BITMASK(debug_messages_bitmask, protocol) !=
        0) {
        const char *protocol_string;
        const char *file;
        const char *func;
        u32 line;
        va_list ap;
        va_start(ap, format);

        protocol_string = prot_short_str[protocol];

        ipoque_debug_get_last_log_function_line(ipoque_struct, &file, &func,
                                                &line);

        printf("\nDEBUG: %s:%s:%u Prot: %s, level: %u packet: %llu :", file,
               func, line, protocol_string, log_level, raw_packet_count);
        vprintf(format, ap);
        va_end(ap);
    }
#endif
}

static void *malloc_wrapper(unsigned long size) { return MALLOC(size); }

static void free_wrapper(void *freeable) { FREE(freeable); }

static void *get_id(const struct osdpi_ip_addr *ip) {
    u32 i;

    for (i = 0; i < osdpi_id_count; i++) {
        if (memcmp(&osdpi_ids[i].ip, ip, sizeof(struct osdpi_ip_addr)) == 0) {
            return osdpi_ids[i].ipoque_id;
        }
    }
    if (osdpi_id_count == MAX_OSDPI_IDS) {
        ERROR("maximum unique id count (%u) has been exceeded\n",
              MAX_OSDPI_IDS);
        terminateDetection(-1);
    } else {
        struct ipoque_id_struct *ipoque_id;
        osdpi_ids[osdpi_id_count].ip = *ip;
        ipoque_id = osdpi_ids[osdpi_id_count].ipoque_id;

        osdpi_id_count += 1;
        return ipoque_id;
    }
    return NULL;
}

static struct osdpi_flow *get_osdpi_flow(const struct iphdr *iph, u16 ipsize) {
    u32 i;
    const u8 *l4 = NULL;
    u16 l4_len = 0;
    u8 l4_protocol = 0;
    struct ipoque_unique_flow_ipv4_and_6_struct key;
    u8 dir = 0;

    if (ipoque_detection_get_l4((u8 *)iph, ipsize, &l4, &l4_len, &l4_protocol,
                                0) == 0) {
        if (ipoque_detection_build_key((u8 *)iph, ipsize, l4, l4_len,
                                       l4_protocol, &key, &dir, 0) == 0) {
            for (i = 0; i < osdpi_flow_count; i++) {
                if (memcmp(
                        &osdpi_flows[i].key, &key,
                        sizeof(struct ipoque_unique_flow_ipv4_and_6_struct)) ==
                    0) {
                    return &osdpi_flows[i];
                }
            }
            if (osdpi_flow_count == MAX_OSDPI_FLOWS) {
                ERROR("maximum flow count (%u) has been exceeded\n",
                      MAX_OSDPI_FLOWS);
                terminateDetection(-1);
            } else {
                struct osdpi_flow *flow;
                osdpi_flows[osdpi_flow_count].key = key;
                flow = &osdpi_flows[osdpi_flow_count];

                osdpi_flow_count += 1;
                return flow;
            }
        }
    }

    return NULL;
}

static void setupDetection(RUN_MODE mode) {
    u32 i;
    IPOQUE_PROTOCOL_BITMASK all;

    // init global detection structure
    ipoque_struct = ipoque_init_detection_module(detection_tick_resolution,
                                                 malloc_wrapper, debug_printf);
    if (ipoque_struct == NULL) {
        ERROR("global structure initialization failed\n");
        terminateDetection(-1);
    }
    // enable all protocols
    IPOQUE_BITMASK_SET_ALL(all);
    ipoque_set_protocol_detection_bitmask2(ipoque_struct, &all);

    // allocate memory for id and flow tracking
    size_id_struct = ipoque_detection_get_sizeof_ipoque_id_struct();
    size_flow_struct = ipoque_detection_get_sizeof_ipoque_flow_struct();

    osdpi_ids = malloc(MAX_OSDPI_IDS * sizeof(struct osdpi_id));
    if (osdpi_ids == NULL) {
        ERROR("malloc for osdpi_ids failed\n");
        terminateDetection(-1);
    }
    for (i = 0; i < MAX_OSDPI_IDS; i++) {
        memset(&osdpi_ids[i], 0, sizeof(struct osdpi_id));
        osdpi_ids[i].ipoque_id = calloc(1, size_id_struct);
        if (osdpi_ids[i].ipoque_id == NULL) {
            ERROR("malloc for ipoque_id_struct failed\n");
            terminateDetection(-1);
        }
    }

    osdpi_flows = malloc(MAX_OSDPI_FLOWS * sizeof(struct osdpi_flow));
    if (osdpi_flows == NULL) {
        ERROR("malloc for osdpi_flows failed\n");
        terminateDetection(-1);
    }
    for (i = 0; i < MAX_OSDPI_FLOWS; i++) {
        memset(&osdpi_flows[i], 0, sizeof(struct osdpi_flow));
        osdpi_flows[i].ipoque_flow = calloc(1, size_flow_struct);
        if (osdpi_flows[i].ipoque_flow == NULL) {
            ERROR("malloc for ipoque_flow_struct failed\n");
            terminateDetection(-1);
        }
    }

    // clear memory for results
    memset(protocol_counter, 0,
           (IPOQUE_MAX_SUPPORTED_PROTOCOLS + 1) * sizeof(u64));
    memset(protocol_counter_bytes, 0,
           (IPOQUE_MAX_SUPPORTED_PROTOCOLS + 1) * sizeof(u64));

    if (REAL_TIME_MODE == mode || SERVER_MODE == mode) {
        on_process = 1;
        memset(real_protocol_counter, 0,
               (IPOQUE_MAX_SUPPORTED_PROTOCOLS + 1) * sizeof(u64));
        memset(real_protocol_counter_bytes, 0,
               (IPOQUE_MAX_SUPPORTED_PROTOCOLS + 1) * sizeof(u64));
    }
    char frule[255], *root;
    root = getenv("DPI_ROOT_PATH");
    sprintf(frule, "%s/bin/%s", root, RULE_FILE);
    if (_deep_inspection) ruleEntry(frule);
}

static void terminateDetection(int exit_code) {
    u32 i;

    if (exit_code == SIGINT) exit_code = 0;  // exit by ctrl + c

    ipoque_exit_detection_module(ipoque_struct, free_wrapper);

    if (osdpi_ids) {
        for (i = 0; i < MAX_OSDPI_IDS; i++) {
            if (osdpi_ids[i].ipoque_id) free(osdpi_ids[i].ipoque_id);
        }
        free(osdpi_ids);
    }

    if (osdpi_flows) {
        for (i = 0; i < MAX_OSDPI_FLOWS; i++) {
            if (osdpi_flows[i].ipoque_flow) free(osdpi_flows[i].ipoque_flow);
        }
        free(osdpi_flows);
    }

    // delete the shared memory
    if (-1 != _shmid) {
        if (-1 == shmdt((char *)_shm)) {
            ERROR("chmdt failed\n");
            exit(-1);
        }

        if (shmctl(_shmid, IPC_RMID, 0) == -1) {
            ERROR("shmctl(IPC_RMID) failed\n");
            exit(-1);
        }
    }

    exit(exit_code);
}

static unsigned int packet_processing(const uint64_t time,
                                      const struct iphdr *iph, uint16_t ipsize,
                                      uint16_t rawsize, RUN_MODE mode) {
    struct ipoque_id_struct *src = NULL;
    struct ipoque_id_struct *dst = NULL;
    struct osdpi_flow *flow = NULL;
    struct ipoque_flow_struct *ipq_flow = NULL;
    u32 protocol = 0;

    struct osdpi_ip_addr src_ip, dst_ip;
    memset(&src_ip, 0, sizeof(struct osdpi_ip_addr));
    memset(&dst_ip, 0, sizeof(struct osdpi_ip_addr));

#ifdef IPOQUE_DETECTION_SUPPORT_IPV6
    if (iph->version == 6 && ipsize >= sizeof(struct ip6_hdr)) {
        struct ip6_hdr *ip6h = (struct ip6_hdr *)iph;
        src_ip.is_ip_v6 = 1;
        src_ip.ipv6 = ip6h->ip6_src;
        dst_ip.is_ip_v6 = 1;
        dst_ip.ipv6 = ip6h->ip6_dst;
    } else
#endif
        if (iph->version == 4 && ipsize >= sizeof(struct iphdr)) {
        src_ip.ipv4 = iph->saddr;
        dst_ip.ipv4 = iph->daddr;
    } else {
        return 1;
    }

    src = get_id(&src_ip);
    dst = get_id(&dst_ip);

    flow = get_osdpi_flow(iph, ipsize);
    if (flow != NULL) {
        ipq_flow = flow->ipoque_flow;
    } else {
        return 1;
    }

    ip_packet_count++;
    if (REAL_TIME_MODE == mode || SERVER_MODE == mode) real_ip_packet_count++;
    total_bytes += rawsize;
    if (REAL_TIME_MODE == mode || SERVER_MODE == mode)
        real_total_bytes += rawsize;

#ifndef IPOQUE_ENABLE_DEBUG_MESSAGES
    if (ip_packet_count % 499 == 0) {
        printf(
            "\rip packets scanned: \x1b[33m%-10llu\x1b[0m ip bytes scanned: "
            "\x1b[34m%-10llu\x1b[0m",
            ip_packet_count, total_bytes);
    }
#endif

    // only handle unfragmented packets
    if (iph->version == 4 && (iph->frag_off & htons(0x1FFF)) != 0) {
        static u8 frag_warning_used = 0;
        if (frag_warning_used == 0) {
            printf(
                "\n\nWARNING: fragmented ip packets are not supported and will "
                "be skipped \n\n");
            sleep(2);
            frag_warning_used = 1;
        }
        return 0;
    } else {
        // here the actual detection is performed
        protocol = ipoque_detection_process_packet(ipoque_struct, ipq_flow,
                                                   (uint8_t *)iph, ipsize, time,
                                                   src, dst, _deep_inspection);
    }

    protocol_counter[protocol]++;
    protocol_counter_bytes[protocol] += rawsize;
    if (REAL_TIME_MODE == mode || SERVER_MODE == mode) {
        real_protocol_counter[protocol]++;
        real_protocol_counter_bytes[protocol] += rawsize;
    }

    if (flow != NULL) {
        flow->detected_protocol = protocol;
    }

    return 0;
}

static void printResults(void) {
    u32 i;

    printf("\x1b[2K\n");
    printf("pcap file contains\n");
    printf("\tip packets:   \x1b[33m%-13llu\x1b[0m of %llu packets total\n",
           ip_packet_count, raw_packet_count);
    printf("\tip bytes:     \x1b[34m%-13llu\x1b[0m\n", total_bytes);
    printf("\tunique ids:   \x1b[35m%-13u\x1b[0m\n", osdpi_id_count);
    printf("\tunique flows: \x1b[36m%-13u\x1b[0m\n", osdpi_flow_count);

    printf("\n\ndetected protocols:\n");
    for (i = 0; i <= IPOQUE_MAX_SUPPORTED_PROTOCOLS; i++) {
        u32 protocol_flows = 0;
        u32 j;

        // count flows for that protocol
        for (j = 0; j < osdpi_flow_count; j++) {
            if (osdpi_flows[j].detected_protocol == i) {
                protocol_flows++;
            }
        }

        if (protocol_counter[i] > 0) {
            printf(
                "\t\x1b[31m%-20s\x1b[0m packets: \x1b[33m%-13llu\x1b[0m bytes: "
                "\x1b[34m%-13llu\x1b[0m "
                "flows: \x1b[36m%-13u\x1b[0m\n",
                prot_long_str[i], protocol_counter[i],
                protocol_counter_bytes[i], protocol_flows);
        }
    }
    printf("\n\n");
}

static void *displayResults(void *arg) {
    // detach it self
    pthread_detach(pthread_self());
    prctl(PR_SET_NAME, "DISPLAY DATA");

    // display
    while (1) {
        on_process = 0;
        printf("\033c");
        u32 i;

        printf("\x1b[2K\n");
        printf("This second\n");
        printf("\tip packets:   \x1b[33m%-13llu\x1b[0m of %llu packets total\n",
               real_ip_packet_count, real_raw_packet_count);
        printf("\tip bytes:     \x1b[34m%-13llu\x1b[0m\n", real_total_bytes);

        printf("\n\ndetected protocols:\n");
        for (i = 0; i <= IPOQUE_MAX_SUPPORTED_PROTOCOLS; i++) {
            u32 protocol_flows = 0;
            u32 j;

            // count flows for that protocol
            for (j = 0; j < osdpi_flow_count; j++) {
                if (osdpi_flows[j].detected_protocol == i) {
                    protocol_flows++;
                }
            }

            if (real_protocol_counter[i] > 0) {
                printf(
                    "\t\x1b[31m%-20s\x1b[0m packets: \x1b[33m%-13llu\x1b[0m "
                    "bytes: \x1b[34m%-13llu\x1b[0m "
                    "flows: \x1b[36m%-13u\x1b[0m\n",
                    prot_long_str[i], real_protocol_counter[i],
                    real_protocol_counter_bytes[i], protocol_flows);
            }
        }
        printf("\n\n");
        printf("\x1b[2K\n");
        printf("Total contains\n");
        printf("\tip packets:   \x1b[33m%-13llu\x1b[0m of %llu packets total\n",
               ip_packet_count, raw_packet_count);
        printf("\tip bytes:     \x1b[34m%-13llu\x1b[0m\n", total_bytes);
        printf("\tunique ids:   \x1b[35m%-13u\x1b[0m\n", osdpi_id_count);
        printf("\tunique flows: \x1b[36m%-13u\x1b[0m\n", osdpi_flow_count);

        // clear this second's data
        real_raw_packet_count = 0;
        real_ip_packet_count = 0;
        real_total_bytes = 0;
        memset(real_protocol_counter, 0,
               (IPOQUE_MAX_SUPPORTED_PROTOCOLS + 1) * sizeof(u64));
        memset(real_protocol_counter_bytes, 0,
               (IPOQUE_MAX_SUPPORTED_PROTOCOLS + 1) * sizeof(u64));
        on_process = 1;
        sleep(1);
    }
    return NULL;
}

static void *writeResults(void *arg) {
    // detach it self
    pthread_detach(pthread_self());
    prctl(PR_SET_NAME, "WRITE DATA");

    // open the shared mem
    _shmid = shmget((key_t)0x5246424a, 8193,
                    0666 | IPC_CREAT);  // the key is base64("DPI")
    if (-1 == _shmid) {
        ERROR("Failed to open a shared memory");
        terminateDetection(0);
    }

    _shm = shmat(_shmid, 0, 0);
    if (!_shm) {
        ERROR("Failed to attach memory chunk");
        terminateDetection(0);
    }

    // write to mem
    while (1) {
        while (DATA_PUT != *(char *)_shm) {
            usleep(100 * 1000);  // no one to request the data
                                 // abandon the cpu
        }

        // block the process route
        on_process = 0;

        // do not need to clear the mem

        // output the result
        u32 i;
        char buf[8192], *pbuf = buf;

        pbuf += sprintf(pbuf, "%llu\n", real_ip_packet_count);
        pbuf += sprintf(pbuf, "%llu\n", real_raw_packet_count);
        pbuf += sprintf(pbuf, "%llu\n", real_total_bytes);

        for (i = 0; i <= IPOQUE_MAX_SUPPORTED_PROTOCOLS; i++) {
            u32 protocol_flows = 0;
            u32 j;

            // count flows for that protocol
            for (j = 0; j < osdpi_flow_count; j++) {
                if (osdpi_flows[j].detected_protocol == i) {
                    protocol_flows++;
                }
            }
            if (real_protocol_counter[i] > 0) {
                pbuf += sprintf(pbuf, "\t%u\n", i);
                pbuf += sprintf(pbuf, "\t%llu\n", real_protocol_counter[i]);
                pbuf +=
                    sprintf(pbuf, "\t%llu\n", real_protocol_counter_bytes[i]);
                pbuf += sprintf(pbuf, "\t%u\n", protocol_flows);
            }
        }
        pbuf += sprintf(pbuf, "%llu\n", ip_packet_count);
        pbuf += sprintf(pbuf, "%llu\n", raw_packet_count);
        pbuf += sprintf(pbuf, "%llu\n", total_bytes);
        pbuf += sprintf(pbuf, "%u\n", osdpi_id_count);
        pbuf += sprintf(pbuf, "%u\n", osdpi_flow_count);

        // clear this second's data
        real_raw_packet_count = 0;
        real_ip_packet_count = 0;
        real_total_bytes = 0;
        memset(real_protocol_counter, 0,
               (IPOQUE_MAX_SUPPORTED_PROTOCOLS + 1) * sizeof(u64));
        memset(real_protocol_counter_bytes, 0,
               (IPOQUE_MAX_SUPPORTED_PROTOCOLS + 1) * sizeof(u64));

        // restore the process
        on_process = 1;

        // write the result
        strncpy((char *)_shm + 1, buf, 8192);
        *(char *)_shm = DATA_GET;  // set the flag to data ready
    }
    return NULL;
}

static void openPcapFile(void) {
    _pcap_handle = pcap_open_offline(_pcap_file, _pcap_error_buffer);

    if (_pcap_handle == NULL) {
        ERROR("could not open pcap file: %s\n", _pcap_error_buffer);
        terminateDetection(-1);
    }
    _pcap_datalink_type = pcap_datalink(_pcap_handle);
}

static void openPcapLive(void) {
    _pcap_handle = pcap_open_live(_eth_name, BUFSIZ, 1, 0, _pcap_error_buffer);

    if (_pcap_handle == NULL) {
        ERROR("could not open the ethernet driver: %s\n", _pcap_error_buffer);
        terminateDetection(-1);
    }
    _pcap_datalink_type = pcap_datalink(_pcap_handle);
}

static void closePcapFile(void) {
    if (_pcap_handle != NULL) {
        pcap_close(_pcap_handle);
    }
}

// executed for each packet in the pcap file
static void pcap_packet_callback(unsigned char *args, const struct pcap_pkthdr *header,
                                 const unsigned char *packet) {
    const struct ethhdr *ethernet = (struct ethhdr *)packet;
    struct iphdr *iph = (struct iphdr *)&packet[sizeof(struct ethhdr)];
    u64 time;
    static u64 lasttime = 0;
    u16 type;
    RUN_MODE mode = *(RUN_MODE *)args;

    if (REAL_TIME_MODE == mode || SERVER_MODE == mode) {
        while (!on_process) sleep(0);
    }
    raw_packet_count++;
    if (REAL_TIME_MODE == mode || SERVER_MODE == mode) {
        real_raw_packet_count++;
    }

    time = ((uint64_t)header->ts.tv_sec) * detection_tick_resolution +
           header->ts.tv_usec / (1000000 / detection_tick_resolution);
    if (lasttime > time) {
        // printf("\nWARNING: timestamp bug in the pcap file (ts delta: %llu,
        // repairing)\n", lasttime - time);
        time = lasttime;
    }
    lasttime = time;

    type = ethernet->h_proto;

    // just work on Ethernet packets that contain IP
    if (_pcap_datalink_type == DLT_EN10MB &&
        (type == htons(ETH_P_IP)
#ifdef IPOQUE_DETECTION_SUPPORT_IPV6
         || type == htons(ETH_P_IPV6)
#endif
             ) &&
        header->caplen >= sizeof(struct ethhdr)) {

        if (header->caplen < header->len) {
            static u8 cap_warning_used = 0;
            if (cap_warning_used == 0) {
                printf(
                    "\n\nWARNING: packet capture size is smaller than packet "
                    "size, DETECTION MIGHT NOT WORK CORRECTLY OR EVEN "
                    "CRASH\n\n");
                sleep(2);
                cap_warning_used = 1;
            }
        }

        if (header->len >= (sizeof(struct ethhdr) + sizeof(struct iphdr))) {
            // process the packet
            packet_processing(time, iph, header->len - sizeof(struct ethhdr),
                              header->len, mode);
        }
    }
}

static void runPcapLoop(RUN_MODE mode) {
    if (_pcap_handle != NULL) {
        pcap_loop(_pcap_handle, -1, &pcap_packet_callback, (unsigned char *)&mode);
    }
}

int main(int argc, char **argv) {
    char env[255] = {0};
    char dir[255] = {0};

    // read the bin_file dir
    readlink("/proc/self/exe", dir, 255);
    *strrchr(dir, '/') = 0;

    // set an environment varible
    *strrchr(dir, '/') = 0;
    sprintf(env, "DPI_ROOT_PATH=%s", dir);
    putenv(env);

    // Initial
    RUN_MODE mode = parseOptions(argc, argv);
    setupDetection(mode);

    // capture the ctrl+c signal
    signal(SIGINT, terminateDetection);

    if (OFFLINE_MODE == mode) {
        openPcapFile();
        runPcapLoop(mode);
        closePcapFile();
        printResults();
        terminateDetection(0);
    } else if (REAL_TIME_MODE == mode) {
        pthread_t tid;
        openPcapLive();
        pthread_create(&tid, NULL, displayResults, NULL);
        runPcapLoop(mode);
        closePcapFile();
    } else if (SERVER_MODE == mode) {
        pthread_t tid;
        openPcapLive();
        pthread_create(&tid, NULL, writeResults, NULL);
        runPcapLoop(mode);
        closePcapFile();
    } else {
        ERROR("Unknown mode\n");
    }

    return 0;
}
