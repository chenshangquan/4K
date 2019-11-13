// vtrcfglogic.cpp: implementation of the CVTRCfgLogic class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h" 
#include "vtrcfglogic.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CVTRCfgLogic::CVTRCfgLogic()
: m_strListVTR( "VTRLstDlg/ListVTR" )
, m_strBtnModify( "BtnModify" )
, m_strBtnAdd( "BtnAdd" )
, m_strBtnDel( "BtnDelete" )
{
}

CVTRCfgLogic::~CVTRCfgLogic()
{
	UnRegMsg();
	UnRegFunc();
}

void CVTRCfgLogic::RegMsg()
{
 	REG_MSG_HANDLER( UI_UMSTOOL_ADD_VTR_RSP, CVTRCfgLogic::OnAddVTRRsp, VTRCFGLOGICRPTR, CVTRCfgLogic );
 	REG_MSG_HANDLER( UI_UMSTOOL_VTR_NTY, CVTRCfgLogic::OnVTRNty, VTRCFGLOGICRPTR, CVTRCfgLogic );
 	REG_MSG_HANDLER( UI_UMSTOOL_MODIFY_VTR_RSP, CVTRCfgLogic::OnModifyVTRRsp, VTRCFGLOGICRPTR, CVTRCfgLogic );
 	REG_MSG_HANDLER( UI_UMSTOOL_DEL_VTR_RSP, CVTRCfgLogic::OnDelVTRRsp, VTRCFGLOGICRPTR, CVTRCfgLogic );
}

void CVTRCfgLogic::UnRegMsg()
{
}

bool CVTRCfgLogic::RegCBFun()
{
	REG_GOBAL_MEMBER_FUNC( "CVTRCfgLogic::InitWnd", CVTRCfgLogic::InitWnd, VTRCFGLOGICRPTR, CVTRCfgLogic );
 	REG_GOBAL_MEMBER_FUNC( "CVTRCfgLogic::OnClickBtnAdd", CVTRCfgLogic::OnClickBtnAdd, VTRCFGLOGICRPTR, CVTRCfgLogic );
 	REG_GOBAL_MEMBER_FUNC( "CVTRCfgLogic::OnClickBtnModify", CVTRCfgLogic::OnClickBtnModify, VTRCFGLOGICRPTR, CVTRCfgLogic );
 	REG_GOBAL_MEMBER_FUNC( "CVTRCfgLogic::OnClickBtnDelete", CVTRCfgLogic::OnClickBtnDelete, VTRCFGLOGICRPTR, CVTRCfgLogic );
 	REG_LIST_CALLFUNC( "CVTRCfgLogic::OnClickVTRLst", CVTRCfgLogic::OnClickVTRLst, VTRCFGLOGICRPTR, CVTRCfgLogic );
 	REG_GOBAL_MEMBER_FUNC( "CVTRCfgLogic::OnClickVTRLstBlack", CVTRCfgLogic::OnClickVTRLstBlack, VTRCFGLOGICRPTR, CVTRCfgLogic );
	
	return true;
}

bool CVTRCfgLogic::UnRegFunc()
{
	UN_REG_GOBAL_FUNC( "CVTRCfgLogic::InitWnd" );
	return true;
}

bool CVTRCfgLogic::InitWnd(  const IArgs & arg )
{
	CWndLogicBase::InitWnd( arg );

	return true;
}

void CVTRCfgLogic::Clear()
{
 	ResetAllData();
 	ResetAllCtrl();
}

bool CVTRCfgLogic::OnClickBtnAdd( const IArgs& args )
{
	CMsgDispatch::SendMessage( UI_UMSTOOL_MSG_VTRSELDATA_Click, (WPARAM)&m_tVTRCfgSel, (LPARAM)em_NETMNGOPT_ADD );
	s32 nDodalResult = UIFACTORYMGR_PTR->Domodal( g_stcStrVTROptDlg );

	return true;
}

