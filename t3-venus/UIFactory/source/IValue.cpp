// IValue.cpp: implementation of the IValue class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "System.h"
#include "IValue.h"
#include "chartoPY.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace AutoUIFactory
{
IValue::IValue(String strType) : m_strType( strType )
{
}

IValue::~IValue()
{

}

bool Value_ListBase::BuildItem(  Args_BuildItem &agrs )
{    
	IBaseItem* pItem = CItemFactory::GetSingletonPtr()->CreateItem( agrs.strImageItem );
	if ( NULL == pItem )
	{
		
		return false;
	}
	pItem->SetLayoutAlgorithm( agrs.strLayoutAlgorithm ); 
	pItem->SetDragStatus(agrs.bDrag); 
	pItem->SetUserData(agrs.pUserData); 
	//点击条目后 
	if ( ! agrs.strClickItemFunc.empty() )
	{
		pItem->SetFunc( agrs.strClickItemFunc );
	} 
	
	pItem->SetItemStatus( agrs.emItemStatus );
	IItemList *pNew  = agrs.pList->ModifyItem( agrs.nKey, pItem );  //添加 一个条目  
	delete pItem;
	pItem = 0;
	
	//条目中添加一个字符串 
	IBaseItem* pSubItem= CItemFactory::GetSingletonPtr()->CreateItem( agrs.strTxtItem );
	if ( CTextItem * pTextItem = dynamic_cast<CTextItem*>(pSubItem)  )
	{
		pTextItem->SetText( agrs.strTxt ); 
		pNew->ModifyItem(0,pSubItem );
	}   
	delete pSubItem;
	pSubItem = 0; 
	
	// 添加 图标
	if ( agrs.pVctSubItem == NULL || agrs.strTxt.empty())
	{ 
		return true;
	}
	
	vector<String>::iterator it = agrs.pVctSubItem->begin();
	int i = 1;
	while ( it != agrs.pVctSubItem->end() )
	{   
		pSubItem= CItemFactory::GetSingletonPtr()->CreateItem( *it ); 
		pNew->ModifyItem(i++,pSubItem ); 
		delete pSubItem;
		pSubItem = 0;
		it++;
	}
	
	return true;
}

bool Value_ListBase::CompareListData( LPTSTR str1, LPTSTR str2 , BOOL bAsc /*= TRUE */)
{

	if ( str1 == str2 )
	{
		return true;
	}
	
    CString strLetter1;
    CString strLetter2;	
	
	CCharToPY::GetFirstLetter( str1, strLetter1 );
	CCharToPY::GetFirstLetter( str2, strLetter2 );
	bool bRe = false;

	if ( bAsc )
	{
		if ( strLetter1.Compare( strLetter2 ) < 0  )
		{
			bRe = true;
		}
	}

	if ( !bAsc )
	{
		if ( strLetter1.Compare( strLetter2 ) > 0  )
		{
			bRe = true;
		}
	}
 
	return bRe;
	 
}

} // namespace AutoUIFactory end
