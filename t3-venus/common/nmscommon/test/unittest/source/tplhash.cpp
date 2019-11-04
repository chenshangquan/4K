/*=======================================================================
模块名      :NmsCommon.lib单元测试
文件名      : tplhash.cpp
相关文件    :
文件实现功能 :
作者        : 李洪强
版本        : V3.6  Copyright(C) 2003-2005 Suzhou Keda Technology Co.Ltd
                    All rights reserved.
--------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2005/01/26  3.6         李洪强      创建
=======================================================================*/

#include "stdafx.h"
#include "tplhash.h"
#include "nmscommon.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define CHECK(nCount, nDelete)                                              \
{                                                                           \
    s16 swResult = 0;                                                       \
    CPPUNIT_ASSERT( tplHash.GetEntryNum() == nCount );                      \
    for ( s32 nIndex = 0; nIndex < nCount; nIndex ++ )                      \
    {                                                                       \
        CPPUNIT_ASSERT( tplHash.GetAt( m_adwFirst[nIndex], swResult ) );    \
        CPPUNIT_ASSERT( swResult == m_aswSecond[nIndex] );                  \
        CPPUNIT_ASSERT( tplHash.IsExist( m_adwFirst[nIndex] ) );            \
    }                                                                       \
    while ( nIndex < 5 )                                                    \
    {                                                                       \
        CPPUNIT_ASSERT( ! tplHash.IsExist( m_adwFirst[nIndex] ) );          \
        nIndex ++;                                                          \
    }                                                                       \
    CPPUNIT_ASSERT( tplHash.Delete( m_adwFirst[nDelete] ) );                \
    CPPUNIT_ASSERT( tplHash.GetEntryNum() == nCount - 1 );                  \
    for ( nIndex = 0; nIndex < nCount; nIndex ++ )                          \
    {                                                                       \
        if ( nIndex == nDelete )                                            \
        {                                                                   \
            continue;                                                       \
        }                                                                   \
        CPPUNIT_ASSERT( tplHash.IsExist( m_adwFirst[nIndex] ) );            \
    }                                                                       \
}

#ifdef _DEBUG
    static CMemoryState s_cMemBefore;
#endif  //  _DEBUG

//////////////////////////////////////////////////////////////////////////
// CTplHashCase 
void CTplHashCase::setUp()
{
    for ( s32 nIndex = 0; nIndex < 5; nIndex ++ )
    {
        m_adwFirst[nIndex] = (u32)nIndex + 1;
        m_aswSecond[nIndex] = (s16)rand();
    }

#ifdef _DEBUG
    s_cMemBefore.Checkpoint();
#endif  //  _DEBUG
}

void CTplHashCase::tearDown()
{
#ifdef _DEBUG
    CMemoryState cMemAfter, cMemCheck;
    cMemAfter.Checkpoint();
	BOOL32 bLeak = cMemCheck.Difference( s_cMemBefore, cMemAfter );
	if ( bLeak )
	{
		cMemCheck.DumpStatistics();
		s_cMemBefore.DumpAllObjectsSince();
	}
    CPPUNIT_ASSERT( ! bLeak );
#endif // _DEBUG
}

void CTplHashCase::HashTest(void)
{
    TplHash<u32, s16> tplHash(0);

    NoItem(tplHash);
    OneItem(tplHash);
    TwoItems(tplHash);
    ThreeItems(tplHash);
    FourItems(tplHash);
    FiveItems(tplHash);

    tplHash.Clear();
}

void CTplHashCase::NoItem(TplHash<u32, s16> &tplHash)
{
    CPPUNIT_ASSERT( tplHash.GetEntryNum() == 0 );
    CPPUNIT_ASSERT( ! tplHash.IsExist( 0 ) );
    s16 swItem = 0;
    CPPUNIT_ASSERT( ! tplHash.GetAt( 0, swItem ) );
    CPPUNIT_ASSERT( ! tplHash.Delete( 0 ) );
}

void CTplHashCase::OneItem(TplHash<u32, s16> &tplHash)
{
    tplHash.SetAt( m_adwFirst[0], m_aswSecond[0] );
    CHECK(1, 0);
    tplHash.Clear();
}

void CTplHashCase::TwoItems(TplHash<u32, s16> &tplHash)
{
    tplHash.SetAt( m_adwFirst[0], m_aswSecond[0] );
    tplHash.SetAt( m_adwFirst[1], m_aswSecond[1] );
    CHECK(2, 0);
    tplHash.Clear();

    tplHash.SetAt( m_adwFirst[1], m_aswSecond[1] );
    tplHash.SetAt( m_adwFirst[0], m_aswSecond[0] );
    CHECK(2, 1);
    tplHash.Clear();
}

