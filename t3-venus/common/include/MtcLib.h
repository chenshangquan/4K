/*=======================================================================
模块名      : 终端控制台
文件名      : MtcLib.h
相关文件    : 
文件实现功能: 声明终端控制台接口
作者        : 熊广化
版本        : V3.0  Copyright(C) 1997-2003 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2003/12/15  3.0         熊广化      创建
2004/08/23  3.5         李洪强      规范代码，更改结构
2005/06/22  3.6         张寒冰      修改，将各类移入不同的头文件中，减小编译依存性
=======================================================================*/
#ifndef MTCLIB_H
#define MTCLIB_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning( disable : 4786 )	// 标识符名称超过255字节
#include <vector>
#include <map>

#include <afxmt.h>
#include "kdvType.h"		// 公共类型
#include "kdvdef.h"			// 公共宏定义
#include "osp.h"			// OSP业务
#include "MtcLibEvent.h"	// 终端控制台内部事件
#include "MtcLibError.h"	// 错误码
#include "ummessagestruct.h"// 身份验证业务
#include "evusermanage.h"	// 身份验证业务
#include "Addrbook.h"		// 地址簿业务
//#include "vccommon.h"		// 终端控制业务
#include "IMtcConnectMt.h"
#include "MtcMt.h"

#define AID_MTC_INTTEST	AID_MTC_BGN + 0	// 21 @kdvDef.h

typedef void (CALLBACK* SDKCALLBACKFUNC)(DWORD dwMsgID, WPARAM wParam, LPARAM lParam);

class CDispEvent;
////////////////////////////////////////////////////////////////////////////////
class CMtcLib
{
	friend class CDispEvent;
public:
	/*功能	创建实现了接口IMtcConnectMt的对象
	参数	ppICnt	[out]成功返回IMtcConnectMt接口,失败返回NULL
	返回值	成功返回0,失败返回非0错误码
	说明	接口使用完成后,调用DestroyInstance方法销毁对象*/
	static u16 CreateInstance(IMtcConnectMt **ppICnt);
	/*功能	销毁实现了接口IMtcConnectMt的对象
	参数	ppICnt	[in, out]接口IMtcConnectMt,成功后返回NULL
	返回值	成功返回0,失败返回非0错误码
	说明	只能销毁由CreateInstance方法创建的对象*/
	static u16 DestroyInstance(IMtcConnectMt **ppICnt);
	/*功能	获取本机首选IP
	参数	无
	返回值	本机首选IP(主机序)
	说明	无*/
	static u32 GetHostIP();
	/*功能	设置消息发送接收调试信息
	参数	b32On		是否输出
			dwCatalog	消息类别
	返回值	无
	说明	无*/
	static void MsgLog(BOOL b32On, u32 dwCatalog);
	/*功能	获取分类调试信息输出状态
    参数	dwSN		是否输出
            dwCatalog	消息类别
    返回值	无
    说明	无*/
	static void GetTraceStatus(u32 &dwSN, u32* dwCatalog);


	static void SetPointOfCallBackFunc(SDKCALLBACKFUNC  pCallBack);
	
	static SDKCALLBACKFUNC m_spCallBackFunc;

private:
#define MTC_MSGCATALOG_COUNT 12
	// 消息分类调试信息输出状态
	static u32 s_dwCatalog[MTC_MSGCATALOG_COUNT];
	// 消息分类说明
	static char* s_szCataDesc[MTC_MSGCATALOG_COUNT];
	static CCriticalSection s_csCatalog;
	// 修改序号,用于同步标识
	static u32 s_dwSN;
};
API void cls();
API u32 mtclibver();
API u32 mtclibhelp();
API void cfghelp();
API void confhelp();
API u32 mtclibmsgon(u32 dwOn);
API u32 mtclibmsgoff(u32 dwOff);

//MutiConf
API void mtlist();
API void confinfo();
API void conflist();
API void reqchairlist();
API void reqspeaklist();
API void vmpstatus();
API void pollstatus();
//p2p
API void caller();
API void mtme();

//audio
API void audio();

//address
API void addrinfo();

//snap
API void snap();

//user
API void alluser();


//配置
API void h323cfg();
API void usercfg();
API void osdcfg();
API void avpriorcfg();
API void videoparam(u8 byType);
API void audioparam();
API void firewall(); 
API void napmapcfg();
API void ethnetcfg();
API void snmpcfg();
API void pppoecfg();
API void cameracfg();
API void serialcfg();
API void qoscfg();
API void imageadjust();
API void videosource();
API void e1cfg();
API void allroutecfg();

API void reqikey(u8 byLocal);


#endif //MTCLIB_H










































