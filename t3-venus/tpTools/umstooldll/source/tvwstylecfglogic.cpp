// tvwstylecfglogic.cpp: implementation of the CTvwStyleCfgLogic class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "umstooldll.h"
#include "tvwstylecfglogic.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CTvwStyleCfgLogic::CTvwStyleCfgLogic():
m_strComboboxTvwStyleCol("ComboboxTvwStyleCol"),
m_strComboboxTvwStyleRow("ComboboxTvwStyleRow"),
m_strLstTvwStyle("TvwStyleListDlg/LstTvwStyle"),
m_strBtnTvwStyleSave("BtnTvwStyleSave")
{
	m_bStyleDataChange = FALSE;
	m_pListWnd = NULL;
}

CTvwStyleCfgLogic::~CTvwStyleCfgLogic()
{
	UnRegMsg();
	UnRegFunc();
}

void CTvwStyleCfgLogic::RegMsg()
{    
	REG_MSG_HANDLER( UI_UMS_HDUSTYLE_NOTIFY, CTvwStyleCfgLogic::OnRefreshTvwStyleInfoNotify, TVWSTYLELOGICRPTR, CTvwStyleCfgLogic );

	REG_MSG_HANDLER( UI_UMSTOOL_MSG_TVWSTYLESAVE, CTvwStyleCfgLogic::OnTvwStyleSave, TVWSTYLELOGICRPTR, CTvwStyleCfgLogic );
	REG_MSG_HANDLER( UI_UMS_HDUSTYLE_RSP, CTvwStyleCfgLogic::OnTvwStyleSaveRsp, TVWSTYLELOGICRPTR, CTvwStyleCfgLogic );
	REG_MSG_HANDLER( UI_UMS_HDUSTYLE_UPDATE_RSP, CTvwStyleCfgLogic::OnTvwStyleUpdateRsp, TVWSTYLELOGICRPTR, CTvwStyleCfgLogic );
}

void CTvwStyleCfgLogic::UnRegMsg()
{

}

