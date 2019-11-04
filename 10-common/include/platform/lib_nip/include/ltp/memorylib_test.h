/*=======================================================================
模块名      : MEMORYLIB测试
文件名      : 
相关文件    : 
文件实现功能: 
作者        : Chen Shuang
版本        : LTP Release 1.0
-------------------------------------------------------------------------
修改记录:
日  期				版本		修改人					修改内容
2006/05/30			1.0		Chen Shuang				创建
=======================================================================*/

#ifndef _MEMORYLIB_TEST_H_
#define _MEMORYLIB_TEST_H_
#define NIP_RETURN_OK 0x0
#define NIP_RETURN_ERROR  (~0)
enum preset_type
{
    PRE_DEL  = -1, 
    TESTCASE,
    PRE_ADD
};

enum rtn_type
{
    API_TST_SUCCEED = 0,   // 测试成功
    API_TST_WARNING,   // 警告
    API_TST_FAILED,    // 测试失败
};

#ifndef MAXLTPLEN 
#define MAXLTPLEN 256
#endif

#define NULL_STR "*"			// 当测试的参数中，有字符串的时候，如果为“*”，将字符串指针赋为NULL
#define TC_FLAG(env) (env == -1)?"PRE_DEL :":(env == 0)?"TESTCASE:":(env == 1)?"PRE_ADD :":"UNKNOWN"

/*------------------------------------*/
struct memorylib_test_01_t
{
	/*预置条件*/
	int setup_env;
	/*测试输入*/
	int mtype;
	size_t size;
	/*预期结果*/
	int val;
	int rtn;
};

/*------------------------------------*/

struct memorylib_test_02_t
{
	/*预置条件*/
	int setup_env;
	/*测试输入*/
	int mtype;
	size_t size;
	/*预期结果*/
	int val;
	int rtn;
};

/*------------------------------------*/

struct memorylib_test_03_t
{
	/*预置条件*/
	int setup_env;
	/*测试输入*/
	int mtype;
	int ptrstat;
	size_t size;
	/*预期结果*/
	int val;
	int rtn;
};

/*------------------------------------*/

struct memorylib_test_04_t
{
	/*预置条件*/
	int setup_env;
	/*测试输入*/
	int mtype;
	int ptrstat;
	/*预期结果*/
	int val;
	int rtn;
};

/*------------------------------------*/

struct memorylib_test_05_t
{
	/*预置条件*/
	int setup_env;
	/*测试输入*/
	int mtype;
	char str[MAXLTPLEN];
	/*预期结果*/
	int val;
	int rtn;
};
#endif
