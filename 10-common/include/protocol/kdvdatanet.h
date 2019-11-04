//////////////////////////////////////////////////////////////////////////
///  模块名      : KdvMediaNet
///  文件名      : KdvMediaNet.h
///  相关文件    : KdvMediaNet.cpp
///  文件实现功能: KdvMediaSnd KdvMediaRcv类定义
///  作者        : 魏治兵 胡昌威
///  版本        : V2.0  Copyright(C) 2003-2005 KDC, All rights reserved.

///  修改记录:
///  日  期      版本        修改人      修改内容
///  2003/06/03  2.0         魏治兵      Create
///  2003/06/03  2.0         魏治兵      Add RTP Option
///  2004/09/25  2.0         万春雷      增加linux版本编译支持
///  2004/10/19  2.0         万春雷      加入动态载荷设置以及加密接口
///  2004/10/19  2.0         万春雷      代码整理
///  2004/10/19  3.0         万春雷      增加DES加密模式支持
///  2004/11/30  3.0         万春雷      增加AES加密模式支持
///  2004/12/02  2.0         万春雷      数据帧上报时，使用m_dwContext字段上报发送端的 源IP（网络序）
///  2004/12/02  2.0         万春雷      取消上报:数据帧上报时，使用m_dwContext字段上报发送端的 源IP（网络序）
///  2004/12/22  2.0         万春雷      数据帧上报时，帧信息结构中增加一个字段上报 发送端的源IP（网络序）
//////////////////////////////////////////////////////////////////////////


#ifndef _KDVDATANET_0302_H_
#define _KDVDATANET_0302_H_

#include "kdvtype.h"
#include "kdvcommon.h"


/// Debugging function 
PROTO_EXTERN_API void h224ver();         ///< Show the version of thie module
PROTO_EXTERN_API void h224log(u8 level); ///< Be use to control the log level
PROTO_EXTERN_API void h224rtplen();       ///< To print the rtp pack length
PROTO_EXTERN_API void h224info();        ///< The information about send session and recv session
PROTO_EXTERN_API void h224help();        ///< The help information

#define  MAXWATCHDATASOCKPORT  (u16)10599      ///< max watchsock port
#define  MINWATCHDATASOCKPORT  (u16)10500      ///< min watchsock port

#define  DATA_PINHOLE_INTERVAL		10         //10s, The time interval of pinhole,defult value is ten second

/// The error number
#define  DATANET_NO_ERROR                   (u16)0                   ///< no error 
#define  ERROR_SND_FRAME                    (s32)-1;                 ///< error send frame
#define  ERROR_DATA_NET_BASE                (u16)16000               ///< the error base of data net
#define  ERROR_SND_PARAM		            (ERROR_DATA_NET_BASE+1)  ///< the param of send error 
#define  ERROR_SND_NOCREATE		            (ERROR_DATA_NET_BASE+2)  ///< the rtp module of send not be created 
#define  ERROR_SND_MEMORY		            (ERROR_DATA_NET_BASE+3)  ///< the memory of send module error
#define  ERROR_SND_CREATE_SOCK		        (ERROR_DATA_NET_BASE+4)  ///< creating socket of send error
#define  ERROR_RTP_SSRC                     (ERROR_DATA_NET_BASE+5)  ///< the SSRC of RTP error
#define  ERROR_LOOPBUF_CREATE               (ERROR_DATA_NET_BASE+6)  ///< 环状缓冲创建错误  
#define  ERROR_RTP_NO_INIT                  (ERROR_DATA_NET_BASE+7)  ///< RTP类有些对象没创建
#define  ERROR_RTCP_NO_INIT                 (ERROR_DATA_NET_BASE+8)  ///< RTCP类有些对象没创建
#define  ERROR_RTCP_SET_TIMER               (ERROR_DATA_NET_BASE+9)  ///< RTCP设置定时器出错
#define  ERROR_RTP_SSRC_COLLISION           (ERROR_DATA_NET_BASE+10) ///< RTP 同步源出错
#define  ERROR_SOCK_INIT                    (ERROR_DATA_NET_BASE+11) ///< socket 没有初始化
#define  ERROR_H261_PACK_NUM                (ERROR_DATA_NET_BASE+12) ///< H261的包数不合理
#define  ERROR_PACK_TOO_LEN                 (ERROR_DATA_NET_BASE+13) ///< 数据包太长
#define  ERROR_H263_PACK_NUM                (ERROR_DATA_NET_BASE+14) ///< H263的包数不合理
#define  ERROR_H263_PACK_TOOMUCH            (ERROR_DATA_NET_BASE+15) ///< H263的数据包太长

