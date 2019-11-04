/******************************************************************************
 * 模块名      : kprop
 * 文件名      : kprop.h
 * 相关文件    : 
 * 文件实现功能: 带分组的属性字典，以及配置文件(INI内容)操作定义。
 * 作者        : 谢志钢
 * 版本        : v1.0  Copyright(C) 2014-2015 KDC, All rights reserved.
 * ----------------------------------------------------------------------------
 * INI 语法:
 *   一个ini文件由若干文本行构成，一行文本是以换行符(0x0a)结尾的字符串。
 *   一行文本内可能包含一个组标签，或者可能包含一个属性，或者为空行。
 *   一行文本中还可能同时包含一个注释。
 *   一个组标签标志着接下来的属性将被安排在这个组标签之下，直到出现新的组标签。
 *   组标签的格式如:
 *
 *     [group_name]
 *
 *   一个属性是从属于一个组标签之下的，由属性名和属性值构成。
 *   一个属性的格式如:
 *
 *     key = value
 *
 *   一个注释是指由‘;’或者‘#’字符引导的一个字符串，直到所在文本行的行尾都是注释。
 *   特殊配置项，可以在注释中设置的可能会影响到后续 ini 语法理解细节的控制项。
 *   这些配置项也可以使用本 API 来控制。目前支持的配置项有:
 *   # ini: inline-comment no-inline-comment case-sensitive case-insensitive
 *
 * INI 语法的正则语言定义如下(ragel):
 *
 *     namespace = [ \t];
 *     groupchar = [^ \t] - '[' - ']';
 *     groupname = groupchar | (groupchar (groupchar | namespace)* groupchar);
 *     group     = '[' namespace* groupname namespace* ']';
 *     keychar   = groupchar - '=' - '#' - ';';
 *     key       = keychar | (keychar (keychar | namespace)* keychar);
 *     valuechar = ([^ \t] - '#' - ';') | ([#;] when test_no_inline_cmt);
 *     value     = valuechar | (valuechar (valuechar | namespace)* valuechar);
 *     entry     = (key) namespace* '=' namespace* (value)** namespace*;
 *     optchar   = [a-z] | '-';
 *     inlinecmt = ('no-'?) 'inline-comment';
 *     casesensi = 'case-' ('in'?) 'sensitive';
 *     oneoption = inlinecmt | casesensi | optchar+;
 *     options   = [#;] namespace* 'ini:' namespace* (oneoption namespace+)** oneoption;
 *     comment   = [#;] (any*);
 *     line      = namespace* (group | entry | options | comment)
 *                 namespace* (comment when test_in_line_cmt)? '\r'? '\n';
 *     ini      := line*;
 *
 * 一段 ini 文本的例子:
 *
 *   1	 # 这里是一行注释
 *   2	 [group_name]
 *   3	 key1 = value1 # <- 这里附加了一个内联的注释
 *   4	 key2 = value2
 *   5	
 *   6	 ; 分号也开始一行注释
 *   7	 [group2]
 *   8	 key_x = value_x
 *
 * 上面的例子中，文本行#1、#6 各描述了一个注释，文本行#2、#7 各描述了一个组标签，
 * 文本行#3、#4、#8 各描述了一个属性，特殊地，文本行#3 还附带了一个注释。
 * #3、#4 描述的属性属于#2描述的组，而#8 描述的属性属于#7 的组。
 *
 * 目前还不支持转义字符。原因是在 ini 中加入转义字符支持的话，很容易对 windows
 * 系统下配置了路径的字符串造成错误理解。还没有找到一个比较合适的提供转义的方案。
 *
 * 特殊配置项:
 *
 *   为了满足一些实际存在的业务需求，可以通过在没有出现组标签或者属性的开头处的
 * 注释中使用一些特殊标记来调整 ini 的默认语法。
 *
 *   所有特殊标记均应该记录在注释当中，并且以 “# ini: ” 引导。可以把多个特殊标
 * 记以空格分隔，串在一个注释中。
 *
 *   no-inline-comment: 禁止在属性后附加注释的特殊标记。
 *
 *     # ini: no-inline-comment
 *
 * 例如
 *
 *   1	# ini: no-inline-comment     <- 这里指示接下来禁止了内联注释
 *   2	# 这里是一行注释
 *   3	[group_name]
 *   4	key1 = value1 # this is part of value1
 *   5	key2 = value2
 *   6	
 *   7	 ; 分号也开始一行注释
 *   8	[group2]
 *   9	key_x = value_x
 *  10  # ini: inline-comment        <- 这里指示接下来允许了内联注释
 *  11	key_y = value_y  # 这里是一个内联注释
 *
 * 上面的例子中，由于使用了 no-inline-comment 标记，对默认的 ini 语法做了调整，
 * 使得 #4 行的 ‘#’ 后的文本不再被当成注释，而是属性值的一部分。而接下来，又使
 * 用了 inline-comment 标记进行了再次调整，并又一次启用了内联注释。
 *
 * 如果使用 API 函数:
 *
 *     KPropsSetOption (ptProps, "no-inline-comment");
 *
 * 则会不再理会 ini 内容中的 [no-]inline-comment 配置项了。使用 API 来控制配置
 * 项只能在 load 内容时对所有内容l做一个全局的配置，无法像 ini 内的配置项一般可
 * 以灵活地进行多次调节。
 *
 * ----------------------------------------------------------------------------
 * 修改记录:
 * 日期        版本  修改人  修改内容
 * 2015-01-05  1.0   谢志钢  创建
 * 2018-11-06  2.1   谢志钢  从内存中加载 ini，支持特殊配置项，整理 ini 语法。
 ******************************************************************************/
