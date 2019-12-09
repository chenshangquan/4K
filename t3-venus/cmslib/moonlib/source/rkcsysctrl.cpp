#include "stdafx.h"
#include "rkcsysctrl.h"
//#include "event.h"
#include "socketmanager.h"
//#include "rkcevent.h"
#include "rkcprintctrl.h"
#include "Tftp.h"
#include "md5.h"

CRkcSysCtrl::CRkcSysCtrl(CRkcSession &cSession) : CRkcSysCtrlIF()
{
    memset(&m_tRK100MsgHead,0,sizeof(m_tRK100MsgHead));
    memset(&m_tRK100UpdateHead, 0, sizeof(TRK100UpdateHead));
    memset(&m_tRK100TftpFwUpdate, 0, sizeof(TRK100TftpFwUpdate));
    m_pSession = &cSession;
    BuildEventsMap();
}

CRkcSysCtrl::~CRkcSysCtrl()
{

}

u16 CRkcSysCtrl::SocketConnect(s8* pchIP, u32 dwPort)
{
    SOCKETWORK->setSocketIP(pchIP);
    SOCKETWORK->SetSocketPort(dwPort);
    u8 nRe = SOCKETWORK->OpenSocket();
    PrtRkcMsg( RK100_EVT_LOGIN, emEventTypeScoketSend, "connect Ip : nRe =  %d", nRe );
    return nRe;
}

u16 CRkcSysCtrl::CloseSocket()
{
    SOCKETWORK->CloseSocket();
    return NO_ERROR;
}

u16 CRkcSysCtrl::SendLoginReq( TRK100LoginInfo tRK100LoginInfo )
{
    TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(RK100_EVT_LOGIN);
    tRK100MsgHead.wMsgLen = htons(sizeof(TRK100LoginInfo));
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容
    CMD5Encrypt cMd5;
    cMd5.GetEncrypted(tRK100LoginInfo.szPwd, tRK100LoginInfo.szPwd);//Md5加密
    rkmsg.CatBody(&tRK100LoginInfo, sizeof(TRK100LoginInfo));//添加消息内容

    PrtRkcMsg( RK100_EVT_LOGIN, emEventTypeScoketSend, "Login : username =  %s", tRK100LoginInfo.szUsr );
    SOCKETWORK->SendDataPack(rkmsg);//消息发送
    return NOERROR;
}

bool CRkcSysCtrl::IsLoginState()
{
    return SOCKETWORK->IsSocket();
}

u16 CRkcSysCtrl::SendModifyPasswordReq( TRK100LoginInfo tRK100LoginInfo )
{
    TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(RK100_EVT_SET_PASSWORD);
    tRK100MsgHead.wMsgLen = htons(sizeof(TRK100LoginInfo));
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容
    CMD5Encrypt cMd5;
    cMd5.GetEncrypted(tRK100LoginInfo.szPwd, tRK100LoginInfo.szPwd);//Md5加密
    rkmsg.CatBody(&tRK100LoginInfo, sizeof(TRK100LoginInfo));//添加消息内容
    CSocketManager::GetSocketManager()->SendDataPack(rkmsg);//消息发送
    return NOERROR;
}

void CRkcSysCtrl::BuildEventsMap()
{
    REG_PFUN( RK100_EVT_LOGIN_ACK, CRkcSysCtrl::OnLoginRsp );
    REG_PFUN( UI_RKC_DISCONNECTED, CRkcSysCtrl::OnDicconnected );
    REG_PFUN( RK100_EVT_LOGIN_OTHER, CRkcSysCtrl::OnLoginOther );
    REG_PFUN( RK100_EVT_SET_PASSWORD_ACK, CRkcSysCtrl::OnModifyPasswordRsp );
    REG_PFUN( RK100_EVT_TFTP_UPDATE_FIRST_ACK, CRkcSysCtrl::OnSetFtpUpdateFirstRsp);
    REG_PFUN( RK100_EVT_TFTP_UPDATE_FIRST_NOTIFY, CRkcSysCtrl::OnSetFtpUpdateFirstNotify);
    REG_PFUN( RK100_EVT_TFTP_UPDATE_SECOND_ACK, CRkcSysCtrl::OnSetFtpUpdateSecondRsp);
    REG_PFUN( RK100_EVT_TFTP_UPDATE_SECOND_NOTIFY, CRkcSysCtrl::OnSetFtpUpdateSecondNotify);
}

