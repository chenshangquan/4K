#ifndef BUTTON_HEAD_H
#define BUTTON_HEAD_H
#include "uiexBaseData.h"


class CTransparentBtn : public CButton, public TransparentAssist<CTransparentBtn>
{
public:
	const static CString strNormalImage;
	const static CString strPressImage;
	const static CString strDisableImage;
	const static CString strOverImage;
	enum EmStatus // 按钮状态
    {
        emStatusNormal = 0,
			emStatusBtnDown,
			emStatusBtnDisable,
			emStatusBtnOver
    };
	
	// Construction
public:
	CTransparentBtn();
	CTransparentBtn( CString strImage );
	// Attributes
public:
	
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransparentBtn)
	//}}AFX_VIRTUAL
protected:
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	// Implementation
public:
	virtual ~CTransparentBtn();
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CTransparentBtn)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point); 
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
    afx_msg void OnEnable(BOOL bEnable);
	//}}AFX_MSG
    afx_msg LRESULT OnRedrawUI( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnMouseLeave( WPARAM wParam, LPARAM lParam );       
	afx_msg LRESULT OnMouseHover( WPARAM wParam, LPARAM lParam );  
    afx_msg LRESULT OnParentHide( WPARAM wParam, LPARAM lParam );
	DECLARE_MESSAGE_MAP()
		
public:
	virtual void OnTouchButtonDown( CPoint pt );

    void    OnTouchButtonUp();
	
    void    SetImage( CString strImageFolder, BOOL bInvalidate = FALSE );
	
	void    SetImage( UINT nImgNormalID, UINT nImgPressID, UINT nImgDisableID, BOOL bInvalidate = FALSE ,const CString& strImgType = "PNG" );
	
    CSize   GetImageSize();
    
	
    BOOL    EnableWindow(BOOL bEnable = TRUE);
	
    void    ShowText( BOOL bShow );   
	
    void    SetTextAlign( StringAlignment emTextAlign, BOOL bInvalidate = FALSE );
	
    void    SetTextPoint( CPoint &cPoint, BOOL bInvalidate = FALSE  );
	
    void	MoveWindow( int x, int y, int nWidth, int nHeight, BOOL bRepaint = TRUE );
	
    void	MoveWindow(LPCRECT lpRect, BOOL bRepaint = TRUE);
	
    void	SetFont( unsigned int dwFontSize = 18 , CString strFontFamily = ("Arial"), BOOL bInvalidate = FALSE );
	
	void	SetOffset( unsigned int wOffset ){ m_wOffset = wOffset; }
	
    void    SetUseTimer( BOOL bUseTimer ){ m_bUseTimer = bUseTimer;};  //add by SXC 20120723

	void    SetUseElapse( unsigned int dwElapse ){ m_dwElapse = dwElapse; };
	
protected:
	void UpdateUI(  BOOL bDrawImmediatly  = FALSE  );
	
	
    Image   *m_pImgNormal;
    Image   *m_pImgPress;
    Image   *m_pImgDisable;
	Image   *m_pImgOver;
	HWND	m_hParentWnd;
	Color			m_coText;
    EmStatus		m_emStatus;
    BOOL			m_bShowText;
    CPoint			m_cPoint;
    Font*			m_pFont;	
	StringFormat	m_cStringFormat;
	unsigned int	m_wOffset;
	BOOL			m_bLButtonDown;
	BOOL			m_bStretch;
	
    UINT            m_nTimer;  //Timer ID
    BOOL            m_bUseTimer; //whether use timer

    BOOL            m_bTouchUp; //WM_TOUCH是否已经UP

	BOOL			m_bImageOver;
    BOOL			m_bMouseTrack;  //是否开启鼠标追踪
	unsigned int    m_dwElapse;     //设置SetTimer()时间间隔

    BOOL            m_bTouchDown; //是否响应了TouchDown
};







