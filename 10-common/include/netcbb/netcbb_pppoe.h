#ifndef _NETCBB_PPPOE_H_
#define _NETCBB_PPPOE_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#define PPPOE_VERSION               "2.4.5"                  /* PPPOE模块的版本号定义 */
#define PPPOE_DUMP_FILE             "/ramdisk/pppoeDump.txt" /* 当PPPOE模块运行在Debug模式时，一些重要信息输出的文件路径 */
#define PPPOE_LOG_FILE              "/ramdisk/pppoelog.txt"  /* 当PPPOE模块的日志文件路径 */
#define MAX_USENAME_LEN             (u16)255                 /* PPPOE拨号时使用的用户名的最大长度 */
#define MAX_PASSWORD_LEN            (u16)255                 /* PPPOE拨号时使用的密码的最大长度 */
#define MAX_SERVERNAME_LEN          (u16)255                 /* PPOE拨号时使用的指定ISP服务商名字的最大长度 */
#define MAX_VERSION_LEN             (u16)255                 /* PPPOE版本信息的最大长度 */
#define MIN_DIAL_RETRY              (u16)1                   /* 最小拨号尝试次数 */
#define MAX_DIAL_RETRY              (u16)10                  /* 最大拨号尝试次数 */
#define DEFAULT_DIAL_RETRY          (u16)3                   /* 默认的拨号尝试次数，超过该次数则认为拨号失败 */
#define MIN_LCP_ECHO_INTERVAL       (u16)1                   /* 最小的发送lcp-echo的时间间隔 */
#define MAX_LCP_ECHO_INTERVAL       (u16)255                 /* 最大的发送lcp-echo的时间间隔 */
#define DEFAULT_LCPECHO_INTERVAL    (u16)20                  /* 链接建立以后，发送LCP-ECHO包的默认时间间隔(单位是秒) */
#define MIN_LCPECHO_TIMEOUT         (u16)1                   /* 最小的lco-echo超时次数 */
#define MAX_LCPECHO_TIMEOUT         (u16)255                 /* 最大的lco-echo超时次数 */
#define DEFAULT_LCPECHO_TIMEOUT     (u16)3                   /* 链接建立以后，发送LCP-ECHO包的默认超时此时 */
#define MIN_AUTODIAL_INTERVAL       (u16)0                   /* 最小的自动拨号时间间隔 */
#define MAX_AUTODIAL_INTERVAL       (u16)10                  /* 最大的自动拨号时间间隔 */
#define DEFAULT_AUTODIAL_INTERVAL   (u16)1                   /* 断链后，再次自动拨号的默认等待时间(单位是秒) */

/* 上层业务程序调用PPPOE模块接口时出错返回值统一定义 */
#define PPPOE_OK                    (u16)0                   /* 调用成功时的返回值*/
#define PPPOE_INIT_NO_USERNAME      (u16)1                   /* 没有指定用户名时的返回值 */
#define PPPOE_INIT_NO_PASSWORD      (u16)2                   /* 没有指定登陆密码时的返回值 */
#define PPPOE_INIT_PARAM_INVALIDE   (u16)3                   /* 初始化时传入的参数不在最大最小值范围之内 */
#define PPPOE_START_NO_INIT         (u16)4                   /* 没有初始化 */
#define PPPOE_START_NO_REGCALLBACK  (u16)5                   /* 没有注册回调函数 */
#define PPPOE_CALLBACK_NULL         (u16)6                   /* 注册的回调函数为空指针 */
#define PPPOE_NOT_RUNNING           (u16)7                   /* 没有开启PPPOE服务 */
#define PPPOE_PARAMETER_NULL        (u16)8                   /* 获取版本信息时传入的指针为NULL */
#define PPPOE_CREAT_PIPE_FAILED     (u16)9                   /* 创建管道失败 */
#define PPPOE_CREAT_PROGRESS_FAILED (u16)10                  /* 创建子进程失败 */


