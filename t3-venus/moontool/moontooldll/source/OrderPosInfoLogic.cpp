// OrderPosInfoLogic.cpp: implementation of the COrderPosInfoLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OrderPosInfoLogic.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COrderPosInfoLogic::COrderPosInfoLogic()	
:m_strEdtPresetInfo("EdtPresetInfo") 
,m_bIsWaitForTra(false)
{

}

COrderPosInfoLogic::~COrderPosInfoLogic()
{

}

bool COrderPosInfoLogic::InitWnd( const IArgs & arg )
{
	CLogicBase::InitWnd( arg );	

	std::vector<CString> vecOrderPos;																//设置预置位下拉框数据
	vecOrderPos.push_back("预置位1");
	vecOrderPos.push_back("预置位2");
	vecOrderPos.push_back("预置位3");
	vecOrderPos.push_back("预置位4");
	vecOrderPos.push_back("预置位5");
	vecOrderPos.push_back("预置位6");
	vecOrderPos.push_back("预置位7");
	vecOrderPos.push_back("预置位8");
	vecOrderPos.push_back("预置位9");
	vecOrderPos.push_back("预置位10");
	vecOrderPos.push_back("预置位11");
	vecOrderPos.push_back("预置位12");
	vecOrderPos.push_back("预置位13");
	vecOrderPos.push_back("预置位14");
	vecOrderPos.push_back("预置位15");
	vecOrderPos.push_back("预置位16");

	UIFACTORYMGR_PTR->SetComboListData( "ComboboxOrderPosIndex", vecOrderPos, m_pWndTree );
	UIFACTORYMGR_PTR->SetComboText( "ComboboxOrderPosIndex", "预置位1", m_pWndTree );

	return true;
}

void COrderPosInfoLogic::RegMsg()
{
	REG_MSG_HANDLER( UI_MOONTOOL_ORDERPOS_MODIFY, COrderPosInfoLogic::OnOrderPosSelData, ORDERPOSINFOLOGICRPTR, COrderPosInfoLogic );
	REG_MSG_HANDLER( WM_MoonTool_PresetListParam_IND, COrderPosInfoLogic::OnCamPreSetListInd, ORDERPOSINFOLOGICRPTR, COrderPosInfoLogic );
	REG_MSG_HANDLER( WM_MoonTool_StatusSet, COrderPosInfoLogic::OnUpdateBtnStatus, ORDERPOSINFOLOGICRPTR, COrderPosInfoLogic );
}

void COrderPosInfoLogic::UnRegMsg()
{
	
}

void COrderPosInfoLogic::RegCBFun()
{
	REG_GOBAL_MEMBER_FUNC( "COrderPosInfoLogic::InitWnd", COrderPosInfoLogic::InitWnd, ORDERPOSINFOLOGICRPTR, COrderPosInfoLogic );
	REG_GOBAL_MEMBER_FUNC( "COrderPosInfoLogic::OnComboboxpresetIndexClick", COrderPosInfoLogic::OnComboboxpresetIndexClick, ORDERPOSINFOLOGICRPTR, COrderPosInfoLogic );
	REG_GOBAL_MEMBER_FUNC( "COrderPosInfoLogic::OnBtnPresetInfoOk", COrderPosInfoLogic::OnBtnPresetInfoOk, ORDERPOSINFOLOGICRPTR, COrderPosInfoLogic )
	REG_GOBAL_MEMBER_FUNC( "COrderPosInfoLogic::OnBtnPresetInfoCancel", COrderPosInfoLogic::OnBtnPresetInfoCancel, ORDERPOSINFOLOGICRPTR, COrderPosInfoLogic );
	REG_GOBAL_MEMBER_FUNC( "COrderPosInfoLogic::OnBtnClose", COrderPosInfoLogic::OnBtnClose, ORDERPOSINFOLOGICRPTR, COrderPosInfoLogic )		
}

void COrderPosInfoLogic::UnRegFunc()
{
	UN_REG_GOBAL_FUNC( "COrderPosInfoLogic::InitWnd" );	
}

void COrderPosInfoLogic::Clear()
{
	m_vctWndName.clear();
	m_bIsWaitForTra = false;
}