#define  ERROR_NET_RCV_PARAM                (ERROR_DATA_NET_BASE+100)///< 设置接收模块参数出错
#define  ERROR_NET_RCV_NOCREATE             (ERROR_DATA_NET_BASE+101)///< 接收模块没有创建
#define  ERROR_NET_RCV_MEMORY               (ERROR_DATA_NET_BASE+102)///< 接收模块内存操作出错
#define  ERROR_RCV_RTP_CREATE               (ERROR_DATA_NET_BASE+103)///< 接收模块RTP创建失败
#define  ERROR_RCV_RTP_CALLBACK             (ERROR_DATA_NET_BASE+104)///< 接收模块设置RTP回调函数失败
#define  ERROR_RCV_RTP_SETREMOTEADDR        (ERROR_DATA_NET_BASE+105)///< 接收模块设置RTP远端地址失败
#define  ERROR_CREATE_LOOP_BUF              (ERROR_DATA_NET_BASE+106)///< 创建环状缓冲失败
#define  ERROR_RCV_NO_CREATE                (ERROR_DATA_NET_BASE+107)///< 接收模块接收对象没有创建
																	 
#define  ERROR_WSA_STARTUP                  (ERROR_DATA_NET_BASE+200)///< wsastartup error
#define  ERROR_CREATE_SEMAPORE              (ERROR_DATA_NET_BASE+201)///< create semapore error
#define  ERROR_SOCKET_CALL                  (ERROR_DATA_NET_BASE+202)///< 调用socket() 函数出错
#define  ERROR_BIND_SOCKET                  (ERROR_DATA_NET_BASE+203)///< socket 绑定出错
#define  ERROR_CREATE_THREAD                (ERROR_DATA_NET_BASE+204)///< 创建线程出错 
#define  ERROR_LOOPBUF_FULL                 (ERROR_DATA_NET_BASE+205)///< 循环缓冲满

#define  ERROR_SET_DECRYPTKEY               (ERROR_DATA_NET_BASE+210)///< 设置解密key失败
#define  ERROR_DECRYPT_FRAME                (ERROR_DATA_NET_BASE+212)///< 解密一帧失败
#define  ERROR_SET_ENCRYPTKEY               (ERROR_DATA_NET_BASE+213)///< 设置加密key失败
#define  ERROR_ENCRYPT_FRAME                (ERROR_DATA_NET_BASE+215)///< 加密一帧失败

/// about encrypt 
#ifndef DES_ENCRYPT_MODE
#define DES_ENCRYPT_MODE         (u8)0      ///< DES加密模式
#define AES_ENCRYPT_MODE         (u8)1      ///< AES加密模式
#define ENCRYPT_KEY_SIZE         (u8)32     ///< 密钥长度 取其中的较大值
#define DES_ENCRYPT_KEY_SIZE     (u8)8      ///< DES密钥长度
#define AES_ENCRYPT_KEY_SIZE_MODE_A (u8)16  ///< AES Mode-A 密钥长度
#define AES_ENCRYPT_KEY_SIZE_MODE_B (u8)24  ///< AES Mode-B 密钥长度
#define AES_ENCRYPT_KEY_SIZE_MODE_C (u8)32  ///< AES Mode-C 密钥长度
#endif

#ifndef  MAX_NETSND_DEST_NUM
	#define  MAX_NETSND_DEST_NUM   5    ///< maximum number of send destination
#endif

