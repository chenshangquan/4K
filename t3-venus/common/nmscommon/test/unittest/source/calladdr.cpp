/*=======================================================================
模块名      :NmsCommon.lib单元测试
文件名      : calladdr.cpp
相关文件    :
文件实现功能 :
作者        : 李洪强
版本        : V3.6  Copyright(C) 2003-2005 Suzhou Keda Technology Co.Ltd
                    All rights reserved.
--------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2005/01/25  3.6         李洪强      创建
=======================================================================*/
#include "stdafx.h"
#include "calladdr.h"
#include "nmscommon.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////
// CCallAddrCase

void CCallAddrCase::setUp()
{
}

void CCallAddrCase::tearDown()
{
}

void CCallAddrCase::NewDelete()
{
#ifdef _DEBUG

	CMemoryState cStateInit, cStateEnd, cStateDiff;    
	cStateInit.Checkpoint();

	CCallAddr *pcAddr = new CCallAddr;
    CPPUNIT_ASSERT(pcAddr != NULL);

	DEL_PTR(pcAddr);

	cStateEnd.Checkpoint();
	BOOL bLeak = cStateDiff.Difference(cStateInit, cStateEnd);
	if (bLeak)
	{
		cStateDiff.DumpStatistics();
		cStateInit.DumpAllObjectsSince();
	}

	CPPUNIT_ASSERT(!bLeak); 
#endif
}

/*========================================================================
函 数 名：IsValidIplpStr
功    能：字串型IP地址的有效性判断
参    数：
返 回 值：
--------------------------------------------------------------------------
修改记录：
日		期	版本	修改人	修改内容
2005/01/25	3.6		李洪强	创建
========================================================================*/
void CCallAddrCase::IsValidIplpStr()
{
    // 有效值
    BOOL bRet = CCallAddr::IsValidIpV4("172.16.5.200");
    CPPUNIT_ASSERT(bRet == TRUE);

    // 空字串指针
    LPCSTR lpIP = NULL;
    bRet = CCallAddr::IsValidIpV4(lpIP);
    CPPUNIT_ASSERT(bRet == FALSE);

    // 长度不正确
    bRet = CCallAddr::IsValidIpV4("172.13");
    CPPUNIT_ASSERT(bRet == FALSE);
    bRet = CCallAddr::IsValidIpV4("182.152.236.2344");
    CPPUNIT_ASSERT(bRet == FALSE);
    
    // 以0打头
    bRet = CCallAddr::IsValidIpV4("0.12.6.6");
    CPPUNIT_ASSERT(bRet == FALSE);

    // 以“.”开头
    bRet = CCallAddr::IsValidIpV4(".72.6.78");
    CPPUNIT_ASSERT(bRet == FALSE);

    // 没有"."
    bRet = CCallAddr::IsValidIpV4("172165223");
    CPPUNIT_ASSERT(bRet == FALSE);

    // 有其他字符
    bRet = CCallAddr::IsValidIpV4("172.a16.5.5");
    CPPUNIT_ASSERT(bRet == FALSE);

    // 点的位置不对
    bRet = CCallAddr::IsValidIpV4("1721.3.4.5");
    CPPUNIT_ASSERT(bRet == FALSE);

    bRet = CCallAddr::IsValidIpV4("172..16.46.5");
    CPPUNIT_ASSERT(bRet == FALSE);

    bRet = CCallAddr::IsValidIpV4("172.1682.5.3");
    CPPUNIT_ASSERT(bRet == FALSE);

    // 单个域超过255
    bRet = CCallAddr::IsValidIpV4("354.2.53.6");
    CPPUNIT_ASSERT(bRet == FALSE);
    
    bRet = CCallAddr::IsValidIpV4("172.335.0.5");
    CPPUNIT_ASSERT(bRet == FALSE);
}

/*========================================================================
函 数 名：IsValidIpCString
功    能：CString型IP地址的有效性判断
参    数：
返 回 值：
--------------------------------------------------------------------------
修改记录：
日		期	版本	修改人	修改内容
2005/01/25	3.6		李洪强	创建
========================================================================*/
void CCallAddrCase::IsValidIpCString()
{
    // 有效值
    BOOL bRet = CCallAddr::IsValidIpV4(CString("172.16.5.200"));
    CPPUNIT_ASSERT(bRet == TRUE);

    //空指针
    
    bRet = CCallAddr::IsValidIpV4(CString(""));
    CPPUNIT_ASSERT(bRet == FALSE);

    //长度不正确
    bRet = CCallAddr::IsValidIpV4(CString("172.13"));
    CPPUNIT_ASSERT(bRet == FALSE);
    bRet = CCallAddr::IsValidIpV4(CString("182.152.236.2344"));
    CPPUNIT_ASSERT(bRet == FALSE);
    
    // 以0打头
    bRet = CCallAddr::IsValidIpV4(CString("0.12.6.6"));
    CPPUNIT_ASSERT(bRet == FALSE);

    // 以“.”开头
    bRet = CCallAddr::IsValidIpV4(CString(".72.6.78"));
    CPPUNIT_ASSERT(bRet == FALSE);

    // 没有"."
    bRet = CCallAddr::IsValidIpV4(CString("172165223"));
    CPPUNIT_ASSERT(bRet == FALSE);

    // 有其他字符
    bRet = CCallAddr::IsValidIpV4(CString("172.a16.5.5"));
    CPPUNIT_ASSERT(bRet == FALSE);

    // 点的位置不对
    bRet = CCallAddr::IsValidIpV4(CString("1721.3.4.5"));
    CPPUNIT_ASSERT(bRet == FALSE);

    bRet = CCallAddr::IsValidIpV4(CString("172..16.46.5"));
    CPPUNIT_ASSERT(bRet == FALSE);

    bRet = CCallAddr::IsValidIpV4(CString("172.1682.5.3"));
    CPPUNIT_ASSERT(bRet == FALSE);

    // 单个域超过255
    bRet = CCallAddr::IsValidIpV4(CString("354.2.53.6"));
    CPPUNIT_ASSERT(bRet == FALSE);
    
    bRet = CCallAddr::IsValidIpV4(CString("172.335.0.5"));
    CPPUNIT_ASSERT(bRet == FALSE);
}

