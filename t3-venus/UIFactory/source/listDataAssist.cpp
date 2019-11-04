// listDataAssist.cpp: implementation of the CListDataAssist class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "listDataAssist.h"
#include "System.h"
#include "PropertyHelp.h"
#include "tinyxml.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace AutoUIFactory
{
using namespace AutoTinyXml;

CListDataAssist::CListDataAssist():m_LstData(),m_pDocument(NULL)
{
    const_cast<String&>(m_strName) = "Name";
    const_cast<String&>(m_strRootTag) = "List" ;
    const_cast<String&>(m_strItem) = "Item";
    const_cast<String&>(m_strIndex) = "Index" ; 
    const_cast<String&>(m_strImg) = "Img";
    const_cast<String&>(m_strClickFun) = "ClickFun";
    const_cast<String&>(m_strVisible) = "Visible";
 
}

CListDataAssist::~CListDataAssist()
{

}



BOOL CListDataAssist::GetListData( const String strFileName, const String strListName, OUT vector<TListItem>& LstData )
{  
    m_strElementName = strListName;
    const TiXmlElement* pElement = GetElement( strFileName, strListName );
    if( pElement == NULL )
    {
        return FALSE;
    }

    GetAttribData( pElement, LstData );
    return TRUE;
         
}

BOOL CListDataAssist::SetListData( const String strFileName, const String strListName,   vector<TListItem>& LstData )
{
    m_strElementName = strListName; 

    const TiXmlElement* pElement = GetElement( strFileName, strListName );
    if( pElement == NULL )
    {
        return FALSE;
    }

    BOOL re = TRUE;
    vector<TListItem>::iterator it = LstData.begin();
    while( it != LstData.end() )
    {
      //  re = SetAttribData( pElement, *it );
        SetItemData(strFileName,   strListName, *it );
        it++;
    }
    
//     TiXmlDocument *myDocument = new TiXmlDocument();
//     myDocument->SaveFile( strFileName.c_str() );
//     
//     if ( myDocument )
//     {
//         delete myDocument;
//         myDocument = NULL;
//         
//     }

    return TRUE;
}


BOOL CListDataAssist::SetItemData( const String strFileName, const String strListName,const TListItem & tItem )
{
    m_strElementName = strListName;
    const TiXmlElement* pElement = GetElement( strFileName, strListName );
    if( pElement == NULL )
    {
        return FALSE;
    }

    BOOL re = SetAttribData( pElement, tItem );
   
//     TiXmlDocument *myDocument = new TiXmlDocument();
//     myDocument->SaveFile( strFileName.c_str() );

    if ( m_pDocument )
    {
        m_pDocument->SaveFile( strFileName.c_str() );
        delete m_pDocument;
        m_pDocument = NULL;

    }
    return re;
     
}




const TiXmlElement* CListDataAssist::GetElement( const String strFileName, const String lstName )
{
    try
    {   
        if ( m_pDocument != NULL )
        {
            delete m_pDocument;
            m_pDocument = NULL;
        }

        /*TiXmlDocument *myDocument*/ m_pDocument = new TiXmlDocument(strFileName.c_str());
        bool re = m_pDocument->LoadFile();
        if ( !re )
        {
            delete m_pDocument;
            m_pDocument = NULL;
            TRACE("[TinyXMLDocument]m_pDocument->LoadFile( %s ) = false ",strFileName );
            return NULL;
        }
        
        const TiXmlElement* currElement = m_pDocument->RootElement();
        if (currElement)
        {    
            // function called recursively to parse xml data
            return FindElement( currElement, lstName );
        } // if (currElement)
        
//         if ( myDocument != NULL )
//         {
//             delete myDocument;
//             myDocument = NULL;
//         }
        
    }
    catch(...)
    {
        throw;
	}

    return FALSE;
}

const TiXmlElement*  CListDataAssist::FindElement( const TiXmlElement* element, const String strListName )
{
    String strElementName = (char*)element->Value();
    if ( strElementName == m_strRootTag  )
    {   
        const  char* pName = element->Attribute( m_strName.c_str() );
        if( pName != NULL && strcmp(m_strElementName.c_str(), pName) == 0 )
        {
            return element;
        }
        else
        {    
            return FindElement( element->NextSiblingElement() , strListName );
        } 
    } 
   else
    {
        const TiXmlNode* childNode = element->FirstChild();
        return FindElement( childNode->ToElement() , strListName );
    }
}

 

void CListDataAssist::GetAttribData(const TiXmlElement* element, OUT vector<TListItem>& LstData )
{ 
    if ( element == NULL )
    {
        return ;
    }

    const TiXmlNode* nextNode = element->FirstChild(); 
    while (nextNode)
    {   
        const  TiXmlElement* pElement = nextNode->ToElement() ;
        if( nextNode->Type() == 1/*TINYXML_ELEMENT*/ && pElement != NULL  )
        {  
            String strElementName = (char*)( pElement->Value() );
            if ( strElementName != m_strItem )
            {
                break ;
            } 
        
            TListItem tItem;
            tItem.strItemName = pElement->Attribute( m_strName.c_str() ); 
        
            
            const char *pVisible = pElement->Attribute( m_strVisible.c_str() )  ;

            int nVisible =  CPropertyHelp::stringToInt( pVisible );

            tItem.bVisible = (bool)nVisible;
            tItem.nIndex = CPropertyHelp::stringToInt( pElement->Attribute( m_strIndex.c_str())) ; 
        
            LstData.push_back( tItem );
        
        } 
            
        nextNode = nextNode->NextSibling();
    }

}
 
BOOL CListDataAssist::SetAttribData( const TiXmlElement* element , const TListItem &tItem  )
{ 
    if ( element == NULL )
    {
        return FALSE;
    }
    
    const TiXmlNode* nextNode = element->FirstChild(); 

    while (nextNode)
    {   
        const  TiXmlElement* pCstElement = nextNode->ToElement() ;
        if( nextNode->Type() == 1/*TINYXML_ELEMENT*/ && pCstElement != NULL  )
        {  
            String strElementName = (char*)( pCstElement->Value() );
            if ( strElementName != m_strItem )
            {
                break ;
            } 

            TiXmlElement* pElement = const_cast<TiXmlElement*> ( pCstElement );
        
            if( pElement != NULL  )
            {  
                const char * pName = pElement->Attribute(m_strName.c_str());
                if( pName != NULL && strcmp(pName ,tItem.strItemName.c_str()) == 0 )
                {
                    String strIndex = CPropertyHelp::intToString( tItem.nIndex  );
                    pElement->SetAttribute( m_strIndex.c_str(), strIndex.c_str() );
                    
                    int nVisible = (int)tItem.bVisible;
                    String strVisible = CPropertyHelp::intToString( nVisible );
                    pElement->SetAttribute( m_strVisible.c_str(), strVisible.c_str() ); 
                    return TRUE;
                }
                
            }
        
        } 
            
        nextNode = nextNode->NextSibling();
    } 
   
    return FALSE;
  
}

}


