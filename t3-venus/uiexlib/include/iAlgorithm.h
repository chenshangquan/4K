
#ifndef IALGORITHM_HEAD_H
#define IALGORITHM_HEAD_H
#include "uiexBaseData.h"


class IAlgorithm  
{
public:
	static const String strHori;
	static const String strVert;
	static const String strVertNoSplit;   //垂直算法    无分割线
    static const String strHoriConfLst;
	static const String strNormalItem;
	static const String strAddrGroupItem;
	static const String strTextOnly;
	static const String strDoubleColumn;
	static const String strTPadMainMenu;
	static const String strTextBottom;
	static const String strWifiItem;
    static const String strTvwView;
    static const String strTvwItem;
	static const String strBoardView;
    static const String strBoardItem;
	static const String strCharacter;
	static const String strDefaultAlg;
	static const String strTPadIpList;
	//static const String strNetMngList;
    static const String strMultiColumn;
	static const String strComboxItem;
	static const String strBoardUpgradItem;
    static const String strFileManagerItem;
	static const String strOrderPosView;
	static const String strPreTextBottom;
	IAlgorithm();
	virtual ~IAlgorithm();
	virtual bool Transition( IArgs* pArgs ) = 0;
	virtual bool TransitionByIndex( int nIndex, IArgs* pArgs ){ return false; }
};


//列表排列信息
struct TListRangeInfo
{
    int nMaxRow;     //最大行数
    int nMaxColumn;  //最大列数
    int nFirstLeft;  //初始左偏移
    int nFirstTop;   //初始上偏移
    int nVertSpace;  //上下间距
    int nHoriSpace;  //左右间距
    
    TListRangeInfo()
    { 
        memset( this, 0, sizeof(struct TListRangeInfo) ); 
    }
};

class Data_ListRangeInfo : public IData
{
public:
    Data_ListRangeInfo( TListRangeInfo &tInfo ) : IData( "RangeInfo" ), m_tRangeInfo( tInfo ){}
    IData* Clone()
    {
        Data_ListRangeInfo* pData = new Data_ListRangeInfo( m_tRangeInfo );
        pData->SetDataKey( GetDataKey() );
        return pData;
    }
    
    TListRangeInfo m_tRangeInfo;
};


#endif
