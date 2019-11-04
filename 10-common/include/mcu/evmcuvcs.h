/*****************************************************************************
   模块名      : mcu
   文件名      : evmcuvcs.h
   相关文件    : 
   文件实现功能: MCU与VCS接口消息定义
   作者        : 付秀华
   版本        : 
-----------------------------------------------------------------------------
   修改记录:
   日  期      版本        修改人      修改内容
   2008/11/20              付秀华      创建
******************************************************************************/
#ifndef _EVMCUVCS_H_
#define _EVMCUVCS_H_

#include "osp.h"
#include "eventid.h"

/*------------------------------------------------------------------------------
 MCU与VCS接口消息
------------------------------------------------------------------------------*/

//1 用户管理采取MCS与MCU交互的消息, 但消息体为CVCSUsrInfo
//2 用户组管理采取MCS与MCU交互的消息及消息体


//3 会议模板管理采取MCS与MCU交互的消息，但消息体如下
//VCS创建模板，     //消息体: TConfInfo + 2 byte(网络序,TMtAlias数组打包长度,即下面的n)
//                  + n 个(TMtAlias数组打包,依次为 1byte(别名类型)+1byte(别名长度)+xbyte(别名字符串)+2byte(呼叫码率)) 
//                  + TMultiTvWallModule(可选字段，由会议属性中的是否有电视墙模板决定) 
//                  + TVmpModule(可选字段，由会议属性中的是否有画面合成墙模板决定)
//                  + 1byte(u8: 0 1  是否配置了高清电视墙)
//                  + (可选, THDTvWall)
//                  + 1byte(u8: 会议配置HDU的通道总数)
//                  + (可选, THduModChnlInfo+...)
//                  + 1byte(是否为级联调度)＋(可选，2byte[u16 网络序，配置打包的总长度]+下级mcu[1byte(别名类型)+1byte(别名长度)+xbyte(别名字符串)+2byte(呼叫码率)...)])
//                  + 1byte(是否支持分组)＋(可选，2byte(u16 网络序，信息总长)+内容(1byte(组数)+n组[1TVCSGroupInfo＋m个TVCSEntryInfo])

//4 创建会议
   //VCS在MCU上按会议模板创建一个即时会议, 无消息体                
    OSPEVENT( VCS_MCU_CREATECONF_BYTEMPLATE_REQ,		EV_VCSVC_BGN + 1 );
    //会议模板成功地转变成即时会议, 无消息体 
    OSPEVENT( MCU_VCS_CREATECONF_BYTEMPLATE_ACK,		EV_VCSVC_BGN + 2 );
    //会议模板转变成即时会议失败, 无消息体
    OSPEVENT( MCU_VCS_CREATECONF_BYTEMPLATE_NACK,       EV_VCSVC_BGN + 3 );


