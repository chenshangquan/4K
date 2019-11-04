/*****************************************************************************
模块名      : 通用视图列表
文件名      : TransparentViewList.h
相关文件    : iList.h transparenBaseWnd.h TransparentListSlider.h
文件实现功能: 通用列表相关功能，列表可以横向及纵向滑动，包含横竖两个滑动条
作者        : 肖楚然
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
  日  期      版本        修改人      修改内容
2012/11/29    1.0         肖楚然        创建
******************************************************************************/
#if !defined(AFX_TRANSPARENTVIEWLIST_H__6C136C36_FA5A_4C4C_841A_0F4F2827D2FE__INCLUDED_)
#define AFX_TRANSPARENTVIEWLIST_H__6C136C36_FA5A_4C4C_841A_0F4F2827D2FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "transparenBaseWnd.h"
#include "iList.h"
#include "TransparentListSlider.h"
#include "TransparentListHoriSlider.h"

class CTransparentViewList : public CTransparentBaseWnd, public IList 
{
public:
    /**
    * 功能: 列表构造函数
    * @param [in]  rcWnd  窗口位置大小
    * @param [in]  pWnd  窗口的父窗口
    * @param [in]  nID 窗口的ID
    * @param [in]  dwStyle  窗口style    
    * @param [in]  dwExStyle  扩展style
    * @remarks
    */
    CTransparentViewList( CString strName = "", CRect rcWnd = CRect(0,0,0,0), CWnd* pWnd = 0, UINT nID = 0, 
        DWORD dStyle = 0, DWORD dwExStyle = 0 );
    
    virtual ~CTransparentViewList();

    /**
    * 功能:	响应列表点击事件
	* @param [in]  同OnLButtonUp参数
	* @return  无
	* @remarks 该函数可在子类中重载，用户自行响应点击事件
               默认点击事件响应需在CListFuncManage类中注册
	*/
    virtual void Clicked( UINT nFlags, CPoint point );

    void SetDragEnable( BOOL bDrag );
    BOOL GetDragEnable() { return m_bDragEnable; }
    
    /**
    * 功能:	设置列表偏移量
	* @param [in]  nOffset/point 偏移位置
	* @return  无
	* @remarks 
	*/
    void SetXOffset( int nOffset );
    void SetYOffset( int nOffset );
    int  GetYOffset();
    void SetListOffset( CPoint point );
    
    //点击后是否选中
    void SetClickNoSel( BOOL bSel );
    BOOL IsClickNoSel() { return m_bClickNoSel; }

    void SetMultiSel( BOOL bMulti );
    BOOL IsMultiSel() { return m_bMultiSel; }
    
    //重置选中项
    void ResetSelItem( BOOL bResetOffset = FALSE );
    /**
    * 功能:	设置当前选中条目
	* @param [in]  dwDataKey 条目数据的Key
	* @return  无
	* @remarks  条目需要有IDate
	*/
    void SetSelItem( unsigned long dwDataKey ); 
    IBaseItem* GetSelItem();
 
    //设置列表背景图片
    void SetImage( CString strImageFolder );
    
    //void SetImage( UINT nImgTopLeft, UINT nImgTopCenter, UINT nImgTopRight, UINT nImgCenterLeft, 
    //    UINT nImgCenterRight, UINT nImgBottomLeft, UINT nImgBottomCenter, UINT nImgBottomRight, UINT nImageBK, const CString& strImgType = "PNG" );

    //设置滚动条图片
    void SetVertSliderImage( UINT nImgNormalUp, UINT nImgNormalCenter, UINT nImgNormalDown, UINT nImgHilightUp, UINT nImgHilightCenter, 
        UINT nImgHilightDown, UINT nImgBkUp, UINT nImgBkCenter, UINT nImgBkDown, const CString& strImgType = "PNG" );
    void SetHoriSliderImage( UINT nImgNormalLeft, UINT nImgNormalCenter, UINT nImgNormalRight, UINT nImgHilightLeft, UINT nImgHilightCenter, 
        UINT nImgHilightRight, UINT nImgBkLeft, UINT nImgBkCenter, UINT nImgBkRight, const CString& strImgType = "PNG" );
    
    //Image* MosaicListImage();
    
