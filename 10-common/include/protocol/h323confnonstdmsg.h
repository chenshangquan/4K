/**
*   COPYRIGHT NOTICE
*   Copyright (C) 2018, KeDaCom
*   All right reserved
*   
*   @file        h323confnonstdmsg.h
*   @author      Sai
*   @version     V5.0_64bit
*   @date        2018-03-05
*   @brief       Nonstandard message for H323 protocol 
*   @details     
*/
#ifndef _H323CONFNONSTDMSG_H
#define _H323CONFNONSTDMSG_H

/**企业非标消息号定义*/
namespace qiye_confnonstd_msg
{
	enum emQiyeConfNsmType
	{
		KDVP_NSM_START_ID                 = 0,
		KDVP_NSM_GETMTLIST_REQ            = (KDVP_NSM_START_ID + 1), /**<MT 向GK请求在线终端列表*/
		KDVP_NSM_GETMTLIST_RSP            = (KDVP_NSM_START_ID + 2), /**<回复*/
		KDVP_NSM_GETTSCATEGORY_REQ        = (KDVP_NSM_START_ID + 3), /**<MT 向TS查询类型（企业还是运营）*/
		KDVP_NSM_GETTSCATEGORY_RSP        = (KDVP_NSM_START_ID + 4), /**<回复*/
		KDVP_NSM_DELETE_CALL              = (KDVP_NSM_START_ID + 5), /**<删除呼叫对残留*/
		KDVP_NSM_CREATECONF_REQ           = (KDVP_NSM_START_ID + 6), /**<MT->GK创建会议请求*/
		KDVP_NSM_CONFE164_NTF             = (KDVP_NSM_START_ID + 7), /**<MT->GK创建会议回复会议E164号*/
		KDVP_NSM_CREATECONF_RSP           = (KDVP_NSM_START_ID + 8), /**<GK->MT创建会议回复*/
		KDVP_NSM_GETCONFLIST_REQ          = (KDVP_NSM_START_ID + 9), /**<MT->获取会议列表*/
		KDVP_NSM_GETCONFLIST_RSP	      = (KDVP_NSM_START_ID + 10),/**<GK->MT回复会议列表*/
		KDVP_NSM_JOINCONF_REQ		      = (KDVP_NSM_START_ID + 11), /**<MT->GK参加会议请求*/
		KDVP_NSM_JOINCONF_RSP		      = (KDVP_NSM_START_ID + 12), /**<GK->MT回复参加会议请求*/
		KDVP_NSM_CONFNUM_REQ              = (KDVP_NSM_START_ID + 13), /**<MT->GK获取最大会议和空闲会议数 */
		KDVP_NSM_CONFNUM_RSP              = (KDVP_NSM_START_ID + 14), /**<GK->MT回复最大会议和空闲会议数*/
		KDVP_NSM_GETBOOKLIST_REQ          = (KDVP_NSM_START_ID + 15), /**<MT->GK获取预约会议列表*/
		KDVP_NSM_GETBOOKLIST_RSP          = (KDVP_NSM_START_ID + 16), /**<GK->MT返回预约会议列表*/
		KDVP_NSM_CONFDETAIL_REQ           = (KDVP_NSM_START_ID + 17), /**<MT_GK获取会议详细信息(内容填写会议别名)*/
		KDVP_NSM_CONFDETAIL_RSP           = (KDVP_NSM_START_ID + 18), /**<GK_MT回复会议详细信息*/
		KDVP_NSM_GETNEWCONFLIST_REQ       = (KDVP_NSM_START_ID + 19), /**<MT->GK获取临时会议列表*/
		KDVP_NSM_GETNEWCONFLIST_RSP       = (KDVP_NSM_START_ID + 20),  /**<GK->MT获取临时会议列表*/
		KDVP_NSM_TEMPLATECONFLIST_REQ     = (KDVP_NSM_START_ID + 21), /**<会议模板列表请求*/
		KDVP_NSM_TEMPLATECONFLIST_RSP     = (KDVP_NSM_START_ID + 22),/**<会议模板列表返回*/
		KDVP_NSM_NEWJOINCONF_REQ          = (KDVP_NSM_START_ID + 23),/**<入会请求*/
		KDVP_NSM_NEWCREATECONF_REQ        = (KDVP_NSM_START_ID + 24),/**<创会请求*/
		h_ctrl_videoFrameRateChangeCmd = 222,         /**<******************<<  (第一路)视频编码帧率调整 >>*******************/
                                             /**< Mc-->ter			 */
                                             /**<[消息体]			 */
                                             /**<				     */
                                             /**<    +   u8  编码帧率*/
                                             /**<*/
		h_ctrl_chimeInFailInd = 223,					/**<*******************<<  MT申请插话失败 >>*******************/
																					/**< Mc-->ter*/
																					/**<[消息体] 无*/
																					/**<*/
																					/**<*/
		h_ctrl_ModifyConfNameReq = 224,				/**<*******************<<  MT命令修改会议名称 >>*******************/
																						/**< ter-->Mcu*/
																						/**< [消息体] s8[64+1]  会议名称*/
																						/**<*/
																						/**<*/
		h_ctrl_ModifyConfNameRsp = 225,				/**<*******************<<  MT命令修改会议名称 >>********************/
																					/**< Mcu-->ter*/
																					/**< [消息体] u8  成功/失败*/
																					/**<*/
																					/**<*/
		h_ctrl_ModifyConfDurationCmd = 226,			/**<*******************<<  MT命令修改会议时长 >>********************/
																						/**< ter-->Mcu*/
																						/**< [消息体] u16	时长，单位是分钟*/
																						/**<*/
																						/**<*/
		h_ctrl_ModifyConfPwdCmd = 227,				/**<*******************<<  MT命令修改会议入会密码 >>********************/
																					/**< ter-->Mcu*/
																					/**< [消息体] u8	是否加密 */
																					/**<          + s8[16+1] 入会密码*/
																					/**<*/
																					/**<*/
    h_ctrl_requestTerminalInfo = 228,				/**<*******************<<  MT(主席)请求获得终端信息 >>********/
                                            /**<ter-->Mcu*/
                                            /**< [消息体] TTERLABEL 终端ID  —— byMcuNo = 0, byTerNo = 0，则为发送全部终端信息，否则为查询单个终端信息*/
                                            /**<*/	
    
    h_ctrl_requestTerminalInfoResponce = 229,	    /**<*******************<<  MT(主席)请求获得终端信息的平台响应 >>********/
                                            /**< Mcu-->ter*/
                                            /**< [消息体] u8(msg flag: 0 - get all, 1- get one)TTerminalInfo  终端信息*/
                                            /**<*/
                                            

		h_ctrl_ModifyConfInfoReq = 230,               /**<*******************<<  MT(主席)命令修改已召开会议信息 >>************/
																									/**< ter-->Mcu*/
																									/**< [消息体] u8 标示修改项(EModifyConfInfoType)*/
																									/**<          + 修改内容长度(u32)*/
																									/**<          + 修改内容的buf*/
																									/**<*/
		h_ctrl_ModifyConfInfoRsp = 231,               /**<*******************<<  MT(主席)命令修改已召开会议信息回复 >>********/
																									/**< Mcu-->ter*/
																									/**<[消息体] u8 修改项(EModifyConfInfoType)*/
																									/**<          + u8  成功/失败(CtrlResult--h323adapter.h)*/
																									/**<*/
    h_ctrl_requestTerminalInfoEx = 232,			/**<*******************<<  MT(主席)请求获得终端信息-新 >>********/
                                            /**< ter-->Mcu*/
                                            /**< [消息体] +u32(时间戳)*/
                                            /**<          +TTERLABEL 终端ID  —— byMcuNo = 0, byTerNo = 0，则为发送全部终端信息，否则为查询单个终端信息*/
                                            /**<*/	
                                            
