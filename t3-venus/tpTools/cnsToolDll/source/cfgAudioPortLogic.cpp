// cfgAudioPortLogic.cpp: implementation of the CCfgAudioPortLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cfgAudioPortLogic.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCfgAudioPortLogic::CCfgAudioPortLogic()
: m_strAudioPort1("CfgAudioPortDlg/AudioPort1")
, m_strAudioPort2("CfgAudioPortDlg/AudioPort2")
, m_strAudioPort3("CfgAudioPortDlg/AudioPort3")
, m_strAudioPort4("CfgAudioPortDlg/AudioPort4")
, m_strAudioPort5("CfgAudioPortDlg/AudioPort5")
, m_strAudioPort6("CfgAudioPortDlg/AudioPort6")
, m_strAudioPort7("CfgAudioPortDlg/AudioPort7")
, m_strAudioPort8("CfgAudioPortDlg/AudioPort8")
, m_strAudioPort9("CfgAudioPortDlg/AudioPort9")
, m_strAudioPort10("CfgAudioPortDlg/AudioPort10")
, m_strAudioPort110("CfgAudioPortDlg/AudioGroup1")
, m_strAudioPort210("CfgAudioPortDlg/AudioGroup2")
, m_strAudioPort310("CfgAudioPortDlg/AudioGroup3")
, m_strNoPort10("CfgAudioPortDlg/NoAudioGroup")
, m_strNoDesktopAudioGroup("CfgAudioPortDlg/NoDesktopAudioGroup")	
{
	m_bNodeskTopBtn = false;
	m_bOldNodeskTopBtn = false;
	m_vctWndName.clear();
}

CCfgAudioPortLogic::~CCfgAudioPortLogic()
{

}

void CCfgAudioPortLogic::RegMsg()
{
	CCfgAudioPortLogic* pThis = GetSingletonPtr();
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_AudPort_NTY, CCfgAudioPortLogic::OnUpdateAudioNty, pThis, CCfgAudioPortLogic ); 
	REG_MSG_HANDLER( UI_CNSTOOL_MSG_DftAudPort_NTY, CCfgAudioPortLogic::OnDefaultAudioNty, pThis, CCfgAudioPortLogic ); 
	REG_MSG_HANDLER( UI_CNSTOOL_SETDESKTOPMIC_NTY, CCfgAudioPortLogic::OnSetDesktopMicNty, pThis, CCfgAudioPortLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_SETDESKTOPMIC_IND, CCfgAudioPortLogic::OnSetDesktopMicInd, pThis, CCfgAudioPortLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_SETMIC10INFO_IND, CCfgAudioPortLogic::OnSetMic10InfoInd, pThis, CCfgAudioPortLogic );
}

void CCfgAudioPortLogic::UnRegMsg()
{
}

void CCfgAudioPortLogic::RegCBFun()
{
	CCfgAudioPortLogic* pThis = GetSingletonPtr();
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::InitWnd", CCfgAudioPortLogic::InitWnd, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnBtnSave", CCfgAudioPortLogic::OnBtnSave, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnBtnCancel", CCfgAudioPortLogic::OnBtnCancel, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnBtnDefault", CCfgAudioPortLogic::OnBtnDefault, pThis, CCfgAudioPortLogic );
	//是否选择卡农麦克风10
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnSelAudio10", CCfgAudioPortLogic::OnSelAudio10, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnNoSelAudio10", CCfgAudioPortLogic::OnNoSelAudio10, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnSelNoDesktopAudio", CCfgAudioPortLogic::OnSelNoDesktopAudio, pThis, CCfgAudioPortLogic );

	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnSelAudio1", CCfgAudioPortLogic::OnSelAudio1, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnSelAudio2", CCfgAudioPortLogic::OnSelAudio2, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnSelAudio3", CCfgAudioPortLogic::OnSelAudio3, pThis, CCfgAudioPortLogic );	
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnSelAudio4", CCfgAudioPortLogic::OnSelAudio4, pThis, CCfgAudioPortLogic );	
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnSelAudio5", CCfgAudioPortLogic::OnSelAudio5, pThis, CCfgAudioPortLogic );	
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnSelAudio6", CCfgAudioPortLogic::OnSelAudio6, pThis, CCfgAudioPortLogic );	
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnSelAudio7", CCfgAudioPortLogic::OnSelAudio7, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnSelAudio8", CCfgAudioPortLogic::OnSelAudio8, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnSelAudio9", CCfgAudioPortLogic::OnSelAudio9, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnSelAudioPort10", CCfgAudioPortLogic::OnSelAudioPort10, pThis, CCfgAudioPortLogic ); //后加的checkbox10
	//REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnSelAudio10", CCfgAudioPortLogic::OnSelAudio10, pThis, CCfgAudioPortLogic );
	//slider 变化
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnSliderGain1Changed", CCfgAudioPortLogic::OnSliderGain1Changed, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnSliderBNA1Changed", CCfgAudioPortLogic::OnSliderBNA1Changed, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnSliderGain2Changed", CCfgAudioPortLogic::OnSliderGain2Changed, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnSliderBNA2Changed", CCfgAudioPortLogic::OnSliderBNA2Changed, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnSliderGain3Changed", CCfgAudioPortLogic::OnSliderGain3Changed, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnSliderBNA3Changed", CCfgAudioPortLogic::OnSliderBNA3Changed, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnSliderGain4Changed", CCfgAudioPortLogic::OnSliderGain4Changed, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnSliderBNA4Changed", CCfgAudioPortLogic::OnSliderBNA4Changed, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnSliderGain5Changed", CCfgAudioPortLogic::OnSliderGain5Changed, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnSliderBNA5Changed", CCfgAudioPortLogic::OnSliderBNA5Changed, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnSliderGain6Changed", CCfgAudioPortLogic::OnSliderGain6Changed, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnSliderBNA6Changed", CCfgAudioPortLogic::OnSliderBNA6Changed, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnSliderGain7Changed", CCfgAudioPortLogic::OnSliderGain7Changed, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnSliderBNA7Changed", CCfgAudioPortLogic::OnSliderBNA7Changed, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnSliderGain8Changed", CCfgAudioPortLogic::OnSliderGain8Changed, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnSliderBNA8Changed", CCfgAudioPortLogic::OnSliderBNA8Changed, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnSliderGain9Changed", CCfgAudioPortLogic::OnSliderGain9Changed, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnSliderBNA9Changed", CCfgAudioPortLogic::OnSliderBNA9Changed, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnSliderGain10Changed", CCfgAudioPortLogic::OnSliderGain10Changed, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnSliderBNA10Changed", CCfgAudioPortLogic::OnSliderBNA10Changed, pThis, CCfgAudioPortLogic );
	//edit变化
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnEditGain1Changed", CCfgAudioPortLogic::OnEditGain1Changed, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnEditBNA1Changed", CCfgAudioPortLogic::OnEditBNA1Changed, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnEditGain2Changed", CCfgAudioPortLogic::OnEditGain2Changed, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnEditBNA2Changed", CCfgAudioPortLogic::OnEditBNA2Changed, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnEditGain3Changed", CCfgAudioPortLogic::OnEditGain3Changed, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnEditBNA3Changed", CCfgAudioPortLogic::OnEditBNA3Changed, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnEditGain4Changed", CCfgAudioPortLogic::OnEditGain4Changed, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnEditBNA4Changed", CCfgAudioPortLogic::OnEditBNA4Changed, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnEditGain5Changed", CCfgAudioPortLogic::OnEditGain5Changed, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnEditBNA5Changed", CCfgAudioPortLogic::OnEditBNA5Changed, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnEditGain6Changed", CCfgAudioPortLogic::OnEditGain6Changed, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnEditBNA6Changed", CCfgAudioPortLogic::OnEditBNA6Changed, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnEditGain7Changed", CCfgAudioPortLogic::OnEditGain7Changed, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnEditBNA7Changed", CCfgAudioPortLogic::OnEditBNA7Changed, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnEditGain8Changed", CCfgAudioPortLogic::OnEditGain8Changed, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnEditBNA8Changed", CCfgAudioPortLogic::OnEditBNA8Changed, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnEditGain9Changed", CCfgAudioPortLogic::OnEditGain9Changed, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnEditBNA9Changed", CCfgAudioPortLogic::OnEditBNA9Changed, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnEditGain10Changed", CCfgAudioPortLogic::OnEditGain10Changed, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnEditBNA10Changed", CCfgAudioPortLogic::OnEditBNA10Changed, pThis, CCfgAudioPortLogic );
	//SwitchButton变化
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnBtnSwitchSimPower1", CCfgAudioPortLogic::OnBtnSwitchSimPower1, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnBtnSwitchSimPower2", CCfgAudioPortLogic::OnBtnSwitchSimPower2, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnBtnSwitchSimPower3", CCfgAudioPortLogic::OnBtnSwitchSimPower3, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnBtnSwitchSimPower4", CCfgAudioPortLogic::OnBtnSwitchSimPower4, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnBtnSwitchSimPower5", CCfgAudioPortLogic::OnBtnSwitchSimPower5, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnBtnSwitchSimPower6", CCfgAudioPortLogic::OnBtnSwitchSimPower6, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnBtnSwitchSimPower7", CCfgAudioPortLogic::OnBtnSwitchSimPower7, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnBtnSwitchSimPower8", CCfgAudioPortLogic::OnBtnSwitchSimPower8, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnBtnSwitchSimPower9", CCfgAudioPortLogic::OnBtnSwitchSimPower9, pThis, CCfgAudioPortLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgAudioPortLogic::OnBtnSwitchSimPower10", CCfgAudioPortLogic::OnBtnSwitchSimPower10, pThis, CCfgAudioPortLogic );

}

void CCfgAudioPortLogic::UnRegFunc()
{
	
}

bool CCfgAudioPortLogic::InitWnd( const IArgs & arg )
{
	CLogicBase::InitWnd( arg );
//	SetDefaultAudioInfo();
//	SetAudioData();
	m_vctWndName.clear();
	UpBtnState();
	return true;
}

void CCfgAudioPortLogic::Clear()
{	
	SetAudioData();
	memset( m_atAudioPortInfo, 0, sizeof(m_atAudioPortInfo) );
	memset( m_atOldAudioPortInfo, 0, sizeof(m_atOldAudioPortInfo) );
	memset( &m_tTpMic10Info, 0, sizeof(TTpMic10Info));
	memset( &m_tOldTpMic10Info, 0, sizeof(TTpMic10Info));
	m_vctWndName.clear();
	UpBtnState();
}

