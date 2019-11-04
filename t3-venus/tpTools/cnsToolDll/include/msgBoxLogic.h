/*****************************************************************************
模块名      : CMsgboxDlgLogic
文件名      : msgboxdlglogic.h
相关文件    : 
文件实现功能: logic Msgbox弹出提示框
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2012/12/07     1.0         刘德印      创建
******************************************************************************/
#if !defined(AFX_MSGBOXDLGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
#define AFX_MSGBOXDLGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LogicBase.h"

typedef LONG MSGBOX_RET;
#define MSGBOX_OK     0
#define MSGBOX_CANCEL 1

class CMsgboxDlgLogic : public CLogicBase, public ISingleTon<CMsgboxDlgLogic> 
{
public:  
    CMsgboxDlgLogic();
	virtual ~CMsgboxDlgLogic();

public:  
	/** 功能:  注册回调函数
	*  @param[in] 
	*  @return 
	*  @remarks  在读取xml文件时候,会调用其中注册的函数
	*/	
	virtual void RegCBFun();
	/** 功能:  反注册回调函数
	*  @param[in] 
	*  @return 
	*  @remarks  与上面函数相反,注销注册的函数
	*/
	virtual void UnRegFunc( );
	/** 功能:  初始化窗口
	*  @param[in] 
	*  @return 
	*  @remarks  在读取xml文件时候调用,根据里面的内容初始化窗口
	*/	
    virtual bool InitWnd( const IArgs & arg );

   /**	 
	* 功能:  清空所有状态和数据
	* @return   
	* @remarks	 
	*/
    virtual void Clear();

public:
	/** 功能:  点击确定的按钮
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnBtnOk( const IArgs & arg );
	/** 功能:  点击取消的按钮
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnBtnCancel( const IArgs & arg );

   /**	 
	* 功能:  窗口弹框(带有确定和取消按钮)
	* @return   
	* @remarks	 
	*/
	void ShowMsgBox( MSGBOX_RET& nResult, const String& strText,const String & StrWindowName = "");
   /**	 
	* 功能:  窗口弹框(无按钮)
	* @return   
	* @remarks	 
	*/
	void ShowMsgBoxNoBtn( const String& strText = ""  );

   /**	 
	* 功能:  窗口弹框(只有确定按钮)
	* @return   
	* @remarks	 
	*/
	void ShowMsgBoxOk( const String& strText ,const String & StrWindowName = "");
	/**	 
	* 功能:  窗口弹框(只读)
	* @return   
	* @remarks	 
	*/
	void ShowMsgBoxOnlyRead( const String& strText = ""  );

protected: 
	/** 功能: 注册消息,接收来自lib库中发送来的消息
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/	
	virtual void RegMsg();
		
	/** 功能: 反注册消息,与上面函数相反,注销注册的消息
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/	
	virtual void UnRegMsg();
	
private:
	const String m_strStcMsgboxShowText;    

	MSGBOX_RET m_nMsgBoxRet; 

};

#ifndef MSG_BOX
#define MSG_BOX( nResult, strText  ) \
CMsgboxDlgLogic::GetSingletonPtr()->ShowMsgBox( nResult, strText );
#endif

#ifndef MSG_BOX_NOBTN
#define MSG_BOX_NOBTN( strText ) \
CMsgboxDlgLogic::GetSingletonPtr()->ShowMsgBoxNoBtn( strText );
#endif

#ifndef MSG_BOX_OK
#define MSG_BOX_OK( strText ) \
CMsgboxDlgLogic::GetSingletonPtr()->ShowMsgBoxOk( strText );
#endif

#ifndef MSG_BOX_ONLY_READ
#define MSG_BOX_ONLY_READ( strText ) \
CMsgboxDlgLogic::GetSingletonPtr()->ShowMsgBoxOnlyRead( strText );
#endif

#ifndef MSG_BOX_SAFE															//当有多层窗口时，需要传入弹框的窗口，否则在非活动窗口时，会导致弹框非模态
#define MSG_BOX_SAFE( nResult, strText ,StrWindowName ) \
CMsgboxDlgLogic::GetSingletonPtr()->ShowMsgBox( nResult, strText , StrWindowName);
#endif

#ifndef MSG_BOX_OK_SAFE
#define MSG_BOX_OK_SAFE( strText ,StrWindowName) \
CMsgboxDlgLogic::GetSingletonPtr()->ShowMsgBoxOk( strText ,StrWindowName);
#endif

#endif // !defined(AFX_MSGBOXDLGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
