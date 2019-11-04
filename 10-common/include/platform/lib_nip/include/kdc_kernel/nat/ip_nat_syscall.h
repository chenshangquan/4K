#ifndef _IP_NAT_SYSCALL_H
#define _IP_NAT_SYSCALL_H

#define IP_NAT_SYSCALL_ENABLE 0
#define IP_NAT_SYSCALL_TIMEOUT 1
#define IP_NAT_SYSCALL_DEBUG 2
#define IP_NAT_SYSCALL_CLR 3

#define IP_NAT_DEBUG_EVENT 0x01 
#define IP_NAT_DEBUG_PACKET 0x02

#define NAT_MIN_TIMEOUT 10
#define NAT_MAX_TIMEOUT 600
#define NAT_ICMP_DFT_TIMEOUT 20
#define NAT_UDP_DFT_TIMEOUT 40
#define NAT_TCP_DFT_TIMEOUT 240

struct ip_nat_syscall
{
    int type;

    union
    {
        int nat_enable;
        struct 
        {
            int enable;
            int debug_type;
        }debug;
        struct 
        {
            int proto;
            int timeout;
        }timeout;
    }u;
};

#endif
