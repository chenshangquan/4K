/**
*   COPYRIGHT NOTICE
*   Copyright (C) 2018, KeDaCom
*   All right reserved
*   
*   @file        h323callstdstruct.h
*   @author      Sai
*   @version     V5.0_64bit
*   @date        2018-03-05
*   @brief       Provided messages struct for H323 protocol 
*   @details     
*/
#ifndef _H323CALLSTDSTRUCT_H
#define _H323CALLSTDSTRUCT_H

#include "protocolcommonpublic.h"
#include "kdv323common.h"
#include "kdvcapset.h"

/**当前平台所支持的列表查询能力*/
enum emPlatformCap
{
	KdvPlatformCapStart						= 0,
	KdvPlatformCapTerLIst					= 1,	/**< 在线终端列表 */
	KdvPlatformCapConfList					= 2,	/**< 会议列表 */
	KdvPlatformCapCreateConfwithTerlist	    = 3,	/**< 召集会商能力 */
	KdvPlatformCapJoinCofByConfList			= 4,	/**< 参加会商能力 */
	KdvPlatformCapGlobalAddrBook			= 5,	/**< 全局地址簿 */
	KdvPlatformCapVideoRecordBroadcast	  	= 6,	/**< 录播能力 */
	KdvPlatformCapEnd						= 7,
};

/**for PlatformCap Capability*/
typedef struct tagPlatformCap
{
	u32 m_dwCap;
	
	void Clear(){  m_dwCap = 0; } 

	BOOL32 SetAllCap( u32 dwCap );
	
	u32 GetAllCap()
	{
		return ntohl( m_dwCap );
	}

	BOOL32 AddCap( emPlatformCap emCap );

	BOOL32 RemoveCap( emPlatformCap emCap );

	BOOL32 IsSupport(emPlatformCap emCap );

}TPlatformCap;


/**for callmake error return */
enum CallMAkeErrReason 
{
    err_unknow				= -1,	/**< 未知原因 */
	err_full_call			= -2,	/**< 呼叫已满 */
	err_set_param			= -3,	/**< 适配层设置参数出错(包含地址) */
	err_null_ptr			= -4,	/**< 指针为NULL或指向的buffer大小不匹配 */	
	err_set_address			= -5,	/**<呼叫时协议栈内部判断地址设置有误 */	
	err_already_setup		= -6,	/**< 已经呼叫过 */	
	err_autoRas_PrepareARQ	= -7,	/**< 发送ARQ失败 */
	err_autoRas_Register	= -8,   /**< 注册失败 */
	err_Q931_Connect		= -9,	/**< Q931呼叫失败 */
	err_iptype_notmatch		= -10,	/**< 呼叫源地址和目的地址类型不一致(多宿IP下) */
};


#ifndef CM_H
typedef enum
{
	cmCreate,
	cmJoin,
	cmInvite,
	cmCapabilityNegotiation,
	cmCallIndependentSupplementaryService,
	cmLastCG
}cmConferenceGoalType;

typedef enum
{
    cmCallTypeP2P,
	cmCallTypeOne2N,
	cmCallTypeN2One,
	cmCallTypeN2Nw
}cmCallType;

/**Equipment type*/
typedef enum
{
    cmEndpointTypeTerminal,
	cmEndpointTypeGateway,
	cmEndpointTypeMCU,
	cmEndpointTypeGK,
	cmEndpointTypeUndefined,
	cmEndpointTypeSET
}cmEndpointType;

/**RAS Disengage Reason*/
typedef enum
{
    cmRASDisengageReasonForcedDrop,
	cmRASDisengageReasonNormalDrop,
	cmRASDisengageReasonUndefinedReason
}cmRASDisengageReason;

/**RAS Unreg Reason*/
typedef enum
{
    cmRASUnregReasonReregistrationRequired,
	cmRASUnregReasonTtlExpired,
	cmRASUnregReasonSecurityDenial,
	cmRASUnregReasonUndefinedReason,
	cmRASUnregReasonMaintenance
}cmRASUnregReason;

/**RAS Reason*/
typedef enum
{
    cmRASReasonResourceUnavailable              = 0,		/**< GRJ, RRJ, ARJ, LRJ - gatekeeper resources exhausted */
    cmRASReasonInsufficientResources            = 1,		/**< BRJ */
    cmRASReasonInvalidRevision                  = 2,		/**< GRJ, RRJ, BRJ */
    cmRASReasonInvalidCallSignalAddress         = 3,		/**< RRJ */
    cmRASReasonInvalidRASAddress		        = 4,		/**< RRJ - supplied address is invalid */
    cmRASReasonInvalidTerminalType              = 5,		/**< RRJ */
    cmRASReasonInvalidPermission                = 6,		/**< ARJ - permission has expired */
															/**< BRJ - true permission violation */										 			/* LRJ - exclusion by administrator or feature */
    cmRASReasonInvalidConferenceID              = 7,		/**< BRJ - possible revision */
    cmRASReasonInvalidEndpointID                = 8,		/**< ARJ */
    cmRASReasonCallerNotRegistered              = 9,		/**< ARJ */
    cmRASReasonCalledPartyNotRegistered         = 10,	/**< ARJ - can't translate address */
    cmRASReasonDiscoveryRequired                = 11,	/**< RRJ - registration permission has aged */
    cmRASReasonDuplicateAlias                   = 12,	/**< RRJ - alias registered to another endpoint */
    cmRASReasonTransportNotSupported            = 13,	/**< RRJ - one or more of the transports */
    cmRASReasonCallInProgress                   = 14,	/**< URJ */
    cmRASReasonRouteCallToGatekeeper            = 15,	/**< ARJ */
    cmRASReasonRequestToDropOther               = 16,	/**< DRJ - can't request drop for others */
    cmRASReasonNotRegistered                    = 17,	/**< DRJ, LRJ, INAK - not registered with gatekeeper */
    cmRASReasonUndefined                        = 18,	/**< GRJ, RRJ, URJ, ARJ, BRJ, LRJ, INAK */
    cmRASReasonTerminalExcluded                 = 19,	/**< GRJ - permission failure, not a resource failure */
    cmRASReasonNotBound                         = 20,	/**< BRJ - discovery permission has aged */
    cmRASReasonNotCurrentlyRegistered           = 21,	/**< URJ */
    cmRASReasonRequestDenied                    = 22,	/**< ARJ - no bandwidrg available */
														/**< LRJ - cannot find location */
    cmRASReasonLocationNotFound                 = 23,	/**< LRJ - cannot find location */
    cmRASReasonSecurityDenial                   = 24,	/**< GRJ, RRJ, URJ, ARJ, BRJ, LRJ, DRJ, INAK */
    cmRASReasonTransportQOSNotSupported         = 25,	/**< RRJ */
    cmRASResourceUnavailable                    = 26,	/**< Same as cmRASReasonResourceUnavailable */
    cmRASReasonInvalidAlias                     = 27,	/**< RRJ - alias not consistent with gatekeeper rules */
    cmRASReasonPermissionDenied                 = 28,	/**< URJ - requesting user not allowed to unregister specified user */
    cmRASReasonQOSControlNotSupported           = 29,	/**< ARJ */
    cmRASReasonIncompleteAddress                = 30,	/**< ARJ, LRJ */
    cmRASReasonFullRegistrationRequired         = 31,	/**< RRJ - registration permission has expired */
    cmRASReasonRouteCallToSCN                   = 32,	/**< ARJ, LRJ */
    cmRASReasonAliasesInconsistent              = 33,	/**< ARJ, LRJ - multiple aliases in request identify distinct people */
    cmRASReasonAdditiveRegistrationNotSupported = 34,	/**< RRJ */
    cmRASReasonInvalidTerminalAliases           = 35,	/**< RRJ */
    cmRASReasonExceedsCallCapacity              = 36,	/**< ARJ - destination does not have the capacity for this call */
    cmRASReasonCollectDestination               = 37,	/**< ARJ */
    cmRASReasonCollectPIN                       = 38,	/**< ARJ */
    cmRASReasonGenericData                      = 39,	/**< GRJ, RRJ, ARJ, LRJ */
    cmRASReasonNeededFeatureNotSupported        = 40,	/**< GRJ, RRJ, ARJ, LRJ */
    cmRASReasonUnknownMessageResponse           = 41,	/**< XRS message was received for the request */
    cmRASReasonHopCountExceeded                 = 42,	/**< LRJ */
}cmRASReason;

/**User Input Signal Rtp Struct*/
typedef struct
{
    int timestamp;      /**< -1 if optional; */
    int expirationTime; /**< -1 if optional;*/
    int logicalChannelNumber;
}cmUserInputSignalRtpStruct;

/**User Input Signal Struct*/
typedef struct
{
    char signalType;
    int duration;
    cmUserInputSignalRtpStruct cmUserInputSignalRtp;/**< if logicalchannel == 0 -optional*/
}cmUserInputSignalStruct;
#endif///CM_H没有包含cm.h

#ifndef CMCTRL_H
/**Capability Direction*/
typedef enum 
{
    cmCapReceive=1,
    cmCapTransmit=2,
    cmCapReceiveAndTransmit=3
} cmCapDirection;
#endif///CMCTRL_H 没有包含cm.h

/**Disconnect Reason*/
enum CallDisconnectReason 
{
	reason_busy					 = 1,
	reason_normal				 = 2,
	reason_rejected				 = 3,
	reason_unreachable			 = 4,
	reason_local				 = 5,
	reason_unknown				 = 6,
								 
	reason_nobandwidth			 = 7,		/**< ARQ拒绝或没有带宽 */
	reason_nopermission			 = 8,		/**< 被叫网守拒绝 */
	reason_unreachablegatekeeper = 9,		/**< 网守不可达for ARQ */
	reason_mcuoccupy			 = 10,      /**< 终端忙,带终端目前所在会议的级别及会议名称 */
	reason_reconnect			 = 11,      /**< 本端行政级别低，由远端自动发起重连 */
	reason_confholding			 = 12,      /**< 该MCU正在召开其它会议 */
	reason_hascascaded			 = 13,      /**< 该MCU已经被其它高级别MCU呼叫 */
								 
	reason_custom				 = 14,		/**< 两个字段u8+u8 = reason_custom + EmCallFailureReason 的非标形式 */
	reason_adaptivebusy			 = 15,      /**< 为AGW相关挂断原因增加处理代码 */
};

/**323非标挂断原因*/
enum EmCallFailureReason
{
	emCallFailureReasonBegin               = 0,

	emCallFailureReasonTimeOut             = 1,      /**< 呼叫超时 */
	emCallFailureReasonNoIdleVPU           = 2,      /**< 没有足够能力的空闲媒体处理器 */
	emCallFailureMinMediaConfMtNum         = 3,		 /**< 兼容2.6终端会议中呼叫点数已达上限 */
	emCallFailureReasonEncrypeErr          = 5,      /**< 与会议加密模式不符 */
	
	emCallFailureReasonMccDrop             = 6,      /**< 会控挂断 */
	emCallFailureReasonChairDrop           = 7,      /**< 主席挂断 */
	emCallFailureReasonMMcuDrop            = 8,      /**< 上级会议挂断 */
	emCallFailureReasonConfRelease         = 9,      /**< 会议结束挂断 */
	
	emDisconnectCustom_PeerInConf          = 10,     /**< 对端正在会议 */
	emDisconnectCustom_PeerInNoDisturb     = 11,     /**< 对端免打扰 */
	emDisconnectCustom_NotInPeerContact    = 12,     /**< 不在通讯录中 */
	emDisconnectCustom_PeerNoP2PPermission = 13,     /**< 对端无点对点权限 */
	emDisconnectCustom_PeerOnSleeping      = 14,     /**< 对端正在待机 */
	emDisconnectCustom_MaxMtNum            = 15,     /**< 会议中呼叫点数已达上限 */

	emCallFailureReasonConfReleaseOnlyOneMt=17,      /**< 仅一个在线终端自动结会-10分钟 */
	emDisconnectCustom_Exception           =18,      /**< 异常挂断 */
	emDisconnectCustom_Eviction			   = 19,     /**< 强拆方式主动退会 */
	emDisconnectCustom_ChannelNoAuth	   = 20,	 /**< 渠道产品未经授权 */
	emDisconnectCustom_OverMaxLicenseNum   = 21,     /**< 端口会议终端数量超过License授权点数 */
	emCallFailureReasonEnd,
};


/**Facility Reason*/
enum FacilityReason 
{
	routeToGK,				
	callForward,				
	routeToMC,
	confListChoice,
	startH245,
	forwardedelements,	/**For us*/
	undefined,			/**For Guoke or HuaWei*/
	unknown
};

enum RrqAuthAlgType
{
	emRrqAuthAlgTypeMD5 = 0,   /**Standard MD5*/
	emRrqAuthAlgTypeGuoKe,	   /**Only for guoke*/
	emRrqAuthAlgTypeSM4		   /**National secret*/
};
/**主从决定结果*/
enum MasterSlaveResult 
{
	msdse_master,		/**<本端为master*/
	msdse_slave,		/**<本端为slave */
    msdse_err = 0xff    
};

/**能力交换结果*/
enum CapExchangeResult 
{
	cese_accept,		/**<对端接受本端能力*/
	cese_reject,		/**<对端拒绝本端能力*/
    cese_err = 0xff
};

/**数据类型*/
enum  DataType 
{
	type_none = 0,
	type_audio,
	type_video,
	type_data,
};

#ifndef MCUCASC_ADAPTER_COMMON
#define MCUCASC_ADAPTER_COMMON

/**Judge Audio Type*/
#define PayloardIsAudioType( paylord )  \
( (emAudioTypeBegin < paylord && paylord < emAudioTypeEnd && paylord != emMpeg4 && paylord != emH262) )

/**Judge Video Type*/
#define PayloardIsVideoType( paylord )  \
( ( (emVideoTypeBegin < paylord && paylord < emVideoTypeEnd) || paylord == emMpeg4 || paylord == emH262) )

/**Judge Data Type*/
#define PayloardIsDataType( paylord )  \
( (emDataTypeBegin < paylord && paylord < emDataTypeEnd) )

#endif

/**呼叫相关的参数*/
enum CallParamType
{
	cpt_ConferenceGoalType,					/**<会议的目标类型 cmConferenceGoalType*/
	cpt_CallType,							/**<呼叫类型       cmCallType*/
	cpt_callId,								/**<呼叫ID		 char[16]*/
	cpt_callCrv,							/**<呼叫CRV		 int*/
	cpt_confId								/**<会议ID		 char[16]*/
};

/**终端类型值*/
typedef enum
{
	emMsMT			= 50,
	emMsMT_MC		= 70,
	emMsMCU			= 190,
	emMsActiveMC	= 240,
}emMsTerminalType;