class CTransparentCheckButton : public CButton, public TransparentAssist<CTransparentCheckButton>
{
public:
	static const CString strCheckNormal;
	static const CString strCheckPress;
	static const CString strCheckDisable;
	static const CString strCheckOver;
	static const CString strUnCheckNormal;
	static const CString strUnCheckPress;
	static const CString strUnCheckDisable;
	static const CString strUnCheckOver;
    // Construction
public:
    CTransparentCheckButton();
    
    // Attributes
public:
    
    // Operations
public:
    
    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CTransparentCheckButton)
    //}}AFX_VIRTUAL
    
    // Implementation
public:
    virtual ~CTransparentCheckButton();
    
    // Generated message map functions
protected:
    //{{AFX_MSG(CTransparentCheckButton)
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
    //}}AFX_MSG
	afx_msg LRESULT OnMouseHover( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnMouseLeave( WPARAM wParam, LPARAM lParam ); 
    afx_msg LRESULT OnRedrawUI( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnBMSetCheck(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnBindWndHide( WPARAM wParam, LPARAM lParam );
    DECLARE_MESSAGE_MAP()

	void OnTouchButtonDown( CPoint pt );
	void OnTouchButtonUp();
	LRESULT  DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) ;
		
public:
	void    SetShowText( BOOL bShow = FALSE );
	
    void    SetImage( CString strFolder, BOOL bInvalidate = FALSE );

	void    SetImage(  UINT nImgCheckNormal, UINT nImgCheckPress, UINT nImgCheckDiable, UINT nImgUnCheckNormal, UINT nImgUnCheckPress, UINT nImgUnCheckDiable, UINT nImgCheckOver = NULL, UINT nImgUnCheckOver = NULL, BOOL bInvalidate = FALSE );

	void    SetTextColor( Color color ){ m_coText = color; };

	CSize   GetImageSize();
	 
    void    SetBindWnd( HWND hdl );
    HWND    GetBindWnd();
	void	SetFont( unsigned int dwFontSize = 13, CString strFontFamily = "微软雅黑", BOOL bInvalidate = FALSE );
	void	SetFontSpan(int	nFontSpan){ m_nFontSpan = nFontSpan;};	//设置check button字和按钮的间距
	void	SetStatus(int nStatus){ m_emStatus = (EmStatus)nStatus;};//设置button状态
protected:
    HWND    m_hParent;  
    Image   *m_pImgCheckNormal;
    Image   *m_pImgCheckPress;
    Image   *m_pImgCheckDiable;
	Image   *m_pImgCheckOver;
    
    Image   *m_pImgUnCheckNormal;
    Image   *m_pImgUnCheckPress;
    Image   *m_pImgUnCheckDiable;
	Image   *m_pImgUnCheckOver;
    
    enum EmStatus
    {
        emStatusNormal = 0,
            emStatusPress,
			emStatusOver
    };

	Font*			m_pFont;
    EmStatus		m_emStatus;
	BOOL			m_bShowText;
	StringFormat	m_cStringFormat;
	Color			m_coText;

	HWND            m_hBindWnd;
	int				m_nFontSpan;
	BOOL			m_bMouseTrack;  //是否开启鼠标追踪
	BOOL            m_bTouchUp; //WM_TOUCH是否已经UP
// 	UINT            m_nTimer;  //Timer ID
//  BOOL            m_bUseTimer; //whether use timer
// 	BOOL            m_dwElapse;
	CString m_strFontName;
};





class CTransparentSwitchButton : public CButton
{
public:
	static const CString strOnNormal;
	static const CString strOnPress;
	static const CString strOnDisable;
	static const CString strOnOver;
	static const CString strOnSel;

	static const CString strOffNormal;
	static const CString strOffPress;
	static const CString strOffDisable;
	static const CString strOffOver;
	static const CString strOffSel;

    // Construction
public:
    CTransparentSwitchButton();
    virtual ~CTransparentSwitchButton();
    
    // Generated message map functions
protected:
    //{{AFX_MSG(CTransparentSwitchButton)
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
    //}}AFX_MSG
    afx_msg LRESULT OnRedrawUI( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnBindWndHide( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnMouseLeave( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnMouseHover( WPARAM wParam, LPARAM lParam );
    DECLARE_MESSAGE_MAP()

    void OnTouchButtonDown( CPoint pt );
	void OnTouchButtonUp();
    LRESULT  DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) ;
		
public:	
	BOOL    GetSwitchState() { return m_bOn; }
	void    SetSwitchState( BOOL bOn );
    void    SetImage( CString strFolder, BOOL bInvalidate = FALSE );

    //using PNG in RC file -SXC 20120712
    void    SetImage( UINT nImgCheckNormal, UINT nImgCheckPress, UINT nImgCheckDiable,
        UINT nImgUnCheckNormal, UINT nImgUnCheckPress, UINT nImgUnCheckDiable, BOOL bInvalidate = FALSE );
    void    SetBindWnd( HWND hdl );
    HWND    GetBindWnd();

    void    SetShowText( BOOL bShow ){ m_bShowText = bShow; }
	void	SetFont( unsigned int dwFontSize = 13, CString strFontFamily = "微软雅黑", BOOL bInvalidate = FALSE );
protected:
    HWND    m_hBindWnd;   //绑定的dlg
 
    HWND    m_hParent;
	BOOL    m_bTouchUp;   //响应WM_TOUCH时是否已经UP
    Image   *m_pImgOnNormal;
    Image   *m_pImgOnPress;
    Image   *m_pImgOnDiable;
    Image   *m_pImgOnOver;
     
    Image   *m_pImgOffNormal;
    Image   *m_pImgOffPress;
    Image   *m_pImgOffDiable;
    Image   *m_pImgOffOver;
	
    enum EmStatus
    {
        emStatusNormal = 0,
			emStatusPress,
			emStatusOver
    };

    EmStatus		m_emStatus;
	BOOL            m_bOn;
	BOOL            m_bStretch;
    BOOL            m_bShowText;  //是否显示名字
    Color			m_cTextColor;
    Font*			m_pFont;	
    StringFormat	m_cStringFormat;
	BOOL			m_bMouseTrack;  //是否开启鼠标追踪
	CString         m_strFontName;
};



class CTransparentDragButton : public CButton
{
    // Construction
public:
    CTransparentDragButton();
    virtual ~CTransparentDragButton();
    
    // Generated message map functions
protected:
    //{{AFX_MSG(CTransparentDragButton)
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
    //}}AFX_MSG
    afx_msg LRESULT OnRedrawUI( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnBMSetCheck(WPARAM wParam, LPARAM lParam);
    DECLARE_MESSAGE_MAP()
		
		void OnTouchButtonDown( CPoint pt );
    LRESULT  DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) ;
	
public:	
	BOOL    GetSelState();
	void    SetSelState( BOOL bSel );
	void    SetOnline( BOOL bOnline ); 
	void    SetUserData( IData* pData );
	IData*  GetUserData() { return m_pUserData; }
    void    SetImage( CString strFolder, BOOL bInvalidate = FALSE );
protected:	
    HWND    m_hParent;
    Image*  m_pImgOnNormal;
    Image*  m_pImgOnPress;
	Image*  m_pImgOnSel;
	Image*  m_pImgOffNormal;
    Image*  m_pImgOffPress;
	Image*  m_pImgOffSel;
	Image*  m_pImage;
	
	Color			m_colTextOn;
	Color           m_colTextOff;
	Font*			m_pFont;	
	StringFormat	m_cStringFormat;
	
    enum EmStatus
    {
        emStatusNormal = 0,
			emStatusPress,
			emStatusSel,

    };
	
    EmStatus		m_emStatus;
	BOOL            m_bOn;
	BOOL            m_bTimer;
	IData*          m_pUserData;               //拖拽的数据
};



#endif