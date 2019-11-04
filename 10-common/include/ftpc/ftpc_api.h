/****************************************************************************** 
模块名: FTPC
文件名: ftpc_api.h 
功能  : 
ftp库头文件 版本： 
******************************************************************************/

#ifndef _FTPC_API_H
#define _FTPC_API_H 

#include "kdvtype.h"

#ifdef __cplusplus 
extern "C" { 
#endif 

//api返回值
#define FTPC_ERR                    -1  //出错
#define FTPC_OK                 (s32)0   //正常
#define FTPC_PARAMERR           (s32)1   //传递的参数错误
#define FTPC_CREATESOCKERR      (s32)2   //创建socket失败
#define FTPC_GETOPTERR          (s32)3   //获取option选项是失败
#define FTPC_SETOPTERR          (s32)4   //设置option选项失败
#define FTPC_SELECTERR          (s32)5   //select调用失败
#define FTPC_CONNECTIMEOUT      (s32)6   //连接超时
#define FTPC_CONNECTREFUSEDERR  (s32)7   //连接被拒绝
#define FTPC_CONNECTFAILED      (s32)8   //获取server连接状况失败
#define FTPC_PASSERR            (s32)9   //密码错误
#define FTPC_USERNAMEERR        (s32)10  //用户名出错
#define FTPC_PASVMODEERR        (s32)11  //传递pasv信令错误
#define FTPC_SIZEGETERR         (s32)12  //获取文件size失败
#define FTPC_RETRCOMERR         (s32)13  //传递下载信令失败
#define FTPC_THREADERR          (s32)14  //创建线程失败
#define FTPC_SEMERR             (s32)15  //信号量操作失败
#define FTPC_FILESTATERR        (s32)16  //获取文件属性失败
#define FTPC_CWDCOMERR          (s32)17  //传递cwd信令失败
#define FTPC_STORCOMERR         (s32)18  //传递stor信令失败
#define FTPC_ALLOCOMERR         (s32)19  //传递allo信令失败
#define FTPC_MEMMALLOCERR       (s32)20  //malloc memory失败
#define FTPC_OPENFILEERR        (s32)21  //打开文件出错
#define FTPC_FILE_NOT_FINISH    (s32)22  //上一个文件未传输完成
#define FTPC_CONNECTERR         (s32)23  //connect调用出错
#define FTPC_RESTCOMERR         (s32)24  //传递REST消息失败
#define FTPC_DELECOMERR         (s32)25  //删除文件消息失败
#define FTPC_COMMANDRCVERR      (s32)26  //接收respond消息失败
#define FTPC_SENDCOMMANDERR     (s32)27  //发送命令失败
#define FTPC_MKDERR             (s32)28  //创建目录失败
#define FTPC_RMDERR             (s32)29  //删除目录失败

//回调消息类型(对应回调函数参数 s32 dwMsgType)
#define FTPC_TRANSFILEERR       (s32)100 //与服务器传输文件出错
#define FTPC_LOCALFILEERR       (s32)101 //写或读本地文件出错
#define FTPC_MEMSPACELACK       (s32)102 //分配的给内存不足
#define FTPC_TRANSPERCENT       (s32)103 //文件已传输百分比消息
#define FTPC_FINISHED           (s32)104 //文件传输完成消息
#define FTPC_STOP_SEND_DATA     (s32)105 //主动停止发送数据


//回调函数参数结构定义
typedef struct 
{
	s32 dwMsgType;		        //消息类型
	union
	{
		u32 dwTransPercent;     //对应 msgType = FTPC_TRANSPERCENT 数据结构	    
		u32 dwMsgDescripton;    //获取的文件size
	}UMsgInfo;
	void *pUserData; 
}TFtpcCallback;			

//回调函数定义
typedef void (*CBFtpcCallbackFun)(TFtpcCallback *PTParam);


/*=============================================================================
函 数 名：FTPCSetServAddr
功    能：设置服务器端的ip地址和端口

注    意：传入的第一个参数是网络地址字符串，是点分二进制形式
算法实现：将网络地址和端口设置到全局变量

全局变量：无
参数说明：
@param：s8  *pwServIp  -    服务器IP网络地址字符串
@param：u16 wServPort  -    服务器端口号
返 回 值： s32   FTPC_OK   成功； FTPC_PARAMERR   失败
=============================================================================*/
s32 FTPCSetServAddr(const s8 *paServIp, const u16 wServPort);

/*=============================================================================
函 数 名：FTPCSetLogId
功    能：设置登陆用户名和密码

注    意：如果是匿名(anonymous),任何密码皆可
算法实现：传登陆的用户名和密码设置模块的全局变量
全局变量：无
参    数：
@param: s8  *paUserName   -     登陆用户名
@param: s8  *pwPassword   -     登陆密码
返 回 值： s32   FTPC_OK   成功； FTPC_PARAMERR   失败
=============================================================================*/
s32 FTPCSetLogId(const s8 *paUserName, const s8 *paPassword);

/*=============================================================================
函 数 名： FTPCGetFileinMem
功    能： 1. 设置文件的下载模式为内存
           2. 设置服务器文件文件名和路径
           3. 下载文件并存放在内存中
注    意：
算法实现： 通过FTP RETR取得文件，将文件保存在pwMemBuf内存中
全局变量：
参数说明：
@param:   s8  *pwServpath   -   文件路径
@param:   s8  *pwFileName    -  文件名
@param:   s8  *pwMemBuf     - 存放文件起始地址
@param:   u32 dwMemSize     -本模块可用内存大小
返 回 值： s32   FTPC_OK   成功;失败见api返回值的宏定义

特殊说明： 文件传输采用异步模式，传输过程中会通过回调将文件传输的进度返回给上层
=============================================================================*/
s32 FTPCGetFileinMem(const s8 *paServpath, const s8 *paFileName, s8 *pwMemBuf, u32 dwMemSize) ;

/*=============================================================================
函 数 名：  FTPCGetFileinFlash
功    能：  1. 设置文件的下载模式为flash
            2. 设置服务器文件文件名和路径
            3. 下载文件并存放在flash中

注    意：
算法实现：  通过FTP RETR取得文件，将文件保存在paLocalPath FLASH中
全局变量：
参数说明：
@param:   s8    *pwServpath   -     服务器文件路径
@param:   s8    *pwFileName   -     服务器文件名
@param:   s8    *pwLocalPath  -     本地存放路径，包含文件名
返 回 值：s32   FTPC_OK   成功   失败见api返回值的宏定义
特殊说明：文件传输采用异步模式，传输过程中会将传输的进度返回给上层
=============================================================================*/
s32 FTPCGetFileinFlash(const s8 *paServpath, const s8 *paFileName, const s8 *paLocalPathFile) ;

/*=============================================================================
函 数 名：  FTPCUploadFile
功    能：  1、设置上传文件的路径文件名
            2、上传文件                        

注    意：
算法实现：  通过FTP STOR上传文件
全局变量：
参数说明：
@param:   s8    *pwServpath   -     服务器文件路径
@param:   s8    *paServFileName -   服务器存放的文件名
@param:   s8    *pwFileName   -     本地文件名
@param:   s8    *pwLocalPath  -     本地路径
返 回 值：s32   FTPC_OK   成功   失败见api返回值的宏定义
特殊说明：文件传输采用异步模式，传输过程中会将传输的进度返回给上层
=============================================================================*/
s32 FTPCPutFile(const s8 *paServpath, const s8 *paServFileName, const s8 *paFileName, const s8 *paLocalPath) ;

/*=============================================================================
函 数 名：  FTPCUploadMemData
功    能：  1、设置上传内存数据地址
            2、上传文件                        

注    意：
算法实现：  通过FTP STOR上传文件
全局变量：
参数说明：
@param:   s8    *pwServpath   -     服务器文件路径
@param:   s8    *paServFileName -   服务器存放的文件名
@param:   s8    *pwMemAddr   -     本地数据地址
@param:   u32  *dwMemSize  -     本地路径
返 回 值：s32   FTPC_OK   成功   失败见api返回值的宏定义
=============================================================================*/
s32 FTPCPutMemData(const s8 *paServpath, const s8 *paServFileName, const s8 *paMemAddr, const s32 dwMemSize) ;
/*=============================================================================
函 数 名：  FTPCPutSerielData
功    能：  1、设置上传内存数据地址
                        2、用于对同一个文件进行追加上传                   

注    意：
算法实现：  通过FTP STOR上传文件
全局变量：
参数说明：
@param:   s8    *pwServpath   -     服务器文件路径
@param:   s8    *paServFileName -   服务器存放的文件名
@param:   s8    *pwMemAddr   -     本地数据地址
@param:   u32  *dwMemSize  -       数据长度
@param:   void *pUserData  -        用户写入回调信令
返 回 值：s32   FTPC_OK   成功   失败见api返回值的宏定义
=============================================================================*/
s32 FTPCPutSerielData(const s8 *paServpath, const s8 *paServFileName, const s8 *paMemAddr, const u32 dwMemSize, void *pUserData);


/*======================================================
函 数 名：	FTPCDelFile
功    能：	ftpc模块删除服务器上某文件
算法实现：
参数说明：	无	 
返 回 值：	FTPC_OK  成功       FTPC_ERROR  失败	
--------------------------------------------------------
修改记录：
	日期	版本	修改人	走读人	修改记录
========================================================*/
s32 FTPCDelFile(const s8 *paServpath, const s8 *paFileName);

/*======================================================
函 数 名 :	FTPCMkdir
功    能 :	ftpc模块在服务器上创建目录
算法实现 :
参数说明 :
@param   :   s8    *paServpath   -     服务器文件路径
返 回 值 :   s32   FTPC_OK   成功   FTPC_ERROR、FTPC_TIMEOUT、FTPC_LOGERR    失败
--------------------------------------------------------
修改记录 :
	日期	版本	修改人	走读人	修改记录
========================================================*/
s32 FTPCMkdir(const s8 *paServpath);


/*=============================================================================
函 数 名：  FTPCReset
功    能：  清除模块所有初始设置

注    意：
算法实现：
全局变量：  无    
参    数：  无
返 回 值：  s32   FTPC_OK   成功； FTPC_ERROR   失败
=============================================================================*/
s32 FTPCReset(void);

/*====================================================================
函 数 名：  FTPCRegCallback
功    能：  注册分配地址的回调函数
算法实现：
全局变量：  无
参数说明：
@param:     CBFtpcCallbackFun fun  -   回调函数
返 回 值：  s32   FTPC_OK   成功；     FTPC_PARAMERR失败
=============================================================================*/
s32 FTPCRegCallback(CBFtpcCallbackFun fun);

/*====================================================================
函 数 名：  FTPCUnRegCallback
功    能：  注销分配和收回地址的回调函数
算法实现：
全局变量：  无
参数说明：  N/A
返 回 值：  s32   FTPC_OK   成功
=============================================================================*/
s32 FTPCUnRegCallback(void);

/*=============================================================================
函 数 名：FtpcGetVersion
功    能：获取ftpc版本号

注    意：dwBufLen 字符长度应大于或等于256
算法实现：

全局变量：无
参数说明：
@param：s8 *pchVer: -- 字符指针
@param：u32 dwBufLen: -- 字符长度

返 回 值： s32    FTPC_OK   成功； FTPC_PARAMERR   失败
=============================================================================*/
s32 FtpcGetVersion(s8 *pchVer, u32 dwBufLen);

/*=============================================================================
函 数 名：  FTPCInit
功    能：  初始化FTPC模块
            
注    意：  
算法实现：  
全局变量：  无
参    数：  无
返 回 值：  u32  FTPC_OK   成功            FTPC_ERROR   失败
=============================================================================*/
s32 FTPCInit(void);

/*======================================================
函 数 名：	FTPCSetMem
功    能：	ftpc模块申请一块内存
算法实现：
参数说明：	无	 
返 回 值：	FTPC_OK  成功       FTPC_MEMMALLOCERR  失败	
--------------------------------------------------------
修改记录：
	日期	版本	修改人	走读人	修改记录
========================================================*/
s32 FTPCSetMem(u32 dwMemLen);

/*======================================================
函 数 名：	FTPCFreeMem
功    能：	ftpc模块释放内存
算法实现：
参数说明：	无	 
返 回 值：	FTPC_OK  成功       FTPC_ERROR  失败	
--------------------------------------------------------
修改记录：
	日期	版本	修改人	走读人	修改记录
========================================================*/
s32 FTPCFreeMem(void);

/*======================================================
函 数 名：	FTPCSetSendDelay
功    能：	ftpc模块设置发送延时
算法实现：
参数说明：	dwDelayTime send的延时时间(单位:微秒)
返 回 值：	FTPC_OK  成功       FTPC_ERROR  失败	
--------------------------------------------------------
修改记录：
	日期	版本	修改人	走读人	修改记录
========================================================*/
s32 FTPCSetSendDelay(s32 dwDelayTime);

/*======================================================
函 数 名 :	FTPCStopSend
功    能 :	ftpc模块停止发送
算法实现 :
参数说明 :
返 回 值 :	FTPC_OK  成功       FTPC_ERROR  失败	
--------------------------------------------------------
修改记录 :
	日期	版本	修改人	走读人	修改记录
========================================================*/
s32 FTPCStopSend(void);

/*======================================================
函 数 名 :	FTPCCloseAll
功    能 :	ftpc模块关闭所有连接
算法实现 :
参数说明 :	
返 回 值 :	FTPC_OK  成功       FTPC_ERROR  失败	
--------------------------------------------------------
修改记录 :
	日期	版本	修改人	走读人	修改记录
========================================================*/
s32 FTPCCloseAll(void);

/*======================================================
函 数 名 :	FTPCDebug
功    能 :	ftpc模块打开调试开关
算法实现 :
参数说明 :
@param：u8 nOn: -- 是否打开
返 回 值 :	FTPC_OK  成功       FTPC_ERROR  失败	
--------------------------------------------------------
修改记录 :
	日期	版本	修改人	走读人	修改记录
========================================================*/
s32 FTPCDebug(u8 nOn);

#ifdef __cplusplus
}
#endif

#endif


