// cfgAdjustImageDlg.cpp: implementation of the CCfgAdjustImageDlg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cfgAdjustImageDlg.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCfgAdjustImageDlg::CCfgAdjustImageDlg()
:m_byMaxGain(31)
{
	m_strBrightnessSlider[0] = "CfgAdjustImageDlg/SliderOfBrightness1";
	m_strBrightnessSlider[1] = "CfgAdjustImageDlg/SliderOfBrightness2";
	m_strBrightnessSlider[2] = "CfgAdjustImageDlg/SliderOfBrightness3";
	m_strBrightnessEdit[0] = "CfgAdjustImageDlg/EditOfBrightness1";
	m_strBrightnessEdit[1] = "CfgAdjustImageDlg/EditOfBrightness2";
	m_strBrightnessEdit[2] = "CfgAdjustImageDlg/EditOfBrightness3";

	m_strSaturationSlider[0] = "CfgAdjustImageDlg/SliderOfSaturation1";
	m_strSaturationSlider[1] = "CfgAdjustImageDlg/SliderOfSaturation2";
	m_strSaturationSlider[2] = "CfgAdjustImageDlg/SliderOfSaturation3";
	m_strSaturationEdit[0] = "CfgAdjustImageDlg/EditOfSaturation1";
	m_strSaturationEdit[1] = "CfgAdjustImageDlg/EditOfSaturation2";
	m_strSaturationEdit[2] = "CfgAdjustImageDlg/EditOfSaturation3";

	m_strContrastSlider[0] = "CfgAdjustImageDlg/SliderOfContrast1";
	m_strContrastSlider[1] = "CfgAdjustImageDlg/SliderOfContrast2";
	m_strContrastSlider[2] = "CfgAdjustImageDlg/SliderOfContrast3";
	m_strContrastEdit[0] = "CfgAdjustImageDlg/EditOfContrast1";
	m_strContrastEdit[1] = "CfgAdjustImageDlg/EditOfContrast2";
	m_strContrastEdit[2] = "CfgAdjustImageDlg/EditOfContrast3";
}

CCfgAdjustImageDlg::~CCfgAdjustImageDlg()
{

}

void CCfgAdjustImageDlg::RegMsg()
{
	CCfgAdjustImageDlg* pThis = GetSingletonPtr();
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_ImageAdjust_Nty, CCfgAdjustImageDlg::OnUpdateParameterNty, pThis, CCfgAdjustImageDlg ); 
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_DefaultImageAdjust_Nty, CCfgAdjustImageDlg::OnDefaultParameterNty, pThis, CCfgAdjustImageDlg );
}

