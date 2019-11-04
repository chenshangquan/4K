// WndMsgEventManage.h: interface for the CWndMsgEventManage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WNDMSGEVENTMANAGE_H__049E4C6D_E3A9_4B99_841E_FAB9EEAF8ACE__INCLUDED_)
#define AFX_WNDMSGEVENTMANAGE_H__049E4C6D_E3A9_4B99_841E_FAB9EEAF8ACE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "uifactorydef.h"
/*---------------------------------------------------------------------
* 类	名：CWndMsgEventManage
* 功    能：窗体消息事件管理类，通过xml文件读取到的消息响应
* 特殊说明：窗体消息相应过程如下
*			窗口ID，找到对应的事件集，从事件集里面找到事件名
*			通过事件名，到全局函数表里面去找对应的事件函数执行
* 修改记录：
* 日期			版本		修改人		修改记录
* 2011/05/13	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
namespace AutoUIFactory
{
class CWndMsgEventManage : public Singleton<CWndMsgEventManage>
{
public:
	const static String strFunc;
	const static String strScript;
public:
	CWndMsgEventManage();
	virtual ~CWndMsgEventManage();
/**  处理Windows消息
 *  @param[in] pMsg window消息
 *  @return 是否成功
 */
	virtual bool TransMsg( WindowMsg* pMsg );

/**  为某一个窗口注册事件
 *  @param[in] wWndId 窗口ID
 *  @param[in] strEvent 事件名称
 *  @param[in] strFunc 事件函数
 *	@param[in] bCover 如果已经注册了是否覆盖
 *  @return 是否成功
 */
	bool RegEvent( HWND hWnd, String strEvent, String strFunc, String strType = CWndMsgEventManage::strFunc, bool bCover = false );

/**  反注册事件
 *  @param[in] wWndId 窗口ID
 *  @param[in] strEvent 事件名称
 *  @return 是否成功
 */
	bool UnRegEvent( HWND hWnd, String strEvent );

/**  UnRegAllEvent
 *   mark  2012.12.3 yjj
 */
	void UnRegAllEvent();

protected:
	typedef pair<String,String>	FuncInfo;
	typedef std::map<String, FuncInfo > EventSet;
	typedef std::map<HWND, EventSet* > EventMap;
/*
 * 事件表，里面存放了一类控件对应的一类事件\n 
 */
	EventMap m_mapEvents;

/*
 * 通过窗口ID获取所属的事件集\n 
 */
	const std::map<String, FuncInfo >* GetFuncMap( HWND hWnd );
};


/*
 * 注册事件 id= 窗口ID event=事件名 func=函数\n
 * 一般这个类是提供给EventTag来用的
 */
#ifndef REG_WND_MSG_EVENT
#define REG_WND_MSG_EVENT( id, event, func, type ) CWndMsgEventManage::GetSingletonPtr()->RegEvent( id, event, func, type );
#endif

/*---------------------------------------------------------------------
* 类	名：CWindowDefaultMsgMap
* 功    能：提供一个从ID到字符串的转换，比如LButtonDown是一个宏，需要转换为字符
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2011/06/02	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
class CWindowDefaultMsgMap
{
public:
	static bool MsgToString( unsigned int wMsg, String& str );
	static bool RegMsg( unsigned int wMsg, String str );
protected:
	typedef std::map< unsigned int, String > DefaultMsgMap;
	static DefaultMsgMap m_mapMsgs;
};

/*
 * 注册从一个ID到一个字符串的映射\n 
 */
#ifndef REG_DEFAULT_WINDOW_MSG
#define REG_DEFAULT_WINDOW_MSG( id ) CWindowDefaultMsgMap::RegMsg( id, #id );
#endif
} // namespace AutoUIFactory end
#endif // !defined(AFX_WNDMSGEVENTMANAGE_H__049E4C6D_E3A9_4B99_841E_FAB9EEAF8ACE__INCLUDED_)
