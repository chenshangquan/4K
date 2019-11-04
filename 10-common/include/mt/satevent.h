      /*****************************************************************************
   模块名      : MT Core
   文件名      : MtEvent.h
   相关文件    : 
   文件实现功能: 终端消息内部定义
   作者        : 黄海明
   版本        : V3.0  Copyright(C); 2003 KDC, All rights reserved.
-----------------------------------------------------------------------------
   修改记录:
   日  期      版本        修改人      修改内容
   2003/08/16  3.0         黄海明      创建
   2003/08/20  3.0         邓辉		   定义消息
******************************************************************************/
#ifndef _MTCORE_EVENT_DEF_H
#define _MTCORE_EVENT_DEF_H

#include "eventid.h"

//业务消息类型
enum  MsgType 
{
	MT_SYS = 1,
	MT_INNER,
	MT_OUTER,
};

//业务子消息类型
enum MsgSubType 
{
	//内部消息接口类型
	INNER_CALL = 1,
	INNER_CHAN,
	INNER_CTRL,
	INNER_RAS,
	INNER_MISC,
	INNER_MC,
	INNER_SAT,

	//外部消息接口类型
	OUTER_CONFCTRL,
	OUTER_MATRIX,
	OUTER_CAMERA,
	OUTER_CODEC,
	OUTER_CFG,
	OUTER_MISC,
	OUTER_VXUI,
	OUTER_WINUI
};

//系统消息边界定义
#define EV_MTSYS_BGN		EV_MT_BGN					//(29001)
#define EV_MTSYS_END		( EV_MTSYS_BGN + 50 ) 		//(29051)

//内部消息边界定义
#define EV_INNER_BGN		EV_MTSYS_END				//(29051)
#define EV_INNER_END		( EV_INNER_BGN + 600 )		//(29551)

#define INNER_CALL_ENTRY	EV_INNER_BGN
#define INNER_CHAN_ENTRY	( INNER_CALL_ENTRY + 20 )	//(29071)
#define INNER_CTRL_ENTRY	( INNER_CHAN_ENTRY + 40 )	//(29111)
#define INNER_RAS_ENTRY		( INNER_CTRL_ENTRY + 150 )	//(29261)
#define INNER_MISC_ENTRY	( INNER_RAS_ENTRY  + 40 )	// 29301
#define INNER_MC_ENTRY		( INNER_MISC_ENTRY + 50 )	// 29351
#define INNER_SAT_ENTRY		( INNER_MC_ENTRY + 50 )		// 29401

//外部消息边界定义
#define EV_OUTER_BGN		EV_INNER_END				//(29451)
#define EV_OUTER_END		( EV_OUTER_BGN + 500 )		//(29951)

#define OUTER_CONF_ENTRY	EV_OUTER_BGN				// 29451
#define OUTER_MATR_ENTRY	( OUTER_CONF_ENTRY + 150 )	// 29601
#define OUTER_CAM_ENTRY		( OUTER_MATR_ENTRY + 30 )	// 29631
#define OUTER_CODEC_ENTRY	( OUTER_CAM_ENTRY  + 20 )	// 29651
#define OUTER_CFG_ENTRY		( OUTER_CODEC_ENTRY + 80 )	// 29731
#define OUTER_MISC_ENTRY	( OUTER_CFG_ENTRY  + 80 )	// 29811
#define OUTER_VXUI_ENTRY	( OUTER_MISC_ENTRY + 50 )	// 29861
#define OUTER_WINUI_ENTRY	( OUTER_VXUI_ENTRY + 50 )	// 29911

//定时器消息边界定义
#define EV_TIMER_BGN		EV_OUTER_END		
#define EV_TIMER_END		( EV_TIMER_BGN + 30 )

// 用于直接OSP消息处理
#define EV_OUTEROSP_BGN		EV_TIMER_END
#define EV_OUTEROSP_END		( EV_OUTEROSP_BGN + 50 )



//==========================================================================================
//									系统消息定义
//==========================================================================================

// 应用对象初始化消息(对于RAS,需要应用句柄参数)
OSPEVENT (EV_SYS_INIT_CMD			, EV_MTSYS_BGN + 1);
// 应用对象初始化完成指示		| 1BYTE,MT_OK|MT_ERR
OSPEVENT (EV_SYS_INITRET_IND		, EV_MTSYS_BGN + 2);
// 终端重启命令					| NULL
OSPEVENT (EV_SYS_REBOOT_CMD			, EV_MTSYS_BGN + 3);
// 本地UI注册指示				| u32(vxWorks:app id,windows:window handle)
OSPEVENT (EV_SYS_UIREG_IND			, EV_MTSYS_BGN + 4);
// 终控上线指示					| u32 nodeid + u32 insid
OSPEVENT (EV_SYS_MTCLOG_IND			, EV_MTSYS_BGN + 5);


// 任务检测请求					| NULL
OSPEVENT( EV_SYS_TASKALIVE_REQ		, EV_MTSYS_BGN + 26);
// 任务检测应答					| NULL
OSPEVENT( EV_SYS_TASKALIVE_RSP		, EV_MTSYS_BGN + 27);

// E1线路状态改变				| CDevStatus				| MT->AGENT
OSPEVENT( EV_AGT_E1LINE_IND		, EV_MTSYS_BGN + 31 );
// 内存状态改变，				| 1BYTE(MT_OK:正常 MT_ERR:异常)		| MT->AGENT
OSPEVENT( EV_AGT_MEMORY_IND		, EV_MTSYS_BGN + 32 );
// 文件系统状态改变				| 1BYTE(MT_OK:正常 MT_ERR:异常)		| MT->AGENT
OSPEVENT( EV_AGT_FILESYSTEM_IND	, EV_MTSYS_BGN + 33 );
// 任务状态改变					| CTaskStatus				| MT->AGENT
OSPEVENT( EV_AGT_TASK_IND		, EV_MTSYS_BGN + 34 );
// MAP状态改变					| CMapStatus				| MT->AGENT
OSPEVENT( EV_AGT_MAP_IND		, EV_MTSYS_BGN + 35 );
// CCI状态改变					| CCCIStatus				| MT->AGENT
OSPEVENT( EV_AGT_CCI_IND		, EV_MTSYS_BGN + 36 );
// 以太网状态					| CEthernetCardStatus		| MT->AGENT
OSPEVENT( EV_AGT_ETHERNET_IND	, EV_MTSYS_BGN + 37 );
// 媒体流状态					| CMediaStreamStatus		| MT->AGENT
OSPEVENT( EV_AGT_MEDIASTREAM_IND, EV_MTSYS_BGN + 38 );
// 设备连接状态改变				| CEqpConnStatus			| MT->AGENT
OSPEVENT( EV_AGT_EQPCONNECT_IND	, EV_MTSYS_BGN + 39 );
// 视频矩阵的状态				| 1BYTE(MT_OK:正常 MT_ERR:异常)		| MT->AGENT
OSPEVENT( EV_AGT_VIDEOSOURCE_IND, EV_MTSYS_BGN + 40 );
// 风扇状态改变					| CFanStatus				| MT->AGENT
OSPEVENT( EV_AGT_FAN_IND		, EV_MTSYS_BGN + 41 );
// V35状态改变					| 1BYTE(MT_OK: 正常			| MT->AGENT
// MT_ERR:异常(bit0载波检测失败 bit1清除发送失败, bit2请求发送失败,bit3数据终端未就绪,bit4数据未准备好)
OSPEVENT( EV_AGT_V35_IND		, EV_MTSYS_BGN + 42 );

//面板灯状态通知                |TBrdMTLedStateDesc         | MT->AGENT
OSPEVENT( EV_AGT_PANELLED_IND		, EV_MTSYS_BGN + 43 );
//线路带宽通知                |4字节(带宽)         | guard->mt
OSPEVENT( EV_GUARD_CHANBW_IND		, EV_MTSYS_BGN + 44 );

// 集成测试查询消息				| 1BYTE						|
OSPEVENT( EV_SYS_INTTEST_CMD		, EV_MTSYS_BGN + 46 );


//==========================================================================================
//									内部消息定义
//==========================================================================================

//////////////////////////// 呼叫消息 //////////////////////////////

// 新呼叫句柄通知			| NULL
OSPEVENT (EV_CALL_NEW_IND				 , INNER_CALL_ENTRY + 1);		
// 发起呼叫					| TCALLPARAM
OSPEVENT (EV_CALL_MAKE_CMD				 , INNER_CALL_ENTRY + 2);		
// FACILITY					| TFACILITYINFO
OSPEVENT (EV_CALL_FACILITY_CMD			 , INNER_CALL_ENTRY + 3);		
// 挂断呼叫					| NULL
OSPEVENT (EV_CALL_HANGUP_CMD			 , INNER_CALL_ENTRY + 4);		
// 呼叫到来					| TCALLPARAM
OSPEVENT (EV_CALL_INCOMING_IND			 , INNER_CALL_ENTRY + 5);		
// 呼叫建立					| TNODEINFO
OSPEVENT (EV_CALL_CONNECTED_IND			 , INNER_CALL_ENTRY + 6);		
// 呼叫断开					| 1BYTE,断开原因
OSPEVENT (EV_CALL_DISCONNECTED_IND		 , INNER_CALL_ENTRY + 7);		
// 呼叫应答					| TNODEINFO
OSPEVENT (EV_CALL_ANSWER_CMD			 , INNER_CALL_ENTRY + 8);

// 传递内部呼叫信息(MT->MC)	| NULL
OSPEVENT (EV_CALL_PASSINFO_IND			 , INNER_CALL_ENTRY + 11);


//////////////////////////// 信道消息 //////////////////////////////

// 进入通道模式				| NULL
OSPEVENT (EV_CHAN_ENTRYMODE_IND			 , INNER_CHAN_ENTRY + 1);		
// 新信道句柄				| NULL
OSPEVENT (EV_CHAN_INCOMINGNEW_IND		 , INNER_CHAN_ENTRY + 2);
// 新信道句柄				| TCHANPARAM
OSPEVENT (EV_CHAN_OUTGOINGNEW_IND		 , INNER_CHAN_ENTRY + 3);
// 打开逻辑通道请求			| TCHANPARAM(Outgoing) | NULL(Incoming)
OSPEVENT (EV_CHAN_OPEN_REQ				 , INNER_CHAN_ENTRY + 4);
// 打开逻辑通道应答			| TCHANPARAM
OSPEVENT (EV_CHAN_OPEN_RSP		  		 , INNER_CHAN_ENTRY + 5);
// 逻辑通道已经打开			| NULL
OSPEVENT (EV_CHAN_CONNECTED_IND			 , INNER_CHAN_ENTRY + 6);
// 关闭逻辑通道命令			| NULL
OSPEVENT (EV_CHAN_CLOSE_CMD				 , INNER_CHAN_ENTRY + 7);	
// 释放逻辑通道指示			| NULL
OSPEVENT (EV_CHAN_RELEASE_IND			 , INNER_CHAN_ENTRY + 8);	
// 释放逻辑通道命令			| NULL
OSPEVENT (EV_CHAN_RELEASE_CMD			 , INNER_CHAN_ENTRY + 9);
// 设置RTP地址				| TNETADDR
OSPEVENT (EV_CHAN_SETRTPADDR_IND		 , INNER_CHAN_ENTRY + 10);
// 设置RTCP地址				| TNETADDR
OSPEVENT (EV_CHAN_SETRTCPADDR_IND		 , INNER_CHAN_ENTRY + 11);
// 逻辑通道参数指示			| TCHANPARAM
OSPEVENT (EV_CHAN_PARAM_IND				 , INNER_CHAN_ENTRY + 12);
// 图像冻结命令				| NULL
OSPEVENT (EV_CHAN_VCF_CMD				 , INNER_CHAN_ENTRY + 13);
// 图像更新命令				| NULL
OSPEVENT (EV_CHAN_VCU_CMD				 , INNER_CHAN_ENTRY + 14);
// 流量控制命令				| BitRate(u16):kbps
OSPEVENT (EV_CHAN_FLOWCTRL_CMD			 , INNER_CHAN_ENTRY + 15);


//////////////////////////// 会议控制消息 //////////////////////////////

// h.245连接建立			| NULL
OSPEVENT (EV_CTRL_H245CONNECT_IND		 , INNER_CTRL_ENTRY + 1);
// 能力交换通知				| TCAP
OSPEVENT (EV_CTRL_CAPNOTIFY_IND			 , INNER_CTRL_ENTRY + 2);
// 能力交换应答				| 1BYTE,CapExchangeResult
OSPEVENT (EV_CTRL_CESE_RSP				 , INNER_CTRL_ENTRY + 3);
// 主从决定开始命令			| terminalType(u32)+random number(u32)
OSPEVENT (EV_CTRL_MASTERSLAVE_CMD		 , INNER_CTRL_ENTRY + 4);
// 主从决定结果指示			| 1BYTE,MasterSlaveResult
OSPEVENT (EV_CTRL_MASTERSLAVE_IND		 , INNER_CTRL_ENTRY + 5);
// 激活MC
OSPEVENT (EV_CTRL_MCACTIVE_IND			 , INNER_CTRL_ENTRY + 6);
// MCU要求输入会议密码		| NULL			mc->ter
OSPEVENT (EV_CTRL_H243PWD_REQ			 , INNER_CTRL_ENTRY + 7);
// MT回答会议密码			| TTERLABEL + 1BYTE,password length (<= LEN_H243PWD) + password(char*)
OSPEVENT (EV_CTRL_H243PWD_RSP			 , INNER_CTRL_ENTRY + 8);

