// MoonAdjustDlg.h: interface for the CMoonAdjustDlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOONADJUSTDLG_H__7481DAC9_C5BC_4E5F_83A4_F91E5016E6B1__INCLUDED_)
#define AFX_MOONADJUSTDLG_H__7481DAC9_C5BC_4E5F_83A4_F91E5016E6B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

class CMoonAdjustDlg  : public CLogicBase, public ISingleTon<CMoonAdjustDlg>
{
public:
	CMoonAdjustDlg();
	virtual ~CMoonAdjustDlg();
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
	/** 功能: 设置参考线
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/
	bool OnRefLineSwitchBtnChange( const IArgs & arg );
	/** 功能: 设置梯形矫正
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/
	bool OnTraCorSwitchBtnChange( const IArgs & arg );
	/** 功能: 设置水平翻转
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/
	bool OnHorFlipSwitchBtnChange( const IArgs & arg );
	/** 功能: 快照
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/
	bool OnSnapShotBtnClick( const IArgs & arg );
	/** 功能: 快照另存为
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/
	bool OnSnapShotSaveBtnClick( const IArgs & arg );
	/** 功能: 按下水平矫正减少幅度按钮后
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/
	bool OnBtnHorCorReduceHold( const IArgs & arg );
	/** 功能: 松开水平矫正减少幅度按钮
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/
	bool OnBtnHorCorReduceHoldEnd( const IArgs & arg );
	/** 功能: 水平矫正编辑框值发生变化
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/
	bool OnHorCorEditChange( const IArgs & arg );
	
	/** 功能: 水平矫正编辑框值失去焦点
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/
	bool OnHorCorEditKillFocus( const IArgs & arg );

	bool OnBtnHorCorIncreaseHoldEnd( const IArgs & arg );
	bool OnBtnHorCorIncreaseHold( const IArgs & arg );

	bool OnBtnHorStrReduceHold( const IArgs & arg );
	bool OnBtnHorStrReduceHoldEnd( const IArgs & arg );
	/** 功能: 水平拉伸编辑框值发生变化
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/
	bool OnHorStrEditChange( const IArgs & arg );
	/** 功能: 水平拉伸编辑框值失去焦点
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/
	bool OnHorStrEditKillFocus( const IArgs & arg );
	bool OnBtnHorStrIncreaseHold( const IArgs & arg );
	bool OnBtnHorStrIncreaseHoldEnd( const IArgs & arg );

	bool OnBtnVerCorReduceHold( const IArgs & arg );
	bool OnBtnVerCorReduceHoldEnd( const IArgs & arg );
	bool OnContrastAreaBtnClick( const IArgs & arg );
	bool OnCorrectParaBtnClick( const IArgs & arg );
	bool OnAutoCalculateBtnClick( const IArgs & arg );
	bool OnRgbConsisSwitchBtnChange( const IArgs & arg );  //颜色一致性开关
	/************     左图增益     ************/

	//左图R
	bool OnRLeftReduceBtnClick( const IArgs & arg );
	bool OnRLeftCorEditChange( const IArgs & arg );
	bool OnRLeftCorEditKillFocus( const IArgs & arg );
	bool OnRLeftIncreaseBtnClick( const IArgs & arg );

	//左图G
	bool OnGLeftReduceBtnClick( const IArgs & arg );
	bool OnGLeftCorEditChange( const IArgs & arg );
	bool OnGLeftCorEditKillFocus( const IArgs & arg );
	bool OnGLeftIncreaseBtnClick( const IArgs & arg );
	
	//左图B
	bool OnBLeftReduceBtnClick( const IArgs & arg );
	bool OnBLeftCorEditChange( const IArgs & arg );
	bool OnBLeftCorEditKillFocus( const IArgs & arg );
    bool OnBLeftIncreaseBtnClick(  const IArgs & arg );

	/************     中图增益     ************/

	//中图R
	bool OnRMidReduceBtnClick( const IArgs & arg );
	bool OnRMidCorEditChange( const IArgs & arg );
	bool OnRMidCorEditKillFocus( const IArgs & arg );
	bool OnRMidIncreaseBtnClick( const IArgs & arg );

	//中图G
	bool OnGMidReduceBtnClick( const IArgs & arg );
	bool OnGMidCorEditChange( const IArgs & arg );
	bool OnGMidCorEditKillFocus( const IArgs & arg );
	bool OnGMidIncreaseBtnClick( const IArgs & arg );

	//中图B
	bool OnBMidReduceBtnClick( const IArgs & arg );
	bool OnBMidCorEditChange( const IArgs & arg );
	bool OnBMidCorEditKillFocus( const IArgs & arg );
	bool OnBMidIncreaseBtnClick( const IArgs & arg );

	/************     右图增益     ************/

