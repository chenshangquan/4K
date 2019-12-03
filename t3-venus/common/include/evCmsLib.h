/*****************************************************************************
模块名      : cms控制台
文件名      : evCmsLib.h
相关文件    : 
文件实现功能: 声明消息（供cms的UI部分和lib（umclib 和 cnclib）部分共同使用）
作者        : 俞锦锦
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2011/4/23   1.0         俞锦锦      创建
*******************************************************************************/
#pragma once

#ifndef _EVCMSLIB_20110423_H_
#define _EVCMSLIB_20110423_H_

#include "msgIdDispatch.h"
#include "tpeventcomm.h"

#define NO_CAM_LOGIN

/** @defgroup  cms 消息定义部分
 *  @{
 */

// 网真控制台内部消息  

//#define CMS_MSG_BEGIN		WM_USER + 0x100


//umcLib中消息定义
enum EmUiUmcMsg
{

#define UI_UMC_MSG_BEGIN    CMS_MSG_BEGIN

	/************************************************************************/
	/** 连接  UMS  
	wparam = BOOL  //是否连接成功
	lparam = errorCode*/
	/************************************************************************/
	ev_UIUMSConnected		=	UI_UMC_MSG_BEGIN,
#define	UI_UMS_CONNECTED    ev_UIUMSConnected
	
		
		/************************************************************************/
		/**已断开UMS
		wParam = 0
		lparam = 0*/
		/************************************************************************/
		ev_UIUmsDisconnected,
#define UI_UMS_DISCONNECTED	 ev_UIUmsDisconnected



        /************************************************************************/
		/**该账户已经在另一个地方登录
		wParam = u32_IP
		lparam = 0*/
		/************************************************************************/
		ev_UIUmsGrabLoginNotify,
#define UI_UMS_GRAB_LOGIN_NOTIFY	 ev_UIUmsGrabLoginNotify

		/************************************************************************/
		/**其他IP正在抓包时，禁止登录
		wParam = u32_IP
		lparam = 0*/
		/************************************************************************/
		ev_UICnsRefuseLoginNotify,
#define UI_CNS_REFUSE_LOGIN_NOTIFY	 ev_UICnsRefuseLoginNotify

        /************************************************************************/
		/**UMS的错误信息通知
		wParam = TTPUmsReasonInd
		lparam = 0*/
		/************************************************************************/
		ev_UIUmsReasonInd,
#define UI_UMS_UMSREASON_IND	 ev_UIUmsReasonInd
		

    	/************************************************************************/
		/** ums 命令处理超时
		wParam = 0
		lparam = 0*/
		/************************************************************************/
		ev_UIUmsCmdTimeout,
#define UI_UMS_CMD_TIMEOUT	 ev_UIUmsCmdTimeout


        /************************************************************************/
		/** ums 登录命令处理超时
		wParam = 0
		lparam = 0*/
		/************************************************************************/
		ev_UIUmsLoginTimeout,
#define UI_UMS_LOGIN_TIMEOUT	 ev_UIUmsLoginTimeout
	  
   
    	/************************************************************************/
		/** 会议模板操作结果回复
		wParam = 0
		lparam = 0*/
		/************************************************************************/
		ev_UIUmsOperateConfTemplateRet,
#define UI_UMS_OPERATE_CONFTEMP_RET	 ev_UIUmsOperateConfTemplateRet

		/************************************************************************/
		/** 删除全部模板消息应答
		wParam = 0
		lparam = 0*/
		/************************************************************************/
		ev_UIUmsDelAllConftempRet,
#define UI_UMS_DEL_ALL_CONFTEMP_RET	 ev_UIUmsDelAllConftempRet

		 /************************************************************************/
		 /**	会议模板更新通知
			wParam = confTempID  //发生变更的会议模板ID，删除时为第一个要删除的模板ID
			lparam = 0*/
		/************************************************************************/ 
        ev_UIUmsRefreshConfTemplateList ,
#define UI_UMS_REFRESH_CONFTEMPLATE_LIST  ev_UIUmsRefreshConfTemplateList



    	/************************************************************************/
		/** 用户操作结果回复
		wParam = 0
		lparam = 0*/
		/************************************************************************/
		ev_UIUmsOperateUserRet,
#define UI_UMS_OPERATE_USER_RET	 ev_UIUmsOperateUserRet


		 /************************************************************************/
		 /**	用户更新通知
			wParam = 0
			lparam = 0*/
		/************************************************************************/ 
	    ev_UIUmsRefreshUserList  ,
#define UI_UMS_REFRESH_USER_LIST ev_UIUmsRefreshUserList


        /************************************************************************/
		 /**	更新会议列表
			wParam = 0
			lparam = 0*/
		/************************************************************************/ 
	    ev_UIUmsRefreshConfList   ,
#define UI_UMS_REFRESH_CONF_LIST ev_UIUmsRefreshConfList 



	    /************************************************************************/
		 /**	开启会议回复
			wParam = confTemplateID 
			lparam =  errorCode*/
		/************************************************************************/ 
	    ev_UIUmsStartConfTemplateRsp  ,
#define UI_UMS_START_CONFTEMPLATE_RSP ev_UIUmsStartConfTemplateRsp
        

		/************************************************************************/
		 /**	邀请cns入会回复
			wParam = strCnsInfoE164/alias 
			lparam =  errorCode*/
		/************************************************************************/ 
	    ev_UIUmsInviteCnsRsp  ,
#define UI_UMS_INVITE_CNS_RSP ev_UIUmsInviteCnsRsp


        /************************************************************************/
		 /**设置发言人结果
			wParam = confID 
			lparam =  EmTpApplySpeakerRet*/
		/************************************************************************/ 
	    ev_UIUmsSetSpeakerRsp  ,
#define UI_UMS_SET_SPEAKER_RSP ev_UIUmsSetSpeakerRsp


        /************************************************************************/
		 /**设置哑音结果
			wParam = confID 
			lparam =  bStart*/
		/************************************************************************/ 
	    ev_UIUmsSetMuteCnsRsp  ,
#define UI_UMS_SET_MUTE_CNS_RSP ev_UIUmsSetMuteCnsRsp


        /************************************************************************/
		 /**设置静音结果
			wParam = confID 
			lparam =  bStart*/
		/************************************************************************/ 
	    ev_UIUmsSetQuietCnsRsp  ,
#define UI_UMS_SET_QUIET_CNS_RSP ev_UIUmsSetQuietCnsRsp


        /************************************************************************/
		 /**设置双流结果
			wParam = confID 
			lparam =  bStart*/
		/************************************************************************/ 
	    ev_UIUmsSetDualCnsRsp  ,
#define UI_UMS_SET_DUAL_CNS_RSP ev_UIUmsSetDualCnsRsp


        /************************************************************************/
		 /** 双流源改变通知
			wParam = confID 
			lparam =  cnsID*/
		/************************************************************************/ 
	    ev_UIUmsDualCnsNotify,
#define UI_UMS_DUAL_CNS_NOTIFY ev_UIUmsDualCnsNotify

 
         /************************************************************************/
		 /**	更新发言人通知
			wParam = confID
			lparam = speakerID*/
		/************************************************************************/ 
	    ev_UIUmsChangeSpeakerNotify,
#define UI_UMS_CHANGE_SPEAKER_NOTIFY ev_UIUmsChangeSpeakerNotify


            /************************************************************************/
		 /**	主席
			wParam = confID  下级会议ID
			lparam = */
		/************************************************************************/ 
	    ev_UIUmsChairCnsNotify,
#define UI_UMS_CHAIR_CNS_NOTIFY ev_UIUmsChairCnsNotify



    /************************************************************************/
		 /**	级联会议通知
			wParam = confID  下级会议ID
			lparam = */
		/************************************************************************/ 
	    ev_UIUmsCascadeConfNotify,
#define UI_UMS_CASCADE_CONF_NOTIFY ev_UIUmsCascadeConfNotify



        /************************************************************************/
		 /**	挂断会议回复
			wParam = confID 
			lparam = errorCode*/
		/************************************************************************/ 
	    ev_UIUmsHangupConfRsp ,
#define UI_UMS_HANGUP_CONF_RSP ev_UIUmsHangupConfRsp


		/************************************************************************/
		 /**	更新会议中的会场列表
			wParam = confID
			lparam = 0*/
		/************************************************************************/ 
	    ev_UIUmsRefreshConfCnsList  ,
#define UI_UMS_REFRESH_CONFCNS_LIST ev_UIUmsRefreshConfCnsList

 
		/************************************************************************/
		 /**	更新会议中的会场列表
			wParam = confID
			lparam =  TConfCnsInfo*/
		/************************************************************************/ 
	    ev_UIUmsUpdateConfCnsList  ,
#define UI_UMS_UPDATE_CONFCNS_LIST ev_UIUmsUpdateConfCnsList
 

		/************************************************************************/
		 /**	更新会议 
		 
		/************************************************************************/ 
	    ev_UIUmsUpdateConfInfo  ,
#define UI_UMS_UPDATE_CONFINFO ev_UIUmsUpdateConfInfo


		/************************************************************************/
		 /**	更新会议中的混音列表
			wParam = confID
			lparam = 0*/
		/************************************************************************/ 
	    ev_UIUmsRefreshConfAudMixList  ,
#define UI_UMS_REFRESH_CONFAUDMIX_LIST ev_UIUmsRefreshConfAudMixList

        /************************************************************************/
		 /** 更新会议中的混音列表-- 本地cns所在会议
			wParam = confID
			lparam = 0*/
		/************************************************************************/ 
	    ev_UIUmsRefreshConfAudMixListLocal  ,
#define UI_UMS_REFRESH_CONFAUDMIX_LIST_LOCAL ev_UIUmsRefreshConfAudMixListLocal


		/************************************************************************/
		 /**	更新会议中轮询列表
			wParam = confID
			lparam = 0*/
		/************************************************************************/ 
	    ev_UIUmsRefreshConfPollList  ,
#define UI_UMS_REFRESH_CONFPOLL_LIST ev_UIUmsRefreshConfPollList

 




 	/************************************************************************/
		 /** ums注册服务器信息通知
			wParam = 0
			lparam = 0*/
		/************************************************************************/ 
	    ev_UIUmsRegInfoNotify  ,
#define UI_UMS_REG_INFO_NOTIFY ev_UIUmsRegInfoNotify


  	/************************************************************************/
		 /**	ums注册服务器结果
			wParam = EmTpCnsRegUms:注册返回的错误码
			lparam = 0*/
		/************************************************************************/ 
	    ev_UIUmsRegServRsp  ,
#define UI_UMS_REG_SERV_RSP ev_UIUmsRegServRsp


	/************************************************************************/
		 /**	umsIP
			wParam = EmTpCnsRegUms: 
			lparam = 0*/
		/************************************************************************/ 
	    ev_UIUmsEthnetInfoNotify  ,
#define UI_UMS_ETHNETINFO_NOTIFY ev_UIUmsEthnetInfoNotify

        
	/************************************************************************/
		 /**	ums刷新电视墙列表通知
			wParam =  HandleID
			lparam = 0*/
		/************************************************************************/ 
	    ev_UIUmsRefreshTvwLstNotify  ,
#define UI_UMS_REFRESH_TVW_LIST_NOTITFY ev_UIUmsRefreshTvwLstNotify

        /************************************************************************/
		 /**	播放 电视墙 回复
			wParam =  TRUE：Ack， FALSE：NAck
			lparam =  HandleID/
		/************************************************************************/ 
	    ev_UIUmsPlayHduRsp  ,
#define UI_UMS_PLAY_HDU_RSP ev_UIUmsPlayHduRsp


               /************************************************************************/
		 /**	停止播放 电视墙 回复
			wParam =  TRUE：Ack， FALSE：NAck
			lparam =  HandleID/
		/************************************************************************/ 
	    ev_UIUmsStopPlayHduRsp  ,
#define UI_UMS_STOP_PLAY_HDU_RSP  ev_UIUmsStopPlayHduRsp


               /************************************************************************/
		 /**	 电视墙中是否有码流通知
			wParam =  HandleID 
			lparam =  BOOL/
		/************************************************************************/ 
	    ev_UIUmsHudCodeStreamNotify  ,
#define UI_UMS_HDU_CODE_STREAM_NOTIFY  ev_UIUmsHudCodeStreamNotify
        


        /************************************************************************/
		/**	 系统时间通知
		/************************************************************************/ 
	    ev_GetUmsSystimeNotify  ,
#define UI_GET_UMS_SYSTIME  ev_GetUmsSystimeNotify


        /************************************************************************/
		/**	 会议中断通知
		/************************************************************************/ 
	    ev_HungUp_Conf_Reason,
#define UI_HUNGUP_UMS_CONF_REASON  ev_HungUp_Conf_Reason

        /************************************************************************/
		/**	 电视墙风格通知
		/************************************************************************/ 
        ev_Tvw_HduStyleNotify,
#define UI_UMS_HDUSTYLE_NOTIFY  ev_Tvw_HduStyleNotify

        /************************************************************************/
		/**	 电视墙风格回应
		/************************************************************************/ 
        ev_Tvw_HduStyleRsp,
#define UI_UMS_HDUSTYLE_RSP  ev_Tvw_HduStyleRsp

		/************************************************************************/
		/**	 更新电视墙预案回应
		/************************************************************************/ 
        ev_Tvw_HduStyleUpdateRsp,
#define UI_UMS_HDUSTYLE_UPDATE_RSP  ev_Tvw_HduStyleUpdateRsp

        /************************************************************************/
		/**	 删除电视墙预案应答
		/************************************************************************/ 
//         ev_Tvw_HduStyle_Del_Rsp,
// #define UI_UMS_HDUSTYLE_DEL_RSP  ev_Tvw_HduStyle_Del_Rsp

        /************************************************************************/
		/**	 电视墙风格通知
             To Umc
		/************************************************************************/ 
        ev_Tvw_HduPlanNotify,
#define UI_UMS_HDUPLAN_NOTIFY  ev_Tvw_HduPlanNotify

        /************************************************************************/
		/**	 更新会议模板资源占用情况
             To Umc
		/************************************************************************/ 
        ev_ConfTmp_ResUsedCountNotify,
#define UI_UMS_CONFTMPRESUSEDCOUNT_NOTIFY  ev_ConfTmp_ResUsedCountNotify


		ev_UIUmsEnd,
#define UI_UMS_MSG_END  ev_UIUmsEnd
		
} ;


//cncLib中消息定义
enum EmUiCnsMsg
{

#define UI_CNC_MSG_BEGIN  	UI_UMS_MSG_END + 0x1 

	/************************************************************************/
	/** 连接  CNS 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UICnsConnect	= UI_CNC_MSG_BEGIN,
#define	UI_CNS_CONNECTED  ev_UICnsConnect
	
	/************************************************************************/
	/** 已断开CNS
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UICnsDisconnected,
#define UI_CNS_DISCONNECTED	 ev_UICnsDisconnected

   /************************************************************************/
	/** 登录CNS 接收回复超时
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UICnsLoginTimeOut,
#define UI_CNS_LOGIN_TIMEOUT	 ev_UICnsLoginTimeOut
		 
    
	/************************************************************************/
	/**	更新地址簿
		wParam = 0
		lparam = 0*/
	/************************************************************************/ 
	ev_UIAddrbookChanged,
#define UI_CNS_ADDRBOOK_CHANGED		ev_UIAddrbookChanged

	/************************************************************************/
	/**	地址簿添加条目通知
		wParam = EntryIndex
		lparam = 0*/
	/************************************************************************/ 
	ev_UIAddrbookAddEntry,
#define	UI_CNS_ADDRBOOK_ADDENTRY    ev_UIAddrbookAddEntry

	/************************************************************************/
	/**	地址簿添加条目、修改条目通知
		wParam = EntryIndex
		lparam = 0*/
	/************************************************************************/ 
	ev_UIAddrbookAddGroup,
#define	UI_CNS_ADDRBOOK_ADDGROUP    ev_UIAddrbookAddGroup

	ev_UIAddrbookModify,
#define	UI_CNS_ADDRBOOK_MODIFY      ev_UIAddrbookModify

    /************************************************************************/
	/**	地址簿操作失败通知
		wParam = EntryIndex
		lparam = 0*/
	/************************************************************************/ 
    ev_UIAddrbookOptFailed,
#define	UI_CNS_ADDRBOOKOPT_FAILED      ev_UIAddrbookOptFailed

