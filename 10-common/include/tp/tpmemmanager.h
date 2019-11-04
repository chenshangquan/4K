/*****************************************************************************
   模块名      : 
   文件名      : mempool.h
   相关文件    : 
   文件实现功能: 内存池
   作者        : 许成
   版本        : V3.0  Copyright(C) 2001-2002 KDC, All rights reserved.
-----------------------------------------------------------------------------
   修改记录:
   日  期      版本        修改人      修改内容
   2012/04/07  1.0         许成        创建
******************************************************************************/
#ifndef MEM_MANAGER_H
#define MEM_MANAGER_H
#include "kdvtype.h"

/**************************************************************
 * 使用双向链表实现的一个内存池,通过一个U32的值来标识元素的位置。
 * 如果需要修改保存的数据有两种方式，一种是通过添加的时候返回的
 * ID，这种方式比较快速。另外也可以使用数据来查找，这比较慢。
 * 因为会有相同的数据存在，所以后面的方式的正确性也很难保证。使用该类
 * 应该总是使用和ID相关的接口进行操作，但是使用者需要保证ID的正确性。
***************************************************************/
template<typename T>
class CMemPool
{
public:
	CMemPool();
	~CMemPool();

public:
	//开辟一个新的空间，并返回给用户
	u32			Add();
	//根据ID获得对应的值
	T*			FindByID(u32 dwID);
	//删除ID对应的值
	void		EraseByID(u32 dwID);
	//清空
	void		Clear();
	//获得有效长度
	u32			Size() const;

public:
	//遍历取得第一个数据
	T*			First();
	//一次取得下面的数据
	T*			Next();
	//获得当前遍历节点的ID
	u32			GetCurID();

public:
	//根据值进行查找，返回找到的第一个
	T*			Find(const T& value);
	//通过值找到对应的ID
	u32			FindID(const T& value);
	//删除指定的值
	void		Erase(const T& value);

public:
	//获得总量
	u32			TotalSize();
	//当前使用量
	u32			UseSize();

private:
	//禁用复制
	CMemPool(const CMemPool<T>& );
	CMemPool<T>& operator=(const CMemPool<T>& );

private:
	//节点
	typedef struct tagNode
	{
		tagNode*	m_pNext;	//下一个
		tagNode*	m_pFront;	//前一个
		T			m_value;	//保存的值
	}TNode, *PTnode;
	//每次额外分配的节点数
	enum
	{
		ASSIGN_SIZE	=	30
	};

private:
	//初始化
	void		Init(u16 wSize);
	//分配节点
	u16			AssignNode(u16 wSize);

public:
	TNode*		m_pHead;		//头节点
	TNode*		m_pCurNode;		//当前节点
	TNode*		m_pFirstNode;	//遍历起始节点
	u32			m_dwIndex;		//遍历的索引
	u32			m_dwSize;		//有效节点个数
	u32			m_dwTotal;		//节点总数
	BOOL32		m_bFlag;		//遍历标识
};

template<typename T>
CMemPool<T>::CMemPool()
{
	Init(ASSIGN_SIZE);
}

template<typename T>
CMemPool<T>::~CMemPool()
{
	TNode* pNode = m_pHead;
	TNode* pNext = NULL;
	while (NULL != pNode)
	{
		pNext = pNode->m_pNext;
		delete pNode;
		pNode = pNext;
	}
}

/*====================================================================
函数名    ：Add
功能      ：添加数据
算法实现  ：
参数说明  ：[I]pValue 指针
返回值说明：返回一个唯一节点ID
----------------------------------------------------------------------
修改记录 ：
日 期       版本  修改人 走读人 修改记录
2012/04/07  1.0   许成          创建
====================================================================*/
template<typename T>
inline u32 CMemPool<T>::Add()
{
	//没有节点
// 	if (0 == m_dwTotal)
// 	{
// 		return 0;
// 	}

	TNode* pNode = m_pCurNode;
	//无可用的节点
	if (0 == m_dwTotal || m_dwSize == m_dwTotal)
	{
		if (0 == AssignNode(ASSIGN_SIZE))
		{
			return 0;
		}
		else
		{
			m_pCurNode = pNode->m_pNext;
		}
	}
	pNode = m_pCurNode;

	++m_dwSize;
	if (m_dwSize != m_dwTotal)
	{
		m_pCurNode = m_pCurNode->m_pNext;
	}

	return (u32)pNode;
}

