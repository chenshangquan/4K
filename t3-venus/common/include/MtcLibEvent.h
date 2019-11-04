/*****************************************************************************
模块名      : 终端控制台
文件名      : MtcLibEvent.h
相关文件    : 
文件实现功能: 声明消息代码
作者        : 熊广化
版本        : V3.0  Copyright(C) 1997-2003 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2003/12/16  3.0         熊广化      创建
*******************************************************************************/
#pragma once

/* 摘自eventid.h
终端控制台内部消息(12001-13000)
#define EV_MTC_BGN	EV_MC_END + 0x001
#define EV_MTC_END	EV_MTC_BGN + 0x3E7*/
#include "eventid.h"	// 消息码范围段定义

#define MTC_SYS_MSG_BEGIN		EV_MTC_BGN + 0x000


///////////////////////////////////////////////////////////////////////////////

enum EmMtcSysMsg
{
	/************************************************************************/
	/* mtc 连接上终端
	  wparam = 0
	  lparam = 0*/
	/************************************************************************/
	ev_MtcUIConnect		=	MTC_SYS_MSG_BEGIN,
#define		MTC_UI_CONNECTED  ev_MtcUIConnect
	/************************************************************************/
	/* 已断开终端
	 wParam = 0
	 lparam = 0*/
	/************************************************************************/
	ev_MtcUIDisconnected,
#define MTC_UI_DISCONNECTED	 ev_MtcUIDisconnected
	/************************************************************************/
	/* 终端状态更新
	lparam = 0
	wparam = 0*/
	/************************************************************************/
	ev_MtcUIMtStatusUpdated,
#define MTC_UI_MTSTATUS_UPDATED  ev_MtcUIMtStatusUpdated
	/************************************************************************/
	/* 终端待机通知
	wparam			MT_SLEEP/MT_WAKEUP	待机或工作
	lparma = 0*/
	/************************************************************************/
	ev_MtcUIDemancyInfo,
#define MTC_UI_DORMANCY_INFO       ev_MtcUIDemancyInfo
	/************************************************************************/
	/* 快照信息通知
	wParam = 0
	lparam = 0
	*/
	/************************************************************************/
	ev_MtcUISnapshotUpdated,
#define MTC_UI_SNAPSHOT_UPDATED	 	ev_MtcUISnapshotUpdated
	/************************************************************************/
	/* GK 注册状态通知
	 wparam = Trus/False  成功/失败*/
	/************************************************************************/
	ev_MtcUIGKRegistInd,

	ev_MtcUISerialNumber,

	/************************************************************************/
	/* PCMT数据会议启动回应通知
	 wparam = Trus/False  TRUE,允许;FALSE,不允许
	/************************************************************************/
	ev_MtcUIPcmtDataConfRspInd,
#define MTC_UI_PCMT_DATACONF_RSP	 	ev_MtcUIPcmtDataConfRspInd

	/************************************************************************/
	/* PCMT数据会议启动请求通知
	 wparam = Trus/False  TRUE,允许;FALSE,不允许
	/************************************************************************/
	ev_MtcUIPcmtDataConfReqInd,
#define MTC_UI_PCMT_DATACONF_REQ	 	ev_MtcUIPcmtDataConfReqInd
	/************************************************************************/
	/*    板卡类型通知         
	 wparam    emMtModel
	 lparam		= 0*/
	/************************************************************************/
	ev_MtcUIMtBoardUpdated,

	/************************************************************************/
	/* 终端升级回应
	wparam = True   同意  False  不同意
	lparam = 0*/
	/************************************************************************/
	ev_MtcUIUpdateSysAck,

#define MTC_UI_MTBOARD_UPDATED   ev_MtcUIMtBoardUpdated

	/************************************************************************/
	/* 终端升级是否成功
	wparam = True   成功  False  不成功
	lparam = 0*/
	/************************************************************************/
	ev_MtcUIUpdateSysInd,
#define MTC_UI_UPDATESYS_IND   ev_MtcUIUpdateSysInd

	/************************************************************************/
	/*  终端用户列表更新
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_MtcUIUserUpdated,
#define MTC_UI_USERS_UPDATED  ev_MtcUIUserUpdated
	/************************************************************************/
	/*   开始传送截屏视频流 u32 u32RtpIP u16 u16RtpPort
	wpram		如果是桌面双流为u32RptIP	RTP目的IP地址 否则0
	lparam		如果是桌面双流为u16PrtPort	RTP目的端口   否则0
	上层根据这个来判断双流类型*/
	/************************************************************************/
	ev_MtcUIStartSnap,
#define MTC_UI_STARTSNAP			ev_MtcUIStartSnap
	/************************************************************************/
	/* 停止传送截屏视频流(双流)                                                                     */
	/************************************************************************/
	ev_MtcUIStopSnap,
#define MTC_UI_STOPSNAP				ev_MtcUIStopSnap
	/************************************************************************/
	/*   双视频流状态指示
	  wparam		True / False 
	  lparam		0    (已经废弃) */
	/************************************************************************/
	ev_MtcUIDualVInd,
#define MTC_UI_DUALV_IND		ev_MtcUIDualVInd
	/************************************************************************/
	/*  音量改变	BOOL bInput, u32 dwVolume
	 wparam 是输入还是输出(true 输入, false 输出) 
	 lparam  u32 音量*/
	/************************************************************************/
	ev_MtcUIVolChanged,
#define MTC_UI_VOLUME_CHANGED   ev_MtcUIVolChanged
	/************************************************************************/
	/* 静音哑音  BOOL bSilent, BOOL bOn
	wparam bSilent	是静音还是哑音.静音指关闭音频信号输出,哑音指关闭音频信号输入
	lparam bOn		是开启还是关闭.开启静音使当前没有音频输出,反之是关闭静音*/
	/************************************************************************/
	ev_MtcUISlientAndMute,
#define MTC_UI_SILENT_AND_MUTE		ev_MtcUISlientAndMute

	/************************************************************************/
	/* 远端遥控 BOOL bEnable  
	wparam  bEnable	是开启还是禁用 */
	/************************************************************************/
	ev_MtcUIbFECC,
#define MTC_UI_REMOTE_CONTROL    ev_MtcUIbFECC

	/************************************************************************/
	/* 地址簿改变  BOOL bEntry     
	wparam bEntry  是条目还是条目组*/
	/************************************************************************/
	ev_MtcUIAddrChanged,
#define MTC_UI_ADDRBOOK_CHANGED		ev_MtcUIAddrChanged

	/************************************************************************/
	/* 自环测试通知 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_MtcUISelfCircleTest,
#define MTC_UI_CIRCLETEST		ev_MtcUISelfCircleTest

	/************************************************************************/
	/* 远端环回测试通知 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_MtcUIRemoteLoopBackTest,
#define MTC_UI_REMOTE_LOOP_BACK_TEST		ev_MtcUIRemoteLoopBackTest

	ev_MtcUIGKUnRegistInd,

	ev_MtcUISysMsgEnd
};



enum EmMtcMatrixMsg
{
	ev_MtcMatrixMsgBegin = ev_MtcUISysMsgEnd + 1,

	/************************************************************************/
	/*当前应用矩阵配置方案号更新 
	lparam 0
	wparam 0*/
	/************************************************************************/
	ev_MtcUIMatrixCurSchemeUpdated,
#define MTC_UI_MATRIX_UPDATED		ev_MtcUIMatrixCurSchemeUpdated
	/************************************************************************/
	/*  矩阵方案内容更新
	lparam 0
	wparam 0*/
	/************************************************************************/
	ev_MtcUIMatrixSchemeUpdated,
#define MTC_UI_MATRIX_SCHEME		ev_MtcUIMatrixSchemeUpdated
	/************************************************************************/
	/* 矩阵配置信息更新
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_MtcUIExMatrixCfgUpdated,
#define MTC_UI_EXMATRIX_UPDATED   ev_MtcUIExMatrixCfgUpdated
	/************************************************************************/
	/* 外部矩阵信息更新指示   
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_MtcUIExMatrixInfoUpdated,
#define MTC_UI_EXMATRIX_INFO_UPDATED	ev_MtcUIExMatrixInfoUpdated
	
	/************************************************************************/
	/* 外部矩阵连接关系的指示
	wparam = u8    输入端口的index (0基质)
	lparam = 0 */
	/************************************************************************/
	ev_MtcUIExVSourceUpdated,

	MTC_UI_EXMATRIX_NOTIFY,


	MTC_UI_AUDIOMATRIX,//音频矩阵
	ev_MtcMatrixMsgEnd
};


enum EmMtcP2PMsg
{
	ev_MtcP2PMsgBegin = ev_MtcMatrixMsgEnd + 1,
	
	/************************************************************************/
	/* 点对点会议开始 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_MtcUIP2PStarted,
#define MTC_UI_P2P_STARTED		ev_MtcUIP2PStarted
	/************************************************************************/
	/*点对点会议取消 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_MtcUIP2PCanceled,
#define MTC_UI_P2P_CANCELED   ev_MtcUIP2PCanceled
	/************************************************************************/
	/*点对点会议结束
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_MtcUIP2PEnd,
#define MTC_UI_P2P_ENDED			ev_MtcUIP2PEnd
	/************************************************************************/
	/* 点对点会议被呼叫
	wparam	u32 dwip  呼叫人的IP地址
	lparam  TCHAR * tszAlias  呼叫人的别名
	*/
	/************************************************************************/
	ev_MtcUIP2PBeCalled,
#define MTC_UI_P2P_CALLED			ev_MtcUIP2PBeCalled
	/************************************************************************/
	/* 会议被扩展 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_MtcUIP2PExpanded,
#define MTC_UI_P2P_EXPANDED			ev_MtcUIP2PExpanded
	/************************************************************************/
	/* 点对点会议不明原因中止
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_MtcUIP2PDiscard,
#define MTC_UI_P2P_DISCARD			ev_MtcUIP2PDiscard

	/************************************************************************/
	/* 终端正在呼叫
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_MtcUIP2PCalling,
#define MTC_UI_P2P_CALLING			ev_MtcUIP2PCalling

	ev_MtcP2PMsgEnd
};


enum EmMtcMConfMsg
{
	ev_MtcMConfMsgBegin = ev_MtcP2PMsgEnd + 1,
	/************************************************************************/
	/* 多点会议开始 
	wparam = dwIp		对端的IP地址(主机序)
	lparam =			对端的别名*/
	/************************************************************************/
	ev_MtcUIConfStarted,
#define MTC_UI_CONF_STARTED			ev_MtcUIConfStarted
	/************************************************************************/
	/* 发言人改变
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_MtcUISpeakerChanged,
#define MTC_UI_SPEAKER_CHANGED		ev_MtcUISpeakerChanged
	/************************************************************************/
	/*主席改变  
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_MtcUIChairmanChanged,
#define MTC_UI_CHAIRMAN_CHANGED		ev_MtcUIChairmanChanged
	/************************************************************************/
	/*与会终端改变 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_MtcUIConfMtListChanged,
#define MTC_UI_MT_CHANGED			ev_MtcUIConfMtListChanged
	/************************************************************************/
	/*内置mc呼叫终端失败提示 
	wparam = 错误类型
	lparam = 0*/
	/************************************************************************/
	ev_MtcMCIllegalCallInd,
#define MTC_MC_CALL_RESULT          ev_MtcMCIllegalCallInd        
	/************************************************************************/
	/* 主席撤销
	wparam = 0；
	lparam = 0*/
	/************************************************************************/
	ev_MtcUIConfLostChairman,

