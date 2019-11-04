// cfgCnsFrame.h: interface for the CcfgCnsFrame class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CFGCNSFRAME_H__246AB085_4508_437B_A9E9_995DBB6F7F4F__INCLUDED_)
#define AFX_CFGCNSFRAME_H__246AB085_4508_437B_A9E9_995DBB6F7F4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

class CCfgCnsFrame  : public CLogicBase, public ISingleTon<CCfgCnsFrame>  
{
public:
	CCfgCnsFrame();
	virtual ~CCfgCnsFrame();
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
	/** 功能:  初始化配置菜单
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	void InitCfgFuncMenu();
	/** 功能:  点击cns配置按钮的响应事件
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnClickCnsCfg( const IArgs& args );
	/** 功能:  点击网络安全配置按钮的响应事件
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnClickNetSecurityMgrCfg( const IArgs& args );
	/** 功能:  点击网管配置按钮的响应事件
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnClickNetMgrCfg( const IArgs& args );
	/** 功能:  点击混音配置按钮的响应事件
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
//	bool OnClickMixCfg( const IArgs& args );
	/** 功能:  点击服务器配置按钮的响应事件
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnClickServerCfg( const IArgs& args );
	/** 功能:  点击呼叫配置按钮的响应事件
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnClickCallSerCfg( const IArgs& args );
	/** 功能:  Table页切换窗口
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	void SwitchCfgTabWnd( string strWnd );
	bool OnClickAdvanceCfg( const IArgs& args );
public:
	string m_strCfgCurWnd;//当前显示的窗口
private:
	string m_strLstFunMenu;//功能列表 
};

#endif // !defined(AFX_CFGCNSFRAME_H__246AB085_4508_437B_A9E9_995DBB6F7F4F__INCLUDED_)
