#ifdef LTP_NIP_TEST

#ifndef __MSG_H__
#define __MSG_H__

#define     HTONL(x)    (x) = htonl((x))
#define     NTOHL(x)    (x) = ntohl((x))

#define     LTP_NIP_PORT    32151   // 调度数据所用的端口号

typedef char MODULE_TST_ITEM[32];

enum action {
    LN_DO_INIT = 0x01,      // 初始化测试
    LN_DO_CLEANUP,          // 结束测试，释放资源
    LN_DO_TUNNEL,           // 发送测试数据
    LN_ERROR = 0xee,
};

struct _tnnldata {
    u_long  handle;         // 测试例句柄
    int     port;           // 测试例发送数据使用的端口
};

struct _cleanupdata {
    u_long  handle;          // 需要终止测试例的句柄
};


struct _initdata {
    MODULE_TST_ITEM item;   // 测试用例的ID
    u_long  handle;         // 测试用例的句柄
};

struct ln_data {
    int     action;         // 调度指令
    char    data[128];      // 调度数据
};


#endif

#endif