bool CCfgAudioPortLogic::OnBtnCancel( const IArgs& args )
{
	SetAudioData();

	if( m_tOldTpMic10Info.m_emGroupIndex == em_GroupNum1 )
	{
		UIFACTORYMGR_PTR->SetCheckState( m_strAudioPort110, 1, m_pWndTree );
		UIFACTORYMGR_PTR->SetCheckState( m_strNoPort10, 0, m_pWndTree );
	}
	else if( m_tOldTpMic10Info.m_emGroupIndex == em_GroupNum2 )
	{
		UIFACTORYMGR_PTR->SetCheckState( m_strAudioPort210, 1, m_pWndTree );
		UIFACTORYMGR_PTR->SetCheckState( m_strNoPort10, 0, m_pWndTree );
	}
	else if( m_tOldTpMic10Info.m_emGroupIndex == em_GroupNum3 )
	{
		UIFACTORYMGR_PTR->SetCheckState( m_strAudioPort310, 1, m_pWndTree );
		UIFACTORYMGR_PTR->SetCheckState( m_strNoPort10, 0, m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->SetCheckState( m_strNoPort10, 1, m_pWndTree );
	}
	
	if( m_tOldTpMic10Info.m_bAudioPort )
	{
		UIFACTORYMGR_PTR->SetCheckState( m_strAudioPort10, 1, m_pWndTree );
		UIFACTORYMGR_PTR->LoadScheme( "SelAudio10", m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->SetCheckState( m_strAudioPort10, 0, m_pWndTree );
		UIFACTORYMGR_PTR->LoadScheme( "NoSelAudio10", m_pWndTree );
	}

	if( m_bOldNodeskTopBtn )
	{
		UIFACTORYMGR_PTR->SetCheckState( m_strNoDesktopAudioGroup, 1, m_pWndTree );
		m_bNodeskTopBtn = true;
	}
	else
	{
		UIFACTORYMGR_PTR->SetCheckState( m_strNoDesktopAudioGroup, 0, m_pWndTree );
		m_bNodeskTopBtn = false;
	}

	m_vctWndName.clear();
	UpBtnState();
	return true;	
}

bool CCfgAudioPortLogic::OnBtnDefault( const IArgs& args )
{
	memset( m_atAudioPortInfo, 0, sizeof(m_atAudioPortInfo) );
	memset( &m_tTpMic10Info, 0, sizeof( m_tTpMic10Info));
	SetDefaultAudioInfo();
	memcpy( m_atAudioPortInfo, m_atOldAudioPortInfo, sizeof(m_atOldAudioPortInfo) );
	m_tTpMic10Info = m_tOldTpMic10Info;
	m_bNodeskTopBtn = m_bOldNodeskTopBtn;
	u16 wRet =  COMIFMGRPTR->SetDefaultAudioPortCmd( m_atAudioPortInfo );	
	if ( NO_ERROR != wRet )
	{
		WARNMESSAGE("恢复默认音频接口配置请求发送失败");
		return false;
	}
	
	u16 wRet1 = COMIFMGRPTR->SetMic10InfoCmd( m_tTpMic10Info );
	if( NO_ERROR != wRet1 )
	{
		WARNMESSAGE("恢复默认卡龙10接口配置请求发送失败");
		return false;
	}

	u16 wRet2 = COMIFMGRPTR->SetNoDeskAudioCmd( m_bNodeskTopBtn );
	if( NO_ERROR != wRet2 )
	{
		WARNMESSAGE("保存非桌面麦克风配置请求发送失败");
		return false;
	}

	return true;
}

bool CCfgAudioPortLogic::OnBtnSave( const IArgs& args )
{
	bool bSaveGroup10 = SaveGroup10();
	bool bSaveGroup1 = SaveGroup1();
	bool bSaveGroup2 = SaveGroup2();
	bool bSaveGroup3 = SaveGroup3();
	
	if( !m_bNodeskTopBtn )
	{
		u16 wRet = COMIFMGRPTR->SetAudioPortInfoCmd( m_atAudioPortInfo );	
		if ( NO_ERROR == wRet )
		{
			m_vctWndName.clear();
			UpBtnState();
		}
		else
		{
			WARNMESSAGE("保存音频接口配置请求发送失败");
			return false;
		}
		
		u16 wRet1 = COMIFMGRPTR->SetNoDeskAudioCmd( m_bNodeskTopBtn );
		if( NO_ERROR != wRet1 )
		{
			WARNMESSAGE("保存非桌面麦克风配置请求发送失败");
		}
	}
	else
	{
		u16 wRet1 = COMIFMGRPTR->SetNoDeskAudioCmd( m_bNodeskTopBtn );
		if( NO_ERROR != wRet1 )
		{
			WARNMESSAGE("保存非桌面麦克风配置请求发送失败");
		}
		
		u16 wRet = COMIFMGRPTR->SetAudioPortInfoCmd( m_atAudioPortInfo );	
		if ( NO_ERROR == wRet )
		{
			m_vctWndName.clear();
			UpBtnState();
		}
		else
		{
			WARNMESSAGE("保存音频接口配置请求发送失败");
			return false;
		}
	}

	u16 wRet2 = COMIFMGRPTR->SetMic10InfoCmd( m_tTpMic10Info );
	if( NO_ERROR != wRet2 )
	{
		WARNMESSAGE("保存卡龙10音频接口配置请求发送失败");
		return false;
	}
	 
	return true;
}
/*---------------------------------------------------------------------
* 函数名称：SaveGroup1
* 功    能：保存音频设置界面的1、2、3
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2012/12/29	v1.0		景洋洋		创建
----------------------------------------------------------------------*/
bool CCfgAudioPortLogic::SaveGroup1()
{
	bool bCheckFlag = false;
	m_atAudioPortInfo[0].m_byGroupIndex = 0;
	s32 nCheckState = 0;
	//COMMON1
	UIFACTORYMGR_PTR->GetCheckState( m_strAudioPort1, nCheckState, m_pWndTree );
	if ( 0 == nCheckState )
 	{
		m_atAudioPortInfo[0].m_abAudioPort[0] = false;
	}
	else
	{
		m_atAudioPortInfo[0].m_abAudioPort[0] = true;
		bCheckFlag = true;
	}					
	//Value_CSliderCtrlPos posGain;								//增益
	//UIFACTORYMGR_PTR->GetPropertyValue( posGain, "CfgAudioPortDlg/SliderGain1", m_pWndTree );
	//m_atAudioPortInfo[0].m_atSingleAudioPortCfg[0].byMicVolume = posGain.nPos;
	String strEdit;				//水平slider获取值有问题,改为从edit框里面获取值
	UIFACTORYMGR_PTR->GetCaption( "CfgAudioPortDlg/GainEdit1", strEdit, m_pWndTree );
	m_atAudioPortInfo[0].m_atSingleAudioPortCfg[0].byMicVolume = atoi(strEdit.c_str());
					
	bool bSimPower = false;												//幻象开关
	UIFACTORYMGR_PTR->GetSwitchState( "CfgAudioPortDlg/BtnSimPower1", bSimPower, m_pWndTree );
	m_atAudioPortInfo[0].m_atSingleAudioPortCfg[0].bIsSimplexPoweringOpened = bSimPower;
				
	//Value_CSliderCtrlPos posBNA;						    	//背景噪声
	//UIFACTORYMGR_PTR->GetPropertyValue( posBNA, "CfgAudioPortDlg/SliderBNA1", m_pWndTree );
	//m_atAudioPortInfo[0].m_atSingleAudioPortCfg[0].byAudioBNA = posBNA.nPos;
	UIFACTORYMGR_PTR->GetCaption( "CfgAudioPortDlg/BNAEdit1", strEdit, m_pWndTree );
	m_atAudioPortInfo[0].m_atSingleAudioPortCfg[0].byAudioBNA = atoi(strEdit.c_str());

	//COMMON2
	UIFACTORYMGR_PTR->GetCheckState( m_strAudioPort2, nCheckState, m_pWndTree );
	if ( 0 == nCheckState )
	{
		m_atAudioPortInfo[0].m_abAudioPort[1] = false;
	}
	else
	{
		m_atAudioPortInfo[0].m_abAudioPort[1] = true;
		bCheckFlag = true;
	}												
	//UIFACTORYMGR_PTR->GetPropertyValue( posGain, "CfgAudioPortDlg/SliderGain2", m_pWndTree );		//增益
	//m_atAudioPortInfo[0].m_atSingleAudioPortCfg[1].byMicVolume = posGain.nPos;
	UIFACTORYMGR_PTR->GetCaption( "CfgAudioPortDlg/GainEdit2", strEdit, m_pWndTree );
	m_atAudioPortInfo[0].m_atSingleAudioPortCfg[1].byMicVolume = atoi(strEdit.c_str());
	
																
	UIFACTORYMGR_PTR->GetSwitchState( "CfgAudioPortDlg/BtnSimPower2", bSimPower, m_pWndTree );		//幻象开关
	m_atAudioPortInfo[0].m_atSingleAudioPortCfg[1].bIsSimplexPoweringOpened = bSimPower;
										    
	//UIFACTORYMGR_PTR->GetPropertyValue( posBNA, "CfgAudioPortDlg/SliderBNA2", m_pWndTree );			//背景噪声
	//m_atAudioPortInfo[0].m_atSingleAudioPortCfg[1].byAudioBNA = posBNA.nPos;
	UIFACTORYMGR_PTR->GetCaption( "CfgAudioPortDlg/BNAEdit2", strEdit, m_pWndTree );
	m_atAudioPortInfo[0].m_atSingleAudioPortCfg[1].byAudioBNA = atoi(strEdit.c_str());

	//COMMON3
	UIFACTORYMGR_PTR->GetCheckState( m_strAudioPort3, nCheckState, m_pWndTree );
	if ( 0 == nCheckState )
	{
		m_atAudioPortInfo[0].m_abAudioPort[2] = false;
	}
	else
	{
		m_atAudioPortInfo[0].m_abAudioPort[2] = true;
		bCheckFlag = true;
	}
	//UIFACTORYMGR_PTR->GetPropertyValue( posGain, "CfgAudioPortDlg/SliderGain3", m_pWndTree );		//增益
	//m_atAudioPortInfo[0].m_atSingleAudioPortCfg[2].byMicVolume = posGain.nPos;
	UIFACTORYMGR_PTR->GetCaption( "CfgAudioPortDlg/GainEdit3", strEdit, m_pWndTree );
	m_atAudioPortInfo[0].m_atSingleAudioPortCfg[2].byMicVolume = atoi(strEdit.c_str());
	
	UIFACTORYMGR_PTR->GetSwitchState( "CfgAudioPortDlg/BtnSimPower3", bSimPower, m_pWndTree );		//幻象开关
	m_atAudioPortInfo[0].m_atSingleAudioPortCfg[2].bIsSimplexPoweringOpened = bSimPower;
	
	//UIFACTORYMGR_PTR->GetPropertyValue( posBNA, "CfgAudioPortDlg/SliderBNA3", m_pWndTree );			//背景噪声
	//m_atAudioPortInfo[0].m_atSingleAudioPortCfg[2].byAudioBNA = posBNA.nPos;
	UIFACTORYMGR_PTR->GetCaption( "CfgAudioPortDlg/BNAEdit3", strEdit, m_pWndTree );
	m_atAudioPortInfo[0].m_atSingleAudioPortCfg[2].byAudioBNA = atoi(strEdit.c_str());


	return bCheckFlag;
}
/*---------------------------------------------------------------------
* 函数名称：SaveGroup2
* 功    能：保存音频设置界面的4、5、6
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2012/12/29	v1.0		景洋洋		创建
----------------------------------------------------------------------*/
bool CCfgAudioPortLogic::SaveGroup2()
{
	bool bCheckFlag = false;
	m_atAudioPortInfo[1].m_byGroupIndex = 1;
	s32 nCheckState = 0;
	//COMMON4
	UIFACTORYMGR_PTR->GetCheckState( m_strAudioPort4, nCheckState, m_pWndTree );
	if ( 0 == nCheckState )
	{
		m_atAudioPortInfo[1].m_abAudioPort[0] = false;
	}
	else
	{
		m_atAudioPortInfo[1].m_abAudioPort[0] = true;
		bCheckFlag = true;
	}
	//Value_CSliderCtrlPos posGain;								//增益
	//UIFACTORYMGR_PTR->GetPropertyValue( posGain, "CfgAudioPortDlg/SliderGain4", m_pWndTree );
	//m_atAudioPortInfo[1].m_atSingleAudioPortCfg[0].byMicVolume = posGain.nPos;
	String strEdit;				//水平slider获取值有问题,改为从edit框里面获取值
	UIFACTORYMGR_PTR->GetCaption( "CfgAudioPortDlg/GainEdit4", strEdit, m_pWndTree );
	m_atAudioPortInfo[1].m_atSingleAudioPortCfg[0].byMicVolume = atoi(strEdit.c_str());
			
	bool bSimPower = false;												//幻象开关
	UIFACTORYMGR_PTR->GetSwitchState( "CfgAudioPortDlg/BtnSimPower4", bSimPower, m_pWndTree );
	m_atAudioPortInfo[1].m_atSingleAudioPortCfg[0].bIsSimplexPoweringOpened = bSimPower;
				
	//Value_CSliderCtrlPos posBNA;						    	//背景噪声
	//UIFACTORYMGR_PTR->GetPropertyValue( posBNA, "CfgAudioPortDlg/SliderBNA4", m_pWndTree );
	//m_atAudioPortInfo[1].m_atSingleAudioPortCfg[0].byAudioBNA = posBNA.nPos;
	UIFACTORYMGR_PTR->GetCaption( "CfgAudioPortDlg/BNAEdit4", strEdit, m_pWndTree );
	m_atAudioPortInfo[1].m_atSingleAudioPortCfg[0].byAudioBNA = atoi(strEdit.c_str());

	//COMMON5
	UIFACTORYMGR_PTR->GetCheckState( m_strAudioPort5, nCheckState, m_pWndTree );
	if ( 0 == nCheckState )
	{
		m_atAudioPortInfo[1].m_abAudioPort[1] = false;
	}
	else
	{
		m_atAudioPortInfo[1].m_abAudioPort[1] = true;
		bCheckFlag = true;
	}
	//UIFACTORYMGR_PTR->GetPropertyValue( posGain, "CfgAudioPortDlg/SliderGain5", m_pWndTree );		//增益
	//m_atAudioPortInfo[1].m_atSingleAudioPortCfg[1].byMicVolume = posGain.nPos;
	UIFACTORYMGR_PTR->GetCaption( "CfgAudioPortDlg/GainEdit5", strEdit, m_pWndTree );
	m_atAudioPortInfo[1].m_atSingleAudioPortCfg[1].byMicVolume = atoi(strEdit.c_str());
	
	UIFACTORYMGR_PTR->GetSwitchState( "CfgAudioPortDlg/BtnSimPower5", bSimPower, m_pWndTree );		//幻象开关
	m_atAudioPortInfo[1].m_atSingleAudioPortCfg[1].bIsSimplexPoweringOpened = bSimPower;
	
	//UIFACTORYMGR_PTR->GetPropertyValue( posBNA, "CfgAudioPortDlg/SliderBNA5", m_pWndTree );			//背景噪声
	//m_atAudioPortInfo[1].m_atSingleAudioPortCfg[1].byAudioBNA = posBNA.nPos;
	UIFACTORYMGR_PTR->GetCaption( "CfgAudioPortDlg/BNAEdit5", strEdit, m_pWndTree );
	m_atAudioPortInfo[1].m_atSingleAudioPortCfg[1].byAudioBNA = atoi(strEdit.c_str());

	//COMMON6
	UIFACTORYMGR_PTR->GetCheckState( m_strAudioPort6, nCheckState, m_pWndTree );
	if ( 0 == nCheckState )
	{
		m_atAudioPortInfo[1].m_abAudioPort[2] = false;
	}
	else
	{
		m_atAudioPortInfo[1].m_abAudioPort[2] = true;
		bCheckFlag = true;
	}
	//UIFACTORYMGR_PTR->GetPropertyValue( posGain, "CfgAudioPortDlg/SliderGain6", m_pWndTree );		//增益
	//m_atAudioPortInfo[1].m_atSingleAudioPortCfg[2].byMicVolume = posGain.nPos;
	UIFACTORYMGR_PTR->GetCaption( "CfgAudioPortDlg/GainEdit6", strEdit, m_pWndTree );
	m_atAudioPortInfo[1].m_atSingleAudioPortCfg[2].byMicVolume = atoi(strEdit.c_str());
	
	UIFACTORYMGR_PTR->GetSwitchState( "CfgAudioPortDlg/BtnSimPower6", bSimPower, m_pWndTree );		//幻象开关
	m_atAudioPortInfo[1].m_atSingleAudioPortCfg[2].bIsSimplexPoweringOpened = bSimPower;
	
	//UIFACTORYMGR_PTR->GetPropertyValue( posBNA, "CfgAudioPortDlg/SliderBNA6", m_pWndTree );			//背景噪声
	//m_atAudioPortInfo[1].m_atSingleAudioPortCfg[2].byAudioBNA = posBNA.nPos;
	UIFACTORYMGR_PTR->GetCaption( "CfgAudioPortDlg/BNAEdit6", strEdit, m_pWndTree );
	m_atAudioPortInfo[1].m_atSingleAudioPortCfg[2].byAudioBNA = atoi(strEdit.c_str());

	return bCheckFlag;
}
/*---------------------------------------------------------------------
* 函数名称：SaveGroup3
* 功    能：保存音频设置界面的7、8、9
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2012/12/29	v1.0		景洋洋		创建
----------------------------------------------------------------------*/
bool CCfgAudioPortLogic::SaveGroup3()
{
	bool bCheckFlag = false;
	m_atAudioPortInfo[2].m_byGroupIndex = 2;
	s32 nCheckState = 0;
	//COMMON7
	UIFACTORYMGR_PTR->GetCheckState( m_strAudioPort7, nCheckState, m_pWndTree );
	if ( 0 == nCheckState )
	{
		m_atAudioPortInfo[2].m_abAudioPort[0] = false;
	}
	else
	{
		m_atAudioPortInfo[2].m_abAudioPort[0] = true;
		bCheckFlag = true;
	}
	//Value_CSliderCtrlPos posGain;								//增益
	//UIFACTORYMGR_PTR->GetPropertyValue( posGain, "CfgAudioPortDlg/SliderGain7", m_pWndTree );
	//m_atAudioPortInfo[2].m_atSingleAudioPortCfg[0].byMicVolume = posGain.nPos;
	String strEdit;				//水平slider获取值有问题,改为从edit框里面获取值
	UIFACTORYMGR_PTR->GetCaption( "CfgAudioPortDlg/GainEdit7", strEdit, m_pWndTree );
	m_atAudioPortInfo[2].m_atSingleAudioPortCfg[0].byMicVolume = atoi(strEdit.c_str());
	
	bool bSimPower = false;												//幻象开关
	UIFACTORYMGR_PTR->GetSwitchState( "CfgAudioPortDlg/BtnSimPower7", bSimPower, m_pWndTree );
	m_atAudioPortInfo[2].m_atSingleAudioPortCfg[0].bIsSimplexPoweringOpened = bSimPower;
				
	//Value_CSliderCtrlPos posBNA;						    	//背景噪声
	//UIFACTORYMGR_PTR->GetPropertyValue( posBNA, "CfgAudioPortDlg/SliderBNA7", m_pWndTree );
	//m_atAudioPortInfo[2].m_atSingleAudioPortCfg[0].byAudioBNA = posBNA.nPos;
	UIFACTORYMGR_PTR->GetCaption( "CfgAudioPortDlg/BNAEdit7", strEdit, m_pWndTree );
	m_atAudioPortInfo[2].m_atSingleAudioPortCfg[0].byAudioBNA = atoi(strEdit.c_str());

	//COMMON8
	UIFACTORYMGR_PTR->GetCheckState( m_strAudioPort8, nCheckState, m_pWndTree );
	if ( 0 == nCheckState )
	{
		m_atAudioPortInfo[2].m_abAudioPort[1] = false;
	}
	else
	{
		m_atAudioPortInfo[2].m_abAudioPort[1] = true;
		bCheckFlag = true;
	}
	//UIFACTORYMGR_PTR->GetPropertyValue( posGain, "CfgAudioPortDlg/SliderGain8", m_pWndTree );		//增益
	//m_atAudioPortInfo[2].m_atSingleAudioPortCfg[1].byMicVolume = posGain.nPos;
	UIFACTORYMGR_PTR->GetCaption( "CfgAudioPortDlg/GainEdit8", strEdit, m_pWndTree );
	m_atAudioPortInfo[2].m_atSingleAudioPortCfg[1].byMicVolume = atoi(strEdit.c_str());
	
	UIFACTORYMGR_PTR->GetSwitchState( "CfgAudioPortDlg/BtnSimPower8", bSimPower, m_pWndTree );		//幻象开关
	m_atAudioPortInfo[2].m_atSingleAudioPortCfg[1].bIsSimplexPoweringOpened = bSimPower;
	
	//UIFACTORYMGR_PTR->GetPropertyValue( posBNA, "CfgAudioPortDlg/SliderBNA8", m_pWndTree );			//背景噪声
	//m_atAudioPortInfo[2].m_atSingleAudioPortCfg[1].byAudioBNA = posBNA.nPos;
	UIFACTORYMGR_PTR->GetCaption( "CfgAudioPortDlg/BNAEdit8", strEdit, m_pWndTree );
	m_atAudioPortInfo[2].m_atSingleAudioPortCfg[1].byAudioBNA = atoi(strEdit.c_str());

	//COMMON9
	UIFACTORYMGR_PTR->GetCheckState( m_strAudioPort9, nCheckState, m_pWndTree );
	if ( 0 == nCheckState )
	{
		m_atAudioPortInfo[2].m_abAudioPort[2] = false;
	}
	else
	{
		m_atAudioPortInfo[2].m_abAudioPort[2] = true;
		bCheckFlag = true;
	}
	//UIFACTORYMGR_PTR->GetPropertyValue( posGain, "CfgAudioPortDlg/SliderGain9", m_pWndTree );		//增益
	//m_atAudioPortInfo[2].m_atSingleAudioPortCfg[2].byMicVolume = posGain.nPos;
	UIFACTORYMGR_PTR->GetCaption( "CfgAudioPortDlg/GainEdit9", strEdit, m_pWndTree );
	m_atAudioPortInfo[2].m_atSingleAudioPortCfg[2].byMicVolume = atoi(strEdit.c_str());
	
	UIFACTORYMGR_PTR->GetSwitchState( "CfgAudioPortDlg/BtnSimPower9", bSimPower, m_pWndTree );		//幻象开关
	m_atAudioPortInfo[2].m_atSingleAudioPortCfg[2].bIsSimplexPoweringOpened = bSimPower;
	
	//UIFACTORYMGR_PTR->GetPropertyValue( posBNA, "CfgAudioPortDlg/SliderBNA9", m_pWndTree );			//背景噪声
	//m_atAudioPortInfo[2].m_atSingleAudioPortCfg[2].byAudioBNA = posBNA.nPos;
	UIFACTORYMGR_PTR->GetCaption( "CfgAudioPortDlg/BNAEdit9", strEdit, m_pWndTree );
	m_atAudioPortInfo[2].m_atSingleAudioPortCfg[2].byAudioBNA = atoi(strEdit.c_str());

	return bCheckFlag;
}
/*---------------------------------------------------------------------
* 函数名称：SaveGroup10
* 功    能：保存音频设置界面各个小组的10
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2012/12/29	v1.0		景洋洋		创建
----------------------------------------------------------------------*/
bool CCfgAudioPortLogic::SaveGroup10()
{
	s32 nCheckState = 0;	
	UIFACTORYMGR_PTR->GetCheckState( m_strNoPort10, nCheckState, m_pWndTree );
	s32 nCheckState10;
	UIFACTORYMGR_PTR->GetCheckState( m_strAudioPort10, nCheckState10, m_pWndTree );
	if ( 0 == nCheckState )
	{
		UIFACTORYMGR_PTR->GetCheckState( m_strAudioPort110, nCheckState, m_pWndTree );
		if ( 0 == nCheckState )
		{
			UIFACTORYMGR_PTR->GetCheckState( m_strAudioPort210, nCheckState, m_pWndTree );
			if ( 0 == nCheckState )
			{
				UIFACTORYMGR_PTR->GetCheckState( m_strAudioPort310, nCheckState, m_pWndTree );
				if ( 0 == nCheckState )
				{
					m_atAudioPortInfo[0].m_abAudioPort[3] = false;
					m_atAudioPortInfo[1].m_abAudioPort[3] = false;
					m_atAudioPortInfo[2].m_abAudioPort[3] = false;
					return false;
				} 
				else
				{
					m_tTpMic10Info.m_emGroupIndex = em_GroupNum3;
					if( 0 == nCheckState10 )
					{
						m_tTpMic10Info.m_bAudioPort = FALSE;
						m_atAudioPortInfo[0].m_abAudioPort[3] = false;
						m_atAudioPortInfo[1].m_abAudioPort[3] = false;
						m_atAudioPortInfo[2].m_abAudioPort[3] = false;
						return false;
					}
					else
					{
						m_tTpMic10Info.m_bAudioPort = TRUE;
						m_atAudioPortInfo[0].m_abAudioPort[3] = false;
						m_atAudioPortInfo[1].m_abAudioPort[3] = false;
						m_atAudioPortInfo[2].m_abAudioPort[3] = true;
						GetAudio10(2);
						return true;
					}					
				}
			}
			else
			{
				m_tTpMic10Info.m_emGroupIndex = em_GroupNum2;
				if( 0 == nCheckState10 )
				{
					m_tTpMic10Info.m_bAudioPort = FALSE;
					m_atAudioPortInfo[0].m_abAudioPort[3] = false;
					m_atAudioPortInfo[1].m_abAudioPort[3] = false;
					m_atAudioPortInfo[2].m_abAudioPort[3] = false;
					return false;
				}
				else
				{
					m_tTpMic10Info.m_bAudioPort = TRUE;
					m_atAudioPortInfo[0].m_abAudioPort[3] = false;
					m_atAudioPortInfo[1].m_abAudioPort[3] = true;
					m_atAudioPortInfo[2].m_abAudioPort[3] = false;
					GetAudio10(1);
					return true;
				}
			}
		}
		else
		{
			m_tTpMic10Info.m_emGroupIndex = em_GroupNum1;
			if( 0 == nCheckState10 )
			{
				m_tTpMic10Info.m_bAudioPort = FALSE;
				m_atAudioPortInfo[0].m_abAudioPort[3] = false;
				m_atAudioPortInfo[1].m_abAudioPort[3] = false;
				m_atAudioPortInfo[2].m_abAudioPort[3] = false;
				return false;
			}
			else
			{
				m_tTpMic10Info.m_bAudioPort = TRUE;
				m_atAudioPortInfo[0].m_abAudioPort[3] = true;
				m_atAudioPortInfo[1].m_abAudioPort[3] = false;
				m_atAudioPortInfo[2].m_abAudioPort[3] = false;
				GetAudio10(0);
				return true;
			}
		}	
	}
	else
	{	
		m_tTpMic10Info.m_emGroupIndex = em_GroupNum4;
		if( 0 == nCheckState10 )
		{
			m_tTpMic10Info.m_bAudioPort = FALSE;
		}
		else
		{
			m_tTpMic10Info.m_bAudioPort = TRUE;
		}
		m_atAudioPortInfo[0].m_abAudioPort[3] = false;
		m_atAudioPortInfo[1].m_abAudioPort[3] = false;
		m_atAudioPortInfo[2].m_abAudioPort[3] = false;
		GetAudio10(2);
		return true;
	}
}

void CCfgAudioPortLogic::GetAudio10( s32 nGroup )
{
	bool bSimPower = false;
	//Value_CSliderCtrlPos posGain;
	//Value_CSliderCtrlPos posBNA;
	//UIFACTORYMGR_PTR->GetPropertyValue( posGain, "CfgAudioPortDlg/SliderGain10", m_pWndTree );		//增益
	String strEdit;				//水平slider获取值有问题,改为从edit框里面获取值
	UIFACTORYMGR_PTR->GetCaption( "CfgAudioPortDlg/GainEdit10", strEdit, m_pWndTree );
	m_atAudioPortInfo[nGroup].m_atSingleAudioPortCfg[3].byMicVolume = /*posGain.nPos*/atoi(strEdit.c_str());
	
	UIFACTORYMGR_PTR->GetSwitchState( "CfgAudioPortDlg/BtnSimPower10", bSimPower, m_pWndTree );		//幻象开关
	m_atAudioPortInfo[nGroup].m_atSingleAudioPortCfg[3].bIsSimplexPoweringOpened = bSimPower;
	
	//UIFACTORYMGR_PTR->GetPropertyValue( posBNA, "CfgAudioPortDlg/SliderBNA10", m_pWndTree );		//背景噪声
	UIFACTORYMGR_PTR->GetCaption( "CfgAudioPortDlg/BNAEdit10", strEdit, m_pWndTree );
	m_atAudioPortInfo[nGroup].m_atSingleAudioPortCfg[3].byAudioBNA = /*posBNA.nPos*/atoi(strEdit.c_str());
}

HRESULT CCfgAudioPortLogic::OnUpdateAudioNty( WPARAM wparam, LPARAM lparam )
{
	if ( m_vctWndName.size() > 0 )
	{
		return S_FALSE;
	}
	BOOL bSuccess = *(BOOL*)lparam;
	if ( !bSuccess )
	{
		WARNMESSAGE( "保存音频接口设置失败" );
		return S_FALSE;
	}
	GetAudioInfo();
	SetAudioData();
	return S_OK;
}

HRESULT CCfgAudioPortLogic::OnDefaultAudioNty( WPARAM wparam, LPARAM lparam )
{
	BOOL bSuccess = *(BOOL*)lparam;
	if ( !bSuccess )
	{
		//MSG_BOX_OK( "恢复默认设置失败" );
		WARNMESSAGE( "恢复音频接口默认设置失败" );
		GetAudioInfo();
		SetAudioData();
		return S_FALSE;
	}
	else
	{
		SetDefaultAudioInfo();
		memcpy( m_atOldAudioPortInfo, m_atAudioPortInfo, sizeof(m_atAudioPortInfo) );
		SetAudioData();
		m_vctWndName.clear();
		UpBtnState();
	}	
	return S_OK;
}

HRESULT CCfgAudioPortLogic::OnSetDesktopMicNty(WPARAM wparam, LPARAM lparam)
{
	BOOL bDesktopMic = *(BOOL*)lparam;

	m_bOldNodeskTopBtn = bDesktopMic;

	if( bDesktopMic )
	{
		m_bNodeskTopBtn = true;
		UIFACTORYMGR_PTR->SetCheckState( m_strNoDesktopAudioGroup, 1, m_pWndTree );
	}
	else
	{
		m_bNodeskTopBtn = false;
		UIFACTORYMGR_PTR->SetCheckState( m_strNoDesktopAudioGroup, 0, m_pWndTree );
	}

	return S_OK;
}

HRESULT CCfgAudioPortLogic::OnSetDesktopMicInd(WPARAM wparam, LPARAM lparam)
{
	BOOL bSuccess = *(BOOL*)wparam;
	BOOL bDesktopMic = *(BOOL*)lparam;

	m_bOldNodeskTopBtn = bDesktopMic;

	if( !bSuccess )
	{
		WARNMESSAGE( "非桌面麦克风请求设置失败" );
		return S_FALSE;
	}

	if( bDesktopMic )
	{
		m_bNodeskTopBtn = true;
		UIFACTORYMGR_PTR->SetCheckState( m_strNoDesktopAudioGroup, 1, m_pWndTree );
	}
	else
	{
		m_bNodeskTopBtn = false;
		UIFACTORYMGR_PTR->SetCheckState( m_strNoDesktopAudioGroup, 0, m_pWndTree );
	}

	return S_OK;
}

HRESULT CCfgAudioPortLogic::OnSetMic10InfoInd(WPARAM wparam, LPARAM lparam)
{
	BOOL bSuccess = *(BOOL*)(wparam);

	if( !bSuccess )
	{
		WARNMESSAGE( "卡龙麦克风10请求设置失败" );
		return S_FALSE;
	}

	TTpMic10Info tTpMic10Info = *(TTpMic10Info*)(lparam);
	m_tTpMic10Info = tTpMic10Info;
	m_tOldTpMic10Info = tTpMic10Info;

	if( tTpMic10Info.m_emGroupIndex == em_GroupNum1 )
	{
		UIFACTORYMGR_PTR->SetCheckState( m_strAudioPort110, 1, m_pWndTree );
		UIFACTORYMGR_PTR->SetCheckState( m_strNoPort10, 0, m_pWndTree );
	}
	else if( tTpMic10Info.m_emGroupIndex == em_GroupNum2 )
	{
		UIFACTORYMGR_PTR->SetCheckState( m_strAudioPort210, 1, m_pWndTree );
		UIFACTORYMGR_PTR->SetCheckState( m_strNoPort10, 0, m_pWndTree );
	}
	else if( tTpMic10Info.m_emGroupIndex == em_GroupNum3 )
	{
		UIFACTORYMGR_PTR->SetCheckState( m_strAudioPort310, 1, m_pWndTree );
		UIFACTORYMGR_PTR->SetCheckState( m_strNoPort10, 0, m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->SetCheckState( m_strNoPort10, 1, m_pWndTree );
	}

	if( tTpMic10Info.m_bAudioPort )
	{
		UIFACTORYMGR_PTR->SetCheckState( m_strAudioPort10, 1, m_pWndTree );
		UIFACTORYMGR_PTR->LoadScheme( "SelAudio10", m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->SetCheckState( m_strAudioPort10, 0, m_pWndTree );
		UIFACTORYMGR_PTR->LoadScheme( "NoSelAudio10", m_pWndTree );
	}

	return S_OK;
}

/*---------------------------------------------------------------------
* 函数名称：UpdateGroup1
* 功    能：更新音频设置界面的Group1
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2012/12/29	v1.0		景洋洋		创建
----------------------------------------------------------------------*/
bool CCfgAudioPortLogic::UpdateGroup1( TTpAudioPortInfo& tAudioPortInfo )
{	
	if (tAudioPortInfo.m_byGroupIndex == 0)
	{
		bool bstate = false;
		s8 chData[8] = {0};
		Value_CSliderCtrlPos valuePos;
 		for( int i = 0; i <4; i++ )
 		{
			switch(i)
			{
			case 0:
				//增益
				valuePos.nPos = tAudioPortInfo.m_atSingleAudioPortCfg[i].byMicVolume;
				UIFACTORYMGR_PTR->SetPropertyValue( valuePos,"CfgAudioPortDlg/SliderGain1",m_pWndTree );
				sprintf( chData, "%u", tAudioPortInfo.m_atSingleAudioPortCfg[i].byMicVolume );
				UIFACTORYMGR_PTR->SetCaption( "CfgAudioPortDlg/GainEdit1", chData, m_pWndTree);
				//幻象开关
				bstate = tAudioPortInfo.m_atSingleAudioPortCfg[i].bIsSimplexPoweringOpened;
				UIFACTORYMGR_PTR->SetSwitchState( "CfgAudioPortDlg/BtnSimPower1", bstate, m_pWndTree);
				//背景噪声
				valuePos.nPos = tAudioPortInfo.m_atSingleAudioPortCfg[i].byAudioBNA;
				UIFACTORYMGR_PTR->SetPropertyValue( valuePos,"CfgAudioPortDlg/SliderBNA1",m_pWndTree );
				sprintf( chData, "%u", tAudioPortInfo.m_atSingleAudioPortCfg[i].byAudioBNA );
				UIFACTORYMGR_PTR->SetCaption( "CfgAudioPortDlg/BNAEdit1", chData, m_pWndTree);
				if ( TRUE == tAudioPortInfo.m_abAudioPort[i] )
				{
					UIFACTORYMGR_PTR->SetCheckState( m_strAudioPort1, 1, m_pWndTree );
				} 
				else
				{					
					UIFACTORYMGR_PTR->LoadScheme( "NoSelAudio1", m_pWndTree );
				}
				break;
			case 1:
				//增益
				valuePos.nPos = tAudioPortInfo.m_atSingleAudioPortCfg[i].byMicVolume;
				UIFACTORYMGR_PTR->SetPropertyValue( valuePos,"CfgAudioPortDlg/SliderGain2",m_pWndTree );
				sprintf( chData, "%u", tAudioPortInfo.m_atSingleAudioPortCfg[i].byMicVolume );
				UIFACTORYMGR_PTR->SetCaption( "CfgAudioPortDlg/GainEdit2", chData, m_pWndTree);
				//幻象开关
				bstate = tAudioPortInfo.m_atSingleAudioPortCfg[i].bIsSimplexPoweringOpened;
				UIFACTORYMGR_PTR->SetSwitchState( "CfgAudioPortDlg/BtnSimPower2", bstate, m_pWndTree);
				//背景噪声
				valuePos.nPos = tAudioPortInfo.m_atSingleAudioPortCfg[i].byAudioBNA;
				UIFACTORYMGR_PTR->SetPropertyValue( valuePos,"CfgAudioPortDlg/SliderBNA2",m_pWndTree );
				sprintf( chData, "%u", tAudioPortInfo.m_atSingleAudioPortCfg[i].byAudioBNA );
				UIFACTORYMGR_PTR->SetCaption( "CfgAudioPortDlg/BNAEdit2", chData, m_pWndTree);
				if ( TRUE == tAudioPortInfo.m_abAudioPort[i] )
				{
					UIFACTORYMGR_PTR->SetCheckState( m_strAudioPort2, 1, m_pWndTree );
				} 
				else
				{					
					UIFACTORYMGR_PTR->LoadScheme( "NoSelAudio2", m_pWndTree );
				}
				break;
			case 2:
				//增益
				valuePos.nPos = tAudioPortInfo.m_atSingleAudioPortCfg[i].byMicVolume;
				UIFACTORYMGR_PTR->SetPropertyValue( valuePos,"CfgAudioPortDlg/SliderGain3",m_pWndTree );
				sprintf( chData, "%u", tAudioPortInfo.m_atSingleAudioPortCfg[i].byMicVolume );
				UIFACTORYMGR_PTR->SetCaption( "CfgAudioPortDlg/GainEdit3", chData, m_pWndTree);
				//幻象开关
				bstate = tAudioPortInfo.m_atSingleAudioPortCfg[i].bIsSimplexPoweringOpened;
				UIFACTORYMGR_PTR->SetSwitchState( "CfgAudioPortDlg/BtnSimPower3", bstate, m_pWndTree);
				//背景噪声
				valuePos.nPos = tAudioPortInfo.m_atSingleAudioPortCfg[i].byAudioBNA;
				UIFACTORYMGR_PTR->SetPropertyValue( valuePos,"CfgAudioPortDlg/SliderBNA3",m_pWndTree );
				sprintf( chData, "%u", tAudioPortInfo.m_atSingleAudioPortCfg[i].byAudioBNA );
				UIFACTORYMGR_PTR->SetCaption( "CfgAudioPortDlg/BNAEdit3", chData, m_pWndTree);
				if ( TRUE == tAudioPortInfo.m_abAudioPort[i] )
				{
					UIFACTORYMGR_PTR->SetCheckState( m_strAudioPort3, 1, m_pWndTree );
				} 
				else
				{					
					UIFACTORYMGR_PTR->LoadScheme( "NoSelAudio3", m_pWndTree );
				}
				break;
			case 3:
				if ( TRUE == tAudioPortInfo.m_abAudioPort[i] )
				{
					UIFACTORYMGR_PTR->SetCheckState( m_strAudioPort110, 1, m_pWndTree );
					//增益
					valuePos.nPos = tAudioPortInfo.m_atSingleAudioPortCfg[i].byMicVolume;
					UIFACTORYMGR_PTR->SetPropertyValue( valuePos,"CfgAudioPortDlg/SliderGain10",m_pWndTree );
					sprintf( chData, "%u", tAudioPortInfo.m_atSingleAudioPortCfg[i].byMicVolume );
					UIFACTORYMGR_PTR->SetCaption( "CfgAudioPortDlg/GainEdit10", chData, m_pWndTree);
					//幻象开关
					bstate = tAudioPortInfo.m_atSingleAudioPortCfg[i].bIsSimplexPoweringOpened;
					UIFACTORYMGR_PTR->SetSwitchState( "CfgAudioPortDlg/BtnSimPower10", bstate, m_pWndTree);
					//背景噪声
					valuePos.nPos = tAudioPortInfo.m_atSingleAudioPortCfg[i].byAudioBNA;
					UIFACTORYMGR_PTR->SetPropertyValue( valuePos,"CfgAudioPortDlg/SliderBNA10",m_pWndTree );
					sprintf( chData, "%u", tAudioPortInfo.m_atSingleAudioPortCfg[i].byAudioBNA );
					UIFACTORYMGR_PTR->SetCaption( "CfgAudioPortDlg/BNAEdit10", chData, m_pWndTree);
				} 
				break;
			default:
				break;
			}
 		}
	} 
	else
	{	
		return false; 
	}
	return true;
}
/*---------------------------------------------------------------------
* 函数名称：UpdateGroup2
* 功    能：更新音频设置界面的Group2
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2012/12/29	v1.0		景洋洋		创建
----------------------------------------------------------------------*/
bool CCfgAudioPortLogic::UpdateGroup2( TTpAudioPortInfo& tAudioPortInfo )
{
	if (tAudioPortInfo.m_byGroupIndex == 1)
	{
		bool bstate = false;
		s8 chData[8] = {0};
		Value_CSliderCtrlPos valuePos;
		for( int i = 0; i <4; i++ )
		{
			switch( i )
			{
			case 0:
				//增益
				valuePos.nPos = tAudioPortInfo.m_atSingleAudioPortCfg[i].byMicVolume;
				UIFACTORYMGR_PTR->SetPropertyValue( valuePos,"CfgAudioPortDlg/SliderGain4",m_pWndTree );
				sprintf( chData, "%u", tAudioPortInfo.m_atSingleAudioPortCfg[i].byMicVolume );
				UIFACTORYMGR_PTR->SetCaption( "CfgAudioPortDlg/GainEdit4", chData, m_pWndTree);
				//幻象开关
				bstate = tAudioPortInfo.m_atSingleAudioPortCfg[i].bIsSimplexPoweringOpened;
				UIFACTORYMGR_PTR->SetSwitchState( "CfgAudioPortDlg/BtnSimPower4", bstate, m_pWndTree);
				//背景噪声
				valuePos.nPos = tAudioPortInfo.m_atSingleAudioPortCfg[i].byAudioBNA;
				UIFACTORYMGR_PTR->SetPropertyValue( valuePos,"CfgAudioPortDlg/SliderBNA4",m_pWndTree );
				sprintf( chData, "%u", tAudioPortInfo.m_atSingleAudioPortCfg[i].byAudioBNA );
				UIFACTORYMGR_PTR->SetCaption( "CfgAudioPortDlg/BNAEdit4", chData, m_pWndTree);
				if ( TRUE == tAudioPortInfo.m_abAudioPort[i] )
				{
					UIFACTORYMGR_PTR->SetCheckState( m_strAudioPort4, 1, m_pWndTree );
				} 
				else
				{					
					UIFACTORYMGR_PTR->LoadScheme( "NoSelAudio4", m_pWndTree );
				}
				break;
			case 1:
				//增益
				valuePos.nPos = tAudioPortInfo.m_atSingleAudioPortCfg[i].byMicVolume;
				UIFACTORYMGR_PTR->SetPropertyValue( valuePos,"CfgAudioPortDlg/SliderGain5",m_pWndTree );
				sprintf( chData, "%u", tAudioPortInfo.m_atSingleAudioPortCfg[i].byMicVolume );
				UIFACTORYMGR_PTR->SetCaption( "CfgAudioPortDlg/GainEdit5", chData, m_pWndTree);
				//幻象开关
				bstate = tAudioPortInfo.m_atSingleAudioPortCfg[i].bIsSimplexPoweringOpened;
				UIFACTORYMGR_PTR->SetSwitchState( "CfgAudioPortDlg/BtnSimPower5", bstate, m_pWndTree);
				//背景噪声
				valuePos.nPos = tAudioPortInfo.m_atSingleAudioPortCfg[i].byAudioBNA;
				UIFACTORYMGR_PTR->SetPropertyValue( valuePos,"CfgAudioPortDlg/SliderBNA5",m_pWndTree );
				sprintf( chData, "%u", tAudioPortInfo.m_atSingleAudioPortCfg[i].byAudioBNA );
				UIFACTORYMGR_PTR->SetCaption( "CfgAudioPortDlg/BNAEdit5", chData, m_pWndTree);
				if ( TRUE == tAudioPortInfo.m_abAudioPort[i] )
				{
					UIFACTORYMGR_PTR->SetCheckState( m_strAudioPort5, 1, m_pWndTree );
				} 
				else
				{					
					UIFACTORYMGR_PTR->LoadScheme( "NoSelAudio5", m_pWndTree );
				}
				break;
			case 2:
				//增益
				valuePos.nPos = tAudioPortInfo.m_atSingleAudioPortCfg[i].byMicVolume;
				UIFACTORYMGR_PTR->SetPropertyValue( valuePos,"CfgAudioPortDlg/SliderGain6",m_pWndTree );
				sprintf( chData, "%u", tAudioPortInfo.m_atSingleAudioPortCfg[i].byMicVolume );
				UIFACTORYMGR_PTR->SetCaption( "CfgAudioPortDlg/GainEdit6", chData, m_pWndTree);
				//幻象开关
				bstate = tAudioPortInfo.m_atSingleAudioPortCfg[i].bIsSimplexPoweringOpened;
				UIFACTORYMGR_PTR->SetSwitchState( "CfgAudioPortDlg/BtnSimPower6", bstate, m_pWndTree);
				//背景噪声
				valuePos.nPos = tAudioPortInfo.m_atSingleAudioPortCfg[i].byAudioBNA;
				UIFACTORYMGR_PTR->SetPropertyValue( valuePos,"CfgAudioPortDlg/SliderBNA6",m_pWndTree );
				sprintf( chData, "%u", tAudioPortInfo.m_atSingleAudioPortCfg[i].byAudioBNA );
				UIFACTORYMGR_PTR->SetCaption( "CfgAudioPortDlg/BNAEdit6", chData, m_pWndTree);
				if ( TRUE == tAudioPortInfo.m_abAudioPort[i] )
				{
					UIFACTORYMGR_PTR->SetCheckState( m_strAudioPort6, 1, m_pWndTree );
				} 
				else
				{					
					UIFACTORYMGR_PTR->LoadScheme( "NoSelAudio6", m_pWndTree );
				}
				break;
			case 3:
				if ( TRUE == tAudioPortInfo.m_abAudioPort[i] )
				{
					//增益
					valuePos.nPos = tAudioPortInfo.m_atSingleAudioPortCfg[i].byMicVolume;
					UIFACTORYMGR_PTR->SetPropertyValue( valuePos,"CfgAudioPortDlg/SliderGain10",m_pWndTree );
					sprintf( chData, "%u", tAudioPortInfo.m_atSingleAudioPortCfg[i].byMicVolume );
					UIFACTORYMGR_PTR->SetCaption( "CfgAudioPortDlg/GainEdit10", chData, m_pWndTree);
					//幻象开关
					bstate = tAudioPortInfo.m_atSingleAudioPortCfg[i].bIsSimplexPoweringOpened;
					UIFACTORYMGR_PTR->SetSwitchState( "CfgAudioPortDlg/BtnSimPower10", bstate, m_pWndTree);
					//背景噪声
					valuePos.nPos = tAudioPortInfo.m_atSingleAudioPortCfg[i].byAudioBNA;
					UIFACTORYMGR_PTR->SetPropertyValue( valuePos,"CfgAudioPortDlg/SliderBNA10",m_pWndTree );
					sprintf( chData, "%u", tAudioPortInfo.m_atSingleAudioPortCfg[i].byAudioBNA );
					UIFACTORYMGR_PTR->SetCaption( "CfgAudioPortDlg/BNAEdit10", chData, m_pWndTree);
					
					UIFACTORYMGR_PTR->SetCheckState( m_strAudioPort210, 1, m_pWndTree );
				} 
				break;
			default:
				break;
			}
		}
	}
	else
	{	
		return false; 
	}
	return true;
}
/*---------------------------------------------------------------------
* 函数名称：UpdateGroup3
* 功    能：更新音频设置界面的Group3
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2012/12/29	v1.0		景洋洋		创建
----------------------------------------------------------------------*/
bool CCfgAudioPortLogic::UpdateGroup3( TTpAudioPortInfo& tAudioPortInfo )
{
	if (tAudioPortInfo.m_byGroupIndex == 2)
	{
		bool bstate = false;
		s8 chData[8] = {0};
		Value_CSliderCtrlPos valuePos;
		for( int i = 0; i <4; i++ )
		{
			switch( i )
			{
			case 0:
				//增益
				valuePos.nPos = tAudioPortInfo.m_atSingleAudioPortCfg[i].byMicVolume;
				UIFACTORYMGR_PTR->SetPropertyValue( valuePos,"CfgAudioPortDlg/SliderGain7",m_pWndTree );
				sprintf( chData, "%u", tAudioPortInfo.m_atSingleAudioPortCfg[i].byMicVolume );
				UIFACTORYMGR_PTR->SetCaption( "CfgAudioPortDlg/GainEdit7", chData, m_pWndTree);
				//幻象开关
				bstate = tAudioPortInfo.m_atSingleAudioPortCfg[i].bIsSimplexPoweringOpened;
				UIFACTORYMGR_PTR->SetSwitchState( "CfgAudioPortDlg/BtnSimPower7", bstate, m_pWndTree);
				//背景噪声
				valuePos.nPos = tAudioPortInfo.m_atSingleAudioPortCfg[i].byAudioBNA;
				UIFACTORYMGR_PTR->SetPropertyValue( valuePos,"CfgAudioPortDlg/SliderBNA7",m_pWndTree );
				sprintf( chData, "%u", tAudioPortInfo.m_atSingleAudioPortCfg[i].byAudioBNA );
				UIFACTORYMGR_PTR->SetCaption( "CfgAudioPortDlg/BNAEdit7", chData, m_pWndTree);
				if ( TRUE == tAudioPortInfo.m_abAudioPort[i] )
				{
					UIFACTORYMGR_PTR->SetCheckState( m_strAudioPort7, 1, m_pWndTree );
				} 
				else
				{					
					UIFACTORYMGR_PTR->LoadScheme( "NoSelAudio7", m_pWndTree );
				}
				break;
			case 1:
				//增益
				valuePos.nPos = tAudioPortInfo.m_atSingleAudioPortCfg[i].byMicVolume;
				UIFACTORYMGR_PTR->SetPropertyValue( valuePos,"CfgAudioPortDlg/SliderGain8",m_pWndTree );
				sprintf( chData, "%u", tAudioPortInfo.m_atSingleAudioPortCfg[i].byMicVolume );
				UIFACTORYMGR_PTR->SetCaption( "CfgAudioPortDlg/GainEdit8", chData, m_pWndTree);
				//幻象开关
				bstate = tAudioPortInfo.m_atSingleAudioPortCfg[i].bIsSimplexPoweringOpened;
				UIFACTORYMGR_PTR->SetSwitchState( "CfgAudioPortDlg/BtnSimPower8", bstate, m_pWndTree);
				//背景噪声
				valuePos.nPos = tAudioPortInfo.m_atSingleAudioPortCfg[i].byAudioBNA;
				UIFACTORYMGR_PTR->SetPropertyValue( valuePos,"CfgAudioPortDlg/SliderBNA8",m_pWndTree );
				sprintf( chData, "%u", tAudioPortInfo.m_atSingleAudioPortCfg[i].byAudioBNA );
				UIFACTORYMGR_PTR->SetCaption( "CfgAudioPortDlg/BNAEdit8", chData, m_pWndTree);
				if ( TRUE == tAudioPortInfo.m_abAudioPort[i] )
				{
					UIFACTORYMGR_PTR->SetCheckState( m_strAudioPort8, 1, m_pWndTree );
				} 
				else
				{					
					UIFACTORYMGR_PTR->LoadScheme( "NoSelAudio8", m_pWndTree );
				}
				break;
			case 2:
				//增益
				valuePos.nPos = tAudioPortInfo.m_atSingleAudioPortCfg[i].byMicVolume;
				UIFACTORYMGR_PTR->SetPropertyValue( valuePos,"CfgAudioPortDlg/SliderGain9",m_pWndTree );
				sprintf( chData, "%u", tAudioPortInfo.m_atSingleAudioPortCfg[i].byMicVolume );
				UIFACTORYMGR_PTR->SetCaption( "CfgAudioPortDlg/GainEdit9", chData, m_pWndTree);
				//幻象开关
				bstate = tAudioPortInfo.m_atSingleAudioPortCfg[i].bIsSimplexPoweringOpened;
				UIFACTORYMGR_PTR->SetSwitchState( "CfgAudioPortDlg/BtnSimPower9", bstate, m_pWndTree);
				//背景噪声
				valuePos.nPos = tAudioPortInfo.m_atSingleAudioPortCfg[i].byAudioBNA;
				UIFACTORYMGR_PTR->SetPropertyValue( valuePos,"CfgAudioPortDlg/SliderBNA9",m_pWndTree );
				sprintf( chData, "%u", tAudioPortInfo.m_atSingleAudioPortCfg[i].byAudioBNA );
				UIFACTORYMGR_PTR->SetCaption( "CfgAudioPortDlg/BNAEdit9", chData, m_pWndTree);
				if ( TRUE == tAudioPortInfo.m_abAudioPort[i] )
				{
					UIFACTORYMGR_PTR->SetCheckState( m_strAudioPort9, 1, m_pWndTree );
				} 
				else
				{					
					UIFACTORYMGR_PTR->LoadScheme( "NoSelAudio9", m_pWndTree );
				}
				break;
			case 3:
				//增益
				valuePos.nPos = tAudioPortInfo.m_atSingleAudioPortCfg[i].byMicVolume;
				UIFACTORYMGR_PTR->SetPropertyValue( valuePos,"CfgAudioPortDlg/SliderGain10",m_pWndTree );
				sprintf( chData, "%u", tAudioPortInfo.m_atSingleAudioPortCfg[i].byMicVolume );
				UIFACTORYMGR_PTR->SetCaption( "CfgAudioPortDlg/GainEdit10", chData, m_pWndTree);
				//幻象开关
				bstate = tAudioPortInfo.m_atSingleAudioPortCfg[i].bIsSimplexPoweringOpened;
				UIFACTORYMGR_PTR->SetSwitchState( "CfgAudioPortDlg/BtnSimPower10", bstate, m_pWndTree);
				//背景噪声
				valuePos.nPos = tAudioPortInfo.m_atSingleAudioPortCfg[i].byAudioBNA;
				UIFACTORYMGR_PTR->SetPropertyValue( valuePos,"CfgAudioPortDlg/SliderBNA10",m_pWndTree );
				sprintf( chData, "%u", tAudioPortInfo.m_atSingleAudioPortCfg[i].byAudioBNA );
				UIFACTORYMGR_PTR->SetCaption( "CfgAudioPortDlg/BNAEdit10", chData, m_pWndTree);
				if ( TRUE == tAudioPortInfo.m_abAudioPort[i] )
				{
					UIFACTORYMGR_PTR->SetCheckState( m_strAudioPort310, 1, m_pWndTree );
				} 
				break;
			default:
				break;
			}
		}
	} 
	else
	{	
		return false; 
	}
	return true;
}

bool CCfgAudioPortLogic::IsCfgAudioChange()
{
	s32 n = m_vctWndName.size();
	if ( n > 0 )
	{
		return SaveMsgBox();
	}
  	return true;
}

bool CCfgAudioPortLogic::SaveMsgBox()
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

bool CCfgAudioPortLogic::OnSliderGain1Changed( const IArgs& args )
{
	UpdateGainNum( "CfgAudioPortDlg/SliderGain1", "CfgAudioPortDlg/GainEdit1" , 0, 0 );
	return true;
}

bool CCfgAudioPortLogic::OnSliderBNA1Changed( const IArgs& args )
{
	UpdateBNANum( "CfgAudioPortDlg/SliderBNA1", "CfgAudioPortDlg/BNAEdit1" , 0, 0 );
	return true;
}

bool CCfgAudioPortLogic::OnEditGain1Changed( const IArgs& args )
{
	UpdateGainEdit( "CfgAudioPortDlg/GainEdit1", "CfgAudioPortDlg/SliderGain1", 0, 0 );
	return true;
}

bool CCfgAudioPortLogic::OnEditBNA1Changed( const IArgs& args )
{
	UpdateBNAEdit( "CfgAudioPortDlg/BNAEdit1", "CfgAudioPortDlg/SliderBNA1", 0, 0 );
	return true;
}

bool CCfgAudioPortLogic::OnSliderGain2Changed( const IArgs& args )
{
	UpdateGainNum( "CfgAudioPortDlg/SliderGain2", "CfgAudioPortDlg/GainEdit2", 0, 1 );
	return true;
}

bool CCfgAudioPortLogic::OnSliderBNA2Changed( const IArgs& args )
{
	UpdateBNANum( "CfgAudioPortDlg/SliderBNA2", "CfgAudioPortDlg/BNAEdit2", 0, 1 );
	return true;
}

bool CCfgAudioPortLogic::OnEditGain2Changed( const IArgs& args )
{
	UpdateGainEdit( "CfgAudioPortDlg/GainEdit2", "CfgAudioPortDlg/SliderGain2", 0, 1 );
	return true;
}

bool CCfgAudioPortLogic::OnEditBNA2Changed( const IArgs& args )
{
	UpdateBNAEdit( "CfgAudioPortDlg/BNAEdit2", "CfgAudioPortDlg/SliderBNA2", 0, 1 );
	return true;
}

bool CCfgAudioPortLogic::OnSliderGain3Changed( const IArgs& args )
{
	UpdateGainNum( "CfgAudioPortDlg/SliderGain3", "CfgAudioPortDlg/GainEdit3", 0, 2 );
	return true;
}

bool CCfgAudioPortLogic::OnSliderBNA3Changed( const IArgs& args )
{
	UpdateBNANum( "CfgAudioPortDlg/SliderBNA3", "CfgAudioPortDlg/BNAEdit3", 0, 2 );
	return true;
}

bool CCfgAudioPortLogic::OnEditGain3Changed( const IArgs& args )
{
	UpdateGainEdit( "CfgAudioPortDlg/GainEdit3", "CfgAudioPortDlg/SliderGain3", 0, 2 );
	return true;
}

bool CCfgAudioPortLogic::OnEditBNA3Changed( const IArgs& args )
{
	UpdateBNAEdit( "CfgAudioPortDlg/BNAEdit3", "CfgAudioPortDlg/SliderBNA3", 0, 2 );
	return true;
}

bool CCfgAudioPortLogic::OnSliderGain4Changed( const IArgs& args )
{
	UpdateGainNum( "CfgAudioPortDlg/SliderGain4", "CfgAudioPortDlg/GainEdit4", 1, 0 );
	return true;
}

bool CCfgAudioPortLogic::OnSliderBNA4Changed( const IArgs& args )
{
	UpdateBNANum( "CfgAudioPortDlg/SliderBNA4", "CfgAudioPortDlg/BNAEdit4", 1, 0 );
	return true;
}

bool CCfgAudioPortLogic::OnEditGain4Changed( const IArgs& args )
{
	UpdateGainEdit( "CfgAudioPortDlg/GainEdit4", "CfgAudioPortDlg/SliderGain4", 1, 0 );
	return true;
}

bool CCfgAudioPortLogic::OnEditBNA4Changed( const IArgs& args )
{
	UpdateBNAEdit( "CfgAudioPortDlg/BNAEdit4", "CfgAudioPortDlg/SliderBNA4", 1, 0 );
	return true;
}

bool CCfgAudioPortLogic::OnSliderGain5Changed( const IArgs& args )
{
	UpdateGainNum( "CfgAudioPortDlg/SliderGain5", "CfgAudioPortDlg/GainEdit5" , 1, 1 );
	return true;
}

bool CCfgAudioPortLogic::OnSliderBNA5Changed( const IArgs& args )
{
	UpdateBNANum( "CfgAudioPortDlg/SliderBNA5", "CfgAudioPortDlg/BNAEdit5", 1, 1 );
	return true;
}

bool CCfgAudioPortLogic::OnEditGain5Changed( const IArgs& args )
{
	UpdateGainEdit( "CfgAudioPortDlg/GainEdit5", "CfgAudioPortDlg/SliderGain5", 1, 1 );
	return true;
}

bool CCfgAudioPortLogic::OnEditBNA5Changed( const IArgs& args )
{
	UpdateBNAEdit( "CfgAudioPortDlg/BNAEdit5", "CfgAudioPortDlg/SliderBNA5", 1, 1 );
	return true;
}

bool CCfgAudioPortLogic::OnSliderGain6Changed( const IArgs& args )
{
	UpdateGainNum( "CfgAudioPortDlg/SliderGain6", "CfgAudioPortDlg/GainEdit6", 1, 2 );
	return true;
}

bool CCfgAudioPortLogic::OnSliderBNA6Changed( const IArgs& args )
{
	UpdateBNANum( "CfgAudioPortDlg/SliderBNA6", "CfgAudioPortDlg/BNAEdit6", 1, 2 );
	return true;
}

bool CCfgAudioPortLogic::OnEditGain6Changed( const IArgs& args )
{
	UpdateGainEdit( "CfgAudioPortDlg/GainEdit6", "CfgAudioPortDlg/SliderGain6", 1, 2 );
	return true;
}

bool CCfgAudioPortLogic::OnEditBNA6Changed( const IArgs& args )
{
	UpdateBNAEdit( "CfgAudioPortDlg/BNAEdit6", "CfgAudioPortDlg/SliderBNA6", 1, 2 );
	return true;
}

bool CCfgAudioPortLogic::OnSliderGain7Changed( const IArgs& args )
{
	UpdateGainNum( "CfgAudioPortDlg/SliderGain7", "CfgAudioPortDlg/GainEdit7", 2, 0 );
	return true;
}

bool CCfgAudioPortLogic::OnSliderBNA7Changed( const IArgs& args )
{
	UpdateBNANum( "CfgAudioPortDlg/SliderBNA7", "CfgAudioPortDlg/BNAEdit7", 2, 0 );
	return true;
}

bool CCfgAudioPortLogic::OnEditGain7Changed( const IArgs& args )
{
	UpdateGainEdit( "CfgAudioPortDlg/GainEdit7", "CfgAudioPortDlg/SliderGain7", 2, 0 );
	return true;
}

bool CCfgAudioPortLogic::OnEditBNA7Changed( const IArgs& args )
{
	UpdateBNAEdit( "CfgAudioPortDlg/BNAEdit7", "CfgAudioPortDlg/SliderBNA7", 2, 0 );
	return true;
}

bool CCfgAudioPortLogic::OnSliderGain8Changed( const IArgs& args )
{
	UpdateGainNum( "CfgAudioPortDlg/SliderGain8", "CfgAudioPortDlg/GainEdit8", 2, 1 );
	return true;
}

bool CCfgAudioPortLogic::OnSliderBNA8Changed( const IArgs& args )
{
	UpdateBNANum( "CfgAudioPortDlg/SliderBNA8", "CfgAudioPortDlg/BNAEdit8", 2, 1 );
	return true;
}

bool CCfgAudioPortLogic::OnEditGain8Changed( const IArgs& args )
{
	UpdateGainEdit( "CfgAudioPortDlg/GainEdit8", "CfgAudioPortDlg/SliderGain8", 2, 1 );
	return true;
}

bool CCfgAudioPortLogic::OnEditBNA8Changed( const IArgs& args )
{
	UpdateBNAEdit( "CfgAudioPortDlg/BNAEdit8", "CfgAudioPortDlg/SliderBNA8", 2, 1 );
	return true;
}

bool CCfgAudioPortLogic::OnSliderGain9Changed( const IArgs& args )
{
	UpdateGainNum( "CfgAudioPortDlg/SliderGain9", "CfgAudioPortDlg/GainEdit9", 2, 2 );
	return true;
}

bool CCfgAudioPortLogic::OnSliderBNA9Changed( const IArgs& args )
{
	UpdateBNANum( "CfgAudioPortDlg/SliderBNA9", "CfgAudioPortDlg/BNAEdit9", 2, 2 );
	return true;
}

bool CCfgAudioPortLogic::OnEditGain9Changed( const IArgs& args )
{
	UpdateGainEdit( "CfgAudioPortDlg/GainEdit9", "CfgAudioPortDlg/SliderGain9", 2, 2 );
	return true;
}

bool CCfgAudioPortLogic::OnEditBNA9Changed( const IArgs& args )
{
	UpdateBNAEdit( "CfgAudioPortDlg/BNAEdit9", "CfgAudioPortDlg/SliderBNA9", 2, 2 );
	return true;
}

bool CCfgAudioPortLogic::OnSliderGain10Changed( const IArgs& args )
{
	if ( TRUE == m_atOldAudioPortInfo[0].m_abAudioPort[3] )
	{
		UpdateGainNum( "CfgAudioPortDlg/SliderGain10", "CfgAudioPortDlg/GainEdit10", 0, 3 );
	} 
	else if ( TRUE == m_atOldAudioPortInfo[1].m_abAudioPort[3] )
	{
		UpdateGainNum( "CfgAudioPortDlg/SliderGain10", "CfgAudioPortDlg/GainEdit10", 1, 3 );
	}
	else if ( TRUE == m_atOldAudioPortInfo[2].m_abAudioPort[3] )
	{
		UpdateGainNum( "CfgAudioPortDlg/SliderGain10", "CfgAudioPortDlg/GainEdit10", 2, 3 );
	}
	else if ( FALSE == m_atOldAudioPortInfo[0].m_abAudioPort[3] && FALSE == m_atOldAudioPortInfo[1].m_abAudioPort[3] && FALSE == m_atOldAudioPortInfo[2].m_abAudioPort[3] )
	{
		UpdateGainNum( "CfgAudioPortDlg/SliderGain10", "CfgAudioPortDlg/GainEdit10", 2, 3 );
	}
	return true;
}

bool CCfgAudioPortLogic::OnSliderBNA10Changed( const IArgs& args )
{
	if ( TRUE == m_atOldAudioPortInfo[0].m_abAudioPort[3] )
	{
		UpdateBNANum( "CfgAudioPortDlg/SliderBNA10", "CfgAudioPortDlg/BNAEdit10", 0, 3 );
	} 
	else if ( TRUE == m_atOldAudioPortInfo[1].m_abAudioPort[3] )
	{
		UpdateBNANum( "CfgAudioPortDlg/SliderBNA10", "CfgAudioPortDlg/BNAEdit10", 1, 3 );
	}
	else if ( TRUE == m_atOldAudioPortInfo[2].m_abAudioPort[3] )
	{
		UpdateBNANum( "CfgAudioPortDlg/SliderBNA10", "CfgAudioPortDlg/BNAEdit10", 2, 3 );
	}
	else if ( FALSE == m_atOldAudioPortInfo[0].m_abAudioPort[3] && FALSE == m_atOldAudioPortInfo[1].m_abAudioPort[3] && FALSE == m_atOldAudioPortInfo[2].m_abAudioPort[3] )
	{
		UpdateBNANum( "CfgAudioPortDlg/SliderBNA10", "CfgAudioPortDlg/BNAEdit10", 2, 3 );
	}
	return true;
}

bool CCfgAudioPortLogic::OnEditGain10Changed( const IArgs& args )
{
	if ( TRUE == m_atOldAudioPortInfo[0].m_abAudioPort[3] )
	{
		UpdateGainEdit( "CfgAudioPortDlg/GainEdit10", "CfgAudioPortDlg/SliderGain10", 0, 3 );
	} 
	else if ( TRUE == m_atOldAudioPortInfo[1].m_abAudioPort[3] )
	{
		UpdateGainEdit( "CfgAudioPortDlg/GainEdit10", "CfgAudioPortDlg/SliderGain10", 1, 3 );
	}
	else if ( TRUE == m_atOldAudioPortInfo[2].m_abAudioPort[3] )
	{
		UpdateGainEdit( "CfgAudioPortDlg/GainEdit10", "CfgAudioPortDlg/SliderGain10", 2, 3 );
	}
	else if ( FALSE == m_atOldAudioPortInfo[0].m_abAudioPort[3] && FALSE == m_atOldAudioPortInfo[1].m_abAudioPort[3] && FALSE == m_atOldAudioPortInfo[2].m_abAudioPort[3] )
	{
		UpdateGainEdit( "CfgAudioPortDlg/GainEdit10", "CfgAudioPortDlg/SliderGain10", 2, 3 );
	}
	return true;
}

bool CCfgAudioPortLogic::OnEditBNA10Changed( const IArgs& args )
{
	if ( TRUE == m_atOldAudioPortInfo[0].m_abAudioPort[3] )
	{
		UpdateBNAEdit( "CfgAudioPortDlg/BNAEdit10", "CfgAudioPortDlg/SliderBNA10", 0, 3 );
	} 
	else if ( TRUE == m_atOldAudioPortInfo[1].m_abAudioPort[3] )
	{
		UpdateBNAEdit( "CfgAudioPortDlg/BNAEdit10", "CfgAudioPortDlg/SliderBNA10", 1, 3 );
	}
	else if ( TRUE == m_atOldAudioPortInfo[2].m_abAudioPort[3] )
	{
		UpdateBNAEdit( "CfgAudioPortDlg/BNAEdit10", "CfgAudioPortDlg/SliderBNA10", 2, 3 );
	}
	else if ( FALSE == m_atOldAudioPortInfo[0].m_abAudioPort[3] && FALSE == m_atOldAudioPortInfo[1].m_abAudioPort[3] && FALSE == m_atOldAudioPortInfo[2].m_abAudioPort[3] )
	{
		UpdateBNAEdit( "CfgAudioPortDlg/BNAEdit10", "CfgAudioPortDlg/SliderBNA10", 2, 3 );
	}
	return true;
}

bool CCfgAudioPortLogic::OnSelAudio1( const IArgs& args )
{
	return UpdateCheckNum( m_strAudioPort1, 0, 0, "SelAudio1", "NoSelAudio1" );
}

bool CCfgAudioPortLogic::OnSelAudio2( const IArgs& args )
{
	return UpdateCheckNum( m_strAudioPort2, 0, 1, "SelAudio2", "NoSelAudio2" );	
}

bool CCfgAudioPortLogic::OnSelAudio3( const IArgs& args )
{
	return UpdateCheckNum( m_strAudioPort3, 0, 2, "SelAudio3", "NoSelAudio3" );	
}

bool CCfgAudioPortLogic::OnSelAudio4( const IArgs& args )
{
	return UpdateCheckNum( m_strAudioPort4, 1, 0, "SelAudio4", "NoSelAudio4" );	
}

bool CCfgAudioPortLogic::OnSelAudio5( const IArgs& args )
{
	return UpdateCheckNum( m_strAudioPort5, 1, 1, "SelAudio5", "NoSelAudio5" );	
}

bool CCfgAudioPortLogic::OnSelAudio6( const IArgs& args )
{
	return UpdateCheckNum( m_strAudioPort6, 1, 2, "SelAudio6", "NoSelAudio6" );	
}

bool CCfgAudioPortLogic::OnSelAudio7( const IArgs& args )
{
	return UpdateCheckNum( m_strAudioPort7, 2, 0, "SelAudio7", "NoSelAudio7" );		
}

bool CCfgAudioPortLogic::OnSelAudio8( const IArgs& args )
{
	return UpdateCheckNum( m_strAudioPort8, 2, 1, "SelAudio8", "NoSelAudio8" );	
}

bool CCfgAudioPortLogic::OnSelAudio9( const IArgs& args )
{
	return UpdateCheckNum( m_strAudioPort9, 2, 2, "SelAudio9", "NoSelAudio9" );	
}

bool CCfgAudioPortLogic::OnSelAudioPort10(const IArgs& args)
{
	s32 nCheckState = 0;
	UIFACTORYMGR_PTR->GetCheckState( m_strAudioPort10, nCheckState, m_pWndTree );

	if( 0 == nCheckState )
	{
		UIFACTORYMGR_PTR->LoadScheme( "NoSelAudio10", m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( "SelAudio10", m_pWndTree );
	}

	bool bChange = false;
	if ( nCheckState != m_tOldTpMic10Info.m_bAudioPort )
	{
		bChange = true;
	}

	CheckData( "AudioPort10", bChange );
	
	return true;
}

bool CCfgAudioPortLogic::OnNoSelAudio10( const IArgs& args )
{
	bool bChange = false;
	//GetAudioInfo();
	if ( m_tOldTpMic10Info.m_emGroupIndex != em_GroupNum4 )
	{
		bChange = true;	
	} 
	CheckData("Audio10",bChange);
	//UIFACTORYMGR_PTR->LoadScheme( "NoSelAudio10", m_pWndTree );
	return true;
}

bool CCfgAudioPortLogic::OnSelAudio10( const IArgs& args )
{
	bool bChange = false;
	s32 nCheckState110 = 0;
	UIFACTORYMGR_PTR->GetCheckState( m_strAudioPort110, nCheckState110, m_pWndTree );
	s32 nCheckState210 = 0;
	UIFACTORYMGR_PTR->GetCheckState( m_strAudioPort210, nCheckState210, m_pWndTree );
	s32 nCheckState310 = 0;
	UIFACTORYMGR_PTR->GetCheckState( m_strAudioPort310, nCheckState310, m_pWndTree );	

	//GetAudioInfo();
	if ( nCheckState110 == 1 )
	{		
		if ( m_tOldTpMic10Info.m_emGroupIndex != em_GroupNum1 )
		{
			bChange = true;
		}	
		CheckData("Audio10",bChange);
	} 
	else if ( nCheckState210 == 1 )
	{
		if ( m_tOldTpMic10Info.m_emGroupIndex != em_GroupNum2 )
		{
			bChange = true;
		}	
		CheckData("Audio10",bChange);
	}
	else if ( nCheckState310 == 1 )
	{
		if ( m_tOldTpMic10Info.m_emGroupIndex != em_GroupNum3 )
		{
			bChange = true;
		}	
		CheckData("Audio10",bChange);
	}	
	//UIFACTORYMGR_PTR->LoadScheme( "SelAudio10", NULL, g_strCfgAudioPort );
	return false;
}

bool CCfgAudioPortLogic::OnSelNoDesktopAudio(const IArgs& args)
{
	bool bChange = false;

	if( m_bNodeskTopBtn )
	{
		UIFACTORYMGR_PTR->SetCheckState( m_strNoDesktopAudioGroup, 0, m_pWndTree );
		m_bNodeskTopBtn = false;
	}
	else
	{
		UIFACTORYMGR_PTR->SetCheckState( m_strNoDesktopAudioGroup, 1, m_pWndTree );
		m_bNodeskTopBtn = true;
	}

	if( m_bNodeskTopBtn != m_bOldNodeskTopBtn )
	{
		bChange = true;
	}

	CheckData("NoDesktopAudioGroup", bChange);
	return true;
}

void CCfgAudioPortLogic::SetAudioData()
{
	if ( m_pWndTree == NULL )
	{
		return;
	}
	//将界面控件初始化
	InitCtrlEnable();

	UpdateGroup3( m_atOldAudioPortInfo[2] );
	UpdateGroup1( m_atOldAudioPortInfo[0] );
	UpdateGroup2( m_atOldAudioPortInfo[1] );
	
// 	if ( !m_atOldAudioPortInfo[0].m_abAudioPort[3] && !m_atOldAudioPortInfo[1].m_abAudioPort[3] && !m_atOldAudioPortInfo[2].m_abAudioPort[3] )
// 	{
// 		UIFACTORYMGR_PTR->SetCheckState( m_strNoPort10, 1, m_pWndTree );
// 		//UIFACTORYMGR_PTR->LoadScheme( "NoSelAudio10", m_pWndTree );
// 	}	
}

void CCfgAudioPortLogic::GetAudioInfo()
{	
	TTpAudioPortInfo* pAudioPortInfo = NULL;
	LIBDATAMGRPTR->GetAudioPortInfo( &pAudioPortInfo );
	for ( int i = 0; i < 3; i++ )
    {
        m_atOldAudioPortInfo[i] = *( pAudioPortInfo + i );        
    }
}

bool CCfgAudioPortLogic::OnBtnSwitchSimPower1( const IArgs& args )
{	
	UpdateSimPowerNum("CfgAudioPortDlg/BtnSimPower1", 0, 0);
	return true;	
}

bool CCfgAudioPortLogic::OnBtnSwitchSimPower2( const IArgs& args )
{
	UpdateSimPowerNum("CfgAudioPortDlg/BtnSimPower2", 0, 1);
	return true;	
}

bool CCfgAudioPortLogic::OnBtnSwitchSimPower3( const IArgs& args )
{
	UpdateSimPowerNum("CfgAudioPortDlg/BtnSimPower3", 0, 2);
	return true;	
}

bool CCfgAudioPortLogic::OnBtnSwitchSimPower4( const IArgs& args )
{
	UpdateSimPowerNum("CfgAudioPortDlg/BtnSimPower4", 1, 0);
	return true;	
}

bool CCfgAudioPortLogic::OnBtnSwitchSimPower5( const IArgs& args )
{
	UpdateSimPowerNum("CfgAudioPortDlg/BtnSimPower5", 1, 1);
	return true;	
}

bool CCfgAudioPortLogic::OnBtnSwitchSimPower6( const IArgs& args )
{
	UpdateSimPowerNum("CfgAudioPortDlg/BtnSimPower6", 1, 2);
	return true;	
}

bool CCfgAudioPortLogic::OnBtnSwitchSimPower7( const IArgs& args )
{
	UpdateSimPowerNum("CfgAudioPortDlg/BtnSimPower7", 2, 0);
	return true;	
}

bool CCfgAudioPortLogic::OnBtnSwitchSimPower8( const IArgs& args )
{
	UpdateSimPowerNum("CfgAudioPortDlg/BtnSimPower8", 2, 1);
	return true;	
}

bool CCfgAudioPortLogic::OnBtnSwitchSimPower9( const IArgs& args )
{
	UpdateSimPowerNum("CfgAudioPortDlg/BtnSimPower9", 2, 2);
	return true;	
}

bool CCfgAudioPortLogic::OnBtnSwitchSimPower10( const IArgs& args )
{
	//GetAudioInfo();
	if ( TRUE == m_atOldAudioPortInfo[0].m_abAudioPort[3] )
	{
		UpdateSimPowerNum("CfgAudioPortDlg/BtnSimPower10", 0, 3);
	} 
	else if ( TRUE == m_atOldAudioPortInfo[1].m_abAudioPort[3] )
	{
		UpdateSimPowerNum("CfgAudioPortDlg/BtnSimPower10", 1, 3);
	}
	else if ( TRUE == m_atOldAudioPortInfo[2].m_abAudioPort[3] )
	{
		UpdateSimPowerNum("CfgAudioPortDlg/BtnSimPower10", 2, 3);
	}
	else if ( FALSE == m_atOldAudioPortInfo[0].m_abAudioPort[3] && FALSE == m_atOldAudioPortInfo[1].m_abAudioPort[3] && FALSE == m_atOldAudioPortInfo[2].m_abAudioPort[3] )
	{
		UpdateSimPowerNum("CfgAudioPortDlg/BtnSimPower10", 2, 3);
	}
	return true;	
}

void CCfgAudioPortLogic::UpdateSimPowerNum( String strWndName, s32 nGroup, s32 nNum )
{
	bool bSimPower = false;												//幻象开关
	UIFACTORYMGR_PTR->GetSwitchState( strWndName, bSimPower, m_pWndTree );
	bool bChange = false;
	//GetAudioInfo();
	if ( (BOOL)bSimPower != m_atOldAudioPortInfo[nGroup].m_atSingleAudioPortCfg[nNum].bIsSimplexPoweringOpened )
	{
		bChange = true;
	}	
	CheckData(strWndName,bChange);
}

void CCfgAudioPortLogic::UpdateGainNum( String strGainName, String strEditName, s32 nGroup, s32 nNum )
{
	Value_CSliderCtrlPos pos;
	UIFACTORYMGR_PTR->GetPropertyValue( pos, strGainName, m_pWndTree );
	s8 chData[8];
	sprintf( chData, "%u", pos.nPos );
	UIFACTORYMGR_PTR->SetCaption( strEditName, chData, m_pWndTree);
	
	//GetAudioInfo();
	bool bChange = false;
	if ( pos.nPos != m_atOldAudioPortInfo[nGroup].m_atSingleAudioPortCfg[nNum].byMicVolume )
	{
		bChange = true;
	}
	CheckData( strGainName, bChange );	
}

void CCfgAudioPortLogic::UpdateBNANum( String strBNAName, String strEditName, s32 nGroup, s32 nNum )
{
	Value_CSliderCtrlPos pos;
	UIFACTORYMGR_PTR->GetPropertyValue( pos,strBNAName,m_pWndTree );
	s8 chData[8];
	sprintf( chData, "%u", pos.nPos );
	UIFACTORYMGR_PTR->SetCaption( strEditName, chData, m_pWndTree );
	
	//GetAudioInfo();
	bool bChange = false;
	if ( pos.nPos != m_atOldAudioPortInfo[nGroup].m_atSingleAudioPortCfg[nNum].byAudioBNA )
	{
		bChange = true;
	}
	CheckData(strBNAName,bChange);	
}

void CCfgAudioPortLogic::UpdateGainEdit( String strEditName, String strSliderName, s32 nGroup, s32 nNum )
{
	String strEdit;
	UIFACTORYMGR_PTR->GetCaption( strEditName, strEdit, m_pWndTree );
	Value_CSliderCtrlPos pos;
	pos.nPos = atoi(strEdit.c_str());
	if ( pos.nPos >= 100 )
	{
		pos.nPos = 100;
	}
		
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
	if ( pos.nPos != m_atOldAudioPortInfo[nGroup].m_atSingleAudioPortCfg[nNum].byMicVolume )
	{
		bChange = true;
	}
	CheckData(strEditName,bChange);	
	CheckData(strSliderName,bChange);	//slider
}

void CCfgAudioPortLogic::UpdateBNAEdit( String strEditName, String strSliderName, s32 nGroup, s32 nNum )
{
	String strEdit;
	UIFACTORYMGR_PTR->GetCaption( strEditName, strEdit, m_pWndTree );
	Value_CSliderCtrlPos pos;
	pos.nPos = atoi(strEdit.c_str());
	if ( pos.nPos >= 3 )
	{
		pos.nPos = 3;
	}

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
	if ( pos.nPos != m_atOldAudioPortInfo[nGroup].m_atSingleAudioPortCfg[nNum].byAudioBNA )
	{
		bChange = true;
	}
	CheckData(strEditName,bChange);	
	CheckData(strSliderName,bChange);	//slider	
}

bool CCfgAudioPortLogic::UpdateCheckNum( String strCheckName, s32 nGroup, s32 nNum, String strShmShow, String strShmHide )
{
	s32 nCheckState = 0;
	UIFACTORYMGR_PTR->GetCheckState( strCheckName, nCheckState, m_pWndTree );
	//GetAudioInfo();
	bool bChange = false;
	if ( nCheckState != m_atOldAudioPortInfo[nGroup].m_abAudioPort[nNum] )
	{
		bChange = true;
	}
	CheckData(strCheckName,bChange);
	
	if ( 0 == nCheckState )
	{
		UIFACTORYMGR_PTR->LoadScheme( strShmHide, m_pWndTree );
		return false;
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( strShmShow, m_pWndTree );
		return true;
	}
}

void CCfgAudioPortLogic::InitCtrlEnable()
{
	UIFACTORYMGR_PTR->SetCheckState( m_strAudioPort1, 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( m_strAudioPort2, 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( m_strAudioPort3, 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( m_strAudioPort4, 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( m_strAudioPort5, 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( m_strAudioPort6, 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( m_strAudioPort7, 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( m_strAudioPort8, 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( m_strAudioPort9, 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( m_strAudioPort10, 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( m_strAudioPort110, 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( m_strAudioPort210, 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( m_strAudioPort310, 0, m_pWndTree );
	UIFACTORYMGR_PTR->SetCheckState( m_strNoPort10, 1, m_pWndTree );
	UIFACTORYMGR_PTR->LoadScheme( "SelAudio1", m_pWndTree );
	UIFACTORYMGR_PTR->LoadScheme( "SelAudio2", m_pWndTree );
	UIFACTORYMGR_PTR->LoadScheme( "SelAudio3", m_pWndTree );
	UIFACTORYMGR_PTR->LoadScheme( "SelAudio4", m_pWndTree );
	UIFACTORYMGR_PTR->LoadScheme( "SelAudio5", m_pWndTree );
	UIFACTORYMGR_PTR->LoadScheme( "SelAudio6", m_pWndTree );
	UIFACTORYMGR_PTR->LoadScheme( "SelAudio7", m_pWndTree );
	UIFACTORYMGR_PTR->LoadScheme( "SelAudio8", m_pWndTree );
	UIFACTORYMGR_PTR->LoadScheme( "SelAudio9", m_pWndTree );
	UIFACTORYMGR_PTR->LoadScheme( "NoSelAudio10", m_pWndTree );
}

void CCfgAudioPortLogic::SetDefaultAudioInfo()
{
	memset( m_atOldAudioPortInfo, 0, sizeof(m_atOldAudioPortInfo) );
	memset( &m_tOldTpMic10Info, 0, sizeof(m_tOldTpMic10Info) );
	m_atOldAudioPortInfo[0].m_byGroupIndex = 0;
	m_atOldAudioPortInfo[0].m_abAudioPort[0] = TRUE;
	m_atOldAudioPortInfo[0].m_atSingleAudioPortCfg[0].byMicVolume = 10;
	m_atOldAudioPortInfo[0].m_atSingleAudioPortCfg[0].bIsSimplexPoweringOpened = TRUE;
	m_atOldAudioPortInfo[0].m_atSingleAudioPortCfg[0].byAudioBNA = 0;
	m_atOldAudioPortInfo[0].m_abAudioPort[1] = FALSE;
	m_atOldAudioPortInfo[0].m_atSingleAudioPortCfg[1].byMicVolume = 10;
	m_atOldAudioPortInfo[0].m_atSingleAudioPortCfg[1].bIsSimplexPoweringOpened = TRUE;
	m_atOldAudioPortInfo[0].m_atSingleAudioPortCfg[1].byAudioBNA = 0;
	m_atOldAudioPortInfo[0].m_abAudioPort[2] = FALSE;
	m_atOldAudioPortInfo[0].m_atSingleAudioPortCfg[2].byMicVolume = 10;
	m_atOldAudioPortInfo[0].m_atSingleAudioPortCfg[2].bIsSimplexPoweringOpened = TRUE;
	m_atOldAudioPortInfo[0].m_atSingleAudioPortCfg[2].byAudioBNA = 0;
		
	m_atOldAudioPortInfo[1].m_byGroupIndex = 1;
	m_atOldAudioPortInfo[1].m_abAudioPort[0] = TRUE;
	m_atOldAudioPortInfo[1].m_atSingleAudioPortCfg[0].byMicVolume = 10;
	m_atOldAudioPortInfo[1].m_atSingleAudioPortCfg[0].bIsSimplexPoweringOpened = TRUE;
	m_atOldAudioPortInfo[1].m_atSingleAudioPortCfg[0].byAudioBNA = 0;
	m_atOldAudioPortInfo[1].m_abAudioPort[1] = FALSE;
	m_atOldAudioPortInfo[1].m_atSingleAudioPortCfg[1].byMicVolume = 10;
	m_atOldAudioPortInfo[1].m_atSingleAudioPortCfg[1].bIsSimplexPoweringOpened = TRUE;
	m_atOldAudioPortInfo[1].m_atSingleAudioPortCfg[1].byAudioBNA = 0;
	m_atOldAudioPortInfo[1].m_abAudioPort[2] = FALSE;
	m_atOldAudioPortInfo[1].m_atSingleAudioPortCfg[2].byMicVolume = 10;
	m_atOldAudioPortInfo[1].m_atSingleAudioPortCfg[2].bIsSimplexPoweringOpened = TRUE;
	m_atOldAudioPortInfo[1].m_atSingleAudioPortCfg[2].byAudioBNA = 0;
			
	m_atOldAudioPortInfo[2].m_byGroupIndex = 2;
	m_atOldAudioPortInfo[2].m_abAudioPort[0] = TRUE;
	m_atOldAudioPortInfo[2].m_atSingleAudioPortCfg[0].byMicVolume = 10;
	m_atOldAudioPortInfo[2].m_atSingleAudioPortCfg[0].bIsSimplexPoweringOpened = TRUE;
	m_atOldAudioPortInfo[2].m_atSingleAudioPortCfg[0].byAudioBNA = 0;
	m_atOldAudioPortInfo[2].m_abAudioPort[1] = FALSE;
	m_atOldAudioPortInfo[2].m_atSingleAudioPortCfg[1].byMicVolume = 10;
	m_atOldAudioPortInfo[2].m_atSingleAudioPortCfg[1].bIsSimplexPoweringOpened = TRUE;
	m_atOldAudioPortInfo[2].m_atSingleAudioPortCfg[1].byAudioBNA = 0;
	m_atOldAudioPortInfo[2].m_abAudioPort[2] = FALSE;
	m_atOldAudioPortInfo[2].m_atSingleAudioPortCfg[2].byMicVolume = 10;
	m_atOldAudioPortInfo[2].m_atSingleAudioPortCfg[2].bIsSimplexPoweringOpened = TRUE;
	m_atOldAudioPortInfo[2].m_atSingleAudioPortCfg[2].byAudioBNA = 0;
	m_atOldAudioPortInfo[2].m_abAudioPort[3] = FALSE;
	m_atOldAudioPortInfo[2].m_atSingleAudioPortCfg[3].byMicVolume = 10;
	m_atOldAudioPortInfo[2].m_atSingleAudioPortCfg[3].bIsSimplexPoweringOpened = TRUE;
	m_atOldAudioPortInfo[2].m_atSingleAudioPortCfg[3].byAudioBNA = 0;

	m_tOldTpMic10Info.m_bAudioPort = FALSE;
	m_tOldTpMic10Info.m_emGroupIndex = em_GroupNum4;

	m_bOldNodeskTopBtn = FALSE;
}
