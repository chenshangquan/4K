/*****************************************************************************
   模块名      : 卫星  终端－MCU 通信消息定义
   文件名      : evsatmcumt.h
   相关文件    : evsatmcumt.cpp
   文件功能    : 
   作者        : 张明义
   版本        : V1.0  Copyright(C) 2001-2002 KDC, All rights reserved.
-----------------------------------------------------------------------------
   修改记录:
   日  期      版本        修改人      修改内容
   2004/11/02  1.0         张明义      创建
******************************************************************************/

#ifndef _EVENT_SATELLITE_MCU_MT_H_
#define _EVENT_SATELLITE_MCU_MT_H_

#include "osp.h"
#include "eventid.h"

//注：为保证程序正确运行，所有成功和失败应答比原消息号分别加1，2

/**********************************************************
 以下为MCU和终端之间业务接口，不包括MCU和MT各自内部消息（25001-26000）
**********************************************************/

/////////////////////////////////////////////////
//MCU和终端之间连接操作---终端不可用

//终端上电后向上级MCU发起的登记请求，MT->MCU，消息体为结构TMt
OSPEVENT( MT_MCU_REG_REQ,			EV_MCUMT_BGN );
//MCU准入应答，MCU->MT，无消息体
OSPEVENT( MCU_MT_REG_ACK,			EV_MCUMT_BGN + 1 );
//MCU拒绝应答，MCU->MT，无消息体
OSPEVENT( MCU_MT_REG_NACK,			EV_MCUMT_BGN + 2 );

//终端发给MCU查询全网MCU拓扑请求，MT->MCU，消息体为结构TMt
OSPEVENT( EV_SAT_MCUMT_TOPO_IND,	EV_MCUMT_BGN + 4 );	
OSPEVENT( MCU_MT_KEY_NOTIF,			EV_MCUMT_BGN + 6 ); 
//终端完成所有建链操作后通知mcu可以进行后继操作，消息体为TMt
OSPEVENT( MT_MCU_READY_NOTIF,		EV_MCUMT_BGN + 8 );
//向终端请求I帧
OSPEVENT( MCU_MT_SENDIFRAME_NOTIF,		EV_MCUMT_BGN + 10 );
/////////////////////////////////////////////////
//MCU邀请终端加入指定会议请求，MCU->MT，消息体为结构TMt
OSPEVENT( MCU_MT_INVITEMT_REQ,		EV_MCUMT_BGN + 100 );
//MT接受应答，MT->MCU，消息体为结构TMt
OSPEVENT( MT_MCU_INVITEMT_ACK,		EV_MCUMT_BGN + 101 );
//MT拒绝应答，MT->MCU，消息体为结构TMt
OSPEVENT( MT_MCU_INVITEMT_NACK,		EV_MCUMT_BGN + 102 );

//MCU强制终端退出会议命令，MCU->MT，无消息体
OSPEVENT( MCU_MT_DELMT_CMD,			EV_MCUMT_BGN + 108 );

//MCU发给MT的打开逻辑通道请求，MCU->MT，消息体为结构TMt+TLogicalChannel+TMt
OSPEVENT( MCU_MT_OPENLOGICCHNNL_REQ,	EV_MCUMT_BGN + 120 );
//终端发给MCU的成功应答，MT->MCU，消息体为结构TMt+TLogicalChannel+TMt
OSPEVENT( MT_MCU_OPENLOGICCHNNL_ACK,	EV_MCUMT_BGN + 121 );
//终端发给MCU的失败应答，MT->MCU，消息体为结构TMt+TLogicalChannel+TMt
OSPEVENT( MT_MCU_OPENLOGICCHNNL_NACK,	EV_MCUMT_BGN + 122 );

//MT发给MCU的打开逻辑通道请求，MT->MCU，消息体为结构TMt+TLogicalChannel
OSPEVENT( MT_MCU_OPENLOGICCHNNL_REQ,	EV_MCUMT_BGN + 124 );
//MCU发给终端的成功应答，MCU->MT，消息体为结构TMt+TLogicalChannel
OSPEVENT( MCU_MT_OPENLOGICCHNNL_ACK,	EV_MCUMT_BGN + 125 );
//MCU发给终端的失败应答，MCU->MT，消息体为结构TMt+TLogicalChannel
OSPEVENT( MCU_MT_OPENLOGICCHNNL_NACK,	EV_MCUMT_BGN + 126 );

