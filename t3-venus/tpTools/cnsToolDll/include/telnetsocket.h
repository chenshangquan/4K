// Telnetsocket.h: interface for the CTelnetSocket class.
//
//////////////////////////////////////////////////////////////////////

/*****************************************************************************
模块名      : 抓包相关模块（和服务器交互）
文件名      : telnetsocket.h
相关文件    : netcapture.h
文件实现功能: 远程登录服务器，给服务器发送抓包命令
作者        : 杨奇峰
版本        : V1.0  Copyright(C) 2012-2016 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2016/8/15      1.0					   创建
******************************************************************************/

#ifndef _TELNET_SOCKET_H_
#define _TELNET_SOCKET_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "netcapture.h"
#include  <afxsock.h>

class CTelnetSocket : public CAsyncSocket
{
public:
	CTelnetSocket();
	virtual ~CTelnetSocket();
	
	void SetLoginInfo(TLoginInfo& tInfo);	//设置登陆消息
	
	s8* GetRcvBuf();                 
	
	void ConnectRemote();       //远程登陆服务器
	
	virtual void Close();      
	
protected:
	virtual void OnClose(int nErrorCode);           
	virtual void OnConnect(int nErrorCode);  //登陆服务器
	virtual void OnOutOfBandData(int nErrorCode);  //越界
	virtual void OnReceive(int nErrorCode);   //收到服务器错误消息
	virtual void OnSend(int nErrorCode);      //发送给服务器出错消息
	
	void    OnReceiveMsgFromT300e(s8* ach);          //对来自服务器T300E的消息进行回应
	
protected:		
	TLoginInfo   m_tLoginInfo;
	TRcvBuf     *m_pRcvBuf;

	s8          m_nLoginNum;             //登录次数
	s8          m_nCdRamdiskNum;		 //进入/ramdisk/目录次数
	s8          m_nCmdStartNum;		     //发送抓包命令次数
};


#endif //_TELNET_SOCKET_H_
