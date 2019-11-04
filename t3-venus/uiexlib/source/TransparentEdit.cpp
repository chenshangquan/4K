// TransparentEdit.cpp : implementation file
//

#include "stdafx.h"
#include "edit.h" 
#include "srcManage.h"
#include <WinSock.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define EDIT_FRONT_LENGTH   19   //Edit前端开始写字的长度

/////////////////////////////////////////////////////////////////////////////
// CTransparentEdit

const CString CTransparentEdit::strNormalLeft = "NormalLeft.png";
const CString CTransparentEdit::strNormalMid = "NormalMid.png";
const CString CTransparentEdit::strNormalRight = "NormalRight.png";
const CString CTransparentEdit::strFocusLeft = "FocusLeft.png";
const CString CTransparentEdit::strFocusMid = "FocusMid.png";
const CString CTransparentEdit::strFocusRight = "FocusRight.png";
const CString CTransparentEdit::strDisableLeft = "DisableLeft.png";
const CString CTransparentEdit::strDisableMid = "DisableMid.png";
const CString CTransparentEdit::strDisableRight = "DisableRight.png";
const CString CTransparentEdit::strNormalIcon = "NormalIcon.png";
const CString CTransparentEdit::strFocusIcon = "FocusIcon.png";
const CString CTransparentEdit::strSearch = "Search.png";
template<> WNDPROC TransparentAssist<CTransparentEdit>::m_pWndProc = NULL;
CTransparentEdit::CTransparentEdit()
{
	RegsiterWndProc();
	m_emStatus = emStatusNormal;
	m_emIconStatus = emStatusNormal;
   	
    m_pImgNormalLeft = NULL;
    m_pImgNormalMiddle = NULL;
    m_pImgNormalRight = NULL;
    m_pImgFocusLeft = NULL;
    m_pImgFocusMiddle = NULL;
    m_pImgFocusRight = NULL;
	m_pImgDisableLeft = NULL;
	m_pImgDisableMiddle = NULL;
	m_pImgDisableRight = NULL;
	m_pImgIconNormal = NULL;
	m_pImgIconFocus = NULL;
	m_pImgSearch = NULL;
	
    m_cNormalColor	= Color( 66, 71, 76 );
    m_cFocusColor	= Color( 0, 0, 0 );
	m_cDisableColor = Color( 194, 197, 206 );
	m_cTipColor		= Color( 184, 190, 200 );
	
	m_pFont = CSrcManage::GetFont( "微软雅黑", 12 );
	m_pTipFont = CSrcManage::GetFont( "微软雅黑", 12 );
	m_cStringFormat.SetAlignment( StringAlignmentNear );
	m_cStringFormat.SetLineAlignment(StringAlignmentCenter);
	m_cStringFormat.SetFormatFlags( StringFormatFlagsNoWrap | StringFormatFlagsMeasureTrailingSpaces );
	m_strTip = _T("");	
	m_bFocus = FALSE;
    m_bShowCursor = FALSE;
	m_bLBtnDown = FALSE;
	m_bShowIcon = TRUE;
	m_bSearchEdit = FALSE;
	m_bIconDeleteText = TRUE;
    m_bDisableImg = TRUE;
	m_nFirstOffset = 0;
	m_nShowIndex = 0;
	m_nDownPos = 0;
	m_nEditBackLen = 17;
	m_nEditFrontLen = EDIT_FRONT_LENGTH;
	m_cIconRect = CRect(-1,-1,-1,-1);			//右边删除按钮图片的默认区域-----JYY
	m_bVerCenter = FALSE;
}

CTransparentEdit::CTransparentEdit( CString strImage )
{
	m_emStatus = emStatusNormal;	
    m_cNormalColor	= Color( 255, 255, 255 );
    m_cFocusColor	= Color( 255, 255, 255 );
	m_cTipColor		= Color( 157, 168, 174 );
	
	m_pFont = CSrcManage::GetFont( "Arial", 18 );
	m_pTipFont = CSrcManage::GetFont( "微软雅黑", 12 );
	m_cStringFormat.SetAlignment( StringAlignmentFar );
	m_cStringFormat.SetFormatFlags( StringFormatFlagsNoWrap | StringFormatFlagsMeasureTrailingSpaces );
	m_strTip = _T("");	
	m_bFocus = FALSE;
    m_bShowCursor = FALSE;
	m_bLBtnDown = FALSE;

	m_nEditFrontLen = EDIT_FRONT_LENGTH;

	SetImage( strImage );
}

CTransparentEdit::~CTransparentEdit()
{

}


BEGIN_MESSAGE_MAP(CTransparentEdit, CEdit)
	//{{AFX_MSG_MAP(CTransparentEdit)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_SHOWWINDOW()
	ON_WM_CHAR()
	ON_WM_LBUTTONDOWN()	
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_SETCURSOR()
	ON_CONTROL_REFLECT(EN_CHANGE, OnChange)
	ON_WM_CTLCOLOR_REFLECT()
	ON_MESSAGE( WM_REDRAW_UI, OnRedrawUI )
	ON_MESSAGE( WM_EDIT_SELECTED, OnEditSelected )
	ON_MESSAGE( WM_EDIT_LEAVE, OnEditLeave )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransparentEdit message handlers

