/*****************************************************************************
模块名      : mcu
文件名      : drvCriControl.h
相关文件    : drvCriControl.c
文件实现功能:  内部使用的一些宏定义和函数声明.
作者        : 张方明
版本        : V1.0  Copyright(C) 2003-2005 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2003/8/19   01a         张方明      创建	
******************************************************************************/
#ifndef __INCdrvCriControlh
#define __INCdrvCriControlh

#ifdef __cplusplus
extern "C" {
#endif

#include "time.h"
#include "timers.h"

UINT8 BrdFpgaRead(UINT8 Addr);
STATUS BrdTimeGet( struct tm* pGettm );        /* 读取RTC时间 */
STATUS BrdTimeSet( struct tm* pSettm );        /* 设置RTC和系统时间 */ 

#ifdef __cplusplus
}
#endif

#endif /* __INCdrvCriPatchh */