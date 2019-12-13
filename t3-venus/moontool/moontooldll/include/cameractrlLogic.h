/*****************************************************************************
模块名      : CCameraCtrlLogic
文件名      : cameractrlLogic.h
相关文件    : 
文件实现功能: 摄像机配置页面
作者        : 吴蒨蒨
版本        : V1.0  Copyright(C) 2013-2014 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2014/12/3      1.0         吴蒨蒨			创建
******************************************************************************/
#if !defined(AFX_CAMERACTRLLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
#define AFX_CAMERACTRLLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

#define ZOOM_MAX_LIMIT  31424  //ZOOM调节范围最大限值

class CCameraCtrlLogic : public CLogicBase, public ISingleTon<CCameraCtrlLogic>
{
public:
	CCameraCtrlLogic();
	virtual ~CCameraCtrlLogic();


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
	* 功能:  清空所有状态和数据
	* @return   
	* @remarks	 
	*/
    virtual void Clear();

	/**	 
	* 功能:  恢复界面控件状态    by xhx
	* @return   
	* @remarks	 
	*/
    void ResetNormal();

	String GetCamMechnismStyle();

protected:
	/**	 
	* 功能:  单击ComboboxCamera某项的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnComboboxCameraClick( const IArgs& args );
	
	/**	 
	* 功能:  单击ComboboxCameraStyle某项的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnComboboxCameraStyleClick( const IArgs& args );


	/**	 
	* 功能:  单击BtnSync的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnSyncClick( const IArgs& args );

    /**	 
	* 功能:  单击ComboboxOutputFormat的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnComboboxOutputFormatClick( const IArgs& args );

	/**	 
	* 功能:  单击BtnZoomPlus的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnZoomPlusClick( const IArgs& args );	

	/**	 
	* 功能:  单击BtnZoomSub的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnZoomSubClick( const IArgs& args );

	/**	 
	* 功能: BtnZoomPlusHold的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnLBtnDownZoomPlus( const IArgs& args );

	bool OnLBtnDoubleDownZoomPlus( const IArgs& args );

	/**	 
	* 功能: BtnZoomPlusHoldEnd的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnLBtnUpZoomPlus( const IArgs& args );

	/**	 
	* 功能: BtnZoomSubHold的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnLBtnDownZoomSub( const IArgs& args );

	bool OnLBtnDoubleDownZoomSub( const IArgs& args );

	/**	 
	* 功能: BtnZoomSubHoldEnd的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnLBtnUpZoomSub( const IArgs& args );
	
	/**	 
	* 功能:  单击BtnManuelFocus的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnManuelFocusClick( const IArgs& args );

	/**	 
	* 功能:  单击BtnAutoFocus的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnAutoFocusClick( const IArgs& args );

	/**	 
	* 功能:  BtnFocusNear的LBtnDown的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnLBtnDownFocusNear( const IArgs& args );

	/**	 
	* 功能:  BtnFocusNear的LBtnUp的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnLBtnUpFocusNear( const IArgs& args );

	/**	 
	* 功能:  BtnFocusFar的LBtnDown的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnLBtnDownFocusFar( const IArgs& args );

	/**	 
	* 功能:  BtnFocusFar的LBtnUp的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnLBtnUpFocusFar( const IArgs& args );

    /**	 
	* 功能:  BtnSwitchManuelApertre的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnSwitchManuelApertre( const IArgs& args );

    /**	 
	* 功能:  BtnSwitchAutoApertre的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnSwitchAutoApertre( const IArgs& args );

    /**	 
	* 功能:  BtnSwitchAutoApertre的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnComboboxApertreClick( const IArgs& args );

    /**	 
	* 功能:  单击BtnSwitchManuelExposure的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnSwitchManuelExposure( const IArgs& args );

	/**	 
	* 功能:  单击BtnSwitchAutoExposure的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnSwitchAutoExposure( const IArgs& args );

	/**	 
	* 功能:  光圈下拉框
	* @return   bool
	* @remarks	 
	*/
	bool OnComboboxApertureClick( const IArgs& args );

