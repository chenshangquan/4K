/*=======================================================================
模块名      :NmsCommon.lib单元测试
文件名      : api.cpp
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
#include "api.h"
#include "nmscommon.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////
// CAPICase

void CAPICase::setUp()
{
}

void CAPICase::tearDown()
{
}

/*========================================================================
函 数 名：GetConfBitrate
功    能：得到会议码率
参    数：
返 回 值：
--------------------------------------------------------------------------
修改记录：
日		期	版本	修改人	修改内容
2005/01/25	3.6		李洪强	创建
========================================================================*/
void CAPICase::GetConfBitrate()
{
    u32 *pdwConfRate = NULL;
    s32 nRateNum = 0;
    ::GetConfBitrate(&pdwConfRate, nRateNum);
    CPPUNIT_ASSERT(pdwConfRate != NULL);
    CPPUNIT_ASSERT(nRateNum >= 0);
    for(s32 nIndex = 0; nIndex < nRateNum; nIndex++)
    {
        u32 dwRate = pdwConfRate[nIndex];
        CPPUNIT_ASSERT(dwRate > 0);
        CPPUNIT_ASSERT((dwRate % 64) == 0);
    }
}

/*========================================================================
函 数 名：GetModuleFullPath
功    能：得到模块全路径
参    数：
返 回 值：
--------------------------------------------------------------------------
修改记录：
日		期	版本	修改人	修改内容
2005/01/25	3.6		李洪强	创建
========================================================================*/
void CAPICase::GetModuleFullPath()
{
    CString csModePath = ::GetModuleFullPath();
    CPPUNIT_ASSERT(!csModePath.IsEmpty());

    s32 nPos = csModePath.Find(":\\");
    CPPUNIT_ASSERT(nPos == 1);

    nPos = csModePath.ReverseFind('\\');
    CPPUNIT_ASSERT(nPos == csModePath.GetLength() - 1);
}

/*========================================================================
函 数 名：nmscommonver
功    能：得到库的版本号
参    数：
返 回 值：
--------------------------------------------------------------------------
修改记录：
日		期	版本	修改人	修改内容
2005/01/25	3.6		李洪强	创建
========================================================================*/
void CAPICase::nmscommonver()
{
    ::nmscommonver();
}

/*========================================================================
函 数 名：ModuleRegToOsp
功    能：向osp注册模块
参    数：
返 回 值：
--------------------------------------------------------------------------
修改记录：
日		期	版本	修改人	修改内容
2005/01/25	3.6		李洪强	创建
========================================================================*/
void CAPICase::ModuleRegToOsp()
{
    BOOL bRet = ::ModuleRegToOsp();
    CPPUNIT_ASSERT(bRet == TRUE);
}

void CAPICase::Encrypt(void)
{
    s8 aszPwd[32];
    s8 aszDecrptPwd[32];
    s8 aszEncryptedPwd[64];

    ZeroMemory( aszDecrptPwd, 32 );
    ZeroMemory( aszEncryptedPwd, 64 );
    strcpy( aszPwd, "qwertyuiopasdfghjklzxcvbnm" );

    ::EncryptPwd( aszPwd, aszEncryptedPwd );
    ::DecryptPwd( aszEncryptedPwd, aszDecrptPwd );
    CPPUNIT_ASSERT( strcmp( aszPwd, aszDecrptPwd ) == 0 );
}

