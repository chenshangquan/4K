/******************************************************************************
模块名  ： VPSS_DRV_API
文件名  ： vpss_api_cap.h
相关文件： vpss_api_cap.c
文件实现功能：
作者    ：张方明
版本    ：1.0.0.0.0
-------------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
04/12/2011  1.0         hcj         创建
******************************************************************************/
#ifndef __VPSS_API_CAP_H
#define __VPSS_API_CAP_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "vpss_api_core.h"
#include "vpss_api_dctrl.h"
#include "vpss_api_frame_mem.h"

/* -------------------------------- 宏定义 ----------------------------------*/
/* dwCapId定义 */
#define VPSS_CAP_INST_VIP0_PORTA            0x0
#define VPSS_CAP_INST_VIP0_PORTB            0x1
#define VPSS_CAP_INST_VIP1_PORTA            0x2
#define VPSS_CAP_INST_VIP1_PORTB            0x3
#define VPSS_CAP_MAX                        0x4

#define VPSS_CAP_FRAME_LIST_MAX             16

#define VPSS_CAP_STREAM_ID_MAX              4
#define VPSS_CAP_CH_PER_PORT_MAX            16

/* VpssCapCtrl操作码定义 */


/* ------------------------------- 类型定义 ---------------------------------*/


/* ------------------------------- 结构定义 ---------------------------------*/
/* 结构定义 */
typedef struct{
    u32             dwDataFormat;               /* 输出的色域空间,如果dwNumStream大于1的话同时只能有1路支持YUV422_SP */
    u32             dwScEnable;                 /* 使能Scale */
    u32             dwMemType;                  /* VPSS_VPDMA_MT_NONTILEDMEM,VPSS_VPDMA_MT_TILEDMEM */
    u32             dwFrameSkipMask;            /* frame skip mask for sequence of 30frames
                                                 * bit0..bit29: bitX = 1, skip frame, else capture frame
                                                 */
} TStreamInfo;

typedef struct{
    u32             dwInWidth;                  /* 输入的视频宽度 */
    u32             dwInHeight;                 /* 输入的视频高度 */
    u32             dwOutWidth;                 /* 输出的视频宽度 */
    u32             dwOutHeight;                /* 输出的视频高度 */
    u32             dwCropStartX;               /* 裁减的x坐标 */
    u32             dwCropStartY;               /* 裁减的y坐标 */
    u32             dwCropWidth;                /* 裁减下的宽度 */
    u32             dwCropHeight;               /* 裁减下的高度 */
} TVpssCapScParams;

typedef struct{
    BOOL32          bvipCropEnable;             /* 是否使用VIP自带的crop模块裁剪图像，仅PG2.0开始的8168和PG2.1开始的8148才支持 */
    u32             dwCropStartX;               /* 裁减的x坐标 */
    u32             dwCropStartY;               /* 裁减的y坐标 */
    u32             dwCropWidth;                /* 裁减后的宽度 */
    u32             dwCropHeight;               /* 裁减后的高度 */
} TVpssCapVipCrop;

typedef struct{
    TVpssVidStd     tVidStd;                    /* 对应的输入的信号制式 */

    u32             dwFrameListNum;             /* 分配几个帧buf链,范围:1-VPSS_CAP_FRAME_LIST_MAX, 0=默认5个（小于5个会卡why?） */

    u32             dwNumCh;                    /* 每个port口有几路video */

    u32             dwNumStream;                /* 分成几路 stream 上来 */

    u32             dwUsrFrameNum;              /* 为0表示由驱动分配buf, >0为用户分配的buf个数，
                                                   至少分配 dwFrameListNum*dwNumCh*dwNumStream个，
                                                   必须用VpssFrameAlloc函数分配，且Tiler内存无法释放，用户最好静态分配好最多最大的内存 */
    TVpssFrame      *ptUsrFrames;               /* 为NULL表示由驱动分配buf, 否则为用户分配的buf描述数组首地址 */


    TStreamInfo     tStreamInfo[VPSS_CAP_STREAM_ID_MAX];
                                                /* 每个窗口区域的参数 */

    TVpssCapScParams   tVpssCapScParams;        /* 缩放参数，必须置上使能Scale, 2路同时使用缩放的话输出的分辨率是一样的缩小后的宽高
                                                   且采集通道中SC不能做UpScale */

    BOOL32          bFieldMerged;               /* 对于隔行信号来说可以设置2场合并为1帧后Deque出来处理 */
    TVpssCapVipCrop tVipCrop;                   /* VIP自带的crop模块参数，仅PG2.0开始的8168和PG2.1开始的8148才支持 */
} TVpssCapParams;

