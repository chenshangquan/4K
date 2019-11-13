/*****************************************************************************
模块名      : globaldef
文件名      : globaldef.h
相关文件    : 
文件实现功能: umstool全局声明文件
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2012/10/30     1.0         刘德印      创建
******************************************************************************/
#ifndef GLOBALDEF_H 
#define GLOBALDEF_H

#pragma warning( disable : 4786 )	// 标识符名称超过255字节
#pragma warning( disable : 4067 )
#pragma warning( disable : 4129 )
#pragma warning( disable : 4503 )
#pragma warning( disable : 4800 )


#include "uiexhead.h"
#include "UifactoryHeader.h"
//10-common
#include "kdvType.h"		// 公共类型
#include "evCmsLib.h"

#pragma warning( disable : 4786 )
#include <afxtempl.h>
#include <afxole.h>
#include <afxdtctl.h>
#include <map>
#include <vector>

#include "msgIddispatch.h"
#define iterator _iterator

#include <string>
using namespace std;
//typedef string String;
#include "templateClass.h"
using namespace AutoUIFactory;

#ifndef   ULONG_PTR   
#define   ULONG_PTR   unsigned   long*   
#endif

//#include <gdiplus.h>   //加入会引起error C2955: 'map' : use of class template requires template argument list
#ifdef _MFC_VER
#include <afx.h>
#endif
#undef iterator

//70-common

#include "cmsConst.h"
#include "tperrno.h"
#include "umclib.h"
#include "tpmsginit.h"
#include "ftpctrl.h"       //ftp功能模块   在NmsCommon公共lib库中包含

#include <algorithm>
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
#include <set>
using namespace std;

//windows 库
#include "Shlwapi.h"
#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "wininet.lib")

enum EM_FTPTRANS_TYPE      //文件导入或导出操作
{
	em_FTPTRANS_IMPORT,
	em_FTPTRANS_EXPORT,
};

enum EM_BOARDOPT_TYPE      //板子操作类型
{
	em_BOARDOPT_ADD,
	em_BOARDOPT_MODIFY,
	em_TVWBOARDOPT_ADD,
	em_TVWBOARDOPT_MODIFY,
};

enum UMSTOOLMSG
{
	em_UMSTOOL_LOGINRESULT = UMSTOOL_MSG_BEGIN + 0x01,
#define WM_UMSTOOL_FTPLOGPROGRESS em_TPTOOL_LOGINRESULT      //日志下载进度提醒 wparam:进度值
		
		em_UMSTOOL_FTPTEMPLATEPROGRESS,
#define WM_UMSTOOL_FTPTEMPLATEPROGRESS em_UMSTOOL_FTPTEMPLATEPROGRESS      //会议模板导入导出进度提醒 wparam:进度值
		
		em_UMSTOOL_FTPADDRBOOKPROGRESS,
#define WM_UMSTOOL_FTPADDRBOOKPROGRESS em_UMSTOOL_FTPADDRBOOKPROGRESS      //地址簿导入导出进度提醒 wparam:进度值


};

enum EM_NETMNGOPT_TYPE      //网管操作类型
{
	em_NETMNGOPT_ADD,
	em_NETMNGOPT_MODIFY,
};

#define  UMSLOG_FILE_NAME			"umslog.ini"
#define  AUTH_FILE_NAME_EXP			"license.ini"
#define  AUTH_FILE_NAME_IMP			"kedalicense.key"
#define  UMSCONFIG_FILE_NAME		"umscfg.ini"
#define  TEMPLATE_FILE_NAME			"template_down.conf"
#define  ADDRBOOK_FILE_NAME		    "kdvaddrbook.kdv"
#define  BOARDUPGRADE_FILE_NAME		"boardupgrade.ini"

