/*****************************************************************************
  模块名      : KDV system
  文件名      : kdvsys.h
  相关文件    : 
  文件实现功能: KDV公共函数及宏定义
  作者        : 李屹
  版本        : V0.9  Copyright(C) 2001-2002 KDC, All rights reserved.
  -----------------------------------------------------------------------------
  修改记录:
  日  期      版本        修改人      修改内容
  2002/01/30  0.9         李屹        创建
  2004/03/03  3.0         jianghy       修改
 ******************************************************************************/
#ifndef KDVSYS_H
#define KDVSYS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// {{{ codes those irrelevant with ini files.
#if defined(_WIN32) || defined(WIN32)
#define DllExport __declspec(dllexport)
#else /* VxWorks*/
#define DllExport
#endif

/* 定义回车 */
#if defined(_WIN32) || defined(WIN32)
#define     STR_RETURN          (const char*)"\r\n"
#elif defined( VXWORKS_SIMU )
#define     STR_RETURN          (const char*)"\r\n"
#else /* VxWorks */
#define     STR_RETURN          (const char*)"\n"
#endif

/* SNMP拷贝FTP文件分割符 */
#define CHAR_FTPFILE_SEPARATOR       (char)'|'   /* 不同文件之间分隔符 */
#define CHAR_FTPFILETYPE_SEPARATOR   (char)':'   /* 文件名和类型之间分隔符 */
#define CHAR_EXE_TYPE                (char)'E'   /* 二进制文件类型 */
#define CHAR_CFG_TYPE                (char)'C'   /* 配置文件类型 */
#define CHAR_RES_TYPE                (char)'R'   /* 资源文件类型 */
#define CHAR_WEB_TYPE                (char)'W'   /* web文件类型 */
#define CHAR_PIC_TYPE                (char)'P'   /* 图片文件类型 */

/* 定义Profile文件中表格数据相关字符串常量 */
#define STR_ENTRY_NUM           (const char*)"EntryNum"
#define STR_ENTRY               (const char*)"Entry"
#define SECTION_ipRouteTable    (const char*)"ipRouteTable"
#define FIELD_ipRouteDest       (const char*)"ipRouteDest"
#define FIELD_ipRouteNextHop    (const char*)"ipRouteNextHop"
#define FIELD_ipRouteMask       (const char*)"ipRouteMask"

/* OID length */
#define OID_IP_ADDR_LEN     4 
#define OID_ID_LEN          1 

/* maximum size of physical address */
#define MAXSIZE_PHYADDR     16

typedef unsigned char   MAC_TYPE[6];

/* 路径定义 */
#if defined( WIN32 )  || defined(_WIN32)   /* WIN32 */
#define PATH_FTP            (const char*)"ftp"
#define PATH_CONFIG         (const char*)"conf"
#define PATH_BIN            (const char*)"."
#define PATH_RES            (const char*)"res"
#define PATH_WEB            (const char*)"webfiles/doc"
#define PATH_PIC            (const char*)"webfiles/doc/images"
#define PATH_XML            (const char*)"webfiles" //add hzc
#define PATH_DOC            (const char*)"doc"      //add hzc
#elif defined( VXWORKS_SIMU )
#define PATH_FTP            (const char*)"ftp"
#define PATH_CONFIG         (const char*)"conf"
#define PATH_BIN            (const char*)"."
#define PATH_RES            (const char*)"res"
#else                   /* vxWorks */
#define PATH_FTP            (const char*)"/ftp"
#define PATH_CONFIG         (const char*)"/conf"
#define PATH_BIN            (const char*)""
#define PATH_RES            (const char*)"res"
#define PATH_WEB            (const char*)"/webfiles/doc"
#define PATH_PIC            (const char*)"/webfiles/doc/images"
#define PATH_XML            (const char*)"/webfiles"//add hzc
#define PATH_DOC            (const char*)"doc"    //add hzc

#endif


/* semTake超时 */
#define WAIT_SEM_TIMEOUT    2000    /* ticks */

