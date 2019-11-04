#ifndef _CPL_EXTERNAL_H_
#define _CPL_EXTERNAL_H_
#include <signal.h>

#include <cpl_lock.h>
#include <cpl_list.h>
#include <cpl_task.h>

/* extern lib init/destroy routine */
extern int cpl_init();

/* extern task related routine */
extern void* task_get_stg(int);
extern cplt_list_head*	task_create_list();
extern int task_exit(int);
extern int task_wait(int, void**);
extern int task_wait_list(void);
extern int task_kill_list(cplt_list_head*);
extern int task_kill(int);
extern int task_need_exit(void);
extern int task_create( 
	const char*, 
	cplt_list_head*, 
	task_attr*,
	void* (*)(void*), 
	void*	args );
extern int task_resched(void);
extern int task_create_stg(void (*)(void*));
extern int task_destroy_stg(int);
extern int task_set_stg(int, const void*);
extern void* task_get_stg(int);
extern int task_excute_once(task_once*, void (*)(void));
extern int task_self(void);

/* extern signal related routine */
extern int task_sig_blockall(sigset_t*);
extern int task_sig_restore(sigset_t*);
extern int task_sigaction(int, const struct sigaction*, struct sigaction*);
extern int task_sigmask(int, sigset_t*, sigset_t*);
extern int task_sigwait(const sigset_t*, int*);
extern int task_send_signal(int, int);

/* extern lock related routine */
extern cpl_rwlock rwlock_create();
extern int rwlock_rdlock(cpl_rwlock);
extern int rwlock_wrlock(cpl_rwlock);
extern int rwlock_unlock(cpl_rwlock);
extern int rwlock_destroy(cpl_rwlock);

extern cpl_sem semb_create();
extern int semb_destroy(cpl_sem);
extern int semb_lock(cpl_sem);
extern int semb_trylock(cpl_sem);
extern int semb_unlock(cpl_sem l);

extern cpl_mutex task_mutex_create();
extern int task_mutex_destroy(cpl_mutex);
extern int task_mutex_lock(cpl_mutex);
extern int task_mutex_trylock(cpl_mutex);
extern int task_mutex_unlock(cpl_mutex);

extern cpl_rwlock rwlock_create(void);
extern int rwlock_destroy(cpl_rwlock);
extern int rwlock_rdlock(cpl_rwlock);
extern int rwlock_tryrdlock(cpl_rwlock);
extern int rwlock_wrlock(cpl_rwlock);
extern int rwlock_trywrlock(cpl_rwlock);
extern int rwlock_unlock(cpl_rwlock);

#endif