/////////////////////////////////////////////////FECC////////////////////////////////////////////////
#define MAX_FECC_LEN 256               ///< maximum length of fecc message

/// H323 Annex Q
/*   
 *   h.281 encoded in host bit order:
 *   +-------+---------+--------+---------+--------+---------+--------+---------+
 *   +   P   | R=1/L=0 |    T   | U=1/D=0 |    Z   | I=1/O=0 |    F   | I=1/O=0 |
 *   +-------+---------+--------+---------+--------+---------+--------+---------+
 */
/// The enum of fecc action
enum EmFeccAction
{
	emActionInvalid					= 0,     ///< invalid action
	emActionStart					= 0x01,  ///< 开始
	emActionContinue				= 0x02,  ///< 继续
	emActionStop					= 0x03,  ///< 停止
	emActionSelectVideoSource		= 0x04,  ///< 选择视频源
	emActionVideoSourceSwitched		= 0x05,  ///< 切换视频源
	emActionStoreAsPreset			= 0x06,  ///< 存储预置位
	emActionActivatePreset			= 0x07,  ///< 恢复到预置位
	emActionAutoFocus				= 0x11,  ///< 自动调焦
};

/// PTFZ codes, parameters for action Start, continue and stop.
enum EmFeccPTFZRequest
{
	emRequestInvalid			= 0,    ///< invalid request
	emRequestPanLeft			= 0x80,	///< 向左移动
	emRequestPanRight			= 0xc0,	///< 向右移动
	emRequestTiltUp			    = 0x30,	///< 向上移动
	emRequestTiltDown			= 0x20,	///< 向下移动
	emRequestFocusIn			= 0x03,	///< 近焦
	emRequestFocusOut			= 0x02,	///< 远焦	
	emRequestZoomIn				= 0x0c,	///< 视野变小
	emRequestZoomOut			= 0x08,	///< 视野变大										
	emRequestBrightnessUp		= 0x01,	///< 亮度加(nonstandard)
	emRequestBrightnessDown		= 0x04  ///< 亮度减(nonstandard)
};										

/// 远遥模块返回值类型
typedef enum
{
	annexQNotInited				= -20,  ///< not inited
	annexQBindError				= -15,	///< bind error
	annexQParamError			= -14,	///< param error
	annexQLockError				= -12,	///< lock error
	annexQCodingError			= -10,	///< coding error
	annexQSendError				= -9, 	///< send error
	annexQGeneralError			= -5, 	///< general error
	annexQOk					= 1	  	///< success
}annexQResult;

/// enum EmFeccVideoSourceNumber, for tanderg
enum EmFeccVideoSourceNumber
{
	emVideoSourceDefault               = 0,    ///< 当前视频源
	emVideoSourceMainCamera            = 1,    ///< 主视频源
	emVideoSourceAuxCamera             = 2,    ///< 辅助视频源
	emVideoSourceDocCamera             = 3,    ///< 文件展示台
	emVideoSourceAuxDocCamera          = 4,    ///< 辅助文件展示台，对于泰德为vcr
	emVideoSourceVideoPlaybackSource   = 5,    ///< vcr，对于泰德为PC
};

/// CME message type
enum EmCMEMsgType
{
	CMEInvalid,				///< 无效
	CMEClientListInfo,		///< 客户列表消息通知
	CMEClientListCommond,	///< 请求客户列表
	CMEExtraCapInfo,		///< 额外能力信息通知
	CMEExtraCapCommond,		///< 请求额外能力

};

/// H323 Annex Q. the struct of fecc message
typedef struct PROTO_API tagFeccStruct
{
	BOOL32 m_bIsCMEMsg;		  ///<  if this message is a CME message  

	u8	m_byCMEMsgType;		  ///< ClientListInfo/Commond,ExtraCapInfo/Commond

	u8 m_byAction;			  ///< start, continue, stop, video source, preset	
	union
	{
		u8 m_byRequest;		  ///< for PTFZ operations
		u8 m_bySourceNo;      ///< for VIDEO SOURCE operations
		u8 m_byPresetNo;      ///< for PRESET operations
	}arguments;	
	u8 m_byTimeout;			  ///< for start action only ,unit 50ms, 0表示800ms
public:
	tagFeccStruct()
	{
		m_bIsCMEMsg		= FALSE;
		m_byCMEMsgType	= CMEInvalid;
		m_byAction		= emActionInvalid;
		arguments.m_byRequest = 0;	
		m_byTimeout		= 0;
	}
}TFeccStruct, *PTFeccStruct;


