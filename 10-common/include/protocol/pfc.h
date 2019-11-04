/******************************************************************************
模块名  ： PFC - Platform/Protocol foundation classes
文件名  ： pfc.h
相关文件：
文件实现功能:   Origined from OSP(Ver: CBB 5.0 20170727) to implement both support for 32bit and 64 bit OS.
                For protocol team related modules use only.
                ultimate goal would be merge this module back into OSP whenever OSP is ready.
作者    ：韦国华
版本    ：1.0.0.1
---------------------------------------------------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
09/15/98        1.0      某某        ------------
******************************************************************************/

#ifndef _PFC_H
#define _PFC_H

#include "protocolcommonpublic.h"

#if (defined(__APPLE__) && defined(__MACH__)) || (defined(macintosh) || defined(Macintosh)) || defined(__MACOSX__)
    #define _IOS_PLATFORM_
    #define _LINUX_
#endif // for ios


/**
 * @defgroup    pfc Platform/Protocol foundation classes
 * @brief       Platform/Protocol foundation interfaces.
 * @{
 */

//#define _ENABLE_SOCK5_API_
//#define _ENABLE_SERIAL_API_
#define PFC_ENABLE_IPV6

///////////////////////////////////////////////////////////////////
//	Linux 操作系统头文件
///////////////////////////////////////////////////////////////////
#if (defined(_LINUX_) || defined(_IOS_PLATFORM_))
#ifdef PWLIB_SUPPORT
#include <ptlib.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>
#ifdef _IOS_PLATFORM_
#include <malloc/malloc.h>
#else
#include <malloc.h>
#endif
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/times.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <termios.h>
#include <signal.h>
#include "syslog.h"

/* 5.0合并： 整合Android平台支持 */
#if defined(_ANDROID_)
#include <sys/epoll.h>
#include <fcntl.h>
#elif (!(defined(_EQUATOR_) || defined(_IOS_PLATFORM_)))
#include <mqueue.h>
#include <sys/epoll.h>
#include <sys/resource.h>
#endif
#endif //_LINUX_

///////////////////////////////////////////////////////////////////
//	Vxworks 操作系统头文件
///////////////////////////////////////////////////////////////////
#ifdef _VXWORKS_

#include <vxworks.h>
#include <tasklib.h>
#include <msgqlib.h>
#include <syslib.h>
#include <string.h>
#include <memLib.h>
#include <stdlib.h>
#include <string.h>
#include <sockLib.h>
#include <inetLib.h>
#include <stdioLib.h>
#include <strLib.h>
#include <hostLib.h>
#include <ioLib.h>
#include <assert.h>
#include <netdb.h>
#include <errno.h>
#include <sys/stat.h>
#include <taskHookLib.h>
#include <logLib.h>
//串口支持
#include "brddrvlib.h"

#endif // _VXWORKS_

///////////////////////////////////////////////////////////////////
//	Win32 操作系统头文件
///////////////////////////////////////////////////////////////////
#ifdef _MSC_VER
#pragma warning(disable:4127)
#pragma warning(disable:4996)
//lint -e728

#ifdef _WIN32_WINNT
#undef _WIN32_WINNT
#endif

#ifdef WINVER
#undef WINVER
#endif
/* vc is vs2005 and later */
#if (_MSC_VER >= 1400)
#define _WIN32_WINNT 0x0501 //support only winxp and above
#define WINVER 0x0501 //support only winxp and above
#else
#define _WIN32_WINNT 0x400
#define WINVER 0x0400
#endif

#include <malloc.h>
#include <time.h>

#ifdef _AFXDLL
#include <afx.h>
#include <afxwin.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#endif

#include <assert.h>
#pragma comment(lib,"Ws2_32.lib")

#endif  // _MSC_VER

#include "kdvtype.h"

///////////////////////////////////////////////////////////////////
//	操作系统相关数据类型定义
///////////////////////////////////////////////////////////////////
#ifdef _LINUX_
    #define TRUE                    1                       ///< TRUE
    #define FALSE                   0                       ///< FALSE
    typedef void *(*LINUXFUNC)(void *);                     ///< Common callback function definition
    #define PFCSEMHANDLE            pthread_cond_t*         ///< PFC sem handle
    #define PFCTASKHANDLE           pthread_t               ///< PFC thread handle
    #define PFCTASKID				PFCTASKHANDLE           ///< PFC thread id
#endif  // _LINUX_

#ifdef _VXWORKS_
    #define PFCSEMHANDLE            SEM_ID                  ///< PFC sem handle for vxworks
    #define PFCTASKHANDLE           u32                     ///< PFC thread handle for vxworks
#endif  // _VXWORKS_

#ifndef _MSC_VER
    /* 5.0合并： 去除u64定义, u64已经定义在kdvtype.h中. */
    //	typedef unsigned long long    u64;
    #define PFCSOCKHANDLE           int                     ///< PFC socket handle
    #ifndef SOCKADDR
        #define SOCKADDR            sockaddr                ///< PFC sock address
    #endif
    #define SOCKADDR_IN             sockaddr_in             ///< PFC sockaddr_in
    #define SOCKADDR_IN6            sockaddr_in6            ///< PFC sockaddr_in6
#endif  // _MSC_VER

#ifdef _MSC_VER
    #define PFCSEMHANDLE            HANDLE                  ///< PFC sem handle
    #define PFCTASKHANDLE           HANDLE                  ///< PFC thread handle
    #define PFCSOCKHANDLE           SOCKET                  ///< PFC sock handle
#endif  // _MSC_VER

///////////////////////////////////////////////////////////////////
//	操作系统相关宏定义
///////////////////////////////////////////////////////////////////
#ifdef _LINUX_
    #define SOCKET_ERROR          (-1)                      ///< SOCKET error
    #define INVALID_SOCKET        (-1)                      ///< Invalid socket handle
    #define OSP_NO_WAIT           0                         ///< no wait
    #define OSP_WAIT_FOREVER      (-1)                      ///< wait forever
#endif // _LINUX_

#ifdef _VXWORKS_
    #define SOCKET_ERROR          ERROR
    #define INVALID_SOCKET        ERROR
    #define INVALID_SERIALHANDLE  ERROR
    #define OSP_NO_WAIT           NO_WAIT
    #define OSP_WAIT_FOREVER      WAIT_FOREVER
#endif  // _VXWORKS_

#ifdef _MSC_VER
    #define INVALID_SERIALHANDLE  INVALID_HANDLE_VALUE
    #define OSP_NO_WAIT           ((int)0)
    #define OSP_WAIT_FOREVER      ((int)-1)
#endif  // _MSC_VER

///////////////////////////////////////////////////////////////////
//	操作系统无关宏定义
///////////////////////////////////////////////////////////////////
// for Microsoft c++
#ifdef _MSC_VER

//紧排列
#ifndef _EQUATOR_
#pragma pack(push)
#pragma pack(1)
#endif

#define API extern "C"          __declspec(dllexport)
#define PFC_API                 __declspec(dllexport)

// for gcc
#else

#define API extern "C"
#define PFC_API

#endif  // _MSC_VER


/// PFC版本信息
#define PFCVERSION              "PFC.1.0.1.20170727"

/// PfcSockShutdown参数
#define STOP_RECV               0
#define STOP_SEND               1
#define STOP_BOTH               2

#define PFC_VERSION_ID          0x52            ///< PFC版本号

#ifndef MULTI_LISTEN_SOCKET_SUPPORT
    #define MULTI_LISTEN_SOCKET_SUPPORT 1       ///< 5.0合并： 原行业特性，支持一个PFC创建多个PFC server
#endif

#ifdef MULTI_LISTEN_SOCKET_SUPPORT
    const u32 PFC_MAX_LISTEN_SOCK_NUM    = 16;  ///< 5.0合并： 最大可支持的PFC server数量
#endif //MULTI_LISTEN_SOCKET_SUPPORT

/// 同一结点最大应用数
/* 5.0合并：  增大app个数, 从512增大到4096, 增大app个数后AppPool会消耗更多内存 */
const u16 PFC_MAX_APP_NUM            = 4096;
const u16 PFC_MAX_INST_NUM           = 65000;   ///< 同一应用最大实例数
const u16 PFC_MAX_TIMER_NUM          = 5000;    ///< 最大定时器数
const u8  PFC_MAX_SERIALPORT_NUM     = 10;      ///< 最大串口数

#define INVALID_NODE             0              ///< 无效的外部结点号
#define LOCAL_NODE               0              ///< 本地结点号
#define INVALID_APP              0              ///< 无效的应用号
#define LOCAL_APP                0              ///< 本地全局应用号
#define INVALID_INS              0xfffb         ///< 无效的实例号
#define LOCAL_INS                0              ///< 本地实例号
#define DEFAULT_TCP_HEARTBEAT_TIME      10      ///< 默认TCP断链检测时间间隔(秒)
#define DEFAULT_TCP_HEARTBEAT_NUM       3       ///< 默认TCP断链检测次数(多次检测均失败认为已经断链)
#define DEFAULT_STATUS_MSGOUT_TIME      3600    ///< 默认OSP系统状态打印时间间隔(秒)
#define UNDETECT_TCP_HEARTBEAT          0       ///< 不进行TCP断链检测

#ifndef MINCHAR
    #define MINCHAR                 0x80
#endif

#ifndef MAXCHAR
    #define MAXCHAR                 0x7f
#endif

#ifndef MINSHORT
    #define MINSHORT                0x8000
#endif

#ifndef MAXSHORT
    #define MAXSHORT                0x7fff
#endif

#ifndef MINLONG
    #define MINLONG                 0x80000000
#endif

#ifndef MAXLONG
    #define MAXLONG                 0x7fffffff
#endif

#ifndef MAXBYTE
    #define MAXBYTE                 0xff
#endif

#ifndef MAXWORD
    #define MAXWORD                 0xffff
#endif

#ifndef MAXDWORD
    #define MAXDWORD                0xffffffff
#endif

#ifdef _ENABLE_SERIAL_API_
    #include "pfc_serial.h"
#endif

#if (defined(_MSC_VER) && (_MSC_VER > 1200)) || !defined(_MSC_VER)
/**
* @brief    PfcNetAddr
* @note     5.0合并： 增加IP地址类型的定义
* @pre      windows 要VS2010才能使用ipv6
*/
typedef union tagPfcNetAddr
{
    struct sockaddr_in		v4addr;                 ///< ipv4地址
    struct sockaddr_in6		v6addr;                 ///< ipv6地址
    struct sockaddr_storage staddr;                 ///< socket表示的地址
    u8  raw_addr[sizeof(struct sockaddr_storage)];  ///< socket无法表示的私有地址类型
} TPfcNetAddr;
#else
/**
* @brief    PfcNetAddr
* @note     5.0之前版本定义的IP地址类型的定义
*/
typedef union tagPfcNetAddr
{
    struct sockaddr_in		v4addr;                 ///< ipv4地址
    u8 raw_addr[128];                               ///< 裸地址串
} TPfcNetAddr;
#endif

/// 根据结点号，APP号和本地实例号构造全局实例ID
inline u32  PFC_MAKEIID( u16 app, u16 ins = 0 , u8 = 0 )
{
	return u32(app << 16) + ins;
}

/// 从ID中获得应用号
inline u16 PFC_GETAPP( u32 GlobIID )
{
	return (u16)(GlobIID >> 16);
}

/// 从ID中获得网关号
inline u8 PFC_GETGATE( u32 = 0 )
{
	return 0;
}

/// 从ID中获得实例号
inline u16 PFC_GETINS( u32 GlobIID )
{
	return (u16)(GlobIID);
}

/// 从ID中获得实例号的低字节
inline u8 PFC_GETINSL( u32 GlobIID )
{
	return (u8)(GlobIID);
}

/// 从ID中获得实例号的高字节
inline u8 PFC_GETINSH(u32 GlobIID)
{
	return (u8)(GlobIID >> 8);
}

/// telnet终端提示符最大长度
#define MAX_PROMPT_LEN          21

/// PFC错误码
enum EM_PFC_ERRORCODE
{
    PFC_ERROR_BASE              = 0,
    PFC_OK                      = (PFC_ERROR_BASE + 0),     ///< 操作成功
    PFC_ERROR                   = (PFC_ERROR_BASE + 1),     ///< 操作失败
    PFC_ERR_SEND_FAIL           = (PFC_ERROR_BASE + 2),     ///< 未使用
    PFC_ERR_SEND_TIMEOUT        = (PFC_ERROR_BASE + 3),     ///< 发送同步消息超时
    PFC_ERR_SYNCACK_EXCEED      = (PFC_ERROR_BASE + 4),     ///< 同步消息应答超长
    PFC_ERR_ALIAS_REPEAT        = (PFC_ERROR_BASE + 5),     ///< 同一应用下实例别名已经存在
    PFC_ERR_APP_REPEAT          = (PFC_ERROR_BASE + 6),     ///< 未使用
    PFC_ERR_NODE_INVALID        = (PFC_ERROR_BASE + 7),     ///< 外部结点号无效
    PFC_ERR_ILLEGAL_PARAM       = (PFC_ERROR_BASE + 8),     ///< 参数无效
    PFC_ERR_PEER_NOT_RESPOND    = (PFC_ERROR_BASE + 9),     ///< 同步消息对端无应答
};

#define MAX_MSG_LEN             (u16)0xffff                 ///< 最大消息长度 /* 5.0合并： 对齐原行业会议， 原企业消息最大长度为0x8000*/
#define MAX_ALIAS_LEN           (u8)255                     ///< 实例别名最大长度
#define MAX_SYNCACK_LEN         MAX_MSG_LEN                 ///< 最大同步消息应答长度
#define MAX_DATA_LEN            (MAX_MSG_LEN+MAX_ALIAS_LEN+MAX_SYNCACK_LEN) ///< 最大数据长度(未使用)

/// PFC消息类型
enum EM_PFC_MSGTYPE
{
    PFC_MSG_TYPE_ASYNC              = (u16)0,               ///< 异步消息
    PFC_MSG_TYPE_SYNC               = (u16)1,               ///< 同步消息
    PFC_MSG_TYPE_SYNCACK            = (u16)2,               ///< 同步应答消息
    PFC_MSG_TYPE_GSYNC              = (u16)3,               ///< 全局同步消息
    PFC_MSG_TYPE_GSYNCACK           = (u16)4,               ///< 全局同步应答消息
    PFC_MSG_TYPE_TIMEOUT            = (u16)5,               ///< 超时消息
    PFC_MSG_TYPE_RAWMSG             = (u16)6,               ///< 5.0合并： 原行业特有定义， raw消息类型
};

#define PFC_NEXTSTATE(x)            NextState(x,#x)         ///< 切换实例状态机
#define PFC_OSP_USEREVENT_BASE      (u16)0x0400             ///< PFC 用户自定义消息事件号基准(小于该值的消息为PFC保留消息，上层禁止发送该消息)
#define PFC_OSPEVENT(x,y)           const u16 x = y         ///< 定义消息事件号

