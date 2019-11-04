/*****************************************************************************
模块名      : CWarningLogic
文件名      : warninglogic.h
相关文件    : 
文件实现功能: logic消息提示页面
作者        : 石城
版本        : V1.0  Copyright(C) 2013-2014 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/7/25      1.0         景洋洋        修改
******************************************************************************/
// waringLogic.h: interface for the CWaringLogic class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_WARINGLOGIC_H__0E1B060C_E01E_4259_AB45_C70CD0D12ED0__INCLUDED_)
#define AFX_WARINGLOGIC_H__0E1B060C_E01E_4259_AB45_C70CD0D12ED0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

class CWarningLogic : public CLogicBase, public ISingleTon<CWarningLogic>  
{
public:
	CWarningLogic();
	virtual ~CWarningLogic();

public:  
	/**	 
	* 功能:  注册该logic中所有的回调函数
	* @return  void
	* @remarks	在此注册的回调函数主要是控件的响应事件，多为成员回调函数,也可注册其他的回调函数
	                    注册时，应注意回调函数对应名子的命名规则：“类名::函数名”
	*/
	virtual void RegCBFun();

	/**	 
	* 功能:  注册要处理的消息
	* @return  void
	* @remarks	 注册后该消息才能发送到本逻辑模块，否则，接收不到该消息
	*/
	virtual void RegMsg(); 

	/**	 
	* 功能:  注销某回调函数
	* @return  void
	* @remarks	 
	*/
	virtual void UnRegFunc( );

	/**	 
	* 功能:  注销某回调函数
	* @return  void
	* @remarks	 
	*/
	virtual void UnRegMsg();
	
	/**	 
	* 功能:  初始化窗口数据,
	* @return  void
	* @remarks	由于该功能被归属到控件属性并在xml中与控件绑定，
	                    需要在RegCBFun（）中注册到回调函数管理模块 
	*/
    virtual bool InitWnd( const IArgs & arg );

   /**	 
	* 功能:  断链时清空所有状态和数据
	* @return   
	* @remarks	 
	*/
    virtual void Clear();

	void MessageBoxWnd( const CString& strWaringText);

protected:
	/**	 
	* 功能: 点击提示消息向上按钮
	* @return   bool
	* @remarks  
	*/
	bool OnBtnWarningPre( const IArgs & arg );

	/**	 
	* 功能: 点击提示消息向下按钮
	* @return   bool
	* @remarks  
	*/
	bool OnBtnWarningNext( const IArgs & arg );
	
private:
	//更新显示信息
	void UpdateItem();

	//更新按钮状态
	void UpdateBtn();

	/*
	**函数功能：消息提示页面改变
	**传入参数：BOOL 表示是否向上
	*/
	void WarningChage( BOOL bPre );	

private:
	//该逻辑单元对应的所有控件名
	const String  m_stcWarning;
	const String  m_btnWarningPre;
	const String  m_btnWarningNext;

	std::vector<CString> m_vecWarning;			//提示消息
	int m_nIndex;								//当前显示提示消息的索引
	std::vector<BOOL> m_vecIsShow;				//提示消息是否已经显示过
};

#define WARNINGLOGICRPTR    CWarningLogic::GetSingletonPtr()               //WarningLogic指针

//系统消息警告
#define WARNMESSAGE(p){ WARNINGLOGICRPTR->MessageBoxWnd(p ); }

#endif // !defined(AFX_WARINGLOGIC_H__0E1B060C_E01E_4259_AB45_C70CD0D12ED0__INCLUDED_)
