#ifdef UILIB_EXPORTS
#define UILIB_API __declspec(dllexport)
#else
#define UILIB_API __declspec(dllimport)
#endif

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <stddef.h>
#include <richedit.h>
#include <tchar.h>
#include <assert.h>
#include <crtdbg.h>
#include <malloc.h>
#include <stdio.h>
#include <olectl.h>
#include <objbase.h>
#include <shlwapi.h>

//preview
#include <shobjidl.h>
#include <shlobj.h>
#include <thumbcache.h>
#include <atlconv.h>

#include <vector>
#include <string>
#include <map>
#include <set>
#include <list>

#include <gdiplus.h> 
using namespace Gdiplus; 

#pragma comment(lib,"Gdiplus.lib")

#pragma comment( lib, "winmm.lib" )
#pragma comment( lib, "comctl32.lib" )

namespace DuiLib {
#ifdef _UNICODE
	typedef std::basic_string<TCHAR> tString;   //std::wstring
#else
	typedef std::basic_string<char> tString;   //std::string
#endif
}

#ifndef NO_USING_DUILIB_NAMESPACE
using namespace DuiLib;
using namespace std;
#endif

#define MESSAGEWND(x) MessageBox(NULL, x, L"TITLE", MB_OK )     //MessageBox弹出框

#define USE(FEATURE) (defined USE_##FEATURE  && USE_##FEATURE)
#define ENABLE(FEATURE) (defined ENABLE_##FEATURE  && ENABLE_##FEATURE)

#define USE_ZIP_SKIN 1
#define MESSAGE_RICHEDIT_MAX  1024

#define lengthof(x) (sizeof(x)/sizeof(*x))
#define MAX max
#define MIN min
#define CLAMP(x,a,b) (MIN(b,MAX(a,x)))

#pragma warning( disable : 4786 )	// 标识符名称超过255字节
#pragma warning( disable : 4067 )
#pragma warning( disable : 4129 )
#pragma warning( disable : 4503 )
#pragma warning( disable : 4800 )
#pragma warning( disable : 4172 )
#pragma warning( disable : 4996 )

#include "UIBase.h"
#include "UIManager.h"
#include "msghandler.h"

#include "UICommonDef.h"
#include "UICommon.h"

#include "UIDelegate.h"
#include "UIControl.h"
#include "UIContainer.h"
#include "UICommonControls.h"
#include "UIList.h"
#include "UICombo.h"
#include "UIActiveX.h"
#include "UIRichEdit.h"
#include "ControlEx.h"

#include "UIMarkup.h"
#include "UIDlgBuilder.h"
#include "UIRender.h"
#include "logicManager.h"


#include "dlgmanager.h"//2013.5.6

#include "ListUICommonDef.h"
#include "BaseWindowWnd.h"
#include "previewAsisst.h"
//#include "previewImg.h"
#include "previewIF.h"
#include "PreWnd.h"
#include "ListUIDragWnd.h"
#include "CommonListUI.h"

#include "DuiexlibInterface.h"				//外部调用接口类

