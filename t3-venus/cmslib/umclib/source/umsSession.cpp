// umsSession.cpp: implementation of the CUmsSession class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "umsSession.h"

#include "confTemplateCtrl.h"
#include "confCtrl.h"
#include "tvwCtrl.h"
#include "userCtrl.h"
#include "umsConfigCtrl.h"
#include "umswebaddrbook.h"

#include "umsexportCtrl.h"
#include "umssysinfoCtrl.h"
#include "umstvwboardCtrl.h"
#include "umsboardCtrl.h"
#include "umsNetMngCtrl.h"
#include "umsVTRCtrl.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUmsSession::CUmsSession( u16 wAppID, BOOL bUseAddr ) 
            :m_bSelfInitOsp(FALSE),
			m_bLogin(FALSE),
			m_dwLocalIP(0),
	        m_dwUmsIp(0),
			m_pConfTemplate(NULL),
            m_pConf(NULL),
            m_pTvw(NULL),
			m_pUser(NULL),
			m_pConfig(NULL),
			m_pAddr(NULL),
			m_pUmsSysInfo(NULL),
			m_pUmsExport(NULL),
			m_pUmsTvwBoard(NULL),
			m_pUmsSingleBoard(NULL),
			m_pUmsNetMng(NULL),
			m_pUmsVTR(NULL),
			m_cUser()
{

	m_bUseAdddr = bUseAddr;

	u16 wRet = InitializeLib(wAppID);

	ASSERT(wRet == NO_ERROR);
	RegHandler(this);
	//在该类中，new出所有的功能类，外部通过接口GetInterface()获取
#define NEW_REG(pCtrlIF, clsName)         \
	pCtrlIF = new clsName(*this);     \
    RegHandler(pCtrlIF);

 	NEW_REG(m_pConfTemplate,CConfTemplateCtrl);
 	NEW_REG(m_pConf,CConfCtrl);
  	NEW_REG(m_pTvw,CTvwCtrl);
  	NEW_REG(m_pUser,CUserCtrl); 
    NEW_REG(m_pConfig,CUmsConfigCtrl);
	//NEW_REG(m_pAddr,CCncAddrbook);
	if ( bUseAddr )
	{
		m_pAddr = new CCncAddrbook( *this );
	}

	//umstool网呈维护工具新加接口
  	NEW_REG(m_pUmsSysInfo,CUmsSysInfoCtrl); 
	NEW_REG(m_pUmsExport,CUmsExportCtrl); 
	NEW_REG(m_pUmsTvwBoard,CUmsTvwBoardCtrl); 
	NEW_REG(m_pUmsSingleBoard,CUmsBoardCtrl); 
	NEW_REG(m_pUmsNetMng,CUmsNetMngCtrl); 
	NEW_REG(m_pUmsVTR,CUmsVTRCtrl); 
	
#undef NEW_REG
   g_UmcLibApp.SetNotifyWindow(GetOspRecvWindow());
}

CUmsSession::~CUmsSession()
{

//如果未断开连接，则需要先断开
   if ( IsConnectedUms() )
   {  
	   u32 dwNodeID = g_UmcLibApp.GetNodeId() ;
	   OspDisconnectTcpNode( dwNodeID );
	  
	   /* 已没有机会收到OSP断链通知了
	   所以伪造一个,以触发断链动作*/
	   u32 dwNode = g_UmcLibApp.GetNodeId();
	   CMessage msg;
	   msg.event = OSP_DISCONNECT;
	   msg.length = sizeof(u32);
	   msg.content = (u8*)&dwNode;
       OnLinkBreak(msg);
   }

   //如果osp是本session 初始化的，则在此反初始化
   //	if( m_bSelfInitOsp )
   {
	   OspQuit();
   }
   
   UnregHandler(this);

//释放空间
#define DEL_UNREG(pCtrlIF, clsName)               \
	if(NULL != pCtrlIF)                       \
	delete dynamic_cast<clsName*>(pCtrlIF);    \
	pCtrlIF = NULL;

    DEL_UNREG(m_pConfTemplate,CConfTemplateCtrl);
    DEL_UNREG(m_pConf,CConfCtrl);
    DEL_UNREG(m_pTvw,CTvwCtrl);
    DEL_UNREG(m_pUser,CUserCtrl);
    DEL_UNREG(m_pConfig,CUmsConfigCtrl); 
	DEL_UNREG(m_pAddr,CCncAddrbook);
 
  	DEL_UNREG(m_pUmsSysInfo,CUmsSysInfoCtrl); 
	DEL_UNREG(m_pUmsExport,CUmsExportCtrl); 
	DEL_UNREG(m_pUmsTvwBoard,CUmsTvwBoardCtrl); 
	DEL_UNREG(m_pUmsSingleBoard,CUmsBoardCtrl); 
	DEL_UNREG(m_pUmsNetMng,CUmsNetMngCtrl);
	DEL_UNREG(m_pUmsVTR,CUmsVTRCtrl);

#undef DEL_UNREG
   
   
	// 置OSP通知目的窗口为空
    g_UmcLibApp.SetNotifyWindow(NULL);
    g_UmcLibApp.SetNodeId(INVALID_NODE);
    g_UmcLibApp.ClearOspMsg();

//	g_UmcLibApp.QuitApp();
	m_hWnd = NULL;
	 
}

