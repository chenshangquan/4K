#ifndef __SYSDBG_H__
#define __SYSDBG_H__
#include <signal.h>

#define BACKTRACE_SIZE      50         /*max size of backtrace*/

#ifdef __cplusplus
extern "C"{
#endif

#define NF_NO_DEBUGTHREAD		0x1000		/*don't need the debugthread*/

/* 该宏已经废弃(20151010)
* 总是使用backtrace/unwind stack两种方式来回溯栈
*/
#define NF_USE_BACKTRACE		0X2000		/*we can use backtrace since glibc2.1*/

/* **********************说明*******************
 *参数:
 * 	symbol_file:是符号文件（总是忽略，传递NULL即可）
 *	crushdump_file:是程序异常的输出文件，为NULL 会输出到控制台
 *	dumpfile_size:生成的log文件大小上限，超出会清空后再写入
 *			默认1M，单位:KB
 *			传入<0表示使用默认值
 *	flags: 下面两种的任意组合或0
 *		NF_NO_DEBUGTHREAD 不启动调试线程，不使用call命令时可指定该选项 
 *	signum:信号id
 *	signals: 自定义需要跟踪的信号集合
 *	size: signals指向的信号的个数
 *
 *
 *示例:
 *	init_sysdbg(NULL, NULL,0);
 *	 __init_sysdbg(NULL, NULL,0, 0);
 *	 __init_sysdbg(NULL, NULL,2048,NF_NO_DEBUGTHREAD);
 *	 __init_sysdbg(NULL, "/usr/cursh.out", 0,NF_NO_DEBUGTHREAD);
 *	 __init_sysdbg2(SIGPIPE,  "/bin/ebt.sym", "/usr/cursh.out",0, 0);
 *
 *编译:
 * gcc main.c -funwind-tables -rdynamic -lsysdbg
 */

/*****************20140507接口修改说明****************
*1. 如果要限制log 文件大小，请使用新接口__init_sysdbg*()
*2. 使用旧接口init_sysdbg*()的程序若要限制log 大小，
*    请设置环境变量SYSDBG_LOG_LIMIT, 单位KB.
*    如:SYSDBG_LOG_LIMIT=50 表示限制log文件大小为50KB.
*3. 如果接口和环境变量中都指定，以环境变量为准.
*/

extern int __init_sysdbg(const char *symbol_file, 
		const char *crushdump_file,
		int dumpfile_size,
		int flags);

#define init_sysdbg(symbol_file, crushdump_file, flags) \
	__init_sysdbg(symbol_file, crushdump_file, 0, flags);

extern int __init_sysdbg2(int signum, 
		const char *symbol_file, 
		const char *crushdump_file,
		int dumpfile_size,
		int flags);

#define init_sysdbg2(signum, symbol_file, crushdump_file, flags) \
	__init_sysdbg2(signum, symbol_file, crushdump_file, 0, flags);

extern int __init_sysdbg3(int *signals, 
		int size, 
		const char *symbol_file, 
		const char *crushdump_file, 
		int dumpfile_size,
		int flags);

#define init_sysdbg3(signals, size, symbol_file, crushdump_file, flags) \
	__init_sysdbg3(signals, size, symbol_file, crushdump_file, 0, flags);


char *sysdbg_version();
#define SYSDBG__VERSION	sysdbg_version()

#ifdef __cplusplus
}
#endif

#endif

