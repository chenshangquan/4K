/*****************************************************************************
模块名      : CAddrbookExpLogic
文件名      : addrbookexplogic.h
相关文件    : 
文件实现功能: logic地址簿导入导出页面
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2012/12/07     1.0         刘德印      创建
******************************************************************************/
#if !defined(AFX_ADDRBOOKEXPLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
#define AFX_ADDRBOOKEXPLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

class CAddrbookExpLogic :public CWndLogicBase, public ISingleTon<CAddrbookExpLogic> 
{
public:  
    CAddrbookExpLogic();
	virtual ~CAddrbookExpLogic();

public:  
	virtual bool RegCBFun();
	virtual bool UnRegFunc( );
    virtual bool InitWnd( const IArgs & arg );

   /**	 
	* 功能:  清空所有状态和数据
	* @return   
	* @remarks	 
	*/
    virtual void Clear();

protected:
		/**	 
	* 功能:  点击导入地址簿
	* @return   
	* @remarks	 
	*/
	bool OnBtnImportAddrbook( const IArgs & arg );
	
		/**	 
	* 功能:  点击导出地址簿
	* @return   
	* @remarks	 
	*/
	bool OnBtnExportAddrbook( const IArgs & arg );

		 /**	 
	* 功能:  点击导入浏览
	* @return   
	* @remarks	 
	*/	
	bool OnBtnImportAddrbookScan( const IArgs & arg );
	
		 /**	 
	* 功能:  点击导出浏览
	* @return   
	* @remarks	 
	*/
	bool OnBtnExportAddrbookScan( const IArgs & arg );
	
		/**	 
	* 功能:  打开文件目录
	* @return   
	* @remarks	 
	*/	
	bool OnBtnExportFolder( const IArgs & arg );

  /**	 
	* 功能:  更新传输进度
	* @return   
	* @remarks	 
	*/
	bool OnTransAddrbookProgress( const IArgs & arg );

		/**	 
	* 功能: 导入目录发生变化
	* @return   bool
	* @remarks  
	*/
	bool OnImpFolderEditChange( const IArgs & arg );

		/**	 
	* 功能: 导出目录发生变化
	* @return   bool
	* @remarks  
	*/
	bool OnExpFolderEditChange( const IArgs & arg );

protected: 
	virtual void RegMsg(); 
	virtual void UnRegMsg();
	
 
private:
		/**	 
	* 功能: FTP传输清理
	* @return   bool
	* @remarks  
	*/
	void CleanTransfer();

		/**	 
	* 功能: 下载核心
	* @param    const String strCheckFileName   [in]     待传输的文件名 
	* @return   bool
	* @remarks  
	*/
	BOOL DownloadCore(const String& strCheckFileName); 


		/**	 
	* 功能: 上传核心
	* @param    const String strCheckFileName   [in]     待传输的文件名 
	* @return   bool
	* @remarks  
	*/
	BOOL UploadCore(const String& strCheckFileName); 

private:
	const String m_strEdtImport;  
	const String m_strProgressImp;  
	const String m_strEdtExport;
	const String m_strProgressExp; 

	Window* m_pWnd;

	CFtpCtrl m_cFtp;
	EM_FTPTRANS_TYPE m_emFtpTransType;  //当前Logic中导入导出互斥  
	EmFtpStatus m_emFileFtpStatus;      //当前FTP传输状态
    u32 m_dwTotalFileSize;				//导入导出文件总大小
	Value_ProgressPos m_valProgress;    //传输进度

	String m_strCurTransRemoteFileFullPath;     //当前传输的文件在服务器端的全路径

};

#define ADDRBOOKEXPLOGICRPTR    CAddrbookExpLogic::GetSingletonPtr()               //地址簿导入导出logic指针

#endif // !defined(AFX_ADDRBOOKEXPLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
