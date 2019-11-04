/***************t300E网络抓包的公共文件 ******************/ 
#ifndef _NETCAPTURE_H_
#define _NETCAPTURE_H_ 

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define  KBIT_SIZE           (1<<10)
#define  MBIT_SIZE           (1<<20)
#define  GBIT_SIZE           (1<<30)

#define STC_CAPTURE_MES    64
#define EXPORT_FILE_NAME_LENGTH  128

#define TELNET_RCV_LINE_LEN  128
#define TELNET_RCV_BUF_LEN   1024
#define TELNET_CMD_LEN       64

#define DEFAULT_TELNET_PORT  23

#define TELNET_RCV_USER_T300e            "KEDACOM login:"
#define TELNET_RCV_PWD_T300e             "Password:"
#define TELNET_Rcv_OK_T300e              "~ #"
#define TELNET_RAMDISK_DIR_T300e         "/ramdisk"

typedef struct tagTRcvBuf{
	
	s8 m_achRcvBuf[TELNET_RCV_BUF_LEN+1];
	
	tagTRcvBuf()
	{
		Clear();
	}
	
	void Clear()
	{
		memset(this, 0, sizeof(tagTRcvBuf));
	}
	
	u16 GetBufSize()
	{
		return strlen(m_achRcvBuf);
	}
	
	void GetLastLineStr(s8* psztemp)
	{
		u16 wSize = strlen(m_achRcvBuf);
		if (0 == wSize)
			return;
		
		u16 wIndex;
		for (wIndex = wSize; wIndex > 0; wIndex--)
		{
			if (m_achRcvBuf[wIndex - 1] == 31 || m_achRcvBuf[wIndex - 1] == 13 || m_achRcvBuf[wIndex - 1] == 10)
			{
				break;
			}
		}
		
		if (wSize - wIndex > TELNET_RCV_LINE_LEN)
		{
			return;
		}
		
		memcpy(psztemp, &m_achRcvBuf[wIndex], wSize - wIndex);
		
		return;
	}
	
}TRcvBuf;


#endif //_NETCAPTURE_H_