void CUmsSession::BuildEventsMap() 
{
	//eg： REG_PFUN(ev_XXX, OnXXX);
	//REG_PFUN():在70/common/CDispEvent.h中实现，第一个参数为要处理的消息号，第二个参数为ex_XXX对应的处理函数
	//其中，OnXXX在对应类中实现
	REG_PFUN(OSP_DISCONNECT, OnLinkBreak);
	REG_PFUN(ev_UMSLoginRet,OnConnectRsp);
    REG_PFUN(ev_UmsLoginByOther_Notify, OnGrabLoginNotify);
	REG_PFUN(evtp_UmsCommonReasonToUI_Ind, OnUmsCommonReasonInd);
}


u16 CUmsSession::GetCtrlInterface(CConfTemplateCtrlIF **ppCtrl) const
{   
    if ( NULL == m_pConfTemplate) 
	{   
		*ppCtrl = NULL;
		return ERR_CMS;
    }

	*ppCtrl = m_pConfTemplate;
    
	return NO_ERROR;

}
u16 CUmsSession::GetCtrlInterface(CConfCtrlIF **ppCtrl) const
{ 
    if ( NULL == m_pConf) 
	{   
		*ppCtrl = NULL;
		return ERR_CMS;
    }
	
	*ppCtrl = m_pConf;
    
	return NO_ERROR;

}
u16 CUmsSession::GetCtrlInterface(CTvwCtrlIF **ppCtrl) const
{ 
	if ( NULL == m_pTvw) 
	{   
		*ppCtrl = NULL;
		return ERR_CMS;
    }
	
	*ppCtrl = m_pTvw;
    
	return NO_ERROR;

}
u16 CUmsSession::GetCtrlInterface(CUserCtrlIF **ppCtrl) const
{ 
	if ( NULL == m_pUser) 
	{   
		*ppCtrl = NULL;
		return ERR_CMS;
    }
	
	*ppCtrl = m_pUser;
    
	return NO_ERROR;

}

u16 CUmsSession::GetCtrlInterface(CUmsConfigCtrlIF **ppCtrl) const
{  
	if ( NULL == m_pConfig) 
	{   
		*ppCtrl = NULL;
		return ERR_CMS;
    }
	
	*ppCtrl = m_pConfig;
    
	return NO_ERROR;
}

u16 CUmsSession::GetCtrlInterface(CCncAddrbookIF **ppCtrl) const
{  
	if ( NULL == m_pAddr) 
	{   
		*ppCtrl = NULL;
		return ERR_CMS;
    }
	
	*ppCtrl = m_pAddr;
    
	return NO_ERROR;
}

u16 CUmsSession::GetCtrlInterface(CUmsSysInfoCtrlIF **ppCtrl) const
{  
	if ( NULL == m_pUmsSysInfo) 
	{   
		*ppCtrl = NULL;
		return ERR_CMS;
    }
	
	*ppCtrl = m_pUmsSysInfo;
    
	return NO_ERROR;
}

u16 CUmsSession::GetCtrlInterface(CUmsExportCtrlIF **ppCtrl) const
{  
	if ( NULL == m_pUmsExport) 
	{   
		*ppCtrl = NULL;
		return ERR_CMS;
    }
	
	*ppCtrl = m_pUmsExport;
    
	return NO_ERROR;
}

