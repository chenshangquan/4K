// tpadlib.h: interface for the CTpadLib class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TPADLIB_H__0EE6CC47_C8B2_4333_B5FE_001BDD8DD258__INCLUDED_)
#define AFX_TPADLIB_H__0EE6CC47_C8B2_4333_B5FE_001BDD8DD258__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "tpadsessionif.h"

class CTPadLib  
{
public:
	CTPadLib();
	virtual ~CTPadLib();

    /*功能	创建实现了接口CTPadSessionIF的对象
	参数	ppIf	[out]成功返回CTPadSessionIF接口,失败返回NULL
	返回值	成功返回0,失败返回非0错误码
	说明	接口使用完成后,调用DestroyInstance方法销毁对象*/
	static u16 CreateSession( CTPadSessionIF **ppIf );

	/*功能	销毁实现了接口CTPadSessionIF的对象
	参数	ppIf	[in, out]接口CTPadSessionIF,成功后返回NULL
	返回值	成功返回0,失败返回非0错误码
	说明	只能销毁由CreateSession方法创建的对象*/
	static u16 DestroySession( CTPadSessionIF **ppIf );
};

#endif // !defined(AFX_TPADLIB_H__0EE6CC47_C8B2_4333_B5FE_001BDD8DD258__INCLUDED_)
