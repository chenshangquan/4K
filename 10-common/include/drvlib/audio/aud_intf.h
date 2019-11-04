/*
 * Audio I/O Config (Codec and Path Route)
 *
 * aud_intf.h
 *
 * Copyright (C) 2013-2020, Kedacom, Inc.
 *
 * History:
 *   2013/09/22 - [xuliqin] Create
 *
 */

#ifndef __AUD_INTF_H
#define __AUD_INTF_H

#ifdef __cplusplus
extern "C" {
#endif

#include <drvlib_def.h>

#ifndef USE_KLSP_DEFINES

/*
 * audio interface defines
 * use u32 type variable
 *     D[31:24]: flag
 *     D[23: 0]: different for each flag
 *       flag = AUDIF_FLAG_PHY
 *         |- D[23:16]: physical interface type
 *         |- D[ 7: 0]: physical interface index for each interface type
 *       flag = AUDIF_FLAG_ASP(audio serial port)
 *         |- D[23:16]: DSP index of board
 *         |- D[15: 8]: ASP index of DSP
 *         |- D[ 7: 0]: Serial(i2s) index of ASP
 */

/* flag defines */
#define AUDIF_FLAG_SHIFT        24
#define AUDIF_FLAG_MASK         0xff
#define AUDIF_FLAG(v)           (((v) >> AUDIF_FLAG_SHIFT) & AUDIF_FLAG_MASK)

#define AUDIF_FLAG_PHY          0x0 /* physical audio interface */
#define AUDIF_FLAG_ASP          0x1 /* audio serial port of CPU */
#define AUDIF_FLAG_HDMI_EMB     0x2 /* hdmi audio port embeded in CPU */

/* physical interface type defines */
#define AUDIF_TYPE_SHIFT        16
#define AUDIF_TYPE_MASK         0xff
#define AUDIF_TYPE(v)           (((v) >> AUDIF_TYPE_SHIFT) & AUDIF_TYPE_MASK)

#define AUDIF_TYPE_DEF          0x00 /* default, used for board only one intf */
#define AUDIF_TYPE_HDMI         0x01
#define AUDIF_TYPE_RCA          0x02
#define AUDIF_TYPE_CANON        0x03
#define AUDIF_TYPE_DMIC         0x04
#define AUDIF_TYPE_FXO          0x05
#define AUDIF_TYPE_SPEAKER      0x06
#define AUDIF_TYPE_SDI          0x07
#define AUDIF_TYPE_JACK_2mm5    0x08
#define AUDIF_TYPE_JACK_3mm5    0x09
#define AUDIF_TYPE_JACK_6mm5    0x0a
#define AUDIF_TYPE_BLUETOOTH    0x0b
#define AUDIF_TYPE_WLA          0x0c
#define AUDIF_TYPE_HDBASET      0x0d
#define AUDIF_TYPE_RF      	0x0e

/* physical interface index defines */
#define AUDIF_NO_SHIFT          0
#define AUDIF_NO_MASK           0xff
#define AUDIF_NO(v)             (((v) >> AUDIF_NO_SHIFT) & AUDIF_NO_MASK)


/* physical interface defines */
#define AUDIF_PHY(type, no)           ((AUDIF_FLAG_PHY << AUDIF_FLAG_SHIFT) | \
                                       ((type) << AUDIF_TYPE_SHIFT) | \
                                       ((no)   << AUDIF_NO_SHIFT))

#define AUDIF_NONE                    0
#define AUDIF_HDMI(n)                 AUDIF_PHY(AUDIF_TYPE_HDMI,      n)
#define AUDIF_RCA(n)                  AUDIF_PHY(AUDIF_TYPE_RCA,       n)
#define AUDIF_CANON(n)                AUDIF_PHY(AUDIF_TYPE_CANON,     n)
#define AUDIF_DMIC(n)                 AUDIF_PHY(AUDIF_TYPE_DMIC,      n)
#define AUDIF_FXO(n)                  AUDIF_PHY(AUDIF_TYPE_FXO,       n)
#define AUDIF_SPEAKER(n)              AUDIF_PHY(AUDIF_TYPE_SPEAKER,   n)
#define AUDIF_SDI(n)                  AUDIF_PHY(AUDIF_TYPE_SDI,       n)
#define AUDIF_JACK_2mm5(n)            AUDIF_PHY(AUDIF_TYPE_JACK_2mm5, n)
#define AUDIF_JACK_3mm5(n)            AUDIF_PHY(AUDIF_TYPE_JACK_3mm5, n)
#define AUDIF_JACK_6mm5(n)            AUDIF_PHY(AUDIF_TYPE_JACK_6mm5, n)
#define AUDIF_BLUETOOTH(n)            AUDIF_PHY(AUDIF_TYPE_BLUETOOTH, n)
#define AUDIF_WLA(n)                  AUDIF_PHY(AUDIF_TYPE_WLA,       n)
#define AUDIF_HDBASET(n)              AUDIF_PHY(AUDIF_TYPE_HDBASET,   n)
#define AUDIF_RF(n)                   AUDIF_PHY(AUDIF_TYPE_RF,        n)

