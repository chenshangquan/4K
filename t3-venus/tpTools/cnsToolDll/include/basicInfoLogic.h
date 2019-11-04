// BasicInfoLogic.h: interface for the CBasicInfoLogic class.
/*****************************************************************************
模块名      : CBasicInfoLogic
文件名      : BasicInfoLogic.h
相关文件    : 
文件实现功能: 基本信息界面
作者        : 景洋洋
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/01/04     1.0         景洋洋      创建
******************************************************************************/

#if !defined(AFX_BASICINFOLOGIC_H__3C7B10DF_6193_494D_BAD6_6822AB12AA2C__INCLUDED_)
#define AFX_BASICINFOLOGIC_H__3C7B10DF_6193_494D_BAD6_6822AB12AA2C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

class CBasicInfoLogic : public CLogicBase, public ISingleTon<CBasicInfoLogic>
{
public:
	CBasicInfoLogic();
	virtual ~CBasicInfoLogic();

//CLogicBase
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
	virtual void UnRegFunc( );
	
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
    virtual void Clear() ;
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

	/** 功能:  接收服务器的会场信息并更新界面
	*  @param[in] 
	*  @return 成功返回true,失败返回false
	*  @remarks 
	*/
	HRESULT OnCnsInfoNty( WPARAM wparam, LPARAM lparam);

	/** 功能:  接收服务器的会议信息并更新界面
	*  @param[in] 
	*  @return 成功返回true,失败返回false
	*  @remarks 
	*/
	HRESULT OnConfInfoNty( WPARAM wparam, LPARAM lparam);

	/** 功能:  接收服务器的会议状态并更新界面（会议名称更新）
	*  @param[in] 
	*  @return 成功返回true,失败返回false
	*  @remarks 
	*/
	HRESULT OnConfStateNty( WPARAM wparam, LPARAM lparam);

	/** 功能:  接收服务器端发过来的云服务器是否设置成功的回复
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	HRESULT OnSetCloudServerInfoInd( WPARAM wParam, LPARAM lParam );
	
	/** 功能:  接收服务器关于TPad的IP信息并更新界面
	*  @param[in] 
	*  @return 成功返回true,失败返回false
	*  @remarks 
	*/
	HRESULT OnTPadIPNty( WPARAM wparam, LPARAM lparam);
	
	/** 功能:  接收服务器的会场注册SIP信息并更新界面
	*  @param[in] 
	*  @return 成功返回true,失败返回false
	*  @remarks 
	*/
	HRESULT OnRegSipNty( WPARAM wparam, LPARAM lparam);
	
	/** 功能:  接收服务器的会场注册GK信息并更新界面
	*  @param[in] 
	*  @return 成功返回true,失败返回false
	*  @remarks 
	*/
	HRESULT OnRegGkNty( WPARAM wparam, LPARAM lparam);
	
	/** 功能:  接收服务器的会场注册NAT信息并更新界面
	*  @param[in] 
	*  @return 成功返回true,失败返回false
	*  @remarks 
	*/
	HRESULT OnRegNATNty( WPARAM wparam, LPARAM lparam);
	
	/** 功能:  接收服务器关于CPU和RAM的信息并更新界面
	*  @param[in] 
	*  @return 成功返回true,失败返回false
	*  @remarks 
	*/
	HRESULT OnCPURAMNty( WPARAM wparam, LPARAM lparam);	
	
	/** 功能:  根据注册GK的回复消息改变界面
	*  @param[in] 
	*  @return 成功返回true,失败返回false
	*  @remarks 
	*/
	HRESULT OnChangeGk( WPARAM wparam, LPARAM lparam);	
	
	/** 功能:  根据注册SIP的回复消息改变界面
	*  @param[in] 
	*  @return 成功返回true,失败返回false
	*  @remarks 
	*/
	HRESULT OnChangeSip( WPARAM wparam, LPARAM lparam);	

	HRESULT OnVerInfoNty( WPARAM wparam, LPARAM lparam );

private:
	/** 功能:  向服务器请求数据并更新界面
	*  @param[in] IArgs  点击操作
	*  @return 成功返回true,失败返回false
	*  @remarks 
	*/
	bool OnBtnRefresh( const IArgs& args );
private:
	const String m_strStcSName;							//会场名称
	const String m_strStcIPS;							//会场IP
	const String m_strStcSE164Num;						//会场E164
	const String m_strStcScrSNum;						//屏数
	const String m_strStcSDaul;							//双流源
	const String m_strStcSSIP;							//注册网呈服务器
	const String m_strStcCloudIP;						//云服务器
	const String m_strStcSGK;							//注册GK
	const String m_strStcSNAT;							//静态NAT地址
	const String m_strStcSCPU;							//CPU使用率
	const String m_strStcSRam;							//内存使用率
	const String m_strStcConfSName;						//会议名称
	const String m_strStcConfSRate;						//单屏码率
	const String m_strStcShowSRate;						//演示码率
	const String m_strStcAudioSRate;					//音频格式
	const String m_strStcConfSHold;						//会议能力
	const String m_strStcConfSCallType;					//会议呼叫类型
	const String m_strStcEncryptKey;					//是否加密
};

#endif // !defined(AFX_BASICINFOLOGIC_H__3C7B10DF_6193_494D_BAD6_6822AB12AA2C__INCLUDED_)