int CTransparentEdit::GetShowIndex( CRect& rectEdit, wchar_t* pText )
{
	if ( NULL == pText)
	{
		return 0;
	}

	DWORD dwAllTextLen = wcslen( pText );
	DWORD dwIndex = 0;
	
	Graphics graphics(m_hWnd);			

	RectF rectString;
	float fMaxWidth = (float)( rectEdit.Width() - /*rectEdit.Width()/22*//*EDIT_FRONT_LENGTH*/m_nEditFrontLen - m_nEditBackLen );

	if ( m_bShowIcon && m_pImgIconNormal != NULL )
	{
		fMaxWidth = fMaxWidth - m_pImgIconNormal->GetWidth();
	}
	if ( m_bSearchEdit && m_pImgSearch != NULL )
	{
		fMaxWidth = fMaxWidth - m_pImgSearch->GetWidth();
	}

	int nStartSel, nEndSel;
	GetSel( nStartSel, nEndSel );
	if ( nStartSel == nEndSel )
	{
		m_nDownPos = nStartSel;
	}
	//DWORD dwPos = GetSel() & 0xFFFF;
	int nTextIndex = GetTextIndex( nStartSel, pText ); 
	int nTextIndex2 = GetTextIndex( nEndSel, pText ); 

	graphics.MeasureString( pText, dwAllTextLen , m_pFont, RectF(0,0,0,0), &m_cStringFormat, &rectString );
	if ( rectString.Width <= fMaxWidth )
	{
		return 0;
	}	

	int nEndIndex = 0;
	for ( int i = 0; i <= dwAllTextLen - m_nShowIndex; i++ )
	{
		graphics.MeasureString( pText + m_nShowIndex, i, m_pFont, RectF(0,0,0,0), &m_cStringFormat, &rectString );
		{
			if ( rectString.Width >= fMaxWidth )
			{
				nEndIndex = m_nShowIndex + i;
				break;
			}
		}
	}

	if ( nTextIndex == nTextIndex2 )
	{
		if ( nTextIndex < m_nShowIndex )
		{
			return nTextIndex;
		}
		else if ( nTextIndex >= nEndIndex )
		{
			for ( int i = 0; i < dwAllTextLen; i++ )
			{
				graphics.MeasureString( pText + i, nTextIndex - i, m_pFont, RectF(0,0,0,0), &m_cStringFormat, &rectString );
				{
					if ( rectString.Width <= fMaxWidth )
					{
						dwIndex = i;
						break;
					}
				}
			}
			return dwIndex;
		}
		else
		{
			return m_nShowIndex;
		}
	}
	else
	{
		if ( nStartSel < m_nDownPos )
		{
			if ( nTextIndex < m_nShowIndex )
			{
				return nTextIndex;
			}
			else
			{
				return m_nShowIndex;
			}
		}
		else
		{	
			if ( nTextIndex2 >= nEndIndex )
			{
				for ( int i = 0; i < dwAllTextLen; i++ )
				{
					graphics.MeasureString( pText + i, nTextIndex2 - i, m_pFont, RectF(0,0,0,0), &m_cStringFormat, &rectString );
					{
						if ( rectString.Width <= fMaxWidth )
						{
							dwIndex = i;
							break;
						}
					}
				}
				return dwIndex;
			}
			else
			{
				return m_nShowIndex;
			}

		}
	}
}

int CTransparentEdit::GetSelPos( int nIndex, wchar_t* pText )
{
	int nMax   = wcslen(pText);
	int nWidth = 0;

	if ( nIndex > nMax )
	{
		nIndex = nMax;
	}
	
	for ( int i = 0; i < nIndex; i++ )
	{
		int nUnicode = pText[i];
		if ( nUnicode > 255 )
		{
			nWidth += 2;
		}
		else
		{
			nWidth += 1;
		}
	}

	return nWidth;
}

int CTransparentEdit::GetTextIndex( int nPos, wchar_t* pText )
{
	if ( pText == NULL )
	{
		return 0;
	}
	if ( nPos == 0 )
	{
		return 0;
	}

	DWORD dwStyle = GetWindowLong( m_hWnd, GWL_STYLE );
	int dwTextLen = wcslen( pText );
	int nTempMax = nPos;
	int nIndex = 0;
	for ( int i = 0; i < dwTextLen; i++ )
	{
		int nUnicode = pText[i];
		if ( nUnicode > 255)
		{
			if ( dwStyle & ES_PASSWORD )
			{
				nTempMax -= 1;
			}
			else
			{
				nTempMax -= 2;
			}			
		}
		else
		{
			nTempMax -= 1;
		}	
		
		nIndex++;

		if ( nTempMax <= 0 )
		{
			break;
		}		
	}
	return nIndex; 
}

