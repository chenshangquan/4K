#include "stdafx.h"
#include "ItemFactory.h"
#include "PropertyHelp.h"
#include "System.h"

namespace AutoUIFactory
{
template<> CItemFactory* Singleton<CItemFactory>::ms_pSingleton  = 0;
const String CItemFactory::strType = "Type";
const String CItemFactory::strSize = "Size";
const String CItemFactory::strImage = "Image";
const String CItemFactory::strText = "Text";

const String CItemFactory::strTextItem = "Text";
const String CItemFactory::strExTextItem = "ExText";
const String CItemFactory::strImageItem = "Image";
const String CItemFactory::strFunc = "Func";
const String CItemFactory::strFontColor = "FontColor";
const String CItemFactory::strFontName = "FontName";
const String CItemFactory::strFontSize = "FontSize";
const String CItemFactory::strSelColor = "SelColor";
const String CItemFactory::strAlignment = "Alignment";
const String CItemFactory::strLineAlignment = "LineAlignment";
const String CItemFactory::strLayoutAlgorithm = "LayoutAlgorithm";
const String CItemFactory::strSortAlgorithm = "SortAlgorithm";

const String CItemFactory::strSecondText = "SecondText";
const String CItemFactory::strSecondFontColor = "SecondFontColor";
const String CItemFactory::strSecondFontName = "SecondFontName";
const String CItemFactory::strSecondFontSize = "SecondFontSize";
const String CItemFactory::strSecondAlignment = "SecondAlignment";

const String CItemFactory::strCanMove = "Move";
const String CItemFactory::strCanDrag = "Drag";
const String CItemFactory::strAlwaysShow = "AlwaysShow";
const String CItemFactory::strListItem = "ListItem";
const String CItemFactory::strCheckItem = "CheckItem";
const String CItemFactory::strButtonItem = "ButtonItem";
const String CItemFactory::strMidImageItem = "MidImage";

IBaseItem* CItemFactory::CreateItem( XMLAttributes& xmlAttrib )
{
	if (!xmlAttrib.exists( CItemFactory::strSize ) || 
		!xmlAttrib.exists( CItemFactory::strType ) )
	{
		return 0;
	}
	String strType = xmlAttrib.getValue( CItemFactory::strType );
	String strSize = xmlAttrib.getValue( CItemFactory::strSize );
   
	//2012-6-19 by yjj
	SIZE sz = CPropertyHelp::stringToSize( strSize );
	//自适应分辨率
    CPropertyHelp::ResolutionAdp( sz.cx, sz.cy );

	IBaseItem* pBase = 0;
	if ( strType == CItemFactory::strTextItem )
	{ 

		String strText = "";
		if ( xmlAttrib.exists( CItemFactory::strText ) )
		{
			strText = xmlAttrib.getValue( CItemFactory::strText );
		}
		CTextItem* pItem = new CTextItem( strText, sz.cx, sz.cy );
		if ( xmlAttrib.exists( CItemFactory::strFunc ) )
		{
			String strFunc = xmlAttrib.getValue( CItemFactory::strFunc );
			pItem->SetFunc( strFunc );
		}
		if ( xmlAttrib.exists( strFontName) && xmlAttrib.exists( strFontSize) && xmlAttrib.exists( strFontColor ) )
		{
			String strFontName = xmlAttrib.getValue( CItemFactory::strFontName );
			int nFontSize = xmlAttrib.getValueAsInteger( CItemFactory::strFontSize );
			CPropertyHelp::FontSizeAdp( nFontSize ); //2012-6-19  自适应分辨率下字体也同步自适应变化 by yjj
			String strFontColor = xmlAttrib.getValue( CItemFactory::strFontColor );
			Font* pFont = CSrcManage::GetFont( strFontName.c_str(), nFontSize );
			pItem->SetFont( pFont );
			COLORREF col = CPropertyHelp::stringToColor( strFontColor );
			Color color = Color( GetRValue(col), GetGValue(col), GetBValue( col ) );
			pItem->SetFontColor( color );
		}
		if ( xmlAttrib.exists( CItemFactory::strAlignment) )
		{
			StringAlignment align = xmlAttrib.getValueAsAlignment( CItemFactory::strAlignment );
			pItem->SetAlignment( align );
		}
		if ( xmlAttrib.exists( CItemFactory::strSelColor) )
		{
			String strColor = xmlAttrib.getValue( CItemFactory::strSelColor );
			COLORREF col = CPropertyHelp::stringToColor( strColor );
			Color color = Color( GetRValue(col), GetGValue(col), GetBValue( col ) );
			pItem->SetSelColor( color );
		}
		pBase = pItem;
	}
	else if ( strType == CItemFactory::strImageItem )
	{
		String strImage = xmlAttrib.getValue( CItemFactory::strImage );
		//SIZE sz = CPropertyHelp::stringToSize( strSize );
		strImage = CSystem::GetSingletonPtr()->GetImagePath() + strImage;
		CImageItem* pItem = new CImageItem( strImage.c_str(), sz.cx, sz.cy );
		if ( xmlAttrib.exists( CItemFactory::strFunc ) )
		{
			String strFunc = xmlAttrib.getValue( CItemFactory::strFunc );
			pItem->SetFunc( strFunc );
		}
		pBase = pItem;
	}
	else if ( strType == CItemFactory::strMidImageItem )
	{
		String strImage = xmlAttrib.getValue( CItemFactory::strImage );
		//SIZE sz = CPropertyHelp::stringToSize( strSize );
		strImage = CSystem::GetSingletonPtr()->GetImagePath() + strImage;
		CMidImageItem* pItem = new CMidImageItem( strImage.c_str(), sz.cx, sz.cy );
		if ( xmlAttrib.exists( CItemFactory::strFunc ) )
		{
			String strFunc = xmlAttrib.getValue( CItemFactory::strFunc );
			pItem->SetFunc( strFunc );
		}
		pBase = pItem;
	}
	else if ( strType == CItemFactory::strListItem )
	{
		String strImage = xmlAttrib.getValue( CItemFactory::strImage );
		//SIZE sz = CPropertyHelp::stringToSize( strSize );
		strImage = CSystem::GetSingletonPtr()->GetImagePath() + strImage;
		CListItem* pItem = new CListItem( strImage.c_str(), sz.cx, sz.cy );
		if ( xmlAttrib.exists( CItemFactory::strFunc ) )
		{
			String strFunc = xmlAttrib.getValue( CItemFactory::strFunc );
			pItem->SetFunc( strFunc );
		}
		pBase = pItem;
	}
	else if ( strType == CItemFactory::strCheckItem )
	{
		String strImage = xmlAttrib.getValue( CItemFactory::strImage );
		//SIZE sz = CPropertyHelp::stringToSize( strSize );
		strImage = CSystem::GetSingletonPtr()->GetImagePath() + strImage;
		CCheckItem* pItem = new CCheckItem( strImage.c_str(), sz.cx, sz.cy );
		if ( xmlAttrib.exists( CItemFactory::strFunc ) )
		{
			String strFunc = xmlAttrib.getValue( CItemFactory::strFunc );
			pItem->SetFunc( strFunc );
		}
		pBase = pItem;
	}
	else if ( strType == CItemFactory::strButtonItem )
	{
		String strImage = xmlAttrib.getValue( CItemFactory::strImage );
		//SIZE sz = CPropertyHelp::stringToSize( strSize );
		strImage = CSystem::GetSingletonPtr()->GetImagePath() + strImage;
		CButtonItem* pItem = new CButtonItem( strImage.c_str(), sz.cx, sz.cy );
		if ( xmlAttrib.exists( CItemFactory::strFunc ) )
		{
			String strFunc = xmlAttrib.getValue( CItemFactory::strFunc );
			pItem->SetFunc( strFunc );
		}
		pBase = pItem;
	}
	else if ( strType == CItemFactory::strExTextItem )
	{
		//SIZE sz = CPropertyHelp::stringToSize( strSize );
		
		String strText = "";
		if ( xmlAttrib.exists( CItemFactory::strText ) )
		{
			strText = xmlAttrib.getValue( CItemFactory::strText );
		}
		CExTextItem* pItem = new CExTextItem( strText, sz.cx, sz.cy );
		if ( xmlAttrib.exists( CItemFactory::strFunc ) )
		{
			String strFunc = xmlAttrib.getValue( CItemFactory::strFunc );
			pItem->SetFunc( strFunc );
		}
		if ( xmlAttrib.exists( strFontName) && xmlAttrib.exists( strFontSize) && xmlAttrib.exists( strFontColor ) )
		{
			String strFontName = xmlAttrib.getValue( CItemFactory::strFontName );
			int nFontSize = xmlAttrib.getValueAsInteger( CItemFactory::strFontSize );
			CPropertyHelp::FontSizeAdp( nFontSize ); //2012-6-19  自适应分辨率下字体也同步自适应变化 by yjj
			String strFontColor = xmlAttrib.getValue( CItemFactory::strFontColor );
			Font* pFont = CSrcManage::GetFont( strFontName.c_str(), nFontSize );
			pItem->SetFont( pFont );
			COLORREF col = CPropertyHelp::stringToColor( strFontColor );
			Color color = Color( GetRValue(col), GetGValue(col), GetBValue( col ) );
			pItem->SetFontColor( color );
		}
		if ( xmlAttrib.exists( CItemFactory::strAlignment) )
		{
			StringAlignment align = xmlAttrib.getValueAsAlignment( CItemFactory::strAlignment );
			pItem->SetAlignment( align );
		}
		if ( xmlAttrib.exists( CItemFactory::strLineAlignment) )
		{
			StringAlignment align = xmlAttrib.getValueAsAlignment( CItemFactory::strLineAlignment );
			pItem->SetLineAlignment( align );
		}
		if ( xmlAttrib.exists( CItemFactory::strSecondFontName ) && xmlAttrib.exists( CItemFactory::strSecondFontSize ) )
		{
			Font* pFont = pItem->GetFont();
			String strFontName = xmlAttrib.getValue( CItemFactory::strSecondFontName );
			int nFontSize = xmlAttrib.getValueAsInteger( CItemFactory::strSecondFontSize );	
			CPropertyHelp::FontSizeAdp( nFontSize ); //地址簿列表第二排会场ID字体大小自适应 2014/11/3
			pFont = CSrcManage::GetFont( strFontName.c_str(), nFontSize );
			Color coFont = pItem->GetFontColor();
			if ( xmlAttrib.exists( CItemFactory::strSecondFontColor) )
			{
				String strFontColor = xmlAttrib.getValue( CItemFactory::strSecondFontColor );
				COLORREF col = CPropertyHelp::stringToColor( strFontColor );
				coFont = Color( GetRValue(col), GetGValue(col), GetBValue( col ) );
			}
			StringAlignment align = pItem->GetAlignment();
			if ( xmlAttrib.exists( CItemFactory::strAlignment) )
			{
				align = xmlAttrib.getValueAsAlignment( CItemFactory::strAlignment );
			}
			String strSecondText = "";
			if ( xmlAttrib.exists( CItemFactory::strSecondText ) )
			{
				strSecondText = xmlAttrib.getValue( CItemFactory::strSecondText );
			}
			pItem->AddText( strSecondText, pFont, coFont, align );
		}
		if ( xmlAttrib.exists( CItemFactory::strSelColor) )
		{
			String strColor = xmlAttrib.getValue( CItemFactory::strSelColor );
			COLORREF col = CPropertyHelp::stringToColor( strColor );
			Color color = Color( GetRValue(col), GetGValue(col), GetBValue( col ) );
			pItem->SetSelColor( color );
		}
		pBase = pItem;
	}
	if ( xmlAttrib.exists( CItemFactory::strLayoutAlgorithm ) )
	{
		String strLayoutAlg = xmlAttrib.getValue( CItemFactory::strLayoutAlgorithm);
		IAlgorithm* pAlg = CAlgorithmFactory::GetAlgorithm( strLayoutAlg );
		if ( pAlg != 0 )
		{
			pBase->SetLayoutAlgorithm( strLayoutAlg );
		}	
	}
	if ( xmlAttrib.exists( CItemFactory::strSortAlgorithm ) )
	{
		String strSortAlg = xmlAttrib.getValue( CItemFactory::strSortAlgorithm);
		IAlgorithm* pAlg = CAlgorithmFactory::GetAlgorithm( strSortAlg );
		if ( pAlg != 0 )
		{
			pBase->SetSortAlgorithm( strSortAlg );
		}	
	}
	if ( xmlAttrib.exists( CItemFactory::strCanDrag ) )
	{
		bool bCanDrag = xmlAttrib.getValueAsBool( CItemFactory::strCanDrag );
		pBase->SetDragStatus( bCanDrag );
	}
	if ( xmlAttrib.exists( CItemFactory::strCanMove ) )
	{
		bool bCanMove = xmlAttrib.getValueAsBool( CItemFactory::strCanMove );
		pBase->SetMoveStatus( bCanMove );
	}
	if ( xmlAttrib.exists( CItemFactory::strAlwaysShow ) )
	{
		bool bShow = xmlAttrib.getValueAsBool( CItemFactory::strAlwaysShow );
		pBase->SetAlwaysShow( bShow );
	}
	return pBase;
}

IBaseItem* CItemFactory::CreateItem( String strType )
{
	XMLAttributes xmlAttribs;
	if ( GetItemInfo( strType, xmlAttribs ) )
	{
		return CreateItem( xmlAttribs );
	}
	return 0;
}

bool CItemFactory::AddItemInfo( String strType, XMLAttributes xmlAttribs )
{
	ItemInfoMap::iterator itr = m_mapItemInfos.find( strType );
	if ( itr == m_mapItemInfos.end() )
	{
		m_mapItemInfos.insert( ItemInfoMap::value_type(strType, xmlAttribs) );
		return true;
	}
	return false;
}

bool CItemFactory::GetItemInfo( String strType, XMLAttributes& xmlAttribs )
{
	ItemInfoMap::iterator itr = m_mapItemInfos.find( strType );
	if ( itr == m_mapItemInfos.end() )
	{
		LOGEVENT( "没有找到该条目" + strType );
		return false;
	}
	xmlAttribs = itr->second;
	return true;
}

}