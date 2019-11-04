/*==========================================================
模块名  ：updatecmc
文件名  ：updatecmcconst.h
相关文件：
实现功能：updatecmc和loadcmc的公共数据
作者	：肖楚然
版权	：
-------------------------------------------------------------------------------------------------------
修改记录:
   日  期      版本        修改人      修改内容
  2011/11/23   1.0         肖楚然        创建 
==========================================================*/
#ifndef UPDATECMCCONST_H
#define UPDATECMCCONST_H

#include "msgIdDispatch.h"

//消息事件定义
enum EmUpdateCmcEvent
{
	ev_UpdatecmcEvent_Start = 0,                  //事件定义开始

	ev_LoginLoadCmc_Req,                          //登录
	ev_LoginLoadCmc_Rsp,
	ev_LogoutLoadCmc_Req,

	ev_RebootCmc_Cmd,                             //重启cmc

	ev_UpdateOver_Nty,                            //更新完毕

	ev_TimeOut,                                   //超时

	ev_UpdatecmcEvent_End,                        //事件定义结束
};


enum EmUiUpdateCmcMsg
{
	#define UI_UPDATECMC_MSG_BEGIN    UPDATECMC_MSG_BEGIN

	UI_UPDATECMC_CONNECTED  =  UI_UPDATECMC_MSG_BEGIN,

	UI_UPDATECMC_DISCONNECTED,

	UI_UPDATECMC_OVER,

	UI_REBOOTCMC_CMD,

	UI_FTP_PROGRESS,

	UI_UPDATECMC_MSG_END,
};


#define CONNETCT_PORT   6666                  //服务器监听端口
#define TIMEOUT         3000                  //超时时间

#define BUF_SIZE        4096

typedef struct tagAddress
{
	u32 dwIP;
	u16 wPort;
	tagAddress()
	{
		dwIP = 0;
		wPort = 0;
	}
}TAddr;



#endif //UPDATECMCCONST_H