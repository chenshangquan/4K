// sysconfig.cpp: implementation of the CSysConfig class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "sysconfig.h"
#include "socketmanager.h"
//#include "rkcevent.h"
#include "rkcprintctrl.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSysConfig::CSysConfig( CRkcSession &cSession) : CSysConfigIF()                                                 
{
	m_pSession = &cSession;

	BuildEventsMap();
} 

CSysConfig::~CSysConfig()
{
	
}


void CSysConfig::BuildEventsMap()
{  
	//断链清空资源
	REG_PFUN(OSP_DISCONNECT, CSysConfig::OnLinkBreak); 
	REG_PFUN(ev_TpMoonVerInfo_Nty, CSysConfig::OnSoftWareVerInfoNty);
	REG_PFUN(ev_TpCamOutPortInfo_Nty, CSysConfig::OnCamOutputInfoNty);
	REG_PFUN(ev_TpCamImageAdjust_Nty, CSysConfig::OnCamImageAdjustNty);
	REG_PFUN(ev_TpCamImageAdjust_Ind, CSysConfig::OnCamImageAdjustInd);	
	REG_PFUN(ev_TpCamOutPortInfo_Ind, CSysConfig::OnCamOutputInfoInd);
	REG_PFUN(ev_TpMoonCfgEthnet_Ind, CSysConfig::OnEthnetInfoInd);
	REG_PFUN(ev_TpSetLVDSBaud_Ind, CSysConfig::OnLVDBaudInd);
	REG_PFUN( ev_TpSetLVDSBaud_Nty, CSysConfig::OnLVDBaudNty);
}

void CSysConfig::OnLinkBreak(const CMessage& cMsg)
{

}

void CSysConfig::DispEvent(const CMessage &cMsg)
{
	DISP_FUN( CSysConfig, cMsg) ;
}

void CSysConfig::OnTimeOut(u16 wEvent)
{
    // 发送超时事件通知
   //PostEvent(UI_UMS_CMD_TIMEOUT, wEvent);
} 

void CSysConfig::OnSoftWareVerInfoNty( const CMessage& cMsg )
{
	/*CTpMsg cTpMsg(&cMsg);
	s8 *achSoftWareVer = (s8*)( cTpMsg.GetBody() );

	EmTpVer emMoonVer = *(EmTpVer*)( cTpMsg.GetBody()+sizeof(s8)*MOON_MAX_DEVICEVER_LEN);
	PrtMsg( ev_TpMoonVerInfo_Nty, emEventTypemoontoolRecv, "SoftWareVer:%s", achSoftWareVer );

	PostEvent( UI_MOONTOOL_VERINFO_NTY, (WPARAM)achSoftWareVer, (LPARAM)&emMoonVer );*/
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

	s8* achSoftWareVer = NULL;
	EmTpVer emMoonVer = tp_Ver_MOON90;
	if (tMsgHead.wMsgLen != 0)
	{
		achSoftWareVer = (s8*)( cMsg.content );
		emMoonVer = *reinterpret_cast<EmTpVer*>( cMsg.content + sizeof(s8)*MOON_MAX_DEVICEVER_LEN + sizeof(EmTPImageAdjust) );
	}

	PrtRkcMsg( ev_TpMoonVerInfo_Nty, emEventTypeScoketRecv, "SoftWareVer:%s", achSoftWareVer);
	PostEvent( UI_MOONTOOL_VERINFO_NTY, (WPARAM)achSoftWareVer, (LPARAM)&emMoonVer );
}

