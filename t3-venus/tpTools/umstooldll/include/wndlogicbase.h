/*****************************************************************************
模块名      : CWndLogicBase
文件名      : wndlogicbase.h
相关文件    : 
文件实现功能: umstool逻辑基类
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2012/10/30     1.0         刘德印      创建
******************************************************************************/
#if !defined(AFX_WNDLOGICBASE_H__F3320A42_A78A_40B7_9B1F_A0FD13BDB0C0__INCLUDED_)
#define AFX_WNDLOGICBASE_H__F3320A42_A78A_40B7_9B1F_A0FD13BDB0C0__INCLUDED_

#pragma warning (disable: 4503)

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CWndLogicBase  
{
public: 
   
	/**	 
	* 功能:  初始化
	* @return   
	* @remarks	 
	*/
	void InitLogic()
	{
        
		RegCBFun();
        RegMsg();
	};


    /**	 
	* 功能:  清空所有状态和数据
	* @return   
	* @remarks	 
	*/
    virtual void Clear() = 0;
    

	/**	 
	* 功能:  注册该logic中所有的回调函数
	* @return  void
	* @remarks	在此注册的回调函数主要是控件的响应事件，多为成员回调函数,也可注册其他的回调函数
	                    注册时，应注意回调函数对应名子的命名规则：“类名::函数名”
	*/
	virtual bool RegCBFun(){ return true; }

	 /**	 
	* 功能:  注销某回调函数
	* @return  void
	* @remarks	 
	*/
	 virtual bool UnRegFunc(){ return true;}

	/**	 
	* 功能:  初始化窗口数据,
	* @return  void
	* @remarks	由于该功能被归属到控件属性并在xml中与控件绑定，
	                    需要在RegCBFun（）中注册到回调函数管理模块 
	*/
	 virtual bool InitWnd(  const IArgs  & arg ) { 
		 Args_WindowTree argTree =* dynamic_cast< Args_WindowTree *>( const_cast<IArgs*>( &arg ));
		 m_pWndTree = argTree.m_piTree; 
		 return true;
	 }

     //显示窗口时有的状态需要初始化,此处应为纯虚函数，每个logic都应强制实现，外部显示对应界面时统一调用此处的showwindow
     virtual bool ShowWindow( BOOL32 bShow ){ return true; } 
    
     IWndTree * GetWndTree(){ return m_pWndTree; }


    /**	 
	* 功能:  初始化管理注销登陆后界面初始化
	* @return   
	* @remarks	 
	*/
	 virtual void InitLogicData(){ return;}

protected:
   
   /**	 
	* 功能:  注册要处理的消息
	* @return  void
	* @remarks	 注册后该消息才能发送到本逻辑模块，否则，接收不到该消息
	*/
    virtual void RegMsg(){};

	virtual void UnRegMsg(){};
  
public:
	CWndLogicBase()
    {   
        m_pWndTree = NULL;
	  	RegMsg();  
	}
	
	virtual ~CWndLogicBase(){}

protected:
	IWndTree * m_pWndTree; 

};

#endif // !defined(AFX_WNDLOGICBASE_H__F3320A42_A78A_40B7_9B1F_A0FD13BDB0C0__INCLUDED_)
