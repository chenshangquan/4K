/*=======================================================================
模块名      :NmsCommon.lib单元测试
文件名      : tplarray.cpp
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
#include "stdafx.h"
#include "tplarray.h"
#include "nmscommon.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TEST_SIZE              49

#define ADD_INIT_ITEM                                   \
    TplArray<u32> tplArray;                             \
    for(s32 nIndex = 0; nIndex < TEST_SIZE; nIndex++)   \
    {                                                   \
        u32 dwItem = nIndex + 10;                       \
        tplArray.Add(&dwItem);                          \
    }

//////////////////////////////////////////////////////////////////////////
// CTplArrayCase

void CTplArrayCase::setUp()
{
}

void CTplArrayCase::tearDown()
{
}

/*========================================================================
函 数 名：NewDelete
功    能：测试分配和删除空间
参    数：
返 回 值：
--------------------------------------------------------------------------
修改记录：
日		期	版本	修改人	修改内容
2005/01/25	3.6		李洪强	创建
========================================================================*/
void CTplArrayCase::NewDelete()
{
#ifdef _DEBUG
	CMemoryState cStateInit, cStateEnd, cStateDiff;    
	cStateInit.Checkpoint();

	TplArray<u32> *ptplArray = new TplArray<u32>;

    for(s32 nIndex = 0; nIndex < TEST_SIZE; nIndex++)
    {
        u32 dwValue = nIndex + 10;
        ptplArray->Add(&dwValue);
    }

	DEL_PTR(ptplArray);

	cStateEnd.Checkpoint();
	BOOL bLeak = cStateDiff.Difference(cStateInit, cStateEnd);
	if (bLeak)
	{
		cStateDiff.DumpStatistics();
		cStateInit.DumpAllObjectsSince();
	}

    CPPUNIT_ASSERT(!bLeak); 
#endif
}

/*========================================================================
函 数 名：SetGetInvalidItem
功    能：设定和取得无效的元素
参    数：
返 回 值：
--------------------------------------------------------------------------
修改记录：
日		期	版本	修改人	修改内容
2005/01/25	3.6		李洪强	创建
========================================================================*/
void CTplArrayCase::SetGetInvalidItem()
{
    TplArray<u32> tplArray;
    u32 dwInvalid = 0xFFFF00FF;
    TplArray<u32>::SetInvalidItem(dwInvalid);
    u32 dwNewValue = TplArray<u32>::GetInvalidItem();
    CPPUNIT_ASSERT(dwInvalid == dwNewValue);
}

/*========================================================================
函 数 名：Add
功    能：添加元素
参    数：
返 回 值：
--------------------------------------------------------------------------
修改记录：
日		期	版本	修改人	修改内容
2005/01/25	3.6		李洪强	创建
========================================================================*/
void CTplArrayCase::Add()
{
    TplArray<u32> tplArray;

    for(s32 nIndex = 0; nIndex < TEST_SIZE; nIndex++)
    {
        u32 dwValue = nIndex + 10;
        s32 nRet = tplArray.Add(&dwValue);
        CPPUNIT_ASSERT(nRet == nIndex);

        s32 nSize = tplArray.Size();
        CPPUNIT_ASSERT(nSize == nIndex + 1);
    }

    for(nIndex = 0; nIndex < TEST_SIZE; nIndex++)
    {
        u32 dwValue = tplArray[nIndex];
        CPPUNIT_ASSERT(dwValue == nIndex + 10);
    }
}

/*========================================================================
函 数 名：InsertAtHead
功    能：在开头处添加
参    数：
返 回 值：
--------------------------------------------------------------------------
修改记录：
日		期	版本	修改人	修改内容
2005/01/25	3.6		李洪强	创建
========================================================================*/
void CTplArrayCase::InsertAtHead()
{
    TplArray<u32> tplArray;

    // 随机的一个表
    u32 adwItemTab[] = { 3, 8, 1, 20, 13, 5, 67, 308 };
    s32 nTabSize = sizeof(adwItemTab) / sizeof(u32);

    // 一次插入一个, 插在前面的情况
    for(s32 nIndex = 0; nIndex < TEST_SIZE; nIndex++)
    {
        s32 nRet = tplArray.Insert(0, adwItemTab, nTabSize);
        CPPUNIT_ASSERT(tplArray.Size() == (nIndex + 1) * nTabSize);
        CPPUNIT_ASSERT(nRet == 0);
    }

    for(nIndex = 0; nIndex < TEST_SIZE; nIndex++)
    {
        for(s32 nItemIdx = 0; nItemIdx < nTabSize; nItemIdx++)
        {
            u32 dwItem = adwItemTab[nItemIdx];
            s32 nPos = nIndex * nTabSize + nItemIdx;

            CPPUNIT_ASSERT(tplArray[nPos] == dwItem);
        }
    }
}

