/*****************************************************************************
模块名      : umstool网呈维护工具
文件名      : umsexportCtrl.h
相关文件    : 
文件实现功能: ums导入导出的所有操作
作者        : 刘德印
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2012/11/23  1.0         刘德印      创建
******************************************************************************/
#if !defined(AFX_EXPORTCTRL_H__EB116E65_7B63_4B3E_B267_9C0B112DA0C1__INCLUDED_)
#define AFX_EXPORTCTRL_H__EB116E65_7B63_4B3E_B267_9C0B112DA0C1__INCLUDED_

#include "umsexportCtrlIF.h"
#include "umsSession.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUmsExportCtrl :public CUmsExportCtrlIF 
{  

/** @defgroup  操作ums导入导出接口实现部分
 *  @{
 */


	friend class CUmsSession;
private:
	CUmsExportCtrl( const CUmsExportCtrl &){};
    CUmsExportCtrl( CUmsSession &cUmsSession );
	
public:
    ~CUmsExportCtrl();
	
	/**
    * 功能:  导出会议模板请求
	* @param [in]	void
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   CMS->UMS  ev_UMSAddUserReq 此消息直接用OSP发送，不经过XML编解码 \n
	                      应回复:UMS->CMS   ev_UMSAddUserRet \n
	                      若成功，还应回复:UMS->CMS   ev_UmsAddUser_Notify
	*/
	virtual u16  ExportInfoReq();

	/**
    * 功能:  导入会议模板请求
	* @param [in]	const s8* strFileName	 会议模板文件名称 
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   CMS->UMS  ev_UMSAddUserReq 此消息直接用OSP发送，不经过XML编解码 \n
	                      应回复:UMS->CMS   ev_UMSAddUserRet \n
	                      若成功，还应回复:UMS->CMS   ev_UmsAddUser_Notify
	*/
	virtual u16  ImportInfoReq(const s8* strFileName);

	/**
    * 功能:  导出授权请求
	* @param [in]	void
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   CMS->UMS  ev_licenseOutput_req 此消息直接用OSP发送，不经过XML编解码 \n
	                      应回复:UMS->CMS   ev_licenseOutput_Ind \n
	*/
	virtual u16  ExportAuthReq();

protected:
 
  /**
    * 功能:	  
	* @param [out]  cMsg	消息
	* @return  无
	* @remarks   
	*/
	void  OnExportInfoRsp(const CMessage& cMsg);

 
  /**
    * 功能:	  
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
    void  OnImportInfoRsp(const CMessage& cMsg);

	/**
    * 功能:	  
	* @param [out]  cMsg	消息
	* @return  无
	* @remarks   
	*/
	void  OnExportAuthRsp(const CMessage& cMsg);

	virtual void DispEvent(const CMessage &cMsg);
	
    virtual void OnTimeOut(u16 wEvent); 
   

    void  OnLinkBreak(const CMessage& cMsg);
private:
 
	/**
    * 功能:	  注册消息响应函数
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
	void  BuildEventsMap();

private:
	CUmsSession *m_pUmsSession;              
 
/** @}*/ // 操作ums导入导出接口实现部分
};

#endif // !defined(AFX_EXPORTCTRL_H__EB116E65_7B63_4B3E_B267_9C0B112DA0C1__INCLUDED_)
