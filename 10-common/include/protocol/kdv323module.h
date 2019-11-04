/**
*   COPYRIGHT NOTICE
*   Copyright (C) 2018, KeDaCom
*   All right reserved
*   
*   @file        kdv323module.h
*   @author      Sai
*   @version     V5.0_64bit
*   @date        2018-03-05
*   @brief       Provide the API function and the callback function prototype for the upper application 
*   @details     
*/

#ifndef H323MODULE_H
#define H323MODULE_H

#include "kdvtype.h"
#include "kdv323common.h"
#include "modulecallstruct.h"
#include "cmH245GeneralDefs.h"

extern BOOL32 g_bIsStackNull; 

/**Callback function for new call incommong*/
typedef BOOL32 (PROTO_CALLBACK* H323CBNewCallIncoming)	(HMDLCALL hCall, TModuleCallInfo* pcCallInfo);
/**Callback function for call disconnected*/
typedef BOOL32 (PROTO_CALLBACK* H323CBCallDisconnected)	(HMDLCALL hCall, HMDLAPPCALL hAppCall, EmModuleCallDisconnectReason emReason);
/**Callback function for call connected*/
typedef BOOL32 (PROTO_CALLBACK* H323CBCallConnected)	(HMDLCALL hCall, HMDLAPPCALL hAppCall, TModuleCallInfo* pcCallInfo);
/**Peer recv capbility for interworking [20140217]*/
typedef BOOL32 (PROTO_CALLBACK* H323CBPeerRecvCapbility)(HMDLCALL hCall, HMDLAPPCALL hAppCall, TCallCapbility* ptPeerRecvCapbility);
//added end

/**Callback function*/
typedef struct tagH323CallCBFunction
{
	H323CBNewCallIncoming m_cbNewCallIncoming;
	H323CBCallDisconnected m_cbCallDisconnected;
	H323CBCallConnected m_cbCallConnected;
	H323CBPeerRecvCapbility m_cbPeerRecvCapbility;/**<for interworking [20170217]*/

	tagH323CallCBFunction()
	{
		m_cbNewCallIncoming = NULL;
		m_cbCallConnected = NULL;
		m_cbCallConnected = NULL;
		m_cbPeerRecvCapbility = NULL;
	}
}TH323CallCBFunction;

