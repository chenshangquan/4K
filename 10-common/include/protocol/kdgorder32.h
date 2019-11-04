/******************************************************************************
 *  Module name: kdgorder32
 *    File name: kdgorder32.h
 *      Related: 
 *     Function: check byte order of cpu, and related operations.
 *       Author: xiezhigang
 *      Version: v1.0  Copyright(C) 2014 KDC, All rights reserved.
 * ----------------------------------------------------------------------------
 * Revisions:
 * Date        Version     Reviser     Description
 * 2014-07-31  v1.0        xiezhigang  created
 ******************************************************************************/
#ifndef KDGORDER32_H
#define KDGORDER32_H

enum
{
    KDG_LITTLE_ENDIAN  =  0x03020100ul,
    KDG_BIG_ENDIAN     =  0x00010203ul,
    KDG_PDP_ENDIAN     =  0x01000302ul
};

static const union
{
    unsigned char bytes[4];
    unsigned int  value;
} kdg_o32_host_order = { { 0, 1, 2, 3 } };

#define KDG_HOST_ORDER (kdg_o32_host_order.value)

#define KDG_IS_LITTLE_ENDIAN  (KDG_HOST_ORDER == KDG_LITTLE_ENDIAN)
#define KDG_IS_BIG_ENDIAN     (KDG_HOST_ORDER == KDG_BIG_ENDIAN)

#endif // KDGORDER32_H