	/************************************************************************/
	/**	CNS信息
		wParam = 0
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsInfoNotify,
#define	UI_CNS_CNSINFO_NOTIFY       ev_UICnsInfoNotify

	/************************************************************************/
	/**	会议状态
		wParam = 0
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsConfStateNotify,
#define	UI_CNS_CONFSTATE_NOTIFY     ev_UICnsConfStateNotify


	/************************************************************************/
	/**	cns 离开会议
		wParam = 0
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsLeaveConfNotify,
#define	UI_CNS_LEAVECONF_NOTIFY     ev_UICnsLeaveConfNotify


 	/************************************************************************/
	/** 屏状态通知
	wParam = screenID
	lparam = emScreenState  
	/************************************************************************/
	ev_UiScreenStateNotify,
#define UI_CNS_SCREEN_STATE_NOTIFY  ev_UiScreenStateNotify

	/************************************************************************/
	/** 屏名通知
	wParam = screenID
	lparam = cstringCnsName */
	/************************************************************************/
	ev_UiScreenNameNotify,
#define UI_CNS_SCREEN_NAME_NOTIFY   ev_UiScreenNameNotify

 

	/************************************************************************/
	/** 设置选看回复
	wParam = screenID
	lparam = bScucces */
	/************************************************************************/
	ev_UiCnsSelViewRsp,
#define UI_CNS_SEL_VIEW_RSP   ev_UiCnsSelViewRsp


    /************************************************************************/
	/** 取消选看回复
	wParam = screenID
	lparam = bScucces */
	/************************************************************************/
	ev_UiCnsCancleSelViewRsp,
#define UI_CNS_CANCLE_SEL_VIEW_RSP   ev_UiCnsCancleSelViewRsp

    /************************************************************************/
	/** 设置轮询回复
	wParam =  bSucess
	lparam = emReslut */
	/************************************************************************/
	ev_UiCnsStartPollRsp,
#define UI_CNS_START_POLL_RSP   ev_UiCnsStartPollRsp


    /************************************************************************/
	/** 轮询状态通知
	wParam =  bPoll
	lparam = 0 */
	/************************************************************************/
	ev_UiCnsPollStateNty,
#define UI_CNS_POLL_STATE_NOTIFY   ev_UiCnsPollStateNty


        /************************************************************************/
	/** 点对点会议挂断通知
	wParam =  bPoll
	lparam = 0 */
	/************************************************************************/
	evUiCnsHungupP2pNty,
#define UI_CNS_HUNGUP_P2P_NOTIFY   evUiCnsHungupP2pNty

   /************************************************************************/
	/** 设置双流回复
	wParam =  bStart
	lparam = bScucces */
	/************************************************************************/
	ev_UiCnsStartDualRsp,
#define UI_CNS_START_DUAL_RSP   ev_UiCnsStartDualRsp

	/************************************************************************/
	/** 双流状态通知
	wParam =  bStart
	lparam = bScucces */
	/************************************************************************/
	ev_UiCnsDualStateNty,
#define	UI_CNS_DUAL_STATE_NOTIFY   ev_UiCnsDualStateNty

	
    	/************************************************************************/
	/** 双流状态通知
	wParam =  bStart
	lparam = bScucces */
	/************************************************************************/
	ev_UiCnsRecvDualNty,
#define	UI_CNS_RECV_DUAL_NOTIFY   ev_UiCnsRecvDualNty
	
	/************************************************************************/
	/** 双流加密密钥通知
	/************************************************************************/
    ev_UiCnsRecvDualKeyNty,
#define UI_CNS_DUAL_KEY_NOTIFY   ev_UiCnsRecvDualKeyNty

    	/************************************************************************/
	/** 接收双流时异常中断
 
	/************************************************************************/
	ev_UiRecvDualInterruptNty,
#define	UI_RECV_DUAL_INTERRUPT   ev_UiRecvDualInterruptNty

	/************************************************************************/
	/** 发言坐席
	wParam = seatID
	lparam =  0 */
	/************************************************************************/
	ev_UiSpokesSeatNotify,
#define UI_CNS_SPOKES_SEAT_NOTIFY   ev_UiSpokesSeatNotify

	/************************************************************************/
	/* 静音哑音通知  
	wparam = bQuite 	是静音还是哑音.TRUE 静音， FALSE 哑音
	lparam = bOn		是开启还是关闭.开启静音使当前没有音频输出,反之是关闭静音*/
	/************************************************************************/
	ev_UiCnsQuiteMute,
#define UI_CNS_QUITE_MUTE           ev_UiCnsQuiteMute

	/************************************************************************/
	/* 输入音量更新通知  
	wparam = 0 	
	lparam = 0		
	/************************************************************************/
	ev_UiCnsInVolUpdate,
#define	UI_CNS_INVOL_UPDATE         ev_UiCnsInVolUpdate

	/************************************************************************/
	/* 输出量更新通知  
	wparam = 0 	
	lparam = 0		
	/************************************************************************/
	ev_UiCnsOutVolUpdate,
#define	UI_CNS_OUTVOL_UPDATE        ev_UiCnsOutVolUpdate      
    
	/************************************************************************/
	/**	Sip注册信息
		wParam = 0
		lparam = 0*/
	/************************************************************************/ 
	ev_UIRegSipNotify,
#define	UI_CNS_REGSIP_NOTIFY       ev_UIRegSipNotify

	/************************************************************************/
	/**	Sip注册是否成功
		wParam = BOOL
		lparam = 会场名*/
	/************************************************************************/ 
	ev_UIRegSipResultNotify,
#define	UI_CNS_REGRESULT_NOTIFY       ev_UIRegSipResultNotify

	/************************************************************************/
	/**	Sip注册别名重复通知
		wParam = BOOL
		lparam = 会场名*/
	/************************************************************************/ 
	ev_UIRegSipAliasRepeatNotify,
#define	UI_CNS_SIPREG_ALIASREPEAT_NOTIFY       ev_UIRegSipAliasRepeatNotify

    /************************************************************************/
	/**	得到GK注册结果
	 
	/************************************************************************/ 
	ev_UIRegGkResultRsp,
#define	UI_CNS_REG_GK_RSP       ev_UIRegGkResultRsp


     /************************************************************************/
	/**	服务器通知 GK注册信息
	 
	/************************************************************************/ 
	ev_UIRegGkNty,
#define	UI_CNS_REG_GK_NTY       ev_UIRegGkNty


	/**	网络信息通知
		wParam = 0
		lparam = 0*/
	/************************************************************************/
	ev_UICnsEthnetInfoNotify,
#define	UI_CNS_ETHNETINFO_NOTIFY       ev_UICnsEthnetInfoNotify

	/**	双网口网络信息通知
		wParam = 0
		lparam = 0*/
	/************************************************************************/
	ev_UICnCfgWEthnetNty,
#define	UI_CNS_CFGWETHNET_NTY       ev_UICnCfgWEthnetNty

	/**	双网口网络信息通知
		wParam = 0
		lparam = 0*/
	/************************************************************************/
	ev_UICnCfgEthStateNty,
#define	UI_CNS_CFGETHSTATE_NTY       ev_UICnCfgEthStateNty

	/**	双网口网络信息通知
		wParam = 0
		lparam = 0*/
	/************************************************************************/
	ev_UICnCfgWEthnetRsp,
#define	UI_CNS_CFGWETHNET_RSP       ev_UICnCfgWEthnetRsp
	
	/************************************************************************/
	/**	主会场名通知
		wParam = 0
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsMainRoomInd,
#define	UI_CNS_MAINROOM_NOTIFY       ev_UICnsMainRoomInd

	/************************************************************************/
	/**	会场离线通知
		wParam = 会场名
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsRoomOffline,
#define UI_CNS_ROOMOFFLINE           ev_UICnsRoomOffline

    /************************************************************************/
	/**	系统时间回复
		wParam = TTpTime
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsSystimeRsp,
#define UI_CNS_SYSTIME_RSP           ev_UICnsSystimeRsp

	/************************************************************************/
	/**	Cns会场列表
		wParam = 0
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsCnListNty,
#define	UI_CNS_CNLIST_NOTIFY         ev_UICnsCnListNty

	/************************************************************************/
	/**	连接CNS会场通知
		wParam = 0
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsInsConnect,
#define	UI_CNSINS_CONNECTED          ev_UICnsInsConnect
 
	/************************************************************************/
	/**	开启双流码流回复
		wParam =   
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsStartDualCdStrmRsp,
#define	UI_CNSINS_START_DUALCODESTREAM_RSP          ev_UICnsStartDualCdStrmRsp   

	/************************************************************************/
	/**	选看双流码流回复
		wParam =   
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsScrnDisplayDualRsp,
#define	UI_CNS_SCRN_DISPLAY_DUAL_RSP          ev_UICnsScrnDisplayDualRsp  
    

    /************************************************************************/
	/**	取消选看双流码流回复
		wParam =   
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsStopScrnDisplayDualRsp,
#define	UI_CNS_STOP_SCRN_DISPLAY_DUAL_RSP          ev_UICnsStopScrnDisplayDualRsp  
	
   /************************************************************************/
	/**	回显 回复
		wParam =   
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsScrnDisplayLocalRsp,
#define	UI_CNS_SCRN_DISPLAY_LOCAL_RSP          ev_UICnsScrnDisplayLocalRsp  

    /************************************************************************/
	/**取消	回显 回复
		wParam =   
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsStopScrnDisplayLocalRsp,
#define	UI_CNS_STOP_SCRN_DISPLAY_LOCAL_RSP          ev_UICnsStopScrnDisplayLocalRsp  

	/************************************************************************/
	/**双流源掉线通知
		wParam =   
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsRoomDualOfflineNty,
#define UI_CNS_DUALOFFLINE_NOTIFY         ev_UICnsRoomDualOfflineNty

	/************************************************************************/
	/**更新会议模板通知
		wParam =   
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsRefreshConfTemplateList,
#define UI_CNS_REFRESH_CONFTEMPLATE_LIST         ev_UICnsRefreshConfTemplateList

	/************************************************************************/
	/**更新会议模板通知
		wParam =   
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsRefreshGlobalAddrbook,
#define UI_CNS_REFRESH_GLOBAL_ADDRBOOK         ev_UICnsRefreshGlobalAddrbook

	/************************************************************************/
	/**更新会议模板通知
		wParam =  BOOL : 表示是否是sip地址 
		lparam = 0*/
	/************************************************************************/ 
	ev_UICnsRefreshGlobalAddrbookEx,
#define UI_CNS_REFRESH_GLOBAL_ADDRBOOKEX       ev_UICnsRefreshGlobalAddrbookEx

    /************************************************************************/
	/**双流源信息通知
		wParam =   
		lparam = 0*/
	/************************************************************************/ 
    ev_UICnsVgaInfoNty,
#define UI_CNS_VGAINFO_NOTIFY                  ev_UICnsVgaInfoNty

    /************************************************************************/
	/**会议中双流源信息通知
		wParam =   
		lparam = 0*/
	/************************************************************************/ 
    ev_UICnsConfVgaInfoNty,
#define UI_CNS_CONFVGAINFO_NOTIFY              ev_UICnsConfVgaInfoNty

    /************************************************************************/
	/**会议中切换双流源通知
		wParam =   
		lparam = 0*/
	/************************************************************************/ 
    ev_UICnsSelDualInputPortInd,
#define UI_CNS_SELDUALPORT_IND                 ev_UICnsSelDualInputPortInd

	/************************************************************************/
	/**	服务器通知 静态NAT注册信息
	 
	/************************************************************************/ 
	ev_UIRegNatNty,
#define	UI_CNS_REG_NAT_NTY       ev_UIRegNatNty


	/************************************************************************/
	/**  网管配置列表页添加修改网管当前选中数据发送
	wParam = Window*   
	lparam = Type*/
	/************************************************************************/
	ev_UiCnsNetMngSelDataClick,
#define UI_CNS_MSG_NETMNGSELDATA_Click  ev_UiCnsNetMngSelDataClick
	/************************************************************************/
	/**  系统待机页面信息通知
	wParam = Window*   
	lparam = Type*/
	/************************************************************************/
	ev_UiCnsSleepInfoNotify,
#define UI_CNS_SLEEPINFO_NOTIFY  ev_UiCnsSleepInfoNotify

    /************************************************************************/
	/**  中控温度通知
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsSchTempNotify,
#define UI_CNS_SCHTEMP_NTY  ev_UiCnsSchTempNotify
    /************************************************************************/
	/**  中控灯光通知
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsSchLightNotify,
#define UI_CNS_SCHLIGHT_NTY  ev_UiCnsSchLightNotify
    /************************************************************************/
	/**  中控面板状态通知
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsSchStateNotify,
#define UI_CNS_SCHSTATE_NTY  ev_UiCnsSchStateNotify
    /************************************************************************/
	/**  系统电源开关回复
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsSchPowerInd,
#define UI_CNS_SCHPOWER_IND  ev_UiCnsSchPowerInd
     /************************************************************************/
    /**  灯光开关回复
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsSchAllLightInd,
#define UI_CNS_SCHALLLIGHT_IND  ev_UiCnsSchAllLightInd
    /************************************************************************/
	/**  主灯开关回复
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsSchMidLightInd,
#define UI_CNS_SCHMIDLIGHT_IND  ev_UiCnsSchMidLightInd
    /************************************************************************/
	/**  主灯开关回复
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsSchScrLightInd,
#define UI_CNS_SCHSCRLIGHT_IND  ev_UiCnsSchScrLightInd
    /************************************************************************/
	/**  电视机状态通知
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsTVStateNotify,
#define UI_CNS_TVSTATE_NTY  ev_UiCnsTVStateNotify
    /************************************************************************/
	/**  电视机开关回复
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsSeleteTvInd,
#define  UI_CNS_SELETETV_IND ev_UiCnsSeleteTvInd
    /************************************************************************/
	/**  电视机选中状态回复
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsTVPowerModeInd,
#define  UI_CNS_TVPOWERMODE_IND ev_UiCnsTVPowerModeInd
    /************************************************************************/
	/**  文档摄像机状态通知
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsDCamStateNotify,
#define UI_CNS_DCAMSTATE_NTY  ev_UiCnsDCamStateNotify
    /************************************************************************/
	/**  文档摄像机开关回复
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsDCamPowerInd,
#define UI_CNS_DCAMPOWER_IND  ev_UiCnsDCamPowerInd
    /************************************************************************/
	/**  空调状态通知
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsACStateNotify,
#define UI_CNS_ACSTATE_NTY  ev_UiCnsACStateNotify

	/************************************************************************/
	/**  空调选中项回复
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsSelectAirInd,
#define  UI_CNS_SELECTAIR_IND ev_UiCnsSelectAirInd
	/************************************************************************/
	/**  空调全部应用开启后结果回复
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiCnsApplyToAllInd,
#define  UI_CNS_APPLYTOALL_IND ev_UiCnsApplyToAllInd

	/************************************************************************/
	/**  空调电源开关状态通知
	wParam = *   
	lparam = */
	/************************************************************************/
//     ev_UiCnsACPowerStateInd,
// #define UI_CNS_ACPOWERSTATE_IND  ev_UiCnsACPowerStateInd
    /************************************************************************/
	/**  中控待机通知
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiTPadCentreSleepNotify,
#define UI_TPAD_CENTRESLEEP_NTY  ev_UiTPadCentreSleepNotify

    /************************************************************************/
	/**  TPad登录用户通知
	wParam = User*   
	lparam = */
	/************************************************************************/
    ev_UiTPadLoginUserNotify,
#define UI_TPAD_LOGINUSER_NOTIFY  ev_UiTPadLoginUserNotify

    /************************************************************************/
	/**  TPad系统升级通知
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiTPadUpdateSystemCmd,
#define UI_TPAD_UPDATESYS_CMD  ev_UiTPadUpdateSystemCmd

    /************************************************************************/
	/**  UMS的错误信息通知
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiUmsReason_Ind,
#define UI_CNS_UMSREASON_IND   ev_UiUmsReason_Ind

    /************************************************************************/
	/**  cnc进行系统名称修改通知  dyy 2013年8月29日
	wParam = 系统名称   
	lparam = */
	/************************************************************************/
    ev_UiTPadCncSetSysNameNotify,
#define UI_TPAD_SETSYSNAME  ev_UiTPadCncSetSysNameNotify

    /************************************************************************/
	/**  TPad Home键响应
	wParam = *   
	lparam = */
	/************************************************************************/
    ev_UiTPadHomeKeyNotify,
#define UI_TPAD_HOMEKEY_NOTIFY  ev_UiTPadHomeKeyNotify

