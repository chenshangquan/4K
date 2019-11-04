#ifndef _h_eventoutcncode_h__
#define _h_eventoutcncode_h__

#include "cnseventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmCNCODEEVENT
{
#endif 
	
	_ev_segment( outercncode  )

/***********************<< 设置音频解码参数 >>**********************	
*[消息体]			 
*  +EmTpCodecComponent  =emAudioDecoder 
*  +EmTpAudioFormat 
*[消息方向]
* cn  = > cnmpctrl
*/_event( ev_tppCodecAudioDecodeParamCmd )
_body ( EmTpCodecComponent    , 1    )
_body ( EmTpAudioFormat       , 1    )
_body ( u16       , 1    )  
_ev_end

/***********************<< 设置音频编码参数 >>**********************	
 *[消息体]			 
 *  +EmTpCodecComponent  =emAudioEncoder
 *  + EmAudioFormat 
 *[消息方向]
 * cn  = > cnmpctrl
 */_event( ev_tppCodecAudioEncodeParamCmd )
   _body ( EmTpCodecComponent    , 1    )
   _body ( EmTpAudioFormat    , 1    )
   _body ( u16       , 1    )
   _ev_end

/***********************<< 设置视频解码参数 >>**********************	
 *[消息体]			 
 *  +EmTpCodecComponent  
 *  + EmTpLostPackageRestore ： 丢包恢复方式
 *  + EmTpVideoFormat    ：解码格式
 *[消息方向]
 * cn  = > cnmpctrl
 */_event( ev_tppCodecVideoDecodeParamCmd )
   _body ( EmTpCodecComponent    , 1    )
   _body ( EmTpLostPackageRestore    , 1    )
   _body ( EmTpVideoFormat    , 1    )
   _body ( u8    , 1    )
   _ev_end

/***********************<< 设置动态载荷 >>**********************	
 *[消息体]			 
 *  +EmTpCodecComponent ：编解码器
 *  +u8	：动态载荷值
 *[消息方向]
 * cn  = > cnmpctrl
 */_event( ev_tppCodecDynamicPayloadCmd )
   _body ( EmTpCodecComponent    , 1    )
   _body ( u8    , 1    )
   _body ( u8    , 1    )
   _ev_end

/***********************<< 设置解码器接收地址 >>**********************	
 *[消息体]			 
 *  + EmTpCodecComponent
 *  + TIPTransAddr      RTP接收地址      
 *  + TIPTransAddr      RTCP接收地址
 *  + TIPTransAddr      RTCP发送目的地址
 *  + u32               接收函数回调指针(H320)
 *[消息方向]
 *   cn  = > cnmpctrl
 */_event( ev_tppCodecRecvAddrCmd )
   _body ( TTpCodecComponent, 1    )
   _body ( TTPTransAddr    , 1    )
   _body ( TTPTransAddr    , 1    )
   _body ( TTPTransAddr    , 1    )
   _body ( u32             , 1    )
   _body ( u16             , 1    )
   _ev_end

   /***********************<< 设置解码器发送地址 >>**********************	
 *[消息体]			 
 *  + EmTpCodecComponent
 *  + TIPTransAddr      RTP发送目的地址 
 *  + TIPTransAddr      RTCP发送目的地址
 *  + TIPTransAddr      RTCP接收地址
 *  + u32               发送函数回调指针(H320)
 *[消息方向]
 *   cn  = > cnmpctrl
 */_event( ev_tppCodecSendAddrCmd )
   _body ( EmTpCodecComponent, 1    )
   _body ( TTPTransAddr    , 1    )
   _body ( TTPTransAddr    , 1    )
   _body ( TTPTransAddr    , 1    )
   _body ( u32             , 1    )
   _body ( u16             , 1    )
   _ev_end

      /***********************<< 设置编码器本地地址 >>**********************	
 *[消息体]			 
 *  + EmTpCodecComponent
 *  + TIPTransAddr      RTP发送目的地址 
 *  + TIPTransAddr      RTCP发送目的地址
 *  + TIPTransAddr      RTCP接收地址
 *  + u32               发送函数回调指针(H320)
 *[消息方向]
 *   cn  = > cnmpctrl
 */_event( ev_tppCodecLocalAddrCmd )
   _body ( TTpCodecComponent, 1    )
   _body ( TTPCnMediaTransPort    , 1    )
   _body ( BOOL    , 1    )
   _ev_end

 /********************<< 音视频编解码密钥  >>*****************************
 *[消息体]	
 *    + EmTpCodecComponent
 *    + TEncryptKey
 *[消息方向]
 *  cn  = > cnmpctrl
*/_event ( ev_tppCodecEncryptKeyCmd )
  _body ( EmTpCodecComponent , 1 )
  _body ( TTpEncryptKey, 1 )
  _body ( u8             , 1    )
  _ev_end

  /***********************<< 设置视频编码参数 >>**********************	
 *[消息体]			 
 *  + EmTpCodecComponent  =emPriomVideoEncoder/emSecondVideoEncoder
 *  + TVideoEncodeParameter 
 *	+ BOOL				使第二路的参数不要直接设置到底层
 *[消息方向]
 * cn  = > cnmpctrl
 */_event( ev_tppCodecVideoEncodeParamCmd )
   _body ( EmTpCodecComponent    , 1    )
   _body ( TTPMtVideoEncodeParameter    , 1    )
   _body ( u8, 1 )
   _ev_end

     /***********************<< 设置视频编码参数 >>**********************	
 *[消息体]			 
 *  + TTPVideoParam  视频参数
 *	+ EmTpVideoFormat  视频协议类型
 *  + EmTpVideoResolution  分辨率类型
 *[消息方向]
 *  cn  = > cnmpctrl
 */_event( ev_tppNotifyVideoEncodeParamCmd )
   _body ( TTPVideoParam    , 1    )
   _body ( EmTpVideoFormat    , 1    )
   _body ( EmTpVideoResolution    , 1    )
   _body ( u8, 1 )
   _body ( EmTpCodecComponent, 1 )
   _ev_end

  /***********************<< 会议ep列表 >>********************	
 *[消息体]
s8* 文件全路径名
 *[消息方向]
 *  cn  = > cnmpctrl
*/
_event(  ev_tppMTAutoTest_Cmd )
_body ( EmTPAutoTestType , 1 )
_ev_end

/***********************<< 请求编解码器统计信息 >>************************	
 *[消息体]		 
 *   无 
 *[消息方向]
 *  cn  = > cnmpctrl 
 */
 _event ( ev_tppCodecPackStatCmd )
 _ev_end


 /***********************<< 请求编解码器统计信息 >>************************	
 *[消息体]		 
 *   无 
 *[消息方向]
 *   cn  = > cnmpctrl 
 */
 _event ( ev_tppCodecPackStatInd )
 _body ( TTPCodecPackStat    , 1          )
 _ev_end

 /***********************<< 请求编解码器丢包信息 >>************************	
 *[消息体]		 
 *  +BOOL  TRUE= 开启 ;FALSE=关闭
 *[消息方向]
 *  cn  = > cnmpctrl
 */
 _event ( ev_tppCodecLostPackCmd )
  _body ( BOOL, 1 )
 _ev_end
 
 /***********************<< 编解码器实际的码率分辨率统计信息指示 >>************************	
 *[消息体]		 
 *  +TTPVideoEncDecResPack  //编解码器分辨率

 *[消息方向]
 *    cnmpctrl  = > cn
 */
 _event ( ev_tppCodecVideoEncDecResInd ) 
 _body ( TTPVideoEncDecResPack, 1 )
 _ev_end

/***********************<< 从编码器获取的第一路帧率上报 >>************************	
 *[消息体]		 
 *  +TTPVideoFrameRatePack6  //视频帧率

 *[消息方向]
 *    cnmpctrl  = > cn
 */_event ( ev_tppVidFramerateInd )
  _body ( TTPVideoFrameRatePack, 1 )
  _ev_end

  /***********************<< 音视频丢包率 >>************************	
 *[消息体]
 * u32  丢包数
 * u32  包总数

 *[消息方向]
 *   cnmpctrl  = > cn
 */_event ( ev_tppCodecLostPackInd )
  _body ( u32, 1 )
  _body ( u32, 1 )
  _ev_end

 /***********************<< 编码器有没有视频源输入>>************************	
 *[消息体]		 
 *  +TTPVideoRecv  //编解码器有没有视频源输入
 *[消息方向]
 *  cnmpctrl  = > cn
 */
 _event ( ev_tppCodecVideoRecvInd ) 
 _body ( TTPVideoRecv, 1 )
 _ev_end
 
 /***********************<<  高清音频端口选择命令    >>********************	
 *[消息体]			 
 *     +TTPHdAudioPort  音频端口
 *[消息方向]
 *  cn  = > cnmpctrl
 */
 _event( ev_tppCfgHDAudioInPortCmd  ) 
 _body ( TTPHdAudioPort   ,1) 
 _ev_end

  /***********************<<  高清音频播放端口选择命令    >>********************	
 *[消息体]			 
 *     +TTPHdAudioOutPort  音频端口
 *[消息方向]
 *  cn  = > cnmpctrl
 */
 _event( ev_tppCfgHDAudioOutPortCmd  ) 
 _body ( TTPHdAudioOutPort   ,1) 
 _ev_end

  /***********************<<  双流高清音频端口选择命令    >>********************	
 *[消息体]			 
 *     +THdAudioPort  音频端口
 *[消息方向]
 *  cn  = > cnmpctrl
 */
 _event( ev_tppCfgHDDualAudioInPortCmd  ) 
 _body ( TTPHdDualAudioPort   ,1)
 _body ( BOOL   ,1)
 _ev_end

 /***********************<< 开启/关闭自动增益控制 >>**********************	
 *[消息体]			 
 *  +BOOL  TRUE= 开启 ;FALSE=关闭   
 *[消息方向]
 * cn  = > cnmpctrl
 */_event( ev_tppAGCCmd )
   _body ( BOOL    , 1    )
   _body ( u8    , 1    )
   _ev_end


   /**********************<< Mic增益控制  >>********************	
 *[消息体]
 * +EmTPHDAudPortIn 音频端口
 * +u8 mic增益值 增益范围1—31
 *[消息方向]
 *   cn  = > cnmpctrl
 */_event( ev_tppMicAdjustCmd )
   _body(EmTPHDAudPortIn, 1)
   _body( u8, 1 )
   _body ( u8    , 1    )
   _ev_end

   /***********************<<  按高清分辨率输出指示  >>********************	
 *[消息体]			 
 * +u32   高清输出模式
 *[消息方向]
 *   cn  = > cnmpctrl
 */_event( ev_tppCfgHDResOutputInd  )
   _body( u32     , 1 )
   _body( u8     , 1 )
   _ev_end

   /***********************<<  输出模式帧率设置提示  >>********************	
 *[消息体]			 
 *     TTPVideoDisplayFrm  输出帧率
 *[消息方向]
 *  cn  = > cnmpctrl
 */_event( ev_tppCfgHDVideoFrmInd  )
   _body( TTPVideoDisplayFrm      , 1 )
   _body( u8     , 1 )
   _ev_end


   /***********************<< 设置双流显示模式 >>**********************	
 *[消息体]			 
 *  +EmDualVideoShowMode  双流显示模式
 *[消息方向]
 *cn  = > cnmpctrl
 */_event( ev_tppCodecDualShowModeCmd )
   _body ( EmTPDualVideoShowMode    , 1    )
   _body( u8     , 1 )
   _ev_end
/***********************<< 设置显示比例模式 >>**********************	
 *[消息体]
 *  +u8   0:主视频， 1:双流
 *  +EmDisplayRatio 显示比例
 *[消息方向]
 * cn  = > cnmpctrl
 */_event( ev_tppCodecDisplayRatioCmd )
   _body ( u8				, 1		)
   _body ( EmTPDisplayRatio    , 1    )
   _body( u8     , 1 )
   _ev_end

   /***********************<< 视频参数调整  >>************************	
 *[消息体]			 
 *    +TImageAdjustParam  图像调整参数
 *[消息方向]
 *   cn  = > cnmpctrl
 */_event(  ev_tppCodecImageAdjustParamCmd  )
   _body( TTPImageAdjustParam ,1           )  
   _body( u8     , 1 )
   _ev_end

/***********************<< 设置丢包时降低码率配置  >>************************
 *[消息体] 
 *  +TBitRateAdjust  丢包时降低码率配置
 *[消息方向]
 *
 *  cn  = > cnmpctrl
 */_event(  ev_tppCodecRateAdjustCmd   )
   _body ( TTPBitRateAdjust      , 1 )//丢包时降低码率配置
   _body( u8     , 1 )
   _ev_end


/**********************<< 将码率降低一个比率  >>********************	
 *[消息体]
 * u8  如果为95，则将码率调整到原来的95%
 * u8  由于ip头的冗余，需要再将编码码率降低一个值
       默认是90%，即降为原来的90%，网络带宽则设为原来的值,编码码率降
 *[消息方向]
 *  cn  = > cnmpctrl
 */_event( ev_tppCodecBitRateDecsRatioCmd )
  _body( u8, 1 )
  _body( u8, 1 )
  _body( u8, 1 )
   _ev_end 

/***********************<< 发送静态图片 >>**********************	
 *[消息体]			 
 *  +BOOL TRUE=开始发送  、FALSE=停止发送
 *[消息方向]
 * cn  = > cnmpctrl
 */_event( ev_tppSendPictureCmd )
   _body ( BOOL    , 1    )
   _body( u8, 1 )
   _ev_end


   /***********************<< 自环测试 >>**********************	
 *[消息体]			 
 *  TTPInterFaceTestInfo  接口测试信息
 *[消息方向]
 * cn  = > cnmpctrl
 */_event( ev_tppLoopbackTestCmd )
   _body ( TTPInterFaceTestInfo    , 1    )
   _ev_end

    /***********************<< 自环测试回应 >>**********************	
 *[消息体]
 *[消息方向]
 * cn  = > cnmpctrl
 */_event( ev_tppLoopbackTestInd )
	_body( u8, 1 )
	_body( EmToolType, 1)
   _ev_end

   //add by niu 2014-04-23
    /***********************<< 生产工具自环测试回应 >>**********************	
 *[消息体]
 *[消息方向]
 * cn  = > cnmpctrl
 */_event( ev_tppAutoLoopbackTestInd )
	_body( BOOL, 1 )
	_body( EmToolType, 1)
   _ev_end

   /***********************<< 生产工具请求编解码器统计信息 >>************************	
 *[消息体]		 
 *   无 
 *[消息方向]
 *  cn  = > cnmpctrl 
 */
	 _event ( ev_tppAutoCodecPackStatCmd )
	 _ev_end

 /***********************<< 生产工具请求编解码器统计信息回应 >>************************	
 *[消息体]		 
 *   无 
 *[消息方向]
 *   cn  = > cnmpctrl 
 */
	_event ( ev_tppAutoCodecPackStatInd )
	_body( BOOL, 1 )
	_body ( TTPAudPower, 1          )
	_ev_end

	  /***********************<< 自环生产测试开启关闭白噪音 >>**********************	
   *[消息体]
   *  +EmTpMediaType      媒体类型
   *  +BOOL             TRUE=播放噪声  、FALSE=停止播放
   *  +TTPHdAudioOutPort              卡农端口
   *[消息方向]
   *cn  = > cnmpctrl
   */_event( ev_tppAutoTestAudNoisePlayCmd )
   _body ( BOOL           , 1    )
   _body( TTPHdAudioOutPort, 1 )
   _ev_end

   //end add by niu

   /***********************<<  设置丢包重传参数    >>********************	
 *[消息体]			 
 *     +TLostPackResend
 *[消息方向]
 *   cn  = > cnmpctrl
 */_event( ev_tppCodecLostPackResendCmd  )
   _body ( TTPLostPackResend   ,1)
   _body( u8, 1 )
   _ev_end

 /***********************<<  接口测试命令   >>********************	
 *[消息体]			 
 * TTPAutoTestMsg    
 *[消息方向]
 *  cn  = > cnmpctrl
 */_event( ev_tppAutoTestCmd  )
   _body ( TTPAutoTestMsg   ,1)
   _ev_end


 /***********************<<  显示音视频编解码信息   >>********************	
 *[消息体]			 
 * +u8             
 * +EmTpCodecType  编解码类型
 *[消息方向]
 *    cnmpctrl  = > cnmpctrl
 */_event( ev_tppShowCodecInfoCmd  ) 
   _body ( EmTpCodecType   ,1)
   _body ( u8   ,1)
   _ev_end

 /***********************<<  设置终端音频的编码格式   >>********************	
 *[消息体]			 
 *     
 *[消息方向]
 *   cn  = > cnmpctrl
 */_event( ev_tppSetAudForPriStrategyCmd  )
   _body ( EmTpAudioFormat   ,1)
   _body ( u8   ,1)
   _ev_end


   
 /***********************<<  设置均衡器(3路主音频)  >>********************	
 *[消息体]			 
 * +TTPEqualizer  均衡器设置  
 *[消息方向]
 *   cn  = > cnmpctrl
 */_event( ev_tppSetAudioEqualizerCmd  )
   _body ( TTPEqualizer   ,1)
   _body ( u8   ,1)
   _ev_end

 /***********************<<  设置音频的低通、高通的滤波  >>********************	
 *[消息体]			 
 *  a.低通滤波器截止频率20Khz
	b.高通滤波器截止频率20hz   
 *[消息方向]
 *   cn  = > cnmpctrl
 */_event( ev_tppSetAudioFilterRateCmd  )
   _body ( u32   ,1)
   _body ( u8   ,1)
   _ev_end

    /***********************<<  设置音频的背景噪声衰减  >>********************	
 *[消息体]			 
 *  +u8 背景噪声衰减范围0-15dB  
 *[消息方向]
 *   cn  = > cnmpctrl 
 */_event( ev_tppSetAudioBNACmd  )
   _body ( u8   ,1)
   _body ( u8   ,1)
   _ev_end
   

       /***********************<<  设置FEC配置信息  >>********************	
 *[消息体]			 
 * +TTPFecInfo  FEC配置信息
 *[消息方向]
 *   cn  = > cnmpctrl 
 */_event( ev_tppSetFecInfoCmd  )
   _body ( TTPFecInfo   ,1)
   _body ( u8   ,1)
   _ev_end

       /***********************<<  画中画设置  >>********************	
 *[消息体]			 
 *   + TTPPIPMod
 *[消息方向]
 *   cn  = > cnmpctrl 
 */_event( ev_tppSetPIPModCmd  )
   _body ( TTPPIPMod   ,1)
   _ev_end
   
   /***********************<<  指示当前的矩阵配置    >>********************	
 *[消息体]			 
 *     +TTPVideoPort 视频端口
 *[消息方向]
 *    cn  = > cnmpctrl 
 */_event( ev_tppMatrixCmd  )
   _body ( TTPVideoPort   ,1)
   _ev_end


   /***********************<< 配置MTU命令 >>************************	
  *[消息体]		 
  * + u32   MTU值
  *[消息方向
  *   cn  = > cnmpctrl 
  */_event ( ev_tppCfgSetMTUCmd )
   _body( s32          ,1 )
   _ev_end

   /***********************<< 配置音质优先命令 >>************************	
 *[消息体]		 
 * + u32   音质优先等级
 *[消息方向
 *   cn  = > cnmpctrl
 */_event ( ev_tppCfgSetAudioPrecedenceCmd )
  _body( u32         ,1 )
  _body( u8, 1 )
  _ev_end 

     /***********************<< 卡农麦克幻象供电开关 >>************************	
 *[消息体]
 * +EmTPHDAudPortIn 音频输入端口  
 * +BOOL  TRUE= 开启 ;FALSE=关闭
 *[消息方向
 *   cn  = > cnmpctrl
 */_event ( ev_tppSimplexPoweringCmd )
  _body( EmTPHDAudPortIn         ,1 )
  _body( BOOL         ,1 )
  _body( u8, 1 )
  _ev_end 


     /***********************<< 检测丢包定时器 >>**********************	
 *[消息体]			 
* 无
 *[消息方向]
 * cn  = > cnmpctrl
 */_event( ev_timer_check_lostpack )
   _ev_end


   /***********************<< 设置LOOP地址 >>**********************	
 *[消息体]			 
 *  + TTpCodecComponent
 *  + TTPCnMediaTransPort  接收地址
 *  + BOOL   TRUE 添加地址，FALSE 删除地址
 *[消息方向]
 *    cn  = > cnmpctrl
 */_event( ev_tppCodecLoopAddrCmd )
   _body ( TTpCodecComponent, 1    )
   _body ( TTPCnMediaTransPort    , 1    )
   _body ( BOOL, 1)
   _ev_end
   
   /***********************<< 检测主解码器统计信息定时器 >>**********************	
 *[消息体]			 
* 无
 *[消息方向]
 *cnmpctrl  = > cnmpctrl
 */_event( ev_timer_tpppriomdecstatis1 )
   _ev_end
   _event( ev_timer_tpppriomdecstatis2 )
   _ev_end
   _event( ev_timer_tpppriomdecstatis3 )
   _ev_end
   _event( ev_timer_tpppriomdecstatis4 )
   _ev_end

    /***********************<< 检测全部解码器是否丢包计时器  >>**********************	
 *[消息体]			 
 * 无
 *[消息方向]
 *cnmpctrl  = > cnmpctrl
 */_event( ev_timer_tppcheckviddec_lostpack1 )
   _ev_end
   _event( ev_timer_tppcheckviddec_lostpack2 )
   _ev_end
   _event( ev_timer_tppcheckviddec_lostpack3 )
   _ev_end
   _event( ev_timer_tppcheckviddec_lostpack4 )
   _ev_end
   
      /**********************<< 卡农麦克配置信息  >>********************	
 *[消息体]
 * +TTPSingleAudioPortCfg  卡农麦克配置信息
 * +EmTPHDAudPortIn  麦克端口
 *[消息方向]
 *    cn  = > cnmpctrl
 */_event( ev_tpSgAudioPortCfgCmd )
   _body( TTPSingleAudioPortCfg, 1 )
   _body ( EmTPHDAudPortIn    , 1    )
   _body ( u8    , 1    )
   _ev_end

  /**********************<< 编码清晰度  >>********************	
 *[消息体]
 * +BOOL  TRUE为提高清晰度，FALSE为关闭清晰度
 *[消息方向]
 *    cn  = > cnmpctrl
 */_event( ev_tppSetEncQualityEnhanceCmd )
   _body ( BOOL    , 1    )
   _body ( u8    , 1    )
   _ev_end

   /**********************<< 图像左右裁边  >>********************	
 *[消息体]
 * +TTPVidSrcCutLines 图像左右裁边
 *[消息方向]
 *    cn  = > cnmpctrl
 */_event( ev_tppSetVidSrcCutLinesCmd )
   _body ( TTPVidSrcCutLines    , 1    )
   _ev_end


 /***********************<< 设置语音激励保持时间，单位秒 >>**********************	
 *[消息体]			 
 *  + u32
 *[消息方向]
 *   cn  = > cnmpctrl
 */_event( ev_tppSetSpeechTimeCmd )
   _body ( u32    , 1    )
   _ev_end
   

   /***********************<< DSP 待机命令 >>************************	
   *[消息体]		 
   * 
   *[消息方向]
   *    cn  = > cnmpctrl
   */ _event ( ev_tppCodecDspSleepCmd )
   _ev_end
   
   /***********************<< DSP 唤醒命令 >>************************	
   *[消息体]		 
   * 
   *[消息方向]
   *    cn  = > cnmpctrl
   */ _event ( ev_tppCodecDspWakeupCmd )
    _ev_end


   /***********************<< MtMP DSP 状态指示 >>************************	
   *[消息体]		 
   *  + BOOL     TRUE =待机 FALSE =运行
   *[消息方向]
   *    cnmpctrl  = > cn
   */ _event ( ev_tppCodecDspSleepStateInd )
   _body(   BOOL   , 1          )
    _ev_end

	/***********************<<  AEC微调命令 >>********************	
	*[消息体]
	+ u32 范围0-60
	*[消息方向]
	*   cn  = > cnmpctrl
	*/_event( ev_tppCfgAECAdjustCmd )
	_body( u32, 1 )
	_body ( u8    , 1    )
   _ev_end

   /***********************<<  AEC微调定时器 >>********************	
	*[消息体]
	+
	*[消息方向]
	*   cnmpctrl  = > cn
	*/_event( ev_tpp_timer_setaecdbg_code1 )
   _ev_end

   _event( ev_tpp_timer_setaecdbg_code2 )
   _ev_end

   _event( ev_tpp_timer_setaecdbg_code3 )
   _ev_end

   _event( ev_tpp_timer_setaecdbg_dualcode )
   _ev_end
   
   /**********************<< 视频信号输入指示  >>********************	
   *[消息体]
   *[消息方向]
   *   cn  = > cnmpctrl
   */_event( ev_tppCodecVideoInputCmd )
   _body( u8, 1 )
   _ev_end

    /**********************<< 视频信号输入指示  >>********************	
   *[消息体]
   * BOOL         //第一路视频是否有信号
   *[消息方向]
   *   cn  = > cnmpctrl
   */_event( ev_tppCodecVideoInputInd )
   _body( BOOL , 1 )
   _body( u8, 1 )
   _ev_end

    /***********************<< 检测视频输入信息是否中断定时器  >>**********************	
 *[消息体]			 
 * 无
 *[消息方向]
 *
 */_event( ev_tpp_timer_checkvideoinput1 )
   _ev_end
   _event( ev_tpp_timer_checkvideoinput2 )
   _ev_end
   _event( ev_tpp_timer_checkvideoinput3 )
   _ev_end
   _event( ev_tpp_timer_checkvideoinput4 )
   _ev_end

   /**********************<< VGA分辨率设置  >>********************	
   *[消息体]
   * TTPVGAInfo         
   *[消息方向]
   *   cn  = > cnmpctrl
   */_event( ev_tppVGAfpsCmd )
   _body( TTPVGAInfo , 1 )
   _ev_end

   /**********************<<  VGA分辨率回应    >>********************	
   *[消息体]
   * u32 VGAPC
   * u32 VGAFS
   * u32 Res
   *[消息方向]
   *   cn  = > cnmpctrl
   */_event( ev_tppVGAfpsInd )
   _body( u32, 1 )
   _body( u32, 1 )
   _body( u32, 1 )  
   _ev_end

   //Add by tanxiaodong 2013-03-15.
   /**********************<<  台标Logo设置请求    >>********************	
   *[消息体]
   *BOOL 是否开启台标
   *u8   0 : CNC消息，1: 维护工具消息
   *[消息方向]
   *   cn  = > cnmpctrl
   */_event( ev_tppSetBannerLogo_Cmd )
   _body( BOOL, 1 )
   //_body( TTPFullLogoParam, 1 )
   _body( u8, 1 )
   _body( TTPAddLogoPos, 2 )
   _ev_end
   //End  to add.

   
   /***********************<< 自环生产测试 >>**********************	
   *[消息体]
   *  +TTPAutoTestLoopInfo      自环信息
   *[消息方向]
   *cn  = > cnmpctrl
   */_event( ev_tppAutoTestLoopbackCmd )
   _body ( TTPAutoTestLoopInfo    , 1    )
   _ev_end

   /**********************<< 扬声器测试命令  >>********************	
   *[消息体]
   * + EmMtLoudspeakerVal 1
   *[消息方向]
   *   cn  = > cnmpctrl
   */_event( ev_tppLoudspeakerTestCmd )
   _body( EmMtLoudspeakerVal, 1 )
   _body( u8, 1 )
   _ev_end

   /**********************<< 扬声器测试指示  >>********************	
   *[消息体]
   * + EmMtLoudspeakerVal 1
   *[消息方向]
   *   cn  <= cnmpservice
   */_event( ev_tppLoudspeakerTestInd )
   _body( EmMtLoudspeakerVal, 1 )
   _ev_end

    /***********************<< 扬声器测试定时器  >>**********************	
 *[消息体]			  
 * 无
 *[消息方向]
 *
 */_event( ev_timer_loudspeaker_test1 )
   _ev_end
   _event( ev_timer_loudspeaker_test2 )
   _ev_end
   _event( ev_timer_loudspeaker_test3 )
   _ev_end

    /***********************<< 自环生产测试(1进2出) >>**********************	
   *[消息体]
   *  +BOOL             TRUE=开始测试  、FALSE=停止测试
   *  +u8               编码器
   *  +u8               第一个解码器
   *  +u8               第二个解码器码器
   *[消息方向]
   *cn  = > cnmpctrl
   */_event( ev_tppAutoTestOneInTowOutCmd )
   _body ( BOOL           , 1    )
   _body( u8, 1 )
   _body( u8, 1 )
   _body( u8, 1 )
   _ev_end

    /***********************<< 设置背景噪声抑制等级（目前只针对卡农麦克风） >>**********************	
   *[消息体]
   *  +EmTPHDAudPortIn    音频端口
   *  +BOOL    TRUE 使用语音增强， FALSE 停止使用语音增强
   *  +u32               背景噪声抑制等级（0-3）
   *[消息方向]
   *cn  = > cnmpctrl
   */_event( ev_tppSetSpeLevelCmd )
   _body ( EmTPHDAudPortIn           , 1    )
   _body ( BOOL           , 1    )
   _body( u32, 1 )
   _body( u8, 1 )
   _ev_end


    /***********************<< 开始/停止 适配 >>**********************	
   *[消息体]
   *   * TTPVAdapterInfo  双流适配参数
   *[消息方向]
   *cn  = > cnmpctrl
   */_event( ev_tppStartAdapterCmd )
   _body ( TTPVAdapterInfo           , 1    )
   _ev_end
	
    /***********************<< 请求适配关键帧 >>**********************	
   *[消息体]
   *[消息方向]
   *cn  = > cnmpctrl
   */_event( ev_tppFastUpdateAdaCmd )
   _ev_end
	
    /***********************<< 自环测试回复 >>**********************	
   *[消息体]
   *  +BOOL             TRUE=开始测试  、FALSE=停止测试
   *[消息方向]
   *cn  = > cnmpctrl
   */_event( ev_tppAutoTestLoopbackInd )
   _body ( TTPSingleLoopInfo           , 1    )
   _ev_end


      /***********************<< 设置解码器发送地址 >>**********************	
 *[消息体]			 
 *  + TTpCodecComponent
 *  + BOOL              TRUE 添加新发送地址， FALSE删除发送地址
 *  + TIPTransAddr      RTP发送目的地址 
 *  + TIPTransAddr      RTCP发送目的地址
 *  + TIPTransAddr      BRTCP发送目的地址
 *[消息方向]
 *   cn  = > cnmpctrl
 */_event( ev_tppSetSendAddrCmd )
   _body ( TTpCodecComponent, 1    )
   _body ( BOOL,               1    )
   _body ( TTPTransAddr    , 1    )
   _body ( TTPTransAddr    , 1    )
   _ev_end
	
   /***********************<< 设置音频播放模式 >>**********************	
   *[消息体]
   *  +TTPAudPlayMode     音频播放模式
   *[消息方向]
   *cn  = > cnmpctrl
   */_event( ev_tppSetAudPlayModeCmd )
   _body ( TTPAudPlayMode           , 1    )
   _body ( BOOL           , 1    )
   _ev_end

   /***********************<< 调节帧率 >>**********************	
   *[消息体]
   *  +TAdjustFrameRate     调节帧率 
   *[消息方向]
   *cn  = > cnmpctrl
   */_event( ev_tppAdjustFrameRate_Cmd )
   _body ( TAdjustFrameRate           , 1    )
   _body ( u8,               1    )
   _ev_end

   /***********************<< 调节分辨率 >>**********************	
   *[消息体]
   *  +TAdjustVidRes     调节分辨率
   *[消息方向]
   *cn  = > cnmpctrl
   */_event( ev_tppAdjustVidRes_Cmd )
   _body ( TAdjustVidRes           , 1    )
   _body ( u8,               1    )
   _ev_end


   /***********************<< 修改解码器接收地址 >>**********************	
 *[消息体]			 
 *  + EmTpCodecComponent
 *  + TIPTransAddr      RTP接收地址      
 *  + TIPTransAddr      RTCP接收地址
 *  + TIPTransAddr      RTCP发送目的地址
 *[消息方向]
 *   cn  = > cnmpctrl
 */_event( ev_tppModifyRecvAddrCmd )
   _body ( TTpCodecComponent, 1    )
   _body ( TTPTransAddr    , 1    )
   _body ( TTPTransAddr    , 1    )
   _body ( TTPTransAddr    , 1    )
   _ev_end


   /***********************<< 设置小画面位置 >>**********************	
   *[消息体]
   *  +TTPSmallPicRectInfo     小画面位置信息
   *  +u8 编解码器
   *[消息方向]
   *cn  = > cnmpctrl
   */_event( ev_tppSetSmallPicRect )
   _body ( TTPSmallPicRectInfo           , 1    )
   _body ( u8   , 1  )
   _ev_end


         /***********************<< 检测双流输入源 >>**********************	
 *[消息体]			 
* 无
 *[消息方向]
 *cnmpctrl  = > cnmpctrl
 */_event( ev_timer_checkdualinput )
   _ev_end


   /***********************<< 设置双流音频输入端口模式 >>**********************	
   *[消息体]
   *  +EmTPAudDualInMode     双流音频输入端口模式
   *  +u8 编解码器
   *[消息方向]
   *cn  = > cnmpctrl
   */_event( ev_tppSetAudDualInModeCmd )
   _body ( EmTPAudDualInMode           , 1    )
   _body ( u8   , 1  )
   _ev_end

   /***********************<< 设置图像偏移  >>**********************	
   *[消息体]
   *  +TTPVidOffsetParam     设置图像偏移
   *[消息方向]
   *cn  = > cnmpctrl
   */_event( ev_tppSetVidOffsetParam  )
   _body ( TTPAllVidOffsetParam           , 1    )
   _ev_end


   /***********************<< 设置音频双流本地播放  >>**********************	
   *[消息体]
   *  BOOL    TRUE:音频双流本地播放; FALSE:非本地播放
   *[消息方向]
   *cn  = > cnmpctrl
   */_event( ev_tppSetAudSubPlay  )
   _body ( BOOL          , 1    )
   _ev_end

	   /***********************<< 中间屏是否开启显示双流策略 >>**********************	
 *[消息体]			 
 *  +BOOL      TRUE=中间屏显示双流  、FALSE=不显示双流
 *[消息方向]
 * cn  = > cnmpctrl
 */_event( ev_tppShowDualCmd )
   _body ( BOOL    , 1    )
   _ev_end

   	   /***********************<< 设置音频检测参数 >>**********************	
 *[消息体]			 
 *  +TTPAudPackCheckInfo
 *[消息方向]
 * cn  = > cnmpctrl
 */_event( ev_tppSetAudPackCheckTimeCmd )
   _body ( TTPAudPackCheckInfo    , 1    )
   _ev_end

   /***********************<< AEC,AGC,ANS设置 >>**********************	
   *[消息体]			 
   *  +EmAudAecType  音频类型
   *  +BOOL  开启关闭
   *[消息方向]
   * cn  = > cnmpctrl
   */_event( ev_tppSetAecParamCmd )
   _body ( EmAudAecType    , 1    )
   _body ( BOOL    , 1    )
   _ev_end

      /***********************<< 设置快照请求 >>**********************	
   *[消息体]			 
   *  +EmTpSnapShotType 快照类型
   *  +u8      当前操作的摄像机索引
   *  +u8      要保存的预置位号
   *[消息方向]
   * cn  = > cnmpctrl
   */_event( ev_tppSetSnapShotCmd )
   _body ( EmTpSnapShotType    , 1)
   _body ( u8				   , 1)
   _body ( u8				   , 1)
   _ev_end

     /***********************<< 快照 >>**********************	
   *[消息体]
   *  +u8 BOOL TRUE快照成功，FALSE快照失败
   *  +EmTpSnapShotType 快照类型
   *[消息方向]
   * cnmp  = > cn
   */_event( ev_tppSetSnapShotInd )
   _body ( EmTpSnapShotType    , 1)
   _body ( BOOL                , 1)
   _body ( u8				   , 1)
   _body ( u8				   , 1)
   _ev_end

    /***********************<< 画面合成 >>**********************	
   *[消息体]
   *  +u8 BOOL TRUE开始画面合成，FALSE取消画面合成
   *[消息方向]
   * cnmp  = > cn
   */_event( ev_tppSetPipMergeCmd )
   _body ( BOOL    , 1    )
   _ev_end
   
    /***********************<< 编码前处理策略（加黑边，裁边等） >>**********************	
   *[消息体]
   *  +EmVidEncResizeMode 图像比例调整策略
   *  +u8 编解码器
   *[消息方向]
   * cnmp  = > cn
   */_event( ev_tppSetVidEncResizeModeCmd )
   _body ( EmVidEncResizeMode    , 1    )
   _body ( u8   , 1  )
   _ev_end

    /**********************<<  台标设置请求    >>********************	
   *[消息体]
   *TTPLogoParam 台标信息
   *[消息方向]
   *   cn  = > cnmpctrl
   */_event( ev_tppSetLogo_Cmd )
   _body( TTPLogoParam, 1 )
   _ev_end

    /**********************<<  横幅设置请求    >>********************	
   *[消息体]
   *TTPBannerParam 横幅信息
   *[消息方向]
   *   cn  = > cnmpctrl
   */_event( ev_tppSetBanner_Cmd )
   _body( TTPBannerParam, 1 )
   _ev_end

      /***********************<< 调整输出音量的命令 >>********************	
 *[消息体]
 * u8 输出音量
 * u8 编解码器位置
 *[消息方向]
 *  cns	  -> cnmp
 */
_event( ev_tppSetSingleAudOutputVolCmd )
   _body ( u8    , 1    )
   _body ( u8, 1 )
   _ev_end

     /***********************<< 发双流时能力做假 >>********************	
 *[消息体]
 * BOOL   TRUE：使用假能力。FALSE：不用假能力
 *[消息方向]
 *  cns	  -> cnmp
 */
  _event( ev_tppSetFakeCapacityCmd )
   _body ( BOOL    , 1    )
   _ev_end

   /***********************<<  通知cnmp双流进混音 >>********************** 
   *[消息体]
   *BOOL TRUE：进混音；FALSE：不进混音
   *[消息方向]
   *cns -> cnmp
   */
   _event( ev_tppNotifyCnmpADualInMix_Nty )
   _body(BOOL, 1)
   _ev_end

   /***********************<<检测主流源接口状态  >>************************
	*[消息体]
	*TTpCodecComponent 编解码器
	*BOOL 主流源接口是否有源
	*[消息方向]
	*  cnmp	   -> cns
	*/
	_event( ev_TppGetMainVidSrc_Nty )
	_body ( TTpCodecComponent, 1    )
	_body( BOOL, 1 )
	_ev_end
	
	 /***********************<< 关闭开机画面  >>************************
	*[消息体]
	*[消息方向]
	*  cns	   -> cnmp
	*/
	_event( ev_tppCloseStartLogo_Cmd )
	_ev_end	

	 /***********************<< 画面合成风格  >>************************
	*[消息体]
	*[消息方向]
	*  cns	   -> cnmp
	*/
	_event( ev_tppSetVideoMergeStyle_Cmd )
	_body( EmVidMergeStyle, 1 )
	_ev_end

	 /***********************<<量子加密秘钥通知>>********************** 
	 *[消息体]	
     *    + EmTpCodecComponent
	 *    + TQtEncryptKey					
	 *[消息方向]
	 *  cn = >  cnmpctrl
	 */
     _event(  ev_tppQtEncryptKey_Cmd )
     _body ( TTpQtEncryptKey, 1 )
     _ev_end

#ifndef _MakeTpEventDescription_
		_ev_segment_end( outercncode )
};
#endif
#endif