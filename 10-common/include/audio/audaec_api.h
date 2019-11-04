/*****************************************************************************
模块名      : 
文件名      : audaec_api.h
相关文件    : 
文件实现功能: 
作者        : 陆志洋
版本        : V1.0  Copyright(C) 2006-2007 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2008/5/13   1.0         陆志洋        创建
******************************************************************************/
#ifndef  _AUDAEC_API_H_
#define  _AUDAEC_API_H_
#ifdef __cplusplus
extern "C" {
#endif   /* __cplusplus */

#include "audcom_api.h"

enum AudAecCmdId
{
    AUDAEC_GET_STATUS = 901,
    AUDAEC_AECTYPE_RESET,              //修改编解码类型时参数变更
    AUDAEC_PLAYSIG_SET,                //把远端信号放入远端信号的缓存中
    AUDAEC_ANALYZE_ERRCODE,
    AUDAEC_DEBUG		
};

l32 AudAecOpen(void **ppvHandle, void *ptAudAecParam);
l32 AudAecClose(void *pvHandle);
l32 AudAecProcess(void *pvHandle, void *ptAecCapInput, void *out, void *unionparam);
l32 AudAecControl(void *pvHandle, l32 cmdid, void *ptAecControlInParam, void *ptAecControlOutParam);
l32 AudAecGetVersion(void *ptAudVerInfoInput, void *ptAudVerInfoOutput);

extern TAudCodecApi tAudAec;

#ifdef __cplusplus
}
#endif  /* __cplusplus */
#endif


