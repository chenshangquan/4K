/*****************************************************************************
模块名      : CSessionIns
文件名      : sessionins.h
相关文件    : 
文件实现功能: umstool 全局Session模块
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2012/11/21     1.0         刘德印      创建
******************************************************************************/
#if !defined(AFX_SESSIONINS_H__B1C93EC9_9BDD_40C7_BA07_694169421352__INCLUDED_)
#define AFX_SESSIONINS_H__B1C93EC9_9BDD_40C7_BA07_694169421352__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSessionIns : public ISingleTon<CSessionIns>
{
public:
	CSessionIns();
	virtual ~CSessionIns();

public:

	/*=============================================================================
    函 数 名:CreateSession
    功    能:创建与Ums通信会话
    参    数:无
    注    意:无
    返 回 值:return BOOL 成功返回TRUE;失败返回FALSE
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/11/21  1.0     刘德印    创建
    =============================================================================*/
	BOOL  CreateSession( u16 wAppId = AID_UMSTOOL2UMS_APP );


	/*=============================================================================
    函 数 名:DisConnectUms
    功    能:创建与Ums通信会话
    参    数:无
    注    意:无
    返 回 值:return BOOL 成功返回TRUE;失败返回FALSE
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/11/21  1.0     刘德印    创建
    =============================================================================*/
	BOOL  DisConnectUms();

	/*=============================================================================
    函 数 名:DesdroySession
    功    能:销毁与Ums通信会话
    参    数:无
    注    意:无
    返 回 值:return BOOL 成功返回TRUE;失败返回FALSE
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/11/21  1.0     刘德印    创建
    =============================================================================*/
	void DesdroySession();

	CUmsSessionCtrlIF* GetSessionCtrlPtr(){ return m_pUmsSessCtrlIF;};
	CUserCtrlIF* GetUserCtrlPtr(){ return m_pUserCtrlIF;};
	CUmsSysInfoCtrlIF* GetSysInfoCtrlPtr(){ return m_pSysInfoCtrlIF;};
	CUmsTvwBoardCtrlIF* GetTvwBoardCtrlPtr(){ return m_pTvwBoardCtrlIF;};
	CUmsBoardCtrlIF* GetBoardCtrlPtr(){ return m_pBoardCtrlIFIF;};
	CUmsExportCtrlIF* GetExportCtrPtr(){ return m_pExportCtrlIF;};
	CUmsConfigCtrlIF* GetConfigCtrlPtr(){ return m_pConfigCtrlIF;};
	CUmsNetMngCtrlIF* GetNetMngCtrlPtr(){ return m_pNetMngCtrlIF;};
	CUmsVTRCtrlIF* GetVTRCtrlPtr(){ return m_pVTRCtrlIF;};

private:
	CUmsSessionCtrlIF*    m_pUmsSessCtrlIF;		    //ums的会话端接口
    CUserCtrlIF*	      m_pUserCtrlIF;			//ums用户控制接口
	CUmsSysInfoCtrlIF*    m_pSysInfoCtrlIF;         //ums系统信息接口
	CUmsTvwBoardCtrlIF*   m_pTvwBoardCtrlIF;        //ums电视墙板卡接口
	CUmsBoardCtrlIF*      m_pBoardCtrlIFIF;         //ums单板接口
	CUmsExportCtrlIF*     m_pExportCtrlIF;          //ums导入导出接口
	CUmsConfigCtrlIF*     m_pConfigCtrlIF;          //ums配置接口
	CUmsNetMngCtrlIF*     m_pNetMngCtrlIF;			//ums网管接口
	CUmsVTRCtrlIF*		  m_pVTRCtrlIF;				//ums录像机接口


};

#define SESSIONPTR    CSessionIns::GetSingletonPtr()     //Session指针

#endif // !defined(AFX_SESSIONINS_H__B1C93EC9_9BDD_40C7_BA07_694169421352__INCLUDED_)
