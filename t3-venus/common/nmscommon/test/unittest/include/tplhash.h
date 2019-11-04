/*=======================================================================
模块名      :NmsCommon.lib单元测试
文件名      : tplhash.h
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
#ifndef _TPLHASH_H
#define _TPLHASH_H

#include "testcase.h"
#include "extensions\HelperMacros.h"
#include "nmscommon.h"

class CTplHashCase : public CppUnit::TestCase
{
	CPPUNIT_TEST_SUITE(CTplHashCase);
        CPPUNIT_TEST_NEW(HashTest,          "hash测试");
    CPPUNIT_TEST_SUITE_END_NEW("TplHash");

public:
	virtual void setUp();
	virtual void tearDown();

    void HashTest(void);

private:
    void NoItem(TplHash<u32, s16> &tplHash);
    void OneItem(TplHash<u32, s16> &tplHash);
    void TwoItems(TplHash<u32, s16> &tplHash);
    void ThreeItems(TplHash<u32, s16> &tplHash);
    void FourItems(TplHash<u32, s16> &tplHash);
    void FiveItems(TplHash<u32, s16> &tplHash);

    void FivePart1(TplHash<u32, s16> &tplHash);
    void FivePart2(TplHash<u32, s16> &tplHash);
    void FivePart3(TplHash<u32, s16> &tplHash);
    void FivePart4(TplHash<u32, s16> &tplHash);
    void FivePart5(TplHash<u32, s16> &tplHash);

private:
    u32 m_adwFirst[5];
    s16 m_aswSecond[5];
};

#endif // _TPLHASH_H