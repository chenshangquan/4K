#ifndef _h_eventoutcnstool_h__
#define _h_eventoutcnstool_h__


#include "tpeventcomm.h"


#ifndef _MakeTpEventDescription_
enum EmCNSTOOLEVENT
{
#endif
	
	_ev_segment( outercnstool )

/***********************<<  Tool请求CNS获取当前系统信息 >>********************
*[消息体]
*NULL	
 *[消息方向]	Tool	-->  CNS
 *
 */
 _event(  ev_tppGetSysInfo_Req )
 _ev_end

/***********************<<  CNS响应Tool获取系统信息 >>********************
*[消息体]
*TTPSysInfo 系统使用信息	
 *[消息方向]	CNS	-->  Tool
 *
 */_event(  ev_tppGetSysInfo_Rsp )
	_body ( TTPSysInfo  , 1  )
   _ev_end

/***********************<<  CNS通知Tool当前系统信息 >>********************	
*[消息体]
*TTPSysInfo 系统使用信息
 *[消息方向]	CNS	-->  Tool
 *
 */_event(  ev_tppGetSysInfo_Nty )
	_body ( TTPSysInfo  , 1  )
   _ev_end

/***********************<<  Tool请求CNS获取TPad列表 >>********************
*[消息体]
*NULL	
 *[消息方向]	Tool	-->  CNS
 *
 */
_event(  ev_tppGetTPadIpList_Req )
_ev_end

/***********************<<  CNS响应Tool获取TPad列表 >>********************
*[消息体]
*TTPTPadList TPad列表	
 *[消息方向]	CNS	-->  Tool
 *
 */
_event(  ev_tppGetTPadIpList_Rsp )
_body ( TTPTPadList  , 1  )
_ev_end

/***********************<<  CNS通知Tool当前TPad列表发生改变 >>********************	
*[消息体]
*TTPTPadList TPad列表
*s8 TPad版本号
 *[消息方向]	CNS	-->  Tool
 *
 */
_event(  ev_tppGetTPadIpList_Nty )
_body ( TTPTPadList  , 1  )	
_ev_end

/***********************<<  会议信息通知 >>********************	
*[消息体]
*TTPCnsConfStatus 会场状态
*TCnVideoParam 视频参数
 *[消息方向]	CNS	-->  Tool
 *
 */
_event(  ev_tppCnConfInfo_Nty )
_body ( TTPCnsConfStatus  , 1  )
_body ( TTPCnConfInfo , 1 )
_ev_end

/***********************<< T300升级命令  >>********************	
*[消息体]
*TTPVerFileInfo 升级文件信息
*[消息方向]	Tool	-->  CNS
*
*/
_event(  ev_tppUpdate_Cmd )
_body ( TTPFTPFileInfo , 1 )
_ev_end


/***********************<<  T300升级回应 >>********************	
*[消息体]
*BOOL 升级结果
*[消息方向]	CNS 	-->  Tool
*
*/
_event(  ev_tppUpdate_Ind )
_body ( BOOL  , 1  )	
_ev_end

/***********************<<  音频接口配置命令  >>********************	
*[消息体]
*TTpAudioPortInfo 3路主音频接口信息
*[消息方向]	Tool	-->  CNS
*
*/
_event(  ev_tppSetAudioPort_Cmd )
_body ( TTpAudioPortInfo  , 3  )		
_ev_end


/***********************<<  音频接口配置回应 >>********************	
*[消息体]
*TTpAudioPortInfo 3路主音频接口信息
*BOOL 设置是否成功
 *[消息方向]	CNS	-->  Tool
 *
 */
_event(  ev_tppSetAudioPort_Ind )
_body ( TTpAudioPortInfo  , 3  )
_body ( BOOL, 1 )	
_ev_end


/***********************<<  音视频选择矩阵方案命令 >>********************	
*[消息体]
*TTPVgaMixInfo
*[消息方向]	   Tool	-->  CNS
*
*/
_event(  ev_tppSelAVMatrixProject_Cmd )
_body ( TTPVgaMixInfo  , 1  )
_ev_end

/***********************<< 音视频选择矩阵方案回应  >>********************	
*[消息体]
*TTPVideoDiagInfo 视频诊断接口信息
*TTPAudioDiagInfo 音频诊断接口信息
*[消息方向]	  CNS	-->  Tool
*
*/
_event(  ev_tppSelAVMatrixProject_Ind )
_body ( TTPVideoDiagInfo  , 1  )
_body ( TTPAudioDiagInfo  , 1  )	
_ev_end

/***********************<< 获取丢包信息请求  >>********************	
*[消息体]
*NULL
*[消息方向]	  Tool	-->  CNS
*
*/
_event(  ev_tppGetLostPacketInfo_Req )
_ev_end

/***********************<< 获取丢包信息响应  >>********************
*[消息体]
*u32
*u32
*[消息方向]	  CNS	-->  Tool
*
*/
_event(  ev_tppGetLostPacketInfo_Rsp )
_body ( u32  , 1  )
_body ( u32  , 1  )
_ev_end

/***********************<< 检测上下行网络速率通知  >>********************
*[消息体]
*TTPUpDownSpeedInfo	上下行网络速率
*[消息方向]	  CNS	-->  Tool
*
*/
_event(  ev_tppGetUpDownstreamRate_Nty )
_body ( TTPUpDownSpeedInfo  , 1  )
_ev_end

/***********************<< 导入地址簿请求  >>********************
*[消息体]
*NULL	
*[消息方向]	  Tool	-->  CNS
*
*/
_event(  ev_tppImportAddr_Req )
_ev_end

/***********************<< 导入地址簿响应  >>********************	
*[消息体]
*BOOL 导入地址簿结果
*[消息方向]	  CNS	-->  Tool
*
*/
_event(  ev_tppImportAddr_Rsp )
_body ( BOOL  , 1  )
_ev_end

/***********************<< 重启CNS通知  >>********************	
*[消息体]
*NULL
*[消息方向]	  Tool	-->  CNS
*
*/
_event(  ev_tppReboot_Nty )
_ev_end

/***********************<< 获取系统信息定时器  >>********************	
*[消息体]
*NULL
*[消息方向]	  Tool	-->  CNS
*
*/
_event(  ev_tppGetSysInfo_Timer )
_ev_end

/***********************<< 添加网管服务器响应  >>********************	
*TTPNMServerCfg	网管服务器配置信息
*EmModifyNMServerRet 添加网管服务器结果
*[消息方向]	  CNS	-->  Tool
*
*/
_event(  ev_tppCnAgtAddNMServer_Ind )
_body( TTPNMServerCfg, 1 )
_body( EmModifyNMServerRet, 1 )
_ev_end

/***********************<< 删除网管服务器响应  >>********************
*TTPNMServerCfg	网管服务器配置信息
*EmModifyNMServerRet 删除网管服务器结果	
*[消息方向]	  CNS	-->  Tool
*
*/
_event(  ev_tppCnAgtDelNMServer_Ind )
_body( TTPNMServerCfg, 1 )
_body( EmModifyNMServerRet, 1 )
_ev_end

/***********************<< 修改网管服务器响应  >>********************	
*[消息体]
*TTPNMServerCfg	网管服务器配置信息
*EmModifyNMServerRet 修改网管服务器结果
*[消息方向]	  CNS	-->  Tool
*
*  
*/
_event(  ev_tppCnAgtModifyNMServer_Ind )
_body( TTPNMServerCfg, 1 )
 _body( EmModifyNMServerRet, 1 )
_ev_end

/***********************<< 通知维护工具管服务器的信息  >>********************
*[消息体]
*TTPNMServerCfg	网管服务器配置信息
*[消息方向]	  CNS	-->  Tool
*
*/
_event(  ev_tppCurAgtNMServerInfo_Nty )
_body( TTPNMServerCfg, 1 )
_ev_end

/***********************<< 维护工具刷新界面请求  >>********************	
*[消息体]
*NULL
*[消息方向]	  Tool	-->  CNS
*
*
*/
_event(  ev_tppRefresh_Req )
_ev_end

/***********************<< 丢包率信息定时器  >>********************	
*[消息体]
*NULL
*[消息方向]	  CNS	-->  CNS
*
*
*/
_event(  ev_tppLoopbackTest_Timer )
_ev_end

//add by niu 2014-04-23
/***********************<< 生产测试自环定时器获得采集音量  >>********************	
*[消息体]
*NULL
*[消息方向]	  CNS	-->  CNS
*
*
*/
_event(  ev_tppAutoLoopbackTest_Timer )
_ev_end
//end add by niu

/***********************<< 获取音量信息定时器  >>********************	
*[消息体]
*NULL
*[消息方向]	  CNS	-->  CNS
*
*
*/
_event(  ev_tppEnableStartDual_Nty )
_ev_end

/***********************<< 上下行速率获取定时器  >>********************
*[消息体]
*NULL	
*[消息方向]	  CNS	-->  CNS
*
*
*/
_event(  ev_tppGetUpDownNetSpeed_Timer )
_ev_end

/***********************<< 登录成功后获取基本信息通知  >>********************	
*[消息体]
*NULL
*[消息方向]	  CNS	-->  CNS
*
*
*/
_event(  ev_tppGetConfInfo_Nty )
_ev_end

/***********************<< 音视频基本信息通知  >>********************
*[消息体]
*TVgaInfo VGA设备信息
*TTPVgaMixInfo	
*[消息方向]	  CNS	-->  Tool
*
*
*/
_event(  ev_tppAVInfo_Nty )
_body( TVgaInfo, CNS_VGA_TYPE_NUM )
_body( TTPVgaMixInfo, 1 )
_ev_end

/***********************<< 通知维护工具是否显示会场名的信息  >>********************	
*[消息体]
*BOOL	
*[消息方向]	  CNS	-->  Tool
*
*/
_event( ev_tppShowRoomName_Nty )
_body( BOOL, 1 )
_ev_end

/***********************<< 显示会场名命令 >>********************
*[消息体]
*BOOL		
*[消息方向]	  CNS	<--  Tool
*
*/
_event( ev_tppShowRoomName_Cmd )
_body( BOOL, 1 )
_ev_end

// **********************<< 通知维护工具系统待机的信息  >>********************	
// *[消息体]
// *TTPSleepInfo	
// *[消息方向]	  CNS	-->  cnc
// *
// _event( ev_tppCnSysSleep_Nty )
// _body( TTPSleepInfo, 1 )
// _ev_end

// **********************<< 系统待机命令的信息  >>********************	
// *[消息体]
// *TTPSleepInfo	
// *[消息方向]	  CNS	-->  Tool
// *
// _event( ev_tppCnSysSleep_Cmd )
// _body( TTPSleepInfo, 1 )
// _ev_end

/***********************<< 音频均衡器配置请求  >>********************	
*[消息体]
*TTPEqualizer 三路音频编解码器的均衡器信息	
*[消息方向]	  Tool	-->  CNS
*
*/
_event( ev_tppSetAudioEqualizer_Cmd )
_body( TTPEqualizer, 3 )
_ev_end

/***********************<< 音频均衡器配置响应  >>********************	
*[消息体]
*TTPEqualizer 三路音频编解码器的均衡器信息
*BOOL 设置是否成功	
*[消息方向]	  CNS	-->  Tool
*
*/
_event( ev_tppSetAudioEqualizer_Ind )
_body( TTPEqualizer, 3 )
_body( BOOL, 1 )
_ev_end

/***********************<< 音频混音数配置请求  >>********************	
*[消息体]
*u8*3 三路主音频混音路数
*u8   会场主音频混音路数	
*[消息方向]	  Tool	-->  CNS
*
*/
_event( ev_tppSetAudiotMixer_Cmd )
_body( u8, 4 )
_ev_end

/***********************<< 音频混音数配置响应  >>********************	
*[消息体]
*u8*3 三路主音频混音路数
*u8   会场主音频混音路数
*BOOL 设置是否成功
*[消息方向]	  CNS	-->  Tool
*
*/
_event( ev_tppSetAudiotMixer_Ind )
_body( u8, 4 )
_body( BOOL, 1 )
_ev_end

/***********************<< 呼叫服务器配置设置请求  >>********************	
*[消息体]
*TTPCallSerInfo   呼叫服务器配置信息
*[消息方向]	  Tool	-->  CNS
*
*/
_event( ev_tppSetCallServerInfo_Cmd )
_body( TTPCallSerInfo, 1 )
_ev_end

/***********************<< 呼叫服务器配置设置通知  >>********************	
*[消息体]
*TTPCallSerInfo   呼叫服务器配置信息
*[消息方向]	  CNS	-->  Tool
*
*/
_event( ev_tppSetCallServerInfo_Nty )
_body( TTPCallSerInfo, 1 )
_ev_end

/***********************<< 呼叫服务器配置设置响应  >>********************	
*[消息体]
*TTPCallSerInfo   呼叫服务器配置信息
*BOOL 呼叫服务器配置是否成功
*[消息方向]	  CNS	-->  Tool
*
*/
_event( ev_tppSetCallServerInfo_Ind )
_body( TTPCallSerInfo, 1 )
_body( BOOL, 1 )
_ev_end

/***********************<< 升级服务器配置设置请求  >>********************	
*[消息体]
*u32_ip   升级服务器配置信息
*[消息方向]	  Tool	-->  CNS
*
*/
_event( ev_tppSetUpgradeServerInfo_Cmd )
_body( TTPUpgradeSer, 1 )
_ev_end

/***********************<< 升级服务器配置设置通知  >>********************	
*[消息体]
*u32_ip   升级服务器配置信息
*[消息方向]	  CNS	-->  Tool
*
*/
_event( ev_tppSetUpgradeServerInfo_Nty )
_body( TTPUpgradeSer, 1 )
_ev_end

/***********************<< 升级服务器配置设置响应  >>********************	
*[消息体]
*u32_ip   升级服务器配置信息
*BOOL 升级服务器配置是否成功
*[消息方向]	  CNS	-->  Tool
*
*/
_event( ev_tppSetUpgradeServerInfo_Ind )
_body( TTPUpgradeSer, 1 )
_body( BOOL, 1 )
_ev_end

/***********************<< 停止音视频接口测试请求  >>********************
*[消息体]
*[消息方向]	  Tool	-->  Cns
*
*/
_event( ev_tppStopAVMatrixProject_Req )
_ev_end

/***********************<< 停止音视频接口测试响应  >>********************
*[消息体]
*[消息方向]	  Cns	-->  Tool
*
*/
_event( ev_tppStopAVMatrixProject_Rsp )
_ev_end

/***********************<< 音频接口配置恢复默认命令  >>********************
*[消息体]
*[消息方向]	  Tool	-->  Cns
*
*/
_event( ev_tppAudioRestoreDefaults_Cmd )
_body ( TTpAudioPortInfo  , 3  )
_ev_end

/***********************<< 音频接口配置恢复默认命令响应  >>********************
*[消息体]
*[消息方向]	  Cns	-->  Tool
*
*/
_event( ev_tppAudioRestoreDefaults_Ind )
_body( BOOL, 1 )
_ev_end

/***********************<< 混音配置恢复默认命令  >>********************
*[消息体]
*[消息方向]	  Tool	-->  Cns
*
*/
_event( ev_tppMixRestoreDefaults_Cmd )
_body( u8, 4 )
_ev_end

/***********************<< 混音配置恢复默认命令响应  >>********************
*[消息体]
*[消息方向]	  Cns	-->  Tool
*
*/
_event( ev_tppMixRestoreDefaults_Ind )
_body( BOOL, 1 )
_ev_end

/***********************<< 均衡器配置恢复默认命令  >>********************
*[消息体]
*[消息方向]	  Tool	-->  Cns
*
*/
_event( ev_tppEqualizerReDefaults_Cmd )
_body( TTPEqualizer, 3 )
_ev_end

/***********************<< 均衡器配置恢复默认命令响应  >>********************
*[消息体]
*[消息方向]	  Cns	-->  Tool
*
*/
_event( ev_tppEqualizerReDefaults_Ind )
_body( BOOL, 1 )
_ev_end

/***********************<< B2版本获取GK列表信息通知  >>********************
*[消息体]
*[消息方向]	  Cncall -->Cns,Cns -->CNC  
*
*/
_event( ev_tppGetRegGKInfo_Nty )
_body( TTPMtRegInfo, 1 )
//_body( BOOL, 1 )
_ev_end

/***********************<< B2版本获取SIP地址簿信息响应  >>********************
*[消息体]
*[消息方向]	  Cncall -->Cns,Cns -->CNC  
*
*/
_event( ev_tppGetRegInfoCNS_Rsp )
_body( TRegPackInfoEx, 1 )
_body( EmGetRegInfoType, 1 )
_body( TCnsRegPackEx, 1 )
_ev_end

/***********************<< B2版本获取SIP地址簿信息响应  >>********************
*[消息体]
*[消息方向]	  Cncall -->Cns,Cns -->CNC  
*
*/
_event( ev_tppGetRegInfoUMS_Rsp )
_body( TRegPackInfoEx, 1 )
_body( EmGetRegInfoType, 1 )
_body( TUmsRegPackEx, 1 )
//_body( TUmsRegPackEx, 1 )
_ev_end

