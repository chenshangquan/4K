/*=======================================================================
Ä£¿éÃû      : ZUSER²âÊÔ
ÎÄ¼şÃû      : 
Ïà¹ØÎÄ¼ş    : 
ÎÄ¼şÊµÏÖ¹¦ÄÜ: 
×÷Õß        : feixiaoping
°æ±¾        : LTP Release 1.0
-------------------------------------------------------------------------
ĞŞ¸Ä¼ÇÂ¼:
ÈÕ  ÆÚ				°æ±¾		ĞŞ¸ÄÈË					ĞŞ¸ÄÄÚÈİ
2006/02/14			1.0			feixiaoping					´´½¨
=======================================================================*/
#ifdef LTP_NIP_TEST

#ifndef _ZUSR_TEST_H_
#define _ZUSR_TEST_H_

#include <sys/mman.h>

#if 0
enum preset_type
{
    PRE_DEL  = -1,         // »·¾³´î½¨
    TESTCASE,¡¡¡¡¡¡¡¡¡// ²âÊÔÊı¾İ
    PRE_ADD       // »·¾³´î½¨
};
#endif


enum rtn_type
{
    ZUSR_TST_SUCCEED = 0,   // ²âÊÔ³É¹¦
    ZUSR_TST_WARNING,   // ¾¯¸æ
    ZUSR_TST_FAILED,    // ²âÊÔÊ§°Ü
};

#if 1
enum preset_type
{
	PRE_DEL = -1,
	TESTCASE = 0,
	PRE_ADD = 1,
};
#endif

#define MAXZUSRLEN 256
#define NULL_STR "*"
/*------------------------------------*/
//struct for nip testing
struct zusr_add_t
{
    /* Ô¤ÖÃÌõ¼ş */      
    int setup_env;
    /* ²âÊÔÊäÈë */
    int  id;
    char pstr_user[MAXZUSRLEN];
    char pstr_pass[MAXZUSRLEN];

    /* Ô¤ÆÚ½á¹û */
   int val;
   int     rtn;
};

/*------------------------------------*/
//struct for nip testing
struct zusr_get_t
{
    /* Ô¤ÖÃÌõ¼ş */      
    int setup_env;
    /* ²âÊÔÊäÈë */
    int  id;
    char pstr_user[MAXZUSRLEN];
    char pstr_pass[MAXZUSRLEN];

    /* Ô¤ÆÚ½á¹û */
    int val;
    int     rtn;
};

/*------------------------------------*/
//struct for nip testing
struct zusr_del_t
{
    /* Ô¤ÖÃÌõ¼ş */      
    int setup_env;
    /* ²âÊÔÊäÈë */
    int  id;
    char pstr_user[MAXZUSRLEN];
    char pstr_pass[MAXZUSRLEN];

    /* Ô¤ÆÚ½á¹û */
    int val;
    int     rtn;
};

/*------------------------------------*/
//struct for nip testing
struct zusr_check_t
{
    /* Ô¤ÖÃÌõ¼ş */      
    int setup_env;
    /* ²âÊÔÊäÈë */
    int  id;
    char pstr_user[MAXZUSRLEN];
    char pstr_pass[MAXZUSRLEN];

    /* Ô¤ÆÚ½á¹û */
    int val;
    int     rtn;
};

/*interproc*/
/*------------------------------------*/
//struct for nip testing
struct zusr_add_interproc_t
{
    /* Ô¤ÖÃÌõ¼ş */      
    int setup_env;
    /* ²âÊÔÊäÈë */
    int  id;
    char pstr_user[MAXZUSRLEN];
    char pstr_pass[MAXZUSRLEN];

    /* Ô¤ÆÚ½á¹û */
    int val;
    int     rtn;
};

/*------------------------------------*/
//struct for nip testing
struct zusr_del_interproc_t
{
    /* Ô¤ÖÃÌõ¼ş */      
    int setup_env;
    /* ²âÊÔÊäÈë */
    int  id;
    char pstr_user[MAXZUSRLEN];
    char pstr_pass[MAXZUSRLEN];

    /* Ô¤ÆÚ½á¹û */
    int val;
    int     rtn;
};

/*------------------------------------*/
//struct for nip testing
struct zusr_check_interproc_t
{
    /* Ô¤ÖÃÌõ¼ş */      
    int setup_env;
    /* ²âÊÔÊäÈë */
    int  id;
    char pstr_user[MAXZUSRLEN];
    char pstr_pass[MAXZUSRLEN];

    /* Ô¤ÆÚ½á¹û */
    int val;
    int     rtn;
};

/*------------------------------------*/
//struct for nip testing
struct zusr_get_interproc_t
{
    /* Ô¤ÖÃÌõ¼ş */      
    int setup_env;
    /* ²âÊÔÊäÈë */
    int  id;
    char pstr_user[MAXZUSRLEN];
    char pstr_pass[MAXZUSRLEN];

    /* Ô¤ÆÚ½á¹û */
    int val;
    int     rtn;
};

#endif

#endif

