/*
 * Kedacom Hardware Abstract Level
 *
 * sys_wdt.h
 *
 * Copyright (C) 2013-2020, Kedacom, Inc.
 *
 * History:
 *   2013/09/22 - [xuliqin] Create
 *
 */

#ifndef _SYS_WDT_H
#define _SYS_WDT_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Watch Dog Timer
 */

typedef struct
{
	int nTimeout;          /* in second */
} TWdParams;

typedef struct
{
	u8  byOpened;           /* 1 = opened */
	int nTimeout;          /* in second */
} TWdStatus;


int SysOpenWdGuard(TWdParams *ptParams);
int SysCloseWdGuard(void);
int SysNoticeWdGuard(void);
int SysWdGuardStatusGet(TWdStatus *ptStatus);
int SysHwReset(int nNormalReboot);

#ifdef __cplusplus
}
#endif

#endif
