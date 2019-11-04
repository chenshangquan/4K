///  All right reserved
///  
///  @file        kdvsipmodule.h
///  @author      zgf
///  @version     1.0
///  @date        2018-3-1
///  @brief       kdvsipmodule2
///  @details     sipmodule interfaces describe here what it is all about.
//////////////////////////////////////////////////////////////////////////

/************************************************************************/
/*  Start of kdvsipmodule2                                         */
/************************************************************************/

/**
 * @defgroup    sipmodule
 * @brief       sipmodule interfaces describe here what it is all about.
 * @{
 */
#ifndef SIPMODULE_H
#define SIPMODULE_H

#include "kdvtype.h"
#include "modulecallstruct.h"
#include "modulemananger.h"
#include "tpmodulestruct.h"

#include "kdvsipcommon.h"
#include "sipconfnonstdstruct.h"
#include "sipconfnonstdmsg.h"

#define S2H_DEFAULT_MAXSENDRECVBUFFERSIZE	20480            ///< 默认套接字发送接收缓冲大小
#define MAX_INSTANCE_PROTOCAL				192              ///< MAX INSTANCE PROTOCAL
#define SIPSERVPRINT_BUFFERSIZE				1024             ///< sipservice print buffer size
#define SIP_DEFAULT_SERVER_PORT				5060             ///< SIP DEFAULT SERVER PORT
#define SIP_DEFAULT_TLS_PORT				5061             ///< SIP DEFAULT TLS PORT
#define SIP_DEFAULT_KEEPALIVE_INTERVAL		30               ///< SIP DEFAULT KEEPALIVE INTERVAL(second)
#define SIP_DEFAULT_CALLINGTIMEOUT          20               ///< SIP DEFAULT CALLING TIMEOUT(second)
#define SIP_CONFIG_NAME						"MdlTestCfg.ini" ///< SIP CONFIG NAME
#define MAX_FILE_PATH_LEN					256              ///< MAX FILE PATH LEN

/// sip safe memcpy
template < class T >
T SIP_SAFE_CAST( T &t, u8 *p )
{
	if (NULL == p) return t;
	MEMCPY_CAST( &t, p, sizeof( T ) );
	return t;
}

/// sip module reg state
enum EmSipModRegState
{
	emSipModSateNone,            ///< None
	emSipModState2Idle,          ///< Idle
	emSipModState2Registered,    ///< Registered
	emSipModSate2Failed,         ///< Failed
	emSipModState2Terminated,    ///< Terminated
	emSipModSate2Redirected,     ///< Redirected
	emSipModState2SendMsgFailed, ///< Send Msg Failed
};

/// module config switch
enum emModuleConfigSwitch
{
	emModuleOff = 0,             ///< off
	emModuleOn	= 1,	         ///< on
};

/// module config type
enum emModuleConfigType
{
	emTypeBigin		= 0,        ///< Bigin
	emTypeCallParam = 1,        ///< CallParam
	emTypeMainCap	= 2,        ///< MainCap
	emTypeDualCap	= 3,        ///< DualCap
	emTypeBfcp		= 4,        ///< Bfcp
	emTypeFecc		= 5,        ///< Fecc
	emTypeRegister	= 6,        ///< Register
	emTypeAll		= 7,        ///< All
	emTypeEnd                   ///< End
};

/// Module Config
typedef struct tagTModuleConfig
{
	emModuleConfigSwitch m_emMdlSwitch; ///< enum moudle switch
	emModuleConfigType m_emType;        ///< enum moudle config type
	/**
    * \brief            tagTModuleConfig Constructor
    * \return           void.
    */
	tagTModuleConfig()
	{
		m_emType = emTypeBigin;
		m_emMdlSwitch = emModuleOff;
	}
}TModuleConfig;

/// sip module reg result
typedef struct tagTSipModRegResult
{ 
	BOOL32 m_bRegistered;          ///< is registered
	EmSipModRegState m_emRegState; ///< enum reg state
	u32 m_dwReceiveIp;             ///< local recv ipv4
	u8  m_abyReceiveIpv6[PFC_IPV6_ADDR_SIZE];         ///< local recv ipv6
	BOOL32 m_bIsLocalReason;       ///< is local reason
	BOOL32 m_bIsIpv6;              ///< is ipv6 for receive ip 

	u8 m_byNonStdHdrNum;	//非标sip包头个数
	TSipNstHeader m_atNonStdHdr[MAX_SIP_NONSTD_HEADER_NUM];	 
	/**
    * \brief            tagTSipModRegResult Constructor
    * \return           void.
    */
	tagTSipModRegResult()
	{
		MEMSET_CAST(this, 0, sizeof(tagTSipModRegResult));
	}
}TSipModRegResult, *PTSipModRegResult;

/**
* \brief            new call incoming callback
* \note             TP is the ums and cns 
* \param[in]        hCall      :call handle
* \param[in]        ptModParam :call info
* \param[in]        ptMainCap  :main cap
* \param[in]        ptTPCap    :TP cap
* \param[in]        ptDualCap  :dual cap
* \param[in]        ptBfcpCap  :bfcp cap
* \param[in]        ptFeccCap  :fecc cap
* \return           BOOL32, TRUE/FALSE
*/
typedef BOOL32 (PROTO_CALLBACK* CBNewCallIncoming)( 
			HMDLCALL hCall, 
			TModuleCallInfo *ptModParam, 
			TMdlCallCap *ptMainCap,
			TMdlTPCap *ptTPCap,  
			TDualCapList *ptDualCap,
			TBfcpCapSet *ptBfcpCap, 
			TFeccCapbility *ptFeccCap);

/**
* \brief            call connected callback
* \param[in]        hCall      :lower call handle
* \param[in]        hAppCall   :upper call info
* \param[in]        ptModParam :call info
* \param[in]        ptCallTP   :TP call info
* \return           BOOL32, TRUE/FALSE
*/
typedef BOOL32 (PROTO_CALLBACK* CBCallConnected)( 
			HMDLCALL hCall, 
			HMDLAPPCALL hAppCall, 
			TModuleCallInfo *ptModParam,
			TCallInfoTP *ptCallTP);

/**
* \brief            call disconnected callback
* \param[in]        hCall      :lower call handle
* \param[in]        hAppCall   :upper call info
* \param[in]        EmReason   :call disconnect reason
* \return           BOOL32, TRUE/FALSE
*/
typedef BOOL32 (PROTO_CALLBACK* CBCallDisconnected)(HMDLCALL hCall, HMDLAPPCALL hAppCall, const EmModuleCallDisconnectReason EmReason ); //sip挂断或拒绝

