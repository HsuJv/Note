/*
 * get_data.c
 * Copyright (C) 2019-2019 by jovi Hsu(jv.hsu@outlook.com)
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include "DPI.h"

static int _shmid = -1;
static void *_shm = NULL;

// ipoque_vars
static char *prot_long_str[] = {IPOQUE_PROTOCOL_LONG_STRING};

// results
static u64 raw_packet_count = 0;
static u64 ip_packet_count = 0;
static u64 total_bytes = 0;

// real_time results
static u64 real_raw_packet_count = 0;
static u64 real_ip_packet_count = 0;
static u64 real_total_bytes = 0;
static u64 real_protocol_counter[IPOQUE_MAX_SUPPORTED_PROTOCOLS + 1];
static u64 real_protocol_counter_bytes[IPOQUE_MAX_SUPPORTED_PROTOCOLS + 1];
static u32 real_protocol_flows[IPOQUE_MAX_SUPPORTED_PROTOCOLS + 1];

// accumulated flows
static u32 osdpi_id_count;
static u32 osdpi_flow_count;

static int getLine(char **src, char *out, int size) {
    int i = 0;
    char c = '\0';
    char *cur = *src;

    while ((i < size - 1) && (c != '\n')) {
        c = *cur++;

        if (c == '\r') {
            c = *(cur + 1);
            if ((c == '\n'))
                c = *cur++;
            else
                c = '\n';
        }

        out[i] = c;
        i++;
    }
    out[i] = '\0';

    *src = cur;
    return i;
}

static void parseResults(char *buf) {
    char line[255];
    // read real time data
    getLine(&buf, line, sizeof line);
    sscanf(line, "%llu", &real_ip_packet_count);

    getLine(&buf, line, sizeof line);
    sscanf(line, "%llu", &real_raw_packet_count);

    getLine(&buf, line, sizeof line);
    sscanf(line, "%llu", &real_total_bytes);

    // read the protocol
    while (getLine(&buf, line, sizeof line) && '\t' == *line) {
        int i;
        sscanf(line, "%u", &i);

        getLine(&buf, line, sizeof line);
        sscanf(line, "%llu", &real_protocol_counter[i]);

        getLine(&buf, line, sizeof line);
        sscanf(line, "%llu", &real_protocol_counter_bytes[i]);

        getLine(&buf, line, sizeof line);
        sscanf(line, "%u", &real_protocol_flows[i]);
    }

    // read the accumulation
    sscanf(line, "%llu", &ip_packet_count);

    getLine(&buf, line, sizeof line);
    sscanf(line, "%llu", &raw_packet_count);

    getLine(&buf, line, sizeof line);
    sscanf(line, "%llu", &total_bytes);

    getLine(&buf, line, sizeof line);
    sscanf(line, "%u", &osdpi_id_count);

    getLine(&buf, line, sizeof line);
    sscanf(line, "%u", &osdpi_flow_count);
}

static void writeResults(void) {
    // output the result
    u32 i;
    char buf[8192], *pbuf = buf;

    pbuf += sprintf(pbuf, "{");
    pbuf += sprintf(pbuf, "\"ip packets\" : %llu, ", real_ip_packet_count);
    pbuf += sprintf(pbuf, "\"packets total\" : %llu, ", real_raw_packet_count);
    pbuf += sprintf(pbuf, "\"ip bytes\" : %llu, ", real_total_bytes);

    pbuf += sprintf(pbuf, "\"protocols\" : ");
    pbuf += sprintf(pbuf, "[");
    for (i = 0; i <= IPOQUE_MAX_SUPPORTED_PROTOCOLS; i++) {
        if (real_protocol_flows[i])
            pbuf += sprintf(pbuf, "{");
        else
            continue;

        pbuf += sprintf(pbuf, "\"name\" : \"%s\", ", prot_long_str[i]);
        pbuf += sprintf(pbuf, "\"packets\" : %llu, ", real_protocol_counter[i]);
        pbuf +=
            sprintf(pbuf, "\"bytes\" : %llu, ", real_protocol_counter_bytes[i]);
        pbuf += sprintf(pbuf, "\"flows\" : %u", real_protocol_flows[i]);

        pbuf += sprintf(pbuf, "}, ");
    }
    if (',' == *(pbuf - 2)) pbuf -= 2;
    pbuf += sprintf(pbuf, " ], ");
    pbuf += sprintf(pbuf, "\"total\" : {");
    pbuf += sprintf(pbuf, "\"ip packets\" : %llu, ", ip_packet_count);
    pbuf += sprintf(pbuf, "\"packets total\" : %llu, ", raw_packet_count);
    pbuf += sprintf(pbuf, "\"ip bytes\" : %llu, ", total_bytes);
    pbuf += sprintf(pbuf, "\"unique ids\" : %u, ", osdpi_id_count);
    pbuf += sprintf(pbuf, "\"unique flows\" : %u", osdpi_flow_count);

    pbuf += sprintf(pbuf, "} }");

    // write the result
    write(1, buf, strlen(buf)+1);
    fsync(1);
}

int main() {
    char buf[8192];

    // open the shared mem
    _shmid = shmget((key_t)0x5246424a, 8193, 0);  // the key is base64("DPI")
    if (-1 == _shmid) {
        perror("Failed to open a shared memory");
        exit(1);
    }

    _shm = shmat(_shmid, 0, 0);
    if (!_shm) {
        perror("Failed to attach memory chunk");
        exit(-1);
    }

    // inform the DPI procee to put data
    *(char *)_shm = DATA_PUT;

    // read data
    while (DATA_GET != *(char *)_shm){
        usleep(0); //wait the data
    }
    *(char *)_shm = DATA_ADD_UP;
    strncpy(buf, (char *)_shm + 1, 8192);

    // detach the mem
    if (-1 == shmdt((char *)_shm)) {
        perror("chmdt failed\n");
        exit(1);
    }
    parseResults(buf);
    writeResults();

    return 0;
}
