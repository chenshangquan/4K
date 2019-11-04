/**************************************************************
*     Copyright (C) 2004-2005, KEDACOM
*
* 1.FILENAME    : cpl_lock.h
* 2.COMPONENT   : Cross Platfrom Libaray lock manager
* 3.AUTHOR      : Zeng Zhaoming (SH)
* 4.DATE        : 2005-9-27 9:04
* 5.DESCRIPTION : define cpl_lock struct and related
* 6.CHANGELOG	: init version designed by Zeng Zhaoming
***************************************************************/
#ifndef _CPL_LOCK_H_
#define _CPL_LOCK_H_

/* include system headers */
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <unistd.h>

/* include custom headers */
#include <cpl_list.h>

#ifndef __USE_UNIX98
# define PTHREAD_RWLOCK_INITIALIZER \
  { __LOCK_INITIALIZER, 0, NULL, NULL, NULL,	\
    PTHREAD_RWLOCK_DEFAULT_NP, PTHREAD_PROCESS_PRIVATE }

enum
{
  PTHREAD_RWLOCK_PREFER_READER_NP,
  PTHREAD_RWLOCK_PREFER_WRITER_NP,
  PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP,
  PTHREAD_RWLOCK_DEFAULT_NP = PTHREAD_RWLOCK_PREFER_WRITER_NP
};

/* Read-write locks.  */
typedef struct _pthread_rwlock_t
{
  struct _pthread_fastlock __rw_lock; /* Lock to guarantee mutual exclusion */
  int __rw_readers;                   /* Number of readers */
  _pthread_descr __rw_writer;         /* Identity of writer, or NULL if none */
  _pthread_descr __rw_read_waiting;   /* Threads waiting for reading */
  _pthread_descr __rw_write_waiting;  /* Threads waiting for writing */
  int __rw_kind;                      /* Reader/Writer preference selection */
  int __rw_pshared;                   /* Shared between processes or not */
} pthread_rwlock_t;

/* Attribute for read-write locks.  */
typedef struct
{
  int __lockkind;
  int __pshared;
} pthread_rwlockattr_t;

extern int pthread_rwlock_init (pthread_rwlock_t *, pthread_rwlockattr_t *);

extern int pthread_rwlock_destroy (pthread_rwlock_t *);

extern int pthread_rwlock_rdlock (pthread_rwlock_t *);

extern int pthread_rwlock_tryrdlock (pthread_rwlock_t *);

extern int pthread_rwlock_wrlock (pthread_rwlock_t *);

extern int pthread_rwlock_trywrlock (pthread_rwlock_t *);

extern int pthread_rwlock_unlock (pthread_rwlock_t *);

extern int pthread_rwlockattr_init (pthread_rwlockattr_t *__attr);

extern int pthread_rwlockattr_destroy (pthread_rwlockattr_t *__attr);

#endif


#define CPL_SEM		0
#define CPL_MUTEX	1
#define CPL_RWLOCK	2

#define cpl_sem	int
#define cpl_mutex int
#define cpl_rwlock int

#define LOCK_TNAME      16

#ifdef CPL_D_DEADLOCK
typedef struct {
	/* lock wait_list */
	pthread_mutex_t	wait_lock;
	cplt_list_head wait_list;
}deadlock_stat_t;
#endif

/* efficency status in list node */
#ifdef CPL_D_LOCKEF
#define tv_cp(dst, src) \
do { \
        (dst)->tv_sec = (src)->tv_sec; \
        (dst)->tv_usec = (src)->tv_usec; \
} while(0)

#define tv_sub(later, bef, count) \
do { \
	if((later)->tv_sec < (bef)->tv_sec || \
		(((later)->tv_sec == (bef)->tv_sec) && \
		((later)->tv_usec < (bef)->tv_usec))) \
		cpl_debug("time sub error\n"); \
	count += 1000000*((later)->tv_sec < (bef)->tv_sec); \
	count += (later)->tv_usec - (bef)->tv_usec; \
} while(0)

#define tv_cls(tv) \
do { \
	(tv)->tv_sec = (tv)->tv_usec = 0; \
} while(0)

typedef struct{
	struct timeval ts; //time stamp hold lock
	int tid; //task id
	char name[LOCK_TNAME]; //task name
	unsigned int count; //this task lock count
	unsigned long tm; //this task total hold_lock time
}lock_ef_t;
#endif


typedef struct cpl_lock {
	union{
		sem_t sem;
		pthread_mutex_t	mutex;
		pthread_rwlock_t rwlock;
	} lock;
	int type;
	int creator;
	int owner;
	int count;
	cplt_list_node* ln;
#ifdef CPL_D_DEADLOCK
	deadlock_stat_t dls;
#endif
#ifdef CPL_D_LOCKEF
	cplt_list_head ef;
#endif
} cplt_lock;


typedef struct {
	int		tid;
	cplt_list_node* n;
	cplt_list_head	h;
} locktask_node_t;


#define l_sem lock.sem
#define l_mutex lock.mutex
#define l_rwlock lock.rwlock

#include <cpl_internal.h>

#define semb_lock_blocksig(l, old) \
do { \
	if(old) \
		task_sig_blockall(old); \
	semb_lock(l); \
} while(0)

#define semb_trylock_blocksig(l, old) \
do { \
	int ret; \
	if(old) \
		task_sig_blockall(old); \
	if((ret = semb_trylock(l))) \
		task_sig_restore(old); \
} while(0)

#define semb_unlock_unblocksig(l, old) \
do { \
	semb_lock(l); \
	if (old) \
		task_sig_restore(old); \
} while(0)

#define task_mutex_lock_blocksig(l, old) \
do {\
	if(old) \
		task_sig_blockall(old); \
	task_mutex_lock(l); \
} while(0)

#define task_mutex_trylock_blocksig(l, old) \
do {\
	int ret; \
	if(old) \
		task_sig_blockall(old); \
	if ((ret = task_mutex_trylock(l))) \
		task_sig_restore(old); \
} while(0)

#define task_mutex_unlock_unblocksig(l, old) \
do { \
	task_mutex_unlock(l); \
	if(old) \
		task_sig_restore(old); \
} while(0)

#define rwlock_rdlock_blocksig(l, old) \
do { \
	if (old) \
		task_sig_blockall(old); \
	rwlock_rdlock(l); \
} while(0)

#define rwlock_tryrdlock_blocksig(l, old) \
do { \
	int ret; \
	if(old) \
		task_sig_blockall(old); \
	if ((ret= rwlock_tryrdlock(l))) \
		task_sig_restore(old); \
} while(0)

#define  rwlock_wrlock_blocksig(l, old) \
do { \
	if (old) \
		task_sig_blockall(old); \
	rwlock_wrlock(l); \
} while(0)

#define  rwlock_trywrlock_blocksig(l, old) \
do { \
	int ret; \
	if (old) \
		task_sig_blockall(old); \
	if ((ret = rwlock_trywrlock(l))) \
		task_sig_restore(old); \
} while(0)

#define rwlock_unlock_unblocksig(l, old) \
do { \
	rwlock_unlock(l); \
	task_sig_restore(old); \
} while(0)

#define safe_semb_lock
#define safe_semb_trylock
#define safe_semb_unlock

#define safe_mutex_lock
#define safe_mutex_trylock
#define safe_mutex_unlock

#define safe_rwlock_rdlock
#define safe_rwlcok_tryrdlock
#define safe_rwlock_wrlock
#define safe_rwlock_trywrlock
#endif //end of _CPL_LOCK_H_
