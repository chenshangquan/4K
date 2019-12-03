// uiDataMgr.h: interface for the CUIDataMgr class.

/*****************************************************************************
模块名      : 窗口相关的公共数据管理模块
文件名      : uiDataMgr.h
相关文件    : 所有窗口相关的全局数据应存放在此处
文件实现功能: 管理窗口数据
作者        : 俞锦锦
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2012/11/23     1.0         景洋洋      创建
******************************************************************************/


#if !defined(AFX_UIDATAMGR_H__C2E44322_FA60_408C_972F_0701D85D461C__INCLUDED_)
#define AFX_UIDATAMGR_H__C2E44322_FA60_408C_972F_0701D85D461C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "templateClass.h"

//ip的数据结构
typedef struct IP_Struct{  
    //ip地址划分后各个域的值  
    struct IpAdress_Struct  
    {  
        int first;    
        int second;    
        int third;    
        int forth;  
    }IpAdress,*pIPAdress;  
    //ip地址  
    char szIPAdress[MAX_PATH];  
    //子网掩码  
    char szIPMask[MAX_PATH];  
    IP_Struct()  
    {  
        strcpy(szIPAdress,"");  
        strcpy(szIPMask,"");  
    }  
    IP_Struct(char szIPAdress[],char szIPMask[])  
    {  
        strcpy(this->szIPAdress,szIPAdress);  
        strcpy(this->szIPMask,szIPMask);  
    }  
}IP,*pIP;  

class CUIDataMgr:public ISingleTon<CUIDataMgr> 
{
public:
	CUIDataMgr();
	virtual ~CUIDataMgr();

	/*---------------------------------------------------------------------
	* 功    能：向外部窗口发送通知
	* 输入参数：
	* 输出参数：
	* 返 回 值：返回FALSE则发送失败
	* 备    注：  
	* 日期			版本		修改人		修改记录
	* 2012.12.13    1.0         俞锦锦        创建
	----------------------------------------------------------------------*/
	 BOOL NotifyOuterWnd( UINT nMsg , WPARAM wparam, LPARAM lparam );
	/*=============================================================================
    函 数 名:IsFileExist
    功    能:检测文件是否存在
    参    数:const CString& strFileFullPath    [in]     文件全路径名称
    注    意:无
    返 回 值:TRUE: 成功   FALSE:失败
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/12/14  1.0     刘德印    创建
    =============================================================================*/
	 BOOL IsFileExist(const CString& strFileFullPath);

	/*=============================================================================
    函 数 名:IsFolderExist
    功    能:检测目录是否存在
    参    数:const CString& strFolderFullPath    [in]     目录全路径名称
    注    意:无
    返 回 值:TRUE: 成功   FALSE:失败
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/12/14  1.0     刘德印    创建
    =============================================================================*/
	 BOOL IsFolderExist(const CString& strFolderFullPath);

	/*=============================================================================
    函 数 名:IsIniFile
    功    能:检测是否是ini文件用于会议模板和地址文件检测
    参    数:const String& strFileName    [in]     文件全路径名称
    注    意:无
    返 回 值:TRUE: 成功   FALSE:失败
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/12/14  1.0     刘德印    创建
    =============================================================================*/
	 BOOL IsIniFile(const String& strFileName);

	/*=============================================================================
    函 数 名:GetIpStr
    功    能:将普通类型转化为IP串
    参    数:unsigned int dwIPAddr    [in]     IP的整型表示形式
    注    意:无
    返 回 值:类似“127.0.0.1”形式
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/12/14  1.0     刘德印    创建
    =============================================================================*/
	 CString GetIpStr(unsigned int dwIPAddr);

	/*=============================================================================
    函 数 名: GetFileFolderPath
    功    能: 得到文件所在文件夹路径名
    参    数: const String& strFilePath        [in]    文件全路径名
    注    意:无
    返 回 值:String     文件所在文件夹路径名
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2013/01/28  1.0     刘德印    创建
    =============================================================================*/
	 String GetFileFolderPath(const String& strFilePath);

	/*=============================================================================
    函 数 名: OpenBrowseForFolder
    功    能: 浏览打开文件目录（应用在文件保存、下载、导出等）
    参    数: const String& strFileName        [in]    文件名
	参    数: HWND hWnd                        [in]    若为模态对话框，hWnd为父窗口句柄   by xhx
    参    数: BOOL bIsAddFileName              [in]    是否附加文件名   FALSE则直接得到目录名
    注    意:无
    返 回 值:String     文件全路径
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2013/01/28  1.0     刘德印    创建
    =============================================================================*/
	 String OpenBrowseForFolder(const String& strFileName, HWND hWnd = NULL, BOOL bIsAddFileName = TRUE );

