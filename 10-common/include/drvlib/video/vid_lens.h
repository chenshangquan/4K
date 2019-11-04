/*
 * Kedacom Hardware Abstract Level
 *
 * vid_lens.h
 *
 * Copyright (C) 2013-2020, Kedacom, Inc.
 *
 * History:
 *   2013/09/22 - [xuliqin] Create
 *
 */

#ifndef __VID_LENS_H
#define __VID_LENS_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef USE_KLSP_DEFINES
/*
 * Lens identify defines
 * use u32 type variable
 *   D[31:24]: Motor driver chip
 *   D[23:16]: Lens  type
 *   D[ 7: 0]: index for each Lens obj
 */
#define LENS_NO_SHIFT            0
#define LENS_NO_MASK             0xff
#define LENS_NO(v)               (((v) >> LENS_NO_SHIFT) & LENS_NO_MASK)

#define LENS_TYPE_SHIFT          16
#define LENS_TYPE_MASK           0xff
#define LENS_TYPE(v)             (((v) >> LENS_TYPE_SHIFT) & LENS_TYPE_MASK)

#define LENS_TYPE_FIXED          0 /* fixed/manu zoom and focuse lens */
#define LENS_TYPE_KINO16X        1 /* kino(muxia) 16x lens */
#define LENS_TYPE_TAMRON         2 /* tamron lens */
#define LENS_TYPE_CANNON20X      3 /* cannon 20x lens */
#define LENS_TYPE_CANNON30X      4 /* cannon 30x lens */
#define LENS_TYPE_AFZ            5 /* af and zoom */

#define MOTOR_DRV_SHIFT          24
#define MOTOR_DRV_MASK           0xff
#define MOTOR_DRV(v)             (((v) >> MOTOR_DRV_SHIFT) & MOTOR_DRV_MASK)

#define MOTOR_DRV_NONE           0
#define MOTOR_DRV_AN41908        1
#define MOTOR_DRV_LV8044         2
#define MOTOR_DRV_PWM            3

#define LENS_ID(motor, type, no) \
        (((motor) << MOTOR_DRV_SHIFT) | \
         ((type)  << LENS_TYPE_SHIFT) | \
         ((no)    << LENS_NO_SHIFT))

/* predefined lens identify code */
#define LENS_ID_FIXED(n)              LENS_ID(MOTOR_DRV_NONE, \
                                              LENS_TYPE_FIXED, n)
#define LENS_ID_AN41908_KINO16X(n)    LENS_ID(MOTOR_DRV_AN41908, \
                                              LENS_TYPE_KINO16X, n)
#define LENS_ID_AN41908_TAMRON(n)     LENS_ID(MOTOR_DRV_AN41908, \
                                              LENS_TYPE_TAMRON,n)
#define LENS_ID_AN41908_CANNON20X(n)  LENS_ID(MOTOR_DRV_AN41908, \
                                              LENS_TYPE_CANNON20X,n)
#define LENS_ID_AN41908_CANNON30X(n)  LENS_ID(MOTOR_DRV_AN41908, \
                                              LENS_TYPE_CANNON30X,n)
#define LENS_ID_LV8044_AFZ(n)         LENS_ID(MOTOR_DRV_LV8044, \
                                              LENS_TYPE_AFZ,n)
#define LENS_ID_PWM_IRIS(n)           LENS_ID(MOTOR_DRV_PWM, \
                                              LENS_TYPE_FIXED,n)

#define LENS_MAX_NUM 1

/* lens capability mask defines */
#define LENS_CAB_IRCUT           0x00000001 /* support ircut set */
#define LENS_CAB_HEATER          0x00000002 /* support heater */
#define LENS_CAB_RAIN_CLR        0x00000004 /* support rain clear */
#define LENS_CAB_ZOOM            0x00000008 /* support zoom in/out control */
#define LENS_CAB_FOCUS           0x00000010 /* support focuse control */
#define LENS_CAB_APERTURE        0x00000020 /* support aperture control */
#define LENS_CAB_IRLED           0x00000040 /* support irled control */

