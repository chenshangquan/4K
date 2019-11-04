/*=============================================================================
模   块   名: 网管公用模块库
文   件   名: calladdr.cpp
相 关  文 件: calladdr.h
文件实现功能: 呼叫终端地址的相关操作类
作        者: 李洪强
版        本: V4.0  Copyright(C) 2003-2006 KDC, All rights reserved.
-------------------------------------------------------------------------------
修改记录:
日      期  版本    修改人      修改内容
2004/07/16  3.0     李洪强      创建
2005/12/08  4.0     王昊        分离出单独文件
=============================================================================*/

#include "stdafx.h"
#include "calladdr.h"
#include <WINSOCK2.H>
#include "osp.h"
#include "vccommon.h"
#include "platform sdk/include/IPTypes.h"
#include "platform sdk/include/Ipexport.h"
#include <vector>


using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//u32 CCallAddr::s_dwError = CCallAddr::VALID_IPADDR;
CString CCallAddr::s_cstrIpStr;

static char g_szCallAddrErrDes[][2][256] =
    {
        "IP 地址无效：%d 不是一个有效项，请指定一个介于 1 和 223 之间的数值",
        "%d is not a valid entry. Please specify a value between 1 and 223.",

        "以 127 开头的 IP 地址无效，请指定介于 1 和 223 间的其他某个有效值",
        "IP address starting with 127 are not valid because they are reserved for loopback address. Please specify some other valid value between 1 and 223.",

        "无效 IP 地址和子网掩码合并",
        "The combination of IP address and subnet mask is invalid. All of the bits in the host address portion of the IP address are set to 0. Please enter a valid combination of IP address and subnet mask."
    };

/*=============================================================================
函 数 名:IsValidIpV4
功    能:检验IP地址是否有效
参    数:LPCTSTR lptrIPStr              [in]    字符串指针型的地址
注    意:无
返 回 值:合法返回TRUE,非法返回FALSE
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2004/09/13  3.5     李洪强  加注释
2005/08/31	4.0     刘瑞飞  根据王昊的算法修改
=============================================================================*/
BOOL32 CCallAddr::IsValidIpV4(LPCTSTR lptrIPStr)
{
    if ( lptrIPStr == NULL ) 
    {
//        s_dwError = ERROR_INPUTNULL;
        return FALSE;
    }

//    s_dwError = VALID_IPADDR;				//	置0
    s32 nDot    = 0;                        //  已处理的字符串里的点号数
    s32 nData   = 0;                        //  已处理的字符串里的数值
    s32 nPos	= 0;						//	两点之间的间隔
    s32 nLen    = _tcslen( lptrIPStr );     //  字符串长度

    //  字符串最少7位最长15位, 且不能以'0'开头
    if ( nLen < 7 || nLen > 15 ) 
    {
        // 2004/05/19 李洪强 *.*.*.*和***.***.***.***
//        s_dwError = ERROR_LEN;
        return FALSE;
    }

    if ( lptrIPStr[0] == '0'
         || ( lptrIPStr[0] == '2' && lptrIPStr[1] == '5'
              && lptrIPStr[2] == '5' ) )
    {
//        s_dwError = ERROR_ZERO_BEGIN;
        return FALSE;
    }

    if ( lptrIPStr[0] == '.' || lptrIPStr[nLen - 1] == '.' )
    {
//        s_dwError = ERROR_POINTSTART_OR_NOPONIT;
        return FALSE;
    }

    for ( s32 nCount = 0; nCount < nLen; ++nCount )
    {
        if ( lptrIPStr[nCount] >= '0' && lptrIPStr[nCount] <= '9' )//遇到数字
        {
            nData = 10 * nData + lptrIPStr[nCount] - '0';     //计算数值
		    ++nPos;
        }
        else if ( lptrIPStr[nCount] == '.' )     //  遇到点号
        {
            nDot++;
            if ( nDot > 3 )  //  点号数大于3
            {
//                s_dwError = ERROR_EXTRA_POINT;
			    return FALSE;
            }
		    else if ( nPos > 3 )
		    {
//			    s_dwError = ERROR_POINT_POS;
			    return FALSE;
		    }
		    else if ( nData > 255 ) //数值大于255
		    {
//			    s_dwError = ERROR_VALUE;
			    return FALSE;
		    }
            else        //  已处理的字符串合法
            {
                nData = 0;
			    nPos = 0;
            }
        }
        else            //  遇到非法字符
        {
//            s_dwError = ERROR_NOT_NUM_OR_POINT;
		    return FALSE;
        }
    }

    if ( nDot != 3 )
    {
//	    s_dwError = ERROR_POINT_POS;
	    return FALSE;
    }
    
    // 顾振华@2006.03.17 检查最后一个数字是否合法
    if ( nData > 255 ) //数值大于255
	{
//		s_dwError = ERROR_VALUE;
		return FALSE;
	}    

    return TRUE;
}

