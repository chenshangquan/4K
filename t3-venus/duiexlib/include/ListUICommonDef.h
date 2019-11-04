/*****************************************************************************
模块名      : ListUICommonDef
文件名      : ListUICommonDef.h
相关文件    : 
文件实现功能: 列表公共定义文件（包括结点、列表数据类型等）
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/5/20     1.0         刘德印      创建
******************************************************************************/
#ifndef LISTUICOMMONDEF_H
#define LISTUICOMMONDEF_H

namespace DuiLib
{

#define PRO_PANE_LISTITEM_HIDE			_T("paneListItemHide")
UILIB_API double CalculateDelay(double state);

//注册Data映射
#define REG_LIST_DATA_MAP( name, datastruct )	\
class UILIB_API name : public IData	\
{	\
public:	\
	name( datastruct &tData ) : IData( L###name ), m_tData( tData ){}	\
	IData* Clone()	\
{	\
	name* pData = new name( m_tData );	\
	pData->SetDataKey( GetDataKey() );	\
	return pData;	\
}	\
	datastruct  m_tData;	\
};


//列表条目单元的信息
typedef struct tagTItemNodeUI
{
	tString strPos;
	tString strWidth;
	tString strHeight;
	tString strText;
	tString strFontColor;
	int nFont;
	int nValue;
	tString strImgPath;

public:
	tagTItemNodeUI()
	{
		Clear();
	}

	void Clear()
	{
		memset( this, 0, sizeof(tagTItemNodeUI) );
	}

}TItemNodeUI;


//列表条目数据基类
class UILIB_API IData
{
public:
	IData( std::wstring strType ) : m_strType( strType ), m_dwKey( -1 ){}
	virtual ~IData(){}
	std::wstring GetType() const { return m_strType; } 
	unsigned long GetDataKey() { return m_dwKey; }
	void SetDataKey( unsigned long dwKey ) { m_dwKey = dwKey; }

	virtual IData* Clone() = 0;
protected:
	unsigned long m_dwKey;      //Data键值，用于查找Item
	std::wstring m_strType;
};

//列表数据域IData
struct NodeData
{
	int nLevel;
	bool bFolder;
	bool bChildVisible;
	bool bHasChild;
	const IData* pData;
	CListContainerElementUI* pListElement;

public:
	NodeData()
	{
		memset( this, 0, sizeof(NodeData) );
	}
};

class UILIB_API Node
{
public:
	Node();
	explicit Node(NodeData tNodeData);
	Node(NodeData tNodeData, Node* pParent);
	~Node();
	NodeData& GetData();
	int GetChildNum() const;
	Node* GetChild(int nIndex);
	Node* GetParent();
	bool IsFolder() const;
	bool IsHasChild() const;
	void AddChild(Node* child);
	void RemoveChild(Node* child);
	Node* GetLastChild();

	//数据域
	const IData* GetUserData();
	void SetUserData( IData* pData );

private:
	void SetParent(Node* pParent);

private:
	typedef std::vector <Node*>	Child;

	Child	m_child;
	Node*		m_pNode;
	NodeData    m_nodeData;
};

//////////////////////////列表Data_Struct////////////////////////////////
//

/////////////////////////////////////////////////////////////////////////
//                     文件列表
//
//文件列表结构体
struct TFileListItemInfo
{
	bool bFolder;
	tString strKey;
	tString strFileName;
	tString strPath;

public:
	TFileListItemInfo()
	{
		memset( this, 0, sizeof(TFileListItemInfo) );
	}
};
REG_LIST_DATA_MAP( Data_FileList, TFileListItemInfo )				//文件列表ITEM数据


/////////////////////////////////////////////////////////////////////////
//                     会议列表
//
//会议列表结构体
struct TConfListItemInfo
{
	tString strKey;
	tString strConfID;
	tString strConfName;
	int     nProgress;

public:
	TConfListItemInfo()
	{
		memset( this, 0, sizeof(TConfListItemInfo) );
	}
};
REG_LIST_DATA_MAP( Data_ConfList, TConfListItemInfo )				//会议列表ITEM数据

/////////////////////////////////////////////////////////////////////////
//                     动态列表
//
//动态列表结构体
struct TDynamicListItemInfo
{
	tString strKey;
	tString strID;
	tString strName;
	int     nProgress;

public:
	TDynamicListItemInfo()
	{
		memset( this, 0, sizeof(TDynamicListItemInfo) );
	}
};
REG_LIST_DATA_MAP( Data_DynamicList, TDynamicListItemInfo )			//动态列表ITEM数据

/////////////////////////////////////////////////////////////////////////
//                     单板列表
//
//单板列表结构体
struct TBoardListItemInfo
{
	tString strKey;
	tString strID;
	tString strName;

public:
	TBoardListItemInfo()
	{
		memset( this, 0, sizeof(TBoardListItemInfo) );
	}
};
REG_LIST_DATA_MAP( Data_BoardList, TBoardListItemInfo )				//单板列表ITEM数据

/////////////////////////////////////////////////////////////////////////
//                     电视墙预案列表
//
//电视墙预案列表结构体
struct TTvwStyleListItemInfo
{
	tString strKey;
	tString strID;
	tString strName;

public:
	TTvwStyleListItemInfo()
	{
		memset( this, 0, sizeof(TTvwStyleListItemInfo) );
	}
};
REG_LIST_DATA_MAP( Data_TvwStyleList, TTvwStyleListItemInfo )		//电视墙预案列表ITEM数据

/////////////////////////////////////////////////////////////////////////
//                     地址簿列表
//
//地址簿列表结构体
struct TAddrListItemInfo
{
	tString strKey;
	//tString strAddrID;
	tString strAddrName;
	tString strAddrNum;
public:
	TAddrListItemInfo()
	{
		memset( this, 0, sizeof(TAddrListItemInfo) );
	}
};
REG_LIST_DATA_MAP( Data_AddrList, TAddrListItemInfo )				//地址簿列表ITEM数据

/////////////////////////////////////////////////////////////////////////
//                     更新进度条数据
//
//进度条数据结构体
struct TProgressInfo
{
	int nIndex;
	int nValue;

public:
	TProgressInfo()
	{
		memset( this, 0, sizeof(TProgressInfo) );
	}
};
REG_LIST_DATA_MAP( Data_ProgressInfo, TProgressInfo )				//地址簿列表ITEM数据


} // DuiLib

#endif // LISTUICOMMONDEF_H