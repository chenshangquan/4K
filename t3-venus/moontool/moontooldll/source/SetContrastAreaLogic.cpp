// SetContrastAreaLogic.cpp: implementation of the CSetContrastAreaLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SetContrastAreaLogic.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSetContrastAreaLogic::CSetContrastAreaLogic()
:m_strRectA("SnapShotDlg/BtnRectA")
,m_strRectB("SnapShotDlg/BtnRectB")
,m_strRectC("SnapShotDlg/BtnRectC")
,m_strRectD("SnapShotDlg/BtnRectD")
,m_strRectAWidth("AAreaWidthEdit")
,m_strRectAHeight("AAreaHeightEdit")
,m_strRectBWidth("BAreaWidthEdit")
,m_strRectBHeight("BAreaHeightEdit")
,m_strRectCWidth("CAreaWidthEdit")
,m_strRectCHeight("CAreaHeightEdit")
,m_strRectDWidth("DAreaWidthEdit")
,m_strRectDHeight("DAreaHeightEdit")
,m_strShowRectSwitchBtn("MoonAdjustDlg/ShowRectSwitchBtn")
{
	m_pWnd = NULL;
	m_nTimes = 6;

	m_strRectInfo[0] = m_strRectA;
	m_strRectInfo[1] = m_strRectB;
	m_strRectInfo[2] = m_strRectC;
	m_strRectInfo[3] = m_strRectD;

	m_vecShatShot.push_back("SnapShotDlg/ImageSnapshot1");
	m_vecShatShot.push_back("SnapShotDlg/ImageSnapshot2");
	m_vecShatShot.push_back("SnapShotDlg/ImageSnapshot3");

}

CSetContrastAreaLogic::~CSetContrastAreaLogic()
{
	UnRegMsg();
	UnRegFunc();
}

void CSetContrastAreaLogic::RegMsg()
{
	CSetContrastAreaLogic *pThis = CSetContrastAreaLogic::GetSingletonPtr();

	REG_MSG_HANDLER( UI_SecBoundary_Nty, CSetContrastAreaLogic::OnSecBoundaryNty, pThis, CSetContrastAreaLogic );
	REG_MSG_HANDLER( UI_CHOOSERECTANGLE_IND, CSetContrastAreaLogic::OnChooseRectangleInd, pThis, CSetContrastAreaLogic );
	REG_MSG_HANDLER( UI_MoonTool_ShowRectRegion_IND, CSetContrastAreaLogic::OnShowRectRegionInd, pThis, CSetContrastAreaLogic );
	REG_MSG_HANDLER( UI_MOONTOOL_CAMOUTPUT_INFO_NTY, CSetContrastAreaLogic::OnCamOutputInfoNty, pThis, CSetContrastAreaLogic );
	REG_MSG_HANDLER( UI_MOONTOOL_CAMOUTPUT_INFO_IND, CSetContrastAreaLogic::OnCamOutputInfoInd, pThis, CSetContrastAreaLogic );
	REG_MSG_HANDLER( UI_MoonSecDefault_Nty, CSetContrastAreaLogic::OnSetDefaultParamNty, pThis, CSetContrastAreaLogic );
	REG_MSG_HANDLER( UI_MoonTool_ColorSwitch_IND, CSetContrastAreaLogic::OnSetOnColorSwitchInd, pThis, CSetContrastAreaLogic );

}

void CSetContrastAreaLogic::UnRegMsg()
{
	
}

