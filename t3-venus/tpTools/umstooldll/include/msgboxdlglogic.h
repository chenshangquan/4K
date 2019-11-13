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

#include "wndLogicBase.h"

typedef LONG MSGBOX_RET;
#define MSGBOX_OK     0
#define MSGBOX_CANCEL -1

class CMsgboxDlgLogic :public CWndLogicBase, public ISingleTon<CMsgboxDlgLogic> 
{
public:  
    CMsgboxDlgLogic();
	virtual ~CMsgboxDlgLogic();

public:  
	
	virtual bool RegCBFun();
	
	virtual bool UnRegFunc( );
	
    virtual bool InitWnd( const IArgs & arg );

   /**	 
	* 功能:  清空所有状态和数据
	* @return   
	* @remarks	 
	*/
    virtual void Clear();

public:
	bool OnBtnOk( const IArgs & arg );
	bool OnBtnCancel( const IArgs & arg );

	void ShowMsgBox( MSGBOX_RET& nResult, const String& strText = ""  );
	void ShowMsgBoxNoBtn( const String& strText = ""  );
	void ShowMsgBoxOk( const String& strText = ""  );
protected: 
	virtual void RegMsg(); 
	virtual void UnRegMsg();
	
private:
	const String m_strStcMsgboxShowText;    

	MSGBOX_RET m_nMsgBoxRet; 

};

#define MSGBOXLOGICRPTR    CMsgboxDlgLogic::GetSingletonPtr()               //msgbox logic指针

#ifndef MSG_BOX
#define MSG_BOX( nResult, strText  ) \
MSGBOXLOGICRPTR->ShowMsgBox( nResult, strText );
#endif

#ifndef MSG_BOX_NOBTN
#define MSG_BOX_NOBTN( strText ) \
MSGBOXLOGICRPTR->ShowMsgBoxNoBtn( strText );
#endif

#ifndef MSG_BOX_OK
#define MSG_BOX_OK( strText ) \
MSGBOXLOGICRPTR->ShowMsgBoxOk( strText );
#endif

#endif // !defined(AFX_MSGBOXDLGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