	/************************************************************************/
	/*有终端提交申请  
	wparam = 申请种类
	ev_ConfApplySpeakReq | ev_ConfApplyChairInInd |ev_ConfApplyChimeInInd
	lparam dwMcuMtId	32比特McuMt复合标识*/
	/************************************************************************/
	ev_MtcUIConfRequsting,
#define MTC_UI_MT_REQUSTING			ev_MtcUIConfRequsting
	/************************************************************************/
	/* 离开会议 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_MtcUIConfLeave,
#define MTC_UI_CONF_LEAVE			ev_MtcUIConfLeave
	/************************************************************************/
	/*会议即将结束
	wparam = dwDelay	还有多少分钟会议结束
	lparam = 0*/
	/************************************************************************/
	ev_MtcUIConfWillEnd,
#define MTC_UI_CONF_BEFORE_END		ev_MtcUIConfWillEnd
	/************************************************************************/
	/* 会议列表已更新 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_MtcUIConfListUpdated,
#define MTC_UI_CONFLIST_UPDATED		ev_MtcUIConfListUpdated
	/************************************************************************/
	/*  会议被取消
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_MtcUIConfCanceled,
#define MTC_UI_CONF_CANCELED		ev_MtcUIConfCanceled
	/************************************************************************/
	/* 会议信息更新
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_MtcUIConfInfoUpdated,
#define MTC_UI_CONFINFO_UPDATED		ev_MtcUIConfInfoUpdated
	/************************************************************************/
	/* 远端视频源切换通知
	wparam dwMcuMtId               32比特的McuMt复合标识
	lparam 0*/
	/************************************************************************/
	ev_MtcUIConfVSrcChange,
#define MTC_UI_CONF_VRSRC			ev_MtcUIConfVSrcChange
	/************************************************************************/
	/* 轮询参数查询返回 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_MtcUIConfPollUpdated,
#define MTC_UI_CONFPOLL_UPDATED		ev_MtcUIConfPollUpdated
	/************************************************************************/
	/*讨论模式变更 
	wparam = BOOL bDiscuss      是否正在讨论中
	lparam = 0*/
	/************************************************************************/
	ev_MtcUIConfDiscussUpdated,
#define MTC_UI_DISCUSS_UPDATED		ev_MtcUIConfDiscussUpdated
	/************************************************************************/
	/* 要求会议密码 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_MtcUIConfReqPwd,
#define MTC_UI_CONFPWD				ev_MtcUIConfReqPwd
	/************************************************************************/
	/*监控终端通知 
	 wparam CAuxMonParam
	 说明	该消息被Send出*/
	/************************************************************************/
	ev_MtcUIConfMonMt,
#define MTC_UI_MONMT				ev_MtcUIConfMonMt
	/************************************************************************/
	/* 视频复合参数已获取通知  
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_MtcUIConfGetVMPParamInd,
#define MTC_UI_VMP					ev_MtcUIConfGetVMPParamInd
	/************************************************************************/
	/*终端状态通知消息  
	wparam &TMtId
	lparam &TMtStatus*/
	/************************************************************************/
	ev_MtcUIConfOtherTerStatusInd,
#define MTC_UI_CONF_MTSTATUS		ev_MtcUIConfOtherTerStatusInd
	/************************************************************************/
	/*强制终端推出 (请退终端失败)
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_MtcUIConfDropTerFailed,
#define MTC_UI_CONF_DROPTERREJECT_IND	ev_MtcUIConfDropTerFailed
	/************************************************************************/
	/* 主席邀请终端失败
		wparam				dwMcuMtId
		lparam				0*/
	/************************************************************************/
	ev_MtcConfInviteFailedInd,
#define MTC_UI_INVITEMT_FAILED		ev_MtcConfInviteFailedInd
	/************************************************************************/
	/* 收到短消息
	wparam dwMcuMtId
	lparam ptstrMsg	收到的消息,以零结尾的字串,位于临时缓冲区
	说明	该消息被送出(SendMessage)*/
	/************************************************************************/
	ev_MtcUIConfRecSMSInd,
#define MTC_UI_SHORT_MSG_RECVED		ev_MtcUIConfRecSMSInd
/************************************************************************/
	/*  请求命令失败 u32 dwEventId
	 wparam = dwEventId		请求命令ID,参见MtEvent.h
	 lparam = 0*/
	/************************************************************************/
	ev_MtcUICmdFailed,
#define MTC_UI_CMD_FAILED		ev_MtcUICmdFailed
	/************************************************************************/
	/* 请求命令成功  
	wparam = dwEventId		请求命令ID,参见MtEvent.h
	lparam = 0*/
	/************************************************************************/
	ev_MtcUICmdSuccess,
#define MTC_UI_CMD_SUCCESS		ev_MtcUICmdSuccess	
	/************************************************************************/
	/* 请求命令超时 u32 dwEventId 
	wparam = dwEventId		请求命令ID,参见MtEvent.h
	lparam = 0*/
	/************************************************************************/
	ev_MtcUICmdTimeOut,
#define MTC_UI_CMD_TIMEOUT		ev_MtcUICmdTimeOut
	/************************************************************************/
	/* 终端标示分配指示
	 wparam McuMtId*/
	/************************************************************************/
	 ev_MtcUIConfLabelAssign,
	 /************************************************************************/
	 /* 语音激励回应
	  wparam =  True 同意   False 
	  lparam = 0*/
	 /************************************************************************/
	ev_MtcUIConfStartVACRsp,
	ev_MtcUIConfStopVACRsp,
	/************************************************************************/
	/*  会议讨论回应
	wparam = True   同意  False  不同意
	lparam = 0*/
	/************************************************************************/
	ev_MtcUIConfStartDiscussRsp,
	ev_MtcUIConfStopDiscussRsp,
	/************************************************************************/
	/* VMP开始回应 
	wparam = True   同意  False  不同意
	lparam = 0*/
	/************************************************************************/
	ev_MtcUIConfStartVMPRsp,
	ev_MtcUIConfStopVMPRsp,
	/************************************************************************/
	/* 设置VMP参数回应
	wparam = True   同意  False  不同意
	lparam = 0*/
	/************************************************************************/
	ev_MtcUISetVMPParamRsp,
	/************************************************************************/
	/* 会议同步消息  用来同步OSD和MTC的状态
	  wparam = 0
	  lparam = 0*/
	/************************************************************************/
	ev_MtcUISynNotify,

	/************************************************************************/
	/* PC 双流编码参数上报
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_MtcPCDualEncodeParamInd,
	/************************************************************************/
	/* PC 双流编码参数码率设置
	wparam = 码率
	lparam = 0*/
	//add by fangdi for 增加双流码率设置
	/************************************************************************/
	ev_MtcPcDualEncodeSetBitRate, 
	/************************************************************************/
	/* PC 双流动态载荷和密钥指示
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_MtcPCDualEncryptInd,
	/************************************************************************/
	/* PC 双流开始编码指示
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_MtcPCDualEncodeStartInd,
	/************************************************************************/
	/* 开始接受双流指示
	wparam = True 开始 / false 停止
	lparam = 0*/
	/************************************************************************/
	ev_MtcRecvDualInd,
	/************************************************************************/
	/* 主叫呼集呼叫指示
	wparam = True 成功 / false 失败
	lparam = 0*/
	/************************************************************************/
    ev_MtcUISiteCallSuccess,
#define MTC_UI_SITE_CALL_SUCCESS    ev_MtcUISiteCallSuccess

    ev_MtcMcCallIncommingInd,
#define MTC_UI_MC_CALL_INCOMMING    ev_MtcMcCallIncommingInd

    ev_MtcMcCapStateInd,
#define MTC_UI_MC_CAPSTATE  ev_MtcMcCapStateInd

    ev_MtcMcDiscussMmbInd,
#define MTC_UI_MC_DISCUSS_MMB  ev_MtcMcDiscussMmbInd

    ev_MtcMcFeccTermInd,
#define MTC_UI_MC_FECC_TERM  ev_MtcMcFeccTermInd

    ev_MtcMcModeCfgInd,
#define MTC_UI_MC_MODE_CFG  ev_MtcMcModeCfgInd

    ev_MtcMcVMPCfgInd,
#define MTC_UI_MC_VMP_CFG  ev_MtcMcVMPCfgInd

    ev_MtcMcSetVMPStyleInd,
#define MTC_UI_MC_SET_VMP_STYLE  ev_MtcMcSetVMPStyleInd

    ev_MtcMcPollInd,
#define MTC_UI_MC_POLL  ev_MtcMcPollInd

	ev_MtcmcViewInd,
#define MTC_UI_MC_VIEW   ev_MtcmcViewInd
    ev_MtcMcMtJoin,
#define MTC_UI_MC_MT_JOIN  ev_MtcMcMtJoin

    ev_MtcMcMtLeave,
#define MTC_UI_MC_MT_LEAVE  ev_MtcMcMtLeave

	/************************************************************************/
	/* FEC能力指示指示
	wparam = m_byFecCapacity 0,1,2
	lparam = 0*/
	/************************************************************************/
	ev_MtcFecCapacity,
#define MTC_UI_FEC_CAPACITY ev_MtcFecCapacity

	MTC_UI_CONF_POLLSCHEME,


	//定制混音
	//	ev_ConfStartMixRsp,
#define MTC_UI_STARTMIXRSP ev_ConfStartMixRsp
	
	//	ev_ConfStopMixRsp,
#define MTC_UI_STOPMIXRSP  ev_ConfStopMixRsp
	
	//	ev_ConfMixParamInd,
#define MTC_UI_SELMTSMIXAUDIOIND ev_ConfMixParamInd

	ev_MtcConfMsgEnd

};



enum emMtcVODMsg
{
	ev_MtcVODMsgBegin = ev_MtcConfMsgEnd + 1,
		
	/************************************************************************/
	/* Vod 正在登陆指示
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_MtcVodLoging,
	/************************************************************************/
	/* Vod 文件列表更新指示
	   wParam = 0
	   lparam = 0*/
	/************************************************************************/
	ev_MtcVODFileListUpdate, 
	/************************************************************************/
	/* Vod 文件信息更新指示
		wParam = 0
		lParam = 0*/
	/************************************************************************/
	ev_MtcVODFileInfoUpdate,
	/************************************************************************/
	/* Vod 文件播放信息指示更新
		wparam = m_dwDuration   播放文件总时长（毫秒）;
		lparam = m_dwPlayTime   已经播放文件的长度（毫秒）*/
	/************************************************************************/
	ev_MtcVODFilePlayInfoUpdate, 
	//vod 登陆和退出的同步消息指示
	ev_MtcVODLoginSys,
	ev_MtcVODLogOutSys,

	/************************************************************************/
	/* Vod 文件详细请求及文件列表请求
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_MtcVodReqing,
	/************************************************************************/
	/* Vod 停止请求信息 ，通知界面置为非等待的状态                                                                    */
	/************************************************************************/
	ev_MtcVodEndReq,
	/************************************************************************/
	/* Vod 状态指示，主要是用来通知主界面是之不可以进行会议操作	
	wparam = True 在vod / False 空闲
	lparam vod的播放状态*/
	/************************************************************************/
	ev_MtcVodStateInd,

	ev_MtcCamControlSourceInd,
	ev_MtcCamNumInd,
	/************************************************************************/
	/* 内置视频源的名称改变                                                                     */
	/************************************************************************/
	ev_MtcCamNameChangeInd,

	ev_MtcCamAutoDualSrcInd,

	ev_MtcVODMsgEnd
};

enum EmMtcCfgMsg
{
	/************************************************************************/
	/*配置信息开始*/
	/************************************************************************/
	ev_emMtcCfgMsgBegin = ev_MtcVODMsgEnd + 1,
	/************************************************************************/
	/*H323 配置信息更新                                                     
	/************************************************************************/
	ev_emUICfgH323Updated,
#define MTC_UI_CFGH323_UPDATED			ev_emUICfgH323Updated

