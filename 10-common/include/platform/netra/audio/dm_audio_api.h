/******************************************************************************
模块名  ： DM_AUDIO_DRV
文件名  ： dm_audio_api.h
相关文件： dm_audio_api.c
文件实现功能：数字媒体音频接口
作者    ：张方明
版本    ：1.0.0.0.0
-------------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
07/12/2011  1.0         张方明      创建
******************************************************************************/
#ifndef __DM_AUDIO_API_H
#define __DM_AUDIO_API_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* runtime include files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "kdvtype.h"


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
模块版本：DM_AUDIO_DRV 1.1.1.20110712
增加功能：创建
修改缺陷：无
提交人：张方明
----------------------------------------------------------------------------

****************************************************************************/
/* 版本号定义 */
#define VER_DM_AUDIO_DRV         (const s8*)"DM_AUDIO_DRV 1.1.1.20110712" 

/* 驱动模块返回值定义 */
#define DM_AUD_ELEN        -8   /**< len err (failure). */
#define DM_AUD_ENOOPEN     -7   /**< IO no open (failure). */
#define DM_AUD_EBUSY       -6   /**< An IO busy occured (failure). */
#define DM_AUD_EINVAL      -5   /**< Invalid input arguments (failure). */
#define DM_AUD_ENOMEM      -4   /**< No memory available (failure). */
#define DM_AUD_EIO         -3   /**< An IO error occured (failure). */
#define DM_AUD_ENOTIMPL    -2   /**< Functionality not implemented (failure). */
#define DM_AUD_EFAIL       -1   /**< General failure code (failure). */
#define DM_AUD_EOK          0   /**< General success code (success). */
#define DM_AUD_EFLUSH       1   /**< The command was flushed (success). */
#define DM_AUD_EPRIME       2   /**< The command was primed (success). */
#define DM_AUD_EFIRSTFIELD  3   /**< Only the first field was processed (success)*/
#define DM_AUD_EBITERROR    4   /**< There was a non fatal bit error (success). */
#define DM_AUD_ETIMEOUT     5   /**< The operation was timed out (success). */
#define DM_AUD_EEOF         6   /**< The operation reached end of file */
#define DM_AUD_EAGAIN       7   /**< The command needs to be rerun (success). */

/* 极限值定义 */
#define DM_AUD_DEV_MAX_NUM  4   /* 目前最大支持4个音频设备 */
#define DM_AUD_BUF_MAX_NUM  32  /* 目前最多允许分配的BUF个数 */

/* 音频设备打开模式定义  */
#define DM_AUD_IOM_INPUT    0   /* 输入模式，即采集 */
#define DM_AUD_IOM_OUTPUT   1   /* 输出模式，即播放 */

/* DmAudCtrl操作码定义 */
#define DM_AUD_GET_RX_STAT  0   /* 音频接收统计状态查询 */
#define DM_AUD_GET_TX_STAT  1   /* 音频播放统计状态查询 */

/* 类型定义 */
typedef void * HDmAudDev;

/* 音频数据口定义，对于McAsp设备来说有效，可以指定当前ASP设备绑定的数据输入输出I2S线路 */
#define DM_AUD_SER0    (1 << 0)
#define DM_AUD_SER1    (1 << 1)
#define DM_AUD_SER2    (1 << 2)
#define DM_AUD_SER3    (1 << 3)
#define DM_AUD_SER4    (1 << 4)
#define DM_AUD_SER5    (1 << 5)
#define DM_AUD_SER6    (1 << 6)
#define DM_AUD_SER7    (1 << 7)
#define DM_AUD_SER8    (1 << 8)
#define DM_AUD_SER9    (1 << 9)
#define DM_AUD_SER10   (1 << 10)
#define DM_AUD_SER11   (1 << 11)
#define DM_AUD_SER12   (1 << 12)
#define DM_AUD_SER13   (1 << 13)
#define DM_AUD_SER14   (1 << 14)
#define DM_AUD_SER15   (1 << 15)


