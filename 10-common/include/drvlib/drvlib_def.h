/*
 * Kedacom Hardware Abstract Level
 *
 * drvlib_def.h
 *
 * Copyright (C) 2013-2020, Kedacom, Inc.
 *
 * History:
 *   2013/09/22 - [xuliqin] Create
 *
 */

#ifndef __DRVLIB_DEF_H
#define __DRVLIB_DEF_H

#ifdef __cplusplus
extern "C" {
#endif

#include <common/kdvtype.h>

/* ========================================================================== */
/* limits */
#define DRVLIB_STR_MAX_LEN (32)

#define DRVLIB_NAME_MAX_LEN (32)

#define DRVLIB_TTY_NAME_MAX_LEN (32)

/* ========================================================================== */
/*
 * Extern module definition
 */
#define EXT_MODULE_E1        0
#define EXT_MODULE_4E1       1
#define EXT_MODULE_V35DTE    2
#define EXT_MODULE_V35DCE    3
#define EXT_MODULE_BRIDGE    4
#define EXT_MODULE_2E1       5
#define EXT_MODULE_KDV8000B  6
#define EXT_MODULE_DSC       0xc
#define EXT_MODULE_MDSC      0xd
#define EXT_MODULE_HDSC      0xe
#define EXT_NO_MODULE        0xf

/* -------------------------------------------------------------------------- */

/* ========================================================================== */
/*
 * HWID definition
 */

#define UNKNOWN_BOARD          0xff
#define BRD_KDM2418            0x02
#define BRD_KDM2518            0x03
#define BRD_KDM2400P           0x10
#define BRD_KDM2464LS          0x22
#define BRD_KDM2110            0x23
#define BRD_KDM2422S           0x24
#define BRD_KDM2422LS          0x25
#define BRD_KDM2421S           0x26
#define BRD_KDM2421LS          0x27
#define BRD_KDM2110L           0x28
#define BRD_KDM2300            0x29
#define BRD_KDM2300P           0x2a
#define BRD_KDM2561            0x30
#define BRD_KDM2401            0x39
#define BRD_KDM2401ES          0x3a
#define BRD_KDM2424LS          0x3b
#define BRD_KDM2501            0x3c
#define BRD_KDM2401S           0x46
#define BRD_KDM2402            0x47
#define BRD_KDM2402S           0x48
#define BRD_KDM2401L           0x49
#define BRD_KDM2461            0x4a
#define BRD_KDM2461L           0x4b
#define BRD_KDM2401LS          0x4c
#define BRD_KDM2402L           0x4d
#define BRD_KDM2402LS          0x4e
#define BRD_KDM201C04          0x4f
#define BRD_KDM201C04L         0x50
#define BRD_KDM201D04          0x51
#define BRD_KDM2440            0x52
#define BRD_KDM2440P           0x53
#define BRD_KDM2462            0x54
#define BRD_KDM2462L           0x55
#define BRD_KDM2462S           0x56
#define BRD_KDM2462LS          0x57
#define BRD_KDM2461LS          0x58
#define BRD_KDM2461S           0x59
#define BRD_KDM2100            0x5a
#define BRD_KDM2100W           0x5b
#define BRD_KDM2100P           0x5c
#define BRD_KDM2820            0x20
#define BRD_KDM2820_4          0x2B
#define BRD_KDM2820_9          0x2C
#define BRD_KDM2820_16         0x2D
#define BRD_KDM2820E_9         0x2E
#define BRD_KDM2820E_16        0x2F
#define BRD_KDM2404S           0x3b
#define BRD_KDM200_MPU         0x3d
#define BRD_KDM200_APC         0x42
#define BRD_KDV8000BHD         0x6E
#define BRD_TS6610             0x70
#define BRD_TS5210             0x71
#define BRD_V5                 0x72
#define BRD_TS6610E            0x73
#define BRD_TS6210             0x74
#define BRD_TS6210E            0x80
#define BRD_TS3210             0xa0
#define BRD_TS5610             0x75
#define BRD_TS3610             0x76
#define BRD_TS7210             0x77
#define BRD_TS7610             0x78
#define BRD_KDV7810            0x7b
#define BRD_KDV7910            0x7c
#define BRD_KDV7820            0x7d
#define BRD_KDV7920            0x7e
#define BRD_KDVM26401          0xf0
#define BRD_HWID_KDM2421E      0x003E
#define BRD_HWID_KDM2210       0x0040
#define BRD_HWID_KDM2700       0x0041
#define BRD_HWID_DSL8000_MPU   0x0042
#define BRD_HWID_EBAP          0x0043
#define BRD_HWID_EVPU          0x0044
#define BRD_HWID_MAU           0x0045
#define BRD_HWID_KDM200_HDU    0x0046
#define BRD_HWID_KDM2310       0x004A
#define BRD_HWID_KDM2311       0x004B
#define BRD_HWID_KDV7620       0x001F
#define BRD_HWID_IPA100        0x0100
#define BRD_HWID_IPA101        0x0067
#define BRD_HWID_IPC201        0x006A
#define BRD_HWID_IPC300        0x0068
#define BRD_HWID_NVR2840       0x0107
#define BRD_HWID_NVR2860       0x0101
#define BRD_HWID_LC2150BN      0x01B9
#define BRD_HWID_LC2110BN      0x01BA
#define BRD_HWID_LC2150CN      0x01EE
#define BRD_HWID_LC2110CN      0x01EF

/* ========================================================================== */


/* ========================================================================== */
/*
 * PID definition
 */
#define BRD_PID_LC2150BN      0x114D
#define BRD_PID_LC2110BN      0x114E
#define BRD_PID_LC2150CN      0x11A7
#define BRD_PID_LC2110CN      0x11A8
/* ========================================================================== */

#ifdef __cplusplus
}
#endif

#endif
