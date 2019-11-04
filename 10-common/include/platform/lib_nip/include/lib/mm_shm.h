/*
**  mm.h -- Shared Memory library API header
*/
#ifndef _MM_H_
#define _MM_H_

#include <g_module.h>
#ifdef MOD_MEMORY_LIB
#ifdef __cplusplus
extern "C" {
#endif
/*
**  ____ Public Part (I) of the API ________________________
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

typedef enum {
    MM_LOCK_RD, 
    MM_LOCK_RW
} mm_lock_mode;

/*
**  ____ Private Part of the API ___________________________
*/
#if defined(MM_PRIVATE)

#include "lib/mm_config.h"

#include <errno.h>
#include <limits.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#ifdef HAVE_SYS_PARAM_H
#include <sys/param.h>
#endif

#include <unistd.h>

#if !defined(FALSE)
#define FALSE 0
#endif
#if !defined(TRUE)
#define TRUE !FALSE
#endif
#if !defined(NULL)
#define NULL (void *)0
#endif
#if !defined(NUL)
#define NUL '\0'
#endif
#if !defined(min_of)
#define min_of(a,b) ((a) < (b) ? (a) : (b))
#endif
#if !defined(max_of)
#define max_of(a,b) ((a) > (b) ? (a) : (b))
#endif

#define ERR(type,str)   mm_lib_error_set(type,str)
#define FAIL(type,str)  { ERR(type,str); goto cus; }
#define BEGIN_FAILURE   cus:
#define END_FAILURE

#if defined(MM_SHMT_IPCSHM) || defined(MM_SEMT_IPCSEM)
#include <sys/ipc.h>
#endif

#if defined(MM_SHMT_IPCSHM)
#include <sys/shm.h>
#if !defined(SHM_R)
#define SHM_R 0400
#endif
#if !defined(SHM_W)
#define SHM_W 0200
#endif
#endif

#if defined(MM_SEMT_IPCSEM)
#include <sys/sem.h>
#ifndef HAVE_UNION_SEMUN
union semun {
    int val;
    struct semid_ds *buf;
    u_short *array;
};
#endif
#endif

#define MM_ALLOC_MINSIZE         (1024*8)
#define MM_CORE_FILEMODE         (S_IRUSR|S_IWUSR)
#define MM_CORE_DEFAULT_PAGESIZE (1024*8)
#define MM_CORE_DEFAULT_FILE     "/tmp/mm.core.%d"  /* %d is PID */

#define MM_ERR_ALLOC    1
#define MM_ERR_CORE     2
#define MM_ERR_SYSTEM   4

/*
 * Define a union with types which are likely to have the longest
 * *relevant* CPU-specific memory word alignment restrictions...
 */
union mem_word {
    void  *mw_vp;
    void (*mw_fp)(void);
    char  *mw_cp;
    long   mw_l;
    double mw_d;
};
typedef union mem_word mem_word;
#define SIZEOF_mem_word (sizeof(mem_word))

/*
 * Define the structure used for memory chunks
 */
union mem_chunk_mc_u {
    struct mem_chunk *mc_next; /* really used when it's free         */
    mem_word          mc_base; /* virtually used when it's allocated */
};
struct mem_chunk {
    size_t mc_size;      /* physical size   */
    size_t mc_usize;     /* user known size */
    union mem_chunk_mc_u mc_u;
};
typedef struct mem_chunk mem_chunk;
#define SIZEOF_mem_chunk (sizeof(mem_chunk)-sizeof(union mem_chunk_mc_u))

/*
 * Define the structure describing a memory pool
 */
struct mem_pool {
   size_t     mp_size;
   size_t     mp_offset;
   mem_chunk  mp_freechunks;
   mem_word   mp_base;
};
typedef struct mem_pool mem_pool;
#define SIZEOF_mem_pool (sizeof(mem_pool)-SIZEOF_mem_word)

/*
 * Define the structure describing a shared memory core area
 * (the actual contents depends on the shared memory and
 * semaphore/mutex type and is stripped down to a minimum
 * required)
 */
struct mem_core {
   size_t       mc_size;
   size_t       mc_usize;
   pid_t        mc_pid;
#if defined(MM_SHMT_IPCSHM)
   int          mc_fdmem;
#endif

  int  mc_fdsem;

#if defined(MM_SEMT_IPCSEM)
   int          mc_fdsem_rd;
   int          mc_readers;
   mm_lock_mode mc_lockmode;
#endif

   mem_word     mc_base;
};
typedef struct mem_core mem_core;
#define SIZEOF_mem_core (sizeof(mem_core)-SIZEOF_mem_word)

#endif /* MM_PRIVATE */

/*
**  ____ Public Part (II) of the API _______________________
*/

#if defined(MM_PRIVATE)
typedef mem_pool MM;
#else
typedef void MM;
#endif

/* Global Malloc-Replacement API */
int     MM_create(size_t, const char *);
void    MM_destroy(void);
int     MM_lock(mm_lock_mode);
int     MM_unlock(void);
void   *MM_malloc(size_t);
void    MM_free(void *);
char   *MM_error(void);

/* Standard Malloc-Style API */
MM     *mm_create(size_t, const char *);
void    mm_destroy(MM *);
int     mm_lock(MM *, mm_lock_mode);
int     mm_unlock(MM *);
void   *mm_malloc(MM *, size_t);
void    mm_free(MM *, void *);
size_t  mm_sizeof(MM *, const void *);
size_t  mm_maxsize(void);
char   *mm_error(void);

/* Low-Level Shared Memory API */
void   *mm_core_create(size_t, const char *);
void    mm_core_delete(void *);
int     mm_core_lock(const void *, mm_lock_mode);
int     mm_core_unlock(const void *);
size_t  mm_core_maxsegsize(void);
size_t  mm_core_align2page(size_t);
size_t  mm_core_align2word(size_t);

/* Internal Library API */
void    mm_lib_error_set(unsigned int, const char *);
char   *mm_lib_error_get(void);

#ifdef __cplusplus
}
#endif

#endif /* MOD_MEMORY_LIB */
#endif /* _MM_H_ */

