/*=======================================================================
模块名      :NmsCommon.lib单元测试
文件名      : api.h
相关文件    :
文件实现功能 :
作者        : 李洪强
版本        : V3.6  Copyright(C) 2003-2005 Suzhou Keda Technology Co.Ltd
                    All rights reserved.
--------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2005/01/25  3.6         李洪强      创建
=======================================================================*/
#ifndef _API_H
#define _API_H

#include "testcase.h"
#include "extensions\HelperMacros.h"

class CAPICase : public CppUnit::TestCase
{
	CPPUNIT_TEST_SUITE(CAPICase);
		CPPUNIT_TEST_NEW(GetConfBitrate, "GetConfBitrate");
		CPPUNIT_TEST_NEW(GetModuleFullPath, "GetModuleFullPath");
		CPPUNIT_TEST_NEW(nmscommonver, "nmscommonver");
		CPPUNIT_TEST_NEW(ModuleRegToOsp, "ModuleRegToOsp");
        CPPUNIT_TEST_NEW(Encrypt,           "加解密");
    CPPUNIT_TEST_SUITE_END_NEW("Global API");
public:
	void setUp();
	void tearDown();
public:
    // 得到会议码率
    void GetConfBitrate();
    // 得到模块全路径
    void GetModuleFullPath();
    // 得到库的版本号
    void nmscommonver();
    // 向osp注册模块
    void ModuleRegToOsp();
    //加解密
    void Encrypt(void);
};

#endif // _API_H