bool CTvwStyleCfgLogic::RegCBFun()
{   	 
	REG_GOBAL_MEMBER_FUNC( "CTvwStyleCfgLogic::InitWnd", CTvwStyleCfgLogic::InitWnd, TVWSTYLELOGICRPTR, CTvwStyleCfgLogic);

	REG_LIST_CALLFUNC( "CTvwStyleCfgLogic::OnTvwStyleItem", CTvwStyleCfgLogic::OnTvwStyleItem, TVWSTYLELOGICRPTR, CTvwStyleCfgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CTvwStyleCfgLogic::OnBtnTvwStyleSave", CTvwStyleCfgLogic::OnBtnTvwStyleSave, TVWSTYLELOGICRPTR, CTvwStyleCfgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CTvwStyleCfgLogic::OnBtnTvwStyleMenu", CTvwStyleCfgLogic::OnBtnTvwStyleMenu, TVWSTYLELOGICRPTR, CTvwStyleCfgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CTvwStyleCfgLogic::OnTvwStyleRowEditChange", CTvwStyleCfgLogic::OnTvwStyleRowEditChange, TVWSTYLELOGICRPTR, CTvwStyleCfgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CTvwStyleCfgLogic::OnTvwStyleColEditChange", CTvwStyleCfgLogic::OnTvwStyleColEditChange, TVWSTYLELOGICRPTR, CTvwStyleCfgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CTvwStyleCfgLogic::OnTvwStyleColClick", CTvwStyleCfgLogic::OnTvwStyleColClick, TVWSTYLELOGICRPTR, CTvwStyleCfgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CTvwStyleCfgLogic::OnTvwStyleRowClick", CTvwStyleCfgLogic::OnTvwStyleRowClick, TVWSTYLELOGICRPTR, CTvwStyleCfgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CTvwStyleCfgLogic::OnBtnTvwStyleMenuDel", CTvwStyleCfgLogic::OnBtnTvwStyleMenuDel, TVWSTYLELOGICRPTR, CTvwStyleCfgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CTvwStyleCfgLogic::OnTvwStyleRowEditOnChar", CTvwStyleCfgLogic::OnTvwStyleRowEditOnChar, TVWSTYLELOGICRPTR, CTvwStyleCfgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CTvwStyleCfgLogic::OnTvwStyleColEditOnChar", CTvwStyleCfgLogic::OnTvwStyleColEditOnChar, TVWSTYLELOGICRPTR, CTvwStyleCfgLogic ); 

	return true;
}

bool CTvwStyleCfgLogic::UnRegFunc()
{

	return true;
}


bool CTvwStyleCfgLogic::InitWnd(  const IArgs & arg )
{   
	CWndLogicBase::InitWnd( arg );

	InitLogicData();

	UpdateTvwStyleList();

	if ( NULL == m_pListWnd )
	{
		m_pListWnd = (CTransparentViewList*)UIFACTORYMGR_PTR->GetWindowPtr( m_strLstTvwStyle, m_pWndTree );
	}

    return true;
}

void CTvwStyleCfgLogic::Clear()
{
	UIFACTORYMGR_PTR->LoadScheme( "SchmTvwStyleListDataClean", m_pWndTree );

	m_tSelTvwStyleInfo.Clear();
	m_tSelTvwStyleInfo.nRow = 0;		//设置行号
	m_tSelTvwStyleInfo.nCol = 0;		//设置列号

	for ( s32 nIndex = 0; nIndex < m_tHduStyleDataMatrix.m_byCol*m_tHduStyleDataMatrix.m_byRow; nIndex++ )
	{
		m_tHduStyleDataMatrix.m_atUnits[nIndex].Clear();
	}
	m_tHduStyleDataMatrix.Clear();

	//InitLogicData();
	UIFACTORYMGR_PTR->SetComboText( m_strComboboxTvwStyleRow, "0", m_pWndTree );
	UIFACTORYMGR_PTR->SetComboText( m_strComboboxTvwStyleCol, "0", m_pWndTree );

	m_bStyleDataChange = FALSE;

	UpdateTvwStyleList();

	if ( NULL != m_pListWnd )
	{
		m_pListWnd->SetListOffset(CPoint(0,0));
	}
}

void CTvwStyleCfgLogic::InitLogicData()
{
	std::vector<CString> vecRowData;
	char chData[3];
	s32 nIndex = 1;
	for ( nIndex = 1; nIndex < 8; nIndex++ )
	{
		memset( chData, 0, 3 );
		itoa( nIndex, chData, 10 );
		vecRowData.push_back(chData);
	}
	UIFACTORYMGR_PTR->SetComboListData( m_strComboboxTvwStyleRow, vecRowData, m_pWndTree );  //设置电视墙预案Row combo列表
	UIFACTORYMGR_PTR->SetComboText( m_strComboboxTvwStyleRow, "0", m_pWndTree );

	vecRowData.clear();
	for ( nIndex = 1; nIndex < 57; nIndex++ )
	{
		memset( chData, 0, 3 );
		itoa( nIndex, chData, 10 );
		vecRowData.push_back(chData);
	}
	UIFACTORYMGR_PTR->SetComboListData( m_strComboboxTvwStyleCol, vecRowData, m_pWndTree );  //设置电视墙预案Col combo列表
	UIFACTORYMGR_PTR->SetComboText( m_strComboboxTvwStyleCol, "", m_pWndTree );
	UIFACTORYMGR_PTR->EnableWindow( m_strComboboxTvwStyleCol, false, m_pWndTree );

	m_tSelTvwStyleInfo.nRow = 0;		//设置行号
	m_tSelTvwStyleInfo.nCol = 0;		//设置列号

	UpdateTvwStyleList();
}

bool CTvwStyleCfgLogic::OnBtnTvwStyleSave( const IArgs & arg )
{
	String strComboboxTvwStyleRow;
	UIFACTORYMGR_PTR->GetComboText( m_strComboboxTvwStyleRow, strComboboxTvwStyleRow, m_pWndTree );
	if ( "" == strComboboxTvwStyleRow )
	{
		MSG_BOX_OK( "电视墙风格行数不能为空！" );
		return false;
	}

	String strComboboxTvwStyleCol;
	UIFACTORYMGR_PTR->GetComboText( m_strComboboxTvwStyleCol, strComboboxTvwStyleCol, m_pWndTree );
	if ( "" == strComboboxTvwStyleCol )
	{
		MSG_BOX_OK( "电视墙风格列数不能为空！" );
		return false;
	}

	m_tHduStyleDataMatrix.m_byRow = m_tSelTvwStyleInfo.nRow;
	m_tHduStyleDataMatrix.m_byCol = m_tSelTvwStyleInfo.nCol;

	//调用发送电视墙风格保存通信接口
	u16 nRet = COMMONMGRIFPTR->AddTvwStyleReq(m_tHduStyleDataMatrix);;
	if ( nRet != NO_ERROR )
	{
		MESSAGEWND( "保存电视墙风格请求发送失败" );
	}

	UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwStyleSave, false, m_pWndTree );

	return true;
}

