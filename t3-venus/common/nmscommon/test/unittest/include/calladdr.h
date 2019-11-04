/*=======================================================================
模块名      :NmsCommon.lib单元测试
文件名      : calladdr.h
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
#ifndef _CALLADDR_H
#define _CALLADDR_H
    
#include "testcase.h"
#include "extensions\HelperMacros.h"

class CCallAddrCase : public CppUnit::TestCase
{
	CPPUNIT_TEST_SUITE(CCallAddrCase);
		CPPUNIT_TEST_NEW(NewDelete,         "New&Delete");
		CPPUNIT_TEST_NEW(IsValidIplpStr,    "IsValidIpV4 - 字串型");
		CPPUNIT_TEST_NEW(IsValidIpCString,  "IsValidIpV4 - CString型");
		CPPUNIT_TEST_NEW(IsValidIpDword,    "IsValidIpV4 - DWORD型");
		CPPUNIT_TEST_NEW(GetLastErrorInfo,  "GetLastErrorInfo");
		CPPUNIT_TEST_NEW(GetIpStr,          "GetIpStr");
		CPPUNIT_TEST_NEW(GetCallStrType,    "GetCallStrType");
		CPPUNIT_TEST_NEW(IsValidIpMask,     "IsValidIpMask ");
		CPPUNIT_TEST_NEW(IsValidIpMaskStr,  "IsValidIpMask - 字串型");
        CPPUNIT_TEST_NEW(GetLocalIpAddr,    "获取本机所有IP地址");
    CPPUNIT_TEST_SUITE_END_NEW("CCallAddr");

public:
	void setUp();
	void tearDown();
public:
    // 分配和删除空间
    void NewDelete();
    // 字串型IP地址的有效性判断
    void IsValidIplpStr();
    // CString型IP地址的有效性判断
    void IsValidIpCString();
    // 双字节型IP地址的有效性判断
    void IsValidIpDword();
    // 返回出错信息
    void GetLastErrorInfo();
    // 双字节到字串型地址的转化
    void GetIpStr();
    // 得到字串是何种呼叫类型
    void GetCallStrType();
	//是否是一个合法的IP掩码
	void IsValidIpMask();
	//是否是一个合法的Ip掩码，字符串型
	void IsValidIpMaskStr();
    //  获取本机所有IP地址
    void GetLocalIpAddr(void);
};

#endif