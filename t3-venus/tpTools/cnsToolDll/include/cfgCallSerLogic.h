// cfgCallSerLogic.h: interface for the CCfgCallSerLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CFGCALLSERLOGIC_H__8B0F0488_400D_4306_A6D1_ACE682E941FE__INCLUDED_)
#define AFX_CFGCALLSERLOGIC_H__8B0F0488_400D_4306_A6D1_ACE682E941FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

class CCfgCallSerLogic : public CLogicBase, public ISingleTon<CCfgCallSerLogic>  
{
public:
	CCfgCallSerLogic();
	virtual ~CCfgCallSerLogic();
	
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
	bool IsCfgCallChange();

	/** 功能:  切换到其他界面时提醒是否保存的窗口	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool SaveMsgBox();

	/**	 
	* 功能: 获取界面上数据变化控件的数目
	* @return   bool
	* @remarks  
	*/
	//s32 GetCtrlChangeNum() { return m_vctWndName.size(); }
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
				
	/** 功能:  改变呼叫演示格式控件时的响应函数	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnShowModeChange( const IArgs& args );	
						
	/** 功能:  改变呼叫会议格式控件时的响应函数	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnCallModeChange( const IArgs& args );	
																
	/** 功能:  获取用户选择的呼叫会议格式
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	void GetCallMode( TTPVidForamt& tVidForamt )const;

	/** 功能:  获取选中格式的分辨率和帧数
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	TTPVidForamt GetMode( String strMode )const;
											
	/** 功能:  获取用户选择的呼叫演示格式
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	void GetShowMode( TTPVidForamt& tVidForamt )const;
											
	/** 功能:  会议讨论的按钮
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnBtnSwitchDiscuss( const IArgs& args );	
											
	/** 功能:  会议轮询的按钮
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnBtnSwitchPolling( const IArgs& args );	
											
	/** 功能:  改变轮询时间控件时的响应函数
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnPollTimeChange( const IArgs& args );	
											
	/** 功能:  改变单屏码率控件时的响应函数
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnConfRateChange( const IArgs& args );	

	bool OnConfRateNoFocus( const IArgs& args );

	bool OnShowRateNoFocus( const IArgs& args );

	bool OnAudioModeChange( const IArgs& args );

	/** 功能:  选择是否加密以及加密方式时的响应函数
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnSelEncrptyStyle( const IArgs& args );
	/** 功能:  选择量子加密方式时的响应函数
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnShowQuantumErpChange( const IArgs& args );

	bool OnShowQuantumErpNoFocus( const IArgs& args );


	/** 功能:  改变演示码率控件时的响应函数
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnShowRateChange( const IArgs& args );	
						
	/** 功能:  根据服务器接收会议优选格式的反馈消息并更新界面
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	HRESULT OnUpdateVideoFormat( WPARAM wparam, LPARAM lparam );
						
	/** 功能:  根据服务器接收演示优选格式的反馈消息并更新界面
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	HRESULT OnUpdateDualVideoFormat( WPARAM wparam, LPARAM lparam );
						
	/** 功能:  根据服务器接收单屏码率的反馈消息并更新界面
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	HRESULT OnUpdateCallRate( WPARAM wparam, LPARAM lparam );
						
	/** 功能:  根据服务器接收演示码率的反馈消息并更新界面
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	HRESULT OnUpdateDualCallRate( WPARAM wparam, LPARAM lparam );
						
	/** 功能:  根据服务器接收会议讨论的反馈消息并更新界面
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	HRESULT OnUpdateConfDis( WPARAM wparam, LPARAM lparam );
						
	/** 功能:  根据服务器接收会议轮询的反馈消息并更新界面
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	HRESULT OnUpdateConfPoll( WPARAM wparam, LPARAM lparam );
						
	/** 功能:  设置优选格式信息
	*  @param[in] strControl  控件名称
	*  @return 
	*  @remarks   
	*/	
	void SetFormat( TTPVidForamt& tVidForamt, String strControl );
						
	/** 功能:  设置会议优选格式信息
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	void SetVideoFormat();							
	/** 功能:  设置演示优选格式信息
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	void SetDualVideoFormat();
						
	/** 功能:  设置单屏码率信息
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	void SetCallRate();							
	/** 功能:  设置演示码率信息
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	void SetDualCallRate();
						
	/** 功能:  设置会议讨论信息
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	void SetConfDisState();							
	/** 功能:  设置会议轮询信息
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	void SetConfPollInfo();

	/** 功能:  收到会议状态的信息
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	HRESULT OnConfStateNty( WPARAM wparam, LPARAM lparam);
						
	/** 功能:  根据服务器接收音频格式的反馈消息并更新界面
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	HRESULT OnUpdateAudioFormat( WPARAM wparam, LPARAM lparam );						
	/** 功能:  设置音频格式信息
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	void SetAudioFormat();

	EmTpAudioFormat GetAudioFormat();
	/** 功能:  更新AES加密状态
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	LRESULT OnEncryptInfoNty( WPARAM wparam, LPARAM lparam );

	void SetEncryptType();
	bool SaveEncryptType();
private:
	vector<CString> m_vecCallModeData;			//会议格式
	vector<CString> m_vecShowModeData;			//演示格式
	vector<CString> m_vecConfRateData;			//会议码率
	vector<CString> m_vecShowRateData;			//演示码率
	vector<CString> m_vecAudioRateData;			//音频格式
	vector<CString> m_vecQuantumErpData;        //加密格式
	const String m_strCallMode;					//多会场呼叫会议格式
	const String m_strShowMode;					//多会场呼叫演示格式
	const String m_strShowQuantumErp;           //量子加密选项
	TTpEncryptKey  m_tEncryptKey;
//	const String m_strBtnAESSwitch;			    //AES开关
	const String m_strNoEncrptyPort;            //不加密
	const String m_strAESEncrptyPort;           //AES加密
	const String m_strQuantumErpPort;           //量子加密

	//EmTPEncryptType m_emTPEncryptType;
};

#endif // !defined(AFX_CFGCALLSERLOGIC_H__8B0F0488_400D_4306_A6D1_ACE682E941FE__INCLUDED_)
