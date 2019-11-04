#ifndef _h_eventoutmoonextend_h__
#define _h_eventoutmoonextend_h__

#include "mooneventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmCNSEXTENDEVENT
{
#endif 

  _ev_segment( outermoonextend  )

 //登录
 /***********************<< 登录请求 >>********************** 
 *[消息体]
 *NULL
 *[消息方向]
 *  cam	  -> moon
*/
_event(  ev_TpMoonLogin_Req )
//_body( CLoginRequest, 1 )
_ev_end

 /***********************<< 登录请求回应 >>********************** 
 *[消息体]
+TLoginRet  登录信息
 *[消息方向]
 *  cam	  <- moon
*/
_event(  ev_TpMoonLogin_Rsp )
_body(TLoginRet,	1)
_ev_end

  /***********************<<  请求添加用户 >>********************	
  *[消息方向]	cam	-->  moon
  *添加用户请求，参数为CUserFullInfo，此消息直接用OSP发送，不经过XML编解码
  */
  _event(  ev_TpMoonAddUser_Req )
  _ev_end



  
  /***********************<< 回复添加用户  >>********************	
  *[消息方向]	moon	-->  cam
  *添加反馈
  */
  _event(  ev_TpMoonAddUser_Rsp )
  _body(EmTpRet,	1)	//操作结果
  _ev_end
  



  /***********************<<  请求删除用户 >>********************	
  *[消息方向]	cam	-->  moon
  *删除用户请求，参数为CUserFullInfo，此消息直接用OSP发送，不经过XML编解码
  */
  _event(  ev_TpMoonDelUser_Req )
  _ev_end	
  



  /***********************<<  回复删除用户 >>********************	
  *[消息方向]	moon	-->  Cam
  *删除反馈
  */
  _event(  ev_TpMoonDelUser_Rsp )
  _body(EmTpRet,	1)	//操作结果
  _ev_end
  



  /***********************<<  请求修改密码 >>********************	
  *[消息方向]	Cam	-->  moon
  *修改用户密码，参数为CUserFullInfo，此消息直接用OSP发送，不经过XML编解码
  */
  _event(  ev_TpMoonChangePWD_Req )
  _ev_end	
  



  /***********************<<   回复修改密码  >>********************	
  *[消息方向]	moon	-->  Cam
  *修改反馈
  */
  _event(  ev_TpMoonChangePWD_Rsp )
  _body(EmTpRet,	1)	//操作结果
  _ev_end	
  



  /***********************<< 有一个用户登录  >>********************	
  *[消息方向]	moon	-->  Cam
  *参数为CUserFullInfo，此消息直接用OSP发送，不经过XML编解码
  */
  _event(  ev_TpMoonAddUser_Nty )
  _ev_end	
  



  /***********************<< 有一个用户退出登录  >>********************	
  *[消息方向]	moon	-->  Cam
  *参数为CUserFullInfo，此消息直接用OSP发送，不经过XML编解码
  */
  _event(  ev_TpMoonDelUser_Nty )
  _ev_end	
  



  /***********************<< 修改用户  >>********************	
  *[消息方向]	moon	-->  Cam
  *参数为CUserFullInfo，此消息直接用OSP发送，不经过XML编解码
  */
  _event(  ev_TpMoonUpdateUser_Nty )
  _ev_end	
  
  

  /***********************<<用户在其它地方登录  >>********************	
  *[消息方向]	moon	-->  Cam
  *
  */
  _event(  ev_TpMoonLoginByOther_Nty )
  _body(u32_ip, 1)
_ev_end	

/***********************<<cam参数通知控制台>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP <- moon 
 */
_event(  ev_TpMoonVerInfo_Nty )
_body( s8, MOON_MAX_DEVICEVER_LEN)
_body( EmTpVer, 1)
_ev_end 

/***********************<<cam参数通知控制台>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP <- moon 
 */
_event(  ev_TpMoonCamInfo_Nty )
_body( TTPMoonCamInfo, 1)
_ev_end  

 /***********************<<cam接口输出类型设置>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamOutPortInfo_Cmd )
_body( EmTPDVIOutPortType, 1)
_body( EmTPMOONOutMode, 1)
_ev_end 

 /***********************<<cam接口输出类型回应>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP <- moon 
 */
_event(  ev_TpCamOutPortInfo_Ind )
_body( EmTPDVIOutPortType, 1)
_body( EmTPMOONOutMode, 1)
_body( BOOL, 1)
_ev_end 

 /***********************<<cam接口输出类型设置通知>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP <- moon 
 */
_event(  ev_TpCamOutPortInfo_Nty )
_body( EmTPDVIOutPortType, 1)
_body( EmTPMOONOutMode, 1)
_ev_end

 /***********************<<cam设置图像反转调节平衡、垂直>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamImageAdjust_Cmd )
_body( EmTPImageAdjust, 1)
_ev_end 

 /***********************<<cam设置图像反转调节平衡、垂直回应>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP <- moon 
 */
_event(  ev_TpCamImageAdjust_Ind )
_body( EmTPImageAdjust, 1)
_body( BOOL, 1)
_ev_end 

 /***********************<<cam设置图像反转调节平衡、垂直 通知>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP <- moon 
 */
_event(  ev_TpCamImageAdjust_Nty )
_body( EmTPImageAdjust, 1)
_ev_end 

/***********************<<cam设置启动是否调用预置位1>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamInitPreset_Cmd )
_body( BOOL, 1)//启动是否调用预置位
_ev_end

/***********************<<cam设置启动是否调用预置位1回应>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  moon -> ue -> camCP
 */
_event(  ev_TpCamInitPreset_Ind )
_body( BOOL, 1)//启动是否调用预置位
_body( BOOL, 1)//是否成功
_ev_end

 /***********************<<cam设置预置位>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamPreSet_Cmd )
_body( TTPCamPre, 1)//预置位参数
_ev_end

 /***********************<<cam设置预置位回应>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP <- moon 
 */
_event(  ev_TpCamPreSet_Ind )
_body( TTPCamPre, 1)
_body( BOOL, 1)
_ev_end

 /***********************<<cam设置预置位回应>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP <- moon 
 */
_event(  ev_TpCamPreSet_Nty )
_body( TTPPreParam, 1)
_ev_end

/***********************<<cam调用预置位>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamPreRecall_Cmd )
_body( TTPCamPre, 1)
_ev_end

 /***********************<<cam调用预置位回应>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP <- moon 
 */
_event(  ev_TpCamPreRecall_Ind )
_body( TTPCamPre, 1)
_body( BOOL, 1)
_ev_end

/***********************<<cam删除预置位>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamPreReset_Cmd )
_body( TTPCamPre, 1)
_ev_end

 /***********************<<cam删除预置位回应>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP <- moon 
 */
_event(  ev_TpCamPreReset_Ind )
_body( TTPCamPre, 1)
_body( BOOL, 1)
_ev_end

/***********************<<cam删除预置位>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamPreModify_Cmd )
_body( TTPCamPre, 1)
_ev_end

 /***********************<<cam删除预置位回应>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP <- moon 
 */
_event(  ev_TpCamPreModify_Ind )
_body( TTPCamPre, 1)
_body( BOOL, 1)
_ev_end

/***********************<<cam设置Zoom放大缩小>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamSetZoonStart_Cmd )
_body( EmTPZOOM, 1)
_body( u8, 1)
_ev_end 

 /***********************<<cam设置Zoom放大缩小回应>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP <- moon 
 */
_event(  ev_TpCamSetZoonStart_Ind )
_body( EmTPZOOM, 1)
_body( u8, 1)
_body( BOOL, 1)
_ev_end 

/***********************<<cam设置Zoom放大缩小>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamSetZoonStop_Cmd )
_body( u8, 1)
_ev_end 

/***********************<<cam设置Zoom放大缩小>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamSetZoonStop_Ind )
_body( u8, 1)
_body( u32, 1)
_body( BOOL, 1)
_body( u32, 1)
_ev_end 

/***********************<<cam设置Zoom值>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamSetDrectZoon_Cmd )
_body( u32, 1)
_body( u8, 1)
_ev_end 

 /***********************<<cam设置Zoom值回应>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP <- moon 
 */
_event(  ev_TpCamSetDrectZoon_Ind )
_body( u32, 1)
_body( u8, 1)
_body( BOOL, 1)
_body(u32, 1)
_ev_end 

/***********************<<cam设置聚焦模式>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamFocusMode_Cmd )
_body( EmTPMOOMMode, 1)
_body( u8, 1)
_ev_end 

 /***********************<<cam设置聚焦模式回应>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP <- moon 
 */
_event(  ev_TpCamFocusMode_Ind )
_body( EmTPMOOMMode, 1)
_body( u8, 1)
_body( BOOL, 1)
_ev_end 

/***********************<<cam设置曝光模式>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamExpMode_Cmd )
_body( EmTPMOOMMode, 1)
_body( u8, 1)
_ev_end 

 /***********************<<cam设置曝光模式回应>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP <- moon 
 */
_event(  ev_TpCamExpMode_Ind )
_body( EmTPMOOMMode, 1)
_body( u8, 1)
_body( BOOL, 1)
_ev_end 

/***********************<<cam设置曝光光圈>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamExpAperture_Cmd )
_body( EmTPAperture, 1)
_body( u8, 1)
_ev_end 

 /***********************<<cam设置曝光光圈回应>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP <- moon 
 */
_event(  ev_TpCamExpAperture_Ind )
_body( EmTPAperture, 1)
_body( u8, 1)
_body( BOOL, 1)
_ev_end 

/***********************<<cam设置曝光快门60/30>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamExpSOrThShutter_Cmd )
_body( EmTPSOrThShutter, 1)
_body( u8, 1)
_ev_end 

 /***********************<<cam设置曝光快门60/30回应>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP <- moon 
 */
_event(  ev_TpCamExpSOrThShutter_Ind )
_body( EmTPSOrThShutter, 1)
_body( u8, 1)
_body( BOOL, 1)
_ev_end 

/***********************<<cam设置曝光快门50/25>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamExpFOrTwShutter_Cmd )
_body( EmTPFOrTwShutter, 1)
_body( u8, 1)
_ev_end 

 /***********************<<cam设置曝光快门50/25回应>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP <- moon 
 */
_event(  ev_TpCamExpFOrTwShutter_Ind )
_body( EmTPFOrTwShutter, 1)
_body( u8, 1)
_body( BOOL, 1)
_ev_end 

/***********************<<cam设置曝光增益>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamExpGain_Cmd )
_body( EmTPExpGain, 1)
_body( u8, 1)
_ev_end 

 /***********************<<cam设置曝光增益回应>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP <- moon 
 */
_event(  ev_TpCamExpGain_Ind )
_body( EmTPExpGain, 1)
_body( u8, 1)
_body( BOOL, 1)
_ev_end 

/***********************<<cam设置白平衡模式>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamWhiteBalanceMode_Cmd )
_body( EmTPMOOMMode, 1)
_body( u8, 1)
_ev_end 

 /***********************<<cam设置白平衡模式回应>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP <- moon 
 */
_event(  ev_TpCamWhiteBalanceMode_Ind )
_body( EmTPMOOMMode, 1)
_body( u8, 1)
_body( BOOL, 1)
_ev_end 

/***********************<<cam设置白平衡红色增益>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamWhiteBalanceRGain_Cmd )
_body( u32, 1)
_body( u8, 1)
_ev_end 

 /***********************<<cam设置白平衡红色增益回应>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP <- moon 
 */
_event(  ev_TpCamWhiteBalanceRGain_Ind )
_body( u32, 1)
_body( u8, 1)
_body( BOOL, 1)
_ev_end 

/***********************<<cam设置白平衡蓝色增益>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamWhiteBalanceBGain_Cmd )
_body( u32, 1)
_body( u8, 1)
_ev_end 

 /***********************<<cam设置白平衡蓝色增益回应>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP <- moon 
 */
_event(  ev_TpCamWhiteBalanceBGain_Ind )
_body( u32, 1)
_body( u8, 1)
_body( BOOL, 1)
_ev_end 

/***********************<<cam设置背光补偿>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamBackLight_Cmd )
_body( BOOL, 1)
_body( u8, 1)
_ev_end 

 /***********************<<cam设置背光补偿回应>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP <- moon 
 */
_event(  ev_TpCamBackLight_Ind )
_body( BOOL, 1)
_body( u8, 1)
_body( BOOL, 1)
_ev_end 

/***********************<<cam设置图像参数：亮度、色度、饱和度、对比度>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamImagePara_Cmd )
_body( EmTPImagePara, 1)
_body( u32, 1)
_body( u8, 1)
_ev_end 

 /***********************<<cam设置图像参数：亮度、色度、饱和度、对比度回应>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP <- moon 
 */
_event(  ev_TpCamImagePara_Ind )
_body( EmTPImagePara, 1)
_body( u32, 1)
_body( u8, 1)
_body( BOOL, 1)
_ev_end 

/***********************<<cam设置FPGA降噪>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamReduNoise_Cmd )
_body( BOOL, 1)
_body( EmTPFpgaReduNoise, 1)
_body( u8, 1)
_ev_end 

 /***********************<<cam设置降噪回应>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP <- moon 
 */
_event(  ev_TpCamReduNoise_Ind )
_body( BOOL, 1)
_body( EmTPFpgaReduNoise, 1)
_body( u8, 1)
_body( BOOL, 1)
_ev_end 

/***********************<<cam快照请求>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamSnapshot_Cmd )
_body( TTPSnapshotInfo, 1)//快照按钮时，该结构体里byIndex需置为3
_ev_end 

 /***********************<<cam快照回应>>***********************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP <- moon 
 */
_event(  ev_TpCamSnapshot_Ind )
_body( TTPSnapshotInfo, 1)//快照按钮时，该结构体里byIndex需置为3
_body( BOOL, 1)//成功与否返回值
_body(BOOL, 1)//moon90h时为TRUE，moon90为FALSE
_ev_end 

/***********************<<cam设置拼接降噪>>********************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP -> moon -> cam
 */
_event(  ev_TpImageReduNoise_Cmd )
_body( EmTPFpgaReduNoise, 1)
_body( u8, 1)
_ev_end 

 /***********************<<cam设置拼接回应>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP <- moon 
 */
_event(  ev_TpImageReduNoise_Ind )
_body( EmTPFpgaReduNoise, 1)
_body( u8, 1)
_body( BOOL, 1)
_ev_end 

/***********************<<cam直接设置梯形校正>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP -> moon -> cam
 */
_event(  ev_TpImageDistortCorrect_Cmd )
_body( TTPDistortParam, 1)
_body( EmTPCorrect, 1)
_body( u8, 1)
_ev_end 

 /***********************<<cam直接设置梯形校正回应>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP <- moon 
 */
_event(  ev_TpImageDistortCorrect_Ind )
_body( TTPDistortParam, 1)
_body( EmTPCorrect, 1)
_body( u8, 1)
_body( BOOL, 1)
_ev_end 

/***********************<<cam上电>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  moon -> cam
 */
_event(  ev_TpCamPowerOn_Cmd )
_body( u8, 1)
_ev_end 

/***********************<<cam下电>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  moon -> cam
 */
_event(  ev_TpCamPowerOff_Cmd )
_body( u8, 1)
_ev_end

/***********************<<cam聚焦调节>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  moon -> cam
 */
_event(  ev_TpCamFocusFar_Cmd )
_body( u8, 1)
_ev_end 

/***********************<<cam聚焦调节>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  moon -> cam
 */
_event(  ev_TpCamFocusFar_Ind )
_body( u8, 1)
_body( BOOL, 1)
_ev_end 

/***********************<<cam聚焦调节>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  moon -> cam
 */
_event(  ev_TpCamFocusNear_Cmd )
_body( u8, 1)
_ev_end 

/***********************<<cam聚焦调节>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  moon -> cam
 */
_event(  ev_TpCamFocusNear_Ind )
_body( u8, 1)
_body( BOOL, 1)
_ev_end 

/***********************<<cam聚焦调节>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  moon -> cam
 */
_event(  ev_TpCamFocusStop_Cmd )
_body( u8, 1)
_ev_end 

/***********************<<cam聚焦调节>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  moon -> cam
 */
_event(  ev_TpCamFocusStop_Ind )
_body( u8, 1)
_body( BOOL, 1)
_ev_end 

 /***********************<<cam选择摄像机命令>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamSelect_Cmd )
_body( u8, 1)
_ev_end 

 /***********************<<cam选择摄像机命令回应>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP <- moon 
 */
_event(  ev_TpCamSelect_Ind )
_body( u8, 1)
_body( BOOL, 1)
_ev_end 

/***********************<<cam选择摄像机命令通知>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP <- moon 
 */
_event(  ev_TpCamSelect_Nty )
_body( u8, 1)
_ev_end

 /***********************<<cam恢复默认命令>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamParamDefault_Cmd )
_body(u8, 1)             //0：第一个几面；1：第二个界面
_ev_end 

 /***********************<<cam恢复默认命令回应>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP <- moon 
 */
_event(  ev_TpCamParamDefault_Ind )
_body( TTPMoonCamInfo, 1)
_body( BOOL, 1)
_ev_end 


 /***********************<<导入预置位消息>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP -> moon 
 */
_event(  ev_TpCamParamUpload_Cmd )
_ev_end 

 /***********************<<导入预置位回应>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP <- moon 
 */
_event(  ev_TpCamParamUpload_Ind )
_body( BOOL, 1)
_ev_end

 /***********************<<导入预置位通知>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP -> moon 
 */
_event(  ev_TpCamParamUpload_Nty )
_body( BOOL, 1)
_ev_end 

 /***********************<<cam选择摄像机命令回应>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP -> moon  
 */
_event(  ev_TpCamReboot_Ind )
_body( BOOL, 1)//上传预置位文件后提醒重启：True，不重启：False
_ev_end

/***********************<< 生产测试工具登陆请求消息 >>********************** 
*[消息体]
*CLoginRequest
*[消息方向]
*    应用终端 <- cns 
*/
_event( ev_CNPRODUCETESTLOGIN_REQ )
//_body(CLoginRequest ,1)
_ev_end

/***********************<< 生产测试工具测试项请求消息 >>********************** 
*[消息体]
*TCnProduceTestMsg
*[消息方向]
*    应用终端 -> cns 
*/
_event( ev_CNPRODUCETEST_CMD )
_body(TMOONProduceTestMsg ,1)
_ev_end

/***********************<< 生产测试工具登陆响应成功消息 >>********************** 
*[消息体]
*
*[消息方向]
*    应用终端 -> cns 
*/
_event( ev_CNPRODUCETESTLOGIN_ACK )
//_body(TCnProduceTestMsg ,1)
_ev_end

/***********************<< 生产测试工具登陆响应失败消息 >>********************** 
*[消息体]
*
*[消息方向]
*    应用终端 -> cns 
*/
_event( ev_CNPRODUCETESTLOGIN_NACK )
//_body(TCnProduceTestMsg ,1)
_ev_end

/***********************<< 生产测试工具测试结果消息 >>********************** 
*[消息体]
*TCnProduceTestMsg
*[消息方向]
*    应用终端 <- cns 
*/
_event( ev_CNPRODUCETESTRESULT_NTY )
_body(TMOONProduceTestMsg ,1)
_ev_end
	  
/***********************<< 生产测试工具连接定时器消息 >>********************** 
*[消息体]
*
*[消息方向]cns -> cns
*    
*/
_event( ev_CNPRODUCETESTCONNECT_TIMER )
//_body(TCnProduceTestMsg ,1)
_ev_end

/***********************<< 生产测试工具登陆注册定时器消息 >>********************** 
*[消息体]
*
*[消息方向]cns -> cns
*    
*/
_event( ev_CNPRODUCETESTLOGIN_TIMER )
//_body(TCnProduceTestMsg ,1)
_ev_end

/***********************<< 生产测试工具指示灯定时器消息 >>********************** 
*[消息体]
*
*[消息方向]cns -> cns
*    
*/
_event( ev_CNPRODUCETESTLIGHT_TIMER )
//_body(TCnProduceTestMsg ,1)
_ev_end

/***********************<< 生产测试工具恢复默认值 >>********************** 
*[消息体]
*
*[消息方向]应用 -> cns
*    
*/
_event( ev_CNPRODUCETESTDEFAULT_CMD )
//_body(TCnProduceTestMsg ,1)
_ev_end
 
/***********************<< 生产测试工具恢复默认值应答 >>********************** 
*[消息体]
*
*[消息方向]cns -> cns
*    
*/
_event( ev_CNPRODUCETESTDEFAULT_NTY )
_body(BOOL ,1)
_ev_end

/***********************<< 生产测试工具红外接收IR OUT 测试LED灯定时器 >>********************** 
*[消息体]
*
*[消息方向]cns -> cns
*    
*/
_event( ev_CNPRODUCETESTLED_TIMER )
//_body(BOOL ,1)
_ev_end

/***********************<<设置LVDS波特率请求>>************************	
*[消消息体]			 
* NULL
*[消息方向]
*  camCP -> moon 
*/
_event(  ev_TpSetLVDSBaud_Cmd )
_body( EmTPLVDSBaud, 1)//比特率选项
_ev_end 

/***********************<<设置LVDS波特率回应>>************************	
*[消消息体]			 
* NULL
*[消息方向]
*  camCP <- moon 
*/
_event(  ev_TpSetLVDSBaud_Ind )
_body( EmTPLVDSBaud, 1)//比特率选项
_body( BOOL, 1)//成功与否返回值
_ev_end 

/***********************<<设置登陆时将LVDS波特率通知界面>>*************	
*[消消息体]			 
* NULL
*[消息方向]
*  camCP <- moon 
*/
_event(  ev_TpSetLVDSBaud_Nty )
_body( EmTPLVDSBaud, 1)//比特率选项
_ev_end 

/***********************<<开启参考线请求>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP -> moon -> cam
 */
_event(  ev_TpSetRefer_Cmd )
_body( BOOL, 1)//开关
_body(u8, 1)//无论打开还是关闭时，该值都需置为3
_ev_end 

 /***********************<<开启参考线回应>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP <- moon 
 */
_event(  ev_TpSetRefer_Ind )
_body( BOOL, 1)//开关
_body( BOOL, 1)//成功与否返回值
_ev_end 

 /***********************<<开启参考线通知>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP <- moon 
 */
_event(  ev_TpSetRefer_Nty )
_body( BOOL, 1)//开关，通知界面
_ev_end 

 /***********************<<开启水平翻转请求>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP -> moon -> cam
 */
_event(  ev_TpFlatTurn_Cmd )
_body( BOOL, 1)//开关
_ev_end 

 /***********************<<开启水平翻转回应>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP <- moon 
 */
_event(  ev_TpFlatTurn_Ind )
_body( BOOL, 1)//开关
_body( BOOL, 1)//成功与否返回值
_ev_end 

 /***********************<<开启水平翻转通知>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP <- moon 
 */
_event(  ev_TpFlatTurn_Nty )
_body( BOOL, 1)//开关通知界面
_ev_end 

 /***********************<<梯形校正改变请求>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP -> moon -> cam
 */
_event(  ev_TpSetDisort_Cmd )
_body( EmTPCorrect, 1)//栏目标识，标识界面具体哪一栏
_body( EmTPCorrectChange, 1)//增加或是减小标识
_ev_end 

 /***********************<<梯形校正改变响应>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP <- moon 
 */
_event(  ev_TpSetDisort_Ind )
_body( u32, 1)//每次设置后的返回值，供给界面用
_body( EmTPCorrect, 1)//栏目标识，标识界面具体哪一栏
_ev_end 
 /***********************<<梯形校开关按钮请求>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP -> moon -> cam
 */
_event(  ev_TpDisortSwitch_Cmd )
_body( BOOL, 1)//开关
_ev_end 
 /***********************<<梯形校开关按钮回应>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP <- moon
 */
_event(  ev_TpDisortSwitch_Ind )
_body( BOOL, 1)//开关
_body( BOOL, 1)//成功与否回应
_ev_end 

/*add by youjx 2016.11.8
/***********************<<cam设置Gamma>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP -> moon -> cam
 */
 _event( ev_TpCamSetGamma_Cmd )
 _body( EmH650Gamma, 1)
 _body( u8, 1)
 _ev_end

 /***********************<<选择机芯类型>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  CamCP-> moon
 */
 _event( ev_TpMechanismSelect_Cmd )
 _body( EmTPMechanism, 1)
 _ev_end

 /***********************<<机芯选择命令回应>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP <- moon 
 */
_event(  ev_TpMechanismSelect_Ind )
_body( EmTPMechanism, 1)
_body( BOOL, 1)
_ev_end 

/***********************<<cam设置Gamma回应>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  moon -> camCP
 */
 _event( ev_TpCamSetGamma_Ind )
 _body( EmH650Gamma, 1)
  _body( u8, 1)
 _body( BOOL, 1)
 _ev_end

 /***********************<<cam选择机芯命令通知>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP <- moon <- Cam
 */
_event(  ev_TpMechanismSelect_Nty )
_body( EmTPMechanism, 1)
_ev_end

 /***********************<<cam版本通知>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  camCP <- moon <- cam
 */
_event( ev_TpMechVer_Nty )
_body( u8, 1)
_body( s8, MOON_MAX_DEVICEVER_LEN)
_body( s8, MOON_MAX_DEVICEVER_LEN)
_ev_end
 /***********************<<Moon上线获得cam版本>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 * moon -> cam
 */
 _event( ev_TpGetMechVer_Cmd )
 _ev_end
 /***********************<<机芯2D降噪设置>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 * camCP -> moon -> cam
 */
 _event( ev_TpSetCam2DNoiseLevle_Cmd )
 _body( BOOL, 1)
 _body( EmTPCamNoiseLevel, 1)
 _body( u8, 1)
 _ev_end
 /***********************<<机芯3D降噪设置>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 * camCP -> moon -> cam
 */
 _event( ev_TpSetCam3DNoiseLevle_Cmd )
 _body( BOOL, 1)
 _body( EmTPCamNoiseLevel, 1)
 _body( u8, 1)
 _ev_end
 /***********************<<机芯2D降噪设置回应>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 * camCP <- moon
 */
 _event( ev_TpSetCam2DNoiseLevle_Ind )
 _body( BOOL, 1)
 _body( EmTPCamNoiseLevel, 1)
 _body( u8, 1)
 _body( BOOL, 1)
 _ev_end
  /***********************<<机芯3D降噪设置回应>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 * camCP <- moon 
 */
 _event( ev_TpSetCam3DNoiseLevle_Ind )
 _body( BOOL, 1)
 _body( EmTPCamNoiseLevel, 1)
 _body( u8, 1)
 _body( BOOL, 1)
 _ev_end

/***********************<<机芯升级请求>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 * camCP -> moon ->cam
 */
 _event( ev_CamUpgrade_Cmd )
 _body(s8,  TP_MAX_FILENAME_LEN + 1)
 _ev_end

/***********************<<机芯升级回应>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 * camCP <- moon <- cam
 */
 _event( ev_CamUpgrade_Ind )
 _body(BOOL,  1)
 _ev_end

 /***********************<<机芯参数同步请求>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 * camCP -> moon 
 */
 _event( ev_CamParaSynchronize_Cmd )
 _body(u8,  1)
 _ev_end

 /***********************<<机芯参数同步回应>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 * camCP <- moon 
 */
 _event( ev_CamParaSynchronize_Ind )
 _body(u8,  1)
 _body(BOOL, 1)
 _ev_end

 /***********************<<改变颜色RGB系数请求>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 * camCP -> moon -> cam
 */
 _event( ev_TPSetColorRGB_Cmd )
 _body(u8,  1)
 _body(EmTPColorConsistency, 1)
 _body(EmTPCorrectChange, 1)
 _ev_end

 /***********************<<改变颜色RGB系数回应>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 * camCP <- moon 
 */
 _event( ev_TPSetColorRGB_Ind )
 _body(u8,  1)
 _body(EmTPColorConsistency, 1)
 _body(u32, 1)
 _body(BOOL, 1)
 _ev_end

 /***********************<<自动计算颜色一致性请求>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 * camCP -> moon ->cam
 */
 _event( ev_TPAutoSetColorConstancy_Cmd )
 _ev_end

 /***********************<<自动计算颜色一致性回应>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 * camCP <- moon <- cam
 */
 _event( ev_TPAutoSetColorConstancy_Ind )
 _body(u32, MOON_COLOR_COEFF_NUM)    //通知界面计算结果，依次为左图R、左图G、左图B、中图R
                                     //中图G、中图B、右图R、右图G、右图B
 _body(BOOL, 1)
 _ev_end

 /***********************<<设置颜色RGB系数请求>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 * camCP -> moon -> cam
 */
 _event( ev_TPDirectSetColorRGB_Cmd )
 _body(u8,  1)
 _body(EmTPColorConsistency, 1)
 _body(u32, 1)
 _ev_end

  /***********************<<设置颜色RGB系数回应>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 * camCP <- moon 
 */
 _event( ev_TPDirectSetColorRGB_Ind )
 _body(u8,  1)
 _body(EmTPColorConsistency, 1)
 _body(u32, 1)
 _body(BOOL, 1)
 _ev_end

  /***********************<<选取矩形区域请求>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 * camCP -> moon -> cam
 */
 _event( ev_TPChooseRectangle_Cmd )
 _body(TTPMoonRectRegion, 1)        //矩形区域位置信息，包括左上角坐标，长，宽
 _ev_end

   /***********************<<选取矩形区域回应>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 * camCP <- moon 
 */
 _event( ev_TPChooseRectangle_Ind )
 _body(TTPMoonRectRegion, 1)
 _body(BOOL, 1)
 _ev_end

 /************<<中间路RGB系数改变时通知两边路RGB改变系数>>**********
 *[消消息体]			 
 * NULL
 *[消息方向]
 * camCP <- moon 
 */
 _event( ev_TPChangeSideRGB_Nty)
 _body(EmTPColorConsistency, 1)
 _body(u32, 1)                   //第一路RGB系数
 _body(u32, 1)                   //第三路RGB系数
 _ev_end

 /*****************<<改变梯形校正请求>>******************************
 *[消消息体]			 
 * NULL
 *[消息方向]
 * camCP -> moon ->cam
 */
 _event(ev_TPChangeDistor_Cmd)
 _body(u8, 1)                         //标示哪一路图像
 _body(EmTPDistortPosition, 1)        //标示梯形校正类型
 _body(EmTPCorrectChange, 1)          //标示梯形校正改变类型：增加或减少
 _ev_end

 /*****************<<改变梯形校正回应>>******************************
 *[消消息体]			 
 * NULL
 *[消息方向]
 * camCP <- moon 
 */
 _event(ev_TPChangeDistor_Ind)
 _body(TTPDistortInfo, 1)          //梯形校正数据
 _body(BOOL, 1)
 _ev_end

 /*****************<<直接设置梯形校正请求>>**************************
 *[消消息体]			 
 * NULL
 *[消息方向]
 * camCP -> moon ->cam
 */
 _event(ev_TPDirectSetDistor_Cmd)
 _body(TTPDistortInfo, 1)
 _ev_end

 /*****************<<直接设置梯形校正回应>>******************************
 *[消消息体]			 
 * NULL
 *[消息方向]
 * camCP <- moon 
 */
 _event(ev_TPDirectSetDistor_Ind)
 _body(TTPDistortInfo, 1)
 _body(BOOL, 1)
 _ev_end

 /*****************<<使能显示矩形外框>>******************************
 *[消消息体]			 
 * NULL
 *[消息方向]
 * camCP -> moon 
 */
 _event(ev_TPMoonShowRectRegion_Cmd)
 _body(BOOL, 1)
 _ev_end

 /*****************<<使能显示矩形外框回应>>******************************
 *[消消息体]			 
 * NULL
 *[消息方向]
 * camCP <- moon 
 */
 _event(ev_TPMoonShowRectRegion_Ind)
 _body(BOOL, 1)
 _body(BOOL, 1)
 _ev_end

  /*****************<<恢复默认值通知界面第二页>>******************************
 *[消消息体]			 
 * NULL
 *[消息方向]
 * camCP <- moon 
 */
 _event(ev_TpSecDefault_Nty)
 _body(TTPSecBoundaryInfo, 1)
 _body(BOOL, 1)
 _ev_end

  /*****************<<tptool登陆时通知界面第二页的信息>>****************
 *[消消息体]			 
 * NULL
 *[消息方向]
 * camCP <- moon 
 */
 _event(ev_TpSecBoundary_Nty)
 _body(TTPSecBoundaryInfo, 1)
 _ev_end

 /*****************<<颜色一致性校正开关>>****************
 *[消消息体]			 
 * NULL
 *[消息方向]
 * camCP <- moon 
 */
 _event(ev_TpColorSwich_Cmd)
 _body(BOOL, 1)
 _ev_end

 /*****************<<颜色一致性校正开关回应>>****************
 *[消消息体]			 
 * NULL
 *[消息方向]
 * camCP <- moon 
 */
 _event(ev_TpColorSwich_Ind)
 _body(BOOL, 1)
 _body(BOOL, 1)
 _ev_end

 /*****************<<设置fpga延时帧数>>****************
 *[消消息体]			 
 * u8 第几路机芯
 * u32 0-5帧
 *[消息方向]
 * camCP -> moon 
 */
 _event(ev_TpFpgaDelayCorrect_Cmd)
 _body(u8, 1)
 _body(u32, 1)
 _ev_end

 /*****************<<设置fpga延时帧数回应>>****************
 *[消消息体]			 
 * u8 第几路机芯
 * u32 0-5帧
 *[消息方向]
 * camCP <- moon 
 */
 _event(ev_TpFpgaDelayCorrect_Ind)
 _body(u8, 1)
 _body(u32, 1)
 _body(BOOL, 1)
 _ev_end

  /*****************<<fpga延时帧数通知>>****************
 *[消消息体]			 
 * u8 第几路机芯
 * u32 0-5帧
 *[消息方向]
 * camCP <- moon 
 */
 _event(ev_TpFpgaDelayCorrect_Nty)
 _body(u8, 1)
 _body(u32, 1)
 _ev_end
//add end


#ifndef _MakeTpEventDescription_
   _ev_segment_end( outermoonextend )
};
#endif
#endif //TPP_EVENT_H