// 开始多点会议				| NULL
OSPEVENT (EV_CTRL_MCCSTART_CMD			 , INNER_CTRL_ENTRY + 10);
// 通讯模式命令				| TCOMMODEINFO
OSPEVENT (EV_CTRL_COMMODE_CMD			 , INNER_CTRL_ENTRY + 11);
// 请求通讯模式				| NULL
OSPEVENT (EV_CTRL_COMMODE_REQ			 , INNER_CTRL_ENTRY + 12);
// 回答通讯模式				| TCOMMODEINFO
OSPEVENT (EV_CTRL_COMMODE_RSP			 , INNER_CTRL_ENTRY + 13);
// MC地址指示				| TNETADDR
OSPEVENT (EV_CTRL_MCLOCATION_IND		 , INNER_CTRL_ENTRY + 14);


// 分配终端编号				| TTERLABEL
OSPEVENT (EV_CTRL_ASSIGNTERNO_IND		 , INNER_CTRL_ENTRY + 16);
// 请求终端列表				| NULL
OSPEVENT (EV_CTRL_TERLIST_REQ			 , INNER_CTRL_ENTRY + 17);
// 终端列表应答				| TTERLABEL数组
OSPEVENT (EV_CTRL_TERLIST_RSP			 , INNER_CTRL_ENTRY + 18);
// MC要求终端输入名字		| NULL
OSPEVENT (EV_CTRL_ENTERNAME_REQ			 , INNER_CTRL_ENTRY + 19);
// 终端回答MC名字			| TTERINFO
OSPEVENT (EV_CTRL_ENTERNAME_RSP			 , INNER_CTRL_ENTRY + 20);
// 终端请求其他终端名字		| TTERLABEL
OSPEVENT (EV_CTRL_TERNAME_REQ			 , INNER_CTRL_ENTRY + 21);
// MC回答其他终端名字		| TTERINFO
OSPEVENT (EV_CTRL_TERNAME_RSP			 , INNER_CTRL_ENTRY + 22);
// 终端请求所有终端名字		| NULL
OSPEVENT (EV_CTRL_ALLNAME_REQ			 , INNER_CTRL_ENTRY + 23);
// MC回答所有终端名字		| TTERINFO数组
OSPEVENT (EV_CTRL_ALLNAME_RSP			 , INNER_CTRL_ENTRY + 24);
// 终端加入会议				| TTERLABEL
OSPEVENT (EV_CTRL_TERJOINED_IND			 , INNER_CTRL_ENTRY + 31);
// 终端退出会议				| TTERLABEL
OSPEVENT (EV_CTRL_TERLEFT_IND			 , INNER_CTRL_ENTRY + 32);
// 请求驱逐终端				| TTERLABEL
OSPEVENT (EV_CTRL_DROPTER_REQ			 , INNER_CTRL_ENTRY + 33);
//	驱逐终端失败指示		| NULL
OSPEVENT (EV_CTRL_DROPTERREJECT_IND		 , INNER_CTRL_ENTRY + 34);

// 本端被选看				| NULL				| mc->ter
OSPEVENT (EV_CTRL_SEENBYOTHER_IND		 , INNER_CTRL_ENTRY + 36);
// 本端被取消选看			| NULL				| mc->ter
OSPEVENT (EV_CTRL_CANCELSEENBYOTHER_IND	 , INNER_CTRL_ENTRY + 37);

// 广播终端命令				| TTERLABEL			| ter->mc
OSPEVENT (EV_CTRL_BROADCAST_CMD			 , INNER_CTRL_ENTRY + 41);
// 广播终端请求				| TTERLABEL			| ter->mc
OSPEVENT (EV_CTRL_BROADCAST_REQ			 , INNER_CTRL_ENTRY + 42);
// 广播终端应答				| 1BYTE,CtrlResult
OSPEVENT (EV_CTRL_BROADCAST_RSP			 , INNER_CTRL_ENTRY + 43);
// 取消广播终端命令			| NULL
OSPEVENT (EV_CTRL_CANCELBROADCAST_CMD	 , INNER_CTRL_ENTRY + 44);

// 选看终端命令				| TTERLABEL
OSPEVENT (EV_CTRL_SENDTHISTER_CMD		 , INNER_CTRL_ENTRY + 46);
// 选看终端请求				| TTERLABEL
OSPEVENT (EV_CTRL_SENDTHISTER_REQ		 , INNER_CTRL_ENTRY + 47);
// 选看终端应答				| 1BYTE,CtrlResult
OSPEVENT (EV_CTRL_SENDTHISTER_RSP		 , INNER_CTRL_ENTRY + 48);
// 取消选看终端命令			| NULL
OSPEVENT (EV_CTRL_CANCELSENDTHISTER_CMD  , INNER_CTRL_ENTRY + 49);
// 主席选看终端				| TTERLABEL + 1Byte(type_audio|type_video|type_av)
OSPEVENT (EV_CTRL_CHAIRVIEW_CMD			 , INNER_CTRL_ENTRY + 50);

// 被广播指示				| NULL
OSPEVENT (EV_CTRL_SEENBYALL_IND			 , INNER_CTRL_ENTRY + 51);	
// 取消被广播指示			| NULL
OSPEVENT (EV_CTRL_CANCELSEENBYALL_IND	 , INNER_CTRL_ENTRY + 52);
// 视频源指示				| TTERLABEL
OSPEVENT (EV_CTRL_YOUARESEEING_IND		 , INNER_CTRL_ENTRY + 53);

// 申请发言请求				| NULL
OSPEVENT (EV_CTRL_APPLYSPEAK_REQ		 , INNER_CTRL_ENTRY + 56);
// 申请发言指示				| TTERLABEL
OSPEVENT (EV_CTRL_APPLYSPEAK_IND		 , INNER_CTRL_ENTRY + 57);

// 主席令牌请求				| 1BYTE,CTRL_CHAIR_GRAB/CTRL_CHAIR_RELEASE
OSPEVENT (EV_CTRL_CHAIRTOKEN_REQ		 , INNER_CTRL_ENTRY + 58);
// 主席令牌应答				| 1BYTE,
OSPEVENT (EV_CTRL_CHAIRTOKEN_RSP		 , INNER_CTRL_ENTRY + 59);
// 询问谁是主席				| NULL
OSPEVENT (EV_CTRL_WHOISCHAIR_REQ		 , INNER_CTRL_ENTRY + 60);
// 回答谁是主席				| TTERLABEL
OSPEVENT (EV_CTRL_WHOISCHAIR_RSP		 , INNER_CTRL_ENTRY + 61);
// 撤消主席指示				| NULL
OSPEVENT (EV_CTRL_WITHDRAWCHAIR_IND		 , INNER_CTRL_ENTRY + 62);
// 发言人指示				| TTERLABEL
OSPEVENT (EV_CTRL_SPEAKER_IND			 , INNER_CTRL_ENTRY + 63);

// 结束会议命令				| NULL
OSPEVENT (EV_CTRL_DROPCONF_CMD			 , INNER_CTRL_ENTRY + 66);	
// 检查对端是否Alive		| INT(最大时延值,单位:ms)
OSPEVENT (EV_CTRL_CHECKPEERALIVE_IND	 , INNER_CTRL_ENTRY + 71);	

///// 自定义消息 /////

// 其它终端申请主席			| TTERLABEL
OSPEVENT (EV_CTRL_CHAIRAPPLY_IND		 , INNER_CTRL_ENTRY + 81);
// 主席令牌转移				| TTERLABEL
OSPEVENT (EV_CTRL_CHAIRTRANSFER_REQ		 , INNER_CTRL_ENTRY + 82);
// 主席邀请终端入会请求		| u32(IP)/E164别名
OSPEVENT (EV_CTRL_CHAIRINVITE_REQ		 , INNER_CTRL_ENTRY + 83);
// 主席邀请终端入会失败		| u32(IP)
OSPEVENT (EV_CTRL_INVITEFAIL_IND		 , INNER_CTRL_ENTRY + 84);
// 远端静音命令				| TTERLABEL(dst) + 1BYTE(turn_on/turn_off)
OSPEVENT (EV_CTRL_MAKETERQUIET_CMD		 , INNER_CTRL_ENTRY + 85);
// 远端哑音命令				| TTERLABEL(dst) + 1BYTE(turn_on/turn_off)
OSPEVENT (EV_CTRL_MAKETERMUTE_CMD		 , INNER_CTRL_ENTRY + 86);
// 开始轮询命令				| 类型(1Byte,广播/选看) + 时间间隔(1Byte) + 终端个数(1Byte) + 列表(TTERLABEL数组)
OSPEVENT (EV_CTRL_STARTPOLL_CMD 		 , INNER_CTRL_ENTRY + 87);
// 结束轮询命令				| NULL
OSPEVENT (EV_CTRL_STOPPOLL_CMD			 , INNER_CTRL_ENTRY + 88);
// 暂停轮询命令				| NULL
OSPEVENT (EV_CTRL_PAUSEPOLL_CMD			 , INNER_CTRL_ENTRY + 89);
// 恢复轮询命令				| NULL
OSPEVENT (EV_CTRL_RESUMEPOLL_CMD		 , INNER_CTRL_ENTRY + 90);
// 查询轮询参数				| NULL
OSPEVENT (EV_CTRL_POLLPARAM_REQ			 , INNER_CTRL_ENTRY + 91);
// 轮询参数应答				| 若没有轮询 + NULL
//							| 若正在轮询 + 类型(1Byte,广播/选看) + 模式(1Byte,A/V/Both) + 时间间隔(1Byte) + 终端个数(1Byte) + 列表(TTERLABEL数组)
OSPEVENT (EV_CTRL_POLLPARAM_RSP			 , INNER_CTRL_ENTRY + 92);
// 轮询状态指示				| 
OSPEVENT (EV_CTRL_POLLPARAM_IND			 , INNER_CTRL_ENTRY + 93);
// 主席终端请求其他终端的终端状态	|TTERLABEL
OSPEVENT (EV_CTRL_MTSTATUS_REQ			 , INNER_CTRL_ENTRY + 94);
// 请求其他终端的终端状态应答		|TTERLABEL + _TTERSTATUS
OSPEVENT (EV_CTRL_MTSTATUS_RSP			 , INNER_CTRL_ENTRY + 95);


// 发送短消息				| TROLLMSG
OSPEVENT (EV_CTRL_SMS_IND				 , INNER_CTRL_ENTRY + 96);
// 远遥命令					| TTERLABEL(src) + TTERLABEL(dst) + TFeccStruct
OSPEVENT (EV_CTRL_FECC_CMD				 , INNER_CTRL_ENTRY + 97);
// 终端状态请求				| NULL
OSPEVENT (EV_CTRL_TERSTATUS_REQ			 , INNER_CTRL_ENTRY + 98);
// 终端状态应答				| _TTERSTATUS
OSPEVENT (EV_CTRL_TERSTATUS_RSP			 , INNER_CTRL_ENTRY + 99);

// 会议信息请求				| NULL					UI->MTCTRL
OSPEVENT (EV_CTRL_CONFINFO_REQ			 , INNER_CTRL_ENTRY + 101);
// 会议信息应答				| 
//													MTCTRL->UI
OSPEVENT (EV_CTRL_CONFINFO_RSP			 , INNER_CTRL_ENTRY + 102);
// 会议即将结束提示			| u16(单位:分钟)		MTCTRL->UI
OSPEVENT (EV_CTRL_CONFWILLEND_IND		 , INNER_CTRL_ENTRY + 103);
// 会议延长请求				| u16(单位:分钟)		UI->MTCTRL
OSPEVENT (EV_CTRL_DELAYCONF_REQ			 , INNER_CTRL_ENTRY + 104);
// 会议延长应答				| 1BYTE	1:OK 0:FAIL		MTCTRL->UI
OSPEVENT (EV_CTRL_DELAYCONF_RSP			 , INNER_CTRL_ENTRY + 105);

