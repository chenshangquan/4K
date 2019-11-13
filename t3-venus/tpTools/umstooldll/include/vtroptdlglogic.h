/*****************************************************************************
模块名      : CVTROptDlgLogic
文件名      : vtroptdlglogic.h
相关文件    : 
文件实现功能: logic录像机添加修改页面
作者        : 石城
版本        : V1.0  Copyright(C) 2013-2014 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/3/4       1.0         石城        创建
******************************************************************************/
#if !defined(UMSTOOL_VTROPTDLGLOGIC_H)
#define UMSTOOL_VTROPTDLGLOGIC_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

#define UMSTOOL_MAX_VTR_NAME_LENTH	32

class CVTROptDlgLogic :public CWndLogicBase, public ISingleTon<CVTROptDlgLogic>
{
public:
    CVTROptDlgLogic();
	virtual ~CVTROptDlgLogic();

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
	* 功能:  注销某回调函数
	* @return  void
	* @remarks	 
	*/
	virtual bool UnRegFunc( );

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

protected:
	/**	 
	* 功能:  响应UI_UMSTOOL_MSG_NETMNGSELDATA_Click的函数
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnSelData( WPARAM wparam, LPARAM lparam );	
	
	

protected:
	/**	 
	* 功能:  单击BtnOK控件的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnOk( const IArgs & arg );
	
	/**	 
	* 功能:  单击BtnCancel控件的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnCancel( const IArgs & arg );
	
private:
	/**	 
	* 功能:  清空所有控件
	* @return   void
	* @remarks	 
	*/
	void ClearAllCtrl();

	/**	 
	* 功能:  将tTPNMServerCfg的值设置到所有控件
	* @return   void
	* @remarks	 
	*/
	void SetAllCtrl( TVcrCfg &tVTRCfg );

	/**	 
	* 功能:  将所有控件的值读取到tTPNMServerCfg
	* @return   bool : 表示读取值是否有错误
	* @remarks	 
	*/
	bool GetAllCtrl( TVcrCfg &tVTRCfg );

private:
	//该逻辑单元对应的所有控件名
	const String  m_strEdtVTRName;
	const String  m_strEdtVTRNo;
	const String  m_strIPCtrlVTRIP;


	//操作类型
	EM_NETMNGOPT_TYPE m_emNMType;

	//修改前的录像机信息
	TVcrCfg m_tVTRCfgOld;
};

#define VTROPTLOGICRPTR    CVTROptDlgLogic::GetSingletonPtr()               //NetMngOptlogic指针

#endif // !defined(UMSTOOL_VTROPTDLGLOGIC_H)
