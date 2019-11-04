/******************************************************************************
模块名  ： VPSS_DRV_API
文件名  ： vpss_api_grpx.h
相关文件： vpss_api_grpx.c
文件实现功能：
作者    ：张方明
版本    ：1.0.0.0.0
-------------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
03/31/2011  1.0         张方明      创建
******************************************************************************/
#ifndef __VPSS_API_GRPX_H
#define __VPSS_API_GRPX_H

#ifdef __cplusplus 
extern "C" { 
#endif /* __cplusplus */

#include "vpss_api_core.h"
#include "vpss_api_dctrl.h"

/* -------------------------------- 宏定义 ----------------------------------*/
/* dwGrpxId定义 */
#define VPSS_GRPX0                          0x0
#define VPSS_GRPX1                          0x1
#define VPSS_GRPX2                          0x2
#define VPSS_GRPX_MAX                       0x3

#define VPSS_GRPX_WIN_MAX                    12
#define VPSS_GRPX_FRAME_LIST_MAX             8

/* dwBlendType 定义 */
#define VPSS_GRPX_BLEND_NO                  0   /* 不透明，等同于透明因子为0xff情况 */
#define VPSS_GRPX_BLEND_REGION_GLOBAL       1   /* 全屏进行半透明处理，透明因子由用户指定 */
#define VPSS_GRPX_BLEND_COLOR               2   /* color (palette) blending, alpha value in the CLUT is applied*/
#define VPSS_GRPX_BLEND_PIXEL               3   /* pixel(embedding alpha)blending, embedded alpha value is applied */

/* dwTransColorMask 全透明颜色掩码定义 */
#define VPSS_GRPX_TRANS_NO_MASK             0   /* No mask, 8 bits compared */
#define VPSS_GRPX_TRANS_1BIT_MASK           1   /* 1bit mask, MSB 7Bits compared */
#define VPSS_GRPX_TRANS_2BIT_MASK           2   /* 2bit mask, MSB 6Bits compared */
#define VPSS_GRPX_TRANS_3BIT_MASK           3   /* 3bit maks, MSB 5bits compared */

/* VpssGrpxCtrl操作码定义 */
#define VPSS_GRPX_SET_WIN_PARAM             0   /* pArgs对应(TVpssGrpxRtWinParam *) */

/* ------------------------------- 类型定义 ---------------------------------*/


/* ------------------------------- 结构定义 ---------------------------------*/
/* 结构定义 */
typedef struct{
    u32             dwImgWidth;                 /* osd图片数据宽度，填0表示全屏大小 */
    u32             dwImgHeight;                /* osd图片数据高度，填0表示全屏大小 */
    u32             dwWinX;                     /* osd窗口相对底图左边右移n个象素，整个图像右移，注意：不能超出底图范围  */
    u32             dwWinY;                     /* osd窗口相对底图顶部下移n行，整个图像下移，注意：不能超出底图范围 */
    u32             dwWinWidth;                 /* 填0则等于dwImgWidth,非0表示osd窗口宽度，如果和dwImgWidth不等的话启动缩放，注意：不能超出底图范围 */
    u32             dwWinHight;                 /* 填0则等于dwImgHeight,非0表示osd窗口高度，如果和dwImgHeight不等的话启动缩放，注意：不能超出底图范围 */
    u32             dwFBufSize;                 /* 填0表示自动计算每帧Buf大小,非0表示用户指定每帧Buf大小 */
    u32             dwFPitch;                   /* 用户不用填值，由驱动自动计算大小 */

    u32             dwBlendType;                /* 透明合成方法, 如: VPSS_GRPX_BLEND_REGION_GLOBAL */
    u32             dwBlendAlpha;               /* 全屏透明时的透明因子,0-255,当dwBlendType为全屏透明时才有效 */

    u32             dwTransEnable;              /* 全透明功能是否允许: 1=en */
    u32             dwTransColorMask;           /* 全透明颜色掩码, 如: VPSS_GRPX_TRANS_NO_MASK */
    u32             dwTransColorRgb24;          /* 全透明颜色RGB888格式 */
} TVpssGrpxWin;

typedef struct{
    TVpssVidStd     tVidStd;                    /* 对应的VENC输出的信号制式 */

    u32             dwFrameListNum;             /* 分配几个帧buf链,范围:1-VPSS_GRPX_FRAME_LIST_MAX, 0=默认3个 */

    u32             dwWinNum;                   /* 创建几个窗口区域,范围:1-VPSS_GRPX_WIN_MAX
                                                   目前暂时支持一个窗口, 0=默认1个 */
    TVpssGrpxWin    tGrpxWin[VPSS_GRPX_WIN_MAX];/* 每个窗口区域的参数 */
} TVpssGrpxParam;

/* 窗口(run time)动态参数设置 */
typedef struct{
    u32             dwWinId;                    /* 填0表示全屏显示,非0表示osd窗口宽度， 注意：不能超出底图范围 */

    u32             dwWinX;                     /* osd窗口相对底图左边右移n个象素，整个图像右移，注意：不能超出底图范围  */
    u32             dwWinY;                     /* osd窗口相对底图顶部下移n行，整个图像下移，注意：不能超出底图范围 */

    u32             dwBlendType;                /* 透明合成方法, 如: VPSS_GRPX_BLEND_REGION_GLOBAL */
    u32             dwBlendAlpha;               /* 全屏透明时的透明因子,0-255,当dwBlendType为全屏透明时才有效 */

    u32             dwTransEnable;              /* 全透明功能是否允许: 1=en */
    u32             dwTransColorMask;           /* 全透明颜色掩码, 如: VPSS_GRPX_TRANS_NO_MASK */
    u32             dwTransColorRgb24;          /* 全透明颜色RGB888格式 */
} TVpssGrpxRtWinParam;


/* 函数声明 */
/*==============================================================================
    函数名      : VpssGrpxOpen
    功能        : 打开指定GRPX口
    输入参数说明: dwGrpxId: GRPX口的ID号，如: VPSS_GRPX0
                  ptGrpxParam: GRPX口参数
    返回值说明  : 错误返回VPSS_FAILURE或错误码；成功返回VPSS_SUCCESS
-----------------------------------------------------------------------------*/
s32 VpssGrpxOpen(u32 dwGrpxId, TVpssGrpxParam *ptGrpxParam);

/*==============================================================================
    函数名      : VpssGrpxClose
    功能        : 关闭指定GRPX口
    输入参数说明: dwGrpxId: GRPX口的ID号，如: VPSS_GRPX0
    返回值说明  : 错误返回VPSS_FAILURE或错误码；成功返回VPSS_SUCCESS
-----------------------------------------------------------------------------*/
s32 VpssGrpxClose(u32 dwGrpxId);

/*==============================================================================
    函数名      : VpssGrpxDequeue
    功能        : 从播放空队列中取一组buf列表
    输入参数说明: 
    返回值说明  : 错误返回VPSS_FAILURE或错误码；成功返回VPSS_SUCCESS
------------------------------------------------------------------------------*/
s32 VpssGrpxDequeue(u32 dwGrpxId, TVpssFrameList *ptFrameList, u32 dwStreamId, s32 nTimeout);

/*==============================================================================
    函数名      : VpssGrpxQueue
    功能        : 放入一组buf列表到播放队列
    输入参数说明: 
    返回值说明  : 错误返回VPSS_FAILURE或错误码；成功返回VPSS_SUCCESS
------------------------------------------------------------------------------*/
s32 VpssGrpxQueue(u32 dwGrpxId, TVpssFrameList *ptFrameList, u32 dwStreamId);

/*==============================================================================
    函数名      : VpssGrpxCtrl
    功能        ：设备控制，目前定义了
                  ......
    输入参数说明：dwGrpxId: GRPX口的ID号，如: VPSS_GRPX0
                  nCmd: 操作码；pArgs: 参数指针 详见: VpssGrpxCtrl操作码定义
    返回值说明  : 错误返回VPSS_FAILURE或错误码；成功返回VPSS_SUCCESS
------------------------------------------------------------------------------*/
s32 VpssGrpxCtrl(u32 dwGrpxId, s32 nCmd, void *pArgs);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __VPSS_API_GRPX_H */
