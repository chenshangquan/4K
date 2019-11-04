/*****************************************************************************
模块名      : umstool网呈维护工具
文件名      : umstvwboardCtrl.h
相关文件    : 
文件实现功能: ums电视墙板卡的所有操作
作者        : 刘德印
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2012/11/23  1.0         刘德印      创建
******************************************************************************/
#if !defined(AFX_TVWBOARDCTRL_H__EB116E65_7B63_4B3E_B267_9C0B112DA0C1__INCLUDED_)
#define AFX_TVWBOARDCTRL_H__EB116E65_7B63_4B3E_B267_9C0B112DA0C1__INCLUDED_

#include "umstvwboardCtrlIF.h"
#include "umsSession.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUmsTvwBoardCtrl :public CUmsTvwBoardCtrlIF 
{  

/** @defgroup  操作电视墙单板接口实现部分
 *  @{
 */
	friend class CUmsSession;
private:
	CUmsTvwBoardCtrl( const CUmsTvwBoardCtrl &){};
    CUmsTvwBoardCtrl( CUmsSession &cUmsSession );
	
public:
    ~CUmsTvwBoardCtrl();

		/**
    * 功能:	 获取电视墙风格数据
	* @param [out]  THduStyleData  电视墙风格数据
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 
	*/
	virtual u16  GetUmsTvwStyleData( THduStyleData& tHduStyleData ) const;

		/**
    * 功能:	 获取电视墙单板数据
	* @param [out]  std::multimap<u8,THduCfg>  电视墙信息（层、槽、IP、通道信息等）
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 
	*/
	virtual u16  GetUmsTvwBoardData( std::multimap<u8,THduCfg>& mulmapTHduCfg ) const;

    /**
    * 功能:	 	        发送添加电视墙单板请求
	* @param [in]       板子信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	virtual u16  TvwBoardAddReq( const TTPBrdPos& tTPBrdPos );

    /**
    * 功能:	 	        发送修改电视墙单板请求
	* @param [in]       板子信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	virtual u16  TvwBoardModifyReq( const TTPBrdPos& tTPBrdPos );

    /**
    * 功能:	 	        发送删除电视墙单板请求
	* @param [in]       板子信息无
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	virtual u16  TvwBoardDeleteReq( const TTPBrdPos& tTPBrdPos );

    /**
    * 功能:	 	        发送添加电视墙单板模式请求
	* @param [in]       模式信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	virtual u16  TvwBoardModeAddReq( const THduInfo& tTHduInfo );

    /**
    * 功能:	 	        发送修改电视墙单板模式请求
	* @param [in]       模式信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	virtual u16  TvwBoardModeModifyReq( const THduInfo& tTHduInfo );

    /**
    * 功能:	 	        发送删除电视墙单板模式请求
	* @param [in]       模式位置
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	virtual u16  TvwBoardModeDeleteReq( const TTPBrdPos& tTPBrdPos );

	    /**
    * 功能:	 	        发送重启电视墙单板请求
	* @param [in]       TTPBrdPos 板子位置
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	virtual u16  TvwBoardRebootReq( const TTPBrdPos& tTPbrdPos );

		    /**
    * 功能:	 	        电视墙板子升级请求
	* @param [in]       const TTPBrdUpGrade& tBrdUpGrade   升级信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	virtual u16  TvwBoardUpgradeReq(const TTPBrdUpGrade& tBrdUpGrade);

	    /**
    * 功能:	 	        添加电视墙风格请求
	* @param [in]       tHduStyleData 电视墙风格信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	virtual u16  AddTvwStyleReq( const THduStyleData& tHduStyleData );

	   /**
    * 功能:	 	        删除电视墙预案请求
	* @param [in]       tHduStyleData 电视墙风格信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	//virtual u16  TvwStyleDeleteReq();

protected:
 
	/**
    * 功能:	  电视墙单板数据通知
	* @param [out]  cMsg	消息
	* @return  无
	* @remarks   
	*/
	void  OnRefreshTvwBoardNotify(const CMessage& cMsg);
 
	/**
    * 功能:	  添加电视墙单板数据通知
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
    void  OnTvwBoardAddNotify(const CMessage& cMsg);

	/**
    * 功能:	  修改电视墙单板数据通知
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
    void  OnTvwBoardModifyNotify(const CMessage& cMsg);

	/**
    * 功能:	  删除电视墙单板数据通知
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
    void  OnTvwBoardDeleteNotify(const CMessage& cMsg);

	/**
    * 功能:	  添加电视墙单板模式数据通知
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
    void  OnTvwBoardModeAddNotify(const CMessage& cMsg);

	/**
    * 功能:	 修改电视墙单板模式数据通知
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
    void  OnTvwBoardModeModifyNotify(const CMessage& cMsg);

	/**
    * 功能:	  删除电视墙单板模式数据通知
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
    void  OnTvwBoardModeDeleteNotify(const CMessage& cMsg);

    /**
    * 功能:	  电视墙风格通知
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
    void OnTvwStyleNotify(const CMessage& cMsg);


    /**
    * 功能:	  添加电视墙风格回应
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
    void OnAddTvwStyleRsp(const CMessage& cMsg);

    /**
    * 功能:	  删除电视墙预案应答
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
//    void OnTvwStyleDeleteRsp(const CMessage& cMsg);

    /**
    * 功能:	  重启电视墙板卡回应
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
    void OnRebootTvwBoardRsp(const CMessage& cMsg);

    /**
    * 功能:	  升级结果
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
    void OnTvwBoardUpgradeRsp(const CMessage& cMsg);

    /**
    * 功能:	  更新电视墙预案结果   by xhx
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
    void OnUpdateTvwStyleRsp(const CMessage& cMsg);

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

	void ResetMapTHduCfgData();

	/**
    * 功能:	  电视墙单板模式改变，同步更新电视墙预案    by xhx
	* @param   无
	* @return  无
	* @remarks   
	*/
	void UpdateUmsTvwStyleData();

private:
	CUmsSession *m_pUmsSession;
	
	std::multimap<u8,THduCfg> m_mulmapTHduCfg;    //对应层号及电视墙单板信息

 	TTPBrdPos m_tTPAddBrdPos;
 	TTPBrdPos m_tTPModifyBrdPos;
	TTPBrdPos m_tTPDelBrdPos;
	THduInfo m_tAddTvwBrdMdlTHduInfo;
	THduInfo m_tModifyTvwBrdMdlTHduInfo;
 	TTPBrdPos m_tDelTvwBrdMdlTPBrdPos;

 	TTPBrdPos m_tRebootTPBrdPos;

    THduStyleData m_tHduStyleData; //电视墙风格

/** @}*/ // 操作ums电视墙板卡信息接口实现部分
};

#endif // !defined(AFX_TVWBOARDCTRL_H__EB116E65_7B63_4B3E_B267_9C0B112DA0C1__INCLUDED_)
