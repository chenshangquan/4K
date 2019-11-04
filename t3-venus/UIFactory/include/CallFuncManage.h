// CallFuncManage.h: interface for the CCallFuncManage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALLFUNCMANAGE_H__449890B2_C187_4CF4_B88F_E4C3A5A6FF0D__INCLUDED_)
#define AFX_CALLFUNCMANAGE_H__449890B2_C187_4CF4_B88F_E4C3A5A6FF0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace AutoUIFactory
{
/*---------------------------------------------------------------------
* 类	名：CFuncManage
* 功    能：管理全局函数指针的一个地方
* 特殊说明：名字必须唯一
* 修改记录：
* 日期			版本		修改人		修改记录
* 2011/06/02	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
class CFuncManage : public Singleton< CFuncManage >
{
public:
	CFuncManage();
	virtual ~CFuncManage();
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
 *  @mark 用于推出uifactory时使用，释放new的内存 2012.12.3 yjj
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
* 注册全局函数、以类成员函数作为函数指针 \n
* str 函数标示 func 函数名 obj 类指针 objType 类类型
*/
#ifndef REG_GOBAL_MEMBER_FUNC
#define REG_GOBAL_MEMBER_FUNC( str, func, obj, objType ) \
CFuncManage::GetSingletonPtr()->RegFunc( str, new CMemberCallBackFunc<objType>( func, obj ) );
#endif

/*
* 注册全局函数、以全局或者静态函数作为函数指针 \n
* str 函数标示 func 函数名
*/
#ifndef REG_GOBAL_STATIC_FUNC 
#define REG_GOBAL_STATIC_FUNC( str, func ) \
CFuncManage::GetSingletonPtr()->RegFunc( str, new CCallBackFunc( func ) );
#endif

/*
* 反注册全局函数 \n
* str 函数标示
*/
#ifndef UN_REG_GOBAL_FUNC
#define UN_REG_GOBAL_FUNC( str ) CFuncManage::GetSingletonPtr()->UnRegFunc( str );
#endif
} // namespace AutoUIFactory end
#endif // !defined(AFX_CALLFUNCMANAGE_H__449890B2_C187_4CF4_B88F_E4C3A5A6FF0D__INCLUDED_)