HRESULT CTvwStyleCfgLogic::OnTvwStyleSave( WPARAM wparam, LPARAM lparam)
{
	if ( 0 == wparam )      //点击取消
	{	
		std::pair<s32,s32> pairLayorSlot( m_tSelTvwStyleInfo.tHduStyleUnit.m_byLayer, m_tSelTvwStyleInfo.tHduStyleUnit.m_bySlot );
		String strDevice = GetDeviceByLayorAndSlot(pairLayorSlot);
		if ( 0 != strcmp( m_tSelTvwStyleInfo.tChanName.m_abyAlias, strDevice.c_str() ) )
		{
			m_tHduStyleDataMatrix.m_atUnits[m_tSelTvwStyleInfo.nKey].Clear();

			UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwStyleSave, true, m_pWndTree );
		}
	}
	else
	{
		m_tSelTvwStyleInfo = *reinterpret_cast<TTvwStyleInfo*>(wparam);

		std::pair<s32,s32> pairLayorSlot( m_tSelTvwStyleInfo.tHduStyleUnit.m_byLayer, m_tSelTvwStyleInfo.tHduStyleUnit.m_bySlot );
		String strDevice = GetDeviceByLayorAndSlot(pairLayorSlot);
		
		//更新THduStyleUnit单元
		m_tHduStyleDataMatrix.m_atUnits[m_tSelTvwStyleInfo.nKey] = m_tSelTvwStyleInfo.tHduStyleUnit;

		if ( strDevice.size() < TP_MAX_ALIAS_LEN )
		{
			m_tHduStyleDataMatrix.m_atUnits[m_tSelTvwStyleInfo.nKey].m_tName.Clear();
			strncpy( m_tHduStyleDataMatrix.m_atUnits[m_tSelTvwStyleInfo.nKey].m_tName.m_abyAlias, strDevice.c_str(), strDevice.size() );
			m_tHduStyleDataMatrix.m_atUnits[m_tSelTvwStyleInfo.nKey].m_tName.m_abyAlias[strDevice.size()] = '\0';
		}
		
		UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwStyleSave, true, m_pWndTree );
	}

	UpdateTvwStyleList();

	return TRUE;
}

bool CTvwStyleCfgLogic::OnTvwStyleRowEditOnChar( const IArgs & arg )
{
	m_tHduStyleDataMatrix.Clear();
	for ( s32 nIndex = 0; nIndex < m_tHduStyleDataMatrix.m_byCol*m_tHduStyleDataMatrix.m_byRow; nIndex++ )
	{
		m_tHduStyleDataMatrix.m_atUnits[nIndex].Clear();
	}
	
	String strComboboxTvwStyleRow;
	UIFACTORYMGR_PTR->GetComboText( m_strComboboxTvwStyleRow, strComboboxTvwStyleRow, m_pWndTree );
	s32 nRow = atoi(strComboboxTvwStyleRow.c_str());

	if ( nRow != m_tSelTvwStyleInfo.nRow )
	{
		m_tSelTvwStyleInfo.nRow = nRow;	    	//设置行号

		if ( nRow == 0 )
		{		
			m_tSelTvwStyleInfo.nCol = 0;		//设置列号	
			UIFACTORYMGR_PTR->SetComboText( m_strComboboxTvwStyleCol, "", m_pWndTree );  //设置单板默认类型名
		}
		else
		{
			m_tSelTvwStyleInfo.nCol = 1;		//设置列号			
			UIFACTORYMGR_PTR->SetComboText( m_strComboboxTvwStyleCol, "1", m_pWndTree );  //设置单板默认类型名
		}
	}
	
	m_tHduStyleDataMatrix.m_byRow = m_tSelTvwStyleInfo.nRow;
	m_tHduStyleDataMatrix.m_byCol = m_tSelTvwStyleInfo.nCol;

	UpdateTvwStyleList();
	
	return true;
}

