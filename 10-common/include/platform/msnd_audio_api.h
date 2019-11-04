/******************************************************************************
模块名  ： MSNDIO_DRV
文件名  ： MSNDio_api.h
相关文件： MSNDio_api.c
文件实现功能：数字媒体音频接口
作者    ：张方明
版本    ：1.0.0.0.0
-------------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
07/12/2011  1.0         张方明      创建
******************************************************************************/
#ifndef __MSND_AUDIO_API_H
#define __MSND_AUDIO_API_H

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
模块版本：MSND_AUDIO_DRV 1.1.1.20110712
增加功能：创建
修改缺陷：无
提交人：张方明
----------------------------------------------------------------------------

****************************************************************************/
/* 版本号定义 */
#define VER_MSNDIO_DRV        (const s8*)"MSND_AUDIO_DRV 1.1.1.20110712" 

/* 驱动模块返回值定义 */
#define MSND_ELEN        -8   /**< len err (failure). */
#define MSND_ENOOPEN     -7   /**< IO no open (failure). */
#define MSND_EBUSY       -6   /**< An IO busy occured (failure). */
#define MSND_EINVAL      -5   /**< Invalid input arguments (failure). */
#define MSND_ENOMEM      -4   /**< No memory available (failure). */
#define MSND_EIO         -3   /**< An IO error occured (failure). */
#define MSND_ENOTIMPL    -2   /**< Functionality not implemented (failure). */
#define MSND_EFAIL       -1   /**< General failure code (failure). */
#define MSND_EOK          0   /**< General success code (success). */
#define MSND_EFLUSH       1   /**< The command was flushed (success). */
#define MSND_EPRIME       2   /**< The command was primed (success). */
#define MSND_EFIRSTFIELD  3   /**< Only the first field was processed (success)*/
#define MSND_EBITERROR    4   /**< There was a non fatal bit error (success). */
#define MSND_ETIMEOUT     5   /**< The operation was timed out (success). */
#define MSND_EEOF         6   /**< The operation reached end of file */
#define MSND_EAGAIN       7   /**< The command needs to be rerun (success). */

/* 极限值定义 */
#define MSND_DEV_MAX_NUM  9   /* 目前最大支持5个音频设备 */
#define MSND_BUF_MAX_NUM  32  /* 目前最多允许分配的BUF个数 */

/* 音频设备打开模式定义  */
#define MSND_IOM_INPUT    0   /* 输入模式，即采集 */
#define MSND_IOM_OUTPUT   1   /* 输出模式，即播放 */

/* MsndCtrl操作码定义 */
#define MSND_GET_RX_STAT  0   /* 音频接收统计状态查询 */
#define MSND_GET_TX_STAT  1   /* 音频播放统计状态查询 */

/* 类型定义 */
typedef void * HMsndDev;

/* 音频数据口定义，对于McAsp设备来说有效，可以指定当前ASP设备绑定的数据输入输出I2S线路 */
#define MSND_SER0    (1 << 0)
#define MSND_SER1    (1 << 1)
#define MSND_SER2    (1 << 2)
#define MSND_SER3    (1 << 3)
#define MSND_SER4    (1 << 4)
#define MSND_SER5    (1 << 5)
#define MSND_SER6    (1 << 6)
#define MSND_SER7    (1 << 7)
#define MSND_SER8    (1 << 8)
#define MSND_SER9    (1 << 9)
#define MSND_SER10   (1 << 10)
#define MSND_SER11   (1 << 11)
#define MSND_SER12   (1 << 12)
#define MSND_SER13   (1 << 13)
#define MSND_SER14   (1 << 14)
#define MSND_SER15   (1 << 15)
#define MSND_SER16   (1 << 16)
#define MSND_SER17   (1 << 17)



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
} TMsndFBufDesc;

