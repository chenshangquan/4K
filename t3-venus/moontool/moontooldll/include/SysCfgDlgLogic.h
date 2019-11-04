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
#if !defined(AFX_SYSCFGDLGLOGIC_H__B06B345C_CF30_42B5_9B64_5F72C61D6269__INCLUDED_)
#define AFX_SYSCFGDLGLOGIC_H__B06B345C_CF30_42B5_9B64_5F72C61D6269__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

class CSysCfgDlgLogic : public CLogicBase, public ISingleTon<CSysCfgDlgLogic> 
{
public:
	CSysCfgDlgLogic();
	virtual ~CSysCfgDlgLogic();
	
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

		
	bool IsCfgCnsChange();

	/**	 
	* 功能: 获取moon sys界面上数据变化控件的数目
	* @return   bool
	* @remarks  
	*/
	s32 GetCtrlChangeNum() { return m_vctWndName.size(); }

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
	
	HRESULT OnSoftWareVerInfoNty( WPARAM wparam, LPARAM lparam );

	HRESULT OnCamOutputInfoNty( WPARAM wparam, LPARAM lparam );

	HRESULT OnCamImageAdjustNty( WPARAM wparam, LPARAM lparam );

	HRESULT OnEthnetInfoNty( WPARAM wparam, LPARAM lparam );

	HRESULT OnCamOutputInfoInd( WPARAM wparam, LPARAM lparam );
	
	HRESULT OnCamImageAdjustInd( WPARAM wparam, LPARAM lparam );

	HRESULT OnLvdsBaudRateInd( WPARAM wparam, LPARAM lparam );
private:	
	/** 功能:  保存配置的按钮
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnBtnSave( const IArgs& args );

	/** 功能:  还原配置的按钮
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnBtnCancel( const IArgs& args );

	/** 功能: 点击HDMI输入源
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnHDMISelClick( const IArgs& args );

	/** 功能: 点击DVI输入源
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnDVISelClick( const IArgs& args );

	/** 功能: 点击输入源选择combox
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnCombOutputStyleClick( const IArgs& args );

	/** 功能: 点击图像不翻转radiobtn
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnNoTurnClick( const IArgs& args );

	/** 功能: 点击图像翻转radiobtn
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnTurnClick( const IArgs& args );

	/** 功能: IP地址edit
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnIPAddrChanged( const IArgs& args );

	/** 功能: 子网掩码edit
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnSubMaskChanged( const IArgs& args );

	/** 功能: 默认网关edit
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool OnGatewayChanged( const IArgs& args );

	/** 功能:  保存配置时聚焦在出错的窗口	
	*  @param[in] strWindow   窗口名称
	*  @return 
	*  @remarks   
	*/	
	void FocusWindow(String strWindow);	

	void SetOutPortType(EmTPDVIOutPortType emOutPortType);

	void SetMoonOutMode(EmTPMOONOutMode emMoonOutMode);

	void GetMoonOutMode( EmTPMOONOutMode &emMoonOutMode )const;

	void SetImageAdjust(EmTPImageAdjust emImageAdjust);

	void SetEthnetCfgData();

	/** 功能:  保存网络配置
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool SaveNet();

	/** 功能:  保存网络配置	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool SaveEthnetCfg();

	bool SaveMsgBox();

	bool OnCombBaudRateClick( const IArgs& args );
private:
	/** 功能:  将波特率的枚举值转化成对应字符串	
	*  @param[in] 波特率枚举值
	*  @return  相应界面字符串
	*  @remarks   
	*/	
	string TransRaudRateTypeToStr( EmTPLVDSBaud emTpLvdBaudValue );
	/** 功能:  将波特率的字符串转化成对应枚举值	
	*  @param[in] 界面显示波特率字符串
	*  @return  对应的枚举值
	*  @remarks   
	*/
	EmTPLVDSBaud TransRaudRateStrToType( string strBaudRate );
	/** 功能:  保存LVDS波特率
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool SaveBaudRate();
private:
	//该逻辑单元对应的所有控件名
	const String m_strCombOutputStyle;
	const String m_strSoftWareInfo;
	const String m_strComboBaudRate;        //Lvds波特率

	const String m_strEdtIp;				//CNS地址
    const String m_strEdtSubMask;			//子网掩码
    const String m_strEdtGateWay;			//默认网关

	const String m_strStyleGroup1;
	const String m_strStyleGroup2;
	const String m_strAdjustGroup1;
	const String m_strAdjustGroup2;

	EmTPDVIOutPortType m_emDVIOutPortType;
	EmTPMOONOutMode m_emMOONOutMode;
	EmTPImageAdjust m_emImageAdjust;
	EmTPLVDSBaud m_emBaudRate;

	BOOL m_bCnsIp;
	BOOL m_bSubMask;
	BOOL m_bGateWay;
};

#endif // !defined(AFX_CFGSERVERLOGIC_H__B06B345C_CF30_42B5_9B64_5F72C61D6269__INCLUDED_)