// 5 调度操作，会议中消息
	// VCS请求对某调度席开始操作       消息体：无(根据消息头中CConfId)
	OSPEVENT( VCS_MCU_OPRCONF_REQ,              EV_VCSVC_BGN + 10 );
	// VCS请求对某调度席开始操作的应答 消息体：无
	OSPEVENT( MCU_VCS_OPRCONF_ACK,              EV_VCSVC_BGN + 11 );
	// VCS请求对某调度席开始操作的应答 消息体：无
	OSPEVENT( MCU_VCS_OPRCONF_NACK,             EV_VCSVC_BGN + 12 );

	// VCS请求退出调度席               消息体：无(根据消息头中CConfId)
	OSPEVENT( VCS_MCU_QUITCONF_REQ,             EV_VCSVC_BGN + 13 );
	// VCS请求退出调度席的应答         消息体：无
	OSPEVENT( MCU_VCS_QUITCONF_ACK,             EV_VCSVC_BGN + 14 );
	// VCS请求退出调度席的应答         消息体：无
	OSPEVENT( MCU_VCS_QUITCONF_NACK,            EV_VCSVC_BGN + 15 );

	//VCS请求会议的调度模式,    消息体：无
	OSPEVENT( VCS_MCU_VCMODE_REQ,               EV_VCSVC_BGN + 20 );
	//VCS请求会议的调度模式应答,消息体：u8(VCS_SINGLE_MODE，VCS_MULTW_MODE，VCS_MULVMP_MODE)
	OSPEVENT( MCU_VCS_VCMODE_ACK,               EV_VCSVC_BGN + 21 );
	//VCS请求会议的调度模式应答,消息体：无
	OSPEVENT( MCU_VCS_VCMODE_NACK,              EV_VCSVC_BGN + 22 );

	//VCS更改会议的调度模式，   消息体：u8(VCS_SINGLE_MODE，VCS_MULTW_MODE，VCS_MULVMP_MODE)
    OSPEVENT( VCS_MCU_CHGVCMODE_REQ,            EV_VCSVC_BGN + 23 );
	//VCS更改会议的调度模式应答
	OSPEVENT( MCU_VCS_CHGVCMODE_ACK,            EV_VCSVC_BGN + 24 );
	//VCS更改会议的调度模式应答,消息体：无
	OSPEVENT( MCU_VCS_CHGVCMODE_NACK,           EV_VCSVC_BGN + 25 );
	//VCS更改会议的调度模式通告,消息体：u8
	OSPEVENT( MCU_VCS_CHGVCMODE_NOTIF,          EV_VCSVC_BGN + 26 );
	
	//VCS调度指定的终端,         消息体：TMt(调度终端的信息) + u8(操作类型:VCS_VCTYPE_DEFAULT, VCS_VCTYPE_DROPMT)
	//                                   u8(强拆类型:VCS_FORCECALL_REQ, VCS_FORCECALL_CMD)
	OSPEVENT( VCS_MCU_VCMT_REQ,                 EV_VCSVC_BGN + 27 );
	//VCS调度指定的终端的应答,   消息体：TMt(调度终端的信息) + u8(操作类型)
	//                                   u8(强拆类型:VCS_FORCECALL_REQ, VCS_FORCECALL_CMD)
	OSPEVENT( MCU_VCS_VCMT_ACK,                 EV_VCSVC_BGN + 28 );
	//VCS调度指定的终端应答,     消息体：仅ERR_MCU_VCS_VCMTING含消息体TMt(上一个调度终端的信息)
	OSPEVENT( MCU_VCS_VCMT_NACK,                EV_VCSVC_BGN + 29 );
	//VCS调度结果通告，          消息体：仅ERR_MCU_VCS_VCMTOVERTIME含消息体TMt(上一个调度终端的信息)(含错误码)
	OSPEVENT( MCU_VCS_VCMT_NOTIF,               EV_VCSVC_BGN + 30 );

	//VCS会议状态通告            消息体：CBasicVCCStatus
	OSPEVENT( MCU_VCS_CONFSTATUS_NOTIF,         EV_VCSVC_BGN + 31 );

	//VCS会议请求静音/哑音       消息体：u8(请求时的调度模式)+u8(开启(1)/关闭(0))
	//                                  +u8(VCS_OPR_LOCAL/VCS_OPR_REMOTE)+u8(VCS_AUDPROC_MUTE/VCS_AUDPROC_SILENCE)
	OSPEVENT( VCS_MCU_MUTE_REQ,                 EV_VCSVC_BGN + 40 );
	//VCS会议请求静音/哑音应答   消息体： 无
	OSPEVENT( MCU_VCS_MUTE_ACK,                 EV_VCSVC_BGN + 41 );
	//VCS会议请求静音/哑音应答   消息体： 无(含错误码，如模式已切换，操作取消)
	OSPEVENT( MCU_VCS_MUTE_NACK,                EV_VCSVC_BGN + 42 );

// 6 
	//软件名称自定义 
	OSPEVENT( VCS_MCU_GETSOFTNAME_REQ  ,        EV_VCSVC_BGN + 60 );
	OSPEVENT( MCU_VCS_GETSOFTNAME_ACK  ,        EV_VCSVC_BGN + 61 );
	OSPEVENT( MCU_VCS_GETSOFTNAME_NACK,         EV_VCSVC_BGN + 62 );

	OSPEVENT( VCS_MCU_CHGSOFTNAME_REQ  ,        EV_VCSVC_BGN + 63 );
	OSPEVENT( MCU_VCS_CHGSOFTNAME_ACK  ,        EV_VCSVC_BGN + 64 );
    OSPEVENT( MCU_VCS_CHGSOFTNAME_NACK ,        EV_VCSVC_BGN + 65 );

	OSPEVENT( VCS_MCU_SOFTNAME_NOTIF   ,        EV_VCSVC_BGN + 66 );

