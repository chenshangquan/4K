// cfgMixLogic.cpp: implementation of the CCfgMixLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cfgMixLogic.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCfgMixLogic::CCfgMixLogic()
: m_strAudio1Group1("CfgMixAudioDlg/Audio1Group1")							 
, m_strAudio1Group2("CfgMixAudioDlg/Audio1Group2")							 
, m_strAudio1Group3("CfgMixAudioDlg/Audio1Group3")						 
, m_strAudio1Group4("CfgMixAudioDlg/Audio1Group4")							 
, m_strAudio2Group1("CfgMixAudioDlg/Audio2Group1")						 
, m_strAudio2Group2("CfgMixAudioDlg/Audio2Group2")						 
, m_strAudio2Group3("CfgMixAudioDlg/Audio2Group3")						 
, m_strAudio2Group4("CfgMixAudioDlg/Audio2Group4")					 
, m_strAudio3Group1("CfgMixAudioDlg/Audio3Group1")						 
, m_strAudio3Group2("CfgMixAudioDlg/Audio3Group2")						 
, m_strAudio3Group3("CfgMixAudioDlg/Audio3Group3")						 
, m_strAudio3Group4("CfgMixAudioDlg/Audio3Group4")						 
, m_strMixGroup1("CfgMixAudioDlg/MixGroup1")						 
, m_strMixGroup2("CfgMixAudioDlg/MixGroup2")						 
, m_strMixGroup3("CfgMixAudioDlg/MixGroup3")	
{
	m_vctWndName.clear();
}

CCfgMixLogic::~CCfgMixLogic()
{

}

bool CCfgMixLogic::InitWnd( const IArgs & arg )
{
	CLogicBase::InitWnd( arg );
	SetDefaultMixInfo();
	SetMixState();
	m_vctWndName.clear();
	UpBtnState();
	return true;
}

void CCfgMixLogic::RegMsg()
{
	CCfgMixLogic *pThis = GetSingletonPtr();
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_AudMixer_NTY, CCfgMixLogic::OnUpdateMixerNty, pThis, CCfgMixLogic ); 
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_DftMixer_NTY, CCfgMixLogic::OnDefaultMixerNty, pThis, CCfgMixLogic ); 
}

void CCfgMixLogic::UnRegMsg()
{
	
}

