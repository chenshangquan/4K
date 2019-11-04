/*=======================================================================
模块名      : UILibHead.h
文件名      : SkinDDListCtrl.cpp
相关文件    : 
文件实现功能: 
作者        : 李洪强
版本        : V1.0  Copyright(C) 2003-2005 KDC, All rights reserved.
-------------------------------------------------------------------------
修改记录:
日  期      版本  修改人  修改内容
2004/07/16  1.0   李洪强  创建
=======================================================================*/

#include "stdafx.h"
#include "UILibHead.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CSkinDDListCtrl::CSkinDDListCtrl()
{
    m_hRevMsgWnd = NULL;
    m_pcDropTarget = new CDDTarget;
}

CSkinDDListCtrl::~CSkinDDListCtrl()
{
    delete m_pcDropTarget;
}

BEGIN_MESSAGE_MAP(CSkinDDListCtrl, CSkinListCtrl)
	//{{AFX_MSG_MAP(CSkinDDListCtrl)
	ON_NOTIFY_REFLECT(LVN_BEGINDRAG, OnBegindrag)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkinDDListCtrl message handlers

/*====================================================================
函数名	：    PreSubclassWindow
功能		：预处理，注册及设置接收消息窗口。
算法实现	：（可选项）
引用全局变量：无
输入参数说明：
返回值说明：  无
----------------------------------------------------------------------
修改记录:
日  期		版本		修改人		走读人    修改内容
2004/07/16	1.0			李洪强                  创建
2004/07/20	1.0			朱允荣                  注释
====================================================================*/
void CSkinDDListCtrl::PreSubclassWindow() 
{
    CSkinListCtrl::PreSubclassWindow();
    m_pcDropTarget->Register(this);
    SetReceiveMsgWnd();
}

/*====================================================================
函数名	：    DefWindowProc
功能		：处理消息，增加处理自定义的拖拉消息。
算法实现	：（可选项）
引用全局变量：无
输入参数说明：
返回值说明：  无
----------------------------------------------------------------------
修改记录:
日  期		版本		修改人		走读人    修改内容
2004/07/16	1.0			李洪强                  创建
2004/07/20	1.0			朱允荣                  注释
====================================================================*/
LRESULT CSkinDDListCtrl::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
    if (CDragDropMsg::HasSetMsgID()) 
    {
        UINT nMsgId = message - CDragDropMsg::GetStartMsgID();
        switch(nMsgId) 
        {
        case MSG_DRAGOVER:
            {
                OnDropOver(wParam, lParam);
            }
            break;
        case MSG_DROP:
            {
                OnDrop(wParam, lParam);
            }
            break;
        case MSG_DROPEX:
            {
                OnDropEx(wParam, lParam);
            }
            break;
        default:
            break;
        }
    }
	
	return CSkinListCtrl::DefWindowProc(message, wParam, lParam);
}

void CSkinDDListCtrl::OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    if(pNMListView)
	{
        //设置拖拉数据
        CString strData;
        strData.Format(_T("%d"), pNMListView->iItem);
        HGLOBAL hData = GlobalAlloc(GHND | GMEM_SHARE, strData.GetLength() + 1);
        char *pbyData = (char *)GlobalLock(hData);
        memcpy(pbyData, (LPCTSTR)strData, strData.GetLength());
        pbyData[strData.GetLength()] = 0;
        GlobalUnlock(hData);

        
        COleDataSource cDataSrc;
        cDataSrc.CacheGlobalData(CF_TEXT, hData);
        DROPEFFECT ret = cDataSrc.DoDragDrop(DROPEFFECT_COPY);
        GlobalFree(hData);
        ::PostMessage(m_hRevMsgWnd, 
            CDragDropMsg::GetDDMsgID(MSG_BEGINDRAG), (WPARAM)m_hWnd, pNMListView->iItem);
    }
	
	*pResult = 0;
}