void CRkcSysCtrl::OnDicconnected(const CMessage& cMsg)
{
    //清空数据
    memset(&m_tRK100MsgHead,0,sizeof(m_tRK100MsgHead));
    memset(&m_tRK100UpdateHead, 0, sizeof(TRK100UpdateHead));
    memset(&m_tRK100TftpFwUpdate, 0, sizeof(TRK100TftpFwUpdate));

    //发送界面提醒
    PrtRkcMsg( RK100_EVT_LOGIN_ACK, emEventTypeScoketRecv, "UI_RKC_DISCONNECTED" );
    //PostEvent( UI_MOONTOOL_DISCONNECTED);
}

void CRkcSysCtrl::OnLoginOther(const CMessage& cMsg)
{
    TRK100MsgHead tMsgHead = *reinterpret_cast<TRK100MsgHead*>( cMsg.content );
    tMsgHead.dwEvent = ntohl(tMsgHead.dwEvent);
    tMsgHead.dwHandle = ntohl(tMsgHead.dwHandle);
    tMsgHead.dwProtocolVer = ntohl(tMsgHead.dwProtocolVer);
    tMsgHead.dwRsvd = ntohl(tMsgHead.dwRsvd);
    tMsgHead.dwSerial = ntohl(tMsgHead.dwSerial);
    tMsgHead.nArgv = ntohl(tMsgHead.nArgv);
    tMsgHead.wExtLen = ntohs(tMsgHead.wExtLen);
    tMsgHead.wMsgLen = ntohs(tMsgHead.wMsgLen);
    tMsgHead.wOptRtn = ntohs(tMsgHead.wOptRtn);
    tMsgHead.wReserved1 = ntohs(tMsgHead.wReserved1);

    u32 dwIP = 0;
    if (tMsgHead.wMsgLen != 0)
    {
        dwIP = *reinterpret_cast<u32*>( cMsg.content + sizeof(TRK100MsgHead) );
	}

    CString strIP;
    struct in_addr addrIPAddr;
    addrIPAddr.S_un.S_addr =  dwIP;
	strIP = inet_ntoa(addrIPAddr);

    PrtRkcMsg( RK100_EVT_LOGIN_OTHER, emEventTypeScoketRecv, "被[IP:%s]抢登...", strIP);
    PostEvent( UI_UMS_GRAB_LOGIN_NOTIFY, (WPARAM)dwIP );
}

void CRkcSysCtrl::OnLoginRsp(const CMessage& cMsg)
{
    TRK100MsgHead tMsgHead = *reinterpret_cast<TRK100MsgHead*>( cMsg.content );
    tMsgHead.dwEvent = ntohl(tMsgHead.dwEvent);
    tMsgHead.dwHandle = ntohl(tMsgHead.dwHandle);
    tMsgHead.dwProtocolVer = ntohl(tMsgHead.dwProtocolVer);
    tMsgHead.dwRsvd = ntohl(tMsgHead.dwRsvd);
    tMsgHead.dwSerial = ntohl(tMsgHead.dwSerial);
    tMsgHead.nArgv = ntohl(tMsgHead.nArgv);
    tMsgHead.wExtLen = ntohs(tMsgHead.wExtLen);
    tMsgHead.wMsgLen = ntohs(tMsgHead.wMsgLen);
    tMsgHead.wOptRtn = ntohs(tMsgHead.wOptRtn);
    tMsgHead.wReserved1 = ntohs(tMsgHead.wReserved1);

    PrtRkcMsg( RK100_EVT_LOGIN_ACK, emEventTypeScoketRecv, "LoginRsp : wOptRtn =  %d", tMsgHead.wOptRtn );

    if (RK100_OPT_RTN_OK != tMsgHead.wOptRtn && tMsgHead.wOptRtn != RK100_OPT_ERR_FIRST_LOGIN)
    {
        CloseSocket();
    }
    m_tRK100MsgHead = tMsgHead;
    PostEvent(UI_MOONTOOL_CONNECTED, WPARAM(RK100_OPT_RTN_OK == tMsgHead.wOptRtn || RK100_OPT_ERR_FIRST_LOGIN == tMsgHead.wOptRtn) , (LPARAM)tMsgHead.wOptRtn );
}

