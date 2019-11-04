// CfgMainAudioDlg.h: interface for the CCfgMainAudioDlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CFGMAINAUDIODLG_H__BA02C747_CF77_4F21_8478_6B2B758621E6__INCLUDED_)
#define AFX_CFGMAINAUDIODLG_H__BA02C747_CF77_4F21_8478_6B2B758621E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCfgMainAudioDlg  : public CLogicBase, public ISingleTon<CCfgMainAudioDlg>
{
public:
	CCfgMainAudioDlg();
	virtual ~CCfgMainAudioDlg();

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
	/* 功能: 获取界面上数据变化控件的数目
	* @return   s32
	* @remarks  
	*/
	s32 GetCtrlChangeNum() { return m_vctWndName.size(); }
	/* 功能: 界面有改动，提示保存
	* @return   bool
	* @remarks  
	*/
	bool IsCfgMainAudioChange();
	//下载超时
	void DownloadOvertime();
private:
	/* 功能: 更新主视频界面
	* @return   HRESULT
	* @remarks  
	*/
	HRESULT OnUpdateMainAudioNty( WPARAM wparam, LPARAM lparam );
	/* 功能: 界面恢复默认消息处理
	* @return   HRESULT
	* @remarks  
	*/
	HRESULT OnDefMainAudioNty( WPARAM wparam, LPARAM lparam );
	/* 功能: 重命名后，刷新主视频大图像，小图像名字
	* @param[in] wparam 传递演示源名称
	* @return   HRESULT
	* @remarks  
	*/
	HRESULT OnRefreshVideoInfoNty( WPARAM wparam, LPARAM lparam );

//	HRESULT OnUpdatePanCamNty( WPARAM wparam, LPARAM lparam );
	/* 功能: 会议状态通知
	* @return   LRESULT
	* @remarks  
	*/
	LRESULT OnConfStateNty( WPARAM wparam, LPARAM lparam );
	/* 功能: 快照通知
	* @return   LRESULT
	* @remarks  
	*/
	LRESULT OnSnapShotNty( WPARAM wparam, LPARAM lparam );
private:
	/* 功能: 大图像1Combobox内容修改
	* @return   bool
	* @remarks  
	*/
	bool OnLargeImage1Change( const IArgs& args );

	bool OnLargeImage2Change( const IArgs& args );

	bool OnLargeImage3Change( const IArgs& args );
	/* 功能: 小图像1Combobox内容修改
	* @return   bool
	* @remarks  
	*/
	bool OnSmallImage1Change( const IArgs& args );

	bool OnSmallImage2Change( const IArgs& args );

	bool OnSmallImage3Change( const IArgs& args );
	/* 功能: 弹出重命名窗口
	* @return   bool
	* @remarks  
	*/
	bool OnBtnOptRenameDlg( const IArgs& args );

	bool OnSwitchSynthesis(const IArgs & arg );
	/* 功能: 取消界面修改
	* @return   bool
	* @remarks  
	*/
	bool OnBtnCancel( const IArgs& args );
	/* 功能: 将配置项恢复到默认
	* @return   bool
	* @remarks  
	*/
	bool OnBtnDefault( const IArgs& args );
	/* 功能: 保存配置
	* @return   bool
	* @remarks  
	*/
	bool OnBtnSave( const IArgs& args );

	bool OnLayoutChange( const IArgs& args );

	bool OnBtnPreview( const IArgs& args );
	/* 功能: 选择画面风格
	* @return   bool
	* @remarks  
	*/
	bool OnSelSynthesisStyle( const IArgs& args );

private:
	/**功能:  判断这路大图像是否有变动，更新按键状态
	*  @param[in] nIndex 第几路大图像  emVideoSourceType 界面大图像对应的枚举值
	*  @return  bool
	*  @remarks  
	*/
	bool UpdateLargeImage( s32 nIndex , EmTPMtVideoPort emVideoSourceType );
	/**功能:  判断这路小图像是否有变动，更新按键状态
	*  @param[in] nIndex 第几路小图像  emVideoSourceType 这路小图像对应的枚举值
	*  @return  bool
	*  @remarks  
	*/
	bool UpdateSmallImage( s32 nIndex ,EmTPMtVideoPort emVideoSourceType );
	/**功能:  通过字符串转化为对应的枚举值
	*  @param[in] 
	*  @return  
	*  @remarks  
	*/
	EmTPMtVideoPort GetVideoSourceType( String strCtrl );
	/**功能:  将图像比例调节字符串转为对应枚举
	*  @param[in] 
	*  @return  
	*  @remarks  
	*/
	EmVidEncResizeMode GetResizeModeType( String strCtrl );
	/**功能:  设置主视频界面显示
	*  @param[in] 
	*  @return  
	*  @remarks  
	*/
	void SetMainAudioDate();
	/**功能:  大、小图像对应的枚举转化为字符串
	*  @param[in] 
	*  @return  
	*  @remarks  
	*/
	string TransVideoSourceType( EmTPMtVideoPort emType );
	/**功能:  将图像比例调节枚举转化为字符串
	*  @param[in] 
	*  @return  
	*  @remarks  
	*/
	string TransResizeModType( EmVidEncResizeMode emType );
	/**功能:  设置默认数据
	*  @param[in] 
	*  @return  
	*  @remarks  
	*/
	void SetDefVideoSrcInfo();

	void SaveMainAudioInfo( );
	/* 功能: 设置第一路COMBOLIST数据
	* @return  
	* @remarks  
	*/
	void SetVideoSrc1Data( );
	/* 功能: 设置第二路COMBOLIST数据
	* @return  
	* @remarks  
	*/
	void SetVideoSrc2Data( );
	/* 功能: 设置第三路COMBOLIST数据
	* @return  
	* @remarks  
	*/
	void SetVideoSrc3Data( );
	/* 功能: 释放快照图片
	* @return  
	* @remarks  
	*/
	void ReleaseSnapImage();
	/* 功能: 保存图片名称
	* @return  
	* @remarks  
	*/
	string GetSnapShotFileName( const string strFileName );

	BOOL DownloadCore(const String& strFilePath,const String & strFileName );

	bool OnDownloadProgress( const IArgs & arg );
private:
	vector<CString> m_vecLayout;                    //方案布局

	TTPVideoInfoTool m_tMainAudioInfo;              //保存界面上的临时数据
	TTPVideoInfoTool m_tOldMainAudioInfo;
	String m_strLargeImage[emEndMPCodec-1];		    //存储XML中对应的大图像控件名称	
	String m_strSmallImage[emEndMPCodec-1];			//存储XML中对应的小图像控件名称	
	const String m_strLayout;						//存储XML中的布局名称
	const String m_strImageSynthesis;				//存储XML中的图像融合策略开关
	const String m_strDefault;						//存储XML中恢复默认按钮
	const String m_strSave;							//存储XML中保存按钮
	const String m_strCancel;						//存储XML中取消按钮
	const String m_strStatus;						//存储XML中隐藏控件，用于在名称修改时，更新保存按键等状态
	const String m_strThreeImage;					//三画面
	const String m_strFourImage;                    //四画面
	vector<string> m_vecShatShot;					//存储XML中对应3张快照控件名称
	CFtpCtrl m_cFtp;
	vector<String> m_vctDownFile;                   //保存待下载快照文件
	vector<String> m_vecFilePath;					//加载快照的路径
	Window* m_pWnd;
	bool		   m_bIsUsedGroup1;				   //未使用snapshot0.jpg snapshot1.jpg snapshot2.jpg组图片
};

#endif // !defined(AFX_CFGMAINAUDIODLG_H__BA02C747_CF77_4F21_8478_6B2B758621E6__INCLUDED_)
