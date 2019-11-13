// netmngcfglogic.cpp: implementation of the CNetMngCfgLogic class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h" 
#include "netmngcfglogic.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CNetMngCfgLogic::CNetMngCfgLogic()
: m_strListNetMng( "NetMngLstDlg/ListNetMng" )
, m_strBtnModify( "BtnModify" )
, m_strBtnAdd( "BtnAdd" )
, m_strBtnDel( "BtnDelete" )
{
}

CNetMngCfgLogic::~CNetMngCfgLogic()
{
	UnRegMsg();
	UnRegFunc();
}

void CNetMngCfgLogic::RegMsg()
{
	REG_MSG_HANDLER( UI_UMSTOOL_ADD_NETMNG_RSP, CNetMngCfgLogic::OnAddNetMngRsp, NETMNGCFGLOGICRPTR, CNetMngCfgLogic );
	REG_MSG_HANDLER( UI_UMSTOOL_NETMNG_NTY, CNetMngCfgLogic::OnNetMngNty, NETMNGCFGLOGICRPTR, CNetMngCfgLogic );
	REG_MSG_HANDLER( UI_UMSTOOL_MODIFY_NETMNG_RSP, CNetMngCfgLogic::OnModifyNetMngRsp, NETMNGCFGLOGICRPTR, CNetMngCfgLogic );
	REG_MSG_HANDLER( UI_UMSTOOL_DEL_NETMNG_RSP, CNetMngCfgLogic::OnDelNetMngRsp, NETMNGCFGLOGICRPTR, CNetMngCfgLogic );
}

void CNetMngCfgLogic::UnRegMsg()
{
}

