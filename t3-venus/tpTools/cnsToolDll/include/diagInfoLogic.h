// diagInfoLogic.h: interface for the CDiagInfoLogic class.
 /*****************************************************************************
 模块名      : CDiagInfoLogic
 文件名      : diagInfoLogic.h
 相关文件    : 
 文件实现功能: 诊断信息界面
 作者        : 景洋洋
 版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
 -----------------------------------------------------------------------------
 修改记录:
 日  期         版本        修改人      修改内容
 2013/01/07     1.0         景洋洋        创建
******************************************************************************/

#if !defined(AFX_DIAGINFOLOGIC_H__FF5413C7_513C_4617_BFF6_B87F5FCE8936__INCLUDED_)
#define AFX_DIAGINFOLOGIC_H__FF5413C7_513C_4617_BFF6_B87F5FCE8936__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

class CDiagInfoLogic : public CLogicBase, public ISingleTon<CDiagInfoLogic>   
{
public:
	CDiagInfoLogic();
	virtual ~CDiagInfoLogic();
	
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

private:
	/** 功能:  收到上下行速率的消息响应
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	LRESULT OnUpDownstreamNty( WPARAM wparam, LPARAM lparam);
	/** 功能:  收到丢包消息的回复
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	LRESULT OnLostPacketRsp( WPARAM wparam, LPARAM lparam);
	/** 功能:  收到卡农麦克风的消息提醒
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	LRESULT OnUpdateAudioNty( WPARAM wparam, LPARAM lparam);
	/** 功能:  演示源输入接口信息 
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	LRESULT OnVgaInfoNotify( WPARAM wparam, LPARAM lparam);
	/** 功能:  演示源输出接口信息
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	LRESULT OnVgaOutInfoNotify( WPARAM wparam, LPARAM lparam);
	/** 功能:  点击诊断测试的按钮
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnBtnDiagTest( const IArgs & arg );
				
	/** 功能:  更新Group1中COMMON
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	String UpdateGroup1( TTpAudioPortInfo& tAudioPortInfo );
					
	/** 功能:  更新Group2中COMMON
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	String UpdateGroup2( TTpAudioPortInfo& tAudioPortInfo );
						
	/** 功能:  更新Group3中COMMON
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	String UpdateGroup3( TTpAudioPortInfo& tAudioPortInfo );
					
	/** 功能:  根据服务器接收默认音频设置的反馈消息并更新界面
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	HRESULT OnDefaultAudioNty( WPARAM wparam, LPARAM lparam );
			
	/** 功能:  收到开会的信息
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	LRESULT OnConfStateNty( WPARAM wparam, LPARAM lparam);
	/** 功能:  更新主视频接口信息
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	HRESULT OnUpdateMainAudioNty( WPARAM wparam, LPARAM lparam );

	bool OnBtnStatistic( const IArgs & arg );

	HRESULT OnRecordMes( WPARAM wparam, LPARAM lparam );
	void WriteToFile();

	HRESULT OnUpdateMainAudioInfo( WPARAM wparam, LPARAM lparam );
private:
	TDualSrcInfo m_tDualSrcInfo;					//演示源输入接口信息
	TTPVgaMixInfo m_tVgaMixInfo;					//演示源输出接口信息
	const String m_strLostPacket;					//丢包率
    const String m_strUpstream;						//上行网络速率
    const String m_strDownstream;					//下行网络速率
	const String m_strComboboxInPort;				//演示源输入接口
	const String m_strComboboxOutPort;				//演示源输出接口
    const String m_strInAdPort1;					//COMMON1
	const String m_strInAdPort2;					//COMMON2
	const String m_strInAdPort3;					//COMMON3
	CFile		 m_cFile;
	BOOL		 m_bIsRecording;					//在线统计		
};
		
#endif // !defined(AFX_DIAGINFOLOGIC_H__FF5413C7_513C_4617_BFF6_B87F5FCE8936__INCLUDED_)
