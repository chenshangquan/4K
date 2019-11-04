/*=======================================================================
模块名      : 
文件名      : xmlstructconvert.h
相关文件    :
文件实现功能: xmlstructconvert.lib的头文件,xml与struct相互转换接口
               
作者        : 吴月龙
版本        : V1.0  Copyright(C) 2005-2010 Suzhou Keda Technology Co.Ltd
              All rights reserved.
--------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2010/10/18  1.0         吴月龙      创建
=======================================================================*/

#ifndef _XML_STRUCT_CONVERT_H
#define _XML_STRUCT_CONVERT_H

#include <stdarg.h>
#include "tinyxml.h"
#include "kdvtype.h"

#define ATTRIBUTE_NAME          "value"
#define ARRAYELEMENT_KEY        "ArrayElement%u"

#ifdef WIN32
#ifndef vsnprintf
#define vsnprintf   _vsnprintf
#endif
#ifndef snprintf
#define snprintf    _snprintf
#endif
#endif

#ifdef WIN32
#ifndef FormatU64
#define FormatU64   "%I64u"
#endif
#endif

#ifdef _LINUX_
#ifndef FormatU64
#define FormatU64   "%llu"
#endif
#endif

#ifndef IN
#define IN
#endif
#ifndef OUT
#define OUT
#endif


#ifdef XMLCONVERT_DLL_EXPORT	
	#define	XMLCONVERT_API __declspec( dllexport )
#else 
	#define XMLCONVERT_API
#endif


class XMLCONVERT_API CXmlStructConvert
{
public:

	CXmlStructConvert();

	~CXmlStructConvert();

	//load document to initialize the object of the CTinyXMLWander
	BOOL32 LoadXMLDocument( const char *pDocumentName );

	//save the xml tree by a given filename
	void SaveXMLDocument( const char *pDocumentName );

	//save the xml tree ( filename has been given before )
	void SaveXMLDocument();

	//transform the xml struct into characters
	//user has to allocate space for pBuffer and nSize is value-result argument 
    BOOL32 TramsformXML2Chars( char *pBuffer, u32 &nSize );
    TIXML_STRING TramsformXML2Chars( );

	//transform the characters into xml struct
	BOOL32 TransformChars2XML(const char *pchars );

    BOOL32 InitXmlWrapper( const s8* pSrcBuf = NULL );

	//clear all the nodes
	void ClearXML();

	//navigate the stage of current's children
	BOOL32 GoDownstairs();

	//navigate current's parent
	BOOL32 GoUpstairs();

	//search for the first sibling element whose value equals pValue
	//when bTest is true, it means that the user just test whether the sibling exits or not 
	//when bTest is false, it means that sets the sibling as current node if the sibling exits
	BOOL32 FindElement( const char *pValue, BOOL32 bTest = FALSE );

	//search for the first sibling element behind current node, whose value equals pValue
	//when bTest is true, it means that the user just test whether the sibling exits or not 
	//when bTest is false, it means that sets the sibling as current node if the sibling exits
	BOOL32 FindNextElement( const char *pValue, BOOL32 bTest = FALSE );

	//search for the first element by the given pass, the pass is that from current node to the aim node
	//the nDepth is that the height of the pass tree subtracts from 1
	BOOL32 FindElementInDepth( const int nDepth, const char *p1stValue, ... )
	#ifdef __GNUC__  //只在GCC时才enable
			__attribute__((format(printf, 3, 4))) //
	#endif
	;

	//create the root node
	BOOL32 CreateRootNode(const char *pValue);

	//get the value of the current element
	const char *GetValue();

	//set the value of the current element
	BOOL32 SetValue( const char *pValue );
    
