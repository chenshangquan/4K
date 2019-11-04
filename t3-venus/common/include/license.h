// License.h: interface for the CLicense class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LICENSEMGR_H__FAE7BA24_0B89_44AB_BD75_73E9C5CF6D66__INCLUDED_)
#define AFX_LICENSEMGR_H__FAE7BA24_0B89_44AB_BD75_73E9C5CF6D66__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define LICENSE_LEN             25
#define LICENSE_RANDOM_LEN      19
#define LICENSE_VER_LEN         2


class CLicense  
{
public:
	CLicense();
	virtual ~CLicense();

public:
    // pbyVer要求输入两个数字（0-9），如10代表1.0版本
    static BOOL32 GenerateLicense( char *pbyRamdom, char *pbyVer, char *pbyLicense, int nLenBuf );

    static BOOL32 ValidateLicense( char *pbyLicense );

    static BOOL32 GetLicenseVer( char *pbyLicense, char *pbyVer, int nBufLen );

private:
    // 计算CRC校验码
    // *ptr指向发送缓冲区的首字节，len是要发送的总字节数。
    static unsigned short CalCRC(unsigned char *ptr, unsigned char len);

    // 将一个数值映射到字符
    static char Int2char( int val );

    // 将一个数值映射到字符串
    static int Char2int( char ch );

private:
    static const char *m_s_pMap2char;
};

#endif // !defined(AFX_LICENSEMGR_H__FAE7BA24_0B89_44AB_BD75_73E9C5CF6D66__INCLUDED_)
