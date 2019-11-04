/******************************************************************************
模块名  ： DM6437_AUDIO_DRV
文件名  ： dm6437_audio_api.h
相关文件： dm6437_audio_api.c
文件实现功能：
作者    ：张方明
版本    ：1.0.0.0.0
-------------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
08/15/2007  1.0         张方明      创建
04/22/2008  1.1         张方明      修改类型定义头文件，修改ioctl类型宏定义
******************************************************************************/
#ifndef __DM6437_AUDIO_API_H
#define __DM6437_AUDIO_API_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* runtime include files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "dm6437_drv_common.h"


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
模块版本：DM6437_AUDIO_DRV 1.1.1.20080422
增加功能：创建
修改缺陷：无
提交人：张方明
----------------------------------------------------------------------------
模块版本：DM6437_AUDIO_DRV 1.1.2.20080527
增加功能：解决音频多次open close或读写数据延时引起音频死掉问题
修改缺陷：无
提交人：张方明
----------------------------------------------------------------------------
模块版本：DM6437_AUDIO_DRV 1.1.3.20080605
增加功能：解决release版本音频左右声道反问题
修改缺陷：无
提交人：张方明
----------------------------------------------------------------------------
模块版本：DM6437_AUDIO_DRV 1.1.4.20100331
增加功能：无
修改缺陷：修正了按非128字节分配buffer内存导致出错的问题(cache对齐)
提交人：赫诚杰

****************************************************************************/
/* 版本号定义 */
#define VER_DM6437_AUDIO_DRV         (const s8*)"DM6437_AUDIO_DRV 1.1.4.20100331" 

/* 板级驱动模块返回值定义  */
#define DM6437_AUD_SUCCESS                0                  /* 成功 */

#define DM6437_AUD_ERR_BASE               0                  /* 错误码基值 */
#define DM6437_AUD_DEV_NOT_EXIST          (DM6437_AUD_SUCCESS+1)  /* 设备不存在 */
#define DM6437_AUD_DEV_NOT_OPEN           (DM6437_AUD_SUCCESS+2)  /* 设备没有打开 */
#define DM6437_AUD_PARAM_ERR              (DM6437_AUD_SUCCESS+3)  /* 参数非法 */
#define DM6437_AUD_LENGTH_ERR             (DM6437_AUD_SUCCESS+4)  /* 信息长度错误 */
#define DM6437_AUD_QUEUE_FULL             (DM6437_AUD_SUCCESS+5)  /* 数据队列已满 */
#define DM6437_AUD_NOT_SUPPORT            (DM6437_AUD_SUCCESS+6)  /* 设备不支持该操作 */
#define DM6437_AUD_OPT_TIMEOUT            (DM6437_AUD_SUCCESS+7)  /* 操作超时 */
#define DM6437_AUD_NO_MEM                 (DM6437_AUD_SUCCESS+8)  /* 没有可用内存 */
#define DM6437_AUD_DEV_BUSY               (DM6437_AUD_SUCCESS+9)  /* 设备忙，已经被打开 */
#define DM6437_AUD_GIO_FAILE              (DM6437_AUD_SUCCESS+10) /* GIO操作失败 */
#define DM6437_AUD_FAILURE                -1                 /* 未知的异常失败 */

/* 极限值定义 */
#define DM6437_AUD_DEV_MAX_NUM             2              /* 目前一个DM6437上最大支持2路音频芯片 */
#define DM6437_AUD_BUF_MAX_NUM             32             /* 目前最多允许分配的BUF个数 */

/* 音频设备打开模式定义  */
#define DM6437_AUD_IOM_INPUT               0              /* 输入模式，即采集 */
#define DM6437_AUD_IOM_OUTPUT              1              /* 输出模式，即播放 */

/* Dm6437AudCtrl操作码定义 */
#define DM6437_AUD_GET_RX_STAT             0              /* 音频接收统计状态查询 */
#define DM6437_AUD_GET_TX_STAT             1              /* 音频播放统计状态查询 */