    //
    BOOL32 GetValueByElementName( const char *pKeyWord, char* strbuf, s32 nMaxBufSize );
    BOOL32 GetValueByElementName( const char *pKeyWord, u64& lwValue );
    BOOL32 GetValueByElementName( const char *pKeyWord, s64& lwValue );
    BOOL32 GetValueByElementName( const char *pKeyWord, u32& dwValue );
    BOOL32 GetValueByElementName( const char *pKeyWord, u16& dwValue );
    BOOL32 GetValueByElementName( const char *pKeyWord, u8& dwValue );
    BOOL32 GetValueByElementName( const char *pKeyWord, s32& dwValue );
    BOOL32 GetValueByElementName( const char *pKeyWord, s16& dwValue );
    BOOL32 GetValueByElementName( const char *pKeyWord, s8& dwValue );
    BOOL32 GetDataByElementName(const char *pKeyWord, u8* pBuf, u32 dwBufLen);

    //复杂的结构直接以二进制数据的形式传输
    template<typename DataType>
    BOOL32 GetDataByElementName(const char *pKeyWord, DataType& type)
    {   
		if(NULL == pKeyWord)
		{
			return FALSE;
		}

        BOOL32 bRet = GetDataByElementName(pKeyWord, (u8*)&type, sizeof(type));   
        return bRet;
    }


    template<typename EnumType>
    BOOL32 GetEnumValueByElementName( const char *pKeyWord, EnumType& emValue )
    {
		if(NULL == pKeyWord)
		{
			return FALSE;
		}

        u32 dwValue = 0;
        BOOL32 bRet = GetValueByElementName(pKeyWord, dwValue);
        if (!bRet)
        {
            return FALSE;
        }
        
        emValue = (EnumType)dwValue;        
        return TRUE;
    }

    template<typename NestedType>
    BOOL32 GetNestedSiblingElement(const char* xmlString, const char *pKeyWord, NestedType& type)
    {
        if (NULL == xmlString || NULL == pKeyWord)
        {
            return FALSE;
        }

        TiXmlDocument cxmlDoc;
        cxmlDoc.Parse(xmlString);
        if (cxmlDoc.Error())
        {
            return FALSE;
        }
        
        TiXmlNode* pRootNode = cxmlDoc.FirstChild();
        if (!pRootNode)
        {
            return FALSE;
        }
        TiXmlNode* pNestedNode = pRootNode->FirstChild(pKeyWord);
        if (!pNestedNode)
        {
            return FALSE;
        }

        TiXmlDocument cNestedDoc;
        cNestedDoc.InsertEndChild(*pNestedNode);
        TiXmlPrinter printer;
        cNestedDoc.Accept( &printer );
        BOOL32 bRet = type.XmlToStruct(printer.CStr());
        if (!bRet)
        {
            return FALSE;
        }

        return TRUE;
    }

    //模板类AaaryType为基本类型,没有实现了XmlToStruct
    //(目前支持:s8,u8,s16,u16,s32,u32,enum;目前不支持:s64,u64)
    template<typename AaaryType>
    BOOL32 GetArraySiblingElement(const char* xmlString, const char *pKeyWord, AaaryType* pType, u32 dwMaxArrayLen, OUT u32& dwRealNum)
    {
        if (NULL == xmlString || NULL == pKeyWord || NULL == pType)
        {
            return FALSE;
        }
        
        dwRealNum = 0;
        TiXmlDocument cxmlDoc;
        cxmlDoc.Parse(xmlString);
        if (cxmlDoc.Error())
        {
            return FALSE;
        }
        
        TiXmlNode* pRootNode = cxmlDoc.FirstChild();
        if (!pRootNode)
        {
            return FALSE;
        }
        TiXmlNode* pArrayRootNode = pRootNode->FirstChild(pKeyWord);
        if (!pArrayRootNode)
        {
            return FALSE;
        }
        
        u32 dwArrayPos = 0;
        s8 achArraySubKey[32] = {0};
        snprintf(achArraySubKey, sizeof(achArraySubKey), ARRAYELEMENT_KEY, dwArrayPos);
        TiXmlElement* pArraySubElement = pArrayRootNode->FirstChildElement(achArraySubKey);
        while( dwArrayPos < dwMaxArrayLen 
            && NULL != pArraySubElement)
        {
            const char* pStrValue = pArraySubElement->Attribute(ATTRIBUTE_NAME);
            if (!pStrValue)
            {
                return FALSE;
            }
            
            pType[dwArrayPos] = (AaaryType)strtoul(pStrValue, 0, 10);
            
            ++dwArrayPos;
            snprintf(achArraySubKey, sizeof(achArraySubKey), ARRAYELEMENT_KEY, dwArrayPos);
            pArraySubElement = pArrayRootNode->FirstChildElement(achArraySubKey);
        }  
        
        dwRealNum = dwArrayPos;
        return TRUE;
    }