	/*=============================================================================
    函 数 名: OpenFileDialog
    功    能: 打开文件目录（应用在文件另存为、导入、打开等）
    参    数: const String& strFilter			  [in]    过滤文件
    参    数: const String& strDefFileName        [in]    默认显示文件名
    参    数: const String& strFilePathName       [out]    文件全路径
    参    数: String strFileName				  [out]    文件名
    参    数: BOOL bOpenStyle					  [in]    标明是浏览还是保存
    注    意:无
    返 回 值:String     文件全路径
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2013/01/28  1.0     刘德印    创建
    =============================================================================*/
	 BOOL OpenFileDialog( const String& strFilter, const String& strDefFileName, String& strFilePathName,
		 String& strFileName, BOOL bOpenStyle = TRUE );

	/*=============================================================================
    函 数 名: OpenMutiFileDlg
    功    能: 打开文件目录（应用在文件另存为、导入、打开等）, 选择多个文件
    参    数: const String& strFilter			  [in]    过滤文件
    参    数: const String& strDefFileName        [in]    默认显示文件名
    参    数: const String& strFilePathName       [out]    文件全路径
    参    数: vector<String>& vecStrFileName	  [out]    全部文件名
    参    数: BOOL bOpenStyle					  [in]    标明是浏览还是保存
    注    意:无
    返 回 值:String     文件全路径
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2013/01/28  1.0     刘德印    创建
    =============================================================================*/
	 BOOL OpenMutiFileDlg( const String& strFilter, const String& strDefFileName, String& strFilePathName,
		 vector<String>& vecStrFileName, BOOL bOpenStyle = TRUE );

	/*=============================================================================
    函 数 名: CheckTransferFile
    功    能: 检测传输全路径和文件名的合法性
    参    数: const String strFileFullPath    [in]     待检测的文件全路径
    参    数: const String strCheckFileName   [in]     待检测的文件名 
    注    意:无
    返 回 值:BOOL
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2013/01/28  1.0     刘德印    创建
    =============================================================================*/
	 BOOL CheckTransferFile( const String& strFileFullPath, const String& strCheckFileName );

	/*=============================================================================
    函 数 名: GetFileSize
    功    能: 得到文件大小
    参    数: const String strFilePath    [in]     文件全路径
    注    意:无
    返 回 值:u64 字节数
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2013/02/01  1.0     刘德印    创建
    =============================================================================*/
	 u64 GetFileSize( const String& strFilePath );
 
	/*=============================================================================
    函 数 名: RecusionMkDir
    功    能: 递归创建目录， 如果目录已经存在或者创建成功返回TRUE
    参    数: CString strFolder        [in]    待创建文件夹路径
    注    意:无
    返 回 值:BOOL
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2013/01/28  1.0     刘德印    创建
    =============================================================================*/
	 BOOL RecusionMkDir(CString strFolder);

	/*=============================================================================
    函 数 名:SetLstSelItem
    功    能: 设置列表控件的选中行（默认去除选中项）
    参    数: const String& strLstWnd        [in]    列表名
	参    数: IWndTree* pWndTree		     [in]    窗口所在
	参    数: s32 nItemNo					 [in]    选中行号
    注    意:无
    返 回 值:BOOL
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2013/01/17  1.0     刘德印    创建
    =============================================================================*/
	 void SetLstSelItem( const String& strLstWnd, IWndTree* pWndTree = NULL, s32 nItemNo = -1 );

	 //是否是正确的密码格式
	 bool IsValidPWStr( CString szPWStr ) ;
	 //是否是正确的会场名称
     bool IsValidNameStr( String strText );
     //判断ip是否合理及获取ip各个域的值
	 bool JudgeIp(char *szIP, IP_Struct::IpAdress_Struct *ipAdress);
     //判断是否同一网段
	 int IsSameNetworkSegment(char *szIPAdress, char *szIPAdresss1, char *szMask);

	 //是否是正确的云服务器账号格式
	 bool IsValidCloudUNStr( CString szPWStr ) ;
	 //是否是正确的云服务器密码格式
     bool IsValidCloudPWStr( CString szPWStr ) ;
	 //字节序转换
	 unsigned int swapInt32(unsigned int value) ;

private:
	

};

#define  UIDATAMGR_PTR CUIDataMgr::GetSingletonPtr()

//主要界面信息
extern const  string g_stcMsgboxDlg;		//警示弹出框
extern const  string g_strMainFrame;		//cnsTool 主界面		
extern const  string g_strBasicInfoDlg;		//基本信息界面		
extern const  string g_strCfgFrame;			//配置框架
extern const  string g_strCfgCnsDlg;		//配置框架中的cns界面
extern const  string g_strCfgAudioPort;		//配置框架中的音频配置界面
//extern const  String g_strCfgMixDlg;		//配置框架中的混音配置界面
extern const  String g_strCfgAudioDlg;		//配置框架中的音频配置界面
extern const  string g_strCfgMainAudioDlg;   //配置框架中的主音频配置界面
extern const  string g_strCfgDemonStrationDlg;   //配置框架中的演示源设置界面
extern const  string g_strCfgAdjustImageDlg;   //配置框架中的图像参数配置界面
extern const  String g_strRenameOptDlg;		//重命名窗口
extern const  string g_strCnsCfg ;        //CNS配置