// 组呼操作, 会议中
	//VCS请求MCU批量增加并组呼终端,   消息体：  u8(组数)+u8(组名长度)+s8字符串(组名)+u8(终端数)+TMt数组+
	//                                          ...
	OSPEVENT( VCS_MCU_GROUPCALLMT_REQ,            EV_VCSVC_BGN + 70 );
	//MCU同意批量增加并组呼终端,      消息体：  无
	OSPEVENT( MCU_VCS_GROUPCALLMT_ACK,            EV_VCSVC_BGN + 71 );
	//MCU拒绝批量增加并组呼终端,      消息体：  无
	OSPEVENT( MCU_VCS_GROUPCALLMT_NACK,           EV_VCSVC_BGN + 72 );
	//通告                            消息体:   组名(含失败错误码)
	OSPEVENT( MCU_VCS_GROUPCALLMT_NOTIF ,           EV_VCSVC_BGN + 73 );

	//VCS请求MCU批量挂断组呼终端,     消息体： u8(组数)+u8(组名长度)+s8字符串(组名)+u8(终端数)+TMt数组+
	//                                          ...
	OSPEVENT( VCS_MCU_GROUPDROPMT_REQ,            EV_VCSVC_BGN + 75 );
	//MCU同意批量挂断组呼终端,        消息体：  无
	OSPEVENT( MCU_VCS_GROUPDROPMT_ACK,            EV_VCSVC_BGN + 76 );
	//MCU拒绝批量挂断呼终端,          消息体：  无
	OSPEVENT( MCU_VCS_GROUPDROPMT_NACK,           EV_VCSVC_BGN + 77 );

	//VCS请求MCU临时增加终端,    消息体：  TAddMtInfo
	OSPEVENT( VCS_MCU_ADDMT_REQ,                EV_VCSVC_BGN + 80 );
	//MCU同意增加终端,           消息体：  无
	OSPEVENT( MCU_VCS_ADDMT_ACK,                EV_VCSVC_BGN + 81 );
	//MCU拒绝增加终端,           消息体：  无
	OSPEVENT( MCU_VCS_ADDMT_NACK,               EV_VCSVC_BGN + 82 );

	//VCS请求MCU删除终端,        消息体：  TMt
	//VCS需要保证请求删除的终端非调度模式中的可调度资源
	OSPEVENT( VCS_MCU_DELMT_REQ,                EV_VCSVC_BGN + 85 );
	//MCU同意增加终端,           消息体：  无
	OSPEVENT( MCU_VCS_DELMT_ACK,                EV_VCSVC_BGN + 86 );
	//MCU拒绝增加终端,           消息体：  无
	OSPEVENT( MCU_VCS_DELMT_NACK,               EV_VCSVC_BGN + 87 );

	//VCS开启主席轮询,               消息体：  u8(轮询间隔)
	OSPEVENT( VCS_MCU_STARTCHAIRMANPOLL_REQ,     EV_VCSVC_BGN + 90 );
	//MCU同意开启主席轮询,           消息体：  无
	OSPEVENT( MCU_VCS_STARTCHAIRMANPOLL_ACK,      EV_VCSVC_BGN + 91 );
	//MCU拒绝开启主席轮询,           消息体：  无(含错误码)
	OSPEVENT( MCU_VCS_STARTCHAIRMANPOLL_NACK,     EV_VCSVC_BGN + 92 );

	//VCS停止主席轮询,               消息体：  无
	OSPEVENT( VCS_MCU_STOPCHAIRMANPOLL_REQ,     EV_VCSVC_BGN + 95 );
	//MCU同意停止主席轮询,           消息体：  无
	OSPEVENT( MCU_VCS_STOPCHAIRMANPOLL_ACK,      EV_VCSVC_BGN + 96 );
	//MCU拒绝停止主席轮询,           消息体：  无
	OSPEVENT( MCU_VCS_STOPCHAIRMANPOLL_NACK,     EV_VCSVC_BGN + 97 );
	
// 其它
    // 同意强拆请求                   消息体:   TMt(请求释放的终端) + s8[](请求抢占的会议名称)
	OSPEVENT( MCU_VCS_RELEASEMT_REQ,             EV_VCSVC_BGN + 100 );
    // 同意强拆                       消息体:   TMt(请求释放的终端) + s8[](请求抢占的会议名称)
	OSPEVENT( VCS_MCU_RELEASEMT_ACK,             EV_VCSVC_BGN + 101 );
	// 拒绝强拆                       消息体:　 TMt(请求释放的终端) + s8[](请求抢占的会议名称)　
	OSPEVENT( VCS_MCU_RELEASEMT_NACK,            EV_VCSVC_BGN + 102 );
	// 强拆执行通告                   消息体:   TMt(请求释放的终端) + s8[](请求抢占的会议名称)
	OSPEVENT( MCU_VCS_RELEASEMT_NOTIF,           EV_VCSVC_BGN + 103 );
 
// 7 为界面保存mcu不处理信息
    //VCS请求获取不处理信息，        消息体：  无
    OSPEVENT( VCS_MCU_GETUNPROCFGINFO_REQ,       EV_VCSVC_BGN + 150 );
    //请求获取不处理信息成功,        消息体：  s8[] 实际内容
    OSPEVENT( MCU_VCS_GETUNPROCFGINFO_ACK,       EV_VCSVC_BGN + 151 );
    //请求获取不处理信息失败,        消息体：  无
    OSPEVENT( MCU_VCS_GETUNPROCFGINFO_NACK ,     EV_VCSVC_BGN + 152 );

    //VCS请求mcu保存不处理信息，     消息体：  s8[] 实际内容
    OSPEVENT( VCS_MCU_SETUNPROCFGINFO_REQ,       EV_VCSVC_BGN + 153 );
    //请求保存mcu不处理信息成功,     消息体：  无
    OSPEVENT( MCU_VCS_SETUNPROCFGINFO_ACK,       EV_VCSVC_BGN + 154 );
    //请求保存mcu不处理信息失败,     消息体：  无  
    OSPEVENT( MCU_VCS_SETUNPROCFGINFO_NACK,      EV_VCSVC_BGN + 155 );
    //mcu不处理信息通告,             消息体：  s8[] 实际内容
    OSPEVENT( MCU_VCS_SETUNPROCFGINFO_NOTIF,     EV_VCSVC_BGN + 156 );


#endif /*_EVMCUVCS_H_*/