/* 类型定义 */
typedef void * HDm6437AudDev;


/* 音频IO设备创建的参数结构定义 */
typedef struct{
    u32   dwBytesPerSample;      /* 一个样本的字节数：1 2 4 */
    u32   dwSamplePerFrame;      /* 一帧的样本个数 */
    u32   dwChanNum;             /* 声道个数，固定填2，即立体声，1帧的字节数=dwBytesPerSample*dwSamplePerFrame*dwChanNum */
    u32   dwFrameNum;            /* 缓存Frame的个数，范围：2~DM6437_AUD_BUF_MAX_NUM-1 */
    u32   dwSampleFreq;          /* 8000，48000，96000，192000Hz ... */
    TFBufDesc *pBufDescs;        /* 指向用户分配的FBufDesc结构变量数组的首地址，用户可以自己分配数据Buf，将指针传递给驱动
                                    数组个数为dwFrameNum, 注意：音频需要128字节边界对齐；
                                    对于不想自己分配Buf的用户填为NULL时即可，驱动会按照前面的参数自动分配BUF */
} TDm6437AudDevParam;

/* 音频采集统计状态结构定义，对应操作码：DM6437_AUD_GET_RX_STAT */
typedef struct{
    u32   dwBytesInDrv;          /* 驱动中缓存的采集到的音频数据字节数，回声抵消时要用 */
    u32   dwLostBytes;           /* 对于采集表示丢弃的字节数，一般在没有可用buf时发生，回声抵消时要用 */
    u32   adwReserved[10];        /* reserved */
} TDm6437AudRxStat;

/* 音频播放状态结构定义，对应操作码：DM6437_AUD_GET_TX_STAT */
typedef struct{
    u32   dwBytesInDrv;          /* 驱动中缓存的待播放的音频数据字节数，回声抵消时要用 */
    u32   dwMuteBytes;           /* 对于播放表示播放静音的字节数，一般在没有音频数据时发生，回声抵消时要用 */
    u32   adwReserved[10];        /* reserved */
} TDm6437AudTxStat;


/*==============================================================================
    函数名      : Dm6437AudOpen
    功能        ：音频IO设备打开，1个dwDevId可以打开2次，分别为INPUT/OUPUT
    输入参数说明：dwDevId: 0~DM6437_AUD_DEV_MAX_NUM-1;
                 nMode: DM6437_AUD_IOM_INPUT/DM6437_AUD_IOM_OUTPUT
                 ptParam: 打开的参数
    返回值说明  ：错误返回NULL；成功返回控制句柄
------------------------------------------------------------------------------*/
HDm6437AudDev Dm6437AudOpen(u32 dwDevId, l32 nMode, TDm6437AudDevParam *ptParam);

/*==============================================================================
    函数名      : Dm6437AudClose
    功能        ：音频IO设备关闭。
    输入参数说明：hAudDev: Dm6437AudOpen函数返回的句柄;
    返回值说明  ：错误返回DM6437_AUD_FAILURE或错误码；成功返回DM6437_AUD_SUCCESS
------------------------------------------------------------------------------*/
l32 Dm6437AudClose(HDm6437AudDev hAudDev);

/*==============================================================================
    函数名      : Dm6437AudRead
    功能        ：音频IO设备读数据，读取长度必须是dwBytesPerSample*dwChanNum的整数倍。
    输入参数说明：hAudDev: 以DM6437_AUD_IOM_INPUT模式调用Dm6437AudOpen函数返回的句柄;
                 pBuf: 指向用户分配的Buf，用来存放采集的音频数据
                 size：要读取的数据字节数
                 nTimeoutMs: -1=wait forever; 0=no wait;其他正值为超时毫秒数
    返回值说明  ：错误返回DM6437_AUD_FAILURE；超时返回0；成功返回读到的字节数(=size)
------------------------------------------------------------------------------*/
l32 Dm6437AudRead(HDm6437AudDev hAudDev, void *pBuf, size_t size, l32 nTimeoutMs);