PFC_OSPEVENT(PFC_OSP_CONFIRM,       0xff);                  ///< 未使用
PFC_OSPEVENT(PFC_OSP_POWERON,       0x100);                 ///< 启动断链检测
PFC_OSPEVENT(PFC_OSP_SWITCHMASTER,  0x101);                 ///< 未使用
PFC_OSPEVENT(PFC_OSP_SWITCHSLAVE,   0x102);                 ///< 未使用
PFC_OSPEVENT(PFC_OSP_OVERFLOW,      0x103);                 ///< 服务端无空闲实例
PFC_OSPEVENT(PFC_OSP_EXCEPTION_IND, 0x104);                 ///< 未使用
PFC_OSPEVENT(PFC_OSP_INSNOTEXIST,   0x105);                 ///< 未使用
PFC_OSPEVENT(PFC_OSP_DISCONNECT,    0x106);                 ///< 与远端结点的TCP链路已断
PFC_OSPEVENT(PFC_OSP_BROADCASTACK,  0x107);                 ///< 广播消息确认应答
PFC_OSPEVENT(PFC_OSP_NODECLOSE,     0x108);                 ///< 未使用
PFC_OSPEVENT(PFC_OSP_NETBRAECHO,    0x109);                 ///< 断链检测探测消息
PFC_OSPEVENT(PFC_OSP_NETBRAECHOACK, 0x110);                 ///< 断链检测探测消息确认应答
PFC_OSPEVENT(PFC_OSP_QUIT,          0x120);                 ///< OSP卸载消息
PFC_OSPEVENT(PFC_OSP_NETSTATEST,    0x121);                 ///< 结点间通信测试消息
PFC_OSPEVENT(PFC_OSP_NETSTATESTACK, 0x122);                 ///< 结点间通信测试消息确认应答
PFC_OSPEVENT(PFC_OSP_APPCONN_ACK,   0x123);                 ///< 未使用

/// Trc跟踪标志
typedef enum PFC_TRCOPTION
{
    PFC_TRCSTATE     = 1,                                   ///< 跟踪状态迁移
	PFC_TRCEVENT     = 2,                                   ///< 跟踪事件
	PFC_TRCTIMER     = 4,                                   ///< 跟踪定时器
} PFC_TRCOPTION;

#define PFC_TRCALL     (u16)(PFC_TRCSTATE|PFC_TRCEVENT|PFC_TRCTIMER)    ///< 状态跃迁、事件、定时器均跟踪

/// 1.1版以后支持同步消息
#if (defined PFC_VERSION_ID) && (PFC_VERSION_ID >= 0x11)
#define PFC_SYNCMSG
#endif

#ifdef _LINUX_
/**
 * @brief       CTiPfcStream
 * @note        用于网络传输数据流的类
 * 任何一个结构要在网络上传输，都写入一个数据流对象中，
 * 然后把此数据流对象OSP，让OSP来传输
 * 不要再直接使用传输一个结构
 */
class CTiPfcStream
{
public:
    u32 m_dwCurrSize;                                   	///< 当前数据长度
	u8 m_achData[MAX_MSG_LEN];                              ///< 当前数据

    /// Construction
	CTiPfcStream()
	{
		m_dwCurrSize = 0;
		memset(m_achData, 0, sizeof(m_achData));
	}
	/// 5.0合并： 原行业特有， 处理raw消息
	BOOL32 IsRawMsg()
	{
		return !memcmp(m_achData , "kedacom" , 7);
	}
    /// Get raw stream data length
	u32 GetRawLen()
	{
		u32 *pLen = (u32 *)(m_achData + 7);
		return htonl(*pLen);
	}

    /// Pack the stream element
	u32  PackElement(const u8 *pData, u32 dwLen);
    /// Unpack the stream element
	u32  ExtractElement(u8 *pData, u32 dwLen);
};

#define PackElement2(data)  PackElement((u8*)&data, sizeof(data))
#define ExtractElement2(data)   ExtractElement((u8*)&data, sizeof(data))

/// PFC消息头部结构
class CTiMessage
{
public:
    u32 srcnode;                                            ///< 源结点
    u32 dstnode;                                            ///< 目的结点
    u32 dstid;                                              ///< 目的应用实例
    u32 srcid;                                              ///< 源目的实例
    u16 type;                                               ///< 消息类型
    u16 event;                                              ///< 消息号
    u16 length;                                             ///< 消息体长度
    u8 *content;                                            ///< 消息体

    /// 如果支持同步消息
#ifdef PFC_SYNCMSG
    u8 *output;                                             ///< 同步消息应答
    u16 outlen;                                             ///< 同步消息应答长度
    u16 expire;                                             ///< 未使用
#endif
    char *dstAlias;                                         ///< 实例别名
    u8 dstAliasLen;                                         ///< 实例别名长度

#ifndef _MSC_VER
    /// 得到PFC消息头部长度
	static u32 GetPackedSize()
	{
		return sizeof(u32) + sizeof(u32) + sizeof(u32) + sizeof(u32) + sizeof(u16) +
			   sizeof(u16) + sizeof(u16) + sizeof(u32) +
#ifdef PFC_SYNCMSG
			   sizeof(u32) + sizeof(u16) + sizeof(u16) +
#endif
			   sizeof(u32) + sizeof(u8);
	}

#else //32bit
    /// 得到PFC消息头部长度
	static u32 GetPackedSize()
	{
		return sizeof(u32) + sizeof(u32) + sizeof(u32) + sizeof(u32) + sizeof(u16) +
			   sizeof(u16) + sizeof(u16) + sizeof(u8 *) +
#ifdef PFC_SYNCMSG
			   sizeof(u8 *) + sizeof(u16) + sizeof(u16) +
#endif
			   sizeof(char *) + sizeof(u8);
	}

#endif
    void Pack(CTiPfcStream &tStream);                       ///< OSP消息头部打包
    void Extract(CTiPfcStream &tStream);                    ///< PFC消息头部解包
};

#else
/// PFC消息头部结构
typedef struct CTiMessage
{
    
    u32 srcnode;                                            ///< 源结点
    u32 dstnode;                                            ///< 目的结点
    u32 dstid;                                              ///< 目的应用实例
    u32 srcid;                                              ///< 源目的实例
    u16 type;                                               ///< 消息类型
    u16 event;                                              ///< 消息号
    u16 length;                                             ///< 消息体长度
    u8 *content;                                            ///< 消息体
    /// 如果支持同步消息
#ifdef PFC_SYNCMSG
    u8 *output;                                             ///< 同步消息应答
    u16 outlen;                                             ///< 同步消息应答长度
    u16 expire;                                             ///< 未使用
#endif
    char *dstAlias;                                         ///< 实例别名
    u8 dstAliasLen;                                         ///< 实例别名长度
}

/// 紧排列
#if defined(_VXWORKS_) || (defined(_LINUX_) && !defined(_EQUATOR_))
__attribute__ ((packed))
#endif
CTiMessage;
#endif

/// 实例简要信息
typedef struct
{
	u32 state;                                              ///< State
	u16 insid;                                              ///< instance id
	u16 evtrcv;                                             ///< total received events
	u16 evtsnd;                                             ///< total sent events
} TTiInstInfo;

/// 5.0合并： 原行业特有接口，创建裸消息监听节点的回调
typedef BOOL32 (*CB_FUNC_PFC_CREATE_RAW_NODE)(int nNodeId , u16 *pwAid, u32 dwAddr , u16 wPort);

/// 5.0合并： 原行业特有接口，设置app处理裸消息的回调
typedef void (*CB_FUNC_PFC_RCV_RAW_MSG)(MemId dwContext, int nNodeId , const char *pchMsg , u32 dwLen );
#define MAX_INSTINFO_NUM           100                      ///< 单个应用中可保存的最大实例简要信息个数

#if defined(PWLIB_SUPPORT) && defined(_LINUX_)
/// 应用抽象基类，主要用于定义用户App模板zTemplate
class CTiApp : public PThread
#else
/// 应用抽象基类，主要用于定义用户App模板zTemplate
struct PFC_API CTiApp
#endif
{
#if defined(PWLIB_SUPPORT) && defined(_LINUX_)
	PCLASSINFO(CTiApp, PThread);
#endif

public:
    u32 msgIncome;                                          ///< 应用接收消息总数
    u32 msgProcessed;                                       ///< 应用已处理消息总数
    u32 msgWaiting;                                         ///< 应用邮箱中待处理的消息总数 - 未使用
    u32 msgWaitingTop;                                      ///< 应用邮箱中待处理的消息总数峰值
    u32 timerProcessed;                                     ///< 已激发的定时消息总数
    u32 maxMsgWaiting;                                      ///< 应用邮箱最大消息容量
    u32 msgdropped;                                         ///< 因邮箱满丢弃的消息总数
    char *pAppName;                                         ///< 应用别名
    kdvHandle queSendId;                                    ///< 应用主邮箱写句柄
    kdvHandle queRcvId;                                     ///< 应用主邮箱读句柄

    /// 为支持同步消息而增加的消息备份队列，存放同步消息发送后，应答超时消息
	/// 或应答消息到达之前的所有消息
    u32 bakQueMsgNum;                                       ///< 应用备邮箱中的消息总数
    kdvHandle bakQueSendId;                                 ///< 应用备邮箱写句柄
    kdvHandle bakQueRcvId;                                  ///< 应用备邮箱读句柄

    u32 taskID;                                             ///< 应用任务ID

    CTiMessage *curMsgRcv;                                  ///< 当前收到的消息
    u16 scrnTraceFlag;                                      ///< 屏幕trc标志
    u16 fileTraceFlag;                                      ///< 文件trc标志
    u16 appId;                                              ///< 应用ID
    u16 wLastIdleInstID;                                    ///< 应用前一个空闲实例号
    u16 curEvtSnd;                                          ///< 当前发送的消息号
    u8 scrnLogFlag;                                         ///< 屏幕log级别
    u8 fileLogFlag;                                         ///< 文件log级别

    PFCTASKHANDLE hAppTask;                                 ///< 应用任务句柄
    PFCSEMHANDLE tSemMutex;                                 ///< 应用任务信号量句柄

    u8 byAppPri;                                            ///< 应用任务优先级

    /// 用于记录实例最近状态和收到数据的环行缓冲
    u8 byInstInfoHead;                                      ///< loop buffer header
    u8 byInstInfoTail;                                      ///< loop buffer tail
    TTiInstInfo tInstInfo[MAX_INSTINFO_NUM];                ///< loop buffer

    /// 5.0合并： 原行业osp特有结构， 处理raw消息
    CB_FUNC_PFC_RCV_RAW_MSG m_cbMsg;                        ///< raw msg call back function pointer
    MemId                 m_dwContext;                      ///< raw msg call back user context

    BOOL32 bDropFlag;                                       ///< drop msg indication

public:
    /// Construction
#if defined(_LINUX_) && defined(PWLIB_SUPPORT)
	CTiApp() : PThread(200 << 10)
#else
	CTiApp()
#endif
	{
		msgIncome = 0;
		msgProcessed = 0;
		timerProcessed = 0;
		maxMsgWaiting = 0;
		msgdropped = 0;
		msgWaitingTop = 0;
		pAppName = NULL;
		queSendId = 0;
		queRcvId = 0;
		bakQueMsgNum = 0;
		bakQueSendId = 0;
		bakQueRcvId = 0;
		taskID = 0;
		scrnTraceFlag = 0;
		fileTraceFlag = 0;
		scrnLogFlag = 0;
		fileLogFlag = 0;
		appId = INVALID_APP;
		byAppPri = 100;
		wLastIdleInstID = 0;
		hAppTask = 0;
#ifndef _LINUX_
		tSemMutex = NULL;
#endif
		byInstInfoHead = 0;
		byInstInfoTail = 0;

		curMsgRcv = NULL;
		curEvtSnd = 0;

		m_cbMsg = NULL;
		m_dwContext = 0;

		bDropFlag = FALSE;
	}

	virtual ~CTiApp()
	{
		scrnTraceFlag = 0;
		fileTraceFlag = 0;
		scrnLogFlag = 0;
		fileLogFlag = 0;
	}

	/// 根据实例号查询指定实例
	virtual class CTiInstance *GetInstance(u16 insid) = 0;
	/// 设定实例别名
	virtual BOOL32 SetInstAlias(u16 insid, const char *pAlias, u8 len) = 0;
	/// 根据别名查询指定实例
	virtual class CTiInstance *FindInstByAlias(const char *pAlias, u8 len) = 0;
	/// 得到应用最大实例数
	virtual int GetInstanceNumber(void) = 0;
	/// 得到实例别名最大长度
	virtual u8 GetMaxAliasLen(void) = 0;
	/// 初始化实例别名记录信息
	virtual BOOL32  InitAliasArray(void) = 0;
	/// 清除实例别名纪录信息
	virtual BOOL32  ClearInstAlias(u16 insid, const char *pAlias, u8 len) = 0;

    /// @brief          CreateApp
	/// @note           启动应用
	/// APP最高优先级为80，如果小于80，OSP将强制为80。此后, 用户可以调用PfcSetAppPriority或CApp::SetPriority更改优先级.
	/// @return         成功返回PFC_OK，失败返回PFC_ERROR
	/// @pre            5.0合并： 修改char* 为const char*
	int CreateApp( const char *name, u16 aid, u8 pri, u16 queuesize = 80, u32 uStackSize = 200 << 10 );
	/** \pre 5.0合并： 原行业osp特有接口，设置裸消息回调函数 **/
	void SetAppCallBack(CB_FUNC_PFC_RCV_RAW_MSG cbMsg , MemId dwContext);
	/// 设定应用任务优先级
	BOOL32 SetPriority(u8 byPrior);
	/// 查询任务优先级
	u8 GetPriority(void)
	{
		return byAppPri;
	}
    void QuitApp(void);	                                ///< 应用退出

    BOOL32 BakMsgNumInc(void);	                        ///< 应用备邮箱消息总数增加查询
    BOOL32 BakMsgNumDec(void);	                        ///< 应用备邮箱消息总数减少查询
	u32 GetBakMsgNum(void);                             ///< 应用备邮箱消息总数

    u32 GetMsgIncomeNum(void);	                        ///< 应用主邮箱消息总数
    void MsgIncomeNumInc(void);	                        ///< 应用主邮箱消息总数查询增加
    void MsgIncomeNumDec(void);	                        ///< 应用主邮箱消息总数查询减少

    void MsgProcessedNumInc(void);	                    ///< 应用处理消息总数增加
    u32 GetMsgWaitingNum(void);	                        ///< 查询待处理的消息总数
    void SetName(const char *pName);	                ///< 应用别名设定
    char *NameGet(void);	                            ///< 应用别名查询

    void TimerProcessedIncrease(void);	                ///< 定时激发次数增加
    void LogLevelSet(u8 file_level, u8 screen_level);	///< 设定文件屏幕log级别
    void TrcFlagSet(u16 file_flag, u16 screen_flag);	///< 设定文件屏幕trc标志
    void InstInfoShow(void);	                        ///< 实例简要信息打印
    void InstInfoAdd(u16 ins, u32 state, u16 evtrcv, u16 evtsnd);	///< 实例简要信息增加
    void DropFlagSet(BOOL32 bDropFlag);	                ///< 设置是否丢弃消息标志

#if defined(_LINUX_) && defined(PWLIB_SUPPORT)
	void Main(void);        ///< pwlib pure virtual function
#endif
};

