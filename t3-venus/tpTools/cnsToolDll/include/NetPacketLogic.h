// NetPacketLogic.h: interface for the CNetPacketLogic class.
//
//////////////////////////////////////////////////////////////////////

/*****************************************************************************
模块名      : CNetPacketLogic
文件名      : NetPacketLogic.h
相关文件    : telnetsocket.h
文件实现功能: 网口抓包界面
作者        : 杨奇峰
版本        : V1.0  Copyright(C) 2012-2016 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2016/8/15      1.0                     创建
******************************************************************************/

#if !defined(AFX_NETPACKETLOGIC_H__FF5413C7_513C_4617_BFF6_B87F5FCE8936__INCLUDED_)
#define AFX_NETPACKETLOGIC_H__FF5413C7_513C_4617_BFF6_B87F5FCE8936__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"
#include "telnetsocket.h"

enum EM_FTPCAPTURETRANS_TYPE      //文件导入或导出操作
{
	em_FTPCAPTRANS_IMPORT,
	em_FTPCAPTRANS_EXPORT,
};

class CNetPacketLogic: public CLogicBase, public ISingleTon<CNetPacketLogic>
{
public:
	CNetPacketLogic();
	~CNetPacketLogic();

public:
	/** 功能:  注册回调函数
	*  @param[in] 
	*  @return 
	*  @remarks  在读取xml文件时候,会调用其中注册的函数
	*/
	virtual void RegCBFun();
	/** 功能:  反注册回调函数
	*  @param[in] 
	*  @return 
	*  @remarks  与上面函数相反,注销注册的函数
	*/
	virtual void UnRegFunc();
	/** 功能:  初始化窗口
	*  @param[in] 
	*  @return 
	*  @remarks  在读取xml文件时候调用,根据里面的内容初始化窗口
	*/	
    virtual bool InitWnd( const IArgs & arg ); 
	/** 功能:  清理窗口
	*  @param[in] 
	*  @return 
	*  @remarks  在窗口关闭的时候调用,清空窗口数据
	*/
    virtual void Clear();
	
	//更新抓包信息
	void UpdateCaptureData();
	//获得当前抓包状态
	bool GetCaptureState();
	//获得当前导出状态
	bool GetExportState();

	void SetCaptureFileSize();

protected:
		/** 功能: 注册消息,接收来自lib库中发送来的消息
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/	
	virtual void RegMsg(); 
		
	/** 功能: 反注册消息,与上面函数相反,注销注册的消息
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/	
	virtual void UnRegMsg();

	/**	 
	* 功能:  更新传输进度
	* @return   
	* @remarks	 
	*/
	bool OnExportProgress( const IArgs & arg );  //导出进度提醒

	bool OnCaptureMaxSize( const IArgs & arg );  //达到抓包上限时的停止抓包的响应

	bool OnCaptureFail(const IArgs & arg);       //抓包失败

	/** 功能:  ftp消息响应
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	HRESULT OnSetFtpInfoRsp( WPARAM wparam, LPARAM lparam );
	/** 功能:  telnet消息响应
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
    HRESULT OnSetTelnetInfoRsp( WPARAM wparam, LPARAM lparam );

	/** 功能:  断链消息响应
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	HRESULT OnDisConnect( WPARAM wparam, LPARAM lparam );

private:
	bool OnBtnPacket(const IArgs & arg);  //点击导出抓包按钮
	bool OnBtnExport(const IArgs & arg);  //点击抓包按钮

	void BtnStartCapture();  //开始抓包
	void BtnStopCapture();   //点击停止抓包按钮的响应函数
	void StartExportFile();  //开始导出
    void GetFileSize(u32 m_dwCaptureFileSize, s8 *chFileSize); //文件显示大小格式化
	void IsCaptureSuccess(); //是否抓包成功

	void StartCapture();     //ftp和telnet都开启后开始抓包
	void ExportPacket();     //ftp开启后导出抓包

private:
	const String m_strBtnStartPacket; 
	const String m_strBtnCaptureExport;
	const String m_strCaptureTimer;
	const String m_strCaptureFileSize;
	const String m_strExportProgress;

private:
	Window* m_pWnd;
	CTelnetSocket m_cTelnet;  //远程登录服务器

	CFtpCtrl m_cFtp;    //FTP用
	EM_FTPCAPTURETRANS_TYPE m_emFtpTransType;  //导入/导出状态区分
	EmFtpStatus m_emFileFtpStatus;      //当前FTP传输状态
	Value_ProgressPos m_valProgress;    //导出进度
	u32   m_dwTime;    //定时器            
	u32   m_dwCaptureFileSize;  //抓包大小
	u32   m_dwTotalFileSize;    //导出抓包文件大小
	bool  m_bIsCapturing;       //是否正在抓包
	bool  m_bIsExporting;       //是否正在导出
	u8    m_nThreeCount;        //3秒后判断抓包是否成功

	BOOL m_bIsClickBtnPacket;   //是否点击开始抓包
	BOOL m_bIsClickBtnExport;   //是否点击导出抓包
};

#define CNETPACKETLOGIC    CNetPacketLogic::GetSingletonPtr()               //CNetPacketLogic指针

#endif //!defined(AFX_NETPACKETLOGIC_H__FF5413C7_513C_4617_BFF6_B87F5FCE8936__INCLUDED_)