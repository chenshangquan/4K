// tvwstyleoptdlglogic.cpp: implementation of the CTvwStyleOptDlgLogic class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "umstooldll.h"
#include "tvwstyleoptdlglogic.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CTvwStyleOptDlgLogic::CTvwStyleOptDlgLogic():
m_strComboboxTvwStyleOptDeviceName("ComboboxTvwStyleOptDeviceName"),
m_strComboboxTvwStyleOptChanNo("ComboboxTvwStyleOptChanNo"),
m_strBtnTvwStyleOptOk("BtnTvwStyleOptOk")
{

}

CTvwStyleOptDlgLogic::~CTvwStyleOptDlgLogic()
{
	UnRegMsg();
	UnRegFunc();
}

void CTvwStyleOptDlgLogic::RegMsg()
{    
    //REG_MSG_HANDLER( UI_CNS_DISCONNECTED, CTvwStyleOptDlgLogic::OnDisConnect, m_pLogic, CTvwStyleOptDlgLogic );
	REG_MSG_HANDLER( UI_UMSTOOL_MSG_TVWSTYLESELDATA_Click, CTvwStyleOptDlgLogic::OnTvwStyleSelData, TVWSTYLEOPTLOGICRPTR, CTvwStyleOptDlgLogic );

}

void CTvwStyleOptDlgLogic::UnRegMsg()
{

}

bool CTvwStyleOptDlgLogic::RegCBFun()
{   	 
	REG_GOBAL_MEMBER_FUNC( "CTvwStyleOptDlgLogic::InitWnd", CTvwStyleOptDlgLogic::InitWnd, TVWSTYLEOPTLOGICRPTR, CTvwStyleOptDlgLogic);

	REG_GOBAL_MEMBER_FUNC( "CTvwStyleOptDlgLogic::OnBtnTvwStyleOptOk", CTvwStyleOptDlgLogic::OnBtnTvwStyleOptOk, TVWSTYLEOPTLOGICRPTR, CTvwStyleOptDlgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CTvwStyleOptDlgLogic::OnBtnTvwStyleOptCancel", CTvwStyleOptDlgLogic::OnBtnTvwStyleOptCancel, TVWSTYLEOPTLOGICRPTR, CTvwStyleOptDlgLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CTvwStyleOptDlgLogic::OnChanNameEditChange", CTvwStyleOptDlgLogic::OnChanNameEditChange, TVWSTYLEOPTLOGICRPTR, CTvwStyleOptDlgLogic ); 

	return true;
}

bool CTvwStyleOptDlgLogic::UnRegFunc()
{

	return true;
}

bool CTvwStyleOptDlgLogic::InitWnd(  const IArgs & arg )
{   
	CWndLogicBase::InitWnd( arg );

    return true;
}

void CTvwStyleOptDlgLogic::Clear()
{
	s32 nResult = 0;
	UIFACTORYMGR_PTR->Endmodal(nResult, g_stcStrTvwStyleOptDlg );

}

bool CTvwStyleOptDlgLogic::OnBtnTvwStyleOptOk( const IArgs & arg )
{
	String strComboboxTvwStyleOptDeviceName;
	UIFACTORYMGR_PTR->GetComboText( m_strComboboxTvwStyleOptDeviceName, strComboboxTvwStyleOptDeviceName, m_pWndTree );
	
	if ( "" == strComboboxTvwStyleOptDeviceName )
	{
		MSG_BOX_OK("设备名称不能为空！");
		
		return false;
	}

	std::pair<s32,s32> pairData = GetLayorAndSlotByDevice(strComboboxTvwStyleOptDeviceName);

	//设置通道层、槽
	m_tTvwStyleInfo.tHduStyleUnit.m_byLayer = pairData.first;
	m_tTvwStyleInfo.tHduStyleUnit.m_bySlot = pairData.second;

	//设置通道号
	if( !RevertChanNoToBrdPos() )
	{
		return false;
	}

	if ( CheckExistChanInfo(m_tTvwStyleInfo.tHduStyleUnit) )
	{
		MSG_BOX_OK( "当前通道信息已经存在，不能重复添加" );
		
		return false;
	}

	s32 nResult = 0;
	UIFACTORYMGR_PTR->Endmodal(nResult, g_stcStrTvwStyleOptDlg );

	//发送数据到电视墙单板配置页面     和通知应该是一样的
	CMsgDispatch::SendMessage( UI_UMSTOOL_MSG_TVWSTYLESAVE, (WPARAM)&m_tTvwStyleInfo, 0 );

	return true;
}

