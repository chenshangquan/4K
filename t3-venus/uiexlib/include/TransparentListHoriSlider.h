/*****************************************************************************
模块名      : 列表横向滑动条
文件名      : TransparentListHoriSlider.cpp
相关文件    : TransparentListHoriSlider.h
文件实现功能: 包含于列表，用于显示列表当前横向位置
作者        : 肖楚然
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
  日  期      版本        修改人      修改内容
2012/11/29    1.0         肖楚然        创建
******************************************************************************/
#if !defined(AFX_TRANSPARENTLISTHORISLIDER_H__13CB0A08_FEE9_4C75_8652_D39C2899C43D__INCLUDED_)
#define AFX_TRANSPARENTLISTHORISLIDER_H__13CB0A08_FEE9_4C75_8652_D39C2899C43D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "transparenBaseWnd.h"

class CTransparentListHoriSlider : public CTransparentBaseWnd
{
private:
	enum EmMoveBtnStatus // 按钮状态
    {
        emStatusMoveBtnNormal = 0,
		emStatusMoveBtnDown
	};

public:
    CTransparentListHoriSlider( CString strName = "", CRect rcWnd = CRect(0,0,0,0), CWnd* pParentWnd = 0, UINT nID = 0, 
        DWORD dStyle = 0, DWORD dwExStyle = 0 );
	virtual ~CTransparentListHoriSlider();
    
    /**
    * 功能:	设置列表数据总宽度
	* @param [in]  nHeight 列表数据宽度
	* @return  无
	* @remarks 列表所有数据总宽度，并非列表对话框宽度
	*/
    void SetListTotalWidth( int nHeight ){ m_nListWidth = nHeight; }
    
    /**
    * 功能:	设置列表X轴偏移量
	* @param [in]  nOffset 偏移量
	* @return  无
	* @remarks 
	*/
    void SetListXOffset( int nOffset ){ m_nListXOffset = nOffset; }

    /**
    * 功能:	设置对应列表指针
	* @param [in]  pWnd 列表指针
	* @return  无
	* @remarks 
	*/
    void SetListWnd( CWnd* pWnd ){ m_pListWnd = pWnd; }
    
    /**
    * 功能:	设置滑动条贴图
	* @param [in]  贴图路径或贴图资源ID
	* @return  无
	* @remarks 
	*/
    void SetImage( CString strImageFolder );
    
    void SetImage( UINT nImgNormalLeft, UINT nImgNormalCenter, UINT nImgNormalRight, 
        UINT nImgHilightLeft, UINT nImgHilightCenter, UINT nImgHilightRight, 
        UINT nImgBkLeft, UINT nImgBkCenter, UINT nImgBkRight, const CString& strImgType);  
    
protected:
    //{{AFX_MSG(CTransparentListHoriSlider)
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg LRESULT OnRedrawUI( WPARAM wParam, LPARAM lParam );
    afx_msg void OnSize(UINT nType, int cx, int cy);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
        
    /**
    * 功能:	计算滚动条位置和宽度
	* @param [in]  nAllHeight 列表框高度，即滑条最大长度
    * @param [in]  nSliderMiniHeight 滑条最小长度
    * @param [out] nSliderPos 滑条起始位置
    * @param [out] nSliderHeight 滑条长度
	* @return  无
	* @remarks 
	*/
    void CalSliderPos( int nBkgWidth, int nSliderMinWidth, int& nSliderPos, int& nSliderWidth );

	void CalSliderPos( int nBkgWidth, int nListDlgWidth, int nSliderMinWidth, int& nSliderPos, int& nSliderWidth );   

	BOOL MoveButtonUpdate(CPoint point); //更新左右移动 按钮   绘制点击非滚动条外的 左移 右移的显示

private:
    int      m_nListWidth;   //列表数据总宽度
    int      m_nListXOffset; //列表X轴偏移量
    
    CRect    m_rctSlider;    //滑动条的rect
    
    BOOL     m_bLButtonDown;
    CPoint   m_ptMouseDown;  //点击的坐标
    
    CWnd*    m_pListWnd;     //对应列表指针
    
    //滑动条贴图
    Image   *m_pImgSliderBkLeft;
    Image   *m_pImgSliderBkCenter;
    Image   *m_pImgSliderBkRight;

	//左 右移动贴图
    Image   *m_pImgLeftMove;
	Image   *m_pImgLeftMoveDown;

    Image   *m_pImgRightMove;
    Image   *m_pImgRightMoveDown;

	CRect	m_cLeftMoveIconRect;
	CRect	m_cRightMoveIconRect;

	EmMoveBtnStatus m_emLeftMoveStatus;
	EmMoveBtnStatus m_emRightMoveStatus;

    Image   *m_pImgSliderNormalLeft;
    Image   *m_pImgSliderNormalCenter;
    Image   *m_pImgSliderNormalRight;
    
    Image   *m_pImgSliderHilightLeft;
    Image   *m_pImgSliderHilightCenter;
	Image   *m_pImgSliderHilightRight;

    int      m_nBkgImgOffset; //滑条背景与滑条间距

    const static CString strNormalLeft;
    const static CString strNormalMiddle;
    const static CString strNormalRight;
    const static CString strHilightLeft;
    const static CString strHilightMiddle;
    const static CString strHilightRight;
    const static CString strBkLeft;
    const static CString strBkMiddle;
    const static CString strBkRight;
	const static CString strBkLeftMove;
	const static CString strBkRightMove;
	const static CString strBkLeftMoveDown;
	const static CString strBkRightMoveDown;
};

#endif // !defined(AFX_TRANSPARENTLISTHORISLIDER_H__13CB0A08_FEE9_4C75_8652_D39C2899C43D__INCLUDED_)