void COrderPosInfoLogic::FocusWindow(String strWindow)
{
	UIFACTORYMGR_PTR->SetFocus( strWindow, m_pWndTree );
}

bool COrderPosInfoLogic::OnComboboxpresetIndexClick( const IArgs& args )
{
	string strComboText = "";
	s32 nIndex = 0;

	UIFACTORYMGR_PTR->GetComboText( "ComboboxOrderPosIndex", strComboText, m_pWndTree );
	nIndex = GetPresetIndex(strComboText);
	
	if ( ( m_vecTPCamPreInfo.size() > 0 ) &&( m_vecTPCamPreInfo.size() < ( MAX_CAMERA_Pre_NUM+1 ) ) )
	{
		UIFACTORYMGR_PTR->SetCaption( m_strEdtPresetInfo, m_vecTPCamPreInfo[nIndex].achachDescription, m_pWndTree);
	}
	return true;	
}

bool COrderPosInfoLogic::OnBtnPresetInfoOk( const IArgs& args )
{
	String strOrderPosIndex;
	UIFACTORYMGR_PTR->GetComboText( "ComboboxOrderPosIndex", strOrderPosIndex, m_pWndTree );
	TTPCamPre tTPCamPre;
	memset(&tTPCamPre,0,sizeof(tTPCamPre));

	if ( strOrderPosIndex == "预置位1")
	{
		tTPCamPre.byPre = 0;
	}
	else if ( strOrderPosIndex == "预置位2")
	{
		tTPCamPre.byPre = 1;
	}
	else if ( strOrderPosIndex == "预置位3")
	{
		tTPCamPre.byPre = 2;
	}
	else if ( strOrderPosIndex == "预置位4")
	{
		tTPCamPre.byPre = 3;
	}
	else if ( strOrderPosIndex == "预置位5")
	{
		tTPCamPre.byPre = 4;
	}
	else if ( strOrderPosIndex == "预置位6")
	{
		tTPCamPre.byPre = 5;
	}
	else if ( strOrderPosIndex == "预置位7")
	{
		tTPCamPre.byPre = 6;
	}
	else if ( strOrderPosIndex == "预置位8")
	{
		tTPCamPre.byPre = 7;
	}
	else if ( strOrderPosIndex == "预置位9")
	{
		tTPCamPre.byPre = 8;
	}
	else if ( strOrderPosIndex == "预置位10")
	{
		tTPCamPre.byPre = 9;
	}
	else if ( strOrderPosIndex == "预置位11")
	{
		tTPCamPre.byPre = 10;
	}
	else if ( strOrderPosIndex == "预置位12")
	{
		tTPCamPre.byPre = 11;
	}
	else if ( strOrderPosIndex == "预置位13")
	{
		tTPCamPre.byPre = 12;
	}
	else if ( strOrderPosIndex == "预置位14")
	{
		tTPCamPre.byPre = 13;
	}
	else if ( strOrderPosIndex == "预置位15")
	{
		tTPCamPre.byPre = 14;
	}
	else if ( strOrderPosIndex == "预置位16")
	{
		tTPCamPre.byPre = 15;
	}
	tTPCamPre.bIsUsed = TRUE;
	String strCaption;
	UIFACTORYMGR_PTR->GetCaption( m_strEdtPresetInfo, strCaption, m_pWndTree);
	if ( !IsValidTPStr( strCaption ) )
	{   
		CString str; 
		str.Format("预置位描述中不可以包含空格及括号中的任意字符 [ %s ]",INVALID_ALIAS_FOR_SHOW);
		MSG_BOX_OK( (String)str );
		FocusWindow(m_strEdtPresetInfo);
		return false;
	}
	strcpy( tTPCamPre.achachDescription, strCaption.c_str() );

	if ( em_ORDERPOSOPT_MODIFY == m_emOPType )
	{
		u16 nRet = COMIFMGRPTR->CamPreSetModifyCmd( tTPCamPre );
	}
	else
	{
		u16 nRet = COMIFMGRPTR->CamPreSetSaveCmd( tTPCamPre );
		m_bIsWaitForTra = true;
	}

	s32 nResult = 0;
	UIFACTORYMGR_PTR->Endmodal(nResult, g_stcStrOrderPosInfoDlg );

	return true;	
}

