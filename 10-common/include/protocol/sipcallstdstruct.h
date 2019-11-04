///  All right reserved
///  
///  @file        sipcallstdstruct.h 
///  @author      zgf
///  @version     1.0
///  @date        2018-3-1
///  @brief       sipcallstdstruct
///  @details     sipcallstdstruct interfaces describe here what it is all about.
//////////////////////////////////////////////////////////////////////////

/************************************************************************/
/*  Start of sipcallstdstruct                                        */
/************************************************************************/

/**
 * @defgroup    sipcallstdstruct
 * @brief       sipcallstdstruct interfaces describe here what it is all about.
 * @{
 */
#ifndef _SIPCALLSTDSTRUCT_H
#define _SIPCALLSTDSTRUCT_H

#include "kdvcapset.h"
#include "kdvsipcommon.h"
#include "kdvdatanet.h"
#include "kdvsiphandle.h"
#include "sipconfnonstdmsg.h"

/// is valid host name address
#define IsValidHostNameAddr( hostname ) TRUE

#define MAX_MIX_EP_LIST_LEN                 64 ///< max mt count in list

/// sip tsx timeout
typedef struct tagSipTsxTimeout
{          
	u32 m_dwTsxTimer1;  ///< Transaction T1 timeout, in msec. Default value is PJSIP_T1_TIMEOUT 
	
	u32 m_dwTsxTimer2;  ///< Transaction T2 timeout, in msec. Default value is PJSIP_T2_TIMEOUT 
	
	u32 m_dwTsxTimer4;  ///< Transaction completed timer for non-INVITE, in msec. Default value is PJSIP_T4_TIMEOUT 
	
	u32 m_dwTsxTimerTD; ///< Transaction completed timer for INVITE, in msec. Default value is PJSIP_TD_TIMEOUT. 

	/**
    * \brief            tagSipTsxTimeout Constructor
    * \return           void.
    */
	tagSipTsxTimeout()
	{
		Clear();
	}
	/**
    * \brief            tagSipTsxTimeout init
    * \return           void.
    */
	void Clear()
	{
		m_dwTsxTimer1 = 500;	
		m_dwTsxTimer2 = 4000;	
		m_dwTsxTimer4 = 5000;	
		m_dwTsxTimerTD= 32000;	
	}
}TSipTsxTimeout;

typedef struct tagAdapterLogCfg
{
	s8 m_achLogPath[LOG_LOGPATH_LENGTH];			///< pfc log path
	u32 m_dwMaxSize;								//pfc log  size(KB)
	u32 m_dwMaxfiles;								//pfc file number
	tagAdapterLogCfg()
	{
		clear();
	}
	void clear()
	{
		MEMSET_CAST(m_achLogPath, 0, LOG_LOGPATH_LENGTH);
		m_dwMaxSize = 0;
		m_dwMaxfiles = 0;
	}
}TAdapterLogCfg;

/// sipadpater config
typedef struct tagSipAdapterCfg
{
	emEndpointType	m_emEndpointType;           ///< endpoint type
	BOOL32  m_bIfRegister;                      ///< if register 
	u32     m_dwMaxCalls;			            ///< 最大呼叫数


	PFC_IPADDR m_tLocalAddrV4;                  ///for ipv4,tcp and udp
	PFC_IPADDR m_tLocalAddrV6;                  ///for ipv6,tcp and udp

	BOOL32  m_bManualAck;                       ///< manual ack
	u16     m_wRegClientNum;                    ///< reg client number
	u32     m_dwMaxSendReciveBufferSize;        ///< mx send and recv buffer size
	s8      m_achProduct[MAX_PRODUCTID_LEN];	///< 产品信息
	s8      m_achTerVer[MAX_PRODUCTID_LEN];		///< 版本信息
	u16		m_wPortRangeStart;                  ///< tcp or tls port range must be assigned by business, or random allocation
	u16		m_wPortRangeEnd;                    ///< range end

	BOOL32	m_bIsh460GW;			            ///< 默认值FALSE,5.0gk应设置此值为TRUE,则adapter中就不会有kdvdatanet的调用
	TSipTsxTimeout m_tTsxTimeout;               ///< tsx time out struct

	BOOL32	m_bUseTLS;                          ///< 是否启用TLS监听
	TTlsCfg m_tTlsCfg;                          ///< tls config

	BOOL32 m_bUseTLSDefConfig;	                ///< 是否启用TLS Default Config
	BOOL32  m_bUseIpv6;							///< is use ipv6
	u32     m_dwLocalIP;						///< 本端地址.网络序
	ALL_LOG_CALlBACK  m_fpLogCB;				///< add callback function for print
	TAdapterLogCfg m_tSipLog;                   ///< Let the business set the PfcOpenLogFile parameters
public:
	/**
    * \brief            tagSipAdapterCfg Constructor
    * \return           void.
    */
	tagSipAdapterCfg()
	{
		Clear();
		m_wPortRangeStart = KDV_PORTRANGE_DEFAULT_START;
		m_wPortRangeEnd	  = KDV_PORTRANGE_DEFAULT_FINISH;
		m_tTsxTimeout.Clear();
	}
	/**
    * \brief            tagSipAdapterCfg init
    * \return           void.
    */
	void Clear()
	{
		memset(this , 0 , sizeof(tagSipAdapterCfg) );
		m_emEndpointType			= emEndpointTypeUnknown;
		m_wRegClientNum				= 2;
		m_dwMaxSendReciveBufferSize = 20480;
		m_bIsh460GW					= FALSE;
		m_bUseTLS                   = FALSE;
		m_bUseTLSDefConfig          = FALSE;
		m_bUseIpv6                = TRUE;
		m_tTlsCfg.Clear();
		m_tLocalAddrV4.Clear();
		m_tLocalAddrV4.m_emType     = PFC_TRANSPORT_TYPE_IP;
		m_tLocalAddrV6.Clear();
		m_tLocalAddrV6.m_emType     = PFC_TRANSPORT_TYPE_IPV6;
		m_fpLogCB = NULL;
		m_tSipLog.clear();
	}
}TSipAdapterCfg;



/// stack init result
typedef struct tagStackInitRes
{
	TSipAdapterCfg tSipAdapterCfg;  ///< sipadapter config
	BOOL32 bSuc;                    ///< is successful
	/**
    * \brief            tagStackInitRes Constructor
    * \return           void.
    */
	tagStackInitRes()
	{
		memset((void*)&tSipAdapterCfg, 0, sizeof(tSipAdapterCfg));
		bSuc = TRUE;
	}
}TStackInitRes;