/*========================================================================
函 数 名：InsertAtMid
功    能：在中间添加
参    数：
返 回 值：
--------------------------------------------------------------------------
修改记录：
日		期	版本	修改人	修改内容
2005/01/25	3.6		李洪强	创建
========================================================================*/
void CTplArrayCase::InsertAtMid()
{
    ADD_INIT_ITEM

    // 随机的一个表
    u32 adwItemTab[] = { 3, 8, 1, 20, 13, 5, 67, 308 };
    s32 nTabSize = sizeof(adwItemTab) / sizeof(u32);

    s32 nInsPos = TEST_SIZE / 2;
    s32 nRet = tplArray.Insert(nInsPos, adwItemTab, nTabSize);
    CPPUNIT_ASSERT(nRet == nInsPos);

    // 检查前面的元素
    for(nIndex = 0; nIndex < nInsPos; nIndex++)
    {
        CPPUNIT_ASSERT(tplArray[nIndex] == nIndex + 10);
    }
    // 检查插入的元素
    for(s32 nInsIdx = 0; nIndex < nInsPos + nTabSize; nIndex++, nInsIdx++)
    {
        CPPUNIT_ASSERT(tplArray[nIndex] == adwItemTab[nInsIdx]);
    }
    // 检查后移的元素
    for(; nIndex < TEST_SIZE + nTabSize; nIndex++)
    {
        CPPUNIT_ASSERT(tplArray[nIndex] == nIndex - nTabSize + 10);
    }
}

/*========================================================================
函 数 名：InsertAtTail
功    能：在末尾添加
参    数：
返 回 值：
--------------------------------------------------------------------------
修改记录：
日		期	版本	修改人	修改内容
2005/01/25	3.6		李洪强	创建
========================================================================*/
void CTplArrayCase::InsertAtTail()
{
    ADD_INIT_ITEM

    // 随机的一个表
    u32 adwItemTab[] = { 3, 8, 1, 20, 13, 5, 67, 308 };
    s32 nTabSize = sizeof(adwItemTab) / sizeof(u32);

    s32 nRet = tplArray.Insert(tplArray.Size(), adwItemTab, nTabSize);
    CPPUNIT_ASSERT(nRet == TEST_SIZE);

    // 检查前面的元素
    for(nIndex = 0; nIndex < TEST_SIZE; nIndex++)
    {
        CPPUNIT_ASSERT(tplArray[nIndex] == nIndex + 10);
    }
    // 检查插入的元素
    for(s32 nItemIdx = 0; nItemIdx <nTabSize; nIndex++, nItemIdx++)
    {
        CPPUNIT_ASSERT(tplArray[nIndex] == adwItemTab[nItemIdx]);
    }
}

#ifndef _DEBUG
/*========================================================================
函 数 名：InsertBeforeHead
功    能：索引值为负的情况
参    数：
返 回 值：
--------------------------------------------------------------------------
修改记录：
日		期	版本	修改人	修改内容
2005/01/25	3.6		李洪强	创建
========================================================================*/
void CTplArrayCase::InsertBeforeHead()
{
    TplArray<u32> tplArray;

    u32 adwItemTab[] = { 3, 8, 1, 20, 13, 5, 67, 308 };
    s32 nTabSize = sizeof(adwItemTab) / sizeof(u32);

    s32 nRet = tplArray.Insert(-1, adwItemTab, nTabSize);
    CPPUNIT_ASSERT(nRet < 0);
}

