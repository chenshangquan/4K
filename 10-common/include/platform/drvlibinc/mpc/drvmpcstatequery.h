/*****************************************************************************
模块名      : mcu
文件名      : drvMpcStateQuery.h
相关文件    : drvMpcStateQuery.c
文件实现功能:  内部使用的一些宏定义和函数声明.
作者        : 张方明
版本        : V1.0  Copyright(C) 2003-2005 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2003/8/19   01a         张方明      创建	
******************************************************************************/
#ifndef __INCdrvMpcStateQueryh
#define __INCdrvMpcStateQueryh

#ifdef __cplusplus
extern "C" {
#endif

#define VER_MCUDRVLIB  ( const char * )"MCUDrvLib 30.01.04.02.040715"


/* fpga读寄存器中bit位掩码定义 */
#define FPGA_REG_BA        ((UINT8)0X80) 
#define FPGA_REG_HSNSI     ((UINT8)0X40) 
#define FPGA_REG_MS        ((UINT8)0X20) 
#define FPGA_REG_OUS       ((UINT8)0X10) 
#define FPGA_REG_HSRSTI    ((UINT8)0X08) 
#define FPGA_REG_MKA       ((UINT8)0X07)
 
#define FPGA_REG_DC48L     ((UINT8)0X80) 
#define FPGA_REG_DC48R     ((UINT8)0X40) 
#define FPGA_REG_DC5L      ((UINT8)0X20) 
#define FPGA_REG_DC5R      ((UINT8)0X10) 
#define FPGA_REG_HPIRDY    ((UINT8)0X08) 
#define FPGA_REG_LOCK      ((UINT8)0X04) 
#define FPGA_REG_TRACK     ((UINT8)0X02) 
#define FPGA_REG_FREERUN   ((UINT8)0X01)

#define FPGA_REG_HWVER     ((UINT8)0Xf0) 
#define FPGA_REG_FPGAVER   ((UINT8)0X0f)
 
#define FPGA_RD_REG0       ((UINT8)0X00) 
#define FPGA_RD_REG1       ((UINT8)0X01)
#define FPGA_RD_REG2       ((UINT8)0X02) 





/* 指示灯状态数据结构 */
typedef struct{
    UINT8 byLedRUN;     /* 系统运行灯 */
    UINT8 byLedDSP;     /* DSP运行灯 */
    UINT8 byLedALM;     /* 系统告警灯 */
    UINT8 byLedMS;      /* 主备用指示灯 */
    UINT8 byLedOUS;     /* ous指示灯 */
    UINT8 byLedSYN;     /* 同步指示灯 */
    UINT8 byLedLNK0;    /* 以太网0连接灯 */
    UINT8 byLedLNK1;    /* 以太网1连接灯 */
    UINT8 byLedNMS;     /* nms指示灯 */
    UINT8 byLedNORM;    /* 灯板上正常指示灯 */
    UINT8 byLedNALM;    /* 灯板上一般告警指示灯 */
    UINT8 byLedSALM ;   /* 灯板上严重告警指示灯 */
}TBrdMPCLedStateDesc;

/* 函数声明 */
UINT8 BrdCheckPowerState(void);
UINT8 BrdCheckSyncLockState(void);

UINT8 BrdMPCQueryAnotherMPCState(void);  /* 对端主处理机板是否在位查询 */
UINT8 BrdMPCQueryLocalMSState(void);     /* 当前主处理机板主备用状态查询 */
UINT8 BrdMPCQuerySDHType(void);          /* 光模块种类查询 */
UINT8 BrdMPCQueryNetSyncMode(void);      /* 锁相环工作模式查询 */
STATUS BrdMPCQueryLedState(TBrdMPCLedStateDesc *ptBrdMPCLedState);  /* 闪灯模式查询 */
void mcudrvver(void);               /* mcuDrv版本信息打印 */

#ifdef __cplusplus
}
#endif

#endif /* __INCdrvMpcPatchh */