bool CVTRCfgLogic::OnClickBtnModify( const IArgs& args )
{
	CMsgDispatch::SendMessage( UI_UMSTOOL_MSG_VTRSELDATA_Click, (WPARAM)&m_tVTRCfgSel, (LPARAM)em_NETMNGOPT_MODIFY );
	s32 nDodalResult = UIFACTORYMGR_PTR->Domodal( g_stcStrVTROptDlg );

	return true;
}

bool CVTRCfgLogic::OnClickBtnDelete( const IArgs& args )
{
	MSGBOX_RET nResult = MSGBOX_OK;
	MSG_BOX( nResult, "是否要删除该录像机？");
	if (nResult == MSGBOX_OK)
	{
		u16 nRet = COMMONMGRIFPTR->VTRDeleteReq(m_tVTRCfgSel);
		if ( nRet != NO_ERROR )
		{
			MESSAGEWND( "删除录像机请求发送失败" );
		}
	}

	return true;
}

HRESULT CVTRCfgLogic::OnAddVTRRsp( WPARAM wparam, LPARAM lparam )
{
	if (m_pWndTree == NULL)
	{
		return S_FALSE;
	}

	EmModifyVcrRet emRes = static_cast<EmModifyVcrRet>(wparam);

	switch( emRes )
	{
	case em_vcr_modify_success:
		{
			vector<TVcrCfg> vecTVcrCfg;
			DATAMGRPTR->GetUmsVTRData( vecTVcrCfg );
			Value_ItemVTR VTRList( &vecTVcrCfg );
			UIFACTORYMGR_PTR->SetPropertyValue( VTRList, m_strListVTR, m_pWndTree);

			memset( &m_tVTRCfgSel, 0, sizeof(TVcrCfg) );
			UpdateBtnState();

			break;
		}
	case em_vcr_full:
		{
			MESSAGEWND( "添加失败，服务器已满" );
			break;
		}
	case em_vcr_invalid:
		{
			MESSAGEWND( "添加失败，数据无效" );
			break;
		}
	case em_vcr_no_exist:
		{
			MESSAGEWND( "添加失败，不存在摄像机" );
			break;
		}
	default:
		break;
	}

	return S_OK;
}

HRESULT CVTRCfgLogic::OnVTRNty( WPARAM wparam, LPARAM lparam )
{
	if (m_pWndTree == NULL)
	{
		return S_FALSE;
	}

	vector<TVcrCfg> vecTVcrCfg;
	DATAMGRPTR->GetUmsVTRData( vecTVcrCfg );

	Value_ItemVTR VTRList( &vecTVcrCfg );
	UIFACTORYMGR_PTR->SetPropertyValue( VTRList, m_strListVTR, m_pWndTree);

	UpdateBtnState();

	return S_OK;
}

HRESULT CVTRCfgLogic::OnModifyVTRRsp( WPARAM wparam, LPARAM lparam )
{
	if (m_pWndTree == NULL)
	{
		return S_FALSE;
	}

	EmModifyVcrRet emRes = static_cast<EmModifyVcrRet>(wparam);
	TVcrCfg tVcrCfg = *((TVcrCfg*)lparam);
	
	switch( emRes )
	{
	case em_vcr_modify_success:
		{
			vector<TVcrCfg> vecTVcrCfg;
			DATAMGRPTR->GetUmsVTRData( vecTVcrCfg );
			
			Value_ItemVTR VTRList( &vecTVcrCfg );
			UIFACTORYMGR_PTR->SetPropertyValue( VTRList, m_strListVTR, m_pWndTree);

			m_tVTRCfgSel = tVcrCfg;

			break;
		}
	case em_vcr_full:
		{
			MESSAGEWND( "修改失败，服务器已满" );
			break;
		}
	case em_vcr_invalid:
		{
			MESSAGEWND( "修改失败，数据无效" );
			break;
		}
	case em_vcr_no_exist:
		{
			MESSAGEWND( "修改失败，不存在摄像机" );
			break;
		}
	default:
		break;
	}

	return S_OK;
}