/* the actions of rain clearer */
#define LENS_RAIN_CLR_STOP       0x00000000 /* idle */
#define LENS_RAIN_CLR_ONESHOT    0x00000001 /* clear once */
#define LENS_RAIN_CLR_CONTINUE   0x00000002 /* clear continue */

#else
/* refer to kernel/driver/klsp */
#include <video/lens/lens_drv.h>
#endif /* USE_KLSP_DEFINES */

typedef struct {
	u32 dwNo;           /* input: -1 = return led_registed_num;
	                       input: 0 ~ led_registed_num-1, return detail */

	u32 dwLensId;      /* see also: LENS_ID_AN41908_KINO16X */
	u32 dwCab;         /* capability mask, see also: LENS_CAB_IRCUT */

	u32 dwIrisClose;   /* iris full close value */
	u32 dwIrisOpen;    /* iris full open  value */
	u32 dwIrisStep;    /* iris adjust step value */

	u32 dwZoomOffset;  /* ZOOM_OFFSET, may be different every product */
	u32 dwFocusOffset; /* FOCUS_OFFSET, may be different every product */
} TLensInfo;

typedef struct {
	u32   dwLensId;     /* see also: LENS_ID_AN41908_KINO16X */
	u32   adwVal32[16];   /* params */
} TLensParams;

typedef struct {
	u32 dwId;
	u32 dwOnOff;   /* switch for heater 1:on 0:off */
	s32 dwTemper;  /* heater temperature, in 0.001 degree C */
} THeaterInfo;

typedef struct {
	u32 dwId;
	u32 dwOnOff;   /* switch for heater 1:on 0:off */
	s32 dwTimes;   /* rain brush action times */
} TRainBrushInfo;

/*
 * LENS COMMANDS
 */

enum eVidLensCmd {
	LENS_CTRL_GET_MOD_VER = 0,
	LENS_CTRL_QUERY = 1,

	LENS_CTRL_SET_IRCUT = 10,
	LENS_CTRL_SET_SHUTTER_SPEED,
	LENS_CTRL_INIT,
	LENS_CTRL_PARK,
	LENS_CTRL_ZOOM_STOP,
	LENS_CTRL_FOCUS_NEAR, /* 15 */
	LENS_CTRL_FOCUS_FAR,
	LENS_CTRL_ZOOM_IN,
	LENS_CTRL_ZOOM_OUT,
	LENS_CTRL_FOCUS_STOP,
	LENS_CTRL_SET_APERTURE, /* 20 */
	LENS_CTRL_SET_MECH_SHUTTER,
	LENS_CTRL_SET_ZOOM_PI,
	LENS_CTRL_SET_FOCUS_PI,
	LENS_CTRL_STANDBY,
	LENS_CTRL_IS_FOCUS_RUNNING, /* 25 */
	LENS_CTRL_IS_ZOOM_RUNNING,
	LENS_CTRL_SET_HEATER,
	LENS_CTRL_SET_RAIN_CLR,
	LENS_CTRL_SET_IRLED,
	LENS_CTRL_SET_MOTO_SPEED,
	LENS_CTRL_BACKFOCUS_NEAR,
	LENS_CTRL_BACKFOCUS_FAR,
	LENS_CTRL_SET_LENS_HW_ENABLE,

	LENS_CTRL_WRT_MOTOR_REG = 50,
	LENS_CTRL_RD_MOTOR_REG,
	LENS_CTRL_TRIG_VD_FZ,
	LENS_CTRL_TRIG_VD_IS,
	LENS_CTRL_GET_FSENSE_STATE,
	LENS_CTRL_GET_ZSENSE_STATE, /* 55 */
	LENS_CTRL_GET_PLS1_STATE,
	LENS_CTRL_GET_PLS2_STATE,
	LENS_CTRL_GET_VD_FZ,
	LENS_CTRL_SYNC_MOTOR_REG,
	LENS_CTRL_GET_BFSENSE_STATE,
};

/* add macro to distinguish day and night mode */
#define DAY_MODE    1
#define NIGHT_MODE  0

int VidLensCtrl(int nIndex, int nCmd, void *pArgs);

#ifdef __cplusplus
}
#endif

#endif
