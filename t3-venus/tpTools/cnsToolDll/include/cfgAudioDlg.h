// cfgAudioDlg.h: interface for the CCfgAudioDlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CFGAUDIODLG_H__069DCC21_7725_4859_8C6B_572E35B5833A__INCLUDED_)
#define AFX_CFGAUDIODLG_H__069DCC21_7725_4859_8C6B_572E35B5833A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCfgAudioDlg : public CLogicBase, public ISingleTon<CCfgAudioDlg>
{
public:
	CCfgAudioDlg();
	virtual ~CCfgAudioDlg();

public:	
	/** 功能: 注册消息,接收来自lib库中发送来的消息
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/
	void RegMsg();
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
	/** 功能:  隐藏所有窗口
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	//	void HideAllWnd();
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
	s32 GetCtrlChangeNum() { return m_vctWndName.size(); }

	bool IsCfgAudioChange();

private:

	void SetAudioData();

	void SetMixType();

	void SetAux2Info();

	void InitCtrlEnable();

	bool UpdateGroup( TTPMPAudioInfo& tAudioInfo );
	/**功能:  第一路输出增益进度条变动，更新编辑框
	*  @param[in] 
	*  @return  
	*  @remarks  
	*/
	bool OnSliderGain1Changed(const IArgs & arg );

	bool OnSliderGain2Changed(const IArgs & arg );

	bool OnSliderGain3Changed(const IArgs & arg );

	bool OnSliderGain4Changed(const IArgs & arg );

	bool OnSliderGain5Changed(const IArgs & arg );
	/**功能:  第一路输出增益编辑框变动，修改滑块进度
	*  @param[in] 
	*  @return  
	*  @remarks  
	*/
	bool OnEditGain1Changed(const IArgs & arg );

	bool OnEditGain2Changed(const IArgs & arg );

	bool OnEditGain3Changed(const IArgs & arg );

	bool OnEditGain4Changed(const IArgs & arg );

	bool OnEditGain5Changed(const IArgs & arg );
	/**功能:  开启、关闭第一路白噪声
	*  @param[in] 
	*  @return  
	*  @remarks  
	*/
	bool OnBtnSwitch1(const IArgs & arg );

	bool OnBtnSwitch2(const IArgs & arg );

	bool OnBtnSwitch3(const IArgs & arg );
	/**功能:  开启、关闭AGC
	*  @param[in] 
	*  @return  
	*  @remarks  
	*/
	bool OnBtnAGC(const IArgs & arg );
	
	bool OnBtnMAEC(const IArgs & arg );

	bool OnBtnMANS(const IArgs & arg );

	/**功能:  监听输出：本地、远端混音、本地和远端混音输出
	*  @param[in] 
	*  @return  
	*  @remarks  
	*/
	bool OnSelMixSound( const IArgs& args );

	bool OnBtnAUX2(  const IArgs& args );

	bool OnBtnCancel( const IArgs& args );
	
	bool OnBtnDefault( const IArgs& args );
	
	bool OnBtnSave( const IArgs& args );
private:
	HRESULT OnDefaultAudioNty( WPARAM wparam, LPARAM lparam );
	/**功能:  开启、关闭白噪声回复
	*  @param[in] 
	*  @return  
	*  @remarks  
	*/
	HRESULT OnWhiteNoiseNty( WPARAM wparam, LPARAM lparam );
	/**功能:  接受消息，更新白噪声播放时间以及滑块的位置
	*  @param[in] 
	*  @return  
	*  @remarks  
	*/
	HRESULT OnUpdateWhiteNoiseNty( WPARAM wparam, LPARAM lparam );
	/**功能:  会议状态通知、会议中禁用白噪声播放开关
	*  @param[in] 
	*  @return  
	*  @remarks  
	*/
	LRESULT OnConfStateNty( WPARAM wparam, LPARAM lparam );

	/**功能:  更新音频界面
	*  @param[in] 
	*  @return  
	*  @remarks  
	*/
	HRESULT OnUpdateAudioNty( WPARAM wparam, LPARAM lparam );

	HRESULT OnSetMixType( WPARAM wparam, LPARAM lparam );

	HRESULT OnSetAux2Info( WPARAM wparam, LPARAM lparam );
	

//	bool OnSliderNoise1Changed(const IArgs & arg );

//	bool OnSliderNoise2Changed(const IArgs & arg );

//	bool OnSliderNoise3Changed(const IArgs & arg );

	/**功能:  开启、关闭白噪声请求
	*  @param[in] 
	*  @return  
	*  @remarks  
	*/
	bool SendWhiteNoiseReq( String strWndName, s32 nNum );
	/**功能:  开启、关闭白噪声请求
	*  @param[in] 
	*  @return  
	*  @remarks  
	*/
	void UpdateGainNum( String strGainName, String strEditName, s32 nNum );

	void UpdateGainEdit( String strEditName, String strSliderName, s32 nNum );
	/**功能:  设置白噪声时间和滑块位置
	*  @param[in] 
	*  @return  
	*  @remarks  
	*/
	void UpdatePlayTimer( String strGainName, String strPlayTimeName,s32 nNum ,u8 byWhiteNoiseTime );

	void SetDefaultAudioInfo();
	
	void SetDefaultMixType();

	void SetDefaultAux2Info();

	void SaveGroup( );

	void initWhiteNoise( );

	void UpdateWhiteNoiseState( String strWndName ,BOOL bIsOpen );

private:
	TTPMPAudioInfo m_tOldAudioSetInfo;                //临时保存的界面数据
	TTPMPAudioInfo m_atAudioSetInfo;				  
	const String   m_strMaxPlayTime;				  //最大时间
	BOOL           m_bOldWhiteNoise[3];				  //
	u8             m_byLastWhiteNoiseTime[3];		  //上一次时间

private:
	const String m_strMixPort1;	
	const String m_strMixPort2;
	const String m_strMixPort3;

	EmAudMixType  m_emCheckState;
	u8            m_byAudMixVolume;
	EmAudExtend   m_emAux2State;
	u8            m_byAudExtendVolume;

};

#endif // !defined(AFX_CFGAUDIODLG_H__069DCC21_7725_4859_8C6B_572E35B5833A__INCLUDED_)
