/*=============================================================================
模   块   名: vcs和pcmt公用头文件
文   件   名: evvcspcmt.h 
相 关  文 件: 
文件实现功能: 主要是消息号定义
作        者: 陈建辉
注        意: 目前vcs发高清每日，而pcmt发r5，所以该文件要和高清每日上的相应文件保持一致
版        本: V1.0  Copyright(C) 2003-2009 KDC, All rights reserved.
-------------------------------------------------------------------------------
修改记录:
日      期  版本    修改人      修改内容
2009/07/14  1.0     陈建辉        创建
=============================================================================*/

#ifndef _EVMTCVCS_H_
#define _EVMTCVCS_H_


#include "osp.h"

const int    AID_VCSLIB          =   100;   //该app号不能和mcu侧的所有app相同,fix
const int    AID_PCMTLIB         =   150;   //该app号不能和mt侧的所有app相同 
        
/*Pcmtlib和VCS通信消息(0-100) */
#define EV_PCMTVCS_BGN                  0
#define EV_PTMTVCS_END                  EV_PCMTVCS_BGN + 100

/*------------------------------------------------------------------------------
 PCMTLIB与VCSLIB接口消息(1-99)
------------------------------------------------------------------------------*/
//body: none
OSPEVENT( VCS_PCMT_CONNECT_REQ,                         EV_PCMTVCS_BGN + 1 );
OSPEVENT( PCMT_VCS_CONNECT_ACK,                         EV_PCMTVCS_BGN + 2 );

OSPEVENT( VCS_PCMT_POWEROFF_CMD,                        EV_PCMTVCS_BGN + 3 );

//body:要绘制的HWND hPreview + HWND hPrimo + HWND hSecond
OSPEVENT( VCS_PCMT_SETVCSHWND_CMD,                      EV_PCMTVCS_BGN + 4 );

//body:none
OSPEVENT( PCMT_VCS_ENTRY_CONF_NOTIFY,                   EV_PCMTVCS_BGN + 5 );

//body:none
OSPEVENT( VCS_PCMT_QUITCONF_CMD,                        EV_PCMTVCS_BGN + 6 );

//body:u8 该值必须与pcmt侧的应答模式枚举值相同
OSPEVENT( VCS_PCMT_SETANSWERMODE_CMD,                   EV_PCMTVCS_BGN + 7 );

//body:none pcmt通知vcs它退出会议了
OSPEVENT( PCMT_VCS_QUITCONF_NOTIFY,                     EV_PCMTVCS_BGN + 8 );

//body:none 消息体:CammerCtrID(4字节) + CtrState(4字节)
OSPEVENT( VCS_PCMT_SET_CAMMER_CMD,                      EV_PCMTVCS_BGN + 9 );

//body:none 
OSPEVENT( VCS_PCMT_CTR_CAMMER_PRE_CMD,                  EV_PCMTVCS_BGN + 10 );

//body:none 
OSPEVENT( PCMT_VCS_INITOK_NOTIFY,				        EV_PCMTVCS_BGN + 11 );
/*------------------------------------------------------------------------------
 PCMTLIB与VCSLIB公用的宏
------------------------------------------------------------------------------*/
#define VCSLIB_LISTEN_PORT                      60100  
#define PCMTLIB_LISTEN_PORT                     60200 

enum emCammerCtrID
{
	emCtrBgn,
    emCtrUP,
    emCtrDown,
    emCtrLeft,
    emCtrRight,
    emCtrFocusAuto,
    emCtrFocusFar,
    emCtrFocusNear,
    emCtrZommOut,
    emCtrZoomIn,
    emCtrBrightLow,
    emCtrBrightHigh,   
};

typedef struct tagCammeralCtr 
{
	tagCammeralCtr(emCammerCtrID emCtrId=emCtrBgn, BOOL32 bCtrState=FALSE): m_emCtrId(emCtrId), m_CtrState(bCtrState) {};

	emCammerCtrID	m_emCtrId;
	BOOL32			m_CtrState;

}TCammeralCtr;

#endif