/**
* \brief            channel connected callback
* \param[in]        hCall             :lower call handle
* \param[in]        hAppCall          :upper call info
* \param[in]        pTConnectedInfo   :channel connected info
* \param[in]        nSize             :channel connected size
* \param[in]        pTDesTP           :TP channel connect info
* \return           BOOL32, TRUE/FALSE
*/
typedef BOOL32 (PROTO_CALLBACK* CBChannelConnected)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TChanConnectedInfo *pTConnectedInfo, s32 nSize, TChanDescriptTP *pTDesTP );       

/**
* \brief            channel disconnected callback
* \param[in]        hCall                   :lower call handle
* \param[in]        hAppCall                :upper call info
* \param[in]        TChanDisConnectedInfo   :channel disconnected info
* \param[in]        nSize                   :channel disconnected size
* \return           BOOL32, TRUE/FALSE
*/
typedef BOOL32 (PROTO_CALLBACK* CBChannelDisconnected)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TChanDisConnectedInfo *pTDisConInfo, s32 nSize );

/**
* \brief            dual incoming callback
* \param[in]        hCall                   :lower call handle
* \param[in]        hAppCall                :upper call info
* \param[in]        tDual                   :dual cap list
* \return           BOOL32, TRUE/FALSE
*/
typedef BOOL32 (PROTO_CALLBACK* CBSipDualIncoming)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TDualCapList *tDual);

/**
* \brief            recive reinvite callback
* \param[in]        hCall      :lower call handle
* \param[in]        hAppCall   :upper call info
* \param[in]        ptMainCap  :main cap
* \param[in]        ptDualCap  :dual cap
* \param[in]        ptBfcpCap  :bfcp cap
* \param[in]        ptFeccCap  :fecc cap
* \return           BOOL32, TRUE/FALSE
*/
typedef BOOL32 (PROTO_CALLBACK* CBSipReinviteRecive)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMdlCallCap *ptMainCap,
	TDualCapList *ptDualCap,
	TBfcpCapSet *ptBfcpCap, 
	TFeccCapbility *ptFeccCap);

/**
* \brief            fast update callback
* \param[in]        hCall      :lower call handle
* \param[in]        hAppCall   :upper call info
* \param[in]        hChan      :lower channel
* \param[in]        hAppChan   :upper channel
* \return           BOOL32, TRUE/FALSE
*/
typedef BOOL32 (PROTO_CALLBACK* CBFastUpdapte)( HMDLCALL hCall, HMDLAPPCALL hAppCall, HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan );

/**
* \brief            fast update callback
* \param[in]        hCall      :lower call handle
* \param[in]        hAppCall   :upper call handle
* \param[in]        hChan      :lower channel
* \param[in]        hAppChan   :upper channel
* \param[in]        wBitRate   :bitrate
* \return           BOOL32, TRUE/FALSE
*/
typedef BOOL32 (PROTO_CALLBACK* CBFlowControl)( HMDLCALL hCall, HMDLAPPCALL hAppCall, HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan, u16 wBitRate);

/**
* \brief            sip register result callback
* \param[in]        hReg               :lower reg handle
* \param[in]        hAppReg            :upper reg info
* \param[in]        emPARegResult      :reg result
* \param[in]        pbyBuf             :pbybuf里放入是否过NAT的判断结果，为一个BOOL32类型,TRUE为过NAT，FALSE为不过NAT
* \param[in]        nLen               :buffer length
* \return           BOOL32, TRUE/FALSE
*/
typedef BOOL32 (PROTO_CALLBACK* CBSipRegister)( HMDLREG hReg, HMDLAPPREG hAppReg, EmRegResult emPARegResult, const u8 *pbyBuf, const s32 nLen );

/**
* \brief            sip unregister result callback
* \param[in]        hReg               :lower reg handle
* \param[in]        hAppReg            :upper reg info
* \param[in]        emPARegResult      :unreg result
* \param[in]        pbyBuf             :如果从服务器收到注册失败回应，如果是重名，pbuf中依次放入emPARegisterNameDup，nsize,TPARegName\n
                                        如果是除了重名之外的失败， pBuf中放入emPARegisterFailed\n
                                        如果服务器不可达, pbuf中放入emPARegistrarUnReachable\n
                                        其他情况， pbuf中放入 emPAUnknownReason 
* \param[in]        nLen               :buffer length
* \return           BOOL32, TRUE/FALSE
*/
typedef BOOL32 (PROTO_CALLBACK* CBSipUnRegister)( HMDLAPPREG hAppReg, EmRegResult emPARegResult, const u8 *pbyBuf, const s32 nLen);

/**
* \brief            sip nonstd message callback
* \param[in]        hCall      :lower call handle
* \param[in]        hAppCall   :upper call handle
* \param[in]        pbyBuf     :nonstd message buffer
* \param[in]        nBufLen    :bufer length
* \return           BOOL32, TRUE/FALSE
*/
typedef BOOL32 (PROTO_CALLBACK* CBSipNonStdMsg)( HMDLCALL hCall, HMDLAPPCALL hAppCall, const u8 *pbyBuf, const s32 nBufLen );

/**
* \brief            get reg info callback
* \param[in]        nAppId      :app id
* \param[in]        pbyBuf      :reg info buffer:TPARegPackInfo,EmPAGetRegInfoType,TPARegInfo
* \param[in]        nLen        :buffer length
* \param[in]        byVersion   :version id
* \return           BOOL32, TRUE/FALSE
*/
typedef BOOL32 (PROTO_CALLBACK* CBGetRegInfoAck)(const s32 nAppId, const u8 *pbyBuf, const s32 nLen, const u8  byVersion );

/**
* \brief            fecc channel connected callback
* \param[in]        hCall             :lower call handle
* \param[in]        hAppCall          :upper call info
* \param[in]        ptFeccCap         :fecc channel connected info
* \return           BOOL32, TRUE/FALSE
*/
typedef BOOL32 (PROTO_CALLBACK* CBFeccChannelConnected)(HMDLCALL hCall, HMDLAPPCALL hAppCall, TFeccCapbility *ptFeccCap);

