// IValue.h: interface for the IValue class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IVALUE_H__7D0A5DF0_E43B_40EF_8028_E9AFD70E0C24__INCLUDED_)
#define AFX_IVALUE_H__7D0A5DF0_E43B_40EF_8028_E9AFD70E0C24__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "uifactorydef.h"
#include "ItemFactory.h"

// dynamic_cast
namespace AutoUIFactory
{
/*---------------------------------------------------------------------
* 类	名：IValue
* 功    能：值的基类 一般它会和property一起被定义
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2011/06/02	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
Interface IValue  
{
public:
	IValue( String strType );
	virtual ~IValue();
	String GetType() const { return m_strType; } 

protected:
	String m_strType;
};


//列表中创建Item所需参数
class Args_BuildItem : public IArgs
{
public:  
	IItemList* pList;
	BOOL32 bDrag;					//该item是否可以拖动
	int nKey;						//该item在其当前层的列表中所占的次序
	String strTxt;					//item上显示的字符串
	IData* pUserData;				//用户信息，主要用于点击时产生的click事件的参数
	String strClickItemFunc;		//点击事件
	vector<String>* pVctSubItem;		//item上显示的图标
	String strImageItem ;			//对应的imgItem类型
	String strTxtItem;				//对应的txtItem类型
	String strLayoutAlgorithm;		//item的布局算法
	EmItemStatus emItemStatus;		//item状态
	
	Args_BuildItem( ):IArgs("BuildItem" )
	{
		pList = NULL;
		bDrag = FALSE;
		nKey =-1;
		strTxt.erase();
		pUserData = 0;
		strClickItemFunc.erase();
		pVctSubItem  = NULL;
		strImageItem ="";
		strTxtItem = "";
		strLayoutAlgorithm= IAlgorithm::strNormalItem ;
		emItemStatus = emItemStatusNormal; 
	}
};

/*---------------------------------------------------------------------
* 类	名：Value_ListBase
* 功    能：主要用于列表数据
* 特殊说明：外部使用时，只需继承该类，并根据自己的数据类型实现SetData即可完成对列表的赋值
* 修改记录：
* 日期			版本		修改人		修改记录
* 2012/12/18	v1.0	    俞锦锦		创建
----------------------------------------------------------------------*/
//菜单型列表
class Value_ListBase:public IValue
{
public:
	Value_ListBase():IValue("TransparentListData"){} 
	
	virtual bool SetData( IItemList* pList ){return true;} 

	//列表中数据排序，默认字符串升序来排
	virtual bool CompareListData( LPTSTR str1, LPTSTR str2, BOOL bAsc = TRUE );

protected:
	//根据agrs创建列表
	bool BuildItem(  Args_BuildItem &agrs );

	
 
};


} // namespace AutoUIFactory end
#endif // !defined(AFX_IVALUE_H__7D0A5DF0_E43B_40EF_8028_E9AFD70E0C24__INCLUDED_)
