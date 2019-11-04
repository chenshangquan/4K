// RenameOptDlg.h: interface for the CCRenameOptDlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RENAMEOPTDLG_H__50CA3A04_095D_42B6_B075_F568638BA64E__INCLUDED_)
#define AFX_RENAMEOPTDLG_H__50CA3A04_095D_42B6_B075_F568638BA64E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum EM_RENAME_TYPE      //窗口类型
{
	em_RENAME_VIDEOSOURCE,			//视频源重命名   
	em_RENAME_DISPLAYDOURCE,		//演示源重命名
	em_SAVE_PRESET,					//保存预置位
	em_CALL_PRESET,					//调用预置位
	em_RNAME_CURTAIN				//窗帘重命名
};

enum EM_PRESET_STYLE     //预置位方案
{
    em_CamDoc_Num3,                 //文档摄像机，预置位数3
    em_CamMoon904K60_Num8           //Moon904K60摄像机，预置位数8
};

class CCRenameOptDlg  :public CLogicBase, public ISingleTon<CCRenameOptDlg>
{
public:
	CCRenameOptDlg();
	virtual ~CCRenameOptDlg();
public:  
	/**	 
	* 功能:  注册该logic中所有的回调函数
	* @return  void
	* @remarks	在此注册的回调函数主要是控件的响应事件，多为成员回调函数,也可注册其他的回调函数
	                    注册时，应注意回调函数对应名子的命名规则：“类名::函数名”
	*/
	virtual void RegCBFun();

	/**	 
	* 功能:  注册要处理的消息
	* @return  void
	* @remarks	 注册后该消息才能发送到本逻辑模块，否则，接收不到该消息
	*/
	virtual void RegMsg(); 

	/**	 
	* 功能:  注销某回调函数
	* @return  void
	* @remarks	 
	*/
	virtual void UnRegFunc( );

	/**	 
	* 功能:  注销某回调函数
	* @return  void
	* @remarks	 
	*/
	virtual void UnRegMsg();
	
	/**	 
	* 功能:  初始化窗口数据,
	* @return  void
	* @remarks	由于该功能被归属到控件属性并在xml中与控件绑定，
	                    需要在RegCBFun（）中注册到回调函数管理模块 
	*/
    virtual bool InitWnd( const IArgs & arg );

   /**	 
	* 功能:  断链时清空所有状态和数据
	* @return   
	* @remarks	 
	*/
    virtual void Clear();
private:
	/** 功能:  收到重命名视频源名称消息、更新界面
	*  @param[in] wparam 存储视频源名称结构体
	*  @return 
	*  @remarks   
	*/
	HRESULT OnRenameVideoSource( WPARAM wparam, LPARAM lparam );
	/** 功能:  收到调用、保存预置位消息
	*  @param[in] wparam 是否为保存预置位
	*  @return 
	*  @remarks   
	*/
	HRESULT OnPreSet( WPARAM wparam, LPARAM lparam );
	/** 功能:  重命名演示源消息
	*  @param[in] wparam 单个演示源名称或全部演示源名称  lparam 是否重命名单个演示源
	*  @return 
	*  @remarks   
	*/
	HRESULT OnRenameDisplaySource( WPARAM wparam, LPARAM lparam );
	/** 功能:  窗帘重命名
	*  @param[in] wparam 单个窗帘名称或窗帘名称  lparam 是否重命名单个窗帘
	*  @return 
	*  @remarks   
	*/
	HRESULT OnCurtainRename( WPARAM wparam, LPARAM lparam );
	/**	 
	* 功能:  编号变动
	* @return   
	* @remarks	 
	*/
	bool OnRenameIDChange( const IArgs & arg );

