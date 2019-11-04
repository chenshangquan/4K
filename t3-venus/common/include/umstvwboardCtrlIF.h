/*****************************************************************************
模块名      : umstool网呈维护工具
文件名      : umstvwboardCtrlIF.h
相关文件    : 
文件实现功能: ums电视墙单板板卡的所有操作
作者        : 刘德印
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2012/11/23  1.0         刘德印      创建
******************************************************************************/
#if !defined(AFX_TVWBOARDCTRLIF_H__F47ED342_9A87_4124_8677_30F8A69F7D1A__INCLUDED_)
#define AFX_TVWBOARDCTRLIF_H__F47ED342_9A87_4124_8677_30F8A69F7D1A__INCLUDED_
#include "kdvdispevent.h"
#include "ummessagestruct.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUmsTvwBoardCtrlIF :public  CKdvDispEvent  
{
public:

		/**
    * 功能:	 获取电视墙风格数据
	* @param [out]  THduStyleData  电视墙风格数据
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 
	*/
	virtual u16  GetUmsTvwStyleData( THduStyleData& tHduStyleData ) const = 0;	
				/**
    * 功能:	 获取电视墙单板数据
	* @param [out]  std::multimap<u8,THduCfg>  电视墙信息（层、槽、IP、通道信息等）
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 
	*/
	virtual u16  GetUmsTvwBoardData( std::multimap<u8,THduCfg>& mulmapTHduCfg ) const = 0;

    /**
    * 功能:	 	        发送添加电视墙单板请求
	* @param [in]       板子信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	virtual u16  TvwBoardAddReq( const TTPBrdPos& tTPBrdPos ) = 0;

    /**
    * 功能:	 	        发送修改电视墙单板请求
	* @param [in]       板子信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	virtual u16  TvwBoardModifyReq( const TTPBrdPos& tTPBrdPos ) = 0;

    /**
    * 功能:	 	        发送删除电视墙单板请求
	* @param [in]       板子信息无
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	virtual u16  TvwBoardDeleteReq( const TTPBrdPos& tTPBrdPos ) = 0;

    /**
    * 功能:	 	        发送添加电视墙单板模式请求
	* @param [in]       模式信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	virtual u16  TvwBoardModeAddReq( const THduInfo& tTHduInfo ) = 0;

    /**
    * 功能:	 	        发送修改电视墙单板模式请求
	* @param [in]       模式信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	virtual u16  TvwBoardModeModifyReq( const THduInfo& tTHduInfo ) = 0;

    /**
    * 功能:	 	        发送删除电视墙单板模式请求
	* @param [in]       模式位置
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	virtual u16  TvwBoardModeDeleteReq( const TTPBrdPos& tTPBrdPos ) = 0;

	    /**
    * 功能:	 	        发送重启电视墙单板请求
	* @param [in]       TTPBrdPos 板子位置
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	virtual u16  TvwBoardRebootReq( const TTPBrdPos& tTPbrdPos ) = 0;

			    /**
    * 功能:	 	        电视墙板子升级请求
	* @param [in]       const TTPBrdUpGrade& tBrdUpGrade   升级信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	virtual u16  TvwBoardUpgradeReq(const TTPBrdUpGrade& tBrdUpGrade) = 0;

	    /**
    * 功能:	 	        添加电视墙风格请求
	* @param [in]       tHduStyleData 电视墙风格信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	virtual u16  AddTvwStyleReq( const THduStyleData& tHduStyleData ) = 0;

	    /**
    * 功能:	 	        删除电视墙预案请求
	* @param [in]       tHduStyleData 电视墙风格信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	//virtual u16  TvwStyleDeleteReq() = 0;

 /** @}*/ // 操作电视墙单板板卡接口

};

#endif // !defined(AFX_TVWBOARDCTRLIF_H__F47ED342_9A87_4124_8677_30F8A69F7D1A__INCLUDED_)