    /**	 
	* 功能:  单击BtnExpGainPlus的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnLBtnClickExpGainPlus( const IArgs& args );

    /**	 
	* 功能:  单击BtnExpGainSub的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnLBtnClickExpGainSub( const IArgs& args );

    /**	 
	* 功能:  单击EdtExpGainChange的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnEdtExpGainChange( const IArgs& args );

    /**	 
	* 功能:  单击EdtExpGainKillFocus的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnEdtExpGainKillFocus( const IArgs& args );

    /**	 
	* 功能:  单击BtnSwitchManuelWB的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnSwitchManuelWB( const IArgs& args );

	/**	 
	* 功能:  单击BtnSwitchAutoWB的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnSwitchAutoWB( const IArgs& args );

	/**	 
	* 功能:  SliderRGain值改变的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnSliderRGainChanged( const IArgs& args );

	/**	 
	* 功能:  SliderBGain值改变的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnSliderBGainChanged( const IArgs& args );

	/**	 
	* 功能:  SliderContrast值改变的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnSliderContrastChanged( const IArgs& args );

	/**	 
	* 功能:  SliderContrast值改变的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnSliderSaturatChanged( const IArgs& args );

	/**	 
	* 功能:  SliderSharp值改变的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnSliderSharpChanged( const IArgs& args );

	/**	 
	* 功能:  SliderBright值改变的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnSliderBrightChanged( const IArgs& args );

    /**	 
	* 功能:  SliderTone值改变的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnSliderHueChanged( const IArgs& args );

	/**	 
	* 功能: 单击ComboboxExposureGain某一项的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnComboboxExposureGainClick( const IArgs& args );

	/**	 
	* 功能: 单击ComboboxShut某一项的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnComboboxShutClick( const IArgs& args );

	/**	 
	* 功能: EdtRGain改变的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnEdtRGainChange( const IArgs& args );

	/**	 
	* 功能: EdtRGain失去焦点的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnKillFocusEdtRGain( const IArgs& args );

	/**	 
	* 功能: EdtBGain改变的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnEdtBGainChange( const IArgs& args );

	/**	 
	* 功能: EdtBGain失去焦点的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnKillFocusEdtBGain( const IArgs& args );

	/**	 
	* 功能: EdtContrast改变的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnEdtContrastChange( const IArgs& args );

	/**	 
	* 功能: EdtContrast失去焦点的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnKillFocusEdtContrast( const IArgs& args );

	/**	 
	* 功能: EdtSaturat改变的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnEdtSaturatChange( const IArgs& args );

	/**	 
	* 功能: EdtSaturat失去焦点的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnKillFocusEdtSaturat( const IArgs& args );

	/**	 
	* 功能: EdtColor锐度改变的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnEdtSharpChange( const IArgs& args );

	/**	 
	* 功能: EdtColor锐度失去焦点的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnKillFocusEdtSharp( const IArgs& args );
	
	/**	 
	* 功能: EdtBright改变的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnEdtBrightChange( const IArgs& args );

	/**	 
	* 功能: EdtBright失去焦点的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnKillFocusEdtBright( const IArgs& args );

    /**	 
	* 功能: EdtHue改变的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnEdtHueChange( const IArgs& args );

	/**	 
	* 功能: EdtHue失去焦点的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnKillFocusEdtHue( const IArgs& args );

	/**	 
	* 功能: EdtZoom改变的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnEdtZoomChange( const IArgs& args );

	/**	 
	* 功能: EdtZoom失去焦点的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnEdtZoomKillFocus( const IArgs& args );
	
	/**	 
	* 功能: 背光补偿是否开启按钮
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnSwitchLightPensationClick( const IArgs& args );

	/**	 
	* 功能: 降噪是否开启
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnSwitchNRClick( const IArgs& args );

	bool OnComboboxNRClick( const IArgs& args );

	bool OnBtnSwitch2DNRClick( const IArgs& args );
	
	bool OnCombobox2DNRClick( const IArgs& args );

	bool OnBtnSwitch3DNRClick( const IArgs& args );
	
	bool OnCombobox3DNRClick( const IArgs& args );

	/**	 
	* 功能: 是否开机调用预置位1
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnSwitchOrderPosClick( const IArgs& args );

	/**	 
	* 功能: 点击升级响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnUpdateVersion( const IArgs& args );

	/**	 
	* 功能: 点击预置位列表按钮响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnOrderPosList( const IArgs& args );

	/**	 
	* 功能: 保存参数按钮响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnSaveParam( const IArgs& args );

	bool OnBtnSwitchKeyStoneAdjust( const IArgs& args );

	bool OnBtnCheckBackLightClick( const IArgs& args );

	bool OnSliderAdjustRangeChanged( const IArgs& args );

	bool OnSliderHoriStretchChanged( const IArgs& args );

	bool OnEdtAdjustRangeChange( const IArgs& args );

	bool OnKillFocusEdtAdjustRange( const IArgs& args );

	bool OnEdtHoriStretchChange( const IArgs& args );

	bool OnKillFocusEdtHoriStretch( const IArgs& args );

	bool OnComboboxGammaClick( const IArgs& args );

    bool OnComboboxOrderPosClick( const IArgs& args );

    bool OnBtnImportParam( const IArgs& args );

    bool OnBtnExportParam( const IArgs& args );

protected:
	/**	 
	* 功能:  响应服务器发来的UI_CNSTOOL_CAMERA_CFG_NTY的函数
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraCfgNty( WPARAM wparam, LPARAM lparam );

	/**	 
	* 功能:  响应服务器发来的UI_TpMechanismSelect_NTY的函数
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnTpMechanismSelectNty( WPARAM wparam, LPARAM lparam );

	/**	 
	* 功能:  响应服务器发来的UI_TpMechVer_NTY的函数
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnTpMechVerNty( WPARAM wparam, LPARAM lparam );

	/**	 
	* 功能:  响应服务器发来的UI_MOONTOOL_CamStyleSel_IND的函数
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraStyleSelectInd( WPARAM wparam, LPARAM lparam );
	
    /**	 
	* 功能:  响应服务器发来的UI_MOONTOOL_OUTPUT_FORMAT_RSP的函数
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraOutputFormatRsp( WPARAM wparam, LPARAM lparam );

	/**	 
	* 功能:  响应服务器发来的UI_CNSTOOL_CAMERA_SELECT_IND的函数
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraSelectInd( WPARAM wparam, LPARAM lparam );

	/**	 
	* 功能:  响应服务器发来的UI_MOONTOOL_CamParamSync_IND的函数
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCamParamSyncInd( WPARAM wparam, LPARAM lparam );
	
	/**	 
	* 功能:  响应服务器发来的UI_CNSTOOL_CAMERA_ZOOM_IND的函数
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraZoomInd( WPARAM wparam, LPARAM lparam );

	/**	 
	* 功能:  响应服务器发来的UI_CNSTOOL_CAMERA_AUTO_FOCUS_IND的函数
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraAutoFocusInd( WPARAM wparam, LPARAM lparam );
	
	/**	 
	* 功能:  响应服务器发来的UI_CNSTOOL_CAMERA_FOCUS_IND的函数
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraFocusInd( WPARAM wparam, LPARAM lparam );

	/**	 
	* 功能:  响应服务器发来的UI_CNSTOOL_CAMERA_PERSET_MOVE_IND的函数
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraPersetMoveInd( WPARAM wparam, LPARAM lparam );

	/**	 
	* 功能: 响应服务器发来的UI_MOONTOOL_CAMERA_APERTRE_RSP的函数
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnApertreRsp( WPARAM wparam, LPARAM lparam );

    /**	 
	* 功能: 响应服务器发来的UI_MOONTOOL_CAMERA_AUTO_EXPOSURE_IND的函数
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnAutoExposureInd( WPARAM wparam, LPARAM lparam );
	
	/**	 
	* 功能:  响应服务器发来的UI_CNSTOOL_CAMERA_GAIN_IND的函数
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraGainInd( WPARAM wparam, LPARAM lparam );
	
	/**	 
	* 功能:  响应服务器发来的UI_CNSTOOL_CAMERA_SHUT_SPD_IND的函数
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraShutSpdInd( WPARAM wparam, LPARAM lparam );
	
	/**	 
	* 功能:  响应服务器发来的UI_CNSTOOL_CAMERA_BACK_LIGHT_IND的函数
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCamLightPensationInd( WPARAM wparam, LPARAM lparam );

	/**	 
	* 功能:  响应服务器发来的UI_CNSTOOL_CAMERA_APERTURE_IND的函数
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraApertureInd( WPARAM wparam, LPARAM lparam );

	/**	 
	* 功能:  响应服务器发来的UI_CNSTOOL_CAMERA_AUTO_WB_IND的函数
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraAutoWBInd( WPARAM wparam, LPARAM lparam );
	
	/**	 
	* 功能:  响应服务器发来的UI_CNSTOOL_CAMERA_RGAIN_IND的函数
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraRGainInd( WPARAM wparam, LPARAM lparam );
	
	/**	 
	* 功能:  响应服务器发来的UI_CNSTOOL_CAMERA_BGAIN_IND的函数
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraBGainInd( WPARAM wparam, LPARAM lparam );
	
	/**	 
	* 功能:  响应服务器发来的UI_CNSTOOL_CAMERA_CONTRAST_IND的函数
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraBrightInd( WPARAM wparam, LPARAM lparam );

	/**	 
	* 功能:  响应服务器发来的UI_CNSTOOL_IMAGEPARA_IND的函数
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraImageParaInd( WPARAM wparam, LPARAM lparam );

	/**	 
	* 功能:  响应服务器发来的UI_CNSTOOL_CAMERA_CONTRAST_IND的函数
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraContrastInd( WPARAM wparam, LPARAM lparam );

	/**	 
	* 功能:  锐度调节结果反馈
	* @return   LRESULT
	* @remarks	 
	*/	
	HRESULT OnCameraSharpInd( WPARAM wparam, LPARAM lparam );

