#ifndef LIST_HEAD_H
#define LIST_HEAD_H

#include "iList.h"
#include "transparenBaseWnd.h" 
#include "TransparentListSlider.h"
#include "letterIndex.h"

class CTransparentList : public CTransparentBaseWnd, public IList
{
public:
	const static CString strTopLeft;
	const static CString strTopCenter;
	const static CString strTopRight;
	const static CString strCenterLeft;
	const static CString strCenterRight;
	const static CString strBottomLeft;
	const static CString strBottomCenter;
	const static CString strBottomRight;
    const static CString strSliderTop;
    const static CString strSliderMiddle;
    const static CString strSliderBottom;

    /**
    * 功能: 列表构造函数
    * @param [in]  strName  列表名称
    * @param [in]  rcWnd  窗口位置大小
    * @param [in]  pWnd  窗口的父窗口
    * @param [in]  nID 窗口的ID
    * @param [in]  dwStyle  窗口style   
    * @param [in]  dwExStyle  扩展style
    * @remarks
    */
	CTransparentList( CString strName = "", CRect rcWnd = CRect(0,0,0,0), CWnd* pWnd = 0, CString strUI = "", UINT nID = 0, 
		DWORD dStyle = 0, DWORD dwExStyle = 0 );
	
	virtual ~CTransparentList();
	
    /**
    * 功能:	响应列表点击事件
	* @param [in]  同OnLButtonUp参数
	* @return  无
	* @remarks 该函数可在子类中重载，用户自行响应点击事件
               默认点击事件响应需在CListFuncManage类中注册
	*/
	virtual void Clicked( UINT nFlags, CPoint point );

    /**
    * 功能:	设置列表是否允许拖拽
	* @param [in]  nOffset 偏移量
	* @return  无
	* @remarks 默认TRUE
	*/
	void SetDragEnable( BOOL bDrag );
	BOOL GetDragEnable() { return m_bDragEnable; }
	
    /**
    * 功能:	设置列表Y轴偏移量
	* @param [in]  nOffset 偏移量
	* @return  无
	* @remarks
	*/
	void SetYOffset( int nOffset );
	int  GetYOffset();

    /**
    * 功能:	设置列表到底部位置
	* @return  无
	* @remarks
	*/
	void SetBottomOffset();

    /**
    * 功能:	设置条目被点击后是否不选中
	* @param [in]  bSel 是否点击不选中
	* @return  无
	* @remarks 默认FALSE，条目点击后高亮
	*/
	void SetClickNoSel( BOOL bSel );
	BOOL IsClickNoSel() { return m_bClickNoSel; }

    /**
    * 功能:	设置列表被点击时是否获得焦点
	* @param [in]  bFocus 是否获得焦点
	* @return  无
	* @remarks 默认TRUE
	*/
	void SetClickFocus( BOOL bFocus );
	BOOL IsClickFocus() { return m_bClickFocus; }

    /**
    * 功能:	设置列表是否允许多个选中
	* @param [in]  bMulti 是否允许多个选中
	* @return  无
	* @remarks 默认不能高亮多个条目
	*/
	void SetMultiSel( BOOL bMulti );
	BOOL IsMultiSel() { return m_bMultiSel; }

    /**
    * 功能:	设置当前选中条目
	* @param [in]  dwDataKey 条目数据的Key
	* @return  无
	* @remarks  条目需要有IDate
	*/
	void SetSelItem( unsigned long dwDataKey, BOOL bResetOffset = TRUE );	
	IBaseItem* GetSelItem();

    /**
    * 功能:	重置选中条目
	* @param [in]  bResetOffset 是否同时重置位置
	* @return  无
	* @remarks  用于列表数据更新之后
	*/
    void ResetSelItem( BOOL bResetOffset = FALSE );

    /**
    * 功能:	设置滑动条是否一直显示
	* @param [in]  bAlwaysShow 是否一直显示
	* @return  无
	* @remarks 默认FALSE，只有列表移动时才显示
	*/
    void SetSliderAlwaysShow( BOOL bAlwaysShow ){ m_bAlwaysShowSlider = bAlwaysShow; }

    /**
    * 功能:	设置滑动条位置
	* @param [in]  rectSlider 滑动条位置
	* @return  无
	* @remarks 设置为列表父窗口上的相对位置
	*/
    void SetSliderRect( CRect rectSlider );
    
    void SetBkgColor( Color colorBkg, BOOL bInvalidate = FALSE );

    /**
    * 功能:	设置列表背景图片
	* @param [in]  strImageFolder 图片目录路径
	* @return  无
	* @remarks
	*/ 
	void SetImage( CString strImageFolder  , BOOL bInvalidate = FALSE ,EmImgCompType emImgType = emImgCompMasic);

