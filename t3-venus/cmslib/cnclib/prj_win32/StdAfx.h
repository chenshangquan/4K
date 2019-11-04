// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__A29FB10A_E1E0_47B7_B453_18472A131EB5__INCLUDED_)
#define AFX_STDAFX_H__A29FB10A_E1E0_47B7_B453_18472A131EB5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#pragma warning( disable : 4786 )	// 标识符名称超过255字节
#pragma warning( disable : 4996 )	// 某些操作（主要是字符串操作）时VS2010会提示使用更安全的函数，但与VC6不兼容，故暂时屏蔽

#include <afx.h>
#include <afxwin.h>

//cms内部共用头文件
#include "cmsConst.h"
#include "evCmsLib.h"

// tp 共用头文件
#include "tpsys.h"

//消息管理
#include "tpeventmgr.h"
#endif // !defined(AFX_STDAFX_H__A29FB10A_E1E0_47B7_B453_18472A131EB5__INCLUDED_)
