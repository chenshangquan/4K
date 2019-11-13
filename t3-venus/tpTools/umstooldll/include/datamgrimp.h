/*****************************************************************************
模块名      : CDataMgrImp
文件名      : datamgrimp.h
相关文件    : 
文件实现功能: umstool 数据管理模块
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2012/11/21     1.0         刘德印      创建
******************************************************************************/

#if !defined(AFX_COMMONMGRIF_H__25AF60AB_76A1_4E49_B81C_E81E55B0A801__INCLUDED_)
#define AFX_COMMONMGRIF_H__25AF60AB_76A1_4E49_B81C_E81E55B0A801__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "umclib.h" 

class CDataMgrImp : public CWnd, public ISingleTon<CDataMgrImp>
{
public:
	CDataMgrImp();
	virtual ~CDataMgrImp();

	/*=============================================================================
    函 数 名:CreateDataMgr
    功    能:得到数据管理指针
    参    数:无
    注    意:无
    返 回 值:CDataMgrImp*
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/11/21  1.0     刘德印    创建
    =============================================================================*/
	BOOL CreateDataMgr();

	/*=============================================================================
    函 数 名:DestroyDataMrg
    功    能:销毁数据管理指针
    参    数:无
    注    意:无
    返 回 值:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/11/21  1.0     刘德印    创建
    =============================================================================*/
    void DestroyDataMrg();

	HWND GetRecvWnd();

	
	//---------------CUmsConfigCtrl业务数据------------------
	TTPEthnetInfo		GetEthnetCfgData();
	TTPSipRegistrarCfg  GetSipCfgData();
	TTPGKCfg			GetGkCfgData();
	TTPTime				GetUmsSystimeData();

	//---------------CUmsSysInfoCtrl业务数据----------------
	TUmsVersion			GetUmsVerData();
	TToolSysInfo		GetUmsSysInfoData();
	std::pair<int,int>  GetAuthCountData();
	u32				    GetConfCountData();

	//---------------CUmsBoardCtrl业务数据----------------
	TTPBrdUsedInfo		GetUmsBoardUsedData();
	TTPBrdUsedInfo		GetUmsTvwUsedData();

	//---------------CUmsTvwBoardCtrl业务数据----------------
	std::multimap<u8,THduCfg> GetUmsTvwBoardData();
	THduStyleData GetUmsTvwStyleData();

	//---------------CUmsNetMngCtrl业务数据----------------
	u16 GetUmsNetMngData( vector<TTPNMServerCfg> &vecTTPNMServerCfg );

	//---------------CUmsVTRCtrl业务数据----------------
	u16 GetUmsVTRData( vector<TVcrCfg> &vecTVcrCfg );

protected:
    virtual BOOL PreCreateWindow( CREATESTRUCT& cs );
    virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam); 

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDataMgrImp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

};

#define DATAMGRPTR    CDataMgrImp::GetSingletonPtr()               //数据指针

#endif // !defined(AFX_COMMONMGRIF_H__25AF60AB_76A1_4E49_B81C_E81E55B0A801__INCLUDED_)