void CSysConfig::OnCamOutputInfoNty( const CMessage& cMsg )
{
	/*CTpMsg cTpMsg(&cMsg);
	EmTPDVIOutPortType emOutputType = *(EmTPDVIOutPortType*)( cTpMsg.GetBody() );
	EmTPMOONOutMode emMoonOutMode = *(EmTPMOONOutMode*)( cTpMsg.GetBody()+sizeof(EmTPDVIOutPortType) );

	PrtMsg( ev_TpCamOutPortInfo_Nty, emEventTypemoontoolRecv, "EmTPDVIOutPortType:%d, EmTPMOONOutMode:%d", emOutputType, emMoonOutMode );

	PostEvent( UI_MOONTOOL_CAMOUTPUT_INFO_NTY, (WPARAM)emOutputType, (LPARAM)emMoonOutMode );*/
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

	EmTPDVIOutPortType emOutputType = TPMOON_DVI_MODE_INVALID;
	EmTPMOONOutMode emMoonOutMode = em_MoonOutMode_Unknown;
	if (tMsgHead.wMsgLen != 0)
	{
		emOutputType = *reinterpret_cast<EmTPDVIOutPortType*>( cMsg.content + sizeof(EmTPDVIOutPortType) );
		emMoonOutMode = *reinterpret_cast<EmTPMOONOutMode*>( cMsg.content + sizeof(EmTPDVIOutPortType) + sizeof(EmTPMOONOutMode) );
	}

	PrtRkcMsg( ev_TpCamOutPortInfo_Nty, emEventTypeScoketRecv, "EmTPDVIOutPortType:%d, EmTPMOONOutMode:%d", emOutputType, emMoonOutMode );
	PostEvent( UI_MOONTOOL_CAMOUTPUT_INFO_NTY, (WPARAM)emOutputType, (LPARAM)emMoonOutMode );
}

void CSysConfig::OnCamImageAdjustNty( const CMessage& cMsg )
{
	/*CTpMsg cTpMsg(&cMsg);
	EmTPImageAdjust emImageAdjust = *(EmTPImageAdjust*)( cTpMsg.GetBody() );

	PrtMsg( ev_TpCamImageAdjust_Nty, emEventTypemoontoolRecv, "EmTPImageAdjust:%d", emImageAdjust );

	PostEvent( UI_MOONTOOL_IMAGE_ADJUST_NTY, (WPARAM)emImageAdjust, NULL );*/
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

	EmTPImageAdjust emImageAdjust = emClosed;
	if (tMsgHead.wMsgLen != 0)
	{
		emImageAdjust = *reinterpret_cast<EmTPImageAdjust*>( cMsg.content + sizeof(EmTPImageAdjust) );
	}

	PrtRkcMsg( ev_TpCamImageAdjust_Nty, emEventTypeScoketRecv, "EmTPImageAdjust:%d", emImageAdjust);
	PostEvent( UI_MOONTOOL_IMAGE_ADJUST_NTY, (WPARAM)emImageAdjust, NULL );
}

void CSysConfig::OnEthnetInfoInd( const CMessage& cMsg )
{
	/*CTpMsg cTpMsg(&cMsg);	
	
    u8 uInst = cTpMsg.GetHomeplace();
	
    TTPEthnetInfo tEthnetInfo = *reinterpret_cast<TTPEthnetInfo*>(cTpMsg.GetBody());

	m_tEthnetInfo = tEthnetInfo;
	PostEvent( UI_MOONTOOL_ETHNETINFO_NOTIFY );
	
	in_addr tAddr;
	tAddr.S_un.S_addr = tEthnetInfo.dwIP;
	PrtMsg( ev_TpMoonCfgEthnet_Ind, emEventTypemoontoolRecv, "TTPEthnetInfo: Ip: %s, Inst: %d", inet_ntoa(tAddr), uInst );*/
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
		m_tEthnetInfo = *reinterpret_cast<TTPEthnetInfo*>( cMsg.content + sizeof(TTPEthnetInfo) );
	}
	m_tEthnetInfo.dwGateWay = ntohl(m_tEthnetInfo.dwGateWay);
	m_tEthnetInfo.dwIP = ntohl(m_tEthnetInfo.dwIP);
	m_tEthnetInfo.dwMask = ntohl(m_tEthnetInfo.dwMask);

	in_addr tAddr;
	tAddr.S_un.S_addr = m_tEthnetInfo.dwIP;
	PrtRkcMsg( ev_TpMoonCfgEthnet_Ind, emEventTypeScoketRecv, "TTPEthnetInfo: Ip: %s", inet_ntoa(tAddr));
	PostEvent( UI_MOONTOOL_ETHNETINFO_NOTIFY );
}

const TTPEthnetInfo& CSysConfig::GetEthnetCfg() const
{
	return m_tEthnetInfo;
}
 