bool CNetMngCfgLogic::RegCBFun()
{
	REG_GOBAL_MEMBER_FUNC( "CNetMngCfgLogic::InitWnd", CNetMngCfgLogic::InitWnd, NETMNGCFGLOGICRPTR, CNetMngCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CNetMngCfgLogic::OnClickBtnAdd", CNetMngCfgLogic::OnClickBtnAdd, NETMNGCFGLOGICRPTR, CNetMngCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CNetMngCfgLogic::OnClickBtnModify", CNetMngCfgLogic::OnClickBtnModify, NETMNGCFGLOGICRPTR, CNetMngCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CNetMngCfgLogic::OnClickBtnDelete", CNetMngCfgLogic::OnClickBtnDelete, NETMNGCFGLOGICRPTR, CNetMngCfgLogic );
	REG_LIST_CALLFUNC( "CNetMngCfgLogic::OnClickNetMngLst", CNetMngCfgLogic::OnClickNetMngLst, NETMNGCFGLOGICRPTR, CNetMngCfgLogic );
	REG_GOBAL_MEMBER_FUNC( "CNetMngCfgLogic::OnClickNetMngLstBlack", CNetMngCfgLogic::OnClickNetMngLstBlack, NETMNGCFGLOGICRPTR, CNetMngCfgLogic );
	
	return true;
}

bool CNetMngCfgLogic::UnRegFunc()
{
	UN_REG_GOBAL_FUNC( "CNetMngCfgLogic::InitWnd" );
	return true;
}

bool CNetMngCfgLogic::InitWnd(  const IArgs & arg )
{
	CWndLogicBase::InitWnd( arg );

	return true;
}

void CNetMngCfgLogic::Clear()
{
 	ResetAllData();
 	ResetAllCtrl();
}

bool CNetMngCfgLogic::OnClickBtnAdd( const IArgs& args )
{
	u16 wNMServerNo = 0;
	vector<TTPNMServerCfg> vecTTPNMServerCfg;
	DATAMGRPTR->GetUmsNetMngData( vecTTPNMServerCfg );

	int n = vecTTPNMServerCfg.size();
	switch( n )
	{
	case 0:
		{
			wNMServerNo = MIN_NMSERVER_NO;
			break;
		}
	case 1:
		{
			if ( vecTTPNMServerCfg[0].wNMServerNO == MAX_NMSERVER_NO )
			{
				wNMServerNo = MIN_NMSERVER_NO;
			}
			else
			{
				wNMServerNo = MAX_NMSERVER_NO;
			}
			break;
		}
	case TP_MAX_NMSERVER:
		{
			return true;
		}
	default:
		break;
	}

	CMsgDispatch::SendMessage( UI_UMSTOOL_MSG_NETMNGSELDATA_Click, (WPARAM)wNMServerNo, (LPARAM)em_NETMNGOPT_ADD );
	s32 nDodalResult = UIFACTORYMGR_PTR->Domodal( g_stcStrNetMngOptDlg );

	return true;
}

bool CNetMngCfgLogic::OnClickBtnModify( const IArgs& args )
{
	CMsgDispatch::SendMessage( UI_UMSTOOL_MSG_NETMNGSELDATA_Click, (WPARAM)&m_tTPNMServerCfgSel, (LPARAM)em_NETMNGOPT_MODIFY );
	s32 nDodalResult = UIFACTORYMGR_PTR->Domodal( g_stcStrNetMngOptDlg );

	return true;
}

bool CNetMngCfgLogic::OnClickBtnDelete( const IArgs& args )
{
	MSGBOX_RET nResult = MSGBOX_OK;
	MSG_BOX( nResult, "是否要删除该网管服务器？");
	if (nResult == MSGBOX_OK)
	{
		u16 nRet = COMMONMGRIFPTR->NetMngDeleteReq(m_tTPNMServerCfgSel);
		if ( nRet != NO_ERROR )
		{
			MESSAGEWND( "删除网管请求发送失败" );
		}
	}

	return true;
}

HRESULT CNetMngCfgLogic::OnAddNetMngRsp( WPARAM wparam, LPARAM lparam )
{
	if (m_pWndTree == NULL)
	{
		return S_FALSE;
	}

	EmModifyNMServerRet emRes = static_cast<EmModifyNMServerRet>(wparam);

	switch( emRes )
	{
	case em_nmserver_modify_success:
		{
			vector<TTPNMServerCfg> vecTTPNMServerCfg;
			DATAMGRPTR->GetUmsNetMngData( vecTTPNMServerCfg );
			Value_ItemNetMng NetMngList( &vecTTPNMServerCfg );
			UIFACTORYMGR_PTR->SetPropertyValue( NetMngList, m_strListNetMng, m_pWndTree);

			memset( &m_tTPNMServerCfgSel, 0, sizeof(TTPNMServerCfg) );
			UpdateBtnState();

			break;
		}
	case em_nmserver_resource_full:
		{
			MESSAGEWND( "添加失败，服务器已满" );
			break;
		}
	case em_nmserver_invalid_handle:
		{
			MESSAGEWND( "添加失败，数据无效" );
			break;
		}
	default:
		break;
	}

	return S_OK;
}

HRESULT CNetMngCfgLogic::OnNetMngNty( WPARAM wparam, LPARAM lparam )
{
	if (m_pWndTree == NULL)
	{
		return S_FALSE;
	}

	vector<TTPNMServerCfg> vecTTPNMServerCfg;
	DATAMGRPTR->GetUmsNetMngData( vecTTPNMServerCfg );

	Value_ItemNetMng NetMngList( &vecTTPNMServerCfg );
	UIFACTORYMGR_PTR->SetPropertyValue( NetMngList, m_strListNetMng, m_pWndTree);

	UpdateBtnState();

	return S_OK;
}

HRESULT CNetMngCfgLogic::OnModifyNetMngRsp( WPARAM wparam, LPARAM lparam )
{
	if (m_pWndTree == NULL)
	{
		return S_FALSE;
	}

	EmModifyNMServerRet emRes = static_cast<EmModifyNMServerRet>(wparam);
	
	switch( emRes )
	{
	case em_nmserver_modify_success:
		{
			vector<TTPNMServerCfg> vecTTPNMServerCfg;
			DATAMGRPTR->GetUmsNetMngData( vecTTPNMServerCfg );
			
			Value_ItemNetMng NetMngList( &vecTTPNMServerCfg );
			UIFACTORYMGR_PTR->SetPropertyValue( NetMngList, m_strListNetMng, m_pWndTree);

			vector<TTPNMServerCfg>::iterator it;
			u8 byIndex = 0;
			for ( it = vecTTPNMServerCfg.begin(); it != vecTTPNMServerCfg.end(); )
			{
				if ( m_tTPNMServerCfgSel.wNMServerNO == it->wNMServerNO )
				{
					m_tTPNMServerCfgSel = vecTTPNMServerCfg[byIndex];
					break;
				}
				it++;
				byIndex++;
			}

			break;
		}
	case em_nmserver_resource_full:
		{
			MESSAGEWND( "修改失败，服务器已满" );
			break;
		}
	case em_nmserver_invalid_handle:
		{
			MESSAGEWND( "修改失败，数据无效" );
			break;
		}
	default:
		break;
	}

	return S_OK;
}

HRESULT CNetMngCfgLogic::OnDelNetMngRsp( WPARAM wparam, LPARAM lparam )
{
	if (m_pWndTree == NULL)
	{
		return S_FALSE;
	}
	
	EmModifyNMServerRet emRes = static_cast<EmModifyNMServerRet>(wparam);
	
	switch( emRes )
	{
	case em_nmserver_modify_success:
		{
			vector<TTPNMServerCfg> vecTTPNMServerCfg;
			DATAMGRPTR->GetUmsNetMngData( vecTTPNMServerCfg );
			
			Value_ItemNetMng NetMngList( &vecTTPNMServerCfg );
			UIFACTORYMGR_PTR->SetPropertyValue( NetMngList, m_strListNetMng, m_pWndTree);

			memset( &m_tTPNMServerCfgSel, 0, sizeof(TTPNMServerCfg) );
			UpdateBtnState();

			UIFACTORYMGR_PTR->LoadScheme( "SchmNetMngListDefault", m_pWndTree );

			break;
		}
	case em_nmserver_resource_full:
		{
			MESSAGEWND( "删除失败，服务器已满" );
			break;
		}
	case em_nmserver_invalid_handle:
		{
			MESSAGEWND( "删除失败，数据无效" );
			break;
		}
	default:
		break;
	}
	
	return S_OK;
}

bool CNetMngCfgLogic::OnClickNetMngLst( const IArgs & arg )
{
	if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast<const Args_ClickItemInfo*>(&arg) )
    {
		const IData *pIData = pClickInfo->m_pClickList->GetItemData()->GetUserData();
		if ( const Data_NetMng * pDataTemp = dynamic_cast< const Data_NetMng*>(pIData) )
		{
			m_tTPNMServerCfgSel = pDataTemp->m_tTPNMServerCfg;
			m_tTPNMServerCfgSel.dwNMServerIP = (ntohl)(pDataTemp->m_tTPNMServerCfg.dwNMServerIP);

			UpdateBtnState();
		}
	}

	return true;
}

