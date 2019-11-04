#ifndef _h_eventoutcnssys_h__
#define _h_eventoutcnssys_h__

#include "cnseventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmCNSSYSEVENT
{
#endif 

  _ev_segment( outercnssys  )
/***********************<< CNS协议栈初始化结果通知 >>********************** 
*[消息体]
* BOOL 初始化是否成功
*[消息方向]
*  cncall	  -> cns
*/
	  _event(  ev_tppCnProtocalInit_Nty )
	  _body( BOOL, 1 )
_ev_end

/***********************<< 通知会场上线 >>********************** 
*[消息体]
+s8[]		会场名
*[消息方向]
*  cns	  -> cnc
*/
_event( ev_tpRoomOnline_Nty )
_body( s8, TP_MAX_NAME_LEN+1)
_ev_end

/***********************<< 通知会场下线 >>********************** 
*[消息体]
+s8[]		会场名
*[消息方向]
*  cns	  -> cnc
*/
_event( ev_tpRoomOffline_Nty )
_body( s8, TP_MAX_NAME_LEN+1)
_ev_end

/***********************<< 设置cns时间 >>********************** 
*[消息体]
+TTPTime		
*[消息方向]
*  cns	  <- cnc
*/
_event( ev_CnSetSysTime_Cmd )
_body( TTPTime, 1 )
_ev_end

/***********************<< 查询cns时间 >>********************** 
*[消息体]
*NULL
*[消息方向]
*  cns	  <- cnc
*/
_event( ev_CnGetSysTime_Req)
_ev_end


/***********************<< 查询cns时间响应 >>********************** 
*[消息体]
+TTPTime
*[消息方向]
*  cns	  -> cnc
*/
_event( ev_CnGetSysTime_Rsp)
_body( TTPTime, 1 )
_ev_end



//============tp_sp1 消息定义

//登录
/***********************<< 通知cn列表 >>********************** 
*[消息体]
+TTPCnList
*[消息方向]
*  cns	  -> cnc
*/
_event( ev_CnList_Nty)
_body( TTPCnList, 1 )
_ev_end

 /***********************<< 登录请求 >>********************** 
 *[消息体]
 *[消息方向]
 注 userdata中包含insid
 *  cnc	  -> cns
*/
_event(  ev_CnLoginIns_Req )
_ev_end

 /***********************<< 登录请求回应 >>********************** 
 *[消息体]
+TLoginRet  登录信息
 注 userdata中包含insid
 *[消息方向]
 *  cnc	 <- cns,  tool <- cns
*/
_event(  ev_CnLoginIns_Rsp )
_body(TLoginRet,	1)
_ev_end

 /***********************<< 重启延时定时器 >>********************** 
 *[消息体]
 *NULL
 *[消息方向]
 *  cns	 <- cns
*/
//
_event(  ev_CnRebootDelay_Timer )
_ev_end

 //登录
 /***********************<< 登录请求 >>********************** 
 *[消息体]
 *NULL
 *[消息方向]
 *  cnc	  -> cns, tool -> cns 
*/
_event(  ev_CnLogin_Req )
//_body( CLoginRequest, 1 )
_ev_end

 /***********************<< 登录请求回应 >>********************** 
 *[消息体]
+TLoginRet  登录信息
 *[消息方向]
 *  cnc	  <- cns， cns -> tool
*/
_event(  ev_CnLogin_Rsp )
_body(TLoginRet,	1)
_ev_end

 /***********************<< 配置会场信息命令 >>********************** 
 *[消息体]
+TTPCnsInfo  会场信息
+u8   0 : CNC消息，1: 维护工具消息
 *[消息方向]
 *  cnc	  ->  cns
*/
_event(  ev_CnCfgCnsInfo_Cmd )
_body( TTPCnsInfo,	1 )
_body( u8,	1 )
_body(EmTpIpNameNatSyn, 1 )
_ev_end
//配置
/***********************<< 通知会场信息 >>********************** 
*[消息体]
+TTPCnsInfo		CNS信息
+EmTPCNSInfoRst 配置会场信息结果
*[消息方向]
*  cns	  -> cnc , cns -> tool
*/
_event(  ev_CnCfgCnsInfo_Ind )
_body( TTPCnsInfo,	1 )
_body( EmTPCNSInfoRst,	1 )
_ev_end


/***********************<< 设置网络信息 >>********************** 
*[消息体]
+TTPEthnetInfo		CNS网络配置信息
*[消息方向]
*  cnc	  -> cns
*/
_event( ev_CnCfgEthnet_Cmd )
_body(TTPEthnetInfo, 1 )
_body(EmTpIpNameNatSyn, 1 )
_ev_end

/***********************<< 通知网络回应 >>********************** 
*[消息体]
+TTPEthnetInfo		CNS网络配置信息
*[消息方向]
*  cns	  -> cnc
*/
_event(  ev_CnCfgEthnet_Ind )
_body(TTPEthnetInfo, 1 )
_ev_end
 
//通知cnc

/***********************<< 修改主会场名命令 >>********************** 
*[消息体]
+s8		会场名
*[消息方向]
*  cns	  <- cnc
*/
_event( ev_CnSetMainRoom_Cmd )
_body( s8, TP_MAX_NAME_LEN+1 )
_ev_end

/***********************<< 修改主会场名响应 >>********************** 
*[消息体]
+s8		会场名
*[消息方向]
*  cns	  ->  cnc
*/
_event( ev_CnSetMainRoom_Ind )
_body( s8, TP_MAX_NAME_LEN+1 )
_ev_end
 

/***********************<< 通知修改会场名 >>********************** 
*[消息体]
+s8 会场名
*[消息方向]
*  cnc	  -> cns
*/
_event(  ev_CnSetRoomName_Cmd )
_body( s8, TP_MAX_ALIAS_LEN + 1 )
_body( EmTpIpNameNatSyn, 1)
_ev_end

/***********************<< 通知修改会场名完成 >>********************** 
*[消息体]
+s8 会场名
*[消息方向]
*  cns	  -> cnc
*/
_event(  ev_CnSetRoomName_Ind )
_body( s8, 1 )
_ev_end

/***********************<< 双流掉线通知 >>********************** 
*[消息体]
+NULL
*[消息方向]
*  cns	  -> cnc
*/
_event(  ev_tpCnRoomDualOffline_Nty )
_ev_end

/***********************<< 静态NAT回应 >>********************** 
*[消息体]
*TTPNatCfg 静态Nat配置
*[消息方向]
*  cns	  -> cnc
*/
_event( ev_tppNatReg_Nty )
_body(TTPNatCfg, 1)
_ev_end

/***********************<< 设置Nat >>********************** 
*[消息体]
*TTPNatCfg 静态Nat配置
*[消息方向]
*  cnc	  -> cns
*/
_event( ev_tppNatReg_Cmd )
_body(TTPNatCfg, 1)
_body(EmTpIpNameNatSyn, 1 )
_ev_end

 /***********************<<系统升级请求 >>************************	
 *[消消息体]			 
 *  TTPVerFileInfo cns升级文件信息
 *[消息方向]
 *    cns <= AGENT，cnc -> cns,  cns -> cns
 */
 _event(  ev_CnUpdateSystem_Cmd  )
 _body ( TTPFTPFileInfo, 1 )
 _ev_end

/***********************<<Tpad升级命令 >>********************** 
*[消息体]
*EmTPUpdateType    TPad升级方式
*TTPTPadVerInfo    TPad的版本信息
*[消息方向]
*   cns -> cnc
*/
  _event( ev_TpadUpdateSystem_Cmd )
  _body(TTPTPadVerInfo ,1)
  _ev_end

/***********************<<Cns通知界面cns的升级类型 >>********************** 
*[消息体]
*EmTPUpdateType  CNS的升级类型
*[消息方向]
*   cns -> cnc
*/
  _event( ev_CnUpdateSystemType_Nty )
  _body(EmTPUpdateType, 1)
  _ev_end

/***********************<<cns的升级结果 >>********************** 
*[消息体]
*BOOL  CNS升级的结果
*[消息方向]
*   cns -> cnc , cnupdate->cnagent
*/
  _event( ev_CnUpdateSystemFile_Ind )
  _body(BOOL, 1)
  _ev_end

  /***********************<<cns的升级结果 >>********************** 
  *[消息体]
  *BOOL  CNS升级的结果
  *[消息方向]
  *   cns -> cns 
  */
  _event( ev_CnUpdateStart_Nty )
  _body(s32, 1)
  _ev_end

  /***********************<<  配置网口命令 >>********************	
  *[消息体]
  * +u8 , 1  //网口的index
  *  
  *[消息方向]
  *  cns -> cns
  */_event(   ev_CfgNetInfSelCmd )
  _body( u8 , 1 )
  _ev_end
   

    /***********************<<  定时检测系统时间 >>********************	
  *[消息体]
  *[消息方向]
  *  cns -> cns
  */_event(   ev_CheckSysTime_Timer )
  _ev_end

   /***********************<< 设置会议视频优选格式，单选 >>********************	
  *[消息体]
  *TTPVidForamt 视频优选格式和分辨率类型
  *[消息方向]
  *  cnc -> cns,  tptool -> cns
  */
  _event(ev_CnCfgVideoFormat_Cmd)
  _body(TTPVidForamt, 1)
  _ev_end

  /***********************<< 设置会议优选格式，单选 >>********************	
  *[消息体]
  *TTPVidForamt 视频优选格式和分辨率类型
  *[消息方向]
  *  cns -> cnc, cns->tptool
  */
  _event(ev_CnCfgVideoFormat_Ind)
  _body(TTPVidForamt, 1)
  _ev_end

  /***********************<< 设置演示优选格式，单选 >>********************	
  *[消息体]
  *TTPVidForamt 视频优选格式和分辨率类型
  *[消息方向]
  *  cnc -> cns,  tptool -> cns
  */
  _event(ev_CnCfgDualVideoFormat_Cmd)
  _body(TTPVidForamt, 1)
  _ev_end

   /***********************<< 设置会议优选格式，单选 >>********************	
  *[消息体]
  *TTPVidForamt 视频优选格式和分辨率类型
  *[消息方向]
  *  cns -> cnc, cns->tptool
  */
  _event(ev_CnCfgDualVideoFormat_Ind)
  _body(TTPVidForamt, 1)
  _ev_end

  /***********************<< 设置单屏码率 >>********************	
  *[消息体]
  *u16 呼叫码率
  *[消息方向]
  *  cnc -> cns,  tptool -> cns
  */
  _event(ev_CnCfgCallRate_Cmd)
  _body(u16, 1)
  _ev_end

   /***********************<< 设置单屏码率 >>********************	
  *[消息体]
  *u16 呼叫码率
  *[消息方向]
  *  cns -> cnc, cns->tptool
  */
  _event(ev_CnCfgCallRate_Ind)
  _body(u16, 1)
  _ev_end

  /***********************<< 设置演示码率 >>********************	
  *[消息体]
  *u16 演示码率
  *[消息方向]
  *  cnc -> cns,  tptool -> cns
  */
  _event(ev_CnCfgDualCallRate_Cmd)
  _body(u16, 1)
  _ev_end

   /***********************<< 设置演示码率 >>********************	
  *[消息体]
  *u16 呼叫码率
  *[消息方向]
  *  cns -> cnc, cns->tptool
  */
  _event(ev_CnCfgDualCallRate_Ind)
  _body(u16, 1)
  _ev_end

  /***********************<< 设置会议轮询是否开启 >>********************	
  *[消息体]
  *TTPPollInfo 轮询信息
  *[消息方向]
  *  cnc -> cns,  tptool -> cns
  */
  _event(ev_CnCfgConfPoll_Cmd)
  _body(TTPPollInfo, 1)
  _ev_end

   /***********************<< 设置会议轮询是否开启 >>********************	
  *[消息体]
  *TTPPollInfo 轮询信息
  *[消息方向]
  *  cns -> cnc, cns->tptool
  */
  _event( ev_CnCfgConfPoll_Ind)
  _body(TTPPollInfo, 1)
  _ev_end

  /***********************<< 设置会议讨论是否开启 >>********************	
  *[消息体]
  *BOOL 是否开启讨论
  *[消息方向]
  *  cnc -> cns,  tptool -> cns
  */
  _event(ev_CnCfgConfDis_Cmd)
  _body(BOOL, 1)

  _ev_end

   /***********************<< 设置会议讨论是否开启 >>********************	
  *[消息体]
  *Bool 是否开启讨论
  *[消息方向]
  *  cns -> cnc, cns->tptool
  */
  _event( ev_CnCfgConfDis_Ind)
  _body(BOOL, 1)
  _ev_end

   /***********************<< 通知显示软件版本信息 >>********************	
  *[消息体]
  *Bool 是否开启讨论
  *[消息方向]
  * cns->tptool
  */
  _event( ev_CnVerInfo_Nty)
  _body(s8, MAX_DEVICEVER_LEN)
  _body( EmCnModel, 1)		//add byfanxiaobo 终端型号
  _ev_end

  /***********************<< 设置会议音频类型 >>********************** 
  *[消息体]	
  * EmTpAudioFormat				音频类型		
  *[消息方向]
  *  cnc	  ->  cns
  */
  _event(  ev_CnCfgAudioFormat_Cmd )
  _body( EmTpAudioFormat, 1 )
  _ev_end

  /***********************<< 设置会议音频类型 >>********************** 
  *[消息体]	
  * EmTpAudioFormat				音频类型		
  *[消息方向]
  *  cns	  ->  cnc
  */
  _event(  ev_CnCfgAudioFormat_Ind )
  _body( EmTpAudioFormat, 1 )
  _ev_end

   /***********************<< 设置显示器类型 >>********************** 
  *[消息体]	
  *BOOL                         是否显示电视墙
  * TTPDisplayType				显示器配置类型(显示器1的配置放在第一个消息体中，显示器2的配置放在第二个消息体中)		
  *[消息方向]
  *  cnc	  ->  cns
  *电视墙服务开启时，支持配置分别显示器1、3的信号源
  */
  _event(  ev_CnCfgDisplay_Cmd )
  _body (BOOL, 1)
  _body( TTPDisplayType, 2 )
  _ev_end

  /***********************<< 设置显示器类型 >>********************** 
  *[消息体]	
  *BOOL                         是否显示电视墙
  * TTPDisplayType				显示屏配置类型(显示器1的配置放在第一个消息体中，显示器2的配置放在第二个消息体中)		
  *[消息方向]
  *  cnc	  <-  cns
  *电视墙服务开启时，支持配置分别显示器1、3的信号源
  */
  _event(  ev_CnCfgDisplay_Ind )
  _body (BOOL, 1)
  _body( TTPDisplayType, 2 )
  _body ( BOOL, 1 )
  _ev_end

  /***********************<< 设置会议语音激励是否开启命令 >>********************	
  *[消息体]
  *BOOL 是否开启语音激励
  *[消息方向]
  *  cnc -> cns
  */
  _event(ev_CnMixIsUsed_Cmd)
  _body(BOOL, 1)

  _ev_end

   /***********************<< 设置会议语音激励是否开启反馈 >>********************	
  *[消息体]
  *BOOL 是否开启语音激励
  *Bool 开启结果
  *[消息方向]
  *  cns -> cnc
  */
  _event( ev_CnMixIsUsed_Ind)
  _body(BOOL, 1)
  _body(BOOL, 1)
  _ev_end

   /***********************<< 设置显示器配置界面显示 >>********************** 
  *[消息体]	
  *BOOL                         是否显示					
  *[消息方向]
  *  cnc	  ->  cns
  */
  _event(  ev_CnCfgDisplayShow_Nty )
  _body (BOOL, 1)
  _ev_end

   /***********************<< 设置显示器配置界面显示 >>********************** 
  *[消息体]	
  *BOOL                         是否显示					
  *[消息方向]
  *  cnc	  ->  cns
  */
  _event(  ev_CnCfgDisplayShow_Cmd )
  _body (BOOL, 1)
  _ev_end

   /***********************<< 设置显示器配置界面显示 >>********************** 
  *[消息体]	
  *BOOL                         是否显示					
  *[消息方向]
  *  cnc	  ->  cns
  */
  _event(  ev_CnCfgDisplayShow_Ind )
  _body (BOOL, 1 )
  _body( BOOL, 1 )
  _ev_end

#ifndef _MakeTpEventDescription_
  _ev_segment_end( outercnssys )
};

#endif
#endif //TPP_EVENT_H
