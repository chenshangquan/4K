/*****************************************************************************
模块名      : sybinterface.lib
文件名      : sybinterface.h
相关文件    : sybinterface.cpp
文件实现功能: sybase数据库访问封装              
作者        : 郑榕
模块版本    : V1.0  Copyright(C) 2002-2005 KDC, All rights reserved.
-----------------------------------------------------------------------------
日  期(y/m/d)      文件版本        创建人      修改内容
2006/02/10          1.0             郑榕         创建
******************************************************************************/

#ifndef _SYB_INTERFACE_H
#define _SYB_INTERFACE_H

#ifdef _MSC_VER
#include <winsock2.h>	
#include <wtypes.h>	
#endif

#ifndef NULL
#define NULL   0
#endif

#include "kdvtype.h"
#include "ctpublic.h"

#define MAX_RECORDCOL_NUM  64   //Table最大列数
#define MAX_COLDATA_WIDTH  513  //数据项最大字节数
#define MAX_SYB_CONNECTIONS 512 //最大连接数

//语言组定义
#define DB_LANG_ENGLISH    "us_english"
#define DB_LANG_CHINESE    "chinese"
#define DB_LANG_TCHINESE   "tchinese"  //繁体中文

//字符集定义
#define DB_CHARSET_ISO1       "iso_1"
#define DB_CHARSET_CP850      "cp850"
#define DB_CHARSET_EUCGB      "eucgb"
#define DB_CHARSET_GB18030    "gb18030"
#define DB_CHARSET_UTF8       "utf8"
#define DB_CHARSET_BIG5       "big5"   //繁体中文字符集

typedef enum
{
    EOpCode_FindRs, //发现新的记录集
	EOpCode_BindDataErr, //绑定数据失败
    EOpCode_CmdErr,   //有命令执行失败
    EOpCode_Finish, //结果集已处理完毕
    EOpCode_OtherErr  //其它错误
}EOpCode;

typedef enum
{
	ERR_SYBCB_CHANNEL_INVALID = 0,  //无效连接
	ERR_SYBCB_OPERATION_TIMEOUT,  //操作超时
	ERR_SYBCB_UNKNOWN      //未知错误
}ESybCbErr;

typedef void (*SybServerCb) (CS_SERVERMSG *SrvMsg, CS_VOID *pCbData);
typedef void (*SybLocalCb) (CS_CLIENTMSG *CtMsg, CS_VOID *pCbData);

typedef struct 
{
	SybServerCb m_CbFunc;
	CS_VOID *m_CbData;
}TSrvCbInfo;

typedef struct 
{
	SybLocalCb m_CbFunc;
	CS_VOID *m_CbData;
}TCtCbInfo;

//全局函数，初始化系统，分配上下文结构
//成功返回true,失败返回false
bool SybInit();

//全局函数，设置本地语言组，字符集
//参数：lpLan 语言组, lpCharSet 字符集
//成功返回true，失败返回false
bool SetDBLocale(LPCSTR lpLang, LPCSTR lpCharSet);

//全局函数，安装CS_Lib消息处理函数，针对所有连接有效
//参数：Fuction 处理函数入口
//成功返回true，失败返回false
bool SetupLibErrFuc(SybLocalCb CbFunc, CS_VOID *pCbData = NULL);

//全局函数，获取回调错误码
ESybCbErr GetCTCbErrCode(CS_CLIENTMSG *CtMsg);

//全局函数，设置操作超时时间
bool SetSybTimeOut(u8 bySec);

//全局函数，获取Buf的字符描述
LPCSTR SybGetStrFromBuf(const void *pBuf, u16 wBufLen, LPSTR lpStr, u16 wStrInLen);

//全局函数，退出系统
//成功返回true,失败返回false
bool SybExit();