/*=============================================================================
函 数 名:IsValidIpV4
功    能:IP控件中的地址是否有效
参    数:CIPAddressCtrl *pcIpCtrl       [in]    IP控件的指针
注    意:无
返 回 值:合法返回TRUE,非法返回FALSE
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2004/09/13  3.5     李洪强  加注释
=============================================================================*/
BOOL32 CCallAddr::IsValidIpV4(CIPAddressCtrl *pcIpCtrl)
{
    ASSERT( pcIpCtrl != NULL );
    if ( pcIpCtrl == NULL ) 
    {
//        s_dwError = ERROR_INPUTNULL;
        return FALSE;
    }

    u8 byPos1 = 0;
    u8 byPos2 = 0;
    u8 byPos3 = 0;
    u8 byPos4 = 0;
    int nFileds = pcIpCtrl->GetAddress( byPos1, byPos2, byPos3, byPos4 );
    if ( nFileds < 4 )
    {
        return FALSE;
    }
    else if ( byPos1 == 0 || byPos1 == 255 )
    {
//        s_dwError = ERROR_ZERO_BEGIN;
        return FALSE;
    }
    else
    {
//        s_dwError = VALID_IPADDR;
        return TRUE;
    }
}

/*=============================================================================
函 数 名:IsValidIpV4
功    能:检验IP地址是否有效
参    数:u32 dwIP                       [in]    u32型的地址, 主机序
注    意:无
返 回 值:合法返回TRUE,非法返回FALSE
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2004/09/13  3.5     李洪强  加注释
=============================================================================*/
BOOL32 CCallAddr::IsValidIpV4(u32 dwIP)
{
    u8 byPos1 = HIBYTE( HIWORD( dwIP ) );
    if ( byPos1 == 0 || byPos1 == 255 )
    {
//        s_dwError = ERROR_ZERO_BEGIN;
        return FALSE;
    }
    else
    {
//        s_dwError = VALID_IPADDR;
        return TRUE;
    }
}

/*=============================================================================
函 数 名:IsValidIpMask
功    能:检验IP是否是合法的掩码
参    数:LPCTSTR lptrIpMask             [in]    LPCTSTR型IP地址字符串
注    意:无
返 回 值:合法返回TRUE,非法返回FALSE
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/08/31  4.0     刘瑞飞  创建
=============================================================================*/
BOOL32 CCallAddr::IsValidIpMask(LPCTSTR lptrIpMask)
{
	BOOL32 bRet = IsValidIpV4( lptrIpMask );
	if ( !bRet )
	{
		return FALSE;
	}

	u32 dwAddr = ntohl( inet_addr( lptrIpMask ) ); 
	bRet = IsValidIpMask( dwAddr );
	return bRet;
}

