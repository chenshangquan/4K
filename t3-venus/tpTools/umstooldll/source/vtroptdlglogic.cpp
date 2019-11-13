// vtroptdlglogic.cpp: implementation of the CVTROptDlgLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "vtroptdlglogic.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVTROptDlgLogic::CVTROptDlgLogic()
: m_strEdtVTRName( _T("EdtVTRName") )
, m_strEdtVTRNo( _T("EdtVTRNo") )
, m_strIPCtrlVTRIP( _T("IPCtrlVTRIP") )
{
}

CVTROptDlgLogic::~CVTROptDlgLogic()
{
	UnRegMsg();
	UnRegFunc();
}

void CVTROptDlgLogic::RegMsg()
{    
	REG_MSG_HANDLER( UI_UMSTOOL_MSG_VTRSELDATA_Click, CVTROptDlgLogic::OnSelData, VTROPTLOGICRPTR, CVTROptDlgLogic );
}

void CVTROptDlgLogic::UnRegMsg()
{
}

bool CVTROptDlgLogic::RegCBFun()
{   	 
	REG_GOBAL_MEMBER_FUNC( "CVTROptDlgLogic::InitWnd", CVTROptDlgLogic::InitWnd, VTROPTLOGICRPTR, CVTROptDlgLogic);
	REG_GOBAL_MEMBER_FUNC( "CVTROptDlgLogic::OnBtnOk", CVTROptDlgLogic::OnBtnOk, VTROPTLOGICRPTR, CVTROptDlgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CVTROptDlgLogic::OnBtnCancel", CVTROptDlgLogic::OnBtnCancel, VTROPTLOGICRPTR, CVTROptDlgLogic ); 

	return true;
}

bool CVTROptDlgLogic::UnRegFunc()
{
	return true;
}

bool CVTROptDlgLogic::InitWnd(  const IArgs & arg )
{   
	CWndLogicBase::InitWnd( arg );

    return true;
}

void CVTROptDlgLogic::Clear()
{
	s32 nResult = 0;
	UIFACTORYMGR_PTR->Endmodal(nResult, g_stcStrVTROptDlg );

	ClearAllCtrl();
}

bool CVTROptDlgLogic::OnBtnOk( const IArgs & arg )
{
	TVcrCfg tVTRCfg;
	bool bGet = GetAllCtrl(tVTRCfg);
	if ( bGet == true )
	{
		if( em_NETMNGOPT_MODIFY == m_emNMType )	//修改
		{
			u16 nRet = COMMONMGRIFPTR->VTRModifyReq( m_tVTRCfgOld , tVTRCfg );
			if ( nRet != NO_ERROR )
			{
				MESSAGEWND( "修改录像机请求发送失败" );
			}
		}
		else	//添加
		{
			u16 nRet = COMMONMGRIFPTR->VTRAddReq( tVTRCfg );
			if ( nRet != NO_ERROR )
			{
				MESSAGEWND( "添加录像机请求发送失败" );
			}
		}

		s32 nResult = 0;
		UIFACTORYMGR_PTR->Endmodal(nResult, g_stcStrVTROptDlg );
	}
	

	return true;
}

bool CVTROptDlgLogic::OnBtnCancel( const IArgs & arg )
{
 	s32 nResult = 0;
 	UIFACTORYMGR_PTR->Endmodal(nResult, g_stcStrVTROptDlg );

	return true;
}


HRESULT CVTROptDlgLogic::OnSelData( WPARAM wparam, LPARAM lparam)
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	m_tVTRCfgOld = *reinterpret_cast<TVcrCfg*>(wparam);
	m_emNMType = static_cast<EM_NETMNGOPT_TYPE>(lparam);

	if ( em_NETMNGOPT_MODIFY == m_emNMType )    //修改
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchVTRModify", m_pWndTree );

		SetAllCtrl(m_tVTRCfgOld);
	}
	else	//添加
	{
		ClearAllCtrl();

		UIFACTORYMGR_PTR->LoadScheme( "SchVTRAdd", m_pWndTree );
	}
	
	//UIFACTORYMGR_PTR->SetFocus( m_strEdtVTRName, m_pWndTree );
	
	return S_OK;
}

void CVTROptDlgLogic::ClearAllCtrl()
{
	if ( m_pWndTree == NULL )
	{
		return;
	}

	UIFACTORYMGR_PTR->SetCaption( m_strEdtVTRName, _T(""), m_pWndTree );
	UIFACTORYMGR_PTR->SetCaption( m_strEdtVTRNo, _T(""), m_pWndTree );
	UIFACTORYMGR_PTR->SetCaption( m_strIPCtrlVTRIP, _T(""), m_pWndTree );
}