	/* 以太网配置信息 
		参数	wParam  以太网卡配置索引号 
				lparam   0*/
	ev_emUICfgEthnetUpdated,
#define MTC_UI_CFGETHNET_UPDATED		ev_emUICfgEthnetUpdated

	/* 用户设置信息更新*/
	ev_emUICfgUserUpdated, 
#define MTC_UI_CFGUSER_UPDATED			ev_emUICfgUserUpdated

	/* 视频配置信息更新
	参数	wParam	视频编解码器索引号  EmVideoType
			lParam	0*/
	ev_emUICfgVideoUpdated,
#define MTC_UI_CFGVIDEO_UPDATED			ev_emUICfgVideoUpdated

	/* 音频配置信息更新*/
	ev_emUICfgAudioUpdated,
#define MTC_UI_CFGAUDIO_UPDATED			ev_emUICfgAudioUpdated

	/* 发送/接收重传信息更新*/
	ev_emUICfgRetransUpdated,
#define MTC_UI_CFGRETRANS_UPDATED		ev_emUICfgRetransUpdated
	
	/* 前向纠错*/
	ev_emCfgFecTypeUpdated,
#define MTC_UI_CFGFECTYPE_UPDATED     ev_emCfgFecTypeUpdated

	ev_emUICfgSoundPriorityUpdated,
#define MTC_UI_CFGSOUNDPRIORITY_UPDATED ev_emUICfgSoundPriorityUpdated

	/* 图像修饰信息更新*/
	ev_emUICfgImageUpdated,
#define MTC_UI_CFGIMGEQ_UPDATED			ev_emUICfgImageUpdated

	/* 电视机制式配置更新*/
	ev_emUICfgVidDisplayFrmUpdated,
#define MTC_UI_CFGVIDDISPLAYFRM_UPDATED			ev_emUICfgVidDisplayFrmUpdated

	/* OSD信息更新*/
	ev_emUICfgOsdUpdated,
#define MTC_UI_CFGOSD_UPDATED			ev_emUICfgOsdUpdated

	/* 第二路视频输出到VGA信息更新*/
	ev_emUICfgSecondVideoToVGAUpdated,
#define MTC_UI_CFGSECONDVIDEOTOVGA_UPDATED  ev_emUICfgSecondVideoToVGAUpdated
    
	/* SNMP配置信息更新*/
	ev_emUICfgSnmpUpdated,
#define MTC_UI_CFGSNMP_UPDATED			ev_emUICfgSnmpUpdated

	/* AEC配置信息*/
	ev_emUICfgAecUpdated,
#define MTC_UI_CFGAEC_UPDATED			ev_emUICfgAecUpdated

	/* 流媒体配置信息*/
	ev_emUICfgStreamUpdated,
#define MTC_UI_CFGSTREAM_UPDATED		ev_emUICfgStreamUpdated

	/* 摄像头配置*/
	ev_emUICfgCameraUpdated,
#define MTC_UI_CFGCAMERA_UPDATED		ev_emUICfgCameraUpdated

	/* 视频输出配置*/
	ev_emUICfgVidoeOutUpdated,
#define MTC_UI_CFGVIDEOOUT_UPDATED		ev_emUICfgVidoeOutUpdated

	ev_emUICfgVideoSourceUpdated,

	/*默认网关配置*/
	ev_emUICfgGatewayUpdated,
#define MTC_UI_GATEWAY_UPDATED			ev_emUICfgGatewayUpdated
	
	/* 串口配置信息*/
	ev_emUICfgSerialUpdated,
#define MTC_UI_CFGSERIAPORT_UPDATED		ev_emUICfgSerialUpdated

	/* 字幕配置信息*/
	ev_emUICfgCaptionUpdated,
#define MTC_UI_CFGCAPTION_UPDATED		ev_emUICfgCaptionUpdated

	/* E1通道配置信息*/
	ev_emUICfgE1ChanInfoUpdated,
#define MTC_UI_CFGE1CHANINFO_UPDATED	ev_emUICfgE1ChanInfoUpdated

	/* 网络模块信息*/
	ev_emUICfgNetModuleUpdated,
#define MTC_UI_CFGNETMODULE_UPDATED		ev_emUICfgNetModuleUpdated

	/* 路由配置信息*/
	ev_emUICfgRouteInfoUpdated,
#define MTC_UI_CFGROUTEINFO_UPDATED		ev_emUICfgRouteInfoUpdated

	/* PPPoE 配置信息上报*/
	ev_emUICfgPppoeUpdated, 
#define  MTC_UI_CFGPPPOE_UPDATED		ev_emUICfgPppoeUpdated

	/*Qos 配置信息上报 */
	ev_emUICfgQosUpdated,
#define  MTC_UI_CFGQOS_UPDATED			ev_emUICfgQosUpdated

	/*优选协议配置更新 */
	ev_emUICfgPriorUpdated,
#define  MTC_UI_CFGAVPRIOR_UPDATED		ev_emUICfgPriorUpdated

	/*AGC 配置信息 */
	ev_emUICfgAgcUpdated,
#define  MTC_UI_CFGAGC_UPDATED			ev_emUICfgAgcUpdated

	/*输入声音更新*/
	ev_emUICfgInVolUpdated,
#define  MTC_UI_CFGINVOL_UPDATED		ev_emUICfgInVolUpdated

	/*输出声音更新 */
	ev_emUICfgOutVolUpdated,
#define  MTC_UI_CFGOUTVOL_UPDATED		ev_emUICfgOutVolUpdated

	/* 视频制式配置更新 
		WPARAM		视频路 EmVideoType*/
	ev_emUICfgVStandardUpdated,
#define  MTC_UI_CFGVSTANDARD_UPDATED	ev_emUICfgVStandardUpdated

	/*呼叫速率配置更新 */
	ev_emUICfgCallRateUpdated,
#define  MTC_UI_CFGCALLRATE_UPDATED		ev_emUICfgCallRateUpdated

	/*界面语言配置更新 */
	ev_emUICfgLangUpdated,
#define  MTC_UI_CFGLANGUAGE_UPDATED		ev_emUICfgLangUpdated

	/*防火墙配置更新 */
	ev_emUICfgFireWallUpdated,
#define  MTC_UI_CFGFIREWALL_UPDATED		ev_emUICfgFireWallUpdated

	/*Nap 静态影射更新 */
	ev_emUICfgNapMapUpdated,
#define  MTC_UI_CFGNAPMAPADDR_UPDATED	ev_emUICfgNapMapUpdated

	// 摄像头类型能力上报
	ev_emUICfgCamTypeUpdated,
#define MTC_UI_CFGCAMTYPE_UPDATED		ev_emUICfgCamTypeUpdated

	//UDP和TCP开始端口号
	ev_emUICfgCommonBasePortUpdated,
#define  MTC_UI_CFGCOMMONBASEPORT_UPDATED	ev_emUICfgCommonBasePortUpdated
	//自动切换为监控终端的参数设置
	ev_emUICfgMonitorServiceUpdated,
	//是否具有自动切换的能力
	ev_emUICfgIsEnableMonitor,
	//IP地址冲突指示
	ev_emUICfgIPConflict,
	//CPU Mem 使用情况上报
	ev_emUICpuMemStatus,
	//是否发送静态图片状态改变
	ev_emUISendPicStatus,
	//图像测试信息指示 
	//Wparam  本地状态
	//lparam  远端状态
	ev_emRabbonTestInd,

/* 编解码配置信息更新*/
MTC_UI_CFGCODEC_UPDATED,


/* 是否可以配置双流中的画中画*/
MTC_UI_DUALPIP_UPDATED,      

/* 是否可以启动终端监控*/
MTC_UI_CFGMTSWITCH_UPDATED, 


/* 视频格式上报信息*/
MTC_UI_VIDEOFORMATINFO_UPDATED,  

/* 音频功率上报消息*/
MTC_UI_AUDIOPOWER_UPDATED,

MTC_UI_AUDIO_G7221_PARAM_UPDATED,

/* 解码器状态上报*/
MTC_UI_CODECSTATUS_UPDATED,
MTC_UI_REALRESSTATUS_UPDATED,//真实分辨率上报
/* mt从编解码器获取的第一、二路高宽信息上报 */
MTC_UI_DECODE_RESOLUTION_UPDATED,

/* 双流中设置保护提示*/
MTC_UI_DUAL_SETUPDATE,

MTC_UI_CAMERA_STATUS,

    /* 终端版本信息上报 */
    ev_emUITerminalInformationUpdated,
#define MTC_UI_TERMINALINFORMATION_UPDATED  ev_emUITerminalInformationUpdated

    /* PCMT视频源信息上报 */
    ev_emUIPcmtVidSourceUpdated,
#define MTC_UI_PCMTVIDSOURCE_UPDATED  ev_emUIPcmtVidSourceUpdated

    /* 8010c显示VGA或者video参数上报 */
    ev_emUI8010cShowModelParamUpdated,
#define MTC_UI_8010CSHOWMODELPARAM_UPDATED  ev_emUI8010cShowModelParamUpdated

    /* 双流码率比上报 */
    ev_emUIDualCodeRationUpdated,
#define MTC_UI_DUALCODERATION_UPDATED  ev_emUIDualCodeRationUpdated

    /* mt请求mtc发起pc双流时的编码统计信息 */
    ev_emUIMTCEncStatisReq,
#define MTC_UI_MTCENCSTATIS_REQ  ev_emUIMTCEncStatisReq

    /* h261格式的快照会失败，给上层（mtc/界面）发送错误码指示 */
    ev_emUIMTCCodecErrorCodeInd,
#define MTC_UI_MTCCODECERRORCODE_IND  ev_emUIMTCCodecErrorCodeInd

    /* Mic增益控制指示 */
    ev_emUIMicAdjustInd,
#define MTC_UI_MICADJUST_IND  ev_emUIMicAdjustInd

    /* mt设备能力指示 */
    ev_emUIMtEquipmentCapsetInd,
#define MTC_UI_MTEQUIPMENTCAPSET_IND  ev_emUIMtEquipmentCapsetInd

    /* 是否启用DHCP服务指示 */
    ev_emUIMtDHCPIPInd,
#define MTC_UI_MTDHCPIP_IND  ev_emUIMtDHCPIPInd
    
    /* MC工作模式指示 */
    ev_emUIMCModeInd,
#define MTC_UI_MCMode_IND  ev_emUIMCModeInd

    /* DNS服务器IP指示 */
    ev_emUIDNSServerInd,
#define MTC_UI_DNSSERVER_IND  ev_emUIDNSServerInd

	//mc多gk配置更新
	ev_emUICfgPxyIPInd,
#define MTC_UI_CFGPXYIP_IND ev_emUICfgPxyIPInd
    /* 内嵌mc配置指示 */
    ev_emUIInnerMCInd,
#define MTC_UI_INNERMC_IND  ev_emUIInnerMCInd

	
	
	//扬声器音量配置
		ev_emUISpeakerValUPDATED, 
#define  MTC_UI_CFGSpeakerVal_UPDATED		ev_emUISpeakerValUPDATED
		
    /* Ldap服务器IP指示 */
    ev_emUILdapServerUPDATED,
#define MTC_UI_LdapSERVER_UPDATED  ev_emUILdapServerUPDATED
	
	/* 主视频输出到Video信息更新*/
	ev_emUICfgMainVideoToVideoUpdated,
#define MTC_UI_CFGMainVIDEOTOVideo_UPDATED  ev_emUICfgMainVideoToVideoUpdated
	/* 遥控器热键更新*/
	ev_emUICfgRemoteHotKeyUpdated,
#define MTC_UI_CFGRemoteHotKey_UPDATED  ev_emUICfgRemoteHotKeyUpdated
	/* 内置GK防火墙更新*/
	ev_emUICfgInnerGKUpdated,
#define MTC_UI_CFGInnerGK_UPDATED  ev_emUICfgInnerGKUpdated
	