#define FECC_ENDPOINTID_LEN 32 ///< 端口复用时需要设置streamId。

/// the stread id information
typedef struct PROTO_API tagFeccStreamIdInfo
{
	s8  aszEndPointId[FECC_ENDPOINTID_LEN];	///< 终端的id, 当前仅支持e164号
	u32 IdLen;				                ///< 终端id的长度
	u32 StreamId;			                ///< 流id
	BOOL32 bSendChan;		                ///< 是否是远遥发送通道

public:
	tagFeccStreamIdInfo()
	{
		memset(aszEndPointId, 0, FECC_ENDPOINTID_LEN);
	}
}TFeccStreamIdInfo;


/**          
* \brief            kdvAnnexQInit, 远遥模块初始化
* \param[in]        dwMaxFeccChannels      :最大FECC通道数
* \param[in]		nDataPinhleAppID       :打洞app的id,默认值是APPID_DATANET_PINHOLE	
* \param[in]		nMinPort			   :创建watchdog socket最小端口号
* \param[in]		nMaxPort			   :创建watchdog socket最大端口号
* \return           annexQOk if succeed, or other if fails
*/
PROTO_EXTERN_API s32 kdvAnnexQInit(u32 dwMaxFeccChannels, s32 nDataPinhleAppID=APPID_DATANET_PINHOLE, u16 dwMinPort=MINWATCHDATASOCKPORT, u16 dwMaxPort=MAXWATCHDATASOCKPORT);

/**
* \brief       kdvAnnexQEnd,关闭远遥功能
*/
PROTO_EXTERN_API void kdvAnnexQEnd();

/**
* \brief            NotifyFeccMsg,H.224, H.281功能回调函数
* \param[in]        pContext         :每个FECC通道的唯一标识，例如信道句柄
* \param[in]		tFeccStruct      :远遥命令(TFeccStruct)
* \param[in]		terSrc     	     :源端终端列表
* \param[in]		terDst     	     :源端终端列表
* \return           annexQOK:success, annexQParamError:failed
*/
typedef s32 (PROTO_CALLBACK *NotifyFeccMsg)(MemId pContext,  TFeccStruct tFeccStruct, TTERLABEL terSrc, TTERLABEL terDst);

/**
* \brief            kdvSetFeccCallBack,注册应用回调函数(针对所有通道设置一次，回调指针全局保存)
* \note             平台使用此函数设置回调
* \param[in]        pNotifyFeccMsg         :回调函数结构指针
* \return           annexQOK:success, annexQParamError:failed
*/
PROTO_API s32  kdvSetFeccCallBack(IN NotifyFeccMsg pNotifyFeccMsg);

/**
* \brief            kdvSetFeccChanCallBack,注册应用回调函数(针对每个通道设置一次，回调指针保存在每个通道信息中)
* \param[in]        pContext               :每个FECC通道的唯一标识，例如信道句柄
* \param[in]        pNotifyFeccMsg         :回调函数结构指针
* \return           annexQOK:success, annexQParamError:failed
*/
PROTO_API s32  kdvSetFeccChanCallBack( IN MemId pContext, IN NotifyFeccMsg pNotifyFeccMsg);

/**
* \brief            kdvAnnexQInitSendSession,远遥信道发送命令初始化
* \note             only for ipv4
* \param[in]        pContext            :每个FECC通道的唯一标识，例如信道句柄
* \param[in]        dwRemoteIp          :发送通道关联的对端的IP地址
* \param[in]        dwRemotePort        :发送通道关联的对端的端口号
* \return           annexQOK:success, annexQParamError:failed
*/
PROTO_API s32 kdvAnnexQInitSendSession(IN MemId pContext, IN u32 dwRemoteIp, IN u16 dwRemotePort);