/// 实例定时器信息
typedef  struct TiTInstTimerInfo
{
	TiTInstTimerInfo *next ;        ///< next instance
	u32 timerId ;                   ///< timer id
	void *timerBlkAdrr ;            ///< timer block address
} TiTInstTimerInfo;

/// @pre 5.0合并： 原行业定时器的底层结构，使得业务可以直接访问底层定时器状态
/// Timer block definition
struct TiTmBlk
{
	/// 定时控制块
	TiTmBlk *suc;		            ///< 下一个时间控制块。
	TiTmBlk *pre;		            ///< 上一个时间控制块。
	u64 tick;                       ///< Tick counter
	u16 appId;                      ///< Timer app id
	u16 instId;                     ///< Timer instance id
	u16 timerId;                    ///< Timer id
	u32 param;                      ///< param, user context? should it be a MemId typed variant?
	u32 settedTick;                 ///< Setted tick counter
	u16 timeToLeft;                 ///< Time left to be triggered
	time_t absTime;                 ///< 绝对定时到时时间
	BOOL32 bExtendMode;             ///< 是否使用扩展模式。默认不使用
	u8  *pExtContent;               ///< 扩展内容
	u16  dwExtLength;               ///< 扩展内容的长度
};

#define  PFCTIMERHANDLE  TiTmBlk*   ///< Timer block redifinition

/// CInstance抽象基类规范。
/// 基于Osp的应用必须从该CInstance基类派生一个具体的Instance类，
/// 并给出一个InstanceEntry()成员函数的具体实现
class PFC_API CTiInstance
{
public:
    /// Instance states
	enum
    {
        PENDING,		        ///< 空闲实例
        EACH = 0xffff,		    ///< 广播
        EACH_ACK = 0xfffe,		///< 广播且要求确认应答
        CONN_ACK = 0xfffd,		///< 未使用
        DAEMON = 0xfffc,		///< 守护实例
        INVALID = 0xfffb		///< 目的实例实例号无效，别名有效
	};

public:
    u16 m_appId;	            ///< 应用号
    u16 m_instId;	            ///< 实例号
    char m_alias[MAX_ALIAS_LEN];///< 实例别名
    u8 m_aliasLen;	            ///< 实例别名长度
    u8 m_maxAliasLen;	        ///< 实例别名最大长度
    u32 m_curState;	            ///< 当前状态机
    u32 m_lastState;	        ///< 上一个状态机

public:
	/// 守护实例入口函数
	virtual void DaemonInstanceEntry( CTiMessage *const, CTiApp *)
	{
		log( 0, (char *)"PFC: message received in default daemon instance of app %d.\nCheck your daemon implementation, please!\n", GetAppID() );
	}
	/// 实例入口函数
	virtual void InstanceEntry( CTiMessage *const pMsg) = 0;
	/// 实例打印函数
	virtual void InstanceDump(MemId lpParam = NULL)
	{
	}
	/// 守护实例打印函数
	virtual void DaemonInstanceDump(MemId lpParam = NULL)
	{
	}
	/// 实例退出
	virtual void InstanceExit(void)
	{
	}

	/// 设定实例别名
	int SetAlias(const char *pchAlias, u8 len);
	/// 删除实例别名
	void DeleteAlias(void);
	/// 查询实例别名
	BOOL32 GetAlias(char *aliasBuf, u8 bufLen, u8 *aliasLen);
	/// 查询实例别名长度
	u8 GetAliasLen(void);

	/// 查询上一个实例状态机
	u32         LastState();
	/// 查询当前实例状态机
	u32         CurState();

	/// 查询应用号
	u16         GetAppID();
	/// 查询实例号
	u16         GetInsID();

	/// 定时器信号量
	PFCSEMHANDLE      m_tSemTimerList;
	/// 定时器信息链表
	TiTInstTimerInfo  m_timerInfoListHead;

	/// 加入定时器信息
	void AddInstTimerInfo(u32 nTimerNo , void *pTimerAddr);
	/// 删除定时器信息
	void DelInstTimerInfo(u32 nTimerNo);
	/// 查询定时器信息
	void *FindInstTimerInfo(u32 nTimerNo);
	/// 删除所有定时器信息
	void DelAllInstTimerInfo();
	/* 5.0合并： 以下两个接口是行业特有接口， 提供定时器的底层操作 */
	/// 设置相对定时
	int SetTimer(PFCTIMERHANDLE *pTimerHandle, u32 dwTimer, long uMilliSeconds, const void *content, u16 length );
	/// 取消定时
	int KillTimer(PFCTIMERHANDLE hTimerHandle);
protected:
	/// 设置相对定时
	int SetTimer( u32 nTimer, long nMilliSeconds, u32 nPara = 0 );
	/// 设置绝对定时
	int SetAbsTimer( u32 nTimer, u16 nYear, u8 nMon, u8 nDay, u8 nHour, u8 nMin, u8 nSec, u32 nPara = 0 );
	/// 取消定时
	int KillTimer(u32 nTimerNo);
	/// 取消绝对定时器
	int KillAbsTimer( u32 nTimerNo);
	/// 实例打印,可调用PfcSetLogLevel修改打印级别
	void log(u8 level, const char *format, ...);
	/// 切换状态机
	void NextState(u32 state, char *s = 0 );

	/// 发送异步消息。目的实例采用实例号标识
	int post(u32 dstiid, u16 event, const void *content = 0, u16 length = 0, u32 dstnode = 0);
	/// 发送异步消息(目的实例采用实例别名标识)
	int post(const char *dstalias, u8 aliaslen, u16 dstapp, u16 event,
			 const void *content = 0, u16 length = 0, u32 dstnode = 0);

	/// 发送同步消息。目的实例采用实例号标识
	int send(u32 dstiid, u16 event, const void *content = 0, u16 length = 0, u32 dstnode = 0,
			 void *ackbuf = NULL, u16 ackbuflen = 0, u16 *realacklen = NULL,
			 u16 timeout = 1000);
	/// 发送同步消息。目的实例采用实例别名标识
	int send(const char *dstalias, u8 aliaslen, u16 dstapp, u16 event,
			 const void *content = 0, u16 length = 0, u32 dstnode = 0,
			 void *ackbuf = NULL, u16 ackbuflen = 0, u16 *realacklen = NULL,
			 u16 timeout = 1000);

	/// 发送同步消息应答
	int SetSyncAck(const void *ack = NULL, u16 ackLen = 0);
	/// 发送同步消息应答。建议使用SetSyncAck
	int reply(const void *ack = NULL, u16 ackLen = 0);
};

/// 用于派生用户App类的模板
class CTiAppNoData
{
};

/// 实例别名快速查找记录数据
typedef struct TTiInstAliasInfo
{
    u32  aliasRet;	            ///< 实例别名的设置值。也是存放的位置下标
    u32  nextLoc;	            ///< 相同设置值的下一个实例存放位置
    u16  instId;	            ///< 实例号
} TTiInstAliasInfo;

/// 应用模板。模板参数为实例的继承类以及最大实例实例数
template <class I, int maxins = 1, class A = CTiAppNoData, u8 maxAliasLen = 0>
class zTiTemplate: public CTiApp, public A
{
public:
	/// 设置实例别名
	BOOL32 SetInstAlias(u16 insid, const char *pchAlias, u8 len);
	/// 清除实例别名纪录信息
	BOOL32  ClearInstAlias(u16 insid, const char *pAlias, u8 len);

private:
	/// 由局部实例号查找实例
	CTiInstance *GetInstance(u16 insid);
	/// 由别名查找实例
	CTiInstance *FindInstByAlias(const char *pchAlias, u8 len);
	/// 获得普通实例个数
	int GetInstanceNumber(void);
	/// 获得最大别名长度
	u8 GetMaxAliasLen(void);

private:
	/// daemon实例
	I daemIns;
	/// 普通实例表
	I insarray[maxins];

	/// 实例别名快速查找
	/// 实例别名记录信息链头表
	TTiInstAliasInfo instAliasArray[maxins];
	/// 实例别名记录信息备用表，记录设置相同的实例
	TTiInstAliasInfo bakInstAliasArray[maxins];
	/// 当前备用表中记录的实例个数
	u32 curBakArrayNum;

	/// 初始化实例别名记录信息
	BOOL32 InitAliasArray();
	/// 实例别名转换成WORD32型整数
	u32 AliasToWord(char *pchAlias, u8 len);
	/// 确定实例别名信息存放在主用表还是在备用表中
	BOOL32 IsInBakArray(u32 setRet);
};

/**
* @brief        PfcLog
* @note         全局log函数。这个函数的开关是应用号0。调用PfcSetLogLevel(0,xx)就可以控制该函数的打开或关闭
* @param[in]    level   : log level
* @param[in]    format  : message format
* @return       void
*/
API void PfcLog(u8 level, const char *format, ...);

/**
* @brief        PfcMsgDumpSet
* @note         set long msg dump detail can/not be whole print, default is printf 10 lines
* @param[in]    LgMsgDumpEnbl : [in] enable or not
* @return       void
*/
API void PfcMsgDumpSet(BOOL32 LgMsgDumpEnbl);

/**
* @brief        PfcStatusMsgOutSet
* @note         set status message can or not be out put every timer
* @param[in]    OutMsgEnable : [in] enable or not
* @return       void
*/
API void PfcStatusMsgOutSet(BOOL32 OutMsgEnable);

/**
* @brief        PfcPrintf
* @note         把相应的内容显示到屏幕,存储到文件,不能屏蔽
* @param[in]    bScreen     : 是否输出到屏幕,
* @param[in]    bFile       : 是否输出到文件,
* @param[in]    szFormat    : 格式
*/
API void PfcPrintf(BOOL32 bScreen, BOOL32 bFile, const char *szFormat, ...);

/**
* @brief        PfcTelAuthor
* @note         设置Telnet的授权用户名和密码。vxworks下用户名和密码为空会设置失败。
* @param[in]    szUsername  : authorization user name
* @param[in]    szPassword  : password for the authorization user
*/
API void PfcTelAuthor(const char *szUsername = NULL , const char *szPassword = NULL );

/**
* @brief        pfcver
* @note         output compile version info to screen
*/
API void pfcver();

/**
* @brief        PfcCat
* @note         output file content to screen
* @param[in]    fname : [in] file to be opened
*/
API void PfcCat(const char  *fname);

#ifdef _LINUX_
/// callback function pointer when PFC quit is triggered
typedef void (*PPfcQuitFunc)(int);
/**
* @brief        PfcRegQuitFunc
* @note         注册任务退出函数，仅linux下有效
* @param[in]    pQuitFunc  : 任务退出函数
* @return       TRUE - 注册成功
  ====================================================================*/
API BOOL32 PfcRegQuitFunc( PPfcQuitFunc pQuitFunc );

/**
* @brief        PfcRegTaskInfo
* @note         注册任务信息，仅linux下有效
* @param[in]    dwTaskId :任务号
* @param[in]    szName : 任务别名
*/
API void PfcRegTaskInfo(u64 dwTaskId, const char *szName);

/**
* @brief        PfcUnRegTaskInfo
* @note         反注册任务信息
* @param[in]    dwTaskId  : 任务号
*/
API BOOL32 PfcUnRegTaskInfo(u64 dwTaskId);

/**
* @brief        PfcTaskShow
* @note         打印任务信息，仅linux下有效
*/
API void PfcTaskShow();

/**
* @brief        PfcRegCommand
* @note         注册可以在Telnet下执行的函数。该函数仅在linux下有效，windows下不需注册。
* @param[in]    szName : Telnet下输入的命令
* @param[in]    pfFunc : 对应的函数指针
* @param[in]    szUsage: 命令的帮助信息
*/
API void PfcRegCommand(const char *szName, void *pfFunc, const char *szUsage);
#endif

/**
* @brief        PfcNodeConnTest
* @note         test a node's network connection
* @param[in]    dwNodeId : [in] id of the node
*/
API void PfcNodeConnTest(u32 dwNodeId);

/**
* @brief        PfcNodeIpGet
* @note         获得指定结点的Ip地址
* @param[in]    dwNodeId : [in] node id
* @return       成功返回结点IP, 失败返回0.
*/
API u32 PfcNodeIpGet(u32 dwNodeId);

/**
* @brief        PfcNodeLocalIpGet
* @note         获取节点的本地地址
* @pre          对于已经连接的tcp节点，在本地存在多个地址的情况下，需要知道对方实际连接的本地ip地址。
* @param[in]    dwNodeId : [in] node id
* @return       成功返回结点IP, 失败返回0.
*/
API u32 PfcNodeLocalIpGet(u32 dwNodeId);

/**
* @brief        PfcInstShow
* @note         显示某个App中的Instance的状态信息
* @param[in]    aid : app id of the instance list
*/
API void PfcInstShow(u16 aid);

/**
* @brief        PfcInstShowAll
* @note         显示所有Instance的状态信息
*/
API void PfcInstShowAll(void);

/**
* @brief        PfcInstDump
* @note         显示某一instance的自定义信息，调用该instance的dump函数。
* @param[in]    aid : [in] app id
* @param[in]    InstId : [in] instance id, 0:显示所有的，-1:显示非IDLE的
* @param[in]    param : [in] reserved parameter
*/
API void PfcInstDump(u16 aid, u16 InstId, MemId param);

/**
* @brief        PfcNodeShow
* @note         显示所有Node的状态信息
*/
API void PfcNodeShow(void);

/**
* @brief        PfcAppShow
* @note         显示App的状态信息
*/
API void PfcAppShow();

/**
* @brief        PfcDispatchShow
* @note         显示Dispatch task的信息
*/
API void PfcDispatchShow();

/**
* @brief        PfcTimerShow
* @note         显示timer状态信息
*/
API void PfcTimerShow(void);

/**
* @brief        PfcLogShow
* @note         显示日志模块状态
*/
API void PfcLogShow(void);

/**
* @brief        PfcMemShow
* @note         显示内存管理堆栈中消息块数目
*/
API void PfcMemShow(void);

/**
* @brief        PfcAppEchoTest
* @note         Application echo testing
* @param[in]    AppId : [in] Application id
*/
API void PfcAppEchoTest(u16 AppId);

