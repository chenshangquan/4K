/**
*   COPYRIGHT NOTICE
*   Copyright (C) 2018, KeDaCom
*   All right reserved
*   
*   @file        h323callstdmsg.h
*   @author      Sai
*   @version     V5.0_64bit
*   @date        2018-03-05
*   @brief       Definded Messages for H323 protocal
*   @details     
*/
#ifndef _H323CALLSTDMSG_H
#define _H323CALLSTDMSG_H


/**呼叫消息*/
enum H225CallMsgType 
{
	h_call_invalidInterface = 0,
    h_call_make             = 1,	   /**< 发起呼叫	      [outgoing]: TCALLPARAM */
	h_call_incoming         = 2,	   /**< 呼叫到来		  [incoming]: TCALLPARAM + VendorProductId */
	h_call_answer		    = 3,       /**< 接受(拒绝)呼叫    [outgoing]: TNODEINFO */
	h_call_drop             = 4,       /**< 结束呼叫		  [outgoing]: 1 byte,reason(标准消息一个u8，非标是u8+u8) */
	h_call_connected        = 5,       /**< 呼叫建立		  [incoming]: TNODEINFO */	
	h_call_disconnected     = 6,       /**< 呼叫断开		  [incoming]: 1 byte,reason */	
	h_call_facility         = 7,	   /**< 呼叫扩展处理	  [incoming]&[outgoing]: TFACILITYINFO */   
	h_call_h460make         = 8,	   /**< 发起h460呼叫	  [outgoing]: TH460CALLPARAM */
	h_call_h460CallerMake   = 9,	   /**< 公网终端收到facility发起呼叫 [outgoing]: TCALLPARAM */
    h_call_alerting         = 10,      /**< Useless except for KDV1000 processes */
};

/**RAS消息*/
enum H225RasMsgType 
{
	h_ras_invalidInterface = 0,
	h_ras_GRQ			   = 1,		/**< reserve */
	h_ras_GCF			   = 2,		/**< reserve */
	h_ras_GRJ              = 3,		/**< reserve */
	h_ras_RRQ              = 4,     /**< [incoming]&[outgoing]:[TRRQINFO] */
	h_ras_RCF			   = 5,		/**< [incoming]&[outgoing]:[TRCFINFO] */    
	h_ras_RRJ              = 6,     /**< [incoming]&[outgoing]:[int:reason] */
	h_ras_LWRRQ            = 7,     /**< [incoming]&[outgoing]:[TRRQINFO] */
	h_ras_ARQ			   = 8,		/**< [incoming]&[outgoing]:[HCALL][TARQINFO] */
	h_ras_ACF              = 9,     /**< [incoming]&[outgoing]:[HCALL][TACFINFO] */
	h_ras_ARJ              = 10,    /**< [incoming]&[outgoing]:[HCALL][int:reason] */
	h_ras_DRQ              = 11,    /**< [incoming]&[outgoing]:[HCALL][TDRQINFO] */
	h_ras_DCF			   = 12,	/**< [incoming]&[outgoing]:[HCALL][TDCFINFO] */
	h_ras_DRJ			   = 13,	/**< [incoming]&[outgoing]:[HCALL][int:reason] */
	h_ras_URQ			   = 14,	/**< [incoming]&[outgoing]:[TURQINFO] */
	h_ras_UCF			   = 15,	/**< [incoming]&[outgoing]:[TUCFINFO] */
	h_ras_URJ			   = 16,	/**< [incoming]&[outgoing]:[int:reason] */
	h_ras_IRQ              = 17,    /**< [incoming]&[outgoing]:[HCALL][TIRQINFO] */
	h_ras_IRQTimeOut       = 18,    /**< [incoming]:           [HCALL] */
	h_ras_IRR			   = 19,	/**< [incoming]&[outgoing]:[HCALL][TIRRINFO] */
	h_ras_BRQ			   = 20,	/**< [incoming]&[outgoing]:[HCALL][TBRQINFO] */ 
	h_ras_BCF              = 21,    /**< [incoming]&[outgoing]:[HCALL][TBCFINFO] */
	h_ras_BRJ			   = 22,	/**< [incoming]&[outgoing]:[HCALL][int:reason] */
	h_ras_LRQ			   = 23,	/**< [incoming]&[outgoing]:[TLRQINFO] */
	h_ras_LCF              = 24,    /**< [incoming]&[outgoing]:[TLCFINFO] */
	h_ras_LRJ              = 25,    /**< [incoming]&[outgoing]:[int:reason] */

	h_ras_registration     = 26,	/**< 自动RAS修改注册信息重新向GK注册	[outgoing]:TRRQINFO */
	h_ras_unregistration   = 27,	/**< 自动RAS向GK注销				    [outgoing]:NULL */
	h_ras_online		   = 28,	/**< 自动RAS在GK注册成功			    [incoming]:NULL */
	h_ras_offline		   = 29,	/**< 自动RAS未在GK注册			        [incoming]:NULL */

	h_ras_NSM              = 30,    /**< 非标消息 */

	h_ras_SCI              = 31,    /**< [incoming]&[outgoing]:[TSCIINFO]
//	h_ras_SCR              = 32,    /**< [incoming]&[outgoing]:[s32] adapter收到SCI消息后会自动回复SCR，业务不需调用此发送了 */

	h_ras_manual_NSM	   = 33,	/**<手动RAS 非标消息*/
};

