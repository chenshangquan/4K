/*****************************************************************************
模块名      : CommonListUI
文件名      : CommonListUI.h
相关文件    : 
文件实现功能: 通用列表控件
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
说明		: 常见方案包含文件列表，支持进入目录，上下级列表
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/5/1      1.0         刘德印      创建
******************************************************************************/
#ifndef COMMONFILELIST_H
#define COMMONFILELIST_H

class UILIB_API CCommonListUI : public CListUI
{
public:
	enum {SCROLL_TIMERID = 10};

	CCommonListUI();
	~CCommonListUI();

public:
	LPCTSTR GetClass() const;
	LPVOID GetInterface(LPCTSTR pstrName);
	/*****************************************************************************
	* 功能:			添加结点数据
	* @param		[in]	const IData& item    结点数据 
	* @param		[in]	Node* parent         父窗口指针 
	* @return		空 
	* @remarks		支持多类型数据扩展，需添加相应TransData
	-----------------------------------------------------------------------------
	修改记录:
	日  期         版本        修改人      修改内容
	2013/5/1       1.0         刘德印      创建
    ******************************************************************************/
	Node* AddNode(const IData& item, Node* pParent = NULL);

	bool CanExpand(Node* pNode) const;

	void SetMainFrameWnd(RECT rcRect);


		 /*****************************************************************************
	* 功能:			设置/获取目标拖拽窗口：实现多列表结点互加，目前支持双列表，如果实现多列表需要扩展注册窗口
	* @param		无
	* @return		空 
	* @remarks		无
	-----------------------------------------------------------------------------
	修改记录:
	日  期         版本        修改人      修改内容
	2013/5/3       1.0         刘德印      创建
    ******************************************************************************/
	CCommonListUI* GetDragListCtrlWnd(){return m_pListDragWnd;};
	void SetDragListCtrlWnd(CCommonListUI* pListDragWnd){ m_pListDragWnd = pListDragWnd;};

	/*****************************************************************************
	* 功能:			更新列表数据
	* @param		[in]	std::vector<IData*>& vecData    列表数据集 
	* @return		空 
	* @remarks		无
	-----------------------------------------------------------------------------
	修改记录:
	日  期         版本        修改人      修改内容
	2013/7/22      1.0         刘德印      创建
    ******************************************************************************/
	void UpdateList(std::vector<IData*>& vecData);	

	void UpdateList(CStdDataArray<IData*>& vecData);

	void SetManagerUI(CPaintManagerUI* pManageUI){ m_pManageUI = pManageUI;};

	bool SetCheckStateMap(int nKey, bool bSelState);
	void GetCheckStateMap(CStdDataList<bool>** pListCheckState){ *pListCheckState = m_pListCheckState; };

	tString GetProgressName(){return m_strProgressName;};

	void SetListData(CStdDataArray<IData*>& aryListData);
	void GetListData(CStdDataArray<IData*>** paryListData){ *paryListData = m_paryListData; };

private:
	//bool Add(CControlUI* pControl); 
	//bool AddAt(CControlUI* pControl, int iIndex);
	bool AddAtEnd( CControlUI* pItemList, Node* pParent );
	bool AddAt( CControlUI* pControl, Node* pParent );
	bool RemoveAt(int iIndex);
	//bool Remove(CControlUI* pControl);
	//bool RemoveAt(int iIndex);
	void RemoveAll();
	
	void DoEvent(TEventUI& event);
	Node* GetRoot();

	void ResetNodeRoot();


	 /*****************************************************************************
	* 功能:			删除结点数据
	* @param		[in]	const IData& item    结点数据 
	* @return		空 
	* @remarks		无
	-----------------------------------------------------------------------------
	修改记录:
	日  期         版本        修改人      修改内容
	2013/5/1       1.0         刘德印      创建
    ******************************************************************************/
	void RemoveNode(Node* pNode);

	 /*****************************************************************************
	* 功能:			选中指定行
	* @param		[in]	int iIndex   待选中行号
	* @return		空 
	* @remarks		无
	-----------------------------------------------------------------------------
	修改记录:
	日  期         版本        修改人      修改内容
	2013/5/1       1.0         刘德印      创建
    ******************************************************************************/
	bool SelectItem(int iIndex);

