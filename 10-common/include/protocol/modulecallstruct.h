/**
*   COPYRIGHT NOTICE
*   Copyright (C) 2018, KeDaCom
*   All right reserved
*   
*   @file        modulecallstruct.h
*   @author      Sai
*   @version     V5.0_64bit
*   @date        2018-03-05
*   @brief       Call struct for H323/Sip protocol 
*   @details     
*/
#ifndef MODULECALLSTRUCT_H
#define MODULECALLSTRUCT_H

#include "protocolcommonpublic.h"
#include "pfc.h"
#include "kdvdef.h"

/// various macro
#define MAX_LEN_CALLID			128
#define MAX_LEN_CALL_ALIAS		64
#define MAX_LEN_PRODUCT_ID		128
#define MAX_LEN_VERSION_ID		128
#define MAX_AUDIO_NUM			4
#define MAX_VIDEO_NUM			4
#define MAX_FECC_NUM			1
#define MAX_TP_STREAM_NUM		3
#define MAX_ENCRYPT_KEY_LEN		(u8)128
#define MAX_LEN_EPID			64
#define MAX_ALIAS_NUM			64
#define MAX_E164_NUM			64
#define MAX_CONFMT_NUM			192
#define MAX_TERMINALID_LEN		128
#define MAX_PASSWD_LEN			128
#define MAX_ONLINE_LIST_NUM		64

#define AES_KEY_LEN				(u8)16

#define MAX_FLOOR_NUM			5
#define MAX_MEDIA_NUM_PER_FLOOR 5
#define MAX_MEDIA_CAP_NUM		20
#define MAX_CONF_ID_LEN			16
#define MAX_CONF_NAME_LEN		96
#define MAX_CONF_E164_LEN		16
#define MAX_USERNAME_LEN		32			///<  For SIP DIGEST authorization, be noticed that LEN_USERNAME is defined with 64 in kdvsipcommon.h
#define MAX_PASSWORD_LEN		16			///<  If we wish to store the DIGEST password, we must make the password len up to 32 bytes
#define MAX_TERMINAL_NUM		32
#define MAX_DOMAINNAME_LEN      64
#define MAX_DEVID_LEN           128         ///< MAX device id length

#define MAX_MTCAMERA_NUM		7			///<  摄像头最大个数 (与终端定义MT_MAX_CAMERA_NUM统一)
#define MAX_CONF_AUDMIX_NUM_TP	27			///<  最大混音参与数量
#define INVALID_INDEX_TP		0xFFFF

#define MODULE_VIDEO_DEFAULT_BITRATE		768
#define MODULE_VIDEO_DEFAULT_MPI			1
#define MODULE_AUDIO_DEFAULT_TIMEPERCAPTURE 20
#define MODULE_AUDIO_DEFAULT_PAYLOADTYPE	0
#define MODULE_AUDIO_DEFAULT_MAXFRAME		1
#define MODULE_VIDEO_DEFAULT_FRAMERATE		30
#define MODULE_VIDEO_DEFAULT_PAYLOADTYPE	0
#define MODULE_REG_DEFAULT_TIMETOLIVE		60
#define MODULE_CONF_MAX_TERMINALNO			192
#define SEEN_BY_OTHERLIST_MASK_NUM			6
#define TelephoneEventCap_ENCODING_LEN		128
#define MAX_SIP_NONSTD_HEADER_NUM			10
#define MAX_SDP_ATTR_NAME_LEN				50
#define MAX_SDP_ATTR_VALUE_LEN				300
#define MAX_MIX_EP_LIST_LEN                 64		///< max mt count in list
#define MAX_RED_SECENC_NUM					3		///< max SecEncDynPayloadNum of redcap

#define INVALID_ORDER        (-1)

#define INVALID_REGHANDLE   (s32)(-1)

#ifdef _KDV_SRTP_SUPPORT_
#define MODULE_MAX_CRYPTO_NUM 8
#define MODULE_MAX_CRYPTO_KEY_LEN 50
#define MODULE_MAX_MKI_VALUE 50
#endif

#include <string.h> 

#ifndef DECLARE_MODULE_HANDLE
#define DECLARE_MODULE_HANDLE(name)    typedef struct { MemId unused; } name##__ ; \
	typedef const name##__ * name; \
typedef name*  LP##name;
#endif

#ifndef MIN
#define MIN(a,b) ((a)>(b)?(b):(a))
#endif

#ifndef MAX
#define MAX(a,b) ((a)>(b)?(a):(b))
#endif

/// declare all the handles of module level using 
DECLARE_MODULE_HANDLE(HMDLAPPCALL)
DECLARE_MODULE_HANDLE(HMDLCALL)
DECLARE_MODULE_HANDLE(HMDLAPPCHANNEL)
DECLARE_MODULE_HANDLE(HMDLCHANNEL)
DECLARE_MODULE_HANDLE(HMDLREG)
DECLARE_MODULE_HANDLE(HMDLAPPREG)
DECLARE_MODULE_HANDLE(HMDLAPPCONFID)

/// endpoint type of module level
enum emModuleEndpointType
{
	emModuletypeBegin = 0,
	emModuleEndpointMcu,
	emModuleEndpointMT ,
	emModuleEndpointGk , 
	emModuleEndpointGateway,
	emModuleEndpointCNS,
	emModuleEndpointUMS,
	emModuleEndpointVRS,
};

/// alias type of module level
enum emModuleAliasType
{
	emModuleType_aliastype,
	emModuleType_e164 = 0x1,
	emModuleType_h323ID,
	emModuleType_email,
	emModuleType_epID,
	emModuleType_GKID,
	emModuleType_partyNumber,
	emModuleType_others
};

/// call type, ip,alias,e164
enum emModuleCallType
{
	emModuleIPCall,
	emModuleAliasCall,
	emModuleE164Call,
};

/// protocol type in conference list
enum emModuleProtocolType
{
	emModuleTypeInvalid,
	emModuleTypeH323,
	emModuleTypeSip,
	emModuleTypeAll,
};

enum EmMdlReinvitestatus
{
	emMdlReinviteSndfailed,
	emMdlReinviteSndsuccess,
	emMdlAnswerReinvite,            /// answer 200
	emMdlRejectReinvite,            /// answer 500
	emMdlPeerRejectReinvite,        /// peer answer 500
	emMdlReinviteconflict,          /// peer answer 491
};

/// 呼叫挂断原因
enum EmModuleCallDisconnectReason
{
	emModuleDisconnect_Busy = 1   ,///< 对端忙
	emModuleDisconnect_Normal     ,///< 正常挂断
	emModuleDisconnect_Rejected   ,///< 对端拒绝
	emModuleDisconnect_Unreachable ,///< 对端不可达
	emModuleDisconnect_Local       ,///< 本地原因	
	emModuleDisconnect_unknown     ,///< 未知原因

	/// TP
	emModuleDisconnect_AlredayInDualStream, ///< 正在双流中，无法发起或接收双流
	emModuleDisconnect_Normal_Peer,         ///< 对方挂断
	emModuleDisconnect_Abnormal,            ///< 本端掉线挂断
	emModuleDisconnect_Abnormal_Peer,       ///< 对端掉线挂断
	emModuleDisconnect_MultiConfOver,       ///< 多点会议结束
	emModuleDisconnect_ConfAlredayExit,     ///< 会议已经存在
	emModuleDisconnect_InvalidDestAddr,		///< 无效的目的地址

	emModuleDisconnect_CallFull, ///< 呼叫句柄已满(可能存在呼叫句柄未释放的问题)

	emModuleDisconnect_MaxMtNum, ///< 会议中呼叫已达上限

	/// 码流原因
	emModuleDisconnect_StreamEncryptKeyNotEqual,    ///< 呼叫两端支持的码流加密（方式或密钥）不一致

	/// mcu
	emModuleDisconnect_RmtReconnect = 100,   ///<  行政级别比对端低  
	emModuleDisconnect_EncrypeErr,    
	emModuleDisconnect_AdaptBusy,     
	emModuleDisconnect_MccDrop,              ///<  会控挂断     
	emModuleDisconnect_ChairDrop,            ///<  主席挂断     
	emModuleDisconnect_MMcuDrop,             ///<  上级会议挂断  
	emModuleDisconnect_ConfReleaseNoMt,      ///<  无终端自动结会-1分钟   
	emModuleDisconnect_ConfReleaseNoJoinedMt,///<  无在线终端自动结会-5分钟    
	emModuleDisconnect_ConfReleaseOnlyOneMt, ///<  仅一个在线终端自动结会-10分钟  
	emModuleDisconnect_Exception,            ///<  异常挂断   
	emModuleDisconnect_MpDisconnect,         ///< mp掉线    

	/// 终端
	emModuleDisconnect_DonotDisturb,         ///< 免打扰

	/// Tls Cert load failed
	emModuleLoadTlsCertFailed,

	/// MT Authenticate Failed
	emModuleDisconnect_AuthenticationErr,

	emModuleDisconnect_OverMaxPortLicense    ///< over max port license

};

/// the value is same as EmVendorProductId(kdvcommon.h)
enum EmModuleVendorID
{
	emModule_vendor_MICROSOFT_NETMEETING = 1,
	emModule_vendor_KEDA,
	emModule_vendor_HUAWEI,
	emModule_vendor_POLYCOM,
	emModule_vendor_POLYCOM_MCU,
	emModule_vendor_TANDBERG,
	emModule_vendor_RADVISION,
	emModule_vendor_VCON,
	emModule_vendor_SONY,
	emModule_vendor_VTEL,
	emModule_vendor_ZTE,
	emModule_vendor_ZTE_MCU,
	emModule_vendor_CODIAN,
	emModule_vendor_AETHRA,
	emModule_vendor_CHAORAN,
	emModule_vendor_AVCON,
	emModule_vendor_DONJIN,
	emModule_vendor_Cisco,
	emModule_vendor_Yealink,
	emModule_vendor_SmartPhone,
	emModule_vendor_UNKNOWN,
	emModule_vendor_END
};

/// connection  type
enum EmModuleConnection
{
	emModuleConnectionType = 0,
	emModuleTcpConnection,
	emModuleUdpConnection,
	emModuleSCTPConnection,
	emModuleTLSConnection,
	emModuleTcp6Connection,
	emModuleUdp6Connection,
	emModuleTLS6Connection,
};

/// capbility direction
enum EmModuleDirection
{
	emModule_Direction_Begin = 0,
	emModule_Direction_SendOnly = 1,
	emModule_Direction_RecvOnly = 2,
	emModule_Direction_SendRecv = 3,
};



/// call alias address
typedef struct tagCallAliasAddr
{
	u8 m_abyCallAliasAddr[MAX_LEN_CALL_ALIAS + 1];
public:
	tagCallAliasAddr()
	{
		Clear();
	}

	void Clear()
	{
		memset( m_abyCallAliasAddr , 0 , sizeof(m_abyCallAliasAddr) );
	}

	void SetCallAliasAddr( u8* pbyAlias , u16 wLen )
	{
		if ( NULL == pbyAlias || 0 == wLen )
		{
			return;
		}
		strncpy( (s8*)m_abyCallAliasAddr , (s8*)pbyAlias ,  MAX_LEN_CALL_ALIAS );
	}

	void GetAliasAddr( u8* pbyAlias , u16 wLen )
	{
		if ( NULL == pbyAlias || 0 == wLen )
		{
			return;
		}
		strncpy( (s8*)pbyAlias , (s8*)m_abyCallAliasAddr, wLen ); 
	}
}TCallAliasAddr;



enum EmModuleProfileMask
{
	emModuleProfileBaseline = 64,
	emModuleProfileMain		= 32,
	emModuleProfileExtend	= 16,
	emModuleProfileHigh		= 8
};

/// H.264 NAL mode --> packetization mode
enum EmModuleH264NALMode
{
	emModuleNALSingle          = 0,       ///< single
	emModuleNALNoneInterleaved = 1,       ///< not interleaved
	emModuleNALInterleaved     = 2,       ///< interleaved
};

/// h265 profile
enum EmModuleH265ProfileMask
{
	//emModuleH265ProfileGeneral = 1,
	emModuleH265ProfileMain = 1,
	emModuleH265ProfileMain10	,
	emModuleH265ProfileMainStill,
};

/// 视频协议类型
enum EmModuleVideoFormat
{
    emModuleVH261     = 0,
	emModuleVH262     = 1,
	emModuleVH263     = 2,
	emModuleVH263plus = 3,
	emModuleVH264     = 4,
	emModuleVMPEG4    = 5,
	emModuleVH265     = 6,
	
	emModuleVEnd =  10,
};