	/* 内置Proxy配置更新*/
	ev_emUICfgInnerProxyUpdated,
#define MTC_UI_CFGInnerProxy_UPDATED ev_emUICfgInnerProxyUpdated
	
	ev_emUICfgSetNetSelectMaskInd,
#define MTC_UI_CFGSETNETSELECTMASK_IND  ev_emUICfgSetNetSelectMaskInd

		/* MTU更新*/
	ev_emUICfgMTUUpdated,
#define MTC_UI_CFGMTU_UPDATED  ev_emUICfgMTUUpdated
	/* 系统时间更新*/
	ev_emUICfgMtTimeUpdated,
#define MTC_UI_CFGMtTime_UPDATED  ev_emUICfgMtTimeUpdated
		/* 自动噪音抑制更新*/
	ev_emUICfgAnsUpdated,
#define MTC_UI_CFGANS_UPDATED  ev_emUICfgAnsUpdated

	//h264是否选择
	ev_emCfgH264FormatSelInd,
#define MTC_UI_CFG_H264SEL_UPDATED ev_emCfgH264FormatSelInd
	/************************************************************************/
	/* Fxo被呼叫
	wparam	0
	lparam  TCHAR *   呼叫人的号码
	*/
	/************************************************************************/
	ev_MtcUIFxoBeCalled,
#define MTC_UI_FXO_CALLED			ev_MtcUIFxoBeCalled
	/************************************************************************/
    /************************************************************************/
	/* Fxo状态更新
	wparam	0
	lparam  EmFxoStatus
	*/
	/************************************************************************/
	ev_MtcUIFxoStatusUpdated,
#define MTC_UI_FXOStatus_Updated			ev_MtcUIFxoStatusUpdated
	/************************************************************************/
	    /************************************************************************/
	/* Fxo超时
	wparam	0
	lparam  EmFxoStatus
	*/
	/************************************************************************/
	ev_MtcUIFxoTimeOut,
#define MTC_UI_FXO_TimeOut			ev_MtcUIFxoTimeOut
	/************************************************************************/
	/* Fxo不再等待
	wparam	0
	lparam  EmFxoStatus
	*/
	/************************************************************************/
	ev_MtcUIFxoNotWaiting,
#define MTC_UI_FXO_NotWaiting			ev_MtcUIFxoNotWaiting
	/************************************************************************/
	
	/* Fxo线路断线
	wparam	0
	lparam  0
	*/
	/************************************************************************/
	ev_MtcUIFxoLineBreak,
#define MTC_UI_FXO_LINE_BREAK			ev_MtcUIFxoLineBreak
	/************************************************************************/

	/************************************************************************/
	/* 编码器cpu异常，终端复位
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_MtcCodecCpuResetInd,
#define MTC_UI_CODEC_CPU_RESET      ev_MtcCodecCpuResetInd  
	

	/************************************************************************/
	/* 编码器cpu异常，终端复位
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_MtcT2IPConflictInd,
#define MTC_UI_T2DEV_IPCONFLICT_IND  ev_MtcT2IPConflictInd

	/************************************************************************/
	/* telnet 密码修改
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_MtcSysTelnetPwdInd,
#define MTC_UI_TELNET_PWD_IND  ev_MtcSysTelnetPwdInd 
	/************************************************************************/
	/* wifi 扫描结果上报
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_MtcWiFiScanBSSInd,
#define MTC_WIFI_SCAN_RESULT_IND  ev_MtcWiFiScanBSSInd

	/************************************************************************/
	/* wifi 配置结果上报
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_MtcWifiCfgInd,
#define MTC_WIFI_CFG_IND ev_MtcWifiCfgInd
	
	/************************************************************************/
	/* wifi 连接状态上报
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_MtcWiFiLinkStatInd,
#define MTC_WIFI_LINKSTATE_IND ev_MtcWiFiLinkStatInd

	/************************************************************************/
	/* wifi ip配置信息
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_MtcCfgWiFiNetInd,
#define MTC_WIFI_NET_IP_IND ev_MtcCfgWiFiNetInd

	/************************************************************************/
	/* 系统运行时间上报
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_MtcSystemTimeInd,
#define MTC_SYSTEM_TIME_IND ev_MtcSystemTimeInd

	/************************************************************************/
	/* 网口工作模式上报
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_MtcEthModeInd,
#define MTC_ETH_MODE_IND ev_MtcEthModeInd
	/* ProxyDomain配置信息
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_MtcFwProxyDomainReqInd,
#define MTC_PROXY_DOMAIN_REQ_IND ev_MtcFwProxyDomainReqInd
	/************************************************************************/
	/* Socket5上报
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_MtcSocket5Ind,
#define MTC_UI_SOCKET5_CFG_IND ev_MtcSocket5Ind
	/************************************************************************/
	/* osd连接服务器,锁定mtc界面
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_MtcUpgradeConnectSrvInd,
#define MTC_LOCKMTC_IND ev_MtcUpgradeConnectSrvInd
	/************************************************************************/
	/* 与升级服务器断链,解锁mtc界面
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_MtcUpgradeDisconnectSrvInd,
#define	MTC_UNLOCKMTC_IND ev_MtcUpgradeDisconnectSrvInd
	/************************************************************************/
	/* 连接到服务器配置信息
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_MtcUpgradeConnectSrvStatusInd,
#define MTC_CONNECT_SRV_IND ev_MtcUpgradeConnectSrvStatusInd

	/************************************************************************/
	/* 断开服务器连接
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_MtcUpgradeDisconnectInd,
#define MTC_UPGRADE_DISCONNECT_IND ev_MtcUpgradeDisconnectInd

	/************************************************************************/
	/* 升级文件列表
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_MtcUpgradeNewVersionInfoListInd,
#define MTC_UPGRADE_FILELIST_IND ev_MtcUpgradeNewVersionInfoListInd

	/************************************************************************/
	/* 终端开始下载文件
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_MtcStartUpgrade,
#define MTC_START_UPGRADE_IND ev_MtcStartUpgrade

	/************************************************************************/
	/* 下载文件信息
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_MtcUpgradeFileDownloadInfoInd,
#define MTC_FILE_DOWNLOAD_INFO_IND ev_MtcUpgradeFileDownloadInfoInd

	/************************************************************************/
	/* 当前文件下载结束
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_MtcUpgradeFileDownloadCompletedInd,
#define MTC_FILE_DOWNLOAD_COMPLETE_IND ev_MtcUpgradeFileDownloadCompletedInd

	//高清音频端口选择
	ev_MtcCfgHDAudioPortInd,
#define  MTC_UI_CFGHDAudioPort_UPDATED 	ev_MtcCfgHDAudioPortInd

	//AAC音频参数设置
	ev_MtcCodecAudAacParamCmd,
#define  MTC_UI_AudAACParam_Cmd     ev_MtcCodecAudAacParamCmd    

	/************************************************************************/
	/*H460 配置信息更新                                                     
	/************************************************************************/
	ev_emUICfgH460Updated,
#define MTC_UI_CFGH460_UPDATED			ev_emUICfgH460Updated
	//////////////////////////////////////////////////////////////////////////
	ev_emUICfgVideoEncodeDecodeModeUpdated,
#define MTC_UI_CFGVIDEOENCODEDECODEMODE_UPDATED		ev_emUICfgVideoEncodeDecodeModeUpdated

	MTC_UI_ETH_NO,

	ev_MtcCfgLogStatusInd,
#define MTC_UI_STARTSTOPLOG			ev_MtcCfgLogStatusInd
	
	ev_MtcCfgLogExportInd,
#define MTC_UI_LOGEXPORT			ev_MtcCfgLogExportInd



	ev_MtE1GroupInd,
#define MTC_UI_E1Group				ev_MtE1GroupInd
	
	ev_MtE1UnitInd,
#define MTC_UI_E1Unit				ev_MtE1UnitInd

	MTC_UI_PASSTHROUGH,

	MTC_UI_CFG_LASTFRAMESHOW,
	MTC_UI_CFG_SHOWAPPLICATION,

	MTC_UI_VIDFRAMERATE_UPDATE,

	MTC_UI_CFG_MCDUALCFG,

	MTC_UI_CFG_SERIALIND,
	MTC_UI_MTCBOXCALLCFG_UPDATE,

	MTC_UI_CFG_SIP_UPDATE,			//新增SIP服务更新
	MTC_UI_CFG_VGA_CTRLSTATUS,		//新增VGA控件是否可编辑消息
	MTC_UI_CFG_VGA_PHASECLOCKIND,
	MTC_UI_CFG_VGA_FILTERSTATUS,
	
	ev_MtCnsInd,
#define MTC_UI_CNS_UPDATE				ev_MtCnsInd

	ev_MtCnsRegRsp,
#define MTC_UI_CNSREG_NOTIFY            ev_MtCnsRegRsp   
	
	/* Mic增益控制指示 */
    ev_emUIAecAdjustInd,
#define MTC_UI_AECADJUST_IND  ev_emUIAecAdjustInd

	ev_MtcUICfgMsgEnd
};











////////////////////////////////////////////////////////////////////////////////
// 集成测试
/* 查询是否已连接终端
   ask	N/A
   rep	BOOL	TRUE已连接,FALSE未连接*/
//#define MTC_INT_IS_CONNECTED		EV_MTC_BGN + 0x100

/* 查询当前连接的终端
   ask	N/A
   rep	CMtcMt	被连接的终端*/
//#define MTC_INT_CONNECTED_MT		EV_MTC_BGN + 0x101

/* 查询登录的用户
   ask	N/A
   rep	CLoginRequest	登录的用户*/
//#define MTC_INT_LOGIN_USER			EV_MTC_BGN + 0x102

/* 是否近端监控中
   ask	N/A
   rep	BOOL	TRUE已监控,FALSE未监控*/
//#define MTC_INT_MONITOR_NEAR		EV_MTC_BGN + 0x103

/* 是否远端监控中
   ask	N/A
   rep	BOOL	TRUE已监控,FALSE未监控*/
//#define MTC_INT_MONITOR_FAR			EV_MTC_BGN + 0x104

/* 当前音频矩阵模式
   ask	N/A
   rep	_TMATRIXSCHEME	当前音频矩阵模式*/
//#define MTC_INT_AMSCHE				EV_MTC_BGN + 0x105

/* 当前视频矩阵模式
   ask	N/A
   rep	_TMATRIXSCHEME	当前视频矩阵模式*/
//#define MTC_INT_VMSCHE				EV_MTC_BGN + 0x106

/* 当前音频输入源
   ask	N/A
   rep	u32	当前音频输入源*/
//#define MTC_INT_ASRC				EV_MTC_BGN + 0x107

/* 当前视频输入源
   ask	N/A
   rep	u32	当前视频输入源*/
//#define MTC_INT_VSRC				EV_MTC_BGN + 0x108

/* 是否近端静音
   ask	N/A
   rep	BOOL	TRUE己静音,FALSE未静音*/
//#define MTC_INT_SPEAKER_MUTE		EV_MTC_BGN + 0x0109

/* 是否近端哑音
   ask	N/A
   rep	BOOL	TRUE己哑音,FALSE未哑音*/
//#define MTC_INT_MIC_MUTE			EV_MTC_BGN + 0x10a

/* 输出音量
   ask	N/A
   rep	u32	输出音量*/
//#define MTC_INT_SPEAKER_VOLUME		EV_MTC_BGN + 0x10b

/* 输入音量
   ask	N/A
   rep	u32	输入音量*/
//#define MTC_INT_MIC_VOLUME			EV_MTC_BGN + 0x10c

/* 遥控器启用状态
   ask	N/A
   rep	BOOL	TRUE已开启,FALSE已禁用*/
//#define MTC_INT_REMOTECTRL			EV_MTC_BGN + 0x10d

