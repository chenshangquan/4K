/*****************************************************************************
模块名      : CImpCommonDlgLogic
文件名      : impcommondlglogic.h
相关文件    : 
文件实现功能: logic上传（导入）通用弹出界面  如：授权导入、升级相关界面   界面基本相同  通过方案区分
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/01/28     1.0         刘德印      创建
******************************************************************************/
#if !defined(AFX_IMPCOMMONDLGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
#define AFX_IMPCOMMONDLGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

class CImpCommonDlgLogic :public CWndLogicBase, public ISingleTon<CImpCommonDlgLogic>  
{
public:  
    CImpCommonDlgLogic();
	virtual ~CImpCommonDlgLogic();

public:
	void SerSevrIpAddr(u32 dwCurSevr){ m_dwCurSevr = dwCurSevr;};	//设置当前升级服务器地址	
	u32 GetSevrIpAddr(){return m_dwCurSevr;};						//得到当前升级服务器地址
	
	void SetEMEqpType(EMEqpType emEqpTy){m_emEqpTy = emEqpTy;};
	EMEqpType GetEMEqpType(){ return m_emEqpTy;};

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
	* 功能: 导入授权
	* @return   bool
	* @remarks  
	*/
	bool OnBtnImportAuthWork( const IArgs & arg );

	/**	 
	* 功能: 单板升级
	* @return   bool
	* @remarks  
	*/
	bool OnBtnUpgradeBoardWork( const IArgs & arg );

protected: 
	virtual void RegMsg(); 
	virtual void UnRegMsg();
	
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
	void UpdateUpgradeFileList();

private:
	const String m_strEdtSaveFolder;
	const String m_strProgressImp;
	const String m_strLstUpgradeFile;

	CFtpCtrl m_cFtp;
	EmFtpStatus m_emFileFtpStatus;
    u32 m_dwTotalFileSize;				//下载文件总大小
	Window* m_pWnd;
	Value_ProgressPos m_valProgress;    //传输进度

	std::vector<TUmsToolFile> m_vecUpgradeFile;

	String m_strCurTransRemoteFileFullPath;     //当前传输的文件在服务器端的全路径

	EMEqpType m_emEqpTy;				//设置当前待升级板子类型
	CString m_strCurTransFile;	    	//当前升级传输的文件名
	u32 m_dwCurSevr;                    //当前升级服务器
	BOOL m_bReUploadCore;               //若上一次升级失败,是否已经重试  xhx
};

#define IMPCOMMONLOGICRPTR    CImpCommonDlgLogic::GetSingletonPtr()               //上传（导入）通用弹出界面logic指针

#endif // !defined(AFX_IMPCOMMONDLGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
