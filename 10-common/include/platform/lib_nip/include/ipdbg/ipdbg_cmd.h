
#define IPDBG_DEBUG(fmt, args...)   zlog_msg(NULL, ZLOG_DEBUG, fmt, ##args)
#define IPDBG_INFO(fmt, args...)     zlog_msg(NULL, ZLOG_INFO, fmt, ##args)
#define IPDBG_NOTIFY(vty, fmt, args...)    vty_out(vty, fmt, ##args)
#define IPDBG_ERROR(fmt, args...)    zlog_msg(NULL, ZLOG_ERROR, fmt, ##args)
#define IPDBG_SHOW(vty, fmt,args...)      vty_out(vty, fmt,##args)


#define ARP_ON              257
#define ARP_OFF            -257
#define IP_ON                 258
#define IP_OFF               -258
#define IP_ICMP_ON      1
#define IP_ICMP_OFF    -1
#define IP_TCP_ON        6
#define IP_TCP_OFF      -6
#define IP_UDP_ON       17
#define IP_UDP_OFF     -17
#define IP_DETAIL_ON   259
#define IP_DETAIL_OFF -259
#define PTHREAD_CLOSE 886