    /*************************<< 设置文档摄像机类型 >>******************************	
 *[消息体]
 *  +EmDcamProType 配置型号 emVISCAPro RS200 , emPELCOPro PC822
 *  
 *[消息方向]
 *   
 *      tptool => cns 
 */_event(  ev_Cn_DocSetTypeCmd )
   _body (EmDCamProType, 1)
   _ev_end

    /*************************<< 设置文档摄像机类型反馈 >>******************************	
 *[消息体]
 *  
 *  +EmDcamProType 配置型号 emVISCAPro RS200 , emPELCOPro PC822
 *  +BOOL 设置是否成功
 *[消息方向]
 *   
 *      cns  => tptool  
 */_event(  ev_Cn_DocSetTypeInd)
   _body (EmDCamProType, 1)
   _body (BOOL, 1)
   _ev_end

   /***********************<<  卡农麦克10配置命令  >>********************	
*[消息体]
*TTpAudioPortInfo 卡农麦克10信息
*[消息方向]	Tools	-->  CNS
*
*/
_event( ev_tppSetMic10Info_Cmd )
_body ( TTpMic10Info, 1 )		
_ev_end

   /***********************<<  卡农麦克10配置回应  >>********************	
*[消息体]
*TTpAudioPortInfo 卡农麦克10信息
*[消息方向]	CNS	-->  Tools
*
*/
_event( ev_tppSetMic10Info_Ind )
_body ( TTpMic10Info, 1 )
_body ( BOOL , 1 )		
_ev_end

/*************************<< 323终端上报视频源类型消息 >>******************************   
*[消息体]
*  +TVidSourceInfo 
*  
*[消息方向]
*	
*	   cns => cnc
*/_event(  ev_H323SendVideoInfo_Nty )
  _body( TVidSourceInfo , 1 )
  _ev_end

/*************************<< 323终端上报视频源类型消息 >>******************************   
*[消息体]
*  +TVidSourceInfo 
*  
*[消息方向]
*	
*	   cns => cnc
*/_event(  ev_H323SendVideoFeccInfo_Nty )
  _body( BOOL32, 1 )
  _body( u8, 1 )
  _ev_end

/*************************<< GK注册 >>****************************** 
*[消息体]
*TTPGKCfg 
*[消息方向]
*cns -> cns
*/
  _event( ev_tppGkRegister_Nty )
  _body( TTPGKCfg, 1 )
  _ev_end

