#ifndef __SNMP_COMMAND__
#define __SNMP_COMMAND__
#include "lib/vty.h"

#define MIB_PART_OID_RANGE    "<0-4294967295>"
#define MIB_PART_OID_LIMIT_LEN   10
#define OPEN_ZIPC_OK_STR              "zebra open"

extern void snmp_cmd_init ();

extern void snmp_config_host(struct vty * vty);

extern void install_snmp_cmd();

extern int snmp_config_erase(struct vty *vty);
#endif

