// SysCfgDlgLogic.h: interface for the CSysCfgDlgLogic class.
//
//////////////////////////////////////////////////////////////////////
/*****************************************************************************
文件名      : CSysCfgDlgLogic.h
相关文件    : 
文件实现功能: 系统配置界面
作者        : 吴蒨蒨
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2014/12/22     1.0         吴蒨蒨      创建
******************************************************************************/
#if !defined(AFX_ORDERPOSINFOLOGIC_H__B06B345C_CF30_42B5_9B64_5F72C61D6269__INCLUDED_)
#define AFX_ORDERPOSINFOLOGIC_H__B06B345C_CF30_42B5_9B64_5F72C61D6269__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

class COrderPosInfoLogic : public CLogicBase, public ISingleTon<COrderPosInfoLogic> 
{
public:
	COrderPosInfoLogic();
	virtual ~COrderPosInfoLogic();
	
	//CLogicBase
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

	bool OnComboboxpresetIndexClick( const IArgs& args );

	bool OnBtnPresetInfoOk( const IArgs& args );

	bool OnBtnPresetInfoCancel( const IArgs& args );

	bool OnBtnClose( const IArgs& args );

	void UpdatePreData( TTPCamPre tTPCamPre );

protected:
	HRESULT OnOrderPosSelData( WPARAM wparam, LPARAM lparam );

	HRESULT OnCamPreSetListInd( WPARAM wparam, LPARAM lparam );
	
	HRESULT OnUpdateBtnStatus( WPARAM wparam, LPARAM lparam );
private:	
	/** 功能:  保存配置时聚焦在出错的窗口	
	*  @param[in] strWindow   窗口名称
	*  @return 
	*  @remarks   
	*/	
	void FocusWindow(String strWindow);
	

	s32 GetPresetIndex( string strPresetInfo );
private:
	//该逻辑单元对应的所有控件名
	const String m_strCombOutputStyle;
	const String m_strSoftWareInfo;
	const String m_strEdtPresetInfo;

	//预置位操作类型
	EM_ORDERPOSOPT_TYPE m_emOPType;

	//当前选中的预置位信息
	TTPCamPre m_tCamPreSel;
	std::vector<TTPCamPre> m_vecTPCamPreInfo;
	bool				   m_bIsWaitForTra;
};

#define ORDERPOSINFOLOGICRPTR    COrderPosInfoLogic::GetSingletonPtr()               //上传（导入）通用弹出界面logic指针

#endif // !defined(AFX_CFGSERVERLOGIC_H__B06B345C_CF30_42B5_9B64_5F72C61D6269__INCLUDED_)
