#ifndef UIEXBASEDATA_HEAD_H
#define UIEXBASEDATA_HEAD_H

#pragma warning( disable : 4786 ) 
#include <afxtempl.h>
#include <afxole.h>
#include <afxdtctl.h>
#include <map>
#include <vector>
#include <set>

#include "Shlwapi.h"
#pragma comment(lib, "Shlwapi.lib")

#define iterator _iterator

//#define WM_TOUCH_BUTTONDOWN		716    
//win8中使用0x024B来确定手触摸, 716是0x02CC, 587是0x024B 
#define  WM_TOUCH_BUTTONDOWN      587
//281是0x0119
#define WM_GESTURE      281     
//响应WM_TOUCH消息
#define  WM_TOUCH       0x0240


#include "msgIddispatch.h"  
//由于消息越来越多，为便于管理，调整为枚举形式来定义  2013.1.21 yjj
enum EmUiexMsg{
	#define UIEX_MSG_BEGIN  UIEXLIB_MSG_BEGIN + 0x01

		/************************************************************************/
		/**  
		wParam =  
		lparam = 
		/************************************************************************/
		msg_dragOver = UIEX_MSG_BEGIN, 
	#define UI_DRAG_OVER   msg_dragOver  

		msg_dragLeave,
	#define UI_DRAG_LEAVE         msg_dragLeave

		msg_dragEnd,
	#define UI_DRAG_END           msg_dragEnd

		/************************************************************************/
		/**  向被拖拽的窗口发送，通知被拖拽结束
		wParam =  
		lparam = 
		/************************************************************************/
		msg_beDragEnd,
	#define UI_BE_DRAG_END        msg_beDragEnd   
		
		msg_letterIndexClick,
	#define UI_LETTERINDEX_CLICK     msg_letterIndexClick

		msg_editDelClick,
	#define UI_EDITDELETE_CLICK      msg_editDelClick

		msg_sliderBlockEndLock,
	#define UI_SLIDEBLOCK_ENDLOCK    msg_sliderBlockEndLock
		
		/************************************************************************/
		/** slider的滑块位置改变
		wParam =  
		lparam = 
		/************************************************************************/
		msg_sliderChanged,
	#define UI_SLIDER_CHANGED        msg_sliderChanged  
		
		/************************************************************************/
		/** list当前没有选中项的通知
		wParam =  
		lparam = 
		/************************************************************************/
		msg_listUnSelItem,
	#define WM_LST_UN_SELECT_ITEM    msg_listUnSelItem
		
		/************************************************************************/
		/** 重绘消息
		wParam =  
		lparam = 
		/************************************************************************/
		msg_redrawUI,
	#define WM_REDRAW_UI             msg_redrawUI


		/************************************************************************/
		/** 点击事件
		wParam =  
		lparam = 
		/************************************************************************/
		msg_btnClick,
	#define WM_BUTTON_CLICK          msg_btnClick

		/************************************************************************/
		/** 失去焦点
		wParam =  
		lparam = 
		/************************************************************************/
		msg_killFocus,
	#define WM_KILL_FOCUS            msg_killFocus


		/************************************************************************/
		/** 日历选择日期通知   
		wParam =  
		lparam = 
		/************************************************************************/
		msg_calenderSelDate,
	#define UI_CALENDAR_SELECT_DATE  msg_calenderSelDate
		
		/************************************************************************/
		/** 编辑框获取到焦点
		wParam =  
		lparam = 
		/************************************************************************/
		msg_editSetFocus,
	#define WM_EDIT_SETFOCUS         msg_editSetFocus

		/************************************************************************/
		/** 编辑框字符改变消息
		wParam =  
		lparam = 
		/************************************************************************/
		msg_editOnChar,
	#define WM_EDIT_ONCHAR           msg_editOnChar

		/************************************************************************/
		/** 编辑框字符改变消息
		wParam =  
		lparam = 
		/************************************************************************/
		msg_comboxOnChar,
	#define WM_COMBOX_ONCHAR           msg_comboxOnChar

		/************************************************************************/
		/** 编辑框改变消息
		wParam =  
		lparam = 
		/************************************************************************/
		msg_editChanged,
	#define WM_EDIT_CHANGED          msg_editChanged  

		/************************************************************************/
		/** 编辑框改变消息并且当前的焦点并不在编辑框-------JYY  供cnstool使用
		wParam =  
		lparam = 
		/************************************************************************/
		msg_editChangedNoFocus,
	#define WM_EDIT_CHANGED_NOFOCUS         msg_editChangedNoFocus  
			
