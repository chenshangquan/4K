/**************************************************************
*     Copyright (C) 2004-2005, KEDACOM
*
* 1.FILENAME    : cpl_task.h
* 2.COMPONENT   : Cross Platfrom Libaray task manager
* 3.AUTHOR      : Zeng Zhaoming (SH)
* 4.DATE        : 2005-09-09 11:12
* 5.DESCRIPTION : define task struct and related
***************************************************************/
#ifndef _CPL_TASK_H_
#define _CPL_TASK_H_

#include <pthread.h>

#include <lib/task/cpl_list.h>
#include <lib/task/cpl_lock.h>
#include <lib/task/cpl_atomic.h>
#include <lib/task/cpl_signal.h>

#include <lib/task/cpl_internal.h>

/* task will take 0 slot TSD */
#define TASK_SLOT_STG	0


#define CPL_MAX_TNAME	16

#define task_attr pthread_attr_t
#define task_cond pthread_cond_t
#define task_condattr pthread_condattr_t

/* define excute once variable */
#define task_once pthread_once_t
#define TASK_ONCE_INIT PTHREAD_ONCE_INIT


#if 0
typedef struct cpl_task_attr {
	int	detachable;
	int	schedulepolicy;
	struct sched_param	param;
	int	inherit;
	int	scope;
} cplt_task_attr;
#endif

typedef struct cpl_task {
	pthread_t tid;
	char	name[CPL_MAX_TNAME];

	volatile int exit_f;   //task exit flag
	volatile int sighdr_f; //in user define sig handler flag
	//reference number protect from cplt_task memory
	cplt_atomic rfno;

	//rwlock protect t_man, t_sig list
	cpl_rwlock lock;

	cplt_list_node*	t_node; //point to task_node in manage list
	cplt_list_head*	t_man;
	locktask_node_t* t_lock; //to cpl_lock task manager list header node
	struct cpl_task_signal	t_sig;
	
	cplt_bool m_head; //manage a sub list ??
	cplt_list_head* t_sublist;
} cplt_task;

extern void* task_get_stg(int);

/* get task from TASK_SLOT_STG */
static inline cplt_task* task_get()
{
	return (cplt_task*)task_get_stg(TASK_SLOT_STG);
}

/* set task to TASK_SLOT_STG */
static inline int task_set(cplt_task* t)
{
	return pthread_setspecific((pthread_key_t)TASK_SLOT_STG, (const void*)t);
}


/*============ task conditional variable related start =============*/
/* in current implement, we only simply encapsulate LinuxPthread */
static inline int task_cond_init(task_cond*	cond, task_condattr* attr)
{
	return pthread_cond_init(cond, attr);
}

static inline int task_cond_destroy(task_cond* cond)
{
	return pthread_cond_destroy(cond);
}

static inline int task_cond_wakeup(task_cond* cond)
{
	return pthread_cond_signal(cond);
}

static inline int task_cond_wakeup_all(task_cond* cond)
{
	return pthread_cond_broadcast(cond);
}

static inline int task_cond_wait(task_cond* cond, cpl_mutex* mutex)
{
	cplt_lock* lock = (cplt_lock*)(*mutex);

	if(lock->type != CPL_MUTEX)
		return (-EINVAL);

	return pthread_cond_wait(cond, &lock->l_mutex);
}

static inline int task_cond_timedwait(
	task_cond* cond, 
	cpl_mutex* mutex, 
	const struct timespec* time
	)
{
	cplt_lock* lock = (cplt_lock*)(*mutex);

	if(lock->type != CPL_MUTEX)
		return (-EINVAL);

	return pthread_cond_timedwait(cond, &lock->l_mutex, time);
}

/*============== task conditional variable end =============*/

/*============== task attribute related start =============*/
/* in current implement, we only encapsulate LinuxPthread */
static inline int task_attr_init(task_attr* attr)
{
	return pthread_attr_init(attr);
}

static inline int task_attr_destroy(task_attr* attr)
{
	return pthread_attr_destroy(attr);
}

static inline int task_attr_setschedparam(
	task_attr* attr, 
	const struct sched_param* param
	)
{
	return pthread_attr_setschedparam(attr, param);
}

static inline int task_attr_getschedparam(
	const task_attr* attr, 
	struct sched_param* param
	)
{
	return pthread_attr_getschedparam(attr, param);
}

static inline int task_attr_setschedpolicy(task_attr* attr, int policy)
{
	return pthread_attr_setschedpolicy(attr, policy);
}

static inline int task_attr_getschedpolicy(const task_attr* attr, int* policy)
{
	return pthread_attr_getschedpolicy(attr, policy);
}

/* not support set task detach state */
static inline int task_attr_setdetachstate(task_attr* attr, int state)
{
	return -1;
//	return pthread_attr_setdetachstate(attr, state);
}

static inline int task_attr_getdetachstate(task_attr* attr, int* state)
{
	return pthread_attr_getdetachstate(attr, state);
}

static inline int task_attr_setinheritsched(task_attr * attr, int inherit)
{
	return pthread_attr_setinheritsched(attr, inherit);
}

static inline int task_attr_getinheritsched(
	const task_attr* attr,
	int* inherit
	)
{
	return pthread_attr_getinheritsched(attr, inherit);
}

static inline int task_attr_setscope(task_attr * attr, int scope)
{
	return pthread_attr_setscope(attr, scope);
}

static inline int task_attr_getscope(
	const task_attr * attr,
	int * scope
	)
{
	return pthread_attr_getscope(attr, scope);
}

static inline int task_getschedparam(int thread, int * policy, struct sched_param * param)
{
	return pthread_getschedparam((pthread_t)thread, policy, param);
}

static inline int task_setschedparam(int thread, int policy, const struct sched_param * param)
{
	return pthread_setschedparam((pthread_t)thread, policy, param);
}

#define task_exit_pre(func, args)  pthread_cleanup_push(func,args)

#define task_exit_pre_clean(excute) pthread_cleanup_pop(excute)

/*============== task attribute related end =============*/

#endif //end of _CPL_TASK_H_
