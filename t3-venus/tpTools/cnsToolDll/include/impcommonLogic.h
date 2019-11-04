/*****************************************************************************
模块名      : CExpCommonDlgLogic
文件名      : impcommonlogic.h
相关文件    : 
文件实现功能: logic上传（导入）通用弹出界面  如：导入参数、升级相关界面  界面基本相同通过方案区分(移植umstool适用于cnstool)
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/01/28     1.0         刘德印      创建
2013/03/21				   景洋洋      修改移植 
******************************************************************************/
#if !defined(AFX_IMPCOMMONLOGIC_H__31BC88EC_E3B5_47B4_998A_A726B272AD12__INCLUDED_)
#define AFX_IMPCOMMONLOGIC_H__31BC88EC_E3B5_47B4_998A_A726B272AD12__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

class CImpCommonDlgLogic : public CLogicBase, public ISingleTon<CImpCommonDlgLogic>    
{
public:
	CImpCommonDlgLogic();
	virtual ~CImpCommonDlgLogic();

public:  
	/** 功能:  注册回调函数
	*  @param[in] 
	*  @return 
	*  @remarks  在读取xml文件时候,会调用其中注册的函数
	*/
	virtual void RegCBFun();
	/** 功能:  反注册回调函数
	*  @param[in] 
	*  @return 
	*  @remarks  与上面函数相反,注销注册的函数
	*/
	virtual void UnRegFunc();
	/** 功能:  初始化窗口
	*  @param[in] 
	*  @return 
	*  @remarks  在读取xml文件时候调用,根据里面的内容初始化窗口
	*/	
    virtual bool InitWnd( const IArgs & arg ); 

   /**	 
	* 功能:  清空所有状态和数据
	* @return   
	* @remarks	 
	*/
    virtual void Clear();
	
public:
	void SetSevrIpAddr(u32 dwCurSevr){ m_dwCurSevr = dwCurSevr;};	//设置当前升级服务器地址	
	u32 GetSevrIpAddr(){return m_dwCurSevr;};						//得到当前升级服务器地址

public:
	bool OnBtnClose( const IArgs & arg );
	
	/**	 
	* 功能: 更新上传进度
	* @return   bool
	* @remarks  
	*/
	bool OnUploadProgress( const IArgs & arg );

	/**	 
	* 功能: 点击浏览
	* @return   bool
	* @remarks  
	*/
	bool OnBtnImportScan( const IArgs & arg );

	/**	 
	* 功能: 目录发生变化
	* @return   bool
	* @remarks  
	*/
	bool OnFolderEditChange( const IArgs & arg );

	/**	 
	* 功能: 导入摄像机参数
	* @return   bool
	* @remarks  
	*/
	bool OnBtnImportCamCfg( const IArgs & arg );

	/**	 
	* 功能: 导入配置文件
	* @return   bool
	* @remarks  
	*/
	bool OnBtnImportCnsCfg( const IArgs & arg );

	/**	 
	* 功能: cns升级
	* @return   bool
	* @remarks  
	*/
	bool OnBtnUpgradeCns( const IArgs & arg );

	EmFtpStatus GetFtpStatus() { return m_emFileFtpStatus; };

	//ftp超时后对服务器文件的处理
	void ClearTransFile();
	/**	 
	* 功能: 设置超时次数
	* @return  
	* @remarks  
	*/
	void SetTimeOutCount();
	/**	 
	* 功能: 返回超时次数
	* @return   
	* @remarks  
	*/
	u32 GetTimeOutCount();


protected: 
	virtual void RegMsg(); 
	virtual void UnRegMsg();

	/** 功能:  ftp消息响应
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	HRESULT OnSetFtpInfoRsp( WPARAM wparam, LPARAM lparam );
	
private:
		/**	 
	* 功能: 上传核心
	* @param    const String strRemotePath      [in]     linux端待存储路径
	* @param    const String strLocalFile       [in]     待传输的文件全路径 
	* @param    const String strCheckFileName   [in]     待传输的文件名 
	* @return   bool
	* @remarks  
	*/
	BOOL UploadCore( const String& strRemotePath, const String& strLocalFile, const String& strCheckFileName, BOOL bIsDefServ = TRUE ); 

		/**	 
	* 功能: FTP传输清理
	* @return   bool
	* @remarks  
	*/
	void CleanTransfer();
	/**	 
	* 功能: 刷新升级文件列表
	* @return   无
	* @remarks  
	*/
//	void UpdateUpgradeFileList();

	void SetLineFileInfo( String strImpFilePath, String strFileName, int lineNum);

    /**	 
	* 功能: 导入配置
	* @param    const String strCheckFileName   [in]     文件名 
	* @param    String strPath                  [in]     路径
	* @return
	* @remarks  
	*/
	void ImportCnsCfg();

    /**	 
	* 功能: 升级cns
	* @param
	* @return
	* @remarks  
	*/
	void UpgradeCns();


private:
	const String m_strEdtSaveFolder;
	const String m_strProgressImp;
	const String m_strLstUpgradeFile;
	const String m_strStcUpSerName;
	const String m_strStcUpSerName1;
	const String m_strStcUpSerName2;
	const String m_strStcUpSerByte;
	const String m_strStcUpSerByte1;
	const String m_strStcUpSerByte2;

	CFtpCtrl m_cFtp;
	EmFtpStatus m_emFileFtpStatus;
    u32 m_dwTotalFileSize;				//下载文件总大小
	Window* m_pWnd;
	Value_ProgressPos m_valProgress;    //传输进度

	String m_strImpFileName;			//升级T300的文件名称
	String m_strCurTransRemoteFileFullPath;     //当前传输的文件在服务器端的全路径

	CString m_strCurTransFile;	    	//当前升级传输的文件名
	u32 m_dwCurSevr;                    //当前升级服务器
	u32 m_nCount;						//统计超时次数

	vector<String> m_vecStrImpFileName;

	BOOL m_bImportCnsCfg;//是否导入配置
	BOOL m_bUpgradeCns;  //升级
};

#define IMPCOMMONLOGICRPTR    CImpCommonDlgLogic::GetSingletonPtr()               //上传（导入）通用弹出界面logic指针

#endif // !defined(AFX_IMPCOMMONLOGIC_H__31BC88EC_E3B5_47B4_998A_A726B272AD12__INCLUDED_)