/* 地址簿条目总数
   ask	N/A
   rep	u32	条目总数*/
//#define MTC_INT_ENTRY_COUNT			EV_MTC_BGN + 0x10e

/* 地址簿条目组总数
   ask	N/A
   rep	u32	条目数总数*/
//#define MTC_INT_GROUP_COUNT			EV_MTC_BGN + 0x10f

/* 获取条目
   ask	u32		条目索引
   rep	CAddrEntry	条目*/
//#define MTC_INT_ENTRY				EV_MTC_BGN + 0x110

/* 获取条目组
   ask	u32				条目组索引
   rep	CAddrMultiSetEntry	条目组*/
//#define MTC_INT_GROUP				EV_MTC_BGN + 0x111

/* 是否在点对点会议中
   ask	N/A
   rep	BOOL	TRUE在点对点会议中,FALSE不在点对点会议中*/
//#define MTC_INT_P2PCONF				EV_MTC_BGN + 0x112

/* 是否正在呼叫其它终端
   ask	N/A
   rep	BOOL	TRUE正在呼叫,FALSE没在呼叫*/
//#define MTC_INT_CALLING				EV_MTC_BGN + 0x113

/* 当前多点会议列表
   ask	N/A
   rep	u32		会议数目
		_TCONFINFO*	会议数组*/
//#define MTC_INT_CONFLIST			EV_MTC_BGN + 0x114

/* 是否正在等待创建会议回应
   ask	N/A
   rep	BOOL	TRUE正在等待回应,FALSE未等待回应*/
//#define MTC_INT_WAITING_CREATE		EV_MTC_BGN + 0x115

/* 是否正在等待加入申请被批准
   ask	N/A
   rep	BOOL	TRUE正在等待加入申请回应,FALSE未等待回应*/
//#define MTC_INT_WAITING_JOIN		EV_MTC_BGN + 0x116

/* 是否正在多点会议中
   ask	N/A
   rep	BOOL	TRUE正在多点会议中,FALSE未在多点会议中*/
//#define MTC_INT_MCONF				EV_MTC_BGN + 0x117

/* 是否轮询中
   ask	N/A
   rep	BOOL	TRUE正在轮询中,FALSE未在轮询中*/
//#define MTC_INT_POLLING				EV_MTC_BGN + 0x118

/* 与会终端列表
   ask	N/A
   rep	u32	终端数目
		CMtcMt	与会终端数组*/
//#define MTC_INT_MTLIST				EV_MTC_BGN + 0x119

/* 在线与终端列表
   ask	N/A
   rep	u32	终端数目
		CMtcMt	在线终端数组*/
//#define MTC_INT_ONLINE_MTLIST		EV_MTC_BGN + 0x11a

/* 发言终端
   ask	N/A
   rep	CMtcMt	当前发言终端*/
//#define MTC_INT_SPEAKER				EV_MTC_BGN + 0x11b

/* 主席终端
   ask	N/A
   rep	CMtcMt	当前主席终端*/
//#define MTC_INT_CHAIRMAN			EV_MTC_BGN + 0x11c

/* 申请入会的终端列表
   ask	N/A
   rep	u32	终端数目
		CMtcMt	当前申请入会终端数组*/
//#define MTC_INT_REQ_JOIN			EV_MTC_BGN + 0x11d

/* 申请发言的终端列表
   ask	N/A
   rep	u32	终端数目
		CMtcMt	当前申请发言终端数组*/
//#define MTC_INT_REQ_SPEAK			EV_MTC_BGN + 0x11e

/* 申请主席的终端列表
   ask	N/A
   rep	u32	终端数目
		CMtcMt	当前申请主席终端数组*/
//#define MTC_INT_REQ_CHAIRMAN		EV_MTC_BGN + 0x11f

/* 开始近端监控
   ask	N/A
   rep	BOOL	操作结果*/
//#define MTC_INT_STARTMONNEAR		EV_MTC_BGN + 0x120

/* 开始远端监控
   ask	N/A
   rep	BOOL	操作结果*/
//#define MTC_INT_STARTMONFAR			EV_MTC_BGN + 0x121

/* 停止近端监控
   ask	N/A
   rep	BOOL	操作结果*/
#define MTC_INT_STOPMONNEAR			EV_MTC_BGN + 0x122

/* 停止远端监控
   ask	N/A
   rep	BOOL	操作结果*/
//#define MTC_INT_STOPMONFAR			EV_MTC_BGN + 0x123

///* 摄像头云台开始向上运动
//   ask	N/A
//   rep	BOOL	操作结果*/
// #define MTC_INT_CAMERATURNUP		EV_MTC_BGN + 0x124

/* 摄像头云台停止向上运动
   ask	N/A
   rep	BOOL	操作结果*/
// #define MTC_INT_CAMERATURNUPSTOP	EV_MTC_BGN + 0x125

/* 摄像头云台开始向下运动
	ask N/A
	rep	BOOL	操作结果*/
// #define MTC_INT_CAMERATURNDOWN		EV_MTC_BGN + 0x126

/* 摄像头云台停止向下运动
	ask	N/A
	rep	BOOL	操作结果*/
// #define MTC_INT_CAMERATURNDOWNSTOP	EV_MTC_BGN + 0x127

/* 摄像头云台开始向左运动
	ask N/A
	rep	BOOL	操作结果*/
// #define MTC_INT_CAMERATURNLEFT		EV_MTC_BGN + 0x128

/* 摄像头云台停止向左运动
	ask	N/A
	rep	BOOL	操作结果*/
// #define MTC_INT_CAMERATURNLEFTSTOP	EV_MTC_BGN + 0x129

/* 摄像头云台开始向右运动
	ask	N/A
	rep	BOOL	操作结果*/
// #define MTC_INT_CAMERATURNRIGHT		EV_MTC_BGN + 0x12a

/* 摄像头云台停止向右运动
	ask	N/A
	rep	BOOL	操作结果*/
// #define MTC_INT_CAMERATURNRIGHTSTOP	EV_MTC_BGN + 0x12b

/* 摄像头自动调整焦距
	ask	N/A
	rep	BOOL	操作结果*/
// #define MTC_INT_CAMERAADJUSTFOCUSAUTO	EV_MTC_BGN + 0x12c

/* 摄像头开始调近焦距开始
	ask	N/A
	rep	BOOL	操作结果*/
// #define MTC_INT_CAMERAADJUSTFOCUS2NEAR	EV_MTC_BGN + 0x12d

/* 摄像头开始调近焦距停止
	ask	N/A
	rep	BOOL	操作结果*/
// #define MTC_INT_CAMERAADJUSTFOCUS2NEARSTOP	EV_MTC_BGN + 0x12e

/* 摄像头调远焦距开始
	ask	N/A
	rep	BOOL	操作结果*/
// #define MTC_INT_CAMERAADJUSTFOCUS2FAR	EV_MTC_BGN + 0x12f

/* 摄像头调远焦距停止
	ask	N/A
	rep	BOOL	操作结果*/
// #define MTC_INT_CAMERAADJUSTFOCUS2FARSTOP	EV_MTC_BGN + 0x130

/* 摄像头亮度增加开始
	ask	N/A
	rep	BOOL	操作结果*/
// #define MTC_INT_CAMERAINCLUM		EV_MTC_BGN + 0x131

/* 摄像头亮度增加停止
	ask	N/A
	rep	BOOL	操作结果*/
// #define MTC_INT_CAMERAINCLUMSTOP	EV_MTC_BGN + 0x132

/* 摄像头亮度减小开始
	ask	N/A
	rep	BOOL	操作结果*/
// #define MTC_INT_CAMERADECLUM		EV_MTC_BGN + 0x133

/* 摄像头亮度减小停止
	ask	N/A
	rep	BOOL	操作结果*/
// #define MTC_INT_CAMERADECLUMSTOP	EV_MTC_BGN + 0x134

/* 摄像头图像放大开始
	ask	N/A
	rep	BOOL	操作结果*/
// #define MTC_INT_CAMERAZOOMIN		EV_MTC_BGN + 0x135

/* 摄像头图像放大停止
	ask	N/A
	rep	BOOL	操作结果*/
// #define MTC_INT_CAMERAZOOMINSTOP	EV_MTC_BGN + 0x136

/* 摄像头图像缩小开始
	ask	N/A
	rep	BOOL	操作结果*/
// #define MTC_INT_CAMERAZOOMOUT		EV_MTC_BGN + 0x137

/* 摄像头图像缩小停止
	ask	N/A
	rep	BOOL	操作结果*/
// #define MTC_INT_CAMERAZOOMOUTSTOP	EV_MTC_BGN + 0x138

/* 载入缺省矩阵模式
	ask	N/A
	rep	BOOL	操作结果*/
// #define MTC_INT_LOADSCHEDEFAULT		EV_MTC_BGN + 0x139

/* 载入摄像头状态
	ask	u32		状态索引号
	rep	BOOL	操作结果*/
// #define MTC_INT_CAMERALOADSTATUS	EV_MTC_BGN + 0x13a

/* 保存摄像头状态
	ask	u32		状态索引号
	rep	BOOL	操作结果*/
// #define MTC_INT_CAMERASAVESTATUS	EV_MTC_BGN + 0x13b

/* 选择摄像头
	ask	u32		摄像头序号
	rep	BOOL	操作结果*/
// #define MTC_INT_SELECTCAMERA		EV_MTC_BGN + 0x13c

/* 本地远端摄像头切换
	ask	BOOL	是否切换到本地摄像头
	rep	BOOL	操作结果*/
// #define MTC_INT_SWITCHSOURCECAM		EV_MTC_BGN + 0x13d

/* 配置音频端口
	ask	TMATRIXPORT	输入端口
		TMATRIXPORT	输出端口
	rep	BOOL	操作结果*/
// #define MTC_INT_CFGAPORTS			EV_MTC_BGN + 0x13e

/* 配置视频端口
	ask	TMATRIXPORT	输入端口
		TMATRIXPORT	输出端口
	rep	BOOL	操作结果*/
//#define MTC_INT_CFGVPORTS			EV_MTC_BGN + 0x13f

/* 选择音频输入源
	ask	u32		输入源
	rep	BOOL	操作结果*/
// #define MTC_INT_SETAINPUTSRC		EV_MTC_BGN + 0x140

/* 选择视频输入源
	ask	u32		输入源
	rep	BOOL	操作结果*/
// #define MTC_INT_SETVINPUTSRC		EV_MTC_BGN + 0x141

/* 载入矩阵模式
	ask	u32		保存位索引
	rep	BOOL	操作结果*/
// #define MTC_INT_LOADSCHE			EV_MTC_BGN + 0x142

/* 保存矩阵模式
	ask	u32		保存位索引
		TCHAR*	说明字符串
	rep	BOOL	操作结果*/
// #define MTC_INT_SAVESCHE			EV_MTC_BGN + 0x143

/* 调节本地输出音量
	ask	u32		音量
	rep	BOOL	操作结果*/
// #define MTC_INT_ADJLOCALSPKVOL		EV_MTC_BGN + 0x144

/* 调节本地输入音量
	ask	u32		音量
	rep	BOOL	操作结果*/
// #define MTC_INT_ADJLOCALMICVOL		EV_MTC_BGN + 0x145

/* 本地输出静音
	ask	BOOL	是否启用静音
	rep	BOOL	操作结果*/
// #define MTC_INT_MUTELOCALSPK		EV_MTC_BGN + 0x146

/* 本地输入静音
	ask	BOOL	是否启用静音
	rep	BOOL	操作结果*/
// #define MTC_INT_MUTELOCALMIC		EV_MTC_BGN + 0x147

/* 启用回声抑制
	ask	BOOL	是否启用回声抑制
	rep	BOOL	操作结果*/
// #define MTC_INT_ENABLEAEC			EV_MTC_BGN + 0x148

