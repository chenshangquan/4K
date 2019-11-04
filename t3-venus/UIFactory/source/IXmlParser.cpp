// IXmlParser.cpp: implementation of the IXmlParser class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "System.h"
#include "IXmlParser.h"
#include "IXmlHanlde.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

namespace AutoUIFactory
{
template<> IXmlParser* Singleton<IXmlParser>::ms_pSingleton  = 0;

IXmlParser::IXmlParser()
{

}

IXmlParser::~IXmlParser()
{

}

} // namespace AutoUIFactory end
