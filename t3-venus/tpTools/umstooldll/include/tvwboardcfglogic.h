/*****************************************************************************
模块名      : CTvwBoardCfgLogic
文件名      : TvwBoardcfglogic.h
相关文件    : 
文件实现功能: logic电视墙单板配置页面
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/01/04     1.0         刘德印      创建
******************************************************************************/
#if !defined(AFX_TVWBoardCFGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
#define AFX_TVWBoardCFGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

#include "touchlistdataproperty.h"

class CTvwBoardCfgLogic :public CWndLogicBase, public ISingleTon<CTvwBoardCfgLogic> 
{
public:  
    CTvwBoardCfgLogic();
	virtual ~CTvwBoardCfgLogic();

public:  
	
	virtual bool RegCBFun();
	
	virtual bool UnRegFunc( );
	
    virtual bool InitWnd( const IArgs & arg );

   /**	 
	* 功能:  清空所有状态和数据
	* @return   
	* @remarks	 
	*/
    virtual void Clear();

public:
		/**	 
	* 功能: 检测切换页面数据  有变化保存
	* @return   BOOL:TRUE可以切换    FALSE禁止切换
	* @remarks  
	*/
	BOOL CheckPageDataChangeToSave();

protected: 
	virtual void RegMsg(); 
	virtual void UnRegMsg();

	HRESULT OnRefreshTvwBoardInfoNotify( WPARAM wparam, LPARAM lparam);
	HRESULT OnOptTvwBoardNotify( WPARAM wparam, LPARAM lparam);
	HRESULT OnOptTvwBoardRsp( WPARAM wparam, LPARAM lparam);
	HRESULT OnDelTvwBoardNotify( WPARAM wparam, LPARAM lparam);
	HRESULT OnOptTvwBoardModeNotify( WPARAM wparam, LPARAM lparam);
	HRESULT OnOptTvwBoardModeRsp( WPARAM wparam, LPARAM lparam);
	HRESULT OnDelTvwBoardModeNotify( WPARAM wparam, LPARAM lparam);
	HRESULT OnTvwBoardUpgradeRsp( WPARAM wparam, LPARAM lparam);
	HRESULT OnTvwBoardBeginUpgrade( WPARAM wparam, LPARAM lparam);

protected:
		/**	 
	* 功能: 点击单板层切换菜单列表
	* @return   bool
	* @remarks  
	*/
	bool OnMenuLstItem( const IArgs & arg );
	
		/**	 
	* 功能: 点击层单板列表
	* @return   bool
	* @remarks  
	*/
	bool OnTvwBoardLstFloorItem( const IArgs & arg );

	/**	 
	* 功能: 重置切换单板列表页面控件状态
	* @return   bool
	* @remarks  
	*/
	void ResetTvwBoardPageControl();

	/**	 
	* 功能: 单板删除
	* @return   bool
	* @remarks  
	*/
	bool OnBtnTvwBoardDel( const IArgs & arg );

	/**	 
	* 功能: 单板修改
	* @return   bool
	* @remarks  
	*/
	bool OnBtnTvwBoardModify( const IArgs & arg );

	/**	 
	* 功能: 单板添加
	* @return   bool
	* @remarks  
	*/
	bool OnBtnTvwBoardAdd( const IArgs & arg );

	/**	 
	* 功能: 单板重启
	* @return   bool
	* @remarks  
	*/
	bool OnBtnTvwBoardReboot( const IArgs & arg );

	/**	 
	* 功能: 单板升级
	* @return   bool
	* @remarks  
	*/
	bool OnBtnTvwBoardUpgrade( const IArgs & arg );

	/**	 
	* 功能: 单板模式删除
	* @return   bool
	* @remarks  
	*/
	bool OnBtnTvwBoardModeDel( const IArgs & arg );

	/**	 
	* 功能: 单板模式修改
	* @return   bool
	* @remarks  
	*/
	bool OnBtnTvwBoardModeSave( const IArgs & arg );

		/**	 
	* 功能: 电视墙单板模式输入接口改变   因为只有输入接口1改变   相应制式接口数据才改变   所以单独抽取
	* @return   bool
	* @remarks  
	*/
	bool OnTvwBoardMdlEditInputPortOneChange( const IArgs & arg );

		/**	 
	* 功能: 电视墙单板模式输入接口改变   因为只有输入接口2改变   相应制式接口数据才改变   所以单独抽取
	* @return   bool
	* @remarks  
	*/
	bool OnTvwBoardMdlEditInputPortTwoChange( const IArgs & arg );

		/**	 
	* 功能: 电视墙单板模式制式1改变
	* @return   bool
	* @remarks  
	*/
	bool OnTvwBoardMdlEditInputNTFSOneChange( const IArgs & arg );

		/**	 
	* 功能: 电视墙单板模式制式2改变
	* @return   bool
	* @remarks  
	*/
	bool OnTvwBoardMdlEditInputNTFSTwoChange( const IArgs & arg );

		/**	 
	* 功能: 点击电视墙单板输入接口1
	* @return   bool
	* @remarks  
	*/
	bool OnTvwBoardMdlEditInputPortOneClick( const IArgs & arg );

		/**	 
	* 功能: 点击电视墙单板输入接口2
	* @return   bool
	* @remarks  
	*/
	bool OnTvwBoardMdlEditInputPortTwoClick( const IArgs & arg );

		/**	 
	* 功能: 点击电视墙单板列表空白处
	* @return   bool
	* @remarks  
	*/
	bool OnClickTvwBoardLstBlack( const IArgs & arg );

private:
		/**	 
	* 功能: 初始化单板层切换菜单列表
	* @return   bool
	* @remarks  
	*/
	void InitFunMenu();

