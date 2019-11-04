#ifndef NET_SNMP_DEFINITIONS_H
#define NET_SNMP_DEFINITIONS_H

    /**
     *  Defined constants, and other similar enumerations.
     */



#define ONE_SEC         1000000L

    /*
     *  For the initial release, this will just refer to the
     *  relevant UCD header files.
     *    In due course, the relevant definitions will be
     *  identified, and listed here directly.
     *
     *  But for the time being, this header file is primarily a placeholder,
     *  to allow application writers to adopt the new header file names.
     */

#include "snmp/types.h"     /* for oid */
#include "snmp/snmp_api.h"
#include "snmp/asn1.h"
#include "snmp/snmp_impl.h"
#include "snmp/snmp.h" 
#include "snmp/snmp-tc.h"
#include "snmp/snmp_agent_lib.h"
/*
 * #include <net-snmp/library/libsnmp.h> 
 */

#endif                          /* NET_SNMP_DEFINITIONS_H */
