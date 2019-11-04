/*******************************************************************************
 *  模块名   : 终端业务                                                        *
 *  文件名   : mtsysapi.h                                                      *
 *  相关文件 :                                                                 *
 *  实现功能 : 提供终端业务系基本接口函数                                      *
 *  作者     : 张明义                                                          *
 *  版本     : V3.0  Copyright(c) 1997-2005 KDC, All rights reserved.          *
 *                                                                             *
 *    =======================================================================  *
 *  修改记录:                                                                  *
 *    日  期      版本        修改人      修改内容                             *
 *  2005/7/20     4.0         张明义      创建                                 *
 *                                                                             *
 *******************************************************************************/

#include "osp.h"
#include "tptype.h"
#include "tpstruct.h"
#include "mthint.h"
#ifndef _MT_SYS_API_H_
#define _MT_SYS_API_H_

#ifdef WIN32
#define MTAPI   extern "C"			__declspec(dllexport)
#else //#ifdef ( _VXWORKS_ || _LINUX_ )
#define MTAPI   extern "C"		
#endif

//终端打印函数
extern "C" void cnPrintf( char *szFormat, ... );

typedef struct tagTPingRtn
{
	s32 nTimeOut;
    s32 nReachable;  //是否到达
    s32 nTTL;
    s32 nTripTime;
}TPingRtn;

//系统升级状态
enum EmMtSysUpdateStatus
{
	emSysUpdateInit = 0,
	emSysUpdateProcessing,
	emSysUpdateSucceed,
	emSysUpdateFail	
};

typedef struct tagTModuleInit
{
	void (  *install   ) ( void );
	BOOL (  *startapp  ) ( void );
	void (  *stopapp   ) ( void );
	void (  *uninstall ) ( void );
}TModuleInit, *PTModuleInit;

API void mtStartCodec();
API void mtStopCodec();
API void mtRegCodec( BOOL ( *startapp ) ( void ) ,void ( *stopapp ) ( void ) );

API void mtStartService();
API void mtStopService();
API void mtRegService( BOOL ( *startapp ) ( void ) ,void ( *stopapp ) ( void ) );

API void mtStartMpRemoteMgr();
API void mtStopMpRemoteMgr();
API void mtRegMpRemoteMgr( BOOL ( *startapp ) ( void ) ,void ( *stopapp ) ( void ) );

API void mtStartUE();
API void mtStopUE();
API void mtRegUE( BOOL ( *startapp ) ( void ) ,void ( *stopapp ) ( void ) );

API void mtStartTPReg();
API void mtStopTPReg();
API void mtRegTPReg( BOOL ( *startapp ) ( void ) ,void ( *stopapp ) ( void ) );


MTAPI EmMtModel GetMtModel();//获取终端型号

MTAPI EmFileSys GetFileSys();//获取终端文件系统
	
BOOL mtMakeDir(const s8* path );
BOOL mtPathExist(const s8* path);
s8* mtGetFileName(EmMtFile emFile );
MTAPI BOOL HardwareInit();//硬件初始化


#if defined(_VXWORKS_) || defined(_LINUX_)

API BOOL InitDSP();
API void mtPing( s8* pchHost, s32 nPacketSize, s32 nTTL, s32 nTimeout, TPingRtn* ptReturn );

#endif//

    /*********************************************/
    /*                板级配置函数               */
    /*********************************************/

API void mtstart();
API void mtquit();

//类型转换
u8 mtMapAudioType(EmTpAudioFormat format );//Mt定义音频格式转换为KdvDef中的音频类型

//mtsysapi初始化
BOOL mtSysApiInit();
void mtSysApiExit();


//根据音频类型获取编码码率
u16 mtGetBitrate( EmTpAudioFormat emFormat );
//动态载荷
u8 mtGetDynamicPayload( EmTpVideoFormat emFormat );

enum EmPathList{
	emFtpPath = 0,
	emRamdiskConfPath,
	emConfPath,
	emUserInfoPath,
	emWebfilesPath,
	emWebDocPath,
	emDataPath,
	emResPath,
	emPathListEnd
};

void mtStartSpeaker( BOOL bOpen ); // 开启关闭扬声器

//8010终端的喂狗问题, xjx_080310
BOOL mtOpenWdGuard(u32 dwNoticeTimeout);
BOOL mtCloseWdGuard(void);
BOOL mtNoticeWdGuard(void);
BOOL mtWdGuardIsOpened(void);
s32 mtSetVidOffsetParam( u32 dwInterface, s32 dwHoff, s32 dwVoff );
void MtmpStartInstallSemphore();
void MtmpStartUninstallSemphore();

#endif/*!_MT_SYS_API_H_*/
