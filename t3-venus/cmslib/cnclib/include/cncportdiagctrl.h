#include "cnsSession.h"

class CCncPortDiagCtrl : public CCncPortDiagCtrlIF
{
public:
	CCncPortDiagCtrl( CCnsSession &cSession );
	~CCncPortDiagCtrl();

	//获取软件版本信息
	virtual s8* GetSoftVersionInfo();
	virtual EmCnModel GetEmCnModelInfo();
	//音频接口信息
	virtual TTpAudioPortInfo* GetAudioPortInfo();							
	virtual	u16 SetAudioPortInfoCmd( const TTpAudioPortInfo** atAudioPortInfo );
	virtual u16 SetMic10InfoCmd( const TTpMic10Info &tTPMic10Info );
	virtual u16 SetNoDeskAudioCmd( bool bNoDeskAudio );
	virtual	u16 DefaultAudioPortCmd( const TTpAudioPortInfo** atAudioPortInfo );		

	//音频配置接口
	virtual const TTPMPAudioInfo& GetAudioInfo() const;
	virtual BOOL * GetWhiteNoiseInfo();
	virtual u16 SetAudioInfoCmd( const TTPMPAudioInfo* atAudioPortInfo );
	virtual u16 SetListenPortCmd( const EmAudMixType emAudMixtype, const u8 byAudMixVolume );
	virtual u16 SetAux2OutCmd( const EmAudExtend emAudExtend, const u8 byAudExtendVolume );
	virtual	u16 DefaultAudioSetCmd( const TTPMPAudioInfo* atAudioPortInfo );
	virtual u16 DefaultListenPortSetCmd(const EmAudMixType emAudMixtype, const u8 byAudMixVolume);
	virtual u16 DefaultAux2OutSetCmd( const EmAudExtend emAudExtend, const u8 byAudExtendVolume);
	virtual u16 SetAudioWhiteNoiseCmd(BOOL bIsOpen ,u32 dwWhiteNoisePort);

	//主视频配置接口
	virtual const TTPVideoInfoTool &GetMainAudioInfo( ) const;
	virtual u16 DefaultMainAudioCmd( const TTPVideoInfoTool* atAudioInfo );
	virtual u16 SetMainAudioInfoCmd( const TTPVideoInfoTool* ptAudioInfo );
	
	//演示源配置
	virtual TVgaInfo *GetDisplaySourceInfo( );
	virtual TTPDualDisplayStrategy &GetDisplayStrategyInfo( );
	virtual	EmVgaType GetDefaultDisplay( );

	virtual u16 SetDefaultDemonStrationCmd( const TVgaInfo *ptDisplaySource, 
		const TTPDualDisplayStrategy *ptDualDisplayStrategy, 
		const EmVgaType emDefaultDisplay );

	u16 SetDemonStrationCmd( const TVgaInfo *ptDisplaySource,
		const TTPDualDisplayStrategy *ptDualDisplayStrategy, const EmVgaType emDefaultDisplay );
	//图像参数调节
	virtual u16 SetDefParameterCmd(const TTPImageAdjustParam * pImageAdjustParam );
	virtual TTPImageAdjustParam * GetImageParam();
	virtual u16 SetParameterCmd(const TTPImageAdjustParam * pImageAdjustParam );

	//添加和删除路由
	virtual u16  RouteMngAddCmd( const TRouteCfg& tRouteCfg );
	virtual u16  RouteMngDelCmd( const TRouteCfg& tRouteCfg );

	//网络丢包信息
	virtual u16 LostPacketInfoReq();
	virtual const CString& GetLostPacketInfo()const;			

	//上传下行速率
	virtual const TTPUpDownSpeedInfo& GetUpDownstreamRate()const;
	//抓包
	virtual u16 SetCaptureStateCmd( const BOOL& bCapture ) const;

	//选择音视频矩阵方案的命令
	virtual u16 SelAVMatrixCmd( const TTPVgaMixInfo& tVgaMixInfo );
	//获取端口诊断结果
	virtual const TTPVideoDiagInfo& GetVideoDiagInfo()const;
	virtual const TTPAudioDiagInfo& GetAudioDiagInfo()const;

	//获取网络安全FTP和TELNET信息
	virtual const TTPFtpInfo& GetFtpInfo()const;
	virtual const TTPTelnetInfo& GetTelnetInfo()const;

	//停止诊断测试请求
	virtual u16 StopAVMatrixReq();

	//Tpad列表
	virtual	const TTPTPadList& GetTpadList()const;								
	virtual	u16 UpdateTpadListReq();	

	//重启cns
	virtual u16 RebootCns();

	//升级T300
	virtual u16 UpgradeCns( const TTPFTPFileInfo& tVerFileInfo );

	//维护工具刷新界面请求
	virtual u16 ReqRefresh();