    //模板类AaaryType必须已经实现了XmlToStruct
    template<typename AaaryType>
    BOOL32 GetNestedArraySiblingElement(const char* xmlString, const char *pKeyWord, AaaryType* pType, u32 dwMaxArrayLen, OUT u32& dwRealNum)
    {
        if (NULL == xmlString || NULL == pKeyWord || NULL == pType)
        {
            return FALSE;
        }

        dwRealNum = 0;
        TiXmlDocument cxmlDoc;
        cxmlDoc.Parse(xmlString);
        if (cxmlDoc.Error())
        {
            return FALSE;
        }
        
        TiXmlNode* pRootNode = cxmlDoc.FirstChild();
        if (!pRootNode)
        {
            return FALSE;
        }
        TiXmlNode* pArrayRootNode = pRootNode->FirstChild(pKeyWord);
        if (!pArrayRootNode)
        {
            return FALSE;
        }
        
        u32 dwArrayPos = 0;
        s8 achArraySubKey[32] = {0};
        snprintf(achArraySubKey, sizeof(achArraySubKey), ARRAYELEMENT_KEY, dwArrayPos);
        TiXmlNode* pArraySubNode = pArrayRootNode->FirstChild(achArraySubKey);
        while( dwArrayPos < dwMaxArrayLen 
            && NULL != pArraySubNode)
        {
            TiXmlDocument cNestedDoc;
            cNestedDoc.InsertEndChild(*pArraySubNode);
            TiXmlPrinter printer;
            cNestedDoc.Accept( &printer );
            BOOL32 bRet = pType[dwArrayPos].XmlToStruct(printer.CStr());
            if (!bRet)
            {
                return FALSE;
            }

            ++dwArrayPos;
            snprintf(achArraySubKey, sizeof(achArraySubKey), ARRAYELEMENT_KEY, dwArrayPos);
            pArraySubNode = pArrayRootNode->FirstChild(achArraySubKey);
        }  
        
        dwRealNum = dwArrayPos;
        return TRUE;
    }

	//add a sibling for the current
	BOOL32 AddSiblingElement( const char *pKeyWord );
    BOOL32 AddSiblingElementAndValue( const char *pKeyWord, const char *pValue );
    BOOL32 AddSiblingElementAndValue( const char *pKeyWord, u64 lwValue );
    BOOL32 AddSiblingElementAndValue( const char *pKeyWord, s64 lwValue );
    BOOL32 AddSiblingElementAndValue( const char *pKeyWord, u32 dwValue );
    BOOL32 AddSiblingElementAndValue( const char *pKeyWord, u16 dwValue );
    BOOL32 AddSiblingElementAndValue( const char *pKeyWord, u8 dwValue );
    BOOL32 AddSiblingElementAndValue( const char *pKeyWord, s32 dwValue );
    BOOL32 AddSiblingElementAndValue( const char *pKeyWord, s16 dwValue );
    BOOL32 AddSiblingElementAndValue( const char *pKeyWord, s8 dwValue );
    BOOL32 AddSiblingData(const char *pKeyWord, const u8* pBuf, u32 dwBufLen);

