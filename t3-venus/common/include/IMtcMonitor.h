#ifndef __IMTCMONITOR_H__
#define __IMTCMONITOR_H__

#include "dispevent.h"

typedef struct tagAudAACParam
{
	u32 dwSamplePerSecond;
	u32 dwChannel;
}TAudAACParam;

typedef struct tagMonitorParam
{
	u8 abyRealType[2];			         //第一路视频和音频的载荷类型
	u8 abyDynamicPayLoad[2];			//第一路视频和音频的动态载荷类型
	TEncryptKey  atEncryptKey[2];		//第一路视频和音频的密钥
	EmSite emSite;
public:
	tagMonitorParam()
	{
		memset(this, 0 ,sizeof(struct tagMonitorParam));
	}
}TMtcMonitorParam;

typedef struct tagMTCPUMemStatus
{
	u8	byCupRate;				//CPU使用的百分比
	u32	dwMTTotalMem;			//MT总的内存数目
	u32 dwUsedMem;				//使用的内存大小
	u32	dwFreeMem;				//可供分配的内存的大小
	public:
		tagMTCPUMemStatus()
		{
			memset(this, 0, sizeof(tagMTCPUMemStatus));
		}
}TMTCPUMemStatus, *PTMTCPUMemStatus;

typedef struct tagResSolution
{
	tagResSolution(){ memset( this, 0 ,sizeof( tagResSolution ) ); }
	u32 dwPriSendVidRes;
	u32 dwSecSendVidRes;
	u32 dwPriRecvVidRes;
	u32 dwSecRecvVidRes;
}TResolution, *PTResolution;

typedef struct tagDIP
{
	tagDIP(){ memset( this, 0 ,sizeof( tagDIP ) ); }
	u32 dwDIPWidth;
	u32 dwDIPHeight;
}TDIP, *PTDIP;

typedef struct tagVideoFrameRate
{
	tagVideoFrameRate(){ memset( this, 0 ,sizeof( tagVideoFrameRate ) ); }
	u32 dwPriSendVidFrmRate;
	u32 dwSecSendVidFrmRate;
	u32 dwPriRecvVidFrmRate;
	u32 dwSecRecvVidFrmRate;
}TVidFrameRate, *PTVidFrameRate;

class IMtcMonitor : public CDispEvent
{
public:
	/*函数名： GetVideoParam
    功    能： 获取监控时候视频参数（包括动态载荷，密钥等）
    参    数： 
    返 回 值： TMtcMonitorParam  MTC的监控参数
    说    明： */
	virtual const TMtcMonitorParam& GetVideoParam() = 0;
    /*函数名： IsInDual
    功    能： 是否在双流中，包括各种双流
    参    数： 
    返 回 值： virtual BOOL32 
    说    明： */
    virtual BOOL32 IsInDual() = 0;

    /*=============================================================================
    函 数 名:IsRcvDual
    功    能:当前终端是否接收双流
    参    数:无
    注    意:无
    返 回 值:接收双流中: TRUE; 没有接收双流: FALSE
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2006/04/26  4.0     王昊    创建
    =============================================================================*/
    virtual BOOL32 IsRcvDual(void) const = 0;

	//是否在发送pc双流
	virtual BOOL32 IsInPCDual() = 0;

	/*函数名： StartDual
    功    能： 开始/停止发送双流
    参    数： EmMtVideoPort emVPort   发起双流的端口（C1 - C6，VGA，S-Video）
			   BOOL32 bStart           True  开始/  False  停止
    返 回 值： virtual BOOL32 
    说    明： */
	virtual u16 StartDual(EmMtVideoPort emVPort, BOOL32 bStart) = 0;