/* 注意：上层业务程序不能在收到这些消息的回调函数中进行过多的处理，应该尽快返回，更不能调用pppoe模块的PppoeStart()、PppoeStop()函数，否则程序会阻塞 */

/* PPPOE模块调用上层业务程序注册的回调函数发送通知消息的消息ID号定义 */
/* 消息ID的基址--------保留1千个消息定以（9000--10000） */
#define PPPOE_MSG_BASE              (u32)9000

/* 因为用户名或者密码不正确而造成PPPOE模块拨号身份验证失败的通知消息 */
/* 消息内容--- 结构体TAuthFailed */
#define PPPOE_AUTH_FAILED_MSG       (u32)(PPPOE_MSG_BASE + 1)
	
/* 拨号超时通知消息 */
/* 消息内容--- 无 */
#define PPPOE_DIAL_TIMEOUT_MSG      (u32)(PPPOE_MSG_BASE + 2)

/* 建链通知消息,消息内容是新获得的IP地址 */
/* 消息内容--- 结构体TConnNotify */
#define PPPOE_LINK_UP_MSG           (u32)(PPPOE_MSG_BASE + 3)

/* 断链通知消息 */
/* 消息内容--- 无 */
#define PPPOE_LINK_DOWN_MSG         (u32)(PPPOE_MSG_BASE + 4)

/* 找不到指定的ISP服务商通知消息 */
/* 消息内容--- 结构体 TNoServer */
#define PPPOE_NO_REQUIREDSERVER_MSG (u32)(PPPOE_MSG_BASE + 5)
#define PPPOE_DIALING_MSG           (u32)(PPPOE_MSG_BASE + 6)

/* 找不到服务器、超时等情况 */
#define PPPOE_GENERAL_SERVER_ERROR_MSG     (u32)(PPPOE_MSG_BASE + 7)


/* 上层业务程序初始化PPPOE模块时使用的结构体 */
typedef struct  PppoeInitParam{
    char      abyUserName [MAX_USENAME_LEN];     /* 拨号时使用的用户名,必填项 */
    char      abyPassword [MAX_PASSWORD_LEN];    /* 拨号时使用的密码,必填项 */
    char      abyServerName[MAX_SERVERNAME_LEN]; /* 指定拨号服务商的名字,可以不填 */
    BOOL32    bAutoDialEnable;                   /* 是否允许断链后自动拨号,默认不自动拨号,只有启用自动拨号后，重播次数和重拨时间才有意义。否则无效 */
    BOOL32    bDefaultRouteEnable;               /* 是否允许将对端的地址设为默认网关，默认不设为网关 */
    BOOL32    bDebug;                            /* 是否以debug模式运行pppoe，默认不运行在debug模式 */
    u32       dwAutoDialInterval;                /* 断链后再次自动拨号需要等带的时间（允许设置成0s）*/
    u16       wDialRetryTimes;                   /* 拨号尝试的次数，如果达到该次数还没有响应则拨号失败,默认为10，为0则无限制拨号 */
    u16       wLcpEchoSendInterval;              /* 链接建立后，发送LCP-ECHO包的时间间隔,默认设置为20 */
    u16       wLcpEchoRetryTimes;                /* 发送几次LCP-ECHO包没有得到相应则认为链接断开,默认设置为3 */
    u32       dwEthID;                           /* PPPOE服务需要绑定的以太网的ID号（从0开始）*/
}TPppoeInitParam;



/*上层业务程序注册的回调类型定义*/
/*参数说明 : u32 dwMsgID   - 消息的ID号,由PPPOE模块填充
             u8 *pbyMsg    - 指向消息内容的指针,由PPPOE模块填充
             u32 dwMsgLen  - 消息内容的有效长度,由PPPOE模块填充 */
typedef void (*TPppoeCallBack)(u32 dwMsgID, u8* pbyMsg, u32 dwMsgLen);


