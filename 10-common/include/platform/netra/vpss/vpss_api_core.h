/******************************************************************************
模块名  ： VPSS_DRV_API
文件名  ： vpss_api_core.h
相关文件： vpss_api_core.c
文件实现功能：
作者    ：张方明
版本    ：1.0.0.0.0
-------------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
03/29/2011  1.0         张方明      创建
******************************************************************************/
#ifndef __VPSS_API_CORE_H
#define __VPSS_API_CORE_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/****************************** 模块的版本号命名规定 *************************
总的结构：mn.mm.ii.cc.tttt
     如  Osp 1.1.7.20040318 表示
模块名称Osp
模块1版本
接口1版本
实现7版本
04年3月18号提交

版本修改记录：
----------------------------------------------------------------------------
模块版本: VpssDrvApi 1.1.1.20110329
增加功能: 创建
修改缺陷: 无
提交人:   张方明

****************************************************************************/

#include "kdvtype.h"
#include "vpss_api_def.h"
#include "brdwrapperdef.h"

/* 版本信息 */
#define VPSSDRV_MOD_VERSION             ( const char * )"VpssDrvApi 1.1.1.20110329"


/* 返回值宏定义 */
#define VPSS_SUCCESS                    0           /* 成功 */
#define VPSS_SMEM_CORRUPT               1           /* 共享内存区被破坏 */
#define VPSS_LENGTH_ERROR               2           /* 长度错误 */
#define VPSS_QUEUE_FULL                 3           /* 队列已满 */
#define VPSS_QUEUE_EMPTY                4           /* 队列空 */
#define VPSS_MSG_LOST                   5           /* 消息丢失 */
#define VPSS_PARAM_ERR                  6           /* 参数错误 */
#define VPSS_NOT_SUPPORT                7           /* 不支持的操作 */
#define VPSS_MULTI_OPEN                 8           /* 多次打开设备 */
#define VPSS_NOT_OPEN                   9           /* 设备没有打开 */
#define VPSS_TIMEOUT                    10          /* 操作超时 */
#define VPSS_OPEN_FAIL                  11          /* 设备打开失败 */
#define VPSS_IOC_FAIL                   12          /* 设备ioctl失败 */
#define VPSS_NO_MEM                     13          /* 内存不足 */
#define VPSS_MEM_ERR                    14          /* 内存错误 */
#define vpss_DEL_FAIL                   15          /* 设备删除失败*/
#define VPSS_FAILURE                    -1          /* 未知错误 */

/* 常用极限宏定义 */
#define VPSS_MAX_FRAMES_PER_LIST        (64u)       /* 每个链最大支持的帧数 */
#define VPSS_MAX_PLANES                 (3u)        /* 最多3层数据，即YUV planar format - Y, Cb and Cr */
#define VPSS_MAX_FIELDS                 (2u)        /* 最多2场 */

#define VPSS_MAX_IN_OUT_PROCESS_LISTS   (4u)

/* dwFid 定义 */
#define VPSS_FID_TOP                    0           /* top field */
#define VPSS_FID_BOTTOM                 1           /* Bottom field */
#define VPSS_FID_FRAME                  2           /* Frame mode - Contains both the fields or a progressive frame. */

/* 视频格式掩码定义 */
#define VPSS_VID_STD_MASK_EMBSYNC       0x80000000  /* 同步模式掩码，1=集成同步，0=外同步 */
#define VPSS_VID_STD_MASK_SD_16BIT      0x40000000  /* 标清分辨率采用16位格式传输标志，针对576i/480i */
#define VPSS_VID_STD_MASK_COLORSPACE    0x000000ff  /* 色度空间掩码，填充色度空间定义，占用低8位 */
#define VPSS_VID_STD_MASK_CAPMODE       0x000f0000  /* 采集模式掩码，填充: 采集模式定义 */
#define VPSS_VID_STD_MASK_INTF_MODE     0x00f00000  /* 接口模式，填充: 接口模式定义 */

/* 色度空间定义 */
#define VPSS_VID_COLORSPACE_YUV422          0       /* YUV422格式 */
#define VPSS_VID_COLORSPACE_RGB888          1       /* RGB888格式 */
#define VPSS_VID_COLORSPACE_RGB444          2       /* RGB444格式 */
#define VPSS_VID_COLORSPACE_RAW16BIT        3       /* 16位裸数据格式 */
#define VPSS_VID_COLORSPACE_RGB565          4       /* RGB565格式 */
#define VPSS_VID_COLORSPACE_YUV422I_YUYV    5       /* 16位YUV422I_YUYV格式 */
#define VPSS_VID_COLORSPACE_YUV422SP_UV     6       /* 16位YUV 422 Semi-Planar - Y separate, UV interleaved. */
#define VPSS_VID_COLORSPACE_YUV420SP_UV     7       /* 12位YUV 420 Semi-Planar - Y separate, UV interleaved. */
#define VPSS_VID_COLORSPACE_YUV444          8       /* YUV444格式 */

