/*****************************************************************************
模块名      : CCfgNetMngLogic
文件名      : cfgnetmngLogic.h
相关文件    : 
文件实现功能: 网管配置页面
作者        : 石城
版本        : V1.0  Copyright(C) 2013-2014 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/1/17      1.0         石城			创建
******************************************************************************/
#if !defined(AFX_CFGNETMNGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
#define AFX_CFGNETMNGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

#define MIN_NMSERVER_NO		0
#define MAX_NMSERVER_NO		1

class CCfgNetMngLogic : public CLogicBase, public ISingleTon<CCfgNetMngLogic>
{
public:
	CCfgNetMngLogic();
	virtual ~CCfgNetMngLogic();


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
	* 功能:  清空所有状态和数据
	* @return   
	* @remarks	 
	*/
    virtual void Clear();

protected:
	/**	 
	* 功能:  单击BtnAdd的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnClickBtnAdd( const IArgs& args );

	/**	 
	* 功能:  单击BtnModify的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnClickBtnModify( const IArgs& args );

	/**	 
	* 功能:  单击BtnDel的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnClickBtnDelete( const IArgs& args );


	/**	 
	* 功能:  单击NetMngLst某个Item的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnClickNetMngLst( const IArgs & arg );

	/**	 
	* 功能:  单击NetMngLst空白区域的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnClickNetMngLstBlack( const IArgs& args );


protected:
	/**	 
	* 功能:  响应服务器发来的UI_UMSTOOL_ADD_NETMNG_RSP的函数
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnAddNetMngRsp( WPARAM wparam, LPARAM lparam );

	/**	 
	* 功能:  响应服务器发来的UI_UMSTOOL_NETMNG_NTY的函数
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnNetMngNty( WPARAM wparam, LPARAM lparam );

	/**	 
	* 功能:  响应服务器发来的UI_UMSTOOL_MODIFY_NETMNG_RSP的函数
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnModifyNetMngRsp( WPARAM wparam, LPARAM lparam );

	/**	 
	* 功能:  响应服务器发来的UI_UMSTOOL_DEL_NETMNG_RSP的函数
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnDelNetMngRsp( WPARAM wparam, LPARAM lparam );	


private:
	/**	 
	* 功能:  重置所有控件
	* @return   void
	* @remarks	 
	*/
	void ResetAllCtrl();

	/**	 
	* 功能:  重置所有数据
	* @return   void
	* @remarks	 
	*/
	void ResetAllData();

	/**	 
	* 功能:  更新Btn状态
	* @return   void
	* @remarks	 
	*/
	void UpdateBtnState();

private:
	//该逻辑单元对应的所有控件名
	const String m_strListNetMng;
	const String m_strBtnAdd;
	const String m_strBtnModify;
	const String m_strBtnDel;


	//当前选中的网管服务器信息
	TTPNMServerCfg m_tTPNMServerCfgSel;
};

#define CFGNETMNGLOGICRPTR    CCfgNetMngLogic::GetSingletonPtr()               //CfgNetMnglogic指针

#endif // !defined(AFX_CFGNETMNGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
