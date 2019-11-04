// cfgAudioPortLogic.h: interface for the CCfgAudioPortLogic class.
/*****************************************************************************
模块名      : CCfgAudioPortLogic
文件名      : cfgAudioPortLogic.h
相关文件    : 
文件实现功能: 相关配置中的音频配置界面
作者        : 景洋洋
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/01/04     1.0         景洋洋      创建
******************************************************************************/

#if !defined(AFX_CFGAUDIOPORTLOGIC_H__77D62CD0_FC1C_4BEF_91F2_3ED104CF6C3D__INCLUDED_)
#define AFX_CFGAUDIOPORTLOGIC_H__77D62CD0_FC1C_4BEF_91F2_3ED104CF6C3D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

class CCfgAudioPortLogic : public CLogicBase, public ISingleTon<CCfgAudioPortLogic> 
{
public:
	CCfgAudioPortLogic();
	virtual ~CCfgAudioPortLogic();

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

	/** 功能:  判断audio配置界面是否改动(切换table页时界面提醒)
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
    bool IsCfgAudioChange();
	
	/**	 
	* 功能: 获取界面上数据变化控件的数目
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
		
	/** 功能:  保存界面中设置项
	*  @param[in] IArgs  点击操作
	*  @return 
	*  @remarks   
	*/	
	bool OnBtnSave( const IArgs& args );
		
	/** 功能:  恢复界面初始项
	*  @param[in] IArgs  点击操作
	*  @return 
	*  @remarks   
	*/		
	bool OnBtnCancel( const IArgs& args );

