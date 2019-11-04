#ifndef BASEWND_HEAD_H
#define BASEWND_HEAD_H


#include "uiexBaseData.h"

class CBaseWnd : public CWnd
{
	// Construction
public:
	CBaseWnd( CString strName = "", CRect rcWnd = CRect(0,0,0,0), CWnd* pWnd = NULL, DWORD dStyle = 0, DWORD dwExStyle = 0, UINT nID = 0, CCreateContext* pContext = NULL );
	virtual ~CBaseWnd();
protected:
	BOOL Create( DWORD dwExStyle, CString strName, CRect rcWnd, CWnd* pWnd,DWORD dStyle,UINT nID, CCreateContext* pContext = NULL );
protected:
	void CheckParam( DWORD& dwExStyle, CWnd** pWnd,DWORD& dStyle,UINT& nID );
	//{{AFX_MSG(CBaseWnd)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

 
#endif