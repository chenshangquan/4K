// SaveXmlHelp.cpp: implementation of the CSaveXmlHelp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "System.h"
#include "SaveXmlHelp.h"
#include "LayoutXmlHandle.h"
#include "tinyxml.h"
#include "tinystr.h"
#include "WindowManage.h"
#include "WindowTag.h"
#include "IPropertyAssist.h"
#include "WndTreeHelp.h"
#include "schemetag.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace AutoUIFactory
{

using namespace AutoTinyXml;

	class XmlSaveDocument : public TiXmlDocument
	{
	public:
	//	XmlSaveDocument(const String& filename );
        
        ////strSavePropertyName 要保存的属性名，bForceSave 如果要保存的属性不在当前方案中，是否强制保存
        XmlSaveDocument(const String& filename , const String& strWndName ="", const String& strPropertyName = "", BOOL bForceSave = FALSE );

		~XmlSaveDocument()
		{
			m_stackWndTree.clear();
		}
        

        //2011-8-12 add by yujinjin
        //保存一个element的内容到文件
        //param:strElementFullPath element的全路径信息
        bool SaveElement( const String& strElementFullPath );
	protected:
		void processElement(const TiXmlElement* element);

		void Process( TiXmlElement* element );
        //StrPropertyName ：要保存的属性名
		bool ElementStart( TiXmlElement* element, const XMLAttributes& xmlAttributes );
 

		bool ElementEnd( TiXmlElement* element );

		/*
	 * 当前的一个IWndTree的堆栈，遇到start添加，遇到end出栈\n 
	 */
		typedef std::vector<IWndTree*> WndTreeStack;
		WndTreeStack m_stackWndTree;

		WndInfo* m_pCurWnd;
		IWndTree* m_pCurWndTree;
		
		String m_strCurScheme;

        String m_strSavePropertyName;
        String m_strSaveWndName;
        String m_strCurWndName;
        BOOL m_bForceSave;
	};
    
    XmlSaveDocument::XmlSaveDocument( const String& strWindow ,const String& strWndName/*= ""*/,
                                                              const String& strPropertyName /*= ""*/,  BOOL bForceSave /*= FALSE */)
	{
		m_strCurScheme = WndInfo::strDefaultScheme;
		m_strSavePropertyName = strPropertyName;
        m_strCurWndName = "";
        m_pCurWnd = 0;

        char chPart = CWndTreeHelp::chPartitionChar;
        int size = strWndName.rfind( chPart );  
        if ( size >= 0 ) 
        {
             m_strSaveWndName = strWndName.substr( size + 1 );
        }
        else
        {
            m_strSaveWndName = strWndName;
        }
        m_bForceSave = bForceSave;
		XMLAttributes xmlAttribs;
		bool bFind = CSystem::GetSingletonPtr()->GetWindowXml( strWindow, xmlAttribs );
		if ( bFind == false )
		{
			return;
		}
		String strFile = xmlAttribs.getValue( CSystem::strValue );
		String strMainPath = CSystem::GetSingletonPtr()->GetLayoutPath();
		strFile = strMainPath + strFile;
		String strParent = xmlAttribs.getValue( CSystem::strWndParent );

        m_pCurWndTree = CWindowManage::GetSingletonPtr()->GetRoot();
        if ( strParent != "" )
		{
            IWndTree* piParentWndTree = const_cast<IWndTree*>( CWndTreeHelp::GetWindow( strParent, m_pCurWndTree ) );
            if ( piParentWndTree != 0 )
            {
                m_pCurWndTree = piParentWndTree;
            }
        }
		
		try
		{
			// Parse the document
			TiXmlDocument *myDocument = new TiXmlDocument(strFile.c_str());
			myDocument->LoadFile();
			
			TiXmlElement* currElement = myDocument->RootElement();
			if (currElement)
			{
				// function called recursively to parse xml data
				Process( const_cast<TiXmlElement*>(currElement) );
			} // if (currElement)
			myDocument->SaveFile( strFile.c_str() );
			if ( myDocument != NULL )
			{
				delete myDocument;
				myDocument = NULL;
			}
		}
		catch(...)
		{
			throw;
		}
	}
	
	
	void XmlSaveDocument::Process( TiXmlElement* element )
	{
		XMLAttributes attrs;
		
		TiXmlAttribute *currAttr = element->FirstAttribute();
		while (currAttr)
		{
			attrs.add((char*)currAttr->Name(), (char*)currAttr->Value());
			currAttr = currAttr->Next();
		}
		ElementStart( element, attrs );
		TiXmlNode* childNode = element->FirstChild();
		while (childNode)
		{
			switch(childNode->Type())
			{
			case TiXmlNode::TINYXML_ELEMENT:
				Process( const_cast<TiXmlElement*>(childNode->ToElement()) );
				break;
			default:
				break;
			};
			childNode = childNode->NextSibling();
		}
		ElementEnd( element );
	}

 

    bool XmlSaveDocument::ElementStart( TiXmlElement* element, const XMLAttributes& xmlAttributes )
    {
        String strElement = (char*)element->Value();
        if ( strElement == CLayoutHandle::strCreateWindow && m_pCurWndTree != 0 )
        {
            String strName = xmlAttributes.getValue( CWindowTag::strName );
            m_strCurWndName = strName;
            IWndTree* pSubWndTree = m_pCurWndTree->GetItemByKey( strName );
            if ( pSubWndTree != 0 )
            {
                m_pCurWnd = pSubWndTree->GetItemData();			
            }
            else
            {
                m_pCurWnd = 0;
            }
            m_pCurWndTree = pSubWndTree;
            m_stackWndTree.push_back( pSubWndTree );		
        }
        else if ( strElement == CLayoutHandle::strScheme ) 
        {
            m_strCurScheme = xmlAttributes.getValue( CSchemeTag::strName );
        }
        else if ( strElement == CLayoutHandle::strProperty && m_pCurWnd )
        {
            // 只有当当前正在使用的方案是xml里面对应的部分才保存
          String strCurScheme = m_pCurWnd->GetCurUseScheme();

          if ( m_pCurWnd != NULL && ( m_strCurScheme == strCurScheme || m_bForceSave) )                
            {   
                String strName = xmlAttributes.getValue( CPropertyAssist::strName );
              
                if (  ( m_strSavePropertyName.empty() || ( !m_strSavePropertyName.empty() && strName == m_strSavePropertyName ) ) &&
                     ( m_strSaveWndName.empty() || ( !m_strSaveWndName.empty() && m_strCurWndName == m_strSaveWndName )) )
                {
                    IProperty* piProperty = CPropertyAssist::GetSingletonPtr()->GetPropertyByCommonName( m_pCurWnd->strType, strName );
                    if ( piProperty != 0  )
                    {
                        String strValue;
                        bool bGet = piProperty->get( m_pCurWnd->pWnd, strValue );
                        if ( bGet == true )
                        {
                            element->SetAttribute( CPropertyAssist::strValue.c_str(), strValue.c_str() );
                        }
                    }
                } 
            }
            
        }
        return true;
	}


	bool XmlSaveDocument::ElementEnd( TiXmlElement* element )
	{
		String strElement = (char*)element->Value();
		if ( strElement == CLayoutHandle::strCreateWindow )
		{
			if ( m_stackWndTree.empty() )
			{
				return false;
			}
			m_stackWndTree.pop_back();
			if ( m_stackWndTree.empty() )
			{
				m_pCurWndTree = 0;
				return true;
			}
			m_pCurWndTree = m_stackWndTree[ m_stackWndTree.size() - 1 ];
			if ( m_pCurWndTree != 0 )
			{
				m_pCurWnd= m_pCurWndTree->GetItemData();		
			}
			else
			{
				m_pCurWnd = 0;
			}
			m_strCurScheme = WndInfo::strDefaultScheme;
		}
		return true;
	}

//strSavePropertyName 要保存的属性名，bForceSave 如果要保存的属性不在当前方案中，是否强制保存
bool CSaveXmlHelp::SaveXml( String strWindow, String strSaveWndName/* = "" */, String strSavePropertyName/* = "" */, BOOL  bForceSave/*= FALSE */)
{
	XmlSaveDocument doc( strWindow,strSaveWndName, strSavePropertyName, bForceSave );
	return true;
}

 

} // namespace AutoUIFactory end