	void SetImage( UINT nImgTopLeft, UINT nImgTopCenter, UINT nImgTopRight, UINT nImgCenterLeft, 
		UINT nImgCenterRight, UINT nImgBottomLeft, UINT nImgBottomCenter, UINT nImgBottomRight, UINT nImageBK, const CString& strImgType = "PNG" );

	Image* MosaicListImage();

    //设置滚动条图片
    void SetSliderImage( UINT nImgNormalUp, UINT nImgNormalCenter, UINT nImgNormalDown, UINT nImgHilightUp, UINT nImgHilightCenter, 
        UINT nImgHilightDown, UINT nImgBkUp, UINT nImgBkCenter, UINT nImgBkDown,  const CString& strImgType = "PNG" );

    void SetSliderImage( CString strImageFolder );

	BOOL IsNeedSlider(){ return m_bNeedSlider;};

	void SetRedrawBk(BOOL bRedrawBk){ m_bRedrawBk = bRedrawBk;};                 //列表大小改变是否重绘背景

    /**
    * 功能:	清空列表数据
	* @return  无
	* @remarks  用于列表数据更新之前
	*/
	void Clear();

	//设置列表是否需要Over状态(作为标签页需要,一般列表不需要)
	void SetListOver( BOOL bNeedOver ){ m_bNeedOver = bNeedOver; }

protected:
    void Draw( IArgs* pArgs );
    
	void DrawUI( Graphics* pGraphics, CWnd* pParent );

	CRect GetFrameInScreen( IItemList* pList );

	CRect GetListRect();
	BOOL IsReadyForDrag();
	void SetSelItemStatus( EmItemStatus emStatus );
	int  GetOffsetHeight( int nIndex );
	void ClearAllSel();
	
	BOOL ListMove();
	void ListAutoMove();

    void CheckYOffset();

    CPoint TransChildPoint( IItemList* pList, CPoint point );

    static void InitList();  //列表初始化，只做一次    

	virtual void ListMouseMove(UINT nFlags, CPoint point);
	virtual void ListKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual	void onReturnKey();
protected:
	CRect   m_rctDlg;                      //列表框Rect
	CRect   m_rctList;	                   //整个列表数据Rect	
	int     m_nTotalYOffset;               //当前总的Y轴偏移量
	int     m_nTotalXOffset;
	CPoint  m_ptMouseLast;
	CPoint  m_ptMouseNow;
	CPoint  m_ptMouseDown;
	int     m_nMoveSpeed;
	BOOL    m_bLBtnDown;
	IItemList*   m_pSelItem;               //当前选中
	IItemList*   m_pMouseHoverItem;       //当前光标经过的条目 2013.5.3  jyy
	IItemList*   m_pLastItem;
	unsigned long m_dwSelDataKey;          //选中Item的数据索引

	BOOL    m_bDragEnable;                 //是否允许拖拽
	BOOL    m_bClickNoSel;                 //点击后是否将条目设为不选中
	BOOL    m_bClickFocus;                 //点击后是否设置焦点
	BOOL    m_bMultiSel;                   //是否允许多个选中
    BOOL    m_bAlwaysShowSlider;           //是否一直显示滑动条
    BOOL    m_bNeedSlider;                 //是否需要显示滑动条
	BOOL    m_bNeedOver;				   //是否需要Over状态显示
	BOOL    m_bMouseTrack;				   //是否开启鼠标追踪

    CTransparentListSlider* m_pSlider;     //列表滚动条

	CLetterIndex* m_pLetterIndex;			//字母索引

	//背景图片
	Image   *m_pImgTopLeft;
    Image   *m_pImgTopCenter;
    Image   *m_pImgTopRight;	
    Image   *m_pImgCenterLeft;
	Image   *m_pImgCenterRight;
    Image   *m_pImgBottomLeft;
    Image   *m_pImgBottomCenter;
	Image   *m_pImgBottomRight;

	Color   m_cBkgColor;                 //背景颜色

    static  BOOL m_bInitList;            //列表是否初始化
	
	BOOL	m_bRedrawBk;                 //列表大小改变是否重绘背景
protected:
	//{{AFX_MSG(CTouchList)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);	
	afx_msg void OnSize(UINT nType, int cx, int cy);
	LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnRedrawUI( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT	OnMouseWheels( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnUpdateProgress( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnLetterClick( WPARAM wParam, LPARAM lParam );
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	afx_msg LRESULT OnMouseLeave( WPARAM wParam, LPARAM lParam );//切换窗口后根据WM_MOUSELEAVE处理控件为normal状态  
	afx_msg LRESULT OnMouseHover( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnBindList( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnEnableWindow( WPARAM wParam, LPARAM lParam );
	DECLARE_MESSAGE_MAP()
};
#endif