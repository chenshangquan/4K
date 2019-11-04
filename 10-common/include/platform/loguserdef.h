/*****************************************************************************
   模块名      : kdvlog
   文件名      : logusrdef.h
   相关文件    : kdvlog.h
   文件实现功能: 模块ID的定义
   注意事项	   : 需要新添加模块ID, 请跟mcu组联系
   作者        : 刘旭
   版本        : V4.6  Copyright(C) 2001-2011 KDC, All rights reserved.
-----------------------------------------------------------------------------
   修改记录:
   日  期      版本        修改人      修改内容
   2011/04/5   4.6          刘旭        创建
******************************************************************************/

#ifndef KDV_LOG_USER_DEF_H
#define KDV_LOG_USER_DEF_H

#include "kdvtype.h"
#include "kdvlog.h"

// 模块名起始值定义, 从0开始
#define MID_START						(u16)0

/************************************************************************/
/* 各模块范围值定义                                                     */
/************************************************************************/
// 公共索引的起始值, 从0开始, 范围[0， 99]
#define MID_PUBLIC_START				(u16)(MID_START + 1)

// mcu模块的起始值, 从100开始,范围[100,499]
#define MID_MCU_START					(u16)(MID_PUBLIC_START + 100)

// wy[2014/08/26] mau模块的起始值，从501开始，范围[500，599]
#define MID_MAU_START					(u16)(MID_MCU_START + 400)

// 会控模块的起始值, 从600开始,范围[600,799]
#define MID_MCS_START					(u16)(MID_MAU_START + 100)
// 终端起始值, 从800开始,范围[800,999]
#define MID_MT_START					(u16)(MID_MCS_START + 200)
// 外设的起始值, 从5000开始,范围[5000,6000]
#define MID_PERI_START					(u16)(MID_START + 5000)

/************************************************************************/
/*  公共索引定义                                                        */
/************************************************************************/
MODULE_DEF( MID_PUB_ALWAYS,			MID_PUBLIC_START + 0 );		// 任何情况都打印

/************************************************************************/
/* MCU模块索引定义                                                      */
/************************************************************************/
MODULE_DEF( MID_MCU_MCS,			MID_MCU_START + 0 );		// pmcsmsg
MODULE_DEF( MID_MCU_VCS,			MID_MCU_START + 1 );		// pvcsmsg
MODULE_DEF( MID_MCU_EQP,			MID_MCU_START + 2 );		// peqpmsg
MODULE_DEF( MID_MCU_REC,			MID_MCU_START + 3 );		// peqpmsg
MODULE_DEF( MID_MCU_HDU,			MID_MCU_START + 4 );		// peqpmsg

MODULE_DEF( MID_MCU_VMP,			MID_MCU_START + 5 );		// peqpmsg
MODULE_DEF( MID_MCU_BAS,			MID_MCU_START + 6 );		// peqpmsg
MODULE_DEF( MID_MCU_PRS,			MID_MCU_START + 7 );		// peqpmsg
MODULE_DEF( MID_MCU_MIXER,			MID_MCU_START + 8 );		// peqpmsg

MODULE_DEF( MID_MCU_SPY,			MID_MCU_START + 16 );		// pspymsg
MODULE_DEF( MID_MCU_MMCU,			MID_MCU_START + 17 );		// pmmcumsg
MODULE_DEF( MID_MCU_DCS,			MID_MCU_START + 18 );		// pdcsmsg
MODULE_DEF( MID_MCU_MT	,			MID_MCU_START + 19 );		// pmtmsg
MODULE_DEF( MID_MCU_MT2,			MID_MCU_START + 20 );		// pmt2msg

MODULE_DEF( MID_MCU_CALL,			MID_MCU_START + 21 );		// pcallmsg
MODULE_DEF( MID_MCU_MPMGR,			MID_MCU_START + 22 );		// pmpmgrmsg
MODULE_DEF( MID_MCU_CFG,			MID_MCU_START + 23 );		// pcfgmsg
MODULE_DEF( MID_MCU_GUARD,			MID_MCU_START + 24 );		// pgdmsg
MODULE_DEF( MID_MCU_NPLUS,			MID_MCU_START + 25 );		// pnplusmsg

MODULE_DEF( MID_MCU_PFM,			MID_MCU_START + 26 );		// ppfmmsg
MODULE_DEF( MID_MCU_MSMGR,			MID_MCU_START + 27 );		// CMSManagerSsnInst

