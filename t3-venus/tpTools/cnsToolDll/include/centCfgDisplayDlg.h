// centCfgDisplayDlg.h: interface for the CCentCfgDisplayDlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CENTCFGDISPLAYDLG_H__A5904C57_8B69_4078_9C21_1F98E93477C9__INCLUDED_)
#define AFX_CENTCFGDISPLAYDLG_H__A5904C57_8B69_4078_9C21_1F98E93477C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

class CCentCfgDisplayDlg : public CLogicBase, public ISingleTon<CCentCfgDisplayDlg>      
{
public:
	CCentCfgDisplayDlg();
	virtual ~CCentCfgDisplayDlg();

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
    virtual void Clear();

	/** 功能:  判断中控显示器界面的信息是否改变
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	bool IsCentCfgDisplayChange();

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
	s32 GetCtrlChangeNum();
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
	/** 功能:  开启NAT设置的按钮
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	bool OnBtnSwitchTVWALL( const IArgs& args );

	/** 功能:  开启显示器配置界面按钮
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	bool OnBtnDisplayCfg( const IArgs& args );

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
						
	/** 功能:  改变显示器1终端信号时的响应函数	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnTerminalOut1Change( const IArgs& args );	
							
	/** 功能:  改变显示器1电视墙信号时的响应函数
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnTVWALLOut1Change( const IArgs& args );	
							
	/** 功能:  改变显示器3终端信号时的响应函数	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnTerminalOut3Change( const IArgs& args );	
							
	/** 功能:  改变显示器3电视墙信号时的响应函数
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnTVWALLOut3Change( const IArgs& args );	
	
	/** 功能:  收到会议状态的信息
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	LRESULT OnConfStateNty( WPARAM wparam, LPARAM lparam);

	/** 功能:  接收服务器发过来的消息控制显示器配置界面显示状态
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	LRESULT OnDisplayShowNty( WPARAM wparam, LPARAM lparam);

	/** 功能:  接收服务器发过来的回应消息控制显示器配置界面显示状态
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	LRESULT OnDisplayShowInd( WPARAM wparam, LPARAM lparam);

	/** 功能:  接收服务器端发过来的消息然后中控电视墙状态
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnUpdateDisplayInfo( WPARAM wParam, LPARAM lParam );
	
	void SetDisplayInfo();
	
	/** 功能:  获取信号源状态
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	EmTVInputSelect GetDisplayType( String strCtrl );

	/** 功能:  设置信号源状态
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	string TransDisplayType( EmTVInputSelect emType );

	/** 功能:  将摄像机的开关状态转换为string类型
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	//String CamStateToString( EmCamPowerMode& emSwitchState );

	/** 功能:  接收服务器端发过来的消息然后更新文档摄像机状态
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	//LRESULT OnDocCamInfoNty( WPARAM wParam, LPARAM lParam );
	LRESULT OnUpdateDisplayModel( WPARAM wParam, LPARAM lParam );
	bool OnSelDisplay550A( const IArgs& args );
	bool OnSelDisplayGM01A( const IArgs& args );
	bool OnSelDisplayGH01A( const IArgs& args );
	bool OnSelDisplay70B17( const IArgs& args );
    bool OnSelDisplay665A( const IArgs& args );
    bool OnSelDisplay70GM44A( const IArgs& args );

	LRESULT OnTvModeInd( WPARAM wParam, LPARAM lParam );
	void UpdateTvState( EmTVModle emTvMode);
	void UpdateBtnState( );
	void RecoveryTerminalOut( );
private:
	vector<CString> m_vecOut;			//信号源
	const String m_strTerminalOut1;					
	const String m_strTVWALLOut1;
	const String m_strTerminalOut3;					
	const String m_strTVWALLOut3;
	const string m_strDisplay550A;
	const string m_strDisplayGM01A;
	const string m_strDisplayGH01A;
	const string m_strTvWallSwitch;
	const string m_strDisplayCfgSwitch;
	const string m_strModStatus;
	EmTVModle	 m_emTvMode;
	EmTVModle	 m_emSelTvMode;
};

#endif // !defined(AFX_CENTCFGDISPLAYDLG_H__A5904C57_8B69_4078_9C21_1F98E93477C9__INCLUDED_)
