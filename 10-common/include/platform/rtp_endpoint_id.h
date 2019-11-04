#ifndef _KEDA_RTPEXT_H_
#define _KEDA_RTPEXT_H_

#include <stdio.h>
#include "kdvtype.h"

//define inline
#if defined(_MSC_VER)
#define WIN32_LEAN_AND_MEAN
#pragma warning(disable:4996)
#ifndef __INLINE__
#ifdef __cplusplus
#define __INLINE__	inline
#else
#define __INLINE__	__inline
#endif
#endif
#elif defined(__GNUC__) || defined(__MINGW32__)
#ifndef __INLINE__
#define __INLINE__ inline
#endif
#else
#ifndef __INLINE__
#define __INLINE__ inline
#endif
#endif

/*
 * 1.0版本的rtp endpoint id 定义为:
 *  63--62-----------------------------------14---12---10-----------0
 *  |ver|    rtp endpoint id(E164)             |DIR|rtcp|stream id  |
 *  -----------------------------------------------------------------
 */
#define DS_RTP_EPID_VER     1
typedef u64 dsRtpEndpointId;

/* 忽略比较的id, for source identify */
#define DS_RTP_ANY_ID       0x0
#define DS_RTP_INVALID_ID   0x0

/* for modifier action */
#define DS_RTP_REMOVE_ID    0x1
#define DS_RTP_UNTOUCH_ID   0x2
#define DS_RTP_REMOVE_EXT   0x3

#define DS_RTP_EPID_STREAM_LEN      10
#define DS_RTP_EPID_TYPE_LEN        2
#define DS_RTP_EPID_DIR_LEN         2
#define DS_RTP_EPID_ID_LEN          48
#define DS_RTP_EPID_VER_LEN         2

#define DS_RTP_EPID_STREAM_OFFSET   0
#define DS_RTP_EPID_TYPE_OFFSET   \
        (DS_RTP_EPID_STREAM_OFFSET + DS_RTP_EPID_STREAM_LEN)
#define DS_RTP_EPID_DIR_OFFSET  \
        (DS_RTP_EPID_TYPE_OFFSET + DS_RTP_EPID_TYPE_LEN)
#define DS_RTP_EPID_ID_OFFSET   \
        (DS_RTP_EPID_DIR_OFFSET + DS_RTP_EPID_DIR_LEN)
#define DS_RTP_EPID_VER_OFFSET  \
        (DS_RTP_EPID_ID_OFFSET + DS_RTP_EPID_ID_LEN)

/* 获取每段信息的掩码 */
#define DS_RTP_EPID_STREAM_MASK \
        (((((u64)0x01) << (DS_RTP_EPID_STREAM_LEN)) - 1) <<  \
            DS_RTP_EPID_STREAM_OFFSET)
#define DS_RTP_EPID_TYPE_MASK \
            (((((u64)0x01) << (DS_RTP_EPID_TYPE_LEN)) - 1) <<  \
                DS_RTP_EPID_TYPE_OFFSET)
#define DS_RTP_EPID_DIR_MASK    \
        (((((u64)0x01) << (DS_RTP_EPID_DIR_LEN)) - 1) <<  \
            DS_RTP_EPID_DIR_OFFSET)
#define DS_RTP_EPID_ID_MASK     \
        (((((u64)0x01) << (DS_RTP_EPID_ID_LEN)) - 1) <<  \
            DS_RTP_EPID_ID_OFFSET)
#define DS_RTP_EPID_VER_MASK    \
        (((((u64)0x01) << (DS_RTP_EPID_VER_LEN)) - 1) <<  \
            DS_RTP_EPID_VER_OFFSET)

/* 生成rtp endpoint id */
#define DS_GEN_RTP_EPID(e164, send, streamId)    \
        ((((u64)DS_RTP_EPID_VER << DS_RTP_EPID_VER_OFFSET) & (DS_RTP_EPID_VER_MASK)) |   \
        ((((u64)(e164)) << DS_RTP_EPID_ID_OFFSET) & (DS_RTP_EPID_ID_MASK)) |       \
        ((((u64)(send)) << DS_RTP_EPID_DIR_OFFSET) & (DS_RTP_EPID_DIR_MASK)) |   \
        (((streamId) << DS_RTP_EPID_STREAM_OFFSET) & (DS_RTP_EPID_STREAM_MASK)))

#define DS_GEN_RTCP_EPID(e164, send, streamId)    \
            ((((u64)DS_RTP_EPID_VER << DS_RTP_EPID_VER_OFFSET) & (DS_RTP_EPID_VER_MASK)) |   \
            ((((u64)(e164)) << DS_RTP_EPID_ID_OFFSET) & (DS_RTP_EPID_ID_MASK)) |       \
            ((((u64)(send)) << DS_RTP_EPID_DIR_OFFSET) & (DS_RTP_EPID_DIR_MASK)) |   \
            ((0x1 << DS_RTP_EPID_TYPE_OFFSET) & (DS_RTP_EPID_TYPE_MASK)) |   \
            (((streamId) << DS_RTP_EPID_STREAM_OFFSET) & (DS_RTP_EPID_STREAM_MASK)))

static __INLINE__ dsRtpEndpointId ds_gen_rtp_epid(
        const char* e164_str,
        BOOL32 send,
        u32 streamId)
{
    u64 e164 = 0;
    if (streamId > 0x1 << DS_RTP_EPID_STREAM_LEN)
        return DS_RTP_INVALID_ID;

    if (e164_str)
        sscanf(e164_str, "%llu", &e164);

    if (send)
        send = TRUE;

    return DS_GEN_RTP_EPID(e164, send, streamId);
}

static __INLINE__ dsRtpEndpointId ds_gen_rtcp_epid(
        const char* e164_str,
        BOOL32 send,
        u32 streamId)
{
    u64 e164 = 0;
    if (streamId > 0x1 << DS_RTP_EPID_STREAM_LEN)
        return DS_RTP_INVALID_ID;

    if (e164_str)
        sscanf(e164_str, "%llu", &e164);

    if (send)
        send = TRUE;

    return DS_GEN_RTCP_EPID(e164, send, streamId);
}

/* 从rtp endpoint id中获取version信息 */
#define DS_GET_RTP_VER(epid) \
        (((epid) & DS_RTP_EPID_VER_MASK) >> DS_RTP_EPID_VER_OFFSET)

/* 从rtp endpoint id中获取id(e164 for v1)信息 */
#define DS_GET_RTP_ID(epid) \
        (((epid) & DS_RTP_EPID_ID_MASK) >> DS_RTP_EPID_ID_OFFSET)

/* 从rtp endpoint id中收发方向信息 */
#define DS_GET_RTP_DIRECTION(epid) \
        (((epid) & DS_RTP_EPID_DIR_MASK) >> DS_RTP_EPID_DIR_OFFSET)

/* 从rtp endpoint id中获取流id信息 */
#define DS_GET_RTP_STREAMID(epid) \
        (((epid) & DS_RTP_EPID_STREAM_MASK) >> DS_RTP_EPID_STREAM_OFFSET)

#define DS_IS_RTCP_ID(epid) \
        (((epid) & DS_RTP_EPID_TYPE_MASK) != 0)

#endif //endof _KEDA_RTPEXT_H_
