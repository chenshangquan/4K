/******************************************************************************
模块名  ： VPSS_DRV_API
文件名  ： vpss_api_frame_mem.h
相关文件： vpss_api_frame_mem.c
文件实现功能：
作者    ：张方明
版本    ：1.0.0.0.0
-------------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
09/15/2011  1.0         张方明      创建
******************************************************************************/
#ifndef __VPSS_API_FRAME_MEM_H
#define __VPSS_API_FRAME_MEM_H

#ifdef __cplusplus 
extern "C" { 
#endif /* __cplusplus */

#include "kdvtype.h"
#include "vpss_api_def.h"
#include "vpss_api_core.h"


/* 函数声明 */
/*==============================================================================
    函数名      : VpssFrameAlloc
    功能        : 申请帧buf
    输入参数说明: ptFrame: 视频参数
                  dwNumFrames: 帧数 
    返回值说明  : 错误返回VPSS_FAILURE或错误码；成功返回VPSS_SUCCESS
------------------------------------------------------------------------------*/
s32 VpssFrameAlloc(TVpssFrame *ptFrame, u32 dwNumFrames);

/*==============================================================================
    函数名      : VpssFrameFree
    功能        : 释放帧buf
    输入参数说明: ptFrame: 视频参数
                  dwNumFrames: 帧数 
    返回值说明  : 错误返回VPSS_FAILURE或错误码；成功返回VPSS_SUCCESS
------------------------------------------------------------------------------*/
s32 VpssFrameFree(TVpssFrame *ptFrame, u32 dwNumFrames);

/*==============================================================================
    函数名      : VpssFrameGetSize
    功能        : 查询帧的大小
    输入参数说明: ptFrame: 视频参数
                  pdwSize: buffer size
                  pdwOffsetC: C plane offset for YUV420SP data
    返回值说明  : 错误返回VPSS_FAILURE或错误码；成功返回VPSS_SUCCESS
------------------------------------------------------------------------------*/
s32 VpssFrameGetSize(TVpssFrame *ptFrame, u32 *pdwSize, u32 *pdwOffsetC);

/*==============================================================================
    函数名      : VpssGetFrameInfo
    功能        : 查询framebuffer的使用情况
    输入参数说明: NULL
    返回值说明  : NULL
------------------------------------------------------------------------------*/
void VpssGetFrameInfo(void);


#ifdef __cplusplus 
} 
#endif /* __cplusplus */

#endif /* __VPSS_API_FRAME_MEM_H */
