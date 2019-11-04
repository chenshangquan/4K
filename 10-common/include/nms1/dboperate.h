/********************************************************************
模块名:      数据库操作函数库
文件名:      DBOperate.h
相关文件:    
文件实现功能 操作接口实现头文件
作者：       
版本：       4.0
------------------------------------------------------------------------
修改记录:
日		期	版本	修改人	走读人	修改内容
2005/08/22	4.0		任厚平

*********************************************************************/

#if !defined(AFX_DBOPERATE_H__C01764B0_66E9_471B_9931_62802DDD3E83__INCLUDED_)
#define AFX_DBOPERATE_H__C01764B0_66E9_471B_9931_62802DDD3E83__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning( disable : 4146)

#import "C:\Program Files\Common Files\System\ADO\msado15.dll"\
	no_namespace \
rename("EOF","ISEOF")


#include <winsock2.h>
#pragma comment(lib, "ws2_32")
#include "kdvtype.h"

//一些宏定义

#define  VOD_OK                 (u16)0    //VOD库操作成功 
#define  VODERR_BASE_CODE		(u16)20000//错误码基准值


//登录时，身份验证失败
#define VODERR_DB_INDENTIFY_METHOD			(u16)(VODERR_BASE_CODE + 1) 
//检索类组信息失败
#define VODERR_DB_LOADCLASSINFO_METHOD		(u16)(VODERR_BASE_CODE + 2) 
//检索类组中的文件信息失败
#define VODERR_DB_LOADFILEINFO_METHOD		(u16)(VODERR_BASE_CODE + 3) 
//检索类类别的权限信息
#define VODERR_DB_LOADPOPINFO_METHOD		(u16)(VODERR_BASE_CODE + 4) 
//更改用户登陆密码
#define VODERR_DB_CHANGEPWD_METHOD			(u16)(VODERR_BASE_CODE + 5) 
//更新组的权限集
#define VODERR_DB_UPDATEPOPS_METHOD			(u16)(VODERR_BASE_CODE + 6) 
//检索日志信息失败
#define VODERR_DB_LOADLOGINFO_METHOD		(u16)(VODERR_BASE_CODE + 7) 
//增加一条点播记录
#define VODERR_DB_ADDONELOG_METHOD			(u16)(VODERR_BASE_CODE + 8) 
//删除一条点播记录
#define VODERR_DB_DELONELOG_METHOD			(u16)(VODERR_BASE_CODE + 9) 
//增加一条文件发布记录
#define VODERR_DB_ADDONEPUB_METHOD			(u16)(VODERR_BASE_CODE + 10)
//更新一条文件发布记录
#define VODERR_DB_UPDATEONEPUB_METHOD		(u16)(VODERR_BASE_CODE + 11) 
//删除一条文件发布记录
#define VODERR_DB_DELONEPUB_METHOD			(u16)(VODERR_BASE_CODE + 12) 
//增加一条文件柜记录
#define VODERR_DB_ADDONECLASS_METHOD		(u16)(VODERR_BASE_CODE + 13)
//更新一条文件柜记录
#define VODERR_DB_UPDATEONECLASS_METHOD		(u16)(VODERR_BASE_CODE + 14) 
//删除一条文件柜记录
#define VODERR_DB_DELONECLASS_METHOD		(u16)(VODERR_BASE_CODE + 15) 
//检索用户信息失败
#define VODERR_DB_LOADUSERINFO_METHOD		(u16)(VODERR_BASE_CODE + 16) 
//增加一条用户记录
#define VODERR_DB_ADDONEUSER_METHOD			(u16)(VODERR_BASE_CODE + 17)
//更新一条用户记录
#define VODERR_DB_UPDATEONEUSER_METHOD		(u16)(VODERR_BASE_CODE + 18) 
//删除一条用户记录
#define VODERR_DB_DELONEUSER_METHOD			(u16)(VODERR_BASE_CODE + 19) 
//更新一条用户的停用、启用记录标记
#define VODERR_DB_SETONEUSERFLAG_METHOD		(u16)(VODERR_BASE_CODE + 20)
//更新一条点播记录
#define VODERR_DB_UPDATEONEPLAYLOG_METHOD   (u16)(VODERR_BASE_CODE + 21)
//查询当前点播人数
#define VODERR_DB_QUERYNUMOFPLAYING_METHOD	(u16)(VODERR_BASE_CODE + 22);


