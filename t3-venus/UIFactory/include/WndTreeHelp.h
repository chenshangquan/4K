// WndTreeHelp.h: interface for the CWndTreeHelp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WNDTREEHELP_H__6FAD23DF_D071_4754_8FF7_59E9654DE4E7__INCLUDED_)
#define AFX_WNDTREEHELP_H__6FAD23DF_D071_4754_8FF7_59E9654DE4E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "templateClass.h"
#include "WindowManage.h"
namespace AutoUIFactory
{

class CWndTreeHelp  
{
public:
/*
 * 分割符号定义\n
 */
	static const char chPartitionChar;
public:
	CWndTreeHelp();
	virtual ~CWndTreeHelp();
	
	/**  获取控件信息
	 *  @param[in] nLevel 哪一层
	 *  @param[in] strName 控件名称
	 *  @param[in] pWndTree 控件树
	 *  @param[in] bPartitionString 是否字符串需要分割
	 *  @return 控件信息
	 */
	static const IWndTree* GetWindow( String strName, const IWndTree* pWndTree );

	/**  获取控件信息
	 *  @param[in] pWnd 窗口指针
	 *  @param[in] pWndTree 所要遍历的树
	 *  @return 返回搜索到的窗口
	 */
	static const IWndTree* GetWindow( Window* pWnd, const IWndTree* pWndTree );
protected:
	/**  在这棵树里面遍历，需要切割传入的字符串
	 *  @param[in] strName 控件名称
	 *  @param[in] pWndTree 控件树
	 *  @return 控件信息
	 */
	static const IWndTree* GetWindowByPartitionString( const String& strName, const IWndTree* pWndTree );
};

} // namespace AutoUIFactory end

#endif // !defined(AFX_WNDTREEHELP_H__6FAD23DF_D071_4754_8FF7_59E9654DE4E7__INCLUDED_)