/**
* \brief            kdvAnnexQInitSendSession,远遥信道发送命令初始化
* \note             for ipv4 and ipv6
* \param[in]        pContext            :每个FECC通道的唯一标识，例如信道句柄
* \param[in]        tRemoteAddress      :发送通道关联的对端的地址
* \return           annexQOK:success, annexQParamError:failed
*/
PROTO_API s32 kdvAnnexQInitSendSession(IN MemId pContext, IN PFC_IPADDR tRemoteAddress);

/**
* \brief            kdvAnnexQNewSendSession,发送远遥命令
* \note             only for ipv4
* \param[in]        pContext            :每个FECC通道的唯一标识，例如信道句柄
* \param[in]        dwLocalIp           :发送通道的ip
* \param[in]        wLocalPort          :发送通道的port
* \param[in]        bSip                :是否是sip的远摇信令
* \return           annexQOk if succeed, or annexQGeneralError if fails
*/
PROTO_API s32 kdvAnnexQNewSendSession(IN MemId pContext, IN u32 dwLocalIp, IN u16 wLocalPort, IN BOOL32 bSip=FALSE);

/**
* \brief            kdvAnnexQNewSendSession,发送远遥命令
* \note             for ipv4 and ipv6
* \param[in]        pContext            :每个FECC通道的唯一标识，例如信道句柄
* \param[in]        tLocalAddress       :发送通道的本地地址
* \param[in]        bSip                :是否是sip的远摇信令
* \return           annexQOk if succeed, or annexQGeneralError if fails
*/
PROTO_API s32 kdvAnnexQNewSendSession(IN MemId pContext, IN PFC_IPADDR tLocalAddress, IN BOOL32 bSip=FALSE);

/**
* \brief            kdvAnnexQDeleteSendSession,删除发送远遥数据的信道
* \param[in]        pContext          :每个FECC通道的唯一标识，例如信道句柄			  
* \return           annexQOk if succeed, or annexQGeneralError if fails
*/
PROTO_API s32 kdvAnnexQDeleteSendSession(IN MemId pContext);

/**
* \brief            kdvAnnexQNewRecvSession,接受远遥数据的信道
* \note             only for ipv4
* \param[in]        pContext           :每个FECC通道的唯一标识，例如信道句柄
* \param[in]        dwLocalIp	       :接收通道的本地IP地址
* \param[in]        wLocalPort         :端口号			  
* \param[in]        bSip               :是否是sip的远摇信令
* \return           annexQOk if succeed, or annexQGeneralError if fails
*/
PROTO_API s32 kdvAnnexQNewRecvSession(IN MemId pContext, IN u32 dwLocalIp, IN u16 wLocalPort, IN BOOL32 bSip=FALSE);

/**
* \brief            kdvAnnexQNewRecvSession,接受远遥数据的信道
* \note             for ipv4 and ipv6
* \param[in]        pContext           :每个FECC通道的唯一标识，例如信道句柄
* \param[in]        tLocalAddress	   :接收通道本地地址			  
* \param[in]        bSip               :是否是sip的远摇信令
* \return           annexQOk if succeed, or annexQGeneralError if fails
*/
PROTO_API s32 kdvAnnexQNewRecvSession(IN MemId pContext, IN PFC_IPADDR tLocalAddress, IN BOOL32 bSip=FALSE);

/**
* \brief            kdvAnnexQDeleteRecvSession,删除接受远遥数据的信道
* \param[in]        pContext          :每个FECC通道的唯一标识，例如信道句柄 			  
* \return           annexQOk if succeed, or annexQGeneralError if fails
*/
PROTO_API s32 kdvAnnexQDeleteRecvSession(IN MemId pContext); 