/**
* @brief        PfcAddEventDesc
* @note         用于将事件的描述登记到消息跟踪系统
* @param[in]    desc : [in]
* @param[in]    event : [in]
*/
API void PfcAddEventDesc (const char   *desc, u16 event);

/**
* @brief        PfcSendTrcOn
* @note         打开OSP结点发送跟踪标识
*/
API void PfcSendTrcOn();

/**
* @brief        PfcSendTrcOff
* @note         关闭OSP结点发送跟踪标识
*/
API void PfcSendTrcOff();

/**
* @brief        PfcRcvTrcOn
* @note         打开OSP结点接收跟踪标识
*/
API void PfcRcvTrcOn();

/**
* @brief        PfcRcvTrcOff
* @note         关闭OSP结点接收跟踪标识
*/
API void PfcRcvTrcOff();

/**
* @brief        PfcTrcAllOn
* @note         打开OSP所有应用的跟踪标设
*/
API void PfcTrcAllOn(void);

/**
* @brief        PfcTrcAllOn
* @note         打开OSP所有应用的跟踪标设
*/
API void PfcTrcAllOff(void);

/**
* @brief        PfcOpenLogFile
* @note         打开日志文件
* @param[in]    name : file name
* @param[in]    maxsize_KB : 文件大小限制
* @param[in]    maxfiles : [in]文件数目限制
* @return       BOOL32 - true 成功, false 失败
*/
API BOOL32 PfcOpenLogFile(const char   *path, const char   *name, u32 maxsize_KB, u32 maxfiles);

/**
* @brief        PfcCloseLogFile
* @note         关闭日志文件。
* @pre          如果调用PfcQuit，则不需要调用该函数。
*/
API void PfcCloseLogFile(void);

/**
* @brief        PfcSetLogLevel
* @note         控制一个APP的CInstance::log函数的级别
* @pre          必须在PfcInit之后调用该函数才能生效。PfcInit将所有应用的该标志置0
* @param[in]    aid : [in] app id
* @param[in]    file_level : [in] file level
* @param[in]    screen_level : [in] screen level. if level=5, 那么0~5 打印,  6~255 不打印,设置为3,则只有log(0|1|2,"")的调用能够输出。
*/
API void PfcSetLogLevel(u16 aid, u8 file_level, u8 screen_level);

/**
* @brief        PfcSetFileLogLevel
* @note         设置App的文件日志等级
* @param[in]    wAid: App的等级
* @param[in]    byFileLevel: 文件Log的等级
*/
API void PfcSetFileLogLevel(u16 wAid, u8 byFileLevel);

/**
* @brief        PfcSetScrnLogLevel
* @note         设置App的屏幕日志等级
* @param[in]    wAid: App的等级
* @param[in]    byScrnLevel: 屏幕Log的等级
*/
API void PfcSetScrnLogLevel(u16 wAid, u8 byScrnLevel);

/**
* @brief        PfcSetTrcFlag
* @note         设置每个应用的跟踪范围。Trace 分为 Trace 状态机 1: 发消息, 2: 收消息, 4: 设定时 8:收定时 16:状态跃迁
* @param[in]    wAid : [in] app id
* @param[in]    wFileFlag : [in] trace file flag
* @param[in]    wScrnFlag : [in] screen output flag
*/
API void PfcSetTrcFlag(u16 wAid, u16 wFileFlag, u16 wScrnFlag);

/**
* @brief        PfcSetFileTrcFlag
* @note         设置某个应用的跟踪标志
* @param[in]    wAid: appl 标设
* @param[in]    wFileFlag: 文件跟踪标设
*/
API void PfcSetFileTrcFlag(u16 wAid, u16 wFileFlag);

/**
* @brief        PfcSetScrnTrcFlag
* @note         设置某个应用的跟踪标志
* @param[in]    wAid: application 标设
* @param[in]    wScreenFlag: 屏幕跟踪标设
*/
API void PfcSetScrnTrcFlag(u16 wAid, u16 wScreenFlag);

/**
* @brief        PfcRegistModule
* @note         向OSP登记一个模块
* @param[in]    szModuleName - 模块（.exe文件）名，以NULL结尾的字符串，如"kdvmt.dll"等
* @return       成功返回TRUE，失败返回FALSE
*/
API BOOL32 PfcRegistModule(const char *szModuleName);

/**
* @brief        PfcSetLogEventDataLength
* @note         设置全局的消息跟踪显示的长度。
* @param[in]    wLength : [in] length of log event data
* @return       u16 previous length
*/
API u16 PfcSetLogEventDataLength(u16 wLength);

/**
* @brief        PfcEnableBroadcastAck
* @note         大多数情况下，用户发送广播消息并不需要对方返回确认消息。缺省情况下，PIS不向消息的发送者发送OSP_BROADCASTACK消息，但是可以通过该函数修改这个选项。是否发送OSP_BROADCASTACK是由接受节点决定的。
* @param[in]    aid : [in] 表示广播消息的接受者AID。
* @param[in]    bEnable : [in] enable or not
* @return       BOOL32 - true Succeeded, false Failed
*/
API BOOL32 PfcEnableBroadcastAck(u16 aid, BOOL32 bEnable);

/// PFC Node Address for IPv4
typedef struct
{
    u32 m_dwLocalIP;    ///< 网络序
    u32 m_dwPeerIP;     ///< 网络序
    u16 m_wLocalPort;   ///< 主机序
    u16 m_wPeerPort;    ///< 主机序
} TPfcNodeAddr;

/**
* @brief        PfcGetNodeAddr
* @note         查找PFC结点地址（本端与远端IP+Port）。
* @param[in]    dwNodeId : [in] 结点ID
* @param[out]   ptPfcNodeAddr : [out] 结点地址
* @return       FALSE - 查询成功 TRUE - 查询失败
*/
API BOOL32 PfcGetNodeAddr( u32 dwNodeId , TPfcNodeAddr *ptPfcNodeAddr );

#ifdef _ENABLE_SOCK5_API_
#include "pfc_sock5.h"
#endif

/** 5.0合并： 原行业osp特有接口， 创建一个raw消息osp server */
/**
* @brief        PfcCreateTcpNode
* @note         创建一个TCP节点。这以后，这个节点可以被连接。请使用6682作为port参数。
* @param[in]    dwAddr : [in] reserved
* @param[in]    wPort : [in] which port to use
* @param[in]    bTcpNodeReuse: [in] 创建的node退出后端口是否能立即重用或被其他程序马上占用
* @param[in]    cb_setappid: callback function pointer for the created TCP node
* @return       int - If no error occurs, CreateTcpNode returns a descriptor referencing the new socket. Otherwise, a value of INVALID_SOCKET is returned.
*/
API int PfcCreateTcpNode(u32 dwAddr, u16 wPort, BOOL32 bTcpNodeReuse = FALSE , CB_FUNC_PFC_CREATE_RAW_NODE cb_setappid = NULL);

/**
* @brief        PfcConnectTcpNode
* @note         在地址uIpv4Addr和端口uTcpPort上连接服务结点, 并设置断链检测参数.全局变量：g_cPfc
* @param[in]    dwIpv4Addr : [in] 服务结点的IP地址,
* @param[in]    wTcpPort : [in] 服务结点的侦听端口号,
* @param[in]    wHb: [in] 断链检测周期(秒),
* @param[in]    byHbNum: [in] byHbNum次未到连接检测应答后认为链路已断开,
* @param[in]    dwTimeoutMs: [in] 如果在dwTimeOutMs毫秒内连接不成功, 返回出错. 缺省值0,表示取connect超时的缺省时间(75s).  该参数目前仅在VxWorks下有效.
* @param[out]   pdwLocalIP: [out] 当前连接所用的IP地址
* @param[in]    wAid: specify the app id
* @return       成功返回一个动态分配的结点号, 此后用户可借此与服务结点通信. 失败返回INVALID_NODE.
*/
API int PfcConnectTcpNode(u32 dwIpv4Addr, u16 wTcpPort, u16 wHb = 10, u8 byHbNum = 3, u32 dwTimeoutMs = 0, u32 *pdwLocalIP = NULL , u16 wAid = 0);

/** 5.0合并： 原企业osp特有接口 */
/**
* @brief        PfcConnectTcpNodeEx
* @note         在地址uIpv4Addr和端口uTcpPort上连接服务结点, 并设置断链检测参数.本地端口绑定范围（wMinPort~wMaxPort）.全局变量：g_cPfc
* @param[in]    dwIpv4Addr  : [in] 服务结点的IP地址,
* @param[in]    wTcpPort    : [in] 服务结点的侦听端口号,
* @param[in]    wHb         : [in] 断链检测周期(秒),
* @param[in]    byHbNum     : [in] uHbNum次未后到连接检测应答后认为链路已断开.
* @param[in]    dwTimeOutMs : [in] 如果在dwTimeOutMs毫秒内连接不成功, 返回出错. 缺省值0.
* @param[in]    pdwLocalIP  : [out] 当前连接所用的IP地址
* @param[in]    wMinPort    : [in] 指定本地绑定端口范围的最小值
* @param[in]    wMaxPort    : [in] 指定本地绑定端口范围的最大值
* @param[in]    wAid        : specify the app id
* @pre          如果绑定端口最小值和最大值都为0，表示随机选择端口，不绑定
* @return       成功返回一个动态分配的结点号, 此后用户可借此与服务结点通信.失败返回INVALID_NODE.
*/
API int PfcConnectTcpNodeEx(u32 dwIpv4Addr, u16 wTcpPort, u16 wHb, u8 byHbNum, u32 dwTimeOutMs, u32 *pdwLocalIP, u16 wMinPort, u16 wMaxPort, u16 wAid = 0);

#ifdef PFC_ENABLE_IPV6
/// PFC Node Address for IPv6
typedef struct
{
    //in_addr6 m_tLocalIP;    ///< 网络序
    //in_addr6 m_tPeerIP;     ///< 网络序
	sockaddr_in6 m_tLocalIP;    ///< 网络序
	sockaddr_in6 m_tPeerIP;     ///< 网络序
    u16 m_wLocalPort;       ///< 主机序
    u16 m_wPeerPort;        ///< 主机序
} TPfcNodeAddr6;
/**
* @brief        PfcGetNodeAddr6
* @note         查找PFC结点地址（本端与远端IP+Port）。
* @param[in]    dwNodeId : [in] 结点ID
* @param[out]   ptPfcNodeAddr6 : [out] 结点地址
* @return       FALSE - 查询成功 TRUE - 查询失败
*/
API BOOL32 PfcGetNodeAddr6( u32 dwNodeId , TPfcNodeAddr6 *ptPfcNodeAddr6 );

/**
* @brief        PfcCreateTcpNode6
* @note         创建一个TCP节点。这以后，这个节点可以被连接。请使用6682作为port参数。
* @param[in]    ptAddr : [in] reserved
* @param[in]    wPort : [in] which port to use
* @param[in]    bTcpNodeReuse: [in] 创建的node退出后端口是否能立即重用或被其他程序马上占用
* @param[in]    cb_setappid: callback function pointer for the created the TCP node
* @return       int - If no error occurs, CreateTcpNode returns a descriptor referencing the new socket. Otherwise, a value of INVALID_SOCKET is returned.
*/
API int PfcCreateTcpNode6(PFC_IPADDR* ptAddr, u16 wPort, BOOL32 bTcpNodeReuse = FALSE , CB_FUNC_PFC_CREATE_RAW_NODE cb_setappid = NULL);

/**
* @brief        PfcConnectTcpNode6
* @note         在地址uIpv4Addr和端口uTcpPort上连接服务结点, 并设置断链检测参数.全局变量：g_cPfc
* @param[in]    ptIpv6Addr : [in] 服务结点的IP地址,
* @param[in]    wTcpPort : [in] 服务结点的侦听端口号,
* @param[in]    wHb: [in] 断链检测周期(秒),
* @param[in]    byHbNum: [in] byHbNum次未到连接检测应答后认为链路已断开,
* @param[in]    dwTimeoutMs: [in] 如果在dwTimeOutMs毫秒内连接不成功, 返回出错. 缺省值0,表示取connect超时的缺省时间(75s).  该参数目前仅在VxWorks下有效.
* @param[out]   ptLocalIP: [out] 当前连接所用的IP地址
* @param[in]    wAid: specify the app id
* @return       成功返回一个动态分配的结点号, 此后用户可借此与服务结点通信. 失败返回INVALID_NODE.
*/
API int PfcConnectTcpNode6(PFC_IPADDR* ptIpv6Addr, u16 wTcpPort, u16 wHb = 10, u8 byHbNum = 3, u32 dwTimeoutMs = 0, PFC_IPADDR *ptLocalIP = NULL , u16 wAid = 0);

/**
* @brief        PfcConnectTcpNodeEx6
* @note         在地址uIpv4Addr和端口uTcpPort上连接服务结点, 并设置断链检测参数.本地端口绑定范围（wMinPort~wMaxPort）.全局变量：g_cPfc
* @param[in]    ptIpv6Addr  : [in] 服务结点的IP地址,
* @param[in]    wTcpPort    : [in] 服务结点的侦听端口号,
* @param[in]    wHb         : [in] 断链检测周期(秒),
* @param[in]    byHbNum     : [in] uHbNum次未后到连接检测应答后认为链路已断开.
* @param[in]    dwTimeOutMs : [in] 如果在dwTimeOutMs毫秒内连接不成功, 返回出错. 缺省值0.
* @param[out]   ptLocalIP   : [out] 当前连接所用的IP地址
* @param[in]    wMinPort    : [in] 指定本地绑定端口范围的最小值
* @param[in]    wMaxPort    : [in] 指定本地绑定端口范围的最大值
* @param[in]    wAid: specify the app id
* @pre          如果绑定端口最小值和最大值都为0，表示随机选择端口，不绑定
* @return       成功返回一个动态分配的结点号, 此后用户可借此与服务结点通信.失败返回INVALID_NODE.
*/
API int PfcConnectTcpNodeEx6(PFC_IPADDR* ptIpv6Addr, u16 wTcpPort, u16 wHb, u8 byHbNum, u32 dwTimeOutMs, PFC_IPADDR *ptLocalIP, u16 wMinPort, u16 wMaxPort, u16 wAid = 0);

/**
* @brief        PfcAddrListGet6
* @note         获取本机地址表内容
* @pre          如果是在Windows下使用本函数，必须先调用PfcInit，或者WSAStartup。本函数效率较低，不要重复调用。
* @param[in]    atIPList[] : [in/out]用户申请的用于地址表内容的数组的首地址
* @param[in]    wNum : [in]用户申请的数组的大小
* @return       返回本机地址表中地址个数，错误时返回0
*/
API u16  PfcAddrListGet6(PFC_IPADDR atIPList[], u16 wNum);

/**
* @brief        PfcIsLocalHost6
* @pre          如果是在Windows下使用本函数，必须先调用PfcInit，或者WSAStartup
*               。本函数效率较低，不要重复调用。
* @note         判断是否是本机IP,目标支持IPv4和IPv6
* @param[in]    ptIP: Input IP address
* @return       是否为本机IP
*/
API BOOL32 PfcIsLocalHost6(PFC_IPADDR* ptIP);

