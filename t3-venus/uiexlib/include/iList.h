
#ifndef ILIST_HEAD_H
#define ILIST_HEAD_H
#include "iBaseItem.h"
class IList  
{
	typedef IItem< IBaseItem, int > IItemList;
public:
	IList( int nWidht, int nHeight, String emLayout = IAlgorithm::strVert, String emSort = IAlgorithm::strCharacter, bool bShowSubItemAlways = TRUE );
	virtual ~IList();

public:
/**  绘制条目，会遍历所有条目的绘制函数
 *  @param[in] pArgs 绘制参数，一般包含一个graphics 
 *  @return
 */
	virtual void Draw( IArgs* pArgs, int nYOffset, int nHeight );
/**  对条目进行布局
 *  @param[in] 对条目进行布局
 *  @return 
 */
	void LayoutItem( IItemList* pList = 0 );

/**  排序条目
 *  @param[in] 对条目进行排序
 *  @return 
 */
	void SortItem( IItemList* pList = 0 );

/**  判断对应列表里面谁被点击了
 *  @param[in] pList父节点
 *  @param[in] point鼠标点 根据不同层次，会被转化为各自层的坐标
 *  @param[out] item 被点击到的条目
 *  @return 是否被点击
 */
	bool IsClick( IItemList* pList, CPoint point, IItemList** item ,BOOL bSetSel = FALSE );

/**  添加一个条目
 *  @param[in] pItem 条目
 *  @param[in] pParent 父节点 为空就表明加到根节点
 *  @param[in] emLayoutAlgorithmType布局的算法，emSortAlgorithmType 排序的算法
 *  @return 添加后的节点
 */
	IItemList* AddItem( IBaseItem* pItem, IItemList* pParent = 0 );
/**  添加一组条目
 *  @param[in] pList 条目列表
 *  @param[in] pParent 父节点 为空就表明加到根节点
 *  @return 是否成功
 */
	bool AddItem( IItemList* pList, IItemList* pParent = 0 );


	IItemList* AddItem( int nIndex, IBaseItem* pItem, IItemList* pParent /* = 0 */ );

/**  根据索引删除一个条目
 *  @param[in] nIndex 索引
 *  @param[in] pParent 父节点 为空就表明是根节点
 *  @return 是否成功
 */
	bool DeleteItem( int nIndex, IItemList* pParent = 0 );

/**  获得根节点
 *  @return 根节点
 */
	IItemList* GetRoot(){ return m_pItemList; }
/**  查找一个条目（不会递归）
 *  @param[in] pItem 条目对应的数据
 *  @param[in] pParent 父节点 为空就表明是根节点
 *  @return 找到的条目
 */
	IItemList* GetItem( IBaseItem* pItem, IItemList* pParent = 0 );

/**  获得一个列表的外框大小，只包含实际条目所在区域的大小，如果这个列表跟父Item有间隙，则不包含在内
 *  @param[in] pList 所要查找的节点，如果为空则表明是根节点
 *  @return 列表大小
 */
	CRect GetFrame( IItemList* pList = 0 );

	void SetListSize( unsigned int nWidht, unsigned int nHeight, IItemList* pList = 0 );

	bool SetLayoutAlgroithm( String strAlgorithm, IItemList* pItem = 0 );
	String GetLayoutAlgroithm( IItemList* pItem = 0 );

	bool SetSortAlgroithm( String strAlgorithm, IItemList* pItem = 0 );
	String GetSortAlgroithm( IItemList* pItem = 0 );

	void ShowItemAlways( bool bShow ){ m_bShowSubItemAlways = bShow; }
	bool IsShowItemAlways(){ return m_bShowSubItemAlways; }

	//是否每个条目的大小都一样  
	void SetItemSizeSame( bool bItemSizeSame = true ){ m_bItemSizeSame = bItemSizeSame; }

/**  
 *  @param[in] 
 *  @param[in] 
 *  @param[out] 
 *  @return 是否成功
 */
	protected:
/**  将目标点从一个坐标系转换到另外一个坐标系
 *  @param[in] ptSrcCoordinate 原来坐标系原点 矩形左上角
 *  @param[in] ptDesCoordinate 目标坐标系原点 矩形左上角
 *  @param[in] point 需要转换的点
 *  @return 转换后的点
 */
	CPoint TransPoint( CPoint& ptSrcCoordinate, CPoint& ptDesCoordinate, CPoint& point );

	//绘制第一层Item,只绘制需要的部分
	void DrawItem( IItemList* pItemList, IArgs* pArgs, int nYOffset, int nHeight );
	// 下面几个函数均用来递归
	void DrawSubItem( IItemList* pItemList, IArgs* pArgs );
	void Trasition( IItemList* pItemList );
	void Layout( IItemList* pItemList );
	void Sort( IItemList* pItemList );	

	void LayoutByIndex( int nIndex, IItemList* pItemList );

/*
 * 根节点\n 
 */
	IItemList* m_pItemList;
/*
 * 索引\n 
 */
	int m_nIndex;
/*
 * 是否根据父条目状态显示子项\n 
 */
	bool m_bShowSubItemAlways;

	int  m_nShowItemIndex;  //显示出来的第一个item的index
	int  m_nShowItemNum;    //显示出来的item的数量
	bool m_bItemSizeSame;   //是否每个item的大小都一样,默认为true，2012-7-11 by yjj 减少获取列表大小的计算量
};

#endif