#ifndef KPROP_H
#define KPROP_H

#include <stddef.h>
#include <stdint.h>

#if !defined(__cplusplus)
# if defined(__GNUC__)
#  include <stdbool.h>
# else
#  if !defined(__bool_true_false_are_defined)
    typedef int8_t _Bool;
    /* ISO C Standard: 7.16 Boolean type */
#   define bool _Bool
#   define true 1
#   define false 0
#   define __bool_true_false_are_defined 1
#  endif
# endif
#endif

#include "kfile.h"

/* {{{ 前置定义项 */

#ifndef KEXTERN
#  ifdef KPROP_DLL
#    ifdef KPROP_INTERNAL
#      define KEXTERN extern __declspec(dllexport)
#    else /* ! KPROP_INTERNAL */
#      define KEXTERN extern __declspec(dllimport)
#    endif /* KPROP_INTERNAL */
#  else /* ! KPROP_DLL */
#    define KEXTERN extern
#  endif /* KPROP_DLL */
#endif /* KEXTERN */

#ifndef HAVE_ERROR_TYPE
typedef int32_t error_t;
#define HAVE_ERROR_TYPE
#endif // HAVE_ERROR_TYPE

#ifndef NO_ERROR
#define NO_ERROR  (error_t)0
#endif // NO_ERROR
// }}}

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \brief kprops 类，内部结构已经隐藏。
 *
 * kprops 类是带分组的属性字典，并且可以解析 ini 格式文本内容。
 */
typedef struct tag_kprops TKProps;

/*!
 * \brief 初始化一个 kprops 对象的实例。
 *
 * \param pptProps   - 创建、初始化一个 kprops 对象，并以此返回对象实例。
 *                     传入此指针的指针之前，请确认已经将接收指针置NULL。
 *
 * \param nSensitive - 在理解 ini 格式时是否对 group、key 的名称区分大小写。
 *                     0/false - 不区分大小写；
 *                     1/true  - 区分大小写；
 *                     -1      - 按 ini 自带的配置来理解，默认情况下区分大小写。
 *
 * 参见: KPropsSetOption 的 case-sensitive/case-insensitive/case-default，可以
 * 影响这里的 nSensitive 的配置。 -- 谢志钢, 2018-11-06
 *
 * \return 0 if successful, otherwise non-zero.
 */
