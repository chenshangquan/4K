// cfgFrameLogic.h: interface for the CCfgFrameLogic class.
 /*****************************************************************************
 模块名      : cnsTool配置框架
 文件名      : cfgFrameLogic.h
 相关文件    : 
 文件实现功能:  
 说明       ： 对应cfgFrame.xml,其中包含配置框架dlg 和 配置菜单
 作者        : 俞锦锦
 版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
 -----------------------------------------------------------------------------
 修改记录:
 日  期         版本        修改人      修改内容
 2012/12/20    1.0          俞锦锦      创建
******************************************************************************/

#if !defined(AFX_CFGFRAMELOGIC_H__00B504BC_6D75_40A9_B8CA_3C1D51B04DCA__INCLUDED_)
#define AFX_CFGFRAMELOGIC_H__00B504BC_6D75_40A9_B8CA_3C1D51B04DCA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

class CCfgFrameLogic : public CLogicBase, public ISingleTon<CCfgFrameLogic>  
{
public:
	CCfgFrameLogic();
	virtual ~CCfgFrameLogic();

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
	/** 功能:  保存配置的按钮
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	HRESULT OnDisConnect( WPARAM wparam, LPARAM lparam);
	/** 功能:  初始化配置菜单
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	void InitCfgFuncMenu();	
	/** 功能:  点击音频接口配置按钮的响应事件
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnClickAudioPortCfg( const IArgs& args );
	/** 功能:  点击均衡器配置按钮的响应事件
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnClickEqCfg( const IArgs& args );
	/** 功能:  点击音频配置按钮的响应事件
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnClickAudioCfg( const IArgs& args );
	/** 功能:  点击主音频配置按钮的响应事件
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnClickMainAudioCfg( const IArgs& args );
	/** 功能:  点击演示源设置按钮的响应事件
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnClickDemonStrationCfg( const IArgs& args );
	/** 功能:  点击图像参数配置按钮的响应事件
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnClickAdjustImageCfg( const IArgs& args );
	/** 功能:  Table页切换窗口
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	void SwitchCfgTabWnd( string strWnd );
private:
    /** 功能:  收到版本通知信息
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	LRESULT OnVerInfoNty( WPARAM wparam, LPARAM lparam);
    /** 功能:  重新初始化配置菜单
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
    void ReInitCfgFuncMenu();
public:
	string m_strCfgCurWnd;//当前显示的窗口
private:
	string m_strLstFunMenu;//功能列表 

};

#endif // !defined(AFX_CFGFRAMELOGIC_H__00B504BC_6D75_40A9_B8CA_3C1D51B04DCA__INCLUDED_)
