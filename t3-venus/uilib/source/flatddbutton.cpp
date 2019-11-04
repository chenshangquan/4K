/********************************************************************
	模块名:      UILib
	文件名:      FlatDDButton.cpp
	相关文件:    UILibHead.h
	文件实现功能 按钮接收拖拉
    作者：       朱允荣
	版本：       1.0
---------------------------------------------------------------------------------------------------------------------
	修改记录:
	日  期		版本		修改人		走读人    修改内容
	7/20/2004	1.0         朱允荣               ------------

*********************************************************************/

#include "stdafx.h"
#include "UIlibHead.h"

//lint -e1060   屏蔽pclint错误

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFlatDDButton::CFlatDDButton()
{
    m_pcDropTarget = new CDDTarget;
}

CFlatDDButton::~CFlatDDButton()
{
    delete m_pcDropTarget;
}

BEGIN_MESSAGE_MAP(CFlatDDButton, CFlatButton)
	//{{AFX_MSG_MAP(CFlatDDButton)
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
2004/07/20	1.0			朱允荣                  创建
====================================================================*/
void CFlatDDButton::PreSubclassWindow() 
{
    CFlatButton::PreSubclassWindow();
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
2004/07/20	1.0			朱允荣                  创建
====================================================================*/
LRESULT CFlatDDButton::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
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
	
	return CFlatButton::DefWindowProc(message, wParam, lParam);
}



/*====================================================================
函数名	：    OnDrop
功能		：收到拖拉消息处理。得到信息，并转发给设定的窗口。
算法实现	：（可选项）
引用全局变量：无
输入参数说明：
返回值说明：  无
----------------------------------------------------------------------
修改记录:
日  期		版本		修改人		走读人    修改内容
2004/07/20	1.0			朱允荣                  创建
====================================================================*/
BOOL CFlatDDButton::OnDrop(WPARAM pDropInfo, LPARAM lParam)
{
    CDropInfo *pInfo = (CDropInfo *)pDropInfo;
	ASSERT(pInfo->IsKindOf(RUNTIME_CLASS(CDropInfo)));

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
        GlobalUnlock(hMem);
        ::PostMessage(m_hRevMsgWnd, 
            CDragDropMsg::GetDDMsgID(MSG_DROP), (WPARAM)m_hWnd, nDragItem);
    }
	return FALSE;
}

DROPEFFECT CFlatDDButton::OnDropOver(WPARAM pDropInfo, LPARAM lParam)
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

DROPEFFECT CFlatDDButton::OnDropEx(WPARAM pDropInfo, LPARAM lParam)
{
	return (DROPEFFECT)-1;
}

/*====================================================================
函数名	：    Register
功能		：注册窗口。
算法实现	：（可选项）
引用全局变量：无
输入参数说明：
返回值说明：  无
----------------------------------------------------------------------
修改记录:
日  期		版本		修改人		走读人    修改内容
2004/07/20	1.0			朱允荣                  创建
====================================================================*/
void CFlatDDButton::Register()
{
    m_pcDropTarget->Register(this);
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
2004/07/20	1.0			朱允荣                  创建
====================================================================*/
void CFlatDDButton::SetReceiveMsgWnd(HWND hRevMsgWnd)
{
    if (hRevMsgWnd == NULL) 
    {
        m_hRevMsgWnd = GetParent()->GetSafeHwnd();
    }
}