void CSetContrastAreaLogic::RegCBFun()
{
	REG_GOBAL_MEMBER_FUNC( "CSetContrastAreaLogic::InitWnd", CSetContrastAreaLogic::InitWnd, SETCONTRASTAREALOGIC, CSetContrastAreaLogic);
	REG_GOBAL_MEMBER_FUNC( "CSetContrastAreaLogic::OnBtnClose", CSetContrastAreaLogic::OnBtnClose, SETCONTRASTAREALOGIC, CSetContrastAreaLogic );

	REG_GOBAL_MEMBER_FUNC( "CSetContrastAreaLogic::OnEndDragBtn", CSetContrastAreaLogic::OnEndDragBtn, SETCONTRASTAREALOGIC, CSetContrastAreaLogic );

	REG_GOBAL_MEMBER_FUNC( "CSetContrastAreaLogic::OnShowRectSwitchBtnChange", CSetContrastAreaLogic::OnShowRectSwitchBtnChange, SETCONTRASTAREALOGIC, CSetContrastAreaLogic );
	
	REG_GOBAL_MEMBER_FUNC( "CSetContrastAreaLogic::OnAAreaWidthEditChange", CSetContrastAreaLogic::OnAAreaWidthEditChange, SETCONTRASTAREALOGIC, CSetContrastAreaLogic );
	REG_GOBAL_MEMBER_FUNC( "CSetContrastAreaLogic::OnAAreaWidthEditKillFocus", CSetContrastAreaLogic::OnAAreaWidthEditKillFocus, SETCONTRASTAREALOGIC, CSetContrastAreaLogic );
	REG_GOBAL_MEMBER_FUNC( "CSetContrastAreaLogic::OnAAreaHeightEditChange", CSetContrastAreaLogic::OnAAreaHeightEditChange, SETCONTRASTAREALOGIC, CSetContrastAreaLogic );
	REG_GOBAL_MEMBER_FUNC( "CSetContrastAreaLogic::OnAAreaHeightEditKillFocus", CSetContrastAreaLogic::OnAAreaHeightEditKillFocus, SETCONTRASTAREALOGIC, CSetContrastAreaLogic );

	REG_GOBAL_MEMBER_FUNC( "CSetContrastAreaLogic::OnBAreaWidthEditChange", CSetContrastAreaLogic::OnBAreaWidthEditChange, SETCONTRASTAREALOGIC, CSetContrastAreaLogic );
	REG_GOBAL_MEMBER_FUNC( "CSetContrastAreaLogic::OnBAreaWidthEditKillFocus", CSetContrastAreaLogic::OnBAreaWidthEditKillFocus, SETCONTRASTAREALOGIC, CSetContrastAreaLogic );
	REG_GOBAL_MEMBER_FUNC( "CSetContrastAreaLogic::OnBAreaHeightEditChange", CSetContrastAreaLogic::OnBAreaHeightEditChange, SETCONTRASTAREALOGIC, CSetContrastAreaLogic );
	REG_GOBAL_MEMBER_FUNC( "CSetContrastAreaLogic::OnBAreaHeightEditKillFocus", CSetContrastAreaLogic::OnBAreaHeightEditKillFocus, SETCONTRASTAREALOGIC, CSetContrastAreaLogic );

	REG_GOBAL_MEMBER_FUNC( "CSetContrastAreaLogic::OnCAreaWidthEditChange", CSetContrastAreaLogic::OnCAreaWidthEditChange, SETCONTRASTAREALOGIC, CSetContrastAreaLogic );
	REG_GOBAL_MEMBER_FUNC( "CSetContrastAreaLogic::OnCAreaWidthEditKillFocus", CSetContrastAreaLogic::OnCAreaWidthEditKillFocus, SETCONTRASTAREALOGIC, CSetContrastAreaLogic );
	REG_GOBAL_MEMBER_FUNC( "CSetContrastAreaLogic::OnCAreaHeightEditChange", CSetContrastAreaLogic::OnCAreaHeightEditChange, SETCONTRASTAREALOGIC, CSetContrastAreaLogic );
	REG_GOBAL_MEMBER_FUNC( "CSetContrastAreaLogic::OnCAreaHeightEditKillFocus", CSetContrastAreaLogic::OnCAreaHeightEditKillFocus, SETCONTRASTAREALOGIC, CSetContrastAreaLogic );

	REG_GOBAL_MEMBER_FUNC( "CSetContrastAreaLogic::OnDAreaWidthEditChange", CSetContrastAreaLogic::OnDAreaWidthEditChange, SETCONTRASTAREALOGIC, CSetContrastAreaLogic );
	REG_GOBAL_MEMBER_FUNC( "CSetContrastAreaLogic::OnDAreaWidthEditKillFocus", CSetContrastAreaLogic::OnDAreaWidthEditKillFocus, SETCONTRASTAREALOGIC, CSetContrastAreaLogic );
	REG_GOBAL_MEMBER_FUNC( "CSetContrastAreaLogic::OnDAreaHeightEditChange", CSetContrastAreaLogic::OnDAreaHeightEditChange, SETCONTRASTAREALOGIC, CSetContrastAreaLogic );
	REG_GOBAL_MEMBER_FUNC( "CSetContrastAreaLogic::OnDAreaHeightEditKillFocus", CSetContrastAreaLogic::OnDAreaHeightEditKillFocus, SETCONTRASTAREALOGIC, CSetContrastAreaLogic );

	REG_GOBAL_MEMBER_FUNC( "CSetContrastAreaLogic::OnStartCalcBtnClick", CSetContrastAreaLogic::OnStartCalcBtnClick, SETCONTRASTAREALOGIC, CSetContrastAreaLogic );
}

void CSetContrastAreaLogic::UnRegFunc()
{
	
}

bool CSetContrastAreaLogic::InitWnd(const IArgs & arg)
{
	CLogicBase::InitWnd( arg );

	CDragWindow* p = CDragWindow::GetDragWindow();
	for(int i=0; i<4; i++)
	{
		Window* pBtn = UIFACTORYMGR_PTR->GetWindowPtr(m_strRectInfo[i], m_pWndTree);
		if ( p != NULL && pBtn != NULL )
		{   			
			p->RegisterDropWindow( pBtn );
		}
	}
	
	for(int j=0; j<4; j++)
	{
		CTransparentDragButton *pBtnInfo = (CTransparentDragButton *)UIFACTORYMGR_PTR->GetWindowPtr( m_strRectInfo[j], m_pWndTree );
		if ( pBtnInfo )
		{
			pBtnInfo -> SetUserData( new Data_BtnInfo(j) );
		}
	}
	
	m_pWnd = UIFACTORYMGR_PTR->GetWindowPtr( g_stcStrSetContrastAreaDlg );
	if ( NULL != m_pWnd )
	{
		return false;
	}
	
	return true;
}

void CSetContrastAreaLogic::Clear()
{
	if ( NULL == m_pWndTree )
	{
		return;
	}
	
	UIFACTORYMGR_PTR->ShowWindow( g_stcStrSetContrastAreaDlg, false );
}

bool CSetContrastAreaLogic::OnBtnClose( const IArgs & arg )
{
	UIFACTORYMGR_PTR->ShowWindow( g_stcStrSetContrastAreaDlg, false );
	
	return true;
}

