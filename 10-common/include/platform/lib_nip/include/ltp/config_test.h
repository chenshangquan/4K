#ifndef _CONFIG_TEST_H_
#define  _CONFIG_TEST_H_
#ifndef CMD_SUCCESS
#define CMD_SUCCESS  0
#endif
#ifndef CMD_WARNING
#define CMD_WARNING 1
#endif
enum preset_type
{
    PRE_DEL  = -1, 
    TESTCASE,
    PRE_ADD
};

enum rtn_type
{
    CFG_TST_SUCCEED = 0,   // 测试成功
    CFG_TST_WARNING,   // 警告
    CFG_TST_FAILED    // 测试失败
};

#ifndef MAXLTPLEN 
#define MAXLTPLEN 256
#endif
#ifndef FILENAME_MAX_LEN
#define FILENAME_MAX_LEN  32
#endif
#define NULL_STR "*"			// 当测试的参数中，有字符串的时候，如果为“*”，将字符串指针赋为NULL
#define TC_FLAG(env) (env == -1)?"PRE_DEL :":(env == 0)?"TESTCASE:":(env == 1)?"PRE_ADD :":"UNKNOWN"

struct config_test_01_t 
{
	/* 预置条件 */      
    int setup_env;
    /* 预期结果 */
   int  val;
   int  rtn;
};
struct config_test_02_t 
{
	/* 预置条件 */      
    int setup_env;
    /* 预期结果 */
   int  val;
   int  rtn;
};
struct config_test_03_t 
{
    /* 预置条件 */      
    int setup_env;
   //测试输入
   char filename[MAXLTPLEN];
    /* 预期结果 */
   int  val;
   int  rtn;
};
struct config_test_04_t 
{
    /* 预置条件 */      
    int setup_env;
   //测试输入
   char filename[MAXLTPLEN];
    /* 预期结果 */
   int  val;
   int  rtn;
};
struct config_test_05_t 
{
    /* 预置条件 */      
    int setup_env;
   //测试输入
   char filename[MAXLTPLEN];
    /* 预期结果 */
   int  val;
   int  rtn;
};
struct config_test_06_t 
{
	/* 预置条件 */      
    int setup_env;
    /* 预期结果 */
   int  val;
   int  rtn;
};
struct config_test_07_t 
{
	/* 预置条件 */      
    int setup_env;
    /* 预期结果 */
   int  val;
   int  rtn;
};
struct config_test_08_t 
{
    /* 预置条件 */      
    int setup_env;
   //测试输入
   char filename[MAXLTPLEN];
    /* 预期结果 */
   int  val;
   int  rtn;
};
#endif