	//音频混音数配置命令
	virtual u16 AudiotMixerCmd( const u8** aAudioMixerInfo );
	virtual u8* GetAudioMixerInfo();
	virtual u16 DefaultMixerCmd( const u8** aAudioMixerInfo );
	virtual	u16 SnapShotCmd( );
	//音频均衡器配置命令
	virtual u16 AudioEqualizerCmd( const TTPEqualizer** atEqualizer );
	virtual TTPEqualizer* GetAudioEqualizer();
	virtual u16 DefaultEqCmd( const TTPEqualizer** atEqualizer );

	//呼叫服务器地址
	virtual u16 CallServerCmd( const TTPCallSerInfo& tCallSerInfo );
	virtual const TTPCallSerInfo& GetCallServerInfo()const;

	//升级服务器地址
	virtual u16 UpgradeSerCmd( const TTPUpgradeSer& tUpgradeSer );
	virtual const TTPUpgradeSer& GetUpgradeSerInfo()const;

	virtual u16 SetDataConfSerCmd( const TTPDataConfInfo& tWBSerIp );

	virtual u16 SetMatrixSerCmd( const TTPMatrixServerInfo& tTPMatrixServerInfo);

	virtual u16 SetNtpSerCmd( const TTPNtpSer& tTpNtpSer);

	virtual u16 SetQtEncryptSerCmd( const TTpQtEncryptCfg& tTpQtEncryptCfg);

	//台标文件上传成功通知
	virtual u16 ConfSignCmd( const BOOL& bOk, u8 byIndex );

	//会议优选格式
	virtual u16 VideoFormatCmd( const TTPVidForamt& tVidForamt );
	virtual const TTPVidForamt& GetVideoFormatInfo()const;

	//演示优选格式
	virtual u16 DualVideoFormatCmd( const TTPVidForamt& tVidForamt );
	virtual const TTPVidForamt& GetDualVideoFormatInfo()const;

	//单屏码率
	virtual u16 CallRateCmd( const u16 wCallRate );
	virtual const u16 GetCallRate()const;

	//演示码率
	virtual u16 DualCallRateCmd( const u16 wDualCallRate );
	virtual const u16 GetDualCallRate()const;

	//会议轮询
	virtual u16 ConfPollCmd( const TTPPollInfo& tPollInfo );
	virtual const TTPPollInfo& GetConfPollInfo()const;

	//会议讨论
	virtual u16 ConfDisCmd( const BOOL& bDis );
	virtual const BOOL& GetConfDisInfo()const;

	//音频格式
	virtual u16 AudioFormatCmd( const EmTpAudioFormat& emAudioFormat );
	virtual const EmTpAudioFormat& GetAudioFormatInfo() const;

	//路由配置
	virtual void GetRouteInfoData( vector<TRouteCfg> &vecTRouteCfg )const;
protected:
	virtual void OnTimeOut(u16 wEvent); 
    virtual void DispEvent(const CMessage &cMsg);
	void BuildEventsMap();
	void OnLinkBreak(const CMessage& cMsg);

	void OnAudioPortInfoInd(const CMessage& cMsg);
	void OnSetDesktopMicInfoNty( const CMessage& cMsg );
	void OnSetDesktopMicInfoInd( const CMessage& cMsg );
	void OnSetMic10InfoInd( const CMessage& cMsg );
	void OnDefaultAudPortInd(const CMessage& cMsg);
	void OnLostPacketInfoRsp(const CMessage& cMsg);
	void OnUpDownstreamRateNty(const CMessage& cMsg);
	void OnAVMatrixInfoInd(const CMessage& cMsg);
	void OnTpadListRsp(const CMessage& cMsg);
	void OnTpadListNty(const CMessage& cMsg);

	void OnAudiotMixerInd(const CMessage& cMsg);
	void OnDefaulttMixerInd(const CMessage& cMsg);
	void OnAudioEqualizerInd(const CMessage& cMsg);
	void OnDefaultEqInd(const CMessage& cMsg);
	void OnUpgradeCnsInd(const CMessage& cMsg);
	void OnCallServerNty(const CMessage& cMsg);
	void OnCallServerInd(const CMessage& cMsg);

	void OnUpgradeSerNty(const CMessage& cMsg);
	void OnUpgradeSerInd(const CMessage& cMsg);

	void OnVideoFormatInd(const CMessage& cMsg);
	void OnDualVideoFormatInd(const CMessage& cMsg);

	void OnCallRateInd(const CMessage& cMsg);
	void OnDualCallRateInd(const CMessage& cMsg);

	void OnConfPollInd(const CMessage& cMsg);
	void OnConfDisInd(const CMessage& cMsg);

	void OnVerInfoNty(const CMessage& cMsg);
	void OnAudioFormatInd( const CMessage& cMsg );

