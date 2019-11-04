/*=======================================================================
模块名      : ZLOG测试使能及关闭功能
文件名      :
相关文件    :
文件实现功能:
作者        : LinZhe
版本        : LTP Release 1.0
-------------------------------------------------------------------------
修改记录:
日  期				版本		修改人					修改内容
2006/02/07			1.0			LinZhe					创建
=======================================================================*/
#ifdef LTP_NIP_TEST

#ifndef _ZLOG_TEST_H_
#define _ZLOG_TEST_H_

enum preset_type
{
    PRE_DEL  = -1, 
    TESTCASE,
    PRE_ADD
};

enum
{
    ZLOG_TST_SUCCEED,   // 测试成功
    ZLOG_TST_WARNING,   // 警告
    ZLOG_TST_FAILED,    // 测试失败
};

#define ZLOGMAXLEN 255
#define NULL_STR "*"			// 当测试的参数中，有字符串的时候，如果为“*”，将字符串指针赋为NULL
#define TC_FLAG(env) (env == -1)?"PRE_DEL :":(env == 0)?"TESTCASE:":(env == 1)?"PRE_ADD :":"UNKNOWN"

/*------------------------------------*/
//struct for nip testing
struct zlog_test_t
{
	int		setup_env;
    int     enable;
	int     priority;
	char    module[ZLOGMAXLEN];
    int     val;
    int     rtn;
};

#endif

#endif
