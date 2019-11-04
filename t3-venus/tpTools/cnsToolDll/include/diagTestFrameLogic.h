// diagTestFrameLogic.h: interface for the DiagTestFrameLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIAGTESTFRAMELOGIC_H__D1C4B9F6_49CD_434B_AB12_DE974E184DE6__INCLUDED_)
#define AFX_DIAGTESTFRAMELOGIC_H__D1C4B9F6_49CD_434B_AB12_DE974E184DE6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

class CDiagTestFrameLogic : public CLogicBase, public ISingleTon<CDiagTestFrameLogic>  
{
public:
	CDiagTestFrameLogic();
	virtual ~CDiagTestFrameLogic();
	
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
	/** 功能:  更新输入接口标题
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	HRESULT OnUpdateInportTitle( WPARAM wparam, LPARAM lparam );
private:
	vector<string> m_vecInPortTitle;
};

#endif // !defined(AFX_DIAGTESTFRAMELOGIC_H__D1C4B9F6_49CD_434B_AB12_DE974E184DE6__INCLUDED_)
