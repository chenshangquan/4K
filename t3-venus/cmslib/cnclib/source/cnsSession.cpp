// cnsSession.cpp: implementation of the CCnsSession class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cnsSession.h"
#include "cncmsgrecver.h"
#include "cmsConst.h"
#include "cncaddrbook.h"
#include "cncconfig.h"
#include "cncconfctrl.h"
#include "cncuserctrl.h"
#include "umcconfCtrl.h"
#include "cncsipinfoctrl.h"
#include "cncportdiagctrl.h"
#include "cncsysctrl.h"
#include "cnccenterctrl.h"
#include "cncnetmngctrl.h"
#include "eventoutcnsallmsg.h"
#include "tpadplatstuct.h"
#include "tpadplatconst.h"

u8 g_abyTemp[sizeof(CLoginRequest) + 1] = { 0 };

UINT g_wTimerID = 0;
void CALLBACK TimerProc(HWND hWnd,UINT nMsg,UINT nTimerid,DWORD dwTime);
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCnsSession* CCnsSession::s_pCnsSession = NULL;

CCnsSession::CCnsSession()
            :m_bInitOsp(FALSE)
{
	m_pAddrBookIF = NULL;
	m_pConfigIF = NULL;
	m_pConfCtrlIF = NULL;
    m_pUmcConfCtrlIF = NULL;
	m_pUserCtrlIF = NULL;
	m_pSipInfoCtrlIF = NULL;
	m_pPortDiagIF = NULL;
	m_pCenterCtrlIF = NULL;
	m_pNetMngCtrlIF = NULL;
	m_pSysCtrlIF = NULL;
	m_dwLocalIP = 0;
	m_dwCnsIp = 0;
	m_uInst = 0;
	m_bUseAdddr = TRUE;
	m_bLogin = FALSE;

	g_CncApp.SetNotifyWindow( GetOspRecvWindow() );

    s_pCnsSession = this;
    
	RegHandler(this);
//在该类中，new出所有的功能类，外部通过接口GetInterface()获取
#define NEW_REG(pCtrlIF, clsName)         \
		pCtrlIF = new clsName(*this);     \
		RegHandler(pCtrlIF);

	//NEW_REG( m_pAddrBookIF, CCncAddrbook );
	NEW_REG( m_pConfigIF, CCncConfig );
	NEW_REG( m_pConfCtrlIF, CCncConfCtrl );
    NEW_REG( m_pUmcConfCtrlIF, CUmcConfCtrl );
	NEW_REG( m_pUserCtrlIF, CCncUserCtrl );
	NEW_REG( m_pSipInfoCtrlIF, CCncSipInfoCtrl );
	NEW_REG( m_pPortDiagIF, CCncPortDiagCtrl );
	NEW_REG( m_pSysCtrlIF, CCncSysCtrl );
	NEW_REG( m_pCenterCtrlIF, CCncCenterCtrl );
	NEW_REG( m_pNetMngCtrlIF, CCncNetMngCtrl );
	//m_pAddrBookIF = new CCncAddrbook( *this );

#undef NEW_REG

}

void CCnsSession::InitEnv( u16 wAppID, u32 dwDesIID )
{
	SetAppID( wAppID );
    SetDesIID( dwDesIID );
	// 初始化Osp
    u16 wRet = InitializeOsp();
    ASSERT(wRet == NO_ERROR);

    if ( m_bUseAdddr && m_pAddrBookIF == NULL )
    {
        m_pAddrBookIF = new CCncAddrbook( *this );
    }
}