KEXTERN
error_t KPropsInit (TKProps **pptProps, int32_t nSensitive);

/*!
 * \brief Destroyes an object of kprops.
 *        If pass NULL, or pointer of NULL, also ok.
 *        After an object is destroyed, the pointer will set NULL.
 */
KEXTERN
void KPropsDestroy (TKProps **pptProps);

/* 当前支持的可以在 KPropsSetOption() 方法中使用的特殊配置项 */
#define KPROP_OPTION_CASE_SENSITIVE     "case-sensitive"
#define KPROP_OPTION_CASE_INSENSITIVE   "case-insensitive"
#define KPROP_OPTION_CASE_DEFAULT       "case-default" /* 等价于移除 case-[in]sensitive */
#define KPROP_OPTION_INLINE_COMMENT     "inline-comment"
#define KPROP_OPTION_NO_INLINE_COMMENT  "no-inline-comment"
#define KPROP_OPTION_INLINE_COMMENT_DEFAULT "inline-comment-default" /* 等价于移除 [no-]inline-comment */

/*!
 * \brief 设置一个 kprop 的配置项
 *
 * 为了应对 ini 格式的细微差异，在某些情况下可能需要设置一些配置项来指示 kprop
 * 恰当地理解 ini 中的内容。
 *
 * 目前支持的配置项有:
 *
 *   case-sensitive:   对 group 和 key 的名字中的字符区分大小写。
 *   case-insensitive: 对 group 和 key 的名字中的字符不区分大小写。
 *          默认情况下，按 KPropsInit(,nSensitive) 中的参数来理解。
 *          如果在这里再次设置了相关选项，则按这里设置的选项来理解。
 *   case-default:  取消之前设置过的 case-sensitive, case-insensitive 配置，也
 *                  取消 KPropsInit(, sensitive) 时设置的配置。这时使用默认行为。
 *
 *   inline-comment:   支持内联注释，即在 group 或者 key 语句的尾部内联一条关于
 *                     这个语句的注释。下面的例子中包含了一条内联注释:
 *                     {{{
 *                         # ini: inline-comment
 *                         [common]
 *                         key = value # with an inline-comment.
 *                         #           ^^^^^^^^^^^^^^^^^^^^^^^^^
 *                         #           这里不是 key 的值而是注释。
 *                     }}}
 *                     默认情况下，kprop 按支持内联注释来理解 ini 内容。
 *   no-inline-comment: 禁止内联注释，即在 group 或者 key 语句的尾部禁止注释。
 *                      尤其是 key 语句尾部，不再使用 ';' 或者 '#' 来引导注释，
 *                      而是其后的字符将作为 key 对应的值的一部分。下面的例子中
 *                      的 key 的值中包含了 '#' 字符以及其后的内容:
 *                      {{{
 *                          # ini: no-inline-comment
 *                          [common]
 *                          key = value with '#' charactor.
 *                          #     ^^^^^^^^^^^^^^^^^^^^^^^^^
 *                          #     这里整个都是 key 的值了。
 *                      }}}
 *  inline-comment-default: 移除之前设置过的 inline-comment/no-inline-comment
 *                          配置，而使用默认行为。
 *
 * 以上的配置项也可以写入到 ini 内容的开头部分的注释中，当 kprop 解析这些 ini
 * 内容时，如果没有通过 API 特别指明某项配置，将按 ini 内容中的指示来调整。
 *
 * 当各处的配置相冲突时按此优先级来理解:
 *
 *     KPropsSetOption() > KPropsInit() > ini 头部注释
 *
 * \author 谢志钢
 * \date   2018-11-06
 */
KEXTERN
void KPropsSetOption (TKProps *ptProps, const char * pszOption);