bool CTvwStyleOptDlgLogic::OnBtnTvwStyleOptCancel( const IArgs & arg )
{
	s32 nResult = 0;
	UIFACTORYMGR_PTR->Endmodal(nResult, g_stcStrTvwStyleOptDlg );

	CMsgDispatch::SendMessage( UI_UMSTOOL_MSG_TVWSTYLESAVE, 0, 0 );

	return true;
}

HRESULT CTvwStyleOptDlgLogic::OnTvwStyleSelData( WPARAM wparam, LPARAM lparam)
{
	UIFACTORYMGR_PTR->LoadScheme( "SchTvwStyleOptClean", m_pWndTree );
	//通道配置弹出后  显示设备名称数据

	if ( 0 == CUmstoolCommon::GetDeviceName().size() )
	{
		UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwStyleOptOk, false, m_pWndTree );
	}
	else
	{
		UIFACTORYMGR_PTR->EnableWindow( m_strBtnTvwStyleOptOk, true, m_pWndTree );
	}
	
	/*UIFACTORYMGR_PTR->SetComboListData( m_strComboboxTvwStyleOptDeviceName, CUmstoolCommon::GetDeviceName(), m_pWndTree );*/	
	
	//当前选中的数据到风格
	m_tTvwStyleInfo = *reinterpret_cast<TTvwStyleInfo*>(wparam);
	RevertComboboxDeviceName();

	if ( HDU_MAX_CHANNEL_NUM != m_tTvwStyleInfo.tHduStyleUnit.m_byChanIndex )
	{	
		String  strComboboxTvwStyleOptDeviceName;
		std::pair<s32,s32> pairLayorSlot( m_tTvwStyleInfo.tHduStyleUnit.m_byLayer, m_tTvwStyleInfo.tHduStyleUnit.m_bySlot );
		String strDevice = TVWSTYLELOGICRPTR->GetDeviceByLayorAndSlot(pairLayorSlot);
		if ( 0 != strcmp( m_tTvwStyleInfo.tChanName.m_abyAlias, strDevice.c_str() ) )
		{
			if ( 0 != CUmstoolCommon::GetDeviceName().size() )
			{
				//若当前选中的单板模式名称不存在，则显示下拉列表中第一个数据
				strComboboxTvwStyleOptDeviceName = CUmstoolCommon::GetDeviceName()[0];
			}
		} 
		else
		{
			strComboboxTvwStyleOptDeviceName = m_tTvwStyleInfo.tChanName.m_abyAlias;
			ShowChanNo(m_tTvwStyleInfo.tHduStyleUnit.m_byChanIndex /*+ 1*/);  // +1转为实际通道号
		}
		UIFACTORYMGR_PTR->SetComboText( m_strComboboxTvwStyleOptDeviceName, strComboboxTvwStyleOptDeviceName, m_pWndTree );
	}

	return S_OK;
}

std::pair<s32,s32> CTvwStyleOptDlgLogic::GetLayorAndSlotByDevice(const String& strDeviceName)
{
	std::pair<s32,s32> pairData;

	THduCfg tHduCfg;
	String  strMdlName;
	std::multimap<u8,THduCfg> mulmapHduCfg = DATAMGRPTR->GetUmsTvwBoardData();
	for ( std::multimap<u8,THduCfg>::iterator iter = mulmapHduCfg.begin(); iter != mulmapHduCfg.end(); iter++ )
	{
		tHduCfg = (*iter).second;
		strMdlName = tHduCfg.m_tName.m_abyAlias;
		if ( strMdlName == strDeviceName )
		{
			pairData.first = tHduCfg.m_byLayer;
			pairData.second = tHduCfg.m_bySlot;
		}
	}

	return pairData;
}