/*=============================================================================
函 数 名:IsValidIpMask
功    能:检验IP是否是合法的掩码
参    数:CIPAddressCtrl *pcIpCtrl   [in]    IP控件指针
注    意:无
返 回 值:合法返回TRUE,非法返回FALSE
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/12/08  4.0     王昊    创建
=============================================================================*/
BOOL32 CCallAddr::IsValidIpMask(CIPAddressCtrl *pcIpCtrl)
{
    ASSERT( pcIpCtrl != NULL );
    if ( pcIpCtrl == NULL ) 
    {
        return FALSE;
    }

    DWORD dwIpMask = 0;
    pcIpCtrl->GetAddress( dwIpMask );
	BOOL32 bRet = IsValidIpMask( dwIpMask );
	return bRet;
}

/*=============================================================================
函 数 名:IsValidIpMask
功    能:检验IP是否是合法的掩码
参    数:u32 dwIpMask                   [in]    u32型IP地址, 主机序
注    意:无
返 回 值:合法返回TRUE,非法返回FALSE
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/08/31  4.0     刘瑞飞  创建
=============================================================================*/
BOOL32 CCallAddr::IsValidIpMask(u32 dwIpMask)
{
	if ( dwIpMask == 0 )
	{
		return FALSE;
	}

	u32 dwTemp1 = ~dwIpMask;
	u32 dwTemp2 = dwIpMask - dwTemp1;
	return ( (dwTemp1 & dwTemp2) == 1 );
}

/*=============================================================================
函 数 名:IsValidE164
功    能:检验E164号是否有效
参    数:LPCTSTR lptrE164Str            [in]    E164号
注    意:无
返 回 值:合法返回TRUE,非法返回FALSE
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/05/26  3.6     王昊    创建
=============================================================================*/
BOOL32 CCallAddr::IsValidE164(LPCTSTR lptrE164Str)
{
    s32 nLen = _tcslen( lptrE164Str );
    if ( nLen == 0 )
    {
        return FALSE;
    }

    s32 nIndex = _tcsspn( lptrE164Str, _T("0123456789*,") );

    return (nLen == nIndex) ? TRUE : FALSE;
}

/*=============================================================================
函 数 名:IsValidH320ID
功    能:检验H320 ID是否有效
参    数:LPCTSTR lptrH320ID             [in]    LPCTSTR型H320 ID
注    意:无
返 回 值:合法返回TRUE,非法返回FALSE
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/07/04  3.6     王昊    创建
=============================================================================*/
BOOL32 CCallAddr::IsValidH320ID(LPCTSTR lptrH320ID)
{
    TMtAlias tMtAlias;
    u8 byLayer = 0;
    u8 bySlot = 0;
    u8 byChannel = 0;

    tMtAlias.m_AliasType = mtAliasTypeH320ID;
    _tcscpy( tMtAlias.m_achAlias, lptrH320ID );
    BOOL32 bRet = tMtAlias.GetH320Alias( byLayer, bySlot, byChannel );
    if ( !bRet )
    {
        return FALSE;
    }

    tMtAlias.SetH320Alias( byLayer, bySlot, byChannel );
    bRet = ( _tcscmp( tMtAlias.m_achAlias, lptrH320ID ) == 0 );

    return bRet;
}

/*=============================================================================
函 数 名:GetIpStr
功    能:得到IP地址的字串
参    数:u32 dwIPAddr                   [in]    IP地址, 主机序
注    意:无
返 回 值:IP地址的字串
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2004/09/13  3.5     李洪强  加注释
2005/10/26  4.0     王昊    取消使用inet_ntoa
=============================================================================*/
CString CCallAddr::GetIpStr(u32 dwIPAddr)
{
    u16 wHigh   = HIWORD( dwIPAddr );
    u16 wLow    = LOWORD( dwIPAddr );
    s_cstrIpStr.Format( _T("%d.%d.%d.%d"), HIBYTE( wHigh ), LOBYTE( wHigh ),
                        HIBYTE( wLow ), LOBYTE( wLow ) );
    return s_cstrIpStr;
}

