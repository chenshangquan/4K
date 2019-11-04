/*****************************************************************************
   模块名      : PCDV
   文件名      : pcdvcomm.h
   相关文件    : 
   文件实现功能: PCDV 内部结构定义
   作者        : 
   版本        : V4.0  Copyright(C) 2004-2007 KDC, All rights reserved.
-----------------------------------------------------------------------------
   修改记录:
   日  期      版本        修改人      修改内容
   2006/12/31  4.0         顾振华      创建
******************************************************************************/

#ifndef _PCDVCOMM_H_
#define _PCDVCOMM_H_

#include "osp.h"

//#define SOFT_CODEC

#include "pcdualvideoevent.h"
#include "mttype.h"
#include "mtstruct.h"
#include "codecevent.h"
#include "callevent.h"
#include "ummessagestruct.h"

#define PCDV_VER            (const char*)"pcdv40.40.01.04.070621 R4"

const u16 RTP_LOCALSNAP_PORT  = 40200;
const u16 wMtListenPort = 60000;

// 错误码
#define  PCDV_RET_OK                (u16)0
#define  PCDV_RET_OSPFAILED         (u16)1001   // OSP 失败
#define  PCDV_RET_NETWORKFAILED     (u16)1002   // 网络通信错误
#define  PCDV_RET_BUSY              (u16)1003   // 应用忙
#define  PCDV_RET_AUTHFAIL          (u16)1004   // 用户认证失败
#define  PCDV_RET_DUPLOGIN          (u16)1005   // 已有用户登录
#define  PCDV_RET_INCOMPVER         (u16)1006   // 版本不兼容
#define  PCDV_RET_NOPERMIT          (u16)1007   // 没有权限
#define  PCDV_RET_ENCODEFAIL        (u16)1008   // 开始桌面捕捉失败
#define  PCDV_RET_RESNONSTANDARD    (u16)1009   // 桌面分辨率不支持
#define  PCDV_RET_RES_DIFF_HIGH     (u16)1010   // 终端和pc的分辨率不一值(本机分辨率高了)
#define  PCDV_RET_RES_DIFF_LOW      (u16)1011   // 终端和pc的分辨率不一值(本机分辨率低了)
// 时间
#define  TIMEOUT_CONNECT            (u32)5000
#define  TIMEOUT_REQ                (u32)15000

// 调试控制
#define PCDV_DEBUG_CRITICAL           (u8)0
#define PCDV_DEBUG_WARNING            (u8)1
#define PCDV_DEBUG_INFO               (u8)2

// 分辨率定义
#define RES_VGA_X       640
#define RES_VGA_Y       480
#define RES_SVGA_X      800
#define RES_SVGA_Y      600
#define RES_XGA_X       1024
#define RES_XGA_Y       768
#define RES_SXGA_X		1280	//SQ081218
#define RES_SXGA_Y		1024
#define RES_UXGA_X		1600
#define RES_UXGA_Y		1200
// uilib 参数
#define TITLEHIGHT          20
#define COLOR_TITLEHILIGT   RGB(216, 228, 235)
#define COLOR_TITLELOW      RGB(54, 95, 135)
#define COLOR_BKWHITE       RGB(255, 255, 255)
#define COLOR_TEXT          RGB(67,108,145)
#define COLOR_BKDIALOG      RGB(226,234,240)


#define LOCAL_IP        htonl(0x7f000001)
#define WM_ICONNOTIFY   (WM_USER + 0xA0)

#define START_WAIT {BeginWaitCursor(); SetCapture(); }
#define END_WAIT   {RestoreWaitCursor(); EndWaitCursor(); ReleaseCapture();}


enum enState
{
    stateIdle = 0,      // 终端未连接
    stateConnectedIdle, // 不在会议中
    stateInConf,        // 在会议中
    stateSending        // 在发送双流
};

//语言类型
enum EMLanType
{
    enumLanTypeCHN      = 1,    //简体中文
    enumLanTypeENG      = 2,     //英文
	enumLanTypeOTHER      = 3    //其它语种，通过选择语言包方式选择，不限具体语言
};

#define FILENAME_CFG    "pcdv.ini"

void ShowMsg(LPCSTR lpszMsg );

#endif 