/* SNMP PORT macro */
#define  SNMP_PORT          161         /* port for snmp */
#define  TRAP_PORT          162         /* port for snmp traps */

/* SNMP TRAP自定义specificTrap */
#define SPECIFICTRAP_COLD_RESTART       1L
#define SPECIFICTRAP_POWERON            1L   //add by hzc
#define SPECIFICTRAP_POWEROFF           2L
#define SPECIFICTRAP_ALARM_GENERATE     3L
#define SPECIFICTRAP_ALARM_RESTORE      4L
#define SPECIFICTRAP_LED_STATE          5L
#define SPECIFICTRAP_CONF_STATE         6L
#define SPECIFICTRAP_MT_STATE           7L
#define SPECIFICTRAP_AUTODETECT         8L   //自动探测 //add by hzc

/* PrintMsg() type取值 */
#define MESSAGE_INFO            (unsigned char  )0x1
#define MESSAGE_WARNING         (unsigned char  )0x2
#define MESSAGE_ERROR           (unsigned char  )0x3

#define MESSAGE_BUFFER_LEN      (uint16_t)1024   /* 消息缓冲的最大长度 */

#ifndef MAX_PATH
/* 定义最大路径长度 */
#define MAX_PATH                (uint16_t)256
#endif

// 由于vc编译器所定义的MAX_PATH为260 与上面的定义长度存在出入，导致window与linux版本兼容问题
// 故新增该宏定义替代MAX_PATH宏定义
#define KDV_MAX_PATH            (uint16_t)256

#ifndef MAX_LINE_LEN
/* 定义一行的最大长度 */
#define MAX_LINE_LEN            (uint16_t)1024
#endif

#define MAX_SECTIONNAME_LEN     (uint16_t)50
#define MAX_KEYNAME_LEN         (uint16_t)50
#define MAX_VALUE_LEN           (uint16_t)255
#define MAX_WRITE_SECTIONONECE_LEN  (uint16_t)(20*100)//写一次section的最大长度

/* OpenProfile() byOpenMode 取值 */
#define PROFILE_READONLY        (unsigned char  )0x1       /*只读*/
#define PROFILE_WRITE           (unsigned char  )0x2       /*读写*/
#define PROFILE_READWRITE       PROFILE_WRITE   /*读写*/
#define PROFILE_WRITEONLY       (unsigned char  )0x4       /*只写*/

#define PROFILE_MAX_OPEN        (uint16_t)20        /* 打开文件的最大数目 */

typedef uint32_t                   tKeyHandle;

#define INVALID_KEYHANDLE       (uint16_t)0xFFFF    /* 无效的文件句柄 */

/* Profile文件注释符定义 */
#define PROFILE_COMMENT1        (const char*)";"
#define PROFILE_COMMENT2        (const char*)"//"
#define PROFILE_COMMENT3        (const char*)"--"
#define PROFILE_COMMENT4        (const char*)"#"

/* struct definition */
typedef struct
{
    uint16_t  dwAddrLen;                      /* Length of address */
    unsigned char   phyAddress[MAXSIZE_PHYADDR];    /* physical address value */
} PHYADDR_STRUCT;

typedef struct
{
    unsigned char   byDtiNo;
    unsigned char   byE1No;
} MCU_E1_STRUCT;

typedef struct
{
    unsigned char   byDtiNo;
    unsigned char   byE1No;
    unsigned char   byTsNo;
} MCU_TS_STRUCT;

typedef struct
{
    uint32_t   dwTsNumber;                 /* TS number */
    MCU_TS_STRUCT   *ptMcuTs;         /* MCU TS array */
} MCU_TS_ARRAY_STRUCT;

typedef struct
{
    unsigned char   byE1No;
    unsigned char   byTsNo;
} MT_TS_STRUCT;

/* -----------------------  系统公用函数  ----------------------------- */
#define LOWORD16(l)     ((uint16_t)(l))
#define HIWORD16(l)     ((uint16_t)(((uint32_t)(l) >> 16) & 0xFFFF))
#define MAKEDWORD(l,h)  ((uint32_t)(((uint16_t)(l)) | ((uint32_t)((uint16_t)(h))) << 16))