/**
* \brief            fecc message callback
* \param[in]        hCall             :lower call handle
* \param[in]        hAppCall          :upper call info
* \param[in]        tFeccStruct       :fecc struct
* \param[in]        tSrcLabel         :fecc src label
* \param[in]        tDstLabel         :fecc dst label
* \return           BOOL32, TRUE/FALSE
*/
typedef BOOL32 (PROTO_CALLBACK* CBFeccMsg)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMdlFeccStruct tFeccStruct, TMDLTERLABEL tSrcLabel, TMDLTERLABEL tDstLabel );

/**
* \brief            reg nsm callback
* \param[in]        nAppId      :app id
* \param[in]        pbyBuf      :reg nsm callbak
* \param[in]        nLen        :buffer length
* \return           BOOL32, TRUE/FALSE
*/
typedef BOOL32 (PROTO_CALLBACK* CBSipRegNSMAck)(const s32 nAppId, const u8 *pbyBuf, const s32 nLen);

/**
* \brief            dual incoming callback for bfcp
* \param[in]        hCall             :lower call handle
* \param[in]        hAppCall          :upper call info
* \param[in]        bNotify           :is notify
* \return           BOOL32, TRUE/FALSE
*/
typedef BOOL32 (PROTO_CALLBACK* CBSipDualIncomingBfcp)(HMDLCALL hCall, HMDLAPPCALL hAppCall, BOOL32 bNotify);

/**
* \brief            round trip time out
* \param[in]        hCall             :lower call handle
* \param[in]        hAppCall          :upper call info
*/
typedef BOOL32 (PROTO_CALLBACK* CBSipRoundTripTimeOut)(HMDLCALL hCall, HMDLAPPCALL hAppCall);

/**
* \brief            round trip time out and receive rtd
* \param[in]        hCall             :lower call handle
* \param[in]        hAppCall          :upper call info
*/
typedef BOOL32 (PROTO_CALLBACK* CBSipRoundTripTimeOutRecv)(HMDLCALL hCall, HMDLAPPCALL hAppCall);

//回调Peerip
/**
* \brief            callback peerip
* \param[in]        hCall             :lower call handle
* \param[in]        hAppCall          :upper call info
* \param[in]        pbyBuf			  :info buffer:peerip
* \param[in]        nLen			  :buffer length
*/
typedef BOOL32 (PROTO_CALLBACK* CBSipPeeripNotify)(HMDLCALL hCall, HMDLAPPCALL hAppCall,const u8 *pbyBuf, const s32 nLen);

/**
* \brief            main video recv channel callback In advance
* \param[in]        hCall             :lower call handle
* \param[in]        hAppCall          :upper call info
* \param[in]        pTVideoInfo       :main video info
* \param[in]        nSize             :channel connected size
* \return           BOOL32, TRUE/FALSE
*/
typedef BOOL32 (PROTO_CALLBACK* CBChannelInAdvance)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TChanConnectedInfo *pTVideoInfo,s32 nSize);


typedef BOOL32 (PROTO_CALLBACK* CBReInviteStatus)(HMDLCALL hCall, HMDLAPPCALL hAppCall,EmMdlReinvitestatus emstatus );

/// call back  function
typedef struct tagCallCBFunction
{
	CBNewCallIncoming      m_cbNewCallIncoming;     ///< new callincoming callback
	CBCallDisconnected     m_cbCallDisconnected;    ///< call disconnected  callback
	CBCallConnected        m_cbCallConnected;       ///< call connectd callback
	CBChannelConnected     m_cbChannelConnected;    ///< channel connected callback
	CBChannelDisconnected  m_cbChannelDisconnected; ///< channel disconnected callback
	CBFastUpdapte          m_cbFastUpdate;          ///< Fast Update callback 
	CBFlowControl          m_cbFlowControl;         ///< Flow Control callback
	CBSipDualIncoming      m_cbDualIncoming;        ///< dual incoming callback
	CBSipRegister          m_cbSipReg;              ///< sip register callback
	CBSipUnRegister        m_cbSipUnReg;            ///< sip unregister callback
	CBSipNonStdMsg         m_cbSipNonStdMsg;        ///< sip nonstd message callback
	CBGetRegInfoAck        m_cbSipGetRegInfoAck;    ///< get sip reg info ack callback
	CBFeccChannelConnected m_cbFeccChannelConnected;///< fecc channel callback
	CBFeccMsg			   m_cbFeccMsg;             ///< fecc message callback
	CBSipRegNSMAck         m_cbSipRegNSMAck;        ///< sip reg nsm ack callback
	CBSipDualIncomingBfcp  m_cbDualIncomingBfcp;    ///< dual incoming for bfcp callback
	CBSipRoundTripTimeOut  m_cbRoundTripTimeOut;    ///< round trip time out callback
	CBSipRoundTripTimeOutRecv  m_cbRoundTripTimeOutRecv;    ///< round trip time out and receive rtd callback
	CBSipReinviteRecive    m_cbReciveReinvite;      ///< receive reinvite callback
	CBSipPeeripNotify      m_cbPeeripNotify;		///< receive peerip callback
	CBChannelInAdvance     m_cbChannelInAdvance;    ///< main video in advance callback
	CBReInviteStatus       m_cbReInviteStatus;      ///< reinvite request/response callback
	/**
    * \brief            tagCallCBFunction init
    * \return           void.
    */
	void Clear()
	{
		m_cbNewCallIncoming		= NULL;
		m_cbCallConnected		= NULL;
		m_cbCallDisconnected	= NULL;
		m_cbChannelConnected	= NULL;
		m_cbChannelDisconnected = NULL;
		m_cbFastUpdate			= NULL;
		m_cbFlowControl			= NULL;
		m_cbDualIncoming		= NULL;
		m_cbSipReg				= NULL;
		m_cbSipUnReg			= NULL;
		m_cbSipNonStdMsg		= NULL;
		m_cbSipGetRegInfoAck	= NULL;
		m_cbFeccChannelConnected= NULL;
		m_cbFeccMsg				= NULL;
		m_cbSipRegNSMAck		= NULL;
		m_cbDualIncomingBfcp	= NULL;
		m_cbRoundTripTimeOut    = NULL;
		m_cbRoundTripTimeOutRecv  = NULL;
		m_cbReciveReinvite      = NULL;
		m_cbPeeripNotify        = NULL;
		m_cbChannelInAdvance    = NULL;
		m_cbReInviteStatus      = NULL;
	}

	/**
    * \brief            tagCallCBFunction Constructor
    * \return           void.
    */
	tagCallCBFunction()
	{
		Clear();
	}
}TCallCBFunction;

