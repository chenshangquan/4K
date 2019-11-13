/*****************************************************************************
模块名      : CCommonMgrIF
文件名      : commonmgrif.h
相关文件    : 
文件实现功能: umstool 消息管理公共模块
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2012/11/21     1.0         刘德印      创建
******************************************************************************/
#if !defined(AFX_DATAMGRIMP_H__0DA134CE_DB83_4357_B0E6_8A6707CBC456__INCLUDED_)
#define AFX_DATAMGRIMP_H__0DA134CE_DB83_4357_B0E6_8A6707CBC456__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "umclib.h" 

class CCommonMgrIF : public ISingleTon<CCommonMgrIF>
{
public:
	CCommonMgrIF();
	virtual ~CCommonMgrIF();

public:
	/*=============================================================================
    函 数 名:DestroyCommMgr
    功    能:销毁公共消息管理类指针
    参    数:无
    注    意:无
    返 回 值:无
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/11/21  1.0     刘德印    创建
    =============================================================================*/
    void DestroyCommMgr();

	u16 LinkUms();

	/*=============================================================================
    函 数 名:Connect
    功    能:连接到服务器
    参    数:LPCTSTR strIpAddr:        [in]        登陆服务器IP地址
			 u16 nPort:                [in]        通信端口
			 LPCTSTR pStrUserName:     [in]        登陆用户名
		   	 LPCTSTR pStrPswd:         [in]        登陆密码
    注    意:无
    返 回 值:u16 成功返回0;失败返回非0错误码 
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/11/21  1.0     刘德印    创建
    =============================================================================*/
	u16 Connect( u32 dwIp, u16 nPort, LPCTSTR pStrUserName, LPCTSTR pStrPswd ); 

	/*=============================================================================
    函 数 名:DisConnect
    功    能:断开服务器连接
    参    数:无
    注    意:无
    返 回 值:u16 成功返回0;失败返回非0错误码 
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/11/21  1.0     刘德印    创建
    =============================================================================*/
	u16 DisConnect(); 

	/*=============================================================================
    函 数 名:GetLoginInfo
    功    能:得到当前登陆服务器信息
    参    数:无
    注    意:无
    返 回 值:u16 成功返回0;失败返回非0错误码 
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/12/14  1.0     刘德印    创建
    =============================================================================*/
	TLoginInfo GetLoginInfo(){ return m_tLoginInfo;};

	/*=============================================================================
    函 数 名:Connect
    功    能:连接到服务器
    参    数:const TTPTime& time:        [in]       本地时间 
    注    意:无
    返 回 值:u16 成功返回0;失败返回非0错误码 
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/11/21  1.0     刘德印    创建
    =============================================================================*/
	u16 SysTimeSetReq(const TTPTime& time); 

	/*=============================================================================
    函 数 名:AuthCountReq
    功    能:授权数目请求
    参    数:无 
    注    意:无
    返 回 值:u16 成功返回0;失败返回非0错误码 
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/11/21  1.0     刘德印    创建
    =============================================================================*/
	u16 AuthCountReq();

	/*=============================================================================
    函 数 名:ConfCountReq
    功    能:会议数目请求
    参    数:无
    注    意:无
    返 回 值:u16 成功返回0;失败返回非0错误码 
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/11/21  1.0     刘德印    创建
    =============================================================================*/
	u16 ConfCountReq();

	/*=============================================================================
    函 数 名:RefreshUmsSysInfoReq
    功    能:刷新系统信息请求
    参    数:无
    注    意:无
    返 回 值:u16 成功返回0;失败返回非0错误码 
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/11/21  1.0     刘德印    创建
    =============================================================================*/
	u16 RefreshUmsSysInfoReq();

