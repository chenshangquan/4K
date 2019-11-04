#ifndef _NETCBB_SERV_H
#define _NETCBB_SERV_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#ifndef NETCBBS_OS_ANDROID

#define NETSERVICE_TELNETD  "telnetd" /* 宏定义telnetd */
#define NETSERVICE_SSH      "ssh"     /* 宏定义ssh */
#define NETSERVICE_FTPD     "ftpd"    /* 宏定义ftpd */
#define NETSERVICE_TFTPD    "tftpd"   /* 宏定义tftpd */
#define NETSERVICE_HTTPD    "httpd"   /* 宏定义httpd */

#define NETPROTO_TCP         "tcp"
#define NETPROTO_UDP         "udp"


typedef struct {
    s8  *pchServName;   /* 服务名 */
    u16  wPort;         /* 服务端口号 */
    s8  *pchProto;      /* 协议类型 */
    s8  *pchArgPath;
}TServInfo;


/************************************************************
 * 函数名 : NetServiceStart
 *
 * 功能 : 开启服务功能
 *
 * 描述 :
 *
 * 参数说明 :
 *      pchServName - 服务名
 *      ptParaM     - 指向TServInfo 的结构体指针
 *
 * 返回值 : OK    - 成功
 *          ERROR - 错误
 ***********************************************************/
s32 NetServiceStart(s8 *pchServName, TServInfo* ptParaM);

/************************************************************
 * 函数名 : NetServiceStop
 *
 * 功能 : 关闭服务功能
 *
 * 描述 :
 *
 * 参数说明 :
 *
 * 返回值 : OK    - 成功
 *          ERROR - 错误
 ***********************************************************/
s32 NetServiceStop(s8* pchServName, u16 wPort);

#else   /* NETCBBS_OS_ANDROID */

/* The service name below defined according to 'netstat -tap' */
#define NETSERVICE_TELNETD  "telnet"
#define NETSERVICE_FTPD     "ftp"
#define NETSERVICE_HTTPD    "webcache"

/* The service name below defined according to inetd.conf */
#define NET_TELNETD_CONF    "telnetd"
#define NET_FTPD_CONF       "ftpd"
#define NET_HTTPD_CONF      "httpd"

#define INETD_CONF_PATH     "/etc/inetd.conf"


/************************************************************
 * 函数名 : NetServiceFtpStart
 *
 * 功能 : 开启ftp服务
 *
 * 描述 :
 *
 * 参数说明 :
 *
 *
 * 返回值 : OK    - 成功
 *          ERROR - 错误
 ***********************************************************/
s32 NetServiceFtpStart();

/************************************************************
 * 函数名 : NetServiceFtpStop
 *
 * 功能 : 关闭ftp功能
 *
 * 描述 :
 *
 * 参数说明 :
 *
 * 返回值 : OK    - 成功
 *          ERROR - 错误
 ***********************************************************/
s32 NetServiceFtpStop();

/************************************************************
 * 函数名 : NetServiceTelnetStart
 *
 * 功能 : 开启telnet服务
 *
 * 描述 :
 *
 * 参数说明 :
 *
 *
 * 返回值 : OK    - 成功
 *          ERROR - 错误
 ***********************************************************/
s32 NetServiceTelnetStart();

/************************************************************
 * 函数名 : NetServiceTelnetStart
 *
 * 功能 : 关闭telnet服务
 *
 * 描述 :
 *
 * 参数说明 :
 *
 * 返回值 : OK    - 成功
 *          ERROR - 错误
 ***********************************************************/
s32 NetServiceTelnetStop();

/************************************************************
 * 函数名 : NetServiceHttpStart
 *
 * 功能 : 开启http服务
 *
 * 描述 :
 *
 * 参数说明 :
 *
 *
 * 返回值 : OK    - 成功
 *          ERROR - 错误
 ***********************************************************/
s32 NetServiceHttpStart();

/************************************************************
 * 函数名 : NetServiceHttpStop
 *
 * 功能 : 关闭http服务
 *
 * 描述 :
 *
 * 参数说明 :
 *
 * 返回值 : OK    - 成功
 *          ERROR - 错误
 ***********************************************************/
s32 NetServiceHttpStop();

#endif /* NETCBBS_OS_ANDROID */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif