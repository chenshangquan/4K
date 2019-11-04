/*****************************************************************************
   模块名      : DataSwitch
   文件名      : dataswitch.h
   相关文件    :
   文件实现功能: DataSwitch模块接口函数定义
-----------------------------------------------------------------------------
   修改记录:
   日  期      版本        修改人      修改内容
   2005/03/18  4.0         靳志业        创建
   2005/08/10  4.0         靳志业        实现3.6中新增的功能
   2014/06/20  5.0         曾昭鸣        实现rtpswitch功能
   2014/10/09  5.1         曾昭鸣        合并所有kdv和movision的dataswitch
******************************************************************************/

#ifndef DATASWITCH_H
#define DATASWITCH_H

#define DSVERSION       "DataSwitch.TS.6.0(Support IPv6)"

#include "osp.h"
#include "kdvtype.h"
#include "rtp_endpoint_id.h"     //rtp标识的定义和接口

#ifdef KDVTYPE_LEGACY_H	
#define  DATASWITCH_LEGACY_H	
#endif


/* DataSwitch 句柄 */
#define DSID    u32

#define DSID_LEN          16
#define DSID_MASK         0xffff0000
#define RTPID_MASK        0x0000ffff

#define DS_GET_DSID(rtpId) \
    ((((rtpId) & DSID_MASK) >> DSID_LEN) + 1)

#define DS_GET_DSRTPID(rtpId) \
    ((rtpId) & RTPID_MASK)

/*DataSwitch 返回值*/
#define DS_ERATELIMIT   2
#define DSOK    1
#define DSERROR 0

#define INVALID_DSID  0xffffffff   /*无效的句柄值*/

#if (defined _MSC_VER)
#include <Winsock2.h>
#include <ws2tcpip.h>
//TODO: inet_pton的工作移到OSP中完成
#ifndef inet_pton
#define inet_pton
#endif
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#endif

typedef struct tagDsGlobalParam
{
	tagDsGlobalParam()
	{
		m_dwRecvBuff = 2 * 1024 * 1024 ;
		m_dwSendBuff = 2 * 1024 * 1024 ;
	}

	u32	m_dwRecvBuff;
	u32	m_dwSendBuff;
} TDsGlobalparam;

API void dsSetGlobalParam(TDsGlobalparam tParam );


#define SENDMEM_MAX_MODLEN        (u8)32        // 发送时允许的最大修改长度

API void dsSetApiTimeOut(s32 timeout);
/**********************************************************
 * 函数: dsSetCapacity                                    *
 * 功能: 容量设置(只能在创建交换模块之前调用)             *
 * 输入: dwMaxRcvGrp        - 最大接收组数                *
 *       dwMaxSndMmbPerRcvGrp  - 每一接收组最大发送目标数   *
 * 输出: 无                                               *
 * 返回: 成功返回DSOK 否则DSERROR                         *
 **********************************************************/
API u32 dsSetCapacity( u32 dwMaxRcvGrp, u32 dwMaxSndMmbPerRcvGrp );

/************************************************************
 * 函数名：dsCreate
 *
 * 功能：  运行DataSwitch模块
 *
 * 实现说明：
 * Dataswitch支持“多用户”；每次调用dsCreate就会返回一个
 * 用户标识。添加、删除时均要匹配用户标志，转发时则不考虑。
 *
 * 返回值：
 * @return INVALID_DSID: 表示失败 ; 否则成功
 ************************************************************/
API DSID dsCreate();

/************************************************************
 * 函数名：dsDestroy
 *
 * 功能： 终止DataSwitch的运行
 *
 * 实现说明：
 * 一次删除一个用户，直到所有用户都删除，所有资源才全释放。
 *
 * 参数说明：
 * @param dsId  - 用户标识
 *
 * 返回值：
 ************************************************************/
API void dsDestroy( DSID dsId );

enum {
    DS_NONE_FLAG			= 0,				//无标志
	DS_RTP_RMV_EXT			= 0x1 << 0,			//转发时，删除RTP扩展头，针对目的使用
    DS_SKIP_POLICY_ROUTING  = 0x1 << 1,         //防止被内核策略路由丢弃
	DS_IS_RTCP_RULE         = 0x1 << 2,         //确定为RTCP交换，重传请求包需要修改rtp回传地址
};

typedef TOspNetAddr dsNetAddr;

#define DS_IS_VALID_ADDR(netaddr) OSP_IS_VALID_LOCAL_ADDR(netaddr)
#define DS_IS_VALID_LOCAL_ADDR(netaddr) OSP_IS_VALID_LOCAL_ADDR(netaddr)
#define DS_IS_VALID_REMOTE_ADDR(netaddr) OSP_IS_VALID_REMOTE_ADDR(netaddr)
/*
#define DS_IS_VALID_ADDR(netaddr)   \
    ((netaddr) &&   \
    (((netaddr)->v4addr.sin_family == AF_INET && (netaddr)->v4addr.sin_port) || \
    ((netaddr)->v6addr.sin6_family == AF_INET6 && (netaddr)->v6addr.sin6_port)))

#define DS_IS_VALID_LOCAL_ADDR(netaddr)   \
    ((netaddr) &&   \
    (((netaddr)->v4addr.sin_family == AF_INET && (netaddr)->v4addr.sin_port) || \
    ((netaddr)->v6addr.sin6_family == AF_INET6 && (netaddr)->v6addr.sin6_port)))

#define DS_IS_VALID_REMOTE_ADDR(netaddr)    \
    ((netaddr) &&   \
    (((netaddr)->v4addr.sin_family == AF_INET &&    \
        (netaddr)->v4addr.sin_addr.s_addr && (netaddr)->v4addr.sin_port) || \
    ((netaddr)->v6addr.sin6_family == AF_INET6 &&   \
        (netaddr)->v6addr.sin6_port)))
*/

/* 提供网络字节序地址设置到dsNetAddr结构中 */
#define DS_SET_NETADDR_ADDR(netaddr, type, address)    \
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

/* 提供网络地址字符串设置到dsNetAddr结构中 */
#define DS_SET_NETADDR_ADDR_STR(netaddr, type, address)    \
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

/* 提供主机序端口号设置到dsNetAddr 中 */
#define DS_SET_NETADDR_PORT(netaddr, type, port)    \
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

/* -------------------- 开始定义rtpswitch -------------------*/
#define INVALID_RTPSWITCHID ((u32)-1)

//为了多实例将 DSRTPSID定义改为 
/*
 *  31---------------------15-----------------------0
 *  |    DSID               | RTPID                 |
 *  -------------------------------------------------
 */
typedef u32		DSRTPSID;

#define DS_MAX_SECKEY_LEN (512)

//密钥长度
#define DS_SECKEY_LEN_AES_256_GCM (44)
#define DS_SECKEY_LEN_AES_128_GCM (28)
#define DS_SECKEY_LEN_AES_256_ICM (46)
#define DS_SECKEY_LEN_AES_128_ICM (30)
#define DS_SECKEY_LEN_SM4_128_CM  (30)
#define DS_SECKEY_LEN_SM1_128_CM  (30)

#define DS_SECKEY_LEN_AES_256_H235 (32)
#define DS_SECKEY_LEN_AES_192_H235 (28)
#define DS_SECKEY_LEN_AES_128_H235 (16)

//auth tag 长度
#define DS_AUTH_LEN_80 (80)
#define DS_AUTH_LEN_32 (32)

typedef enum {
	DS_SECKEY_TYPE_UNDEFINED	= 0,
    DS_SECKEY_TYPE_STATIC		= 1, 
	DS_SECKEY_TYPE_DYNAMIC		= 2, 
	DS_SECKEY_TYPE_DTLS			= 3,
	DS_SECKEY_TYPE_MAX          = 4
} dsSecKeyTypes;

typedef enum {
    DS_REKEY_MODE_NULL  = 0, 
    DS_REKEY_MODE_BY_ID = 1, 
    DS_REKEY_MODE_BY_SN = 2, 
    DS_REKEY_MODE_MAX,       
} dsCryptReKeyMode;    

typedef struct dsCryptRekeyByidCfg {
    u8 rekey_rate;
    u64 intv;
    u16 id_len;
    u16 len_after_id;	//业务不需要填写
    u8 *id_buf;			//业务不需要填写
} dsCryptRekeyByidCfg;

typedef struct dsCryptRekeyBySNCfg {
    u16 sn_intv;
} dsCryptRekeyBySNCfg;

typedef struct dsCryptRekeyCfg {
    u8 rekey_mode;
    void *ctx;
    void *alloc_key;
    void *find_key;

    union {
        dsCryptRekeyByidCfg byid;
        dsCryptRekeyBySNCfg bysn;
    } cfg;

} dsCryptRekeyCfg;


//加密获取key的回调
typedef u16 (*dsReKeyAllocCBById)(void* pContext, u8* pKey, u16* pKeyLen, u8* pKeyId, u16* pKeyIdLen);
//解密获取key的回调
typedef u16 (*dsReKeyFindCBById)(void* pContext, u8* pKey, u16* pKeyLen, u8* pKeyId, u16 pKeyIdLen);

//加密获取key的回调
typedef u16 (*dsReKeyAllocCBBySn)(void* pContext, u8* pKey, u16* pKeyLen, u64 sn, BOOL32 *rekeyChange);
//解密获取key的回调
typedef u16 (*dsReKeyFindCBBySn)(void* pContext, u8* pKey, u16* pKeyLen, u64 sn, BOOL32 *rekeyChange);

typedef struct {
  u8        keytype;  
  u16		keylen;
  u8		key[DS_MAX_SECKEY_LEN];  

  dsCryptRekeyCfg rekeyCfg;
} dsSecKey; 

#define DS_CIPHER_ENABLE      ((u8)1)
#define DS_CIPHER_DISABLE     ((u8)0)

#define DS_CIPHERPOLICY_NONE  ((u8)0)
#define DS_CIPHERPOLICY_H235  ((u8)1)
#define DS_CIPHERPOLICY_SRTP  ((u8)2)
#define DS_CIPHERPOLICY_MAX   ((u8)3)

//算法类型
typedef enum {
	DS_SEC_ALG_NONE		= 0,
	DS_SEC_ALG_AES_128	= 1,
	DS_SEC_ALG_AES_192	= 2,
	DS_SEC_ALG_AES_256	= 3,
	DS_SEC_ALG_SM_4     = 4,
	DS_SEC_ALG_SM_1     = 5,
	DS_SEC_ALG_MAX      = 6
}dsCipherAlgId;

typedef enum {
	DS_AUTH_ALG_NONE		= 0,
	DS_AUTH_ALG_SHA1		= 1,
	DS_AUTH_ALG_SM_3        = 6,
	DS_AUTH_ALG_MAX         = 7
}dsAuthAlgId;


//模式
typedef enum {
    SRTP_AES_ICM	= 1, 
	SRTP_AES_GCM	= 2,
	
	H235_AES_CBC	= 3,
	H235_AES_ECB	= 4,
	H235_AES_CFB1	= 5,

	SRTP_SM4_CM     = 6,

	SRTP_SM1_CM     = 7,
	DS_CRYPTO_TYPE_MAX = 8,
	SRTP_UNDEFINED  = 0,
} dsSrtpCryptoTypes;


typedef struct dsCipher{
  u8        enable;//是否启用加解密 1：启用 0：不启用
  u8		policy;//模式 0: none 1：H235 2: srtp 
  u8		isCipher;//是否加解密 1: 加解密 0: 不加解密  
  u32		cipherAlgId;//算法id   
  u8        cipherMod;//加密工作模式 
  //u8        ext_cipher;//是否加密扩展头
  dsSecKey  seckey;//密钥
  u8		isAuth;//是否认证
  u32		authAlgId;//算法id
  u8        authTagLen;//auth tag 长度
  dsSecKey  authKey;//认证密钥 
  dsCipher* next;
} dsCipher;

#define DS_EP_ATTR_MAX_SIZE (2048)
#define DS_EP_PATTR_MAX_SIZE (80)

//终端属性
typedef union {
	u8 attr_data[DS_EP_PATTR_MAX_SIZE];
	void* align;
}dsEpAttr_t;

typedef enum {
    DS_SYNC_ADAPTER_INVALID = 0,
    DS_SYNC_ADAPTER_STD_TO_SSRCTS = 1,
    DS_SYNC_ADAPTER_SSRCTS_TO_STD = 2,  
} dsSyncAdapterType;

typedef enum {
    DS_MEDIA_TYPE_INVALID = 0,
    DS_MEDIA_TYPE_VIDEO = 1,
    DS_MEDIA_TYPE_AUDIO = 2,
    DS_MEDIA_TYPE_TEXT = 3,
	DS_MEDIA_TYPE_CTL = 4,
} dsMediaType;

/* rtp终端的信息 */
typedef struct {
    dsRtpEndpointId id;     //rtp 终端id
    dsNetAddr addr;         //rtp 终端的网络地址
    s32 ifindex;            //rtp 终端的上线网口
    dsMediaType mediaType;

	dsEpAttr_t attr;        //终端属性
} dsRtpEndpoint;


typedef enum {    
	DS_FRAME_CB_EV       = 0x00000001, //帧事件通知
	DS_UNDEFINED_EV      = 0x00000000, 
} dsCBEvType;

// 终端事件通知回调属性 

typedef struct {
	u8	ptype;
	u32 timestamp;
	u32 ssrc;
	u16 sequence;
} dsRtpInf;

typedef enum {
	DS_EVT_CB_SSRC_CHANGE       	= 0x00000001,		//源切变检测

    DS_EVT_CB_KEYFRAME_DETECT   	= 0x00000002,		//源切变检测 并检测关键帧

	DS_EVT_CB_UNDEFINED			    = 0x00000000, 
} dsFrameEvtCBType;

typedef struct {
   u32              type;    //事件类型 参考 dsFrameEvtCBType，
                             //可以多个类型 : type=DS_EVT_CB_SSRC_CHANGE|DS_EVT_CB_KEYFRAME_DETECT
   dsRtpEndpoint	src;     //udp/rtp数据源信息
   dsRtpEndpoint	dst;     //udp/rtp数据目的信息
   DSRTPSID         dsRtpSId;//接收组标识
   dsRtpInf			rtpInf;  //rtp信息
   BOOL32			bIFrame; //是否关键帧
   u8				EvtSrc;  //事件源 srcEp 1 /dstEp : 2
} dsFrameEvtCBParam;

// 终端回调返回属性 
typedef struct {
   BOOL32	bIsSwitch;//是否转发
} dsFrameEvtCBRetParam;

typedef void (*dsFrameEvtCB)(void					 *pAppData,			//用户自定义的回调函数的参数
						     dsFrameEvtCBParam       *cbEvtParam,		//回调事件参数
						     dsFrameEvtCBRetParam    *cbEvtRetParam     //回调返回参数
	                        );

// 终端事件通知回调属性 
typedef struct dsFrameEvtCBAttr{
  u32                   type;               //事件类型 参考 dsFrameEvtCBType，
                                            //可以多个类型 : type=DS_EVT_CB_SSRC_CHANGE|DS_EVT_CB_KEYFRAME_DETECT
  void *				pAppData;			//用户自定义的回调函数的参数
  dsFrameEvtCB			pdsFrameEvtCB;	    //回调函数指针
  dsFrameEvtCBAttr*		next;			    //业务不需要关心
} dsFrameEvtCBAttr;

