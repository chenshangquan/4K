// cncuserctrl.h: interface for the CCncUserCtrl class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_USERCTRL_H__EB116E65_7B63_4B3E_B267_9C0B112DA0C1__INCLUDED_)
#define AFX_USERCTRL_H__EB116E65_7B63_4B3E_B267_9C0B112DA0C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cnsSession.h"

class CCncUserCtrl :public CCncUserCtrlIF 
{  

/** @defgroup  操作用户接口实现部分
 *  @{
 */
public:
    CCncUserCtrl( CCnsSession &cSession );
	virtual ~CCncUserCtrl();
 
  /**
    * 功能:	 获取用户列表
	* @param [out]  tplUserList	 用户列表
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 
	*/
	virtual u16  GetUserList( TplArray<CUserFullInfo>& tplUserList) const;
 
	
   /**
    * 功能:	 	添加用户
	* @param [in]  tUser	 用户 
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 消息：CMS->UMS  ev_UMSAddUserReq 此消息直接用OSP发送，不经过XML编解码 \n
	                   应回复:UMS->CMS   ev_UMSAddUserRet \n
	                   若成功，还应回复:UMS->CMS   ev_UmsAddUser_Notify
	*/
	virtual u16  AddUserReq( const CUserFullInfo& tUser ) ;


  
  /**
    * 功能:	 	修改用户
	* @param [in]  tUser	 用户 
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks  消息：CMS->UMS  ev_UMSChangePWDReq 此消息直接用OSP发送，不经过XML编解码 \n
                    	应回复:：UMS->CMS   ev_UMSAddUserRet \n
	                    若成功，还应回复:：UMS->CMS   ev_UmsUpdateUser_Notify
	*/
	virtual u16  ModifyUserReq( const CUserFullInfo& tUser ) ;

	
 
  /**
    * 功能:	  删除用户
	* @param [out]  tUser	 用户 
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks  消息：CMS->UMS  ev_UMSDelUserReq 此消息直接用OSP发送，不经过XML编解码  \n
                     	应回复: UMS->CMS   ev_UMSDelUserRet \n
		            	若成功，还应回复: UMS->CMS   ev_UmsDelUser_Notify  
	*/
	virtual u16  DeleteUserReq( const CUserFullInfo& tUser );


protected:
 
  /**
    * 功能:	  用户变更通知（包含添加、删除、修改）
	* @param [out]  cMsg	消息
	* @return  无
	* @remarks   
	*/
	void  OnUserChangedNotify(const CMessage& cMsg);

  /**
    * 功能:	  操作用户结果回复（包含添加、删除、修改）
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
    void  OnOperateUserRsp(const CMessage& cMsg);

	virtual void DispEvent(const CMessage &cMsg);
	
    virtual void OnTimeOut(u16 wEvent); 
   

    void  OnLinkBreak(const CMessage& cMsg);
private:
 
	/**
    * 功能:	  注册消息响应函数
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
	void  BuildEventsMap();
   
 
  /**
    * 功能:	  根据用户名，获取用户信息
	* @param [in]  wConfTemplateID：要检查的会议ID号 
	* @return  获取到的用户在列表中的索引
	* @remarks   
	*/
    s16  FindUserByName( char name[MAX_CHARLENGTH] );

private:
	CCnsSession *m_pSession;              
	TplArray<CUserFullInfo> m_tplUserList;   ///<用户列表
 
/** @}*/ // 操作用户接口实现部分
};

#endif // !defined(AFX_USERCTRL_H__EB116E65_7B63_4B3E_B267_9C0B112DA0C1__INCLUDED_)