LRESULT CTransparentEdit::OnRedrawUI( WPARAM wParam, LPARAM lParam )
{
    Graphics *pGraphics = (Graphics*)wParam;
    HWND hGraphWnd = (HWND )lParam;
    CWnd * pGraphWnd = FromHandle(hGraphWnd);

    if ( IsWindowVisible() == FALSE || GetParent() == NULL || m_pImgNormalLeft == NULL || pGraphWnd == NULL )
    {
        return S_FALSE;
    }

    CRect cRect;
    GetWindowRect( &cRect );
    POINT point = cRect.TopLeft();

    //GetParent()->ScreenToClient( &point );
    pGraphWnd->ScreenToClient( &point );

    Image *pImgLeft = NULL;
    Image *pImgMiddle = NULL;
    Image *pImgRight = NULL;
	Image *pImgIcon = NULL;
    Color colorText;
    if ( m_emStatus == emStatusSetFocus )
    {
        pImgLeft = m_pImgFocusLeft;
        pImgMiddle = m_pImgFocusMiddle;
        pImgRight = m_pImgFocusRight;
        colorText = m_cFocusColor;
    }
    else
    {
        pImgLeft = m_pImgNormalLeft;
        pImgMiddle = m_pImgNormalMiddle;
        pImgRight = m_pImgNormalRight;		
        colorText = m_cNormalColor;
    }

	if ( m_emIconStatus == emStatusSetFocus )
	{
		pImgIcon = m_pImgIconFocus;
	}
	else
	{
		pImgIcon = m_pImgIconNormal;
	}

	if ( FALSE == IsWindowEnabled() )
    {
        pImgLeft = m_pImgDisableLeft;
		pImgMiddle = m_pImgDisableMiddle;
		pImgRight = m_pImgDisableRight;
		pImgIcon = NULL;
		colorText = m_cDisableColor;
    }

    if ( m_bDisableImg || IsWindowEnabled() )//非编辑状态无输入框
    {  
        if ( pImgLeft != NULL && pImgMiddle != NULL && pImgRight != NULL && pImgMiddle->GetWidth() != 0  )
        {
            unsigned int nPosX = point.x + pImgLeft->GetWidth();

            unsigned int dwMiddleWidth = 0;
	        if ( cRect.Width() > pImgLeft->GetWidth() + pImgRight->GetWidth() )
	        {
		        dwMiddleWidth = cRect.Width() - pImgLeft->GetWidth() - pImgRight->GetWidth();
	        }
	        
            // 左
            pGraphics->DrawImage( pImgLeft, point.x, point.y, pImgLeft->GetWidth(), cRect.Height()/*pImgLeft->GetHeight()*/ );
            // 右
	        pGraphics->DrawImage( pImgRight, point.x + cRect.Width() - pImgRight->GetWidth(), point.y,
                                                        pImgRight->GetWidth(), cRect.Height()/*pImgRight->GetHeight()*/ );

            // 中，尽量避免拉伸，因为拉伸的比例大了会导致边缘有模糊的问题
            for ( unsigned int nIndex = 0; nIndex < ( dwMiddleWidth / pImgMiddle->GetWidth() ); nIndex++ )
            {
                pGraphics->DrawImage( pImgMiddle, nPosX, point.y, pImgMiddle->GetWidth(), cRect.Height()/*pImgMiddle->GetHeight()*/ );
                nPosX += pImgMiddle->GetWidth();
            }
            pGraphics->DrawImage( pImgMiddle, nPosX, point.y, dwMiddleWidth % pImgMiddle->GetWidth() /*dwMiddleWidth - 5*/, cRect.Height()/*pImgMiddle->GetHeight()*/ );

        }
    }

	//绘制SearchEdit的图片
	if ( m_bSearchEdit && m_pImgSearch != NULL )
	{
		int nPosX = point.x + 13; 
		int	nPosY = point.y + ( /*m_pImgFocusLeft->GetHeight()*/cRect.Height() - m_pImgSearch->GetHeight() ) / 2;
        pGraphics->DrawImage( m_pImgSearch, nPosX, nPosY, m_pImgSearch->GetWidth(), m_pImgSearch->GetHeight() );

		m_nFirstOffset = /*EDIT_FRONT_LENGTH*/m_nEditFrontLen + m_pImgSearch->GetWidth();
	}
	else if ( m_cStringFormat.GetAlignment() == StringAlignmentNear )
	{
		//第一个字的起始位置
		m_nFirstOffset = /*EDIT_FRONT_LENGTH*/m_nEditFrontLen/*cRect.Width()/22*/;
	}

	CString strWindowText;
    GetWindowText( strWindowText );
    // 绘制Icon
    if ( m_bShowIcon && pImgIcon != NULL )
    {
		if ( !m_bIconDeleteText || strWindowText != "" )
		{
			int nPosX = point.x + cRect.Width() - m_nEditBackLen - pImgIcon->GetWidth(); 
			int	nPosY = point.y + ( /*m_pImgFocusLeft->GetHeight()*/cRect.Height() - pImgIcon->GetHeight() ) / 2;
			pGraphics->DrawImage( pImgIcon, nPosX, nPosY, pImgIcon->GetWidth(), pImgIcon->GetHeight() );

			m_cIconRect.SetRect( cRect.Width() - m_nEditBackLen - pImgIcon->GetWidth(), ( cRect.Height() - pImgIcon->GetHeight() ) / 2,
				cRect.Width() - m_nEditBackLen, ( cRect.Height() + pImgIcon->GetHeight() ) / 2 );
		}
    }

	//Edit最右位置
	int nLimitRight = point.x + cRect.Width() - m_nEditBackLen;
	if ( m_bShowIcon && pImgIcon != NULL )
	{
		nLimitRight = nLimitRight - pImgIcon->GetWidth();
	}

    //宋体字不做平滑处理、去毛边
    if ( m_strFontName != _T("宋体") )
    {
        pGraphics->SetTextRenderingHint(TextRenderingHint(TextRenderingHintAntiAlias));
    }

    CString strText = GetShowText();
	RectF outRect;

	DWORD dwStyle = GetWindowLong( m_hWnd, GWL_STYLE );

    if ( strText.GetLength() > 0 )
    {        
        // 判断是否显示Tip
        BOOL bShowTip = FALSE;      
        if ( m_bFocus == FALSE && strWindowText == "" )
        {
            bShowTip = TRUE;
        }

        if ( ( dwStyle & ES_PASSWORD ) && bShowTip == FALSE )
        {
            CString strTemp = "";
			//不编辑时显示6个点
			if( !m_bFocus )
			{
				for( int i=0; i<strText.GetLength(); i++ )
				{
					strTemp += "●"; //有多少个字符就显示多少个点
				}
			}
			else
			{
				//针对输入的汉字密码占用两个*问题进行改写处理
				unsigned short wChsCntParm = 0;
				unsigned short wEngCntParm = 0;
				CSrcManage::GetChsAndEngCnt( strText, wChsCntParm, wEngCntParm );
				
				unsigned int nIndex = 0;
				for ( nIndex = 0; nIndex < wEngCntParm + wChsCntParm; nIndex++ )
				{
					strTemp += "●"; //·				
				}
			}
		
            strText = strTemp;
        }


		//对于tip和真正的文字进行不同的绘制
		WCHAR *pwszText = NULL;
        int nLen = MultiByteToWideChar( CP_ACP, 0, strText, -1, NULL, NULL ); 
        pwszText = new WCHAR[ nLen+1 ];  
        MultiByteToWideChar( CP_ACP, 0, strText, -1, pwszText, nLen );
        pwszText[nLen] = '\0';
		unsigned int dwTextLen = wcslen(pwszText);

		//选中多个文字底部置灰
		int nStartSel, nEndSel;
		GetSel( nStartSel, nEndSel );
		if ( nStartSel != nEndSel && m_bFocus && !(dwStyle & ES_READONLY) )
		{
			int nIndex = GetTextIndex( nStartSel, pwszText );
			int nIndex2 = GetTextIndex( nEndSel, pwszText );
			if ( nIndex < m_nShowIndex )
			{
				nIndex = m_nShowIndex;
			}
			pGraphics->MeasureString( pwszText + m_nShowIndex, nIndex - m_nShowIndex, m_pFont, RectF(0,0,0,0), &m_cStringFormat, &outRect );
			int fStart = point.x + m_nFirstOffset + outRect.Width - 3;
			pGraphics->MeasureString( pwszText + nIndex, nIndex2-nIndex , m_pFont, RectF(0,0,0,0), &m_cStringFormat, &outRect );
			int nWide = outRect.Width;

			if ( fStart + nWide > nLimitRight )
			{
				nWide = nLimitRight - fStart;
			}
			if ( nIndex != 0 )
			{
				nWide -= 3;
			}
			int	nPosY = point.y + cRect.Height()/4;
			SolidBrush brush( m_cTipColor );
			pGraphics->FillRectangle( &brush, fStart, nPosY, nWide, cRect.Height()/4 * 2 );
			m_bShowCursor= FALSE;
		}

		#define FONT_Y_OFFSET	2
        if ( TRUE == bShowTip )
		{			
			SolidBrush brush( m_cTipColor );
			//Font* pFont = CSrcManage::GetFont( "微软雅黑", 12 );
			
			float fPosX = (float)point.x + /*EDIT_FRONT_LENGTH*/m_nEditFrontLen;
			if ( m_bSearchEdit && m_pImgSearch != NULL )
			{
				fPosX = (float)point.x + /*EDIT_FRONT_LENGTH*/m_nEditFrontLen + m_pImgSearch->GetWidth();
			}

			BSTR bstrText = strText.AllocSysString();
			pGraphics->DrawString( bstrText, -1, m_pTipFont, RectF( fPosX, (float)point.y+FONT_Y_OFFSET, 
					cRect.Width(), cRect.Height()/*m_pImgFocusLeft->GetHeight()*/ ), &m_cStringFormat, &brush );	
			SysFreeString( bstrText );
		} 
		else
		{
			SolidBrush brush( colorText );
	
			if ( dwStyle & ES_PASSWORD )
			{
				m_pFont = CSrcManage::GetFont( "微软雅黑", 13 );
			}

			if ( m_cStringFormat.GetAlignment() == StringAlignmentNear )
			{
				m_nShowIndex = GetShowIndex( cRect, pwszText );	

				float fPosX = (float)point.x + /*EDIT_FRONT_LENGTH*/m_nEditFrontLen;
				if ( m_bSearchEdit && m_pImgSearch != NULL )
				{
					fPosX = (float)point.x + /*EDIT_FRONT_LENGTH*/m_nEditFrontLen + m_pImgSearch->GetWidth();
				}

				if ( m_bVerCenter )
				{
					pGraphics->DrawString( pwszText + m_nShowIndex, -1, m_pFont, RectF( fPosX, (float)point.y, 
						nLimitRight - fPosX, cRect.Height()/*m_pImgFocusLeft->GetHeight()*/ ), &m_cStringFormat, &brush );
				}
				else
				{
					pGraphics->DrawString( pwszText + m_nShowIndex, -1, m_pFont, RectF( fPosX, (float)point.y+FONT_Y_OFFSET, 
						nLimitRight - fPosX, cRect.Height()/*m_pImgFocusLeft->GetHeight()*/ ), &m_cStringFormat, &brush );
				}
			}
			else
			{
				BSTR bstrText = strText.AllocSysString();

				if ( m_bVerCenter )
				{
					pGraphics->DrawString( bstrText, -1, m_pFont, RectF( (float)point.x , (float)point.y, 
						cRect.Width(), cRect.Height()/*m_pImgFocusLeft->GetHeight()*/ ), &m_cStringFormat, &brush );
				}
				else
				{
					pGraphics->DrawString( bstrText, -1, m_pFont, RectF( (float)point.x , (float)point.y+FONT_Y_OFFSET, 
						cRect.Width(), cRect.Height()/*m_pImgFocusLeft->GetHeight()*/ ), &m_cStringFormat, &brush );
				}

				SysFreeString( bstrText );

				pGraphics->MeasureString( pwszText, dwTextLen, m_pFont, RectF(0,0,0,0), &m_cStringFormat, &outRect );
				m_nFirstOffset = ( cRect.Width() - outRect.Width ) / 2;
			}		
		}    

        // 保存每个字的rect，以便设置编辑框的光标位置
        m_chractarLst.clear(); 
        RectF rectf(0,0,0,0);
        for( int i = 0; i<= dwTextLen - m_nShowIndex; i++ )
        {   
            pGraphics->MeasureString( pwszText + m_nShowIndex, i, m_pFont, RectF(0,0,0,0), &m_cStringFormat, &rectf ); 
            m_chractarLst.push_back( rectf );
        }  		
        
		DWORD dwPos = GetSel() & 0xFFFF;
		int nTextIndex = GetTextIndex( dwPos, pwszText );
		pGraphics->MeasureString( pwszText + m_nShowIndex, nTextIndex - m_nShowIndex, m_pFont, RectF(0,0,0,0), &m_cStringFormat, &outRect );
		
		if ( NULL != pwszText )
        {
			delete []pwszText;
			pwszText = NULL;
		}
    }

	// 绘制光标
	if ( !(dwStyle & ES_READONLY) && IsWindowEnabled() )
	{	
		if ( m_bShowCursor == TRUE )
		{		
			int nPosX = point.x + m_nFirstOffset + outRect.Width - 3;  
			if ( nPosX > nLimitRight  )
			{
				nPosX = nLimitRight;
			}
           
            //防止当编辑框中无文字时，效果上 光标显现在边框的外侧
            if ( nPosX < point.x + pImgLeft->GetWidth())
            {
                nPosX = point.x + pImgLeft->GetWidth();
            }

			int	nPosY = point.y + cRect.Height()/4;
			pGraphics->DrawLine( &Pen( m_cFocusColor, 2 ), Point( nPosX, nPosY ), 
				Point( nPosX, point.y + cRect.Height()/4 * 3 ) );
		}
	}

    return S_OK;
}

