/*****************************************************************************
模块名      : CBoardCfgLogic
文件名      : boardcfglogic.h
相关文件    : 
文件实现功能: logic单板配置页面
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2012/12/17     1.0         刘德印      创建
******************************************************************************/
#if !defined(AFX_BOARDCFGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
#define AFX_BOARDCFGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"
#include "touchlistdataproperty.h"

class CBoardCfgLogic :public CWndLogicBase, public ISingleTon<CBoardCfgLogic> 
{
public:  
    CBoardCfgLogic();
	virtual ~CBoardCfgLogic();

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

	/**	 
	* 功能: 判断当前有无会议，更新控件状态
	* @return   bool
	* @remarks  
	*/
	void UpdateBtnState();

public:
		/**	 
	* 功能: 检测切换页面数据  有变化保存
	* @return   BOOL:TRUE可以切换    FALSE禁止切换
	* @remarks  
	*/
	BOOL CheckPageDataChangeToSave();

protected:
		/**	 
	* 功能: 点击层单板列表
	* @return   bool
	* @remarks  
	*/
	bool OnBoardLstFloorItem( const IArgs & arg );

	/**	 
	* 功能: 单板删除
	* @return   bool
	* @remarks  
	*/
	bool OnBtnBoardDel( const IArgs & arg );

	/**	 
	* 功能: 单板修改
	* @return   bool
	* @remarks  
	*/
	bool OnBtnBoardModify( const IArgs & arg );

	/**	 
	* 功能: 单板添加
	* @return   bool
	* @remarks  
	*/
	bool OnBtnBoardAdd( const IArgs & arg );

	/**	 
	* 功能: 单板重启
	* @return   bool
	* @remarks  
	*/
	bool OnBtnBoardReboot( const IArgs & arg );

	/**	 
	* 功能: 单板升级
	* @return   bool
	* @remarks  
	*/
	bool OnBtnBoardUpgrade( const IArgs & arg );

	/**	 
	* 功能: 单板模式删除
	* @return   bool
	* @remarks  
	*/
	bool OnBtnBoardModeDel( const IArgs & arg );

	/**	 
	* 功能: 单板模式修改(需求为 添加 修改合并为保存)
	* @return   bool
	* @remarks  
	*/
	bool OnBtnBoardModeSave( const IArgs & arg );

	/**	 
	* 功能: 单板模式名称、类型数据改变
	* @return   bool
	* @remarks  
	*/
	bool OnBoardMdlEditChange( const IArgs & arg );

	/**	 
	* 功能: apu单板混音器别名改变
	* @return   bool
	* @remarks  
	*/
	bool OnBoardAudioMixNameEditChange( const IArgs & arg );

	/**	 
	* 功能: apu单板混音器最大混音路数1改变
	* @return   bool
	* @remarks  
	*/
	bool OnBoardAudioMixNum1EditChange( const IArgs & arg );

	/**	 
	* 功能: apu单板混音器最大混音路数2改变
	* @return   bool
	* @remarks  
	*/
	bool OnBoardAudioMixNum2EditChange( const IArgs & arg );

	/**	 
	* 功能: 点击单板列表空白处
	* @return   bool
	* @remarks  
	*/
	bool OnClickBoardLstBlack( const IArgs & arg );

	/**	 
	* 功能: 单板模式数据是否改变
	* @return   bool
	* @remarks  
	*/
	BOOL GetMdlDataChange(){ return m_bMdlDataChange;};


protected: 
	virtual void RegMsg(); 
	virtual void UnRegMsg();

