/*****************************************************************************
文件实现功能: 管理logic 和 方案
文件名      : logicManager.h 
相关文件    : UIDlgBuilder.h DUIDialog.h 
备注		:  
作者        : 俞锦锦
版本        : V1.0  Copyright(C) 2013-2014 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/4/18      1.0         俞锦锦      创建
******************************************************************************/
#pragma once

#include <map>
#include <vector>
namespace DuiLib { 



typedef std::map</*CStdString*/tString,INotifyUI*> LOGICMAP; 
/*****************************************************************************
* 功能:管理dlgName和其对应的布局xml及logic间的映射关系， 及已经创建出的dlg指针
* @remarks	 
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/4/18       1.0         俞锦锦      创建
******************************************************************************/
class  CLogicManager 
{
public: 
	
	UILIB_API static BOOL RegLogic( INotifyUI* pLogic, LPCTSTR szLogicName );

	static INotifyUI* FindLogicByName(  LPCTSTR szLogicName  );

protected: 
	static  LOGICMAP m_logicMap; //存储所有logic
	 
};

 #define REG_LOGIC( logicPtr,logicName ) \
	CLogicManager::RegLogic( logicPtr, logicName  ); 


}