CCnsSession::~CCnsSession()
{
	//如果未断开连接，则需要先断开
	if( IsConnectedCns() )
    {
        DisconnectCns();
        /* 已没有机会收到OSP断链通知了
        所以伪造一个,以触发断链动作*/
        u32 dwNode = g_CncApp.GetNodeId();
        CMessage msg;
        msg.event = OSP_DISCONNECT;
        msg.length = sizeof(u32);
        msg.content = (u8*)&dwNode;
        OnLinkBreak(msg);
    }

    if (g_wTimerID != 0)
    {
        KillTimer( NULL, g_wTimerID );
        g_wTimerID = 0;
    }

	ClearDisp();
	UnregHandler(this);

    s_pCnsSession = NULL;

//释放空间
#define DEL_UNREG(pCtrlIF, clsName)           \
	UnregHandler(pCtrlIF);					  \
	if(NULL != pCtrlIF)                       \
	delete dynamic_cast<clsName*>(pCtrlIF);   \
	pCtrlIF = NULL;

	DEL_UNREG( m_pAddrBookIF, CCncAddrbook );
	DEL_UNREG( m_pConfigIF, CCncConfig );
	DEL_UNREG( m_pConfCtrlIF, CCncConfCtrl );
	DEL_UNREG( m_pUserCtrlIF, CCncUserCtrl );
	DEL_UNREG( m_pUmcConfCtrlIF, CUmcConfCtrl );
	DEL_UNREG( m_pSipInfoCtrlIF, CCncSipInfoCtrl );
	DEL_UNREG( m_pPortDiagIF, CCncPortDiagCtrl );
	DEL_UNREG( m_pSysCtrlIF, CCncSysCtrl );
	DEL_UNREG( m_pCenterCtrlIF, CCncCenterCtrl );
	DEL_UNREG( m_pNetMngCtrlIF, CCncNetMngCtrl );

#undef DEL_UNREG

	// 强制断开连接 清空静态变量
    if(IsConnectedCns())
    {
        DisconnectCns();
    }
	// 置OSP通知目的窗口为空
    g_CncApp.SetNotifyWindow(NULL);
    g_CncApp.SetNodeId(INVALID_NODE);
    g_CncApp.ClearOspMsg();
	// 如果OSP是自己初始化的，则需要退出OSP
    if(!m_bInitOsp)
    {
        OspQuit();
    }
}



u16 CCnsSession::PostMsg( u32 dwType /* = TYPE_CMESSAGE */)
{
	//判断当前是否满足向cns发送消息的条件，不满足的话就直接返回
	
	return CCncMsgDriver::PostMsg( dwType );
}

/*=============================================================================
  函 数 名： DispEvent
  功    能： 分发消息处理
  算法实现： 
  全局变量： 
  参    数： const CMessage &cMsg
  返 回 值： void 
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2011/04/28    1.0		    肖楚然                  创建
=============================================================================*/
void CCnsSession::DispEvent(const CMessage &cMsg)
{
    DISP_FUN(CCnsSession, cMsg);
}

/*=============================================================================
  函 数 名： OnTimeOut
  功    能： 超时消息处理
  算法实现： 
  全局变量： 
  参    数： u16 wEvent
  返 回 值： void 
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2011/04/28    1.0		    肖楚然                  创建
=============================================================================*/
void CCnsSession::OnTimeOut(u16 wEvent)
{ 
    //处理超时消息
    if(wEvent == ev_CnLogin_Req/*ev_CnLogin_Rsp*/)
    {
        // OSP通道建立成功,但ACK NACK都没有收到
        OspDisconnectTcpNode(g_CncApp.GetNodeId());
        g_CncApp.SetNodeId(INVALID_NODE);
        g_AddrBookApp.SetNodeId( INVALID_NODE );

        PostEvent(UI_CNS_LOGIN_TIMEOUT, wEvent);
    }

	// 发送超时事件通知
	//PostEvent(UI_UMS_CMD_TIMEOUT, wEvent);    
}

/*===========================================================================
  函 数 名： CncGetInterface
  功    能： 获取接口指针
  算法实现： 
  全局变量： 
  参    数： 
  返 回 值： 
 ----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2011/04/28    1.0		    肖楚然                  创建
===========================================================================*/
u16 CCnsSession::CncGetInterface(CCncAddrbookIF **ppCtrl)
{
    if( m_pAddrBookIF != NULL)
    {
        *ppCtrl = m_pAddrBookIF;
        return NO_ERROR;
    }
    else
    {
        *ppCtrl = NULL;
        return ERR_CNC;
    }
}

u16 CCnsSession::CncGetInterface(CCncConfigIF **ppCtrl)
{
    if( m_pConfigIF != NULL)
    {
        *ppCtrl = m_pConfigIF;
        return NO_ERROR;
    }
    else
    {
        *ppCtrl = NULL;
        return ERR_CNC;
    }
}

u16 CCnsSession::CncGetInterface(CCncConfCtrlIF **ppCtrl)
{
    if( m_pConfCtrlIF != NULL)
    {
        *ppCtrl = m_pConfCtrlIF;
        return NO_ERROR;
    }
    else
    {
        *ppCtrl = NULL;
        return ERR_CNC;
    }
}

u16 CCnsSession::CncGetInterface(CUmcConfCtrlIF **ppCtrl)
{
    if( m_pUmcConfCtrlIF != NULL)
    {
        *ppCtrl = m_pUmcConfCtrlIF;
        return NO_ERROR;
    }
    else
    {
        *ppCtrl = NULL;
        return ERR_CNC;
    }
}

