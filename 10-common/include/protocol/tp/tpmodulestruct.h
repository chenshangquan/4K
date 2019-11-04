#ifndef TPMODULESTRUCT_H
#define TPMODULESTRUCT_H
#include "pastruct.h"

#define     TPMODULE_MAX_NAME_LEN             64            //最大名字数
#define     TPMODULE_REGNAME_SIZE			  64            //注册别名个数
#define     TPMODULE_MAX_PASSWORD_LEN         16            //密码最大长度
#define     TPMODULE_INVALID_VALUE            -1            //用作s32的无效值  


enum EmPAEndpointType
{
	emPAEndpointTypeUnknown  = 0,
	emPAEndpointTypeCNS	     = 0x01,
	emPAEndpointTypeUMS		 = 0x02,
	emPAEndpointTypeRegister = 0x04
};


enum EmPASipLevel
{
	emPASipCounty,
	emPASipCity,
	emPASipProvince,
	emPASipUnKnown = 255,
};

enum EmPACapSign    //能力标识， 大，左，右
{
	emPACapBig = 0,  
	emPACapLeft,
	emPACapSmall = emPACapLeft,  //能力标识由原来的大，左，右转换成大，小，
	                             //枚举只有0,1,2。原来的左相当于小，右相当于结束
	emPACapRight,
	emPACapEnd = emPACapRight,
};

enum EmPAAddrType
{
	emPAUnknown =0,
	emPAAlias,
	emPAE164Num,
	emPAIPAddr,
	emPAIP6Addr,
	emPADomain,
};

enum EmPAConnection
{
	emPAConnectionType = 0,
	emPATcpConnection,
	emPAUdpConnection,
	emPASCTPConnection,
	emPATLSConnection,
};

typedef struct tagPARegistLocalInfo
{
	EmPAEndpointType  m_emEndpointType;				  //类型是ums或cns
	u32 m_dwLocalIP;								  //自身IP地址
	s8  m_achSoftVersion[TPMODULE_MAX_NAME_LEN + 1];  //软件版本号
	s8  m_achCompileTime[TPMODULE_MAX_NAME_LEN + 1];  //编译时间
public:
    tagPARegistLocalInfo() {memset(this, 0, sizeof(tagPARegistLocalInfo));}
}TPARegistLocalInfo, *PTPARegistLocalInfo;


typedef struct tagPARegName
{
	EmPAAddrType m_emPAAddrType;                      //注册名的type
	s8  m_achUserName[TPMODULE_MAX_NAME_LEN + 1];     //注册名
	tagPARegName()
	{
		memset( this, 0, sizeof(tagPARegName) );
	}
}TPARegName, *PTPARegName;

typedef struct tagPARegCfg
{
	u32      m_dwHostIP;		 //注册主机IP地址
	u16      m_wHostPort;      //注册主机端口
	u32      m_dwRegIP;        //注册服务器IP地址
	u16      m_wRegPort;	     //注册服务器端口
	u16      m_wExpire;

	s32		           m_nPARegNameSize;                             //实际别名个数
	TPARegName         m_atPARegName[TPMODULE_REGNAME_SIZE];         //注册别名支持多个
	TPARegistLocalInfo m_tRegistLocalInfo;
	EmPAConnection	   m_emConnection;								 //注册地址类型

	tagPARegCfg()
	{
		memset( this, 0, sizeof(tagPARegCfg) );
		m_emConnection = emPAUdpConnection;
	}
}TPARegCfg, *PTPARegCfg;


//网真呼叫额外的参数
typedef struct tagCallInfoTP
{
	//EmPAEndpointType		  m_emEndpointType;
	EmPASipLevel			  m_emSipLevel;
	s32                       m_nScreenNum;                           //屏总数
	
public:
	tagCallInfoTP()
	{
		Clear();
	}
	
	void Clear()
	{
		//m_emEndpointType = emPAEndpointTypeUnknown;
		m_emSipLevel = emPASipUnKnown;
		m_nScreenNum = TPMODULE_INVALID_VALUE;
	}
}TCallInfoTP;


