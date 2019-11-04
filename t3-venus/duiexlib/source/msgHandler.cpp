#include "StdAfx.h"
#include "msgHandler.h"

namespace DuiLib {
CMsgHandler::CMsgHandler( /*LPCTSTR  strDlgName */ ) 
{   
}


CMsgHandler::~CMsgHandler(void)
{
}

void CMsgHandler::InitWnd()
{

}

void CMsgHandler::Notify( TNotifyUI& msg )
{
	if ( msg.pSender == 0 || _tcsicmp( msg.sType, L"" ) == 0 )
	{
		 return;
	}

	if( msg.sType == DUI_MSGTYPE_WINDOWINIT ) 
	{
		InitWnd();
	}
	else
	{
		tString strItemName = _T("");
		if ( _tcsicmp(msg.pSender->GetClass(), _T("ListContainerElementUI")) == 0 )
		{
			CListContainerElementUI* pItemList = (CListContainerElementUI*)msg.pSender;
			if ( NULL != pItemList )
			{
				strItemName = pItemList->GetItemName();
			}
		}
		else
		{
			strItemName = msg.pSender->GetName();
		}

		const TCtrlMsg* pMap = GetCtrlMessageMap();
		if( NULL == pMap )
		{ 
			return;
		} 

		TCtrlMsg* pBegin = const_cast<TCtrlMsg*>(pMap);
		while ( NULL != pBegin && pBegin->pMsgHdlFun != 0 )
		{ 
			if (  _tcscmp(strItemName.c_str(),  pBegin->tcCtrlName ) == 0 
				&& _tcscmp( msg.sType, pBegin->tcCtrlMsgType) == 0 )
			{
				(this->*(pBegin->pMsgHdlFun))(msg);
				break;
			}
			pBegin++;
		} 
	}
}



void CMsgHandler::BusiMsgNotify( UINT uiMsgID, WPARAM wparam, LPARAM lparam )
{
	const TBusiMsg* pMap = GetBusiMessageMap();
	if( NULL == pMap )
	{ 
		return;
	} 
	

	TBusiMsg* pBegin = const_cast<TBusiMsg*>(pMap);
	while ( NULL != pBegin && pBegin->pMsgHdlFun != 0 )
	{ 
		if (  uiMsgID== pBegin->uiMsgID )
		{ 			
			(this->*(pBegin->pMsgHdlFun))( wparam,lparam );
			break;
			 
	    }
	    pBegin++;
	}
	
}

const TCtrlMsg* CMsgHandler::GetCtrlMessageMap() const
{
	return NULL;
}

const TBusiMsg* CMsgHandler::GetBusiMessageMap() const
{
	return NULL;
}
}