u16 CCnsSession::CncGetInterface(CCncUserCtrlIF **ppCtrl)
{
	if( m_pUserCtrlIF != NULL)
    {
        *ppCtrl = m_pUserCtrlIF;
        return NO_ERROR;
    }
    else
    {
        *ppCtrl = NULL;
        return ERR_CNC;
    }
}

u16 CCnsSession::CncGetInterface(CCncSipInfoCtrlIF **ppCtrl)
{	
	if( m_pSipInfoCtrlIF != NULL)
    {
        *ppCtrl = m_pSipInfoCtrlIF;
        return NO_ERROR;
    }
    else
    {
        *ppCtrl = NULL;
        return ERR_CNC;
    }
}

u16 CCnsSession::CncGetInterface(CCncSysCtrlIF **ppCtrl)
{
	if( m_pSysCtrlIF != NULL)
    {
        *ppCtrl = m_pSysCtrlIF;
        return NO_ERROR;
    }
    else
    {
        *ppCtrl = NULL;
        return ERR_CNC;
    }
}

u16 CCnsSession::CncGetInterface(CCncPortDiagCtrlIF **ppCtrl)
{
	if( m_pPortDiagIF != NULL)
    {
        *ppCtrl = m_pPortDiagIF;
        return NO_ERROR;
    }
    else
    {
        *ppCtrl = NULL;
        return ERR_CNC;
    }
}

u16 CCnsSession::CncGetInterface(CCncCenterCtrlIF **ppCtrl)
{
	if( m_pCenterCtrlIF != NULL)
    {
        *ppCtrl = m_pCenterCtrlIF;
        return NO_ERROR;
    }
    else
    {
        *ppCtrl = NULL;
        return ERR_CNC;
    }
}

u16 CCnsSession::CncGetInterface(CCncNetMngCtrlIF **ppCtrl)
{
	if( m_pNetMngCtrlIF != NULL)
    {
        *ppCtrl = m_pNetMngCtrlIF;
        return NO_ERROR;
    }
    else
    {
        *ppCtrl = NULL;
        return ERR_CNC;
    }
}

/*===========================================================================
  函 数 名： IsConnectedCns
  功    能： 是否已和CNS建立了连接
  算法实现： 
  全局变量： 
  参    数： 
  返 回 值： BOOL32
 ----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2011/04/28    1.0		    肖楚然                  创建
===========================================================================*/
BOOL CCnsSession::IsConnectedCns()
{
	return g_CncApp.GetNodeId() != INVALID_NODE;
}

/*===========================================================================
  函 数 名： ConnectCns
  功    能： 连接Cns
  算法实现： 
  全局变量： 
  参    数： u32 dwIP    要连接的终端IP 本机序
             u32 dwPort  连接端口
             const CString &strUser   连接的用户名
             const CString &strPwd    用户密码
  返 回 值： u16 
 ----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2011/04/28    1.0		    肖楚然                  创建
===========================================================================*/
u16 CCnsSession::ConnectCns(u32 dwIP, u32 dwPort, const CString &strUser, 
							 const CString &strPwd, BOOL32 bConnect /* = TRUE */)
{
    // 建立TCP连接
    if( IsConnectedCns() )
    { 
		if( !m_bLogin )
		{
			return Refuse_CNC_LOGIN;
		}
        //如何已经登录了该IP，则直接返回，否则断开重连
        if ( dwIP == m_dwCnsIp )
        {		
			return ERR_CNC_ACTIVE_CONNECT;			           
        }
        else
        {
            DisconnectCns();
			return ERR_CNC_ACTIVE_CONNECT;
        }
        
    }
    
    //ClearDisp();
    // 重构消息分发表
    //BuildEventsMap();
    
    //建立Osp的TCP连接,得到本地机器的IP地址
	u32 dwCnNodeId = 0;
	if ( bConnect )
	{
		dwCnNodeId = OspConnectTcpNode( htonl(dwIP), static_cast<u16>(dwPort), /*5*/10   //2012.8.27 解决：由于多个平板同时连接cns 尤其在发送双流时会产生丢命令断开连接现象by yjj
			, 3, 5000/*30000*/, &m_dwLocalIP );
		//保留登陆Cns的ip
		m_dwCnsIp = dwIP;
		m_dwLocalIP = ntohl( m_dwLocalIP );
		if( dwCnNodeId == INVALID_NODE )
		{
			return ERR_CNC_TCPCONNECT;
		}		
	}
	else
	{
		dwCnNodeId = 0;
	}

    g_CncApp.SetNodeId( dwCnNodeId );
	g_AddrBookApp.SetNodeId( dwCnNodeId );
    //设置在node连接中断时需通知的appid和InstId
    ::OspNodeDiscCBReg( dwCnNodeId, /*AID_CNC2CNS_APP*/GetAppID(), 1);

	m_cUser.Empty();
    m_cUser.SetName((s8*)(LPCTSTR)strUser);
    m_cUser.SetPassword((s8*)(LPCTSTR)strPwd);

	// 向CNS发送登录请求
	memset( g_abyTemp,0, sizeof( g_abyTemp ));
    ZeroMemory(&m_cMsg, sizeof(CMessage));
    m_cMsg.event = ev_CnLogin_Req;
    m_cMsg.length = sizeof(CLoginRequest);
	memcpy( g_abyTemp, &m_cUser, sizeof(CLoginRequest) );
    m_cMsg.content = g_abyTemp;

    u16 awEvent[1];
    awEvent[0] = ev_CnLogin_Rsp;
	u16 wRet = PostCommand(this, awEvent, 1, TYPE_CMESSAGE, 3000);

// 	CTpMsg *pcTpMsg = GetKdvMsgPtr();
// 	pcTpMsg->SetEvent( ev_CnLogin_Req );
// 	pcTpMsg->SetBody( &m_cUser, sizeof(CLoginRequest) );
// 
//     u16 awEvent[1];
//     awEvent[0] = ev_CnLogin_Rsp;  
//     
//     u16 wRet = PostCommand(this,awEvent,1,TYPE_TPMSG );

	PrtMsg( ev_CnLogin_Req, emEventTypeCnsSend, "userName:%s pswd:%s", m_cUser.GetName(), m_cUser.GetPassword() );

	return wRet;
}