BOOL CTvwStyleOptDlgLogic::CheckExistChanInfo( const THduStyleUnit& tStyleUnits )
{
	THduStyleData tHduStyleDataMatrix = TVWSTYLELOGICRPTR->GetStyleDataMatrix();
	for ( s32 nIndex = 0; nIndex < m_tTvwStyleInfo.nCol*m_tTvwStyleInfo.nRow; nIndex++ )
	{	
		if ( tStyleUnits.m_byLayer == tHduStyleDataMatrix.m_atUnits[nIndex].m_byLayer &&
			tStyleUnits.m_bySlot == tHduStyleDataMatrix.m_atUnits[nIndex].m_bySlot &&
			tStyleUnits.m_byChanIndex == tHduStyleDataMatrix.m_atUnits[nIndex].m_byChanIndex )
		{
			return TRUE;
		}
	}
	
	return FALSE;
}

bool CTvwStyleOptDlgLogic::OnChanNameEditChange( const IArgs & arg )
{
	String strComboboxTvwStyleOptDeviceName;
	UIFACTORYMGR_PTR->GetComboText( m_strComboboxTvwStyleOptDeviceName, strComboboxTvwStyleOptDeviceName, m_pWndTree );

	if ( strComboboxTvwStyleOptDeviceName.empty() || "无" == strComboboxTvwStyleOptDeviceName )
	{
		std::vector<CString> vecChanNo;     //清空通道combox数据
		UIFACTORYMGR_PTR->SetComboListData( m_strComboboxTvwStyleOptChanNo, vecChanNo, m_pWndTree );
		return true;
	}

	std::pair<s32,s32> pairData = GetLayorAndSlotByDevice(strComboboxTvwStyleOptDeviceName);
	//显示通道号
	RevertBrdPosToChanNo( pairData.first, pairData.second );	
	
	return true;
}

//经需求确认，所以通道都配置过的名称不再显示  -- 20140521 by xhx
bool CTvwStyleOptDlgLogic::RevertComboboxDeviceName()
{
	std::vector<CString> vecDeviceName = CUmstoolCommon::GetDeviceName();
	vector<CString>::iterator iter = vecDeviceName.begin();

	THduStyleUnit tStyleUnits0;
	tStyleUnits0.m_byChanIndex = 0;
	THduStyleUnit tStyleUnits1;
	tStyleUnits1.m_byChanIndex = 1;
	std::pair<s32,s32> pairData;

	for ( ; iter != vecDeviceName.end(); )
	{
		if ( *iter != m_tTvwStyleInfo.tChanName.m_abyAlias )
		{
			pairData = GetLayorAndSlotByDevice((LPCSTR)(*iter));
			
			tStyleUnits0.m_byLayer = pairData.first;
			tStyleUnits0.m_bySlot = pairData.second;
			
			tStyleUnits1.m_byLayer = pairData.first;
			tStyleUnits1.m_bySlot = pairData.second;
			
			if ( CheckExistChanInfo( tStyleUnits0 ) && CheckExistChanInfo( tStyleUnits1 ) )
			{
				iter = vecDeviceName.erase(iter);
				continue;
			}
		}

		iter++;
	}

	UIFACTORYMGR_PTR->SetComboListData( m_strComboboxTvwStyleOptDeviceName, vecDeviceName, m_pWndTree );

	return true;
}