/**Channel Connected Callback Function*/
typedef BOOL32 (PROTO_CALLBACK* H323CBChannelConnected)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TChanConnectedInfo* atChanConnectInfo, u8 bySize );
/**Channel Disconnected Callback Function*/
typedef BOOL32 (PROTO_CALLBACK* H323CBChannelDisconnected)( HMDLCALL hCall , HMDLAPPCALL hAppCall , HMDLAPPCHANNEL hAppChan , HMDLCHANNEL hChan , u8 byReason );
/**Channel Flow Ctrl Callback Function*/
typedef BOOL32 (PROTO_CALLBACK* H323CBChannelFlowCtrl)( HMDLCALL hCall , HMDLAPPCALL hAppCall , HMDLAPPCHANNEL hAppChan , HMDLCHANNEL hChan , u16 wBitrate );
/**Channel Fast Update Callback Function*/
typedef BOOL32 (PROTO_CALLBACK* H323CBChannelFastUpdate)( HMDLCALL hCall , HMDLAPPCALL hAppCall , HMDLAPPCHANNEL hAppChan , HMDLCHANNEL hChan );
/**Dual Stream Incoming Callback Function*/
typedef BOOL32 (PROTO_CALLBACK* H323CBDualStreamIncoming)( HMDLCALL hCall, HMDLAPPCALL hAppCall, HMDLAPPCHANNEL hAppChan, HMDLCHANNEL hChan, TCallCapbility* ptDualCap );
/**Dual Stream Connected Callback Function*/
typedef BOOL32 (PROTO_CALLBACK* H323CBDualStreamConnected)( HMDLCALL hCall, HMDLAPPCALL hAppCall, HMDLAPPCHANNEL hAppChan, HMDLCHANNEL hChan, TChanConnectedInfo* ptChanInfo );
/**Dual Stream Reject Callback Function*/
typedef BOOL32 (PROTO_CALLBACK* H323CBDualStreamReject)( HMDLCALL hCall, HMDLAPPCALL hAppCall, HMDLAPPCHANNEL hAppChan, HMDLCHANNEL hChan );
/**Dual Stream Stop Callback Function*/
typedef BOOL32 (PROTO_CALLBACK* H323CBDualStreamStop)( HMDLCALL hCall, HMDLAPPCALL hAppCall, HMDLAPPCHANNEL hAppChan, HMDLCHANNEL hChan );
/**Chan Disconnected reopen for interworking Callback Function*/
typedef BOOL32 (PROTO_CALLBACK* H323CBChanDisconnectedEx)( HMDLCALL hCall , HMDLAPPCALL hAppCall , HMDLAPPCHANNEL hAppChan , HMDLCHANNEL hChan , TChanConnectedInfo* ptChanDisconnectInfo);
//added end 
/**Fecc Channel Connected Callback Function*/
typedef BOOL32 (PROTO_CALLBACK* H323CBFeccChannelConnected)(HMDLCALL hCall, HMDLAPPCALL hAppCall, TFeccCapbility *ptFeccCap);
/**MMcu Channel Connected Callback Function*/
typedef BOOL32 (PROTO_CALLBACK* H323CBMMcuChannelConnected)(HMDLCALL hCall, HMDLAPPCALL hAppCall, TChanConnectedInfo *ptChanInfo);
/**Fecc Message Callback Function*/
typedef BOOL32 (PROTO_CALLBACK* H323CBFeccMsg)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMdlFeccStruct *ptFeccStruct, TMDLTERLABEL *ptSrcLabel, TMDLTERLABEL *ptDstLabel );
/**MMcu Message Callback Function*/
typedef BOOL32 (PROTO_CALLBACK* H323CBMMcuMsg)( HMDLCALL hCall, HMDLAPPCALL hAppCall, HMDLAPPCHANNEL hAppChan, HMDLCHANNEL hChan, u16 wEvent, u8* pBuf, u16 wLen );

/**Channel Callback function*/
typedef struct tagH323ChannelCBFunction
{
	H323CBChannelConnected m_cbChannelConnected;
	H323CBChannelDisconnected m_cbChannelDisconnected;
	H323CBChannelFlowCtrl m_cbChannelFlowCtrl;
	H323CBChannelFastUpdate m_cbChannelFastUpdate;
	H323CBDualStreamIncoming m_cbDualStreamIncoming;
	H323CBDualStreamConnected m_cbDualStreamConnected;
	H323CBDualStreamReject m_cbDualStreamReject;
	H323CBDualStreamStop m_cbDualStreamStop;

	H323CBChanDisconnectedEx m_cbChanDisconnectedEx; /**<for interworking's reopen [20140217] */
	H323CBFeccChannelConnected m_cbFeccChannelConnected;
	H323CBFeccMsg m_cbFeccMsg;
	H323CBMMcuChannelConnected m_cbMMcuChannelConnected;
	H323CBMMcuMsg m_cbMMcuMsg;

	tagH323ChannelCBFunction()
	{
		memset( this , 0 , sizeof(tagH323ChannelCBFunction) );
	}
}TH323ChannelCBFunction;


typedef BOOL32 (PROTO_CALLBACK* CBRegResult)( HMDLREG hReg , HMDLAPPREG hAppReg , u8* pbuf , u16 wLen );
typedef BOOL32 (PROTO_CALLBACK* CBOnlineList)( HMDLREG hReg , HMDLAPPREG hAppReg , u32 dwAppId, u8* pbuf , u16 wLen );
typedef BOOL32 (PROTO_CALLBACK* H323CBConfEvent)( HMDLCALL hCall, HMDLAPPCALL hAppCall, u16 wEvent, u8* pBuf, u16 wLen );

