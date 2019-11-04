/*****************************************************************************
模块名      : mcu
文件名      : drvMpcAlarm.h
相关文件    : drvMpcPatch.c
文件实现功能:  内部使用的一些宏定义和函数声明.
作者        : 张方明
版本        : V1.0  Copyright(C) 2003-2005 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2003/8/19   01a         张方明      创建	
******************************************************************************/
#ifndef __INCdrvMpcAlarmh
#define __INCdrvMpcAlarmh

#ifdef __cplusplus
extern "C" {
#endif

/* 电源告警数据结构 */
typedef struct{
    BOOL bAlarmPowerDC48VLDown;     /* 左电源-48V异常 */
    BOOL bAlarmPowerDC48VRDown;     /* 右电源-48V异常 */
    BOOL bAlarmPowerDC5VLDown;      /* 左电源+5V异常 */
    BOOL bAlarmPowerDC5VRDown;      /* 右电源+5V异常 */
}TBrdMPCAlarmPowerDesc;

/* 电源风扇告警数据结构 */
typedef struct{
    BOOL bAlarmPowerFanLLDown;      /* 左电源左风扇停转 */
    BOOL bAlarmPowerFanLRDown;      /* 左电源右风扇停转 */
    BOOL bAlarmPowerFanRLDown;      /* 右电源左风扇停转 */
    BOOL bAlarmPowerFanRRDown;      /* 右电源右风扇停转 */
}TBrdMPCAlarmPowerFanDesc;

/* MPC单板告警数据结构定义 */
typedef struct{
    BOOL bAlarmNetClkLockFailed;     /*  锁相环没有锁住参考时钟 */
    TBrdMPCAlarmPowerDesc tBrdMPCAlarmPower; /* 电源告警 */
    TBrdMPCAlarmPowerFanDesc tBrdMPCAlarmPowerFan; /* 电源风扇告警 */
}TBrdMPCAlarmVeneer;

/* SDH告警结构定义 */
typedef struct{
    BOOL bAlarmLOS;         /* 信号丢失 */
    BOOL bAlarmLOF;         /* 帧丢失 */
    BOOL bAlarmOOF;         /* 帧失步 */
    BOOL bAlarmLOM;         /* 复帧丢失 */
    BOOL bAlarmAU_LOP;      /* 管理单元指针丢失 */
    BOOL bAlarmMS_RDI;      /* 复用段远端缺陷指示 */
    BOOL bAlarmMS_AIS;      /* 复用段报警指示 */
    BOOL bAlarmHP_RDI;      /* 高阶通道远端缺陷指示 */
    BOOL bAlarmHP_AIS;      /* 高阶通道报警指示 */
    BOOL bAlarmRS_TIM;      /* 再生段通道踪迹字节不匹配 */
    BOOL bAlarmHP_TIM;      /* 阶通道踪迹字节不匹配 */
    BOOL bAlarmHP_UNEQ;     /* 高阶通道信号标记字节未装载 */
    BOOL bAlarmHP_PLSM;     /* 高阶通道信号标记字节不匹配 */

    BOOL bAlarmTU_LOP;      /* 支路单元指针丢失 */
    BOOL bAlarmLP_RDI;      /* 低阶通道远端缺陷指示 */
    BOOL bAlarmLP_AIS;      /* 低阶通道报警指示 */
    BOOL bAlarmLP_TIM;      /* 低阶通道踪迹字节不匹配 */
    BOOL bAlarmLP_PLSM;     /* 低阶通道信号标记字节不匹配 */
}TBrdMPCAlarmSDH;


STATUS BrdMPCAlarmVeneerStateScan(TBrdMPCAlarmVeneer *pTBrdMPCAlarmVeneer); /* MPC单板告警函数声明 */
STATUS BrdMPCAlarmSDHStateScan(TBrdMPCAlarmSDH *pTBrdMPCAlarmSDH);          /* MPC SDH告警函数声明 */


#ifdef __cplusplus
}
#endif

#endif /* __INCdrvMpcPatchh */