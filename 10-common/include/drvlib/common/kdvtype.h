/*****************************************************************************
   模块名      : KDV type
   文件名      : kdvtype.h
   相关文件    :
   文件实现功能: KDV宏定义
   作者        : 魏治兵
   版本        : V3.0  Copyright(C) 2001-2002 KDC, All rights reserved.
-----------------------------------------------------------------------------
   修改记录:
   日  期      版本        修改人      修改内容
   2004/02/17  3.0         魏治兵        创建
-----------------------------------------------------------------------------
  Modify Record:
  date: 2013/09/18
  version: 4.0 Copyright(C) 2001-2013 KDC, All rights reserved.
  author: Xu Liqin
  modify content:
    Refined Standard Integer types as: s64/s32/s16/s8/u64/u32/u16/u8

    Refer to ISO C99 (ANSI C):
      There are five standard signed integer types,
      designated as signed char, short int, int, long int, and long long int.
      Relations:
	long long >= long >= int >= short >= char

    Test on GNU C:
      i386:
        sizeof(long long): 64bit
        sizeof(long):      32bit
        sizeof(int):       32bit
        sizeof(short):     16bit
        sizeof(char):      8bit

      x86_64:
        sizeof(long long): 64bit
        sizeof(long):      64bit
        sizeof(int):       32bit
        sizeof(short):     16bit
        sizeof(char):      8bit

    So define types on GNU C(arm-none-linux-gnueabi) as below codes.

    Maybe they are difference on each C Compiler, if using other compiler,
    Should redefine types, use built-in macro to distinguish.

******************************************************************************/

#ifndef _KDV_TYPE_H_
#define _KDV_TYPE_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Type definition */
/*-----------------------------------------------------------------------------
系统公用文件，开发人员严禁修改
------------------------------------------------------------------------------*/

/* Defined as GNU C and VC */
#if defined(__GNUC__) || defined(_MSC_VER)
typedef signed int      s32, BOOL32;
typedef signed short    s16;
typedef signed char     s8;
typedef unsigned int    u32;
typedef unsigned short  u16;
typedef unsigned char   u8;
#endif

#ifdef _MSC_VER
typedef signed __int64   s64;
#elif defined(__GNUC__)
typedef signed long long s64;
#endif

#ifdef _MSC_VER
typedef unsigned __int64   u64;
#elif defined(__GNUC__)
typedef unsigned long long u64;
#endif

//#ifndef _MSC_VER
#ifdef __GNUC__
#ifndef LPSTR
#define LPSTR   char *
#endif
#ifndef LPCSTR
#define LPCSTR  const char *
#endif
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif /* _KDV_def_H_ */

/* end of file kdvdef.h */