int CTransparentEdit::GetSelByPos( int nPosX )
{   
    CRect rect;
    GetClientRect(&rect);
    
    int nOffSet = m_nFirstOffset - 6;
	if ( nOffSet < 0 )
	{
		nOffSet = 0;
	}
    int re = 0;
    int nSize = m_chractarLst.size();
    for (int i = 0; i< nSize -1 ; i++ )
    {   
        float pos = m_chractarLst[i].Width;
        float posNext =  m_chractarLst[i + 1 ].Width;
        if ( pos + nOffSet > nPosX )
        {   
            if ( i > 0 &&  ( pos - m_chractarLst[i-1].Width )/2 + m_chractarLst[i-1].Width + nOffSet > nPosX )
            {
                re = i;
            }
            else
            {
				re = i - 1 ;
            }
            
            break; 
        }

        if ( pos + nOffSet < nPosX && posNext + nOffSet > nPosX )
        { 
			if ( (posNext - pos)/2 + pos + nOffSet < nPosX )
			{   
				re = i + 1; 
			}
			else
			{
				re = i;
			}

			break;
        }
        else
        {
            continue;
        }
   }

    if ( i == nSize -1 )
    {  
		re = nSize - 1;
    }

	CString strText;
	GetWindowText( strText );
	BSTR bstrText = strText.AllocSysString();

	int nPos = GetSelPos( re + m_nShowIndex, bstrText );

	SysFreeString( bstrText );
		
	return nPos; 
}