MODULE_DEF( MID_MCU_CONF,			MID_MCU_START + 40 );		// ConfLog
MODULE_DEF( MID_CONFCFG_CONFTEMPLATE,		MID_MCU_START + 41 );		// 会议模板配置模块
MODULE_DEF( MID_CONFCFG_HDUCFG,		        MID_MCU_START + 42 );		// hdu预案配置模块
MODULE_DEF( MID_CONFCFG_VMPCFG,		        MID_MCU_START + 43 );		// 画面合成预案配置模块
MODULE_DEF( MID_CONFCFG_CONFPLAN,		    MID_MCU_START + 44 );		// 会议预案配置模块
MODULE_DEF( MID_CONFCFG_SECHUDLECONF,		MID_MCU_START + 45 );		// 预约会议计时模块

MODULE_DEF( MID_MCU_MAUSSN, 		MID_MCU_START + 46 );		// MauSsn模块
MODULE_DEF( MID_MCU_RESPOOL, 		MID_MCU_START + 47 );		// ResPool模块
MODULE_DEF( MID_MCU_MP,      		MID_MCU_START + 48 );		// Mp模块



// mcu其它lib库打印
MODULE_DEF( MID_MCULIB_MTADP,		MID_MCU_START + 100 );		// MtAdp log

MODULE_DEF( MID_MCULIB_MCUAGT,		MID_MCU_START + 110 );		// MCU Agent log

MODULE_DEF( MID_MCULIB_MMCULIB,		MID_MCU_START + 111 );		// MMcuLib log 级联库
MODULE_DEF( MID_BOARDMGR_BRDMONITOR,        MID_MCU_START + 112 );		// 单板监控模块
MODULE_DEF( MID_BOARDMGR_BRDPROCESSGUARD,   MID_MCU_START + 113 );		// 进程守护模块

/************************************************************************/
/* 外设ID定义                                                         */
/************************************************************************/

// 录像外设的起始值, 从1000开始,范围[1000,1019]
#define MID_RECEQP_START			(u16)(MID_START + 1000)
// BAS外设的起始值, 从1020开始,范围[1020,1039]
#define MID_BASEQP_START			(u16)(MID_RECEQP_START + 20)
// HDU外设的起始值, 从1040开始,范围[1040,1059]
#define MID_HDUEQP_START			(u16)(MID_BASEQP_START + 20)
// VMP外设的起始值, 从1060开始,范围[1060,1079]
#define MID_VMPEQP_START			(u16)(MID_HDUEQP_START + 20)
// BAS外设的起始值, 从1080开始,范围[1080,1099]
#define MID_MIXEQP_START			(u16)(MID_VMPEQP_START + 20)
// TVW外设的起始值, 从1100开始,范围[1100,1119]
#define MID_TVWEQP_START			(u16)(MID_MIXEQP_START + 20)
// TVW外设的起始值, 从1120开始,范围[1120,1139]
#define MID_PRSEQP_START			(u16)(MID_TVWEQP_START + 20)
// SNMP网元起始值, 从1140开始, 范围[1140, 1159]
#define MID_SNMP_START				(u16)(MID_PRSEQP_START + 20)
// VRS业务起始值,从1160开始,范围[1160, 1179]
#define MID_VRS_START               (u16)(MID_SNMP_START + 20)
// 组件平台起始值,从1180开始,范围[1180,　1189]
#define MID_COMPONENT_START         (u16)(MID_VRS_START + 20)
// 端口业务起始值，从1190开始,范围[1190,　1199]
#define MID_PORT_START              (u16)(MID_COMPONENT_START + 10)
// Acs模块      [1200, 1219]
#define MID_ACS_START               (u16)(MID_PORT_START + 10)
// ApiServer模块[1220, 1239]
#define MID_MCSDK_START             (u16)(MID_ACS_START  + 20)

// 录像机的ID定义
MODULE_DEF( MID_RECEQP_COMMON,		MID_RECEQP_START + 0 );			// 通常
MODULE_DEF( MID_RECEQP_ASFLIB,		MID_RECEQP_START + 3 );			// asflib库
MODULE_DEF( MID_RECEQP_RPCTRL,		MID_RECEQP_START + 6 );			// rpctrl库
MODULE_DEF( MID_RECEQP_REC,			MID_RECEQP_START + 9 );			// 录像功能
MODULE_DEF( MID_RECEQP_PLAY,		MID_RECEQP_START + 12 );		// 放像功能
MODULE_DEF( MID_RECEQP_RECSERVER,	MID_RECEQP_START + 15 );		// 录像服务器