//conf
// typedef BOOL (H323CALLBACK* H323CBMultipleConf)( HMDLCALL hCall, HMDLAPPCALL hAppCall ); //通知开始多点会议
// typedef BOOL (H323CALLBACK* H323CBConfList)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMDLTERINFOLIST tTerInfoList );  //回调与会列表
// typedef BOOL (H323CALLBACK* H323CBTerLabel)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMDLTERLABEL tTerLabel );   //回调MC分配的TerLabel
// typedef BOOL (H323CALLBACK* H323CBConfYouAreSee)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMDLTERLABEL tTerLabel); //回调当前发言人(YouAreSeeing)
// typedef BOOL (H323CALLBACK* H323CBSeeByAll )( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMDLTERLABEL tTerLabel );  //回调被看指示
// typedef BOOL (H323CALLBACK* H323CBConfTerJoin)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMDLTERLABEL tTerLabel ); //回调加入会议的终端
// typedef BOOL (H323CALLBACK* H323CBConfTerLeft)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMDLTERLABEL tTerLabel ); //回调离开会议的终端
// typedef BOOL (H323CALLBACK* H323CBConfTerIDListRequest)( HMDLCALL hCall, HMDLAPPCALL hAppCall );   //回调终端ID列表请求
// typedef BOOL (H323CALLBACK* H323CBConfTerLabelListRequest)( HMDLCALL hCall, HMDLAPPCALL hAppCall );  //回调终端List列表请求



/**新会控接口前面的不用*/
typedef BOOL32 (PROTO_CALLBACK* H323CBTerFloorReqToMc)( HMDLAPPCONFID hAppConfId, TMDLTERLABEL tTerLabel );
typedef BOOL32 (PROTO_CALLBACK* H323CBTerChairReqToMc)( HMDLAPPCONFID hAppConfId, TMDLTERLABEL tTerLabel );
typedef BOOL32 (PROTO_CALLBACK* H323CBTer239TokenReqToMc)( HMDLAPPCONFID hAppConfId, TMDLTERLABEL tTerLabel );
typedef BOOL32 (PROTO_CALLBACK* H323CB239TokenOwnerToMc)( HMDLAPPCONFID hAppConfId, TMDLTERLABEL tTerLabel );


/**chiar请求的回调*/
typedef BOOL32 (PROTO_CALLBACK* H323CBChairSendThisSource)( HMDLAPPCONFID hAppConfId, TMDLTERLABEL Viewer, TMDLTERLABEL Viewed );
typedef BOOL32 (PROTO_CALLBACK* H323CBChairBroadcastTerminal)( HMDLAPPCONFID hAppConfId, TMDLTERLABEL tTerLabel );
typedef BOOL32 (PROTO_CALLBACK* H323CBChairCancelBroadcastTerminal)( HMDLAPPCONFID hAppConfId, TMDLTERLABEL tTerLabel );
typedef BOOL32 (PROTO_CALLBACK* H323CBSendThisSourceRsp)( HMDLCALL hCall, HMDLAPPCALL hAppCall, BOOL32 bIsSuccess );

/**ter侧回调*/
typedef BOOL32 (PROTO_CALLBACK* H323CBMultipleConf)( HMDLCALL hCall, HMDLAPPCALL hAppCall );
typedef BOOL32 (PROTO_CALLBACK* H323CBSelfTerLabel)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMDLTERLABEL tTerLabel );
typedef BOOL32 (PROTO_CALLBACK* H323CBChairTokenOwner)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMDLTERMINALINFO tTerInfo );
typedef BOOL32 (PROTO_CALLBACK* H323CBTerList )( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMDLTERINFOLIST tTerList );
typedef BOOL32 (PROTO_CALLBACK* H323CBYouAreSeeing)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMDLTERMINALINFO tTerInfo );
typedef BOOL32 (PROTO_CALLBACK* H323CBSeeByAll)( HMDLCALL hCall, HMDLAPPCALL hAppCall );
typedef BOOL32 (PROTO_CALLBACK* H323CBTerFloorReqToChair)( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMDLTERMINALINFO tTerInfo );