    h_ctrl_requestTerminalInfoResponceEx = 233,	/**<******************<<  MT(主席)请求获得终端信息的平台响应-新 >>********/
                                            /**<Mcu-->ter*/
                                            /**<[消息体] +u32(时间戳)*/
                                            /**<         +u8(msg end flag: 0 - not end, 1-end)*/
                                            /**<         +u8(msg flag: 0 - get all, 1- get one)*/
                                            /**<         +[u32(mtinfo buf size, 网络序) + [mt info buf]](终端信息列表)*/
                                            /**<*/
    h_ctrl_getDialogAuthReq = 234,                /**<*******************<<  MT请求 >>********/
                                            /**< ter-->Mcu*/
                                            /**< [消息体] 无*/
                                            /**<*/
    h_ctrl_getDialogAuthRsp = 235,                /********************<<  MCU回应 >>********/
                                            /**< Mcu-->ter*/
                                            /**< [消息体] u8( 0 - 失败，1 - 成功 )*/
                                            /**<*/
    h_ctrl_giveupDialogAuthReq = 236,             /**<*******************<<  MT请求 >>********/
                                            /**<ter-->Mcu*/	
                                            /**< [消息体] 无*/	
                                            /**<*/
    h_ctrl_giveupDialogAuthRsp = 237,             /**<*******************<<  MCU回应 >>********/
                                            /**< Mcu-->ter*/
                                            /**< [消息体] u8( 0 - 失败，1 - 成功 )*/
                                            /**<*/
    h_ctrl_applySpeakerFailInd = 238,             /********************<<  MCU回应 >>********/
                                            /**< Mcu-->ter*/	
                                            /**< [消息体] 无*/	
                                            /**<*/
		h_ctrl_confFailNtf = 239,                 /**<****************会议发生错误通知***********/
																						/**<MCU--->ter*/
																						/**<[消息体]错误原因EConfFailureReason*/
																						/**<*/
    h_ctrl_startDialogReq = 240,                  /**<****************申请开始对讲模式***********/
                                            /**<ter-->Mcu, 主席专用*/
                                            /**<[消息体] 无*/
                                            /**<*/
    h_ctrl_startDialogRsp = 241,                  /**<****************申请开始对讲模式回应***********/
                                            /**<*MCU--->ter*/
                                           /**< *[消息体] u8( 0 - 失败，1 - 成功 )*/
                                            /**<*/
    h_ctrl_stopDialogReq = 242,                   /**<****************申请停止对讲模式***********/
                                            /**<ter-->Mcu, 主席专用*/
                                            /**<[消息体] 无*/
                                            /**<*/
    h_ctrl_stopDialogRsp = 243,                  /**<****************申请停止对讲模式回应***********/
                                            /**<MCU--->ter*/
                                            /**<[消息体] u8( 0 - 失败，1 - 成功 )*/
                                            /**<*/
		h_ctrl_specDialogMtReq = 244,           /*****************主席指定对讲终端***********/
                                            /**<ter-->Mcu, 主席专用*/
                                            /**<[消息体] TTERLABEL*/
                                            /**<*/
    h_ctrl_specDialogMtRsp = 245,           /**<****************主席指定对讲终端回应***********/
                                            /**<MCU--->ter*/
                                            /**<[消息体] u8( 0 - 失败，1 - 成功 )*/
                                            /**<*/
		h_ctrl_confDialogStateNtf = 246,        /**<****************会议对讲模式状态通知***********/
                                            /**<MCU--->ter*/	
                                            /**<[消息体] u8( 会议对讲模式状态：0 - 非对讲模式，1 - 对讲模式 ) + [s8*N](进入对讲模式的触发者别名，会议对讲模式状态=1时有效)*/
                                            /**<*/
		h_ctrl_youInDialogPosNtf = 247,			/*****************终端对话位置通知***********/
                                            /**<MCU--->ter*/	
                                            /**<[消息体] u8( 0 - 不在对讲位置，1 - 在对讲位置 )*/	
                                            /**<*/
		h_ctrl_youInPresidePosNtf = 248,		/**<****************终端主讲位置通知***********/
                                            /**<MCU--->ter*/
                                            /**<[消息体] u8( 0 - 不在主讲位置，1 - 在主讲位置 )*/
                                            /**<*/

		h_ctrl_termSwitchModeNtf = 249,			/**<****************终端切换模式通知***********/	
                                            /**<ter--->MCU*/	
                                            /**<[消息体] u8 切换模式类型( ETermSwitchMode )*/	
                                            /**<*/	
	};
}

/**非标消息号定义*/
typedef enum
{
	KDVP_NSM_START_ID						= 0,
	KDVP_NSM_GETMTLIST_REQ					= 1,			/**<MT 向GK请求在线终端列表*/
	KDVP_NSM_GETMTLIST_RSP					= 2,			/**<会商平台回复KDVP_NSM_GETMTLIST_REQ*/

	KDVP_NSM_NEW_BEGIN						= (KDVP_NSM_START_ID + 10),
	KDVP_NSM_PALTFORMCAP_NOTIFY				= (KDVP_NSM_START_ID + 11),		/**<GK告知h323实体平台能力*/
	KDVP_NSM_GETMTLIST_RSP2					= (KDVP_NSM_START_ID + 12),		/**<会议平台回复KDVP_NSM_GETMTLIST_REQ*/
	KDVP_NSM_GETMTLIST_REJECT				= (KDVP_NSM_START_ID + 13),		/**<4.2GK回复KDVP_NSM_GETMTLIST_REQ*/
	
	/**MT向GK申请地址簿消息*/
	KDVP_NSM_ADDRBOOK_ENTRY_REQ				= (KDVP_NSM_START_ID + 14),
	KDVP_NSM_ADDRBOOK_ENTRY_REJECT			= (KDVP_NSM_START_ID + 15),
	KDVP_NSM_ADDRBOOK_ENTRY_RSP				= (KDVP_NSM_START_ID + 16),
	
	KDVP_NSM_ADDRBOOK_GROUP_REQ				= (KDVP_NSM_START_ID + 17),
	KDVP_NSM_ADDRBOOK_GROUP_REJECT			= (KDVP_NSM_START_ID + 18),
	KDVP_NSM_ADDRBOOK_GROUP_RSP				= (KDVP_NSM_START_ID + 19),
	
	KDVP_NSM_ADDRBOOK_GROUPLEVEL_REQ		= (KDVP_NSM_START_ID + 20),
	KDVP_NSM_ADDRBOOK_GROUPLEVEL_REJECT		= (KDVP_NSM_START_ID + 21),
	KDVP_NSM_ADDRBOOK_GROUPLEVEL_RSP		= (KDVP_NSM_START_ID + 22),
	
	/**终端注册 MT<-- >MTCarrier*/
	KDVP_NSM__REG_REQ						= (KDVP_NSM_START_ID + 23),										
	KDVP_NSM_REG_ACK						= (KDVP_NSM_START_ID + 24),
	KDVP_NSM_REG_NACK						= (KDVP_NSM_START_ID + 25),
	KDVP_NSM__ROUNDTRIP_TIMER				= (KDVP_NSM_START_ID + 26),
	
	/**0.1 开启录像 MT<-->GK*/
	KDVP_NSM_STARTP2PREC_REQ				= (KDVP_NSM_START_ID + 27),
	KDVP_NSM_STARTP2PREC_REJECT				= (KDVP_NSM_START_ID + 28),
	KDVP_NSM_STARTP2PREC_RSP				= (KDVP_NSM_START_ID + 29),
	
	/**0.2 终止录像 双向的*/
	KDVP_NSM_STOPP2PREC_CMD					= (KDVP_NSM_START_ID + 30),
	KDVP_NSM_P2PRECSTATUS_NTY				= (KDVP_NSM_START_ID + 31),
	KDVP_NSM_P2PFASTUPDATE_CMD				= (KDVP_NSM_START_ID + 32),
	KDVP_NSM_P2P_COMMON_MSG					= (KDVP_NSM_START_ID + 33),

	KDVP_NSM_GETTSCATEGORY_REQ				= 100,		/**<MT 向TS查询类型（企业还是运营）*/
	KDVP_NSM_GETTSCATEGORY_RSP				= 101,		/**<回复*/
	KDVP_NSM_DELETE_CALL					= 102,		/**<删除呼叫对残留*/
	KDVP_NSM_CREATECONF_REQ					= 103,		/**<MT->GK创建会议请求*/
	KDVP_NSM_CONFE164_NTF					= 104,   	/**<MT->GK创建会议回复会议E164号*/
	KDVP_NSM_CREATECONF_RSP					= 105,  	/**<GK->MT创建会议回复*/
	KDVP_NSM_GETCONFLIST_REQ				= 106, 		/**<MT->获取会议列表*/
	KDVP_NSM_GETCONFLIST_RSP				= 107,	 	/**<GK->MT回复会议列表*/
	KDVP_NSM_JOINCONF_REQ					= 108,	 	/**<MT->GK参加会议请求*/
	KDVP_NSM_JOINCONF_RSP					= 109,	 	/**<GK->MT回复参加会议请求*/
	KDVP_NSM_CONFNUM_REQ					= 110,   	/**<MT->GK获取最大会议和空闲会议数 */
	KDVP_NSM_CONFNUM_RSP					= 111,   	/**<GK->MT回复最大会议和空闲会议数*/
	KDVP_NSM_GETBOOKLIST_REQ				= 112,		/**<MT->GK获取预约会议列表*/
	KDVP_NSM_GETBOOKLIST_RSP				= 113, 		/**<GK->MT返回预约会议列表*/
	KDVP_NSM_CONFDETAIL_REQ					= 114,		/**<MT_GK获取会议详细信息(内容填写会议别名)*/
	KDVP_NSM_CONFDETAIL_RSP					= 115,    	/**<GK_MT回复会议详细信息*/
	KDVP_NSM_GETNEWCONFLIST_REQ				= 116, 		/**<MT->GK获取临时会议列表*/
	KDVP_NSM_GETNEWCONFLIST_RSP				= 117,	  
	KDVP_NSM_TEMPLATECONFLIST_REQ			= 118,		/**<MT_GK获取会议模板列表*/
	KDVP_NSM_TEMPLATECONFLIST_RSP			= 119,
	KDVP_NSM_NEWJOINCONF_REQ				= 120,    
	KDVP_NSM_NEWCREATECONF_REQ				= 121,  	

	KDVP_NSM_END_ID							= 200,
}emKDVPNsmType;