/* 采集模式定义 */
#define VPSS_VID_CAPMODE_SINGLE_CH_NON_MUX_EMBEDDED_SYNC        0 /* Single Channel non multiplexed mode */
#define VPSS_VID_CAPMODE_MULTI_CH_LINE_MUX_EMBEDDED_SYNC        1 /* Multi-channel line-multiplexed mode */
#define VPSS_VID_CAPMODE_MULTI_CH_PIXEL_MUX_EMBEDDED_SYNC       2 /* Multi-channel pixel muxed */
#define VPSS_VID_CAPMODE_SINGLE_CH_NON_MUX_DISSYNC_HSYNC_VBLK   3 /* Single Channel non multiplexed
                                                                   discrete sync mode with HSYNC and
                                                                   VBLK as control signals. */
#define VPSS_VID_CAPMODE_SINGLE_CH_NON_MUX_DISSYNC_HSYNC_VSYNC  4 /**< Single Channel non multiplexed
                                                                    discrete sync mode with HSYNC and
                                                                    VSYNC as control signals. */
#define VPSS_VID_CAPMODE_SINGLE_CH_NON_MUX_DISSYNC_ACTVID_VBLK  5 /* Single Channel non multiplexed
                                                                    discrete sync mode with ACTVID and
                                                                    VBLK as control signals. */
#define VPSS_VID_CAPMODE_SINGLE_CH_NON_MUX_DISSYNC_ACTVID_VSYNC 6 /* Single Channel non multiplexed
                                                                    discrete sync mode with ACTVID and
                                                                    VBLK as control signals. */
#define VPSS_VID_CAPMODE_MULTI_CH_LINE_MUX_SPLIT_LINE_EMBEDDED_SYNC 7 /* Multi-channel line-multiplexed mode - split line mode */

/* 接口模式定义 */
#define VPSS_VID_IF_MODE_AUTO               0   /* 由驱动根据分辨率设置默认的接口模式  */
#define VPSS_VID_IF_MODE_8BIT               1   /* 8bit - BT656 standard  */
#define VPSS_VID_IF_MODE_16BIT              2   /* 16bit - BT1120 standard  */
#define VPSS_VID_IF_MODE_24BIT              3   /* 24bit */

/* dwMemType 定义 */
#define VPSS_VPDMA_MT_NONTILEDMEM           0       /* 1D non-tiled memory. */
#define VPSS_VPDMA_MT_TILEDMEM              1       /* 2D tiled memory. */

/* 类型定义 */
typedef void * HVpssHandle;                         /* 通用句柄类型 */

/* 设备身份信息 */
typedef struct{
    u32 dwBrdID;         /* 使用brdwrapperdef.h中单板种类ID号宏定义 */
    u32 dwHwVer;         /* 硬件版本号 */
    u32 dwFpgaVer;       /* EPLD/FPGA/CPLD的程序版本号 */
    u32 dwDspId;         /* 标识当前是哪一块dsp，从0开始编号 */
} TVpssDevInfo;

/* 结构声明 */
/* 视频格式结构定义 */
typedef struct{
    u32	    dwWidth;                    /* 视频宽，像素为单位,为0表示无信号 */
    u32	    dwHeight;                   /* 视频高，行为单位,为0表示无信号 */
    BOOL32  bProgressive;               /* 逐行或隔行，TRUE=逐行；FALSE=隔行 */
    u32     dwFrameRate;                /* 帧率，逐行时=场频，隔行时=场频/2，即60i=30P, 为0表示无信号
                                           如果值大于1000，则认为包含小数点后3位，如59940表示59.940Hz
                                           常用的有60/1.001=59.940; 24/1.001=23.976; 30/1.001=29.970 */
    u32     dwColorSpace;               /* 详见: 视频格式掩码定义 */
} TVpssVidStd;