	void OnStopAVMatrixRsp(const CMessage& cMsg);
    //数据会议服务器ipNty
    void OnWBServerNty( const CMessage& cMsg );
	void OnWBServerInd( const CMessage& cMsg );
	//矩阵服务器ipNty
	void OnSetMatrixServerInfoNty( const CMessage& cMsg );
	void OnSetMatrixServerInfoInd( const CMessage& cMsg );
	//量子加密服务器ipNty
	void OnSetQtEntryptInfoNty( const CMessage &cMsg );
	void OnSetQtEncryptInfoInd( const CMessage &cMsg );
	//时间同步服务器
	void OnSetNtpServerInfoNty( const CMessage &cMsg );
	void OnSetNtpServerInfoInd( const CMessage &cMsg ); 
	//网络安全
	void OnSetFtpStateNty( const CMessage &cMsg );
	void OnOpenFtpRsp( const CMessage &cMsg );
	void OnSetFtpInfoNty( const CMessage &cMsg );
	void OnSetFtpRsp( const CMessage &cMsg );
	void OnSetTelnetStateNty( const CMessage &cMsg );
	void OnOpenTelnetRsp( const CMessage &cMsg );
	void OnSetTelnetInfoNty( const CMessage &cMsg );
	void OnSetTelnetRsp( const CMessage &cMsg );

    const TTPDataConfInfo& GetWBSerIp() const;
	const TTpQtEncryptCfg& GetQtEncryptCfg() const;
	const TTPNtpSer& GetNtpSerIP() const;

	const TTPMatrixServerInfo& GetMatrixSerInfo() const;

	void OnAudioInfoInd(const CMessage& cMsg);

	void OnVedioPortNameInd(const CMessage& cMsg);

	void OnDefaultAudioSetInd(const CMessage& cMsg);

	void OnAudioWhiteNoiseRsp(const CMessage& cMsg);

	void OnUpdateWhiteNoise(const CMessage& cMsg);
	
	void OnSetMixTypeInd(const CMessage& cMsg);

	void OnSetAUX2InfoInd(const CMessage& cMsg);

	void OnVedioSourceInd(const CMessage& cMsg);

	void OnDefaultMainAudioInd( const CMessage& cMsg );

	void OnDisplaySourceInd( const CMessage& cMsg );

	void OnDefaultDisplaySourceInd(const CMessage& cMsg);

	void OnImageAdjustInd( const CMessage& cMsg );

	void OnDefaultImageAdjustInd( const CMessage& cMsg );
	void OnSnapShotInd( const CMessage& cMsg );

	//路由配置
	void OnSetRouteInfoNty( const CMessage& cMsg );
	void OnAddRouteInfoInd( const CMessage& cMsg );
	void OnDelRouteInfoInd( const CMessage& cMsg );
private:
	CCnsSession		*m_pSession;
	s8  m_achVerInfo[MAX_DEVICEVER_LEN];
	EmCnModel m_emCnModel;
	TTpAudioPortInfo	m_atAudioPortInfo[3];
	u8	m_aAudioMixerInfo[4];
	CString	m_strLostPacketInfo;
	TTPAudioDiagInfo	m_tAudioDiagInfo;
	TTPVideoDiagInfo	m_tVideoDiagInfo;
	TTPTPadList		m_tTPadList;
	TTPUpDownSpeedInfo		m_tUpDownSpeedInfo;

	TTPEqualizer     m_atEqualizer[3];
	TTPCallSerInfo   m_tCallSerInfo;
	TTPUpgradeSer	 m_tUpgradeSer;
	TTPVidForamt	 m_tVidForamt;
	TTPVidForamt	 m_tDualVidForamt;
	TTPPollInfo		 m_tPollInfo;
	EmTpAudioFormat  m_emAudioFormat;
	BOOL m_bDis;
	u16	 m_wCallRate;
	u16  m_wDualCallRate;

    TTPDataConfInfo m_tWBSerIp;
	TTPMatrixServerInfo m_tMatrixServerInfo;
	TTpQtEncryptCfg m_tTpQtEncryptCfg;
	TTPNtpSer  m_tTpNtpSerIp;
	TTPMPAudioInfo  m_tAudioSetInfo;
	BOOL m_bWhiteNoise[3];

	TTPVideoInfoTool m_tVideoSource;
	TVgaInfo         m_atDemoSourceName[CNS_VGA_TYPE_NUM];
	TTPDualDisplayStrategy   m_tDisplayStrategy;
	EmVgaType        m_emDefaultDisplay;
	TVgaInfo		 m_tDefaultDemoSource;

	TTPImageAdjustParam m_atImageAdjust[3];

	TTPFtpInfo       m_tTPFtpInfo;
	TTPTelnetInfo    m_tTPTelnetInfo;

	vector<TRouteCfg>	m_vecTRouteCfg;		//路由配置列表

	TTpMic10Info     m_tTpMic10Info;        //卡农10音频配置
};