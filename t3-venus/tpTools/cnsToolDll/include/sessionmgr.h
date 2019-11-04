/*****************************************************************************
模块名      : 创建cnclib中各个功能类的接口
文件名      : sessionmgr.h
相关文件    : cnclib.h
文件实现功能: 供外部访问cnclib
作者        : 景洋洋
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2012/11/23     1.0						创建
******************************************************************************/
#ifndef __SESSIONMGR_H__
#define __SESSIONMGR_H__

#include "cnclib.h"

class CCnclibSessionMgr
{
public:
	static CCnclibSessionMgr* GetSingleTon();
	~CCnclibSessionMgr();
 
	void CreateSession();
	void DesdroySession();
	CCnsSessionCtrlIF* GetSessionIF() const					{ return m_pCnsSessionIF; }
	CCncConfigIF* GetConfigIF() const						{ return m_pCnsConfigIF; }
	CCncConfCtrlIF* GetConfCtrlIF() const					{ return m_pCnsConfIF; }
	CCncSipInfoCtrlIF* GetSipInfoCtrlIF() const				{ return m_pSipInfoIF; }
	CCncPortDiagCtrlIF* GetPortDiagCtrlIF() const			{ return m_pPortDiagIF; }
	CCncSysCtrlIF* GetSysCtrlIF() const						{ return m_pSysCtrlIF; }
	CCncCenterCtrlIF* GetCenterCtrlIF() const				{ return m_pCenterCtrlIF; }
	CCncNetMngCtrlIF* GetNetMngCtrlIF() const				{ return m_pNetMngCtrlIF; }
private:
	CCnclibSessionMgr();
private:
 	static CCnclibSessionMgr	*m_pThis;
 	CCnsSessionCtrlIF	*m_pCnsSessionIF;
	CCncConfigIF        *m_pCnsConfigIF;
	CCncConfCtrlIF      *m_pCnsConfIF;
	CCncSipInfoCtrlIF   *m_pSipInfoIF;
	CCncPortDiagCtrlIF	*m_pPortDiagIF;
	CCncSysCtrlIF       *m_pSysCtrlIF;
	CCncCenterCtrlIF    *m_pCenterCtrlIF;
	CCncNetMngCtrlIF	*m_pNetMngCtrlIF;
};

#define CNCSESSION_MGR_PTR CCnclibSessionMgr::GetSingleTon()
 
#endif