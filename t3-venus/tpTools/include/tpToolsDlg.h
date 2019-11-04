/*****************************************************************************
模块名      : CTpToolsDlg
文件名      : tpToolsDlg.h
相关文件    : 
文件实现功能: tptool登陆控制模块
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2012/11/30     1.0         刘德印      创建
******************************************************************************/
#if !defined(AFX_TPTOOLSDLG_H__2D9E8A35_54C7_4086_90FE_8DE8BF4FEF74__INCLUDED_)
#define AFX_TPTOOLSDLG_H__2D9E8A35_54C7_4086_90FE_8DE8BF4FEF74__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTpToolsDlg dialog

class CTpToolsDlg : public CTransparentDlgBase
{
// Construction
public:
	CTpToolsDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTpToolsDlg)
	enum { IDD = IDD_TPTOOLS_DIALOG };
	CTransparentStatic	m_stUmsTab;
	CTransparentStatic	m_stCnsTab;
//	CTransparentStatic  m_stMoonTab;
	CTransparentStatic	m_stVersion;
	CTransparentStatic	m_stCoryRight;
	CTransparentBtn	m_btnMin;
	CTransparentBtn	m_btnClose;
	CTransparentBtn	m_btnLogin;
	CTransparentCheckButton	m_btnRadioUms;
	CTransparentCheckButton	m_btnRadioCns;
	//CTransparentCheckButton m_btnRadioMoon;
	CTransparentStatic	m_stWarningIcon;
	CTransparentStatic	m_stWarningText;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTpToolsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTpToolsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBtnClose();
	afx_msg void OnBtnMin();
	afx_msg void OnBtnSetting();
	afx_msg void OnBtnLogin();
	afx_msg void OnRadioUms();
	afx_msg void OnRadioCns();
	//afx_msg void OnRadioMoon();
	afx_msg LRESULT OnComboClickListIcon( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnIpAddrChange( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnComboClickList( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnLoginResult( WPARAM wParam, LPARAM lParam );	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	/*=============================================================================
    函 数 名:InitControl
    功    能:初始化界面控件
    参    数:无
    注    意:无
    返 回 值:TRUE 成功;FALSE 失败 
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/11/30  1.0     刘德印    创建
    =============================================================================*/
	BOOL InitControl();

	/*=============================================================================
    函 数 名:CheckIPAddr
    功    能:IP地址检测
    参    数:检测是否成功  成功返回IP地址
    注    意:无
    返 回 值:TRUE 成功;FALSE 失败 
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/11/30  1.0     刘德印    创建
    =============================================================================*/
	BOOL CheckIPAddr(CString& strIp);

	BOOL LoginSuccess();
	BOOL LoginFails(CString strErrorText);
	BOOL LoginTimeOut();
	BOOL LoginGrab(u32 dwIP);
	BOOL LoginRefuse(u32 dwIP);
	BOOL LoginLogoff();
	BOOL LoginBreak();

	BOOL ClearWarningText();

	void ShowWarningText(const CString& strText);

	BOOL WriteIpAddr(std::vector<CString> vecIpAddr);
	BOOL ReadIpAddr();

	void EnableControl( BOOL bEnable );	//登陆过程中对一些按钮的保护

private:
	CTransparentComboBox* m_pComboWnd;
	std::vector<CString> m_vecCombList;
	CString m_strIpConfigFullPath;
	BOOL m_bRefuseLogin;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TPTOOLSDLG_H__2D9E8A35_54C7_4086_90FE_8DE8BF4FEF74__INCLUDED_)