/**
* \brief            kdvAnnexQSetEncryptSendSession,设置发送远遥数据信道的加密信息
* \param[in]        pContext			:每个FECC通道的唯一标识，例如信道句柄 
* \param[in]        ptEncryptSync		:加密信息(TEncryptSync)			  
* \return           annexQOk if succeed, or annexQGeneralError if fails
*/
PROTO_API s32 kdvAnnexQSetEncryptSendSession(IN MemId pContext, IN TEncryptSync *ptEncryptSync);

/**
* \brief            kdvAnnexQSetDecryptRecvSession,设置接收远遥数据信道的加密信息
* \param[in]        pContext			:每个FECC通道的唯一标识，例如信道句柄 
* \param[in]        ptEncryptSync		:加密信息(TEncryptSync)			  
* \return           annexQOk if succeed, or annexQGeneralError if fails
*/
PROTO_API s32 kdvAnnexQSetDecryptRecvSession(IN MemId pContext, IN TEncryptSync *ptEncryptSync);


/**
* \brief            kdvFeccBind,多点会议中绑定远遥对象，点对点呼叫时无需绑定
* \param[in]        pContext          :每个FECC通道的唯一标识，例如信道句柄
* \param[in]        localTer          :本地终端列表(TTERLABEL)
* \param[in]        remoteTer	      :远端终端列表(TTERLABEL)
* \return           annexQOk if succeed, or annexQGeneralError if fails
*/
PROTO_API s32 kdvFeccBind(IN MemId pContext, IN TTERLABEL localTer, IN TTERLABEL remoteTer, IN BOOL32 bSync = TRUE);

/**
* \brief            kdvSendFeccMsg,通过h224通道发送远遥命令
* \param[in]        pContext	      :每个FECC通道的唯一标识，例如信道句柄
* \param[in]        feccStruct	      :远遥命令(TFeccStruct)
* \return           annexQOk if succeed, or annexQGeneralError if fails
*/
PROTO_API s32 kdvSendFeccMsg(IN MemId pContext, IN TFeccStruct tFeccStruct, IN BOOL32 bSync = TRUE);

/**
* \brief            kdvAnnexQSetStreamId,端口复用时设置远遥码流id
* \param[in]        pContext           :每个FECC通道的唯一标识，例如信道句柄
* \param[in]        EndPointId         :终端的id, 当前仅支持e164号
* \param[in]        IdLen       	   :终端id的长度
* \param[in]        StreamId           :流id
* \param[in]        bSendChan		   :是否是远遥发送通道
* \return           annexQOk if succeed, or annexQGeneralError if fails
*/
PROTO_API s32 kdvFeccSetStreamId(IN MemId pContext, TFeccStreamIdInfo tFeccStreamIdInfo, IN BOOL32 bSync = TRUE);

/**
* \brief             kdvAnnexQSetKeepAliveAddress,启用h460的远遥打洞
* \note              only for ipv4
* \param[in]         pContext           :每个FECC通道的唯一标识，例如信道句柄
* \param[in]         dwLocalIp          :KeepAlive通道的ip
* \param[in]         wLocalPort  	    :KeepAlive通道的port
* \param[in]         dwInterval         :KeepAlive通道的打洞时间间隔
* \return            annexQOk if succeed, or annexQGeneralError if fails
*/
PROTO_API s32 kdvAnnexQSetKeepAliveAddress(IN MemId pContext, IN u32 dwKeepAliveIp, IN u16 wKeepAlivePort, IN s32 nInterval=0, IN BOOL32 bSync = TRUE);

/**
* \brief             kdvAnnexQSetKeepAliveAddress,启用h460的远遥打洞
* \note              for ipv4 and ipv6
* \param[in]         pContext           :每个FECC通道的唯一标识，例如信道句柄
* \param[in]         tKeepAliveAddr     :KeepAlive通道的地址
* \param[in]         dwInterval         :KeepAlive通道的打洞时间间隔
* \return            annexQOk if succeed, or annexQGeneralError if fails
*/
PROTO_API s32 kdvAnnexQSetKeepAliveAddress(IN MemId pContext, IN PFC_IPADDR tKeepAliveAddr, IN s32 nInterval=0, IN BOOL32 bSync = TRUE);