s8 * CCallAddr::GetIpStr2(u32 dwIPAddr)
{
    dwIPAddr = htonl(dwIPAddr);
    static char strIP[17];  
    u8 *p = (u8 *)&dwIPAddr;
    sprintf(strIP,"%d.%d.%d.%d%c",p[0],p[1],p[2],p[3],0);
	return strIP;
}

/*=============================================================================
函 数 名:GetCallStrType
功    能:得到呼叫字符串类型
参    数:const CString &csCallAddr      [in]    呼叫的字符串
注    意:无
返 回 值:呼叫类型           NORMAL_STR 一般字串
                            IP_STR      IP字串
                            NUM164_STR  E164号码
                            H323ID_STR  H323ID
                            H320ID_STR  H320ID
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2004/09/13  3.5   李洪强  加注释
2005/07/04  3.6   王昊    加入H320 ID
=============================================================================*/
UINT CCallAddr::GetCallStrType(const CString &csCallAddr)
{
    if ( IsValidIpV4( csCallAddr ) )	
	{
		return IP_STR;
	}

    if ( IsValidE164( csCallAddr ) )
    {
        return NUM164_STR;
    }

	if ( csCallAddr.IsEmpty() )
	{
		return NORMAL_STR;
	}

    if ( IsValidH320ID( csCallAddr ) )
    {
        return H320ID_STR;
    }

	if ( csCallAddr.GetLength() >= MAXLEN_ALIAS )   //  wanghao 2004/10/26
	{
		return NORMAL_STR;
	}
	else
	{
		return H323ID_STR;
	}
}

typedef DWORD (WINAPI *GETADAPTERSINFO)(PIP_ADAPTER_INFO pAdapterInfo, PULONG pOutBufLen);
typedef DWORD (WINAPI *GETUNIDIRECTIONALADAPTERSINFO)(PIP_UNIDIRECTIONAL_ADAPTER_ADDRESS pIPIfInfo, PULONG dwOutBufLen);