u16 CSysConfig::SetOutPortTypeCmd( EmTPDVIOutPortType emDVIOutPortType, EmTPMOONOutMode emMOONOutMode )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&emDVIOutPortType, sizeof(EmTPDVIOutPortType));
	pcTpMsg->CatBody(&emMOONOutMode, sizeof(EmTPMOONOutMode));
	pcTpMsg->SetEvent(ev_TpCamOutPortInfo_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamOutPortInfo_Cmd, emEventTypemoontoolSend, "EmTPDVIOutPortType:%d,EmTPMOONOutMode:%d", emDVIOutPortType, emMOONOutMode );
	return wRet;*/
	TRK100MsgHead tRK100MsgHead;//定义消息头结构体
	memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
	//整型传数据集的转网络序
	tRK100MsgHead.dwEvent = htonl(ev_TpCamOutPortInfo_Cmd);
	tRK100MsgHead.wMsgLen = htons(sizeof(EmTPDVIOutPortType) + sizeof(EmTPMOONOutMode));
	CRkMessage rkmsg;//定义消息
	rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容
	rkmsg.CatBody(&emDVIOutPortType, sizeof(EmTPDVIOutPortType));//添加消息体
	rkmsg.CatBody(&emDVIOutPortType, sizeof(EmTPMOONOutMode));

	PrtRkcMsg( ev_TpCamOutPortInfo_Cmd, emEventTypeScoketSend ,"EmTPDVIOutPortType:%d,EmTPMOONOutMode:%d", emDVIOutPortType, emMOONOutMode);

	SOCKETWORK->SendDataPack(rkmsg);//消息发送
	return NOERROR;
}

void CSysConfig::OnCamOutputInfoInd( const CMessage& cMsg )
{
	/*CTpMsg cTpMsg(&cMsg);	
	
    u8 uInst = cTpMsg.GetHomeplace();
	
    EmTPDVIOutPortType emDVIOutPortType = *reinterpret_cast<EmTPDVIOutPortType*>(cTpMsg.GetBody());

	EmTPMOONOutMode	emMOONOutMode = *reinterpret_cast<EmTPMOONOutMode*>(cTpMsg.GetBody()+sizeof(EmTPDVIOutPortType));

	BOOL bOk = *(BOOL*)(cTpMsg.GetBody()+sizeof(EmTPDVIOutPortType)+sizeof(EmTPMOONOutMode));

	PrtMsg( ev_TpCamOutPortInfo_Ind, emEventTypemoontoolRecv, "EmTPDVIOutPortType:%d, EmTPMOONOutMode:%d, bOk:%d", emDVIOutPortType, emMOONOutMode, bOk );

	PostEvent( UI_MOONTOOL_CAMOUTPUT_INFO_IND, (WPARAM)emDVIOutPortType, (LPARAM)emMOONOutMode );*/

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

	EmTPDVIOutPortType emDVIOutPortType = TPMOON_DVI_MODE_INVALID;
	EmTPMOONOutMode emMOONOutMode  = em_MoonOutMode_Unknown;
	if (tMsgHead.wMsgLen != 0)
	{
		emDVIOutPortType = *reinterpret_cast<EmTPDVIOutPortType*>( cMsg.content + sizeof(EmTPDVIOutPortType) );
		emMOONOutMode = *reinterpret_cast<EmTPMOONOutMode*>( cMsg.content + sizeof(EmTPDVIOutPortType) + sizeof(EmTPMOONOutMode) );
	}

	PrtRkcMsg( ev_TpCamOutPortInfo_Ind, emEventTypeScoketRecv, "EmTPDVIOutPortType:%d, EmTPMOONOutMode:%d, bOk:%d", emDVIOutPortType, emMOONOutMode, tMsgHead.wOptRtn);
	PostEvent( UI_MOONTOOL_CAMOUTPUT_INFO_IND, (WPARAM)emDVIOutPortType, (LPARAM)emMOONOutMode );
}

u16 CSysConfig::SetImageAdjustCmd( EmTPImageAdjust emImageAdjust )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData(m_pSession->GetInst());
	pcTpMsg->SetBody(&emImageAdjust, sizeof(EmTPImageAdjust));
	pcTpMsg->SetEvent(ev_TpCamImageAdjust_Cmd);
	
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	PrtMsg( ev_TpCamImageAdjust_Cmd, emEventTypemoontoolSend, "EmTPImageAdjust:%d", emImageAdjust );
	return wRet;*/
	TRK100MsgHead tRK100MsgHead;//定义消息头结构体
	memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
	//整型传数据集的转网络序
	tRK100MsgHead.dwEvent = htonl(ev_TpCamImageAdjust_Cmd);
	tRK100MsgHead.wMsgLen = htons(sizeof(EmTPImageAdjust));
	CRkMessage rkmsg;//定义消息
	rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容
	rkmsg.CatBody(&emImageAdjust, sizeof(EmTPImageAdjust));//添加消息体

	PrtRkcMsg( ev_TpCamImageAdjust_Cmd, emEventTypeScoketSend ,"EmTPImageAdjust:%d", emImageAdjust);

	SOCKETWORK->SendDataPack(rkmsg);//消息发送
	return NOERROR;
}