//专门用于网真的参数
typedef struct tagDescriptTP
{
	BOOL32 m_bAudMix;
	s32	m_nScreenNo;                //屏序号
	s32	m_nPACapSignNum;
	EmPACapSign m_aemPACapSign[MAX_TP_STREAM_NUM];				 //标识大小码流, 能力发下来时一定要按照顺序， 左，中，右 
	PFC_IPADDR m_atRtpAddr[MAX_TP_STREAM_NUM];
	PFC_IPADDR m_atRtcpAddr[MAX_TP_STREAM_NUM];
	
	void Clear()
	{
		m_bAudMix = FALSE;
		m_nScreenNo = TPMODULE_INVALID_VALUE;
		m_nPACapSignNum = 0;
		for ( s32 i = 0; i < MAX_TP_STREAM_NUM; i++ )
		{
			m_aemPACapSign[i] = emPACapBig;
			m_atRtpAddr[i].Clear();
			m_atRtcpAddr[i].Clear();
		}
	}

	tagDescriptTP()
	{
		Clear();
	}
}TDescriptTP;

//对应到每一个能力
typedef struct tagCallDescriptTP
{
	u16 m_wAudioNum;
	TDescriptTP m_tAudioList[MAX_AUDIO_NUM];     
	u16 m_wVideoNum;
	TDescriptTP m_tVideoList[MAX_VIDEO_NUM];

	tagCallDescriptTP()
	{
		Clear();
	}
	
	void Clear()
	{
		m_wAudioNum = 0;
		m_wVideoNum = 0;
		s32 i = 0;
		for ( i = 0; i < MAX_AUDIO_NUM; i++ )
		{
			m_tAudioList[i].Clear();
		}
		for ( i = 0; i < MAX_VIDEO_NUM; i++ )
		{
			m_tVideoList[i].Clear();
		}
	}

}TCallDescriptTP;

typedef struct tagChanDescriptTP
{
	TDescriptTP m_tLocalTP; //本地TP参数
	TDescriptTP m_tPeerTP;  //对端TP参数

	tagChanDescriptTP()
	{
		m_tLocalTP.Clear();
		m_tPeerTP.Clear();
	}

}TChanDescriptTP;

enum EmPAConfMsgType
{
	  emPAConfMsgTypeBegin = 0,

		emPAChanMsgBegin = 1,
		emPAConfFastUpdate,                 //NULL
		emPAConfFlowCtrl,                   //wBitRate
		emPAChanMeetingSpeaker,             //cns->ums 会场内发言人
		emPAChanSelecteCascad,              //add-by wuhu cns向ums指定选看, 参数 u16,表示会场id
		emPAChanSelecteCascadRes,           //ums回复cns选看结果， TPAChanSelecteCascadRes, 表示结果
    emPAChanSelecteCascadCancel,        //取消选看，无参数
		emPAChanSelecteCascadCancelRes,     //取消选看结果，  参数u32, 表示结果 
		emPAChanSeeLocal,                   //ums -> cns, 看本地，无参数
		emPAChanSeeLocalCancel,             //ums -> cns  取消看本地，无参数
		emPAChanMsgEnd = 160,