//MCU发给终端的能力集通知，MCU->MT，消息体为结构TMt+TCapSupport
OSPEVENT( MCU_MT_CAPBILITYSET_NOTIF,	EV_MCUMT_BGN + 128 );
//终端发给MCU的能力集通知，MT->MCU，消息体为结构TMt+TCapSupport
OSPEVENT( MT_MCU_CAPBILITYSET_NOTIF,	EV_MCUMT_BGN + 129 );

//终端发给MCU的申请主席请求，MT->MCU，消息体为结构TMt
OSPEVENT( MT_MCU_APPLYCHAIRMAN_REQ,		EV_MCUMT_BGN + 132 );
//通知主席终端申请发言请求，MCU->MT，消息体为结构TMt
OSPEVENT( MCU_MT_APPLYCHAIRMAN_NOTIF,	EV_MCUMT_BGN + 135 );

//终端发给MCU的申请发言请求，MT->MCU，消息体为结构TMt
OSPEVENT( MT_MCU_APPLYSPEAKER_CMD,		EV_MCUMT_BGN + 136 );
//通知主席终端申请发言请求，MCU->MT，消息体为结构TMt
OSPEVENT( MCU_MT_APPLYSPEAKER_NOTIF,	EV_MCUMT_BGN + 137 );

//终端发给MCU的申请退出会议请求，MT->MCU，消息体为结构TMt
OSPEVENT( MT_MCU_APPLYQUITCONF_CMD,		EV_MCUMT_BGN + 140 );
//通知主席终端退出会议请求，MCU->MT，消息体为结构TMt
OSPEVENT( MCU_MT_APPLYQUITCONF_NOTIF,	EV_MCUMT_BGN + 141 );

//终端发给MCU的加入会议的请求，MT->MCU，消息体为结构TMt
OSPEVENT( MT_MCU_APPLYJOINCONF_REQ,		EV_MCUMT_BGN + 144 );
//终端发给MCU的加入会议的请求成功应答，MT->MCU，消息体为结构TMt
OSPEVENT( MCU_MT_APPLYJOINCONF_ACK,		EV_MCUMT_BGN + 145 );
//终端发给MCU的加入会议的请求失败应答，MT->MCU，无消息体
OSPEVENT( MCU_MT_APPLYJOINCONF_NACK,	EV_MCUMT_BGN + 146 );
//MCU通知主席终端有终端申请加入会议，MCU->MT，消息体为结构TMt
OSPEVENT( MCU_MT_APPLYJOINCONF_NOTIF,	EV_MCUMT_BGN + 147 );

//主席终端发给MCU的邀请终端请求，MT->MCU，消息体为结构TMt
OSPEVENT( MT_MCU_ADDMT_REQ,				EV_MCUMT_BGN + 152 );
//MCU回的成功应答，MCU->MT，TMt
OSPEVENT( MCU_MT_ADDMT_ACK,				EV_MCUMT_BGN + 153 );
//MCU回的失败应答，MCU->MT，TMt
OSPEVENT( MCU_MT_ADDMT_NACK,			EV_MCUMT_BGN + 154 );
OSPEVENT( MT_MCU_ADDMT_CMD,				EV_MCUMT_BGN + 155 );
//主席终端发给MCU的强制终端退出请求，MT->MCU，消息体为结构TMt
OSPEVENT( MT_MCU_DELMT_REQ,				EV_MCUMT_BGN + 156 );
//MCU回的成功应答，MCU->MT，TMt
OSPEVENT( MCU_MT_DELMT_ACK,				EV_MCUMT_BGN + 157 );
//MCU回的失败应答，MCU->MT，TMt
OSPEVENT( MCU_MT_DELMT_NACK,			EV_MCUMT_BGN + 158 );
OSPEVENT( MT_MCU_DELMT_CMD,				EV_MCUMT_BGN + 159 );

//主席终端发给MCU的中止会议请求，MT->MCU，无消息体
OSPEVENT( MT_MCU_DROPCONF_CMD,			EV_MCUMT_BGN + 160 );

