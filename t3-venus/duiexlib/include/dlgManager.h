/*****************************************************************************
文件实现功能: 管理dlgName和其对应的布局xml及logic间的映射关系， 及已经创建出的dlg指针
文件名      : dlgMap.h 
相关文件    : UIlib.h DUIDialog.h 
备注		: 读取dlgMap.xml
作者        : 俞锦锦
版本        : V1.0  Copyright(C) 2013-2014 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/4/18      1.0         俞锦锦      创建
******************************************************************************/

#pragma once
#include "DUIDialog.h"
#include<map>
namespace DuiLib {

#define PARENT_NAME_LEN 40

class UILIB_API CDlgManager:public ISingleTon<CDlgManager>
{
public:
	/*****************************************************************************
	* 功能: 解析szDlgMapXml文件，并把对应的属性都存储到m_dlgMap
	* @param [in]  szDlgMapXml  对应的dlgMap文件
	* @return    
	* @remarks	 
	-----------------------------------------------------------------------------
	修改记录:
	日  期         版本        修改人      修改内容
	2013/4/18       1.0         俞锦锦      创建
    ******************************************************************************/  
	BOOL InitDlgMap( const LPCTSTR szDlgMapXml );


	/*****************************************************************************
	* 功能: 根据dlg名查找对应的dlg
	* @param [in]  szDlgName  dlg名
	* @return   成功返回 szDlgName对应的CDUIDialog*;失败返回 NULL
	* @remarks	若未创建，则创建出来
	-----------------------------------------------------------------------------
	修改记录:
	日  期         版本        修改人      修改内容
	2013/4/18       1.0         俞锦锦      创建
    ******************************************************************************/
	CDUIDialog* FindDlgByName( const LPCTSTR szDlgName );



	/*****************************************************************************
	* 功能: domodal某个dlg
	* @param [in]  szDlgMapXml  对应的dlgMap文件
	* @return    
	* @remarks	 
	-----------------------------------------------------------------------------
	修改记录:
	日  期         版本        修改人      修改内容
	2013/4/18       1.0         俞锦锦      创建
    ******************************************************************************/  
	int DoModal( const LPCTSTR szDlgMapXml );


	/*****************************************************************************
	* 功能:结束某个dlg的模式状态
	* @param [in]  szDlgMapXml  对应的dlgMap文件
	* @param [in]  nResult   DoModal  的返回值
	* @return    
	* @remarks	 
	-----------------------------------------------------------------------------
	修改记录:
	日  期         版本        修改人      修改内容
	2013/4/18       1.0         俞锦锦      创建
    ******************************************************************************/  
	void EndModal( const LPCTSTR szDlgMapXml, int nResult );


	/*****************************************************************************
	* 功能: 关闭dlg
	* @param [in]  szDlgName 对应的dlg名
	* @return   成功返回  TRUE，失败返回FALSE
	* @remarks	 
	-----------------------------------------------------------------------------
	修改记录:
	日  期         版本        修改人      修改内容
	2013/5/2       1.0         俞锦锦      创建
    ******************************************************************************/ 
	BOOL CloseDlg( const LPCTSTR szDlgName);


	/*****************************************************************************
	* 功能: 调用方案
	* @param [in]  szCaseName  方案名，szDlgName 对应的dlg名
	* @return   成功返回  TRUE，失败返回FALSE
	* @remarks	若未创建，则创建出来
	-----------------------------------------------------------------------------
	修改记录:
	日  期         版本        修改人      修改内容
	2013/5/2       1.0         俞锦锦      创建
    ******************************************************************************/
	BOOL DoCase( const LPCTSTR szCaseName, const LPCTSTR szDlgName );


public:
	CDlgManager();
	~CDlgManager(void);
private:
	 

	typedef struct
	{
		DWORD dwStyle  ;
		DWORD dwExStyle ;
		TCHAR tcParent[PARENT_NAME_LEN];
		BOOL bAuotHide ;
		TCHAR tcLayoutFile[MAX_PATH];
	}TDlgAttrib;
	 

	

	//根据dlgName创建dlg
	CDUIDialog* CreateDlgByName(  const LPCTSTR szDlgName  ); 

	//根据dlgName 查找对应的dlg配置
	TDlgAttrib* FindElementByDlgName( const LPCTSTR szDlgName );

private:
	 
	typedef std::map<tString/*CStdString*/,TDlgAttrib> DLGMAP;       
	typedef std::map<tString/*CStdString*/,CDUIDialog*> LIVEDLGMAP;
	  

	DLGMAP m_dlgMap;				//对应于存储dlg map 的xml文件
	LIVEDLGMAP m_liveDlgMap;		//已经创建了的dlg
 

};
#define DLG_MNG_PTR CDlgManager::GetSingletonPtr()

/*****************************************************************************
模块实现功能: 常用窗口属性管理，根据字符串转换为对应的属性值
备注		:  
作者        : 俞锦锦
版本        : V1.0  Copyright(C) 2013-2014 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/4/19      1.0         俞锦锦      创建
******************************************************************************/
class CWindowStyleMap
{
public:
	static const TCHAR m_chPartitionChar;
public:
	/**  通过一个字符串转换为一个风格
	 *  @param[in] str 字符串
	 *  @param[out] dwStyle 风格
	 *  @return 是否成功
	 */
	static DWORD StringToStyle( LPCTSTR str );


    static bool StringToStyle( LPCTSTR str, DWORD& dwStyle, DWORD& dwStyleEx );

	/**  注册一个风格对应关系 默认注册会在CRegDefaultData里面
	 *  @param[in] dwStyle	风格
	 *  @param[in] str		字符串
	 *  @return 是否成功
	 */
	static bool RegStyle( DWORD dwStyle, LPCTSTR str );
protected:
	typedef std::map< CStdString, DWORD > DefaultStyleMap;
	static DefaultStyleMap m_mapStyles;
};

/*
* 注册从一个ID到一个字符串的映射\n 
*/
#ifndef REG_WINDOW_STYLE
#define REG_WINDOW_STYLE( strKey ) CWindowStyleMap::RegStyle( strKey, _T(#strKey) );
#endif

}