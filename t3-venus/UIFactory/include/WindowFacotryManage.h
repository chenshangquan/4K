// WindowFacotryManage.h: interface for the CWindowFacotryManage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINDOWFACOTRYMANAGE_H__5220EE0A_4FC2_4C36_90F8_A46CEDEE8F20__INCLUDED_)
#define AFX_WINDOWFACOTRYMANAGE_H__5220EE0A_4FC2_4C36_90F8_A46CEDEE8F20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "uifactorydef.h"
#include "templateClass.h"
#include "windowfactory.h"

namespace AutoUIFactory
{
/*---------------------------------------------------------------------
* 类	名：CWindowFacotryManage
* 功    能：工厂管理类
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2011/06/02	v1.0		牟兴茂		创建
-----s-----------------------------------------------------------------*/
class CWindowFacotryManage : public Singleton< CWindowFacotryManage >
{
public:
	CWindowFacotryManage();
	virtual ~CWindowFacotryManage();
public:
/**  添加一个工厂
 *  @param[in] strType工厂类型
 *  @param[in] pWindowFactory
 *  @return 是否成功
 */
	bool AddFactory( String strType, IWindowFactory* pWindowFactory, bool bCover = false );
/**  获得一个工厂
 *  @param[in] strType工厂类型
 *  @return 工厂指针
 */
	const IWindowFactory* GetFactory( String strType );

/**  销毁所有工厂类型  
 *  @mark 2012.12.3 yjj
 */
	void ClearFactory( );



protected:
	typedef std::map<std::string, IWindowFactory* > FactoryMap;
/*
 * 工厂map表\n 
 */
	FactoryMap m_mapFactories;
};

/*
 * 注册一个工厂 name=类型 class=类名\n 
 * 为了保证命名一致，所以注册的时候需要按照要求填写宏
 * 如果不想用这样的明明方式，可以写其他宏，或者直接调用对应函数
 */
#define REG_WINDOW_FACTORY( name ) \
	CWindowFacotryManage::GetSingletonPtr()->AddFactory( #name, new name##Factory )
} // namespace AutoUIFactory end
#endif // !defined(AFX_WINDOWFACOTRYMANAGE_H__5220EE0A_4FC2_4C36_90F8_A46CEDEE8F20__INCLUDED_)
