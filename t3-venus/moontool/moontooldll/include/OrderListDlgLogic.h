// OrderListDlgLogic.h: interface for the COrderListDlgLogic class.
//
//////////////////////////////////////////////////////////////////////
/*****************************************************************************
文件名      : COrderListDlgLogic.h
相关文件    : 
文件实现功能: 系统配置界面
作者        : 吴蒨蒨
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2014/12/22     1.0         吴蒨蒨      创建
******************************************************************************/
#if !defined(AFX_ORDERLISTDLGLOGIC_H__B06B345C_CF30_42B5_9B64_5F72C61D6269__INCLUDED_)
#define AFX_ORDERLISTDLGLOGIC_H__B06B345C_CF30_42B5_9B64_5F72C61D6269__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

class COrderListDlgLogic : public CLogicBase, public ISingleTon<COrderListDlgLogic> 
{
public:
	COrderListDlgLogic();
	virtual ~COrderListDlgLogic();
	
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

	bool OnBtnImport( const IArgs& args );

	bool OnBtnExport( const IArgs& args );

	bool OnBtnModify( const IArgs& args );

	bool OnBtnInvoke( const IArgs& args );

	bool OnBtnDelete( const IArgs& args );

	bool OnBtnBack( const IArgs& args );

	bool OnClickOrderPosItem( const IArgs& args );

	bool OnClickOrderLstDlgBlack( const IArgs& args );
protected:
	
	HRESULT OnCamPreSetNty( WPARAM wparam, LPARAM lparam );

	HRESULT OnCamPreDelInd( WPARAM wparam, LPARAM lparam );

	HRESULT OnCamPreModifyInd( WPARAM wparam, LPARAM lparam );

	HRESULT OnCamPreSetInd( WPARAM wparam, LPARAM lparam );

	LRESULT OnSnapShotNty( WPARAM wparam, LPARAM lparam );
private:
	/** 功能: 因为占用图片不能被使用，所以采用中间图片来进行交换
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/	
	void SwapImage( );
	/** 功能: 拷贝图片
	*  @param[in] bIsSwaped False  将下载后的图片保存为326*256大小  True 将临时中间图片保存在与服务器同名的快照名称中
	*  @return 
	*  @remarks  
	*/
	bool CopySnapShotImage( bool bIsSwaped );
	/** 功能: 释放图片资源
	*  @param[in] bIsRelOriPic  True 将与服务器同名的快照图片释放 False 释放Temp的中间快照图片
	*  @return 
	*  @remarks  
	*/
	void ReleaseSnapShotImage( bool bIsRelOriPic );
	/** 功能: 删除交换图片资源后，产生的中间快照图片
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/
	void DeleteFile();
	/** 功能: 下载文件
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/
	void DownLoadFile( vector<TTPCamPreOption> &VecTCamPreInfo );
	BOOL DownloadCore(const String & strFileName );
	bool OnDownloadProgress( const IArgs & arg );
	/** 功能: 下释放所有Download文件夹下快照图片资源 
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/
	void ReleaseAllImage( vector<TTPCamPreOption> &VecTCamPreInfo );
	/** 功能: 使用GDI保存图片时，获取不同图片的clsid使用 
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/
	int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
	/** 功能: 将1920*1080图片保存为326*256图片
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/
	bool PictureChange(string strSrcName, string strDestName );
private:
	
	string							m_strLstOrderPos;
	std::vector<TTPCamPreOption>	m_vecTPCamPreInfo;

	TTPCamPre						m_tCamPreSel;
	BOOL							m_bIsSelect;
	CTransparentViewList*			m_pListWnd;	
	std::vector<string>				m_vecDownLoadfile;							//保存下载快照文件
	std::vector<string>				m_vecWaitDownLoad;							//保存等待下载的快照文件
	EmFtpStatus m_emFileFtpStatus;
private:
	CFtpCtrl m_cFtp;
};


#endif // !defined(AFX_ORDERLISTDLGLOGIC_H__B06B345C_CF30_42B5_9B64_5F72C61D6269__INCLUDED_)
