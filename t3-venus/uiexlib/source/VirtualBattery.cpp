// VirtualBattery : implementation file
//

#include "stdafx.h"
#include "virtualBattery.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


const CString CVirtualBattery::strImgBattery = "Battery.png";
const CString CVirtualBattery::strImgACLine = "ACLine.png";


CVirtualBattery::CVirtualBattery( CString strName, CString strUI,CRect rcWnd, CWnd* pWnd, UINT nID, DWORD dStyle, DWORD dwExStyle ) 
: CTransparentBaseWnd( rcWnd, pWnd, dStyle, strUI,nID )
{
    m_pImgBattery = NULL;
	m_nBatteryLife = 0;	
}

CVirtualBattery::~CVirtualBattery()
{
}


BEGIN_MESSAGE_MAP(CVirtualBattery, CTransparentBaseWnd)
//{{AFX_MSG_MAP(CVirtualBattery)
ON_MESSAGE( WM_REDRAW_UI, OnRedrawUI )
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVirtualBattery message handlers
LRESULT CVirtualBattery::OnRedrawUI( WPARAM wParam, LPARAM lParam )
{
	Graphics *pGraphics = (Graphics*)wParam;
	HWND hGraphWnd = (HWND)lParam;
	
    if ( IsWindowVisible() == FALSE || pGraphics == NULL || m_pImgBattery == NULL || hGraphWnd == 0 )
    {
        return S_FALSE;
    }
	
    CRect cRect;
    GetWindowRect( &cRect );
    POINT point = cRect.TopLeft();
	
    ::ScreenToClient( hGraphWnd, &point );
    //GetParent()->ScreenToClient( &point );
	
    //m_nBatteryLife=255表示正使用交流电源
    if ( m_nBatteryLife == 255 )
    {
        if ( NULL != m_pImgACLine )
        {
            //充电时填满颜色 内部电量填充自适应
            int nHeight = /*m_pImgACLine->GetHeight()*/cRect.Height() - 5;
            int nAllLength = /*m_pImgACLine->GetWidth()*/cRect.Width() - 12;           
            int nLength = nAllLength;
            
            SolidBrush cBrush( Color(93,192,17) );
            pGraphics->FillRectangle( &cBrush, point.x + 2, point.y + 2, nLength, nHeight );

            pGraphics->DrawImage( m_pImgACLine, point.x, point.y, /*m_pImgACLine->GetWidth(), m_pImgACLine->GetHeight()*/cRect.Width(),cRect.Height() );        
        }
    }
    else
    {
        if ( NULL != m_pImgBattery )
        {
            pGraphics->DrawImage( m_pImgBattery, point.x, point.y, /*m_pImgBattery->GetWidth(), m_pImgBattery->GetHeight()*/cRect.Width(),cRect.Height() );
        }
        
        if ( m_nBatteryLife > 0 )
        {
			//自适应分辨率 使用控件大小
            int nHeight = /*m_pImgBattery->GetHeight()*/cRect.Height() - 5;
            int nAllLength = /*m_pImgBattery->GetWidth()*/cRect.Width() - 12;
            
            int nLength = nAllLength * m_nBatteryLife / 100;
            
            SolidBrush cBrush( Color(93,192,17) );
            pGraphics->FillRectangle( &cBrush, point.x + 2, point.y + 2, nLength, nHeight );
	    }
    }	
	
    return S_OK;  
}

void CVirtualBattery::SetBatteryLife( int nLife )
{
	m_nBatteryLife = nLife;
	NOTIF_PARENT_WND
}

void CVirtualBattery::SetImage( CString strFolder, BOOL bInvalidate )
{
    String strFile = strFolder + "//" + CVirtualBattery::strImgBattery;
    m_pImgBattery = CSrcManage::GetImage( strFile.c_str() );
    strFile = strFolder + "//" + CVirtualBattery::strImgACLine;
    m_pImgACLine = CSrcManage::GetImage( strFile.c_str() );

	if ( bInvalidate )
	{
		NOTIF_PARENT_WND
	}
}