		/**	 
	* 功能: 初始化模式列表下拉数据   空板子无数据   非空板子设置相应数据
	* @return   bool
	* @remarks  
	*/
	void InitMdlComboList();

		/**	 
	* 功能: 初始化单板列表数据
	* @return   bool
	* @remarks  
	*/
	void InitTvwBoardListData();

	/**	 
	* 功能: 刷新第几层列表显示
	* @return   无
	* @remarks  
	*/
	void UpdateTvwBoardLayarList(s32 nLayar);
	void UpdateLayarList( s32 nLayar, BOOL bIsReset = FALSE );

	/**	 
	* 功能: 设置电视墙单板模式控件数据到服务器
	* @return   无
	* @remarks  
	*/
	bool SetTvwModeControlInfoToSevr();

	/**	 
	* 功能: 清空电视墙模式页面数据显示
	* @return   无
	* @remarks  
	*/
	void CleanTvwMdlControlShow();

	/**	 
	* 功能: 设置电视墙模式控件数据
	* @return   无
	* @remarks  
	*/
	BOOL SetTvwModeDataToControl(const THduCfg& tHduCfgSel);

		/**	 
	* 功能: 检测模式名称是否存在    存在则保存失败
	* @return   BOOL:TRUE存在    TRUE不存在
	* @remarks  
	*/
	BOOL IsExistMdlName();

		/**	 
	* 功能: 检测电视墙单板模式数据的合法性
	* @return   BOOL
	* @remarks  
	*/
	BOOL CheckPageTvwBoardMdlData();

		/**	 
	* 功能: 控制单板层数   最多只允许4层有数据
	* @return   BOOL
	* @remarks  
	*/
	BOOL ControlNotNullBoradLayorCount();

	/**	 
	* 功能: 电视墙单板模式数据是否改变
	* @return   bool
	* @remarks  
	*/
	BOOL GetMdlDataChange(){ return m_bMdlDataChange;};

	/**	 
	* 功能: 比较界面数据变化
	* @return   bool
	* @remarks  
	*/
	void CompareDataChange();

	/**	 
	* 功能: 设置几种combox控件的默认显示值
	* @return   无
	* @remarks  
	*/
	void InitHduOutPortValue();	
	void InitHduOutModeValue();	
	void InitHduZoomRateValue();	
	void InitHduShowModeValue();	

	String EmHduOutPortToString(EmHduOutPort emValue);		//接口类型转换
	EmHduOutPort StringToEmHduOutPort(String strValue);
	String EmHduOutModeToString(EmHduOutMode emValue);		//输出制式转换
	EmHduOutMode StringToEmHduOutMode(String strValue);
	String EmHduZoomRateToString(EmHduZoomRate emValue);	//缩放比列转换
	EmHduZoomRate StringToEmHduZoomRate(String strValue);
	String EmHduShowModeToString(EmHduShowMode emValue);	//输出比例转换
	EmHduShowMode StringToEmHduShowMode(String strValue);

	void SetMdlDataChange(BOOL bMdlDataChange){ m_bMdlDataChange = bMdlDataChange;};

	/**	 
	* 功能: 设置控件1模式名
	* @return   无
	* @remarks  
	*/
	void SetModePortOneDataToCtrl( BOOL bIsEditDataChange = TRUE );	

	/**	 
	* 功能: 设置控件2模式名
	* @return   无
	* @remarks  
	*/
	void SetModePortTwoDataToCtrl( BOOL bIsEditDataChange = TRUE );

	/**	 
	* 功能: 设置当前选中的模式信息
	* @return   无
	* @remarks  
	*/
	void SetSelMdlDataToCtrl();

private:
	const String m_strLstTvwBoardFloor;
	const String m_strLstTvwFloorMenu;
	const String m_strBtnTvwBoardDel;
	const String m_strBtnTvwBoardModify;
	const String m_strBtnTvwBoardAdd;
	const String m_strBtnTvwBoardReboot;
	const String m_strBtnTvwBoardUpgrade;
	const String m_strBtnTvwBoardModeDel;
	const String m_strBtnTvwBoardModeSave;

	const String m_strEdtTvwBoardModeName;
	const String m_strComboxTvwBoardInputPortOne;
	const String m_strComboxTvwBoardInputPortTwo;
	const String m_strComboxTvwBoardInputPortOneNTSC;
	const String m_strComboxTvwBoardInputPortTwoNTSC;
	const String m_strComboxTvwBoardInputPortOnePer;
	const String m_strComboxTvwBoardInputPortTwoPer;
	const String m_strComboxTvwBoardInputPortOnePerPloy;
	const String m_strComboxTvwBoardInputPortTwoPerPloy;


	std::vector<THduCfg> m_vecTPTvwBrdInfo;
	THduCfg m_tHduCfgSel;

	std::vector<CString> m_vecHduOutPort;
	std::vector<CString> m_vecHduOutModeCommon;     //接口类型为DVI（默认）/HDMI/YPbPr时，输出制式支持
	std::vector<CString> m_vecHduOutModeVGA;        //接口类型为VGA时，输出制式支持
	std::vector<CString> m_vecHduZoomRate;
	std::vector<CString> m_vecHduShowMode;

	BOOL m_bMdlDataChange;

	s32 m_nCurFloorNo;
};

#define TVWBOARDLOGICRPTR    CTvwBoardCfgLogic::GetSingletonPtr()               //电视墙单板logic指针

#endif // !defined(AFX_TVWBoardCFGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