//////////////////////////  会控消息处理以后的结构体  //////////////////
/**H239 Messages*/
typedef enum
{
    emH239InfoTypeInvalid		        = 0,

    emH239FlowControlReleaseRequest     = 1,
    emH239FlowControlReleaseResponse    = 2,
    emH239PresentationTokenRequest      = 3,
    emH239PresentationTokenResponse     = 4,
    emH239PresentationTokenRelease      = 5,
    emH239PresentationTokenIndicateOwner= 6,

    emH239InfoTypeEnd
}emH239InfoType;

/**Pic Style*/
typedef enum
{
	emStyle2p  = 0x07,
	emStyle3p  = 0x08,
	emStyle4p  = 0x00,
	emStyle6p  = 0x02,
	emStyle8p  = 0x04,
	emStyle9p  = 0x01,
	emStyle13p = 0x06,
	emStyle13  = 0x05,
	emStyle16p = 0x03,
	emStyleEnd
}emPicStyle;

/**log Channel Reject Cause*/
typedef enum
{
    emLogChanRejectUnspecified							= 0,
    emLogChanRejectUnsuitableReverseParameters			= 1,
    emLogChanRejectDataTypeNotSupported					= 2,
    emLogChanRejectDataTypeNotAvailable					= 3,
    emLogChanRejectUnknownDataType						= 4,
    emLogChanRejectDataTypeALCombinationNotSupported	= 5,
    emLogChanRejectMulticastChannelNotAllowed			= 6,
    emLogChanRejectInsuffientBandwdith					= 7,
    emLogChanRejectSeparateStackEstablishmentFailed		= 8,
    emLogChanRejectInvalidSessionID						= 9,
    emLogChanRejectMasterSlaveConflict					= 10,
    emLogChanRejectWaitForCommunicationMode				= 11,
    emLogChanRejectInvalidDependentChannel				= 12,
    emLogChanRejectReplacementForRejected				=13
}emlogChannelRejectCause;

/**Init Fail Reason*/
typedef enum
{
    emInitFailReasonSuccess           = 0x00,
    emInitFailReasonMemoryProblem     = 0x01,
    emInitFailReasonConfigProblem     = 0x02,
    emInitFailReasonNetWorkProblem    = 0x03,
    emInitFailReasonInitAgain         = 0x04,
    emInitFailReasonGenConfigFail     = 0x05,
    emInitFailReasonInitSemFail       = 0x06,
    emInitFailReasonNewConnInfoFail   = 0x07,
    emInitFailReasonSetCBFail         = 0x08,
    emInitFailReasonUnknown           = 0x09,
}emInitFailReason;

/**User Input Indication*/
typedef enum 
{
	emUserInputNonStandard=0,
	emUserInputAlphanumeric,
	emUserInputSupport,
	emUserInputSignal,
	emUserInputSignalUpdate,
	emUserInputExtendedAlphanumeric,
	emUserInputEncryptedAlphanumeric
}emUserInputIndication;

/**支持媒体穿越*/
typedef enum
{
	emNotSupportNATFWTraversal,			/**<不支持460穿越*/
	emSupportNATFWTraversal,			/**<支持460*/
	emSupportTransmitMulti,			    /**<支持端口复用*/
	emSupportMediaTraversal				/**<本端为460服务器*/
}emNATFWTraversal;

/**开关常量*/
enum AdpSwitchConstant
{
	Adp_turn_on,		/**<开启*/
	Adp_turn_off		/**<关闭*/
};

/**轮询类型*/
enum AdpPollType
{
	Adp_poll_none,		/**<没有轮询*/
	Adp_poll_vcb,		/**<轮流广播*/
	Adp_poll_vcs		/**<轮流选看*/
};

/**轮询状态*/
enum AdpPollStatus
{
	Adp_poll_status_none,    /**<未轮询*/
	Adp_poll_status_normal,  /**<轮询进行中*/
	Adp_poll_status_pause    /**<轮询暂停*/
};

/**操作类型宏定义*/
enum AdpOprType
{
    Adp_opr_start,		
	Adp_opr_stop
};

/**MCU发向终端的自定义通知消息 消息体号定义*/
enum AdpMcu2MtNtfMsgType
{
    emAdpNoneNtf           = 0,
	emAdpBePolledNextNtf   = 1           /**<即将被轮询到 通知*/
};

/**H460 Features*/
typedef struct PROTO_API tagH460Features
{
	BOOL32 m_bPeerSupportH460;
	BOOL32 m_bPeerMediaTraversalServer;
	BOOL32 m_bPeerSupportTransMultiMedia;
	tagH460Features()
	{
		m_bPeerSupportH460 = FALSE;
		m_bPeerMediaTraversalServer = FALSE;
		m_bPeerSupportTransMultiMedia = FALSE;
	}
}TH460Features,*PTH460Features;

/**H221非标参数*/
typedef struct PROTO_API tagH221NonStandard
{
	u8		m_byT35CountryCode;
	u8		m_byT35Extension;
	u16		m_wManufacturerCode;
	
	void Clear()
	{
		m_byT35CountryCode	 = 0;
		m_byT35Extension	 = 0;
		m_wManufacturerCode  = 0;
	}
	
	void SetH221NonStandard( u8 byCountryCode, u8 byExtension, u16 wManufacturerCode)
	{
		m_byT35CountryCode	= byCountryCode;
		m_byT35Extension	= byExtension;
		m_wManufacturerCode = wManufacturerCode;
	}
	u8 GetT35CountryCode()
	{
		return m_byT35CountryCode;
	}
	u8 GetT35Extension()
	{
		return m_byT35Extension;
	}
	u16 GetManufacturerCode()
	{
		return m_wManufacturerCode;
	}
}TH221NONSTANDARD,*PTH221NONSTANDARD;

/**厂商标识信息*/
/**5.0中规范对vendor结点的相关字段的使用，把之前各个结构体中关于vendor字段提取以及合并到此结构体里。*/
typedef struct PROTO_API tagVendorInfo
{
	TH221NONSTANDARD	m_tVendor;
	s32					m_nVenderid;					/**<厂商id*/

	s32					m_nProductIdSize;
	s8					m_achProductId[MAX_PRODUCTID_LEN+1];	/**<产品号*/

	s32					m_nVersionIdSize;
	s8					m_achVersionId[MAX_PRODUCTID_LEN+1];	/**<版本号*/					

	tagVendorInfo()
	{
		Clear();
	}

	void Clear();

	void SetH221NonStandard( TH221NONSTANDARD &tVendor)
	{
		m_tVendor = tVendor;
	}
	TH221NONSTANDARD& GetH221NonStandard()
	{
		return m_tVendor;
	}

	/**设置厂商ID*/
	void SetVenderId( s32 nVenderId)
	{
		m_nVenderid = nVenderId;
	}
	void SetVendorID( s8 *pProductId, s8 *pVersionId )
	{
		strncpy( m_achProductId, pProductId, Minimum(strlen(pProductId), sizeof(m_achProductId) - 1));
		strncpy( m_achVersionId, pVersionId, Minimum(strlen(pVersionId), sizeof(m_achVersionId) - 1));		
	}
	/**获取厂商ID*/
	s32 GetVenderId()
	{
		return m_nVenderid;
	}


	/**获取产品号长度*/
	s32 GetProductIdSize()
	{
		return m_nProductIdSize;
	}
	void SetProductIdSize( s32 nProductSize )
	{
		m_nProductIdSize = nProductSize;
	}
	/**设置产品号*/
	void SetProductId(s8 *pchId, s32 nLen);

	/**获取产品号*/
	s32 GetProductId(s8 *pchId, s32 nLen);

	s8* GetProductID()
	{
		return m_achProductId;
	}

	/**获取版本号长度*/
	s32 GetVersionIdSize()
	{
		return m_nVersionIdSize;
	}
	void SetVersionIdSize( s32 nVersionIdSize )
	{
		m_nVersionIdSize = nVersionIdSize;
	}
	/**设置版本号*/	
	void SetVersionId(s8 *pchId, s32 nLen);

	/**获取版本号*/
	s32 GetVersionId(s8 *pchId, s32 nLen);

	s8* GetVersionID()
	{
		return m_achVersionId;
	}

}TVENDORINFO,*PTVENDORINFO;

/**给业务设置的初始化级联库相关信息以避免端口冲突*/
typedef struct PROTO_API tagMmcuInfo
{
    /**初始化级联库时设置的watchdog端口范围*/
    u16 m_wWatchPortFrom;
    u16 m_wWatchPortTo;

    /**是否初始化级联库指示*/
    BOOL32 m_bEnableMMCU;

    tagMmcuInfo()
    {
        Clear();
    }

    void Clear()
    {
        m_wWatchPortFrom = 0;
        m_wWatchPortTo = 0;
        m_bEnableMMCU = FALSE;
    }

    BOOL32 GetEnableMMCU()
    {
        return m_bEnableMMCU;
    }

    void SetEnableMMCU(BOOL32 bEnabled)
    {
        m_bEnableMMCU = bEnabled;
    }

    BOOL32 GetMMCUStartPort()
    {
        return m_wWatchPortFrom;
    }

    void SetMMCUStartPort(u16 wWatchPortFrom)
    {
        m_wWatchPortFrom = wWatchPortFrom;
    }

    BOOL32 GetMMCUEndPort()
    {
        return m_wWatchPortFrom;
    }

    void SetMMCUEndPort(u16 wWatchPortTo)
    {
        m_wWatchPortTo = wWatchPortTo;
    }

}TMMCUINFO,*PTMMCUINFO;

typedef struct tagH323AdapterLogCfg
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
	tagH323AdapterLogCfg()
	{
		clear();
	}
}TH323AdapterLogCfg;

/**关键配置参数定义*/
typedef struct PROTO_API tagConfigs
{
	u32				m_dwSystem_maxCalls;				    /**<最大呼叫数*/
	u32				m_dwSystem_maxChannels;					/**<每个呼叫打开的逻辑通道数*/

	u32             m_dwSystem_maxBufferSize;               /**<协议栈消息缓冲buf*/
	
	emEndpointType  m_emTerminalType;						/**<终端类型如(emMt emMcu)*/
	BOOL32			m_bRas_manualRAS;						/**<是否手动RAS操作*/
	BOOL32			m_bRas_manualRegistration;				/**<是否手动RAS注册*/
	PFC_IPADDR      m_tRas_DefaultGkIp[MAX_MULTI_ADDR_NUM];	/**<缺省gk地址*/
	u16				m_wRas_defaultlocalPort;				/**<缺省本地RAS端口*/
	s8				m_achUsername[REG_NAME_LEN];			/**<注册帐号(E164)*/
	s8				m_achPassword[REG_PWD_LEN];				/**<注册密钥*/
	
	TVENDORINFO		m_tVendorInfo;							/**<产品号、版本号*/

	TALIASADDR		m_atAlias[type_others];					/**<别名数组*/
		
	u16				m_wQ931_CallingPort;					/**<h225呼叫端口*/
	emMsTerminalType  m_emMsTerminalType;					/**<主从决定终端类型*/   
	BOOL32			m_bH245_masterSlaveManualOperation;		/**<是否手工进行主从确定*/
	BOOL32			m_bH245_capabilitiesManualOperation;	/**<是否进行手工能力交换*/

    s32             m_nPortFrom;                            /**<端口起始*/
    s32             m_nPortTo;                              /**<端口截止*/

	PFC_IPADDR		m_tStackIp[MAX_MULTI_ADDR_NUM];			/**<协议栈运行IP，Ipv4 and Ipv6 网络序*/

	BOOL32		m_bOptimizeMem;								/**<stack模块初始化内存优化相关参数*/

	u32			m_dwRasResponseTimeout;						/**<ras消息的timeout时长，默认值20s*/

    TMMCUINFO   m_tMmcuInfo;                                /**<给业务设置的初始化级联库相关信息以避免端口冲突*/

	ALL_LOG_CALlBACK m_fpAllLogCallback;					/**<打印日志回调*/
	TH323AdapterLogCfg m_tH323Log;                          /**<让业务设置PfcOpenLogFile参数*/

	s8         byMultiAddrNum;                              /**<Multi IpAddr Num*/
	tagConfigs()
	{
		Clear();
	}

	void Clear();
		
    u32 GetMaxBufferSize()
    {
        return m_dwSystem_maxBufferSize;
    }
	
	void SetMaxBufferSize(u32 maxBufferSize)
	{
		m_dwSystem_maxBufferSize = maxBufferSize;
		return;
	}

	/**设置最大呼叫数、最大逻辑通道数*/
	void SetMaxNum( u32 dwMaxCalls, u32 dwMaxChannels )
	{
        m_dwSystem_maxCalls = (dwMaxCalls>MIN_CALL_NUM && dwMaxCalls<MAX_CALL_NUM)?dwMaxCalls:MAX_CALL_NUM;
        m_dwSystem_maxChannels = (dwMaxChannels>MIN_CHANNEL_NUM && dwMaxChannels<MAX_CHANNEL_NUM)?dwMaxChannels:MIN_CHANNEL_NUM;
	}
	/**获取最大呼叫数*/
	u32 GetMaxCalls()
	{
		return m_dwSystem_maxCalls;
	}
	/**获取最大通道数*/
	u32 GetMaxChannels()
	{
		return m_dwSystem_maxChannels;
	}
	/**设置是否使用手动RAS*/
	void SetMannualRAS( BOOL32 bManualRAS, BOOL32 bManualReg )
	{
		m_bRas_manualRAS = bManualRAS;
		m_bRas_manualRegistration = bManualReg;
	}
	/**获取是否手动RAS*/
	BOOL32 IsManualRAS()
	{
		return m_bRas_manualRAS;
	}
	/**获取是否手动注册*/
	BOOL32 IsManualReg()
	{
		return m_bRas_manualRegistration;
	}
	/**设置终端类型、主从决定终端类型*/
	void SetTerminalType( emEndpointType emEpType, emMsTerminalType emMSTType )
	{
		m_emTerminalType = emEpType;
		m_emMsTerminalType = emMSTType;
	}
	/**获取终端类型*/
	emEndpointType GetEndpointType()
	{
		return m_emTerminalType;
	}
	/**获取主从决定的终端类型*/
	emMsTerminalType GetMsTerminalType()
	{
		return m_emMsTerminalType;
	}
	
	/**设置用户密码*/
	void SetUserInfo(s8* pszUserName, s8* pszPassword);

	/**取用户名*/
	s8* GetUserName()
	{
		return m_achUsername;
	}
	/**取密码*/
	s8* GetPassword()
	{
		return m_achPassword;
	}

	/**设置别名*/
	void SetAliasAddr( TALIASADDR &tAliasAddr, u32 dwAliasNo );

	/**获取别名类型*/
	PTALIASADDR GetAliasAddr( u32 dwAliasNo );

	/**设置h225呼叫端口*/
	void SetH225CallingPort( u16 wCallPort = CALLPORT )
	{
		m_wQ931_CallingPort = wCallPort;
	}

	/**获取h225呼叫端口*/
	u16 GetH225CallingPort()
	{
		return m_wQ931_CallingPort;
	}

    /**设置本地RAS端口*/
    void SetLocalRASPort( u16 wRASPort = RASPORT )
    {
        m_wRas_defaultlocalPort = wRASPort;
    }
    /**获取本地RAS端口*/
    u16 GetLocalRASPort()
    {
        return m_wRas_defaultlocalPort;
    }
	/**设置是否手动MSD，CSE*/
	void SetH245IsManual( BOOL32 bMsdManual, BOOL32 bCseManual )
	{
		m_bH245_masterSlaveManualOperation  = bMsdManual;
		m_bH245_capabilitiesManualOperation = bCseManual;
	}
	/**获取MSD是否手动操作*/
	BOOL32 IsMasterSlaveManual()
	{
		return m_bH245_masterSlaveManualOperation;
	}
	/**获取CSE是否手动操作*/
	BOOL32 IsCapabilitiesManual()
	{
		return m_bH245_capabilitiesManualOperation;
	}
    /**设置端口范围*/
    void SetPortRange(s32 portFrom, s32 portTo)
    {
        m_nPortFrom = portFrom;
        m_nPortTo   = portTo;
    }
    /**得到起始端口号*/
    s32 GetFirstPort()
    {
        return m_nPortFrom;
    }
    /**得到最后一个端口号*/
    s32 GetLastPort()
    {
        return m_nPortTo;
    }

	/**设置协议栈运行IP*/
	void SetStackIP( PFC_IPADDR &tIPAddr, u8 addrNo )
	{
		if ( addrNo < MAX_MULTI_ADDR_NUM)
		{
			m_tStackIp[addrNo] = tIPAddr;
		}
	}

	/** 获取Stack IP地址*/
	PFC_IPADDR GetStackIP( u8 addrNo )
	{
		if ( addrNo < MAX_MULTI_ADDR_NUM )
		{
			return m_tStackIp[addrNo];
		}
		return m_tStackIp[0];
	}

	/**设置协议栈运行 GK IP*/
	void SetGkIP( PFC_IPADDR &tIPAddr, u8 addrNo )
	{
		if ( addrNo < MAX_MULTI_ADDR_NUM)
		{
			m_tRas_DefaultGkIp[addrNo] = tIPAddr;
		}
	}

	/** 获取GK IP地址*/
	PFC_IPADDR GetGkIP( u8 addrNo )
	{
		if ( addrNo < MAX_MULTI_ADDR_NUM )
		{
			return m_tRas_DefaultGkIp[addrNo];
		}
		return m_tRas_DefaultGkIp[0];
	}

	void SetOptimizeMem(BOOL32 bOptimizeMem) 
	{
		m_bOptimizeMem = bOptimizeMem;
	}

	BOOL32 IsOptimizeMem()
	{
		return m_bOptimizeMem;	
	}

	void SetRasTimeout(u32 dwRasResponseTimeout)
	{
		m_dwRasResponseTimeout = dwRasResponseTimeout;
	}
	u32	GetRasTimeout()
	{
		return m_dwRasResponseTimeout;
	}

}TH323CONFIG,*PH323TH323CONFIG; 