	/**	 
	* 功能:  饱和度调节结果反馈
	* @return   LRESULT
	* @remarks	 
	*/	
	HRESULT OnCameraSaturatInd( WPARAM wparam, LPARAM lparam );

	/**	 
	* 功能:  背光补偿设置结果反馈
	* @return   LRESULT
	* @remarks	 
	*/	
	HRESULT OnCameraBackLightInd( WPARAM wparam, LPARAM lparam );
	
	/**	 
	* 功能:  响应服务器发来的UI_CNSTOOL_CAMERA_NR_IND的函数
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraNRInd( WPARAM wparam, LPARAM lparam );

	/**	 
	* 功能:  响应服务器发来的UI_CNSTOOL_CAMERA_2DNR_IND的函数
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCamera2DNRInd( WPARAM wparam, LPARAM lparam );

	/**	 
	* 功能:  响应服务器发来的UI_CNSTOOL_CAMERA_3DNR_IND的函数
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCamera3DNRInd( WPARAM wparam, LPARAM lparam );

	HRESULT OnCamOrderPosSelInd( WPARAM wparam, LPARAM lparam );

	HRESULT OnCamOutputInfoNty( WPARAM wparam, LPARAM lparam );

	HRESULT OnCamOutputInfoInd( WPARAM wparam, LPARAM lparam );

	HRESULT OnCamParameterDefaultInd( WPARAM wparam, LPARAM lparam );

	/**	 
	* 功能:  响应服务器发来的UI_CNSTOOL_CAMERA_RESET_IND的函数
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraResetInd( WPARAM wparam, LPARAM lparam );
	
	/**	 
	* 功能:  响应服务器发来的UI_CNSTOOL_CAMERA_PERSET_SAVE_IND的函数
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnCameraPersetSaveInd( WPARAM wparam, LPARAM lparam );

	/**	 
	* 功能:  响应服务器发来的UI_CNSTOOL_SET_CAMERA_ZOOM_IND的函数
	* @return   LRESULT
	* @remarks	 
	*/
	HRESULT OnSetCameraZoomInd( WPARAM wparam, LPARAM lparam );