bool CTvwStyleOptDlgLogic::RevertBrdPosToChanNo( u8 byLayer, u8 bySlot )
{
	char chChanFir[4];
	char chChanSec[4];
	memset( chChanFir, 0, 4 );
	memset( chChanSec, 0, 4 );
//	itoa( byLayer*7*2 + bySlot*2 + 1, chChanFir, 10 );
//	itoa( byLayer*7*2 + bySlot*2 + 2, chChanSec, 10 );
	//经需求确认，通道号均显示0或1 -- 20140603 by xhx
	itoa( 0, chChanFir, 10 );
	itoa( 1, chChanSec, 10 );

	//设置通道号数据
	std::vector<CString> vecChanNo;
//	vecChanNo.push_back(chChanFir);
//	vecChanNo.push_back(chChanSec);

	//经需求确认，配置过的通道号不再显示  -- 20140521 by xhx
	THduStyleUnit tStyleUnits;
	tStyleUnits.m_byLayer = byLayer;
	tStyleUnits.m_bySlot = bySlot;
	
	if ( byLayer == m_tTvwStyleInfo.tHduStyleUnit.m_byLayer && bySlot == m_tTvwStyleInfo.tHduStyleUnit.m_bySlot )
	{
		if ( 0 == m_tTvwStyleInfo.tHduStyleUnit.m_byChanIndex )
		{
			vecChanNo.push_back(chChanFir);

			tStyleUnits.m_byChanIndex = 1;
			if ( !CheckExistChanInfo( tStyleUnits ) )
			{
				vecChanNo.push_back(chChanSec);
			}
		}
		else if ( 1 == m_tTvwStyleInfo.tHduStyleUnit.m_byChanIndex )
		{
			tStyleUnits.m_byChanIndex = 0;
			if ( !CheckExistChanInfo( tStyleUnits ) )
			{
				vecChanNo.push_back(chChanFir);
			}

			vecChanNo.push_back(chChanSec);
		}
	}
	else
	{
		tStyleUnits.m_byChanIndex = 0;
		if ( !CheckExistChanInfo( tStyleUnits ) )
		{
			vecChanNo.push_back(chChanFir);
		}
		
		tStyleUnits.m_byChanIndex = 1;
		if ( !CheckExistChanInfo( tStyleUnits ) )
		{
			vecChanNo.push_back(chChanSec);
		}
	}
	
	UIFACTORYMGR_PTR->SetComboListData( m_strComboboxTvwStyleOptChanNo, vecChanNo, m_pWndTree );
	if ( m_tTvwStyleInfo.tHduStyleUnit.m_byChanIndex != HDU_MAX_CHANNEL_NUM )
	{
		ShowChanNo(m_tTvwStyleInfo.tHduStyleUnit.m_byChanIndex /*+ 1*/);  // +1转为实际通道号
	}

	return true;
}

bool CTvwStyleOptDlgLogic::RevertChanNoToBrdPos()
{
	String strComboboxTvwStyleOptChanNo;
	UIFACTORYMGR_PTR->GetComboText( m_strComboboxTvwStyleOptChanNo, strComboboxTvwStyleOptChanNo, m_pWndTree );
	
	if ( strComboboxTvwStyleOptChanNo.empty() )
	{
		MSG_BOX_OK("通道号不能为空！");
		
		return false;
	}

	String strComboboxTvwStyleOptDeviceName;
	UIFACTORYMGR_PTR->GetComboText( m_strComboboxTvwStyleOptDeviceName, strComboboxTvwStyleOptDeviceName, m_pWndTree );
	
	std::pair<s32,s32> pairData = GetLayorAndSlotByDevice(strComboboxTvwStyleOptDeviceName);

// 	s32 nChanNo = atoi(strComboboxTvwStyleOptChanNo.c_str());
// 	
// 	char chChanNo[3];
// 	memset( chChanNo, 0, 3 );
// 	itoa( nChanNo - pairData.second*2 - pairData.first*7*2, chChanNo, 10 );
// 	strComboboxTvwStyleOptChanNo = chChanNo;

	if ( "0" == strComboboxTvwStyleOptChanNo )
	{
		m_tTvwStyleInfo.tHduStyleUnit.m_byChanIndex = 0;
	}
	else if ( "1" == strComboboxTvwStyleOptChanNo )
	{
		m_tTvwStyleInfo.tHduStyleUnit.m_byChanIndex = 1;
	}

	return true;
}

void CTvwStyleOptDlgLogic::ShowChanNo(u8 byChanNo)
{
	String strComboboxTvwStyleOptDeviceName;
	UIFACTORYMGR_PTR->GetComboText( m_strComboboxTvwStyleOptDeviceName, strComboboxTvwStyleOptDeviceName, m_pWndTree );
	if ( strComboboxTvwStyleOptDeviceName.empty() )
	{
		return;
	}
	
//	std::pair<s32,s32> pairData = GetLayorAndSlotByDevice(strComboboxTvwStyleOptDeviceName);

	char chChanNo[4];
	memset( chChanNo, 0, 4 );
	itoa( /*pairData.first*7*2 + pairData.second*2 + */byChanNo, chChanNo, 10 );
	
	//设置通道号显示
	UIFACTORYMGR_PTR->SetComboText( m_strComboboxTvwStyleOptChanNo, chChanNo, m_pWndTree );
}