void CRkcSysCtrl::OnModifyPasswordRsp(const CMessage& cMsg)
{
    TRK100MsgHead tMsgHead = *reinterpret_cast<TRK100MsgHead*>( cMsg.content );
    tMsgHead.dwEvent = ntohl(tMsgHead.dwEvent);
    tMsgHead.dwHandle = ntohl(tMsgHead.dwHandle);
    tMsgHead.dwProtocolVer = ntohl(tMsgHead.dwProtocolVer);
    tMsgHead.dwRsvd = ntohl(tMsgHead.dwRsvd);
    tMsgHead.dwSerial = ntohl(tMsgHead.dwSerial);
    tMsgHead.nArgv = ntohl(tMsgHead.nArgv);
    tMsgHead.wExtLen = ntohs(tMsgHead.wExtLen);
    tMsgHead.wMsgLen = ntohs(tMsgHead.wMsgLen);
    tMsgHead.wOptRtn = ntohs(tMsgHead.wOptRtn);
    tMsgHead.wReserved1 = ntohs(tMsgHead.wReserved1);

    PostEvent(UI_RKC_MODIFY_PASSWORD, WPARAM(RK100_OPT_RTN_OK == tMsgHead.wOptRtn) , (LPARAM)tMsgHead.wOptRtn );
}

u16 CRkcSysCtrl::GetLoginBackInfo(TRK100MsgHead& tRK100MsgHead)
{
    tRK100MsgHead = m_tRK100MsgHead;
    return NOERROR;
}

void CRkcSysCtrl::DispEvent(const CMessage &cMsg)
{
    DISP_FUN(CRkcSysCtrl, cMsg);
}

void CRkcSysCtrl::OnTimeOut(u16 wEvent)
{ 
}

u16 CRkcSysCtrl::SetFtpUpdateFirst(TRK100TftpFwUpdate tRK100TftpFwUpdate)
{
    //保存参数 用于second消息发送
    m_tRK100TftpFwUpdate = tRK100TftpFwUpdate;

    TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(RK100_EVT_TFTP_UPDATE_FIRST);
    tRK100MsgHead.wMsgLen = htons(sizeof(TRK100TftpFwUpdate));
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容
    tRK100TftpFwUpdate.dwTftpSvrIp = htonl(tRK100TftpFwUpdate.dwTftpSvrIp);
    tRK100TftpFwUpdate.dwFileSize = htonl(tRK100TftpFwUpdate.dwFileSize);
    rkmsg.CatBody(&tRK100TftpFwUpdate, sizeof(TRK100TftpFwUpdate));//添加后续消息
    SOCKETWORK->SendDataPack(rkmsg);//消息发送

    in_addr tAddr;
	tAddr.S_un.S_addr = m_tRK100TftpFwUpdate.dwTftpSvrIp;
    PrtRkcMsg( RK100_EVT_TFTP_UPDATE_FIRST, emEventTypeScoketSend, "IP = %s, FileSize = %d", inet_ntoa(tAddr), m_tRK100TftpFwUpdate.dwFileSize );
    return NOERROR;
}