/*=============================================================================
函 数 名:GetLocalIpAddr
功    能:获取所有本机IP地址, 不包括127.0.0.1
参    数:u32 *&pdwLocalIp               [out]   本机IP地址数组, 主机序
         s32 &nIpNum                    [out]   数组个数
注    意:本函数会分配pdwLocalIp空间, 请在调用完毕delete 分配的空间
         调用举例:
             u32 *pdwLocalIp = NULL;
             s32 nIpNum = 0;
             CCallAddr::GetLocalIpAddr( pdwLocalIp, nIpNum );
             DEL_PTR_ARRAY( pdwLocalIp );

         返回的IP为主机序
返 回 值:是否获取成功
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/10/29  4.0   王昊    创建
2007/05/09  4.0   王廖荣  修改
=============================================================================*/
BOOL32 CCallAddr::GetLocalIpAddr(u32 *&pdwLocalIp, s32 &nIpNum)
{/*
    nIpNum = 0;

    s8 aszHostName[128] = {0};
    s32 nRet = gethostname( aszHostName, 128 );
    if ( nRet == 0 )
    {
        struct hostent *ptHost = gethostbyname( aszHostName );
        for ( nIpNum = 0; ptHost->h_addr_list[nIpNum] != NULL; nIpNum ++ );

        pdwLocalIp = new u32 [nIpNum];
        for ( s32 nIndex = 0; nIndex < nIpNum; nIndex ++ )
        {
            pdwLocalIp[nIndex]
                = ((struct in_addr *)ptHost->h_addr_list[nIndex])->s_addr;
            pdwLocalIp[nIndex] = ntohl( pdwLocalIp[nIndex] );
        }

        return TRUE;
    }
    else
    {
        return FALSE;
    }
    */

    GETADAPTERSINFO GetAdaptersInfo = NULL;
    GETUNIDIRECTIONALADAPTERSINFO GetUniDirectionalAdapterInfo = NULL;

    HMODULE hModule = LoadLibrary("Iphlpapi.dll");
    if ( NULL == hModule )
    {
        return FALSE;
    }

    GetAdaptersInfo = (GETADAPTERSINFO)GetProcAddress( hModule, "GetAdaptersInfo" );
    GetUniDirectionalAdapterInfo = (GETUNIDIRECTIONALADAPTERSINFO)GetProcAddress( hModule, "GetUniDirectionalAdapterInfo" );
    if ( NULL == GetAdaptersInfo || NULL == GetUniDirectionalAdapterInfo )
    {
        FreeLibrary( hModule );
        return FALSE;
    }

    IP_ADAPTER_INFO *pAdptInfo = NULL;
    IP_ADAPTER_INFO *pNextAd = NULL;
    PIP_UNIDIRECTIONAL_ADAPTER_ADDRESS ptIPIfInfo = NULL;
    ULONG ulLen = 0;
    DWORD dwRet = 0;

    dwRet = GetAdaptersInfo( pAdptInfo, &ulLen );
    if ( dwRet == ERROR_BUFFER_OVERFLOW )
    {
        pAdptInfo = reinterpret_cast<IP_ADAPTER_INFO*>(new u8[ulLen]);
        dwRet = GetAdaptersInfo( pAdptInfo, &ulLen );
    }
    u8 pbyBuf[4096] = {0};
    ulLen = 4096;
    memset( pbyBuf, 0, sizeof (pbyBuf) );
    ptIPIfInfo = reinterpret_cast<PIP_UNIDIRECTIONAL_ADAPTER_ADDRESS>(pbyBuf);
    GetUniDirectionalAdapterInfo( ptIPIfInfo, &ulLen );


    //1. 获取所有网卡信息
    vector<u32> vctIP;
    if ( dwRet == ERROR_SUCCESS )
    {
        // 取网卡信息
        pNextAd = pAdptInfo;

        // 遍历各个网卡
        while ( pNextAd != NULL )
        {
            IP_ADDR_STRING *pIPStr = &(pNextAd->IpAddressList);
            if ( pNextAd->DhcpEnabled > 0 )
            {
                pIPStr = &(pNextAd->DhcpServer);
            }
            // 遍历各个网卡的所有IP
            while ( pIPStr != NULL )
            {
                LPCSTR lptrIpAddr = pIPStr->IpAddress.Str;
                vctIP.push_back( inet_addr( lptrIpAddr ) );
                pIPStr = pIPStr->Next;
            }
            pNextAd = pNextAd->Next;
        }
    }

    FreeLibrary( hModule );
    hModule = NULL;

    //2. 排除只接受不发送的IP
    for ( ulLen = 0; ulLen < ptIPIfInfo->NumAdapters; ulLen ++ )
    {
        vector<u32>::iterator itr = vctIP.begin();
        vector<u32>::iterator itrEnd = vctIP.end();
        for ( ; itr < itrEnd; itr ++ )
        {
            if ( (*itr) == ntohl( ptIPIfInfo->Address[ulLen] ) )
            {
                vctIP.erase( itr );
                break;
            }
        }
    }


    //3. 排除127.0.0.1
    vector<u32>::iterator itr = vctIP.begin();
    vector<u32>::iterator itrEnd = vctIP.end();
    while ( itr < itrEnd )
    {
        if ( (*itr) == 0 || (*itr) == 0x0100007F )
        {
            itr = vctIP.erase( itr );
            itrEnd = vctIP.end();
        }
        else
        {
            itr ++;
        }
    }


    //4. 赋值
    nIpNum = vctIP.size();
    if ( nIpNum > 0 )
    {
        pdwLocalIp = new u32 [nIpNum];
    }
    else
    {
        pdwLocalIp = NULL;
    }

    s32 nIndex = 0;
    while ( nIndex < nIpNum )
    {
        pdwLocalIp[nIndex] = ntohl( vctIP[nIndex] );
        nIndex++;
    }

    delete [] (u8*)pAdptInfo;

    return TRUE;
}

