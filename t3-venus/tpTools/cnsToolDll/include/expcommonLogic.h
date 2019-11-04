/*****************************************************************************
模块名      : CExpCommonDlgLogic
文件名      : expcommonlogic.h
相关文件    : 
文件实现功能: 下载（导出）通用弹出界面  如：导出配置、下载日志界面  界面基本相同通过方案区分(移植umstool适用于cnstool)
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/01/28     1.0         刘德印      创建
2013/03/21				   景洋洋      修改移植 
******************************************************************************/
#if !defined(AFX_EXPCOMMONLOGIC_H__CF8FB18A_BC99_46F4_B98F_21441701BA58__INCLUDED_)
#define AFX_EXPCOMMONLOGIC_H__CF8FB18A_BC99_46F4_B98F_21441701BA58__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"


class CExpCommonDlgLogic : public CLogicBase, public ISingleTon<CExpCommonDlgLogic>    
{
public:
	CExpCommonDlgLogic();
	virtual ~CExpCommonDlgLogic();

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

protected:
	bool OnBtnClose( const IArgs & arg );

	/**	 
	* 功能: 下载日志
	* @return   bool
	* @remarks  
	*/
	bool OnBtnDownloadLogWork( const IArgs & arg );
	
	/**	 
	* 功能: 导出cns配置
	* @return   bool
	* @remarks  
	*/
	bool OnBtnExportConfigWork( const IArgs & arg );	
	
	/**	 
	* 功能: 导出摄像机配置
	* @return   bool
	* @remarks  
	*/
	bool OnBtnExportCameraCfg( const IArgs & arg );	

protected: 
	virtual void RegMsg(); 
	virtual void UnRegMsg();
	
	/**	 
	* 功能: 更新下载进度
	* @return   bool
	* @remarks  
	*/
	bool OnDownloadProgress( const IArgs & arg );

	/**	 
	* 功能: 点击浏览
	* @return   bool
	* @remarks  
	*/
	bool OnBtnExportScan( const IArgs & arg );

	/**	 
	* 功能: 点击打开文件目录
	* @return   bool
	* @remarks  
	*/
	bool OnBtnOpenFolder( const IArgs & arg );

		/**	 
	* 功能: 目录发生变化
	* @return   bool
	* @remarks  
	*/
	bool OnFolderEditChange( const IArgs & arg );

	/** 功能:  ftp消息响应
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	HRESULT OnSetFtpInfoRsp( WPARAM wparam, LPARAM lparam );

private:
		/**	 
	* 功能: FTP传输清理
	* @return   bool
	* @remarks  
	*/
	void CleanTransfer();

		/**	 
	* 功能: 下载核心
	* @param    const String strFilePath        [in]     待传输的文件路径
	* @param    const String strCheckFileName   [in]     待传输的文件名 
	* @return   bool
	* @remarks  
	*/
	BOOL DownloadCore(const String& strFilePath, const String& strCheckFileName); 
	BOOL DownLoadLogFile( const String& strFilePath, const String& strCheckFileName );
	BOOL isLogFileExist( string &strSavePath );
	BOOL isCfgFileExist( string &strSavePath );

	/** 功能:  下载日志
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	void DownloadLogWork();

    /** 功能:  导出配置
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
    void ExportConfigWork();

private:
	const String m_strEdtSaveFolder;
	const String m_strProgressExp;

	CFtpCtrl m_cFtp;
	EmFtpStatus m_emFileFtpStatus;
    u32 m_dwTotalFileSize;				//下载文件总大小
	Window* m_pWnd;
	Value_ProgressPos m_valProgress;    //传输进度

	u32 m_nCount;
	u32 m_nCfgCount;
	vector<String> m_vctDownFile;
	vector<String> m_vctDownCfgFile;

	BOOL m_bDownloadLog; //是否下载日志
	BOOL m_bExportConfig;//是否导出配置
};

#define EXPCOMMONLOGICRPTR    CExpCommonDlgLogic::GetSingletonPtr()               //下载（导出）通用弹出界面logic指针

#endif // !defined(AFX_EXPCOMMONLOGIC_H__CF8FB18A_BC99_46F4_B98F_21441701BA58__INCLUDED_)
