/******************************************************************************
模块名  ： VPSS_DRV_API
文件名  ： vpss_api_disp.h
相关文件： vpss_api_disp.c
文件实现功能：
作者    ：张方明
版本    ：1.0.0.0.0
-------------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
04/12/2011  1.0         张方明      创建
******************************************************************************/
#ifndef __VPSS_API_DISP_H
#define __VPSS_API_DISP_H

#ifdef __cplusplus
extern "C" { 
#endif /* __cplusplus */

#include "vpss_api_core.h"
#include "vpss_api_dctrl.h"

/* -------------------------------- 宏定义 ----------------------------------*/
/* dwDispId定义
 * 其中BP0和BP1的数据格式只支持: VPSS_VID_COLORSPACE_YUV422I_YUYV
 * DEC1可以支持: VPSS_VID_COLORSPACE_YUV422I_YUYV
                 VPSS_VID_COLORSPACE_YUV422SP_UV
                 VPSS_VID_COLORSPACE_YUV420SP_UV
 */
#define VPSS_DISP_INST_BP0                  0x0 /* Bypass path 0 display driver instance number. */
#define VPSS_DISP_INST_BP1                  0x1 /* Bypass path 1 display driver instance number. */
#define VPSS_DISP_INST_SEC1                 0x2 /* Secondary path SD display driver instance number. */
#define VPSS_DISP_INST_DEIH                 0x3 /* DEI HQ path display driver instance number. */
#define VPSS_DISP_INST_DEI                  0x4 /* DEI path display driver instance number. */
#define VPSS_DISP_MAX                       0x5

#define VPSS_DISP_DEFAULT_MAX               0x3
#define VPSS_DISP_FRAME_LIST_DEFAULT_MAX    0x5
#define VPSS_DISP_WIN_DEFAULT_MAX           0x1

#define VPSS_DISP_WIN_MAX                   20
#define VPSS_DISP_FRAME_LIST_MAX            8
#define VPSS_DISP_LAYOUT_MAX                16


/* VpssDispCtrl操作码定义 */
#define VPSS_DISP_SET_WIN_PARAM             0   /* pArgs对应(TVpssDispRtWinParam *) */
#define VPSS_DISP_GET_DISP_STATUS           1

/* ------------------------------- 类型定义 ---------------------------------*/


/* ------------------------------- 结构定义 ---------------------------------*/
/* 结构定义 */
typedef struct{
    u32             dwWinX;                     /* 窗口相对底图左边右移n个象素，注意：必须是8的整数倍，不能超出底图范围  */
    u32             dwWinY;                     /* 窗口相对底图顶部下移n行，整个图像下移，注意：不能超出底图范围 */
    u32             dwWinWidth;                 /* 填0表示全屏显示,非0表示窗口宽度， 注意：不能超出底图范围 */
    u32             dwWinHight;                 /* 填0表示全屏显示,非0表示窗口高度， 注意：不能超出底图范围 */
    u32             dwFBufSize;                 /* 填0表示自动计算每帧Buf大小,非0表示用户指定每帧Buf大小 */
    u32             dwPriority;                 /* 窗口显示优先级: 0=最高，即叠加在最上面一层;1其次...依次递减
                                                   如果窗口之间有重叠的话必须设置不同的优先级，否则会挂死；
                                                   没有重叠的窗口尽量设置相同的优先级 */
} TVpssDispWin;

typedef struct
{
    u32             dwWinNum;                   /* 该布局风格共有几个窗口 */
    TVpssDispWin    atWinFmt[VPSS_DISP_WIN_MAX];/* 每个窗口的参数 */
} TVpssDispLayout;


/*defined the memory informaton shared between A8 and M3 for each submodule*/
typedef struct 
{
    u32     paddr;  /* phy  addr */
    void    *vaddr; /* virt addr */
    u32     size;   /* size in byte */
}TVpssFramebufInfo;

typedef struct{
    /* 对应的VENC输出的信号制式 */
    TVpssVidStd     tVidStd;
    /* 分配几个帧buf链,范围:1-VPSS_DISP_FRAME_LIST_MAX, 0=默认3个 */
    u32             dwFrameListNum;             
     /**
     *为0表示由驱动分配buf, >0为用户分配的buf个数
     *至少分配wFrameListNum * dwWinNumMax 
     *必须用VpssFbufAlloc函数分配，且Tiler内存无法释放
     *用户最好静态分配好最多最大的内存 
     */
    u32             dwUsrFrameNum;
    /**
      * 为NULL表示由驱动分配buf
      * 否则为用户分配的buf描述数组首地址 
      */
    TVpssFramebufInfo *ptUsrFrames;
    u32             dwLayoutNum;                /* 有几种窗口布局风格，范围: 1~VPSS_DISP_LAYOUT_MAX,0=默认1个 */
    u32             dwLayoutDisp;               /* 创建后用哪种布局风格显示 */
    TVpssDispLayout atDispLayout[VPSS_DISP_LAYOUT_MAX];/* 窗口布局风格参数 */

    u32             dwMemType;                  /* 暂不支持: VPSS_VPDMA_MT_NONTILEDMEM,VPSS_VPDMA_MT_TILEDMEM */
} TVpssDispParam;

/* 窗口(run time)动态参数设置 */
typedef struct{
    u32             dwLayoutDisp;               /* 采用哪种窗口布局风格 */
} TVpssDispRtWinParam;


/* 函数声明 */
/*==============================================================================
    函数名      : VpssDispOpen
    功能        : 打开指定DISP口
    输入参数说明: dwDispId: DISP口的ID号，如: VPSS_DISP_INST_BP0
                  ptDispParam: DISP口参数
    返回值说明  : 错误返回VPSS_FAILURE或错误码；成功返回VPSS_SUCCESS
-----------------------------------------------------------------------------*/
s32 VpssDispOpen(u32 dwDispId, TVpssDispParam *ptDispParam);

/*==============================================================================
    函数名      : VpssDispClose
    功能        : 关闭指定DISP口
    输入参数说明: dwDispId: DISP口的ID号，如: VPSS_DISP_INST_BP0
    返回值说明  : 错误返回VPSS_FAILURE或错误码；成功返回VPSS_SUCCESS
-----------------------------------------------------------------------------*/
s32 VpssDispClose(u32 dwDispId);

/*==============================================================================
    函数名      : VpssDispDequeue
    功能        : 从播放空队列中取一组buf列表
    输入参数说明: 
    返回值说明  : 错误返回VPSS_FAILURE或错误码；成功返回VPSS_SUCCESS
------------------------------------------------------------------------------*/
s32 VpssDispDequeue(u32 dwDispId, TVpssFrameList *ptFrameList, u32 dwStreamId, s32 nTimeout);

/*==============================================================================
    函数名      : VpssDispQueue
    功能        : 放入一组buf列表到播放队列
    输入参数说明: 
    返回值说明  : 错误返回VPSS_FAILURE或错误码；成功返回VPSS_SUCCESS
------------------------------------------------------------------------------*/
s32 VpssDispQueue(u32 dwDispId, TVpssFrameList *ptFrameList, u32 dwStreamId);

/*==============================================================================
    函数名      : VpssDispCtrl
    功能        ：设备控制，目前定义了
                  ......
    输入参数说明：dwDispId: DISP口的ID号，如: VPSS_DISP_INST_BP0
                  nCmd: 操作码；pArgs: 参数指针 详见: VpssDispCtrl操作码定义
    返回值说明  : 错误返回VPSS_FAILURE或错误码；成功返回VPSS_SUCCESS
------------------------------------------------------------------------------*/
s32 VpssDispCtrl(u32 dwDispId, s32 nCmd, void *pArgs);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __VPSS_API_DISP_H */
