// CentCfgCameraDlg.h: interface for the CCentCfgCameraDlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CENTCFGCAMERADLG_H__4EF58907_60FB_4087_A492_755896396F1A__INCLUDED_)
#define AFX_CENTCFGCAMERADLG_H__4EF58907_60FB_4087_A492_755896396F1A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCentCfgCameraDlg  : public CLogicBase, public ISingleTon<CCentCfgCameraDlg> 
{
public:
	CCentCfgCameraDlg();
	virtual ~CCentCfgCameraDlg();
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
	 /** 功能: 注册消息,接收来自lib库中发送来的消息
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/
	 void RegMsg();
	 /** 功能:  更新全景摄像机界面
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
//	 LRESULT OnPanCamNty( WPARAM wParam, LPARAM lParam );
	/** 功能:  更新文档摄像机界面
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	 LRESULT OnDocCamInfoNty( WPARAM wParam, LPARAM lParam );
	 /** 功能:  文档摄像机聚焦通知，更新界面
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	 LRESULT OnDocCamAutoFocusNty( WPARAM wParam, LPARAM lParam );
	 /** 功能:  文档摄像机ZOOM操作通知，更新界面
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	 LRESULT OnDocCamZoomNty( WPARAM wParam, LPARAM lParam );
	 /** 功能:  文档摄像机白平衡操作通知，更新界面
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	 LRESULT OnDocCamWBNty( WPARAM wParam, LPARAM lParam );
	 /** 功能:  文档摄像机曝光模式是否设置成功，成功更新界面
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	 LRESULT OnDcCamExpMode( WPARAM wParam, LPARAM lParam );
	 /** 功能:  文档摄像机曝光增益设置反馈，失败返回上次状态
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	 LRESULT OnDcCamExpGain( WPARAM wParam, LPARAM lParam );
	 /** 功能:  文档摄像机曝光快门设置反馈，失败返回上次状态
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	 LRESULT OnDCCamShutNty( WPARAM wParam, LPARAM lParam );
	 /** 功能:  文档摄像机曝光光圈设置反馈，失败返回上次状态
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	 LRESULT OnDCCamApertureNty( WPARAM wParam, LPARAM lParam );
	 /** 功能:  文档摄像机白平衡R增益设置反馈，失败返回上次状态
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	 LRESULT OnDocCamRGainNty( WPARAM wParam, LPARAM lParam );
	 /** 功能:  文档摄像机白平衡B增益增益设置反馈，失败返回上次状态
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	 LRESULT OnDocCamBGainNty( WPARAM wParam, LPARAM lParam );
	 /** 功能:  全景摄像机数量设置反馈，失败返回上次状态
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	 LRESULT OnPanCamNumNty( WPARAM wParam, LPARAM lParam );
	 /** 功能:  文档摄像机保存预置位反馈，失败进行提示
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	 LRESULT OnDocCamSavePreSetNty( WPARAM wParam, LPARAM lParam );
	 /** 功能:  文档摄像机调用预置位反馈，失败进行提示
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	 LRESULT OnDocCamCallPreSetNty( WPARAM wParam, LPARAM lParam );

	 LRESULT OnDocCamCfg( WPARAM wParam, LPARAM lParam );

	 LRESULT OnDocCamBootCall( WPARAM wParam, LPARAM lParam );

	 LRESULT OnDocCamModelNty( WPARAM wParam, LPARAM lParam );

	 LRESULT OnPanCamModelNty( WPARAM wParam, LPARAM lParam );
private:
	/** 功能:  预置位1
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnSelPreset( const IArgs& args );
	/** 功能:  选中上次状态
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnSelLastPreset( const IArgs& args );
	/** 功能:  开启，关闭全景摄像机
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	 bool OnPanCamBtnChange( const IArgs& args );
	 /** 功能:  开启，关闭文档摄像机
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	 bool OnDocCameraBtnChange( const IArgs& args );
     /** 功能:  开启，关闭CMA300摄像机
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	 bool OnCMACameraBtnChange( const IArgs& args );
	 /** 功能:  修改全景摄像机数量
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	 bool OnPanCamNumChange( const IArgs& args );
	 /** 功能:  按下ZOOM+操作
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	 bool OnLBtnDownZoonPlus( const IArgs& args );
	 /** 功能:  松开ZOOM+操作
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	 bool OnLBtnUpZoonPlus( const IArgs& args );
	 /** 功能:  按下ZOOM-操作
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	 bool OnLBtnDownZoonSub( const IArgs& args );
	 /** 功能:  松开ZOOM-操作
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	 bool OnLBtnUpZoonSub( const IArgs& args );
	 /** 功能:  切换到自动模式
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	 bool OnBtnAutoFocusClick( const IArgs& args );
	 /** 功能:  按下焦距拉近
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	 bool OnLBtnDownFocusNear( const IArgs& args );
	 /** 功能:  松开焦距拉近
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	 bool OnLBtnUpFocusNear( const IArgs& args );

	 bool OnLBtnDownFocusFar( const IArgs& args );

	 bool OnLBtnUpFocusFar( const IArgs& args );

	 bool OnBtnManualFocusClick( const IArgs& args );
	 /** 功能:  自动/手动曝光设置
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	 bool OnBtnSwitchAutoExposure( const IArgs& args );
	 /** 功能:  视眼拉近
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	 bool OnBtnSwitchAutoWB( const IArgs& args );
	 /** 功能:  根据R增益滑块位置变化，更新编辑框数据，并发送给服务器
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	 bool OnSliderRGainChanged( const IArgs& args );
	 /** 功能:  根据B增益滑块位置变化，更新编辑框数据，并发送给服务器
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	 bool OnSliderBGainChanged( const IArgs& args );
	 /** 功能:  R增益编辑框失去焦点，发给服务器设置R增益命令
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	 bool OnEditRGainKillFocus( const IArgs& args );
	 /** 功能:  编辑框内容变化，改变进度条位置
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	 bool OnEditRGainChange( const IArgs& args );
	 /** 功能:  编辑框内容变化，改变进度条位置
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	 bool OnEditBGainChange( const IArgs& args );
	 /** 功能:  B增益编辑框失去焦点，发给服务器设置B增益命令
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	 bool OnEditBGainKillFocus( const IArgs& args );

	 /** 功能:  点击光圈，设置光圈数值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	 bool OnComboboxApertureClick( const IArgs& args );
	 /** 功能:  点击快门COMBOLIST，设置快门
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	 bool OnComboboxShutClick( const IArgs& args );
	 /** 功能:  点击增益COMBOLIST，设置快门
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	 bool OnComboboxExpGainClick( const IArgs& args );
	 /** 功能:  点击保存预置位，弹出保持预置位窗口
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	 bool OnBtnSavePreSet( const IArgs& args );
	 /** 功能:  点击调用预置位，弹出调用预置位窗口
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	 bool OnBtnCallPreSet( const IArgs& args );
	 /** 功能:  Zoom编辑框值变化
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	 bool OnEdtZoomChange( const IArgs& args );
	 /** 功能:  Zoom编辑框值失去焦点
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	 bool OnEdtZoomKillFocus( const IArgs& args );

	 bool OnSelIPC822( const IArgs& args );

	 bool OnSelPRS200( const IArgs& args );

	 bool OnSel120E( const IArgs& args );
	 
	 bool OnSelMOON50( const IArgs& args );
private:
	/** 功能:  根据Edit值，更新滑块位置
	*  @param[in]	strEditName 编辑框名称   strSliderName 对应的进度名称
	*  @return 
	*  @remarks   
	*/
	 void GainEditChange( const IArgs& args ,string strEditName, string strSliderName );
	 /** 功能:  根据滑块位置，更新编辑框
	*  @param[in]	strSliderName 对应的进度名称  strEditName 编辑框名称
	*  @return 
	*  @remarks   
	*/
	 void SetGainValue( u16 wRGain ,string strStrliderName, string strEditName );

	 void SetZoomValue( float fZoom );

	 string TransApertureTypeToString( EmDCamIris emAperture );

	 EmDCamIris TransApertureTextToType( string strAperture );
	 
	 string TransGainTypeToString( EmDCamGain emDCGain );

	 EmDCamGain TransGainTextToType( string strGainText );

	 string TransShutterTypeToString( EmDCamShutSpd emDCShut );

	 EmDCamShutSpd TransShutterTextToType( string strShutterText );

	 CString OnlyFloat( CString str );

	 float StringToFloatTwo( CString str );

	 void SetZoomCmd( CString str );
private:
	 const string m_strPanSwitchBtn;						//全景摄像机开关
	 const string m_strPancombobox;							//全景摄像机数量
	 const string m_strDocSwitch;							//文档摄像机开关
	 const string m_strDocZoonPlusBtn;						//文档摄像机增加视眼
	 const string m_strDocZoonSubBtn;						//文档摄像机缩进视眼
	 const string m_strDocZoonEdit;							//文档摄像机视眼编辑框
	 const string m_strDocAperture;							//文档摄像机光圈
	 const string m_strDocExposureGain;						//文档摄像机增益
	 const string m_strDocShutter;							//文档摄像机快门
	 const string m_strDocPreset;							//文档摄像机开机调用预置位1
	 const string m_strDocLastState;						//文档摄像机上一次状态
	 const string m_strDocAutoFocus;						//文档摄像机自动焦距
	 const string m_strDocManualFocus;						//文档摄像机手动焦距
	 const string m_strDocFocusNear;						//文档摄像机焦距拉近
	 const string m_strDocFocusAway;						//文档摄像机焦距拉远	
	 const string m_strDocAutoExposure;						//文档摄像机自动曝光开关
	 const string m_strDocAutoWB;							//文档摄像机自动白平衡开关
	 const string m_strDocRGainSlider;						//文档摄像机白平衡R增益
	 const string m_strDocRGainEdit;						//文档摄像机白平衡R增益编辑框
	 const string m_strDocBGainSlider;						//文档摄像机白平衡B增益
	 const string m_strDocBGainEdit;						//文档摄像机白平衡B增益编辑框
     const string m_strCMASwitchBtn;						//CMA300摄像机开关

	 u8				 m_byPanCamNum;							//全景摄像机数量
	 TPanCamInfo     m_tQCamInfo;
	 TCentreDCamCfg  m_tDCamInfo;
	 const string StrDocCamExistSch;
	 const string StrDocCamNonExistSch;
};

#endif // !defined(AFX_CENTCFGCAMERADLG_H__4EF58907_60FB_4087_A492_755896396F1A__INCLUDED_)