class CSybConnection
{
// Constructors/Destruction
public:
    CSybConnection();
    ~CSybConnection();

public:
/*====================================================================
函数名      : ConnecttoSrv
功能        : 建立到数据库服务器的连接
输入参数说明: szUsrName 登陆用户名
              szPwd 密码
			  szDBName 数据库名
              szSrvIP 数据库服务器地址(字符串IP)
              wPort 端口
返回值说明  : 成功true,失败false
====================================================================*/    
    bool ConnecttoSrv(LPCSTR szUsrName,
                      LPCSTR szPwd,
					  LPCSTR szDBName,
                      LPCSTR szSrvIP,
                      u16 wPort = 5000);

/*====================================================================
函数名      : CloseConnection
功能        : 断开到数据库服务器的连接
输入参数说明: 无
返回值说明  : 成功true,失败false
====================================================================*/    
    bool CloseConnection();

/*====================================================================
函数名      : GetCmd
功能        : 获取命令结构指针
输入参数说明: 无
返回值说明  : 命令指针
====================================================================*/    
    CS_COMMAND* GetCmd();

/*====================================================================
函数名      : SetupCtErrFuc
功能        : 安装客户端错误消息处理函数
输入参数说明: Function 函数入口指针
返回值说明  : 成功true,失败false
====================================================================*/    
    bool SetupCtErrFuc(SybLocalCb CbFunc, CS_VOID *CbData = NULL);

/*====================================================================
函数名      : SetupSrvErrFuc
功能        : 安装服务器端错误消息处理函数
输入参数说明: Function 函数入口指针
返回值说明  : 成功true,失败false
====================================================================*/    
    bool SetupSrvErrFuc(SybServerCb CbFunc, CS_VOID *CbData = NULL);

/*====================================================================
函数名      : RemoveCallBack
功能        : 移除该连接上的回调信息
输入参数说明: 无
返回值说明  : 成功true,失败false
====================================================================*/    
    void RemoveCallBack();
	
public:
	BOOL32 m_bIsCurRsEnd;  //当前记录集是否处理完毕
	BOOL32 m_bIsFinish;    //当前命令是否处理结束
	
protected:
    CS_CONNECTION *m_pcConnection;  //CTLib连接结构指针
	CS_COMMAND *m_pcCmd;            //CTLib命令结构指针
	TSrvCbInfo m_tSrvCbInfo;        //服务端回调信息
	TCtCbInfo m_tCtCbInfo;          //客户端回调信息
};

