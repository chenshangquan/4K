/*
 * A simple helpful wrapper to include lots of agent specific include
 * * files for people wanting to embed and snmp agent into an external
 * * application
 */
#ifndef NET_SNMP_AGENT_INCLUDES_H
#define NET_SNMP_AGENT_INCLUDES_H

#ifndef MOD_SNMP_VER_0
#define MOD_SNMP_VER_0 
#endif

#include <string.h>

#include "snmp/net-snmp-config.h"
#include "snmp/types.h"
#include "snmp/snmp_api.h"
#include "snmp/snmp_client.h"
#include "snmp/snmp_logging.h"
#include "snmp/snmp_agent.h"
#include "snmp/snmp_debug.h"
#include "snmp/agent_handler.h"
#include "snmp/scalar.h"
#include "snmp/snmp_impl.h"
#include "snmp/callback.h"
#include "snmp/snmp_transport.h"
#include "snmp/tools.h"
#include "snmp/data_list.h"
#include "snmp/snmp_module.h"
#include "snmp/snmp_vars.h"
#include "snmp/ds_agent.h"
#include "snmp/agent_read_config.h"
#include "snmp/agent_trap.h"
#include "snmp/container.h"
#include "snmp/oid_stash.h"
#include "snmp/all_helpers.h"
#include "snmp/var_struct.h"

#include"snmp/mib_module_config.h"
#include "snmp/agent_module_config.h"

#endif                          /* NET_SNMP_AGENT_INCLUDES_H */