	//右图R
	bool OnRRightReduceBtnClick( const IArgs & arg );
	bool OnRRightCorEditChange( const IArgs & arg );
    bool OnRRightCorEditKillFocus( const IArgs & arg );
	bool OnRRightIncreaseBtnClick( const IArgs & arg );

	//右图G
	bool OnGRightReduceBtnClick( const IArgs & arg );
	bool OnGRightCorEditChange( const IArgs & arg );
	bool OnGRightCorEditKillFocus( const IArgs & arg );
	bool OnGRightIncreaseBtnClick( const IArgs & arg );

	//右图B
	bool OnBRightReduceBtnClick( const IArgs & arg );
	bool OnBRightCorEditChange( const IArgs & arg );
	bool OnBRightCorEditKillFocus( const IArgs & arg );
	bool OnBRightIncreaseBtnClick( const IArgs & arg );

	/** 功能: 垂直矫正编辑框值发生变化
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/
	bool OnVerStrEditChange( const IArgs & arg );
	/** 功能: 垂直矫正编辑框值失去焦点
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/
	bool OnVerCorEditKillFocus( const IArgs & arg );

	bool OnBtnVerCorIncreaseHold( const IArgs & arg );
	bool OnBtnVerCorIncreaseHoldEnd( const IArgs & arg );

	bool OnBtnVerStrReduceHold( const IArgs & arg );
	bool OnBtnVerStrReduceHoldEnd( const IArgs & arg );

	/** 功能: 垂直拉伸编辑框值发生变化
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/
	bool OnVerCorEditChange( const IArgs & arg );
	/** 功能: 垂直拉伸编辑框值失去焦点
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/
	bool OnVerStrEditKillFocus( const IArgs & arg );

	bool OnBtnVerStrIncreaseHold( const IArgs & arg );
	bool OnBtnVerStrIncreaseHoldEnd( const IArgs & arg );


	/************     延时矫正     ************/
	//左图
    bool OnLeftDelayReduceBtnClick( const IArgs & arg );
	bool OnLeftDelayCorEditChange( const IArgs & arg );
	bool OnLeftDelayCorEditKillFocus( const IArgs & arg );
	bool OnLeftDelayIncreaseBtnClick( const IArgs & arg );

	//中图
    bool OnMiddleDelayReduceBtnClick( const IArgs & arg );
	bool OnMiddleDelayCorEditChange( const IArgs & arg );
	bool OnMiddleDelayCorEditKillFocus( const IArgs & arg );
	bool OnMiddleDelayIncreaseBtnClick( const IArgs & arg );

	//右图
	bool OnRightDelayReduceBtnClick( const IArgs & arg );
	bool OnRightDelayCorEditChange( const IArgs & arg );
	bool OnRightDelayCorEditKillFocus( const IArgs & arg );
	bool OnRightDelayIncreaseBtnClick( const IArgs & arg );

	LRESULT OnSnapShotNty( WPARAM wparam, LPARAM lparam );


	/** 功能: 更新界面显示
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/
	HRESULT OnTralCorParamInd( WPARAM wparam, LPARAM lparam );
	/** 功能: 参考线设置通知
	*  @param[in] lparam 是否成功
	*  @return 
	*  @remarks  
	*/
	HRESULT OnReferenceLineInd( WPARAM wparam, LPARAM lparam );

	/** 功能: 水平翻转设置通知
	*  @param[in] lparam 是否成功
	*  @return 
	*  @remarks  
	*/
	HRESULT OnHorizontalFlipInd( WPARAM wparam, LPARAM lparam );
	/** 功能: 梯形矫正设置通知
	*  @param[in] lparam 是否成功
	*  @return 
	*  @remarks  
	*/
	HRESULT OnTrapezoidalCorInd( WPARAM wparam, LPARAM lparam );

	HRESULT OnCameraSelectInd( WPARAM wparam, LPARAM lparam );

	HRESULT OnSetCamDistortParamInd( WPARAM wparam, LPARAM lparam );

	HRESULT OnTraCorValueInd( WPARAM wparam, LPARAM lparam );

	HRESULT OnSecBoundaryNty( WPARAM wparam, LPARAM lparam );
	
	HRESULT OnSetChangeSideRGBNty( WPARAM wparam, LPARAM lparam );

	HRESULT OnSetDefaultParamNty( WPARAM wparam, LPARAM lparam );

	HRESULT OnSetColorRGBInd( WPARAM wparam, LPARAM lparam );

	HRESULT OnSetDirectColorRGBInd( WPARAM wparam, LPARAM lparam );

	HRESULT OnSetAutoColConstancyInd( WPARAM wparam, LPARAM lparam );
	
	HRESULT OnShowRectRegionInd( WPARAM wparam, LPARAM lparam );

	HRESULT OnSetOnColorSwitchInd( WPARAM wparam, LPARAM lparam );

