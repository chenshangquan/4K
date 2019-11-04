/*=======================================================================
模块名      : ZIPC测试收发数据所使用的数据类型
文件名      : 
相关文件    : 
文件实现功能: 
作者        : JinFeng
版本        : LTP Release 1.0
-------------------------------------------------------------------------
修改记录:
日  期				版本		修改人					修改内容
2006/02/07			1.0			Jinfeng					创建
=======================================================================*/
#ifdef LTP_NIP_TEST

#ifndef _ZIPC_TEST_H_
#define _ZIPC_TEST_H_

enum
{
    ZIPC_TST_SUCCEED,   // 测试成功
    ZIPC_TST_WARNING,   // 警告
    ZIPC_TST_FAILED,    // 测试失败
};

#define MAXZIPCLEN 255
/*------------------------------------*/
//struct for nip testing
struct zipc_create_t
{
    char  sockname[MAXZIPCLEN];
    int     val;
    int     rtn;
};

/*------------------------------------*/
//struct for nip testing
struct zipc_close_t
{
    char  sockname[MAXZIPCLEN];
    int     val;
    int     rtn;
};

/*------------------------------------*/

//struct for nip testing
struct zipc_zmsg_tst
{
    int     length;
    int     val;
    int     rtn;
};

/*------------------------------------*/

//struct for nip testing
struct zipc_send_tst
{
    int     length;
    int     val;
    int     rtn;
};

/*------------------------------------*/

//struct for nip testing
struct zipc_recv_tst
{
    int     length;
    int     val;
    int     rtn;
};

/*------------------------------------*/

//struct for nip testing
struct zipc_send_recv_tst
{
    int     length;
    int     val;
    int     rtn;
};
/*------------------------------------*/
//struct for nip testing
struct zipc_zmsg_set_type_tst
{
 
    int		length;
	u_long	msgtype;
	int		val;
    int		rtn;
};

#endif

#endif
