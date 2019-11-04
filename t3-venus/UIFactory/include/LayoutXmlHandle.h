// LayoutXmlHandle.h: interface for the CLayoutXmlHandle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LAYOUTXMLHANDLE_H__C9E3A152_E2BA_450F_9551_195E9AE54A2A__INCLUDED_)
#define AFX_LAYOUTXMLHANDLE_H__C9E3A152_E2BA_450F_9551_195E9AE54A2A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "uifactorydef.h"
#include "IXmlHanlde.h"
#include "ITag.h"

#include "WindowManage.h"

namespace AutoUIFactory
{
/*---------------------------------------------------------------------
* 类	名：CLayoutHandle
* 功    能：专门用于解析布局xml文件的类
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2011/06/02	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
class CLayoutHandle : public IXmlHanlde
{
public:
	const static String strCreateWindow;
	const static String strProperty;
	const static String strEvent;
	const static String strCallBackFunc;
	const static String strLayout;
	const static String strScheme;
public:
	CLayoutHandle();
	~CLayoutHandle();
/*---------------------------------------------------------------------
* 函 数 名：ElementStart
* 功    能：读写布局标签
* 参数说明：
* 返 回 值：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2011/05/11	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
	bool ElementStart( String strElement, const XMLAttributes& xmlAttributes );
	bool ElementEnd( String strElement );

/*---------------------------------------------------------------------
* 函 数 名：ClearTags
* 功    能：清空所有tag，释放内存 
* 参数说明：
* 返 回 值：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2012/12/3  	v1.0		俞锦锦		创建
----------------------------------------------------------------------*/
	void ClearTags();

public:
/*---------------------------------------------------------------------
* 函 数 名：AppendWindow
* 功    能：添加窗口
* 参数说明：
* 返 回 值：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2011/05/12	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
	bool AppendWindow( Window* pWnd, String strName, XMLAttributes xmlAttribs );
	bool PopWindow();
	const Window* GetCurWindow();
	
	void SetCurWnd( Window* pWnd )
	{
		m_pCurWindow = pWnd;
		m_stackWnd.push_back( pWnd );
	}

	void SetCurWndTree( IWndTree* pWndTree );

	const IWndTree* GetCurWindowTree();

	bool AddXmlTag( String strElement, IXmlTag* pXmlTag );
protected:
	bool AppendWindowInTree( Window* pWnd, String strName, XMLAttributes xmlAttribs );
	bool PopWindowFromTree();
/*---------------------------------------------------------------------
* 函 数 名：IniTags
* 功    能：添加默认标签处理
* 参数说明：
* 返 回 值：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2011/05/12	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
	bool IniDefaultTags();

	
protected:

	typedef std::map<String, IXmlTag*> TagMap;
	TagMap	m_mapTags;

/*
 * 窗口的一个堆栈，随着xml的解析，永远都能知道该对哪个窗口进行设置\n 
 */
	typedef std::vector<Window*> WindowStack;
	WindowStack m_stackWnd;
	Window* m_pCurWindow;

/*
 * 当前的一个IWndTree的堆栈，遇到start添加，遇到end出栈\n 
 */
	typedef std::vector<IWndTree*> WndTreeStack;
	WndTreeStack m_stackWndTree;
	IWndTree* m_pCurWndTree;

public:
	bool m_bInScheme;
};

} // namespace AutoUIFactory end

#endif // !defined(AFX_LAYOUTXMLHANDLE_H__C9E3A152_E2BA_450F_9551_195E9AE54A2A__INCLUDED_)
