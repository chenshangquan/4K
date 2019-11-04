/*****************************************************************************
模块名      : 列表滑动条
文件名      : TransparentListSlider.h
相关文件    : TransparentListSlider.cpp transparenBaseWnd.h
文件实现功能: 包含于列表，用于显示列表当前位置
作者        : 肖楚然
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
  日  期      版本        修改人      修改内容
2012/11/28    1.0         肖楚然        创建
******************************************************************************/
#if !defined(AFX_TRANSPARENTLISTSLIDER_H__16B233EA_D0F5_459B_9D6C_A50C0DC83B12__INCLUDED_)
#define AFX_TRANSPARENTLISTSLIDER_H__16B233EA_D0F5_459B_9D6C_A50C0DC83B12__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "transparenBaseWnd.h"

class CTransparentListSlider : public CTransparentBaseWnd  
{
private:
	enum EmMoveBtnStatus // 按钮状态
    {
        emStatusMoveBtnNormal = 0,
		emStatusMoveBtnDown
	};
public:
    CTransparentListSlider( CString strName = "", CRect rcWnd = CRect(0,0,0,0), CWnd* pParentWnd = 0, UINT nID = 0, 
		DWORD dStyle = 0, DWORD dwExStyle = 0 );
	virtual ~CTransparentListSlider();

    /**
    * 功能:	设置列表数据总高度
	* @param [in]  nHeight 列表数据高度
	* @return  无
	* @remarks 列表所有数据总高度，并非列表对话框高度
	*/
    void SetListTotalHeight( int nHeight ){ m_nListHeight = nHeight; }

    /**
    * 功能:	设置列表Y轴偏移量
	* @param [in]  nOffset 偏移量
	* @return  无
	* @remarks 
	*/
    void SetListYOffset( int nOffset ){ m_nListYOffset = nOffset; }

    /**
    * 功能:	设置对应列表指针
	* @param [in]  pWnd 列表指针
	* @return  无
	* @remarks 
	*/
    void SetListWnd( CWnd* pWnd ){ m_pListWnd = pWnd; }

    /**
    * 功能:	设置滑动条是否一直显示
	* @param [in]  bAlwaysShow 是否一直显示
	* @return  无
	* @remarks FALSE时，只有列表移动时才显示
	*/
    void SetAlwaysShow( BOOL bAlwaysShow ){ m_bAlwaysShow = bAlwaysShow; }

    /**
    * 功能:	设置滑动条贴图
	* @param [in]  贴图路径或贴图资源ID
	* @return  无
	* @remarks 
	*/
    void SetImage( CString strImageFolder );

    void SetImage( CString strImageTop, CString strImageMiddle, CString strImageBottom,
                   CString strBkTop = "", CString strBkMiddle = "", CString strBkBottom = "");
    
    void SetImage( UINT nImgNormalUp, UINT nImgNormalCenter, UINT nImgNormalDown, 
        UINT nImgHilightUp, UINT nImgHilightCenter, UINT nImgHilightDown, 
        UINT nImgBkUp, UINT nImgBkCenter, UINT nImgBkDown, const CString& strImgType);
protected:
    //{{AFX_MSG(CTransparentListSlider)
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg LRESULT OnRedrawUI( WPARAM wParam, LPARAM lParam );
    afx_msg void OnSize(UINT nType, int cx, int cy);
    //}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    /**
    * 功能:	计算滚动条位置和长度
	* @param [in]  nAllHeight 列表框高度，即滑条最大长度
    * @param [in]  nSliderMiniHeight 滑条最小长度
    * @param [out] nSliderPos 滑条起始位置
    * @param [out] nSliderHeight 滑条长度
	* @return  无
	* @remarks 
	*/
    void CalSliderPos( int nAllHeight, int nSliderMinHeight, int& nSliderPos, int& nSliderHeight );

	void CalSliderPos( int nAllHeight, int nListDlgHeight, int nSliderMinHeight, int& nSliderPos, int& nSliderHeight );

	BOOL MoveButtonUpdate(CPoint point); //更新上下移动 按钮   绘制点击非

private:
    int      m_nListHeight;  //列表数据总高度
    int      m_nListYOffset; //列表Y轴偏移量

    CRect    m_rctSlider;    //滑动条的rect

    BOOL     m_bLButtonDown;
    CPoint   m_ptMouseDown;  //点击的坐标

    BOOL     m_bAlwaysShow;  //是否一直显示

    CWnd*    m_pListWnd;     //对应列表指针

    //滑动条贴图
    Image   *m_pImgSliderBkUp;
    Image   *m_pImgSliderBkCenter;
	Image   *m_pImgSliderBkDown;
	
    Image   *m_pImgSliderNormalUp;
    Image   *m_pImgSliderNormalCenter;
	Image   *m_pImgSliderNormalDown;
    
    Image   *m_pImgSliderHilightUp;
    Image   *m_pImgSliderHilightCenter;
	Image   *m_pImgSliderHilightDown;

	//上 下移动贴图
    Image   *m_pImgUpMove;
	Image   *m_pImgUpMoveDown;
	
    Image   *m_pImgDownMove;
    Image   *m_pImgDownMoveDown;

	EmMoveBtnStatus m_emUpMoveStatus;
	EmMoveBtnStatus m_emDownMoveStatus;

	CRect	m_cUpMoveIconRect;
	CRect	m_cDownMoveIconRect;

    int      m_nBkgImgOffset; //滑条背景与滑条间距

    const static CString strNormalTop;
    const static CString strNormalMiddle;
    const static CString strNormalBottom;
    const static CString strHilightTop;
    const static CString strHilightMiddle;
    const static CString strHilightBottom;
    const static CString strBkTop;
    const static CString strBkMiddle;
    const static CString strBkBottom;
	const static CString strBkUpMove;
	const static CString strBkDownMove;
	const static CString strBkUpMoveDown;
	const static CString strBkDownMoveDown;

};

#endif // !defined(AFX_TRANSPARENTLISTSLIDER_H__16B233EA_D0F5_459B_9D6C_A50C0DC83B12__INCLUDED_)
