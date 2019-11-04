/*****************************************************************************
模块名      : CMS控制台
文件名      : umsSession.h
相关文件    : 
文件实现功能: 一个ums的会话,1.连接UMS 2.监控整个连接过程，有断链则发出通知 3.控制所有直接和UMS交互的接口（发送消息等）
作者        : 俞锦锦
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2011/4/25  1.0          俞锦锦      创建
******************************************************************************/

#if !defined(AFX_UMSSESSION_H__5CE4C0CD_7295_4920_931F_35AFEF812B15__INCLUDED_)
#define AFX_UMSSESSION_H__5CE4C0CD_7295_4920_931F_35AFEF812B15__INCLUDED_
#include "umclib.h" 
#include "msgdriver.h"
#include "umssessionctrlif.h"

#include "confTemplateCtrlIF.h"
#include "confCtrlIF.h"
#include "userCtrlIF.h"
#include "tvwCtrlIF.h"
#include "umsConfigCtrlIF.h"
#include "cncaddrbookif.h"
#include "umsexportCtrlIF.h"
#include "umssysinfoCtrlIF.h"
#include "umstvwboardCtrlIF.h"
#include "umsboardCtrlIF.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUmsSession:public  CUmsSessionCtrlIF,
                  public  CMsgDriver
{

/** @defgroup  USMSession 实现部分
 *  @{
 */

public:
	CUmsSession( u16 wAppID = AID_CMS2UMS_APP, BOOL bUseAddr = TRUE );
	virtual ~CUmsSession();

public: 

  /**
	* 功能   连接到UMS 
	* @param [in]  dwIP	被连接UMS的IP地址，主机序
	* @param [in]  strUser 用户名	
	* @param [in]  strPwd	密码
	* @return u16 成功返回0;失败返回非0错误码 
	*/
	virtual u16 ConnectUms(u32 dwIP, u16 dwPort,  LPCTSTR pStrUserName,
	                        	 LPCTSTR pStrUserPswd, BOOL32 bConnect = TRUE);


  /**
    * 功能:	断开与UMS的连接
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks	在没有连接到UMS时调用此方法，不起任何作用
	*/
	virtual u16 DisconnectUms() ; 


  /**
	* 功能:	查询是否初始话完成
	* @return  TRUE:初始话完成   FALSE:没有初始话完成
    */
	virtual BOOL IsInitFinish();
  

	/**
	* 功能:	查询是否已连接UMS
	* @return  TRUE 	已连接UMS    FALSE	没有连接UMS
    */
	virtual BOOL IsConnectedUms();



  /**
	* 功能:	用户是否是管理员
	* @return  TRUE是管理员    FALSE一般用户
	*/
	virtual BOOL IsManagerUser();
    




  /**
	* 功能:	获取接口模块
	* @param [out]  接口模块对应的指针
	* @return  u16 成功返回0,失败返回非0错误码
    */
    virtual u16 GetCtrlInterface(CConfTemplateCtrlIF **ppCtrl) const;
	virtual u16 GetCtrlInterface(CConfCtrlIF **ppCtrl) const;
	virtual u16 GetCtrlInterface(CTvwCtrlIF **ppCtrl) const;
	virtual u16 GetCtrlInterface(CUserCtrlIF **ppCtrl) const;
	virtual u16 GetCtrlInterface(CUmsConfigCtrlIF **ppCtrl) const;
	virtual u16 GetCtrlInterface(CCncAddrbookIF **ppCtrl) const;
	virtual u16 GetCtrlInterface(CUmsSysInfoCtrlIF **ppCtrl) const;
	virtual u16 GetCtrlInterface(CUmsExportCtrlIF **ppCtrl) const;
	virtual u16 GetCtrlInterface(CUmsTvwBoardCtrlIF **ppCtrl) const;
	virtual u16 GetCtrlInterface(CUmsBoardCtrlIF **ppCtrl) const;
	virtual u16 GetCtrlInterface(CUmsNetMngCtrlIF **ppCtrl) const;
	virtual u16 GetCtrlInterface(CUmsVTRCtrlIF **ppCtrl) const;

	/**
	* 功能:	获取ums 的IP 
	* @return  u32  IP
    */
	virtual u32 GetUmsIP();

    
  /**
	* 功能:	获取本地 的IP 
	* @return  u32  IP
    */
	virtual u32 GetLocalIP() ;


	/**
	* 功能:	获取登录的用户信息
	* @return   
    */
	virtual const CLoginRequest& GetConnectedUser();


  /**
	* 功能:	向ums发送消息接口 
	* @param [in]  消息类型
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 一般情况下该消息可以不回复，如果确认需要回复的使用postCommand()接口发送
    */
   	u16  PostMsg( u32 dwType  = TYPE_CMESSAGE ); 
  
  /**
	* 功能:	向UI发送消息
	* @param [in]  消息
	* @return  无
	* @remarks 一般情况下该消息可以不回复，如果确认需要回复的使用postCommand()接口发送
    */
	virtual void DispEvent(const CMessage &cMsg)  ;
	virtual void OnTimeOut(u16 wEvent);
	
protected:
	void  OnLinkBreak( const CMessage& cMsg);
    void  OnConnectRsp( const CMessage& cMsg );
    void  OnGrabLoginNotify(const CMessage& cMsg);
	void  OnUmsCommonReasonInd(const CMessage& cMsg);
private:
	
 
  /**
	* 功能:	初始化OSP,创建app 
	* @return  成功返回0，失败返回错误码  
    */
	virtual u16 InitializeLib( u16 wAppID = AID_CMS2UMS_APP );
 
  /**
	* 功能:	注册消息响应函数
	* @return  无
    */
	void  BuildEventsMap();
	 
   
private: 
	BOOL32 m_bSelfInitOsp;  ///<是否是自身做了initosp
	BOOL32 m_bLogin;        ///<是否已经登录
	u32    m_dwLocalIP;
	u32    m_dwUmsIp;
	BOOL32 m_bUseAdddr;     //是否使用地址簿,默认使用
	
    CConfTemplateCtrlIF *m_pConfTemplate;
	CConfCtrlIF         *m_pConf;
	CTvwCtrlIF          *m_pTvw;
	CUserCtrlIF         *m_pUser;
    CUmsConfigCtrlIF    *m_pConfig;
	CCncAddrbookIF      *m_pAddr;
	CUmsSysInfoCtrlIF   *m_pUmsSysInfo;
    CUmsExportCtrlIF    *m_pUmsExport;
	CUmsTvwBoardCtrlIF  *m_pUmsTvwBoard;
	CUmsBoardCtrlIF     *m_pUmsSingleBoard;
	CUmsNetMngCtrlIF    *m_pUmsNetMng;
	CUmsVTRCtrlIF		*m_pUmsVTR;
    CLoginRequest m_cUser; ///<身份验证

/** @}*/   //umsSession实现部分
};

#endif // !defined(AFX_UMSSESSION_H__5CE4C0CD_7295_4920_931F_35AFEF812B15__INCLUDED_)
