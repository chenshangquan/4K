// CfgAdvanceDlg.h: interface for the CCfgAdvanceDlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CFGADVANCEDLG_H__146F781C_947B_4E31_B49B_F16BE3072D67__INCLUDED_)
#define AFX_CFGADVANCEDLG_H__146F781C_947B_4E31_B49B_F16BE3072D67__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCfgAdvanceDlg : public CLogicBase, public ISingleTon<CCfgAdvanceDlg>
{
public:
	CCfgAdvanceDlg();
	virtual ~CCfgAdvanceDlg();

	void RegCBFun();

	virtual void Clear();

	virtual void RegMsg();

	bool InitWnd( const IArgs & arg );

	bool OnSwitchLossPacket( const IArgs & arg );
	
	bool OnLossPacketLevel( const IArgs & arg );

	bool OnRouteCfgChange( const IArgs & arg );

	bool OnBtnAdd( const IArgs& args );
	
	bool OnBtnDel( const IArgs& args );

	bool OnBtnSave( const IArgs& args );

	bool OnBtnCancel( const IArgs& args );

	/**	 
	* 功能:  单击RouteMngLst某个Item的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnClickRouteMngLst( const IArgs & arg );

	/**	 
	* 功能:  单击RouteMngLst空白区域的响应函数
	* @return   bool
	* @remarks	 
	*/
	bool OnClickRouteCfgLstBlack( const IArgs& args );
	
	HRESULT OnLostPacketNty( WPARAM wparam, LPARAM lparam );

	LRESULT OnConfStateNty( WPARAM wparam, LPARAM lparam );

	HRESULT OnSetRouteInfoNty( WPARAM wparam, LPARAM lparam );

	HRESULT OnAddRouteInfoInd( WPARAM wparam, LPARAM lparam );

	HRESULT OnDelRouteInfoInd( WPARAM wparam, LPARAM lparam );

	bool IsCfgChange();
	bool SaveMsgBox();
	s32 GetCtrlChangeNum() { return m_vctWndName.size(); }
private:
	string GetLoatPacketConf( EmTpLostPackageRestore emLostPacket );

	EmTpLostPackageRestore TransLostPacketConf( string strConf );

	void UpdateBtnLossPacket( EmTpLostPackageRestore emLostPacket );

	/**	 
	* 功能:  更新Btn状态
	* @return   void
	* @remarks	 
	*/
	void UpdateBtnState();

	/**	 
	* 功能:  重置所有控件
	* @return   void
	* @remarks	 
	*/
	void ResetAllCtrl();
private:
	EmTpLostPackageRestore m_emLostPacket;
	EmTpLostPackageRestore m_emTempLevel;

	const String m_strRouteInfoList;
	const String m_strBtnAdd;
	const String m_strBtnDel;

	TRouteCfg m_tTRouteCfgSel;  //选中的行
};

#endif // !defined(AFX_CFGADVANCEDLG_H__146F781C_947B_4E31_B49B_F16BE3072D67__INCLUDED_)
