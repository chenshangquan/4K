/*****************************************************************************
模块名      : Property_UmcToolListData
文件名      : touchlistdataproperty.h
相关文件    : 
文件实现功能: 列表属性管理类
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2012/12/18     1.0         刘德印      创建
******************************************************************************/
#if !defined(AFX_TOUCHLISTDATAPROPERTY_H__6BEB62C7_9690_4ABB_852B_2CE555E8A57A__INCLUDED_)
#define AFX_TOUCHLISTDATAPROPERTY_H__6BEB62C7_9690_4ABB_852B_2CE555E8A57A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PropertyHelp.h"

#define ARRAY   vector
#define FUNNAME_MAXLEN 64	//函数名最大长度
#define ITEMNAME_MAXLEN 32	//条目名称最大长度
#define PATH_MAX		512

//菜单条目
typedef struct tagMenuItem
{   
	char szName[ITEMNAME_MAXLEN];		     //条目名称
	char szClickFunName[FUNNAME_MAXLEN];	 //click处理函数名
	char szItemType[ITEMNAME_MAXLEN];        //条目类型，具体内容在itemInfo.xml 配置
	char szImgFolder[PATH_MAX];			  	 //条目图片路径
	
	void SetItemName( LPCSTR lpstring  )
	{ 
		_snprintf( szName, sizeof(szName), "%s", lpstring );	
	}
	
	void SetItemFuncName( LPCSTR lpstring  )
	{ 
		_snprintf( szClickFunName, sizeof(szClickFunName), "%s", lpstring );	
	}
	
	void SetItemType( LPCSTR lpstring  )
	{ 
		_snprintf( szItemType, sizeof(szItemType), "%s", lpstring );	
	}
	
	void SetItemImg( LPCSTR lpstring  )
	{ 
		_snprintf( szImgFolder, sizeof(szImgFolder), "%s", lpstring );	
	}
	
	
	tagMenuItem()
	{
		ZeroMemory( this, sizeof(tagMenuItem) );
	}
	
} TMenuItem, *PTMenuItem;

class Data_Common : public IData
{
public:
    Data_Common( CUserFullInfo &cUser ) : IData( "CommonList" ), m_cUser( cUser ){}
    IData* Clone()
    {
        Data_Common* pData = new Data_Common( m_cUser );
        pData->SetDataKey( GetDataKey() );
        return pData;
    }
	
    CUserFullInfo m_cUser;
};

//普通列表 
class Value_TouchListCommon : public Value_ListBase
{
public:
    Value_TouchListCommon( TplArray<CUserFullInfo>* pUserLst, String strClickItemFunc = IBaseItem::strDefaultFunc ,
        vector<String> * pVctSubItem = NULL, String strAlgroithm = IAlgorithm::strVert,
        BOOL32 bDrag = FALSE ) 
        : Value_ListBase(), m_pTplArryUser( pUserLst ), m_strClickItemFunc( strClickItemFunc ),
        m_pVctSubItem( pVctSubItem ), m_strAlgroithm(strAlgroithm),m_bDrag(bDrag){}
	
    TplArray<CUserFullInfo>*  m_pTplArryUser ;
    String m_strClickItemFunc;		    		// 条目点击回调函数 
    vector<String> * m_pVctSubItem;				//子条目对应的xml中名字
    BOOL32 m_bDrag;								//是否可以拖动
    String m_strAlgroithm;						//排列算法

public:
	virtual bool SetData( IItemList* pList );

};


//单板列表 
class Value_ViewListBoard: public Value_ListBase
{
public:  
    Value_ViewListBoard( vector<TTPBrdInfo> *pVecBoardLst, String strClickItemFunc = IBaseItem::strDefaultFunc ) 
        : Value_ListBase(), m_pVecBoardList( pVecBoardLst ), m_strClickItemFunc( strClickItemFunc ){}
	
    vector<TTPBrdInfo> *m_pVecBoardList; 
    String m_strClickItemFunc;		    	// 条目点击回调函数
public:
	virtual bool SetData( IItemList* pList );
};