u16 CUmsSession::GetCtrlInterface(CUmsTvwBoardCtrlIF **ppCtrl) const
{  
	if ( NULL == m_pUmsTvwBoard) 
	{   
		*ppCtrl = NULL;
		return ERR_CMS;
    }
	
	*ppCtrl = m_pUmsTvwBoard;
    
	return NO_ERROR;
}

u16 CUmsSession::GetCtrlInterface(CUmsBoardCtrlIF **ppCtrl) const
{  
	if ( NULL == m_pUmsSingleBoard) 
	{   
		*ppCtrl = NULL;
		return ERR_CMS;
    }
	
	*ppCtrl = m_pUmsSingleBoard;
    
	return NO_ERROR;
}

u16 CUmsSession::GetCtrlInterface(CUmsNetMngCtrlIF **ppCtrl) const
{  
	if ( NULL == m_pUmsNetMng) 
	{   
		*ppCtrl = NULL;
		return ERR_CMS;
    }
	
	*ppCtrl = m_pUmsNetMng;
    
	return NO_ERROR;
}

u16 CUmsSession::GetCtrlInterface(CUmsVTRCtrlIF **ppCtrl) const
{  
	if ( NULL == m_pUmsVTR) 
	{   
		*ppCtrl = NULL;
		return ERR_CMS;
    }
	
	*ppCtrl = m_pUmsVTR;
    
	return NO_ERROR;
}
 
void CUmsSession::OnLinkBreak(const CMessage& cMsg)
{
    // OSP断链通知
    u32 u32NodeId = *(u32*)(cMsg.content);
    PrtMsg(OSP_DISCONNECT,emEventTypeUmsRecv,"Link Break (NodeID: %d)",u32NodeId);

    ClearWaiting();	// OSP断链后,尚未执行完的命令中断执行 
	ClearAllCommand(); // 清空所有在队列中等待执行的命令
    
   
    g_UmcLibApp.SetNodeId(INVALID_NODE);
	m_dwUmsIp = 0;
    m_bLogin = FALSE;

	if ( m_pAddr ) 
    {
		dynamic_cast<CCncAddrbook*>(m_pAddr)->OnLinkBreak();
    }

	//向界面发通知
    PostEvent(UI_UMS_DISCONNECTED);	
}


//相同账号的人抢占登录
void CUmsSession::OnGrabLoginNotify(const CMessage& cMsg)
{ 
   CTpMsg kdvMsg(&cMsg);
   u32 dwIP = *reinterpret_cast< u32*>(kdvMsg.GetBody());
   in_addr tAddr;
   tAddr.S_un.S_addr = ntohl(dwIP) ;   
   PrtMsg(ev_UmsLoginByOther_Notify,emEventTypeUmsRecv,"抢登通知(抢占方 IP:  %s ；dwIP=%d )", inet_ntoa(tAddr), dwIP );

   PostEvent(UI_UMS_GRAB_LOGIN_NOTIFY,(WPARAM)ntohl(dwIP));

}

//UMS的错误信息通知
void CUmsSession::OnUmsCommonReasonInd(const CMessage& cMsg)
{ 
	CTpMsg kdvMsg(&cMsg);
	TTPUmsReasonInd tReason = *reinterpret_cast<TTPUmsReasonInd*>(kdvMsg.GetBody());

	PrtMsg( evtp_UmsCommonReasonToUI_Ind, emEventTypeUmsRecv, "ReasonId: %d", tReason.m_dwReason );
	
	PostEvent( UI_UMS_UMSREASON_IND, (WPARAM)&tReason, 0 );
}

