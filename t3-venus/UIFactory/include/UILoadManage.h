// UILoadManage.h: interface for the CUILoadManage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UILOADMANAGE_H__F943A576_E87E_4418_97C6_4AEDD36944AB__INCLUDED_)
#define AFX_UILOADMANAGE_H__F943A576_E87E_4418_97C6_4AEDD36944AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace AutoUIFactory
{

class CUILoadManage : public IObserver, public Singleton<CUILoadManage>
{
public:
	static const String strName;	
	static const String strValue;
	static const String strType;
public:
	CUILoadManage();
	virtual ~CUILoadManage();

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

    String GetWindowXml( String strName ); //2011-11-16 by yjj
	
	/**  添加一个文件路径到列表中
	 *  @param[in] strName 文件名
	 *  @param[in] strPath 文件路径
	 *  @return 是否添加成功
	 */
	bool AddWindowXml( String strName, const XMLAttributes& attrib );

	/**  添加系统信息
	 *  @param[in] strElement 信息名
	 *  @param[in] attrib 信息数据
	 *  @return 是否添加成功
	 */

	void Update( IArgs* pArgs );
protected:
	void Update( XMLAttributes& xmlAttribs );

	typedef std::map< String, XMLAttributes > WindowAttribMap;
	WindowAttribMap m_mapWindowAttribs;
};

}
#endif // !defined(AFX_UILOADMANAGE_H__F943A576_E87E_4418_97C6_4AEDD36944AB__INCLUDED_)
