#ifndef __UIRENDER_H__
#define __UIRENDER_H__

#pragma once

namespace DuiLib {
/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CRenderClip
{
public:
    ~CRenderClip();
    RECT rcItem;
    HDC hDC;
    HRGN hRgn;
    HRGN hOldRgn;

    static void GenerateClip(HDC hDC, RECT rc, CRenderClip& clip);
    static void GenerateRoundClip(HDC hDC, RECT rc, RECT rcItem, int width, int height, CRenderClip& clip);
    static void UseOldClipBegin(HDC hDC, CRenderClip& clip);
    static void UseOldClipEnd(HDC hDC, CRenderClip& clip);
};

/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CRenderEngine
{
public:
    static DWORD AdjustColor(DWORD dwColor, short H, short S, short L);

    static TImageInfo* LoadImage( STRINGorID bitmap, LPCTSTR type = NULL, DWORD mask = 0, bool bRelativePath = true );

	//bool xtiled 水平拉伸   bool ytiled 垂直拉伸  默认false为拉伸 by ldy 2013.06.06
    static void DrawImage( HDC hDC, HBITMAP hBitmap, const RECT& rc, const RECT& rcPaint, \
        const RECT& rcBmpPart, const RECT& rcCorners, bool alphaChannel, BYTE uFade = 255, 
        bool hole = false, bool xtiled = false, bool ytiled = false );

	//bool xtiled 水平拉伸   bool ytiled 垂直拉伸  默认false为拉伸 by ldy 2013.06.06
    static bool DrawImageString(HDC hDC, CPaintManagerUI* pManager, const RECT& rcItem, const RECT& rcPaint, 
        LPCTSTR pStrImage, LPCTSTR pStrModify = NULL, bool bTiledX = false, bool bTiledY = false );

	static bool DrawImageGDIPlus( HDC hDC, CPaintManagerUI* pManager, const RECT& rc, const RECT& rcPaint, \
		const TImageInfo* imgInfo, Image* pImg, TEventUI& event, CPoint ptInCtl, RECT rcItem, bool bSuportGesture = false );

	static bool DrawGDIPlus( Graphics& grps, const RECT& rc, const RECT& rcPaint, \
		const TImageInfo* imgInfo, Image* pImg, CPoint ptInCtl, RECT rcItem );

	static bool DrawGestureImage( Graphics& grps, HDC hDC, const RECT& rc, const RECT& rcPaint, \
		const TImageInfo* imgInfo, Image* pImg, TEventUI& event, CPoint ptInCtl, RECT rcItem );

    static void DrawColor( HDC hDC, const RECT& rc, DWORD color );

    static void DrawGradient( HDC hDC, const RECT& rc, DWORD dwFirst, DWORD dwSecond, bool bVertical, int nSteps );

    // 以下函数中的颜色参数alpha值无效
    static void DrawLine( HDC hDC, const RECT& rc, int nSize, DWORD dwPenColor );
    static void DrawRect( HDC hDC, const RECT& rc, int nSize, DWORD dwPenColor );
    static void DrawRoundRect( HDC hDC, const RECT& rc, int width, int height, int nSize, DWORD dwPenColor );
    static void DrawText( HDC hDC, CPaintManagerUI* pManager, RECT& rc, LPCTSTR pstrText, \
        DWORD dwTextColor, int iFont, UINT uStyle );
    static void DrawHtmlText( HDC hDC, CPaintManagerUI* pManager, RECT& rc, LPCTSTR pstrText, 
        DWORD dwTextColor, RECT* pLinks, CStdString* sLinks, int& nLinkRects, UINT uStyle );
    static HBITMAP GenerateBitmap( CPaintManagerUI* pManager, CControlUI* pControl, RECT rc );
};

} // namespace DuiLib

#endif // __UIRENDER_H__
