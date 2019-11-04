#ifndef _CPL_DEBUG_H_
#define _CPL_DEBUG_H_

#define CPL_CALLTRACE 		1
#define CPL_DEBUG_MSG		2
#define CPL_SIG_SAFE		3
#define CPL_LOCK_SIG		4
#define CPL_LOCK_EF		5
#define CPL_DEADLOCK_DETECT	6

#define CPLDM(bit) (1UL<<(bit-1))

#define CPL_DEB_VAL	0

#if CPL_DEB_VAL&(CPLDM(CPL_CALLTRACE))
#define CPL_D_CALLTRACE	1
#endif

#if CPL_DEB_VAL&(CPLDM(CPL_DEBUG_MSG))
#define CPL_D_DEBUG	1
#endif

#if CPL_DEB_VAL&(CPLDM(CPL_SIG_SAFE))
#define CPL_D_SIGSAFE	1
#endif

#if CPL_DEB_VAL&(CPLDM(CPL_LOCK_EF))
#define CPL_D_LOCKEF	1
#endif

#if CPL_DEB_VAL&(CPLDM(CPL_DEADLOCK_DETECT))
#define CPL_D_DEADLOCK	1
#endif

#undef CPLDM
#endif

