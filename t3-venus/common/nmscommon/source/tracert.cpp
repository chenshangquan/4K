/*=============================================================================
模   块   名: 无
文   件   名: TraceRT.cpp
相 关  文 件: TraceRT.h
文件实现功能: tracert功能
作        者: 王昊
版        本: V4.0  Copyright(C) 2003-2006 Kedacom, All rights reserved.
-------------------------------------------------------------------------------
修改记录:
日      期  版本    修改人      修改内容
2006/06/06  4.0     王昊        创建
=============================================================================*/

#include "stdafx.h"
#include "icmpstruct.h"
#include "tracert.h"

#ifdef WIN32
#include <ws2tcpip.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif  //  _DEBUG
#endif  //  WIN32

#define TRACERT_PACKSIZE        (s32)64     //定死发送包长为64字节

CTraceRoute::CTraceRoute() : m_dwHostIP(0), m_pfnResult(NULL), m_pcbData(NULL)
{
}

CTraceRoute::~CTraceRoute()
{
}

/*=============================================================================
函 数 名:SetParam
功    能:设置参数
参    数:u32 dwHostIP                   [in]    对端IP地址(主机序)
         PFNTraceRTResult pfnResult     [in]    回调函数
         void *pcbData                  [in]    回调数据
注    意:无
返 回 值:参数检查结果
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2006/06/06  4.0     王昊    创建
=============================================================================*/
BOOL32 CTraceRoute::SetParam(u32 dwHostIP, PFNTraceRTResult pfnResult,
                             void *pcbData)
{
    if ( ! CheckParam( dwHostIP, pfnResult ) )
    {
        return FALSE;
    }

    m_dwHostIP = dwHostIP;
    m_pfnResult = pfnResult;
    m_pcbData = pcbData;

    return TRUE;
}

/*=============================================================================
函 数 名:Start
功    能:开始测试
参    数:无
注    意:无
返 回 值:成功: TRUE; 失败: FALSE
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2006/06/06  4.0     王昊    创建
=============================================================================*/
BOOL32 CTraceRoute::Start(void)
{
    BOOL32 bStop = FALSE;
    if ( ! CheckParam(m_dwHostIP, m_pfnResult) )
    {
        return FALSE;
    }

    sockaddr_in tDst = {0},tSrc;
    tDst.sin_family = AF_INET;
    tDst.sin_port = 0;
    tDst.sin_addr.s_addr = htonl( m_dwHostIP );

    for ( s32 nIndex = 0; nIndex < MAX_GW_NUM; nIndex ++ )
    {
        u32 dwGWIPAddr = 0;
        TTraceRtRst tTraceRst;

        for ( s32 nTestIdx = 0; nTestIdx < TEST_PER_GW; nTestIdx ++ )
        {
            SOCKET s = socket( AF_INET, SOCK_RAW, IPPROTO_ICMP );
            if ( s == INVALID_SOCKET )
            {
                s = NULL;
                tTraceRst.m_byTraceRt = emTraceRtUnreachable;
                m_pfnResult( m_pcbData, tTraceRst );
                return FALSE;
            }

            u32 dwSendTime = GetTickCount();
            BOOL32 bRet = SendReq( s, static_cast<u16>(nIndex) + 1 );
            if ( ! bRet )
            {
                closesocket( s );
                s = NULL;
                tTraceRst.m_byTraceRt = emTraceRtUnreachable;
                m_pfnResult( m_pcbData, tTraceRst );
                return FALSE;
            }


			struct timeval tTimeVal;
			tTimeVal.tv_sec = 4 ; 
			tTimeVal.tv_usec=0 ;

			fd_set  readSet;
			FD_ZERO(&readSet);
			FD_SET(s,&readSet);
			if (select(0,&readSet,NULL,NULL,&tTimeVal)==0)
			{
				closesocket( s );
				if (nTestIdx+1==TEST_PER_GW)
				{
					tTraceRst.m_byTraceRt = emTraceRtUnreachable;
					m_pfnResult( m_pcbData, tTraceRst );
					return FALSE;
				}
				else
				{
					continue;
				}
				
			}

            IICMPMsg tRcvMsg;
            int nFromLen = sizeof (tSrc);
            int nRet = recvfrom( s, reinterpret_cast<s8*>(&tRcvMsg),
                                 sizeof (tRcvMsg), 0,
                                 reinterpret_cast<SOCKADDR*>(&tSrc),
                                 &nFromLen );
            u32 dwEchoTime = GetTickCount();
            if ( nRet == SOCKET_ERROR )     //接收错误, 认为是对端不可及
            {
                closesocket( s );
                s = NULL;
                tTraceRst.m_byTraceRt = emTraceRtUnreachable;
                m_pfnResult( m_pcbData, tTraceRst );
                return FALSE;
            }

            switch ( tRcvMsg.m_tIPHdr.GetType() )
            {
            case emDstUnreachable:
//                if ( tRcvMsg.m_tIPHdr.GetCode() == emUnreachHost )   //对端不可及
//                {
                    closesocket( s );
                    s = NULL;
                    tTraceRst.m_byTraceRt = emTraceRtUnreachable;
                    m_pfnResult( m_pcbData, tTraceRst );
                    return FALSE;
//                }
//                else        //  端口无响应, 收完所有不可及消息, 通知上层, 并继续
//                {
//                    while ( nTestIdx < MAX_GW_NUM )
//                    {
//                        recvfrom( s, reinterpret_cast<s8*>(&tRcvMsg),
//                                  sizeof (tRcvMsg), 0,
//                                  reinterpret_cast<SOCKADDR*>(&tDst),
//                                  &nFromLen );
//                        nTestIdx ++;
//                    }
//                    tTraceRst.m_byTraceRt = emTraceRtGW;
//                    tTraceRst.m_dwGWIP = tRcvMsg.m_tIPHdr.m_tIPHdr.GetSrcIPAddr();
//                    bStop = ! m_pfnResult( m_pcbData, tTraceRst );
//                    if ( bStop )
//                    {
//                        closesocket( s );
//                        s = NULL;
//                        return FALSE;
//                    }
//                }
                break;
            case emTimeExceeded:
                dwGWIPAddr = tRcvMsg.m_tIPHdr.m_tIPHdr.GetSrcIPAddr();
                closesocket( s );
                s = NULL;
                tTraceRst.m_byTraceRt = emTraceRtEcho;
                tTraceRst.m_dwEchoTime = dwEchoTime - dwSendTime;
                bStop = ! m_pfnResult( m_pcbData, tTraceRst );
                if ( bStop )
                {
                    return FALSE;
                }
                break;
            case emEchoReply:
                closesocket( s );
                s = NULL;
                tTraceRst.m_byTraceRt = emTraceRtEnd;
                m_pfnResult( m_pcbData, tTraceRst );
                return TRUE;
            default:
                tTraceRst.m_byTraceRt = emTraceRtOtherMsg;
                bStop = ! m_pfnResult( m_pcbData, tTraceRst );
                if ( bStop )
                {
                    closesocket( s );
                    s = NULL;
                    return FALSE;
                }
                break;
            }
        }

        if ( dwGWIPAddr > 0 )
        {
            tTraceRst.m_byTraceRt = emTraceRtGW;
            tTraceRst.m_dwGWIP = dwGWIPAddr;
            bStop = ! m_pfnResult( m_pcbData, tTraceRst );
        }
    }

    return FALSE;
}