	/** 功能:  恢复默认配置的按钮
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnBtnDefault( const IArgs& args );
		
	/** 功能:  设置音频组数据
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	void SetAudioData();
		
	/** 功能:  初始化音频接口界面控件
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	void InitCtrlEnable();
					
	/** 功能:  保存音频设置界面的1、2、3
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	bool SaveGroup1();
			
	/** 功能:  保存音频设置界面的4、5、6
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool SaveGroup2();
				
	/** 功能:  保存音频设置界面的7、8、9
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool SaveGroup3();
				
	/** 功能:  保存音频设置界面中各个组中的10
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	bool SaveGroup10();
				
	/** 功能:  更新音频设置界面的Group1
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool UpdateGroup1( TTpAudioPortInfo& tAudioPortInfo );
					
	/** 功能:  更新音频设置界面的Group2
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool UpdateGroup2( TTpAudioPortInfo& tAudioPortInfo );
						
	/** 功能:  更新音频设置界面的Group3
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool UpdateGroup3( TTpAudioPortInfo& tAudioPortInfo );
						
	/** 功能:  接收服务器关于音频设置的消息并更新界面
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	HRESULT OnUpdateAudioNty( WPARAM wparam, LPARAM lparam );
						
	/** 功能:  根据服务器接收默认音频设置的反馈消息并更新界面
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	HRESULT OnDefaultAudioNty( WPARAM wparam, LPARAM lparam );

	HRESULT OnSetDesktopMicNty( WPARAM wparam, LPARAM lparam );
	
	HRESULT OnSetDesktopMicInd( WPARAM wparam, LPARAM lparam );	

	HRESULT OnSetMic10InfoInd( WPARAM wparam, LPARAM lparam );	
	
	/** 功能:  根据slider变化,改变增益的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSliderGain1Changed( const IArgs& args );
						
	/** 功能:  根据slider变化,改变背景噪声的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSliderBNA1Changed( const IArgs& args );
						
	/** 功能:  根据edit变化,改变输入框的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnEditGain1Changed( const IArgs& args );
						
	/** 功能:  根据edit变化,改变输入框的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnEditBNA1Changed( const IArgs& args );
						
	/** 功能:  根据slider变化,改变增益的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSliderGain2Changed( const IArgs& args );
						
	/** 功能:  根据slider变化,改变背景噪声的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSliderBNA2Changed( const IArgs& args );
						
	/** 功能:  根据edit变化,改变输入框的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnEditGain2Changed( const IArgs& args );
						
	/** 功能:  根据edit变化,改变输入框的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnEditBNA2Changed( const IArgs& args );
												
	/** 功能:  根据slider变化,改变增益的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSliderGain3Changed( const IArgs& args );
						
	/** 功能:  根据slider变化,改变背景噪声的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSliderBNA3Changed( const IArgs& args );
						
	/** 功能:  根据edit变化,改变输入框的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnEditGain3Changed( const IArgs& args );
						
	/** 功能:  根据edit变化,改变输入框的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnEditBNA3Changed( const IArgs& args );
												
	/** 功能:  根据slider变化,改变增益的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSliderGain4Changed( const IArgs& args );
						
	/** 功能:  根据slider变化,改变背景噪声的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSliderBNA4Changed( const IArgs& args );
						
	/** 功能:  根据edit变化,改变输入框的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnEditGain4Changed( const IArgs& args );
						
	/** 功能:  根据edit变化,改变输入框的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnEditBNA4Changed( const IArgs& args );
												
	/** 功能:  根据slider变化,改变增益的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSliderGain5Changed( const IArgs& args );
						
	/** 功能:  根据slider变化,改变背景噪声的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSliderBNA5Changed( const IArgs& args );
						
	/** 功能:  根据edit变化,改变输入框的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnEditGain5Changed( const IArgs& args );
						
	/** 功能:  根据edit变化,改变输入框的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnEditBNA5Changed( const IArgs& args );
												
	/** 功能:  根据slider变化,改变增益的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSliderGain6Changed( const IArgs& args );
						
	/** 功能:  根据slider变化,改变背景噪声的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSliderBNA6Changed( const IArgs& args );
						
	/** 功能:  根据edit变化,改变输入框的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnEditGain6Changed( const IArgs& args );
						
	/** 功能:  根据edit变化,改变输入框的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnEditBNA6Changed( const IArgs& args );
												
	/** 功能:  根据slider变化,改变增益的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSliderGain7Changed( const IArgs& args );
						
	/** 功能:  根据slider变化,改变背景噪声的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSliderBNA7Changed( const IArgs& args );
						
	/** 功能:  根据edit变化,改变输入框的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnEditGain7Changed( const IArgs& args );
						
	/** 功能:  根据edit变化,改变输入框的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnEditBNA7Changed( const IArgs& args );
												
	/** 功能:  根据slider变化,改变增益的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSliderGain8Changed( const IArgs& args );
						
	/** 功能:  根据slider变化,改变背景噪声的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSliderBNA8Changed( const IArgs& args );
						
	/** 功能:  根据edit变化,改变输入框的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnEditGain8Changed( const IArgs& args );
						
	/** 功能:  根据edit变化,改变输入框的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnEditBNA8Changed( const IArgs& args );
												
	/** 功能:  根据slider变化,改变增益的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSliderGain9Changed( const IArgs& args );
						
	/** 功能:  根据slider变化,改变背景噪声的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSliderBNA9Changed( const IArgs& args );
						
	/** 功能:  根据edit变化,改变输入框的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnEditGain9Changed( const IArgs& args );
						
	/** 功能:  根据edit变化,改变输入框的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnEditBNA9Changed( const IArgs& args );
												
	/** 功能:  根据slider变化,改变增益的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSliderGain10Changed( const IArgs& args );
						
	/** 功能:  根据slider变化,改变背景噪声的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSliderBNA10Changed( const IArgs& args );
						
	/** 功能:  根据edit变化,改变输入框的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnEditGain10Changed( const IArgs& args );
						
	/** 功能:  根据edit变化,改变输入框的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnEditBNA10Changed( const IArgs& args );
												
	/** 功能:  未选择audio1之后界面做出的响应
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnNoSelAudio1( const IArgs& args );
						
	/** 功能:  选择audio1之后界面做出的响应
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSelAudio1( const IArgs& args );
													
	/** 功能:  未选择audio2之后界面做出的响应
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnNoSelAudio2( const IArgs& args );
						
	/** 功能:  选择audio2之后界面做出的响应
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSelAudio2( const IArgs& args );
												
	/** 功能:  未选择audio3之后界面做出的响应
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnNoSelAudio3( const IArgs& args );
						
	/** 功能:  选择audio3之后界面做出的响应
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSelAudio3( const IArgs& args );
												
	/** 功能:  未选择audio4之后界面做出的响应
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnNoSelAudio4( const IArgs& args );
						
	/** 功能:  选择audio4之后界面做出的响应
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSelAudio4( const IArgs& args );
												
	/** 功能:  未选择audio5之后界面做出的响应
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnNoSelAudio5( const IArgs& args );
						
	/** 功能:  选择audio5之后界面做出的响应
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSelAudio5( const IArgs& args );
												
	/** 功能:  未选择audio6之后界面做出的响应
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnNoSelAudio6( const IArgs& args );
						
	/** 功能:  选择audio6之后界面做出的响应
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSelAudio6( const IArgs& args );
												
	/** 功能:  未选择audio7之后界面做出的响应
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnNoSelAudio7( const IArgs& args );
						
	/** 功能:  选择audio7之后界面做出的响应
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSelAudio7( const IArgs& args );
												
	/** 功能:  未选择audio8之后界面做出的响应
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnNoSelAudio8( const IArgs& args );
						
	/** 功能:  选择audio8之后界面做出的响应
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSelAudio8( const IArgs& args );
												
	/** 功能:  未选择audio9之后界面做出的响应
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnNoSelAudio9( const IArgs& args );
						
	/** 功能:  选择audio9之后界面做出的响应
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSelAudio9( const IArgs& args );

	/** 功能:  选择audio10之后界面做出的响应
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSelAudioPort10( const IArgs& args );
												
	/** 功能:  未选择audio10之后界面做出的响应
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnNoSelAudio10( const IArgs& args );
						
	/** 功能:  选择audio10之后界面做出的响应
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSelAudio10( const IArgs& args );

	/** 功能:  选择非桌面麦克风之后界面做出的响应
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSelNoDesktopAudio( const IArgs& args );
						
	/** 功能:  选择卡农1幻象供电按钮之后,判断数据是否改变
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnBtnSwitchSimPower1( const IArgs& args );
						
	/** 功能:  选择卡农2幻象供电按钮之后,判断数据是否改变
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnBtnSwitchSimPower2( const IArgs& args );
						
	/** 功能:  选择卡农3幻象供电按钮之后,判断数据是否改变
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnBtnSwitchSimPower3( const IArgs& args );
						
	/** 功能:  选择卡农4幻象供电按钮之后,判断数据是否改变
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnBtnSwitchSimPower4( const IArgs& args );
						
	/** 功能:  选择卡农5幻象供电按钮之后,判断数据是否改变
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnBtnSwitchSimPower5( const IArgs& args );
						
	/** 功能:  选择卡农6幻象供电按钮之后,判断数据是否改变
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnBtnSwitchSimPower6( const IArgs& args );
						
	/** 功能:  选择卡农7幻象供电按钮之后,判断数据是否改变
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnBtnSwitchSimPower7( const IArgs& args );
						
	/** 功能:  选择卡农8幻象供电按钮之后,判断数据是否改变
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnBtnSwitchSimPower8( const IArgs& args );
						
	/** 功能:  选择卡农9幻象供电按钮之后,判断数据是否改变
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnBtnSwitchSimPower9( const IArgs& args );
						
	/** 功能:  选择卡农10幻象供电按钮之后,判断数据是否改变
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnBtnSwitchSimPower10( const IArgs& args );
								
	/** 功能:  获取界面卡农10中的数据
	*  @param[in] nGroup  主音频组别
	*  @return 
	*  @remarks   
	*/	
	void GetAudio10( s32 nGroup );

