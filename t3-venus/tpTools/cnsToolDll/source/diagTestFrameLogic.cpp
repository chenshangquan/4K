// diagTestFrameLogic.cpp: implementation of the DiagTestFrameLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "diagTestFrameLogic.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDiagTestFrameLogic::CDiagTestFrameLogic()
{
	m_vecInPortTitle.push_back("DiagTestInDlg/StcCamera1Info");
	m_vecInPortTitle.push_back("DiagTestInDlg/StcCamera2Info");
	m_vecInPortTitle.push_back("DiagTestInDlg/StcCamera3Info");
}

CDiagTestFrameLogic::~CDiagTestFrameLogic()
{
	m_vecInPortTitle.clear();
}

bool CDiagTestFrameLogic::InitWnd( const IArgs & arg )
{
	CLogicBase::InitWnd( arg );
	UIFACTORYMGR_PTR->ShowWindow( g_strDiagInTestInfo);
    UIFACTORYMGR_PTR->ShowWindow( g_strDiagOutTestInfo, false );
	return true;
}

void CDiagTestFrameLogic::RegMsg()
{
	CDiagTestFrameLogic *pThis =  GetSingletonPtr(); 
	REG_MSG_HANDLER( UI_CNSTOOL_RefInportTitle_Nty, CDiagTestFrameLogic::OnUpdateInportTitle, pThis, CDiagTestFrameLogic ); 
}

void CDiagTestFrameLogic::UnRegMsg()
{
	
}

void CDiagTestFrameLogic::RegCBFun()
{
	CDiagTestFrameLogic *pThis =  GetSingletonPtr();	
    REG_GOBAL_MEMBER_FUNC( "CDiagTestFrameLogic::InitWnd", CDiagTestFrameLogic::InitWnd, pThis, CDiagTestFrameLogic );
	
}

void CDiagTestFrameLogic::UnRegFunc()
{
	UN_REG_GOBAL_FUNC( "CDiagTestInfoLogic::InitWnd" );	
}

void CDiagTestFrameLogic::Clear()
{
	s32 nResult = 0;
	UIFACTORYMGR_PTR->Endmodal(nResult, g_strDiagTestFrame );
}

HRESULT CDiagTestFrameLogic::OnUpdateInportTitle( WPARAM wparam, LPARAM lparam )
{
	TTPVideoInfoTool tMainAudioInfo;
	
	string strInport = "";
	LIBDATAMGRPTR->GetMainAudioInfo( &tMainAudioInfo );
	
	for ( s32 nIndex = 0 ; nIndex < (emEndMPCodec-1) ; nIndex ++ )
	{
		for( s32 nNum = 0; nNum <( emTPC7Vid+1 ) ; nNum ++ )
		{
			if ( tMainAudioInfo.m_aemBigVideoSource[nIndex] == tMainAudioInfo.m_atVideoSourceName[nNum].m_emPortType )
			{
				strInport = tMainAudioInfo.m_atVideoSourceName[nNum].m_achSourceName;
				strInport += "£º";
				UIFACTORYMGR_PTR->SetCaption(m_vecInPortTitle[nIndex],strInport,m_pWndTree);
				break;
			}
		}
	}
	
	return S_OK;
}