// 终端PT值
typedef struct dsFixedPtAttr{
 u8				ptype;				//载荷类型
 dsFixedPtAttr*	next;				//业务不需要关心
} dsFixedPtAttr;

// rtp接收组类型
typedef enum {
	DS_RTP_RCVGRP_MUX         = 0x00000001,		//以下行规则的目的来匹配上行规则的源

	DS_RTP_RCVGRP_NONE	      = 0x00000000,		//无特殊
} dsRtpRcvGrpType;

// rtp规则类型 可组合使用
#define     DS_RTP_RULE_NONE		((u64)0x0000000000000000)		//无特殊
#define		DS_RULE_RTP				((u64)0x0000000000000001)		//RTP规则
#define		DS_RULE_RTCP			((u64)0x0000000000000002)		//RTCP规则
#define		DS_RULE_DOWN			((u64)0x0000000000000004)		//下行规则,在 DS_RTP_RCVGRP_MUX 类型的接收组中，该规则的目的为其他规则的源
#define		DS_RULE_UP		        ((u64)0x0000000000000008)       //上行规则,在 DS_RTP_RCVGRP_MUX 类型的接收组中，该规则的源为DS_RULE_DOWN规则的目的
#define		DS_RULE_VIDEO			((u64)0x0000000000000010)       //视频规则
#define		DS_RULE_AUDIO			((u64)0x0000000000000020)       //音频规则
#define     DS_RULE_DATA            ((u64)0x0000000000000040)       //远遥控制...


/* -------------------- 开始定义统计数据 -------------------*/
//统计数据相关定义
/* base */
//取值范围0~100的整形值, 精度为1%
typedef struct dsStatisPercent {
    u8 cur;
    u8 avg;
    u8 max;
} dsStatisPercent;

//每周期的增量
typedef struct dsStatisRate {
    u32 cur;
    u32 avg;
    u32 max;
} dsStatisRate;

/* udp */
typedef struct dsUdpPktStatis {
    u64 totalPkts;
    dsStatisRate pktRate;
    u64 totalBytes;
    dsStatisRate bytesRate;
} dsUdpPktStatis;

typedef struct dsUdpErrStatis {
    u64 totalErrCnt;

    u16 sockErrCnt;
    u16 queueErrCnt;
    u16 checksumErrCnt;
} dsUdpErrStatis;

typedef struct dsUdpDropStatis {
    u64 totalDropPkt;
    u16 dropOverSizePkt;
} dsUdpDropStatis;

typedef struct dsUdpModStatis {
    u64 totalModPkts;
    u16 addrModPkts;
} dsUdpModStatis;

typedef struct dsUdpEndpointStatis {
    dsUdpPktStatis pkt;
    
    dsUdpErrStatis errors;
    dsUdpDropStatis dropped;
    dsUdpModStatis modified;
} dsUdpEndpointStatis;

/* rtp */
typedef struct dsRtpLossStatis {
    u32 lossCnt;
    u32 expected;
    dsStatisPercent lossPercent;
} dsRtpLossStatis;

typedef struct dsRtpErrStatis {
    u64 totalErrCnt;

    u16 cipherErrCnt;
    u16 queueErrCnt;
    u16 checksumErrCnt;
} dsRtpErrStatis;

typedef struct dsRtpPktStatis {
    u16 totalFecPkt;
    u16 totalRtxPkt;
    u16 totalRedPkt;
} dsRtpPktStatis;

typedef struct dsRtpDropStatis {
    u64 totalDropPkt;
    u16 dropFecPkt;
    u16 dropRedPkt;
	u16 dropBindPkt;
    u16 dropOverSizePkt;
	u16 dropMuxInvalidAddrPkt;
} dsRtpDropStatis;

typedef struct dsRtpModStatis {
    u64 totalModPkts;
    u16 rtpRmvExtHdr;
    u16 rtpRmvId;
} dsRtpModStatis;

typedef struct dsRtpReorderStatis {
    u64 totalCnt;
} dsRtpReorderStatis;

typedef struct dsRtpJitterStatis {
    u64 totalCnt;
} dsRtpJitterStatis;

typedef struct dsRtpFlowId {
    u32 ssrc;
} dsRtpFlowId;

typedef struct dsRtpEndpointStatis {
    dsUdpEndpointStatis udpStatis;

    dsRtpFlowId idInfo;
    dsRtpPktStatis pkts;
    dsRtpLossStatis loss;

    dsRtpErrStatis errors;
    dsRtpDropStatis dropped;
    dsRtpModStatis modified;
    dsRtpReorderStatis reorder;
    dsRtpJitterStatis jitter;
} dsRtpEndpointStatis;
/* -------------------- 结束定义统计数据 -------------------*/


#define DS_INIT_RTP_ENDPOINT(endpoint)  \
    do {    \
        (endpoint)->id = DS_RTP_ANY_ID; \
        (endpoint)->ifindex = -1;   \
        (endpoint)->mediaType = DS_MEDIA_TYPE_INVALID; \
        memset(&(endpoint)->addr, 0, sizeof((endpoint)->addr));  \
		memset(&(endpoint)->attr, 0, sizeof((endpoint)->attr));  \
    } while(0)

