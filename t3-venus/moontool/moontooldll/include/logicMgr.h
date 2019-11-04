// logicMgr.h: interface for the CLogicMgr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGICMGR_H__7B7DC23D_9E73_4096_8042_79ED81C7A199__INCLUDED_)
#define AFX_LOGICMGR_H__7B7DC23D_9E73_4096_8042_79ED81C7A199__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "templateClass.h"
//no why to add not in cnstooldll 
/*using namespace AutoUIFactory;*/
#include "logicbase.h"
#include "warningLogic.h"
#include "mainFrameLogic.h"

class CLogicMgr: public ISingleTon<CLogicMgr>
{
public: 
	virtual ~CLogicMgr();

    CLogicMgr();
 /**	 
	* 功能:  创建所有logic 
	* @return   
	* @remarks	   
	*/ 
   void CreateLogic();
 

   	/**	 
	* 功能:  销毁所有logic 
	* @return   
	* @remarks	   
	*/ 
   void DestroyLogic();
 
   /**	 
	* 功能:  获取logic指针
	* @return   
	* @remarks	   
	*/ 
  // void GetLogic( CCfgCnsLogic **pLogic );
 
private:
 
};



#define  LOGICMGR_PTR CLogicMgr::GetSingletonPtr()



#endif // !defined(AFX_LOGICMGR_H__7B7DC23D_9E73_4096_8042_79ED81C7A199__INCLUDED_)