	/** 功能: 延时矫正设置通知
	*  @param[in] lparam 是否成功
	*  @return 
	*  @remarks  
	*/
    HRESULT OnSetDelayCorrectInd( WPARAM wparam, LPARAM lparam );

	HRESULT OnSetDelayCorrectNty( WPARAM wparam, LPARAM lparam );
private:
	bool SetSnapShotImage( const string strFileName );
	/** 功能: 设置梯形矫正的参数
	*  @param[in] emTpMyOption 参数类型    dwValue 参数值
	*  @return 
	*  @remarks  
	*/
	void SetTraCorrectionParam( EmTPCorrect emTpMyOption , TTPDistortParam &tTraCorParam );
	/** 功能: 释放被程序占用且不被使用的图片资源
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/
	void ReleaseSnapImage();
		/** 功能: 更新编辑框的数值，防止超过边界及出现0开始的数值
	*  @param[in] strEditName 对应XML中的控件名称 nMaxValue 对应界面显示最大值
	*  @return 
	*  @remarks  
	*/
	void UpdateEditNum( const IArgs & arg, String strEditName ,s32 nMaxValue ,s32 nMinValue);
	
	/** 功能:获取快照名称
	*  @param[in] strFileName 初始快照名称
	*  @return  获取快照名称，如果第一组被使用，会在快照名称中添加TEMP头
	*  @remarks  
	*/
	string GetSnapShotFileName( const string strFileName );
	/** 功能: 下载文件
	*  @param[in] strFilePath 服务器文件所在路径 strFileName 下载文件名
	*  @return 
	*  @remarks  
	*/
	BOOL DownloadCore(const String& strFilePath,const String & strFileName );

	bool OnDownloadProgress( const IArgs & arg );

	void CopyImage( string strCopyPath, string strSavePath );

public:
	void CopyFile( string strCopyFilePath, string strSaveFilePath );

private:
	void UpdateColorRGBVal( TTPColorCoeff tTPColorCoeff);
	void SetRGBColorValCmd( CString str, u8 nPosition, EmTPColorConsistency emMyColorOption );

	float StringToFloatThree( CString str );
	CString OnlyFloat( CString str );


private:
	const string m_strRefLineSwitchBtn;							 //参考线开关
	const string m_strHorFlipSwitchBtn;							 //水平翻转开关
	const string m_strTraCorSwitchBtn;							 //梯形矫正开关
	const string m_strRgbConsisSwitchBtn;                        //颜色一致性开关
	const String m_strSchemeEnable;                              //可以使用梯形矫正功能模式
	const String m_strSchemeDisable;                             //禁用梯形矫正功能模式
	const string m_strHorCorEdit;                                //保存XML中水平矫正编辑框的字符串
	const string m_strHorStrEdit;                                //保存XML中水平拉伸编辑框的字符串
	const string m_strVerCorEdit;                                //保存XML中垂直矫正编辑框的字符串
	const string m_strVerStrEdit;                                //保存XML中垂直拉伸编辑框的字符串
	//颜色RGB一致性
	const string m_strRLeftCorEdit;
	const string m_strGLeftCorEdit;
	const string m_strBLeftCorEdit;
	const string m_strRMidCorEdit;
	const string m_strGMidCorEdit;
	const string m_strBMidCorEdit;
	const string m_strRRightCorEdit;
	const string m_strGRightCorEdit;
	const string m_strBRightCorEdit;
	//延时矫正
    const string m_strLeftDelayCorEdit;
	const string m_strMiddleDelayCorEdit;
	const string m_strRightDelayCorEdit;

	std::map<string,s32> m_mapMaxValue;                          //保存XML中编辑框的字符串及对应的界面最大值
	std::map<string,s32> m_mapMinValue;
	CFtpCtrl m_cFtp;
	std::vector<string>  m_vecFilePath;                          //保存下载文件目录
	std::vector<string>  m_vecDownFile;                          //保存未下载文件名
	std::vector<string>  m_vecShatShot;                          //对应界面快照控件
	BOOL m_bIsFirstGroupUsed;                                    //是否使用第一组快照图片
	BOOL m_bRefLineOpen;										//是否开启参考线
	BOOL m_bHorFlipOpen;										//是否开启水平翻转
	BOOL m_bTraCorOpen;											//是否开启梯形矫正
	BOOL m_bIsSaveAsSnapShot;								    //是否重命名
	TTPDistortParam     m_tHorParam;                            // 保存水平参数
	TTPDistortParam     m_tVerParam;                            // 保存垂直参数
	EmFtpStatus m_emFileFtpStatus;
	BOOL       m_bIsOption;                                     //是否进行过快照操作
};

#endif // !defined(AFX_MOONADJUSTDLG_H__7481DAC9_C5BC_4E5F_83A4_F91E5016E6B1__INCLUDED_)
