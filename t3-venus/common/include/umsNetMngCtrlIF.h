/*****************************************************************************
模块名      : umstool网呈维护工具
文件名      : umsNetMngCtrlIF.h
相关文件    : 
文件实现功能: ums网管的所有操作
作者        : 石城
版本        : V1.0  Copyright(C) 2012-2013 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2013/1/7    1.0         石城	      创建
******************************************************************************/
#if !defined(AFX_NETMNGCTRLIF_H__F47ED342_9A87_4124_8677_30F8A69F7D1A__INCLUDED_)
#define AFX_NETMNGCTRLIF_H__F47ED342_9A87_4124_8677_30F8A69F7D1A__INCLUDED_
#include "kdvdispevent.h"
#include "tpstruct.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUmsNetMngCtrlIF :public  CKdvDispEvent  
{
public:
	/**
    * 功能:	 	        发送添加网管请求
	* @param [in]       网管信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   ev_CnAgtAddNMServerCmd
	*/
	virtual u16  NetMngAddReq( const TTPNMServerCfg& tTPNMServerCfg ) = 0;

    /**
    * 功能:	 	        发送修改网管请求
	* @param [in]       网管信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   ev_CnAgtDelNMServerCmd
	*/
	virtual u16  NetMngModifyReq( const TTPNMServerCfg& tTPNMServerCfg ) = 0;

    /**
    * 功能:	 	        发送删除网管请求
	* @param [in]       网管信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   ev_CnAgtModifyNMServerCmd
	*/
	virtual u16  NetMngDeleteReq( const TTPNMServerCfg& tTPNMServerCfg ) = 0;

	/** 
	* 功能  获取网管信息
	* @param [in]  
	* @return  
	*/
	virtual u16 GetUmsNetMngData( vector<TTPNMServerCfg> &vecTTPNMServerCfg ) = 0;

 /** @}*/ // 操作单板接口

};

#endif // !defined(AFX_NETMNGCTRLIF_H__F47ED342_9A87_4124_8677_30F8A69F7D1A__INCLUDED_)