bool CSetContrastAreaLogic::OnEndDragBtn(const IArgs & arg)
{
	if ( m_pWndTree == NULL )
    {
        return true;
    }
	
    Args_WindowMsg WinMsg = *dynamic_cast<const Args_WindowMsg*>(&arg);
    WindowMsg msg = WinMsg.m_Msg;  
	
	s32 x = LOWORD(msg.lParam);
	s32 y = HIWORD(msg.lParam);
	CPoint point(x, y);

	Window *pWnd = UIFACTORYMGR_PTR->GetWindowPtr("SetContrastAreaDlg/SnapShotDlg");
	pWnd->ScreenToClient(&point);

	if(Data_BtnInfo *pData = dynamic_cast<Data_BtnInfo*>( (IData*)msg.wParam ))
	{
		int byRectIndex = pData->m_dwBtnInfo;

		if( 0 == byRectIndex )
		{
			if( ( (int)(point.x - m_tTpMoonRectRegionA.dwLenth/(m_nTimes*2)) < 0) || ( ( point.x + m_tTpMoonRectRegionA.dwLenth/(m_nTimes*2) ) > 320 ) 
				|| ( (int)(point.y - m_tTpMoonRectRegionA.dwWidth/(m_nTimes*2)) < 0 ) || ( ( point.y + m_tTpMoonRectRegionA.dwWidth/(m_nTimes*2) ) > 184) )
			{
// 				u16 nRet = COMIFMGRPTR->SetChooseRectangleCmd( m_tTpMoonRectRegionA );
// 				
// 				if( nRet != NO_ERROR )
// 				{
// 					WARNMESSAGE( "矩形区域设置请求发送失败" );
// 				}
			}
			else
			{
				UIFACTORYMGR_PTR->SetWndPos( point, m_strRectA, m_pWndTree, "" );
				TTPMoonRectRegion tTPMoonRectRegion;
				tTPMoonRectRegion.dwLenth = m_tTpMoonRectRegionA.dwLenth;
				tTPMoonRectRegion.dwWidth = m_tTpMoonRectRegionA.dwWidth;
				tTPMoonRectRegion.dwXCoordinate = (point.x - m_tTpMoonRectRegionA.dwLenth/(m_nTimes*2) - 1 )*m_nTimes;
				tTPMoonRectRegion.dwYCoordinate = (point.y - m_tTpMoonRectRegionA.dwWidth/(m_nTimes*2))*m_nTimes;
				tTPMoonRectRegion.byIndex = byRectIndex;

				u16 nRet = COMIFMGRPTR->SetChooseRectangleCmd( tTPMoonRectRegion );
				if( nRet != NO_ERROR )
				{
					WARNMESSAGE( "矩形区域设置请求发送失败" );
				}
			}
		} 
		else if( 1 == byRectIndex )
		{
			if( ( (int)(point.x - m_tTpMoonRectRegionB.dwLenth/(m_nTimes*2) ) < 323) || ( ( point.x + m_tTpMoonRectRegionB.dwLenth/(m_nTimes*2) ) > 642 )
				|| ( (int)(point.y - m_tTpMoonRectRegionB.dwWidth/(m_nTimes*2)) < 0 ) || ( ( point.y + m_tTpMoonRectRegionB.dwWidth/(m_nTimes*2) ) > 184) )
			{
				// 				u16 nRet = COMIFMGRPTR->SetChooseRectangleCmd( m_tTpMoonRectRegionB );
				// 				
				// 				if( nRet != NO_ERROR )
				// 				{
				// 					WARNMESSAGE( "矩形区域设置请求发送失败" );
				// 				}
			}
			else
			{
				UIFACTORYMGR_PTR->SetWndPos( point, m_strRectB, m_pWndTree, "" );
				TTPMoonRectRegion tTPMoonRectRegion;
				tTPMoonRectRegion.dwLenth = m_tTpMoonRectRegionB.dwLenth;
				tTPMoonRectRegion.dwWidth = m_tTpMoonRectRegionB.dwWidth; 
				tTPMoonRectRegion.dwXCoordinate = (point.x - m_tTpMoonRectRegionB.dwLenth/(m_nTimes*2) - 323 )*m_nTimes;
				tTPMoonRectRegion.dwYCoordinate = (point.y - m_tTpMoonRectRegionB.dwWidth/(m_nTimes*2))*m_nTimes;
				tTPMoonRectRegion.byIndex = byRectIndex;
				
				u16 nRet = COMIFMGRPTR->SetChooseRectangleCmd( tTPMoonRectRegion );
				if( nRet != NO_ERROR )
				{
					WARNMESSAGE( "矩形区域设置请求发送失败" );
				}
			}
		}
		else if( 2 == byRectIndex )
		{
			if( ( (int)(point.x - m_tTpMoonRectRegionC.dwLenth/(m_nTimes*2)) < 323) || ( ( point.x + m_tTpMoonRectRegionC.dwLenth/(m_nTimes*2) ) > 642 )
				|| ((int)(point.y - m_tTpMoonRectRegionC.dwWidth/(m_nTimes*2)) < 0 ) || ( ( point.y + m_tTpMoonRectRegionC.dwWidth/(m_nTimes*2) ) > 184) )
			{
				// 				u16 nRet = COMIFMGRPTR->SetChooseRectangleCmd( m_tTpMoonRectRegionC );
				// 				
				// 				if( nRet != NO_ERROR )
				// 				{
				// 					WARNMESSAGE( "矩形区域设置请求发送失败" );
				// 				}
			}
			else
			{
				UIFACTORYMGR_PTR->SetWndPos( point, m_strRectC, m_pWndTree, "" );
				TTPMoonRectRegion tTPMoonRectRegion;
				tTPMoonRectRegion.dwLenth = m_tTpMoonRectRegionC.dwLenth;
				tTPMoonRectRegion.dwWidth = m_tTpMoonRectRegionC.dwWidth;
				tTPMoonRectRegion.dwXCoordinate = (point.x - m_tTpMoonRectRegionC.dwLenth/(m_nTimes*2) - 323 )*m_nTimes ;
				tTPMoonRectRegion.dwYCoordinate = (point.y - m_tTpMoonRectRegionC.dwWidth/(m_nTimes*2))*m_nTimes;
				tTPMoonRectRegion.byIndex = byRectIndex;
				
				u16 nRet = COMIFMGRPTR->SetChooseRectangleCmd( tTPMoonRectRegion );
				if( nRet != NO_ERROR )
				{
					WARNMESSAGE( "矩形区域设置请求发送失败" );
				}
			}
		}
		else if( 3 == byRectIndex )
		{
			if( ( (int)(point.x - m_tTpMoonRectRegionD.dwLenth/(m_nTimes*2)) < 645) || ( ( point.x + m_tTpMoonRectRegionD.dwLenth/(m_nTimes*2) ) > 969 ) 
				|| ( (int)(point.y - m_tTpMoonRectRegionD.dwWidth/(m_nTimes*2)) < 0 ) || ( ( point.y + m_tTpMoonRectRegionD.dwWidth/(m_nTimes*2) ) > 184) )
			{
				// 				u16 nRet = COMIFMGRPTR->SetChooseRectangleCmd( m_tTpMoonRectRegionA );
				// 				
				// 				if( nRet != NO_ERROR )
				// 				{
				// 					WARNMESSAGE( "矩形区域设置请求发送失败" );
				// 				}
			}
			else
			{
				UIFACTORYMGR_PTR->SetWndPos( point, m_strRectD, m_pWndTree, "" );
				TTPMoonRectRegion tTPMoonRectRegion;
				tTPMoonRectRegion.dwLenth = m_tTpMoonRectRegionD.dwLenth;
				tTPMoonRectRegion.dwWidth = m_tTpMoonRectRegionD.dwWidth;
				tTPMoonRectRegion.dwXCoordinate = (point.x - m_tTpMoonRectRegionD.dwLenth/(m_nTimes*2) - 645 )*m_nTimes;
				tTPMoonRectRegion.dwYCoordinate = (point.y - m_tTpMoonRectRegionD.dwWidth/(m_nTimes*2))*m_nTimes;
				tTPMoonRectRegion.byIndex = byRectIndex;
				
				u16 nRet = COMIFMGRPTR->SetChooseRectangleCmd( tTPMoonRectRegion );
				if( nRet != NO_ERROR )
				{
					WARNMESSAGE( "矩形区域设置请求发送失败" );
				}
			}
		}
		else
		{

		}
	}

	return true;
}

