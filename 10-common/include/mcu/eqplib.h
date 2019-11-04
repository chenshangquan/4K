/*
	外设库 初始化调用入口函数
*/
#ifndef _KDV_EQP_LIB_INI_H_
#define _KDV_EQP_LIB_INI_H_

#include "eqpcfg.h"
//码流适配器初始化函数
BOOL basInit(TEqpCfg* ptCfg);
//bool basInit( TEqpCfg* ptCfg );


//电视墙初始化函数
BOOL twInit(TEqpCfg* ptCfg);
//bool  twInit( TEqpCfg* ptCfg );


//混音器初始化函数
BOOL mixInit(TAudioMixerCfg* tAudioMixerCfg);
//bool  mixInit(TAudioMixerCfg* tAudioMixerCfg);


// 画面合成初始化
BOOL vmpinit(TVmpCfg * ptVmpCfg);
//void  vmpinit(TEqpCfg* tVmpCfg, u8 byDbVid);

BOOL32 MpwInit(TVmpCfg& tVmpCfg);

BOOL MpuInit( TMpuCfg* ptCfg, u8 byWorkMode, u8 byEqpId2 );
API void vmphelp(void);
API void vmpver(void);

API void twver(void);
API void basver(void);
API void mixerver(void);

API void mmpagtver(void);
API void imtagtver(void);

#ifdef WIN32
API bool prsinit(TPrsCfg* tPrsCfg);
#else
bool prsinit(TPrsCfg* tPrsCfg);
#endif
API void prsver(void);
API void prshelp(void);

#endif/*! _KDV_EQP_LIB_INI_H_*/