/// sipadapter callback
typedef struct tagSipAdapterCB
{
	/**
	* \brief            new call notify
	* \param[in]        haCall        :upper call handle
	* \param[in]        hsCall        :lower call handle
	* \param[in]        pBuf          :null
	* \param[in]        dwBufLen      :0
	* \return           BOOL32, TRUE/FALSE
	*/
	s32 (PROTO_CALLBACK* cbNotifyNewCall)(s32 haCall, s32 hsCall, const void *pBuf, u32 dwBufLen);

	/**
	* \brief            Notify Call Ctrl Msg
	* \param[in]        haCall        :upper call handle
	* \param[in]        hsCall        :lower call handle
	* \param[in]        wMsgType      :h_call_capsetnotify,h_call_connected,h_call_disconnected,h_call_callidnotify\n
	* \param[in]        pBuf          :h_call_capsetnotify - CSipCapSet + u8(u8可以没有,根据dwBufLen判断)\n
	                                   h_call_connected - TSipCallParam\n
                                              h_call_incoming - TSipCallParam + s32(nViaCount) + ( u8(TpType) + TSipHostAddress ) * nViaCount \n
	                                   h_call_disconnected - 呼叫挂断原因(u8)+sip包头Call-ID字符串(only mcu need callid)\n
	                                   h_call_callidnotify - sip包头Call-ID字符串
	* \param[in]        dwBufLen      :buffer length
	* \return           BOOL32, TRUE/FALSE
	*/
	s32 (PROTO_CALLBACK* cbNotifyCallCtrlMsg)(s32 haCall, s32 hsCall,u16 wMsgType, const void *pBuf,u32 dwBufLen);

	/**
	* \brief            会议控制请求函数(uas)
	* \param[in]        haCall        :upper call handle
	* \param[in]        hsCall        :lower call handle
	* \param[in]        pHandle       :stack handle
	* \param[in]        pBuf          :sip信令类型(EmSipArbitraryMsgType) + 是否存在非标包头(BOOL32) + 非标包头个数(u8) 
	                                   + 非标包头有效值(非标包头个数 * sizeof(TSipHead)) + 包体长度(u32) + 包体内容(From、To、Via)
	* \param[in]        dwBufLen      :buffer length
	* \return           BOOL32, TRUE/FALSE
	*/
	s32 (PROTO_CALLBACK* cbNotifyConfCtrlReqMsg)(s32 haCall, s32 hsCall, TSipUasHandle pHandle, const void *pBuf, u32 dwBufLen);

	/**
	* \brief            会议控制应答函数(uac)
	* \param[in]        haCall        :upper call handle
	* \param[in]        hsCall        :lower call handle
	* \param[in]        pHandle       :stack handle
	* \param[in]        pBuf          :buffer
	* \param[in]        dwBufLen      :buffer length
	                    dwBufLen                        pBuf的内容：
						sizeof(EmSipArbitraryMsgType)   --ArbitraryMsgType
						+ sizeof(BOOL32)                --bHaveNonStdHdr
						+ sizeof(u8);                   --byNonStdHdr非标头个数
						+ NonStdHdrBody                 --byNonStdHdr* sizeof(TSipHead) 非标头
						+ sizeof(u32)                   --dwBodyLen
						+ dwBodyLen                     --ptPjBody->data，如果有body的话会带。
						+ sizeof(s32)                   --nStatusCode
						+ sizeof(TUriSip)               --tUriFrom
						+ sizeof(TUriSip)               --tUriTo
						+ sizeof(TUriSip)               --tUriVia
						+ sizeof(u32)                   --dwStatusReasonLen
						+ dwStatusReasonLen             --status.reason.ptr
	* \return           BOOL32, TRUE/FALSE
	*/
	s32 (PROTO_CALLBACK* cbNotifyConfCtrlRspMsg)(s32 haCall, s32 hsCall, TSipUacHandle pHandle, const void *pBuf, u32 dwBufLen);

	/**
	* \brief            注册控制通知函数(uas)
	* \param[in]        pHandle       :stack handle
	* \param[in]        pBuf          :TRegReqInfo
	* \param[in]        dwBufLen      :buffer length
	* \return           BOOL32, TRUE/FALSE
	*/
	s32 (PROTO_CALLBACK* cbNotifyRegCtrlReqMsg)(TSipUasHandle pHandle, const void *pBuf, u32 dwBufLen);

	/**
	* \brief            注册控制通知函数(uac)
	* \param[in]        haReg         :upper reg handle
	* \param[in]        hsReg         :lower reg handle
	* \param[in]        wMsgType      :h_sip_state2failed,h_sip_state2registered
	* \param[in]        pBuf          :h_sip_state2failed - 错误码(s32)\n
	                                   h_sip_state2registered - via中receive ip（u32）\n
	                                   其他情况为NULL
	* \param[in]        dwBufLen      :buffer length
	* \return           BOOL32, TRUE/FALSE
	*/
	s32 (PROTO_CALLBACK* cbNotifyRegCtrlRspMsg)(s32 haReg, s32 hsReg, u16 wMsgType, const void *pBuf, u32 dwBufLen);

	/**
    * \brief            tagSipAdapterCB Constructor
    * \return           void.
    */
	tagSipAdapterCB()
	{
		memset(this, 0, sizeof(tagSipAdapterCB));
	}

} TSipAdapterCB;

/// channel reason
enum EmSipChannelReason
{
	emSipChannelReasonBegin,        ///< channel reason begin
	emSipChannelDisconnectNormal,   ///< Channel Disconnect Normal
	emSipDualOffLine,               ///< Dual Off Line
	emSipChannelDisconnectForce,	///< 抢断双流（双流请求发送成功，但收到对端非200Ok的正常应答）
	emSipDualNotSend,	            ///< 双流未经协议栈发送出去（当前状态不正确，导致协议栈未发送）
};

/// 呼叫挂断原因
enum EmSipCallDisconReason
{
	emSipDiscon_Busy			= 1,	///< 对端忙
	emSipDiscon_Normal			= 2,	///< 正常挂断
	emSipDiscon_Rejected		= 3,	///< 对端拒绝
	emSipDiscon_Unreachable		= 4,	///< 对端不可达
	emSipDiscon_Local			= 5,	///< 本地原因
	emSipDiscon_unknown			= 6,	///< 未知原因
		
