/*******************************************************************************
 * 模块名  : MINI_SOUND
 * 文件名  : aud_msnd.h
 * 相关文件: aud_msnd.c
 * 文件实现功能: 迷你声卡驱动接口
 * 作者    : 张方明
 * 版本    : 1.0.0.0.0
 * -----------------------------------------------------------------------------
 * 修改记录:
 * 日  期      版本        修改人      修改内容
 * 2013/11/06  1.1.1       张方明      创建
*******************************************************************************/
#ifndef __AUD_MSND_H
#define __AUD_MSND_H

#include "common/kdvtype.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/*==============================================================================
 * 模块的版本号命名规定:
 * 总的结构: mn.mm.ii.cc.tttt
 *      如  Osp 1.1.7.20040318 表示
 * 模块名称Osp
 * 模块1版本
 * 接口1版本
 * 实现7版本
 * 2004年3月18号修改
 *----------------------------------------------------------------------------*/
#define VER_MSND_DRV         (const char*)"MSND_DRV 1.1.1.20131106"

/* 驱动模块返回值定义 */
#define MSND_EFLUSH      -15  /* The command was flushed (success). */
#define MSND_EPRIME      -14  /* The command was primed (success). */
#define MSND_EFIRSTFIELD -13  /* Only the first field was processed (success)*/
#define MSND_EBITERROR   -12  /* There was a non fatal bit error (success). */
#define MSND_ETIMEOUT    -11  /* The operation was timed out (success). */
#define MSND_EEOF        -10  /* The operation reached end of file */
#define MSND_EAGAIN      -9   /* The command needs to be rerun (success). */
#define MSND_ELEN        -8   /* len err (failure). */
#define MSND_ENOOPEN     -7   /* IO no open (failure). */
#define MSND_EBUSY       -6   /* An IO busy occured (failure). */
#define MSND_EINVAL      -5   /* Invalid input arguments (failure). */
#define MSND_ENOMEM      -4   /* No memory available (failure). */
#define MSND_EIO         -3   /* An IO error occured (failure). */
#define MSND_ENOTIMPL    -2   /* Functionality not implemented (failure). */
#define MSND_EFAIL       -1   /* General failure code (failure). */
#define MSND_EOK          0   /* General success code (success). */

/* 极限值定义 */
#define MSND_DEV_MAX_NUM  8   /* 目前最大支持8个音频设备 */
#define MSND_DEV_ID_McASP 0   /* 0=asp0 1=asp1 2=asp2 for SOC or DSP */
#define MSND_DEV_ID_HDMI  3   /* hdmi audio */
#define MSND_DEV_ID_PCI   4   /* pci sound card */

/* 音频设备打开模式定义  */
#define MSND_IOM_INPUT    0   /* 输入模式，即采集 */
#define MSND_IOM_OUTPUT   1   /* 输出模式，即播放 */

/* MSndCtrl操作码定义 */
#define MSND_GET_RX_STAT  0   /* 音频接收统计状态查询 */
#define MSND_GET_TX_STAT  1   /* 音频播放统计状态查询 */

/* 类型定义 */
typedef void * HMSndDev;

/*
 * 音频数据口定义，对于多路音频设备有效，可以指定当前声卡绑定的数据
 * 输入输出I2S线路，一个serial口对应一个i2s数据线
 */
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
#define MSND_SER18   (1 << 18)

/*
 * 音频帧Buffer数据格式类型定义:
 * SER : serial的缩写，对应串行数据线(如I2S数据线或TDM时分复用数据线)
 * SLOT: 每路串行数据中2个同步信号之间可能有多个音频声道复用传输，用时隙号表示
 * ##物理线路数据传输模型如下：
 *  Fs: __|~~|__________________________|~~|___________________________|~~|_
 *        |<----- sample 0 ------------>|<----------sample 1 --------->|
 *
 * +------+-------+-------+-----+-------+-------+-------+---------------
 *  SER0: | SLOT0 | SLOT1 | ... | SLOTx | SLOT0 | ...
 * +------+-------+-------+-----+-------+-------+-------+---------------
 *  SER1: | SLOT0 | SLOT1 | ... | SLOTx | SLOT0 | ...
 * +------+-------+-------+-----+-------+-------+-------+---------------
 *   ...
 * +------+-------+-------+-----+-------+-------+-------+---------------
 *  SERn: | SLOT0 | SLOT1 | ... | SLOTx | SLOT0 | ...
 * +------+-------+-------+-----+-------+-------+-------+---------------
 *
 * 其中每个serial的每个slot对应一个音频声道，
 * 比如：Chnl[0]->SER0_SLOT0; Chnl[1]->SER1_SLOT0; Chnl[2]->SER0_SLOT1
 * 有些采集设备采集到的数据由于DMA的限制必须交织存放，
 * 有些可以将每个声道数据连续存放在一个内存区域中
 */