// 语音激励请求				| 1BYTE(MT_START/MT_STOP)	| chair->MC
OSPEVENT (EV_CTRL_VAC_REQ				 , INNER_CTRL_ENTRY + 111);
// 语音激励应答				| 1BYTE(MT_START/MT_STOP) + 1BYTE(ctrl_granted/ctrl_denied)		| MC->chair
OSPEVENT (EV_CTRL_VAC_RSP				 , INNER_CTRL_ENTRY + 112);
// 讨论模式请求				| 1BYTE(MT_START)+1BYTE(最大终端个数)/1BYTE(MT_STOP)	| chair->MC
OSPEVENT (EV_CTRL_DISCUSS_REQ			 , INNER_CTRL_ENTRY + 113);
// 讨论模式应答				| 1BYTE(MT_START/MT_STOP) + 1BYTE(ctrl_granted/ctrl_denied)		| MC->chair
OSPEVENT (EV_CTRL_DISCUSS_RSP			 , INNER_CTRL_ENTRY + 114);
// 视频复合请求				| MT_START(1BYTE)+TVMPParam|MT_STOP(1BYTE)	| ter->MC(主席才可发此命令)
OSPEVENT (EV_CTRL_VMP_REQ				 , INNER_CTRL_ENTRY + 115);
// 视频复合应答				| 1BYTE(MT_START/MT_STOP) + 1BYTE(ctrl_granted/ctrl_denied)		| MC->ter
OSPEVENT (EV_CTRL_VMP_RSP				 , INNER_CTRL_ENTRY + 116);
// 设置视频复合参数请求		| TVMPParam								| ter->MC(主席才可发此命令)
OSPEVENT (EV_CTRL_VMPSETPARAM_REQ		 , INNER_CTRL_ENTRY + 117);
// 设置视频复合参数应答		| 1BYTE(ctrl_granted/ctrl_denied)		| MC->ter
OSPEVENT (EV_CTRL_VMPSETPARAM_RSP		 , INNER_CTRL_ENTRY + 118);
// 获取视频复合参数请求		| NULL									| ter->MC(主席才可发此命令)
OSPEVENT (EV_CTRL_VMPGETPARAM_REQ		 , INNER_CTRL_ENTRY + 119);
// 获取视频复合参数应答		| TVMPParam								| MC->ter
OSPEVENT (EV_CTRL_VMPGETPARAM_RSP		 , INNER_CTRL_ENTRY + 120);
// 视频源指示				|以\0结束的字符串						| MC->ter
OSPEVENT (EV_CTRL_SRCNAME_IND			 , INNER_CTRL_ENTRY + 121);



/************************会 议 监 控************************/

// 开始监控请求				| <m,t>									| ter->MC
OSPEVENT (EV_CTRL_STARTMONITOR_REQ		 , INNER_CTRL_ENTRY + 126);
// 开始监控应答				| <m,t> + TIPADDR(接收地址,如果失败ip为0)	| MC->ter
OSPEVENT (EV_CTRL_STARTMONITOR_RSP		 , INNER_CTRL_ENTRY + 127);
// 停止监控命令				| <m,t>									| ter->MC
OSPEVENT (EV_CTRL_STOPMONITOR_CMD		 , INNER_CTRL_ENTRY + 128);

/************************矩 阵 控 制************************/

// MCU请求矩阵当前配置		| 1BYTE(MT_AUDIO|MT_VIDEO|MT_AV)		| MC->ter
OSPEVENT (EV_CTRL_MATRIXINFO_REQ		 , INNER_CTRL_ENTRY + 131);
// 终端上报矩阵当前配置		| 1BYTE(MT_AUDIO|MT_VIDEO|MT_AV) + _TMATRIXINFO(如果是MT_AV则为数组,A+V) | ter->MC
OSPEVENT (EV_CTRL_MATRIXINFO_IND		 , INNER_CTRL_ENTRY + 132);
// MCU配置终端矩阵命令		| 1BYTE(MT_AUDIO|MT_VIDEO|MT_AV) + _TMATRIXPORT(输出端口) + _TMATRIXPORT(输入端口) | MC->ter
OSPEVENT (EV_CTRL_MATRIXCFG_CMD			 , INNER_CTRL_ENTRY + 133);
// MCU请求矩阵方案			| 1BYTE(MT_AUDIO|MT_VIDEO|MT_AV)		| MC->ter
OSPEVENT (EV_CTRL_MATRIXSCHEME_REQ		 , INNER_CTRL_ENTRY + 134);
// 终端上报矩阵方案			| TMATRIXSCHEME					| ter->MC
OSPEVENT (EV_CTRL_MATRIXSCHEM_IND		 , INNER_CTRL_ENTRY + 135);
// MCU载入方案				| TMATRIXSCHEME					| MC->ter
OSPEVENT (EV_CTRL_LOADSCHEME_CMD			 , INNER_CTRL_ENTRY + 136);
// MCU保存方案				| TMATRIXSCHEME					| MC->ter
OSPEVENT (EV_CTRL_SAVESCHEME_CMD			 , INNER_CTRL_ENTRY + 137);
// MCU配置终端矩阵为默认值	| 1BYTE(MT_AUDIO|MT_VIDEO|MT_AV)		| MC->ter
OSPEVENT (EV_CTRL_DEFAULTCFG_CMD			 , INNER_CTRL_ENTRY + 138);


///////////////////////////// RAS消息 ///////////////////////////////

// GK注册请求				| TALIASADDR(本端别名) + TNETADDR(GK地址)						| MTCTRL->STACKOUT
OSPEVENT ( EV_RAS_REG_REQ				 , INNER_RAS_ENTRY + 1);
// GK注销请求				| NULL									| STACKIN->MTCTRL
OSPEVENT ( EV_RAS_UNREG_REQ				 , INNER_RAS_ENTRY + 2);
// 终端在GK的状态指示		| 1BYTE(MT_OK:已注册 MT_ERR:未注册)		| STACKIN->MTCTRL
OSPEVENT ( EV_RAS_STAT_IND				 , INNER_RAS_ENTRY + 3);
// GK鉴权确认		| 4BYTE带宽值		| STACKIN->MTCTRL
OSPEVENT ( EV_RAS_ACF_RSP				 , INNER_RAS_ENTRY + 4);


	
/////////////////////////////杂项消息/////////////////////////////////





/////////////////////////////内置MC消息//////////////////////////////

//激活MC消息					| MC_ACTIVE/MC_INACTIVE		| MtCtrl -> MTMC   				 
OSPEVENT ( EV_MC_SETACTIVE_CMD				, 	INNER_MC_ENTRY + 1 );
//设置会议扩充模式				| MC_NEWCONF	MC_NEWCONF_ALWAYS/MC_NEWCONF_NEVER/MC_NEWCONF_ASK
//												| MtCtrl -> MTMC  
OSPEVENT ( EV_MC_NEWCONFMODE_CMD	, 			INNER_MC_ENTRY + 2 );
//上级会议信息通知	            | TMCRegConf	| MTCtrl->MTMC			 
OSPEVENT ( EV_MC_REGCONF_IND	, 				INNER_MC_ENTRY + 3 );
//内置MC分配RTP/RTCP端口号		| TMCResetAddr  | MTMC->MtCtrl    
OSPEVENT ( EV_MC_RESETMEDIAADDR_CMD	,			INNER_MC_ENTRY + 4 );
// 扩展会议通知					| NULL			| MtCtrl->MTMC
OSPEVENT ( EV_MC_HOCACTIVE_IND		,			INNER_MC_ENTRY + 5 );
// 扩展会议状态通知通知			| 1 BYTE(MC_CONF_NONE/MC_CONF_SUPER/MC_CONF_CASCADE)
//								| MTMC->MtCtrl
OSPEVENT ( EV_MC_HOCSTATUS_IND		,			INNER_MC_ENTRY + 6 );
// 级联会议开始请求				|  TNETADDR(对端地址) | MTMC->MtCtrl
OSPEVENT ( EV_MC_CONFCASCADE_REQ	,			INNER_MC_ENTRY + 7 );
// 级联会议请求应答				| 1 BYTE(MT_ENABLE/MT_DISABLE)	| MtCtrl->MTMC
OSPEVENT ( EV_MC_CONFCASCADE_RSP	,			INNER_MC_ENTRY + 8 );

/*
// 邀请终端						| _TDIALPARAM	| UI->MTMC
OSPEVENT (EV_MC_MAKECALL_CMD			 ,		INNER_MC_ENTRY + 5);
// 呼叫到来						| _TDIALPARAM	| MTMC->UI
OSPEVENT (EV_MC_CALLINCOMING_IND		 ,		INNER_MC_ENTRY + 6);	
// 呼叫应答						| NULL			| UI->MTMC
OSPEVENT (EV_MC_ANSWERCALL_CMD		 ,			INNER_MC_ENTRY + 7);
// 连接状态						| 1BYTE,CALL_LINKING(连接中)/CALL_LINKED(已连接)/CALL_UNLINK(连接断开)	| MTMC->UI
OSPEVENT (EV_MC_LINKSTATE_IND			 ,		INNER_MC_ENTRY + 8);
// 挂断呼叫						| NULL			| UI->MTMC
OSPEVENT (EV_MC_HANGUP_CMD			 ,			INNER_MC_ENTRY + 9);
*/


///////////////////////////////////////Sat相关消息///////////////////////////////////////
//初始化协议栈					| TSatInitParam				|mcu->ter 
OSPEVENT (EV_SAT_INITSTACK_IND			 ,			EV_OUTEROSP_BGN + 1);
//会议列表消息通知				| TSatConfInfo结构数组		|mcu->ter
OSPEVENT (EV_SAT_CONFLIST_IND			 ,			EV_OUTEROSP_BGN + 2);
//入会议通知					| 1 BYTE 会议类型 1= 多点会议 0=点对点会议		|mcu->ter
//OSPEVENT (EV_SAT_JIONCONF_IND			     ,		EV_OUTEROSP_BGN + 3);
//退出会议通知					| 1 BYTE 退回原因			|mcu->ter
//OSPEVENT (EV_SAT_QUITCONF_IND			     ,		EV_OUTEROSP_BGN + 4);
//终端列表通知					| TSatMtInfo 结构数组		|mcu->ter
OSPEVENT (EV_SAT_MTLIST_IND			     ,			EV_OUTEROSP_BGN + 5);
//终端成为主席通知				| NULL						|muc->ter
OSPEVENT (EV_SAT_SPECCHAIRMAN_IND			     ,	EV_OUTEROSP_BGN + 6);
//终端释放主席通知				| NULL						|muc->ter
OSPEVENT (EV_SAT_CANCELCHAIRMAN_IND			     ,	EV_OUTEROSP_BGN + 7);
//本终端为发言人通知			| NULL						|muc->ter
OSPEVENT ( EV_SAT_SPECSPEAKER_IND			     ,	EV_OUTEROSP_BGN + 8);
//本终端取消发言人通知			| NULL						|muc->ter
OSPEVENT ( EV_SAT_CANCELSPEAKER_IND			     ,	EV_OUTEROSP_BGN + 9);
//设置视频码率					|TSatBitrate				|muc->ter
OSPEVENT ( EV_SAT_SETBITRATE_CMD			     ,	EV_OUTEROSP_BGN + 10);
//哑音消息						|1BYTE 1=哑音 0=停止哑音	|muc->ter
OSPEVENT ( EV_SAT_MUTE_CMD			     ,			EV_OUTEROSP_BGN + 11);
//静音消息						|1BYTE 1=静音 0=停止静音	|muc->ter
OSPEVENT ( EV_SAT_QUIET_CMD			     ,			EV_OUTEROSP_BGN + 12);
//回传通道状态指示消息			|1BYTE 1=获取回传通道 0=没有回传通道	|muc->ter
OSPEVENT ( EV_SAT_UPLOAD_IND			     ,		EV_OUTEROSP_BGN + 13);
//其他终端申请主席				| 终端ID TSatMtId			| mcu->ter
OSPEVENT ( EV_SAT_OTHERAPPLYCHAIR_CMD			  , EV_OUTEROSP_BGN + 14);
//其他终端申请发言				| 终端ID TSatMtId			| mcu->ter
OSPEVENT ( EV_SAT_OTHERAPPLYSPEAK_CMD			  , EV_OUTEROSP_BGN + 15);
//请求加入会议					| 会议索引号(u8)(0: 加入指示) | ter->mcu
//OSPEVENT ( EV_SAT_JIONCONF_CMD			     ,		EV_OUTEROSP_BGN + 16);
//申请主席						| NULL					| ter->mcu
OSPEVENT ( EV_SAT_APPLYCHAIRMAN_CMD		     ,		EV_OUTEROSP_BGN + 17);
//申请发言						| NULL					| ter->mcu
OSPEVENT ( EV_SAT_APPLYSPEAKER_CMD			     ,	EV_OUTEROSP_BGN + 18);
//指定发言人					| 终端ID(u16)			| ter->mcu
OSPEVENT ( EV_SAT_SPECSPEAKER_CMD			     ,	EV_OUTEROSP_BGN + 19);
//取消发言人					| 终端ID(u16)			| ter->mcu
OSPEVENT ( EV_SAT_CANCEALSPEAKER_CMD			  , EV_OUTEROSP_BGN + 20);
//指定主席						| 终端ID(u16)			| ter->mcu
OSPEVENT ( EV_SAT_SPECCHAIRMAN_CMD			     ,	EV_OUTEROSP_BGN + 21);
//取消主席						| NULL					| ter->mcu
OSPEVENT ( EV_SAT_CANCEALCHAIRMAN_CMD			  , EV_OUTEROSP_BGN + 22);
//短消息通知					|TSatSMS        		| mcu->ter
OSPEVENT ( EV_SAT_SMS_IND   			     ,		EV_OUTEROSP_BGN + 23);
// 关键帧请求						|NULL					| mcu->ter
OSPEVENT ( EV_SAT_VIDEOUPDATE_CMD   			     ,	EV_OUTEROSP_BGN + 24);
//结束会议						|NULL					| ter->mcu
OSPEVENT ( EV_SAT_DROPCONF_CMD   			     ,	EV_OUTEROSP_BGN + 25);
//等待呼叫应答超时				|NULL									| mcu->ter
OSPEVENT ( EV_SAT_WAITQUITCONFTIMEOUT_IND 				,EV_OUTEROSP_BGN + 26);

