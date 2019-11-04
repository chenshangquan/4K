/*****************************************************************************
模块名      : mcu
文件名      : drvCriStateQuery.h
相关文件    : drvCriStateQuery.c
文件实现功能:  内部使用的一些宏定义和函数声明.
作者        : 张方明
版本        : V1.0  Copyright(C) 2003-2005 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2003/8/19   01a         张方明      创建	
******************************************************************************/
#ifndef __INCdrvCriStateQueryh
#define __INCdrvCriStateQueryh

#ifdef __cplusplus
extern "C" {
#endif

#define VER_CRIDRVLIB  ( const char * )"CRIVxNIP 30.01.05.02.040715"


/* fpga读寄存器中bit位掩码定义 */
#define FPGA_REG_HWVER     ((UINT8)0Xf0) 
#define FPGA_REG_FPGAVER   ((UINT8)0X0f)
#define FPGA_REG_BK        ((UINT8)0X0f)
#define FPGA_REG_LAYER     ((UINT8)0X03)

#define FPGA_RD_REG0       ((UINT8)0X00) 
#define FPGA_RD_REG1       ((UINT8)0X01)
#define FPGA_RD_REG2       ((UINT8)0X02) 
#define FPGA_RD_REG3       ((UINT8)0X03)


/* 指示灯状态数据结构 */
typedef struct{
    UINT8 byLedRUN;      /* 系统运行灯 */
    UINT8 byLedMRUN;     /* VOIP/DDN模块运行灯 */
    UINT8 byLedSPD0;     /* 网口0速率指示灯 */
    UINT8 byLedLNK0;     /* 网口0联机指示灯 */
    UINT8 byLedACT0;     /* 网口0数据收发有效指示灯 */
    UINT8 byLedSPD1;     /* 网口1速率指示灯 */
    UINT8 byLedLNK1;     /* 以太网1连接灯 */
    UINT8 byLedACT1;     /* 网口1数据收发有效指示灯 */
    UINT8 byLedWERR;     /* 广义网数据错误 */
    UINT8 byLedMLNK;     /* 与MPC联机指示灯 */
}TBrdCRILedStateDesc;


UINT8 BrdCRIGetModuelState(void);   /* 查询板上模块在线否 */
STATUS BrdCRIQueryLedState(TBrdCRILedStateDesc *ptBrdCRILedState);  /* 闪灯模式查询 */
void cridrvver(void);               /* criDrv版本信息打印 */

#ifdef __cplusplus
}
#endif

#endif /* __INCdrvCriPatchh */