/**NonStandard Message for H245*/
enum H245CtrlNonStandardMsgType 
{
	h_ctrl_nonstandardinvalid			= 101,
	h_ctrl_chairTransferReq				= 102,		/**<主席终端转移令牌请求	chair->MC, TTERLABEL*/
	h_ctrl_chairInviteTerminalReq		= 103,		/**<主席邀请终端请求		chair->MC, TTERADDR(vccommon.h)*/
	h_ctrl_terStatusReq					= 104,		/**<终端状态请求			MC->ter,   NULL*/
	h_ctrl_pollParamReq					= 105,		/**<查询轮询参数			MC->ter,   NULL	*/
	h_ctrl_whoViewThisTerReq			= 106,		/**<询问MCU A终端被谁选看	ter->MC,   TTERLABEL(A)*/
	h_ctrl_confInfoReq					= 107,		/**<询问会议信息			ter->MC,   NULL*/
	h_ctrl_delayConfTimeReq				= 108,		/**<延长会议时间			chair->MC, u16, minutes*/
	h_ctrl_letTerViewMeReq				= 109,		/**<强制选看请求			ter->MC,   TTERLABEL(被强制选看者) + 1BYTE(DataType) */
	h_ctrl_multicastTerReq				= 110,		/**<组播终端请求			ter->MC,   TTERLABEL(目的终端)	*/
	h_ctrl_destterStatusReq             = 111,		/**<源终端请求目的终端状态     ter->MC,TTERLABEL(目的终端)*/

	h_ctrl_whoViewThisTerRsp			= 112,		/**<对应whoViewThisTerReq	MC->ter, TTERLABEL(被选看终端) + 1Byte(选看终端个数) + TTERLABEL数组*/
	h_ctrl_pollParamRsp					= 113,		/**<轮询参数应答			ter->MC,  */
													/**<类型(1Byte,PollType) + 模式(1Byte,DataType) + 当前状态(1Byte, PollStatus)*/
													/**<+ 当前轮询到的终端(TTERLABEL，+ 时间间隔(u16,s). 如果没有则全填0)*/
													/**<终端个数(1Byte) + 列表(TTERLABEL数组 + 时间间隔(1Byte,s))*/

													/**<类型(1Byte,PollType) + 模式(1Byte,DataType) + 时间间隔(1Byte,s) + 终端个数(1Byte) + 列表(TTERLABEL数组)*/
	h_ctrl_confInfoRsp					= 114,		/**<回答会议信息			MC->ter, 透明转发给MTC*/
	h_ctrl_delayConfTimeRsp				= 115,		/**<延长会议时间应答		1BYTE,granted/denied*/
	h_ctrl_letTerViewMeRsp				= 116,		/**<强制选看应答			MC->ter,   1BYTE(granted/denied)*/
	
	h_ctrl_startVACReq					= 117,		/**<开始语音激励请求 chair->MC, NULL*/
	h_ctrl_stopVACReq					= 118,		/**<停止语音激励请求 chair->MC, NULL*/
	h_ctrl_startVACRsp					= 119,		/**<开始语音激励请求响应 MC->ter, 1BYTE(granted/denied)*/
	h_ctrl_stopVACRsp					= 120,		/**<停止语音激励请求响应 MC->ter,1BYTE(granted/denied)*/

	h_ctrl_startDiscussReq				= 121,		/**<开始讨论 chair->MC, 1byte(同时参加讨论(混音)的成员个数)*/
	h_ctrl_stopDiscussReq				= 122,		/**<停止讨论 chair->MC, NULL*/
	h_ctrl_startDiscussRsp				= 123,		/**<开始讨论请求响应 MC->ter,1BYTE(granted/denied)*/
	h_ctrl_stopDiscussRsp				= 124,		/**<停止讨论请求响应 MC->ter,1BYTE(granted/denied)*/
	
	h_ctrl_startVMPReq					= 125,		/**<开始视频复合 chair->MC, struct TVMPParam(vccommon.h)*/
	h_ctrl_stopVMPReq					= 126,		/**<停止视频复合 chair->MC, NULL*/
	h_ctrl_changeVMPParamReq			= 127,		/**<改变视频复合参数 chair->MC, struct TVMPParam*/
	h_ctrl_getVMPParamReq				= 128,		/**<得到视频复合参数 chair->MC, NULL*/
	h_ctrl_startVMPRsp					= 129,		/**<开始视频复合请求响应 MC->ter,1BYTE(granted/denied)*/
	h_ctrl_stopVMPRsp					= 130,		/**<停止视频复合请求响应 MC->ter,1BYTE(granted/denied)*/
	h_ctrl_changeVMPParamRsp			= 131,		/**<改变视频复合参数请求响应 MC->ter,1BYTE(granted/denied)*/
	h_ctrl_getVMPParamRsp				= 132,		/**<得到视频复合参数请求响应 MC->ter,struct TVMPParam*/
	
	h_ctrl_multicastTerRsp				= 133,		/**<组播终端应答   MC->ter,  TTERLABEL(目的终端) + u32(ip,如果失败ip为0) */
													/**<                       + u16(音频端口号)     + u16(视频端口号)*/
													/**<                       + u8(音频真实载荷值)  + u8(视频真实载荷值)*/
													/**<                       + u8(音频加密类型)    + u8(视频加密类型) -- emEncryptTypeNone等*/
													/**<                       + TEncryptSync(音频加密信息) + TEncryptSync(视频加密信息)*/
	
	h_ctrl_destterStatusRsp             = 134,		/**<请求目的终端状态的响应   MC->ter,TTERLABEL(目的终端) + _TTERSTATUS(vccommon.h)*/

	h_ctrl_makeTerQuietCmd				= 135,		/**<远端静音命令			ter->MC,MC->ter,  TTERLABEL(dst) + 1BYTE(turn_on/turn_off)*/
	h_ctrl_makeTerMuteCmd				= 136,		/**<远端哑音命令			ter->MC,MC->ter,  TTERLABEL(dst) + 1BYTE(turn_on/turn_off)*/
	h_ctrl_startPollCmd					= 137,		/**<开始轮询命令			MC->ter,   */ 
													/**<类型(1Byte,PollType) + 模式(1Byte,DataType) + 终端个数(1Byte) + 列表(TTERLABEL数组 + 时间间隔(1Byte,s))*/
	h_ctrl_stopPollCmd		   			= 138,		/**<停止轮询命令			MC->ter,	NULL*/
	h_ctrl_pausePollCmd					= 139,		/**<暂停轮询				MC->ter,	NULL*/
	h_ctrl_resumePollCmd				= 140,		/**<恢复轮询				MC->ter,	NULL*/
													/**<						action(1Byte,对于普通操作:turn_on(开始)/turn_off(停止);对于预置命令:后面跟1-4表示预置位)*/
	h_ctrl_stopViewMeCmd				= 141,		/**<停止强制选看			ter->MC*/
	h_ctrl_stopMulticastTer				= 142,		/**<停止组播终端			ter->MC,	TTERLABEL*/
	
