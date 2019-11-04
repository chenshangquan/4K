// DefaultLogger.cpp: implementation of the CDefaultLogger class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "System.h"
#include "DefaultLogger.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace AutoUIFactory
{

CDefaultLogger::CDefaultLogger()
{

}

CDefaultLogger::~CDefaultLogger()
{
#ifndef _DEBUG
// 	if ( m_file.m_hFile != CFile::hFileNull)
// 	{ 
// 		m_file.Close(); 
// 	}
#endif  
}

bool CDefaultLogger::LogEvent( String strEvent, LogLevel emLoglv /* = Standard */ )
{   
#ifdef _DEBUG
	//TRACE( strEvent.c_str() );
#else
	//添加打印内容输入到文件(最好在本地运行,不要提交到版本机上)--------JYY
	
// 	if ( m_file.m_hFile == CFile::hFileNull)
// 	{
// 		m_file.Open( _T("uiFactory.txt"), CFile::modeWrite | CFile::modeCreate );
// 	}
// 	
// 	if ( m_file.m_hFile != CFile::hFileNull)
// 	{ 
// 		m_file.SeekToEnd();
// 		m_file.Write( strEvent.c_str(), strlen(strEvent.c_str()));	
// 	}
#endif
	return true;
}

}// namespace AutoUIFactory end
 