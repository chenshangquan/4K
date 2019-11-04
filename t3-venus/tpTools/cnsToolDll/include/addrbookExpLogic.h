// addrbookExpLogic.h: interface for the AddrbookExpLogic class.
//
//////////////////////////////////////////////////////////////////////
/*****************************************************************************
模块名      : CAddrbookExpLogic
文件名      : addrbookExpLogic.h
相关文件    : 
文件实现功能: 地址簿信息界面
作者        : 景洋洋
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/02/04     1.0         景洋洋      创建
******************************************************************************/

#if !defined(AFX_ADDRBOOKEXPLOGIC_H__07ADDBF0_47EB_4983_B5EA_7E3B34DCDF78__INCLUDED_)
#define AFX_ADDRBOOKEXPLOGIC_H__07ADDBF0_47EB_4983_B5EA_7E3B34DCDF78__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

enum EM_FTPTRANS_TYPE      //文件导入或导出操作
{
	em_FTPTRANS_IMPORT,
	em_FTPTRANS_EXPORT,
};

class CAddrbookExpLogic : public CLogicBase, public ISingleTon<CAddrbookExpLogic>  
{
public:
	CAddrbookExpLogic();
	virtual ~CAddrbookExpLogic();

//CLogicBase
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
	virtual void UnRegFunc( );
	
	/** 功能:  初始化窗口
	*  @param[in] 
	*  @return 
	*  @remarks  在读取xml文件时候调用,根据里面的内容初始化窗口
	*/	
    virtual bool InitWnd( const IArgs & arg ); 
	
	/** 功能:  清理窗口
	*  @param[in] 
	*  @return 
	*  @remarks  在窗口关闭的时候调用,清空窗口数据
	*/		
    virtual void Clear() ;
protected:
		
	/** 功能: 注册消息,接收来自lib库中发送来的消息
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/	
	virtual void RegMsg(); 
		
	/** 功能: 反注册消息,与上面函数相反,注销注册的消息
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/	
	virtual void UnRegMsg();

	/** 功能:  接收服务器的会场信息并更新界面
	*  @param[in] 
	*  @return 成功返回true,失败返回false
	*  @remarks 
	*/
	/** 功能:  ftp消息响应
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	HRESULT OnSetFtpInfoRsp( WPARAM wparam, LPARAM lparam );
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

	/**	 
	* 功能: 导出地址簿
	* @param    const String strCheckFileName   [in]     文件名 
	* @param    String strPath                  [in]     路径
	* @return
	* @remarks  
	*/
	void ExportAddrbook(const String& strCheckFileName, String& strPath);
	
	/**	 
	* 功能: 导入地址簿
	* @param    const String strCheckFileName   [in]     文件名 
	* @param    String strPath                  [in]     路径
	* @return
	* @remarks  
	*/
	void ImportAddrbook(const String& strCheckFileName, String& strPath);

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

	BOOL m_bClickBtnExportAddrbook;     //是否点击了导出地址簿
    BOOL m_bClickBtnImportAddrbook;     //是否点击了导入地址簿

};

#define ADDRBOOKEXPLOGICRPTR    CAddrbookExpLogic::GetSingletonPtr()               //地址簿导入导出logic指针

#endif // !defined(AFX_ADDRBOOKEXPLOGIC_H__07ADDBF0_47EB_4983_B5EA_7E3B34DCDF78__INCLUDED_)