	/** 功能:  切换到其他界面时提醒是否保存的窗口	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool SaveMsgBox();

	/** 功能:  获取lib库中的音频接口数据	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	void GetAudioInfo();

	/** 功能:  获取界面幻想开关状态然后与lib库中比对,更新基类m_vctWndName数目
	*  @param[in] strWndName 窗口名称	nGroup 主音频组别	nNum 序号   
	*  @return 
	*  @remarks   
	*/	
	void UpdateSimPowerNum( String strWndName, s32 nGroup, s32 nNum );

	/** 功能:  获取界面增益的值然后与lib库中比对,更新界面
				Edit框中数据和基类m_vctWndName的数目
	*  @param[in] strWndName slider控件名称 strEditName edit框名称	nGroup 主音频组别	nNum 序号   
	*  @return 
	*  @remarks   
	*/	
	void UpdateGainNum( String strGainName, String strEditName, s32 nGroup, s32 nNum );

	/** 功能:  获取界面背景噪声的值然后与lib库中比对,更新界面
				Edit框中数据和基类m_vctWndName的数目
	*  @param[in] strWndName slider控件名称 strEditName edit框名称	nGroup 主音频组别	nNum 序号   
	*  @return 
	*  @remarks   
	*/	
	void UpdateBNANum( String strBNAName, String strEditName, s32 nGroup, s32 nNum );