void CCfgAdjustImageDlg::RegCBFun()
{
	CCfgAdjustImageDlg *pThis = GetSingletonPtr();
    REG_GOBAL_MEMBER_FUNC( "CCfgAdjustImageDlg::InitWnd", CCfgAdjustImageDlg::InitWnd, pThis, CCfgAdjustImageDlg );
	
	REG_GOBAL_MEMBER_FUNC( "CCfgAdjustImageDlg::OnSliderBrightness1Changed", CCfgAdjustImageDlg::OnSliderBrightness1Changed, pThis, CCfgAdjustImageDlg );
	REG_GOBAL_MEMBER_FUNC( "CCfgAdjustImageDlg::OnEditBrightness1Changed", CCfgAdjustImageDlg::OnEditBrightness1Changed, pThis, CCfgAdjustImageDlg );
	REG_GOBAL_MEMBER_FUNC( "CCfgAdjustImageDlg::OnEditBrightness1KillFocus", CCfgAdjustImageDlg::OnEditBrightness1KillFocus, pThis, CCfgAdjustImageDlg );

	REG_GOBAL_MEMBER_FUNC( "CCfgAdjustImageDlg::OnSliderSaturation1Changed", CCfgAdjustImageDlg::OnSliderSaturation1Changed, pThis, CCfgAdjustImageDlg );
	REG_GOBAL_MEMBER_FUNC( "CCfgAdjustImageDlg::OnEditSaturation1Changed", CCfgAdjustImageDlg::OnEditSaturation1Changed, pThis, CCfgAdjustImageDlg );
	REG_GOBAL_MEMBER_FUNC( "CCfgAdjustImageDlg::OnEditSaturation1KillFocus", CCfgAdjustImageDlg::OnEditSaturation1KillFocus, pThis, CCfgAdjustImageDlg );

	REG_GOBAL_MEMBER_FUNC( "CCfgAdjustImageDlg::OnSliderContrast1Changed", CCfgAdjustImageDlg::OnSliderContrast1Changed, pThis, CCfgAdjustImageDlg );
	REG_GOBAL_MEMBER_FUNC( "CCfgAdjustImageDlg::OnEditContrast1Changed", CCfgAdjustImageDlg::OnEditContrast1Changed, pThis, CCfgAdjustImageDlg );
	REG_GOBAL_MEMBER_FUNC( "CCfgAdjustImageDlg::OnEditContrast1KillFocus", CCfgAdjustImageDlg::OnEditContrast1KillFocus, pThis, CCfgAdjustImageDlg );

	REG_GOBAL_MEMBER_FUNC( "CCfgAdjustImageDlg::OnSliderBrightness2Changed", CCfgAdjustImageDlg::OnSliderBrightness2Changed, pThis, CCfgAdjustImageDlg );
	REG_GOBAL_MEMBER_FUNC( "CCfgAdjustImageDlg::OnEditBrightness2Changed", CCfgAdjustImageDlg::OnEditBrightness2Changed, pThis, CCfgAdjustImageDlg );
	REG_GOBAL_MEMBER_FUNC( "CCfgAdjustImageDlg::OnEditBrightness2KillFocus", CCfgAdjustImageDlg::OnEditBrightness2KillFocus, pThis, CCfgAdjustImageDlg );
	
	REG_GOBAL_MEMBER_FUNC( "CCfgAdjustImageDlg::OnSliderSaturation2Changed", CCfgAdjustImageDlg::OnSliderSaturation2Changed, pThis, CCfgAdjustImageDlg );
	REG_GOBAL_MEMBER_FUNC( "CCfgAdjustImageDlg::OnEditSaturation2Changed", CCfgAdjustImageDlg::OnEditSaturation2Changed, pThis, CCfgAdjustImageDlg );
	REG_GOBAL_MEMBER_FUNC( "CCfgAdjustImageDlg::OnEditSaturation2KillFocus", CCfgAdjustImageDlg::OnEditSaturation2KillFocus, pThis, CCfgAdjustImageDlg );

	REG_GOBAL_MEMBER_FUNC( "CCfgAdjustImageDlg::OnSliderContrast2Changed", CCfgAdjustImageDlg::OnSliderContrast2Changed, pThis, CCfgAdjustImageDlg );
	REG_GOBAL_MEMBER_FUNC( "CCfgAdjustImageDlg::OnEditContrast2Changed", CCfgAdjustImageDlg::OnEditContrast2Changed, pThis, CCfgAdjustImageDlg );
	REG_GOBAL_MEMBER_FUNC( "CCfgAdjustImageDlg::OnEditContrast2KillFocus", CCfgAdjustImageDlg::OnEditContrast2KillFocus, pThis, CCfgAdjustImageDlg );
	
	REG_GOBAL_MEMBER_FUNC( "CCfgAdjustImageDlg::OnSliderBrightness3Changed", CCfgAdjustImageDlg::OnSliderBrightness3Changed, pThis, CCfgAdjustImageDlg );
	REG_GOBAL_MEMBER_FUNC( "CCfgAdjustImageDlg::OnEditBrightness3Changed", CCfgAdjustImageDlg::OnEditBrightness3Changed, pThis, CCfgAdjustImageDlg );
	REG_GOBAL_MEMBER_FUNC( "CCfgAdjustImageDlg::OnEditBrightness3KillFocus", CCfgAdjustImageDlg::OnEditBrightness3KillFocus, pThis, CCfgAdjustImageDlg );

	REG_GOBAL_MEMBER_FUNC( "CCfgAdjustImageDlg::OnSliderSaturation3Changed", CCfgAdjustImageDlg::OnSliderSaturation3Changed, pThis, CCfgAdjustImageDlg );
	REG_GOBAL_MEMBER_FUNC( "CCfgAdjustImageDlg::OnEditSaturation3Changed", CCfgAdjustImageDlg::OnEditSaturation3Changed, pThis, CCfgAdjustImageDlg );
	REG_GOBAL_MEMBER_FUNC( "CCfgAdjustImageDlg::OnEditSaturation3KillFocus", CCfgAdjustImageDlg::OnEditSaturation3KillFocus, pThis, CCfgAdjustImageDlg );

	REG_GOBAL_MEMBER_FUNC( "CCfgAdjustImageDlg::OnSliderContrast3Changed", CCfgAdjustImageDlg::OnSliderContrast3Changed, pThis, CCfgAdjustImageDlg );
	REG_GOBAL_MEMBER_FUNC( "CCfgAdjustImageDlg::OnEditContrast3Changed", CCfgAdjustImageDlg::OnEditContrast3Changed, pThis, CCfgAdjustImageDlg );
	REG_GOBAL_MEMBER_FUNC( "CCfgAdjustImageDlg::OnEditContrast3KillFocus", CCfgAdjustImageDlg::OnEditContrast3KillFocus, pThis, CCfgAdjustImageDlg );
	
	REG_GOBAL_MEMBER_FUNC( "CCfgAdjustImageDlg::OnBtnDefault", CCfgAdjustImageDlg::OnBtnDefault, pThis, CCfgAdjustImageDlg );
	REG_GOBAL_MEMBER_FUNC( "CCfgAdjustImageDlg::OnBtnSave", CCfgAdjustImageDlg::OnBtnSave, pThis, CCfgAdjustImageDlg );
	REG_GOBAL_MEMBER_FUNC( "CCfgAdjustImageDlg::OnBtnCancel", CCfgAdjustImageDlg::OnBtnCancel, pThis, CCfgAdjustImageDlg );
}