/* CPU ASP interface defines */
#define AUDIF_CPUx_ASPi_Sn(x, i, n)   ((AUDIF_FLAG_ASP << AUDIF_FLAG_SHIFT) | \
                                       ((x&0xff)<<16)    | \
                                       ((i&0xff)<<8)     | \
                                       ((n&0xff)<<0))

/* CPU Embeded Hdmi audio interface defines */
#define AUDIF_CPUx_EMB_HDMIn(x, n)   ((AUDIF_FLAG_HDMI_EMB<<AUDIF_FLAG_SHIFT) |\
                                       ((x&0xff)<<16)    | \
                                       ((n&0xff)<<0))

/* chnl_msk defines */
#define AUDIF_CHNL_LEFT         0x00000001
#define AUDIF_CHNL_RIGHT        0x00000002
#define AUDIF_CHNL_STEREO       0x00000003 /* AUDIF_CHNL_LEFT | RIGHT */

/* interface capability mask defines */
#define AUDIF_CAB_MICPLUS       0x00000001 /* ext MIC Plus Volume adjustable */

/*
 * Digital Audio Interface Formats.
 * mask by MSND_DAIFMT_FORMAT_MASK
 * Describes the physical PCM data formating and clocking. Add new formats
 * to the end.
 */
#define AUDIF_DAIFMT_I2S        0 /* I2S mode */
#define AUDIF_DAIFMT_RIGHT_J    1 /* Right Justified mode */
#define AUDIF_DAIFMT_LEFT_J     2 /* Left Justified mode */
#define AUDIF_DAIFMT_DSP_A      3 /* L data MSB after FRM LRC */
#define AUDIF_DAIFMT_DSP_B      4 /* L data MSB during FRM LRC */
#define AUDIF_DAIFMT_AC97       5 /* AC97 */
#define AUDIF_DAIFMT_PDM        6 /* Pulse density modulation */

/*
 * audio PCM ID defines
 * use u32 type variable
 *     D[31:16]:
 *     D[15: 8]: PCM driver type
 *     D[ 7: 0]: PCM driver device index
 */

/* PCM driver type defines */
#define AUDPCM_DRV_TYPE_SHIFT   8
#define AUDPCM_DRV_TYPE_MASK    0xff
#define AUDPCM_DRV_TYPE(v)      (((v) >> AUDPCM_DRV_TYPE_SHIFT) & \
                                 AUDPCM_DRV_TYPE_MASK)

#define AUDPCM_DRV_ALSA         1 /* use alsa lib to operate */
#define AUDPCM_DRV_MSND         2 /* use msnd lib to operate */

/* PCM driver device index defines */
#define AUDPCM_NO_SHIFT         0
#define AUDPCM_NO_MASK          0xff
#define AUDPCM_NO(v)            (((v) >> AUDPCM_NO_SHIFT) & AUDPCM_NO_MASK)

/* PCM driver device identify code defines */
#define AUDPCM_ID(t, n)         (((t) << AUDPCM_DRV_TYPE_SHIFT) | \
                                 ((n) << AUDPCM_NO_SHIFT))

/* sample rate capability mask defines */
#define AUDPCM_RATE_5512        (1<< 0)    /* 5512Hz */
#define AUDPCM_RATE_8000        (1<< 1)    /* 8000Hz */
#define AUDPCM_RATE_11025       (1<< 2)    /* 11025Hz */
#define AUDPCM_RATE_16000       (1<< 3)    /* 16000Hz */
#define AUDPCM_RATE_22050       (1<< 4)    /* 22050Hz */
#define AUDPCM_RATE_32000       (1<< 5)    /* 32000Hz */
#define AUDPCM_RATE_44100       (1<< 6)    /* 44100Hz */
#define AUDPCM_RATE_48000       (1<< 7)    /* 48000Hz */
#define AUDPCM_RATE_64000       (1<< 8)    /* 64000Hz */
#define AUDPCM_RATE_88200       (1<< 9)    /* 88200Hz */
#define AUDPCM_RATE_96000       (1<<10)    /* 96000Hz */
#define AUDPCM_RATE_176400      (1<<11)    /* 176400Hz */
#define AUDPCM_RATE_192000      (1<<12)    /* 192000Hz */