//当前观看视频源				|TSatMtId						| mcu->ter
OSPEVENT ( EV_SAT_YOUARESEEING_IND 			     ,	EV_OUTEROSP_BGN + 27);
//当前正在收听的音频源			|TSatMtId						| mcu->ter
OSPEVENT ( EV_SAT_YOUARELISTENING_IND 			   ,EV_OUTEROSP_BGN + 28);
//系统密钥						|长度为16的u8数组						| mcu->ter
OSPEVENT ( EV_SAT_SYSPWD_IND 						,EV_OUTEROSP_BGN + 29);
//远遥命令						|TFeccCmd						        | mcu->ter
OSPEVENT ( EV_SAT_FECC_CMD 						    ,EV_OUTEROSP_BGN + 30);
//mcu信息更新					|TSatConfStatus							| mcu->ter
OSPEVENT ( EV_SAT_CONFINFO_IND 						,EV_OUTEROSP_BGN + 31);
//终端业务通知接收加入会议邀请	|NULL									| mcu->ter		
OSPEVENT ( EV_SAT_ACCEPTCONFINVITE_IND 				,EV_OUTEROSP_BGN + 32);
//等待呼叫应答超时				|NULL									| mcu->ter
OSPEVENT ( EV_SAT_WAITCALLTIMEOUT_IND 				,EV_OUTEROSP_BGN + 33);
//终端别名指示					|以/0结束的字符串						| mcu->ter
OSPEVENT ( EV_SAT_MTNAME_IND 						,EV_OUTEROSP_BGN + 34);

//卫星实体上线					|NULL						| ter->mcu
OSPEVENT ( EV_ENTITY_SAT_ONLINE_IND 						,EV_OUTEROSP_BGN + 35);

//卫星实体掉线					|NULL						| ter->mcu
OSPEVENT ( EV_ENTITY_SAT_OFFLINE_IND 						,EV_OUTEROSP_BGN + 36);

//设置发送地址                  |
OSPEVENT(  EV_SAT_ENTITY_SETSENDADDR_CMD    				,EV_OUTEROSP_BGN + 37);

//画面复合状态                  |u8(=0 停止 1=开始)＋TSatVMPStatus  | mcu->ter
OSPEVENT(  EV_SAT_VMPSTATUS_IND    				    ,EV_OUTEROSP_BGN + 38);


///////////////////////////////////////////////////////////////
//卫星系统接收到MCU发来的消息通知 |卫星定义消息
OSPEVENT(  EV_SAT_INNER_MCUMSG_IND    				,EV_OUTEROSP_BGN + 39);

//MT与卫星之间断链指示            |NULL
OSPEVENT(  EV_SAT_INNER_DISCONNECT_IND				,EV_OUTEROSP_BGN + 40);

//MCU 开始工作             |NULL
OSPEVENT(  EV_SAT_INNER_CONNECTED_IND				,EV_OUTEROSP_BGN + 41);

//定时发送消息                    |NULL
OSPEVENT(  EV_SAT_INNER_SENDTIMER_IND				,EV_OUTEROSP_BGN + 42);

//会议信息更新超时消息            |NULL
OSPEVENT(  EV_SAT_INNER_CONFINFOTIMEOUT_IND  		,EV_OUTEROSP_BGN + 43);

//点对点等待接受呼叫定时消息      |NULL
OSPEVENT(  EV_SAT_P2P_WAITACCEPT_TIMER  	    	,EV_OUTEROSP_BGN + 44);

//点对点ROUNDTRIP 定时消息      |NULL
OSPEVENT(  EV_SAT_P2P_ROUNDTRIP_TIMER  	    	,EV_OUTEROSP_BGN + 45);
 
//等待进入多点会议超时
OSPEVENT ( EV_SAT_INNER_WAITMCCTIMEOUT_IND		 ,EV_OUTEROSP_BGN + 46);

//等待进入点对点呼完毕超时
OSPEVENT ( EV_SAT_INNER_WAITP2PCALLCOMPLETE_IND		 ,EV_OUTEROSP_BGN + 47);

//Modem 检测管理
OSPEVENT ( EV_SAT_INNER_MODEMMANAGER_TIMER		 ,EV_OUTEROSP_BGN + 48);


//通知上层topo信息指示            |TSatMtInfo数组
OSPEVENT(  EV_SAT_TOPO_IND				    ,EV_OUTEROSP_BGN + 50);

//入会议通知					| TSatConfFormat		|mcu->ter
OSPEVENT (EV_SAT_INCONF_IND			        ,EV_OUTEROSP_BGN + 51);

//请求加入会议					| 会议索引号(u8)(0: 加入指示) | ter->mcu
OSPEVENT ( EV_SAT_APPLYJOINCONF_CMD		     ,EV_OUTEROSP_BGN + 52);

//拥有回传终端列表				| TSatMtList | mcu->ter
OSPEVENT ( EV_SAT_CANSENDMT_IND		         ,EV_OUTEROSP_BGN + 53);

//创建会议                      |TSatConfFormat+TSatMtList |ter->mcu
OSPEVENT ( EV_SAT_CREATECONF_CMD		     ,EV_OUTEROSP_BGN + 54);

//退出会议请求                  |NULL        |ter->mcu
OSPEVENT ( EV_SAT_LEAVECONF_CMD		     ,EV_OUTEROSP_BGN + 55);

//退出会议指示                  |NULL        |ter->mcu
OSPEVENT ( EV_SAT_LEAVECONF_IND		     ,EV_OUTEROSP_BGN + 56);

//结束会议                      |NULL        |ter->mcu
OSPEVENT ( EV_SAT_QUITCONF_CMD		     ,EV_OUTEROSP_BGN + 57);

//会议终端列表              		| TSatMtList | mcu->ter
OSPEVENT ( EV_SAT_CONFMTLIST_IND		         ,EV_OUTEROSP_BGN + 62);


//活动(已签到)终端列表				| TSatMtList | mcu->ter
OSPEVENT ( EV_SAT_ACTIVEMT_IND		         ,EV_OUTEROSP_BGN + 63);

//点对点发起呼叫
//                   -ITSatMtId  发起呼叫者ID
//                   +ITSatTransAddr 发起者接收地址
//                   +TSatConfFormat 点对点会议格式 
OSPEVENT ( EV_SAT_P2P_CALL_CMD		         ,EV_OUTEROSP_BGN + 64);

//点对点接收呼叫
//                   -ITSatMtId  接收呼叫者ID
//                   +ITSatTransAddr 接收地址
OSPEVENT ( EV_SAT_P2P_ACCEPT_IND		     ,EV_OUTEROSP_BGN + 65);

//点对点呼叫确认结束   |NULL
OSPEVENT ( EV_SAT_P2P_CALL_COMPLETE_IND		 ,EV_OUTEROSP_BGN + 66);

//点对点TROUNDTRIP     |NULL
OSPEVENT ( EV_SAT_P2P_ROUNDTRIP		 ,EV_OUTEROSP_BGN + 67);

//点对点会议结束       |NULL
OSPEVENT ( EV_SAT_P2P_RELEASE_CMD		 ,EV_OUTEROSP_BGN + 68);


//适配器会议定时检测消息      |NULL
OSPEVENT ( EV_SATH323ADP_CHECKCONFTIMER		 ,EV_OUTEROSP_BGN + 69);

//画面复合状态                  |TSatVMPStatus  | mcu->ter
OSPEVENT(  EV_SAT_SETVMP_CMD    				    ,EV_OUTEROSP_BGN + 70);

//强制关键帧定时器
OSPEVENT(  EV_SAT_IFRAME_TIMER    				    ,EV_OUTEROSP_BGN + 71);

//link setup信息提示		|ITLinkSetup |satinterface->satadapter
OSPEVENT( EV_SAT_NOTIFY_LINKSETUP	,EV_OUTEROSP_BGN + 72);
//双流
OSPEVENT( EV_SAT_OPEN_DUALCHAN	,EV_OUTEROSP_BGN + 73);

OSPEVENT( EV_SAT_OPEN_DUALCHAN_RSP , EV_OUTEROSP_BGN + 74);

OSPEVENT( EV_SAT_OPEN_DUALCHAN_TIMEOUT , EV_OUTEROSP_BGN + 75);

OSPEVENT( EV_SAT_DUAL_STREAM_IND , EV_OUTEROSP_BGN + 76 );
//==========================================================================================
//									外部消息定义
//==========================================================================================

///////////////////////////////会议控制消息//////////////////////////////////

// 发起呼叫					| _TDIALPARAM	| UI->MTCTRL
OSPEVENT (EV_CONF_MAKECALL_CMD			 , OUTER_CONF_ENTRY + 1);
// 呼叫到来					| _TDIALPARAM(对于320终端,没有参数)	| MTCTRL->UI 
OSPEVENT (EV_CONF_CALLINCOMING_IND		 , OUTER_CONF_ENTRY + 2);	
// 呼叫应答					| NULL			| UI->MTCTRL
OSPEVENT (EV_CONF_ANSWERCALL_CMD		 , OUTER_CONF_ENTRY + 3);
// 连接状态					|				| MTCTRL->UI	
// 参数说明: 连接中:1BYTE,CALL_LINKING
//			 已连接:1BYTE,CALL_LINKED + 对端名称
//			 连接断开:1BYTE,CALL_UNLINK 			
OSPEVENT (EV_CONF_LINKSTATE_IND			 , OUTER_CONF_ENTRY + 4);
// 挂断呼叫					| NULL			| UI->MTCTRL
OSPEVENT (EV_CONF_HANGUP_CMD			 , OUTER_CONF_ENTRY + 5);
// 拒绝新呼叫(已经在呼叫中)	| NULL			| UI->MTCTRL
OSPEVENT (EV_CONF_REJECTCALL_CMD		 , OUTER_CONF_ENTRY + 6);
// 扩展会议命令				| NULL			| UI->MTCTRL
OSPEVENT (EV_CONF_ADHOC_CMD				 , OUTER_CONF_ENTRY + 7);
// 选择会议列表请求			| _TCONFINFO数组| MTCTRL->UI
OSPEVENT (EV_CONF_LISTCHOICE_REQ		 , OUTER_CONF_ENTRY + 8);
// 选择会议列表应答			| confId(16 BYTE)	| UI->MTCTRL
OSPEVENT (EV_CONF_LISTCHOICE_RSP		 , OUTER_CONF_ENTRY + 9);

// 向GK发起注册请求			| u32(GK IP地址,网络序)	| UI->MTCTRL
//OSPEVENT (EV_CONF_RASREG_REQ			 , OUTER_CONF_ENTRY + 11);
// 向GK发起注销请求			| NULL						| UI->MTCTRL
//OSPEVENT (EV_CONF_RASUNREG_REQ			 , OUTER_CONF_ENTRY + 12);
// 终端在GK的状态指示		| 1BYTE(MT_OK:已注册 MT_ERR:未注册)	| STACKIN->MTCTRL
OSPEVENT (EV_CONF_RASSTAT_IND			 , OUTER_CONF_ENTRY + 13);

// 主从结果通知				| 1BYTE(MT_MASTER|MT_SLAVER) | MTCTRL->UI
OSPEVENT (EV_CONF_MSDE_IND				 , OUTER_CONF_ENTRY + 15);
// 两点会议开始指示			| NULL			| MTCTRL->UI
OSPEVENT (EV_CONF_P2PSTART_IND			 , OUTER_CONF_ENTRY + 16);
// 多点会议开始指示			| NULL			| MTCTRL->UI
OSPEVENT (EV_CONF_MCCSTART_IND			 , OUTER_CONF_ENTRY + 17);

// MCU要求输入会议密码		| NULL			| MTCTRL->UI
OSPEVENT (EV_CONF_H243PWD_REQ			 , OUTER_CONF_ENTRY + 18);
// MT回答会议密码			| password(char*) 最大长度MT_PWD_LEN | MTCTRL->UI
OSPEVENT (EV_CONF_H243PWD_RSP			 , OUTER_CONF_ENTRY + 19);