/**h323stack additional config*/
typedef struct PROTO_API tagAdditionalConfig
{
	RrqAuthAlgType      m_emAuthAlgType;	        /**set RRQ Auth Type */
	FacilityReason      m_emH225FacilityReason;	    /**set facility reason for H460*/
	TStaticNATAddr		m_tNATAddress;				/**Static NAT AddrParis*/
	tagAdditionalConfig()
	{
		m_emAuthAlgType = emRrqAuthAlgTypeMD5;
		m_emH225FacilityReason = undefined;
		m_tNATAddress.Clear();
	}
	/**设置NAT地址*/
	void SetNATAddress(TStaticNATAddr tNATAddress)
	{
		memcpy(&m_tNATAddress,&tNATAddress,sizeof(TStaticNATAddr));
	}
	/**得到NAT地址*/
	TStaticNATAddr& GetNATAddress()
	{
		return m_tNATAddress;
	}
	/**设置RRQ认证类型*/
	void SetRrqAuthAlgType(RrqAuthAlgType emAuthAlgType)
	{
		m_emAuthAlgType = emAuthAlgType;
	}
	/**得到RRQ认证类型*/
	RrqAuthAlgType GetRrqAuthAlgType()
	{
		return m_emAuthAlgType;
	}

	/**设置facility类型*/
	void SetH225FacilityReason(FacilityReason emH225FacilityReason)
	{
		m_emH225FacilityReason = emH225FacilityReason;
	}
	/**得到facility类型*/
	FacilityReason GetH225FacilityReason()
	{
		return m_emH225FacilityReason;
	}
}TAdditionalConfig;

/**呼叫地址*/
typedef struct PROTO_API tagCallAddr
{
private:
	CallAddrType    m_eType;
	PFC_IPADDR		m_tIPAddr;					
	TALIASADDR		m_tAliasAddr;
public:
	tagCallAddr()
	{
		Clear();
	}

	void Clear()
	{
		m_tIPAddr.Clear();
		m_tAliasAddr.Clear();
	}
	
	/**设置CallAddrType*/
	void SetCallAddrType(CallAddrType emAddrType)
	{
		m_eType = emAddrType;
	}
	/**获得CallAddrType*/
	CallAddrType GetCallAddrType()
	{
		return m_eType;
	}

	/**设置IP地址和端口号*/
	void SetIPAddr(u32 dwIp,u16 wPort = 0)
	{
		wPort = htons(wPort);
		m_tIPAddr.SetIpAddr(dwIp,wPort);
	}	
	/**获得IP地址*/
	u32 GetIPAddr()  
	{	
		return m_tIPAddr.m_tAddr.m_tIPv4.m_dwIP;
	}

	/**获得端口号*/
	u16 GetIPPort()  
	{	
		return ntohs( m_tIPAddr.m_wPort);	
	}
	/**设置IPV6地址和端口号*/
	void SetIPv6Addr(u8 abyIpv6[],u16 wPort = 0)
	{
		wPort = htons(wPort);
		m_tIPAddr.SetIpv6Addr(abyIpv6,wPort);
	}

	/**获得IPV6地址*/
	void GetIPv6Addr(u8* abyIpv6,u16* pwPort)  
	{	
		m_tIPAddr.GetIpv6Addr(abyIpv6,pwPort);
	}
	/**设置Alias地址*/
	void SetAliasAddr( AliasType emAliasType, const s8* sAlias );
	
	/**获得TALIASADDR的type*/
	AliasType GetAliasType()
	{
		return m_tAliasAddr.m_emType;
	}
	/**获得TALIASADDR的别名*/
	s8* GetAliasName()  
	{
		return m_tAliasAddr.m_achAlias;	
	}	
}TCALLADDR,*PTCALLADDR;

/**connect消息到来时返回给上层的结构*/
typedef struct PROTO_API tagNodeInfo 
{
	u32                 m_dwEndpointType;                   /**< 此值可代表多个类型，可以是emEndpointType多个成员的或操作*/ 
	u8					m_bySubMtType;						/**<  卫星/电话/普通*/ 
	s8					m_achName[LEN_DISPLAY_MAX+1];		/**<  结点名称*/ 
	BOOL32				m_bIsEncrypt;						/**<  是否支持加密*/ 
	TVENDORINFO			m_tVendorInfo;						/**<  产品号、版本号*/ 
	u32					m_dwCallRate;						/**<  呼叫速率	(kbps)*/ 
	emNATFWTraversal	m_emMediaTraversal;					/**<  Media traversal*/ 
	TH460Features		m_tH460Features;					/**<  H.460 features*/ 
	TAliasAddr			m_atCallingAliasAddr[type_others+1];/**<  主叫别名地址(别名地址+IP)*/ 
	TAliasAddr			m_atCalledAliasAddr[type_others+1]; /**<  被叫别名地址(别名地址+IP)*/ 
	u8					m_abyCallID[LEN_GUID];				/**<  CallIdentifier, a global identifier for TrueLink to support EPs called by IP mode*/ 
	u32					m_dwStaticNATAddr;					/**< Static NAT*/ 
    
	tagNodeInfo()
	{
		Clear();
	}

	void Clear();

	/** Set CallID to TNodeInfo*/
	void SetCallID(IN const u8* pbyCallID, IN u8 byLen)
	{
		if (pbyCallID == NULL || byLen <= 0 )
		{
			return;
		}
		s32 nReal = Minimum(Maximum((s32)LEN_1, (s32)byLen), (s32)LEN_GUID);
		memcpy(m_abyCallID, pbyCallID, nReal);
	}

	/** Get CallID from TNodeINfo*/
	s32 GetCallID(OUT u8* pbyCallId, IN s32 nMaxOutLen)
	{
		if(pbyCallId == NULL|| nMaxOutLen <= 0 )
		{
			return 0;
		}
		
		s32 nReal = Minimum(Maximum((s32)LEN_1, nMaxOutLen), (s32)LEN_GUID);
		memcpy(pbyCallId, m_abyCallID, nReal);

		return nReal;
	}

	/** set Static NAT Addr*/
	void SetStaticNATAddr(u32 dwNATIP)
	{
		m_dwStaticNATAddr = dwNATIP;
	}
	
	u32 GetStaticNATAddr()
	{
		return m_dwStaticNATAddr;
	}

	/** 设置终端类型*/
	void SetEndpointType(u32 dwEpType)
	{
		m_dwEndpointType = dwEpType;
	}
	/** 获取终端类型*/
	u32 GetEndpointType()
	{
		return m_dwEndpointType;
	}
	
	void SetSubMtType( u8 byMtType )
	{
		m_bySubMtType = byMtType;
	}
	u8  GetSubMtType( )
	{
		return m_bySubMtType;	
	}
		
	/** 设置display name*/
	void SetName(s8 *pchName, s32 nLen);

	/** 获取display name*/
	s8* GetName()
	{
		return m_achName;
	}
	/** 设置是否加密*/
	void SetIsEncrypt( BOOL32 bIsEncrypt )
	{
		m_bIsEncrypt = bIsEncrypt;
	}
	/** 获取是否加密*/
	BOOL32 IsEncrypt()
	{
		return m_bIsEncrypt;
	}
	
	void SetSupportMediaTraversal(emNATFWTraversal emNet)
	{
		m_emMediaTraversal = emNet;
	}
	emNATFWTraversal GetSupportMediaTraversal()
	{
		return m_emMediaTraversal;
	}
	void SetH460features( const TH460Features &th460features )
	{
		memcpy( &m_tH460Features, &th460features, sizeof(TH460Features) );
	}
	void GetH460features( TH460Features &th460features )
	{
		memcpy( &th460features, &m_tH460Features, sizeof(TH460Features) );
	}


	/** 设置主叫别名地址	作为源端的信息*/
	void SetCallingAliasaddr( TAliasAddr &tAliasAddr, u8 addrNo )
	{
		if ( addrNo < type_others+1  )
		{
			m_atCallingAliasAddr[addrNo] = tAliasAddr;
		}
	}
	/** 获取主叫别名地址*/
	PTAliasAddr GetCallingAliasaddr( u8 addrNo )
	{
		if ( addrNo < type_others+1  )
		{
			return &(m_atCallingAliasAddr[addrNo]);
		}
		return NULL;
	}
	
	/**设置被叫别名地址	作为目的端的信息*/
	void SetCalledAliasAddr( TAliasAddr &tAliasAddr, u8 byAddrNo )
	{
		if ( byAddrNo < type_others+1  )
		{
			m_atCalledAliasAddr[byAddrNo] = tAliasAddr;
		}		
	}
	/**获取被叫别名地址*/
	PTAliasAddr GetCalledAliasAddr( u8 byAddrNo )
	{
		if ( byAddrNo < type_others+1  )
		{
			return &(m_atCalledAliasAddr[byAddrNo]);
		}
		return NULL;
	}
}TNODEINFO,*PTNODEINFO;

/**发起H460呼叫参数*/
typedef struct PROTO_API tagH460CallParam 
{
	cmTransportAddress   m_tCallSignalAddr;
	u8                   m_abyCallId[LEN_GUID];      /**<CallIdentifier*/

	tagH460CallParam()
	{
		memset(&m_tCallSignalAddr, 0, sizeof(cmTransportAddress));
		memset(m_abyCallId, 0, LEN_GUID);
	}
}TH460CALLPARAM, *PTH460CALLPARAM;