//主席终端发给MCU的指定主席请求，MT->MCU，消息体为结构TMt，代表新主席
OSPEVENT( MT_MCU_SPECCHAIRMAN_REQ,		EV_MCUMT_BGN + 164 );
//MCU回的成功应答，MCU->MT，无消息体
OSPEVENT( MCU_MT_SPECCHAIRMAN_ACK,		EV_MCUMT_BGN + 165 );
//MCU回的失败应答，MCU->MT，无消息体
OSPEVENT( MCU_MT_SPECCHAIRMAN_NACK,		EV_MCUMT_BGN + 166 );

//主席终端发给MCU的指定发言人请求，MT->MCU，消息体为结构TMt，代表新发言人
OSPEVENT( MT_MCU_SPECSPEAKER_REQ,		EV_MCUMT_BGN + 168 );
//MCU回的成功应答，MCU->MT，无消息体
OSPEVENT( MCU_MT_SPECSPEAKER_ACK,		EV_MCUMT_BGN + 169 );
//MCU回的失败应答，MCU->MT，无消息体
OSPEVENT( MCU_MT_SPECSPEAKER_NACK,		EV_MCUMT_BGN + 170 );

//主席终端发给MCU的取消主席请求，MT->MCU，无消息体
OSPEVENT( MT_MCU_CANCELCHAIRMAN_CMD,	EV_MCUMT_BGN + 172 );

//主席终端发给MCU的取消发言人请求，MT->MCU，无消息体
OSPEVENT( MT_MCU_CANCELSPEAKER_CMD,		EV_MCUMT_BGN + 176 );

//列出所有会议信息，MT->MCU，无消息体
OSPEVENT( MT_MCU_CREATECONF_REQ,		EV_MCUMT_BGN + 180 );
//列出所有会议信息成功应答，MCU->MT，无消息体
OSPEVENT( MCU_MT_CREATECONF_ACK,		EV_MCUMT_BGN + 181 );
//列出所有会议信息失败应答，无消息体
OSPEVENT( MCU_MT_CREATECONF_NACK,		EV_MCUMT_BGN + 182 );

//至终端短消息通知，MCU->MT，消息体为结构TMt+短消息结构
OSPEVENT( MCU_MT_SENDMSG_NOTIF,			EV_MCUMT_BGN + 184 );
//终端复位命令，MCU->MT，消息体为结构TMt+单字节
OSPEVENT( MCU_MT_RESETDECODER_CMD,		EV_MCUMT_BGN + 185 );
//终端至终端短消息命令，MT->MCU，消息体为结构TMt(源)+TMt(目的)+短消息结构
//TMt: MCU和终端号都为0表示发给所有会议终端，只终端号为0发给MCU下所有终端，都不为0发给指定终端
OSPEVENT( MT_MCU_SENDMSG_CMD,			EV_MCUMT_BGN + 186 );
//终端至会议控制台短消息命令，MT->MCU，消息体为结构TMt+短消息结构
OSPEVENT( MT_MCU_SENDMCMSG_CMD,			EV_MCUMT_BGN + 187 );

//开始混音，MCU->MT，无消息体
OSPEVENT( MCU_MT_STARTMIX_CMD,			EV_MCUMT_BGN + 228 );
//停止混音，MCU->MT，无消息体
OSPEVENT( MCU_MT_STOPMIX_CMD,			EV_MCUMT_BGN + 229 );
//设置终端码率 TBitRate
OSPEVENT( MCU_MT_SETBITRATE_CMD,			EV_MCUMT_BGN + 230 );

//向终端请求I帧
//OSPEVENT( MCU_MT_SENDIFRAME_NOTIF,			EV_MCUMT_BGN + 230 );

//主席终端命令MCU进行终端静音设置，MT->MCU，消息体为结构ITSatMtId+cmd
//1：MUTE，2：NOTMUTE
OSPEVENT( MT_MCU_MTMUTE_CMD,		EV_MCUMT_BGN + 343 );
//主席终端命令MCU进行终端哑音设置，MT->MCU，消息体为结构ITSatMtId+cmd
//1：MUTE，2：NOTMUTE
OSPEVENT( MT_MCU_MTDUMB_CMD,		EV_MCUMT_BGN + 345 );

