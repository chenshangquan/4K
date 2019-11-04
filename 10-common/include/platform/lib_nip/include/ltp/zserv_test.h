/*=======================================================================
模块名      : ZSERV测试收发数据所使用的数据类型
文件名      : 
相关文件    : 
文件实现功能: 
作者        : JinFeng
版本        : LTP Release 1.0
-------------------------------------------------------------------------
修改记录:
日  期				版本		修改人					修改内容
2006/04/11			1.0			Jinfeng					创建
=======================================================================*/
#ifdef LTP_NIP_TEST

#ifndef _ZSERV_TEST_H_
#define _ZSERV_TEST_H_

enum preset_type
{
    PRE_DEL  = -1, 
    TESTCASE,
    PRE_ADD
};

enum rtn_type
{
    ZSERV_TST_SUCCEED = 0,   // 测试成功
    ZSERV_TST_WARNING,   // 警告
    ZSERV_TST_FAILED,    // 测试失败
};


#define MAXZIPCLEN 255
/*------------------------------------*/
//struct for nip testing
struct zserv_test_01
{
    /* 预置条件 */      
        int setup_env;
    /* 测试输入 */
        int  type;

    /* 预期结果 */
       int   val; 
       int   rtn;
};


#endif

#endif