/**发起呼叫参数*/
typedef struct PROTO_API tagCallParam 
{
	cmConferenceGoalType  m_emConfGoalType;  				  /**<会议的目标类型*/
	cmCallType            m_emCallType;						  /**<呼叫类型 */
	u32                   m_dwEndpointType;					  /**<端点类型，此值可以是多个类型的复合类型，即emEndpointType多个成员可做或操作 */
	u32					  m_dwCallRate;						  /**<呼叫速率	(kbps)*/
    TAliasAddr			  m_tCalledAddr;					  /**<被叫地址。 发送时,可设置为别名地址，接收时为被叫信令地址*/
    TAliasAddr			  m_tCallingAddr;					  /**<主叫地址   主叫信令地址*/
	TAliasAddr			  m_atCallingAliasAddr[type_others+1];/**<主叫别名地址(别名地址+IP) ，缺省采用配置文件的设置*/
	TAliasAddr			  m_atCalledAliasAddr[type_others+1]; /**<被叫别名地址(别名地址+IP)*/
	u8					  m_abyConfId[LEN_GUID];		      /**<会议号,必须16 octet*/
	u8					  m_abyCallId[LEN_GUID];  
	s8					  m_achDisplay[LEN_DISPLAY_MAX+1];	  /**<主叫信息*/

    /**UserInfo字段暂不使用*/
    s32					  m_nUUSize; 
	u8					  m_abyUserInfo[LEN_USERINFO_MAX];	  /**<UserInfo消息长度：2-131字节*/

	BOOL32				  m_bIsEncrypt;						  /**<是否加密*/

    /**<代替原来的UserInfo字段*/
	s32					  m_nNonStandLen;
	u8					  m_abyNonStandData[LEN_NONSTANDARD_MAX];
    
	TVENDORINFO			  m_tVendorInfo;		/**产品号、版本号*/

	emNATFWTraversal	  m_bySupportMediaTraversal;
	TH460Features		  m_tH460Features;
    
	tagCallParam()
	{
		Clear();	
		CreateConfId();
	}

	void Clear();

    /**设置终端类型*/
    void SetEndpointType(u32 dwType)
    {
        m_dwEndpointType = dwType;
    }
    /**得到终端类型*/
    u32 GetEndpointType()
    {
        return m_dwEndpointType;
    }
    

    /**设置最大速率*/
    void SetCallRate( u32 dwCallRate )
    {
        m_dwCallRate = dwCallRate;
    }
    /**得到最大速率*/
    u32 GetCallRate()
    {
        return m_dwCallRate;
    }
	/**设置被叫地址*/
	void SetCalledAddr(u32 dwIp,u16 wPort = CALLPORT)
	{
		PFC_IPADDR addr;
		addr.SetIpAddr(dwIp,wPort==0 ? CALLPORT : wPort );
		m_tCalledAddr.SetIPCallAddr( &addr );
	}

//add by yj for ipv6
	/**设置被叫地址(ipv6)*/
//	void SetCalledAddr_Ipv6(u8* dwIp_ipv6, s16 swScopeId,u16 wPort = CALLPORT)
	void SetCalledAddr_Ipv6(u8* pbyIp_ipv6,u16 wPort = CALLPORT)
	{
		PFC_IPADDR addr;
		addr.SetIpv6Addr(pbyIp_ipv6,wPort==0 ? CALLPORT : wPort);
		m_tCalledAddr.SetIPCallAddr( &addr );
	}
	/**获得被叫IP(ipv6)*/
	u8* GetCalledIp_Ipv6()
	{
		return m_tCalledAddr.GetIPAddr_Ipv6(); 
	}
//	s16 GetCalledIp_Ipv6_ScopeId()
//	{
//		return m_tCalledAddr.GetIPAddr_Ipv6_ScopeId();
//	}
// TAliasAddr& GetCalledIp()
// {
//    return m_tCalledAddr;
// }
// TAliasAddr& GetCallingIp()
// {
// 	return m_tCallingAddr;
// }
//end
	/**获得被叫IP*/
	u32 GetCalledIp()
	{
		return m_tCalledAddr.GetIPAddr(); 
	}	
	/**获得被叫端口*/
	u16 GetCalledPort() 
	{ 
		return m_tCalledAddr.GetIPPort(); 
	}

	/**设置被叫地址*/
	void SetCalledAddr(AliasType eType,const s8* sAlias)
	{
		TALIASADDR aliasAddr;
		aliasAddr.SetAliasAddr( eType, sAlias );
		m_tCalledAddr.SetIPCallAddr( &aliasAddr );
	}
    /**得到被叫地址*/
    TAliasAddr& GetCalledAddr()
    {
        return m_tCalledAddr;
    }

	/**设置主叫地址*/
	void SetCallingAddr( u32 dwIp,u16 wPort = 0 )
	{
		PFC_IPADDR addr;
        //Jacky Wei Replace port 0 with default CALLPORT for Bug00144938(Intercommunication problem with HUAWEI EP)
		/*addr.SetNetAddress( dwIp, (wPort==CALLPORT||wPort==TLCALLPORT)? 0 : wPort);*/
        //addr.SetNetAddress(dwIp, wPort == 0 ? CALLPORT : wPort);
		addr.SetIpAddr( dwIp, wPort == 0 ? CALLPORT : wPort);
		m_tCallingAddr.SetIPCallAddr( &addr );
		
	}
	/**获得主叫IP*/
	u32 GetCallingIp()
	{
		return m_tCallingAddr.GetIPAddr();	
	}	
	/**获得主叫端口*/
	u16 GetCallingPort()
	{
		return m_tCallingAddr.GetIPPort();	
	}
    /**设置主叫地址*/
    void SetCallingAddr(AliasType eType,const char* sAlias)
    {
        TALIASADDR aliasAddr;
        aliasAddr.SetAliasAddr( eType, sAlias );
        m_tCallingAddr.SetIPCallAddr( &aliasAddr );
    }

	//add by yj for ipv6
	/**设置主叫地址(ipv6)*/
//	void SetCallingAddr_Ipv6( u8* dwIp_ipv6,s16 swScopeId,u16 wPort = 0 )
	void SetCallingAddr_Ipv6( u8* dwIp_ipv6,u16 wPort = 0 )
	{
		PFC_IPADDR addr;
		addr.SetIpv6Addr(dwIp_ipv6, wPort == 0 ? CALLPORT : wPort);
		m_tCallingAddr.SetIPCallAddr( &addr );
	}
	/**获得主叫IP(ipv6)*/
	u8* GetCallingIp_Ipv6()
	{
		return m_tCallingAddr.GetIPAddr_Ipv6(); 
	}
//	s16 GetCallingIp_Ipv6_ScopeId()
//	{
//		return m_tCalledAddr.GetIPAddr_Ipv6_ScopeId();
//	}
	//end

    /**得到主叫地址*/
    TAliasAddr& GetCallingAddr()
    {
        return m_tCallingAddr;
    }   

	/**设置主叫别名地址	作为源端的信息*/
	void SetCallingAliasaddr( TAliasAddr &tAliasAddr, u8 addrNo )
	{
		if ( addrNo < type_others+1  )
		{
			m_atCallingAliasAddr[addrNo] = tAliasAddr;
		}
	}
	/**获取主叫别名地址*/
	PTAliasAddr GetCallingAliasaddr( u8 addrNo )
	{
		if ( addrNo < type_others+1  )
		{
			return &(m_atCallingAliasAddr[addrNo]);
		}
		return NULL;
	}
	
	/**设置被叫别名地址	作为目的端的信息*/
	void SetCalledAliasAddr( TAliasAddr &tAliasAddr, u8 byAddrNo )
	{
		if ( byAddrNo < type_others+1  )
		{
			m_atCalledAliasAddr[byAddrNo] = tAliasAddr;
		}		
	}
	/**获取被叫别名地址*/
	PTAliasAddr GetCalledAliasAddr( u8 byAddrNo )
	{
		if ( byAddrNo < type_others+1  )
		{
			return &(m_atCalledAliasAddr[byAddrNo]);
		}
		return NULL;
	}

	/**设置会议号*/
	void SetConfId(const u8* pchConfId,u8 byLen);

	/**会议号长度*/
	s32 GetConfIdSize()
	{
		return LEN_GUID;
	};
	/**获取会议号*/
	s32 GetConfId(u8* pbyConfId, s32 nLen);

	/**生成一个会议号*/
	void CreateConfId()
	{
		memcpy(m_abyConfId, KDV::utils::GetGUID(), LEN_GUID);
	}
	
	/**生成一个Callidentifier*/
	void CreateCallId()
	{
		memcpy(m_abyCallId, KDV::utils::GetGUID(), LEN_GUID);
	}
	/**设置呼叫ID*/
	void SetCallId(const u8* pbyCallId, u8 byLen);

	/**获取呼叫ID的长度*/
	s32 GetCallIdSize()
	{
		return LEN_GUID;
	};
	/**获取呼叫ID*/
	s32 GetCallId(u8* pbyCallId, s32 nLen);

	/**设置显示信息*/
	void SetDisplayInfo(const s8* pchInfo);

	/**获得显示信息*/
	s8* GetDisplayInfo()
	{
		return m_achDisplay;
	}
	
	/**设置UserInfo*/
	void SetUserInfo(const u8* pchUserInfo, u8 byLen);
	
	/**获得UserInfo长度*/
	s32 GetUserInfoSize()
	{
		return m_nUUSize;
	}
	/**获取UserInfo*/
	s32 GetUserInfo(u8* pbyUserInfo, u8 byLen);

	/**设置加密*/
	void SetIsEncrypt( BOOL32 bIsEncrypt )
	{
		m_bIsEncrypt = bIsEncrypt;
	}
	/**是否加密*/
	BOOL32 IsEncrypt()
	{
		return m_bIsEncrypt;
	}

	/**对指针赋值，不能保存， 小心！！！！！！！！*/
	BOOL32 SetNonStandData(u8 *pBuf, s32 nLen);

    /**获取指针，不能保存小心！！！！！！！！*/
	BOOL32 GetNonStandData(u8 **ppBuf, s32 *pnLen);

	void SetSupportMediaTraversal(emNATFWTraversal emNet)
	{
		m_bySupportMediaTraversal = emNet;
	}
	emNATFWTraversal GetSupportMediaTraversal()
	{
		return m_bySupportMediaTraversal;
	}
	void SetH460features( const TH460Features &th460features )
	{
		memcpy( &m_tH460Features, &th460features, sizeof(TH460Features) );
	}
	void GetH460features( TH460Features &th460features )
	{
		memcpy( &th460features, &m_tH460Features, sizeof(TH460Features) );
	}

}TCALLPARAM,*PTCALLPARAM;


/**打开信道参数*/
typedef struct PROTO_API tagChannelParam 
{
	PFC_IPADDR	     m_tRtp;				/**<rtp地址 ,incoming chan使用*/
	PFC_IPADDR	     m_tRtcp;				/**<rtcp地址,incoming and outgoing chan使用*/
	u16			     m_wPayloadType;		/**<媒体通道类型*/	

	TKdvVideoCap	 m_tVideoCap;
	TKdvAudioCap	 m_tAudioCap;
	TKdvDataCap		 m_tDataCap;
	TKdvG7231Cap	 m_tG7231Cap;

	TKdvG7221Cap     m_tG7221Cap;
	TKdvOpusCap      m_tOpusCap;			

	BOOL32		     m_bFlowToZero;		/**<是否要求发送端在信道建立时不发送码流*/
	TTERLABEL	     m_tSrcTer;
	TTERLABEL	     m_tDstTer;

	u8			     m_byDynamicPT;		/**<动态载荷类型值(96~127)*/
	emEncryptType    m_emEncryptType;		/**<加密类型*/
	TEncryptSync     m_tEncryptSync;       /**<master需设置此结构  */       

    BOOL32           m_bIsH239DStream;     /**<在打开视频通道时指明是否H239协议的双流*/

    BOOL32           m_bSupportRSVP;       /**<是否支持RSVP，双方都支持RSVP则设为TRUE*/
    
    u8               m_byFECType;          /**<前向纠错类型。音视频通道可填*/

    TKdvH264VideoCap m_tH264Cap;           /**<H.264能力视频能力，与m_tVideoCap互斥，只需填写一个即可*/

    TKdvAACCap       m_tAacCap;            /**<AAC LC/LD 音频能力*/
	
	PFC_IPADDR	     m_tKeepAliveAddr;		/**<460 server's rtp sending address for keep-alive channel added by wangxiaoyi 29 July 2010*/
	u16			     m_byKeepAlivePayload;	/**<打洞包载荷类型(0~127)*/
	u32			     m_dwKeepAliveInterval; /**<打洞包发送时间间隔*/

	TKdvH265VideoCap m_tH265Cap;
    
public:
	tagChannelParam()
	{
		Reset();
	};

	void Reset();

	void host2net(BOOL32 bhton);

    /**设置是否支持RSVP*/
    void SetSupportRSVP(BOOL32 bSupportRSVP) 
    {	
        m_bSupportRSVP = bSupportRSVP; 
    }
    BOOL32 IsSupportRSVP() 
    {
        return m_bSupportRSVP;
    }

    /**设置FEC类型*/
    void SetFECType(u8 emType)
    {
        m_byFECType = emType;
    }
	/**获取FEC类型*/
    u8 GetFECType() const
    {
        return m_byFECType;
    }
	
    /**设置RTP参数*/
	void SetRtp(PFC_IPADDR& rtp) 
	{ 
		m_tRtp = rtp; 
	}
    /**得到RTP参数*/
	PFC_IPADDR& GetRtp() 
	{
		return m_tRtp; 
	};
	/**设置KeepAliveAddr参数 for h460 keepalivechannel*/
	void SetKeepAliveAddr(PFC_IPADDR& keepaliveaddr) 
	{ 
		m_tKeepAliveAddr = keepaliveaddr; 
	}
    /**得到KeepAliveAddr参数 for h460 keepalivechannel*/
	PFC_IPADDR& GetKeepAliveAddr() 
	{
		return m_tKeepAliveAddr; 
	};

    /**设置RTCP参数*/
	void SetRtcp(PFC_IPADDR& rtcp) 
	{
		m_tRtcp = rtcp; 
	}
    /**得到RTCP参数*/
	PFC_IPADDR& GetRtcp() 
	{
		return m_tRtcp; 
	}

    /**设置FlowToZero*/
	void SetIsFlowToZero(BOOL32 bFlowToZero) 
	{	
		m_bFlowToZero = bFlowToZero; 
	}
	BOOL32 IsFlowToZero() 
	{
		return m_bFlowToZero;
	}
	
    /**设置加密类型*/
    void SetEncryptType(emEncryptType emType)
	{
		m_emEncryptType = emType; 
	}
    /**得到加密类型*/
	emEncryptType GetEncryptType()
	{
		return m_emEncryptType;
	}

    /**设置源端TTERLABEL*/
	void SetSrcTerLabel( TTERLABEL& tTer) 
	{ 
		m_tSrcTer = tTer;
	}
    /**得到源端TTERLABEL*/
    TTERLABEL& GetSrcTerLabel() 
	{ 
		return m_tSrcTer; 
	}

    /**设置目的端TTERLABEL*/
	void SetDstTerLabel( TTERLABEL& tTer) 
	{ 
		m_tDstTer = tTer;
	}
    /**得到目的端TTERLABEL*/
    TTERLABEL& GetDstTerLabel() 
	{ 
		return m_tDstTer; 
	}

    /**设置动态载荷类型*/
	BOOL32 SetDynamicPayloadParam( u8 byDynamicPT )
	{
		if ( byDynamicPT>=96 && byDynamicPT<=127 ) 
		{
			m_byDynamicPT = byDynamicPT;
			return TRUE;
		}
		return FALSE;
	}
	u8 GetDynamicPayloadParam()
	{
	    return m_byDynamicPT;
	} 
    /**是否动态载荷类型 */
    BOOL32 IsDynamicPayload()	
    { 
        return (m_byDynamicPT >= 96)&&(m_byDynamicPT <= 127); 
    }

    /**得到载荷类型*/
    u16 GetPayloadType()
    {
        return m_wPayloadType; 
    }

    /**设置视频参数，不包括H.264 H.265*/
	BOOL32 SetPayloadParam(u16 wPayloadType, TKdvVideoCap &tVideoCap);

    /**得到视频参数*/
    BOOL32 GetPayloadParam(u16 wPayloadType, TKdvVideoCap *ptVideoCap);

    /**设置H.264视频参数*/
    BOOL32 SetPayloadParam(u16 wPayloadType, TKdvH264VideoCap &tVideoCap);

    /**得到H.264视频参数*/
    BOOL32 GetPayloadParam(u16 wPayloadType, TKdvH264VideoCap *ptVideoCap);
	
	/**设置H.265视频参数*/
    BOOL32 SetPayloadParam(u16 wPayloadType, TKdvH265VideoCap &tVideoCap);

	/**得到H.265视频参数*/
    BOOL32 GetPayloadParam(u16 wPayloadType, TKdvH265VideoCap *ptVideoCap);

    /**设置音频参数，不包括G7231*/
	BOOL32 SetPayloadParam(u16 wPayloadType, TKdvAudioCap &tAudioCap);

    /**得到音频参数，不包括G7231/AAC/7221*/
    BOOL32 GetPayloadParam(u16 wPayloadType, TKdvAudioCap *ptAudioCap);

    /**设置G7231参数*/
    BOOL32 SetPayloadParam(u16 wPayloadType, TKdvG7231Cap &tG7231Cap);

    /**得到G7231参数*/
    BOOL32 GetPayloadParam(u16 wPayloadType, TKdvG7231Cap *ptG7231Cap);
	
    /**设置AAC参数*/
    BOOL32 SetPayloadParam(u16 wPayloadType, TKdvAACCap &tAacCap);

    /**得到AAC参数*/
    BOOL32 GetPayloadParam(u16 wPayloadType, TKdvAACCap *ptAacCap);

    /**设置数据参数*/
	BOOL32 SetPayloadParam(u16 wPayloadType, TKdvDataCap &tDataCap);

    /**得到数据参数*/
    BOOL32 GetPayloadParam(u16 wPayloadType, TKdvDataCap *ptDataCap);
	
	/**设置Opus参数*/
    BOOL32 SetPayloadParam(u16 wPayloadType, TKdvOpusCap &tOpusCap);

    /**得到Opus参数*/
    BOOL32 GetPayloadParam(u16 wPayloadType, TKdvOpusCap *ptOpusCap);	

	/**设置G7221参数*/
	BOOL32 SetPayloadParam(u16 wPayloadType, TKdvG7221Cap &tG7221Cap);

    /**得到G7221参数*/
    BOOL32 GetPayloadParam(u16 wPayloadType, TKdvG7221Cap *ptG7221Cap);
		
    /**设置加密同步信息*/
	void SetEncryptSync( TEncryptSync &tSync)
	{ 
		m_tEncryptSync = tSync; 
	}
    /**得到加密同步信息*/
	TEncryptSync &GetEncryptSync() 
	{ 
		return m_tEncryptSync; 
	} 

	void SetKeepAlivePayload(u16 payload)
	{
		m_byKeepAlivePayload = payload;
	}
	u16 GetKeepAlivePayload()
	{
		return m_byKeepAlivePayload;
	}

	void SetKeepAliveInterval(u32 time)
	{
		m_dwKeepAliveInterval = time;
	}
	u32 GetKeepAliveInterval()
	{
		return m_dwKeepAliveInterval;
	}
	
}TCHANPARAM,*PTCHANPARAM;