bool CTvwStyleCfgLogic::OnTvwStyleRowEditChange( const IArgs & arg )
{
	String strComboboxTvwStyleRow;
	UIFACTORYMGR_PTR->GetComboText( m_strComboboxTvwStyleRow, strComboboxTvwStyleRow, m_pWndTree );

	if ( "" != strComboboxTvwStyleRow )
	{
		s32 nRow = atoi(strComboboxTvwStyleRow.c_str());
		s32 nLen = strComboboxTvwStyleRow.size();

		if ( nRow > 7 || nRow <= 0 || 
			(strComboboxTvwStyleRow.at(nLen - 1) > '7') || (strComboboxTvwStyleRow.at(nLen - 1) <= '0') )
		{
			nRow = m_tSelTvwStyleInfo.nRow;
			char chData[3];
			memset( chData, 0, 3 );
			itoa( nRow , chData, 10 );
			if ( 0 == nRow )
			{
				UIFACTORYMGR_PTR->SetComboText( m_strComboboxTvwStyleRow, "", m_pWndTree );
			}
			else
			{
				UIFACTORYMGR_PTR->SetComboText( m_strComboboxTvwStyleRow, chData, m_pWndTree );
			}

			Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strComboboxTvwStyleRow, m_pWndTree );
			if ( NULL != pWnd )
			{
				(((CTransparentComboBox*)pWnd)->GetEditPoint())->SetSel(-1);
			}
		}

		UIFACTORYMGR_PTR->EnableWindow( m_strComboboxTvwStyleCol, true, m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->EnableWindow( m_strComboboxTvwStyleCol, false, m_pWndTree );
	}

	UIFACTORYMGR_PTR->LoadScheme( "SchmTvwStyleListDataClean", m_pWndTree );
	UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwStyleSave, false, m_pWndTree );

	SetStyleColData();

	return true;
}

void CTvwStyleCfgLogic::SetStyleColData()
{
	String strComboboxTvwStyleRow;
	UIFACTORYMGR_PTR->GetComboText( m_strComboboxTvwStyleRow, strComboboxTvwStyleRow, m_pWndTree );
	
	s32 nRow = atoi(strComboboxTvwStyleRow.c_str());
	if ( 0 == nRow)
	{
		UpdateTvwStyleList();
		return;
	}

	s32 nCol = 0;
	if( 0 != 56%nRow )
	{
		nCol = 56/nRow + 1;
	}
	else
	{
		nCol = 56/nRow;
	}

	char chData[3];
	std::vector<CString> vecComboboxTvwStyleCol;
	for( s32 nIndex = 1; nIndex <= nCol; nIndex++ )
	{
		if ( nRow*nIndex > 56 )
		{
			break;
		}

		memset( chData, 0, 3 );
		itoa( nIndex, chData, 10 );
		vecComboboxTvwStyleCol.push_back(chData);
	}

	UIFACTORYMGR_PTR->SetComboListData( m_strComboboxTvwStyleCol, vecComboboxTvwStyleCol, m_pWndTree );

 	//m_tSelTvwStyleInfo.nRow = nRow;		//设置行号

	memset( chData, 0, 3 );
	itoa( m_tSelTvwStyleInfo.nCol , chData, 10 );
 	UIFACTORYMGR_PTR->SetComboText( m_strComboboxTvwStyleCol, chData, m_pWndTree );

	UpdateTvwStyleList();

}

bool CTvwStyleCfgLogic::OnTvwStyleColEditOnChar( const IArgs & arg )
{
	m_tHduStyleDataMatrix.Clear();
	for ( s32 nIndex = 0; nIndex < m_tHduStyleDataMatrix.m_byCol*m_tHduStyleDataMatrix.m_byRow; nIndex++ )
	{
		m_tHduStyleDataMatrix.m_atUnits[nIndex].Clear();
	}
	
	String strComboboxTvwStyleCol;
	UIFACTORYMGR_PTR->GetComboText( m_strComboboxTvwStyleCol, strComboboxTvwStyleCol, m_pWndTree );

 	s32 nCol = atoi(strComboboxTvwStyleCol.c_str());

	m_tSelTvwStyleInfo.nCol = nCol;	

	//设置重置后列表显示的数据
	m_tHduStyleDataMatrix.m_byRow = m_tSelTvwStyleInfo.nRow;
	m_tHduStyleDataMatrix.m_byCol = m_tSelTvwStyleInfo.nCol;

	UpdateTvwStyleList();

	return true;
}