    //复杂的结构直接以二进制数据的形式传输
    template<typename DataType>
    BOOL32 AddSiblingData(const char *pKeyWord, const DataType& type)
    {
		if(NULL == pKeyWord)
		{
			return FALSE;
		}

        BOOL32 bRet = AddSiblingData( pKeyWord, (const u8*)&type, sizeof(type) );
        return bRet;
    }



    template<typename NestedType>
    BOOL32 AddNestedSiblingElement( const char *pKeyWord, IN NestedType& type )
    {  
		if(NULL == pKeyWord)
		{
			return FALSE;
		}

        TIXML_STRING strxmlNested = type.StructToXml();
        TiXmlDocument cNestedTiXmlDoc;
        cNestedTiXmlDoc.Parse(strxmlNested.c_str());
        if (cNestedTiXmlDoc.Error())
        {
            return FALSE;
        }
        TiXmlNode* pNestedRootNode = cNestedTiXmlDoc.FirstChild();
        if (!pNestedRootNode)
        {
            return FALSE;
        }
        pNestedRootNode->SetValue(pKeyWord);

        m_pCurrentElement = ( m_pParentElement->InsertEndChild(*pNestedRootNode) )->ToElement();
	    m_pChildElement = m_pCurrentElement->FirstChildElement();

        return TRUE;
    }
    
    //模板类AaaryType为基本结构类型,没有实现StructToXml
    template<typename AaaryType>
    BOOL32 AddArraySiblingElement(const char *pKeyWord, AaaryType* pType, u32 dwArrayLen)
    {
		if(NULL == pKeyWord || NULL == pType)
		{
			return FALSE;
		}

        TiXmlElement* pAaaryRootElement = new TiXmlElement(pKeyWord);
        if (!pAaaryRootElement)
        {
            return FALSE;
        }
        pAaaryRootElement->SetAttribute("Version" , "1.0");
        
        for ( u32 dwIndex = 0; dwIndex<dwArrayLen; ++dwIndex )
        {
            TiXmlElement* pSubElement = new TiXmlElement(pKeyWord);

            s8 achSubKey[32] = {0};
            snprintf(achSubKey, sizeof(achSubKey), ARRAYELEMENT_KEY, dwIndex);
            pSubElement->SetValue(achSubKey);  

            char buf[128] = {0};
            sprintf(buf, "%lu", pType[dwIndex]);
            pSubElement->SetAttribute(ATTRIBUTE_NAME, buf);
          
            pAaaryRootElement->InsertEndChild(*pSubElement);  

            if (pSubElement)
            {
                delete pSubElement;
                pSubElement = NULL;
            }

        }        
        m_pCurrentElement = ( m_pParentElement->InsertEndChild(*pAaaryRootElement) )->ToElement();
        m_pChildElement = m_pCurrentElement->FirstChildElement();
        
        if (pAaaryRootElement)
        {
            delete pAaaryRootElement;
            pAaaryRootElement = NULL;        
        }

        return TRUE;
    }

