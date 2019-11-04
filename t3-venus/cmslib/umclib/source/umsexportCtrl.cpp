// umsexportCtrl.cpp: implementation of the CUmsExportCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "umssysinfoCtrl.h"
#include "umsexportCtrl.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUmsExportCtrl::CUmsExportCtrl( CUmsSession &cUmsSession)
          :CUmsExportCtrlIF(),
		  m_pUmsSession(NULL)                                       
{
   m_pUmsSession = &cUmsSession;
   BuildEventsMap();
} 

CUmsExportCtrl::~CUmsExportCtrl()
{

}

void  CUmsExportCtrl::BuildEventsMap()
{  
   REG_PFUN(ev_downloadConftemp_rsq,OnExportInfoRsp);
   REG_PFUN(ev_uploadConftemp_rsq,OnImportInfoRsp);
   REG_PFUN(ev_licenseOutput_Ind,OnExportAuthRsp);


   //断链清空资源
   REG_PFUN(OSP_DISCONNECT, OnLinkBreak); 
}

void  CUmsExportCtrl::OnLinkBreak(const CMessage& cMsg)
{
    PrtMsg( OSP_DISCONNECT,emEventTypeUmsRecv,"清空ums导入导出信息"); 
}

void CUmsExportCtrl::DispEvent(const CMessage &cMsg)
{
	DISP_FUN(CUmsExportCtrl,cMsg);
}

void CUmsExportCtrl::OnTimeOut(u16 wEvent)
{
    // 发送超时事件通知
   PostEvent(UI_UMS_CMD_TIMEOUT, wEvent);
} 
 
u16  CUmsExportCtrl::ExportInfoReq()  
{
	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}
    
	CTpMsg *pkdvMsg = m_pUmsSession->GetKdvMsgPtr();
    pkdvMsg->SetEvent(ev_downloadConftemp_req);
    u16 wRe = m_pUmsSession->PostMsg( TYPE_TPMSG );
	PrtMsg(ev_downloadConftemp_req,emEventTypeUmsSend,"发送会议模板导出请求");	 
	
    return NO_ERROR;
}

u16  CUmsExportCtrl::ImportInfoReq(const s8* strFileName)  
{
	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}
    
	CTpMsg *pkdvMsg = m_pUmsSession->GetKdvMsgPtr();
    pkdvMsg->SetEvent(ev_uploadConftemp_req);
	pkdvMsg->SetBody( strFileName,strlen(strFileName) );
    u16 wRe = m_pUmsSession->PostMsg( TYPE_TPMSG );
	PrtMsg(ev_uploadConftemp_req,emEventTypeUmsSend,"发送会议模板导入请求 FileName=%s",strFileName);	 
	
    return NO_ERROR;
}

u16  CUmsExportCtrl::ExportAuthReq()
{
	if ( NULL == m_pUmsSession ) 
	{
		return ERR_CMS;
	}
    
	CTpMsg *pkdvMsg = m_pUmsSession->GetKdvMsgPtr();
    pkdvMsg->SetEvent(ev_licenseOutput_req);
    u16 wRe = m_pUmsSession->PostMsg( TYPE_TPMSG );
	PrtMsg( ev_licenseOutput_req,emEventTypeUmsSend, "发送授权导出请求" );	 
	
    return NO_ERROR;
}

void  CUmsExportCtrl::OnImportInfoRsp(const CMessage& cMsg)   //目前不涉及导入会议模板的失败情况  作为预留
{    
}

void  CUmsExportCtrl::OnExportAuthRsp(const CMessage& cMsg)
{
	CTpMsg kdvMsg( &cMsg );
	BOOL32 bRet = *reinterpret_cast<BOOL32*>( kdvMsg.GetBody() );
	s8 strPath[255] = {0};
	s8* pStrPath = reinterpret_cast<s8*>( kdvMsg.GetBody() + sizeof(BOOL32) );

	if ( pStrPath )
	{
		strncpy( strPath, pStrPath, 255 );
	}		 
	
	PrtMsg( ev_licenseOutput_Ind, emEventTypeUmstoolRecv, _T("bRet:%d, strPath:%s"), bRet, strPath );
	PostEvent( UI_UMSTOOL_EXPAUTH_RSP, (WPARAM)bRet, (LPARAM)strPath );
}

void  CUmsExportCtrl::OnExportInfoRsp(const CMessage& cMsg)    
{   
	PrtMsg( ev_downloadConftemp_rsq, emEventTypeUmstoolRecv, "get conf template export rsp" );
	
	PostEvent(UI_UMSTOOL_EXPTEMPLATE_RSP);	
}


