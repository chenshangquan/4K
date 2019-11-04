// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__4980F6B9_0DE1_41E5_A5AA_3C4D4E800462__INCLUDED_)
#define AFX_STDAFX_H__4980F6B9_0DE1_41E5_A5AA_3C4D4E800462__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

 
#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC Automation classes
#endif // _AFX_NO_OLE_SUPPORT
 

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>			// MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>			// MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT
 

#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#pragma warning( disable : 4786 )	// 标识符名称超过255字节
#pragma warning( disable : 4503 )
#pragma warning( disable : 4800 )
 

#include "kdvtype.h"
#include "kdvsys.h"

#include "nmscommon.h"
#include "uifactorylib.h"  

#include "cmsconst.h"
#include "evCmsLib.h" 

#include "cnsToolConst.h"

#include "tptooldef.h" 

#include "cnclibdatamgr.h"
#include "cnclibcommonif.h"
#include "msgdispatch.h"
#include "uiDataMgr.h"
#include "confsign.h"

#include "uiDataType.h"
#include "listAssist.h"
#include "msgBoxLogic.h"
#include "logicMgr.h"
#include "globaldefine.h"
#include "netcapture.h"

extern HWND g_hNotifyWnd; //向dll外部的窗口发送通知

#pragma comment(lib, "nmscommon.lib") 
#pragma comment(lib, "wininet.lib")


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__4980F6B9_0DE1_41E5_A5AA_3C4D4E800462__INCLUDED_)
