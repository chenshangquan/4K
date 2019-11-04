#ifndef _ACL_IPT_H
#define _ACL_IPT_H

#include <linux/netfilter_ipv4/ip_tables.h>
#include <linux/netfilter.h>
#include "kdc_kernel/acl/ipt_acl.h"

#define IPT_SO_SET_DEBUG    (IPT_BASE_CTL + 2)
#define IPT_SO_SET_CLR_COUNTERS  (IPT_BASE_CTL + 3)
#define IPT_SO_SET_FIREWALL  (IPT_BASE_CTL + 4)

#define IPT_SO_GET_COUNTER  (IPT_BASE_CTL + 2)
#define IPT_SO_GET_DEF_COUNTER  (IPT_BASE_CTL + 3)
#define IPT_SO_GET_DEF_RULE_COUNTER  (IPT_BASE_CTL + 4)


#ifdef IPT_SO_GET_MAX
#undef IPT_SO_GET_MAX
#endif

#ifdef IPT_SO_SET_MAX
#undef IPT_SO_SET_MAX
#endif

#define IPT_SO_GET_MAX  IPT_SO_GET_DEF_RULE_COUNTER
#define IPT_SO_SET_MAX  IPT_SO_SET_FIREWALL

#define ACL_IPT_CMD_NONE        0x0000U
#define ACL_IPT_CMD_INSERT      0x0001U
#define ACL_IPT_CMD_DELETE_NUM  0x0002U
#define ACL_IPT_CMD_REPLACE     0x0004U
#define ACL_IPT_CMD_APPEND      0x0008U
#define ACL_IPT_CMD_SET_POLICY  0x0010U
#define ACL_IPT_CMD_FLUSH   0x0020U
#define ACL_IPT_NUMBER_OF_CMD   7

#define NUMHOOKS                NF_IP_NUMHOOKS
#define HOOK_PRE_ROUTING        NF_IP_PRE_ROUTING
#define HOOK_LOCAL_IN           NF_IP_LOCAL_IN
#define HOOK_FORWARD            NF_IP_FORWARD
#define HOOK_LOCAL_OUT          NF_IP_LOCAL_OUT
#define HOOK_POST_ROUTING       NF_IP_POST_ROUTING
#ifdef NF_IP_DROPPING
#define HOOK_DROPPING           NF_IP_DROPPING
#endif

#define TABLE_MAXNAMELEN        IPT_TABLE_MAXNAMELEN
#define CHAIN_MAXNAMELEN    16

typedef struct iptc_handle *iptc_handle_t;

struct ipt_get_counter
{
    unsigned int rulenum;
    struct ipt_counters in_perm_counter;
    struct ipt_counters in_deny_counter;
    struct ipt_counters out_perm_counter;
    struct ipt_counters out_deny_counter;
};

struct ipt_get_def_counter
{
    struct ipt_counters in_def_perm_counter;
    struct ipt_counters in_def_deny_counter;
    struct ipt_counters out_def_perm_counter;
    struct ipt_counters out_def_deny_counter;
};

int acl_ipt_do_command(ACL_RULE_ENTRY* entry, char* ifname, char *table, char* chain,
               int command, int count, int pos, void* target_info, char* policy);
void acl_ipt_get_counter(const char *tablename, unsigned int rulenum,
                         u_int64_t* in_perm_bcnt, u_int64_t* in_perm_pcnt, u_int64_t* in_deny_bcnt, u_int64_t* in_deny_pcnt, 
                         u_int64_t* out_perm_bcnt, u_int64_t* out_perm_pcnt, u_int64_t* out_deny_bcnt, u_int64_t* out_deny_pcnt);
void acl_ipt_get_def_counter(const char* tablename, u_int64_t* in_def_perm_bcnt, u_int64_t* in_def_perm_pcnt, u_int64_t* in_def_deny_bcnt, u_int64_t* in_def_deny_pcnt, 
                         u_int64_t* out_def_perm_bcnt, u_int64_t* out_def_perm_pcnt, u_int64_t* out_def_deny_bcnt, u_int64_t* out_def_deny_pcnt);
void acl_ipt_get_def_rule_counter(const char* tablename, u_int64_t* in_def_perm_bcnt, u_int64_t* in_def_perm_pcnt, u_int64_t* in_def_deny_bcnt, u_int64_t* in_def_deny_pcnt, 
                         u_int64_t* out_def_perm_bcnt, u_int64_t* out_def_perm_pcnt, u_int64_t* out_def_deny_bcnt, u_int64_t* out_def_deny_pcnt);
void acl_ipt_clr_counter(const char *tablename, int rulenum);
int acl_ipt_set_debug(int debug);
int acl_ipt_set_firewall(int enable);

#endif
