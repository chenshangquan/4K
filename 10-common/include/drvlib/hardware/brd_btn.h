/*
 * Kedacom Hardware Abstract Level
 *
 * brd_btn.h
 *
 * Copyright (C) 2013-2020, Kedacom, Inc.
 *
 * History:
 *   2013/09/22 - [xuliqin] Create
 *
 */

#ifndef _BRD_BTN_H
#define _BRD_BTN_H

#include <drvlib_def.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef USE_KLSP_DEFINES

/*
 * Button identify defines for all boards
 * use u32 type variable
 *   D[31:16]: Button type
 *   D[ 7: 0]: index for each Button type
 */
#define BUTTON_NO_SHIFT          0
#define BUTTON_NO_MASK           0xff
#define BUTTON_NO(v)             (((v) >> BUTTON_NO_SHIFT) & BUTTON_NO_MASK)

#define BUTTON_TYPE_SHIFT        16
#define BUTTON_TYPE_MASK         0xffff
#define BUTTON_TYPE(v)           (((v) >> BUTTON_TYPE_SHIFT) & BUTTON_TYPE_MASK)

#define BUTTON_ID(type, no) \
        (((type) << BUTTON_TYPE_SHIFT) | \
         ((no)   << BUTTON_NO_SHIFT))
#define BUTTON_TYPE_DIAL         0x04

/* one and only button defines */
#define BUTTON_ID_RST            BUTTON_ID(0, 0)
#define BUTTON_ID_AFMOD          BUTTON_ID(0, 1)
#define BUTTON_ID_WPS            BUTTON_ID(0, 2)
#define BUTTON_ID_SHOTENABLE     BUTTON_ID(0, 3)
#define BUTTON_ID_STARTBURN      BUTTON_ID(0, 4)
#define BUTTON_ID_REPLAY         BUTTON_ID(0, 5)
#define BUTTON_ID_STOPBURN       BUTTON_ID(0, 6)
#define BUTTON_ID_DIAL(n)        BUTTON_ID(BUTTON_TYPE_DIAL, n)
/* Button state */
#define BUTTON_STATE_OFF           0
#define BUTTON_STATE_ON            1

#endif /* USE_KLSP_DEFINES */

typedef struct
{
        u32   dwNo;       /* Input: 0 ~ button_registed_num-1 */

        u32   dwId;          /* see also: BUTTON_ID_RST */

        char   achName[DRVLIB_NAME_MAX_LEN];
} TButtonInfo;

typedef struct
{
        u32   dwId;          /* see also: BUTTON_ID_RST */
        u32   dwState;       /* see also: BUTTON_STATE_OFF */
} TButtonStatus;

int BrdButtonQueryInfo(TButtonInfo *tInfo);
int BrdButtonGetStatus(u32 dwId, u32 *pdwStatus);

#ifdef __cplusplus
}
#endif

#endif