		emPAConfMsgBegin = 161,
		emPAConfYouAreSeeing,               //TYouAreSeeing 发言人指示
		emPAYouAreSeeing_v2,			    //TPAYouAreSeeing
		emPAConfBeChairman,                 //BOOL ums->cns 成为主席
		emPAConfCascadingSpeaker,           //TPACascadingSpeaker 级联信令 级联会场内发言人
		emPAConfStartPoll,                  //TPAPollCmd 级联信令 开启轮询
		emPAConfStartPollAck,               //TPAPollAck
		emPAConfPollNodeChange,             //TPAPollNodeChange 级联信令
		emPAConfEndPoll,                    //u32(Reserved)
		emPAConfPollFastUpdate,             //级联信令u32(Reserved)
		emPAConfStatusIndicate,             //TPAConfStatusInd , ums->cns
		emPAConfPeerMuteCmd,                //远端哑音  TPAPeerMuteCmd
		emPAConfPeerMuteInd,                //远端哑音状态指示 TPAPeerMuteInd
		emPAConfCallCascadingOff,           //呼叫下级未上线会场 u16 epid
		emPAConfHangUpCascadingConf,        //挂断下级会议 THangupCascadingConf
		emPAConfNodeUpdateTrList,           //通知更新结点信息 TPAConfNodeUpdateTrList
		emPAConfNodeUpdateB2NewTrList,      //通知更新结点信息 TPAConfNodeUpdateB2NEWTrList
		emPAConfNodeDelTrList,              //通知删除结点 TPAConfNodeDelTrList
		emPAConfAudMixEpCmd,                //上级通知下级混音某个端点  TPAAudMixEpCmdTr
		emPAConfAudMixEpAck,                // 下级通知上级混音某个端点的结果 TPAAudMixEpAckTr
		emPAConfAudMixEpStop,               // 上级级通知下级停止某个端点的混音 u16
		emPAConfAudMixOpenNCmd,             // 上级通知下级打开N模式通道 TPAAudMixEpCmdTr
		emPAConfAudMixOpenNAck,             // 下级通知上级打开N模式通道 TPAAudMixEpAckTr
		emPAConfPeerSoundOffCmd,            //远端静音 TPAPeerMuteCmd
		emPAConfPeerSoundOffInd,            //远端静音指示 TPAPeerMuteInd
		emPARequestDualStreamCmd,           //请求发双流 TDualRequest
		emPARequestDualStreamInd,           //请求发双流指示 BOOl + EmDualReason + TDualRequest
		emPASendDualStream,                 //发双流 TDualInfo
		emPASendDualStreamAck,              //发双流结果 TDualInfoAck
		emPAStopDualStream,                 //停止双流 TPAEpKey
		emPADualStreamFastUpdate,           //双流关键帧请求 BOOL32值
		emPAViewLocal,                      //看本地 u32(Reserved)
		emPACancelViewlocal,                //取消看本地 u32(Reserved)
		emPAStartRcvDualInd,                //接受双流指示TPAEpKey
		emPAStopRcvDualInd,                 //停止接受双流指示EmDualReason
		emPAAddTvMonitorCmd,                //电视墙监控 TPATvMonitorCmd 
		emPAAddTvMonitorInd,                //电视墙监控 TPATvMonitorInd 
		emPAStopMonitorCmd,	                //停止电视墙的监控	u16
		emPAAskKeybyScreen,                 //停止电视墙的监控	TPAAskKeyByScreenTr
		emPAPollDstNameInd,                 //通知轮询目标信息 ,TPAPollDstName
		emPASrcDualNameInd,                 //通知双流源信息 TPAName
		emPAChairCapNotify,                 //通知下级主席坐席调整
		emPAConfCnsList,                    // UMS给CNS报会场列表,   参数： TPAConfCnsList;
		emPAConfStartPolling,               //cns向ums请求轮询,  无参数，但需传递无意义的u32值
    emPAConfStartPollingRes,            //ums回应cns轮询结果, 参数：u32
		emPAConfClosePolling,               //cns向ums关闭轮询,   无参数，但需传递无意义的u32值
		emPAConfClosePollingRes,            //ums向cns回应关闭轮询结果,  参数 u32
		emPAConfNotifyPollingRes,           //ums通知cns当前轮询结果,   参数 BOOL32
		emPACascadeStartViewcmd,	          //上级通知下级选看某个会场 TPAViewCmd
		emPACascadeStartViewInd,	          //下级通知上级选看某个会场结果 TPAViewAck
		emPACascadeStopView_cmd,	          //上级通知下级停止某个选看	u16
		emPACascadeGetVidcmd,	              //上级调用下级图像 TPAViewCmd
		emPACascadeGetVidInd,	              //下级调用下级图像结果 TPAViewAck
		emPACascadeStopGetVidcmd,	          //上级通知停止下级调用	u16
		emPACascadeFlowCtrl,		            //上级通知下级flowctrl， 参数TPAFlowControl
		
