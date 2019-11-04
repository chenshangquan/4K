#ifndef _h_eventoutcnshduextend_h__
#define _h_eventoutcnshduextend_h__

#include "cnseventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmUMSCNSHDUEVENT
{
#endif 
	
	_ev_segment( outercnshduextend  )


/***********************<< 电视墙通知 >>********************	
 *[消息体]
 * TTpHduPlanPackData 
 *[消息方向]
 *  cnc <- cns, cns	 <-  ums
*/
_event(  ev_TpUMS_CNS_HduPlan_Nty  )
_body( TTpHduPlanPackData ,1 )			
_ev_end

/***********************<< 电视墙开启 >>********************	
 *[消息体]
 * TPAHduPlayReq 
 *[消息方向]
 *  cnc -> cns, cns	 ->  ums
*/
_event(  ev_TpCNS_UMS_HduPlay_Req  )
_body( TTpHduPlayReq ,1 )			
_ev_end

/***********************<< 开启电视墙回应 >>********************	
 *[消息体]
 * TPAHduPlayReq 
 * EmCnsHduPlayNackReason
 *[消息方向]
 *  cnc <- cns, cns	 <-  ums
*/
_event(  ev_TpUMS_CNS_HduPlay_Ind  )
_body( TTpHduBaseInfo ,1 )	
_body( EmCnsHduPlayNackReason ,1 )		
_ev_end

/***********************<< 停止选中电视墙 >>********************	
 *[消息体]
 * TPAHduPlayReq 
 *[消息方向]
 *  cnc -> cns, cns	 ->  ums
*/
_event(  ev_TpCNS_UMS_HduStopPlay_Req  )
_body( TTpHduPlayReq ,1 )			
_ev_end

/***********************<< 停止选中电视墙回应 >>********************	
 *[消息体]
 * TTpHduBaseInfo 
 *[消息方向]
 *  cnc <- cns, cns	 <-  ums
*/
_event(  ev_TpUMS_CNS_HduStopPlay_Ind  )
_body( TTpHduBaseInfo ,1 )	
_body( u16 ,1 )		//0:成功，非0：错误码
_ev_end

/***********************<< 停止全部电视墙 >>********************	
 *[消息体]
 * TTpHduSetVolInfo 
 *[消息方向]
 *  cnc -> cns, cns	 ->  ums
*/
_event(  ev_TpCNS_UMS_HduAllStopPlay_Req  )			
_ev_end

/***********************<< 设置电视墙vol >>********************	
 *[消息体]
 * TPAHduPlayReq 
 *[消息方向]
 *  cnc -> cns, cns	 ->  ums
*/
_event(  ev_TpCNS_UMS_HduSetVol_Req  )
_body( TTpHduSetVolInfo ,1 )			
_ev_end

/***********************<< 设置电视墙vol回应 >>********************	
 *[消息体]
 * TTpHduSetVolInfo 
 * EmCnsHduSetVolRes
 *[消息方向]
 *  cnc <- cns, cns	 <-  ums
*/
_event(  ev_TpUMS_CNS_HduSetVol_Ind  )
_body( TTpHduSetVolInfo ,1 )	
_body( EmCnsHduSetVolRes ,1 )		//0:成功，非0：错误码
_ev_end

/***********************<< 电视墙模式改变 >>********************	
 *[消息体]
 * TTpHduChanModeSetInfo 
 *[消息方向]
 *  cnc -> cns, cns	 ->  ums
*/
_event(  ev_TpHduChangeChanMode_Req  )
_body( TTpHduChanModeSetInfo ,1 )			
_ev_end

/***********************<< 电视墙模式改变回应 >>********************	
 *[消息体]
 * TTpHduChanModeSetInfo 
 * EmCnsHduChangeChanModeRes
 *[消息方向]
 *  cnc <- cns, cns	 <-  ums
*/
_event(  ev_TpHduChangeChanMode_Ind  )
_body( TTpHduChanModeSetInfo ,1 )
_body( EmCnsHduChangeChanModeRes ,1 )			
_ev_end

/***********************<<开关图标提示>>********************	
 *[消息体]
 
 *[消息方向]
 *  cnc -> cns
*/
_event(  ev_TpIconSwitch_Cmd  )
_body( BOOL ,1 )		
_ev_end

/***********************<< 开关图标回应 >>********************	
 *[消息体]
 
 *[消息方向]
 *  cns -> cnc
*/
_event(  ev_TpIconSwitch_Ind  )
_body( BOOL ,1 )	
_body( BOOL ,1 )	
_ev_end

/***********************<<设置画面裁剪  >>************************
	*[消息体]

	*[消息方向]
	*  cns	   -> cnmp
	*/
	_event( ev_TppSetVidCutLine )
	_body ( TTpVidCutLine, 1    )	
	_ev_end

	
	/***********************<<设置图标  >>************************
	*[消息体]

	*[消息方向]
	*  cns	   -> cnmp
	*/
	_event( ev_TppSetIcon )
	_body ( TTpIconInfo, 1    )	
	_ev_end

		/***********************<<设置音频监控类型  >>************************
	*[消息体]

	*[消息方向]
	*  cns	   -> cnmp
	*/
	_event( ev_TppSetMixType_Nty )
	_body ( TTpAudMix, 1    )
	_body ( u8, 1 )
	_ev_end

	
		/***********************<<设置音频监控类型  >>************************
	*[消息体]

	*[消息方向]
	*  cnc	   -> cns
	*/
	_event( ev_TppSetMixType_Cmd )
	_body ( EmAudMixType, 1    )	
	_body ( u8, 1 )
	_ev_end

		/***********************<<设置音频监控类型回应  >>************************
	*[消息体]

	*[消息方向]
	*  cns	   -> cnc
	*/
	_event( ev_TppSetMixType_Ind )
	_body ( EmAudMixType, 1    )	
	_body ( u8, 1 )
	_ev_end

		/***********************<<设置本地扩声请求  >>************************
	*[消息体]

	*[消息方向]
	*  cnc	   -> cns
	*/
	_event( ev_TppSetLocalAudExtend_Cmd )
	_body ( EmAudExtend, 1    )	
	_body ( u8, 1 )
	_ev_end

		/***********************<<设置本地扩声回应  >>************************
	*[消息体]

	*[消息方向]
	*  cns	   -> cnc
	*/
	_event( ev_TppSetLocalAudExtend_Ind )
	_body ( EmAudExtend, 1    )	
	_body ( u8, 1 )
	_ev_end

		/***********************<<设置本地扩声通知  >>************************
	*[消息体]

	*[消息方向]
	*  cns	   -> cnmp
	*/
	_event( ev_TppSetLocalAudExtend_Nty )
	_body ( BOOL, 1    )	
	_body ( u8, 1 )
	_ev_end

	
	/***********************<< 多点会议点名开启  >>********************	
	*[消息方向]	CNC->CNS,CNS	-->  UMS
	*
	*/
	_event(  evConfRollCallUpdate_Cmd )
	_body ( TTpConfRollCallInfo , 1 )	
	_ev_end
	
	
	
	/***********************<< 多点会议点名开启回应  >>********************	
	*[消息方向]	UMS	-->  CNS, CNS->CNC
	*
	*/
	_event(  evConfRollCallUpdate_Ind )	
	_body ( TTpConfRollCallInfo , 1 )
	_ev_end
	
	
	
	
	/***********************<< 点名下一个请求  >>********************	
	*[消息方向]	CNC->CNS, CNS	-->  UMS
	*
	*/
	_event(  evConfRollCallNextEp_Cmd )
	_body ( TTpRollCallNextEpInfo , 1 )	
	_ev_end
	
	
	
	/***********************<< 点名下一个回应  >>********************	
	*[消息方向]	UMS	-->  CNS, CNS->CNC
	*
	*/
	_event(  evConfRollCallNextEp_Ind )
	_body ( TTpRollCallNextEpInfo , 1 )	
	_ev_end

	
	/***********************<< 多点会议点名开启通知  >>********************	
	*[消息方向]	UMS	-->  CNS, CNS->CNC
	*
	*/
	_event(  evConfRollCallUpdate_Nty )
	_body ( TTpConfRollCallInfo , 1 )	
_ev_end

// 会议混音
/***********************<<  开启智能混音，开启定制混音，停止混音cmd消息共用 >>********************	
*[消息方向]	CNS	-->  UMS, CNS -->CNC
备注：开启智能混音、停止混音两种情形，忽略TUmsAudMixInfo里面的m_tMixList字段
*
*/
_event(  evConfAudMixMode_Cmd )
_body ( TTpAudMixInfo  , 1  )
_ev_end

/***********************<<  开启智能混音，开启定制混音，停止混音ind消息共用 >>********************	
*[消息方向]	UMS	-->  CNS, CNC -->CNS
*
*/
_event(  evConfAudMixMode_Ind ) 
_body ( TTpAudMixModeCmdRes  , 1  )
_ev_end

/***********************<< 修改混音成员列表cmd消息，非混音模式也有效 >>********************	
*[消息方向]	CNS	-->  UMS, CNS -->CNC
*
*/
_event(  evConfAudMixList_Cmd ) 
_body ( TTpAudMixListCmd  , 1  )
_ev_end

/***********************<<  修改混音成员列表cmd消息回应 >>********************	
*[消息方向]	UMS	-->  CNS, CNC -->CNS
*
*/
_event(  evConfAudMixList_Ind ) 
_body ( TTpAudMixListCmdRes  , 1  )
_ev_end


/***********************<<  会议混音通知消息 >>********************	
*[消息方向]	UMS	-->  CNS, CNC -->CNS
*
*/
_event(  evtpConfAudMixMode_Nty ) 
_body ( TTpAudMixInfo  , 1  )
_ev_end

/***********************<< 多点会议更新点名列表  >>********************	
*[消息方向]	CNS	-->  UMS
*
*/
_event(  evConfRollCallUpdataList_Cmd )
_body ( TTpUpdataRollCallList , 1 )	
_ev_end



/***********************<< 多点会议更新点名列表回应  >>********************	
*[消息方向]	UMS	-->  CNS
*
*/
_event(  evConfRollCallUpdataList_Ind )
_body ( TTpUpdataRollCallListRes , 1 )	
_ev_end



/***********************<<  主席更新点名答到情况 >>********************	
*[消息方向] CNS->UMS
*
*/
_event(  evtpRollUpdate_PresentState )
_body ( TTpRollCallPresentStateMsg  , 1  )	
_ev_end


/***********************<<  点名答到情况 同步 >>********************	
*[消息方向] UMS->CNS
*
*/
_event(  evtpRoll_PresentState_Nty )
_body ( TTpRollCallPresentStateMsg  , 1  )	
_ev_end

/***********************<<设置画面裁剪请求  >>************************
*[消息体]
*[消息方向]
*  cnc	   -> cns
*/
_event( ev_TppSetVidCutLine_Cmd )
_body ( BOOL, 1    )	
_ev_end

/***********************<<设置画面裁剪回应  >>************************
*[消息体]
*[消息方向]
*  cnc	   -> cns
*/
_event( ev_TppSetVidCutLine_Ind )
_body ( BOOL, 1    )
_body ( BOOL, 1    )	
_ev_end

/***********************<<Tptools抓包提醒  >>************************
*[消息体]
*[消息方向]
*  cnc	   -> cns
*/
_event( ev_TppToolgetPak_Cmd )
_body ( BOOL, 1    )	
_ev_end
/***********************<<抓包拒绝抢登  >>************************
*[消息体]
*[消息方向]
*  cns	   -> cnc
*/
_event( ev_TppRefuseLogin_Nty )	
_body(u32_ip, 1)
_ev_end
/***********************<<发言人设置发言坐席  >>************************
*[消息体]
*[消息方向]
*  cnc	   -> cns
*/
_event(  ev_CnSetSayState )
_body( u8, 1 )
_ev_end
/***********************<<是否在混音状态通知  >>************************
*[消息体]
*[消息方向]
*  cns	   -> cnc
*/
_event(  ev_EpInAudMix_Nty )
_body( BOOL32, 1 )
_ev_end
/***********************<<设置图标参数  >>************************
*[消息体]
*[消息方向]
*  cnc	   -> cns
*/
_event(  ev_CnSetIconCfg_cmd )
_body( EmIconType, 1 )
_ev_end
/***********************<<关闭图标  >>************************
*[消息体]
*[消息方向]
*  cnc	   -> cns
*/
_event(  ev_CnCloseIconCfg_cmd )
_body( EmIconType, 1 )
_ev_end

/***********************<<查询图标  >>************************
*[消息体]
*[消息方向]
*  cnc	   -> cns
*/
_event(  ev_CnIconShow )
_ev_end

/***********************<< 量子加密服务器配置设置请求  >>********************	
  *[消息体]
  *TTpQtEncryptCfg 量子加密信息
  *[消息方向]	  CNC	-->  CNS
  *
  */
  _event( ev_tppSetQtEncryptInfo_Cmd )
  _body( TTpQtEncryptCfg, 1 )
  _ev_end

  /***********************<< 量子加密服务器配置设置通知  >>********************	
  *[消息体]
  *TTpQtEncryptCfg 量子加密信息
  *[消息方向]	  CNC	-->  CNS
  *
  */
  _event( ev_tppSetQtEncryptInfo_Nty )
  _body( TTpQtEncryptCfg, 1 )
  _ev_end

   /***********************<< 量子加密服务器配置设置响应  >>********************	
  *[消息体]
  *TTpQtEncryptCfg 量子加密信息
  *BOOL 量子加密信息是否写到配置文件
  *[消息方向]	  CNS	-->  CNC
  *
  */
  _event( ev_tppSetQtEncryptInfo_Ind )
  _body( TTpQtEncryptCfg, 1 )
  _body( BOOL, 1 )
  _body( u8, 1 )
  _ev_end

  /***********************<< 多点会场发送323终端视频源给cnc  >>*****************
  *[消息体]
  *TConfVidFeccInfo 多点会场视频源信息
  *[消息方向] CNS-->CNC
  *
  */
  _event( ev_SendFeccVidSrcInfo_Nty )
  _body( TConfVidFeccInfo, 1 )
  _ev_end

     /***********************<< 画面合成时配置小画面尺寸  >>********************	
  *[消息体]
  *EmMeetingRoomType 小画面尺寸
  *[消息方向]     cns	-->	 cnmp
  */
  _event( ev_CnSetMeetingRoomType_Cmd )
  _body( EmTpVideoResolution, 1 )
  _ev_end

   /***********************<< 矩阵服务器信息配置通知  >>********************	
  *[消息体]
  *TTPMatrixServerInfo 矩阵服务器信息
  *[消息方向]	 cns   -->   tptools
  */
  _event( ev_CnSetMatrixServerInfo_Nty )
  _body( TTPMatrixServerInfo, 1 )
  _ev_end

     /***********************<< 矩阵服务器信息配置请求  >>********************	
  *[消息体]
  *TTPMatrixServerInfo 矩阵服务器信息
  *[消息方向]	tptools   -->   cns
  */
  _event( ev_CnSetMatrixServerInfo_Cmd )
  _body( TTPMatrixServerInfo, 1 )
  _ev_end

     /***********************<< 矩阵服务器信息配置回应  >>********************	
  *[消息体]
  *TTPMatrixServerInfo 矩阵服务器信息
  *[消息方向]	cns   -->   tptools
  */
  _event( ev_CnSetMatrixServerInfo_Ind )
  _body( TTPMatrixServerInfo, 1 )
  _body( BOOL, 1 )
  _ev_end

       /***********************<< 桌面麦克风开关配置通知  >>********************	
  *[消息体]
  *TTPDesktopMicInfo 桌面麦克风信息
  *[消息方向]	cns   -->   tptools
  */
  _event( ev_CnSetDesktopMicInfo_Nty )
  _body( BOOL, 1 )
  _ev_end

       /***********************<< 桌面麦克风开关配置请求  >>********************	
  *[消息体]
  *TTPDesktopMicInfo 桌面麦克风信息
  *[消息方向]	tptools   -->   cns
  */
  _event( ev_CnSetDesktopMicInfo_Cmd )
  _body( BOOL, 1 )
  _ev_end
         /***********************<< 桌面麦克风开关配置回应  >>********************	
  *[消息体]   
  *TTPDesktopMicInfo 桌面麦克风信息
  *[消息方向]	cns   -->   tptools
  */
  _event( ev_CnSetDesktopMicInfo_Ind )
  _body( BOOL, 1 )
  _body( BOOL, 1 )
  _ev_end

  /***********************<< 设置Telnet服务请求  >>********************	
  *[消息体]   
  *
  *[消息方向]	cns   -->   tptools
  */
  _event( ev_CnSetTelnet_Req )
  _body( TTPTelnetInfo, 1 ) 
  _ev_end
  
  /***********************<< 设置Telnet服务回应  >>********************	
  *[消息体]   
  *
  *[消息方向]	cns   -->   tptools
  */
  _event( ev_CnSetTelnet_Rsp )
  _body( TTPTelnetInfo, 1 )
  _body( BOOL, 1 ) 
  _ev_end
  
  /***********************<< 设置FTP服务请求  >>********************	
  *[消息体]   
  *
  *[消息方向]	cns   -->   tptools
  */
  _event( ev_CnSetFtp_Req )
  _body( TTPFtpInfo, 1 ) 
  _ev_end
  
  /***********************<< 设置FTP服务回应  >>********************	
  *[消息体]   
  *
  *[消息方向]	cns   -->   tptools
  */
  _event( ev_CnSetFtp_Rsp )
  _body( TTPFtpInfo, 1 )
  _body( BOOL, 1 ) 
  _ev_end
  
  _event(  ev_CnCfgSetTelnet_Cmd )
  _body  ( TTPTelnetInfo, 1 )
  _ev_end
  
  _event(  ev_CnCfgSetTelnet_Nty )
  _body ( TTPTelnetInfo, 1 )
  _ev_end

  _event(  ev_CnTelnetInfo_Nty )
  _body  ( TTPTelnetInfo, 1 )
  _ev_end

  _event(  ev_CnFtpInfo_Nty )
  _body  ( TTPFtpInfo, 1 )
  _ev_end

    /***********************<< 设置双网络信息 >>********************** 
*[消息体]
+TTPEthnetInfo		CNS网络配置信息
*[消息方向]
*  cnc	  -> cns
*/
  _event( ev_CnCfgWEthnet_Cmd )
  _body(TTPWEthnetInfo, 1 )
  _body(EmTpIpNameNatSyn, 1 )
  _ev_end

  _event( ev_CnCfgWEthnet_Rsp )
  _body(TTPWEthnetInfo, 1 )
  _body(EmTpIpNameNatSyn, 1 )
  _body( BOOL, 1 )
  _ev_end

  _event( ev_CnCfgWEthnet_Nty )
  _body(TTPWEthnetInfo, 1 ) 
  _ev_end
   //以下内部使用
  _event( ev_CnCfgEthnet1_Cmd )
  _body(TTPEthnetInfo, 1 )
  _body(EmTpIpNameNatSyn, 1 )
  _ev_end

  _event( ev_CnCfgEthState_Nty )
  _body(EmEthState, 1 )
  _ev_end

  _event( ev_CnSetMicPower_Cmd )
  _body(u8, 1 )
  _body(BOOL, 1 )
  _ev_end

  _event( ev_CnSetMicPower_Rsp )
  _body(u8, 1 )
  _body(BOOL, 1 )
  _body(BOOL, 1 )
  _ev_end

  _event( ev_CnMicPower_Nty )
  _body(TTpMicState, 1 )
  _ev_end

  _event( ev_CnMicPowerStyle_Nty )
  _body(TTpMicState, 1 )
  _ev_end

  _event( ev_CnMicPowerIner_Nty )
  _body(TTpMicState, 1 )
  _ev_end

  /***********************<< 通知323终端视频源给cnc  >>*****************
  *[消息体]
  *TConfVidFeccInfo 多点会场视频源信息
  *[消息方向] CNS-->CNC
  *
  */
  _event( ev_SendFeccVidSrcInfo_Ind )
  _body( TConfVidFeccInfo, 1 )
  _ev_end

  /***********************<< 修改矩阵名字 >>********************	
  *[消息体]
  * TTpSuperUser
  *[消息方向]
  *  cnc	  -> cns
  */
  _event(  ev_tppChangeMatrixName_Cmd )
  _body( TTPMatrixName, 1 )
  _ev_end
  /***********************<< 修改矩阵名字回复 >>********************	
  *[消息体]
  * TTpSuperUser
  *[消息方向]
  *  cnc	  -> cns
  */
  _event(  ev_tppChangeMatrixName_Ind )
  _body( TTPMatrixName, 1 )
  _body( BOOL, 1 )
  _ev_end
  /***********************<< 设置发送对端主视频源只主 >>********************	
  *[消息体]
  * TTpSuperUser
  *[消息方向]
  *  cnc	  -> cns
  */
  _event(  ev_tppSetMainSrc_Cmd )  
  _body( u8, 1 )
  _ev_end
  /***********************<< 设置发送对端主视频源只主 回复>>********************	
  *[消息体]
  * TTpSuperUser
  *[消息方向]
  *  cnc	  -> cns
  */
  _event(  ev_tppSetMainSrc_Ind )  
  _body( u8, 1 )
  _body( BOOL, 1 )
  _ev_end

  /***********************<< 设置回显本地（含设置和取消）>>********************	
   *[消息体]
   * TTpSuperUser
   *[消息方向]
   *  cnc	  -> cns
   */
   _event(  ev_tppSetViewSrc_Cmd ) 
   _body( TTPSlectView, 1 ) 
   _ev_end
         /***********************<< 设置回显本地回复>>********************	
   *[消息体]
   * TTpSuperUser
   *[消息方向]
   *  cnc	  -> cns
   */
   _event(  ev_tppSetViewSrc_Ind ) 
   _body( TTPSlectView, 1 )
   _body( BOOL, 1 )
   _ev_end

            /***********************<< SDK信息通知cnmp>>********************	
   *[消息体]
   * TTpSuperUser
   *[消息方向]
   *  cnc	  -> cns
   */
   _event(  ev_tppSdkVersion_Nty ) 
   _body( BOOL, 1 )
   _body( EmTPMtVideoPort, 1 )
   _ev_end

     /***********************<< 设置发送对端主视频源只主 通知>>********************	
  *[消息体]
  * TTpSuperUser
  *[消息方向]
  *  cnc	  -> cns
  */
  _event(  ev_tppSetMainSrc_Nty )  
  _body( u8, 1 ) 
  _ev_end
    /***********************<< SDK版本告知>>********************	
  *[消息体]
  * TTpSuperUser
  *[消息方向]
  *  cnc	  -> cns
  */
  _event(  ev_tppIsSdk_Nty )  
  _ev_end

  //删除root账户
  _event( ev_CnDelRoot_Cmd )
  _ev_end
  //删除root账户定时器
  _event( ev_CnDelRootTimer )
  _ev_end
  

#ifndef _MakeTpEventDescription_
		_ev_segment_end( outercnshduextend )
};
#endif
#endif 