#define DS_SYNC_BUF_LEN (256)

typedef struct dsSyncAdapterAttr {
    dsSyncAdapterType type;
    char grpId[DS_SYNC_BUF_LEN];

    dsSyncAdapterAttr *next; //业务不需要关心
} dsSyncAdapterAttr;

//设置多流同步转换属性
//请先设置ep的id和mediaType字段后调用这个接口
API u32 dsAllocEpAttrSyncAdapter(dsRtpEndpoint *ep, const dsSyncAdapterAttr * const syncAttr);

//设置目的为dump,对目的有效
API u32 dsAllocEpAttrDump(dsRtpEndpoint * dstEp);

//设置目的不转发FEC,对目的有效
API u32 dsAllocEpAttrDisFEC(dsRtpEndpoint * dstEp);

//设置目的需要修改码流,对目的有效
API u32 dsAllocEpAttrMdyRtpData(dsRtpEndpoint * dstEp);

//设置终端加密属性
API u32 dsAllocEpAttrCipher( dsRtpEndpoint * ep, const dsCipher * const cipher );

//设置终端事件通知回调,对源有效
API u32 dsAllocEpAttrFrameEvtCB( dsRtpEndpoint * srcEp, const dsFrameEvtCBAttr * const frameEvtCBAttr );

//设置终端固定SSRC,对目的有效
API u32 dsAllocEpAttrFixedSSRC( dsRtpEndpoint * dstEp);

//设置终端修改PT值,对目的有效
API u32 dsAllocEpAttrFixedPT( dsRtpEndpoint * dstEp, const dsFixedPtAttr * const fixedPt );

//设置终端过滤多倍发送的rtp包
API u32 dsAllocEpAttrFilterRED(dsRtpEndpoint * dstEp);

//释放终端属性资源
API u32 dsFreeEpAttr(dsRtpEndpoint * ep);

/****************************************************************
 * 函数: dsCreateRtpRtcpSwitch()
 * 功能: 在某个ip地址和端口创建rtpswitch
 * 参数:
 *   dsid: dataswitch 实例id
 *   addr: 要创建rtpswitch的地址和端口信息
 * 输出:
 *   返回值dsrtpswitch id，出错返回INVALID_RTPSWITCHID
 ****************************************************************/
API DSRTPSID dsCreateRtpRtcpSwitch(DSID dsid, dsNetAddr *addr, dsRtpRcvGrpType rcvGrpType = DS_RTP_RCVGRP_NONE);


/****************************************************************
 * 函数: dsAddRtpSwitchRule() / dsAddRtcpSwitchRule()
 * 功能: 在某个rtpswitch中添加rtp交换规则
 * 参数:
 *   id: rtpswitch的id，标识码流接收的ip地址和端口
 *   src: 码流的源信息，包括原ip地址和端口，原endpoint id信息等
 *        如果不包括ip地址和端口，则不尝试匹配地址和端口
 *        如果不包括endpoint id信息，则不匹配endpoint id信息
 *        如果src == NULL, 收到的所有包都匹配这个规则.
 *   modifier: 码流经过转发后修改的源信息, 如果 == NULL, 不修改
 *   dst: 码流转发到的目的信息，包括目的ip和端口，目的endpoint等
 *   priority: 规则的优先级(1~100), 越大优先级越高。
 * 输出:
 *   返回值DSOK和DSERROR.
 ****************************************************************/
API u32 dsAddRtpSwitchRule(
    DSRTPSID id,
    dsRtpEndpoint *src,
    dsRtpEndpoint *modifier,
    dsRtpEndpoint *dst,
    u32 priority);

API u32 dsAddRtcpSwitchRule(
    DSRTPSID id,
    dsRtpEndpoint *src,
    dsRtpEndpoint *modifier,
    dsRtpEndpoint *dst,
    u32 priority);

API u32 dsAddRtpRtcpSwitchRule(
    DSRTPSID id,
    dsRtpEndpoint *src,
    dsRtpEndpoint *modifier,
    dsRtpEndpoint *dst,
    u32 priority,
	u64 ruleType);
/****************************************************************
 * 函数: dsRemoveRtpSwitchRule() / dsRemoveRtcpSwitchRule()
 * 功能: 在某个rtpswitch中删除rtp交换规则
 * 参数:
 *   id: 规则所在的rtpswitch的id.
 *   src: 码流的源信息，包括原ip地址和端口，原endpoint id信息等
 *        如果src == NULL, 匹配所有源
 *   modifier: 码流经过转发后修改的源信息, 如果 == NULL, 不修改
 *   dst: 码流转发到的目的信息，包括目的ip和端口，目的endpoint等
 * 输出:
 *   返回值DSOK和DSERROR.
 ****************************************************************/
API u32 dsRemoveRtpSwitchRule(
    DSRTPSID id,
    dsRtpEndpoint *src,
    dsRtpEndpoint *modifier,
    dsRtpEndpoint *dst);

API u32 dsRemoveRtcpSwitchRule(
    DSRTPSID id,
    dsRtpEndpoint *src,
    dsRtpEndpoint *modifier,
    dsRtpEndpoint *dst);

