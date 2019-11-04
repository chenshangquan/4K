/*****************************************************************************
模块名      : CSetContrastAreaLogic
文件名      : SetContrastAreaLogic.h
相关文件    : 
文件实现功能: 设置对比区域参数
作者        : 杨奇峰
版本        : V1.0  Copyright(C) 2017-2018 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2017/04/25     1.0         杨奇峰      创建
******************************************************************************/
// SetContrastAreaLogic.h: interface for the CSetContrastAreaLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SETCONTRASTAREALOGIC_H__E6D544B7_DA04_4D05_BCB4_10015F3DDCBC__INCLUDED_)
#define AFX_SETCONTRASTAREALOGIC_H__E6D544B7_DA04_4D05_BCB4_10015F3DDCBC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class Data_BtnInfo : public IData
{
public:
	Data_BtnInfo() : IData( "BtnInfo" ){}
    Data_BtnInfo( int Btntype ) : IData( "BtnInfo" ), m_dwBtnInfo( Btntype ){}
    
	IData* Clone()
    {
        Data_BtnInfo* pData = new Data_BtnInfo( m_dwBtnInfo );
        pData->SetDataKey( GetDataKey() );
        return pData;
    }
	
    int m_dwBtnInfo;
};

class CSetContrastAreaLogic: public CLogicBase,public ISingleTon<CSetContrastAreaLogic>
{
public:
	CSetContrastAreaLogic();
	virtual ~CSetContrastAreaLogic();

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
	virtual void UnRegFunc();
	/** 功能:  初始化窗口
	*  @param[in] 
	*  @return 
	*  @remarks  在读取xml文件时候调用,根据里面的内容初始化窗口
	*/	
    virtual bool InitWnd( const IArgs & arg ); 

   /**	 
	* 功能:  清空所有状态和数据
	* @return   
	* @remarks	 
	*/
    virtual void Clear();

public:

	bool OnBtnClose( const IArgs & arg );

	bool OnEndDragBtn( const IArgs & arg );

	/** 功能: 设置矩形区域是否显示
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/
	bool OnShowRectSwitchBtnChange( const IArgs & arg );

	//设置对比区域快照图片，有就设置，没有就空着
	void SetContrastAreaImage( const string strFileName );

	/* 矩形A 长宽 */
	bool OnAAreaWidthEditChange( const IArgs & arg );
	bool OnAAreaWidthEditKillFocus( const IArgs & arg );
	bool OnAAreaHeightEditChange( const IArgs & arg );
	bool OnAAreaHeightEditKillFocus( const IArgs & arg );

    /* 矩形B 长宽 */
	bool OnBAreaWidthEditChange( const IArgs & arg );
	bool OnBAreaWidthEditKillFocus( const IArgs & arg );
	bool OnBAreaHeightEditChange( const IArgs & arg );
	bool OnBAreaHeightEditKillFocus( const IArgs & arg );

	/* 矩形C 长宽 */
	bool OnCAreaWidthEditChange( const IArgs & arg );
	bool OnCAreaWidthEditKillFocus( const IArgs & arg );
	bool OnCAreaHeightEditChange( const IArgs & arg );
	bool OnCAreaHeightEditKillFocus( const IArgs & arg );

	/* 矩形D 长宽 */
	bool OnDAreaWidthEditChange( const IArgs & arg );
	bool OnDAreaWidthEditKillFocus( const IArgs & arg );
	bool OnDAreaHeightEditChange( const IArgs & arg );
	bool OnDAreaHeightEditKillFocus( const IArgs & arg );

	bool OnStartCalcBtnClick( const IArgs & arg );

public:
	
	HRESULT OnSecBoundaryNty( WPARAM wparam, LPARAM lparam );
	HRESULT OnChooseRectangleInd( WPARAM wparam, LPARAM lparam );
	
	HRESULT OnShowRectRegionInd( WPARAM wparam, LPARAM lparam );
	
	HRESULT OnCamOutputInfoNty( WPARAM wparam, LPARAM lparam );
	HRESULT OnCamOutputInfoInd( WPARAM wparam, LPARAM lparam );

	HRESULT OnSetDefaultParamNty( WPARAM wparam, LPARAM lparam );

	HRESULT OnSetOnColorSwitchInd( WPARAM wparam, LPARAM lparam );
	
protected: 
	virtual void RegMsg(); 
	virtual void UnRegMsg();

private: 
	void UpdateEditNum(const IArgs & arg);
	void UpdateRectRegionInfo( TTPMoonRectRegion tTPMoonRectRegion );

	//void SetRectAreaValCmd( CString str, u8 byIndex );

private:

	std::vector<string>  m_vecShatShot;                          //对应界面快照控件

	//四个矩形Button:A B C D
	const string m_strRectA;
	const string m_strRectB;
	const string m_strRectC;
	const string m_strRectD;

	//四个矩形的长宽
	const string m_strRectAWidth;
	const string m_strRectAHeight;
	const string m_strRectBWidth;
	const string m_strRectBHeight;
	const string m_strRectCWidth;
	const string m_strRectCHeight;
	const string m_strRectDWidth;
	const string m_strRectDHeight;
	const string m_strShowRectSwitchBtn;                         //矩形显示开关

	TTPMoonRectRegion m_tTpMoonRectRegionA;
	TTPMoonRectRegion m_tTpMoonRectRegionB;
	TTPMoonRectRegion m_tTpMoonRectRegionC;
	TTPMoonRectRegion m_tTpMoonRectRegionD;

	string m_strRectInfo[4];
	int         m_nTimes;         //信号源帧数不同时图像缩放倍数不一样

	Window* m_pWnd;

};

#define SETCONTRASTAREALOGIC   CSetContrastAreaLogic::GetSingletonPtr()

#endif // !defined(AFX_SETCONTRASTAREALOGIC_H__E6D544B7_DA04_4D05_BCB4_10015F3DDCBC__INCLUDED_)
