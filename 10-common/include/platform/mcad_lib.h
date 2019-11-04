/*****************************************************************************
模块名      : MCAD
文件名      : mcad_lib.h
相关文件    : 
文件实现功能: mcad lib head file
作者        : Xinxing Zhou
版本        : V1.0  Copyright(C) 2013 KEDACOM, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      	版本        修改人      		修改内容
11/14/2013  	01.0        Xinxing Zhou		Creat	
******************************************************************************/
#ifndef __MCAD_LIB_H__
#define __MCAD_LIB_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include "kdvtype.h"

typedef int TMcadObj;

typedef void (*TMcadFunc)(void *h, u32 dwContext, u64 qwOpt);

#define MCAD_RC_ID							0x9c

#define MCAD_UCAST_CHAN						(1 << 0)
#define MCAD_MCAST_CHAN						(1 << 1)
#define MCAD_UCAST_FAKE						(1 << 2)
#define MCAD_MCAST_FAKE						(1 << 3)

#define MCA_POOL_MCG0						0
#define MCA_POOL_MCG1						1
#define MCA_POOL_MCG2						2
#define MCA_POOL_MCG3						3

#define SRC_NONFLUSH_DST_NONCOHERENT		0
#define SRC_FLUSH_DST_NONCOHERENT			1
#define SRC_NONFLUSH_DST_COHERENT			2
#define SRC_FLUSH_DST_COHERENT				3

enum EDMA_EVENT_Q {
	EVENTQ_0 = 0,
	EVENTQ_1 = 1,
	EVENTQ_2 = 2,
	EVENTQ_3 = 3,
	EVENTQ_DEFAULT = -1
};

#define STATUS_MMAP_NONCACHED				(1 << 0)
#define STATUS_MMAP_CACHED					(1 << 1)

#define MCAD_LOG_PRINT						0
#define MCAD_LOG_SYS						1
#define MCAD_LOG_ALL						2
#define MCAD_LOG_SHUT						3

s32 McadDeviceIdGet(u16 *pwId);

s32 McadDeviceSlotGet(u8 *bySlot);

s32 McadDevicePortGet(u8 *byPort);

s32 McadReserveMemGet(u64 *pqwPhys, u32 *pdwLen);

s32 McadReserveMemSet(u64 qwPhys, u32 dwLen);

s32 McadReserveMemAlloc(u64 *qwPhys, u32 dwLen);

void McadReserveMemFree(u64 qwPhys);

s32 McadMemSet(u64 qwPhys, u32 dwLen);

s32 McadConnect(void);

s32 McadDisconnect(u16 wId);

void *McadMmap64(u64 qwPhys, u32 dwLen, u8 byFlag);

void McadUnmap(void *pdwVirt, u32 dwLen);

void *McadChanCreate(u16 wRxId[], u64 qwOpt[], u32 dwRxNum, 
		u32 dwChanLen, u16 wCast, u16 wMcg, u16 wChanno);

s32 McadChanDestroy(void *pchHandle);

s32 McadChanAdd(void *pchHandle, u16 wRxId[], u64 qwOpt[], u32 dwRxNum);

s32 McadChanDel(void *pchHandle, u16 wRxId[], u32 dwRxNum);

void *McadChanDeclare(u16 wRxId[], u32 dwRxNum, u16 wChanno);

s32 McadChanUndeclare(void *pchHandle);

void *McadChanReCreate(void *pchHandle);

u16 McadChannoGet(void *pchHandle);

int McadChanStateGet(void *pchHandle, u16 wRxId);

s32 McadEmptyPacketGet(void *pchHandle, u32 dwLen, u32 *pdwVirt, u64 *pqwPhys);

s32 McadPacketSend(void *handle, u32 dwSeqNo);

s32 McadFullPacketGet(void *handle, u32 *pdwVirt, u64 *pqwPhys, u32 *dwLen);

s32 McadPacketReceive(void *handle, s32 dwSeqNo);

s32 McadCallbackSet(TMcadFunc func, u32 context);

void McadLogPthreadCreate(void);

s32 McadLogChanCreate(void);

s32 McadLogRemove(void);

s32 McadEpPrintf(const char *fmt, ...);

void McadLogOpt(u8 opt);

s32 McadCacheFlush(u32 dwVirt, u32 dwLen, u8 byCacheMode);

s32 McadCacheClean(u32 dwVirt, u32 dwLen, u8 byCacheMode);

s32 McadCacheInvalidate(u32 dwVirt, u32 dwLen, u8 byCacheMode);

s32 McadEdmaXfer(u64 qwTxPhys, u64 qwRxPhys, u32 dwLen, int swEventQ);

u32 McadEdma2DFill(u64 qwPixPhys, u64 qwDstPhys, u32 dwWidth, u32 dwHeight, 
		u32 dwPitch, u32 dwBpp, int swEventQ);

u32 McadEdma2DMove(u64 qwPixPhys, u64 qwDstPhys, u32 dwWidth, u32 dwHeight, 
		u32 dwPitch, u32 dwBpp);
		
void uart_printf(const char *fmt, ...);

#ifdef __cplusplus 
}
#endif /* __cplusplus */

#endif
