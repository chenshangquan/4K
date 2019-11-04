/******************************************************************************
模块名  ： VPSS_DRV_API
文件名  ： vpss_api_m2m_nf.h
相关文件： vpss_api_m2m_nf.c
文件实现功能：
作者    ：张方明
版本    ：1.0.0.0.0
-------------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
05/06/2011  1.0         张方明      创建
******************************************************************************/
#ifndef __VPSS_API_M2M_NF_H
#define __VPSS_API_M2M_NF_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "vpss_api_core.h"

/* -------------------------------- 宏定义 ----------------------------------*/
/* dwM2mNfId定义 */
#define VPSS_M2M_INST_NF0                   (0u)    /* 就1个端口设备 */
#define VPSS_M2M_NF_INST_MAX                (1u)

#define VPSS_M2M_NF_MAX_CH                  (16u)   /* 所有端口加起来最多不能超过16个channel */
#define VPSS_M2M_NF_MAX_HANDLES             (4u)    /* 1个端口设备最多可以创建多少次，目前只支持创建1次 */

/* dwBypassMode宏定义 */
#define VPSS_NSF_DISABLE_NONE               (0u)    /* Full NF, Spatial NF ON + Temporal NF ON */
#define VPSS_NSF_DISABLE_SNF                (1u)    /* Only Temporal NF ON, Spatial NF bypassed */
#define VPSS_NSF_DISABLE_TNF                (2u)    /* Only Spatial NF ON, Temporal NF bypassed */
#define VPSS_NSF_DISABLE_SNF_TNF            (3u)    /* No NF, Only YUV422 to YUV420 downsample ON */

/* VpssM2mNfCtrl操作码定义 */
#define VPSS_M2M_NF_SET_XXX                 0   /* pArgs对应(TVpssM2mNfRtXXX *) */

/* ------------------------------- 类型定义 ---------------------------------*/


/* ------------------------------- 结构定义 ---------------------------------*/
/* 结构定义 */
typedef struct{
    u32             dwInWidth;                  /* 噪声滤波处理的图像宽度,必须是32的整数倍 */
    u32             dwInHeight;                 /* 噪声滤波处理的图像高度,必须是32的整数倍 */
    u32             dwInPitch[VPSS_MAX_PLANES]; /* 连续2行第一个像素每个分量数据之间的字节数，用户传0时由驱动根据
                                                   输入视频制式自动计算，如果用户指定需要32字节对齐, 输入格式固定为YUV422I_YUYV */
    u32             dwOutPitch[VPSS_MAX_PLANES];/* 同上，输出格式固定为YUV420SP_UV */

    u32             dwInMemType;                /* VPSS_VPDMA_MT_NONTILEDMEM,VPSS_VPDMA_MT_TILEDMEM */
    u32             dwOutMemType;               /* VPSS_VPDMA_MT_NONTILEDMEM,VPSS_VPDMA_MT_TILEDMEM */
} TVpssM2mNfDataFormat;

/* This structure is changed ,please note it!!!  */