/// 音频协议类型
enum EmModuleAudioFormat
{
    emModuleAG711a			= 0,
	emModuleAG711u			= 1,
	emModuleAG722			= 2,
	emModuleAG7231			= 3,
	emModuleAG728			= 4,
	emModuleAG729			= 5,
	emModuleAMP3			= 6,
	emModuleAG721			= 7,
	emModuleAG7221			= 8,
	emModuleAG719			= 9,
	emModuleAMpegAACLC		= 10,
	emModuleAMpegAACLD		= 11,
	
	emModuleAMpegAACLCDual	= 12,
	emModuleAMpegAACLDDual	= 13,
	emModuleOPUS            = 14,
	emModuleTelephoneEvent	= 15,
	emModuleRED             = 16,
	emModuleAEnd			= 20,	 
};

/// sampling frequency
enum EmModuleAudioSampleFreq                    
{
	emModuleFs96000 = 0,
    emModuleFs88200 = 1,
    emModuleFs64000 = 2,
    emModuleFs48000 = 3,
    emModuleFs44100 = 4,
    emModuleFs32000 = 5,
    emModuleFs24000 = 6,
    emModuleFs22050 = 7,
    emModuleFs16000 = 8,
    emModuleFs12000 = 9,
    emModuleFs11025 = 10,
    emModuleFs8000  = 11
};

/// audio channel config
enum EmModuleAudioChnlCfg
{
	emModuleChnlCust   = 0,
    emModuleChnl1      = 1,                   ///< 单声道
    emModuleChnl2      = 2,                   ///< 双声道
    emModuleChnl3      = 3,
    emModuleChnl4      = 4,
    emModuleChnl5      = 5,
    emModuleChnl5dot1  = 6,                   ///< 5.1声道
    emModuleChnl7dot1  = 7                    ///< 7.1声道
};

/// 分辨率类型
enum EmModuleVideoResolution
{
    emModuleVResolutionAuto   = 0,   ///< 自动
	emModuleVSQCIF              = 1,   ///< SQCIF128x96
	emModuleVQCIF               = 2,   ///< QCIF176x144
	emModuleVCIF                = 3,   ///< CIF352x288
	emModuleV2CIF               = 4,   ///< 2CIF352x576
	emModuleV4CIF               = 5,   ///< 4CIF704x576
	emModuleV16CIF              = 6,   ///< 16CIF1408x1152
	
	emModuleVHD480i720x480      = 7,   ///< 480i720x480
	emModuleVHD480p720x480      = 8,   ///< 480p720x480
	emModuleVHD576i720x576      = 9,   ///< 576i720x576
	emModuleVHD576p720x576      = 10,  ///< 576p720x576
	emModuleVHD720p1280x720     = 11,  ///< 720p1280x720
	emModuleVHD1080i1920x1080   = 12,  ///< 1080i1920x1080
	emModuleVHD1080p1920x1080   = 13,  ///< 1080p1920x1080
	
	emModuleVGA352x240          = 14,  ///< 352x240
	emModuleVGA704x480          = 15,  ///< 704x480
	emModuleVGA640x480          = 16,  ///< VGA640x480
	emModuleVGA800x600          = 17,  ///< SVGA800x600
	emModuleW4CIF               = 18,  ///< Wide4CIF 16:9 1024*576
	emModuleVGA1024x768         = 19,  ///< XGA1024x768
	emModuleVGA1280x768         = 20,  ///< WXGA1280x768
	emModuleVGA1280x800         = 21,  ///< WXGA1280x800
	emModuleVGA1366x768         = 22,  ///< WXGA1366x768
	emModuleVGA1280x854         = 23,  ///< WSXGA1280x854
	emModuleVGA1440x900         = 24,  ///< WSXGA1440x900
	emModuleVGA1280x1024        = 25,  ///< SXGA1280x1024
	emModuleVGA1680x1050        = 26,  ///< SXGA+1680x1050
	emModuleVGA1600x1200        = 27,  ///< UXGA1600x1200
	emModuleVGA1920x1200        = 28,  ///< WUXGA1920x1200
	
	/// Resolutions supported by H.265, added by zgf according to kdvcommon.h
	emModuleVRes2Kx1K           = 29,			///<  2048 1024  2 097 152  - - - - - 31.8 63.7 
	emModuleVRes2Kx1080         = 30,			///<  2048 1080  2 228 224  - - - - - 30.0 60.0 
	emModuleVRes4XGA            = 31,			///<  2048 1536  3 145 728  - - - - - -  - 
	emModuleVRes16VGA           = 32,			///<  2560 1920  4 915 200  - - - - - -  - 
	emModuleVRes3616x1536       = 33,			///<  (2.35:1)  3616  1536  5 603 328  - - - - - -  - 
	emModuleVRes3672x1536       = 34,			///<  (2.39:1)  3680  1536  5 701 632  - - - - - -  - 
	emModuleVRes3840x2160       = 35,			///<  (4*HD)  3840  2160  8 355 840 - - - - - -  - 
	emModuleVRes4Kx2K           = 36,			///<  4096 2048  8 388 608  - - - - - -  - 
	emModuleVRes4096x2160       = 37,			///<  4096 2160  8 912 896  - - - - - -  - 
	emModuleVRes4096x2304       = 38,			///<  (16:9)  4096  2304  9 437 184  - - - - - -  - 
	emModuleVRes7680x4320       = 39,			///<  7680 4320  33 423 360  - - - - - -  - 
	emModuleVRes8192x4096       = 40,			///<  8192 4096  33 554 432 - - - - - -  - 
	emModuleVRes8192x4320       = 41,			///<  8192 4320  35 651 584 - - - - - -  - 
	emModuleWCIF                = 42,           ///< 512*288
	emModuleVResEnd ,
};

/// conference message type
enum EmModuleConfMsgType
{
	emModuleConfMsgTypeBegin = 500,  ///< 这个要和TP的消息不冲突
		
	emModuleMultipleConference,   ///< NULL
	emModuleCancelMultipleConference, ///< NULL
	emModuleTerminalNumberAssign, ///< TMDLTERLABEL
	emModuleTerminalYouAreSeeing, ///< TMDLTERMINALINFO + BOOL32 + TYouAreSeeing
	emModuleSeenByAll,  ///< NULL
	emModuleCancelSeenByAll,  ///< NULL

	emModuleTerminalListRequest, ///< NULL
	emModuleTerminalListResponce, ///< TMDLTERLABELLIST
	emModuleTerminalIDListRequest, ///< NULL
	emModuleTerminalIDListResponse, ///< TMDLTERINFOLIST + BOOL32 + TConfCnsList

	emModuleTerminalJoinConf,  ///< TMDLTERMINALINFO
	emModuleterminalLeftConf,  ///< TMDLTERMINALINFO

	emModuleRequestTerminalID, ///< TMDLTERLABEL
	emModuleMcTerminalIDResponse, ///< TMDLTERMINALINFO

	emModuleMakeTerQuietCmd, ///< TMDLTERLABEL(dst) + BOOL32(TRUE = 开启/ FALSE = 关闭) 静音
	emModuleMakeTerMuteCmd, ///< TMDLTERLABEL(dst) + BOOL32(TRUE = 开启/ FALSE = 关闭) 哑音
	emModuleChgSecVidSendCmd, ///< BOOL32(发送/关闭) 开-关双流

		//add by yj for confMSG [20130726]
	emModulevideoFpsChangeCmd,		///< u32(emModuleChannelType) + u8(帧率)


	emModulevideoFormatChangeCmd,	    ///< 发送：emModuleVideoType + u8(填入vccommon.h里的视频格式) ( 宽高可以选填，如果填顺序：With(u32)+Height(u32) )
										///< 接收：emModuleVideoType + u32 + u32 (兼容终端，他们那边现在只解析宽高来确定分辨率)
		
										///< *    +   u8  通道类型   LOGCHL_VIDEO      (默认主视频通道)
										///< *    +   u8  分辨率类型 VIDEO_FORMAT_QCIF (176*144)
										///< 注：新的MCU会增加以下宽度和高度字段，老的MCU没有以下字段(PA处理后会直接把宽高带上)
										///< *    +   u32  分辨率宽度 
										///< *    +   u32  分辨率高度
		
	emModuleterStatusInd,				///< TModuleTerStatus ter -> Mc
	emModulesetAudioVolumeCmd,			///<  音量类型(u8) + 音量(u8)
		//end [20130726]

	/// added by sna for dual channel on/off [20140107]
	emModuleStartRcvDualInd,			///< NULL
	emModuleStopRcvDualInd,				///< NULL
		//added end [20140107]
	emModuleNSMGeneral,              ///< 非标会控消息added by hong[20140910]

	emModuleChairSelectViewCmd,  ///< TMDLTERLABEL(dst) + u32(EmDataType:audio、video、av) 主席选看--非标
	emMoudleSendThisSource,      ///< TMDLTERLABEL(dst) + u32(EmCtrlMode:command、request)  选看终端--标准
	emMoudleSendThisSourceResponse, ///< B00L32(bGranted:TRUE FALSE)
	emMoudleCancelSendThisSource, ///< NULL
	emMoudleVideoAliasInd,
	emModuleKedaManuProduct,			///< 防串货渠道标识， mt<-->mcu，mt<-->mt非标内容：
										///< V5.0 <--> V5.0: protobuf
										///< V5.0 <--> V4.x(HD3): TKedaManuProduct
										///< TPS <--> TPS: TKedaManuProduct
	emModuleConfInfoRsp,		        ///< 会议基本信息和状态	
	emModuleConfMsgTypeEnd
};

/// mcu-mcu msg type
enum EmModuleMMcuMsgType
{
	emModuleMMcuBegin = emModuleConfMsgTypeEnd + 1,			

	emModuleRegUnReg_Req,		///< [IN]&[OUT]:[TRegUnRegReq]	register request

	emModuleRegUnReg_Rsp,		///< [IN]&[OUT]:[TRegUnRegRsp]	register response

	emModuleNewRoster_Ntf,		///< [IN]&[OUT]:[TRosterList]  roster notify

	emModulePartList_Req,		///< [IN]&[OUT]:[TReq]         request part list

	emModulePartList_Rsp,		///< [IN]&[OUT]:[TPartListMsg + n*sizeof(TPart)] reponse part list (dwpid ==0 表示对方的MCU)

	emModuleInvitePart_Req,		///< [IN]&[OUT]:[TInvitePartReq]  invite part request

	emModuleInvitePart_Rsp,		///< [IN]&[OUT]:[Tsp]             invite part response

	emModuleNewPart_Ntf,		///< [IN]&[OUT]:[TPart]           new part notify

	emModuleCall_Alerting_Ntf,	///< [IN]&[OUT]:[TCallNtf]

	emModuleReinvitePart_Req,	///< [IN]&[OUT]:[TReInviteReq]    reinvite part request

	emModuleReinvitePart_Rsp,	///< [IN]&[OUT]:[Tsp]        reinvite part response

	emModuleDisconnPart_Req,	///< [IN]&[OUT]:[TPartReq]     disconnect part request

	emModuleDisconnpart_Rsp,	///< [IN]&[OUT]:[Tsp]         disconnect part response

	emModuleDisconnpart_Ntf,	///< [IN]&[OUT]:[TDiscPartNF] disconnect part notify

	emModuleDeletepart_Req,		///< [IN]&[OUT]:[TPartReq]		delete part request

	emModuleDeletepart_Rsp,		///< [IN]&[OUT]:[Tsp]			delete part response

	emModuleDeletepart_Ntf,		///< [IN]&[OUT]:[TPartNtf]   delete part notify (whether or not local)

	emModuleSetIn_Req,			///< [IN]&[OUT]:[TSetInReq]    request video in

	emModuleSetIn_Rsp,			///< [IN]&[OUT]:[Tsp]          response msg

	emModuleSetOut_Req,			///< [IN]&[OUT]:[TSetOutReq],视频输出到自己的请求(视频流向:MCU->MT)

	emModuleSetOut_Rsp,			///< [IN]&[OUT]:[Tsp]//视频输出到自己的应答(视频流向:MCU->MT)

	emModuleOutPut_Ntf,			///< [IN]&[OUT]:[TPartOutputNtf]      video output notify (dwpid ==0 表示对方的MCU)

	emModuleNewSpeaker_Ntf,		///< [IN]&[OUT]:[TNewSpeakerNtf]      newSpeaker output notify (dwpid ==0 表示对方的MCU)

	emModuleAudioInfo_Req,		///< [IN]&[OUT]:[TConfVideInfoReq]         audio info request 

	emModuleAudioInfo_Rsp,		///< [IN]&[OUT]:[TConfAudioInfo]    audio info response

