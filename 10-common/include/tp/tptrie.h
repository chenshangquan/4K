/*****************************************************************************
   模块名      : 
   文件名      : trie.h
   相关文件    : 
   文件实现功能: 字典树
   作者        : 许成
   版本        : V3.0  Copyright(C) 2001-2002 KDC, All rights reserved.
-----------------------------------------------------------------------------
   修改记录:
   日  期      版本        修改人      修改内容
   2012/03/29  1.0         许成        创建
******************************************************************************/

#ifndef TRIE_H
#define TRIE_H
#include "tpnode.h"

//字典树
template<typename T>
class CTrie
{
public:
	CTrie();
	~CTrie();

public:
	//插入
	BOOL32			Insert(char* szKey, const T& value);
	//查找
	T*				Find(char* szKey);
	//保留关键字，删除关键字对应的值
	BOOL32			Erase(char* szKey);
	//删除，同时删除关键字和对应的值
	BOOL32			EraseEx(char* szKey);
	//获得树中有效节点总数
	u16				GetTotalNodes() const;

private:
	//查找指定的串
	CNode<T>*		FindKey(char* szKey);

private:
	CNode<T>*		m_pcRootNode;	//根节点
	u16				m_wTotalNodes;	//有效节点总数
};

template<typename T>
CTrie<T>::CTrie()
{
	m_pcRootNode	= new CNode<T>(NULL);
	m_wTotalNodes	= 0;
}

template<typename T>
CTrie<T>::~CTrie()
{
	delete m_pcRootNode;
}

/*====================================================================
函数名    ：Insert
功能      ：插入关键字及其对应的值，如果关键字已经存在则更新它对应的值
算法实现  ：
参数说明  ：[I]chkey 关键字	[I]value 关键字对应的值
返回值说明：存在返回true 不存在返回false
----------------------------------------------------------------------
修改记录 ：
日 期       版本  修改人 走读人 修改记录
2012/03/30  1.0   许成          创建
====================================================================*/
template<typename T>
inline BOOL32 CTrie<T>::Insert(char* szKey, const T& value)
{
	CNode<T>* pNode = FindKey(szKey);

	//节点不存在插入新节点
	if (NULL == pNode)
	{
		CNode<T>* pTemp = m_pcRootNode;
		u8 byIndex = 0;
		u8 byVal = szKey[byIndex];

		while (true)
		{
			byVal = szKey[byIndex];

			if (0 == byVal)
			{
				if (0 == byIndex)
				{
					return FALSE;
				}
				else
				{
					pTemp->SetValue(value);
					++m_wTotalNodes;
					break;
				}
			}
			else
			{
				pTemp = pTemp->AddChildNode(byVal);
				++byIndex;
			}
		}
	}
	else
	{
		pNode->SetValue(value);
		++m_wTotalNodes;
	}

	return TRUE;
}

/*====================================================================
函数名    ：Find
功能      ：查找对应的关键字是否存在
算法实现  ：
参数说明  ：[I]chkey 关键字
返回值说明：存在返回对应的指针  不存在返回0
----------------------------------------------------------------------
修改记录 ：
日 期       版本  修改人 走读人 修改记录
2012/03/30  1.0   许成          创建
====================================================================*/
template<typename T>
inline T* CTrie<T>::Find(char* szKey)
{
	CNode<T>* pNode = FindKey(szKey);
	if (NULL == pNode)
	{
		return NULL;
	}
	else
	{
		if (0 == pNode->GetValue())
		{
			return FALSE;
		}
		else
		{
			return pNode->GetValue();
		}
	}
}

/*====================================================================
函数名    ：Erase
功能      ：删除指定的串对应的信息
算法实现  ：
参数说明  ：[I]chkey 关键字
返回值说明：删除成功返回true  失败返回false
----------------------------------------------------------------------
修改记录 ：
日 期       版本  修改人 走读人 修改记录
2012/03/31  1.0   许成          创建
====================================================================*/
template<typename T>
inline BOOL32 CTrie<T>::Erase(char* szKey)
{
	CNode<T>* pNode = FindKey(szKey);
	if (NULL == pNode)
	{
		return FALSE;
	}
	else
	{
		if (NULL == pNode->GetValue())
		{
			return FALSE;
		}
		else
		{
			pNode->ResetValue();
			--m_wTotalNodes;
			return TRUE;
		}
	}
}

/*====================================================================
函数名    ：EraseEx
功能      ：进行删除，同时删除关键字和对应的值
算法实现  ：
参数说明  ：[I]chkey 关键字
返回值说明：删除成功返回true  失败返回false
----------------------------------------------------------------------
修改记录 ：
日 期       版本  修改人 走读人 修改记录
2012/03/31  1.0   许成          创建
====================================================================*/
template<typename T>
inline BOOL32 CTrie<T>::EraseEx(char* szKey)
{
	CNode<T>* pNode = FindKey(szKey);
	if (NULL == pNode)
	{
		return FALSE;
	}
	else
	{
		if (NULL == pNode->GetValue())
		{
			return FALSE;
		}
		else
		{
			pNode->ResetValue();
			--m_wTotalNodes;
			
			//删除串中不被共享的节点
			CNode<T>* pTemp = pNode->GetParentNode();
			while (true)
			{
				if (0 != pNode->GetChilidNodeNums())
				{
					return TRUE;
				}
				else
				{
					pTemp->EraseChildNode(pNode->GetKey());
					pNode = pTemp;
					pTemp = pNode->GetParentNode();
					if (0 == pTemp)
					{
						return TRUE;
					}
				}
			}
		}
	}
}


/*====================================================================
函数名    ：FindKey
功能      ：查找指定关键字对应的节点
算法实现  ：
参数说明  ：[I]chkey 关键字
返回值说明：存在返回节点的指针，不存在返回0
----------------------------------------------------------------------
修改记录 ：
日 期       版本  修改人 走读人 修改记录
2012/03/30  1.0   许成          创建
====================================================================*/
template<typename T>
inline CNode<T>* CTrie<T>::FindKey(char* szKey)
{
	if (NULL == m_pcRootNode)
	{
		return NULL;
	}

	CNode<T>* pTemp = m_pcRootNode;
	u8 byIndex		= 0;
	u8 byVal		= 0;

	while (true)
	{
		byVal = szKey[byIndex];
		if (0 == byVal)
		{
			if (0 == byIndex)
			{
				return NULL;
			}
			else
			{
				return pTemp;
			}
		}
		else
		{
			if (0 == pTemp->GetChildPtr(byVal))
			{
				return 0;
			}
			else
			{
				pTemp = pTemp->GetChildPtr(byVal);
				++byIndex;
			}
		}
	}
}

/*====================================================================
函数名    ：GetTotalNodes
功能      ：获得树中有效节点总数
算法实现  ：
参数说明  ：无
返回值说明：返回树中有效节点总数
----------------------------------------------------------------------
修改记录 ：
日 期       版本  修改人 走读人 修改记录
2012/04/06  1.0   许成          创建
====================================================================*/
template<typename T>
inline u16 CTrie<T>::GetTotalNodes() const
{
	return m_wTotalNodes;
}

#endif