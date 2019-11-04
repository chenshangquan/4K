// TransparentCalendar.cpp : implementation file
//

#include "stdafx.h"
#include "calendar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CTransparentCalendar
const CString CTransparentCalendar::strBkg = "CalendarBkg.png";
const CString CTransparentCalendar::strMonthBack = "MonthBack";
const CString CTransparentCalendar::strMonthForward = "MonthForward";

CTransparentCalendar::CTransparentCalendar(CString strName, CString strUI, CRect rcWnd, CWnd* pWnd, UINT nID, DWORD dStyle, DWORD dwExStyle) 
: CTransparentBaseWnd( rcWnd, pWnd, dStyle, strUI,nID )
{
    m_pImgBkg = NULL;

	SYSTEMTIME st;
    GetLocalTime(&st);
	m_Day = st.wDay;
	m_Month = st.wMonth;
    m_Year = st.wYear;
	m_bMarkToday = TRUE;
	m_cDateColor = Color( 141, 179, 236 );
	m_cWeekColor = Color( 196, 159, 94 );
	m_cSelColor = Color( 246, 250, 255 );
	m_cEmptyColor = Color( 53, 59, 66 );
	m_cTodayBkColor = Color( 21, 36, 55 );
	m_cSelBkColor = Color( 22, 58, 113 );
	m_cFrameColor = Color( 75, 136, 220 );

	m_pFont = CSrcManage::GetFont( "微软雅黑", 15 );
	m_cStringFormat.SetAlignment( StringAlignmentCenter );
	m_cStringFormat.SetLineAlignment(StringAlignmentCenter);

	
	m_pBtnMonthBack = new CTransparentBtn();
	m_pBtnMonthBack->Create( "MonthBack", WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS, CRect(0,0,0,0), this, 0 );
	
	m_pBtnMonthForward = new CTransparentBtn();
	m_pBtnMonthForward->Create( "MonthForward", WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS, CRect(0,0,0,0), this, 0 );

	m_pStcDate = new CTransparentStatic();
	m_pStcDate->Create( "DateName", WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS, CRect(93,10, 0, 0), this );

}

CTransparentCalendar::~CTransparentCalendar()
{

	//ldy 120821 内存泄露优化
	if ( NULL != m_pBtnMonthBack )
	{
		m_pBtnMonthBack->DestroyWindow();
		delete m_pBtnMonthBack;
		m_pBtnMonthBack = NULL;
	}
	if( NULL != m_pBtnMonthForward )
	{
		m_pBtnMonthForward->DestroyWindow();
		delete m_pBtnMonthForward;
		m_pBtnMonthForward = NULL;
	}
	if( NULL != m_pStcDate )
	{
		m_pStcDate->DestroyWindow();
		delete m_pStcDate;
		m_pStcDate = NULL;
	}
}


BEGIN_MESSAGE_MAP(CTransparentCalendar, CTransparentBaseWnd)
//{{AFX_MSG_MAP(CTransparentCheckButton)
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_MESSAGE( WM_REDRAW_UI, OnRedrawUI )
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransparentCalendar message handlers

LRESULT CTransparentCalendar::OnRedrawUI( WPARAM wParam, LPARAM lParam )
{
	Graphics *pGraphics = (Graphics*)wParam;
    HWND hGraphWnd = (HWND )lParam;
    CWnd * pGraphWnd = FromHandle(hGraphWnd);

	if ( pGraphics == NULL )
	{
		NOTIF_PARENT_WND
		return S_OK;
	}
	
    if ( IsWindowVisible() == FALSE || GetParent() == NULL || m_pImgBkg == NULL || pGraphWnd == NULL )
    {
        return S_FALSE;
    }
	
    CRect cRect;
    GetWindowRect( &cRect );
    POINT point = cRect.TopLeft();
	
    //GetParent()->ScreenToClient( &point );
    pGraphWnd->ScreenToClient( &point );

	if ( NULL != m_pImgBkg && m_pImgBkg->GetWidth() != 0 )
    {
        pGraphics->DrawImage( m_pImgBkg, point.x, point.y , m_pImgBkg->GetWidth(), m_pImgBkg->GetHeight() );
    }
	
    if ( cRect.Width() != m_pImgBkg->GetWidth()
		|| cRect.Height() != m_pImgBkg->GetHeight() )
    {
        SetWindowPos( NULL, 0, 0, m_pImgBkg->GetWidth(), m_pImgBkg->GetHeight(), SWP_NOMOVE|SWP_NOACTIVATE );
    }

	pGraphics->SetTextRenderingHint(TextRenderingHint(TextRenderingHintAntiAlias));

	FillDates();

	DrawBody( pGraphics, point );

	return S_OK;
}


