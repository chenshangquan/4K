// cnclib.cpp: implementation of the CCncLib class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cnclib.h"
#include "cmsConst.h"
#include "cnsSession.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CCncLib::CCncLib()
{

}

CCncLib::~CCncLib()
{

}

/*=============================================================================
  函 数 名： CreateSession
  功    能： 创建实现了接口CCnsSessionCtrlIF的对象
  算法实现： 接口使用完成后,调用DestroyInstance方法销毁对象
  全局变量： 
  参    数： CCnsSessionCtrlIF **ppICnt 成功返回CCnsSessionCtrlIF接口,失败返回NULL
  返 回 值： u16 
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
 2011.05.04     1.0		    肖楚然                  创建
=============================================================================*/
u16 CCncLib::CreateSession(CCnsSessionCtrlIF **ppICnt)
{
	CCnsSession *pConnect = new CCnsSession();
	if(pConnect == NULL)
	{
		*ppICnt = NULL;
		return ERR_CNC_CREATINSTANCE;
	}
	else
	{
		*ppICnt = pConnect;
		return NO_ERROR;
	}
}

/*=============================================================================
  函 数 名： DestroySession
  功    能： 销毁实现了接口CCnsSessionCtrlIF的对象
  算法实现： 
  全局变量： 
  参    数： CCnsSessionCtrlIF **ppICnt 输入接口CCnsSessionCtrlIF,成功后返回NULL
  返 回 值： u16 
  说    明： 只能销毁由CreateInstance方法创建的对象
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
 2011.05.04     1.0		    肖楚然                  创建
=============================================================================*/
u16 CCncLib::DestroySession(CCnsSessionCtrlIF **ppICnt)
{
	CCnsSession *pConnect = dynamic_cast<CCnsSession*>(*ppICnt);
	if(pConnect == NULL)
    {
        return ERR_CNC_INTERFACE;
    }
	delete pConnect;
	*ppICnt = NULL;
	return NO_ERROR;
}