//extern const  string g_strDiagInfoDlg;		//诊断测试界面
extern const  string g_strCfgDiagnosticFrame;  //诊断测试界面
extern const  string g_strDiagInterfaceDlg;  //接口诊断界面
extern const  string g_strNetDiagnosticDlg;  //网络诊断界面
extern const  string g_strNetPacketDlg;      //网口抓包界面
extern const  string g_strCentCfgFrame;	//中控信息界面
extern const  string g_strDiagInTestInfo;	//输入测试界面
extern const  string g_strDiagOutTestInfo;	//输出测试界面
extern const  string g_strDiagTestFrame;	//诊断测试显示界面
extern const  string g_strDiagStatistic;	//统计界面
extern const  String g_stcStrCfgNetMngDlg;	//网管配置界面
extern const  String g_stcStrCfgNetSecurityDlg;  //网络安全配置界面  
extern const  String g_stcStrRouteCfgDlg;	//路由添加配置界面
extern const  String g_stcStrNetMngOptDlg;	//网管操作界面
extern const  String g_StrCameraDlg;		//摄像调节界面
extern const  String g_strAddrbookExpDlg;	//地址簿界面
extern const  String g_strCfgServerDlg;		//配置框架中的服务器界面
extern const  String g_strCfgEqDlg;			//配置框架中的均衡器界面
extern const  String g_stcStrImpCommonDlg;	//上传（导入）通用弹出界面
extern const  String g_stcStrExpCommonDlg;	//下载（导出）通用弹出界面
extern const  String g_strWarningDlg;		//界面左下角警示界面
extern const  String g_strCfgCallSer;		//呼叫配置界面
extern const  String g_strCfgAdvanceDlg;	//高级配置界面
extern const  String g_strCentAirCondition;	//中控空调界面
extern const  String g_strCentCameraDlg;	//中控摄像机界面
extern const  String g_strCentLightDlg;		//中控灯光界面
extern const  String g_strCentDisplayDlg;	//中控电视机界面
extern const  String g_strCentStatusMesDlg;	//中控状态信息界面
extern const  String g_strCentCurtainDlg;	//中控窗帘配置界面
extern const  String g_strCentDuoVideo;	//中控双流屏配置界面


//主要方案
extern const  string g_strShmShow ; //显示方案, 所有调用该方案的窗口需要将xml的方案名设置为 "SchmShow" 
extern const  string g_strShmHide ; //隐藏方案, 所有调用该方案的窗口需要将xml的方案名设置为 "SchmHide"

#define  ADDRBOOK_FILE_PATH         "/usr/conf/"
#define  ADDRBOOK_FILE_NAME		    "kdvaddrbook.kdv"
#define  CNSLOG_FILE_PATH			"/usr/kdvlog/log/"
#define  CNSLOG_FILE_NAME			"cnlog.ini"
#define  CNSCONFIG_FILE_PATH		"/usr/conf/"
#define  CNSCONFIG_FILE_NAME		"cncfg.ini"
#define  CNSCONFIG_FILE_EXT_PATH	"/usr/"
#define  CNSCONFIG_FILE_NAME_ZERO	"0cncfg.ini"
#define  CNSCONFIG_FILE_NAME_ONE	"1cncfg.ini"
#define  CNSCONF_FILE_PATH			"/usr/bin/"
#define  CNSCAPTURE_FILE_PATH       "/ramdisk/"
#define  REMOTE_FILE_NAME           "/ramdisk/kdvcapture.pcap"
#define  CNS_T300E_TUMP_NAME        "tcpdump.t300e"	
#define  CAPTURE_FILE_NAME          "kdvcapture.pcap"			
#define  CNSUPGRADE_FILE_NAME		"tpcns.bin"
#define  CNSCAMERA_FILE_PATH		"/usr/conf/"
#define  CNSCAMERA_FILE_NAME		"cameracfg.ini"
#define  CNSSNAPSHOT_FILE_PATH		"download"
#define  CNSSNAPSHOT_FILE_NAME1		"snapshot0.jpg"
#define  CNSSNAPSHOT_FILE_NAME2		"snapshot1.jpg"
#define  CNSSNAPSHOT_FILE_NAME3		"snapshot2.jpg"
#define  CNSUPGRADE_NAME			"T300E.bin"
//#define  CNSUPGRADE_NAME_Y			"T300E-y.bin"
#define  CNSUPGRADE_NAME_4K			"T300E-4K.bin"

#define  CAPTURE_FILE_MAX_SIZE      199*1024*1024

#define SOFTWARE_BOUNDARY_VERSION   "V1.1.6"         //ftp用户名密码变更临界版本
//#define  SOFTWARE_BETA_VERSION      6      //做用户名和密码兼容老版本用

#endif // !defined(AFX_UIDATAMGR_H__C2E44322_FA60_408C_972F_0701D85D461C__INCLUDED_)