    /************************************************************************/
	/**  cnc会议状态通知  
	wParam =    
	lparam = */
	/************************************************************************/
    ev_UiTPadConfStateNty,
#define UI_CONFSTATE_NTY  ev_UiTPadConfStateNty

    /************************************************************************/
	/**  开启pc双流的结果 
	wParam =    
	lparam = */
	/************************************************************************/
    ev_UiTPadFileDualResult,
#define UI_FILE_DUAL_RESULT  ev_UiTPadFileDualResult

    /************************************************************************/
	/**  接收pc双流远端地址 
	wParam =    
	lparam = */
	/************************************************************************/
    ev_UiTPadFileDualRcvAddr,
#define UI_FILE_DUAL_RCVADDR  ev_UiTPadFileDualRcvAddr

    /************************************************************************/
	/**  停止pc双流 
	wParam =    
	lparam = */
	/************************************************************************/
    ev_UiTPadStopFileDual,
#define UI_FILE_DUAL_STOP  ev_UiTPadStopFileDual

    /************************************************************************/
	/**  pc双流key的通知 
	wParam =    
	lparam = */
	/************************************************************************/
    ev_UiTPadFileDualkey,
#define UI_FILE_DUAL_KEY  ev_UiTPadFileDualkey

    /************************************************************************/
	/**  远端请求关键帧 
	wParam =    
	lparam = */
	/************************************************************************/
    ev_UiTPadFileKeyFrame,
#define UI_FILE_DUAL_KEYFRAME_REQ  ev_UiTPadFileKeyFrame

	/************************************************************************/
	/** 设置选看电视墙回复
	wParam = screenID
	lparam = bScucces */
	/************************************************************************/
	ev_UiCnsSelTVSViewRsp,
#define UI_CNS_SEL_TVSVIEW_RSP   ev_UiCnsSelTVSViewRsp


    /************************************************************************/
	/** 取消选看电视墙回复
	wParam = screenID
	lparam = bScucces */
	/************************************************************************/
	ev_UiCnsCancleSelTVSViewRsp,
#define UI_CNS_CANCLE_SEL_TVSVIEW_RSP   ev_UiCnsCancleSelTVSViewRsp

   /************************************************************************/
	/**  本端主动开启一个数据会议
	wParam =    
	lparam = */
	/************************************************************************/
    ev_UiSelfStartWBConf,
#define UI_SELFSTARTWBCONFNTY  ev_UiSelfStartWBConf

    /************************************************************************/
	/**  加入数据会议 
	wParam =    
	lparam = */
	/************************************************************************/
    ev_UiJoinWBConfCmd,
#define UI_JOINWBCONF_CMD  ev_UiJoinWBConfCmd
    /************************************************************************/
	/**  网呈会议结束，离开数据会议  
	wParam =    
	lparam = ip */
	/************************************************************************/
    ev_UiLeaveWBConfNty,
#define UI_LEAVEWBCONF_NTY  ev_UiLeaveWBConfNty
    /************************************************************************/
	/**  WB新会议呼进请求Tpad加入 
	wParam =    
	lparam = IP*/
	/************************************************************************/
    ev_UiNewWBConfCallReq,
#define UI_NEWWBCONFCALL_REQ  ev_UiNewWBConfCallReq

    /************************************************************************/
	/**  会议获得会场信息时将会场名发给界面
	wParam =    
	lparam = 会场名 m_achRoomName*/
	/************************************************************************/
    ev_UiConfRoomName,
#define UI_CONFROOMNAME_NTY  ev_UiConfRoomName

    /************************************************************************/
	/**  数据会议状态发给界面
	wParam =    
	lparam = 是否在数据会议中
	/************************************************************************/
    ev_UiWBConfStateNty,
#define UI_WBCONFSTATE_NTY  ev_UiWBConfStateNty
    /************************************************************************/
	/**  WB配置IP发给界面 cns->tpad 
	wParam =    
	lparam = IP*/
	/************************************************************************/
    ev_UiTppSetDataServerInfoNty,
#define UI_TPPSETDATASERVERINFONTY  ev_UiTppSetDataServerInfoNty
    /************************************************************************/
	/**  WB配置IP是否操作成功结果反馈给界面 cns->tpad 
	wParam =    
	lparam = IP*/
	/************************************************************************/
	ev_UiTppSetDataServerInd,
#define	UI_TPPSETDATASERVER_IND  ev_UiTppSetDataServerInd

	/************************************************************************/
	/**  MatrixServer配置IP发给界面 cns->tpad 
	wParam =    
	lparam = IP*/
	/************************************************************************/
	ev_UiTpSetMatrixServerInfoNty,
#define UI_TPSETMATRIXSERVERINFO_NTY ev_UiTpSetMatrixServerInfoNty

	/************************************************************************/
	/** MatrixServer配置IP是否操作成功结果反馈给界面 cns->tpad 
	wParam =    
	lparam = IP*/
	/************************************************************************/
	ev_UiTpSetMatrixServerInfoInd,
#define	UI_TPSETMATRIXSERVERINFO_IND  ev_UiTpSetMatrixServerInfoInd

	/************************************************************************/
	/**  NtpServer配置IP发给界面 cns->tpad 
	wParam =    
	lparam = IP*/
	/************************************************************************/
	ev_UitppSetNtpServerInfoNty,
#define UI_TPSETNTPSERVERINFO_NTY ev_UitppSetNtpServerInfoNty

	/************************************************************************/
	/** NtpServer配置IP是否操作成功结果反馈给界面 cns->tpad 
	wParam =    
	lparam = IP*/
	/************************************************************************/
	ev_UitppSetNtpServerInfoInd,
#define	UI_TPSETNTPSERVERINFO_IND  ev_UitppSetNtpServerInfoInd

    /************************************************************************/
	/**  本端开启视频会议
	wParam =    
	lparam = 
	/************************************************************************/
    ev_UiSelfStartConfCmdNty,
#define UI_SELFSTARTCONF_CMD  ev_UiSelfStartConfCmdNty
    /************************************************************************/
	/**  修改白板服务器ip
	wParam =  bool 是否成功  
	lparam = IP*/
	/************************************************************************/
    ev_UiSetWBServerIpNty,
#define UI_SETWBSERVERIP_NTY  ev_UiSetWBServerIpNty
    /************************************************************************/
	/**  点对点会议数据会议名消息 cns->tpad 
	wParam =    
	lparam = IP*/
	/************************************************************************/
    ev_UiTppSetDataConfNameNty,
#define UI_TPPSETDATACONFNAMENTY  ev_UiTppSetDataConfNameNty
    /************************************************************************/
	/**  升级T300通知 cns->tpad 
	wParam =    
	lparam = IP*/
	/************************************************************************/
    ev_UiTppUpDateT300Nty,
#define UI_TPPUPDATET300NTY  ev_UiTppUpDateT300Nty

    ev_UICncEnd,
#define	UI_CNC_MSG_END   ev_UICncEnd

};



//cms 逻辑单元间的消息定义
enum EmUiCmsMsg
{  

#define UI_CMS_MSG_BEGIN  UI_CNC_MSG_END + 0x1

    	/************************************************************************/
		/** 出现异常
		wParam = 异常错误码
		lparam = 0*/
		/************************************************************************/
	ev_UiCMsError = UI_CMS_MSG_BEGIN,
#define UI_CMS_ERROR  ev_UiCMsError


			
    /************************************************************************/
	/**  
	wParam =  errorcode
	lparam = 0*/
	/************************************************************************/
	ev_UiConnectRsp,
#define UI_CONNECT_RSP  ev_UiConnectRsp


	/************************************************************************/
	/**  单击会场列表中的cns条目
	wParam =  cnsInfo
	lparam = 所单击的item相对于屏幕的rect*/
	/************************************************************************/
	ev_UiCnsConfItemClick,
#define UI_CONF_CNS_ITEM_CLICK  ev_UiCnsConfItemClick
   

   /************************************************************************/
	/**  单击会议模板列表中的 条目
	wParam =  wConfTempID
	lparam = 所单击的item相对于屏幕的rect*/
	/************************************************************************/
    ev_UiCnsConfTempItemClick,
#define UI_CONF_TEMP_ITEM_CLICK  ev_UiCnsConfTempItemClick

   /************************************************************************/
	/**  单击地址簿列表中的条目呼叫
	wParam =  Args_ClickItemInfo
	lparam = 0*/
	/************************************************************************/
	ev_UiCmsAddrItemCallClick,
#define	UI_ADDR_ITEM_CALL_CLICK  ev_UiCmsAddrItemCallClick



       /************************************************************************/
	/**  更新时间通知,由titlebar通知 时间设置界面
	wParam =  SYSTEMTIME
	lparam = 0*/
	/************************************************************************/
	ev_UiCmsUpdateTime,
#define	UI_CMS_UPDATE_SYSTEM_TIME  ev_UiCmsUpdateTime


      /************************************************************************/
	/**  设置时间通知    由时间设置界面通知titlebar
	wParam =  SYSTEMTIME
	lparam = 0*/
	/************************************************************************/
	ev_UiCmsModifySystemTime,
#define	UI_CMS_MODIFY_SYSTEM_TIME  ev_UiCmsModifySystemTime

  /************************************************************************/
	/**  mainmenu 点击了 Toolbar
	wParam =    
	lparam = 0*/
	/************************************************************************/
	ev_UiCmsMainmenuClickToolBtn,
#define	UI_CMS_CLICK_TOOL_BTN  ev_UiCmsMainmenuClickToolBtn

    
   /************************************************************************/
	/**  calling timer 到时间 主会场未上线
	wParam =    
	lparam = 0*/
	/************************************************************************/
	ev_UiCmsCallingTimeOut,
#define	UI_CMS_CALLING_TIME_OUT  ev_UiCmsCallingTimeOut


     /************************************************************************/
	/**  显示呼叫dlg
	wParam =    
	lparam = 0*/
	/************************************************************************/
	ev_UiCmsShowCallingDlg,
#define	UI_UMS_SHOW_CALLING_DLG  ev_UiCmsShowCallingDlg


     /************************************************************************/
	/**  隐藏呼叫dlg
	wParam =    
	lparam = 0*/
	/************************************************************************/
	ev_UiCmsHideCallingDlg, 
#define	UI_UMS_HIDE_CALLING_DLG  ev_UiCmsHideCallingDlg

	/************************************************************************/
	/**  显示告警dlg
	wParam =    
	lparam = 0*/
	/************************************************************************/
	ev_UiCmsShowAlarmDlg,
#define UI_CMS_SHOW_ALARM_DLG  ev_UiCmsShowAlarmDlg 



   ev_UiCmsSwitchIme,
#define WM_SWITCH_IME  ev_UiCmsSwitchIme
 
   ev_UiCmsKeyboardClose,
#define WM_KEYBOARD_CLOSE  ev_UiCmsKeyboardClose

   /************************************************************************/
	/**  登录ok
	wParam =    
	lparam = 0*/
	/************************************************************************/
    ev_UiCmsLoginOk,
#define WM_CMS_UI_LOGIN_OK  ev_UiCmsLoginOk

   /************************************************************************/
	/**  自动登录CNS会场
	wParam =    
	lparam = 0*/
	/************************************************************************/	
	ev_UiCmsAutoLogCnsIns,
#define UI_CMS_AUTOLOG_CNSINS   ev_UiCmsAutoLogCnsIns


   /************************************************************************/
	/** 网络断开
	wParam =    
	lparam = 0*/
	/************************************************************************/
   ev_UiCmsNetDisconnect,
#define WM_NET_DISCONNECT  ev_UiCmsNetDisconnect

   /************************************************************************/
	/**  IP 冲突
	wParam =    
	lparam = 0*/
	/************************************************************************/
   ev_UiCmsIpConflict,
#define WM_NET_IPCONFLICT  ev_UiCmsIpConflict

   /************************************************************************/
	/**  更新confmenu
	wParam =    
	lparam = 0*/
	/************************************************************************/
   ev_UiCmsIUpdateConfMenu,
#define WM_CMS_UPDATE_CONFMENU  ev_UiCmsIUpdateConfMenu


    /************************************************************************/
	/**  点击了显示视频解码按钮
	wParam =   1 表示是要最大化显示
	lparam = 0*/
	/************************************************************************/
   ev_UiCmsShowVideo,
#define WM_CMS_SHOWVIDEO  ev_UiCmsShowVideo


    /************************************************************************/
	/**  更新mainMenu
	wParam =    
	lparam = 0*/
	/************************************************************************/
    ev_UiCmsIUpdateMainMenu,
#define WM_CMS_UPDATE_CMAINMENU  ev_UiCmsIUpdateMainMenu


    /************************************************************************/
	/**  更新mainMenu
	wParam =    
	lparam = 0*/
	/************************************************************************/
	ev_UiCmsHideVedio,
#define WM_CMS_HIDE_VEDIO  ev_UiCmsHideVedio

	/************************************************************************/
	/**  开始等待更新注册信息
	wParam = Window*   
	lparam = Type*/
	/************************************************************************/
	ev_UiCncBeginWaitingRefresh,
#define UI_CNC_BEGINWAITING_REFRESH  ev_UiCncBeginWaitingRefresh

	/************************************************************************/
	/**  结束等待更新注册信息
	wParam = 0 
	lparam = 0*/
	/************************************************************************/
	ev_UiCncEndWaitingRefresh,
#define UI_CNC_ENDWAITING_REFRESH  ev_UiCncEndWaitingRefresh

	/************************************************************************/
	/**  通知导入地址簿时剩余的条目数量
	wParam = u32 
	lparam = 0*/
	/************************************************************************/
	ev_UiCncLoadAddrNumNty,
#define UI_CNC_LOADADDRNUM_NTY  ev_UiCncLoadAddrNumNty

	/************************************************************************/
	/**  等待更新注册信息超时
	wParam = 0 
	lparam = 0*/
	/************************************************************************/
	ev_UiCncWaitingRefreshOverTime,
#define UI_CNC_WAITINGREFRESH_OVERTIME  ev_UiCncWaitingRefreshOverTime


	/************************************************************************/
	/**  隐藏窗口的消息 
	wParam = 0 
	lparam = 0*/
	/************************************************************************/
	ev_UiCncHideWnd,
#define UI_CNC_HIDE_WND  ev_UiCncHideWnd

	/************************************************************************/
	/**  呼叫服务器配置码流格式选择的消息 (callserverlogic2modelogic)
	wParam = TTPCallSerFormat 
	lparam = 0*/
	/************************************************************************/
	ev_UiCncCallSvr2ModeChooseModeNty,
#define UI_CNC_CALLSVR2MODECHOOSE_MODE_NTY  ev_UiCncCallSvr2ModeChooseModeNty

	/************************************************************************/
	/**  呼叫服务器配置码流格式选择的消息 (modelogic2callserverlogic)
	wParam = TTPCallSerFormat 
	lparam = 0*/
	/************************************************************************/
	ev_UiCncModeChoose2CallSvrModeNty,
#define UI_CNC_MODECHOOSE2CALLSVR_MODE_NTY  ev_UiCncModeChoose2CallSvrModeNty

	/************************************************************************/
	/**  呼叫服务器配置码流格式选择的消息 (callserverlogic2showmodelogic)
	wParam = TTPCallSerFormat 
	lparam = 0*/
	/************************************************************************/
	ev_UiCncCallSvr2ShowModeChooseModeNty,
#define UI_CNC_CALLSVR2SHOWMODECHOOSE_MODE_NTY  ev_UiCncCallSvr2ShowModeChooseModeNty

	/************************************************************************/
	/**  呼叫服务器配置码流格式选择的消息 (showmodelogic2callserverlogic)
	wParam = TTPCallSerFormat 
	lparam = 0*/
	/************************************************************************/
	ev_UiCncShowModeChoose2CallSvrModeNty,
#define UI_CNC_SHOWMODECHOOSE2CALLSVR_MODE_NTY  ev_UiCncShowModeChoose2CallSvrModeNty

	/************************************************************************/
	/**  呼叫服务器配置音频格式选择的消息 (callserverlogic2Audiomodelogic)
	wParam = EmTpAudioFormat
	lparam = 0*/
	/************************************************************************/
	ev_UiCncCallSvr2AudioModeNty,
#define UI_CNC_CALLSVR2AUDIO_MODE_NTY  ev_UiCncCallSvr2AudioModeNty