		/************************************************************************/
		/** 通知被绑的窗口，当前被绑定到的窗口handle
		wParam =  
		lparam = 
		/************************************************************************/
		msg_bindWnd,
	#define WM_BIND_WND              msg_bindWnd

		/************************************************************************/
		/**  通知被绑的窗口，当前被绑定到的窗口隐藏
		wParam =  
		lparam = 
		/************************************************************************/
		msg_bindWndHide,
	#define WM_BIND_WND_HIDE         msg_bindWndHide       

		/************************************************************************/
		/** 通知列表偏移位置 
		wParam =  
		lparam = 
		/************************************************************************/
		msg_listOffsetNty,
	#define UI_LISTOFFSET_NOTIFY     msg_listOffsetNty

		/************************************************************************/
		/** 通知窗口 开始手写了 
		wParam =  
		lparam = 
		/************************************************************************/
		msg_endHandWriteNty,
	#define WM_HAND_END_WRITE_NOTIFY    msg_endHandWriteNty

		/************************************************************************/
		/** 通知窗口 开始手写了 
		wParam =  
		lparam = 
		/************************************************************************/
		msg_beginHandWriteNty,
	#define WM_HAND_BEGIN_WRITE_NOTIFY  msg_beginHandWriteNty

		/************************************************************************/
		/** btn is press in a period  --SXC
		wParam =  
		lparam = 
		/************************************************************************/
		msg_btnHold,
	#define WM_BTN_HOLD                msg_btnHold

		msg_btnHoldEnd,
	#define WM_BTN_HOLD_END             msg_btnHoldEnd

		/************************************************************************/
		/**  软键盘显示
		wParam =  
		lparam = 
		/************************************************************************/
		msg_softKBShow,
	#define WM_SOFTKEYBOARD_SHOW        msg_softKBShow   
		
		/************************************************************************/
		/**  软键盘隐藏
		wParam =  
		lparam = 
		/************************************************************************/
		msg_softKBHide,
	#define WM_SOFTKEYBOARD_HIDE        msg_softKBHide
		
		/************************************************************************/
		/** 拖动滑动条，通知列表更新   
		wParam =  
		lparam = 
		/************************************************************************/
		msg_LstUpdateProgress,
	#define WM_LIST_UPDATEPROGRESS      msg_LstUpdateProgress
		
			 
		/************************************************************************/
		/** 更新transparentcombobox编辑框数据
		wParam =  
		lparam = 
		/************************************************************************/
		msg_updateCombEditTxt,
	#define WM_UPDATE_COMBOEDIT_TEXT      msg_updateCombEditTxt


		/************************************************************************/
		/** 点击transparentcombobox列表
		wParam =  
		lparam = 
		/************************************************************************/
		msg_ClickCombList,
	#define WM_CLICK_COMBOLIST      msg_ClickCombList
	 
		/************************************************************************/
		/**响应点击transparentcombobox列表事件
		wParam =  
		lparam = 
		/************************************************************************/
		msg_clickCombLstIcon,
	#define WM_CLICK_COMBOLISTICON        msg_clickCombLstIcon

		/************************************************************************/
		/**鼠标移动transparentcombobox图标显示事件
		wParam =  
		lparam = 
		/************************************************************************/
		msg_mousemoveCombLstShowIcon,
	#define WM_MOUSEMOVE_COMBOLISTSHOWICON        msg_mousemoveCombLstShowIcon

		/************************************************************************/
		/**自定义隐藏窗口事件
		wParam =  
		lparam = 
		/************************************************************************/
		msg_hideWnd,
	#define WM_HIDE_WND        msg_hideWnd
		
		/************************************************************************/
		/**子窗口失去焦点事件
		wParam =  
		lparam = 
		/************************************************************************/
		msg_childWndInActive,
	#define WM_CHILDWND_INACTIVE        msg_childWndInActive

        /************************************************************************/
		/**  通知窗口，当前窗口被隐藏   2013.dyy
		wParam =  
		lparam = 
		/************************************************************************/
		msg_UIWndHide,
	#define UI_WND_HIDE               msg_UIWndHide    

        /************************************************************************/
		/** 收到此消息后做Domodal操作
		wParam =  
		lparam = 
		/************************************************************************/
		msg_postdomodal,
	#define WM_POST_DOMODAL          msg_postdomodal

		/************************************************************************/
		/** 通知列表字母索引的指针
		wParam = NULL
		lparam = CWND*:字母索引指针
		/************************************************************************/
		msg_bindlist,
	#define WM_BIND_LIST          msg_bindlist

        /************************************************************************/
		/** 通知所有子窗口父窗口隐藏 Bug00167582
		wParam = NULL
		lparam = NULL
		/************************************************************************/
		msg_parenthide,
	#define WM_PARENT_HIDE        msg_parenthide

