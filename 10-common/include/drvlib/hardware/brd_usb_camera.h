/*
 * Kedacom Hardware Abstract Level
 *
 * brd_usb_camera.h
 *
 * Copyright (C) 2013-2020, Kedacom, Inc.
 *
 * History:
 *   2017/10/10 - [gulidong] Create
 *
 */

#ifndef _BRD_USB_CAMERA_H
#define _BRD_USB_CAMERA_H

#include <drvlib_def.h>

#ifdef __cplusplus
extern "C" {
#endif

unsigned int BrdUvcInit(void);
unsigned int BrdUvcDeinit(void);
unsigned char BrdUvcStatCheck(void);
unsigned char BrdUvcImagePut(char *img_data, unsigned int img_size);

#ifdef __cplusplus
}
#endif

#endif
