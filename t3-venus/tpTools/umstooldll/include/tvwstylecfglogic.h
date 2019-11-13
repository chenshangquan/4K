/*****************************************************************************
模块名      : CTvwStyleCfgLogic
文件名      : templateexplogic.h
相关文件    : 
文件实现功能: logic电视墙风格配置页面
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/01/16     1.0         刘德印      创建
******************************************************************************/
#if !defined(AFX_TVWSTYLECFGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
#define AFX_TVWSTYLECFGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

class CTvwStyleCfgLogic :public CWndLogicBase,public ISingleTon<CTvwStyleCfgLogic> 
{
public:  
    CTvwStyleCfgLogic();
	virtual ~CTvwStyleCfgLogic();

public:
		/**	 
	* 功能: 检测电视墙风格数据是否改变
	* @return   bool
	* @remarks  
	*/
	BOOL CheckPageDataChangeToSave();

		/**	 
	* 功能: 得到当前待保存的电视墙风格矩阵
	* @return   void
	* @remarks  
	*/
	THduStyleData GetStyleDataMatrix(){return m_tHduStyleDataMatrix;}; 


			/**	 
	* 功能: 更新电视墙风格列表
	* @return   void
	* @remarks  
	*/
	void UpdateTvwStyleList();

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
	* 功能: 初始化界面数据
	* @return   void
	* @remarks  
	*/
	virtual void InitLogicData();

	/**	 
	* 功能:  获取层、槽通过设备名对应信息
	* @return   
	* @remarks	 
	*/
	String GetDeviceByLayorAndSlot(const std::pair<s32,s32>& pairLayorSlot);

protected:
		/**	 
	* 功能: 点击电视墙风格列表
	* @return   bool
	* @remarks  
	*/
	bool OnTvwStyleItem( const IArgs & arg );

			/**	 
	* 功能: 保存配置的电视墙风格
	* @return   bool
	* @remarks  
	*/
	bool OnBtnTvwStyleSave( const IArgs & arg );

		/**	 
	* 功能: 点击菜单配置电视墙风格
	* @return   bool
	* @remarks  
	*/
	bool OnBtnTvwStyleMenu( const IArgs & arg );

	/**	 
	* 功能: 点击菜单删除电视墙风格
	* @return   bool
	* @remarks  
	*/
	bool OnBtnTvwStyleMenuDel( const IArgs & arg );
	
protected: 
	virtual void RegMsg(); 
	virtual void UnRegMsg();

		/**	 
	* 功能: 刷新电视墙风格数据通知
	* @return   bool
	* @remarks  
	*/
	HRESULT OnRefreshTvwStyleInfoNotify( WPARAM wparam, LPARAM lparam);
	
		/**	 
	* 功能: 保存电视墙风格结果
	* @return   bool
	* @remarks  
	*/
	HRESULT OnTvwStyleSaveRsp( WPARAM wparam, LPARAM lparam);

	/**	 
	* 功能: 更新电视墙风格结果
	* @return   bool
	* @remarks  
	*/
	HRESULT OnTvwStyleUpdateRsp( WPARAM wparam, LPARAM lparam);

		/**	 
	* 功能: 电视墙风格行数据Edit改变(动态控制列中显示数据)
	* @return   bool
	* @remarks  
	*/
	bool OnTvwStyleRowEditChange( const IArgs & arg );

		/**	 
	* 功能: 手动输入电视墙风格行数据(动态控制列中显示数据)
	* @return   bool
	* @remarks  
	*/
	bool OnTvwStyleRowEditOnChar( const IArgs & arg );
	
		/**	 
	* 功能: 电视墙风格列数据Edit改变(动态控制电视墙风格列表多行多列显示风格)
	* @return   bool
	* @remarks  
	*/
	bool OnTvwStyleColEditChange( const IArgs & arg );


		/**	 
	* 功能: 手动输入电视墙风格列数据(动态控制电视墙风格列表多行多列显示风格)
	* @return   bool
	* @remarks  
	*/
	bool OnTvwStyleColEditOnChar( const IArgs & arg );

		/**	 
	* 功能: 点击combo列列表数据
	* @return   bool
	* @remarks  
	*/
	bool OnTvwStyleColClick( const IArgs & arg );


		/**	 
	* 功能: 点击combo行列表数据
	* @return   bool
	* @remarks  
	*/
	bool OnTvwStyleRowClick( const IArgs & arg );


		/**	 
	* 功能: 刷新电视墙风格数据通知
	* @param    wparam:TTvwStyleInfo m_tSelTvwStyleInfo
	* @return   bool
	* @remarks  
	*/
	HRESULT OnTvwStyleSave( WPARAM wparam, LPARAM lparam);
	
private:
		/**	 
	* 功能: 下拉行列控件动态设置列数据   默认显示第一个数据
	* @return   void
	* @remarks  
	*/
	void SetStyleColData();

		/**	 
	* 功能: 动态控制电视墙风格列表多行多列显示风格
	* @return   void
	* @remarks  
	*/
	void SetDynamicStyleList();


		/**	 
	* 功能: 保存电视墙风格预案
	* @return   void
	* @remarks  
	*/
	BOOL TvwStyleSave( const TTvwStyleInfo& m_tSelTvwStyleInfo );

		/**	 
	* 功能: 更新电视墙风格界面信息
	* @return   void
	* @remarks  
	*/
	void RefreshTvwStyleInfo();

		/**	 
	* 功能: 电视墙风格矩阵数据是否变化检测
	* @return   void
	* @remarks  
	*/
	BOOL CompareStyleDataMatrixChange();

	/**	 
	* 功能: 当点击某个预案配置，根据当前层、槽、通道号，得到应显示的通道号  如通道号0   0层0槽则显示1    如通道号1   0层1槽则显示4   
	* @return   String 设备名  u8 通道号
	* @remarks
	*/
//	u8 GetShowChanNo( u8 byLayer, u8 bySlot, u8 byChanNo );

private:
	const String m_strComboboxTvwStyleCol;
	const String m_strComboboxTvwStyleRow;
	const String m_strLstTvwStyle;
	const String m_strBtnTvwStyleSave;

	TTvwStyleInfo m_tSelTvwStyleInfo;		//当前选中对应的电视墙通道数据，更新数据列表使用 
	THduStyleData m_tHduStyleDataMatrix;    //接收服务器发过来的电视墙风格数据，如果做了行列切换数据清空 界面更新 保存配置使用 
											//其中THduStyleUnit只在数据刷新和配置保存时候更新整个矩阵数据

	BOOL m_bStyleDataChange;
	CTransparentViewList* m_pListWnd;
};

#define TVWSTYLELOGICRPTR    CTvwStyleCfgLogic::GetSingletonPtr()               //电视墙风格logic指针

#endif // !defined(AFX_TVWSTYLECFGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
