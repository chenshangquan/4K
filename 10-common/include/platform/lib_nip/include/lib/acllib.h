#ifndef _ACLLIB_H
#define _ACLLIB_H

#include "lib/zebra.h"
#include "lib/acllist.h"
#include "lib/command.h"
#include "lib/stream.h"
#include "lib/zipc.h"
#include "zebra/zserv.h"
#include "lib/notify_mcast.h"

#define ACL_MAX_RULE_NUM	199
#define ACL_MIN_RULE_NUM	1
#define ACL_MAX_SUB_NUM     255
#define ACL_MIN_SUB_NUM     0
#define ACL_MAX_PORT        65535
#define ACL_MIN_PORT        0

#define ACL_ENTRY_PROTO           0x0001
#define ACL_ENTRY_SRC_ADDR        0x0002
#define ACL_ENTRY_DST_ADDR        0x0004
#define ACL_ENTRY_SRCPORT_EQ      0x0008
#define ACL_ENTRY_SRCPORT_GT      0x0010
#define ACL_ENTRY_SRCPORT_LT      0x0020
#define ACL_ENTRY_SRCPORT_NEQ     0x0040
#define ACL_ENTRY_SRCPORT_RANGE   0x0080
#define ACL_ENTRY_DSTPORT_EQ      0x0100
#define ACL_ENTRY_DSTPORT_GT      0x0200
#define ACL_ENTRY_DSTPORT_LT      0x0400
#define ACL_ENTRY_DSTPORT_NEQ     0x0800
#define ACL_ENTRY_DSTPORT_RANGE   0x1000
#define ACL_ENTRY_ICMPTYPE        0x2000
#define ACL_ENTRY_TOS             0x4000
#define ACL_ENTRY_FRAGMENT        0x8000

#define ACL_VERDICT_NONE    0x00
#define ACL_VERDICT_DENY    0x01
#define ACL_VERDICT_ACCEPT  0x02

#define ACL_NOTIFY_ADD      0x01
#define ACL_NOTIFY_REPLACE  0x02
#define ACL_NOTIFY_DEL      0x04

#ifndef IFNAMSIZ
#define IFNAMSIZ	16
#endif

#define NOTIFY_MC_TYPE_ACL_CHANGE 1
#define ZMSG_ACL_CHANGE ZMSG_ACL_BASE + 1

#define ACL_NOTIFY_FILTER "filter"
#define ACL_NOTIFY_NAT  "nat"

enum acl_opcodes
{						/* arguments (4 byte each)	*/
	O_IP_SRC = 0,			/* u32 = IP			*/
	O_IP_DST = 1,			/* u32 = IP			*/
	O_ANYIP = 2,

	O_IP_SRCPORT_EQ = 3,	/* (n)port list:mask 4 byte ea	*/
	O_IP_SRCPORT_GT = 4,	/* (n)port list:mask 4 byte ea	*/
	O_IP_SRCPORT_LT = 5,	/* (n)port list:mask 4 byte ea	*/
	O_IP_SRCPORT_NEQ = 6,	/* (n)port list:mask 4 byte ea	*/
	O_IP_SRCPORT_RANGE = 7,	/* (n)port list:mask 4 byte ea	*/
	O_IP_DSTPORT_EQ = 8,	/* (n)port list:mask 4 byte ea	*/
	O_IP_DSTPORT_GT = 9,	/* (n)port list:mask 4 byte ea	*/
	O_IP_DSTPORT_LT = 10,	/* (n)port list:mask 4 byte ea	*/
	O_IP_DSTPORT_NEQ = 11,	/* (n)port list:mask 4 byte ea	*/
	O_IP_DSTPORT_RANGE = 12,	/* (n)port list:mask 4 byte ea	*/
	O_PROTO = 13,			/* arg1=protocol		*/

	O_FRAG = 14,				/* none				*/
	O_IPTOS = 15,			/* arg1 = id			*/
	O_ICMPTYPE = 16,		/* u32 = icmp bitmap		*/

