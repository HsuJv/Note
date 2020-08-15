/*
 * msi.h
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

#ifndef _MSI_INCLUDED
#define _MSI_INCLUDED

typedef unsigned char byte;

typedef enum _MSI_PACKET_TYPE {
    PACKET_INVALID = 0,
    PACKET_TCP,
    PACKET_UDP,
    PACKET_ICMP,
    PACKET_IP
} MSI_PACKET_TYPE;

typedef enum _MSI_HOST_TYPE {
    HOST_INVALID = 0,
    HOST_HOME,
    HOST_ENTERN
} MSI_HOST_TYPE;

// function
extern const char *msiLog();
extern int msiCheck(const byte *s, int max, MSI_PACKET_TYPE type);
extern int ruleEntry(const char *ruleFile);
#endif /* _MSI_INCLUDED */