/*========================================================================
函 数 名：InsertBeyondTail
功    能：索引值超出数组大小
参    数：
返 回 值：
--------------------------------------------------------------------------
修改记录：
日		期	版本	修改人	修改内容
2005/01/25	3.6		李洪强	创建
========================================================================*/
void CTplArrayCase::InsertBeyondTail()
{
    ADD_INIT_ITEM

    u32 adwItemTab[] = { 3, 8, 1, 20, 13, 5, 67, 308 };
    s32 nTabSize = sizeof(adwItemTab) / sizeof(u32);

    s32 nRet = tplArray.Insert(tplArray.Size() + 1, adwItemTab, nTabSize);
    CPPUNIT_ASSERT(nRet < 0);
}
#endif // _DEBUG

/*========================================================================
函 数 名：DeleteFromHead
功    能：从头部删除
参    数：
返 回 值：
--------------------------------------------------------------------------
修改记录：
日		期	版本	修改人	修改内容
2005/01/25	3.6		李洪强	创建
========================================================================*/
void CTplArrayCase::DeleteFromHead()
{
    ADD_INIT_ITEM

#define DEL_SIZE                13
    s32 nRet = tplArray.Delete(0, DEL_SIZE);
    CPPUNIT_ASSERT(nRet == DEL_SIZE);

    CPPUNIT_ASSERT(tplArray.Size() == TEST_SIZE - DEL_SIZE);

    for(nIndex = 0; nIndex < TEST_SIZE - DEL_SIZE; nIndex++)
    {
        CPPUNIT_ASSERT(tplArray[nIndex] == nIndex + DEL_SIZE + 10);
    }

#undef DEL_SIZE
}

/*========================================================================
函 数 名：DeleteMidNoExceed
功    能：从中间删除，不超过上边界
参    数：
返 回 值：
--------------------------------------------------------------------------
修改记录：
日		期	版本	修改人	修改内容
2005/01/25	3.6		李洪强	创建
========================================================================*/
void CTplArrayCase::DeleteMidNoExceed()
{
    ADD_INIT_ITEM

    s32 nDelPos = TEST_SIZE / 2;
#define DEL_SIZE                13
    s32 nRet = tplArray.Delete(nDelPos, DEL_SIZE);
    CPPUNIT_ASSERT(nRet == DEL_SIZE);

    CPPUNIT_ASSERT(tplArray.Size() == TEST_SIZE - DEL_SIZE);

    // 前面的元素没有改变
    for(nIndex = 0; nIndex < nDelPos; nIndex++)
    {
        CPPUNIT_ASSERT(tplArray[nIndex] == nIndex + 10);
    }
    // 检查后面的元素
    for(; nIndex < TEST_SIZE - DEL_SIZE; nIndex++)
    {
        CPPUNIT_ASSERT(tplArray[nIndex] == nIndex + DEL_SIZE + 10);
    }

#undef DEL_SIZE
}

/*========================================================================
函 数 名：DeleteMidExceed
功    能：从中间删除，超过上边界
参    数：
返 回 值：
--------------------------------------------------------------------------
修改记录：
日		期	版本	修改人	修改内容
2005/01/25	3.6		李洪强	创建
========================================================================*/
void CTplArrayCase::DeleteMidExceed()
{
    ADD_INIT_ITEM

    s32 nDelPos = TEST_SIZE / 2;
#define DEL_SIZE                50
    s32 nRet = tplArray.Delete(nDelPos, DEL_SIZE);

    CPPUNIT_ASSERT(nRet == TEST_SIZE - nDelPos);

    CPPUNIT_ASSERT(tplArray.Size() == nDelPos);

    // 前面的元素没有改变
    for(nIndex = 0; nIndex < nDelPos; nIndex++)
    {
        CPPUNIT_ASSERT(tplArray[nIndex] == nIndex + 10);
    }
#undef DEL_SIZE
}

#ifndef _DEBUG
/*========================================================================
函 数 名：DeleteBeforeHead
功    能：删除的索引为负值
参    数：
返 回 值：
--------------------------------------------------------------------------
修改记录：
日		期	版本	修改人	修改内容
2005/01/25	3.6		李洪强	创建
========================================================================*/
void CTplArrayCase::DeleteBeforeHead()
{
    ADD_INIT_ITEM

    s32 nRet = tplArray.Delete(-1, 3);
    CPPUNIT_ASSERT(nRet < 0);
}