    /*************************<< 添加路由信息请求 >>******************************   
*[消息体]
*  +TRouteCfg 
*  
*[消息方向]
*	
*	   tptools => cns
*/_event(  ev_tppAddRoute_Cmd )
  _body( TRouteCfg, 1 )
  _ev_end

    /*************************<< 配置路由信息响应 >>******************************   
*[消息体]
*  +TRouteCfg 
*  
*[消息方向]
*	
*	   tptools => cns
*/_event(  ev_tppAddRoute_Ind )
  _body( TRouteCfg, 1 )
  _body( BOOL, 1 )
  _ev_end

  /*************************<< 刪除路由信息请求 >>******************************   
  *[消息体]
  *  +TRouteCfg 
  *  
  *[消息方向]
  *	
  *	   tptools => cns
  */_event(  ev_tppDelRoute_Cmd )
  _body( TRouteCfg, 1 )
  _ev_end

  /*************************<< 刪除路由信息响应 >>******************************   
  *[消息体]
  *  +TRouteCfg 
  *  
  *[消息方向]
  *	
  *	   tptools => cns
  */_event(  ev_tppDelRoute_Ind )
  _body( TRouteCfg, 1 )
  _body( BOOL, 1 )
  _ev_end

    /*************************<< 路由信息通知 >>******************************   
  *[消息体]
  *  +TRouteCfg 
  *  
  *[消息方向]
  *	
  *	   tptools => cns
  */_event(  ev_tppRouteInfo_Nty )
  _body( TRouteCfg, 16 )
  _ev_end

