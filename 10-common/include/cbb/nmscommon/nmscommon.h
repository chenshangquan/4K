/*=======================================================================
模块名      : 网管公用模块库
文件名      : nmscommon.h
相关文件    : 
文件实现功能: 将网管组各公用模块提出来
作者        : 李洪强
版本        : V4.0  Copyright(C) 2003-2006 Suzhou Keda Technology Co.Ltd
                    All rights reserved.
-------------------------------------------------------------------------
修改记录:
日      期  版本    修改人  修改内容
2004/07/16  3.0     李洪强  创建
2005/12/08  4.0     王昊    增加文件，分离功能
=======================================================================*/

#ifndef _NMSCOMMON_H
#define _NMSCOMMON_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <comcat.h>
#include <afxole.h>
#include <objsafe.h>
#include <AFXCTL.H>
#include "osp.h"
#include "ftpctrl.h"
#include "calladdr.h"
#include "tplarray.h"
#include "tplhash.h"
#include "logmanage.h"
#include "hexasciistring.h"

//	删除单个指针
#define DEL_PTR(p)              if (p != NULL) { delete p; p = NULL; }
//	删除数组指针
#define DEL_PTR_ARRAY(p)        if (p != NULL) { delete [] p; p = NULL; }

//////////////////////////////////////////////////////////////////////////
//
//     安全注册ocx控件的辅助函数
//
// Helper function to create a component category and associated description
HRESULT CreateComponentCategory(CATID catid, WCHAR *catDescription);
// Helper function to register a CLSID as belonging to a component category
HRESULT RegisterCLSIDInCategory(REFCLSID clsid, CATID catid);
// Helper function to unregister a CLSID as belonging to a component category
HRESULT UnRegisterCLSIDInCategory(REFCLSID clsid, CATID catid);

/*=============================================================================
函 数 名:nmscommonver
功    能:打印NmsCommon库的版本号
参    数:无
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2004/09/13  3.5     李洪强  创建
=============================================================================*/
API void nmscommonver(void);

/*=============================================================================
函 数 名:GetConfBitrate
功    能:获取会议码率
参    数:u32 **ppdwBitrate              [out]   会议码率数组
         s32 &nNum                      [out]   数组大小
         u32 dwMCUType                  [in]    MCU类型
注    意:不需要给ppdwBitrate分配空间, 且不能delete ppdwBitrate
         8000C MCU只支持到4M
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2004/09/29  3.5     王昊    创建
2007/04/25  4.0     王廖荣  修改
=============================================================================*/
void GetConfBitrate(u32 **ppdwBitrate, s32 &nNum, u32 dwMCUType = 0);

/*=============================================================================
函 数 名:GetModuleFullPath
功    能:获取模块所在文件夹全路径, 包括最后的\
参    数:无
注    意:例如 C:\
返 回 值:文件夹字符串
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2004/10/26  3.5     王昊    创建
=============================================================================*/
CString GetModuleFullPath(void);

/*=============================================================================
函 数 名:ModuleRegToOsp
功    能:向OSP注册本模块
参    数:无
注    意:无
返 回 值:成功：TRUE; 失败：FALSE
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2004/10/26  3.5     王昊    创建
=============================================================================*/
BOOL32 ModuleRegToOsp(void);

/*=============================================================================
函 数 名:GetUrl
功    能:获取IE地址栏内容
参    数:const COleControl *pcCtrl          [in]    ocx控件
         CString &cstrUrl                   [out]    地址栏内容
注    意:无
返 回 值:成功:TRUE; 失败:FALSE
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/11/08  4.0     王昊    创建
=============================================================================*/
BOOL32 GetUrl(const COleControl *pcCtrl, CString &cstrUrl);

/*=============================================================================
函 数 名:EncryptPwd
功    能:密码加密
参    数:LPCSTR lpszPwd                     [in]    原始密码, 最长32位(包括'/0')
         s8 aszEncryptedPwd[64]             [out]   加密密码
算法说明:字符替换
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/11/21  4.0     王昊    创建
=============================================================================*/
void EncryptPwd(LPCSTR lpszPwd, s8 aszEncryptedPwd[64]);

/*=============================================================================
函 数 名:DecryptPwd
功    能:密码解密
参    数:s8 aszEncryptedPwd[64]             [in]    加密密码
         LPSTR lpszPwd                      [out]   原始密码, 最长32位(包括'/0')
算法说明:字符替换
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2005/11/21  4.0     王昊    创建
=============================================================================*/
void DecryptPwd(s8 aszEncryptedPwd[64], LPSTR lpszPwd);

/*=============================================================================
函 数 名:InitNonChineseCtrl
功    能:非中文操作系统界面初始化
参    数:无
算法说明:无
注    意:无
返 回 值:无
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2006/08/04  4.0     王昊    创建
=============================================================================*/
inline void InitNonChineseCtrl(void)
{
    //  wanghao 2006/08/04 非中文操作系统处理
    if ( PRIMARYLANGID( GetSystemDefaultLangID() ) != LANG_CHINESE )
    {
        TCHAR aszFontFile[MAX_PATH + 1] = _T("");
        GetWindowsDirectory( aszFontFile, MAX_PATH );
        _tcscat( aszFontFile, _T("\\Fonts\\simsun.ttc") );
        FILE *pf = fopen( aszFontFile, "r" );
        if ( pf != NULL )
        {
            fclose( pf );
            pf = NULL;
            ShellExecute( NULL, "open", aszFontFile, "", "", SW_HIDE );
            Sleep( 500 );   //等待字体安装完成
        }
        else
        {
            CString cstrFontFile = GetModuleFullPath() + _T("simsun.ttc");
            pf = fopen( cstrFontFile, "r" );
            if ( pf != NULL )
            {
                fclose( pf );
                pf = NULL;
                CopyFile( cstrFontFile, aszFontFile, TRUE );
                ShellExecute( NULL, "open", aszFontFile, "", "", SW_HIDE );
                Sleep( 500 );   //等待字体安装完成
            }
        }
    }
}

/*=============================================================================
函 数 名: GetModuleCfgFileFullName
功    能: 获取配置文件全路径
参    数: LPCSTR lptrFileName                   [in]    配置文件名
注    意: 无
返 回 值: 配置文件全路径
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2007/03/01  1.0     王昊    创建
=============================================================================*/
CString GetModuleCfgFileFullName(LPCSTR lptrFileName);

/*========================================================================
函 数 名：CheckIEBHOAvailable
功    能：检查IE中是否加载了和我们的OCX控件不兼容的插件
注    意：可以在控件的InitInstance()中进行调用，如返回FALSE则控件退出
          例如：
            BOOL CTestApp::InitInstance()
            {
	            BOOL bInit = COleControlModule::InitInstance();

	            if (bInit)
	            {
                    BOOL bBHOAvailable = CheckIEBHOAvailable( 0 );
                    if ( FALSE == bBHOAvailable )
                    {
                        return FALSE;
                    }
	            }

	            return bInit;
            }

参    数：u32 dwLanguage        [in]    语言类型    0为英文，1为中文
返 回 值：TRUE：    没有不兼容的插件或用户选择不卸载相应的插件
          FALSE：   检测到有不兼容的插件，且用户选择卸载相应的插件
相关消息：
--------------------------------------------------------------------------
修改记录：
日      期  版本    修改人  修改内容
2007/11/07  1.0     王廖荣    创建
========================================================================*/
BOOL32 CheckIEBHOAvailable(u32 dwLanguage);


#endif // _NMSCOMMON_H