/*==============================================================================
    函数名      : Dm6437AudWrite
    功能        ：向音频IO设备写数据，数据字节数必须是dwBytesPerSample*dwChanNum的整数倍
    输入参数说明：hAudDev: 以DM6437_AUD_IOM_OUTPUT模式调用Dm6437AudOpen函数返回的句柄;
                 pData: 指向用户存放待播放的音频数据
                 size：要播放的数据字节数
                 nTimeoutMs: -1=wait forever; 0=no wait;其他正值为超时毫秒数
    返回值说明  ：错误返回DM6437_AUD_FAILURE；超时返回0；成功返回写入的字节数(=size)
------------------------------------------------------------------------------*/
l32 Dm6437AudWrite(HDm6437AudDev hAudDev, void *pData, size_t size, l32 nTimeoutMs);

/*==============================================================================
    函数名      : Dm6437AudFBufGet
    功能        ：取一帧音频BUF，对于采集用户拿到的是音频数据Buf，对于播放用户
                  拿到的是空Buf，用户可以多次调用取多个BUF。
                  # 如果用户使用read write的话不要使用该函数!!!
    输入参数说明：hAudDev: 调用Dm6437AudOpen函数返回的句柄;
                  ptBufDesc: 用户分配并传入指针，驱动将BUF信息拷贝给用户
                  nTimeoutMs: -1=wait forever; 0=no wait;其他正值为超时毫秒数
    返回值说明  ：错误返回DM6437_AUD_FAILURE或错误码；成功返回DM6437_AUD_SUCCESS
------------------------------------------------------------------------------*/
l32 Dm6437AudFBufGet(HDm6437AudDev hAudDev, TFBufDesc *ptBufDesc, l32 nTimeoutMs);

/*==============================================================================
    函数名      : Dm6437AudFBufPut
    功能        ：归还一帧音频BUF
                  # 如果用户使用read write的话不要使用该函数!!!
    输入参数说明：hAudDev: 调用Dm6437AudOpen函数返回的句柄;
                  ptBufDesc: 用户调用Dm6437AudFBufGet得到的BufDesc信息
    返回值说明  ：错误返回DM6437_AUD_FAILURE或错误码；成功返回DM6437_AUD_SUCCESS
------------------------------------------------------------------------------*/
l32 Dm6437AudFBufPut(HDm6437AudDev hAudDev, TFBufDesc *ptBufDesc);

/*====================================================================
    函数名      : Dm6437AudCtrl
    功能        ：音频IO设备控制，目前定义了
                    DM6437_AUD_GET_RX_STAT: pArgs为TDm6437AudRxStat *
                    DM6437_AUD_GET_TX_STAT: pArgs为TDm6437AudTxStat *
                  ......
    输入参数说明：hAudDev: 调用Dm6437AudOpen函数返回的句柄;
                 nCmd: 操作码；pArgs: 参数指针
    返回值说明  ：错误返回DM6437_AUD_FAILURE或错误码；成功返回DM6437_AUD_SUCCESS
---------------------------------------------------------------------*/
l32 Dm6437AudCtrl(HDm6437AudDev hAudDev, l32 nCmd, void *pArgs);

/*====================================================================
    函数名      : Dm6437AudGetVer
    功能        ：模块版本号查询。
    输入参数说明：pchVer： 给定的存放版本信息的buf指针
                  dwBufLen：给定buf的长度
    返回值说明  ：版本的实际字符串长度。小于0为出错;
                 如果实际字符串长度大于dwBufLen，赋值为0
--------------------------------------------------------------------*/
l32 Dm6437AudGetVer(s8 *pchVer, u32 dwBufLen);


#ifdef __cplusplus 
} 
#endif /* __cplusplus */

#endif /* __DM6437_AUDIO_API_H */