/*========================================================================
函 数 名：IsValidIpDword
功    能：双字节型IP地址的有效性判断
参    数：
返 回 值：
--------------------------------------------------------------------------
修改记录：
日		期	版本	修改人	修改内容
2005/01/25	3.6		李洪强	创建
========================================================================*/
void CCallAddrCase::IsValidIpDword()
{
    // 有效值
    BOOL bRet = CCallAddr::IsValidIpV4(0xAC1005C8);
    CPPUNIT_ASSERT(bRet == TRUE);

    // 0值
    bRet = CCallAddr::IsValidIpV4((u32)0);
    CPPUNIT_ASSERT(bRet == FALSE);
    
    // 以0打头
    bRet = CCallAddr::IsValidIpV4(0x001005C8);
    CPPUNIT_ASSERT(bRet == FALSE);
}

/*========================================================================
函 数 名：GetLastErrorInfo
功    能：返回出错信息
参    数：
返 回 值：
--------------------------------------------------------------------------
修改记录：
日		期	版本	修改人	修改内容
2005/01/25	3.6		李洪强	创建
========================================================================*/
void CCallAddrCase::GetLastErrorInfo()
{
    // 有效值
    CCallAddr::IsValidIpV4("172.16.5.200");
    CString csErroInfo;
    CCallAddr::GetLastErrorInfo(csErroInfo);

    CPPUNIT_ASSERT(csErroInfo.Find("合法") >= 0);

    // 空字串指针
    LPCSTR lpIP = NULL;
    CCallAddr::IsValidIpV4(lpIP);
    CCallAddr::GetLastErrorInfo(csErroInfo);
    CPPUNIT_ASSERT(csErroInfo.Find("为空") >= 0);

    // 长度不正确
    CCallAddr::IsValidIpV4("172.36");
    CCallAddr::GetLastErrorInfo(csErroInfo);
    CPPUNIT_ASSERT(csErroInfo.Find("长度非法") >= 0);

    CCallAddr::IsValidIpV4("182.152.236.2344");
    CCallAddr::GetLastErrorInfo(csErroInfo);
    CPPUNIT_ASSERT(csErroInfo.Find("长度非法") >= 0);

    
    // 以0打头
    CCallAddr::IsValidIpV4("0.12.6.6");
    CCallAddr::GetLastErrorInfo(csErroInfo);
    CPPUNIT_ASSERT(csErroInfo.Find("以0开头") >= 0);

    // 以“.”开头
    CCallAddr::IsValidIpV4(".72.6.78");
    CCallAddr::GetLastErrorInfo(csErroInfo);
    CPPUNIT_ASSERT(csErroInfo.Find("以点开头") >= 0);

    // 没有"."
    CCallAddr::IsValidIpV4("172165223");
    CCallAddr::GetLastErrorInfo(csErroInfo);
    CPPUNIT_ASSERT(csErroInfo.Find("IP地址分隔点位置不正确") >= 0);

    // 有其他字符
    CCallAddr::IsValidIpV4("172.a16.5.5");
    CCallAddr::GetLastErrorInfo(csErroInfo);
    CPPUNIT_ASSERT(csErroInfo.Find("非法字符") >= 0);

    // 点的位置不对
    CCallAddr::IsValidIpV4("1721.3.4.5");
    CCallAddr::GetLastErrorInfo(csErroInfo);
    CPPUNIT_ASSERT(csErroInfo.Find("点位置不正确") >= 0);

    CCallAddr::IsValidIpV4("172..16.46.5");
    CCallAddr::GetLastErrorInfo(csErroInfo);
    CPPUNIT_ASSERT(csErroInfo.Find("多余的分隔符") >= 0);

    CCallAddr::IsValidIpV4("172.1682.5.3");
    CCallAddr::GetLastErrorInfo(csErroInfo);
    CPPUNIT_ASSERT(csErroInfo.Find("点位置不正确") >= 0);

    // 单个域超过255
    CCallAddr::IsValidIpV4("354.2.53.6");
    CCallAddr::GetLastErrorInfo(csErroInfo);
    CPPUNIT_ASSERT(csErroInfo.Find("超范围") >= 0);

    CCallAddr::IsValidIpV4("172.335.0.5");
    CCallAddr::GetLastErrorInfo(csErroInfo);
    CPPUNIT_ASSERT(csErroInfo.Find("超范围") >= 0);
}

