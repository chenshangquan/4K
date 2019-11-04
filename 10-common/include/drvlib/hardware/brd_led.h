/*
 * Kedacom Hardware Abstract Level
 *
 * brd_led.h
 *
 * Copyright (C) 2013-2020, Kedacom, Inc.
 *
 * History:
 *   2013/09/22 - [xuliqin] Create
 *
 */

#ifndef _BRD_LED_H
#define _BRD_LED_H

#ifdef __cplusplus
extern "C" {
#endif

#include <drvlib_def.h>

#ifndef USE_KLSP_DEFINES

/*
 * Led identify defines for all boards
 * use u32 type variable
 *   D[31:16]: Led type
 *   D[ 7: 0]: index for each Led type
 */
#define LED_NO_SHIFT            0
#define LED_NO_MASK             0xff
#define LED_NO(v)               (((v) >> LED_NO_SHIFT) & LED_NO_MASK)

#define LED_TYPE_SHIFT          16
#define LED_TYPE_MASK           0xffff
#define LED_TYPE(v)             (((v) >> LED_TYPE_SHIFT) & LED_TYPE_MASK)

#define LED_ID(type, no) \
        (((type) << LED_TYPE_SHIFT) | \
         ((no)   << LED_NO_SHIFT))

/* one and only led defines */
#define LED_ID_RUN              LED_ID(0, 0)
#define LED_ID_ALARM            LED_ID(0, 1)
#define LED_ID_LINK             LED_ID(0, 2)
#define LED_ID_CHASSIS_NORM     LED_ID(0, 4)
#define LED_ID_CHASSIS_NALM     LED_ID(0, 5)
#define LED_ID_CHASSIS_SALM     LED_ID(0, 6)
#define LED_ID_GREEN            LED_ID(0, 7)
#define LED_ID_ORANGE           LED_ID(0, 8)
#define LED_ID_RED              LED_ID(0, 9)
#define LED_ID_IR               LED_ID(0, 10)
#define LED_ID_ENCODER          LED_ID(0, 11)
#define LED_ID_DECODER          LED_ID(0, 12)
#define LED_ID_SDI              LED_ID(0, 13)
#define LED_ID_CDMA             LED_ID(0, 14)
#define LED_ID_WLAN             LED_ID(0, 15)
#define LED_ID_DISK             LED_ID(0, 16)
#define LED_ID_MPC              LED_ID(0, 17)

/* multi led defines */
#define LED_ID_ETH(n)           LED_ID(1, n)
#define LED_ID_E1(n)            LED_ID(2, n)
#define LED_ID_DSP(n)           LED_ID(3, n)
#define LED_ID_VIDEOIN(n)       LED_ID(4, n)
#define LED_ID_BATTER(n)        LED_ID(5, n)


/* Led state: D[31:0] = R[31:24] G[23:16] B[15:8] RSV[7:4] MODE[3:0] */
#define LED_COLOR_R(stat)       (((stat) >> 24) & 0xff)
#define LED_COLOR_G(stat)       (((stat) >> 16) & 0xff)
#define LED_COLOR_B(stat)       (((stat) >> 8) & 0xff)
#define LED_MODE(stat)          ((stat) & 0xf)

#define LED_MODE_OFF            0
#define LED_MODE_ON             1
#define LED_MODE_FLICKER_FAST   2
#define LED_MODE_FLICKER        3
#define LED_MODE_FLICKER_SLOW   4

#define LED_STAT(r, g, b, m)    ((((r) & 0xff) << 24) | (((g) & 0xff) << 16) | \
                                 (((b) & 0xff) <<  8) | ((m) & 0xf))


#endif /* USE_KLSP_DEFINES */

typedef struct
{
	u32   dwNo;          /* Input: 0 ~ led_registed_num-1 */
	u32   dwId;          /* see also: LED_ID_RUN */
	u32   dwCab;

	char achName[DRVLIB_NAME_MAX_LEN];
} TLedInfo;

typedef struct
{
	u32   dwId;          /* see also: LED_ID_RUN */
	u32   dwState;       /* see also: LED_STATE_OFF */
} TLedStatus;

int BrdLedQueryInfo(TLedInfo *ptInfo);
int BrdLedSetStatus(u32 dwId, u32 dwStatus);
int BrdLedGetStatus(u32 dwId, u32 *pdwStatus);

#ifdef __cplusplus
}
#endif

#endif