	emSipDiscon_AlredayInDualStream = 7,		///< 正在双流中，无法发起或接收双流
	emSipDiscon_Normal_Peer			= 8,        ///< 对方挂断
	emSipDiscon_Abnormal			= 9,        ///< 本端掉线挂断
	emSipDiscon_Abnormal_Peer		= 10,       ///< 对端掉线挂断
	emSipDiscon_MultiConfOver		= 11,       ///< 多点会议结束
	emSipDiscon_ConfAlredayExit		= 12,       ///< 会议已经存在
	emSipDiscon_InvalidDestAddr		= 13,		///< 无效的目的地址
		
	emSipDiscon_CallFull			= 14,		///< 呼叫句柄已满(可能存在呼叫句柄未释放的问题)
	emSipDiscon_MaxMtNum            = 15,       ///< 会议中呼叫已达上限

	emSipDisconnect_StreamEncryptKeyNotEqual = 16,    ///< 呼叫两端支持的码流加密（方式或密钥）不一致

	emSipDiscon_RmtReconnect = 100,   ///< 行政级别比对端低  
	emSipDiscon_EncrypeErr,           ///< encrypt error
	emSipDiscon_AdaptBusy,            ///< adapter busy
	emSipDiscon_MccDrop,              ///< 会控挂断     
	emSipDiscon_ChairDrop,            ///< 主席挂断     
	emSipDiscon_MMcuDrop,             ///< 上级会议挂断  
	emSipDiscon_ConfReleaseNoMt,      ///< 无终端自动结会-1分钟   
	emSipDiscon_ConfReleaseNoJoinedMt,///< 无在线终端自动结会-5分钟    
	emSipDiscon_ConfReleaseOnlyOneMt, ///< 仅一个在线终端自动结会-10分钟  
	emSipDiscon_Exception,            ///< 异常挂断   
	emSipDiscon_MpDisconnect,         ///< mp掉线   

	emSipDiscon_DonotDisturb,         ///< 免打扰
	
	emSipLoadTlsCertFailed,           ///< Tls Cert load failed

	emSipDiscon_AuthenticationErr,	  ///< MT Authenticate Failed
	emSipDiscon_OverMaxPortLicense    ///< over max port license
};

/// regserver发送的查询指令
typedef struct tagRegOptionData		
{
	u32 m_dwtime;						///< 注册句柄
	u32 m_ip;							///< 终端的ip	
	u16 m_port;					    	///< 终端的port
	/**
    * \brief            tagRegOptionData Constructor
    * \return           void.
    */
	tagRegOptionData()
	{
		memset(this, 0, sizeof(tagRegOptionData));
	}
}TRegOptionData;

/// reg state
enum EmRegState
{
	emRegIdle,         /// idle
	emRegRegistering,  /// registering
	emRegRegistered,   /// registered
	emRegFailed,       /// failed
	emUnReg,           /// unreg
};

/// call type
enum EmSipCallType
{
	emDirect = 0,					///< 直接呼叫
	emByRedirect,					///< 通过重定向服务器呼叫
	emByPxy,						///< 通过代理服务器呼叫
};



/// register reason
enum EmRegisterReason
{
	emRegNone = 0,     ///< none
	emRegSuc,          ///< 注册成功
	emRegFail,         ///< 注册失败
	emRegNotFound,     ///< not found
	emRegNameDup,      ///< 注册服务器重名时，服务器发送重名消息
	emRegTimeOut,      ///< 注册服务器不可达，超时
};

/// 终端信息参数
typedef struct tagTerminalInformation 
{
	TTERLABEL	m_tTerLabel;                 ///< ter label
	s8			m_achTerID[LEN_TERID + 1];   ///< ter id
	
	/**
    * \brief            tagTerminalInformation Constructor
    * \return           void.
    */
	tagTerminalInformation()
	{
		Clear();
	}
	/**
    * \brief            tagTerminalInformation init
    * \return           void.
    */
	void Clear()
	{
		m_tTerLabel.Clear();
        memset( m_achTerID, 0, sizeof(m_achTerID) );        
	}	
	
	/**
	* \brief            设置终端编号
	* \param[in]        ptLabel       :ter label
	*/
	void SetLabel(const PTTERLABEL ptLabel)
	{
		if (ptLabel != NULL)
		{
			memcpy( &m_tTerLabel, ptLabel, sizeof(m_tTerLabel) );
		}		
	}
	/**
	* \brief            set label
	* \param[in]        byMcuNo       :mcu no
	* \param[in]        byTerNo       :ter no
	*/
	void SetLabel(u8 byMcuNo, u8 byTerNo)
	{
		if (byMcuNo <= MAX_MT_NUM_IN_CONF && byTerNo <= MAX_MT_NUM_IN_CONF)
		{
			m_tTerLabel.SetTerminalLabel(byMcuNo, byTerNo);
		}
	}
	/**
	* \brief            get ter label
	* \return           TTERLABEL.
	*/
	TTERLABEL& GetTerlabel()
	{
		return m_tTerLabel;
	}
	/**
	* \brief            get label
	* \param[in]        byMcuNo       :mcu no
	* \param[in]        byTerNo       :ter no
	*/
	void GetLabel(u8& byMcuNo, u8& byTerNo)
	{
		m_tTerLabel.GetTerminalLabel( &byMcuNo, &byTerNo );
	}
	/**
	* \brief            get mcu no
	* \return           u8.
	*/
	u8 GetMcuNo() 
	{ 
		return m_tTerLabel.GetMcuNo();	
	}
	/**
	* \brief            get ter no
	* \return           u8.
	*/
	u8 GetTerNo() 
	{ 
		return m_tTerLabel.GetTerNo();	
	}
	
	 /**
	 * \brief            set name
	 * \param[in]        pchName  :name value
	 * \return           BOOL32, TRUE/FALSE
	 */
	BOOL32 SetName(const s8* pchName)
	{
		if (pchName != NULL)
		{
			strncpy( m_achTerID, pchName, LEN_TERID + 1 );
			m_achTerID[LEN_TERID] = '\0';
			return TRUE;
		}
		return FALSE;
	}
	/**
	 * \brief            get name
	 * \return           s8*
	 */
	s8* GetName()
	{
		return m_achTerID;
	}
	/**
    * \brief            tagTerminalInformation operator =
    * \return           void.
    */
	void operator = (tagTerminalInformation& tTerInfo)
	{
		m_tTerLabel.SetTerminalLabel( tTerInfo.m_tTerLabel.GetMcuNo(), 
			tTerInfo.m_tTerLabel.GetTerNo() );
		
		strncpy( m_achTerID,tTerInfo.GetName(), LEN_TERID + 1);
	}
	/**
    * \brief            tagTerminalInformation operator !=
    * \return           BOOL32, TRUE/FALSE
    */
	BOOL32 operator != (tagTerminalInformation& tTerInfo)
	{
		if ( m_tTerLabel.GetMcuNo() == tTerInfo.m_tTerLabel.GetMcuNo() && 
			m_tTerLabel.GetTerNo() == tTerInfo.m_tTerLabel.GetTerNo() &&
			strcmp( m_achTerID, tTerInfo.m_achTerID ) == 0 )
		{
			return FALSE;
		}
		return TRUE;
	}
	/**
    * \brief            tagTerminalInformation operator ==
    * \return           BOOL32, TRUE/FALSE
    */
	BOOL32 operator == (tagTerminalInformation& tTerInfo)
	{
		if ( m_tTerLabel.GetMcuNo() == tTerInfo.m_tTerLabel.GetMcuNo() && 
			m_tTerLabel.GetTerNo() == tTerInfo.m_tTerLabel.GetTerNo() &&
			strcmp( m_achTerID, tTerInfo.m_achTerID ) == 0 )
		{
			return TRUE;
		}
		return FALSE;
	}
}TTERINFO,*PTTERINFO;

