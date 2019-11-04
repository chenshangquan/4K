// WindowManage.h: interface for the CWindowManage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINDOWMANAGE_H__D64B4440_822E_4154_A06C_BD2CB1DFDC20__INCLUDED_)
#define AFX_WINDOWMANAGE_H__D64B4440_822E_4154_A06C_BD2CB1DFDC20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "uifactorydef.h"
#include "windowfactory.h"
/*---------------------------------------------------------------------
* 类	名：CWindowManage
* 功    能：用于管理和创建窗体
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2011/05/11	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
namespace AutoUIFactory
{
	class CTagInfo
	{
	public:
		CTagInfo( String strTag, XMLAttributes xmlAttribs ) : m_strTag( strTag ), m_xmlAttribs( xmlAttribs ){}
		String m_strTag;
		XMLAttributes m_xmlAttribs;
		CTagInfo* Clone()
		{
			CTagInfo* pTagInfo = new CTagInfo( m_strTag, m_xmlAttribs );
			return pTagInfo;
		}
	};
typedef IItem<CTagInfo,int> SchemeMap;
class WndInfo
{
public:
	static const String strDefaultScheme;
public:
	WndInfo();
	~WndInfo();
	
	String strType;
	Window* pWnd;
	
	void AddScheme( String strName, XMLAttributes xmlAttributes );
	void AddAttribs( String strName, XMLAttributes xmlAttributes );

	WndInfo* Clone();
	SchemeMap* GetSchemeMap( String strName );

	void SetCurUseScheme( String str ){ m_strCurUseScheme = str; }
	String GetCurUseScheme(){ return m_strCurUseScheme; }

    void EndScheme();//执行完一个Scheme
private:
	int m_nIndex;
	SchemeMap* m_pCurScheme;
	SchemeMap* m_schemeMap;
	String m_strCurUseScheme;
};

typedef IItem< WndInfo, String > IWndTree;

class CWindowManage : public Singleton<CWindowManage>
{
public:
	CWindowManage();
	virtual ~CWindowManage();
/**  
 *  @param[in] strType 窗口类型，如：Window，Button
 *  @param[in] strName 窗口名字
 *  @param[in] pParent 父窗口
 *  @return 窗口指针
 */
	Window* Create( IArgs& iArgs );
public:
/**  通过名字获得根节点下面的窗口树，如果需要获取窗口树下面的其他控件，请参看CWndTreeHelp
 *  @param[in] strName 窗口名称
 *  @return 窗口树指针
 */
	const IWndTree* GetWindowTree( String strName );
/**  获取跟节点
 *  @return 返回根节点
 */
	IWndTree*	GetRoot() const { return m_pRoot; }
/**  销毁窗口，这里会调用CWnd的Destory
 *  @param[in] pWnd 窗口指针
 *  @return 是否销毁成功
 */
	bool DestoryWnd( Window* pWnd );
/**  销毁窗口，这里会调用CWnd的Destory
 *  @param[in] pWndTree 窗口树
 *  @return 是否销毁成功
 */
	bool DestoryWnd( IWndTree* pWndTree );

	/**  销毁所有窗口窗口，这里会调用CWnd的Destory
 *  @param[in] pWndTree 窗口树
 *  @return 是否销毁成功
 *  @auth yjj 2011.11.30
 */
	bool DestoryAllWnd();
protected:
/*
 * 根节点\n
 */
	IWndTree* m_pRoot;
};


} // namespace AutoUIFactory end
#endif // !defined(AFX_WINDOWMANAGE_H__D64B4440_822E_4154_A06C_BD2CB1DFDC20__INCLUDED_)