/*!
 * \brief 查询当前的 kprop 是否已经被用户通过 KPropsSetOption() 设置了某个配置项。
 *
 * \param pszOption  需要查询的配置项，目前有:
 *              "case-sensitive", "case-insensitive",
 *              "inline-comment", "no-inline_comment"
 *
 * \return true   已经设置了对应的配置项。
 *         false  没有设置对应的配置项。
 *
 * \note 与 KPropsHasConfig() 不同之处在于，此方法只反映用户设置过的配置项，如
 *       果查询没有设置过的配置项，则直接返回 false 。如果最新设置的配置项与之
 *       前设置的配置项有冲突，则用最新设置的配置项覆盖陈旧的配置项。例如:
 *       {{{
 *          KPropsSetOption(ptProps, "case-sensitive");
 *          KPropsSetOption(ptProps, "case-insensitive");
 *          printf("case sensitivity: %d\n", KPropsHasOption(ptProps, "case-sensitive"));
 *       }}}
 *       打印的将是
 *       {{{
 *          case sensitivity: 0
 *       }}}
 */
KEXTERN
bool KPropsHasOption (TKProps *ptProps, const char * pszOption);

/*!
 * \brief 查询当前的 kprop 是否正在使用某个配置项。
 *
 * \param pszOption  需要查询的配置项，目前有:
 *              "case-sensitive", "case-insensitive",
 *              "inline-comment", "no-inline_comment"
 *
 * \return true   正在使用这个配置项。
 *         false  不，没有使用这个配置项。
 *
 * \note 与 KPropsHasOption() 不同之处在于，如果用户没有通过 KPropsSetOption()
 *       设置某个配置项，则会查询到 kprop 的默认配置的行为。
 */
KEXTERN
bool KPropsHasConfig (TKProps *ptProps, const char * pszOption);

/*!
 * \brief 从 INI 文件中加载分组的属性字典。一段有效的 INI 内容如下:
 *
 *           # comments goes here.
 *           [group_name]
 *           key1 = value1 # from here it is commedted off.
 *           key2 = value2
 *
 *           ; a semi-colum also indicates a comment line.
 *           [group2]
 *           key_x = value_x
 * 
 * \note  与 KPropsLoadFile() 的区别在于后者需要一个已经打开的 TKFile 对象，
 *        TKFile 对象可以造成排他性的文件打开占用效果，也就是当有人使用了一个
 *        TKFile 对象并打开了某个文件时，其他人将不再能够对同一路径上的这个文件
 *        进行读、写操作。
 *
 * \param ptProps     - 分组属性字典
 * \param pszFilename - INI文件路径
 *
 * \return 0 - 成功，返回 0 之外的其它值均失败。
 */
KEXTERN
error_t KPropsLoadPath (TKProps *ptProps, const char* pszFilename);

/*!
 * \brief 从 INI 文件中加载分组的属性字典。一段有效的 INI 内容如下:
 *
 *           # comments goes here.
 *           [group_name]
 *           key1 = value1 # from here it is commedted off.
 *           key2 = value2
 *
 *           ; a semi-colum also indicates a comment line.
 *           [group2]
 *           key_x = value_x
 * 
 * \note  与 KPropsLoadPath() 的区别在于，后者只需要一个文件路径，而本方法则需
 *        要一个已经打开的 TKFile 对象。 TKFile 对象可以造成排他性的文件打开占
 *        用效果，也就是当有人使用了一个 TKFile 对象并打开了某个文件时，其他人
 *        将不再能够对同一路径上的这个文件进行读、写操作。
 *
 * \param ptProps    - 分组属性字典
 * \param ptFile     - INI文件对象
 *
 * \return 0 - 成功，返回 0 之外的其它值均失败。
 */
KEXTERN
error_t KPropsLoadFile (TKProps *ptProps, TKFile *ptFile);