/*=============================================================================
函 数 名:CheckParam
功    能:检查参数
参    数:u32 dwHostIP                   [in]    对端IP地址(主机序)
         PFNTraceRTResult pfnResult     [in]    回调函数
注    意:无
返 回 值:参数合法: TRUE; 参数非法: FALSE
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2006/06/06  4.0     王昊    创建
=============================================================================*/
BOOL32 CTraceRoute::CheckParam(u32 dwHostIP, PFNTraceRTResult pfnResult)
{
    if ( pfnResult != NULL )
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/*=============================================================================
函 数 名:SendReq
功    能:发送请求
参    数:SOCKET s                       [in]    socket
         u16 wSN                        [in]    序列号
注    意:无
返 回 值:发送成功: TRUE; 发送失败: FALSE
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2006/06/06  4.0     王昊    创建
=============================================================================*/
BOOL32 CTraceRoute::SendReq(SOCKET s, u16 wSN)
{
    sockaddr_in tDst = {0};
    tDst.sin_family = AF_INET;
    tDst.sin_port = 0;
    tDst.sin_addr.s_addr = htonl( m_dwHostIP );

    s32 nTTL = static_cast<s32>(wSN);
    int nRet = setsockopt( s, IPPROTO_IP, IP_TTL, reinterpret_cast<s8*>(&nTTL),
                           sizeof (nTTL) );
    if ( nRet ==  SOCKET_ERROR )    //设置socket生存时间失败, 认为对端不可及
    {
        return FALSE;
    }

    IIcmpSendMsg tIcmpReq;
    u8 abyBuf[TRACERT_PACKSIZE] = {0};
    memset( abyBuf, 0, sizeof (abyBuf) );
    memcpy( tIcmpReq.m_abyBuf, abyBuf, sizeof (abyBuf) );
    s32 nLen = sizeof (tIcmpReq) - sizeof (tIcmpReq.m_abyBuf) + TRACERT_PACKSIZE;
    TTraceRtRst tTraceRst;

    tIcmpReq.SetID( static_cast<u16>(GetCurrentProcessId()) );
    tIcmpReq.SetSerialNo( wSN );
    tIcmpReq.SetCheckSum( 0 );
    s32 nSendTime = GetTickCount();
    tIcmpReq.SetTimeStamp( nSendTime );
    u16 wCheckSum = MakeCheckSum( reinterpret_cast<u8*>(&tIcmpReq), nLen );
    tIcmpReq.SetCheckSum( wCheckSum );

    nRet = sendto( s, reinterpret_cast<s8*>(&tIcmpReq), nLen, 0,
                   reinterpret_cast<SOCKADDR*>(&tDst), sizeof (tDst) );
    if ( nRet == SOCKET_ERROR )     //发送错误, 认为是对端不可及
    {
        return FALSE;
    }

    return TRUE;
}