/// module cert config
typedef struct tagModuleCertCfg
{
	s8      m_achCACertFile[MAX_FILE_PATH_LEN]; ///< 载入的CA证书文件，如果启用校验，CACertFile和CACertPath有一个即可。
	s8      m_achCACertPath[MAX_FILE_PATH_LEN]; ///< 载入的CA证书目录，如果启用校验，CACertFile和CACertPath有一个即可。
	s8      m_achCertFile[MAX_FILE_PATH_LEN];   ///< 载入的证书文件，服务端需设置，客户端选择性设置。
	s8      m_achKeyFile[MAX_FILE_PATH_LEN];    ///< private key，服务端需设置，客户端选择性设置。
	s8		m_achPassword[MAX_SIP_PASSWORD_LEN];///< Password to open private key.
}TModuleCertCfg;

/// module tls congif
typedef struct tagModuleTlsCfg
{
	TModuleCertCfg m_atCertCfg[MAX_CERTICATE_NUM];    ///< cert config array
	u16            m_wLocalTlsPort;		              ///< 本地tls侦听端口,defult：5061
	s8             m_achDevId[MAX_DEVID_LEN];         ///< devid for qt tls  

	/**
	* \brief            sipmodule tls verify callback
	* \param[in]        bVerifyServer  :TRUE -> vertify server,FALSE -> vertify client
	* \param[in]        nVerifyStatus  :vertify status
	* \param[in]        Cert           :cert string
	* \param[in]        dwCertLen      :cert string length
	* \return           BOOL32, TRUE/FALSE
	*/
	BOOL32 (PROTO_CALLBACK* cbCertForVerify)(BOOL32 bVerifyServer, s32 nVerifyStatus, const s8 *Cert, u32 dwCertLen);
    
	/**
	* \brief            sipmodule tls verify callback
	* \param[in]        nStatus  :cert load failed status
	* \return           BOOL32, TRUE/FALSE
	*/
	BOOL32 (PROTO_CALLBACK* cbCertLoadFailedStatus)(s32 nStatus);

	/**
	* \brief            call back to notify upper to create a qt session
	* \param[in]        pSession  :The session's handle after be created
	                    args:some args to create session
	* \return           s32, status code
	*/
	s32 (PROTO_CALLBACK* cbCreateQTSession)(void *args, void** pSession);

	/**
	* \brief            call back to notify upper to Destroy a qt session
	* \param[in]        pSession  :The session's handle after be created
	                    args:some args to Destroy session
	* \return           s32, status code
	*/
	s32 (PROTO_CALLBACK* cbDestroyQTSession)(void *args, void* pSession);

	/**
	* \brief            call back to upper to get qt key
	* \param[in]        pSession  :The session's handle after be created
	                    pLocalDevId:local devid
						pPeerDevId:peer devid
						qk:INOUT,qt key
	* \return           s32, qt key len if success
	*/
	s32 (PROTO_CALLBACK* cbGetQTKey)(void* pSession, const s8* pLocalDevId, const s8 *pPeerDevId, u8* pbyQtKey, u32 dwMaxQTKeyLen, BOOL32 isClient);

	/**
    * \brief            tagModuleTlsCfg Constructor
    * \return           void.
    */
	tagModuleTlsCfg()
	{
		Clear();
	}

	/**
    * \brief            tagModuleTlsCfg init
    * \return           void.
    */
	void Clear()
	{
		memset(this , 0 , sizeof(tagModuleTlsCfg) );
		cbCertForVerify        = NULL;
		cbCertLoadFailedStatus = NULL;
		cbCreateQTSession      = NULL;
		cbDestroyQTSession     = NULL;
		cbGetQTKey             = NULL;
		m_wLocalTlsPort        = 5061;
	}
}TModuleTlsCfg;

typedef struct tagModuleLogCfg
{
	s8 m_achLogPath[LOG_LOGPATH_LENGTH];			///< pfc log path
	u32 m_dwMaxSize;								//pfc log  size(KB)
	u32 m_dwMaxfiles;								//pfc file number
	void clear()
	{
		MEMSET_CAST(m_achLogPath,0, LOG_LOGPATH_LENGTH);
		m_dwMaxSize = 0;
		m_dwMaxfiles = 0;
	}
	tagModuleLogCfg()
	{
		clear();
	}
}TModuleLogCfg;

