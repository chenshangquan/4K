#ifndef TRANSPARETNCOMBOBOX_HEAD_H
#define TRANSPARETNCOMBOBOX_HEAD_H

#include "uiexBaseData.h"


class Data_ComboMenu : public IData
{
public:
    Data_ComboMenu( CString &strMenu ) : IData( "ComboMenu" ), m_strMenuInfo( strMenu ){}
    IData* Clone()
    {
        Data_ComboMenu* pData = new Data_ComboMenu( m_strMenuInfo );
        pData->SetDataKey( GetDataKey() );
        return pData;
    }
    
    CString m_strMenuInfo;
};

class CComboBoxList :public CTransparentList
{
public:
	CComboBoxList( CString strName = "", CRect rcWnd = CRect(0,0,0,0), CWnd* pWnd = 0, CString strUI = "", UINT nID = 0, 
		DWORD dStyle = 0, DWORD dwExStyle = 0 );
	virtual ~CComboBoxList();

	virtual void Clicked( UINT nFlags, CPoint point );
	virtual void ListMouseMove(UINT nFlags, CPoint point);
	virtual void ListKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

	void SetComboWnd(CWnd* hComboWnd){ m_hComboWnd = hComboWnd;};
	CWnd* GetComboWnd(){ return m_hComboWnd;};
	void GoToListItem( s32 nOffset , IData * pSelData );
	void UpdateListItem( s32 nBorderIndex , s32 nOffset ,IItemList *pLastSelList );
	void UpArrowPress( s32 nItemHeight , s32 nItemShowIndex );
	void DownArrowPress( s32 nItemHeight , s32 nItemShowIndex );
	void onReturnKey();
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CComboBoxList)
	//}}AFX_MSG
	
	//DECLARE_MESSAGE_MAP()

private:
	CWnd* m_hComboWnd;
	static BOOL m_bIsRegAlgo;
	CString m_strLastMoveItem;    //记录最后一次鼠标停留的条目  防止闪烁
};

class CComboxDropBaseWnd : public CTransparentBaseWnd
{
public:
    CComboxDropBaseWnd( CRect rcWnd, CWnd* pWnd,DWORD dStyle,
		CString strUI,UINT nID, DWORD dwExStyle = 0,int nTrans = 255,BOOL bCanMove = FALSE, BOOL bStretchImage = TRUE );
    virtual ~CComboxDropBaseWnd();
	
	// Generated message map functions
protected:
    //{{AFX_MSG(CComboxDropBaseWnd)
    //}}AFX_MSG
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	DECLARE_MESSAGE_MAP()
	
private:

};


class CTransparentComboBox : public CTransparentBaseWnd  
{
	typedef IItem< IBaseItem, int > IItemList;
	// Construction
public:
	CTransparentComboBox( CString strName = "", CWnd* pWnd = 0, CRect rcWnd = CRect(0,0,0,0), 
		UINT nID = 0, DWORD dStyle = 0 );
	virtual ~CTransparentComboBox();
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CTransparentComboBox)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg LRESULT OnRedrawUI( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnDropListClick( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnSetFocus( WPARAM wParam, LPARAM lParam );
	//afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg LRESULT OnUpdateEditText( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnClickListIcon( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnMouseMoveShowIcon( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnComboEditChange( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnComboEditChar( WPARAM wParam, LPARAM lParam );
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()

public:
	void    InitComboControl();
	void    SetIpStyle(BOOL bIPStyle){ m_bIsIPStyle = bIPStyle;};
    void	SetImage( const CString& strImageFolder = "" );
	void	SetReadOnly( BOOL bReadOnly = TRUE );
	void	SetComboText(CString strComboText);
	CString GetComboText();								//普通风格combox获取数据
	DWORD   GetIpAddress( DWORD dwIp );					//IP风格combox获取数据   
	void    SetIpAddress( DWORD dwIp );					//IP风格combox设置数据   
	void	SetDropListHeight(int nListHeight){ m_nListHeight = nListHeight;};		//设置下拉列表高度   否则为默认高度
	void    SetEditEdgeHeight(int nEditEdge){ m_nEditEdge = nEditEdge;};			//不作为通用接口   编辑框边缘的大小以确保Edit&List无缝拼接
	void    SetItemHeight(int nListItemHeight){ m_nListItemHeight = nListItemHeight;};
	void	SetFont( unsigned int dwFontSize = 9, CString strFontFamily = ("微软雅黑"), BOOL bInvalidate = FALSE );
	void    SetImgHeight(int nListImgHeight){ m_nListImgHeight = nListImgHeight;};
	void    SetShowIcon(BOOL bIsShowListIcon){ m_bIsShowListIcon = bIsShowListIcon;};
	void    SetEnableWindow( BOOL bEnable );										//控制编辑框的enable状态
	void    SetListBkgColor( Color colorBkg );
	void    SetItemSelColor( Color colorItemSel ){ m_itemSelColor = colorItemSel;};
	void	SetEditFrontLen(int nEditFrontLen);		//设置编辑框第一个输入字符距离左侧偏移 
	void	SetEditBackLen(int nEditBackLen);		//设置编辑框图标距离右侧偏移 

	void	SetTextColor( Color colorNormal, Color colorFocus, BOOL bInvalidate = FALSE );
    void	SetDisableColor( Color colorDisable, BOOL bInvalidate = FALSE );

	BOOL	AddString(CString strString);
	BOOL	DeleteString(CString strString);
	void	UpdateComboList( std::vector<CString>* pListData, s32 nCurMoveItem = -1 );
	s32		JumpToSelItem(const CString& strEditText);			//下拉自动跳转到高亮选中行    返回匹配行号

	void	SetListOver(BOOL bNeedOver);

	void	SetTipStr( CString strTip );
	void	SetTipFont( unsigned int dwFontSize = 12, CString strFontFamily = ("微软雅黑"), BOOL bInvalidate = FALSE );
	void	SetTipColor( Color colorTip, BOOL bInvalidate = FALSE );

	CTransparentEdit* GetEditPoint();
	void IsIpInvalid( BOOL &bIsEmpty/*,BOOL &bIsInvalid */);
private:
	Image   *m_pImgBkg;

	CTransparentEdit* m_pTransEdit;
	CComboxDropBaseWnd* m_pDropWnd;
	CComboBoxList* m_pDropList;

	std::vector<CString> m_vecListData;

	CString m_strListItemFolder;   //列表对应目录
 	CString m_strImageItemFolder;

	CString m_strComboText;    

	BOOL m_bIsIPStyle;           //是否是IP风格
	CRect m_rcWnd;
	int m_nListHeight;         //下拉列表高度
	int m_nListItemHeight;     //设置列表行高度
	int m_nListImgHeight;      //设置列表点击图标高度

	int m_nEditEdge;          //编辑框边缘的大小以确保Edit&List无缝拼接     左上边缘保持同高

	BOOL m_bIsShowListIcon;
	Color m_colorBkg;


	int m_nFontSize;
	int m_nSliderWidth;
	int m_nEditBackLen;

	BOOL m_bSetBkColor;
	Color m_itemNormalColor;
	Color m_itemSelColor;

	Color m_colorNormal;
	Color m_colorFocus;
    Color m_colorDisable;
};




#endif