BOOL CSkinDDListCtrl::OnDrop(WPARAM pDropInfo, LPARAM lParam)
{
    CDropInfo *pInfo = (CDropInfo *)pDropInfo;
	ASSERT(pInfo->IsKindOf(RUNTIME_CLASS(CDropInfo)));

	//模拟会场
	if(pInfo->m_pDataObject->IsDataAvailable(CF_TEXT))
	{
		//得到拖拉数据
		HGLOBAL hMem = pInfo->m_pDataObject->GetGlobalData(CF_TEXT);
        char *pMem = (char *)GlobalLock(hMem);

        if(pMem == NULL)
		{
			GlobalUnlock(hMem);
			return FALSE;
		}

		int nDragItem = (DWORD)atoi(pMem);
		UINT uFlags = 0;
		int nDropItem = HitTest(pInfo->m_point, &uFlags);
        GlobalUnlock(hMem);
        UINT dwItem = MAKELONG(nDragItem, nDropItem);
        ::PostMessage(m_hRevMsgWnd, 
            CDragDropMsg::GetDDMsgID(MSG_DROP), (WPARAM)m_hWnd, dwItem);
    }
	return FALSE;
}

DROPEFFECT CSkinDDListCtrl::OnDropOver(WPARAM pDropInfo, LPARAM lParam)
{
    CDropInfo *pInfo = (CDropInfo *)pDropInfo;
	ASSERT(pInfo->IsKindOf(RUNTIME_CLASS(CDropInfo)));
	
	if(pInfo->m_pDataObject->IsDataAvailable(CF_TEXT))
	{
		return DROPEFFECT_COPY;
	}
	else
	{
		return DROPEFFECT_NONE;
	}
}

DROPEFFECT CSkinDDListCtrl::OnDropEx(WPARAM pDropInfo, LPARAM lParam)
{
	return (DROPEFFECT)-1;
}

/*====================================================================
函数名	：    SetReceiveMsgWnd
功能		：设置接收消息窗口。
算法实现	：（可选项）
引用全局变量：无
输入参数说明：
返回值说明：  无
----------------------------------------------------------------------
修改记录:
日  期		版本		修改人		走读人    修改内容
2004/07/16	1.0			李洪强                  创建
2004/07/20	1.0			朱允荣                  注释
====================================================================*/
void CSkinDDListCtrl::SetReceiveMsgWnd(HWND hRevMsgWnd)
{
    if (hRevMsgWnd == NULL) 
    {
        m_hRevMsgWnd = GetParent()->GetSafeHwnd();
    }
    else
    {
        m_hRevMsgWnd = hRevMsgWnd;
    }
}

//////////////////////////////////////////////////////////////////////////
//拖拉消息类                                                            //
//////////////////////////////////////////////////////////////////////////

UINT CDragDropMsg::m_nStartMsgID = 0;

//设置消息的基点。
void CDragDropMsg::SetStartMsgID(UINT nStartMsgID)
{
    m_nStartMsgID = nStartMsgID;
}

//得到消息的基点。
UINT CDragDropMsg::GetStartMsgID()
{
    return m_nStartMsgID;
}

//是否设置了消息
BOOL CDragDropMsg::HasSetMsgID()
{
    return m_nStartMsgID != 0;
}

//根据偏移计算实际的消息ID
UINT CDragDropMsg::GetDDMsgID(UINT nMsgType)
{
    return m_nStartMsgID + nMsgType;
}


//////////////////////////////////////////////////////////////////////////
//
//    CDropInfo  用于传递拖拉信息的类
//////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC( CDropInfo, CObject );

CDropInfo::CDropInfo()
{
	m_pDataObject = NULL;
	m_dwKeyState = 0;
	m_dropEffect = (DROPEFFECT)-1;
	m_dropEffectList = DROPEFFECT_NONE;
}

CDropInfo::CDropInfo(COleDataObject* pDataObject,DWORD dwKeyState,
				DROPEFFECT dropEffect,DROPEFFECT dropEffectList,CPoint point )
{
	m_pDataObject = pDataObject;
	m_dwKeyState = dwKeyState;
	m_dropEffect = dropEffect;
	m_dropEffectList = dropEffectList;
	m_point = point;
}

CDropInfo::~CDropInfo()
{
	m_pDataObject = NULL;
}

//////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
// CDDTarget 继承拖拉目标的类
//////////////////////////////////////////////////////////////////////////


CDDTarget::CDDTarget()
{

}

CDDTarget::~CDDTarget()
{
    Revoke();
}

