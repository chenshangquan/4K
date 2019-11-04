#ifndef VIRTUALBATTERY_HEAD_H
#define VIRTUALBATTERY_HEAD_H


#include "transparenBaseWnd.h"
//ÐéÄâµç³Ø
class CVirtualBattery : public CTransparentBaseWnd
{
    const static CString strImgBattery;
	const static CString strImgACLine;
public:
    CVirtualBattery( CString strName = "", CString strUI = "", CRect rcWnd = CRect(0,0,0,0), CWnd* pWnd = 0, UINT nID = 0, 
		DWORD dStyle = 0, DWORD dwExStyle = 0 );
    virtual ~CVirtualBattery();

	// Generated message map functions
protected:
    //{{AFX_MSG(CVirtualBattery)
    //}}AFX_MSG
    afx_msg LRESULT OnRedrawUI( WPARAM wParam, LPARAM lParam );
	
	DECLARE_MESSAGE_MAP()
public:
	void SetBatteryLife( int nLife );
	int  GetBatteryLife(){ return m_nBatteryLife; }
	void SetImage( CString strFolder, BOOL bInvalidate = FALSE );

private:
	int    m_nBatteryLife;

	Image *m_pImgBattery; 
    Image *m_pImgACLine;

};


#endif