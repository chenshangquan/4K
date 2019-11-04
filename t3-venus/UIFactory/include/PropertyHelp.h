// PropertyHelp.h: interface for the CPropertyHelp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROPERTYHELP_H__367F886B_837E_4680_8867_1BA68DBF1481__INCLUDED_)
#define AFX_PROPERTYHELP_H__367F886B_837E_4680_8867_1BA68DBF1481__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "uifactorydef.h"

 
#include "list.h"
#include "IValue.h"
namespace AutoUIFactory
{
/*---------------------------------------------------------------------
* 类	名：CPropertyHelp
* 功    能：提供一些公用的属性转换
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2011/06/02	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
class CPropertyHelp  
{
public:
	CPropertyHelp();
	virtual ~CPropertyHelp();
public:
	static	float		stringToFloat(const String& str);
	static	String		floatToString(float val);

	static	int			stringToInt(const String& str);
	static	String		intToString(int val);

	static	bool		stringToBool(const String& str);
	static	String		boolToString(bool val);

	static	POINT		stringToPoint(const String& str);
	static	String		pointToString(const POINT& val);

	static	SIZE		stringToSize(const String& str);
	static	String		sizeToString(const SIZE& val);

	static  COLORREF	stringToColor(const String& str); 
	static	String		colorToString(const COLORREF& col);
	
	static	RECT		stringToRect(const String& str);
	static	String		rectToString(const RECT& rc);

	static DWORD		StringToDWORD(const String& str);
	static String       DWORDToString(const DWORD&val);

    static void         StringToRange( const String& str, int &nMin, int &nMax);
    static String       RangeToString(int nMin, int nMax);

	static StringAlignment stringToAlignment(const String& str);
	static String		alignmentToString(const StringAlignment& align);

    static FontStyle    stringToFontStyle(const String& str);
	static String		fontStyleToString(const FontStyle& align);

    //当前分辨率和原分辨率的比值
    static void CPropertyHelp::GetResolutionScale( float &fx, float &fy);

    //分辨率自适应
    static void ResolutionAdp( long &nx, long  &ny);

    //字体大小自适应
    static void  FontSizeAdp( int &nFontSize );
   
};

 
}// namespace AutoUIFactory end

#endif // !defined(AFX_PROPERTYHELP_H__367F886B_837E_4680_8867_1BA68DBF1481__INCLUDED_)