#define BOARD_IS22_NAME				"ums-tp.bin"
#define BOARD_EAPU_NAME				"kdvapu2.bin"
#define BOARD_MPC2_NAME				"mpc-tp.bin"
#define BOARD_CRI2_SIP_NAME			"sip-tp.bin"
#define BOARD_CRI2_DSU_NAME			"dsu-tp.bin"
#define BOARD_MPU2_VMP_NAME			"kdvmpu2.bin"
#define BOARD_MPU2_BAS_NAME			"kdvmpu2.bin"
#define BOARD_TVW_NAME				"kdvhdu2.bin"

#define  UMSLOG_FILE_PATH			"/usr/kdvlog/log"
#define  AUTH_FILE_PATH				"/usr/conf/"
#define  UMSCONFIG_FILE_PATH		"/usr/conf/"
#define  TEMPLATE_FILE_PATH			"/ramdisk/"
#define  ADDRBOOK_FILE_PATH			"/usr/conf/"
#define  BOARDUPGRADE_FILE_PATH		"/ramdisk/"

#define UMSTOOLEXCEPTION_FILE _T("umsToolExcep.log")

//////////////////////////////ui logic///////////////////////////////////////////
#define  SYSTEM_UMSTOOL_XML "resumstool\\umstoolsystem.xml"
const String g_stcStrMainFrmDlg				= "TPMainDlg";				//popup界面
const String g_stcStrSysinfoDlg				= "SysInfoDlg";				//系统基本信息界面
const String g_stcStrCorrelativeCfgDlg		= "CorrelativeCfgDlg";      //相关配置界面
const String g_stcStrAddrbookExpDlg			= "AddrbookExpDlg";			//导出地址簿界面
const String g_stcStrTemplateExpDlg			= "TemplateExpDlg";			//导出会议模板界面
const String g_stcStrBoardCfgDlg			= "BoardCfgDlg";			//单板配置界面
const String g_stcStrUmsCfgDlg				= "UmsCfgDlg";				//Ums配置界面
const String g_stcStrBoardOptDlg			= "BoardOptDlg";			//Ums单板添加修改界面
const String g_stcMsgboxDlg					= "MsgboxDlg";				//msgbox消息提示框
const String g_stcStrTvwBoardCfgDlg			= "TvwBoardCfgDlg";			//电视墙单板配置界面
const String g_stcStrNetMngCfgDlg			= "NetMngCfgDlg";			//网管配置界面
const String g_stcStrNetMngOptDlg			= "NetMngOptDlg";			//网管添加修改界面
const String g_stcStrTvwStyleCfgDlg			= "TvwStyleCfgDlg";			//电视墙预案界面
const String g_stcStrTvwStyleListMenuDlg    = "TvwStyleCfgDlg/TvwStyleListMenuDlg";		//电视墙预案菜单WS_POPUP
const String g_stcStrTvwStyleOptDlg			= "TvwStyleOptDlg";			//电视墙预案配置界面
const String g_stcStrImpCommonDlg			= "ImpCommonDlg";			//上传（导入）通用弹出界面  如：授权导入、升级相关界面   界面基本相同  通过方案区分
const String g_stcStrExpCommonDlg			= "ExpCommonDlg";			//下载（导出）通用弹出界面  如：授权导出、下载日志界面  界面基本相同  通过方案区分
const String g_stcStrVTRCfgDlg				= "VTRCfgDlg";				//录像机配置界面
const String g_stcStrVTROptDlg				= "VTROptDlg";				//录像机添加修改界面
const String g_stcWaringDlg					= "WarningDlg";				//消息提示界面
const String g_stcStrBackupCfgDlg			= "BackupCfgDlg";			//1+1备份配置界面

//umstoollib函数
#include "exceptioncatch.h"

#include "MsgDispatch.h"
#include "msghandle.h"
#include "commonmgrif.h"
#include "datamgrimp.h"
#include "sessionins.h"
#include "umstoolcommon.h"

#include "logicmanage.h"
#include "uifactorylib.h"
#include "touchlistdataproperty.h"


#endif