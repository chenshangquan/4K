
/*****************************************************************************
模块名      : DataConfLib
文件名      : DataConfLib.h
相关文件    : DataConfLib.cpp
文件实现功能: CDataConfObj Class Define
作者        : 万春雷
版本        : V3.0  Copyright(C) 2003-2005 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2004/04/22  3.0         万春雷      Create
******************************************************************************/

#ifndef _DATACONFLIB_0601_H_
#define _DATACONFLIB_0601_H_


//----------------------------------------------------------------------

//模块版本信息和编译时间 及 依赖的库的版本和编译时间
API void dataconflibfver();

//模块帮助信息 及 依赖的库的帮助信息
API void dataconflibhelp();

//----------------------------------------------------------------------

#define  WM_DCT120_CONNECTION	(WM_USER + 1)
#define  WM_DC_PLUGABLE_SOCKET  (WM_DCT120_CONNECTION + 1)

#define  WM_DC_STATE_NOTIFY     (WM_USER + 1000)

#define  DCERR_NO_ERROR          (u16)0		//DataConfLib库操作成功 
#define  DCERR_BASE_CODE         (u16)23000	//错误码基准值


#define  DCERR_NOT_INIT_LIB      (u16)(DCERR_BASE_CODE + 1)//没有初始化dc库
#define  DCERR_NOT_RELEASE_LIB   (u16)(DCERR_BASE_CODE + 2)//没有释放nb库
#define  DCERR_OUTOFMEMORY       (u16)(DCERR_BASE_CODE + 3)//内存分配错误


#define  DCERR_DC_NOCREATE       (u16)(DCERR_BASE_CODE + 11)//没有成功调用CreateDCObj()生成有效CDCManager对象
#define  DCERR_INVALID_CON_PARAM (u16)(DCERR_BASE_CODE + 12)//连接主机参数无效
#define  DCERR_CON_HOST          (u16)(DCERR_BASE_CODE + 13)//连接主机失败
#define  DCERR_NO_CON_STATE      (u16)(DCERR_BASE_CODE + 14)//没有处在已连接状态
#define  DCERR_OPEN_CHAT         (u16)(DCERR_BASE_CODE + 15)//打开聊天功能失败
#define  DCERR_OPEN_SHAREAPP     (u16)(DCERR_BASE_CODE + 16)//开启程序共享功能失败
#define  DCERR_TRANS_FILE        (u16)(DCERR_BASE_CODE + 17)//开启文件传输功能失败
#define  DCERR_WRITE_BOARD       (u16)(DCERR_BASE_CODE + 18)//开启白板功能失败
#define  DCERR_WRITE_BOARD_V12   (u16)(DCERR_BASE_CODE + 19)//开启白板(1.0-2.x)功能失败


#define  DCERR_WSA_STARTUP       (u16)(DCERR_BASE_CODE + 100)//wsastartup error
#define  DCERR_COM_STARTUP       (u16)(DCERR_BASE_CODE + 101)//create semapore error


//状态参数
typedef enum {
	DC_CON_LISTENING,    //等待中...
	DC_CON_CONNECTING,   //连接中...
	DC_CON_CONNECTED,    //已连接
	DC_CON_DISCONNECTED, //未连接, 已断开连接
	DC_CON_FAILED,       //连接失败
	DC_CON_UNKNOWN_STATE //未知连接状态
} emDCState;

//----------------------------------------------------------------------

/*=============================================================================
函数名		nbInit
功能		初始化 KEDA数字会议模块 库,重载之一， 外部使用
算法实现	：（可选项）
输入参数说明：
返回值说明： 成功返回FE_OK,  失败返回错误码
=============================================================================*/
u16 dclibInit();


/*=============================================================================
函数名		nbRelease
功能		反化 KEDA数字会议模块 库,减少引用参数计数,直至释放库，重载之一， 外部使用
算法实现	：（可选项）
输入参数说明：无
返回值说明： 成功返回FE_OK,  失败返回错误码
=============================================================================*/
u16 dclibRelease();


class CDCManager;

class CDataConfObj
{
public:
    CDataConfObj();
    ~CDataConfObj();
	
public:
	u16  CreateDCObj( HWND hPWnd );
	u16  FreeDCObj( );

	u16  ConnectHost(LPSTR pszHostName, u16 wPort=1503);
	u16  Disconnect();
	u16  Chat();
	u16  ShareApp();
	u16  TransFile();
	u16  WhiteBoard();
	u16  WhiteBoardV12();

	u16  CallBackMsg(u32 dwMsg, WPARAM wParam, LPARAM lParam);
	
	u16  GetState(emDCState &emDCState);
	u16  GetDCLastError(CString &szLastErr);
	
private:
	CDCManager *m_pcDCManager;
};


//----------------------------------------------------------------------

#endif /////_DATACONFLIB_0601_H_