void CTplHashCase::ThreeItems(TplHash<u32, s16> &tplHash)
{
    tplHash.SetAt( m_adwFirst[0], m_aswSecond[0] );
    tplHash.SetAt( m_adwFirst[1], m_aswSecond[1] );
    tplHash.SetAt( m_adwFirst[2], m_aswSecond[2] );
    CHECK(3, 0);
    tplHash.Clear();

    tplHash.SetAt( m_adwFirst[1], m_aswSecond[1] );
    tplHash.SetAt( m_adwFirst[0], m_aswSecond[0] );
    tplHash.SetAt( m_adwFirst[2], m_aswSecond[2] );
    CHECK(3, 1);
    tplHash.Clear();

    tplHash.SetAt( m_adwFirst[2], m_aswSecond[2] );
    tplHash.SetAt( m_adwFirst[0], m_aswSecond[0] );
    tplHash.SetAt( m_adwFirst[1], m_aswSecond[1] );
    CHECK(3, 2);
    tplHash.Clear();

    tplHash.SetAt( m_adwFirst[2], m_aswSecond[2] );
    tplHash.SetAt( m_adwFirst[1], m_aswSecond[1] );
    tplHash.SetAt( m_adwFirst[0], m_aswSecond[0] );
    CHECK(3, 1);
    tplHash.Clear();

    tplHash.SetAt( m_adwFirst[1], m_aswSecond[1] );
    tplHash.SetAt( m_adwFirst[2], m_aswSecond[2] );
    tplHash.SetAt( m_adwFirst[0], m_aswSecond[0] );
    CHECK(3, 0);
    tplHash.Clear();

    tplHash.SetAt( m_adwFirst[0], m_aswSecond[0] );
    tplHash.SetAt( m_adwFirst[2], m_aswSecond[2] );
    tplHash.SetAt( m_adwFirst[1], m_aswSecond[1] );
    CHECK(3, 2);
    tplHash.Clear();
}

void CTplHashCase::FourItems(TplHash<u32, s16> &tplHash)
{
#define THREECASE( nFirst, nSecond, nThird, nFourth, nDelete )      \
{                                                                   \
    tplHash.SetAt( m_adwFirst[nFirst], m_aswSecond[nFirst] );       \
    tplHash.SetAt( m_adwFirst[nSecond], m_aswSecond[nSecond] );     \
    tplHash.SetAt( m_adwFirst[nThird], m_aswSecond[nThird] );       \
    tplHash.SetAt( m_adwFirst[nFourth], m_aswSecond[nFourth] );     \
    CHECK(4, nDelete);                                              \
    tplHash.Clear();                                                \
}

    THREECASE( 0, 1, 2, 3, 0 );
    THREECASE( 0, 1, 3, 2, 1 );
    THREECASE( 0, 2, 1, 3, 2 );
    THREECASE( 0, 2, 3, 1, 3 );
    THREECASE( 0, 3, 1, 2, 0 );
    THREECASE( 0, 3, 2, 1, 1 );
    THREECASE( 1, 0, 2, 3, 2 );
    THREECASE( 1, 0, 3, 2, 3 );
    THREECASE( 1, 2, 0, 3, 0 );
    THREECASE( 1, 2, 3, 0, 1 );
    THREECASE( 1, 3, 0, 2, 2 );
    THREECASE( 1, 3, 2, 0, 3 );
    THREECASE( 2, 0, 1, 3, 0 );
    THREECASE( 2, 0, 3, 1, 1 );
    THREECASE( 2, 1, 0, 3, 2 );
    THREECASE( 2, 1, 3, 0, 3 );
    THREECASE( 2, 3, 0, 1, 0 );
    THREECASE( 2, 3, 1, 0, 1 );
}

void CTplHashCase::FiveItems(TplHash<u32, s16> &tplHash)
{
#define FOURCASE( nFirst, nSecond, nThird, nFourth, nFifth, nDelete )   \
{                                                                       \
    tplHash.SetAt( m_adwFirst[nFirst], m_aswSecond[nFirst] );           \
    tplHash.SetAt( m_adwFirst[nSecond], m_aswSecond[nSecond] );         \
    tplHash.SetAt( m_adwFirst[nThird], m_aswSecond[nThird] );           \
    tplHash.SetAt( m_adwFirst[nFourth], m_aswSecond[nFourth] );         \
    tplHash.SetAt( m_adwFirst[nFifth], m_aswSecond[nFifth] );           \
    CHECK(5, nDelete);                                                  \
    tplHash.Clear();                                                    \
}

    FivePart1(tplHash);
    FivePart2(tplHash);
    FivePart3(tplHash);
    FivePart4(tplHash);
    FivePart5(tplHash);
}

