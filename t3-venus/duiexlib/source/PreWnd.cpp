#include "stdafx.h"

CPreWnd::CPreWnd(CPaintManagerUI& paint_manager)
: m_cPaintMng(paint_manager)
{
	m_pShowImgLabelUI = NULL;
	m_pScrollContainerUI = NULL;
}

void CPreWnd::SetMainFrameWnd(HWND hWnd)
{ 
	m_hWndMain = hWnd;

	Create( m_hWndMain, _T("CPreWnd"), WS_CHILD, WS_EX_TOOLWINDOW, 0, 0);	//WS_POPUP

	m_pShowImgLabelUI = static_cast<CLabelUI*>(m_cPaintManager.FindControl(_T("showpreviewimg")));
}

void CPreWnd::SetScrollContainerUI(CommonScrollContainerUI* pScrollContainerUI)
{
	m_pScrollContainerUI = pScrollContainerUI;
}

void CPreWnd::ShowPageDown( const tString& strFile )
{
	if ( NULL != m_pScrollContainerUI )
	{
		if ( !CUICommon::IsImgFile( strFile.c_str() ) )
		{
			m_pScrollContainerUI->SetVisible(false);
			this->Draw(strFile);
		}
		else
		{
			this->ShowWindow(SW_HIDE);
			m_pScrollContainerUI->SetVisible(true);

			m_pScrollContainerUI->SetImage(strFile.c_str());
		}
	}
}

LPCTSTR CPreWnd::GetWindowClassName() const 
{ 
	return _T("CPreWnd");
}

void CPreWnd::OnFinalMessage(HWND hWnd)
{
	CBaseWindowWnd::OnFinalMessage(hWnd);
	delete this;
}

LRESULT CPreWnd::OnDestroy( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	g_clsPreview.Unload();

	return CBaseWindowWnd::OnDestroy( uMsg, wParam, lParam, bHandled );
}

void CPreWnd::Notify(TNotifyUI& msg)
{
}

void CPreWnd::Init()
{
	m_cPaintManager.SetTransparent(100);   //设置透明度100%
}

const TCHAR* CPreWnd::GetSkinFile()
{
	return _T("prewnd.xml");
}

void CPreWnd::ShowWnd(bool bShow)
{
	ShowWindow(bShow);
}

void CPreWnd::MoveWnd( POINT pt )
{
	SetWindowPos( m_hWnd, NULL, pt.x, pt.y, 10, 10, SWP_NOSIZE|SWP_SHOWWINDOW );
}

void CPreWnd::Draw(const tString& strFile)
{
	//调用Preview接口显示文件资源
	RECT rc;
	GetClientRect( this->GetHWND(), &rc );     //得到客户区RECT

	if ( !::IsWindowVisible( this->GetHWND() ) )
	{
		this->ShowWindow(SW_SHOW);
	}

	BOOL bImg = CUICommon::IsImgFile( strFile.c_str() );
	if( bImg )   
	{  
		g_clsPreview.Unload();

		ShowImage( strFile );
	}
	else
	{
		ShowImage( strFile, FALSE );

		g_clsPreview.DoPreview( this->GetHWND(), rc, strFile.c_str() );
	}
}

void CPreWnd::ShowImage( const tString& strFile, BOOL bShow )
{
	if ( NULL != m_pShowImgLabelUI )
	{
		m_pShowImgLabelUI->SetImage( strFile.c_str(), true );  //默认preview背景图拉伸    当改变图片显示防止拉伸
	}
}

LRESULT CPreWnd::MessageHandler( UINT uMsg, WPARAM wParam, LPARAM /*lParam*/, bool& /*bHandled*/ )
{
	return FALSE;
}