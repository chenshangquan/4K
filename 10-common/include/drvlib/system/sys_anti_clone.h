/*
 * Kedacom anti-clone subsystem
 *
 * sys_anti_clone.h
 *
 * Copyright (C) 2013-2020, Kedacom, Inc.
 *
 * History:
 *   2015/07/30 - [liuqinglin] Create
 *
 */
#ifndef _SYS_ANTI_CLONE_H
#define _SYS_ANTI_CLONE_H

#ifdef __cplusplus
extern "C" {
#endif

/* SysACC - Anti Clone Authentication
* @force: 1 - exit when it is running on a clone device 
*		 0 - only return !0 rather than exit
*/
int SysACC(int force);

#ifdef __cplusplus
}
#endif

#endif
