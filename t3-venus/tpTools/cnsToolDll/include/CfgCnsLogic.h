// CfgCnsLogic.h: interface for the CCfgCnsLogic class.
/*****************************************************************************
文件名      : CfgCnsLogic.h
相关文件    : 
文件实现功能: 相关配置中的cns配置界面
作者        : 景洋洋
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/01/04     1.0         景洋洋      创建
******************************************************************************/
#if !defined(AFX_CFGCNSLOGIC_H__5E754113_422F_4B4C_A8B0_D9907522897E__INCLUDED_)
#define AFX_CFGCNSLOGIC_H__5E754113_422F_4B4C_A8B0_D9907522897E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

class CCfgCnsLogic : public CLogicBase, public ISingleTon<CCfgCnsLogic>
{
public:
	CCfgCnsLogic();
	virtual ~CCfgCnsLogic();
	
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
	/** 功能:  判断cns配置页面的消息是否改变
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	bool IsCfgCnsChange();
	
	/**	 
	* 功能: 更新上传进度
	* @return   bool
	* @remarks  
	*/
	bool OnUploadProgress( const IArgs & arg );

	/**	 
	* 功能: 上传核心
	* @param    const String strRemotePath      [in]     linux端待存储路径
	* @param    const String strLocalFile       [in]     待传输的文件全路径 
	* @param    const String strCheckFileName   [in]     待传输的文件名 
	* @return   bool
	* @remarks  
	*/
	BOOL UploadCore( const String& strRemotePath, const String& strLocalFile, const String& strCheckFileName ); 

	/**	 
	* 功能: 获取cns界面上数据变化控件的数目
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
	/** 功能:  升级的按钮
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	bool OnBtnUpgrade( const IArgs& args );
	/** 功能:  重启的按钮
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	bool OnBtnReboot( const IArgs& args );
	/** 功能:  导出配置的按钮
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	bool OnBtnExport( const IArgs& args );
	/** 功能:  导入配置的按钮
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	bool OnBtnImport( const IArgs& args );
	/** 功能:  开启NAT设置的按钮
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	bool OnBtnSwitchNAT( const IArgs& args );

	/** 功能:  接收服务器端发过来的消息然后更新NAT状态
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnUpdateNATNty( WPARAM wParam, LPARAM lParam );

	/** 功能:  接收服务器端发过来的消息然后更新网络配置状态
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnUpdateEthnetNty( WPARAM wParam, LPARAM lParam );

	LRESULT OnSetCfgEthnetStateNty( WPARAM wParam, LPARAM lParam );

	LRESULT OnSetCfgWEthnetNty( WPARAM wParam, LPARAM lParam );

	LRESULT OnSetCfgWEthnetRsp( WPARAM wParam, LPARAM lParam );
    //云服务器配置回复
    LRESULT OnSetCloudServerInfoInd( WPARAM wParam, LPARAM lParam );

	/** 功能:  接收服务器端发过来的消息然后更新会场名称及E164号
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnUpdateCnsInfoNty( WPARAM wParam, LPARAM lParam );

	/** 功能:  接收服务器端发过来的升级T300的结果
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnUpgradeCnsNty( WPARAM wParam, LPARAM lParam );

	/** 功能:  保存会场名称和E164号部分
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool SaveNameAndE164( EmTpIpNameNatSyn emTpIpType );
	/** 功能:  保存网络配置
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
//	bool SaveNet();

	/** 功能:  保存静态NAT配置
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool SaveNAT( EmTpIpNameNatSyn emTpIpType );

	bool SaveDoubleNet( EmTpIpNameNatSyn emTpIpType );
	/** 功能:  保存网络配置	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool SaveEthnetCfg( EmTpIpNameNatSyn emTpIpType );
	/** 功能:  切换到其他界面时提醒是否保存的窗口	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool SaveMsgBox();

	/** 功能:  保存配置时聚焦在出错的窗口	
	*  @param[in] strWindow   窗口名称
	*  @return 
	*  @remarks   
	*/	
	void FocusWindow(String strWindow);	
	
	/** 功能:  改变会场名称控件时的响应函数	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnChangedName( const IArgs& args );	
	
	/** 功能:  改变会场E164号控件时的响应函数	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnChangedE164( const IArgs& args );	
	
	/** 功能:  改变cns地址控件时的响应函数	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnChangedCnsIp( const IArgs& args );	
	
	/** 功能:  改变默认网关控件时的响应函数	
	*  @param[in]
	*  @return 
	*  @remarks   
	*/	
	bool OnChangedGatewayIp( const IArgs& args );	
	
