/*****************************************************************************
模块名      : CLogicManage
文件名      : logicmanage.h
相关文件    : 
文件实现功能: logic管理类
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2012/12/04     1.0         刘德印      创建
******************************************************************************/
#if !defined(AFX_LOGICMANAGE_H__12E93E38_C38D_47CB_897A_CCE0522BEDD8__INCLUDED_)
#define AFX_LOGICMANAGE_H__12E93E38_C38D_47CB_897A_CCE0522BEDD8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndlogicbase.h"
#include "mainFrameLogic.h"
#include "sysinfologic.h"
#include "correlativecfglogic.h"
#include "addrbookexplogic.h"
#include "templateexplogic.h"
#include "boardcfglogic.h"
#include "umscfglogic.h"
#include "boardoptdlglogic.h"
#include "msgboxdlglogic.h"
#include "tvwboardcfglogic.h"
#include "netmngcfglogic.h"
#include "netmngoptdlglogic.h"
#include "tvwstylecfglogic.h"
#include "tvwstyleoptdlglogic.h"
#include "impcommondlglogic.h"
#include "expcommondlglogic.h"
#include "vtrcfglogic.h"
#include "vtroptdlglogic.h"
#include "warninglogic.h"
#include "backupcfglogic.h"

class CLogicManage  
{
public: 
	virtual ~CLogicManage();
    
public:
	 /**	 
	* 功能:  获取单例指针
	* @return    CLogicManage指针
	* @remarks	   
	*/ 
   static CLogicManage *GetLogicManagePtr();
   
    /**	 
	* 功能:  创建所有logic 
	* @return   
	* @remarks	   
	*/ 
   void CreateLogic();

   /**	 
	* 功能:  销毁 logic 
	* @param [in]  pLogic 要销毁的logic指针
	* @return   
	* @remarks	   
	*/ 
   void DestroyLogic( CWndLogicBase *pLogic );

   	/**	 
	* 功能:  销毁所有logic 
	* @return   
	* @remarks	   
	*/ 
   void DestroyLogic();



protected:
   void OnNotify( WPARAM wparam ,LPARAM lparam );

  /**	 
	* 功能:  获取logic列表
	* @return   
	* @remarks	   
	*/ 
   const  TplArray<CWndLogicBase*>* GetLogicList() const;

  /**	 
	* 功能:  服务器断链
	* @return   
	* @remarks	   
	*/ 
   HRESULT OnDisConnect( WPARAM wparam, LPARAM lparam );

  /**	 
	* 功能:  服务器抢占
	* @return   
	* @remarks	   
	*/ 
   HRESULT OnLoginGrab( WPARAM wparam, LPARAM lparam );

private:
  /**	 
	* 功能:  清空所有logic
	* @return   
	* @remarks	   
	*/
	void ClearAllLogic();

private:
    CLogicManage();
  
	TplArray<CWndLogicBase*> m_tplLogicList; //<logic列表
    static CLogicManage *m_pLogicManage;

};

#define LogicManagePtr  CLogicManage::GetLogicManagePtr()

#endif // !defined(AFX_LOGICMANAGE_H__12E93E38_C38D_47CB_897A_CCE0522BEDD8__INCLUDED_)