    h_ctrl_chairSelectViewCmd			= 144,		/**<主席选看				ter->MC,    <m,t> + 1Byte(type_audio/type_video/type_av)*/	

	h_ctrl_chairInviteFailedInd			= 145,		/**<主席邀请终端失败		MC->chair, TTERADDR*/
	h_ctrl_confWillEndInd				= 146,		/**<会议即将结束指示		MC->chair, u16 minutes, 表示还有多久结束*/
	h_ctrl_delayConfTimeInd             = 147,		/**<延长会议时间指示      MC->ter, u16 分钟*/
	h_ctrl_terApplyChairInd				= 148,		/**<有终端申Ind,					//终端状态指示			ter->MC,   _TTERSTATUS ( response h_ctrl_terStatusReq)*/	
	h_ctrl_terStatusInd					= 149,		/**<终端状态指示			ter->MC,   _TTERSTATUS ( response h_ctrl_terStatusReq)	*/
	h_ctrl_pollParamInd                 = 150,		/**<轮询状态指示          类型(1Byte,PollType) + 模式(1Byte,DataType) + 当前状态(1Byte, PollStatus) */
													/**< + 当前轮询到的终端(TTERLABEL，+ 时间间隔(u16,s). 如果没有则全填0)*/
	h_ctrl_smsInd						= 151,		/**<短消息指示			ter->MC,MC->ter,TTERLABEL(src) + TTERLABEL(dst) + (1BYTE:滚动次数)+字符串('\0'结束)*/	
	h_ctrl_broadcasterTokenOwnerInd		= 152,		/**<新广播源通告			MC->ter, TTERLABEL*/
	
    h_ctrl_termSourceNameInd            = 157,		/**<终端视频源名称指示    MC->ter,消息体是字符串，'\0'结束*/
	
    h_ctrl_termVideoSrcCmd				= 162,		/**<选择终端视频源		MC->ter, 1BYTE(视频源索引0:S端子 1~16:C端子)*/

	h_ctrl_chimeInReq					= 163,		/**<终端申请插话				ter->MC,		NULL*/
	h_ctrl_makeTerChimeInCmd			= 164,		/**<主席指定终端插话			ter->MC,		TTERLABEL*/
	h_ctrl_chimeInInd					= 165,		/**<终端插话状态				MC->ter			1字节（0: 不在插话, 1: 在插话）*/
	h_ctrl_otherTerChimeInInd			= 166,		/**<其它终端申请插话指示		MC->chair		TTERLABEL*/

    //add by jason 2005-10-11
    h_ctrl_SimpleConfInfoInd            = 189,		/**<mcu通知终端更新会议信息      MC->ter			1字节（0: 不在插话, 1: 在插话）*/
    
    h_ctrl_terBandWidthInd              = 190,		/**<mt接收发送带宽通知           ter->MC      u16(接收带宽（包括音频和视频）,网络序) + u16(发送带宽（包括音频和视频）,网络序)*/
    h_ctrl_terBitrateInfoReq            = 191,		/**<mcu请求终端码率              MC->ter      消息体：无*/
    h_ctrl_terBitrateInfoRsp            = 192,		/**<mt对终端码率应答             ter->MC      消息体：_TERBITRATE*/
	
    h_ctrl_ViewBroadcastingSrcCmd       = 217,		/**<主席终端强制广播, 消息体: u8 (opr_start-开始，opr_stop－取消)*/
    
    h_ctrl_SatDConfAddrInd              = 218,		/**<******************<< 卫星分散会议接收地址通知 >>**************/
														/**< Mcu-->ter*/
														/**<[消息体](均网络序)*/
														/**<    +   u32   第一路视频地址*/
														/**<    +   u16   第一路视频端口*/
														/**<    +   u32   第一路音频地址*/
														/**<    +   u16   第一路音频端口*/
														/**<    +   u32   第二路视频地址*/
														/**<    +   u16   第二路视频端口*/
														/**<*/

	 h_ctrl_videoFormatChangeCmd			,		/**<********************<< 视频分辨率调整  >>*********************/
														/**< Mcu-->ter*/
														/**<[消息体]*/
														/**<*/
														/**<    +   u8  通道类型   LOGCHL_VIDEO      (默认主视频通道)*/
														/**<    +   u8  分辨率类型 VIDEO_FORMAT_CIF, VIDEO_FORMAT_QCIF, VIDEO_FORMAT_SQCIF_* 等*/
														/**<*/
														
    

    h_ctrl_setAudioVolumeCmd				,		/**<********************<<  终端音量调节   >>*********************/
														/**< Mcu-->ter*/
														/**<[消息体]*/
														/**<*/
														/**<    +   u8  音量类型(NOTE: VOLUME_TYPE_OUT or VOLUME_TYPE_IN)*/
														/**<    +   u8  调整后的音量(NOTE: vx linux 0～32; PCMT: 0～255)*/
														/**<*/
    
    h_ctrl_someOfferingNtf					,		/**<*******************<<  终端通知通用消息 >>********************/
														/**< Mcu-->ter*/
														/**<[消息体]*/
														/**<*/
														/**<    Mcu2MtNtfMsgType*/
														/**<*/ 
                                             
    h_ctrl_videoFrameRateChangeCmd			,		/**<*******************<<  (第一路)视频编码帧率调整 >>************/
														/**< Mc-->ter*/
														/**<[消息体]*/
														/**<*/
														/**<    +   u8  编码帧率*/
														/**<*/

	h_ctrl_removeMixMemberCmd				,		/**<*******************<<  移除定制混音中的终端 (由主席触发有效) >>********************/
														/**< Mt-->Mc*/
														/**<[消息体]*/
														/**<*/
														/**<    +   TMt 数组*/
														/**<*/ 
														/**<*/
	h_ctrl_discussParamInd					,		/**<******************<< 混音信息通知>>****************************/
														/**< Mt-->Mc*/
														/**< [消息体]*/
														/**< + TDiscussParam*/
														/**<*/
														/**<*/
	h_ctrl_videoFormatRecoverCmd			,		/**<*****************<<  终端分辨率恢复命令   >>****not in use now***********/
														/**< ter-->Mt*/
														/**< [消息体]  无*/
														/**<*/
	h_ctrl_mtSelectVmpReq					,		/**<******************<< 终端（仅限主席MT）选看画面合成请求 >>***************/
														/**< ter --> MC*/
														/**< [消息体] u8	1表start,0表stop*/
														/**<*/
	h_ctrl_mtSelectVmpRsp					,		/**<******************<< 终端（仅限主席MT）选看画面合成应答 >>***************/
														/**< MC --> ter*/
														/**< [消息体] u8  ok/fail(1表ok，0表fail)*/
														/**<*/	
    h_ctrl_mtSpeakStatusNtf					,		/**<******************<< 终端 申请发言中的终端              >>***************/
														/**< MC --> ter*/
														/**< [消息体] emMtSpeakerStatus*/
														/**<*/
                                                        /**<     emWaiting       = 1,        //等待同意；mcu不会发送此状态，终端在发起申请 到 成为发言人通知 到 之前，自动跳入该状态*/
                                                        /**<     emAgreed        = 2,        //发言人；*/
                                                        /**<    emDenid         = 3,        //申请被拒绝；*/
                                                        /**<     enCanceled      = 4,        //被取消发言；*/
														/**<*/	

    h_ctrl_confSpeakModeNtf					,		/**<******************<< 终端 所有与会终端                 >>***************/
														/**< MC --> ter*/
														/**< [消息体] emConfSpeakMode*/
                                                        /**<   emNormal            = 0,        //普通发言模式：主席指定/会控指定/一般的终端申请*/
                                                        /**<    emAnswerInstantly   = 1         //抢答模式*/
														/**<*/	

    h_ctrl_applycancelspeakerReq			,		/**<******************<< 发言人终端 －> MCU                 >>***************/
														/**< ter --> MC*/
														/**< [消息体] u8:0-取消发言 1-申请发言*/
														/**<*/	

    h_ctrl_applycancelspeakerRsp			,		/**<******************<< MCU －>  发言人终端                >>***************/
														/**< MC --> ter*/
														/**< [消息体] u8:0-取消发言 1-申请发言*/
														/**<	u8 result: granted/denied*/
														/**<*/	

