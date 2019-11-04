/*
 * Kedacom Hardware Abstract Level
 *
 * brd_eth.h
 *
 * Copyright (C) 2013-2020, Kedacom, Inc.
 *
 * History:
 *   2013/09/22 - [xuliqin] Create
 *
 */

#ifndef _BRD_ETH_H
#define _BRD_ETH_H

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*
 * Infomation & Peripherals definition
 */

#ifndef USE_KLSP_DEFINES

/*  eth type */
#define ETH_10M_HALF                    0
#define ETH_10M_FULL                    1
#define ETH_100M_HALF                   2
#define ETH_100M_FULL                   3
#define ETH_1000M_FULL                  4

#endif

typedef struct
{
	u32   dwNo;    /* Input: 0 ~ eth_num-1 */
	u32   dwType;     /* see also: ETH_10M_HALF */
	u8   abyMac[6];   /* MAC Address */
	char  achName[DRVLIB_NAME_MAX_LEN]; /* name */
} TEthInfo;


int BrdEthQueryInfo(TEthInfo *ptInfo);
int BrdEthGetLinkStat(u32 dwNo, int *pnLink);
int BrdEthGetNegStat(u32 dwNo, int *pnAutoNego, int *pnDuplex, int *pnSpeed);
int BrdEthSetNego(u32 dwNo, int nDuplex, int nSpeed);


#ifdef __cplusplus
}
#endif

#endif
