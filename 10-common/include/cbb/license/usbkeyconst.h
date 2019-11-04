/*=======================================================================
模块名      :
文件名      : usbkeyconst.h
相关文件    :
文件实现功能 : usbkey公共宏定义
作者        : 邵云东
版本        : KCMV1.0  Copyright(C) 2003-2008 Suzhou Keda Technology Co.Ltd
                    All rights reserved.
--------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2007/01/11  KCM1.0      邵云东      创建
=======================================================================*/
#ifndef _USBKEYCONST_H
#define _USBKEYCONST_H


// License控制

#define KEDA_AES_KEY						(LPCSTR)"kedacom200606231"			// 保证16位
#define KEDA_COPYRIGHT						(LPCSTR)"Suzhou Keda Technology Co.,ltd. Tel:86-512-68418188, Fax: 86-512-68412699, http://www.kedacom.com"

// 加密内容的长度
#define LEN_KEYFILE_CONT					(u16)512

#define MAXLEN_USBKEY_NAME					(u16)512

//缺省的授权码 （klms.kedacom.com进行md5运算后结果32位结果）
#define DEFAULT_MCULICENSE_AUTHCODE			(LPCSTR)"b2ae4e5afc3619dae447fd23dc0605b2"
#define USB_PATH							(LPCSTR)"USBKEY"					// 写USB标志
#define KEY_VALUE_SEPARETE					(LPCSTR)"&"							// Key-Value对分隔符
#define KEY_VALUE_CONNECTOR					(LPCSTR)"="							// Key-Value连接符

#define KEY_DESCRIPTION_FILE				(LPCSTR)"USBKey.ini"				// Key值描述文件
#define KEY_TYPE_KEY						(LPCSTR)"TYPE"						// Key值类型名
#define VALUE_MIN							(LPCSTR)"MIN"						// 数值型最小值
#define VALUE_MAX							(LPCSTR)"MAX"						// 数值型最大值
#define STRING_LENGTH						(LPCSTR)"LENGTH"					// 字符串型最大长度
#define ENUM_NUM							(LPCSTR)"ITEMNUM"					// 选项型个体数
#define ENUM_ITEM							(LPCSTR)"ITEM"						// 选项型个体
#define DATE_OUT_DATE						(LPCSTR)"MAX"						// 最后日期

#define ERROR_CODE_DESCRIPTION_FILE			(LPCSTR)"licenseError.ini"		// 错误码描述文件
#define ERROR_SEGMENT						(LPCSTR)"ERRORCODE"					// 错误码段名

#define ENCRPT_LENGTH						(LPCSTR)"ENCRPT_LENGTH"				// 信息长度

// 错误码 ////////////////////////////////////////////////////////////////
#define SUCCESS_LICENSE						(u16)0                      // 成功
#define ERR_LICENSE_AUTH_FAILED				(u16)1                      // 授权码验证失败
#define ERR_LICENSE_FORMAT_FAILED			(u16)2                      // 信息格式错误
#define ERR_LICENSE_NO_VER_FAILED			(u16)3                      // 无版本信息
#define ERR_LICENSE_DEV_INFO_FAILED			(u16)4                      // 设备信息不全
#define ERR_LICENSE_ENCRYPT_FAILED			(u16)5                      // 加密失败
#define ERR_LICENSE_WRITEKEY_FAILED			(u16)6                      // 写license文件失败
#define ERR_LICENSE_SMALL_VALUE				(u16)7                      // 数值小于下限
#define ERR_LICENSE_BIG_VALUE				(u16)8                      // 数值大于上限
#define ERR_LICENSE_LONG_STRING				(u16)9                      // 字符串长度大于上限
#define ERR_LICENSE_NO_ITEM_ENUM			(u16)10                     // 没有此选项
#define ERR_LICENSE_OUT_DATE				(u16)11                     // 日期超出期限
#define ERR_LICENSE_NO_KEY					(u16)12                     // 不支持此KEY值
#define ERR_LICENSE_READ_CFG_FAIL			(u16)13                     // 读配置文件失败
#define ERR_LICENSE_INVALID_PARAM			(u16)14                     // 参数非法
#define ERR_LICENSE_NO_KEY_TYPE				(u16)15                     // 不支持此类型
#define ERR_LICENSE_NO_USB_KEY				(u16)16                     // 无USBKEY
#define ERR_LICENSE_USB_CONNECT_FAIL		(u16)17                     // 连接USB设备失败
#define ERR_LICENSE_USB_GET_FAIL			(u16)18                     // 独占USB设备失败
#define ERR_LICENSE_OPENFILE_FAILED			(u16)19                     // 打开文件错误
#define ERR_LICENSE_INVALID_USBKEY			(u16)20                     // License文件与USB设备不符
#define ERR_LICENSE_USB_FORMAT_FAIL			(u16)21                     // 格式化USB设备失败
#define ERR_LICENSE_USB_VERY_PASSWORD		(u16)22                     // 校验USB设备口令失败
#define ERR_LICENSE_USB_CREATE_FILE_FAIL	(u16)23                     // USB设备创建文件失败
#define ERR_LICENSE_USB_OPEN_FILE_FAIL		(u16)24                     // USB设备打开文件失败
#define ERR_LICENSE_USB_DELETE_FILE_FAIL	(u16)25                     // USB设备擦除文件失败
#define ERR_LICENSE_READKEY_FAILED			(u16)26                     // 读license文件失败
#define ERR_LICENSE_TOO_MANY_CHAR           (u16)27                     // 授权信息过长
#define ERR_LICENSE_UNKNOWN					(u16)1000                   // 不明原因的错误
//////////////////////////////////////////////////////////////////////////

// 必须的KEY值 ///////////////////////////////////////////////////////////
#define KEY_LICENSE_FILE_PATH				(LPCSTR)"KEY_LICENSE_FILE_PATH"		// 写License文件路径
#define KEY_LICENSE_KEY						(LPCSTR)"KEY_LICENSE_KEY"			// 许可证编码(36位UUID)
//////////////////////////////////////////////////////////////////////////

#endif // _USBKEYCONST_H