/*!
 * \brief 从内存中的 INI 内容中加载分组的属性字典。
 *
 * 当可以访问在内存中某处存在的一段 INI 内容时，没有必要把这段内存块写入某个文
 * 件而后再加载，可以直接使用本方法来快速加载其中的内容。
 *
 * \note (尤其是针对 windows 应用程序) 如果您使用了 wchar，很抱歉，目前本工具类
 *       还不具有直接从 wchar 内容中解析语法的能力，您需要自己把 wchar 转换成
 *       multi-bytes 的内码后，再行加载。
 *
 * \param ptProps    - 分组属性字典
 * \param pContent   - 内存中的 INI 内容
 * \param uContentBytes  - 需要解析的内容的长度，允许为 0，当为 0 时表示以 '\0'
 *                         结尾的字符串。
 *
 * \return 0 - 成功，返回 0 之外的其它值均失败。
 */
KEXTERN
error_t KPropsLoadContent (TKProps *ptProps,
                           const char *pContent, uint32_t uContentBytes);

/*!
 * \brief 把分组属性字典中的内容按 INI 格式写入一个内存数据块
 * 
 * \param ptProps     - 属性字典
 * \param pBuffer     - 内存块，或者使用 NULL 来查询需要多少字节的内存块。
 * \param uBufferSize - 内存块大小，或者使用 0 来查询需要多少字节的内存块。
 *
 * \return 需要写入或者已经写入 INI 内容的字节数，或者失败。
 */
KEXTERN
uint32_t KPropsSaveContent (TKProps *ptProps,
                            char *pBuffer, uint32_t uBufferSize);

/*!
 * \brief 把分组属性字典写入 INI 文件中
 * 
 * \note  与 KPropsSaveFile() 的区别在于后者需要一个已经打开的 TKFile 对象，
 *        TKFile 对象可以造成排他性的文件打开占用效果，也就是当有人使用了一个
 *        TKFile 对象并打开了某个文件时，其他人将不再能够对同一路径上的这个文件
 *        进行读、写操作。
 *
 * \param ptProps     - 分组属性字典
 * \param pszFilename - 需要写入的 INI 文件路径
 *
 * \return 0 - 成功，返回 0 之外的其它值均失败。
 */
KEXTERN
error_t KPropsSavePath (TKProps *ptProps, const char* pszFilename);

/*!
 * \brief 把分组属性字典写入 INI 文件中
 * 
 * \note  与 KPropsSavePath() 的区别在于，后者只需要一个文件路径，而本方法则需
 *        要一个已经打开的 TKFile 对象。 TKFile 对象可以造成排他性的文件打开占
 *        用效果，也就是当有人使用了一个 TKFile 对象并打开了某个文件时，其他人
 *        将不再能够对同一路径上的这个文件进行读、写操作。
 *
 * \param ptProps    - 分组属性字典
 * \param ptFile     - INI文件对象
 *
 * \return 0 - 成功，返回 0 之外的其它值均失败。
 */
KEXTERN
error_t KPropsSaveFile (TKProps *ptProps, TKFile *ptFile);

/*!
 * \brief 从分组属性字典中按分组取出一个属性的整数值
 *
 * \param [in] ptProps     - 分组属性字典
 * \param [in] pszGroup    - 分组名 (区分大小写的配置项对此有影响)
 * \param [in] pszKey      - 属性名 (区分大小写的配置项对此有影响)
 * \param [in] nDefValue   - 默认值(如果没有这个属性)
 * \param [out] pnValue    - 属性的值
 *
 * \return 0 成功获得了属性值
 *         1 没有找到分组名
 *         2 没有找到属性名
 *        其它值表示失败了。
 */
KEXTERN
error_t KPropsGetInt (TKProps *ptProps, const char* pszGroup, const char* pszKey,
        int32_t nDefValue, int32_t *pnValue);

