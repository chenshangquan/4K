/*****************************************************************************
模块名      : CBackupCfgLogic
文件名      : backupcfglogic.h
相关文件    : 
文件实现功能: 1+1备份配置页面
作者        : 徐华秀
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/7/29      1.0         徐华秀		创建
******************************************************************************/
#if !defined(AFX_BACKUPCFGLOGIC_H__5F7CF890_69C3_4BC3_A76E_382BB893ADED__INCLUDED_)
#define AFX_BACKUPCFGLOGIC_H__5F7CF890_69C3_4BC3_A76E_382BB893ADED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

class CBackupCfgLogic : public CWndLogicBase, public ISingleTon<CBackupCfgLogic>  
{
public:
	CBackupCfgLogic();
	virtual ~CBackupCfgLogic();

public:  
	/**	 
	* 功能:  注册该logic中所有的回调函数
	* @return  void
	* @remarks	在此注册的回调函数主要是控件的响应事件，多为成员回调函数,也可注册其他的回调函数
	                    注册时，应注意回调函数对应名子的命名规则：“类名::函数名”
	*/
	virtual bool RegCBFun();

	/**	 
	* 功能:  注册要处理的消息
	* @return  void
	* @remarks	 注册后该消息才能发送到本逻辑模块，否则，接收不到该消息
	*/
	virtual void RegMsg(); 

	/**	 
	* 功能:  注销回调函数
	* @return  void
	* @remarks	 
	*/
	virtual bool UnRegFunc( );

	/**	 
	* 功能:  注销要处理的消息
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
	* 功能:  清空所有状态和数据
	* @return   
	* @remarks	 
	*/
    virtual void Clear();

	/**	 
	* 功能: 初始化界面数据
	* @return   void
	* @remarks  
	*/
	virtual void InitLogicData();
	
protected: 
	/**	 
	* 功能: 点击做为主用机
	* @return   bool
	* @remarks  
	*/
	bool OnBtnRadioIsAsHost( const IArgs & arg );

	/**	 
	* 功能: 点击做为备用机
	* @return   bool
	* @remarks  
	*/
	bool OnBtnRadioIsAsBackup( const IArgs & arg );

	/**	 
	* 功能: 点击设置断链检测间隔时间
	* @return   bool
	* @remarks  
	*/
	bool OnBtnRadioTime( const IArgs & arg );

	/**	 
	* 功能: 点击设置断链检测次数
	* @return   bool
	* @remarks  
	*/
	bool OnBtnRadioCount( const IArgs & arg );

	/**	 
	* 功能: 是否开启1+1备份功能
	* @return   bool
	* @remarks  
	*/
	bool OnBtnSwitchBackupClick( const IArgs & arg );

private:
// 	u8 m_abyBackupInfo[4];                 //记录选择的radiobtn的状态
// 	u8 m_abyOldBackupInfo[4];              //记录原radiobtn的状态

	//该逻辑单元对应的所有控件名  
	const String m_strDlgAsHost;           //做为主用机对话框
	const String m_strDlgAsBackup;         //做为备用机对话框
	const String m_strBtnRadioAsHost;      //做为主用机
	const String m_strBtnRadioAsBackup;    //做为备用机
	const String m_strBtnRadioTime1;       //断链检测间隔时间 1秒
	const String m_strBtnRadioTime2;       //断链检测间隔时间 2秒
	const String m_strBtnRadioTime3;       //断链检测间隔时间 3秒
	const String m_strBtnRadioCount1;      //断链检测次数 1次
	const String m_strBtnRadioCount2;      //断链检测次数 2次
	const String m_strBtnRadioCount3;      //断链检测次数 3次
	const String m_strIPBackupIP;          //备用机IP地址
};

#define BACKUPCFGLOGICRPTR    CBackupCfgLogic::GetSingletonPtr()           //BackupCfgLogic指针

#endif // !defined(AFX_BACKUPCFGLOGIC_H__5F7CF890_69C3_4BC3_A76E_382BB893ADED__INCLUDED_)