void CRkcSysCtrl::OnSetFtpUpdateFirstRsp(const CMessage& cMsg)
{
    TRK100MsgHead tMsgHead = *reinterpret_cast<TRK100MsgHead*>( cMsg.content );
    tMsgHead.dwEvent = ntohl(tMsgHead.dwEvent);
    tMsgHead.dwHandle = ntohl(tMsgHead.dwHandle);
    tMsgHead.dwProtocolVer = ntohl(tMsgHead.dwProtocolVer);
    tMsgHead.dwRsvd = ntohl(tMsgHead.dwRsvd);
    tMsgHead.dwSerial = ntohl(tMsgHead.dwSerial);
    tMsgHead.nArgv = ntohl(tMsgHead.nArgv);
    tMsgHead.wExtLen = ntohs(tMsgHead.wExtLen);
    tMsgHead.wMsgLen = ntohs(tMsgHead.wMsgLen);
    tMsgHead.wOptRtn = ntohs(tMsgHead.wOptRtn);
    tMsgHead.wReserved1 = ntohs(tMsgHead.wReserved1);

    PrtRkcMsg( RK100_EVT_TFTP_UPDATE_FIRST_ACK, emEventTypeScoketRecv, "wOptRtn = %d", tMsgHead.wOptRtn);
    PostEvent(UI_RKC_UPDATE_FIRST_ACK, WPARAM(RK100_OPT_RTN_OK == tMsgHead.wOptRtn) , (LPARAM)tMsgHead.wOptRtn);

}

void CRkcSysCtrl::OnSetFtpUpdateFirstNotify(const CMessage& cMsg)
{
    TRK100MsgHead tMsgHead = *reinterpret_cast<TRK100MsgHead*>( cMsg.content );
    tMsgHead.dwEvent = ntohl(tMsgHead.dwEvent);
    tMsgHead.dwHandle = ntohl(tMsgHead.dwHandle);
    tMsgHead.dwProtocolVer = ntohl(tMsgHead.dwProtocolVer);
    tMsgHead.dwRsvd = ntohl(tMsgHead.dwRsvd);
    tMsgHead.dwSerial = ntohl(tMsgHead.dwSerial);
    tMsgHead.nArgv = ntohl(tMsgHead.nArgv);
    tMsgHead.wExtLen = ntohs(tMsgHead.wExtLen);
    tMsgHead.wMsgLen = ntohs(tMsgHead.wMsgLen);
    tMsgHead.wOptRtn = ntohs(tMsgHead.wOptRtn);
    tMsgHead.wReserved1 = ntohs(tMsgHead.wReserved1);

    if (tMsgHead.wMsgLen != 0)
    {
        m_tRK100UpdateHead = *reinterpret_cast<TRK100UpdateHead*>( cMsg.content + sizeof(TRK100MsgHead) );
        m_tRK100UpdateHead.Magic = ntohl(m_tRK100UpdateHead.Magic);
    }

    PrtRkcMsg( RK100_EVT_TFTP_UPDATE_FIRST_NOTIFY, emEventTypeScoketRecv, "wOptRtn = %d, version:%s", tMsgHead.wOptRtn, m_tRK100UpdateHead.Version);
    PostEvent(UI_RKC_UPDATE_FIRST_NTY, WPARAM(RK100_OPT_RTN_OK == tMsgHead.wOptRtn) , (LPARAM)tMsgHead.wOptRtn);
}

u16 CRkcSysCtrl::SetFtpUpdateSecond()
{
    TRK100MsgHead tRK100MsgHead;//定义消息头结构体
    memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
    //整型传数据集的转网络序
    tRK100MsgHead.dwEvent = htonl(RK100_EVT_TFTP_UPDATE_SECOND);
    tRK100MsgHead.wMsgLen = htons(sizeof(TRK100TftpFwUpdate));
    CRkMessage rkmsg;//定义消息
    rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容
    m_tRK100TftpFwUpdate.dwTftpSvrIp = htonl(m_tRK100TftpFwUpdate.dwTftpSvrIp);
    m_tRK100TftpFwUpdate.dwFileSize = htonl(m_tRK100TftpFwUpdate.dwFileSize);
    rkmsg.CatBody(&m_tRK100TftpFwUpdate, sizeof(TRK100TftpFwUpdate));//添加后续消息
    SOCKETWORK->SendDataPack(rkmsg);//消息发送
    return NOERROR;
}