/// Module Config for init stack
typedef struct tagSipModuleCfg
{
	s32 m_nsipServiceAppId;                     ///< Service模块AppId
	s32 m_nsipStackinAppId;                     ///< Stackin模块AppId
	s32 m_nsipStackoutAppId;                    ///< Stackout模块AppId

	emModuleEndpointType m_emEndpointType;  	///< Endpoint类型 MT、CNS、UMS
	u16 m_wTotalCallNum;	                    ///< 最大呼叫数
	u16 m_wTotalRegNum;		                    ///< 最大注册个数
	u32	m_dwKeepAliveTime;	                    ///< 心跳检测间隔（second）
	u32	m_dwCallingTimeOut;	                    ///< The time of calling timeout（second）
	u32	m_dwMaxSendRecvBufferSize;	            ///< 套接字发送接收缓冲大小(暂时使用默认值)
	s32	m_nProductIdSize;                       ///< product id size
	u8 m_abyProductId[MAX_LEN_PRODUCT_ID];	    ///< 产品号
	s32	m_nVerIdSize;                           ///< Version id size
	u8 m_abyVersionId[MAX_LEN_VERSION_ID];	    ///< 版本号

	BOOL32 m_bSendRecv;                      	///< sip通道属性是否为sendrecv
	BOOL32 m_bSendRecvWithCommonCap;	        ///< sip能力是否取交集
	BOOL32 m_bAutoAnswerFCS;	                ///< BFCP server收到bfcp请求消息是否自动回复
	BOOL32 m_bCompareCapsetInOrder;	            ///< sip能力集比较是否采用顺序比较（默认采用类二分查找算法比较）

	BOOL32 m_bUseTLS;		                    ///< 是否启用TLS，如果启用则tls端口默认是tcp+1(5061)
	BOOL32 m_bUseTLSDefConfig;	                ///< 是否启用TLS Default Config
	TModuleTlsCfg m_tModuleTlsCfg;              ///< TLS配置信息

	TCallCBFunction m_tCallCBFuntion;           ///< 回调功能函数

	TSipTsxTimeout	m_tSipTsxTimeout;           ///< Transaction Timer超时设置

	u16		m_wPortRangeStart;                  ///< tcp or tls port range must be assigned by business, or random allocation
	u16		m_wPortRangeEnd;                    ///< tcp or tls port range must be assigned by business, or random allocation

	BOOL32     m_bIfUseIpv6;                       ///< whether to use ipv6,default false
	/// 本端地址ipv6.网络序 only fe80::,if ipv6 addr is 0,will bind addr_any
	///< if ipv6 Scopeid is 0,then ipv6 addr mut be global address
	PFC_IPADDR m_tLocalAddr6;                   ///< local address of ipv6, port is default 5060
	PFC_IPADDR m_tLocalAddr4;                   ///< local address of ipv4, port is default 
	ALL_LOG_CALlBACK  m_fpLogCB;				///< add callback function for print
	TModuleLogCfg m_tSipLog;                    ///< Let the business set the PfcOpenLogFile parameters
	/**
    * \brief            tagSipModuleCfg Constructor
    * \return           void.
    */
	tagSipModuleCfg()
	{
		m_nsipServiceAppId = -1;
		m_nsipStackinAppId = -1;
		m_nsipStackoutAppId= -1;
		m_emEndpointType  = emModuletypeBegin;
		m_wTotalCallNum   = MAX_INSTANCE_PROTOCAL;
		m_wTotalRegNum    = MAX_INSTANCE_PROTOCAL;
		
		m_dwKeepAliveTime = SIP_DEFAULT_KEEPALIVE_INTERVAL;
		m_dwCallingTimeOut= SIP_DEFAULT_CALLINGTIMEOUT;
		m_dwMaxSendRecvBufferSize = S2H_DEFAULT_MAXSENDRECVBUFFERSIZE;
		m_nProductIdSize  = 0;
		m_nVerIdSize      = 0;
		MEMSET_CAST(m_abyProductId, 0, MAX_LEN_PRODUCT_ID);
		MEMSET_CAST(m_abyVersionId, 0, MAX_LEN_VERSION_ID);
		m_bSendRecv = FALSE;
		m_bSendRecvWithCommonCap = FALSE;
		m_bAutoAnswerFCS = FALSE;
		m_bCompareCapsetInOrder  = FALSE;

		m_tCallCBFuntion.Clear();
		m_tSipTsxTimeout.Clear();

		m_bUseTLS = FALSE;
		m_tModuleTlsCfg.Clear();

		m_wPortRangeStart = KDV_PORTRANGE_DEFAULT_START;
		m_wPortRangeEnd	  = KDV_PORTRANGE_DEFAULT_FINISH;

		m_bUseTLSDefConfig = FALSE;

		m_bIfUseIpv6 = FALSE;
		m_tLocalAddr6.Clear();
		m_tLocalAddr6.m_emType= PFC_TRANSPORT_TYPE_IPV6;
		m_tLocalAddr6.m_wPort = SIP_DEFAULT_SERVER_PORT;
		m_tLocalAddr4.Clear();
		m_tLocalAddr4.m_emType= PFC_TRANSPORT_TYPE_IP;
		m_tLocalAddr4.m_wPort = SIP_DEFAULT_SERVER_PORT;
		m_fpLogCB = NULL;
		m_tSipLog.clear();
	}
	
}TSipModuleCfg;

/// sipmodule call API
class PROTO_API CSipModule
{
public:
	
	 /**
	 * \brief            sip module init
	 * \param[in]        tCfg  :module config
	 * \return           BOOL32, TRUE/FALSE
	 */
	 static BOOL32 SipModuleInit( TSipModuleCfg &tCfg); 

	 /**
	 * \brief            sip module start recv
	 * \return           BOOL32, TRUE/FALSE
	 */
	 static BOOL32 SipModuleStart();

	 /**
	 * \brief            sip module stop recv
	 * \return           BOOL32, TRUE/FALSE
	 */
	 static BOOL32 SipModuleStop();

	 /**
	 * \brief            sip module exit function
	 * \return           BOOL32, TRUE/FALSE
	 */
	 static BOOL32 SipModuleExit();
	
	 /**
	 * \brief            sip make call
	 * \note             如果makeCall时tdual传下来， 就认为双流能力是tdual, 但是呼叫时双流能力不带过去，上层调用sendual才发双流过去， 就不回调dualincoming, 只回调channelconnected,和disconnected
	 * \param[in]        hCall            :call handle
	 * \param[in]        ptModParam       :call info
	 * \param[in]        bInviteWithSDP   :is invite with sdp
	 * \param[in]        bInviteWithDual  :is invite with dual
	 * \param[in]        bInviteWithBfcp  :is invite with bfcp
     * \param[in]        bAutoGetRegSrvIP :is auto get reg server ip
	 * \param[in]        ptMainCap        :main cap
	 * \param[in]        ptTPCap          :TP cap
	 * \param[in]        ptDualCap        :dual cap
	 * \param[in]        ptBfcpCap        :bfcp cap
	 * \param[in]        ptFeccCap        :fecc cap
	 * \return           BOOL32, TRUE/FALSE
	 */
	 static BOOL32 SipModuleMakeOutgoingCall(
				HMDLAPPCALL hAppCall, 
				TModuleCallInfo *ptModParam, 
				BOOL32 bInviteWithSDP = TRUE,
				BOOL32 bInviteWithDual = FALSE,
				BOOL32 bInviteWithBfcp = FALSE,
				BOOL32 bAutoGetRegSrvIP = FALSE,
				TMdlCallCap *ptMainCap = NULL,
				TMdlTPCap *ptTPCap = NULL,  
				TDualCapList *ptDualCap = NULL,
				TBfcpCapSet *ptBfcpCap = NULL, 
				TFeccCapbility *ptFeccCap = NULL
				);

	 /**
	 * \brief            sip answer call
	 * \param[in]        hCall            :lower call handle
	 * \param[in]        hAppCall         :upper call info
	 * \param[in]        bInviteWithDual  :is answer with dual
	 * \param[in]        bInviteWithBfcp  :is answer with bfcp
	 * \param[in]        ptModParam       :call info
	 * \param[in]        ptMainCap        :main cap
	 * \param[in]        ptTPCap          :TP cap
	 * \param[in]        ptDualCap        :dual cap
	 * \param[in]        ptBfcpCap        :bfcp cap
	 * \param[in]        ptFeccCap        :fecc cap
	 * \return           BOOL32, TRUE/FALSE
	 */
	 static BOOL32 SipModuleCallAnswer(
				HMDLCALL hCall, 
				HMDLAPPCALL hAppCall, 
				BOOL32 bInviteWithDual = FALSE,
				BOOL32 bInviteWithBfcp = FALSE,
				TModuleCallInfo *ptModParam = NULL, 
				TMdlCallCap *ptMainCap = NULL,
				TMdlTPCap *ptTPCap = NULL,  
				TDualCapList *ptDualCap = NULL,
				TBfcpCapSet *ptBfcpCap = NULL, 
				TFeccCapbility *ptFeccCap = NULL
				);