void CVTROptDlgLogic::SetAllCtrl( TVcrCfg &tVTRCfg )
{
	if ( m_pWndTree == NULL )
	{
		return;
	}

	String strCaption;

	strCaption = tVTRCfg.m_achName;
	UIFACTORYMGR_PTR->SetCaption( m_strEdtVTRName, strCaption, m_pWndTree );
	
	char arrSTRNo[3] = {0};
	_itot( tVTRCfg.m_byEqpID, arrSTRNo, 10 );
	strCaption = arrSTRNo;
	UIFACTORYMGR_PTR->SetCaption( m_strEdtVTRNo, strCaption, m_pWndTree );
	
	strCaption = CUmstoolCommon::GetIpStr( tVTRCfg.m_dwIP );
	UIFACTORYMGR_PTR->SetCaption( m_strIPCtrlVTRIP, strCaption, m_pWndTree );
}

bool CVTROptDlgLogic::GetAllCtrl( TVcrCfg &tVTRCfg )
{
	if ( m_pWndTree == NULL )
	{
		return false;
	}	

	Value_WindowCaption valCaption;
	UIFACTORYMGR_PTR->GetPropertyValue( valCaption, m_strEdtVTRName, m_pWndTree );
	if ( valCaption.strCaption.empty() )
	{
		MSG_BOX_OK( "录像机名称不能为空" );
		UIFACTORYMGR_PTR->SetFocus( m_strEdtVTRName, m_pWndTree );
		return false;
	}
	if ( valCaption.strCaption.length() > UMSTOOL_MAX_VTR_NAME_LENTH )
	{
		CString str;
		str.Format( _T("录像机名称超过最大长度：%d"), UMSTOOL_MAX_VTR_NAME_LENTH );
		MSG_BOX_OK( (LPCTSTR)str );
		UIFACTORYMGR_PTR->SetFocus( m_strEdtVTRName, m_pWndTree );
		return false;
	}
	strncpy( tVTRCfg.m_achName, valCaption.strCaption.c_str(), UMSTOOL_MAX_VTR_NAME_LENTH+1 );
	

	UIFACTORYMGR_PTR->GetPropertyValue( valCaption, m_strEdtVTRNo, m_pWndTree );
	if ( valCaption.strCaption.empty() )
	{
		MSG_BOX_OK( "录像机编号不能为空" );
		UIFACTORYMGR_PTR->SetFocus( m_strEdtVTRNo, m_pWndTree );
		return false;
	}
	int nNo = 0;
	nNo = _ttoi( valCaption.strCaption.c_str() );
	if ( nNo < 17 || nNo > 32 )
	{
		MSG_BOX_OK( "录像机编号范围17-32，不在范围之内" );
		UIFACTORYMGR_PTR->SetFocus( m_strEdtVTRNo, m_pWndTree );
		return false;
	}

	vector<TVcrCfg> vecTVcrCfg;
	DATAMGRPTR->GetUmsVTRData( vecTVcrCfg );
	vector<TVcrCfg>::iterator it = vecTVcrCfg.begin();
	for ( ; it != vecTVcrCfg.end(); it++ )
	{
		if ( it->m_byEqpID == m_tVTRCfgOld.m_byEqpID )
		{
			continue;
		}
		if ( it->m_byEqpID == nNo )
		{
			MSG_BOX_OK( "录像机编号已被占用" );
			UIFACTORYMGR_PTR->SetFocus( m_strEdtVTRNo, m_pWndTree );
			return false;
		}
	}
	tVTRCfg.m_byEqpID = nNo;
	
	UIFACTORYMGR_PTR->GetPropertyValue( valCaption, m_strIPCtrlVTRIP, m_pWndTree );
	if ( valCaption.strCaption.empty() )
	{
		MSG_BOX_OK( "录像机地址不能为空" );
		UIFACTORYMGR_PTR->SetFocus( m_strIPCtrlVTRIP, m_pWndTree );
		return false;
	}
	
	u32_ip dwIp = inet_addr(valCaption.strCaption.c_str());
	if ( !CCallAddr::IsValidIpV4( dwIp ) ) 
	{
		MSG_BOX_OK( "录像机地址无效" );
		UIFACTORYMGR_PTR->SetFocus( m_strIPCtrlVTRIP, m_pWndTree );
		return false;
    }
	tVTRCfg.m_dwIP = dwIp;
	
	return true;
}