	h_ctrl_videoFpsChangeCmd				,		/**<********************<< 视频帧率调整  >>*********************/
														/**<* Mcu-->ter*/
														/**<*[消息体]*/
										 				/**<**/
										 				/**<*    +   u8  通道类型   LOGCHL_VIDEO      (默认主视频通道)*/
														/**<*    +   u8  帧率值 */
														/**<*/

	h_ctrl_videoAliasCmd					,		/**<********************<< mcu获取终端视频源别名  >>*********************/
														/**< Mcu-->ter*/
														/**<[消息体] 空*/
														/**<*/
														/**< */   
														/**<*/    
														/**<*/
	h_ctrl_videoAliasInd					,		/*********************<< 终端视频源别名指示  >>*********************/
														/**< ter-->Mcu*/
														/**<[消息体]*/
														/**<  u8 byVidNum（视频源数量）+ u8 byVidIdx（视频源端口索引）+ */  
														/**<  u8 byAliaseLen（别名长度）+ s8 *pchAlias（别名）+ */
														/**<  u8 byVidIdx（视频源端口索引）+ u8 byAliaseLen（别名长度）+  */
														/**<  s8 *pchAlias（别名）+ ...*/
														/**<  */  
														/**<   */ 
														/**<*/
	h_ctrl_ChgSecVidSendCmd	= 101 + 134,/**<********************<< 控制终端双流发送命令 >>*********************/
												/**< Mcu-->ter*/
												/**<[消息体] */
												/**<u8 0—停止双流  1—发起双流*/
												/**< */   
												/**<   */ 
												/**<*/
//[20120613]
	h_ctrl_transparentMsgNtf = 236,    /**<**************<< 界面、终端透传消息  >>*********************/
										/**< ter<-->Mcu*/
										/**<[消息体]*/
										/**<     根据消息类型不同，消息体内容不同*/
										/**< */     
										/**<*/  
										
	h_ctrl_CodingFormNtf = 237,         /**<*************<< 在h245建立后马上向对端发送该非标消息通告对端本端的编码方式  >>*********************/
										 /**<* ter<-->Mcu*/
										 /**<*[消息体]*/
									     /**<* u8(编码方式)*/
										 /**<* /      
										/**< */
	h_ctrl_nonstandardVrsDef = 238,     /**<**************<<非标自定义》*******************/
                                         /**< ter<-->Mcu*/
                                         /**<[消息体]*/
                                         /**<     根据消息类型不同，消息体内容不同*/
                                         /**<     上层两端业务协商消息的子类型和消息内容*/
                                         /**<*/
							             /**<*/
//[20140704]
	h_ctrl_StartMtVmpReq = 239,		/**<********* <<终端开启画面合成请求>>**************************/
   									 /**< ter -->Mcu*/
   									 /**<[消息体]*/
									 /**< u8(画面合成类型：vccommon.h中定义) ) */
									 /**< u8(画面合成方式：vccommon.h中定义) ) */
  	 								 /**< u8(画面合成风格：vccommon.h中定义)*/ 
   									 /**< u8(byLen-有效成员数)*/
   									 /**< （u8(通道号)  + TVMPMember）* byLen*/
									 /**<*/

	h_ctrl_StartMtVmpRsp = 240,		/**<**********<<停止终端画面合成请求>>***************************/        
									/**<ter --> Mcu  */
									/**< [消息体]*/
									/**< u8(画面合成类型：vccommon.h中定义)*/
									 /**<*/

	h_ctrl_StartMtVmpNotify = 241,	/**<***********<<终端开启画面合成通告>>****************************/
   									 /**< Mcu -->ter*/
   									 /**< [消息体]*/
   									 /**< u8(0-成功 1-失败)*/
									 /**< u8(画面合成类型：vccommon.h中定义)*/
								 	 /**<  以下成功时才有 */
									 /**< u8(画面合成方式：vccommon.h中定义)*/
   									 /**< u8(画面合成风格：vccommon.h中定义) */
   									 /**< u8(byLen-有效成员数)*/
   									 /**<(u8(通道号) + TVMPMember) * byLen*/
									 /**<*/


	h_ctrl_StopMtVmpReq = 242, 		/**<***********<<停止终端画面合成请求>>****************************/          
									 /**< ter --> Mcu  */
									 /**< [消息体]*/
									 /**< u8(画面合成类型：vccommon.h中定义)*/
									 /**<*/

	h_ctrl_StopMtVmpRsp = 243,		/**<***********<<停止终端画面合成请求应答>>*************************** */         
									 /**< Mcu --> ter */
									 /**< [消息体]*/
									/**< u8(0-成功 1-失败)*/
									 /**< u8(画面合成类型：vccommon.h中定义) */

	h_ctrl_StopMtVmpNotify = 244,   /**<***********<<停止终端画面合成请求应答>>****************************/          
									 /**< Mcu --> ter */
									/**< [消息体]*/
									 /**< u8(0-成功 1-失败)*/
									 /**< u8(画面合成类型：vccommon.h中定义)*/ 
									 /**<*/


	h_ctrl_ChangeMtVmpReq = 245,	/**<***********<<更改终端画面合成请求>>****************************/
 									 /**< ter -->Mcu*/
 									 /**< [消息体]*/
									 /**< u8(画面合成类型：vccommon.h中定义)*/
									 /**< u8(画面合成方式：vccommon.h中定义)*/
 									/**< u8(画面合成风格：vccommon.h中定义) */
 									/**< u8(byLen-有效成员数)*/
 									 /**< （u8(通道号)  + TVMPMember）* byLen*/
									 /**<*/

	h_ctrl_ChangeMtVmpRsp = 246, 	/**<***********<<更改终端自主画面合成请求应答>>****************************/
 									 /**< Mcu -->ter*/
 									 /**< [消息体]*/
									 /**< u8(0-成功 1-失败)*/
									 /**< u8(画面合成类型：vccommon.h中定义)*/
									 /**<*/

	h_ctrl_ChangeMtVmpNotify = 247,	/**<***********<<更改终端画面合成通告>>****************************/
 									 /**< Mcu -->ter*/
 									 /**< [消息体]*/
									 /**<u8(0-成功 1-失败)*/
									 /**< u8(画面合成类型：vccommon.h中定义)*/
									 /**<  以下成功时才有 */
									 /**<u8(画面合成方式：vccommon.h中定义)*/
 									 /**< u8(画面合成风格：vccommon.h中定义) */
 									 /**< u8(byLen-有效成员数)*/
 									 /**< (u8(通道号)  + TVMPMember) * byLen*/
									 /**<*/
//--20140704--
	h_ctrl_chimeInFailInd = 260,			/**<*******************<<  MT申请插话失败 >>********************/
											/**< Mc-->ter*/
											/**<[消息体] 无*/
											/**<*/
											/**<*/

	h_ctrl_ModifyConfNameReq = 261,			/**<*******************<<  MT命令修改会议名称 >>********************/
											/**< ter-->Mcu*/
											/**< [消息体] s8[64+1]  会议名称*/
											/**<*/
											/**<*/

	h_ctrl_ModifyConfNameRsp = 262,			/**<*******************<<  MT命令修改会议名称 >>********************/
											/**< Mcu-->ter*/
											/**< [消息体] u8  成功/失败*/
											/**<*/
											/**<*/

	h_ctrl_ModifyConfDurationCmd = 263,		/**<*******************<<  MT命令修改会议时长 >>********************/
											/**< ter-->Mcu*/
											/**< [消息体] u16	时长，单位是分钟*/
											/**<*/
											/**<*/

	h_ctrl_ModifyConfPwdCmd = 264,			/**<*******************<<  MT命令修改会议入会密码 >>********************/
											/**< ter-->Mcu*/
											/**< [消息体] u8	是否加密*/ 
											/**<          + s8[16+1] 入会密码*/
											/**<*/
	                                        /**<*/

	h_ctrl_requestTerminalInfo = 265,		/**<*******************<<  MT(主席)请求获得终端信息 >>********/
                                            /**< ter-->Mcu*/
                                            /**< [消息体] TTERLABEL 终端ID  -- byMcuNo = 0, byTerNo = 0，则为发送全部终端信息，否则为查询单个终端信息*/
                                            /**<*/

	h_ctrl_requestTerminalInfoResponce = 266,	/**<*******************<<  MT(主席)请求获得终端信息的平台响应 >>********/
												/**< Mcu-->ter*/
												/**< [消息体] u8(msg flag: 0 - get all, 1- get one)TTerminalInfo  终端信息(adapter42.h,已提取)*/
												/**<*/