/*========================================================================
函 数 名：DeleteAfterTail
功    能：删除的索引超过上边界
参    数：
返 回 值：
--------------------------------------------------------------------------
修改记录：
日		期	版本	修改人	修改内容
2005/01/25	3.6		李洪强	创建
========================================================================*/
void CTplArrayCase::DeleteAfterTail()
{
    ADD_INIT_ITEM

    s32 nRet = tplArray.Delete(TEST_SIZE, 3);
    CPPUNIT_ASSERT(nRet < 0);
}
#endif // _DEBUG

/*========================================================================
函 数 名：Clear
功    能：清空元素
参    数：
返 回 值：
--------------------------------------------------------------------------
修改记录：
日		期	版本	修改人	修改内容
2005/01/25	3.6		李洪强	创建
========================================================================*/
void CTplArrayCase::Clear()
{
    ADD_INIT_ITEM

    tplArray.Clear();
    
    CPPUNIT_ASSERT(tplArray.Size() == 0);
    CPPUNIT_ASSERT(tplArray.GetMaxSize() == 0);
#ifndef _DEBUG
    CPPUNIT_ASSERT(tplArray.GetItemPtr(0) == NULL);
#endif // _DEBUG
}

/*========================================================================
函 数 名：SetAt
功    能：在有效区域内设定元素
参    数：
返 回 值：
--------------------------------------------------------------------------
修改记录：
日		期	版本	修改人	修改内容
2005/01/25	3.6		李洪强	创建
========================================================================*/
void CTplArrayCase::SetAt()
{
    ADD_INIT_ITEM

    u32 adwItemTab[] = { 3, 8, 1, 20, 13, 5, 67, 308 };
    s32 nTabSize = sizeof(adwItemTab) / sizeof(u32);

    s32 nStartPos = TEST_SIZE / 2;
    for(nIndex = 0; nIndex < nTabSize; nIndex++)
    {
        s32 nSetPos = nStartPos + nIndex;
        BOOL bRet = tplArray.SetAt(nSetPos, adwItemTab + nIndex);
        CPPUNIT_ASSERT(bRet == TRUE);
        CPPUNIT_ASSERT(tplArray[nSetPos] == adwItemTab[nIndex]);
    }
}

#ifndef _DEBUG
/*========================================================================
函 数 名：SetAtBeforeHead
功    能：设定元素索引为负值
参    数：
返 回 值：
--------------------------------------------------------------------------
修改记录：
日		期	版本	修改人	修改内容
2005/01/25	3.6		李洪强	创建
========================================================================*/
void CTplArrayCase::SetAtBeforeHead()
{
    ADD_INIT_ITEM

    u32 dwItem = 33;
    BOOL bRet = tplArray.SetAt(-1, &dwItem);
    CPPUNIT_ASSERT(bRet == FALSE);
}

/*========================================================================
函 数 名：SetAtAfterTail
功    能：设定元素索引超过上边界
参    数：
返 回 值：
--------------------------------------------------------------------------
修改记录：
日		期	版本	修改人	修改内容
2005/01/25	3.6		李洪强	创建
========================================================================*/
void CTplArrayCase::SetAtAfterTail()
{
    ADD_INIT_ITEM

    u32 dwItem = 33;
    BOOL bRet = tplArray.SetAt(TEST_SIZE, &dwItem);
    CPPUNIT_ASSERT(bRet == FALSE);
}

/*========================================================================
函 数 名：SetAtNullPtr
功    能：设定空指针元素
参    数：
返 回 值：
--------------------------------------------------------------------------
修改记录：
日		期	版本	修改人	修改内容
2005/01/25	3.6		李洪强	创建
========================================================================*/
void CTplArrayCase::SetAtNullPtr()
{
    ADD_INIT_ITEM

    BOOL bRet = tplArray.SetAt(3, NULL);
    CPPUNIT_ASSERT(bRet == FALSE);
}
#endif// _DEBUG

