// cfgNetSecurityLogic.h: interface for the cfgNetSecurityLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CFGNETSECURITYLOGIC_H__21896890_9A54_4DE8_96AE_063C6281D3FA__INCLUDED_)
#define AFX_CFGNETSECURITYLOGIC_H__21896890_9A54_4DE8_96AE_063C6281D3FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

class CCfgNetSecurityLogic : public CLogicBase, public ISingleTon<CCfgNetSecurityLogic>  
{
public:
	CCfgNetSecurityLogic();
	virtual ~CCfgNetSecurityLogic();

	//CLogicBase
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

	/** 功能:  清理窗口
	*  @param[in] 
	*  @return 
	*  @remarks  在窗口关闭的时候调用,清空窗口数据
	*/
    virtual void Clear() ;

	/** 功能:  判断cns配置页面的消息是否改变
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	bool IsCfgNetChange();

	/**	 
	* 功能: 获取界面上数据变化控件的数目
	* @return   bool
	* @remarks  
	*/
	s32 GetCtrlChangeNum() { return m_vctWndName.size(); }

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

protected:

	/** 功能:  收到会议状态的信息
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	LRESULT OnConfStateNty( WPARAM wparam, LPARAM lparam);

	HRESULT OnSetFtpInfoNty( WPARAM wparam, LPARAM lparam );
	
	HRESULT OnSetFtpInfoRsp( WPARAM wparam, LPARAM lparam );

	HRESULT OnSetTelnetInfoNty( WPARAM wparam, LPARAM lparam );
	
	HRESULT OnSetTelnetInfoRsp( WPARAM wparam, LPARAM lparam );


private:

	/** 功能:  保存配置的按钮
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnBtnSave( const IArgs& args );

	/** 功能:  还原配置的按钮
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnBtnCancel( const IArgs& args );

	/** 功能:  开启/关闭FTP服务
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnBtnSwitchFtpServer( const IArgs& args );

	/** 功能:  编辑FTP用户名的响应
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnFtpUsernameChange( const IArgs& args );

	/** 功能:  获得编辑FTP密码焦点的响应
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnEdtFtpPasswdSetFocus( const IArgs& args );

	/** 功能:  编辑FTP密码的响应
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnFtpPasswdChange( const IArgs& args );
	
	/** 功能:  失去编辑FTP密码焦点的响应
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnEdtFtpPasswdKillFocus(  const IArgs& args );

	/** 功能:  开启/关闭Telnet服务
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnBtnSwitchTelnetServer( const IArgs& args );

	/** 功能:  编辑Telnet用户名的响应
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnTelnetUsernameChange( const IArgs& args );

	/** 功能:  编辑Telnet密码的响应
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnTelnetPasswdChange( const IArgs& args );

	/** 功能:  获得编辑Telnet密码焦点的响应
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnEdtTelnetPasswdSetFocus( const IArgs& args );

	/** 功能:  失去编辑Telnet密码焦点的响应
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnEdtTelnetPasswdKillFocus( const IArgs& args );

	/** 功能:  切换到其他界面时提醒是否保存的窗口	
	*  @param[in] 
	*  @return 
	*  @remarks
	*/	
	bool SaveMsgBox();

private:
	void SetFtpInfo();

	void SetTelnetInfo();

	bool IsValidPWChar(CString szPWStr);

	bool IsValidPWCharStyle(CString szPWStr);

	void UpdateFtpPasswdTip( String strPasswd);

	void UpdateTelnetPasswdTip( String strPasswd);

private:

	const String    m_strBtnFtpServerSwitch;
	const String    m_strEdtFtpUsername;
	const String    m_strEdtFtpPasswd;
	const String    m_strBtnTelnetServerSwitch;
	const String    m_strEdtTelnetUsername;
	const String    m_strEdtTelnetPasswd;

	TTPFtpInfo  m_tTPFtpInfo;
	TTPTelnetInfo m_tTPTelnetInfo;

};

#endif // !defined(AFX_CFGNETSECURITYLOGIC_H__21896890_9A54_4DE8_96AE_063C6281D3FA__INCLUDED_)