//////////////////////////////////////////////////////////////////////
DROPEFFECT CDDTarget::OnDragEnter(CWnd* pWnd, COleDataObject* pDataObject,
			DWORD dwKeyState, CPoint point)
{
	ASSERT_VALID(this);
	ASSERT(::IsWindow(pWnd->m_hWnd));

	if (pWnd->IsKindOf(RUNTIME_CLASS(CView)))
		return COleDropTarget::OnDragEnter(pWnd,pDataObject, dwKeyState, point);

	CDropInfo DropInfo( pDataObject, dwKeyState, 0, 0, point );
	 ::SendMessage( pWnd->GetSafeHwnd(), CDragDropMsg::GetDDMsgID(MSG_DRAGENTER), (WPARAM)&DropInfo, 0 );
    return DROPEFFECT_COPY;
}

DROPEFFECT CDDTarget::OnDragOver(CWnd* pWnd, COleDataObject* pDataObject,
			DWORD dwKeyState, CPoint point)
{
	ASSERT_VALID(this);
	ASSERT(::IsWindow(pWnd->m_hWnd));

	if (pWnd->IsKindOf(RUNTIME_CLASS(CView)))//if CView,Call base class
		return COleDropTarget::OnDragOver(pWnd,pDataObject, dwKeyState, point);
	
	CDropInfo DropInfo(pDataObject, dwKeyState, 0, 0, point);
    ::SendMessage(pWnd->GetSafeHwnd(), CDragDropMsg::GetDDMsgID(MSG_DRAGOVER), (WPARAM)&DropInfo, 0);
    return DROPEFFECT_COPY;
}

BOOL CDDTarget::OnDrop(CWnd* pWnd, COleDataObject* pDataObject,
        DROPEFFECT dropEffect, CPoint point)
{
	ASSERT_VALID(this);
	ASSERT(::IsWindow(pWnd->m_hWnd));

	if (pWnd->IsKindOf(RUNTIME_CLASS(CView)))//if CView,Call base class
		return COleDropTarget::OnDrop(pWnd, pDataObject,dropEffect,point);

	CDropInfo DropInfo(pDataObject, 0, dropEffect, 0, point);
    ::SendMessage(pWnd->GetSafeHwnd(), CDragDropMsg::GetDDMsgID(MSG_DROP), (WPARAM)&DropInfo, 0);

    return TRUE;
}

DROPEFFECT CDDTarget::OnDropEx(CWnd* pWnd, COleDataObject* pDataObject,
			DROPEFFECT dropEffect, DROPEFFECT dropEffectList, CPoint point)
{
	ASSERT_VALID(this);
	ASSERT(::IsWindow(pWnd->m_hWnd));

	if (pWnd->IsKindOf(RUNTIME_CLASS(CView)))//if CView,Call base class
		return COleDropTarget::OnDropEx( pWnd, pDataObject, dropEffect, dropEffectList, point) ;

	CDropInfo DropInfo(pDataObject, 0, dropEffect, dropEffectList, point);
    ::SendMessage(pWnd->GetSafeHwnd(), CDragDropMsg::GetDDMsgID(MSG_DROPEX), (WPARAM)&DropInfo, 0);
    return (DROPEFFECT)-1;
}

void CDDTarget::OnDragLeave(CWnd* pWnd)
{
	ASSERT_VALID(this);
	ASSERT(::IsWindow(pWnd->m_hWnd));

	if (pWnd->IsKindOf(RUNTIME_CLASS(CView)))//if CView,Call base class
	{
		COleDropTarget::OnDragLeave(pWnd);
		return;
	}

    ::SendMessage(pWnd->GetSafeHwnd(), CDragDropMsg::GetDDMsgID(MSG_DRAGLEAVE), 0, 0);
	return;
}


BOOL CDDTarget::MyRegist(CWnd *pWnd)
{
	ASSERT_VALID(this);
	ASSERT(m_hWnd == NULL);     // registering drop target twice?
	ASSERT_VALID(pWnd);

	LPUNKNOWN lpUnknown = (LPUNKNOWN)GetInterface(&IID_IUnknown);
	ASSERT(lpUnknown != NULL);

	// the object must be locked externally to keep LRPC connections alive
    
    HRESULT re = CoLockObjectExternal(lpUnknown, TRUE, FALSE);
	if (re != S_OK)
		return FALSE;

	// connect the HWND to the IDropTarget implementation
	if (RegisterDragDrop(pWnd->m_hWnd,
		(LPDROPTARGET)GetInterface(&IID_IDropTarget)) != S_OK)
	{
		CoLockObjectExternal(lpUnknown, FALSE, FALSE);
		return FALSE;
	}

	// connect internal data
	m_hWnd = pWnd->m_hWnd;


	return TRUE;

}