#ifndef _WINDEF_  /* 为了能够有Windows下使用 */
#define LOBYTE(w)       ((unsigned char)(w))
#define HIBYTE(w)       ((unsigned char)(((uint16_t)(w) >> 8) & 0xFF))
#define MAKEWORD(l,h)   ((uint16_t)(((unsigned char)(l)) | ((uint16_t)((unsigned char)(h))) << 8))
#endif

#ifdef _DEBUG 
#undef ASSERT
#define ASSERT(exp)    \
{ \
    if ( !( exp ) ) \
    { \
        printf((char*)"Assert File %s, Line %d (%s)\n", \
                __FILE__, __LINE__, (char*)#exp ); \
    } \
}
#else
#undef ASSERT
#define ASSERT( exp )    {}
#endif

// }}}
// {{{ functions with ini files

/* 读取配置文件类函数 */
DllExport int32_t GetRegKeyInt(
        const char* lpszProfileName,  /* 文件名（含绝对路径）*/
        const char* lpszSectionName,  /* Profile中的段名   */
        const char* lpszKeyName,      /* 段内的关键字名    */
        const int32_t sdwDefault,       /* 失败时返回的默认值*/
        int32_t  *sdwReturnValue        /* 返回值            */
        );

/* 从配置文件中读取一整数型值 */
DllExport int32_t GetRegKeyStringTable(
        const char* lpszProfileName,  /* 文件名（含绝对路径）*/
        const char* lpszSectionName,  /* Profile中的段名   */        
        const char* lpszDefault,      /* 失败时返回的默认值*/
        char* *lpszEntryArray,        /* 返回字符串数组指针 */
        uint32_t *dwEntryNum,            /* 字符串数组数目，成功后返回字符串数组实际数
                                       目，如传入的数目不够则多余的记录不予传回 */
        uint32_t dwBufSize               /* 返回字串的长度，如不够则截断，最
                                       后一个字节填上'\0'    */
        );

/* 从配置文件中读取一张表里的若干行数据 */
DllExport int32_t GetRegKeyString(
        const char* lpszProfileName,  /* 文件名（含绝对路径）*/
        const char* lpszSectionName,  /* Profile中的段名   */
        const char* lpszKeyName,      /* 段内的关键字名    */
        const char* lpszDefault,      /* 失败时返回的默认值*/
        char* lpszReturnValue,        /* 返回字串          */
        uint32_t dwBufSize               /* 返回字串的长度，如不够则截断，最
                                       后一个字节填上'\0'    */
        );

/**
 *
 * 重要的注意项:
 *
 *   原来在 libkdvsys.a 中提供的方法 `GetRegKeyString2' 因为直接操作未受控制
 *   与保护的文件指针而存在导致缺陷的隐患，现在已经不再在新版的 API 中提供了。
 *   相同的功能将由方法 `GetRegKeyString' 提供。
 *
 *   当需要批量获取一个配置文件中的属性字典时，使用 <kprop.h> 中提供的与对象
 *   TKProps 相关的方法集可以获得高效的访问。参见如下代码片段：
 *
 *   : // 这段代码主要用来说明如何获取属性值，省去了错误码的检查等，
 *   : // 在严格的产品代码中总是应该检查错误码的。
 *   : char achBuff[120];         // 待接收属性值的缓冲
 *   : TKProps * ptProps = NULL;  // 申明一个 TKProps 对象的句柄（必置空）
 *   : KPropsInit(&ptProps, 1);   // 创建一个 TKProps 对象，并指定区分大小写
 *   : KPropsLoadPath(ptProps, "myconf.ini"); // 从 myconf.ini 中加载属性字典
 *   : KPropsGetString(ptProps,   // 从 TKProps 对象中获取属性值
 *   :     "group", "key",        // 使用指定的分组 group 和关键字 key
 *   :     "def",                 // 或者设置成缺省值（如果未找到）
 *   :     achBuff, sizeof(achBuff)); // 结果存入缓冲
 *   :
 *   : // ... 可以使用 ptProps 进行批量的属性查询操作。
 *   :
 *   : KPropsDestroy(&ptProps);   // 最后，总是应该释放掉这个对象中的资源
 *
 * 关于方法 `GetRegKeyString2' 原来的接口定义如下：
 *
 * DllExport int32_t GetRegKeyString2(
 *         FILE *stream,
 *         const char* lpszSectionName,
 *         const char* lpszKeyName,
 *         const char* lpszDefault,
 *         char* lpszReturnValue,
 *         uint32_t dwBufSize
 *         );
 *
 * -- 谢志钢，2015-03-04
 */

/* 根据文件句柄从配置文件中读取一字符串值，该文件需以"rb"方式打开 */
DllExport int32_t SetRegKeyInt(
        const char* lpszProfileName,  /* 文件名（含绝对路径）*/
        const char* lpszSectionName,  /* Profile中的段名   */
        const char* lpszKeyName,      /* 段内的关键字名    */
        const int32_t sdwValue          /* 新的整数值        */
        );

/* 往配置文件中写入一新的整数型的值，如果不存在则自动创建 */
DllExport int32_t SetRegKeyString(
        const char* lpszProfileName,  /* 文件名（含绝对路径）*/
        const char* lpszSectionName,  /* Profile中的段名   */
        const char* lpszKeyName,      /* 段内的关键字名    */
        const char* lpszValue         /* 新的字串值, NULL则表示删除改行 */
        );

/*====================================================================
  函数名      SetRegKeySection
  功能        ：往配置文件中写入一个段内容
                (一次最大20*100，超过该大小应多次调用该接口写入)，
                如果不存在则自动创建
  算法实现    ：（可选项）
  引用全局变量：无
  输入参数说明：const char* lpszProfileName, 文件名（含绝对路径）   
                const char* lpszSectionName, Profile中的段名
                const char* lpszValue, 新的字串值, NULL则表示删除
                uint16_t wCurInSectionOffset,当前写入的段内偏移
                         （如：写单板的时候，配置的单板过多，可能要分多次写）
                const char* lpSzSectionKeepKey 段中要保留的关键字名
                         （如：写一整段的时候要保留entrynum的值）
  返回值说明  ：TRUE/0
  ====================================================================*/
DllExport int32_t SetRegKeySection(
        const char* lpszProfileName, 
        const char* lpszSectionName, 
        const char* lpszValue,
        uint16_t wCurInSectionOffset,
        const char* lpSzSectionKeepKey
        );

/* 往配置文件中写入一新的字符串型的值，如果不存在则自动创建 */
DllExport int32_t DeleteRegKey(
        const char* lpszProfileName,  /* 文件名（含绝对路径）*/
        const char* lpszSectionName,  /* Profile中的段名   */
        const char* lpszKeyName       /* 段内的关键字名    */
        );

/* 从配置文件中删除一行Key */
#if !defined( WIN32 ) && !defined(_WIN32)
DllExport int32_t ReadRouteTable( const char*  lpszProfileName );
#endif
/* 从配置文件中读取路由表并设置 */

/* 字符串处理类函数 */
DllExport void Trim( char* lpszSrc );        /* 去除字符串的前导及后续空格以及TAB键 */
DllExport void StrUpper( char* lpszSrc );    /* 字符串转换成大写 */
DllExport void StrLower( char* lpszSrc );    /* 字符串转换成小写 */

/*====================================================================
  功能        ：验证是否合法日期
  输入参数说明：u16 wYear, 年
  unsigned char byMonth, 月
  unsigned char byDay, 日
  unsigned char byHour, 时
  unsigned char byMin, 分
  unsigned char bySec, 秒
  返回值说明  ：合法返回TRUE，负责返回FALSE
  ====================================================================*/
DllExport int32_t IsValidTime( uint16_t wYear, unsigned char byMonth, unsigned char byDay, 
        unsigned char byHour, unsigned char byMin, unsigned char bySec );

// }}}
#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif /* KDVSYS_H */

/* end of file sys.h */
/* vim:set foldmethod=marker: */