bool CTvwStyleCfgLogic::OnTvwStyleColEditChange( const IArgs & arg )
{
	String strComboboxTvwStyleRow;
	UIFACTORYMGR_PTR->GetComboText( m_strComboboxTvwStyleRow, strComboboxTvwStyleRow, m_pWndTree );	
	s32 nRow = atoi(strComboboxTvwStyleRow.c_str());
	s32 nColMax = 0;
	if ( 0 == nRow)
	{
		return true;
	}
	else
	{
		nColMax = 56/nRow;
	}

	String strComboboxTvwStyleCol;
	UIFACTORYMGR_PTR->GetComboText( m_strComboboxTvwStyleCol, strComboboxTvwStyleCol, m_pWndTree );
	if ( "" != strComboboxTvwStyleCol )
	{
		s32 nCol = atoi(strComboboxTvwStyleCol.c_str());
		s32 nLen = strComboboxTvwStyleCol.size();
		if ( nCol > nColMax || nCol <= 0 || 
			(strComboboxTvwStyleCol.at(nLen - 1) > '9') || (strComboboxTvwStyleCol.at(nLen - 1) < '0') )
		{
			nCol = m_tSelTvwStyleInfo.nCol;
			char chData[3];
			memset( chData, 0, 3 );
			itoa( nCol , chData, 10 );
			if ( 0 == nCol )
			{
				UIFACTORYMGR_PTR->SetComboText( m_strComboboxTvwStyleCol, "", m_pWndTree );
			} 
			else
			{
				UIFACTORYMGR_PTR->SetComboText( m_strComboboxTvwStyleCol, chData, m_pWndTree );
			}

			Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strComboboxTvwStyleCol, m_pWndTree );
			if ( NULL != pWnd )
			{
				(((CTransparentComboBox*)pWnd)->GetEditPoint())->SetSel(-1);
			}
		}
	}
	
	UIFACTORYMGR_PTR->LoadScheme( "SchmTvwStyleListDataClean", m_pWndTree );
	UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwStyleSave, false, m_pWndTree );

 	SetDynamicStyleList();
	
	return true;
}

void CTvwStyleCfgLogic::SetDynamicStyleList()
{
	String strComboboxTvwStyleCol;
	UIFACTORYMGR_PTR->GetComboText( m_strComboboxTvwStyleCol, strComboboxTvwStyleCol, m_pWndTree );
	s32 nCol = atoi(strComboboxTvwStyleCol.c_str());

	m_tSelTvwStyleInfo.nCol = nCol;   //设置列号

	UpdateTvwStyleList();
}

bool CTvwStyleCfgLogic::OnTvwStyleColClick( const IArgs & arg )
{
	m_tHduStyleDataMatrix.Clear();
	for ( s32 nIndex = 0; nIndex < m_tHduStyleDataMatrix.m_byCol*m_tHduStyleDataMatrix.m_byRow; nIndex++ )
	{
		m_tHduStyleDataMatrix.m_atUnits[nIndex].Clear();
	}
	
	//设置重置后列表显示的数据
	m_tHduStyleDataMatrix.m_byRow = m_tSelTvwStyleInfo.nRow;
	m_tHduStyleDataMatrix.m_byCol = m_tSelTvwStyleInfo.nCol;

	UpdateTvwStyleList();

	return true;
}

bool CTvwStyleCfgLogic::OnTvwStyleRowClick( const IArgs & arg )
{
	m_tHduStyleDataMatrix.Clear();
	for ( s32 nIndex = 0; nIndex < m_tHduStyleDataMatrix.m_byCol*m_tHduStyleDataMatrix.m_byRow; nIndex++ )
	{
		m_tHduStyleDataMatrix.m_atUnits[nIndex].Clear();
	}

	String strComboboxTvwStyleRow;
	UIFACTORYMGR_PTR->GetComboText( m_strComboboxTvwStyleRow, strComboboxTvwStyleRow, m_pWndTree );
	s32 nRow = atoi(strComboboxTvwStyleRow.c_str());

	UIFACTORYMGR_PTR->SetComboText( m_strComboboxTvwStyleCol, "1", m_pWndTree );  //设置单板默认类型名

	m_tSelTvwStyleInfo.nRow = nRow;		//设置行号
	m_tSelTvwStyleInfo.nCol = 1;		//设置列号

	m_tHduStyleDataMatrix.m_byRow = m_tSelTvwStyleInfo.nRow;
	m_tHduStyleDataMatrix.m_byCol = m_tSelTvwStyleInfo.nCol;

	UpdateTvwStyleList();

	return true;
}

