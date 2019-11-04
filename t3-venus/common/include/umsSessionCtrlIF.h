/*****************************************************************************
模块名      : CMS控制台
文件名      : umsSessionCtrlIF.h
相关文件    : 
文件实现功能: 一个ums的会话,1.连接UMS 2.监控整个连接过程，有断链则发出通知 3.控制所有直接和UMS交互的接口（发送消息等）
作者        : 俞锦锦
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2011/4/25  1.0          俞锦锦      创建
******************************************************************************/

#if !defined(AFX_UMSSESSIONCTRLIF_H__8A75E9D0_6535_4DD2_A298_1BE3D2D80850__INCLUDED_)
#define AFX_UMSSESSIONCTRLIF_H__8A75E9D0_6535_4DD2_A298_1BE3D2D80850__INCLUDED_
#include "kdvdispevent.h"

#include "conftemplatectrlif.h"
#include "confctrlif.h"
#include "umsconfigctrlif.h"
#include "tvwctrlif.h"
#include "userctrlif.h"
#include "cncaddrbookif.h"
#include "umsexportCtrlIF.h"
#include "umssysinfoCtrlIF.h"
#include "umstvwboardCtrlIF.h"
#include "umsboardCtrlIF.h"
#include "umsNetMngCtrlIF.h"
#include "umsVTRCtrlIF.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CUmsSessionCtrlIF:public  CKdvDispEvent 
{
public:
 
/** @defgroup  umsSession接口
 *  @{
 */


  /**
	* 功能   连接到UMS 
	* @param [in]  dwIP	被连接UMS的IP地址，主机序
	* @param [in]  strUser 用户名	
	* @param [in]  strPwd	密码
	* @return u16 成功返回0;失败返回非0错误码 
	*/
	virtual u16 ConnectUms(u32 dwIP, u16 dwPort,   LPCTSTR pStrUserName,
	                         LPCTSTR pStrUserPswd, BOOL32 bConnect = TRUE) = 0;


   /**
    * 功能:	断开与UMS的连接
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	在没有连接到UMS时调用此方法，不起任何作用
	*/
	virtual u16 DisconnectUms() = 0; 
   
	/**
	* 功能:	获取接口模块
	* @param [out]  接口模块对应的指针
	* @return  u16 成功返回0,失败返回非0错误码
    */
    virtual u16 GetCtrlInterface(CConfTemplateCtrlIF **ppCtrl) const = 0;
	virtual u16 GetCtrlInterface(CConfCtrlIF **ppCtrl) const = 0;
	virtual u16 GetCtrlInterface(CTvwCtrlIF **ppCtrl) const = 0;
	virtual u16 GetCtrlInterface(CUserCtrlIF **ppCtrl) const = 0;
	virtual u16 GetCtrlInterface(CUmsConfigCtrlIF **ppCtrl) const = 0;
	virtual u16 GetCtrlInterface(CCncAddrbookIF **ppCtrl) const = 0;
	virtual u16 GetCtrlInterface(CUmsSysInfoCtrlIF **ppCtrl) const = 0;
	virtual u16 GetCtrlInterface(CUmsExportCtrlIF **ppCtrl) const = 0;
	virtual u16 GetCtrlInterface(CUmsTvwBoardCtrlIF **ppCtrl) const = 0;
	virtual u16 GetCtrlInterface(CUmsBoardCtrlIF **ppCtrl) const = 0;
	virtual u16 GetCtrlInterface(CUmsNetMngCtrlIF **ppCtrl) const = 0;
	virtual u16 GetCtrlInterface(CUmsVTRCtrlIF **ppCtrl) const = 0;

 
	/**
	* 功能:	查询是否初始话完成
	* @return  TRUE:初始话完成   FALSE:没有初始话完成
    */
	virtual BOOL IsInitFinish() = 0;

 
  /**
	* 功能:	查询是否已连接UMS
	* @return  TRUE 	已连接UMS    FALSE	没有连接UMS
    */
	virtual BOOL IsConnectedUms() = 0;



 /**
	* 功能:	用户是否是管理员
	* @return  TRUE是管理员    FALSE一般用户
	*/
	virtual BOOL IsManagerUser() = 0;

  /**
	* 功能:	获取ums 的IP 
	* @return  u32  IP
    */
	virtual u32 GetUmsIP() = 0;


	/**
	* 功能:	获取本地 的IP 
	* @return  u32  IP
    */
	virtual u32 GetLocalIP() = 0;


	/**
	* 功能:	获取登录的用户信息
	* @return   
    */
	virtual const CLoginRequest& GetConnectedUser() = 0;
 
/** @}*/  //umsSession 接口
};

#endif // !defined(AFX_UMSSESSIONCTRLIF_H__8A75E9D0_6535_4DD2_A298_1BE3D2D80850__INCLUDED_)
