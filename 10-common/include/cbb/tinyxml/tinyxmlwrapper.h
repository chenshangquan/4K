/* CTinyXMLWrapper 1.0

  The tinyxml is encapsulated by CTinyXMLWrapper.  
The purpose of encapsulation is to make the use of 
tinyxml more easier and convenient. With the help of
CTinyXMLWander, you don't have to know what exactly the 
tinyxml is and how to use numerous fussy member functions 
in tinyxml. All you know is Add/Remove and Navigation.
By such useful functions, you can access every single 
detail about the XML Tree freely.It is amazing, isn't it? 
So enjoy the CTinyXMLWrapper.

Author:WangXiaoyi  Date:20100106 
if find bugs or good tips, please contact me.
*/
#ifndef _TINYXMLWRAPPER_H
#define _TINYXMLWRAPPER_H

#include <stdarg.h>
#include "tinyxml.h"
#include "kdvtype.h"
#include "tinyxml_export.h"

//lint -sem(CTinyXMLWrapper::ClearXML,cleanup)
class TINYXML_API CTinyXMLWrapper
{
public:

	CTinyXMLWrapper();

	~CTinyXMLWrapper();

	//load document to initialize the object of the CTinyXMLWander
	BOOL32 LoadXMLDocument( const char *pDocumentName ,  TiXmlEncoding emEncoding = TIXML_ENCODING_LEGACY);

	//save the xml tree by a given filename
	void SaveXMLDocument( const char *pDocumentName );

	//save the xml tree ( filename has been given before )
	void SaveXMLDocument();

	//transform the xml struct into characters
	//user has to allocate space for pBuffer and nSize is value-result argument 
	BOOL32 TramsformXML2Chars( char *pBuffer, unsigned long &nSize );

	//transform the characters into xml struct
	void TransformChars2XML(const char *pchars );

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
	BOOL32 FindElementInDepth( const int nDepth, const char *p1stValue, ... );

	//create the root node
	BOOL32 CreateRootNode(const char *pValue);

	//get the value of the current element
	const char *GetValue();

	//set the value of the current element
	BOOL32 SetValue( const char *pValue );

	//add a sibling for the current
	BOOL32 AddElement( const char *pValue );

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

private:
	TiXmlDocument m_cTiXmlDoc;
	TiXmlDeclaration *m_pTiXmlDec;
	TiXmlElement *m_pParentElement;
	TiXmlElement *m_pCurrentElement;
	TiXmlElement *m_pChildElement;
	BOOL32        m_bRootInit;
};
#endif