/**Conf CallBack Struct*/
typedef struct tagH323ConfCallBack
{
	/**ter侧回调*/
	H323CBMultipleConf m_cbMultipleConf;
	H323CBSelfTerLabel m_cbSelfTerLabel;
	H323CBChairTokenOwner m_cbChairTokenOwner;
	H323CBTerList m_cbTerList;
	H323CBYouAreSeeing m_cbYouAreSeeing;
	H323CBSeeByAll m_cbSeeByAll;
	/**chair回调*/
	H323CBTerFloorReqToChair m_cbTerFloorReqToChair;
	H323CBSendThisSourceRsp m_cbSendThisSouceRsp;
	
	/**mc侧回调*/
	H323CBTerFloorReqToMc m_cbTerFloorReqToMc;
	H323CBTerChairReqToMc m_cbTerChairReqToMc;
	H323CBChairSendThisSource m_cbChairSendThisSource;
	H323CBChairBroadcastTerminal m_cbChairBroadcastTerminal;
	H323CBChairCancelBroadcastTerminal m_cbChairCancelBroadcastTerminal;
	H323CBTer239TokenReqToMc m_cbTer239TokenReqToMc;
	H323CB239TokenOwnerToMc m_cb239TokenOwnerToMc;
	
	tagH323ConfCallBack()
	{
		memset( this , 0 , sizeof(tagH323ConfCallBack) );
	}
}TH323ConfCallBack;


typedef struct tagH323ModuleLogCfg
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
	tagH323ModuleLogCfg()
	{
		clear();
	}
}TH323ModuleLogCfg;

/**H323 config struct*/
typedef struct tagH323Cfg
{
	s32 m_nh323ServiceAppId;
	s32 m_nh323StackinAppid;
	s32 m_nh323StackoutAppid;

	PFC_IPADDR m_th323StackIp;

	u16 m_wh225port;
	u16 m_dwh323StackPortStart;
	u16 m_dwh323StackPortEnd;

	u16 m_wTotalCallNum;
	u16 m_wTotalRegNum;

	emModuleEndpointType m_emEndpointType;

	TH323CallCBFunction m_tCallCBFuntion;
	TH323ChannelCBFunction m_tChannelCBFuntion;
	TH323ConfCallBack m_cbConfCallBack;
	CBRegResult     m_cbRegResult;
	H323CBConfEvent m_cbConfEvent;
	CBOnlineList    m_cbOnlineList;

	BOOL32          m_bOptimizeMem;			/**<初始化是否需要对stack模块内存优化选项(rasInit)*/
	ALL_LOG_CALlBACK  m_fpLogCB;				///< add callback function for print
	TH323ModuleLogCfg m_tH323Log;                    ///< Let the business set the PfcOpenLogFile parameters

	tagH323Cfg()
	{
		m_nh323ServiceAppId = -1;
		m_nh323StackinAppid = -1;
		m_nh323StackoutAppid = -1;

		m_wh225port = 1720;

		m_wTotalCallNum = 10;
		m_wTotalRegNum = 10;
		m_dwh323StackPortStart = 60000;
		m_dwh323StackPortEnd = 60000+4*10;

		m_emEndpointType = emModuleEndpointMT;

		m_cbRegResult = NULL;
		m_cbConfEvent = NULL;
		m_cbOnlineList = NULL;
		m_bOptimizeMem = TRUE;
		m_fpLogCB = NULL;
		m_th323StackIp.Clear();
		
	}

}TH323Cfg;

