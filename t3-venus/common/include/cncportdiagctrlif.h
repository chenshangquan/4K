#ifndef _CNCPORTDIAGNOSISIF_H_
#define _CNCPORTDIAGNOSISIF_H_

#include "kdvdispevent.h"

class CCncPortDiagCtrlIF : public CKdvDispEvent
{
public:	
	//获取软件版本信息
	virtual s8* GetSoftVersionInfo() = 0;
	virtual EmCnModel GetEmCnModelInfo() = 0;
	//音频接口信息
	virtual TTpAudioPortInfo* GetAudioPortInfo() = 0;							
	virtual	u16 SetAudioPortInfoCmd( const TTpAudioPortInfo** atAudioPortInfo ) = 0;
	virtual u16 SetMic10InfoCmd( const TTpMic10Info &tTPMic10Info ) = 0;
	virtual u16 SetNoDeskAudioCmd( bool bNoDeskAudio ) = 0;
	virtual	u16 DefaultAudioPortCmd( const TTpAudioPortInfo** atAudioPortInfo ) = 0;
	
	//网络丢包信息
	virtual u16 LostPacketInfoReq() = 0;
	virtual const CString& GetLostPacketInfo()const = 0;			
	
	//上传下行速率
	virtual const TTPUpDownSpeedInfo& GetUpDownstreamRate()const = 0;
	
	//抓包
	virtual u16 SetCaptureStateCmd( const BOOL& bCapture ) const = 0;
	
	//选择音视频矩阵方案的命令
	virtual u16 SelAVMatrixCmd( const TTPVgaMixInfo& tVgaMixInfo ) = 0;
	//获取端口诊断结果
	virtual const TTPVideoDiagInfo& GetVideoDiagInfo()const = 0;
	virtual const TTPAudioDiagInfo& GetAudioDiagInfo()const = 0;

	//获取网络安全FTP和TELNET信息
	virtual const TTPFtpInfo& GetFtpInfo()const = 0;
	virtual const TTPTelnetInfo& GetTelnetInfo()const = 0;
	
	//停止诊断测试请求
	virtual u16 StopAVMatrixReq() = 0;
	
	//Tpad列表
	virtual	const TTPTPadList& GetTpadList()const = 0;								
	virtual	u16 UpdateTpadListReq() = 0;	

	//重启Cns
	virtual u16 RebootCns() = 0;
	
	//升级T300
	virtual u16 UpgradeCns( const TTPFTPFileInfo& tVerFileInfo ) = 0;
	
	//维护工具刷新界面请求
	virtual u16 ReqRefresh() = 0;
	
	//音频混音数配置命令
	virtual u16 AudiotMixerCmd( const u8** aAudioMixerInfo ) = 0;
	virtual u8* GetAudioMixerInfo() = 0;
	virtual u16 DefaultMixerCmd( const u8** aAudioMixerInfo ) = 0;
	
	//音频均衡器配置命令
	virtual u16 AudioEqualizerCmd( const TTPEqualizer** atEqualizer ) = 0;
	virtual TTPEqualizer* GetAudioEqualizer() = 0;
	virtual u16 DefaultEqCmd( const TTPEqualizer** atEqualizer ) = 0;
	
	//呼叫服务器地址
	virtual u16 CallServerCmd( const TTPCallSerInfo& tCallSerInfo ) = 0;
	virtual const TTPCallSerInfo& GetCallServerInfo()const = 0;

	//升级服务器地址
	virtual u16 UpgradeSerCmd( const TTPUpgradeSer& tUpgradeSer ) = 0;

	//设置数据会议服务器地址
	virtual u16 SetDataConfSerCmd( const TTPDataConfInfo& tWBSerIp ) = 0;

	virtual u16 SetMatrixSerCmd( const TTPMatrixServerInfo& tTPMatrixServerInfo) = 0;

	virtual u16 SetNtpSerCmd( const TTPNtpSer& tTpNtpSer) = 0;

	virtual u16 SetQtEncryptSerCmd( const TTpQtEncryptCfg& tTpQtEncryptCfg) = 0;

	virtual const TTPUpgradeSer& GetUpgradeSerInfo()const = 0;

    //白板服务器地址
    virtual const TTPDataConfInfo& GetWBSerIp()const = 0;

	virtual const TTpQtEncryptCfg& GetQtEncryptCfg() const = 0;

	virtual const TTPNtpSer& GetNtpSerIP() const = 0;

	virtual const TTPMatrixServerInfo& GetMatrixSerInfo() const = 0;
	