class CSybCmd;
class CSybRs
{
// Constructors/Destruction
public:
    CSybRs();
    ~CSybRs();

public:    
/*====================================================================
函数名      : BindData
功能        : 绑定记录集到程序空间
输入参数说明: 无
返回值说明  : 绑定成功返回true,否则返回false
====================================================================*/    
    bool BindData();

/*====================================================================
函数名      : MoveNext
功能        : 将指针指向结果集下一条记录
输入参数说明: 无
返回值说明  : 成功读出当前行返回true,否则返回false
====================================================================*/    
    bool MoveNext();

/*====================================================================
函数名      : IsEof
功能        : 记录集是否到达末尾
输入参数说明: 无
返回值说明  : 到达末尾返回true,否则false
====================================================================*/    
    bool IsEof();

/*====================================================================
函数名      : GetFieldCount
功能        : 获取结果集列数
输入参数说明: 无
返回值说明  : 结果集列数
====================================================================*/    
    const u16 GetFieldCount();

/*====================================================================
函数名      : GetFieldInfo
功能        : 获取结果集列描述信息
输入参数说明: IN lpColName 列名
              OUT fieldinfo 该列格式描述
返回值说明  : 成功true,失败false
====================================================================*/    
    bool GetFieldInfo(LPCSTR lpColName, CS_DATAFMT& Fieldinfo);

/*====================================================================
函数名      : GetFieldValue
功能        : 获取某列值
输入参数说明: IN lpColName 列名
              OUT Value 该列值  
返回值说明  : 成功true,失败false
====================================================================*/    
    bool GetFieldValue(LPCSTR lpColName, double& Value);

/*====================================================================
函数名      : GetFieldValue
功能        : 获取某列值
输入参数说明: IN lpColName 列名
              OUT Value 该列值  
返回值说明  : 成功true,失败false
====================================================================*/    
    bool GetFieldValue(LPCSTR lpColName, float& Value);

/*====================================================================
函数名      : GetFieldValue
功能        : 获取某列值
输入参数说明: IN lpColName 列名
              OUT Value 该列值  
返回值说明  : 成功true,失败false
====================================================================*/    
    bool GetFieldValue(LPCSTR lpColName, s32& Value);

/*====================================================================
函数名      : GetFieldValue
功能        : 获取某列值
输入参数说明: IN lpColName 列名
              OUT Value 该列值  
返回值说明  : 成功true,失败false
====================================================================*/    
    bool GetFieldValue(LPCSTR lpColName, u32& Value);

/*====================================================================
函数名      : GetFieldValue
功能        : 获取某列值
输入参数说明: IN lpColName 列名
              OUT Value 该列值  
返回值说明  : 成功true,失败false
====================================================================*/    
    bool GetFieldValue(LPCSTR lpColName, s16& Value);

/*====================================================================
函数名      : GetFieldValue
功能        : 获取某列值
输入参数说明: IN lpColName 列名
              OUT Value 该列值  
返回值说明  : 成功true,失败false
====================================================================*/    
    bool GetFieldValue(LPCSTR lpColName, u16& Value);
	
/*====================================================================
函数名      : GetFieldValue
功能        : 获取某列值
输入参数说明: IN lpColName 列名
              OUT Value 该列值  
返回值说明  : 成功true,失败false
====================================================================*/    
    bool GetFieldValue(LPCSTR lpColName, s8& Value);

/*====================================================================
函数名      : GetFieldValue
功能        : 获取某列值
输入参数说明: IN lpColName 列名
              OUT Value 该列值  
返回值说明  : 成功true,失败false
====================================================================*/    
    bool GetFieldValue(LPCSTR lpColName, u8& Value);

/*====================================================================
函数名      : GetFieldValue
功能        : 获取某列值
输入参数说明: IN lpColName 列名
              IN wBufLen 缓存大小
              OUT pstr 该列字串值
返回值说明  : 成功true,失败false
====================================================================*/    
    bool GetFieldValue(LPCSTR lpColName, LPSTR pstr, u16 wBufLen);

/*====================================================================
函数名      : GetFieldValue
功能        : 获取某列值(用户自定义数据块)
输入参数说明: IN lpColName 列名
              IN wBufLen 缓存大小
              OUT pBuf 缓存首地址
			  OUT wOutLen 实际取出数据块的大小
返回值说明  : 成功true,失败false
====================================================================*/    
    bool GetFieldValue(LPCSTR lpColName, void *pBuf, u16 wBufLen, u16 &wOutLen);

/*====================================================================
函数名      : GetFieldValue
功能        : 获取某列值
输入参数说明: IN wIndex 列索引
              OUT Value 该列值  
返回值说明  : 成功true,失败false
====================================================================*/    
    bool GetFieldValue(u8 byIndex, double& Value);

/*====================================================================
函数名      : GetFieldValue
功能        : 获取某列值
输入参数说明: IN wIndex 列索引
              OUT Value 该列值  
返回值说明  : 成功true,失败false
====================================================================*/    
    bool GetFieldValue(u8 byIndex, float& Value);

/*====================================================================
函数名      : GetFieldValue
功能        : 获取某列值
输入参数说明: IN wIndex 列索引
              OUT Value 该列值  
返回值说明  : 成功true,失败false
====================================================================*/    
    bool GetFieldValue(u8 byIndex, s32& Value);

/*====================================================================
函数名      : GetFieldValue
功能        : 获取某列值
输入参数说明: IN wIndex 列索引
              OUT Value 该列值  
返回值说明  : 成功true,失败false
====================================================================*/    
    bool GetFieldValue(u8 byIndex, u32& Value);

/*====================================================================
函数名      : GetFieldValue
功能        : 获取某列值
输入参数说明: IN wIndex 列索引
              OUT Value 该列值  
返回值说明  : 成功true,失败false
====================================================================*/    
    bool GetFieldValue(u8 byIndex, s16& Value);

/*====================================================================
函数名      : GetFieldValue
功能        : 获取某列值
输入参数说明: IN wIndex 列索引
              OUT Value 该列值  
返回值说明  : 成功true,失败false
====================================================================*/    
    bool GetFieldValue(u8 byIndex, u16& Value);

/*====================================================================
函数名      : GetFieldValue
功能        : 获取某列值
输入参数说明: IN wIndex 列索引
              OUT Value 该列值  
返回值说明  : 成功true,失败false
====================================================================*/    
    bool GetFieldValue(u8 byIndex, s8& Value);

/*====================================================================
函数名      : GetFieldValue
功能        : 获取某列值
输入参数说明: IN wIndex 列索引
              OUT Value 该列值  
返回值说明  : 成功true,失败false
====================================================================*/    
    bool GetFieldValue(u8 byIndex, u8& Value);

/*====================================================================
函数名      : GetFieldValue
功能        : 获取某列值
输入参数说明: IN wIndex 列索引
              IN wBufLen 缓存大小
              OUT pstr 该列字串值
返回值说明  : 成功true,失败false
====================================================================*/    
    bool GetFieldValue(u8 byIndex, LPSTR pstr, u16 wBufLen);

/*====================================================================
函数名      : GetFieldValue
功能        : 获取某列值(用户自定义数据块)
输入参数说明: IN wIndex 列索引
              IN wBufLen 缓存大小
              OUT pBuf 缓存首地址
			  OUT wOutLen 实际取出数据块的大小
返回值说明  : 成功true,失败false
====================================================================*/    
    bool GetFieldValue(u8 byIndex, void *pBuf, u16 wBufLen, u16 &wOutLen);

///*====================================================================
//函数名      : CancelCurRs
//功能        : 取消当前记录集
//输入参数说明: 无
//返回值说明  : 成功true,失败false
//====================================================================*/    
//    bool CancelCurRs();

/*====================================================================
函数名      : SetCmdPt
功能        : 设置命令结构指针
输入参数说明: 命令结构指针
返回值说明  : 无
====================================================================*/    
    void SetCmdPt(CSybCmd*, CS_COMMAND*);

/*====================================================================
函数名      : GetBufDesc
功能        : 获取取出的数据块描述符
输入参数说明: out iodesc 数据块描述符
返回值说明  : 成功true,失败false
====================================================================*/    
	bool GetBufDesc(CS_IODESC &iodesc);

protected:
    s16 FindField(LPCSTR lpszName);  //查找列

protected:
    CSybCmd *m_pcSybCmd;  //CSybCmd类指针
    CS_COMMAND *m_pcCommand; //CTLib命令结构指针
    u8 m_abyBuf[MAX_RECORDCOL_NUM*MAX_COLDATA_WIDTH]; //缓存当前行
    CS_DATAFMT m_atFmt[MAX_RECORDCOL_NUM]; //当前记录集的格式信息
	s32 m_dwColNum;   //当前记录集实际列数
    BOOL32 m_bEnd;    //是否到达记录集末尾
};