		emPAOpenAudChanCmd,                 //打开音频通道           TPAAudChanCmd
		emPAOpenAudChanAck,                 //打开音频通道应答       TPAAudChanAck
		emPAOpenVidChanCmd,                 //打开视频通道           TPAVidChanCmd
		emPAOpenVidChanAck,                 //打开视频通道应答       TPAVidChanAck
		emPACloseVidChanCmd,                //关闭视频通道           u16+u32
		
		emPATpConfAMixUpdate_Cmd,           //多点会议开启           TPAConfAuxMixInfo
		emPATpConfAMixUpdate_Ind,           //多点会议回应           TPAConfAuxMixInfo
		emPATpConfAMixUpdate_Nty,           //多点会议讨论开启通知   TPAConfAuxMixInfo
		
		emPATpConfApplySpeaker_Cmd,         //多点会议切换发言人     TPAConfEpID
		emPATpConfApplySpeaker_Ind,         //多点会议切换发言人回应 TPAConfEpID,  EmPATpApplySpeakerRet 
		emPATpConfApplySpeaker_Nty,         //多点会议切换发言人通知 TPAConfEpID
		
		emPATpConfMute_Cmd,                 //多点会议控制远端哑音      TPAConfEpID, BOOL,  TRUE指示远端哑音，FALSE取消远端哑音
		emPATpConfMute_Ind,                 //多点会议控制远端哑音回应  TPAConfEpID, BOOL,  TRUE指示远端哑音，FALSE取消远端哑音
		emPATpConfMute_Nty,                 //多点会议控制远端哑音通知  TPAConfEpID, BOOL,  TRUE指示远端哑音，FALSE取消远端哑音

		emPATpConfQuiet_Cmd,                //多点会议控制远端静音        TPAConfEpID, BOOL,  TRUE指示远端哑音，FALSE取消远端哑音
		emPATpConfQuiet_Ind,		            //多点会议控制远端静音回应    TPAConfEpID, BOOL,  TRUE指示远端哑音，FALSE取消远端哑音
		emPATpConfQuiet_Nty,                //多点会议控制远端静音通知    TPAConfEpID, BOOL,  TRUE指示远端哑音，FALSE取消远端哑音
		
		emPATpConfStartDual_Cmd,            //多点会议双流请求          TPAConfEpID   
		emPATpConfStartDual_Ind,            //多点会议双流请求应答      TPAConfEpID,  EmPATPDualReason
		emPATpConfStopDual_Cmd,             //多点会议停双流请求        TPAConfEpID
		emPATpConfStopDual_Ind,             //多点会议停双流请求应答    TPAConfEpID,  EmPATPDualReason
		emPATpConfDualEp_Nty,               //多点会议双流会场广播通知  TPAConfEpID

		emPATpInviteCnsByAlias_Cmd,         //多点会议中通过名字邀请列表中不存在的会场          TPACallAddr
		emPATpInviteCnsByAlias_Ind,         //多点会议中通过名字邀请列表中不存在的会场回应      TPACallAddr, EmPACnsCallReason
		emPATpInviteCnsByEpId_Cmd,          //多点会议中通过名字呼叫列表中存在的不在线会场      u16 wEpId
		emPATpInviteCnsByEpId_Ind,          //多点会议中通过名字呼叫列表中存在的不在线会场回应  u16 wEpId, EmPACnsCallReason
	
		emPATpHangupCns_Cmd,                 //多点挂断指定会场         u16 wEpId
		emPATpHangupCns_Ind,                 //多点挂断指定会场回应     u16 wEpId, EmPACnsCallReason
		emPATpHangupConf_Cmd,                //挂断会议                 无参数，需传递无意义的u32值
		
		emPATpUpdateConfTurnlist_Nty,        //轮询列表通知           TPAConfTurnInfo
		emPATpCallEPResult_Ind,              //呼叫结点结果           TPAConfCallEpAddr, EmPACnsCallReason,  
		emPATpChairConfInfo_Nty,             //通知主席会议信息       TPAChairConfInfo
		emPATpAudMixStatus_Nty,              //会场语音激励状态通知   TPAAudMixStat