/*========================================================================
函 数 名：GetAt
功    能：在有效区域内获取元素
参    数：
返 回 值：
--------------------------------------------------------------------------
修改记录：
日		期	版本	修改人	修改内容
2005/01/25	3.6		李洪强	创建
========================================================================*/
void CTplArrayCase::GetAt()
{
    ADD_INIT_ITEM

    for(nIndex = 0; nIndex < TEST_SIZE; nIndex++)
    {
        u32 dwItem = tplArray.GetAt(nIndex);
        CPPUNIT_ASSERT(dwItem == nIndex + 10);
    }
}

#ifndef _DEBUG
/*========================================================================
函 数 名：GetAtBeforeHead
功    能：获取元素的索引为负
参    数：
返 回 值：
--------------------------------------------------------------------------
修改记录：
日		期	版本	修改人	修改内容
2005/01/25	3.6		李洪强	创建
========================================================================*/
void CTplArrayCase::GetAtBeforeHead()
{
    ADD_INIT_ITEM

    u32 dwInvalid = 0xFF00FF;
    TplArray<u32>::SetInvalidItem(dwInvalid);

    u32 dwItem = tplArray.GetAt(-1);
    CPPUNIT_ASSERT(dwItem == dwInvalid);
}

/*========================================================================
函 数 名：GetAtAfterTail
功    能：获取元素的索引超过上边界
参    数：
返 回 值：
--------------------------------------------------------------------------
修改记录：
日		期	版本	修改人	修改内容
2005/01/25	3.6		李洪强	创建
========================================================================*/
void CTplArrayCase::GetAtAfterTail()
{
    ADD_INIT_ITEM

    u32 dwInvalid = 0xFF00FF;
    TplArray<u32>::SetInvalidItem(dwInvalid);

    u32 dwItem = tplArray.GetAt(TEST_SIZE);
    CPPUNIT_ASSERT(dwItem == dwInvalid);
}
#endif// _DEBUG

/*========================================================================
函 数 名：GetItemPtr
功    能：在有效区域内得到元素指针
参    数：
返 回 值：
--------------------------------------------------------------------------
修改记录：
日		期	版本	修改人	修改内容
2005/01/25	3.6		李洪强	创建
========================================================================*/
void CTplArrayCase::GetItemPtr()
{
    ADD_INIT_ITEM

    const u32 *pdwStart = tplArray.GetItemPtr(0);
    CPPUNIT_ASSERT(pdwStart != NULL);

    for(nIndex = 1; nIndex < TEST_SIZE; nIndex++)
    {
        const u32 *pdwItem = tplArray.GetItemPtr(nIndex);
        CPPUNIT_ASSERT(pdwItem != NULL);
        CPPUNIT_ASSERT(pdwItem - pdwStart == nIndex);
    }
}

#ifndef _DEBUG
/*========================================================================
函 数 名：GetPtrBeforeHead
功    能：获取的元素指针索引为负值
参    数：
返 回 值：
--------------------------------------------------------------------------
修改记录：
日		期	版本	修改人	修改内容
2005/01/25	3.6		李洪强	创建
========================================================================*/
void CTplArrayCase::GetPtrBeforeHead()
{
    ADD_INIT_ITEM

    const u32 *pdwStart = tplArray.GetItemPtr(-1);
    CPPUNIT_ASSERT(pdwStart == NULL);
}

/*========================================================================
函 数 名：GetPtrAfterTail
功    能：获取的元素指针索引超过上边界
参    数：
返 回 值：
--------------------------------------------------------------------------
修改记录：
日		期	版本	修改人	修改内容
2005/01/25	3.6		李洪强	创建
========================================================================*/
void CTplArrayCase::GetPtrAfterTail()
{
    ADD_INIT_ITEM

    const u32 *pdwStart = tplArray.GetItemPtr(TEST_SIZE);
    CPPUNIT_ASSERT(pdwStart == NULL);
}
#endif // _DEBUG

