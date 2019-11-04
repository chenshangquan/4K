/*****************************************************************************
模块名      : cmc cnclib接口
文件名      : cncsipinfoctrlif.h
相关文件    : 
文件实现功能: 获取sip服务器注册信息接口
作者        : 肖楚然
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2012/4/12   1.0         肖楚然        创建
******************************************************************************/
#ifndef __CNCSIPINFOCTRLIF_H__
#define __CNCSIPINFOCTRLIF_H__

#include "kdvdispevent.h"

class CCncSipInfoCtrlIF : public CKdvDispEvent
{
public:
	/** 
	* 功能  请求SIP注册信息
	* @param [in]  emType 注册类型
	* @return  
	* @remarks 
	*/
	virtual u16 ReqSipRegInfo( EmGetRegInfoType emType ) = 0;

	/** 
	* 功能  获取Cns注册信息
	* @return  vector<TTPAlias>  Cns注册信息
	* @remarks 
	*/
	virtual const vector<TAddrInfo>& GetCnsRegInfo() const = 0;

	/** 
	* 功能  获取Ums注册信息
	* @return  vector<TTPAlias>  Ums注册信息
	* @remarks
	*/
	virtual const vector<TTPAlias>& GetUmsRegInfo() const = 0;

};

#endif