/*===========================================================================
  函 数 名： DisconnectCns
  功    能： 断开Cns
  算法实现： 
  全局变量： 
  参    数： 
  返 回 值： u16 
 ----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2011/04/28    1.0		    肖楚然                  创建
===========================================================================*/
u16 CCnsSession::DisconnectCns()
{
    if( !IsConnectedCns() )
    {
        return NO_ERROR;
    }
 
	//清除地址条目
    if ( m_pAddrBookIF != NULL && m_bUseAdddr ) 
    {
		dynamic_cast<CCncAddrbook*>(m_pAddrBookIF)->UnRegAddrBook();
    }	

    OspDisconnectTcpNode(g_CncApp.GetNodeId()); 
	m_dwCnsIp = 0;
    
    return NO_ERROR;
}


u16 CCnsSession::LoginCnsIns( u8 byIns )
{	
	CTpMsg *pcTpMsg = GetKdvMsgPtr();
	
	pcTpMsg->SetUserData( byIns );
	pcTpMsg->SetEvent( ev_CnLoginIns_Req );

	m_uInst = byIns;
	
	u16 wRet = PostMsg(TYPE_TPMSG);
	PrtMsg( ev_CnLoginIns_Req, emEventTypeCnsSend, "Inst: %d", m_uInst );
    return wRet;
}

//tpad版进行tpad的系统名修改 dyy 2013年8月29日
u16 CCnsSession::SetTpadSysName( string strSysName )
{    
    u8 abyTemp[TP_MAX_ALIAS_LEN+1] = { 0 };
    u16 wSize = ( strSysName.length() > (sizeof(abyTemp)-1) ? (sizeof(abyTemp)-1) : strSysName.length() ); 

    ZeroMemory(&m_cMsg, sizeof(CMessage));
    m_cMsg.event = ev_TPadSetSysName_Nty;
    m_cMsg.length = sizeof(abyTemp);
   
    memcpy( abyTemp, strSysName.c_str(), wSize );
    m_cMsg.content = abyTemp;
    
    u16 wRet = PostMsg( TYPE_CMESSAGE );

    PrtMsg( ev_TPadSetSysName_Nty, emEventTypeCnsSend, "cnc系统名称: %s", strSysName );
    return wRet;
}

