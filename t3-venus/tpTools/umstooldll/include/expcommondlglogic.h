/*****************************************************************************
模块名      : CExpCommonDlgLogic
文件名      : Expcommondlglogic.h
相关文件    : 
文件实现功能: logic下载（导出）通用弹出界面  如：授权导出、下载日志界面  界面基本相同  通过方案区分
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/01/28     1.0         刘德印      创建
******************************************************************************/
#if !defined(AFX_EXPCOMMONDLGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
#define AFX_EXPCOMMONDLGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

class CExpCommonDlgLogic :public CWndLogicBase, public ISingleTon<CExpCommonDlgLogic>  
{
public:  
    CExpCommonDlgLogic();
	virtual ~CExpCommonDlgLogic();

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
	bool OnBtnClose( const IArgs & arg );

	/**	 
	* 功能: 下载日志
	* @return   bool
	* @remarks  
	*/
	bool OnBtnDownloadLogWork( const IArgs & arg );
	
	/**	 
	* 功能: 导出授权
	* @return   bool
	* @remarks  
	*/
	bool OnBtnExportAuthWork( const IArgs & arg );	

	/**	 
	* 功能: 导出ums配置
	* @return   bool
	* @remarks  
	*/
	bool OnBtnExportConfigWork( const IArgs & arg );	

protected: 
	virtual void RegMsg(); 
	virtual void UnRegMsg();

	HRESULT OnExpAuthRsp( WPARAM wparam, LPARAM lparam);
	
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

private:
	const String m_strEdtSaveFolder;
	const String m_strProgressExp;

	CFtpCtrl m_cFtp;
	EmFtpStatus m_emFileFtpStatus;
    u32 m_dwTotalFileSize;				//下载文件总大小
	Window* m_pWnd;
	Value_ProgressPos m_valProgress;    //传输进度

};

#define EXPCOMMONLOGICRPTR    CExpCommonDlgLogic::GetSingletonPtr()               //下载（导出）通用弹出界面logic指针

#endif // !defined(AFX_EXPCOMMONDLGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
