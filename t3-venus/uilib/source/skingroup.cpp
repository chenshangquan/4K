/********************************************************************
	模块名:      UILib
	文件名:      skingroup.cpp
	相关文件:    UILibHead.h
	文件实现功能 
    作者：       朱允荣
	版本：       1.0
------------------------------------------------------------------------
	修改记录:
	日  期		版本		修改人		走读人    修改内容
	2004/07/30	1.0			朱允荣                  创建

*********************************************************************/

#include "stdafx.h"
#include "UILibHead.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkinGroup
COLORREF CSkinGroup::m_s_crText[2] = { RGB(80, 114, 170), RGB(172, 172, 172)};
COLORREF CSkinGroup::m_s_crLine[2] = { RGB(80, 114, 170), RGB(172, 172, 172)};
CSkinGroup::CSkinGroup()
{
    m_crText[0] = m_s_crText[0];
    m_crText[1] = m_s_crText[1];
    m_crLine[0] = m_s_crLine[0];
    m_crLine[1] = m_s_crLine[1];

    m_penLine[0].CreatePen(PS_SOLID , 1, m_crLine[0]);
    m_penLine[1].CreatePen(PS_SOLID , 1, m_crLine[1]);

    m_nLMetric = 7;
}
CSkinGroup::~CSkinGroup()
{
    m_penLine[0].DeleteObject();
    m_penLine[1].DeleteObject();
}


BEGIN_MESSAGE_MAP(CSkinGroup, CButton)
	//{{AFX_MSG_MAP(CSkinGroup)
	ON_WM_PAINT()
	ON_WM_ENABLE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkinGroup message handlers

void CSkinGroup::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	dc.SelectObject(GetFont());
	// Do not call CButton::OnPaint() for painting messages
    CString strText;
    CRect rect;
    
    GetClientRect(rect);
    GetWindowText(strText);
    if (m_strTitle != strText)
    {
        m_strTitle = strText;
        CWnd* pParent = GetParent();
        if (pParent != NULL)
        {
            CRect rect;
            GetClientRect(rect);

            MapWindowPoints(pParent, rect);
            pParent->InvalidateRect(rect);
        }
        return;
    }

    int nIndex = IsWindowEnabled()? 0:1;

    //没有标题，直接画个方框，结束。   [zhuyr][7/30/2004]
    if (strText.IsEmpty()) 
    {
        dc.FrameRect(rect, &CBrush(m_crLine[nIndex]));
        return;
    }

    CSize size = dc.GetTextExtent(strText);
    rect.left += m_nLMetric;
    
    dc.SetBkMode(TRANSPARENT);

    CPen* pOld;
    dc.SetTextColor(m_crText[nIndex]);

    dc.DrawText(strText, rect, DT_LEFT|DT_SINGLELINE|DT_TOP);

    pOld = dc.SelectObject(&m_penLine[nIndex]);

    rect.top += size.cy / 2;
    dc.MoveTo(rect.left - 2, rect.top);
    dc.LineTo(rect.left - m_nLMetric, rect.top);
    //  wanghao 2006/12/26 HIDE之后，边框残留
//    dc.LineTo(rect.left - m_nLMetric, rect.bottom);
//    dc.LineTo(rect.right, rect.bottom);
//    dc.LineTo(rect.right, rect.top);
    dc.LineTo( rect.left - m_nLMetric, rect.bottom - 1 );
    dc.LineTo( rect.right - 1, rect.bottom - 1 );
    dc.LineTo( rect.right - 1, rect.top );
    dc.LineTo(rect.left + size.cx + 2, rect.top);

    dc.SelectObject(pOld);    
}

void CSkinGroup::OnEnable(BOOL bEnable) 
{
	CButton::OnEnable(bEnable);
	
	// TODO: Add your message handler code here
	CWnd* pParent = GetParent();
    if (pParent != NULL)
    {
        CRect rect;
        GetClientRect(rect);

        MapWindowPoints(pParent, rect);
        pParent->InvalidateRect(rect);
    }
}

/*====================================================================
函数名	：    SetGroupColor
功能		：设置控件颜色
算法实现	：（可选项）
引用全局变量：无
输入参数说明：crNormal: 正常时显示的颜色, -1时保持原来的颜色。
              crDisable:失效时显示的颜色, -1时保持原来的颜色。
              bRepaint:是否马上重画控件。
返回值说明：  无
----------------------------------------------------------------------
修改记录:
日  期		版本		修改人		走读人    修改内容
2004/07/30	1.0			朱允荣                  创建
====================================================================*/
void CSkinGroup::SetGroupColor(COLORREF crNormal, COLORREF crDisable,
                               BOOL bRepaint, int nType)
{
    if (-1 != crNormal)
    {
         if (nType & COLTYPE_TEXT)
         {
            m_crText[0] = crNormal;
         }

         if (nType & COLTYPE_LINE)
         {
            m_crLine[0] = crNormal;
            m_penLine[0].DeleteObject();
            m_penLine[0].CreatePen(PS_SOLID , 1, m_crLine[0]);
         }
    }
    
    if (-1 != crDisable)
    {
         if (nType & COLTYPE_TEXT)
         {
            m_crText[1] = crNormal;
         }

         if (nType & COLTYPE_LINE)
         {
            m_crLine[1] = crNormal;
            m_penLine[1].DeleteObject();
            m_penLine[1].CreatePen(PS_SOLID , 1, m_crLine[1]);
         }
    }

    if (bRepaint) 
    {
        Invalidate();
    }
}

/*====================================================================
函数名	：    SetLMetric
功能		：设置文字到左边框的距离
算法实现	：（可选项）
引用全局变量：无
输入参数说明：nMetric：距离
返回值说明：  无
----------------------------------------------------------------------
修改记录:
日  期		版本		修改人		走读人    修改内容
2004/07/30	1.0			朱允荣                  创建
====================================================================*/
void CSkinGroup::SetLMetric(UINT nMetric)
{
    m_nLMetric = nMetric;
}

void CSkinGroup::staticSetGroupColor(COLORREF crNormal, COLORREF crDisable, int nType)
{
    if (nType & COLTYPE_TEXT)
    {
        m_s_crText[0] = crNormal;
        m_s_crText[1] = crDisable;
    }

    if (nType & COLTYPE_LINE)
    {
        m_s_crLine[0] = crNormal;
        m_s_crLine[1] = crDisable;
    }
}

/*=============================================================================
函 数 名:SetWindowText
功    能:设置标题文字
参    数:LPCTSTR lpszString         [in]    标题文字
注    意:专门用于处理重影问题
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2006/12/26  4.0     王昊    创建
=============================================================================*/
void CSkinGroup::SetWindowText(LPCTSTR lpszString)
{
    CWnd::SetWindowText( lpszString );
    if ( IsWindowVisible() )
    {
        ShowWindow( SW_HIDE );
        ShowWindow( SW_SHOW );
    }
    return;
}

/*=============================================================================
函 数 名:DefWindowProc
功    能:过滤按tab键在vista和xp_sp3系统上的重影的消息：WM_UPDATEUISTATE 0x0128
参    数:
注    意:
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2009/03/26  4.0     陈建辉    创建
=============================================================================*/
LRESULT CSkinGroup::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    switch( message )
    {
    case 0x0128:
    	return S_OK;
    default:
        break;
    }
    return CWnd::DefWindowProc( message, wParam, lParam );
}