void CCfgMixLogic::RegCBFun()
{
	CCfgMixLogic *pThis = GetSingletonPtr();
	REG_GOBAL_MEMBER_FUNC( "CCfgMixLogic::InitWnd", CCfgMixLogic::InitWnd, pThis, CCfgMixLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgMixLogic::OnBtnSave", CCfgMixLogic::OnBtnSave, pThis, CCfgMixLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgMixLogic::OnBtnCancel", CCfgMixLogic::OnBtnCancel, pThis, CCfgMixLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgMixLogic::OnBtnDefault", CCfgMixLogic::OnBtnDefault, pThis, CCfgMixLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgMixLogic::OnSelAudio1Group", CCfgMixLogic::OnSelAudio1Group, pThis, CCfgMixLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgMixLogic::OnSelAudio2Group", CCfgMixLogic::OnSelAudio2Group, pThis, CCfgMixLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgMixLogic::OnSelAudio3Group", CCfgMixLogic::OnSelAudio3Group, pThis, CCfgMixLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgMixLogic::OnSelMixGroup", CCfgMixLogic::OnSelMixGroup, pThis, CCfgMixLogic );
}

void CCfgMixLogic::UnRegFunc()
{
	UN_REG_GOBAL_FUNC( "CCfgMixLogic::InitWnd" );	
}

void CCfgMixLogic::Clear()
{
	memset( m_aAudioMixerInfo, 0, sizeof(m_aAudioMixerInfo) );
	memset( m_aOldAudioMixerInfo, 0, sizeof(m_aOldAudioMixerInfo) );
	m_vctWndName.clear();
	UpBtnState();
}

bool CCfgMixLogic::OnBtnSave( const IArgs& args )
{
	SaveGroup1();
	SaveGroup2();
	SaveGroup3();
	SaveRoomGroup();
	u16 wRet =  COMIFMGRPTR->SetAudiotMixerCmd( m_aAudioMixerInfo );	
	if ( NO_ERROR != wRet )
	{
		//MSG_BOX_OK("±£´æ»ìÒôÅäÖÃÇëÇó·¢ËÍÊ§°Ü");
		WARNMESSAGE("±£´æ»ìÒôÅäÖÃÇëÇó·¢ËÍÊ§°Ü");
		return false;
	}
	m_vctWndName.clear();
	UpBtnState();
	return true;
}

bool CCfgMixLogic::OnBtnCancel( const IArgs& args )
{
	SetMixState();
	m_vctWndName.clear();
	UpBtnState();
	return true;
}

bool CCfgMixLogic::OnBtnDefault( const IArgs& args )
{
	memset( m_aAudioMixerInfo, 0, sizeof(m_aAudioMixerInfo) );
	SetDefaultMixInfo();
	memcpy( m_aAudioMixerInfo, m_aOldAudioMixerInfo, sizeof(m_aOldAudioMixerInfo) );
	u16 wRet =  COMIFMGRPTR->SetDefaultMixerCmd( m_aAudioMixerInfo );	
	if ( NO_ERROR != wRet )
	{
		//MSG_BOX_OK("»Ö¸´Ä¬ÈÏ»ìÒôÅäÖÃÇëÇó·¢ËÍÊ§°Ü");
		WARNMESSAGE("»Ö¸´Ä¬ÈÏ»ìÒôÅäÖÃÇëÇó·¢ËÍÊ§°Ü");
		return false;
	}
	return true;
}

LRESULT CCfgMixLogic::OnUpdateMixerNty( WPARAM wParam, LPARAM lParam )
{
	if ( m_vctWndName.size() > 0 )
	{
		return S_FALSE;
	}
	BOOL bSuccess = *(BOOL*)lParam;
	if ( !bSuccess )
	{
		WARNMESSAGE( "±£´æ»ìÒôÉèÖÃÊ§°Ü" );
		return S_FALSE;
	}
	GetMixInfo();
	SetMixState();
	return S_OK;
}

LRESULT CCfgMixLogic::OnDefaultMixerNty( WPARAM wParam, LPARAM lParam )
{
	BOOL bSuccess = *(BOOL*)lParam;
	if ( !bSuccess )
	{
		WARNMESSAGE( "»Ö¸´»ìÒôÄ¬ÈÏÉèÖÃÊ§°Ü" );
		GetMixInfo();
		SetMixState();
		return S_FALSE;
	}
	else
	{
		SetDefaultMixInfo();
		SetMixState();
		m_vctWndName.clear();
		UpBtnState();
	}
	
	return S_OK;
}

bool CCfgMixLogic::SetMixState()
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	UIFACTORYMGR_PTR->SetCheckState( m_strMixGroup1, 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( m_strMixGroup2, 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( m_strMixGroup3, 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( m_strAudio1Group1, 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( m_strAudio1Group2, 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( m_strAudio1Group3, 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( m_strAudio1Group4, 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( m_strAudio2Group1, 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( m_strAudio2Group2, 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( m_strAudio2Group3, 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( m_strAudio2Group4, 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( m_strAudio3Group1, 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( m_strAudio3Group2, 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( m_strAudio3Group3, 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( m_strAudio3Group4, 0, m_pWndTree );

	for ( int i = 0; i < 4; i++ )
    {
		switch( m_aOldAudioMixerInfo[i] )
		{
		case 1:
			if ( 0 == i )
			{
				UIFACTORYMGR_PTR->SetCheckState( m_strAudio1Group1, 1, m_pWndTree );
			}
			else if ( 1 == i )
			{
				UIFACTORYMGR_PTR->SetCheckState( m_strAudio2Group1, 1, m_pWndTree );
			}
			else if ( 2 == i )
			{
				UIFACTORYMGR_PTR->SetCheckState( m_strAudio3Group1, 1, m_pWndTree );
			}
			else if ( 3 == i )
			{
				UIFACTORYMGR_PTR->SetCheckState( m_strMixGroup1, 1, m_pWndTree );
			}						
			break;
		case 2:
			if ( 0 == i )
			{
				UIFACTORYMGR_PTR->SetCheckState( m_strAudio1Group2, 1, m_pWndTree );
			}
			else if ( 1 == i )
			{
				UIFACTORYMGR_PTR->SetCheckState( m_strAudio2Group2, 1, m_pWndTree );
			}
			else if ( 2 == i )
			{
				UIFACTORYMGR_PTR->SetCheckState( m_strAudio3Group2, 1, m_pWndTree );
			}
			else if ( 3 == i )
			{
				UIFACTORYMGR_PTR->SetCheckState( m_strMixGroup2, 1, m_pWndTree );
			}						
			break;
		case 3:
			if ( 0 == i )
			{
				UIFACTORYMGR_PTR->SetCheckState( m_strAudio1Group3, 1, m_pWndTree );
			}
			else if ( 1 == i )
			{
				UIFACTORYMGR_PTR->SetCheckState( m_strAudio2Group3, 1, m_pWndTree );
			}
			else if ( 2 == i )
			{
				UIFACTORYMGR_PTR->SetCheckState( m_strAudio3Group3, 1, m_pWndTree );
			}
			else if ( 3 == i )
			{
				UIFACTORYMGR_PTR->SetCheckState( m_strMixGroup3, 1, m_pWndTree );
			}						
			break;
		case 4:
			if ( 0 == i )
			{
				UIFACTORYMGR_PTR->SetCheckState( m_strAudio1Group4, 1, m_pWndTree );
			}
			else if ( 1 == i )
			{
				UIFACTORYMGR_PTR->SetCheckState( m_strAudio2Group4, 1, m_pWndTree );
			}
			else if ( 2 == i )
			{
				UIFACTORYMGR_PTR->SetCheckState( m_strAudio3Group4, 1, m_pWndTree );
			}					
			break;
		}
    }	
	return true;
}

bool CCfgMixLogic::SaveGroup1()
{
	s32 nCheckState = 0;	
	UIFACTORYMGR_PTR->GetCheckState( m_strAudio1Group1, nCheckState, m_pWndTree );
	if ( 0 == nCheckState )
	{
		UIFACTORYMGR_PTR->GetCheckState( m_strAudio1Group2, nCheckState, m_pWndTree );
		if ( 0 == nCheckState )
		{
			UIFACTORYMGR_PTR->GetCheckState( m_strAudio1Group3, nCheckState, m_pWndTree );
			if ( 0 == nCheckState )
			{
				UIFACTORYMGR_PTR->GetCheckState( m_strAudio1Group4, nCheckState, m_pWndTree );
				if ( 0 == nCheckState )
				{
					m_aAudioMixerInfo[0] = 0;
					return false;
				} 
				else
				{
					m_aAudioMixerInfo[0] = 4;
					return true;
				}
			}
			else
			{
				m_aAudioMixerInfo[0] = 3;
				return true;
			}
		}
		else
		{	
			m_aAudioMixerInfo[0] = 2;
			return true;
		}	
	}
	else
	{
		m_aAudioMixerInfo[0] = 1;
		return false;
	}
}

bool CCfgMixLogic::SaveGroup2()
{
	s32 nCheckState = 0;	
	UIFACTORYMGR_PTR->GetCheckState( m_strAudio2Group1, nCheckState, m_pWndTree );
	if ( 0 == nCheckState )
	{
		UIFACTORYMGR_PTR->GetCheckState( m_strAudio2Group2, nCheckState, m_pWndTree );
		if ( 0 == nCheckState )
		{
			UIFACTORYMGR_PTR->GetCheckState( m_strAudio2Group3, nCheckState, m_pWndTree );
			if ( 0 == nCheckState )
			{
				UIFACTORYMGR_PTR->GetCheckState( m_strAudio2Group4, nCheckState, m_pWndTree );
				if ( 0 == nCheckState )
				{
					m_aAudioMixerInfo[1] = 0;
					return false;
				} 
				else
				{
					m_aAudioMixerInfo[1] = 4;
					return true;
				}
			}
			else
			{
				m_aAudioMixerInfo[1] = 3;
				return true;
			}
		}
		else
		{	
			m_aAudioMixerInfo[1] = 2;
			return true;
		}	
	}
	else
	{
		m_aAudioMixerInfo[1] = 1;
		return false;
	}
}

bool CCfgMixLogic::SaveGroup3()
{
	s32 nCheckState = 0;	
	UIFACTORYMGR_PTR->GetCheckState( m_strAudio3Group1, nCheckState, m_pWndTree );
	if ( 0 == nCheckState )
	{
		UIFACTORYMGR_PTR->GetCheckState( m_strAudio3Group2, nCheckState, m_pWndTree );
		if ( 0 == nCheckState )
		{
			UIFACTORYMGR_PTR->GetCheckState( m_strAudio3Group3, nCheckState, m_pWndTree );
			if ( 0 == nCheckState )
			{
				UIFACTORYMGR_PTR->GetCheckState( m_strAudio3Group4, nCheckState, m_pWndTree );
				if ( 0 == nCheckState )
				{
					m_aAudioMixerInfo[2] = 0;
					return false;
				} 
				else
				{
					m_aAudioMixerInfo[2] = 4;
					return true;
				}
			}
			else
			{
				m_aAudioMixerInfo[2] = 3;
				return true;
			}
		}
		else
		{	
			m_aAudioMixerInfo[2] = 2;
			return true;
		}	
	}
	else
	{
		m_aAudioMixerInfo[2] = 1;
		return false;
	}
}

bool CCfgMixLogic::SaveRoomGroup()
{
	s32 nCheckState = 0;	
	UIFACTORYMGR_PTR->GetCheckState( m_strMixGroup1, nCheckState, m_pWndTree );
	if ( 0 == nCheckState )
	{
		UIFACTORYMGR_PTR->GetCheckState( m_strMixGroup2, nCheckState, m_pWndTree );
		if ( 0 == nCheckState )
		{
			UIFACTORYMGR_PTR->GetCheckState( m_strMixGroup3, nCheckState, m_pWndTree );
			if ( 0 == nCheckState )
			{
				m_aAudioMixerInfo[3] = 0;
				return false;
			} 
			else
			{
				m_aAudioMixerInfo[3] = 3;
				return true;
			}
		}
		else
		{	
			m_aAudioMixerInfo[3] = 2;
			return true;
		}	
	}
	else
	{
		m_aAudioMixerInfo[3] = 1;
		return false;
	}
}

bool CCfgMixLogic::IsCfgMixChange()
{
	s32 n = m_vctWndName.size();
	if ( n > 0 )
	{
		return SaveMsgBox();
	}
	return true;
}

bool CCfgMixLogic::SaveMsgBox()
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

bool CCfgMixLogic::OnSelAudio1Group( const IArgs& args )
{
	s32 nCheckState = 0;
	switch ( m_aOldAudioMixerInfo[0] )
	{
	case 1:
		UIFACTORYMGR_PTR->GetCheckState( m_strAudio1Group1, nCheckState, m_pWndTree );
		break;
	case 2:
		UIFACTORYMGR_PTR->GetCheckState( m_strAudio1Group2, nCheckState, m_pWndTree );
		break;
	case 3:
		UIFACTORYMGR_PTR->GetCheckState( m_strAudio1Group3, nCheckState, m_pWndTree );
		break;
	case 4:
		UIFACTORYMGR_PTR->GetCheckState( m_strAudio1Group4, nCheckState, m_pWndTree );
		break;
	}

	bool bChange = false;
	if ( nCheckState != 1 )
	{
		bChange = true;
	}
	CheckData(m_strAudio1Group1,bChange);
	
	return true;
}

bool CCfgMixLogic::OnSelAudio2Group( const IArgs& args )
{
	s32 nCheckState = 0;
	switch ( m_aOldAudioMixerInfo[1] )
	{
	case 1:
		UIFACTORYMGR_PTR->GetCheckState( m_strAudio2Group1, nCheckState, m_pWndTree );
		break;
	case 2:
		UIFACTORYMGR_PTR->GetCheckState( m_strAudio2Group2, nCheckState, m_pWndTree );
		break;
	case 3:
		UIFACTORYMGR_PTR->GetCheckState( m_strAudio2Group3, nCheckState, m_pWndTree );
		break;
	case 4:
		UIFACTORYMGR_PTR->GetCheckState( m_strAudio2Group4, nCheckState, m_pWndTree );
		break;
	}
	
	bool bChange = false;
	if ( nCheckState != 1 )
	{
		bChange = true;
	}
	CheckData(m_strAudio2Group1,bChange);
	
	return true;
}

bool CCfgMixLogic::OnSelAudio3Group( const IArgs& args )
{
	s32 nCheckState = 0;
	switch ( m_aOldAudioMixerInfo[2] )
	{
	case 1:
		UIFACTORYMGR_PTR->GetCheckState( m_strAudio3Group1, nCheckState, m_pWndTree );
		break;
	case 2:
		UIFACTORYMGR_PTR->GetCheckState( m_strAudio3Group2, nCheckState, m_pWndTree );
		break;
	case 3:
		UIFACTORYMGR_PTR->GetCheckState( m_strAudio3Group3, nCheckState, m_pWndTree );
		break;
	case 4:
		UIFACTORYMGR_PTR->GetCheckState( m_strAudio3Group4, nCheckState, m_pWndTree );
		break;
	}
	
	bool bChange = false;
	if ( nCheckState != 1 )
	{
		bChange = true;
	}
	CheckData(m_strAudio3Group1,bChange);
	
	return true;
}

bool CCfgMixLogic::OnSelMixGroup( const IArgs& args )
{
	s32 nCheckState = 0;
	switch ( m_aOldAudioMixerInfo[3] )
	{
	case 1:
		UIFACTORYMGR_PTR->GetCheckState( m_strMixGroup1, nCheckState, m_pWndTree );
		break;
	case 2:
		UIFACTORYMGR_PTR->GetCheckState( m_strMixGroup2, nCheckState, m_pWndTree );
		break;
	case 3:
		UIFACTORYMGR_PTR->GetCheckState( m_strMixGroup3, nCheckState, m_pWndTree );
		break;
	}
	
	bool bChange = false;
	if ( nCheckState != 1 )
	{
		bChange = true;
	}
	CheckData(m_strMixGroup1,bChange);
	
	return true;
}

void CCfgMixLogic::GetMixInfo()
{
	memset( m_aOldAudioMixerInfo, 0, sizeof(m_aOldAudioMixerInfo) );
	u8* pAudioMixerInfo = NULL;
	LIBDATAMGRPTR->GetAudiotMixer( &pAudioMixerInfo );
	for ( int i = 0; i < 4; i++ )
    {
        m_aOldAudioMixerInfo[i] = *( pAudioMixerInfo + i );
	}
}

void CCfgMixLogic::SetDefaultMixInfo()
{
	memset( m_aOldAudioMixerInfo, 0, sizeof(m_aOldAudioMixerInfo) );
	m_aOldAudioMixerInfo[0] = 1;
	m_aOldAudioMixerInfo[1] = 1;
	m_aOldAudioMixerInfo[2] = 1;
	m_aOldAudioMixerInfo[3] = 3;
}
