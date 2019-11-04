/**************************************************************
*     Copyright (C) 2004-2005, KEDACOM
*
* 1.FILENAME    : cpl.h
* 2.COMPONENT   : Cross Platfrom Libaray top header
* 3.AUTHOR      : Zeng Zhaoming (SH)
* 4.DATE        : 2005-9-15 10:01
* 5.DESCRIPTION : user interface defines
* 6 Changelog	:
	2005-9-15 10:02: Zzm write init version
***************************************************************/
#ifndef _CPL_INTERNAL_H_
#define _CPL_INTERNAL_H_

/* include custom headers */
#include <cpl_def.h>
#include <cpl_debug.h>
#include <cpl_signal.h>

/* define lib init routines */
extern int cpl_init();
extern int cpl_tm_init();
extern int cpl_signal_init();
extern int cpl_lock_init();
extern int cpl_signal_destroy();
extern int cpl_tm_destroy();
extern int cpl_lock_uninit();
extern struct cpl_init cpl_init_info;

/* define task lib related */
extern void* task_get_stg(int);
extern int task_self();
extern int task_exit(int);

#include <cpl_task.h>
extern cplt_task* manager_task;
extern int cpl_get_task(cplt_task*);
extern int cpl_put_task(cplt_task*);

/* define signal lib related */
extern int task_sig_blockall(sigset_t*);
extern int task_sig_restore(sigset_t*);
extern int task_siglist_cleanup(cplt_task*);
extern int cpl_siglist_clone(struct cpl_task_signal*, struct cpl_task_signal*);
extern int task_signal_enable(cplt_task*);

/* define lock related */
extern int tasklock_moveto_garbage(cplt_task*);
extern int cpl_lock_man_chashlock();
extern cpl_rwlock rwlock_create(void);
extern int rwlock_destroy(cpl_rwlock);
extern int rwlock_rdlock(cpl_rwlock);
extern int rwlock_tryrdlock(cpl_rwlock);
extern int rwlock_wrlock(cpl_rwlock);
extern int rwlock_trywrlock(cpl_rwlock);
extern int rwlock_unlock(cpl_rwlock);

#endif