API u32 dsRemoveRtpRtcpSwitchRule(
    DSRTPSID id,
    dsRtpEndpoint *src,
    dsRtpEndpoint *modifier,
    dsRtpEndpoint *dst,
	u64 ruleType);

/****************************************************************
 * 函数: dsDestroyRtpSwitch()
 * 功能: 清除一个rtpswitch
 * 参数:
 *   dsid: dataswitch 实例id
 *   id:   rtp switch id
 * 输出:
 *   返回值DSOK和DSERROR.
 ****************************************************************/
 API u32 dsDestroyRtpSwitch(DSID dsid, DSRTPSID id);


/*---------------- 定义rtpswitch 统计信息接口 开始 -------------------------*/
/****************************************************************
 * 函数: dsGetStatistics()
 * 功能: 获取dsid对应的RTPRTCP的转发总统计数据(所有RtpRtcpSwitch实例算一起)
 * 参数:
 *   dsid: dataswitch 实例id
 *   statisSrc: 单个rtp转发的总接收统计信息, 这个指针指向的内存块必须是有效内存块
 *   statisDst: 单个rtp转发的总发送统计信息, 这个指针指向的内存块必须是有效内存块
 * 输出:
 *   返回值DSOK和DSERROR.
 ****************************************************************/
API s32 dsGetStatistics(DSID dsid, dsRtpEndpointStatis *srcStatis, dsRtpEndpointStatis *dstStatis);

/****************************************************************
 * 函数: dsGetRtpRtcpSwitchStatistics()
 * 功能: 获取rtpswitch中某个规则的收发统计信息
 * 参数:
 *   id: rtpswitch的id，标识码流接收的ip地址和端口
 *   lclStatis[out]: 单个接收组的接收统计信息, 这个指针指向的内存块必须是有效内存块
 * 输出:
 *   返回值DSOK和DSERROR.
 ****************************************************************/
API s32 dsGetRtpRtcpSwitchStatistics(
    DSRTPSID id,
    dsRtpEndpointStatis *lclStatis,
    dsRtpEndpointStatis *dstStatis = NULL);

/****************************************************************
 * 函数: dsGetRtpSwitchRuleStatistics()
 * 功能: 获取rtpswitch中某个规则的收发统计信息
 * 参数:
 *   id: rtpswitch的id，标识码流接收的ip地址和端口
 *   epSrc[in]: dsAddRtpSwitchRule 传入的src结构
 *   epDst[in]: dsAddRtpSwitchRule 传入的dst结构
 *   statisSrc[out]: 单条规则的接收统计信息, 这个指针指向的内存块必须是有效内存块
 *   statisDst[out]: 单条规则的发送统计信息, 这个指针指向的内存块必须是有效内存块
 *   ruleType[in]: 规则类型, 复用接收组区分上下行用
 * 注意:
 *   复用模式: UP类型, 支持通配符, dstep可以传NULL, 只查询src统计
 *             DOWN类型, 不论srcEp, dstEp传入什么, 都返回src和dst
 * 输出:
 *   返回值DSOK和DSERROR.
 ****************************************************************/
API s32 dsGetRtpSwitchRuleStatistics(
    DSRTPSID id,
    dsRtpEndpoint *srcEp,
    dsRtpEndpoint *dstEp,
    dsRtpEndpointStatis *srcStatis,
    dsRtpEndpointStatis *dstStatis,
    u64 ruleType=DS_RTP_RULE_NONE);
/*---------------- 定义rtpswitch 统计信息接口 结束 -------------------------*/



/*---------------- 定义rtpswitch 结束 -------------------------*/

/*---------------- 定义sipswitch 开始 -------------------------*/
#define INVALID_SIPSWITCHID ((u32)-1)

 //为了多实例将 DSSIPSID定义改为 
/*
 *  31---------------------15-----------------------0
 *  |    DSID               | SIPID                 |
 *  -------------------------------------------------
 */
 typedef u32		DSSIPSID;

#define DS_SIP_INVALID_ID   ((u8*)0x0)

enum
{
    /* for src match */
    DS_SRC_SIP_ANY_ID = 0x0,		//转发时源不匹配任何信息
    DS_SRC_SIP_MATCH_ID = 0x1,		//转发时源必须匹配e164和callid
	DS_SRC_SIP_MATCH_STD = 0x02,	//转发时源必须匹配confid和userid

    /* for modifier action */
    DS_MOD_SIP_UNTOUCH_ID = 0x0, //转发时不修改包中的e164和callid信息
    DS_MOD_SIP_CHANGE_ID = 0x1,  //转发时修改包中的e164和callid信息
    DS_MOD_SIP_REMOVE_ID = 0x2,  //转发时去除包中的e164和callid信息

    /* for forward to destination */
    DS_DST_SIP_TO_IP = 0x0,     //转发到指定的ip地址和端口
    DS_DST_SIP_TO_ID = 0x1,     //转发到指定的e164号和callid终端
	DS_DST_SIP_TO_STD = 0x2,     //转发到指定的confid和userid终端
};

#define DS_MAX_E164_LEN     64
#define DS_MAX_CALLID_LEN   64

#define DS_SIP_INVALID_CONFID ((u32)0)
#define DS_SIP_INVALID_USERID ((u16)0)

