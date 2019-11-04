/*
 * Kedacom Hardware Abstract Level
 *
 * brd_touchscreen.h
 *
 * Copyright (C) 2013-2020, Kedacom, Inc.
 *
 * History:
 *   2015/10/30 - [wanghantao] Create
 *
 */

#ifndef _BRD_TOUCHSCREEN_H
#define _BRD_TOUCHSCREEN_H

#ifdef __cplusplus
extern "C" {
#endif

#include <drvlib_def.h>

#define INPUT_EVENT_SUPPORT         1
#define MAX_POING                   5
typedef struct 
{
	unsigned short au16_X[MAX_POING];       /*x coordinate */
	unsigned short au16_Y[MAX_POING];       /*y coordinate */
	unsigned int au8_Touch_Event[MAX_POING];/*touch event: 
						  0 -- down; 1-- contact; 2 -- contact */
	unsigned int au8_Finger_Id[MAX_POING];  /*touch ID */
	//u16 pressure;
	//unsigned int touch_point;   
} TSeventInfo;

/*TS*/
#define TS_CTL_DEV                      "/proc/driver/ft5x0x_ts" 
#ifdef INPUT_EVENT_SUPPORT
#define TS_HANDLE                       "/dev/event0"
#else
#define TS_HANDLE                       TS_CTL_DEV
#endif
#define TS_FW_SIZE_MAX          (32 * 1024)
#define TS_CMD_CALIBRATE        0x51
#define TS_CMD_READ_POINT       0x52
#define TS_CMD_SET_PARAM        0x53
#define TS_FW_UPGRADE           0x54
#define TS_GET_FW_VER           0x55
#define TS_GET_HW_ID            0x56

/*
 * Name     : BrdTSInit
 * Function : TouchScreen init: open device node;set calibrate param
 * Input    : @mode : 1--open ts,set calibrate param
 *                    0---close ts
 *            @CalibData--param array CalibData[7]
 * Output   :  NONE
 * Return   :  > 0:device operate handle : <= 0: error
 *                                              
 */
int BrdTSInit(int mode, int *CalibData);

/*
 * Name     : BrdTsFwUpgrad
 * Function : TouchScreen firmware upgrade
 * Input     :  @fwFilePath : firmware file path
 * Output   :  NONE
 * Return   :  0 : success, -1: error
 */
int BrdTsFwUpgrad(char *fwFilePath);

/*
 * Name     : BrdTSGetHardWareID
 * Function : Get TS hard ware ID
 * Input     :  none
 * Output   :  NONE
 * Return   :  0x0a:FT5316  0x55:FT5306  -1: error
 */
int BrdTSGetHardWareID(void);
/*
 * Name     : BrdGetTSEvent
 * Function : get TouchScreen event, this function will block
 * Input    : @event : ts data pointer 
 *            @fd: touch-screen file handle
 * Output   :  NONE
 * Return   :  0 : success, -1: error
 */
int BrdGetTSEvent(int fd, void *event);
#ifdef __cplusplus
}
#endif

#endif
