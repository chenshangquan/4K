// System.h: interface for the CSystem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSTEM_H__0A0675EB_2D2B_4BCD_9310_F9D9A7038FDB__INCLUDED_)
#define AFX_SYSTEM_H__0A0675EB_2D2B_4BCD_9310_F9D9A7038FDB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*
 * @defgroup System 系统类，统管所有创建工作
 * @author  牟兴茂
 * @version 1.0
 * @date  2011/05/31
 * @{
 */
 
#include "uifactorydef.h"
#include "Logger.h"
#include "templateClass.h"
#include "WindowFacotryManage.h"
#include "XmlAttrib.h"
#include "IScript.h"
#include "WindowManage.h"
namespace AutoUIFactory
{

class IXmlParser;
class IScript;

typedef std::multimap<String, XMLAttributes> SystemInfoMultiMap;
class Args_SystemObserver : public IArgs
{
public:
	Args_SystemObserver( SystemInfoMultiMap& mapSystemInfo ) : IArgs( "SystemObserver" ), m_mapSystemInfos( mapSystemInfo ){}
	SystemInfoMultiMap&		m_mapSystemInfos;
};
/*---------------------------------------------------------------------
* 类	名：CSystem
* 功    能：作为UIFactory的总管
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2011/06/02	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
class CSystem : public Singleton<CSystem>
{
public:
	friend class CWindowManage;
	friend class CSystemXmlHandle;
	friend class XmlSaveDocument;
	static const String strWndParent;
	static const String strName;
	static const String strValue;
public:
	/**  
	 *  @param[in] strMainXml 主xml路径(包含一些系统用信息)
	 *  @param[in] piScript 脚本执行模块
	 *  @param[in] IXmlParser xml解析类
	 *  @deprecated 这是一个单例类，只需要在整个调用的程序里面new一次就可以
	 */
	CSystem( String strMainXml = "", IScript* piScript = 0, IXmlParser* pXmlParser = 0 );
	virtual ~CSystem();

	void AddObserver( IObserver* piObserver );
	
	void Launch();
public:
	
	void SetImagePath( String strPath );
	String GetImagePath();

	/**  设置系统布局文件路径
	 *  @param[in] strPath 路径
	 *  @return 
	 */
	void SetLayoutPath( String strPath );
	String GetLayoutPath();

	/**  设置ItemInfo文件路径
	 *  @param[in] strPath 路径
	 *  @return 
	 */
	void SetItemInfoPath( String strPath );
	String GetItemInfoPath();

    /**  获取Edit默认字体信息
	 *  @return 
	 */
    TFontInfo GetEditFontInfo();

    /**  获取Static默认字体信息
	 *  @return 
	 */
    TFontInfo GetStaticFontInfo();

public:
		/**  读取ui配置文件
	 *  @param[in] strLayout 
	 *  @return 是否读取成功
	 *  @deprecated 
	 */
	bool ReadLayoutXml( String strLayout );

	/**  获取一个窗口对应的xml路径
	 *  @param[in] strName 窗口名称
	 *  @param[out] strXml 路径
	 *  @return 是否读取成功
	 */
	bool GetWindowXml( String strName, XMLAttributes& attrib );

    /**  获取一个窗口对应的xml路径
	 *  @param[in] strName 窗口名称
	 *  @param[out] strXml 路径
	 *  @return 是否读取成功
	 */
	String GetWindowXml( String strName );
	
	/**  添加一个文件路径到列表中
	 *  @param[in] strName 文件名
	 *  @param[in] strPath 文件路径
	 *  @return 是否添加成功
	 */
	bool AddWindowXml( String strName, const XMLAttributes& attrib );
protected:
	/**  读写主xml文件
	 *  @param[in] strMainXml 文件路径
	 *  @return 读取是否成功
	 *  @deprecated 如果读取错误，系统将无法使用
	 */
	bool ReadMainXml( String strMainXml );

	bool AddSystemInfo( String strElement, const XMLAttributes& attrib );

	void Update();

protected:
	/*
	 * 脚本解析模块  
	 */
	IScript* m_pScript;
	
	/*
	 * xml解析模块  
	 */
	IXmlParser* m_pXmlParser;	

	/*
	 * 记录所有窗体对应的xml文件  
	 */
	SystemInfoMultiMap		m_mapSystemInfos;

	/*
	 * 系统初始化后需要通知的对象\n 
	 */
	typedef std::vector<IObserver*> ObserverVec;
	ObserverVec				m_vecObservers;

	String m_strMainXml;
};
} // namespace AutoUIFactory end

/** @} */ 
#endif // !defined(AFX_SYSTEM_H__0A0675EB_2D2B_4BCD_9310_F9D9A7038FDB__INCLUDED_)
