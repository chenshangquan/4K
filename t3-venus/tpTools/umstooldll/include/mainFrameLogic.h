/*****************************************************************************
模块名      : CMainFrameLogic
文件名      : mainFrameLogic.h
相关文件    : 
文件实现功能: logic主界面
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2012/12/04     1.0         刘德印      创建
******************************************************************************/
#if !defined(AFX_MAINWNDLOGIC_H__336C3B31_4484_4F36_9B80_1BA09DB004FA__INCLUDED_)
#define AFX_MAINWNDLOGIC_H__336C3B31_4484_4F36_9B80_1BA09DB004FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

class CMainFrameLogic :public CWndLogicBase, public ISingleTon<CMainFrameLogic> 
{
public:   
     CMainFrameLogic();
	 virtual ~CMainFrameLogic();  

public:  
	virtual bool RegCBFun();
	virtual bool UnRegFunc( );
    virtual bool InitWnd( const IArgs & arg );
   
	/**	 
	* 功能:  清空所有状态和数据
	* @return   
	* @remarks	 
	*/
    virtual void Clear() ;

protected:
	/**	 
	* 功能: 弹出下载日志
	* @return   bool
	* @remarks  
	*/
	bool OnBtnDownloadLog( const IArgs & arg );

	/**	 
	* 功能: 重启服务器
	* @return   bool
	* @remarks  
	*/
	bool OnBtnRebootUms( const IArgs & arg );

	/**	 
	* 功能: 注销登录
	* @return   bool
	* @remarks  
	*/
	bool OnBtnLogoff( const IArgs & arg );

	/**	 
	* 功能: 最小化
	* @return   bool
	* @remarks  
	*/
	bool OnBtnMinimize( const IArgs & arg );

	/**	 
	* 功能: 关闭
	* @return   bool
	* @remarks  
	*/
	bool OnBtnClose( const IArgs & arg );

	/**	 
	* 功能: 相应tab页列表点击
	* @return   bool
	* @remarks  
	*/
	bool OnMenuLstItem( const IArgs & arg );

	/**	 
	* 功能: 初始化功能列表页面
	* @return   bool
	* @remarks  
	*/
	void InitFunMenu();
	

protected:
	virtual void RegMsg(); 
	virtual void UnRegMsg();

	/**	 
	* 功能: 登陆回应
	* @return   bool
	* @remarks  
	*/
	HRESULT OnLoginRsp( WPARAM wparam, LPARAM lparam);

	/**	 
	* 功能: 登陆超时
	* @return   bool
	* @remarks  
	*/
	HRESULT OnLoginTimeOut( WPARAM wparam, LPARAM lparam);

private:
   void  CreateWnd();

  	/**	 
	* 功能: 切换功能页面
	* @return   bool
	* @remarks  
	*/
	void SwitchTabWnd(CString strItemName);

private:
	Window* m_pWndMain;
	const String m_strDlgMain;
	const String m_strLstFunMenu;
	const String m_strStcUmsIP;

	//当前正在显示的页面
	CString m_strCurPage;
};

#define MAINFRMLOGICRPTR    CMainFrameLogic::GetSingletonPtr()               //主logic指针

#endif // !defined(AFX_MAINWNDLOGIC_H__336C3B31_4484_4F36_9B80_1BA09DB004FA__INCLUDED_)