	 /**
	 * \brief            sip ack call
	 * \param[in]        hCall            :lower call handle
	 * \param[in]        hAppCall         :upper call info
	 * \param[in]        bInviteWithDual  :is answer with dual
	 * \param[in]        bInviteWithBfcp  :is answer with bfcp
	 * \param[in]        ptModParam       :call info
	 * \param[in]        ptMainCap        :main cap
	 * \param[in]        ptDualCap        :dual cap
	 * \param[in]        ptBfcpCap        :bfcp cap
	 * \param[in]        ptFeccCap        :fecc cap
	 * \return           BOOL32, TRUE/FALSE
	 */
	 static BOOL32 SipModuleCallAck(
				HMDLCALL hCall, 
				HMDLAPPCALL hAppCall,                                
				BOOL32 bInviteWithDual = FALSE,
				BOOL32 bInviteWithBfcp = FALSE,
				TMdlCallCap *ptMainCap = NULL,
				TDualCapList *ptDualCap = NULL,
				TBfcpCapSet *ptBfcpCap = NULL, 
				TFeccCapbility *ptFeccCap = NULL
				);
	 /**
	 * \brief            sip reject call
	 * \param[in]        hCall            :lower call handle
	 * \param[in]        hAppCall         :upper call info
	 * \param[in]        emReason         :reject call reason
	 * \return           BOOL32, TRUE/FALSE
	 */
	 static BOOL32 SipModuleCallReject(HMDLCALL hCall, HMDLAPPCALL hAppCall, EmModuleCallDisconnectReason emReason);   

	 /**
	 * \brief            sip hangup call
	 * \param[in]        hCall            :lower call handle
	 * \param[in]        hAppCall         :upper call info
	 * \param[in]        emReason         :hangup call reason
	 * \return           BOOL32, TRUE/FALSE
	 */
	 static BOOL32 SipModuleCallHangup(HMDLCALL hCall, HMDLAPPCALL hAppCall, EmModuleCallDisconnectReason emReason);   

public:
	/**
	 * \brief            close channel
	 * \param[in]        hCall            :lower call handle
	 * \param[in]        hAppCall         :upper call info
	 * \param[in]        ahChan           :channel array
	 * \param[in]        ahAppChan        :app channel array
	 * \param[in]        bySize           :channel size
	 * \param[in]        emReason         :close channel reason
	 * \return           BOOL32, TRUE/FALSE
	 */
	static BOOL32	CloseChannel(HMDLCALL hCall , HMDLAPPCALL hAppCall,  HMDLCHANNEL ahChan[], HMDLAPPCHANNEL ahAppChan[], u8 bySize, EmChannelReason emReason = emModuleChannelDisconnectNormal );   
	
	/**
	* \brief            change channel
	* \param[in]        hCall            :lower call handle
	* \param[in]        hAppCall         :upper call info
	* \param[in]        ptConnectedInfo  :channel connected info
	* \param[in]        bChangeAddress   :is change address
	* \return           BOOL32, TRUE/FALSE
	*/
	static BOOL32	ChangeChannel(HMDLCALL hCall, HMDLAPPCALL hAppCall, TChanConnectedInfo *ptConnectedInfo, s32 nSize, BOOL32 bChangeAddress = FALSE );

	/**
	* \brief            use to change srtp key after call connect
	* \param[in]        hCall            :lower call handle
	* \param[in]        hAppCall         :upper call info
	* \param[in]        ptMainCap        :main cap
	* \param[in]        ptDualCap        :dual cap
	* \param[in]        ptBfcpCap        :bfcp cap
	* \param[in]        ptFeccCap        :fecc cap
	* \return           BOOL32, TRUE/FALSE
	*/
	static BOOL32   SipModuleSendReinvite(HMDLCALL hCall , HMDLAPPCALL hAppCall, TMdlCallCap *ptMainCap, TDualCapList *ptDualCap,TBfcpCapSet *ptBfcpCap, TFeccCapbility *ptFeccCap);

	/**
	* \brief            use to Answer change srtp key after call connect
	* \param[in]        hCall            :lower call handle
	* \param[in]        hAppCall         :upper call info
	* \param[in]        ptMainCap        :main cap
	* \param[in]        ptDualCap        :dual cap
	* \param[in]        ptBfcpCap        :bfcp cap
	* \param[in]        ptFeccCap        :fecc cap
	* \return           BOOL32, TRUE/FALSE
	*/
	static BOOL32   SipModuleAnswerReinvite(HMDLCALL hCall , HMDLAPPCALL hAppCall, TMdlCallCap *ptMainCap, TDualCapList *ptDualCap,TBfcpCapSet *ptBfcpCap, TFeccCapbility *ptFeccCap, EmMdlReinvitestatus emReason);

	/**
	* \brief            sip register
	* \param[in]        hReg            :lower reg handle
	* \param[in]        hAppReg         :upper reg handle
	* \param[in]        ptRegInfo       :register info
	* \return           BOOL32, TRUE/FALSE
	*/
	static BOOL32	SipModuleRegister(HMDLREG hReg, HMDLAPPREG hAppReg, TRegistReq* ptRegInfo);

	/**
	* \brief            sip unregister
	* \param[in]        hReg            :lower reg handle
	* \param[in]        hAppReg         :upper reg handle
	* \return           BOOL32, TRUE/FALSE
	*/
	static BOOL32	SipModuleUnregister(HMDLREG hReg, HMDLAPPREG hAppReg);

	/**
	* \brief            sip tls Renegotiate after register successed
	* \param[in]        hReg            :lower reg handle
	* \param[in]        hAppReg         :upper reg handle
	* \return           BOOL32, TRUE/FALSE
	*/
	static BOOL32   SipModuleTlsRenegotiate(HMDLREG hReg, HMDLAPPREG hAppReg);

	/**
	* \brief            flow control callback
	* \param[in]        hCall      :lower call handle
	* \param[in]        hAppCall   :upper call handle
	* \param[in]        hChan      :lower channel
	* \param[in]        hAppChan   :upper channel
	* \param[in]        wBitRate   :bitrate
	* \return           BOOL32, TRUE/FALSE
	*/
	static BOOL32	FlowCtrl(HMDLCALL hCall , HMDLAPPCALL hAppCall , HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan, u16 wBitrate);