typedef struct PROTO_API tagKeepAliveInfo
{
	PFC_IPADDR	m_tKeepAliveNet;
	u16			m_wKeepAlivePayload;
	u32			m_dwKeepAliveInterval;

	tagKeepAliveInfo()
	{
		Clear();
	}
	void Clear()
	{
		m_tKeepAliveNet.Clear();
		m_wKeepAlivePayload = 0;
		m_dwKeepAliveInterval = 0;
	}
}TKeepAliveInfo, *PTKeepAliveInfo;

typedef struct PROTO_API tagTTerminalInfo
{
	TTERLABEL	m_tTerLabel;					/**< 终端ID*/
	u8			m_byType;						/**< 终端类型（视频or电话）*/
	s8			m_achE164[MAXLEN_E164+1];		/**< 终端E164号*/
	s8			m_achAlias[LEN_TERID + 1];		/**< 终端别名*/
	u8			m_byNone;						/**< 终端是否为为只发送音频码流 0-不只发送音频，1-只发送音频*/
	
	u8 GetMcuNo() 
	{ 
		return m_tTerLabel.GetMcuNo();	
	}
	/**获得终端号*/
	u8 GetTerNo() 
	{ 
		return m_tTerLabel.GetTerNo();	
	}
	
	/**获得终端名字*/
	s8* GetName()
	{
		return m_achAlias;
	}

	s8* GetE164()
	{
		return m_achE164;
	}
	
public:
	tagTTerminalInfo(){memset( this ,0 ,sizeof( struct tagTTerminalInfo) );}

public:
/**
	* \brief            对结构体进行打包 
	* \param[out]       pbyBuf	   :结构体PACK包，不包括包长度
	* \param[in]        dwBufSize  :pbyBuf的空间长度
	* \param[out]       dwBufSize  :返回实际需要的BUF长度（即结构体包长）
	* \retval           success:TRUE
	* \retval           failed :FALSE
	* \par 示例：
	* \code
					u32 dwBufSize = 0;
					u8 * pbyBuf = NULL;
					Pack(pbyBuf, dwBufSize);
					if ( dwBufSize > 0 )
					{
						pbyBuf = new u8[dwBufSize];
						Pack( pbyBuf, dwBufSize );
						...
						delete [] pbyBuf;
					}
	* \endcode

*/
    BOOL32 Pack( u8 * pbyBuf, u32 &dwBufSize ); 
/**
	* \brief            对结构体进行解包 
	* \param[in]        pbyBuf	   :结构体PACK包，不包括包长度
	* \param[out]       dwBufSize  :pbyBuf的长度
	* \retval           success:TRUE
	* \retval           failed :FALSE
*/
    BOOL32 UnPack( u8 * pbyBuf, u32 dwBufSize );

}TTerminalInfo ,*PTTTerminalInfo;				

/**temporal spatial tradeoff*/
typedef struct PROTO_API tagTSTO
{
	u8  m_chIsCommand;     /**<命令还是指示*/
    u8  m_chTradeoffValue; /**<The trade off value, between 0(high spatial resolution) to 31(a high frame rate)*/

    tagTSTO()
	{
		Clear();
	}

	void Clear()
	{
		m_chIsCommand = 0;
		m_chTradeoffValue = 0;
	}

	void SetIsCommand(BOOL32 bCommand)
	{
		m_chIsCommand = bCommand ? 1:0;
	}
	BOOL32 IsCommand()
	{
		return m_chIsCommand>0;
	}
	/**set The trade off value, between 0 to 31.*/
	void SetTradeoffValue(u8 byTradeoffValue)
	{
		if( byTradeoffValue > 31 )
		{
           return ;
		}
        m_chTradeoffValue = byTradeoffValue;
	}

	s8 GetTradeoffValue()
	{
		return m_chTradeoffValue;
	}
}TTSTO;

/**update GOB struct*/
typedef struct PROTO_API tagVFUGOB
{
	s32 m_nFirstGOB;
	s32 m_nNumOfGOB;

	tagVFUGOB()
	{
		Clear();
	}

	void Clear()
	{
		m_nFirstGOB = 0;
		m_nNumOfGOB = 0;
	}

    void host2net(BOOL32 bhton);

    void SetFirstGOB(s32 nFirstGOB)
	{
		m_nFirstGOB = nFirstGOB;
	}
	s32 GetFirstGOB()
	{
		return m_nFirstGOB;
	}
	void SetNumOfGOB(s32 nNumOfGOB)
	{
		//add by yj
		//m_nNumOfGOB = m_nNumOfGOB;
		m_nNumOfGOB = nNumOfGOB;
		//end
	}
	s32 GetNumOfGOB()
	{
		return m_nNumOfGOB;
	}

}TVFUGOB;

/**update MB struct*/
typedef struct PROTO_API tagVFUMB
{
	s32 m_nFirstGOB;
	s32 m_nFirstMB;
	s32 m_nNumOfMB;

	tagVFUMB()
	{
		Clear();
	}

	void Clear()
	{
		m_nFirstGOB = 0;
		m_nFirstMB	= 0;
		m_nNumOfMB	= 0;
	}

    void host2net(BOOL32 bhton);

    void SetFirstGOB(s32 nFirstGOB)
	{
		m_nFirstGOB = nFirstGOB;
	}
	s32 GetFirstGOB()
	{
		return m_nFirstGOB;
	}

	void SetFirstMB(s32 nFirstMB)
	{
		m_nFirstMB = nFirstMB;
	}
	s32 GetFirstMB()
	{
		return m_nFirstMB;
	}

	void SetNumOfMB(s32 nNumOfMB)
	{
		//add by yj
		//m_nNumOfMB = m_nNumOfMB;
		m_nNumOfMB = nNumOfMB;
		//end
	}
	s32 GetNumOfMB()
	{
		return m_nNumOfMB;
	}
	
}TVFUMB;

/**RRQ消息结构*/
typedef struct PROTO_API tagRRQInfo
{
	PFC_IPADDR		m_tCallAddr;			/**<呼叫信令地址*/
	PFC_IPADDR		m_tLocalRASAddr;		/**<本地RAS地址*/
	cmEndpointType	m_eTerminalType;		/**<终端类型,GK用*/
	TALIASADDR		m_atAlias[MAXALIASNUM];	/**<向GK注册时的多个别名，必须从第0个索引开始赋值*/
	s32				m_nTimetoLive;			/**<timetolive，单位：秒	(optional)*/
	BOOL32			m_bKeepAlive;			/**<轻量级注册标志位*/
	TALIASADDR		m_tEndpointID;			/**<终端ID,GK用			(optional)*/
	PFC_IPADDR		m_tGkAddr;				/**<GK地址*/
	TALIASADDR		m_tUserName;	             //注册帐号(E164、h323id)
	s8				m_ach_Password[REG_PWD_LEN];			/**<注册密钥*/
	TALIASADDR		m_tGKID;				/**<GK ID,GK用*/
	BOOL32          m_bSigTraversal;        /**<signalling traversal*/
 	BOOL32			m_bRequireGKPermison;

	TVENDORINFO		m_tVendorInfo;			/**<产品号、版本号*/

	PFC_IPADDR        m_tParaAddr;          /**<NAT过后的源地址*/
	
	BOOL32			m_bPortReused;   /**<是否支持端口复用*/

	tagRRQInfo()
	{
		Clear();
	}

	void Clear();
	
    /**设置呼叫信令地址*/
    void SetCallAddr( PFC_IPADDR &tCallAddr )
    {
        m_tCallAddr = tCallAddr;
    }
    /**得到呼叫信令地址*/
    PFC_IPADDR& GetCallAddr()
    {
        return m_tCallAddr;
    }

    /**设置本地RAS地址*/
    void SetLocalRASAddr( PFC_IPADDR &tLocalRASAddr )
    {
        m_tLocalRASAddr = tLocalRASAddr;
    }
    /**得到本地RAS地址*/
    PFC_IPADDR& GetLocalRASAddr()
    {
        return m_tLocalRASAddr;
    }
    /**设置终端类型*/
    void SetTerminalType( cmEndpointType emTerminalType )
    {
        m_eTerminalType = emTerminalType;
    }
    /**得到终端类型*/
    cmEndpointType GetTerminalType()
    {
        return m_eTerminalType;
    }

    /**设置注册别名*/
    void SetRRQAlias( TALIASADDR &tAlias, u8 byAliasNo )
    {
        if ( byAliasNo >= MAXALIASNUM )
            return;
        
        m_atAlias[byAliasNo] = tAlias;
    }
    /**得到注册的别名*/
    TALIASADDR& GetRRQAlias( u8 byAliasNo )
    {
        if ( byAliasNo < MAXALIASNUM ) 
            return m_atAlias[byAliasNo];
        else
            return m_atAlias[0];        
    }

    /**设置TimetoLive值*/
    void SetTimetoLive( s32 nTimetoLive )
    {
        m_nTimetoLive = nTimetoLive;
    }
    /**得到TimetoLive值*/
    s32 GetTimetoLive()
    {
        return m_nTimetoLive;
    }

    /**设置是否轻量级注册*/
    void SetKeepAlive( BOOL32 bKeepAlive )
    {
        m_bKeepAlive = bKeepAlive;
    }
    /**判断是否轻量级注册*/
    BOOL32 IsKeepAlive()
    {
        return m_bKeepAlive;
    }

    /**设置终端ID*/
    void SetEndpointID( TALIASADDR &tEndpointID )
    {
        m_tEndpointID = tEndpointID;
    }
    /**得到终端ID*/
    TALIASADDR& GetEndpointID()
    {
        return m_tEndpointID;
    }
	/**设置用户密码*/
	void SetUserInfo(TALIASADDR* ptUserName, s8* pszPassword);

	/**取用户名*/
	TALIASADDR* GetUserName()
	{
		return &m_tUserName;
	}
	/**取密码*/
	s8* GetPassword()
	{
		return m_ach_Password;
	}
    /**设置GK地址*/
    void SetGKAddr( PFC_IPADDR &tGkAddr )
    {
        m_tGkAddr = tGkAddr;
    }
    /**得到GK地址*/
    PFC_IPADDR& GetGKAddr()
    {
        return m_tGkAddr;
    }
    /**设置GK ID*/
    void SetGKID( TALIASADDR &tGKID )
    {
        m_tGKID = tGKID;
    }
    /**得到GK ID*/
    TALIASADDR& GetGKID()
    {
        return m_tGKID;
    }
	
	/**设置NAT 源地址*/
    void SetParaAddr( PFC_IPADDR &tParamAddr )
    {
        m_tParaAddr = tParamAddr;
    }
    /**得到NAT 源地址*/
    PFC_IPADDR& GetParaAddr()
    {
        return m_tParaAddr;
    }
	void SetBeH460Ep(BOOL32 bType)
	{
		m_bSigTraversal = htonl(bType);
	}
	BOOL32 GetBeH460Ep()
	{
		return ntohl(m_bSigTraversal);
	}

	/**端口复用，默认值0，非标传输时会转成u8类型传输*/
	void SetPortReused(BOOL32 bPortReused)
	{
		m_bPortReused = bPortReused;
	}
	BOOL32 GetPortReused()
	{
		return m_bPortReused;
	}

}TRRQINFO, *PTRRQINFO;