//设置文件发布的数据库操作参数无效
#define VODERR_OPEN_DB_PARAM				(u16)(VODERR_BASE_CODE + 47) 
//打开数据库连接的操作失败
#define VODERR_OPEN_DB						(u16)(VODERR_BASE_CODE + 48) 
//数据库没有进行连接操作，仍处于关闭状态
#define VODERR_DB_CLOSE_STATUS				(u16)(VODERR_BASE_CODE + 49) 


//发布文件操作失败
#define VODERR_DB_INSERT_METHOD				(u16)(VODERR_BASE_CODE + 50) 
//取消发布文件操作失败
#define VODERR_DB_CANCEL_METHOD				(u16)(VODERR_BASE_CODE + 51) 
//查询文件发布状态操作失败
#define VODERR_DB_QUERY_METHOD				(u16)(VODERR_BASE_CODE + 52) 
//更新文件发布状态操作失败
#define VODERR_DB_UPDATE_METHOD				(u16)(VODERR_BASE_CODE + 53) 

#define MAX_LIST_PAGE_SIZE		10


//DBOperate类定义

class CDBOperate  
{
public:
	CDBOperate();
	virtual ~CDBOperate();

public:
	/*=============================================================================
	函 数 名：OpenDB
	功    能：打开数据库
	参    数：szHostIP
			  szUserName
			  szPwd
			  wPort = 1433          
	返 回 值：WORD      : 返回VOD_OK 表示操作成功，
	=============================================================================*/
	virtual u16 OpenDB(CString &szHostIP, CString &szUserName, CString &szPwd, u16 wPort = 1433);
	/*=============================================================================
	函 数 名：CloseDB
	功    能：关闭数据库
	参    数：无	           
	返 回 值：WORD
	=============================================================================*/
	virtual u16 CloseDB();
	/*=============================================================================
	函 数 名：GetErrorDescript
	功    能： 
	参    数：无	           
	返 回 值：CString
	=============================================================================*/
	 virtual CString GetErrorDescript();
	/*=============================================================================
	函 数 名：PublishOneFile
	功    能：
	参    数：szFilePath
	          szFileName
			  bSecret
	返 回 值：WORD
	=============================================================================*/
	
	virtual u16 PublishOneFile(char *szFilePath, char *szFileName, u32 dwFileSize, char *szPublishTime, BOOL bSecret);
	/*=============================================================================
	函 数 名：CancelOnePublishedFile
	功    能：
	参    数：szFilePath
			  szFileName
	返 回 值：WORD
	=============================================================================*/
	
	virtual u16 UpdatePublishOneFile(char *szFilePath, char *szFileName, u32 dwFileSize);
	/*=============================================================================
	函 数 名：UpdateOnePublishedFile
	功    能：
	参    数：szFilePath
			  szFileName
	返 回 值：WORD
	=============================================================================*/

	virtual u16 CancelOnePublishedFile(char *szFilePath, char *szFileName);
	/*=============================================================================
	函 数 名：QueryOneFileStauts
	功    能：
	参    数：szFilePath
			  szFileName
			  bPublished
	返 回 值：WORD
	=============================================================================*/
	virtual u16 QueryOneFileStauts(char *szFilePath, char *szFileName, BOOL &bPublished);	 


private:
	_ConnectionPtr m_pCon;		//数据库连接变量
	
	CString m_szErrorInfo;

	CRITICAL_SECTION  m_csdbLock;

//	static BOOL m_bComInited;
	
	BOOL m_bWSAInited;
};
#endif // !defined(AFX_DBOPERATE_H__C01764B0_66E9_471B_9931_62802DDD3E83__INCLUDED_)