// Bas外设
MODULE_DEF( MID_BASEQP_COMMON,		MID_BASEQP_START + 0 );			// 通常
MODULE_DEF( MID_AUDBASEQP_COMMON,   MID_BASEQP_START + 1 );         // 音频适配
MODULE_DEF( MID_VIDBASEQP_COMMON,   MID_BASEQP_START + 2 );         // 视频适配
// HDU外设
MODULE_DEF( MID_HDUEQP_COMMON,		MID_HDUEQP_START + 0 );			// 通常

// VMP外设
MODULE_DEF( MID_VMPEQP_COMMON,		MID_VMPEQP_START + 0 );			// 通常
MODULE_DEF( MID_VMPEQP_DRAWBMP,		MID_VMPEQP_START + 1 );			//drawBmp模块

// MIX外设
MODULE_DEF( MID_MIXEQP_COMMON,		MID_MIXEQP_START + 0 );			// 通常

// MIX外设
MODULE_DEF( MID_TVWEQP_COMMON,		MID_TVWEQP_START + 0 );			// 通常

// PRS外设
MODULE_DEF( MID_PRSEQP_COMMON,		MID_PRSEQP_START + 0 );			// 通常

// SNMP网元 
MODULE_DEF( MID_SNMP_EQPAGT,		MID_SNMP_START + 0 );			// 通常
// SNMP mgr_client
MODULE_DEF( MID_SNMPMGR_CLIENT,		MID_SNMP_START + 1 );			// 网管客户端
// SNMP mgr_server
MODULE_DEF( MID_SNMPMGR_SERVER,		MID_SNMP_START + 2 );			// 网管服务器
// sm
MODULE_DEF( MID_SM_COMMON,          MID_SNMP_START + 3 );
// nms
MODULE_DEF( MID_NMS_COMMON,         MID_SNMP_START + 4 );

//CNS
MODULE_DEF (MID_CNS_1,				MID_MT_START + 1 );			//802			
MODULE_DEF (MID_CNS_2,				MID_MT_START + 2 );			//803	
MODULE_DEF (MID_CNS_3,				MID_MT_START + 3 );			//804
MODULE_DEF (MID_CNS_4,				MID_MT_START + 4 );			//805
MODULE_DEF (MID_CNS_5,				MID_MT_START + 5 );			//806	
MODULE_DEF (MID_CNS_6,				MID_MT_START + 6 );			//807
MODULE_DEF (MID_CNS_7,				MID_MT_START + 7 );			//808
MODULE_DEF (MID_CNS_8,				MID_MT_START + 8 );			//809	
MODULE_DEF (MID_CNS_9,				MID_MT_START + 9 );			//810
MODULE_DEF (MID_CNS_10,				MID_MT_START + 10 );		//811
MODULE_DEF (MID_CNS_11,				MID_MT_START + 11 );		//812			
MODULE_DEF (MID_CNS_12,				MID_MT_START + 12 );		//813	
MODULE_DEF (MID_CNS_13,				MID_MT_START + 13 );		//814
MODULE_DEF (MID_CNS_14,				MID_MT_START + 14 );		//815
MODULE_DEF (MID_CNS_15,				MID_MT_START + 15 );		//816	
MODULE_DEF (MID_CNS_16,				MID_MT_START + 16 );		//817
MODULE_DEF (MID_CNS_17,				MID_MT_START + 17 );		//818
MODULE_DEF (MID_CNS_18,				MID_MT_START + 18 );		//819	
MODULE_DEF (MID_CNS_19,				MID_MT_START + 19 );		//820
MODULE_DEF (MID_CNS_20,				MID_MT_START + 20 );		//821

