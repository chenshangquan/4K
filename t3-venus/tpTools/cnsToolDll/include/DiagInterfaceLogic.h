// DiagInterfaceLogic.h: interface for the CDiagInterfaceLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIAGINTERFACELOGIC_H__FF5413C7_513C_4617_BFF6_B87F5FCE8936__INCLUDED_)
#define AFX_DIAGINTERFACELOGIC_H__FF5413C7_513C_4617_BFF6_B87F5FCE8936__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

class CDiagInterfaceLogic: public CLogicBase, public ISingleTon<CDiagInterfaceLogic> 
{
public:
	CDiagInterfaceLogic();
	virtual ~CDiagInterfaceLogic();

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

	HRESULT OnUpdateMainAudioInfo( WPARAM wparam, LPARAM lparam );
	
private:
	TDualSrcInfo m_tDualSrcInfo;					//演示源输入接口信息
	TTPVgaMixInfo m_tVgaMixInfo;					//演示源输出接口信息
	const String m_strComboboxInPort;				//演示源输入接口
	const String m_strComboboxOutPort;				//演示源输出接口
    const String m_strInAdPort1;					//COMMON1
	const String m_strInAdPort2;					//COMMON2
	const String m_strInAdPort3;					//COMMON3

};

#endif // !defined(AFX_DIAGINTERFACELOGIC_H__FF5413C7_513C_4617_BFF6_B87F5FCE8936__INCLUDED_)