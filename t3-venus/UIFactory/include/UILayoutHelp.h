// UILayoutHelp.h: interface for the CUILayoutHelp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UILAYOUTHELP_H__A9262EDB_ED17_4A47_9455_E0DA12A70182__INCLUDED_)
#define AFX_UILAYOUTHELP_H__A9262EDB_ED17_4A47_9455_E0DA12A70182__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "uifactorydef.h"
#include "templateClass.h"
namespace AutoUIFactory
{
/*---------------------------------------------------------------------
* 类	名：CUILayoutHelp
* 功    能：用于动态调整UI布局的类，需要在xml进行相应的配置才可以
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2011/06/09	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
class CUILayoutHelp  
{
public:
	const static String strLeft;
	const static String strRight;
	const static String strTop;
	const static String strBottom;
	const static String strCenter;
	const static char chPartitionChar;
public:
	CUILayoutHelp();
	virtual ~CUILayoutHelp();
/**  进行UI布局
 *  @param[in] strWndName		所要布局窗口的名称
 *	@param[in] bRecurrence		是否要遍历该窗口下所有窗口
 *  @return 是否成功
 */
	static bool LayoutUI( const String& strWndName, bool bRecurrence = true );

/**  进行UI布局
 *  @param[in] pWnd				窗口指针
 *	@param[in] bRecurrence		是否要遍历该窗口下所有窗口
 *  @return 是否成功
 */
	static bool LayoutUI( const Window* pWnd, bool bRecurrence = true );

/**  进行UI布局
 *  @param[in] pWndTree			控件树
 *	@param[in] bRecurrence		是否要遍历该窗口下所有窗口
 *  @return 是否成功
 */
	static bool LayoutUI( const IWndTree* pWndTree, bool bRecurrence = true );

protected:
/**  Layout
 *  @param[in] 
 *  @param[in] 
 *  @param[out] 
 *  @return 是否成功
 */
	static bool Layout( WndInfo* pWndInfo );
};

} // namespace AutoUIFactory end
#endif // !defined(AFX_UILAYOUTHELP_H__A9262EDB_ED17_4A47_9455_E0DA12A70182__INCLUDED_)
