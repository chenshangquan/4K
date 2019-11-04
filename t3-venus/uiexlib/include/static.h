#ifndef STATIC_HEAD_H
#define STATIC_HEAD_H

#include "uiexBaseData.h"

class CTransparentStatic : public CStatic, public TransparentAssist<CTransparentStatic>
{
	// Construction
public:
	CTransparentStatic();
	virtual ~CTransparentStatic();
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CTransparentStatic)
	afx_msg LRESULT OnRedrawUI( WPARAM wParam, LPARAM lParam );
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
public:
    void SetImage( CString strImage, BOOL bInvalidate = TRUE );
	
	void SetImage( UINT nImgID ,const CString& strImgType = "PNG" );
	
	void SetMosaicHoriImage( UINT nImgLeft, UINT nImgMid, UINT nImgRight, const CString& strImgType = "PNG" );
	
	CSize GetImageSize();
	
    void SetWindowText( CString strWindowText, BOOL bInvalidate = FALSE );
	
    void SetTextColor( Color coNormal, BOOL bInvalidate = FALSE );
	
	void SetDisableColor( Color coDisable, BOOL bInvalidate = FALSE );
	
    void SetTextAlign( StringAlignment emTextAlign, BOOL bInvalidate = FALSE );
	
	void SetFont( unsigned int dwFontSize = 12, CString strFontFamily = _T("Î¢ÈíÑÅºÚ"), FontStyle emStyle = FontStyleRegular, BOOL bInvalidate = FALSE );
	
	Color GetTextColor() { return m_cNormalColor; }
	
	Font* GetFont() { return m_pFont; }
	
	void CheckTextLength( CString& strText, CRect cRect );
	
protected:
    Image   *m_pImgBk;
	Font*	m_pFont;
	Color   m_cNormalColor;
	Color	m_cDisableColor;
	StringFormat m_cStringFormat;
	BOOL    m_MosaicHoriImage;
    CString m_strFontName;
};

#endif
