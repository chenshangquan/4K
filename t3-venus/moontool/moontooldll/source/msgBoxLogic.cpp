// msgBoxLogic.cpp: implementation of the CMsgBoxLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "moonToolDll.h"
#include "msgBoxLogic.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
   

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMsgboxDlgLogic::CMsgboxDlgLogic()
				:m_strStcMsgboxShowText("StcMsgboxShowText") 
{
	m_nMsgBoxRet = MSGBOX_CANCEL;
}

CMsgboxDlgLogic::~CMsgboxDlgLogic()
{
	UnRegMsg();
	UnRegFunc();
}


void CMsgboxDlgLogic::RegMsg()
{    
}

void CMsgboxDlgLogic::UnRegMsg()
{

}

void CMsgboxDlgLogic::RegCBFun()
{   	 
	CMsgboxDlgLogic *m_pLogic = GetSingletonPtr();
	REG_GOBAL_MEMBER_FUNC( "CMsgboxDlgLogic::InitWnd", CMsgboxDlgLogic::InitWnd, m_pLogic, CMsgboxDlgLogic);

	REG_GOBAL_MEMBER_FUNC( "CMsgboxDlgLogic::OnBtnOk", CMsgboxDlgLogic::OnBtnOk, m_pLogic, CMsgboxDlgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CMsgboxDlgLogic::OnBtnCancel", CMsgboxDlgLogic::OnBtnCancel, m_pLogic, CMsgboxDlgLogic ); 

}

void CMsgboxDlgLogic::UnRegFunc()
{

}


bool CMsgboxDlgLogic::InitWnd(  const IArgs & arg )
{   
	CLogicBase::InitWnd( arg );

    return true;
}

void CMsgboxDlgLogic::Clear()
{
	m_nMsgBoxRet = MSGBOX_CANCEL;
	UIFACTORYMGR_PTR->Endmodal(m_nMsgBoxRet, g_stcMsgboxDlg );

}

bool CMsgboxDlgLogic::OnBtnOk( const IArgs & arg )
{
 
	m_nMsgBoxRet = MSGBOX_OK;
	UIFACTORYMGR_PTR->Endmodal(m_nMsgBoxRet, g_stcMsgboxDlg );

	return true;
}

bool CMsgboxDlgLogic::OnBtnCancel( const IArgs & arg )
{
	m_nMsgBoxRet = MSGBOX_CANCEL;
	UIFACTORYMGR_PTR->Endmodal(m_nMsgBoxRet, g_stcMsgboxDlg ); 

	return true;
}

void CMsgboxDlgLogic::ShowMsgBox( MSGBOX_RET& nResult, const String& strText )
{
	UIFACTORYMGR_PTR->LoadScheme( "SchmDefBtnStyle", m_pWndTree );
	UIFACTORYMGR_PTR->SetCaption( m_strStcMsgboxShowText, strText, m_pWndTree );
	
	BOOL bIsVisible = UIFACTORYMGR_PTR->IsVisible( g_stcMsgboxDlg );
	if ( !bIsVisible )
	{
		UIFACTORYMGR_PTR->Domodal( g_stcMsgboxDlg );
	}

	nResult = m_nMsgBoxRet;
}

void CMsgboxDlgLogic::ShowMsgBoxNoBtn( const String& strText  )
{
	UIFACTORYMGR_PTR->LoadScheme( "SchmNoBtnStyle", m_pWndTree );
	UIFACTORYMGR_PTR->SetCaption( m_strStcMsgboxShowText, strText, m_pWndTree );
	
	BOOL bIsVisible = UIFACTORYMGR_PTR->IsVisible( g_stcMsgboxDlg );
	if ( !bIsVisible )
	{
		UIFACTORYMGR_PTR->Domodal( g_stcMsgboxDlg );
	}
}

void CMsgboxDlgLogic::ShowMsgBoxOk( const String& strText )
{
	UIFACTORYMGR_PTR->LoadScheme( "SchmOnlyOkBtnStyle", m_pWndTree );
	UIFACTORYMGR_PTR->SetCaption( m_strStcMsgboxShowText, strText, m_pWndTree );
	
	BOOL bIsVisible = UIFACTORYMGR_PTR->IsVisible( g_stcMsgboxDlg );
	if ( !bIsVisible )
	{
		UIFACTORYMGR_PTR->Domodal( g_stcMsgboxDlg );
	}
}

void CMsgboxDlgLogic::ShowMsgBoxOnlyRead( const String& strText )
{
	UIFACTORYMGR_PTR->LoadScheme( "SchmOnlyRead", m_pWndTree );
	UIFACTORYMGR_PTR->SetCaption( m_strStcMsgboxShowText, strText, m_pWndTree );
	
	BOOL bIsVisible = UIFACTORYMGR_PTR->IsVisible( g_stcMsgboxDlg );
	if ( !bIsVisible )
	{
		UIFACTORYMGR_PTR->Domodal( g_stcMsgboxDlg );
	}
}
