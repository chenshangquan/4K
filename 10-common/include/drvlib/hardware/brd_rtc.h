/*
 * Kedacom Hardware Abstract Level
 *
 * brd_rtc.h
 *
 * Copyright (C) 2013-2020, Kedacom, Inc.
 *
 * History:
 *   2013/09/22 - [xuliqin] Create
 *
 */

#ifndef _BRD_RTC_H
#define _BRD_RTC_H

#include <drvlib_def.h>

#ifdef __cplusplus
extern "C" {
#endif

int BrdTimeGet(struct tm *tTime);
int BrdTimeSet(const struct tm *tTime);
int BrdSetRtcToSysClock(void);
int BrdSetSysToRtcClock(void);

#ifdef __cplusplus
}
#endif

#endif