	/************************************************************************/
	/**  呼叫服务器配置音频格式选择的消息 (Audiomodelogic2callserverlogic)
	wParam = EmTpAudioFormat 
	lparam = 0*/
	/************************************************************************/
	ev_UiCncAudioMode2CallSvrNty,
#define UI_CNC_AUDIO2CALLSVR_MODE_NTY  ev_UiCncAudioMode2CallSvrNty
				
	/************************************************************************/
	/**  台标上传进度提醒
	wParam =  进度值  
	lparam = 0*/
	/************************************************************************/	
	em_CNC_CONFSIGNPROGRESS,
#define WM_CNC_FTPCONFSIGNPROGRESS  em_CNC_CONFSIGNPROGRESS		   
	
    /************************************************************************/
	/**  开启或关闭画中画操作反馈 
	wParam =    
	lparam = */
	/************************************************************************/
    ev_UiViewLocalPIPInd,
#define UI_CNS_VIEWLOCALPIP_IND  ev_UiViewLocalPIPInd
	
    /************************************************************************/
	/**  画中画开启或关闭状态通知 
	wParam =    
	lparam = */
	/************************************************************************/
    ev_UiViewLocalPIPNty,
#define UI_CNS_VIEWLOCALPIP_NTY  ev_UiViewLocalPIPNty

	ev_UiCmsMsgEnd,
#define UI_CMS_MSG_END  ev_UiCmsMsgEnd
};


enum EmTPadMsg
{
    #define EV_TPAD_MSG_BEGIN  CMS_MSG_BEGIN + 900

    ev_TPadMsg_Begin = EV_TPAD_MSG_BEGIN,

    /************************************************************************/
	/** 通知Tpad登录信息
	/************************************************************************/
    ev_TPadLoginInfo_Nty,

    /************************************************************************/
	/** cnc修改系统名称 dyy
	/************************************************************************/
    ev_TPadSetSysName_Nty,

    /************************************************************************/
	/** 通知Tpad Home键响应
	/************************************************************************/
    ev_TPadHomeKey_Nty,

	/************************************************************************/
	/** 通知Tpad响应主动跟cns断链
	/************************************************************************/
    ev_TpadDisconnectCns_Nty,

    /************************************************************************/
	/** 通知cnc 是否加入白板会议  
	/************************************************************************/
    ev_WBConfStateNty,
    /************************************************************************/
	/** 通知打开中控  dyy 2015-5-26
	/************************************************************************/
    ev_OpenCenterCtrl_Nty,

    ev_TPadMsg_End,
};


//umstool中消息定义
enum EmUiUmstoolMsg
{
#define UI_UMSTOOL_MSG_BEGIN  UMSTOOL_MSG_BEGIN + 0x1

    	/************************************************************************/
		/** 出现异常
		wParam = 异常错误码
		lparam = 0*/
		/************************************************************************/
	ev_UiUMSTOOLError = UI_UMSTOOL_MSG_BEGIN,
#define UI_UMSTOOL_ERROR  ev_UiUMSTOOLError

	/************************************************************************/
	/**  ums版本信息刷新
	wParam = Window*   
	lparam = Type*/
	/************************************************************************/
	ev_UiUmstoolUmsVerNty,
#define UI_UMSTOOL_MSG_UMSVER_NTY  ev_UiUmstoolUmsVerNty

	/************************************************************************/
	/**  ums授权数目
	wParam = Window*   
	lparam = Type*/
	/************************************************************************/
	ev_UiUmstoolAuthCountNty,
#define UI_UMSTOOL_MSG_AUTHCOUNT_NTY  ev_UiUmstoolAuthCountNty

	/************************************************************************/
	/**  ums会议数目
	wParam = Window*   
	lparam = Type*/
	/************************************************************************/
	ev_UiUmstoolConfCountNty,
#define UI_UMSTOOL_MSG_CONFCOUNT_NTY  ev_UiUmstoolConfCountNty

	/************************************************************************/
	/**  ums系统信息
	wParam = Window*   
	lparam = Type*/
	/************************************************************************/
	ev_UiUmstoolSysInfoNty,
#define UI_UMSTOOL_MSG_SYSINFO_NTY  ev_UiUmstoolSysInfoNty

	/************************************************************************/
	/**  ums电视墙使用情况信息
	wParam = Window*   
	lparam = Type*/
	/************************************************************************/
	ev_UiUmstoolTvwUsedNty,
#define UI_UMSTOOL_MSG_TVWUSED_NTY  ev_UiUmstoolTvwUsedNty

	/************************************************************************/
	/**  单板数据通知
	wParam = TTPBrdInfo 单板信息*   
	lparam = 无*/
	/************************************************************************/
	ev_UiUmstoolRefreshBoardNty,
#define UI_UMSTOOL_MSG_REFRESHBOARD_NTY  ev_UiUmstoolRefreshBoardNty

	/************************************************************************/
	/**  修改单板数据通知
	wParam = TTPBrdCfg   单板配置*   
	lparam = 无*/
	/************************************************************************/
	ev_UiUmstoolModifyBoardNty,
#define UI_UMSTOOL_MSG_MODIFYBOARD_NTY  ev_UiUmstoolModifyBoardNty

	/************************************************************************/
	/**  删除单板数据通知
	wParam = TTPBrdCfg   单板配置*   
	lparam = 无*/
	/************************************************************************/
	ev_UiUmstoolDeleteBoardNty,
#define UI_UMSTOOL_MSG_DELETEBOARD_NTY  ev_UiUmstoolDeleteBoardNty

	/************************************************************************/
	/**  添加单板数据通知(修改共用)
	wParam = TTPBrdCfg   单板配置*   
	lparam = 无*/
	/************************************************************************/
	ev_UiUmstoolOptBoardNty,
#define UI_UMSTOOL_MSG_OPTBOARD_NTY  ev_UiUmstoolOptBoardNty

	/************************************************************************/
	/**  单板操作数据结果回应（添加 删除 修改）
	wParam = TTPBrdCfg   单板配置*   
	lparam = EmTpBoardRet 失败原因*/
	/************************************************************************/
	ev_UiUmstoolOptBoardRsp,
#define UI_UMSTOOL_MSG_OPTBOARD_RSP  ev_UiUmstoolOptBoardRsp

	/************************************************************************/
	/**  添加单板模式数据通知(修改 删除共用  其中删除后数据为空)
	wParam = TTPBrdMdlInfo   单板模式信息*   
	lparam = 无*/
	/************************************************************************/
	ev_UiUmstoolOptBoardModeNty,
#define UI_UMSTOOL_MSG_OPTBOARDMODE_NTY  ev_UiUmstoolOptBoardModeNty

	/************************************************************************/
	/**  单板模式操作数据结果回应（添加 删除 修改）
	wParam = TTPBrdMdlInfo   单板配置*   
	lparam = EmTpBoardRet 失败原因*/
	/************************************************************************/
	ev_UiUmstoolOptBoardModeRsp,
#define UI_UMSTOOL_MSG_OPTBOARDMODE_RSP  ev_UiUmstoolOptBoardModeRsp

	/************************************************************************/
	/**  单板占用情况通知   包括 混音器、画面合成、码流适配占用情况
	wParam = Window*   
	lparam = Type*/
	/************************************************************************/
	ev_UiUmstoolBoardUsed,
#define UI_UMSTOOL_MSG_BOARDUSED_NTY  ev_UiUmstoolBoardUsed


	/************************************************************************/
	/**  单板页面添加修改单板当前选中数据发送
	wParam = Window*   
	lparam = Type*/
	/************************************************************************/
	ev_UiUmstoolBoardSelDataClick,
#define UI_UMSTOOL_MSG_BOARDSELDATA_Click  ev_UiUmstoolBoardSelDataClick

	/************************************************************************/
	/**  电视墙单板页面添加修改单板当前选中数据发送
	wParam = Window*   
	lparam = Type*/
	/************************************************************************/
	ev_UiUmstoolTvwBoardSelDataClick,
#define UI_UMSTOOL_MSG_TVWBOARDSELDATA_Click  ev_UiUmstoolTvwBoardSelDataClick

	/************************************************************************/
	/**  电视墙风格数据保存发送
	wParam = TTvwStyleInfo m_tSelTvwStyleInfo     当前选中对应的电视墙通道数据    更新数据列表使用*   
	lparam = Type*/
	/************************************************************************/
	ev_UiUmstoolTvwStyleSave,
#define UI_UMSTOOL_MSG_TVWSTYLESAVE  ev_UiUmstoolTvwStyleSave

	/************************************************************************/
	/**  电视墙风格通道点击数据发送
	wParam = Window*   
	lparam = Type*/
	/************************************************************************/
	ev_UiUmstoolTvwStyleSelDataClick,
#define UI_UMSTOOL_MSG_TVWSTYLESELDATA_Click  ev_UiUmstoolTvwStyleSelDataClick

	/************************************************************************/
	/**  电视墙单板数据通知
	wParam = TTPBrdInfo 单板信息*   
	lparam = 无*/
	/************************************************************************/
	ev_UiUmstoolRefreshTvwBoardNty,
#define UI_UMSTOOL_MSG_REFRESHTVWBOARD_NTY  ev_UiUmstoolRefreshTvwBoardNty

	/************************************************************************/
	/**  添加电视墙单板数据通知(修改共用)
	wParam = TTPBrdCfg   单板配置*   
	lparam = 无*/
	/************************************************************************/
	ev_UiUmstoolOptTvwBoardNty,
#define UI_UMSTOOL_MSG_OPTTVWBOARD_NTY  ev_UiUmstoolOptTvwBoardNty

	/************************************************************************/
	/**  电视墙单板操作数据结果回应（添加 修改 删除）
	wParam = TTPBrdCfg   单板配置*   
	lparam = EmTpBoardRet 失败原因*/
	/************************************************************************/
	ev_UiUmstoolOptTvwBoardRsp,
#define UI_UMSTOOL_MSG_OPTTVWBOARD_RSP  ev_UiUmstoolOptTvwBoardRsp

	/************************************************************************/
	/**  电视墙单板操作数据通知（删除）
	wParam = TTPBrdCfg   单板配置*   
	lparam = EmTpBoardRet 失败原因*/
	/************************************************************************/
	ev_UiUmstoolDelTvwBoardNty,
#define UI_UMSTOOL_MSG_DELTVWBOARD_NTY  ev_UiUmstoolDelTvwBoardNty

	/************************************************************************/
	/**  添加电视墙单板模式通知(修改共用)
	wParam = TTPBrdCfg   单板配置*   
	lparam = 无*/
	/************************************************************************/
	ev_UiUmstoolOptTvwBoardModeNty,
#define UI_UMSTOOL_MSG_OPTTVWBOARDMODE_NTY  ev_UiUmstoolOptTvwBoardModeNty

	/************************************************************************/
	/**  电视墙单板操作模式结果回应（添加 修改 删除）
	wParam = TTPBrdCfg   单板配置*   
	lparam = EmTpBoardRet 失败原因*/
	/************************************************************************/
	ev_UiUmstoolOptTvwBoardModeRsp,
#define UI_UMSTOOL_MSG_OPTTVWBOARDMODE_RSP  ev_UiUmstoolOptTvwBoardModeRsp

	/************************************************************************/
	/**  电视墙单板操作模式通知（删除）
	wParam = TTPBrdCfg   单板配置*   
	lparam = EmTpBoardRet 失败原因*/
	/************************************************************************/
	ev_UiUmstoolDelTvwBoardModeNty,
#define UI_UMSTOOL_MSG_DELTVWBOARDMODE_NTY  ev_UiUmstoolDelTvwBoardModeNty

	/************************************************************************/
	/**  添加网管指示
	wParam = EmModifyNMServerRet 是否成功
	lparam = 无*/
	/************************************************************************/
	ev_UIUmstoolAddNetmngRsp,
#define UI_UMSTOOL_ADD_NETMNG_RSP  ev_UIUmstoolAddNetmngRsp

	/************************************************************************/
	/**  删除网管指示
	wParam = EmModifyNMServerRet 是否成功
	lparam = 无*/
	/************************************************************************/
	ev_UIUmstoolDelNetmngRsp,
#define UI_UMSTOOL_DEL_NETMNG_RSP  ev_UIUmstoolDelNetmngRsp

	/************************************************************************/
	/**  网管信息通知
	wParam = NULL
	lparam = 无*/
	/************************************************************************/
	ev_UIUmstoolNetmngNty,
#define UI_UMSTOOL_NETMNG_NTY  ev_UIUmstoolNetmngNty

	/************************************************************************/
	/**  修改网管指示
	wParam = EmModifyNMServerRet 是否成功
	lparam = 无*/
	/************************************************************************/
	ev_UIUmstoolModifyNetmngRsp,
#define UI_UMSTOOL_MODIFY_NETMNG_RSP  ev_UIUmstoolModifyNetmngRsp

	/************************************************************************/
	/**  单板页面添加修改网管当前选中数据发送
	wParam = Window*   
	lparam = Type*/
	/************************************************************************/
	ev_UiUmstoolNetMngSelDataClick,
#define UI_UMSTOOL_MSG_NETMNGSELDATA_Click  ev_UiUmstoolNetMngSelDataClick
	
        /************************************************************************/
		/**	 重启电视墙板卡回应
		wParam = TTPBrdPos  板子位置信息*   
		lparam = EmModifyHduRet 操作返回结果*/
		/************************************************************************/ 
        ev_Tvw_RebootRsp,
#define UI_UMSTOOL_MSG_REBOOTTVWBOARD_RSP  ev_Tvw_RebootRsp

        /************************************************************************/
		/**	 板子升级回应
		wParam = BOOL  升级成功失败*   
		/************************************************************************/ 
        ev_Board_UpgradeRsp,
#define UI_UMSTOOL_MSG_BOARDUPGRADE_RSP  ev_Board_UpgradeRsp

        /************************************************************************/
		/**	 发送通知到单板 升级单板消息
		wParam = CString  文件名*   
		/************************************************************************/ 
        em_UMSTOOL_BOARDBEGINUPGRADE,
#define UI_UMSTOOL_BOARDBEGINUPGRADE  em_UMSTOOL_BOARDBEGINUPGRADE

	/************************************************************************/
	/**  录像机页面添加修改网管当前选中数据发送
	wParam = Window*   
	lparam = Type*/
	/************************************************************************/
	ev_UiUmstoolVTRSelDataClick,
#define UI_UMSTOOL_MSG_VTRSELDATA_Click  ev_UiUmstoolVTRSelDataClick

	/************************************************************************/
	/**  添加录像机回应
	wParam = EmModifyVTRRet 是否成功
	lparam = 无*/
	/************************************************************************/
	ev_UIUmstoolAddVTRRsp,
#define UI_UMSTOOL_ADD_VTR_RSP  ev_UIUmstoolAddVTRRsp

	/************************************************************************/
	/**  删除录像机回应
	wParam = EmModifyVTRRet 是否成功
	lparam = 无*/
	/************************************************************************/
	ev_UIUmstoolDelVTRRsp,
#define UI_UMSTOOL_DEL_VTR_RSP  ev_UIUmstoolDelVTRRsp

	/************************************************************************/
	/**  录像机信息通知
	wParam = NULL
	lparam = 无*/
	/************************************************************************/
	ev_UIUmstoolVTRNty,
#define UI_UMSTOOL_VTR_NTY  ev_UIUmstoolVTRNty

	/************************************************************************/
	/**  录像机注册状态通知
	wParam = NULL
	lparam = 无*/
	/************************************************************************/
	ev_UIUmstoolVTRRegStateNty,
#define UI_UMSTOOL_VTR_REG_STATE_NTY  ev_UIUmstoolVTRRegStateNty

	/************************************************************************/
	/**  修改录像机回应
	wParam = EmModifyVTRRet 是否成功
	lparam = 无*/
	/************************************************************************/
	ev_UIUmstoolModifyVTRRsp,
#define UI_UMSTOOL_MODIFY_VTR_RSP  ev_UIUmstoolModifyVTRRsp
	
	/************************************************************************/
	/**  会议模板导出回应
	wParam = void 
	lparam = 无*/
	/************************************************************************/
	ev_UIUmstoolExpTemplateRsp,
#define UI_UMSTOOL_EXPTEMPLATE_RSP  ev_UIUmstoolExpTemplateRsp

	/************************************************************************/
	/**  SIP注册服务器数据通知
	wParam = NULL
	lparam = 无*/
	/************************************************************************/
	ev_UIUmstoolRegNty,
#define UI_UMSTOOL_REG_NTY  ev_UIUmstoolRegNty