		/************************************************************************/
		 /**	拖拽到指定的edit上时，发送消息通知edit高亮
			wParam = 
			lparam = 0*/
		/************************************************************************/ 
	    msg_editselected  ,
#define WM_EDIT_SELECTED msg_editselected

		/************************************************************************/
		 /**	拖离指定的edit时，edit状态还原
			wParam = 
			lparam = 0*/
		/************************************************************************/ 
	    msg_editleave  ,
#define WM_EDIT_LEAVE msg_editleave

		/************************************************************************/
        /** 单击鼠标左键消息 dyy 2014年4月28日 响应文档摄像机点击down时发送actBegin消息
		wParam = NULL
		lparam = NULL
		/************************************************************************/
        msg_buttondwon,
#define WM_BUTTON_DOWN        msg_buttondwon
	
        /************************************************************************/
        /** 鼠标状态还原消息
		wParam = NULL
		lparam = NULL
		/************************************************************************/
        msg_buttonstatus_normal,
#define WM_BUTTONSTATUS_NORMAL    msg_buttonstatus_normal
};



//发送WM_LBUTTONDOWN的来源
#define FLAG_TRANSBASEDLG        0
#define FLAG_TRANSBASEWND        2
#define FLAG_TOUCHBUTTONDOWN     3

#ifdef _DEBUG 

static int nGdiPlusObjects = 0;


namespace Gdiplus
{
	namespace DllExports
	{
		#include <GdiplusMem.h>
	};

	#ifndef _GDIPLUSBASE_H
	#define _GDIPLUSBASE_H
	class GdiplusBase
	{
		public:
			void (operator delete)(void* in_pVoid)
			{
				nGdiPlusObjects--;
				DllExports::GdipFree(in_pVoid);
			}

			void* (operator new)(size_t in_size)
			{
				nGdiPlusObjects++;
				return DllExports::GdipAlloc(in_size);
			}

			void (operator delete[])(void* in_pVoid)
			{
				nGdiPlusObjects--;
				DllExports::GdipFree(in_pVoid);
			}

			void* (operator new[])(size_t in_size)
			{
				nGdiPlusObjects++;
				return DllExports::GdipAlloc(in_size);
			}

			void * (operator new)(size_t nSize, LPCSTR /*lpszFileName*/, int /*nLine*/)
			{
				nGdiPlusObjects++;
				return DllExports::GdipAlloc(nSize);
			}

			void operator delete(void* p, LPCSTR /*lpszFileName*/, int /*nLine*/)
			{
				nGdiPlusObjects--;
				DllExports::GdipFree(p);
			}

		};
	#endif // #ifndef _GDIPLUSBASE_H
}
#endif // #ifdef _DEBUG

#ifndef   ULONG_PTR   
#define   ULONG_PTR   unsigned   long*   
#endif

#include <gdiplus.h>
#ifdef _MFC_VER
#include <afx.h>
#endif
#undef iterator

using namespace Gdiplus;
#pragma comment (lib, "Gdiplus.lib")

class QGdiPlus
{
public:
	QGdiPlus(): m_Token(0)	{ 
		Gdiplus::GdiplusStartupInput input; 
		Gdiplus::GdiplusStartup(& m_Token, & input, NULL); 
	}
	~QGdiPlus()
	{
		Gdiplus::GdiplusShutdown(m_Token);
#ifdef _DEBUG
#ifdef _MFC_VER
		if (nGdiPlusObjects > 0)
			afxDump << _T(">>> GdiPlus Memory Leaks: ") << nGdiPlusObjects << _T(" objects! <<<\n");
		else if (nGdiPlusObjects < 0)
			afxDump << _T(">>> GdiPlus Multiple Deletes: ") << -nGdiPlusObjects << _T(" objects! <<<\n");
#endif
#ifdef _ATL_VER
		if (nGdiPlusObjects > 0)
			ATLTRACE2(_T(">>> GdiPlus Memory Leaks: %d objects! <<<\n"), nGdiPlusObjects);
		else if (nGdiPlusObjects < 0)
			ATLTRACE2(_T(">>> GdiPlus Multiple Deletes: %d objects! <<<\n"), -nGdiPlusObjects);
#endif
#endif
	}
private:
	// The token we get from GDI+
	ULONG_PTR m_Token;
};





 



typedef std::string String;
#include "templateClass.h"
using namespace AutoUIFactory;
using namespace std; 