#endif  /// end of PFC_ENABLE_IPV6

/**
* @brief        PfcSetHBParam
* @note         设置结点的断链检测参数
* @param[in]    dwNodeID: 结点号,
* @param[in]    wHb: 链路检测周期(以秒为单位),
* @param[in]    byHbNum: 如果连续ping了uHbNum次没有应答, 主动断开.
* @return       成功返回TRUE, 失败返回FALSE.
*/
API BOOL32 PfcSetHBParam(u32 dwNodeID, u16 wHb, u8 byHbNum);

/**
* @brief        PfcNodeDiscCBReg
* @note         设置在node连接中断时需通知的appid和InstId
* @pre          目前支持通知多个实例，每次调用该函数，则只通知指定实例，其他已注册待通知实例将被清除。
* @param[in]    dwNodeId : [in] node id
* @param[in]    wAppId : [in] application id
* @param[in]    wInsId : [in] instance id
* @return       成功返回PFC_OK，失败参见错误码
*/
API int PfcNodeDiscCBReg(u32 dwNodeId, u16 wAppId, u16 wInsId);

/**
* @brief        PfcNodeDiscCBRegQ
* @pre          增加在node连接中断时需通知的appid和InstId
* @note         每次调用此函数，则增加一个要通知的实例。除非达到最大个数
* @param[in]    dwNodeId : [in] node id
* @param[in]    wAppId : [in] application id
* @param[in]    wInsId : [in] instance id
* @return       成功返回PFC_OK，失败参见错误码
*/
API int PfcNodeDiscCBRegQ(u32 dwNodeId, u16 wAppId, u16 wInsId);

/**
* \brief        PfcNodeDelDiscCB
* \pre          删除在node连接中断时需通知的appid和InstId
* \note         每次调用此函数，则删除一个要通知的实例。
* \param[in]    dwNodeId : [in] node id
* \param[in]    wAppId : [in] application id
* \param[in]    wInsId : [in] instance id
* \return       成功返回PFC_OK，失败参见错误码
*/
API int PfcNodeDelDiscCB(u32 dwNodeId, u16 wAppId, u16 wInsId);

/**
* \brief        PfcDisconnectTcpNode
* \pre          断开在一个node上的连接。
* \note
* \param[in]    dwNodeId : [in] node id
* \return       BOOL32 - true Succeeded, false Failed
*/
API BOOL32 PfcDisconnectTcpNode(u32 dwNodeId);

/**
* \brief        PfcCloseTcpNode
* \pre          关闭一个套接字的监听，对应于PfcCreateTcpNode创建监听(目前仅linux下有效)。
*               5.0合并： 原行业osp的接口， 支持一个进程创建多个osp server 
* \note
* \param[in]    nSocketFd : [in] 套接字描述符，一般为PfcCreateTcpNode的返回值
* \return       BOOL32 - true Succeeded, false Failed
*/
API BOOL32 PfcCloseTcpNode(int nSocketFd);

#ifdef _LINUX_
/**
* @brief        PfcDisconnectAllTcpNode
* @note         停止当前的监听,并断开其上创建全部连接(目前仅linux下有效)。
*/
API BOOL32 PfcDisconnectAllTcpNode(void);
#endif

/**
* @brief        PfcIsValidTcpNode
* @note         判断一个TCP节点是否有效。
* @param[in]    node_id: [in] node id
* @return       BOOL32 - Valid or not
*/
API BOOL32 PfcIsValidTcpNode (u32 node_id);

/**
* @brief        PfcIsNodeCheckEnable
* @note         判断指定结点的链路检测功能是否起用
* @param[in]    dwNodeId: node id
* @return       BOOL32 - Valid or not
*/
API BOOL32 PfcIsNodeCheckEnable(u32 dwNodeId);

/**
* @brief        PfcEnableNodeCheck
* @note         起用指定结点的链路检测功能
* @param[in]    dwNodeId: node id
* @return       void
*/
API void PfcEnableNodeCheck(u32 dwNodeId);

/**
* @brief        PfcDisableNodeCheck
* @note         禁用指定结点的链路检测功能
* @param[in]    dwNodeId: node id
* @return       void
*/
API void PfcDisableNodeCheck(u32 dwNodeId);

/**
* @brief        PfcSetAppPriority
* @note         设置App的调度优先级
* @param[in]    wAppId: AppID
* @param[in]    byPrior: priority value
* @return       成功, 返回TRUE; 失败, 返回FALSE.
*/
API BOOL32 PfcSetAppPriority(u16 wAppId, u8 byPrior);

/**
* @brief        PfcGetAppPriority
* @note         获得指定App的调度优先级。
* @param[in]    wAppId: AppID
* @param[out]   pbyPrior: priority value
* @return       成功, 返回TRUE; 失败, 返回FALSE.
*/
API BOOL32 PfcGetAppPriority(u16 wAppId, u8 *pbyPrior);

/**
* @brief        PfcIsLocalHost
* @pre          如果是在Windows下使用本函数，必须先调用PfcInit，或者WSAStartup
*               。本函数效率较低，不要重复调用。
* @note         判断是否是本机IP，如PfcIsLocalHost( inet_addr( "127.0.0.1" ) );
* @param[in]    dwIP: Input IP address
* @return       是否为本机IP
*/
API BOOL32 PfcIsLocalHost( u32 dwIP );

/**
* @brief        PfcPost
* @pre          发送异步消息
* @param[in]    dstid : [in] destination info
* @param[in]    event : [in] OSP_ event
* @param[in]    content : [in] message data
* @param[in]    length : [in] sizeof content in u8s
* @param[in]    dstnode : [in] destionation socket node
* @param[in]    srciid : [in] source info
* @param[in]    srcnode : [in] source node
* @param[in]    timeout : [in] message send timeout
* @return       0 Succeeded, others Failed
*/
API int PfcPost(u32 dstid, u16 event, const void *content = 0, u16 length = 0,
				u32 dstnode = 0, u32 srciid = PFC_MAKEIID(INVALID_APP, INVALID_INS), u32 srcnode = INVALID_NODE, int timeout = 2000);

/* used only in C++ environment */
/// 曾昭鸣修改, 添加参数timeout, 默认值2秒
/**
* @brief        PfcPost
* @pre          发送异步消息
* @param[in]    dstalias : [in] destination info
* @param[in]    aliaslen: dst alias string length
* @param[in]    dstapp: dst app id
* @param[in]    event : [in] OSP_ event
* @param[in]    content : [in] message data
* @param[in]    length : [in] sizeof content in u8s
* @param[in]    dstnode : [in] destionation socket node
* @param[in]    srciid : [in] source info
* @param[in]    srcnode : [in] source node
* @param[in]    timout : [in] message send timeout
* @return       0 Succeeded, others Failed
*/
int PfcPost(const char *dstalias, u8 aliaslen, u16 dstapp, u16 event, const void *content = 0, u16 length = 0, u32 dstnode = 0, u32 srciid = PFC_MAKEIID(INVALID_APP, INVALID_INS), u32 srcnode = INVALID_NODE, int timout = 2000);

/**
* @brief        PfcSend
* @pre          全局同步消息发送
* @param[in]    dstiid : [in] destination info
* @param[in]    event : [in] OSP_ event
* @param[in]    content : [in] message data
* @param[in]    length : [in] sizeof content in u8s
* @param[in]    dstnode : [in] destionation socket node
* @param[in]    srciid : [in] source info
* @param[in]    srcnode : [in] source node
* @param[in]    ackbuf : ack buffer
* @param[in]    ackbuflen: ack buffer length
* @param[in]    realacklen: real ack len
* @param[in]    timeout: send time out parameter for the sending message
* @return       0 Succeeded, others Failed
*/
API int PfcSend(u32 dstiid, u16 event, const void *content = 0, u16 length = 0, u32 dstnode = 0,
				u32 srciid = PFC_MAKEIID(INVALID_APP, INVALID_INS), u32 srcnode = INVALID_NODE,
				void *ackbuf = NULL, u16 ackbuflen = 0, u16 *realacklen = NULL,
				u16 timeout = 1000);

/**
* @brief        PfcSend
* @pre          全局同步消息发送
* @param[in]    dstalias : [in] destination info
* @param[in]    aliaslen: dst alias length
* @param[in]    dstapp: dst app id
* @param[in]    event : [in] OSP_ event
* @param[in]    content : [in] message data
* @param[in]    length : [in] sizeof content in u8s
* @param[in]    dstnode : [in] destionation socket node
* @param[in]    srciid : [in] source info
* @param[in]    srcnode : [in] source node
* @param[in]    ackbuf: ack buffer
* @param[in]    ackbuflen: ack buffer length
* @param[in]    realacklen: real ack length
* @param[in]    timeout: send msg timeout
* @return       0 Succeeded, others Failed
*/
/* used only in C++ environment */
int PfcSend(const char *dstalias, u8 aliaslen, u16 dstapp, u16 event,
			const void *content = 0, u16 length = 0, u32 dstnode = 0,
			u32 srciid = PFC_MAKEIID(INVALID_APP, INVALID_INS), u32 srcnode = INVALID_NODE,
			void *ackbuf = NULL, u16 ackbuflen = 0, u16 *realacklen = NULL,
			u16 timeout = 1000);


//////////////////////////////////////////////////////////////////////////
//  Start of pfc_telnet_service wrapper
//////////////////////////////////////////////////////////////////////////
/**
 * @defgroup    pfc_telnet_service  PFC telnet service
 * @brief       PFC telnet service implementations.
 * @{
 */

/**
* @brief        IsPFCInitd
* @note         判断PFC是否已初始化过了
* @return       PFC已初始化，返回TRUE；否则返回FALSE
*/
API BOOL32 IsPFCInitd(void);


#define MAX_MODULE_NAME_LENGTH 63   ///< Max module name string length definition

/**
* @brief        PfcInit
* @note         initialize PFC module
* @param[in]    TelNetEnable : [in] start telnet.exe
* @param[in]    TelNetPort : [in] PFC telnet server port
* @param[in]    pchModuleName : [in] process module name，maxlength = 63
* @param[in]    dwMaxNodeNum: max socket nodes
* @param[in]    dwMaxDispatchMsg: maximun dispatch messages
* @return       return TRUE if success, otherwise return FALSE
*/
API BOOL32 PfcInit(BOOL32 TelNetEnable = FALSE, u16 TelNetPort = 0, const char *pchModuleName = NULL, u32 dwMaxNodeNum = 512, u32 dwMaxDispatchMsg = 1024 );

/**
* @brief        PfcQuit
* @pre          OSP退出之后，所有OSP服务将不能使用。
* @note         退出PFC，调用本地所有APP的所有实例的InstanceExit方法，退出实例，
*               断开所有OSP结点，挂起所有OSP任务包括APP，然后返回。
* @return       void
*/
API void PfcQuit(void);

/**
* \brief        PfcSetPrompt
* \pre          
* \note         设置终端提示符
* \param[in]    prompt: prompt title caption string
* \return       return TRUE if success, otherwise return FALSE
*/
API BOOL32 PfcSetPrompt(const char *prompt);

/**
* \brief        PfcStopScrnLog
* \pre          
* \note         暂停屏幕日志输出
* \return       void
*/
API void PfcStopScrnLog(void);

/**
* \brief        PfcResumeScrnLog
* \pre          
* \note         恢复屏幕日志输出
* \return       void
*/
API void PfcResumeScrnLog(void);

/**
* \brief        PfcGetLocalID
* \pre          
* \note         本地全局编号
* \return       本地全局编号
*/
API int PfcGetLocalID(); // 本地全局编号

/**
* \brief        PfcEventDesc
* \pre          
* \note         返回消息的描述
* \param[in]    wEventID : [in]消息的ID
* \return       消息的描述，如果消息ID无效或者该消息没有描述字符串，返回值将为NULL。
*/
API const char *PfcEventDesc( u16 wEventID );

/**
 * \brief        PfcEventDescShow
 * \pre          
 * \note         Show/print event description for the specified eventid
 * \param[in]    wEventID : [in]消息的ID
 * \return       void
 */
API void PfcEventDescShow( u16 wEventID );

/**
* @}
*/
//////////////////////////////////////////////////////////////////////////
//  Group end of pfc_telnet_service wrapper
//////////////////////////////////////////////////////////////////////////




























//////////////////////////////////////////////////////////////////////////
//  Start of pfc_semhandle wrapper
//////////////////////////////////////////////////////////////////////////

/**
 * @defgroup    pfc_semhandle PFC semi-handle wrapper
 * @brief       PFC Semi-handle interfaces wrapper.
 * @{
 */

/**
* \brief        PfcSemBCreate
* \pre          
* \note         创建一个二元信号量
* \param[out]   ptSemHandle 返回的信号量句柄
* \return       return TRUE if success, otherwise return FALSE
*/
API BOOL32 PfcSemBCreate(PFCSEMHANDLE *ptSemHandle);

/**
* \brief        PfcSemCCreate
* \pre          
* \note         创建计数信号量
* \param[out]   ptSemHandle 返回的信号量句柄
* \param[in]    initcount: 初始计数
* \param[in]    MaxSemCount: 最大计数
* \return       return TRUE if success, otherwise return FALSE
*/
API BOOL32 PfcSemCCreate(PFCSEMHANDLE *ptSemHandle, u32 initcount, u32 MaxSemCount);

/**
* \brief        PfcSemDelete
* \note         删除信号量
* \param[in]    tSemHandle 待删除信号量的句柄
* \return       return TRUE if success, otherwise return FALSE
*/
API  BOOL32 PfcSemDelete(PFCSEMHANDLE tSemHandle );

/**
* \brief        PfcSemTake
* \note         信号量p操作，如该信号量不可用，则阻塞调用实例所在任务(APP)
* \param[in]    tSemHandle 信号量的句柄
* \return       return TRUE if success, otherwise return FALSE
*/
API BOOL32  PfcSemTake(PFCSEMHANDLE tSemHandle );

/**
* \brief        PfcSemTakeByTime
* \note         带超时的信号量p操作，如信号量不可用，则时间消逝dwtime毫秒后，出错返回
* \param[in]    tSemHandle 信号量的句柄
* \param[in]    dwtime 超时间隔(以ms为单位)
* \return       return TRUE if success, otherwise return FALSE
*/
API BOOL32 PfcSemTakeByTime(PFCSEMHANDLE tSemHandle, u32 dwtime);

/**
* \brief        PfcSemGive
* \note         信号量v操作
* \param[in]    tSemHandle 信号量的句柄
* \return       return TRUE if success, otherwise return FALSE
*/
API BOOL32 PfcSemGive(PFCSEMHANDLE tSemHandle );

