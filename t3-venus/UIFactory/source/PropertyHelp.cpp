// PropertyHelp.cpp: implementation of the CPropertyHelp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "System.h"
#include "PropertyHelp.h"
#include "SystemInfoManage.h"
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
CPropertyHelp::CPropertyHelp()
{

}

CPropertyHelp::~CPropertyHelp()
{

}

float CPropertyHelp::stringToFloat(const String& str)
{
	using namespace std;
	
	float val = 0;
	sscanf(str.c_str(), "%g", &val);
	
	return val;
}

String CPropertyHelp::floatToString(float val)
{
	using namespace std;
	
	char buff[64];
	_snprintf(buff, sizeof (buff), "%g", val);
	
	return String(buff);
}

int CPropertyHelp::stringToInt(const String& str)
{
	using namespace std;
	
	int val = 0;
	sscanf(str.c_str(), "%d", &val);
	
	return val;
}

String CPropertyHelp::intToString(int val)
{
	using namespace std;
	
	char buff[64];
	_snprintf(buff, sizeof (buff), "%d", val);
	
	return String(buff);
}

bool CPropertyHelp::stringToBool(const String& str)
{
	if ((str == "True") || (str == "true") || (str == "1"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

String CPropertyHelp::boolToString(bool val)
{
	if (val)
	{
		return String("True");
	}
	else
	{
		return String ("False");
	}
}

POINT CPropertyHelp::stringToPoint(const String& str)
{
	POINT val;
	sscanf(str.c_str(), "x:%d y:%d", &val.x, &val.y);
	return val;
}

String CPropertyHelp::pointToString(const POINT& val)
{
	using namespace std;
	
	char buff[128];
	_snprintf(buff, sizeof (buff), "x:%d y:%d", val.x, val.y);
	
	return String(buff);
}

SIZE CPropertyHelp::stringToSize(const String& str)
{
	SIZE val;
	sscanf(str.c_str(), "x:%d y:%d", &val.cx, &val.cy);
	return val;	
}

String CPropertyHelp::sizeToString(const SIZE& val)
{
	using namespace std;
	
	char buff[128];
	_snprintf(buff, sizeof (buff), "x:%d y:%d", val.cx, val.cy);
	
	return String(buff);
}

COLORREF CPropertyHelp::stringToColor(const String& str)
{
	unsigned int r = 0;
	unsigned int g = 0;
	unsigned int b = 0;
	sscanf(str.c_str(), "r:%d g:%d b:%d",&r,&g,&b);
	return RGB(r,g,b);	
}

String	CPropertyHelp::colorToString(const COLORREF& col)
{
	char buff[128];
	_snprintf(buff, sizeof (buff), "r:%d g:%d b:%d", GetRValue(col), GetGValue(col), GetBValue(col));
	return String(buff);
}


RECT CPropertyHelp::stringToRect(const String& str)
{
	RECT rc;
	sscanf(str.c_str(), "b:%d t:%d l:%d r:%d",&rc.bottom,&rc.top,&rc.left,&rc.right);
	return rc;
}

String CPropertyHelp::rectToString(const RECT& rc)
{
	char buff[128];
	_snprintf(buff, sizeof (buff), "b:%d t:%d l:%d r:%d",rc.bottom,rc.top,rc.left,rc.right);
	return String(buff);
}

DWORD CPropertyHelp::StringToDWORD(const String& str)
{
	using namespace std;
	
	float val = 0;
	sscanf(str.c_str(), "%l", &val);
	
	return val;
}
String  CPropertyHelp::DWORDToString(const DWORD&val)
{
	using namespace std;
	
	char buff[64];
	_snprintf(buff, sizeof (buff), "%d", val);
	
	return String(buff);
}

void CPropertyHelp::StringToRange( const String& str, int &nMin, int &nMax)
{ 
    sscanf(str.c_str(), "min:%d max:%d", &nMin, &nMax); 
}

String CPropertyHelp::RangeToString(int nMin, int nMax)
{
    using namespace std;
    
    char buff[128];
    _snprintf(buff, sizeof (buff), "min:%d max:%d", nMin, nMax);
    
	return String(buff);
}

StringAlignment CPropertyHelp::stringToAlignment(const String& str)
{
	if ( str == "StringAlignmentNear" || str == "0" )
	{
		return StringAlignmentNear;
	}
	else if (str == "StringAlignmentCenter" || str == "1")
	{
		return StringAlignmentCenter;
	}
	else if (str == "StringAlignmentFar" || str == "2")
	{
		return StringAlignmentFar;
	}
	return StringAlignmentNear;
}

String CPropertyHelp::alignmentToString(const StringAlignment& align)
{
	String str;
	if ( align == StringAlignmentNear )
	{
		str = "StringAlignmentNear";
	}
	else if ( align == StringAlignmentCenter )
	{
		str = "StringAlignmentCenter";
	}
	else
	{
		str = "StringAlignmentFar";
	}
	return str;
}


FontStyle CPropertyHelp::stringToFontStyle(const String& str)
{
    if ( str == "FontStyleRegular" || str == "0" )
    {
        return FontStyleRegular;
    }
    else if (str == "FontStyleBold" || str == "1")
    {
        return FontStyleBold;
    }
    else if (str == "FontStyleItalic" || str == "2")
    {
        return FontStyleItalic;
    }
    else if (str == "FontStyleBoldItalic" || str == "3")
    {
        return FontStyleBoldItalic;
    }
    else if (str == "FontStyleUnderline" || str == "4")
    {
        return FontStyleUnderline;
    }
    else if (str == "FontStyleStrikeout" || str == "8")
    {
        return FontStyleStrikeout;
    }
	return FontStyleRegular;
}

String CPropertyHelp::fontStyleToString(const FontStyle& style)
{
    String str;
    if ( style == FontStyleRegular )
    {
        str = "FontStyleRegular";
    }
    else if ( style == FontStyleBold )
    {
        str = "FontStyleBold";
    }
    else if ( style == FontStyleItalic )
    {
        str = "FontStyleItalic";
    }
    else if ( style == FontStyleBoldItalic )
    {
        str = "FontStyleBoldItalic";
    }
    else if ( style == FontStyleUnderline )
    {
        str = "FontStyleUnderline";
    }
    else
    {
        str = "FontStyleStrikeout";
    }
    return str;
}


//当前分辨率和原分辨率的比值
void CPropertyHelp::GetResolutionScale( float &fx, float &fy)
{ 
    
    int oriX,oriY;
    CSystemInfoManage::GetSingletonPtr()->GetResolution( oriX, oriY);
    
    long curX =  GetSystemMetrics(SM_CXSCREEN );
    long curY = GetSystemMetrics(SM_CYSCREEN);
    
    if ( oriX != 0 )
    {
        fx =  (float)curX / oriX;
    }
    
    if ( oriY != 0 )
    {
        fy =  (float)curY / oriY;
    }
    
}

//分辨率自适应
void CPropertyHelp::ResolutionAdp( long &nx, long &ny)
{
    if ( !CSystemInfoManage::GetSingletonPtr()->IsSelAdpResolution() )
        return ;
    
    
    int oriX,oriY;
    CSystemInfoManage::GetSingletonPtr()->GetResolution( oriX, oriY);
    
    long curX =  GetSystemMetrics(SM_CXSCREEN );
    long curY = GetSystemMetrics(SM_CYSCREEN);
    
    if ( oriX != 0 )
    {
        nx = nx* curX / oriX;
    }
    
    if ( oriY != 0 )
    {
        ny = ny* curY / oriY;
    }
    
}

//字体大小自适应
void CPropertyHelp::FontSizeAdp( int &nFontSize )
{   
    //若设置为不变化，则不进行自适应变化
    if ( !CSystemInfoManage::GetSingletonPtr()->IsSelAdpResolution() )
        return ;
    
    
    // 字体随分辨率等比变化 2012-2-9 by yjj
    float fx, fy;
    CPropertyHelp::GetResolutionScale( fx, fy );
    if ( fx < fy )
    {
        fx  = fy;
    }
    
    nFontSize *= fx; 
    
}

} // namespace AutoUIFactory end
