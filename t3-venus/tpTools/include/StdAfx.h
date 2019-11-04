// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__03859296_6562_41C1_BBF5_E4C0EBC791F2__INCLUDED_)
#define AFX_STDAFX_H__03859296_6562_41C1_BBF5_E4C0EBC791F2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#pragma   warning (disable: 4786)

#include <vector>
#include <algorithm>
                                                                      //应放入tptool的公共文件中 供umstool和cnstool发送
#include "tinyxml.h"
#include "tinystr.h"

#include "uiexhead.h"
#pragma comment(lib,"uiex.lib")

#include "nmscommon.h"
#pragma comment(lib,"nmscommon.lib")

#ifndef _TPTOOLPRJ
#define _TPTOOLPRJ
#endif
#include "globalumstool.h"
#include "cnsToolDllIF.h" //cnstoolDll接口文件
#include "moonToolDllIF.h"
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__03859296_6562_41C1_BBF5_E4C0EBC791F2__INCLUDED_)
