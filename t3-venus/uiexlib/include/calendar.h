
#ifndef CALENDAR_HEAD_H
#define CALENDAR_HEAD_H

#include "transparenBaseWnd.h"
#include "button.h"
#include "static.h"
/* MyCalendar enums */
enum EMTCState {SELECTED, UNSELECTED, EMPTY};

/*MyDate definition*/
typedef struct tagTCDate
{
	int mcDay;
	int mcState;
	bool mcToday;
}TTCDate;



class CTransparentCalendar : public CTransparentBaseWnd  
{
	// Construction
public:
	const static CString strBkg;
	const static CString strMonthBack;
	const static CString strMonthForward;

	CTransparentCalendar( CString strName = "", CString strUI = "", CRect rcWnd = CRect(0,0,0,0), CWnd* pWnd = 0, UINT nID = 0, 
		DWORD dStyle = 0, DWORD dwExStyle = 0 );
	virtual ~CTransparentCalendar();
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CLetterIndex)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnRedrawUI( WPARAM wParam, LPARAM lParam );
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()

public:
    void SetImage( CString strImageFolder, BOOL bInvalidate = FALSE );
	void SetImage( UINT nImgBK,UINT nImgMonthBackNormal, UINT nImgMonthBackPress,UINT nImgMonthForwardNormal, UINT nImgMonthForwardPress, BOOL bInvalidate = FALSE );
	void SetSelDate( int nYear, int nMonth, int nDay );
	CString GetClickDateString(){ return m_strSelDate; };

protected:
	void DrawBody( Graphics *pGraphics, POINT point );

	void FillDates();

	int CalculateDayOfWeek(int day, int month, int year, BOOL bGregorian);
	bool IsLeapYear(int year, BOOL bGregorian);
	int GetNumberOfDays(int month, int year);

	void CheckCellClick( CPoint point );

protected:
	Image   *m_pImgBkg;
    Image   *m_pImgMonthBackNormal;
	Image   *m_pImgMonthBackPress;

	CTransparentBtn* m_pBtnMonthBack;
	CTransparentBtn* m_pBtnMonthForward;
	CTransparentStatic*  m_pStcDate;

	Color   m_cDateColor;
	Color	m_cWeekColor;
	Color   m_cSelColor;
	Color   m_cEmptyColor;
	Color   m_cTodayBkColor;
	Color   m_cSelBkColor;
	Color   m_cFrameColor;
	
	Font*   m_pFont;
	StringFormat  m_cStringFormat;

	TTCDate m_Dates[42];
	int     m_Day;
	int     m_Month;
    int     m_Year;
	BOOL    m_bMarkToday;
	CString m_strSelDate;
};


#endif