void CTvwStyleCfgLogic::UpdateTvwStyleList()
{
	String strComboboxTvwStyleRow;
	UIFACTORYMGR_PTR->GetComboText( m_strComboboxTvwStyleRow, strComboboxTvwStyleRow, m_pWndTree );
	s32 nRow = atoi(strComboboxTvwStyleRow.c_str());

	String strComboboxTvwStyleCol;
	UIFACTORYMGR_PTR->GetComboText( m_strComboboxTvwStyleCol, strComboboxTvwStyleCol, m_pWndTree );
	s32 nCol = atoi(strComboboxTvwStyleCol.c_str());

	std::vector<TTvwStyleInfo> vecTPTvwStyleInfo;
	TTvwStyleInfo tTvwStyleInfo;
	tTvwStyleInfo.nRow = nRow;
	tTvwStyleInfo.nCol = nCol;
	for ( s32 nIndex = 0; nIndex < nCol*nRow; nIndex++ )
	{
		tTvwStyleInfo.nKey = nIndex;
		tTvwStyleInfo.tHduStyleUnit = m_tHduStyleDataMatrix.m_atUnits[nIndex];

// 		std::pair<s32,s32> pairLayorSlot( m_tHduStyleDataMatrix.m_atUnits[nIndex].m_byLayer, m_tHduStyleDataMatrix.m_atUnits[nIndex].m_bySlot );
// 		String strDevice = GetDeviceByLayorAndSlot(pairLayorSlot);
		String strDevice = m_tHduStyleDataMatrix.m_atUnits[nIndex].m_tName.m_abyAlias;
		if ( strDevice.size() < TP_MAX_ALIAS_LEN )
		{
			tTvwStyleInfo.tChanName.Clear();
			strncpy( tTvwStyleInfo.tChanName.m_abyAlias, strDevice.c_str(), strDevice.size() );
			tTvwStyleInfo.tChanName.m_abyAlias[strDevice.size()] = '\0';

			//经需求确认，通道号均显示0或1 -- 20140603 by xhx
			//经需求确认，显示配置时弹出框中显示的通道号  -- 20140521 by xhx
// 			u8 nShowChanNo = GetShowChanNo( tTvwStyleInfo.tHduStyleUnit.m_byLayer, tTvwStyleInfo.tHduStyleUnit.m_bySlot, 
// 				tTvwStyleInfo.tHduStyleUnit.m_byChanIndex );
// 			tTvwStyleInfo.tHduStyleUnit.m_byChanIndex = nShowChanNo;
		}

		vecTPTvwStyleInfo.push_back(tTvwStyleInfo);
	}
	
	Value_ViewListTvwStyle valStyle(&vecTPTvwStyleInfo);
	TListRangeInfo tListRangeInfo;
	tListRangeInfo.nMaxRow = nRow;
	tListRangeInfo.nMaxColumn = nCol;
	valStyle.m_tListRangeInfo = tListRangeInfo;
	valStyle.m_strClickItemFunc = "CTvwStyleCfgLogic::OnTvwStyleItem";
	UIFACTORYMGR_PTR->SetPropertyValue( valStyle, m_strLstTvwStyle, m_pWndTree );

	BOOL bShow = UIFACTORYMGR_PTR->IsVisible( g_stcStrTvwStyleCfgDlg.c_str() );
	if ( bShow )
	{
		if ( CompareStyleDataMatrixChange() )
		{
			UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwStyleSave, true, m_pWndTree );
		}
		else
		{
			UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwStyleSave, false, m_pWndTree );
		}
	}
}

bool CTvwStyleCfgLogic::OnTvwStyleItem( const IArgs & arg )
{
	if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast<const Args_ClickItemInfo*>(&arg) )
    {
		UIFACTORYMGR_PTR->ShowWindow( g_stcStrTvwStyleListMenuDlg, true );

		CRect rectItem = pClickInfo->m_rcFrame;
		POINT pt;
		pt.x = rectItem.left + rectItem.Width() - 20;
		pt.y = rectItem.top + rectItem.Height() - 20;
		UIFACTORYMGR_PTR->SetWndPos( pt, g_stcStrTvwStyleListMenuDlg, m_pWndTree, g_stcStrMainFrmDlg );

        const IData *pIData = pClickInfo->m_pClickList->GetItemData()->GetUserData();
        if ( const Data_TvwStyleInfo * pDataTemp = dynamic_cast< const Data_TvwStyleInfo*>(pIData) )
        {   			
			m_tSelTvwStyleInfo = pDataTemp->m_tTvwStyleInfo;

// 			if ( m_tSelTvwStyleInfo.tHduStyleUnit.m_byChanIndex != HDU_MAX_CHANNEL_NUM )
// 			{
// 				u8 byChanNo = m_tSelTvwStyleInfo.tHduStyleUnit.m_byChanIndex - m_tSelTvwStyleInfo.tHduStyleUnit.m_bySlot*2
// 					- m_tSelTvwStyleInfo.tHduStyleUnit.m_byLayer*7*2 - 1;
// 				
// 				m_tSelTvwStyleInfo.tHduStyleUnit.m_byChanIndex = byChanNo;
// 			}
		}

		if ( HDU_MAX_CHANNEL_NUM == m_tSelTvwStyleInfo.tHduStyleUnit.m_byChanIndex )
		{
			UIFACTORYMGR_PTR->LoadScheme( "SchmDelEnable", m_pWndTree );
		}
		else
		{
			UIFACTORYMGR_PTR->LoadScheme( "SchmDelAble", m_pWndTree );
		}
	}

	return true;
}