  /***********************<<  定时等待渠道号 >>********************** 
  *[消息体]
  *NULL
  *[消息方向]
  *cns -> cns
  */
  _event( ev_TppCheckPID__timer )
  _ev_end

  /*************************<< ntp时间同步服务器请求 >>******************************   
  *[消息体]
  * u32_ip   时间同步服务器配置信息
  *  
  *[消息方向]
  *	
  *	tptools => cns
  */_event(  ev_tppSetNtpServerInfo_Cmd )
  _body( TTPNtpSer, 1 )
  _ev_end

    /*************************<< ntp时间同步服务器回应 >>******************************   
  *[消息体]
  * u32_ip   时间同步服务器配置信息
  *  
  *[消息方向]
  *	
  *	tptools => cns
  */_event(  ev_tppSetNtpServerInfo_Ind )
  _body( TTPNtpSer, 1 )
  _body( BOOL, 1 )
  _ev_end

    /*************************<< ntp时间同步服务器通知 >>******************************   
  *[消息体]
  * u32_ip   时间同步服务器配置信息
  *  
  *[消息方向]
  *	
  *	tptools => cns
  */_event(  ev_tppSetNtpServerInfo_Nty )
  _body( TTPNtpSer, 1 )
  _ev_end

    /***********************<< 设置是否登录同步时间命令 >>********************** 
  *[消息体]	
  *BOOL    是否同步时间到cns					
  *[消息方向]
  *  cnc	  ->  cns
  */
  _event(  ev_CnNtpIsUsed_Cmd )
  _body (BOOL, 1)
  _ev_end