/// 别名地址
typedef struct PROTO_API tagAliasTransAddress
{
	s8  m_achAlias[LEN_ALIAS + 1];			///< h323-Id 别名后两位为空
	/**
    * \brief            tagAliasTransAddress Constructor
    * \return           void.
    */
	tagAliasTransAddress()
	{
		Clear();
	}
	/**
    * \brief            tagAliasTransAddress init
    * \return           void.
    */
	void Clear()
	{
		memset( m_achAlias, 0, sizeof(m_achAlias) );
	}
	
	/**
	* \brief            set alias address
	* \param[in]        pAlias          :alias string
	* \return           BOOL32, TRUE/FALSE
	*/
	BOOL32 SetAliasAddr( const s8* pAlias )
	{
		memset( m_achAlias, 0, sizeof(m_achAlias) );
		s32 nLen = Minimum( (s32)strlen(pAlias), (s32)LEN_ALIAS );
		strncpy( m_achAlias, pAlias, nLen );
		m_achAlias[nLen] = '\0';
		return TRUE;
	}	
	
	/**
	* \brief            get alias address
	* \return           s8*
	*/
	s8* GetAliasName()  
	{
		return m_achAlias;	
	}
}TAliasTransAddress, *PTAliasTransAddress;

/// 呼叫时的别名地址
typedef struct PROTO_API tagSipTransAddress
{
	CallAddrType        m_emType;		///< 呼叫类型
	PFC_IPADDR  	    m_tNetAddr;		///< IP呼叫时使用	
	TAliasTransAddress	m_tAlias;		///< 别名呼叫使用
	emProtocolType      m_emProtocolType;///<  Protocol Type

	/**
    * \brief            tagSipTransAddress  Constructor
    * \return           void.
    */
	tagSipTransAddress()
	{
		Clear();
	}
	/**
    * \brief            tagSipTransAddress init
    * \return           void.
    */
	void Clear()
	{
		m_emType         = emcat_err;
		m_emProtocolType = emTypeInvalid;
		m_tNetAddr.Clear();
		m_tAlias.Clear();
	}
	
}TSipTransAddress, *PTSipTransAddress;

/// goal type
typedef enum
{
    emCreate,                              ///< create 
	emJoin,                                ///< join
	emInvite,                              ///< invite
	emCapabilityNegotiation,               ///< capability negotiation
	emCallIndependentSupplementaryService, ///< Call Independent Supplementary Service
	emLastCG                               ///< last CG
} EmConfGoalType;

/// sip encrypt key
typedef struct PROTO_API tagTSipEncryptKey
{
	emEncryptType m_emEncryptType;        ///< encrypt type
	u8 m_byLen;                           ///< 密钥长度
	u8 m_abyKey[MAX_SIP_ENCRYPT_KEY_LEN]; ///< 密钥长度
	
public:
	/**
    * \brief            tagTSipEncryptKey init
    * \return           void.
    */
	void Clear()
	{
		memset( this, 0, sizeof(tagTSipEncryptKey) );
		m_emEncryptType = emEncryptTypeNone;
	}
	/**
    * \brief            tagTSipEncryptKey  Constructor
    * \return           void.
    */
	tagTSipEncryptKey()
	{
		Clear();
	}
	/**
    * \brief            tagTSipEncryptKey  Print
    * \return           void.
    */
	void Print()
	{
		PfcPrintf(TRUE, FALSE, "TSipEncryptKey:EncryptType=%d, m_byLen=%d, key:", m_emEncryptType, m_byLen);
		s32 nLen = Minimum(m_byLen, LEN_AES_KEY);
		if ( emEncryptTypeNone != m_emEncryptType )
		{
			for (int i = 0; i < nLen; i++)
			{
				PfcPrintf(TRUE, FALSE, "%c", m_abyKey[i]);
				if ( i == (nLen - 1))
				{
					PfcPrintf(TRUE, FALSE, "\n");
				}
			}
		}		
	}
}TSipEncryptKey;

/// sip poll info for tp
typedef struct PROTO_API tagTSipPollInfoTP
{
	BOOL32 m_bIsPoll;                  ///< is poll
	u16  m_wPollExpire;                ///< poll expire
	
	/**
    * \brief            tagTSipPollInfoTP init
    * \return           void.
    */
	void Clear()
	{
		memset( this, 0, sizeof(tagTSipPollInfoTP) );
	}
	/**
    * \brief            tagTSipPollInfoTP Constructor
    * \return           void.
    */
	tagTSipPollInfoTP()
	{
		Clear();
	}
}TSipPollInfoTP;

