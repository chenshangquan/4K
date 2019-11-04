// SystemInfoManage.cpp: implementation of the CSystemInfoManage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "System.h"
#include "SystemInfoManage.h"
#include "PropertyHelp.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace AutoUIFactory
{
const String CSystemInfoManage::strSystemInfo = "SystemInfo";
const String CSystemInfoManage::strVersion = "Version";
const String CSystemInfoManage::strName = "Name";
const String CSystemInfoManage::strValue = "Value";
const String CSystemInfoManage::strImagePath = "ImagePath";
const String CSystemInfoManage::strLayoutPath = "LayoutPath";
const String CSystemInfoManage::strItemInfo = "ItemInfo";
const String CSystemInfoManage::strResolution = "DefaultResolution";//默认分辨率
const String CSystemInfoManage::strBeSelAdpResolution = "IsSelAdpResolution"; //是否自适应分辨率
const String CSystemInfoManage::strEditInfo = "EditInfo";
const String CSystemInfoManage::strStaticInfo = "StaticInfo";
const String CSystemInfoManage::strKeyValue = "KeyValue"; //平板电脑home键键值

template<> CSystemInfoManage* Singleton<CSystemInfoManage>::ms_pSingleton  = 0;
CSystemInfoManage::CSystemInfoManage():m_strMainXml(),
                                       m_strImagePath(),
                                       m_strLayoutPath(),
                                       m_strItemInfo(),
                                       m_strResolution(),
                                       m_bBeSelAdpResolution( TRUE ),
									   m_strVersion()

{

}

CSystemInfoManage::~CSystemInfoManage()
{

}

void CSystemInfoManage::Update( IArgs* pArgs )
{
	if (  Args_SystemObserver* pObser = dynamic_cast<Args_SystemObserver*>(pArgs) )
	{
		SystemInfoMultiMap::iterator itr = pObser->m_mapSystemInfos.begin();
		while ( itr != pObser->m_mapSystemInfos.end() )
		{
			if ( itr->first == CSystemInfoManage::strSystemInfo )
			{
				UpdateSystemInfo( itr->second );
			}
			itr++;
		}
	}
}

void CSystemInfoManage::UpdateSystemInfo( XMLAttributes& xmlAttribs )
{   
	if ( !xmlAttribs.exists( CSystemInfoManage::strName ) || !xmlAttribs.exists( CSystemInfoManage::strValue ) )
    {   
        LOGEVENT("[CSystemInfoManage::UpdateSystemInfo] return ：不存在 " + CSystemInfoManage::strName + "或者不存在"+CSystemInfoManage::strValue );
		return;
	}
	String strName = xmlAttribs.getValue( CSystemInfoManage::strName );
	String strValue = xmlAttribs.getValue( CSystemInfoManage::strValue );
	
	if ( strName == CSystemInfoManage::strImagePath)
	{		
		SetImagePath( strValue );
	}	
	else if ( strName == CSystemInfoManage::strLayoutPath )
	{
		SetLayoutPath( strValue );
	}
	else if ( strName == CSystemInfoManage::strItemInfo )
	{
		SetItemInfoPath( strValue );
 	}
    else if ( strName == CSystemInfoManage::strResolution)
    {
        SetResolution( strValue );
    }
    else if ( strName == CSystemInfoManage::strBeSelAdpResolution )
    {
        SetBeSelAdpResolution(strValue);
    }
    else if ( strName == CSystemInfoManage::strEditInfo )
    {
        SetFontInfo( m_tEditFontInfo, xmlAttribs );
    }
    else if ( strName == CSystemInfoManage::strStaticInfo )
    {
        SetFontInfo( m_tStaticFontInfo, xmlAttribs );
    }
	else if ( strName == CSystemInfoManage::strVersion )
    {
        SetVersion( strValue );
    }
	else if ( strName == CSystemInfoManage::strKeyValue )
	{
		SetPadKeyValue( strValue );
	}

}

/**  设置系统图片资源路径
 *  @param[in] strPath 路径
 *  @return 
 */
void CSystemInfoManage::SetImagePath( String strPath )
{ 
    m_strImagePath = strPath ;
#ifndef _DEBUG
    MakeFullPath( m_strImagePath );
#endif
    
}


/**  设置系统布局文件路径
*  @param[in] strPath 路径
*  @return 
*/
void CSystemInfoManage::SetLayoutPath( String strPath )
{ 
    m_strLayoutPath = strPath ; 
#ifndef _DEBUG
    MakeFullPath(m_strLayoutPath); 
#endif
    
}


/**  设置ItemInfo文件路径
 *  @param[in] strPath 路径
 *  @return 
 */
void CSystemInfoManage::SetItemInfoPath( String strPath )
{  
    m_strItemInfo =  strPath ;
#ifndef _DEBUG
    MakeFullPath(m_strItemInfo );
#endif
    
    LOGEVENT("[etItemInfoPath( String strPath )]" + m_strItemInfo );
}

//把某个文件的相对路径设置为绝对路径
void CSystemInfoManage::MakeFullPath( String& strFileSubPath )
{
    TCHAR achDllName[MAX_PATH] = _T(""); 
    GetModuleFileName(AfxGetInstanceHandle(), achDllName, sizeof (achDllName));
    String str( achDllName ); 
    
    int pos = str.find_last_of('\\'); 
    String strSub = str.substr( 0,pos+1 );
    char strFullPath[MAX_PATH] = _T(""); 
   
    _snprintf(strFullPath , sizeof(strFullPath), "%s%s",strSub.c_str(),strFileSubPath.c_str() );
   
    strFileSubPath = strFullPath ;
  
}


void CSystemInfoManage::SetResolution( String strValue )
{  
    m_strResolution = strValue; 
}


void CSystemInfoManage::GetResolution( int &cx, int &cy )
{ 
    SIZE  sz ;
	//默认分辨率1366*768
    sz.cx = 1366;
    sz.cy = 768;
    if ( !m_strResolution.empty() )
    {
         sz = CPropertyHelp::stringToSize( m_strResolution );
    }
   
    cx = sz.cx;
    cy = sz.cy;
}


//是否自适应分辨率
void CSystemInfoManage::SetBeSelAdpResolution( String strValue )
{
    m_bBeSelAdpResolution = CPropertyHelp::stringToBool( strValue );
}


BOOL CSystemInfoManage::IsSelAdpResolution() 
{
    return m_bBeSelAdpResolution;
}


void CSystemInfoManage::SetFontInfo( TFontInfo &tFontInfo, XMLAttributes& xmlAttribs )
{
    if ( !xmlAttribs.exists( CSystemInfoManage::strName ) )
    {   
        LOGEVENT("[CSystemInfoManage::SetEditFontInfo] return：不存在 " + CSystemInfoManage::strName );
        return;
    }
    String strName = xmlAttribs.getValue( CSystemInfoManage::strName );
	String strValue = xmlAttribs.getValue( CSystemInfoManage::strValue );

    if ( xmlAttribs.exists( CItemFactory::strFontName ) )
    {
        tFontInfo.strFontName = xmlAttribs.getValue( CItemFactory::strFontName );            
	}
    if ( xmlAttribs.exists( CItemFactory::strFontSize ) )
    {
        tFontInfo.nFontSize = xmlAttribs.getValueAsInteger( CItemFactory::strFontSize );
    }
    if ( xmlAttribs.exists( CItemFactory::strFontColor ) )
    {
        tFontInfo.strNormalColor = xmlAttribs.getValue( CItemFactory::strFontColor );
    }
    if ( xmlAttribs.exists( "FocusColor" ) )
    {
        tFontInfo.strFocusColor = xmlAttribs.getValue( "FocusColor" );
    }
    if ( xmlAttribs.exists( "DisableColor" ) )
    {
        tFontInfo.strDisableColor = xmlAttribs.getValue( "DisableColor" );
    }
    if ( xmlAttribs.exists( "DisableImg" ) )
    {
        tFontInfo.strDisableImg = xmlAttribs.getValue( "DisableImg" );
    }

}
 

void  CSystemInfoManage::SetVersion( string strVer )
{
	m_strVersion =  strVer ; 
   
}

void CSystemInfoManage::SetPadKeyValue( String strValue )
{
	m_dwKeyValue = CPropertyHelp::stringToInt( strValue );
}

DWORD CSystemInfoManage::GetPadKeyValue()
{
	return m_dwKeyValue;
}

}
