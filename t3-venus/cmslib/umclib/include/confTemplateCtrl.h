/*****************************************************************************
模块名      : CMS控制台
文件名      : confTemplateCtrl.h
相关文件    : 
文件实现功能: 会议模板相关的所有操作
作者        : 俞锦锦
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2011/4/25  1.0          俞锦锦      创建
******************************************************************************/
//Note:会议别名和会议的E164号均不可重复，且会议别名必须为非纯数字，会议164号必须为纯数字

#if !defined(AFX_CONFTEMPLATECTRL_H__92C02860_1783_462D_9A53_784A335A906C__INCLUDED_)
#define AFX_CONFTEMPLATECTRL_H__92C02860_1783_462D_9A53_784A335A906C__INCLUDED_

#include "confTemplateCtrlIF.h"
#include "umsSession.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CConfTemplateCtrl:public CConfTemplateCtrlIF  
{

/** @defgroup 会议模板接口实现部分
 *  @{
 */

	friend class CUmsSession;
private:
	CConfTemplateCtrl(CUmsSession &cUmsSession);
	CConfTemplateCtrl(const CConfTemplateCtrl&){}; 
    
public:
	~CConfTemplateCtrl();

	/**
    * 功 能:	获取会议模板列表
	* @param [out] tplConfTempList	 会议模板列表
	* @return 成功返回0,失败返回非0错误码
	*/
	virtual u16 GetConfTemplateList( TplArray<TTPConfTemplate> &tplConfTempList ) const ;
   

  /**
    * 功能:  添加会议模板
	* @param [in]	tConfTemp	 会议模板 
	* @return	成功返回0,失败返回非0错误码
	* @remarks  消息：cms->ums    evtp_AddConfTemplate_req \n
	                    应回复: ums->cms  evpt_OperatorConfTemplate_Ret\n
	                    若添加成功，则又有 ums->cms  evtp_AddConftemplate_Notify
	*/
	virtual u16 AddConfTemplateReq( const TTPConfTemplate &tConfTemp )    ;
 
 
 /**
    * 功能:  修改会议模板
	* @param [in]	tConfTemp	 会议模板 
	* @return	成功返回0,失败返回非0错误码
	* @remarks  消息：cms->ums  evtp_Updateconftemplate_Req \n
	                    应回复: ums->cms  evpt_OperatorConfTemplate_Ret\n
	                    若添加成功，则又有 ums->cms  evtp_UpdateConftemplate_Notify
	*/
	virtual u16 ModifyConfTemplateReq( const TTPConfTemplate &tConfTemp )    ;

  

  /**
    * 功能:  删除会议模板
	* @param [in]	wConfTempID	 会议模板ID
	* @return	成功返回0,失败返回非0错误码
	* @remarks  消息：cms->ums  evtp_AddConfTemplate_req \n
	                    应回复: ums->cms  evpt_OperatorConfTemplate_Ret\n
	                    若添加成功，则又有 ums->cms  evtp_Delconftemplate_Notify
	*/
	virtual u16 DeleteConfTemplateReq( const u16 wConfTempID )    ;

	/**
    * 功能:  删除全部模板
	* @param
	* @return	成功返回0,失败返回非0错误码
	* @remarks  消息：umc->ums  ev_del_all_conftemp_req \n
	            应回复: ums->umc  ev_del_all_conftemp_rsp\n
	*/
	virtual u16 DelAllConfTempReq();   //by xhx

protected:

 
  /**
    * 功能: 请求添加、删除、修改会议模板的回复
	* @param [in]	cMsg:消息内容
	* @return	无
	* @remarks  消息： ums->cms evpt_OperatorConfTemplate_Ret 
	*/
   void OnOperateConfTempRsp( const CMessage& cMsg );

	 
  
    /**
    * 功能: 添加会议模板列表的通知
	* @param [in]	cMsg:消息内容
	* @return	无
	* @remarks  消息： ums->cms evtp_AddConftemplate_Notify
	*/
   void OnAddConfTempNotify( const CMessage& cMsg );


   
   /**
    * 功能: 删除会议模板列表的通知 
	* @param [in]	cMsg:消息内容
	* @return	无
	* @remarks  消息：ums->cms  evtp_Delconftemplate_Notify
	*/
   void OnDelConfTempNotify( const CMessage& cMsg );

    /**
    * 功能: 删除全部模板消息应答
	* @param [in]	cMsg:消息内容
	* @return	无
	* @remarks  消息：ums->umc  ev_del_all_conftemp_rsp
	*/
   void OnDelAllConfTempRsp( const CMessage& cMsg );  //by xhx

  
    /**
    * 功能: 修改会议模板列表的通知 
	* @param [in]	cMsg:消息内容
	* @return	无
	* @remarks  消息：ums->cms  evtp_Updateconftemplate_Notify
	*/
   void OnUpdateConfTempNotify( const CMessage& cMsg );

    /**
    * 功能: 更新会议模板资源占用数 
	* @param [in]	cMsg:消息内容
	* @return	无
	* @remarks  消息：ums->cms  evtp_Updateconftemplate_Notify
	*/
   void OnUpdateResUsedCountNotify( const CMessage& cMsg );

   void OnLinkBreak( const CMessage& cMsg );
   
    
   virtual void DispEvent(const CMessage &cMsg);
   
   virtual void OnTimeOut(u16 wEvent);


private:
   void  BuildEventsMap();
 
   /**
    * 功能: 检查某会议模板 是否已存在
	* @param [in]	wConfTemplateID：要检查的会议ID号
	* @return	TRUE：已存在，FALSE：不存在
	*/
   BOOL32  IsExistConfTemplate( u16 wConfTemplateID );

 
  /**
    * 功能: 根据会议模板ID，获取会议模板
	* @param [in]	wConfTemplateID：要检查的会议ID号
	* @return	会议模板在列表中的索引
	*/
   int  FindConfTemplateByID( u16 wConfTemplateID );

private:
	TplArray<TTPConfTemplate> m_tplConfTempList;
    
	CUmsSession *m_pUmsSession;

/** @}*/  //会议模板接口实现部分
};

#endif // !defined(AFX_CONFTEMPLATECTRL_H__92C02860_1783_462D_9A53_784A335A906C__INCLUDED_)