/**Call API for H323module:*/
class H323Module
{
	
public:
	//Set H460 configuration
	static BOOL32 H323ModuleSetH460Config(BOOL32 bSupportH460, BOOL32 bMediaTraversalServer, BOOL32 bSupportTransMultiMedia);	
	/**H323 module init function*/
	static BOOL32 H323ModuleInit( TH323Cfg &tCfg );
	/**H323 module start recv*/
	static BOOL32 H323ModuleStart();
	/**H323 module stop recv*/
	static BOOL32 H323ModuleStop();
	/**H323 module exit function*/
	static BOOL32 H323ModuleExit();
	/**H323 module create a new outgoing call*/
	static BOOL32 H323ModuleMakeOutgoingCall( HMDLAPPCALL hAppCall, TModuleCallInfo* ptModuleCallInfo, TCallCapbility* ptSendCapbility, TCallCapbility* ptRecvCapbility, HMDLAPPCONFID hAppConfId = 0, TMDLTERLABEL* pTerLabel = NULL, TFeccCapbility* ptFeccCap = NULL, TMMcuCapbility* ptMMcuCap = NULL );
	/**H323 module answer a new call*/
	static BOOL32 H323ModuleCallAnswer( HMDLCALL hCall, HMDLAPPCALL hAppCall, TModuleCallInfo* ptModuleCallInfo, TCallCapbility* ptSendCapbility, TCallCapbility* ptRecvCapbility, HMDLAPPCONFID hAppConfId = 0, TMDLTERLABEL* pTerLabel = NULL, TFeccCapbility* ptFeccCap = NULL, TMMcuCapbility* ptMMcuCap = NULL );
	/**H323 module reject a call*/
	static BOOL32 H323ModuleCallReject( HMDLCALL hCall, HMDLAPPCALL hAppCall, EmModuleCallDisconnectReason emReason );
	/**H323 module hangup a call*/
	static BOOL32 H323ModuleCallHangup( HMDLCALL hCall, HMDLAPPCALL hAppCall, EmModuleCallDisconnectReason emReason );

	/**for interworking [20140214]*/
	static BOOL32 H323LocalSendCapSet( HMDLCALL hCall, HMDLAPPCALL hAppCall , TCallCapbility* ptSendCapbility);
	static BOOL32 H323IWReopenChannel( HMDLCALL hCall , HMDLAPPCALL hAppCall , HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan  , TChanConnectedInfo * ptReopenChanInfo);
	/**set standard or nonstandard stack*/
	static s32 H323ModuleSetKDV323(BOOL32 bIsTypeKD323);
	/**Channel API:*/
public:
	static BOOL32 CloseChannel( HMDLCALL hCall, HMDLAPPCALL hAppCall, HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan );
	static BOOL32 FlowCtrl( HMDLCALL hCall , HMDLAPPCALL hAppCall , HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan , u16 wBitrate );
    static BOOL32 FastUpdate( HMDLCALL hCall , HMDLAPPCALL hAppCall , HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan  );
	static BOOL32 DualSteam( HMDLCALL hCall , HMDLAPPCALL hAppCall , HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan, TCallCapbility* ptDualCap);
	
	/**
	* \brief            DualStreamAnswer
	* \param[in]        hCall		:Call handle for module
	* \param[in]        hAppCall    :Call handle for upper
	* \param[in]        hChan       :Chan handle for module
	* \param[in]        hAppChan    :hAppChan handle for upper
	* \param[in]        bIsSuc      :TRUE is answer,FALSE is stop and ptDualInfo is null
	* \param[in]        ptDualInfo  :Dual Info
	* \retval           success:TRUE
	* \retval           failed :FALSE
	*/

	static BOOL32 DualStreamAnswer( HMDLCALL hCall, HMDLAPPCALL hAppCall, HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan, BOOL32 bIsSuc, TChanConnectedInfo* ptDualInfo );
	static BOOL32 DualStreamStop( HMDLCALL hCall, HMDLAPPCALL hAppCall, HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan );

    /**for manual channel on/off*/
    static BOOL32 ChannelSwitch( HMDLCALL hCall, HMDLAPPCALL hAppCall, HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan, BOOL32 bActive);
    