#define AUDPCM_RATE_8000_44100  (AUDPCM_RATE_8000  | AUDPCM_RATE_11025 | \
                                 AUDPCM_RATE_16000 | AUDPCM_RATE_22050 | \
                                 AUDPCM_RATE_32000 | AUDPCM_RATE_44100)
#define AUDPCM_RATE_8000_48000  (AUDPCM_RATE_8000_44100|AUDPCM_RATE_48000)
#define AUDPCM_RATE_8000_96000  (AUDPCM_RATE_8000_48000|AUDPCM_RATE_64000|\
                                 AUDPCM_RATE_88200     |AUDPCM_RATE_96000)
#define AUDPCM_RATE_8000_192000 (AUDPCM_RATE_8000_96000|AUDPCM_RATE_176400|\
                                 AUDPCM_RATE_192000)

/* sample bit capability mask defines */
#define AUDPCM_BIT_S8           (1 << 0) /* signed 8 bits */
#define AUDPCM_BIT_S16          (1 << 1) /* signed 16 bits */
#define AUDPCM_BIT_S24          (1 << 2) /* signed 24 bits */
#define AUDPCM_BIT_S32          (1 << 3) /* signed 32 bits */

#define AUDPCM_BIT_U8           (1 << 8) /* unsigned signed 8 bits */
#define AUDPCM_BIT_U16          (1 << 9) /* unsigned signed 16 bits */
#define AUDPCM_BIT_U24          (1 <<10) /* unsigned signed 24 bits */
#define AUDPCM_BIT_U32          (1 <<11) /* unsigned signed 32 bits */

#endif /* USE_KLSP_DEFINES */


/*
 * audio interface info
 * path mapping example:
 * ----------------------------------------------------------------------
 *  dwLinkPcmId|     dwLinkAudIf    |  codec info        | dwIntf
 * ----------------------------------------------------------------------
 *  AUDPCM_ID  | AUDIF_CPUx_ASPi_Sn |  codec  channel    | interface
 * ----------------------------------------------------------------------
 *    0x100 <-   0 <- 0 <---- 0 <--- 3104[0] <--- stereo<- AUDIF_JACK_3mm5(0)
 *
 *    0x200 <-   1 <- 0 <-|<- 0 <--- 3104[1] <-|- left  <- AUDIF_CANON(0)
 *                        |                    |- right <- AUDIF_CANON(1)
 *                        |<- 1 <--- 3104[2] <--- stereo<- AUDIF_RCA(0)
 *
 *    0x201 <-   1 <- 1 <-|<- 3 <--- 3104[3] <-|- left  <- AUDIF_CANON(2)
 *                        |                    |- right <- AUDIF_CANON(1)
 *                        |<- 4 <--- 7604[0] <--- stereo<- AUDIF_HDMI(0)
 */
typedef struct
{
	u32 dwIntf;       /* for query number: return registed interface number;
	                     for detail: return interface ID: AUDIF_RCA(n)... */

	/* Bit[31:0] -> audio channel[31:0]
	   for stereo: 0x1 = left chnl; 0x2 = right chnl;
	               0x3 = left&right chanl */
	u32 dwChnlMsk;    /* see also: AUDIF_CHNL_STEREO */

	u32 dwLinkAudIf;  /* see also: AUDIF_CPUx_ASPi_Sn(x, i, n) */
	u32 dwLinkPcmId;  /* for cap/play pcm open, etc: AUDPCM_ID(t, n) */
	u32 dwCabIntf;    /* capability mask, see also: AUDIF_CAB_MICPLUS */
	u32 dwCabRate;    /* see also: AUDPCM_RATE_8000_48000 */
	u32 dwCabBit;     /* see also: AUDPCM_BIT_S16 */
} TAudIfInfo;