/* sip终端的信息 */
typedef struct {
    u8 e164[DS_MAX_E164_LEN];
    u8 callId[DS_MAX_CALLID_LEN];
	u32 confId;             //Conference ID
	u16 userId;				//User ID
    u16 action;             //标识e164和callid中的信息如何使用
    s16 ifindex;            //sip 终端的上线网口
    dsNetAddr addr;         //sip 终端的网络地址
} dsSipEndpoint;

#define DS_INIT_SIP_ENDPOINT(endpoint)  \
    do {    \
        (endpoint)->action = 0x0; \
        (endpoint)->ifindex = -1;   \
		(endpoint)->confId = DS_SIP_INVALID_CONFID; \
		(endpoint)->userId = DS_SIP_INVALID_USERID; \
        memset(&((endpoint)->e164[0]), 0, sizeof((endpoint)->e164)); \
        memset(&((endpoint)->callId[0]), 0, sizeof((endpoint)->callId)); \
        memset(&(endpoint)->addr, 0, sizeof((endpoint)->addr));  \
    } while(0)

/****************************************************************
 * 函数: dsCreateSipSwitch()
 * 功能: 在某个ip地址和端口创建sipswitch
 * 参数:
 *   dsid: dataswitch 实例id
 *   addr: 要创建sipswitch的地址和端口信息
 * 输出:
 *   返回值dssipswitch id，出错返回INVALID_SIPSWITCHID
 ****************************************************************/
API DSSIPSID dsCreateSipSwitch(DSID dsid, dsNetAddr *addr);

/****************************************************************
 * 函数: dsAddSipSwitchRule()
 * 功能: 在某个sipswitch中添加sip交换规则
 * 参数:
 *   id: sipswitch的id，标识码流接收的ip地址和端口
 *   src: 码流的源信息，包括原ip地址和端口，原endpoint id信息等
 *        如果想根据源ip地址和端口转发，
 *          设置addr信息，且action为DS_SRC_SIP_ANY_ID
 *        如果想根据e164和callid信息转发，
 *          设置e164和callid，且action为DS_SRC_SIP_MATCH_ID
 *        如果src == NULL, 收到的所有包都匹配这个规则.
 *
 *   modifier: 码流经过转发后修改的源信息, 如果 == NULL, 不修改
 *         如果想修改该数据包的源ip和端口，设置addr信息
 *         如果想修改该数据包的e164和callid信息，设置e164和callid，且
 *          action设置为DS_MOD_SIP_CHANGE_ID或者DS_MOD_SIP_REMOVE_ID
 *
 *   dst: 码流转发到的目的信息，包括目的ip和端口，目的endpoint等
 *         如果目标设备的公网ip不可知，想通过nat穿越包获取，addr不填，
 *         填对应的e164和callid，后续收到nat穿越包会自动更新这个交换的地址。
 *
 *   priority: 规则的优先级(1~100), 越大优先级越高。
 * 输出:
 *   返回值DSOK和DSERROR.
 ****************************************************************/
API u32 dsAddSipSwitchRule(
    DSSIPSID id,
    dsSipEndpoint *src,
    dsSipEndpoint *modifier,
    dsSipEndpoint *dst,
    u32 priority);

/****************************************************************
 * 函数: dsRemoveSipSwitchRule()
 * 功能: 在某个sipswitch中删除sip交换规则
 * 参数:
 *   id: 规则所在的sipswitch的id.
 *   src: 码流的源信息，包括原ip地址和端口，原endpoint id信息等
 *        如果src == NULL, 匹配所有源
 *   modifier: 码流经过转发后修改的源信息, 如果 == NULL, 不修改
 *   dst: 码流转发到的目的信息，包括目的ip和端口，目的endpoint等
 * 输出:
 *   返回值DSOK和DSERROR.
 ****************************************************************/
API u32 dsRemoveSipSwitchRule(
    DSSIPSID id,
    dsSipEndpoint *src,
    dsSipEndpoint *modifier,
    dsSipEndpoint *dst);

/****************************************************************
 * 函数: dsDestroySipSwitch()
 * 功能: 清除一个sipswitch
 * 参数:
 *   dsid: dataswitch 实例id
 *   id:   sip switch id
 * 输出:
 *   返回值DSOK和DSERROR.
 ****************************************************************/
 API u32 dsDestroySipSwitch(DSID dsid, DSSIPSID id);

/*---------------- 定义sipswitch 结束 -------------------------*/

/**********************************************************
 * 函数: dsGetRecvBytesCount	                          *
 * 功能: 查询接收总字节数                                 *
 * 输入:												  *
 * 输出: 无                                               *
 * 返回: 返回即时接收字节数								  *
 **********************************************************/
API s64 dsGetRecvBytesCount( );

/**********************************************************
 * 函数: dsGetSendBytesCount	                          *
 * 功能: 查询发送总字节数                                 *
 * 输入:												  *
 * 输出: 无                                               *
 * 返回: 返回即时字节数									  *
 **********************************************************/