/*!
 * \brief 从分组属性字典中按分组取出一个属性的字符串值
 *
 * \param [in] ptProps     - 分组属性字典
 * \param [in] pszGroup    - 分组名 (区分大小写的配置项对此有影响)
 * \param [in] pszKey      - 属性名 (区分大小写的配置项对此有影响)
 * \param [in] pszDefValue - 默认值(如果没有这个属性)
 * \param [out] pBuf       - 用来接收属性值的内存块
 * \param [in]  dwBufSize  - 用来接收属性值的内存块的字节大小
 *
 * \return 0 成功获得了属性值
 *         1 没有找到分组名
 *         2 没有找到属性名
 *        其它值表示失败了。
 *
 * How to obtain the size of a key value?
 * Or, how to check existance of a key or a group?
 *   Provide NULL for both pBuff and pszDefValue, and check return value.
 * - If the key is found, the return value is negative, and negate it you
 *   will get the bytes of value in positive (including terminal nill).
 * - If the group is not found, it returns 1.
 * - If the key is not found, but the group is found, it returns 2.
 * - Other errors, it returns a positive FAR LARGER THAN 2.
 *
 * 怎么获得值的字节大小呢？
 * 又或者，怎么检查是否存在一个属性或者分组？
 * 方法:
 *   在 pBuff 和 pszDefValue 处都填 NULL，然后检查返回值：
 *   - 如果找到了属性，返回值为负，其绝对值就是此属性的字节大小（包含了结尾的 '\0'）。
 *   - 如果没有找到分组，返回值为 1 。
 *   - 如果没有找到属性，返回值为 2 。
 *   - 其它的情况（错误情况），返回一个远大于 2 的正整数值。
 */
KEXTERN
error_t KPropsGetString(TKProps *ptProps,
        const char* pszGroup, const char* pszKey,
        const char* pszDefValue, char *pBuf, uint32_t dwBufSize);

/*!
 * \brief  在分组属性字典中设置一个属性的整数值 (int32_t)
 *
 * \param [in] ptProps   - 分组属性字典
 * \param [in] pszGroup  - 分组名 (区分大小写的配置项对此有影响)
 * \param [in] pszKey    - 属性名 (区分大小写的配置项对此有影响)
 * \param [in] nValue    - 需要设置的整数值
 *
 * \return 0 - 成功，返回 0 之外的其它值均失败。
 */
KEXTERN
error_t KPropsSetInt(TKProps *ptProps,
        const char*  pszGroup, const char*  pszKey, int32_t nValue);

/*!
 * \brief  在分组属性字典中设置一个属性的字符串值
 *
 * \param [in] ptProps   - 分组属性字典
 * \param [in] pszGroup  - 分组名 (区分大小写的配置项对此有影响)
 * \param [in] pszKey    - 属性名 (区分大小写的配置项对此有影响)
 * \param [in] pszValue  - 需要设置的字符串
 *
 * \return 0 - 成功，返回 0 之外的其它值均失败。
 */
KEXTERN
error_t KPropsSetString(TKProps *ptProps,
        const char* pszGroup, const char* pszKey, const char* pszValue);

/*!
 * \brief  从分组属性字典中删除一个属性
 *
 * \param [in] ptProps   - 分组属性字典
 * \param [in] pszGroup  - 分组名 (区分大小写的配置项对此有影响)
 * \param [in] pszKey    - 属性名 (区分大小写的配置项对此有影响)
 *
 * \return 0 - 成功，返回 0 之外的其它值均失败。
 */
KEXTERN
error_t KPropsRemoveKey(TKProps *ptProps, const char*  pszGroup, const char*  pszKey);

/*!
 * \brief  从分组属性字典中删除一个分组（以及这个分组下的所有属性）
 *
 * \param [in] ptProps   - 分组属性字典
 * \param [in] pszGroup  - 分组名 (区分大小写的配置项对此有影响)
 *
 * \return 0 - 成功，返回 0 之外的其它值均失败。
 */
KEXTERN
error_t KPropsRemoveGroup(TKProps *ptProps, const char*  pszGroup);