void CRkcSysCtrl::OnSetFtpUpdateSecondRsp(const CMessage& cMsg)
{
    TRK100MsgHead tMsgHead = *reinterpret_cast<TRK100MsgHead*>( cMsg.content );
    tMsgHead.dwEvent = ntohl(tMsgHead.dwEvent);
    tMsgHead.dwHandle = ntohl(tMsgHead.dwHandle);
    tMsgHead.dwProtocolVer = ntohl(tMsgHead.dwProtocolVer);
    tMsgHead.dwRsvd = ntohl(tMsgHead.dwRsvd);
    tMsgHead.dwSerial = ntohl(tMsgHead.dwSerial);
    tMsgHead.nArgv = ntohl(tMsgHead.nArgv);
    tMsgHead.wExtLen = ntohs(tMsgHead.wExtLen);
    tMsgHead.wMsgLen = ntohs(tMsgHead.wMsgLen);
    tMsgHead.wOptRtn = ntohs(tMsgHead.wOptRtn);
    tMsgHead.wReserved1 = ntohs(tMsgHead.wReserved1);

    PrtRkcMsg( RK100_EVT_TFTP_UPDATE_SECOND_ACK, emEventTypeScoketRecv, "wOptRtn = %d", tMsgHead.wOptRtn);
}

void CRkcSysCtrl::OnSetFtpUpdateSecondNotify(const CMessage& cMsg)
{
    TRK100MsgHead tMsgHead = *reinterpret_cast<TRK100MsgHead*>( cMsg.content );
    tMsgHead.dwEvent = ntohl(tMsgHead.dwEvent);
    tMsgHead.dwHandle = ntohl(tMsgHead.dwHandle);
    tMsgHead.dwProtocolVer = ntohl(tMsgHead.dwProtocolVer);
    tMsgHead.dwRsvd = ntohl(tMsgHead.dwRsvd);
    tMsgHead.dwSerial = ntohl(tMsgHead.dwSerial);
    tMsgHead.nArgv = ntohl(tMsgHead.nArgv);
    tMsgHead.wExtLen = ntohs(tMsgHead.wExtLen);
    tMsgHead.wMsgLen = ntohs(tMsgHead.wMsgLen);
    tMsgHead.wOptRtn = ntohs(tMsgHead.wOptRtn);
    tMsgHead.wReserved1 = ntohs(tMsgHead.wReserved1);

    PrtRkcMsg( RK100_EVT_TFTP_UPDATE_SECOND_NOTIFY, emEventTypeScoketRecv, "wOptRtn = %d", tMsgHead.wOptRtn);
    PostEvent(UI_RKC_UPDATE_SECOND_NTY, WPARAM(RK100_OPT_RTN_OK == tMsgHead.wOptRtn) , (LPARAM)tMsgHead.wOptRtn);
}

u16 CRkcSysCtrl::GetUpdateConfig(TRK100UpdateHead& tRK100UpdateHead)
{
    tRK100UpdateHead = m_tRK100UpdateHead;
    return true;
}

//Tftp相关接口
bool CRkcSysCtrl::OpenTftp()
{
    try
    {
        return CTftpOp::Open();
    }
    catch (...)
    {
        return false;
    }
}
bool CRkcSysCtrl::CloseTftp()
{
    try
    {
        return CTftpOp::Open();
    }
    catch (...)
    {
        return false;
    }
    return CTftpOp::Close();
}
bool CRkcSysCtrl::SetTftpPath(const s8 *pchPath)
{
    try
    {
        return CTftpOp::SetTftpPath(pchPath);
    }
    catch (...)
    {
        return false;
    }
}
bool CRkcSysCtrl::SetDhcpBootFile(const s8 *pchPath)
{
    try
    {
        return CTftpOp::SetDhcpBootFile(pchPath);
    }
    catch (...)
    {
        return false;
    }
}
bool CRkcSysCtrl::KillTftpProcess()
{
    try
    {
        return CTftpOp::KillTftpProcess();
    }
    catch (...)
    {
        return false;
    }
}
