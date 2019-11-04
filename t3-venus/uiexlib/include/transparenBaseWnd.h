#ifndef TRANSPARENTBASEWND_HEAD_H
#define TRANSPARENTBASEWND_HEAD_H

#include "baseWnd.h"
#include "uiexBaseData.h"
#include "srcManage.h"
class CTransparentBaseWnd : public CBaseWnd
{
	// Construction
public:
	const static CString strLeft;
	const static CString strMid;
	const static CString strRight;
	const static CString strTop;
	const static CString strBottom;
	
	CTransparentBaseWnd(CRect rcWnd, CWnd* pWnd,DWORD dStyle,
		CString strUI,UINT nID, DWORD dwExStyle = 0,int nTrans = 255,BOOL bCanMove = FALSE, BOOL bStretchImage = TRUE ,CString strName = "");

	virtual ~CTransparentBaseWnd();
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransparentBaseWnd)
	protected:
    virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTransparentBaseWnd)
    afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnSize(UINT nType, int cx, int cy) ;
    BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
    //}}AFX_MSG
    afx_msg LRESULT OnRedrawUI( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnBindWnd( WPARAM wParam, LPARAM lParam );
	DECLARE_MESSAGE_MAP()

public:
    void SetAutoHideStatus( BOOL bStatus ){ m_bAutoHide = bStatus; } 
 
    void SetImage( CString strPath, BOOL bInvalidate = FALSE );
	void SetImage( Image* pImage, BOOL bInvalidate = FALSE );
    
    void SetMoveStatus( bool bMove ){ m_bCanMove = bMove; }

    BOOL ShowWindow(int nCmdShow)
    {
        BOOL bRet = CWnd::ShowWindow( nCmdShow );

        if ( SW_SHOW == nCmdShow )
        {
            SendMessage( WM_REDRAW_UI, NULL, NULL );
        }

        return bRet;
    }

    BOOL UpdateData(BOOL bSaveAndValidate = TRUE)
    {
        BOOL bRet = CWnd::UpdateData( bSaveAndValidate );

        if ( FALSE == bSaveAndValidate )
        {
            PostMessage( WM_REDRAW_UI, NULL, NULL );
        }

        return bRet;
    }

protected:
    virtual void RedrawUI();
    virtual void DrawChildWnd( Graphics *pGraphics, HWND hParentWnd );

	void InitMemDC(); 
public:  
    BOOL  m_bTransparentWithoutBK;    // 在无背景图的情况下是否透明显示
    BOOL  m_bRedrawUIImediately;      // 是否立即刷新，用来控制刷新频率的

	virtual int		GetWindowWidth();
	virtual int		GetWindowHeight();
	virtual BYTE	GetSourceConstantAlpha(){ return m_byteSourceConstantAlpha; }
	virtual void	SetSourceConstantAlpha(BYTE byteSCA){ m_byteSourceConstantAlpha = byteSCA; }

    static void AddIgnoreWnd( CWnd* pWnd );
protected:
	static PFN_UpdateLayeredWindow          m_s_pfnUpdateLayeredWindow;
   
    static vector<CWnd*> m_vctIgnoreWnd;   //失去焦点隐藏窗口时 忽略的窗口
    HWND    m_hBindWnd;        //绑定的wnd
    Image   *m_pImageBK;
    BOOL    m_bReadyToRedrawUI; // 避免刷新太频繁，导致效率降低
	BYTE	m_byteSourceConstantAlpha; //透明度 
   
    BOOL m_bCanMove;
    BOOL m_bAutoHide;  //失去焦点自动隐藏

	//如果使用图片文件夹，由三张图拼接 
    Image   *m_pImgLeft;           
    Image   *m_pImgMiddle;
    Image   *m_pImgRight;

	HDC      m_hDcMem;
	HBITMAP  m_hBtMap;

    CString m_strImgPath;
	bool    m_bDeleteImg;  //是否需要清楚图片
};

#endif