// cfgnetmnglogic.cpp: implementation of the CCfgNetMngLogic class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h" 
#include "cfgnetmnglogic.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CCfgNetMngLogic::CCfgNetMngLogic()
: m_strListNetMng( "NetMngLstDlg/ListNetMng" )
, m_strBtnModify( "BtnModify" )
, m_strBtnAdd( "BtnAdd" )
, m_strBtnDel( "BtnDelete" )
{
}

CCfgNetMngLogic::~CCfgNetMngLogic()
{
	UnRegMsg();
	UnRegFunc();
}

void CCfgNetMngLogic::RegMsg()
{
	REG_MSG_HANDLER( UI_CNSTOOL_ADD_NETMNG_IND, CCfgNetMngLogic::OnAddNetMngRsp, CFGNETMNGLOGICRPTR, CCfgNetMngLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_NETMNG_NTY, CCfgNetMngLogic::OnNetMngNty, CFGNETMNGLOGICRPTR, CCfgNetMngLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_MODIFY_NETMNG_IND, CCfgNetMngLogic::OnModifyNetMngRsp, CFGNETMNGLOGICRPTR, CCfgNetMngLogic );
	REG_MSG_HANDLER( UI_CNSTOOL_DEL_NETMNG_IND, CCfgNetMngLogic::OnDelNetMngRsp, CFGNETMNGLOGICRPTR, CCfgNetMngLogic );
}

void CCfgNetMngLogic::UnRegMsg()
{
}

void CCfgNetMngLogic::RegCBFun()
{
	REG_GOBAL_MEMBER_FUNC( "CCfgNetMngLogic::InitWnd", CCfgNetMngLogic::InitWnd, CFGNETMNGLOGICRPTR, CCfgNetMngLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgNetMngLogic::OnClickBtnAdd", CCfgNetMngLogic::OnClickBtnAdd, CFGNETMNGLOGICRPTR, CCfgNetMngLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgNetMngLogic::OnClickBtnModify", CCfgNetMngLogic::OnClickBtnModify, CFGNETMNGLOGICRPTR, CCfgNetMngLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgNetMngLogic::OnClickBtnDelete", CCfgNetMngLogic::OnClickBtnDelete, CFGNETMNGLOGICRPTR, CCfgNetMngLogic );
	REG_LIST_CALLFUNC( "CCfgNetMngLogic::OnClickNetMngLst", CCfgNetMngLogic::OnClickNetMngLst, CFGNETMNGLOGICRPTR, CCfgNetMngLogic );
	REG_GOBAL_MEMBER_FUNC( "CCfgNetMngLogic::OnClickNetMngLstBlack", CCfgNetMngLogic::OnClickNetMngLstBlack, CFGNETMNGLOGICRPTR, CCfgNetMngLogic );
}

void CCfgNetMngLogic::UnRegFunc()
{
	UN_REG_GOBAL_FUNC( "CNetMngCfgLogic::InitWnd" );
}

bool CCfgNetMngLogic::InitWnd(  const IArgs & arg )
{
	CLogicBase::InitWnd( arg );

	return true;
}

void CCfgNetMngLogic::Clear()
{
 	ResetAllData();
 	ResetAllCtrl();
}

bool CCfgNetMngLogic::OnClickBtnAdd( const IArgs& args )
{
	u16 wNMServerNo = 0;
	vector<TTPNMServerCfg> vecTTPNMServerCfg;
	LIBDATAMGRPTR->GetNetMngData( vecTTPNMServerCfg );

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
			vector<TTPNMServerCfg>::iterator it = vecTTPNMServerCfg.begin();
			int nNo = it->wNMServerNO;
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

	CMsgDispatch::SendMessage( UI_CNSTOOL_MSG_NETMNGSELDATA_Click, (WPARAM)wNMServerNo, (LPARAM)em_NETMNGOPT_ADD );
	s32 nDodalResult = UIFACTORYMGR_PTR->Domodal( g_stcStrNetMngOptDlg );

	return true;
}

bool CCfgNetMngLogic::OnClickBtnModify( const IArgs& args )
{
	CMsgDispatch::SendMessage( UI_CNSTOOL_MSG_NETMNGSELDATA_Click, (WPARAM)&m_tTPNMServerCfgSel, (LPARAM)em_NETMNGOPT_MODIFY );
	s32 nDodalResult = UIFACTORYMGR_PTR->Domodal( g_stcStrNetMngOptDlg );

	return true;
}

bool CCfgNetMngLogic::OnClickBtnDelete( const IArgs& args )
{
	MSGBOX_RET nResult = MSGBOX_OK;
	MSG_BOX( nResult, "是否要删除该网管服务器？");
	if (nResult == MSGBOX_OK)
	{
		u16 nRet = COMIFMGRPTR->NetMngDeleteCmd(m_tTPNMServerCfgSel);
		if ( nRet != NO_ERROR )
		{
			//MSG_BOX_OK( "删除网管请求发送失败" );
			WARNMESSAGE( "删除网管请求发送失败" );
		}
	}

	return true;
}

HRESULT CCfgNetMngLogic::OnAddNetMngRsp( WPARAM wparam, LPARAM lparam )
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
			LIBDATAMGRPTR->GetNetMngData( vecTTPNMServerCfg );
			Value_ItemNetMng NetMngList( &vecTTPNMServerCfg );
			UIFACTORYMGR_PTR->SetPropertyValue( NetMngList, m_strListNetMng, m_pWndTree);

			memset( &m_tTPNMServerCfgSel, 0, sizeof(TTPNMServerCfg) );
			UpdateBtnState();

			break;
		}
	case em_nmserver_resource_full:
		{
			//MSG_BOX_OK( "添加失败，服务器已满" );
			WARNMESSAGE( "添加失败，服务器已满" );
			break;
		}
	case em_nmserver_invalid_handle:
		{
			//MSG_BOX_OK( "添加失败，数据无效" );
			WARNMESSAGE( "添加失败，数据无效" );
			break;
		}
	default:
		break;
	}

	return S_OK;
}