void CSysConfig::OnCamImageAdjustInd( const CMessage& cMsg )
{
	/*CTpMsg cTpMsg(&cMsg);	
	
    u8 uInst = cTpMsg.GetHomeplace();
	
    EmTPImageAdjust emImageAdjust = *reinterpret_cast<EmTPImageAdjust*>(cTpMsg.GetBody());
	
	BOOL bOk = *(BOOL*)(cTpMsg.GetBody()+sizeof(EmTPImageAdjust));
	
	PrtMsg( ev_TpCamImageAdjust_Ind, emEventTypemoontoolRecv, "EmTPImageAdjust:%d, bOk:%d", emImageAdjust, bOk );
	
	PostEvent( UI_MOONTOOL_IMAGE_ADJUST_IND, (WPARAM)emImageAdjust, NULL );*/
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

	EmTPImageAdjust emImageAdjust = emClosed;
	if (tMsgHead.wMsgLen != 0)
	{
		emImageAdjust = *reinterpret_cast<EmTPImageAdjust*>( cMsg.content + sizeof(EmTPImageAdjust) );
	}

	PrtRkcMsg( ev_TpCamImageAdjust_Ind, emEventTypeScoketRecv, "EmTPImageAdjust:%d, bOk:%d", emImageAdjust, tMsgHead.wOptRtn);
	PostEvent( UI_MOONTOOL_IMAGE_ADJUST_IND, (WPARAM)emImageAdjust, NULL );
}

u16 CSysConfig::UpdateEthnetCfg( const TTPEthnetInfo& cfg )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetEvent( ev_TpMoonCfgEthnet_Cmd );
	pcTpMsg->SetBody( &cfg, sizeof(TTPEthnetInfo) );
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	
	in_addr tAddr;
	tAddr.S_un.S_addr = cfg.dwIP;
	PrtMsg( ev_TpMoonCfgEthnet_Cmd, emEventTypemoontoolSend, "MoonIP: %s", inet_ntoa(tAddr) );
	return wRet;*/
	TRK100MsgHead tRK100MsgHead;//定义消息头结构体
	memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
	//整型传数据集的转网络序
	tRK100MsgHead.dwEvent = htonl(ev_TpMoonCfgEthnet_Cmd);
	tRK100MsgHead.wMsgLen = htons(sizeof(TTPEthnetInfo));
	CRkMessage rkmsg;//定义消息
	rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容
	TTPEthnetInfo tTpEthnetInfo = cfg;
	tTpEthnetInfo.dwGateWay = htonl(cfg.dwGateWay);
	tTpEthnetInfo.dwIP = htonl(cfg.dwIP);
	tTpEthnetInfo.dwMask = htonl(cfg.dwMask);
	rkmsg.CatBody(&tTpEthnetInfo, sizeof(TTPEthnetInfo));//添加消息体

	in_addr tAddr;
	tAddr.S_un.S_addr = cfg.dwIP;
	PrtRkcMsg( ev_TpMoonCfgEthnet_Cmd, emEventTypeScoketSend , "MoonIP: %s", inet_ntoa(tAddr) );

	SOCKETWORK->SendDataPack(rkmsg);//消息发送
	return NOERROR;
}