	h_ctrl_ModifyConfInfoReq = 267,         /**<*******************<<  MT(主席)命令修改已召开会议信息 >>************/
											/**< * ter-->Mcu*/
											/**< * [消息体] u8 标示修改项(EModifyConfInfoType) (vccommon.h)*/
											/**< *          + 修改内容长度(u32)*/
											/**< *          + 修改内容的buf*/
											/**< */
	h_ctrl_ModifyConfInfoRsp = 268,         /********************<<  MT(主席)命令修改已召开会议信息回复 >>********/
											/**< Mcu-->ter*/
											/**< [消息体] u8 修改项(EModifyConfInfoType)*/
											/**<          + u8  成功/失败(CtrlResult--h323adapter.h)*/
											/**<*/
	h_ctrl_requestTerminalInfoEx = 269,		/**<*******************<<  MT(主席)请求获得终端信息-新 >>********/
                                            /**< ter-->Mcu*/
                                            /**< [消息体] +u32(时间戳)*/
                                            /**<          +TTERLABEL 终端ID  -- byMcuNo = 0, byTerNo = 0，则为发送全部终端信息，否则为查询单个终端信息*/
                                            /**<*/	
                                            
    h_ctrl_requestTerminalInfoResponceEx = 270,		/**<*******************<<  MT(主席)请求获得终端信息的平台响应-新 >>********/
													/**< Mcu-->ter*/
													/**< [消息体] +u32(时间戳)*/
													/**<          +u8(msg end flag: 0 - not end, 1-end)*/
													/**<          +u8(msg flag: 0 - get all, 1- get one)*/
													/**<          +[u32(mtinfo buf size, 网络序) + [mt info buf]](终端信息列表)*/
													/**<*/

	h_ctrl_getDialogAuthReq = 271,          /**<*******************<<  MT请求 >>********/
                                           /**< ter-->Mcu*/
                                            /**< [消息体] 无*/
                                            /**<*/

	h_ctrl_getDialogAuthRsp = 272,          /**<*******************<<  MCU回应 >>********/
                                            /**<* Mcu-->ter*/
                                            /**<* [消息体] u8( 0 - 失败，1 - 成功 )*/
                                            /**<*/

	h_ctrl_giveupDialogAuthReq = 273,       /**<*******************<<  MT请求 >>********/
                                            /**< ter-->Mcu*/
                                           /**< [消息体] 无*/
                                            /**<*/

	h_ctrl_giveupDialogAuthRsp = 274,       /**<*******************<<  MCU回应 >>********/
                                            /**< Mcu-->ter*/
                                            /**< [消息体] u8( 0 - 失败，1 - 成功 )*/
                                            /**<*/

	h_ctrl_applySpeakerFailInd = 275,       /**<*******************<<  MCU回应 >>********/
                                            /**< Mcu-->ter*/
                                            /**< [消息体] 无*/
                                            /**<*/

	h_ctrl_confFailNtf = 276,               /**<****************会议发生错误通知***********/
											/**<MCU--->ter*/
											/**<[消息体]错误原因EConfFailureReason*/
											/**<*/

	h_ctrl_startDialogReq = 277,            /**<****************申请开始对讲模式***********/
                                            /**<ter-->Mcu, 主席专用*/
                                            /**<[消息体] 无*/
                                            /**<*/

	h_ctrl_startDialogRsp = 278,            /**<****************申请开始对讲模式回应***********/
                                            /**<*MCU--->ter
                                            /**< [消息体] u8( 0 - 失败，1 - 成功 )*/
                                            /**<*/

	h_ctrl_stopDialogReq = 279,             /*****************申请停止对讲模式***********/
                                            /**<ter-->Mcu, 主席专用*/
                                            /**<[消息体] 无*/
                                            /**<*/

	h_ctrl_stopDialogRsp = 280,             /**<****************申请停止对讲模式回应***********/
                                            /**<MCU--->ter
                                            /**<[消息体] u8( 0 - 失败，1 - 成功 )*/
                                            /**<*/

	h_ctrl_specDialogMtReq = 281,			/**<****************主席指定对讲终端***********/
                                            /**<ter-->Mcu, 主席专用*/
                                            /**<[消息体] TTERLABEL*/
                                            /**<*/

	h_ctrl_specDialogMtRsp = 282,			/*****************主席指定对讲终端回应***********/
                                            /**<MCU--->ter*/
                                            /**<[消息体] u8( 0 - 失败，1 - 成功 )*/
                                            /**<*/

	h_ctrl_confDialogStateNtf = 283,		/**<****************会议对讲模式状态通知***********/
                                            /**<MCU--->ter*/
                                            /**<[消息体] u8( 会议对讲模式状态：0 - 非对讲模式，1 - 对讲模式 ) + [s8*N](进入对讲模式的触发者别名，会议对讲模式状态=1时有效)*/
                                            /**<*/

	h_ctrl_youInDialogPosNtf = 284,			/**<****************终端对话位置通知***********/
                                            /**<MCU--->ter*/
                                            /**<*[消息体] u8( 0 - 不在对讲位置，1 - 在对讲位置 )*/
                                            /**<*/
//285
	h_ctrl_youInPresidePosNtf				= 285,		/**<****************终端主讲位置通知***********/
													    /**<MCU--->ter*/
														/**<[消息体] u8( 0 - 不在主讲位置，1 - 在主讲位置 )*/
														/**<*/
	h_ctrl_SvrGeneralMsg					= 286,		//Svr通用消息,专用Svr之间通信，mcu不感知[incoming]&[outgoing] TTERLABEL tDstSvr + buf
	/**Nonstandard message*/
	h_ctrl_nonstandstart					= 300,	

	h_ctrl_quietRequest						= 301,  /**<远端静音请求,				[outgoing]: [TTERLABEL]*/
	h_ctrl_quietResponse					= 302,  /**<远端静音响应				[incoming]: [TTERLABEL+u8:CtrlResult]*/

	h_ctrl_cancelQuietRequest				= 303,  /**<取消远端静音请求			[outgoing]: [TTERLABEL]*/
	h_ctrl_cancelQuietResponse				= 304,  /**<取消远端静音响应			[incoming]: [TTERLABEL+u8:CtrlResult]*/

	h_ctrl_muteRequest						= 305,  /**<远端闭音请求,				[outgoing]: [TTERLABEL]*/
	h_ctrl_muteResponse 					= 306,  /**<远端闭音响应				[incoming]: [TTERLABEL+u8:CtrlResult]*/

	h_ctrl_cancelMuteRequest				= 307,  /**<取消远端闭音请求			[outgoing]: [TTERLABEL]*/
	h_ctrl_cancelMuteResponse				= 308,  /**<取消远端闭音响应			[incoming]: [TTERLABEL+u8:CtrlResult]*/

	h_ctrl_setVACReqequest					= 309,  /**<设置声控切换(语音激励)	[outgoing]: [u8+DW] 0：设置声控切换1：取消声控切换+1 DW 声控门限(0~100之间的一个值),可以没有声控门限，这时使用缺省的声控门限*/
	h_ctrl_setVACResponse					= 310,  //设置声控切换结果			[incoming]: [u8:CtrlResult](返回是对设置操作的结果，不是表明当前声控切换的状态。例如，取消声控切换的结果为成功，表示取消声控切换的设置成功。)*/

	h_ctrl_startDiscussRequest				= 311,  /**<开始自由讨论				[outgoing]: NULL*/
	h_ctrl_startDiscussResponse				= 312,  /**<自由讨论结果				[incoming]: [u8:CtrlResult]终端收到这条结果,所有会场开音,全部取消静音*/
	
	h_ctrl_setMultiPicRequest				= 313,  /**<//设置多画面				[outgoing]: TMultiPic*/
	h_ctrl_setMultiPicResponse				= 314,  
	h_ctrl_notInConfTerminalListRequest		= 315,	/**<请求所有未入会会场名	[outgoing]: NULL*/
	h_ctrl_notInConfTerminalListResponse	= 316,	/**<所有未入会会场名应答	[incoming]: [TTERINFO[]]*/

