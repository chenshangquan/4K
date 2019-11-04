/*****************************************************************************
模块名      : 列表数据类型及列表数据设置方法的实现
文件名      : listAssist.h
相关文件    : 本工程中使用的所有列表的数据都应统一在此文件定义
文件实现功能: 列表设置数据部分已经整改，UI中只需要定义继承自Value_ListBase的类，
              并实现SetData即可完成列表数据的设置，无需另行增加属性注册和数据设置的模块
作者        : 俞锦锦
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2012/12/17     1.0         俞锦锦      创建
******************************************************************************/
#if !defined(AFX_LISTASSIST_H__01F8A625_C9CB_49C2_BB33_C02D30F86D1A__INCLUDED_)
#define AFX_LISTASSIST_H__01F8A625_C9CB_49C2_BB33_C02D30F86D1A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
 
#include "PropertyHelp.h"
#include "uiDataType.h"

/*---------------------------------------------------------------------
* 类	Data_ItemMenu
* 功    能：
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2012/12/19	v1.0		俞锦锦		创建
----------------------------------------------------------------------*/ 
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
 
/*---------------------------------------------------------------------
* 类	Value_ItemMenu
* 功    能：功能标签页列表属性设置
* 特殊说明：设置用于标签页列表显示时候的value值
* 修改记录：
* 日期			版本		修改人		修改记录
* 2012/12/19	v1.0		俞锦锦		创建
----------------------------------------------------------------------*/
class Value_ItemMenu : public Value_ListBase
{
public:
	Value_ItemMenu( vector<TMenuItem>* pArray, String strClickItemFunc = IBaseItem::strDefaultFunc ,
        vector<String> * pVctSubItem = NULL, String strAlgroithm = IAlgorithm::strHori,
        BOOL32 bDrag = FALSE ): Value_ListBase(  ),
		m_pMenuList( pArray ), 
	//	m_strClickItemFunc( strClickItemFunc ),
    //    m_pVctSubItem( pVctSubItem ), 
		m_strAlgroithm(strAlgroithm),
		m_bDrag(bDrag){} 
 
	vector<TMenuItem>* m_pMenuList;
//	vector<String> * m_pVctSubItem;         //子条目对应的xml中名字
    string m_strImgItemType;
	string m_strTxtItemType;
//	String m_strClickItemFunc;		    	// 条目点击回调函数   
    String m_strAlgroithm;                  //排列算法
	BOOL32 m_bDrag;                         //是否可以拖动
	
	//使用Value_ItemMenu的列表 设置数据 的实现
	virtual bool SetData( IItemList* pList );
 
};

/*---------------------------------------------------------------------
* 类	Value_ItemTPad
* 功    能：TPad列表属性设置
* 特殊说明：设置用于TPad列表显示时候的value值
* 修改记录：
* 日期			版本		修改人		修改记录
* 2012/12/19	v1.0		景洋洋		创建
----------------------------------------------------------------------*/
class Value_ItemTPad : public Value_ListBase
{
public:
	Value_ItemTPad( TTPTPadList* ptTPadList, String strAlgroithm = IAlgorithm::strVert,
        BOOL32 bDrag = FALSE ): Value_ListBase(),
		m_ptTPadList( ptTPadList ), 
		m_strAlgroithm(strAlgroithm),
		m_bDrag(bDrag){}   
	
	TTPTPadList*      m_ptTPadList;
    String m_strAlgroithm;                  //排列算法
	BOOL32 m_bDrag;                         //是否可以拖动
	virtual bool SetData( IItemList* pList );
};


//中控信息中灯光的状态列表
class Value_ItemLight : public Value_ListBase
{
public:
	Value_ItemLight( TCentreSchCfg* ptSchCfg, String strAlgroithm = IAlgorithm::strVert,
        BOOL32 bDrag = FALSE ): Value_ListBase(),
		m_ptSchCfg( ptSchCfg ), 
		m_strAlgroithm(strAlgroithm),
		m_bDrag(bDrag){}   
	
	TCentreSchCfg* m_ptSchCfg;
    String m_strAlgroithm;                  //排列算法
	BOOL32 m_bDrag;                         //是否可以拖动
	virtual bool SetData( IItemList* pList );
};

//诊断测试结果中卡农麦克风列表
class Value_ItemCOMMON : public Value_ListBase
{
public:
	Value_ItemCOMMON( TTPAudioDiagInfo* ptAudioDiagInfo, String strAlgroithm = IAlgorithm::strVert,
        BOOL32 bDrag = FALSE ): Value_ListBase(),
		m_ptAudioDiagInfo( ptAudioDiagInfo ), 
		m_strAlgroithm(strAlgroithm),
		m_bDrag(bDrag){}   
	
