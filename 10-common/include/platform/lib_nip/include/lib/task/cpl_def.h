#ifndef _CPL_DEF_H_
#define _CPL_DEF_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <assert.h>

#include <cpl_debug.h>
/* include custom headers */
#ifdef I386
#undef I386
#endif

#ifdef PPC
#undef PPC
#endif

#ifdef BFIN
#undef BFIN
#endif


#define I386 1
#define PPC  2
#define BFIN 3

typedef unsigned char cplt_bool;
typedef unsigned char cpl_u8;

struct cpl_init {
	int 	all:1,
		task:1,
		sig:1,
		lock:1,
		reserve:28;
};

#define cpl_print	printf

#define cpl_memcpy 	memcpy
#define cpl_free(p)	free(p)

#define cpl_assert	assert

#ifdef likely
#undef likely
#endif

#ifdef unlikely
#undef unlikely
#endif

/* compiler optimize code */
#define likely(x) 	__builtin_expect((!!(x)),1)
#define unlikely(x) 	__builtin_expect((!!(x)),0)

#ifdef CPL_D_CALLTRACE

#define CPL_D_ENTER()	\
do { \
	cpl_print("-----------------------\n%s entrance:\n", __func__); \
}while(0)

#define CPL_D_PARAM(str...)	\
do { \
	cpl_print(str); \
}while(0)


#define CPL_D_EXIT()	\
do { \
	cpl_print("-----------------------\n%s exit success:\n", __func__); \
}while(0)

#define CPL_D_FAIL()	\
do { \
	cpl_print("-----------------------\n%s exit failed:\n", __func__); \
}while(0)

#else

#define CPL_D_ENTER()	do {}while(0)

#define CPL_D_PARAM(str...)	do {}while(0)


#define CPL_D_EXIT()	do {}while(0)

#define CPL_D_FAIL()  do {}while(0)

#endif

#define cpl_error(str...)	\
	do {	\
		cpl_print("###%s:%d\n", __func__, __LINE__); \
		cpl_print(str);	\
		perror(NULL); \
	}while(0)

#ifdef CPL_D_DEBUG
#define cpl_debug(str...)	\
	do {	\
		cpl_print("###%s:%d\n", __func__, __LINE__); \
		cpl_print(str);	\
	} while(0)
#else
#define cpl_debug(str...)
#endif

#define cpl_bug(str...) \
	do { \
		cpl_print("###BUG!:%s:%d\n", __func__, __LINE__); \
		cpl_error(str); \
		cpl_assert(0); \
	}while(0)

#define cpl_malloc malloc
#define cpl_malloc_init(len) \
	({ \
		void* ret; \
		ret = cpl_malloc(len); \
		cpl_assert(ret);\
		memset(ret, 0, len); \
		ret; \
	})

#endif //end of _CPL_DEF_H_