	HRESULT OnSetCamDistortParamInd( WPARAM wparam, LPARAM lparam );

	HRESULT OnSetCamAutoFocusInd( WPARAM wparam, LPARAM lparam );

    /**	 
	* 功能:  预置位1保存结果界面通知
	* @return   LRESULT
	* @remarks	 
	*/
    HRESULT OnCamPreSet1SaveRsp( WPARAM wparam, LPARAM lparam );

public:
    void GetShutSpdValue( EmTPSOrThShutter &emShutSpd );
	void GetTwShutterValue( EmTPFOrTwShutter &emTwShutter );

private:
    void SetOutputFormatValue( TPOutputFmt &tOutputFmt );
	void GetApertureValue(EmTPAperture &emAper);
	void SetApertureValue(TIrisAutoManuMode &tAperMode);
	void GetExpGainValue( EmTPExpGain &emGain );
	void SetExpGainValue( u8 byExpGain );
	void SetShutSpdValue(  TPSOrThShutter tTPShutSpd );
	void SetTwShutterValue( TPFOrTwShutter tTPTwShutter );
	void SetAutoWB( EmTPMOOMMode emWBMode );
	void SetAutoExp( EmTPMOOMMode emExpMode );
	void SetCameraCfg( TTPMoonCamInfo tMoonCameraCfg );
	void SetAptValue( u8 byApt );
	void SetPresetValue( BOOL bUsed );
	void SetCamName( CString strCaption );
	void SetCamStyleName( CString strCaption );
	void SetGammaName( CString strCaption );
	void SetRGainValue( u32 dwRGain );
	void SetBGainValue( u32 dwBGain );
	void SetAdjustRangeValue( u32 dwAdjustRange );
	void SetHoriStretchValue( u32 dwHoriStretch );
	void SetContrastValue( u32 dwContrast );
	void SetSaturatValue( u32 dwSaturat );
	void SetSharpValue( u32 dwSharp );
	void SetBrightValue( u32 dwBright );
    void SetHueValue( u32 dwHue );
	void GetNRValue(EmTPFpgaReduNoise &emTPReduNoise);
	void Get2DNRValue(EmTPReduNoise &emTPReduNoise);
	void Get3DNRValue(EmTPReduNoise &emTPReduNoise);
 	void SetNRValue( EmTPFpgaReduNoise emReduNoise );
	void Set2DNRValue( TCamD2NRMode tCam2DNRMode );
	void Set3DNRValue( TCamD3NRMode tCam3DNRMode );
	void SetFocusState( EmTPMOOMMode emFocusMode );
    void SetApertreState( EmTPMOOMMode emApertreMode );
	void SetLightPensationValue( BOOL bUsed );
	void SetKeyStoneAdjust( BOOL bUsed );
	void SetGammaValue(EmH650Gamma emGamma);
	void SetMechVersion( s8 *achSwVersion, s8 *achHwVersion );
 