bool CSetContrastAreaLogic::OnShowRectSwitchBtnChange(const IArgs & arg)
{
	
	bool bOpen = false;
	
	UIFACTORYMGR_PTR->GetSwitchState( m_strShowRectSwitchBtn, bOpen, m_pWndTree );
	if ( COMIFMGRPTR->SetShowRectRegionCmd((bOpen==true)?TRUE:FALSE ) != NO_ERROR )
	{
		WARNMESSAGE( "显示矩形区域请求发送失败" );
		UIFACTORYMGR_PTR->SetSwitchState( m_strShowRectSwitchBtn, (( bOpen == true )? false:true ), m_pWndTree );
	}

	return true;	
}

void CSetContrastAreaLogic::SetContrastAreaImage( const string strFileName )
{
	if ( strFileName.find(MOONSNAPSHOT_FILE_NAME1) != string::npos )
	{
		UIFACTORYMGR_PTR->SetTransStaticImage(m_vecShatShot[2],strFileName.c_str(),m_pWndTree);	
	}
	else if ( strFileName.find(MOONSNAPSHOT_FILE_NAME2) != string::npos)
	{
		UIFACTORYMGR_PTR->SetTransStaticImage(m_vecShatShot[1],strFileName.c_str(),m_pWndTree);					
	}
	else if ( strFileName.find(MOONSNAPSHOT_FILE_NAME3) != string::npos )
	{
		UIFACTORYMGR_PTR->SetTransStaticImage(m_vecShatShot[0],strFileName.c_str(),m_pWndTree);					
	}
	else
	{
		return;
	}

	return;
}

bool CSetContrastAreaLogic::OnAAreaWidthEditChange(const IArgs & arg)
{
	UpdateEditNum(arg);
	return true;
}

bool CSetContrastAreaLogic::OnAAreaWidthEditKillFocus(const IArgs & arg)
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strRectAWidth, str, m_pWndTree );
	u32 dwLength = atoi( str.c_str() );

	if( dwLength < 20 )
	{
		dwLength = 20;
	}

	if( dwLength > 1920 )
	{
		dwLength = 1920;
	}

	TTPMoonRectRegion tTPMoonRectRegion;
	tTPMoonRectRegion.byIndex = 0;
	tTPMoonRectRegion.dwWidth = m_tTpMoonRectRegionA.dwWidth ;
	tTPMoonRectRegion.dwXCoordinate = m_tTpMoonRectRegionA.dwXCoordinate;
	tTPMoonRectRegion.dwYCoordinate = m_tTpMoonRectRegionA.dwYCoordinate;
	if( ( m_tTpMoonRectRegionA.dwXCoordinate/m_nTimes + dwLength/m_nTimes ) > 320 )
	{
		tTPMoonRectRegion.dwLenth = ( 320 - m_tTpMoonRectRegionA.dwXCoordinate/m_nTimes ) * m_nTimes;
	}
	else
	{
		tTPMoonRectRegion.dwLenth = dwLength;
	}
		
	u16 nRet = COMIFMGRPTR->SetChooseRectangleCmd( tTPMoonRectRegion );

	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "矩形区域设置请求发送失败" );
	}

	return true;
}

bool CSetContrastAreaLogic::OnAAreaHeightEditChange(const IArgs & arg)
{
	UpdateEditNum(arg);
	return true;
}

bool CSetContrastAreaLogic::OnAAreaHeightEditKillFocus(const IArgs & arg)
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strRectAHeight, str, m_pWndTree );
	u32 dwWidth = atoi(str.c_str());

	if( dwWidth < 20 )
	{
		dwWidth = 20;
	}

	if( dwWidth > 1080 )
	{
		dwWidth = 1080;
	}

	TTPMoonRectRegion tTPMoonRectRegion;
	tTPMoonRectRegion.byIndex = 0;
	tTPMoonRectRegion.dwLenth = m_tTpMoonRectRegionA.dwLenth;
	tTPMoonRectRegion.dwXCoordinate = m_tTpMoonRectRegionA.dwXCoordinate;
	tTPMoonRectRegion.dwYCoordinate = m_tTpMoonRectRegionA.dwYCoordinate;
	if( ( m_tTpMoonRectRegionA.dwYCoordinate/m_nTimes + dwWidth/m_nTimes ) > 180 )
	{
		tTPMoonRectRegion.dwWidth = (180 - m_tTpMoonRectRegionA.dwYCoordinate/m_nTimes) * m_nTimes;
	}
	else
	{
		tTPMoonRectRegion.dwWidth = dwWidth;
	}
	
	u16 nRet = COMIFMGRPTR->SetChooseRectangleCmd( tTPMoonRectRegion );
	
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "矩形区域设置请求发送失败" );
	}

	return true;
}

