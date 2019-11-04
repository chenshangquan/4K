/*=============================================================================
模   块   名: USB-KEY操作
文   件   名: UsbImportLicence.h
相 关  文 件: UsbImportLicence.cpp
文件实现功能: USB授权操作
作        者: 王昊
版        本: V4.0  Copyright(C) 2006-2006 Kedacom, All rights reserved.
-------------------------------------------------------------------------------
修改记录:
日      期  版本    修改人      修改内容
2006/10/11  1.0     王昊        创建
=============================================================================*/

// UsbImportLicence.h: interface for the CUsbImportLicence class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USBIMPORTLICENCE_H__AEF29107_53CE_4A6B_9EBE_1DB91BEA8C6F__INCLUDED_)
#define AFX_USBIMPORTLICENCE_H__AEF29107_53CE_4A6B_9EBE_1DB91BEA8C6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UsbKey.h"

//设备信息
typedef struct tagUsbDeviceInfo
{
public:
    tagUsbDeviceInfo()
    {
        Clear();
    }

    /*=============================================================================
    函 数 名:Clear
    功    能:清空
    参    数:无
    注    意:无
    返 回 值:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2006/10/11  1.0     王昊    创建
    =============================================================================*/
    inline void Clear(void) { memset( this, 0, sizeof (tagUsbDeviceInfo) ); }

    /*=============================================================================
    函 数 名:SetTag
    功    能:设置标签名
    参    数:IN LPCSTR lptrTag                      [in]    标签名
    注    意:无
    返 回 值:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2006/10/11  1.0     王昊    创建
    =============================================================================*/
    void SetTag(IN LPCSTR lptrTag);

    /*=============================================================================
    函 数 名:SetSerialNo
    功    能:设置序列号
    参    数:IN u8 *pbySerialNo                     [in]    序列号
    注    意:输入序列号为16进制内存
    返 回 值:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2006/10/11  1.0     王昊    创建
    =============================================================================*/
    void SetSerialNo(IN u8 *pbySerialNo);

    /*=============================================================================
    函 数 名:SetUsbFreeSpace
    功    能:设置USB盘剩余空间
    参    数:IN u32 dwUsbFreeSpace                  [in]    剩余空间
    注    意:无
    返 回 值:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2006/10/11  1.0     王昊    创建
    =============================================================================*/
    inline void SetUsbFreeSpace(IN u32 dwUsbFreeSpace)
    { m_dwUsbFreeSpace = dwUsbFreeSpace; }

    /*=============================================================================
    函 数 名:GetTag
    功    能:获取标签名
    参    数:无
    注    意:无
    返 回 值:标签名
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2006/10/11  1.0     王昊    创建
    =============================================================================*/
    LPCSTR GetTag(void) const { return m_szTag; }

    /*=============================================================================
    函 数 名:GetSerialNo
    功    能:获取序列号
    参    数:无
    注    意:返回字符串
    返 回 值:序列号
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2006/10/11  1.0     王昊    创建
    =============================================================================*/
    LPCSTR GetSerialNo(void) const { return m_szSerialNo; }

    /*=============================================================================
    函 数 名:GetUsbFreeSpace
    功    能:获取USB盘剩余空间
    参    数:无
    注    意:无
    返 回 值:USB盘剩余空间
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2006/10/11  1.0     王昊    创建
    =============================================================================*/
    u32 GetUsbFreeSpace(void) const { return m_dwUsbFreeSpace; }

private:
    s8  m_szTag[MAXLEN_USBKEY_DEVICE_TAG];          //设备标签名
    s8  m_szSerialNo[2 * HK_SERIAL_NUM_LEN + 1];    //设备序列号
    u32 m_dwUsbFreeSpace;                           //剩余空间
} TUsbDeviceInfo;




