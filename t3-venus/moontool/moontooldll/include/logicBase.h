   
/*****************************************************************************
模块名      : 窗口的逻辑处理基类
文件名      : CLogicBase.h
相关文件    : 所有窗口的逻辑处理模块都应继承该类
文件实现功能: 窗口的逻辑管理
作者        : 俞锦锦
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2012/11/23     1.0         俞锦锦      创建
******************************************************************************/

#if !defined(AFX_LOGICBASE_H__A66AA693_6ED0_4B3C_977E_1EC92248A074__INCLUDED_)
#define AFX_LOGICBASE_H__A66AA693_6ED0_4B3C_977E_1EC92248A074__INCLUDED_ 

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning (disable: 4503)

#include "uifactorylib.h" 
#include "templateClass.h" 

class CLogicBase//: public Singleton<CLogicBase>
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
	virtual void RegCBFun(){  }

   /**	 
	* 功能:  注销某回调函数
	* @return  void
	* @remarks	 
	*/
//	virtual void UnRegFunc( u32 dwMsgID ); 


	 /**	 
	* 功能:  注销某回调函数
	* @return  void
	* @remarks	 
	*/
	virtual void UnRegFunc(){  }

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
     
	 
	 bool IsAllE164Number( String strText );
	 
	 bool IsValidTPStr( String strText );
    
    
     IWndTree * GetWndTree(){ return m_pWndTree; }

protected:
   
   /**	 
	* 功能:  注册要处理的消息
	* @return  void
	* @remarks	 注册后该消息才能发送到本逻辑模块，否则，接收不到该消息
	*/
    virtual void RegMsg(){};

	virtual void UnRegMsg(){};
															
	/** 功能: 检查数据后更新m_vctWndName中数量 
	*  @param[in] strCtrlName  控件名称
					bChange    控件中的数据是否变化
	*  @return 
	*  @remarks   控件中数据变化,查找m_vctWndName中是否有该控件的名字
				  数据改变,m_vctWndName不存在则添加进去.数据没变,m_vctWndName存在则删除
	*/	
	void CheckData( String strCtrlName, bool bChange );
	
	/** 功能:  在m_vctWndName中查找数据变化控件的名字	
	*  @param[in] 
	*  @return 
	*  @remarks   true 表示m_vctWndName已存有该控件的名字
				  false 表示m_vctWndName没有该控件的名字
	*/	
	bool FindCtrlName( String strWindow );	
												
	/** 功能:  删除m_vctWndName中数据没有变化的控件名字
	*  @param[in] strWndName  控件名字
	*  @return 
	*  @remarks   
	*/	
	void DelVctWndName( String strWindow );
										
	/** 功能:  根据m_vctWndName中的数量确定右下角的保存取消按钮是否可用
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool UpBtnState();
					  
public:
	CLogicBase()
    {   
        m_pWndTree = NULL;
	  	RegMsg();  
	}
	
	virtual ~CLogicBase(){
		UnRegFunc(); 
	}

protected:
	IWndTree * m_pWndTree; 
    vector<String> m_vctWndName;			//存储界面控件名字 
	static String m_strCurWnd;				//当前显示的窗口 
};



#endif // !defined(AFX_WNDLOGIC_H__A66AA693_6ED0_4B3C_977E_1EC92248A074__INCLUDED_)
