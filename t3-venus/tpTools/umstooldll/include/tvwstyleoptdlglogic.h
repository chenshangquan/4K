/*****************************************************************************
模块名      : CTvwStyleOptDlgLogic
文件名      : tvwstyleoptdlglogic.h
相关文件    : 
文件实现功能: logic电视墙风格配置页面
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/01/21     1.0         刘德印      创建
******************************************************************************/
#if !defined(AFX_TVWSTYLEOPTDLGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
#define AFX_TVWSTYLEOPTDLGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

class CTvwStyleOptDlgLogic :public CWndLogicBase, public ISingleTon<CTvwStyleOptDlgLogic>  
{
public:  
    CTvwStyleOptDlgLogic();
	virtual ~CTvwStyleOptDlgLogic();

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

	bool OnBtnTvwStyleOptCancel( const IArgs & arg );

protected:
   /**	 
	* 功能:  发送当前选中的数据到风格配置页面
	* @return   
	* @remarks	 
	*/
	HRESULT OnTvwStyleSelData( WPARAM wparam, LPARAM lparam );



protected:
	virtual void RegMsg(); 
	virtual void UnRegMsg();

	bool OnBtnTvwStyleOptOk( const IArgs & arg );
	
		/**	 
	* 功能: 通道名编辑框发生改变
	* @return   bool
	* @remarks  
	*/
	bool OnChanNameEditChange( const IArgs & arg );

private:
	   /**	 
	* 功能:  获取设备名对应层、槽信息
	* @return   
	* @remarks	 
	*/
	std::pair<s32,s32> GetLayorAndSlotByDevice(const String& strDeviceName);

		/**	 
	* 功能: 检测已添加的通道信息中是否存在相同的   存在则添加失败    
	* @return   BOOL
	* @remarks  
	*/
	BOOL CheckExistChanInfo(const THduStyleUnit& tStyleUnits);

	/**	 
	* 功能: 更新设备名称列表
	* @return
	* @remarks
	*/
	bool RevertComboboxDeviceName();

		/**	 
	* 功能: 转换通道号   转换规则   0层0槽 为1 2， 0层1槽为3 4   以此类推     但实际发送   只发0 1
	* @return   bool
	* @remarks  RevertBrdPosToChanNo 为1 2界面显示      RevertChanNoToBrdPos 0或0 1
	*/
	bool RevertBrdPosToChanNo( u8 byLayer, u8 bySlot );
	bool RevertChanNoToBrdPos();

		/**	 
	* 功能: 当点击某个预案配置   根据当前通道号   设置相应的显示数据  如通道号0   0层0槽则显示1    如通道号1   0层1槽则显示4   
	* @return   void
	* @remarks
	*/
	void ShowChanNo(u8 byChanNo);

private:
	const String  m_strComboboxTvwStyleOptDeviceName;
	const String  m_strComboboxTvwStyleOptChanNo;
	const String  m_strBtnTvwStyleOptOk;

	TTvwStyleInfo m_tTvwStyleInfo;

};

#define TVWSTYLEOPTLOGICRPTR    CTvwStyleOptDlgLogic::GetSingletonPtr()               //电视墙风格配置logic指针

#endif // !defined(AFX_TVWSTYLEOPTDLGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