/**
* @}
*/
//////////////////////////////////////////////////////////////////////////
//  End of pfc_semhandle wrapper
//////////////////////////////////////////////////////////////////////////





/** 5.0合并： 原行业osp特有接口 */
/**
* @brief        PfcSetNodeAppId
* @note         为节点设置关联appid
* @param[in]    nNodeId: 待设置的节点号
* @param[in]    wAid: 设置的appid
* @return       返回值说明：成功返回TRUE，失败返回FALSE.
*/
API BOOL32 PfcSetNodeAppId(int nNodeId, u16 wAid);







/************************************************************************/
/*  Start of pfc_thread wrapper                                          */
/************************************************************************/

/**
 * @defgroup    pfc_thread  PFC thread wrapper
 * @brief       SemHandle interfaces describe here what it is all about.
 * @{
 */

/**
* @brief           PfcTaskCreate
* @note            创建并执行一个任务
* @param[in]       pvTaskEntry: thread function pointer
* @param[in]       szName: thread name
* @param[in]       byPriority: thread priority
* @param[in]       dwStacksize: thread init stack size
* @param[in]       dwParam: user context for the thread
* @param[in]       wFlag: thread flag
* @param[out]      puTaskID: task id
* @return          return NULL if failed, otherwise success
*/
#ifdef _LINUX_
API PFCTASKHANDLE PfcTaskCreate(LINUXFUNC pvTaskEntry, const char *szName, u8 byPriority, u32 dwStacksize, MemId dwParam, u16 wFlag, u32 *puTaskID = NULL);
#else
API PFCTASKHANDLE PfcTaskCreate(void *pvTaskEntry, const char *szName, u8 byPriority, u32 dwStacksize, MemId dwParam, u16 wFlag, u32 *puTaskID = NULL);
#endif

#ifdef _MSC_VER
/**
* @brief           PfcTaskSetAffinity
* @note            创建并执行一个任务
* @param[in]       hTaskHandle      : windows下的线程、进程的句柄；
* @param[in]       dwCpuId          : 需绑定的CPU。从0开始计数,逐次递加
* @param[in]       byTaskType       ：绑定的线程、进程、任务的类型，0--线程，1-进程，其他-任务，linux下默认0即可
* @param[in]       pdwPreviousBind  ：如果之前该进程、线程、任务被绑定到某CPU，则会返回该CPU号。仅Solaris下有效
* @return          return NULL if failed, otherwise success
*/
API BOOL32 PfcTaskSetAffinity( PFCTASKHANDLE hTaskHandle, u32 dwCpuId, u8 byTaskType = 0, u32 *pdwPreviousBind = NULL);
#else
/**
* @brief           PfcTaskSetAffinity
* @note            创建并执行一个任务
* @param[in]       hTaskId          : 绑定的线程、进程、任务的ID；
* @param[in]       dwCpuId          : 需绑定的CPU。从0开始计数,逐次递加
* @param[in]       byTaskType       ：绑定的线程、进程、任务的类型。0--线程，1-进程，其他-任务。linux下默认0即可
* @param[in]       pdwPreviousBind  ：如果之前该进程、线程、任务被绑定到某CPU，则会返回该CPU号。仅Solaris下有效
* @return          return NULL if failed, otherwise success
*/
API BOOL32 PfcTaskSetAffinity( u64 hTaskId, u32 dwCpuId, u8 byTaskType = 0, u32 *pdwPreviousBind = NULL);
#endif

/**
* @brief           PfcPostRaw
* @note            Post a raw data to the specified node
* @param[in]       nNodeId  : Node ID
* @param[in]       content  : Content need to be posted
* @param[in]       dwLen    ：Content length
* @return          return NULL if failed, otherwise success
*/
API int PfcPostRaw(int nNodeId , const void *content , u32 dwLen);

/**
* @brief        PfcTaskExit
* @note         退出调用任务，任务退出之前用户要注意释放本任务申请的内存、信号量等资源。
* @pre          封装Windows的ExitThread(0)和vxWorks的taskDelete(0)。
* @return       成功返回TRUE，失败返回FALSE
*/
API BOOL32 PfcTaskExit(void);

/**
* @brief        PfcTaskTerminate
* @note         强行终止指定任务。
* @pre          封装Windows的ExitThread()和vxWorks的taskDelete()。
* @param[in]    handle: 待杀任务的handle
* @return       返回值说明：成功返回TRUE, 失败返回FALSE
*/
API BOOL32 PfcTaskTerminate(PFCTASKHANDLE handle);

/**
* @brief        PfcTaskSuspend
* @note         挂起当前任务
* @param[in]    handle: task handle
*/
API BOOL32 PfcTaskSuspend(PFCTASKHANDLE handle = 0);

/**
* @brief        PfcTaskResume
* @note         挂起当前任务
* @param[in]    handle: task handle
*/
API BOOL32 PfcTaskResume(PFCTASKHANDLE handle);

/**
* @brief        PfcTaskSetPriority
* @note         改变任务的优先级。
* @param[in]    taskHandle: task handle
* @param[out]   newPriority: task priority
* @param[out]   newSchedPolicy: task scheduled policy
*/
API BOOL32 PfcTaskSetPriority(PFCTASKHANDLE taskHandle, u8 newPriority, int newSchedPolicy = 0);

/**
* @brief        PfcTaskGetPriority
* @note         获得任务的优先级。
* @param[in]    taskHandle: task handle
* @param[out]   puPri: task priority
* @param[out]   SchedPolicy: task scheduled policy
*/
API BOOL32 PfcTaskGetPriority(PFCTASKHANDLE taskHandle, u8 *puPri, int *SchedPolicy = NULL);

/**
* @brief        PfcSetTaskPriorityByName
* @note         通过任务名设置任务的优先级linux下有效
* @param[in]    name: task name
* @param[in]    priority: task priority
* @param[in]    newSchedPolicy: task scheduled policy
*/
API void PfcSetTaskPriorityByName(s8 *name , u8 priority, int newSchedPolicy = 0);

/// 曾昭鸣添加, Linux下使用的设置task nice优先级的接口.
/// 这个接口可以去除, 但涉及到云视讯的一些业务代码的修改, 暂时先保留. 待评估后再决定.
/**
* @brief        PfcSetTaskNiceByName
* @note         通过任务名设置任务的时间片大小，linux下有效
* @param[in]    name: task name
* @param[in]    nice: task nice value
*/
API void PfcSetTaskNiceByName(s8 *name , int nice);

/**
* @brief        PfcGetTaskPriorityByName
* @note         通过任务名获取任务的优先级
*/
API void PfcGetTaskPriorityByName(s8 *name , u8 *priority, int *newSchedPolicy = NULL);

/**
* @brief        PfcTaskSelfHandle
* @note         获得调用任务的句柄
*/
API PFCTASKHANDLE PfcTaskSelfHandle(void);

/**
* @brief        PfcTaskSelfHandle
* @note         获得调用任务的ID
*/
API u32 PfcTaskSelfID(void);

/**
* @brief        PfcTaskHandleVerify
* @note         判断指定任务是否存在
*/
API BOOL32 PfcTaskHandleVerify(PFCTASKHANDLE handle);

/**
* @brief        PfcTaskSafe
* @note         保护调用任务不被非法删除
*/
API void PfcTaskSafe(void);

/**
* @brief        PfcTaskUnsafe
* @note         释放调用任务的删除保护，使得调用任务可以被安全删除
*/
API void PfcTaskUnsafe(void);

/**
* @brief        PfcTaskDelay
* @note         任务延时
* @param[in]    dwMseconds: 延时间隔(ms)
*/
API void PfcTaskDelay(u32 dwMseconds);

/** redefinition PfcDelay */
#define PfcDelay                      PfcTaskDelay

/**
* @}
*/

/**
* @brief        PfcCreateMailbox
* @note         创建消息队列
* @param[in]    szName: mailbox name
* @param[in]    dwMsgNumber: max msg number for the creating mail box
* @param[in]    dwMsgLength: max msg length for the creating mail box
* @param[out]   puQueueIDRead: read handle for the created mail box
* @param[out]   puQueueIDWrite: write handle for the created mail box
*/
API BOOL32 PfcCreateMailbox(const char *szName, u32 dwMsgNumber, u32 dwMsgLength , kdvHandle *puQueueIDRead, kdvHandle *puQueueIDWrite);

/**
* @brief        PfcCloseMailbox
* @note         关闭邮箱
* @param[in]    dwQueueIDRead : 邮箱的读、写句柄
* @param[in]    dwQueueIDWrite: 邮箱的读、写句柄
*/
API void PfcCloseMailbox(kdvHandle dwQueueIDRead, kdvHandle dwQueueIDWrite);

/**
* @brief        PfcSndMsg
* @note         向信箱发消息
* @param[in]    tQueueID: 信箱ID,
* @param[in]    lpMsgBuf: 内容指针,
* @param[in]    len     : 长度,
* @param[in]    timeout : 超时值ms. Windows下该参数无效, 邮箱满将一直阻塞直到有空的buffer. VxWorks下, 缺省为2秒。OSP_NO_WAIT 邮箱满立即返回；OSP_WAIT_FOREVER 邮箱满阻塞直到有空的buffer.
* @return       成功返回TRUE, 失败或超时返回FALSE.
*/
API BOOL32 PfcSndMsg(kdvHandle tQueueID, const char *lpMsgBuf, u32 len, int timeout = 2000);

/**
* @brief        PfcRcvMsg
* @note         从信箱收消息
* @param[in]    tQueueID:    信箱ID
* @param[in]    dwTimeout:   超时ms
* @param[out]   lpMsgBuf:    返回消息内容指针
* @param[in]    len: max receive length
* @param[out]   pLenRcved: actual receive length
*/
API BOOL32 PfcRcvMsg(kdvHandle tQueueID, u32  dwTimeout, char *lpMsgBuf, size_t len, size_t *pLenRcved);

/**
* @brief        PfcClkRateGet
* @note         得到tick精度：n ticks/sec
*/
API u32 PfcClkRateGet();

/**
* @brief        PfcTickGet
* @note         取得当前的tick数
*/
API u32 PfcTickGet();

/**
* @brief        PfcTickGet64
* @note         取得当前的tick数,64长度，解决溢出问题
*/
API u64 PfcTickGet64();

/**
* @brief        PfcCpuShow
* @note         show current CPU usage
*/
API void PfcCpuShow();

/// CPU信息
typedef struct
{
    u8 m_byIdlePercent;	                ///< 空闲百分比，0－100
} TPfcCpuInfo;

/**
* @brief        PfcGetCpuInfo
* @note         取得当前的CPU信息
* @param[in]    ptCpuInfo: 用户CPU信息结构
* @return       返回值说明：为TRUE时表示获取信息成功，否则表示失败
*/
API BOOL32 PfcGetCpuInfo( TPfcCpuInfo *ptCpuInfo );

/// 内存信息
typedef struct
{
    size_t m_dwPhysicsSize;	            ///< 物理内存大小 KByte
    size_t m_dwAllocSize;	            ///< 已使用内存   KBytes 
    size_t m_dwFreeSize;	            ///< 可用内存     KBytes
} TPfcMemInfo;

/**
* @brief        PfcGetMemInfo
* @note         取得当前的Mem信息
* @param[in]    ptMemInfo: 用户MEM信息结构
* @return       返回值说明：为TRUE时表示获取信息成功，否则表示失败
*/
API BOOL32 PfcGetMemInfo( TPfcMemInfo *ptMemInfo );

/// 时间信息
typedef struct
{
    u16 m_wYear;	                    ///< 年 - 2006
    u16 m_wMonth;	                    ///< 月 - 1--12
    u16 m_wDay;	                        ///< 日 - 1--31
    u16 m_wHour;	                    ///< 时 - 0--23
    u16 m_wMinute;	                    ///< 分 - 0--59
    u16 m_wSecond;	                    ///< 秒 - 0--59
} TPfcTimeInfo;

/**
* @brief        PfcGetTimeInfo
* @note         取得当前的Time信息
* @param[in]    ptTimeInfo: 系统time信息结构
* @return       返回值说明：为TRUE时表示获取信息成功，否则表示失败
*/
API BOOL32 PfcGetTimeInfo( TPfcTimeInfo *ptTimeInfo );

/**
* @brief        PfcSetTimeInfo
* @note         设置当前的Time信息
* @param[in]    ptTimeInfo: 系统time信息结构
* @return       返回值说明：为TRUE时表示获取信息成功，否则表示失败
*/
API BOOL32 PfcSetTimeInfo( TPfcTimeInfo *ptTimeInfo );

/// 磁盘分区信息
typedef struct
{
    u32 m_dwPhysicsSize;	            ///< 磁盘分区大小(MByte)
    u32 m_dwUsedSize;	                ///< 已使用磁盘分区大小(MBytes)
    u32 m_dwFreeSize;	                ///< 可用磁盘分区大小(MBytes)
} TPfcDiskInfo;

/// 磁盘分区最大长度
#define MAX_PARTION_NAME_LENGTH     255
/**
* @brief        PfcGetDiskInfo
* @note         取得当前的磁盘分区信息
* @param[in]    pchPartionName: 分区名
                    win32 - "c:"
                    Vxworks - "/ata0/"
                    Linux - "/"
* @param[out]   ptDiskInfo: 系统磁盘分区信息结构
* @return       为TRUE时表示获取信息成功，否则表示失败
*/
API BOOL32 PfcGetDiskInfo( s8 *pchPartionName , TPfcDiskInfo *ptDiskInfo );

//////////////////////////////////////////////////////////////////////
//	套接字封装：用户使用套接字前必须先调用PfcSockInit()对套接字库进行初始化，
//	使用完之后则需要调用PfcSockCleanup()释放对套接字库的使用。由于vxWorks和
//	Windows的关闭套接字的函数不同，而且在调用socket、connect等函数时，返回
//	值类型也不一样，OSP也进行了必要的封装，原则是保持与Windows下基本一致。
/////////////////////////////////////////////////////////////////////

/**
* @brief        PfcSockInit
* @note         套接字初始化，封装Windows下的WSAStartup，vxWorks下返回TRUE
* @return       返回值说明：成功返回TRUE，失败返回FALSE
*/
API BOOL32 PfcSockInit(void);

/**
* @brief        PfcSockShutdown
* @note         对各平台shutdown的简单封装
* @param[in]    hSock: 要操作的套接字，
* @param[in]    dwMode: 操作模式, 可取值为STOP_SEND, STOP_RECV或STOP_BOTH
* @return       返回值说明：成功返回TRUE，失败返回FALSE
*/
API BOOL32 PfcSockShutdown(PFCSOCKHANDLE hSock, u32 dwMode);

/**
* @brief        SockClose
* @note         关闭套接字，封装windows下的closesocket和vxworks下的close.
* @param[in]    tSock: 待关闭套接字的句柄（调用socket时返回）。
* @return       返回值说明：成功返回TRUE，失败返回FALSE
*/
API BOOL32 PfcSockClose(PFCSOCKHANDLE tSock);