void CCfgAdjustImageDlg::UnRegFunc()
{
	
}

bool CCfgAdjustImageDlg::InitWnd( const IArgs & arg )
{
	CLogicBase::InitWnd( arg );	
	UpBtnState();
	return true;
}

void CCfgAdjustImageDlg::Clear()
{
	
}

bool CCfgAdjustImageDlg::IsCfgParameterChange()
{
	s32 n = m_vctWndName.size();
	if ( n > 0 )
	{
		return SaveMsgBox();
	}
	return true;
}

bool CCfgAdjustImageDlg::SaveMsgBox()
{
	IArgs args("");
	MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
	MSG_BOX( nMsgBoxRet, "配置项已修改，是否保存配置？" );	
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

HRESULT CCfgAdjustImageDlg::OnUpdateParameterNty( WPARAM wparam, LPARAM lparam )
{
	BOOL bSuccess = *(BOOL*)lparam;
	if ( !bSuccess )
	{
		WARNMESSAGE( "保存图像参数配置失败" );
		return S_FALSE;
	}

	TTPImageAdjustParam * pImageAdjust = NULL;
	LIBDATAMGRPTR->GetImageParam( &pImageAdjust );
	for ( s32 nIndex = 0; nIndex < 3; nIndex ++ )
	{
		m_aOldtImageAdjust[nIndex] = *(pImageAdjust+nIndex);
	}
	SetImageParameterDate();
	m_vctWndName.clear();
	UpBtnState();
	return S_OK;
}

HRESULT CCfgAdjustImageDlg::OnDefaultParameterNty( WPARAM wparam, LPARAM lparam )
{
	BOOL bSuccess = *(BOOL*)lparam;
	if ( !bSuccess )
	{
		WARNMESSAGE( "设置默认图像参数配置失败" );
		return S_FALSE;
	}

	TTPImageAdjustParam * pImageAdjust = NULL;
	SetDefaultParameter();
	memcpy(m_aOldtImageAdjust,m_aCurtImageAdjust,sizeof(m_aOldtImageAdjust));
	SetImageParameterDate();
	m_vctWndName.clear();
	UpBtnState();
	return S_OK;
}

bool CCfgAdjustImageDlg::OnBtnCancel( const IArgs& args )
{
	SetImageParameterDate();
	m_vctWndName.clear();
	UpBtnState();
	return S_OK;
}

bool CCfgAdjustImageDlg::OnBtnSave( const IArgs& args )
{
	GetImageParameterData();
	u16 wRet = COMIFMGRPTR->SetParameterCmd(m_aCurtImageAdjust);	
	if ( NO_ERROR == wRet )
	{
		return true;
	}
	else
	{
		WARNMESSAGE("保存图像参数配置请求发送失败");
		return false;
	}
}

//group 1
/*
bool CCfgAdjustImageDlg::OnSliderColor1Changed( const IArgs& args )
{
	UpdateGainNum( m_strImageColorSlider[0], m_strImageColorEdit[0] , m_aOldtImageAdjust[0].byChroma );
	return true;
}

bool CCfgAdjustImageDlg::OnfEditColor1Changed( const IArgs& args )
{
	UpdateGainEdit( m_strImageColorEdit[0] ,m_strImageColorSlider[0], m_aOldtImageAdjust[0].byChroma );
	return true;
}
*/
bool CCfgAdjustImageDlg::OnSliderBrightness1Changed( const IArgs& args )
{
	UpdateGainNum( m_strBrightnessSlider[0], m_strBrightnessEdit[0] , m_aOldtImageAdjust[0].wBrightness );
	return true;
}

bool CCfgAdjustImageDlg::OnEditBrightness1Changed( const IArgs& args )
{
	UpdateGainEdit( m_strBrightnessEdit[0] ,m_strBrightnessSlider[0], m_aOldtImageAdjust[0].wBrightness );
	return true;
}

bool CCfgAdjustImageDlg::OnEditBrightness1KillFocus( const IArgs& args )
{
	UpdateEditDate( m_strBrightnessEdit[0] ,m_strBrightnessSlider[0], m_aOldtImageAdjust[0].wBrightness );
	return true;
}

bool CCfgAdjustImageDlg::OnSliderSaturation1Changed( const IArgs& args )
{
	UpdateGainNum( m_strSaturationSlider[0], m_strSaturationEdit[0] , m_aOldtImageAdjust[0].wSaturation );
	return true;
}

bool CCfgAdjustImageDlg::OnEditSaturation1Changed( const IArgs& args )
{
	UpdateGainEdit( m_strSaturationEdit[0] ,m_strSaturationSlider[0], m_aOldtImageAdjust[0].wSaturation );
	return true;
}

bool CCfgAdjustImageDlg::OnEditSaturation1KillFocus( const IArgs& args )
{
	UpdateEditDate( m_strSaturationEdit[0] ,m_strSaturationSlider[0], m_aOldtImageAdjust[0].wBrightness );
	return true;
}

bool CCfgAdjustImageDlg::OnSliderContrast1Changed( const IArgs& args )
{
	UpdateGainNum( m_strContrastSlider[0], m_strContrastEdit[0] , m_aOldtImageAdjust[0].wContrast );
	return true;
}

bool CCfgAdjustImageDlg::OnEditContrast1Changed( const IArgs& args )
{
	UpdateGainEdit( m_strContrastEdit[0] ,m_strContrastSlider[0], m_aOldtImageAdjust[0].wContrast );
	return true;
}

bool CCfgAdjustImageDlg::OnEditContrast1KillFocus( const IArgs& args )
{
	UpdateEditDate( m_strContrastEdit[0] ,m_strContrastSlider[0], m_aOldtImageAdjust[0].wContrast );
	return true;
}

//group 2
/*
bool CCfgAdjustImageDlg::OnSliderColor2Changed( const IArgs& args )
{
	UpdateGainNum( m_strImageColorSlider[1], m_strImageColorEdit[1] , m_aOldtImageAdjust[1].byChroma );
	return true;
}

bool CCfgAdjustImageDlg::OnfEditColor2Changed( const IArgs& args )
{
	UpdateGainEdit( m_strImageColorEdit[1] ,m_strImageColorSlider[1], m_aOldtImageAdjust[1].byChroma );
	return true;
}
*/
bool CCfgAdjustImageDlg::OnSliderBrightness2Changed( const IArgs& args )
{
	UpdateGainNum( m_strBrightnessSlider[1], m_strBrightnessEdit[1] , m_aOldtImageAdjust[1].wBrightness );
	return true;
}

bool CCfgAdjustImageDlg::OnEditBrightness2Changed( const IArgs& args )
{
	UpdateGainEdit( m_strBrightnessEdit[1] ,m_strBrightnessSlider[1], m_aOldtImageAdjust[1].wBrightness );
	return true;
}

bool CCfgAdjustImageDlg::OnEditBrightness2KillFocus( const IArgs& args )
{
	UpdateEditDate( m_strBrightnessEdit[1] ,m_strBrightnessSlider[1], m_aOldtImageAdjust[1].wBrightness );
	return true;
}

bool CCfgAdjustImageDlg::OnSliderSaturation2Changed( const IArgs& args )
{
	UpdateGainNum( m_strSaturationSlider[1], m_strSaturationEdit[1] , m_aOldtImageAdjust[1].wSaturation );
	return true;
}

bool CCfgAdjustImageDlg::OnEditSaturation2Changed( const IArgs& args )
{
	UpdateGainEdit( m_strSaturationEdit[1] ,m_strSaturationSlider[1], m_aOldtImageAdjust[1].wSaturation );
	return true;
}

bool CCfgAdjustImageDlg::OnEditSaturation2KillFocus( const IArgs& args )
{
	UpdateEditDate( m_strSaturationEdit[1] ,m_strSaturationSlider[1], m_aOldtImageAdjust[1].wSaturation );
	return true;
}

bool CCfgAdjustImageDlg::OnSliderContrast2Changed( const IArgs& args )
{
	UpdateGainNum( m_strContrastSlider[1], m_strContrastEdit[1] , m_aOldtImageAdjust[1].wContrast );
	return true;
}

bool CCfgAdjustImageDlg::OnEditContrast2Changed( const IArgs& args )
{
	UpdateGainEdit( m_strContrastEdit[1] ,m_strContrastSlider[1], m_aOldtImageAdjust[1].wContrast );
	return true;
}

bool CCfgAdjustImageDlg::OnEditContrast2KillFocus( const IArgs& args )
{
	UpdateEditDate( m_strContrastEdit[1] ,m_strContrastSlider[1], m_aOldtImageAdjust[1].wContrast );
	return true;
}

//group 3
/*
bool CCfgAdjustImageDlg::OnSliderColor3Changed( const IArgs& args )
{
	UpdateGainNum( m_strImageColorSlider[2], m_strImageColorEdit[2] , m_aOldtImageAdjust[2].byChroma );
	return true;
}

bool CCfgAdjustImageDlg::OnfEditColor3Changed( const IArgs& args )
{
	UpdateGainEdit( m_strImageColorEdit[2] ,m_strImageColorSlider[2], m_aOldtImageAdjust[2].byChroma );
	return true;
}
*/

bool CCfgAdjustImageDlg::OnSliderBrightness3Changed( const IArgs& args )
{
	UpdateGainNum( m_strBrightnessSlider[2], m_strBrightnessEdit[2] , m_aOldtImageAdjust[2].wBrightness );
	return true;
}

bool CCfgAdjustImageDlg::OnEditBrightness3Changed( const IArgs& args )
{
	UpdateGainEdit( m_strBrightnessEdit[2] ,m_strBrightnessSlider[2], m_aOldtImageAdjust[2].wBrightness );
	return true;
}

bool CCfgAdjustImageDlg::OnEditBrightness3KillFocus( const IArgs& args )
{
	UpdateEditDate( m_strBrightnessEdit[2], m_strBrightnessSlider[2] , m_aOldtImageAdjust[2].wSaturation );
	return true;
}

bool CCfgAdjustImageDlg::OnSliderSaturation3Changed( const IArgs& args )
{
	UpdateGainNum( m_strSaturationSlider[2], m_strSaturationEdit[2] , m_aOldtImageAdjust[2].wSaturation );
	return true;
}

bool CCfgAdjustImageDlg::OnEditSaturation3Changed( const IArgs& args )
{
	UpdateGainEdit( m_strSaturationEdit[2] ,m_strSaturationSlider[2], m_aOldtImageAdjust[2].wSaturation );
	return true;
}

bool CCfgAdjustImageDlg::OnEditSaturation3KillFocus( const IArgs& args )
{
	UpdateEditDate( m_strSaturationEdit[2] ,m_strSaturationSlider[2], m_aOldtImageAdjust[2].wSaturation );
	return true;
}

bool CCfgAdjustImageDlg::OnSliderContrast3Changed( const IArgs& args )
{
	UpdateGainNum( m_strContrastSlider[2], m_strContrastEdit[2] , m_aOldtImageAdjust[2].wContrast );
	return true;
}

bool CCfgAdjustImageDlg::OnEditContrast3Changed( const IArgs& args )
{
	UpdateGainEdit( m_strContrastEdit[2] ,m_strContrastSlider[2], m_aOldtImageAdjust[2].wContrast );
	return true;
}

bool CCfgAdjustImageDlg::OnEditContrast3KillFocus( const IArgs& args )
{
	UpdateEditDate( m_strContrastEdit[2] ,m_strContrastSlider[2], m_aOldtImageAdjust[2].wContrast );
	return true;
}

bool CCfgAdjustImageDlg::OnBtnDefault( const IArgs& args )
{
	memset( &m_aCurtImageAdjust, 0, sizeof(m_aCurtImageAdjust) );
	SetDefaultParameter();
	u16 wRet =  COMIFMGRPTR->SetDefParameterCmd( m_aCurtImageAdjust );	
	if ( NO_ERROR != wRet )
	{
		WARNMESSAGE("恢复默认参数调节配置请求发送失败");
		return false;
	}	
	return true;
}

void CCfgAdjustImageDlg::UpdateGainNum( String strGainName, String strEditName, u8 byGain )
{
	Value_CSliderCtrlPos pos;
	UIFACTORYMGR_PTR->GetPropertyValue( pos, strGainName, m_pWndTree );
	s8 chData[8];
	sprintf( chData, "%u", pos.nPos );
	UIFACTORYMGR_PTR->SetCaption( strEditName, chData, m_pWndTree);
	
	bool bChange = false;
	if ( pos.nPos != byGain )
	{
		bChange = true;
	}
	CheckData( strGainName, bChange );	
}

void CCfgAdjustImageDlg::UpdateGainEdit( String strEditName, String strSliderName, u8 byGain )
{
	String strEdit;
	UIFACTORYMGR_PTR->GetCaption( strEditName, strEdit, m_pWndTree );
	Value_CSliderCtrlPos pos;
	pos.nPos = atoi(strEdit.c_str());
	if ( pos.nPos >= m_byMaxGain )
	{
		pos.nPos = m_byMaxGain;
	}

/*	if ( pos.nPos <= 1 )
	{
		pos.nPos = 1;
	}
	*/
	s8 chVal[5] = { 0 };
	itoa( pos.nPos, chVal,10 );
	UIFACTORYMGR_PTR->SetCaption( strEditName, chVal, m_pWndTree );
	
	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( strEditName, m_pWndTree );
	//将光标移动至最后一个字
	if ( pWnd )
	{
		(( CEdit *) pWnd)->SetSel( -1 );
	}
	
	UIFACTORYMGR_PTR->SetPropertyValue( pos,strSliderName,m_pWndTree );
	
	//GetAudioInfo();
	bool bChange = false;
	if ( pos.nPos != byGain )
	{
		bChange = true;
	}
	CheckData(strEditName,bChange);	
	CheckData(strSliderName,bChange);	//slider
}

void CCfgAdjustImageDlg::UpdateEditDate( String strEditName, String strSliderName, u8 byGain )
{
	String strEdit;
	UIFACTORYMGR_PTR->GetCaption( strEditName, strEdit, m_pWndTree );
	Value_CSliderCtrlPos pos;
	pos.nPos = atoi(strEdit.c_str());
	if ( pos.nPos >= m_byMaxGain )
	{
		pos.nPos = m_byMaxGain;
	}

	if ( pos.nPos <= 1 )
	{
		pos.nPos = 1;
	}

	s8 chVal[5] = { 0 };
	itoa( pos.nPos, chVal,10 );
	UIFACTORYMGR_PTR->SetCaption( strEditName, chVal, m_pWndTree );

	UIFACTORYMGR_PTR->SetPropertyValue( pos,strSliderName,m_pWndTree );
	
	//GetAudioInfo();
	bool bChange = false;
	if ( pos.nPos != byGain )
	{
		bChange = true;
	}
	CheckData(strEditName,bChange);	
	CheckData(strSliderName,bChange);	//slider
}


void CCfgAdjustImageDlg::SetDefaultParameter()
{
	for ( s32 nIndex = 0; nIndex <3; nIndex ++ )
	{
		m_aCurtImageAdjust[nIndex].byChroma = 16;
		m_aCurtImageAdjust[nIndex].wBrightness = 16;
		m_aCurtImageAdjust[nIndex].wSaturation = 16;
		m_aCurtImageAdjust[nIndex].wContrast = 16;
	}
}

void CCfgAdjustImageDlg::SetImageParameterDate()
{
	if ( m_pWndTree == NULL )
	{
		return;
	}
	s8 chData[8] = {0};
	Value_CSliderCtrlPos valuePos;
	//将界面控件初始化

	for ( s32 nIndex = 0; nIndex < 3 ; nIndex ++ )
	{
/*		valuePos.nPos = m_aOldtImageAdjust[nIndex].byChroma;
		UIFACTORYMGR_PTR->SetPropertyValue( valuePos,m_strImageColorSlider[nIndex],m_pWndTree );
		sprintf( chData, "%u", m_aOldtImageAdjust[nIndex].byChroma );
		UIFACTORYMGR_PTR->SetCaption( m_strImageColorEdit[nIndex], chData, m_pWndTree);
*/
		valuePos.nPos = m_aOldtImageAdjust[nIndex].wBrightness;
		UIFACTORYMGR_PTR->SetPropertyValue( valuePos,m_strBrightnessSlider[nIndex],m_pWndTree );
		sprintf( chData, "%u", m_aOldtImageAdjust[nIndex].wBrightness );
		UIFACTORYMGR_PTR->SetCaption( m_strBrightnessEdit[nIndex], chData, m_pWndTree);

		valuePos.nPos = m_aOldtImageAdjust[nIndex].wContrast;
		UIFACTORYMGR_PTR->SetPropertyValue( valuePos,m_strContrastSlider[nIndex],m_pWndTree );
		sprintf( chData, "%u", m_aOldtImageAdjust[nIndex].wContrast );
		UIFACTORYMGR_PTR->SetCaption( m_strContrastEdit[nIndex], chData, m_pWndTree);

		valuePos.nPos = m_aOldtImageAdjust[nIndex].wSaturation;
		UIFACTORYMGR_PTR->SetPropertyValue( valuePos,m_strSaturationSlider[nIndex],m_pWndTree );
		sprintf( chData, "%u", m_aOldtImageAdjust[nIndex].wSaturation );
		UIFACTORYMGR_PTR->SetCaption( m_strSaturationEdit[nIndex], chData, m_pWndTree);
	}
}

void CCfgAdjustImageDlg::GetImageParameterData()
{
	bool bSimPower = false;

	for ( s32 nIndex = 0; nIndex <3 ; nIndex ++ )
	{
		String strEdit;				//水平slider获取值有问题,改为从edit框里面获取值

	//	UIFACTORYMGR_PTR->GetCaption( m_strImageColorEdit[nIndex], strEdit, m_pWndTree );
	//	m_aCurtImageAdjust[nIndex].byChroma = /*posGain.nPos*/atoi(strEdit.c_str());

		UIFACTORYMGR_PTR->GetCaption( m_strBrightnessEdit[nIndex], strEdit, m_pWndTree );
		m_aCurtImageAdjust[nIndex].wBrightness = /*posGain.nPos*/atoi(strEdit.c_str());

		UIFACTORYMGR_PTR->GetCaption( m_strContrastEdit[nIndex], strEdit, m_pWndTree );
		m_aCurtImageAdjust[nIndex].wContrast = /*posGain.nPos*/atoi(strEdit.c_str());

		UIFACTORYMGR_PTR->GetCaption( m_strSaturationEdit[nIndex], strEdit, m_pWndTree );
		m_aCurtImageAdjust[nIndex].wSaturation = /*posGain.nPos*/atoi(strEdit.c_str());
	}
}

bool CCfgAdjustImageDlg::CheckBrightness()
{
	for ( s32 nIndex = 0; nIndex <3 ; nIndex ++ )
	{
		if ( m_aCurtImageAdjust[nIndex].wBrightness == 0 )
		{
			MSG_BOX_OK("亮度参数设置不能为0");
			return false;
		}
	}
	return true;
}

bool CCfgAdjustImageDlg::CheckSaturation()
{
	for ( s32 nIndex = 0; nIndex <3 ; nIndex ++ )
	{
		if ( m_aCurtImageAdjust[nIndex].wSaturation == 0 )
		{
			MSG_BOX_OK("饱和度参数设置不能为0");
			return false;
		}
	}
	return true;
}

bool CCfgAdjustImageDlg::CheckContrast()
{
	for ( s32 nIndex = 0; nIndex <3 ; nIndex ++ )
	{
		if ( m_aCurtImageAdjust[nIndex].wContrast == 0 )
		{
			MSG_BOX_OK("对比度参数设置不能为0");
			return false;
		}
	}
	return true;
}