	/**for dual channel on/off[20130107]*/
	static BOOL32 H323ModuleChanEvent( HMDLCALL hCall, HMDLAPPCALL hAppCall, HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan, u16 wEvent, u8* pBuf, u16 wLen);

	/**REG API*/
public:
	static BOOL32 Regist( HMDLREG hReg , HMDLAPPREG hAppReg , TRegistReq* ptRegInfo );
	static BOOL32 UnRegist( HMDLREG hReg , HMDLAPPREG hAppReg );
	static BOOL32 RegistUpdate( HMDLREG hReg, HMDLAPPREG hAppReg, TRegistReq* ptRegInfo );

public:
	/**CONFERENCE*/
	static BOOL32 H323ModuleConfEvent( HMDLCALL hCall, HMDLAPPCALL hAppCall, u16 wEvent, u8* pBuf, u16 wLen );

	/**cascade MMcu*/
	static BOOL32 H323ModuleMMcuEvent( HMDLCALL hCall, HMDLAPPCALL hAppCall, HMDLCHANNEL hChan, HMDLAPPCHANNEL hAppChan, u16 wEvent, u8* pBuf, u16 wLen);

	/**新接口  上面的不用*/
	/**mc用*/
	static BOOL32 H323MCStopConference( HMDLAPPCONFID hAppConfId );
	static BOOL32 H323MCMakeSpeaker( HMDLAPPCONFID hAppConfId, TMDLTERLABEL tTerLabel );
	static BOOL32 H323MCWithdrawSpeaker( HMDLAPPCONFID hAppConfId, TMDLTERLABEL tTerLabel );
	static BOOL32 H323MCMakeChair( HMDLAPPCONFID hAppConfId, TMDLTERLABEL tTerLabel );
	static BOOL32 H323MCWithdrawChair( HMDLAPPCONFID hAppConfId, TMDLTERLABEL tTerLabel );
	static BOOL32 H323MCSendThisSource( HMDLAPPCONFID hAppConfId, TMDLTERLABEL Viewer, TMDLTERLABEL Viewed );
	static BOOL32 H323MCCancelSendThisSource( HMDLAPPCONFID hAppConfId, TMDLTERLABEL Viewer, TMDLTERLABEL Viewed );
	static BOOL32 H323MCAddTer( HMDLAPPCONFID hAppConfId, TMDLTERMINALINFO* ptTerInfoList, u8 byNum );
	static BOOL32 H323MCDelTer( HMDLAPPCONFID hAppConfId, TMDLTERMINALINFO* ptTerInfoList, u8 byNum );

	/**chair用*/
	static BOOL32 H323ChairCancelMakeMeChair( HMDLCALL hCall, HMDLAPPCALL hAppCall );
	static BOOL32 H323ChairSendThisSourceCmd( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMDLTERLABEL tTerlabel );
	static BOOL32 H323ChairCancelSendThisSource( HMDLCALL hCall, HMDLAPPCALL hAppCall );
	static BOOL32 H323ChairBroadcastTerminalReq( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMDLTERLABEL tTerLabel );
	static BOOL32 H323ChairBroadcastTerminalCmd( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMDLTERLABEL tTerLabel );
	static BOOL32 H323ChairCancelBroadcastTerminal( HMDLCALL hCall, HMDLAPPCALL hAppCall );

	/**ter用*/
	static BOOL32 H323TerMakeMeSpeaker( HMDLCALL hCall, HMDLAPPCALL hAppCall );
	static BOOL32 H323TerMakeMeChair( HMDLCALL hCall, HMDLAPPCALL hAppCall );
	
public:
	static BOOL32 H323SendFeccMsg( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMdlFeccStruct tFeccAction, TMDLTERLABEL tSrcLabel, TMDLTERLABEL tDstLabel );
	static BOOL32 H323SetFeccStreamId( HMDLCALL hCall, HMDLAPPCALL hAppCall, TMdlFeccStreamIdInfo tFeccStreamIdInfo);
	