    /*函数名： StartPCDual
    功    能： 开始/停止PC双流	
    参    数： BOOL32 bStart	TRUE开始/False 停止
               TIPTransAddr& tLocalIPAddr  本地RTCP回传地址
    返 回 值： virtual u16 
    说    明： */
	virtual u16 StartPCDual(BOOL32 bStart, TIPTransAddr& tLocalIPAddr) = 0;
    /*函数名： GetPCEncodeParam
    功    能： 
    参    数： 获取PC双流的编码参数
    返 回 值： virtual TVideoEncodeParameter 
    说    明： */
	virtual TVideoEncodeParameter GetPCEncodeParam() = 0;
	
    /*函数名： GetPCEncodeEncrypeKey
    功    能： 
    参    数： 获取PC双流编码的密钥
    返 回 值： virtual TEncryptKey 
    说    明： */
	virtual TEncryptKey GetPCEncodeEncrypeKey() = 0;

    /*函数名： GetPCEncodePayload
    功    能： 获取PC双流编码的动态载荷值
    参    数： 
    返 回 值： virtual u8 动态载荷 
    说    明： */
	virtual u8 GetPCEncodePayload() = 0;

    /*函数名： GetPCSendAddr
    功    能： 获取PC双流的远端地址
    参    数： TIPTransAddr& tRTPAddr	远端RTP地址
               TIPTransAddr& tRTCPAddr	远端RTCP地址
    返 回 值： virtual void 
    说    明： */
	virtual void GetPCSendAddr(TIPTransAddr& tRTPAddr, TIPTransAddr& tRTCPAddr) = 0;

    /*功能	获取当前双视频流的类型
	参数	无
	返回值	u16 u16Type 类型  --0表示无效
	说明	无*/
	virtual EmMtVideoPort GetDualType() = 0;
	/*功能	开始传送本地/远端媒体流
	参数	EmSite emSite	  本地/远端
	        const TIPTransAddr& tIpAddr		视频流发送的IP地址和端口
	返回值	成功返回0;失败返回非0错误码
	说明	无*/
	virtual u16 StartMonitor(EmSite emSite, const TIPTransAddr& tIpAddr) = 0;
	/*功能	请求当前监控源的关键帧
	参数	无
	返回值	EmSite emSite   本地还是远端
	说明	无*/
	virtual u16 ReqMonitorKeyFrame(EmSite emSite) = 0;
	/*功能	停止传送本地/远端媒体流
	参数	EmSite emSite	  本地/远端
	返回值	成功返回0;失败返回非0错误码
	说明	无*/
	virtual u16 StopMonitor(EmSite emSite) = 0;
	/*功能	自环测试
	参数	BOOL32 bStart      开始/停止
	返回值	成功返回0;失败返回非0错误码
	说明	稍后会收到通知消息MTC_UI_CIRCLETEST*/
	virtual u16 SelfTest(BOOL32 bStart) = 0;
	/*功能	解码器丢包上报通知
	参数	byCodecId	解码器标识
	返回值	成功返回0;失败返回非0错误码
	说明	无*/
//	virtual u16 CodecPackedLost(u8 byCodecId) = 0;
    /*功能	图像测试
	参数	EmSite emSite			本地/远端
	        BOOL32 bStart			开始/停止
	返回值	成功返回0;失败返回非0错误码
	说明    无*/
	virtual u16 ImageTest(EmSite emSite, BOOL32 bStart) = 0;
	/*功能	请求/停止解码器信息
	参数	u8 byEnable 开始/停止 MT_ENABLE/MT_DISABLE
	返回值	成功返回0;失败返回非0错误码
	说明	请求成功后,会收到MTC_UI_CODECSTATUS_UPDATED通知*/
	virtual u16 ReqCodecStatus() = 0;
    /*功能	获取解码器信息
	参数	无
	返回值	快照信息
	说明	收到MTC_UI_CODECSTATUS_UPDATED消息后用此方法更新信息*/
	virtual const TCallInfoStatistics& GetCodecStatus()const = 0;
	/*功能	开始/停止音量测试
	参数	
	返回值	成功返回0;失败返回非0错误码
	说明	请求成功后,会收到MTC_UI_AUDIOPOWER_UPDATED通知*/
	virtual u16 ReqAudioPower() = 0;
    /*功能	是否在自环,本地、远端图像测试,声音测试
	参数	无
	返回值	自环中TURE 
	说明	*/
	virtual BOOL32 IsInnerLoop() = 0;
    virtual BOOL32 IsLocalImageTest() = 0;
    virtual BOOL32 IsRemoteImageTest() = 0;
    virtual BOOL32 IsVolumeImageTest() = 0;
    /*功能	画中画切换命令
	参数	无
	返回值	成功返回0;失败返回非0错误码 
	说明	*/
	virtual u16 SwitchPIP() = 0;
    /*功能	画中画位置调整命令
	参数	无
	返回值	成功返回0;失败返回非0错误码 
	说明	*/
    virtual u16 MovePIP() = 0;
    /*功能	码率上报
    参数	无
    返回值	成功返回0;失败返回非0错误码
    说明	桌面终端向业务库上报编码码率*/
//    virtual u16 ReportBitRate(_TBITRATE &tBitRate) = 0;