/// sip config aux mix info for tp
typedef struct PROTO_API tagTSipConfAuxMixInfoTP
{
	BOOL32 m_bStart;                            ///< is start
	u16	m_wConfID;                              ///< config id
	u16 m_wSpeakerIndex;					    ///< 下面数组的索引
	u16	m_awList[MAX_SIP_CONF_AUDMIX_NUM_TP];	///< 混音ID
	
	/**
    * \brief            tagTSipConfAuxMixInfoTP init
    * \return           void.
    */
	void Clear()
	{
		memset( this, 0, sizeof(tagTSipConfAuxMixInfoTP) );
		m_wConfID = SIP_INVALID_INDEX_TP;
		m_bStart = FALSE;
	}
	/**
    * \brief            tagTSipConfAuxMixInfoTP Constructor
    * \return           void.
    */
	tagTSipConfAuxMixInfoTP()
	{
		Clear();
	}
}TSipConfAuxMixInfoTP;

typedef struct PROTO_API tagTSipConfSpeechMixTP
{
	u32          m_mode;        //0:idle   1: smart   2:custom
	u16          m_wNum;
	u16          m_awMixEp[MAX_MIX_EP_LIST_LEN];
	BOOL32       m_bVacOn;

	void Clear()
	{
		memset(this, 0, sizeof(tagTSipConfSpeechMixTP));
	}

	tagTSipConfSpeechMixTP()
	{
		Clear();
	}
}TSipConfSpeechMixTP;

/// conference information
typedef struct PROTO_API tagTSipConfInfo
{
	s8	 m_achConfId[MAX_SIP_CONF_ID_LEN + 1];			///< conference ID
	s8	 m_achConfName[MAX_SIP_CONF_NAME_LEN + 1];		///< conference name
	s8	 m_achConfNumber[MAX_SIP_CONF_E164_LEN + 1];	///< conference number
	s8	 m_achConfPwd[MAX_SIP_PASSWORD_LEN + 1];	    ///< conference password
	BOOL32 m_bNeedPassword;                             ///< is need password
	u16  m_wConfDuration;							    ///< 会议持续时间		
	PayloadType   m_emVideoFormat;				        ///< 会议视频格式(VIDEO_H261等)
	PayloadType   m_emAudioFormat;				        ///< 会议音频格式(AUDIO_MP3等)
	emResolution  m_emResolution;					    ///< 会议视频分辨率(VIDEO_CIF等)
	u8 m_byProfile;									    ///< 主流profile
	u8 m_byVidMPI;					                    ///< 主流帧率
	BOOL32 m_bIsAutoVMP;								///< 是否自动画面合成
	BOOL32 m_bIsMix;	    							///< 是否混音
	PayloadType	m_emSecVideoFormat;			            ///< 双流格式
	emResolution m_emSecVidRes;					        ///< 双流分辨率
	u8 m_bySecProfile;								    ///< 双流profile
	u8 m_bySecVidMPI;					                ///< 双流帧率
	u16 m_wCallRate;									///< 呼叫速率(kbps)
	u16	m_wDualCallRate;								///< 双流呼叫速率(kbps)
	TSipPollInfoTP  m_tPollInfo;                        ///< poll info
	TSipConfAuxMixInfoTP m_tConfAudMixInfo;             ///< config audio mix info
	TSipConfSpeechMixTP  m_tSpeechMixInfo;              ///< speech mix info
	
public:
	/**
    * \brief            tagTSipConfInfo Constructor
    * \return           void.
    */
	tagTSipConfInfo()
	{ 
		Clear();	
	}
	/**
    * \brief            tagTSipConfInfo init
    * \return           void.
    */
	void Clear()
	{
		memset( this, 0, sizeof(tagTSipConfInfo) );
		m_tPollInfo.Clear();
		m_tConfAudMixInfo.Clear();
		m_tSpeechMixInfo.Clear();
	}
	
}TSipConfInfo ,*PTSipConfInfo;

/// 发起呼叫参数
typedef struct PROTO_API tagSipCallParam 
{
	BOOL32				m_bCreateConf;                          ///< is create conf
	EmConfGoalType		m_emConfGoalType;  						///< 会议的目标类型
	u32					m_dwCallRate;							///< 呼叫速率	(kbps)
	TSipUrl				m_tCalledAddress;						///< 被叫地址
	TSipUrl				m_tCallingAddress;						///< 主叫地址
	EmSipCallType		m_emCallType;							///< 呼叫类型 (direct|by pxy|by redirect)
    THostName			m_tServerAddr;							///< pxy server| redirect server    
	EmSipConnection		m_emSipConnection;						///< 信令连接类型 tcp udp tls default udp
	s32					m_nProductIdSize;                       ///< productid size 
	u8					m_abyProductId[MAX_PRODUCTID_LEN];		///< 产品号
	s32					m_nVerIdSize;                           ///< version id size
	u8					m_abyVersionId[MAX_PRODUCTID_LEN];		///< 版本号
	emEndpointType		m_emSipTerType;                         ///< endpoint type
	
	/// 用于网真
	EmSipLevel			m_emSipLevel;							///< 级别
	s32					m_nScreenNum;                           ///< 屏数
	u8					m_abyConfId[LEN_GUID];		            ///< 会议号,必须16 octet
	u16					m_wConfId;                              ///< conf id
	u8					m_byTerNum;								///< 被邀终端个数
	TSipTransAddress	m_atList[MAX_TERMINAL_NUM];				///< 被邀终端列表
	TSipConfInfo		m_tConfInfo;							///< 会议信息
	
	BOOL32				m_bNatCall;								///< 呼叫是否过nat
	BOOL32				m_bAddTpAttr;							///< 是否添加TP属性（sip包头及sdp能力包含TP非标属性）
	BOOL32				m_bSupportMmcu;							///< 是否支持合并级联
	
	s8 m_achCallId[MAX_NUM_CALLID];								///< CALL-ID	
	TSipEncryptKey	    m_tStreamKey;							///< 若m_tStreamKey.m_emEncryptType=emEncryptTypeNone 表示码流不加密

    EmVendorProductId   m_emVendorId;                           ///< vendor id
	EmVendorProductId   m_emPeerVendorId;                       ///< peer vendor id

	u8 m_byNonStdHdrNum;	                                    ///< 非标sip包头个数
	TSipHead m_atNonStdHdr[MAX_SIP_NONSTD_HEADER_NUM];	        ///< 非标sip包头

#ifdef _KDV_SRTP_SUPPORT_
	EmSrtpMode			m_emSrtpMode;	                        ///< None、Optional、Mandatory
#endif
	TSipUrl				m_tReqUri;                              ///< request uri

	s8 m_achPassword[MAX_PASSWORD_LEN+1];                       ///< 认证密码
	s8 m_achUsername[MAX_USER_NAME_LEN+1];	                    ///< 认证用户名
	s8 m_achDomainName[MAX_DOMAIN_NAME_LEN+1];	                ///< 域名

	EmTlsType m_emTlsType;                                      ///< TLS type
public:
	/**
    * \brief            tagSipCallParam  Constructor
    * \return           void.
    */
	tagSipCallParam()
	{
		memset(this, 0, sizeof(tagSipCallParam));
		m_tStreamKey.Clear();
		m_emSipConnection = emSipUdpConnection;
		m_emVendorId      = emKeda;
		m_emPeerVendorId  = emKeda;
#ifdef _KDV_SRTP_SUPPORT_
		m_emSrtpMode      = emSrtpModeNone;
#endif
		m_emTlsType       = emTlsNone;
	}
	
	/**
	* \brief            set conf id
	* \param[in]        pchConfId          :conf id string
	* \param[in]        byLen              :id length
	*/
	void SetConfId(const u8* pchConfId, u8 byLen)
	{
		if (pchConfId == NULL || (s32)byLen <= 0)
		{
			return;
		}
		
		s32 nReal = Minimum(Maximum((s32)LEN_1, (s32)byLen), (s32)LEN_GUID);
		memcpy(m_abyConfId, pchConfId, nReal);
	}
	
}TSipCallParam;

