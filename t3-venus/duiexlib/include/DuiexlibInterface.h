/*****************************************************************************
模块名      : CDuiexlibInterface
文件名      : DuiexlibInterface.h
相关文件    : 
文件实现功能: duiexlib通用接口
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/7/22      1.0         刘德印      创建
******************************************************************************/
#ifndef _DUIEXLIBINTERFACE_H
#define _DUIEXLIBINTERFACE_H

class UILIB_API CDuiexlibInterface:public ISingleTon<CDuiexlibInterface>
{
public:
	CDuiexlibInterface();
	virtual ~CDuiexlibInterface();


	//列表控制方案
	static bool UpdateList( const tString& strWndName, std::vector<IData*>& vecData, CPaintManagerUI& pm );

	static bool UpdateList( const tString& strWndName, CStdDataArray<IData*>& vecData, CPaintManagerUI& pm );

	static int GetListIndex( const tString& strWndName, CControlUI* pElement, CPaintManagerUI& pm );


	static bool ShowWindow( const tString& strWndName, bool bShow = true );
	static CDUIDialog* GetDUIDialogPtr(const tString& strDlgName);   //by xhx
	static CPaintManagerUI& GetPaintMngUI(const tString& strDlgName);   //by xhx
	static void GetCheckStateByName(const tString& strListName, const CPaintManagerUI& pm, CStdDataList<bool>** mapCheckState);//by xhx




//static void InitUIFactory( String strSystemName );
//
//static void UnInitUIFactory();
//
///** @defgroup   窗口属性部分
//*  @{
//*/
//static void UpdateUI(   IWndTree* pWndTree );
//
//static void UpdateUI( String strWndName,   IWndTree* pWndTree = NULL);
///**	 
//* 功能:  显示/隐藏某个窗口
//* @param [in]  strWndName  窗口名
//* @param [in]  bShow  是否要显示 
//* @param [in]  bReDraw  是否重绘
//* @return  u16 成功返回0;失败返回非0错误码
//* @remarks	 
//*/
//static short ShowWindow( String strWndName, bool bShow = true,const IWndTree* pWndTree = NULL, BOOL bReDraw = TRUE );
// 
//
///**	 
//* 功能:  窗口开始进入模式状态
//* @param [in]  strWndName  窗口名
//* @param [in]  bCenter     窗口是否居中
//* @return  int  返回窗口结束modal状态时的结果
//* @remarks	 2012.12.6 yjj
//*/
//static int Domodal( String strName, const IWndTree* pWndTree = NULL, BOOL bCenter = TRUE ); 
//static int Domodal( Window* pWnd  );
//
///**	 
//* 功能:  窗口结束模式状态
//* @param [in]  nReslut 为 Domodal的返回值
//* @return   
//* @remarks	 2012.12.6 yjj
//*/
//static void Endmodal( int nResult, String strName, const IWndTree* pWndTree = NULL  ); 
//static void Endmodal( int nResult, Window* pWnd  );
//
//
///**  获取控件信息 
// *  @param[in] strName 控件名称
// *  @param[in] pWndTree 控件树 
// *  @return 控件信息
// *  @remarks 若控件中含有“/” 则会按照分隔符处理
// */ 
//static const IWndTree* GetWindow( String strName, const IWndTree* pWndTree = NULL )  ;
//
//
///**  获取控件信息
// *  @param[in] pWnd 窗口指针
// *  @param[in] pWndTree 所要遍历的树
// *  @return 返回搜索到的窗口
// */
//static const IWndTree* GetWindow( Window* pWnd, const IWndTree* pWndTree );
//
//
///**  获取控件指针 
// *  @param[in] strName 控件名称
// *  @param[in] pWndTree 控件树 
// *  @return 控件信息
// *  @remarks 若控件中含有“/” 则会按照分隔符处理
// */ 
//static Window* GetWindowPtr( String strName, const IWndTree* pWndTree = NULL );
//
// /**	 
//* 功能:  把启用方案
//* @param [in] strSchemeName 方案名
//* @param [in] String strWndName 启用该方案的窗口名
//* @param[in] pWndTree 窗口所在的控件树 
//* @return   
//* @remarks	   
//*/
//static bool LoadScheme( String strSchemeName, IWndTree* pWndTree = NULL , String strWndName = "", bool bInvalidate = true );
//
// /**	 
//* 功能:  设置某控件属性值
//* @param [in]  strWndName  窗口名
//* @param [in]  value 要设置的属性信息 
//* @param[in] pWndTree 控件所在的树
//* @return  bool 成功返回true;失败返回false
//* @remarks	 若控件中含有“/” 则会按照分隔符处理
//*/
//static bool SetPropertyValue( const IValue& value,   String strWndName, const IWndTree* pWndTree = NULL );
//
// /**	 
//* 功能:  获取某控件属性值
//* @param [in&out]  IValue  要获取的属性信息
//* @param [in]  window  要获取的属性的窗口指针
//* @param [in]  strWndType  要获取的属性的窗口类型
//* @return  bool 成功返回true;失败返回false
//* @remarks	 
//*/
//static bool SetPropertyValue( const IValue& value, const Window* window,  const String& strWndType );
//
//
// /**	 
//* 功能:  获取某控件属性值
//* @param [in&out]  IValue  要获取的属性信息
//* @param [in]  strWndName  窗口名 
//* @param[in] pWndTree 控件所在的树
//* @return  bool 成功返回true;失败返回false
//* @remarks	 若控件中含有“/” 则会按照分隔符处理
//*/
//static bool GetPropertyValue( IValue& value, String strWndName, const IWndTree* pWndTree = NULL);
//
// /**	 
//* 功能:  获取某控件属性值
//* @param [in&out]  IValue  要获取的属性信息
//* @param [in]  window  要获取的属性的窗口指针
//* @param [in]  strWndType  要获取的属性的窗口类型
//* @return  bool 成功返回true;失败返回false
//* @remarks	 
//*/
//static bool GetPropertyValue( IValue& value, const Window* window,  const String& strWndType );
//
///**	 
//* 功能:  设置控件是否可用
//* @param [in]  strWndName  控件名
//* @param [in]  bEnable  状态
//* @param [in]  pWndTree 控件树 
//* @return  bool 成功返回true;失败返回false
//* @remarks	 
//*/
//static bool EnableWindow( String strWndName, bool bEnable = true, const IWndTree* pWndTree = NULL );
//
///**	 
//* 功能:  设置控件标题
//* @param [in]  strWndName  控件名
//* @param [in]  strCaption  标题
//* @param [in]  pWndTree 控件树 
//* @param [in]  bReDraw  是否重绘 
//* @return  bool 成功返回true;失败返回false
//* @remarks	 
//*/
//static bool SetCaption( String strWndName, String strCaption, const IWndTree* pWndTree = NULL, BOOL bReDraw = FALSE );
//
///**	 
//* 功能:  获取控件标题
//* @param [in]  strWndName  控件名
//* @param [out] strCaption  标题
//* @param [in]  pWndTree 控件树 
//* @return  bool 成功返回true;失败返回false
//* @remarks	 
//*/
//static bool GetCaption( String strWndName, String& strCaption, const IWndTree* pWndTree = NULL );
//
///**	 
//* 功能:  设置焦点
//* @param [in]  strWndName  控件名
//* @param [in]  pWndTree 控件树 
//* @return  bool 成功返回true;失败返回false
//* @remarks	 
//*/
//static bool SetFocus( String strWndName, const IWndTree* pWndTree = NULL );
//
///**	 
//* 功能:  设置Button Check状态
//* @param [in]  strWndName  控件名
//* @param [in] nCheckState  状态
//* @param [in]  pWndTree 控件树 
//* @return  bool 成功返回true;失败返回false
//* @remarks	 
//*/
//static bool SetCheckState( String strWndName, int nCheckState, const IWndTree* pWndTree = NULL );
//
///**	 
//* 功能:  获取Button Check状态
//* @param [in]  strWndName  控件名
//* @param [in] nCheckState  状态
//* @param [in]  pWndTree 控件树 
//* @return  bool 成功返回true;失败返回false
//* @remarks	 
//*/
//static bool GetCheckState( String strWndName, int& nCheckState, const IWndTree* pWndTree = NULL );
//
///**	 
//* 功能:  设置SwitchButton Check状态
//* @param [in]  strWndName  控件名
//* @param [in]  bState  状态
//* @param [in]  pWndTree 控件树 
//* @return  bool 成功返回true;失败返回false
//* @remarks	 
//*/
//static bool SetSwitchState( String strWndName, bool bState, const IWndTree* pWndTree = NULL );
//
///**	 
//* 功能:  获取SwitchButton Check状态
//* @param [in]  strWndName  控件名
//* @param [out] bState  状态
//* @param [in]  pWndTree 控件树 
//* @return  bool 成功返回true;失败返回false
//* @remarks	 
//*/
//static bool GetSwitchState( String strWndName, bool& bState, const IWndTree* pWndTree = NULL );
//
///**	 
//* 功能:  查看控件是否显示
//* @param [in]  strWndName  控件名 
//* @param [in]  pWndTree 控件树 
//* @return  bool 显示返回true;未显示返回false
//* @remarks	 
//*/
//static bool IsVisible( String strWndName, const IWndTree* pWndTree = NULL );
//
///**	 
//* 功能:  设置Dlg图片
//* @param [in]  strWndName  控件名
//* @param [in]  strPath  图片路径
//* @param [in]  pWndTree 控件树 
//* @return  bool 成功返回true;失败返回false
//* @remarks	 
//*/
//static bool SetTransparentDlgImage( String strWndName, String strPath, const IWndTree* pWndTree = NULL );
//
///**	 
//* 功能:  设置Static图片
//* @param [in]  strWndName  控件名
//* @param [in]  strPath  图片路径
//* @param [in]  pWndTree 控件树 
//* @return  bool 成功返回true;失败返回false
//* @remarks	 
//*/
//static bool SetTransStaticImage( String strWndName, String strPath, const IWndTree* pWndTree = NULL );
//
///**	 
//* 功能:  设置DragButton Sel状态
//* @param [in]  strWndName  控件名
//* @param [out] bState  状态
//* @param [in]  pWndTree 控件树 
//* @return  bool 成功返回true;失败返回false
//*/
//static bool SetSelState( String strWndName, bool bState, const IWndTree* pWndTree = NULL );
//
///**	 
//* 功能:  获取DragButton Sel状态
//* @param [in]  strWndName  控件名
//* @param [out] bState  状态
//* @param [in]  pWndTree 控件树 
//* @return  bool 成功返回true;失败返回false
//*/
//static bool GetSelState( String strWndName, bool& bState, const IWndTree* pWndTree = NULL );
//
///**	 
//* 功能:  设置DragButton Online状态
//* @param [in]  strWndName  控件名
//* @param [out] bOnline  状态
//* @param [in]  pWndTree 控件树 
//* @return  bool 成功返回true;失败返回false
//*/
//static bool SetDragBtnOnline( String strWndName, bool bOnline, const IWndTree* pWndTree = NULL );   
///**@} */  //窗口属性处理部分
//
//
///**	 
//* 功能:  处理windows消息
//* @param [in]  pMsg 要处理的消息信息
//* @return  bool 成功返回true;失败返回false
//* @remarks	在uifactroy内部查找注册过该消息的处理函数 对该消息做出响应
//*/
//static bool HandleMsg( WindowMsg* pMsg );
//
//
//
// /**  隐藏所有窗口
//*  @param[in]  
//*  @return 是否隐藏成功
//*/
//static bool HideAllWindow();
//
//
///**	 
//* 功能:  销毁窗口	 
//* @param [in]  strWndName 要销毁的窗口名
//* @return  u16 成功返回0，失败返回错码
//* @remarks	   
//*/ 
//static bool DestoryWnd( String strWndName );
//
//
///**  销毁窗口，这里会调用CWnd的Destory
//*  @param[in] pWnd 窗口指针
//*  @return 是否销毁成功
//*/
//static bool DestoryWnd( Window* pWnd );
//
//
///**  销毁窗口，这里会调用CWnd的Destory
//*  @param[in] pWnd 窗口指针,只销毁非child类型 且 无父窗口的window
//*  @return 是否销毁成功
//*  @auth yjj 2012.12.12
//*/
//static bool DestoryWnd(   IWndTree* pWndTree );
//
// 
///**  销毁所有窗口窗口，这里会调用CWnd的Destory
//*  @param[in] pWndTree 窗口树
//*  @return 是否销毁成功
//*  @auth yjj 2011.11.30
//*/
//static bool DestoryAllWnd();
//
//
//
///**  最小化窗口
//*  @return 是否最小化成功
//*  @auth yjj 2012.12.12
//*/
//static bool MinmizeWnd();
//
//
///**@} */  //wnd管理部分
//
///**	 
//* 功能:  把窗口风格的改变记录到文件中 
//* @param [in]   String strWndName窗口名
//*  @param[in] strSavePropertyName 要保存的属性名
//*  @param[in] bForceSave 如果要保存的属性不在当前方案中，是否强制保存
//* @return   
//* @remarks	   
//*/
//static bool  SaveToFile( String strWndName, string strSaveWndName = "" ,string strSavePropertyName = "" , BOOL bForceSave = FALSE );
//
//static String GetImagePath(); 
//
//
///**	 
//* 功能:  设置Combobox 编辑框文本显示内容
//* @param [in]  strWndName  控件名
//* @param [in]  strText  文本
//* @param [in]  pWndTree 控件树 
//* @return  bool 成功返回true;失败返回false
//* @remarks	 
//*/
//static bool SetComboText( String strWndName, String strText, const IWndTree* pWndTree /* = NULL */ );
//
///**	 
//* 功能:  得到Combobox 编辑框文本显示内容
//* @param [in]  strWndName  控件名
//* @param [in]  strText  文本内容
//* @param [in]  pWndTree 控件树 
//* @return  bool 成功返回true;失败返回false
//* @remarks	 
//*/
//static bool GetComboText( String strWndName, String& strText, const IWndTree* pWndTree /* = NULL */ );
//
///**	 
//* 功能:  设置Combobox 列表内容
//* @param [in]  strWndName  控件名
//* @param [in]  strText  文本
//* @param [in]  pWndTree 控件树 
//* @return  bool 成功返回true;失败返回false
//* @remarks	 
//*/
//static bool SetComboListData( String strWndName, std::vector<CString> vecListData, const IWndTree* pWndTree /* = NULL */ );
//
///**	 
//* 功能:  清空Combobox 列表内容
//* @param [in]  strWndName  控件名
//* @param [in]  strDefText  combox默认显示的内容
//* @param [in]  pWndTree 控件树 
//* @return  bool 成功返回true;失败返回false
//* @remarks	 
//*/
//static bool CleanComboListData( String strWndName, const IWndTree* pWndTree /* = NULL */, String strDefText = "无" );
//
//
///**	 
//* 功能:  获取版本号
//*
//* @return  bool 成功返回true;失败返回false
//* @remarks	 
//*/
//static string GetVersion();
//
///**	 
//* 功能:  设置窗口位置
//* @param [in]  pt  位置
//* @param [in]  strWndName 要设置的窗口名
//* @param [in]  pWndTree 控件树 
//* @param [in]  strRelativeWnd 如果该参数不为空则设置的位置为相对该窗口位置 
//* @return  bool 成功返回true;失败返回false
//* @remarks	2013.1.10 yjj 
//*/
//static void SetWndPos(  POINT pt, String strWndName,   IWndTree* pWndTree = NULL,  String strRelativeWnd = "" );
// 
///**	 
//* 功能:  设置编辑框焦点置后
//* @param [in]  strWndName  控件名
//* @param [in]  pWndTree 控件树 
//* @param [in]  bReDraw  是否重绘 
//* @return  bool 成功返回true;失败返回false
//* @remarks	 
//*/
//static bool SetEditFocusEnd( String strEditWndName, const IWndTree* pWndTree = NULL, BOOL bReDraw = FALSE ); 

};

#define UI_PTR CDuiexlibInterface::GetSingletonPtr()






#endif