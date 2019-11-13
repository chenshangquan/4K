/*****************************************************************************
模块名      : CUmsCfgLogic
文件名      : umscfglogic.h
相关文件    : 
文件实现功能: ums配置页面
作者        : 石城
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2012/12/24     1.0         石城			创建
******************************************************************************/
#if !defined(AFX_UMSCFGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
#define AFX_UMSCFGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

class CUmsCfgLogic :public CWndLogicBase, public ISingleTon<CUmsCfgLogic>
{
public:
	CUmsCfgLogic();
	virtual ~CUmsCfgLogic();

public:  
	/**	 
	* 功能:  注册该logic中所有的回调函数
	* @return  void
	* @remarks	在此注册的回调函数主要是控件的响应事件，多为成员回调函数,也可注册其他的回调函数
	                    注册时，应注意回调函数对应名子的命名规则：“类名::函数名”
	*/
	virtual bool RegCBFun();

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
	virtual bool UnRegFunc( );

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
	* 功能:  显示或隐藏窗口
	* @return  bool 表示是否该显示
	* @remarks
	*/
	virtual bool ShowWindow( BOOL32 bShow );

	/**	 
	* 功能:  检测当前会议数量，改变控件状态
	* @return
	* @remarks
	*/
	void CheckCtrlState();

   /**	 
	* 功能:  断链时清空所有状态和数据
	* @return   
	* @remarks	 
	*/
    virtual void Clear();

protected:
	/**	 
	* 功能:  单击GK开关Btn控件的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnSwitchGKClick( const IArgs& args );

	/**	 
	* 功能:  单击保存配置Btn控件的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnSaveClick( const IArgs& args );

	/**	 
	* 功能:  单击恢复配置Btn控件的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnReductionClick( const IArgs& args );

	/**	 
	* 功能:  单击导出配置Btn控件的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnBtnExportClick( const IArgs& args );

	/**	 
	* 功能:  改变UmsIP控件的字符时的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnChangedIPCtrlUmsIP( const IArgs& args );

	/**	 
	* 功能:  改变子网掩码IP控件的字符时的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnChangedIPCtrlSubnetMask( const IArgs& args );

	/**	 
	* 功能:  改变网关IP控件的字符时的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnChangedIPCtrlGateway( const IArgs& args );

	/**	 
	* 功能:  改变SipIP控件的字符时的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnChangedIPCtrlSipIP( const IArgs& args );

	/**	 
	* 功能:  改变GKIP控件的字符时的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnChangedIPCtrlGKIP( const IArgs& args );

protected:
	/**	 
	* 功能:  响应服务器发来的UI_UMS_ETHNETINFO_NOTIFY的函数
	* @return   LRESULT
	* @remarks	 
	*/
	LRESULT OnEthnetInfoNty( WPARAM wParam, LPARAM lParam );
	
	/**	 
	* 功能:  响应服务器发来的UI_UMS_REG_INFO_NOTIFY的函数
	* @return   LRESULT
	* @remarks	 
	*/
	LRESULT OnSipInfoNty( WPARAM wParam, LPARAM lParam );

	/**	 
	* 功能:  响应服务器发来的UI_UMS_REG_INFO_NOTIFY的函数
	* @return   LRESULT
	* @remarks	 
	*/
	LRESULT OnSipInfoRsp( WPARAM wParam, LPARAM lParam );

	/**	 
	* 功能:  响应服务器发来的UI_UMS_REG_SERV_RSP的函数
	* @return   LRESULT
	* @remarks	 
	*/
	LRESULT OnRegSipResult( WPARAM wParam, LPARAM lParam );
	
	/**	 
	* 功能:  响应服务器发来的UI_CNS_REG_GK_NTY的函数
	* @return   LRESULT
	* @remarks	 
	*/
	LRESULT OnGKInfoNty( WPARAM wParam, LPARAM lParam );