API s64 dsGetSendBytesCount( );

 /**********************************************************
 * 函数: DsGetUdpSocket                               *
 * 功能: 获取一个dataswitch的端口去发送数据, 提供给proxy   *
 *       client使用以解决无法使用raw socket的问题。        *
 * 输入:
 * @param dsId          - DSID
 * @param ptLocAddr     - 本地地址信息
 * 输出: 无                                               *
 * 返回: 成功返回socket 否则invalid_socket                *
 **********************************************************/
API SOCKHANDLE DsGetUdpSocket(DSID dsId, dsNetAddr *ptLocAddr);


 /**********************************************************
 * 函数: DsReleaseUdpSocket                                *
 * 功能: 释放获取到的dataswitch socket。 提供给proxy       *
 *       client使用以解决无法使用raw socket的问题。        *
 * 输入:
 * @param SOCKHANDLE          - socket
 * 输出: 无                                               *
 * 返回: 成功返回DSOK 否则DSERROR                         *
 **********************************************************/
API u32 DsReleaseUdpSocket(DSID dsId, SOCKHANDLE socket);

//DsInit ExFlag
enum
{
    DS_INIT_EXT_NONE = 0x0,             //不设置任何扩展标志
    DS_INIT_EXT_RTCP_NO_MAPIP = 0x1,    //rtcp不使用raw socket 地址伪装发送，只对非端口复用接口起作用
};

 /**********************************************************
 * 函数: DsInit                                            *
 * 功能: 初始化DsInit库,兼容以前功能,默认不设置任何扩展标志*
 * 输入:                                                   *
 * @param u32          - dwExFlag                          *
 * 输出: 无                                                *
 * 返回: 成功返回DSOK 否则DSERROR                          *
 **********************************************************/
API u32 DsInit(u32 dwExFlag = DS_INIT_EXT_NONE);

 /**********************************************************
 * 函数: dsBindRtpRule                                     *
 * 功能: 设置规则进行关联                                  *
 * 输入:                                                   *
 * srcId: rtpswitch的id，标识 绑定源 的接收的ip地址和端口  *
 * srcSrc: 绑定源的源信息                                  *
 * dstId: rtpswitch的id，标识 绑定目的 的接收的ip地址和端口*
 * dstSrc: 绑定目的的源信息                                *
 * dstModifier: 绑定目的的修改信息                         *
 * dstDst: 绑定目的的目的信息                              *
 * priority: 规则的优先级(1~100), 越大优先级越高。         *
 * 输出:                                                   *
 * 返回: 成功返回DSOK 否则DSERROR                          *
 **********************************************************/
API u32 dsBindRtpRule(DSRTPSID srcId, dsRtpEndpoint *srcSrc, DSRTPSID dstId, dsRtpEndpoint *dstSrc,
				   dsRtpEndpoint *dstModifier, dsRtpEndpoint *dstDst, u32 priority);

 /**********************************************************
 * 函数: dsRmvBindRtpRule                                  *
 * 功能: 删除关联规则                                      *
 * 输入:                                                   *
 * srcId: rtpswitch的id，标识 绑定源 的接收的ip地址和端口  *
 * srcSrc: 绑定源的源信息                                  *
 * dstId: rtpswitch的id，标识 绑定目的 的接收的ip地址和端口*
 * dstSrc: 绑定目的的源信息                                *
 * dstModifier: 绑定目的的修改信息                         *
 * dstDst: 绑定目的的目的信息                              *
 * 输出:                                                   *
 * 返回: 成功返回DSOK 否则DSERROR                          *
 **********************************************************/
API u32 dsRmvBindRtpRule(DSRTPSID srcId, dsRtpEndpoint *srcSrc, DSRTPSID dstId, dsRtpEndpoint *dstSrc,
				      dsRtpEndpoint *dstModifier, dsRtpEndpoint *dstDst);


#ifdef DATASWITCH_LEGACY_H

/**********************************************************
 * 函数: dsSpecifyFwdSrc                                  *
 * 功能: 为指定接收地址设置转发数据包所填充的源地址       *
 * 输入:
 * @param dsId          - DSID
 * @param OrigIP        - 原始IP
 * @param OrigPort      - 原始Port
 * @param MappedIP      - 映射IP
 * @param MappedPort    - 映射Port
 * 输出: 无                                               *
 * 返回: 成功返回DSOK 否则DSERROR                         *
 **********************************************************/
API u32 dsSpecifyFwdSrc(DSID dsId, u32 OrigIP, u16 OrigPort, u32 MappedIP, u16 MappedPort);

/**********************************************************
 * 函数: dsResetFwdSrc                                    *
 * 功能: 恢复指定地址转发数据包的源地址
 * 输入:
 * @param dsId          - DSID
 * @param OrigIP        - 原始IP
 * @param OrigPort      - 原始Port
 * 输出: 无                                               *
 * 返回: 成功返回DSOK 否则DSERROR                         *
 **********************************************************/
API u32 dsResetFwdSrc(DSID dsId, u32 OrigIP, u16 OrigPort);

#endif


/**********************************************************
 * 函数: dsFlush                                          *
 * 功能: 清除该实例所有交换
 * 输入:
 * @param dsId          - DSID
 * 输出: 无                                               *
 * 返回: 成功返回DSOK 否则DSERROR                         *
 **********************************************************/
API u32 dsFlush(DSID dsId);

#endif
