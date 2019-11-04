// userCtrlIF.h: interface for the CUserCtrlIF class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USERCTRLIF_H__F47ED342_9A87_4124_8677_30F8A69F7D1A__INCLUDED_)
#define AFX_USERCTRLIF_H__F47ED342_9A87_4124_8677_30F8A69F7D1A__INCLUDED_
#include "kdvdispevent.h"
#include "ummessagestruct.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUserCtrlIF :public  CKdvDispEvent  
{
public:
 
/** @defgroup  操作用户接口
 *  @{
 */

	/**
    * 功能:	 获取用户列表
	* @param [out]  tplUserList	 用户列表
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 
	*/
	virtual u16  GetUserList( TplArray<CUserFullInfo>& tplUserList) const = 0 ;
   

   /**
    * 功能:	 	添加用户
	* @param [in]  tUser	 用户 
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 
	*/
	virtual u16  AddUserReq( const CUserFullInfo& tUser )   = 0 ;


 
	/**
    * 功能:	 	修改用户
	* @param [in]  tUser	 用户 
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 
	*/
	virtual u16  ModifyUserReq( const CUserFullInfo& tUser )   = 0 ;


 
  /**
    * 功能:	 	删除用户
	* @param [in]  tUser	 用户 
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 
	*/
	virtual u16  DeleteUserReq( const CUserFullInfo& tUser )   = 0 ;

 /** @}*/ // 操作用户接口

};

#endif // !defined(AFX_USERCTRLIF_H__F47ED342_9A87_4124_8677_30F8A69F7D1A__INCLUDED_)