bool CSetContrastAreaLogic::OnBAreaWidthEditChange(const IArgs & arg)
{
	UpdateEditNum(arg);
	return true;
}

bool CSetContrastAreaLogic::OnBAreaWidthEditKillFocus(const IArgs & arg)
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strRectBWidth, str, m_pWndTree );
	u32 dwLength = atoi( str.c_str() );

	if( dwLength < 20 )
	{
		dwLength = 20;
	}
	
	if( dwLength > 1920 )
	{
		dwLength = 1920;
	}

	TTPMoonRectRegion tTPMoonRectRegion;
	tTPMoonRectRegion.byIndex = 1;
	tTPMoonRectRegion.dwWidth = m_tTpMoonRectRegionB.dwWidth ;
	tTPMoonRectRegion.dwXCoordinate = m_tTpMoonRectRegionB.dwXCoordinate;
	tTPMoonRectRegion.dwYCoordinate = m_tTpMoonRectRegionB.dwYCoordinate;
	if( ( m_tTpMoonRectRegionB.dwXCoordinate/m_nTimes + dwLength/m_nTimes ) > 320 )
	{
		tTPMoonRectRegion.dwLenth = ( 320 - m_tTpMoonRectRegionB.dwXCoordinate/m_nTimes ) * m_nTimes;
	}
	else
	{
		tTPMoonRectRegion.dwLenth = dwLength;
	}
	
	u16 nRet = COMIFMGRPTR->SetChooseRectangleCmd( tTPMoonRectRegion );
	
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "矩形区域设置请求发送失败" );
	}

	return true;
}

bool CSetContrastAreaLogic::OnBAreaHeightEditChange(const IArgs & arg)
{
	UpdateEditNum(arg);
	return true;
}

bool CSetContrastAreaLogic::OnBAreaHeightEditKillFocus(const IArgs & arg)
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strRectBHeight, str, m_pWndTree );
	u32 dwWidth = atoi(str.c_str());

	if( dwWidth < 20 )
	{
		dwWidth = 20;
	}
	
	if( dwWidth > 1080 )
	{
		dwWidth = 1080;
	}

	TTPMoonRectRegion tTPMoonRectRegion;
	tTPMoonRectRegion.byIndex = 1;
	tTPMoonRectRegion.dwLenth = m_tTpMoonRectRegionB.dwLenth;
	tTPMoonRectRegion.dwXCoordinate = m_tTpMoonRectRegionB.dwXCoordinate;
	tTPMoonRectRegion.dwYCoordinate = m_tTpMoonRectRegionB.dwYCoordinate;
	if( ( m_tTpMoonRectRegionB.dwYCoordinate/m_nTimes + dwWidth/m_nTimes ) > 180 )
	{
		tTPMoonRectRegion.dwWidth = (180 - m_tTpMoonRectRegionB.dwYCoordinate/m_nTimes) * m_nTimes;
	}
	else
	{
		tTPMoonRectRegion.dwWidth = dwWidth;
	}
	
	u16 nRet = COMIFMGRPTR->SetChooseRectangleCmd( tTPMoonRectRegion );
	
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "矩形区域设置请求发送失败" );
	}

	return true;
}

bool CSetContrastAreaLogic::OnCAreaWidthEditChange(const IArgs & arg)
{
	UpdateEditNum(arg);
	return true;
}

bool CSetContrastAreaLogic::OnCAreaWidthEditKillFocus(const IArgs & arg)
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strRectCWidth, str, m_pWndTree );
	u32 dwLength = atoi( str.c_str() );

	if( dwLength < 20 )
	{
		dwLength = 20;
	}
	
	if( dwLength > 1920 )
	{
		dwLength = 1920;
	}

	TTPMoonRectRegion tTPMoonRectRegion;
	tTPMoonRectRegion.byIndex = 2;
	tTPMoonRectRegion.dwWidth = m_tTpMoonRectRegionC.dwWidth ;
	tTPMoonRectRegion.dwXCoordinate = m_tTpMoonRectRegionC.dwXCoordinate;
	tTPMoonRectRegion.dwYCoordinate = m_tTpMoonRectRegionC.dwYCoordinate;
	if( ( m_tTpMoonRectRegionC.dwXCoordinate/m_nTimes + dwLength/m_nTimes ) > 320 )
	{
		tTPMoonRectRegion.dwLenth = ( 320 - m_tTpMoonRectRegionC.dwXCoordinate/m_nTimes ) * m_nTimes;
	}
	else
	{
		tTPMoonRectRegion.dwLenth = dwLength;
	}
	
	u16 nRet = COMIFMGRPTR->SetChooseRectangleCmd( tTPMoonRectRegion );
	
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "矩形区域设置请求发送失败" );
	}

	return true;
}

bool CSetContrastAreaLogic::OnCAreaHeightEditChange(const IArgs & arg)
{
	UpdateEditNum(arg);
	return true;
}