/* 函数声明 */
/*==============================================================================
    函数名      : VpssCapOpen
    功能        : 打开指定CAP口
    输入参数说明: dwCapId: CAP口的ID号，如: VPSS_CAP_INST_VIP0_PORTA
                  ptCapParams: CAP口参数
        !!!几个限制：
        1、缩放参数必须置上对应stream的使能Scale参数, 2路同时使用缩放的话输出的
           分辨率是一样的缩小后的宽高；
        2、采集通道中SC不能做UpScale，宽高都不行
        3、如果dwNumStream大于1即采2路的话同时只能有1路支持YUV422_SP格式(dwDataFormat)
           可以2路YUYV、2路YUV420_SP或混杂，就是不能2路都是YUV422_SP，芯片能力限制不支持；
    返回值说明  : 错误返回VPSS_FAILURE或错误码；成功返回VPSS_SUCCESS
-----------------------------------------------------------------------------*/
s32 VpssCapOpen(u32 dwCapId, TVpssCapParams *ptCapParams);

/*==============================================================================
    函数名      : VpssCapClose
    功能        : 关闭指定CAP口
    输入参数说明: dwCapId: CAP口的ID号，如: VPSS_CAP_INST_VIP0_PORTA
    返回值说明  : 错误返回VPSS_FAILURE或错误码；成功返回VPSS_SUCCESS
-----------------------------------------------------------------------------*/
s32 VpssCapClose(u32 dwCapId);

/*==============================================================================
    函数名      : VpssCapDequeue
    功能        : 从采集空队列中取一组buf列表
    输入参数说明:
    返回值说明  : 错误返回VPSS_FAILURE或错误码；成功返回VPSS_SUCCESS
------------------------------------------------------------------------------*/
s32 VpssCapDequeue(u32 dwCapId, TVpssFrameList *ptFrameList, u32 dwStreamId, s32 nTimeout);

/*==============================================================================
    函数名      : VpssCapQueue
    功能        : 放入一组buf列表到采集队列
    输入参数说明:
    返回值说明  : 错误返回VPSS_FAILURE或错误码；成功返回VPSS_SUCCESS
------------------------------------------------------------------------------*/
s32 VpssCapQueue(u32 dwCapId, TVpssFrameList *ptFrameList, u32 dwStreamId);

/*==============================================================================
    函数名      : VpssCapCtrl
    功能        ：设备控制，目前定义了
                  ......
    输入参数说明：dwCapId: CAP口的ID号，如: VPSS_CAP_INST_VIP0_PORTA
                  nCmd: 操作码；pArgs: 参数指针 详见: VpssCapCtrl操作码定义
    返回值说明  : 错误返回VPSS_FAILURE或错误码；成功返回VPSS_SUCCESS
------------------------------------------------------------------------------*/
s32 VpssCapCtrl(u32 dwCapId, s32 nCmd, void *pArgs);

/*==============================================================================
    函数名      : VpssCapPrtStatus
    功能        ：打印状态
    输入参数说明：dwCapId: CAP口的ID号，如: VPSS_CAP_INST_VIP0_PORTA
    返回值说明  : 错误返回VPSS_FAILURE或错误码；成功返回VPSS_SUCCESS
------------------------------------------------------------------------------*/
s32 VpssCapPrtStatus(u32 dwCapId);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __VPSS_API_CAP_H */