    //模板类AaaryType必须已经实现了StructToXml
    template<typename AaaryType>
    BOOL32 AddNestedArraySiblingElement(const char *pKeyWord, AaaryType* pType, u32 dwArrayLen)
    {
		if(NULL == pKeyWord || NULL == pType)
		{
			return FALSE;
		}

        TiXmlElement* pAaaryRootElement = new TiXmlElement(pKeyWord);
        if (!pAaaryRootElement)
        {
            return FALSE;
        }
        pAaaryRootElement->SetAttribute("Version" , "1.0");

        for ( u32 dwIndex = 0; dwIndex<dwArrayLen; ++dwIndex )
        {
			TiXmlDocument cSubArrayDoc;		//必须放再循环中
            TIXML_STRING strxmlSubArray = pType[dwIndex].StructToXml();
            cSubArrayDoc.Parse(strxmlSubArray.c_str());
            if (cSubArrayDoc.Error())
            {
				//return之前需要不要忘了释放资源
				if (pAaaryRootElement)
				{
					delete pAaaryRootElement;
					pAaaryRootElement = NULL;
				}				
                return FALSE;
            }

            TiXmlNode* pSubArrayRootNode = cSubArrayDoc.FirstChild();
            if (!pSubArrayRootNode)
            {
				//return之前需要不要忘了释放资源
				if (pAaaryRootElement)
				{
					delete pAaaryRootElement;
					pAaaryRootElement = NULL;
				}
                return FALSE;
            }
            
            s8 achSubKey[32] = {0};
            snprintf(achSubKey, sizeof(achSubKey), ARRAYELEMENT_KEY, dwIndex);
            pSubArrayRootNode->SetValue(achSubKey);              
            pAaaryRootElement->InsertEndChild(*pSubArrayRootNode);
        }
        
        m_pCurrentElement = ( m_pParentElement->InsertEndChild(*pAaaryRootElement) )->ToElement();
        m_pChildElement = m_pCurrentElement->FirstChildElement();

        if (pAaaryRootElement)
        {
            delete pAaaryRootElement;
            pAaaryRootElement = NULL;
        }
        return TRUE;
    }


	BOOL32 AddText( const char *pText );

	//remove current element and its children 
	BOOL32 RemoveElement();

	//set attribute name with content
	BOOL32 SetAttribute( const char * pName, const char *pContent );

	BOOL32 SetAttribute( const char *pName, int dwValue);

	//get attribute name's content
	const char *GetAttribute( const char *pName )const;

	int GetAttribute( const char * pName, int *dwValue );

	//remove attribute name
	BOOL32 RemoveAttribute( const char *pName );

	//get the text of current element
	const char *GetText();

	//navigate  the first sibling of current's
	BOOL32 FirstSibling();

	//navigate current's next sibling
	BOOL32 NextSibling();

	//navigate current's previous sibling
	BOOL32 PreviousSibling();

	//navigate current's first child
	BOOL32 FirstChild();

	//navigate current's first child whose value equals pvalue
	BOOL32 FirstChild( const char *pValue );

	//set the current pos to the root element
	BOOL32 Return2Root();

	//print xml tree to screen
	void Print();

    //将xml语法数转成字符串
    BOOL32 ConvertXMLToString(s8* pDstBuf, u32& dwDstBufSize );
    const TIXML_STRING ConvertXMLToString( );

    
    BOOL32 InitStructToXml();    
    
    template <typename BaseClass> 
    BOOL32 InitStructToXmlByBaseClass(BaseClass& base)
    {
        TIXML_STRING strBaseClassXml = base.StructToXml();
        BOOL32 bRet = InitXmlWrapper( strBaseClassXml.c_str() );
        if (!bRet)
        {
            return FALSE;
        }

        bRet = GoDownstairs();
        if (!bRet)
        {
            return FALSE;
        }

        return TRUE;
    }


    BOOL32 InitXmlToStruct(const char* xmlString);

    template <typename CurrentType, typename BaseType> 
    BOOL32 InitXmlToStructByBaseClass(const char* xmlString, CurrentType& currentType, const BaseType& baseType)
    {        
        BOOL32 bRet = currentType.BaseType::XmlToStruct(xmlString);
        if (!bRet)
        {
            return FALSE;
        }
        
        bRet = InitXmlWrapper(xmlString);
        if (!bRet)
        {
            return FALSE;
        }
       
        bRet = GoDownstairs();
        if (!bRet)
        {
            return FALSE;
        }

        return TRUE;
    }

//private:
public: //理应为private，但终端代码有直接操作成员变量的需求，改成public，直接操作时请小心，尽量避免直接操作
	TiXmlDocument m_cTiXmlDoc;
	TiXmlDeclaration *m_pTiXmlDec;
	TiXmlElement *m_pParentElement;
	TiXmlElement *m_pCurrentElement;
	TiXmlElement *m_pChildElement;
	BOOL32        m_bRootInit;
};

#endif  //_XML_STRUCT_CONVERT_H