/*!
 * \brief  查询分组属性字典中的分组个数
 *
 * \param [in] ptProps   - 分组属性字典
 * \param [out] pnCount  - 分组数
 *
 * \return 0 - 成功，返回 0 之外的其它值均失败。
 */
KEXTERN
error_t KPropsGetGroupCount(TKProps *ptProps, int32_t* pnCount);

/*!
 * \brief  按索引获得分组的分组名
 *
 * \param  [in] ptProps   - 分组属性字典
 * \param  [in] nIndex    - 分组索引 (从 0 开始)
 * \param [out] pBuf      - 接收分组名的内存块
 * \param  [in] dwBufSize - 接收分组名的内存块的字节大小
 *
 * \return 0 成功
 *         1 分组没有找到
 *        其它值表示失败
 *
 * How to obtain the size of a group name?
 *   Provide NULL for pBuff, and check return value.
 * - If the group is found, the return value is negative, and negate it you
 *   will get the bytes of name in positive (including terminal nill).
 * - If the group is not found, it returns 1.
 * - Other errors, it returns a positive FAR LARGER THAN 1.
 *
 * 怎么知道某个分组的分组名的字节数？
 * 方法：把 pBuff 填 NULL，然后检查返回值:
 * - 如果找到了分组，则返回一个负数，其绝对值即分组名的字节数（含结尾 '\0'）
 * - 如果没有找到，返回 1
 * - 否则，表示其它错误，返回的是一个远大于 1 的正数。
 */
KEXTERN
error_t KPropsGetGroupName(TKProps *ptProps, int32_t nIndex,
        char* pBuf, uint32_t dwBufSize);

/*!
 * \brief  查询分组中的属性个数
 *
 * \param  [in] ptProps  - 分组属性字典
 * \param  [in] pszGroup - 分组名
 * \param [out] pnCount  - 接收查询结果的指针。
 *
 * \return 0 - 成功，返回 0 之外的其它值均失败。
 */
KEXTERN
error_t KPropsGetKeyCount(TKProps *ptProps, const char* pszGroup,
        int32_t* pnCount);

/*!
 * \brief  按索引获得分组下的一个属性名
 *
 * \param  [in] ptProps   - 分组属性字典
 * \param  [in] pszGroup  - 分组名
 * \param  [in] nIndex    - 需要查询的属性在这个分组下的索引（从 0 开始）
 * \param [out] pBuf      - 接收属性名的内存块
 * \param  [in] dwBufSize - 接收属性名的内存块的字节大小
 *
 * \return 0 成功
 *         1 分组不存在
 *         2 属性不存在
 *        其它值表示失败
 *
 * How to obtain the size of a key name?
 *   Provide NULL for pBuff, and check return value.
 * - If the key is found, the return value is negative, and negate it you
 *   will get the bytes of name in positive (including terminal nill).
 * - If the group is not found, it returns 1.
 * - If the key is not found, but the group is found, it returns 2.
 * - Other errors, it returns a positive FAR LARGER THAN 2.
 *
 * 怎么知道某个属性的属性名的字节数？
 * 方法：把 pBuff 填 NULL，然后检查返回值：
 * - 如果属性找到了，返回一个负数，其绝对值表示字节数（包含结尾 '\0'）
 * - 如果分组不存在，返回 1；
 * - 如果属性不存在，返回 2；
 * - 其它情况，表示错误，返回一个远大于 2 的正数。
 */
KEXTERN
error_t KPropsGetKeyName(TKProps *ptProps, const char* pszGroup, int32_t nIndex,
        char* pBuf, uint32_t dwBufSize);