	/**
	* \brief            fast update  callback
	* \param[in]        hCall      :lower call handle
	* \param[in]        hAppCall   :upper call handle
	* \param[in]        hChan      :lower channel
	* \param[in]        hAppChan   :upper channel
	* \return           BOOL32, TRUE/FALSE
	*/
	static BOOL32	FastUpdate(HMDLCALL hCall , HMDLAPPCALL hAppCall , HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan);

	/**
	* \brief            fast update  without id
	* \param[in]        hCall      :lower call handle
	* \param[in]        hAppCall   :upper call handle
	* \return           BOOL32, TRUE/FALSE
	*/
	static BOOL32	FastUpdateWithoutID(HMDLCALL hCall , HMDLAPPCALL hAppCall);

	/**
	* \brief            send fecc message
	* \param[in]        hCall       :lower call handle
	* \param[in]        hAppCall    :upper call handle
	* \param[in]        tFeccAction :fecc action
	* \param[in]        tSrcLabel   :src label
	* \param[in]        tDstLabel   :dst label
	* \return           BOOL32, TRUE/FALSE
	*/
	static BOOL32	SipModuleSendFeccMsg( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMdlFeccStruct tFeccAction, TMDLTERLABEL tSrcLabel, TMDLTERLABEL tDstLabel );

	/**
	* \brief            set fecc stream id
	* \param[in]        hCall             :lower call handle
	* \param[in]        hAppCall          :upper call handle
	* \param[in]        tFeccStreamIdInfo :fecc stream id info
	* \return           BOOL32, TRUE/FALSE
	*/
	static BOOL32	SipModuleSetFeccStreamId( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMdlFeccStreamIdInfo tFeccStreamIdInfo );

	/**
	* \brief            set fecc keep alive
	* \param[in]        hCall             :lower call handle
	* \param[in]        hAppCall          :upper call handle
	* \param[in]        dwKeepAliveIp     :keep alive ip
    * \param[in]        wKeepAlivePort    :keep alive port
    * \param[in]        nInterval         :keep alive nInterval
	* \return           BOOL32, TRUE/FALSE
	*/
	static BOOL32	SipModuleSetFeccKeepAlive( HMDLCALL hCall, HMDLAPPCALL hAppCall, u32 dwKeepAliveIp, u16 wKeepAlivePort, s32 nInterval);

	/**
	* \brief            sip module send dual
	* \param[in]        hCall             :lower call handle
	* \param[in]        hAppCall          :upper call handle
	* \note             发送双流,添加通道，上层业务控制, 如果makecall时双流能力带下来，sendDual发送的是makecall带下来的双流能力
    * \param[in]        ptDual            :dual cap list
	* \return           BOOL32, TRUE/FALSE
	*/
	static BOOL32	SipModuleSendDual(HMDLCALL hCall , HMDLAPPCALL hAppCall, TDualCapList *ptDual = NULL);    

	/**
	* \brief            sip module answer dual
	* \param[in]        hCall             :lower call handle
	* \param[in]        hAppCall          :upper call handle
	* \note             发送双流,添加通道，上层业务控制, 如果makecall时双流能力带下来，sendDual发送的是makecall带下来的双流能力
	* \param[in]        ptDual            :dual cap list
    * \param[in]        bSuc              :bSuc为TRUE, 有双流， bSuc为False, 拒绝双流
	* \return           BOOL32, TRUE/FALSE
	*/
	static BOOL32	SipModuleAnswerDual(HMDLCALL hCall , HMDLAPPCALL hAppCall, BOOL32 bSuc, TDualCapList *ptDual = NULL);  

	/**
	* \brief            sip module stop dual
	* \param[in]        hCall             :lower call handle
	* \param[in]        hAppCall          :upper call handle
	* \param[in]        emReason          :dual channel disconnect reason
    * \param[in]        bSuc              :bSuc为TRUE, 有双流， bSuc为False, 拒绝双流
	* \return           BOOL32, TRUE/FALSE
	*/
	static BOOL32	SipModuleStopDual(HMDLCALL hCall , HMDLAPPCALL hAppCall, EmChannelReason emReason = emModuleChannelDisconnectNormal ); 

	/**
	* \brief            Independent SIP conference-create related NON-STANDARD messages 
	* \note             Data format: XML must have ConfNSM node right under the root node
	* \param[in]        tSIPRegNSM             :Contains with the IP address info and NONSTANDARD message type
	* \param[in]        pchNSMRegXML           :Detail XML for the message
	* \param[in]        nBytes                 :XML content length
    * \param[in]        hReg                   :Register handle which you get when you succeeded to register to the registrar
	* \param[in]        nAppID                 :Upper layer ID, same with interface SipModuleGetRegInfoReq(). *Legacy issue, leaving it only to keep interface compatibility with old TPS interfaces;
	* \return           BOOL32, TRUE/FALSE
	*/
	static BOOL32	SipModuleSendRegNSM(TSIPRegNSM tSIPRegNSM, const s8* pchNSMRegXML, s32 nBytes, HMDLREG hReg, s32 nAppID);

	/**
	* \brief            send dtmf info
	* \param[in]        hCall             :lower call
	* \param[in]        hAppCall          :upper call
	* \param[in]        pbyBuf            :dtmf info buffer
    * \param[in]        wLen              :buffer length
	* \return           BOOL32, TRUE/FALSE
	*/
	static BOOL32	SipModuleSendDtmfInfo(HMDLCALL hCall, HMDLAPPCALL hAppCall, u8 *pbyBuf, u16 wLen);

	/**
	* \brief            stop round trip
	* \param[in]        hCall             :lower call
	* \param[in]        hAppCall          :upper call
	* \return           BOOL32, TRUE/FALSE
	*/
	static BOOL32   SipModuleStopRoundTrip(HMDLCALL hCall, HMDLAPPCALL hAppCall);

public:
	/**
	* \brief            send register for tp
	* \param[in]        hReg             :lower reg handle
	* \param[in]        hAppReg          :upper reg handle
	* \param[in]        tPARegCfg        :注册多个别名，非标注册，通过xml注册
	* \return           BOOL32, TRUE/FALSE
	*/
	static BOOL32	SipModuleRegisterTP		(HMDLREG hReg, HMDLAPPREG hAppReg, TPARegCfg tPARegCfg); 