	h_ctrl_callTerminal						= 317,  /**<呼叫离线会场				[outgoing]: [TTERLABEL]*/
	h_ctrl_disconnectTerminal				= 318,  /**<//挂断终端					[outgoing]: [TTERLABEL]*/
	h_ctrl_selectSpeakingUserRequest		= 319,	/**<点名发言					[outgoing]: [TTERLABEL]*/
	h_ctrl_selectSpeakingUserResponse		= 320,  /**<点名发言结果				[incoming]: [TTERLABEL+u8:CtrlResult]*/
	h_ctrl_setPicSwitch						= 321,	/**<单,多画面切换				[outgoing]: [u8] 0:单画面;1:多画面*/
    h_ctrl_capabilitiesInd					= 322,  /**<对通能力指示              [incoming]: [TCAPINFO]*/
    h_ctrl_serialPortData					= 323,  /**<串口数据                  [incoming]&[outgoing]: [TCOMDATA]*/

	h_ctrl_setChanMultiCastAddr				= 400,  /**<//设置通道组播地址			[incoming]&[outgoing]: [TCHANMULTICAST]*/
	h_ctrl_serialNumber      				= 401,  /**<序列号    				[incoming]&[outgoing]: [u8[]]*/ 
    h_ctrl_startDataConfRequest				= 402,  /**<请求开始数据会议          NULL*/
	h_ctrl_startDataConfResponse			= 403,  /**<应答开始数据会议          [incoming]&[outgoing]: u8: result*/

	h_ctrl_askVcsOccupyPermit				= 500,	/**<请求会议是否同意强拆      [outgoing]:[NULL]  mt->mcu */
	h_ctrl_askVcsOccupyPermitResp			= 501,  /**<会议回复是否同意强拆      [incoming]:[u8]0:不同意 1:同意  mcu->mt*/
	h_ctrl_requestConfTerminalIDs			= 502,  /**< 请求与会终端E164号      [outgoing]*/
	h_ctrl_requestConfTerminalIDsResponse	= 503,	/**< 应答*/
	h_ctrl_requestTerminalE164				= 504,	/**<ter询问终端E164	    ter->MC,   [incoming]&[outgoing]: []*/
	h_ctrl_requestTerminalE164Responce		= 505,	/**<MC回答终端名E164	    MC->ter,   [incoming]&[outgoing]: []*/

	h_ctrl_VersionIdInd						= 600,	/**< 消息体为u8[LEN_256]*/
	h_ctrl_KdvpExtraConfNSNInfo				= 601,	/**< 超过192个终端列表用这个非标 [incoming]&[outgoing]*/

	h_ctrl_startVMPNotify					= 602,	/**<与h_ctrl_startVMPReq, h_ctrl_startVMPRsp相对应*/
	h_ctrl_stopVMPNotify					= 603,	/**<与h_ctrl_stopVMPReq, h_ctrl_stopVMPRsp相对应*/
	h_ctrl_changeVMPParamNotify				= 604,	/**<与h_ctrl_changeVMPParamReq, h_ctrl_changeVMPParamRsp相对应*/
	
	h_ctrl_SecVidSrcInd						= 605,		/**<sip用 通知双流源是谁*/
	h_ctrl_confsubscribe_ntf                = 700,  //终端请求或取消订阅
	
	/** 电话终端信令*/
    h_ctrl_joinConferenceNtf				= 1001,        /**<*******************<< Mcu to Phone>>**************************/
    h_ctrl_TerminalJoinNtf					= 1002,
    h_ctrl_TerminalLeftNtf					= 1003,
    h_ctrl_youQuietNtf						= 1004,
    h_ctrl_youMuteNtf						= 1005,
    h_ctrl_youAreSpeaker					= 1006,
    h_ctrl_youAreJoinAudMixer				= 1007,
    h_ctrl_terminalApplyAsSpeakerRsp		= 1008,
    h_ctrl_terminalChimeInRsp				= 1009,
    h_ctrl_joinedTerminalNumNtf				= 1010,

    h_ctrl_phoneStatusReq					= 1050,
    h_ctrl_joinedTerminalNumReq				= 1051,
    h_ctrl_confInfoNtf						= 1052,
	
	/**三条vip列表消息信令*/
	h_ctrl_VipListReq						= 1101,
	h_ctrl_VipListRsp						= 1102,
	h_ctrl_VipListNotify					= 1103,

	h_ctrl_dataConfCreatedNtf				= 1104,		/**<白板会议创建通知 mt -> mcu, 字符串：confname*/
	h_ctrl_joinDataConfCmd					= 1105,		/**<加入白板会议命令 mcu -> mt, 字符串：confname*/

	h_ctrl_allLocAliasNotif					= 1106,     /**<终端通知所有通道别名*/
	h_ctrl_selectViewChnCmd					= 1107,		/**<指定选看某终端某通道*/

	/**添加ter-->mc对应的非标信令ID：*/
	h_ctrl_chairSpecifyDualStream			= 1108,		/**<Chair --> MC 指定与会终端发双流 */
	h_ctrl_bitRatePercentage				= 1109,		/**<MT --> MC    指定当前终端多路接收通道码率的比例*/

    h_ctrl_cancelSelectViewChnCmd			= 1110,		/**<取消指定选看某终端某通道*/

	h_ctrl_nonstandard_fecc					= 1111,		/**<nonstandard message for fecc*/
	
	h_ctrl_terGetTerVidAliasReq             = 1112,  /**<终端向平台获取其他终端的视频源别名*/

	h_ctrl_terGetTerVidAliasRsp             = 1113,  /**<平台回复终端 其他终端的视频源别名*/
	
	h_ctrl_getTerCameraPosCmd               = 1114, /**< 平台获取终端预置位信息*/
	h_ctrl_terCameraPosNtf				    = 1115, /**< 终端预置位信息上报*/

	h_ctrl_terGetTerCameraPosCmd            = 1116, /**< 终端向平台获取其他终端预置位信息*/
	h_ctrl_terGetTerCameraPosNtf            = 1117, /**<平台回复终端其他终端预置位信息*/

	h_ctrl_GetTerLossRateCmd				= 1118,	 /**<mcu获取终端丢包率*/
	h_ctrl_terGetTerLossRateNtf				= 1119,	 /**<mt向mcu发送丢包率通知*/
	h_ctrl_bFeccSupport             		= 1120, /**<是否支持fec 功能， mt->mcu, mcu->mt*/

	h_ctrl_KedaManuProduct          		= 1121, /**<防串货渠道标识， mt<-->mcu，mt<-->mt非标内容：*/
											                    /**<V5.0 <--> V5.0: protobuf*/
											                    /**<V5.0 <--> V4.x(HD3): TKedaManuProduct*/
											                    /**<TPS <--> TPS: TKedaManuProduct*/

	h_ctrl_GetTerRealtimeInfoCmd			= 1122, /**<mcu获取终端实时信息*/
	h_ctrl_GetTerRealtimeInfoNtf			= 1123, /**<mt向mcu发送实时信息通知*/
	h_ctrl_PlatformCloudType                = 1124, /**<表示不同云类型， 0-私有云 1-公有云 2-混合云*/

    h_ctrl_PAMeetingSpeaker                 = 1329, //网呈终端切换发言人
    h_ctrl_SpeakerChanSwithNtf              = 1330, //主屏切换通知

	h_ctrl_terAuthMsg               		= 1500, /**<终端认证消息*/
	h_ctrl_terQTMsg                         = 1501, //量通非标消息，目前只用于查询devid和回复
		
	h_ctrl_nonstandard_general				= 2000,		/**<Jacky Wei: a general nonstandard event id for KDV v5.0*/
	h_ctrl_nonstandardend					= 2001,
};

/**<企业非标h_ctrl_nonstandardinvalid定义为101，和h_ctrl_mcuvccommonnonstandstart冲突*/
#define h_ctrl_nonstandardinvalid	h_ctrl_mcuvccommonnonstandstart



/**//////////////////////  从kdv323adapter.h中提出的级联会议消息和结构体 begin  /////////*/
enum H323MCUMsgType
{
		CASCADE_MSGTYPE_BEGINNING		= 0,
        
        H_CASCADE_REGUNREG_REQ			= 1,   /**<[IN]&[OUT]:[TRegUnRegReq]	register request*/
        H_CASCADE_REGUNREG_RSP			= 2,   /**<[IN]&[OUT]:[TRegUnRegRsp]	register response*/
        
        H_CASCADE_NEWROSTER_NTF			= 3,   /**<[IN]&[OUT]:[TRosterList]  roster notify*/
        
        H_CASCADE_PARTLIST_REQ			= 4,   /**<[IN]&[OUT]:[TReq]         request part list */
        H_CASCADE_PARTLIST_RSP			= 5,   /**<[IN]&[OUT]:[TPartListRsp] reponse part list (dwpid ==0 表示对方的MCU)*/
        
