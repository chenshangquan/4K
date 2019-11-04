// cfgMixLogic.h: interface for the CCfgMixLogic class.
//////////////////////////////////////////////////////////////////////
/*****************************************************************************
文件名      : CfgMixLogic.h
相关文件    : 
文件实现功能: 相关配置中的混音配置界面
作者        : 景洋洋
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/02/20     1.0         景洋洋      创建
******************************************************************************/
#if !defined(AFX_CFGMIXLOGIC_H__59D20473_A152_4386_9B30_20974F68D33B__INCLUDED_)
#define AFX_CFGMIXLOGIC_H__59D20473_A152_4386_9B30_20974F68D33B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

class CCfgMixLogic : public CLogicBase, public ISingleTon<CCfgMixLogic>
{
public:
	CCfgMixLogic();
	virtual ~CCfgMixLogic();
	
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
	bool IsCfgMixChange();

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
	/** 功能:  恢复默认配置的按钮
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnBtnDefault( const IArgs& args );

	/** 功能:  接收服务器端发过来的消息然后更新混音状态
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnUpdateMixerNty( WPARAM wParam, LPARAM lParam );

	/** 功能:  根据服务器接收默认混音设置的反馈消息并更新界面
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnDefaultMixerNty( WPARAM wParam, LPARAM lParam );

	/** 功能:  获取cns端的混音数据
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	void GetMixInfo();

	/** 功能:  根据接收的数据更新混音状态
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool SetMixState();

	/** 功能:  保存单路主音频组1的混音路数
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool SaveGroup1();

	/** 功能:  保存单路主音频组2的混音路数
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool SaveGroup2();

	/** 功能:  保存单路主音频组3的混音路数
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool SaveGroup3();

	/** 功能:  保存会场主音频的混音路数
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool SaveRoomGroup();

	/** 功能:  切换到其他界面时提醒是否保存的窗口	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool SaveMsgBox();
						
	/** 功能:  选择主音频组1,对比lib库中数据改变右下角保存取消按钮状态
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSelAudio1Group( const IArgs& args );
						
	/** 功能:  选择主音频组2,对比lib库中数据改变右下角保存取消按钮状态
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSelAudio2Group( const IArgs& args );
								
	/** 功能:  选择主音频组3,对比lib库中数据改变右下角保存取消按钮状态
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSelAudio3Group( const IArgs& args );
								
	/** 功能:  选择混音路数,对比lib库中数据改变右下角保存取消按钮状态
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSelMixGroup( const IArgs& args );

	/** 功能:  设置混音默认数据	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	void SetDefaultMixInfo();
					
private:
	u8 m_aAudioMixerInfo[4];
	u8 m_aOldAudioMixerInfo[4];
	
	const String m_strAudio1Group1;							//主音频组1中的1
	const String m_strAudio1Group2;							//主音频组1中的2
	const String m_strAudio1Group3;							//主音频组1中的3
	const String m_strAudio1Group4;							//主音频组1中的4
	const String m_strAudio2Group1;							//主音频组2中的1
	const String m_strAudio2Group2;							//主音频组2中的2
	const String m_strAudio2Group3;							//主音频组2中的3
	const String m_strAudio2Group4;							//主音频组2中的4
	const String m_strAudio3Group1;							//主音频组3中的1
	const String m_strAudio3Group2;							//主音频组3中的2
	const String m_strAudio3Group3;							//主音频组3中的3
	const String m_strAudio3Group4;							//主音频组3中的4
	const String m_strMixGroup1;							//混音路数中的1
	const String m_strMixGroup2;							//混音路数中的2
	const String m_strMixGroup3;							//混音路数中的3

};

#endif // !defined(AFX_CFGMIXLOGIC_H__59D20473_A152_4386_9B30_20974F68D33B__INCLUDED_)