	//台标文件上传成功通知
	virtual u16 ConfSignCmd( const BOOL& bOk, u8 byIndex ) = 0;
	
	//会议优选格式
	virtual u16 VideoFormatCmd( const TTPVidForamt& tVidForamt ) = 0;
	virtual const TTPVidForamt& GetVideoFormatInfo()const = 0;
	
	//演示优选格式
	virtual u16 DualVideoFormatCmd( const TTPVidForamt& tVidForamt ) = 0;
	virtual const TTPVidForamt& GetDualVideoFormatInfo()const = 0;
	
	//单屏码率
	virtual u16 CallRateCmd( const u16 wCallRate ) = 0;
	virtual const u16 GetCallRate()const = 0;
	
	//演示码率
	virtual u16 DualCallRateCmd( const u16 wDualCallRate ) = 0;
	virtual const u16 GetDualCallRate()const = 0;
	
	//会议轮询
	virtual u16 ConfPollCmd( const TTPPollInfo& tPollInfo ) = 0;
	virtual const TTPPollInfo& GetConfPollInfo()const = 0;
	
	//会议讨论
	virtual u16 ConfDisCmd( const BOOL& bDis ) = 0;
	virtual const BOOL& GetConfDisInfo()const = 0;
	
	//音频格式
	virtual u16 AudioFormatCmd( const EmTpAudioFormat& emAudioFormat ) = 0;
	virtual const EmTpAudioFormat& GetAudioFormatInfo() const = 0;

	//音频配置接口
	virtual const TTPMPAudioInfo& GetAudioInfo() const= 0;

	virtual	u16 DefaultAudioSetCmd( const TTPMPAudioInfo* atAudioPortInfo ) = 0;

	virtual u16 DefaultListenPortSetCmd(const EmAudMixType emAudMixtype, const u8 byAudMixVolume) = 0;

	virtual u16 DefaultAux2OutSetCmd( const EmAudExtend emAudExtend, const u8 byAudExtendVolume) = 0;

	virtual u16 SetAudioInfoCmd( const TTPMPAudioInfo* atAudioPortInfo ) = 0 ;

	virtual u16 SetListenPortCmd( const EmAudMixType emAudMixtype, const u8 byAudMixVolume ) = 0;

	virtual u16 SetAux2OutCmd( const EmAudExtend emAudExtend, const u8 byAudExtendVolume) = 0;

	virtual u16 SetAudioWhiteNoiseCmd(BOOL bIsOpen ,u32 dwWhiteNoisePort) = 0 ;

	virtual BOOL *GetWhiteNoiseInfo() = 0;

	//主视频配置接口
	virtual const TTPVideoInfoTool &GetMainAudioInfo( ) const= 0 ;

	virtual u16 DefaultMainAudioCmd( const TTPVideoInfoTool* ptAudioInfo ) = 0 ;

	virtual u16 SetMainAudioInfoCmd( const TTPVideoInfoTool* ptAudioInfo ) = 0 ;

	virtual	u16 SnapShotCmd( ) =0;

	//演示源配置接口
	virtual	u16 SetDefaultDemonStrationCmd( const TVgaInfo *ptDisplaySource,
		const TTPDualDisplayStrategy *ptDualDisplayStrategy,
		const EmVgaType emDefaultDisplay ) = 0;

	virtual	u16 SetDemonStrationCmd( const TVgaInfo *ptDisplaySource,
		const TTPDualDisplayStrategy *ptDualDisplayStrategy,
		const EmVgaType emDefaultDisplay ) = 0;

	virtual TVgaInfo *GetDisplaySourceInfo( ) = 0 ;
	
	virtual TTPDualDisplayStrategy &GetDisplayStrategyInfo( ) = 0 ;
	
	virtual EmVgaType GetDefaultDisplay( ) = 0 ;

	//图像参数调节
	virtual	u16 SetDefParameterCmd(const TTPImageAdjustParam * pImageAdjustParam ) =0;

	virtual TTPImageAdjustParam *GetImageParam() = 0;

	virtual	u16 SetParameterCmd(const TTPImageAdjustParam * pImageAdjustParam ) =0;

	//路由配置
	virtual void GetRouteInfoData( vector<TRouteCfg> &vecTRouteCfg )const = 0;
	//添加和删除路由
	virtual u16  RouteMngAddCmd( const TRouteCfg& tRouteCfg ) = 0;
	virtual u16  RouteMngDelCmd( const TRouteCfg& tRouteCfg ) = 0;
};

#endif 