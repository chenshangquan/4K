// NetDiagnosticLogic.h: interface for the CNetDiagnosticLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NETDIAGNOSTICLOGIC_H__FF5413C7_513C_4617_BFF6_B87F5FCE8936__INCLUDED_)
#define AFX_NETDIAGNOSTICLOGIC_H__FF5413C7_513C_4617_BFF6_B87F5FCE8936__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

class CNetDiagnosticLogic: public CLogicBase, public ISingleTon<CNetDiagnosticLogic> 
{
public:
	CNetDiagnosticLogic();
	virtual ~CNetDiagnosticLogic();

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
	/** 功能:  收到开会的信息
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	LRESULT OnConfStateNty( WPARAM wparam, LPARAM lparam);
	bool OnBtnStatistic( const IArgs & arg );
	bool OnBtnRefresh( const IArgs & arg );

	HRESULT OnRecordMes( WPARAM wparam, LPARAM lparam );
	void WriteToFile();

private:
	const String m_strLostPacket;					//丢包率
    const String m_strUpstream;						//上行网络速率
    const String m_strDownstream;					//下行网络速率
	CFile		 m_cFile;
	BOOL		 m_bIsRecording;					//在线统计	
};

#endif   // !defined(AFX_NETDIAGNOSTICLOGIC_H__FF5413C7_513C_4617_BFF6_B87F5FCE8936__INCLUDED_)