bool CTvwStyleCfgLogic::OnBtnTvwStyleMenu( const IArgs & arg )
{
// 	if( CUmstoolCommon::GetDeviceName().size() == 0 )
// 	{
// 		MSG_BOX_OK("通道名为空，无法配置！");
// 
// 		return false;
// 	}

	UIFACTORYMGR_PTR->ShowWindow( g_stcStrTvwStyleListMenuDlg, false );

	//显示电视墙风格配置页面
	CMsgDispatch::SendMessage( UI_UMSTOOL_MSG_TVWSTYLESELDATA_Click, (WPARAM)&m_tSelTvwStyleInfo, 0 );
	s32 nDodalResult = UIFACTORYMGR_PTR->Domodal( g_stcStrTvwStyleOptDlg );

	return true;
}

bool CTvwStyleCfgLogic::OnBtnTvwStyleMenuDel( const IArgs & arg )
{
	UIFACTORYMGR_PTR->ShowWindow( g_stcStrTvwStyleListMenuDlg, false );

	m_tHduStyleDataMatrix.m_atUnits[m_tSelTvwStyleInfo.nKey].Clear();

	UpdateTvwStyleList();

	return true;
}

HRESULT CTvwStyleCfgLogic::OnRefreshTvwStyleInfoNotify( WPARAM wparam, LPARAM lparam)
{
	UIFACTORYMGR_PTR->LoadScheme( "SchmTvwStyleListDataClean", m_pWndTree );

	RefreshTvwStyleInfo();

	return S_OK;
}

void CTvwStyleCfgLogic::RefreshTvwStyleInfo()
{
	m_tHduStyleDataMatrix = DATAMGRPTR->GetUmsTvwStyleData();
	
	m_tSelTvwStyleInfo.nCol = m_tHduStyleDataMatrix.m_byCol;
	m_tSelTvwStyleInfo.nRow = m_tHduStyleDataMatrix.m_byRow;

	s8 chData[3];
	memset( chData, 0, 3 );
	itoa( m_tSelTvwStyleInfo.nRow , chData, 10 );
	UIFACTORYMGR_PTR->SetComboText( m_strComboboxTvwStyleRow, chData, m_pWndTree );

 	memset( chData, 0, 3 );
 	itoa( m_tSelTvwStyleInfo.nCol , chData, 10 );
	if ( 0 == m_tSelTvwStyleInfo.nCol )
	{
		UIFACTORYMGR_PTR->SetComboText( m_strComboboxTvwStyleCol, "", m_pWndTree );
		UIFACTORYMGR_PTR->EnableWindow( m_strComboboxTvwStyleCol, false, m_pWndTree );
	} 
	else
	{
		UIFACTORYMGR_PTR->SetComboText( m_strComboboxTvwStyleCol, chData, m_pWndTree );
	}
	
	UpdateTvwStyleList();
}

HRESULT CTvwStyleCfgLogic::OnTvwStyleSaveRsp( WPARAM wparam, LPARAM lparam)
{
	EmModifyHduRet emRet = *reinterpret_cast<EmModifyHduRet*>(wparam);
	String strErrHead = "保存电视墙风格失败：";
	String strErr;
	switch(emRet)
	{
	case em_hdu_modify_success:
		{
			strErr = "";
		}
		break;
	case em_hdu_invalid_index:
		{
			strErr = "无效的索引";
		}
		break;
	case em_hdu_brd_no_cfg:
		{
			strErr = "配置无效";
		}
		break;
	default:
		{
		}
		break;
	}

	if ( !strErr.empty() )
	{
		strErrHead = strErrHead + strErr;
		MESSAGEWND( strErrHead.c_str() );
	}
	
	return S_OK;
}

HRESULT CTvwStyleCfgLogic::OnTvwStyleUpdateRsp( WPARAM wparam, LPARAM lparam)
{
	EmModifyHduRet emRet = *reinterpret_cast<EmModifyHduRet*>(wparam);
	String strErrHead = "更新电视墙风格失败：";
	String strErr;
	switch(emRet)
	{
	case em_hdu_modify_success:
		{
			strErr = "";
		}
		break;
	case em_hdu_invalid_index:
		{
			strErr = "无效的索引";
		}
		break;
	case em_hdu_brd_no_cfg:
		{
			strErr = "配置无效";
		}
		break;
	default:
		{
		}
		break;
	}
	
	if ( !strErr.empty() )
	{
		strErrHead = strErrHead + strErr;
		MESSAGEWND( strErrHead.c_str() );
	}
	
	return S_OK;
}

