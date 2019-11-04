// TransparentDlg.h: interface for the CTransparentDlg class.
//
//////////////////////////////////////////////////////////////////////

/*****************************************************************************
模块名      : 透明dialog 
文件名      : TransparentDlg.h
相关文件    : TransparentBaseDlg.h  
文件实现功能:  实现无模板资源的情况下直接创建dlg 
作者        : 俞锦锦
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2012/11/25     1.0         俞锦锦      创建
******************************************************************************/

#if !defined(AFX_TRANSPARENTDLG_H__491179F1_B1F3_4F9A_B7F1_F3E639BFE850__INCLUDED_)
#define AFX_TRANSPARENTDLG_H__491179F1_B1F3_4F9A_B7F1_F3E639BFE850__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "TransparentDlgBase.h"
class CTransparentDlg: public CTransparentDlgBase  
{
public: 
	CTransparentDlg();
	~CTransparentDlg(); 
    
	/*****************************************************************************
	* 功能: 创建对话框
	* @param [in]  strDlgName  窗口名
	* @param [in]  rc  窗口位置大小
	* @param [in]  dwStyle  窗口style， dwExtendedStyle 扩展style
	* @param [in]  pParent 窗口的父窗口
	* @param [in]  bModal  是否为模态窗口
	* @return  BOOL 成功返回TRUE;失败返回FALSE
	* @remarks	 
	-----------------------------------------------------------------------------
	修改记录:
	日  期         版本        修改人      修改内容
	2012/11/25     1.0         俞锦锦      创建
    ******************************************************************************/
	BOOL Create( CString strDlgName, CRect rc,DWORD dwStyle, DWORD dwExtendedStyle, CWnd* pParent = NULL,BOOL bModal = FALSE );  


	/*****************************************************************************
	* 功能: domodal对话框 
	* @return  int  
	* @remarks 调用该接口前需要先调用Create（其中 参数bModal需设置为true） 
	-----------------------------------------------------------------------------
	修改记录:
	日  期         版本        修改人      修改内容
	2012/11/25     1.0         俞锦锦      创建
    ******************************************************************************/
	int  DoModal();


	/*****************************************************************************
	* 功能: domodal对话框	
	* @param [in]  strDlgName  窗口名
	* @param [in]  rc  窗口位置大小
	* @param [in]  dwStyle  窗口style， dwExtendedStyle 扩展style
	* @return  int  
	* @remarks 无需先调用Create，可直接调用
	-----------------------------------------------------------------------------
	修改记录:
	日  期         版本        修改人      修改内容
	2012/11/25     1.0         俞锦锦      创建
    ******************************************************************************/
	int  DoModal(CString strDlgName, CRect rc,DWORD dwStyle, DWORD dwExtendedStyle, CWnd* pParent = NULL);



	/*****************************************************************************
	* 功能: 开始进入modal消息循环，即开始窗口的domodal状态
	* @return  int  
	* @remarks 窗口已经以非模态的形式创建，在此转换为模态形式;
	           需要结束窗口的domodal状态时调用StopModalLoop( int nResult ),
			   其中输入参数nResult即为StartModalLoop的返回值
	-----------------------------------------------------------------------------
	修改记录:
	日  期         版本        修改人      修改内容
	2012/12/30     1.0         俞锦锦      创建
    ******************************************************************************/
	int StartModalLoop();
    

	/*****************************************************************************
	* 功能: 是否已经在modal循环，在StartModalLoop前先做判断，
	        如果当前已经在domal状态，仍再次调用StartModalLoop则domodal会失败
	* @return  int  
	* @remarks 窗口已经以非模态的形式创建，在此转换为模态形式;
	           需要结束窗口的domodal状态时调用StopModalLoop( int nResult ),
			   其中输入参数nResult即为StartModalLoop的返回值
	-----------------------------------------------------------------------------
	修改记录:
	日  期         版本        修改人      修改内容
	2013/2/28     1.0         俞锦锦      创建
    ******************************************************************************/
	BOOL IsInModalLoop();
    
	void StopModalLoop( int nResult );
protected:

	virtual BOOL PreTranslateMessage(MSG* pMsg);       //修正domodal窗口和child窗口弹出   点击回车隐藏问题
private:
    
	//构造dlg模板
	DLGTEMPLATE* ConstructDlgTemp( CRect rc,DWORD dwStyle, DWORD dwExtendedStyle );
	
	//清空dlg模板buffer 
	void ClearDlgTempBuff();

	//打印错误
	void PrtError( CString strErrFun,CString strErr );

	//检验Dlg参数是否合法
    BOOL CheckParam( DWORD& dStyle, CWnd* pParent = NULL, BOOL bModalDlg = FALSE );


 

private: 
	CString m_strTxt;            //dlg 标题
    DLGTEMPLATE *m_pDlgTemp;    //存储dlg模板,主要用于modal类型窗口
    
};

#endif // !defined(AFX_TRANSPARENTDLG_H__491179F1_B1F3_4F9A_B7F1_F3E639BFE850__INCLUDED_)
