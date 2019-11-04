// cfgEqLogic.cpp: implementation of the CCfgEqLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cfgEqLogic.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCfgEqLogic::CCfgEqLogic()
: m_strBtnEq1Switch("DlgEqualizer1/BtnEq1")
, m_strBtnEq2Switch("DlgEqualizer2/BtnEq2")
, m_strBtnEq3Switch("DlgEqualizer3/BtnEq3")
{
	m_vctWndName.clear();
}

CCfgEqLogic::~CCfgEqLogic()
{

}

bool CCfgEqLogic::InitWnd( const IArgs & arg )
{
	CLogicBase::InitWnd( arg );
	SetEqDefaultData();
	SetEqInfo();
	m_vctWndName.clear();
	UpBtnState();
	return true;
}

void CCfgEqLogic::RegMsg()
{
	CCfgEqLogic* pThis = GetSingletonPtr();
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_AudEqualizer_NTY, CCfgEqLogic::OnUpdateEqNty, pThis, CCfgEqLogic ); 
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_DftEq_NTY, CCfgEqLogic::OnDefaultEqNty, pThis, CCfgEqLogic ); 
}

void CCfgEqLogic::UnRegMsg()
{
	
}
 
void CCfgEqLogic::RegCBFun()
{
	CCfgEqLogic *pThis = GetSingletonPtr();
	REG_GOBAL_MEMBER_FUNC( "CCfgEqLogic::InitWnd", CCfgEqLogic::InitWnd, pThis, CCfgEqLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgEqLogic::OnBtnSave", CCfgEqLogic::OnBtnSave, pThis, CCfgEqLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgEqLogic::OnBtnCancel", CCfgEqLogic::OnBtnCancel, pThis, CCfgEqLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgEqLogic::OnBtnDefault", CCfgEqLogic::OnBtnDefault, pThis, CCfgEqLogic );
	//Slider±ä»¯
	REG_GOBAL_MEMBER_FUNC( "CCfgEqLogic::OnSld1Eq100Changed", CCfgEqLogic::OnSld1Eq100Changed, pThis, CCfgEqLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgEqLogic::OnSld1Eq200Changed", CCfgEqLogic::OnSld1Eq200Changed, pThis, CCfgEqLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgEqLogic::OnSld1Eq400Changed", CCfgEqLogic::OnSld1Eq400Changed, pThis, CCfgEqLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgEqLogic::OnSld1Eq600Changed", CCfgEqLogic::OnSld1Eq600Changed, pThis, CCfgEqLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgEqLogic::OnSld1Eq1KChanged", CCfgEqLogic::OnSld1Eq1KChanged, pThis, CCfgEqLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgEqLogic::OnSld1Eq3KChanged", CCfgEqLogic::OnSld1Eq3KChanged, pThis, CCfgEqLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgEqLogic::OnSld1Eq6KChanged", CCfgEqLogic::OnSld1Eq6KChanged, pThis, CCfgEqLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgEqLogic::OnSld1Eq12KChanged", CCfgEqLogic::OnSld1Eq12KChanged, pThis, CCfgEqLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgEqLogic::OnSld1Eq14KChanged", CCfgEqLogic::OnSld1Eq14KChanged, pThis, CCfgEqLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgEqLogic::OnSld1Eq16KChanged", CCfgEqLogic::OnSld1Eq16KChanged, pThis, CCfgEqLogic );

	REG_GOBAL_MEMBER_FUNC( "CCfgEqLogic::OnSld2Eq100Changed", CCfgEqLogic::OnSld2Eq100Changed, pThis, CCfgEqLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgEqLogic::OnSld2Eq200Changed", CCfgEqLogic::OnSld2Eq200Changed, pThis, CCfgEqLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgEqLogic::OnSld2Eq400Changed", CCfgEqLogic::OnSld2Eq400Changed, pThis, CCfgEqLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgEqLogic::OnSld2Eq600Changed", CCfgEqLogic::OnSld2Eq600Changed, pThis, CCfgEqLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgEqLogic::OnSld2Eq1KChanged", CCfgEqLogic::OnSld2Eq1KChanged, pThis, CCfgEqLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgEqLogic::OnSld2Eq3KChanged", CCfgEqLogic::OnSld2Eq3KChanged, pThis, CCfgEqLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgEqLogic::OnSld2Eq6KChanged", CCfgEqLogic::OnSld2Eq6KChanged, pThis, CCfgEqLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgEqLogic::OnSld2Eq12KChanged", CCfgEqLogic::OnSld2Eq12KChanged, pThis, CCfgEqLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgEqLogic::OnSld2Eq14KChanged", CCfgEqLogic::OnSld2Eq14KChanged, pThis, CCfgEqLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgEqLogic::OnSld2Eq16KChanged", CCfgEqLogic::OnSld2Eq16KChanged, pThis, CCfgEqLogic );

	REG_GOBAL_MEMBER_FUNC( "CCfgEqLogic::OnSld3Eq100Changed", CCfgEqLogic::OnSld3Eq100Changed, pThis, CCfgEqLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgEqLogic::OnSld3Eq200Changed", CCfgEqLogic::OnSld3Eq200Changed, pThis, CCfgEqLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgEqLogic::OnSld3Eq400Changed", CCfgEqLogic::OnSld3Eq400Changed, pThis, CCfgEqLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgEqLogic::OnSld3Eq600Changed", CCfgEqLogic::OnSld3Eq600Changed, pThis, CCfgEqLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgEqLogic::OnSld3Eq1KChanged", CCfgEqLogic::OnSld3Eq1KChanged, pThis, CCfgEqLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgEqLogic::OnSld3Eq3KChanged", CCfgEqLogic::OnSld3Eq3KChanged, pThis, CCfgEqLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgEqLogic::OnSld3Eq6KChanged", CCfgEqLogic::OnSld3Eq6KChanged, pThis, CCfgEqLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgEqLogic::OnSld3Eq12KChanged", CCfgEqLogic::OnSld3Eq12KChanged, pThis, CCfgEqLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgEqLogic::OnSld3Eq14KChanged", CCfgEqLogic::OnSld3Eq14KChanged, pThis, CCfgEqLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgEqLogic::OnSld3Eq16KChanged", CCfgEqLogic::OnSld3Eq16KChanged, pThis, CCfgEqLogic );
	//SwitchButton±ä»¯
	REG_GOBAL_MEMBER_FUNC( "CCfgEqLogic::OnBtnSwitchEq1", CCfgEqLogic::OnBtnSwitchEq1, pThis, CCfgEqLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgEqLogic::OnBtnSwitchEq2", CCfgEqLogic::OnBtnSwitchEq2, pThis, CCfgEqLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgEqLogic::OnBtnSwitchEq3", CCfgEqLogic::OnBtnSwitchEq3, pThis, CCfgEqLogic );
}

void CCfgEqLogic::UnRegFunc()
{
	UN_REG_GOBAL_FUNC( "CCfgEqLogic::InitWnd" );	
}

void CCfgEqLogic::Clear()
{
	memset( m_atEqInfo, 0, sizeof(m_atEqInfo) );
	memset( m_atOldEqInfo, 0, sizeof(m_atOldEqInfo) );
	m_vctWndName.clear();
	UpBtnState();
}

bool CCfgEqLogic::OnBtnSave( const IArgs& args )
{
	bool bEq1 = SaveEq1();
	bool bEq2 = SaveEq2();
	bool bEq3 = SaveEq3();
// 	if ( !bEq1 && !bEq2 && !bEq3 )
// 	{
// 		return false;
// 	}
	u16 wRet = COMIFMGRPTR->SetAudioEqualizerCmd( m_atEqInfo );
	if (wRet != NO_ERROR)
	{
		WARNMESSAGE( "±£´æ¾ùºâÆ÷ÅäÖÃÇëÇó·¢ËÍÊ§°Ü" );
		return false;
	}
	m_vctWndName.clear();
	UpBtnState();
	return true;
}

bool CCfgEqLogic::OnBtnDefault( const IArgs& args )
{
	memset( m_atEqInfo, 0, sizeof(m_atEqInfo) );
	SetEqDefaultData();
	memcpy( m_atEqInfo, m_atOldEqInfo, sizeof(m_atOldEqInfo) );
	u16 wRet = COMIFMGRPTR->SetDefaultEqCmd( m_atEqInfo );
	if (wRet != NO_ERROR)
	{
		WARNMESSAGE( "»Ö¸´¾ùºâÆ÷ÅäÖÃÇëÇó·¢ËÍÊ§°Ü" );
		return false;
	}
	return true;
}

bool CCfgEqLogic::OnBtnCancel( const IArgs& args )
{
	SetEqInfo();
	m_vctWndName.clear();
	UpBtnState();
	return true;	
}

bool CCfgEqLogic::IsCfgEqChange()
{
	s32 n = m_vctWndName.size();
	if ( n > 0 )
	{
		return SaveMsgBox();
	}
  	return true;
}

LRESULT CCfgEqLogic::OnUpdateEqNty( WPARAM wParam, LPARAM lParam )
{
	if ( m_vctWndName.size() > 0 )
	{
		return S_FALSE;
	}
	BOOL bSuccess = *(BOOL*)lParam;
	if ( !bSuccess )
	{
		WARNMESSAGE( "±£´æ¾ùºâÆ÷ÉèÖÃÊ§°Ü" );
		return S_FALSE;
	}
	GetEqData();
	SetEqInfo();
	return S_OK;
}

LRESULT CCfgEqLogic::OnDefaultEqNty( WPARAM wParam, LPARAM lParam )
{
	BOOL bSuccess = *(BOOL*)lParam;
	if ( !bSuccess )
	{
		WARNMESSAGE( "»Ö¸´¾ùºâÆ÷Ä¬ÈÏÉèÖÃÊ§°Ü" );
		GetEqData();
		SetEqInfo();
		return S_FALSE;
	}
	else
	{
		SetEqDefaultData();
		SetEqInfo();
		m_vctWndName.clear();
		UpBtnState();
	}
	
	return S_OK;
}

bool CCfgEqLogic::SaveMsgBox()
{
	IArgs args("");
	MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
	MSG_BOX( nMsgBoxRet, "ÅäÖÃÏîÒÑÐÞ¸Ä£¬ÊÇ·ñ±£´æÅäÖÃ£¿" );	
	if ( MSGBOX_OK == nMsgBoxRet )
	{
		return OnBtnSave(args);		 
	}
	else
	{	
		OnBtnCancel(args);
	}
	return true;
}

void CCfgEqLogic::SetEqInfo()
{
	if ( m_pWndTree == NULL )
	{
		return;
	}
	if ( m_atOldEqInfo[0].byIndex == 0 )
	{
		bool bUseEq = m_atOldEqInfo[0].bEqualizer;
		UIFACTORYMGR_PTR->SetSwitchState( m_strBtnEq1Switch, bUseEq, m_pWndTree );
		if ( bUseEq )
		{
			UIFACTORYMGR_PTR->LoadScheme( "UseEq1", m_pWndTree, "DlgEqualizer1");  
		}
		else
		{   
			UIFACTORYMGR_PTR->LoadScheme( "NoUseEq1", m_pWndTree,"DlgEqualizer1");
		}
		SetEqRate( "DlgEqualizer1/Sld1Eq100", 0, 0 );
		SetEqRate( "DlgEqualizer1/Sld1Eq200", 0, 1 );
		SetEqRate( "DlgEqualizer1/Sld1Eq400", 0, 2 );
		SetEqRate( "DlgEqualizer1/Sld1Eq600", 0, 3 );
		SetEqRate( "DlgEqualizer1/Sld1Eq1K", 0, 4 );
		SetEqRate( "DlgEqualizer1/Sld1Eq3K", 0, 5 );
		SetEqRate( "DlgEqualizer1/Sld1Eq6K", 0, 6 );
		SetEqRate( "DlgEqualizer1/Sld1Eq12K", 0, 7 );
		SetEqRate( "DlgEqualizer1/Sld1Eq14K", 0, 8 );
		SetEqRate( "DlgEqualizer1/Sld1Eq16K", 0, 9 );
	}
	if ( m_atOldEqInfo[1].byIndex == 1 )
	{
		bool bUseEq = m_atOldEqInfo[1].bEqualizer;
		UIFACTORYMGR_PTR->SetSwitchState( m_strBtnEq2Switch, bUseEq, m_pWndTree );
		if ( bUseEq )
		{
			UIFACTORYMGR_PTR->LoadScheme( "UseEq2", m_pWndTree, "DlgEqualizer2");  
		}
		else
		{   
			UIFACTORYMGR_PTR->LoadScheme( "NoUseEq2", m_pWndTree,"DlgEqualizer2");
		}
		SetEqRate( "DlgEqualizer2/Sld2Eq100", 1, 0 );
		SetEqRate( "DlgEqualizer2/Sld2Eq200", 1, 1 );
		SetEqRate( "DlgEqualizer2/Sld2Eq400", 1, 2 );
		SetEqRate( "DlgEqualizer2/Sld2Eq600", 1, 3 );
		SetEqRate( "DlgEqualizer2/Sld2Eq1K", 1, 4 );
		SetEqRate( "DlgEqualizer2/Sld2Eq3K", 1, 5 );
		SetEqRate( "DlgEqualizer2/Sld2Eq6K", 1, 6 );
		SetEqRate( "DlgEqualizer2/Sld2Eq12K", 1, 7 );
		SetEqRate( "DlgEqualizer2/Sld2Eq14K", 1, 8 );
		SetEqRate( "DlgEqualizer2/Sld2Eq16K", 1, 9 );
	} 
	if ( m_atOldEqInfo[2].byIndex == 2 )
	{
		bool bUseEq = m_atOldEqInfo[2].bEqualizer;
		UIFACTORYMGR_PTR->SetSwitchState( m_strBtnEq3Switch, bUseEq, m_pWndTree );
		if ( bUseEq )
		{
			UIFACTORYMGR_PTR->LoadScheme( "UseEq3", m_pWndTree, "DlgEqualizer3");  
		}
		else
		{   
			UIFACTORYMGR_PTR->LoadScheme( "NoUseEq3", m_pWndTree,"DlgEqualizer3");
		}
		SetEqRate( "DlgEqualizer3/Sld3Eq100", 2, 0 );
		SetEqRate( "DlgEqualizer3/Sld3Eq200", 2, 1 );
		SetEqRate( "DlgEqualizer3/Sld3Eq400", 2, 2 );
		SetEqRate( "DlgEqualizer3/Sld3Eq600", 2, 3 );
		SetEqRate( "DlgEqualizer3/Sld3Eq1K", 2, 4 );
		SetEqRate( "DlgEqualizer3/Sld3Eq3K", 2, 5 );
		SetEqRate( "DlgEqualizer3/Sld3Eq6K", 2, 6 );
		SetEqRate( "DlgEqualizer3/Sld3Eq12K", 2, 7 );
		SetEqRate( "DlgEqualizer3/Sld3Eq14K", 2, 8 );
		SetEqRate( "DlgEqualizer3/Sld3Eq16K", 2, 9 );
	}
}

bool CCfgEqLogic::OnBtnSwitchEq1( const IArgs& args )
{
	bool bUseEq = false;
    UIFACTORYMGR_PTR->GetSwitchState( m_strBtnEq1Switch, bUseEq, m_pWndTree );
    if ( bUseEq )
    {
        UIFACTORYMGR_PTR->LoadScheme( "UseEq1", m_pWndTree, "DlgEqualizer1" );  
    }
    else
    {   
        UIFACTORYMGR_PTR->LoadScheme( "NoUseEq1", m_pWndTree, "DlgEqualizer1" );
    }
	
	bool bChange = false;
	if ( (BOOL)bUseEq != m_atOldEqInfo[0].bEqualizer )
	{
		bChange = true;
	}
	
	CheckData(m_strBtnEq1Switch,bChange);
	return true;	
}

bool CCfgEqLogic::OnBtnSwitchEq2( const IArgs& args )
{
	bool bUseEq = false;
    UIFACTORYMGR_PTR->GetSwitchState( m_strBtnEq2Switch, bUseEq, m_pWndTree );
    if ( bUseEq )
    {
        UIFACTORYMGR_PTR->LoadScheme( "UseEq2", m_pWndTree, "DlgEqualizer2" );  
    }
    else
    {   
        UIFACTORYMGR_PTR->LoadScheme( "NoUseEq2", m_pWndTree, "DlgEqualizer2" );
    }
	
	bool bChange = false;
	if ( (BOOL)bUseEq != m_atOldEqInfo[1].bEqualizer )
	{
		bChange = true;
	}	
	CheckData(m_strBtnEq3Switch,bChange);
	return true;		
}

bool CCfgEqLogic::OnBtnSwitchEq3( const IArgs& args )
{
	bool bUseEq = false;
    UIFACTORYMGR_PTR->GetSwitchState( m_strBtnEq3Switch, bUseEq, m_pWndTree );
    if ( bUseEq )
    {
        UIFACTORYMGR_PTR->LoadScheme( "UseEq3", m_pWndTree, "DlgEqualizer3" );  
    }
    else
    {   
        UIFACTORYMGR_PTR->LoadScheme( "NoUseEq3", m_pWndTree, "DlgEqualizer3" );
    }
	
	bool bChange = false;
	if ( (BOOL)bUseEq != m_atOldEqInfo[2].bEqualizer )
	{
		bChange = true;
	}	
	CheckData(m_strBtnEq3Switch,bChange);
	return true;		
}

void CCfgEqLogic::GetEqData()
{
	if ( m_pWndTree == NULL )
	{
		return;
	}
	TTPEqualizer* ptEqualizer = NULL;
	LIBDATAMGRPTR->GetAudioEqualizer( &ptEqualizer );
	for ( int i = 0; i < 3; i++ )
    {
        m_atOldEqInfo[i] = *( ptEqualizer + i );        
    }
}

void CCfgEqLogic::SetEqRate( String strWndName, s32 nGroup, s32 nNum )
{
	Value_CSliderCtrlPos pos;
	pos.nPos = m_atOldEqInfo[nGroup].anEqualizerGain[nNum];
	UIFACTORYMGR_PTR->SetPropertyValue( pos,strWndName,m_pWndTree );	
}

void CCfgEqLogic::CheckEqRate( String strWndName, s32 nGroup, s32 nNum )
{
	Value_CSliderCtrlPos pos;
	UIFACTORYMGR_PTR->GetPropertyValue( pos,strWndName,m_pWndTree );
	
	bool bChange = false;
	if ( pos.nPos != m_atOldEqInfo[nGroup].anEqualizerGain[nNum] )
	{
		bChange = true;
	}	
	CheckData(strWndName,bChange);
}

bool CCfgEqLogic::OnSld1Eq100Changed( const IArgs& args )
{
	CheckEqRate( "DlgEqualizer1/Sld1Eq100", 0, 0 );
	return true;
}

bool CCfgEqLogic::OnSld1Eq200Changed( const IArgs& args )
{
	CheckEqRate( "DlgEqualizer1/Sld1Eq200", 0, 1 );
	return true;
}

bool CCfgEqLogic::OnSld1Eq400Changed( const IArgs& args )
{
	CheckEqRate( "DlgEqualizer1/Sld1Eq400", 0, 2 );
	return true;
}

bool CCfgEqLogic::OnSld1Eq600Changed( const IArgs& args )
{
	CheckEqRate( "DlgEqualizer1/Sld1Eq600", 0, 3 );
	return true;
}

bool CCfgEqLogic::OnSld1Eq1KChanged( const IArgs& args )
{
	CheckEqRate( "DlgEqualizer1/Sld1Eq1K", 0, 4 );
	return true;
}

bool CCfgEqLogic::OnSld1Eq3KChanged( const IArgs& args )
{
	CheckEqRate( "DlgEqualizer1/Sld1Eq3K", 0, 5 );
	return true;
}

bool CCfgEqLogic::OnSld1Eq6KChanged( const IArgs& args )
{
	CheckEqRate( "DlgEqualizer1/Sld1Eq6K", 0, 6 );
	return true;
}

bool CCfgEqLogic::OnSld1Eq12KChanged( const IArgs& args )
{
	CheckEqRate( "DlgEqualizer1/Sld1Eq12K", 0, 7 );
	return true;
}

bool CCfgEqLogic::OnSld1Eq14KChanged( const IArgs& args )
{
	CheckEqRate( "DlgEqualizer1/Sld1Eq14K", 0, 8 );
	return true;
}

bool CCfgEqLogic::OnSld1Eq16KChanged( const IArgs& args )
{
	CheckEqRate( "DlgEqualizer1/Sld1Eq16K", 0, 9 );
	return true;
}

bool CCfgEqLogic::OnSld2Eq100Changed( const IArgs& args )
{
	CheckEqRate( "DlgEqualizer2/Sld2Eq100", 1, 0 );
	return true;
}

bool CCfgEqLogic::OnSld2Eq200Changed( const IArgs& args )
{
	CheckEqRate( "DlgEqualizer2/Sld2Eq200", 1, 1 );
	return true;
}

bool CCfgEqLogic::OnSld2Eq400Changed( const IArgs& args )
{
	CheckEqRate( "DlgEqualizer2/Sld2Eq400", 1, 2 );
	return true;
}

bool CCfgEqLogic::OnSld2Eq600Changed( const IArgs& args )
{
	CheckEqRate( "DlgEqualizer2/Sld2Eq600", 1, 3 );
	return true;
}

bool CCfgEqLogic::OnSld2Eq1KChanged( const IArgs& args )
{
	CheckEqRate( "DlgEqualizer2/Sld2Eq1K", 1, 4 );
	return true;
}

bool CCfgEqLogic::OnSld2Eq3KChanged( const IArgs& args )
{
	CheckEqRate( "DlgEqualizer2/Sld2Eq3K", 1, 5 );
	return true;
}

bool CCfgEqLogic::OnSld2Eq6KChanged( const IArgs& args )
{
	CheckEqRate( "DlgEqualizer2/Sld2Eq6K", 1, 6 );
	return true;
}

bool CCfgEqLogic::OnSld2Eq12KChanged( const IArgs& args )
{
	CheckEqRate( "DlgEqualizer2/Sld2Eq12K", 1, 7 );
	return true;
}

bool CCfgEqLogic::OnSld2Eq14KChanged( const IArgs& args )
{
	CheckEqRate( "DlgEqualizer2/Sld2Eq14K", 1, 8 );
	return true;
}

bool CCfgEqLogic::OnSld2Eq16KChanged( const IArgs& args )
{
	CheckEqRate( "DlgEqualizer2/Sld2Eq16K", 1, 9 );
	return true;
}

bool CCfgEqLogic::OnSld3Eq100Changed( const IArgs& args )
{
	CheckEqRate( "DlgEqualizer3/Sld3Eq100", 2, 0 );
	return true;
}

bool CCfgEqLogic::OnSld3Eq200Changed( const IArgs& args )
{
	CheckEqRate( "DlgEqualizer3/Sld3Eq200", 2, 1 );
	return true;
}

bool CCfgEqLogic::OnSld3Eq400Changed( const IArgs& args )
{
	CheckEqRate( "DlgEqualizer3/Sld3Eq400", 2, 2 );
	return true;
}

bool CCfgEqLogic::OnSld3Eq600Changed( const IArgs& args )
{
	CheckEqRate( "DlgEqualizer3/Sld3Eq600", 2, 3 );
	return true;
}

bool CCfgEqLogic::OnSld3Eq1KChanged( const IArgs& args )
{
	CheckEqRate( "DlgEqualizer3/Sld3Eq1K", 2, 4 );
	return true;
}

bool CCfgEqLogic::OnSld3Eq3KChanged( const IArgs& args )
{
	CheckEqRate( "DlgEqualizer3/Sld3Eq3K", 2, 5 );
	return true;
}

bool CCfgEqLogic::OnSld3Eq6KChanged( const IArgs& args )
{
	CheckEqRate( "DlgEqualizer3/Sld3Eq6K", 2, 6 );
	return true;
}

bool CCfgEqLogic::OnSld3Eq12KChanged( const IArgs& args )
{
	CheckEqRate( "DlgEqualizer3/Sld3Eq12K", 2, 7 );
	return true;
}

bool CCfgEqLogic::OnSld3Eq14KChanged( const IArgs& args )
{
	CheckEqRate( "DlgEqualizer3/Sld3Eq14K", 2, 8 );
	return true;
}

bool CCfgEqLogic::OnSld3Eq16KChanged( const IArgs& args )
{
	CheckEqRate( "DlgEqualizer3/Sld3Eq16K", 2, 9 );
	return true;
}

bool CCfgEqLogic::SaveEq1()
{
//	bool bChange = true;
	bool bUseEq = false;
    UIFACTORYMGR_PTR->GetSwitchState( m_strBtnEq1Switch, bUseEq, m_pWndTree );
	m_atEqInfo[0].bEqualizer = bUseEq;
	SaveEqRate( "DlgEqualizer1/Sld1Eq100", 0, 0 );
	SaveEqRate( "DlgEqualizer1/Sld1Eq200", 0, 1 );
	SaveEqRate( "DlgEqualizer1/Sld1Eq400", 0, 2 );
	SaveEqRate( "DlgEqualizer1/Sld1Eq600", 0, 3 );
	SaveEqRate( "DlgEqualizer1/Sld1Eq1K", 0, 4 );
	SaveEqRate( "DlgEqualizer1/Sld1Eq3K", 0, 5 );
	SaveEqRate( "DlgEqualizer1/Sld1Eq6K", 0, 6 );
	SaveEqRate( "DlgEqualizer1/Sld1Eq12K", 0, 7 );
	SaveEqRate( "DlgEqualizer1/Sld1Eq14K", 0, 8 );
	SaveEqRate( "DlgEqualizer1/Sld1Eq16K", 0, 9 );
// 	GetEqData();
// 	if ( m_atOldEqInfo[0].achEqualizerGain[0] == m_atEqInfo[0].achEqualizerGain[0] || m_atOldEqInfo[0].achEqualizerGain[1] == m_atEqInfo[0].achEqualizerGain[1]
// 		|| m_atOldEqInfo[0].achEqualizerGain[2] == m_atEqInfo[0].achEqualizerGain[2] || m_atOldEqInfo[0].achEqualizerGain[3] == m_atEqInfo[0].achEqualizerGain[3]
// 		|| m_atOldEqInfo[0].achEqualizerGain[4] == m_atEqInfo[0].achEqualizerGain[4] || m_atOldEqInfo[0].achEqualizerGain[5] == m_atEqInfo[0].achEqualizerGain[5]
// 		|| m_atOldEqInfo[0].achEqualizerGain[6] == m_atEqInfo[0].achEqualizerGain[6] || m_atOldEqInfo[0].achEqualizerGain[7] == m_atEqInfo[0].achEqualizerGain[7]
// 		|| m_atOldEqInfo[0].achEqualizerGain[8] == m_atEqInfo[0].achEqualizerGain[8])
// 	{
// 		bChange = false;
// 	}
// 	return bChange;
	return true;
}

bool CCfgEqLogic::SaveEq2()
{
//	bool bChange = true;
	bool bUseEq = false;
    UIFACTORYMGR_PTR->GetSwitchState( m_strBtnEq2Switch, bUseEq, m_pWndTree );
	m_atEqInfo[1].bEqualizer = bUseEq;
	SaveEqRate( "DlgEqualizer2/Sld2Eq100", 1, 0 );
	SaveEqRate( "DlgEqualizer2/Sld2Eq200", 1, 1 );
	SaveEqRate( "DlgEqualizer2/Sld2Eq400", 1, 2 );
	SaveEqRate( "DlgEqualizer2/Sld2Eq600", 1, 3 );
	SaveEqRate( "DlgEqualizer2/Sld2Eq1K", 1, 4 );
	SaveEqRate( "DlgEqualizer2/Sld2Eq3K", 1, 5 );
	SaveEqRate( "DlgEqualizer2/Sld2Eq6K", 1, 6 );
	SaveEqRate( "DlgEqualizer2/Sld2Eq12K", 1, 7 );
	SaveEqRate( "DlgEqualizer2/Sld2Eq14K", 1, 8 );
	SaveEqRate( "DlgEqualizer2/Sld2Eq16K", 1, 9 );
// 	GetEqData();
// 	if ( m_atOldEqInfo[1].achEqualizerGain[0] == m_atEqInfo[0].achEqualizerGain[0] || m_atOldEqInfo[1].achEqualizerGain[1] == m_atEqInfo[0].achEqualizerGain[1]
// 		|| m_atOldEqInfo[1].achEqualizerGain[2] == m_atEqInfo[0].achEqualizerGain[2] || m_atOldEqInfo[1].achEqualizerGain[3] == m_atEqInfo[0].achEqualizerGain[3]
// 		|| m_atOldEqInfo[1].achEqualizerGain[4] == m_atEqInfo[0].achEqualizerGain[4] || m_atOldEqInfo[1].achEqualizerGain[5] == m_atEqInfo[0].achEqualizerGain[5]
// 		|| m_atOldEqInfo[1].achEqualizerGain[6] == m_atEqInfo[0].achEqualizerGain[6] || m_atOldEqInfo[1].achEqualizerGain[7] == m_atEqInfo[0].achEqualizerGain[7]
// 		|| m_atOldEqInfo[1].achEqualizerGain[8] == m_atEqInfo[0].achEqualizerGain[8])
// 	{
// 		bChange = false;
// 	}
// 	return bChange;
	return true;
}

bool CCfgEqLogic::SaveEq3()
{
//	bool bChange = true;
	bool bUseEq = false;
    UIFACTORYMGR_PTR->GetSwitchState( m_strBtnEq3Switch, bUseEq, m_pWndTree );
	m_atEqInfo[2].bEqualizer = bUseEq;
	SaveEqRate( "DlgEqualizer3/Sld3Eq100", 2, 0 );
	SaveEqRate( "DlgEqualizer3/Sld3Eq200", 2, 1 );
	SaveEqRate( "DlgEqualizer3/Sld3Eq400", 2, 2 );
	SaveEqRate( "DlgEqualizer3/Sld3Eq600", 2, 3 );
	SaveEqRate( "DlgEqualizer3/Sld3Eq1K", 2, 4 );
	SaveEqRate( "DlgEqualizer3/Sld3Eq3K", 2, 5 );
	SaveEqRate( "DlgEqualizer3/Sld3Eq6K", 2, 6 );
	SaveEqRate( "DlgEqualizer3/Sld3Eq12K", 2, 7 );
	SaveEqRate( "DlgEqualizer3/Sld3Eq14K", 2, 8 );
	SaveEqRate( "DlgEqualizer3/Sld3Eq16K", 2, 9 );
// 	GetEqData();
// 	if ( m_atOldEqInfo[2].achEqualizerGain[0] == m_atEqInfo[0].achEqualizerGain[0] || m_atOldEqInfo[2].achEqualizerGain[1] == m_atEqInfo[0].achEqualizerGain[1]
// 		|| m_atOldEqInfo[2].achEqualizerGain[2] == m_atEqInfo[0].achEqualizerGain[2] || m_atOldEqInfo[2].achEqualizerGain[3] == m_atEqInfo[0].achEqualizerGain[3]
// 		|| m_atOldEqInfo[2].achEqualizerGain[4] == m_atEqInfo[0].achEqualizerGain[4] || m_atOldEqInfo[2].achEqualizerGain[5] == m_atEqInfo[0].achEqualizerGain[5]
// 		|| m_atOldEqInfo[2].achEqualizerGain[6] == m_atEqInfo[0].achEqualizerGain[6] || m_atOldEqInfo[2].achEqualizerGain[7] == m_atEqInfo[0].achEqualizerGain[7]
// 		|| m_atOldEqInfo[2].achEqualizerGain[8] == m_atEqInfo[0].achEqualizerGain[8])
// 	{
// 		bChange = false;
// 	}
// 	return bChange;
	return true;
}

void CCfgEqLogic::SaveEqRate( String strWndName, s32 nGroup, s32 nNum )
{
	Value_CSliderCtrlPos pos;
	UIFACTORYMGR_PTR->GetPropertyValue( pos,strWndName,m_pWndTree );
	m_atEqInfo[nGroup].anEqualizerGain[nNum] = pos.nPos;
}

void CCfgEqLogic::SetEqDefaultData()
{
	memset( m_atOldEqInfo, 0, sizeof(m_atOldEqInfo) );

	m_atOldEqInfo[0].byIndex = 0;
	m_atOldEqInfo[0].bEqualizer = FALSE;

	m_atOldEqInfo[1].byIndex = 1;
	m_atOldEqInfo[1].bEqualizer = FALSE;

	m_atOldEqInfo[2].byIndex = 2;
	m_atOldEqInfo[2].bEqualizer = FALSE;
}