    /**
    * 功能:	 	        发送电视墙占用情况请求
	* @param [in]       无
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	u16  TvwUsedCountReq();

	/*=============================================================================
    函 数 名:RebootReq
    功    能:ums重启请求
    参    数:无
    注    意:无
    返 回 值:u16 成功返回0;失败返回非0错误码 
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人    修改内容
    2012/11/21  1.0     刘德印    创建
    =============================================================================*/
	u16 RebootReq();

	/**
    * 功能:	 获取单板信息
	* @param [out]  单板信息
	* @return  u16 成功返回0,失败返回非0错误码
	* @remarks 
	*/
	u16  GetTPBrdInfoData( TTPBrdInfo& tTPBrdInfo) const;


    /**
    * 功能:	 	        发送修改单板请求
	* @param [in]       板子信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	u16  BoardModifyReq( const TTPBrdCfg& tTPbrdCfg );


	    /**
    * 功能:	 	        板子升级请求
	* @param [in]       const TTPBrdUpGrade& tBrdUpGrade   升级信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	u16  BoardUpgradeReq(const TTPBrdUpGrade& tBrdUpGrade);

    /**
    * 功能:	 	        发送删除单板请求
	* @param [in]       板子信息无
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	u16  BoardDeleteReq( const TTPBrdCfg& tTPbrdCfg );

    /**
    * 功能:	 	        发送添加单板请求
	* @param [in]       板子信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	u16  BoardAddReq( const TTPBrdCfg& tTPbrdCfg );

    /**
    * 功能:	 	        发送添加单板模式请求
	* @param [in]       模式信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
//	u16  BoardModeAddReq( const TTPBrdMdlInfo& tTPbrdMdlInfo );

    /**
    * 功能:	 	        发送修改单板模式请求
	* @param [in]       模式信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	u16  BoardModeModifyReq( const TTPBrdMdlInfo& tTPbrdMdlInfo );

    /**
    * 功能:	 	        发送删除单板模式请求
	* @param [in]       模式信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	u16  BoardModeDeleteReq( const TTPBrdMdlInfo& tTPbrdMdlInfo );


	 /**
    * 功能:	 	        发送重启单板请求
	* @param [in]       TTPBrdPos 板子位置
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	u16  BoardRebootReq( const TTPBrdPos& tTPbrdPos );

	    /**
    * 功能:	 	        发送混音器占用请求
	* @param [in]       无
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	u16  BoardAudiomixReq();
	
	    /**
    * 功能:	 	        发送画面合成占用请求
	* @param [in]       无
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	u16  BoardVmpReq();

	    /**
    * 功能:	 	        发送码流适配占用请求
	* @param [in]       无
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	u16  BoardBasStreamReq();

    /**
    * 功能:	 	        发送添加电视墙单板请求
	* @param [in]       板子信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	u16  TvwBoardAddReq( const TTPBrdPos& tTPBrdPos );

    /**
    * 功能:	 	        发送修改电视墙单板请求
	* @param [in]       板子信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	u16  TvwBoardModifyReq( const TTPBrdPos& tTPBrdPos );

    /**
    * 功能:	 	        发送删除电视墙单板请求
	* @param [in]       板子信息无
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	u16  TvwBoardDeleteReq( const TTPBrdPos& tTPBrdPos );

    /**
    * 功能:	 	        发送添加电视墙单板模式请求
	* @param [in]       模式信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	u16  TvwBoardModeAddReq( const THduInfo& tTHduInfo );

    /**
    * 功能:	 	        发送修改电视墙单板模式请求
	* @param [in]       模式信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	u16  TvwBoardModeModifyReq( const THduInfo& tTHduInfo );

    /**
    * 功能:	 	        发送删除电视墙单板模式请求
	* @param [in]       模式位置
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	u16  TvwBoardModeDeleteReq( const TTPBrdPos& tTPBrdPos );

	    /**
    * 功能:	 	        发送重启电视墙单板请求
	* @param [in]       TTPBrdPos 板子位置
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	u16  TvwBoardRebootReq( const TTPBrdPos& tTPbrdPos );

		    /**
    * 功能:	 	        电视墙板子升级请求
	* @param [in]       const TTPBrdUpGrade& tBrdUpGrade   升级信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	u16  TvwBoardUpgradeReq(const TTPBrdUpGrade& tBrdUpGrade);


	    /**
    * 功能:	 	        添加电视墙风格请求
	* @param [in]       tHduStyleData 电视墙风格信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	u16  AddTvwStyleReq( const THduStyleData& tHduStyleData  );

	    /**
    * 功能:	 	        删除电视墙预案请求
	* @param [in]       tHduStyleData 电视墙风格信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   
	*/
	//u16  TvwStyleDeleteReq();

