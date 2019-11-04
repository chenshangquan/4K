/*****************************************************************************
模块名      : mcu
文件名      : drvCriAlarm.h
相关文件    : drvCriAlarm.c
文件实现功能:  内部使用的一些宏定义和函数声明.
作者        : 张方明
版本        : V1.0  Copyright(C) 2003-2005 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2003/8/19   01a         张方明      创建	
******************************************************************************/
#ifndef __INCdrvCriAlarmh
#define __INCdrvCriAlarmh

#ifdef __cplusplus
extern "C" {
#endif


/* DIC告警数据结构 */
typedef struct{
    BOOL bAlarmModuleOffLine;     /* 模块离线 */
}TBrdCRIAlarmVeneer;

/* CRI 单板告警函数声明 */
STATUS BrdCRIAlarmVeneerStateScan(TBrdCRIAlarmVeneer *pTBrdCRIAlarmVeneer); 

#ifdef __cplusplus
}
#endif

#endif /* __INCdrvMpcPatchh */