	/************************************************************************/
	/**  GK注册服务器数据通知
	wParam = NULL
	lparam = 无*/
	/************************************************************************/
	ev_UIUmstoolGkNty,
#define UI_UMSTOOL_GK_NTY  ev_UIUmstoolGkNty

        /************************************************************************/
		/**	 发送通知到单板 升级单板消息
		wParam = 层 槽*   
		/************************************************************************/ 
        em_UMSTOOL_TVWBOARDBEGINUPGRADE,
#define UI_UMSTOOL_TVWBOARDBEGINUPGRADE  em_UMSTOOL_TVWBOARDBEGINUPGRADE

        /************************************************************************/
		/**	 电视墙板子升级回应
		wParam = EmUpdateHduRet  升级成功失败*   
		/************************************************************************/ 
        ev_TvwBoard_UpgradeRsp,
#define UI_UMSTOOL_MSG_TVWBOARDUPGRADE_RSP  ev_TvwBoard_UpgradeRsp

		/************************************************************************/
		/**  录播服务器基本信息通知
		wParam = NULL
		lparam = 无*/
		/************************************************************************/
		ev_UIUmstoolRecBaseInfoNty,
#define UI_UMSTOOL_REC_BASE_INFO_NTY  ev_UIUmstoolRecBaseInfoNty

		/************************************************************************/
		/**  录播服务器文件列表通知
		wParam = NULL
		lparam = 无*/
		/************************************************************************/
		ev_UIUmstoolRecFileListInfoNty,
#define UI_UMSTOOL_REC_FILE_LIST_INFO_NTY  ev_UIUmstoolRecFileListInfoNty

		/************************************************************************/
		/**  录播服务器修改文件回复
		wParam = NULL
		lparam = BOOL 是否成功*/
		/************************************************************************/
		ev_UIUmstoolRecMdyFileRsp,
#define UI_UMSTOOL_REC_MDY_FILE_RSP  ev_UIUmstoolRecMdyFileRsp

		/************************************************************************/
		/**  会议录制信息通知
		wParam = TConfRecInfo* 会议录制信息
		lparam = BOOL 是否成功*/
		/************************************************************************/
		ev_UIUmstoolRecConfRecInfoNty,
#define UI_UMSTOOL_REC_CONF_REC_INFO_NTY  ev_UIUmstoolRecConfRecInfoNty

		/************************************************************************/
		/**  开始录制回复
		wParam = NULL 
		lparam = EmRecStartRecorderRes 结果*/
		/************************************************************************/
		ev_UIUmstoolRecStartRecordRsp,
#define UI_UMSTOOL_REC_START_CONF_RSP  ev_UIUmstoolRecStartRecordRsp

		/************************************************************************/
		/**  暂停录制回复
		wParam = NULL 
		lparam = EmRecStartRecorderRes 结果*/
		/************************************************************************/
		ev_UIUmstoolRecPauseRecordRsp,
#define UI_UMSTOOL_REC_PAUSE_CONF_RSP  ev_UIUmstoolRecPauseRecordRsp

		/************************************************************************/
		/**  继续录制回复
		wParam = NULL 
		lparam = EmRecStartRecorderRes 结果*/
		/************************************************************************/
		ev_UIUmstoolRecResumeRecordRsp,
#define UI_UMSTOOL_REC_RESUME_CONF_RSP  ev_UIUmstoolRecResumeRecordRsp

		/************************************************************************/
		/**  结束录制回复
		wParam = NULL 
		lparam = EmRecStartRecorderRes 结果*/
		/************************************************************************/
		ev_UIUmstoolRecStopRecordRsp,
#define UI_UMSTOOL_REC_STOP_CONF_RSP  ev_UIUmstoolRecStopRecordRsp

		/************************************************************************/
		/**  开始放像回复
		wParam = NULL 
		lparam = EmRecStartRecorderRes 结果*/
		/************************************************************************/
		ev_UIUmstoolRecStartPlayRsp,
#define UI_UMSTOOL_START_PLAY_RSP  ev_UIUmstoolRecStartPlayRsp

		/************************************************************************/
		/**  暂停放像回复
		wParam = NULL 
		lparam = EmRecStartRecorderRes 结果*/
		/************************************************************************/
		ev_UIUmstoolRecPausePlayRsp,
#define UI_UMSTOOL_PAUSE_PLAY_RSP  ev_UIUmstoolRecPausePlayRsp

		/************************************************************************/
		/**  继续放像回复
		wParam = NULL 
		lparam = EmRecStartRecorderRes 结果*/
		/************************************************************************/
		ev_UIUmstoolRecResumePlayRsp,
#define UI_UMSTOOL_RESUME_PLAY_RSP  ev_UIUmstoolRecResumePlayRsp

		/************************************************************************/
		/**  结束放像回复
		wParam = NULL 
		lparam = EmRecStartRecorderRes 结果*/
		/************************************************************************/
		ev_UIUmstoolRecStopPlayRsp,
#define UI_UMSTOOL_STOP_PLAY_RSP  ev_UIUmstoolRecStopPlayRsp

		/************************************************************************/
		/**  会议放像通知
		wParam = NULL 
		lparam = NULL*/
		/************************************************************************/
		ev_UIUmstoolRecConfPlayInfoNty,
#define UI_UMSTOOL_REC_CONF_PLAY_INFO_NTY  ev_UIUmstoolRecConfPlayInfoNty

		/************************************************************************/
		/**  地址簿OPT显示状态改变通知
		wParam = bShow 显示状态 
		lparam = NULL*/
		/************************************************************************/
		ev_UIUmstoolAddreditChangeStateNty,
#define MSG_UMSTOOL_ADDREDITOPT_CHANGESTATE_NTY  ev_UIUmstoolAddreditChangeStateNty
		
		/************************************************************************/
		/**  录播服务器删除文件回复
		wParam = NULL
		lparam = BOOL 是否成功*/
		/************************************************************************/
		ev_UIUmstoolRecDelFileRsp,
#define UI_UMSTOOL_REC_DEL_FILE_RSP  ev_UIUmstoolRecDelFileRsp

		/************************************************************************/
		/**  Record筛选通知
		wParam = emShowState 筛选状态
		lparam = NULL*/
		/************************************************************************/
		ev_UIUmstoolShowOptNty,
#define UI_UMSTOOL_SHOWOPT_NTY  ev_UIUmstoolShowOptNty

		/************************************************************************/
		/**  Recordep筛选通知
		wParam = emShowState 筛选状态
		lparam = NULL*/
		/************************************************************************/
		ev_UIUmstoolShowOptEpNty,
#define UI_UMSTOOL_SHOWOPT_EP_NTY  ev_UIUmstoolShowOptEpNty

		/************************************************************************/
		/**  授权导出回应
		wParam = BOOL32 是否成功
		lparam = s8* 绝对路径+文件名*/
		/************************************************************************/
		ev_UIUmstoolExpAuthRsp,
#define UI_UMSTOOL_EXPAUTH_RSP  ev_UIUmstoolExpAuthRsp

		/************************************************************************/
		/**  会场格式回应
		wParam = TTPRecMtFormat 会场格式信息
		lparam = NULL*/
		/************************************************************************/
		ev_UIUmstoolRecMtFormatRsp,
#define UI_UMSTOOL_REC_MT_FORMAT_RSP  ev_UIUmstoolRecMtFormatRsp

};


//cnstool消息定义
enum EmUiCnstoolMsg
{
#define UI_CNSTOOL_MSG_BEGIN  CNSTOOL_MSG_BEGIN + 0x1

    	/************************************************************************/
		/** 出现异常
		wParam = 异常错误码
		lparam = 0*/
		/************************************************************************/
	ev_UiCNSTOOLError = UI_CNSTOOL_MSG_BEGIN,
#define UI_CNSTOOL_ERROR  ev_UiCNSTOOLError

	/************************************************************************/
	/**  请求TPadIP列表回复消息
	wParam =  &TTPTPadList
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolTPadIPRsp,
#define UI_CNSTOOL_MSG_TPadIP_RSP  ev_UiCnstoolTPadIPRsp

	/************************************************************************/
	/**  接收TPadIP列表通知消息
	wParam =  &TTPTPadList
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolTPadIPNty,
#define UI_CNSTOOL_MSG_TPadIP_NTY  ev_UiCnstoolTPadIPNty

	/************************************************************************/
	/**  接收cpu/内存通知消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolSYSInfoNty,
#define UI_CNSTOOL_MSG_CPURAM_NTY  ev_UiCnstoolSYSInfoNty

	/************************************************************************/
	/**  接收会议信息通知消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolConfInfoNty,
#define UI_CNSTOOL_MSG_CONF_NTY  ev_UiCnstoolConfInfoNty

	/************************************************************************/
	/**  接收音频端口设置通知消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolAudPortInd,
#define UI_CNSTOOL_MSG_AudPort_NTY  ev_UiCnstoolAudPortInd

	/************************************************************************/
	/**  接收非桌面麦克风设置通知消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnSetDesktopMicInfoNty,
#define UI_CNSTOOL_SETDESKTOPMIC_NTY  ev_UiCnSetDesktopMicInfoNty
	
	/************************************************************************/
	/**  接收非桌面麦克风设置回复消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnSetDesktopMicInfoInd,
#define UI_CNSTOOL_SETDESKTOPMIC_IND  ev_UiCnSetDesktopMicInfoInd

	/************************************************************************/
	/**  接收GANNON10的设置消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UitppSetMic10InfoInd,
#define UI_CNSTOOL_SETMIC10INFO_IND  ev_UitppSetMic10InfoInd
	
	/************************************************************************/
	/**  接收默认音频端口消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolDftAudPortInd,
#define UI_CNSTOOL_MSG_DftAudPort_NTY  ev_UiCnstoolDftAudPortInd
	
	/************************************************************************/
	/**  接收上下行速率通知消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolUpDownstreamInd,
#define UI_CNSTOOL_MSG_UpDownstream_NTY  ev_UiCnstoolUpDownstreamInd

	/************************************************************************/
	/**  接收丢包消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolLostPacketRsp,
#define UI_CNSTOOL_MSG_LostPacket_Rsp  ev_UiCnstoolLostPacketRsp

	/************************************************************************/
	/**  接收诊断测试消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolAVDiagInd,
#define UI_CNSTOOL_MSG_AVDiag_IND  ev_UiCnstoolAVDiagInd

	/************************************************************************/
	/**  添加网管指示
	wParam = EmModifyNMServerRet 是否成功
	lparam = 无*/
	/************************************************************************/
	ev_UICnstoolAddNetmngInd,
#define UI_CNSTOOL_ADD_NETMNG_IND  ev_UICnstoolAddNetmngInd

	/************************************************************************/
	/**  删除网管指示
	wParam = EmModifyNMServerRet 是否成功
	lparam = 无*/
	/************************************************************************/
	ev_UICnstoolDelNetmngInd,
#define UI_CNSTOOL_DEL_NETMNG_IND  ev_UICnstoolDelNetmngInd

	/************************************************************************/
	/**  网管信息通知
	wParam = TTPNMServerCfg* 网管信息
	lparam = 无*/
	/************************************************************************/
	ev_UICnstoolNetmngNty,
#define UI_CNSTOOL_NETMNG_NTY  ev_UICnstoolNetmngNty

	/************************************************************************/
	/**  修改网管指示
	wParam = EmModifyNMServerRet 是否成功
	lparam = 无*/
	/************************************************************************/
	ev_UICnstoolModifyNetmngInd,
#define UI_CNSTOOL_MODIFY_NETMNG_IND  ev_UICnstoolModifyNetmngInd

	/************************************************************************/
	/**  单板页面添加修改网管当前选中数据发送
	wParam = Window*   
	lparam = Type*/
	/************************************************************************/
	ev_UiCnstoolNetMngSelDataClick,
#define UI_CNSTOOL_MSG_NETMNGSELDATA_Click  ev_UiCnstoolNetMngSelDataClick

	/************************************************************************/
	/**  单板页面添加修改网管当前选中数据发送
	wParam = Window*   
	lparam = Type*/
	/************************************************************************/
	ev_UiCnstoolRouteSelDataClick,
#define UI_CNSTOOL_MSG_ROUTESELDATA_Click  ev_UiCnstoolRouteSelDataClick
	
	/************************************************************************/
	/**  接收呼叫服务器的通知信息
	wParam = 0   
	lparam = 0
	/************************************************************************/
	ev_UiCnstoolCallSerNty,
#define UI_CNSTOOL_MSG_CallSer_NTY  ev_UiCnstoolCallSerNty
		
	/************************************************************************/
	/**  接收呼叫服务器的回复信息
	wParam = TTPCallSerInfo  
	lparam = bSuccess 
	/************************************************************************/
	ev_UiCnstoolCallSerInd,
#define UI_CNSTOOL_MSG_CallSer_IND  ev_UiCnstoolCallSerInd
	
	/************************************************************************/
	/**  接收升级服务器的通知信息
	wParam = 0   
	lparam = 0
	/************************************************************************/
	ev_UiCnstoolUpgradeSerNty,
#define UI_CNSTOOL_MSG_UpgradeSer_NTY  ev_UiCnstoolUpgradeSerNty
		
	/************************************************************************/
	/**  接收升级服务器的回复信息
	wParam = u32_Ip
	lparam = bSuccess 
	/************************************************************************/
	ev_UiCnstoolUpgradeSerInd,
#define UI_CNSTOOL_MSG_UpgradeSer_IND  ev_UiCnstoolUpgradeSerInd
		
	/************************************************************************/
	/**  接收中控信息中空调的信息
	wParam = 0  
	lparam = 0
	/************************************************************************/
	ev_UiCnstoolAirInfoNty,
#define UI_CNSTOOL_MSG_AirInfo_NTY  ev_UiCnstoolAirInfoNty
	
	/************************************************************************/
	/**  接收中控信息中新风的信息
	wParam = 0 
	lparam = 0
	/************************************************************************/
	ev_UiCnstoolXinFengInfoNty,
#define UI_CNSTOOL_MSG_XinFengInfo_NTY  ev_UiCnstoolXinFengInfoNty
	
	/************************************************************************/
	/**  接收中控信息中显示器的信息
	wParam = 0 
	lparam = 0
	/************************************************************************/
	ev_UiCnstoolDisplayInfoNty,
#define UI_CNSTOOL_MSG_DisplayInfo_NTY  ev_UiCnstoolDisplayInfoNty
	
	/************************************************************************/
	/**  接收中控信息中摄像机的信息
	wParam = 0 
	lparam = 0
	/************************************************************************/
	ev_UiCnstoolCameraInfoNty,
#define UI_CNSTOOL_MSG_CameraInfo_NTY  ev_UiCnstoolCameraInfoNty
	
	/************************************************************************/
	/**  接收中控信息中文档摄像机的信息
	wParam = 0 
	lparam = 0
	/************************************************************************/
	ev_UiCnstoolDocCamInfoNty,
#define UI_CNSTOOL_MSG_DocCamInfo_NTY  ev_UiCnstoolDocCamInfoNty
	
	/************************************************************************/
	/**  接收中控信息中灯光的信息
	wParam = 0 
	lparam = 0
	/************************************************************************/
	ev_UiCnstoolLightInfoNty,
#define UI_CNSTOOL_MSG_LightInfo_NTY  ev_UiCnstoolLightInfoNty

	/************************************************************************/
	/**  摄像机配置通知
	wParam = NULL
	lparam = NULL
	/************************************************************************/
	ev_UICnstoolCameraCfgNty,
#define UI_CNSTOOL_CAMERA_CFG_NTY  ev_UICnstoolCameraCfgNty

	/************************************************************************/
	/**  选择控制摄像机返回命令
	wParam = NULL
	lparam = BOOL  = TRUE 选择成功 =FALSE 选择失败
	/************************************************************************/
	ev_UICnstoolCameraSelectInd,
#define UI_CNSTOOL_CAMERA_SELECT_IND  ev_UICnstoolCameraSelectInd

	/************************************************************************/
	/**  恢复摄像机出厂配置返回消息
	wParam = NULL
	lparam = BOOL   =TRUE 设置成功  FALSE 设置失败
	/************************************************************************/
	ev_UICnstoolCameraResetInd,
#define UI_CNSTOOL_CAMERA_RESET_IND  ev_UICnstoolCameraResetInd

	/************************************************************************/
	/**  摄像视野调节返回命令
	wParam = NULL
	lparam = BOOL:				TRUE 设置成功  =FALSE 设置失败
	/************************************************************************/
	ev_UICnstoolCameraZoomInd,
#define UI_CNSTOOL_CAMERA_ZOOM_IND  ev_UICnstoolCameraZoomInd