u16 CCnsSession::ConnectTPad( TTPadSubInfo tSubInfo/*u32 dwIP, u32 dwPort, emTPadSubType emSubType*/ )
{
    //记录登陆TPad信息
    m_tTPadSubInfo = tSubInfo;

    // 建立TCP连接
    if( IsConnectedCns() )
    { 
        return ERR_CNC_ACTIVE_CONNECT;
    }

    //建立Osp的TCP连接,得到本地机器的IP地址
    u32 dwCnNodeId = OspConnectTcpNode( htonl(m_tTPadSubInfo.dwIp), static_cast<u16>(m_tTPadSubInfo.dwPort), /*5*/10
            , 3, 5000/*30000*/, &m_dwLocalIP );  
    if( dwCnNodeId == INVALID_NODE )
    {
        if ( g_wTimerID == 0 )
        {
            g_wTimerID = SetTimer( NULL, 0, 5000, TimerProc);
        } 
        return ERR_CNC_TCPCONNECT;
    }
  
    g_CncApp.SetNodeId( dwCnNodeId );
    g_AddrBookApp.SetNodeId( dwCnNodeId );
    //设置在node连接中断时需通知的appid和InstId
    ::OspNodeDiscCBReg( dwCnNodeId, /*AID_CNC2CNS_APP*/GetAppID(), 1);
    
    // 向CNS发送登录请求
    memset( g_abyTemp,0, sizeof( g_abyTemp ));
    ZeroMemory(&m_cMsg, sizeof(CMessage));
    m_cMsg.event = ev_CnLogin_Req;
    m_cMsg.length = sizeof(CLoginRequest);
    memcpy( g_abyTemp, &m_tTPadSubInfo.emType, sizeof( emTPadSubType ));
    m_cMsg.content = g_abyTemp;
    
    u16 wRet = PostMsg( TYPE_CMESSAGE );
    if( wRet != 0 )
    {
        if ( g_wTimerID == 0 )
        {
            g_wTimerID = SetTimer( NULL, 0, 5000, TimerProc);
        } 
    }
    else
    {
        if ( g_wTimerID != 0 )
        {
            KillTimer( NULL, g_wTimerID );
            g_wTimerID = 0;
        }
    }
   
	PrtMsg( ev_CnLogin_Req, emEventTypeCnsSend, "ConnectTPad" );
    return wRet;
}


/*===========================================================================
  函 数 名： BuildEventsMap
  功    能： 构建消息映射表
  算法实现： REG_PFUN():在70/common/kdvdispevent.h中实现，第一个参数为要处理的消息号，第二个参数为ex_XXX对应的处理函数
  全局变量： 
  参    数： 
  返 回 值： u16 
 ----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2011/04/28    1.0		    肖楚然                  创建
===========================================================================*/
void CCnsSession::BuildEventsMap()
{
	REG_PFUN( OSP_DISCONNECT, CCnsSession::OnLinkBreak );
	REG_PFUN( ev_CnLogin_Rsp, CCnsSession::OnCnsLoginRsp );
	REG_PFUN( ev_TppRefuseLogin_Nty, CCnsSession::OnCnsRefuseLoginNty );
	REG_PFUN( ev_CnList_Nty, CCnsSession::OnCnsListNty );
	REG_PFUN( ev_CnLoginIns_Rsp, CCnsSession::OnLoginCnsInsRsp );
	REG_PFUN( ev_tpRoomOffline_Nty, CCnsSession::OnCnsOfflineNty );
	REG_PFUN( ev_tpRoomOnline_Nty, CCnsSession::OnCnsOnlineNty );
	REG_PFUN( ev_CNSLoginByOther_Notify, CCnsSession::OnLoginByOtherNotify );

    REG_PFUN( ev_Cn_CentreSleepNty, CCnsSession::OnCentreSleepNty ); //中控待机消息

    REG_PFUN( ev_TPadLoginInfo_Nty, CCnsSession::OnTPadLoginUserNotify );
    REG_PFUN( ev_TPadHomeKey_Nty, CCnsSession::OnTPadHomeKeyNotify );
    REG_PFUN( ev_WBConfStateNty, CCnsSession::OnWBConfStateNty );
    REG_PFUN( ev_tpp_NewConfCall_Req,CCnsSession:: OnNewConfCallReq );
}

void CCnsSession::OnLinkBreak(const CMessage& cMsg)
{
	// OSP断链通知
    u32 dwNodeId = *(u32*)(cMsg.content);

    PrtMsg( OSP_DISCONNECT, emEventTypeCnsRecv, "Link Break (NodeID: %d)", dwNodeId );

    ClearWaiting();	// OSP断链后,尚未执行完的命令中断执行 
	ClearAllCommand(); // 清空所有在队列中等待执行的命令
    g_CncApp.ClearOspMsg(); //2012-7-12

    //与cns断链，但与tpad未断链，不将NodeId置空
    if ( dwNodeId == g_CncApp.GetNodeId() )
    {
        g_CncApp.SetNodeId(INVALID_NODE);

        if ( m_tTPadSubInfo.emType != emTPad_none && g_wTimerID == 0 )//与tpad断链后进行自动重连 dyy
        {
            g_wTimerID = SetTimer( NULL, 0, 5000, TimerProc );
        }
    }

	m_bLogin = FALSE;
    m_cUser.SetName("");
	m_cUser.SetPassword(""); 
	m_dwCnsIp = 0;
	m_uInst = 0;
	memset( &m_tCnList, 0, sizeof(m_tCnList) );

	if (m_pAddrBookIF) 
    {
		dynamic_cast<CCncAddrbook*>(m_pAddrBookIF)->OnLinkBreak( dwNodeId );
    }

    PostEvent(UI_CNS_DISCONNECTED);
}