		emPAAdjustFrameRate_Cmd,             //TPAAdjustFrameRate
		emPAAdjustVidRes_Cmd,                //TPAAdjustVidRes
		
		emPAUmsDiscussScreenStat_Notify,     //讨论模式中的会场，需要收到讨论状态通知, TPADisScreenStat 
		emPAUmsCnsSpeakerIndxAdjust_Notify,  //TPACascadingSpeaker
		
		emPAUmsDiscussFastUpdate_Req,        /*根据源会场ID和屏序号，就可以通过AskKeyByScreen来向目标会场的发言屏请求关键帧
		                                        TPADisAskKeyFrame */
		emPAUmsAudMixDisListOpr_Cmd,         //CNC -> CNS -> UMS, TPADisListOpr
		emPAUmsAudMixDisListOpr_Ind,         //UMS -> CNS -> CNC, TPADisListOpr

		emPAUmsCascadeOpenChairChan_Cmd,     // UMS 级联会议 打开主席通道命令, TPACascadeOpenChanCmd
		emPAUmsCascadeOpenChairChan_Ack,     // UMS 级联会议 打开主席通道应答, TPACascadeOpenChanAck

		emPAUmsCommonReasonToUI_Ind,         // 消息方向: ums -> cns -> cnc, 消息内容: TPAUmsReasonInd

    emPAUmsConfRecPlayState_Nty,         // 更新放像状态, 消息内容: TPAUmsUpRecPlayState
    emPAUmsConfStopRecPlay_Req,          // 停止下级的放像，无参数，但需传递无意义的u32值
		
		emPAChanResetFastUpdate,				     //通道消息，用来去除ums的关键帧保护，u32
		emPAJoinWBConf_Cmd,						       //消息体：U32 dwDsIPAddr
		emPAJoinWBConf_Ind,					         //消息体：BOOL bIsSucc
		emPAHangupWBConf_Cmd,			          //消息体：Null

		emPAVMPOpr_Cmd,						//开启/关闭画面合成, 消息体：TTPVMPInfo
		emPAVMPOpr_Ind,						//开启/关闭画面合成, 消息体：TTPVMPInfo

		emPAChanSelecteVMPView,             //选看画面合成, 无参数
		emPAChanSelecteVMPViewRes,          // 选看画面合成, u32,选看结果
		
		emPAChanSelecteVMPViewCancel,		//取消选看画面合成,无参数
		emPAChanSelecteVMPViewCancelRes,	//取消选看画面合成, u32,取消选看结果
		emPACNC_UMS_SelView_Req,			//TPATPSelViewReq
		emPAUMS_CNC_SelView_Ind,			//TPATPSelViewInd
		emPAUMS_UMC_SelView_Ntfy,			//TPASelViewNtfy
		
		emPAGetVid_Req,                     //TPAUmsHandle,TPAGetVidInfo
		emPAGetVid_Res,						//TPAUmsHandle,TPAGetVidInfoRes
		emPAGetVid_Stop_Req,				//TPAUmsHandle,TPAGetVidBaseInf
		emPAGetVid_Stop_Res,				//TPAUmsHandle,TPAStopGetVid

		emPAConf_SuspendPoll_Req,			//BOOL32
		emPAConf_SuspendPoll_Ind,			//u32
		emPAConf_CasecadePollEp_Req,		//TPACasecadePollEpReq
		emPAConf_CasecadePollEp_Rsp,		//TPACasecadePollEpRsp

		emPAUmsUpdateConfTurnlist_Ind,		//TPAPollListInd

