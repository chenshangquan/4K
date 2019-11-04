/*=======================================================================
模块名      :  接口管理测试
文件名      : 
相关文件    : 
文件实现功能: 
作者        : Jin Feng
版本        : LTP Release 1.0
-------------------------------------------------------------------------
修改记录:
日  期				版本		修改人					修改内容
2006/5/10			1.0			Jin Feng					创建
=======================================================================*/

#ifndef _IFMANAGER_TEST_H_
#define _IFMANAGER_TEST_H_

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

#define RETURN_OK 0
#define RETURN_ERROR 1

#define NULL_STR "*"			// 当测试的参数中，有字符串的时候，如果为“*”，将字符串指针赋为NULL
#define TC_FLAG(env) (env == -1)?"PRE_DEL :":(env == 0)?"TESTCASE:":(env == 1)?"PRE_ADD :":"UNKNOWN"

/*------------------------------------*/

struct ifmanager_test_01_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */

    /* 预期结果 */
   int  val;
   int  rtn;
};

/*------------------------------------*/

struct ifmanager_test_02_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */

    /* 预期结果 */
   int  val;
   int  rtn;
};

/*------------------------------------*/

struct ifmanager_test_03_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    int if_type;            
    char zebra[MAXLTPLEN];  
    char kernel[MAXLTPLEN]; 
    /* 预期结果 */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct ifmanager_test_04_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    int if_type;
    /* 预期结果 */
   int  val;
   int  rtn;
};

/*------------------------------------*/

struct ifmanager_test_05_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char name[MAXLTPLEN];
    int type;
    int unit;
    /* 预期结果 */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct ifmanager_test_06_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    int ifindex; 
    /* 预期结果 */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct ifmanager_test_07_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char ifname[MAXLTPLEN];
    /* 预期结果 */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct ifmanager_test_08_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    int if_type;
    int ifunit;  
    /* 预期结果 */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct ifmanager_test_09_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char ipaddr[MAXLTPLEN];
    /* 预期结果 */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct ifmanager_test_10_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char ipaddr[MAXLTPLEN];
    /* 预期结果 */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct ifmanager_test_11_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char ifname[MAXLTPLEN];
    /* 预期结果 */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct ifmanager_test_12_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char ifname[MAXLTPLEN];
    /* 预期结果 */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct ifmanager_test_13_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char ifname[MAXLTPLEN];
    /* 预期结果 */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct ifmanager_test_14_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char ifname[MAXLTPLEN];
    /* 预期结果 */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct ifmanager_test_15_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char ifname[MAXLTPLEN];
    /* 预期结果 */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct ifmanager_test_16_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char ifname[MAXLTPLEN];
    /* 预期结果 */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct ifmanager_test_17_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char ifname[MAXLTPLEN];
    /* 预期结果 */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct ifmanager_test_18_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char ifname[MAXLTPLEN];
    /* 预期结果 */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct ifmanager_test_19_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    int ifindex;
    char ifname[MAXLTPLEN];
    /* 预期结果 */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct ifmanager_test_20_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    int ifindex;
    char ifname[MAXLTPLEN];
    /* 预期结果 */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct ifmanager_test_21_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char ifname[MAXLTPLEN];
    /* 预期结果 */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct ifmanager_test_22_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char ifinfo[MAXLTPLEN];
    /* 预期结果 */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct ifmanager_test_23_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char nodeinfo[MAXLTPLEN];
    /* 预期结果 */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct ifmanager_test_24_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char ztype[MAXLTPLEN];
    /* 预期结果 */
    int  val;
    int  rtn;
};

/*------------------------------------*/

struct ifmanager_test_25_t
{
    /* 预置条件 */      
    int setup_env;
    /* 测试输入 */
    char ztype[MAXLTPLEN];
    /* 预期结果 */
    int  val;
    int  rtn;
};
/*------------------------------------*/
#endif
