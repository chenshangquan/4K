// IBaseItem.cpp: implementation of the IBaseItem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h" 
#include "iBaseItem.h"
#include "srcManage.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const String IBaseItem::strNormalImg = "Normal.png";
const String IBaseItem::strDownImg = "Down.png";
const String IBaseItem::strDisableImg = "Disable.png"; 
const String IBaseItem::strSelImg = "Sel.png";
const String IBaseItem::strOverImg = "Over.png";

const String IBaseItem::strDefaultFunc = "";
IBaseItem::IBaseItem( int nWidht, int nHeight, String strFunc, 
					 String strLayout, String strSort, 
		bool bCanDrag, bool bCanMove, CPoint ptOffset, EmItemStatus emItemStatus, bool bAlwaysShow ) :   
m_emItemStatus( emItemStatus ), m_strFunc( strFunc ), m_strLayoutAlgorithm( strLayout ), m_strSortAlgorithm( strSort ), 
m_bCanDrag( bCanDrag ), m_bCanMove( bCanMove ), m_ptOffset( ptOffset ), m_bAlwaysShow( bAlwaysShow )
{
	m_rcItem.SetRect( 0, 0, nWidht, nHeight );
	m_pData = NULL;
}

IBaseItem::~IBaseItem()
{  
	if ( m_pData != NULL )
	{
		delete m_pData;
		m_pData = NULL;
	}
}

IBaseItem::IBaseItem(const IBaseItem& item)
{
	if (this == &item)
    {
        return;
    }
    *this = item;
}

bool IBaseItem::ExeFunc()
{
	return true;
}

const IData* IBaseItem::GetUserData()
{
	return m_pData;
}

void IBaseItem::SetUserData( IData* pData )
{
	if ( m_pData != NULL )
	{
		delete m_pData;
		m_pData = NULL;
	}
	
	if ( pData != NULL )
	{
		m_pData = pData->Clone();
	}
}
 
