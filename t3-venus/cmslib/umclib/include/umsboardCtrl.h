/*****************************************************************************
模块名      : umstool网呈维护工具
文件名      : umsboardCtrl.h
相关文件    : 
文件实现功能: ums单板的所有操作
作者        : 刘德印
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2012/11/23  1.0         刘德印      创建
******************************************************************************/
#if !defined(AFX_BOARDCTRL_H__EB116E65_7B63_4B3E_B267_9C0B112DA0C1__INCLUDED_)
#define AFX_BOARDCTRL_H__EB116E65_7B63_4B3E_B267_9C0B112DA0C1__INCLUDED_

#include "umsboardCtrlIF.h"
#include "umsSession.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUmsBoardCtrl :public CUmsBoardCtrlIF 
{  

/** @defgroup  操作单板接口实现部分
 *  @{
 */
	friend class CUmsSession;
private:
	CUmsBoardCtrl( const CUmsBoardCtrl &){};
    CUmsBoardCtrl( CUmsSession &cUmsSession );
	
public:
    ~CUmsBoardCtrl();
	

		/**
    * 功能:	 获取单板占用情况信息数据
	* @param [out]  TTPBrdUsedInfo	单板占用信息(包括混音器、画面合成、码流适配器占用)
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 
	*/
	virtual u16  GetUmsBoardUsedData( TTPBrdUsedInfo& tBoardUsed) const;


    /**
    * 功能:	 	        发送修改单板请求
	* @param [in]       板子信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	virtual u16  BoardModifyReq( const TTPBrdCfg& tTPbrdCfg );

    /**
    * 功能:	 	        发送删除单板请求
	* @param [in]       板子信息无
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	virtual u16  BoardDeleteReq( const TTPBrdCfg& tTPbrdCfg );

    /**
    * 功能:	 	        发送添加单板请求
	* @param [in]       板子信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	virtual u16  BoardAddReq( const TTPBrdCfg& tTPbrdCfg );

    /**
    * 功能:	 	        发送添加单板模式请求
	* @param [in]       模式信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
//	virtual u16  BoardModeAddReq( const TTPBrdMdlInfo& tTPbrdMdlInfo );

    /**
    * 功能:	 	        发送修改单板模式请求
	* @param [in]       模式信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	virtual u16  BoardModeModifyReq( const TTPBrdMdlInfo& tTPbrdMdlInfo );

    /**
    * 功能:	 	        发送删除单板模式请求
	* @param [in]       模式信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	virtual u16  BoardModeDeleteReq( const TTPBrdMdlInfo& tTPbrdMdlInfo );

	    /**
    * 功能:	 	        发送重启单板请求
	* @param [in]       TTPBrdPos 板子位置
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	virtual u16  BoardRebootReq( const TTPBrdPos& tTPbrdPos );

	    /**
    * 功能:	 	        发送混音器占用请求
	* @param [in]       无
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	virtual u16  BoardAudiomixReq();
	
	    /**
    * 功能:	 	        发送画面合成占用请求
	* @param [in]       无
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	virtual u16  BoardVmpReq();

	    /**
    * 功能:	 	        发送码流适配占用请求
	* @param [in]       无
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	virtual u16  BoardBasStreamReq();

	    /**
    * 功能:	 	        板子升级请求
	* @param [in]       const TTPBrdUpGrade& tBrdUpGrade   升级信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	virtual u16  BoardUpgradeReq(const TTPBrdUpGrade& tBrdUpGrade);


protected:
 
	/**
    * 功能:	  单板数据通知
	* @param [out]  cMsg	消息
	* @return  无
	* @remarks   
	*/
	void  OnRefreshboardNotify(const CMessage& cMsg);
 
	/**
    * 功能:	  修改单板数据通知
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
    void  OnBoardModifyNotify(const CMessage& cMsg);

	/**
    * 功能:	  删除单板数据通知
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
    void  OnBoardDeleteNotify(const CMessage& cMsg);

	/**
    * 功能:	  添加单板数据通知
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
    void  OnBoardAddNotify(const CMessage& cMsg);

	/**
    * 功能:	  添加单板模式数据通知
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
//  void  OnBoardModeAddNotify(const CMessage& cMsg);


	/**
    * 功能:	  修改单板模式数据通知
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
    void  OnBoardModeModifyNotify(const CMessage& cMsg);

	/**
    * 功能:	  删除单板模式数据通知
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
    void  OnBoardModeDeleteNotify(const CMessage& cMsg);

		/**
    * 功能:	  单板占用信息数据通知
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
    void  OnBoardUsedNotify(const CMessage& cMsg);

    /**
    * 功能:	  升级结果
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
    void OnBoardUpgradeRsp(const CMessage& cMsg);

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

private:
	CUmsSession *m_pUmsSession;
	
	TTPBrdInfo m_tTPBrdInfo;
	TTPBrdCfg m_tTPBrdCfgModify;
	TTPBrdCfg m_tTPBrdCfgAdd;
	TTPBrdCfg m_tTPBrdCfgDelete;
	TTPBrdMdlInfo m_tTPBrdModeCfgModify;
	TTPBrdMdlInfo m_tTPBrdModeCfgAdd;
	TTPBrdMdlInfo m_tTPBrdModeCfgDelete;

	TTPBrdUsedInfo m_tBoardUsed;

/** @}*/ // 操作ums单板信息接口实现部分
};

#endif // !defined(AFX_BOARDCTRL_H__EB116E65_7B63_4B3E_B267_9C0B112DA0C1__INCLUDED_)
