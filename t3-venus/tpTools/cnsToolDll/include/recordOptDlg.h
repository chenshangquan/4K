// recordOptDlg.h: interface for the RecordOptDlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RECORDOPTDLG_H__C7A5678B_ABAF_489F_B595_6E2744B6EA9E__INCLUDED_)
#define AFX_RECORDOPTDLG_H__C7A5678B_ABAF_489F_B595_6E2744B6EA9E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define  CNSSTATISTIC_FILE_NAME		"网络诊断.ini"

class RecordOptDlg  :public CLogicBase, public ISingleTon<RecordOptDlg>
{
public:
	RecordOptDlg();
	virtual ~RecordOptDlg();
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

	bool OnBtnClose( const IArgs & arg );
	bool OnBtnScan( const IArgs & arg );
	bool OnOpenFolder( const IArgs & arg );

	bool OnBtnSave( const IArgs & arg );

	HRESULT OnInterfaceSelection( WPARAM wparam, LPARAM lparam );
	CString getNewFileName( string strFolder , string strFileName );
private:
	const string		m_StrStartingSch;
	const string		m_StrEndingSch;
	const string		m_StrCleanSch;

	const string		m_StrForder;
	const string		m_StrFileName;

//	string              m_strFullFilePath;
	CFile				m_cFile;
	bool				m_bIsRecording;
};

#endif // !defined(AFX_RECORDOPTDLG_H__C7A5678B_ABAF_489F_B595_6E2744B6EA9E__INCLUDED_)