HBRUSH CTransparentEdit::CtlColor(CDC *pDC, UINT nCtlColor)
{
// 	if ( pDC != NULL )
// 	{
// 		ReleaseDC( pDC );
// 		pDC->DeleteDC();
// 		pDC = NULL;
// 	}

	//隐藏自身光标
	HideCaret();
	//pDC->SetBkMode(TRANSPARENT);  // 设置透明背景    
	//pDC->OffsetClipRgn(-100, -100);
	//pDC->SetTextColor(RGB(0, 0, 255));  // 设置文本颜色    
	//TODO: Return a non-NULL brush if the parent's handler should not be called    
	return (HBRUSH)GetStockObject(HOLLOW_BRUSH); // 返回透明画刷  
}


void CTransparentEdit::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_emStatus = emStatusSetFocus;
	m_bLBtnDown = TRUE;

	if ( m_bShowIcon && m_cIconRect.PtInRect( point ) )
	{
		m_emIconStatus = emStatusSetFocus;
	}
   		
	CEdit::OnLButtonDown(nFlags, point); 

	m_nDownPos = GetSelByPos( point.x );
	SetSel( m_nDownPos, m_nDownPos, FALSE );
   
	NOTIF_PARENT_WND
}

void CTransparentEdit::OnMouseMove(UINT nFlags, CPoint point)
{
	if ( !m_bLBtnDown )
	{
		return;
	}

	int nPos = GetSelByPos( point.x );
	if ( nPos < m_nDownPos )
	{
		SetSel( nPos, m_nDownPos, FALSE );
	}
	else
	{
		SetSel( m_nDownPos, nPos, FALSE );
	}
	NOTIF_PARENT_WND
}

void CTransparentEdit::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if ( m_bShowIcon && m_cIconRect.PtInRect( point ) )
	{
		if ( m_emIconStatus == emStatusSetFocus )
		{	
			PostMessage( UI_EDITDELETE_CLICK );
			GetParent()->PostMessage( UI_EDITDELETE_CLICK );
			if ( m_bIconDeleteText )
			{
				SetWindowText( "" );
			}					
		}
	}
	m_emIconStatus = emStatusNormal;
	m_bLBtnDown = FALSE;

    CEdit::OnLButtonUp(nFlags, point);
}

void CTransparentEdit::OnSetFocus(CWnd* pOldWnd) 
{
	CEdit::OnSetFocus(pOldWnd);

    SetSel( -1 );  // 获取焦点后，光标显示在最后
	m_bFocus = TRUE;
	m_emStatus = emStatusSetFocus;  
    PostMessage( WM_EDIT_SETFOCUS, 0, 0 );
	GetParent()->PostMessage( WM_EDIT_SETFOCUS, (WPARAM)GetSafeHwnd(), 0 );
	
	DWORD dwStyle = GetWindowLong( m_hWnd, GWL_STYLE );
	if ( dwStyle & ES_PASSWORD )
	{
		//SetWindowText( "" );
	}
    
	NOTIF_PARENT_WND
    SetTimer( 100, 500, NULL );
    m_bShowCursor = TRUE;
}