/**RCF消息结构*/
typedef struct PROTO_API tagRCFInfo
{
	PFC_IPADDR		m_tCallSignalAddr;		/**<GK返回的呼叫信令地址*/
	TALIASADDR		m_atAlias[MAXALIASNUM];	/**<GK返回的多个别名			(optional)*/
	TALIASADDR		m_tGKID;				/**<GK ID,GK用*/
	TALIASADDR		m_tEndpointID;			/**<终端ID,GK用*/
	s32				m_nTimetoLive;			/**<timetolive 单位：秒		(optional)*/
	BOOL32			m_bWillRespondToIRR;	/**<是否响应IRR消息,GK用*/
	BOOL32          m_bIsKDVTSGK;           /**<是否是KDVTS的GK*/
	BOOL32          m_bSigTraversal;        /**<signalling traversal*/
	BOOL32          m_bIfAccess;            /**<是否获得GK授权，没有usbkey的pcmt需要获得GK授权才能正常开会*/

    // XXX
    u8              byNonAccessReason;      /**<如果未获得GK授权，这个字段描述了原因*/

	tagRCFInfo()
	{
		Clear();
	}

	void Clear();

	void SetBeH460Ep(BOOL32 bType)
	{
		m_bSigTraversal = bType;
	}
	BOOL32 GetBeH460Ep()
	{
		return m_bSigTraversal;
	}			

    /**设置GK返回的呼叫信令地址*/
    void SetCallSignalAddr( PFC_IPADDR &tCallSignalAddr )
    {
        m_tCallSignalAddr = tCallSignalAddr;
    }
    /**得到GK返回的呼叫信令地址*/
    PFC_IPADDR& GetCallSignalAddr()
    {
        return m_tCallSignalAddr;
    }

    /**设置GK返回的多个别名*/
    void SetRCFAlias( TALIASADDR &tAlias, u8 byAliasNo )
    {
        if ( byAliasNo >= MAXALIASNUM )
            return;
        
        m_atAlias[byAliasNo] = tAlias;
    }
    /**得到GK返回的多个别名*/
    TALIASADDR& GetRCFAlias( u8 byAliasNo )
    {
        if ( byAliasNo < MAXALIASNUM ) 
            return m_atAlias[byAliasNo];
        else
            return m_atAlias[0];
    }

    /**设置GK ID*/
    void SetGKID( TALIASADDR &tGKID )
    {
        m_tGKID = tGKID;
    }
    /**得到GK ID*/
    TALIASADDR& GetGKID()
    {
        return m_tGKID;
    }
    
    /**设置终端ID*/
    void SetEndpointID( TALIASADDR &tEndpointID )
    {
        m_tEndpointID = tEndpointID;
    }
    /**得到终端ID*/
    TALIASADDR& GetEndpointID()
    {
        return m_tEndpointID;
    }

    /**设置TimetoLive值*/
    void SetTimetoLive( s32 nTimetoLive )
    {
        m_nTimetoLive = nTimetoLive;
    }
    /**得到TimetoLive值*/
    s32 GetTimetoLive()
    {
        return m_nTimetoLive;
    }

    /**设置是否响应IRR消息*/
    void SetWillRespondToIRR( BOOL32 bKeepAlive )
    {
        m_bWillRespondToIRR = bKeepAlive;
    }
    /**判断是否响应IRR消息*/
    BOOL32 IsWillRespondToIRR()
    {
        return m_bWillRespondToIRR;
    }
	void SetIsKDVTSGK(BOOL32 bIsKDVGK)
	{
		m_bIsKDVTSGK = bIsKDVGK;
	}
	BOOL32 GetIsKDVTSGK()
	{
		return m_bIsKDVTSGK;
    }
}TRCFINFO, *PTRCFINFO;

/**ARQ结构体*/
typedef struct PROTO_API tagARQInfo
{
	cmCallType		m_eCallType;			    /**<呼叫类型,GK用*/
	cmCallModelType m_eCallModel;			    /**<GK呼叫模式,默认值为直接呼叫	(optional)*/
	TALIASADDR		m_tEndpointID;			    /**<终端ID,GK用*/
	TALIASADDR		m_tDestAlias;			    /**<目的端别名*/
	PFC_IPADDR		m_tCalledAddr;			    /**<目的端地址*/
	TALIASADDR		m_atSrcAlias[MAXALIASNUM];  /**<源端别名*/
	PFC_IPADDR		m_tCallAddr;			    /**<源端地址,GK用(optional)*/
	s32				m_nBandWidth;			    /**<单位：kbps*/
	s32				m_nCRV;					    /**<呼叫参考值,GK用*/
	s8  			m_achConferenceID[LEN_GUID];/**<会议ID,GK用*/
	BOOL32			m_bAnswerCall;			    /**<是否被叫,GK用*/
	s8  			m_achCallID[LEN_GUID];	    /**<呼叫ID,GK用*/
	TALIASADDR		m_tGKID;				    /**<GK ID,GK用(optional)*/
	
	PFC_IPADDR		m_tGkAddr;				    /**<GK地址*/
	
	tagARQInfo()
	{
		Clear();
	}

	void Clear();

    /**设置呼叫类型*/
    void SetCallType( cmCallType emCallType )
    {
        m_eCallType = emCallType;
    }
    /**得到呼叫类型*/
    cmCallType GetCallType()
    { 
        return m_eCallType;
    }

    /**设置呼叫模式*/
    void SetCallModelType( cmCallModelType emCallModel )
    {
        m_eCallModel = emCallModel;
    }
    /**得到呼叫模式*/
    cmCallModelType GetCallModelType()
    { 
        return m_eCallModel;
    }

    /**设置终端ID*/
    void SetEndpointID( TALIASADDR &tEndpointID )
    {
        m_tEndpointID = tEndpointID;
    }
    /**得到终端ID*/
    TALIASADDR& GetEndpointID()
    {
        return m_tEndpointID;
    }

    /**设置目的端别名*/
    void SetDestAlias( TALIASADDR &tDestAlias )
    {
        m_tDestAlias = tDestAlias;
    }
    /**得到目的端别名*/
    TALIASADDR& GetDestAlias()
    {
        return m_tDestAlias;
    }

    /**设置目的端地址*/
    void SetCalledAddr( PFC_IPADDR &tCalledAddr )
    {
        m_tCalledAddr = tCalledAddr;
    }
    /**得到目的端地址*/
    PFC_IPADDR& GetCalledAddr()
    {
        return m_tCalledAddr;
    }

    /**设置源端别名*/
    void SetARQSrcAlias( TALIASADDR &tAlias, u8 byAliasNo )
    {
        if ( byAliasNo >= MAXALIASNUM )
            return;
        
        m_atSrcAlias[byAliasNo] = tAlias;
    }
    /**得到源端别名*/
    TALIASADDR& GetARQSrcAlias( u8 byAliasNo )
    {
        if ( byAliasNo < MAXALIASNUM ) 
            return m_atSrcAlias[byAliasNo];
        else
            return m_atSrcAlias[0];
    }

    /**设置源端地址*/
    void SetCallAddr( PFC_IPADDR &tCallAddr )
    {
        m_tCallAddr = tCallAddr;
    }
    /**得到源端地址*/
    PFC_IPADDR& GetCallAddr()
    {
        return m_tCallAddr;
    }

    /**设置带宽*/
    void SetBandWidth( s32 nBandWidth )
    {
        m_nBandWidth = nBandWidth;
    }
    /**得到带宽*/
    s32 GetBandWidth()
    {
        return m_nBandWidth;
    }

    /**设置呼叫参考值*/
    void SetCRV( s32 nCRV )
    {
        m_nCRV = nCRV;
    }
    /**得到呼叫参考值*/
    s32 GetCRV()
    {
        return m_nCRV;
    }

    /**设置会议ID*/
    void SetConferenceID( s8 *pchConferenceID, u8 byLen );

    /**得到会议ID*/
    s8* GetConferenceID()
    {
        return m_achConferenceID;
    }

    /**设置是否被叫*/
    void SetAnswerCall( BOOL32 bAnswerCall )
    {
        m_bAnswerCall = bAnswerCall;
    }
    /**判断是否被叫*/
    BOOL32 IsAnswerCall()
    {
        return m_bAnswerCall;
    }

    /**设置呼叫ID*/
    void SetCallID( s8 *pchCallID, u8 byLen );

    /**得到呼叫ID*/
    s8* GetCallID()
    {
        return m_achCallID;
    }

    /**设置GK ID*/
    void SetGKID( TALIASADDR &tGKID )
    {
        m_tGKID = tGKID;
    }
    /**得到GK ID*/
    TALIASADDR& GetGKID()
    {
        return m_tGKID;
    }

    /**设置GK地址*/
    void SetGKAddr( PFC_IPADDR &tGKAddr )
    {
        m_tGkAddr = tGKAddr;
    }
    /**得到GK地址*/
    PFC_IPADDR& GetGKAddr()
    {
        return m_tGkAddr;
    }    
}TARQINFO, *PTARQINFO;

/**ACF结构体*/
typedef struct PROTO_API tagACFInfo
{
	s32				m_nBandWidth;			    /**<单位：kbps*/
	cmCallModelType m_eCallModel;			    /**<GK呼叫模式,默认值为直接呼叫*/
	PFC_IPADDR		m_tCalledAddr;			    /**<目的端地址*/
	s32				m_nIRRFrequency;		    /**<IRR的发送频率，单位：秒	(optional)*/
	BOOL32			m_bWillResponseIRR;		    /**<响应IRR消息*/
	TALIASADDR		m_atDestAlias[MAXALIASNUM];	/**<GK返回的多个别名(optional) */

	PFC_IPADDR        m_tP2PCheckAddr;            /**<add by zhanghb for kdvp2.0 P2P呼叫检测地址，非标*/			
	
	tagACFInfo()
	{
		Clear();
	}

	void Clear();

    /**设置带宽*/
    void SetBandWidth( s32 nBandWidth )
    {
        m_nBandWidth = nBandWidth;
    }
    /**得到带宽*/
    s32 GetBandWidth()
    {
        return m_nBandWidth;
    }

    /**设置呼叫模式*/
    void SetCallModelType( cmCallModelType emCallModel )
    {
        m_eCallModel = emCallModel;
    }
    /**得到呼叫模式*/
    cmCallModelType GetCallModelType()
    { 
        return m_eCallModel;
    }

    /**设置目的端地址*/
    void SetCalledAddr( PFC_IPADDR &tCalledAddr )
    {
        m_tCalledAddr = tCalledAddr;
    }
    /**得到目的端地址*/
    PFC_IPADDR& GetCalledAddr()
    {
        return m_tCalledAddr;
    }

	/**设置目的端地址*/
    void SetP2PCallCheckAddr( PFC_IPADDR &tCalledAddr )
    {
        m_tP2PCheckAddr = tCalledAddr;
    }
    /**得到目的端地址*/
    PFC_IPADDR& GetP2PCallCheckAddr()
    {
        return m_tP2PCheckAddr;
    }		


    /**设置IRR的发送频率*/
    void SetIRRFrequency( s32 nIRRFrequency )
    {
        m_nIRRFrequency = nIRRFrequency;
    }
    /**得到IRR的发送频率*/
    s32 GetIRRFrequency()
    {
        return m_nIRRFrequency;
    }

    /**设置是否响应IRR消息*/
    void SetWillResponseIRR( BOOL32 bWillResponseIRR )
    {
        m_bWillResponseIRR = bWillResponseIRR;
    }
    /**判断是否响应IRR消息*/
    BOOL32 IsWillResponseIRR()
    {
        return m_bWillResponseIRR;
    }
    /**设置GK返回的多个别名*/
    void SetACFAlias( TALIASADDR &tAlias, u8 byAliasNo )
    {
        if ( byAliasNo >= MAXALIASNUM )
            return;
        
        m_atDestAlias[byAliasNo] = tAlias;
    }
    /**得到GK返回的多个别名*/
    TALIASADDR& GetACFAlias( u8 byAliasNo )
    {
        if ( byAliasNo < MAXALIASNUM ) 
            return m_atDestAlias[byAliasNo];
        else
            return m_atDestAlias[0];
    }
}TACFINFO, *PTACFINFO;

/**DRQ结构体*/
typedef struct PROTO_API tagDRQInfo
{
	TALIASADDR		m_tEndpointID;			    /**<终端ID,GK用*/
	s8  			m_achConferenceID[LEN_GUID];/**<会议ID,GK用*/
	s32				m_nCRV;					    /**<呼叫参考值,GK用*/
	cmRASDisengageReason m_eReason;			    /**<DRQ的原因*/		
	s8  			m_achCallID[LEN_GUID];	    /**<呼叫ID,GK用*/
	TALIASADDR		m_tGKID;				    /**<GK ID,GK用(optional)*/
	BOOL32			m_bAnsweredCall;		    /**<是否为被叫端,GK用*/

	PFC_IPADDR		m_tDestAddr;			    /**<DRQ的接受端地址*/
	
	tagDRQInfo()
	{
		Clear();
	}

	void Clear();

    /**设置终端ID*/
    void SetEndpointID( TALIASADDR &tEndpointID )
    {
        m_tEndpointID = tEndpointID;
    }
    /**得到终端ID*/
    TALIASADDR& GetEndpointID()
    {
        return m_tEndpointID;
    }

    /**设置会议ID*/
    void SetConferenceID( s8 *pchConferenceID, u8 byLen );

    /**得到会议ID*/
    s8* GetConferenceID()
    {
        return m_achConferenceID;
    }

    /**设置呼叫参考值*/
    void SetCRV( s32 nCRV )
    {
        m_nCRV = nCRV;
    }
    /**到呼叫参考值*/
    s32 GetCRV()
    {
        return m_nCRV;
    }

    /**设置DRQ的原因*/
    void SetDRQReason( cmRASDisengageReason emDRQReason )
    {
        m_eReason = emDRQReason;
    }
    /**得到DRQ的原因*/
    cmRASDisengageReason GetDRQReason()
    { 
        return m_eReason;
    }

    /**设置呼叫ID*/
    void SetCallID( s8 *pchCallID, u8 byLen );

    /**得到呼叫ID*/
    s8* GetCallID()
    {
        return m_achCallID;
    }
    
    /**设置GK ID*/
    void SetGKID( TALIASADDR &tGKID )
    {
        m_tGKID = tGKID;
    }
    /**得到GK ID*/
    TALIASADDR& GetGKID()
    {
        return m_tGKID;
    }

    /**设置是否被叫*/
    void SetAnsweredCall( BOOL32 bAnsweredCall )
    {
        m_bAnsweredCall = bAnsweredCall;
    }
    /**判断是否被叫*/
    BOOL32 IsAnsweredCall()
    {
        return m_bAnsweredCall;
    }
    
    /**设置DRQ的接受端地址*/
    void SetDestAddr( PFC_IPADDR &tDestAddr )
    {
        m_tDestAddr = tDestAddr;
    }
    /**得到DRQ的接受端地址*/
    PFC_IPADDR& GetDestAddr()
    {
        return m_tDestAddr;
    }
}TDRQINFO, *PTDRQINFO;