class Data_BoardInfo : public IData
{
public:
    Data_BoardInfo( TTPBrdInfo &tBoard ) : IData( "BoardInfo" ), m_tBoardInfo( tBoard ){}
    IData* Clone()
    {
        Data_BoardInfo* pData = new Data_BoardInfo( m_tBoardInfo );
        pData->SetDataKey( GetDataKey() );
        return pData;
    }
	
    TTPBrdInfo m_tBoardInfo;
};

//电视墙单板列表 
class Value_ViewListTvwBoard: public Value_ListBase
{
public:  
    Value_ViewListTvwBoard( vector<THduCfg> *pVecTvwBoardLst, String strClickItemFunc = IBaseItem::strDefaultFunc ) 
        : Value_ListBase(), m_pVecTvwBoardList( pVecTvwBoardLst ), m_strClickItemFunc( strClickItemFunc ){}
	
    vector<THduCfg> *m_pVecTvwBoardList; 
    String m_strClickItemFunc;		    	// 条目点击回调函数
public:
	virtual bool SetData( IItemList* pList );
};

class Data_TvwBoardInfo : public IData
{
public:
    Data_TvwBoardInfo( THduCfg &tTvwBoard ) : IData( "BoardInfo" ), m_tTvwBoardInfo( tTvwBoard ){}
    IData* Clone()
    {
        Data_TvwBoardInfo* pData = new Data_TvwBoardInfo( m_tTvwBoardInfo );
        pData->SetDataKey( GetDataKey() );
        return pData;
    }
	
    THduCfg m_tTvwBoardInfo;
};

//电视墙预案列表 
class Value_ViewListTvwStyle: public Value_ListBase
{
public:  
    Value_ViewListTvwStyle( vector<TTvwStyleInfo> *pVecTvwStyleLst, String strClickItemFunc = IBaseItem::strDefaultFunc ) 
        : Value_ListBase(), m_pVecTvwStyleList( pVecTvwStyleLst ), m_strClickItemFunc( strClickItemFunc ){}
	
    vector<TTvwStyleInfo> *m_pVecTvwStyleList; 
    String m_strClickItemFunc;		    	// 条目点击回调函数
	TListRangeInfo m_tListRangeInfo;
public:
	virtual bool SetData( IItemList* pList );
};

class Data_TvwStyleInfo : public IData
{
public:
    Data_TvwStyleInfo( TTvwStyleInfo &tTvwStyle) : IData( "TvwStyleInfo" ), m_tTvwStyleInfo( tTvwStyle ){}
    IData* Clone()
    {
        Data_TvwStyleInfo* pData = new Data_TvwStyleInfo( m_tTvwStyleInfo );
        pData->SetDataKey( GetDataKey() );
        return pData;
    }
	
    TTvwStyleInfo m_tTvwStyleInfo;
};

class Data_ItemMenu : public IData
{
public:
    Data_ItemMenu( TMenuItem t ) : IData( "MenuItem" ), m_tMenuItem( t ){}
    IData* Clone()
    {
        Data_ItemMenu* pData = new Data_ItemMenu( m_tMenuItem );
        pData->SetDataKey( GetDataKey() );
        return pData;
    }
    TMenuItem  m_tMenuItem;
};

class Value_ItemMenu : public Value_ListBase
{
public:
	Value_ItemMenu( vector<TMenuItem>* pArray, String strClickItemFunc = IBaseItem::strDefaultFunc ,
        vector<String> * pVctSubItem = NULL, String strAlgroithm = IAlgorithm::strHori,
        BOOL32 bDrag = FALSE ): Value_ListBase(  ),
		m_pMenuList( pArray ), 
		m_strAlgroithm(strAlgroithm),
		m_bDrag(bDrag){} 
	
	vector<TMenuItem>* m_pMenuList;
	String m_strClickItemFunc;		    	// 条目点击
    string m_strImgItemType;
	string m_strTxtItemType;
    String m_strAlgroithm;                  //排列算法
	BOOL32 m_bDrag;                         //是否可以拖动
	
	//使用Value_ItemMenu的列表 设置数据 的实现
	virtual bool SetData( IItemList* pList );
	
};


