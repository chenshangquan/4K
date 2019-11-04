/*****************************************************************************
模块名      : CMS控制台
文件名      : confTemplateCtrlIF.h
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

#if !defined(AFX_CONFTEMPLATECTRLIF_H__291A729D_3EC2_42F1_8E39_D9C20E52B18A__INCLUDED_)
#include "kdvdispevent.h"
#include "tplarray.h"
#include "cmsstruct.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CConfTemplateCtrlIF:public  CKdvDispEvent 
{
 
public:
/** @defgroup  会议模板接口
 *  @{
 */


  /**
    * 功 能:	获取会议模板列表
	* @param [out] tplConfTempList	 会议模板列表
	* @return 成功返回0,失败返回非0错误码
	*/
	virtual u16 GetConfTemplateList( TplArray<TTPConfTemplate> &tplConfTempList ) const = 0;
   
  /**
    * 功能:  添加会议模板
	* @param [in]	tConfTemp	 会议模板 
	* @return	成功返回0,失败返回非0错误码
	*/
	virtual u16 AddConfTemplateReq( const TTPConfTemplate &tConfTemp )    = 0 ;
 
 
	/**
    * 功能:  修改会议模板
	* @param [in]	tConfTemp	 会议模板 
	* @return	成功返回0,失败返回非0错误码
	*/
	virtual u16 ModifyConfTemplateReq( const TTPConfTemplate &tConfTemp )    = 0 ;

  
	/**
    * 功能:  删除会议模板
	* @param [in] wConfTempID	 会议模板ID 
	* @return	成功返回0,失败返回非0错误码
	*/
	virtual u16 DeleteConfTemplateReq( const u16 wConfTempID )    = 0 ;

	/**
    * 功能:  删除全部模板
	* @param
	* @return	成功返回0,失败返回非0错误码
	*/
	virtual u16 DelAllConfTempReq() = 0;   //by xhx

/** @}*/  //会议模板操作接口
};

#endif // !defined(AFX_CONFTEMPLATECTRLIF_H__291A729D_3EC2_42F1_8E39_D9C20E52B18A__INCLUDED_)
