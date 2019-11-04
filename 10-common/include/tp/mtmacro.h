/*******************************************************************************
 *  模块名   : MT                                                              *
 *  文件名   : mtmacro.h                                                       *
 *  相关文件 :                                                                 *
 *  实现功能 : 终端常用宏定义                                                  *
 *  作者     : 张明义                                                          *
 *  版本     : V3.0  Copyright(c) 1997-2005 KDC, All rights reserved.          *
 *                                                                             *
 *    =======================================================================  *
 *  修改记录:                                                                  *
 *    日  期      版本        修改人      修改内容                             *
 *  2005/8/6  x.0         张明义      创建          *
 *                                                                             *
 *******************************************************************************/

#ifndef _MT_MACRO_H_
#define _MT_MACRO_H_

#include "cnconst.h"
#include <string.h>


#ifdef _MSC_VER
#define inline _inline
#endif

#define MT_OK 0
#define MT_ERR 0xFF
#define MT_MAX_VERSTR_LEN	128

#define IN_PARAM
#define OUT_PARAM
	
#define  _OffSetOf(s,m)   (size_t)&(((s *)0)->m)
#define  _CountOf(array)  (sizeof(array)/sizeof(array[0]))
#define  _SizeOfMember( s ,m ) (size_t)(sizeof((((s *)0)->m)))

#define HEXCAR(  val ) ( ( (u8)(val) >= 0xA ) ? ('A'+ (u8)(val)-0xA) : ('0' + (u8)(val) )  )

// 指针判断
#define MT_ASSERT( p ) if ( p == NULL ) { ::OspPrintf( TRUE, FALSE, "[SYSTEM]Invalid Pointer(%s:(%d))!\n", __FILE__, __LINE__ ); return; }
#define MT_ASSERT_RET( p, ret ) if ( p == NULL ) { ::OspPrintf( TRUE, FALSE, "[SYSTEM]Invalid Pointer(%s:(%d))!\n", __FILE__, __LINE__ ); return ret; }

// 释放内存
#define MT_SAFE_DELETE( p ) if ( p != NULL ) { delete p; p = NULL; }
#define MT_SAFE_DELETE_ARRAY( p ) if ( p != NULL ) { delete []p; p = NULL; }


#define IPFORMAT     "%d.%d.%d.%d"
#define u32ToIP( ip )   (u8)(ntohl(ip)>>24),\
                        (u8)(ntohl(ip)>>16),\
                        (u8)(ntohl(ip)>>8), \
                        (u8)ntohl(ip) 
//判断是否为组播地址
#define IS_MCADDR( ip ) ( (ntohl(ip) &0xE0000000) == 0xE0000000 )

#define SEAL_ARRAY( array ,val) (array[sizeof(array)-1]=val)

//安全复制字符串，旨在防止目标数组溢出。
//dst: 目标字符数组地址
//src: 源字符串指针
#define SAFE_STRCPY( dst, src)\
{\
	strncpy(dst, src, sizeof(dst));\
	dst[sizeof(dst)-1] = '\0';\
}

//////////////////////////////////////////////////////////////////////////


#ifdef _LINUX_

#ifndef min
#define min(a,b) ((a)>(b)?(b):(a))
#endif
#ifndef max
#define max(a,b) ((a)>(b)?(a):(b))
#endif

#endif

#ifdef _LINUX_
#define mtRegCommand( fun ) OspRegCommand (#fun, (void*) fun, "")
#else
#define mtRegCommand( fun ) 
#endif

#ifdef _LINUX_
#define tpRegCommand( fun ) OspRegCommand (#fun, (void*) fun, "")
#else
#define tpRegCommand( fun ) 
#endif

#ifndef ABS
#define ABS(x) ((x <0) ? -x: x )
#endif



#define BOOL_DESCRIPTION( val )  ( (val) ? "TRUE" : "FALSE" )

//#ifdef _LINUX_
//	#ifndef _LINUX_CONFIG_DEBUG_
//	#define _LINUX_CONFIG_DEBUG_
//	#endif
// #else
	#ifdef _LINUX_CONFIG_DEBUG_
	#undef _LINUX_CONFIG_DEBUG_
	#endif
// #endif


#define CHECK_POINTER( p )  \
{                  \
	if (p == NULL) \
	{              \
		tpError("NULL Pointer, in %s,%d \n", __FILE__, __LINE__); \
		return MT_ERR; \
	}\
}

#define VOID_CHECK_POINTER( p )  \
{                  \
	if (p == NULL) \
	{              \
		tpError("NULL Pointer, in %s,%d \n", __FILE__, __LINE__); \
		return; \
	}\
}

#ifdef _LINUX_
#define _MT_STRICMP( str1, str2 ) strcasecmp( str1, str2 )
#else
#define _MT_STRICMP( str1, str2 ) stricmp( str1, str2 )
#endif

#define BOOL_DESCRIPTION( val )  ( (val) ? "TRUE" : "FALSE" )

// --------------- 高清图像参数配置相关宏 --------------- 

#endif//!_MT_MACRO_H_