/*!
 * \brief  获得分组的注释
 *
 * \param  [in] ptProps   - 分组属性字典
 * \param  [in] pszGroup  - 分组名
 * \param [out] pBuf      - 接收注释的内存块
 * \param  [in] dwBufSize - 接收注释的内存块的字节大小
 *
 * \return 0 成功
 *         1 分组不存在
 *        其它值表示失败
 *
 * How to obtain the size of a group comment?
 *   Provide NULL for pBuff, and check return value.
 * - If the group is found, the return value is negative, and negate it you
 *   will get the bytes of comment in positive (including terminal nill).
 * - If the group is not found, it returns 1.
 * - Other errors, it returns a positive FAR LARGER THAN 1.
 *
 * 怎么知道注释的字节数？
 * 方法：把 pBuff 填 NULL，然后检查返回值：
 * - 如果分组找到了，返回一个负数，其绝对值表示字节数（包含结尾 '\0'）
 * - 如果分组不存在，返回 1；
 * - 其它情况，表示错误，返回一个远大于 1 的正数。
 */
KEXTERN
error_t KPropsGetGroupComment(TKProps *ptProps, const char* pszGroup,
        char* pBuf, uint32_t dwBufSize);

/*!
 * \brief  为分组追加一段注释
 *
 * \param  [in] ptProps   - 分组属性字典
 * \param  [in] pszGroup  - 分组名
 * \param  [in] pszComment- 待追加的注释
 *
 * \return 0 - 成功，返回 0 之外的其它值均失败。
 */
KEXTERN
error_t KPropsAddGroupComment(TKProps *ptProps, const char* pszGroup,
        const char* pszComment);

/*!
 * \brief  清理分组的所有注释
 *
 * \param  [in] ptProps   - 分组属性字典
 * \param  [in] pszGroup  - 分组名
 */
KEXTERN
void KPropsClearGroupComment(TKProps *ptProps, const char* pszGroup);

/*!
 * \brief  获得属性的注释
 *
 * \param  [in] ptProps   - 分组属性字典
 * \param  [in] pszGroup  - 分组名
 * \param  [in] pszKey    - 属性名
 * \param [out] pBuf      - 接收注释的内存块
 * \param  [in] dwBufSize - 接收注释的内存块的字节数
 *
 * How to obtain the size of a key comment?
 *   Provide NULL for pBuff, and check return value.
 * - If the key is found, the return value is negative, and negate it you
 *   will get the bytes of name in positive (including terminal nill).
 * - If the group is not found, it returns 1.
 * - If the key is not found, but the group is found, it returns 2.
 * - Other errors, it returns a positive FAR LARGER THAN 2.
 *
 * 怎么知道注释的字节数？
 * 方法：把 pBuff 填 NULL，然后检查返回值：
 * - 如果属性找到了，返回一个负数，其绝对值表示字节数（包含结尾 '\0'）
 * - 如果分组不存在，返回 1；
 * - 如果属性不存在，返回 2；
 * - 其它情况，表示错误，返回一个远大于 2 的正数。
 */
KEXTERN
error_t KPropsGetKeyComment(TKProps *ptProps, const char* pszGroup,
        const char* pszKey, char* pBuf, uint32_t dwBufSize);

/*!
 * \brief  清理属性的所有注释
 *
 * \param  [in] ptProps   - 分组属性字典
 * \param  [in] pszGroup  - 分组名
 * \param  [in] pszKey    - 属性名
 */
KEXTERN
void KPropsClearKeyComment(TKProps *ptProps, const char* pszGroup,
        const char* pszKey);

/*!
 * \brief  为属性追加一段注释
 *
 * \param  [in] ptProps   - 分组属性字典
 * \param  [in] pszGroup  - 分组名
 * \param  [in] pszKey    - 属性名
 * \param  [in] pszComment- 待追加的注释
 *
 * \return 0 - 成功，返回 0 之外的其它值均失败。
 */
KEXTERN
error_t KPropsAddKeyComment(TKProps *ptProps, const char* pszGroup,
        const char* pszKey, const char* pszComment);
#ifdef __cplusplus
}
#endif

#endif // KPROP_H
/* vim:set foldmethod=marker: */