/* 音频IO设备创建的参数结构定义
 *  在buffer中 AUD_SER0 到 AUD_SERn 路从左到右交错分布，长度为buffer的n分之1, 
    无法设置 AUD_SERn 在buffer中的位置。如采集用了SER1 SER2 和 SER3，则内存中数据排列为：
    SER1_L SER2_L SER3_L SER1_R SER2_R SER3_R ... 这和DM647不同
 *
 *  dwChnlCfg配置：
 *  T300: 
 *       音频输入    
 *                  物理口                物理名称                    对应宏
 *                RCA_DIN1    2组莲花端子混音输入(正对背板最右边)    MSND_SER0
 *                3.5_DIN2    3.5mm耳机插孔1输入(正对背板最左边)     MSND_SER1
 *                3.5_DIN3    3.5mm耳机插孔2输入                     MSND_SER2
 *                3.5_DIN4    3.5mm耳机插孔3输入				     MSND_SER3
 *                3.5_DIN5    3.5mm耳机插孔4输入                     MSND_SER4
 *                XLR1_2_DIN1     卡农1&卡农2(正对背板最左边)        MSND_SER5
 *                XLR3_4_DIN2     卡农3&卡农4						 MSND_SER6
 *				  XLR5_6_DIN3     卡农5&卡农6                        MSND_SER7
 *			      XLR7_8_DIN4     卡农7&卡农8 						 MSND_SER8
 *                XLR9_10_DIN5    卡农9&卡农10 						 MSND_SER9
 *				  RX1_DIN1		  数字MIC1                           MSND_SER10
 *				  RX2_DIN2		  数字MIC2                           MSND_SER11
 *				  RX3_DIN3		  数字MIC3                           MSND_SER12
 *                DVI-IN-5 6 7 8 选一路                              MSND_SER13
 *                DVI-IN-9 10 11 选一路                              MSND_SER14
 *                RCA-DIN1   莲花端子输出口1(回采)					 MSND_SER15
 *                RCA-DIN2   莲花端子输出口2(回采) 				     MSND_SER16
 *                RCA-DIN3   莲花端子输出口3(回采)					 MSND_SER17
 *       音频输出
 *                  物理口                物理名称                    对应宏
 *				  RCA-DOUT1   莲花端子输出口1 (正对背板最左边)       MSND_SER0
 *				  RCA-DOUT2   莲花端子输出口2                        MSND_SER1
 *				  RCA-DOUT3   莲花端子输出口3                        MSND_SER2
 *				  RCA-DOUT4   莲花端子输出口4                        MSND_SER3
 *				  RCA-DOUT5   莲花端子输出口5                        MSND_SER4
 *				  SPEAKER     扬声器                                 MSND_SER5
 *                DVI-OUT1    DVI-OUT-1                              MSND_SER6
 *                DVI-OUT2    DVI-OUT-2                              MSND_SER7
 *                DVI-OUT3    DVI-OUT-3                              MSND_SER8
 *                DVI-OUT4    DVI-OUT-4                              MSND_SER9
 *                DVI-OUT5    DVI-OUT-5                              MSND_SER10
 *  
 */
typedef struct{
    u32   dwBytesPerSample;     /* 一个样本的字节数：1 2 4 */
    u32   dwSamplePerFrame;     /* 一帧的样本个数 */
    u32   dwChnlNum;            /* 声道个数，2的整数倍，即n路立体声，1帧的字节数=dwBytesPerSample*dwSamplePerFrame*dwChanNum */
    u32   dwChnlCfg;            /* 填0表示按默认配置serial输入输出线路, 其他值填MSND_SER0等的集合体，高级用户使用 */
    u32   dwFrameNum;           /* 缓存Frame的个数，范围：2~MSND_BUF_MAX_NUM-1 */
    u32   dwSampleFreq;         /* 8000，48000，96000，192000Hz ... */
    TMsndFBufDesc *pBufDescs;  /* 指向用户分配的FBufDesc结构变量数组的首地址，用户可以自己分配数据Buf，将指针传递给驱动
                                    数组个数为dwFrameNum, 注意：音频需要128字节边界对齐；
                                    对于不想自己分配Buf的用户填为NULL时即可，驱动会按照前面的参数自动分配BUF */
} TMsndDevParam;

/* 音频采集统计状态结构定义，对应操作码：MSND_GET_RX_STAT */
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
} TMsndRxStat;

/* 音频播放状态结构定义，对应操作码：MSND_GET_TX_STAT */
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
} TMsndTxStat;


/*==============================================================================
    函数名      : MsndOpen
    功能        ：音频IO设备打开，1个dwDevId可以打开2次，分别为INPUT/OUPUT
    输入参数说明：dwDevId: 0~MSND_DEV_MAX_NUM-1;
                  nMode: MSND_IOM_INPUT/MSND_IOM_OUTPUT
                  ptParam: 打开的参数
                  phAudDev: 控制句柄指针
    返回值说明  ：错误返回MSND_EFAIL或错误码；成功返回MSND_EOK和控制句柄
------------------------------------------------------------------------------*/
s32 MsndOpen(u32 dwDevId, s32 nMode, TMsndDevParam *ptParam, HMsndDev *phAudDev);