    /*函数名： ReqCpuMemStatus
    功    能： 请求cpu 和 mem的状态
    参    数： 
    返 回 值： 
    说    明： */
	virtual u16	ReqCpuMemStatus() = 0;
    /*函数名： TMTCPUMemStatus& GetCPUMemStatus
    功    能： 获取cpu 和 mem 的状态
    参    数： 
    返 回 值： virtual const 
    说    明： */
	virtual const TMTCPUMemStatus& GetCPUMemStatus() = 0;

	/*函数名： ReqMonitorIKey
    功    能： 请求监控关键帧
    参    数： EmSite emSite   本地/远端
    返 回 值： virtual void 
    说    明： */
	virtual void ReqMonIKey(u8 byLocal) = 0;
    /*函数名： GetDualVidCap
    功    能： 
    参    数： EmVideoType emType
    返 回 值： virtual EmMtVideoPort* 
    说    明： */
	virtual EmMtVideoPort* GetDualVidCap( EmVideoType emType ) = 0;
    
    /*函数名： MTCEncStatisAck
    功    能： mtc编码统计信息回馈
    参    数： const TCodecPackStat& tCodecPackStat
    返 回 值： virtual u16 
    说    明： */
	virtual u16 MTCEncStatisAck( const TCodecPackStat& tCodecPackStat ) = 0;

    /*函数名： IsRemoteLoopBackTest
    功    能： 是否正在进行远端环回测试
    参    数： 
    返 回 值： BOOL32 
    说    明： */
    virtual BOOL32 IsRemoteLoopBackTest() = 0;

    /*函数名： RemoteLoopBackTest
    功    能： 远端环回测试
    参    数： EmVideoType emVideoType, BOOL32 bStart
    返 回 值： u16 
    说    明： */
    virtual u16 RemoteLoopBackTest(EmVideoType emVideoType, BOOL32 bStart) = 0;
	/*函数名： RemoteLoopBackTest
    功    能： 远端环回测试
    参    数： EmVideoType emVideoType, BOOL32 bStart
    返 回 值： u16 
    说    明： */
    virtual u16 SpeakerTest() = 0;
	/*函数名： SendMtcResToMt
    功    能： 双流前发送给终端当前分辨率
    参    数： u32 byflag
    返 回 值： u16 
    说    明： */
	virtual u16 SendMtcResToMt(u32 byflag) = 0;

	//获取本地AAC配置
	virtual const TAudAACParam& GetLocalAACParam() = 0;
	//获取远端AAC配置
	virtual const TAudAACParam& GetRemoteAACParam() = 0;
	//获得真正分辨率
	virtual TDIP* GetRealRes() = 0;
	//获得视频码率
	virtual TVidFrameRate* GetVideoFrameRate() = 0;
}; // IMtcMonitor


#endif