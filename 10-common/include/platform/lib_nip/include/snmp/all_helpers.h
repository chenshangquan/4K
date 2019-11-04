#ifndef ALL_HANDLERS_H
#define ALL_HANDLERS_H

#ifdef __cplusplus
extern          "C" {
#endif

#include "snmp/instance.h"
#include "snmp/baby_steps.h"
#include "snmp/scalar.h"
#include "snmp/scalar_group.h"
#include "snmp/watcher.h"
#include "snmp/multiplexer.h"
#include "snmp/null.h"
#include "snmp/debug_handler.h"
#include "snmp/cache_handler.h"
#include "snmp/old_api.h"
#include "snmp/read_only.h"
#include "snmp/row_merge.h"
#include "snmp/serialize.h"
#include "snmp/bulk_to_next.h"
#include "snmp/mode_end_call.h"
/*
 * #include <net-snmp/agent/set_helper.h> 
 */
#include "snmp/snmp_table.h"
#include "snmp/table_data.h"
#include "snmp/table_dataset.h"
#include "snmp/table_iterator.h"
#include "snmp/table_container.h"
/*
 * #include <net-snmp/agent/table_array.h> 
 */

#include "snmp/mfd.h"


void            netsnmp_init_helpers(void);

#ifdef __cplusplus
}
#endif
#endif                          /* ALL_HANDLERS_H */
