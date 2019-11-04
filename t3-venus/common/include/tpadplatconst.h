#pragma once

#ifndef _TPADPLATCONST_H_
#define _TPADPLATCONST_H_

#include "printctrl.h"  

//------------------------------常量部分------begin-------------------------------
#define ARRAY                  vector
#define INVALID_WORD           0xffff                                          //非法的u16 / unsinged short 类型的值
#define INVALID_DWORD          0xffffffffff                                    //非法的u32/ DWORD 类型的值
#define MSG_SUCESS             -1                                              //消息传递时使用


#define MAX_PAGEITEM_COUNT        12                                         //MainMenu一页显示的最多Item个数

#define MANAGER_USER              "admin"                                    //管理员用户名
#define MANAGER_PSWD              "kedacomTP"									 //管理员密码
#define TP_PASSWORD               "tpkedacom"                                //解锁超级密码


#define WIFI_MAX_SEARCH_NUM     (30)                                         //wifi能搜索到的最大数


//MainMenu名
#define MENU_CNSCONSOLE        _T("会议管理")       
#define MENU_NETCFG            _T("网络设置")
#define MENU_IEXPLORE          _T("浏览器")
#define MENU_VOLUMECTRL        _T("音量控制")
#define MENU_READSHARE         _T("文件共享")              /*_T("阅读与共享")*/
#define MENU_SYSLOG            _T("系统日志")
#define MENU_FILEMANAGE        _T("文件管理")
#define MENU_REBOOT            _T("重启")
#define MENU_SHUTDOWN          _T("关机")
#define MENU_SLEEP             _T("待机")
#define MENU_SYSUPDATE         _T("系统升级")
#define MENU_CENTERCTRL        _T("中控管理")
#define MENU_LOUOUT            _T("注销")
#define MENU_WATCHVEDIO		   _T("收看演示")
#define MENU_DATACONF          _T("数据会议")


#define CENTERCTRL_PATH      _T("centerctrl\\bin\\")         // 中控系统目录



#define TPAD_VERSION_ID	   "1.1.4.0.1."

#define CONNETCT_CNS_PORT  60002                             //cns服务器端口

#define TPAD_LISTEN_PORT   60888                             //TPad监听端口

#define AID_TPAD_MSGTRANS    1                               //TPad消息转发App
#define AID_TPAD_CNC         2                               //TPad中cnc App
#define AID_TPAD_CENTERCTRL  3                               //TPad中中控 App


#define PrtMsg (CPrintCtrl::GetPrintCtrl()->PrintMsg)                        //打印消息接口
#define PrtMsgForce (CPrintCtrl::GetPrintCtrl()->ForcePrtMsg)
#define IS_PRINT_ENTER_MSG (CPrintCtrl::GetPrintCtrl()->IsPrintEnterMsg())   //是否要打印入口处消息
#define IS_PRINT_OUT_MSG (CPrintCtrl::GetPrintCtrl()->IsPrintOutMsg())       //是否打印出口处消息
#define MAPPING_HELPER (CPrintCtrl::GetPrintCtrl()->MappingHelper)           //注册打印的消息名



//TPad内部消息定义
#include "msgIdDispatch.h"

enum EmUiTPadMsg
{
#define UI_TPAD_MSG_BEGIN    TPAD_MSG_BEGIN

	    ev_UIUpdateMainMenu  = UI_TPAD_MSG_BEGIN,
#define	UI_TPAD_UPDATE_MAINMENU    ev_UIUpdateMainMenu


        ev_UIShowWifiConnectingDlg,
#define	UI_TPAD_SHOW_WIFI_CONNECTING_DLG    ev_UIShowWifiConnectingDlg

        ev_UIHideWifiConnectingDlg,
#define	UI_TPAD_HIDE_WIFI_CONNECTING_DLG    ev_UIHideWifiConnectingDlg

		ev_UIWifiConnectingTimeOut,
#define	UI_TPAD_WIFICONNECTING_TIMEOUT    ev_UIWifiConnectingTimeOut

		ev_UIWifiCancleConnect,
#define	UI_TPAD_WIFI_CANCLE_CONNECT         ev_UIWifiCancleConnect

		ev_UIRefreshWifi,
#define UI_TPAD_REFRESH_WIFI                ev_UIRefreshWifi    

		/************************************************************************/
		/** 系统升级完毕
		wParam =    
		lparam = 0*/
		/************************************************************************/
		ev_UISysUpdateOver,
#define	UI_TPAD_SYSUPDATE_OVER              ev_UISysUpdateOver

        ev_UITPadUpdate_Progress,
#define	UI_TPADUPDATE_PROGRESS              ev_UITPadUpdate_Progress

		ev_UITPadEnd,
#define UI_TPAD_MSG_END    ev_UITPadEnd
};



//------------------------------错误码部分------begin-------------------------------
/* 摘自errorid.h
/*TPadPlat错误码 （29501 - 30000）
#define ERR_TPADPLAT_BGN      ERR_CMS_END + 1
#define ERR_TPADPLAT_END      ERR_TPADPLAT_BGN + 499
*/
#include "errorid.h"	// 错误码范围段定义

//共用部分 
enum EmErrTPad
{
#define  ERR_TPAD_BEGIN   ERR_TPADPLAT_BGN

	errTPadPlat = ERR_TPAD_BEGIN,
#define  ERR_TPADPLAT   errTPadPlat 

    errTPadInterface,
#define  ERR_TPAD_INTERFACE  errTPadInterface

    errTPadOspInit,
#define  ERR_TPAD_OSPINIT  errTPadOspInit

    errTPadCreatTcpNode,
#define  ERR_TPAD_CREAT_TCPNODE  errTPadCreatTcpNode

    errTPadActiveConnect,
#define  ERR_TPAD_ACTIVE_CONNECT  errTPadActiveConnect

    errTPadTcpConnect,
#define  ERR_TPAD_TCPCONNECT  errTPadTcpConnect

    errTPadWaitForSendCmd,
#define  ERR_TPAD_WAIT_FOR_SEND_CMD  errTPadWaitForSendCmd

	errTPadPlatEnd,
#define ERR_TPAD_END  errTPadPlatEnd
};  
 

 
#endif