bool CSetContrastAreaLogic::OnCAreaHeightEditKillFocus(const IArgs & arg)
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strRectCHeight, str, m_pWndTree );
	u32 dwWidth = atoi(str.c_str());

	if( dwWidth < 20 )
	{
		dwWidth = 20;
	}
	
	if( dwWidth > 1080 )
	{
		dwWidth = 1080;
	}

	TTPMoonRectRegion tTPMoonRectRegion;
	tTPMoonRectRegion.byIndex = 2;
	tTPMoonRectRegion.dwLenth = m_tTpMoonRectRegionC.dwLenth;
	tTPMoonRectRegion.dwXCoordinate = m_tTpMoonRectRegionC.dwXCoordinate;
	tTPMoonRectRegion.dwYCoordinate = m_tTpMoonRectRegionC.dwYCoordinate;
	if( ( m_tTpMoonRectRegionC.dwYCoordinate/m_nTimes + dwWidth/m_nTimes ) > 180 )
	{
		tTPMoonRectRegion.dwWidth = (180 - m_tTpMoonRectRegionC.dwYCoordinate/m_nTimes) * m_nTimes;
	}
	else
	{
		tTPMoonRectRegion.dwWidth = dwWidth;
	}
	
	u16 nRet = COMIFMGRPTR->SetChooseRectangleCmd( tTPMoonRectRegion );
	
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "矩形区域设置请求发送失败" );
	}

	return true;
}

bool CSetContrastAreaLogic::OnDAreaWidthEditChange(const IArgs & arg)
{
	UpdateEditNum(arg);
	return true;
}

bool CSetContrastAreaLogic::OnDAreaWidthEditKillFocus(const IArgs & arg)
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strRectDWidth, str, m_pWndTree );
	u32 dwLength = atoi( str.c_str() );

	if( dwLength < 20 )
	{
		dwLength = 20;
	}
	
	if( dwLength > 1920 )
	{
		dwLength = 1920;
	}

	TTPMoonRectRegion tTPMoonRectRegion;
	tTPMoonRectRegion.byIndex = 3;
	tTPMoonRectRegion.dwWidth = m_tTpMoonRectRegionD.dwWidth ;
	tTPMoonRectRegion.dwXCoordinate = m_tTpMoonRectRegionD.dwXCoordinate;
	tTPMoonRectRegion.dwYCoordinate = m_tTpMoonRectRegionD.dwYCoordinate;
	if( ( m_tTpMoonRectRegionD.dwXCoordinate/m_nTimes + dwLength/m_nTimes ) > 320 )
	{
		tTPMoonRectRegion.dwLenth = ( 320 - m_tTpMoonRectRegionD.dwXCoordinate/m_nTimes ) * m_nTimes;
	}
	else
	{
		tTPMoonRectRegion.dwLenth = dwLength;
	}
	
	u16 nRet = COMIFMGRPTR->SetChooseRectangleCmd( tTPMoonRectRegion );
	
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "矩形区域设置请求发送失败" );
	}

	return true;
}

bool CSetContrastAreaLogic::OnDAreaHeightEditChange(const IArgs & arg)
{
	UpdateEditNum(arg);
	return true;
}

bool CSetContrastAreaLogic::OnDAreaHeightEditKillFocus(const IArgs & arg)
{
	String str;
	UIFACTORYMGR_PTR->GetCaption( m_strRectDHeight, str, m_pWndTree );
	u32 dwWidth = atoi(str.c_str());

	if( dwWidth < 20 )
	{
		dwWidth = 20;
	}
	
	if( dwWidth > 1080 )
	{
		dwWidth = 1080;
	}

	TTPMoonRectRegion tTPMoonRectRegion;
	tTPMoonRectRegion.byIndex = 3;
	tTPMoonRectRegion.dwLenth = m_tTpMoonRectRegionD.dwLenth;
	tTPMoonRectRegion.dwXCoordinate = m_tTpMoonRectRegionD.dwXCoordinate;
	tTPMoonRectRegion.dwYCoordinate = m_tTpMoonRectRegionD.dwYCoordinate;
	if( ( m_tTpMoonRectRegionD.dwYCoordinate/m_nTimes + dwWidth/m_nTimes ) > 180 )
	{
		tTPMoonRectRegion.dwWidth = (180 - m_tTpMoonRectRegionD.dwYCoordinate/m_nTimes) * m_nTimes;
	}
	else
	{
		tTPMoonRectRegion.dwWidth = dwWidth;
	}
	
	u16 nRet = COMIFMGRPTR->SetChooseRectangleCmd( tTPMoonRectRegion );
	
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "矩形区域设置请求发送失败" );
	}

	return true;
}

bool CSetContrastAreaLogic::OnStartCalcBtnClick(const IArgs & arg)
{
	u16 nRet = COMIFMGRPTR->SetAutoSetColorConstancyCmd();
	
	if( nRet != NO_ERROR )
	{
		WARNMESSAGE( "设置对比区域开始计算请求发送失败" );
	}

	return true;
}

