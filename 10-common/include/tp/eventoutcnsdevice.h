#ifndef _h_eventoutcnsdevice_h__
#define _h_eventoutcnsdevice_h__

#include "cnseventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmCNSDEVICEEVENT
{
#endif 

  _ev_segment( outercnsdevice  )

	  //serial begin.
	  /*********************<< 配置串口参数  >>****************************	
 *[消息体]			 
 *    + EmSerialType     232/422/485
 *    + TSerialCfg
 *
 *[消息方向]
 *
 *   UI          => MtService
 *   MtService   => MtDevice
 */_event(  ev_SerialPortConfigCmd  )
   _body ( EmSerialType ,1 )
   _body ( TSerialCfg   ,1 )
   _ev_end

/*********************<< 发送透明串口数据  >>****************************	
 *[消息体]			 
 *    + TTransparentSerial
 *[消息方向]
 *
 *   MtService   => UI
 */_event(  ev_TransparentSerialDataCmd )
   _body ( TTransparentSerial ,1 )
   _ev_end
   

/*********************<< 接收透明串口数据  >>****************************	
 *[消息体]			 
 *    + TTransparentSerial
 *[消息方向]
 *
 *   MtService   => UI
 */_event(  ev_TransparentSerialDataInd)
   _body ( TTransparentSerial ,1 )
   _ev_end
	  //serial end.

	  //file_trans begin.
	  /***********************<< MTC请求下载文件 >>********************	
	  *[消息体]			 
	  *   + u8	文件类型
	  *[消息方向]
	  *    MTC => UE
	  */_event(  ev_FTDownLoadReq )
	  _body ( u8    ,1         )
	  _ev_end
	  
	  /***********************<< MTC请求下载文件被拒绝 >>********************	
	  *[消息体]			 
	  *   + u8	原因
	  *[消息方向]
	  *    UE => MTC
	  */_event(  ev_FTDownLoadNACK )
	  _body ( u8    ,1         )
	  _ev_end
	  
	  /***********************<< MTC请求下载文件被同意 >>********************	
	  *[消息体]			 
	  *   + TDownLoadPara	文件名称列表
	  *[消息方向]
	  *    UE => MTC
	  */_event(  ev_FTDownLoadACK )
	  _body ( TDownLoadPara    ,1         )
	  _ev_end
	  
	  /***********************<< MTC下载文件完毕 >>********************	
	  *[消息体]			 
	  *   
	  *[消息方向]
	  *    MTC => UE
	  */_event(  ev_FTDownLoadFinish  )
      _ev_end
	  //file_trans end.

      //conferenceex begin.
      /**********************<< 会议信息应答 >>**************	
 *[消息体]			 
 *  TMtConfInfo
 *  
 *[消息方向]
 *
 *   MtService <= 323/sip/320
 *   MtService => UI
 */_event(  ev_ConfConfInfoInd   ) 
   _body ( TMtConfInfo, 1 )
   _body ( BOOL, 1 )
   _ev_end


/**********************<< 开始自动多画面合成请求 >>**************	
 *[消息体]			 
 * +TMtVMPParam

 *[消息方向]
 *
 *   MtService <= 323/sip/320
 *   MtService => UI
 */_event(  ev_ConfStartVMPReq   )
   _body( TMtVMPParam, 1 )
   _ev_end


/**********************<< 停止自动多画面合成请求 >>**************	
 *[消息体]			 
 * +TMtVMPParam
 *
 *[消息方向]
 *
 *   MtService <= 323/sip/320
 *   MtService => UI
 */_event(  ev_ConfStopVMPReq   )
   _body( TMtVMPParam, 1 )
   _ev_end


/**********************<< 停止自动多画面合成应答 >>**************	
 *[消息体]	
 *  +BOOL    TRUE=同意
 *  
 *[消息方向]
 *
 *   MtService <= 323/sip/320
 *   MtService => UI
 */_event(  ev_ConfStopVMPRsp   ) 
   _body ( BOOL      , 1          )
   _ev_end


/**********************<< 设置自动多画面合成参数请求 >>**************	
 *[消息体]	
 *  +TMtVMPParam
 *  
 *  
 *[消息方向]
 *
 *   MtService <= 323/sip/320
 *   MtService => UI
 */_event(  ev_ConfSetVMPParamReq   ) 
   _body ( TMtVMPParam   , 1          )
   _ev_end


/**********************<< 获取自动多画面合成应答参数应答 >>**************	
 *[消息体]	
 *  +TMtVMPParam
 *  
 *[消息方向]
 *
 *   MtService <= 323/sip/320
 *   MtService => UI
 */_event(  ev_ConfGetVMPParamRsp   ) 
   _body ( TMtVMPParam   , 1          )
   _ev_end
	  //conferenceex end.

	  //config begin.
	  /***********************<< 引导指示>>************************	
 *[消息体]			 
 *    + TGuideCfg
 *[消息方向]
 *   MtService => UI
 */_event(  ev_CfgGuidInd  )
   _body( TGuideCfg       ,1  ) 
   _ev_end



/***********************<< 引导配置>>************************	
 *[消息体]			 
 *    + TGuideCfg
 *[消息方向]
 *    UI< = MtService
 */_event(  ev_CfgGuidCmd  )
   _body( TGuideCfg       ,1  ) 
   _ev_end

/***********************<< 显示配置指示 >>************************	
 *[消息体]			 
 *    + TDisplay (TOsdCfg)
 *[消息方向]
 *    MtService => UI
 */_event(  ev_CfgDisplayInd  )
   _body( TOsdCfg    ,1  ) 
   _ev_end

/***********************<< 以太网指示 >>************************	
 *[消息体]			 
 *    + u8 以太网索引 (0-eth0   )
 *    + TEthnetInfo
 *[消息方向]
 *    MtService => UI
 */_event(  ev_CfgEthnetInd  )
   _body( u8          ,1  )
   _body( TEthnetInfo ,1  )
   _ev_end


/***********************<< 以太网配置 >>************************	
 *[消息体]			 
 *    + u8 以太网索引 (0-eth0   )
 *    + TEthnetInfo
 *[消息方向]
 *    UI< = MtService
 */_event(  ev_CfgEthnetCmd  )
   _body( u8          ,1  )
   _body( TEthnetInfo ,1  )
   _ev_end


/***********************<< PPPOE配置 >>************************	
 *[消息体]			 
 *    + TPPPOECfg
 *[消息方向]
 *    UI< = MtService
 */_event(  ev_CfgPPPOECmd  )
   _body( TPPPOECfg ,1  )
   _ev_end


/***********************<< 防火墙配置 >>************************	
 *[消息体]			 
 *    + TEmbedFwNatProxy
 *[消息方向]
 *    UI< = MtService
 */_event(  ev_CfgFireWallCmd  )
   _body( TEmbedFwNatProxy ,1  )
   _ev_end

/***********************<< 设置默认网关 >>**********************	
 *[消息体]			 
 *  + u32_ip    默认网关
  *[消息方向]
 *  UI => MtService
 */_event(  ev_CfgDefaultGatewayCmd )
   _body (  u32_ip    ,1            )
   _ev_end
   
   /***********************<< 配置DNS Server >>**********************	
 *[消息体]			 
 *  + u32_ip    DNS Server ip
 *[消息方向]
 *  MtService => UI
 */_event(  ev_CfgDNSServerCmd )
   _body (  u32_ip    ,1            )
   _ev_end

     /***********************<< DNS Server指示 >>**********************	
 *[消息体]			 
 *  + u32_ip    DNS Server ip
 *[消息方向]
 *  MtService => UI
 */_event(  ev_CfgDNSServerInd )
   _body (  u32_ip    ,1            )
   _ev_end
  
//////////////////////////////////////////////////////////////////////////
//[xujinxing-2006-10-17]
/***********************<< 内嵌mc配置 >>************************	
 *[消息体]		 
 *  + TInnerMcCfg //mc配置的结构    
 *[消息方向
 *   ui => mtservice => mcservice
 */_event ( ev_CfgInnerMcCmd )
  _body ( TInnerMcCfg , 1 )
  _ev_end
  
//////////////////////////////////////////////////////////////////////////
//[xujinxing-2006-10-17]
/***********************<< 内嵌mc配置指示 >>************************	
 *[消息体]		 
 *  + TInnerMcCfg //mc配置的结构    
 *[消息方向
 *   ui <= mtservice 
 */_event ( ev_CfgInnerMcInd )
  _body ( TInnerMcCfg , 1 )
  _ev_end
  
  //////////////////////////////////////////////////////////////////////////
//[zhaixiaogang-2009-2-24 15:05:32]
/***********************<< 日志状态指示 >>************************	
*[消息体]		 
*  + u8    
*[消息方向
*   ui => mtservice 
*/_event ( ev_CfgLogStatusCmd )
_body ( u8 , 1 )
_ev_end

//////////////////////////////////////////////////////////////////////////
//[zhaixiaogang-2009-2-24 15:05:32]
/***********************<< 日志状态指示 >>************************
*[消息体]		 
*  + u8    
*[消息方向
*   ui <= mtservice 
*/_event ( ev_CfgLogStatusInd )
_body ( u8 , 1 )
_ev_end

//////////////////////////////////////////////////////////////////////////
//[zhaixiaogang-2009-2-24 15:05:32]
/***********************<< 导出日志指示 >>************************	
*[消息体]		 
*  + u8    
*[消息方向
*   ui => mtservice 
*/_event ( ev_CfgLogExportCmd )
_body ( u8 , 1 )
_ev_end

//////////////////////////////////////////////////////////////////////////
//[zhaixiaogang-2009-2-24 15:05:32]
/***********************<< 导出日志指示 >>************************
*[消息体]		 
*  + u8    
*[消息方向
*   ui <= mtservice 
*/_event ( ev_CfgLogExportInd )
_body ( u8 , 1 )
_ev_end


/***********************<< 内置GK配置命令 >>************************	
 *[消息体]		 
 *  + TInnerGK     
 *[消息方向
 *   ui <= mtservice 
 */_event ( ev_CfgInnerGKCmd )
  _body( TInnerGKCfg, 1 )
  _ev_end

/***********************<< 内置GK配置指示 >>************************	
 *[消息体]		 
 *  + TInnerGK     
 *[消息方向
 *   ui <= mtservice 
 */_event ( ev_CfgInnerGKInd )
  _body( TInnerGKCfg, 1 ) 
  _ev_end 


/***********************<< 向导配置改动需要重启命令 >>************************	
 *[消息体]		 
   
 *[消息方向
 *   ui => mtservice 
 */_event ( ev_GuideNeedRebootCmd )
  _ev_end

/***********************<< 配置网络WAN/LAN选择命令 >>************************	
 *[消息体]		 
 * + u8   最右三位代表 MT/GK/PXY, 1表示选择LAN
 *[消息方向
 *   ui => mtservice 
 */_event ( ev_CfgSetNetSelectMaskCmd )
  _body( u8          ,1 )
  _ev_end

/***********************<< 配置网络WAN/LAN选择指示 >>************************	
 *[消息体]		 
 * + u8   最右三位代表 MT/GK/PXY, 1表示选择LAN
 *[消息方向
 *   mtservice => ui
 */_event ( ev_CfgSetNetSelectMaskInd )
  _body( u8          ,1 )
  _ev_end
   
/***********************<<  配置ldap服务器地址查询 >>********************	
 *[消息体]
 * +s8 , MT_MAX_LDAPSERVER_NAME_LEN  //对端的域名
 *  
 *[消息方向]
 *   mtservice  => mtservice 
 */_event(   ev_LdapServerIPCfgCmd )
   _body( s8 , MT_MAX_LDAPSERVER_NAME_LEN )
   _ev_end

/***********************<<  配置ldap服务器地址查询指示 >>********************	
 *[消息体]
 * +s8 , MT_MAX_LDAPSERVER_NAME_LEN  //对端的域名
 *  
 *[消息方向]
 *   mtservice  => mtservice 
 */_event(   ev_LdapServerIPCfgInd )
   _body( s8 , MT_MAX_LDAPSERVER_NAME_LEN )
   _ev_end
	  //config end.

      //codec begin.
      /***********************<< 设置双流显示模式 >>**********************	
 *[消息体]			 
 *  +EmDualVideoShowMode
 *[消息方向]
 * UI         ->MtService
 */_event( ev_CodecDualShowModeCmd )
   _body ( EmDualVideoShowMode    , 1    )
   _ev_end


/***********************<< 设置显示比例模式 >>**********************	
 *[消息体]			 
 *  +EmDisplayRatio
 *[消息方向]
 * UI         ->MtService
 */_event( ev_CodecDisplayRatioCmd )
   _body ( u8				, 1		)
   _body ( EmDisplayRatio    , 1    )
   _ev_end

/***********************<< 台标融入码流 >>************************	
 *[消息体]		 
 * +BOOL
 * +TSymboPoint
 * +s8[MT_MAX_NAME_LEN] 
 *[消息方向]
 *    MtMP => MtService 
 */ _event ( ev_CodecSetLogoCmd )
   _body  ( BOOL, 1  )
   _body  ( TSymboPoint ,1 )
   _body  ( s8   ,MT_MAX_NAME_LEN )
   _ev_end

/***********************<< 设置自动画中画  >>************************
 *[消息体] 
 *  +BOOL             TRUE/ FALSE
 *[消息方向]
 *
 *    MtService => mtmp
 */_event(  ev_CodecAutoPIPCmd   )
   _body ( BOOL            , 1 )//TRUE=自动画中画,FALSE =否
   _ev_end

   _event(  ev_tppreg_timer )
  _ev_end
  
  _event(  ev_tppStartreg_cmd )
  _ev_end

  _event(  ev_tppStopreg_cmd )
  _ev_end
  
  _event(  ev_tppreg_connect_time_out_timer )
  _ev_end
	  //codec end.

      //dhcp begin.
	  /***********************<< DHCP 分配失败  >>************************
 *[消息体]			 
 *  + BOOL  TRUE = 注册成功 FALSE失败
 *
 *[消息方向]
 *
 *    MtService => UI
 *
 */_event(  ev_DHCPIpDown   )
  _body(u8,1 )/*取得/失去IP地址的网口号*/
  _body(u32_ip,1 )/*取得/失去的IP地址，网络字节序*/
  _body(u32_ip,1 )/*取得/失去的IP地址子网掩码，网络字节序*/
  _body(u32_ip,1 )/*取得/失去的默认网关，网络字节序，有可能为0，因为有的DHCP-Server不一定为设备指定默认网关*/
   _ev_end
   
  /***********************<< 配置DHCP  >>************************
 *[消息体]			 
 * BOOL 是否启用DHCP
 *[消息方向]
 *
 *    UI | MTC       => MtService 
 *
 */_event(  ev_CfgDHCPIPCmd   )
	_body(BOOL , 1)
   _ev_end

  /***********************<< 配置DHCP指示  >>************************
 *[消息体]			 
 *  无	
 *[消息方向]
 *
 *    MtService => UI | MTC
 *
 */_event(  ev_CfgDHCPIPInd   )
   _body(BOOL , 1)
   _ev_end
   
  /***********************<< 通知Serveci DHCP IP申请成功  >>************************
 *[消息体]			 
 * u32_ip  DHCP IP 地址
 * u32_ip  DHCP 网关地址
 *[消息方向]
 *
 *    HDCP server        => MtService 
 *
 */_event(  ev_NewDHCPIpInd   )
  _body(u8,1 )/*取得/失去IP地址的网口号*/
  _body(u32_ip,1 )/*取得/失去的IP地址，网络字节序*/
  _body(u32_ip,1 )/*取得/失去的IP地址子网掩码，网络字节序*/
  _body(u32_ip,1 )/*取得/失去的默认网关，网络字节序，有可能为0，因为有的DHCP-Server不一定为设备指定默认网关*/
  _ev_end     
   
 /***********************<< 通知Service DHCP IP申请失败  >>************************
 *[消息体]			 
 * u32_ip  DHCP IP 地址
 * u32_ip  DHCP 网关地址
 *[消息方向]
 *
 *    HDCP server        => MtService 
 *
 */_event(  ev_RenewDHCPIpFailInd   )
  _body(u8,1 )/*失去IP地址的网口号*/
  _body(u32_ip,1 )/*失去的IP地址，网络字节序*/
  _body(u32_ip,1 )/*失去的IP地址子网掩码，网络字节序*/
  _body(u32_ip,1 )/*失去的默认网关，网络字节序，有可能为0，因为有的DHCP-Server不一定为设备指定默认网关*/
  _ev_end     
	  //dhcp end.

	  //extend begin.
	  /***********************<<  按高清分辨率输出指示  >>********************	
 *[消息体]			 
 *     +BOOL  是否启用按高清分辨率输出
 *[消息方向]
 *    MtService => MTC/MTMP
 */_event( ev_CfgHDResOutputInd  )
   _body( u32     , 1 )
   _body( u32     , 1 )//Reversed 1
   _body( u32     , 1 )//Reversed 2  
   _ev_end  

/***********************<<  输出模式帧率设置提示  >>********************	
 *[消息体]			 
 *     TVideoOutputFrm  输出帧率
 *[消息方向]
 *    MtService <= MTC/MTMP
 */_event( ev_CfgHDVideoFrmInd  )
   _body( TVideoDisplayFrm      , 1 )
   _ev_end
	  //extend end.
	  
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
_body(TCnProduceTestMsg ,1)
_ev_end

/***********************<< 生产测试工具登陆响应成功消息 >>********************** 
*[消息体]
*
*[消息方向]
*    应用终端 -> cns 
*/
_event( ev_CNPRODUCETESTLOGIN_ACK )
//_body(TTPEthnetInfo ,1)
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
_body(TCnProduceTestMsg ,1)
_body(BOOL , 5)
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
 
/***********************<< 电视机康冠模式加定时保护  >>************************	
*[消息体]		
*
*[消息方向]
*
*   CNS => CnDevice
*/

_event(  ev_cns_centreTV0ModeTimer  )
_ev_end

_event(  ev_cns_centreTV1ModeTimer  )
_ev_end

_event(  ev_cns_centreTV2ModeTimer  )
   _ev_end

   /***********************<< 生产测试工具IP反馈  >>************************	
   *[消息体]		
   *
   *[消息方向]
   
	 */
	 _event(  ev_CNPRODUCETESTLED_IP  )
	 _body(TTPEthnetInfo ,1)
	 _ev_end
   

#ifndef _MakeTpEventDescription_
   _ev_segment_end( outercnsdevice )
};
#endif
#endif //TPP_EVENT_H