	/************************************************************************/
	/**  摄像机 视野在OSD上显示比例返回命令
	wParam = NULL
	lparam = BOOL          =TRUE 设置成功  =FALSE 设置失败
	/************************************************************************/
	ev_UICnstoolCameraOSDShowInd,
#define UI_CNSTOOL_CAMERA_OSDSHOW_IND  ev_UICnstoolCameraOSDShowInd

	/************************************************************************/
	/**  摄像头自动聚焦返回命令
	wParam = BOOL   =TRUE 设置成功   =FALSE 设置失败
	lparam = NULL
	/************************************************************************/
	ev_UICnstoolCameraAutoFocusInd,
#define UI_CNSTOOL_CAMERA_AUTO_FOCUS_IND  ev_UICnstoolCameraAutoFocusInd

	/************************************************************************/
	/**  摄像头聚焦返回命令
	wParam = EmFocus         emFar 远焦  emNear近焦
	lparam = BOOL        =TRUE 设置成功  =FALSE 设置失败
	/************************************************************************/
	ev_UICnstoolCameraFocusInd,
#define UI_CNSTOOL_CAMERA_FOCUS_IND  ev_UICnstoolCameraFocusInd

	/************************************************************************/
	/**  摄像机自动曝光返回命令
	wParam = NULL
	lparam = BOOL       =TRUE 设置成功  =FALSE 设置失败 
	/************************************************************************/
	ev_UICnstoolCameraAutoExposureInd,
#define UI_CNSTOOL_CAMERA_AUTO_EXPOSURE_IND  ev_UICnstoolCameraAutoExposureInd

	/************************************************************************/
	/**  摄像机手动曝光——增益调节返回命令
	wParam = NULL
	lparam = BOOL    =　TRUE 设置成功   =FALSE 设置失败
	/************************************************************************/
	ev_UICnstoolCameraGainInd,
#define UI_CNSTOOL_CAMERA_GAIN_IND  ev_UICnstoolCameraGainInd

	/************************************************************************/
	/**  摄像机手动曝光——快门调节返回命令
	wParam = NULL
	lparam = BOOL    =　TRUE 设置成功   =FALSE 设置失败
	/************************************************************************/
	ev_UICnstoolCameraShutSpdInd,
#define UI_CNSTOOL_CAMERA_SHUT_SPD_IND  ev_UICnstoolCameraShutSpdInd

	/************************************************************************/
	/**  摄像机手动曝光——背光调节返回命令
	wParam = NULL
	lparam = BOOL    =　TRUE 设置成功   =FALSE 设置失败
	/************************************************************************/
	ev_UICnstoolCameraBackLightInd,
#define UI_CNSTOOL_CAMERA_BACK_LIGHT_IND  ev_UICnstoolCameraBackLightInd

	/************************************************************************/
	/**  摄像机手动曝光——光圈调节返回命令
	wParam = NULL
	lparam = BOOL   =TRUE 设置成功   =FALSE 设置失败
	/************************************************************************/
	ev_UICnstoolCameraApertureInd,
#define UI_CNSTOOL_CAMERA_APERTURE_IND  ev_UICnstoolCameraApertureInd

	/************************************************************************/
	/**  摄像机自动白平衡返回命令
	wParam = BOOL   =TRUE 设置成功   =FALSE 设置失败
	lparam = NULL
	/************************************************************************/
	ev_UICnstoolCameraAutoWBInd,
#define UI_CNSTOOL_CAMERA_AUTO_WB_IND  ev_UICnstoolCameraAutoWBInd

	/************************************************************************/
	/**  摄像机手动白平衡--R Gain返回命令
	wParam = NULL
	lparam = BOOL   =TRUE 设置成功      =FALSE  设置失败
	/************************************************************************/
	ev_UICnstoolCameraRGainInd,
#define UI_CNSTOOL_CAMERA_RGAIN_IND  ev_UICnstoolCameraRGainInd

	/************************************************************************/
	/**  摄像机手动白平衡--B Gain返回命令
	wParam = NULL
	lparam = BOOL   =TRUE 设置成功      =FALSE  设置失败
	/************************************************************************/
	ev_UICnstoolCameraBGainInd,
#define UI_CNSTOOL_CAMERA_BGAIN_IND  ev_UICnstoolCameraBGainInd

	/************************************************************************/
	/**  摄像机场景模式返回命令
	wParam = NULL
	lparam = BOOL   =TRUE 设置成功      =FALSE  设置失败
	/************************************************************************/
	ev_UICnstoolCameraPicSceneModeInd,
#define UI_CNSTOOL_CAMERA_PIC_SCENE_MODE_IND  ev_UICnstoolCameraPicSceneModeInd

	/************************************************************************/
	/**  摄像机 模式--- 手动 GAMMA调节返回命令
	wParam = NULL
	lparam = BOOL   =TRUE 设置成功      =FALSE  设置失败
	/************************************************************************/
	ev_UICnstoolCameraGammaInd,
#define UI_CNSTOOL_CAMERA_GAMMA_IND  ev_UICnstoolCameraGammaInd

	/************************************************************************/
	/**  摄像机 模式--- 光圈调节返回命令
	wParam = NULL
	lparam = BOOL   =TRUE 设置成功      =FALSE  设置失败
	/************************************************************************/
	ev_UICnstoolCameraPicSceAptInd,
#define UI_CNSTOOL_CAMERA_PIC_SCE_APT_IND  ev_UICnstoolCameraPicSceAptInd

	/************************************************************************/
	/**  摄像机 图片调节---对比度 调节返回命令
	wParam = NULL
	lparam = BOOL   =TRUE 设置成功      =FALSE  设置失败
	/************************************************************************/
	ev_UICnstoolCameraContrastInd,
#define UI_CNSTOOL_CAMERA_CONTRAST_IND  ev_UICnstoolCameraContrastInd

	/************************************************************************/
	/**  摄像机 图片调节---饱和度 调节返回命令
	wParam = NULL
	lparam = BOOL   =TRUE 设置成功      =FALSE  设置失败
	/************************************************************************/
	ev_UICnstoolCameraSaturatInd,
#define UI_CNSTOOL_CAMERA_SATURAT_IND  ev_UICnstoolCameraSaturatInd

	/************************************************************************/
	/**  摄像机 图片调节--- 色度 调节返回命令
	wParam = NULL
	lparam = BOOL   =TRUE 设置成功      =FALSE  设置失败
	/************************************************************************/
	ev_UICnstoolCameraHueInd,
#define UI_CNSTOOL_CAMERA_HUE_IND  ev_UICnstoolCameraHueInd

	/************************************************************************/
	/**  摄像机 图片调节--- 亮度 调节返回命令
	wParam = NULL
	lparam = BOOL   =TRUE 设置成功      =FALSE  设置失败
	/************************************************************************/
	ev_UICnstoolCameraBrightInd,
#define UI_CNSTOOL_CAMERA_BRIGHT_IND  ev_UICnstoolCameraBrightInd

	/************************************************************************/
	/**  摄像机 降噪---噪点过滤 调节返回命令
	wParam = NULL
	lparam = BOOL   =TRUE 设置成功      =FALSE  设置失败
	/************************************************************************/
	ev_UICnstoolCameraNRStmCleanInd,
#define UI_CNSTOOL_CAMERA_NR_STM_CLEAN_IND  ev_UICnstoolCameraNRStmCleanInd

	/************************************************************************/
	/**  摄像机 降噪---3D降噪 调节返回命令
	wParam = NULL
	lparam = BOOL   =TRUE 设置成功      =FALSE  设置失败
	/************************************************************************/
	ev_UICnstoolCamera3DNRInd,
#define UI_CNSTOOL_CAMERA_3DNR_IND  ev_UICnstoolCamera3DNRInd

	/************************************************************************/
	/**  摄像机 预置位保存返回命令
	wParam = NULL	
	lparam = BOOL	TRUE= 保存预置位成功   = FALSE 保存失败
	/************************************************************************/
	ev_UICnstoolCameraPersetSaveInd,
#define UI_CNSTOOL_CAMERA_PERSET_SAVE_IND  ev_UICnstoolCameraPersetSaveInd

	/************************************************************************/
	/**  摄像机 设置开机调用预置位
	wParam = NULL	
	lparam = BOOL	TRUE= 设置成功   = FALSE 设置失败
	/************************************************************************/
	ev_UICnstoolCameraPersetMoveInd,
#define UI_CNSTOOL_CAMERA_PERSET_MOVE_IND  ev_UICnstoolCameraPersetMoveInd

	/************************************************************************/
	/**  摄像机 设置ZOOM
	wParam = NULL	
	lparam = BOOL	TRUE= 设置成功   = FALSE 设置失败
	/************************************************************************/
	ev_UICnstoolSetCameraZoomInd,
#define UI_CNSTOOL_SET_CAMERA_ZOOM_IND  ev_UICnstoolSetCameraZoomInd
			
	/************************************************************************/
	/**  接收音频混音数设置通知消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolAudMixerInd,
#define UI_CNSTOOL_MSG_AudMixer_NTY  ev_UiCnstoolAudMixerInd
				
	/************************************************************************/
	/**  接收系统默认音频混音数消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolDefaultMixerInd,
#define UI_CNSTOOL_MSG_DftMixer_NTY  ev_UiCnstoolDefaultMixerInd
	
	/************************************************************************/
	/**  接收音频均衡器设置通知消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolAudEqualizerInd,
#define UI_CNSTOOL_MSG_AudEqualizer_NTY  ev_UiCnstoolAudEqualizerInd
				
	/************************************************************************/
	/**  接收系统默认音频均衡器消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolDefaultEqInd,
#define UI_CNSTOOL_MSG_DftEq_NTY  ev_UiCnstoolDefaultEqInd
			
	/************************************************************************/
	/**  接收升级T300回复消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolUpgradeCnsInd,
#define UI_CNSTOOL_MSG_UpgradeCns_NTY  ev_UiCnstoolUpgradeCnsInd
			
	/************************************************************************/
	/**  接收停止测试回复消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolStopAVMatrixRsp,
#define UI_CNSTOOL_MSG_StopAVMatrix_RSP  ev_UiCnstoolStopAVMatrixRsp
				
	/************************************************************************/
	/**  中控摄像机状态通知信息
	wParam =  aemCam   存放摄像机数组头指针
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolCamPowerStateNty,
#define UI_CNSTOOL_MSG_CamPowerState_NTY  ev_UiCnstoolCamPowerStateNty
				
	/************************************************************************/
	/**  根据收到的GK注册消息改变基本信息界面的状态
	wParam =  0   
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolGKRspNty,
#define UI_CNSTOOL_MSG_GKRsp_NTY  ev_UiCnstoolGKRspNty
				
	/************************************************************************/
	/**  根据收到的sip注册消息改变基本信息界面的状态
	wParam =  0   
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolSIPRspNty,
#define UI_CNSTOOL_MSG_SIPRsp_NTY  ev_UiCnstoolSIPRspNty
				
	/************************************************************************/
	/**  日志下载进度提醒 
	wParam =  进度值  
	lparam = 0*/
	/************************************************************************/
	em_CNSTOOL_FTPLOGPROGRESS,
#define WM_CNSTOOL_FTPLOGPROGRESS  em_CNSTOOL_FTPLOGPROGRESS				   
				
	/************************************************************************/
	/**  地址簿导入导出进度提醒
	wParam =  进度值  
	lparam = 0*/
	/************************************************************************/	
	em_CNSTOOL_FTPADDRBOOKPROGRESS,
#define WM_CNSTOOL_FTPADDRBOOKPROGRESS  em_CNSTOOL_FTPADDRBOOKPROGRESS  
    
	/************************************************************************/
	/**  网络抓包工具导入以及抓包文件导出
	wParam =  进度值  
	lparam = 0*/
	/************************************************************************/	
	em_CNSTOOL_FTPCAPTUREPROGRESS,
#define WM_CNSTOOL_FTPCAPTUREPROGRESS  em_CNSTOOL_FTPCAPTUREPROGRESS

	/************************************************************************/
	/**  网络抓包失败
	*/
	/************************************************************************/
	em_CNSTOOL_CAPTUREFAIL,
#define WM_CNSTOOL_CAPTUREFAIL 	em_CNSTOOL_CAPTUREFAIL
	
	/************************************************************************/
	/**  停止抓包消息
	wParam =  进度值  
	lparam = 0*/
	/************************************************************************/	
	em_CNSTOOL_CAPTUREMAXSIZE,
#define WM_CNSTOOL_CAPTUREMAXSIZE  em_CNSTOOL_CAPTUREMAXSIZE

	/************************************************************************/
	/**  台标上传进度提醒
	wParam =  进度值  
	lparam = 0*/
	/************************************************************************/	
	em_CNSTOOL_CONFSIGNPROGRESS,
#define WM_CNSTOOL_FTPCONFSIGNPROGRESS  em_CNSTOOL_CONFSIGNPROGRESS		   
				
	/************************************************************************/
	/**  文件上传进度提醒 
	wParam =  进度值  
	lparam = 0*/
	/************************************************************************/
	em_CNSTOOL_UPLODEPROGRESS,
#define WM_CNSTOOL_UPLODEPROGRESS  em_CNSTOOL_UPLODEPROGRESS				   

	/************************************************************************/
	/**  收到摄像机上电消息
	wParam = 0  
	lparam = 0*/
	/************************************************************************/
	ev_UICnstoolCameraPowerOnNty,
#define UI_CNSTOOL_CAMERA_POWER_ON_NTY  ev_UICnstoolCameraPowerOnNty
	
	/************************************************************************/
	/**  收到会议优选格式消息
	wParam = 0  
	lparam = 0*/
	/************************************************************************/
	ev_UICnstoolVideoFormatInd,
#define UI_CNSTOOL_VIDEOFORMAT_IND  ev_UICnstoolVideoFormatInd
		
	/************************************************************************/
	/**  收到演示优选格式消息
	wParam = 0  
	lparam = 0*/
	/************************************************************************/
	ev_UICnstoolDualVideoFormatInd,
#define UI_CNSTOOL_DUALVIDEOFORMAT_IND  ev_UICnstoolDualVideoFormatInd
			
	/************************************************************************/
	/**  收到单屏码率消息
	wParam = 0  
	lparam = 0*/
	/************************************************************************/
	ev_UICnstoolCallRateInd,
#define UI_CNSTOOL_CALLRATE_IND  ev_UICnstoolCallRateInd
				
	/************************************************************************/
	/**  收到演示码率消息
	wParam = 0  
	lparam = 0*/
	/************************************************************************/
	ev_UICnstoolDualCallRateInd,
#define UI_CNSTOOL_DUALCALLRATE_IND  ev_UICnstoolDualCallRateInd
					
	/************************************************************************/
	/**  收到版本通知消息
	wParam = 0  
	lparam = 0*/
	/************************************************************************/
	ev_UICnstoolVerInfoNty,
#define UI_CNSTOOL_VERINFO_NTY  ev_UICnstoolVerInfoNty
				
	/************************************************************************/
	/**  收到会议讨论消息
	wParam = 0  
	lparam = 0*/
	/************************************************************************/
	ev_UICnstoolConfDisInd,
#define UI_CNSTOOL_CONFDIS_IND  ev_UICnstoolConfDisInd
				
	/************************************************************************/
	/**  收到会议轮询消息
	wParam = 0  
	lparam = 0*/
	/************************************************************************/
	ev_UICnstoolConfPollInd,
#define UI_CNSTOOL_CONFPOOL_IND  ev_UICnstoolConfPollInd
				
	/************************************************************************/
	/**  收到音频格式消息
	wParam = 0  
	lparam = 0*/
	/************************************************************************/
	ev_UICnstoolAudioFormatInd,
#define UI_CNSTOOL_AUDIOFORMAT_IND  ev_UICnstoolAudioFormatInd
				