void CTransparentCalendar::DrawBody( Graphics *pGraphics, POINT point )
{	
	
	// Get MyCalendar window rect
// 	RECT clientRect;
// 	GetClientRect( &clientRect );

	CRect cRect;
    GetWindowRect( &cRect );
	
	Color colorText;
	CString strText;

	// Draw date's table
	RectF rectF = RectF( point.x+28, point.y+104, 38, 33 );
	for ( int i=1; i<=42; i++ )
	{

		// If date is selected
		if ( m_Dates[i-1].mcState == SELECTED )
		{
			//DrawEdge( hDC, &rect, EDGE_SUNKEN, BF_RECT | BF_MIDDLE );
			//SetTextColor( hDC, MC_DATE_TXTCOLOR );
			Pen pen( m_cFrameColor, 1 );
			SolidBrush brush( m_cSelBkColor );
			pGraphics->FillRectangle( &brush, rectF.X, rectF.Y, rectF.Width, rectF.Height );
			pGraphics->DrawRectangle( &pen, rectF.X, rectF.Y, rectF.Width, rectF.Height );			
			colorText = m_cSelColor;
		}
		else
		{
			// Draw today marker 
			if ( ( m_Dates[i-1].mcToday == true ) && ( m_Dates[i-1].mcState != EMPTY ) )
			{
				Pen pen( m_cFrameColor, 1 );
				SolidBrush brush( m_cTodayBkColor );
				pGraphics->FillRectangle( &brush, rectF.X, rectF.Y, rectF.Width, rectF.Height );
				pGraphics->DrawRectangle( &pen, rectF.X, rectF.Y, rectF.Width, rectF.Height );				
				colorText = m_cSelColor;
			}
			else
			{
				colorText = m_cDateColor;
			}		
		}
		
		// If date is on Sunday | Saturday 
		if ( ( i % 7 == 1 ) || ( i % 7 == 0 ) )
		{
			if ( m_Dates[i-1].mcState == UNSELECTED )
			{
				colorText = m_cWeekColor;
			}
			else if ( m_Dates[i-1].mcState == SELECTED )
			{
				colorText = m_cWeekColor;
			}
		}
		
		// Draw date value
		if ( m_Dates[i-1].mcState != EMPTY )
		{			
			//itoa( m_Dates[i-1].mcDay, buffer, 10 );
			//TextOut( hDC, (rect.left+rect.right)/2, rect.top+3, buffer, strlen(buffer) );
			SolidBrush brush( colorText );

			strText.Format( "%d", m_Dates[i-1].mcDay );
			BSTR bstr = strText.AllocSysString();
			pGraphics->DrawString( bstr, -1, m_pFont, rectF, &m_cStringFormat, &brush );
			SysFreeString( bstr );
		}
				
		if ( i % 7 == 0 )
		{
			rectF.X = point.x + 28;
			rectF.Y = rectF.Y + 33 + 10;
		}
		else
		{
			rectF.X = rectF.X + 38 + 13;
		}
	}
    
}



void CTransparentCalendar::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CheckCellClick( point );
	NOTIF_PARENT_WND
}


BOOL CTransparentCalendar::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	if ( (HWND)lParam == m_pBtnMonthBack->GetSafeHwnd() )
	{
		if ( m_Month == 1 )
		{
			m_Month = 12;
			m_Year--;
		}
		else
		{
			m_Month--;
		}
		m_strSelDate.Format( "%d年%d月%d日", m_Year, m_Month, m_Day );
		PostMessage( UI_CALENDAR_SELECT_DATE, (WPARAM)&m_strSelDate );
		GetParent()->PostMessage( UI_CALENDAR_SELECT_DATE, (WPARAM)&m_strSelDate );
		NOTIF_PARENT_WND
    }
	else if ( (HWND)lParam == m_pBtnMonthForward->GetSafeHwnd() )
	{
		if ( m_Month == 12 )
		{
			m_Month = 1;
			m_Year++;
		}
		else
		{
			m_Month++;
		}
		m_strSelDate.Format( "%d年%d月%d日", m_Year, m_Month, m_Day );
		PostMessage( UI_CALENDAR_SELECT_DATE, (WPARAM)&m_strSelDate );
		GetParent()->PostMessage( UI_CALENDAR_SELECT_DATE, (WPARAM)&m_strSelDate );
		NOTIF_PARENT_WND
    }
	return CTransparentBaseWnd::OnCommand(wParam, lParam);
}