// 本端编号指示				| <m,t>			| MTCTRL->UI
OSPEVENT (EV_CONF_LABELASSIGN_IND		 , OUTER_CONF_ENTRY + 21);	
// 终端加入					| <m,t>			| MTCTRL->UI
OSPEVENT (EV_CONF_TERJOINED_IND			 , OUTER_CONF_ENTRY + 22);	
// 终端退出					| <m,t>			| MTCTRL->UI
OSPEVENT (EV_CONF_TERLEFT_IND			 , OUTER_CONF_ENTRY + 23);	
// 强制终端退出				| <m,t>			| UI->MTCTRL
OSPEVENT (EV_CONF_DROPTER_CMD			 , OUTER_CONF_ENTRY + 24);	
// 强制终端退出拒绝			| NULL			| MTCTRL->UI
OSPEVENT (EV_CONF_DROPREJECT_IND		 , OUTER_CONF_ENTRY + 25);	

// 终端列表更新				| TMTINFO的数组	| MTCTRL->UI
OSPEVENT (EV_CONF_TERLIST_IND			 , OUTER_CONF_ENTRY + 26);	
// 申请发言请求				| NULL			| UI->MTCTRL
OSPEVENT (EV_CONF_APPLYSPEAK_REQ		 , OUTER_CONF_ENTRY + 27);
// 申请发言指示				| <m,t>			| MTCTRL->UI
OSPEVENT (EV_CONF_APPLYSPEAK_IND		 , OUTER_CONF_ENTRY + 28);
// 广播终端命令(主席)		| <m,t>			| UI->MTCTRL
OSPEVENT (EV_CONF_BROADCASTTER_CMD		 , OUTER_CONF_ENTRY + 29);
// 选看终端命令(主席)		| <m,t>	+ 1Byte(MT_VIDEO|MT_AUDIO|MT_AV) | UI->MTCTRL
OSPEVENT (EV_CONF_VIEWTHSITER_CMD		 , OUTER_CONF_ENTRY + 30);
// 视频源指示				| <m,t>			| MTCTRL->UI
OSPEVENT (EV_CONF_YOUARESEEING_IND		 , OUTER_CONF_ENTRY + 31);
// 本端被广播指示			| 无			| MTCTRL->UI
OSPEVENT (EV_CONF_SEENBYALL_IND			 , OUTER_CONF_ENTRY + 32);
// 本端被取消广播指示		| 无			| MTCTRL->UI
OSPEVENT (EV_CONF_CANCELSEENBYALL_IND	 , OUTER_CONF_ENTRY + 33);
// 广播终端请求				| <m,t>			| UI->MTCTRL
OSPEVENT (EV_CONF_BROADCASTTER_REQ		 , OUTER_CONF_ENTRY + 34);
// 广播终端应答				| 1BYTE(MT_OK:成功 MT_ERR:失败)	| MTCTRL->UI
OSPEVENT (EV_CONF_BROADCASTTER_RSP		 , OUTER_CONF_ENTRY + 35);
// 选看终端请求				| <m,t>			| UI->MTCTRL
OSPEVENT (EV_CONF_VIEWTHISTER_REQ		 , OUTER_CONF_ENTRY + 36);
// 选看终端应答				| 1BYTE(MT_OK:成功 MT_ERR:失败)	| MTCTRL->UI
OSPEVENT (EV_CONF_VIEWTHISTER_RSP		 , OUTER_CONF_ENTRY + 37);
// 取消选看					| NULL			| UI->MTCTRL
OSPEVENT (EV_CONF_STOPVIEWTHISTER_CMD	 , OUTER_CONF_ENTRY + 38);
// 取消发言					| NULL			| UI->MTCTRL
OSPEVENT (EV_CONF_STOPBROADCASTTER_CMD	 , OUTER_CONF_ENTRY + 39);
// 请求终端列表				| NULL			| UI->MTCTRL
OSPEVENT (EV_CONF_TERLIST_REQ			 , OUTER_CONF_ENTRY + 40);


// 轮询终端					| 类型(1Byte,CTRL_POLL_VCB:广播/CTRL_POLL_VCS:选看) + 
//							| 媒体类型(1Byte,MT_AUDIO/MT_VIDEO/MT_AV) +
//							| 时间间隔(1Byte) + 
//							| 终端个数(1BYTE) + 轮询的终端列表(<m,t>数组)	| UI->MTCTRL
OSPEVENT (EV_CONF_STARTPOLL_CMD			 , OUTER_CONF_ENTRY + 41);
// 停止轮询					| NULL			| UI->MTCTRL
OSPEVENT (EV_CONF_STOPPOLL_CMD			 , OUTER_CONF_ENTRY + 42);
// 暂停轮询命令				| NULL
OSPEVENT (EV_CONF_PAUSEPOLL_CMD			 , OUTER_CONF_ENTRY + 43);
// 恢复轮询命令				| NULL
OSPEVENT (EV_CONF_RESUMEPOLL_CMD		 , OUTER_CONF_ENTRY + 44);
// 查询轮询参数				| NULL			| UI->MTCTRL
OSPEVENT (EV_CONF_POLLPARAM_REQ			 , OUTER_CONF_ENTRY + 45);
// 回答轮询参数				| 是否在轮询(1BYTE) + <在轮询: 轮询类型(1BYTE) +　时间间隔(1BYTE) +　终端个数(1BYTE) + 轮询列表(<m,t>数组)>	| MTCTRL->UI
OSPEVENT (EV_CONF_POLLPARAM_RSP			 , OUTER_CONF_ENTRY + 46);


// 申请主席					| NULL			| UI->MTCTRL
OSPEVENT (EV_CONF_MAKEMECHAIR_REQ		 , OUTER_CONF_ENTRY + 51);	
// 释放主席					| NULL			| UI->MTCTRL
OSPEVENT (EV_CONF_RELEASECHAIR_REQ		 , OUTER_CONF_ENTRY + 52);
// 主席操作结果				| 1BYTE(MT_OK:获得主席 MT_ERR:失去主席)	| MTCTRL->UI
OSPEVENT (EV_CONF_CHAIR_RSP				 , OUTER_CONF_ENTRY + 53);
// 询问主席					| NULL			| UI->MTCTRL
OSPEVENT (EV_CONF_CHAIRLOCATION_REQ		 , OUTER_CONF_ENTRY + 54);
// 主席指示					| <m,t>			| MTCTRL->UI
OSPEVENT (EV_CONF_CHAIR_IND				 , OUTER_CONF_ENTRY + 55);
// 发言人指示				| <m,t>			| MTCTRL->UI
OSPEVENT (EV_CONF_SPEAKER_IND			 , OUTER_CONF_ENTRY + 56);

// 其它终端申请主席			| <m,t>			| MTCTRL->UI
OSPEVENT (EV_CONF_APPLYCHAIR_IND		 , OUTER_CONF_ENTRY + 61);
// 主席令牌转移				| <m,t> 表示要转移的目的终端	| UI->MTCTRL
OSPEVENT (EV_CONF_CHAIRTRANSFER_REQ		 , OUTER_CONF_ENTRY + 62);
// 主席邀请加入请求			| _TERADDR		| UI->MTCTRL
OSPEVENT (EV_CONF_CHAIRINVITE_REQ		 , OUTER_CONF_ENTRY + 63);
// 主席邀请终端失败			| _TERADDR		| MTCTRL->UI
OSPEVENT (EV_CONF_INVITEFAILED_IND		 , OUTER_CONF_ENTRY + 64);
// 主席远端静音				| <m,t> + 1Byte(MT_ENABLE/MT_DISABLE)	| UI->MTCTRL
OSPEVENT (EV_CONF_REMOTEQUIET_CMD		 , OUTER_CONF_ENTRY + 65);
// 主席远端哑音				| <m,t> + 1Byte(MT_ENABLE/MT_DISABLE)	| UI->MTCTRL
OSPEVENT (EV_CONF_REMOTEMUTE_CMD		 , OUTER_CONF_ENTRY + 66);
// 短消息指示				| TROLLMSG	| UI->MTCTRL,MTCTRL->UI
OSPEVENT (EV_CONF_SMS_IND				 , OUTER_CONF_ENTRY + 67);
// 主席终端请求其他终端的终端状态	|TMTLABEL
OSPEVENT (EV_CONF_MTSTATUS_REQ			 , OUTER_CONF_ENTRY + 68);
// 请求其他终端的终端状态应答		|TMTLABEL + _TTERSTATUS
OSPEVENT (EV_CONF_MTSTATUS_RSP			 , OUTER_CONF_ENTRY + 69);

// 会议信息请求				| NULL			| UI->MTCTRL
OSPEVENT (EV_CONF_INFO_REQ				 , OUTER_CONF_ENTRY + 71);
// 会议信息应答				| 会议信息结构,MCU给出结构说明			| MTCTRL->UI
OSPEVENT (EV_CONF_INFO_RSP				 , OUTER_CONF_ENTRY + 72);
// 会议即将结束提示			| u16(单位:分钟)	| MTCTRL->UI
OSPEVENT (EV_CONF_END_IND				 , OUTER_CONF_ENTRY + 73);
// 会议延长请求				| u16(单位:分钟)	| UI->MTCTRL
OSPEVENT (EV_CONF_DELAY_REQ				 , OUTER_CONF_ENTRY + 74);
// 会议延长应答				| 1BYTE(MT_OK:成功 MT_ERR:失败)			| MTCTRL->UI
OSPEVENT (EV_CONF_DELAY_RSP				 , OUTER_CONF_ENTRY + 75);

// 语音激励请求				| 1BYTE(MT_START/MT_STOP)				| UI->MTCTRL(主席才可发此命令)
OSPEVENT (EV_CONF_VAC_REQ				 , OUTER_CONF_ENTRY + 76);
// 语音激励应答				| 1BYTE(MT_START/MT_STOP) + 1BYTE(MT_OK/MT_ERR)			| MTCTRL->UI
OSPEVENT (EV_CONF_VAC_RSP				 , OUTER_CONF_ENTRY + 77);
// 讨论模式请求				| 1BYTE(MT_START)+1BYTE(最大终端个数)/1BYTE(MT_STOP)	| UI->MTCTRL(主席才可发此命令)
OSPEVENT (EV_CONF_DISCUSS_REQ			 , OUTER_CONF_ENTRY + 78);
// 讨论模式应答				| 1BYTE(MT_START/MT_STOP) + 1BYTE(MT_OK/MT_ERR)			| MTCTRL->UI
OSPEVENT (EV_CONF_DISCUSS_RSP			 , OUTER_CONF_ENTRY + 79);
// 视频复合请求				| MT_START(1BYTE)+TVMPParam|MT_STOP(1BYTE)	| UI->MTCTRL(主席才可发此命令)
OSPEVENT (EV_CONF_VMP_REQ				 , OUTER_CONF_ENTRY + 80);
// 视频复合应答				| 1BYTE(MT_START/MT_STOP) + 1BYTE(MT_OK/MT_ERR)			| MTCTRL->UI
OSPEVENT (EV_CONF_VMP_RSP				 , OUTER_CONF_ENTRY + 81);
// 设置视频复合参数请求		| TVMPParam								| UI->MTCTRL(主席才可发此命令)
OSPEVENT (EV_CONF_VMPSETPARAM_REQ		 , OUTER_CONF_ENTRY + 82);
// 设置视频复合参数应答		| 1BYTE(MT_OK/MT_ERR)					| MTCTRL->UI
OSPEVENT (EV_CONF_VMPSETPARAM_RSP		 , OUTER_CONF_ENTRY + 83);
// 获取视频复合参数请求		| NULL									| UI->MTCTRL(主席才可发此命令)
OSPEVENT (EV_CONF_VMPGETPARAM_REQ		 , OUTER_CONF_ENTRY + 84);
// 获取视频复合参数应答		| TVMPParam								| MTCTRL->UI
OSPEVENT (EV_CONF_VMPGETPARAM_RSP		 , OUTER_CONF_ENTRY + 85);
// 视频源指示				|以\0结束的字符串						| MTCTRL->UI
OSPEVENT (EV_CONF_SRCNAME_IND			 , OUTER_CONF_ENTRY + 86);
// 回传通道指示				|(u8)MT_ENABLE/MT_DISABLE				| MTCTRL->UI
OSPEVENT (EV_CONF_UPLOADCHAN_IND			 , OUTER_CONF_ENTRY + 87);
// 终端别名指示				|以/0结束的字符串						| MTCTRL->UI
OSPEVENT (EV_CONF_MTNAME_IND			 , OUTER_CONF_ENTRY + 88);


/************************会 议 监 控************************/

// 开始监控请求				| <m,t>									| UI->MTCTRL
OSPEVENT (EV_CONF_STARTMONITOR_REQ			 , OUTER_CONF_ENTRY + 91);
// 开始监控应答				| <m,t> + DWORD(ip,如果失败ip为0) + WORD(音频端口号) + WORD(视频端口号)	| MTCTRL->UI
OSPEVENT (EV_CONF_STARTMONITOR_RSP			 , OUTER_CONF_ENTRY + 92);
// 停止监控命令				| <m,t>									| UI->MTCTRL
OSPEVENT (EV_CONF_STOPMONITOR_CMD			 , OUTER_CONF_ENTRY + 93);


