// MsgDispatch.cpp: implementation of the CMsgDispatch class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h" 
#include "Msghandle.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CMsgHandle* CMsgHandle::m_pMySelf = NULL;
map< u32, vector<HWND> > CMsgHandle::m_mapDispatch;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMsgHandle::CMsgHandle()
{
 
}

CMsgHandle::~CMsgHandle()
{

}

BEGIN_MESSAGE_MAP(CMsgHandle, CWnd)
END_MESSAGE_MAP()

void CMsgHandle::Init()
{
    if ( NULL != m_pMySelf )
    {
        return;
    }

    m_pMySelf = new CMsgHandle;

    if ( NULL != m_pMySelf )
    {
        VERIFY( m_pMySelf->CreateEx( 0, AfxRegisterWndClass(CS_DBLCLKS), _T("View"),
		                             WS_OVERLAPPEDWINDOW, CRect(10, 10, 10, 10), NULL, NULL, NULL ) );
    }
}

void CMsgHandle::Destroy()
{
    if ( NULL != m_pMySelf )
    {
        m_pMySelf->DestroyWindow();

        delete m_pMySelf;
        m_pMySelf = NULL;
    }
}

HWND CMsgHandle::GetMsgReceiveHandle()
{
    return m_pMySelf->GetSafeHwnd();
}

void CMsgHandle::RegMsgHandler( u32 nMsgId, HWND hHandleWnd )
{
    map< u32, vector<HWND> >::iterator itr = m_mapDispatch.find( nMsgId );

    vector<HWND> vctTemp;
    if ( m_mapDispatch.end() != itr )
    {
        vctTemp = (vector<HWND>)(itr->second);
    }

    vctTemp.push_back( hHandleWnd );

    m_mapDispatch[nMsgId] = vctTemp;
}


void CMsgHandle::DetachMsgHandler( u32 nMsgId, HWND hHandleWnd )
{
    map< u32, vector<HWND> >::iterator itr = m_mapDispatch.find( nMsgId );

    vector<HWND> vctTemp;
    if ( m_mapDispatch.end() != itr )//找到这条消息
    {
        vctTemp = (vector<HWND>)(itr->second);

		vector<HWND>::iterator iter_Hwnd = vctTemp.begin();

		for( ;  iter_Hwnd < vctTemp.end(); iter_Hwnd++ )
		{
			if( *iter_Hwnd == hHandleWnd )
			{
				vctTemp.erase(iter_Hwnd);
				break;
			}
		}

		m_mapDispatch[nMsgId] = vctTemp;
    }
	

}

BOOL CMsgHandle::PreCreateWindow( CREATESTRUCT& cs )
{
    cs.style &= ~WS_SYSMENU; 
    return CWnd::PreCreateWindow(cs);
}

LRESULT CMsgHandle::DefWindowProc( UINT message, WPARAM wParam, LPARAM lParam )
{
    if ( NULL != m_pMySelf )
    {
        map< u32, vector<HWND> >::iterator itr = m_mapDispatch.find( message );

        // TRACE( "[CMsgDispatch] Receive Msg = %d", message );

        if ( m_mapDispatch.end() != itr )
        {
            vector<HWND> &vctWnd = (vector<HWND>)(itr->second);

            for ( u32 nIndex = 0; nIndex < vctWnd.size(); nIndex++ )
            {
                ::SendMessage( vctWnd[nIndex], message, wParam, lParam );
            }
        }
    }

    return CWnd::DefWindowProc(message, wParam, lParam);
}

LRESULT CMsgHandle::SendMessage( u32 dwMessage, WPARAM wParam, LPARAM lParam )
{   
	if ( NULL == m_pMySelf )
	{
		Init();
	}
 
	return ::SendMessage( m_pMySelf->GetSafeHwnd(), dwMessage, wParam, lParam );
	 
 
}