	float StringToFloatThree( CString str );
	CString OnlyFloat( CString str );

	void SetZoomValue( u32 dwZoom );
	void SetH650ZoomValue(u32 dwZoom, u32 dwZoomPos);
	void SetZoomCmd( CString str );
	void SetApertureCmd( CString str );
	void SetRGainCmd( CString str );
	void SetBGainCmd( CString str );
	void SetAdjustRangeCmd( CString str );
	void SetHoriStretchCmd( CString str );
	void SetPicSceAptCmd( CString str );
	void SetContrastCmd( CString str );
	void SetSaturatCmd( CString str );
	void SetHueCmd( CString str );
	void SetBrightCmd( CString str );
	void SetShutComboxData();
	void showCameraInfo(EmTPMechanism emCamType, bool bHide);

private:
	//该逻辑单元对应的所有控件名
	const String m_strStcLineImagePara;
	const String m_strStcImageParam;
	const String m_strStcLineBright;
	const String m_strStcBright;
	const String m_strStcLineSaturat;
	const String m_strStcSaturat;
	const String m_strStcLineContrast;
	const String m_strStcContrast;
	const String m_strStcLineSharp;
	const String m_strStcSharp;
	const String m_strStcLineGamma;
	const String m_strStcGamma;
	const String m_strStcVersion;
	const String m_strStcVersionNum;
	const String m_strBtnUpdateVersion;
	const String m_strComboboxCamera;
	const String m_strComboboxCameraStyle;
    const String m_strComboboxOutputFormat;
	const String m_strComboboxExposureGain;
	const String m_strComboboxGamma;
	const String m_strComboboxShut;
	const String m_strComboboxAperture;
	const String m_strSliderAperture;
	const String m_strEdtAperture;
	const String m_strSliderRGain;
	const String m_strEdtRGain;
	const String m_strSliderBGain;
	const String m_strEdtBGain;
	const String m_strSliderAdjustRange;
	const String m_strSliderHoriStretch;
	const String m_strEdtHoriStretch;
	const String m_strEdtAdjustRange;
	const String m_strSliderPicSceApt;
	const String m_strEdtPicSceApt;
	const String m_strSliderContrast;
	const String m_strEdtContrast;
	const String m_strSliderSaturat;
	const String m_strEdtSaturat;
	const String m_strSliderSharp;
	const String m_strEdtSharp;
	const String m_strSliderBright;
	const String m_strEdtBright;
    const String m_strSliderHue;
    const String m_strEdtHue;
	const String m_strEdtZoom;
	const String m_strStcZoom;
	const String m_strStcLine2DNR;
	const String m_strStc2DNR;
	const String m_strStcLine3DNR;
	const String m_strStc3DNR;
	const String m_strCombobox2DNR;
	const String m_strCombobox3DNR;
	const String m_strBtnCheckManuelFocus;
	const String m_strBtnCheckAutoFocus;
	