// 结束会议					| NULL			| UI->MTCTRL
OSPEVENT (EV_CONF_END_CMD				 , OUTER_CONF_ENTRY + 120);

/*
////////多画面///////////
//开始显示多画面请求		| <m,t>
OSPEVENT (EV_CONF_PIPSTART_REQ			 , OUTER_CONF_ENTRY + 51);
//开始显示多画面应答		| <m,t> + 1byte(granted/denied)
OSPEVENT (EV_CONF_PIPSTART_RSP			 , OUTER_CONF_ENTRY + 52);
//停止显示多画面			| <m,t>
OSPEVENT (EV_CONF_PIPSTOP_CMD			 , OUTER_CONF_ENTRY + 53);
//查询其他终端选看的请求	| <m,t>
OSPEVENT (EV_CONF_PIPQUERY_REQ			 , OUTER_CONF_ENTRY + 54);
//查询其他终端选看的应答	| <m,t>(dest) + <m,t>(viewing)
OSPEVENT (EV_CONF_PIPQUERY_RSP			 , OUTER_CONF_ENTRY + 55);
*/

///////////////////////////////视频矩阵消息//////////////////////////////////

// 初始化视频矩阵			| _TDEVCFG	| MTCTRL->DEVCTRL
OSPEVENT (EV_MATRIX_INIT_CMD	    , OUTER_MATR_ENTRY + 1);
// 配置一个输入－输出		| 1BYTE(MT_AUDIO/MT_VIDEO/MT_AV) + 输出端口(1BYTE) + 输入端口(1BYTE) | MTCTRL->DEVCTRL
OSPEVENT (EV_MATRIX_LINKONE_CMD	    , OUTER_MATR_ENTRY + 2);
// 配置所有输入－输出		| 1BYTE(MT_AUDIO/MT_VIDEO/MT_AV) + 端口总数(num,1BYTE) + num个输出端口对应的输入端口(num个BYTEs) | MTCTRL->DEVCTRL
OSPEVENT (EV_MATRIX_LINKALL_CMD	    , OUTER_MATR_ENTRY + 3);
// 矩阵状态指示				| 1BYTE(MT_OK:连接成功 MT_ERR:连接失败)	| DEVCTRL->MTCTRL
OSPEVENT (EV_MATRIX_STATUS_IND	    , OUTER_MATR_ENTRY + 4);
		
// 保存矩阵方案				| 1BYTE(MT_AUDIO/MT_VIDEO/MT_AV)+1BYTE,方案号(1~8) + 方案名('\0'结束的字符串)	| UI->MTCTRL
OSPEVENT (EV_MATRIX_SCHEMESAVE_CMD	, OUTER_MATR_ENTRY + 6);
// 删除矩阵方案				| 1BYTE,方案号(1~8)	| UI->MTCTRL
OSPEVENT (EV_MATRIX_SCHEMEDEL_CMD	, OUTER_MATR_ENTRY + 7);
// 加载矩阵方案				| 1BYTE(MT_AUDIO/MT_VIDEO/MT_AV)+1BYTE,方案号(1~8) | UI->MTCTRL
OSPEVENT (EV_MATRIX_SCHEMELOAD_CMD	, OUTER_MATR_ENTRY + 8);
// 矩阵方案指示				| TMATRIXSCHEME数组 | MTCTRL->UI
OSPEVENT (EV_MATRIX_SCHEME_IND		, OUTER_MATR_ENTRY + 9);
// 配置矩阵端口				| 1BYTE(MT_AUDIO/MT_VIDEO/MT_AV) + 输出端口(_TMATRIXPORT) + 输入端口(_TMATRIXPORT)	| UI->MTCTRL
OSPEVENT (EV_MATRIX_CFGPORT_CMD		, OUTER_MATR_ENTRY + 10);
// 恢复默认设置				| 1BYTE(MT_AUDIO/MT_VIDEO/MT_AV)	| UI->MTCTRL
OSPEVENT (EV_MATRIX_LOADDEFAULT_CMD	, OUTER_MATR_ENTRY + 11);
// 选择一路输入源			| 1BYTE(MT_AUDIO/MT_VIDEO/MT_AV) + 1BYTE(表示选择几号视音频源，1~16)	| UI->MTCTRL
OSPEVENT (EV_MATRIX_SELECTINPUT_REQ , OUTER_MATR_ENTRY + 12);
// 当前矩阵配置信息请求		| 1BYTE(MT_AUDIO/MT_VIDEO/MT_AV)	| UI->MTCTRL
OSPEVENT (EV_MATRIX_INFO_REQ	    , OUTER_MATR_ENTRY + 13);
// 当前矩阵配置信息指示		| 1BYTE(MT_AUDIO/MT_VIDEO/MT_AV) + _TMATRIXINFO(如为Both,_TMATRIXINFO数组,A+V)	| MTCTRL->UI
OSPEVENT (EV_MATRIX_INFO_IND	    , OUTER_MATR_ENTRY + 14);
// 所有矩阵方案请求			| TMATRIXSCHEME数组					| MTCTRL->UI
OSPEVENT (EV_MATRIX_SCHEME_REQ	    , OUTER_MATR_ENTRY + 15);



///////////////////////////////摄像头消息//////////////////////////////////

// 摄像头初始化				| 摄像头个数(1Byte) + _TDEVCFG数组
OSPEVENT (EV_CAMERA_INIT_CMD		, OUTER_CAM_ENTRY + 1);
// 摄像头状态指示			| 4 BYTE,1-4号摄像头的连接状态(MT_OK/MT_ERR)
OSPEVENT (EV_CAMERA_STATUS_IND		, OUTER_CAM_ENTRY + 2);

// 本地/远端摄像头切换		| 1 BYTE(MT_LOCAL:本地/MT_REMOTE:远端)
OSPEVENT (EV_CAMERA_SOURCE_CMD		, OUTER_CAM_ENTRY + 6);
// 选择视频源命令			| 1 BYTE,Video Source Number(1-4)
OSPEVENT (EV_CAMERA_SELECT_CMD		, OUTER_CAM_ENTRY + 7);

// 说明:以下的Direction定义详见MtConstDef.h中摄像头的常量定义(如CAMERA_PAN_LEFT)

// 移动命令					| 2 BYTE,Direction + Action(MT_START/MT_STOP)
OSPEVENT (EV_CAMERA_PANTILT_CMD		, OUTER_CAM_ENTRY + 8);		
// 聚焦命令					| 2 BYTE,Direction + Action(MT_START/MT_STOP)
OSPEVENT (EV_CAMERA_FOCUS_CMD		, OUTER_CAM_ENTRY + 9);
// 视野命令					| 2 BYTE,Direction + Action(MT_START/MT_STOP)
OSPEVENT (EV_CAMERA_ZOOM_CMD		, OUTER_CAM_ENTRY + 10);
// 预置位命令				| 2 BYTE,Action(save/move) + preset No(1-16)
OSPEVENT (EV_CAMERA_PRESET_CMD		, OUTER_CAM_ENTRY + 11);
// 亮度调节命令				| 2 BYTE,Direction + Action(MT_START/MT_STOP)
OSPEVENT (EV_CAMERA_BRIGHT_CMD		, OUTER_CAM_ENTRY + 12);

///////////////////////////////串口消息//////////////////////////////////
// 配置串口                 | _TSERCFG | MTCTRL->DEVCTRL
OSPEVENT (EV_SERIES_SETCOM_CMD     , OUTER_CAM_ENTRY + 13);
// IRAY启动命令                 | 协议类型(u8)+地址(u8) | MTCTRL->DEVCTRL
OSPEVENT (EV_IRAY_START_CMD     , OUTER_CAM_ENTRY + 14);


///////////////////////////////Codec相关消息//////////////////////////////////

// 创建编码器请求			| EncoderID	+ _TPCCODEC	| MTCTRL->CODEC
OSPEVENT (EV_ENCODE_CREATE_REQ		, OUTER_CODEC_ENTRY + 1);
// 创建编码器应答			| EncoderID + Result(1BYTE,MT_OK:成功 MT_ERR:失败)	| CODEC->MTCTRL
OSPEVENT (EV_ENCODE_CREATE_RSP		, OUTER_CODEC_ENTRY + 2);
// 设置编码参数				| EncoderID + MediaType(MT_AUDIO/MT_VIDEO/MT_AV) + _TAENCPARAM/_TVENCPARAM	| MTCTRL->CODEC
OSPEVENT (EV_ENCODE_SETPARAM_CMD	, OUTER_CODEC_ENTRY + 3);
// 开始编码命令				| EncoderID + MediaType(MT_AUDIO/MT_VIDEO/MT_AV)	| MTCTRL->CODEC
OSPEVENT (EV_ENCODE_STARTENCODE_CMD , OUTER_CODEC_ENTRY + 4);
// 停止编码命令				| EncoderID + MediaType(MT_AUDIO/MT_VIDEO/MT_AV) | MTCTRL->CODEC
OSPEVENT (EV_ENCODE_STOPENCODE_CMD	, OUTER_CODEC_ENTRY + 5);
// 开始发送命令				| EncoderID + MediaType(MT_AUDIO/MT_VIDEO/MT_AV) + rtcp(TPROADDR) + rtp(TPROADDR)	| MTCTRL->CODEC
OSPEVENT (EV_ENCODE_STARTSEND_CMD	, OUTER_CODEC_ENTRY + 6);
// 停止发送命令				| EncoderID + MediaType(MT_AUDIO/MT_VIDEO/MT_AV) + rtcp(TPROADDR) + rtp(TPROADDR)	| MTCTRL->CODEC
OSPEVENT (EV_ENCODE_STOPSEND_CMD	, OUTER_CODEC_ENTRY + 7);
// 设置发送重发参数			| EncoderID + _TSENDRTCFG
OSPEVENT (EV_ENCODE_SETRETRAN_CMD	, OUTER_CODEC_ENTRY + 8);
// 设置图像质量参数			| EncoderID + _TIMAGEQUAL
OSPEVENT (EV_ENCODE_SETIMAGEQUAL_CMD	, OUTER_CODEC_ENTRY + 9);
// 哑音命令					| 1BYTE(MT_ENABLE/MT_DISABLE)	| UI->MTCTRL
// 哑音命令					| EncoderID + 1BYTE(MT_ENABLE/MT_DISABLE)	| MTCTRL->CODEC
OSPEVENT (EV_ENCODE_MUTE_CMD		, OUTER_CODEC_ENTRY + 10);
// 设置编码音量				| 1BYTE(vol)			| UI->MTCTRL
// 设置编码音量				| EncoderID + 1BYTE(vol)| MTCTRL->CODEC
OSPEVENT (EV_ENCODE_SETVOLUMN_CMD	, OUTER_CODEC_ENTRY + 11);

// 创建解码器请求			| 1BYTE,DecoderID	| MTCTRL->CODEC
OSPEVENT (EV_DECODE_CREATE_REQ		, OUTER_CODEC_ENTRY + 12);
// 创建解码器应答			| DecoderID + Result(1BYTE,MT_OK:成功 MT_ERR:失败)	| CODEC->MTCTRL
OSPEVENT (EV_DECODE_CREATE_RSP		, OUTER_CODEC_ENTRY + 13);
// 设置解码参数				| DecoderID + MediaType(MT_AUDIO/MT_VIDEO/MT_AV)  + _TADECPARAM/_TVDECPARAM	| MTCTRL->CODEC
OSPEVENT (EV_DECODE_SETPARAM_CMD	, OUTER_CODEC_ENTRY + 14);
// 开始解码命令				| 2BYTE,DecoderID + MediaType(MT_AUDIO/MT_VIDEO/MT_AV)	| MTCTRL->CODEC
OSPEVENT (EV_DECODE_STARTDECODE_CMD	, OUTER_CODEC_ENTRY + 15);
// 停止解码命令				| 2BYTE,DecoderID + MediaType(MT_AUDIO/MT_VIDEO/MT_AV)	| MTCTRL->CODEC
OSPEVENT (EV_DECODE_STOPDECODE_CMD	, OUTER_CODEC_ENTRY + 16);
// 开始接收码流				| DecoderID + MediaType(MT_AUDIO/MT_VIDEO/MT_AV) + rtcp(TPROADDR) + rtp(TPROADDR)	| MTCTRL->CODEC
OSPEVENT (EV_DECODE_STARTRECV_CMD	, OUTER_CODEC_ENTRY + 17);
// 停止接收码流				| 2BYTE,DecoderID + MediaType(MT_AUDIO/MT_VIDEO/MT_AV)	| MTCTRL->CODEC
OSPEVENT (EV_DECODE_STOPRECV_CMD	, OUTER_CODEC_ENTRY + 18);
// 图像冻结					| 1BYTE,DecoderID				| MTCTRL->CODEC
OSPEVENT (EV_DECODE_FREEZE_CMD		, OUTER_CODEC_ENTRY + 19);
// 图像更新					| 1BYTE,DecoderID				| MTCTRL->CODEC
OSPEVENT (EV_DECODE_UPDATE_CMD		, OUTER_CODEC_ENTRY + 20);
// 设置接收重传参数			| 1BYTE,DecoderID + _RECVRTCFG
OSPEVENT (EV_DECODE_SETRETRAN_CMD	, OUTER_CODEC_ENTRY + 21);