	emModuleVideoInfo_Req,		///< [IN]&[OUT]:[pReq]          conference videoinfo request

	emModuleVideoInfo_Rsp,		///< [IN]&[OUT]:[TConfVideoInfo] conference videoinfo response

	emModuleConfView_Chg_Ntf,	///< [IN]&[OUT]:[TConfViewChgNtf] conference view format(layout geometry)change notify

	emModulePartMediaChan_Req,	///< [IN]&[OUT]:[TPartMediaChanReq] 请求会议成员打开/关闭音/视频/数据通道

	emModulePartMediaChan_Rsp,	///< [IN]&[OUT]:[TRsp]    response

	emModulePartMediaChan_Ntf,	///< [IN]&[OUT]:[TPartMediaChanNtf] 会议成员的音/视频/数据通道打开/关闭的通知

	emModuleGetMcuServiceList_Req,	///< [IN]&[OUT]:[TReq] 获取MCU上的服务模板列表的请求消息

	emModuleGetMcuServiceList_Rsp,	///< [IN]&[OUT]:[暂时未定义]  response

	emModuleGetMucConfList_Req,		///< [IN]&[OUT]:[TMCUConfListReq] 获取MCU上当前召开的所有会议的列表

	emModuleGetMucConfList_Rsp,		///< [IN]&[OUT]:[暂时未定义]

	emModuleGetConfgIdByName_Req,	///< [IN]&[OUT]:[TGetConfIDByNameReq] 通过会议名字获得会议ID的请求消息

	emModuleGetConfgIdByName_Rsp,	///< [IN]&[OUT]:[暂时未定义]

	emModuleGet_ConfProfile_Req,	///< [IN]&[OUT]:[TConfProfileReq] 获取MCU上当前召开的所有会议的profile

	emModuleGet_ConfProfile_Rsp,	///< [IN]&[OUT]:[暂时未定义]

	emModuleNonStandard_Req,		///< [IN]&[OUT]:[TNonStandardReq] 非标(自定义)请求消息

	emModuleNonStandard_Rsp,		///< [IN]&[OUT]:[TNonStandardRsp] 非标(自定义)response消息

	emModuleNonStandard_Ntf,		///< [IN]&[OUT]:[TNonStandardMsg] 非标(自定义)notify消息

	emModuleNot_Supported,			///< 目前我们还不支持,但是radmuc支持的消息类型

	emModuleVA_Req,					///< [IN]&[OUT]:[TVAReq]

	emModuleVA_Rsp,					///< [IN]&[OUT]:[TRsp]

	emModuleReleaseControl_of_Conf_Req,		///< [IN]&[OUT]:[]

	emModuleReleaseControl_of_Conf_Rsp,		///< [IN]&[OUT]:[]

	emModuleTakeControl_of_Conf_Req,		///< [IN]&[OUT]:[]

	emModuleTakeControl_of_Conf_Rsp,		///< [IN]&[OUT]:[]

	emModuleAllPart_SetOut_Req,				///< [IN]&[OUT]:[]

	emModuleAllPart_SetOut_Rsp,				///< [IN]&[OUT]:[]

	emModuleCreate_Conf_Req,				///< [IN]&[OUT]:[]

	emModuleCreate_Conf_Rsp,				///< [IN]&[OUT]:[]

	emModuleTerminate_Conf_Req,				///< [IN]&[OUT]:[]

	emModuleTerminate_Conf_Rsp,				///< [IN]&[OUT]:[]

	emModuleUndefined_Req,					///< [IN]&[OUT]:[]

	emModuleUndefined_Rsp,					///< [IN]&[OUT]:[]

	emModuleUndefined_Ntf,					///< [IN]&[OUT]:[]

	emModuleSet_Layout_AutoSwitch_Request,	///< [IN]&[OUT]:TSetLayoutAutoswitchReq

	emModuleSet_Layout_AutoSwitch_Response,

	emModuleMMcuEnd
};

/// 数据类型
enum  EmDataType 
{
	emModeNone = 0,
	emModeAudio,
	emModeVideo,
	emModeData,
};

/// 会议操作:makeTerminalBroadcaster和sendThisSource的操作方式
enum EmCtrlMode 
{
	emModeInvalid = -1,
	emModeCommand,
	emModeRequest,
};

/// 呼叫模式
enum EmCallModeType
{
	emModeJoin,
	emModeCreate,
	emModeInvite
};

/// 加密类型
enum EmMdlEncryptType
{
	emMdlEncryptTypeNone = 1,///< 00000001
	emMdlEncryptTypeDES  = 2,///< 00000010
	emMdlEncryptTypeAES  = 4,///< 00000100
	emMdlEncryptTypeH239 = 8,///< 00001000
	emMdlEncryptTypeAES256  = 16,///< 00010000
};

/// srtp
#ifdef _KDV_SRTP_SUPPORT_
enum EmMdlSrtpMode
{
	emMdlSrtpModeNone,
	emMdlSrtpModeOptional,
	emMdlSrtpModeMandatory
};
enum EmMdlSrtpCryptoType
{
	emMdlSrtpCryptoNone = 0,     ///< 不加密
	emMdlSrtpCryptoAES_CM_128,
	emMdlSrtpCryptoAES_CM_192,
	emMdlSrtpCryptoAES_CM_256,
	emMdlSrtpCryptoAES_GCM_128, 
	emMdlSrtpCryptoAES_GCM_192,
	emMdlSrtpCryptoAES_GCM_256,    
	emMdlSrtpCryptoSM4_CM_128,    ///< SM目前只有128的  
	emMdlSrtpCryptoSM1_CM_128, 
};

/// for AES-CM and SM,the authType is HMAC_SHA1 and have tag length
///< for AES-GCM,only has tag length
enum EmMdlSrtpAuthType
{
	emMdlSrtpAuthNone = 0,     ///< 不认证
	emMdlSrtpAuthTag_8,
	emMdlSrtpAuthTag_16,
	emMdlSrtpAuthTag_32,
	emMdlSrtpAuthTag_80,	
};

/// srtp config
typedef struct tagMdlMediaSrtpCrypto
{
	s32 m_nTag;
	EmMdlSrtpCryptoType m_emCryptoType;
	EmMdlSrtpAuthType   m_emAuthType;
	s8 m_achCryptoKey[MODULE_MAX_CRYPTO_KEY_LEN];
	s8 m_achMkiValue[MODULE_MAX_MKI_VALUE];
	u32 m_dwMkiLen;
	tagMdlMediaSrtpCrypto()
	{
		Clear();
	}
	void Clear()
	{
		m_nTag = 0;
		m_emCryptoType = emMdlSrtpCryptoNone;
		m_emAuthType   = emMdlSrtpAuthNone;
		memset(m_achCryptoKey, 0, sizeof(m_achCryptoKey));
		memset(m_achMkiValue, 0, sizeof(m_achMkiValue));
		m_dwMkiLen = 0;
	}
} TMdlMediaSrtpCrypto;
typedef struct tagMdlSrtpMediaSetting
{
	EmMdlSrtpMode m_emSrtpMode;
	u32 m_dwCryptoCount;
	TMdlMediaSrtpCrypto m_atSrtpCrypto[MODULE_MAX_CRYPTO_NUM];

	tagMdlSrtpMediaSetting()
	{
		Clear();
	}
	void Clear()
	{
		m_emSrtpMode = emMdlSrtpModeNone;
		m_dwCryptoCount = 0;
		for (s32 i = 0; i < sizeof(m_atSrtpCrypto)/sizeof(m_atSrtpCrypto[0]); i++)
		{
			m_atSrtpCrypto[i].Clear();
		}
	}
} TMdlSrtpMediaSetting;
#endif

/// 防串货渠道标识， mt<-->mcu，暂定此非标内容长度为一个BYTE，用于存储渠道标识代号
///< 对应非标消息h_ctrl_KedaManuProduct	= 1121
typedef struct tagKedaManuProductTP
{
	u8	m_byAgentID; ///< 暂定此非标内容长度为一个BYTE，用于存储渠道标识代号
	tagKedaManuProductTP()
	{
		m_byAgentID = 0;
	}
}TKedaManuProductTP;

typedef struct tagTMdlPollInfoTP
{
	BOOL32 m_bIsPoll;
	u16  m_wPollExpire;
	
	tagTMdlPollInfoTP()
	{
		Clear();
	}

	void Clear()
	{
		//memset( this, 0, sizeof(tagTMdlPollInfoTP) );
		m_bIsPoll		= FALSE;
		m_wPollExpire = 0;
	}
}TMdlPollInfoTP;

typedef struct tagTMdlConfAuxMixInfoTP
{
	BOOL32 m_bStart;
	u16	m_wConfID;
	u16 m_wSpeakerIndex;					///< 下面数组的索引
	u16	m_awList[MAX_CONF_AUDMIX_NUM_TP];	///< 混音ID

	void Clear()
	{
		m_bStart			= FALSE;
		m_wConfID			= INVALID_INDEX_TP;
		m_wSpeakerIndex	= 0;
		memset(this, 0, sizeof(tagTMdlConfAuxMixInfoTP));
	}
	tagTMdlConfAuxMixInfoTP()
	{
		Clear();
	}
}TMdlConfAuxMixInfoTP;

typedef struct tagTMdlSpeechMixTP
{
	u32          m_mode;        //0:idle   1: smart   2:custom
	u16          m_wNum;
	u16          m_awMixEp[MAX_MIX_EP_LIST_LEN];
	BOOL32       m_bVacOn;

	void Clear()
	{
		m_mode = 0;
		m_wNum = 0;
		m_bVacOn = 0;
		memset(m_awMixEp, 0, MAX_MIX_EP_LIST_LEN);
		memset(this, 0, sizeof(tagTMdlSpeechMixTP));
	}

	tagTMdlSpeechMixTP()
	{
		Clear();
	}
}TMdlSpeechMixTP;

/// conference info
typedef struct tagTMdlConfInfo
{
	s8	 m_achConfId[MAX_CONF_ID_LEN + 1];			    ///<  会议ID
	s8	 m_achConfName[MAX_CONF_NAME_LEN + 1];		    ///<  会议名
	s8	 m_achConfNumber[MAX_CONF_E164_LEN + 1];	    ///<  会议号码
	s8	 m_achConfPwd[MAX_PASSWORD_LEN + 1];			///<  会议密码
	BOOL32 m_bNeedPassword;                             ///<  是否需要密码
	u16  m_wConfDuration;							    ///<  会议持续时间		
	EmModuleVideoFormat   m_emVideoFormat;			///<  会议视频格式(VIDEO_H261等)
	EmModuleAudioFormat   m_emAudioFormat;			///<  会议音频格式(AUDIO_MP3等)
	EmModuleVideoResolution  m_emResolution;			///<  会议视频分辨率(VIDEO_CIF等)
// 	EmModuleProfileMask m_emProfile;					// 主流profile
	u32 m_emProfile;					///<  主流profile
	u8 m_byVidMPI;					                ///<  主流帧率
	BOOL32 m_bIsAutoVMP;								///<  是否自动画面合成
	BOOL32 m_bIsMix;	    							///<  是否混音
	EmModuleVideoFormat	m_emSecVideoFormat;			///<  双流格式
	EmModuleVideoResolution m_emSecVidRes;			///<  双流分辨率
// 	EmModuleProfileMask m_emSecProfile;				//  双流profile
	u32 m_emSecProfile;				///<  双流profile
	u8 m_bySecVidMPI;					                ///<  双流帧率
	u16 m_wCallRate;									///<  呼叫速率(kbps)
	u16	m_wDualCallRate;								///<  双流呼叫速率(kbps)
	TMdlPollInfoTP  m_tPollInfo;
	TMdlConfAuxMixInfoTP m_tConfAudMixInfo;
	TMdlSpeechMixTP      m_tSpeechMixInfo;

public:
	tagTMdlConfInfo()
	{ 
		Clear();	
	}
	void Clear()
	{
		memset( this, 0, sizeof(tagTMdlConfInfo) );
		m_tPollInfo.Clear();
		m_tConfAudMixInfo.Clear();
		m_tSpeechMixInfo.Clear();
	}
}TMdlConfInfo, *PTMdlConfInfo;