bool COrderPosInfoLogic::OnBtnPresetInfoCancel( const IArgs& args )
{
	if ( em_ORDERPOSOPT_MODIFY == m_emOPType )
	{
		UpdatePreData( m_tCamPreSel );		
	}
	
	s32 nResult = 0;
	UIFACTORYMGR_PTR->Endmodal(nResult, g_stcStrOrderPosInfoDlg );
	return true;	
}

bool COrderPosInfoLogic::OnBtnClose( const IArgs& args )
{
	s32 nResult = 0;
	UIFACTORYMGR_PTR->Endmodal(nResult, g_stcStrOrderPosInfoDlg );
	return true;	
}

HRESULT COrderPosInfoLogic::OnOrderPosSelData( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
	{
		return S_FALSE;
	}
	
	m_emOPType = static_cast<EM_ORDERPOSOPT_TYPE>(lparam);

	if ( em_ORDERPOSOPT_MODIFY == m_emOPType )
	{
		if ( wparam != NULL )
		{
			m_tCamPreSel = *reinterpret_cast<TTPCamPre*>(wparam);
		}
		else
		{
			if (m_vecTPCamPreInfo.size() > 0 )
			{
				m_tCamPreSel = m_vecTPCamPreInfo.at(0);
			}
		}
	}
	else if ( m_emOPType == em_ORDERPOSOPT_SAVE )
	{
		if (m_vecTPCamPreInfo.size() > 0 )
		{
			m_tCamPreSel = m_vecTPCamPreInfo.at(0);
		}
		else
		{
			return S_FALSE;
		}
	}

	UpdatePreData( m_tCamPreSel );

	if ( em_ORDERPOSOPT_MODIFY == m_emOPType && wparam != NULL )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmEnable",m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmNormal",m_pWndTree );
	}

	if ( ( m_emOPType == em_ORDERPOSOPT_SAVE )&& ( m_bIsWaitForTra == true ))
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmBegin",m_pWndTree );
	}

	s32 nDodalResult = UIFACTORYMGR_PTR->Domodal( g_stcStrOrderPosInfoDlg );
	return NO_ERROR;	
}

void COrderPosInfoLogic::UpdatePreData( TTPCamPre tTPCamPre )
{
	String strOrderPosIndex;

	if ( tTPCamPre.byPre == 0 )
	{
		strOrderPosIndex = "预置位1";
	}
	else if ( tTPCamPre.byPre == 1 )
	{
		strOrderPosIndex = "预置位2";
	}
	else if ( tTPCamPre.byPre == 2)
	{
		strOrderPosIndex = "预置位3";
	}
	else if ( tTPCamPre.byPre == 3 )
	{
		strOrderPosIndex = "预置位4";
	}
	else if ( tTPCamPre.byPre == 4 )
	{
		strOrderPosIndex = "预置位5";
	}
	else if ( tTPCamPre.byPre == 5 )
	{
		strOrderPosIndex = "预置位6";
	}
	else if ( tTPCamPre.byPre == 6 )
	{
		strOrderPosIndex = "预置位7";
	}
	else if ( tTPCamPre.byPre == 7 )
	{
		strOrderPosIndex = "预置位8";
	}
	else if ( tTPCamPre.byPre == 8 )
	{
		strOrderPosIndex = "预置位9";
	}
	else if ( tTPCamPre.byPre == 9 )
	{
		strOrderPosIndex = "预置位10";
	}
	else if ( tTPCamPre.byPre == 10 )
	{
		strOrderPosIndex = "预置位11";
	}
	else if ( tTPCamPre.byPre == 11 )
	{
		strOrderPosIndex = "预置位12";
	}
	else if ( tTPCamPre.byPre == 12 )
	{
		strOrderPosIndex = "预置位13";
	}
	else if ( tTPCamPre.byPre == 13 )
	{
		strOrderPosIndex = "预置位14";
	}
	else if ( tTPCamPre.byPre == 14 )
	{
		strOrderPosIndex = "预置位15";
	}
	else if ( tTPCamPre.byPre == 15 )
	{
		strOrderPosIndex = "预置位16";
	}

	UIFACTORYMGR_PTR->SetComboText( "ComboboxOrderPosIndex", strOrderPosIndex, m_pWndTree );
	
	UIFACTORYMGR_PTR->SetCaption( m_strEdtPresetInfo, tTPCamPre.achachDescription, m_pWndTree);
}