/*******************************SPECIAL FOR SATELLATE MCU***********************/
//MCU到终端的拓扑通知，消息体TSatMtTopo数组
OSPEVENT( MCU_MT_TOPO_NOTIF,								EV_MCUMT_BGN + 800 );
//MCU到终端的会议列表通知，消息体u8数组
OSPEVENT( MCU_MT_CONFLIST_NOTIF,							EV_MCUMT_BGN + 801 );
//MCU到终端的终端状态通知，消息体CSatMtStatus
OSPEVENT( MCU_MT_MTSTATUS_NOTIF,							EV_MCUMT_BGN + 802 );
//MCU到终端的会议状态通知，消息体CSatConfInfo
OSPEVENT( MCU_MT_CONFSTATUS_NOTIF,							EV_MCUMT_BGN + 803 );

//终端发起画面复合的操作
//终端开始视频复合请求,MT->MCU,消息体TVMPParam
OSPEVENT( MT_MCU_STARTVMP_CMD,								EV_MCUMT_BGN + 810 );
//终端结束视频复合请求,MT->MCU,消息体空	
OSPEVENT( MT_MCU_STOPVMP_CMD ,								EV_MCUMT_BGN + 811 );
//终端请求MCU改变复合参数,MT->MCU,消息体TVMPParam	
OSPEVENT( MT_MCU_CHANGEVMPPARAM_CMD,							EV_MCUMT_BGN + 812 );
//终端命令MCU开始把画面合成图像广播,MT->MCU,消息体空
OSPEVENT( MT_MCU_STARTVMPBRDST_CMD,							EV_MCUMT_BGN + 813 );
//会议控制台命令MCU停止把画面合成图像广播,MT->MCU,消息体空
OSPEVENT( MT_MCU_STOPVMPBRDST_CMD,							EV_MCUMT_BGN + 814 );

//终端发起混音操作
//终端命令请求混音，MT->MCU,消息体空
OSPEVENT( MT_MCU_STARTMIX_CMD,							EV_MCUMT_BGN + 820 );
//终端停止混音,MT->MCU,消息体空
OSPEVENT( MT_MCU_STOPMIX_CMD,							EV_MCUMT_BGN + 821 );

//会议签到
//MCU要求终端签到,MCU->MT,消息体为空
OSPEVENT( MCU_MT_SIGNNOW_CMD,							EV_MCUMT_BGN + 830);
//终端签到,MT->MCU,消息体为TMt
OSPEVENT( MT_MCU_SIGNNOW_NOTIF,							EV_MCUMT_BGN + 831);
//终端指定会议发言人间隔，MT->MCU,消息体为u8(秒为单位)
OSPEVENT( MT_MCU_SPECSPEAKERINTERV_CMD,					EV_MCUMT_BGN + 840);
//MT给MCU摄像头控制，消息体为Cmd(u8)+CmdVal(u8) 
OSPEVENT( MT_MCU_CAMCTRL_CMD,					EV_MCUMT_BGN + 841);

/*
 *	以下为广播消息
 */
//广播TOPO消息，前4字节为时间(MCU启动时填写),TInterfaceMtTopo数组
#define EV_SAT_MCUMT_TOPO_IND MCU_MT_TOPO_NOTIF
//广播终端密码，ITSatMtKey数组
#define EV_SAT_MCUMT_KEY_IND MCU_MT_KEY_NOTIF
//会议列表信息, ITSatTransAddr(MCU 信令地址和端口)+ITSatConfList数组
#define EV_SAT_MCUMT_CONFLIST_IND MCU_MT_CONFLIST_NOTIF
//会议信息，ITSatConfInfo＋地址信息
#define EV_SAT_MCUMT_CONFINFO_IND MCU_MT_CONFSTATUS_NOTIF
/*
 *	以下消息为MT--MCU间消息
 */
//创建会议消息，消息体为ITSateConfInfo
#define EV_SAT_MTMCU_CREATECONF_CMD MT_MCU_CREATECONF_REQ

