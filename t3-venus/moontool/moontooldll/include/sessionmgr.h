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

#include "rkclib.h"

class CMoonlibSessionMgr
{
public:
	static CMoonlibSessionMgr* GetSingleTon();
	~CMoonlibSessionMgr();
 
	void CreateSession();
	void DestroySession();
	CRkcSessionCtrlIF* GetSessionIF() const					{ return m_pMoonSessionIF; }
    CRkcSysCtrlIF* GetSysCtrlIF() const                       { return m_pSysCtrlIf; }
	CCamConfigIF* GetCamConfigIF() const                        { return m_pCamConfigIF; }
	CSysConfigIF* GetSysConfigIF() const						{ return m_pSysConfigIF; }
	

private:
	CMoonlibSessionMgr();
private:
 	static CMoonlibSessionMgr	*m_pThis;
 	CRkcSessionCtrlIF	*m_pMoonSessionIF;

    CRkcSysCtrlIF *m_pSysCtrlIf;
	CCamConfigIF *m_pCamConfigIF;
	CSysConfigIF *m_pSysConfigIF;
};

#define MOONSESSION_MGR_PTR CMoonlibSessionMgr::GetSingleTon()
 
#endif