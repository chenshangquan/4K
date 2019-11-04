/******************************************************************************
模块名      ：CBMPDlg                        
文件名      ：BMPDlg.cpp
相关文件	：UILibHead.h
文件实现功能：实现CBMPDlg类
作者		：朱允荣
版本		：1.0
---------------------------------------------------------------------------------------------------------------------
修改记录:
日  期		版本		修改人		走读人    修改内容
03/24/04    1.0         朱允荣                  创建      
******************************************************************************/

#include "stdafx.h"
#include "UILibHead.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBMPDlg dialog

CBMPDlg::CBMPDlg(UINT uResourceID, CWnd* pParent)
	: CDialog(uResourceID, pParent)
{
	//{{AFX_DATA_INIT(CBkDialogST)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	Init();
}

CBMPDlg::CBMPDlg(CWnd* pParent /*=NULL*/)
{
	//{{AFX_DATA_INIT(CBMPDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CBMPDlg::CBMPDlg(LPCTSTR pszResourceID, CWnd* pParent)
	: CDialog(pszResourceID, pParent)
{
	Init();
}

CBMPDlg::~CBMPDlg()
{
    FreeResources();
}

void CBMPDlg::FreeResources()
{
    if (m_hBitmap != NULL)
    {
        ::DeleteObject(m_hBitmap);
        m_hBitmap = NULL;
    }
    
    if (m_BkDC.m_hDC != NULL) 
    {
        if (m_OldBitmap != NULL)
        {
            ::SelectObject(m_BkDC.m_hDC,m_OldBitmap);
        }
        ::DeleteObject(m_BkDC.m_hDC);
    }
}

void CBMPDlg::Init()
{
    m_hBitmap = NULL;
    m_dwHeight = 0;
    m_dwWidth = 0;
    m_bSizeToContent = FALSE;

    m_crTop =RGB(105,146,214);
    m_crBottom = RGB(34,52,88);
    m_OldBitmap = NULL;
    if (m_BkDC.GetSafeHdc() != NULL)
    {
        m_BkDC.DeleteDC();
    }
}


void CBMPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBMPDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBMPDlg, CDialog)
	//{{AFX_MSG_MAP(CBMPDlg)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBMPDlg message handlers

BOOL CBMPDlg::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	BOOL	bRetValue = CDialog::OnEraseBkgnd(pDC);

    CRect rcDlg;
    GetClientRect(&rcDlg);
    if (m_hBitmap == NULL)
    {
        DrawBk(pDC);
        return bRetValue;
    }


    CDC			dcMemoryDC;
	CBitmap		bmpMemoryBitmap;
	CBitmap*	pbmpOldMemoryBitmap = NULL;

    dcMemoryDC.CreateCompatibleDC(pDC);
	bmpMemoryBitmap.CreateCompatibleBitmap(pDC, rcDlg.Width(), rcDlg.Height());
	pbmpOldMemoryBitmap = (CBitmap*)dcMemoryDC.SelectObject(&bmpMemoryBitmap);

	// Fill background 
	dcMemoryDC.FillSolidRect(rcDlg, pDC->GetBkColor());

	CDC			dcTempDC;
	HBITMAP		hbmpOldTempBitmap = NULL;

	dcTempDC.CreateCompatibleDC(pDC);
	hbmpOldTempBitmap = (HBITMAP)::SelectObject(dcTempDC.m_hDC, m_hBitmap);

    if (m_bSizeToContent)
    {
        dcMemoryDC.BitBlt(0, 0, m_dwWidth, m_dwHeight, &dcTempDC, 0, 0, SRCCOPY);
    }
    else
    {
        dcMemoryDC.StretchBlt(0, 0, rcDlg.Width(), rcDlg.Height(), &dcTempDC, 0, 0, m_dwWidth, m_dwHeight, SRCCOPY);
    }

    pDC->BitBlt(0, 0, rcDlg.Width(), rcDlg.Height(), &dcMemoryDC, 0, 0, SRCCOPY);

	::SelectObject(dcTempDC.m_hDC, hbmpOldTempBitmap);
	dcMemoryDC.SelectObject(pbmpOldMemoryBitmap);
    dcTempDC.DeleteDC();
    dcMemoryDC.DeleteDC();
	return bRetValue;
}

//接口

/*====================================================================
函数名  ：SetBkImage
功  能  ：设置对话框背景图。
全局变量：无
输入参数：nBitmap: 背景图的资源ID号。
返回值  ：无
====================================================================*/
void CBMPDlg::SetBkImage(UINT nBitmap)
{
    HBITMAP		hBitmap			= NULL;
	HINSTANCE	hInstResource	= NULL;
    
    if (nBitmap == 0)
    {
        SetBkImage(hBitmap);
        return;
    }
	// Find correct resource handle
	hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(nBitmap), RT_BITMAP);

	// Load bitmap In
	hBitmap = (HBITMAP)::LoadImage(hInstResource, MAKEINTRESOURCE(nBitmap), IMAGE_BITMAP, 0, 0, 0);

	SetBkImage(hBitmap);
}

/*====================================================================
函数名  ：SetBkImage
功  能  ：设置对话框背景图。
全局变量：无
输入参数：hBitmap: 背景图的句柄。
返回值  ：无
====================================================================*/
void CBMPDlg::SetBkImage(HBITMAP hBitmap)
{
    int		nRetValue;
	BITMAP	csBitmapSize;

	// Free any loaded resource
	FreeResources();

	if (hBitmap)
	{
		m_hBitmap = hBitmap;

		// Get bitmap size
		nRetValue = ::GetObject(hBitmap, sizeof(csBitmapSize), &csBitmapSize);
		if (nRetValue == 0)
		{
			FreeResources();
			return;
		} // if
		m_dwWidth = (DWORD)csBitmapSize.bmWidth;
		m_dwHeight = (DWORD)csBitmapSize.bmHeight;
        if (m_bSizeToContent)
        {
            SizeToContent();
        }
    }
}

/*====================================================================
函数名  ：SizeToContent
功  能  ：改变对话框大小，适应图片。
全局变量：无
输入参数：无
返回值  ：无
====================================================================*/
void CBMPDlg::SizeToContent()
{
    if (m_hBitmap != NULL)
    {
        SetWindowPos(NULL, -1, -1, m_dwWidth, m_dwHeight, 
            SWP_NOMOVE | SWP_NOZORDER | SWP_NOREDRAW | SWP_NOACTIVATE);
    }
    m_bSizeToContent = TRUE;
}

/*====================================================================
函数名  ：SetBkColor
功  能  ：设置对话框的背景色，可以设为渐进色。
全局变量：无
输入参数：crTop:对话框最上端的颜色。
          crBottom:对话框最下端的颜色。
返回值  ：无
====================================================================*/
void CBMPDlg::SetBkColor(COLORREF crTop, COLORREF crBottom, BOOL bRepaint)
{
    m_crTop = crTop;
    m_crBottom = crBottom;

    if (bRepaint)
    {
        Invalidate();
    }
}

void CBMPDlg::DrawBk(CDC *pDC)
{
    CRect rect;
    GetClientRect(rect);

    if (rect.Height() == 0)
    {
        return;
    }
    
    if (m_crBottom == -1 || m_crTop == m_crBottom)
    {
        pDC->FillSolidRect(rect, m_crTop);
        return;
    }

    CUITools::DrawStepBk(pDC, m_crTop, m_crBottom, rect, rect);   
}