        H_CASCADE_INVITEPART_REQ		= 6,	/**<[IN]&[OUT]:[TInvitePartReq]  invite part request*/
        H_CASCADE_INVITEPART_RSP		= 7,	/**<[IN]&[OUT]:[Tsp]             invite part response*/
        H_CASCADE_NEWPART_NTF			= 8,    /**<[IN]&[OUT]:[TPart]           new part notify*/
        
        H_CASCADE_CALL_ALERTING_NTF		= 9,	/**<[IN]&[OUT]:[TCallNtf]*/
        
        H_CASCADE_REINVITEPART_REQ		= 10,	 /**<[IN]&[OUT]:[TReInviteReq]    reinvite part request*/
        H_CASCADE_REINVITEPART_RSP		= 11,	/**<[IN]&[OUT]:[Tsp]        reinvite part response*/
        
        H_CASCADE_DISCONNPART_REQ		= 12,	/**<[IN]&[OUT]:[TPartReq]     disconnect part request*/
        H_CASCADE_DISCONNPART_RSP		= 13,	/**<[IN]&[OUT]:[Tsp]         disconnect part response*/
        H_CASCADE_DISCONNPART_NTF		= 14,	/**<[IN]&[OUT]:[TDiscPartNF] disconnect part notify*/
        
        
        H_CASCADE_DELETEPART_REQ		= 15,	/**<[IN]&[OUT]:[TPartReq]		delete part request*/
        H_CASCADE_DELETEPART_RSP		= 16,	/**<[IN]&[OUT]:[Tsp]			delete part response*/
        H_CASCADE_DELETEPART_NTF		= 17,	/**<[IN]&[OUT]:[TPartNtf]   delete part notify (whether or not local)*/
        
        H_CASCADE_SETIN_REQ				= 18,      /**<[IN]&[OUT]:[TSetInReq]    request video in*/
        H_CASCADE_SETIN_RSP				= 19,      /**<[IN]&[OUT]:[Tsp]          response msg*/
        
        H_CASCADE_SETOUT_REQ			= 20,     /**<[IN]&[OUT]:[TSetOutReq]//视频输出到自己的请求(视频流向:MCU->MT)*/
        H_CASCADE_SETOUT_RSP			= 21,     /**<[IN]&[OUT]:[Tsp]//视频输出到自己的应答(视频流向:MCU->MT)*/
        
        H_CASCADE_OUTPUT_NTF			= 22,     /**<[IN]&[OUT]:[TPartOutputNtf]      video output notify (dwpid ==0 表示对方的MCU)*/
        
        H_CASCADE_NEWSPEAKER_NTF		= 23,	/**<[IN]&[OUT]:[TNewSpeakerNtf]      newSpeaker output notify (dwpid ==0 表示对方的MCU)*/
        
        H_CASCADE_AUDIOINFO_REQ			= 24,	/**<[IN]&[OUT]:[TConfVideInfoReq]         audio info request */
        H_CASCADE_AUDIOINFO_RSP			= 25,   /**<[IN]&[OUT]:[TConfAudioInfo]    audio info response*/
        
        H_CASCADE_VIDEOINFO_REQ			= 26,	/**<[IN]&[OUT]:[pReq]          conference videoinfo request */
        H_CASCADE_VIDEOINFO_RSP			= 27,	/**<[IN]&[OUT]:[TConfVideoInfo] conference videoinfo response*/
        
        
        H_CASCADE_CONFVIEW_CHG_NTF		= 28,	/**<[IN]&[OUT]:[TConfViewChgNtf] conference view format(layout geometry)change notify*/
        
        H_CASCADE_PARTMEDIACHAN_REQ		= 29,   /**<[IN]&[OUT]:[TPartMediaChanReq] 请求会议成员打开/关闭音/视频/数据通道*/
        H_CASCADE_PARTMEDIACHAN_RSP		= 30,   /**<[IN]&[OUT]:[TRsp]    response*/
        H_CASCADE_PARTMEDIACHAN_NTF		= 31,   /**<[IN]&[OUT]:[TPartMediaChanNtf] 会议成员的音/视频/数据通道打开/关闭的通知*/

        H_CASCADE_GETMCUSERVICELIST_REQ = 32,	/**<[IN]&[OUT]:[TReq] 获取MCU上的服务模板列表的请求消息*/
		H_CASCADE_GETMCUSERVICELIST_RSP	= 33,	/**<[IN]&[OUT]:[暂时未定义]  response*/

		H_CASCADE_GETMUCCONFLIST_REQ	= 34,	/**<[IN]&[OUT]:[TMCUConfListReq] 获取MCU上当前召开的所有会议的列表*/
		H_CASCADE_GETMUCCONFLIST_RSP	= 35,	/**<[IN]&[OUT]:[暂时未定义]*/
  
        H_CASCADE_GETCONFGIDBYNAME_REQ	= 36,	/**<[IN]&[OUT]:[TGetConfIDByNameReq] 通过会议名字获得会议ID的请求消息*/
        H_CASCADE_GETCONFGIDBYNAME_RSP	= 37,	/**<[IN]&[OUT]:[暂时未定义]*/
		
        H_CASCADE_GET_CONFPROFILE_REQ	= 38,	/**<[IN]&[OUT]:[TConfProfileReq] 获取MCU上当前召开的所有会议的profile*/
		
        H_CASCADE_GET_CONFPROFILE_RSP	= 39,	/**<[IN]&[OUT]:[暂时未定义]*/

        H_CASCADE_NONSTANDARD_REQ		= 40,	/**<[IN]&[OUT]:[TNonStandardReq] 非标(自定义)请求消息*/
        H_CASCADE_NONSTANDARD_RSP		= 41,	/**<[IN]&[OUT]:[TNonStandardRsp] 非标(自定义)response消息*/
		H_CASCADE_NONSTANDARD_NTF		= 42,	/**<[IN]&[OUT]:[TNonStandardMsg] 非标(自定义)notify消息*/
		//
        H_CASCADE_NOT_SUPPORTED			= 43,
		/**目前我们还不支持,但是radmuc支持的消息类型*/
        H_CASCADE_VA_REQ				= 44,       /**<[IN]&[OUT]:[TVAReq]*/
        H_CASCADE_VA_RSP				= 45,       /**<[IN]&[OUT]:[TRsp]*/

        H_CASCADE_RELEASECONTROL_OF_CONF_REQ = 46,	/**<[IN]&[OUT]:[]*/
        H_CASCADE_RELEASECONTROL_OF_CONF_RSP = 47,	/**<[IN]&[OUT]:[]*/

        H_CASCADE_TAKECONTROL_OF_CONF_REQ	 = 48,	/**<[IN]&[OUT]:[]*/
        H_CASCADE_TAKECONTROL_OF_CONF_RSP	 = 49,	/**<[IN]&[OUT]:[]*/

        H_CASCADE_ALLPART_SETOUT_REQ	= 50,	/**<[IN]&[OUT]:[]*/
        H_CASCADE_ALLPART_SETOUT_RSP	= 51,	/**<[IN]&[OUT]:[]*/
        
        H_CASCADE_CREATE_CONF_REQ		= 52,	/**<[IN]&[OUT]:[]*/
        H_CASCADE_CREATE_CONF_RSP		= 53,	/**<[IN]&[OUT]:[]*/
        
        H_CASCADE_TERMINATE_CONF_REQ	= 54,	/**<[IN]&[OUT]:[]*/
        H_CASCADE_TERMINATE_CONF_RSP	= 55,	/**<[IN]&[OUT]:[]*/

        H_CASCADE_UNDEFINED_REQ			= 56,	/**<[IN]&[OUT]:[]*/
        H_CASCADE_UNDEFINED_RSP			= 57,	/**<[IN]&[OUT]:[]*/
        H_CASCADE_UNDEFINED_NTF			= 58,	/**<[IN]&[OUT]:[]*/

        //add 2007.04.28
        H_CASCADE_SET_LAYOUT_AUTOSWITCH_REQUEST  = 59,	/**<[IN]&[OUT]:TSetLayoutAutoswitchReq*/
        H_CASCADE_SET_LAYOUT_AUTOSWITCH_RESPONSE = 60,
        
        CASCADE_MSGTYPE_ENDING = 61
};

#endif //_H323CONFNONSTDMSG_H
