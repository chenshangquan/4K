#include "stdafx.h"
#include "ListUICommonDef.h"

namespace DuiLib
{
//////////////////////////////////////////////////////////////////////////

	double CalculateDelay(double state)
	{
		return pow(state, 2);
	}

	void Node::SetParent(Node* parent)
	{
		m_pNode = parent;
	}

	Node::Node()
		: m_pNode(NULL)
	{}

	Node::Node(NodeData t)
		: m_nodeData(t)
		, m_pNode(NULL)
	{
	}

	Node::Node(NodeData t, Node* parent)
		: m_nodeData (t)
		, m_pNode (parent)
	{}

	Node::~Node() 
	{
		for ( int i = 0; i < GetChildNum(); ++i )
		{
			SAFE_RELEASE(m_child[i]);
		}
	}

	NodeData& Node::GetData()
	{
		return m_nodeData;
	}

	int Node::GetChildNum() const
	{
		return static_cast<int>(m_child.size());
	}

	Node* Node::GetChild(int i)
	{
		return m_child[i];
	}

	Node* Node::GetParent()
	{
		return ( m_pNode);
	}

	bool Node::IsHasChild() const
	{
		return GetChildNum() > 0;
	}

	bool Node::IsFolder() const
	{
		return m_nodeData.bFolder;
	}

	void Node::AddChild(Node* child)
	{
		child->SetParent(this); 
		m_child.push_back(child); 
	}

	void Node::RemoveChild(Node* child)
	{
		Child::iterator iter = m_child.begin();
		for (; iter < m_child.end(); ++iter)
		{
			if (*iter == child) 
			{
				m_child.erase(iter);
				return;
			}
		}
	}

	Node* Node::GetLastChild()
	{
		if (IsHasChild())
		{
			return GetChild(GetChildNum() - 1)->GetLastChild();
		}
		return this;
	}

	const IData* Node::GetUserData()
	{
		return m_nodeData.pData;
	}

	void Node::SetUserData( IData* pNode )
	{
		if ( m_nodeData.pData != NULL )
		{
			SAFE_RELEASE(m_nodeData.pData);
		}
		else
		{
			m_nodeData.pData = dynamic_cast<IData*>(pNode->Clone());
		}
	}

}