/*====================================================================
函数名    ：FindByID
功能      ：根据指定的ID获得对应值的引用，它并不保证ID的有效性，如果无效会
			产生异常
算法实现  ：
参数说明  ：[I]dwID ID
返回值说明：返回值对应的指针，如果传递0则返回空指针
----------------------------------------------------------------------
修改记录 ：
日 期       版本  修改人 走读人 修改记录
2012/04/07  1.0   许成          创建
====================================================================*/
template<typename T>
inline T* CMemPool<T>::FindByID(u32 dwID)
{
	if (0 == dwID)
	{
		return NULL;
	}
	else
	{
		TNode* pNode = (TNode*)dwID;
		return &(pNode->m_value);
	}
}

/*====================================================================
函数名    ：Find
功能      ：根据值进行查找，它会返回找到得第一个。如果保存的T类型不支持
			比较操作符(==)，不要调用该接口
算法实现  ：
参数说明  ：[I]value 要查找的值
返回值说明：返回值对应的指针，如果传递0则返回空指针
----------------------------------------------------------------------
修改记录 ：
日 期       版本  修改人 走读人 修改记录
2012/04/07  1.0   许成          创建
====================================================================*/
template<typename T>
inline T* CMemPool<T>::Find(const T& value)
{
	TNode* pNode = m_pHead->m_pNext;
	for (u16 wIndex = 0; wIndex < m_dwSize; ++wIndex)
	{
		if (value == pNode->m_value)
		{
			return &(pNode->m_value);
		}
		pNode = pNode->m_pNext;
	}
	return 0;
}

/*====================================================================
函数名    ：FindID
功能      ：根据值查找对应的ID，它会返回找到得第一个。如果保存的T类型不支持
			比较操作符(==)，不要调用该接口
算法实现  ：
参数说明  ：[I]value 要查找的值
返回值说明：返回值对应的ID，如果传递0则返回空指针
----------------------------------------------------------------------
修改记录 ：
日 期       版本  修改人 走读人 修改记录
2012/04/07  1.0   许成          创建
====================================================================*/
template<typename T>
inline u32 CMemPool<T>::FindID(const T& value)
{
	TNode* pNode = m_pHead->m_pNext;
	for (u16 wIndex = 0; wIndex < m_dwSize; ++wIndex)
	{
		if (value == pNode->m_value)
		{
			return (u32)pNode;
		}
		pNode = pNode->m_pNext;
	}
	return 0;
}

/*====================================================================
函数名    ：EraseByID
功能      ：删除指定的ID对应的数据,内部不保证ID的有效性，如果不存在会发生异常
算法实现  ：
参数说明  ：[I]dwID  ID
返回值说明：无
----------------------------------------------------------------------
修改记录 ：
日 期       版本  修改人 走读人 修改记录
2012/04/07  1.0   许成          创建
====================================================================*/
template<typename T>
inline void CMemPool<T>::EraseByID(u32 dwID)
{
	TNode* pNode = (TNode*)dwID;
	if (m_pCurNode == pNode)
	{
		m_pCurNode = pNode->m_pFront;
	}

	pNode->m_pFront->m_pNext = pNode->m_pNext;
	if (0 != pNode->m_pNext)
	{
		pNode->m_pNext->m_pFront = pNode->m_pFront;
	}
	delete pNode;
	--m_dwSize;
	--m_dwTotal;
}

/*====================================================================
函数名    ：Erase
功能      ：根据值进行删除，它会删除找到得第一个。如果保存的T类型不支持
			比较操作符(==)，不要调用该接口
算法实现  ：
参数说明  ：[I]value 要删除的值
返回值说明：无
----------------------------------------------------------------------
修改记录 ：
日 期       版本  修改人 走读人 修改记录
2012/04/07  1.0   许成          创建
====================================================================*/
template<typename T>
inline void CMemPool<T>::Erase(const T& value)
{
	TNode* pNode = m_pHead->m_pNext;
	for (u16 wIndex = 0; wIndex < m_dwSize; ++wIndex)
	{
		if (value == pNode->m_value)
		{
			pNode->m_pFront->m_pNext = pNode->m_pNext;
			if (0 != pNode->m_pNext)
			{
				pNode->m_pNext->m_pFront = pNode->m_pFront;
			}
			delete pNode;
			--m_dwSize;
			--m_dwTotal;

			return ;
		}
		pNode = pNode->m_pNext;
	}
}

