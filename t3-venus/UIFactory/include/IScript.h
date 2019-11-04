// IScript.h: interface for the IScript class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ISCRIPT_H__5142ED78_9EC4_4E00_A49B_86D0DFA8E5F8__INCLUDED_)
#define AFX_ISCRIPT_H__5142ED78_9EC4_4E00_A49B_86D0DFA8E5F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*---------------------------------------------------------------------
* 类	名：IScript
* 功    能：脚本执行类
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2011/05/11	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
namespace AutoUIFactory
{

Interface IScript : public Singleton<IScript>
{
public:
	IScript();
	virtual ~IScript();
	/*
		strScript 脚本文本、nType 脚本类型(函数、脚本)
	*/
	virtual bool ExecuteScript( String strScript, String strType = "" ) = 0;
};

} // namespace AutoUIFactory end
#endif // !defined(AFX_ISCRIPT_H__5142ED78_9EC4_4E00_A49B_86D0DFA8E5F8__INCLUDED_)