HRESULT CSetContrastAreaLogic::OnSecBoundaryNty(WPARAM wparam, LPARAM lparam)
{
	TTPSecBoundaryInfo tTPSecBoundaryInfo = *(TTPSecBoundaryInfo*)(wparam);

	BOOL bShowRectSwich = tTPSecBoundaryInfo.bShowRectSwich;
	UIFACTORYMGR_PTR->SetSwitchState( m_strShowRectSwitchBtn.c_str(), ((bShowRectSwich ==TRUE ) ? true:false) ,m_pWndTree );

	BOOL bColorSwitch = tTPSecBoundaryInfo.bColorSwitch;
	if( bColorSwitch )
	{
		UIFACTORYMGR_PTR->LoadScheme("EnableScheme", m_pWndTree);
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme("DisableScheme", m_pWndTree);
	}

	TTPMoonRectRegion tTPMoonRectRegion1 = tTPSecBoundaryInfo.tRectRegion[0];
	TTPMoonRectRegion tTPMoonRectRegion2 = tTPSecBoundaryInfo.tRectRegion[1];
	TTPMoonRectRegion tTPMoonRectRegion3 = tTPSecBoundaryInfo.tRectRegion[2];
	TTPMoonRectRegion tTPMoonRectRegion4 = tTPSecBoundaryInfo.tRectRegion[3];

	UpdateRectRegionInfo( tTPMoonRectRegion1 );
	UpdateRectRegionInfo( tTPMoonRectRegion2 );
	UpdateRectRegionInfo( tTPMoonRectRegion3 );
	UpdateRectRegionInfo( tTPMoonRectRegion4 );

// 	if( bShowRectSwich )
// 	{
// 		UIFACTORYMGR_PTR->ShowWindow(m_strRectA, true, m_pWndTree);
// 		UIFACTORYMGR_PTR->ShowWindow(m_strRectB, true, m_pWndTree);
// 		UIFACTORYMGR_PTR->ShowWindow(m_strRectC, true, m_pWndTree);
// 		UIFACTORYMGR_PTR->ShowWindow(m_strRectD, true, m_pWndTree);
// 	}
// 	else
// 	{
// 		UIFACTORYMGR_PTR->ShowWindow(m_strRectA, false, m_pWndTree);
// 		UIFACTORYMGR_PTR->ShowWindow(m_strRectB, false, m_pWndTree);
// 		UIFACTORYMGR_PTR->ShowWindow(m_strRectC, false, m_pWndTree);
// 		UIFACTORYMGR_PTR->ShowWindow(m_strRectD, false, m_pWndTree);
// 	}

	return S_OK;
}

HRESULT CSetContrastAreaLogic::OnChooseRectangleInd(WPARAM wparam, LPARAM lparam)
{
	TTPMoonRectRegion tTPMoonRectRegion = *(TTPMoonRectRegion*)(wparam);
	BOOL bSuccess = *(BOOL*)(lparam);
	
	if( !bSuccess )
	{
		WARNMESSAGE("颜色一致性RGB矩形参数设置失败");
	}

	UpdateRectRegionInfo( tTPMoonRectRegion );

	return S_OK;
}

HRESULT CSetContrastAreaLogic::OnShowRectRegionInd(WPARAM wparam, LPARAM lparam)
{
	BOOL bOpen = *(BOOL*)wparam;

	UIFACTORYMGR_PTR->SetSwitchState( m_strShowRectSwitchBtn.c_str(), ((bOpen ==TRUE ) ? true:false) ,m_pWndTree );

// 	if( bOpen )
// 	{
// 		UIFACTORYMGR_PTR->ShowWindow(m_strRectA, true, m_pWndTree);
// 		UIFACTORYMGR_PTR->ShowWindow(m_strRectB, true, m_pWndTree);
// 		UIFACTORYMGR_PTR->ShowWindow(m_strRectC, true, m_pWndTree);
// 		UIFACTORYMGR_PTR->ShowWindow(m_strRectD, true, m_pWndTree);
// 	}
// 	else
// 	{
// 		UIFACTORYMGR_PTR->ShowWindow(m_strRectA, false, m_pWndTree);
// 		UIFACTORYMGR_PTR->ShowWindow(m_strRectB, false, m_pWndTree);
// 		UIFACTORYMGR_PTR->ShowWindow(m_strRectC, false, m_pWndTree);
// 		UIFACTORYMGR_PTR->ShowWindow(m_strRectD, false, m_pWndTree);
// 	}

	return S_OK;
}

HRESULT CSetContrastAreaLogic::OnCamOutputInfoNty(WPARAM wparam, LPARAM lparam)
{
	EmTPMOONOutMode emTPMoonOutMode =  static_cast<EmTPMOONOutMode>(lparam);	
	
	if ( emTPMoonOutMode == em_MoonOutMode_1080P_25fps || emTPMoonOutMode == em_MoonOutMode_1080P_50fps|| emTPMoonOutMode == em_MoonOutMode_1080P_30fps || emTPMoonOutMode == em_MoonOutMode_1080P_60fps  )
	{
		m_nTimes = 6;		
	}
	else if ( emTPMoonOutMode == em_MoonOutMode_720P_60fps || emTPMoonOutMode == em_MoonOutMode_720P_50fps )
	{
		m_nTimes = 4;
	}

	return S_OK;
}

HRESULT CSetContrastAreaLogic::OnCamOutputInfoInd(WPARAM wparam, LPARAM lparam)
{
	EmTPMOONOutMode emTPMoonOutMode =  static_cast<EmTPMOONOutMode>(lparam);	
	
	if ( emTPMoonOutMode == em_MoonOutMode_1080P_25fps || emTPMoonOutMode == em_MoonOutMode_1080P_50fps|| emTPMoonOutMode == em_MoonOutMode_1080P_30fps || emTPMoonOutMode == em_MoonOutMode_1080P_60fps  )
	{
		m_nTimes = 6;		
	}
	else if ( emTPMoonOutMode == em_MoonOutMode_720P_60fps || emTPMoonOutMode == em_MoonOutMode_720P_50fps )
	{
		m_nTimes = 4;
	}
	
	return S_OK;
}