HRESULT COrderPosInfoLogic::OnCamPreSetListInd( WPARAM wparam, LPARAM lparam )
{
	if ( m_pWndTree == NULL )
    {
        return NO_ERROR;
    }
	
	std::vector<TTPCamPreOption> vectTPCamPre = *reinterpret_cast<std::vector<TTPCamPreOption>*>(wparam);

	if ( vectTPCamPre.size() > 0 )
	{
		m_vecTPCamPreInfo.clear();
	}
	for ( vector<TTPCamPreOption>::size_type nIndex = 0; nIndex < vectTPCamPre.size() ; nIndex ++ )
	{
		m_vecTPCamPreInfo.push_back(vectTPCamPre.at(nIndex).m_tCamPre);
	}

	return NO_ERROR;	
}

s32 COrderPosInfoLogic::GetPresetIndex( string strPresetInfo )
{
	s32 nIndex = 0;

	if ( strcmp( strPresetInfo.c_str(),"预置位1") == 0 )
	{
		nIndex = 0;
	}
	else if ( strcmp( strPresetInfo.c_str(),"预置位2") == 0 )
	{
		nIndex = 1;
	}
	else if ( strcmp( strPresetInfo.c_str(),"预置位3") == 0 )
	{
		nIndex = 2;
	}
	else if ( strcmp( strPresetInfo.c_str(),"预置位4") == 0 )
	{
		nIndex = 3;
	}
	else if (strcmp( strPresetInfo.c_str(),"预置位5") == 0 )
	{
		nIndex = 4;
	}
	else if ( strcmp( strPresetInfo.c_str(),"预置位6") == 0 )
	{
		nIndex = 5;
	}
	else if ( strcmp( strPresetInfo.c_str(),"预置位7") == 0 )
	{
		nIndex = 6;
	}
	else if ( strcmp( strPresetInfo.c_str(),"预置位8") == 0 )
	{
		nIndex = 7;
	}
	else if ( strcmp( strPresetInfo.c_str(),"预置位9") == 0 )
	{
		nIndex = 8;
	}
	else if ( strcmp( strPresetInfo.c_str(),"预置位10") == 0 )
	{
		nIndex = 9;
	}
	else if ( strcmp( strPresetInfo.c_str(),"预置位11") == 0 )
	{
		nIndex = 10;
	}
	else if ( strcmp( strPresetInfo.c_str(),"预置位12") == 0  )
	{
		nIndex  = 11;
	}
	else if ( strcmp( strPresetInfo.c_str(),"预置位13") == 0 )
	{
		nIndex = 12;
	}
	else if ( strcmp( strPresetInfo.c_str(),"预置位14") == 0 )
	{
		nIndex = 13;
	}
	else if ( strcmp( strPresetInfo.c_str(),"预置位15") == 0 )
	{
		nIndex = 14;
	}
	else if ( strcmp(strPresetInfo.c_str(),"预置位16") == 0 )
	{
		nIndex = 15;
	}
	else
	{
		nIndex = 0;
	}

	return nIndex ;
}

HRESULT COrderPosInfoLogic::OnUpdateBtnStatus( WPARAM wparam, LPARAM lparam )
{	
	m_bIsWaitForTra = false;

	//解决快速反复操作的情况下，确定按钮灰显不可用的问题
// 	if ( UIFACTORYMGR_PTR->IsVisible(g_stcStrOrderPosInfoDlg) == TRUE )
// 	{
// 		UIFACTORYMGR_PTR->LoadScheme( "SchmEnd",m_pWndTree );
// 	}
	
	UIFACTORYMGR_PTR->LoadScheme( "SchmEnd",m_pWndTree );
	return NO_ERROR;	
}