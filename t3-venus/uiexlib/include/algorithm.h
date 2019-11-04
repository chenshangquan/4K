
#ifndef ALGORITHM_HEAD_H
#define ALGORITHM_HEAD_H
#include "uiexBaseData.h"
#include "iAlgorithm.h" 


class CAlgorithmFactory
{
public:
	static IAlgorithm* GetAlgorithm( String alg );
	static bool AddAlgorithm( String strName, IAlgorithm* pAlgorithm );
protected:
	typedef map< String, IAlgorithm* > AlgorithmMap;
	static AlgorithmMap m_mapAlgorithms;
};

#ifndef REG_ALGORITHM
#define REG_ALGORITHM( name, AlgClass ) \
CAlgorithmFactory::AddAlgorithm( name, new AlgClass );
#endif


typedef IItem< IBaseItem, int > IItemList;

class Args_ItemList : public IArgs
{
	//typedef IItem< IBaseItem, int > IItemList;
public:
	Args_ItemList( IItemList* pList ) : IArgs( "ItemList" ) , m_pList( pList ) {}
	
	IItemList* m_pList;
};

class CLayoutAlgorithm_Vert : public IAlgorithm
{
public:
	static /*const*/ int nXSpace;
	static const int nYSpace;

	bool Transition( IArgs* pArgs );
	bool TransitionByIndex( int nIndex, IArgs* pArgs );
};

class CLayoutAlgorithm_VertNoSplit : public IAlgorithm
{
public:
	static const int nXSpace;
	static const int nYSpace;
	
	bool Transition( IArgs* pArgs );
	bool TransitionByIndex( int nIndex, IArgs* pArgs );
};

class CLayoutAlgorithm_Hori : public IAlgorithm
{
public:
	static const int nXSpace;
	static const int nYSpace;

	bool Transition( IArgs* pArgs );
};

class CLayoutAlgorithm_NormalItem : public IAlgorithm
{
public:
	bool Transition( IArgs* pArgs );
	bool TransitionByIndex( int nIndex, IArgs* pArgs );
};

class CLayoutAlgorithm_HoriConfLst : public IAlgorithm
{
public:
    bool Transition( IArgs* pArgs );
};

class CLayoutAlgorithm_AddrGroupItem : public IAlgorithm
{
public:
	bool Transition( IArgs* pArgs );
};

class CLayoutAlgorithm_TextOnly : public IAlgorithm
{
public:
    bool Transition( IArgs* pArgs );
};

class CLayoutAlgorithm_DoubleColumn : public IAlgorithm
{
public:
    bool Transition( IArgs* pArgs );
};

//TPad主界面列表
class CLayoutAlgorithm_TPadMainMenu : public IAlgorithm
{
public:
    bool Transition( IArgs* pArgs );
};

//文字位于底部
class CLayoutAlgorithm_TextBottom : public IAlgorithm
{
public:
    bool Transition( IArgs* pArgs );
};

//Wifi列表条目
class CLayoutAlgorithm_WifiItem : public IAlgorithm
{
public:
    bool Transition( IArgs* pArgs );
};

//单板列表
class CLayoutAlgorithm_BoardView : public IAlgorithm
{
public:
    bool Transition( IArgs* pArgs );
};

//单个单板
class CLayoutAlgorithm_BoardItem : public IAlgorithm
{
public:
    bool Transition( IArgs* pArgs );
};

class CSortAlgorithm_Char : public IAlgorithm
{
public:
	bool Transition( IArgs* pArgs );
};

//TPad列表
class CLayoutAlgorithm_TPadIPList : public IAlgorithm
{
public:
    bool Transition( IArgs* pArgs );
};

//网管列表
class CLayoutAlgorithm_NetMngList : public IAlgorithm
{
public:
    bool Transition( IArgs* pArgs );
};

/*---------------------------------------------------------------------
* 类	CLayoutAlgorithm_MultiColumn
* 功    能：多列通用算法
* 特殊说明：用于网管列表显示
* 修改记录：
* 日期			版本		修改人		修改记录
* 2013/1/16   	v1.0		肖楚然		  创建
----------------------------------------------------------------------*/
class CLayoutAlgorithm_MultiColumn : public IAlgorithm
{
public:
    bool Transition( IArgs* pArgs );
};

//Combox算法
class CLayoutAlgorithm_ComboxItem : public IAlgorithm
{
public:
	bool Transition( IArgs* pArgs );
};

//文件管理列表
class CLayoutAlgorithm_FileManagerItem : public IAlgorithm
{
public:
    bool Transition( IArgs* pArgs );
};

//预置位列表
class CLayoutAlgorithm_PreTextBottom :  public IAlgorithm
{
public:
    bool Transition( IArgs* pArgs );
};




#endif