/* 启用遥控器
	ask	BOOL	是否启用遥控器
	rep	BOOL	操作结果*/
// #define MTC_INT_ENABLERCTRL			EV_MTC_BGN + 0x149

/* 修改用户
	ask	CLoginRequest	将要被修改的用户
		BOOL	是否改为管理员用户
	rep	BOOL	操作结果*/
//#define MTC_INT_BOOKMODUSER				EV_MTC_BGN + 0x14a

/* 增加用户
	ask	CLoginRequest	将要被修改的用户
		BOOL	是否增加为管理员用户
	rep	BOOL	操作结果*/
// #define MTC_INT_BOOKADDUSER				EV_MTC_BGN + 0x14b

/* 删除用户
	ask	CLoginRequest	将要被删除的用户
	rep	BOOL	操作结果*/
// #define MTC_INT_BOOKDELUSER				EV_MTC_BGN + 0x14c

/* 增加地址簿条目
	ask	CAddrEntry	增加的条目
	rep	BOOL	操作结果*/
// #define MTC_INT_ADDENTRY			EV_MTC_BGN + 0x14d

/* 修改地址簿条目
	ask	CAddrEntry
	rep	BOOL	操作结果*/
// #define MTC_INT_MODENTRY			EV_MTC_BGN + 0x14e

/* 删除地址簿条目
	ask	u32		将要删除的条目索引
	rep	BOOL	操作结果*/
// #define MTC_INT_DELENTRY			EV_MTC_BGN + 0x14f

/* 增加地址簿组
	ask	CAddrMultiSetEtry	增加的条目组
	rep	BOOL	操作结果*/
// #define MTC_INT_ADDGROUP			EV_MTC_BGN + 0x150

/* 修改地址簿组
	ask	CAddrMultiSetEntry	修改的条目组
	rep	BOOL	操作结果*/
// #define MTC_INT_MODGROUP			EV_MTC_BGN + 0x151

/* 删除地址簿组
	ask	u32		将要删除的条目组索引
	rep	BOOL	操作结果*/
// #define MTC_INT_DELGROUP			EV_MTC_BGN + 0x152

/* P2P按IP呼叫
	ask	u32		被呼叫终端的IP地址
	rep	BOOL	操作结果*/
// #define MTC_INT_CALLBYIP			EV_MTC_BGN + 0x153

/* P2P按E164号码呼叫
	ask	TCHAR	被呼叫终端E164号码	
	rep	BOOL	操作结果*/
// #define MTC_INT_CALLBYNUM			EV_MTC_BGN + 0x154

/* P2P取消呼叫
	ask	N/A
	rep	BOOL	操作结果*/
// #define MTC_INT_CANCELCALLING		EV_MTC_BGN + 0x155

/* P2P结束点对点会议
	ask	N/A
	rep	BOOL	操作结果*/
// #define MTC_INT_ENDP2PCONF			EV_MTC_BGN + 0x156

/* 加入会议
	ask	_TCONFINFO	参加的会议
	rep	BOOL	操作结果*/
// #define MTC_INT_JOINCONF			EV_MTC_BGN + 0x157

/* 取消加入会议
	ask	N/A
	rep	BOOL	操作结果*/
// #define MTC_INT_CANCELJOIN			EV_MTC_BGN + 0x158

/* 申请发言
	ask	N/A
	rep	BOOL	操作结果*/
// #define MTC_INT_REQSPK				EV_MTC_BGN + 0x159

/* 申请主席
	ask	N/A
	rep	BOOL	操作结果*/
// #define MTC_INT_REQCHAIRMAN			EV_MTC_BGN + 0x15a

/* 创建会议
	ask	u32		会议所在的MCU的IP地址
		_TCONFINFO	会议信息
		u32		入会终端数目
		_TERADDR*	入会终端
	rep	BOOL	操作结果*/
//# define MTC_INT_CREATECONF			EV_MTC_BGN + 0x15b

/* 退出会议
	ask	N/A
	rep	BOOL	操作结果*/
// #define MTC_INT_QUITCONF			EV_MTC_BGN + 0x15c

/* 开始轮询
	ask	BOOL	是否广播
		BOOL	是否包括音频
		BOOL	是否包括视频
		u32		轮询时间间隔
		u32		被轮询终端数目
		CMtcMt*	被轮询终端
	rep	BOOL	操作结果*/
// #define MTC_INT_STARTPOLL			EV_MTC_BGN + 0x15d

/* 结束轮询
	ask	N/A
	rep	BOOL	操作结果*/
//#define MTC_INT_ENDPOLL				EV_MTC_BGN + 0x15e

/* 发送短消息
	ask	CMtcMt	消息目的终端
		TCHAR*	消息
	rep	BOOL	操作结果*/
// #define MTC_INT_SENDMSG				EV_MTC_BGN + 0x15f

/* 邀请终端(按IP)
	ask	u32		被邀请终端IP地址
	rep	BOOL	操作结果*/
// #define MTC_INT_INVITEBYIP			EV_MTC_BGN + 0x160

/* 邀请终端(终端结构)
	ask	_TERADDR被邀请终端_TERADDR结构
	rep	BOOL	操作结果*/
// #define MTC_INT_INVITE_MT		    EV_MTC_BGN + 0x161

/* 驱逐终端
	ask	CMtcMt	被驱逐终端
	rep	BOOL	操作结果*/
// #define MTC_INT_DROPMT				EV_MTC_BGN + 0x162

/* 指定发言
	ask	CMtcMt	被指定发言的终端
	rep	BOOL	操作结果*/
// #define MTC_INT_SPECSPK				EV_MTC_BGN + 0x163

/* 指定主席
	ask	CMtcMt	被指定为主席的终端
	rep	BOOL	操作结果*/
// #define MTC_INT_SPECCHAIRMAN		EV_MTC_BGN + 0x164

/* 取消发言
	ask	N/A
	rep	BOOL	操作结果*/
// #define MTC_INT_REVOKESPK			EV_MTC_BGN + 0x165

/* 取消主席
	ask	N/A
	rep	BOOL	操作结果*/
// #define MTC_INT_REVOKECHAIRMAN		EV_MTC_BGN + 0x166

/* 接受入会申请
	ask	CMtcMt	被接受入会的终端
	rep	BOOL	操作结果*/
// #define MTC_INT_ACCEPTJOIN			EV_MTC_BGN + 0x167

/* 拒绝入会申请
	ask	CMtcMt	被拒绝入会的终端
	rep	BOOL	操作结果*/
// #define MTC_INT_REFUSEJOINT			EV_MTC_BGN + 0x168

/* 接受发言申请
	ask	CMtcMt	被接受发言申请的终端
	rep	BOOL	操作结果*/
//#define MTC_INT_ACCEPTSPK			EV_MTC_BGN + 0x169

/* 拒绝发言申请
	ask	CMtcMt	被拒绝发言申请的终端
	rep	BOOL	操作结果*/
// #define MTC_INT_REFUSESPK			EV_MTC_BGN + 0x16a

/* 接受申请主席权限申请
	ask	CMtcMt	被接受主席申请的终端
	rep	BOOL	操作结果*/
// #define MTC_INT_ACCEPTCHAIRMAN		EV_MTC_BGN + 0x16b

/* 拒绝申请主席权限申请
	ask	CMtcMt	被拒绝主席申请的终端
	rep	BOOL	操作结果*/
// #define MTC_INT_REFUSECHAIRMANT		EV_MTC_BGN + 0x16c

/* 静音
	ask	CMtcMt	被操作的终端
		BOOL	是否启用静音
	rep	BOOL	操作结果*/
// #define MTC_INT_SILENCE				EV_MTC_BGN + 0x16d

/* 哑音
	ask	CMtcMt	被操作的终端
		BOOL	是否启用哑音
	rep	BOOL	操作结果*/
// #define MTC_INT_DUMB				EV_MTC_BGN + 0x16e

/* 结束会议
	ask	N/A
	rep	BOOL	操作结果*/
// #define MTC_INT_ENDCONF				EV_MTC_BGN + 0x16f

/* 广播终端
	ask	CMtcMt	被广播的终端
	rep	BOOL	操作结果*/
// #define MTC_INT_BROADCASTMT			EV_MTC_BGN + 0x170

/* 选看终端
	ask	CMtcMt	被选看的终端
	rep	BOOL	操作结果*/
// #define MTC_INT_VIEWMT				EV_MTC_BGN + 0x171

/* 开始讨论
	ask u8		最大参与讨论终端数目
	rep	BOOL	操作结果*/
//#define MTC_INT_START_DISCUSS		EV_MTC_BGN + 0x172

/* 停止讨论
	ask NULL
	rep BOOL	操作结果*/
//#define MTC_INT_STOP_DISCUSS		EV_MTC_BGN + 0x0173

/* 使MtcLib连接到终端业务
	ask	u32		终端业务IP地址
		u16		终端业务端口
		TCHAR*	用户名,以零结尾的字符串
		TCHAR*	密码,以零结尾的字符串
	rep	BOOL	操作结果*/
//#define	MTC_INT_CONNECT				EV_MTC_BGN + 0x0174

/* 使MtcLib断开终端业务
	ask	N/A
	rep	BOOL	操作结果*/
//#define MTC_INT_DISCONNECT			EV_MTC_BGN + 0x0175

/* 获取所有配置信息
	ask N/A
	rep BOOL	操作结果*/
//#define MTC_INT_REQALLCFG			EV_MTC_BGN + 0x0176

/* 配置文件-本地
	ask N/A
	rep BOOL		操作结果
		_TTERCFG	本地配置信息*/
//#define MTC_INT_GETCFGLOCAL			EV_MTC_BGN + 0x0177

/* 配置文件-网络
	ask	N/A
	rep BOOL		操作结果
		_TNETCFG	网络配置信息*/
//#define MTC_INT_GETCFGNET			EV_MTC_BGN + 0x0178

/* 配置文件-呼叫
	ask	N/A
	rep BOOL		操作结果
		_TCALLCFG	呼叫配置信息*/
//#define MTC_INT_GETCFGCALL			EV_MTC_BGN + 0x0179

/* 配置文件-视频编码
	ask	N/A
	rep BOOL		操作结果
		_TVENCPARAM	视频编码配置信息*/
//#define MTC_INT_GETCFGVENC			EV_MTC_BGN + 0x017a

/* 配置文件-视频解码
	ask	N/A
	rep BOOL		操作结果
		_TVDECPARAM	视频解码配置信息*/
//#define MTC_INT_GETCFGVDEC			EV_MTC_BGN + 0x017b

/* 配置文件-音频编码
	ask	N/A
	rep BOOL		操作结果
		_TAENCPARAM	音频编码配置信息*/
//#define MTC_INT_GETCFGAENC			EV_MTC_BGN + 0x017c

/* 配置文件-音频解码
	ask	N/A
	rep BOOL		操作结果
		_TADECPARAM	音频解码配置信息*/
//#define MTC_INT_GETCFGADEC			EV_MTC_BGN + 0x017d

/* 配置文件-发送重传
	ask	N/A
	rep BOOL		操作结果
		_TSENDRTCFG	发送重传配置信息*/
//#define MTC_INT_GETCFGSENDRT		EV_MTC_BGN + 0x017e

/* 配置文件-接收重传
	ask	N/A
	rep BOOL		操作结果
		_TRECVRTCFG	接收重传配置信息*/
//#define MTC_INT_GETCFGRECVRT		EV_MTC_BGN + 0x017f

/* 配置文件-本地
	ask	_TTERCFG	本地配置
	rep	BOOL		操作结果*/
//#define MTC_INT_UPDATECFGLOCAL		EV_MTC_BGN + 0x0180

/* 配置文件-网络
	ask	_TNETCFG	网络配置
	rep	BOOL		操作结果*/
