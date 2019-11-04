/******************************************************************************
模块名  ： VPSS_DRV_API
文件名  ： vpss_api_m2m_sc.h
相关文件： vpss_api_m2m_sc.c
文件实现功能：
作者    ：张方明
版本    ：1.0.0.0.0
-------------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
04/25/2011  1.0         张方明      创建
******************************************************************************/
#ifndef __VPSS_API_M2M_SC_H
#define __VPSS_API_M2M_SC_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "vpss_api_core.h"

/* -------------------------------- 宏定义 ----------------------------------*/
/* dwM2mScId定义 */
#define VPSS_M2M_INST_SEC0_SC5_WB2          (0u)    /* 0 1 2这3路同时只能 */
#define VPSS_M2M_INST_BP0_SC5_WB2           (1u)    /* 打开一路，因为它们 */
#define VPSS_M2M_INST_BP1_SC5_WB2           (2u)    /* 共用SC5 */
#define VPSS_M2M_INST_SEC0_SC3_VIP0         (3u)    /* 3和0由于共用SEC0互斥 */
#define VPSS_M2M_INST_SEC1_SC4_VIP1         (4u)
#define VPSS_M2M_INST_HDMI_SC5_WB2          (5u)    /* hdmi blend -> sc5 -> write back to mem  */
#define VPSS_M2M_SC_INST_MAX                (6u)

#define VPSS_M2M_SC_MAX_HANDLE_PER_INST            20
#define VPSS_M2M_SC_MAX_CH                  (36u)   /* 所有端口加起来最多不能超过36个channel */

/* dwCfgMode宏定义 */
#define VPSS_M2M_CONFIG_PER_HANDLE          0   /* 打开的端口设备所有通道采用相同的参数 */
#define VPSS_M2M_CONFIG_PER_CHANNEL         1   /* 打开的端口设备所有通道采用不同的参数 */

/* dwVertScType宏定义 */
#define VPSS_SC_VST_POLYPHASE   0 /* Selects polyphase filter. Used for both down as well as up scaling. */
#define VPSS_SC_VST_RAV         1 /* Uses Running Average Filter. Used for down scaling only. Vertical
                                     Scaling ratio <= 0.5x should use RAV. */

/* VpssM2mScCtrl操作码定义 */
#define VPSS_M2M_SC_SET_XXX                 0   /* pArgs对应(TVpssM2mScRtXXX *) */

/* ------------------------------- 类型定义 ---------------------------------*/


/* ------------------------------- 结构定义 ---------------------------------*/
/* 结构定义 */
typedef struct{
    TVpssVidStd     tInVidStd;                  /* 缩放前的图像参数 */
    TVpssVidStd     tOutVidStd;                 /* 缩放后的图像参数 */

    u32             dwInPitch[VPSS_MAX_PLANES]; /* 连续2行第一个像素每个分量数据之间的字节数，用户传0时由驱动根据
                                                   输入视频制式自动计算，如果用户指定需要16字节对齐 */
    u32             dwOutPitch[VPSS_MAX_PLANES];/* 同上 */

    u32             dwInMemType;                /* VPSS_VPDMA_MT_NONTILEDMEM,VPSS_VPDMA_MT_TILEDMEM */
    u32             dwOutMemType;               /* VPSS_VPDMA_MT_NONTILEDMEM,VPSS_VPDMA_MT_TILEDMEM */

    u32             dwCropStartX;               /* 对原始图像裁剪起始位置X坐标 */
    u32             dwCropStartY;               /* 对原始图像裁剪起始位置Y坐标 */
    u32             dwCropWidth;                /* 对原始图像裁剪后的宽度，0=不裁剪 */
    u32             dwCropHeight;               /* 对原始图像裁剪起的高度，0=不裁剪 */

    u32             dwVertScType;               /* 垂直方向缩放处理方法，如dwVertScType宏定义 */
    BOOL32          bNonlinearScaling;          /* 非线性缩放标志 */
    u32             dwStripSize;                /* Strip size for the non linear scaling. */
    u32             dwScBypass;                 /* Scalar should be bypassed or not. */
    u32             dwSubFrameProcEn;           /* 是否启用分块处理，目前先不支持，用户填0 */
    u32             dwNumSubFrames;             /* 启用分块处理时分几块，每块的图片高度为原始高度的1/dwNumSubFrames */
} TVpssM2mScChParam;

typedef struct{
    u32             dwChnlNum;                      /* 创建几个通道，每个通道可以处理一路图片的缩放处理，
                                                       当然处理调用时每个通道必须给定framelist */
    u32             dwCfgMode;                      /* 配置模式，如: dwCfgMode宏定义 */
    TVpssM2mScChParam atChParam[VPSS_M2M_SC_MAX_CH];/* 每个通道的参数 */
} TVpssM2mScParam;


/* 函数声明 */
/*==============================================================================
    函数名      : VpssM2mScOpen
    功能        : 打开指定M2M_SC端口
    输入参数说明: dwM2mScId: M2M_SC端口的ID号，如: VPSS_M2M_INST_SEC0_SC5_WB2
                  ptM2mScParam: M2M_SC端口参数
    返回值说明  : 错误返回VPSS_FAILURE或错误码；成功返回VPSS_SUCCESS
-----------------------------------------------------------------------------*/
s32 VpssM2mScOpen(u32 dwM2mScId, u32 dwHdlId, TVpssM2mScParam *ptM2mScParam);

/*==============================================================================
    函数名      : VpssM2mScClose
    功能        : 关闭指定M2M_SC端口
    输入参数说明: dwM2mScId: M2M_SC端口的ID号，如: VPSS_M2M_INST_SEC0_SC5_WB2
    返回值说明  : 错误返回VPSS_FAILURE或错误码；成功返回VPSS_SUCCESS
-----------------------------------------------------------------------------*/
s32 VpssM2mScClose(u32 dwM2mScId, u32 dwHdlId);

/*==============================================================================
    函数名      : VpssM2mScProcessFrames
    功能        : 缩放处理
    输入参数说明: dwM2mScId: M2M_SC端口的ID号，如: VPSS_M2M_INST_SEC0_SC5_WB2
    返回值说明  : 错误返回VPSS_FAILURE或错误码；成功返回VPSS_SUCCESS
------------------------------------------------------------------------------*/
s32 VpssM2mScProcessFrames(u32 dwM2mScId, u32 dwHdlId, TVpssProcessList *ptProcList, s32 nTimeout);

/*==============================================================================
    函数名      : VpssM2mScCtrl
    功能        ：设备控制，目前定义了
                  ......
    输入参数说明：dwM2mScId: M2M_SC端口的ID号，如: VPSS_M2M_INST_SEC0_SC5_WB2
                  nCmd: 操作码；pArgs: 参数指针 详见: VpssM2mScCtrl操作码定义
    返回值说明  : 错误返回VPSS_FAILURE或错误码；成功返回VPSS_SUCCESS
------------------------------------------------------------------------------*/
s32 VpssM2mScCtrl(u32 dwM2mScId, u32 dwHdlId, s32 nCmd, void *pArgs);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __VPSS_API_M2M_SC_H */
