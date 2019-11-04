#ifndef _KDVSECDEVFEATURE_H_
#define _KDVSECDEVFEATURE_H_
#include <system/kdvtype.h>

typedef struct _TSecDevFeatrue
{
    char szMacAddr[32];
    u32 dwDeviceIpCount; 
    char szDeviceIp[8][64];
    char szDeviceType[64];               /*设备ProductID*/
    char szDeviceVersion[64];            /*设备VersionID*/
    char szDeviceE164Num[16];            /*设备E164号码*/
    BOOL32 bIsKdvDevice;
}TSecDevFeatrue,*PTSecDevFeatrue;

typedef struct _TSecDevVerifyResult
{
    char szMacAddr[32];
    u32 dwDeviceIpCount;
    char szDeviceIP[8][64];
    char szDeviceType[64];
    char szDeviceVersion[64];
    char szDeviceE164Num[16];
    BOOL32 bIsKdvDevice;
    char szRemoteIp[64];
    u16 wRemotePort;
    u64 fwUpdateTime;
}TSecDevVerifyResult,*PTSecDevVerifyResult;

s32 KdvSecGetDeviceFeature(TSecDevFeatrue *ptFeatrue);

#endif
