#ifndef IF_DSW_H
#define IF_DSW_H

#define IPQM_DSW_CORE (IPQM_BASE + 4)
#ifdef IPQM_MAX
#undef IPQM_MAX
#endif
#define IPQM_MAX    (IPQM_BASE + 5)

#define IP_DSW_SYSCALL_PORT 0
#define IP_DSW_SYSCALL_REGHOOK  1
#define IP_DSW_SYSCALL_IP2INDEX 2

struct ip_dsw_set_port
{
#define IP_DSW_ADD_PORT 0
#define IP_DSW_DEL_PORT  1
#define IP_DSW_CLR_PORT  2
    int cmd;
    unsigned short port;
};

struct ip_dsw_set_reghook
{
#define IP_DSW_REG   0
#define IP_DSW_UNREG 1
    int cmd;
};

struct ip_dsw_get_index
{
#define IP_DSW_INDEX 0
    int cmd;
    unsigned long ip;
};

struct ip_dsw_syscall
{
    int type;

    union
    {
        struct ip_dsw_set_reghook reghook;
        struct ip_dsw_set_port port;
        struct ip_dsw_get_index index;
    }u;
};

#endif
