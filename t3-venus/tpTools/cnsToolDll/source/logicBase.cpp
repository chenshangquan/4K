#include "StdAfx.h"

#include "logicBase.h"

//template<> CLogicBase* Singleton<CLogicBase>::ms_pSingleton = NULL;


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


String CLogicBase::m_strCurWnd = "";
bool CLogicBase::IsAllE164Number( String strText )
{
	LPCTSTR  lpstr  =  (LPCTSTR)strText.c_str(); 
	
    s32 nLen = _tcslen( lpstr );
    if ( nLen == 0 )
    {
        return false;
    }
	
    s32 nIndex = _tcsspn( lpstr, _T("0123456789*,") );
	
	if ( nLen == nIndex )
	{
		return true;
	}
	return false;
}

//  ; /   ?   : @ & = + $ , % ¡­¡­ & ^ ¿Õ¸ñ tab
bool CLogicBase::IsValidTPStr( String strText )
{
	CString strError = INVALID_ALIAS_FOR_CODE;
	CString str(strText.c_str());
	CString strRe = str.SpanExcluding( strError );
	if ( strRe != str )
	{
		return false;
	} 
    return true;
}

void CLogicBase::CheckData( String strCtrlName, bool bChange )
{
	if ( bChange )
	{
		if ( true != FindCtrlName( strCtrlName ) )
		{
			m_vctWndName.push_back( strCtrlName );
		} 
	}
	else
	{
		if ( true == FindCtrlName( strCtrlName ) )
		{
			DelVctWndName( strCtrlName );
		}
	}
	UpBtnState();
}

bool CLogicBase::FindCtrlName( String strWindow )
{
	vector<String>::iterator it = m_vctWndName.begin();
	while( it != m_vctWndName.end() )
	{
		if ( 0 == strcmp( it->c_str(), strWindow.c_str() ) )
		{	
			return true;
		}
		it++;
	}
	return false;
}

void CLogicBase::DelVctWndName( String strWindow )
{
	vector<String>::iterator it = m_vctWndName.begin();
	while( it != m_vctWndName.end() )
	{
		if ( 0 == strcmp( it->c_str(), strWindow.c_str() ) )
		{	
			m_vctWndName.erase( it );
			return;
		}
		it++;
	}
}

bool CLogicBase::UpBtnState()
{
	Value_WindowEnable valEnableBtn;
	s32 n = m_vctWndName.size();
	if ( 0 == n )
	{	
		valEnableBtn.bEnable = false;
		UIFACTORYMGR_PTR->SetPropertyValue( valEnableBtn, "BtnSave", m_pWndTree );
		UIFACTORYMGR_PTR->SetPropertyValue( valEnableBtn, "BtnCancle", m_pWndTree );
	} 
	else
	{
		valEnableBtn.bEnable = true;
		UIFACTORYMGR_PTR->SetPropertyValue( valEnableBtn, "BtnSave", m_pWndTree );
		UIFACTORYMGR_PTR->SetPropertyValue( valEnableBtn, "BtnCancle", m_pWndTree );
	}
	return true;
}
 