    void SetBkgColor( Color colorBkg, BOOL bInvalidate = FALSE );

    /**
    * 功能:	设置竖滑动条位置
	* @param [in]  ptOffset 偏移位置
	* @return  无
	* @remarks 滑条相对于列表右上角的偏移位置
	*/
    void SetVertSliderOffsetPos( CPoint ptOffset );
     /**
    * 功能:	设置横滑动条位置
	* @param [in]  ptOffset 偏移位置
	* @return  无
	* @remarks 滑条相对于列表左下角的偏移位置
	*/
    void SetHoriSliderOffsetPos( CPoint ptOffset );
    
	void Clear();

	//设置列表是否需要Over状态
	void SetListOver( BOOL bNeedOver ){ m_bNeedOver = bNeedOver; }

    //设置多个选中项
    void SetMultiSelSet( set<unsigned long> setMultiSel );
    void ClearAllSel();

protected:
    void Draw( IArgs* pArgs );
    void DrawUI( Graphics* pGraphics, CWnd* pParent );

    CRect GetFrameInScreen( IItemList* pList );
    
    CRect GetListRect();
    BOOL IsReadyForDrag();
    void SetSelItemStatus( EmItemStatus emStatus );
    //int  GetOffsetHeight( int nIndex );
    //void ClearAllSel();
    
    void ListMove();
    void ListAutoMove();

    void CheckXOffset();
    void CheckYOffset();
    virtual void ListMouseMove(UINT nFlags, CPoint point);


protected:
    //{{AFX_MSG(CTransparentViewList)
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnTimer(UINT nIDEvent);    
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg LRESULT OnRedrawUI( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT	OnUpdateProgress( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT	OnDragOver( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnDragLeave( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT	OnDragEnd( WPARAM wParam, LPARAM lParam );
    LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
    //}}AFX_MSG
	afx_msg LRESULT OnMouseLeave( WPARAM wParam, LPARAM lParam );  
	afx_msg LRESULT OnMouseHover( WPARAM wParam, LPARAM lParam );
	DECLARE_MESSAGE_MAP()

protected:
    CRect   m_rctDlg;                      //列表框Rect
    CRect   m_rctList;	                   //整个列表数据Rect	
    int     m_nTotalYOffset;               //当前总的Y轴偏移量
    int     m_nTotalXOffset;               //当前总的X轴偏移量
    CPoint  m_ptMouseLast;                 //鼠标之前位置
    CPoint  m_ptMouseNow;                  //鼠标当前位置
    CPoint  m_ptMouseDown;                 //鼠标点击下的位置
    int     m_nMoveSpeed;                 
    BOOL    m_bLBtnDown;
	IItemList*   m_pMouseHoverItem;		   //当前光标经过的条目 2013.5.6  jyy
    IItemList*   m_pSelItem;               //当前选中
    IItemList*   m_pLastItem;
    unsigned long m_dwSelDataKey;          //选中Item的数据索引

    IItemList*   m_pDragOverItem;          //拖拽经过的条目
    
    BOOL    m_bDragEnable;                 //是否允许拖拽
    BOOL    m_bClickNoSel;                 //点击后是否将条目设为不选中
    BOOL    m_bMultiSel;                   //是否多个选中
	BOOL    m_bNeedOver;				   //是否需要Over状态显示
	BOOL    m_bMouseTrack;				   //是否开启鼠标追踪

    CTransparentListSlider*     m_pVertSlider; //纵向滚动条
    CTransparentListHoriSlider* m_pHoriSlider; //横向滚动条
    
    const static CString strBkgImg;
    const static CString strVertSliderImg;
    const static CString strHoriSliderImg;
    /*//背景图片
    Image   *m_pImgTopLeft;
    Image   *m_pImgTopCenter;
    Image   *m_pImgTopRight;	
    Image   *m_pImgCenterLeft;
    Image   *m_pImgCenterRight;
    Image   *m_pImgBottomLeft;
    Image   *m_pImgBottomCenter;
    Image   *m_pImgBottomRight;
    */
    Color   m_cBkgColor;                 //背景颜色
    
};

#endif // !defined(AFX_TRANSPARENTVIEWLIST_H__6C136C36_FA5A_4C4C_841A_0F4F2827D2FE__INCLUDED_)