//#define MTC_INT_UPDATECFGNET		EV_MTC_BGN + 0x0181

/* 配置文件-呼叫
	ask	_TCALLCFG	呼叫配置
	rep	BOOL		操作结果*/
//#define MTC_INT_UPDATECFGCALL		EV_MTC_BGN + 0x0182

/* 配置文件-视频编码
	ask	_TVENCPARAM	视频编码配置
	rep	BOOL		操作结果*/
//#define MTC_INT_UPDATECFGVENC		EV_MTC_BGN + 0x0183

/* 配置文件-视频解码
	ask	_TVDECPARAM	视频解码配置
	rep	BOOL		操作结果*/
//#define MTC_INT_UPDATECFGVDEC		EV_MTC_BGN + 0x0184

/* 配置文件-音频编码
	ask	_TAENCPARAM	音频编码配置
	rep	BOOL		操作结果*/
//#define MTC_INT_UPDATECFGAENC		EV_MTC_BGN + 0x0185

/* 配置文件-音频解码
	ask	_TADECPARAM	音频解码配置
	rep	BOOL		操作结果*/
//#define MTC_INT_UPDATECFGADEC		EV_MTC_BGN + 0x0186

/* 配置文件-发送重传
	ask	_TSENDRT	发送重传配置
	rep	BOOL		操作结果*/
//#define MTC_INT_UPDATECFGSENDRT		EV_MTC_BGN + 0x0187

/* 配置文件-接收重传
	ask	_TRECVRT	接收重传配置
	rep	BOOL		操作结果*/
//#define MTC_INT_UPDATECFGRECVRT		EV_MTC_BGN + 0x0188

/* 用户管理-增加
	ask CUserFullInfo	被增加的用户
	rep BOOL			操作结果*/
//#define MTC_INT_ADDUSER				EV_MTC_BGN + 0x0189

/* 用户管理-修改
	ask CUserFullInfo	被修改的用户
	rep BOOL			操作结果*/
//#define MTC_INT_MODUSER				EV_MTC_BGN + 0x018a

/* 用户管理-删除
	ask CUserFullInfo	被删除的用户
	rep BOOL			操作结果*/
//#define MTC_INT_DELUSER				EV_MTC_BGN + 0x018b

/* 用户管理-请求全部用户
	ask N/A
	rep BOOL			操作结果*/
//#define MTC_INT_REQALLUSERS			EV_MTC_BGN + 0x018c

/* 用户管理-获取用户数目
	ask N/A
	rep u32		用户数目*/
//#define MTC_INT_GETUSERCOUNTS		EV_MTC_BGN + 0x018d

/* 用户管理-获取全部用户
	ask N/A
	rep	u32				用户数目
		CUserFullInfo*	用户阵列*/
//#define MTC_INT_GETALLUSERS			EV_MTC_BGN + 0x018e

/* 停止选看
	ask N/A
	rep BOOL			操作结果*/
//#define MTC_INT_STOPVIEWMT			EV_MTC_BGN + 0x018f

/* 第一个地址簿条目
	ask N/A
	rep CAddrEntry		条目*/
//#define MTC_INT_FIRSTENTRY			EV_MTC_BGN + 0x0190

/* 后一个地址簿条目
	ask u32				索引
	rep CAddrEntry		条目*/
//#define MTC_INT_NEXTENTRY			EV_MTC_BGN + 0x0191

/* 第一个地址簿条目
	ask N/A
	rep CAddrEntry		条目*/
//#define MTC_INT_FIRSTGROUP			EV_MTC_BGN + 0x0192

/* 后一个地址簿条目
	ask u32				索引
	rep CAddrEntry		条目*/
//#define MTC_INT_NEXTGROUP			EV_MTC_BGN + 0x0193

/* 会议延迟
	ask u16				延迟时间,以分钟计
	rep N/A*/
//#define MTC_INT_CONFDELAY			EV_MTC_BGN + 0x0194

/* 开始视频复合
	ask TVMPParam		视频复合参数
	rep N/A*/
//#define MTC_INT_STARTVMP			EV_MTC_BGN + 0x0195

/* 停止视频复合
	ask N/A
	rep N/A*/
//#define MTC_INT_STOPVMP				EV_MTC_BGN + 0x0196

/* 更新视频复合参数
	ask TVMPParam		视频复合参数
	rep N/A*/
//#define MTC_INT_UPDATEVMP			EV_MTC_BGN + 0x0197

/* 获取会议ID
	ask N/A
    rep BOOL		操作结果
        char*   会议ID字符串数组指针*/
//#define MTC_INT_GETCURRENTCONF			EV_MTC_BGN + 0x0198

/* 获取当前选看终端
	ask N/A
    rep BOOL		操作结果
        CMtcMt      终端*/
//#define MTC_INT_GETCURRENTCHOICE    	EV_MTC_BGN + 0x0199

//以下为新添20041230
/* 是否存在当前地址条目
	ask CAddrEntry  地址条目
    rep BOOL32		操作结果*/
//#define MTC_INT_ISEXIST_ENTRY    	EV_MTC_BGN + 0x019a

/* 是否存在当前组条目
	ask CAddrMultiSetEntry  组条目
    rep BOOL32		操作结果*/
//#define MTC_INT_ISEXIST_GROUP    	EV_MTC_BGN + 0x019b

/* 是否存在当前用户
	ask CUserFullInfo  用户
    rep BOOL32		操作结果*/
//#define MTC_INT_ISEXIST_USER    	EV_MTC_BGN + 0x019c

/* 是否在双流
	ask N/A  
    rep BOOL32		操作结果*/
//#define MTC_INT_IS_DUAL         	EV_MTC_BGN + 0x019d

/* 获取双流类型
	ask N/A  用户
    rep u8		操作结果*/
//#define MTC_INT_GETDUALTYPE    	    EV_MTC_BGN + 0x019e

/* 是否在插话
	ask N/A  
    rep BOOL32		操作结果*/
//#define MTC_INT_ISCHIME      	    EV_MTC_BGN + 0x019f

/* 获得当前视频源
	ask N/A  
    rep CMtcMt		操作结果*/
//#define MTC_INT_GETVSOURCE      	EV_MTC_BGN + 0x0200


/* 获得配置
	ask N/A  
    rep CMtcMt		操作结果*/
//#define MTC_INT_GETCFGIMG               EV_MTC_BGN + 0x0201
//#define MTC_INT_GETCFGOSD               EV_MTC_BGN + 0x0202
//#define MTC_INT_GETCFGSNMP              EV_MTC_BGN + 0x0203
//#define MTC_INT_GETCFGAEC               EV_MTC_BGN + 0x0204
//#define MTC_INT_GETCFGMATRIX            EV_MTC_BGN + 0x0205
//#define MTC_INT_GETCFGPANEL             EV_MTC_BGN + 0x0206
//#define MTC_INT_GETCFGCAMERAL           EV_MTC_BGN + 0x0207
//#define MTC_INT_GETCFGTVOUT             EV_MTC_BGN + 0x0208
//#define MTC_INT_GETCFGSMALLLOCAL        EV_MTC_BGN + 0x0209
//#define MTC_INT_GETCFGMONIORSW          EV_MTC_BGN + 0x020a
//#define MTC_INT_GETCFGSERIAPORT         EV_MTC_BGN + 0x020b
//#define MTC_INT_GETCFGCAPTION           EV_MTC_BGN + 0x020c

/* 获得当前视频复合状态
	ask N/A  
    rep CMtcMt		操作结果*/
//#define MTC_INT_GETVMPINFO      	    EV_MTC_BGN + 0x020d

/* 获得当前终端状态
	ask N/A  
    rep _TTERSTATUS		操作结果*/
//#define MTC_INT_GETMTSTATUS      	    EV_MTC_BGN + 0x020e

/* 获得当前终端状态
	ask u8 byType  类型  
    rep _TVENCPARAM		操作结果*/
//#define MTC_INT_GETDUALCFG              EV_MTC_BGN + 0x020f

/* 获得当前终端状态
	ask N/A  类型  
    rep u16  个数		操作结果*/
//#define MTC_INT_GETSNAPSHOTCOUNT        EV_MTC_BGN + 0x0210


/* 清空地址簿*/
//#define MTC_INT_UI_CLEAR_ADDRBOOK           EV_MTC_BGN + 0X0212

/* 清空用户 */
//#define MTC_INT_UI_CLEAR_USER               EV_MTC_BGN + 0X0213



/*获取在多点会议中某个终端的别名信息*/
//#define MTC_INT_GETMTINFO					EV_MTC_BGN + 0X0215

/*获取点对点会议中呼叫终端的信息*/
//#define MTC_INT_P2PCALLER						EV_MTC_BGN + 0X0216

/* 获取点对点会议中本地终端的信息*/
//#define MTC_INT_P2PMTME						EV_MTC_BGN + 0X0217

/*
 *	=====================================================================
 *	集成测试消息
 *  =====================================================================
 */
//CConnect
/* 查询是否已连接终端
   ask	N/A
   rep	BOOL	TRUE已连接,FALSE未连接*/
#define MTC_INT_IS_CONNECTED		EV_MTC_BGN + 0x100

/* 查询当前连接的终端
   ask	N/A
   rep	TMtInfo	被连接的终端*/
#define MTC_INT_CONNECTED_MT		EV_MTC_BGN + 0x101

/* 查询登录的用户
   ask	N/A
   rep	CLoginRequest	登录的用户*/
#define MTC_INT_LOGIN_USER			EV_MTC_BGN + 0x102
/* 查询终端的状态
   ask	N/a
   rep   TMtStatus */
#define MTC_INT_MT_STATUS			EV_MTC_BGN + 0x103
/*	查询快照的数目
 *	ask	n/a
	rep u16		快照数目 */
#define  MTC_INT_GETSNAPSHOTCOUNT			EV_MTC_BGN +0x104
//CConfig
/*	查询当前的语言设置
 *	ask n/a
	rep EmLanguage	语言设置 */
#define  MT_INT_CFG_LANGUAGE		EV_MTC_BGN + 0x105
/*	查询当前的以太网配置
 *	ask u8网卡序号
	rep	TEthnetInfo	以太网配置 */
#define  MT_INT_CFG_ETHNET			EV_MTC_BGN + 0x106
/*	查询当前的用户配置
 *	ask	n/a
	rep TUserCfg	用户配置 */
#define  MT_INT_CFG_USER			EV_MTC_BGN + 0x107
/*	查询当前的H323配置
 *	ask n/a
	rep	TH323Cfg	H323配置*/	
#define  MT_INT_CFG_H323			EV_MTC_BGN + 0x108
/*  查询视频配置信息
 *	ask EmVideoType emType
	rep TVideoParam 
 */
#define  MT_INT_CFG_VIDEO			EV_MTC_BGN + 0x109
/*	查询台标配置
 *	ask n/a
	rep	TOsdCfg */
#define  MT_INT_CFG_OSD				EV_MTC_BGN + 0x10a
/*	查询E1配置
 *	ask n/a
	rep TE1Config */
#define  MT_INT_CFG_E1				EV_MTC_BGN + 0x10b
/*	查询当前的串口信息
 *	ask	EmSerialType
	rep TSerialCfg	*/	
#define	 MT_INT_CFG_SERIAL			EV_MTC_BGN + 0x10c
/*	查询Qos配置信息
 *	 ask	n/a
	rep		TIpQoscfg */
#define  MT_INT_CFG_IPQOS			EV_MTC_BGN + 0x10d
/*	查询防火墙的配置信息
 *	ask		n/a
	rep		TEmbedFwNatProxy */
#define  MT_INT_CFG_FIREWALL		EV_MTC_BGN + 0x10e
/*	查询路由配置信息	
 *	ask u8 dwIndex
	rep TRouteCfg */