typedef struct{
    u32             dwBypassMode;
    /* 详见: dwBypassMode宏定义 */               
    u32             dwSubFrameProcEn;
    /* 是否启用分块处理，目前先不支持，用户填0 */           
    u32             dwNumLinesPerSubFrame;
    /* 启用分块处理时每块的图片高度，即行数 */      
    u32             frameNoiseAutoCalcEnable;
  /**< TRUE: "frameNoise" auto-calculated by HW,
   *  FALSE: auto-calculation disabled, staticFrameNoise[] used instead */

    u32             frameNoiseCalcReset;
  /**< TRUE: "frameNoise" calculation is reset,
   *  FALSE: "frameNoise" calculation is not reset
   *  Use this when changing input stream or input resolution or
   *  for the first frame of processing.
   */

    //u32             subFrameModeEnable;
  /**< TRUE: SubFrame based NSF is ON,
   *   Vps_NsfPerFrameCfgSubFrameCfg must be set for FVID2_Frame.perFrameCfg,
   *  FALSE: Frame/field based NSF  */

    //u32             numLinesPerSubFrame;
  /**< Num lines per subframe, except for last subframe. */

    u32             staticFrameNoise[VPSS_MAX_PLANES];
  /**< Static "frameNoise", valid only when frameNoiseAutoCalcEnable = FALSE */

    u32             spatialStrengthLow[VPSS_MAX_PLANES];
  /**< Advanced NSF parameters, refer to NSF spec for details,
   *  set to VPS_NSF_PROCESSING_CFG_DEFAULT for default values  */

    u32             spatialStrengthHigh[VPSS_MAX_PLANES];
  /**< Advanced NSF parameters, refer to NSF spec for details,
   *  set to VPS_NSF_PROCESSING_CFG_DEFAULT for default values  */

    u32             temporalStrength;
  /**< Advanced NSF parameters, refer to NSF spec for details,
   *  set to VPS_NSF_PROCESSING_CFG_DEFAULT for default values  */

    u32             temporalTriggerNoise;
  /**< Advanced NSF parameters, refer to NSF spec for details,
   *  set to VPS_NSF_PROCESSING_CFG_DEFAULT for default values  */

    u32             noiseIirCoeff;
  /**< Advanced NSF parameters, refer to NSF spec for details,
   *  set to VPS_NSF_PROCESSING_CFG_DEFAULT for default values  */

    u32             maxNoise;
  /**< Advanced NSF parameters, refer to NSF spec for details,
   *  set to VPS_NSF_PROCESSING_CFG_DEFAULT for default values  */

    u32             pureBlackThres;
  /**< Advanced NSF parameters, refer to NSF spec for details,
   *  set to VPS_NSF_PROCESSING_CFG_DEFAULT for default values  */

    u32             pureWhiteThres;
  /**< Advanced NSF parameters, refer to NSF spec for details,
   *  set to VPS_NSF_PROCESSING_CFG_DEFAULT for default values  */
} TVpssM2mNfProcingCfg;

typedef struct{
    u32             dwChnlNum;                      /* 创建几个通道，每个通道可以处理一路图片的噪声滤波处理，
                                                       当然处理调用时每个通道必须给定framelist */
    TVpssM2mNfDataFormat atDataFormat[VPSS_M2M_NF_MAX_CH];/* 每个通道的数据格式 */
    TVpssM2mNfProcingCfg atProcingCfg[VPSS_M2M_NF_MAX_CH];/* 每个通道的滤波处理配置 */
} TVpssM2mNfParam;


/* 函数声明 */
/*==============================================================================
    函数名      : VpssM2mNfOpen
    功能        : 打开指定M2M_NF端口
    输入参数说明: dwM2mNfId: M2M_NF端口的ID号，如: VPSS_M2M_INST_NF0
                  ptM2mNfParam: M2M_NF端口参数
    返回值说明  : 错误返回VPSS_FAILURE或错误码；成功返回VPSS_SUCCESS
-----------------------------------------------------------------------------*/
s32 VpssM2mNfOpen(u32 dwM2mNfId, TVpssM2mNfParam *ptM2mNfParam);

/*==============================================================================
    函数名      : VpssM2mNfClose
    功能        : 关闭指定M2M_NF端口
    输入参数说明: dwM2mNfId: M2M_NF端口的ID号，如: VPSS_M2M_INST_NF0
    返回值说明  : 错误返回VPSS_FAILURE或错误码；成功返回VPSS_SUCCESS
-----------------------------------------------------------------------------*/
s32 VpssM2mNfClose(u32 dwM2mNfId);

/*==============================================================================
    函数名      : VpssM2mNfProcessFrames
    功能        : 噪声滤波处理
    输入参数说明: dwM2mNfId: M2M_NF端口的ID号，如: VPSS_M2M_INST_NF0
    返回值说明  : 错误返回VPSS_FAILURE或错误码；成功返回VPSS_SUCCESS
------------------------------------------------------------------------------*/
s32 VpssM2mNfProcessFrames(u32 dwM2mNfId, TVpssProcessList *ptProcList, s32 nTimeout);

/*==============================================================================
    函数名      : VpssM2mNfCtrl
    功能        ：设备控制，目前定义了
                  ......
    输入参数说明：dwM2mNfId: M2M_NF端口的ID号，如: VPSS_M2M_INST_NF0
                  nCmd: 操作码；pArgs: 参数指针 详见: VpssM2mNfCtrl操作码定义
    返回值说明  : 错误返回VPSS_FAILURE或错误码；成功返回VPSS_SUCCESS
------------------------------------------------------------------------------*/
s32 VpssM2mNfCtrl(u32 dwM2mNfId, s32 nCmd, void *pArgs);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __VPSS_API_M2M_NF_H */
