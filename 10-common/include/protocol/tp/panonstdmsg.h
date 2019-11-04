#ifndef PANONSTDCOFMSG_H
#define PANONSTDCOFMSG_H
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
		emPACloseVidChanCmd,                //关闭视频通道           u16
		
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

		emPATpInviteCnsByAlias_Cmd,         //多点会议中通过名字邀请列表中不存在的会场          TPAAlias
		emPATpInviteCnsByAlias_Ind,         //多点会议中通过名字邀请列表中不存在的会场回应      TPAAlias, EmPACnsCallReason
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
};

#endif