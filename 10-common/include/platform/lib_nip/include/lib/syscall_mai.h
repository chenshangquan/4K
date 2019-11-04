/*
 * =====================================================================================
 * 
 *        Filename:  syscall_mai.h
 * 
 *     Description:  mai_syscall header file 
 * 
 *         Version:  1.0
 *         Created:  10/17/2005 04:56:41 PM UTC
 *        Revision:  none
 *        Compiler:  gcc
 * 
 *          Author:  Liang Yu Lin (Mr)
 *         Company:  kedacom.com
 *           Email:  liangyulin@kedacom.com   urlion@sina.com
 * 
 * =====================================================================================
 */
#ifndef SYSCALL_MAI_HEADER_
#define SYSCALL_MAI_HEADER_
#include <config.h>
#include <linux/unistd.h>

/* type value from kernel*/
/* if you change type value in kernel, change this also*/
#define MAI_CONF_MIN 0
#define MAI_CONF_INTERFACE 1
#define MAI_CONF_INTERFACE_DEL 2
#define MAI_CONF_SYMBOL 3
#define MAI_CONF_RUN 4
#define MAI_CONF_MISC 5
#define MAI_CONF_DSW 6
#define MAI_CONF_NAT 7
#define MAI_CONF_QOS 8
#define MAI_CONF_MAX 8

/* for use in Nip*/
#if ARCH == ppc
#define __NR_mai_syscall                272
#elif ARCH == ARM
#define __NR_mai_syscall                (__NR_SYSCALL_BASE+281)
#else
#define __NR_mai_syscall                272
#endif

int errno;

static _syscall5(long,mai_syscall,int ,type, char*,in_buf,char*,out_buf,int,in_len,int,out_len)




#endif