class Args_Graphics : public IArgs
{
public:
	Args_Graphics( Graphics* pGraphics, Rect rc, CPoint pt = 0 ) : IArgs( "Graphics") ,
		m_pGraphics( pGraphics ), m_rc( rc ),m_ptOffset(pt){}
	Graphics* m_pGraphics;
	Rect m_rc;
	CPoint m_ptOffset;  	//  2012-8-6 解决xp、ocx中列表只能显示七八百个条目的问题 by yjj
};


typedef BOOL(WINAPI *PFN_UpdateLayeredWindow)( 
                                              HWND hWnd,
                                              HDC hdcDst,
                                              POINT *pptDst,
                                              SIZE *psize,
                                              HDC hdcSrc,
                                              POINT *pptSrc,
                                              COLORREF crKey,
                                              BLENDFUNCTION *pblend,
											  DWORD dwFlags);

#ifndef WS_EX_LAYERED
#	define WS_EX_LAYERED			0x00080000
#endif

#ifndef LWA_ALPHA
#	define LWA_ALPHA				0x00000002
#endif

#ifndef ULW_ALPHA
#	define ULW_ALPHA				0x00000002
#endif





#define NOTIF_PARENT_WND \
	if ( GetParent() != NULL ) \
{		\
	GetParent()->SendMessage( WM_REDRAW_UI, NULL, /*(LPARAM)m_hWnd*/ (LPARAM)0  ); \
}
#define NOTIF_ALL_WND \
	if ( GetParent() != NULL ) \
{		\
	GetParent()->SendMessage( WM_REDRAW_UI, NULL, (LPARAM)0 ); \
}

#define NOTIF_PARENT_WND_IMMEDIATLY_DRAW \
	if ( GetParent() != NULL ) \
{		\
	GetParent()->SendMessage( WM_REDRAW_UI, NULL, 1 ); \
}




// 
template <class T> class TransparentAssist
{
public:
	typedef LRESULT (CALLBACK* WNDPROC)( HWND,UINT,WPARAM,LPARAM);
	static WNDPROC m_pWndProc;
	void RegsiterWndProc()
	{
		T* pObject = (T*)this;
		m_pWndProc = (WNDPROC)GetWindowLong( pObject->m_hWnd, GWL_WNDPROC );
		::SetWindowLong( pObject->m_hWnd,GWL_WNDPROC,(LONG)AssistProc );
	}
	static LRESULT CALLBACK AssistProc( HWND hWnd , UINT message, WPARAM wParam, LPARAM lParam )
	{
		LRESULT ret = CallWindowProc( m_pWndProc, hWnd, message, wParam, lParam );
		HWND hParent = ::GetParent( hWnd );
#define UPDATEUI_ALL SendMessage( hParent, WM_REDRAW_UI, 0, (LPARAM)0 );
#define UPDATEUI_SUB SendMessage( hParent, WM_REDRAW_UI, 0, (LPARAM)hWnd );	
		switch ( message )
		{
		case WM_SIZING:
			{
				if ( IsWindowVisible( hParent ) )
				{
					UPDATEUI_ALL
				}
			}
			break;
		case WM_MOVING:
			{
				if ( IsWindowVisible( hParent ) )
				{
					UPDATEUI_ALL
				}
			}
			break;
		default:
			break;
		}
		return ret;
	}		
};



class IData
{
public:
	IData( std::string strType ) : m_strType( strType ), m_dwKey( -1 ){}
	virtual ~IData(){}
	std::string GetType() const { return m_strType; } 
	unsigned long GetDataKey() { return m_dwKey; }
	void SetDataKey( unsigned long dwKey ) { m_dwKey = dwKey; }
	
	virtual IData* Clone() = 0;
protected:
	unsigned long m_dwKey;      //Data键值，用于查找Item
	std::string m_strType;
};


/*
 * Gesture IDs
 */
#define GID_BEGIN                       1
#define GID_END                         2
#define GID_ZOOM                        3
#define GID_PAN                         4
#define GID_ROTATE                      5
#define GID_TWOFINGERTAP                6
#define GID_PRESSANDTAP                 7
#define GID_ROLLOVER                    GID_PRESSANDTAP


#define GF_BEGIN                        0x00000001
#define GF_INERTIA                      0x00000002
#define GF_END                          0x00000004




DECLARE_HANDLE(HGESTUREINFO);

/*
 * Gesture information structure
 *   - Pass the HGESTUREINFO received in the WM_GESTURE message lParam into the
 *     GetGestureInfo function to retrieve this information.
 *   - If cbExtraArgs is non-zero, pass the HGESTUREINFO received in the WM_GESTURE
 *     message lParam into the GetGestureExtraArgs function to retrieve extended
 *     argument information.
 */