/*========================================================================
函 数 名：IsEmpty
功    能：数组是否为空
参    数：
返 回 值：
--------------------------------------------------------------------------
修改记录：
日		期	版本	修改人	修改内容
2005/01/25	3.6		李洪强	创建
========================================================================*/
void CTplArrayCase::IsEmpty()
{
    TplArray<u32> tplArray;

    CPPUNIT_ASSERT(tplArray.IsEmpty() == TRUE);
    for(s32 nIndex = 0; nIndex < TEST_SIZE; nIndex++)
    {
        u32 dwItem = nIndex + 10;
        tplArray.Add(&dwItem);
    }

    CPPUNIT_ASSERT(tplArray.IsEmpty() == FALSE);

    tplArray.Clear();
    CPPUNIT_ASSERT(tplArray.IsEmpty() == TRUE);
}

/*========================================================================
函 数 名：OpEqual
功    能：=号是否正确交换信息
参    数：
返 回 值：
--------------------------------------------------------------------------
修改记录：
日		期	版本	修改人	修改内容
2005/01/25	3.6		李洪强	创建
========================================================================*/
void CTplArrayCase::OpEqual()
{
    TplArray<u32> tplOldArray(11, 13);
    for(s32 nIndex = 0; nIndex < TEST_SIZE; nIndex++)
    {
        u32 dwItem = nIndex + 10;
        tplOldArray.Add(&dwItem);
    }

    TplArray<u32> tplNewArray;
    tplNewArray = tplOldArray;

    CPPUNIT_ASSERT(tplOldArray.Size() == tplNewArray.Size());
    CPPUNIT_ASSERT(tplOldArray.Size() == tplNewArray.GetMaxSize());
    CPPUNIT_ASSERT(tplOldArray.GetStep() == tplNewArray.GetStep());

    for(nIndex = 0; nIndex < TEST_SIZE; nIndex++)
    {
        CPPUNIT_ASSERT(tplOldArray[nIndex] == tplNewArray[nIndex]);
    }
}

/*========================================================================
函 数 名：GetMaxSize
功    能：得到数组的最大空间
参    数：
返 回 值：
--------------------------------------------------------------------------
修改记录：
日		期	版本	修改人	修改内容
2005/01/25	3.6		李洪强	创建
========================================================================*/
void CTplArrayCase::GetMaxSize()
{
    TplArray<u32> tplArray;
    CPPUNIT_ASSERT(tplArray.GetMaxSize() == 10);

    for(s32 nIndex = 0; nIndex < TEST_SIZE; nIndex++)
    {
        u32 dwItem = nIndex + 10;
        tplArray.Add(&dwItem);
    }

    s32 nStep = tplArray.GetStep();
    s32 nSize = (TEST_SIZE + nStep - 1) / nStep * nStep;
    CPPUNIT_ASSERT(tplArray.GetMaxSize() == nSize);
}

/*========================================================================
函 数 名：GetStep
功    能：得到数组递增的步长
参    数：
返 回 值：
--------------------------------------------------------------------------
修改记录：
日		期	版本	修改人	修改内容
2005/01/25	3.6		李洪强	创建
========================================================================*/
void CTplArrayCase::GetStep()
{
    TplArray<u32> tplArray;
    CPPUNIT_ASSERT(tplArray.GetStep() == 10);

    for(s32 nIndex = 0; nIndex < TEST_SIZE; nIndex++)
    {
        u32 dwItem = nIndex + 10;
        tplArray.Add(&dwItem);
    }

    CPPUNIT_ASSERT(tplArray.GetStep() == 10);
}

/*========================================================================
函 数 名：GetData
功    能：得到数组的首地址
参    数：
返 回 值：
--------------------------------------------------------------------------
修改记录：
日		期	版本	修改人	修改内容
2005/01/25	3.6		李洪强	创建
========================================================================*/
void CTplArrayCase::GetData()
{
    TplArray<u32> tplArray;
    CPPUNIT_ASSERT(tplArray.GetData() != NULL);

    for(s32 nIndex = 0; nIndex < TEST_SIZE; nIndex++)
    {
        u32 dwItem = nIndex + 10;
        tplArray.Add(&dwItem);
    }

    CPPUNIT_ASSERT(tplArray.GetData() != NULL);

    tplArray.Clear();
    CPPUNIT_ASSERT(tplArray.GetData() == NULL);
}


