
#ifndef IBASEITEM_HEAD_H
#define IBASEITEM_HEAD_H
#include "iAlgorithm.h"
#include "uiexBaseData.h"


enum EmItemStatus
{    
	emItemStatusNormal = 0,
		emItemStatusSel,
		emItemStatusDown,
		emItemStatusOver,
		emItemStatusDisable   
};


class IBaseItem  
{
public:
	static const String strDefaultFunc;
	
	const static String strNormalImg;
	const static String strDownImg;
	const static String strDisableImg;
	const static String strOverImg;
    const static String strSelImg;
public:
	IBaseItem( int nWidht, int nHeight, String strFunc = IBaseItem::strDefaultFunc,
		String emLayout = IAlgorithm::strHori, String emSort = IAlgorithm::strDefaultAlg, 
		bool bCanDrag = false, bool bCanMove = false, CPoint ptOffset = CPoint(0,0), EmItemStatus emItemStatus = emItemStatusNormal, bool bAlwaysShow = true );

	IBaseItem(const IBaseItem& item);
	virtual ~IBaseItem();
 
public:
/**  绘制条目
 *  @param[in] pArgs 绘制参数 
 *  @return 
 */
	virtual void Draw( IArgs* pArgs ) = 0;
/**  条目克隆
 *  @return 克隆后的条目
 */
	virtual IBaseItem* Clone() = 0;	

/*
 * 条目的一些属性获取\n 
 */
	CRect GetItemRect(){ return m_rcItem; }
	void SetItemRect(CRect rc){ m_rcItem = rc; }
	int GetItemHeight(){ return m_rcItem.Height(); }
	int GetItemWidth(){ return m_rcItem.Width(); }

/*
 * 条目是否被点中\n 
 */
	bool IsClick( CPoint ptMouse )
	{
		return m_rcItem.PtInRect( ptMouse );
	}
	virtual void SetItemStatus( EmItemStatus emStatus = emItemStatusNormal ){ m_emItemStatus = emStatus; }
	EmItemStatus GetItemStatus(){ return m_emItemStatus; }

/**  条目绑定的事件执行
 *  @return 
 */
	bool ExeFunc();
	String GetFunc(){ return m_strFunc; }
	void SetFunc( String strFunc ){ m_strFunc = strFunc; }

/*
 * 设置和获取用户数据\n 
 */
	void SetUserData( IData* pData );
	const IData* GetUserData();

/*
 * Item可重载事件\n 
 */
	virtual void Click(){};
    virtual void SetImageFolder( String strFolder ) {}

    virtual void OnItemDown(){ SetItemStatus( emItemStatusDown ); }
    virtual void OnItemUp( CPoint point ){ }

/*
 * 设置ImageItem的图片全路径 
 */
	virtual void SetImagePath( String strImagePath ) {};
protected:
	CRect m_rcItem;
	String m_strFunc;
	EmItemStatus m_emItemStatus;
	IData* m_pData;// 临时保存的变量

public:
	void SetLayoutAlgorithm( String strType ){ m_strLayoutAlgorithm = strType; }
	String GetLayoutAlgorithm(){ return m_strLayoutAlgorithm; }
	void SetSortAlgorithm( String strType ){ m_strSortAlgorithm = strType; }
 	String GetSortAlgorithm(){ return m_strSortAlgorithm; }

	CPoint GetOffset(){ return m_ptOffset; }
	void SetOffset( CPoint pt ){ m_ptOffset = pt; }
	bool GetDragStatus(){ return m_bCanDrag; }
 	void SetDragStatus( bool bDrag ){ m_bCanDrag = bDrag; }
	bool GetMoveStatus(){ return m_bCanMove; }
	void SetMoveStatus( bool bMove ){ m_bCanMove = bMove; }
	bool IsAlwaysShow(){ return m_bAlwaysShow; }
	void SetAlwaysShow( bool bShow ){ m_bAlwaysShow = bShow; } 
protected:
	/*
 * 布局算法 表示这个Item内部条目的布局算法\n 
 */
	String m_strLayoutAlgorithm;
/*
 * 排序算法 表示这个Item内部条目的排序算法\n 
 */
	String m_strSortAlgorithm;
/*
 * 偏移点 表示这个Item里面条目的偏移，并非自身的\n 
 */
	CPoint m_ptOffset;
/*
 * 是否拖拽\n 
 */
	bool m_bCanDrag;
/*
 * 是否移动\n 
 */
	bool m_bCanMove;
/*
 * 是否一直显示，false时父条目选中才显示\n 
 */
	bool m_bAlwaysShow;
};

typedef IItem<IBaseItem,int> IItemList;
//点击Item后的返回参数
class Args_ClickItemInfo : public IArgs
{
public:
    
    Args_ClickItemInfo( CWnd* pSrcWnd, IItemList* pList, CRect rcFrame ) : IArgs( "ClickItemInfo" ), m_pSrcWnd( pSrcWnd ),m_pClickList( pList ), m_rcFrame( rcFrame ){}
    CWnd* m_pSrcWnd;
    IItemList* m_pClickList;
    CRect m_rcFrame;
};

#endif