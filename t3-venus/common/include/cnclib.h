// cnclib.h: interface for the CCncLib class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNCLIB_H__846EEC8C_FDB4_4222_A2A6_55EC0820D8B3__INCLUDED_)
#define AFX_CNCLIB_H__846EEC8C_FDB4_4222_A2A6_55EC0820D8B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cnsSessionCtrlIF.h"

class CCncLib  
{
public:
	CCncLib();
	virtual ~CCncLib();

	/*功能	创建实现了接口CCnsSessionCtrlIF的对象
	参数	ppICnt	[out]成功返回CCnsSessionCtrlIF接口,失败返回NULL
	返回值	成功返回0,失败返回非0错误码
	说明	接口使用完成后,调用DestroyInstance方法销毁对象*/
	static u16 CreateSession(CCnsSessionCtrlIF **ppICnt);
	/*功能	销毁实现了接口CCnsSessionCtrlIF的对象
	参数	ppICnt	[in, out]接口CCnsSessionCtrlIF,成功后返回NULL
	返回值	成功返回0,失败返回非0错误码
	说明	只能销毁由CreateInstance方法创建的对象*/
	static u16 DestroySession(CCnsSessionCtrlIF **ppICnt);

};

#endif // !defined(AFX_CNCLIB_H__846EEC8C_FDB4_4222_A2A6_55EC0820D8B3__INCLUDED_)