/*
tp_LoginUms_sucess,
	tp_LoginUms_NameError,	//用户名错误
	tp_LoginUms_PwdError,	//密码错误
    tp_LoginUms_MaxLogin,	//达到用户登录上限
	tp_LoginUms_Logged,		//用户已经登录
*/
void  CUmsSession::OnConnectRsp( const CMessage& cMsg )
{  
	CTpMsg kdvMsg( &cMsg ); 
   TLoginRet tLogRe = *reinterpret_cast<TLoginRet *>(kdvMsg.GetBody() );
   
   PrtMsg(ev_UMSLoginRet,emEventTypeUmsRecv,"m_dwUserID=%d,errorCode: %d ( %d:sucess, %d:NameError, %d:PwdError, %d: MaxLogin, %d: Logged )",
	      tLogRe.m_dwUserID,tLogRe.m_emRet,tp_LoginUms_sucess,tp_LoginUms_NameError,tp_LoginUms_PwdError,tp_LoginUms_MaxLogin,tp_LoginUms_Logged);

   u32 dwErrCode = NO_ERROR;
   switch( tLogRe.m_emRet )
   {
   case tp_LoginUms_sucess:
	    m_bLogin = TRUE;
		break;
   case tp_LoginUms_NameError:	//用户名 错误
       m_bLogin = FALSE;
       dwErrCode = ERR_UMC_LOGIN_UMS_USER_ERR;
        break;
   case tp_LoginUms_PwdError:	// 密码错误
	    m_bLogin = FALSE;
        dwErrCode = ERR_UMC_LOGIN_UMS_PSWD_ERR;
        break;
   case tp_LoginUms_MaxLogin:	//达到用户登录上限
	    m_bLogin = FALSE;
        dwErrCode = ERR_UMC_LOGIN_UMS_MAX_LOGIN;
        break;
   case	tp_LoginUms_Logged:		//用户已经登录
	    m_bLogin = FALSE;
        dwErrCode = ERR_UMC_LOGIN_UMS_LOGED;
   case tp_LoginUms_SysIniting:  //系统正在初始化
        m_bLogin = FALSE;
        dwErrCode = ERR_UMC_LOGIN_UMS_SYSINITING;
		break;
   } 

    if( m_bLogin )
	{   
		SetSndInstID(cMsg.srcid);
		// 初始化工作
		if ( m_bUseAdddr && m_pAddr != NULL )
		{
			dynamic_cast<CCncAddrbook*>(m_pAddr)->RegAddrBook();
		}		
	}
 	else
 	{
		DisconnectUms();
		g_UmcLibApp.SetNodeId( INVALID_NODE );
		
 	}


	PostEvent(UI_UMS_CONNECTED,m_bLogin,dwErrCode );
   
} 




u16 CUmsSession::PostMsg( u32 dwType /* = TYPE_CMESSAGE  */)
{
	//编写post消息前需要满足的条件 
	return CMsgDriver::PostMsg( dwType );
}


BOOL CUmsSession::IsInitFinish()
{
	return IsOspInitd();
}


BOOL CUmsSession::IsConnectedUms()
{   
	//return m_bLogin;
	return g_UmcLibApp.GetNodeId() != INVALID_NODE;
} 


BOOL CUmsSession::IsManagerUser()
{  
	s8 *pName = m_cUser.GetName();
	if ( strcmp(pName,MANAGER_USER) == 0 ) 
	{
		return TRUE;
	}

	return FALSE;
}

 
u16 CUmsSession::InitializeLib( u16 wAppID )
{
    // 初始化OSP
    const u32 dwTelnetPort = 0;
	u16 nRe = NO_ERROR;
    if(!IsOspInitd())
    {  
        BOOL bTelnet  = FALSE ;
        
#ifdef _DEBUG
        bTelnet = TRUE;
#endif

	 
        if(!OspInit( bTelnet , dwTelnetPort))
        {   
			m_bSelfInitOsp = TRUE; 
            return ERR_CMS_OSP_Init;
        }
       
    }
   
    // 构造事件映射表
    BuildEventsMap(); 

	char szOspApp[] = "UmcLib1.0";
	const u32 dwPrior = 80;
	int nRet = g_UmcLibApp.CreateApp(&szOspApp[0], wAppID, dwPrior, 300, 200);

	ASSERT(nRet == OSP_OK);

	if ( OSP_OK != nRet)
	{
		nRe = ERR_UMC_CREATE_OSP_FAIL;
	}
	else
	{
		SetAppID(wAppID);
		PrtMsg( "APP 启动成功\n" );
	}
    return nRe;
}