	 /*****************************************************************************
	* 功能:			设置列表属性
	* @param		[in]	LPCTSTR pstrName	属性name
	* @param		[in]	LPCTSTR pstrValue	属性value
	* @return		空 
	* @remarks		无
	-----------------------------------------------------------------------------
	修改记录:
	日  期         版本        修改人      修改内容
	2013/5/1       1.0         刘德印      创建
    ******************************************************************************/
	void SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue );

	 /*****************************************************************************
	* 功能:			设置/获取当前选中结点
	* @param		[in]	Node* pNodeSelItem   选中Node
	* @return		空 
	* @remarks		无
	-----------------------------------------------------------------------------
	修改记录:
	日  期         版本        修改人      修改内容
	2013/5/1       1.0         刘德印      创建
    ******************************************************************************/
	void SetSelectItemNode(Node* pNodeSelItem){ m_pNodeSelItem = pNodeSelItem;};
	Node* GetSelectItemNode(){ return m_pNodeSelItem;};


	 /*****************************************************************************
	* 功能:			方式一：创建列表数据(XML方式)
	* @param		[in]	const Data_FileList &data   文件列表结点数据 
	* @param		[in]	Node* parent				父窗口指针 
	* @return		空 
	* @remarks		针对不同列表创建不同的数据规则
	-----------------------------------------------------------------------------
	修改记录:
	日  期         版本        修改人      修改内容
	2013/5/3       1.0         刘德印      创建
    ******************************************************************************/
	Node* DrawItemEx( const Data_FileList* pData, Node* pParent );
	Node* DrawItemEx( const Data_ConfList* pData, Node* pParent );
	Node* DrawItemEx( const Data_AddrList* pData, Node* pParent );     //by xhx

	CListContainerElementUI* CreateElement();
	void SetContainerVisible( CControlUI* pItemList, const tString& strWndName, bool bVisible = false );
	CButtonUI* SetButtonNode( CControlUI* pItemList, const tString& strWndName, bool (*pFn)(void*) );
	CLabelUI* SetLabelNode( CControlUI* pItemList, const tString& strWndName, const tString& strText, bool bShowHtml = false );
	CProgressUI* SetProgressNode( CControlUI* pItemList, const tString& strWndName, int nValue = 0, bool bShowHtml = false );
	//nIndex->序号，bSelState->是否为勾选状态，bIsActivate->是否响应click消息  by xhx
	CListIconUI* SetClickLabelNode( CControlUI* pItemList, const tString& strWndName, int nIndex = -1,
		bool bSelState = false, const tString& strItemName = _T(""), Node* pItemNode = NULL );


	 /*****************************************************************************
	* 功能:			方式二：创建列表数据(动态创建 条目 更灵活)
	* @param		[in]	const Data_DynamicList &data   动态列表结点数据 
	* @param		[in]	Node* parent				   父窗口指针 
	* @return		空 
	* @remarks		针对不同列表创建不同的数据规则
	-----------------------------------------------------------------------------
	修改记录:
	日  期         版本        修改人      修改内容
	2013/5/3       1.0         刘德印      创建
    ******************************************************************************/
	Node* DrawItem( const Data_DynamicList* pData, Node* pParent );
	Node* DrawItem( const Data_BoardList* pData, Node* pParent );
	Node* DrawItem( const Data_TvwStyleList* pData, Node* pParent );

	CListContainerElementUI* CreateElement( const tString& strHeight, const tString& strWidth = L"" );
	CLabelUI* CreateLabel(const TItemNodeUI& tItemNodeUI);
	CTextUI* CreateText(const TItemNodeUI& tItemNodeUI);
	CButtonUI* CreateButton(const TItemNodeUI& tItemNodeUI);
	CProgressUI* CreateProgress(const TItemNodeUI& tItemNodeUI);

	BOOL RemoveVirtualItem();      //删除已插入的虚拟列表项
	void ShowVirtualItemData();    //显示虚拟列表项

	void SetVirtualItemPos( int nIndex ){ m_nVirtualItemPos = nIndex; };
	int GetVirtualItemPos(){ return m_nVirtualItemPos; };

	void SetVirtualItemShow( BOOL bShowVirtualItem ){ m_bShowVirtualItem = bShowVirtualItem; };
	BOOL IsVirtualItemShow(){ return m_bShowVirtualItem; };

	BOOL DragEnd();					//拖拽结束同时更新列表数据

private:
	Node*	m_pNodeRoot;
	LONG	m_delayDeltaY;
	DWORD	m_delayNumber;
	DWORD	m_delayLeft;
	CRect	m_rcTextPadding;
	int m_nLevelTextStartPos;

	tString m_strLevelExpandImg;
	tString m_strLevelCollapseImg;

	tString m_strProgressName;

	int m_nListItemHeight;				//ITEM高度
	int m_nListItemSelHeight;			//ITEM选中高度
	int m_nListItemSelBkPos;            //ITEM选中背景位置

	CListUIDragWnd* m_wndListUIDrag;    //列表拖拽窗口

	BOOL m_bLButtonDown;
	POINT m_ptLButtonDown;				//鼠标按下位置
	BOOL m_bTimer;
	CRect m_rcPaintWindow;

	BOOL m_bDrag;

	CCommonListUI* m_pListDragWnd;
	Node* m_pNodeSelItem;				//当前选中的行数据信息
	HWND m_hWndMain;

	tString m_strStyle;

	CDialogBuilder m_dlgBuilder;

	CPaintManagerUI* m_pManageUI;

	CStdDataList<bool>* m_pListCheckState;
	CStdDataArray<IData*>* m_paryListData;

	int m_nVirtualItemPos;             //虚拟列表项的位置
	BOOL m_bShowVirtualItem;           //虚拟列表项是否已显示
};

#define ADD_NODE_VALUE( name, item, parent ) \
	if( L###name == item.GetType() ) { \
	if ( const name* pData = dynamic_cast<const name*>( &item ) )	\
{	\
	if ( NULL != pData )	\
	{	\
	return DrawItem( pData, parent );	\
}	\
}	\
}

#define ADD_NODE_VALUE_EX( name, item, parent ) \
if( L###name == item.GetType() ) { \
if ( const name* pData = dynamic_cast<const name*>( &item ) )	\
{	\
	if ( NULL != pData )	\
	{	\
	return DrawItemEx( pData, parent );	\
}	\
}	\
}


#endif // COMMONFILELIST_H