#ifndef _VCSLIBCOM_H_
#define _VCSLIBCOM_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "kdvtype.h"
#include "evvcspcmt.h"
#include "evmcslib.h"

//vcslib消息
enum emVcsLibUIMsg
{
    em_VcsLibUIMsgBgn   =   VCSLIB_DISP_MSG_BGN,

    VCSLIB_VCS_PCMTCONNECTED_ACK,
    VCSLIB_VCS_PCMTENTRYCONF_NOTIFY,
	VCSLIB_VCS_PCMTQIUTCONF_NOTIFY,
	VCSLIB_VCS_PCMTDISCONNECT_NOTIFY,
	VCSLIB_VCS_PCMTINITOK_NOTIFY,

    em_VcsLibUIMsgEnd = VCSLIB_DISP_MSG_END,
};

//pcmt的应答方式类型
enum EmTripMode
{
    emTripModeAuto      =0,  //自动
	emTripModeManu      =1,  //手动 
	emTripModeNegative  =2,   //拒绝、关闭
};



//全局函数定义    
u16 InitVcslib(BOOL32 bOpenTelnet = FALSE);



#endif/*_VCSLIBCOM_H_*/