void CTplHashCase::FivePart1(TplHash<u32, s16> &tplHash)
{
    FOURCASE( 0, 1, 2, 3, 4, 0 );
    FOURCASE( 0, 1, 2, 4, 3, 1 );
    FOURCASE( 0, 1, 3, 2, 4, 2 );
    FOURCASE( 0, 1, 3, 4, 2, 3 );
    FOURCASE( 0, 1, 4, 2, 3, 4 );
    FOURCASE( 0, 1, 4, 3, 2, 0 );
    FOURCASE( 0, 2, 1, 3, 4, 1 );
    FOURCASE( 0, 2, 1, 4, 3, 2 );
    FOURCASE( 0, 2, 3, 1, 4, 3 );
    FOURCASE( 0, 2, 3, 4, 1, 4 );
    FOURCASE( 0, 2, 4, 1, 3, 0 );
    FOURCASE( 0, 2, 4, 3, 1, 1 );
    FOURCASE( 0, 3, 1, 2, 4, 2 );
    FOURCASE( 0, 3, 1, 4, 2, 3 );
    FOURCASE( 0, 3, 2, 1, 4, 4 );
    FOURCASE( 0, 3, 2, 4, 1, 0 );
    FOURCASE( 0, 3, 4, 1, 2, 1 );
    FOURCASE( 0, 3, 4, 2, 1, 2 );
    FOURCASE( 0, 4, 1, 2, 3, 3 );
    FOURCASE( 0, 4, 1, 3, 2, 4 );
    FOURCASE( 0, 4, 2, 1, 3, 0 );
    FOURCASE( 0, 4, 2, 3, 1, 1 );
    FOURCASE( 0, 4, 3, 1, 2, 2 );
    FOURCASE( 0, 4, 3, 2, 1, 3 );
}

void CTplHashCase::FivePart2(TplHash<u32, s16> &tplHash)
{
    FOURCASE( 1, 0, 2, 3, 4, 0 );
    FOURCASE( 1, 0, 2, 4, 3, 1 );
    FOURCASE( 1, 0, 3, 2, 4, 2 );
    FOURCASE( 1, 0, 3, 4, 2, 3 );
    FOURCASE( 1, 0, 4, 2, 3, 4 );
    FOURCASE( 1, 0, 4, 3, 2, 0 );
    FOURCASE( 1, 2, 0, 3, 4, 1 );
    FOURCASE( 1, 2, 0, 4, 3, 2 );
    FOURCASE( 1, 2, 3, 0, 4, 3 );
    FOURCASE( 1, 2, 3, 4, 0, 4 );
    FOURCASE( 1, 2, 4, 0, 3, 0 );
    FOURCASE( 1, 2, 4, 3, 0, 1 );
    FOURCASE( 1, 3, 0, 2, 4, 2 );
    FOURCASE( 1, 3, 0, 4, 2, 3 );
    FOURCASE( 1, 3, 2, 0, 4, 4 );
    FOURCASE( 1, 3, 2, 4, 0, 0 );
    FOURCASE( 1, 3, 4, 0, 2, 1 );
    FOURCASE( 1, 3, 4, 2, 0, 2 );
    FOURCASE( 1, 4, 0, 2, 3, 3 );
    FOURCASE( 1, 4, 0, 3, 2, 4 );
    FOURCASE( 1, 4, 2, 0, 3, 0 );
    FOURCASE( 1, 4, 2, 3, 0, 1 );
    FOURCASE( 1, 4, 3, 0, 2, 2 );
    FOURCASE( 1, 4, 3, 2, 0, 3 );
}

