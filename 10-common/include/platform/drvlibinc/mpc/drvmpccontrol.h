/*****************************************************************************
模块名      : mcu
文件名      : drvMpcControl.h
相关文件    : drvMpcControl.c
文件实现功能:  内部使用的一些宏定义和函数声明.
作者        : 张方明
版本        : V1.0  Copyright(C) 2003-2005 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2003/8/19   01a         张方明      创建	
******************************************************************************/
#ifndef __INCdrvMpcControlh
#define __INCdrvMpcControlh

#ifdef __cplusplus
extern "C" {
#endif

#include "time.h"
#include "timers.h"

/* FPGA写寄存器BIT位掩码  */
#define FPGA_WD_REG0       ((UINT8)0X00) 
#define FPGA_WD_REG1       ((UINT8)0X01)
#define FPGA_WD_REG2       ((UINT8)0X02)

#define FPGA_REG_WDIN      ((UINT8)0x01) 
#define FPGA_REG_WDEN      ((UINT8)0X80) 
#define FPGA_WR_REG_MS     ((UINT8)0X04)

#define FPGA_REG_MSEL      ((UINT8)0X01) 
#define FPGA_REG_FSEL      ((UINT8)0X02) 
#define FPGA_REG_FS1       ((UINT8)0X04) 
#define FPGA_REG_FS2       ((UINT8)0X08) 

#define FPGA_REG_DRST      ((UINT8)0X01) 
#define FPGA_REG_MRST      ((UINT8)0X02) 
#define FPGA_REG_HIRSTO    ((UINT8)0X04) 
#define FPGA_REG_HSRSTEN   ((UINT8)0X08) 


/*==================================以太网模块设置===============================*/
/* 网络设备参数netEquipUnit宏定义 */
#define NETEQUIP_IS_ETH1    1    /* 以太网1： 对应8265的FCC2 或 x86上的启动网卡 */
#define NETEQUIP_IS_ETH2    2    /* 以太网2： 对应8265的FCC1 或 x86上的网关网卡*/
#define NETEQUIP_IS_ETH3    3    /* 以太网3： 对应8265的SCC1 */
#define NETEQUIP_IS_IPOH    4    /* IPOH  ：  对应8265的MCC1 */


/* MPC板功能设置部分 444444444444444444444444444444444444444444444444444 */


/* 函数声明 */
STATUS BrdMPCSetNetSyncMode(UINT8 mode);   /* 锁相环网同步模式选择设置 */
STATUS BrdMPCResetSDH(void);               /* 光模块复位 */
STATUS BrdMPCReSetAnotherMPC(void);        /* 复位对端主处理机 */
STATUS BrdMPCOppReSetDisable (void);       /* 禁止对端主处理机复位本主处理机 */
STATUS BrdMPCOppReSetEnable (void);        /* 允许对端主处理机复位本主处理机 */
void BrdMpcWatchdogMode(UINT8 data);
void BrdMpcFeedDog(void);
STATUS BrdMPCLedBoardSpeakerSet(UINT8 state);
STATUS BrdMPCLedBoardLedSet(UINT8 LedID, UINT8 state);
STATUS BrdTimeGet( struct tm* pGettm );        /* 读取RTC时间 */
STATUS BrdTimeSet( struct tm* pSettm );        /* 设置RTC和系统时间 */ 

/*设置网卡的IP地址、MAC地址和子网掩码*/
STATUS ethernetSet
    (
    int netEquipUnit,	 /* 见上 */
    char *pIpAddrStr,    /* ip地址 例:"100.1.1.1" */
    int   netmask  ,     /* 子网掩码 ：例:0xff000000 ;0 = 自动识别 */
    char *pEtherMacAddr  /* mac地址：null -> 不改变当前值 
                         例：unsigned char sysFccEnetAddr [6] = {0x08, 0x00, 0x33, 0x02, 0x02, 0x51};*/
    );



/*==============================网同步=============================*/  
/* 同步模式宏定义 */
#define SYNC_MODE_TRACK_2M_SLAVE  4   /* 跟踪模式，作为下级MCU应设置为该模式，跟踪DT来的从2M时钟 */

/* 函数定义 */
void BrdNetSyncModeSet(UINT8 mode);                 /* 网同步模式设置
                                                       输入参数: 见同步模式宏定义 */
void BrdNetSyncSrcSelect(UINT8 dtiNo, UINT8 E1No);  /* 网同步源选择
                                                       输入参数: dtiNo 范围0~14；E1No范围0~7 */
int BrdNetSyncLock(void);                           /* 检测网同步跟踪模式时是否锁定时钟源
                                                       输出参数：#define SYNC_CLOCK_UNLOCK 0    跟踪模式时时钟未锁定 
                                                                #define SYNC_CLOCK_LOCK   1    跟踪模式时时钟锁定成功 
                                                       注：只有当前MCU配成跟踪模式时才有效，自由振荡时
                                                       MCU不会跟踪任何时钟，调该函数是无效的，永远返回未锁定 */





#ifdef __cplusplus
}
#endif

#endif /* __INCdrvMpcPatchh */