typedef struct{
    u32	    dwFBufId;           /* 帧BUF的索引号，驱动内部使用，用户不能修改 */
    u8 *    pbyFBuf;            /* 帧BUF的指针，指向帧数据Buf；
                                    用户分配BufDesc时如果填NULL的话驱动自动分配1个数据BUF，否则使用用户指定的地址作为数据BUF，
                                    !!! 如果是用户分配，
                                        1、用户必须保证Buf的对齐，即起始地址必须是128字节对齐;
                                        计算BUF大小=dwBytesPerSample*dwSamplePerFrame*dwChanNum;
                                        2、关闭设备时驱动不会释放这些内存 */
    BOOL32  bUseCache;          /* 仅对于用户分配Buf有效，驱动自动分配的为带cache的；
                                   为TRUE表示用户分配的Buf带cache，驱动里面会进行刷cache处理；
                                   为FALSE为不带cache的，驱动不做刷cache处理 */
    u32	    dwTimeStamp;        /* 帧的时间戳，采集时用户可以读取当前帧的时间搓 */
} TDmAudFBufDesc;

/* 音频IO设备创建的参数结构定义
 *  在buffer中 AUD_SER0 到 AUD_SERn 路从左到右交错分布，长度为buffer的n分之1, 
    无法设置 AUD_SERn 在buffer中的位置。如采集用了SER1 SER2 和 SER3，则内存中数据排列为：
    SER1_L SER2_L SER3_L SER1_R SER2_R SER3_R ... 这和DM647不同
 *
 *  dwChnlCfg配置：
 *                  物理口                  对应宏
 *  H600:
 *      Asp0采集    模拟音频                DM_AUD_SER0
 *                  数字MIC                 DM_AUD_SER4 (固定48K 32位采样)
 *      Asp0播放    3.5音频接口             DM_AUD_SER1
 *                  扬声器                  DM_AUD_SER5
 *  H700:
 *      Asp0采集    RCA模拟音频             DM_AUD_SER1
 *                  卡农MIC                 DM_AUD_SER3
 *                  数字MIC                 DM_AUD_SER4 (固定48K 32位采样)
 *      Asp0播放    RCA模拟音频             DM_AUD_SER0
 *                  6.5平衡输出             DM_AUD_SER2
 *                  扬声器                  DM_AUD_SER5
 *      Asp1采集    HDMI音频                DM_AUD_SER0 (视输入源格式)
 *  H900:
 *      DM8168:
 *          Asp0采集    11个接口输入选一        DM_AUD_SER0
 *                      9个C6747输入选一        DM_AUD_SER1                
 *          Asp1采集    C6747 AXR0_11           DM_AUD_SER0(物理上连通)
 *					    C6747 AXR1_11	        DM_AUD_SER1(物理上连通)
 *	        Asp0播放    RCA模拟音频             DM_AUD_SER3
 *	        Asp2播放    C6747 AXR0_14           DM_AUD_SER0(物理上连通)
 *                      C6747 AXR0_15           DM_AUD_SER1(物理上连通)
 *	HDU2:
 *		Asp0播放 	3.5音频接口0 			 DM_AUD_SER0
 *		Asp0播放 	3.5音频接口1 			 DM_AUD_SER1
 * 		Asp0播放 	HDMI音频接口0 			 DM_AUD_SER2
 * 		Asp0播放 	HDMI音频接口1 			 DM_AUD_SER3
 */
typedef struct{
    u32   dwBytesPerSample;     /* 一个样本的字节数：1 2 4 */
    u32   dwSamplePerFrame;     /* 一帧的样本个数 */
    u32   dwChnlNum;            /* 声道个数，2的整数倍，即n路立体声，1帧的字节数=dwBytesPerSample*dwSamplePerFrame*dwChanNum */
    u32   dwChnlCfg;            /* 填0表示按默认配置serial输入输出线路, 其他值填DM_AUD_SER0等的集合体，高级用户使用 */
    u32   dwFrameNum;           /* 缓存Frame的个数，范围：2~DM_AUD_BUF_MAX_NUM-1 */
    u32   dwSampleFreq;         /* 8000，48000，96000，192000Hz ... */
    TDmAudFBufDesc *pBufDescs;  /* 指向用户分配的FBufDesc结构变量数组的首地址，用户可以自己分配数据Buf，将指针传递给驱动
                                    数组个数为dwFrameNum, 注意：音频需要128字节边界对齐；
                                    对于不想自己分配Buf的用户填为NULL时即可，驱动会按照前面的参数自动分配BUF */
} TDmAudDevParam;