BOOL CTvwStyleCfgLogic::CheckPageDataChangeToSave()
{	
	if ( CompareStyleDataMatrixChange() )
	{
		MSGBOX_RET nMsgBoxRet = MSGBOX_CANCEL;
		MSG_BOX( nMsgBoxRet, "电视墙风格数据有变化，是否保存？" );
		if ( MSGBOX_OK == nMsgBoxRet )
		{
			IArgs arg("");
			if ( !OnBtnTvwStyleSave(arg) )	//保存电视墙风格数据
			{
				return FALSE;
			}
		}
		else								//取消则恢复原始模式信息
		{		
			RefreshTvwStyleInfo();
		}
	}
	
	return TRUE;
}

String CTvwStyleCfgLogic::GetDeviceByLayorAndSlot(const std::pair<s32,s32>& pairLayorSlot)
{
	THduCfg tHduCfg;
	std::multimap<u8,THduCfg> mulmapHduCfg = DATAMGRPTR->GetUmsTvwBoardData();
	for ( std::multimap<u8,THduCfg>::iterator iter = mulmapHduCfg.begin(); iter != mulmapHduCfg.end(); iter++ )
	{
		tHduCfg = (*iter).second;
		if ( tHduCfg.m_byLayer == pairLayorSlot.first && tHduCfg.m_bySlot == pairLayorSlot.second )
		{
			return tHduCfg.m_tName.m_abyAlias;
		}
	}

	return "";
}

BOOL CTvwStyleCfgLogic::CompareStyleDataMatrixChange()
{
	THduStyleData tHduStyleDataMatrix = DATAMGRPTR->GetUmsTvwStyleData();

	if ( NULL == m_pWndTree )
	{
		return FALSE;
	}
	
	if( m_tHduStyleDataMatrix.m_byCol == tHduStyleDataMatrix.m_byCol && m_tHduStyleDataMatrix.m_byRow == tHduStyleDataMatrix.m_byRow )
	{
		if ( 0 == m_tHduStyleDataMatrix.m_byCol )
		{
			UIFACTORYMGR_PTR->SetComboText( m_strComboboxTvwStyleCol, "", m_pWndTree );  //避免注销再登陆时，列数显示为0
		}

		for ( s32 nIndex = 0; nIndex < m_tHduStyleDataMatrix.m_byCol*m_tHduStyleDataMatrix.m_byRow; nIndex++ )
		{
			if( tHduStyleDataMatrix.m_atUnits[nIndex].m_byLayer != m_tHduStyleDataMatrix.m_atUnits[nIndex].m_byLayer || 
				tHduStyleDataMatrix.m_atUnits[nIndex].m_bySlot != m_tHduStyleDataMatrix.m_atUnits[nIndex].m_bySlot ||
				tHduStyleDataMatrix.m_atUnits[nIndex].m_byChanIndex != m_tHduStyleDataMatrix.m_atUnits[nIndex].m_byChanIndex
				)
			{
				return TRUE;
			}
		}

		return FALSE;
	}
	else
	{
		String strComboboxTvwStyleRow, strComboboxTvwStyleCol;
		UIFACTORYMGR_PTR->GetComboText( m_strComboboxTvwStyleRow, strComboboxTvwStyleRow, m_pWndTree );
    	UIFACTORYMGR_PTR->GetComboText( m_strComboboxTvwStyleCol, strComboboxTvwStyleCol, m_pWndTree );

		if ( "" == strComboboxTvwStyleRow && "" == strComboboxTvwStyleCol )
		{
			if( m_tHduStyleDataMatrix.m_byCol != tHduStyleDataMatrix.m_byCol || m_tHduStyleDataMatrix.m_byRow != tHduStyleDataMatrix.m_byRow )
			{
				return TRUE;
			}	
		}

		if ( 0 == m_tHduStyleDataMatrix.m_byCol && 0 == m_tHduStyleDataMatrix.m_byRow )   //防止GetUmsTvwStyleData数据刷新在其之后
		{
			return FALSE;
		}

		return TRUE;
	}

	return TRUE;
}

// u8 CTvwStyleCfgLogic::GetShowChanNo( u8 byLayer, u8 bySlot, u8 byChanNo )
// {	
// 	u8 byShowChanNo = byChanNo;
// 	if ( 0 == byChanNo )
// 	{
// 		byShowChanNo = byLayer*7*2 + bySlot*2 + 1;
// 	}
// 	else if ( 1 == byChanNo )
// 	{
// 		byShowChanNo = byLayer*7*2 + bySlot*2 + 2;
// 	}
// 	
// 	return byShowChanNo;
// }
