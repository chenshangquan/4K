// cfgDemonStrationDlg.h: interface for the CCfgDemonStrationDlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CFGDEMONSTRATIONDLG_H__2C5DCC8D_7069_4EC1_AD0F_50C94CB2E640__INCLUDED_)
#define AFX_CFGDEMONSTRATIONDLG_H__2C5DCC8D_7069_4EC1_AD0F_50C94CB2E640__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCfgDemonStrationDlg  : public CLogicBase, public ISingleTon<CCfgDemonStrationDlg>
{
public:
	CCfgDemonStrationDlg();
	virtual ~CCfgDemonStrationDlg();

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
	/** 功能:  接收服务器消息并更新界面
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	HRESULT OnDisplaySourceNty( WPARAM wparam, LPARAM lparam );
	/** 功能:  接收服务器消息并更新界面
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	HRESULT OnDefDisplaySourceNty( WPARAM wparam, LPARAM lparam );
	/** 功能:  接收重命名弹出框消息并发送给服务器
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	HRESULT OnUpdateDisplaySource( WPARAM wparam, LPARAM lparam );

	LRESULT OnConfStateNty( WPARAM wparam, LPARAM lparam );
    /** 功能:  收到版本通知信息
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	LRESULT OnVerInfoNty( WPARAM wparam, LPARAM lparam);
	/** 功能:  将控件设置为不可用
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	void InitCtrlEnable();					
	/** 功能:  空闲演示按钮
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnBtnIdleSwitch( const IArgs & arg );
	/** 功能:  会议演示按钮
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnBtnConfSwitch( const IArgs & arg );
	/** 功能:  空闲演示 选择左屏幕，并发送请求给服务器
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnSelLeft1( const IArgs & arg );
	/** 功能:  空闲演示 选择中间屏幕，并发送请求给服务器
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnSelMid1( const IArgs & arg );
	/** 功能:  空闲演示 选择右屏幕，并发送请求给服务器
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnSelRight1( const IArgs & arg );
	
	bool OnSelLeft2( const IArgs & arg );
	
	bool OnSelMid2( const IArgs & arg );
	
	bool OnSelRight2( const IArgs & arg );
	/** 功能:  重命名功能，弹出重命名窗口
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnBtnOptRenameDlg( const IArgs& args );
	/** 功能:  将当前选择演示源设为默认演示源，并发送请求给服务器
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnBtnSetDefault( const IArgs & arg );
	
	bool OnClickDisplayLstBlack( const IArgs& args );

	bool OnClickVideoSourceList( const IArgs & arg );

	void SetDemonStrationDate( );
	/** 功能:  恢复默认演示源请求
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnBtnDefault( const IArgs & arg );

	void SetDefaultDemonStration( TTPDualDisplayStrategy & tDualDisplayStrategy, EmVgaType &emDefaultDisplay );

	void SendCommand();
	/** 功能:  设置列表数据
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	void SetListDate( );
	/** 功能:  列表数据排序
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	void SoftDemoStrationData( vector<Value_DisplaySrc::TDisplaySrcData> &vecTDisplaySource );
	/** 功能:  列表数据交换
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	void SwapDemoSourceData( s32 nNum ,EmVgaType emType , vector<Value_DisplaySrc::TDisplaySrcData> &vecTDisplaySource );
	/** 功能:  获取演示源数据
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	void GetDemoStrationData();
	/** 功能:  保存演示源的演示策略
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	void SaveDemoStrationData( TTPDualDisplayStrategy &tDualDisplayStrategy );
	
	BOOL CheckIdleStrategy( );
	BOOL CheckConfStrategy( );
private:
	String							    m_strIdleStrategy[emEndMPCodec-1];					//保存空闲时演示3个CheckBox字符串
	String								m_strConfStrategy[emEndMPCodec-1];					//会议时演示3个CheckBox字符串

	const String						m_strIdleSwitch;
	const String						m_strConfSwitch;
	const String						m_strList;	
	TVgaInfo							m_atDemoSourceName[5];							   //视频源名称
	EmVgaType							m_emDefault;
	TTPDualDisplayStrategy				m_tDualDisplayStrategy;
	vector<Value_DisplaySrc::TDisplaySrcData>   m_vecDisplaySource;
	Value_DisplaySrc::TDisplaySrcData	m_tCurSelEntry;
};

#endif // !defined(AFX_CFGDEMONSTRATIONDLG_H__2C5DCC8D_7069_4EC1_AD0F_50C94CB2E640__INCLUDED_)