//导入授权
class CUsbImportLicence : public CUsbKey
{
public:
	CUsbImportLicence();
	virtual ~CUsbImportLicence();

public:
    /*=============================================================================
    函 数 名:SetDeviceCallBack
    功    能:设置设备状态回调函数
    参    数:IN LPCSTR lptrReaderName               [in]    读卡器名
             IN TUsbVerifyCallBack pFuncOnCallBack  [in]    插入回调函数
             IN TUsbVerifyCallBack pFuncOffCallBack [in]    拔出回调函数
             IN void *pCBData                       [in]    回调数据
    注    意:错误码用GetErrorDescription解释
    返 回 值:设置成功: 0; 设置失败: 错误码
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2006/10/11  1.0     王昊    创建
    =============================================================================*/
    u32 SetDeviceCallBack(IN LPCSTR lptrReaderName,
                          IN TUsbVerifyCallBack pFuncOnCallBack,
                          IN TUsbVerifyCallBack pFuncOffCallBack,
                          IN void *pCBData);

    /*=============================================================================
    函 数 名:FormatDevice
    功    能:格式化设备
    参    数:IN LPCSTR lptrReaderName               [in]    读卡器名
    注    意:错误码用GetErrorDescription解释
    返 回 值:格式化成功: 0; 格式化失败: 错误码
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2006/10/11  1.0     王昊    创建
    =============================================================================*/
    u32 FormatDevice(IN LPCSTR lptrReaderName);

    /*=============================================================================
    函 数 名:GetDeviceInfo
    功    能:获取设备信息
    参    数:IN LPCSTR lptrReaderName               [in]    读卡器名
             OUT TUsbDeviceInfo &tInfo              [out]   设备信息
    注    意:错误码用GetErrorDescription解释
    返 回 值:获取成功: 0; 获取失败: 错误码
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2006/10/11  1.0     王昊    创建
    =============================================================================*/
    u32 GetDeviceInfo(IN LPCSTR lptrReaderName, OUT TUsbDeviceInfo &tInfo);

    /*=============================================================================
    函 数 名:SaveRight
    功    能:保存授权信息
    参    数:IN LPCSTR lptrReaderName               [in]    读卡器名
             IN const TUsbMcsSaveInfo &tMcsInfo     [in]    MCS保存信息
             IN const TUsbNmsSaveInfo &tNmsInfo     [in]    NMS保存信息
             IN const TUsbPcmtSaveInfo &tPcmtInfo   [in]    PCMT保存信息
             IN const TUsbVosSaveInfo &tVosInfo     [in]    VOS保存信息
    注    意:错误码用GetErrorDescription解释
    返 回 值:保存成功: 0; 保存失败: 错误码
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2006/10/12  1.0     王昊    创建
    =============================================================================*/
    u32 SaveRight(IN LPCSTR lptrReaderName,
                  IN const TUsbMcsSaveInfo &tMcsInfo,
                  IN const TUsbNmsSaveInfo &tNmsInfo,
                  IN const TUsbPcmtSaveInfo &tPcmtInfo,
                  IN const TUsbVosSaveInfo &tVosInfo);

    /*=============================================================================
    函 数 名:ReadRight
    功    能:读取授权信息
    参    数:IN LPCSTR lptrReaderName               [in]    读卡器名
             OUT LPSTR lptrVersion                  [out]   版本信息
             OUT TUsbMcsSaveInfo &tMcsInfo          [out]   MCS授权信息
             OUT TUsbNmsSaveInfo &tNmsInfo          [out]   NMS授权信息
             OUT TUsbPcmtSaveInfo &tPcmtInfo        [out]   PCMT授权信息
             OUT TUsbVosSaveInfo &tVosInfo          [out]   VOS授权信息
    注    意:错误码用GetErrorDescription解释
    返 回 值:读取成功: 0; 读取失败: 错误码
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2006/10/12  1.0     王昊    创建
    =============================================================================*/
    u32 ReadRight(IN LPCSTR lptrReaderName,
                  OUT LPSTR lptrVersion,
                  OUT TUsbMcsSaveInfo &tMcsInfo,
                  OUT TUsbNmsSaveInfo &tNmsInfo,
                  OUT TUsbPcmtSaveInfo &tPcmtInfo,
                  OUT TUsbVosSaveInfo &tVosInfo);
};

#endif // !defined(AFX_USBIMPORTLICENCE_H__AEF29107_53CE_4A6B_9EBE_1DB91BEA8C6F__INCLUDED_)
