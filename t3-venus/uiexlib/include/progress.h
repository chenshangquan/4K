#ifndef PROGRESS_HEAD_H
#define PROGRESS_HEAD_H





#include "transparenBaseWnd.h"

class CTransparentProgress : public CTransparentBaseWnd
{
	const static CString strBkgLeft;
	const static CString strBkgMid;
	const static CString strBkgRight;

public:
    CTransparentProgress( CString strName = "", CString strUI = "", CRect rcWnd = CRect(0,0,0,0), CWnd* pWnd = 0, UINT nID = 0, 
		DWORD dStyle = 0, DWORD dwExStyle = 0 );
    virtual ~CTransparentProgress();
	
	// Generated message map functions
protected:
    //{{AFX_MSG(CTransparentProgress)
    //}}AFX_MSG
    afx_msg LRESULT OnRedrawUI( WPARAM wParam, LPARAM lParam );
	
	DECLARE_MESSAGE_MAP()

public:
	void SetPos( int nPos );
	int GetPos(){ return m_nPos; }
	void SetImage( CString strFolder, BOOL bInvalidate = FALSE );
	void SetImage( UINT nImgBkgLeftID, UINT nImgBkgMiddleID, UINT nImgBkgRightID,
		UINT nImgHLLeftID, UINT nImgHMiddleID, UINT nImgHRightID, BOOL bInvalidate = FALSE ,const CString& strImgType = "PNG");

private:
	int m_nPos;

	Image   *m_pImgBkgLeft;
    Image   *m_pImgBkgMiddle;
    Image   *m_pImgBkgRight;

	Image   *m_pImgHLLeft;
	Image   *m_pImgHLMiddle;
    Image   *m_pImgHLRight;
};




#endif