	/************************************************************************/
	/**  中控电视墙通知信息
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolCfgDisplayInd,
#define UI_CNSTOOL_MSG_DISPLAY_IND  ev_UiCnstoolCfgDisplayInd

	/************************************************************************/
	/**  中控显示器显示配置界面通知信息
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UICnstoolDisplayShowNty,
#define UI_CNSTOOL_DISPLAY_SHOW_Nty  ev_UICnstoolDisplayShowNty

	/************************************************************************/
	/**  中控显示器显示配置界面通知信息
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UICnstoolDisplayShowInd,
#define UI_CNSTOOL_DISPLAY_SHOW_Ind  ev_UICnstoolDisplayShowInd
	/************************************************************************/
	/**  中控显示器型号通知消息
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolCfgTVModeInd,
#define UI_CNSTOOL_MSG_TVMode_IND  ev_UiCnstoolCfgTVModeInd

	/************************************************************************/
	/**  收到窗帘名称数组消息
	wParam = 窗帘名称数组  
	lparam = 0*/
	/************************************************************************/
	ev_UITpadCurtainStateNty,
#define UI_TPAD_CURTAINSTATE_NTY  ev_UITpadCurtainStateNty
	
	/************************************************************************/
	/**  接收音频配置端口消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolAudioInd,
#define UI_CNSTOOL_MSG_Audio_NTY  ev_UiCnstoolAudioInd

	/************************************************************************/
	/**  音频配置监听输出端口消息 本地还是远端混音
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_TppSetMixTypeInd,
#define UI_CNSTOOL_MSG_Listen_NTY ev_TppSetMixTypeInd

	/************************************************************************/
	/**  AUX2 OUT本地扩音输出
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_TppSetLocalAudExtendInd,
#define UI_CNSTOOL_MSG_AUX2_NTY  ev_TppSetLocalAudExtendInd
	/************************************************************************/
	/**  接收默认音频配置端口消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolDftAudioInd,
#define UI_CNSTOOL_MSG_DftAudio_NTY  ev_UiCnstoolDftAudioInd
	/************************************************************************/
	/**  接收白噪声设置消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolWhiteNoiseInd,
#define UI_CNSTOOL_MSG_WhiteNoise_NTY  ev_UiCnstoolWhiteNoiseInd
	/************************************************************************/
	/**  接收更新白噪声消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolWhiteNoiseUpdate,
#define UI_CNSTOOL_MSG_WhiteNoiseUpdate_NTY  ev_UiCnstoolWhiteNoiseUpdate
	/************************************************************************/
	/**  接收主视频配置消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolVideoSourceInd,
#define UI_CNSTOOL_MSG_VideoSource_NTY  ev_UiCnstoolVideoSourceInd
	/************************************************************************/
	/**  接收默认主视频配置消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolDefMainAudioInd,
#define UI_CNSTOOL_MSG_DefAudio_NTY  ev_UiCnstoolDefMainAudioInd
	/************************************************************************/
	/**  接收重命名视频源端口消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolRenameVideoSourceClick,
#define UI_CNSTOOL_MSG_RenameVideoSource_Click  ev_UiCnstoolRenameVideoSourceClick
	/************************************************************************/
	/**  接收视频源端口更新消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolUpdateVideoSourceNty,
#define UI_CNSTOOL_MSG_UpdateVideoSource_Nty  ev_UiCnstoolUpdateVideoSourceNty
	/************************************************************************/
	/**  接收演示源消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolDisplaySourceInd,
#define UI_CNSTOOL_MSG_DisplaySource_Nty  ev_UiCnstoolDisplaySourceInd
	/**  接收默认演示源消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolDefaultDisplaySourceInd,
#define UI_CNSTOOL_MSG_DefaultDisplaySource_Nty  ev_UiCnstoolDefaultDisplaySourceInd
	/************************************************************************/
	/**  接收重命名演示源消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolRenameDisplaySourceClick,
#define UI_CNSTOOL_MSG_ReDisplaySrc_Click  ev_UiCnstoolRenameDisplaySourceClick
	/**  接收重命名视频源更新消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolRenameDisplaySourceNty,
#define UI_CNSTOOL_MSG_RenameDisplaySource_Nty  ev_UiCnstoolRenameDisplaySourceNty
	/**  接收输出图像参数消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolImageAdjustInd,
#define UI_CNSTOOL_MSG_ImageAdjust_Nty  ev_UiCnstoolImageAdjustInd
	/**  接收默认输出图像参数消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolDefaultImageAdjustInd,
#define UI_CNSTOOL_MSG_DefaultImageAdjust_Nty  ev_UiCnstoolDefaultImageAdjustInd
	/**  开始在线统计
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolStartRecorderNty,
#define UI_CNSTOOL_MSG_StartRecorder_Nty  ev_UiCnstoolStartRecorderNty
	/**  接收统计操作消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolStatisticNty,
#define UI_CNSTOOL_MSG_Statistic_Nty  ev_UiCnstoolStatisticNty
	/**  接收全景摄像机通知消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
//	ev_UiCnstoolPanCamNty,
//#define UI_CNSTOOL_PanCam_Nty  ev_UiCnstoolPanCamNty
	/**  接收设置全景摄像机数量反馈消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolPanCamNumInd,
#define UI_CNSTOOL_PanCamNum_Nty  ev_UiCnstoolPanCamNumInd
	/**  接收文档摄像机ZOOM消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolDcCameraZOOMInd,
#define UI_CNSTOOL_DCCAMERA_ZOOM_Nty  ev_UiCnstoolDcCameraZOOMInd
	/**  接收文档摄像机视眼值消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
//	ev_UiCnstoolDcCameraZOOMValueInd,
//#define UI_CNSTOOL_DCCAMERA_ZOOMValue_Nty  ev_UiCnstoolDcCameraZOOMValueInd
	/**  接收文档摄像机自动/手动消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolDcCameraAutoFocusInd,
#define UI_CNSTOOL_DCCAMERA_AUTO_FOCUS_IND  ev_UiCnstoolDcCameraAutoFocusInd
	/**  接收文档摄像机曝光模式消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolDCamExposureInd,
#define UI_CNSTOOL_DCamExposure_Nty  ev_UiCnstoolDCamExposureInd
	/**  接收文档摄像机增益消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolDCamGainInd,
#define UI_CNSTOOL_DCamGain_Nty  ev_UiCnstoolDCamGainInd
	/**  接收文档摄像机快门消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolDCamShutterInd,
#define UI_CNSTOOL_DCamShut_Nty  ev_UiCnstoolDCamShutterInd
	/**  接收文档摄像机光圈消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolDCamApertureInd,
#define UI_CNSTOOL_DCamAperture_Nty  ev_UiCnstoolDCamApertureInd
	/**  接收文档摄像机白平衡消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolDcCameraWBInd,
#define UI_CNSTOOL_DCCAMERA_WB_Nty  ev_UiCnstoolDcCameraWBInd
	/**  接收文档摄像机R增益消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolDcCameraRGainInd,
#define UI_CNSTOOL_DCCAMERA_RGain_Nty  ev_UiCnstoolDcCameraRGainInd
	/**  接收文档摄像机B增益消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolDcCameraBGainInd,
#define UI_CNSTOOL_DCCAMERA_BGain_Nty  ev_UiCnstoolDcCameraBGainInd
	/**  接收文档摄像机预置位
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolDcCameraPreSetNty,
#define UI_CNSTOOL_DCCAMERA_PreSet_Nty  ev_UiCnstoolDcCameraPreSetNty
	/**  接收文档摄像机保存预置位消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolDcCamSavePreSetInd,
#define UI_CNSTOOL_DCCAMERA_SavePreSet_Nty  ev_UiCnstoolDcCamSavePreSetInd
	/**  接收文档摄像机调用预置位消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolDcCamCallPreSetInd,
#define UI_CNSTOOL_DCCAMERA_CallPreSet_Nty  ev_UiCnstoolDcCamCallPreSetInd
	/**  接收窗帘重命名消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolCurtainRenameNty,
#define UI_CNSTOOL_CurtainRename_Nty  ev_UiCnstoolCurtainRenameNty
	/**  接收CNS窗帘重命名消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolCurtainRenameInd,
#define UI_CNSTOOL_CENTRE_CurRename_Nty  ev_UiCnstoolCurtainRenameInd
	/**  接收窗帘数量消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolCurtainNumInd,
#define UI_CNSTOOL_CENTRE_CurNumSet_Nty  ev_UiCnstoolCurtainNumInd
	/**  接收窗帘开启/关闭消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolCurtainOpenInd,
#define UI_CNSTOOL_CENTRE_CurOpen_Nty  ev_UiCnstoolCurtainOpenInd
	/**  接收快照消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolSnapShotInd,
#define UI_CNSTOOL_SnapShot_Nty  ev_UiCnstoolSnapShotInd
	/**  接收加密消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolEncryptInfoInd,
#define UI_CNSTOOL_EncryptInfo_Nty  ev_UiCnstoolEncryptInfoInd
	/**  接收丢包恢复消息
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolLostPacketInd,
#define UI_CNSTOOL_LostPacket_Nty  ev_UiCnstoolLostPacketInd
	/************************************************************************/
	/**  快照下载提醒 
	wParam =  进度值  
	lparam = 0*/
	/************************************************************************/
	em_CNSTOOL_FTPSnapDownLoad,
#define WM_CNSTOOL_FTPSnapDownLoad  em_CNSTOOL_FTPSnapDownLoad
	/**  接口诊断界面刷新主视频接口
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolRefInportTitleNty,
#define UI_CNSTOOL_RefInportTitle_Nty  ev_UiCnstoolRefInportTitleNty
	/**  双流屏配置通知
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolDualScreenNty,
#define UI_CNSTOOL_DUALSCREEN_Nty  ev_UiCnstoolDualScreenNty
	/**  配置文档摄像机通知
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolDCCamCfgNty,
#define UI_CNSTOOL_DCCamCfg_Nty  ev_UiCnstoolDCCamCfgNty
	/**  配置文档摄像机开机调用预置位
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolDCCamBootCallPresetNty,
#define UI_CNSTOOL_DCCamBootCallPreset_Nty  ev_UiCnstoolDCCamBootCallPresetNty
	/**  配置空调是否存在
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolAirCondtitionNty,
#define UI_CNSTOOL_AirCondtition_Nty  ev_UiCnstoolAirCondtitionNty
	/**  配置文档摄像机型号
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolDocCamTypeNty,
#define UI_CNSTOOL_DocCamType_Nty  ev_UiCnstoolDocCamTypeNty
	/**  配置全景摄像机型号
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UiCnstoolPanCamTypeNty,
#define UI_CNSTOOL_PanCamType_Nty  ev_UiCnstoolPanCamTypeNty
	/**  量子加密信息通知界面
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UISetQtEncryptInfoNty,
#define UI_SETQTENCRYPTINFO_Nty  ev_UISetQtEncryptInfoNty
		/**  量子加密设置信息通知界面
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UISetQtEncryptInfoInd,
#define UI_SETQTENCRYPTINFO_Ind  ev_UISetQtEncryptInfoInd
	/**  Ftp状态信息通知界面
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_CnFtpStateNty,
#define UI_FTPSTATE_NTY  ev_CnFtpStateNty
	/**  Ftp状态设置回复信息通知界面
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_CnOpenFtpRsp,
#define UI_OPENFTP_Rsp  ev_CnOpenFtpRsp
	/**  Ftp用户名和密码信息通知界面
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_CnFtpInfoNty,
#define UI_FTPINFO_Nty  ev_CnFtpInfoNty
	/**  Ftp用户名和密码设置回复信息通知界面
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_CnSetFtpRsp,
#define UI_SETFTPINFO_Rsp  ev_CnSetFtpRsp
		/**  Telnet状态信息通知界面
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_CnTelnetStateNty,
#define UI_TELNETSTATE_NTY  ev_CnTelnetStateNty
	/**  Telnet状态设置回复信息通知界面
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_CnOpenTelnetRsp,
#define UI_OPENTELNET_Rsp  ev_CnOpenTelnetRsp
	/**  Telnet用户名和密码信息通知界面
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_CnTelnetInfoNty,
#define UI_TELNETINFO_Nty  ev_CnTelnetInfoNty
	/**  Telnet用户名和密码设置回复信息通知界面
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_CnSetTelnetRsp,
#define UI_SETTELNETINFO_Rsp  ev_CnSetTelnetRsp

	/**  路由通知
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UItppRouteInfoNty,
#define UI_ROUTEINFO_Nty  ev_UItppRouteInfoNty

	/**  路由添加通知
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UItppAddRouteInd,
#define UI_ADDROUTE_Ind  ev_UItppAddRouteInd
	
	/**  路由删除通知
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UItppDelRouteInd,
#define UI_DelROUTE_Ind  ev_UItppDelRouteInd

	/**  云平台服务器通知
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UICloudServerInd,
#define UI_CNC_CLOUDSERVER_IND  ev_UICloudServerInd

    /**  Moon904K摄像机配置修改回复
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoon904KCamCfgInd,
#define UI_CNSTOOL_MOON904KCAMCFG_IND  ev_UIMoon904KCamCfgInd

    /**  视频源掉线通知
	wParam =  0
	lparam = 0*/
	/************************************************************************/
	ev_UISrcOfflineNty,
#define UI_SRCOFFLINE_NTY  ev_UISrcOfflineNty
};

//moontool中消息定义
enum EmUiMoontoolMsg
{
#define UI_MOONTOOL_MSG_BEGIN  MOONTOOL_MSG_BEGIN + 0x1