// 静音命令					| 1BYTE(MT_ENABLE/MT_DISABLE)	| UI->MTCTRL
// 静音命令					| 2BYTE,DecoderID + 1BYTE(MT_ENABLE/MT_DISABLE)	| MTCTRL->CODEC
OSPEVENT (EV_DECODE_QUIET_CMD		, OUTER_CODEC_ENTRY + 22);
// 设置音量					| 1BYTE(vol)	| UI->MTCTRL
// 设置音量					| 2BYTE,DecoderID + 1BYTE(vol)	| MTCTRL->CODEC
OSPEVENT (EV_DECODE_SETVOLUMN_CMD	, OUTER_CODEC_ENTRY + 23);
// 第二路视频的解码器ID指示 | 1BYTE(Decoder ID) + 1BYTE(MT_START|MT_STOP)
OSPEVENT (EV_DECODE_DUALVIDEO_IND	, OUTER_CODEC_ENTRY + 24);
// 开始转发码流				| DecoderID + MediaType(MT_AUDIO/MT_VIDEO) + rtcp(TPROADDR) + rtp(TPROADDR)	| MTCTRL->CODEC
OSPEVENT (EV_DECODE_STARTFWD_CMD	, OUTER_CODEC_ENTRY + 25);
// 停止转发码流				| DecoderID + MediaType(MT_AUDIO/MT_VIDEO) + rtcp(TPROADDR) + rtp(TPROADDR)	| MTCTRL->CODEC
OSPEVENT (EV_DECODE_STOPFWD_CMD		, OUTER_CODEC_ENTRY + 26);
//设置回声抵消参数			| _TAEC							| MTCTRL->CODEC
OSPEVENT (EV_AEC_SETPARAM_CMD		, OUTER_CODEC_ENTRY + 27);
//快照信息请求				| _TSNAPINFO	 | MTCTRL->CODEC
OSPEVENT( EV_OUT_SNAPSHOTINFO_REQ	, OUTER_CODEC_ENTRY + 28);
//快照信息指示				| _TSNAPINFO	 | MTCTRL->MTC
OSPEVENT( EV_OUT_SNAPSHOTINFO_IND	, OUTER_CODEC_ENTRY + 29);
//清除快照命令				| NULL			 | MTC->MTCTRL
OSPEVENT( EV_OUT_CLEARSNAP_CMD		,OUTER_CODEC_ENTRY + 30);
// 上报视频编解码码率		|_TBITRATE	| codec->MTCTRL
OSPEVENT (EV_CODEC_BITRATE_IND		, OUTER_CODEC_ENTRY + 31);
// 上报MAP状态				|_TMAPSTATUS		| codec->MTCTRL
OSPEVENT (EV_CODEC_MAPSTATUS_IND	, OUTER_CODEC_ENTRY + 32);
// 画中画操作(2字节:		| DecoderID + 打开/关闭/移动/切换)
OSPEVENT (EV_CODEC_PIPOPT_CMD		, OUTER_CODEC_ENTRY + 33);
// Codec统计信息请求		|(1字节 MT_ENABLE/MT_DISABLE)
OSPEVENT (EV_CODEC_STATISTIC_REQ	, OUTER_CODEC_ENTRY + 34);
// Codec统计信息上报		|_TCODECSTATISTIC
OSPEVENT (EV_CODEC_STATISTIC_IND	, OUTER_CODEC_ENTRY + 35);
// 音频功率请求				|	(1字节 MT_ENABLE/MT_DISABLE)
OSPEVENT (EV_CODEC_AUDIOPOWER_REQ	, OUTER_CODEC_ENTRY + 36);
// 音频功率上报				|	_TAUDIOPOWER
OSPEVENT (EV_CODEC_AUDIOPOWER_IND	, OUTER_CODEC_ENTRY + 37);
// 编码加密					|	指定长度的数组
OSPEVENT (EV_ENCODE_SYSPWD_CMD	, OUTER_CODEC_ENTRY + 38);
// 音频功率上报				|	_TAUDIOPOWER
OSPEVENT (EV_DECODE_SYSPWD_CMD	, OUTER_CODEC_ENTRY + 39);
// 上报丢包				   |解码器ID(1字节)	| codec->MTCTRL
OSPEVENT (EV_CODEC_LOSTPACK_IND			, OUTER_CODEC_ENTRY + 40);





///////////////////////////////终端配置消息//////////////////////////////////

//本地信息指示				| _TTERCFG						| MTCTRL->UI
OSPEVENT (EV_CFG_LOCALINFO_IND		, OUTER_CFG_ENTRY + 1);
//本地配置命令				| _TTERCFG						| UI->MTCTRL
OSPEVENT (EV_CFG_LOCALINFO_CMD		, OUTER_CFG_ENTRY + 2);
//恢复本地配置默认值		| NULL							| UI->MTCTRL
OSPEVENT (EV_CFG_LOCALINFODEF_CMD	, OUTER_CFG_ENTRY + 3);

//网络信息指示				| _TNETCFG						| MTCTRL->UI
OSPEVENT (EV_CFG_NET_IND			, OUTER_CFG_ENTRY + 4);
//网络配置命令				| _TNETCFG						| UI->MTCTRL
OSPEVENT (EV_CFG_NET_CMD			, OUTER_CFG_ENTRY + 5);
//恢复网络配置默认值		| NULL							| UI->MTCTRL
OSPEVENT (EV_CFG_NETDEF_CMD			, OUTER_CFG_ENTRY + 6);


//呼叫配置指示				| _TCALLCFG						| MTCTRL->UI
OSPEVENT (EV_CFG_CALL_IND			, OUTER_CFG_ENTRY + 7);
//呼叫配置命令				| _TCALLCFG						| UI->MTCTRL
OSPEVENT (EV_CFG_CALL_CMD			, OUTER_CFG_ENTRY + 8);
//恢复呼叫配置默认值		| NULL							| UI->MTCTRL
OSPEVENT (EV_CFG_CALLDEF_CMD		, OUTER_CFG_ENTRY + 9);

//视频配置指示				| Index(1字节) + _TVENCPARAM + _TVDECPARAM		| MTCTRL->UI
OSPEVENT (EV_CFG_VIDEO_IND			, OUTER_CFG_ENTRY + 10);
//视频配置命令				| Index(1字节) + _TVENCPARAM + _TVDECPARAM		| UI->MTCTRL
OSPEVENT (EV_CFG_VIDEO_CMD			, OUTER_CFG_ENTRY + 11);
//恢复视频配置默认值		| Index(1字节)									| UI->MTCTRL
OSPEVENT (EV_CFG_VIDEODEF_CMD		, OUTER_CFG_ENTRY + 12);

//音频配置指示				| _TAENCPARAM + _TADECPARAM		| MTCTRL->UI
OSPEVENT (EV_CFG_AUDIO_IND			, OUTER_CFG_ENTRY + 13);
//音频配置命令				| _TAENCPARAM + _TADECPARAM		| UI->MTCTRL
OSPEVENT (EV_CFG_AUDIO_CMD			, OUTER_CFG_ENTRY + 14);
//恢复音频配置默认值		| NULL							| UI->MTCTRL
OSPEVENT (EV_CFG_AUDIODEF_CMD		, OUTER_CFG_ENTRY + 15);

//摄像头配置指示			| 1BYTE(摄像头个数,1~6) + _TDEVCFG数组	| MTCTRL->UI
OSPEVENT (EV_CFG_CAMERA_IND			, OUTER_CFG_ENTRY + 16);
//摄像头配置命令			| _TDEVCFG						| UI->MTCTRL
OSPEVENT (EV_CFG_CAMERA_CMD			, OUTER_CFG_ENTRY + 17);
//恢复摄像头配置默认值		| NULL							| UI->MTCTRL
OSPEVENT (EV_CFG_CAMERADEF_CMD		, OUTER_CFG_ENTRY + 18);

//矩阵配置指示				| _TDEVCFG						| MTCTRL->UI
OSPEVENT (EV_CFG_MATRIX_IND			, OUTER_CFG_ENTRY + 19);
//矩阵配置命令				| _TDEVCFG						| UI->MTCTRL
OSPEVENT (EV_CFG_MATRIX_CMD			, OUTER_CFG_ENTRY + 20);
//恢复矩阵配置默认值		| NULL							| UI->MTCTRL
OSPEVENT (EV_CFG_MATRIXDEF_CMD		, OUTER_CFG_ENTRY + 21);

//显示配置指示				| _TOSDCFG						| MTCTRL->UI
OSPEVENT (EV_CFG_OSD_IND			, OUTER_CFG_ENTRY + 22);
//显示配置命令				| _TOSDCFG						| UI->MTCTRL
OSPEVENT (EV_CFG_OSD_CMD			, OUTER_CFG_ENTRY + 23);
//恢复显示配置默认值		| NULL							| UI->MTCTRL
OSPEVENT (EV_CFG_OSDDEF_CMD			, OUTER_CFG_ENTRY + 24);

//pccodec配置指示			| _PCCODEC					    | MTCTRL->UI(Windows)
OSPEVENT( EV_CFG_PCCODEC_IND		, OUTER_CFG_ENTRY + 25);
//pccodec配置命令			| _PCCODEC						| UI->MTCTRL(Windows)
OSPEVENT( EV_CFG_PCCODEC_CMD		, OUTER_CFG_ENTRY + 26);
//恢复pccodec配置默认值		| NULL							| UI->MTCTRL(Windows)
OSPEVENT( EV_CFG_PCCODEDEF_CMD		, OUTER_CFG_ENTRY + 27);

//AEC配置指示				| _TAEC							| MTCTRL->UI
OSPEVENT( EV_CFG_AEC_IND			, OUTER_CFG_ENTRY + 31);
//AEC配置命令				| _TAEC							| UI->MTCTRL
OSPEVENT( EV_CFG_AEC_CMD			, OUTER_CFG_ENTRY + 32);
//恢复AEC默认配置			| NULL							| UI->MTCTRL
OSPEVENT( EV_CFG_AECDEF_CMD			, OUTER_CFG_ENTRY + 33);

//发送重传配置指示			| _TSENDRTCFG					| MTCTRL->UI
OSPEVENT( EV_CFG_SENDRT_IND			, OUTER_CFG_ENTRY + 34);
//发送重传配置命令			| _TSENDRTCFG					| UI->MTCTRL
OSPEVENT( EV_CFG_SENDRT_CMD			, OUTER_CFG_ENTRY + 35);
//恢复发送重传默认配置		| NULL							| UI->MTCTRL
OSPEVENT( EV_CFG_SENDRTDEF_CMD		, OUTER_CFG_ENTRY + 36);

//接收重传配置指示			| _TRECVRTCFG					| MTCTRL->UI
OSPEVENT( EV_CFG_RECVRT_IND			, OUTER_CFG_ENTRY + 37);
//接收重传配置命令			| _TRECVRTCFG					| UI->MTCTRL
OSPEVENT( EV_CFG_RECVRT_CMD			, OUTER_CFG_ENTRY + 38);
//恢复接收重传默认配置		| NULL							| UI->MTCTRL
OSPEVENT( EV_CFG_RECVRTDEF_CMD		, OUTER_CFG_ENTRY + 39);
//broadcast panel会议命令	| _TPANELCFG					| UI->MTCTRL
OSPEVENT( EV_CFG_CONFPANEL_CMD		, OUTER_CFG_ENTRY + 40);
//broadcast panel会议信息指示	| _TPANELCFG					| MTCTRL->UI
OSPEVENT( EV_CFG_CONFPANEL_IND		, OUTER_CFG_ENTRY + 41);


//视频输出配置指示			| _TVOUT						| MTCTRL->UI
OSPEVENT (EV_CFG_VIDEOOUT_IND		, OUTER_CFG_ENTRY + 46);
//视频输出配置命令			| _TVOUT						| UI->MTCTRL
OSPEVENT (EV_CFG_VIDEOOUT_CMD		, OUTER_CFG_ENTRY + 47);

//恢复所有配置的默认值		| NULL							| UI->MTCTRL
OSPEVENT (EV_CFG_RESUMEALL_CMD		, OUTER_CFG_ENTRY + 48);
//请求各项配置信息			| NULL							| UI->MTCTRL
OSPEVENT( EV_CFG_GETALL_REQ			, OUTER_CFG_ENTRY + 49);

// 图像质量指示				|_TIMAGEQUAL
OSPEVENT (EV_CFG_IMAGEQUALITY_IND			, OUTER_CFG_ENTRY + 50);
// 图像质量命令				|_TIMAGEQUAL
OSPEVENT (EV_CFG_IMAGEQUALITY_CMD			, OUTER_CFG_ENTRY + 51);
// 图像质量恢复默认值		|_TIMAGEQUAL
OSPEVENT (EV_CFG_IMAGEQUALDEF_CMD			, OUTER_CFG_ENTRY + 52);