/// sip node info
typedef struct tagSipNodeInfo
{
    EmVendorProductId 	m_emVendorId;                         ///< vendor id
	BOOL32     			m_bMt;                                ///< is mt
	s8       			m_achProductId[MAX_PRODUCTID_LEN + 1];///< product id
	s8       			m_achVersion[MAX_PRODUCTID_LEN + 1];  ///< version id
	
	public:
		/**
        * \brief            tagSipNodeInfo  Constructor
        * \return           void.
        */
		tagSipNodeInfo()
		{ 
			Clear();
		}
		/**
        * \brief            tagSipNodeInfo  init
        * \return           void.
        */
		void Clear()
		{
			memset(this, 0, sizeof(tagSipNodeInfo));
		}
}TSipNodeInfo;

/// sdp session info
typedef struct tagSdpSessionInfo
{
    s8      m_achSessionName[SESSION_NAME_LEN + 1];     ///< session name

    s8      m_achOriginSID[SESSION_ID_LEN + 1];         ///< SessionId
    s8      m_achOriginUserName[MAX_PRODUCTID_LEN + 1]; ///< User name
    //s8      m_achOriginVer[SESSION_VERSION_LEN+1];    ///< session Version
	s32     m_nOriginVer;                               ///< origin ver
    s8      m_achOriginAddress[128];                    ///< Address-url
    s8      m_achTerVer[SESSION_INFO_LEN + 1];          ///< terminal ver
    
    u32     m_dwBandWidth;                              ///< band width
    u32     m_dwStartTime;                              ///< start time
    u32     m_dwEndTime;                                ///< end time
    u32     m_dwIP;                                     ///< ip
public:
	/**
    * \brief            tagSdpSessionInfo  Constructor
    * \return           void.
    */
	tagSdpSessionInfo(){ memset(this, 0, sizeof(tagSdpSessionInfo));}
} TSdpSessionInfo;

/// endpoint type
enum EmSipEndpointType
{
	emSipEndpointTypeUnknown  = 0,            ///< unknown
	emSipEndpointTypeCNS	  = 0x01,         ///< cns
	emSipEndpointTypeUMS	  = 0x02,         ///< ums
	emSipEndpointTypeRegister = 0x04          ///< register
};
/// sip register local info
typedef struct tagSipRegistLocalInfo
{
	EmSipEndpointType  m_emEndpointType;     ///< 类型是ums或cns
	u32 m_dwLocalIP;                         ///< 自身IP地址
	s8  m_achSoftVersion[MAX_USER_NAME_LEN + 1];  ///< 软件版本号
	s8  m_achCompileTime[MAX_USER_NAME_LEN + 1];  ///< 编译时间 
public:
	/**
    * \brief            tagSipRegistLocalInfo  Constructor
    * \return           void.
    */
    tagSipRegistLocalInfo() 
    {memset(this, 0, sizeof(tagSipRegistLocalInfo));}
}TSipRegistLocalInfo, *PTSipRegistLocalInfo;
/// register info
typedef struct tagRegisterInfo
{
	TSipUrl m_tFromUrl;			                   ///< From 字段URL
	TSipUrl m_tToUrl;			                   ///< To 字段URL
	THostName m_tLocalAddr;		                   ///< 本地主机信息,for via contact
	THostName m_tRegistrar;		                   ///< 注册server主机信息
	u32 m_dwExpires;			                   ///< 超时时间,单位秒
	TSipRegistLocalInfo			m_tSipRegLocalInfo;///< register local info
	EmSipConnection	m_emConnection;	               ///< 注册地址类型
	PFC_IPADDR m_tNatAddress;                      ///< nat address
	BOOL32 m_bPortReused;	                       ///< 是否端口复用
	s8	m_achProductId[MAX_PRODUCTID_LEN + 1];     ///< product id
	s8	m_achVersionId[MAX_PRODUCTID_LEN + 1];     ///< version id
	emEndpointType	 m_emEndpointType;             ///< endpoint type
	EmVendorProductId m_emVendorId;                ///< vendor id
	EmTlsType         m_emTlsType;                 ///< tls type
	s8                m_achDevId[MAX_QT_ID_LEN];   ///< max length of device id for qt tls
	u8       m_byNonStdHdrNum;                          ///< max nonstandard header number
	TSipHead m_atNonStdHdr[MAX_SIP_NONSTD_HEADER_NUM];  ///< nonstandard header
	BOOL32            m_bAddTpAttr;                 /// istps 
public:	
	/**
    * \brief            tagRegisterInfo  Constructor
    * \return           void.
    */
	tagRegisterInfo()
	{ 
		memset(this, 0, sizeof(tagRegisterInfo));
		m_emConnection   = emSipUdpConnection;
		m_emEndpointType = emEndpointTypeMT;
		m_emVendorId     = emKeda;
		m_emTlsType      = emTlsNone;
	}
}TRegisterInfo;
/// sip register name
typedef struct tagSipRegName
{
	EmHostNameType m_emSipAddrType;
	s8     m_achUserName[MAX_USER_NAME_LEN + 1];         ///< 注册名
	s8     m_achPassword[MAX_PASSWORD_LEN + 1];	        ///< 注册密码
	s8     m_achDisplayName[MAX_USER_NAME_LEN + 1];      ///< 显示名称

	s8     m_achPeerUserName[MAX_USER_NAME_LEN + 1];     ///< 对端注册名
	s8     m_achPeerDisplayName[MAX_USER_NAME_LEN + 1];  ///< 对端显示名称
	/**
    * \brief            tagSipRegName  Constructor
    * \return           void.
    */
	tagSipRegName()
	{
		memset( this, 0, sizeof(tagSipRegName) );
	}
}TSipRegName, *PTSipRegName;
/// register request
typedef struct tagRegisterRequest
{
	TSipRegName      m_atSipRegName[MAX_NUM_REGNAME_SIZE]; ///< sip reg name
	s32				 m_nSipRegArraySize;                   ///< sip reg array size
	
	PFC_IPADDR       m_atContactAddr[MAX_NUM_CONTACT_ADDR];///< 注册地址
	u32 m_dwExpires;                                       ///< 超时时间,单位秒
	s8 m_achCallId[MAX_NUM_CALLID];                        ///< 呼叫ID
	s32 m_nCSqence;                                        ///< 序列号 m_tRegistrar m_dwExpires m_aCallId m_nCSqence 需要业务层保存，以便查询
	EmSipConnection m_emSipConnection;                     ///< sip connection
    TSipRegistLocalInfo  m_tLocalInfo;                     ///< local info
	
public:
	/**
    * \brief            tagRegisterRequest  Constructor
    * \return           void.
    */
	tagRegisterRequest()
	{ 
		memset(this , 0 , sizeof(tagRegisterRequest));
		m_emSipConnection = emSipTcpConnection;
	}
}RegisterRequest;

