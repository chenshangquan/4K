/*****************************************************************************
模块名      : umstool网呈维护工具
文件名      : umsVTRCtrlIF.h
相关文件    : 
文件实现功能: ums录像机的所有操作
作者        : 石城
版本        : V1.0  Copyright(C) 2013-2014 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2013/3/5    1.0         石城	      创建
******************************************************************************/
#if !defined(UMCLIB_VTRCTRLIF_H)
#define UMCLIB_VTRCTRLIF_H
#include "kdvdispevent.h"
#include "tpstruct.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUmsVTRCtrlIF :public  CKdvDispEvent  
{
public:
	/**
    * 功能:	 	        发送添加录像机请求
	* @param [in]       网管信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   ev_VTRAdd_req
	*/
	virtual u16  VTRAddReq( const TVcrCfg& tVTRCfg ) = 0;

    /**
    * 功能:	 	        发送修改录像机请求
	* @param [in]       网管信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   ev_VTRMdy_req
	*/
	virtual u16  VTRModifyReq( const TVcrCfg& tVTRCfgOld, const TVcrCfg& tVTRCfgNew ) = 0;

    /**
    * 功能:	 	        发送删除录像机请求
	* @param [in]       网管信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   ev_VTRDel_req
	*/
	virtual u16  VTRDeleteReq( const TVcrCfg& tVTRCfg ) = 0;

	/** 
	* 功能  获取录像机信息
	* @param [in]  
	* @return  
	*/
	virtual u16 GetUmsVTRData( TVcrCfg& tVTRCfg ) = 0;

	/** 
	* 功能  获取全部录像机信息
	* @param [in]  
	* @return  
	*/
	virtual u16 GetUmsVTRData( vector<TVcrCfg> &vecTVcrCfg ) = 0;

	/** 
	* 功能  获取录播服务器注册状态
	* @param [in]  
	* @return  
	*/
	virtual u16 GetVtrRegState( BOOL32 &bRegState ) = 0;

	/** 
	* 功能  获取录播服务器基本信息
	* @param [in]  
	* @return  
	*/
	virtual u16 GetRecBaseInfo( vector<TRecBaseInfo> &vecTRecBaseInfo ) = 0;

	/** 
	* 功能  获取录播服务器文件列表
	* @param [in]  
	* @return  
	*/
	virtual u16 GetRecFileListInfo( vector<TRecFileInfo> &vecTVtrFileInfo ) = 0;

	/** 
	* 功能  获取录播服务器文件列表(无后缀)
	* @param [in]  
	* @return  
	*/
	virtual u16 GetRecFileListInfoNoSuffix( vector<TRecFileInfo> &vecTVtrFileInfoNoSuffix ) = 0;

	/**
    * 功能:	 	        删除文件请求
	* @param [in]       文件信息
	*/
	virtual u16  RecDelFileReq( const TRecFileInfo& tRecFileInfo ) = 0;

	/**
    * 功能:	 	        修改文件请求
	* @param [in]       文件信息
	*/
	virtual u16  RecMdyFileReq( const TRecFileInfo& tRecFileInfoOld, const TRecFileInfo& tRecFileInfoNew ) = 0;

	/**
    * 功能:	 	        录像请求
	* @param [in]       录像信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   ev_rec_recorder_conf_req
	*/
	virtual u16 RecStartConfReq( const TRecConfInfo& tRecConfInfo ) = 0;

	/**
    * 功能:	 	        暂停录像请求
	* @param [in]       录像信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   ev_rec_pause_conf_req
	*/
	virtual u16 RecPauseConfReq( const TRecConfRes& tRecConfRes ) = 0;

	/**
    * 功能:	 	        继续录像请求
	* @param [in]       录像信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   ev_rec_resume_conf_req
	*/
	virtual u16 RecResumeConfReq( const TRecConfRes& tRecConfRes ) = 0;

	/**
    * 功能:	 	        结束录像请求
	* @param [in]       录像信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   ev_rec_stop_conf_req
	*/
	virtual u16 RecStopConfReq( const TRecConfRes& tRecConfRes ) = 0;

	/**
    * 功能:	 	        获取录像信息
	* @param [in]       录像信息
	* @return           u16 成功返回0,失败返回非0错误码
	*/
	virtual u16 GetRecConfInfo( vector<TConRecState>& vecTConRecState ) = 0;

	/**
    * 功能:	 	        获取放像信息
	* @param [in]       放像信息
	* @return           u16 成功返回0,失败返回非0错误码
	*/
	virtual u16 GetPlayConfInfo( vector<TConfPlayStatus>& vecTConfPlayStatus ) = 0;

	/**
    * 功能:	 	        开始放像请求
	* @param [in]       放像信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   ev_rec_start_play_req
	*/
	virtual u16 RecStartPlayReq( const TRecPlayInfo& tRecPlayInfo ) = 0;
	
	/**
    * 功能:	 	        暂停放像请求
	* @param [in]       放像信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   ev_rec_pause_play_req
	*/
	virtual u16 RecPausePlayReq( const TPlayStatusMdyInfo& tPlayStatusMdyInfo ) = 0;
	
	/**
    * 功能:	 	        继续放像请求
	* @param [in]       放像信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   ev_rec_resume_play_req
	*/
	virtual u16 RecResumePlayReq( const TPlayStatusMdyInfo& tPlayStatusMdyInfo ) = 0;
	
	/**
    * 功能:	 	        结束放像请求
	* @param [in]       放像信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   ev_rec_stop_play_req
	*/
	virtual u16 RecStopPlayReq( const TPlayStatusMdyInfo& tPlayStatusMdyInfo ) = 0;

	/**
    * 功能:	 	        会场格式请求
	* @param [in]       wConfID:会议ID, wMtID:会场ID
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   ev_rec_mt_format
	*/
	virtual u16 RecMtFormatReq( const u16& wConfID, const u16& wMtID ) = 0;

	/**
    * 功能:	 	        获取录像机ID
	* @param [in]       录像机ID
	* @return           u16 成功返回0,失败返回非0错误码
	*/
	virtual u16 GetEqpID( u8& byEqpID ) = 0;

	//从m_vecTRecFileInfo中查找strFileNameNoSuffix对应的TRecFileInfo
	virtual TRecFileInfo FindFileName( CString strFileNameNoSuffix ) = 0;

	/**
    * 功能:	 	        得到没有前缀和后缀的录像文件名
	* @param [in]       录像文件名
	* @return           没有前缀和后缀的录像文件名
	*/
	virtual CString GetNoSuffixString( CString strFileName ) = 0;

 /** @}*/ // 操作录像机接口

};

#endif // !defined(UMCLIB_VTRCTRLIF_H)