	bool OnBtnOptMsgCancel( const IArgs & arg );
	/** 功能:  保存修改
	*  @param[in]
	*  @return 
	*  @remarks   
	*/
	bool OnBtnOptMngOk( const IArgs & arg );

private:
	/** 功能:  将字符串对应成视频源枚举
	*  @param[in]
	*  @return 
	*  @remarks   
	*/
	EmTPMtVideoPort GetVideoSourceType( String strCtrl );
	/** 功能:  将默认字符串对应成视频源枚举
	*  @param[in]
	*  @return 
	*  @remarks   
	*/
	EmTPMtVideoPort GetDefaultVideoSource( string strVideoSource );
	/** 功能:  将枚举对应成当前修改名称字符串
	*  @param[in]
	*  @return 
	*  @remarks   
	*/
	string TransVideoSourceType( EmTPMtVideoPort emType );
	/** 功能:  将枚举对应成默认名称字符串
	*  @param[in]
	*  @return 
	*  @remarks   
	*/
	string TransDefaultVideoSource( EmTPMtVideoPort emType );
	/** 功能:  该名称是否已经存在
	*  @param[in]
	*  @return 
	*  @remarks   
	*/
	bool IsExist( String strOldRenameInfo );

	bool IsVisible( String strOldRenameInfo );

	bool CheckInfo( String strOldRenameInfo );

	void SetVideoSourceData();

	void SetDisplaySourceData();
	/** 功能:  将演示源枚举对应成修改的字符串
	*  @param[in]
	*  @return 
	*  @remarks   
	*/
	string TransDisplaySourceType( EmVgaType emType );
	/** 功能:  将演示源枚举对应成默认的字符串
	*  @param[in]
	*  @return 
	*  @remarks   
	*/
	string TransDefaultDisplaySource( EmVgaType emType );

	EmVgaType GetDisplaySourceType( String strCtrl );

	EmVgaType GetDefaultDisplaySource( string strDisplaySource );
	/** 功能:  将修改的内容保存到结构体中
	*  @param[in]
	*  @return 
	*  @remarks   
	*/
	void SaveContext( String strLastRenameInfo );

	void UpdateState();

//	bool IsChange( );

	bool GetType( String strContext );
	/** 功能:  组合框选择新条目时，对上一次名称检测未通过，用于获取上一次组合框的值
	*  @param[in]
	*  @return 
	*  @remarks   
	*/
	String GetLastDefaultContext( );

	void SetPreSetData();

	bool onRenameOptDlg();
	/** 功能:  将字符串对应成调用预置位枚举值
	*  @param[in]
	*  @return 
	*  @remarks   
	*/
	EmDCamRecallNum GetCallPreSetType( string strDCamCallPreSet );

	EmDCamPresetNum GetSavePreSetType( string strDCamCallPreSet );

    /** 功能:  将字符串对应成调用预置位索引
	*  @param[in]
	*  @return 
	*  @remarks   
	*/
	u8 GetPreSetIndex( string strPreSet );

	/** 功能:  获取Combobox的Text,对应成默认枚举，通过枚举，对应成当前临时保存的字符串
	*  @param[in]
	*  @return 
	*  @remarks   
	*/
	String GetCurrentText( );
private:
	TTPVideoSourceName     m_atVideoSourceName[emTPC7Vid+1];					//视频源名称
	const String           m_strRenameCombox;									//XML中的Combobox 对应的字符串
	const String           m_strRenameInfo;										//存储XML对应的重命名编辑框

	EmTPMtVideoPort		   m_emOldVideoSourceType;								//上一次演示源对应的枚举值
	EmTPMtVideoPort		   m_emCurrentVideoSourceType;							//当前对应的枚举值

	TVgaInfo			   m_atDisplaySourceInfo[5];							//视频源名称
	EM_RENAME_TYPE         m_emRenameType;										//窗口类型

	EmVgaType			   m_emOldDisplaySourceType;							//上一次状态
	EmVgaType			   m_emCurrentDisplaySourceType;						//当前演示源对应的枚举值
	TCentreCurInfo		   m_tCurtainInfo;										//临时窗帘名称
	TCentreCurInfo		   m_tOldCurtainInfo;									//未修改之前的名称
	s32					   m_nLastIndex;										//最近一次修改的窗帘索引
    EM_PRESET_STYLE        m_emPresetStyle;                                     //预置位方案
};

#endif // !defined(AFX_RENAMEOPTDLG_H__50CA3A04_095D_42B6_B075_F568638BA64E__INCLUDED_)
