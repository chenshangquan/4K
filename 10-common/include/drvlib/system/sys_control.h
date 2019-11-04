/*
 * Kedacom Hardware Abstract Level
 *
 * sys_control.h
 *
 * Copyright (C) 2013-2020, Kedacom, Inc.
 *
 * History:
 *   2013/09/22 - [xuliqin] Create
 *
 */

#ifndef _SYS_CONTROL_H
#define _SYS_CONTROL_H

#include <drvlib_def.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PWR_UP_INIT 0x1 /* bootloader status */
#define PWR_UP_IOS  0x2 /* kernel status */
#define PWR_UP_SUC  0x0 /* app status */

int SysSetBootStatus(u32 dwStatus);

#ifdef __cplusplus
}
#endif

#endif