	/** 功能:  根据edit框中的数据更新增益slider控件
				检查BNA数据是否变化,更新基类m_vctWndName数目
	*  @param[in] strWndName slider控件名称 strEditName edit框名称   nGroup 主音频组别	nNum 序号  
	*  @return 
	*  @remarks   
	*/	
	void UpdateGainEdit( String strEditName, String strSliderName, s32 nGroup, s32 nNum );

	/** 功能:  根据edit框中的数据更新背景噪声slider控件
				检查BNA数据是否变化,更新基类m_vctWndName数目
	*  @param[in] strWndName slider控件名称 strEditName edit框名称   nGroup 主音频组别	nNum 序号  
	*  @return 
	*  @remarks   
	*/	
	void UpdateBNAEdit( String strEditName, String strSliderName, s32 nGroup, s32 nNum );

	/** 功能:  根据check框是否被选中来更改同一组控件是否显示及基类m_vctWndName的数目
	*  @param[in] strCheckName check控件名称	nGroup 主音频组别	nNum 序号  
					strShmShow 选中执行显示方案	strShmHide 未选中执行隐藏方案
	*  @return 
	*  @remarks   
	*/	
	bool UpdateCheckNum( String strCheckName, s32 nGroup, s32 nNum, String strShmShow, String strShmHide );

	/** 功能:  设置音频接口默认数据	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	void SetDefaultAudioInfo();
		
private:
	TTpAudioPortInfo m_atAudioPortInfo[3];
	TTpAudioPortInfo m_atOldAudioPortInfo[3];
	TTpMic10Info m_tTpMic10Info;
	TTpMic10Info m_tOldTpMic10Info;
	const String m_strAudioPort1;							//GANNON1
	const String m_strAudioPort2;							//GANNON2
	const String m_strAudioPort3;							//GANNON3
	const String m_strAudioPort4;							//GANNON4
	const String m_strAudioPort5;							//GANNON5
	const String m_strAudioPort6;							//GANNON6
	const String m_strAudioPort7;							//GANNON7
	const String m_strAudioPort8;							//GANNON8
	const String m_strAudioPort9;							//GANNON9
	const String m_strAudioPort10;                          //GANNON10
	const String m_strAudioPort110;							//GANNON110
	const String m_strAudioPort210;							//GANNON210
	const String m_strAudioPort310;							//GANNON310
	const String m_strNoPort10;								//GANNON10没有配置
	const String m_strNoDesktopAudioGroup;                  //非桌面麦克风

	BOOL m_bNodeskTopBtn;
	BOOL m_bOldNodeskTopBtn;
};

#endif // !defined(AFX_CFGAUDIOPORTLOGIC_H__77D62CD0_FC1C_4BEF_91F2_3ED104CF6C3D__INCLUDED_)
