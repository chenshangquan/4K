/*
 * Kedacom Hardware Abstract Level
 *
 * vid_ptz.h
 *
 * Copyright (C) 2013-2020, Kedacom, Inc.
 *
 * History:
 *   2015/04/28 - [gulidong] Create
 *
 */

#ifndef __VID_PTZ_H
#define __VID_PTZ_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef USE_KLSP_DEFINES

/*
 * Ptz identify defines
 * use u32 type variable
 *   D[23:16]: Ptz type
 *   D[ 7: 0]: index for each Ptz obj
 */
#define PTZ_NO_SHIFT            0
#define PTZ_NO_MASK             0xff
#define PTZ_NO(v)               (((v) >> PTZ_NO_SHIFT) & PTZ_NO_MASK)

#define PTZ_TYPE_SHIFT          16
#define PTZ_TYPE_MASK           0xff
#define PTZ_TYPE(v)             (((v) >> PTZ_TYPE_SHIFT) & PTZ_TYPE_MASK)

#define PTZ_TYPE_IPC425_E230_N  0  /* ptz:ipc425_e230_n */

#define PTZ_ID(type, no) \
         (((type)  << PTZ_TYPE_SHIFT) | \
         ((no)    << PTZ_NO_SHIFT))

/* predefined ptz identify code */
#define PTZ_ID_IPC425_E230_N(n)  PTZ_ID(PTZ_TYPE_IPC425_E230_N, n)

/*
 * Ptz identify defines
 */
#define PTZ_MAX_NUM             1
/* ptz capability mask defines */
#define PTZ_CAB_FAN             0x00000001 /* support fan */
#define PTZ_CAB_HEATER          0x00000002 /* support heater */
#define PTZ_CAB_PWM             0x00000004 /* support pwm */
#define PTZ_CAB_LASER           0x00000008 /* support laser */
#define PTZ_CAB_RST             0x00000010 /* support reset */
#define PTZ_CAB_IRLED           0x00000020 /* support irled control */

#else
/* refer to kernel/driver/klsp */
#include <video/ptz/ptz_drv.h>
#endif /* USE_KLSP_DEFINES */

/* fan info */
typedef struct
{
	u32   dwId;         /* fan device index */
	u32   dwOnOff;      /* fan control switch/0:off,1:on */
} TPtzFan;

/* heater info */
typedef struct {
	u32 dwId;           /* heater device index */
	u32 dwOnOff;        /* switch for heater/0:off,1:on */
	s32 dwTemper;       /* heater temperature, in 0.001 degree C */
} TPtzHeater;

/* pwm info */
typedef struct {
	u32   dwCh;         /* pwm channel(logic) index(0¡¢1¡¢2...) */
	u32   dwFreq;       /* pwm work frequency */
	u32   dwDuty;       /* pwm duty rate/scope:0~255 */
} TPtzPwm;

/* laser info */
typedef struct {
	u32   dwId;         /* laser device index */
	u32   dwOnOff;      /* laser switch/0:off,1:on */
} TPtzLaser;

/* reset info */
typedef struct {
	u32   dwId;         /* reset device index */
	u32   dwRst;        /* device reset control/0:reset,1:normal */
} TPtzRst;

/* infrared info */
typedef struct {
	u32   dwId;         /* irled index */
	u32   dwOnOff;      /* ir led switch/0:off,1:on */
} TPtzIrLed;

/* rotation info */
typedef struct {
	u32   dwId;         /* motor index */
	u32   dwDir;        /* 0/1 two direction */
	u32   dwSpeed;      /* motor run speed */
} TPtzRotation;

/* move info*/
typedef struct{
	u32   dwId;         /* motor index */
	u32   dwDir;        /* 0/1 two direction */
	u32   dwStepNum;    /* motor move step number */
}TPtzMove;

/* go to postion by beeline info*/
typedef struct{
	u32   dwId;         /* motor index */
	u32   dwPos;        /* absolute position */
}TPtzGo2PosBeeline;

/* go to postion by direction info*/
typedef struct{
	u32   dwId;         /* motor index */
	u32   dwPos;        /* absolute position */
	u32   dwDir;        /* move direction  */
}TPtzGo2PosDir;

/* reset position info*/
typedef struct{
	u32   dwId;         /* motor index */
}TPtzResetPos;

/* soft reset info*/
typedef struct{
	u32   dwId;         /* motor index */
}TPtzSoftReset;

/* soft stop info*/
typedef struct{
	u32   dwId;         /* motor index */
}TPtzSoftStop;

/* hard stop info*/
typedef struct{
	u32   dwId;         /* motor index */
}TPtzHardStop;

/* get status info*/
typedef struct{
	u32   dwId;         /* motor index */
	u8    dwStatus;     /* get busy status */
}TPtzGetStatus;

/* ptz param*/
typedef struct{
	u32   dwId;         /* motor index */
	u32   reg;          /* reg addr */
	u32   val;          /* reg val */
}TPtzParam;

/* ptz get photosens */
typedef struct{
	u32 dwId;           /* photosens index */
	u32 val;            /* photosens value */
}TPtzPhotoSens;

/* ptz get thermal */
typedef struct{
	u32 dwId;           /* thermal index */
	u32 val;            /* thermal valude */
}TPtzThermal;

typedef struct {
	u32 dwNo;           /* input: -1 = return ptz_registed_num;	          
	                     * input: 0 ~ ptz_registed_num-1, return detail
	                     */
	u32 dwPtzId;      
	u32 dwCab;          /* capability mask, see also: PTZ_CAB_HEATER */
} TPtzInfo;

/*
 * ptz commands
 */
enum eVidPtzCmd { 
	PTZ_CTRL_QUERY       = 0,/* TPtzInfo */
	PTZ_CTRL_SET_FAN,        /* TPtzFan */
	PTZ_CTRL_SET_HEATER,     /* TPtzHeater */
	PTZ_CTRL_SET_LASER,      /* TPtzLaser */
	PTZ_CTRL_SET_PWM,        /* TPtzPwm */
	PTZ_CTRL_SET_RST,        /* TPtzRst */
	PTZ_CTRL_SET_IRLED,      /* TPtzIrLed */
	PTZ_CTRL_SET_ROTATION,   /* TPtzRotation */
	PTZ_CTRL_SET_MOVE,       /* TPtzMove */
	PTZ_CTRL_SET_GO2POS_BEELINE, /* TPtzGo2PosBeeline */
	PTZ_CTRL_SET_GO2POS_DIR, /* TPtzGo2PosDir */
	PTZ_CTRL_SET_RESET_POS,  /* TPtzResetPos */
	PTZ_CTRL_SET_SOFT_RESET, /* TPtzSoftReset */
	PTZ_CTRL_SET_SOFT_STOP,  /* TPtzSoftStop */
	PTZ_CTRL_SET_HARD_STOP,  /* TPtzHardStop */
	PTZ_CTRL_GET_STATUS,     /* TPtzGetStatus*/
	PTZ_CTRL_SET_PARAM,      /* TPtzSetParam */
	PTZ_CTRL_GET_PARAM,      /* TPtzGetParam */
	PTZ_CTRL_GET_PHOTOSENS,  /* TPtzPhotoSens */
	PTZ_CTRL_GET_THERMAL,    /* TPtzThermal */
};


/* function declared */
int PtzCtrl(int idx, int cmd, void *args);

#ifdef __cplusplus
}
#endif

#endif