void CTplHashCase::FivePart3(TplHash<u32, s16> &tplHash)
{
    FOURCASE( 2, 0, 1, 3, 4, 0 );
    FOURCASE( 2, 0, 1, 4, 3, 1 );
    FOURCASE( 2, 0, 3, 1, 4, 2 );
    FOURCASE( 2, 0, 3, 4, 1, 3 );
    FOURCASE( 2, 0, 4, 1, 3, 4 );
    FOURCASE( 2, 0, 4, 3, 1, 0 );
    FOURCASE( 2, 1, 0, 3, 4, 1 );
    FOURCASE( 2, 1, 0, 4, 3, 2 );
    FOURCASE( 2, 1, 3, 0, 4, 3 );
    FOURCASE( 2, 1, 3, 4, 0, 4 );
    FOURCASE( 2, 1, 4, 0, 3, 0 );
    FOURCASE( 2, 1, 4, 3, 0, 1 );
    FOURCASE( 2, 3, 0, 1, 4, 2 );
    FOURCASE( 2, 3, 0, 4, 1, 3 );
    FOURCASE( 2, 3, 1, 0, 4, 4 );
    FOURCASE( 2, 3, 1, 4, 0, 0 );
    FOURCASE( 2, 3, 4, 0, 1, 1 );
    FOURCASE( 2, 3, 4, 1, 0, 2 );
    FOURCASE( 2, 4, 0, 1, 3, 3 );
    FOURCASE( 2, 4, 0, 3, 1, 4 );
    FOURCASE( 2, 4, 1, 0, 3, 0 );
    FOURCASE( 2, 4, 1, 3, 0, 1 );
    FOURCASE( 2, 4, 3, 0, 1, 2 );
    FOURCASE( 2, 4, 3, 1, 0, 3 );
}

void CTplHashCase::FivePart4(TplHash<u32, s16> &tplHash)
{
    FOURCASE( 3, 0, 1, 2, 4, 0 );
    FOURCASE( 3, 0, 1, 4, 2, 1 );
    FOURCASE( 3, 0, 2, 1, 4, 2 );
    FOURCASE( 3, 0, 2, 4, 1, 3 );
    FOURCASE( 3, 0, 4, 1, 2, 4 );
    FOURCASE( 3, 0, 4, 2, 1, 0 );
    FOURCASE( 3, 1, 0, 2, 4, 1 );
    FOURCASE( 3, 1, 0, 4, 2, 2 );
    FOURCASE( 3, 1, 2, 0, 4, 3 );
    FOURCASE( 3, 1, 2, 4, 0, 4 );
    FOURCASE( 3, 1, 4, 0, 2, 0 );
    FOURCASE( 3, 1, 4, 2, 0, 1 );
    FOURCASE( 3, 2, 0, 1, 4, 2 );
    FOURCASE( 3, 2, 0, 4, 1, 3 );
    FOURCASE( 3, 2, 1, 0, 4, 4 );
    FOURCASE( 3, 2, 1, 4, 0, 0 );
    FOURCASE( 3, 2, 4, 0, 1, 1 );
    FOURCASE( 3, 2, 4, 1, 0, 2 );
    FOURCASE( 3, 4, 0, 1, 2, 3 );
    FOURCASE( 3, 4, 0, 2, 1, 4 );
    FOURCASE( 3, 4, 1, 0, 2, 0 );
    FOURCASE( 3, 4, 1, 2, 0, 1 );
    FOURCASE( 3, 4, 2, 0, 1, 2 );
    FOURCASE( 3, 4, 2, 1, 0, 3 );
}

void CTplHashCase::FivePart5(TplHash<u32, s16> &tplHash)
{
    FOURCASE( 4, 0, 1, 2, 3, 0 );
    FOURCASE( 4, 0, 1, 3, 2, 1 );
    FOURCASE( 4, 0, 2, 1, 3, 2 );
    FOURCASE( 4, 0, 2, 3, 1, 3 );
    FOURCASE( 4, 0, 3, 1, 2, 4 );
    FOURCASE( 4, 0, 3, 2, 1, 0 );
    FOURCASE( 4, 1, 0, 2, 3, 1 );
    FOURCASE( 4, 1, 0, 3, 2, 2 );
    FOURCASE( 4, 1, 2, 0, 3, 3 );
    FOURCASE( 4, 1, 2, 3, 0, 4 );
    FOURCASE( 4, 1, 3, 0, 2, 0 );
    FOURCASE( 4, 1, 3, 2, 0, 1 );
    FOURCASE( 4, 2, 0, 1, 3, 2 );
    FOURCASE( 4, 2, 0, 3, 1, 3 );
    FOURCASE( 4, 2, 1, 0, 3, 4 );
    FOURCASE( 4, 2, 1, 3, 0, 0 );
    FOURCASE( 4, 2, 3, 0, 1, 1 );
    FOURCASE( 4, 2, 3, 1, 0, 2 );
    FOURCASE( 4, 3, 0, 1, 2, 3 );
    FOURCASE( 4, 3, 0, 2, 1, 4 );
    FOURCASE( 4, 3, 1, 0, 2, 0 );
    FOURCASE( 4, 3, 1, 2, 0, 1 );
    FOURCASE( 4, 3, 2, 0, 1, 2 );
    FOURCASE( 4, 3, 2, 1, 0, 3 );
}