void CTransparentEdit::OnKillFocus(CWnd* pNewWnd) 
{
	CEdit::OnKillFocus(pNewWnd);
	m_bFocus = FALSE;
    m_bShowCursor = FALSE;
	m_bLBtnDown = FALSE;
	m_emStatus = emStatusNormal;

	PostMessage( WM_KILL_FOCUS, NULL, (LPARAM)pNewWnd );
	GetParent()->PostMessage( WM_KILL_FOCUS, (WPARAM)GetSafeHwnd(), (LPARAM)pNewWnd );

	NOTIF_PARENT_WND
    KillTimer( 100 );
}

void CTransparentEdit::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CEdit::OnShowWindow(bShow, nStatus);
	m_emStatus = emStatusNormal;
//	NOTIF_PARENT_WND
}

void CTransparentEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{	
	m_emStatus = emStatusSetFocus;

	PostMessage( WM_EDIT_ONCHAR, nChar);
    //发给父窗口，供umcweb使用
	GetParent()->PostMessage( WM_EDIT_ONCHAR, (WPARAM)GetSafeHwnd() );

 	NOTIF_PARENT_WND

    CEdit::OnChar(nChar, nRepCnt, nFlags);
}

void CTransparentEdit::OnChange() 
{ 
	CString strText;
	GetWindowText( strText );
	if ( strText != m_strText )
	{
		m_strText = strText;
		PostMessage( WM_EDIT_CHANGED, (WPARAM)GetSafeHwnd() );
		//发给父窗口，供umcweb使用
		GetParent()->PostMessage( WM_EDIT_CHANGED, (WPARAM)GetSafeHwnd() );

		if ( this == GetFocus() )
		{  
			PostMessage( WM_EDIT_CHANGED_NOFOCUS, (WPARAM)GetSafeHwnd() ); //-----JYY   cnstool中使用，当edit框获得焦点且数据变化发送change消息
		}
	}
    NOTIF_PARENT_WND
}

void CTransparentEdit::OnTimer(UINT nIDEvent) 
{
    // TODO: Add your message handler code here and/or call default
    if ( GetParent() != NULL && IsWindowVisible() == TRUE )
    {
        m_bShowCursor = !m_bShowCursor;

        NOTIF_PARENT_WND
    }

    CEdit::OnTimer(nIDEvent);
}


//不响应右键消息
void CTransparentEdit::OnRButtonDown(UINT nFlags, CPoint point)
{
	return;
}


CString CTransparentEdit::GetShowText()
{
    CString strText;
    GetWindowText(strText);
	
    if ( FALSE == m_bFocus && strText == "" )
    {
        return m_strTip;
    } 
	
	return strText;
}

void CTransparentEdit::SetTextAlign( StringAlignment emTextAlign, BOOL bInvalidate )
{
	m_cStringFormat.SetAlignment( emTextAlign );
	if ( bInvalidate )
	{
		NOTIF_PARENT_WND
	}
}

void CTransparentEdit::SetTextColor( Color colorNormal, Color colorFocus, BOOL bInvalidate )
{
	m_cNormalColor = colorNormal;
	m_cFocusColor = colorFocus;

    //如果是宋体，将color的ALPHA值设为254，防止文字透明
    if ( m_strFontName == _T("宋体") )
    {
        ARGB argb = m_cNormalColor.GetValue(); 
        argb = (argb & 0x00FFFFFF) | ( 0xFE << 24 );
        m_cNormalColor.SetValue( argb );

        argb = m_cFocusColor.GetValue(); 
        argb = (argb & 0x00FFFFFF) | ( 0xFE << 24 );
        m_cFocusColor.SetValue( argb );
    }

	if ( bInvalidate )
	{
		NOTIF_PARENT_WND
	}
}

void CTransparentEdit::SetDisableColor( Color colorDisable, BOOL bInvalidate /* = FALSE */ )
{
    m_cDisableColor = colorDisable;

    if ( m_strFontName == _T("宋体") )
    {
        ARGB argb = m_cDisableColor.GetValue(); 
        argb = (argb & 0x00FFFFFF) | ( 0xFE << 24 );
        m_cDisableColor.SetValue( argb );
    }

    if ( bInvalidate )
    {
        NOTIF_PARENT_WND
	}
}

void CTransparentEdit::SetTipColor( Color colorTip, BOOL bInvalidate /* = FALSE */ )
{
	m_cTipColor = colorTip;
	
    if ( m_strFontName == _T("宋体") )
    {
        ARGB argb = m_cTipColor.GetValue(); 
        argb = (argb & 0x00FFFFFF) | ( 0xFE << 24 );
        m_cTipColor.SetValue( argb );
    }

	if ( bInvalidate )
	{
		NOTIF_PARENT_WND
	}
}

void CTransparentEdit::SetFont( const unsigned int dwFontSize, CString strFontFamily, BOOL bInvalidate )
{
    m_strFontName = strFontFamily;
	m_pFont = CSrcManage::GetFont( strFontFamily, dwFontSize );
	SetTipFont( dwFontSize, strFontFamily );
	if ( bInvalidate )
	{
		NOTIF_PARENT_WND
	}
}

void CTransparentEdit::SetTipFont( const unsigned int dwFontSize, CString strFontFamily, BOOL bInvalidate )
{
    m_strFontName = strFontFamily;
	m_pTipFont = CSrcManage::GetFont( strFontFamily, dwFontSize );
	if ( bInvalidate )
	{
		NOTIF_PARENT_WND
	}
}