/* 音频采集统计状态结构定义，对应操作码：DM_AUD_GET_RX_STAT */
typedef struct{
    u32   dwFragsTotal;         /* 驱动中最大能缓存的音频数据帧的总数 */
    u32   dwFragSize;           /* 驱动中缓存一帧音频数据的字节数,多路声道的总和 */
    u32   dwFragments;          /* 驱动中能读取的音频数据帧的个数 */
    u32   dwBytesCanRd;         /* 驱动中能读取的音频数据字节数，回声抵消时要用 */
    u32   dwLostBytes;          /* 对于采集表示丢弃的字节数，一般在没有可用buf时发生，回声抵消时要用 */
    u32   dwDmaErr;             /* dma出错的次数 */
    u32   dwOverRunErr;         /* Overrun出错的次数 */
    u32   dwSyncErr;            /* 帧同步出错的次数 */
    u32   dwPingPongErr;        /* ping-pong反转出错的次数 */
    u32   adwReserved[5];       /* reserved */
} TDmAudRxStat;

/* 音频播放状态结构定义，对应操作码：DM_AUD_GET_TX_STAT */
typedef struct{
    u32   dwFragsTotal;         /* 驱动中最大能缓存的音频数据帧的总数 */
    u32   dwFragSize;           /* 驱动中缓存一帧音频数据的字节数 */
    u32   dwFragments;          /* 驱动中能写入的音频数据帧的个数 */
    u32   dwBytesCanWrt;        /* 驱动中能写入的音频数据字节数，dwFragsTotal*dwFragSize-dwBytesCanWrt=当前待播放的音频数据字节数 */
    u32   dwMuteBytes;          /* 对于播放表示播放静音的字节数，一般在没有音频数据时发生，回声抵消时要用 */
    u32   dwDmaErr;             /* dma出错的次数 */
    u32   dwUnderRunErr;        /* Underrun出错的次数 */
    u32   dwSyncErr;            /* 帧同步出错的次数 */
    u32   dwPingPongErr;        /* ping-pong反转出错的次数 */
    u32   adwReserved[5];       /* reserved */
} TDmAudTxStat;


/*==============================================================================
    函数名      : DmAudOpen
    功能        ：音频IO设备打开，1个dwDevId可以打开2次，分别为INPUT/OUPUT
    输入参数说明：dwDevId: 0~DM_AUD_DEV_MAX_NUM-1;
                  nMode: DM_AUD_IOM_INPUT/DM_AUD_IOM_OUTPUT
                  ptParam: 打开的参数
                  phAudDev: 控制句柄指针
    返回值说明  ：错误返回DM_AUD_EFAIL或错误码；成功返回DM_AUD_EOK和控制句柄
------------------------------------------------------------------------------*/
s32 DmAudOpen(u32 dwDevId, s32 nMode, TDmAudDevParam *ptParam, HDmAudDev *phAudDev);

/*==============================================================================
    函数名      : DmAudClose
    功能        ：音频IO设备关闭。
    输入参数说明：hAudDev: DmAudOpen函数返回的句柄;
    返回值说明  ：错误返回DM_AUD_EFAIL或错误码；成功返回DM_AUD_EOK
------------------------------------------------------------------------------*/
s32 DmAudClose(HDmAudDev hAudDev);