/**URQ结构体*/
typedef struct PROTO_API tagURQInfo
{
	PFC_IPADDR		m_tCallAddr;			/**<源端呼叫信令地址*/
	TALIASADDR		m_atAlias[MAXALIASNUM];	/**<向GK注册时的多个别名(optional)*/
	TALIASADDR		m_tEndpointID;			/**<终端ID(optional)*/
	TALIASADDR		m_tGKID;				/**<GK ID(optional)*/
	cmRASUnregReason m_eReason;				/**<URQ的原因(optional)*/
	
	PFC_IPADDR		m_tDestAddr;			/**<URQ的接受端地址*/
	
	tagURQInfo()
	{
		Clear();
	}

	void Clear();

    /**设置源端呼叫信令地址*/
    void SetCallAddr( PFC_IPADDR &tCallAddr )
    {
        m_tCallAddr = tCallAddr;
    }
    /**得到源端呼叫信令地址*/
    PFC_IPADDR& GetCallAddr()
    {
        return m_tCallAddr;
    }

    /**设置向GK注册时的多个别名*/
    void SetURQAlias( TALIASADDR &tAlias, u8 byAliasNo )
    {
        if ( byAliasNo >= MAXALIASNUM )
            return;
        
        m_atAlias[byAliasNo] = tAlias;
    }
    /**得到向GK注册时的多个别名*/
    TALIASADDR& GetURQAlias( u8 byAliasNo )
    {
        if ( byAliasNo < MAXALIASNUM ) 
            return m_atAlias[byAliasNo];
        else
            return m_atAlias[0];
    }

    /**设置终端ID*/
    void SetEndpointID( TALIASADDR &tEndpointID )
    {
        m_tEndpointID = tEndpointID;
    }
    /**得到终端ID*/
    TALIASADDR& GetEndpointID()
    {
        return m_tEndpointID;
    }

    /**设置GK ID*/
    void SetGKID( TALIASADDR &tGKID )
    {
        m_tGKID = tGKID;
    }
    /**得到GK ID*/
    TALIASADDR& GetGKID()
    {
        return m_tGKID;
    }

    /**设置URQ的原因*/
    void SetURQReason( cmRASUnregReason emURQReason )
    {
        m_eReason = emURQReason;
    }
    /**得到URQ的原因*/
    cmRASUnregReason GetURQReason()
    { 
        return m_eReason;
    }

    /**设置URQ的接受端地址*/
    void SetDestAddr( PFC_IPADDR &tDestAddr )
    {
        m_tDestAddr = tDestAddr;
    }
    /**得到URQ的接受端地址*/
    PFC_IPADDR& GetDestAddr()
    {
        return m_tDestAddr;
    }
}TURQINFO, *PTURQINFO;

/**BRQ结构体*/
typedef struct tagBRQInfo
{
	TALIASADDR		m_tEndpointID;			    /**<终端ID,GK用*/
	s8			    m_achConferenceID[LEN_GUID];/**<会议ID,GK用*/
	s32				m_nCRV;					    /**<呼叫参考值,GK用*/
	cmCallType		m_eCallType;			    /**<呼叫类型,GK用，默认为点对点	(optional)*/
	s32				m_nBandWidth;			    /**<单位：kbps*/
	
	s8			    m_achCallID[LEN_GUID];	    /**<呼叫ID,GK用*/
	TALIASADDR		m_tGKID;				    /**<GK ID,GK用(optional)*/
	BOOL32			m_bAnsweredCall;		    /**<是否为被叫端,GK用*/

	PFC_IPADDR		m_tDestAddr;			    /**<BRQ的接受端地址*/
	
	tagBRQInfo()
	{
		Clear();
	}

	void Clear();

    /**设置终端ID*/
    void SetEndpointID( TALIASADDR &tEndpointID )
    {
        m_tEndpointID = tEndpointID;
    }
    /**得到终端ID*/
    TALIASADDR& GetEndpointID()
    {
        return m_tEndpointID;
    }

    /**设置会议ID*/
    void SetConferenceID( s8 *pchConferenceID, u8 byLen );

    /**得到会议ID*/
    s8* GetConferenceID()
    {
        return m_achConferenceID;
    }

    /**设置呼叫参考值*/
    void SetCRV( s32 nCRV )
    {
        m_nCRV = nCRV;
    }
    /**得到呼叫参考值*/
    s32 GetCRV()
    {
        return m_nCRV;
    }

    /**设置呼叫类型*/
    void SetCallType( cmCallType emCallType )
    {
        m_eCallType = emCallType;
    }
    /**得到呼叫类型*/
    cmCallType GetCallType()
    { 
        return m_eCallType;
    }

    /**设置带宽*/
    void SetBandWidth( s32 nBandWidth )
    {
        m_nBandWidth = nBandWidth;
    }
    /**得到带宽*/
    s32 GetBandWidth()
    {
        return m_nBandWidth;
    }

    /**设置呼叫ID*/
    void SetCallID( s8 *pchCallID, u8 byLen );

    /**得到呼叫ID*/
    s8* GetCallID()
    {
        return m_achCallID;
    }

    /**设置GK ID*/
    void SetGKID( TALIASADDR &tGKID )
    {
        m_tGKID = tGKID;
    }
    /**得到GK ID*/
    TALIASADDR& GetGKID()
    {
        return m_tGKID;
    }

    /**设置是否被叫*/
    void SetAnsweredCall( BOOL32 bAnsweredCall )
    {
        m_bAnsweredCall = bAnsweredCall;
    }
    /**判断是否被叫*/
    BOOL32 IsAnsweredCall()
    {
        return m_bAnsweredCall;
    }

    /**设置BRQ的接受端地址*/
    void SetDestAddr( PFC_IPADDR &tDestAddr )
    {
        m_tDestAddr = tDestAddr;
    }
    /**得到BRQ的接受端地址*/
    PFC_IPADDR& GetDestAddr()
    {
        return m_tDestAddr;
    }
}TBRQINFO, *PTBRQINFO;

/**BCF结构体*/
typedef struct tagBCFInfo
{
	s32				m_nBandWidth;			/**<单位：kbps*/
	tagBCFInfo()
	{
		m_nBandWidth = 0;
	}

    /**设置带宽*/
    void SetBandWidth( s32 nBandWidth )
    {
        m_nBandWidth = nBandWidth;
    }
    /**得到带宽*/
    s32 GetBandWidth()
    {
        return m_nBandWidth;
    }
}TBCFINFO, *PTBCFINFO;

/**LRQ结构体*/
typedef struct tagLRQInfo
{
	TALIASADDR		m_tEndpointID;			/**<终端ID,GK用(optional)*/
	TALIASADDR		m_tDestAlias;			/**<目的端别名*/
	PFC_IPADDR		m_tReplyAddr;			/**<发送端地址*/	
	TALIASADDR		m_tGKID;				/**<GK ID,GK用(optional)*/

	PFC_IPADDR		m_tResponseAddr;		/**<接受端地址*/

	tagLRQInfo()
	{
		Clear();
	}

	void Clear();

    /**设置终端ID*/
    void SetEndpointID( TALIASADDR &tEndpointID )
    {
        m_tEndpointID = tEndpointID;
    }
    /**得到终端ID*/
    TALIASADDR& GetEndpointID()
    {
        return m_tEndpointID;
    }

    /**设置目的端别名*/
    void SetDestAlias( TALIASADDR &tDestAlias )
    {
        m_tDestAlias = tDestAlias;
    }
    /**得到目的端别名*/
    TALIASADDR& GetDestAlias()
    {
        return m_tDestAlias;
    }

    /**设置发送端地址*/
    void SetReplyAddr( PFC_IPADDR &tReplyAddr )
    {
        m_tReplyAddr = tReplyAddr;
    }
    /**得到发送端地址*/
    PFC_IPADDR& GetReplyAddr()
    {
        return m_tReplyAddr;
    }
    
    /**设置GK ID*/
    void SetGKID( TALIASADDR &tGKID )
    {
        m_tGKID = tGKID;
    }
    /**得到GK ID*/
    TALIASADDR& GetGKID()
    {
        return m_tGKID;
    }

    /**设置接受端地址*/
    void SetResponseAddr( PFC_IPADDR &tResponseAddr )
    {
        m_tResponseAddr = tResponseAddr;
    }
    /**得到接受端地址*/
    PFC_IPADDR& GetResponseAddr()
    {
        return m_tResponseAddr;
    }
}TLRQINFO, *PTLRQINFO;

/**LCF结构体*/
typedef struct tagLCFInfo
{
	PFC_IPADDR		m_tCallAddr;			/**<呼叫信令地址*/
	PFC_IPADDR		m_tRASAddr;				/**<RAS地址*/
	cmEndpointType	m_nDestinationType;		/**<终端类型(optional)*/

	tagLCFInfo()
	{
		Clear();
	}

	void Clear();

    /**设置呼叫信令地址*/
    void SetCallAddr( PFC_IPADDR &tCallAddr )
    {
        m_tCallAddr = tCallAddr;
    }
    /**得到呼叫信令地址*/
    PFC_IPADDR& GetCallAddr()
    {
        return m_tCallAddr;
    }
    
    /**设置RAS地址*/
    void SetRASAddr( PFC_IPADDR &tRASAddr )
    {
        m_tRASAddr = tRASAddr;
    }
    /**得到RAS地址*/
    PFC_IPADDR& GetRASAddr()
    {
        return m_tRASAddr;
    }
    
    /**设置终端类型*/
    void SetDestinationType( cmEndpointType emDestinationType )
    {
        m_nDestinationType = emDestinationType;
    }
    /**得到终端类型*/
    cmEndpointType GetDestinationType()
    {
        return m_nDestinationType;
    }
}TLCFINFO, *PTLCFINFO;

/**IRQ结构体*/
typedef struct tagIRQInfo
{	
	s32				m_nCRV;					/**<呼叫参考值*/
	s8  			m_achCallID[LEN_GUID];	/**<呼叫ID*/

	HCALL			m_hsCall;				/**<呼叫句柄*/
	PFC_IPADDR		m_tPeerRasAddr;			/**<对端RAS地址*/

	tagIRQInfo()
	{
		Clear();
	}

	void Clear();

    /**设置呼叫参考值*/
    void SetCRV( s32 nCRV )
    {
        m_nCRV = nCRV;
    }
    /**得到呼叫参考值*/
    s32 GetCRV()
    {
        return m_nCRV;
    }

    /**设置呼叫ID*/
    void SetCallID( s8 *pchCallID, u8 byLen );

    /**得到呼叫ID*/
    s8* GetCallID()
    {
        return m_achCallID;
    }

    /**设置呼叫句柄*/
    void SetHCALL( HCALL hsCall )
    {
        if ( hsCall != NULL )
            m_hsCall = hsCall;
    }
    /**得到呼叫句柄*/
    HCALL GetHCALL()
    {
        return m_hsCall;
    }

    /**设置对端RAS地址*/
    void SetPeerRasAddr( PFC_IPADDR &tPeerRasAddr )
    {
        m_tPeerRasAddr = tPeerRasAddr;
    }
    /**得到对端RAS地址*/
    PFC_IPADDR& GetPeerRasAddr()
    {
        return m_tPeerRasAddr;
    }
}TIRQINFO, *PTIRQINFO;

/**IRR结构体*/
typedef struct PROTO_API tagIRRInfo
{
	cmEndpointType	m_eEndpointType;		    /**<终端类型,GK用*/
	TALIASADDR		m_tEndpointID;			    /**<终端ID,GK用*/
	PFC_IPADDR		m_tRASAddr;				    /**<本地RAS地址*/
	PFC_IPADDR		m_tCallAddr;			    /**<呼叫信令地址*/
	TALIASADDR		m_atAlias[MAXALIASNUM];	    /**<向GK注册的多个别名	(optional)	*/
	//perCallInfo
	s32				m_nCRV;					    /**<呼叫参考值,GK用*/
	s8				m_achConferenceID[LEN_GUID];/**<会议ID,GK用*/
	BOOL32			m_bOriginator;			    /**<是否为主叫,GK用*/

	s8				m_achCallID[LEN_GUID];	    /**<呼叫ID,GK用*/
	BOOL32			m_bNeedResponse;		    /**<是否响应IRR消息*/
	BOOL32			m_bIsUnsolicited;		    /**<默认为TRUE：主动发IRR；FALSE：响应IRQ*/
											
	PFC_IPADDR		m_tGKAddr;				    /**<GK地址*/
	

	tagIRRInfo()
	{
		Clear();
	}

	void Clear();
	
    /**设置终端类型*/
    void SetEndpointType( cmEndpointType emEndpointType )
    {
        m_eEndpointType = emEndpointType;
    }
    /**得到终端类型*/
    cmEndpointType GetEndpointType()
    {
        return m_eEndpointType;
    }

    /**设置终端ID*/
    void SetEndpointID( TALIASADDR &tEndpointID )
    {
        m_tEndpointID = tEndpointID;
    }
    /**得到终端ID*/
    TALIASADDR& GetEndpointID()
    {
        return m_tEndpointID;
    }

    /**设置RAS地址*/
    void SetRASAddr( PFC_IPADDR &tRASAddr )
    {
        m_tRASAddr = tRASAddr;
    }
    /**得到RAS地址*/
    PFC_IPADDR& GetRASAddr()
    {
        return m_tRASAddr;
    }

    /**设置呼叫信令地址*/
    void SetCallAddr( PFC_IPADDR &tCallAddr )
    {
        m_tCallAddr = tCallAddr;
    }
    /**得到呼叫信令地址*/
    PFC_IPADDR& GetCallAddr()
    {
        return m_tCallAddr;
    }

    /**设置注册别名*/
    void SetIRRAlias( TALIASADDR &tAlias, u8 byAliasNo )
    {
        if ( byAliasNo >= MAXALIASNUM )
            return;
        
        m_atAlias[byAliasNo] = tAlias;
    }
    /**得到注册的别名*/
    TALIASADDR& GetIRRAlias( u8 byAliasNo )
    {
        if ( byAliasNo < MAXALIASNUM ) 
            return m_atAlias[byAliasNo];
        else
            return m_atAlias[0];
    }

    /**设置呼叫参考值*/
    void SetCRV( s32 nCRV )
    {
        m_nCRV = nCRV;
    }
    /**得到呼叫参考值*/
    s32 GetCRV()
    {
        return m_nCRV;
    }

    /**设置会议ID*/
    void SetConferenceID( s8 *pchConferenceID, u8 byLen );
  
    /**得到会议ID*/
    s8* GetConferenceID()
    {
        return m_achConferenceID;
    }
    
    /**设置是否主叫*/
    void SetOriginator( BOOL32 bOriginator )
    {
        m_bOriginator = bOriginator;
    }
    /**判断是否主叫*/
    BOOL32 IsOriginator()
    {
        return m_bOriginator;
    }

    /**设置呼叫ID*/
    void SetCallID( s8 *pchCallID, u8 byLen );

    /**得到呼叫ID*/
    s8* GetCallID()
    {
        return m_achCallID;
    }
    
    /**设置是否响应IRR消息*/
    void SetNeedResponse( BOOL32 bNeedResponse )
    {
        m_bNeedResponse = bNeedResponse;
    }
    /**判断是否响应IRR消息*/
    BOOL32 IsNeedResponse()
    {
        return m_bNeedResponse;
    }

    /**设置是否Unsolicited消息*/
    void SetUnsolicited( BOOL32 bIsUnsolicited )
    {
        m_bIsUnsolicited = bIsUnsolicited;
    }
    /**判断是否Unsolicited消息*/
    BOOL32 IsUnsolicited()
    {
        return m_bIsUnsolicited;
    }
    
    /**设置GK地址*/
    void SetGKAddr( PFC_IPADDR &tGkAddr )
    {
        m_tGKAddr = tGkAddr;
    }
    /**得到GK地址*/
    PFC_IPADDR& GetGKAddr()
    {
        return m_tGKAddr;
    }
    
}TIRRINFO, *PTIRRINFO;

