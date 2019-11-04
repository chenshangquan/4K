/******************************************************************************
 *  Module name: kdglib_common
 *    File name: kdglib_common.h
 *      Related: 
 *     Function: Common definitions of kdglib.
 *       Author: xiezhigang
 *      Version: v1.0  Copyright(C) 2014 KDC, All rights reserved.
 * ----------------------------------------------------------------------------
 * Revisions:
 * Date        Version     Reviser     Description
 * 2014-07-31  v1.0        xiezhigang  created
 ******************************************************************************/
#ifndef KDGLIB_COMMON_H
#define KDGLIB_COMMON_H

#include <stddef.h>

#ifndef _MSC_VER
#include <stdint.h>
#else // _MSC_VER
typedef unsigned __int8     uint8_t;
typedef unsigned __int16    uint16_t;
#endif // _MSC_VER

#ifdef __cplusplus
#define BEGIN_KDGLIBAPI     extern "C" {
#define END_KDGLIBAPI       }
#else  // !__cplusplus
#define BEGIN_KDGLIBAPI
#define END_KDGLIBAPI
#endif // !__cplusplus

#define KDGLIBAPI           extern

#endif // KDGLIB_COMMON_H