/*====================================================================
函数名    ：Clear
功能      ：清空
算法实现  ：
参数说明  ：无
返回值说明：无
----------------------------------------------------------------------
修改记录 ：
日 期       版本  修改人 走读人 修改记录
2012/04/07  1.0   许成          创建
====================================================================*/
template<typename T>
inline void CMemPool<T>::Clear()
{
	m_dwSize	= 0;
	m_pCurNode	= m_pHead->m_pNext;
}
/*====================================================================
函数名    ：First
功能      ：遍历获得第一个节点数据
算法实现  ：
参数说明  ：无
返回值说明：成功返回指针，失败返回0
----------------------------------------------------------------------
修改记录 ：
日 期       版本  修改人 走读人 修改记录
2012/04/07  1.0   许成          创建
====================================================================*/
template<typename T>
inline T* CMemPool<T>::First()
{
	m_dwIndex		= 0;
	if (0 == m_dwSize)
	{
		m_bFlag = FALSE;
		return NULL;
	}
	else
	{
		m_bFlag = TRUE;
		m_pFirstNode = m_pHead->m_pNext;
		return &(m_pFirstNode->m_value);
	}
}

/*====================================================================
函数名    ：Next
功能      ：获得下一个节点，必须首先成功调用first，否则会失败
算法实现  ：
参数说明  ：无
返回值说明：成功返回指针，失败返回0
----------------------------------------------------------------------
修改记录 ：
日 期       版本  修改人 走读人 修改记录
2012/04/07  1.0   许成          创建
====================================================================*/
template<typename T>
inline T* CMemPool<T>::Next()
{
	if (!m_bFlag)
	{
		return NULL;
	}

	++m_dwIndex;
	if (m_dwIndex == m_dwSize)
	{
		m_bFlag = FALSE;
		return NULL;
	}
	else
	{
		m_pFirstNode = m_pFirstNode->m_pNext;
		return &(m_pFirstNode->m_value);
	}
}

/*====================================================================
函数名    ：GetCurID
功能      ：获得当前遍历节点的ID
算法实现  ：
参数说明  ：无
返回值说明：返回当前遍历节点的ID
----------------------------------------------------------------------
修改记录 ：
日 期       版本  修改人 走读人 修改记录
2012/04/07  1.0   许成          创建
====================================================================*/
template<typename T>
inline u32 CMemPool<T>::GetCurID()
{
	if (!m_bFlag)
	{
		return 0;
	}
	else
	{
		return (u32)m_pFirstNode;
	}
}

/*====================================================================
函数名    ：Size
功能      ：获取有效长度
算法实现  ：
参数说明  ：无
返回值说明：无
----------------------------------------------------------------------
修改记录 ：
日 期       版本  修改人 走读人 修改记录
2012/04/13  1.0   许成          创建
====================================================================*/
template<typename T>
inline u32 CMemPool<T>::Size() const
{
	return m_dwSize;
}


/*====================================================================
函数名    ：Init
功能      ：初始化
算法实现  ：
参数说明  ：[I]wSize 节点的数量
返回值说明：无
----------------------------------------------------------------------
修改记录 ：
日 期       版本  修改人 走读人 修改记录
2012/04/07  1.0   许成          创建
====================================================================*/
template<typename T>
inline void CMemPool<T>::Init(u16 wSize)
{
	m_dwSize	= 0;
	m_dwTotal	= 0;
	m_dwIndex	= 0;
	m_pCurNode	= NULL;
	m_bFlag		= FALSE;
	m_pHead = new TNode();
	if (NULL == m_pHead)
	{
		return ;
	}
	else
	{
		m_pHead->m_pFront = NULL;
		m_pHead->m_pNext  = NULL;

		m_pCurNode = m_pHead;

		AssignNode(wSize);

		m_pCurNode		= m_pHead->m_pNext;
		m_pFirstNode	= m_pHead->m_pNext;
	}
}

/*====================================================================
函数名    ：AssignNode
功能      ：分配节点
算法实现  ：
参数说明  ：[I]wSize 节点的数量
返回值说明：返回分配的节点数
----------------------------------------------------------------------
修改记录 ：
日 期       版本  修改人 走读人 修改记录
2012/04/07  1.0   许成          创建
====================================================================*/
template<typename T>
inline u16 CMemPool<T>::AssignNode(u16 wSize)
{
	for (u16 wIndex = 0; wIndex < wSize; ++wIndex)
	{
		m_pCurNode->m_pNext = new TNode();
		if (NULL == m_pCurNode->m_pNext)
		{
			return wIndex;
		}
		else
		{
			m_pCurNode->m_pNext->m_pFront = m_pCurNode;
			m_pCurNode = m_pCurNode->m_pNext;
			++m_dwTotal;
		}
	}
	m_pCurNode->m_pNext = NULL;
	return wSize;
}

template<typename T>
inline u32 CMemPool<T>::TotalSize()
{
	return m_dwTotal;
}

template<typename T>
inline u32 CMemPool<T>::UseSize()
{
	return m_dwSize;
}

#endif
