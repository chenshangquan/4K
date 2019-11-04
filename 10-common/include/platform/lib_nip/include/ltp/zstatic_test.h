/*=======================================================================
模块名      : 静态路由测试
文件名      : 
相关文件    : 
文件实现功能: 
作者        : Jin Feng
版本        : LTP Release 1.0
-------------------------------------------------------------------------
修改记录:
日  期				版本		修改人					修改内容
2006/4/20			1.0			Jin Feng					创建
=======================================================================*/

#ifndef _ZSTATIC_TEST_H_
#define _ZSTATIC_TEST_H_

enum preset_type
{
    PRE_DEL  = -1, 
    TESTCASE,
    PRE_ADD
};

enum rtn_type
{
    TST_SUCCEED = 0,   // 测试成功
    TST_WARNING,   // 警告
    TST_FAILED,    // 测试失败
};

#ifndef MAXLTPLEN 
#define MAXLTPLEN 255
#endif

#define NULL_STR "*"			// 当测试的参数中，有字符串的时候，如果为“*”，将字符串指针赋为NULL
#define TC_FLAG(env) (env == -1)?"PRE_DEL :":(env == 0)?"TESTCASE:":(env == 1)?"PRE_ADD :":"UNKNOWN"

/*------------------------------------*/

struct zstatic_test_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    int   add_cmd;
    char  dest_str[MAXLTPLEN];    // 目的路由
    char  mask_str[MAXLTPLEN];    // 路由的网络掩码
    char  gate_str[MAXLTPLEN];    // 路由的网关
    char  distance_str[MAXLTPLEN];              // 路由优先级
    int   errid;                 // add、delete  type
    /* 预期结果 */
   int  val;
   int  rtn;
};

/*------------------------------------*/
#endif