void CTransparentCalendar::FillDates()
{
	// Get current local time
	SYSTEMTIME st;
	GetLocalTime(&st);
	
	// Calculate day of the week
	int dayOfWeek = CalculateDayOfWeek( 1, m_Month, m_Year, true );
	// Check if current year is leap year
	bool isLeapYear = IsLeapYear( m_Year, true );
	// Get number of days of the current month
	int numberOfDays = GetNumberOfDays( m_Month, m_Year );
	
	int day = 0;
	for ( int i=0; i<42; i++ )
	{
		// Check starting day of the month
		if ( ( i < dayOfWeek ) || ( day >= numberOfDays ) )
			m_Dates[i].mcState = EMPTY;
		else
		{
			day++;
			m_Dates[i].mcDay = day;
			if ( m_Day != day )
				m_Dates[i].mcState = UNSELECTED;
			else
				m_Dates[i].mcState = SELECTED;
		}
		
		// If current day is today
		if ( ( day == st.wDay ) && ( m_Month == st.wMonth ) && ( m_Year == st.wYear ) )
			m_Dates[i].mcToday = true;
		else
			m_Dates[i].mcToday = false;
	}
	
	// Set date window text
	CString strDate;
	strDate.Format( "%d 年 %d 月", m_Year, m_Month );
	m_pStcDate->SetWindowText( strDate );

}


int CTransparentCalendar::CalculateDayOfWeek(int day, int month, int year, BOOL bGregorian)
{
	int result = -1;
    
    // Calculate params
    int a = (int)((14-month) / 12);
    int y = year - a;
    int m = month + 12*a - 2;
    
    // Calculate day of the week
    if ( bGregorian == TRUE )
		result = (int)((day + y + y/4 - y/100 + y/400 + (31*m)/12) % 7);
    else
		result = (int)((5 + day + y + y/4 + (31*m)/12) % 7);
    
    return result;
}

bool CTransparentCalendar::IsLeapYear(int year, BOOL bGregorian)
{
	bool result = false;
	
	// Is year a leap year
	if ( bGregorian == TRUE )
	{
		if ( ( year % 400 == 0 ) || ( ( year % 4 == 0 ) && ( year % 100 != 0 ) ) )
			result = true;
	}
	else
	{
		if ( year % 4 == 0 )
			result = true;
	}
	
	return result;
}


int CTransparentCalendar::GetNumberOfDays(int month, int year)
{
    int result;
    
    // Calculate number of days in the month
    if ( month != 2 )
    {
		// In the first half of the year
		if ( month <= 7 )
		{
			if ( month % 2 == 1 )
				result = 31;
			else
				result = 30;
		}
		// In the second half of the year
		else
		{
			if ( month % 2 == 0 )
				result = 31;
			else
				result = 30;
		}
    }
    else
    {
        // If year is leap year
        if ( IsLeapYear(year, TRUE) )
			result = 29;
        else
			result = 28;
    }
    
    return result;
}


void CTransparentCalendar::CheckCellClick( CPoint pt )
{
	int selected = -1;
	bool bFound = false;
 
	// Get MyCalendar window rect
	RECT clientRect;
	GetClientRect( &clientRect );

	// Clear date's table
	//RECT rect = {clientRect.left+8, clientRect.top+65, clientRect.left+35, clientRect.top+85};
	RECT rect = { 28, 104, 28 + 38, 104 + 33 };

	for ( int i=1; i<=42; i++ )
	{
		if ( m_Dates[i-1].mcState != EMPTY )
		{
			if ( m_Dates[i-1].mcState == SELECTED )
				selected = i-1;
			m_Dates[i-1].mcState = UNSELECTED;
		}
	}
     
	// Check date's table
	for ( i=1; i<=42; i++ )
	{
		if ( m_Dates[i-1].mcState != EMPTY )
		{
			// Check if cell is selected
			if ( ( PtInRect( &rect, pt ) ) && ( m_Dates[i-1].mcDay != 0 ) )
			{
				bFound = true;
				m_Dates[i-1].mcState = SELECTED;
				m_Day = m_Dates[i-1].mcDay;

				// Set date window text
				FillDates();

				m_strSelDate.Format( "%d年%d月%d日", m_Year, m_Month, m_Day );
				// Send notification message
				PostMessage( UI_CALENDAR_SELECT_DATE, (WPARAM)&m_strSelDate );
				GetParent()->PostMessage( UI_CALENDAR_SELECT_DATE, (WPARAM)&m_strSelDate );

				return;
			}

			if ( i % 7 == 0 )
			{
				rect.left = 28;
				rect.right = 28 + 38;
				rect.top = rect.bottom + 10;
				rect.bottom = rect.top + 33;
			}
			else
			{
				rect.left = rect.right + 13;
				rect.right = rect.left + 38;
			}
		}
		else
		{
			rect.left = rect.right + 13;
			rect.right = rect.left + 38;
		}
	}

	if ( ( !bFound ) && ( selected != -1 ) )
	{
		m_Dates[selected].mcState = SELECTED;
		m_Day = m_Dates[selected].mcDay;
	}

}


