/*******************************************************************************
 * 模块名  : DSPCCI
 * 文件名  : dspcci_common.h
 * 相关文件: .c
 * 文件实现功能: host和dsp双方cci通信协议相关的宏和数据结构定义，被两者同时包含，
 *           注意：包含本头文件前必须包含相应的数据类型头文件，host包含kdvtype.h
 *                 dsp侧包含dsp_typedefs.h，不可混淆！
 * 作者    : 张方明
 * 版本    : V1.0  Copyright(C) 2014-2020 KEDACOM, All rights reserved.
 * -----------------------------------------------------------------------------
 * 修改记录:
 * 日  期      版本        修改人      修改内容
 * 2014/03/01  1.1.1       张方明      创建
*******************************************************************************/
#ifndef __DSPCCI_COMMON_H
#define __DSPCCI_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif


/* 版本信息 */
#define DSPCCI_MOD_VERSION          (const char *)"DspCciLib 1.3.19.20100701"

/* 极限定义 */
#define DSPCCI_DSP_MAXNUM               5   /* 最多支持的DSP的个数 */

/* 消息打印宏定义 */
#define DSPCCI_MAX_PRT_MSGS             100 /* 打印信息的最大个数 */
#define DSPCCI_MAX_PRT_MSGLEN           320 /* 打印信息的最大长度 */

/* DSPCCI通信消息属性的宏定义 */
#define DSPCCI_DN_MSGQ_MAX              256 /* 最大下行消息队列数 */
#define DSPCCI_UP_MSGQ_MAX              256 /* 最大上行消息队列数 */
#define DSPCCI_ERR_LOG_MAX_NUM          32  /* DSP错误记录的最大个数 */
#define DSPCCI_MSG_ALIGN_BYTES          32  /* n字节对齐，要求是TDspCciMsgHead
                                               结构大小的整数倍 */
#define DSPCCI_PROTOCOL_VERSION         1   /* DSPCCI的协议版本号，协议发生改变
                                               时加1，HOST和DSP必须保持一致 */

/* 幻数宏定义 */
#define DSPCCI_MAGIC_NUMBER             0xbeafbeaf
#define DSPCCI_START_MAGIC_NUMBER       0xdaaddeed

/* 消息类型宏定义 */
#define DSPCCI_IS_USR_MSG               0   /* 用户消息 */
#define DSPCCI_IS_HOST_LOOPBACK_MSG     1   /* 主机自环测试消息 */
#define DSPCCI_IS_HOST_SEND_TEST_MSG    2   /* 主机发送测试消息*/
#define DSPCCI_IS_DSP_SEND_TEST_MSG     3   /* DSP发送测试消息 */
#define DSPCCI_IS_DSP_PRINT_MSG         4   /* DSP打印消息 */

/* 返回值宏定义 */
#define DSPCCI_SUCCESS                  0   /* CCI通信连接建立成功 */
#define DSPCCI_FAILURE                 -1   /* CCI操作失败 */
#define DSPCCI_NOT_CONNECTED           -2   /* CCI通信没有建链 */
#define DSPCCI_SMEM_CORRUPT            -3   /* CCI共享内存区被破坏 */
#define DSPCCI_LENGTH_ERROR            -4   /* CCI通信信息长度错误 */
#define DSPCCI_QUEUE_FULL              -5   /* CCI消息队列已满 */
#define DSPCCI_MSG_LOST                -6   /* CCI消息丢失 */
#define DSPCCI_PARAM_ERR               -7   /* 参数错误 */
#define DSPCCI_NOT_SUPPORT             -8   /* 不支持的操作 */
#define DSPCCI_MULTI_OPEN              -9   /* 多次打开设备 */
#define DSPCCI_NOT_OPEN                -10  /* 设备没有打开 */
#define DSPCCI_OPEN_FAIL               -11  /* 设备打开失败 */
#define DSPCCI_IOC_FAIL                -12  /* 设备ioctl失败 */
#define DSPCCI_NO_MEM                  -13  /* 内存不足 */
#define DSPCCI_TIMEOUT                 -14  /* 操作超时 */
#define DSPCCI_QUEUE_EMPTY             -15  /* CCI消息队列空 */
#define DSPCCI_PEER_CLOSED             -16  /* CCI通信远端设备断开 */

/* CCI通信消息属性的宏定义 */
#define DSPCCI_UPCHNL                   0   /* 上行通道编号 */
#define DSPCCI_DNCHNL                   1   /* 下行通道编号 */


/* -------------------------------------------------------------------------- *
 * 以下结构仅适用于HOST可以直接访问DSP侧内存的通信方式(如PCI、PCIE、HPI)      *
 * 如果是其他比较特殊的通信方式以各自的私有协议为准，如基于spi接口的fifo通信  *
 *----------------------------------------------------------------------------*/

/* START区相对于RAM_BASE的偏移量，最前面0x20空间保留, 
   PCI通信时该区0x20大小用于reset_vector，负责引导程序 */
#define DSPCCI_START_SHM_OFFSET         0x20

/* 类型定义 */
typedef void * HDspCciObj;                  /* DSP通信对象类型 */