/// register response
typedef struct tagRegisterResponse
{
	PFC_IPADDR       m_tContactAddr;    ///< contact address
	EmSipConnection  m_emSipConnection; ///< sip connection
	BOOL32 m_bSerchPrefix;              ///< 判断regserver是否用了前缀查找，如果用前缀查找，回复的300中就将achAlias写入到contact地址中
	s8 m_achAlias[MAX_USER_NAME_LEN + 1];    ///< alias
public:
	/**
    * \brief            tagRegisterResponse  Constructor
    * \return           void.
    */
	tagRegisterResponse()
	{
		memset(this, 0, sizeof(tagRegisterResponse));
		m_emSipConnection = emSipTcpConnection;
	}
}RegisterResponse;

/// sip alias type
enum EmSipAliasType
{
	sip_Alias_Unknow, ///<  sip alias unknown
	sip_Alias_e164,   ///<  e164
	sip_Alias_h323,   ///<  h323
	sip_Alias_IP,     ///<  ip
};
/// sip alias
typedef struct tagTSipAlias
{
	EmSipAliasType	m_emType;                         ///< sip alias type
	s8				m_achAlias[MAX_USER_NAME_LEN + 1];     ///< alias string
	/**
    * \brief            tagTSipAlias  Constructor
    * \return           void.
    */
    tagTSipAlias()
	{
		memset( this, 0, sizeof(tagTSipAlias) );
	}
}TSipAlias;
/// Sip reg Nsm Type
enum EmSIPRegNSMType
{
	emSipRegNSMType_CNS = 0,  ///< cns
	emSipRegNSMType_UMS,      ///< ums
	emSipRegNSMType_ALL,      ///< all
	emSipRegNSMType_CONF = 10,///< conf
	emSipRegNSMType_CONF_TLS ,///< don't add kdNstd-ApplicationHandle
};
/// sip reg NSM
typedef struct tagSIPRegNSM
{
	EmSIPRegNSMType m_emType;

	PFC_IPADDR m_tRegSeverAddr;      ///< 注册服务器地址
	PFC_IPADDR m_tRegLocalAddr;      ///< 本地地址

	TSipRegName	m_tSipRegName;		 ///< RegName: including user and display name for SIP header
	EmSipConnection m_emConn;	     ///< tcp/tls or udp

	BOOL32 m_bIsAddNonstHeader;      ///< if use Add Nonstd Header 
	TSipHead m_tNonstdAttr;          ///< if m_bIsAddNonstHeader is true,m_tNonstdAttr will be used
	/**
    * \brief            tagSIPRegNSM  Constructor
    * \return           void.
    */
	tagSIPRegNSM()
	{
		memset( this, 0, sizeof(tagSIPRegNSM) );
		m_tSipRegName.m_emSipAddrType = emUrlNone;
		m_emConn = emSipUdpConnection;
	}
}TSIPRegNSM;
/// sip reg pack info
typedef struct tagTSipRegPackInfo
{
	u16 m_wPackSeq;       ///< 包序号，从1开始，0为无效值
	u16 m_wTotalPackNum;  ///< 包总数
	/**
    * \brief            tagTSipRegPackInfo  Constructor
    * \return           void.
    */
	tagTSipRegPackInfo()
	{
		m_wPackSeq = 0;
		m_wTotalPackNum = 0;
	}
	
}TSipRegPackInfo, *PTSipRegPackInfo;
/// sip reg info
typedef struct tagTSipRegInfo
{
	u16		   m_wAliasNum;                           ///< alias number
	TSipAlias  m_atAlias[MAX_NUM_REGNAME_SIZE];       ///< 暂时定为最大值为64个名称为一波返回
	EmSipEndpointType m_emSelfType;                   ///< 注册方 的系统类型(UMS和CNS)    
	/**
    * \brief            tagTSipRegInfo  Constructor
    * \return           void.
    */
	tagTSipRegInfo()
	{
		m_wAliasNum = 0;
		memset( m_atAlias, 0, sizeof( m_atAlias ) );
		m_emSelfType = emSipEndpointTypeUnknown;
	}
	
}TSipRegInfo;