void CCnsSession::OnCnsLoginRsp(const CMessage& cMsg)
{
// 	CTpMsg cTpMsg(&cMsg);	
// 	TLoginRet tLogRe = *reinterpret_cast<TLoginRet *>(cTpMsg.GetBody());

	TLoginRet tLogRe = *reinterpret_cast<TLoginRet *>( cMsg.content );

	PrtMsg( ev_CnLogin_Rsp, emEventTypeCnsRecv,"EmTpLoginUmsRet: %d, ErrorCode: %d ", tLogRe.GetRet(), tLogRe.m_dwErrorCode );

	//u16 wInsID = GETINS(cMsg.srcid);

	BOOL bLogin = FALSE;
	u32 dwErrCode = NO_ERROR;
	switch( tLogRe.GetRet() )
	{
	case tp_LoginUms_sucess:
		bLogin = TRUE;
		break;
	case tp_LoginUms_NameError: //用户名错误
		bLogin = FALSE;
		dwErrCode = ERR_UMC_LOGIN_UMS_USER_ERR;
		break;
	case tp_LoginUms_PwdError:	//密码错误
		bLogin = FALSE;
		dwErrCode = ERR_UMC_LOGIN_UMS_PSWD_ERR;
		break;
	case tp_LoginUms_MaxLogin:	//达到用户登录上限
		bLogin = FALSE;
		dwErrCode = ERR_UMC_LOGIN_UMS_MAX_LOGIN;
		break;
	case tp_LoginUms_Logged:	//用户已经登录
		bLogin = FALSE;
		dwErrCode = ERR_UMC_LOGIN_UMS_LOGED;
		break;
    case tp_LoginUms_SysIniting: //系统正在初始化
        bLogin = FALSE;
        dwErrCode = ERR_UMC_LOGIN_UMS_SYSINITING;
		break;
	default:
		bLogin = FALSE;
		dwErrCode = ERR_UMC_LOGIN_FAIL;
		break;
	} 

	m_bLogin = bLogin;

	// 通知界面
	PostEvent(UI_CNS_CONNECTED, m_bLogin, dwErrCode);

    if ( m_bLogin )
    {
        // 初始化工作
        if ( m_bUseAdddr && m_pAddrBookIF != NULL )
        {
	        dynamic_cast<CCncAddrbook*>(m_pAddrBookIF)->RegAddrBook();
        }
    }
    else
    {
        if ( m_tTPadSubInfo.emType == emTPad_none ) //若为pad版，断链后，若收到tpad连接cns未成功的消息时，不进行断链  dyy 
        {
            DisconnectCns();
        }
    }
	
}


void CCnsSession::OnCnsListNty(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);

	m_tCnList = *reinterpret_cast<TTPCnList*>(cTpMsg.GetBody());

	PostEvent( UI_CNS_CNLIST_NOTIFY );

	PrtMsg( ev_CnList_Nty, emEventTypeCnsRecv, "TTPCnList: wNum: %d", m_tCnList.wNum );

	if ( m_tCnList.wNum > 0 )
	{
		PrtMsg ( "\tCnName: " );
		for ( int i = 0; i < m_tCnList.wNum; i++ )
		{
			PrtMsg( "%s ", m_tCnList.tCn[i].achName );
		}
		PrtMsg ( "\n" );
	}
	
}

const TTPCnList& CCnsSession::GetConnectCnsList() const
{
	return m_tCnList;
}

