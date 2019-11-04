/*****************************************************************************
   模块名      : 
   文件名      : node.h
   相关文件    : 
   文件实现功能: 字典树节点
   作者        : 许成
   版本        : V3.0  Copyright(C) 2001-2002 KDC, All rights reserved.
-----------------------------------------------------------------------------
   修改记录:
   日  期      版本        修改人      修改内容
   2012/03/30  1.0         许成        创建
******************************************************************************/
#ifndef NODE_H
#define NODE_H
#include <memory.h>
#include "kdvtype.h"


//字典树节点
template<typename T>
class CNode
{
public:
	CNode(CNode<T>* pParent);
	~CNode();

public:
	//获得关键字
	u8				GetKey() const;
	//获得值
	T*				GetValue() const;
	//设置
	void			Set(u8 byKey, const T& value);
	//设置键
	void			SetKey(u8 byKey);
	//设置值
	void			SetValue(const T& value);
	//重置值
	void			ResetValue();
	//获得对应键值的指针
	CNode<T>*		GetChildPtr(u8 byKey);
	//添加子节点
	CNode<T>*		AddChildNode(u8 byKey);
	//删除子节点
	void			EraseChildNode(u8 byKey);
	//获得有效子节点的个数
	u8				GetChilidNodeNums() const;
	//返回父节点指针
	CNode<T>*		GetParentNode() const;

private:
	enum
	{
		MAX_CHILD_NODES	=	256	//子节点的最大数
	};

private:
	CNode<T>*		m_apChildNodes[MAX_CHILD_NODES];	//子节点指针
	CNode<T>*		m_pParent;							//指向父节点
	u8				m_byKey;							//当前节点保存的字母
	T*				m_pValue;							//获得保存的内容
	u8				m_byNums;							//子节点当前的个数
};

template<typename T>
CNode<T>::CNode(CNode<T>* pParent)
{
	memset(m_apChildNodes, 0, sizeof(m_apChildNodes));
	m_pParent   = pParent;
	m_byKey		= 0;
	m_pValue	= NULL;
	m_byNums	= 0;
}

template<typename T>
CNode<T>::~CNode()
{
	for (int i = 0; i < MAX_CHILD_NODES; ++i)
	{
		if (NULL != m_apChildNodes[i])
		{
			delete m_apChildNodes[i];
		}
	}

	if (NULL != m_pValue)
	{
		delete m_pValue;
	}
}

/*====================================================================
函数名    ：GetKey
功能      ：获得关键字
算法实现  ：
参数说明  ：
返回值说明：返回关键字
----------------------------------------------------------------------
修改记录 ：
日 期       版本  修改人 走读人 修改记录
2012/03/30  1.0   许成          创建
====================================================================*/
template<typename T>
inline u8 CNode<T>::GetKey() const
{
	return m_byKey;
}

/*====================================================================
函数名    ：GetValue
功能      ：获得值
算法实现  ：
参数说明  ：
返回值说明：返回关键字对应的值
----------------------------------------------------------------------
修改记录 ：
日 期       版本  修改人 走读人 修改记录
2012/03/30  1.0   许成          创建
====================================================================*/
template<typename T>
inline T* CNode<T>::GetValue() const
{
	return m_pValue;
}


/*====================================================================
函数名    ：Set
功能      ：设置
算法实现  ：
参数说明  ：[I]chKey 关键字 [I]value 关键字对应的值
返回值说明：无
----------------------------------------------------------------------
修改记录 ：
日 期       版本  修改人 走读人 修改记录
2012/03/30  1.0   许成          创建
====================================================================*/
template<typename T>
inline void CNode<T>::Set(u8 byKey, const T& value)
{
	SetKey(byKey);
	SetValue(value);
}