void CTransparentCalendar::SetSelDate( int nYear, int nMonth, int nDay )
{
	m_Year = nYear;
	m_Month = nMonth;
	m_Day = nDay;
}


void CTransparentCalendar::SetImage( CString strImageFolder, BOOL bInvalidate )
{
	String strFile = strImageFolder + "//" + CTransparentCalendar::strBkg;
	m_pImgBkg = CSrcManage::GetImage( strFile.c_str() );

	CString strFolder = strImageFolder + "//" + CTransparentCalendar::strMonthBack;
	if ( m_pBtnMonthBack != NULL )
	{
		m_pBtnMonthBack->SetImage( strFolder, bInvalidate );
		m_pBtnMonthBack->SetWindowPos( NULL, 50, 3, 38, 43, SWP_SHOWWINDOW|SWP_NOACTIVATE );
	}

	strFolder = strImageFolder + "//" + CTransparentCalendar::strMonthForward;
	if ( m_pBtnMonthForward != NULL )
	{
		m_pBtnMonthForward->SetImage( strFolder, bInvalidate );
		m_pBtnMonthForward->SetWindowPos( NULL, 312, 3, 38, 43, SWP_SHOWWINDOW|SWP_NOACTIVATE );
	}

	if ( m_pStcDate != NULL )
	{
		m_pStcDate->SetWindowPos( NULL, 88, 10, 224, 30, SWP_SHOWWINDOW|SWP_NOACTIVATE );
		m_pStcDate->SetTextColor( Color(217, 234, 255) );
		m_pStcDate->SetTextAlign( StringAlignmentCenter );
		m_pStcDate->SetFont( 15, "微软雅黑" );
	}

	if ( bInvalidate )
	{
		NOTIF_PARENT_WND
	}	
}

void CTransparentCalendar::SetImage( UINT nImgBK,UINT nImgMonthBackNormal, UINT nImgMonthBackPress,UINT nImgMonthForwardNormal, UINT nImgMonthForwardPress, BOOL bInvalidate )
{
	m_pImgBkg = CSrcManage::GetImage( nImgBK, "PNG" );

	if ( m_pBtnMonthBack != NULL )
	{
		m_pBtnMonthBack->SetImage( nImgMonthBackNormal, nImgMonthBackPress, nImgMonthBackNormal, bInvalidate, "PNG" );
		m_pBtnMonthBack->SetWindowPos( NULL, 50, 3, 38, 43, SWP_SHOWWINDOW|SWP_NOACTIVATE );
	}
	
	if ( m_pBtnMonthForward != NULL )
	{
		m_pBtnMonthForward->SetImage( nImgMonthForwardNormal, nImgMonthForwardPress, nImgMonthForwardNormal, bInvalidate, "PNG" );
		m_pBtnMonthForward->SetWindowPos( NULL, 312, 3, 38, 43, SWP_SHOWWINDOW|SWP_NOACTIVATE );
	}
	
	if ( m_pStcDate != NULL )
	{
		m_pStcDate->SetWindowPos( NULL, 88, 10, 224, 30, SWP_SHOWWINDOW|SWP_NOACTIVATE );
		m_pStcDate->SetTextColor( Color(217, 234, 255) );
		m_pStcDate->SetTextAlign( StringAlignmentCenter );
		m_pStcDate->SetFont( 15, "微软雅黑" );
	}
	
	if ( bInvalidate )
	{
		NOTIF_PARENT_WND
	}	
}