	/**	 

	* 功能:  响应服务器发来的UI_CNS_REG_GK_NTY的函数
	* @return   LRESULT
	* @remarks	 
	*/
	LRESULT OnGKInfoRsp( WPARAM wParam, LPARAM lParam );

	/**	 
	* 功能:  响应服务器发来的UI_CNS_REG_GK_RSP的函数
	* @return   LRESULT
	* @remarks	 
	*/
	LRESULT OnRegGKResult( WPARAM wParam, LPARAM lParam );
	
	/**	 
	* 功能:  响应服务器发来的UI_UMS_CMD_TIMEOUT的函数
	* @return   LRESULT
	* @remarks	 
	*/
	LRESULT OnTimeOut( WPARAM wParam, LPARAM lParam );

	/**	 
	* 功能:  响应服务器发来的UI_UMSTOOL_MSG_CONFCOUNT_NTY的函数
	* @return   LRESULT
	* @remarks	 
	*/
	LRESULT OnConfCount( WPARAM wParam, LPARAM lParam );

private:
	/**	 
	* 功能:  设置网络信息
	* @return   
	* @remarks	 
	*/
	void SetEthnetInfo();

	/**	 
	* 功能:  设置Sip信息
	* @return   
	* @remarks	 
	*/
	void SetSipInfo();

	/**	 
	* 功能:  设置GK信息
	* @return   
	* @remarks	 
	*/
	void SetGKInfo();

	/**	 
	* 功能:  检查所有数据
	* @return   bool : 表示数据是否有错误
	* @remarks	 
	*/
	bool CheckAll();

	/**	 
	* 功能:  保存所有数据
	* @return   void
	* @remarks	 
	*/
	void SaveAll();

	/**	 
	* 功能:  检查Ethnet数据
	* @return   bool : 表示数据是否有错误
	* @remarks	 
	*/
	bool CheckEthnet();

	/**	 
	* 功能:  检查Sip数据
	* @return   bool : 表示数据是否有错误
	* @remarks	 
	*/
	bool CheckSip();

	/**	 
	* 功能:  检查GK数据
	* @return   bool : 表示数据是否有错误
	* @remarks	 
	*/
	bool CheckGK();

	/**	 
	* 功能:  保存Ethnet
	* @return  
	* @remarks	 
	*/
	void SaveEthnet( TTPEthnetInfo &tTPEthnetInfo );

	/**	 
	* 功能:  保存Sip
	* @return  
	* @remarks	 
	*/
	void SaveSip( TTPSipRegistrarCfg &tTPSipRegistrarCfg );

	/**	 
	* 功能:  保存GK
	* @return  
	* @remarks	 
	*/
	void SaveGK( TTPGKCfg &tTPGKCfg );

	/**	 
	* 功能:  更新所有Btn状态
	* @return  
	* @remarks	 
	*/
	void UpdBtnState();

	/**	 
	* 功能: 重置所有类内成员变量
	* @return  
	* @remarks	 
	*/
	void ResetAllData();

	/**	 
	* 功能: 恢复Ums配置
	* @return  
	* @remarks	 
	*/
	void RecductUmsCfg();

private:
	//该逻辑单元对应的所有控件名
	const String m_strEdtUmsIp;
	const String m_strEdtSubnetMask;
	const String m_strEdtGateWay;
	const String m_strEdtSipIP;
	const String m_strBtnGKSwitch;
	const String m_strEdtGKIP;
	const String m_strBtnSave;
	const String m_strBtnReduction;
	const String m_strBtnExport;

	//该逻辑单元对应的所有数据是否变动
	BOOL m_bIsUmsIPChanged;
	BOOL m_bIsSubnetMaskChanged;
	BOOL m_bIsGateWayChanged;
	BOOL m_bIsSipIPChanged;
	BOOL m_bIsGKIPSwitchChanged;
	BOOL m_bIsGKIPChanged;
};

#define UMSCFGLOGICRPTR    CUmsCfgLogic::GetSingletonPtr()               //UmsCfglogic指针

#endif // !defined(AFX_UMSCFGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