// SNMP配置指示				|_TSNMPCFG
OSPEVENT (EV_CFG_SNMPCFG_IND			, OUTER_CFG_ENTRY + 53);
// SNMP配置命令				|_TSNMPCFG
OSPEVENT (EV_CFG_SNMPCFG_CMD			, OUTER_CFG_ENTRY + 54);
// SNMP配置恢复默认值		|_TSNMPCFG
OSPEVENT (EV_CFG_SNMPCFGDEF_CMD			, OUTER_CFG_ENTRY + 55);

// 串口配置指示					|_TSERCFG
OSPEVENT (EV_CFG_SERIAL_IND			, OUTER_CFG_ENTRY + 59);
// 串口配置命令					|_TSERCFG
OSPEVENT (EV_CFG_SERIAL_CMD			, OUTER_CFG_ENTRY + 60);
// 串口配置恢复默认值			|_TSERCFG
OSPEVENT (EV_CFG_SERIALDEF_CMD			, OUTER_CFG_ENTRY + 61);



// 设置编码格式				| 1BYTE MediaType(MT_AUDIO/MT_VIDEO) + 1BYTE type
OSPEVENT( EV_CFG_SETTYPE_CMD			, OUTER_CFG_ENTRY + 70);
// 设置编码码率				| 2BYTE 码率
OSPEVENT( EV_CFG_SETBITRATE_CMD			, OUTER_CFG_ENTRY + 71);


///////////////////////////////   杂项消息  //////////////////////////////////

//终端提示信息				| _TMTNOTE						| MTCTRL->UI
OSPEVENT (EV_OUT_MTNOTE_IND			, OUTER_MISC_ENTRY + 1);
//终端状态查询				| NULL							| UI->MTCTRL
OSPEVENT (EV_OUT_MTSTATUS_REQ		, OUTER_MISC_ENTRY + 2);
//终端状态上报				| _TTERSTATUS					| MTCTRL->UI
OSPEVENT (EV_OUT_MTSTATUS_IND		, OUTER_MISC_ENTRY + 3);
//本地自环					| 2BYTE, MediaType(MT_AUDIO/MT_VIDEO/MT_AV) + Action(MT_START:开始  MT_STOP:停止) | UI->MTCTRL
OSPEVENT (EV_OUT_INNERLOOP_CMD		, OUTER_MISC_ENTRY + 4);
//外环命令					| 1BYTE(MT_START:开始 MT_STOP:停止)			| UI->MTCTRL
OSPEVENT (EV_OUT_OUTERLOOP_CMD		, OUTER_MISC_ENTRY + 5);
//滚动消息					| '\0'结束的字符串				| MTCTRL->UI
OSPEVENT (EV_OUT_ROLLMSG_CMD	    , OUTER_MISC_ENTRY + 6);
//隐藏OSD标志				| 1BYTE,标志号					| UI->MTCTRL
OSPEVENT (EV_OUT_HIDETAG_CMD	    , OUTER_MISC_ENTRY + 7);
//显示OSD标志				| 1BYTE,标志号					| UI->MTCTRL
OSPEVENT (EV_OUT_SHOWTAG_CMD		, OUTER_MISC_ENTRY + 8);
//启动CodecManager模块      | NULL							| UI->MTCTRL
OSPEVENT( EV_CODEC_ENCAP_MODULE_START		, OUTER_MISC_ENTRY + 9 );
// 协议栈初始化结果上报		| 1字节 MT_OK/MT_ERR
OSPEVENT( EV_OUT_STACKINIT_IND		, OUTER_MISC_ENTRY + 10 );

// MTC请求开始接收媒体流	| MTC->MTCTRL
// 1BYTE(本地:MT_LOCAL 远端:MT_REMOTE) + TIPADDR(视频RTP地址,音频在此基础上叠加) 
OSPEVENT( EV_MTC_STARTRECV_CMD		, OUTER_MISC_ENTRY + 11);
// MTC请求停止接收媒体流	| MTC->MTCTRL
// 1BYTE(本地:MT_LOCAL 远端:MT_REMOTE)
OSPEVENT( EV_MTC_STOPRECV_CMD		, OUTER_MISC_ENTRY + 12);

// MTC请求开始传送第二路视频| NULL						 | MTC->MTCTRL
OSPEVENT( EV_MTC_DUALVIDEOSTART_REQ	, OUTER_MISC_ENTRY + 13);
// 双视频流开始应答			|							 | MCTRL->MTC
// 成功:1BYTE(MT_OK) + TIPADDR(接受码流的地址)	失败:1BYTE(MT_ERR)
OSPEVENT( EV_MTC_DUALVIDEOSTART_RSP	, OUTER_MISC_ENTRY + 14);

// MTC请求停止传送第二路视频| NULL						 | MTC->MTCTRL
OSPEVENT( EV_MTC_DUALVIDEOSTOP_REQ	, OUTER_MISC_ENTRY + 15);
// 双视频流停止应答			| 1BYTE(MT_OK/MT_ERR)		 | MCTRL->MTC
OSPEVENT( EV_MTC_DUALVIDEOSTOP_RSP	, OUTER_MISC_ENTRY + 16);
// 双流连接状态指示			| 1BYTE(MT_ENABLE/MT_DISABLE)
OSPEVENT( EV_DUALVID_CONNECT_IND	, OUTER_MISC_ENTRY + 17);

//双流编码器连接状态通知    | 1BYTE(MT_ENABLE/MT_DIABLE) + TIPADDR(DualCodce发送的RTCP地址) + TIPADDR(DualCodec接收起始地址)	 
//							|  DEVCTRL->MTCTRL
OSPEVENT( EV_OUT_DUALENCCONNECT_IND	, OUTER_MISC_ENTRY + 18);
// 双视频流动作请求			| 1BYTE(MT_START|MT_STOP)	 | VxUI->MTCTRL
//							| 1BYTE(MT_START) + TIPADDR(视频RTP地址) | MTCTRL->DEVCTRL
//							| 1BYTE(MT_STOP)			 | MTCTRL->DEVCTRL
OSPEVENT( EV_OUT_DUALVIDEO_REQ	, OUTER_MISC_ENTRY + 19);
// 双视频流动作应答			| 1BYTE(MT_OK|MT_ERR)		 | DEVCTRL->MTCTRL,MTCTRL->VxUI
OSPEVENT( EV_OUT_DUALVIDEO_RSP	, OUTER_MISC_ENTRY + 20);
//双视频流接收命令			| 1BYTE(MT_START/MT_STOP)	 | MTCTRL->DEVCTRL
OSPEVENT( EV_OUT_DUALVIDEORCV_CMD,OUTER_MISC_ENTRY + 21);
// 图像测试( 1字节: MT_LOCAL/MT_REMOTE, 1字节 类型:RESOLUTION_TEST/COLOR_TEST/GRAY_TEST/TEST_CLOSE )
OSPEVENT (EV_OUT_IMAGETEST_CMD			, OUTER_MISC_ENTRY + 22);
// 本地小画面打开/关闭(1字节:MT_ENABLE/MT_DISABLE)
OSPEVENT (EV_OUT_SMALLLOCAL_CMD			, OUTER_MISC_ENTRY + 23);
// 本地小画面使能状态上报(1字节:MT_ENABLE/MT_DISABLE)
OSPEVENT (EV_OUT_SMALLLOCAL_IND			, OUTER_MISC_ENTRY + 24);
// 系统钥匙生成					|NULL				|UI->MTCTRL
OSPEVENT (EV_OUT_SYSPWDGEN_CMD				, OUTER_MISC_ENTRY + 25);
// 系统钥匙保存					|1BYTE(MT_ENABLE/MT_DISABLE)				|UI->MTCTRL
OSPEVENT (EV_OUT_SYSPWDSAVE_CMD				, OUTER_MISC_ENTRY + 26);
// 公钥内容指示					|8字节的公钥		|MTCTRL->UI
OSPEVENT (EV_OUT_SYSPUBPWD_IND			, OUTER_MISC_ENTRY + 27);


 


////////////////////////// VxWorks UI 内部消息(50)  /////////////////////////////
//OSPEVENT (EV_VXUI_MSG_TYPE		, OUTER_VXUI_ENTRY + 1);

// 按键按下(1字节: 键码)
OSPEVENT (EV_UI_KEYPRESS_IND			, OUTER_VXUI_ENTRY + 1);
// 按键弹起(1字节: 键码)
OSPEVENT (EV_UI_KEYRELEASE_IND			, OUTER_VXUI_ENTRY + 2);
// 属性页更新消息(1字节:属性页ID)
OSPEVENT (EV_UI_PROPERTY_UPDATE			, OUTER_VXUI_ENTRY + 3);
// 快照命令
OSPEVENT (EV_UICODEC_SNAPSHOT_CMD			, OUTER_VXUI_ENTRY + 4);
// 发送本地视频(1字节MT_ENABLE/MT_DISABLE)
OSPEVENT (EV_UICODEC_SENDLOCAL_CMD			, OUTER_VXUI_ENTRY + 5);
// 菜单重置消息
OSPEVENT (EV_MENU_RESET_CMD                 , OUTER_VXUI_ENTRY + 6);
// 用户更新图片通知
OSPEVENT (EV_USERLBL_UPDATE_IND             , OUTER_VXUI_ENTRY + 7);
// 用户开启定时器通知
OSPEVENT (EV_UISTARTUP_TIMER_IND            , OUTER_VXUI_ENTRY + 8);
// 自环使能通知(1字节MT_ENABLE/MT_DISABLE)
OSPEVENT (EV_LOOP_TEST_IND                  , OUTER_VXUI_ENTRY + 9);

////////////////////////// Windows UI 内部消息(50) //////////////////////////////

//////////////////////////定时器消息定义(100)///////////////////////////////////////

//轮询定时器
OSPEVENT( TIMER_CTRL_POLLING		, EV_TIMER_BGN + 1 );
//TPS_ROUND_TRIP
OSPEVENT( TIMER_ROUND_TRIP			, EV_TIMER_BGN + 2 );
//TPS_GUARD
OSPEVENT( TIMER_GUARD				, EV_TIMER_BGN + 3 );
//会议开始检测定时器(TPS_CONFENTRY)
OSPEVENT( TIMER_CONFENTRY			, EV_TIMER_BGN + 4 );
//flowctrl定时器					| hsChan
OSPEVENT( TIMER_FLOWCTRL				, EV_TIMER_BGN + 5 );
//h281重发定时器
OSPEVENT( TIMER_H281_CONTINUE		, EV_TIMER_BGN + 6 );
//线路带宽检测定时器
OSPEVENT( TIMER_CHANCHK_BANDWIDTH	, EV_TIMER_BGN + 7 );
//串口重连检测
OSPEVENT( TIMER_COM_RECONNECT	    , EV_TIMER_BGN + 9 );	
//强制关键帧
OSPEVENT( TIMER_VIDEO_UPDATE        , EV_TIMER_BGN + 10 );   


//外设重联定时器(TPS_DEV_RECONNECT)
OSPEVENT( TIMER_CAMERA_RECONNECT	, EV_TIMER_BGN + 31 );
OSPEVENT( TIMER_MATRIX_RECONNECT	, EV_TIMER_BGN + 32 );
OSPEVENT( TIMER_SHOW_VOLUMNE		, EV_TIMER_BGN + 33 );	// 显示音量	
OSPEVENT( TIMER_SHOW_CODEC			, EV_TIMER_BGN + 34 );	// 显示codec统计信息
OSPEVENT( TIMER_VIDEO_BITRATE		, EV_TIMER_BGN + 35 );	// 上报编解码码率
OSPEVENT( TIMER_QUICKPHOTO_TIP		, EV_TIMER_BGN + 36 );	// 快照
OSPEVENT( TIMER_SMS_PAGETITLE		, EV_TIMER_BGN + 37 );	// 
OSPEVENT( TIMER_CONFEND_INS 		, EV_TIMER_BGN + 38 );
OSPEVENT( TIMER_INPUTPWD_DUR 		, EV_TIMER_BGN + 39 );
OSPEVENT( TIMER_MAP_STATUS	 		, EV_TIMER_BGN + 40 );	// map异常告警
OSPEVENT( TIMER_AUDIO_POWER	 		, EV_TIMER_BGN + 41 );	// 音频功率上报
OSPEVENT( TIMER_SNAPSHOT_INFO	 	, EV_TIMER_BGN + 42 );	// 快照信息上报
OSPEVENT( TIMER_HOTKEY_INFO	 	    , EV_TIMER_BGN + 43 );	// 提示停留时间


// 只用于OSP消息处理
// MTC发送图片文件			| 图片文件			|MTCTRL->MTC
OSPEVENT( EV_MTC_LABELBMP_IND	, EV_OUTEROSP_BGN + 1 );


#endif

