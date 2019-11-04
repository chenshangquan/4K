/*****************************************************************************
模块名      : ControlEx
文件名      : ControlEx.h
相关文件    : 
文件实现功能: 通用控件封装
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/5/1       1.0         刘德印      创建
******************************************************************************/
#ifndef CONTROLEX_H
#define CONTROLEX_H

namespace DuiLib {

/////////////////////////////////////////////////////////////////////////////////////
//


/*****************************************************************************
* 功能:			上下左右滚动的CContainerUI控件
* @return		空 
* @remarks		无
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/6/9       1.0         刘德印      创建
******************************************************************************/
class UILIB_API CommonScrollContainerUI : public CScrollContainerUI
{
public:
	enum { SCROLL_TIMERID = 10 };

	CommonScrollContainerUI();											//ScrollContainerUI画布

	void DoEvent(TEventUI& event);
	void SetPos(RECT rc);
	tString GetImage(){ return m_strImage;};
	void SetImage( const tString& strImage, double dblZoomRatio = 1.0, bool bFixedYX = false );   // double	dblZoomRatio 比例, bool bFixedYX = true则置宽高为图片高宽

	SIZE GetContainSize(){return m_szContain;};
	void SetContainSize(SIZE szContain){ m_szContain = szContain; };

	void UpdateUILayout( double dblZoomRatio = 1.0, double dbAngle = 0 );										//更新窗口布局  重新计算滚动视图显示

private:
	UINT m_uButtonState;
	POINT m_ptLastMouse;
	LONG m_dwDelayDeltaY;
	DWORD m_dwDelayNum;
	DWORD m_dwDelayLeft;

	tString m_strImage;

	SIZE m_szContain;

	TImageInfo* m_pImgData;									//存储ImageInfo减少重复GetImgInfo引起的效率即界面绘制问题

	tString m_strScrollXml;
};


/*****************************************************************************
* 功能:			CommonScrollContainerUI中的滚动画布
* @return		空 
* @remarks		无
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/7/5       1.0         刘德印      创建
******************************************************************************/
class UILIB_API CScollImageUI : public CLabelUI
{
public:
	CScollImageUI();

	LPCTSTR GetClass() const;
	LPVOID GetInterface(LPCTSTR pstrName);
	UINT GetControlFlags() const;

	bool Activate();
	void SetEnabled(bool bEnable = true);
	void DoEvent(TEventUI& event);

 	LPCTSTR GetNormalImage();
 	void SetNormalImage( LPCTSTR pStrImage, TImageInfo* pImgData = NULL );
	SIZE EstimateSize(SIZE szAvailable);
	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	void PaintStatusImage(HDC hDC);

	void SetScrollContainerUI(CommonScrollContainerUI* pScrollContainerUI);

private:
	//触摸消息处理分发   2013.07.24 by ldy
	virtual void OnGestureBeg( TEventUI& event );			//POINT ptFrom
	virtual void OnGestureEnd( TEventUI& event );			//POINT ptFrom
	virtual BOOL OnGestureZoom( TEventUI& event );			//POINT ptCenter, long lDelta
	virtual BOOL OnGesturePan( TEventUI& event );			//POINT ptFrom, POINT ptTo
	virtual BOOL OnGestureRotate( TEventUI& event );		//POINT ptCenter, double dblAngle
	virtual BOOL OnGestureTwoFingerTap( TEventUI& event );	//POINT ptCenter
	virtual BOOL OnGesturePressAndTap( TEventUI& event );	//POINT ptFirstFinger, long lDelta

protected:
	UINT m_uButtonState;
	CStdString m_strNormalImage;
	CommonScrollContainerUI* m_pScrollContainerUI; 

	TImageInfo* m_pImgData;									//存储ImageInfo减少重复GetImgInfo引起的效率即界面绘制问题

	TEventUI m_eventUI;
	double m_dbAngle;
};


} // namespace DuiLib

#endif CONTROLEX_H