void CCnsSession::OnLoginCnsInsRsp(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);
	
	TLoginRet tLogRe = *reinterpret_cast<TLoginRet *>(cTpMsg.GetBody());
	m_uInst = cTpMsg.GetHomeplace();
	
	PrtMsg( ev_CnLoginIns_Rsp, emEventTypeCnsRecv, "EmTpLoginUmsRet: %d, Inst: %d ", tLogRe.GetRet(), m_uInst );
		
	BOOL bLogin = FALSE;
	u32 dwErrCode = NO_ERROR;
	switch( tLogRe.GetRet() )
	{
	case tp_LoginUms_sucess:
		bLogin = TRUE;
		break;
	case tp_LoginUms_PwdError:	//用户名或者密码错误
		bLogin = FALSE;
		dwErrCode = ERR_UMC_LOGIN_UMS_PSWD_ERR;
		break;
	case tp_LoginUms_MaxLogin:	//达到用户登录上限
		bLogin = FALSE;
		dwErrCode = ERR_UMC_LOGIN_UMS_MAX_LOGIN;
		break;
	case tp_LoginUms_Logged:	//用户已经登录
		bLogin = FALSE;
		dwErrCode = ERR_UMC_LOGIN_UMS_LOGED;
		break;
	default:
		bLogin = FALSE;
		dwErrCode = ERR_UMC_LOGIN_FAIL;
		break;
	} 
	
	if ( bLogin )
	{		
		PostEvent( UI_CNSINS_CONNECTED, bLogin, dwErrCode );
	}
}

void CCnsSession::OnCnsOfflineNty( const CMessage& cMsg )
{
	CTpMsg cTpMsg(&cMsg);
	s8 achCnsName[TP_MAX_ALIAS_LEN + 1] = {0};
	s8 *pRoomName = reinterpret_cast<s8 *>(cTpMsg.GetBody());
	memcpy( achCnsName, pRoomName, sizeof(achCnsName) );
	u8 uInst = cTpMsg.GetHomeplace();
			
	//PrtMsg( ev_tpRoomOffline_Nty, emEventTypeCnsRecv, "CnsOffline: %s, bMainCns: %d, Inst: %d", achCnsName, bMainCns, uInst );
	
	int nCount = m_tCnList.wNum;
	BOOL bFind = FALSE;
	for ( int i = 0; i < nCount; i++ )
	{
		if ( uInst == m_tCnList.tCn[i].byInsId )
		{
			bFind = TRUE;
		}
		if ( bFind && ( i + 1 < nCount) )
		{
			m_tCnList.tCn[i] = m_tCnList.tCn[i+1];
		}
	}
	if ( bFind )
	{
		m_tCnList.wNum--;
		memset( &m_tCnList.tCn[nCount-1], 0, sizeof(TTPCn) );
		//刷新
		PostEvent( UI_CNS_CNLIST_NOTIFY );
	}
}

void CCnsSession::OnCnsOnlineNty(const CMessage& cMsg)
{
	CTpMsg cTpMsg(&cMsg);
	s8 achCnsName[TP_MAX_ALIAS_LEN + 1] = {0};
	s8 *pRoomName = reinterpret_cast<s8 *>(cTpMsg.GetBody());
	memcpy( achCnsName, pRoomName, sizeof(achCnsName) );
	u8 uInst = cTpMsg.GetHomeplace();
	
	PrtMsg( ev_tpRoomOnline_Nty, emEventTypeCnsRecv, "CnsOnline: %s, Inst: %d", achCnsName, uInst );

	int nCount = m_tCnList.wNum;
	BOOL bFind = FALSE;
	for ( int i = 0; i < nCount; i++ )
	{
		if ( uInst == m_tCnList.tCn[i].byInsId )
		{
			bFind = TRUE;
			break;
		}
	}
	if ( !bFind )
	{
		m_tCnList.wNum++;
		m_tCnList.tCn[nCount].byInsId = uInst;
		memcpy( m_tCnList.tCn[nCount].achName, achCnsName, sizeof(achCnsName) );
		PostEvent( UI_CNS_CNLIST_NOTIFY );
	}
}


//被抢断
void CCnsSession::OnLoginByOtherNotify(const CMessage& cMsg)
{
	u32 dwIP = *reinterpret_cast<u32*>( cMsg.content );

	in_addr tAddr;
	tAddr.S_un.S_addr = dwIP ;   
	PrtMsg( ev_CNSLoginByOther_Notify, emEventTypeCnsRecv, "抢登通知(抢占方 IP:  %s ；dwIP=%d )", inet_ntoa(tAddr), dwIP );
	
	PostEvent( UI_UMS_GRAB_LOGIN_NOTIFY, (WPARAM)dwIP );
}	