  /***********************<< 设置是否登录同步时间回应 >>********************** 
  *[消息体]	
  *BOOL    是否同步时间到cns					
  *[消息方向]
  *  cns	  ->  cnc
  */
  _event(  ev_CnNtpIsUsed_Ind )
  _body (BOOL, 1)
  _body (BOOL, 1)
  _body( TTPTime, 1 )
  _ev_end

  /***********************<< 通知cnc当前cns的系统时间 >>********************** 
  *[消息体]	
  *TTPTime 系统时间
  *BOOL    是否同步时间到cns					
  *[消息方向]
  *  cns	  ->  cnc
  */
  _event(  ev_CnSysTimeToCnc_Nty )
  _body( TTPTime, 1 )
  _body( BOOL, 1 )
  _ev_end

  /***********************<<  音频输入音量控制  >>********************	
  *[消息体]
  *TTpAudioPortInfo 3路主音频接口信息
  *[消息方向]	Tool	-->  CNS
  *
  */
  _event(  ev_tppSetAudioVolum_Cmd )
  _body ( u8  , 1  )	
  _body ( u8  , 1  )	
  _body ( BOOL  , 1  )
  _ev_end
  
  /***********************<<  音频输入音量控制回应  >>********************	
  *[消息体]
  *TTpAudioPortInfo 3路主音频接口信息
  *[消息方向]	Tool	-->  CNS
  *
  */
  _event(  ev_tppSetAudioVolum_Ind )
  _body ( u8  , 1  )	
  _body ( BOOL  , 1  )	
_ev_end

    /***********************<< Tpad密码周期性更新请求 >>********************** 
  *[消息体]	
  *TTpPasswordUpdateInfo 					
  *[消息方向]
  *  cnc	  ->  cns
  */
  _event( ev_CnTpadPasswordUpdate_Cmd )
  _body( TTpPasswordUpdateInfo, 1 )
  _ev_end

      /***********************<< Tpad密码周期性更新响应 >>********************** 
  *[消息体]	
  *TTpPasswordUpdateInfo 					
  *[消息方向]
  *  cns	  ->  cnc
  */
  _event( ev_CnTpadPasswordUpdate_Ind )
  _body( TTpPasswordUpdateInfo, 1 )
  _body( BOOL, 1 )
  _ev_end

      /***********************<< Tpad密码周期性更新通知 >>********************** 
  *[消息体]	
  *TTpPasswordUpdateInfo 					
  *[消息方向]
  *  cns	  ->  cnc
  */
  _event(  ev_CnTpadPasswordUpdate_Nty )
  _body( TTpPasswordUpdateInfo, 1 )
  _ev_end

#ifndef _MakeTpEventDescription_
		_ev_segment_end(outercnstool)
};
#endif


#endif // _h_tooleventoutcomm_h__
