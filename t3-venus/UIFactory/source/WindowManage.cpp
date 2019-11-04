// WindowManage.cpp: implementation of the CWindowManage class.
//
//////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "System.h"
#include "WindowManage.h"
#include "windowfactory.h"
#include "WindowFacotryManage.h"
#include "WndTreeHelp.h"
#include "MfcDefaultArgs.h"
#include "UILayoutHelp.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace AutoUIFactory
{
template<> CWindowManage* Singleton<CWindowManage>::ms_pSingleton  = 0;
const String WndInfo::strDefaultScheme = "";
CWindowManage::CWindowManage()
{
	m_pRoot = new CItemGroup< WndInfo, String >();
}

CWindowManage::~CWindowManage()
{

}

Window* CWindowManage::Create( IArgs& iArgs )
{
	try 
	{
		Args_WindowCreate& args = dynamic_cast<Args_WindowCreate&>(iArgs);
		const IWindowFactory* piWindowFactory = CWindowFacotryManage::GetSingletonPtr()->GetFactory( args.m_strType );
		if ( piWindowFactory == 0 )
		{
			LOGEVENT( "没有找到对应的工厂" + args.m_strType );
			return 0;
		}
		return const_cast<IWindowFactory*>(piWindowFactory)->Create( args );
	}
	catch( bad_cast )
	{
		LOGEVENT( "CWindowManage::Create 传入的参数不正确" );
		return false;
	}
}

const IWndTree* CWindowManage::GetWindowTree( String strName )
{	
	// 有些窗口并不一定要写在单独的xml文件里面，但是也可以创建，这种窗体直接在根目录取
	IWndTree* piWndTree = const_cast<IWndTree*>( CWndTreeHelp::GetWindow( strName, m_pRoot ) );
	if ( piWndTree != 0 )
	{
		return piWndTree;
	}

    XMLAttributes xmlAttrib;
    bool bResult = CSystem::GetSingletonPtr()->GetWindowXml( strName, xmlAttrib );

    if ( bResult == false)
    {
		
		CString str = "";
		str.Format("\r\n[CWindowManage::GetWindowTree] GetWindowXml(%s) 失败\r\n", strName.c_str() );
		LOGEVENT(str);
        return 0;
    }
    String strParent = xmlAttrib.getValue( CSystem::strWndParent );
    IWndTree* piParentWndTree  =  const_cast<IWndTree*>( CWndTreeHelp::GetWindow( strParent, m_pRoot ) );
    if ( piParentWndTree == 0 )
    {
        piParentWndTree = m_pRoot;
    }
	piWndTree = piParentWndTree->GetItemByKey( strName );

	if ( piWndTree == 0 )
	{
		if ( CSystem::GetSingletonPtr()->ReadLayoutXml( strName ) == false )
		{
			LOGEVENT( "CWindowManage::GetWindow 尝试创建窗体失败 name= " + strName );
			return 0;
		}
		piWndTree = piParentWndTree->GetItemByKey( strName );
		if ( piWndTree != 0 )
		{
			CUILayoutHelp::LayoutUI( piWndTree );
		}
	}
	return piWndTree;
}



bool CWindowManage::DestoryWnd( Window* pWnd )
{
	const IWndTree* pWndTree = CWndTreeHelp::GetWindow( pWnd, m_pRoot );
	return DestoryWnd( const_cast<IWndTree*>(pWndTree) );
}

bool CWindowManage::DestoryWnd( IWndTree* pWndTree )
{
	if ( pWndTree == 0 )
	{
		return false;
	}
	IWndTree* pParent = pWndTree->GetParentItem();
	if ( pParent == 0 )
	{
		return false;
	}
	WndInfo* pWndInfo = pWndTree->GetItemData();
	if ( pWndInfo == 0 )
	{
		return false;
	}
	Window* pWnd = pWndInfo->pWnd;
	//在删除窗口对象之前销毁窗口2012.12.3 yjj
	if ( pWnd != 0 )
	{ 
        pWnd->SendMessage( WM_CLOSE, 0 , 0 );  
	 
	}	
   
	bool bResult = pParent->DeleteItem( pWndTree->GetItemName() );
 
	
	
	return bResult;	
}


bool CWindowManage::DestoryAllWnd()
{
	int n = m_pRoot->GetItemCount();
	for ( int i = 0; i< n; i++ )
	{
		IWndTree* pWnd = m_pRoot->GetItemByIndex( i );
		DestoryWnd( pWnd );
	}
	return true;
}

WndInfo::WndInfo()
{ 
	m_nIndex = 0; 
	m_schemeMap = new CItemGroup< CTagInfo,int>();
	m_pCurScheme = 0;
	m_strCurUseScheme = WndInfo::strDefaultScheme;
}

WndInfo::~WndInfo()
{	
	m_schemeMap->DeleteAllItem();
	delete m_schemeMap;
	m_schemeMap = 0;	
}

WndInfo* WndInfo::Clone()
{
	WndInfo* pInfo = new WndInfo;
	pInfo->strType = strType;
	pInfo->pWnd = pWnd;
	pInfo->m_schemeMap = m_schemeMap->Clone();
	pInfo->m_pCurScheme = pInfo->m_schemeMap->GetItemByKey( m_pCurScheme->GetItemName() );
	pInfo->m_nIndex = m_nIndex;
	pInfo->m_strCurUseScheme = m_strCurUseScheme;
	return pInfo;
}

void WndInfo::AddScheme( String strName, XMLAttributes xmlAttributes )
{
	m_nIndex++;
	m_pCurScheme = m_schemeMap->AddItem( m_nIndex, &CTagInfo( strName, xmlAttributes ), emGroup );
}

void WndInfo::AddAttribs( String strName, XMLAttributes xmlAttributes )
{
	if ( m_pCurScheme == 0 )
	{
		return;
	}
	static int nIndex = 0;
	nIndex++;	
	m_pCurScheme->AddItem( nIndex, &CTagInfo( strName, xmlAttributes ), emGroup );
}

SchemeMap* WndInfo::GetSchemeMap( String strName )
{
	if ( m_schemeMap == 0 )
	{
		return false;
	}
	int nCounts = m_schemeMap->GetItemCount();
	for ( int i = 0; i < nCounts; i++ )
	{
		SchemeMap* pSub = m_schemeMap->GetItemByIndex( i );
		if ( pSub != 0 )
		{
			CTagInfo* pTagInfo = pSub->GetItemData();
			if ( pTagInfo != 0 && pTagInfo->m_strTag == strName )
			{
				return pSub;
			}
		}
	}
	return 0;
}

void WndInfo::EndScheme()
{
    if ( m_pCurScheme == 0 )
    {
        return;
	}
    m_pCurScheme = GetSchemeMap( strDefaultScheme );
}

} // namespace AutoUIFactory end
