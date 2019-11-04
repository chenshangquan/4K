/*
 * Kedacom Hardware Abstract Level
 *
 * brd_oled.h
 *
 * Copyright (C) 2013-2020, Kedacom, Inc.
 *
 * History:
 *   2017/01/05 - [gulidong] Create
 *
 */

#ifndef _BRD_OLED_H
#define _BRD_OLED_H

#include <drvlib_def.h>

#ifdef __cplusplus
extern "C" {
#endif

/* oled device */
#define OLED_DEV_ONE                (0)
#define OLED_DEV_TWO                (1)
#define OLED_DEV_THREE              (2)
#define OLED_DEV_FOUR               (2)
/* position for charactors shows */
#define OLED_ROW_ONE                (1<<0)
#define OLED_ROW_TWO                (1<<1)
#define OLED_ROW_THREE              (1<<2)
#define OLED_ROW_MID_ONE_TWO        (1<<8)
#define OLED_ROW_MID_TWO_THREE      (1<<9)
#define OLED_COLUMN_CENTER          (1<<16) /* default left, you can choose center by this flag */
#define OLED_ROW_OFF                (0)
#define OLED_ROW_ON                 (0xFF)

/* oled capacity */
#define OLED_CAP_CHAR               (1<<0)  /* this oled can show charactors */
#define OLED_CAP_GRAPH              (1<<1)  /* this oled can show pictures */
#define OLED_CAP_BOTH               (1<<2)  /* this oled can show charactors and pictures */

#define OLED_STATE_OFF              0
#define OLED_STATE_ON               1


typedef struct
{
    u32   No;               /* Input: 0 ~ oled_registed_num-1 */
    u32   Cab;              /* See : OLED_CAP_CHARACTOR */

    struct Char_info{
        u32 MaxRowNum;      /* oled can show max row num ,See */
        u32 MaxColumnChar;  /* oled can show max char num per line */
    }Chars;
    struct Graph_info{
        u32 GraphType;      /* oled can show high*weight type graph, from database */
    }Graph;

    char achName[DRVLIB_NAME_MAX_LEN]; /* device name, for user open */
}TOledInfo;

/*
 * 矩形框区域参数，由于控制器要求将屏按行划分多个page，每个page为8行，因此
 * 有些参数需要时8的整数倍
 */
typedef struct {
    u32 wDevId;     /* oled index */
    u16 wPosX;      /* 起始点X坐标，像素为单位 */
    u16 wPosY;      /* 起始点Y坐标，行为单位，必须是8的整数倍*/
    u16 wWidth;     /* 矩形框宽度，像素为单位 */
    u16 wHeight;    /* 矩形框高度，行为单位，必须是8的整数倍 */

    u8 *pbyFBuf;    /* 矩形框点阵数据buffer的指针，由驱动分配 */
    u32 dwSize;     /* 矩形框点阵数据字节数 */
} TOledRectInfo;

/**
 * BrdOledQueryInfo
 *
 * query oled info
 *
 * @param TOledInfo
 * @return 0/code num
 */
int BrdOledQueryInfo(TOledInfo *info);

/**
 * BrdOledSetStatus
 *
 * set Oled status
 *
 * @param
 *      id : oled num
 *      status : 0 / close 1 open
 * @return 0/code num
 */
int BrdOledSetStatus(u32 id, u32 status);

/**
 * BrdOledShowChars
 *
 * show string on Oled
 *
 * @param
 *      id  : oled num
 *      pos : position
 *      string : string to show
 * @return 0/code num
 */
int BrdOledShowChars(u32 id, u32 pos,char *string);
int BrdOledOnOff(u32 id, u8 on_off);
int BrdOledUpdateRect(u32 id, TOledRectInfo *pRect);
int BrdOledSetGraphicMode(u32 id, u8 mode, u8 time_intv);
int BrdOledSetContrast(u32 id, u8 contrast);

#ifdef __cplusplus
}
#endif

#endif