	TTPAudioDiagInfo*      m_ptAudioDiagInfo;
    String m_strAlgroithm;                  //排列算法
	BOOL32 m_bDrag;                         //是否可以拖动
	virtual bool SetData( IItemList* pList );
	String CommonToStr( int u );			//将具体的音量值转化为string类型
};


// class CListAssist 
// {
// public: 
//     static bool SetData( IItemList* pList, const IValue* pValue );
// 	static bool SetData( IItemList* pList,  const Value_ListItem* pValue );
//   
// 
// 	CListAssist();
// 	virtual ~CListAssist();
// private:
//     static bool MakeItem ( Args_MakeItem &agrs )  ;
// };
// 	
// private:
// 	CString m_strValTypeFuncMenu;//功能列表
// 	
// };

//路由配置列表 
class Value_ItemRouteCfg : public Value_ListBase
{
public:
	Value_ItemRouteCfg( vector<TRouteCfg>* pVecRouteCfgLst, String strAlgroithm = IAlgorithm::strVert, BOOL32 bDrag = FALSE ) 
		: Value_ListBase(),
		m_pVecRouteCfgLst( pVecRouteCfgLst ), 
		m_strAlgroithm(strAlgroithm),
		m_bDrag(bDrag){}   
	
	vector<TRouteCfg> *m_pVecRouteCfgLst; 
    String m_strAlgroithm;                  //排列算法
	BOOL32 m_bDrag;                         //是否可以拖动
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

class Data_RouteMng : public IData
{
public:
    Data_RouteMng( TRouteCfg &tRouteCfg ) : IData( "RouteMngInfo" ), m_tRouteCfg( tRouteCfg ){}
    IData* Clone()
    {
        Data_RouteMng* pData = new Data_RouteMng( m_tRouteCfg );
        pData->SetDataKey( GetDataKey() );
        return pData;
    }
	
    TRouteCfg m_tRouteCfg;
};

class Value_DisplaySrc : public Value_ListBase
{
public:
	typedef struct tagTDisplaySrcData
	{
		TVgaInfo  m_tDisplaySourceInfo; 
		bool      m_bDefault;
		tagTDisplaySrcData()
		{
			memset(&m_tDisplaySourceInfo,0,sizeof(&m_tDisplaySourceInfo));
			m_bDefault = false;
		}
	}TDisplaySrcData;
public:
	Value_DisplaySrc( vector<TDisplaySrcData> *pVecListData,String strAlgroithm = IAlgorithm::strVert, BOOL32 bDrag = FALSE ) 
		: Value_ListBase(),
		m_pVecListData(pVecListData),
		m_strAlgroithm(strAlgroithm),
		m_bDrag(bDrag){}   
	
	vector<TDisplaySrcData> *m_pVecListData;
    String m_strAlgroithm;                  //排列算法
	BOOL32 m_bDrag;                         //是否可以拖动
	virtual bool SetData( IItemList* pList );
	String CommonToStr( EmVgaType emVideoSourceType );
	IBaseItem *CreatText( s32 nIndex );
};

class Data_DisplaySource : public IData
{
public:
    Data_DisplaySource( Value_DisplaySrc::TDisplaySrcData &tTDisplaySource ) : IData( "VidoeSourceInfo" ), m_tDisplaySource( tTDisplaySource ){}
    IData* Clone()
    {
        Data_DisplaySource* pData = new Data_DisplaySource( m_tDisplaySource );
        pData->SetDataKey( GetDataKey() );
        return pData;
    }
	
	Value_DisplaySrc::TDisplaySrcData m_tDisplaySource;
};

class Value_CurtainList : public Value_ListBase
{
public:
	Value_CurtainList( vector<TCentreCurName> *pVecListData,String strAlgroithm = IAlgorithm::strVert, BOOL32 bDrag = FALSE ) 
		: Value_ListBase(),
		m_pVecListData(pVecListData),
		m_strAlgroithm(strAlgroithm),
		m_bDrag(bDrag){}   
	
	vector<TCentreCurName> *m_pVecListData;
    String m_strAlgroithm;                  //排列算法
	BOOL32 m_bDrag;                         //是否可以拖动
	virtual bool SetData( IItemList* pList );
};

class Data_CurName : public IData
{
public:
    Data_CurName( TCentreCurName &tCurtianName ) : IData( "CurtainInfo" ), m_tCurtainName( tCurtianName ){}
    IData* Clone()
    {
        Data_CurName* pData = new Data_CurName( m_tCurtainName );
        pData->SetDataKey( GetDataKey() );
        return pData;
    }
	
	TCentreCurName m_tCurtainName;
};

#endif // !defined(AFX_LISTASSIST_H__01F8A625_C9CB_49C2_BB33_C02D30F86D1A__INCLUDED_)
