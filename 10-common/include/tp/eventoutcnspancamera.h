#ifndef _h_eventoutcnspancamera_h__
#define _h_eventoutcnspancamera_h__

#include "cnseventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmCNSPANCAMEVENT
{
#endif 
	
	_ev_segment( outercnspancamera  )

/***********************<< 全景摄像机选择 >>************************	
 *[消息体]
 *  + u8  摄像机索引
 *  
 *[消息方向]
 *   
 *      UI => Cndevice 
 */_event( ev_Cns_PanCamSelectCmd )
   _body(  u8,                  1 )
   _ev_end

/***********************<< 全景摄像机选择反馈 >>************************	
 *[消息体]
 *  + u8  摄像机索引
 *  + BOOL 
 *  
 *[消息方向]
 *   
 *      UI => Cndevice 
 */_event( ev_Cns_PanCamSelectInd )
   _body(  u8,                  1 )
   _body(  BOOL,				1 )
   _ev_end



/***********************<< 全景摄像机调节PT >>************************	
 *[消息体]
 *  + EmDirection  移动方向  Up Down Left Right
 *  + EmAction     操作      emStrat  emStop
 *  
 *[消息方向]
 *   
 *      UI => Cndevice 
 */_event( ev_Cns_PanCamPTCmd )
   _body(  EmDirection,     1 )
   _body(  EmCnAction ,     1 )
   _ev_end

/***********************<< 全景摄像机自动调节 >>************************	
 *[消息体]
 *  
 *  
 *[消息方向]
 *   
 *      UI => Cndevice 
 */_event( ev_Cns_PanCamAutoFocusCmd )
   _ev_end

/***********************<< 全景摄像机焦距调节 >>************************	
 *[消息体]
 *  + EmFocus  emFar 远焦  emNear 近焦
 *  + EmCnAction  调焦为手动时的操作
 *  
 *[消息方向]
 *   
 *      UI => Cndevice 
 */_event( ev_Cns_PanCamFocusCmd )
   _body(  EmFocus   ,         1 )
   _body(  EmCnAction,         1 )
   _ev_end

/***********************<< 全景摄像机zoom调节 >>************************	
 *[消息体]
 *  + EmZoom   emTele  拉近   emWide 拉远
 *  
 *[消息方向]
 *   
 *      UI => Cndevice 
 */_event( ev_Cns_PanCamZoomCmd )
   _body(  EmZoom  ,          1 )
   _body(  EmCnAction,        1 )
   _ev_end

/***********************<< 全景摄像机保存预置位 >>************************	
 *[消息体]
 *  +  u8    预置位索引
 *  
 *[消息方向]
 *   
 *      UI => Cndevice 
 */_event( ev_Cns_PanCamSavePresetCmd )
   _body(  u8  ,           1 )
   _ev_end

/***********************<< 全景摄像机保存预置位反馈 >>************************	
 *[消息体]
 *  +  u8    预置位索引
 *  +  BOOL  保存结果 TRUE 成功
 *  
 *[消息方向]
 *   
 *      UI => Cndevice 
 */_event( ev_Cns_PanCamSavePresetInd )
   _body(  u8  ,           1 )
   _body(  BOOL,		   1 )
   _ev_end

/***********************<< 全景摄像机调用预置位 >>************************	
 *[消息体]
 *  +  u8    预置位索引
 *  
 *[消息方向]
 *   
 *      UI => Cndevice 
 */_event( ev_Cns_PanCamPresetMoveCmd )
   _body(  u8  ,           1 )
   _ev_end

/***********************<< 全景摄像机调用预置位反馈 >>************************	
 *[消息体]
 *  +  u8    预置位索引
 *  +  BOOL  保存结果 TRUE 成功
 *  
 *[消息方向]
 *   
 *      UI => Cndevice 
 */_event( ev_Cns_PanCamPresetMoveInd )
   _body(  u8  ,           1 )
   _body(  BOOL,		   1 )
   _ev_end

/***********************<< 全景摄像机删除预置位 >>************************	
 *[消息体]
 *  +  u8    预置位索引
 *  
 *[消息方向]
 *   
 *      UI => Cndevice 
 */_event( ev_Cns_PanCamPresetDeleteCmd )
   _body(  u8  ,           1 )
   _ev_end

/***********************<< 全景摄像机删除预置位反馈 >>************************	
 *[消息体]
 *  +  u8    预置位索引
 *  +  BOOL  删除结果
 *  
 *[消息方向]
 *   
 *      UI => Cndevice 
 */_event( ev_Cns_PanCamPresetDeleteInd )
   _body(  u8		  ,		  1    )
   _body(  BOOL       ,		  1    )
   _ev_end


/***********************<< 全景摄像机亮度调节 >>************************	
 *[消息体]
 *  + EmPanCamBright  up 亮度增加  Down 亮度减少
 *  
 *[消息方向]
 *   
 *      UI => Cndevice 
 */_event( ev_Cns_PanCamBackLightCmd )
   _body(  EmPanCamBright,    1 )
   _body(  EmCnAction,        1 )
   _ev_end

/***********************<< 全景摄像机信息通知 >>************************	
 *[消息体]
 *  +TCentrePanCamInfo   全景摄像机
 *  +u8                  全景摄像机当前索引
 *  
 *[消息方向]
 *   
 *      UI => Cndevice 
 */_event( ev_Cns_PanCamCfgNty  )
   _body(  TPanCamInfo,       1 )
   _body(  u8		  ,       1 )
   _ev_end

/***********************<< 全景摄像机数量设置 >>************************	
 *[消息体]
 *  + u8   全景摄像机数目
 *  
 *[消息方向]
 *   
 *      UI => Cndevice 
 */_event( ev_Cns_SetPanCamNumCmd )
   _body(  u8    ,              1 )
   _ev_end

/***********************<< 全景摄像机开关 >>************************	
 *[消息体]   
 * + u8    全景摄像机索引
 * + BOOL  =TRUE 启用全景摄像机 
 *  
 *[消息方向]
 *   
 *       => Cndevice 
 */_event( ev_Cns_SetPanCamOpenCmd )
   _body(  BOOL  ,               1 )
   _body(  u8    ,				 1 )
   _ev_end

/***********************<< 维护工具登陆通知 >>************************	
 *[消息体]
 *  
 *[消息方向]
 *   
 *       => Cndevice 
 */_event( ev_cns_CnsToolsOnLineNty_Req )
   _ev_end

   /***********************<< TPad登陆通知 >>************************	
 *[消息体]
 *  
 *[消息方向]
 *   
 *       => Cndevice 
 */_event( ev_cns_CnsTPadOnLineNty_Req )
   _ev_end

/***********************<< 全景摄像机预置位名设置 >>************************	
 *[消息体]
 *  + u8  预置位索引
 *  + TPanCamName  预置位名
 *  
 *[消息方向]
 *   
 *       => Cndevice 
 */_event( ev_Cns_SetPanCamNameCmd )
   _body(  u8         ,       1    )
   _body(  TPanCamName,       1    )
   _ev_end

/***********************<< 全景摄像机预置位名设置 >>************************	
 *[消息体]
 *  + u8  预置位索引
 *  + BOOL名称设置结果
 *  + 
 *  
 *[消息方向]
 *   
 *       => Cndevice 
 */_event( ev_Cns_SetPanCamNameInd )
   _body(  u8		  ,		  1    )
   _body(  BOOL       ,       1    )
   _ev_end

/***********************<< 全景摄像机开关回应消息 >>************************	
 *[消息体]   
 * + u8    全景摄像机索引
 * + BOOL  =TRUE 启用全景摄像机 
 *  
 *[消息方向]
 *   
 *       => CnUE
 */_event( ev_Cns_SetPanCamOpenInd )
   _body(  BOOL  ,               1 )
   _body(  u8    ,				 1 )
   _ev_end

/***********************<< 全景摄像机设置数量回应消息 >>************************	
 *[消息体]   
 * + BOOL  =TRUE 数量设置成功
 * + u8    设置的数量
 *  
 *[消息方向]
 *   
 *       => CNtool
 */_event( ev_Cns_SetPanCamNumInd )
   _body(  BOOL  ,               1 )
   _body(  u8    ,				 1 )
   _ev_end


/***********************<< 全景摄像机设置灯光定时器消息 >>************************	
 *[消息体]   
 * + BOOL  =TRUE 数量设置成功
 * + u8    设置的数量
 *  
 *[消息方向]
 *   
 *  CnDevice  => CnDevice
 */_event( ev_CnsBackLight_Timer )
   _ev_end


/***********************<< 全景摄像机切源后关闭全景摄像机 >>************************	
 *[消息体]   
 * + BOOL  =TRUE 数量设置成功
 * + u8    设置的数量
 *  
 *[消息方向]
 *   
 *  CnDevice  => CnDevice
 */_event( ev_SecMainVideoChange_Nty )
   _ev_end

/***********************<< 全景摄像机类型设置 >>************************	
 *[消息体]
 *  + EmQCamProType   全景摄像机类型设置
 *  
 *[消息方向]
 *   
 *      UI => Cndevice 
 */_event( ev_Cns_SetPanCamTypeCmd )
   _body(  EmQCamProType    ,              1 )
   _ev_end

   /***********************<< 全景摄像机类型设置 >>************************	
 *[消息体]
 *  + EmQCamProType   全景摄像机类型设置
 *  
 *[消息方向]
 *   
 *      UI => Cndevice 
 */_event( ev_Cns_SetPanCamTypeInd )
 _body(  BOOL  ,               1 )
 _body(  EmQCamProType    ,              1 ) 
 _ev_end
		
#ifndef _MakeTpEventDescription_
		_ev_segment_end( outercnspancamera )
};
#endif
#endif 