HRESULT CSetContrastAreaLogic::OnSetDefaultParamNty(WPARAM wparam, LPARAM lparam)
{
	TTPSecBoundaryInfo tTPSecBoundaryInfo = *(TTPSecBoundaryInfo*)(wparam);
	BOOL bSuccess = *(BOOL*)(lparam);

	BOOL bShowRectSwich = tTPSecBoundaryInfo.bShowRectSwich;
	UIFACTORYMGR_PTR->SetSwitchState( m_strShowRectSwitchBtn.c_str(), ((bShowRectSwich ==TRUE ) ? true:false) ,m_pWndTree );

	BOOL bColorSwitch = tTPSecBoundaryInfo.bColorSwitch;
	if( bColorSwitch )
	{
		UIFACTORYMGR_PTR->LoadScheme("EnableScheme", m_pWndTree);
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme("DisableScheme", m_pWndTree);
	}

	TTPMoonRectRegion tTPMoonRectRegion1 = tTPSecBoundaryInfo.tRectRegion[0];
	TTPMoonRectRegion tTPMoonRectRegion2 = tTPSecBoundaryInfo.tRectRegion[1];
	TTPMoonRectRegion tTPMoonRectRegion3 = tTPSecBoundaryInfo.tRectRegion[2];
	TTPMoonRectRegion tTPMoonRectRegion4 = tTPSecBoundaryInfo.tRectRegion[3];

	UpdateRectRegionInfo( tTPMoonRectRegion1 );
	UpdateRectRegionInfo( tTPMoonRectRegion2 );
	UpdateRectRegionInfo( tTPMoonRectRegion3 );
	UpdateRectRegionInfo( tTPMoonRectRegion4 );

// 	if( tTPSecBoundaryInfo.bShowRectSwich )
// 	{
// 		UIFACTORYMGR_PTR->ShowWindow(m_strRectA, true, m_pWndTree);
// 		UIFACTORYMGR_PTR->ShowWindow(m_strRectB, true, m_pWndTree);
// 		UIFACTORYMGR_PTR->ShowWindow(m_strRectC, true, m_pWndTree);
// 		UIFACTORYMGR_PTR->ShowWindow(m_strRectD, true, m_pWndTree);
// 	}
// 	else
// 	{
// 		UIFACTORYMGR_PTR->ShowWindow(m_strRectA, false, m_pWndTree);
// 		UIFACTORYMGR_PTR->ShowWindow(m_strRectB, false, m_pWndTree);
// 		UIFACTORYMGR_PTR->ShowWindow(m_strRectC, false, m_pWndTree);
// 		UIFACTORYMGR_PTR->ShowWindow(m_strRectD, false, m_pWndTree);
// 	}
	
	return S_OK;
}

HRESULT CSetContrastAreaLogic::OnSetOnColorSwitchInd(WPARAM wparam, LPARAM lparam)
{
	BOOL bOpen = *(BOOL*)wparam;

	BOOL bSuccess = *(BOOL*)lparam;
	
	if( bSuccess == FALSE )
	{
		return S_FALSE;
	}

	if( bOpen )
	{
		UIFACTORYMGR_PTR->LoadScheme("EnableScheme", m_pWndTree);
	}
	else
	{
		UIFACTORYMGR_PTR->LoadScheme("DisableScheme", m_pWndTree);
	}
	
	return S_OK;
}

void CSetContrastAreaLogic::UpdateEditNum(const IArgs & arg)
{
	Args_WindowMsg* pMsg = dynamic_cast< Args_WindowMsg *>( const_cast<IArgs*>( &arg ));
	UINT nChar = 0;
	if ( NULL !=  pMsg  )
	{
		nChar = pMsg->m_Msg.wParam;
	}

	if ( nChar == 0x0d )
	{
		SetFocus(NULL);
	}
}

void CSetContrastAreaLogic::UpdateRectRegionInfo(TTPMoonRectRegion tTPMoonRectRegion)
{
	u32 dwLength = tTPMoonRectRegion.dwLenth;
	u32 dwWidth = tTPMoonRectRegion.dwWidth;
	u32 nXPos = tTPMoonRectRegion.dwXCoordinate/m_nTimes;
	u32 nYPos = tTPMoonRectRegion.dwYCoordinate/m_nTimes;
	s8 chLength[10] = {0};
	s8 chWidth[10] = {0};
	POINT pt;
	pt.x = nXPos;
	pt.y = nYPos;
	
	sprintf( chLength, "%d", dwLength );
	sprintf( chWidth, "%d", dwWidth );

	if( 0 == tTPMoonRectRegion.byIndex )
	{
		m_tTpMoonRectRegionA = tTPMoonRectRegion;
		UIFACTORYMGR_PTR->SetWndPos( pt, m_strRectA, dwLength/m_nTimes, dwWidth/m_nTimes, m_pWndTree, "" );
		UIFACTORYMGR_PTR->SetCaption( m_strRectAWidth, chLength, m_pWndTree );
		UIFACTORYMGR_PTR->SetCaption( m_strRectAHeight, chWidth, m_pWndTree);		
	}
	else if( 1 == tTPMoonRectRegion.byIndex )
	{
		pt.x = pt.x + 323;
		m_tTpMoonRectRegionB = tTPMoonRectRegion;
		UIFACTORYMGR_PTR->SetWndPos( pt, m_strRectB, dwLength/m_nTimes, dwWidth/m_nTimes, m_pWndTree, "" );
		UIFACTORYMGR_PTR->SetCaption( m_strRectBWidth, chLength, m_pWndTree );
		UIFACTORYMGR_PTR->SetCaption( m_strRectBHeight, chWidth, m_pWndTree );
		
	}
	else if( 2 == tTPMoonRectRegion.byIndex )
	{
		pt.x = pt.x + 323;
		m_tTpMoonRectRegionC = tTPMoonRectRegion;
		UIFACTORYMGR_PTR->SetWndPos( pt, m_strRectC, dwLength/m_nTimes, dwWidth/m_nTimes, m_pWndTree, "" );
		UIFACTORYMGR_PTR->SetCaption( m_strRectCWidth, chLength, m_pWndTree );
		UIFACTORYMGR_PTR->SetCaption( m_strRectCHeight, chWidth, m_pWndTree );
	}
	else
	{
		pt.x = pt.x + 645;
		m_tTpMoonRectRegionD = tTPMoonRectRegion;
		UIFACTORYMGR_PTR->SetWndPos( pt, m_strRectD, dwLength/m_nTimes, dwWidth/m_nTimes, m_pWndTree, "" );
		UIFACTORYMGR_PTR->SetCaption( m_strRectDWidth, chLength, m_pWndTree );
		UIFACTORYMGR_PTR->SetCaption( m_strRectDHeight, chWidth, m_pWndTree );
	}
}