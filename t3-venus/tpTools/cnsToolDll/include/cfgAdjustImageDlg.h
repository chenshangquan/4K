// cfgAdjustImageDlg.h: interface for the CCfgAdjustImageDlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CFGADJUSTIMAGEDLG_H__0C555072_4A50_410D_9C03_0F25A01041FD__INCLUDED_)
#define AFX_CFGADJUSTIMAGEDLG_H__0C555072_4A50_410D_9C03_0F25A01041FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCfgAdjustImageDlg : public CLogicBase, public ISingleTon<CCfgAdjustImageDlg>
{
public:
	CCfgAdjustImageDlg();
	virtual ~CCfgAdjustImageDlg();
public:	 
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
	/* 功能: 获取界面上数据变化控件的数目
	* @return   bool
	* @remarks  
	*/
	s32 GetCtrlChangeNum() { return m_vctWndName.size(); }
	HRESULT OnUpdateParameterNty( WPARAM wparam, LPARAM lparam );

	HRESULT OnDefaultParameterNty( WPARAM wparam, LPARAM lparam );

	bool OnBtnSave( const IArgs& args );

	bool OnBtnCancel( const IArgs& args );

	bool OnBtnDefault( const IArgs& args );

	bool IsCfgParameterChange();

//	bool OnSliderColor1Changed( const IArgs& args );
//	bool OnfEditColor1Changed( const IArgs& args );

	bool OnSliderBrightness1Changed( const IArgs& args );
	bool OnEditBrightness1Changed( const IArgs& args );

	bool OnSliderSaturation1Changed( const IArgs& args );
	bool OnEditSaturation1Changed( const IArgs& args );

	bool OnSliderContrast1Changed( const IArgs& args );
	bool OnEditContrast1Changed( const IArgs& args );

//	bool OnSliderColor2Changed( const IArgs& args );
//	bool OnfEditColor2Changed( const IArgs& args );

	bool OnSliderBrightness2Changed( const IArgs& args );
	bool OnEditBrightness2Changed( const IArgs& args );

	bool OnSliderSaturation2Changed( const IArgs& args );
	bool OnEditSaturation2Changed( const IArgs& args );

	bool OnSliderContrast2Changed( const IArgs& args );
	bool OnEditContrast2Changed( const IArgs& args );

//	bool OnSliderColor3Changed( const IArgs& args );
//	bool OnfEditColor3Changed( const IArgs& args );

	bool OnSliderBrightness3Changed( const IArgs& args );
	bool OnEditBrightness3Changed( const IArgs& args );

	bool OnSliderSaturation3Changed( const IArgs& args );
	bool OnEditSaturation3Changed( const IArgs& args );

	bool OnSliderContrast3Changed( const IArgs& args );
	bool OnEditContrast3Changed( const IArgs& args );

	bool OnEditSaturation1KillFocus( const IArgs& args );
	bool OnEditBrightness1KillFocus( const IArgs& args );
	bool OnEditContrast1KillFocus( const IArgs& args );
	bool OnEditSaturation2KillFocus( const IArgs& args );
	bool OnEditBrightness2KillFocus( const IArgs& args );
	bool OnEditContrast2KillFocus( const IArgs& args );
	bool OnEditBrightness3KillFocus( const IArgs& args );
	bool OnEditSaturation3KillFocus( const IArgs& args );
	bool OnEditContrast3KillFocus( const IArgs& args );
private:
	void UpdateGainNum( String strGainName, String strEditName, u8 byGain );

	void UpdateGainEdit( String strEditName, String strSliderName, u8 byGain );

	void UpdateEditDate( String strEditName, String strSliderName, u8 byGain );

	void SetDefaultParameter();

	void SetImageParameterDate();

	void GetImageParameterData();

	bool SaveMsgBox();
	bool CheckBrightness();
	bool CheckSaturation();
	bool CheckContrast();
private:
//	String			m_strDenoise[3];

//	String			m_strImageColorSlider[3];
//	String			m_strImageColorEdit[3];

	String			m_strBrightnessSlider[3];
	String			m_strBrightnessEdit[3];

	String			m_strSaturationSlider[3];
	String			m_strSaturationEdit[3];

	String			m_strContrastSlider[3];
	String			m_strContrastEdit[3];

	TTPImageAdjustParam m_aOldtImageAdjust[3];
	TTPImageAdjustParam m_aCurtImageAdjust[3];
	const u8		m_byMaxGain;
};

#endif // !defined(AFX_CFGADJUSTIMAGEDLG_H__0C555072_4A50_410D_9C03_0F25A01041FD__INCLUDED_)