	/************************************************************************/
	/** 连接 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIRkConnect	= UI_MOONTOOL_MSG_BEGIN,
#define	UI_RKC_CONNECTED  ev_UIRkConnect
	
	/************************************************************************/
	/** 已断开
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIRkDisconnected,
#define UI_RKC_DISCONNECTED	 ev_UIRkDisconnected

    /************************************************************************/
	/** 重启
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIRkReBoot,
#define UI_RKC_REBOOT	 ev_UIRkReBoot

    /************************************************************************/
	/** 恢复出厂设置
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIRkRestore,
#define UI_RKC_RESTONE	 ev_UIRkRestore

    /************************************************************************/
	/** 刷新搜索列表
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIRkDevReflesh,
#define UI_RKC_RKDEV_REFLESH    ev_UIRkDevReflesh

    /************************************************************************/
	/** 搜索包发送完毕
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UISearchFinish,
#define UI_RKC_SEARCH_FINISH    ev_UISearchFinish

     /************************************************************************/
	/** 刷新工作模式界面
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIWorkModeReflesh,
#define UI_RKC_WORKMODE_REFLESH    ev_UIWorkModeReflesh

    /************************************************************************/
	/** 工作模式修改反馈
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIWorkModeChange,
#define UI_RKC_WORKMODE_CHANGE    ev_UIWorkModeChange

    /************************************************************************/
	/** IP校验反馈
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIIPChecking,
#define UI_RKC_IP_CHECK    ev_UIIPChecking

    /************************************************************************/
	/** 刷新网络配置界面
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UINetWorkReflesh,
#define UI_RKC_NETWORK_REFLESH    ev_UINetWorkReflesh

    /************************************************************************/
	/** 网络配置修改反馈
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UINetWorkChange,
#define UI_RKC_NETWORK_CHANGE    ev_UINetWorkChange

	/************************************************************************/
	/** 修改密码反馈
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIRkModifyPassword,
#define UI_RKC_MODIFY_PASSWORD    ev_UIRkModifyPassword

    /************************************************************************/
	/** 功耗电源刷新
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIPowerFlesh,
#define UI_RKC_POWER_FLESH    ev_UIPowerFlesh

    /************************************************************************/
	/** 升级更新回复
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIRkUpdateFirstAck,
#define UI_RKC_UPDATE_FIRST_ACK    ev_UIRkUpdateFirstAck

    /************************************************************************/
	/** 升级更新回复notify
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIRkUpdateFirstNty,
#define UI_RKC_UPDATE_FIRST_NTY    ev_UIRkUpdateFirstNty

    /************************************************************************/
	/** 升级更新回复notify
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIRkUpdateSecondNty,
#define UI_RKC_UPDATE_SECOND_NTY    ev_UIRkUpdateSecondNty

    /************************************************************************/
	/** 调试模式刷新
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIDebugModeFlesh,
#define UI_RKC_DEBUGMODE_FLESH    ev_UIDebugModeFlesh

    /************************************************************************/
	/** 调试模式修改反馈
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIDebugModeChange,
#define UI_RKC_DEBUGMODE_CHANGE    ev_UIDebugModeChange

    /************************************************************************/
	/** 板卡信息通知
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIBrdInfoNty,
#define UI_RKC_BRDINFO_NTY    ev_UIBrdInfoNty

//MOON90
	/************************************************************************/
	/** 连接  MOON90 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolLoginRsp,
#define	UI_MOONTOOL_CONNECTED  ev_UIMoonToolLoginRsp

	/************************************************************************/
	/** 已断开MOON90
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolDisconnected,
#define UI_MOONTOOL_DISCONNECTED	 ev_UIMoonToolDisconnected

	/************************************************************************/
	/** MOON90摄像调节界面数据信息通知 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamInfoNty,
#define	UI_MOONTOOL_CAMINFO_NTY  ev_UIMoonToolCamInfoNty

	/************************************************************************/
	/** MOON90梯形矫正Zoom值通知界面 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonDistortZoomNty,
#define	UI_DISTORTZOOM_NTY  ev_UIMoonDistortZoomNty

	/************************************************************************/
	/** MOON90摄像机选择界面通知 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamSelectInd,
#define	UI_MOONTOOL_CamSel_IND  ev_UIMoonToolCamSelectInd

	/************************************************************************/
	/** MOON90摄像机机芯同步通知 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamParamSyncInd,
#define	UI_MOONTOOL_CamParamSync_IND  ev_UIMoonToolCamParamSyncInd

	/************************************************************************/
	/** MOON90摄像机机芯选择界面通知 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamStyleSelectInd,
#define	UI_MOONTOOL_CamStyleSel_IND  ev_UIMoonToolCamStyleSelectInd

    /************************************************************************/
	/** 摄像调节界面输出制式设置回复 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolOutputFormatRsp,
#define	UI_MOONTOOL_OUTPUT_FORMAT_RSP  ev_UIMoonToolOutputFormatRsp

	/************************************************************************/
	/** 摄像调节界面zoom值增减设置回复 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamZoomInd,
#define	UI_MOONTOOL_SET_CAMERA_ZOOM_IND  ev_UIMoonToolCamZoomInd

	/************************************************************************/
	/** 梯形矫正界面zoom值增减设置回复 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamSetZoonStopInd,
#define	UI_MOONTOOL_CAMSETZOON_STOP_IND  ev_UIMoonToolCamSetZoonStopInd

	/************************************************************************/
	/** 摄像调节界面zoom值增减设置回复 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamAutoFocusInd,
#define	UI_MOONTOOL_CAMERA_AUTO_FOCUS_IND  ev_UIMoonToolCamAutoFocusInd

    /************************************************************************/
	/** 光圈设置回复 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamApertreRsp,
#define	UI_MOONTOOL_CAMERA_APERTRE_RSP  ev_UIMoonToolCamApertreRsp

	/************************************************************************/
	/** 是否开启自动曝光回复 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamAutoExposureInd,
#define	UI_MOONTOOL_CAMERA_AUTO_EXPOSURE_IND  ev_UIMoonToolCamAutoExposureInd

	/************************************************************************/
	/** 是否开启自动白平衡回复 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamAutoWBInd,
#define	UI_MOONTOOL_CAMERA_AUTO_WB_IND  ev_UIMoonToolCamAutoWBInd

	/************************************************************************/
	/** 白平衡R制式回复 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamRGainInd,
#define	UI_MOONTOOL_CAMERA_RGAIN_IND  ev_UIMoonToolCamRGainInd

	/************************************************************************/
	/** 白平衡B制式回复 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamBGainInd,
#define	UI_MOONTOOL_CAMERA_BGAIN_IND  ev_UIMoonToolCamBGainInd

	/************************************************************************/
	/** 背光补偿是否开启界面回复 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamBackLightInd,
#define	UI_MOONTOOL_CAMERA_BACKLIGHT_IND  ev_UIMoonToolCamBackLightInd

	/************************************************************************/
	/** 降噪设置界面回复 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamNRInd,
#define	UI_MOONTOOL_CAMERA_NR_IND  ev_UIMoonToolCamNRInd

	/************************************************************************/
	/** 2D降噪设置界面回复 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCam2DNRInd,
#define	UI_MOONTOOL_CAMERA_2DNR_IND  ev_UIMoonToolCam2DNRInd

	/************************************************************************/
	/** 3D降噪设置界面回复 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCam3DNRInd,
#define	UI_MOONTOOL_CAMERA_3DNR_IND  ev_UIMoonToolCam3DNRInd

	/************************************************************************/
	/** 降噪设置界面回复 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamInitPresetInd,
#define	UI_MOONTOOL_CAMERA_INITPRESET_IND  ev_UIMoonToolCamInitPresetInd
		
	/************************************************************************/
	/** 亮度调节后通知界面 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolImageBLightInd,
#define	UI_MOONTOOL_IMAGE_BLIGHT_IND  ev_UIMoonToolImageBLightInd

	/************************************************************************/
	/** 对比度调节后通知界面 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolImageContrastInd,
#define	UI_MOONTOOL_IMAGE_CONTRAST_IND  ev_UIMoonToolImageContrastInd

	/************************************************************************/
	/** 色度调节后通知界面 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolImageSharpInd,
#define	UI_MOONTOOL_IMAGE_Sharp_IND  ev_UIMoonToolImageSharpInd

	/************************************************************************/
	/** 饱和度调节后通知界面 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolImageSaturatInd,
#define	UI_MOONTOOL_IMAGE_SATURAT_IND  ev_UIMoonToolImageSaturatInd
	
	/************************************************************************/
	/** 光圈调节后通知界面 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamApertureInd,
#define	UI_MOONTOOL_CAMERA_APERTURE_IND  ev_UIMoonToolCamApertureInd

	/************************************************************************/
	/** 快门调节后通知界面 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamShutSpdInd,
#define	UI_MOONTOOL_CAMERA_SHUT_SPD_IND  ev_UIMoonToolCamShutSpdInd

	/************************************************************************/
	/** 增益调节后通知界面 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamGainInd,
#define	UI_MOONTOOL_CAMERA_GAIN_IND  ev_UIMoonToolCamGainInd

	/************************************************************************/
	/** 增益调节后通知界面 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolImageParaInd,
#define	UI_MOONTOOL_IMAGEPARA_IND  ev_UIMoonToolImageParaInd

	/************************************************************************/
	/** 梯形校正操作结果通知界面 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolCamDistortParamInd,
#define	UI_MOONTOOL_CAMERA_DISTORTPARAM_IND  ev_UIMoonToolCamDistortParamInd

	/************************************************************************/
	/** 设置颜色一致性自动计算通知界面 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIAutoSetColorConstancyInd,
#define	UI_AUTOSETCOLORCONSTANCY_IND  ev_UIAutoSetColorConstancyInd

	/************************************************************************/
	/** 中间路RGB系数改变时通知两边路RGB改变系数通知界面 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
    ev_UIChangeSideRGBNty,
#define	UI_CHANGESIDERGB_NTY  ev_UIChangeSideRGBNty
	/************************************************************************/
	/** 设置颜色一致性RGB值通知界面 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UISetColorRGBInd,
#define	UI_SETCOLORRGB_IND  ev_UISetColorRGBInd

	/************************************************************************/
	/** 直接设置颜色一致性RGB值通知界面 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIDirectSetColorRGBInd,
#define	UI_DIRECT_SETCOLORRGB_IND  ev_UIDirectSetColorRGBInd

	/************************************************************************/
	/** 矩形长宽设置请求通知界面 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIChooseRectangleInd,
#define	UI_CHOOSERECTANGLE_IND  ev_UIChooseRectangleInd

	/************************************************************************/
	/** 恢复默认设置请求通知界面 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpSecDefaultNty,
#define	UI_MoonSecDefault_Nty  ev_TpSecDefaultNty

	/************************************************************************/
	/** 登录请求第二页数据通知界面 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpSecBoundaryNty,
#define	UI_SecBoundary_Nty  ev_TpSecBoundaryNty

	/************************************************************************/
	/** 设置增减梯形矫正参数值通知界面 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIChangeDistorInd,
#define	UI_CHANGEDISTORT_IND  ev_UIChangeDistorInd

	/************************************************************************/
	/** 直接设置梯形矫正参数值通知界面 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIDirectSetDistorInd,
#define	UI_DIRECTSETDISTORT_IND  ev_UIDirectSetDistorInd

	/************************************************************************/
	/** 软件版本信息通知界面 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpMoonToolVerInfo_Nty,
#define	UI_MOONTOOL_VERINFO_NTY  ev_TpMoonToolVerInfo_Nty

	/************************************************************************/
	/** 输出信号源通知界面 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpMoonToolCamOutputInfo_Nty,
#define	UI_MOONTOOL_CAMOUTPUT_INFO_NTY  ev_TpMoonToolCamOutputInfo_Nty

	/************************************************************************/
	/** 图片翻转信息通知界面 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpMoonToolCamImageAdjustInfo_Nty,
#define	UI_MOONTOOL_IMAGE_ADJUST_NTY  ev_TpMoonToolCamImageAdjustInfo_Nty

	/************************************************************************/
	/** 网络信息通知界面 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpMoonToolEthnetInfo_Nty,
#define	UI_MOONTOOL_ETHNETINFO_NOTIFY  ev_TpMoonToolEthnetInfo_Nty

	/************************************************************************/
	/** 设置时输出信号源通知界面 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpMoonToolCamOutputInfo_Ind,
#define	UI_MOONTOOL_CAMOUTPUT_INFO_IND  ev_TpMoonToolCamOutputInfo_Ind

	/************************************************************************/
	/** 图片翻转结果通知界面 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpMoonToolCamImageAdjustInfo_Ind,
#define	UI_MOONTOOL_IMAGE_ADJUST_IND  ev_TpMoonToolCamImageAdjustInfo_Ind

	/************************************************************************/
	/** 预置位列表通知消息 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpMoonToolCamPreSet_Nty,
#define	UI_MOONTOOL_CAMPRESET_NTY  ev_TpMoonToolCamPreSet_Nty

	/************************************************************************/
	/** 点击修改按钮后通知弹框窗口数据消息 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpMoonToolOrderPos_Modify,
#define	UI_MOONTOOL_ORDERPOS_MODIFY  ev_TpMoonToolOrderPos_Modify

	/************************************************************************/
	/** 通知主界面显隐标题栏消息 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpMoonToolListMenu_Option,
#define	UI_MOONTOOL_LISTMENU_OPTION  ev_TpMoonToolListMenu_Option

	/************************************************************************/
	/** 删除预置位后通知界面更新 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpMoonToolPreDel_Ind,
#define	UI_MOONTOOL_PREDEL_IND  ev_TpMoonToolPreDel_Ind

	/************************************************************************/
	/** 修改预置位后通知界面更新 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpMoonToolPreModify_Ind,
#define	UI_MOONTOOL_PREMODIFY_IND  ev_TpMoonToolPreModify_Ind

	/************************************************************************/
	/** 保存预置位后通知界面更新 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpMoonToolPreSet_Ind,
#define	UI_MOONTOOL_PRESET_IND  ev_TpMoonToolPreSet_Ind

	/************************************************************************/
	/** 底层发送默认值通知界面更新 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpMoonToolCamParamDefault_Ind,
#define	UI_MOONTOOL_CAMPARAMDEFAULT_IND  ev_TpMoonToolCamParamDefault_Ind

	/************************************************************************/
	/** 机芯升级回复通知界面
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_CamMechanismUpgrade_Ind,
#define	UI_CAMMECHANISM_UPGRADE_IND  ev_CamMechanismUpgrade_Ind

	/************************************************************************/
	/** 升级回复通知界面
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpMoonToolUpgrade_Ind,
#define	UI_MOONTOOL_UPGRADE_IND  ev_TpMoonToolUpgrade_Ind
	/************************************************************************/
	/** 波特率通知
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_TpMoonToolLVDSBaud_Ind,
#define	UI_MOONTOOL_LVDSBAUD_IND  ev_TpMoonToolLVDSBaud_Ind
	
	
	

	
	
	/************************************************************************/
	/** 参考线设置通知
	wparam 
	lparam */
	/************************************************************************/
	ev_TpReferenceLine_Ind,
#define	UI_MoonTool_ReferenceLine_IND  ev_TpReferenceLine_Ind
	/************************************************************************/
	/** 水平翻转设置通知
	wparam 
	lparam */
	/************************************************************************/
	ev_TpHorizontalFlip_Ind,
#define	UI_MoonTool_HorizontalFlip_IND  ev_TpHorizontalFlip_Ind
	/************************************************************************/
	/** 梯形矫正设置通知
	wparam  
	lparam */
	/************************************************************************/
	ev_TpTrapezoidalCor_Ind,
#define	UI_MoonTool_TrapezoidalCor_IND  ev_TpTrapezoidalCor_Ind
	/************************************************************************/
	/** 登录矩形显示设置通知
	wparam  
	lparam */
	/************************************************************************/
	ev_UIMoonShowRectRegion_Nty,
#define	UI_MoonTool_ShowRectRegion_NTY  ev_UIMoonShowRectRegion_Nty
	/************************************************************************/
	/** 矩形显示设置通知
	wparam  
	lparam */
	/************************************************************************/
	ev_UIMoonShowRectRegion_Ind,
#define	UI_MoonTool_ShowRectRegion_IND  ev_UIMoonShowRectRegion_Ind
	/************************************************************************/
	/** 颜色一致性开关设置通知
	wparam  
	lparam */
	/************************************************************************/
	ev_UIMoonTpColorSwich_Ind,
#define	UI_MoonTool_ColorSwitch_IND  ev_UIMoonTpColorSwich_Ind
	/************************************************************************/
	/** 梯形矫正参数值通知
	wparam  操作类型
	lparam = 0*/
	/************************************************************************/
	ev_TpTraCorValue_Ind,
#define	UI_MoonTool_TraCorValue_IND  ev_TpTraCorValue_Ind
	/************************************************************************/
	/** 快照操作通知
	wparam  操作类型
	lparam = 0*/
	/************************************************************************/
	ev_TpSnapShot_Ind,
#define	UI_MoonTool_SnapShot_IND  ev_TpSnapShot_Ind
	/************************************************************************/
	/** FTP下载快照进度通知
	wparam 
	lparam */
	/************************************************************************/
	ev_TpMoonToolFTPSnapDownLoad,
#define	WM_MoonTool_FTPSnapDownLoad  ev_TpMoonToolFTPSnapDownLoad
	/************************************************************************/
	/** 给预置位信息界面传递预置位列表
	wparam 
	lparam */
	/************************************************************************/
	ev_TpMoonToolPresetListParam_Ind,
#define	WM_MoonTool_PresetListParam_IND  ev_TpMoonToolPresetListParam_Ind	
	/************************************************************************/
	/** FTP下载预置位快照
	wparam 
	lparam */
	/************************************************************************/
	ev_TpMoonToolFTPPreSetSnapDownLoad,
#define	WM_MoonTool_FTP_PreSetSnapDownLoad  ev_TpMoonToolFTPPreSetSnapDownLoad

	/************************************************************************/
	/** MOON90 Gamma选择界面通知 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIMoonToolGammaSelectInd,
#define	UI_MOONTOOL_GammaStyleSel_IND  ev_UIMoonToolGammaSelectInd

	/************************************************************************/
	/** 防止在短时间内保存多个预制位 设置空间按钮
	wparam 
	lparam */
	/************************************************************************/
	ev_TpMoonToolStatusSet,
#define	WM_MoonTool_StatusSet  ev_TpMoonToolStatusSet

	/************************************************************************/
	/** 登陆时从服务器获取机芯类型
	wparam 
	lparam */
	/************************************************************************/
	ev_TpMechanismSelectNty,
#define	UI_TpMechanismSelect_NTY  ev_TpMechanismSelectNty

	/** 登陆时从服务器获取机芯版本号
	wparam 
	lparam */
	/************************************************************************/
	ev_TpMechVerNty,
#define	UI_TpMechVer_NTY  ev_TpMechVerNty

	/************************************************************************/
	/** 设置延时矫正通知界面 
	wparam TTPFpgaDelay具体信息
	lparam* BOOL/
	/************************************************************************/
	ev_UISetDelayCorrectInd,
#define	UI_SETDELAYCORRECT_IND  ev_UISetDelayCorrectInd
   
	/************************************************************************/
	/** 设置延时矫正通知界面 
	wparam TTPFpgaDelay
	lparam*/
	/************************************************************************/
	ev_UISetDelayCorrectNty,
#define	UI_SETDELAYCORRECT_NTY  ev_UISetDelayCorrectNty

    /************************************************************************/
	/** 预置位1保存结果通知界面 
	wparam 
	lparam*/
	/************************************************************************/
	ev_UICameraPreset1SaveRsp,
#define	UI_CAMERA_PRESET1_SAVE_RSP  ev_UICameraPreset1SaveRsp

};
//* @}*/
#endif 