	HRESULT OnRefreshBoardInfoNotify( WPARAM wparam, LPARAM lparam);
	HRESULT OnOptBoardNotify( WPARAM wparam, LPARAM lparam);
	HRESULT OnOptBoardRsp( WPARAM wparam, LPARAM lparam);
	HRESULT OnDelBoardNotify( WPARAM wparam, LPARAM lparam);
	HRESULT OnOptBoardModeNotify( WPARAM wparam, LPARAM lparam);
	HRESULT OnOptBoardModeRsp( WPARAM wparam, LPARAM lparam);
	HRESULT OnBoardUpgradeRsp( WPARAM wparam, LPARAM lparam);
	HRESULT OnBoardBeginUpgrade( WPARAM wparam, LPARAM lparam);
	HRESULT OnConfCount( WPARAM wparam, LPARAM lparam);

private:
		/**	 
	* 功能: 初始化单板层切换菜单列表
	* @return   bool
	* @remarks  
	*/
	void InitFunMenu();

		/**	 
	* 功能: 初始化单板列表数据
	* @return   bool
	* @remarks  
	*/
	void InitBoardListData();

		/**	 
	* 功能: 点击单板层切换菜单列表
	* @return   bool
	* @remarks  
	*/
	bool OnMenuLstItem( const IArgs & arg );

		/**	 
	* 功能: 切换单板层菜单
	* @return   bool
	* @remarks  
	*/
	void SwitchTabWnd(CString strItemName);


	/**	 
	* 功能: 重置切换单板列表页面控件状态
	* @return   bool
	* @remarks  
	*/
	void ResetBoardPageControl();
	
		/**	 
	* 功能: 检测单板模式数据的合法性
	* @return   BOOL
	* @remarks  
	*/
	BOOL CheckPageBoardMdlData();

	String EmTpBoardRetToString(EmTpBoardRet emValue);				//操作板子错误值转换
	std::vector<CString> EMBrdTypeToVector(EMBrdType emBrdType);	//单板类型转换
	String EMEqpTypeToString(EMEqpType emValue);					//外设类型转换
	EMEqpType StringToEMEqpType(String strType);

	void SetMdlDataChange(BOOL bMdlDataChange){ m_bMdlDataChange = bMdlDataChange;};
	void SetLstNoSelItem(s32 nExceptLayarNo);						//点击列表后   切换层  除此列表置所有层设置无选中项

	void ShowBoardMdlCfg();				                    		//设置单板模块信息配置显示
	void EnableApuBoardMdlEdit(BOOL bEnable = TRUE);

	void ResetBoardMdlData(BOOL bDefault = TRUE);					//重置单板模块信息

private:
	const String m_strLstBoardZeroFloor;
	const String m_strLstBoardFirstFloor;
	const String m_strLstBoardSecondFloor;
	const String m_strLstBoardThirdFloor;
	const String m_strLstMenuFloor;
	const String m_strEdtBoardModeName;
	const String m_strComboboxModeType;
	const String m_strBtnBoardDel;
	const String m_strBtnBoardModify;
	const String m_strBtnBoardAdd;
	const String m_strBtnBoardReboot;
	const String m_strBtnBoardUpgrade;
	const String m_strBtnBoardModeDel;
	const String m_strBtnBoardModeSave;
	const String m_strStBoardModeName;
	const String m_strStBoardModeType;
	const String m_strStAudioMixName1;
	const String m_strStAudioMixName2;
	const String m_strEdtAudioMixName1;
	const String m_strEdtAudioMixName2;
	const String m_strStAudioMixNum1;
	const String m_strStAudioMixNum2;
	const String m_strEdtAudioMixNum1;
	const String m_strEdtAudioMixNum2;

	std::vector<TTPBrdInfo> m_vecTPBrdInfoZero;
	std::vector<TTPBrdInfo> m_vecTPBrdInfoFirst;
	std::vector<TTPBrdInfo> m_vecTPBrdInfoSecond;
	std::vector<TTPBrdInfo> m_vecTPBrdInfoThird;

	TTPBrdInfo m_tTBoardInfoSel;

	BOOL m_bMdlDataChange;
	BOOL m_bApuMdlNameChange;
	BOOL m_bApuMdlNum1Change;
	BOOL m_bApuMdlNum2Change;

	BOOL m_bSelItem;
};

#define BOARDLOGICRPTR    CBoardCfgLogic::GetSingletonPtr()               //单板logic指针

#endif // !defined(AFX_BOARDCFGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