/* 每帧的描述信息结构 */
typedef struct
{
    /**<
         FVID2 buffer pointers for supporting multiple addresses like
         Y, U, V etc for a given frame. The interpretation of these pointers
         depend on the format configured for the driver.
         The first dimension represents the field and the second dimension
         represents the color plane.
         Not all pointers are valid for a given format.

         Representation of YUV422 Planar Buffer:
         Field 0 Y -> addr[0][0], Field 1 Y -> addr[1][0]
         Field 0 U -> addr[0][1], Field 1 U -> addr[1][1]
         Field 0 V -> addr[0][2], Field 1 V -> addr[1][2]
         Other pointers are not valid.

         Representation of YUV422 Interleaved Buffer:
         Field 0 YUV -> addr[0][0], Field 1 YUV -> addr[1][0]
         Other pointers are not valid.

         Representation of YUV420SP or YUV422SP Buffer:
         Field 0 Y  -> addr[0][0], Field 1 Y  -> addr[1][0]
         Field 0 UV -> addr[0][1], Field 1 UV -> addr[1][1]
         Other pointers are not valid.

         Representation of RGB888 Buffer
         Field 0 RGB -> addr[0][0], Field 1 RGB -> addr[1][0],
         Other pointers are not valid.

         For progressive mode data formats
         or when fields are processed by driver in frame mode.
         addr[1][x] is not used.

         Instead of using numerical for accessing the buffers, the application
         can use the macros defined for each buffer formats like
         FVID2_YUV_INT_ADDR_IDX, FVID2_RGB_ADDR_IDX, FVID2_FID_TOP etc. */
    void   *pbyVirtAddr[VPSS_MAX_FIELDS][VPSS_MAX_PLANES];  /* 帧数据的虚拟地址,具体用法看上面的描述 */
    u32     adwPhyAddr[VPSS_MAX_FIELDS][VPSS_MAX_PLANES];   /* 帧数据的物理地址,可用于DMA操作 */
    u32     dwColorSpace;   /* 视频数据色度空间，如: 色度空间定义 */

    u32     dwMemType;      /* VPSS_VPDMA_MT_NONTILEDMEM,VPSS_VPDMA_MT_TILEDMEM */
    u32     dwImgWidth;     /* 图像的宽度 */
    u32     dwImgHight;     /* 图像的高度 */
    u32     dwImgPitch[VPSS_MAX_PLANES];  /* 图像的一行占用的字节数,最多有3个区域：Y=0, U=1, V=2; Y_UV:Y=0,UV=1; YUYV/RGB只用[0] */
    u32     dwImgSize;      /* 一帧图像的占用的字节数 */

    u32     dwFid;          /* 场标识,如: VPSS_FID_FRAME */
    u32     dwChannelId;    /* 对应的通道号 */
    u32     dwTimeStamp;    /* 时间戳, 毫秒为单位 */
    void    *pDrvData;      /* 驱动私有数据，用户不能修改 */
    void    *pReserved;     /* 备用 */
} TVpssFrame;

typedef struct
{
    u32         dwNumFrames;    /* 实际有多少子画面的帧数据 */
    TVpssFrame  atFrame[VPSS_MAX_FRAMES_PER_LIST];  /* 每个子画面的帧描述 */

    void        *pDrvData;      /* 驱动内部使用的私有数据，用户不能修改 */
    void        *pAppData;      /* 目前没有实现! 用户使用的私有数据，驱动不修改 */
} TVpssFrameList;

typedef struct
{
    TVpssFrameList  *ptInFrameList[VPSS_MAX_IN_OUT_PROCESS_LISTS];
    TVpssFrameList  *ptOutFrameList[VPSS_MAX_IN_OUT_PROCESS_LISTS];
    u32              dwNumInLists;  /* Number of input frame lists */
    u32              dwNumOutLists; /* Number of output frame lists */
    void            *pbyDrvData;    /* 驱动私有数据，用户不能修改 */
    void            *pbyReserved;   /* reserved */
} TVpssProcessList;


/* 函数声明 */
/*==============================================================================
    函数名      : VpssOpen
    功能        : 打开VPSS模块并初始化
    输入参数说明: 无
    返回值说明  : 错误返回VPSS_FAILURE或错误码；成功返回VPSS_SUCCESS
------------------------------------------------------------------------------*/
s32 VpssOpen(TVpssDevInfo *ptVpssDevInfo);

/*==============================================================================
    函数名      : VpssClose
    功能        : 关闭VPSS模块并释放资源
    输入参数说明: 无
    返回值说明  : 错误返回VPSS_FAILURE或错误码；成功返回VPSS_SUCCESS
------------------------------------------------------------------------------*/
s32 VpssClose(TVpssDevInfo *ptVpssDevInfo);

/*==============================================================================
    函数名      : VpssFbufAlloc
    功能        : 申请帧buf，从共享内存中分配，可以被多核访问
    输入参数说明: 无
    返回值说明  : 错误返回VPSS_FAILURE或错误码；成功返回VPSS_SUCCESS
------------------------------------------------------------------------------*/
void *VpssFbufAlloc(u32 dwSize, u32 *pdwPhyAddr);

/*==============================================================================
    函数名      : VpssFbufFree
    功能        : 释放帧buf
    输入参数说明: 无
    返回值说明  : 错误返回VPSS_FAILURE或错误码；成功返回VPSS_SUCCESS
------------------------------------------------------------------------------*/
s32 VpssFbufFree(u32 dwPhyAddr, void *pbyVirAddr, u32 dwSize);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __VPSS_API_CORE_H */