/* audio standard param */
typedef struct
{
	u32 dwSampleRate;      /* in Hz, 0=shutdown; 8000,32000,48000,96000 */
	u32 dwSampleBits;      /* width: 16/20/24/32 */
	u32 dwChnlNum;         /* channel number: 1/2/3(2.1)/6(5.1) */
} TAudStd;

/* audio hardware config */
typedef struct
{
	u32 dwMclkFreq;        /* freq of mclk */
	TAudStd std;   /* audio standard param */
}TAudHwCfg;

/* cc8530 rf chip info */
typedef struct {
	u32 dwDeviceID;		/* Device ID */
	u32 dwManfID;		/* Manufacturer ID */
	u32 dwProdID;		/* Product/family ID */ 	
} TRFChipinfo;

#define NWM_SCAN_MAX_NETWORK	8

/* cc8530 rf network */
typedef struct {
	u32 dwNetNum;
	u32 dwDevID[NWM_SCAN_MAX_NETWORK];
} TRFNetwork;

#define MAX_DATAGRAM_SIZE	32	/* bytes */

/* cc8530 rf datagram */
typedef struct {
	u32 dwDevID;
	u32 dwDataNum;
	u8  abyData[MAX_DATAGRAM_SIZE];
} TRFDataGram;

/* AudInApiCtrl&AudOutApiCtrl nCmd Macro defines */
enum eAudIfCmd {
	AUDIF_QUERY = 1,       /* pArgs = (TAudIfInfo *) */
	AUDIF_SEL_INTF,        /* pArgs = (u32 *); src: AUDIF_JACK_3mm5(0).. */
	AUDIF_SET_MIC_48V,     /* pArgs = (u32 *); on=1 off=0 */
	AUDIF_GET_AUD_INTF_STATE,
	AUDIF_SET_STD,         /* pArgs = (TAudioStd *) */
	AUDIF_GET_STD,         /* pArgs = (TAudioStd *) */

	AUDIF_SET_MICPLUS_VOL, /* pArgs = (u32 *); in percent: 0~100% */
	AUDIF_GET_MICPLUS_VOL, /* pArgs = (u32 *); in percent: 0~100% */

	AUDIF_SET_VOL,         /* pArgs = (u32 *); in percent: 0~100% */
	AUDIF_SET_LEFT_VOL,    /* pArgs = (u32 *); in percent: 0~100% */
	AUDIF_SET_RIGHT_VOL,   /* pArgs = (u32 *); in percent: 0~100% */

	AUDIF_GET_VOL,         /* pArgs = (u32 *); in percent: 0~100% */
	AUDIF_GET_LEFT_VOL,    /* pArgs = (u32 *); in percent: 0~100% */
	AUDIF_GET_RIGHT_VOL,   /* pArgs = (u32 *); in percent: 0~100% */

	AUDIF_GET_PLUG_STATE,  /* pArgs = (u32 *); 0 nothing plugin*/

	AUDIF_RF_GET_DEVICE_INFO,	/* pArgs = (TRFChipinfo *) */
	AUDIF_RF_ENABLE_CONTROL,	/* pArgs = (u32 *); enable=1 disable=0*/
	AUDIF_RF_SCAN,			/* pArgs = (TRFNetwork *) */
	AUDIF_RF_JOIN,			/* pArgs = (u32 *); device id */
	AUDIF_RF_TX_DATA,		/* pArgs = (TRFDataGram *) */
	AUDIF_RF_RX_DATA,		/* pArgs = (TRFDataGram *) */
	AUDIF_RF_GET_STATUS,		/* pArgs = (TRFNetwork *) */
	AUDIF_RF_GET_RSSI,		/* pArgs = (u32 *); 0 to ~0dbm */
	AUDIF_SET_HW_CFG,		/* pArgs = (u32 *); 0 to ~0dbm */
};


/* APIs */

/*
 * for AUDIF_QUERY:
 *   dwIntf = -1: return registed interface number by TAudIfInfo.dwIntf
 *   dwIntf = 0 ~ TAudIfInfo.dwIntf-1: return interface detail info
 * for the other command:
 *   dwIntf = TAudIfInfo.dwIntf: config specifically interface, AUDIF_RCA(n)...
 */
int AudInApiCtrl(u32 dwIntf, int nCmd, void *pArgs);
int AudOutApiCtrl(u32 dwIntf, int nCmd, void *pArgs);

#ifdef __cplusplus
}
#endif

#endif /* end __AUD_INTF_H */