typedef struct tagGESTUREINFO {
    UINT cbSize;                    // size, in bytes, of this structure (including variable length Args field)
    DWORD dwFlags;                  // see GF_* flags
    DWORD dwID;                     // gesture ID, see GID_* defines
    HWND hwndTarget;                // handle to window targeted by this gesture
    POINTS ptsLocation;             // current location of this gesture
    DWORD dwInstanceID;             // internally used
    DWORD dwSequenceID;             // internally used
    ULONGLONG ullArguments;         // arguments for gestures whose arguments fit in 8 BYTES
    UINT cbExtraArgs;               // size, in bytes, of extra arguments, if any, that accompany this gesture
} GESTUREINFO, *PGESTUREINFO;
typedef GESTUREINFO const * PCGESTUREINFO;

/*
 * Gesture configuration structure
 *   - Used in SetGestureConfig and GetGestureConfig
 *   - Note that any setting not included in either GESTURECONFIG.dwWant or
 *     GESTURECONFIG.dwBlock will use the parent window's preferences or
 *     system defaults.
 */
typedef struct tagGESTURECONFIG {
    DWORD dwID;                     // gesture ID
    DWORD dwWant;                   // settings related to gesture ID that are to be turned on
    DWORD dwBlock;                  // settings related to gesture ID that are to be turned off
} GESTURECONFIG, *PGESTURECONFIG;


/*
 * Gesture configuration flags - GESTURECONFIG.dwWant or GESTURECONFIG.dwBlock
 */

/*
 * Common gesture configuration flags - set GESTURECONFIG.dwID to zero
 */
#define GC_ALLGESTURES                              0x00000001

/*
 * Zoom gesture configuration flags - set GESTURECONFIG.dwID to GID_ZOOM
 */
#define GC_ZOOM                                     0x00000001

/*
 * Pan gesture configuration flags - set GESTURECONFIG.dwID to GID_PAN
 */
#define GC_PAN                                      0x00000001
#define GC_PAN_WITH_SINGLE_FINGER_VERTICALLY        0x00000002
#define GC_PAN_WITH_SINGLE_FINGER_HORIZONTALLY      0x00000004
#define GC_PAN_WITH_GUTTER                          0x00000008
#define GC_PAN_WITH_INERTIA                         0x00000010

/*
 * Rotate gesture configuration flags - set GESTURECONFIG.dwID to GID_ROTATE
 */
#define GC_ROTATE                                   0x00000001

/*
 * Two finger tap gesture configuration flags - set GESTURECONFIG.dwID to GID_TWOFINGERTAP
 */
#define GC_TWOFINGERTAP                             0x00000001

/*
 * PressAndTap gesture configuration flags - set GESTURECONFIG.dwID to GID_PRESSANDTAP
 */
#define GC_PRESSANDTAP                              0x00000001
#define GC_ROLLOVER                                 GC_PRESSANDTAP

#define GESTURECONFIGMAXCOUNT           256             // Maximum number of gestures that can be included
 



                                                       // in a single call to SetGestureConfig / GetGestureConfig

typedef BOOL (*WINSDK_GetGestureInfo)( HGESTUREINFO hgi, GESTUREINFO& gi );
typedef BOOL (*WINSDK_SetGestureConfig)( HWND hwnd, DWORD dwReserved, UINT cIDs, PGESTURECONFIG pGestureConfig, UINT cbSize );




/*
 * Touch input flag values (TOUCHINPUT.dwFlags)
 */
#define TOUCHEVENTF_MOVE            0x0001
#define TOUCHEVENTF_DOWN            0x0002
#define TOUCHEVENTF_UP              0x0004
#define TOUCHEVENTF_INRANGE         0x0008

//WM_TOUCH消息结构体
typedef struct tagTOUCHINPUT {
    LONG x;
    LONG y;
    HANDLE hSource;
    DWORD dwID;
    DWORD dwFlags;
    DWORD dwMask;
    DWORD dwTime;
    ULONG_PTR dwExtraInfo;
    DWORD cxContact;
    DWORD cyContact;
} TOUCHINPUT, *PTOUCHINPUT;
typedef TOUCHINPUT const * PCTOUCHINPUT;


typedef VOID (*WINSDK_RegTouchWindow)(HWND hWnd);
typedef BOOL (*WINSDK_GetTouchInputInfo)( LPARAM lParam, UINT cInputs, TOUCHINPUT& tInput );
typedef BOOL (*WINSDK_GetTouchInputPoint)( LPARAM lParam, UINT cInputs, POINT& ptInput );

#define TOUCH_COORD_TO_PIXEL(l)         ((l) / 100)

#endif