/*====================================================================
函数名    ：SetValue
功能      ：设置值
算法实现  ：
参数说明  ：[I]value 关键字对应的值
返回值说明：无
----------------------------------------------------------------------
修改记录 ：
日 期       版本  修改人 走读人 修改记录
2012/03/30  1.0   许成          创建
====================================================================*/
template<typename T>
inline void CNode<T>::SetValue(const T& value)
{
	if (NULL == m_pValue)
	{
		m_pValue = new T();
	}

	*m_pValue = value;
}

/*====================================================================
函数名    ：ResetValue
功能      ：重置值
算法实现  ：
参数说明  ：无
返回值说明：无
----------------------------------------------------------------------
修改记录 ：
日 期       版本  修改人 走读人 修改记录
2012/03/31  1.0   许成          创建
====================================================================*/
template<typename T>
inline void CNode<T>::ResetValue()
{
	if (NULL != m_pValue)
	{
		delete m_pValue;
		m_pValue = NULL;
	}
}


/*====================================================================
函数名    ：AddChileNode
功能      ：添加子节点
算法实现  ：
参数说明  ：[I]byKey 关键字
返回值说明：无
----------------------------------------------------------------------
修改记录 ：
日 期       版本  修改人 走读人 修改记录
2012/03/31  1.0   许成          创建
====================================================================*/
template<typename T>
inline CNode<T>* CNode<T>::AddChildNode(u8 byKey)
{
	if (NULL == m_apChildNodes[byKey])
	{
		m_apChildNodes[byKey] = new CNode<T>(this);
		m_apChildNodes[byKey]->SetKey(byKey);
		++m_byNums;
	}

	return m_apChildNodes[byKey];
}


/*====================================================================
函数名    ：GetChildPtr
功能      ：获得子关键字对应的值指针
算法实现  ：
参数说明  ：[I]byKey 关键字
返回值说明：关键字对应的值的指针
----------------------------------------------------------------------
修改记录 ：
日 期       版本  修改人 走读人 修改记录
2012/03/30  1.0   许成          创建
====================================================================*/
template<typename T>
inline CNode<T>* CNode<T>::GetChildPtr(u8 byKey)
{
	return m_apChildNodes[byKey];
}

/*====================================================================
函数名    ：GetChildNodeNums
功能      ：获得有效的子节点数目
算法实现  ：
参数说明  ：无
返回值说明：子节点数
----------------------------------------------------------------------
修改记录 ：
日 期       版本  修改人 走读人 修改记录
2012/03/31  1.0   许成          创建
====================================================================*/
template<typename T>
inline u8 CNode<T>::GetChilidNodeNums() const
{
	return m_byNums;
}

/*====================================================================
函数名    ：GetParentNode
功能      ：获得父节点的指针
算法实现  ：
参数说明  ：无
返回值说明：父节点指针
----------------------------------------------------------------------
修改记录 ：
日 期       版本  修改人 走读人 修改记录
2012/03/31  1.0   许成          创建
====================================================================*/
template<typename T>
inline CNode<T>* CNode<T>::GetParentNode() const
{
	return m_pParent;
}

/*====================================================================
函数名    ：EraseChildNode
功能      ：删除子节点
算法实现  ：
参数说明  ：[I]byKey 关键字
返回值说明：无
----------------------------------------------------------------------
修改记录 ：
日 期       版本  修改人 走读人 修改记录
2012/03/31  1.0   许成          创建
====================================================================*/
template<typename T>
inline void CNode<T>::EraseChildNode(u8 byKey)
{
	if (NULL != m_apChildNodes[byKey])
	{
		delete m_apChildNodes[byKey];
		m_apChildNodes[byKey] = NULL;
		--m_byNums;
	}
}

/*====================================================================
函数名    ：SetKey
功能      ：设置关键字
算法实现  ：
参数说明  ：[I]byKey 关键字
返回值说明：无
----------------------------------------------------------------------
修改记录 ：
日 期       版本  修改人 走读人 修改记录
2012/03/31  1.0   许成          创建
====================================================================*/
template<typename T>
inline void CNode<T>::SetKey(u8 byKey)
{
	m_byKey = byKey;
}

#endif