/*=============================================================================
函 数 名:GetLastErrorInfo
功    能:得到错误的原因
参    数:CString &csErrorInfo           [out]   错误的描述
注    意:中文字符串, 不考虑双语
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2004/09/13  3.5   李洪强  加注释
=============================================================================*/
//void CCallAddr::GetLastErrorInfo(CString &csErrorInfo)
//{
//    static TCHAR *lppError[] = 
//    {
//        _T("合法的IP地址"),
//        _T("输入字串为空"),
//        _T("IP地址长度非法"),
//        _T("IP地址以0开头"),
//        _T("IP地址没有分隔点或以点开头"),
//        _T("IP地址含有非法字符"),
//        _T("IP地址分隔点位置不正确"),
//        _T("IP地址含有多余的分隔符"),
//        _T("IP地址超范围")
//    };
//    csErrorInfo = lppError[s_dwError];
//}

/*=============================================================================
函 数 名: IsValidCallIP
功    能: 判断IP地址是否为合法呼叫IP
参    数: u32 dwIP                          [in]    主机序IP地址
注    意: 输入IP地址必须为IsValidIpV4判断出来的合法地址，
          在GetCallStrType之后使用
返 回 值: BOOL
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2007/04/25  1.0     王昊    创建
=============================================================================*/
BOOL32 CCallAddr::IsValidCallIP(u32 dwIP)
{
    u8 byFirstField = static_cast<u8>( dwIP >> 24 );
    if ( byFirstField >= 1 && byFirstField <= 223 && byFirstField != 127 )
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/*=============================================================================
函 数 名: IsValidCallIP
功    能: 判断IP地址是否为合法呼叫IP
参    数: u32 dwIP                          [in]    主机序IP地址
          CString &cstrErrStr               [out]   错误描述字符串
          u8 byLanType                      [in]    错误描述语言类型(0: 简体中文; 1: 英文)
注    意: 输入IP地址必须为IsValidIpV4判断出来的合法地址，
          在GetCallStrType之后使用
返 回 值: BOOL
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2007/04/25  1.0     王昊    创建
=============================================================================*/
BOOL32 CCallAddr::IsValidCallIP(u32 dwIP, CString &cstrErrStr,
                                u8 byLanType)
{
    if ( byLanType > 1 )
    {
        byLanType = 1;
    }

    BOOL32 bRet = FALSE;
    u8 byFirstField = static_cast<u8>( dwIP >> 24 );
    do
    {
        if ( byFirstField == 127 )
        {
            cstrErrStr = g_szCallAddrErrDes[1][byLanType];
            break;
        }
    	else if ( byFirstField == 0 || byFirstField > 223 )
        {
            //cstrErrStr = g_szCallAddrErrDes[0][byLanType];
			cstrErrStr.Format( g_szCallAddrErrDes[0][byLanType], byFirstField );
            break;
        }

        bRet = TRUE;

    } while ( FALSE );


    return bRet;
}

/*=============================================================================
函 数 名: IsValidMulticastIP
功    能: 判断IP地址是否为合法组播IP
参    数: u32 dwIP                          [in]    主机序IP地址
注    意: 输入IP地址必须为IsValidIpV4判断出来的合法地址
返 回 值: BOOL
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2007/04/25  1.0     王昊    创建
=============================================================================*/
BOOL32 CCallAddr::IsValidMulticastIP(u32 dwIP)
{
    u8 byFirstField = static_cast<u8>( dwIP >> 24 );
    if (    ( byFirstField >= 225 && byFirstField <= 231 )
         || ( byFirstField >= 233 && byFirstField <= 239 ) )
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/*=============================================================================
函 数 名: IsValidDevIP
功    能: 判断IP地址是否为合法设备IP(检验设备配置IP地址)
参    数: u32 dwIP                          [in]    主机序设备IP地址
          u32 dwMask                        [in]    主机序掩码
          CString &cstrErrStr               [out]   错误描述字符串
          u8 byLanType                      [in]    错误描述语言类型(0: 简体中文; 1: 英文)
注    意: 设备IP地址必须为IsValidIpV4判断出来的合法地址，
          掩码必须为IsValidIpMask判断出来的合法掩码
返 回 值: BOOL
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2007/04/25  1.0     王昊    创建
=============================================================================*/
BOOL32 CCallAddr::IsValidDevIP(u32 dwIP, u32 dwMask, CString &cstrErrStr,
                               u8 byLanType)
{
    if ( byLanType > 1 )
    {
        byLanType = 1;
    }

    BOOL32 bRet = FALSE;
    u8 byFirstField = static_cast<u8>( dwIP >> 24 );
    do
    {
        if ( byFirstField == 127 )
        {
            cstrErrStr = g_szCallAddrErrDes[1][byLanType];
            break;
        }
    	else if ( byFirstField == 0 || byFirstField > 223 )
        {
            //cstrErrStr = g_szCallAddrErrDes[0][byLanType];
			cstrErrStr.Format( g_szCallAddrErrDes[0][byLanType], byFirstField );
            break;
        }
        else
        {
            u32 dwTemp = dwIP & ( ~ dwMask );
            if ( dwTemp == dwMask || dwTemp == 0 )
            {
                cstrErrStr = g_szCallAddrErrDes[2][byLanType];
                break;
            }
			
			//增加效验，原效验不全面
			if ( !IsValidIpCombineMask( dwIP, dwMask ) )
			{
				cstrErrStr = g_szCallAddrErrDes[2][byLanType];
				break;
			}
        }

        bRet = TRUE;

    } while ( FALSE );


    return bRet;
}

const u32 IP_BITE_NUMBERS = 32; //IP地址二进制位数
/*=============================================================================
函 数 名: IsValidIpCombineMask
功    能: 判断IP地址和子网掩码的组合是否有效
参    数: u32 dwIP                          [in]    主机序设备IP地址
          u32 dwMask                        [in]    主机序掩码
注    意: 设备IP地址必须为IsValidIpV4判断出来的合法地址，
          掩码必须为IsValidIpMask判断出来的合法掩码
返 回 值: BOOL
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2011/12/29  1.0     肖楚然    添加
=============================================================================*/
BOOL32 CCallAddr::IsValidIpCombineMask(u32 dwIP, u32 dwMask)
{
	u32 dwNetAddr = 0;    //网络地址
	u32 dwBroadAddr = 0;  //广播地址
	
	dwNetAddr = dwIP & dwMask; 
	if( dwNetAddr == dwIP )
	{
		return FALSE;
	}
	
	//主机地址位数, IP_BITE_NUMBERS表示IP地址总位数(32)
	u32 dwIndex;         
	u32 dwAmount = 1;
	
	//计算子网掩码的二进制形式中第几位开始变成0，从而得出主机地址的位数
	u32 dwBitCount = dwMask ^ 0xFFFFFFFF;  
	u32 dwTemp = 1;
	
	for( int j = 0; j < IP_BITE_NUMBERS; j ++ )
	{
		if (dwBitCount < dwTemp)
		{
			dwIndex = j;
			break;
		}
		else if ( dwBitCount == dwTemp )
		{
			dwIndex = j + 1;
			break;
		}
		dwTemp = dwTemp * 2;
	}
	
	for( int k = 0; k < dwIndex; k ++ )
	{
		dwAmount = dwAmount * 2;
	}
	
	dwAmount = dwAmount - 1;
	dwBroadAddr = dwNetAddr | dwAmount; 
	
	if ( dwBroadAddr == dwIP )
	{
		return FALSE;
	}
	return TRUE;
}