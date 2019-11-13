/*****************************************************************************
模块名      : CVTRCfgLogic
文件名      : vtrcfglogic.h
相关文件    : 
文件实现功能: 网管配置页面
作者        : 石城
版本        : V1.0  Copyright(C) 2013-2014 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/3/4       1.0         石城			创建
******************************************************************************/
#if !defined(UMSTOOL_VTRCFGLOGIC_H)
#define UMSTOOL_VTRCFGLOGIC_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

class CVTRCfgLogic :public CWndLogicBase, public ISingleTon<CVTRCfgLogic>
{
public:
	CVTRCfgLogic();
	virtual ~CVTRCfgLogic();


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
	* 功能:  单击VTRLst某个Item的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnClickVTRLst( const IArgs & arg );

	/**	 
	* 功能:  单击VTRLst空白区域的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnClickVTRLstBlack( const IArgs& args );


protected:
	/**	 
	* 功能:  响应服务器发来的UI_UMSTOOL_ADD_VTR_RSP的函数
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnAddVTRRsp( WPARAM wparam, LPARAM lparam );

	/**	 
	* 功能:  响应服务器发来的UI_UMSTOOL_VTR_NTY的函数
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnVTRNty( WPARAM wparam, LPARAM lparam );

	/**	 
	* 功能:  响应服务器发来的UI_UMSTOOL_MODIFY_VTR_RSP的函数
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnModifyVTRRsp( WPARAM wparam, LPARAM lparam );

	/**	 
	* 功能:  响应服务器发来的UI_UMSTOOL_DEL_VTR_RSP的函数
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnDelVTRRsp( WPARAM wparam, LPARAM lparam );	


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
	const String m_strListVTR;
	const String m_strBtnAdd;
	const String m_strBtnModify;
	const String m_strBtnDel;


	//当前选中的网管服务器信息
	TVcrCfg m_tVTRCfgSel;
};

#define VTRCFGLOGICRPTR    CVTRCfgLogic::GetSingletonPtr()               //VTRCfglogic指针

#endif // !defined(UMSTOOL_VTRCFGLOGIC_H)