/// encrypt key
typedef struct tagModuleTEncryptKey
{
	EmMdlEncryptType m_emEncryptType;
	u8 m_byLen;   ///< 密钥长度
	u8 m_abyKey[MAX_ENCRYPT_KEY_LEN]; ///< 密钥长度
public:
	void Clear()
	{
		memset( this, 0, sizeof(tagModuleTEncryptKey) );
		m_emEncryptType = emMdlEncryptTypeNone;
	}
	tagModuleTEncryptKey()
	{
		Clear();
	}

	/// 设置H235Key
	u8 SetEncryptKey(u8 *pBuf, u8 byLen)
	{
		m_byLen = MIN(byLen, MAX_ENCRYPT_KEY_LEN);
		memcpy(m_abyKey, pBuf, m_byLen);
		return m_byLen;
	}	
	/// 获取H235Key的长度
	u8 GetEncryptKeyLen() 
	{
		return m_byLen; 
	}
	/// 获取H235Key
	u8* GetEncryptKey()
	{
		return m_abyKey;
	}

	/// set/get encrypt type
	void SetEncryptType( EmMdlEncryptType emEncryptType )
	{
		m_emEncryptType = emEncryptType;
	}
	EmMdlEncryptType GetEncryptType()
	{
		return m_emEncryptType;
	}

	/// generate a key
	struct tagModuleTEncryptKey & GenerateEncrytKey()
	{
		s32 i = 0;
		s8 abyBuf[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz,./;\"'<>?";
		s32 nstrLen = strlen( abyBuf );
		
		if ( m_emEncryptType == emMdlEncryptTypeAES )	// 16BYTE
		{
			for( i = 0; i < AES_KEY_LEN; i++ )
			{
				sprintf( (s8*)m_abyKey+i, "%c", abyBuf[rand() % nstrLen] );
			}
			m_byLen = AES_KEY_LEN;
		}
		else if (m_emEncryptType == emMdlEncryptTypeDES)  // 8BYTE
		{
			for( i = 0; i < 8; i++ )
			{
				sprintf( (s8*)m_abyKey+i, "%c", abyBuf[rand() % nstrLen] );
			}
			m_byLen = 8;
		}
		else
		{
			m_byLen = 0;
		}
		return *this;
	}

	void Print()
	{
		PfcPrintf(TRUE, FALSE, "TModuleEncryptKey:EncryptType=%d, m_byLen=%d, key:", m_emEncryptType, m_byLen);
		s32 nLen = Minimum(m_byLen, AES_KEY_LEN);
		if ( emMdlEncryptTypeNone != m_emEncryptType )
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

}TModuleEncryptKey;


/// 终端地址
typedef struct tagTerminalAddress
{
	emModuleCallType	m_emCallType;
	s8	                m_achAlias[MAX_LEN_CALL_ALIAS + 1];	    ///< 终端别名或E164号
	PFC_IPADDR	        m_tModuleAddress;	    ///< 终端IP地址
	emModuleProtocolType m_emProtocolType;      ///< protocol type in conference list

public:
	tagTerminalAddress()
	{
		Clear();
	}
	void Clear()
	{
		m_emCallType     = emModuleAliasCall;
		m_emProtocolType = emModuleTypeInvalid;
		memset(m_achAlias, 0 ,sizeof(m_achAlias));
		m_tModuleAddress.Clear();
	}
}TerminalAddress, *PTerminalAddress;

/// sip nonstandard header
typedef struct PROTO_API tagSipNstHeader
{
	s8	m_achName[MAX_SDP_ATTR_NAME_LEN];	/**< Param/header name.	    */
	s8	m_achValue[MAX_SDP_ATTR_VALUE_LEN];	/**< Param/header value.    */

	void Clear()
	{
		memset(m_achName, 0, sizeof(m_achName));
		memset(m_achValue, 0, sizeof(m_achValue));
	}
	tagSipNstHeader()
	{
		Clear();
	}
}TSipNstHeader;

typedef enum 
{
	emModuleTlsNone= 0,
	emModuleStdTls = 1,
	emModuleGMTls  = 2,
	emModuleQTTls  = 3
}EmModuleTlsType;

/// call info struct for module both 323 and sip
typedef struct tagModuleCallInfo
{
	u8 m_abyCallId[MAX_LEN_CALLID];                 ///< CallId Attribute,Max Length is 128 bytes
	
	u16 m_wBitrate;                                 ///< Bit rate
	emModuleEndpointType m_emEndpointType;          ///< Endpoint Type;0-Begin,1-Mcu,2-MT,3-GK,4-Gateway,5-CNS,6-UMS,7-VRS
	emModuleEndpointType m_emPeerEndpointType;      ///< PeerEndpoint Type;0-Begin,1-Mcu,2-MT,3-GK,4-Gateway,5-CNS,6-UMS,7-VRS
	
	emModuleCallType    m_emCallType;               ///< Call Type; 0-IP,1-Alias,2-E164
	EmModuleConnection  m_emSipConnection;          ///< Connection Type;0-initial,1-TCP,2-UDP,3-SCTP,4-TLS,5-TCP6,6-UDP6,7-TLS6
	
	PFC_IPADDR m_emCallerIp;                        ///< Caller Ip Address Struct
	PFC_IPADDR m_emCalleeIp;                        ///< Callee Ip Address Struct
	
	TCallAliasAddr m_emCallerAlias;                 ///< Caller Alias Struct
	TCallAliasAddr m_emCalleeAlias;                 ///< Callee Alias Struct
	
	TCallAliasAddr m_emCallerE164;                  ///< Caller E164 Struct
	TCallAliasAddr m_emCalleeE164;                  ///< Callee E164 Struct
	
	s8 m_achLocalProductId[MAX_LEN_PRODUCT_ID + 1]; ///< Local Product Id；MAX_LEN_PRODUCT_ID-128
	s8 m_achLocalVersionId[MAX_LEN_VERSION_ID + 1]; ///< Local Version Id；MAX_LEN_VERSION_ID-128
	
	s8 m_achPeerProductId[MAX_LEN_PRODUCT_ID + 1];  ///< PeerProduct Id；MAX_LEN_PRODUCT_ID-128
	s8 m_achPeerVersionId[MAX_LEN_VERSION_ID + 1];  ///< PeerVersion Id；MAX_LEN_VERSION_ID-128
	
	EmModuleVendorID m_emVendorId;                  ///< VendorId;1-MICROSOFT_NETMEETING,2-KEDA,3-HUAWEI,4-POLYCOM,5-POLYCOM_MCU,6-TANDBERG,7-RADVISION,8-VCON,
	                                                ///< 9-SONY,10-VTEL,11-ZTE,12-ZTE_MCU,13-CODIAN,14-AETHRA,15-CHAORAN,16-AVCON,17-DONJIN,18-UNKNOWN,19-END

	EmModuleVendorID m_emPeerVendorId;              ///< PeerVendorId;1-MICROSOFT_NETMEETING,2-KEDA,3-HUAWEI,4-POLYCOM,5-POLYCOM_MCU,6-TANDBERG,7-RADVISION,8-VCON,
	                                                ///< 9-SONY,10-VTEL,11-ZTE,12-ZTE_MCU,13-CODIAN,14-AETHRA,15-CHAORAN,16-AVCON,17-DONJIN,18-UNKNOWN,19-END
	EmCallModeType   m_emCallMode;			        ///< CallMode;0-JOIN,1-CREATE,2-INVITE

	BOOL32 m_bIsInterworking;				        ///< added by sna for interworking [20140214];TRUE/FALSE

	///The following is only used to create a conference.
	BOOL32				m_bCreateConf;		        ///< Whether to create a conference
	u8					m_byTerNum;			        ///< Number of invited terminals
	TerminalAddress		m_atList[MAX_TERMINAL_NUM];	///< Invited terminal list；MAX_TERMINAL_NUM-32
	TMdlConfInfo		m_tConfInfo;			    ///< conference information
	
	BOOL32				m_bNatCall;	                ///< Whether to call through NAT

	TModuleEncryptKey	m_tStreamKey;	            ///< EncryptKey;if m_tStreamKey.m_emEncryptType=emMdlEncryptTypeNone,the code stream is not encrypted
	u32					m_dwSendRoundTripTime;	    ///< Send RoundTripTimeout (s)
	u32					m_dwRecvRoundTripTime;	    ///< Receive RoundTrip Timeout (s)
	u32					m_dwStaticNATAddr;		    ///< Static NAT Address

	BOOL32              m_bStrongAut;               ///< Call for strong authentication;TRUE/FALSE
	
	s8 m_achPassword[MAX_PASSWORD_LEN+1];           ///< Password；MAX_PASSWORD_LEN-16
	s8 m_achUsername[MAX_LEN_CALL_ALIAS+1];	        ///< Username；MAX_LEN_CALL_ALIAS-64
	s8 m_achDomainName[MAX_DOMAINNAME_LEN+1];       ///< DomainName；MAX_DOMAINNAME_LEN-64

	u8 m_byNonStdHdrNum;	                        ///< non-standard headers number
	TSipNstHeader m_atNonStdHdr[MAX_SIP_NONSTD_HEADER_NUM];	 ///< non-standard headers,KdNstd-为sip协议栈内部标示,业务不需要填下来；MAX_SIP_NONSTD_HEADER_NUM-10

	EmModuleTlsType m_emTlsType; ///<tls type
public:
	tagModuleCallInfo()
	{
		Clear();
	}
	
	void Clear()
	{
		m_emVendorId     = emModule_vendor_KEDA;
		m_emPeerVendorId = emModule_vendor_KEDA;
		m_emEndpointType = emModuleEndpointMT;
		m_emPeerEndpointType = emModuleEndpointMT;
		m_emCallType         = emModuleIPCall;
		m_emSipConnection    = emModuleUdpConnection;
//		m_emSipConnection    = emModuleTLSConnection;
		memset( m_achLocalProductId , 0 , sizeof(m_achLocalProductId) );
		memset( m_achLocalVersionId , 0 , sizeof(m_achLocalVersionId) );
		memset( m_achPeerProductId ,  0 , sizeof(m_achPeerProductId) );
		memset( m_achPeerVersionId ,  0 , sizeof(m_achPeerVersionId) );
		memcpy( m_achLocalProductId, "kedacom", sizeof("kedacom") );
		memcpy( m_achLocalVersionId, "unknown", sizeof("unknown") );
		memset( m_abyCallId , 0 , sizeof(m_abyCallId) );
		memset( m_achPassword, 0, sizeof( m_achPassword) );
		memset( m_achUsername, 0, sizeof(m_achUsername) );
		memset( m_achDomainName, 0, sizeof(m_achDomainName) );
		m_wBitrate = 768;
		m_emCallMode  = emModeCreate;
		m_bCreateConf = FALSE;
		m_byTerNum = 0;
		m_tConfInfo.Clear();
		m_bNatCall = FALSE;
		m_bIsInterworking = FALSE;
		for ( u8 i = 0; i < MAX_TERMINAL_NUM; i++ )
		{
			m_atList[i].Clear();
		}
		m_tStreamKey.Clear();
		m_dwSendRoundTripTime = 0;
		m_dwRecvRoundTripTime = 0;
		m_dwStaticNATAddr	  = 0;
		m_byNonStdHdrNum      = 0;
		for ( u8 j = 0; j < MAX_SIP_NONSTD_HEADER_NUM; j++ )
		{
			m_atNonStdHdr[j].Clear();
		}
		m_emTlsType = emModuleTlsNone;  
		m_bStrongAut = FALSE;
	}
}TModuleCallInfo;

/// 视频描述项
struct TVideoDescript
{
	EmModuleVideoResolution m_emRes; ///< 分辨率
	u8                m_byMPI;       ///< 帧率 1=30 2=15 ...? Where is the definition about the MPI values?
	u16               m_wMaxBitrate; ///< 支持最大码率
public:
	TVideoDescript()
	{
		Clear();
	}

	void Clear()
	{
		m_emRes			= emModuleVResEnd;
		m_byMPI			= MODULE_VIDEO_DEFAULT_MPI;
		m_wMaxBitrate	= MODULE_VIDEO_DEFAULT_BITRATE;
	}
};

/// 指定视频格式能力列表
struct TVideoFormatCapbility
{
	u8     m_byNum;
	u8     m_byDynamicPayload;
	EmModuleVideoFormat m_emFormat;
	EmModuleH264NALMode m_emH264NALMode; ///< h264用
	u32	   m_emProfile; ///< h264 h265用
	TVideoDescript      m_atItem[emModuleVResEnd]; ///< for h264 and h265, only Max Resolution enable 
	
	TVideoFormatCapbility()
	{
		Clear();
	}

	void Clear()
	{
		m_byNum				= 0;
		m_emFormat			= emModuleVEnd;
		m_byDynamicPayload	= 0;
		m_emProfile			= 0;
		m_emH264NALMode     = emModuleNALSingle;
		for (u8 i = 0; i < emModuleVResEnd; i ++)
		{
			m_atItem[i].Clear();
		}
	}
};

/// rtcp feedback
struct TMdlRtcpFeedbackParam
{
	BOOL32 m_bRtcpFbFir;     ///< cmm fir
	BOOL32 m_bRtcpFbTmmbr;   ///< cmm tmmbr
	BOOL32 m_bRtcpFbPli;     ///< nack pli

public:
	TMdlRtcpFeedbackParam()
	{
		Clear();
	}

	void Clear()
	{
		m_bRtcpFbFir   = FALSE;   
		m_bRtcpFbTmmbr = FALSE;
		m_bRtcpFbPli   = FALSE;  
	}
};
/// 视频能力表
struct TVideoCapbilityList
{
	u8 m_byNum;
	TVideoFormatCapbility m_atList[emModuleVEnd];
	
	HMDLAPPCHANNEL m_hAppChan;
	PFC_IPADDR m_tRtpAddr;
	PFC_IPADDR m_tRtcpAddr;
	BOOL32 m_bActive;
	u8     m_byBitratePercent;
#ifdef _KDV_SRTP_SUPPORT_
	TMdlSrtpMediaSetting m_tSrtpSetting;
#endif
		
	TMdlRtcpFeedbackParam   m_tRtcpFbParam; ///< rtcp feedback mode
	BOOL32 m_bRtcpMux;    ///< is use rtcp_mux
public:
	TVideoCapbilityList()
	{
		Clear();
	}

	void Clear()
	{
		m_byNum = 0;
		m_hAppChan = NULL;

		for ( u8 i=0; i<emModuleVEnd; i++ )
		{
			m_atList[i].Clear();
		}
		m_tRtpAddr.Clear();
		m_tRtcpAddr.Clear();
		m_bActive = TRUE;
		m_byBitratePercent = 0;
#ifdef _KDV_SRTP_SUPPORT_
		m_tSrtpSetting.Clear();
#endif
		m_tRtcpFbParam.Clear();
		m_bRtcpMux = FALSE;
	}
};


typedef struct tagTEncodeDescript
{
	EmModuleAudioFormat m_emFormat;			///< If the media format is less than 96, use the media format value,m_wDynamicPayload=0
	u16					m_wDynamicPayload;
	tagTEncodeDescript()
	{
		Clear();
	}
	void Clear()
	{
		m_emFormat = emModuleAEnd;
		m_wDynamicPayload = 0;
	}
} TEncodeDescript;



/// 音频描述项
struct TAudioDescript
{
	EmModuleAudioFormat m_emFormat;
	u8           m_byPackTime;
	u8           m_byDynamicPayload;

	
	EmModuleAudioSampleFreq m_emSampleFreq;
	/// AAC 用
	EmModuleAudioChnlCfg	m_emChnlCfg;
	u8                      m_abySpecificConfig[2];///< AAC-LC直接设置用，临时修改
	u8                      m_abyMuxConfig[7];///< AAC-LD直接设置用，临时修改
	BOOL32                  m_bOldConfig; // is old config version (2B)

	///  g7231用
	u8				m_byMaxFrameNum;		///< 单包最大的帧数
	BOOL32			m_bSilenceSuppression;	///< 是否静音抑制
	
	/// g7221用
	u16				m_wBitRate;

	/// TelephoneEvent 用
	///< this array must use '0' or '1' to fill when you want to use 
	///< EventEncoding default value is 0-15
	s8 m_achEventEncoding[TelephoneEventCap_ENCODING_LEN];

public: 
	TAudioDescript()
	{
		Clear();
	}

	void Clear()
	{
		m_emFormat				= emModuleAEnd;
		m_byPackTime			= MODULE_AUDIO_DEFAULT_TIMEPERCAPTURE;
		m_byDynamicPayload		= MODULE_AUDIO_DEFAULT_PAYLOADTYPE;
		m_emChnlCfg				= emModuleChnl1;
		m_emSampleFreq			= emModuleFs32000;
		m_byMaxFrameNum			= MODULE_AUDIO_DEFAULT_MAXFRAME;
		m_bSilenceSuppression	= FALSE;
		m_wBitRate				= 0;
		memset(m_achEventEncoding, 0,sizeof(m_achEventEncoding));
		memset(m_abySpecificConfig,0,sizeof(m_abySpecificConfig));
		memset(m_abyMuxConfig,     0,sizeof(m_abyMuxConfig));
		m_bOldConfig = FALSE;
	}
};


struct TRedEncode
{
	TEncodeDescript m_tPriEncode;							///< primary encoding
	TEncodeDescript m_atSecEncode[MAX_RED_SECENC_NUM];		///< secondary encoding
	u8	m_bySecEncodedNum;									///< the number of secondary encoding
public: 
	TRedEncode()
	{
		Clear();
	}

	void Clear()
	{
		m_bySecEncodedNum = 0;
		m_tPriEncode.Clear();
		for ( u8 i=0; i<MAX_RED_SECENC_NUM; i++ )
		{
			m_atSecEncode[i].Clear();
		}
	}
};


struct TRedDescript : public TAudioDescript
{
	TRedEncode tRedEncode;
public: 
	TRedDescript()
	{
		Clear();
	}

	void Clear()
	{
		tRedEncode.Clear();
		TAudioDescript::Clear();
	}
};



/// 音频能力表
struct TAudioCapbilityList
{
	u8 m_byNum;								///< Number of capabilities in m_atItem
	TAudioDescript m_atItem[emModuleAEnd];
	TRedDescript m_tRed;

	HMDLAPPCHANNEL m_hAppChan;
	PFC_IPADDR m_tRtpAddr;
	PFC_IPADDR m_tRtcpAddr;
	BOOL32  m_bActive;

	/// extmap扩展（audio-level）
	EmModuleDirection m_emAudLvlDirect;
	u8 m_byAudLvlId;
	BOOL32 m_bAudLvlVadOn;
#ifdef _KDV_SRTP_SUPPORT_
	TMdlSrtpMediaSetting m_tSrtpSetting;
#endif
	BOOL32 m_bRtcpMux;    ///< is use rtcp_mux
public:
	TAudioCapbilityList()
	{
		Clear();
	}

	void Clear()
	{
		m_hAppChan	= NULL;
		m_byNum		= 0;
		
		for ( u8 i=0; i<emModuleAEnd; i++ )
		{
			m_atItem[i].Clear();
		}

		m_tRtpAddr.Clear();
		m_tRtcpAddr.Clear();
		m_bActive	= TRUE;
		m_emAudLvlDirect = emModule_Direction_Begin;
		m_byAudLvlId = 0;
		m_bAudLvlVadOn = TRUE;
#ifdef _KDV_SRTP_SUPPORT_
		m_tSrtpSetting.Clear();
#endif
		m_bRtcpMux = FALSE;
	}
};

typedef enum 
{
	emDualAttribueBegin = 0,
	emDualSendOnly = 1,
	emDualSendRecv = 2,
	emDualSendOnlyAndRecvOnly = 3,
}EmDualAttribue;

/// call capbility for sip
typedef struct tagMdlCallCap
{
	u16 m_wSndVidNum;
	u16 m_wRcvVidNum;
	u16 m_wSndAudNum;
	u16 m_wRcvAudNum;
	
	TVideoCapbilityList m_atSndVidCap[MAX_VIDEO_NUM];
	TVideoCapbilityList m_atRcvVidCap[MAX_VIDEO_NUM];
	TAudioCapbilityList m_atSndAudCap[MAX_AUDIO_NUM];
	TAudioCapbilityList m_atRcvAudCap[MAX_AUDIO_NUM];
	
	void Clear()
	{	
		u8 i = 0;
		m_wSndAudNum = 0;
		m_wRcvAudNum = 0;
		m_wSndVidNum = 0;
		m_wRcvVidNum = 0;
		for (i = 0; i < MAX_VIDEO_NUM; i++)
		{
			m_atSndVidCap[i].Clear();
			m_atRcvVidCap[i].Clear();
		}
		for (i = 0; i < MAX_AUDIO_NUM; i++)
		{
			m_atSndAudCap[i].Clear();
			m_atRcvAudCap[i].Clear();
		}
	}

	tagMdlCallCap()
	{
		Clear();
	}
	
}TMdlCallCap;

/// dual capbility list
typedef struct tagDualCapList
{
	EmDualAttribue m_emDualAttribue;
	TMdlCallCap m_tCallCap;
	
	void Clear()
	{
		m_emDualAttribue = emDualSendOnlyAndRecvOnly;
		m_tCallCap.Clear();
	}
	tagDualCapList()
	{
		Clear();
	}
}TDualCapList;


typedef enum 
{
	emFECCCapReceive	=1,
	emFECCCapTransmit	=2,
	emFECCCapReceiveAndTransmit=3
} cmFECCCapDirection;

typedef enum 
{
	emMMcuCapReceive	=1,
	emMMcuCapTransmit	=2,
	emMMcuCapReceiveAndTransmit=3
} cmMMcuCapDirection;

/// fecc capbility
typedef struct tagFeccCapbility
{
	PFC_IPADDR              m_tSendAddress;	///< FECC发送地址
	PFC_IPADDR              m_tRecvAddress;	///< FECC接收地址
	cmFECCCapDirection		m_byDirection;
	u16						m_wSampleRate;
	u8						m_byDynamicPayload;
#ifdef _KDV_SRTP_SUPPORT_
	TMdlSrtpMediaSetting    m_tSrtpSetting; 
#endif

	void Clear()
	{
		m_tSendAddress.Clear();
		m_tRecvAddress.Clear();
		m_wSampleRate		= 0;
		m_byDynamicPayload	= MEDIA_TYPE_H224	;
		m_byDirection		= emFECCCapReceiveAndTransmit;

#ifdef _KDV_SRTP_SUPPORT_
		m_tSrtpSetting.Clear();
#endif
	}
	
	tagFeccCapbility()
	{
		Clear();
	}
	
}TFeccCapbility;

/// mcu-mcu capbility
typedef struct tagMMcuCapbility
{
	PFC_IPADDR m_tListenAddress;	///< MMcu监听地址
	cmMMcuCapDirection		m_byDirection;
	u8						m_byDynamicPayload;

	void Clear()
	{
		m_tListenAddress.Clear();
		m_byDynamicPayload	=  MEDIA_TYPE_MMCU;
		m_byDirection		= emMMcuCapReceiveAndTransmit;
		m_tListenAddress.m_tAddr.m_tIPv4.m_dwIP = 0;
		m_tListenAddress.m_wPort = 3337;
	}

	tagMMcuCapbility()
	{
		Clear();
	}

}TMMcuCapbility;

/// call capbility for h323
typedef struct tagCallCapbility
{
	u16 m_wAudioNum;
	TAudioCapbilityList m_atAudioCapList[MAX_AUDIO_NUM];     ///< 每一个通道
	u16 m_wVideoNum;
	TVideoCapbilityList m_atVideoCapList[MAX_VIDEO_NUM];

	//////////////////////////////////////////////////////////////////////////
	//Jacky Invite with BFCP
	///	The following variants will be used only for H.323 call
	u16 m_wDualVideoNum;
	TVideoCapbilityList m_tDualCapList;						///< 视频双流能力，默认为1路
	//////////////////////////////////////////////////////////////////////////

	tagCallCapbility()
	{
		Clear();
	}

	void Clear()
	{
		u8 i			= 0;
		m_wAudioNum		= 0;
		m_wVideoNum		= 0;
		m_wDualVideoNum = 1;

		for ( i=0; i<MAX_AUDIO_NUM; i++)
		{
			m_atAudioCapList[i].Clear();
		}

		for ( i=0; i<MAX_VIDEO_NUM; i++)
		{
			m_atVideoCapList[i].Clear();
		}

		m_tDualCapList.Clear();
	}

}TCallCapbility;

/// defined in rfc4145
typedef enum 
{
	emSetupBegin = 0,
	emActive   = 1,	///< The endpoint will initiate an outgoing connection.
	emPassive  = 2,	///< The endpoint will accept an incoming connection.
	emActpass  = 3,	///< The endpoint is willing to accept an incoming connection or to initiate an outgoing connection.
	emHoldconn = 4,	///< The endpoint does not want the connection to be established for the time being.
}EmSetupAttr;

/// defined in rfc4145
typedef enum 
{
	emConnectionBegin = 0,
	emNew = 1,
	emExisting = 2,
}EmConnectionAttr;

/// defined in rfc4583
typedef enum 
{
	emFloorcontrolBegin = 0,
	emClientOnly = 1,	///< The answerer will act as a floor control client. Consequently, the offerer will act as a floor control server.
	emServerOnly = 2,	///< The answerer will act as a floor control server. Consequently, the offerer will act as a floor control client.
	emClientServer = 3,	///< The answerer will act both as a floor control client and as a floor control server. Consequently, the offerer will also act \
						///< both as a floor control client and as a floor control server.
}EmFloorcontrolAttr;

typedef enum
{
	emBfcpSdpBegin = 0,
	emTcpBfcp,
	emTcpTlsBfcp,
	emUdpBfcp,
	emUdpTlsBfcp,
}EmBfcpSdpAttr;

typedef struct tagBfcpFloor
{
	u16 m_wFloorId;
	s32 m_nLabelNum;
	s32 m_anLabelList[MAX_MEDIA_NUM_PER_FLOOR];

	void Clear()
	{
		m_wFloorId = 0;
		m_nLabelNum = 0;
		for (s32 i = 0; i < MAX_MEDIA_NUM_PER_FLOOR; i++)
		{
			m_anLabelList[i] = 0;
		}
	}
	tagBfcpFloor()
	{
		Clear();
	}
}TBfcpFloor;

typedef struct tagBfcpCapSet
{	
	u16 m_wPort;	///< BFCP接收端端口
	
	EmFloorcontrolAttr m_emFloorcontrolAttr;	///< BFCP实体（Floorcontrol属性）
	EmSetupAttr        m_emSetupAttr;	///< BFCP数据流动方向（Setup属性）
	EmConnectionAttr   m_emConnectionAttr;	///< 连接属性（默认new）
	EmBfcpSdpAttr      m_emBfcpSdpAttr;	///< TCPBFCP、TCPTLSBFCP、UDPBFCP、UDPTLSBFCP

	u32 m_dwConfId;	///< 会议ID
	u16 m_wUserId;	///< 用户ID
	s32 m_nFloorNum;	///< Floor Number
	TBfcpFloor m_atBfcpFloor[MAX_FLOOR_NUM];	///< Floor

	EmModuleTlsType m_emTlsType; ///< tls type
	void Clear()
	{
		m_wPort = 0;

		m_emFloorcontrolAttr = emFloorcontrolBegin;
		m_emSetupAttr = emSetupBegin;
		m_emConnectionAttr = emConnectionBegin;
		m_emBfcpSdpAttr = emUdpBfcp;

		m_dwConfId = 0;
		m_wUserId = 0;
		m_nFloorNum = 0;

		for (s32 i = 0; i < MAX_FLOOR_NUM; i++)
		{
			m_atBfcpFloor[i].Clear();
		}
		m_emTlsType = emModuleTlsNone;
	}
	tagBfcpCapSet()
	{
		Clear();
	}
}TBfcpCapSet;


/// H323 Annex Q
/*   
 *   h.281 encoded in host bit order:
 *   +-------+---------+--------+---------+--------+---------+--------+---------+
 *   +   P   | R=1/L=0 |    T   | U=1/D=0 |    Z   | I=1/O=0 |    F   | I=1/O=0 |
 *   +-------+---------+--------+---------+--------+---------+--------+---------+
 */
/// fecc action
enum emModulefeccAction
{
	emModuleactionInvalid				= 0,  
	emModuleactionStart					= 0x01,  ///< 开始
	emModuleactionContinue				= 0x02,  ///< 继续
	emModuleactionStop					= 0x03,  ///< 停止
	emModuleactionSelectVideoSource		= 0x04,  ///< 选择视频源
	emModuleactionVideoSourceSwitched	= 0x05,  ///< 切换视频源
	emModuleactionStoreAsPreset			= 0x06,  ///< 存储预置位
	emModuleactionActivatePreset		= 0x07,  ///< 恢复到预置位
	emModuleactionAutoFocus				= 0x11,  ///< 自动调焦
};

/// PTFZ codes, parameters for action Start, continue and stop.
enum emModulefeccPTFZRequest
{
	emModulerequestInvalid				= 0,
	emModulerequestPanLeft				= 0x80,	///< 向左移动
	emModulerequestPanRight				= 0xc0,	///< 向右移动
	emModulerequestTiltUp				= 0x30,	///< 向上移动
	emModulerequestTiltDown				= 0x20,	///< 向下移动
	emModulerequestFocusIn				= 0x03,	///< 近焦
	emModulerequestFocusOut				= 0x02,	///< 远焦
	
	emModulerequestZoomIn				= 0x0c,	///< 视野变小
	emModulerequestZoomOut				= 0x08,	///< 视野变大

	emModulerequestBrightnessUp			= 0x01,	///< 亮度加(nonstandard)
	emModulerequestBrightnessDown		= 0x04  ///< 亮度减(nonstandard)
};

/// CME message type
enum emModuleCMEMsgType
{
	emModuleCMEInvalid,				///< 无效									
	emModuleCMEClientListInfo,		///< 客户列表消息通知
	emModuleCMEClientListCommond,	///< 请求客户列表	
	emModuleCMEExtraCapInfo,		///< 额外能力信息通知			
	emModuleCMEExtraCapCommond,		///< 请求额外能力			
};

/// H323 Annex Q
///< CME消息以及控制消息复用在一个结构体里
///< if m_bIsCMEMsg is true,only use m_byCMEMsgType, otherwise use others
typedef struct tagMdlFeccStruct
{
	BOOL32 m_bIsCMEMsg;		    
	
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
	tagMdlFeccStruct()
	{
		m_bIsCMEMsg		= FALSE;
		m_byCMEMsgType	= emModuleCMEInvalid;
		m_byAction		= emModuleactionInvalid;
		arguments.m_byRequest = emModulerequestInvalid;	
		m_byTimeout		= 0;
	}
	
}TMdlFeccStruct, *PTMdlFeccStruct;

/// 端口复用,需要设置streamId。
#define FECC_ENDPOINTID_LEN 32
typedef struct tagMdlFeccStreamIdInfo
{
	s8  aszEndPointId[FECC_ENDPOINTID_LEN];	///< 终端的id, 当前仅支持e164号
	u32 IdLen;				///< 终端id的长度
	u32 StreamId;			///< 流id
	BOOL32 bSendChan;		///< 是否是远遥发送通道

public:
	tagMdlFeccStreamIdInfo()
	{
		memset(aszEndPointId, 0, FECC_ENDPOINTID_LEN);
	}
}TMdlFeccStreamIdInfo;

/// 视频通道参数
typedef struct tagTModuleVideoChanParam
{
	EmModuleVideoFormat     m_emVideoFormat;
	EmModuleVideoResolution m_emVideoResolution;
	u16                m_wChanMaxBitrate;      ///<  单位 Kbps
	u8                 m_byPayload;			   ///< 动态载荷
	TModuleEncryptKey  m_tKey;				   ///< 若tKey.byLen=0 表示不加密
	u8                 m_byFrameRate;          ///< 帧率
public:
	tagTModuleVideoChanParam()
	{ 
		Clear();
	}	
	void Clear()
	{
		m_emVideoFormat		= emModuleVEnd;
		m_emVideoResolution = emModuleVResEnd;
		m_wChanMaxBitrate   = 0;
		m_byPayload         = MODULE_VIDEO_DEFAULT_PAYLOADTYPE;
		memset( &m_tKey ,0 ,sizeof(m_tKey) );
		m_byFrameRate		= MODULE_VIDEO_DEFAULT_FRAMERATE;
	}
}TModuleVideoChanParam, *PTModuleVideoChanParam;

/// 视频通道参数 
typedef struct tagTModuleAudioChanParam
{
	EmModuleAudioFormat   m_emAudioFormat;
	u8					  m_byPayload;     ///< 动态载荷
	TModuleEncryptKey     m_tKey;          ///< 若tKey.byLen=0 表示不加密
public:
	tagTModuleAudioChanParam()
	{
		Clear();
	}

	void Clear()
	{
		m_emAudioFormat = emModuleAEnd;
		m_byPayload     = 0;
		memset( &m_tKey ,0 ,sizeof(m_tKey));
	}
}TModuleAudioChanParam;

/// video channel pararm
typedef struct tagModuleVideoChannelParam
{
	TModuleVideoChanParam m_tParam;
	PFC_IPADDR m_tRtpAddr;
	PFC_IPADDR m_tRtcpAddr;

}TModuleVideoChannelParam;

/// audio channel pararm
typedef struct tagModuleAudioChannelParam
{
	TModuleVideoChannelParam m_tParam;
	PFC_IPADDR m_tRtpAddr;
	PFC_IPADDR m_tRtcpAddr;
	
}TModuleAudioChannelParam;

/// channel type,send or recv
enum emChanType
{
	emModuleChanTypeBegin,
	emModuleSndAud,
	emModuleSndVid,
	emModuleRcvAud,  
	emModuleRcvVid,
};

/// channel type,audio or video or data
enum emAVType
{
	emModuleTypeBegin,
	emModuleAudioType,
	emModuleVideoType,

	emModuleAudioSecondType,
	emModuleVideoSecondType,

	/// data type
	emModuleH224Type,
	emModuleT120Type,
	emModuleMMcuType
};
//add by yj for conf MSG [20130726]
/// 用于调整帧率时填写通道类型,共计10个通道
enum emModuleChannelType
{
	emModuleChanSendAudio,
	emModuleChanSendPrimoVideo,
	emModuleChanSendSecondVideo,
	emModuleChanSendFecc,
	emModuleChanSendT120,
	
	/// 接收通道
	emModuleChanRecvAudio,
	emModuleChanRecvPrimoVideo,
	emModuleChanRecvSecondVideo,
	emModuleChanRecvFecc,
	emModuleChanRecvT120,
	
	emModuleChanTypeEnd	
};

/// 视频类型
enum emModVideoType
{
	emModulePriomVideo = 0 ,///< 主视频
	emModuleSecondVideo = 1///< 第二路视频
};

/// 终端型号
enum EmModuleMtModel
{
	emModuleUnknownMtModel = 0,
	emModulePCMT  = 1 ,///< 桌面终端
	emModule8010      ,
	emModule8010A     ,
	emModule8010Aplus ,///< 8010A+
	emModule8010C     ,
	emModule8010C1    ,///< 8010C1
	emModuleIMT       ,
	emModule8220A     ,
	emModule8220B     ,
	emModule8220C     ,
	emModule8620A     ,
	emModuleTS6610E   ,
	emModuleTS6210    ,
	emModule8010A_2   ,
	emModule8010A_4   ,
	emModule8010A_8   ,
	emModule7210      ,
	emModule7610      ,
	emModuleTS5610    ,
	emModuleTS6610    ,
	emModule7810      ,
	emModule7910      ,
	emModule7620_A    ,
	emModule7620_B    ,
	emModule7820_A	,
	emModule7820_B	,
	emModule7920_A	,
	emModule7920_B	,
	emModuleKDV1000   ,
	emModule7921_L    ,
	emModule7921_H    ,
	emModuleH600_LB    ,
	emModuleH600_B    ,
	emModuleH600_C    ,
	emModuleH700_A    ,
	emModuleH700_B    ,
	emModuleH700_C    ,
	emModuleH900_A    ,
	emModuleH900_B    ,
	emModuleH900_C    ,
	emModuleH600_LC   ,
	emModuleH800_A    ,
	emModuleH800_B    ,
	emModuleH800_C    ,
};

/// 文件系统类型
enum EmModuleFileSys
{
	emModuleRAWFS = 1,///< raw file system [ramdisk + rawblock + tffs]
	emModuleTFFS  ///< tffs
};

/// 操作
enum EmModuleAction
{
    emModuleStart,
	emModuleStop,
	emModulePause,
	emModuleResume,
};

/// 位置
enum EmModuleSite
{
    emModuleLocal = 0,  ///< 本地
	emModuleRemote    ///< 远端
};

/// 会议模式
enum EmModuleConfMode
{
	emModuleP2PConf = 0,///< 点对点会议
	emModuleMCCConf = 1 ///< 多点会议
};

/// 终端视频端口
enum EmModuleMtVideoPort
{
	emModuleMtVidPort1 = 0,  
	emModuleMtVidPort2    ,  
	emModuleMtVidPort3    ,  
	emModuleMtVidPort4    ,  
	emModuleMtVidPort5    ,  
	emModuleMtVidPort6    ,  
	emModuleMtVidPort7	  , 
	emModuleMtVidPort8    ,
	emModuleMtVidPort9    ,
	emModuleMtVidPort10   ,
	
	emModuleMtExternalVid,
	emModuleMtVidPortMaxCount = 40, ///< 最多支持视频源个数
	emModuleMtVidInvalid = 255 
};

/// 加密算法
enum EmModuleEncryptArithmetic
{
	emModuleEncryptNone = 0,
	emModuleDES         = 1,
	emModuleAES         = 2,
	emModuleEncryptAuto = 3,
	
	emModuleEncryptEnd		
};

enum EmModuleUIPosion
{
	emModuleMT = 0,
	emModuleMTC = 1
};

/// 视频编解码状态
typedef struct tagTModuleMtVideoCodecStatus
{
	BOOL32                m_bRuning;           ///< 是否在工作
	EmModuleVideoFormat       m_emFormat;          ///< 视频编码格式
	EmModuleVideoResolution   m_emRes;             ///< 视频编码格式
	u16                 m_wBitrate;          ///< 视频编码码率(单位:kbps)
	u16                 m_wAverageBitrate;   ///< 主视频编平均码码率(单位:kbps)
	BOOL32                m_bIsEncrypt;         ///< 主视频编码是否加密
	EmModuleEncryptArithmetic m_emArithmetic;	   ///< 主视编码使用的加密算法	
	
public:
	tagTModuleMtVideoCodecStatus()
	{ 
		memset ( this ,0 ,sizeof( struct tagTModuleMtVideoCodecStatus) );
	}
}TModuleMtVideoCodecStatus, *PTModuleMtVideoCodecStatus;

/// 终端状态
typedef struct tagTModuleTerStatus
{
	EmModuleMtModel  m_emMtModel;				    ///< 终端型号
	EmModuleFileSys  m_emFileSys;                 ///< 文件系统类型
	
	u8		m_byEncVol;					///< 当前编码音量(单位:等级)
	u8		m_byDecVol;					///< 当前解码音量(单位:等级)
	BOOL32	m_bIsMute;					///< 是否哑音	
	BOOL32	m_bIsQuiet;					///< 是否静音			
	BOOL32	m_bIsLoopBack;				///< 是否自环
	BOOL32    m_bIsInMixing;                ///< 是否参加混音
	BOOL32    m_bRegGkStat;			    	///< GK注册结果	1 成功 0 失败
	EmModuleAction   m_emPollStat;		///< 轮询状态		emStart ,emPause ,emStop /开始/暂停/停止
	EmModuleSite	 m_emCamCtrlSrc;		///< 当前控制摄像头源类型 emLocal, emRemote
	u8		m_byLocalCamCtrlNo;			    ///< 当前控制的本地摄像头号(1-6号摄像头)
	u8		m_byRemoteCamCtrlNo;			    ///< 当前控制的远端摄像头号(1-6号摄像头)
	u8      m_byE1UnitNum ;                   ///< 终端E1模块的的E1个数
	BOOL32	m_bFECCEnalbe;				///< 是否允许远遥
	BOOL32    m_bLocalIsVAG;                ///< 本地第二路码流输出到是否VGA
	BOOL32    m_bPVHasVideo;                ///< 第一路是否有视频源
	BOOL32    m_bSVHasVideo;                ///< 第二路是否有视频源
	/// 一下部分不建议使用
	BOOL32	m_bIsAudioPowerTest;			///< 是否在测试音频	
	BOOL32	m_bIsLocalImageTest;			///< 是否本地图像测试
	BOOL32	m_bIsRemoteImageTest;			///< 是否远端图像测试 
	/// 	///////会议状态///////
	BOOL32       m_bIsInConf;				///< 是否在会议中	
	EmModuleConfMode m_emConfMode;				///< 会议模式		1 两点 2 多点		
    BOOL32       m_bCallByGK;				///< 是否通过GK呼叫 TRUE GK路由 FALSE直接呼叫
	//	
	///	///////设备状态///////
	BOOL32	m_bMatrixStatus;				    ///< 外置矩阵状态		(TRUE ok FALSE err)
	u8		m_byCamNum;					    ///< 摄像头个数	(0~6)
	BOOL32	m_bCamStatus[MAX_MTCAMERA_NUM];					///< 摄像头状态 (TRUE ok FALSE err)
	EmModuleMtVideoPort m_emVideoSrc;					///< 当前本地视频源(0:S端子,1-6:C端子)
	
	BOOL32    m_bIsEncrypt;
	///	//编解码器状态
	EmModuleAudioFormat	    m_emADecFormat;	///< 音频解码格式
	EmModuleAudioFormat	    m_emAEncFormat;	///< 音频编码格式
	TModuleMtVideoCodecStatus  m_tPVEncStatus;   ///< 主视频编码器
	TModuleMtVideoCodecStatus  m_tSVEncStatus;   ///< 辅视频编码器
	TModuleMtVideoCodecStatus  m_tPVDecStatus;   ///< 主视频解码器
	TModuleMtVideoCodecStatus  m_tSVDecStatus;   ///< 辅视频解码器
	//	
	u16		m_wSysSleep;					///< 待机时间(0x0表示不待机)
	/// VOD states
	BOOL32	m_bIsInVOD;
	EmModuleUIPosion	m_emVodUser;
	//////配置状态///////
public:
	tagTModuleTerStatus(){ memset ( this, 0, sizeof( struct tagTModuleTerStatus) );}
}TModuleTerStatus, *PTModuleTerStatus;
//end [20130726]

enum emModuleChannelDirection
{
	emModuleChannelDirectionBegin,
	emModuleChannelSend,
	emModuleChannelRecv,
	emModuleChannelBidirectional,
};

enum EmChannelReason
{
	emModuleChannelReasonBegin,
	emModuleChannelDisconnectNormal,
	emModuleDualOffLine, 
	emModuleChannelDisconnectForce,        ///< 抢断双流（双流请求发送成功，但收到对端非200Ok的正常应答）
	emModuleDualNotSend,	///< 双流未经协议栈发送出去（当前状态不正确，导致协议栈未发送）
	emModuleDualAudioNotSupport,  ///< 发双流时，直接回调双流音频失败（只针对323），提供此理由让t300判断是双流音频的。[20141029]
};

/// channel type
typedef struct tagModuleChannelType
{
	emAVType m_emAVType;
	emModuleChannelDirection m_emDirection;
public:
	tagModuleChannelType()
	{
		Clear();
	}
	void Clear()
	{
		m_emAVType = emModuleTypeBegin;
		m_emDirection = emModuleChannelDirectionBegin;
	}
}TModuleChannelType;

/// capbility setting information
typedef struct tagTCapSetInfo
{
	u8   m_byDynamicPayload;
	EmModuleAudioFormat m_emAudioFormat;        ///< 音频能力
	u8                  m_byPackTime;           ///< 音频能力
	EmModuleAudioChnlCfg m_emAudioChnlCfg;      ///< 音频通道数
	EmModuleAudioSampleFreq m_emAudioSampleFreq;///< 音频采样率
	u8                      m_abySpecificConfig[2];
	u8                      m_abyMuxConfig[7];
	BOOL32                  m_bOldConfig;
	/// g7231用
	u8				m_byMaxFrameNum;		    ///< 音频单包最大的帧数
	BOOL32			m_bSilenceSuppression;	    ///< 音频是否静音抑制
	
	EmModuleVideoFormat m_emVideoFormat;        ///< 视频能力
	TVideoDescript      m_atItem;               ///< 视频能力
	//EmModuleProfileMask m_emProfile;
	u32 m_emProfile;
	TRedEncode tRedEncode;

public:
	tagTCapSetInfo()
	{
		Clear();
	}
	void Clear()
	{
		m_byDynamicPayload = 0;
		m_emAudioFormat = emModuleAEnd;
		m_byPackTime = 0;
		m_emAudioChnlCfg = emModuleChnlCust;
		m_emAudioSampleFreq = emModuleFs96000;
		m_byMaxFrameNum = 0;
		m_bSilenceSuppression = FALSE;
		m_emVideoFormat = emModuleVEnd;
		m_emProfile = 0;
		m_atItem.Clear();
		MEMSET_CAST(m_abySpecificConfig, 0, sizeof(m_abySpecificConfig));
		MEMSET_CAST(m_abyMuxConfig, 0, sizeof(m_abyMuxConfig));
		m_bOldConfig = FALSE;
		tRedEncode.Clear();
	}
}TCapSetInfo;

///  channel keeplive info
typedef struct tagTKeepAliveAddress
{
	PFC_IPADDR	m_tKeepAliveNet;
	u16			m_wKeepAlivePayload;
	u32			m_dwKeepAliveInterval;

	tagTKeepAliveAddress()
	{
		Clear();
	}

	void Clear()
	{
		m_tKeepAliveNet.Clear();
		m_wKeepAlivePayload = 0;
		m_dwKeepAliveInterval = 0;
	}

}TKeepAliveAddress,*PTKeepAliveAddress;

/// TCapSet channel information
typedef struct tagTCapSetChanInfo
{
	PFC_IPADDR		m_tLocalRtcpAddr;
	PFC_IPADDR      m_tLocalRtpAddr;
	PFC_IPADDR		m_tPeerRtcpAddr;
	PFC_IPADDR      m_tPeerRtpAddr;
	
	u8	m_byMediaCount;
	TCapSetInfo	m_atCapSetInfo[MAX_MEDIA_CAP_NUM];
#ifdef _KDV_SRTP_SUPPORT_
	TMdlSrtpMediaSetting m_tChanSrtpSetting;
#endif

	TMdlRtcpFeedbackParam   m_tRtcpFbParam;  ///< rtcp feedback mode
	BOOL32 m_bRtcpMux;    ///< is use rtcp_mux
	TKeepAliveAddress m_tKeepAliveAddr;
public:
    tagTCapSetChanInfo()
	{
		Clear();
	}
	void Clear()
	{
		m_tLocalRtcpAddr.Clear();
		m_tLocalRtpAddr.Clear();
		m_tPeerRtcpAddr.Clear();
		m_tPeerRtpAddr.Clear();
		m_tKeepAliveAddr.Clear();
		m_byMediaCount = 0;
		for ( s32 i =0; i < MAX_MEDIA_CAP_NUM; i++ )
		{
			m_atCapSetInfo[i].Clear();
		}
#ifdef _KDV_SRTP_SUPPORT_
		m_tChanSrtpSetting.Clear();
#endif
		m_tRtcpFbParam.Clear(); 
		m_bRtcpMux = FALSE;
	}
}TCapSetChanInfo;

/// channel connected information
typedef struct tagTChanConnectedInfo
{
	HMDLCHANNEL         m_hChan;
	HMDLAPPCHANNEL      m_hAppChan;
    TModuleChannelType  m_tChanType;
    TCapSetChanInfo     m_tCapsetInfo;
	TModuleEncryptKey	m_tStreamKey;
	
	tagTChanConnectedInfo()
	{
		Clear();
	}
	void Clear()
	{
		m_hChan = (HMDLCHANNEL)0;
		m_hAppChan = (HMDLAPPCHANNEL)0;
		m_tChanType.Clear();
		m_tCapsetInfo.Clear();
		m_tStreamKey.Clear();
	}
}TChanConnectedInfo;

/// channel disconnected information
typedef struct tagTChanDisConnectedInfo
{
	HMDLCHANNEL         m_hChan;
	HMDLAPPCHANNEL      m_hAppChan; 
	
	EmChannelReason     m_emReason;

    tagTChanDisConnectedInfo()
	{
		Clear();
	}
	void Clear()
	{
		m_hChan = (HMDLCHANNEL)0;
		m_hAppChan = (HMDLAPPCHANNEL)0;
		m_emReason = emModuleChannelReasonBegin;
	}
}TChanDisConnectedInfo;

/// TRegistReq : used to register request
typedef struct tagRegistReq
{
	///Support multiple aliases
	TCallAliasAddr m_atH323Alias[MAX_ALIAS_NUM];      ///< H323 Alias address;MAX_ALIAS_NUM-64
	TCallAliasAddr m_atE164[MAX_E164_NUM];            ///< E164 Alias address;MAX_E164_NUM-64
	
	s8 m_achEPID[MAX_LEN_EPID + 1];                   ///< EPID;MAX_LEN_EPID-64
	
	EmModuleConnection      m_emConnection;	          ///< Connection Type;0-initial,1-TCP,2-UDP,3-SCTP,4-TLS,5-TCP6,6-UDP6,7TLS6
	PFC_IPADDR m_tLocalAddress;                       ///< The address to be registered；
	PFC_IPADDR m_tGKAddress;                          ///< GK Address
	PFC_IPADDR m_tRegAddress;                         ///< sip regserver address
	s32	m_nTimeToLive;                                ///< the time to live;(s)

	s8	m_achProductId[MAX_LEN_PRODUCT_ID + 1];       ///< Product Id;MAX_LEN_PRODUCT_ID-128
	s8	m_achVersionId[MAX_LEN_VERSION_ID + 1];       ///< Version Id;MAX_LEN_VERSION_ID-128

	emModuleEndpointType m_emEndpointType;            ///< Endpoint Type;0-Begin,1-Mcu,2-MT,3-GK,4-Gateway,5-CNS,6-UMS,7-VRS

	s8	m_achUsername[MAX_LEN_CALL_ALIAS + 1];          ///< Username;MAX_LEN_CALL_ALIAS-64
	s8	m_achPassword[MAX_PASSWORD_LEN + 1];          ///< Password;MAX_PASSWORD_LEN-16
	s8	m_achDomainName[MAX_DOMAINNAME_LEN+1];	      ///< DomainName;MAX_DOMAINNAME_LEN-64

	BOOL32 m_bPortReused;	                          ///< Whether the port is reused;TRUE/FALSE

	EmModuleTlsType m_emTlsType;                       ///< TLS type
	s8              m_achDevId[MAX_DEVID_LEN];         ///< devid for qt tls,the new devid will cover the old one.  
	u8     m_byNonStdHdrNum;
	TSipNstHeader m_atNonStdHdr[MAX_SIP_NONSTD_HEADER_NUM];

	BOOL32  m_bTps;
public:
	tagRegistReq()
	{
		Clear();
	}
	void Clear()
	{
		memset( m_atE164,        0 , sizeof(m_atE164) );
		memset( m_atH323Alias,   0 , sizeof(m_atH323Alias) );
		memset( m_achEPID,       0, sizeof( m_achEPID) );
		memset( m_achProductId,  0, sizeof( m_achProductId) );
		memset( m_achVersionId,  0, sizeof( m_achVersionId) );
		memset( m_achUsername,   0, sizeof( m_achUsername) );
		memset( m_achPassword,   0, sizeof( m_achPassword) );
		memset( m_achDomainName, 0, sizeof( m_achDomainName) );
		memset( m_atNonStdHdr,   0, sizeof( m_atNonStdHdr) );
		memset( m_achDevId,      0, sizeof( m_achDevId) );
		m_byNonStdHdrNum = 0;
		m_tLocalAddress.Clear();
		m_tGKAddress.Clear();
		m_tRegAddress.Clear();
		m_nTimeToLive  = MODULE_REG_DEFAULT_TIMETOLIVE;
		m_emConnection = emModuleUdpConnection;
		m_bPortReused  = FALSE;
		m_emEndpointType = emModuleEndpointMT;
		m_emTlsType      = emModuleTlsNone;
		m_bTps           = FALSE;
	}
}TRegistReq;


/// 终端编号参数
typedef struct tagModuleTerminalLabel 
{
	u8 m_byMcuNo;
	u8 m_byTerNo;
	
	tagModuleTerminalLabel()
	{
        m_byMcuNo = 0xff;
		m_byTerNo = 0xff;		
	}

    ~tagModuleTerminalLabel()
    {
        m_byMcuNo = 0xff;
		m_byTerNo = 0xff;
    }
	
	void Clear()
	{
		m_byMcuNo = 0xff;
		m_byTerNo = 0xff;
	}

	BOOL32 isValid()
	{
		return ( m_byTerNo <= MAX_CONFMT_NUM && m_byMcuNo != 0xff );
	}

	BOOL32 operator == (const tagModuleTerminalLabel& tTerLabel)
	{
        return !memcmp(this, (void*)&tTerLabel, sizeof(tTerLabel));
	}

}TMDLTERLABEL,*PMDLTTERLABEL;


/// 终端信息(会控用)
typedef struct tagModuleTerminalInfo
{
	u8 m_byMcuNo;   
	u8 m_byTerNo;
	u8 m_byConfNo;   ///< 会议号码
	s8 m_achTerminalId[MAX_TERMINALID_LEN+1];    ///< TerminalID
	BOOL32 m_bIsChair;   ///< 是否是主席
	BOOL32 m_bIsFloor;   ///< 是否是发言人

	BOOL32 m_bLastPack;  ///<  是否是最后一包
	BOOL32 m_bOnline;    ///<  是否在线

	TMDLTERLABEL m_tTerYouAreView;    ///< 正在选看谁
	u32 m_adwSeenByOtherListMask[SEEN_BY_OTHERLIST_MASK_NUM];   ///< 6个int表示192个位，来表示192个终端，谁选看了这个终端

	tagModuleTerminalInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_byConfNo = 0xff;
		m_byMcuNo = 0xff;
		m_byTerNo = 0xff;
		memset( m_achTerminalId, 0, sizeof(m_achTerminalId) );
		m_bIsChair = FALSE;
		m_bIsFloor = FALSE;

		m_bLastPack = FALSE;
		m_bOnline   = FALSE;
		m_tTerYouAreView.Clear();
		
		memset( m_adwSeenByOtherListMask, 0, sizeof(m_adwSeenByOtherListMask) );
	}

	void AddSeenByOtherList( u8 terNo )
	{
		if( terNo >= 192 )
			return;

		u8 i = terNo/(sizeof(u32)*8);
		u8 j = terNo%(sizeof(u32)*8);
		
		u32 mask = 0x00000001;
		mask <<= j;
		
		m_adwSeenByOtherListMask[i] |= mask;
	}

	void DelSeenByOtherList( u8 terNo )
	{
		if( terNo >= 192 )
			return;

		u8 i = terNo/(sizeof(u32)*8);
		u8 j = terNo%(sizeof(u32)*8);

		u32 mask = 0x00000001;
		mask <<= j;

		m_adwSeenByOtherListMask[i] &= ~mask;
	}

	BOOL32 IsSeenByOtherListEmpty( )
	{
		u32 temp[SEEN_BY_OTHERLIST_MASK_NUM];
		memset( temp, 0, sizeof(temp) );
		return !memcmp( temp, m_adwSeenByOtherListMask, sizeof(temp) );
	}

	void ResetSeenByOtherList( )
	{
		memset( m_adwSeenByOtherListMask, 0, sizeof(m_adwSeenByOtherListMask) );
	}

	u8 GetSeenByOtherList( u8* list )  ///< 这个数组最大可能192个u8
	{ 
		u8 count = 0;

		for( u8 i = 0; i < SEEN_BY_OTHERLIST_MASK_NUM; i++ )
		{
			if( m_adwSeenByOtherListMask[i] != 0 )
			{
				for( u8 j = 0; j < sizeof(u32)*8; j++ )
				{
					u32 mask = 0x00000001;
					mask <<= j;

					if( m_adwSeenByOtherListMask[i] & mask )
					{
						list[count++] = (u8)(sizeof(u32)*8*i + j);
					}
				}
			}
		}
		return count;
	}

}TMDLTERMINALINFO,*PMDLTERMINALINFO;


enum EmModuleOperateType
{
	emModuleOperateType_NULL,       ///< 空操作
	emModuleOperateType_Add,        ///< 增加操作
	emModuleOperateType_Del,        ///< 删除操作
	emModuleOperateType_Update      ///< 修改操作
};

/// terminal information list
typedef struct tagModuleTerInfoList
{
	EmModuleOperateType	    m_emOperateType;
	u8 m_byNum;
	TMDLTERMINALINFO m_atTerInfoList[MAX_CONFMT_NUM];
	
	tagModuleTerInfoList()
	{
		Clear();
	}

	void Clear()
	{
		m_emOperateType = emModuleOperateType_Add;
		m_byNum = 0;
		memset( m_atTerInfoList, 0, sizeof(m_atTerInfoList) );
		for( u8 index = 0; index < MAX_CONFMT_NUM; index++ )
		{
			m_atTerInfoList[index].Clear();
		}
	}
}TMDLTERINFOLIST,*PTMDLTERINFOLIST;


/// terminal label list
typedef struct tagModuleTerLabelList
{
	u8 m_byNum;
	TMDLTERLABEL m_atTerLabelList[MAX_CONFMT_NUM];
	
	tagModuleTerLabelList()
	{
		Clear();
	}
	
	void Clear()
	{
		m_byNum = 0;
		//memset( m_atTerLabelList, 0, sizeof(m_atTerLabelList) );
		for( u8 index = 0; index < MAX_CONFMT_NUM; index++ )
		{
			m_atTerLabelList[index].Clear();
		}
	}
}TMDLTERLABELLIST,*PTMDLTERLABELLIST;

/// conference list
typedef struct tagModuleConfList
{
	u8 m_byConfNo;  ///< 会议号
	u8 m_byTerCount;
	HMDLCALL m_ahCall[MAX_CONFMT_NUM];

	tagModuleConfList()
	{
		Clear();
	}

	void Clear()
	{
		m_byConfNo = 0xff;
		m_byTerCount = 0;
		memset( m_ahCall, 0, sizeof(m_ahCall) );
	}
}TMDLCONFLIST, *PTMDLCONFLIST;


/// Module Alias information
typedef struct tagModuleAlias
{
	emModuleAliasType m_emAliasType;
	u8 m_abyCallAliasAddr[MAX_LEN_CALL_ALIAS + 1];

	tagModuleAlias()
	{
		Clear();
	}
	void Clear()
	{
		m_emAliasType = emModuleType_aliastype;
		memset( m_abyCallAliasAddr, 0, sizeof(m_abyCallAliasAddr) );
	}
}TModuleAlias;

typedef struct tagModuleTerminal
{
	u32 m_dwIp;
	TModuleAlias m_atAlias[2];
	emModuleEndpointType m_emTerminalType;

	tagModuleTerminal()
	{
		Clear();
	}
	
	void Clear()
	{
		memset( m_atAlias, 0, sizeof(m_atAlias) );
		m_emTerminalType = emModuletypeBegin;
		m_dwIp = 0;
	}
}TModuleTerminal;

/// mt online list
typedef struct tagModuleMtOnlineList
{
	u16 m_wListNum;
	TModuleTerminal m_atTerminal[MAX_ONLINE_LIST_NUM];
	BOOL32 m_bIsEnd;

	tagModuleMtOnlineList()
	{
		Clear();
	}

	void Clear()
	{
		m_wListNum = 0;
		memset( m_atTerminal, 0, sizeof(m_atTerminal) );
		m_bIsEnd = FALSE;
	}
}TModuleMtOnlineList;

/// mcu online list
typedef struct tagModuleMcuOnlineList
{
	u16 m_wAliasNum;
	TModuleAlias m_atAlias[MAX_ALIAS_NUM];
	u32 m_dwIp;
	BOOL32 m_bIsEnd;

	tagModuleMcuOnlineList()
	{
		Clear();
	}
	
	void Clear()
	{
		m_wAliasNum = 0;
		memset( m_atAlias, 0, sizeof(m_atAlias) );
		m_bIsEnd = FALSE;
		m_dwIp = 0;
	}
}TModuleMcuOnlineList;



/// 注册结果
enum EmRegResult
{
	emModuleRegResultBegin = 0,
	emModuleRegResultReg,
	emModuleRegResultUnReg,
};

/// register failed reason
enum EmPARegFailedReason
{
	emPALocalNormalUnreg = 0,
	emPAInvalidUserNameAndPassword,
	emPARegistrarUnReachable,
	emPAInvalidAlias,
	emPAUnknownReason,
	emPARegisterFailed,
	emPARegisterNameDup,
	emPAUnRegistSuccess,
	emPALoadTlsCertFailed,
};

enum emModuleRasReason
{
	emModuleRasGKUnReachable,
	emModuleRasInvalidAlias,
	emModuleRasInvalidCallSignalAddress,
	emModuleRasInvalidTerminalType,
	emModuleRasFullRegistrationRequired,
	emModuleRasInvalidTerminalAliases,
	emModuleRasDuplicateAlias,
	emModuleRasUnknownReason
};

enum EmModuleGetGKInfoType
{
	emModuleGetGKInfoType_MT = 0,
	emModuleGetGKInfoType_MCU,
	emModuleGetGKInfoType_ALL
};

/// 打印的模块
enum emModuleType 
{
	emModuleNon = 0,
	emModuleService,
	emModuleStackin,
	emModuleStackout,
	emModuleCapSet,
	emModule,
	emModuleAll,
	emModuleAllExceptCapSet,
};

enum emCallBy
{
	emModuleCallByNum = 0,
	emModuleCallByName,
};

/// 日志级别定义
#define LOG_OFF			        (s32)0		///< 关闭
#define LOG_EXP			        (s32)1		///< 异常
#define LOG_IMT			        (s32)2		///< 重要日志
#define LOG_DEBUG		        (s32)3		///< 一级调试信息
#define LOG_CONF                (s32)4      ///< 会议相关信息（会控、关键帧等）
#define LOG_ALL                 (s32)5      ///< 所有调试信息 

/// int类型ip转换成字符串
#define IP2CHAR(ip)  ((u8 *)&(ip))[0], \
				     ((u8 *)&(ip))[1], \
					 ((u8 *)&(ip))[2], \
					 ((u8 *)&(ip))[3]


#endif