//UMS
MODULE_DEF (MID_UMS_1,				MID_MT_START + 51 );			//852			
MODULE_DEF (MID_UMS_2,				MID_MT_START + 52 );			//853	
MODULE_DEF (MID_UMS_3,				MID_MT_START + 53 );			//854
MODULE_DEF (MID_UMS_4,				MID_MT_START + 54 );			//855
MODULE_DEF (MID_UMS_5,				MID_MT_START + 55 );			//856	
MODULE_DEF (MID_UMS_6,				MID_MT_START + 56 );			//857
MODULE_DEF (MID_UMS_7,				MID_MT_START + 57 );			//858
MODULE_DEF (MID_UMS_8,				MID_MT_START + 58 );			//859	
MODULE_DEF (MID_UMS_9,				MID_MT_START + 59 );			//860
MODULE_DEF (MID_UMS_10,				MID_MT_START + 60 );		//861
MODULE_DEF (MID_UMS_11,				MID_MT_START + 61 );		//862			
MODULE_DEF (MID_UMS_12,				MID_MT_START + 62 );		//863	
MODULE_DEF (MID_UMS_13,				MID_MT_START + 63 );		//864
MODULE_DEF (MID_UMS_14,				MID_MT_START + 64 );		//865
MODULE_DEF (MID_UMS_15,				MID_MT_START + 65 );		//866	
MODULE_DEF (MID_UMS_16,				MID_MT_START + 66 );		//867
MODULE_DEF (MID_UMS_17,				MID_MT_START + 67 );		//868
MODULE_DEF (MID_UMS_18,				MID_MT_START + 68 );		//869	
MODULE_DEF (MID_UMS_19,				MID_MT_START + 69 );		//870
MODULE_DEF (MID_UMS_20,				MID_MT_START + 70 );		//871

//VRS
MODULE_DEF (MID_VRSMC_CONF,         MID_VRS_START + 0 );		//1160
MODULE_DEF (MID_VRSMC_DB,           MID_VRS_START + 1 );        //1161
MODULE_DEF (MID_VRSMC_WEBS,         MID_VRS_START + 2 );        //1162
MODULE_DEF (MID_VRSMC_KMS,          MID_VRS_START + 3 );        //1163
MODULE_DEF (MID_VRSMC_EQP,          MID_VRS_START + 4 );        //1164
MODULE_DEF (MID_KMS_COMMON,         MID_VRS_START + 5 );        //1165
MODULE_DEF (MID_VRSDB,              MID_VRS_START + 6 );        //1166
MODULE_DEF (MID_VRSWEBSRV,          MID_VRS_START + 7 );        //1167
MODULE_DEF (MID_VRSWEBSRV_RP,       MID_VRS_START + 8 );        //1168
MODULE_DEF (MID_VRSFCGI,            MID_VRS_START + 9 );        //1169

//COMPONENT
MODULE_DEF (MID_COMLIB_CONFMGR,     MID_COMPONENT_START + 0 );		//1180
MODULE_DEF (MID_COMLIB_MSGRCVSND,   MID_COMPONENT_START + 1 );		//1181
MODULE_DEF (MID_COMLIB_ACC,         MID_COMPONENT_START + 2 );		//1182
MODULE_DEF (MID_COMLIB_PA,          MID_COMPONENT_START + 3 );		//1183

//Port
MODULE_DEF (MID_PORTDECENCEQP_COMMON,    MID_PORT_START + 0 );      //1190
MODULE_DEF (MID_PORTMULPICEQP_COMMON,    MID_PORT_START + 1 );      //1190

// Acs模块      [1200, 1219]
MODULE_DEF (MID_ACS_CONF,           MID_ACS_START + 0);         //1200
MODULE_DEF (MID_ACS_MCS,            MID_ACS_START + 1);         //1201
MODULE_DEF (MID_ACS_MNGR,           MID_ACS_START + 2);         //1202
MODULE_DEF (MID_ACS_HDU,            MID_ACS_START + 3);         //1203
MODULE_DEF (MID_ACS_CEU,            MID_ACS_START + 4);         //1204
MODULE_DEF (MID_ACS_ADP,            MID_ACS_START + 5);         //1205
MODULE_DEF (MID_ACS_DB,             MID_ACS_START + 6);         //1206

// ApiServer模块[1220, 1239]
MODULE_DEF (MID_MCSDK_DATADRIVER,   MID_MCSDK_START + 0);      //1220
MODULE_DEF (MID_MCSDK_MEETINGCONTROL, MID_MCSDK_START+1);      //1221
MODULE_DEF (MID_MCSDK_USERSESSION,  MID_MCSDK_START + 2);      //1222

#endif
//end of file