/*==============================================================================
    函数名      : DmAudRead
    功能        ：音频IO设备读数据，读取长度必须是dwBytesPerSample*dwChanNum的整数倍。
    输入参数说明：hAudDev: 以DM_AUD_IOM_INPUT模式调用DmAudOpen函数返回的句柄;
                 pBuf: 指向用户分配的Buf，用来存放采集的音频数据
                 size：要读取的数据字节数
                 nTimeoutMs: -1=wait forever; 0=no wait;其他正值为超时毫秒数
    返回值说明  ：错误返回DM_AUD_EFAIL；超时返回0；成功返回读到的字节数(=size)
------------------------------------------------------------------------------*/
s32 DmAudRead(HDmAudDev hAudDev, void *pBuf, size_t size, s32 nTimeoutMs);

/*==============================================================================
    函数名      : DmAudWrite
    功能        ：向音频IO设备写数据，数据字节数必须是dwBytesPerSample*dwChanNum的整数倍
    输入参数说明：hAudDev: 以DM_AUD_IOM_OUTPUT模式调用DmAudOpen函数返回的句柄;
                 pData: 指向用户存放待播放的音频数据
                 size：要播放的数据字节数
                 nTimeoutMs: -1=wait forever; 0=no wait;其他正值为超时毫秒数
    返回值说明  ：错误返回DM_AUD_EFAIL；超时返回0；成功返回写入的字节数(=size)
------------------------------------------------------------------------------*/
s32 DmAudWrite(HDmAudDev hAudDev, void *pData, size_t size, s32 nTimeoutMs);

/*==============================================================================
    函数名      : DmAudFBufGet
    功能        ：取一帧音频BUF，对于采集用户拿到的是音频数据Buf，对于播放用户
                  拿到的是空Buf，用户可以多次调用取多个BUF。
                  # 如果用户使用read write的话不能使用该函数!!!
    输入参数说明：hAudDev: 调用DmAudOpen函数返回的句柄;
                  ptBufDesc: 用户分配并传入指针，驱动将BUF信息拷贝给用户
                  nTimeoutMs: -1=wait forever; 0=no wait;其他正值为超时毫秒数
    返回值说明  ：错误返回DM_AUD_EFAIL或错误码；成功返回DM_AUD_EOK
------------------------------------------------------------------------------*/
s32 DmAudFBufGet(HDmAudDev hAudDev, TDmAudFBufDesc *ptBufDesc, s32 nTimeoutMs);

/*==============================================================================
    函数名      : DmAudFBufPut
    功能        ：归还一帧音频BUF
                  # 如果用户使用read write的话不能使用该函数!!!
    输入参数说明：hAudDev: 调用DmAudOpen函数返回的句柄;
                  ptBufDesc: 用户调用DmAudFBufGet得到的BufDesc信息
    返回值说明  ：错误返回DM_AUD_EFAIL或错误码；成功返回DM_AUD_EOK
------------------------------------------------------------------------------*/
s32 DmAudFBufPut(HDmAudDev hAudDev, TDmAudFBufDesc *ptBufDesc);

/*====================================================================
    函数名      : DmAudCtrl
    功能        ：音频IO设备控制，目前定义了
                    DM_AUD_GET_RX_STAT: pArgs为TDmAudRxStat *
                    DM_AUD_GET_TX_STAT: pArgs为TDmAudTxStat *
                  ......
    输入参数说明：hAudDev: 调用DmAudOpen函数返回的句柄;
                 nCmd: 操作码；pArgs: 参数指针
    返回值说明  ：错误返回DM_AUD_EFAIL或错误码；成功返回DM_AUD_EOK
---------------------------------------------------------------------*/
s32 DmAudCtrl(HDmAudDev hAudDev, s32 nCmd, void *pArgs);

/*====================================================================
    函数名      : DmAudGetVer
    功能        ：模块版本号查询。
    输入参数说明：pchVer： 给定的存放版本信息的buf指针
                  dwBufLen：给定buf的长度
    返回值说明  ：版本的实际字符串长度。小于0为出错;
                 如果实际字符串长度大于dwBufLen，赋值为0
--------------------------------------------------------------------*/
s32 DmAudGetVer(s8 *pchVer, u32 dwBufLen);


#ifdef __cplusplus 
} 
#endif /* __cplusplus */

#endif /* __DM_AUDIO_API_H */
