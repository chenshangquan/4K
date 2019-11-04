// WindowFactory.cpp: implementation of the CWindowFactory class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "System.h"
#include "WindowFactory.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace AutoUIFactory
{

const DWORD IWindowFactory::m_dwDefaultStyle = 0 ;
const DWORD IWindowFactory::m_dwDebugStyle = 0;//WS_THICKFRAME;
const CRect IWindowFactory::m_rcDefaultRect = CRect(0,0,0,0);
const char	CWindowDefaultStyleMap::m_chPartitionChar = '|';
std::map< String, DWORD >  CWindowDefaultStyleMap::m_mapStyles;
bool CWindowDefaultStyleMap::StringToStyle( String& str, DWORD& dwStyle )
{
	stringstream ss( str );
	string sub_str;
	DWORD dwResult = 0;
	bool bFind = false;
	while( getline( ss, sub_str, CWindowDefaultStyleMap::m_chPartitionChar ) )         
	{
		DefaultStyleMap::iterator itr = m_mapStyles.find( sub_str );
	
		if ( itr != m_mapStyles.end() )
		{		
			dwResult |= itr->second;
			bFind = true;					
		}	
	}
	dwStyle = dwResult;
	return bFind;
}


bool CWindowDefaultStyleMap::StringToStyle( String& str, DWORD& dwStyle, DWORD& dwStyleEx )
{
    stringstream ss( str );
    string sub_str;
    DWORD dwResult = 0;
    bool bFind = false;
    while( getline( ss, sub_str, CWindowDefaultStyleMap::m_chPartitionChar ) )         
    {
        DefaultStyleMap::iterator itr = m_mapStyles.find( sub_str );
        
        if ( itr != m_mapStyles.end() )
        {	
            if ( sub_str.find("EX"))
            {
                dwStyleEx |= itr->second;
            }
            else
            {
               dwResult |= itr->second;
            }
            
            bFind = true;					
        }	
    }
    dwStyle = dwResult;
    return bFind;
}


bool CWindowDefaultStyleMap::RegStyle( DWORD dwStyle, String str )
{
	DefaultStyleMap::iterator itr = m_mapStyles.find( str );
	if ( itr == m_mapStyles.end() )
	{
		m_mapStyles.insert( DefaultStyleMap::value_type( str, dwStyle) );
		return true;
	}
	return false;
}

} // namespace AutoUIFactory end
