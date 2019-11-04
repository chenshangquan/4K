/*****************************************************************************
模块名      : CCorrectParamLogic
文件名      : CorrectParamLogic.h
相关文件    : 
文件实现功能: 矫正参数设置
作者        : 杨奇峰
版本        : V1.0  Copyright(C) 2017-2018 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2017/04/25     1.0         杨奇峰      创建
******************************************************************************/
// CorrectParamLogic.h: interface for the CCorrectParamLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CORRECTPARAMLOGIC_H__974545AF_6B7C_4069_8884_33EFC4FDAEEB__INCLUDED_)
#define AFX_CORRECTPARAMLOGIC_H__974545AF_6B7C_4069_8884_33EFC4FDAEEB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCorrectParamLogic:public CLogicBase, public ISingleTon<CCorrectParamLogic> 
{
public:
	CCorrectParamLogic();
	virtual ~CCorrectParamLogic();

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
	virtual void UnRegFunc();
	/** 功能:  初始化窗口
	*  @param[in] 
	*  @return 
	*  @remarks  在读取xml文件时候调用,根据里面的内容初始化窗口
	*/	
    virtual bool InitWnd( const IArgs & arg ); 

   /**	 
	* 功能:  清空所有状态和数据
	* @return   
	* @remarks	 
	*/
    virtual void Clear();

public:

	HRESULT OnSecBoundaryNty( WPARAM wparam, LPARAM lparam );
	HRESULT OnSetDistortValueNty( WPARAM wparam, LPARAM lparam );
	HRESULT OnSetCamZoomStopInd( WPARAM wparam, LPARAM lparam );	
	HRESULT OnCamParamSyncInd( WPARAM wparam, LPARAM lparam );
	HRESULT OnChangeDistortInd( WPARAM wparam, LPARAM lparam );
	HRESULT OnDirectSetDistortInd( WPARAM wparam, LPARAM lparam );	
	HRESULT OnSetDefaultParamNty( WPARAM wparam, LPARAM lparam );
	HRESULT	OnSetDistortZoomValNty( WPARAM wparam, LPARAM lparam );
	HRESULT OnTpMechanismSelectNty( WPARAM wparam, LPARAM lparam );
	HRESULT OnCameraStyleSelectInd( WPARAM wparam, LPARAM lparam );
	HRESULT OnSetDefaultZoomInd( WPARAM wparam, LPARAM lparam );

public:
	
	bool OnBtnClose( const IArgs & arg );

	bool OnRotateLeftReduceBtnClick( const IArgs & arg );
	bool OnRotateLeftEditChange( const IArgs & arg );
	bool OnRotateLeftEditKillFocus( const IArgs & arg );
	bool OnRotateLeftIncreaseBtnClick( const IArgs & arg );
	
	bool OnLeftOneReduceBtnClick( const IArgs & arg );
	bool OnLeftOneEditChange( const IArgs & arg );
	bool OnLeftOneEditKillFocus( const IArgs & arg );
	bool OnLeftOneIncreaseBtnClick( const IArgs & arg );

	bool OnLeftTwoReduceBtnClick( const IArgs & arg );
	bool OnLeftTwoEditChange( const IArgs & arg );
	bool OnLeftTwoEditKillFocus( const IArgs & arg );
	bool OnLeftTwoIncreaseBtnClick( const IArgs & arg );

	bool OnLeftThreeReduceBtnClick( const IArgs & arg );
	bool OnLeftThreeEditChange( const IArgs & arg );
	bool OnLeftThreeEditKillFocus( const IArgs & arg );
	bool OnLeftThreeIncreaseBtnClick( const IArgs & arg );

	bool OnLeftFourReduceBtnClick( const IArgs & arg );
	bool OnLeftFourEditChange( const IArgs & arg );
	bool OnLeftFourEditKillFocus( const IArgs & arg );
	bool OnLeftFourIncreaseBtnClick( const IArgs & arg );

	bool OnLeftFiveReduceBtnClick( const IArgs & arg );
	bool OnLeftFiveEditChange( const IArgs & arg );
	bool OnLeftFiveEditKillFocus( const IArgs & arg );
	bool OnLeftFiveIncreaseBtnClick( const IArgs & arg );

	bool OnLeftSixReduceBtnClick( const IArgs & arg );
	bool OnLeftSixEditChange( const IArgs & arg );
	bool OnLeftSixEditKillFocus( const IArgs & arg );
	bool OnLeftSixIncreaseBtnClick( const IArgs & arg );

	bool OnLeftSevenReduceBtnClick( const IArgs & arg );
	bool OnLeftSevenEditChange( const IArgs & arg );
	bool OnLeftSevenEditKillFocus( const IArgs & arg );
	bool OnLeftSevenIncreaseBtnClick( const IArgs & arg );

	bool OnLeftEightReduceBtnClick( const IArgs & arg );
	bool OnLeftEightEditChange( const IArgs & arg );
	bool OnLeftEightEditKillFocus( const IArgs & arg );
	bool OnLeftEightIncreaseBtnClick( const IArgs & arg );

	bool OnLeftNineReduceBtnClick( const IArgs & arg );
	bool OnLeftNineEditChange( const IArgs & arg );
	bool OnLeftNineEditKillFocus( const IArgs & arg );
	bool OnLeftNineIncreaseBtnClick( const IArgs & arg );

	bool OnLeftTenReduceBtnClick( const IArgs & arg );
	bool OnLeftTenEditChange( const IArgs & arg );
	bool OnLeftTenEditKillFocus( const IArgs & arg );
	bool OnLeftTenIncreaseBtnClick( const IArgs & arg );

	bool OnLeftElevenReduceBtnClick( const IArgs & arg );
	bool OnLeftElevenEditChange( const IArgs & arg );
	bool OnLeftElevenEditKillFocus( const IArgs & arg );
	bool OnLeftElevenIncreaseBtnClick( const IArgs & arg );

	bool OnLeftTwelveReduceBtnClick( const IArgs & arg );
	bool OnLeftTwelveEditChange( const IArgs & arg );
	bool OnLeftTwelveEditKillFocus( const IArgs & arg );
	bool OnLeftTwelveIncreaseBtnClick( const IArgs & arg );

	bool OnLBtnDownZoomPlus( const IArgs & arg );
	bool OnLBtnUpZoomPlus( const IArgs & arg );
	bool OnLBtnDoubleDownZoomPlus( const IArgs & arg );
	
	bool OnLBtnDownZoomSub( const IArgs & arg );
	bool OnLBtnUpZoomSub( const IArgs & arg );
	bool OnLBtnDoubleDownZoomSub( const IArgs & arg );

	bool OnEdtLeftZoomChange( const IArgs & arg );
	bool OnEdtLeftZoomKillFocus( const IArgs & arg );

	/*  右边矩形  */
	bool OnRotateRightReduceBtnClick( const IArgs & arg );
	bool OnRotateRightEditChange( const IArgs & arg );
	bool OnRotateRightEditKillFocus( const IArgs & arg );
	bool OnRotateRightIncreaseBtnClick( const IArgs & arg );

	bool OnRightOneReduceBtnClick( const IArgs & arg );
	bool OnRightOneEditChange( const IArgs & arg );
	bool OnRightOneEditKillFocus( const IArgs & arg );
	bool OnRightOneIncreaseBtnClick( const IArgs & arg );
	
	bool OnRightTwoReduceBtnClick( const IArgs & arg );
	bool OnRightTwoEditChange( const IArgs & arg );
	bool OnRightTwoEditKillFocus( const IArgs & arg );
	bool OnRightTwoIncreaseBtnClick( const IArgs & arg );
	
	bool OnRightThreeReduceBtnClick( const IArgs & arg );
	bool OnRightThreeEditChange( const IArgs & arg );
	bool OnRightThreeEditKillFocus( const IArgs & arg );
	bool OnRightThreeIncreaseBtnClick( const IArgs & arg );
	
	bool OnRightFourReduceBtnClick( const IArgs & arg );
	bool OnRightFourEditChange( const IArgs & arg );
	bool OnRightFourEditKillFocus( const IArgs & arg );
	bool OnRightFourIncreaseBtnClick( const IArgs & arg );
	
	bool OnRightFiveReduceBtnClick( const IArgs & arg );
	bool OnRightFiveEditChange( const IArgs & arg );
	bool OnRightFiveEditKillFocus( const IArgs & arg );
	bool OnRightFiveIncreaseBtnClick( const IArgs & arg );
	
	bool OnRightSixReduceBtnClick( const IArgs & arg );
	bool OnRightSixEditChange( const IArgs & arg );
	bool OnRightSixEditKillFocus( const IArgs & arg );
	bool OnRightSixIncreaseBtnClick( const IArgs & arg );
	
	bool OnRightSevenReduceBtnClick( const IArgs & arg );
	bool OnRightSevenEditChange( const IArgs & arg );
	bool OnRightSevenEditKillFocus( const IArgs & arg );
	bool OnRightSevenIncreaseBtnClick( const IArgs & arg );
	
	bool OnRightEightReduceBtnClick( const IArgs & arg );
	bool OnRightEightEditChange( const IArgs & arg );
	bool OnRightEightEditKillFocus( const IArgs & arg );
	bool OnRightEightIncreaseBtnClick( const IArgs & arg );
	
	bool OnRightNineReduceBtnClick( const IArgs & arg );
	bool OnRightNineEditChange( const IArgs & arg );
	bool OnRightNineEditKillFocus( const IArgs & arg );
	bool OnRightNineIncreaseBtnClick( const IArgs & arg );
	
	bool OnRightTenReduceBtnClick( const IArgs & arg );
	bool OnRightTenEditChange( const IArgs & arg );
	bool OnRightTenEditKillFocus( const IArgs & arg );
	bool OnRightTenIncreaseBtnClick( const IArgs & arg );
	
	bool OnRightElevenReduceBtnClick( const IArgs & arg );
	bool OnRightElevenEditChange( const IArgs & arg );
	bool OnRightElevenEditKillFocus( const IArgs & arg );
	bool OnRightElevenIncreaseBtnClick( const IArgs & arg );
	
	bool OnRightTwelveReduceBtnClick( const IArgs & arg );
	bool OnRightTwelveEditChange( const IArgs & arg );
	bool OnRightTwelveEditKillFocus( const IArgs & arg );
	bool OnRightTwelveIncreaseBtnClick( const IArgs & arg );
	
	bool OnRBtnDownZoomPlus( const IArgs & arg );
	bool OnRBtnUpZoomPlus( const IArgs & arg );
	bool OnRBtnDoubleDownZoomPlus( const IArgs & arg );
	
	bool OnRBtnDownZoomSub( const IArgs & arg );
	bool OnRBtnUpZoomSub( const IArgs & arg );
	bool OnRBtnDoubleDownZoomSub( const IArgs & arg );
	
	bool OnEdtRightZoomChange( const IArgs & arg );
	bool OnEdtRightZoomKillFocus( const IArgs & arg );

	bool OnBtnUppage( const IArgs & arg );
	bool OnBtnDownpage( const IArgs & arg );

	void SetH650ZoomValue(u32 dwZoom, u32 dwZoomPos);

protected: 
	virtual void RegMsg(); 
	virtual void UnRegMsg();

private:
	
	void UpdateDistortParam(int nPage);
	void UpdateEditNum(const IArgs & arg);
	void SetLeftDistortValue( TTPAllDistortParam tTPAllDistortParam );
	void SetRightDistortValue( TTPAllDistortParam tTPAllDistortParam );

	void UpdateDistortIndVal( TTPDistortInfo tTPDistortInfo, TTPAllDistortParam &tTPAllDistortParam );

	void SetZoomCmd( CString str, u8 byIndex );
	void SetDistortZoomVal( u8 byIndex, u32 dwZoom, u32 dwZoomPos );

	float StringToFloatTwo( CString str );
	float StringToFloatThree( CString str );
	CString OnlyFloat( CString str );

private:

	Window* m_pWnd;

	u32 m_dwZoom1;
	u32 m_dwZoom2;
	u32 m_dwZoom3;

	u32 m_dwZoomPos1;
	u32 m_dwZoomPos2;
	u32 m_dwZoomPos3;

	TTPAllDistortParam m_tTPAllDistortParam1;
	TTPAllDistortParam m_tTPAllDistortParam2;
	TTPAllDistortParam m_tTPAllDistortParam3;
	
	const string m_strRotateLeftEdit;
	const string m_strRotateRightEdit;
	const string m_strEdtLeftZoom;
	const string m_strStcLeftZoom;
	const string m_strEdtRightZoom;
	const string m_strStcRightZoom;

	const string m_strLeftOneEdit;
	const string m_strLeftTwoEdit;
	const string m_strLeftThreeEdit;
	const string m_strLeftFourEdit;
	const string m_strLeftFiveEdit;
	const string m_strLeftSixEdit;
	const string m_strLeftSevenEdit;
	const string m_strLeftEightEdit;
	const string m_strLeftNineEdit;
	const string m_strLeftTenEdit;
	const string m_strLeftElevenEdit;
	const string m_strLeftTwelveEdit;
	
	const string m_strRightOneEdit;
	const string m_strRightTwoEdit;
	const string m_strRightThreeEdit;
	const string m_strRightFourEdit;
	const string m_strRightFiveEdit;
	const string m_strRightSixEdit;
	const string m_strRightSevenEdit;
	const string m_strRightEightEdit;
	const string m_strRightNineEdit;
	const string m_strRightTenEdit;
	const string m_strRightElevenEdit;
	const string m_strRightTwelveEdit;

	const string m_strBtnUppage;
	const string m_strBtnDownpage;

	const string m_strStcCamStyle1;
	const string m_strStcCamStyle2;

private:
	u8           m_nbyIndex;           //用于标识是当前是界面显示是左中还是中右
	EmTPMechanism m_emTPMechanism;     //看机芯是sony还是H650

};

#define CORRECTPARAMLOGIC  CCorrectParamLogic::GetSingletonPtr()

#endif // !defined(AFX_CORRECTPARAMLOGIC_H__974545AF_6B7C_4069_8884_33EFC4FDAEEB__INCLUDED_)

