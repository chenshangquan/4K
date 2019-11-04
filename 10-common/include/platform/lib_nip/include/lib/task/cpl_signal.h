#ifndef _CPL_SIGNAL_H_
#define _CPL_SIGNAL_H_
#include <signal.h>

#include <cpl_list.h>

//maximum signal number
#define CPL_MAX_SIG	__SIGRTMAX
#define CPL_MIN_RTSIG	__SIGRTMIN
#define EXIT_SIG	CPL_MIN_RTSIG + 10
#define CPL_SIG_WORD	((CPL_MAX_SIG + sizeof(int) -1)/sizeof(int))
#define SIG_INT_LEN	32

struct cpl_task_signal {
	int mask[CPL_SIG_WORD];
	cplt_list_head	siglist;
};

#endif //end of _CPL_SIGNAL_H_
