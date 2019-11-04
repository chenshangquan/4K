#ifndef DATASWITCH_H
#define DATASWITCH_H

#define IP_DSW_ADD_PORT 0
#define IP_DSW_DEL_PORT 1
#define IP_DSW_CLR_PORT 2

#define IP_DSW_REG   0
#define IP_DSW_UNREG 1

typedef char* (*DSW_BCALLFUNC)(char* buf, unsigned short recv_len, unsigned short* sent_len);

int ip_dsw_enable(unsigned short datalen, DSW_BCALLFUNC func);
int ip_dsw_disable();
int ip_dsw_set_port(int cmd, unsigned short port);
int ip_dsw_get_index(unsigned long ip);
int ip_dsw_core();
int ip_dsw_cleanup();
int ip_dsw_init();

#endif
