// DefaultXmlParser.cpp: implementation of the DefaultXmlParser class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "System.h"
#include "DefaultXmlParser.h"
#include "IXmlHanlde.h"
#include "XmlAttrib.h"
#include "SystemXmlHandle.h"
#include "DefaultLogger.h"
#include "tinyxml.h"
#include "tinystr.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace AutoUIFactory
{

using namespace AutoTinyXml;

#define XML_FILE_BUFF_SIZE 200

class TinyXMLDocument : public TiXmlDocument
{
public:
	TinyXMLDocument(IXmlHanlde& handler, const String& filename );
	~TinyXMLDocument()
	{}
protected:
	void processElement(const TiXmlElement* element);
	
private:
	IXmlHanlde* d_handler;
};

TinyXMLDocument::TinyXMLDocument( IXmlHanlde& handler, const String& filename )
{
	if (  filename.empty() )// 名称为空就不解析，防止崩溃 2012.11.30 by yjj
	{
		LOGEVENT("[TinyXMLDocument]文件名为空 ");
		return;
	}

	d_handler = &handler;
	
	try
    {   
		// Parse the document
		TiXmlDocument *myDocument = new TiXmlDocument(filename.c_str());
		bool re = myDocument->LoadFile();
        if ( !re )
        {
            LOGEVENT("[TinyXMLDocument]myDocument->LoadFile(" + filename + " ) = false ");
        }
		
		const TiXmlElement* currElement = myDocument->RootElement();
		if (currElement)
        {    
			// function called recursively to parse xml data
			processElement(currElement);
		} // if (currElement)
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


void TinyXMLDocument::processElement(const TiXmlElement* element)
{
	// build attributes block for the element
	XMLAttributes attrs;
	
	const TiXmlAttribute *currAttr = element->FirstAttribute();
	while (currAttr)
	{
		attrs.add((char*)currAttr->Name(), (char*)currAttr->Value());
		currAttr = currAttr->Next();
	}
	// start element
	d_handler->ElementStart((char*)element->Value(), attrs);
	
	// do children
	const TiXmlNode* childNode = element->FirstChild();
	while (childNode)
	{
		switch(childNode->Type())
		{
		case TiXmlNode::TINYXML_ELEMENT:
			processElement(childNode->ToElement());
			break;
		default:
			break;
		};
		childNode = childNode->NextSibling();
	}
	
	// end element
	d_handler->ElementEnd((char*)element->Value());
}


bool DefaultXmlParser::ParserXml(IXmlHanlde* piXmlHandle, String strFileName)
{   
    
	TinyXMLDocument doc( *piXmlHandle, strFileName );
	return true;
}


bool DefaultXmlParser::initialiseImpl(void)
{
	return true;
}

void DefaultXmlParser::cleanupImpl(void)
{}

} // namespace AutoUIFactory end