	/**
	* \brief            send nonstd message for tp
	* \param[in]        hCall             :lower call handle
	* \param[in]        hAppCall          :upper call handle
	* \param[in]        pbyBuf            :nonst message buffer
	* \param[in]        nBufLen           :buffer length
	* \return           BOOL32, TRUE/FALSE
	*/
	static BOOL32	SipModuleSendNonStdMsg	(HMDLCALL hCall , HMDLAPPCALL hAppCall,  u8 *pbyBuf,  s32 nBufLen); //网真发送NonStandard-conf消息

	/**
	* \brief            sip module get tls situation from info
	* \param[in]        hCall                     :lower call handle
	* \param[in]        pbTls                     :is tls
	* \param[in]        pdwPeerCertificatStatus   :peer certificat status
	* \param[in]        pnCipher                  :cipher
	* \return           BOOL32, TRUE/FALSE
	*/
	static BOOL32	SipModuleGetTlsSituationFromInfo(IN HMDLCALL hCall , OUT BOOL32 *pbTls, OUT u32 *pdwPeerCertificatStatus,  OUT s32 *pnCipher); 

	/**
	* \brief            get register info request
	* \param[in]        nAppId             :app id
	* \param[in]        tPAGetRegInfo      :reg info struct
	* \param[in]        hReg               :lower reg handle
	* \return           BOOL32, TRUE/FALSE
	*/
	static BOOL32	SipModuleGetRegInfoReq	(s32 nAppId, TPAGetRegInfo tPAGetRegInfo, HMDLREG hReg = (HMDLREG)-1);	


	/**
	* \brief            set nat ip,for ipv4 or ipv6
	* \param[in]        tNatIp             :nat ip
	* \return           BOOL32, TRUE/FALSE
	*/
	static BOOL32	SipModuleSetNatIp		(PFC_IPADDR tNatIp);

	/**
	* \brief            send info without call
	* \param[in]        TSipNonStdData     :nonstd data
	* \param[in]        pchXML             :xml buffer
	* \param[in]        wBytes             :xml length
	* \return           BOOL32, TRUE/FALSE
	*/
	static BOOL32	SipModuleSendInfoOutCall	(TSipNonStdData tSipData, const s8* pchXML, u16 wBytes);

	/**
	* \brief            Tls qt get key result notify
	* \param[in]        phSession       :qt session
	* \param[in]        args            :ssock
	* \param[in]        result          :0 is failed; >0 is success
	* \return           status, pj_success is success.
	*/
	static BOOL32 SipModuleQtGetKeyResult(void *phSession, void* args, u32 result);

private:
	/**
	* \brief            pfc post
	* \param[in]        cMsg             :message body
	* \return           BOOL32, TRUE/FALSE
	*/
	static	BOOL32	Post( CModuleMsg &cMsg );

private:
	static	u16		m_wSipServiceAppId;  ///< service app id
};

/// sip print flag
enum emSIPPrintFlag
{
	emSIPPrintDefault = 0,	///< 0,不分callid alias
	emSIPPrintByCallID,		///< 1,按callid 打印 
	emSIPPrintByAlias,		///< 2,按alias打印
};

/// sip print
typedef struct tagTSipPrint
{
	emModuleType m_emSipModule;              ///< sipmodule type
	s32 m_nLevel;                            ///< log level
	s8  m_achAlias[MAX_LEN_CALL_ALIAS + 1];  ///< log alias
	u16 m_wCallId;                           ///< log call id 
	emSIPPrintFlag m_emFlag;                 ///< print flag
	EmLogFilter m_emLogFilter;            ///< log filter

	/**
    * \brief            tagTSipPrint Constructor
    * \return           void.
    */
	tagTSipPrint()
	{
		m_emSipModule	= emModuleService ;
		m_nLevel		= LOG_OFF;					 
		MEMSET_CAST(m_achAlias, 0, sizeof(m_achAlias));
		m_wCallId		= 0;
		m_emFlag		= emSIPPrintDefault;
		m_emLogFilter	= emLogNull;
	}
}TSipPrint;

/**
* \brief            set module log alias
* \param[in]        pAlias             :call alias
* \return           void.
*/
PROTO_EXTERN_API void setmlogalias(s8 *pAlias); 
/**
* \brief            set module log callid
* \param[in]        wCallId            :call id
* \return           void.
*/
PROTO_EXTERN_API void setmlogcallid(u16 wCallId);
/**
* \brief            sip module log on
* \param[in]        nModule            :log module
* \param[in]        nLevel             :log level
* \return           void.
*/
PROTO_EXTERN_API void sipmlog(s32 nModule, s32 nLevel = 0);

/**
* \brief            sip module help
* \return           void.
*/
PROTO_EXTERN_API void sipmhelp();
//PROTO_EXTERN_API void kdvsipmodulehelp();

/**
* \brief            sip show call
* \return           void.
*/
PROTO_EXTERN_API void sipshowcall();
/**
* \brief            sip show call id
* \return           void.
*/
PROTO_EXTERN_API void sipshowcallid(u16 wCallid);
/**
* \brief            show sip modulever
* \return           void.
*/
//PROTO_EXTERN_API void sipmodulever();
PROTO_EXTERN_API void sipmver();

/**
* \brief            sip show reg
* \return           void.
*/
PROTO_EXTERN_API void sipshowreg();
/**
* \brief            sip module log to telnet or cmd
* \return           void.
*/
PROTO_EXTERN_API void sipmlogto(u8 byFilter);
/**
* \brief            uer register ip
* \param[in]        bUseRegistarIP            :is use register ip
* \return           void.
*/
PROTO_EXTERN_API void useregistarip(BOOL32 bUseRegistarIP);
/**
* \brief            sip module config on
* \param[in]        nType           :config type
* \return           void.
*/
PROTO_EXTERN_API void sipmconfig(s32 nType);

/**
* \brief            sip module printf
* \param[in]        emSipModule      :enum sip module
* \param[in]        nLevel           :sip moudle level
* \param[in]        pAlias           :alias
* \param[in]        wCallId          :call id
* \param[in]        pFormat          :print format
* \return           void.
*/
void SipmdlPrintf( emModuleType emSipModule, s32 nLevel, s8 *pAlias, u16 wCallId, const char* pFormat, ... );

/**
* \brief            print sip module config
* \return           void.
*/
PROTO_EXTERN_API void sipmconfigon();

/**
* @}
*/
#endif