u16 CSysConfig::SetBaudRateCmd( EmTPLVDSBaud emBaudRate )
{
	/*CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
	pcTpMsg->SetUserData( m_pSession->GetInst() );
	pcTpMsg->SetEvent( ev_TpSetLVDSBaud_Cmd );
	pcTpMsg->SetBody( &emBaudRate, sizeof(EmTPLVDSBaud) );
	u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);
	
	PrtMsg( ev_TpSetLVDSBaud_Cmd, emEventTypemoontoolSend, "emBaudRate: %d<em_LVDSBaud_9600bps: %d,\
 em_LVDSBaud_19200bps: %d, em_LVDSBaud_38400bps:%d, em_LVDSBaud_115200bps :%d>", emBaudRate,em_LVDSBaud_9600bps,
 em_LVDSBaud_19200bps,em_LVDSBaud_38400bps,em_LVDSBaud_115200bps);
	return wRet;*/
	TRK100MsgHead tRK100MsgHead;//定义消息头结构体
	memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
	//整型传数据集的转网络序
	tRK100MsgHead.dwEvent = htonl(ev_TpSetLVDSBaud_Cmd);
	tRK100MsgHead.wMsgLen = htons(sizeof(EmTPLVDSBaud));
	CRkMessage rkmsg;//定义消息
	rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//添加头内容
	rkmsg.CatBody(&emBaudRate, sizeof(EmTPLVDSBaud));//添加消息体

	PrtRkcMsg( ev_TpSetLVDSBaud_Cmd, emEventTypeScoketSend ,"emBaudRate: %d<em_LVDSBaud_9600bps: %d,\
 em_LVDSBaud_19200bps: %d, em_LVDSBaud_38400bps:%d, em_LVDSBaud_115200bps :%d>", emBaudRate,em_LVDSBaud_9600bps,
 em_LVDSBaud_19200bps,em_LVDSBaud_38400bps,em_LVDSBaud_115200bps);

	SOCKETWORK->SendDataPack(rkmsg);//消息发送
	return NOERROR;
}

void CSysConfig::OnLVDBaudInd( const CMessage& cMsg )
{
	/*CTpMsg cTpMsg(&cMsg);	
	
    EmTPLVDSBaud emTpBaudRate = *reinterpret_cast<EmTPLVDSBaud*>(cTpMsg.GetBody());
	
	BOOL bOk = *(BOOL*)(cTpMsg.GetBody()+sizeof(EmTPLVDSBaud));
	
	PrtMsg( ev_TpSetLVDSBaud_Ind, emEventTypemoontoolRecv, "EmTPLVDSBaud:%d, bOk:%d", emTpBaudRate, bOk );*/
	
//	PostEvent( UI_MOONTOOL_LVDSBAUD_IND, (WPARAM)&emTpBaudRate, (LPARAM)&bOk );
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

	EmTPLVDSBaud emTpBaudRate = em_LVDSBaud_Unknown;
	if (tMsgHead.wMsgLen != 0)
	{
		emTpBaudRate = *reinterpret_cast<EmTPLVDSBaud*>( cMsg.content + sizeof(EmTPLVDSBaud) );
	}

	PrtRkcMsg( ev_TpSetLVDSBaud_Ind, emEventTypeScoketRecv, "EmTPLVDSBaud:%d, bOk:%d", emTpBaudRate, tMsgHead.wOptRtn);
	//PostEvent( UI_MOONTOOL_LVDSBAUD_IND, (WPARAM)&emTpBaudRate, (LPARAM)&tMsgHead.wOptRtn );
}

void CSysConfig::OnLVDBaudNty( const CMessage& cMsg )
{
	/*CTpMsg cTpMsg(&cMsg);	
	
    EmTPLVDSBaud emTpBaudRate = *reinterpret_cast<EmTPLVDSBaud*>(cTpMsg.GetBody());
	BOOL bOk = TRUE;

	PrtMsg( ev_TpSetLVDSBaud_Nty, emEventTypemoontoolRecv, "EmTPLVDSBaud:%d", emTpBaudRate );*/
	
//	PostEvent( UI_MOONTOOL_LVDSBAUD_IND, (WPARAM)&emTpBaudRate, (LPARAM)&bOk );
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

	EmTPLVDSBaud emTpBaudRate = em_LVDSBaud_Unknown;
	if (tMsgHead.wMsgLen != 0)
	{
		emTpBaudRate = *reinterpret_cast<EmTPLVDSBaud*>( cMsg.content + sizeof(EmTPLVDSBaud) );
	}

	PrtRkcMsg( ev_TpSetLVDSBaud_Nty, emEventTypeScoketRecv, "EmTPLVDSBaud:%d", emTpBaudRate);
	//PostEvent( UI_MOONTOOL_LVDSBAUD_IND, (WPARAM)&emTpBaudRate, (LPARAM)&bOk );
}