class CSybCmd
{
// Constructors/Destruction
public:
    CSybCmd(CSybConnection*);
	CSybCmd();
    ~CSybCmd();

public:
/*====================================================================
函数名      : SetConnection
功能        : 指定命令所用连接
输入参数说明: 连接对象指针
返回值说明  : 成功true,失败false
====================================================================*/    
	bool SetConnection(CSybConnection*);

/*====================================================================
函数名      : UseDB
功能        : 打开制定数据库
输入参数说明: szDBName目标数据库名
返回值说明  : 成功true,失败false
====================================================================*/    
    bool UseDB(LPCSTR szDBName);

/*====================================================================
函数名      : ExecSql
功能        : 执行命令类sql语句
输入参数说明: szsql sql字串
返回值说明  : 成功true,失败false
====================================================================*/    
    bool ExecSql(LPCSTR szsql);

/*====================================================================
函数名      : ExecSql
功能        : 执行有记录集返回的sql语句
输入参数说明: szsql sql字串
              pcRecordSet 返回结果集指针
返回值说明  : 成功true,失败false
====================================================================*/    
    bool ExecSql(LPCSTR szsql, CSybRs *pcRecordSet);

/*====================================================================
函数名      : OpenCursor
功能        : 打开游标操作
输入参数说明: lpCursorSql 和游标相关联的查询语句
              pcRecordSet 游标返回的记录集指针
返回值说明  : 成功true,失败false
====================================================================*/    
	bool OpenCursor(LPCSTR lpCursorSql, CSybRs *pcRecordSet);

/*====================================================================
函数名      : UpdateCurRow
功能        : 更新游标当前行
输入参数说明: lpUpdateSql 更新当前行的sql语句
			  lpTableName 和游标相关联的表名 
返回值说明  : 成功true,失败false
====================================================================*/    
	bool UpdateCurRow(LPCSTR lpUpdateSql, LPCSTR lpTableName);

/*====================================================================
函数名      : DelCurRow
功能        : 删除游标当前行
输入参数说明: lpUpdateSql 更新当前行的sql语句
			  lpTableName 和游标相关联的表名
			  特别注意: 当游标涉及多个表时，删除将失败
返回值说明  : 成功true,失败false
====================================================================*/    
	bool DelCurRow(LPCSTR lpTableName);
	
/*====================================================================
函数名      : InsertBuf
功能        : 插入用户自定义的非结构化数据到数据库表中
输入参数说明: lpszSql 获取页指针的Sql语句
		      pcRecordSet 获取返回指针时使用
			  pBuf  数据块首地址
              wBufLen 数据块长度
返回值说明  : 成功true,失败false
====================================================================*/    
    bool InsertBuf(LPCSTR lpszSql, CSybRs *pcRecordSet, const void *pBuf, u16 wBufLen);

/*====================================================================
函数名      : ExecSql
功能        : 执行有多个记录集返回的sql语句
输入参数说明: szsql sql字串
              wleng 字串长
              pcRecordSet 返回结果集指针
返回值说明  : 成功true,失败false
====================================================================*/    
//    EOpCode ExecSqlWithMultiRs(LPCSTR szsql, u16 wleng, CSybRs *pcRecordSet);
	
/*====================================================================
函数名      : GoOnProcRes
功能        : 继续处理结果集
输入参数说明: bIsClear 是否清除当前结果集
			  用户无需关心此参数，全部使用默认值即可
返回值说明  : EOpCode_FindRs 发现新的记录集
              EOpCode_Finish 结果集已处理完毕
			  EOpCode_BindDataErr 数据邦定失败
              EOpCode_CmdErr 发现某条命令执行失败
====================================================================*/    
    EOpCode GoOnProcRes(bool bIsClear = false); 

/*====================================================================
函数名      : GetAffectedRowCount
功能        : 获取本次命令作用的记录条数
输入参数说明: 无
返回值说明  : 记录条数
====================================================================*/    
	u32 GetAffectedRowCount();

///*====================================================================
//函数名      : ClearResults
//功能        : 清除所有结果
//输入参数说明: 无
//返回值说明  : 成功true,失败false
//====================================================================*/    
//    bool ClearResults();

/*====================================================================
函数名      : IsCurRsEnd
功能        : 判断当前记录集是否已处理完毕
输入参数说明: 无
返回值说明  : 处理完毕返回true,否则false
====================================================================*/    
    bool IsCurRsEnd();

    //以下两友元为了修改标志位m_bIsCurRsEnd
//    friend bool CSybRs::CancelCurRs();
    friend bool CSybRs::MoveNext();

private:
/*====================================================================
函数名      : SendSql
功能        : 发送命令串
输入参数说明: szsql 命令串
返回值说明  : 发送成功true,失败false
====================================================================*/    
    bool SendSql(LPCSTR szsql); 

protected:
    CSybRs *m_pcSybRs;    //当前结果集容器
	CS_COMMAND *m_pcCommand;  //CTLib命令结构指针
    BOOL32 *m_pbIsCurRsEnd;   //当前记录集是否处理完毕
	BOOL32 *m_pbIsFinish;    //当前命令是否处理结束
	u32 m_dwEffectRows;    //当前命令生效的记录条数
};

#endif