	/** 功能:  改变子网掩码控件时的响应函数	
	*  @param[in]
	*  @return 
	*  @remarks   
	*/	
	bool OnChangedSubMaskIp( const IArgs& args );
	
	/** 功能:  改变cns地址控件LAN1时的响应函数	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnChangedCnsLan1Ip( const IArgs& args );	
	
	/** 功能:  改变默认网关控件LAN1时的响应函数	
	*  @param[in]
	*  @return 
	*  @remarks   
	*/	
	bool OnChangedGatewayLan1Ip( const IArgs& args );	
	
	/** 功能:  改变子网掩码控件LAN1时的响应函数	
	*  @param[in]
	*  @return 
	*  @remarks   
	*/	
	bool OnChangedSubMaskLan1Ip( const IArgs& args );

	/** 功能:  改变cns地址控件LAN2时的响应函数	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnChangedCnsLan2Ip( const IArgs& args );	
	
	/** 功能:  改变默认网关控件LAN1时的响应函数	
	*  @param[in]
	*  @return 
	*  @remarks   
	*/	
	bool OnChangedGatewayLan2Ip( const IArgs& args );	
	
	/** 功能:  改变子网掩码控件LAN1时的响应函数	
	*  @param[in]
	*  @return 
	*  @remarks   
	*/	
	bool OnChangedSubMaskLan2Ip( const IArgs& args );
	
	/** 功能:  改变NAT地址控件时的响应函数	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnChangedNATIp( const IArgs& args );
	
	bool OnSelNetInterfaceStyle( const IArgs& args );
							
	/** 功能:  设置NAT地址
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	void SetNATData();
														
	/** 功能:  设置会场名称及会场E164号
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	void SetCnsInfoData();
														
	/** 功能:  设置cns网络配置的数据
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	void SetEthnetCfgData();

	void SetEthnetSwitchtype();

	//设置双网口数据
	void SetWEthnetInfo();

	/** 功能:  收到会议状态的信息
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	LRESULT OnConfStateNty( WPARAM wparam, LPARAM lparam);

	/** 功能:  收到版本通知信息
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	LRESULT OnVerInfoNty( WPARAM wparam, LPARAM lparam);
	bool CheckNameAndE164(bool &bChange );
	bool CheckNet( bool &bChange );
	bool CheckDoubleNet(bool &bChange);
	bool CheckNAt( bool &bChange);
private:
	EmFtpStatus m_emFileFtpStatus;
	CFtpCtrl m_cFtp;
	Window* m_pWnd;
	std::vector<String> m_vecConfFile;
	const String m_strBtnNetBackUp;         //网口备份
	const String m_strBtnDoubleNet;         //双网口
	const String m_strEdtIp;				//CNS地址
    const String m_strEdtSubMask;			//子网掩码
    const String m_strEdtGateWay;			//默认网关
	const String m_strEdtLan1Ip;            //Lan1 IP
	const String m_strEdtSubMaskLan1;       //Lan1掩码
	const String m_strEdtGateWayLan1;		//Lan1默认网关
	const String m_strEdtLan2Ip;            //Lan2 IP
	const String m_strEdtSubMaskLan2;       //Lan2掩码
	const String m_strEdtGateWayLan2;		//Lan2默认网关
	const String m_strNameEdit;				//会场名称
	const String m_strBtnNATSwitch;			//NAT开关
	const String m_strEdtNatIP;				//NAT地址
	const String m_strName164Edit;			//会场E164号码
	BOOL m_bNameChange;
	BOOL m_bCnsIp;
	BOOL m_bSubMask;
	BOOL m_bGateWay;
	BOOL m_bCnsIpLan1;
	BOOL m_bSubMaskLanl;
	BOOL m_bGateWayLan1;
	BOOL m_bCnsIpLan2;
	BOOL m_bSubMaskLan2;
	BOOL m_bGateWayLan2;

	TTPWEthnetInfo  m_tTPWEthnetInfo;
	EmEthState m_emEthState;
    BOOL m_bCloudServerEnable;  //云服务是否开启
};

#endif // !defined(AFX_CFGCNSLOGIC_H__5E754113_422F_4B4C_A8B0_D9907522897E__INCLUDED_)