	O_LOG = 17,				/* ipfw_insn_log		*/
	O_ACCEPT = 18,			/* none				*/
	O_DENY = 19				/* none 			*/
};

enum acl_tokens
{
	TOK_ACCEPT = 0,
	TOK_DENY = 1,
	TOK_LOG = 2,

	TOK_FRAG = 3,
	TOK_IPTOS = 4,
	TOK_ICMPTYPE = 5,

	TOK_DSTIP = 6,
	TOK_SRCIP = 7,
	TOK_ANYIP = 8,
	TOK_PORT_EQ = 9,
	TOK_PORT_GT = 10,
	TOK_PORT_LT = 11,
	TOK_PORT_NEQ = 12,
	TOK_PORT_RANGE = 13,
	TOK_PROTO = 14
};

typedef struct _acl_insn
{
	enum acl_opcodes		opcode:8;
	unsigned char			len;	    /* number of 32-byte words */
	unsigned short		arg1;
} ACL_INSN;

typedef struct _acl_insn_ip {
	ACL_INSN 		o;
	struct in_addr	addr;
	struct in_addr	mask;
} ACL_INSN_IP;

typedef struct _acl_insn_port {
	ACL_INSN 		o;
	unsigned short	port[2];
} ACL_INSN_PORT;

typedef struct _acl_rule
{
    acl_list_t      list;
    unsigned short  rulenum;
    unsigned short  subnum;
    unsigned int    del;
    unsigned int    verdict; 
    unsigned short  act_ofs;
    unsigned short  cmd_len;
    unsigned int    pcnt;
    unsigned int    bcnt;
    ACL_INSN        cmd[0];
}ACL_RULE;

typedef struct _acl_rule_head
{
    acl_list_t      list;
    unsigned int    rulenum;
    unsigned int    count;
}ACL_RULE_HEAD;

typedef struct _acl_rule_entry
{
    unsigned int      rulenum;
    unsigned int      subnum;

    int op;
    unsigned short protonum;
    unsigned short tos;
    struct
    {
        unsigned long ip;
        unsigned long mask;
        union
        {
            struct
            {
                unsigned short port1, port2;
            } tcp;
            struct
            {
                unsigned short port1, port2;
            } udp;
            struct
            {
                unsigned char type;
            } icmp;
        } u;
    } src, dst;
    
    int fragment;
    int verdict;
}ACL_RULE_ENTRY;

typedef struct _acl_tuple
{
    struct
    {
        unsigned long ip;
        union
        {
            unsigned short all;

            struct
            {
                unsigned short port;
            } tcp;
            struct
            {
                unsigned short port;
            } udp;
            struct
            {
                unsigned char type;
            } icmp;
        } u;
    } src, dst;
    
    unsigned short protonum;
}ACL_TUPLE;

typedef struct _acl_notify
{
    int acl_notify_type;
    unsigned int rulenum;
    unsigned int subnum;
    unsigned int verdict;
#if 0
    int (*func)();
#endif
}ACL_NOTIFY;

extern NOTIFY_MC_ID mc_table;

int acl_add_rule(ACL_RULE* rule);
int acl_del_rule(int rulenum, int subnum, struct vty* vty);
int acl_del_allrule(int rulenum, struct vty* vty);
void __acl_get_rule_index(int rulenum, int subnum, int type, int* pos);
void acl_get_rule_index(int rulenum, int subnum, int type, int* pos);
ACL_RULE_ENTRY* __acl_get_rule(int rulenum, int subnum, int type, int* pos);
ACL_RULE_ENTRY* acl_get_rule(int rulenum, int subnum, int type, int* pos);
ACL_RULE_ENTRY* __acl_get_allrule(int rulenum, int type, int* count);
ACL_RULE_ENTRY* acl_get_allrule(int rulenum, int type, int* count);
int acl_notify_register(ACL_NOTIFY* notify, ZIPC_ID to);
int acl_notify_unregister(ACL_NOTIFY* notify, ZIPC_ID to);
int acl_pkt_match(ACL_TUPLE* tuple, unsigned int rulenum);
void acl_show_list(int rulenum, int show_run, struct vty* vty);

#endif
