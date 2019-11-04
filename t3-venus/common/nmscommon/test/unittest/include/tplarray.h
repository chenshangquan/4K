/*=======================================================================
模块名      : NmsCommon.lib单元测试
文件名      : tplarray.h
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
#ifndef _TPLARRAY_H
#define _TPLARRAY_H

#include "testcase.h"
#include "extensions\HelperMacros.h"

class CTplArrayCase : public CppUnit::TestCase
{
	CPPUNIT_TEST_SUITE(CTplArrayCase);
		CPPUNIT_TEST_NEW(NewDelete, "New&Delete");
        CPPUNIT_TEST_NEW(SetGetInvalidItem, "SetInvalidItem&GetInvalidItem");
        CPPUNIT_TEST_NEW(Add, "Add - 增加一组");
        // Insert
        CPPUNIT_TEST_NEW(InsertAtHead, "Insert - 从前部插入");
        CPPUNIT_TEST_NEW(InsertAtMid, "Insert - 从中间插入");
        CPPUNIT_TEST_NEW(InsertAtTail, "Insert - 从尾部插入");
#ifndef _DEBUG
        CPPUNIT_TEST_NEW(InsertBeforeHead, "Insert - 插入索引为负");
        CPPUNIT_TEST_NEW(InsertBeyondTail, "Insert - 插入位置超过最大值");
#endif // _DEBUG
        // Delete
        CPPUNIT_TEST_NEW(DeleteFromHead, "Delete - 从头开始删除");
        CPPUNIT_TEST_NEW(DeleteMidNoExceed, "Delete - 从中间开始删除,不越界");
        CPPUNIT_TEST_NEW(DeleteMidExceed, "Delete - 从中间删除，越界");
#ifndef _DEBUG
        CPPUNIT_TEST_NEW(DeleteBeforeHead, "Delete - 删除索引为负");
        CPPUNIT_TEST_NEW(DeleteAfterTail, "Delete - 删除位置越过最大值");
#endif // _DEBUG

        CPPUNIT_TEST_NEW(Clear, "Clear");
        CPPUNIT_TEST_NEW(SetAt, "SetAt");
#ifndef _DEBUG
        CPPUNIT_TEST_NEW(SetAtBeforeHead, "SetAt - 设定索引为负");
        CPPUNIT_TEST_NEW(SetAtAfterTail, "SetAt - 设定索引超过最大值");
        CPPUNIT_TEST_NEW(SetAtNullPtr, "SetAt - 传入的参数为空");
#endif// _DEBUG

        CPPUNIT_TEST_NEW(GetAt, "GetAt");
#ifndef _DEBUG
        CPPUNIT_TEST_NEW(GetAtBeforeHead, "GetAt - 查询索引值为负");
        CPPUNIT_TEST_NEW(GetAtAfterTail, "GetAt - 查询位置超过最大值");
#endif// _DEBUG

        CPPUNIT_TEST_NEW(GetItemPtr, "GetItemPtr");
#ifndef _DEBUG
        CPPUNIT_TEST_NEW(GetPtrBeforeHead, "GetItemPtr - 查询索引值为负");
        CPPUNIT_TEST_NEW(GetPtrAfterTail, "GetItemPtr - 查询索引超过最大值");
#endif // _DEBUG
        CPPUNIT_TEST_NEW(IsEmpty, "IsEmpty");
        CPPUNIT_TEST_NEW(OpEqual, "Operator =");
        CPPUNIT_TEST_NEW(GetMaxSize, "GetMaxSize");
        CPPUNIT_TEST_NEW(GetStep, "GetStep");
        CPPUNIT_TEST_NEW(GetData, "GetData");
    CPPUNIT_TEST_SUITE_END_NEW("TplArray");

public:
	virtual void setUp();
	virtual void tearDown();
public:
    // 分配和删除空间
    void NewDelete();
    // 设定和取得无效的元素
    void SetGetInvalidItem();
    // 添加元素
    void Add();
    // 在开头处添加
    void InsertAtHead();
    // 在中间添加
    void InsertAtMid();
    // 在末尾添加
    void InsertAtTail();
#ifndef _DEBUG
    // 索引值为负的情况
    void InsertBeforeHead();
    // 索引值超出数组大小
    void InsertBeyondTail();
#endif // _DEBUG

    // 从头部删除
    void DeleteFromHead();
    // 从中间删除，不超过上边界
    void DeleteMidNoExceed();
    // 从中间删除，超过上边界
    void DeleteMidExceed();
#ifndef _DEBUG
    // 删除的索引为负值
    void DeleteBeforeHead();
    // 删除的索引超过上边界
    void DeleteAfterTail();
#endif // _DEBUG
    // 清空元素
    void Clear();

    // 在有效区域内设定元素
    void SetAt();
#ifndef _DEBUG
    // 设定元素索引为负值
    void SetAtBeforeHead();
    // 设定元素索引超过上边界
    void SetAtAfterTail();
    // 设定空指针元素
    void SetAtNullPtr();
#endif // _DEBUG

    // 在有效区域内获取元素
    void GetAt();
#ifndef _DEBUG
    // 获取元素的索引为负
    void GetAtBeforeHead();
    // 获取元素的索引超过上边界
    void GetAtAfterTail();
#endif // _DEBUG

    // 在有效区域内得到元素指针
    void GetItemPtr();
#ifndef _DEBUG
    // 获取的元素指针索引为负值
    void GetPtrBeforeHead();
    // 获取的元素指针索引超过上边界
    void GetPtrAfterTail();
#endif // _DEBUG
    // 数组是否为空
    void IsEmpty();
    // =号是否正确交换信息
    void OpEqual();
    // 得到数组的最大空间
    void GetMaxSize();
    // 得到数组递增的步长
    void GetStep();
    // 得到数组的首地址
    void GetData();
};

#endif // _TPLARRAY_H