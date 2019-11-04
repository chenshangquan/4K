/*****************************************************************************
模块名      : umstool网呈维护工具
文件名      : umsboardCtrlIF.h
相关文件    : 
文件实现功能: ums单板的所有操作
作者        : 刘德印
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2012/11/23  1.0         刘德印      创建
******************************************************************************/
#if !defined(AFX_BOARDCTRLIF_H__F47ED342_9A87_4124_8677_30F8A69F7D1A__INCLUDED_)
#define AFX_BOARDCTRLIF_H__F47ED342_9A87_4124_8677_30F8A69F7D1A__INCLUDED_
#include "kdvdispevent.h"
#include "ummessagestruct.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUmsBoardCtrlIF :public  CKdvDispEvent  
{
public:
		/**
    * 功能:	 获取单板占用情况信息数据
	* @param [out]  TTPBrdUsedInfo	单板占用信息(包括混音器、画面合成、码流适配器占用)
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 
	*/
	virtual u16  GetUmsBoardUsedData( TTPBrdUsedInfo& tBoardUsed) const = 0;

       /**
    * 功能:	 	        发送修改单板请求
	* @param [in]       板子信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	virtual u16  BoardModifyReq( const TTPBrdCfg& tTPbrdCfg ) = 0;

    /**
    * 功能:	 	        发送删除单板请求
	* @param [in]       板子信息无
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	virtual u16  BoardDeleteReq( const TTPBrdCfg& tTPbrdCfg ) = 0;

    /**
    * 功能:	 	        发送添加单板请求
	* @param [in]       板子信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	virtual u16  BoardAddReq( const TTPBrdCfg& tTPbrdCfg ) = 0;

    /**
    * 功能:	 	        发送添加单板模式请求
	* @param [in]       模式信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
//	virtual u16  BoardModeAddReq( const TTPBrdMdlInfo& tTPbrdMdlInfo ) = 0;

    /**
    * 功能:	 	        发送修改单板模式请求
	* @param [in]       模式信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	virtual u16  BoardModeModifyReq( const TTPBrdMdlInfo& tTPbrdMdlInfo ) = 0;

    /**
    * 功能:	 	        发送删除单板模式请求
	* @param [in]       模式信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	virtual u16  BoardModeDeleteReq( const TTPBrdMdlInfo& tTPbrdMdlInfo ) = 0;

	    /**
    * 功能:	 	        发送重启单板请求
	* @param [in]       TTPBrdPos 板子位置
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	virtual u16  BoardRebootReq( const TTPBrdPos& tTPbrdPos ) = 0;

	    /**
    * 功能:	 	        发送混音器占用请求
	* @param [in]       无
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	virtual u16  BoardAudiomixReq() = 0;
	
	    /**
    * 功能:	 	        发送画面合成占用请求
	* @param [in]       无
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	virtual u16  BoardVmpReq() = 0;

	    /**
    * 功能:	 	        发送码流适配占用请求
	* @param [in]       无
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	virtual u16  BoardBasStreamReq() = 0;

	    /**
    * 功能:	 	        板子升级请求
	* @param [in]       const TTPBrdUpGrade& tBrdUpGrade   升级信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	virtual u16  BoardUpgradeReq(const TTPBrdUpGrade& tBrdUpGrade) = 0;

 /** @}*/ // 操作单板接口

};

#endif // !defined(AFX_BOARDCTRLIF_H__F47ED342_9A87_4124_8677_30F8A69F7D1A__INCLUDED_)
