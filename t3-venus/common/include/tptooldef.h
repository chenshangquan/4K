/*****************************************************************************
模块名      : tptooldef
文件名      : tptooldef.h
相关文件    : 
文件实现功能: tptool库公共定义
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2012/12/11     1.0         刘德印      创建
******************************************************************************/
#ifndef TPTOOLDEF_H 
#define TPTOOLDEF_H

///////////////////////////与tptool通用交互消息////////////////////////////////
enum TPTOOLMSG
{
	em_TPTOOL_LOGINRESULT = TPTOOL_MSG_BEGIN + 0x01,
#define WM_TPTOOL_LOGINRESULT em_TPTOOL_LOGINRESULT      //tptool登陆结果  EM_LOGIN__TYPE:登陆消息类型  其他错误码  lParam:错误原因   默认注销不需要提醒 直接赋0   抢占则填写抢占的IP

	em_TPTOOL_LOGOFF,
#define WM_TPTOOL_LOGOFF em_TPTOOL_LOGOFF                //tptool注销事件

	em_TPTOOL_LOGGRAB,
#define WM_TPTOOL_LOGGRAB em_TPTOOL_LOGGRAB              //tptool抢占事件

};


enum EM_SERVERAPP_TYPE      //当前登陆的服务器类型
{
	em_UMSTOOL_APP,
	em_CNSTOOL_APP,
	em_MOONTOOL_APP
};

enum EM_LOGIN__TYPE      //登陆类型
{
	em_LOGIN_SUCCESS,    //登陆成功
	em_LOGIN_ERROR_RSQ,  //登陆结果
	em_LOGIN_TIMEOUT,	 //登陆超时
	em_LOGIN_LOGOFF,	 //注销
	em_LOGIN_GRAP,		 //抢占
	em_LOGIN_REFUSE,     //抢登被拒绝
	em_LOGIN_EXCEPTION,  //登陆异常
	em_LOGIN_BREAK		 //与服务器断开
};


#endif