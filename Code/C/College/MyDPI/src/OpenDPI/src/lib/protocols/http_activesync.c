/*
 * http_activesync.c
 * Copyright (C) 2009-2011 by ipoque GmbH
 * 
 * This file is part of OpenDPI, an open source deep packet inspection
 * library based on the PACE technology by ipoque GmbH
 * 
 * OpenDPI is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * OpenDPI is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with OpenDPI.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */



#include "ipq_protocols.h"
#ifdef IPOQUE_PROTOCOL_HTTP_APPLICATION_ACTIVESYNC
static void ipoque_int_activesync_add_connection(struct ipoque_detection_module_struct
												 *ipoque_struct)
{
	ipoque_int_add_connection(ipoque_struct, IPOQUE_PROTOCOL_HTTP_APPLICATION_ACTIVESYNC, IPOQUE_CORRELATED_PROTOCOL);
}

void ipoque_search_activesync(struct ipoque_detection_module_struct *ipoque_struct)
{
	struct ipoque_packet_struct *packet = &ipoque_struct->packet;
	struct ipoque_flow_struct *flow = ipoque_struct->flow;
	if (packet->tcp != NULL) {

		if (packet->payload_packet_len > 150
			&& ((memcmp(packet->payload, "OPTIONS /Microsoft-Server-ActiveSync?", 37) == 0)
				|| (memcmp(packet->payload, "POST /Microsoft-Server-ActiveSync?", 34) == 0))) {
			ipoque_int_activesync_add_connection(ipoque_struct);
			IPQ_LOG(IPOQUE_PROTOCOL_HTTP_APPLICATION_ACTIVESYNC, ipoque_struct, IPQ_LOG_DEBUG,
					" flow marked as ActiveSync \n");
			return;
		}
	}

	IPQ_LOG(IPOQUE_PROTOCOL_HTTP_APPLICATION_ACTIVESYNC, ipoque_struct, IPQ_LOG_DEBUG, "exclude activesync\n");
	IPOQUE_ADD_PROTOCOL_TO_BITMASK(flow->excluded_protocol_bitmask, IPOQUE_PROTOCOL_HTTP_APPLICATION_ACTIVESYNC);

}
#endif