void CCnsSession::OnTPadLoginUserNotify(const CMessage& cMsg)
{
    //CLoginRequest cUser = *reinterpret_cast<CLoginRequest *>( cMsg.content );
    TPadLoginInfo tLoginInfo = *reinterpret_cast<TPadLoginInfo *>( cMsg.content );
    
    //传过来的IP为主机序
    m_dwCnsIp = tLoginInfo.dwCnsIp;
    m_dwLocalIP = tLoginInfo.dwLocalIp;
    m_cUser = tLoginInfo.cUserInfo;

    in_addr tAddr;
    tAddr.S_un.S_addr = htonl(m_dwCnsIp);  
    PrtMsg( ev_TPadLoginInfo_Nty, emEventTypeTPadRecv, "LoginIp:%s, UserName: %s", inet_ntoa(tAddr), m_cUser.GetName() );
    
    PostEvent( UI_TPAD_LOGINUSER_NOTIFY, (WPARAM)&tLoginInfo );
}


void CCnsSession::OnTPadHomeKeyNotify(const CMessage& cMsg)
{
    PrtMsg( ev_TPadHomeKey_Nty, emEventTypeTPadRecv, "" );

    PostEvent( UI_TPAD_HOMEKEY_NOTIFY );
}


void CCnsSession::OnCentreSleepNty(const CMessage& cMsg)
{
    CTpMsg cTpMsg(&cMsg);
    
    PrtMsg( ev_Cn_CentreSleepNty, emEventTypeCnsRecv, "" );
    
    PostEvent( UI_TPAD_CENTRESLEEP_NTY );
}

u16 CCnsSession::DisConnectTpad()
{
    ZeroMemory(&m_cMsg, sizeof(CMessage));
    m_cMsg.event = ev_TpadDisconnectCns_Nty;	
	u16 wRet = PostMsg( TYPE_CMESSAGE );
	return wRet;
}

 

u16 CCnsSession::InitializeOsp()
{
	// 初始化OSP
    const u32 dwTelnetPort = 0;
    if( !IsOspInitd() )
    {

        BOOL bTelnet  = FALSE ;

#ifdef _DEBUG
        bTelnet = TRUE;
#endif

        if(!OspInit( bTelnet, dwTelnetPort))
        {
            return ERR_CMS_OSP_Init;
        }
        else
        {
            m_bInitOsp = FALSE;
        }
    }
    else
    {
        m_bInitOsp = TRUE;
    }
    
    // 构造事件映射表
	BuildEventsMap(); 
	
	char szOspApp[] = "CncLib1.0";
	const u32 dwPrior = 80;
	int nRet = g_CncApp.CreateApp(&szOspApp[0], /*AID_CNC2CNS_APP*/GetAppID(), dwPrior, 300, 200);
	ASSERT(nRet == 0);
    
	PrtMsg( "cncLib osp启动成功\n" );

    return NO_ERROR;
}

void CALLBACK TimerProc(HWND hWnd,UINT nMsg,UINT nTimerid,DWORD dwTime) //pad版的cnc，断链后自动连接tpad
{
    u16 wRet = CCnsSession::s_pCnsSession->ConnectTPad( CCnsSession::s_pCnsSession->GetTPadSubInfo() );
}

void CCnsSession::OnWBConfStateNty(const CMessage& cMsg)
{
    bool bIsInWBConf = *reinterpret_cast<bool *>( cMsg.content );
    
    PrtMsg( ev_WBConfStateNty, emEventTypeTPadRecv, "IsInWBConf:%d", bIsInWBConf );
    
    PostEvent( UI_WBCONFSTATE_NTY, (WPARAM)&bIsInWBConf );
}

void CCnsSession::OnNewConfCallReq( const CMessage& cMsg )
{    
    CTpMsg cTpMsg(&cMsg); 
    
    s8 sConfName = *reinterpret_cast<s8*>(cTpMsg.GetBody());
    
    bool bIsInWBConf = *reinterpret_cast<bool *>( cMsg.content );
    
    PrtMsg( ev_tpp_NewConfCall_Req, emEventTypeCnsRecv, "WB新会议呼进请求Tpad加入" );
    
    PostEvent( UI_NEWWBCONFCALL_REQ, 0, (LPARAM)&sConfName  );
}

void CCnsSession::OnCnsRefuseLoginNty(const CMessage& cMsg)
{
	u32 dwIP = *reinterpret_cast<u32*>( cMsg.content );
	
	in_addr tAddr;
	tAddr.S_un.S_addr = dwIP ;   
	PrtMsg( ev_TppRefuseLogin_Nty, emEventTypeCnsRecv, "抢登失败通知(使用方 IP:  %s ；dwIP=%d )", inet_ntoa(tAddr), dwIP );
	
	PostEvent( UI_CNS_REFUSE_LOGIN_NOTIFY, (WPARAM)dwIP );
}