		emPACNC_UMS_RervesBrdVmp_Req,       //TPARersvesEqpReq
		emPAUMS_CNC_RervesBrdVmp_Ind,		//TPARersvesEqpRsp
		emPACNC_UMS_SetBrdVmp_Req,			//TPASetVmpInfoReq
		emPAUMS_CNC_SetBrdVmp_Ind,			//TPASetVmpInfoRsp
		emPACNC_UMS_BrdVmp_Req,				//TPABrdVmpReq
		emPAUMS_CNC_BrdVmp_Ind,				//TPABrdVmpRsp
		emPAUMS_UMS_VmpCasecade_Ntfy,		//TPAVmpCasecadeNtfy
		emPAUMS_CNC_BrdVmp_Ntfy,			//TPABrdVmpResArray 

		emPAUmsConfAMixVacSwitch,			//语音激励开启和关闭      cns->ums   TPAConfAuxMixVacOpr
		emPAUmsConfAMixVacSwitchInd,		//语音激励开启和关闭回应  ums->cns	  TPAConfAuxMixVacOpr
		emPACNC_UMS_SaveVmpCfg_Cmd,			//TPAVmpMemberCfg
		emPAUMS_CNC_SaveVmpCfg_Ind,			//TPAVmpMemberCfgInd

		emPA_CnsJoinConf_Req,				//TPAConfEpInfo
		emPA_CnsJoinConf_Ack,				//TPAConfEpInfo

		emPACnsJoinConf_Notify,				//u16 TPACallAddr
		emPAUMS_CNS_HduPlan_Nty,			//TPAHduPlanPackData  这个消息采用分包发送，请注意
		emPACNS_UMS_HduPlay_Req,			//TPAHduPlayReq
		emPAUMS_CNS_HduPlay_Ind,			//TPAHduBaseInfo EmPAHduPlayNackReason
		emPACNS_UMS_HduStopPlay_Req,		//TPAHduPlayReq
		emPAUMS_CNS_HduStopPlay_Ind,		//TPAHduBaseInfo u16(错误码，0成功，非零失败)
		emPACNS_UMS_HduAllStopPlay_Req,		//u32
		emPACNS_UMS_HduSetVol_Req,			//TPAHduSetVolInfo
		emPAUMS_CNS_HduSetVol_Ind,			//TPAHduSetVolInfo EmPAHduSetVolRes
		emPACNS_UMS_HduChangeChanMode_Req,	//TPAHduChanModeSetInfo
		emPAUMS_CNS_HduChangeChanMode_Ind,	//TPAHduChanModeSetInfo EmPAHduChangeChanModeRes

		emPACNS_UMS_ConfAudMixMode_cmd,    //TPAUmsAudMixInfo
		emPAUMS_CNS_ConfAudMixMode_ind,    //TPAUmsAudMixModeCmdRes
		emPACNS_UMS_ConfAudMixList_cmd,    //TPAUmsAudMixListCmd
		emPAUMS_CNS_ConfAudMixList_ind,    //TPAUmsAudMixListCmdRes
		emPAUMS_CNS_ConfAudMixMode_Notify, //TPAUmsAudMixInfo
		emPAUMS_UMS_ConfAudMixMode_Notify, //TPAUmsAudMixCasecadeInfo

		emPAUmsConfRollCallUpdate_Cmd,    //TPAConfRollCallInfo
		emPAUmsConfRollCallUpdate_Ind,   //TPAConfRollCallInfo
		emPAUmsConfRollCallNextEp_Cmd,   //TPARollCallNextEpInfo
		emPAUmsConfRollCallNextEp_Ind,   //TPARollCallNextEpInfo
		emPAUmsRollCallScreenStat_Notify,//TPARollCallCasecadeNtfy
		emPAUmsConfRollCallUpdate_Nty,  //TPAConfRollCallInfo

		emPAUmsConfRollCallUpdataList_Cmd,//TPAUpdataRollCallList
		emPAUmsConfRollCallUpdataList_Ind,//TPAUpdataRollCallListRes
		emPAUmsRollUpdate_PresentState,//TPARollCallPresentStateMsg
		emPAUmsRoll_PresentState_Notify,//TPARollCallPresentStateMsg

		emPAUMS_CNS_EpInAudMix_Notify,//BOOL32

		emPAUMS_CNS_VidFeccInfoNty,//TPAConfVidFeccInfo 
		emPAConf_EpVidFeccInfo_Update,//TConfEpVidFeccList 

