/*****************************************************************************
模块名      : umstool网呈维护工具
文件名      : umsVTRCtrl.h
相关文件    : 
文件实现功能: ums录像机的所有操作
作者        : 石城
版本        : V1.0  Copyright(C) 2013-2014 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2013/3/5    1.0         石城         创建
******************************************************************************/
#if !defined(UMCLIB_VTRCTRL_H)
#define UMCLIB_VTRCTRL_H

#include "umsVTRCtrlIF.h"
#include "umsSession.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUmsVTRCtrl :public CUmsVTRCtrlIF
{  

/** @defgroup  操作单板接口实现部分
 *  @{
 */
	friend class CUmsSession;
private:
	CUmsVTRCtrl( const CUmsVTRCtrl &){};
    CUmsVTRCtrl( CUmsSession &cUmsSession );
	
public:
    ~CUmsVTRCtrl();
	
	/**
    * 功能:	 	        发送添加录像机请求
	* @param [in]       网管信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   ev_VTRAdd_req
	*/
	virtual u16  VTRAddReq( const TVcrCfg& tVTRCfg );

    /**
    * 功能:	 	        发送修改录像机请求
	* @param [in]       修改前和修改后的网管信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   ev_VTRMdy_req
	*/
	virtual u16  VTRModifyReq( const TVcrCfg& tVTRCfgOld, const TVcrCfg& tVTRCfgNew );

    /**
    * 功能:	 	        发送删除录像机请求
	* @param [in]       网管信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   ev_VTRDel_req
	*/
	virtual u16  VTRDeleteReq( const TVcrCfg& tVTRCfg );

	/** 
	* 功能  获取第一个录像机信息
	* @param [in]  
	* @return  
	*/
	virtual u16 GetUmsVTRData( TVcrCfg& tVTRCfg );

	/** 
	* 功能  获取全部录像机信息
	* @param [in]  
	* @return  
	*/
	virtual u16 GetUmsVTRData( vector<TVcrCfg> &vecTVcrCfg );

	/** 
	* 功能  获取录播服务器注册状态
	* @param [in]  
	* @return  
	*/
	virtual u16 GetVtrRegState( BOOL32 &bRegState );

	/** 
	* 功能  获取录播服务器基本信息
	* @param [in]  
	* @return  
	*/
	virtual u16 GetRecBaseInfo( vector<TRecBaseInfo> &vecTRecBaseInfo );

	/** 
	* 功能  获取录播服务器文件列表
	* @param [in]  
	* @return  
	*/
	virtual u16 GetRecFileListInfo( vector<TRecFileInfo> &vecTVtrFileInfo );

	/** 
	* 功能  获取录播服务器文件列表(无后缀)
	* @param [in]  
	* @return  
	*/
	virtual u16 GetRecFileListInfoNoSuffix( vector<TRecFileInfo> &vecTVtrFileInfoNoSuffix );

	/**
    * 功能:	 	        删除文件请求
	* @param [in]       文件信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   ev_rec_del_file_req
	*/
	virtual u16  RecDelFileReq( const TRecFileInfo& tRecFileInfo );

	/**
    * 功能:	 	        修改文件请求
	* @param [in]       文件信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   ev_rec_mdy_file_req
	*/
	virtual u16  RecMdyFileReq( const TRecFileInfo& tRecFileInfoOld, const TRecFileInfo& tRecFileInfoNew );

	/**
    * 功能:	 	        录像请求
	* @param [in]       录像信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   ev_rec_recorder_conf_req
	*/
	virtual u16 RecStartConfReq( const TRecConfInfo& tRecConfInfo );

	/**
    * 功能:	 	        暂停录像请求
	* @param [in]       录像信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   ev_rec_pause_conf_req
	*/
	virtual u16 RecPauseConfReq( const TRecConfRes& tRecConfRes );

	/**
    * 功能:	 	        继续录像请求
	* @param [in]       录像信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   ev_rec_resume_conf_req
	*/
	virtual u16 RecResumeConfReq( const TRecConfRes& tRecConfRes );

	/**
    * 功能:	 	        结束录像请求
	* @param [in]       录像信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   ev_rec_stop_conf_req
	*/
	virtual u16 RecStopConfReq( const TRecConfRes& tRecConfRes );

	/**
    * 功能:	 	        获取录像信息
	* @param [in]       录像信息
	* @return           u16 成功返回0,失败返回非0错误码
	*/
	virtual u16 GetRecConfInfo( vector<TConRecState>& vecTConRecState );

	/**
    * 功能:	 	        获取放像信息
	* @param [in]       放像信息
	* @return           u16 成功返回0,失败返回非0错误码
	*/
	virtual u16 GetPlayConfInfo( vector<TConfPlayStatus>& vecTConfPlayStatus );

	/**
    * 功能:	 	        开始放像请求
	* @param [in]       放像信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   ev_rec_start_play_req
	*/
	virtual u16 RecStartPlayReq( const TRecPlayInfo& tRecPlayInfo );
	
	/**
    * 功能:	 	        暂停放像请求
	* @param [in]       放像信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   ev_rec_pause_play_req
	*/
	virtual u16 RecPausePlayReq( const TPlayStatusMdyInfo& tPlayStatusMdyInfo );
	
	/**
    * 功能:	 	        继续放像请求
	* @param [in]       放像信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   ev_rec_resume_play_req
	*/
	virtual u16 RecResumePlayReq( const TPlayStatusMdyInfo& tPlayStatusMdyInfo );
	
	/**
    * 功能:	 	        结束放像请求
	* @param [in]       放像信息
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   ev_rec_stop_play_req
	*/
	virtual u16 RecStopPlayReq( const TPlayStatusMdyInfo& tPlayStatusMdyInfo );

	/**
    * 功能:	 	        会场格式请求
	* @param [in]       wConfID:会议ID, wMtID:会场ID
	* @return           u16 成功返回0,失败返回非0错误码
	* @remarks 消息：   ev_rec_mt_format
	*/
	virtual u16 RecMtFormatReq( const u16& wConfID, const u16& wMtID );

	/**
    * 功能:	 	        获取录像机ID
	* @param [in]       录像机ID
	* @return           u16 成功返回0,失败返回非0错误码
	*/
	virtual u16 GetEqpID( u8& byEqpID );
	
	//从m_vecTRecFileInfo中查找strFileNameNoSuffix对应的TRecFileInfo
	virtual TRecFileInfo FindFileName( CString strFileNameNoSuffix );

	/**
    * 功能:	 	        得到没有前缀和后缀的录像文件名
	* @param [in]       录像文件名
	* @return           没有前缀和后缀的录像文件名
	*/
	virtual CString GetNoSuffixString( CString strFileName );


protected:
 
	/**
    * 功能:	  添加录像机通知
	* @param [out]  cMsg	消息
	* @return  无
	* @remarks   
	*/
	void  OnAddVTRRsp(const CMessage& cMsg);
 
	/**
    * 功能:	  删除录像机通知
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
    void  OnDelVTRRsp(const CMessage& cMsg);

	/**
    * 功能:	  修改录像机通知
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
    void  OnModifyVTRRsp(const CMessage& cMsg);

	/**
    * 功能:	  网管录像机通知
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
    void  OnVTRNty(const CMessage& cMsg);

	/**
    * 功能:	  录播服务器基本信息通知
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
    void  OnRecBaseInfoNty(const CMessage& cMsg);

	/**
    * 功能:	  录播服务器注册状态通知
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
	void OnRecRegStatusNty(const CMessage& cMsg);

	/**
    * 功能:	  录播服务器文件列表通知
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
	void OnRecFileListInfoNty(const CMessage& cMsg);

	/**
    * 功能:	  修改文件失败回复
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
	void OnRecMdyFileNack(const CMessage& cMsg);

	/**
    * 功能:	  修改文件成功回复
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
	void OnRecMdyFileAck(const CMessage& cMsg);

	/**
    * 功能:	  会议录制信息通知
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
	void OnRecConfRecInfoNty(const CMessage& cMsg);

	/**
    * 功能:	  会议放像信息通知
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
	void OnRecConfPlayInfoNty(const CMessage& cMsg);
	

	/**
    * 功能:	  开始录像回复
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
	void OnRecStartConfRsp( const CMessage& cMsg );

	/**
    * 功能:	  暂停录像回复
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
	void OnRecPauseConfRsp( const CMessage& cMsg );

	/**
    * 功能:	  恢复录像回复
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
	void OnRecResumeConfRsp( const CMessage& cMsg );

	/**
    * 功能:	  结束录像回复
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
	void OnRecStopConfRsp( const CMessage& cMsg );

	/**
    * 功能:	  开始放像回复
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
	void OnRecStartPlayRsp( const CMessage& cMsg );

	/**
    * 功能:	  暂停放像回复
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
	void OnRecPausePlayRsp( const CMessage& cMsg );

	/**
    * 功能:	  继续放像回复
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
	void OnRecResumePlayRsp( const CMessage& cMsg );

	/**
    * 功能:	  结束放像回复
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
	void OnRecStopPlayRsp( const CMessage& cMsg );

	/**
    * 功能:	  会议挂断回复
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
	void OnHungUpConfRsp( const CMessage& cMsg );

	/**
    * 功能:	  会场格式回复
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
	void OnMtFormatRsp( const CMessage& cMsg );

	/**
    * 功能:	  断链通知
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
    void  OnLinkBreak(const CMessage& cMsg);

	/**
    * 功能:	 超时通知
	* @param [in]  u16 wEvent
	* @return  无
	* @remarks   
	*/
	virtual void OnTimeOut(u16 wEvent);

	virtual void DispEvent(const CMessage &cMsg);
   	


private:
	/**
    * 功能:	  注册消息响应函数
	* @param [in]  cMsg	消息
	* @return  无
	* @remarks   
	*/
	void  BuildEventsMap();

	TConRecState* FindRecInfo( TRecConfRes tRecConfRes );
	TConfPlayStatus* FindPlayInfo( TPlayStatusMdyInfo& tPlayStatusMdyInfo );

	//从m_vecTRecFileInfo设置m_vecTRecFileInfoNoSuffix
	void SetRecFileListNoSuffix();

	//转换(无后缀)TRecFileInfo为(有后缀)TRecFileInfo
	void TRecFileInfoNoSuffix2TRecFileInfo( const TRecFileInfo& tRecFileInfoNoSuffix, TRecFileInfo& tRecFileInfo );

	
private:
	CUmsSession *m_pUmsSession;

	vector<TVcrCfg> m_vecTVTRCfg;					//网管服务器信息
	vector<TRecBaseInfo> m_vecTRecBaseInfo;			//录播服务器基本信息
	vector<TRecFileInfo> m_vecTRecFileInfo;			//录播服务器文件列表
	vector<TRecFileInfo> m_vecTRecFileInfoNoSuffix;			//录播服务器文件列表(无后缀)
	int m_nLeft;									//录播服务器文件列表剩余包数，0表示已接收满
	vector<TConRecState> m_vecTConRecState;			//录像信息
	vector<TConfPlayStatus> m_vecTConfPlayStatus;	//放像信息

	BOOL32 m_bRegState;

/** @}*/ // 操作ums录像机信息接口实现部分
};

#endif // !defined(UMCLIB_VTRCTRL_H)