HRESULT CVTRCfgLogic::OnDelVTRRsp( WPARAM wparam, LPARAM lparam )
{
	if (m_pWndTree == NULL)
	{
		return S_FALSE;
	}
	
	EmModifyVcrRet emRes = static_cast<EmModifyVcrRet>(wparam);
	
	switch( emRes )
	{
	case em_vcr_modify_success:
		{
			vector<TVcrCfg> vecTVcrCfg;
			DATAMGRPTR->GetUmsVTRData( vecTVcrCfg );
			
			Value_ItemVTR VTRList( &vecTVcrCfg );
			UIFACTORYMGR_PTR->SetPropertyValue( VTRList, m_strListVTR, m_pWndTree);

			memset( &m_tVTRCfgSel, 0, sizeof(TVcrCfg) );
			UpdateBtnState();

			UIFACTORYMGR_PTR->LoadScheme( "SchmVTRListDefault", m_pWndTree );

			break;
		}
	case em_vcr_full:
		{
			MESSAGEWND( "删除失败，服务器已满" );
			break;
		}
	case em_vcr_invalid:
		{
			MESSAGEWND( "删除失败，数据无效" );
			break;
		}
	case em_vcr_no_exist:
		{
			MESSAGEWND( "删除失败，不存在摄像机" );
			break;
		}
	default:
		break;
	}
	
	return S_OK;
}

bool CVTRCfgLogic::OnClickVTRLst( const IArgs & arg )
{
	if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast<const Args_ClickItemInfo*>(&arg) )
    {
		const IData *pIData = pClickInfo->m_pClickList->GetItemData()->GetUserData();
		if ( const Data_VTR * pDataTemp = dynamic_cast< const Data_VTR*>(pIData) )
		{
			m_tVTRCfgSel = pDataTemp->m_tVcrCfg;

			UpdateBtnState();
		}
	}

	return true;
}

bool CVTRCfgLogic::OnClickVTRLstBlack( const IArgs& args )
{
	if (m_pWndTree == NULL)
	{
		return S_FALSE;
	}

	memset( &m_tVTRCfgSel, 0, sizeof(TVcrCfg) );
	UpdateBtnState();

	return true;
}

void CVTRCfgLogic::ResetAllCtrl()
{
	if (m_pWndTree == NULL)
	{
		return;
	}

	vector<TVcrCfg> vecTVcrCfg;
	Value_ItemVTR VTRList( &vecTVcrCfg );
	UIFACTORYMGR_PTR->SetPropertyValue( VTRList, m_strListVTR, m_pWndTree);


	UIFACTORYMGR_PTR->LoadScheme( "SchmVTRCtrlReset", m_pWndTree );
}

void CVTRCfgLogic::ResetAllData()
{
	memset( &m_tVTRCfgSel, 0, sizeof(TVcrCfg) );
}

void CVTRCfgLogic::UpdateBtnState()
{
	if (m_pWndTree == NULL)
	{
		return;
	}

	vector<TVcrCfg> vecTVcrCfg;
	DATAMGRPTR->GetUmsVTRData( vecTVcrCfg );

	int nNum = vecTVcrCfg.size();
	if ( nNum == TP_MAX_VCR )
	{
		UIFACTORYMGR_PTR->EnableWindow( m_strBtnAdd, false, m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->EnableWindow( m_strBtnAdd, true, m_pWndTree );
	}

	int nRes = strncmp( m_tVTRCfgSel.m_achName, "", MAX_VTR_NAME_LENGTH );
	if ( nRes == 0 )
	{
		UIFACTORYMGR_PTR->EnableWindow( m_strBtnModify, false, m_pWndTree );
		UIFACTORYMGR_PTR->EnableWindow( m_strBtnDel, false, m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->EnableWindow( m_strBtnModify, true, m_pWndTree );
		UIFACTORYMGR_PTR->EnableWindow( m_strBtnDel, true, m_pWndTree );
	}
}