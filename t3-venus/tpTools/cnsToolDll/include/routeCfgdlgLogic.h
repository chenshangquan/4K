// routeCfgdlgLogic.h: interface for the routeCfgdlgLogic class.
//路由配置添加对话框
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ROUTECFGDLGLOGIC_H__9353F1F3_BA28_482A_8E01_BFD93BB0A411__INCLUDED_)
#define AFX_ROUTECFGDLGLOGIC_H__9353F1F3_BA28_482A_8E01_BFD93BB0A411__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LogicBase.h"

class CRouteCfgdlgLogic: public CLogicBase, public ISingleTon<CRouteCfgdlgLogic> 
{
public:
	CRouteCfgdlgLogic();
	virtual ~CRouteCfgdlgLogic();

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

protected:
	/**	 
	* 功能:  单击BtnOK控件的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnRouteCfgOk( const IArgs & arg );
	
	/**	 
	* 功能:  单击BtnCancel控件的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnRouteCfgCancel( const IArgs & arg );

	/**	 
	* 功能:  编辑EdtPriorLevel控件的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnEdtPriorLevelChange( const IArgs & arg );
	bool OnEdtPriorLevelKillFocus( const IArgs & arg );

	HRESULT OnRouteAdd( WPARAM wparam, LPARAM lparam );

private:

	vector<CString> m_vecComboPriorLevel;

	const String  m_strEdtPriorLevel;
	const String  m_strIPCtrlDstSubnetIP;
	const String  m_strIPCtrlMastIP;
	const String  m_strIPCtrlGatewayIP;

};

#define ROUTECFGDLGLOGIC    CRouteCfgdlgLogic::GetSingletonPtr()               //NetMngOptlogic指针

#endif // !defined(AFX_ROUTECFGDLGLOGIC_H__9353F1F3_BA28_482A_8E01_BFD93BB0A411__INCLUDED_)
