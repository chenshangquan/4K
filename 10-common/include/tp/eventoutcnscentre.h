#ifndef _h_eventoutcnscentre_h__
#define _h_eventoutcnscentre_h__

#include "cnseventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmCNSCENTREEVENT
{
#endif 
	
	_ev_segment( outercnscentre  )


/***********************<< TPad登陆通知 >>************************	
 *[消息体]
 *  
 *  
 *[消息方向]
 *   
 *      UI => Cndevice 
 */_event(  ev_cns_TPadOnLine_Req )
   _ev_end

/***********************<< CnTools登陆通知 >>************************	
 *[消息体]
 *  
 *  
 *[消息方向]
 *   
 *      UI => Cndevice 
 */_event(  ev_cns_CnsToolsOnLine_Req )
   _ev_end

/***********************<< 通知界面电视机配置 >>************************	
 *[消息体]
 *  + TCentreTVCfg
 *  
 *[消息方向]
 *   
 *      UI => Cndevice 
 */_event(  ev_cns_centreTVStateNty       )
   _body(   TCentreTVCfg, MAX_CENTRETV_NUM)
   _ev_end

/***********************<< 通知界面文档摄像机配置 >>************************	
 *[消息体]
 *   + TCentreDCamCfg
 *  
 *[消息方向]
 *   
 *      UI => Cndevice 
 */_event(  ev_cns_centreDCamStateNty  )
   _body(   TCentreDCamCfg,       1  )
   _ev_end

/***********************<< 通知界面施耐德配置 >>************************	
 *[消息体]
 *   + TCentreSchCfg
 *  
 *[消息方向]
 *   
 *      UI => Cndevice 
 */_event(  ev_cns_centreSchStateNty  )
   _body(   TCentreSchCfg,       1  )
   _ev_end

/***********************<< 中控选择电视机操作命令 >>************************	
 *[消息体]
 *     + u8  电视机索引
 *  
 *  
 *[消息方向]
 *   
 *      UI => Cndevice 
 */_event(  ev_cns_centreselectTV_cmd )
   _body(   u8   ,       1    )
   _ev_end

/***********************<< 中控选择电视机操作返回命令 >>************************	
 *[消息体]
 *     + u8     电视机索引
 *     + BOOL   操作成功/失败
 *  
 *[消息方向]
 *   
 *      Cndevice => UE 
 */_event(  ev_cns_centreselectTV_Ind )
   _body(   u8   ,       1    )
   _body(   BOOL ,       1    )
   _ev_end

/***********************<< 中控 设置电视模式命令 >>************************	
 *[消息体]
 *     +  EmTvMode   电视机模式  	emTVPowerOFF/emTVPowerON 电源关/开
 *  
 *  
 *[消息方向]
 *   
 *      UI => Cndevice 
 */_event(  ev_cns_centreTVMode_cmd )
   _body(   EmTvPowerMode,     1    )
   _body(   u8           ,     1    )
   _ev_end

/***********************<< 中控 设置电视模式返回命令 >>************************	
 *[消息体]
 *     + EmTvMode   电视机模式  	emTVPowerOFF/emTVPowerON 电源关/开
 *     + BOOL       设置成功/失败
 *  
 *[消息方向]
 *   
 *      Cndevice => UE 
 */_event(  ev_cns_centreTVMode_Ind )
   _body(   EmTvPowerMode,     1    )
   _body(	u8	,	           1    )
   _body(   BOOL         ,     1    )
   _ev_end

/***********************<< 中控 设置电视视听模式命令 >>************************	
 *[消息体]
 *     +  EmTVAudVisMode   电视机视听模式  	
 *  
 *  
 *[消息方向]
 *   
 *      UI => Cndevice 
 */_event(  ev_cns_centreTVAudVisMode_cmd )
   _body(   EmTVAudVisMode   ,       1    )
   _ev_end

/***********************<< 中控 设置电视视听模式返回命令 >>************************	
 *[消息体]
 *     + EmTVAudVisMode   电视机视听模式  	
 *     + BOOL           设置成功/失败
 *  
 *[消息方向]
 *   
 *      Cndevice => UE 
 */_event(  ev_cns_centreTVAudVisMode_Ind )
   _body(   EmTVAudVisMode   ,       1    )
   _body(   BOOL       ,       1    )
   _ev_end


/***********************<< 中控 设置电视显示模式命令 >>************************	
 *[消息体]
 *     +  EmTVDisplayMode   电视机视听模式  	
 *  
 *  
 *[消息方向]
 *   
 *      UI => Cndevice 
 */_event(  ev_cns_centreTVDisMode_cmd )
   _body(   EmTVDisplayMode   ,       1    )
   _ev_end

/***********************<< 中控 设置电视显示模式返回命令 >>************************	
 *[消息体]
 *     + EmTVDisplayMode   电视机视听模式  	
 *     + BOOL            设置成功/失败
 *  
 *[消息方向]
 *   
 *      Cndevice => UE 
 */_event(  ev_cns_centreTVDisMode_Ind )
   _body(   EmTVDisplayMode   ,       1    )
   _body(   BOOL       ,       1    )
   _ev_end

/***********************<< 中控 设置电视输入选择命令 >>************************	
 *[消息体]
 *  u8 屏序号
 *     +  EmTVInputSelect   电视机输入选择  	
 *  
 *  
 *[消息方向]
 *   
 *      UI => Cndevice 
 */_event(  ev_cns_centreTVInpSelect_cmd )
   _body( u8, 1 )
   _body(   EmTVInputSelect   ,       1    )
   _ev_end

/***********************<< 中控 设置电视输入选择返回命令 >>************************	
 *[消息体]
 *  u8 屏序号
 *     + EmTVInputSelect   电视机输入选择  	
 *     + BOOL            设置成功/失败
 *  
 *[消息方向]
 *   
 *      Cndevice => UE 
 */_event(  ev_cns_centreTVInpSelect_Ind )
   _body( u8, 1 )
   _body(   EmTVInputSelect   ,       1    )
   _body(   BOOL            ,       1    )
   _ev_end
   
  //Add by panhaiyang
/***********************<< 设置控制文档摄像头的任意指令 >>************************	
 *[消息体]			 
 *    + s8  设给文档摄像头的控制指令
 *[消息方向]
 *
 *   CNS => CnDevice
 */_event(  ev_Cn_DCam_Set_Cmd )
   _body (   s8        ,    1 )
   _ev_end

// **********************<< 文档摄像机开关选择   >>************************	
//  *[消息体]			 
//  *EmDCamPower:文档摄像头待机唤醒选择
//   emDCamPowerOn        唤醒
//   emDCamPowerOff       待机
//   emDCamPowerToggle    待机与唤醒开关切换 
//  *[消息方向]
//  *
//  *   CNS => CnDevice
   _event(  ev_Cn_DCamPower_Cmd )
   _body( EmDCamPower, 1 )
   _ev_end
// 
//  **********************<< 文档摄像机自动聚焦选择   >>************************	
//  *[消息体]			 
//  *EmDCamAFMode: 文档摄像机自动聚焦选择
//   emDCamAFOn          开启自动聚焦
//   emDcamAFOff         关闭自动聚焦
//   emDCamAFToggle      自动聚焦开关切换 
//  *[消息方向]
//  *
//  *   CNS => CnDevice
   _event(  ev_Cn_DCamAFMode_Cmd )
   _body( EmDCamAFMode, 1 )
   _ev_end
// 
//  **********************<< 文档摄像机白平衡模式选择   >>************************	
//  *[消息体]			 
//  *EmDCamBWMode: 文档摄像机白平衡模式选择
//   emDcamWBAuto         开启自动白平衡模式
//   emDCamWBManual       开启手动白平衡模式 
//   emDCamOnePush        开启一键式白平衡模式
//  *[消息方向]
//  *
//  *   CNS => CnDevice
   _event(  ev_Cn_DCamWBMode_Cmd )
   _body( EmDCamWBMode, 1 )
   _ev_end
// 
//  **********************<< 文档摄像头视野调节   >>************************	
//  *[消息体]
//  *EmCnAction         emCnStart,  emCnStop			 
//  *EmDCamZoom 文档摄像头视野调节
//   emDCamZoomWide       放大视野
//   emDCamZoomTele       缩小视野 
//  *[消息方向]
//  *
//  *   CNS => CnDevice
   _event(  ev_Cn_DCamZoom_Cmd )
   _body( EmCnAction, 1 )
   _body( EmDCamZoom, 1 )
   _ev_end
// 
// 
//  **********************<< 保存文档摄像头预置位   >>************************	
//  *[消息体]			 
//  *EmDCamPresetNum      保存的预置位编号
//   emDCamPresetOne      保存预置位1
//   emDCamPresetTwo      保存预置位2 
//   emDCamPresetThree    保存预置位3
//  *[消息方向]
//  *
//  *   CNS => CnDevice
   _event(  ev_Cn_DCamPreset_Cmd )
   _body( EmDCamPresetNum, 1 )
   _ev_end
// 
//  **********************<< 调度文档摄像头预置位   >>************************	
//  *[消息体]			 
//  *EmDCamRecallNum      调度的预置位编号
//   emDCamRecallOne      调度预置位1
//   emDCamRecallTwo      调度预置位2 
//   emDCamRecallThree    调度预置位3
//  *[消息方向]
//  *
//  *   CNS => CnDevice
   _event(  ev_Cn_DCamRecall_Cmd )
   _body( EmDCamRecallNum, 1 )
   _ev_end
// 
//  **********************<< 文档摄像头开关选择回应   >>************************	
//  *[消息体]			 
//  *BOOL = TRUE 开关选择成功，= FALSE 开关选择失败
//  *EmDCamPower:文档摄像头待机唤醒选择
//   emDCamPowerOn        唤醒
//   emDCamPowerOff       待机
//   emDCamPowerToggle    待机与唤醒开关切换  
//  *[消息方向]
//  *
//  *  CnDevice => CNS
   _event(  ev_Cn_DCamPower_Ind )
   _body( BOOL, 1)
   _body( EmDCamPower, 1 )
   _ev_end
// 
//  **********************<< 文档摄像头自动聚焦调节回应   >>************************	
//  *[消息体]			 
//  *BOOL = TRUE 操作成功，= FALSE 操作失败
//  *EmDCamAFMode: 文档摄像机自动聚焦选择
//   emDCamAFOn          开启自动聚焦
//   emDcamAFOff         关闭自动聚焦
//   emDCamAFToggle      自动聚焦开关切换
//  *[消息方向]
//  *
//  *   CnDevice => CNS
   _event(  ev_Cn_DCamAFMode_Ind )
   _body( BOOL, 1)
   _body( EmDCamAFMode, 1 )
   _ev_end
// 
//  **********************<< 文档摄像头白平衡模式设置回应   >>************************	
//  *[消息体]			 
//  *BOOL = TRUE 操作成功，= FALSE 操作失败
//  *EmDCamBWMode: 文档摄像机白平衡模式选择
//   emDcamWBAuto         开启自动白平衡模式
//   emDCamWBManual       开启手动白平衡模式 
//   emDCamOnePush        开启一键式白平衡模式
//  *[消息方向]
//  *
//  *   CnDevice => CNS
   _event(  ev_Cn_DCamWBMode_Ind )
   _body( BOOL, 1)
   _body( EmDCamWBMode, 1 )
   _ev_end
// 
//  **********************<< 文档摄像头视野调节回应   >>************************	
//  *[消息体]			 
//  *BOOL = TRUE 操作成功，= FALSE 操作失败
//  *EmDCamZoom 文档摄像头视野调节
//   emDCamZoomWide       放大视野
//   emDCamZoomTele       缩小视野
//  *u16 当前的zoom值
//  *[消息方向]
//  *
//  *   CnDevice => CNS
   _event(  ev_Cn_DCamZoom_Ind )
   _body(BOOL, 1)
   _body(EmDCamZoom, 1)
   _body(u16 , 1)
   _ev_end
// 
// 
//  **********************<< 保存文档摄像头预置位回应   >>************************	
//  *[消息体]			 
//  *BOOL = TRUE 操作成功，= FALSE 操作失败
//  *EmDCamPresetNum      保存的预置位编号
//   emDCamPresetOne      保存预置位1
//   emDCamPresetTwo      保存预置位2 
//   emDCamPresetThree    保存预置位3
//  *[消息方向]
//  *
//  *   CnDevice => CNS
   _event(  ev_Cn_DCamPreset_Ind )
   _body( BOOL, 1)
   _body( EmDCamPresetNum, 1 )
   _ev_end
// 
//  **********************<< 调度文档摄像头预置位回应   >>************************	
//  *[消息体]			 
//  *BOOL = TRUE 操作成功，= FALSE 操作失败
//  *EmDCamRecallNum      调度的预置位编号
//   emDCamRecallOne      调度预置位1
//   emDCamRecallTwo      调度预置位2 
//   emDCamRecallThree    调度预置位3
//  *[消息方向]
//  *
//  *   CnDevice => CNS
   _event(  ev_Cn_DCamRecall_Ind )
   _body( BOOL, 1)
   _body( EmDCamRecallNum, 1 )
   _ev_end
   
//  **********************<< 文档摄像头操作指令回复超时   >>************************	
//  *[消息体]			 
//  *[消息方向]
//  *
//  *   CnDevice => CNS
   _event(  ev_Cn_DCamCmdAck_Timer )
   _ev_end

//  **********************<< 控制系统电源开关   >>************************	
//  *[消息体]			 
//  *EmSchPower           会议系统电源开关选择
//   emSchPowerOff        关闭会议系统电源
//   emSchPowerOn         开启会议系统电源
//  *[消息方向]
//  *
//  *   CNS => CnDevice
   _event(  ev_Cn_Sch_Power_Cmd )
   _body( EmSchPower, 1 )
   _ev_end

//  **********************<< 系统电源开关回应   >>************************	
//  *[消息体]
//  *BOOL    = TRUE 操作成功， = FALSE 操作失败   		 
//  *EmSchPower           会议系统电源开关选择
//   emSchPowerOff        关闭会议系统电源
//   emSchPowerOn         开启会议系统电源
//  *[消息方向]
//  *
//  *   CnDevice => CNS
   _event(  ev_Cn_Sch_Power_Ind )
   _body( BOOL, 1)
   _body( EmSchPower, 1 )
   _ev_end

//  **********************<< 施耐德电气系统电源开关反馈   >>************************	
//  *[消息体]			 
//  *EmSchPower           会议系统电源开关选择反馈
//   emSchPowerOff        反馈会议系统电源已被关闭
//   emSchPowerOn         反馈会议系统电源已被开启
//  *[消息方向]
//  *
//  *   CnDevice => CNS
   _event(  ev_Cn_Sch_Power_FB_Notify )
   _body( EmSchPower, 1 )
   _ev_end

//  **********************<< 控制灯光系统电源开关   >>************************	
//  *[消息体]			 
//  *EmSchLight           会议系统电源开关选择
//   emSchLightOff        关闭灯光系统电源
//   emSchLightOn         开启灯光系统电源
//  *[消息方向]
//  *
//  *   CNS => CnDevice
   _event(  ev_Cn_Sch_Light_Cmd )
   _body( EmSchLight, 1 )
   _ev_end

//  **********************<<  控制灯光系统电源开关回应  >>************************	
//  *[消息体]			 
//  *BOOL    = TRUE 操作成功， = FALSE 操作失败   		 
//  *EmSchLight           会议系统电源开关选择
//   emSchLightOff        关闭灯光系统电源
//   emSchLightOn         开启灯光系统电源
//  *[消息方向]
//  *
//  *   CnDevice => CNS
   _event(  ev_Cn_Sch_Light_Ind )
   _body( BOOL, 1)
   _body( EmSchLight, 1 )
   _ev_end

//  **********************<< 施耐德电气系统灯光开关反馈   >>************************	
//  *[消息体]			 
//  *EmSchLight           灯光电源开关选择反馈
//   emSchLightOff        反馈灯光电源已被关闭
//   emSchLightOn         反馈灯光电源已被开启
//  *[消息方向]
//  *
//  *   CnDevice => CNS
   _event(  ev_Cn_Sch_Light_FB_Notify )
   _body( EmSchLight, 1 )
   _ev_end

//  **********************<< 控制顶上中前排灯光开关   >>************************	
//  *[消息体]			 
//  *EmSchMidLight           会议系统顶上中前排灯光开关选择
//   emSchMidLightOff        关闭顶上中前排灯光电源
//   emSchMidLightOn         开启顶上中前排灯光电源
//  *[消息方向]
//  *
//  *   CNS => CnDevice
//   _event(  ev_Cn_Sch_MidLight_Cmd )
//  _body( EmSchMidLight, 1 )
//   _ev_end
   
//  **********************<<  控制顶上中前排灯光开关回应  >>************************	
//  *[消息体]			 
//  *BOOL    = TRUE 操作成功， = FALSE 操作失败   		 
//  *EmSchMidLight           会议系统顶上中前排灯光开关选择
//   emSchMidLightOff        关闭顶上中前排灯光电源
//   emSchMidLightOn         开启顶上中前排灯光电源
//  *[消息方向]
//  *
//  *   CnDevice => CNS
   _event(  ev_Cn_Sch_MidLight_Ind )
   _body( BOOL, 1)
   _body( EmSchMidLight, 1 )
   _ev_end
   
//  **********************<< 施耐德电气系统顶上中前排灯光开关开关反馈   >>************************	
//  *[消息体]			 
//  *EmSchMidLight           顶上中前排灯光开关选择反馈
//   emSchMidLightOff        反馈顶上中前排灯光已被关闭
//   emSchMidLightOn         反馈顶上中前排灯光已被开启
//  *[消息方向]
//  *
//  *   CnDevice => CNS
   _event(  ev_Cn_Sch_MidLight_FB_Notify )
   _body( EmSchMidLight, 1 )
   _ev_end

   //  **********************<< 控制机柜面光灯开关   >>************************	
   //  *[消息体]			 
   //  *EmSchScrLight           会议系统顶上中前排灯光开关选择
   //   emSchScrLightOff        关闭机柜面光灯电源
   //   emSchScrLightOn         开启机柜面光灯电源
   //  *[消息方向]
   //  *
   //  *   CNS => CnDevice
   _event(  ev_Cn_Sch_ScrLight_Cmd )
   _body( EmSchScrLight, 1 )
   _ev_end
   
   //  **********************<<  控制机柜面光灯开关回应  >>************************	
   //  *[消息体]			 
   //  *BOOL    = TRUE 操作成功， = FALSE 操作失败   		 
   //  *EmSchScrLight           会议系统顶上中前排灯光开关选择
   //   emSchScrLightOff        关闭机柜面光灯电源
   //   emSchScrLightOn         开启机柜面光灯电源
   //  *[消息方向]
   //  *
   //  *   CnDevice => CNS
   _event(  ev_Cn_Sch_ScrLight_Ind )
   _body( BOOL, 1)
   _body( EmSchScrLight, 1 )
   _ev_end
   
   //  **********************<< 施耐德电气系统控制机柜面光灯开关反馈   >>************************	
   //  *[消息体]			 
   //  *EmSchScrLight           顶上中前排灯光开关选择反馈
   //   emSchScrLightOff        反馈机柜面光灯已被关闭
   //   emSchScrLightOn         反馈机柜面光灯已被开启
   //  *[消息方向]
   //  *
   //  *   CnDevice => CNS
   _event(  ev_Cn_Sch_ScrLight_FB_Notify )
   _body( EmSchScrLight, 1 )
   _ev_end


//  **********************<< 控制人体感应器的锁定与解锁   >>************************	
//  *[消息体]			 
//  *EmSchArgus           人体感应器锁定与解除锁定选择
//   emSchArgusUnlock     解除人体感应器的锁定
//   emSchArgusLock       锁定人体感应器
//  *[消息方向]
//  *
//  *   CNS => CnDevice
   _event(  ev_Cn_Sch_Argus_Cmd )
   _body( EmSchArgus, 1 )
   _ev_end

//  **********************<< 施耐德电气系统感应器锁定与解锁状态反馈   >>************************	
//  *[消息体]			 
//  *EmSchArgus           反馈人体感应器锁定与解除锁定状态
//   emSchArgusUnlock     反馈人体感应器已被解锁
//   emSchArgusLock       反馈人体感应器已被锁定
//  *[消息方向]
//  *
//  *   CnDevice => CNS
   _event(  ev_Cn_Sch_Argus_FB_Notify )
   _body( EmSchArgus, 1 )
   _ev_end

//  **********************<< 施耐德电气系统室内温度反馈   >>************************	
//  *[消息体]			 
//  *u16 预置位编号
//  *[消息方向]
//  *
//  *   CnDevice => CNS
   _event(  ev_Cn_Sch_Temp_FB_Notify )
   _body( u16, 1)
   _ev_end

//  **********************<< 施耐德电气操作指令回复超时   >>************************	
//  *[消息体]			 
//  *[消息方向]
//  *
//  *   CNS => CnDevice
   _event(  ev_Cn_SchCmdAck_Timer )
   _ev_end

/***********************<< 向施耐德电气系统发送任意操作指令 >>************************	
 *[消息体]			 
 *    + s8  写入施耐德电气控制串口的操作指令 施耐德消息命令长度均为8
 *[消息方向]
 *
 *   CNS => CnDevice
 */_event(  ev_Cn_Sch_Set_Cmd )
   _body (   u8        ,    8 )
   _ev_end

/***********************<< 设定T300关闭系统电源后解除人体感应器锁定的超时 >>************************	
 *[消息体]			 
 *
 *[消息方向]
 *
 *   CnDevice => CnDevice
 */_event(  ev_Cn_Sch_UnlockArgus_Timer )
   _ev_end

/***********************<< 系统强电开关通知 >>************************	
 *[消息体]			 
 //  *EmSchPower           会议系统电源开关选择
 //   emSchPowerOff        关闭会议系统电源
 //   emSchPowerOn         开启会议系统电源
 *[消息方向]
 *
 *   CnDevice => CnDevice
 */_event(  ev_Cn_Cenctrl_SysPower_Nty )
   _body( EmSchPower, 1 )
   _ev_end

//End Add

//add for air-control by zhangapei
/***********************<< 通知界面空调配置 >>************************	
 *[消息体]
 *  + TCentreACCfg   空调配置列表
 *  + BOOL           空调列表  TRUE 该位置空调存在 FALSE 该位置空调不存在
 *  
 *[消息方向]
 *   
 *      UI => Cndevice 
 */_event(  ev_cns_centreACStateNty   )
   _body(   TCentreACInfo, 1  )
   _ev_end

/***********************<< 设定中控空调开关 >>************************	
 *[消息体]	
 *    + EmCentreACPower  Off/On
 *
 *[消息方向]
 *
 *   Cns => CnDevice
 */_event(  ev_Cn_CentreSetACPowerCmd )
   _body(   u8             ,      1  )
   _body(   EmCentreACPower,      1  )
   _ev_end

/***********************<< 设定中控空调开关返回消息 >>************************	
 *[消息体]	
 *    + EmCentreACPower  Off/On
 *    + BOOL 设置成功TRUE， 失败FALSE
 *
 *[消息方向]
 *
 *   Cns => CnDevice
 */_event(  ev_Cn_CentreSetACPowerInd )
   _body(   u8             ,      1  )
   _body(   EmCentreACPower,      1  )
   _body(   BOOL ,                1  )
   _ev_end

/***********************<< 设定中控空调温度命令 >>************************	
 *[消息体]	
 *    + u8   温度  17°C -- 30°C
 *
 *[消息方向]
 *
 *   Cns => CnDevice
 */_event(  ev_Cn_CentreSetACTempCmd )
   _body(  u8   ,                1  )
   _ev_end

/***********************<< 设定中控空调温度返回消息 >>************************	
 *[消息体]	
 *    + u8   温度  17°C -- 30°C
 *    + BOOL 设置成功TRUE， 失败FALSE
 *
 *[消息方向]
 *
 *   Cns => CnDevice
 */_event(  ev_Cn_CentreSetACTempInd )
   _body(   u8   ,                1  )
   _body(   BOOL ,                1  )
   _ev_end


/***********************<< 设定中控空调模式 >>************************	
 *[消息体]		
 *     + EmCentreACMode    
 *
 *[消息方向]
 *
 *   Cns => CnDevice
 */_event(  ev_Cn_CentreSetACModeCmd )
   _body(   EmCentreACMode  ,     1  )
   _ev_end

/***********************<< 设定中控空调模式返回消息 >>************************	
 *[消息体]		
 *     + EmCentreACMode 
 *     + BOOL          设置成功TRUE/失败FALSE
 *
 *[消息方向]
 *
 *   Cns => CnDevice
 */_event(  ev_Cn_CentreSetACModeInd )
   _body(   EmCentreACMode  ,     1  )
   _body(   BOOL ,                1  )
   _ev_end


/***********************<< 设定中控空调新风风量 >>************************	
 *[消息体]		
 *     + EmCentreACAirVol   自动、1--5 
 *
 *[消息方向]
 *
 *   Cns=> CnDevice
 */_event(  ev_Cn_CentreSetACAirVolCmd )
   _body(   EmCentreACAirVol,     1  )
   _ev_end


/***********************<< 设定中控空调新风风量返回消息 >>************************	
 *[消息体]		
 *     + u8    共9级   
 *     + BOOL  设置成功TRUE ， 失败 FALSE
 *
 *[消息方向]
 *
 *   Cns=> CnDevice
 */_event(  ev_Cn_CentreSetAirVolInd )
   _body(   EmCentreACAirVol,     1  )
   _body(   BOOL ,                1  )
   _ev_end

/***********************<< 向空调设备发送任意操作指令 >>************************	
*[消息体]			 
*    + s8  写入空调控制串口的操作指令
*[消息方向]
*
*   CnDevice => CnDevice
*/_event(  ev_Cn_AC_Set_Cmd )
  _body (   s8        ,    1 )
  _ev_end

//add end

//set Timer for sleep  
/***********************<< 呼叫状态通知 >>************************	
 *[消息体]		
 *     +EmCALLSTATE  	em_CALL_IDLE      空闲
 *						em_CALL_CALLING   正在呼叫
 *						em_CALL_CONNECTED 入会
 *
 *[消息方向]  
 * CnCall => CnDevice
 */_event(  ev_Cn_CallStateNty     )
   _body(   EmCALLSTATE,         1 )
   _ev_end

/***********************<< 设定待机定时器 >>************************	
 *[消息体]		
 *NULL
 *
 *[消息方向]  
 * CnDevice => CnDevice
 */_event(  ev_Cn_DeviceSleep_Timer )
   _ev_end

/***********************<< 施耐德待机/唤醒通知 >>************************	
 *[消息体]		
 *    +EmCenSchMode     emSchSleep/待机   emSchWakeUp/唤醒
 *
 *[消息方向]  
 *
 * CnDevice => CnDevice
 */_event(  ev_Cn_CentreSchSleepNty )
   _body(   EmCenSchMode,       1   )
   _ev_end

/***********************<< 设置待机信息 >>************************	
 *[消息体]		
 *    + TTPSleepInfo 待机信息设置
 *
 *[消息方向]  
 *
 * UE => CnDevice
 */_event(  ev_Cn_SetSleepInfoCmd )
   _body(   TCenDevSleepInfo ,   1    )
   _ev_end

/***********************<< 设置待机信息应答 >>************************	
 *[消息体]		
 *    + TTPSleepInfo 待机信息设置
 *    + Bool  =FALSE 修改失败，= TRUE 修改成功
 *
 *[消息方向]  
 *
 * UE => CnDevice
 */_event(  ev_Cn_SetSleepInfoInd )
   _body(   TCenDevSleepInfo , 1  )
   _body(   BOOL             , 1  )
   _ev_end

/***********************<< 界面操作通知 >>************************	
 *[消息体]		
 *    +u8    node_cnc/node_cnstools
 *
 *[消息方向]  
 *
 * UE => CnDevice
 */_event(  ev_Cn_UEMsgNty )
   _body(   u8 ,      1    )
   _ev_end

/***********************<< 中控待机通知界面 >>************************	
 *[消息体]		
 *
 *[消息方向]  
 *
 * UE <= CnDevice
 */_event(  ev_Cn_CentreSleepNty )
   _ev_end

 /***********************<< 空调选择消息 >>************************	
 *[消息体]
 *  + u8   空调选择索引
 *  
 *[消息方向]
 *   
 *      UI => Cndevice 
 */_event(  ev_cns_centreSelectAC_Cmd   )
   _body(   u8            ,         1   )
   _ev_end

 /***********************<< 空调选择返回消息 >>************************	
 *[消息体]
 *  + u8   空调选择索引
 *  + BOOL 操作结果
 *  
 *[消息方向]
 *   
 *      UI => Cndevice 
 */_event(  ev_cns_centreSelectAC_Ind   )
   _body(   u8            ,         1   )
   _body(   BOOL          ,         1   )
   _ev_end

/***********************<< 空调配置拷贝 >>************************	
 *[消息体]
 *  + u8        选中空调索引号
 *  + BOOL      要修改的空调列表 = TRUE 要复制修改 =FALSE 不需要修改
 *  
 *[消息方向]
 *   
 *      UI => Cndevice 
 */_event(  ev_cns_centreACCopyCmd   )
   _body(   u8        , 1            )
   _body(   BOOL      , MAX_AC_NUM   )
   _ev_end

/***********************<< 空调配置拷贝返回消息 >>************************	
 *[消息体]
 *  + BOOL      要修改的空调列表
 *  + BOOL      修改结果
 *  
 *[消息方向]
 *   
 *      UI => Cndevice 
 */_event(  ev_cns_centreACCopyInd   )
   _body(   BOOL        , MAX_AC_NUM )
   _body(   BOOL        , 1          )
   _ev_end

/***********************<< CNC地址薄操作通知 >>************************	
 *[消息体]
 *
 *  
 *[消息方向]
 *   
 *      cnc => cns 
 */_event(  ev_cns_cncAddrBookNty   )
   _ev_end

/***********************<< 系统开关上电延时打开电视机 >>************************	
 *[消息体]
 *
 *  
 *[消息方向]
 *   
 *      cnc => cns 
 */_event(  ev_Cn_SetTvPowerTimer   )
   _ev_end
   
/*************************<< 中控，窗帘动作命令  >>******************************	
 *[消息体]
 * +BOOL         窗帘列表，=TRUE标识选中需要修改，=FALSE标识，没有选中
 * +EmCurAction  窗帘动作，emCurUp 上升 emCurDown 下降 emCurStop 停止
 *  
 *[消息方向]
 *   
 *      cnc => cns 
 */_event(  ev_Cn_centreCurActCmd      )
   _body(BOOL       , MAX_CURTAIN_NUM  )
   _body(EmCurAction, 1                )
   _ev_end

/*************************<< 中控，窗帘动作反馈  >>******************************	
 *[消息体]
 * +BOOL         窗帘列表，=TRUE标识选中需要修改，=FALSE标识，没有选中
 * +EmCurAction  窗帘动作，emCurUp 上升 emCurDown 下降 emCurStop 停止
 * +BOOL         窗帘设置列表 =TRUE设置成功  =FALSE 设置失败      
 *[消息方向]
 *   
 *      cnc => cns 
 */_event(  ev_Cn_centreCurActInd      )
   _body(BOOL       , MAX_CURTAIN_NUM  )
   _body(EmCurAction, 1                )
   _body(BOOL       , MAX_CURTAIN_NUM  )
   _ev_end

/*************************<< 中控，窗帘名称通知  >>******************************	
 *[消息体]
 *
 * +TCentreCurInfo 窗帘信息
 *  
 *[消息方向]
 *   
 *      cnc => cns 
 */_event(  ev_Cn_centreCurInfoNty)
   _body(TCentreCurInfo,		1 )
   _ev_end

/**********************<< 韩光摄像机启动之后定时调用预置位 >>*************************	
 *[消息体]
 *  
 *[消息方向]
 *   
 *      cnc => cns 
 */_event(  ev_Cn_SetDocRecallPresetTimer  )
   _ev_end

/**********************<< 响应窗帘操作命令后定时关闭所有窗帘电机回路 >>*************************	
 *[消息体]
 *  
 *[消息方向]
 *   
 *      cns => cns 
 */_event(  ev_Cn_SetCurtainPowerDownTimer  )
   _ev_end


 /***********************<< 串口数据反馈  >>************************	
 *[消息体]		
 *    + u8    串口类型
 *    + u8    数据内容
 *
 *[消息方向]
 *
 *   CNS => CnDevice
 */_event(  ev_Cn_SerialRecvByteInd  )
   _body (  u8          ,    1  )
   _body (  u8          ,    1  )
   _ev_end

   _event(  ev_cns_centreTV0InputSelKeepTimer  )
   _ev_end

   _event(  ev_cns_centreTV1InputSelKeepTimer  )
   _ev_end

   _event(  ev_cns_centreTV2InputSelKeepTimer  )
   _ev_end
   
   
//Add end
/***********************<< 系统开关上电延时打开电视机 >>************************	
 *[消息体]
 *
 *  
 *[消息方向]
 *   
 *      cns => cns 
 */_event(  ev_Cn_SetTvInpSelectTimer   )
   _ev_end

/***********************<< 文档摄像机电源开关保护定时器 >>************************	
 *[消息体]
 *
 *  
 *[消息方向]
 *   
 *      cns => cns 
 */_event(  ev_Cn_SetDCamPowerKeepTimer   )
   _ev_end

/*************************<< 设置中控窗帘名称  >>******************************	
 *[消息体]
 * +u8  窗帘索引
 * +s8  窗帘名
 *  
 *[消息方向]
 *   
 *      cnc => cns 
 */_event(  ev_Cn_centreCurNameCmd  )
   _body(	u8            ,      1  )
   _body(   TCentreCurName,		 1  )
   _ev_end

/*************************<< 设置中控窗帘是否存在  >>******************************	
 *[消息体]
 *  +BOOL  = TURE 窗帘存在，= FALSE 不存在
 *  
 *[消息方向]
 *   
 *      cnc => cns 
 */_event(  ev_Cn_centreCurOpenCmd  )
   _body(	BOOL          ,      1  )
   _ev_end

/*************************<< 设置中控窗帘数  >>******************************	
 *[消息体]
 *  +u8   num 窗帘数
 *  
 *[消息方向]
 *   
 *      cnc => cns 
 */_event(  ev_Cn_centreCurNumCmd  )
   _body(	u8           ,      1  )
   _ev_end

/*************************<< 设置中控电视机型号  >>******************************	
 *[消息体]
 * +u8  窗帘索引
 * +s8  窗帘名
 *  
 *[消息方向]
 *   
 *      cnc => cns 
 */_event(  ev_Cn_centreTVModleCmd  )
   _body(	EmTVModle        ,      1  )
   _ev_end

/*************************<< 电视机型号设置反馈  >>******************************	
 *[消息体]
 * +u8  窗帘索引
 * +s8  窗帘名
 *  
 *[消息方向]
 *   
 *      cnc => cns 
 */_event(  ev_Cn_centreTVModleInd  )
   _body(	EmTVModle        ,      1  )
   _body(   BOOL			 ,		1  )
   _ev_end

//文档摄像机添加新功能  2015/3/16 
/*************************<< 文档摄像机焦距调节  >>******************************	
 *[消息体]
 * +EmFocus  emNear 拉近  emFar 推远
 * +EmCnAction emCnStart 开始 emCnStop 停止
 *[消息方向]
 *   
 *      ui => cndevice 
 */_event(  ev_Cn_DCamFocusCmd  )
   _body(	EmFocus       ,    1  )
   _body(   EmCnAction    ,    1  )
   _ev_end

/***********************<< 摄像机自动曝光命令 >>************************	
 *[消息体]			 
 *   EmExpMode   
 *
 *[消息方向]
 *   
 *   ui => cndevice 
 */_event(  ev_Cn_DCamAutoExposureCmd  )
   _body (  EmExpMode,                1)
   _ev_end

/***********************<< 摄像机自动曝光反馈 >>************************	
 *[消息体]			 
 *   EmExpMode   
 *   BOOL      FALSE 设置失败  TRUE 成功
 *
 *[消息方向]
 *   
 *   cndevice => ui
 */_event(  ev_Cn_DCamAutoExposureInd )
   _body (  EmExpMode,               1)
   _body (  BOOL     ,               1)
   _ev_end

/***********************<< 摄像机手动曝光——增益调节命令 >>************************	
 *[消息体]
 *
 * EmDCamGain  增益范围 0dB  3dB  6dB ···42dB
 *
 *[消息方向]
 *  
 *   ui => cndevice 
 */_event(  ev_Cn_DCamGainCmd  )
   _body (  EmDCamGain       ,1)
   _ev_end

/***********************<< 摄像机手动曝光——增益调节反馈 >>************************	
 *[消息体]
 *
 * EmGain  增益范围
 * BOOL    设置结果
 *
 *[消息方向]
 *  
 *   cndevice => ui
 */_event(  ev_Cn_DCamGainInd  )
   _body (  EmDCamGain,		  1)
   _body (  BOOL      ,		  1)
   _ev_end
   

/***********************<< 摄像机手动曝光——快门调节命令 >>************************	
 *[消息体]
 *
 * EmDCamShutSpd  快门范围 
 *
 *[消息方向]
 *   
 *   ui => cndevice 
 */_event(  ev_Cn_DCamShutSpdCmd  )
   _body (  EmDCamShutSpd    ,   1)
   _ev_end

/***********************<< 摄像机手动曝光——快门调节反馈 >>************************	
 *[消息体]
 *
 * EmDCamShutSpd  快门范围 
 * BOOL           设置结果
 *
 *[消息方向]
 *   
 *   cndevice => ui 
 */_event(  ev_Cn_DCamShutSpdInd  )
   _body (  EmDCamShutSpd,       1)
   _body (  BOOL		 ,       1)
   _ev_end


/***********************<< 摄像机手动曝光——光圈调节命令 >>************************	
 *[消息体]
 *
 * EmDCamIris 光圈
 *
 *[消息方向]
 *   
 *   ui => cndevice 
 */_event(  ev_Cn_DCamApertureCmd)
   _body (  EmDCamIris    ,     1)
   _ev_end

/***********************<< 摄像机手动曝光——光圈调节反馈 >>************************	
 *[消息体]
 *
 * EmDCamIris  光圈
 * BOOL        设置结果
 *
 *[消息方向]
 *   
 *   cndevice => ui 
 */_event(  ev_Cn_DCamApertureInd)
   _body (  EmDCamIris    ,     1)
   _body (  BOOL		  ,     1)
   _ev_end

/***********************<< 摄像机R增益调节命令 >>************************	
 *[消息体]
 *
 * u16 增益 0--255
 *
 *[消息方向]
 *   
 *   ui => cndevice 
 */_event(  ev_Cn_DCamRGainCmd)
   _body (  u16        ,     1)
   _ev_end

/***********************<< 摄像机R增益反馈 >>************************	
 *[消息体]
 * u16      增益 0--255
 * BOOL     设置结果
 *
 *[消息方向]
 *   
 *   cndevice => ui 
 */_event(  ev_Cn_DCamRGainInd)
   _body (  u16        ,     1)
   _body (  BOOL	   ,     1)
   _ev_end

/***********************<< 摄像机BGain命令 >>************************	
 *[消息体]
 * u16      增益 0--255
 *
 *[消息方向]
 *   
 *   ui => cndevice 
 */_event(  ev_Cn_DCamBGainCmd)
   _body (  u16        ,     1)
   _ev_end

/***********************<< 摄像机B增益反馈 >>************************	
 *[消息体]
 * u16         增益 0--255
 * BOOL        设置结果
 *
 *[消息方向]
 *   
 *   cndevice => ui 
 */_event(  ev_Cn_DCamBGainInd)
   _body (  u16        ,     1)
   _body (  BOOL	   ,     1)
   _ev_end

/***********************<< 文档摄像机Zoom设置 >>************************	
 *[消息体]
 * u16         Zoom值
 *
 *[消息方向]
 *   
 *   cndevice => ui 
 */_event(  ev_Cn_SetDCamZoom_Cmd)
   _body (  u16        ,        1)
   _ev_end

/***********************<< 文档摄像机Zoom设置反馈 >>************************	
 *[消息体]
 * u16         Zoom值
 * BOOL        设置结果
 *
 *[消息方向]
 *   
 *   cndevice => ui 
 */_event(  ev_Cn_SetDCamZoom_Ind)
   _body (  u16        ,        1)
   _body (  BOOL	   ,		1)
   _ev_end


/***********************<< 文档摄像机设置开机调用预置位 >>*********************	
 *[消息体]
 * BOOL         =TRUE 开机调用预置位 =FALSE 关闭调用 
 *
 *[消息方向]
 *   
 *   cndevice => ui 
 */_event(  ev_Cn_SetDCamPreset_Cmd)
   _body (  BOOL	   ,        1  )
   _ev_end


/*************************<< 设置中控窗帘名称  >>******************************	
 *[消息体]
 * +u8   窗帘索引
 * +s8   窗帘名
 * +BOOL 设置结果
 *  
 *[消息方向]
 *   
 *      cnc => cns 
 */_event(  ev_Cn_centreCurNameInd  )
   _body(	u8            ,      1  )
   _body(   TCentreCurName,		 1  )
   _body(   BOOL		  ,		 1  )
   _ev_end

/*************************<< 设置中控窗帘是否存在  >>******************************	
 *[消息体]
 *  +BOOL  = TURE 窗帘存在，= FALSE 不存在
 *  +BOOL  设置结果
 *  
 *[消息方向]
 *   
 *      cnc => cns 
 */_event(  ev_Cn_centreCurOpenInd  )
   _body(	BOOL          ,      2  )
   _ev_end

/*************************<< 设置中控窗帘数  >>******************************	
 *[消息体]
 *  +u8   num 窗帘数
 *  +BOOL 设置结果
 *  
 *[消息方向]
 *   
 *      cnc => cns 
 */_event(  ev_Cn_centreCurNumInd  )
   _body(	u8           ,      1  )
   _body(   BOOL		 ,		1  )
   _ev_end

/*************************<< 文档摄像机快照  >>******************************	
 *[消息体]
 *  
 *[消息方向]
 *   
 *      cnc => cns 
 */_event(  ev_Cn_DocSetSnapShotCmd )
   _ev_end

 /*************************<< 文档摄像机快照结果  >>******************************	
 *[消息体]
 *  +BOOL 设置结果
 *  
 *[消息方向]
 *   
 *      cnc => cns 
 */_event(  ev_Cn_DocSetSnapShotInd )
   _body (BOOL ,         1          )
   _ev_end

   
/***********************<< 文档摄像机设置开机调用预置位反馈 >>*********************	
 *[消息体]
 * BOOL         =TRUE 设置成功 =FALSE 设置失败
 * BOOL         =TRUE 开机调用预置位 =FALSE 关闭调用 
 *
 *[消息方向]
 *   
 *   cndevice => tptool 
 */_event(  ev_Cn_SetDCamPreset_Ind)
   _body (BOOL, 1)
   _body (BOOL, 1)
   _ev_end
 
/***********************<< cndevice将待机信息通知cnue >>************************	
 *[消息体]		
 *BOOL		=TRUE 待机状态 唤醒 =FALSE 待机
 *BOOL		=TRUE 会议空闲      =FALSE 在会
 *
 *[消息方向]  
 * CnDevice => Cnue
 */_event(  ev_Cn_DeviceSleepInfo_Nty)
   _body (BOOL, 1)
   _body (BOOL, 1)
   _ev_end


    /***********************<< 串口数据反馈  >>************************	
 *[消息体]		
 *    + u8    串口类型
 *    + u8    数据内容
 *
 *[消息方向]
 *
 *   CNS => CnDevice
 */

   _event(  ev_cns_centreTVModeTimer  )
   _ev_end 

    /***********************<< 文档摄像机上电检测定时器  >>************************ 
 *[消息体]     
 *
 *[消息方向]
 *   CnDevice => CnDevice
 */

   _event(  ev_Cn_CheckDCamPowerTimer  )
   _ev_end 


//add end


		
#ifndef _MakeTpEventDescription_
		_ev_segment_end( outercnscentre )
};
#endif
#endif 