/*==============================================================================
    函数名      : MsndClose
    功能        ：音频IO设备关闭。
    输入参数说明：hAudDev: MsndOpen函数返回的句柄;
    返回值说明  ：错误返回MSND_EFAIL或错误码；成功返回MSND_EOK
------------------------------------------------------------------------------*/
s32 MsndClose(HMsndDev hAudDev);

/*==============================================================================
    函数名      : MsndRead
    功能        ：音频IO设备读数据，读取长度必须是dwBytesPerSample*dwChanNum的整数倍。
    输入参数说明：hAudDev: 以MSND_IOM_INPUT模式调用MsndOpen函数返回的句柄;
                 pBuf: 指向用户分配的Buf，用来存放采集的音频数据
                 size：要读取的数据字节数
                 nTimeoutMs: -1=wait forever; 0=no wait;其他正值为超时毫秒数
    返回值说明  ：错误返回MSND_EFAIL；超时返回0；成功返回读到的字节数(=size)
------------------------------------------------------------------------------*/
s32 MsndRead(HMsndDev hAudDev, void *pBuf, size_t size, s32 nTimeoutMs);

/*==============================================================================
    函数名      : MsndWrite
    功能        ：向音频IO设备写数据，数据字节数必须是dwBytesPerSample*dwChanNum的整数倍
    输入参数说明：hAudDev: 以MSND_IOM_OUTPUT模式调用MsndOpen函数返回的句柄;
                 pData: 指向用户存放待播放的音频数据
                 size：要播放的数据字节数
                 nTimeoutMs: -1=wait forever; 0=no wait;其他正值为超时毫秒数
    返回值说明  ：错误返回MSND_EFAIL；超时返回0；成功返回写入的字节数(=size)
------------------------------------------------------------------------------*/
s32 MsndWrite(HMsndDev hAudDev, void *pData, size_t size, s32 nTimeoutMs);

/*==============================================================================
    函数名      : MsndFBufGet
    功能        ：取一帧音频BUF，对于采集用户拿到的是音频数据Buf，对于播放用户
                  拿到的是空Buf，用户可以多次调用取多个BUF。
                  # 如果用户使用read write的话不能使用该函数!!!
    输入参数说明：hAudDev: 调用MsndOpen函数返回的句柄;
                  ptBufDesc: 用户分配并传入指针，驱动将BUF信息拷贝给用户
                  nTimeoutMs: -1=wait forever; 0=no wait;其他正值为超时毫秒数
    返回值说明  ：错误返回MSND_EFAIL或错误码；成功返回MSND_EOK
------------------------------------------------------------------------------*/
s32 MsndFBufGet(HMsndDev hAudDev, TMsndFBufDesc *ptBufDesc, s32 nTimeoutMs);

/*==============================================================================
    函数名      : MsndFBufPut
    功能        ：归还一帧音频BUF
                  # 如果用户使用read write的话不能使用该函数!!!
    输入参数说明：hAudDev: 调用MsndOpen函数返回的句柄;
                  ptBufDesc: 用户调用MsndFBufGet得到的BufDesc信息
    返回值说明  ：错误返回MSND_EFAIL或错误码；成功返回MSND_EOK
------------------------------------------------------------------------------*/
s32 MsndFBufPut(HMsndDev hAudDev, TMsndFBufDesc *ptBufDesc);

/*====================================================================
    函数名      : MsndCtrl
    功能        ：音频IO设备控制，目前定义了
                    MSND_GET_RX_STAT: pArgs为TMsndRxStat *
                    MSND_GET_TX_STAT: pArgs为TMsndTxStat *
                  ......
    输入参数说明：hAudDev: 调用MsndOpen函数返回的句柄;
                 nCmd: 操作码；pArgs: 参数指针
    返回值说明  ：错误返回MSND_EFAIL或错误码；成功返回MSND_EOK
---------------------------------------------------------------------*/
s32 MsndCtrl(HMsndDev hAudDev, s32 nCmd, void *pArgs);

/*====================================================================
    函数名      : MsndGetVer
    功能        ：模块版本号查询。
    输入参数说明：pchVer： 给定的存放版本信息的buf指针
                  dwBufLen：给定buf的长度
    返回值说明  ：版本的实际字符串长度。小于0为出错;
                 如果实际字符串长度大于dwBufLen，赋值为0
--------------------------------------------------------------------*/
s32 MsndGetVer(s8 *pchVer, u32 dwBufLen);


#ifdef __cplusplus 
} 
#endif /* __cplusplus */

#endif /* __MSNDIO_API_H */