/*========================================================================
函 数 名：GetIpStr
功    能：双字节到字串型地址的转化
参    数：
返 回 值：
--------------------------------------------------------------------------
修改记录：
日		期	版本	修改人	修改内容
2005/01/25	3.6		李洪强	创建
========================================================================*/
void CCallAddrCase::GetIpStr()
{
    CString csIP = CCallAddr::GetIpStr(0xAC1005C8);
    CPPUNIT_ASSERT(csIP == "172.16.5.200");
}

/*========================================================================
函 数 名：GetCallStrType
功    能：得到字串是何种呼叫类型
参    数：
返 回 值：
--------------------------------------------------------------------------
修改记录：
日		期	版本	修改人	修改内容
2005/01/25	3.6		李洪强	创建
========================================================================*/
void CCallAddrCase::GetCallStrType()
{
    CString csCallAddr = "";
    UINT dwType = CCallAddr::GetCallStrType(csCallAddr);
    CPPUNIT_ASSERT(dwType == CCallAddr::NORMAL_STR);

    csCallAddr = "172.16.5.200";
    dwType = CCallAddr::GetCallStrType(csCallAddr);
    CPPUNIT_ASSERT(dwType == CCallAddr::IP_STR);

    csCallAddr = "123455";
    dwType = CCallAddr::GetCallStrType(csCallAddr);
    CPPUNIT_ASSERT(dwType == CCallAddr::NUM164_STR);

    csCallAddr = "Mt20";
    dwType = CCallAddr::GetCallStrType(csCallAddr);
    CPPUNIT_ASSERT(dwType == CCallAddr::H323ID_STR);
}
/*========================================================================
函 数 名：GetCallStrType
功    能：一个u32 数是不是一个合法的Ip掩码
参    数：
返 回 值：
--------------------------------------------------------------------------
修改记录：
日		期	版本	修改人	修改内容
2005/08/31	4.0		刘瑞飞	创建
========================================================================*/
void CCallAddrCase::IsValidIpMask()
{
	//有效
	BOOL32 bRet = CCallAddr::IsValidIpMask(0xffffff00);
	CPPUNIT_ASSERT(bRet == TRUE);

	//0值
	bRet = CCallAddr::IsValidIpMask(u32(0));
	CPPUNIT_ASSERT(FALSE == bRet);

	//101 
	bRet = CCallAddr::IsValidIpMask(0xffdf0000);
	CPPUNIT_ASSERT(FALSE == bRet);

	//255.255.255.255
	bRet = CCallAddr::IsValidIpMask(0xffffffff);
	CPPUNIT_ASSERT(FALSE == bRet);
}
/*========================================================================
函 数 名：IsValidIpMaskStr
功    能： 字符串是不是一个合法的Ip地址
参    数：
返 回 值：
--------------------------------------------------------------------------
修改记录：
日		期	版本	修改人	修改内容
2005/08/31	4.0		刘瑞飞	创建
========================================================================*/
void CCallAddrCase::IsValidIpMaskStr()
{
	//合法
	BOOL32 bRet = CCallAddr::IsValidIpMask("255.255.255.0");
	CPPUNIT_ASSERT(TRUE == bRet);

	//0 value
	bRet = CCallAddr::IsValidIpMask("0.0.0.0");
	CPPUNIT_ASSERT(FALSE == bRet);

	//非法
	bRet = CCallAddr::IsValidIpMask("255.225.223.0");
	CPPUNIT_ASSERT(FALSE == bRet);

	//255.255.255.255
	bRet = CCallAddr::IsValidIpMask("255.255.255.255");
	CPPUNIT_ASSERT(FALSE == bRet);

	//255.001.000.000
	bRet = CCallAddr::IsValidIpMask("255.001.000.000");
	CPPUNIT_ASSERT(FALSE == bRet);
}

/*=============================================================================
函 数 名:GetLocalIpAddr
功    能:获取所有本机IP地址测试
参    数:无
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/10/29  4.0   王昊    创建
=============================================================================*/
void CCallAddrCase::GetLocalIpAddr(void)
{
    WSAData wsaData;
    WSAStartup( 0x0202, &wsaData );

    u32 *pdwLocalIp = NULL;
    s32 nIpNum = 0;
    CCallAddr::GetLocalIpAddr( pdwLocalIp, nIpNum );
    DEL_PTR_ARRAY( pdwLocalIp );
    CPPUNIT_ASSERT( nIpNum > 0 );

    WSACleanup();
}