bool CNetMngCfgLogic::OnClickNetMngLstBlack( const IArgs& args )
{
	if (m_pWndTree == NULL)
	{
		return S_FALSE;
	}

	memset( &m_tTPNMServerCfgSel, 0, sizeof(TTPNMServerCfg) );
	UpdateBtnState();

	return true;
}

void CNetMngCfgLogic::ResetAllCtrl()
{
	if (m_pWndTree == NULL)
	{
		return;
	}

	vector<TTPNMServerCfg> vecTPNMServerCfg;
	Value_ItemNetMng NetMngList( &vecTPNMServerCfg );
	UIFACTORYMGR_PTR->SetPropertyValue( NetMngList, m_strListNetMng, m_pWndTree);


	UIFACTORYMGR_PTR->LoadScheme( "SchmNetMngCtrlReset", m_pWndTree );
}

void CNetMngCfgLogic::ResetAllData()
{
	memset( &m_tTPNMServerCfgSel, 0, sizeof(TTPNMServerCfg) );
}

void CNetMngCfgLogic::UpdateBtnState()
{
	if (m_pWndTree == NULL)
	{
		return;
	}

	vector<TTPNMServerCfg> vecTTPNMServerCfg;
	DATAMGRPTR->GetUmsNetMngData( vecTTPNMServerCfg );

	bool bChoose = false;
	if ( m_tTPNMServerCfgSel.dwNMServerIP != 0 )
	{
		bChoose = true;
	}

	if ( bChoose )
	{
		UIFACTORYMGR_PTR->EnableWindow( m_strBtnAdd, false, m_pWndTree );
	}
	else
	{
		int nNum = vecTTPNMServerCfg.size();
		if ( nNum == TP_MAX_NMSERVER )
		{
			UIFACTORYMGR_PTR->EnableWindow( m_strBtnAdd, false, m_pWndTree );
		}
		else
		{
			UIFACTORYMGR_PTR->EnableWindow( m_strBtnAdd, true, m_pWndTree );
		}
	}

	UIFACTORYMGR_PTR->EnableWindow( m_strBtnModify, bChoose, m_pWndTree );
	UIFACTORYMGR_PTR->EnableWindow( m_strBtnDel, bChoose, m_pWndTree );
}