/* START区结构定义 */
typedef struct {
    /* start区的幻数，DSP先初始化为0xdaaddeed,之后主机初始化为0xbeafbeaf */
    volatile u32 dwCciStartMarker;
    /* 主机启动标志； 1--启动 */
    volatile u32 dwCciHostStartupFlag;
    /* Info区有效标志；主机初始化为0，由DSP分配完INFO区内存后设置为1 */
    volatile u32 dwCciInfoAvailableFlag;
    /* info区基地址，主机初始化为0 */
    volatile u32 dwCciInfoBaseAddr;
    /* DSP侧CCI版本号,由DSP侧填写，主机侧校验是否匹配 */
    volatile u32 dwDspCciVer;
    /* 主机侧CCI版本号,由主机侧填写，DSP侧校验是否匹配 */
    volatile u32 dwHostCciVer;
    /* 使用brdwrapperdef.h中单板种类ID号宏定义 */
    volatile u32 dwBrdID;
    /* 硬件版本号 */
    volatile u32 dwHwVer;
    /* EPLD/FPGA/CPLD的程序版本号 */
    volatile u32 dwFpgaVer;
    /* 标识当前是哪一块dsp，从0开始编号 */
    volatile u32 dwDspId;
} TDspCciStartBuf;


/* 通道控制信息结构定义 */
typedef struct{
    /* 内存池基地址, DSPCCI_MSG_ALIGN_BYTES对齐 */
    volatile u32 dwBufBase;
    /* 消息的最大长度(按BYTE计)，要求8的整数倍 */
    volatile u32 dwMaxMsgLen;
    /* 最多缓存的消息个数 */
    volatile u32 dwMaxMsgs;
    /* 内存池大小,为(dwMaxMsgLen*dwMaxMsgs)作DSPCCI_MSG_ALIGN_BYTES对齐 */
    volatile u32 dwBufSize;
    /* 内存池读指针,为相对内存池基地址的偏移量 */
    volatile u32 dwReadPtr;
    /* 内存池写指针,为相对内存池基地址的偏移量 */
    volatile u32 dwWritePtr;
    /* 已经写入的数据包个数 */
    volatile u32 dwWriteNum;
    /* 已经读出的数据包个数 */
    volatile u32 dwReadNum;
    /* 保存下一个接收消息的地址 */
    volatile u32 dwNextRcvMsgPtr;
    /* DSP发包/收包计数 */
    volatile u32 dwDspRxTxMsgs;
    /* DSP成功发包/接收错包计数 */
    volatile u32 dwDspRxErrOrTxOkMsgs;
    /* DSP发送/接收数据量KByte */
    volatile u32 dwDspRxTxKBytes;
    /* DSP发送/接收数据量Byte */
    volatile u32 dwDspRxTxBytes;
} TDspCciChnlInfo;


/* INFO区结构定义 */
typedef struct{
    /* INFO区的幻数,有效值为0xbeafbeaf */
    volatile u32 dwCciInfoMarker;
    /* 主机就绪标志：1-请求分配通道控制区；3-请求分配通道内存池；
                     7-通知dsp通信创建ok */
    volatile u32 dwHostRdyFlag;
    /* DSP就绪标志：1--已分配通道控制区；3--已分配通道内存池； */
    volatile u32 dwDspRdyFlag;
    /* DSP心跳：由DSP驱动不断累加，主机侧检测 */
    volatile u32 dwDspHeartBeat;
    volatile u32 dwUpChnlNum;                /* 上行通道个数 */
    volatile u32 dwDnChnlNum;                /* 下行通道个数  */
    volatile u32 dwUpChnlInfoBase;           /* 上行通道管理区基地址 */
    volatile u32 dwDnChnlInfoBase;           /* 下行通道管理区基地址  */

    volatile u32 dwDspPrtEn;                 /* 允许打印标志  */
    volatile TDspCciChnlInfo tPrtChnlInfo;   /* 打印通道控制信息 */
    /* DSP错误纪录，由DSP出错后填写 */
    volatile u32 dwDspErrLog[DSPCCI_ERR_LOG_MAX_NUM];
} TDspCciInfoBuf;


/* 消息头部结构定义 */
typedef struct{
    volatile u32 dwMsgMarker;   /* 消息头幻数,有效值为0xbeafbeaf */
    volatile u32 dwMsgType;     /* 消息类型：参考: 消息类型宏定义 */
    volatile u32 dwMsgLen;      /* 消息体长度 */
    volatile u32 dwNextMsgAddr; /* 下一个消息的偏移地址(相对dwBufBase)，
                                   DSPCCI_MSG_ALIGN_NUMBER字节对齐 */
} TDspCciMsgHead;

/* -------------------------------------------------------------------------- *
 * 以上结构仅适用于HOST可以直接访问DSP侧内存的通信方式(如PCI、PCIE、HPI)  *
 * 如果是其他比较特殊的通信方式以各自的私有协议为准，如基于spi接口的fifo通信  *
 *----------------------------------------------------------------------------*/


/* 消息描述结构定义 */
typedef struct{
    u32   dwMsgType;            /* 消息类型，见: 消息类型宏定义 */
    void *pbyMsg1;              /* 用户消息1指针 */
    void *pbyMsg2;              /* 用户消息2指针，接收时该段无效 */
    u32   dwMsg1Len;            /* 用户消息1长度 */
    u32   dwMsg2Len;            /* 用户消息2长度，接收时该段无效 */
} TDspCciMsgDesc;


#ifdef __cplusplus
}
#endif

#endif /* __DSPCCI_COMMON_H */
