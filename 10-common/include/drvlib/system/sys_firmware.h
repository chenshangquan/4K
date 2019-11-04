/*
 * Kedacom Hardware Abstract Level
 *
 * sys_firmware.h
 *
 * Copyright (C) 2013-2020, Kedacom, Inc.
 *
 * History:
 *   2014/01/06 - [yuanzengxing] Create
 *
 */

#ifndef _SYS_FIRMWARE_H
#define _SYS_FIRMWARE_H

#include <drvlib_def.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef USE_KLSP_DEFINES
/*
 * Firmware identify defines for all boards
 * use u32 type variable
 *   D[31:16]: Firmware type DSP or MCU
 *   D[ 7: 0]: index for each Firmware type
 */
#define FIRMWARE_NO_SHIFT    0
#define FIRMWARE_NO_MASK     0xff
#define FIRMWARE_NO(v)       (((v) >> FIRMWARE_NO_SHIFT) & FIRMWARE_NO_MASK)

#define FIRMWARE_TYPE_SHIFT  16
#define FIRMWARE_TYPE_MASK   0xffff
#define FIRMWARE_TYPE(v)     (((v) >> FIRMWARE_TYPE_SHIFT) & FIRMWARE_TYPE_MASK)

#define FIRMWARE_ID(type, no) \
	(((type) << FIRMWARE_TYPE_SHIFT) | \
	 ((no)   << FIRMWARE_NO_SHIFT))

#define FIRMWARE_TYPE_DSP       0
#define FIRMWARE_TYPE_FPGA      1
#define FIRMWARE_TYPE_MCU       2

/* firmware object identify defines */
#define FIRMWARE_ID_DSP(n)      FIRMWARE_ID(FIRMWARE_TYPE_DSP, n)
#define FIRMWARE_ID_FPGA(n)     FIRMWARE_ID(FIRMWARE_TYPE_FPGA, n)
#define FIRMWARE_ID_MCU(n)      FIRMWARE_ID(FIRMWARE_TYPE_MCU, n)

/* firmware object cability defines */
#define FIRMWARE_CAB_ERASE      0x00000001 /* must erase before write */
#define FIRMWARE_CAB_BLOCK      0x00000002 /* fast block write supported */
#define FIRMWARE_CAB_READ       0x00000008 /* fast block read supported */

#endif /* USE_KLSP_DEFINES */

typedef struct {
	u32   no;          /* Input: 0 ~ firmware_registed_num-1;
	                              -1 = return firmware obj number */

	u32   id;          /* such as FIRMWARE_ID_C6657 */
	u32   cab;         /* cability, see alse: FIRMWARE_CAB_ERASE */
	u32   rom_size;    /* rom storage size, in Byte */
	u32   blk_size;    /* rom block size, in Byte */

	char  name[DRVLIB_NAME_MAX_LEN];
} TFirmWareInfo;

void SysFirmwareExit(void);
int SysFirmwareQuery(TFirmWareInfo *info);
int SysFirmwareOpen(u32 id);
int SysFirmwareClose(u32 id);
int SysFirmwareErase(u32 id, u32 addr, u32 len);
int SysFirmwareRead(u32 id, u32 addr, u8 *buf, u32 len);
int SysFirmwareWrite(u32 id, u32 addr, u8 *buf, u32 len);

#ifdef __cplusplus
}
#endif

#endif
