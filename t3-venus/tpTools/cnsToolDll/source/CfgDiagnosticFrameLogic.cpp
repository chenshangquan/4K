// CfgDiagnosticFrameLogic.cpp: implementation of the CCfgDiagnosticFrameLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CfgDiagnosticFrameLogic.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCfgDiagnosticFrameLogic::CCfgDiagnosticFrameLogic()
{
	m_strLstFunMenu = "CfgDiagnosticFrameMenuDlg/LstCfgDiagnosticFrameFuncMenu";
}

CCfgDiagnosticFrameLogic::~CCfgDiagnosticFrameLogic()
{
	
}

void CCfgDiagnosticFrameLogic::RegCBFun()
{
	CCfgDiagnosticFrameLogic *pThis =  GetSingletonPtr();
	
    REG_GOBAL_MEMBER_FUNC( "CCfgDiagnosticFrameLogic::InitWnd", CCfgDiagnosticFrameLogic::InitWnd, pThis, CCfgDiagnosticFrameLogic ) ;
	//列表按钮点击事件
	REG_LIST_CALLFUNC( "CCfgDiagnosticFrameLogic::OnClickInterfaceDiagnostic", CCfgDiagnosticFrameLogic::OnClickInterfaceDiagnostic, pThis, CCfgDiagnosticFrameLogic ) ;
	REG_LIST_CALLFUNC( "CCfgDiagnosticFrameLogic::OnClickNetDiagnostic", CCfgDiagnosticFrameLogic::OnClickNetDiagnostic, pThis, CCfgDiagnosticFrameLogic ) ;
	REG_LIST_CALLFUNC( "CCfgDiagnosticFrameLogic::OnClickNetPacket", CCfgDiagnosticFrameLogic::OnClickNetPacket, pThis, CCfgDiagnosticFrameLogic ) ;
}

void CCfgDiagnosticFrameLogic::UnRegFunc()
{
	UN_REG_GOBAL_FUNC( "CCfgDiagnosticFrameLogic::InitWnd" );
}

bool CCfgDiagnosticFrameLogic::InitWnd(const IArgs & arg)
{
	CLogicBase::InitWnd( arg );
	InitCfgFuncMenu();
	UIFACTORYMGR_PTR->ShowWindow( g_strDiagInterfaceDlg );
	UIFACTORYMGR_PTR->ShowWindow( g_strNetDiagnosticDlg ,false);
	UIFACTORYMGR_PTR->ShowWindow( g_strNetPacketDlg ,false);
	m_strCurWnd = g_strDiagInterfaceDlg;
	m_strCfgCurWnd = g_strDiagInterfaceDlg;
	return true;
}

void CCfgDiagnosticFrameLogic::Clear()
{
	m_strCfgCurWnd = g_strDiagInterfaceDlg;
	if ( m_pWndTree != NULL )
	{	
		UIFACTORYMGR_PTR->LoadScheme( "SchStartStatistics", m_pWndTree );
		UIFACTORYMGR_PTR->LoadScheme( "SchStartPacket", m_pWndTree);
		UIFACTORYMGR_PTR->LoadScheme( "SchExportPacket", m_pWndTree);
		UIFACTORYMGR_PTR->LoadScheme( "SchmConfMenuListDefault", m_pWndTree );   //登陆后初始化默认页面
	}
}

void CCfgDiagnosticFrameLogic::HideAllWnd()
{
	UIFACTORYMGR_PTR->ShowWindow( g_strDiagInterfaceDlg, false);
	UIFACTORYMGR_PTR->ShowWindow( g_strNetDiagnosticDlg, false);
	UIFACTORYMGR_PTR->ShowWindow( g_strNetPacketDlg , false);
}

void CCfgDiagnosticFrameLogic::InitCfgFuncMenu()
{
	ARRAY<TMenuItem> aryItem;
	TMenuItem item; 	
	item.SetItemName("接口诊断" );  
	item.SetItemType("ImageItemMenuInterfaceDiagnostic"); 
	aryItem.push_back(item);
	
	item.SetItemName("网络诊断" );  
	item.SetItemType("ImageItemMenuNetDiagnostic"); 
	aryItem.push_back(item);
	
	item.SetItemName("网口抓包" );  
	item.SetItemType("ImageItemMenuNetPacket");
	aryItem.push_back(item);
	
	Value_ItemMenu valueMenu( &aryItem ); 
	valueMenu.m_strAlgroithm = IAlgorithm::strVert;
	UIFACTORYMGR_PTR->SetPropertyValue( valueMenu, m_strLstFunMenu, m_pWndTree ); 
}

bool CCfgDiagnosticFrameLogic::OnClickInterfaceDiagnostic(const IArgs& args)
{
	SwitchCfgTabWnd(g_strDiagInterfaceDlg);
	return true;
}

bool CCfgDiagnosticFrameLogic::OnClickNetDiagnostic(const IArgs& args)
{
	SwitchCfgTabWnd(g_strNetDiagnosticDlg);
	return true;
}

UINT threadGetCapturefileSize(LPVOID lpParam)
{
	CNETPACKETLOGIC->SetCaptureFileSize();
	return 0;
}

bool CCfgDiagnosticFrameLogic::OnClickNetPacket(const IArgs& args)
{
	SwitchCfgTabWnd(g_strNetPacketDlg);
	//CNETPACKETLOGIC->SetCaptureFileSize();
	AfxBeginThread(threadGetCapturefileSize,NULL);
	return true;
}

void CCfgDiagnosticFrameLogic::SwitchCfgTabWnd(string strWnd)
{
	HideAllWnd();
	UIFACTORYMGR_PTR->ShowWindow(strWnd);
	m_strCurWnd = strWnd;
	m_strCfgCurWnd = strWnd;
}

