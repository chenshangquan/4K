/******************************************************************************
模块名  ： VPSS_DRV_API
文件名  ： vpss_api_m2m_dei.h
相关文件： vpss_api_m2m_dei.c
文件实现功能：
作者    ：hcj
版本    ：1.0.0.0.0
-------------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
04/12/2011  1.0         hcj         创建
06/03/2011  1.1         张方明      增加多handle的支持
******************************************************************************/
#ifndef __VPSS_API_M2M_DEI_H
#define __VPSS_API_M2M_DEI_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "vpss_api_core.h"

/* -------------------------------- 宏定义 ----------------------------------*/

/* dwDeiId定义 */
#define VPSS_M2M_INST_MAIN_DEIH_SC1_WB0             0x0 /* DEI HQ writeback memory driver instance number */
#define VPSS_M2M_INST_AUX_DEI_SC2_WB1               0x1 /* DEI writeback memory driver instance number */
#define VPSS_M2M_INST_MAIN_DEIH_SC3_VIP0            0x2 /* DEI HQ-VIP0 memory driver instance number */
#define VPSS_M2M_INST_AUX_DEI_SC4_VIP1              0x3 /* DEI VIP1 memory driver instance number */
#define VPSS_M2M_INST_MAIN_DEIH_SC1_SC3_WB0_VIP0    0x4 /* DEI HQ-WRBK-VIP0 dual output memory driver instance number */
#define VPSS_M2M_INST_AUX_DEI_SC2_SC4_WB1_VIP1      0x5 /* DEI WRBK-VIP1 dual output memory driver instance number */
#define VPSS_M2M_DEI_INST_MAX                       0x6

#define VPSS_M2M_DEI_FRAME_LIST_MAX                 16

#define VPSS_M2M_DEI_MAX_HANDLE_PER_INST            4
#define VPSS_M2M_DEI_CH_PER_INST_MAX                16
#define VPSS_M2M_DEIH_REF_FRM_MAX_SIZE              (1920 * 1088 * 4 + 1920 * 272 * 3 * 2)
#define VPSS_M2M_DEIM_REF_FRM_MAX_SIZE              (1920 * 1088 * 3 + 1920 * 272 * 2)

/* dwCfgMode宏定义 */
#define VPSS_M2M_DEI_CONFIG_PER_HANDLE          0   /* 打开的端口设备所有通道采用相同的参数 */
#define VPSS_M2M_DEI_CONFIG_PER_CHANNEL         1   /* 打开的端口设备所有通道采用不同的参数 */

/* VpssM2mDeiCtrl操作码定义 */


/* ------------------------------- 类型定义 ---------------------------------*/


/* ------------------------------- 结构定义 ---------------------------------*/
typedef struct{
    TVpssVidStd     tInVidStd;      /* DEI处理前的图像参数 */
    TVpssVidStd     tDeiOutVidStd;  /* DEI处理后回写的图像参数 */
    TVpssVidStd     tVipOutVidStd;  /* DEI处理并经过VIP的图像参数 */

    u32             dwInPitch[VPSS_MAX_PLANES]; /* 连续2行第一个像素每个分量数据之间的字节数，用户传0时由驱动根据
                                                   输入视频制式自动计算，如果用户指定需要16字节对齐 */
    u32             dwDeiOutPitch[VPSS_MAX_PLANES]; /* 同上 */
    u32             dwVipOutPitch[VPSS_MAX_PLANES]; /* 同上 */

    u32             dwInMemType;    /* VPSS_VPDMA_MT_NONTILEDMEM,VPSS_VPDMA_MT_TILEDMEM */
    u32             dwDeiOutMemType;/* 该输出口为YUYV格式，只能是VPSS_VPDMA_MT_NONTILEDMEM */
    u32             dwVipOutMemType;/* VPSS_VPDMA_MT_NONTILEDMEM,VPSS_VPDMA_MT_TILEDMEM */

    u32             dwDrnEnable;    /* Enables/disables the DRN module in the DEI path. */
    u32             dwComprEnable;  /* Enable compression/decompression for writing back the DEI context
                                       to and from DDR. */
} TVpssM2mDeiChParam;

typedef struct{
    u32             dwChnlNum;                      /* 创建几个通道，每个通道可以处理一路图片的DEI处理，
                                                      当然处理调用时每个通道必须给定framelist */
    void            *UsrRefFrameVaddr;
    u32             UsrRefFramePaddr;
    u32             dwCfgMode;                      /* 配置模式，如: dwCfgMode宏定义 */
    TVpssM2mDeiChParam atChParam[VPSS_M2M_DEI_CH_PER_INST_MAX]; /* 每个通道的参数 */
} TVpssM2mDeiParams;

/* 函数声明 */
/*==============================================================================
    函数名      : VpssM2mDeiOpen
    功能        : 打开指定DEI口
    输入参数说明: dwDeiId: DEI口的ID号，如: VPSS_M2M_INST_MAIN_DEIH_SC1_WB0
                  ptCapParams: DEI口参数
    返回值说明  : 错误返回VPSS_FAILURE或错误码；成功返回VPSS_SUCCESS
-----------------------------------------------------------------------------*/
s32 VpssM2mDeiOpen(u32 dwDeiId, u32 dwHdlId, TVpssM2mDeiParams *ptDeiParams);

/*==============================================================================
    函数名      : VpssM2mDeiClose
    功能        : 关闭指定DEI口
    输入参数说明: dwDeiId: DEI口的ID号，如: VPSS_M2M_INST_MAIN_DEIH_SC1_WB0
    返回值说明  : 错误返回VPSS_FAILURE或错误码；成功返回VPSS_SUCCESS
-----------------------------------------------------------------------------*/
s32 VpssM2mDeiClose(u32 dwDeiId, u32 dwHdlId);

/*==============================================================================
    函数名      : VpssM2mDeiProcessFrames
    功能        : DEI处理处理
    输入参数说明: dwDeiId: DEI口的ID号，如: VPSS_M2M_INST_MAIN_DEIH_SC1_WB0
    返回值说明  : 错误返回VPSS_FAILURE或错误码；成功返回VPSS_SUCCESS
==============================================================================*/
s32 VpssM2mDeiProcessFrames(u32 dwDeiId, u32 dwHdlId, TVpssProcessList *ptProcList, s32 nTimeout);

/*==============================================================================
    函数名      : VpssM2mDeiCtrl
    功能        ：设备控制，目前定义了
                  ......
    输入参数说明：dwDeiId: DEI口的ID号，如: VPSS_M2M_INST_MAIN_DEIH_SC1_WB0
                  nCmd: 操作码；pArgs: 参数指针 详见: VpssM2mDeiCtrl操作码定义
    返回值说明  : 错误返回VPSS_FAILURE或错误码；成功返回VPSS_SUCCESS
------------------------------------------------------------------------------*/
s32 VpssM2mDeiCtrl(u32 dwDeiId, u32 dwHdlId, s32 nCmd, void *pArgs);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __VPSS_API_M2M_DEI_H */