#define MT_INT_CFG_ROUTE			EV_MTC_BGN + 0x10f
/*	查询PPPoE配置
 *	ask     no
	rep		TPPPOECfg */
#define MT_INT_CFG_PPPOE			EV_MTC_BGN + 0x110
/*	查询snmp配置
 *	ask			no
	rep			TSNMPCfg */
#define MT_INT_CFG_SNMP				EV_MTC_BGN + 0x111
/*	查询静态映射配置信息
 *	ask		no
	rep		TNATMapAddr */
#define MT_INT_CFG_NAPMAP			EV_MTC_BGN + 0x112
/*	查询发送重传配置
 *	ask			no
	rep			TRetransCfg */
#define MT_INT_CFG_RETRANS			EV_MTC_BGN + 0x113
/*	查询是否AEC
 *	ask				no
	rep			TRUE/FASLE */
#define MT_INT_CFG_AEC				EV_MTC_BGN + 0x114
/*	查询是否AGC
 *	ask				no
	rep			TRUE/FASLE */
#define MT_INT_CFG_AGC				EV_MTC_BGN + 0x115
/*	查询优选协议配置
 *	ask				no
	rep				TAVPriorStrategy */
#define MT_INT_CFG_AVPRIOR			EV_MTC_BGN + 0x116
/*	查询输入音量
 *	ask				no
	rep				u8 音量大小 */
#define MT_INT_CFG_INVOL			EV_MTC_BGN + 0x117
/*	查询输出音量
 *	ask				no
	rep				u8 音量大小 */
#define MT_INT_CFG_OUTVOL			EV_MTC_BGN + 0x118
/*	查询图像配置
 *	ask			no
	rep			TImageAdjustParam */
#define MT_INT_CFG_IMAGE			EV_MTC_BGN + 0x119
/*	查询视频制式
 *	ask			EmVideoType
	rep			EmVideoStandard */
#define MT_INT_CFG_VSTAND			EV_MTC_BGN + 0x11a
/*	查询呼叫速率
 *	ask			no
	rep			u32   呼叫速率 */
#define MT_INT_CFG_CALLRATE			EV_MTC_BGN + 0x11b
/*	查询摄像头配置
 *	ask			u8 摄像头索引
	rep			TCameraCfg */
#define MT_INT_CFG_CAMREA			EV_MTC_BGN + 0x11c
/*	查询流媒体配置
 *	ask			no	
	rep			TStreamMedia */
#define	MT_INT_CFG_STREAM			EV_MTC_BGN + 0x11d
/*	查询全部的路由配置信息
 *	ask			no	
	rep			tplarray<TRouteCfg> */
#define MT_INT_CFG_ALLROUTECFG		EV_MTC_BGN + 0x11e

//地址簿 
/* 地址簿条目总数
   ask	N/A
   rep	u32	条目总数*/
#define MTC_INT_ENTRY_COUNT			EV_MTC_BGN + 0x120

/* 地址簿条目组总数
   ask	N/A
   rep	u32	条目数总数*/
#define MTC_INT_GROUP_COUNT			EV_MTC_BGN + 0x121

/* 获取条目
   ask	u32		条目索引
   rep	CAddrEntry	条目*/
#define MTC_INT_ENTRY				EV_MTC_BGN + 0x122

/* 获取条目组
   ask	u32				条目组索引
   rep	CAddrMultiSetEntry	条目组*/
#define MTC_INT_GROUP				EV_MTC_BGN + 0x123

/* 第一个地址簿条目
	ask N/A
	rep CAddrEntry		条目*/
#define MTC_INT_FIRSTENTRY			EV_MTC_BGN + 0x0124

/* 后一个地址簿条目
	ask u32				索引
	rep CAddrEntry		条目*/
#define MTC_INT_NEXTENTRY			EV_MTC_BGN + 0x0125

/* 第一个地址簿条目
	ask N/A
	rep CAddrEntry		条目*/
#define MTC_INT_FIRSTGROUP			EV_MTC_BGN + 0x0126

/* 后一个地址簿条目
	ask u32				索引
	rep CAddrEntry		条目*/
#define MTC_INT_NEXTGROUP			EV_MTC_BGN + 0x0127
/* 是否存在当前地址条目
	ask CAddrEntry  地址条目
    rep BOOL32		操作结果*/
#define MTC_INT_ISEXIST_ENTRY    	EV_MTC_BGN + 0x0128

/* 是否存在当前组条目
	ask CAddrMultiSetEntry  组条目
    rep BOOL32		操作结果*/
#define MTC_INT_ISEXIST_GROUP    	EV_MTC_BGN + 0x0129


//cuser
/* 用户管理-请求全部用户
	ask N/A
	rep BOOL			操作结果*/
#define MTC_INT_REQALLUSERS			EV_MTC_BGN + 0x0130

/* 用户管理-获取用户数目
	ask N/A
	rep u32		用户数目*/
#define MTC_INT_GETUSERCOUNTS		EV_MTC_BGN + 0x0131

/* 用户管理-获取全部用户
	ask N/A
	rep	u32				用户数目
		CUserFullInfo*	用户阵列*/
#define MTC_INT_GETALLUSERS			EV_MTC_BGN + 0x0132
/* 是否存在当前用户
	ask CUserFullInfo  用户
    rep BOOL32		操作结果*/
#define MTC_INT_ISEXIST_USER    	EV_MTC_BGN + 0x0133

//cmutilpointconf
/* 当前多点会议列表
   ask	N/A
   rep	u32		会议数目
		_TCONFINFO*	会议数组*/
#define MTC_INT_CONFLIST			EV_MTC_BGN + 0x140

/* 是否正在等待创建会议回应
   ask	N/A
   rep	BOOL	TRUE正在等待回应,FALSE未等待回应*/
#define MTC_INT_WAITING_CREATE		EV_MTC_BGN + 0x141

/* 是否正在等待加入申请被批准
   ask	N/A
   rep	BOOL	TRUE正在等待加入申请回应,FALSE未等待回应*/
#define MTC_INT_WAITING_JOIN		EV_MTC_BGN + 0x142

/* 是否正在多点会议中
   ask	N/A
   rep	BOOL	TRUE正在多点会议中,FALSE未在多点会议中*/
#define MTC_INT_MCONF				EV_MTC_BGN + 0x143

/* 是否轮询中
   ask	N/A
   rep	BOOL	TRUE正在轮询中,FALSE未在轮询中*/
#define MTC_INT_POLLING				EV_MTC_BGN + 0x144

/* 与会终端列表
   ask	N/A
   rep	u32	终端数目
		CMtcMt	与会终端数组*/
#define MTC_INT_MTLIST				EV_MTC_BGN + 0x145

/* 在线与终端列表
   ask	N/A
   rep	u32	终端数目
		CMtcMt	在线终端数组*/
#define MTC_INT_ONLINE_MTLIST		EV_MTC_BGN + 0x146

/* 发言终端
   ask	N/A
   rep	CMtcMt	当前发言终端*/
#define MTC_INT_SPEAKER				EV_MTC_BGN + 0x147

/* 主席终端
   ask	N/A
   rep	CMtcMt	当前主席终端*/
#define MTC_INT_CHAIRMAN			EV_MTC_BGN + 0x148

/* 申请入会的终端列表
   ask	N/A
   rep	u32	终端数目
		CMtcMt	当前申请入会终端数组*/
#define MTC_INT_REQ_JOIN			EV_MTC_BGN + 0x149

/* 申请发言的终端列表
   ask	N/A
   rep	u32	终端数目
		CMtcMt	当前申请发言终端数组*/
#define MTC_INT_REQ_SPEAK			EV_MTC_BGN + 0x14a

/* 申请主席的终端列表
   ask	N/A
   rep	u32	终端数目
		CMtcMt	当前申请主席终端数组*/
#define MTC_INT_REQ_CHAIRMAN		EV_MTC_BGN + 0x14b
/* 获取会议ID
	ask N/A
    rep BOOL		操作结果
        char*   会议ID字符串数组指针*/
#define MTC_INT_GETCURRENTCONF			EV_MTC_BGN + 0x014c

/* 获取当前选看终端
	ask N/A
    rep BOOL		操作结果
        CMtcMt      终端*/
#define MTC_INT_GETCURRENTCHOICE    	EV_MTC_BGN + 0x014d
/* 是否在插话
	ask N/A  
    rep BOOL32		操作结果*/
#define MTC_INT_ISCHIME      	    EV_MTC_BGN + 0x014e

/* 获得当前视频源
	ask N/A  
    rep CMtcMt		操作结果*/
#define MTC_INT_GETVSOURCE      	EV_MTC_BGN + 0x014f
/* 获得当前视频复合状态
	ask N/A  
    rep CMtcMt		操作结果*/
#define MTC_INT_GETVMPINFO      	    EV_MTC_BGN + 0x0151

/* 获得当前终端状态
	ask N/A  
    rep _TTERSTATUS		操作结果*/
#define MTC_INT_GETMTSTATUS      	    EV_MTC_BGN + 0x0152
/* 当前视频输入源
   ask	N/A
   rep	u32	当前视频输入源*/
#define MTC_INT_VSRC				EV_MTC_BGN + 0x0153
/*获取在多点会议中某个终端的别名信息*/
#define MTC_INT_GETMTINFO					EV_MTC_BGN + 0X0215

//P2pconf
/* 是否在点对点会议中
   ask	N/A
   rep	BOOL	TRUE在点对点会议中,FALSE不在点对点会议中*/
#define MTC_INT_P2PCONF					EV_MTC_BGN + 0x160

/* 是否正在呼叫其它终端
   ask	N/A
   rep	BOOL	TRUE正在呼叫,FALSE没在呼叫*/
#define MTC_INT_CALLING					EV_MTC_BGN + 0x161
/*获取点对点会议中呼叫终端的信息*/
#define MTC_INT_P2PCALLER				EV_MTC_BGN + 0x162

/* 获取点对点会议中本地终端的信息*/
#define MTC_INT_P2PMTME						EV_MTC_BGN + 0x163

//crometectrl
/* 遥控器启用状态
   ask	N/A
   rep	BOOL	TRUE已开启,FALSE已禁用*/
#define MTC_INT_REMOTECTRL			EV_MTC_BGN + 0x169

//cmonintor
/* 是否在双流
	ask N/A  
    rep BOOL32		操作结果*/
#define MTC_INT_IS_DUAL         	EV_MTC_BGN + 0x016a

/* 获取双流类型
	ask N/A  用户
    rep u8		操作结果*/
#define MTC_INT_GETDUALTYPE    	    EV_MTC_BGN + 0x016b
/* 是否近端监控中
   ask	N/A
   rep	BOOL	TRUE已监控,FALSE未监控*/
#define MTC_INT_MONITOR_NEAR		EV_MTC_BGN + 0x16c

/* 是否远端监控中
   ask	N/A
   rep	BOOL	TRUE已监控,FALSE未监控*/
#define MTC_INT_MONITOR_FAR			EV_MTC_BGN + 0x16d

//caudio
/* 是否近端静音
   ask	N/A
   rep	BOOL	TRUE己静音,FALSE未静音*/
#define MTC_INT_SPEAKER_MUTE		EV_MTC_BGN + 0x0170

/* 是否近端哑音
   ask	N/A
   rep	BOOL	TRUE己哑音,FALSE未哑音*/
#define MTC_INT_MIC_MUTE			EV_MTC_BGN + 0x171

/* 输出音量
   ask	N/A
   rep	u32	输出音量*/
#define MTC_INT_SPEAKER_VOLUME		EV_MTC_BGN + 0x172

/* 输入音量
   ask	N/A
   rep	u32	输入音量*/
#define MTC_INT_MIC_VOLUME			EV_MTC_BGN + 0x173

//最后 一条消息
#define MTCLIB_TO_UI_LASTMSG		EV_MTC_BGN + 0x174