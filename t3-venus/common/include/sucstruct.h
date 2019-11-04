/*=============================================================================
模   块   名: 文件升级客户端业务功能库
文   件   名: sucstruct.h
相 关  文 件: sucstruct.cpp
文件实现功能: suc模块公用结构定义
作        者: 王昊
版        本: V1.0  Copyright(C) 2006-2007 Kedacom, All rights reserved.
-------------------------------------------------------------------------------
修改记录:
日      期  版本    修改人      修改内容
2007/02/11  1.0     王昊        创建
=============================================================================*/

#ifndef _SUCSTRUCT_
#define _SUCSTRUCT_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "filesrvclientstruct.h"
#include <vector>
using namespace std;

//上传文件信息
class CAddFileInfo
{
public:
    //构造函数
    CAddFileInfo() : m_emType(enumFileSrvFileTypeUnknown),
                     m_dwFileSize(0)//m_dwFileNo(0), 
    { memset( m_szFilename, 0, sizeof (m_szFilename) ); }

    //析构函数
    virtual ~CAddFileInfo() {}

public:
    //设置文件编号
//    inline void SetFileNo(u32 dwFileNo) { m_dwFileNo = dwFileNo; }

    //设置文件名
    inline void SetFilename(LPCSTR lptrFilename)
    {
        memset( m_szFilename, 0, sizeof (m_szFilename) );
        if ( lptrFilename != NULL )
        {
            strncpy( m_szFilename, lptrFilename, sizeof (m_szFilename) - 1 );
        }
    }

    //设置文件类型
    inline void SetFileType(EMFileSrvFileType emType) { m_emType = emType; }

    //设置文件大小
    inline void SetFileSize(u32 dwSize) { m_dwFileSize = dwSize; } 

    //获取文件编号
//    inline u32 GetFileNo(void) const { return m_dwFileNo; }

    //获取文件名
    inline LPCSTR GetFilename(void) const { return m_szFilename; }

    //获取文件类型
    inline EMFileSrvFileType GetFileType(void) const { return m_emType; }

    //获取文件大小
    inline u32 GetFileSize(void) const { return m_dwFileSize; }

private:
//    u32                 m_dwFileNo;             //文件编号(主机序)
    s8                  m_szFilename[MAX_PATH]; //本地文件全名
    EMFileSrvFileType   m_emType;               //文件类型
    u32                 m_dwFileSize;           //文件大小(按字节计算，主机序)
};

//上传版本信息
class CAddVerInfo
{
public:
    CAddVerInfo() : m_emDevType(enumFileSrvDevTypeUnknown),
                    m_byDevModel(0), m_emOsType(enumFileSrvOSTypeUnknown)//m_dwDevNo(0)
    { memset( m_szBugReport, 0, sizeof (m_szBugReport) ); }

    virtual ~CAddVerInfo() {}

public:
    //设置设备编号
//    inline void SetDevNo(u32 dwDevNo) { m_dwDevNo = dwDevNo; }

    //获取设备编号
//    inline u32 GetDevNo(void) const { return m_dwDevNo; }

    //设置设备类型
    inline void SetDevType(EMFileSrvDevType emType) { m_emDevType = emType; }

    //获取设备类型
    inline EMFileSrvDevType GetDevType(void) const { return m_emDevType; }

    //设置设备型号
    inline void SetDevModel(u8 byDevModel) { m_byDevModel = byDevModel; }

    //获取设备型号
    inline u8 GetDevModel(void) const { return m_byDevModel; }

    //设置操作系统类型
    inline void SetOsType(EMFileSrvOSType emOsType) { m_emOsType = emOsType; }

    //获取操作系统类型
    inline EMFileSrvOSType GetOsType(void) const { return m_emOsType; }

    //设置硬件版本号
    inline void SetHardwareVer(const IFCHardwareVer &tHardVer)
    { m_tHardVer = tHardVer; }

    //获取硬件版本号
    inline IFCHardwareVer GetHardwareVer(void) const
    { return m_tHardVer; }

    //设置软件版本号
    inline void SetSoftwareVer(const IFCSoftwareVer &tSoftVer)
    { m_tSoftVer = tSoftVer; }

    //获取软件版本号
    inline IFCSoftwareVer GetSoftwareVer(void) const
    { return m_tSoftVer; }

    //设置修复描述
    inline void SetBugReport(LPCSTR lptrBugReport)
    {
        memset( m_szBugReport, 0, sizeof (m_szBugReport) );
        if ( lptrBugReport != NULL )
        {
            strncpy( m_szBugReport, lptrBugReport, sizeof (m_szBugReport) - 1 );
        }
    }

    //获取修复描述
    inline LPCSTR GetBugReport(void) const { return m_szBugReport; }

private:
//    u32                     m_dwDevNo;
    EMFileSrvDevType        m_emDevType;
    u8                      m_byDevModel;
    EMFileSrvOSType         m_emOsType;
    IFCHardwareVer          m_tHardVer;
    IFCSoftwareVer          m_tSoftVer;
    s8                      m_szBugReport[MAX_FILESRV_BUG_REPORT_LEN];
public:
    vector<CAddFileInfo>    m_vctFile;
};

#endif//_SUCSTRUCT_