enum
{
    /*
     * 所有声道数据交织存放，如，下面以2个serial+2个时隙为例说明排列方式
     * (每行是一段时长的音频数据，行与行之间内存连续):
     * SER0_SLOT0[0] SER1_SLOT0[0] SER0_SLOT1[0] SER1_SLOT1[0];
     * SER0_SLOT0[1] SER1_SLOT0[1] SER0_SLOT1[1] SER1_SLOT1[1];
     * ...
     * SER0_SLOT0[s] SER1_SLOT0[s] SER0_SLOT1[s] SER1_SLOT1[s]
     */
    MSND_DATA_FMT_CHNL_INTERLEAVED,

    /*
     * 每个声道数据独立连续存放，下面以2个serial+2个时隙为例说明排列方式
     * (行与行之间内存连续):
     * Single Chnl[0]: SER0_SLOT0[0] SER0_SLOT0[1] ... SER0_SLOT0[s];
     * Single Chnl[1]: SER1_SLOT0[0] SER1_SLOT0[1] ... SER1_SLOT0[s];
     * Single Chnl[2]: SER0_SLOT1[0] SER0_SLOT1[1] ... SER0_SLOT1[s];
     * Single Chnl[3]: SER1_SLOT1[0] SER1_SLOT1[1] ... SER1_SLOT1[s];
     */
    MSND_DATA_FMT_CHNL_NON_INTERLEAVED,

    /*
     * 每个Serial的声道数据独立连续存放，对于I2S来说就是多路立体声采集时
     * 每路立体声数据独立连续存放，下面以2个serial+2个时隙为例说明排列方式
     * (行与行之间内存连续):
     * Stereo[0]: SER0_SLOT0[0] SER0_SLOT1[0] SER0_SLOT0[1] SER0_SLOT1[1]...;
     * Stereo[1]: SER1_SLOT0[0] SER1_SLOT1[0] SER1_SLOT0[1] SER1_SLOT1[1]...;
     */
    MSND_DATA_FMT_SER_NON_INTERLEAVED
};


typedef struct{
    u32    dwFBufId;    /* 帧BUF的索引号，驱动内部使用，用户不能修改 */
    u8    *pbyFBuf;     /* 帧BUF的指针，指向帧数据Buf；
                           用户如果填NULL的话驱动自动分配1个数据BUF，否则使用用
                           户指定的地址作为数据BUF。
                           !!! 如果是用户分配，有一些限制条件:
                          1、用户必须保证Buf的对齐，即起始地址必须是128字节对齐;
                            BUF大小=dwBytesPerSample*dwSamplePerFrame*dwChnlNum;
                          2、关闭设备时驱动不会释放这些内存 */
    BOOL32 bUseCache;   /* 仅对于用户分配Buf有效，驱动自动分配的为带cache的；
                           为TRUE表示用户分配的Buf带cache，驱动会进行刷cache处理
                           为FALSE为不带cache的，驱动不做刷cache处理 */
    u32    dwTimeStamp; /* 帧的时间戳，采集时用户可以读取当前帧的时间搓 */
} TMSndFBufDesc;

