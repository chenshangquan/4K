/*****************************************************************************
模块名      : umstool网呈维护工具
文件名      : umsexportCtrlIF.h
相关文件    : 
文件实现功能: ums导入导出的所有操作
作者        : 刘德印
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2012/11/23  1.0         刘德印      创建
******************************************************************************/
#if !defined(AFX_EXPORTCTRLIF_H__F47ED342_9A87_4124_8677_30F8A69F7D1A__INCLUDED_)
#define AFX_EXPORTCTRLIF_H__F47ED342_9A87_4124_8677_30F8A69F7D1A__INCLUDED_
#include "kdvdispevent.h"
#include "ummessagestruct.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUmsExportCtrlIF :public  CKdvDispEvent  
{
public:

   /**
    * 功能:	   导出会议模板请求
	* @param   无 
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 
	*/
	virtual u16  ExportInfoReq()   = 0 ;

   /**
    * 功能:	   导入会议模板请求
	* @param   无 
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 
	*/
	virtual u16  ImportInfoReq(const s8* strFileName)   = 0 ;

	/**
    * 功能:	   导出授权请求
	* @param   无 
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 
	*/
	virtual u16  ExportAuthReq()   = 0 ;


 /** @}*/ // 操作ums导入导出接口

};

#endif // !defined(AFX_EXPORTCTRLIF_H__F47ED342_9A87_4124_8677_30F8A69F7D1A__INCLUDED_)