/**GRQ结构体*/
typedef struct tagGRQInfo
{	
	PFC_IPADDR		m_tRASAddr;				    /**<终端RAS地址*/
	cmEndpointType	m_eEndpointType;		    /**<终端类型*/
	TALIASADDR		m_tGKID;				    /**<GK ID,GK用*/

	TVENDORINFO		m_tVendorInfo;				/**<产品号*/
	TALIASADDR		m_atAlias[MAXALIASNUM];	    /**<向GK注册时的多个别名*/

	tagGRQInfo()
	{
		Clear();
	}

	void Clear();

    /**设置注册别名*/
    void SetRRQAlias( TALIASADDR &tAlias, u8 byAliasNo )
    {
        if ( byAliasNo >= MAXALIASNUM )
            return;
        
        m_atAlias[byAliasNo] = tAlias;
    }
    /**得到注册的别名*/
    TALIASADDR& GetRRQAlias( u8 byAliasNo )
    {
        if ( byAliasNo < MAXALIASNUM ) 
            return m_atAlias[byAliasNo];
        else
            return m_atAlias[0];        
    }


}TGRQINFO, *PTGRQINFO;

/**GCF结构体*/
typedef struct tagGCFInfo
{	
	TALIASADDR		m_tGKID;				    /**<GK ID,GK用*/
	PFC_IPADDR		m_tRASAddr;				    /**<GK的RAS地址*/

	tagGCFInfo()
	{
		Clear();
	}

	void Clear()
	{
		memset(&m_tGKID,0,sizeof(TALIASADDR));	
		m_tRASAddr.Clear();		
		//m_tRASAddr.SetNetAddress( 0, RASPORT );
	}
}TGCFINFO, *PTGCFINFO;

/**Service Control Session*/
typedef struct tagServiceControlSession
{
	u8       m_bySessionId;
    u8       m_byReason;
}TServiceControlSession, *PTServiceControlSession;

/**SCI for H460*/
typedef struct tagSCIInfo
{
	TServiceControlSession m_tServiceControlSession;
    PFC_IPADDR        m_tCallSignallingAddress;  /**<信令呼叫地址*/
	u8	            m_abyCallId[LEN_GUID];      /**<CallIdentifier*/
	
	tagSCIInfo()
	{
		Clear();
	}
	
	void Clear()
	{
		memset(&m_tServiceControlSession, 0, sizeof(m_tServiceControlSession));
		m_tCallSignallingAddress.Clear();
		memset(m_abyCallId, 0, LEN_GUID);
	}
	
}TSCIINFO, *PTSCIINFO;


/**SCR for H460*/
typedef struct tagSCRINFO
{
	u16             m_wRequestSeqNum;           /**<请求序列编号*/
	TALIASADDR      m_tEndpointID;
	s8	            m_abyCallId[LEN_GUID];      /**<CallIdentifier*/
}TSCRINFO;

#ifdef WIN32
#pragma comment( lib, "ws2_32.lib" ) 
#pragma pack( push )
#pragma pack( 1 )
#define window( x )	x
#ifndef PACKED
#define PACKED
#endif
#else
#include <netinet/in.h>
#define window( x )
#if defined(__ETI_linux__)
#define PACKED
#else
#ifdef PACKED
#undef PACKED
#endif
#define PACKED __attribute__ ((packed))	/**< 取消编译器的优化对齐*/
#endif
#endif

/**Only for TPS*/
#ifdef CBB_FOR_TPS
typedef struct PROTO_API tagNSMInfo
{
	u32          m_dwNSMID;               /**<消息号*/
    u32          m_dwErrorCode;           /**<错误码 回复消息时才有用*/
    u32          m_dwSequenceNumber;      /**<序列号 暂时未用*/
    u32          m_dwContentLen;          /**<消息体内容长度*/
    u32          m_dwStructNum;           /**<消息体的结构体数目*/
    BOOL32       m_bWillContinue;         /**<是否有后续的消息，用于消息体长度太长的情况*/
	TALIASADDR   m_tMTAlias;              /**<终端别名目前只填E164号*/
	u8           m_bybuf[KDV_NSM_MAX_LEN];/**<消息体*/
	
    tagNSMInfo()
    {
        Clear();
    }
	
    void Clear()
	{
		m_dwNSMID            = 0;
		m_dwErrorCode        = 0;       
		m_dwSequenceNumber   = 0;
		m_dwContentLen       = 0;
		m_dwStructNum        = 0;
		m_bWillContinue      = FALSE;	
		memset(m_bybuf,0,KDV_NSM_MAX_LEN);
	}
	
	/**设置别名*/
	void SetAliasAddr( TALIASADDR tAliasAddr )
	{		
		m_tMTAlias.SetAliasAddr(tAliasAddr.GetAliasType(),tAliasAddr.GetAliasName());
		m_tMTAlias.m_emType = (AliasType)htonl(tAliasAddr.m_emType);
	}
	/**获取别名类型*/
    void GetAliasAddr( TALIASADDR &tAliasAddr)
	{
		tAliasAddr.m_emType = (AliasType)ntohl(m_tMTAlias.m_emType);
		tAliasAddr.SetAliasAddr(tAliasAddr.GetAliasType(),m_tMTAlias.GetAliasName());
	}
	void SetNSMID(u32 dwNSMID)
	{ 
		m_dwNSMID = htonl(dwNSMID);
	}
	u32 GetNSMID()
	{
		return ntohl(m_dwNSMID);
	}
	void SetErrorCode(u32 dwErrorCode)
	{
		m_dwErrorCode = htonl(dwErrorCode);
	}
	u32 GetErrorCode()
	{
		return ntohl(m_dwErrorCode);
	}
	void SetSQN(u32 dwSQN)
	{
		m_dwSequenceNumber = htonl(dwSQN);
	}
	u32 GetSQN()
	{
		return ntohl(m_dwSequenceNumber);
	}
	void SetStructNum(u32 dwMsgNum)
	{
		m_dwStructNum = htonl(dwMsgNum);
	}
	u32 GetStructNum()
	{
		return ntohl(m_dwStructNum);
	}
    void SetWillContinue(BOOL32 bWillContinue)
    {
        m_bWillContinue = htonl(bWillContinue);
    }
    BOOL32 IsWillContinue()
    {
        return ntohl(m_bWillContinue);
    }
    void SetContentLen(u32 dwContentLen)
    {
        m_dwContentLen = htonl(dwContentLen);
    }
    u32 GetContentLen()
    {
        return ntohl(m_dwContentLen);
    }
	u8* GetMsgData()
	{
		return (u8*)m_bybuf;
	}
	
	BOOL32 SetMsgData(u8 * pbuf,u32 dwMsgLen)
	{
		if (pbuf == NULL || dwMsgLen > KDV_NSM_MAX_LEN)
		{
			return FALSE;
		}
		memset( m_bybuf, 0, KDV_NSM_MAX_LEN );
		memcpy(m_bybuf,pbuf,dwMsgLen);
		return TRUE;
	}
}
#if defined(_VXWORKS_) || defined(_LINUX_)
__attribute__ ( (packed) ) 
#endif // _VXWORKS_
TNSMInfo,*PTNSMInfo;
#else
typedef struct PROTO_API tagNSMInfo
{
	u32          m_dwNSMID;               /**<消息号*/
    u32          m_dwErrorCode;           /**<错误码 回复消息时才有用*/
    u32          m_dwSequenceNumber;      /**<序列号 暂时未用*/
    u32          m_dwContentLen;          /**<消息体内容长度*/
    u32          m_dwStructNum;           /**<消息体的结构体数目*/
    BOOL32       m_bWillContinue;         /**<是否有后续的消息，用于消息体长度太长的情况*/
	TALIASADDR   m_tMTAlias;              /**<终端别名目前只填E164号*/
	u32          m_dwRas;                 /**<RAS句柄. The only meaning of its existence is to compatible to old MOVISION endpoints*/
	u8           m_bybuf[KDV_NSM_MAX_LEN];/**<消息体*/

    tagNSMInfo()
    {
        Clear();
    }
	
    void Clear()
	{
		m_dwNSMID            = 0;
		m_dwErrorCode        = 0;       
		m_dwSequenceNumber   = 0;
		m_dwContentLen       = 0;
		m_dwStructNum        = 0;
		m_bWillContinue      = FALSE;	
		m_dwRas				 = 0;
		memset(m_bybuf,0,KDV_NSM_MAX_LEN);
	}
   
	/**设置别名*/
	void SetAliasAddr( TALIASADDR tAliasAddr )
	{		
		m_tMTAlias.SetAliasAddr(tAliasAddr.GetAliasType(),tAliasAddr.GetAliasName());
		m_tMTAlias.m_emType = (AliasType)htonl(tAliasAddr.m_emType);
	}
	/**获取别名类型*/
    void GetAliasAddr( TALIASADDR &tAliasAddr)
	{
		tAliasAddr.m_emType = (AliasType)ntohl(m_tMTAlias.m_emType);
		tAliasAddr.SetAliasAddr(tAliasAddr.GetAliasType(),m_tMTAlias.GetAliasName());
	}
	void SetNSMID(u32 dwNSMID)
	{ 
		m_dwNSMID = htonl(dwNSMID);
	}
	u32 GetNSMID()
	{
		return ntohl(m_dwNSMID);
	}
	void SetErrorCode(u32 dwErrorCode)
	{
		m_dwErrorCode = htonl(dwErrorCode);
	}
	u32 GetErrorCode()
	{
		return ntohl(m_dwErrorCode);
	}
	void SetSQN(u32 dwSQN)
	{
		m_dwSequenceNumber = htonl(dwSQN);
	}
	u32 GetSQN()
	{
		return ntohl(m_dwSequenceNumber);
	}
	void SetStructNum(u32 dwMsgNum)
	{
		m_dwStructNum = htonl(dwMsgNum);
	}
	u32 GetStructNum()
	{
		return ntohl(m_dwStructNum);
	}
    void SetWillContinue(BOOL32 bWillContinue)
    {
        m_bWillContinue = htonl(bWillContinue);
    }
    BOOL32 IsWillContinue()
    {
        return ntohl(m_bWillContinue);
    }
    void SetContentLen(u32 dwContentLen)
    {
        m_dwContentLen = htonl(dwContentLen);
    }
    u32 GetContentLen()
    {
        return ntohl(m_dwContentLen);
    }
	u8* GetMsgData()
	{
		return (u8*)m_bybuf;
	}
	u32 GetRas()
	{
		return ntohl(m_dwRas);
	}
	void SetRas(u32 dwRas)
	{
		m_dwRas = htonl(dwRas );
	}

	BOOL32 SetMsgData(u8 * pbuf, u32 dwMsgLen)
	{
		if (pbuf == NULL || dwMsgLen > KDV_NSM_MAX_LEN)
		{
			return FALSE;
		}
		memset( m_bybuf, 0, KDV_NSM_MAX_LEN );
		memcpy(m_bybuf,pbuf,dwMsgLen);
		return TRUE;
	}
}
#if defined(_VXWORKS_) || defined(_LINUX_)
__attribute__ ( (packed) ) 
#endif // _VXWORKS_
TNSMInfo,*PTNSMInfo;
#endif //CBB_FOR_TPS

typedef struct tagNSM_MTList_RSP_BodyHead
{
private:
    cmEndpointType	m_emEndpointType;       /**<终端类型*/
    PFC_IPADDR        m_tRasAddr;           /**<RAS地址*/
    u16				m_wCallAddrNum;         /**<呼叫信令地址的个数 */   
    u16				m_wAliasNum;            /**<别名个数*/
    u32             m_dwAliasBufLen;        /**<压缩后的别名buf长度*/
	
public:
	
    void SetTerminalType( cmEndpointType emEndpointType )
    {
        m_emEndpointType = (cmEndpointType)htonl(emEndpointType);
    }
    cmEndpointType GetTerminalType()
    {
        return (cmEndpointType)ntohl(m_emEndpointType);
    }
	
    void SetAliasNum( u16 wAliasNum )
    {
        m_wAliasNum = htons(wAliasNum);
    }
    u16 GetAliasNum()
    {
        return ntohs(m_wAliasNum);
    }
    
    void SetAliasBufLen( u32 dwAliasBufLen )
    {
        m_dwAliasBufLen = htonl(dwAliasBufLen);
    }
    u32 GetAliasBufLen()
    {
        return ntohl(m_dwAliasBufLen);
    }
	
    void SetRASAddr( PFC_IPADDR &tRASAddr )
    {
        m_tRasAddr = tRASAddr;
    }
    PFC_IPADDR* GetRASAddr()
    {
        return &m_tRasAddr;
    }
	
    void SetCallAddrNum( u16 wCallAddrNum )
    {
        m_wCallAddrNum = htons(wCallAddrNum);
    }
    u16 GetCallAddrNum()
    {
        return ntohs(m_wCallAddrNum);
    }
}
#if defined(_VXWORKS_) || defined(_LINUX_)
__attribute__ ( (packed) ) 
#endif // _VXWORKS_
TNSM_MTList_RSP_BodyHead,*PTNSM_MTList_RSP_BodyHead;

#define KDVTS_ENTERPRISE	(u32)150
#define KDVTS_P1			(u32)160
#define KDVTS_P2			(u32)170


typedef struct tagNSM_TS_CATEGORY_RSP_Body
{
private:
	u32				m_dwTSCategory;     /**< 用于标识是企业版还是运营版*/
	s8				m_achBuf[128];      /**< 暂时未用*/
	
public:
	
    void SetTSCategory( u32 dwTSCategory )
    {
        m_dwTSCategory = htonl(dwTSCategory);
    }
    u32 GetTSCategory()
    {
        return ntohl(m_dwTSCategory);
    }
}
#if defined(_VXWORKS_) || defined(_LINUX_)
__attribute__ ( (packed) ) 
#endif // _VXWORKS_
TNSM_TS_CATEGORY_RSP_Body, *PTNSM_TS_CATEGORY_RSP_Body;

#ifdef WIN32
#pragma pack( pop )
#endif

#endif //_H323CALLSTDSTRUCT_H