/* 音频IO设备创建的参数结构定义
 *  在buffer中 AUD_SER0 到 AUD_SERn 路从左到右交错分布，长度为buffer的n分之1,
    无法设置 AUD_SERn 在buffer中的位置。如采集用了SER1 SER2 和 SER3，则内存中
    数据排列为:
        SER1_L SER2_L SER3_L SER1_R SER2_R SER3_R ... 这和DM647不同
 *
 *  dwChnlCfg配置举例:
 *                  物理口                  对应宏
 *  H600:
 *      Asp0采集    模拟音频                MSND_SER0
 *                  数字MIC                 MSND_SER4 (固定48K 32位采样)
 *      Asp0播放    3.5音频接口             MSND_SER1
 *                  扬声器                  MSND_SER5
 *  H700:
 *      Asp0采集    RCA模拟音频             MSND_SER1
 *                  卡农MIC                 MSND_SER3
 *                  数字MIC                 MSND_SER4 (固定48K 32位采样)
 *      Asp0播放    RCA模拟音频             MSND_SER0
 *                  6.5平衡输出             MSND_SER2
 *                  扬声器                  MSND_SER5
 *      Asp1采集    HDMI音频                MSND_SER0 (视输入源格式)
 *
 */
typedef struct{
    u32   dwBytesPerSample;   /* 一个样本的字节数: 1 2 4 */
    u32   dwSamplePerFrame;   /* 一帧的样本个数 */
    u32   dwChnlNum;          /* 声道个数，2的整数倍，即n路立体声，1帧的字节数
                                 =dwBytesPerSample*dwSamplePerFrame*dwChnlNum */
    u32   dwChnlCfg;          /* 填0表示按默认配置serial输入输出线路, 其他值填
                                 MSND_SER0等的集合体，高级用户使用 */
    u32   dwFrameNum;         /* 缓存Frame的个数，范围: 2~MSND_BUF_MAX_NUM-1 */
    u32   dwSampleFreq;       /* 8000，48000，96000，192000Hz ... */
    u32   dwSampleBit;        /* 采样位宽: 8 12 16 20 24 28 32,
                                 填0则自动计算为dwBytesPerSample*8
                                !!如dwSampleBit=32表示线路数据为32位采样，部分音
                                频IO设备可以设置dwBytesPerSample=2只取高16位 */
    u32   dwDataFmt;          /* 音频数据格式如MSND_DATA_FMT_CHNL_INTERLEAVED */
    TMSndFBufDesc *pBufDescs; /* 指向用户分配的FBufDesc结构变量数组的首地址，
                                 用户可以自己分配数据Buf，将指针传递给驱动
                                 数组个数为dwFrameNum,
                                 ! 注意: 音频需要128字节边界对齐；
                                 对于不想自己分配Buf的用户填为NULL时即可，
                                 驱动会按照前面的参数自动分配BUF */
} TMSndDevParam;

/* 音频采集统计状态结构定义，对应操作码: MSND_GET_RX_STAT */
typedef struct{
    u32   dwFrameTotal;       /* 最大能缓存的音频数据帧的总数 */
    u32   dwFrameSize;        /* 一帧音频数据的字节数,多路声道的总和 */
    u32   dwFramesCanRd;      /* 能读取的音频数据帧的个数 */
    u32   dwBytesCanRd;       /* 能读取的音频数据字节数，回声抵消时要用 */
    u32   dwLostBytes;        /* 对于采集表示丢弃的字节数，没有可用buf时发生 */
    u32   dwDmaErr;           /* dma出错的次数 */
    u32   dwOverRunErr;       /* Overrun出错的次数 */
    u32   dwSyncErr;          /* 帧同步出错的次数 */
    u32   dwPingPongErr;      /* ping-pong反转出错的次数 */
    u32   adwReserved[5];     /* reserved */
} TMSndRxStat;

/* 音频播放状态结构定义，对应操作码: MSND_GET_TX_STAT */
typedef struct{
    u32   dwFrameTotal;       /* 最大能缓存的音频数据帧的总数 */
    u32   dwFrameSize;        /* 一帧音频数据的字节数 */
    u32   dwFramesCanWrt;     /* 能写入的音频数据帧的个数 */
    u32   dwBytesCanWrt;      /* 驱动中能写入的音频数据字节数，
                                 dwFrameTotal*dwFrameSize-dwBytesCanWrt=当前待播
                                 放的音频数据字节数 */
    u32   dwMuteBytes;        /* 对于播放表示播放静音的字节数，一般在没有音频数
                                 据时发生，回声抵消时要用 */
    u32   dwDmaErr;           /* dma出错的次数 */
    u32   dwUnderRunErr;      /* Underrun出错的次数 */
    u32   dwSyncErr;          /* 帧同步出错的次数 */
    u32   dwPingPongErr;      /* ping-pong反转出错的次数 */
    u32   adwReserved[5];     /* reserved */
} TMSndTxStat;