/**
* @brief        PfcSockCleanup
* @note         套接字销毁，封装windows的WSACleanup，vxWorks下返回TRUE
* @return       成功返回TRUE，失败返回FALSE
*/
API BOOL32 PfcSockCleanup(void);

/**
* @brief        PfcAgentStart
* @note         启动一个Osp测试代理, 其中包含一个测试服务器APP和一个客户端APP, 它们主要不同是APP号, 消息处理过程都是一样的.
* @param[in]    port -- 端口号, 如无其他APP创建服务节点则用该端口创建之
*/
API int PfcAgentStart(u16 port);


//////////////////////////////////////////////////////////////////////////
// Start of PFC memory pool
//////////////////////////////////////////////////////////////////////////
/**
* @defgroup     PFC_MemoryPool PFC memory pool wrapper
* @brief        pfc memory pool wrapper interfaces.
* @{
*/

/**
* @brief        PfcAllocMem
* @note         从内存池中分配内存块
* @param[in]    size: 待分配的内存块大小，
* @return       成功返回指向分配到的内存块的指针，失败返回NULL.
*/
API void *PfcAllocMem(size_t size);

/**
* @brief        PfcFreeMem
* @note         释放事先分配的内存块
* @param[in]    token: 指向待释放的内存块的指针。
*/
API void PfcFreeMem(void *token);

/**
* @}
*/
//////////////////////////////////////////////////////////////////////////
// End of PFC memory pool wrapper
//////////////////////////////////////////////////////////////////////////





/**
* @brief        PfcSetPriRealTime
* @note         把定时器、消息发送等任务提高到比系统net任务还高的优先级
*/
API void PfcSetPriRealTime();

/**
* @brief        PfcAddrListGet
* @note         获取本机地址表内容
* @pre          如果是在Windows下使用本函数，必须先调用PfcInit，或者WSAStartup。本函数效率较低，不要重复调用。
* @param[in]    adwIPList[] : [in/out]用户申请的用于地址表内容的数组的首地址
* @param[in]    wNum : [in]用户申请的数组的大小
* @return       返回本机地址表中地址个数，错误时返回0
*/
API u16  PfcAddrListGet(u32 adwIPList[], u16 wNum);

/** 5.0合并： 原企业osp特有接口 */
/**
* @brief        PfcGetTelServerPort
* @note         获取telnet server的端口号.
* @pre          如果没有启动telnet server, 或者没有初始化Osp, 返回-1
* @return       返回telnet server的listen端口号, 如果没有启动, 返回-1
*/
API s32 PfcGetTelServerPort();

/**
* @brief        OspPton
* @note         IP address & string conversion
* @param[in]    af: socket type
* @param[in]    src: IP address string
* @param[out]   dst: IP address
*/
API s32 PfcPton(s32 af, const char *src, void *dst);

/**
* @brief        OspNtop
* @note         IP address & string conversion
* @param[in]    af: socket type
* @param[in]    src: ip address pointer
* @param[out]   dst: ip address string
* @param[in]    size: input ip address length
*/
API const char *PfcNtop(s32 af, const void *src, char *dst, size_t size);

#if (defined(_MSC_VER) && (_MSC_VER > 1200)) || !defined(_MSC_VER)

#define OSP_IS_VALID_LOCAL_ADDR(netaddr)   \
    ((netaddr) &&   \
    (((netaddr)->v4addr.sin_family == AF_INET && (netaddr)->v4addr.sin_port) || \
    ((netaddr)->v6addr.sin6_family == AF_INET6 && (netaddr)->v6addr.sin6_port)))

#define OSP_IS_VALID_REMOTE_ADDR(netaddr)    \
    ((netaddr) &&   \
    (((netaddr)->v4addr.sin_family == AF_INET &&    \
        (netaddr)->v4addr.sin_addr.s_addr && (netaddr)->v4addr.sin_port) || \
    ((netaddr)->v6addr.sin6_family == AF_INET6 &&   \
        (netaddr)->v6addr.sin6_port)))

/**
* @brief        PFC_SET_NETADDR_ADDR
* @note         IPV4网络字节序地址设置到TNetAddr结构中
* @pre          只能是IPV4网络序的地址暂时
* @param[in]    netaddr: TPfcNetAddr结构体
* @param[in]    type: AF_INET(ipv4) 或者 AF_INET6(ipv6)
* @param[in]    address: u32网络序地址
*/
#define PFC_SET_NETADDR_ADDR(netaddr, type, address)    \
    do {    \
        switch(type) {    \
        case AF_INET:   \
            (netaddr)->v4addr.sin_family = (type);      \
            (netaddr)->v4addr.sin_addr.s_addr = (address);   \
            break;      \
        case AF_INET6:  \
            (netaddr)->v6addr.sin6_family = (type);     \
            break;  \
        default:    \
            break;  \
        }   \
    } while(0)

/**
* @brief        PFC_GET_NETADDR_ADDR
* @note         获取TNetAddr结构体中的网络字节序地址到address,获取TNetAddr结构体中的type到type
* @param[in]    netaddr: TOspNetAddr结构体
* @param[out]   type: 存放类型的指针
* @param[out]   address: 存放地址的指针
*/
#define PFC_GET_NETADDR_ADDR(netaddr, type, address)    \
	do {	\
		switch((netaddr)->staddr.ss_family) {	  \
		case AF_INET:	\
			*(type) = (netaddr)->v4addr.sin_family;		\
			*(address) = (netaddr)->v4addr.sin_addr.s_addr;	 \
			break;		\
		case AF_INET6:	\
			*(type) = (netaddr)->v6addr.sin6_family; 	\
			break;	\
		default:	\
			break;	\
		}	\
	} while(0)

/**
* @brief        PFC_SET_NETADDR_ADDR_STR
* @note         将地址字符串设置到netaddr结构中
* @param[in]    netaddr: TOspNetAddr结构体
* @param[in]    type: AF_INET(ipv4) 或者 AF_INET6(ipv6)
* @param[in]    address: 地址字符串指针
*/
#define PFC_SET_NETADDR_ADDR_STR(netaddr, type, address)    \
    do {    \
        switch(type) {      \
        case AF_INET:       \
            (netaddr)->v4addr.sin_family = (type);      \
            if (address)    \
                OspPton(type, address, &((netaddr)->v4addr.sin_addr.s_addr));\
            else        \
                (netaddr)->v4addr.sin_addr.s_addr = INADDR_ANY;    \
            break;      \
        case AF_INET6:  \
            (netaddr)->v6addr.sin6_family = (type);     \
            if (address)    \
                OspPton(type, address, &((netaddr)->v6addr.sin6_addr.s6_addr));  \
            else    \
                memcpy(&(netaddr)->v6addr.sin6_addr, &in6addr_any, sizeof(in6addr_any));  \
            break;  \
        default:    \
            break;  \
        }   \
    } while(0)

/**
* @brief        PFC_GET_NETADDR_ADDR_STR
* @note         获取TNetAddr结构体中的地址字符串到address,获取TNetAddr结构体中的type到type
* @param[in]    netaddr: TOspNetAddr结构体
* @param[out]   type: 存放类型的指针
* @param[out]   address: 地址字符串指针
* @param[out]   size: address地址的长度
*/
#define PFC_GET_NETADDR_ADDR_STR(netaddr, type, address, size)    \
	do {	\
		if (type)    \
		    *(type) = (netaddr)->staddr.ss_family;		\
		switch((netaddr)->staddr.ss_family) {		\
		case AF_INET:		\
			if (address)	\
				OspNtop((s32)(*(type)), &((netaddr)->v4addr.sin_addr.s_addr), address, size);\
			break;		\
		case AF_INET6:	\
			if (address)	\
				OspNtop((s32)(*(type)), &((netaddr)->v6addr.sin6_addr.s6_addr), address, size);  \
			break;	\
		default:	\
			break;	\
		}	\
	} while(0)

/**
* @brief        PFC_SET_NETADDR_PORT
* @note         提供主机序端口号设置到TNetAddr 中
* @param[in]    netaddr: TOspNetAddr结构体
* @param[in]    type: AF_INET(ipv4) 或者 AF_INET6(ipv6)
* @param[in]    port: 主机序端口号
*/
#define PFC_SET_NETADDR_PORT(netaddr, type, port)    \
    do {    \
        switch(type) {    \
        case AF_INET:   \
            (netaddr)->v4addr.sin_family = (type);      \
            (netaddr)->v4addr.sin_port = htons(port);   \
            break;      \
        case AF_INET6:  \
            (netaddr)->v6addr.sin6_family = (type);     \
            (netaddr)->v6addr.sin6_port = htons(port);  \
            break;  \
        default:    \
            break;  \
        }   \
    } while(0)

/**
* @brief        PFC_GET_NETADDR_PORT
* @note         获取TNetAddr结构体中端口号到port,获取TNetAddr结构体中的type到type
* @param[in]    netaddr: TOspNetAddr结构体
* @param[out]   type: 存放类型的指针
* @param[out]   port: 存放主机序端口号的指针
*/
#define PFC_GET_NETADDR_PORT(netaddr, type, port)    \
	do {	\
		if (type)    \
		    *(type) = (netaddr)->staddr.ss_family;    \
		switch((netaddr)->staddr.ss_family) {	  \
		case AF_INET:	\
			if (port)   \
			    *(port) = ntohs((netaddr)->v4addr.sin_port);	\
			break;		\
		case AF_INET6:	\
			if (port)   \
			    *(port) = ntohs((netaddr)->v6addr.sin6_port);	\
			break;	\
		default:	\
			break;	\
		}	\
	} while(0)

#endif

/// 系统限制参数
#define OSP_ETHERNET_ADAPTER_MAX_IP         16              ///< 每个接口上最大地址个数
#define OSP_ETHERNET_ADAPTER_MAX_NUM        32              ///< 每个设备最大接口数
#define OSP_ETHERNET_ADAPTER_NAME_LENGTH    64              ///< 每个接口名的最大长度
#define OSP_ETHERNET_ADAPTER_MAC_LENGTH     6               ///< 接口的MAC地址长度

/// 网卡状态,对应于TOSPEthernetAdapterInfo 结构的nState字段
#define OSP_ETHERNET_ADAPTER_UNKNOWN        0               ///< unknown status
#define OSP_ETHERNET_ADAPTER_UP             1               ///< ethernet up
#define OSP_ETHERNET_ADAPTER_DOWN           2               ///< ethernet down

/// 单个网卡信息
typedef struct
{
	u32 nId;                                                ///< 网卡号
	u32 nState;                                             ///< 网卡状态
	u8  achName[OSP_ETHERNET_ADAPTER_NAME_LENGTH];          ///< 网卡名
	u8  achDescription[OSP_ETHERNET_ADAPTER_NAME_LENGTH];   ///< 网卡信息描述
	u8  achMacAddr[OSP_ETHERNET_ADAPTER_MAC_LENGTH];        ///< 卡物理地址
	u32 nIpNum;                                             ///< 地址数量
	u32 anIp[OSP_ETHERNET_ADAPTER_MAX_IP];                  ///< 地址
} TPfcEthernetAdapterInfo;

/// 多个网卡信息
typedef struct
{
	u32 nNum;                                               ///< 网卡数量
	TPfcEthernetAdapterInfo atEthernetAdapter[OSP_ETHERNET_ADAPTER_MAX_NUM];///< 网卡信息
} TPfcEthernetAdapterInfoAll;

/**
* @brief        PfcGetEthernetAdapterInfoAll
* @note         获取本系统所有以太网网卡信息
* @pre          如果是在Windows下使用本函数，必须先调用PfcInit，或者WSAStartup。本函数效率较低，不要重复调用。
* @param[out]   ptEthernetAdapterInfoAll: 多网卡信息结构，参考数据结构的定义
* @return       TRUE/ FALSE 成功/失败
*/
API BOOL32 PfcGetEthernetAdapterInfoAll(TPfcEthernetAdapterInfoAll *ptEthernetAdapterInfoAll);

/**
* @brief        PfcGetEthernetAdapterInfo
* @note         根据网卡号获取网卡信息
* @pre          如果是在Windows下使用本函数，必须先调用PfcInit，或者WSAStartup。本函数效率较低，不要重复调用。
* @param[in]    nEthAdapterId: 网卡编号0-ETHERNET_ADAPTER_MAX_NUM，最多支持16个网卡
* @param[out]   ptEthernetAdapterInfo: 单网卡信息结构
* @return       TRUE/FALSE  成功/失败
*/
API BOOL32 PfcGetEthernetAdapterInfo(u32 nEthAdapterId, TPfcEthernetAdapterInfo *ptEthernetAdapterInfo);

/**
* @brief        PfcSetMemCheck
* @note         获取内存地址内容
* @param[in]    pdwCheckMem :  要检查的内存地址
* @param[in]    dwCheckValue ：  期望检查的值
* @param[in]    bEqual ：当本参数为真时，表示要检查的内存地址内容不等于期望值时需要告警
* @pre          当本参数为假时，表示要检查的内存地址内容等于期望值时需要告警
* @return       成功返回TRUE, 失败返回FALSE.
*/
API BOOL32  PfcSetMemCheck(u32 *pdwCheckMem, u32 dwCheckValue, BOOL32  bEqual);

/**
* @brief        pfchelp
* @pre          
* @note         inline help function of PFC module
* @return       void
*/
API void pfchelp(void);


/*=============================================================================
函 数 名：PfcTelSvrSetAddr
功    能：指定侦听地址
注    意：
算法实现：
全局变量：
参    数：void
返 回 值：void
-------------------------------------------------------------------------------
修改纪录：
日      期  版本  修改人  修改内容
2018/11/20  1.0
=============================================================================*/
API u16 PfcTelSvrSetAddr(TPfcNetAddr addr);

typedef enum {
	PFC_EVENT_CB_TIMEOUT           = 1,
	PFC_EVENT_CB_UNDEFINED         = 0
} PfcTelSvrEvtType;

typedef struct {
	PfcTelSvrEvtType     type;        //需要处理的回调类型
	void                *param;
} PfcTelSvrEvtCBParam;
typedef void (*PfcTelSvrSetCallback)(void *pContext, PfcTelSvrEvtCBParam *pCBEvtParam);
/*=============================================================================
函 数 名：PfcTelSvrSetTimeout
功    能：telnet超时断开检测
注    意：
算法实现：
全局变量：
参    数：u32 timeout 超时时间以秒为单位 若timeout==0则取消定时器
返 回 值：void
-------------------------------------------------------------------------------
修改纪录：
日      期  版本  修改人  修改内容
2018/11/20  1.0
=============================================================================*/
API u16 PfcTelSvrSetTimeout(u32 timeout);