/*有关PPPOE模块各种统计信息的结构体*/
typedef struct PppoeStates{
    BOOL32  bPppoeRunning;                       /* PPPOE是否运行，TRUR—运行；FALSE—没有运行 */
    u32     dwLocalIpAddr;                       /* 本机IP地址,网络序 */
    u32     dwPeerIpAddr;                        /* 对端IP地址,网络序 */
    char    abyServerName[MAX_SERVERNAME_LEN];   /* ISP Server的名字 */
    u32     dwLinkKeepTimes;                     /* 链路建立的时间 */
    u32     dwLinkDownTimes;                     /* 链路断链的次数统计 */
    u32     dwPktsSend;                          /* 总共发送的数据包数--包括各类协议包以及上层业务程序的数据包 */
    u32     dwPktsRecv;                          /* 总共接收的数据包数 */
    u32     dwBytesSend;                         /* 总共发送的字节数 */
    u32     dwBytesRecv;                         /* 总共接收的字节数 */
}TPppoeStates;

/* 调用上层业务程序注册的回调函数发送认证失败时消息的内容结构体 */
typedef struct AuthFailed{
    char  abyUserName[MAX_USENAME_LEN];          /* 业务程序给的拨号时使用的用户名 */
    char  abyPassword[MAX_PASSWORD_LEN];         /* 业务程序给的拨号时使用的密码 */
}TAuthFailed;

/* 调用上层业务程序注册的回调函数发送建链通知消息的结构体 */
typedef struct ConnNotify{
    u32  dwOurIpAddr;   /* 本断获得的IP地址,网络序 */
    u32  dwPeerIpAddr;  /* 对端的IP地址 */
    u32  dwDnsServer1;  /* DNS Server1,网络序 */
    u32  dwDnsServer2;  /* DNS Server1,网络序 */
}TConnNotify;

/* 通知业务程序找不到指定的ISP Server的消息结构体 */
typedef struct NoServer{
    char  abyServerName[MAX_SERVERNAME_LEN]; /* ISP Server的名字 */
}TNoServer;

/*存储PPPOE版本信息的结构体*/
typedef struct Version{
    char  abyVersion[MAX_VERSION_LEN];
}TVersion;


/************************************************************
 * 函数名 : PppoeStart
 *
 * 功能 : 启动PPPoE服务
 *
 * 描述 : 原PppoeInit和PppoeCallBackReg都集成在NetPppoeStart中		
 *
 * 参数说明 :
 *
 * 返回值 : oK - 成功
 *          ERROR - 失败
 *          参考netcbb_def.h
 ***********************************************************/
s32 NetPppoeStart(TPppoeInitParam* ptPppoeInitParam, TPppoeCallBack ptNotifyCallBack);

/************************************************************
 * 函数名 : PppoeStop
 *
 * 功能 : 停止PPPoE服务
 *
 * 描述 :
 *
 * 参数说明 :
 *
 * 返回值 : #define PPPOE_ OK           0
 *          #define PPPOE_NOT_RUNNING   6
 ***********************************************************/
s32 NetPppoeStop(void);

/************************************************************
 * 函数名 : NetPppoeStatesDump
 *
 * 功能 : 获取PPPoE模块的统计信息
 *
 * 描述 : 不提供支持
 *
 * 参数说明 :
 *      ptPppoeStates - 指向存放统计结果的指针
 *
 * 返回值 : 无
 ***********************************************************/
void NetPppoeStatesDump(TPppoeStates* ptPppoeStates);

/************************************************************
 * 函数名 : NetPppoeVer
 *
 * 功能 : 获取PPPoE模块的版本信息
 *
 * 描述 :
 * 
 * 参数说明 :
 *      ptVersion - 指向存放版本信息的指针
 *
 * 返回值 : OK    - 成功
 *          ERROR - 失败
 ***********************************************************/
s32 NetPppoeVer(TVersion* ptVersion);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _NETCBB_PPPOE_H_ */