//网管列表 
class Value_ItemNetMng : public Value_ListBase
{
public:
	Value_ItemNetMng( vector<TTPNMServerCfg>* pVecNMServerCfgLst, String strAlgroithm = IAlgorithm::strVert, BOOL32 bDrag = FALSE ) 
		: Value_ListBase(),
		m_pVecNMServerCfgLst( pVecNMServerCfgLst ), 
		m_strAlgroithm(strAlgroithm),
		m_bDrag(bDrag){}   
	
	vector<TTPNMServerCfg> *m_pVecNMServerCfgLst; 
    String m_strAlgroithm;                  //排列算法
	BOOL32 m_bDrag;                         //是否可以拖动
	virtual bool SetData( IItemList* pList );
};

class Data_NetMng : public IData
{
public:
    Data_NetMng( TTPNMServerCfg &tTPNMServerCfg ) : IData( "NetMngInfo" ), m_tTPNMServerCfg( tTPNMServerCfg ){}
    IData* Clone()
    {
        Data_NetMng* pData = new Data_NetMng( m_tTPNMServerCfg );
        pData->SetDataKey( GetDataKey() );
        return pData;
    }
	
    TTPNMServerCfg m_tTPNMServerCfg;
};

//单板升级文件列表 
class Value_ItemBoardUpgrade : public Value_ListBase
{
public:
	Value_ItemBoardUpgrade( std::vector<TUmsToolFile>* pVecUmsToolFileCfgLst, String strAlgroithm = IAlgorithm::strVert, BOOL32 bDrag = FALSE ) 
		: Value_ListBase(),
		m_pVecUmsToolFileLst( pVecUmsToolFileCfgLst ), 
		m_strAlgroithm(strAlgroithm),
		m_bDrag(bDrag){}   
	
	std::vector<TUmsToolFile> *m_pVecUmsToolFileLst; 
    String m_strAlgroithm;                  //排列算法
	BOOL32 m_bDrag;                         //是否可以拖动
	virtual bool SetData( IItemList* pList );
};

class Data_BoardUpgrade : public IData
{
public:
    Data_BoardUpgrade( TUmsToolFile &tUmsToolFile ) : IData( "BoardUpgrade" ), m_tUmsToolFile( tUmsToolFile ){}
    IData* Clone()
    {
        Data_BoardUpgrade* pData = new Data_BoardUpgrade( m_tUmsToolFile );
        pData->SetDataKey( GetDataKey() );
        return pData;
    }
	
    TUmsToolFile m_tUmsToolFile;
};

//录像机列表 
class Value_ItemVTR : public Value_ListBase
{
public:
	Value_ItemVTR( vector<TVcrCfg>* pVecVcrCfgLst, String strAlgroithm = IAlgorithm::strVert, BOOL32 bDrag = FALSE ) 
		: Value_ListBase(),
		m_pVecVcrCfgLst( pVecVcrCfgLst ), 
		m_strAlgroithm(strAlgroithm),
		m_bDrag(bDrag){}   
	
	vector<TVcrCfg> *m_pVecVcrCfgLst; 
    String m_strAlgroithm;                  //排列算法
	BOOL32 m_bDrag;                         //是否可以拖动
	virtual bool SetData( IItemList* pList );
};

class Data_VTR : public IData
{
public:
    Data_VTR( TVcrCfg &tVcrCfg ) : IData( "VTRInfo" ), m_tVcrCfg( tVcrCfg ){}
    IData* Clone()
    {
        Data_VTR* pData = new Data_VTR( m_tVcrCfg );
        pData->SetDataKey( GetDataKey() );
        return pData;
    }
	
    TVcrCfg m_tVcrCfg;
};

class CLayoutAlgorithm_BoardUpgrade : public IAlgorithm
{
public:
	static const int nXSpace;
	static const int nYSpace;
	
	bool Transition( IArgs* pArgs );
};

#endif // !defined(AFX_TOUCHLISTDATAPROPERTY_H__6BEB62C7_9690_4ABB_852B_2CE555E8A57A__INCLUDED_)