		emPAGetTempPwdCmd,        ///< TPAConfGetTempPwdReq 
		emPAGetTempPwdInd,        ///< 

		emPACNS_UMS_Vac_Cmd,		///< TPAUmsVacInfo
		emPA_UMS_CNS_VacCmd_Ind,
		emPA_UMS_CNS_VacInfo_Notify

};

typedef struct tagMdlCallCapTP
{
	TCallInfoTP m_tCallInfoTP;
	TCallDescriptTP m_tCallSndTP;
	TCallDescriptTP m_tCallRcvTP;

	tagMdlCallCapTP()
	{
		Clear();
	}

	void Clear()
	{
		m_tCallInfoTP.Clear();
		m_tCallSndTP.Clear();
		m_tCallRcvTP.Clear();
	}

}TMdlTPCap;

enum EmPAGetRegInfoType
{
	emPAGetRegInfoType_CNS = 0,
	emPAGetRegInfoType_UMS,
	emPAGetRegInfoType_ALL
};
typedef struct tagPAGetRegInfo
{
	EmPAGetRegInfoType m_emType; //register info type
	PFC_IPADDR m_tRegSeverAddr; //注册服务器IP地址
	PFC_IPADDR m_tRegLocalAddr; //注册服务器IP地址
	
	tagPAGetRegInfo()
	{
		memset( this, 0, sizeof(tagPAGetRegInfo) );
	}
}TPAGetRegInfo;

 
typedef struct tagTPARegPackInfo
{
	u16 m_wPackSeq;       //包序号，从1开始，0为无效值
	u16 m_wTotalPackNum;  //包总数
	tagTPARegPackInfo()
	{
		m_wPackSeq = 0;
		m_wTotalPackNum = 0;
	}
	
}TPARegPackInfo, *PTPARegPackInfo;


typedef struct tagTPARegInfo
{
	u16		   m_wAliasNum;
	TPAAlias   m_atAlias[PA_REGNAME_SIZE];           //暂时定为最大值为64个名称为一波返回
	EmPAEndpointType m_emSelfType;                   //注册方 的系统类型(UMS和CNS)    
	
	tagTPARegInfo()
	{
		m_wAliasNum = 0;
		memset( m_atAlias, 0, sizeof( m_atAlias ) );
		m_emSelfType = emPAEndpointTypeUnknown;
	}
	
}TPARegInfo;

typedef struct tagTPARegInfoUms
{
	u16		  m_wAliasNum;
	TPAAlias  m_atAlias[PA_REGNAME_SIZE];				 //暂时定为最大值为64个名称为一波返回
	PFC_IPADDR  m_atContactAddr[PA_CONTACT_ADDR_SIZE]; //注册地址
	u32 m_dwExpires;									 //超时时间,单位秒
	EmPAConnection emPaConnection;
	TPARegistLocalInfo m_tPaRegistLocalInfo;
	
	tagTPARegInfoUms()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTPARegInfoUms));
	}
	
}TPARegInfoUms;

typedef struct tagTPARegInfoCns
{
	u16		   m_wAliasNum;
	TPAAlias   m_atAlias[PA_REGNAME_SIZE_CNS];           //暂时定为最大值为2个名称为一波返回
	PFC_IPADDR  m_atContactAddr[PA_CONTACT_ADDR_SIZE]; //注册地址
	u32 m_dwExpires;//超时时间,单位秒
	EmPAConnection emPaConnection;
	TPARegistLocalInfo m_tPaRegistLocalInfo;
	
	tagTPARegInfoCns()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTPARegInfoCns));
	}
	
}TPARegInfoCns;

typedef struct tagTPARegPack
{
	TPARegPackInfo m_tPackInfo;
	EmPAGetRegInfoType m_emType;
	EmPAEndpointType  m_emEndpointType;
	u16	m_wTotalRegInfo;

	tagTPARegPack()
	{
		Clear();
		m_emType = emPAGetRegInfoType_ALL;
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTPARegPack));
	}

}TPARegPack;




#endif
