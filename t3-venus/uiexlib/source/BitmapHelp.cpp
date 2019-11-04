// BitmapHelp.cpp: implementation of the CBitmapHelp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "bitmapHelp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
Bitmap* CBitmapHelp::m_pBitmap = NULL;
CBitmapHelp::CBitmapHelp()
{

}

CBitmapHelp::~CBitmapHelp()
{

}


Bitmap* CBitmapHelp::CreateBitmap( IItemList* pItemList )
{
	if ( pItemList == NULL )
	{
		return NULL;
	}
	if (m_pBitmap != NULL)
	{
		delete m_pBitmap;
		m_pBitmap = NULL;
	}

	IBaseItem* pBaseItem = pItemList->GetItemData();
	
	CRect rect = pBaseItem->GetItemRect(); 
	
	m_pBitmap = new Bitmap( pBaseItem->GetItemWidth(), pBaseItem->GetItemHeight() );

	//Graphics graphics( m_pBitmap );
	Graphics* pGraphics = Graphics::FromImage( m_pBitmap );
	
	pGraphics->TranslateTransform( -rect.left, -rect.top );
	
	Args_Graphics args_Graphics( pGraphics, Rect( rect.left, rect.top, rect.Width(), rect.Height() ) );
	
	DrawItem( pItemList, &args_Graphics );
	
	pGraphics->ResetTransform();

	if ( pGraphics != NULL )
	{
		delete pGraphics;
		pGraphics = NULL;
	}

	return m_pBitmap;
}


Bitmap* CBitmapHelp::CreateBitmap( IBaseItem* pBaseItem )
{
	if ( pBaseItem == NULL )
	{
		return NULL;
	}
	if (m_pBitmap != NULL)
	{
		delete m_pBitmap;
		m_pBitmap = NULL;
	}
		
	CRect rect = pBaseItem->GetItemRect(); 
	
	m_pBitmap = new Bitmap( pBaseItem->GetItemWidth(), pBaseItem->GetItemHeight() );
	
	Graphics* pGraphics = Graphics::FromImage( m_pBitmap );

	Args_Graphics args_Graphics( pGraphics, Rect( rect.left, rect.top, rect.Width(), rect.Height() ) );

	pBaseItem->Draw( &args_Graphics );

	if ( pGraphics != NULL )
	{
		delete pGraphics;
		pGraphics = NULL;
	}

	return m_pBitmap;
}


BOOL CBitmapHelp::GetBitmap( Bitmap* pBitmap, IItemList* pItemList )
{
	if ( pBitmap == NULL || pItemList == NULL )
	{
		return FALSE;
	}
	
	IBaseItem* pBaseItem = pItemList->GetItemData();
	
	CRect rect = pBaseItem->GetItemRect(); 
	
	Graphics* pGraphics = Graphics::FromImage( pBitmap );
	
	pGraphics->TranslateTransform( -rect.left, -rect.top );
	
	Args_Graphics args_Graphics( pGraphics, Rect( rect.left, rect.top, rect.Width(), rect.Height() ) );
	
	DrawItem( pItemList, &args_Graphics );
	
	pGraphics->ResetTransform();
	
	return TRUE;
}


void CBitmapHelp::DrawItem( IItemList* pItemList, IArgs* pArgs )
{
	int nItemCount = pItemList->GetItemCount();
	IBaseItem* pBaseItem = pItemList->GetItemData();
		
	Args_Graphics* p = NULL;
	Args_Graphics pSubGraphics( 0, Rect(0,0,0,0) );
	Bitmap* pSubBitmap = NULL;
	if ( p = dynamic_cast<Args_Graphics*>(pArgs) )
	{		
		if ( pBaseItem != NULL )
		{
			pBaseItem->Draw( pArgs );
			CRect rc = pBaseItem->GetItemRect();
			p->m_rc = Rect( Point(rc.left,rc.top), Size(rc.Width(),rc.Height()) );
			
			if ( nItemCount != 0 )
			{
				pSubBitmap = new Bitmap( rc.Width(), rc.Height(), p->m_pGraphics );
				pSubGraphics.m_pGraphics = Graphics::FromImage( pSubBitmap );
				pSubGraphics.m_rc = Rect( Point(rc.left,rc.top), Size(rc.Width(),rc.Height()) );
			}
		}		
	}
	else
	{
		return;
	}
	
	for ( int nIndex = 0; nIndex < nItemCount; nIndex++ )
	{
		IItemList* pSubList = pItemList->GetItemByIndex( nIndex );
		if ( pSubList != 0 )
		{
			DrawItem( pSubList, &pSubGraphics );
		}
	}
		
	if ( nItemCount != 0)
	{
		p->m_pGraphics->DrawImage( pSubBitmap, p->m_rc.GetLeft(), p->m_rc.GetTop() );
		delete pSubBitmap;
		pSubBitmap = 0;
		delete pSubGraphics.m_pGraphics;
		pSubGraphics.m_pGraphics = 0;
	}	
}



Bitmap* CBitmapHelp::CreateBitmap( Image* pImg, CString strText, Font* pFont, StringFormat& strFormat, Color& col )
{
	if ( pImg == NULL )
	{
		return NULL;
	}
	if (m_pBitmap != NULL)
	{
		delete m_pBitmap;
		m_pBitmap = NULL;
	}
	
	m_pBitmap = new Bitmap( pImg->GetWidth(), pImg->GetHeight() );
	
	Graphics* pGraphics = Graphics::FromImage( m_pBitmap );

    pGraphics->DrawImage( pImg, 0, 0, pImg->GetWidth(), pImg->GetHeight() );
		
	if ( strText.GetLength() > 0 )
	{
		SolidBrush brush( col );
		pGraphics->SetTextRenderingHint( TextRenderingHint( TextRenderingHintAntiAlias ) );
		
		BSTR bstr = strText.AllocSysString();
		pGraphics->DrawString( bstr, -1, pFont, RectF( 0, 0, pImg->GetWidth(), pImg->GetHeight() ), &strFormat, &brush );
		SysFreeString( bstr );
	}

	if ( pGraphics != NULL )
	{
		delete pGraphics;
		pGraphics = NULL;
	}

	return m_pBitmap;
}
