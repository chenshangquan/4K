/*---------------------------------------------------------------------
* 类	名：CListFuncManage
* 功    能：列表回调函数管理类
* 特殊说明：用于注册列表响应函数
* 修改记录：
* 日期			版本		修改人		修改记录
* 2012/12/05	v1.0		肖楚然		创建
----------------------------------------------------------------------*/

#if !defined(AFX_LISTFUNCMANAGE_H__6CD44751_8882_4EE4_89D2_C7367CB5C255__INCLUDED_)
#define AFX_LISTFUNCMANAGE_H__6CD44751_8882_4EE4_89D2_C7367CB5C255__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "uiexBaseData.h"

class CListFuncManage : public ISingleTon< CListFuncManage > 
{
public:
	CListFuncManage();
	virtual ~CListFuncManage();

    /**  注册全局函数
    *  @param[in] strName 函数所对应的名称 必须唯一
    *  @param[in] piFunc 函数指针，可以是静态函数，可以是成员函数等
    *  @return 是否成功
    */
	bool RegFunc( String strName, ICallBackFuncBase* piFunc );

    /**  反注册全局函数
    *  @param[in] strName 函数所对应的名称
    *  @return 是否成功
    */
	bool UnRegFunc( String strName );

    /**  反注册所有全局函数 
    *  @return 是否成功
    *  @mark 用于推出uifactory时使用，释放new的内存  yjj
    */
	void UnRegAllFunc();

    /**  执行函数
    *  @param[in] strName 函数名
    *  @param[in] args 参数 可以根据自己需要进行添加
    *  @see IArgs
    *  @param[out] 
    *  @return 是否成功
    */
	bool ExeFunc( String strName, const IArgs& args );
protected:
	typedef std::map< String, ICallBackFuncBase* > FuncMap;
/*
 * 全局函数map表\n 
 */
	FuncMap m_mapFuncs;
};

/*
* 注册列表回调函数、以类成员函数作为函数指针 \n
* str 函数标示 func 函数名 obj 类指针 objType 类类型
*/
#ifndef REG_LIST_CALLFUNC
#define REG_LIST_CALLFUNC( str, func, obj, objType ) \
CListFuncManage::GetSingletonPtr()->RegFunc( str, new CMemberCallBackFunc<objType>( func, obj ) );
#endif

/*
* 反注册列表回调函数 \n
* str 函数标示
*/
#ifndef UN_REG_LIST_CALLFUNC
#define UN_REG_LIST_CALLFUNC( str ) CListFuncManage::GetSingletonPtr()->UnRegFunc( str );
#endif

#endif // !defined(AFX_LISTFUNCMANAGE_H__6CD44751_8882_4EE4_89D2_C7367CB5C255__INCLUDED_)
