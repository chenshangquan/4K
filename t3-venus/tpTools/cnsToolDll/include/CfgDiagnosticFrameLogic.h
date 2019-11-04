// CfgDiagnosticFrameLogic.h: interface for the CCfgDiagnosticFrameLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CFGDIAGNOSTICFRAME_H__246AB085_4508_437B_A9E9_995DBB6F7F4F__INCLUDED_)
#define AFX_CFGDIAGNOSTICFRAME_H__246AB085_4508_437B_A9E9_995DBB6F7F4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

class CCfgDiagnosticFrameLogic  : public CLogicBase, public ISingleTon<CCfgDiagnosticFrameLogic>  
{
public:
	CCfgDiagnosticFrameLogic();
	virtual ~CCfgDiagnosticFrameLogic();
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
	/** 功能:  隐藏所有窗口
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	void HideAllWnd();
private:
	/** 功能:  初始化诊断测试菜单
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	void InitCfgFuncMenu();
	/** 功能:  点击接口诊断按钮的响应事件
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnClickInterfaceDiagnostic( const IArgs& args );
	/** 功能:  点击网络诊断按钮的响应事件
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnClickNetDiagnostic( const IArgs& args );
	/** 功能:  点击网口抓包按钮的响应事件
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnClickNetPacket( const IArgs& args );
	/** 功能:  Table页切换窗口
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	void SwitchCfgTabWnd( string strWnd );
public:
	string m_strCfgCurWnd;//当前显示的窗口
private:
	string m_strLstFunMenu;//功能列表 
};

#endif // !defined(AFX_CFGDIAGNOSTICFRAME_H__246AB085_4508_437B_A9E9_995DBB6F7F4F__INCLUDED_)