/// sip reg pack xml
typedef struct tagTSipRegPackXml
{
	TSipRegPackInfo tPackInfo;    ///< pack info
	EmSIPRegNSMType emType;       ///< sip reg nsm type
	TSipRegInfo  tRegInfo;        ///< reg info
	/**
    * \brief            tagTSipRegPackXml  Constructor
    * \return           void.
    */
	tagTSipRegPackXml()
	{
		emType = emSipRegNSMType_ALL;
	}
}TSipRegPackXml;
/// sip reg info ums
typedef struct tagTSipRegInfoUms
{
	u16		   m_wAliasNum;                                ///< alias number
	TSipAlias  m_atAlias[MAX_NUM_REGNAME_SIZE];            ///< 暂时定为最大值为64个名称为一波返回
	PFC_IPADDR   m_atContactAddr[MAX_NUM_CONTACT_ADDR];///< 注册地址
	u32 m_dwExpires;                                       ///< 超时时间,单位秒
	EmSipConnection emSipConnection;                       ///< sip connection
	TSipRegistLocalInfo m_tSipRegistLocalInfo;             ///< sip register local info
	/**
    * \brief            tagTSipRegInfoUms  Constructor
    * \return           void.
    */
	tagTSipRegInfoUms()
	{
		Clear();
	}
	/**
    * \brief            tagTSipRegInfoUms  init
    * \return           void.
    */
	void Clear()
	{
		memset(this, 0, sizeof(tagTSipRegInfoUms));
	}
	
}TSipRegInfoUms;
/// sip reg info cns
typedef struct tagTSipRegInfoCns
{
	u16		   m_wAliasNum;                                ///< alias number
	TSipAlias  m_atAlias[MAX_NUM_REGNAME_SIZE_CNS];        ///< 暂时定为最大值为64个名称为一波返回
	PFC_IPADDR   m_atContactAddr[MAX_NUM_CONTACT_ADDR];///< 注册地址
	u32 m_dwExpires;                                       ///< 超时时间,单位秒
	EmSipConnection emSipConnection;                       ///< sip connection
	TSipRegistLocalInfo m_tSipRegistLocalInfo;             ///< sip register loacal info
	/**
    * \brief            tagTSipRegInfoCns  Constructor
    * \return           void.
    */
	tagTSipRegInfoCns()
	{
		Clear();
	}
	/**
    * \brief            tagTSipRegInfoCns  init
    * \return           void.
    */
	void Clear()
	{
		memset(this, 0, sizeof(tagTSipRegInfoCns));
	}
}TSipRegInfoCns;
/// sip reg pack xml b2
typedef struct tagTSipRegPackXmlB2
{
	TSipRegPackInfo m_tPackInfo;          ///< packet info
	EmSIPRegNSMType m_emType;             ///< sip reg nsm type
	EmSipEndpointType  m_emEndpointType;  ///< endpoint type
	u16	m_wTotalRegInfo;                  ///< total reg info
	/**
    * \brief            tagTSipRegPackXmlB2  Constructor
    * \return           void.
    */
	tagTSipRegPackXmlB2()
	{
		m_emType = emSipRegNSMType_ALL;
		m_wTotalRegInfo = 0;
	}
}TSipRegPackXmlB2;


/// sip nonstd data
typedef struct tagSipNonStdData
{
	EmSipConnection m_emConn;	                         ///< tcp or udp
	TSipUrl m_tLocalUrl;	                             ///< 本端地址
	TSipUrl m_tRemoteUrl;	                             ///< 对端地址
	u8 m_byNonStdHdrNum;	                             ///< 非标sip包头个数
	TSipHead m_atNonStdHdr[MAX_SIP_NONSTD_HEADER_NUM];	 ///< 非标sip包头
	/**
    * \brief            tagSipNonStdData  init
    * \return           void.
    */
	void Clear()
	{
		memset(this, 0, sizeof(tagSipNonStdData));
	}
	/**
    * \brief            tagSipNonStdData  Constructor
    * \return           void.
    */
	tagSipNonStdData()
	{
		Clear();
	}
} TSipNonStdData;
/// register request info
typedef struct tagRegReqInfo
{
	TSipUri m_tLocalUri;	                                ///< Currently point to Request-URI ip address 
	s8 m_achCallId[MAX_SDP_ATTR_VALUE_LEN];                 ///< call id 
	s8 m_achRegName[MAX_USER_NAME_LEN + 1];	                    ///< Register name 
	TSipUri m_tUaAddress;	                                ///< Local ip address 
	TSipUri m_tUaNatAddress;	                            ///< Local real address with nat 
	s32	m_nExpires;	                                        ///< Expires parameter, otherwise -1 if not present. 
	BOOL32 m_bIsContactStar;	                            ///< The contact contains only a '*' character 
	s8 m_achProductId[MAX_PRODUCTID_LEN];                   ///< product id 
	s8 m_achVersionId[MAX_PRODUCTID_LEN];                   ///< version id 
	u8 m_byNonStdHeadNum;                                   ///< nonstd header number
	TSipHead m_atNonStdHead[MAX_SIP_NONSTD_HEADER_NUM];     ///< nonstd header array
	u8 m_byOtherParamNum;                                   ///< other parament number
	TSipParam m_atUriOtherParam[MAX_SIP_PARAM_NUM];///< other uri parament
	/**
    * \brief            tagRegReqInfo  Constructor
    * \return           void.
    */
	tagRegReqInfo()
	{ 
		memset(this, 0, sizeof(tagRegReqInfo));
		m_nExpires = -1;
	}
} TRegReqInfo;

/**
* \brief            GenerateChannelXml
* \param[in]        pbyInBuf          :h_chan_flowControl-stream_id(s32)+Bitrate(u16),sizeof(s32)+ sizeof(u16)\n 
                                       h_chan_fastupdate-stream_id(s32),sizeof(s32)\n
                                       Null-0
* \param[in]        wInLen            :buffer length
* \param[in]        emCtrlMsg         :h_chan_flowControl,h_chan_fastupdate
* \param[in]        pchOutBuf         :generate xml
* \param[in]        wOutLen           :the size of xml
*/
PROTO_API void GenerateChannelXml(u8* pbyInBuf, u16 wInLen, EmSipConfCtrlMsgType  emCtrlMsg , s8* pchOutBuf, u16 &wOutLen);

/**
* \brief            Parse NonStd Xml
* \param[in]        pbyInBuf          :h_chan_flowControl-stream_id(s32)+Bitrate(u16),sizeof(s32)+ sizeof(u16)\n 
                                       h_chan_fastupdate-stream_id(s32),sizeof(s32)\n
                                       Null-0
* \param[in]        wInLen            :buffer length
* \param[in]        emCtrlMsg         :h_chan_flowControl,h_chan_fastupdate
* \param[in]        pchOutBuf         :generate xml
* \param[in]        wOutLen           :the size of xml
*/
PROTO_API void ParseNonStdXml(s8* pchInBuf, u16 wInLen, EmSipConfCtrlMsgType  &emCtrlMsg , s8* pchOutBuf, u16 &wOutLen);

/**
* @}
*/
#endif
