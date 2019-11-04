// cfgEqLogic.h: interface for the CCfgEqLogic class.
//
//////////////////////////////////////////////////////////////////////
/*****************************************************************************
文件名      : CfgEqLogic.h
相关文件    : 
文件实现功能: 相关配置中的均衡器配置界面
作者        : 景洋洋
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/02/20     1.0         景洋洋      创建
******************************************************************************/
#if !defined(AFX_CFGEQLOGIC_H__54D81828_1457_401C_A4DF_597F9F16F6EF__INCLUDED_)
#define AFX_CFGEQLOGIC_H__54D81828_1457_401C_A4DF_597F9F16F6EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

class CCfgEqLogic : public CLogicBase, public ISingleTon<CCfgEqLogic>  
{
public:
	CCfgEqLogic();
	virtual ~CCfgEqLogic();
	
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
	bool IsCfgEqChange();

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

	/** 功能:  切换到其他界面时提醒是否保存的窗口	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool SaveMsgBox();

	/** 功能:  接收服务器端发过来的消息然后更新均衡器状态
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnUpdateEqNty( WPARAM wParam, LPARAM lParam );

	/** 功能:  根据服务器接收默认音频均衡器设置的反馈消息并更新界面
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	LRESULT OnDefaultEqNty( WPARAM wParam, LPARAM lParam );

	/** 功能:  设置音频均衡器默认数据	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	void SetEqDefaultData();
															
	/** 功能:  设置均衡器信息
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	void SetEqInfo();
														
	/** 功能:  设置均衡器单个频率信息
	*  @param[in] strWndName 频率窗口名称 nGroup 主音频组别	nNum 序号  
	*  @return 
	*  @remarks   
	*/	
	void SetEqRate( String strWndName, s32 nGroup, s32 nNum );

	/** 功能:  获取lib库中的音频均衡器数据	
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	void GetEqData();
														
	/** 功能:  主音频1组中的slider变化,改变Eq100控件的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld1Eq100Changed( const IArgs& args );
											
	/** 功能:  主音频1组中的slider变化,改变Eq200控件的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld1Eq200Changed( const IArgs& args );
														
	/** 功能:  主音频1组中的slider变化,改变Eq400控件的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld1Eq400Changed( const IArgs& args );
															
	/** 功能:  主音频1组中的slider变化,改变Eq600控件的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld1Eq600Changed( const IArgs& args );
															
	/** 功能:  主音频1组中的slider变化,改变Eq1K控件的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld1Eq1KChanged( const IArgs& args );
															
	/** 功能:  主音频1组中的slider变化,改变Eq3K控件的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld1Eq3KChanged( const IArgs& args );
															
	/** 功能:  主音频1组中的slider变化,改变Eq6K控件的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld1Eq6KChanged( const IArgs& args );
															
	/** 功能:  主音频1组中的slider变化,改变Eq12K控件的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld1Eq12KChanged( const IArgs& args );
																	
	/** 功能:  主音频1组中的slider变化,改变Eq14K控件的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld1Eq14KChanged( const IArgs& args );
															
	/** 功能:  主音频1组中的slider变化,改变Eq16K控件的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld1Eq16KChanged( const IArgs& args );
														
	/** 功能:  主音频2组中的slider变化,改变Eq100控件的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld2Eq100Changed( const IArgs& args );
											
	/** 功能:  主音频2组中的slider变化,改变Eq200控件的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld2Eq200Changed( const IArgs& args );
														
	/** 功能:  主音频2组中的slider变化,改变Eq400控件的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld2Eq400Changed( const IArgs& args );
															
	/** 功能:  主音频2组中的slider变化,改变Eq600控件的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld2Eq600Changed( const IArgs& args );
															
	/** 功能:  主音频2组中的slider变化,改变Eq1K控件的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld2Eq1KChanged( const IArgs& args );
															
	/** 功能:  主音频2组中的slider变化,改变Eq3K控件的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld2Eq3KChanged( const IArgs& args );
															
	/** 功能:  主音频2组中的slider变化,改变Eq6K控件的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld2Eq6KChanged( const IArgs& args );
															
	/** 功能:  主音频2组中的slider变化,改变Eq12K控件的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld2Eq12KChanged( const IArgs& args );
																
	/** 功能:  主音频2组中的slider变化,改变Eq14K控件的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld2Eq14KChanged( const IArgs& args );
															
	/** 功能:  主音频2组中的slider变化,改变Eq16K控件的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld2Eq16KChanged( const IArgs& args );
																
	/** 功能:  主音频3组中的slider变化,改变Eq100控件的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld3Eq100Changed( const IArgs& args );
											
	/** 功能:  主音频3组中的slider变化,改变Eq200控件的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld3Eq200Changed( const IArgs& args );
														
	/** 功能:  主音频3组中的slider变化,改变Eq400控件的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld3Eq400Changed( const IArgs& args );
															
	/** 功能:  主音频3组中的slider变化,改变Eq600控件的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld3Eq600Changed( const IArgs& args );
															
	/** 功能:  主音频3组中的slider变化,改变Eq1K控件的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld3Eq1KChanged( const IArgs& args );
															
	/** 功能:  主音频3组中的slider变化,改变Eq3K控件的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld3Eq3KChanged( const IArgs& args );
															
	/** 功能:  主音频3组中的slider变化,改变Eq6K控件的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld3Eq6KChanged( const IArgs& args );
															
	/** 功能:  主音频3组中的slider变化,改变Eq12K控件的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld3Eq12KChanged( const IArgs& args );
																
	/** 功能:  主音频3组中的slider变化,改变Eq14K控件的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld3Eq14KChanged( const IArgs& args );
															
	/** 功能:  主音频3组中的slider变化,改变Eq16K控件的值
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnSld3Eq16KChanged( const IArgs& args );
				
	/** 功能:  控制主音频1组中均衡器的开关,改变slider状态,判断数据是否改变
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnBtnSwitchEq1( const IArgs& args );
						
	/** 功能:  控制主音频2组中均衡器的开关,改变slider状态,判断数据是否改变
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnBtnSwitchEq2( const IArgs& args );
							
	/** 功能:  控制主音频3组中均衡器的开关,改变slider状态,判断数据是否改变
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnBtnSwitchEq3( const IArgs& args );
							
	/** 功能:  判断Eq频率数据是否改变,更新基类中m_vctWndName数目
	*  @param[in] strWndName 频率窗口名称 nGroup 主音频组别	nNum 序号 
	*  @return 
	*  @remarks   
	*/	
	void CheckEqRate( String strWndName, s32 nGroup, s32 nNum );

	/** 功能:  保存主音频1Eq
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool SaveEq1();

	/** 功能:  保存主音频2Eq
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool SaveEq2();
	
	/** 功能:  保存主音频3Eq
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool SaveEq3();
														
	/** 功能:  保存均衡器单个频率信息
	*  @param[in] strWndName 频率窗口名称 nGroup 主音频组别	nNum 序号  
	*  @return 
	*  @remarks   
	*/	
	void SaveEqRate( String strWndName, s32 nGroup, s32 nNum );
			
private:
	TTPEqualizer m_atEqInfo[3];
	TTPEqualizer m_atOldEqInfo[3];
	const String m_strBtnEq1Switch;			//主音频1均衡器开关
	const String m_strBtnEq2Switch;			//主音频2均衡器开关
	const String m_strBtnEq3Switch;			//主音频3均衡器开关
};

#endif // !defined(AFX_CFGEQLOGIC_H__54D81828_1457_401C_A4DF_597F9F16F6EF__INCLUDED_)