#ifdef _KDV_SRTP_SUPPORT_
/**
* \brief            kdvFeccSetSrtp,设置远摇通道的srtp内容
* \param[in]        pContext            :每个FECC通道的唯一标识，例如信道句柄
* \param[in]        bSend  	     	    :通道方向，TRUE为发送通道，FALSE为接收通道
* \param[in]        tSrtpCrypto         :srtp相关信息	      
* \return           annexQOk if succeed, or annexQGeneralError if fails
*/
PROTO_API s32 kdvFeccSetSrtp(IN MemId pContext, IN BOOL32 bSend, IN TMediaSrtpCrypto tSrtpCrypto, IN BOOL32 bSync=TRUE); 
#endif

/**
* \brief            kdvSetDataTOS,set the TOS value
* \param[in]        nTOS	      :the tos value which want to be set
* \return           nTOS
*/
PROTO_API s32 kdvSetDataTOS(s32 nTOS);  

/**
* \brief            kdvGetDataTOS,get the TOS value
* \return           g_st_nDatanetTOS
*/
PROTO_API s32 kdvGetDataTOS();         


/// Frame Header Structure
typedef struct tagH224Data
{
    u8     *m_pData;       ///< 数据缓冲
    u32     m_dwDataSize;  ///< m_pData指向的实际缓冲大小缓冲大小
}TH224Data,*PTH224Data;

/// the h224 session,be used to create and extract fecc message
typedef struct PROTO_API tagH224Session
{
public:
	TTERLABEL	m_tSrcLabel;  ///< the source label
	TTERLABEL	m_tDstLabel;  ///< the destination label
	BOOL32      m_bSip;       ///< sip和323的远摇信令区别：sip无界标记、字节序不反转、不带校验和、不做插0处理

public:
	tagH224Session()
	{	
		Clear();
	}
	~tagH224Session()
	{        
        Clear();
	}

	void Clear()
	{
		m_tSrcLabel.Clear();
		m_tDstLabel.Clear();
		m_bSip = FALSE;
	}

	/**
	* \brief            FeccBind,生成FECC的消息，多点会议中绑定远遥对象，点对点呼叫时无需绑定
	* \param[in]        tSrcLabel	  	    :本地终端列表(TTERLABEL)
	* \param[in]        tDstLabel           :远端终端列表(TTERLABEL)       
	* \return           annexQOk if succeed, or annexQGeneralError if fails
	*/
    void FeccBind(IN TTERLABEL tSrcLabel, IN TTERLABEL tDstLabel );

/**
* \brief            kdvCreateFeccMsg,生成FECC的消息，由TFeccStruct-->TH224Data
* \param[in]        FeccStruct	  	    :业务使用的远遥信息结构体TFeccStruct
* \param[out]       tDataHdr            :FECC的信息，RTP数据部分       
* \return           annexQOk if succeed, or annexQGeneralError if fails
*/
	BOOL32  kdvCreateFeccMsg( IN TFeccStruct &tFeccStruct, OUT TH224Data &tDataHdr);

/**
* \brief             kdvExtractFeccMsg,解析FECC消息，由TH224Data-->TFeccStruct
* \param[out]        tFeccStruct  	    :业务使用的远遥信息结构体TFeccStruct
* \param[in]         TH224Data	        :FECC的信息，RTP数据部分
* \return            annexQOk if succeed, or annexQGeneralError if fails
*/
	BOOL32  kdvExtractFeccMsg( OUT TFeccStruct &tFeccStruct, IN const TH224Data &tDataHdr);

private:
    u16 PackH224Payload(IN u8* h224Buf,  IN u16 h224Len, OUT u8* rawData, IN u32 rawBufLen);
	u32 ExtractH224Payload(IN u8* rawData, IN u32 rawLen, OUT u8* h224Buf, IN u16 h224BufLen);
	u16 GenCRC16Code( u8 *pbyBuff, u16 wBuffLen );
 	
}TH224Session;
  

#endif //_KDVDATANET_0302_H_