	static BOOL32 H323SetStaticNAT(u32 dwNATIP);
	static BOOL32 H323SetStaticNAT(PTStaticNATAddr pStaticNATAddr);
public:
	static BOOL32 H323OnlineListReq( EmModuleGetGKInfoType emType, HMDLREG hReg, HMDLAPPREG hAppReg, u32 dwAppId );
    static BOOL32 H323ChanConnectTimeOut(u32 dwTimeOut);
private:
	/**added by sna for print capbility form upper level [20140219]*/
	/**bIsOnlyDual变量：DualStream的时候只打印双流发送能力*/
	static void H323PrintCapbility( TCallCapbility* ptSendCapbility, TCallCapbility* ptRecvCapbility, BOOL32 bIsOnlyDual=FALSE );
	//added end

public:
	static u16 m_wh323serviceAppId;
	static TH323ChannelCBFunction m_tCHannelCBFuntion;
	static TH323CallCBFunction m_tCallCBFunction;
//	static TH323ConfCBFunction m_tConfCBFunction;
	static TH323ConfCallBack m_tConfCallBack;
	static CBRegResult     m_CbRegResult;
	static H323CBConfEvent m_CbConfEvent;
//	static H323CBFeccMsg   m_CbFeccMsg;
	static CBOnlineList    m_CbOnlineList;
    static u32 m_dwChanConnectTimeOut;
};

/**打印*/
static u8 g_byMDLLogLevel = 0;
static BOOL32 g_bLog2File = FALSE;
static BOOL32 g_bLog2Screen = TRUE;
static s8 g_achCallerAlias[MAX_ALIAS_LEN]  = "all";
static u8 g_byModuleType = (int)emModuleAll;
static u16 g_wCallNum = 0;
static emCallBy g_emCallBy = emModuleCallByNum;

#define IS_LOG(n)  (n <= g_byMDLLogLevel)
#define MODULE_PRINT_BUFFERSIZE  1024

/**Debug Commomd*/
PROTO_EXTERN_API void h323msetlog( u8 byLevel );
PROTO_EXTERN_API void h323mcallbyname( s8* pchCallerAlias );
PROTO_EXTERN_API void h323mcallbynum( u8 wCallNum );
PROTO_EXTERN_API void h323mtype( u8 byModuel );
PROTO_EXTERN_API void h323mcallby( u8 byCallBy );
PROTO_EXTERN_API void h323mhelp(); 
PROTO_EXTERN_API void h323mshowreg();
PROTO_EXTERN_API void h323mshowcall( u8 i );
PROTO_EXTERN_API void h323mshowconf();
PROTO_EXTERN_API void h323mver();

void ModulePrintf( emModuleType ModuleType, u16 byLogLevel, s8* pchCallerAlias, HAPPCALL byCallNum, const char* pFormat, ... );

/**Defined for 64bit*/
#define HMDLAPPCONFID_TO_U8(x)		(u8)(u32)(u64)(x)

#define HAPPCALL_TO_U16(x)			(u16)(u32)(u64)(x)
#define HAPPCHAN_TO_U16(x)			(u16)(u32)(u64)(x)

#define HMDLAPPCALL_TO_U16(x)		(u16)(u32)(u64)(x)
#define HMDLAPPCHANNEL_TO_U16(x)	(u16)(u32)(u64)(x)

#define HMDLCALL_TO_U16(x)			(u16)(u32)(u64)(x)
#define HMDLCHANNEL_TO_U16(x)		(u16)(u32)(u64)(x)

#define HCALL_TO_U16(x)			    (u16)(u32)(u64)(x)	
#define HCHAN_TO_U16(x)			    (u16)(u32)(u64)(x)

#define HMDLREG_TO_U16(x)			(u16)(u32)(u64)(x)
#define HMDLAPPREG_TO_U16(x)		(u16)(u32)(u64)(x)

#define TH323CFG_TO_U32(x)          (u32)(u64)(x)
#define HAPPRAS_TO_U16(x)		    (u16)(u32)(u64)(x)

#endif

