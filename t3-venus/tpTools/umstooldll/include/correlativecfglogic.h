/*****************************************************************************
模块名      : CCorrelativeCfgLogic
文件名      : correlativecfglogic.h
相关文件    : 
文件实现功能: logic相关配置页面
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2012/12/07     1.0         刘德印      创建
******************************************************************************/
#if !defined(AFX_CORRELATIVECFGLOGIC_H__48C10C74_39FD_4237_B8A0_129393B3BBD1__INCLUDED_)
#define AFX_CORRELATIVECFGLOGIC_H__48C10C74_39FD_4237_B8A0_129393B3BBD1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

class CCorrelativeCfgLogic :public CWndLogicBase, public ISingleTon<CCorrelativeCfgLogic>  
{
public:  
    CCorrelativeCfgLogic();
	virtual ~CCorrelativeCfgLogic();

public:  
	virtual bool RegCBFun();
	virtual bool UnRegFunc( );
    virtual bool InitWnd( const IArgs & arg );

	/**	 
	* 功能:  显示或隐藏窗口
	* @return  bool 表示是否该显示
	* @remarks
	*/
	virtual bool ShowWindow( BOOL32 bShow );

   /**	 
	* 功能:  清空所有状态和数据
	* @return   
	* @remarks	 
	*/
    virtual void Clear();

	void InitCfgFuncMenu();			//初始化配置菜单

	/**	 
	* 功能:  切换窗口
	* @return   void
	* Param : [in] strItemName 即将显示窗口名
	*/
	void SwitchConfigTabWnd(CString strItemName);

public:
	bool OnMenuLstItem( const IArgs & arg );

protected: 
	virtual void RegMsg(); 
	virtual void UnRegMsg();

	
private:
	//切换窗口列表控件名
	const String m_strLstCfgFunMenu;

	//当前显示的配置页面
	CString m_strCurPage;
};

#define CORRELATIVECFGLOGICRPTR    CCorrelativeCfgLogic::GetSingletonPtr()               //单板logic指针

#endif // !defined(AFX_CORRELATIVECFGLOGIC_H__48C10C74_39FD_4237_B8A0_129393B3BBD1__INCLUDED_)