/*==============================================================================
    函数名      : MSndOpen
    功能        : 音频IO设备打开，1个dwDevId可以打开2次，分别为INPUT/OUPUT
    输入参数说明: dwDevId: 0~MSND_DEV_MAX_NUM-1，如：MSND_DEV_ID_McASP;
                  nMode: MSND_IOM_INPUT/MSND_IOM_OUTPUT
                  ptParam: 打开的参数
                  phDev: 设备控制句柄指针
    返回值说明  : 错误返回MSND_EFAIL或错误码；成功返回MSND_EOK和控制句柄
------------------------------------------------------------------------------*/
s32 MSndOpen(u32 dwDevId, s32 nMode, TMSndDevParam *ptParam, HMSndDev *phDev);

/*==============================================================================
    函数名      : MSndClose
    功能        : 音频IO设备关闭。
    输入参数说明: hDev: MSndOpen函数返回的句柄;
    返回值说明  : 错误返回MSND_EFAIL或错误码；成功返回MSND_EOK
------------------------------------------------------------------------------*/
s32 MSndClose(HMSndDev hDev);

/*==============================================================================
    函数名      : MSndRead
    功能        : 从音频设备读数据，读取长度必须是dwBytesPerSample*dwChnlNum的
                  整数倍，不要破坏声道的完整性。
    输入参数说明: hDev: 以MSND_IOM_INPUT模式调用MSndOpen函数返回的句柄;
                  pBuf: 指向用户分配的Buf，用来存放采集的音频数据
                  size: 要读取的数据字节数
                  nTimeoutMs: -1=wait forever; 0=no wait;其他正值为超时毫秒数
    返回值说明  : 错误返回MSND_EFAIL；超时返回0；成功返回读到的字节数(=size)
------------------------------------------------------------------------------*/
s32 MSndRead(HMSndDev hDev, void *pBuf, size_t size, s32 nTimeoutMs);

/*==============================================================================
    函数名      : MSndWrite
    功能        : 向音频设备写数据，数据长度必须是dwBytesPerSample*dwChnlNum的
                  整数倍，不要破坏声道的完整性。
    输入参数说明: hDev: 以MSND_IOM_OUTPUT模式调用MSndOpen函数返回的句柄;
                  pData: 指向用户存放待播放的音频数据
                  size: 要播放的数据字节数
                  nTimeoutMs: -1=wait forever; 0=no wait;其他正值为超时毫秒数
    返回值说明  : 错误返回MSND_EFAIL；超时返回0；成功返回写入的字节数(=size)
------------------------------------------------------------------------------*/
s32 MSndWrite(HMSndDev hDev, void *pData, size_t size, s32 nTimeoutMs);

/*==============================================================================
    函数名      : MSndCtrl
    功能        : 音频IO设备控制，目前定义了
                    MSND_GET_RX_STAT: pArgs为TMSndRxStat *
                    MSND_GET_TX_STAT: pArgs为TMSndTxStat *
                  ......
    输入参数说明: hDev: 调用MSndOpen函数返回的句柄;
                  nCmd: 操作码；pArgs: 参数指针
    返回值说明  : 错误返回MSND_EFAIL或错误码；成功返回MSND_EOK
------------------------------------------------------------------------------*/
s32 MSndCtrl(HMSndDev hDev, s32 nCmd, void *pArgs);

/*==============================================================================
    函数名      : MSndGetVer
    功能        : 模块版本号查询。
    输入参数说明: pchVer:  给定的存放版本信息的buf指针
                  dwBufLen: 给定buf的长度
    返回值说明  : 版本的实际字符串长度。小于0为出错;
                  如果实际字符串长度大于dwBufLen，赋值为0
------------------------------------------------------------------------------*/
s32 MSndGetVer(char *pchVer, u32 dwBufLen);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __AUD_MSND_H */
