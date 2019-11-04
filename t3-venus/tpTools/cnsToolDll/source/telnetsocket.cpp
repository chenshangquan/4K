// telnetsocket.cpp: implementation of the CTelnetSocket class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "telnetsocket.h"


CTelnetSocket::CTelnetSocket()
{
	m_nLoginNum = 0;
	m_nCdRamdiskNum = 0;
	m_nCmdStartNum = 0;
	m_pRcvBuf = new TRcvBuf;
}

CTelnetSocket::~CTelnetSocket()
{
	if (NULL != m_pRcvBuf)
	{
		delete m_pRcvBuf;
		m_pRcvBuf = NULL;
	}
}

void CTelnetSocket::SetLoginInfo(TLoginInfo& tInfo)
{
	memcpy(&m_tLoginInfo, &tInfo, sizeof(tInfo));
}

s8* CTelnetSocket::GetRcvBuf()
{
	return m_pRcvBuf->m_achRcvBuf;
}

void CTelnetSocket::ConnectRemote()
{
	CString strIpAddr = UIDATAMGR_PTR->GetIpStr( m_tLoginInfo.dwIp );
	BOOL bRet = Connect(strIpAddr, DEFAULT_TELNET_PORT);
	PrtMsg("CTelnetSocket::ConnectRemote Ip:%s, ret:%d \n", strIpAddr, bRet);
}

void CTelnetSocket::Close()
{
	if (NULL != m_pRcvBuf)
	{
		m_pRcvBuf->Clear();
	}
	m_nLoginNum = 0;
	m_nCdRamdiskNum = 0;
	m_nCmdStartNum = 0;
	CAsyncSocket::Close();
}

void CTelnetSocket::OnClose(int nErrorCode)
{
	CAsyncSocket::OnClose(nErrorCode);
	PrtMsg("CTelnetSocket::OnClose [%d]\n", nErrorCode);
}

void CTelnetSocket::OnConnect(int nErrorCode)
{
	CAsyncSocket::OnConnect(nErrorCode);
	PrtMsg("CTelnetSocket::OnConnect [%d]\n", nErrorCode);
}

void CTelnetSocket::OnOutOfBandData(int nErrorCode)
{
	CAsyncSocket::OnOutOfBandData(nErrorCode);
	PrtMsg("CTelnetSocket::OnOutOfBandData [%d]\n", nErrorCode);
}

void CTelnetSocket::OnReceive(int nErrorCode)
{
	CAsyncSocket::OnReceive(nErrorCode);

	if(0 != nErrorCode)
	{
		return;
	}

	if(NULL == m_pRcvBuf)
	{
		return;
	}

	m_pRcvBuf->Clear();

	int nBytes = Receive(m_pRcvBuf->m_achRcvBuf, TELNET_RCV_BUF_LEN);

	PrtMsg("CTelnetSocket::OnReceive ProcessMessage data:%s, size:%d, Res:%d\n", 
 		m_pRcvBuf->m_achRcvBuf, m_pRcvBuf->GetBufSize(), nBytes);

	s8 ach[TELNET_RCV_LINE_LEN + 1] = {0};

	m_pRcvBuf->GetLastLineStr(ach);
	Trim(ach);

	PrtMsg("CTelnetSocket::OnReceive Last data:%s, len:%d.\n", ach, strlen(ach));

	if (0 == strlen(ach))
	{
		return;
	}

	OnReceiveMsgFromT300e(ach);
}

void CTelnetSocket::OnSend(int nErrorCode)
{
	CAsyncSocket::OnSend(nErrorCode);
	PrtMsg("CTelnetSocket::OnSend [%d] \n", nErrorCode);
}

void CTelnetSocket::OnReceiveMsgFromT300e(s8* ach)
{
	s8 acmd[TELNET_CMD_LEN + 1] = {0};

	EmCnModel emCnModel;
	LIBDATAMGRPTR->GetEmCnModelInfo( &emCnModel );

	TTPTelnetInfo tTPTelnetInfo;
	LIBDATAMGRPTR->GetTelnetInfo(tTPTelnetInfo);

	TTPFtpInfo tTPFtpInfo;
	LIBDATAMGRPTR->GetFtpInfo(tTPFtpInfo);
	
	if (0 == strncmp(ach, TELNET_RCV_USER_T300e, strlen(TELNET_RCV_USER_T300e)))
	{		
		if (0 == m_nLoginNum)
		{
			if( LIBDATAMGRPTR->CheckVerNew() == false)
			{
				if( (emCnModel == T300) || (emCnModel == T300E ) || ( emCnModel == em7920 ) )
				{
					_snprintf(acmd, TELNET_CMD_LEN, "%s\r\n", FTP_CONNECT_USER);
				}
				else
				{
					_snprintf(acmd, TELNET_CMD_LEN, "%s\r\n", T300E_TEL_USRNAME);
				}				
			}
			else
			{
				if(tTPTelnetInfo.bOpen)
				{
					_snprintf(acmd, TELNET_CMD_LEN, "%s\r\n", tTPFtpInfo.achUserName );
				}
				else
				{
					_snprintf(acmd, TELNET_CMD_LEN, "%s\r\n", "" );
				}				
			}
			
			Send(acmd, strlen(acmd));
			
			m_nLoginNum++;
		}
	}
	else if(0 == strncmp(ach, TELNET_RCV_PWD_T300e, strlen(TELNET_RCV_PWD_T300e)))
	{
		if (1 == m_nLoginNum)
		{
			if( LIBDATAMGRPTR->CheckVerNew() == false)
			{
				if( (emCnModel == T300) || (emCnModel == T300E ) || ( emCnModel == em7920 ) )
				{
					_snprintf(acmd, TELNET_CMD_LEN, "%s\r\n",  FTP_CONNECT_PSWD );
				}
				else
				{
					_snprintf(acmd, TELNET_CMD_LEN, "%s\r\n",  T300E_TEL_PWD );
				}
				
			}
			else
			{
				if(tTPTelnetInfo.bOpen)
				{
					_snprintf(acmd, TELNET_CMD_LEN, "%s\r\n", tTPFtpInfo.achPassword );
				}
				else
				{
					_snprintf(acmd, TELNET_CMD_LEN, "%s\r\n", "" );
				}	
			}

			Send(acmd, strlen(acmd));
			
			m_nLoginNum++;
		}
	}
	else if(0 == strncmp(ach, TELNET_Rcv_OK_T300e, strlen(TELNET_Rcv_OK_T300e)))
	{
		if (0 == m_nCdRamdiskNum)
		{
			s8 achsend[]="cd /ramdisk\r\n chmod 777 *\r\n";			
			Send(achsend, strlen(achsend));
			
			m_nCdRamdiskNum++;
		}
	}
	else if(0 == strncmp(ach, TELNET_RAMDISK_DIR_T300e, strlen(TELNET_RAMDISK_DIR_T300e)))
	{
		if (0 == m_nCmdStartNum)
		{	
			_snprintf(acmd, TELNET_CMD_LEN, "./%s -w %s -s 1800\r\n", CNS_T300E_TUMP_NAME, CAPTURE_FILE_NAME);
			Send(acmd, strlen(acmd));
			
			m_nCmdStartNum++;
		}
	}
	else
	{
		PrtMsg("CTelnetSocket::OnReceiveMsgFromT300e Unknow buf:%s,%d\n", ach, strlen(ach));
	}
	
	return;
}