/*=============================================================================
函 数 名：PfcTelSvrSetCB
功    能：telnet超时断开回调
注    意：
算法实现：
全局变量：
参    数：OspTelSvrSetCallback cb 超时回调函数 若pContext==NULL 则取消回调
返 回 值：BOOL32
-------------------------------------------------------------------------------
修改纪录：
日      期  版本  修改人  修改内容
2018/11/20  1.0
=============================================================================*/
API u16 PfcTelSvrSetCB(void *pContext, PfcTelSvrEvtCBParam *pCBEvtParam, PfcTelSvrSetCallback cb);

/*=============================================================================
函 数 名：PfcTelSvrStart
功    能：开启PfcTelnet
注    意：
算法实现：
全局变量：
参    数：
返 回 值：u16  开启telnet，并返回当前telnet状态
-------------------------------------------------------------------------------
修改纪录：
日      期  版本  修改人  修改内容
2018/11/20  1.0
=============================================================================*/
API u16 PfcTelSvrStart();

/*=============================================================================
函 数 名：PfcTelSvrStop
功    能：关闭PfcTelnet
注    意：
算法实现：
全局变量：
参    数：
返 回 值：u16 关闭telnet，并返回当前telnet状态
-------------------------------------------------------------------------------
修改纪录：
日      期  版本  修改人  修改内容
2018/11/20  1.0
=============================================================================*/
API u16 PfcTelSvrStop();

/*=============================================================================
函 数 名：PfcTelSvrInit
功    能：Pfc终端初始化
注    意：
算法实现：
全局变量：
参    数：
返 回 值：BOOL32
-------------------------------------------------------------------------------
修改纪录：
日      期  版本  修改人  修改内容
2018/12/24  1.0
=============================================================================*/
API BOOL32 PfcTelSvrInit();






















/// 内联成员函数或模板类成员函数的实现
template <class I, int maxins, class A, u8 maxAliasLen>
BOOL32 zTiTemplate<I, maxins, A, maxAliasLen>::InitAliasArray()
{
	for(int i = 0; i < maxins; i++) {
		instAliasArray[i].instId = 0xFFFF;
		instAliasArray[i].aliasRet = 0;
		instAliasArray[i].nextLoc = 0xFFFF;

		bakInstAliasArray[i].instId = 0xFFFF;
		bakInstAliasArray[i].aliasRet = 0;
		bakInstAliasArray[i].nextLoc = 0xFFFF;
	}
	curBakArrayNum = 0;

	return TRUE;
}

template <class I, int maxins, class A, u8 maxAliasLen>
u32 zTiTemplate<I, maxins, A, maxAliasLen>::AliasToWord(char *pchAlias, u8 len)
{
	u32  ret = 0;
	for(u8 i = 0; i < len; i++ ) {
		ret =  (ret << 5) + ret + (*(pchAlias + i));
	}

	ret = ret & (maxins - 1);
	return  ret;
}

template <class I, int maxins, class A, u8 maxAliasLen>
BOOL32 zTiTemplate<I, maxins, A, maxAliasLen>::IsInBakArray(u32  setRet)
{
	/* 首先检查主数组 */
	if(instAliasArray[setRet].instId == 0xFFFF) {  /*主数组中这个位置还没有被占用*/
		return FALSE;     /*这个实例存放到主数组中*/
	} else {     /*主数组中这个位置还已经被占用*/
		return TRUE;   /*这个实例存放到bak数组中的空闲位置*/
	}
}

template <class I, int maxins, class A, u8 maxAliasLen>
int zTiTemplate<I, maxins, A, maxAliasLen>::GetInstanceNumber(void)
{
	return maxins;
}

template <class I, int maxins, class A, u8 maxAliasLen>
u8 zTiTemplate<I, maxins, A, maxAliasLen>::GetMaxAliasLen(void)
{
	return maxAliasLen;
}

template <class I, int maxins, class A, u8 maxAliasLen>
CTiInstance *zTiTemplate<I, maxins, A, maxAliasLen>::GetInstance(u16 insid)
{
	if(insid == CTiInstance::DAEMON)
		return &daemIns;

	if((insid > 0) && (insid <= maxins))
		return &insarray[insid - 1];

	return NULL;
}

template <class I, int maxins, class A, u8 maxAliasLen>
BOOL32 zTiTemplate<I, maxins, A, maxAliasLen>::SetInstAlias(u16 insid, const char *pchAlias, u8 len)
{
	u32  dwCycTime = 0;

	/*先把记录信息放入快速查找数组中*/
	if(insid != CTiInstance::DAEMON) {
		u32 setRet = AliasToWord((char *)pchAlias, len);    /*通过别名计算设置值*/
		if(setRet >= maxins)
			return FALSE;

		BOOL32  isBak = IsInBakArray(setRet);   /*确定存放位置*/
		if( isBak == FALSE) {   /*存放在主数组中*/
			instAliasArray[setRet].aliasRet = setRet;
			instAliasArray[setRet].instId = insid;
			instAliasArray[setRet].nextLoc = 0xFFFF;   /*初始化*/
		} else {     /*存放在bak数组中*/
			u32 loc = curBakArrayNum;
			/*把数据记录到bak数组相应位置中*/
			for(loc = 0; loc < maxins; loc++) {
				if(bakInstAliasArray[loc].instId == 0xFFFF)
					break;
			}
			if(loc >= maxins) {
				return FALSE;
			}

			bakInstAliasArray[loc].aliasRet = setRet;
			bakInstAliasArray[loc].instId = insid;
			bakInstAliasArray[loc].nextLoc = 0xFFFF;   /*初始化*/

			/*把相同设置值的数据块连接起来*/
			if(instAliasArray[setRet].nextLoc == 0xFFFF) { /*主数组中尚未连接*/
				instAliasArray[setRet].nextLoc = loc;   /*指向bak数组中存放位置*/
			} else {
				TTiInstAliasInfo *tempAlias = &bakInstAliasArray[instAliasArray[setRet].nextLoc];
				if(tempAlias == NULL)
					return FALSE;

				dwCycTime = 0;
				while(tempAlias->nextLoc != 0xFFFF) {
					if(tempAlias->nextLoc >= maxins)
						return FALSE;

					tempAlias = &bakInstAliasArray[tempAlias->nextLoc];
					if(tempAlias == NULL)
						return FALSE;

					dwCycTime++;
					if(dwCycTime > maxins) {
						PfcPrintf(TRUE, FALSE, "SetInstAlias() return Cycle as dwCycTime=%d\n", dwCycTime);
						return FALSE;
					}
				}

				tempAlias->nextLoc = loc; /*找到bak数组中最后一个相同设置值的位置*/
			}

			curBakArrayNum++;     /*bak数组存放个数增加*/
		}
	}

	CTiInstance *pIns = GetInstance(insid);
	if( pIns != NULL && len <= maxAliasLen) {
		CTiInstance *pOtherIns = FindInstByAlias(pchAlias, len);
		if( (pOtherIns != NULL) && (pOtherIns->GetInsID() != pIns->GetInsID()) ) {
			return FALSE;
		}
		memcpy(pIns->m_alias, pchAlias, len);
		pIns->m_aliasLen = len;
		//return pIns->SetAlias(pchAlias, len);
	}
	return TRUE;
}

template <class I, int maxins, class A, u8 maxAliasLen>
CTiInstance *zTiTemplate<I, maxins, A, maxAliasLen>::FindInstByAlias(const char *pchAlias, u8 len)
{
	/* 先看是否是Daemon实例 */
	u8   aliasLen = 0;
	u32  dwCycTime = 0;

	if(maxAliasLen < len) {
		return NULL;
	}

	char aliasBuf[MAX_ALIAS_LEN];
	memset(aliasBuf, 0, MAX_ALIAS_LEN);

	CTiInstance *pIns = GetInstance(CTiInstance::DAEMON);
	if(pIns != NULL &&
	   pIns->GetAlias(aliasBuf, maxAliasLen, &aliasLen)) {
		if( (aliasLen == len) &&
			(memcmp(aliasBuf, pchAlias, len) == 0) ) {
			return pIns;
		}
	}

	/* 再看是否普通实例 */
	TTiInstAliasInfo *tempAlias = NULL;
	u32  setRet = AliasToWord((char *)pchAlias, len);
	/*先查找主数组*/
	if(setRet >= maxins)
		return NULL;

	tempAlias = &instAliasArray[setRet];
	if(tempAlias == NULL)
		return NULL;

	pIns = GetInstance(tempAlias->instId);
	if((pIns != NULL) && (pIns->GetAlias(aliasBuf, maxAliasLen, &aliasLen))) {
		if( (aliasLen == len) && (memcmp(aliasBuf, pchAlias, len) == 0) ) {
			return pIns;
		}
	}
	/*再查找bak数组*/
	do {
		if((tempAlias == NULL) || (tempAlias->nextLoc >= maxins))
			return NULL;

		tempAlias = &bakInstAliasArray[tempAlias->nextLoc];
		if(tempAlias == NULL)
			return NULL;

		CTiInstance *pIns = GetInstance(tempAlias->instId);
		if((pIns != NULL) && (pIns->GetAlias(aliasBuf, maxAliasLen, &aliasLen))) {
			if((aliasLen == len) && (memcmp(aliasBuf, pchAlias, len) == 0)) {
				return pIns;
			}
		}

		dwCycTime++;
		if(dwCycTime > maxins) {
			PfcPrintf(TRUE, FALSE, "FindInstByAlias() return Cycle as dwCycTime=%d\n", dwCycTime);
			return NULL;
		}
	} while(tempAlias->nextLoc != 0xFFFF);

	return NULL;
}

/*清除实例别名纪录信息*/
template <class I, int maxins, class A, u8 maxAliasLen>
BOOL32 zTiTemplate<I, maxins, A, maxAliasLen>::ClearInstAlias(u16 insid, const char *pAlias, u8 len)
{
	u32  dwCycTime = 0;

	if((maxAliasLen < len) || (insid == CTiInstance::DAEMON)) {
		return FALSE;
	}

	u32 setRet = AliasToWord((char *)pAlias, len);    /*通过别名计算设置值*/
	if(setRet >= maxins)
		return FALSE;

	/*先查找主数组，再查找备用数组*/
	if(instAliasArray[setRet].instId == insid) {
		if(instAliasArray[setRet].nextLoc == 0xFFFF) { /*主数组中尚未连接*/
			instAliasArray[setRet].aliasRet = 0;       /*初始化*/
			instAliasArray[setRet].instId = 0xFFFF;
			instAliasArray[setRet].nextLoc = 0xFFFF;
		} else {
			TTiInstAliasInfo *tempAlias = &instAliasArray[setRet];
			if(tempAlias == NULL)
				return FALSE;

			if(tempAlias->nextLoc >= maxins)
				return FALSE;

			TTiInstAliasInfo *relocAlias = &bakInstAliasArray[tempAlias->nextLoc];
			if(relocAlias == NULL)
				return FALSE;

			dwCycTime = 0;
			while(relocAlias->nextLoc != 0xFFFF) {
				tempAlias->aliasRet = relocAlias->aliasRet;    //用下一块记录信息填充本块记录信息
				tempAlias->instId = relocAlias->instId;

				if(relocAlias->nextLoc >= maxins)
					return  FALSE;

				tempAlias = relocAlias;         //位置移到下一块
				relocAlias = &bakInstAliasArray[relocAlias->nextLoc];
				if(relocAlias == NULL)
					return  FALSE;

				dwCycTime++;
				if(dwCycTime > maxins) {
					PfcPrintf(TRUE, FALSE, "ClearInstAlias(1) return Cycle as dwCycTime=%d\n", dwCycTime);
					return FALSE;
				}
			}

			tempAlias->aliasRet = relocAlias->aliasRet;    //已到最后一块记录信息块
			tempAlias->instId = relocAlias->instId;
			tempAlias->nextLoc = 0xFFFF;

			relocAlias->aliasRet = 0;      //清除最后一块记录块
			relocAlias->instId = 0xFFFF;
			relocAlias->nextLoc = 0xFFFF;

			curBakArrayNum--;     /*bak数组存放个数减少*/
		}
	} else {
		if(instAliasArray[setRet].nextLoc == 0xFFFF) { /*主数组中尚未连接*/
			return  FALSE;
		} else {
			TTiInstAliasInfo *tempAlias = &bakInstAliasArray[instAliasArray[setRet].nextLoc];
			if(tempAlias == NULL)
				return FALSE;

			TTiInstAliasInfo *relocAlias = &(instAliasArray[setRet]);

			dwCycTime = 0;
			while(tempAlias->instId != insid) {
				relocAlias = tempAlias;

				if(tempAlias->nextLoc != 0xFFFF) {
					if(tempAlias->nextLoc >= maxins)
						return  FALSE;

					tempAlias = &bakInstAliasArray[tempAlias->nextLoc];
					if(tempAlias == NULL)
						return FALSE;

					dwCycTime++;
					if(dwCycTime > maxins) {
						PfcPrintf(TRUE, FALSE, "ClearInstAlias(2) return Cycle as dwCycTime=%d\n", dwCycTime);
						return FALSE;
					}
				} else {
					return  FALSE;
				}
			}

			/*找到bak数组中对应实例纪录位置，清除该位置的记录值，把记录链表重新连接*/
			if(tempAlias->nextLoc == 0xFFFF) {
				if(relocAlias != NULL)
					relocAlias->nextLoc = 0xFFFF;

				tempAlias->aliasRet = 0;     //该位置为本设置值的最后一位置，直接清除
				tempAlias->instId = 0xFFFF;
			} else {
				relocAlias = &bakInstAliasArray[tempAlias->nextLoc];
				if(relocAlias == NULL)
					return FALSE;

				dwCycTime = 0;
				while(relocAlias->nextLoc != 0xFFFF) {
					tempAlias->aliasRet = relocAlias->aliasRet;    //用下一块记录信息填充本块记录信息
					tempAlias->instId = relocAlias->instId;

					if(relocAlias->nextLoc >= maxins)
						return  FALSE;

					tempAlias = relocAlias;         //位置移到下一块
					relocAlias = &bakInstAliasArray[relocAlias->nextLoc];
					if(relocAlias == NULL)
						return  FALSE;

					dwCycTime++;
					if(dwCycTime > maxins) {
						PfcPrintf(TRUE, FALSE, "ClearInstAlias(3) return Cycle as dwCycTime=%d\n", dwCycTime);
						return FALSE;
					}
				}

				tempAlias->aliasRet = relocAlias->aliasRet;    //已到最后一块记录信息块
				tempAlias->instId = relocAlias->instId;
				tempAlias->nextLoc = 0xFFFF;

				relocAlias->aliasRet = 0;      //清除最后一块记录块
				relocAlias->instId = 0xFFFF;
				relocAlias->nextLoc = 0xFFFF;
			}

			curBakArrayNum--;     /*bak数组存放个数减少*/
		}
	}

	return  TRUE;
}

#if defined(_MSC_VER) && !defined(_EQUATOR_)
#pragma pack(pop)
#endif

/**
* @}
*/

#endif // _OSP_H