//设置终端码率，消息体为ITSatBitrate
#define EV_SAT_MCUMT_BITRATE_IND MCU_MT_SETBITRATE_CMD 

//MCU要求终端签到，消息体为ITSatMtId
#define EV_SAT_MCUMT_SIGNNOW_CMD MCU_MT_SIGNNOW_CMD 

//MT给MCU签到应答，消息体为ITSatMtId
#define EV_SAT_MTMCU_SIGNNOW_IND MT_MCU_SIGNNOW_NOTIF

//MT给MCU申请发言，消息体为NULL
#define EV_SAT_MCUMT_APPLYSPEAKER_CMD MT_MCU_APPLYSPEAKER_CMD

//MT给MCU申请主席，消息体为NULL
#define EV_SAT_MTMCU_APPLYCHAIR_CMD MT_MCU_APPLYCHAIRMAN_REQ

//MT给MCU指定发言人，消息体为ITSatMtId
#define EV_SAT_MTMCU_SPECSPEAKER_CMD MT_MCU_SPECSPEAKER_REQ

//MT给MCU取消发言人，消息体为NULL
#define EV_SAT_MTMCU_CANCELSPEAKER_CMD MT_MCU_CANCELSPEAKER_CMD

//MT给MCU指定主席，消息体为ITSatMtId
#define EV_SAT_MTMCU_SPECCHAIRMAN_CMD MT_MCU_SPECCHAIRMAN_REQ

//MT给MCU取消主席，消息体为NULL
#define EV_SAT_MTMCU_CANCELCHAIRMAN_CMD MT_MCU_CANCELCHAIRMAN_CMD

//MT给MCU开始画面复合，消息体为ITMtList
#define EV_SAT_MTMCU_SETVMP_CMD MT_MCU_STARTVMP_CMD
//MT给MCU停止画面复合，消息体为NULL
#define EV_SAT_MTMCU_STOPVMP_CMD MT_MCU_STOPVMP_CMD

//MT给MCU开始混音，消息体为NULL
#define EV_SAT_MTMCU_SETMIX_CMD MT_MCU_STARTMIX_CMD
//MT给MCU停止混音，消息体为NULL
#define EV_SAT_MTMCU_STOPMIX_CMD MT_MCU_STOPMIX_CMD

//MT给MCU添加终端，消息体为ITSatMtId
#define EV_SAT_MTMCU_INVITEMT_CMD MT_MCU_ADDMT_CMD

//MT给MCU申请加入会议，消息体为NULL
#define EV_SAT_MTMCU_APPLYJOINCONF_CMD MT_MCU_APPLYJOINCONF_REQ

//MT给MCU申请退会，消息体为NULL
#define EV_SAT_MTMCU_APPLYLEAVECONF_CMD MT_MCU_APPLYQUITCONF_CMD

//MT给MCU结束会议，消息体为NULL
#define EV_SAT_MTMCU_QUITCONF_CMD MT_MCU_DROPCONF_CMD

//MT给MCU端消息，消息体为ITSatMtId,NULL(给会控)
#define EV_SAT_MTMCU_MESSAGE_IND MT_MCU_SENDMSG_CMD

//MT给MCU摄像头控制，消息体为Cmd(u8)+CmdVal(u8) 
#define EV_SAT_MTMCU_CAMCTRL_CMD    MT_MCU_CAMCTRL_CMD

//至终端短消息通知，MCU->MT，消息体为ITSatShortMsg
#define EV_SAT_MCUMT_MSG_IND  MCU_MT_SENDMSG_NOTIF

//MCU通知主席其他终端申请主席，MCU->MT，消息体为ITSatMtId
#define EV_SAT_MCUMT_APPLYCHAIR_IND MCU_MT_APPLYCHAIRMAN_NOTIF

//MCU通知主席其他终端申请主席，MCU->MT，消息体为ITSatMtId
#define EV_SAT_MCUMT_APPLYSPEAKER_IND MCU_MT_APPLYSPEAKER_NOTIF
//向终端请求关键帧，MCU->MT，消息体为ITSatMsgHdr
#define EV_SAT_MCUMT_SENDIFRAME_CMD MCU_MT_SENDIFRAME_NOTIF
#endif//!_EVENT_SATELLITE_MCU_MT_H_