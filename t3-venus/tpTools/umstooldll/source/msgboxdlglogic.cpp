// msgboxdlglogic.cpp: implementation of the CMsgboxDlgLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "umstooldll.h"
#include "msgboxdlglogic.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
 
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMsgboxDlgLogic::CMsgboxDlgLogic():
m_strStcMsgboxShowText("StcMsgboxShowText") 
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

bool CMsgboxDlgLogic::RegCBFun()
{   	 
	REG_GOBAL_MEMBER_FUNC( "CMsgboxDlgLogic::InitWnd", CMsgboxDlgLogic::InitWnd, MSGBOXLOGICRPTR, CMsgboxDlgLogic);

	REG_GOBAL_MEMBER_FUNC( "CMsgboxDlgLogic::OnBtnOk", CMsgboxDlgLogic::OnBtnOk, MSGBOXLOGICRPTR, CMsgboxDlgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CMsgboxDlgLogic::OnBtnCancel", CMsgboxDlgLogic::OnBtnCancel, MSGBOXLOGICRPTR, CMsgboxDlgLogic ); 

	return true;
}

bool CMsgboxDlgLogic::UnRegFunc()
{

	return true;
}


bool CMsgboxDlgLogic::InitWnd(  const IArgs & arg )
{   
	CWndLogicBase::InitWnd( arg );

    return true;
}

void CMsgboxDlgLogic::Clear()
{
	s32 nResult = 0;
	UIFACTORYMGR_PTR->Endmodal(nResult, g_stcMsgboxDlg );
	m_nMsgBoxRet = MSGBOX_CANCEL;
}

bool CMsgboxDlgLogic::OnBtnOk( const IArgs & arg )
{
	s32 nResult = 0;
	UIFACTORYMGR_PTR->Endmodal(nResult, g_stcMsgboxDlg );

	m_nMsgBoxRet = MSGBOX_OK;

	return true;
}

bool CMsgboxDlgLogic::OnBtnCancel( const IArgs & arg )
{
	s32 nResult = 0;
	UIFACTORYMGR_PTR->Endmodal(nResult, g_stcMsgboxDlg );

	m_nMsgBoxRet = MSGBOX_CANCEL;

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