u16 CUmsSession::ConnectUms(u32 dwIP, u16 dwPort,  LPCTSTR pStrUserName,
	                        	 LPCTSTR pStrUserPswd, BOOL32 bConnect /*= TRUE*/) 
{   
	// 建立TCP连接
    if( IsConnectedUms() )
    {   
//         //如何已经登录了该IP，则直接返回，否则断开重连
//         if ( dwIP == m_dwUmsIp )
//         {
// 		    PrtMsg( "ERR_UMC_ACTIVE_CONNECTION  IP已连接\n" );
//             return ERR_UMC_ACTIVE_CONNECTION;
//         }
//         else
//         {
           DisconnectUms();
//		} 
        
    }
    
    ClearDisp();

    // 重构消息分发表
    BuildEventsMap();
    
    //建立Osp的TCP连接,得到本地机器的IP地址
	u32 dwUmsNodeId = 0; 
	dwUmsNodeId = OspConnectTcpNode(htonl(dwIP), static_cast<u16>(dwPort), 5
			, 3, 5000/*30000*/, &m_dwLocalIP);    
 
	m_dwUmsIp = dwIP;
	m_dwLocalIP = ntohl( m_dwLocalIP );
	
	if(dwUmsNodeId == INVALID_NODE)
	{
	   PrtMsg( "ERR_UMC_CREATE_TCP_FAIL 创建TCP失败，端口号：%d\n", dwUmsNodeId );
	   return ERR_UMC_CREATE_TCP_FAIL;
	}		
   
    g_UmcLibApp.SetNodeId( dwUmsNodeId );
	g_AddrBookApp.SetNodeId( dwUmsNodeId );
	
    //设置在node连接中断时需通知的appid和InstId
    ::OspNodeDiscCBReg(dwUmsNodeId, GetAppID(), 1); 
	

	//登录ums ，验证用户
	m_cUser.Empty();
    m_cUser.SetName((s8*)pStrUserName);
   m_cUser.SetPassword((s8*)pStrUserPswd);
// 	m_cUser.SetEncryptedPassword((s8*)pStrUserPswd);
    
	CMessage *pcMsg = GetCMsgPtr();
	pcMsg->event  =  ev_UMSLoginReq ;
    pcMsg->length = sizeof(CLoginRequest) ;
    pcMsg->content = (u8*)&m_cUser;

//  	u16 awEvent[1];
//     awEvent[0] = ev_UMSLoginRet;  
// 
//  	u16 wRet =  PostCommand(this,awEvent,1 );

	u16 awEvent[1];
    awEvent[0] = ev_UMSLoginRet;
	u16 wRet = PostCommand(this, awEvent, 1, TYPE_CMESSAGE, 3000);

	in_addr tAddr;
	tAddr.S_un.S_addr = ntohl(dwIP);
    PrtMsg(ev_UMSLoginReq,emEventTypeUmsSend,"ret = %d ip = %s userName=%s pswd=%s", wRet, inet_ntoa(tAddr), m_cUser.GetName(),m_cUser.GetPassword());

	return wRet;
}
 


u16 CUmsSession::DisconnectUms()
{
	if ( !IsConnectedUms() )
	{
		return NO_ERROR;
	}

	//注销
    if (m_pAddr && m_bUseAdddr) 
    {
		dynamic_cast<CCncAddrbook*>(m_pAddr)->UnRegAddrBook();
    }

	u32 dwNodeID = g_UmcLibApp.GetNodeId() ;
	BOOL32 re = OspDisconnectTcpNode( dwNodeID );

	//m_dwUmsIp = 0;

	return (u16)re;
}


u32 CUmsSession::GetUmsIP()
{
	return m_dwUmsIp;
}


u32 CUmsSession::GetLocalIP()
{
	return m_dwLocalIP;
}

const CLoginRequest& CUmsSession::GetConnectedUser()
{
	return m_cUser;
}

void CUmsSession::DispEvent(const CMessage &cMsg)
{
    DISP_FUN(CUmsSession, cMsg);
}

void CUmsSession::OnTimeOut(u16 wEvent)
{  
    //处理超时消息
    if(wEvent == ev_UMSLoginReq/*ev_UMSLoginRet*/)
    {
        // OSP通道建立成功,但ACK NACK都没有收到
        OspDisconnectTcpNode(g_UmcLibApp.GetNodeId());
        g_UmcLibApp.SetNodeId(INVALID_NODE);
        PostEvent(UI_UMS_LOGIN_TIMEOUT, wEvent);
        
    } 
    

    // 发送超时事件通知
    PostEvent(UI_UMS_CMD_TIMEOUT, wEvent);
}