    const String m_strBtnSwitchManuelExposure;
	const String m_strBtnSwitchAutoExposure;
	const String m_strBtnSwitchAutoWB;
	const String m_strBtnZoomPlus;
	const String m_strBtnZoomSub;
	const String m_strBtnSwitchPersetMove;
	const String m_strBtnSwitchNR;
	const String m_strBtnSwitch2DNR;
	const String m_strBtnSwitch3DNR;
	const String m_strBtnSwitchLightPensation;
	const String m_strBtnSwitchKeystoneAdjust;
	const String m_strBtnCheckBackLight;

    //moon904k30 新增
    const String m_strBtnSwitchManuelApertre;
    const String m_strBtnSwitchAutoApertre;
    const String m_strComboboxApertre;
    const String m_strEdtExpGain;
    const String m_strComboboxOrderPos;

    //自定义成员变量
	bool         m_bIsCameraPowerOn;   //摄像机是否正在上电   by xhx
	bool         m_bLoginByOther;      //tptools是否被抢登    by xhx
	bool         m_bSourceCfg;         //信号源帧数不同时快门参数不同
	u32          m_dwContrast;		   //滑动设置后的值通过消息通知界面后保存	
	u32          m_dwSharp;
	u32          m_dwBright;
	u32          m_dwSaturat;
	EmTPMOOMMode m_emFocusMode;        //聚焦模式
    EmTPMOOMMode m_emExposureMode;     //曝光模式
    EmTPMOOMMode m_emWBMode;           //白平衡模式
	BOOL		 m_bIsOrderPos;

	TTPMechVer m_tTpMechver1;
	TTPMechVer m_tTpMechver2;
	TTPMechVer m_tTpMechver3;

	u8 m_byCamIndex;
    EmTPMechanism m_emTPMechanism;
    EmTPMOOMMode m_emApertre;
};

#define CAMERALOGICRPTR    CCameraCtrlLogic::GetSingletonPtr()               //CameraCtrllogic指针

#endif // !defined(AFX_CAMERALOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
