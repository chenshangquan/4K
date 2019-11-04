/*****************************************************************************
模块名      : CListUIDragWnd
文件名      : ListUIDragWnd.h
相关文件    : 
文件实现功能: 列表控件拖拽窗口  拖影窗口(WS_POPUP)
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/5/16     1.0         刘德印      创建
******************************************************************************/
#ifndef LISTUIDRAGWND_H
#define LISTUIDRAGWND_H

class UILIB_API CListUIDragWnd : public CWindowWnd
{
public:
	CListUIDragWnd( HWND wndMain,CPaintManagerUI& cPaintManager );

	~CListUIDragWnd();

	LPCTSTR GetWindowClassName() const;

	 /*****************************************************************************
	* 功能:			显示drag窗口
	* @param		[in]	TRUE：显示     FALSE：隐藏
	* @return		空 
	* @remarks		无
	-----------------------------------------------------------------------------
	修改记录:
	日  期         版本        修改人      修改内容
	2013/5/3       1.0         刘德印      创建
    ******************************************************************************/
	void ShowWnd(bool bShow = true);	

	 /*****************************************************************************
	* 功能:			移动drag窗口位置
	* @param		[in]	目标窗口位置POINT
	* @return		空 
	* @remarks		无
	-----------------------------------------------------------------------------
	修改记录:
	日  期         版本        修改人      修改内容
	2013/5/3       1.0         刘德印      创建
    ******************************************************************************/
	void MoveWnd(POINT pt,CListContainerElementUI* pLsElem);

	void SetThisRect(CRect rcThis){m_rcThis = rcThis;};

	CRect GetMainFrameRect();
	void SetListItemHeight( int nListItemHeight );

	void ResetDraw();
	void Draw(CListContainerElementUI* pLsElem);


private:
	RECT m_rcParentRect;
	HWND m_hWndMain;

	int m_nListItemHeight;

	CRect m_rcThis;
	CRect m_rcMainFrame;

	HDC m_hdc;
	HDC m_mdc;
	HBITMAP m_bmpItem;

	CPaintManagerUI m_cPaintManager;
};

#endif // LISTUIDRAGWND_H