HRESULT CCfgNetMngLogic::OnNetMngNty( WPARAM wparam, LPARAM lparam )
{
	if (m_pWndTree == NULL)
	{
		return S_FALSE;
	}

	vector<TTPNMServerCfg> vecTTPNMServerCfg;
	LIBDATAMGRPTR->GetNetMngData( vecTTPNMServerCfg );

	Value_ItemNetMng NetMngList( &vecTTPNMServerCfg );
	UIFACTORYMGR_PTR->SetPropertyValue( NetMngList, m_strListNetMng, m_pWndTree);

	UpdateBtnState();

	return S_OK;
}

HRESULT CCfgNetMngLogic::OnModifyNetMngRsp( WPARAM wparam, LPARAM lparam )
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
			LIBDATAMGRPTR->GetNetMngData( vecTTPNMServerCfg );
			
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
			//MSG_BOX_OK( "修改失败，服务器已满" );
			WARNMESSAGE( "修改失败，服务器已满" );
			break;
		}
	case em_nmserver_invalid_handle:
		{
			//MSG_BOX_OK( "修改失败，数据无效" );
			WARNMESSAGE( "修改失败，数据无效" );
			break;
		}
	default:
		break;
	}

	return S_OK;
}

HRESULT CCfgNetMngLogic::OnDelNetMngRsp( WPARAM wparam, LPARAM lparam )
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
			LIBDATAMGRPTR->GetNetMngData( vecTTPNMServerCfg );
			
			Value_ItemNetMng NetMngList( &vecTTPNMServerCfg );
			UIFACTORYMGR_PTR->SetPropertyValue( NetMngList, m_strListNetMng, m_pWndTree);

			memset( &m_tTPNMServerCfgSel, 0, sizeof(TTPNMServerCfg) );
			UpdateBtnState();

			UIFACTORYMGR_PTR->LoadScheme( "SchmNetMngListDefault", m_pWndTree );

			break;
		}
	case em_nmserver_resource_full:
		{
			//MSG_BOX_OK( "删除失败，服务器已满" );
			WARNMESSAGE( "删除失败，服务器已满" );
			break;
		}
	case em_nmserver_invalid_handle:
		{
			//MSG_BOX_OK( "删除失败，数据无效" );
			WARNMESSAGE( "删除失败，数据无效" );
			break;
		}
	default:
		break;
	}
	
	return S_OK;
}

bool CCfgNetMngLogic::OnClickNetMngLst( const IArgs & arg )
{
	if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast<const Args_ClickItemInfo*>(&arg) )
    {
		const IData *pIData = pClickInfo->m_pClickList->GetItemData()->GetUserData();
		if ( const Data_NetMng * pDataTemp = dynamic_cast< const Data_NetMng*>(pIData) )
		{
			m_tTPNMServerCfgSel = pDataTemp->m_tTPNMServerCfg;

			UpdateBtnState();
		}
	}

	return true;
}

bool CCfgNetMngLogic::OnClickNetMngLstBlack( const IArgs& args )
{
	if (m_pWndTree == NULL)
	{
		return S_FALSE;
	}

	memset( &m_tTPNMServerCfgSel, 0, sizeof(TTPNMServerCfg) );
	UpdateBtnState();

	return true;
}

void CCfgNetMngLogic::ResetAllCtrl()
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

void CCfgNetMngLogic::ResetAllData()
{
	memset( &m_tTPNMServerCfgSel, 0, sizeof(TTPNMServerCfg) );
}

void CCfgNetMngLogic::UpdateBtnState()
{
	if (m_pWndTree == NULL)
	{
		return;
	}

	vector<TTPNMServerCfg> vecTTPNMServerCfg;
	LIBDATAMGRPTR->GetNetMngData( vecTTPNMServerCfg );

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