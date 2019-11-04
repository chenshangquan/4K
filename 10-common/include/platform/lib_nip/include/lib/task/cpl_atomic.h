#ifndef _CPL_ATOMIC_H_
#define _CPL_ATOMIC_H_
#include <lib/task/cpl_internal.h>

typedef struct {int counter;} cplt_atomic;
#define cpl_atomic_read(v)		((v)->counter)
#define cpl_atomic_set(v, i)	(((v)->counter) = i)

#if ARCH==PPC
static inline void cpl_atomic_inc(cplt_atomic *v)
{
	int t;

	__asm__ __volatile__(
"1:	lwarx	%0,0,%2		# atomic_inc\n\
	addic	%0,%0,1\n"
"	stwcx.	%0,0,%2 \n\
	bne-	1b"
	: "=&r" (t), "=m" (v->counter)
	: "r" (&v->counter), "m" (v->counter)
	: "cc");
}

static inline void cpl_atomic_dec(cplt_atomic *v)
{
	int t;

	__asm__ __volatile__(
"1:	lwarx	%0,0,%2		# atomic_dec\n\
	addic	%0,%0,-1\n"
"	stwcx.	%0,0,%2\n\
	bne-	1b"
	: "=&r" (t), "=m" (v->counter)
	: "r" (&v->counter), "m" (v->counter)
	: "cc");
}
#elif ARCH==BFIN
static inline void cpl_atomic_inc(volatile cplt_atomic *v)
{
	int __temp = 0;
	__asm__ __volatile__(
		"cli R3;\n\t"
		"%0 = %1;\n\t"
		"%0 += 1;\n\t"
		"%1 = %0;\n\t"
		"sti R3;\n\t"
		: "=d" (__temp), "=m" (v->counter)
		: "m" (v->counter), "0" (__temp)
		: "R3");
}

static inline void cpl_atomic_dec(volatile cplt_atomic *v)
{ 
	int __temp = 0;
	__asm__ __volatile__(
		"cli R3;\n\t"
		"%0 = %1;\n\t"
		"%0 += -1;\n\t"
		"%1 = %0;\n\t"
		"sti R3;\n\t"
		: "=d" (__temp), "=m" (v->counter)
		: "m" (v->counter), "0" (__temp)
		: "R3");
}
#elif ARCH==I386
static inline void cpl_atomic_inc(cplt_atomic *v)
{
	__asm__ __volatile__(
		"incl %0"
		:"=m" (v->counter)
		:"m" (v->counter));
}

static inline void cpl_atomic_dec(cplt_atomic *v)
{
	__asm__ __volatile__(
		"decl %0"
		:"=m" (v->counter)
		:"m" (v->counter));
}

#else
#error not support atomic_t yet!
#endif

#endif //end of _CPL_ATOMIC_H_