void CTransparentEdit::SetLimitLength( unsigned int dwLength )
{
	SetLimitText( dwLength );
}

void CTransparentEdit::SetImage( CString strFolder, BOOL bInvalidate )
{
	String strFile = strFolder + "//" + CTransparentEdit::strNormalLeft;
	m_pImgNormalLeft = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CTransparentEdit::strNormalMid;
	m_pImgNormalMiddle = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CTransparentEdit::strNormalRight;
	m_pImgNormalRight = CSrcManage::GetImage( strFile.c_str() );

	strFile = strFolder + "//" + CTransparentEdit::strFocusLeft;
	m_pImgFocusLeft = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CTransparentEdit::strFocusMid;
	m_pImgFocusMiddle = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CTransparentEdit::strFocusRight;
	m_pImgFocusRight = CSrcManage::GetImage( strFile.c_str() );

	strFile = strFolder + "//" + CTransparentEdit::strDisableLeft;
	m_pImgDisableLeft = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CTransparentEdit::strDisableMid;
	m_pImgDisableMiddle = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CTransparentEdit::strDisableRight;
	m_pImgDisableRight = CSrcManage::GetImage( strFile.c_str() );

	strFile = strFolder + "//" + CTransparentEdit::strNormalIcon;
	m_pImgIconNormal = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CTransparentEdit::strFocusIcon;
	m_pImgIconFocus = CSrcManage::GetImage( strFile.c_str() );

	strFile = strFolder + "//" + CTransparentEdit::strSearch;
	m_pImgSearch = CSrcManage::GetImage( strFile.c_str() );
	if ( bInvalidate )
	{
		NOTIF_PARENT_WND
	}	
}

void CTransparentEdit::SetImage( UINT nImgNormalLeftID, UINT nImgNormalMiddleID, UINT nImgNormalRightID, 
								  UINT nImgFocusLeftID, UINT nImgFocusMiddleID, UINT nImgFocusRightID, 
								  UINT nImgDisableLeftID, UINT nImgDisableMiddleID, UINT nImgDisableRightID,
								  UINT nImgIconNormalID, UINT nImgIconFocusID, UINT nImgSearchIconID,
								  BOOL bInvalidate, const CString& strImgType)
{
	m_pImgNormalLeft  = CSrcManage::GetImage( nImgNormalLeftID, strImgType );
	m_pImgNormalMiddle   = CSrcManage::GetImage( nImgNormalMiddleID, strImgType );
	m_pImgNormalRight = CSrcManage::GetImage( nImgNormalRightID, strImgType );
	m_pImgFocusLeft  = CSrcManage::GetImage( nImgFocusLeftID, strImgType );
	m_pImgFocusMiddle   = CSrcManage::GetImage( nImgFocusMiddleID, strImgType );
	m_pImgFocusRight = CSrcManage::GetImage( nImgFocusRightID, strImgType );
	m_pImgDisableLeft  = CSrcManage::GetImage( nImgDisableLeftID, strImgType );
	m_pImgDisableMiddle   = CSrcManage::GetImage( nImgDisableMiddleID, strImgType );
	m_pImgDisableRight = CSrcManage::GetImage( nImgDisableRightID, strImgType );
	m_pImgIconNormal  = CSrcManage::GetImage( nImgIconNormalID, strImgType );
	m_pImgIconFocus   = CSrcManage::GetImage( nImgIconFocusID, strImgType );
	m_pImgSearch = CSrcManage::GetImage( nImgSearchIconID, strImgType );
	
}

LRESULT CTransparentEdit::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    if( WM_IME_NOTIFY == message ) //120803--ldy 切换输入法发送消息
    {  
        HideCaret();
    }

    return CEdit::DefWindowProc(message, wParam, lParam);  
}



CTransparentIpEdit::CTransparentIpEdit()
{
	//ModifyStyle(0, ES_NUMBER);
}

BEGIN_MESSAGE_MAP(CTransparentIpEdit, CTransparentEdit)
//{{AFX_MSG_MAP(CTransparentIpEdit)
ON_WM_CHAR()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CTransparentIpEdit::GetAddress( DWORD& dwIp )
{
	CString strWindowText;
    GetWindowText( strWindowText );

	int count = -1;
	int i = -1;	
	do
	{
		count++;
		i = strWindowText.Find( 46, i+1 );
	}while( i != -1 );
	
	if ( count != 3 )
	{
		dwIp = 0;
		return;
	}
	
	int nIp[4] = {0};
    sscanf( (LPTSTR)(LPCTSTR)strWindowText, "%d.%d.%d.%d", &nIp[0],&nIp[1],&nIp[2],&nIp[3] );
	
	CString strIP;
    strIP.Format( _T("%d.%d.%d.%d"), nIp[0], nIp[1], nIp[2], nIp[3] );
	
	dwIp = ntohl( inet_addr( strIP ) );

	SetWindowText( strIP );
}

void CTransparentIpEdit::SetAddress( DWORD dwIp )
{
	CString strIP = "";
	if ( dwIp != 0 )
	{
		strIP = GetIpStr( dwIp );
	}
	SetWindowText( strIP );
}

CString CTransparentIpEdit::GetIpStr( DWORD dwIPAddr)
{
    unsigned short wHigh   = HIWORD( dwIPAddr );
    unsigned short wLow    = LOWORD( dwIPAddr );
	CString strIP;
    strIP.Format( _T("%d.%d.%d.%d"), HIBYTE( wHigh ), LOBYTE( wHigh ),
		HIBYTE( wLow ), LOBYTE( wLow ) );
    return strIP;
}


void CTransparentIpEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
    //收到重复按键不处理
    if ( nRepCnt != 1 )
    {      
        return;
    }

	if (nChar == VK_BACK) 
	{
		CEdit::OnChar(nChar, nRepCnt, nFlags);
	}
	else if ( (nChar >= '0' && nChar <= '9') || nChar == '.' )
	{
		int nStartSel, nEndSel;
		GetSel( nStartSel, nEndSel );
		if ( nStartSel != nEndSel )
		{
			CEdit::OnChar(nChar, nRepCnt, nFlags);
			return;
		}

		DWORD dwPos = GetSel() & 0xFFFF;	//获取鼠标当前位置
		int len;	
		CString str,tmpS;	//s:编辑框原来的字串加上刚输入的字符；tmpS：用于后面获得原来的字串中“.”的数目
		GetWindowText( str );
		GetWindowText( tmpS );
		len = str.GetLength();
		str.Insert( dwPos, nChar );
		//str += nChar;	//加上刚输入的字符
		if( dwPos==0 && nChar==46 )	//不允许在第一位输入点
			return;
		int count = -1;	
		int i = -1;	 
		int j = -1;
		BOOL bDot=TRUE;  //是否可以再输入. （即“.”的数目大于3个）
 		
		do	//获取“.”的数量
		{
			count++;
			i = tmpS.Find( 46, i+1 );
		}while( i != -1 );
		if( count >= 3 )
		{
			bDot=FALSE;
		}

		if ( dwPos == len )
		{	
			if( len > 0 && tmpS.GetAt(len-1) == 46 && nChar==46 )//如果最后一个字符是"."
			{
				return;
			}
			
			i = str.ReverseFind(46);	//获取最后一个“.”的位置
			if( !bDot )//如果不允许输入点
			{
				if ( nChar==46 )
				{
					return;
				}
				if ( len - i > 3 )
				{
					return;
				}			
			}
			else
			{
				if ( len - i > 3 && nChar != 46 )
				{
					tmpS += 46;
					SetWindowText( tmpS );

					SetSel( dwPos+1, dwPos+1, FALSE );
				}
			}
			CEdit::OnChar(nChar, nRepCnt, nFlags);		
			if( len - i == 3 && len!=3 )	//用字串长度减去最后一个“.”的位置，等于3则在后面加多一个点
			{
				BOOL bChange = FALSE;
				CString strRight = str.Right(3);
				int nRight = atoi(strRight);
				if ( nRight > 255 )
				{
					strRight = "255";
					str = str.Left( len - 2 ) + strRight;
					bChange = TRUE;
				}

				if( !bDot )	//判断能否再输入点
				{
					if ( bChange )
					{
						SetWindowText( str );

						SetSel( dwPos+1, dwPos+1, FALSE );
					}					
					return;
				}
				str += 46;
				SetWindowText( str );

				SetSel( dwPos+2, dwPos+2, FALSE );	//将鼠标移至相应位置
			}
		}
		else
		{
			if ( nChar==46 )
			{
				if ( !bDot )
				{
					return;
				}
// 				if( tmpS.GetAt(dwPos -1) == 46 || tmpS.GetAt(dwPos) == 46 )
// 				{
// 					return;
// 				}
				CEdit::OnChar(nChar, nRepCnt, nFlags);
			}
			else
			{
				i = -1;
				j = 0;
				CString astr[4];
				
				if ( count == 0 )
				{
					int nTemp = atoi( str );
					if ( nTemp > 255 )
					{
						str = "255.";
						SetWindowText( str );

						SetSel( 4, 4, FALSE );
 						return;
					}
				}

				for ( int k = 0; k <= count; k++ )
				{					
					if ( k == count )
					{
						astr[k] = str.Right( len - i );
					}
					else
					{
						i = str.Find( 46, i+1 ); 
						astr[k] = str.Mid( j, i - j );
					}
					int nTemp = atoi( astr[k] ); 
					int nAstrLen = strlen(astr[k]);
					if ( nTemp > 255 )
					{
						astr[k] = "255";
					}
					else
					{
						if ( nAstrLen > 3 )
						{
							return;
						}
					}

					j = i + 1;
				}
				
				str = "";
				for ( k = 0; k <= count; k++  )
				{
					str += astr[k];
					if ( k != count )
					{
						str += '.';
					}
				}
				SetWindowText( str );	
				SetSel( dwPos+1, dwPos+1, FALSE );				
			}
		}
	}	
	m_emStatus = emStatusSetFocus;
}

CSize CTransparentEdit::GetImageSize()
{
    CSize sz(0);
    if ( m_pImgNormalLeft != NULL )
    {
        sz.cx = m_pImgNormalLeft->GetWidth();
        sz.cy = m_pImgNormalLeft->GetHeight();
    }
    
    return sz;
}

//解决Bug00164072 win7 IE10 鼠标放到编辑框位置，光标不停闪烁 20131129 by xhx
BOOL CTransparentEdit::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{   
	HCURSOR hCurOld = GetCursor();  
    HCURSOR hCur = LoadCursor( NULL, IDC_IBEAM ); 
    if ( hCurOld != hCur )
    {
        SetCursor( hCur );
    }
	
	return TRUE;
}

//会议讨论拖拽到edit上方时 edit高亮但不是实际的focus效果
LRESULT CTransparentEdit::OnEditSelected( WPARAM wParam, LPARAM lParam )
{
	if ( m_emStatus!= emStatusSetFocus )
	{
		m_emStatus = emStatusSetFocus; 
		NOTIF_PARENT_WND
	}

    return S_OK;
}

LRESULT CTransparentEdit::OnEditLeave( WPARAM wParam, LPARAM lParam )
{
	if ( m_emStatus != emStatusNormal )
	{
		 m_emStatus = emStatusNormal; 
		 NOTIF_PARENT_WND
	}

	return S_OK;
}


