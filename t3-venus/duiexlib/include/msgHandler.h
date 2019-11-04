/*****************************************************************************
文件实现功能: 分发处理窗口类消息和lib中业务类消息
文件名      : msgHandler.h 
相关文件    : LogicMap.h
备注		: 通过logicMap最终注册到dlg的paintManager的Notifier队列中，以响应对应的dlg消息 
作者        : 俞锦锦
版本        : V1.0  Copyright(C) 2013-2014 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/4/10      1.0         俞锦锦      创建
******************************************************************************/

#pragma once
namespace DuiLib {

#define MAX_MSG_NAME_LEN      100
#define MAX_CTRL_NAME_LEN  255
 
class CMsgHandler;

typedef LRESULT (CMsgHandler::*BUSI_MSG_HDL_FUNC)(WPARAM , LPARAM);
typedef void (CMsgHandler::*CTRL_MSG_HDL_FUNC)(TNotifyUI& msg);

//UI相关的消息
typedef struct tagCtrlMsg{

	TCHAR	tcCtrlMsgType[MAX_MSG_NAME_LEN];			  //消息号
	TCHAR   tcCtrlName[MAX_CTRL_NAME_LEN];  //控件名
	CTRL_MSG_HDL_FUNC pMsgHdlFun;			  //对应的处理函数指针
} TCtrlMsg,*PTCtrlMsg;


//lib库相关的业务类消息
typedef struct tagBusiMsg{
	unsigned int	uiMsgID; //消息号
	BUSI_MSG_HDL_FUNC pMsgHdlFun; //对应的处理函数指针
}TBusiMsg,*PTBusiMsg;




/*****************************************************************************
模块名      : CMsgHandler 
相关类      : CDUIDialog 、 UI模块中逻辑处理类的父类
模块实现功能: 分发处理窗口类消息和lib中业务类消息
备注        : CDUIDialog对象通过AddNotifier接口把该对象添加到Notifier队列中以响应通知
版本        : V1.0  Copyright(C) 2013-2014 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/4/10      1.0         俞锦锦      创建
******************************************************************************/
class   UILIB_API CMsgHandler: public INotifyUI
{
public:
	//CMsgHandler(void);
	CMsgHandler( /* LPCTSTR  strDlgName = NULL */);
	~CMsgHandler(void);

	virtual void InitWnd();  //by xhx

	//UI类消息分发处理
	virtual void Notify(TNotifyUI& msg);

	virtual LPCTSTR GetClassName() = 0;

	//业务类消息分发处理
	void  BusiMsgNotify( UINT uiMsgID, WPARAM wparam, LPARAM lparam );

protected:

	//UI类消息映射队列
	virtual const TCtrlMsg* GetCtrlMessageMap() const;

	//业务类消息映射队列
	virtual const TBusiMsg* GetBusiMessageMap() const;
private:
  //static	const TCtrlMsg m_ctlMsgMap[]; //控件类消息映射队列
  //static	const TBusiMsg m_busiMsgMap[];//业务类消息映射队列
  
   /*CStdString  m_strDlgName;*/
	/*CDUIDialog  *m_pRoot;  */   
};


//定义
#define DECLARE_MSG_MAP() \
	private: \
	static const TCtrlMsg m_ctlMsgMap[]; \
	static const TBusiMsg m_busiMsgMap[]; \
	protected: \
	virtual const TCtrlMsg* GetCtrlMessageMap() const; \
	virtual const TBusiMsg* GetBusiMessageMap() const; \

 

// UI消息数组初始化 同 END_CONTROL_MSG_MAP配套使用 
#define BEGIN_CONTROL_MSG_MAP(theClass) \
	const TCtrlMsg* theClass::GetCtrlMessageMap() const \
	{ \
		return m_ctlMsgMap; \
	} \
	const TCtrlMsg theClass::m_ctlMsgMap[] = \
	{ \

//UI消息在此建立映射声明
//CTRL_MSG()
//UI消息建立映射声明结束	
#define END_CONTROL_MSG_MAP() \
	{ \
		_T(""), _T(""), NULL } \
	}; \
 
#define CTRL_MSG(tcCtrlMsgType, tcCtrlName, handlerFunc) \
	{ tcCtrlMsgType,tcCtrlName,(CTRL_MSG_HDL_FUNC)(void (CMsgHandler::*)(TNotifyUI&))&handlerFunc },







// 业务类消息数组初始化 同 END_BUSINESS_MSG_MAP配套使用  
#define BEGIN_BUSINESS_MSG_MAP(theClass) \
	const TBusiMsg* theClass::GetBusiMessageMap() const \
	{ \
		return m_busiMsgMap; \
	} \
	const TBusiMsg theClass::m_busiMsgMap[] = \
   { \

//业务类消息在此建立映射声明
//BUSI_MSG()
//业务类消息建立映射声明结束
#define END_BUSINESS_MSG_MAP() \
	{ \
		0, NULL } \
	};

#define BUSI_MSG( uiMsgID, handlerFunc) \
	{ uiMsgID,(BUSI_MSG_HDL_FUNC)(HRESULT (CMsgHandler::*)(WPARAM,LPARAM))&handlerFunc },








}