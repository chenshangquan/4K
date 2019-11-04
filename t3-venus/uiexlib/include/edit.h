#ifndef EDIT_HEAD_H
#define EDIT_HEAD_H

#include "uiexBaseData.h"

class CTransparentEdit : public CEdit , public TransparentAssist<CTransparentEdit>
{
public:
	enum EmStatus
    {
        emStatusNormal = 0,
			emStatusSetFocus,
    };
	const static CString strNormalLeft;
	const static CString strNormalMid;
	const static CString strNormalRight;
	const static CString strFocusLeft;
	const static CString strFocusMid;
	const static CString strFocusRight;
	const static CString strDisableLeft;
	const static CString strDisableMid;
	const static CString strDisableRight;
	const static CString strNormalIcon;
	const static CString strFocusIcon;
	const static CString strSearch;
    // Construction
public:
    CTransparentEdit();
	CTransparentEdit( CString strImage );
	virtual ~CTransparentEdit();
protected:
	//{{AFX_MSG(CTransparentEdit)
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);  
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnChange();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg LRESULT OnRedrawUI( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnEditSelected( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnEditLeave( WPARAM wParam, LPARAM lParam );
	afx_msg HBRUSH CtlColor(CDC *pDC, UINT nCtlColor);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
public:
	void SetImage( CString strImageFolder, BOOL bInvalidate = FALSE );

	void SetImage( UINT nImgNormalLeftID, UINT nImgNormalMiddleID, UINT nImgNormalRightID, 
		UINT nImgFocusLeftID, UINT nImgFocusMiddleID, UINT nImgFocusRightID, 
		UINT nImgDisableLeftID, UINT nImgDisableMiddleID, UINT nImgDisableRightID,
		UINT nImgIconNormalID, UINT nImgIconFocusID, UINT nImgSearchIconID = 0,
		BOOL bInvalidate = FALSE, const CString& strImgType = "PNG");
	
    void SetTextAlign( StringAlignment, BOOL bInvalidate = FALSE );
	
    void SetTextColor( Color colorNormal, Color colorFocus, BOOL bInvalidate = FALSE );

    void SetDisableColor( Color colorDisable, BOOL bInvalidate = FALSE );
	
	void SetTipColor( Color colorTip, BOOL bInvalidate = FALSE );    
	
	void SetFont( unsigned int dwFontSize = 14, CString strFontFamily = ("微软雅黑"), BOOL bInvalidate = FALSE );

	void SetTipFont( unsigned int dwFontSize = 12, CString strFontFamily = ("微软雅黑"), BOOL bInvalidate = FALSE );
	
	void SetTipStr( CString strTip ){ m_strTip = strTip; }
    CString GetTipStr(){ return m_strTip; } 
 
	void SetStringFormat( StringAlignment strAlign );

	void SetShowIcon( BOOL bShow ){ m_bShowIcon = bShow; } 

	void SetSearchEdit( BOOL bSearch ){ m_bSearchEdit = bSearch; }

	void SetLimitLength( unsigned int dwLength );

	BOOL IsFocus(){ return m_bFocus; }

	void SetIconDeleteText( BOOL bDelete ){ m_bIconDeleteText = bDelete; }

	CSize GetImageSize();

	void SetEditBackLen(int nEditBackLen){ m_nEditBackLen = nEditBackLen; }

	void SetEditFrontLen(int nFrontLen){ m_nEditFrontLen = nFrontLen; }

    void SetDisableImg( BOOL bImg ){ m_bDisableImg = bImg; } 

	void SetVerCenter(BOOL bVerCenter){ m_bVerCenter = bVerCenter; }

protected:
    BOOL  m_bShowCursor;                //是否显示光标
	BOOL  m_bShowIcon;                  //是否显示图标
	BOOL  m_bSearchEdit;                //是否是搜索框
	BOOL  m_bIconDeleteText;            //点击删除图标是否删除内容
    BOOL  m_bDisableImg;                //Disable状态是否显示背景图片
	BOOL  m_bVerCenter;                 //文字是否上下方向居中
	
    EmStatus    m_emStatus;	
	EmStatus    m_emIconStatus;
	
    Image   *m_pImgNormalLeft;
    Image   *m_pImgNormalMiddle;
    Image   *m_pImgNormalRight;
	
    Image   *m_pImgFocusLeft;
    Image   *m_pImgFocusMiddle;
    Image   *m_pImgFocusRight;

	Image   *m_pImgDisableLeft;
	Image   *m_pImgDisableMiddle;
	Image   *m_pImgDisableRight;

	Image   *m_pImgIconNormal;
	Image   *m_pImgIconFocus;
	Image   *m_pImgSearch;
	
    Color   m_cNormalColor;
    Color   m_cFocusColor;
	Color   m_cDisableColor;
	Color	m_cTipColor;
	
	Font* m_pFont;
	Font* m_pTipFont;
	StringFormat	m_cStringFormat;
    CString m_strFontName;         //字体
	
	CString m_strText;
	CString m_strTip;	
	BOOL	m_bFocus;
	BOOL  m_bLBtnDown;
	CRect m_cIconRect;
	int   m_nFirstOffset;
	int   m_nShowIndex;
	int   m_nDownPos;
	int   m_nEditBackLen;
	int   m_nEditFrontLen;

    vector<RectF> m_chractarLst;
private:
	CString GetShowText();
	int     GetShowIndex( CRect& rectEdit, wchar_t* pText ); //计算显示文字的索引
	int		GetSelPos( int nIndex, wchar_t* pText );
	int     GetSelByPos( int nPosX );
	int     GetTextIndex( int nPos, wchar_t* pText );
};








class CTransparentIpEdit : public CTransparentEdit
{
public:
	CTransparentIpEdit();
	
protected:
    //{{AFX_MSG(CTransparentIpEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);	
	afx_msg LRESULT OnRedrawUI( WPARAM wParam, LPARAM lParam );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
public:
	void SetAddress( DWORD dwIp );
	void GetAddress( DWORD& dwIp );
	
	CString GetIpStr( DWORD dwIPAddr);
};


#endif