	/** 
	* 功能:  设置IP	 
	* @param [out]  cfg ：ip信息
	* @return u16 成功返回0;失败返回非0错误码
	* @remarks	如果 
	*/ 
	u16  UpdateEthnetCfg( TTPEthnetInfo &tEthnetInfo );

    /* 功能:	 gk 注册请求
    * @param [int]  tTvwInfo：请求播放的电视墙信息
    * @return    
    * @remarks  成功返回0，失败返回错误码
    */
	u16 UpdateGKCfg( TTPGKCfg &tGkwInfo );

	/*功  能	sip注册
	参  数	 
	返回值	成功返回0,失败返回非0错误码
	说  明	 */
	u16 UpdateSipCfg( TTPSipRegistrarCfg &tSipInfo );

	/**
    * 功能:	 	        发送添加网管请求
	* @param [in]       网管信息
	* @return           u16 成功返回0,失败返回非0错误码
	*/
	u16  NetMngAddReq( const TTPNMServerCfg& tTPNMServerCfg );

    /**
    * 功能:	 	        发送修改网管请求
	* @param [in]       网管信息
	* @return           u16 成功返回0,失败返回非0错误码
	*/
	u16  NetMngModifyReq( const TTPNMServerCfg& tTPNMServerCfg );

    /**
    * 功能:	 	        发送删除网管请求
	* @param [in]       网管信息
	* @return           u16 成功返回0,失败返回非0错误码
	*/
	u16  NetMngDeleteReq( const TTPNMServerCfg& tTPNMServerCfg );

	/**
    * 功能:	 	        发送添加录像机请求
	* @param [in]       录像机信息
	* @return           u16 成功返回0,失败返回非0错误码
	*/
	u16  VTRAddReq( const TVcrCfg& tVTRCfg );

    /**
    * 功能:	 	        发送修改录像机请求
	* @param [in]       录像机信息
	* @return           u16 成功返回0,失败返回非0错误码
	*/
	u16  VTRModifyReq( const TVcrCfg& tVTRCfgOld, const TVcrCfg& tVTRCfgNew );

    /**
    * 功能:	 	        发送删除录像机请求
	* @param [in]       录像机信息
	* @return           u16 成功返回0,失败返回非0错误码
	*/
	u16  VTRDeleteReq( const TVcrCfg& tVTRCfg );

	
	/**
    * 功能:  导入会议模板请求
	* @param [in]	const s8* strFileName	 会议模板文件名称 
	* @return           u16 成功返回0,失败返回非0错误码
	*/
	u16  ImportInfoReq(const s8* strFileName);

	/**
    * 功能:  导出会议模板请求
	* @param [in]	void 
	* @return           u16 成功返回0,失败返回非0错误码
	*/
	u16  ExportInfoReq();

	/**
    * 功能:  导出授权请求
	* @param [in]	void 
	* @return           u16 成功返回0,失败返回非0错误码
	*/
	u16  ExportAuthReq();
	


private:
	TLoginInfo m_tLoginInfo;		//存储登陆参数信息



};

#define COMMONMGRIFPTR     CCommonMgrIF::GetSingletonPtr()          //接口指针

#endif // !defined(AFX_DATAMGRIMP_H__0DA134CE_DB83_4357_B0E6_8A6707CBC456__INCLUDED_)
