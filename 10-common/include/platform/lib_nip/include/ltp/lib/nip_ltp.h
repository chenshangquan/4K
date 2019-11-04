/*=======================================================================
模块名      : LTP测试--数据收发模块
文件名      : nip_ltp.h
相关文件    : 
文件实现功能: 
作者        : JinFeng
版本        : LTP Release 1.0
-------------------------------------------------------------------------
修改记录:
日  期				版本		修改人					修改内容
2006/01/09			1.0			SWP				        创建
2006/02/07			1.0			Jinfeng					修改
=======================================================================*/
#ifdef LTP_NIP_TEST

#ifndef __NIP_LTP_H__
#define __NIP_LTP_H__


#define   NL_MAX_TST    10

typedef  char    NL_MODULE[16];

/*----------------------------------------------------------------------
结 构 名  : tst_list
功    能  : 测试链表
注    意  : 
参    数  : 
返 回 值  : 
-------------------------------------------------------------------------
修改纪录:
日  期				版本		修改人					修改内容
2006/01/09			1.0			SWP				        创建
2006/02/07			1.0			Jinfeng					修改
------------------------------------------------------------------------*/
struct tst_list
{
    NL_MODULE   tst;        // 测试模块名
    GList       *item;      // 测试例(节点)名
};


/*----------------------------------------------------------------------
结 构 名  : nl_opts
功    能  : 
注    意  : 
参    数  : 
返 回 值  : 
-------------------------------------------------------------------------
修改纪录:
日  期				版本		修改人					修改内容
2006/01/09			1.0			SWP				        修改
2006/02/07			1.0			Jinfeng					创建
------------------------------------------------------------------------*/
struct nl_opts {
    int (*tstdo)();         // 测试执行的线程
    int (*cleanup)();       // 测试执行结束后的清理(开发人员自定义)
};


/*----------------------------------------------------------------------
结 构 名  : nl_handle
功    能  : 
注    意  : 
参    数  : 
返 回 值  : 
-------------------------------------------------------------------------
修改纪录:
日  期				版本		修改人					修改内容
2006/01/09			1.0			SWP				        创建
2006/02/07			1.0			Jinfeng					修改
------------------------------------------------------------------------*/
struct nl_handle {
    MODULE_TST_ITEM item;       // 测试例ID
    struct nl_opts *opts;       // 测试例选项(测试需要的启动线程)
    int  tunnel;                // 测试例所使用的tunnel(TCP连接的fd)
    int  thread_id;             // 测试例执行线程的ID
};
#define  NL_HANDLE   struct nl_handle

#define TESTCASE_OPT() \
static struct nl_opts opt = {  \
    .tstdo = tst_do,  \
    .cleanup = tst_cleanup,  \
};

/* Register TESTCASE ID to system */
#define TESTCASE_INIT(func_name, nl_module, module_tst_item)		 \
int func_name()		 \
{    \
		 if (nl_get_tst(nl_module) == NULL)    \
		 {   \
		 		 nl_register_tst(nl_module);    		 \
		 }    \
\
		 if (nl_register_item(module_tst_item, &opt) != 1)    /* 这是和客户端一样的ID*/\
		 {        \
		 		 printf("register item error\r\n");        \
		 		 return 0;    \
		 }    \
\
		 return 1;\
}

/* receive testdata for Driver */
#define RECV_TESTCASE(datatype) \
{ \
    if (tunnel_recv(fd, (void *)&tstdata, sizeof(struct datatype))	 \
                != sizeof(struct datatype))  \
        {   \
            tstdata.rtn = htonl(API_TST_WARNING);   \
            tunnel_send(fd, &tstdata, sizeof(struct datatype));   \
            continue;  \
        }   \
}

/* Set testcase, then get an fd to send/recv */
#define GET_TESTCASE( datatype) \
{  \
    memset(&tstdata, 0, sizeof(struct datatype));  \
    \
    while ((fd = tunnel_get(handle)) <= 0)    \
    {  \
        sleep(1);  \
    }  \
}

/* Execute testcase = main */
#define TESTCASE_EXEC(datatype, comp) \
static int \
tst_do(NL_HANDLE *handle) \
{  \
    int fd;  \
    int reval = 0;  \
    \
    struct datatype tstdata;  \
    \
    GET_TESTCASE(datatype);       \
    \
    while (1)  \
    {  \
        RECV_TESTCASE(datatype);  \
        \
        reval = self_func(&tstdata);  \
        \
        comp(reval);   \
        \
        tunnel_send(fd, &tstdata, sizeof(struct datatype));  \
    }  \
    \
    return 1;  \
}


/* compare test result with expect */
#define DEFAULT_COMP(ret)  \
{ \
    if ( ret == tstdata.val)  \
    {  \
        tstdata.val = htonl(ret);  \
        tstdata.rtn = htonl(API_TST_SUCCEED);  \
    }  \
    else  \
    {  \
        tstdata.val = htonl(ret);  \
        tstdata.rtn = htonl(API_TST_FAILED);  \
    }  \
}

/* For the logic compare in some case: !3 == !-1.
   Sometimes they told me return is non-zero  */
#define BOOL_COMP(ret)  \
{ \
    if ( !ret == !tstdata.val)  \
    {  \
        tstdata.val = htonl(ret);  \
        tstdata.rtn = htonl(API_TST_SUCCEED);  \
    }  \
    else  \
    {  \
        tstdata.val = htonl(ret);  \
        tstdata.rtn = htonl(API_TST_FAILED);  \
    }  \
}

#define TESTCASE_CLEAN() \
static int  \
tst_cleanup()  \
{  \
    return 1;  \
}  

#endif

#endif