/**逻辑通道消息*/
enum H245ChanMsgType 
{
	h_chan_invalidInterface				= 0,
   	h_chan_open   						= 1,		/**< [incoming]&[outgoing]: [NULL]&[TCHANPARAM] 打开逻辑通道 */
	h_chan_openAck						= 2,		/**< [incoming]           : [TCHANPARAM]        同意打开逻辑通道 */
	h_chan_openReject					= 3,		/**< [outgoing]           : [emlogChannelRejectCause]     拒绝打开逻辑通道 */
	h_chan_connected					= 4,		/**< [incoming]           : NULL                信道已建立 */
	h_chan_close						= 5,		/**< [outgoing][incoming] : NULL                关闭逻辑通道 */	
	h_chan_parameter					= 6,		/**< [incoming]	       : [TCHANPARAM]        得到逻辑信道媒体参数和数据信道地址 */
	h_chan_remoteRtpAddress				= 7,		/**< [incoming]           : [TNETADDR]          得到对端RTP地址 */ 
	h_chan_remoteRtcpAddress			= 8,		/**< [incoming]           : [TNETADDR]          得到对端RTCP地址 */
	h_chan_dynamicpayloadtype			= 9,		/**< [incoming]           : [u8]                得到通道的动态载荷类型 */    
	h_chan_VideoFreezePicture			= 10,		/**< [incoming]&[outgoing]: [NULL]&[NULL]       图像冻结命令 */
	h_chan_videofastupdatePIC			= 11,		/**< [incoming]&[outgoing]: [NULL]&[NULL]       图像更新命令 */
	h_chan_videofastupdateGOB			= 12,		/**< [incoming]&[outgoing]: [TVFUGOB]&[TVFUGOB] GOB更新命令 */
	h_chan_videofastupdateMB			= 13,		/**< [incoming]&[outgoing]: [TVFUMB]&[TVFUMB]   MB更新命令 */
	h_chan_VideoSendSyncEveryGOB		= 14,		/**< [incoming]&[outgoing]: [NULL]&[NULL]       use sync for every GOB as defined in H.263 */
	h_chan_VideoSendSyncEveryGOBCancel	= 15,		/**< [incoming]&[outgoing]: [NULL]&[NULL]       cancel use sync for every GOB as defined in H.263 */
    h_chan_SwitchReceiveMediaOn         = 16,		/**< [incoming]&[outgoing]: [NULL]&[NULL]       logical channel should be used for receive */
	h_chan_SwitchReceiveMediaOff        = 17,		/**< [incoming]&[outgoing]: [NULL]&[NULL]       logical channel should not be used for receive */
	h_chan_tsto							= 18,		/**< [incoming]&[outgoing]: [TTSTO]             temporal spatial tradeoff operation. */
	h_chan_flowControl					= 19,		/**< [incoming]&[outgoing]: [u16:rate(kbps)]    码流控制命令 */

	h_chan_on							= 20,		/**< [incoming]&[outgoing]: [NULL]&[NULL]       激活逻辑通道，    开始接收数据  */   
	h_chan_off							= 21,		/**< [incoming]&[outgoing]: [NULL]&[NULL]       冻结逻辑通道，    停止接收数据 */

	h_chan_MediaLoopRequest				= 22,		/**< [incoming]: [HCHAN] */
	h_chan_MediaLoopConfirm				= 23,		/**< [incoming]: [HCHAN] */
	h_chan_MediaLoopReject				= 24,		/**< [incoming]: [HCHAN] */
	h_chan_MediaLoopOff					= 25,		/**< [incoming]: [HCALL] */
	h_chan_EncryptSyn                   = 26,		/**< [incoming]: [TEncryptSync] */
	h_chan_EncryptionUpdateRequest      = 27,		/**< [incoming]: [HCHAN] */
	h_chan_EncryptionUpdateCommand      = 28,		/**< [incoming]: [HCHAN][TEncryptSync] */

    h_chan_flowControlIndication   		= 29,		/**< [incoming]&[outgoing]: [u16:rate(kbps)]    码流控制指示 */
	h_chan_keepAliveAddress				= 30,		/**< [incoming]           : [TNETADDR]          得到对端keepAlive地址added by wangxiaoyi for h460 keepalivechannel */
	h_chan_newchan						= 31,	    /**< [incoming]           : [HCHAN]          OnNewChan的消息 */
};

/**从h245CtrlMsgType中提取出来*/
enum H323CapsetCtrlMsgType 
{
	h_ctrl_invlaidInterface				= 0,
	h_ctrl_h245TransportConnected		= 1,         /**< [incoming]	       :[NULL]	       h245通道刚刚建立, 此时可以开始能力交换和主从确定 */
	h_ctrl_h245Established				= 2,		 /**< [incoming]		   :[NULL]		   能力交换和主从确定完成,可以开始打开逻辑通道，收到CancelMultipointConference 也会发此消息 */ 
	h_ctrl_masterSlave					= 3,		 /**< [incoming]		   :[u8:result]	   主从决定ack, [incoming]--result表示本端主从 */ 
	h_ctrl_masterSlaveDetermine         = 4,		 /**< [outgoing]&[incoming]:[s32[2]]       主从决定request, 4byte(terminal Type， 50－240) + (optional)4 bytes(random number 0-0xffffff), */ 
	h_ctrl_capNotifyExt					= 5,         /**< [incoming]&[outgoing]:[TCapSet]&[TCapSet]  对端能力指示 */
	h_ctrl_capResponse				  	= 6,		 /**< [incoming]&[outgoing]:[u8: result]         能力集响应 */
};

#endif //_H323CALLSTDMSG_H
