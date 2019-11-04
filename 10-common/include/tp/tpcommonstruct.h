#ifndef _h_tpcommonstruct_h__
#define _h_tpcommonstruct_h__
#include "tpsys.h"
#include <time.h>
#include "mtmacro.h"
#include "tphdu2.h"

//MTStruct begin.
#include "kdvtype.h"
#include "mtmacro.h"
#include "tpcommontype.h"
#include "osp.h"
#include "cnconst.h"
#include "cnstype.h"

/////////////用于升级服务器///////////////////////
//FTP文件信息
typedef struct tagTTPFTPFileInfo
{
	u32_ip	dwSerIP;
	u16		wSerPort;
	u8		byUserNameLen;
	s8		achUserName[MAX_FTP_NAME_LEN];
	u8		byPasswordLen;
	s8		achPassword[MAX_FTP_NAME_LEN];
	u8		byFilePathLen;
	s8		achFilePath[TP_MAX_FILESRV_FILENAME_LEN];
	public:
		tagTTPFTPFileInfo(){ memset( this, 0, sizeof( struct tagTTPFTPFileInfo ) ); };
}TTPFTPFileInfo;

typedef struct tagTTPDev
{
	EmTPDevRegUpdateSer    m_emDevRegUpdateSer; //具体设备的设备类型
	s8                     m_achDevVersion[MAX_DEVICEVER_LEN];
	TTPFTPFileInfo         m_tDevVerFileInfo;
	EmTPUpdateType         m_emTPUpdateType;
public:
	tagTTPDev()
	{ 
		memset( this, 0, sizeof(struct tagTTPDev) ); 
		m_emDevRegUpdateSer = emDevInvalid; 
	}
}TTPDev;

//设备信息
typedef struct tagTTPDevVerInfo
{
	TTPDev	m_atDev[MAX_REG_DEVICE_NUM]; //cns升级文件为第一个元素，TPad升级文件为第二个元素
	public:
		tagTTPDevVerInfo(){ memset( this, 0, sizeof(struct tagTTPDevVerInfo) ); }
}TTPDevVerInfo;

typedef struct tagTTPLocalVerInfo
{
	EmTPDevRegUpdateSer    m_emDevRegUpdateSer; //具体设备的设备类型
	s8                     m_achDevVersion[MAX_DEVICEVER_LEN];
public:
	tagTTPLocalVerInfo()
	{
		memset( this, 0, sizeof(tagTTPLocalVerInfo) );
		m_emDevRegUpdateSer = emDevInvalid;
	}
}TTPLocalVerInfo;

//设备的本地信息
typedef struct tagTTPLocalDevVerInfo
{
	EmTPDevRegUpdateSer    m_emDevRegUpdateSer; //请求端的设备类型
	TTPLocalVerInfo        m_atLocalVerInfo[MAX_DEVICE_NUM]; 
public:
	tagTTPLocalDevVerInfo()
	{
		m_emDevRegUpdateSer = emDevInvalid;
	}
}TTPLocalDevVerInfo;

//TPad升级文件信息
typedef struct tagTTPTPadVerInfo
{
	EmTPUpdateType         m_emTPUpdateType;
	TTPFTPFileInfo         m_tPadVerFileInfo;
	s8                     m_achTPadVersion[MAX_DEVICEVER_LEN];
	public:
		tagTTPTPadVerInfo(){ memset( this, 0, sizeof( struct tagTTPTPadVerInfo ) ); }
}TTPTPadVerInfo;




/*************************add struct begin********************************/



/************************************************************************/
/* 配置相关信息数据结构定义开始                                         */
/************************************************************************/
/************************************************************************/
/* H323信息数据结构定义                                                 */
/************************************************************************/
typedef struct tagTH323Cfg
{
    s8   achMtAlias[MT_MAX_H323ALIAS_LEN+1]; //别名
    s8   achE164[MT_MAX_E164NUM_LEN+1];      //E164号码
    BOOL bIsUseGk;                  // 是否使用GK
	s8   achGKPwd[MT_MAX_PASSWORD_LEN+1];//GK密码
    u32_ip  dwGkIp;                     // GK 地址
    s8   achGkIpName[MT_MAX_H323GKSERVER_NAME_LEN]; //Gk域名地址
    BOOL bIsH239Enable;                  // H239方式
    BOOL bIsEnctyptEnable;          // 是否使用加密
    EmEncryptArithmetic emEncrptMode;      //加密方式
    u16  wRoundTrip;                //链路检测时间
public:
	tagTH323Cfg(){memset(this , 0 ,sizeof( struct tagTH323Cfg) );	}
}TH323Cfg,*PTH323Cfg;

/************************************************************************/
/* 引导信息数据结构定义                                               */
/************************************************************************/
typedef struct tagTGuideCfg
{
    EmLanguage  emLanguage;         //语言选择
    BOOL  bIsDHCPEnable;            //是否使用DHCP
    u32_ip  dwIp;                      //终端IP地址    
    u32_ip  dwMask;                     //子网掩码
	u32_ip  dwGateWay;                  //网关地址
    BOOL bH323Enable;              //是否使用H323
	BOOL bH320Enable;              //是否使用H320
	BOOL bSIPEnable;                //是否使用SIP
	BOOL bSATEnable;                //是否使用卫星
    TH323Cfg tH323Info;             //H323设置
    BOOL bUserCfgPwdEnable;         //是否设置配置密码
    s8  achUserCfgPwd[MT_MAX_PASSWORD_LEN+1]; //是否设置配置密码
    BOOL bNetCfgPwdEnable;         //是否设置网络配置密码
    s8  achNetCfgPwd[MT_MAX_PASSWORD_LEN+1]; //网络设置密码
public:
	tagTGuideCfg(){ memset ( this ,0 ,sizeof( struct tagTGuideCfg) );}
}TGuideCfg, *PTGuideCfg;
// TsymboPoint台标位置结构
typedef struct tagTSymboPoint
{
	u16 X;
	u16 Y;
public:
	tagTSymboPoint(){ memset( this ,0 ,sizeof( struct  tagTSymboPoint ) );}
}TSymboPoint;
/************************************************************************/
/* 显示设置信息数据结构定义                                               */
/************************************************************************/
typedef struct tagTOsdCfg
{
    BOOL  bIsAutoPip;            //是否启用自动画中画
    BOOL  bIsShowConfLapse;      //是否显示会议时间
    BOOL  bIsShowSysTime;        //是否显示系统时间
    BOOL  bIsShowState;          //是否显示状态标志
    EmLabelType  emLabelType;    //台标类型
	TSymboPoint  tLableCoordinate; // 自定义台标位置
	EmLabelPosType emLabelPosType; //终端别名台标位置
    EmDualVideoShowMode emDualMode;//双流显示方式
	EmDisplayRatio  emPrimaryDisplayRatio;//第一路显示比例模式
	EmDisplayRatio  emSecondDisplayRatio;//第二路显示比例模式
public:
	tagTOsdCfg(){ memset( this ,0 ,sizeof( struct  tagTOsdCfg ) );}
}TOsdCfg, *PTOsdCfg;

//时间结构重新定义
typedef struct tagTMtKdvTime
{
    u16 		m_wYear;//年
    u8  		m_byMonth;//月
    u8  		m_byMDay;//日
    u8  		m_byHour;//时
	u8  		m_byMinute;//分
	u8  		m_bySecond;//秒
public:
    tagTMtKdvTime(){ memset ( this ,0 ,sizeof( struct tagTMtKdvTime) );}
}TMtKdvTime, *PTMtKdvTime;

/************************************************************************/
/* 用户设置信息数据结构定义                                               */
/************************************************************************/
typedef struct tagTUserCfg
{
    EmTripMode emAnswerMode;   //应答方式
    BOOL  bIsAutoCallEnable;    //是否启用自动呼叫
    s8  achTerminal[MT_MAX_H323ALIAS_LEN+1]; //自动呼叫的终端名
    u16  wCallRate;               //自动呼叫码率
    BOOL  bIsRmtCtrlEnbale;      //是否允许远端控制
    BOOL  bIsSleepEnable;        //是否开启待机功能
    u16  wSleepTime;            //待机时间
	BOOL  bDisableTelephone;       // 是否禁用电话功能
public:
    tagTUserCfg(){ memset ( this ,0 ,sizeof( struct tagTUserCfg) );}
}TUserCfg, *PTUserCfg;

/************************************************************************/
/*8010c配置vga输出参数                                               */
/************************************************************************/
typedef struct tagTVgaOutCfg
{
	BOOL bVgaOut; //8010c是否在vga上输出
	u16  wRefreshRate; //vga的刷新率
 public:
 	tagTVgaOutCfg(){memset(this , 0 ,sizeof( struct tagTVgaOutCfg) );	}
	tagTVgaOutCfg( BOOL bOut, u16 wRate ){ bVgaOut = bOut; wRefreshRate = wRate; }
}TVgaOutCfg, *PTVgaOutCfg;

typedef struct tagTMtEquipmentCapset
{
    BOOL bMicAdjustSupport;
	BOOL bMcSupport;
public:
	tagTMtEquipmentCapset(){memset(this , 0 ,sizeof( struct tagTMtEquipmentCapset) );	}
}TMtEquipmentCapset, *PTMtEquipmentCapset;


/************************************************************************/
/*内嵌mc配置                                                            */
/************************************************************************/
//[xujinxing-2006-10-17]
typedef struct tagTInnerMcCfg
{
	BOOL bUseMc;
	EmMCMode emMode;
	BOOL bAutoVMP;
	tagTInnerMcCfg()
	{
		bUseMc = FALSE;
		emMode = emMcModeEnd;
		bAutoVMP = FALSE;
	}
}TInnerMcCfg,*PTInnerMcCfg;



/************************************************************************/
/* 以太网信息数据结构定义                                               */
/************************************************************************/
typedef struct tagTEthnetInfo
{
    BOOL bEnable;
    u32_ip  dwIP;
    u32_ip  dwMask;
    BOOL bIsUserAssignBandWidth;
    u32  dwUpBandWidth;
    u32  dwDownBandWidth;
public:
	tagTEthnetInfo(){ memset( this ,0 ,sizeof( struct  tagTEthnetInfo ) );}
}TEthnetInfo, *PTEthnetInfo;



typedef struct tagTE1Unit                                                                                     
{                                                                                                              
    BOOL bUsed;        //使用标志,置1使用，0不使用  
    u32   dwE1TSMask;        // E1时隙分配说明 
    EmDLProtocol emProtocol; //接口协议封装类型,如果是单E1连接可以指定PPP/HDLC，
    //如果是多E1捆绑连接必须是PPP协议
    u32 dwEchoInterval; // 对应serial同步接口的echo请求时间间隔，秒为单位，有效范围0-256，默认填2
    u32 dwEchoMaxRetry;// 对应serial同步接口的echo最大重发次数，有效范围0-256，默认填2 
public:
	tagTE1Unit(){ memset( this ,0 ,sizeof( struct  tagTE1Unit ) );}
}TE1Unit,*PTE1Unit;

/************************************************************************/
/* E1信息数据结构定义                                               */
/************************************************************************/
typedef struct tagTE1Config
{                                                                                                            
// Single & Multi Chan param.                                                                                  

	u8  byUnitNum;                 //使用E1单元个数
    BOOL  bIsBind;                  //  是否绑定                                                                    
    u32_ip  dwIP;                      //  ip地址                                                                          
    u32_ip  dwIPMask;                  //  掩码，                                                                          
	// 多通道参数
    EmAuthenticationType emAuthenticationType;//PPP链接的验证方法PAP/CHAP,默认填emPAP 
    u32  dwFragMinPackageLen;       //  最小分片包长，字节为单位，范围20~1500，默认填20                                 
    s8   achSvrUsrName[MT_MAX_E1_NAME_LEN+1]; 	/* 服务端用户名称，用来验证对端的数据 */                                       
    s8   achSvrUsrPwd[MT_MAX_E1_NAME_LEN+1];   	/* 服务端用户密码，用来验证对端的数据 */                               
    s8   achSentUsrName[MT_MAX_E1_NAME_LEN+1];	/* 客户端用户名称，用来被对端验证 */                                           
    s8   achSentUsrPwd[MT_MAX_E1_NAME_LEN+1]; 	/* 客户端用户密码，用来被对端验证 */                                           
	// E1 Module Param.                                                                                            
    TE1Unit atE1Unit[ MT_MAX_E1UNIT_NUM ];//E1_SINGLE_LINK_CHAN_MT_MAX_NUM];/* 每个被捆绑的serial同步接口参数 */
public:
	tagTE1Config(){ memset( this ,0 ,sizeof( struct  tagTE1Config ) );}	
}TE1Config, *PTE1Config;



/************************************************************************/
/* 串口信息数据结构定义                                               */
/************************************************************************/
typedef struct tagTSerialCfg
{
    u32  dwBaudRate; //波特率单位kbps
    u8   byByteSize;   //数据位长度 5,6,7,8
    EmParityCheck emCheck; //校验算法
    EmStopBits emStopBits; //停止位
public:
 	tagTSerialCfg(){memset(this , 0 ,sizeof( struct tagTSerialCfg) );	}
}TSerialCfg, *PTSerialCfg;


/************************************************************************/
/* 路由信息数据结构定义                                               */
/************************************************************************/
typedef struct tagTRouteCfg
{
    BOOL bUsed;
    u32_ip dwDstNet; //目的子网
    u32_ip dwDstNetMask; //目的子网掩码
    u32_ip dwNextIP; //下一跳IP地址  
    u32 dwPri;  //路由优先级
public:
  	tagTRouteCfg(){memset(this , 0 ,sizeof( struct tagTRouteCfg) );	}
}TRouteCfg, *PTRouteCfg;

/************************************************************************/
/* PPPOE信息数据结构定义                                               */
/************************************************************************/

/*初始化PPPOE模块时使用的结构体*/
typedef struct  tagTPPPOECfg
{
	BOOL    bUsed;   //是否使用PPPoE
    s8      abyUserName [MT_PPPoE_MAX_USENAME_LEN];/*拨号时使用的用户名,必填项*/
    s8      abyPassword [MT_PPPoE_MAX_PASSWORD_LEN]; /*拨号时使用的密码,必填项*/
    s8      abyServerName[MT_PPPoE_MAX_SERVERNAME_LEN];/*指定拨号服务商的名字*/
    BOOL  bAutoDialEnable;/*是否允许断链后自动拨号,默认不自动拨号*/
    BOOL  bDefaultRouteEnable;/*是否允许将对端的地址设为默认网关，默认不设为网关*/
    BOOL  bDebug;/*是否以debug模式运行pppoe，默认不运行在debug模式*/
    u32     dwAutoDialInterval;/*断链后再次自动拨号需要等带的时间（允许设置成0s）*/
    u16     wDialRetryTimes;/*拨号尝试的次数，如果达到该次数还没有响应则拨号失败*/
    u16     wLcpEchoSendInterval;/*链接建立后，发送LCP-ECHO包的时间间隔*/
    u16     wLcpEchoRetryTimes;/* 发送几次LCP-ECHO包没有得到相应则认为链接断开*/
    u8      byEthID;/*PPPOE服务需要绑定的以太网的ID号（从0开始）*/
public:
 	tagTPPPOECfg(){ memset( this ,0 ,sizeof( struct  tagTPPPOECfg ) );}
}TPPPOECfg, *PTPPPOECfg;


/*有关PPPOE模块各种统计信息的结构体*/
typedef struct tagTPPPoEStates
{
    BOOL    bPppoeRunning;/*PPPOE是否运行，TRUR—运行；FALSE—没有运行*/
    u32     dwLocalIpAddr;/*本机IP地址,网络序*/
    u32     dwPeerIpAddr;/*对端IP地址,网络序*/
    s8      abyServerName[MT_PPPoE_MAX_SERVERNAME_LEN];/*ISP Server的名字*/
    u32     dwLinkKeepTimes;/*链路建立的时间*/
    u32     dwLinkDownTimes;/*链路断链的次数统计*/
    u32     dwPktsSend;/*总共发送的数据包数--包括各类协议包以及上层业务程序的数据包*/
    u32     dwPktsRecv;/*总共接收的数据包数*/
    u32     dwBytesSend;/*总共发送的字节数*/
    u32     dwBytesRecv;/*总共接收的字节数*/
public:
	tagTPPPoEStates(){ memset( this ,0 ,sizeof( struct  tagTPPPoEStates ) );}
}TPPPoEStates,*PTPPPoEStates;

/*调用上层业务程序注册的回调函数发送认证失败时消息的内容结构体*/
typedef struct tagTPPPoEAuthFailed
{
    s8      abyUserName [MT_PPPoE_MAX_USENAME_LEN];/*业务程序给的拨号时使用的用户名*/
    s8      abyPassword [MT_PPPoE_MAX_PASSWORD_LEN]; /*业务程序给的拨号时使用的密码 */
public:
 	tagTPPPoEAuthFailed(){ memset( this ,0 ,sizeof( struct  tagTPPPoEAuthFailed ) );}
}TPPPoEAuthFailed,*PTPPPoEAuthFailed;

/*调用上层业务程序注册的回调函数发送建链通知消息的结构体*/
typedef struct tagTPPPoEConnNotify
{
    u32     dwOurIpAddr;/*本断获得的IP地址,网络序*/
    u32     dwPeerIpAddr;/*对端的IP地址*/
    u32     dwDnsServer1;/*DNS Server1,网络序*/
    u32     dwDnsServer2;/*DNS Server1,网络序*/ 
public:
 	tagTPPPoEConnNotify(){ memset( this ,0 ,sizeof( struct  tagTPPPoEConnNotify ) );}
}TPPPoEConnNotify,*PTPPPoEConnNotify;

/*通知业务程序找不到指定的ISP Server的消息结构体*/
typedef struct tagTPPPoENoServer
{
    s8      abyServerName[MT_PPPoE_MAX_SERVERNAME_LEN];/*ISP Server的名字*/
public:
  tagTPPPoENoServer(){ memset( this ,0 ,sizeof( struct  tagTPPPoENoServer ) );}
}TPPPoENoServer,*PTPPPoENoServer;

/************************************************************************/
/* SNMP信息数据结构定义                                               */
/************************************************************************/
typedef struct tagTSNMPCfg
{
    s8    achUserName[MT_MAX_COMM_LEN+1];//共同体名
    u32_ip   dwTrapServerIp;//告警主机地址
public:
	tagTSNMPCfg(){ memset( this ,0 ,sizeof( struct  tagTSNMPCfg ) );}
}TSNMPCfg, *PTSNMPCfg;


/************************************************************************/
/* QOS信息数据结构定义                                               */
/************************************************************************/
typedef struct tagTIPQoS
{
	//QoS服务类型
    EmQoS    emType;
	//信令QOS值 范围
    u8       abySignalling[2];
	//数据信道（用于摄像头远摇）QOS值 范围
    u8       abyData[2];
	//语音QOS值 范围
    u8       abyAudio[2];
	//视频QOS值 范围
    u8       abyVideo[2];
	//质量保证类型
    EmTOS    emTOS;
public:
	tagTIPQoS(){ memset( this ,0 ,sizeof( struct  tagTIPQoS ) );}
}TIPQoS, *PTIPQoS;




/************************************************************************/
/* 流媒体信息数据结构定义                                               */
/************************************************************************/
typedef struct tagTStreamMedia
{
    BOOL bUse;
    BOOL bForwardLocalVideo; //是否转发本地视频
    u32_ip  dwMCIP;    //组播IP地址
    u16  wPort;     //端口号
	u8   byTTL;     //TTL值
    s8   achChannelName[MT_MAX_CHANNEL_NAME_LEN+1];//频道名称
    s8   achPassword[MT_MAX_PASSWORD_LEN+1];//密码
public:
	tagTStreamMedia(){ memset( this ,0 ,sizeof( struct  tagTStreamMedia ) );}
}TStreamMedia, *PTStreamMedia;


/************************************************************************/
/*视频参数体信息数据结构定义                                               */
/************************************************************************/
typedef struct tagTVideoParam 
{
    BOOL  bUseFixedFrame;    //使用固定帧 
    u8 byFrameRate;	///帧率
    EmFrameUnitType  emFrameUnit;	//帧率单位
    u8 byQualMaxValue;	//最小量化参数
    u8 byQualMinValue;	//最大量化参数
    u16 wIKeyRate;	//关键帧间隔
    EmEncodeMode emEncodeMode;     //编码方式
    EmLostPackageRestore emRestoreType; //丢包恢复方式
    u16 wH264IKeyRate;		//H264关键帧间隔
    u8  byH264QualMaxValue;	//H264最大量化参数
    u8  byH264QualMinValue;	//H264最小量化参数
//以下参数只有在windows下才有用
//添加采集图像宽高
	u16	wWidth; //视频捕获图像宽度 仅Windows有效(default:640)
	u16	wHeight;//视频捕获图像高度 仅Windows有效(default:480)
	EmMediaType   emCapType;    //采集类型   (default:emMediaAV)
	EmPCCapFormat emPCCapFormat;//视频捕获帧格式 仅Windows有效(default:emCapPCFrameBMP)
//以下参数，针对高清终端, 
	u8 by720pFrameRate; //720p分辨率下帧率
	u8 byVgaFrameRate;  //双流vga下帧率
	//xjx_080612
	u8 byD1FrameRate; //D1分辨率下帧率
public:
	tagTVideoParam(){ memset( this ,0 ,sizeof( struct  tagTVideoParam ) );}	
}TVideoParam, *PTVideoParam;


/************************************************************************/
/*优选协议信息数据结构定义                                               */
/************************************************************************/
typedef struct tagTAVPriorStrategy 
{
    EmVideoFormat  emVideoFormat;  //视频优选协议
    EmAudioFormat  emAudioFormat;    //音频优选协议
    EmVideoResolution emVideoResolution; //分辨率优选协议
public:
	tagTAVPriorStrategy(){ memset( this ,0 ,sizeof( struct  tagTAVPriorStrategy ) );}	
}TAVPriorStrategy, *PTAVPriorStrategy;
/************************************************************************/
/* 码流重传信息数据结构定义                                               */
/************************************************************************/
typedef struct tagTLostPackResend
{
	BOOL bUse;             //是否启用
	EmNetType emNetType;   //网络类型
	u8   byResendLevel;    //重传等级 0<低,重传一次> 1<中,重传两次> 2<高,重传三次>
	u16  wFirstTimeSpan;   //第一个重传检测点   default 40
	u16  wSecondTimeSpan;  //第二个重传检测点   default 80
	u16  wThirdTimeSpan;   //第三个重传检测点   default 160
	u16  wRejectTimeSpan;  //过期丢弃的时间跨度 default 200
	u16  wSendBufTimeSpan; //发送缓存           default 1000
	BOOL bUseSmoothSend;   //启用平滑发送
	BOOL bUseAdaptSend;  //双流视频适配启用重传
public:
	tagTLostPackResend(){ memset( this ,0 ,sizeof( struct  tagTLostPackResend ) );}
}TLostPackResend,*PTLostPackResend;


/************************************************************************/
/*摄像机信息数据结构定义                                               */
/************************************************************************/


//摄像头能力类型
typedef struct tagTCameraTypeInfo
{
	s8 achName[MT_MAXLEN_CAMERA_TYPE_NAME];
	u8 byMaxAddr; //摄像头最大地址值
	u8 byMaxSpeedLevel;//摄像头最大速度级别 
public:
	tagTCameraTypeInfo(){ memset( this ,0 ,sizeof( struct  tagTCameraTypeInfo ) );}
}TCameraTypeInfo ,*PTCameraTypeInfo;


//摄像头配置
typedef struct tagTCameraCfg
{
    BOOL  bUse;
    s8  achCamera[MT_MAX_CAMERA_NAME_LEN+1];//摄像头名
    u8  byAddr;  //摄像头地址
    u8  bySpeedLevel; //摄像头控制速度
    EmSerialType emSerialType;
    u32_ip dwSerialServerIP; //串口服务器IP ,当该值为0时表示使用本地串口
    u16 wSerialServerPort; //串口服务器端口号    
public:
	tagTCameraCfg(){ memset( this ,0 ,sizeof( struct  tagTCameraCfg ) );}	
}TCameraCfg, *PTCameraCfg;

typedef struct tagTVideoStandard
{
	EmVideoType     emVideoType;
	BOOL            bIsInPort;    //是否为输入端口
	EmVideoStandard emStandard;
public:
	tagTVideoStandard(){ memset( this ,0 ,sizeof( struct  tagTVideoStandard ) );}	
}TVideoStandard ,*PTVideoStandard;

/************************************************************************/
/*视频源信息数据结构定义                                               */
/************************************************************************/
typedef struct tagTVideoSource
{
    EmVideoInterface emMainCam;
    u8 byCPortIndex ;//C端子输入时表明输入端口号，0基址
    EmVideoInterface emVideoOut;
    u8  byFrequency; //VGA时为刷新率
public:
	tagTVideoSource(){ memset( this ,0 ,sizeof( struct  tagTVideoSource ) );}
}TVideoSource, *PTVideoSource;


//快照信息
typedef struct tagTSnapInfo
{
	BOOL bResult;		// 获取结果(成功TRUE /失败FALSE)
	u32  dwMaxSize;		// 最大空间大小(字节)
	u32  dwUsedSize;		// 已用空间大小(字节)
	u32	 dwPicNum;	// 快照图片个数(个)
public:
	tagTSnapInfo(){ memset( this ,0 ,sizeof( struct  tagTSnapInfo ) );}
} TSnapInfo,*PTSnapInfo;

typedef struct tagTBannerInfo
{
	BOOL        bEnable;			// 使能(MT_ENABLE/MT_DISABLE)
	u32		    dwTextClr;			// 文字颜色
	u32		    dwBkgClr;			// 背景色
	EmTextAlign	emTextAlign;	// 文字对齐模式(TEXT_ALIGN_LEFT/TEXT_ALIGN_CENTER/TEXT_ALIGN_RIGHT)
	EmRollMode	emRollMode;		// 滚动模式(ROLL_NOT_ROLL/ROLL_RIGHT_LEFT/ROLL_DOWN_UP)
	u8 	        byTransParent;		// 透明度
	EmRollSpeed	emRollSpeed;		// 滚动速度(ROLL_SPEED_SLOW/ROLL_SPEED_NORMAL/ROLL_SPEED_FAST/ROLL_SPEED_FASTER)
	u8		    byRollNum;			// 滚动次数(0:表示无限制滚动,1~255:表示用户指定的滚动次数)
	u8		    byStayTime;			// 停留时间(0:表示不停留,1~255:表示用户指定的时间,单位秒)
	u32		    dwStartXPos;		// 字幕显示的起始X坐标
	u32		    dwStartYPos;		// 字幕显示的起始Y坐标
	u32		    dwDisplayWidth;		// 字幕显示区域的宽(以象素为单位)
	u32		    dwDisplayHeight;	// 字幕显示区域的高(指行高,以象素为单位)
	u8	        achWinInfo[ 256 ];	// 用于存放Windows的相关信息(以\0结束)
	s8          achBannerText[1024];//存放横幅内容
public:
	tagTBannerInfo(){ memset( this ,0 ,sizeof( struct tagTBannerInfo ) );	}
} TBannerInfo, *PTBannerInfo;


/************************************************************************/
/*     矩阵配置                                                         */
/************************************************************************/

/************************************************************************/
/* 配置相关信息数据结构定义结束                                         */
/************************************************************************/



/************************************************************************/
/* 会议相关信息数据结构定义开始                                         */
/************************************************************************/

//终端编号
typedef struct tagTMtId
{
	u8 byMcuNo;
	u8 byTerNo;
	
public:
	tagTMtId(){ memset( this ,0 ,sizeof( struct tagTMtId ) );	}
	
}TMtId ,*PTMtId;

//基本会议信息
typedef struct tagTConfBaseInfo
{
	s8	 achConfId[MT_MAX_CONF_ID_LEN + 1 ];			// 会议ID
	s8	 achConfName[MT_MAX_CONF_NAME_LEN + 1 ];		// 会议名
	s8	 achConfNumber[ MT_MAX_CONF_E164_LEN + 1 ];	    // 会议号码
	s8	 achConfPwd[ MT_MAXLEN_PASSWORD + 1 ];			// 会议密码
	BOOL bNeedPassword;                         //是否需要密码
	u16  wConfDuration;							// 会议持续时间		
	EmVideoFormat   emVideoFormat;							// 会议视频格式(VIDEO_H261等)
	EmAudioFormat   emAudioFormat;							// 会议音频格式(AUDIO_MP3等)
	EmVideoResolution  emResolution;							// 会议视频分辨率(VIDEO_CIF等)
	BOOL  bIsAutoVMP;								// 是否自动画面合成
	BOOL  bIsMix;	    							// 是否混音
	u8				  bySecVideoFormat;				// 双流格式
	EmVideoResolution emSecVidRes;					// 双流分辨率
	u8				  bySecVidFps;					// 双流帧率

public:
	tagTConfBaseInfo(){ memset( this ,0 ,sizeof( struct tagTConfBaseInfo ) );	}
}TConfBaseInfo ,*PTConfBaseInfo;

//会议列表信息
typedef struct tagTConfListInfo
{
	u8			  byConfNum;
	TConfBaseInfo atConfInfo[MT_MAX_CONF_NUM];
public:
	tagTConfListInfo(){ memset( this ,0 ,sizeof( struct tagTConfListInfo ) );	}
}TConfListInfo ,*PTConfListInfo;

//终端信息
typedef struct tagTMtInfo
{
	TMtId tLabel;
	s8     achAlias[MT_MAX_NAME_LEN+1];

public:
	tagTMtInfo(){memset( this ,0 ,sizeof( struct tagTMtInfo) );}
}TMtInfo ,*PTMtInfo;

//视频编解码状态
typedef struct tagTMtVideoCodecStatus
{
	BOOL                bRuning;           //是否在工作
	EmVideoFormat       emFormat;          //视频编码格式
	EmVideoResolution   emRes;             //视频编码格式
	u16                 wBitrate;          //视频编码码率(单位:kbps)
	u16                 wAverageBitrate;   //主视频编平均码码率(单位:kbps)
	BOOL                IsEncrypt;         //主视频编码是否加密
	EmEncryptArithmetic emArithmetic;	   //主视编码使用的加密算法	

public:
	tagTMtVideoCodecStatus()
	{ 
		memset ( this ,0 ,sizeof( struct tagTMtVideoCodecStatus) );
	}
}TMtVideoCodecStatus ,*PTMtVideoCodecStatus;

//终端状态
typedef struct tagTTerStatus
{
	EmMtModel  emMtModel;				    //终端型号
	EmFileSys  emFileSys;                   //文件系统类型

	u8		byEncVol;					//当前编码音量(单位:等级)
	u8		byDecVol;					//当前解码音量(单位:等级)
	BOOL	bIsMute;					//是否哑音	
	BOOL	bIsQuiet;					//是否静音			
	BOOL	bIsLoopBack;				//是否自环
	BOOL    bIsInMixing;                //是否参加混音
	BOOL    bRegGkStat;			    	//GK注册结果	1 成功 0 失败
	EmAction   emPollStat;				//轮询状态		emStart ,emPause ,emStop /开始/暂停/停止
	EmSite	emCamCtrlSrc;				    //当前控制摄像头源类型 emLocal, emRemote
	u8		byLocalCamCtrlNo;			    //当前控制的本地摄像头号(1-6号摄像头)
	u8		byRemoteCamCtrlNo;			    //当前控制的远端摄像头号(1-6号摄像头)
	u8      byE1UnitNum ;                   //终端E1模块的的E1个数
	BOOL	bFECCEnalbe;				//是否允许远遥
	BOOL    bLocalIsVAG;                //本地第二路码流输出到是否VGA
	BOOL    bPVHasVideo;                //第一路是否有视频源
	BOOL    bSVHasVideo;                //第二路是否有视频源
//一下部分不建议使用
	BOOL	bIsAudioPowerTest;			//是否在测试音频	
	BOOL	bIsLocalImageTest;			//是否本地图像测试
	BOOL	bIsRemoteImageTest;			//是否远端图像测试 
//	///////会议状态///////
	BOOL       bIsInConf;				//是否在会议中	
	EmConfMode emConfMode;				//会议模式		1 两点 2 多点		
    BOOL       bCallByGK;				//是否通过GK呼叫 TRUE GK路由 FALSE直接呼叫
//	
//	///////设备状态///////
	BOOL	bMatrixStatus;				    //外置矩阵状态		(TRUE ok FALSE err)
	u8		byCamNum;					    //摄像头个数	(0~6)
	BOOL	bCamStatus[MT_MAX_CAMERA_NUM];	//摄像头状态 (TRUE ok FALSE err)
	EmMtVideoPort emVideoSrc;					//当前本地视频源(0:S端子,1-6:C端子)

	BOOL    bIsEncrypt;
//	//编解码器状态
	EmAudioFormat	    emADecFormat;	//音频解码格式
	EmAudioFormat	    emAEncFormat;	//音频编码格式
	TMtVideoCodecStatus  tPVEncStatus;   //主视频编码器
	TMtVideoCodecStatus  tSVEncStatus;   //辅视频编码器
	TMtVideoCodecStatus  tPVDecStatus;   //主视频解码器
	TMtVideoCodecStatus  tSVDecStatus;   //辅视频解码器
//	
	u16		wSysSleep;					//待机时间(0x0表示不待机)
//VOD states
	BOOL bIsInVOD;
	EmUIPosion   byVodUser;
	//////配置状态///////
public:
   tagTTerStatus(){ memset ( this ,0 ,sizeof( struct tagTTerStatus) );}
}TTerStatus ,*PTTerStatus;

typedef struct tagTMtMixParam
{
	u8 byMixNum;
	u8 byDIscussMode;
	TMtId atMtMixItem[MT_MAXNUM_MIX_MEMBER];
public:
	tagTMtMixParam()
	{
		memset( this, 0, sizeof( struct tagTMtMixParam) );
	}
}TMtMixParam, *PTMtMixParam;

// 扩展画面合成参数
typedef struct tagTMtVmpItem
{
	TMtId        tMt;       //画面合成成员
	EmVMPMmbType emMmbType; //个成员的类型
	u32          adwReserved[8];
public:
	tagTMtVmpItem(){ memset ( this ,0 ,sizeof( struct tagTMtVmpItem) );}
}TMtVmpItem, *PTMtVmpItem;
//画面合成参数
typedef struct tagTMtVMPParam
{
	BOOL    bIsCustomVMP;  //是否自定义画面合成
	BOOL    bIsAutoVMP;    //是否自动画面合成
	BOOL    bIsBroadcast;
	EmVMPStyle emStyle;       //画面合成风格
	TMtVmpItem atMtVmpItem[MT_MAXNUM_VMP_MEMBER];
public:
	tagTMtVMPParam(){ memset ( this ,0 ,sizeof( struct tagTMtVMPParam) );}
}TMtVMPParam ,*PTMtVMPParam;



//轮询信息
typedef struct tagTMtPollInfo
{
	EmMediaType emMode;      //轮询模式 emMediaVide /emMediaAV 
	EmAction    emStat;      //    emStart/  emStop/  emPause 轮询状态
	u16         wKeepTime;   //终端轮询的保留时间 单位:秒(s)
	u8			byMtNum;			// 参加轮询的终端个数,0表示所有与会终端(单位个,最多CTRL_POLL_MAXNUM)
	TMtInfo	    atMtInfo[ MT_MAX_POLL_NUM ]; // 参加轮询的终端<m,t>
public:
	tagTMtPollInfo(){ memset ( this ,0 ,sizeof( struct tagTMtPollInfo) );}
}TMtPollInfo ,*PTMtPollInfo;

//轮询方案名集合
typedef struct tagTMtPollSchemeNameSet
{
	s8      achMtPollSchemeName[MAX_CHAIR_POLLSCHEME_NUM][MT_MAX_NAME_LEN + 1];
public:
	tagTMtPollSchemeNameSet(){ 
		memset ( this ,0 ,sizeof( struct tagTMtPollSchemeNameSet) );
	}
}TMtPollSchemeNameSet, *PTMtPollSchemeNameSet;

typedef struct tagTMtViewPollInfo
{
	EmMediaType emMode;      //轮询模式 emMediaVide /emMediaAV 
	EmAction    emStat;      //    emStart/  emStop/  emPause 轮询状态
	u16         wKeepTime;   //终端轮询的保留时间 单位:秒(s)
	u8			byMtNum;			// 参加轮询的终端个数,0表示所有与会终端(单位个,最多CTRL_POLL_MAXNUM)
	TMtInfo	    atMtInfo[ MT_MAX_POLL_NUM ]; // 参加轮询的终端<m,t>
public:
	tagTMtViewPollInfo(){ memset ( this ,0 ,sizeof( struct tagTMtViewPollInfo) );}
}TMtViewPollInfo ,*PTMtViewPollInfo;
 
typedef struct tagTMtSimpConfInfo 
{
	TMtId tSpeaker;
	TMtId tChairMan;
	BOOL  bIsVAC;
	BOOL  bIsDisc;
	BOOL  bIsAutoVMP;
	BOOL  bIsCustomVMP;
public:
	tagTMtSimpConfInfo(){ memset( this, 0, sizeof( struct tagTMtSimpConfInfo ) ); }
}TMtSimpConfInfo, *PTMtSimpConfInfo;
  
//定义会议信息
typedef struct tagTMtConfInfo
{
	s8          chConfId[MT_MAXLEN_CONFGUID+1];
	TMtKdvTime    tStartTime;//开始时间，控制台填0为立即开始
	u16           wDuration;   //持续时间(分钟)，0表示不自动停止
    u16           wBitRate;        //会议码率(单位:Kbps,1K=1024)
    u16           wSecBitRate;     //双速会议的第2码率(单位:Kbps,为0表示是单速会议)
    EmVideoResolution emMainVideoResolution;  //主视频格式
    EmVideoResolution emSecondVideoResolution; //辅视频格式
    EmVideoResolution emDoubleVideoResolution;   //第二路视频格式,
    u8            byTalkHoldTime;                 //最小发言持续时间(单位:秒)

	s8            achConfPwd[MT_MAXLEN_PASSWORD+1];    //会议密码
    s8            achConfName[MT_MAX_CONF_NAME_LEN+1]; //会议名
    s8            achConfE164[MT_MAX_CONF_E164_LEN+1]; //会议的E164号码
	
	BOOL          bIsAudioPowerSel;   //是否语音激励
	BOOL          bIsDiscussMode;     //是否讨论模式
    BOOL          bIsAutoVMP;            //是否自动多画面合成
	BOOL          bIsCustomVMP;        //是否自定义多画面合成
	BOOL          bIsForceBroadcast;//强制广播

    TMtId 	      tChairman;	   //主席终端，MCU号为0表示无主席
    TMtId		  tSpeaker;		  //发言终端，MCU号为0表示无发言人
    TMtPollInfo   tPollInfo;        //会议轮询参数,仅轮询时有较
    TMtVMPParam   tVMPParam;        //当前视频复合参数，仅视频复合时有效
  
public:
	tagTMtConfInfo(){ memset ( this ,0 ,sizeof( struct tagTMtConfInfo) );}
}TMtConfInfo ,*PTMtConfInfo;

//IP传输地址
typedef struct tagTIPTransAddr
{
	u32_ip dwIP ;
	u16 wPort;
public:
	tagTIPTransAddr(){ memset( this, 0, sizeof( struct tagTIPTransAddr));}
}TIPTransAddr,*PTIPTransAddr;

//终端地址
typedef struct tagTMtAddr
{
	EmMtAddrType emType;							//地址类型
	u32_ip			 dwIP;						//终端IP地址
	s8			 achAlias[MT_MAX_H323ALIAS_LEN+1];		//(别名)
public:
	tagTMtAddr(){memset( this ,0 ,sizeof( struct tagTMtAddr));	}
}TMtAddr,*PTMtAddr;




//会议标识
typedef struct tagTConfId
{
	u8  byGuid[MT_MAXLEN_CONFGUID];//会议Id
	TMtAddr   tAlias;    //会议别名
public:
	tagTConfId(){ memset( this ,0 ,sizeof( struct tagTConfId)) ;	}
}TConfId ,PTConfId ;

// 呼叫链路状态结构
typedef struct tagTLinkState
{
	EmCallState emCallState; //会话状态
	u32_ip			dwIpAddr;					  // 对端IP地址(网络序)
	s8  		achAlias[ MT_MAX_NAME_LEN + 1 ];  // 对端别名
	BOOL        bCalling;                         // TRUE = 主叫  FALSE=被叫
	EmCallDisconnectReason	emReason;   // 呼叫挂断原因
	BOOL        bGetChairToken;                   //获得主席令牌
	BOOL        bSeenByAll;                       //被广播
	u16         wCallRate;                        //呼叫码率
	EmMtModel   emPeerMtModel;                    //add by xujinxing,07/07/26,对端型号
public:
	tagTLinkState(){ memset( this ,0 ,sizeof( struct tagTLinkState ) );}
}TLinkState,*PTLinkState;


//TEmbedFwNatProxy 内嵌防火墙代理配置结构
typedef struct tagTEmbedFwNatProxy
{
    BOOL   bUsed;
    u32_ip dwFwNatProxyServIP;
	s8     achPrxySrvName[MT_MAX_PROXYSERVER_NAME_LEN];
    u16    wFwNatProxyServListenPort;
    u16    wStreamBasePort;//媒体流传输起始端口号
public:
	tagTEmbedFwNatProxy(){ memset( this ,0 ,sizeof( struct tagTEmbedFwNatProxy ) );}
}TEmbedFwNatProxy,*PTEmbedFwNatProxy;


//静态NAT映射地址
typedef struct tagTNATMapAddr
{
	BOOL bUsed; //是否启用静态映射地址
	u32_ip  dwIP;  //映射地址
public:
	tagTNATMapAddr(){ memset( this ,0 ,sizeof( struct  tagTNATMapAddr ) );}
}TNATMapAddr,*PTNATMapAddr;

//SIP Register配置
typedef struct tagTSipRegistrarCfg
{
	BOOL   bUsed;   //是否注册
	u32_ip dwRegIP; //注册服务器IP地址
	u16    wRegPort;//注册服务器端口
	s8     achRegDomain[MT_MAX_PROXYSERVER_NAME_LEN];
	u16    wExpire;

	s8     achDisplayName[MT_MAX_NAME_LEN+1];  //别名
    s8     achUserName[MT_MAX_NAME_LEN+1];     //注册名
	s8     achPassword[MT_MAX_PASSWORD_LEN+1]; //注册密码
	s8     achHostDomain[MT_MAX_PROXYSERVER_NAME_LEN];//自身域名
	u32_ip dwHostIP;
	u16    wHostPort;      
public:
	tagTSipRegistrarCfg(){ memset( this, 0, sizeof(struct tagTSipRegistrarCfg) ); }
}TSipRegistrarCfg,*PTSipRegistrarCfg;

//GK配置
typedef struct tagTGKCfg
{
	BOOL bUsed; //是否使用GK
	u32_ip  dwGKIP; //GK IP地址
    s8   achGkIpName[MT_MAX_H323GKSERVER_NAME_LEN]; //Gk域名地址
	s8   achGKPasswd[MT_MAX_PASSWORD_LEN + 1]; //Gk密码
public:
	tagTGKCfg(){ memset( this ,0 ,sizeof( struct  tagTGKCfg ) );}
}TGKCfg,*PTGKCfg;

/************************************************************************/
/* 内置GK信息数据结构定义                                               */
/************************************************************************/
typedef struct tagTInnerGKCfg
{
    BOOL bGKUsed; //是否启用内置GK
    u32_ip dwIp; //ip地址
    u32_ip dwMask; //子网掩码
    u32_ip dwGateWay; //网关
public:
    tagTInnerGKCfg(){ memset( this, 0, sizeof(struct tagTInnerGKCfg ) ); }   
}TInnerGKCfg, *PTInnerGKCfg;

/************************************************************************/
/* 内置Proxy信息数据结构定义                                               */
/************************************************************************/
typedef struct tagTInnerProxyCfg
{
    BOOL bInnerProxyUsed; //是否启用代理服务器
    u32_ip dwIp; //ip地址
    u32_ip dwMask; //子网掩码
    u32_ip dwGateWay; //网关
public:
    tagTInnerProxyCfg(){ memset( this, 0, sizeof(struct tagTInnerProxyCfg ) ); }  
}TInnerProxyCfg, *PTInnerProxyCfg;

/************************************************************************/
/* WiFi无线网络信息数据结构定义                                         */
/************************************************************************/
typedef struct tagTWiFiNetCfg
{
    BOOL   bWiFiUsed;  //是否启用WiFi 
    BOOL   bDHCP;      //是否启用DHCP
    u32_ip dwIp;       //ip地址
    u32_ip dwMask;     //子网掩码
    u32_ip dwGateWay;  //网关
public:
    tagTWiFiNetCfg(){ memset( this, 0, sizeof(struct tagTWiFiNetCfg ) ); }  
}TWiFiNetCfg, *PTWiFiNetCfg;

// TMonitorService（监控切换业务数据结构） 
typedef struct tagTMonitorService
{
	BOOL bSwitchEnable;
	//空闲时切换到监控业务的时间间隔
	u32   dwSwitchTimeout;
public:
	tagTMonitorService(){ memset( this ,0 ,sizeof( struct  tagTMonitorService ) );}
}TMonitorService,*PTMonitorService;

//矩形结构定义
typedef struct  tagTRect
{
    u16  wLeft;
    u16  wTop;
    u16  wWidth;
    u16  wHeight;
public:
 	tagTRect(){ memset( this ,0 ,sizeof( struct  tagTRect ) );}
}TRect;

//双流码率比例配置
typedef struct tagTDualRation
{
    BOOL bSecondSendRateType;   //TRUE auto
    BOOL bSecondRecvRateType;   //接收码率类型
    u8 bySecondSendRate;  //如果不是自动时双流发送码率的比例值
    u8 bySecondRecvRate;  //双流接收码率的比例值
    u8 byPrimaryRecvRate; //单流接收码率的比例值
    tagTDualRation(){ memset( this ,0 ,sizeof( struct  tagTDualRation ) );}
}TDualRation, *PTDualRation;

//	图像调整参数
typedef struct tagTImageAdjustParam
{	 
	u8  wBrightness;//亮度  	 
	u8  wContrast;   //对比度  	
	u8  wSaturation; //色彩饱和度 
public:
	tagTImageAdjustParam(){ memset( this ,0 ,sizeof( struct  tagTImageAdjustParam ) );}
	
}TImageAdjustParam,*PTImageAdjustParam;


//视频编码参数
typedef struct tagTVideoEncodeParameter    
{
	EmVideoFormat      emVideoFormat; 
	u16                byMaxKeyFrameInterval; // I帧间最大P帧数目
    u8                 byMaxQuant;  //最大量化参数
	u8                 byMinQuant;  //最小量化参数
    BOOL               bUseFixedFrame; //是否使用固定帧率
	u8	               byFrameRate;  //帧率
	BOOL               bFramePerSecond;  //帧率单位 TRUE＝ 帧/秒  FALSE＝秒/帧 

    EmEncodeMode emEncodeMode;     //编码方式
	EmVideoResolution  emVideoResolution;
	u32                wChanMaxBitrate; // 单位 Kbps
//以下数据只有在windows平台下有用
//添加采集图像宽高
	u16	m_wWidth; //视频捕获图像宽度 仅Windows有效(default:640)
	u16	m_wHeight;//视频捕获图像高度 仅Windows有效(default:480)
	EmMediaType   emCapType;    //采集类型   (default:emMediaAV)
	EmPCCapFormat emPCCapFormat;//视频捕获帧格式 仅Windows有效(default:emCapPCFrameBMP)
public:
	tagTVideoEncodeParameter(){ memset( this ,0 ,sizeof( struct  tagTVideoEncodeParameter ) );}	
}TVideoEncodeParameter ,*PTVideoEncodeParameter;

typedef struct tagTEncryptKey
{
	u8 byLen;   //密钥长度
	u8 byKey[MT_MAXLEN_ENCRYPTKEY]; //密钥长度
public:
	tagTEncryptKey(){ memset( this ,0 ,sizeof( struct  tagTEncryptKey ) );}	
}TEncryptKey,*PTEncryptKey;

//视频通道参数
typedef struct tagTVideoChanParam
{
	EmVideoFormat     emVideoFormat;
	EmVideoResolution emVideoResolution;
	u32                wChanMaxBitrate; // 单位 Kbps
	u8                 byPayload;       //动态载荷
	TEncryptKey        tKey;            //若tKey.byLen=0 表示不加密
	BOOL               bIsH239;
	u8                 byFrameRate;          //帧率
 // 	u8                 byFrameRate;     2005-12-19 张明义委托张飞添加
public:
	tagTVideoChanParam()
	{ 
		emVideoFormat = emVEnd;
		emVideoResolution = emVResEnd;
		wChanMaxBitrate   = 0;
		byPayload         = 0;
		memset( &tKey ,0 ,sizeof(tKey) );
		bIsH239  = FALSE;
		byFrameRate = 25;
	}	
}TVideoChanParam ,*PTVideoChanParam;

//视频通道参数
typedef struct tagTAudioChanParam
{
	EmAudioFormat   emAudioFormat;
  
	u8               byPayload;     //动态载荷
	TEncryptKey      tKey;          //若tKey.byLen=0 表示不加密
public:
	tagTAudioChanParam()
	{
		emAudioFormat = emAEnd;
		byPayload     = 0;
		memset( &tKey ,0 ,sizeof(tKey));
	}
}TAudioChanParam ,*PtagTAudioChanParam;

//***************************** VOD *************************************
//
//登陆VOD服务器用户信息
//
typedef struct tagTVODUserInfo
{
	TIPTransAddr m_tIp;  //VOD服务器地址
	s8   m_achUserName[VOD_MAX_USER_NAME_LENGTH + 1];//用户名
	s8   m_achUserPass[VOD_MAX_PASSWORD_LENGTH + 1];//用户密码
	BOOL m_bRecordNamePass; //下次登录是否提示用户名和密码
public:
	tagTVODUserInfo()
	{
		memset(this,0,sizeof(tagTVODUserInfo));
	}
}TVODUserInfo,*PTVODUserInfo;


//
// vod 文件信息 本结构取代 TVODFileNameInfo+TVODFileInfo 
//
typedef struct tagTVODFile
{
	s8   achName[ MT_MAX_NAME_LEN + 1 ]; // 文件名
    BOOL bIsFile;     // TRUE =file FALSE= folder
    u32  dwFileSize;  // 文件长度
	//-- 文件信息--
	BOOL bIsInfoValid;       //文件信息是否有效
	u32 dwRecordTime;        //录制时间，
    u32 dwDuration;          //播放总时长，毫秒
    EmAudioFormat emAudio;          //音频， emAEnd表示没有该路码流 
    EmVideoFormat emPrimoVideo;     //视频1，emVEnd表示没有该路码流 
    EmVideoFormat emSecondVideo;    //视频2，emVEnd表示没有该路码流
public:
	tagTVODFile(){ memset( this ,0 ,sizeof( struct  tagTVODFile ) );}
}TVODFile;
//
// Files from VODServer Directory 
//
 
typedef struct tagTE1Group
{                                                                                                            
	u8  byGroupIndex;              // E1分组序号
    u32 dwE1Mask;                 // 使用的E1的掩码                                                                    
    u32_ip  dwIP;                  //  ip地址                                                                          
	u32_ip  dwIPMask;             //  掩码       
	EmDLProtocol emProtocol;       //接口协议封装类型,如果是单E1连接可以指定PPP/HDLC                                                                   
	BOOL  bEnable;               //是否启用        
	// 多通道参数
    EmAuthenticationType emAuthenticationType;//PPP链接的验证方法PAP/CHAP,默认填emPAP 
    u32  dwFragMinPackageLen;       //  最小分片包长，字节为单位，范围20~1500，默认填20                                 
	s8   achSvrUsrName[MT_MAX_E1_NAME_LEN+1]; 	/* 服务端用户名称  */                                  
	s8   achSvrUsrPwd[MT_MAX_E1_NAME_LEN+1];   	/* 服务端用户密码  */                         
	s8   achSentUsrName[MT_MAX_E1_NAME_LEN+1];	/* 客户端用户名称，用来被对端验证 */                                           
	s8   achSentUsrPwd[MT_MAX_E1_NAME_LEN+1]; 	/* 客户端用户密码，用来被对端验证 */  
	u32  dwVal;                   //保留
public:
	tagTE1Group(){ memset( this ,0 ,sizeof( struct  tagTE1Group ) );}
}TE1Group, *PTE1Group;

//
// File Info from VODServer
//

//
// Request Play Info from UI
//

typedef struct tagTVideoSourceInfo
{
	EmMtVideoPort  emVideoPort;
	s8  achPortName[MT_MAX_PORTNAME_LEN +1];
public:
	tagTVideoSourceInfo( ) { memset( this, 0, sizeof ( *this ) );	}
}TVideoSourceInfo,*PTVideoSourceInfo;


//外部矩阵信息
typedef struct tagTExternalMatrixInfo 
{
	s8 TypeName[ MT_MAX_AVMATRIX_MODEL_NAME ]; //矩阵型号
	u8 OutPort; //指定的输出断口号
	u8 InPortTotal; //输入端口总数 
public:
	tagTExternalMatrixInfo( ) { memset( this, 0, sizeof ( *this ) );	}

} TExternalMatrixInfo, *PTExternalMatrixInfo;


//内部矩阵方案结构
typedef struct tagTAVInnerMatrixScheme
{
	  EmMatrixType  emType; //矩阵类型
		s8 achName[ MT_MAXLEN_AVMATRIX_SCHEMENAME + 1 ]; 
		u8 byIndex; 
		//
		// 输出端口号( 1 - 6 )
		// 各个输出端口连接的输入端口
		//
		u8 abyOutPort2InPort[ 6 ]; 
		//
		// 端口( 1- 6 )名字
		//
		s8 achOutPortName[6][ MT_MAXLEN_AVMATRIX_SCHEMENAME + 1 ];
		s8 achInPortName [6][ MT_MAXLEN_AVMATRIX_SCHEMENAME + 1 ];
public:
	tagTAVInnerMatrixScheme( )
	{
		memset( this, 0, sizeof ( struct tagTAVInnerMatrixScheme ) );
	}
}TAVInnerMatrixScheme,*PTAVInnerMatrixScheme;

//
//    配置通知数据结构
//

/************************************************************************/
/* 会议相关信息数据结构定义结束                                         */
/************************************************************************/

//////////////////////////////////////////////////////////////////////////
//丢包时自动降低码率配置
typedef struct tagTBitRateAdjust
{
	BOOL bEnable;   //是否启动
	u16  wInterval;  //时间间隔
	u16  wLostTimes; //丢包次数
	u16  wDescRatio; //降速比率
	u16  wLowDescRatio; //慢速降速码率
	u16  wDelayInterval;  //延迟时间
public:
	tagTBitRateAdjust(){ memset( this ,0 ,sizeof( struct  tagTBitRateAdjust ) );}
}TBitRateAdjust,*PTBitRateAdjust;

//////////////////////////////////////////
//编码器统计信息
typedef struct tagTCodecPackStat
{
	u16    wBitrate;       //实时码率
	u16    wAvrBitrate;    //平均码率
	u32    dwLostPacks;    //丢包数
	u32    dwTotalPacks;   //收发包数
	u32    dwFrames;       //收发帧数
	u8     byLostFrameRate;//丢帧率(2秒)%d   
public:
	tagTCodecPackStat(){ memset( this ,0 ,sizeof( struct  tagTCodecPackStat ) );}
}TCodecPackStat,*PTCodecPackStat;

//视频统计信息
typedef struct tagTVideoStatistics
{
	BOOL             bH239;	
	EmVideoFormat     emFormat;      //格式
	EmVideoResolution emRes;
	TCodecPackStat    tPack;
public:
	tagTVideoStatistics(){ memset( this ,0 ,sizeof( struct  tagTVideoStatistics ) );}
}TVideoStatistics ,*PTVideoStatistics;

//视频统计信息
typedef struct tagTAudioStatistics
{
	EmAudioFormat     emFormat;      //格式
	TCodecPackStat    tPack;
public:
	tagTAudioStatistics(){ memset( this ,0 ,sizeof( struct  tagTAudioStatistics ) );}
}TAudioStatistics ,*PTAudioStatistics;

/************************************************************************/
/* PCMT视频源信息 Add by FangTao                                                       */
/************************************************************************/
typedef struct tagTCapType
{
	s8 m_achCapFileName[MT_MAX_FULLFILENAME_LEN+1];
	EmCapType emCapType;
public:
	tagTCapType(){ memset(this ,0 ,sizeof( tagTCapType)); }
}TCapType ,*PTCapType;

//呼叫统计信息
typedef struct tagTCallInfoStatistics
{
	u16               wCallBitrate;//呼叫码率
	EmEncryptArithmetic emRecvEncrypt; //会议接收加密类型
	EmEncryptArithmetic emSendEncrypt; //会议发送加密类型
	TAudioStatistics  tRecvAudio;//音频接收格式
	TAudioStatistics  tSendAudio;//音频发送格式

	TVideoStatistics tPrimoRecvVideo;  //主视频接收统计信息 
	TVideoStatistics tPrimoSendVideo;  //主视频发送统计信息 
	TVideoStatistics tSencodRecvVideo; //第二路视频接收统计信息 
	TVideoStatistics tSecondSendVideo; //第二路视频发送统计信息 
public:
	tagTCallInfoStatistics()
	{
		wCallBitrate = 0;
		emRecvEncrypt = emEncryptNone;
		emSendEncrypt = emEncryptNone;
		tRecvAudio.emFormat = emAEnd;
		memset(&tRecvAudio.tPack,0,sizeof(tRecvAudio.tPack));
		memcpy(&tSendAudio,&tRecvAudio,sizeof(tSendAudio));

		tPrimoRecvVideo.bH239 = FALSE;
		tPrimoRecvVideo.emFormat = emVEnd;
		tPrimoRecvVideo.emRes = emVResEnd;
		memset(&tPrimoRecvVideo.tPack,0,sizeof(tPrimoRecvVideo.tPack));

		memcpy(&tPrimoSendVideo,&tPrimoRecvVideo,sizeof(tPrimoRecvVideo));
		memcpy(&tSencodRecvVideo,&tPrimoRecvVideo,sizeof(tPrimoRecvVideo));
		memcpy(&tSecondSendVideo,&tPrimoRecvVideo,sizeof(tPrimoRecvVideo));
	}

}TCallInfoStatistics,*PTCallInfoStatistics;


/************************************************************************/
/* 双流盒信息                                                           */
/************************************************************************/
typedef struct tagTDualStreamBoxInfo
{
	BOOL   m_bUsed;
	u32_ip m_dwIp;
	u16    m_wPort;
public:
	tagTDualStreamBoxInfo(){ memset( this ,0 ,sizeof( struct  tagTDualStreamBoxInfo ) );}
}TDualStreamBoxInfo,*PTDualStreamBoxInfo;


/************************************************************************/
/* 编码器统计信息                                                       */
/************************************************************************/

typedef  struct tagTFileTransfer 
{
public:
	//版本号		0x0100
	u16 wProtocolIdentifer;

	// 文件传输当前分片编号，0开始编号，循环标号
	u16 wFileSliceNo;


	//文件类型		台标,滚动消息,字幕
	u8 byType;

	//原因
	u8 byRspInfo;
	
	//文件标识符
	u16 wFileIdentifer;

	//消息包最大长度
	u16 wPakageMaxLen;

	//用户数据长度，值=消息头+文件切片长度
	u16 wDataLen;
public:
	tagTFileTransfer(){ memset( this ,0 ,sizeof( struct  tagTFileTransfer ) );}
}TFileTransfer,*PTFileTransfer;

/************************************************************************/
/* 双流盒结构定义
/************************************************************************/
typedef struct tagTDVBNetSession
{
	 //[xujinxing]
	 u32_ip   m_dwRTPAddr; /*RTP地址*/
	 u16    m_wRTPPort;  /*RTP端口*/
	 u32_ip   m_dwRTCPAddr;/*RTCP地址*/
	 u16    m_wRTCPPort; /*RTCP端口*/
public:
	tagTDVBNetSession(){ memset( this ,0 ,sizeof( struct  tagTDVBNetSession ) );}
}TDVBNetSession,*PTDVBNetSession;

typedef struct tagTDVBNetSndParam
{
	 u8 m_byNum;
	 TDVBNetSession m_tLocalNet;
	 TDVBNetSession m_tRemoteNet[MT_MAX_NETSND_DEST_NUM];
public:
	tagTDVBNetSndParam(){ memset( this ,0 ,sizeof( struct  tagTDVBNetSndParam ) );}
}TDVBNetSndParam,*PTDVBNetSndParam;

typedef struct tagTDVBLocalNetParam
{
	 TDVBNetSession  m_tLocalNet;
	 u32_ip        m_dwRtcpBackAddr;/*RTCP回发地址*/
	 u16         m_wRtcpBackPort; /*RTCP回发端口*/ 
public:
	tagTDVBLocalNetParam(){ memset( this ,0 ,sizeof( struct  tagTDVBLocalNetParam ) );}
}TDVBLocalNetParam,*PTDVBLocalNetParam;

typedef struct tagTDVBVideoEncParam
{
	u8  m_byEncType;   /*图像编码类型*/
    u8  m_byRcMode;    /*图像压缩码率控制参数*/
    u16  m_byMaxKeyFrameInterval;/*I帧间最大P帧数目*/
    u8  m_byMaxQuant;  /*最大量化参数(1-31)*/
    u8  m_byMinQuant;  /*最小量化参数(1-31)*/
    u8  m_byReserved1; /*保留*/
    u8  m_byReserved2; /*保留*/
    u8  m_byReserved3; /*保留*/
    u16  m_wBitRate;    /*编码比特率(Kbps)*/
    u16  m_wReserved4;  /*保留*/		
	u32 m_dwSndNetBand;/*网络发送带宽(单位:Kbps,1K=1024)*/   
    u32 m_dwReserved5; /*保留*/

	u8    m_byPalNtsc;    /*图像制式(PAL或NTSC)*/	
	u8    m_byCapPort;    /*采集端口号: 1~7有效。在KDV8010上，S端子端口号为7；C端子端口号缺省为2*/
	u8	m_byFrameRate;  /*帧率(default:25)*/	
	u8    m_byImageQulity;/*图象压缩质量,0:速度优先;1:质量优先*/
	u8    m_byReserved6;  /*保留*/
	u16	m_wVideoWidth;  /*图像宽度(default:640)*/
	u16	m_wVideoHeight; /*图像高度(default:480)*/


	u8  m_byFrameFmt; // 分辨率 0:不固定类型, 1: half cif, 2: 1 cif, 3: 2 cif,  4: 4 cif,  5: 用于图像合成编码  
	u8	m_byFrmRateCanSet; //帧率是否由外界设定 ?
	u8  m_byFrmRateLittleThanOne; // 帧率是否小于1 ?
public:
	tagTDVBVideoEncParam(){ memset( this ,0 ,sizeof( struct  tagTDVBVideoEncParam ) );}
}TDVBVideoEncParam,*PTDVBVideoEncParam;

typedef struct tagTSitecallInformation
{
	BOOL m_bIsCustomConf;
	s8 m_achConfName[MT_MAX_CONF_NAME_LEN+1];
	s8 m_achConfPwd[MT_MAXLEN_PASSWORD+1];
	BOOL m_bLocalPay;	
	s8 m_achConfCard[MT_MAX_CONF_NAME_LEN+1];
	s8 m_achConfCardPwd[MT_MAXLEN_PASSWORD+1];
	u8 m_byMultiPicCount;
	EmCallRate        m_emRate;
	EmVideoFormat     m_emVideoType;
	EmVideoResolution m_emVideoFormat;
	EmAudioFormat     m_emAudioFormat;
	u8   m_byTerninalCount;
	TMtAddr m_atTerminalE164Info[MT_MAX_CALLSITE_TERNINAL];
	TMtAddr m_atTerminalH323Info[MT_MAX_CALLSITE_TERNINAL];
public:
	tagTSitecallInformation()
	{
		memset(this,0,sizeof(tagTSitecallInformation));
		m_emRate = emRaten64;
		m_emVideoType = emVH263;
		m_emVideoFormat = emVCIF;
		m_emAudioFormat = emAG711a;
		m_bLocalPay = TRUE;
	}
}TSitecallInformation,*PTSitecallInformation;

typedef struct tagTTransparentSerial
{
    EmSerialType  m_emComType;
	u32           m_nDataLen;
    s8            m_achData[128];
public:
	tagTTransparentSerial(){ memset( this ,0 ,sizeof( struct  tagTTransparentSerial ) );}
}TTransparentSerial,*PTTransparentSerial;

typedef struct tagTPeerCapabilityInfo
{
    BOOL m_bMix;                        //混音
    BOOL m_bVAC;                        //语音激励
    BOOL m_bCustomVMP;                  //定制画面合成
    BOOL m_bAutoVMP;                    //自动画面合成
    BOOL m_bEndConf;                    //结束会议
    BOOL m_bInvateMt;                   //邀请终端
    BOOL m_bDropMt;                     //删除终端
    BOOL m_bSelSpeaker;                 //指定/取消发言人
    BOOL m_bSelChair;                   //指定/放弃主席
    BOOL m_bSelSource;                  //选看终端
    BOOL m_bFECC;                       //远程摄像头遥控
    BOOL m_bQuiet;                      //远端静音
    BOOL m_bMute;                       //远端哑音
    BOOL m_bConfReq;                    //会议申请处理
    BOOL m_bOnlineList;                 //在线终端列表
    BOOL m_bOfflineList;                //离线终端列表
	BOOL m_bPicSwitch;                  //画面切换
	BOOL m_bSelSpeakingUser;            //点名 
	BOOL m_bForceBroadcast;             //强制广播
public:
	tagTPeerCapabilityInfo(){ memset( this ,0 ,sizeof( struct  tagTPeerCapabilityInfo ) );}
}TPeerCapabilityInfo,*PTPeerCapabilityInfo;


/************************************************************************/
/*              快捷键结构体                                            */
/************************************************************************/
typedef struct tagTRapidKey 
{
	EmMtVideoPort emMainVidSrcBtn;
	EmHotKeyType emRedBtn;
	EmHotKeyType emYellowBtn;
	EmHotKeyType emGreenBtn;
public:
	tagTRapidKey(){ memset( this ,0 ,sizeof( struct  tagTRapidKey ) );}
}TRapidKey, *PTRapidKey;

/************************************************************************/
/*              终端在线升级结构体                                      */
/************************************************************************/
//升级版本中的文件信息
typedef struct tagTVerFileInfo
{
    EmMtOSType   m_emFileType;       //文件类型(Linux,Vxworks)
    u32          m_dwFileSize;       //文件大小(按字节计算)
    s8           m_szFileName[MT_MAX_FILESRV_FILENAME_LEN];//文件名
public:
	tagTVerFileInfo(){ memset( this ,0 ,sizeof( struct  tagTVerFileInfo ) );}
}TVerFileInfo, *PTVerFileInfo;

//升级版本的信息
typedef struct tagTVerInfo
{ 
    u8 m_byFileNum;
    s8 m_achBugReport[MT_MAX_FILESRV_BUG_REPORT_LEN];
    s8 m_achSoftVer[MT_MAX_FILESRV_SOFTWARE_VER_LEN];
    TVerFileInfo m_atVerFile[MT_MAX_FILESRV_DEVFILE_NUM];
public:
	tagTVerInfo(){ memset( this ,0 ,sizeof( struct  tagTVerInfo ) );}
}TVerInfo,*PTVerInfo;


// FEC配置信息结构
typedef struct tagTFecInfo
{
	BOOL   m_bEnableFec;   //视频是否使用前向纠错
	u8     m_byAlgorithm;  //设置fec算法 0:NONE 1:RAID5 2:RAID6
	u16    m_wPackLen;     //设置fec的切包长度
	BOOL   m_bIntraFrame;  //是否帧内fec
	u32    m_dwDataPackNum; //设置fec的x包数据包
	u32    m_dwCrcPackNum;  //设置fec的y包冗余包
public:
	tagTFecInfo(){ memset( this, 0, sizeof( struct tagTFecInfo ) ); }
}TFecInfo,*PTFecInfo;

//ruiyigen 091216
typedef struct tagTVInnerMatrixScheme
{
	u8 byIndex;
	s8 achName[MT_MAXLEN_AVMATRIX_SCHEMENAME + 1];
	u8 abyOutPort2InPort[MT_HD_MAX_AV_OUTPORT_NUM]; //依次为DVI1,DVI2,DVI3,SDI输出
	u8 abyDVIMode[MT_DVI_PORT_NUM];//依次为DVI1,DVI2,DVI3输入,DVI1,DVI2,DVI3输出
	s8 achOutPortName[6][ MT_MAXLEN_AVMATRIX_SCHEMENAME + 1 ];
	s8 achInPortName [6][ MT_MAXLEN_AVMATRIX_SCHEMENAME + 1 ];
public:
	tagTVInnerMatrixScheme()
	{
		memset( this, 0, sizeof(struct tagTVInnerMatrixScheme) );
		memset( abyOutPort2InPort, HD2G_VIDEO_IN_INVALID, sizeof(abyOutPort2InPort) );
	}
}TVInnerMatrixScheme,*PTVInnerMatrixScheme;


template < class T >
T SAFE_CAST( T &t, u8 *p )
{
	if (NULL == p) return t;
	memcpy( &t, p, sizeof( T ) );
	return t;
}



//char* GetStructVersion();

// 地址薄条目信息
typedef struct tagTAddrEntry
{
    s8      m_achEntryName[ MT_MAX_NAME_LEN + 1 ];		// 条目名字
    s8      m_achIpaddr[ MT_MAX_H323ALIAS_LEN + 1 ];	// 呼叫地址
    u32     m_dwCallTime;                               // 呼叫时间
    u16	    m_wCallRate;								// 呼叫速率
	BOOL    m_bTeleCall;
public:
	tagTAddrEntry(){ memset( this ,0 ,sizeof( struct  tagTAddrEntry ) );}
}TAddrEntry,*PTAddrEntry;


/************************************************************************/
/* 内置代理，多网段接入的配置                                           */
/************************************************************************/
typedef struct tagTPxyIPCfg
{
    BOOL bUsed;
    u32_ip dwIP;         //IP地址
    u32_ip dwMask;       //子网掩码
    u32_ip dwGateway;    //网关地址
public:
	tagTPxyIPCfg(){ memset( this ,0 ,sizeof( struct  tagTPxyIPCfg ) );}
}TPxyIPCfg, *PTPxyIPCfg;

typedef struct tagTWifiLinkInfo
{
    s8       achSSID[MT_MAX_NAME_LEN];            /* WiFi network name */
	s8       achBssMacAddr[MT_MAX_NAME_LEN];      /* Bss Mac Address*/
    u32      dwSignalLevel;                         /*Signal level : 0-100*/
    u32      dwLinkRate;				 	        /* Rate, unit: mpbs */
    u32      dwChannel;                             /* Wireless channel number*/
    u8       byAuthType;                            /*Authentication method*/
    u8       byEncrytoType;                         /*Encryto method*/
	u8       byNetType;                             /*ad-hoc or infra*/
public:
	tagTWifiLinkInfo(){ memset( this ,0 ,sizeof( struct  tagTWifiLinkInfo ) );}
}TWifiLinkInfo, *PTWifiLinkInfo;

typedef struct tagTWifiScanResult
{
    u32 dwBssNum;   /*Number of Link info, 0 -- WIFI_MAX_BSS_NUM*/
    TWifiLinkInfo tLinkInfo[WIFI_MAX_BSS_NUM];
public:
	tagTWifiScanResult(){ memset( this ,0 ,sizeof( struct  tagTWifiScanResult ) );}
} TWifiScanResult, *PTWifiScanResult;

typedef struct tagTWifiLinkCfgItem
{
	u32  dwId;
    s8   achCfgName[WIFI_MAX_NAME_LEN]; /*Configure name, shall not be empty when need save */
    TWifiLinkInfo tWifiLinkInfo;           /* Wifi link basic info*/

    s8   achWepKey1[WIFI_MAX_KEY_LEN];     /*Web key, shall not be null when byAuthType is Web*/
    s8   achWepKey2[WIFI_MAX_KEY_LEN];
    s8   achWepKey3[WIFI_MAX_KEY_LEN];
    s8   achWepKey4[WIFI_MAX_KEY_LEN];
    s8   achWpaPasswd[WIFI_MAX_KEY_LEN];  /*Wpa key, shall not be null when byAuthType is wpa or wpa2*/
public:
	tagTWifiLinkCfgItem(){ memset( this ,0 ,sizeof( struct  tagTWifiLinkCfgItem ) );}
}TWifiLinkCfgItem, *PTWifiLinkCfgItem;


//扫描SSID信息
typedef struct tagTWiFiBSSIDInfo
{
    u8                      byPSKOFF;                              //PSK or enterprise
    EmWiFiNetType           emNetType;                             //网络类型
    EmWiFiEncryptType       emEncryptType;                         //加密类型
    EmWiFiEncryptArithmetic emArithType;                           //加密算法
    BOOL                    bEncrypt;                              //是否加密
    u32                     dwChannel;                             //Wireless channel number
    u32                     dwBeaconInterval;                      //BCN（省电参数）
    u32                     dwLinkRate;				 	           //Rate, unit: mpbs 
    u32                     dwSignalLevel;                         //信号强度
    s8                      achBSSMacAddr[MT_WIFI_MAX_NAME_LEN];   // Bss Mac Address
    s8                      achSSID[MT_WIFI_MAX_NAME_LEN];         //WiFi network name
    s8                      achPasswd[MT_WIFI_MAX_PASSWORD_LEN];   //加密密码
public:
    tagTWiFiBSSIDInfo()
    {
        memset( this, 0, sizeof( struct tagTWiFiBSSIDInfo ) );
    }
}TWiFiBSSIDInfo, *PTWiFiBSSIDInfo;

//配置SSID信息,是否需要保存其他的配置信息如省电模式,待确定?
typedef struct tagTWiFiBSSIDCfg
{
    u8                      byPSKOFF;                              //PSK or enterprise
    EmWiFiNetType           emNetType;                             //网络类型
    EmWiFiEncryptType       emEncryptType;                         //加密类型
    EmWiFiEncryptArithmetic emArithType;                           //加密算法
    BOOL                    bEncrypt;                              //是否加密
	u32                     dwCfgPri;                              //网络连接优先级
    u32                     dwChannel;                             //Wireless channel number
    s8                      achSSID[MT_WIFI_MAX_NAME_LEN];           //WiFi network name
    s8                      achPassword[MT_WIFI_MAX_PASSWORD_LEN];   //加密密码
    //u8                      byCfgType;                             //扫描项，配置项
    //s8                      achBSSMacAddr[MT_WIFI_MAX_NAME_LEN];   // Bss Mac Address
    //u32                     dwBeaconInterval;                      //BCN（省电参数）
    //u32                     dwLinkRate;				 	           //Rate, unit: mpbs
    //u32                     dwSignalLevel;                         //信号强度
public:
    tagTWiFiBSSIDCfg()
    {
        memset( this, 0, sizeof( struct tagTWiFiBSSIDCfg ) );
    }
}TWiFiBSSIDCfg, *PTWiFiBSSIDCfg;

typedef struct tagTGkRegInfo
{
	BOOL bRegisted;
	EmGKRegFailedReason emReason;
public:
	tagTGkRegInfo(){ memset( this ,0 ,sizeof( struct  tagTGkRegInfo ) );}
}TGkRegInfo, *PTGkRegInfo;

typedef struct tagTSipRegResult
{
	BOOL bRegistered;
	EmSipRegFailedReason emReason;
}TSipRegResult, *PTSipRegResult;

typedef struct tagTHdAudioPort
{
	u8 abHdAudPortIn[MT_MAX_HDAUDIOPORT_LEN];
	u8 abHdAudPortOut[MT_MAX_HDAUDIOPORT_LEN];
public:
	tagTHdAudioPort(){ memset( this ,0 ,sizeof( struct  tagTHdAudioPort ) );}
}THdAudioPort, *PTHdAudioPort;

typedef struct tagTMiscCfg
{
	BOOL bUseSlice; //启用切包传输
public:
	tagTMiscCfg(){ memset( this ,0 ,sizeof( struct  tagTMiscCfg ) );}
}TMiscCfg, *PTMiscCfg;

typedef struct tagTVideoDisplayFrm
{
    u32 m_dw1080PFrm;
    u32 m_dw1080IFrm;
    u32 m_dwVGAFrm;
    u32 m_dw720PFrm;
    u32 m_dwSDFrm;
public:
		tagTVideoDisplayFrm()
		{
			memset( this, 0, sizeof( struct tagTVideoDisplayFrm ) );
    }
}TVideoDisplayFrm,*PTVideoDisplayFrm;


typedef struct tagTDownLoadPara
{
public:
	u8	byFileType;			//文件类型
	u8	byFileCount;		//文件数量
	s8  m_achFileName[255];	//文件名
	
public:
	tagTDownLoadPara()
	{
		byFileType = emMtFileBegin;
		byFileCount = 0;
		memset(m_achFileName, 0, sizeof(m_achFileName));
	}
	
	void SetFileType(u8 byType)	{ byFileType = byType; }
	u8	 GetFileType()			{ return byFileType; }
	u8	 GetFileCount()			{ return byFileCount; }
	
	BOOL AddFile(const s8* pszFileName)
	{
		if (!pszFileName)
		{
			return FALSE;
		}
		u8 byIndex;
		u8 byNameLen = strlen(pszFileName);
		u8 byCurBufIndex = 0;
		for (byIndex = 0; byIndex < byFileCount; ++byIndex)
		{
			byCurBufIndex += m_achFileName[byCurBufIndex];
			byCurBufIndex += sizeof(u8);
		}
		
		if ( (byCurBufIndex + byNameLen + 1) >= 255)
		{
			return FALSE;
		}
		m_achFileName[byCurBufIndex] = byNameLen;
		++byCurBufIndex;
		memcpy(&m_achFileName[byCurBufIndex], pszFileName, byNameLen);
		
		++byFileCount;
		return TRUE;
	}
	BOOL GetFileName(s8* pDestBuf, u8 byBufLen, u8 byNameIndex)
	{
		if (!pDestBuf)
		{
			return FALSE;
		}
		
		if ( byNameIndex >= byFileCount)
		{
			return FALSE;
		}
		
		u8 byIndex = 0;
		u8 byCurBufIndex = 0;
		for (byIndex = 0; byIndex < byNameIndex; ++byIndex)
		{
			byCurBufIndex += (m_achFileName[byCurBufIndex] + 1);
		}
		
		u8 byNameLen = m_achFileName[byCurBufIndex];
		if ( byNameLen + 1 > byBufLen)
		{
			return FALSE;
		}
		
		memcpy(pDestBuf, &m_achFileName[byCurBufIndex+1], byNameLen);
		pDestBuf[byCurBufIndex+byNameLen+1] = '\0' ;
		return TRUE;
	}
	
}TDownLoadPara,*PTDownLoadPara;


typedef struct tagTSecurePwd
{
	BOOL bUserCfgPwd;
	s8  achUserCfgPwd[MT_MAX_PASSWORD_LEN+1]; //是否设置配置密码
public:
	tagTSecurePwd()
	{
		bUserCfgPwd = FALSE;
		memset( achUserCfgPwd, 0, sizeof( achUserCfgPwd ) );
	}
}TSecurePwd,*PTSecurePwd;
typedef struct tagTMtBackBGDColor
{
public:
	u8 RColor;    //R背景
	u8 GColor;    //G背景
	u8 BColor;    //B背景
	u8 u8Transparency;
	tagTMtBackBGDColor()
	{
		RColor = 0;
		GColor = 0;
	    BColor = 0;
		u8Transparency = 0;
	}
}TMtBackBGDColor,*PTMtBackBGDColor;
/* SIP信息数据结构定义                                                 */
/************************************************************************/
typedef struct tagTSipCfg
{
    s8     achDisplayName[MT_MAX_NAME_LEN+1];  //别名
    s8     achUserName[MT_MAX_NAME_LEN+1];     //注册名
	s8     achPassword[MT_MAX_PASSWORD_LEN+1]; //注册密码
	s8     achHostDomain[MT_MAX_PROXYSERVER_NAME_LEN];//自身域名
	u16    wHostPort;                          //自身端口
    
	BOOL   bUseRegistrar;                      //是否Register
    u32_ip dwRegistrarIp;                      //Registrar IP
	u16    wRegistrarPort;                     //Registrar端口
    s8     achRegistrarDomain[MT_MAX_PROXYSERVER_NAME_LEN]; //Registrar域名
	u16    wExpire; 

    BOOL   bUseProxy;                          //是否启用Proxy
	u32_ip dwProxyIp;                          //Proxy IP
	u16    wProxyPort;                         //Proxy端口
	s8     achProxyDomain[MT_MAX_PROXYSERVER_NAME_LEN]; //Proxy域名
public:
	tagTSipCfg(){memset(this , 0 ,sizeof( struct tagTSipCfg) );	}
}TSipCfg,*PTSipCfg;


/************************************************************************/
/*摄像机信息数据结构定义                                               */
/************************************************************************/


/************************************************************************/
/*     矩阵配置                                                         */
/************************************************************************/

/************************************************************************/
/* 配置相关信息数据结构定义结束                                         */
/************************************************************************/



/************************************************************************/
/* 会议相关信息数据结构定义开始                                         */
/************************************************************************/


/************************************************************************/
/* 编码器统计信息                                                       */
/************************************************************************/



/************************************************************************/
/* 文件传输模块开始
/************************************************************************/






//char* GetStructVersion();

typedef struct tagTMtAddBannerParam
{
public:
	u32 dwXPos;
    u32 dwYPos;//显示区域的Y坐标
    u32 dwWidth;//显示区域的宽
    u32 dwHeight;//显示区域的高
    u32 dwBMPWight;//BMP图像宽
    u32 dwBMPHeight;//BMP图像高
    u32 dwBannerCharHeight;//字体高度－－主要用于上下滚动时，确定停顿的位置
    TMtBackBGDColor tBackBGDColor;//背景色 
    u32 dwBGDClarity;//具体颜色透明度
    u32 dwPicClarity;//整幅图片透明度
    u32 dwRunMode;//滚动模式：上下or左右or静止（宏定义如上）
    u32 dwRunSpeed;//滚动速度 四个等级（宏定义如上）
    u32 dwRunTimes;//滚动次数 0为无限制滚动
	u32 bRunForever;//无限制滚动
	u32 dwHaltTime;//停顿时间(秒)，上下滚动时，每滚完一行字的停顿间隔：0始终停留（与静止等同） 
	tagTMtAddBannerParam()
	{
		dwXPos = 0;
		dwYPos = 0;
		dwWidth = 0;
		dwHeight = 0;
		dwBMPWight = 0;
		dwBMPHeight = 0;
		dwBannerCharHeight = 0;
		dwBGDClarity = 0;
		dwPicClarity = 0;
		dwRunMode = 0;
		dwRunSpeed = 0;
		dwRunTimes = 0;
		bRunForever = 0;
		dwHaltTime = 0;
	}
}TMtAddBannerParam;
typedef struct tagTMtBmpInfo
{
public:
    u32 dwWidth;    //图片所对应的视频源制式宽度
    u32 dwHeight;  //图片所对应的视频源制式高度
//     u8 *pBMP;
//     u32 dwBmpLen;
	tagTMtBmpInfo()
	{
		dwWidth = 0;
		dwHeight = 0;
	}
}TMtBmpInfo;

typedef struct tagTMtFullBannerParam
{
public:
    TMtBmpInfo tBmpInfo[3];//576i,720p,1080p三种制式
    TMtAddBannerParam tBannerParam[3];//576i,720p,1080p三种制式
    u32 Reserver;
	tagTMtFullBannerParam()
	{
		Reserver = 0;
	}
}TMtFullBannerParam;

// Region 适应Symbol台标显示接口变化
/*
Ops: Add
Signature: liujian - 6/4/2010
Other: 台标融入码流的相关信息设置
*/
#ifndef MAX_LOGO_NAME_LEN
#define  MAX_LOGO_NAME_LEN (u8)32
#endif

typedef struct tagTMTBmpInfo
{
    u32 dwWidth;    //图片所对应的视频源制式宽度
    u32 dwHeight;  //图片所对应的视频源制式高度
}TMTBmpInfo;

typedef struct tagTMTAddLogoParam
{
    u32 dwXPos;
    u32 dwYPos;
    u32 dwLogoWidth;//logo宽
    u32 dwLogoHeight;//logo高
    TMtBackBGDColor tBackBGDColor;    
}TMTAddLogoParam;

typedef struct tagTMTFullLogoParam
{
    TMTBmpInfo tBmpInfo[3];
    TMTAddLogoParam tLogoParam[3];
}TMTFullLogoParam;
// End Region
typedef struct tagTMtcBoxCallCfg
{
	u8		byUseIndex;							//当前使用哪一个进行呼叫 0:ip  1:E164 2:别名
	u32_ip  dwIp;								//IP 地址
	s8		achE164[MT_MAX_E164NUM_LEN+1];      //E164号码
	s8		achMtAlias[MT_MAX_H323ALIAS_LEN+1]; //别名
	u16		wCallRate;							//码率
	
public:
	tagTMtcBoxCallCfg()
	{
		memset( this, 0, sizeof( tagTMtcBoxCallCfg ) );
	}
}TMtcBoxCallCfg,*PTMtcBoxCallCfg;

typedef struct tagTMTRSParam
{
    u16  m_wFirstTimeSpan;	 //第一个重传检测点(ms)
	u16  m_wSecondTimeSpan;  //第二个重传检测点(ms)
	u16  m_wThirdTimeSpan;   //第三个重传检测点(ms)
	u16  m_wRejectTimeSpan;  //过期丢弃的时间跨度(ms)
public:
	tagTMTRSParam()
	{
		m_wFirstTimeSpan = 40;
		m_wSecondTimeSpan = 2000;
		m_wThirdTimeSpan = 0;
		m_wRejectTimeSpan = 0;
	}
} TMTRSParam;

typedef struct tagTMtRecStartParam
{
public:
	
	EmSite			emSite;
	BOOL			bIsRecSecVideo;				//是否录双流
	u8				m_byPublishMode;     //发布模式//有关发布方式定义 0:不发布 1:立即发布 2:录像完毕之后发布
	s8				achFileName[MT_MAX_REC_NAME+1];//录像的文件名
public:
    tagTMtRecStartParam()
    {
        memset( this, 0, sizeof(tagTMtRecStartParam) );
    };
}TMtRecStartParam,*PTMtRecStartParam;

typedef struct tagTMtRecRegParam{
	u32_ip	  dwRecIp;
	u32_ip	  dwHostIp;
	s8        achDirName[MT_MAX_H323ALIAS_LEN + 1];
	public:
	tagTMtRecRegParam()
    {
        memset( this, 0, sizeof(tagTMtRecRegParam) );
    };
}TMtRecRegParam;

typedef struct tagTMtRecParam{
	u8					byState;//0:未连接,1:连接,2:recording,3:pause
	TMtRecRegParam		tMtRecRegParam;
	TMtRecStartParam	tMtRecStartParam;
	public:
	tagTMtRecParam()
    {
        memset( this, 0, sizeof(tagTMtRecParam) );
    };
}TMtRecParam;

typedef struct tagTMtCnsParam{
	u32_ip	dwCnsIp;
	s8		achRoomName[MT_MAX_CNS_NAME_LEN+1];
	u16		wPos;
	u16		wPosCount;	
	BOOL    bIsDual;//是否是双流源
	public:
		tagTMtCnsParam()
		{
			memset( this, 0, sizeof(tagTMtCnsParam) );
		};
}TMtCnsParam;

//MTStruct end.

typedef struct tagTLoginRet 
{
public:
	void SetRet( EmTpLoginUmsRet emRet )
	{
		m_emRet = (EmTpLoginUmsRet)htonl( emRet );
	}

	EmTpLoginUmsRet GetRet( )
	{
		return (EmTpLoginUmsRet)ntohl( m_emRet );
	}
public:
	EmTpLoginUmsRet m_emRet;
	u32		m_dwUserID;
	u32		m_dwErrorCode;
	u8      m_byNumber;  //密码输入次数
	u8      m_byLockNumber; //密码锁定次数

	tagTLoginRet()
	{
		m_emRet = tp_LoginUms_sucess;
		m_dwUserID = 0;
		m_dwErrorCode = 0;
		m_byNumber = 0;
	}
}TLoginRet;


typedef struct tagTTPTransAddr
{
public:
	u32_ip	m_dwIP;		//网络序
	u16 m_wPort;	//主机序

public:
	tagTTPTransAddr()
		:m_dwIP(0)
		,m_wPort(0)
	{
	}

	u32 GetIP()	{ return m_dwIP; }
	u16 GetPort()	{ return m_wPort; }	

	
	void SetIP(u32 dwIP)
	{
		m_dwIP = dwIP;
	}
	void SetAddr(u32 dwIP, u16 wPort)
	{
		m_dwIP = dwIP;
		m_wPort = wPort;
	}
	void Clear()
	{
		m_wPort = 0;
		m_dwIP = 0;
	}
	tagTTPTransAddr& operator = (const tagTTPTransAddr& tRhs)
	{
		if (this == &tRhs)
		{
			return *this;
		}
		this->m_dwIP = tRhs.m_dwIP;
		this->m_wPort = tRhs.m_wPort;
		return *this;
	}

	BOOL operator == (const tagTTPTransAddr& tRhs)
	{
		if ( this->m_dwIP == tRhs.m_dwIP
			&&this->m_wPort == tRhs.m_wPort )
		{
			return TRUE;
		}
		return FALSE;
	}
}TTPTransAddr, *PTTPTransAddr;


typedef struct tagTTPName
{
	s8				m_abyAlias[TP_MAX_ALIAS_LEN + 1];
	tagTTPName()
	{
		Clear();
	}
	void Clear()
	{
		m_abyAlias[0]	= '\0';
	}
	
	void SetAlias(const s8* alias)
	{
		strncpy(m_abyAlias, alias, TP_MAX_ALIAS_LEN);
		m_abyAlias[TP_MAX_ALIAS_LEN] = '\0';
	}
	BOOL32 IsEmpty()
	{
		return '\0' == m_abyAlias[0];
	}
}TTPName;

//别名定义
typedef struct tagTTPAlias
{
	EmTpAliasType	m_byType;
	s8				m_abyAlias[TP_MAX_ALIAS_LEN + 1];
	tagTTPAlias()
	{
		Clear();
	}
	void Clear()
	{
		m_byType = tp_Alias_Unknow;
		m_abyAlias[0]	= '\0';
	}
	
	BOOL32 IsInValid()
	{
		return m_byType == tp_Alias_Unknow || strlen(m_abyAlias) == 0;
	}

	void SetAlias(EmTpAliasType type, const s8* alias)
	{
		if (NULL == alias)
		{
			return;
		}
		m_byType = type;
		strncpy(m_abyAlias, alias, TP_MAX_ALIAS_LEN);
		m_abyAlias[TP_MAX_ALIAS_LEN] = '\0';
	}

	void SetAlias(const s8* alias)
	{
		if (NULL == alias)
		{
			return;
		}
		m_byType = tp_Alias_h323;
		strncpy(m_abyAlias, alias, TP_MAX_ALIAS_LEN);
		m_abyAlias[TP_MAX_ALIAS_LEN] = '\0';
	}

	BOOL32 operator == (const tagTTPAlias& tRhs)
	{
		return (0 == strcmp(m_abyAlias, tRhs.m_abyAlias));
	}

	tagTTPAlias& operator = (const tagTTPAlias& tRhs)
	{
		if (this == &tRhs)
		{
			return *this;
		}
		m_byType = tRhs.m_byType;
		strncpy(m_abyAlias, tRhs.m_abyAlias, sizeof(m_abyAlias));
		return *this;
	}
}TTPAlias, *PTTPAlias;


typedef struct tagTTpCallAddr
{
	TTPAlias	    m_tAlias;
	TTPAlias    	m_tE164;
	u32_ip		    m_dwIP;
	BOOL32          m_bAliasIP;
	EmTpAliasType	m_byCallType;
	tagTTpCallAddr()
	{
		Clear();
	}
	
	void Clear()
	{
		m_tAlias.Clear();
		m_tE164.Clear();
		m_dwIP       = 0;
		m_bAliasIP   = FALSE;
		m_byCallType = tp_Alias_Unknow;
	}
	
	tagTTpCallAddr& operator = (const tagTTpCallAddr& tRhs)
	{
		if (this == &tRhs)
		{
			return *this;
		}
		m_tAlias     = tRhs.m_tAlias;
		m_tE164      = tRhs.m_tE164;
		m_dwIP       = tRhs.m_dwIP;
		m_bAliasIP   = tRhs.m_bAliasIP;
		m_byCallType = tRhs.m_byCallType;
		return *this;
	}
	BOOL32 operator == (const tagTTpCallAddr& tRhs)
	{
		return (0 == strcmp(m_tAlias.m_abyAlias, tRhs.m_tAlias.m_abyAlias) 
				&& 0 == strcmp(m_tE164.m_abyAlias, tRhs.m_tE164.m_abyAlias) 
				&& m_dwIP == tRhs.m_dwIP && m_bAliasIP == tRhs.m_bAliasIP 
			    && m_byCallType == tRhs.m_byCallType);
	}

	TTPAlias GetValidAlias()
	{
		TTPAlias tTmp;
		if( !m_tAlias.IsInValid() )
		{
			return m_tAlias;
		}
		else if ( !m_tE164.IsInValid() )
		{
			return m_tE164;
		}
		else if( m_dwIP != 0 )
		{
			tTmp.m_byType = tp_Alias_IP;
			sprintf(tTmp.m_abyAlias, ""TPIPFORMAT"", Tpu32ToIP(m_dwIP));
		}
		return tTmp;
	}
}TTpCallAddr;

typedef struct tagTTpCallEp
{
	BOOL32		m_bAliasIP;
	TTpCallAddr	m_tCallAddr;
	u16			m_wConfID;
	tagTTpCallEp()
	{
		Clear();
	}
	
	void Clear()
	{
		m_bAliasIP = FALSE;
		m_tCallAddr.Clear();
	}
}TTpCallEp;

//加密配置信息
typedef struct tagTTpEncryptKey
{
	u8 byLen;   //密钥长度
	u8 byKey[TP_MAXLEN_ENCRYPTKEY]; //密钥
	EmTPEncryptType emTPEncryptType; //加密类型
	EmQtEncryptFrequency emQtKeyFrequency; //加密等级
public:
	tagTTpEncryptKey()
	{
		Clear();
	}
	
	void Clear()
	{
		memset(this, 0, sizeof(tagTTpEncryptKey));
		emTPEncryptType = emTPEncryptTypeNone;
		emQtKeyFrequency = emQtFrequencyEverySeconds;
	}
}TTpEncryptKey,*PTTpEncryptKey;

//量子加密服务器配置信息
typedef struct tagTTpQtEncryptCfg
{
	BOOL    m_bOpen;
	u32_ip  m_dwQtIP;
	u32     m_dwQtID;
public:
	tagTTpQtEncryptCfg()
	{
		Clear();
	}
	
	void Clear()
	{
		memset(this, 0, sizeof(tagTTpQtEncryptCfg));
	}

}TTpQtEncryptCfg,*PTTpQtEncryptCfg;

//量子加密秘钥
typedef struct tagTTpQtEncryptKey
{
    u32 m_dwMediaHandl;
	u32 m_dwKeyLen;    
	u8  m_byMediaKey1[QT_MAX_MEDIA_KEY/4+1];
	u8  m_byMediaKey2[QT_MAX_MEDIA_KEY/4+1];
	u8  m_byMediaKey3[QT_MAX_MEDIA_KEY/4+1];
	u8  m_byMediaKey4[QT_MAX_MEDIA_KEY/4+1];
	EmQtEncryptFrequency m_emQtKeyFrequency;
	u32 m_dwQtFlag;
	u16 m_wConverIndex;
public:
	tagTTpQtEncryptKey()
	{
		Clear();
	}
	
	void Clear()
	{
		memset(this, 0, sizeof(tagTTpQtEncryptKey));

	}
	
}TTpQtEncryptKey,*PTTpQtEncryptKey;

typedef struct tagTTPMediaTransAddr
{
	TTPTransAddr m_tRtpAddr;
	TTPTransAddr m_tRtcpAddr;	
	TTPTransAddr m_tBackRtcpAddr;
	tagTTPMediaTransAddr()
	{
	}

	tagTTPMediaTransAddr(tagTTPMediaTransAddr& tAddr)
	{
		m_tRtpAddr = tAddr.m_tRtpAddr;
		m_tRtcpAddr = tAddr.m_tRtcpAddr;
		m_tBackRtcpAddr = tAddr.m_tBackRtcpAddr;
	}

	tagTTPMediaTransAddr& operator=(const tagTTPMediaTransAddr& tAddr)
	{
		if (this != &tAddr)
		{
			m_tRtpAddr = tAddr.m_tRtpAddr;
			m_tRtcpAddr = tAddr.m_tRtcpAddr;
			m_tBackRtcpAddr = tAddr.m_tBackRtcpAddr;
		}

		return *this;
	}

	bool operator==(const tagTTPMediaTransAddr& tAddr)
	{
		return	m_tRtpAddr == tAddr.m_tRtpAddr &&
				m_tRtcpAddr == tAddr.m_tRtcpAddr &&
				m_tBackRtcpAddr == tAddr.m_tBackRtcpAddr;
	}

	void Clear()
	{
		m_tRtpAddr.Clear();
		m_tRtcpAddr.Clear();
		m_tBackRtcpAddr.Clear();
	}
	void SetIP(u32 dwIP)
	{
		m_tRtpAddr.SetIP(dwIP);
		m_tRtcpAddr.SetIP(dwIP);
		m_tBackRtcpAddr.SetIP(dwIP);
	}


}TTPMediaTransAddr;

typedef struct tagTTPVideoCap
{
	EmTpVideoFormat			m_emFormat;
	EmTpVideoResolution		m_emRes;
	u16		m_byMaxFrameRate;				//最大帧率
	u16             m_wBitrate;

	TTpEncryptKey m_tEnc;

	u16     m_wStaticPayload;				
	u16     m_wDynamicPayload;

	EmTpVideoQualityLevel emTpVideoQualityLevel; //HP,BP

	tagTTPVideoCap()
	{
		m_emFormat = emTPVH264;
		m_emRes = emTPVHD1080p1920x1080;
		m_byMaxFrameRate = 50;

		m_wStaticPayload = MEDIA_TYPE_H264;
		m_wDynamicPayload = MEDIA_TYPE_H264;
		
		emTpVideoQualityLevel = emTPH264HP;
	}
	void Clear()
	{
		m_emFormat = emTPVH264;
		m_emRes = emTPVHD1080p1920x1080;
		m_byMaxFrameRate = 50;
		
		memset( &m_tEnc, 0, sizeof(m_tEnc) );

		m_wStaticPayload = MEDIA_TYPE_H264;
		m_wDynamicPayload = MEDIA_TYPE_H264;
		
		emTpVideoQualityLevel = emTPH264HP;
	}
}TTPVideoCap, *PTTPVideoCap;


typedef struct tagTTPAudCap
{
	EmTpAudioFormat		m_emFormat;
	u16     m_wStaticPayload;				
	u16     m_wDynamicPayload;

	u16             m_wBitrate;

	TTpEncryptKey m_tEnc;

	tagTTPAudCap()
	{
		m_emFormat = emTPAMpegAACLD;
	}

	void Clear()
	{
		m_emFormat = emTPAMpegAACLD;
		m_wStaticPayload = MEDIA_TYPE_AACLD;
		m_wDynamicPayload = MEDIA_TYPE_AACLD;
		
		memset( &m_tEnc, 0, sizeof(m_tEnc) );	
	}
}TTPAudCap, *PTTPAudCap;

//会议视频格式
typedef struct tagTUmsVidFormat
{
	EmTpVideoFormat		  m_emFormat; //视频格式
	EmTpVideoResolution	  m_emRes;    //视频分辨率
	u16					  m_wFrameRate;	//帧率
	u16					  m_wBitrate;       //视频码率
	EmTpVideoQualityLevel m_emQualityLvl;  //H.264画质级别

	tagTUmsVidFormat()
	{
		Clear();
	}
	void Clear()
	{
		m_emFormat = emTPVH264;
		m_emRes = emTPVHD1080p1920x1080;
		m_wFrameRate = 60;
		m_wBitrate = 3072;
		m_emQualityLvl = emTPH264HP;
	}

	tagTUmsVidFormat& operator=(const tagTUmsVidFormat& tInfo)
	{
		if (this == &tInfo)
		{
			return *this;
		}
		
		m_emFormat = tInfo.m_emFormat;
		m_emQualityLvl = tInfo.m_emQualityLvl;
		m_emRes = tInfo.m_emRes;
		m_wBitrate = tInfo.m_wBitrate;
		m_wFrameRate = tInfo.m_wFrameRate;
		
		return *this;
	}
	BOOL32 IsValid() const	{ return emTPVResEnd != m_emRes; }
}TUmsVidFormat;

//重传设定
typedef struct tagTUmsRSParam
{
    u16  m_wFirstTimeSpan;	 //第一个重传检测点(ms)
	u16  m_wSecondTimeSpan;  //第二个重传检测点(ms)
	u16  m_wThirdTimeSpan;   //第三个重传检测点(ms)
	u16  m_wRejectTimeSpan;  //过期丢弃的时间跨度(ms)

	tagTUmsRSParam()
	{
		m_wFirstTimeSpan = 40;
		m_wSecondTimeSpan = 80;
		m_wThirdTimeSpan = 120;
		m_wRejectTimeSpan = 2000;
	}
}TUmsRSParam;


//ConfEp : 
typedef struct tagTEpAddr
{
// 	TTPAlias	m_tEpAddr.m_tAlias;//别名
// 	TTPAlias	m_tEpAddr.m_tE164;//E164
// 	u32_ip		m_tEpAddr.m_dwIP;//IP

	TTpCallAddr m_tEpAddr;
	u16			m_wEpID;
	tagTEpAddr()
	{
		m_tEpAddr.Clear();
		m_wEpID = TP_INVALID_INDEX;
	}
}TEpAddr, *PTEpAddr;

//混音列表
typedef struct tagTAuxMixList
{
	//u16 m_wSpeakerIndex;					//下面数组的索引 注：b4没有用到
	u16	m_awList[TP_CONF_MAX_AUDMIXNUM];	//混音ID
	
	BOOL32 m_bAudMixOn;                     //讨论开关，默认关闭
	BOOL32 m_bVacOn;                        //语音激励开关 注：b4新增

	tagTAuxMixList()
	{
		Clear();
	}
	
	BOOL32 operator == (const tagTAuxMixList& tRhs)
	{
		/*if (m_wSpeakerIndex != tRhs.m_wSpeakerIndex)
		{
			return FALSE;
		}*/
		for (u16 wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; ++wIndex)
		{
			if (m_awList[wIndex] != tRhs.m_awList[wIndex])
			{
				return FALSE;
			}
		}
		return TRUE;
	}

	void Clear()
	{
		//m_wSpeakerIndex = TP_INVALID_INDEX;
		for (u16 wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; ++wIndex)
		{
			m_awList[wIndex] = TP_INVALID_INDEX;
		}
		m_bAudMixOn = FALSE;
		m_bVacOn = FALSE;
	}
	/*BOOL32 SetSpeakerIndex(u16 wSpeakerIndex)
	{
		if (wSpeakerIndex >= TP_CONF_MAX_AUDMIXNUM)
		{
			return FALSE;
		}
		
		//发言人设置，则采用此设置
		if (TP_VALID_HANDLE(m_awList[wSpeakerIndex]))
		{
			m_wSpeakerIndex = wSpeakerIndex;
			return TRUE;
		}
		
		//如果没有发言人，则默认取第一个
		for (u16 wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; ++wIndex)
		{
			if (TP_VALID_HANDLE(m_awList[wIndex]))
			{
				m_wSpeakerIndex = wIndex;
				return TRUE;
			}
		}
		return FALSE;
	}*/

	BOOL32 AddMixID(u16 wEpID)
	{		
		u16 wIndex = 0;
		for (wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; ++wIndex)
		{
			if (m_awList[wIndex] == wEpID)
			{
				return FALSE;
			}
		}
		for (wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; ++wIndex)
		{
			if (!TP_VALID_HANDLE(m_awList[wIndex]))
			{
				m_awList[wIndex] = wEpID;
				return TRUE;
			}
		}
		return FALSE;
	}
	
	void DelMixId(u16 wEpId)
	{
		u16 wIndex = 0;
		u16 wDelIndex = TP_INVALID_INDEX;
		for (wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; ++wIndex)
		{
			if (m_awList[wIndex] == wEpId)
			{
				m_awList[wIndex] = TP_INVALID_INDEX;
				wDelIndex = wIndex;
				break;
			}
		}

		if (TP_VALID_HANDLE(wDelIndex))
		{
			for (wIndex = wDelIndex+1; wIndex < TP_CONF_MAX_AUDMIXNUM; ++wIndex)
			{
				if (TP_VALID_HANDLE(m_awList[wIndex]))
				{
					m_awList[wIndex-1] = m_awList[wIndex];
					m_awList[wIndex] = TP_INVALID_INDEX;
					continue;
				}
				break;
			}
		}
		return;
	}

	u16 GetMixNum() const
	{
		u16 wMixNum = 0;
		for (u16 wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; ++wIndex)
		{
			if (!TP_VALID_HANDLE(m_awList[wIndex]))
			{
				continue;
			}
			wMixNum++;
		}
		return wMixNum;
	}
	
	BOOL32 IsValid() const
	{
		if (GetMixNum() < 1)
		{
			return FALSE;
		}
		/*if (m_wSpeakerIndex >= TP_CONF_MAX_AUDMIXNUM)
		{
			return FALSE;
		}

		if (!TP_VALID_HANDLE(m_awList[m_wSpeakerIndex]))
		{
			return FALSE;
		}*/
		return TRUE;
	}

	u16 FindIndexByEp(u16 wEpID) const
	{
		for (u16 wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; ++wIndex)
		{
			if (m_awList[wIndex] == wEpID)
			{
				return wIndex;
			}
		}
		return TP_INVALID_INDEX;
	}
	/*u16 GetSpeakerEpID( u16 wSpeaker = TP_INVALID_INDEX ) const
	{
		if (TP_VALID_HANDLE(m_wSpeakerIndex) && TP_VALID_HANDLE(m_awList[m_wSpeakerIndex]))
		{
			return m_awList[m_wSpeakerIndex];
		}
		u16 wIndex = 0;
		//先查找当前发言人是否在讨论中
		for ( wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; ++wIndex)
		{
			if (m_awList[wIndex] == wSpeaker)
			{
				return wSpeaker;
			}
		}

		for ( wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; ++wIndex)
		{
			if (TP_VALID_HANDLE(wIndex) && TP_VALID_HANDLE(m_awList[wIndex]))
			{
				return m_awList[wIndex];
			}
		}
		
		return TP_INVALID_INDEX;
	}
	BOOL32 SetSpeakerEpID(u16 wEpID) 
	{
		m_wSpeakerIndex = TP_INVALID_INDEX;
		u16 wSpeakerIndex = FindIndexByEp(wEpID);
		if (!TP_VALID_HANDLE(wSpeakerIndex))
		{
			for (u16 wIndex = 0; wIndex < TP_CONF_MAX_AUDMIXNUM; ++wIndex)
			{
				if (TP_VALID_HANDLE(m_awList[wIndex]))
				{
					wSpeakerIndex = wIndex;
					break;
				}
			}
		}
		if (!TP_VALID_HANDLE(wSpeakerIndex))
		{
			return FALSE;
		}
		
		return SetSpeakerIndex(wSpeakerIndex);
	}*/
}TAuxMixList, *PTAuxMixList;

//会议混音列表
typedef struct tagTConfAuxMixVacOpr
{
	u16			m_wConfID;
	BOOL32      m_bVacOn;

	u16         m_wOprRet; // TP_RET_ERROR 和TP_RET_OK

	tagTConfAuxMixVacOpr()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_wOprRet = TP_RET_ERROR;
		m_bVacOn = FALSE;
	}
}TConfAuxMixVacOpr;

typedef struct tagTConfAuxMixInfo
{
	u16			m_wConfID;
	BOOL32		m_bStart;
	BOOL32      m_bVacOn;
	TAuxMixList	m_atAuxMixList;
	EmDiscussRspRet m_emRet;  // 开启讨论的结果，用于ind消息

	tagTConfAuxMixInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_bStart = FALSE;
		m_bVacOn = FALSE;
		m_atAuxMixList.Clear();
		m_emRet = em_DiscussOprRsp_End;
	}

}TConfAuxMixInfo;

typedef struct tagTTPPollInfo
{
	BOOL bIsPoll;
	u16  wPollExpire;
	
	tagTTPPollInfo()
	{
		memset( this, 0, sizeof(struct tagTTPPollInfo) );
	}
}TTPPollInfo;

//基本会议信息
typedef struct tagTTPConfBaseInfo
{
	s8	 achConfId[TP_MAX_CONF_ID_LEN + 1 ];			// 会议ID
	s8	 achConfName[TP_MAX_NAME_LEN + 1 ];		// 会议名
	s8	 achConfNumber[ TP_MAX_CONF_E164_LEN + 1 ];	    // 会议号码
	s8	 achConfPwd[ TP_MAXLEN_PASSWORD + 1 ];			// 会议密码
	BOOL32 bNeedPassword;                         //是否需要密码
	u16  wConfDuration;							// 会议持续时间		
	EmTpVideoFormat   emTpVideoFormat;							// 会议视频格式(VIDEO_H261等)
	EmTpAudioFormat   emTpAudioFormat;							// 会议音频格式(AUDIO_MP3等)
	EmTpVideoResolution  emTpResolution;							// 会议视频分辨率(VIDEO_CIF等)
	BOOL32  bIsAutoVMP;								// 是否自动画面合成
	BOOL32  bIsMix;	    							// 是否混音
	u8				  bySecVideoFormat;				// 双流格式
	EmTpVideoResolution emTpSecVidRes;					// 双流分辨率
	u8				  bySecVidFps;					// 双流帧率
	//Add by tanxiaodong 2013-06-21.
	EmTpVideoQualityLevel emPriVideoQualityLevel;  // 主流profile
	EmTpVideoQualityLevel emDualVideoQualityLevel;  // 双流profile
    u8 byPriVidFps;									// 主流帧率
	//End to add.
	u16			 wCallRate;			        // 呼叫码率(kbps)
	u16			 wDualCallRate;			    // 双流码率(kbps)
	TTPPollInfo  tPollInfo;
	TConfAuxMixInfo tConfAudMixInfo;
	
public:
	tagTTPConfBaseInfo(){ memset( this ,0 ,sizeof( struct tagTTPConfBaseInfo ) );	}
	void Clear(){ memset( this ,0 ,sizeof( struct tagTTPConfBaseInfo ) );};
}TTPConfBaseInfo ,*PTTPConfBaseInfo;

typedef struct tagTUmsAudFormat
{
	EmTpAudioFormat		m_emFormat;
	EmTPAACSampleFreq	m_emSampleFreq;
    EmTPAACChnlCfg		m_emChnlCfg;
	u8					m_byReserve1;
	u8					m_byReserve2;
	
	tagTUmsAudFormat()
	{
		Clear();
	}
	void Clear()	
	{
		memset(this, 0, sizeof(tagTUmsAudFormat));
		
		m_emFormat = emTPAMpegAACLD;
		m_emSampleFreq = emTPFs32000;
		m_emChnlCfg = emTPChnl1;
	}
}TUmsAudFormat;


//TP加密参数 by ywd
typedef struct tagTTPEncrypt
{
	EmTPEncryptType	m_emEncryptModel;		//加密模式: none, aes, des
    u8				m_byKeyLen;		//加密key的长度
	s8				m_achEncKey[TP_ENCRYPT_KEY_LEN+1]; //加密key

	tagTTPEncrypt()
	{
		Clear();
	}

	tagTTPEncrypt(const tagTTPEncrypt& tInfo)
	{
		Copy(tInfo);
	}

	tagTTPEncrypt& operator=(const tagTTPEncrypt& tInfo)
	{
		if (&tInfo != this)
		{
			Copy(tInfo);
		}

		return *this;
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTTPEncrypt));
	}

private:
	void Copy(const tagTTPEncrypt& tInfo)
	{
		m_emEncryptModel = tInfo.m_emEncryptModel;
		m_byKeyLen = tInfo.m_byKeyLen;
		memcpy(m_achEncKey, tInfo.m_achEncKey, TP_ENCRYPT_KEY_LEN + 1);
	}
	
}TTPEncrypt;

typedef struct tagTTPVmpCfgChnl
{
    u16         m_wScrIndx;
    TTPAlias    m_tEpAlias;
    tagTTPVmpCfgChnl()
    {
        Clear();
    }
	
    void Clear()
    {
        m_wScrIndx = 0;
        m_tEpAlias.Clear();
    }
}TTPVmpCfgChnl;

typedef struct tagTTpVmpMemberCfg
{
	u16			    m_wConfID;
	EMVmpStyle	    m_emStyle;
	u16			    m_wFlag;
	u16			    m_wTotalNum;
	u16			    m_wEpNum;
	u16			    m_wSpeakerIndx;		   //发言人跟随索引
	u16			    m_wDualIndx;		   //双流跟随索引
	BOOL32          m_bFirst;              //是否第一包 
	TTPVmpCfgChnl   m_atEpList[TP_REFRESH_LIST_EIGHT];
	tagTTpVmpMemberCfg()
	{
		Clear();
	}
	tagTTpVmpMemberCfg& operator = (const tagTTpVmpMemberCfg& tRhs)
	{
		if(this == &tRhs)
			return *this;
		m_wConfID = tRhs.m_wConfID;
		m_emStyle = tRhs.m_emStyle;
		m_wFlag = tRhs.m_wFlag;
		m_wEpNum = tRhs.m_wEpNum;
		m_wTotalNum = tRhs.m_wTotalNum;
		m_wSpeakerIndx = tRhs.m_wSpeakerIndx;
		m_wDualIndx = tRhs.m_wDualIndx;
		m_bFirst = tRhs.m_bFirst;
		for (u16 wIndex = 0 ; wIndex < TP_REFRESH_LIST_EIGHT ; ++wIndex)
		{
			m_atEpList[wIndex] = tRhs.m_atEpList[wIndex];
		}
		return *this;
	}

	void Clear()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_wFlag = TP_INVALID_INDEX;
		m_emStyle = tp_VmpStyle_DYNAMIC;
		m_wEpNum = 0;
		m_wTotalNum = 0;
		m_wSpeakerIndx = TP_INVALID_INDEX;
		m_wDualIndx = TP_INVALID_INDEX;
		m_bFirst = FALSE;
		
		for ( u16 wIndex = 0; wIndex < TP_REFRESH_LIST_EIGHT; wIndex ++ )
		{
			m_atEpList[wIndex].Clear();
		}
	}
}TTpVmpMemberCfg;

typedef struct tagTSaveVmpCfg
{
	EMVmpStyle			m_emStyle;
	u16					m_wEpNum;
	TTPAlias			m_atEpList[TP_VMP_MAX_IN_CHN_NUM];
	
	tagTSaveVmpCfg()
	{
		Clear();
	}
	tagTSaveVmpCfg& operator = (const tagTSaveVmpCfg& tRhs)
	{
		if(this == &tRhs)
			return *this;
		m_emStyle = tRhs.m_emStyle;
		m_wEpNum = tRhs.m_wEpNum;
		for (u16 wIndex = 0 ; wIndex < TP_VMP_MAX_IN_CHN_NUM ; ++wIndex)
		{
			m_atEpList[wIndex] = tRhs.m_atEpList[wIndex];
		}
		return *this;
	}
	void Clear()
	{
		m_emStyle = tp_VmpStyle_DYNAMIC;
		m_wEpNum = 0;
		for ( u16 wIndex = 0; wIndex < TP_VMP_MAX_IN_CHN_NUM; wIndex ++)
		{
			m_atEpList[wIndex].Clear();
		}
	}
}TSaveVmpCfg;


//会议基本信息
typedef struct tagTUmsConfBase
{
	s8  m_achConfName[TP_MAX_ALIAS_LEN+1];	//会议名称
	s8  m_achConfE164[TP_MAX_ALIAS_LEN+1];	//会议e164
	u16	m_wConfBitRate;						//会议码率(HP码率)
	u16	m_wBpConfBitRate;					//会议码率(BP码率)
	u16 m_wHpDualBitRate;					//双流码率(HP码率)
	u16 m_wBpDualBitRate;					//双流码率(BP码流)
	u32	m_dwPersistenceTime;				//会议持续时间，单位为秒，为0表示手动结束
	time_t m_tStartTime;					//会议开始时间, 为0表示手动开始
	
	u16 m_wAudFmtNum;  //音频数量
	TUmsAudFormat		m_atAudFmt[TP_CONF_MAX_AUD_FMT_NUM];
//	EmTpAudioFormat		m_emTpAudioFormat;					// 主会议音频格式(AUDIO_MP3等)

	TUmsRSParam m_tRsParam;						//重传参数
	
	u16	m_wDefaultChairMan;						//默认主席	

	u16 m_wMainNum;  //主格式数量
	TUmsVidFormat m_atTpMainVideoRes[TP_CONF_MAX_MAIN_VIDEO_RES_NUM];  //会议主视频分辨率
	u16 m_wMinorNum; //双流格式数量
	TUmsVidFormat m_atTpMinorVideoRes[TP_CONF_MAX_MINOR_VIDEO_RES_NUM]; //会议辅视频分辨率

	u16  m_wUpBandWid;
	u16  m_wDownBandWid;

	TTPEncrypt		m_tEncrypt;					//模板加密信息

 	TSaveVmpCfg     m_tVmpPlanCfg;			//画面合成信息 

	tagTUmsConfBase()
	{
		Clear();
	}
	
	tagTUmsConfBase& operator = (const tagTUmsConfBase& tRhs)
	{
		if(this == &tRhs)
			return *this;
		
		memcpy(m_achConfName, tRhs.m_achConfName, TP_MAX_ALIAS_LEN+1);
		memcpy(m_achConfE164, tRhs.m_achConfE164, TP_MAX_ALIAS_LEN+1);

		m_wConfBitRate = tRhs.m_wConfBitRate;
		m_wBpConfBitRate = tRhs.m_wBpConfBitRate;
		m_wHpDualBitRate = tRhs.m_wHpDualBitRate;
		m_wBpDualBitRate = tRhs.m_wBpDualBitRate;
		m_dwPersistenceTime = tRhs.m_dwPersistenceTime;
		m_tStartTime = tRhs.m_tStartTime;

	//	m_emTpAudioFormat = tRhs.m_emTpAudioFormat;

		memcpy(&m_tRsParam, &tRhs.m_tRsParam, sizeof(m_tRsParam));
		m_tEncrypt = tRhs.m_tEncrypt;


		m_wDefaultChairMan = tRhs.m_wDefaultChairMan;	

		m_wMainNum = tRhs.m_wMainNum;
		m_wMinorNum = tRhs.m_wMinorNum;
		memcpy(m_atTpMainVideoRes, tRhs.m_atTpMainVideoRes, sizeof(m_atTpMainVideoRes));
		memcpy(m_atTpMinorVideoRes, tRhs.m_atTpMinorVideoRes, sizeof(m_atTpMinorVideoRes));

		m_wAudFmtNum = tRhs.m_wAudFmtNum;
		memcpy(m_atAudFmt, tRhs.m_atAudFmt, sizeof(m_atAudFmt));

		m_wUpBandWid = tRhs.m_wUpBandWid;
		m_wDownBandWid = tRhs.m_wDownBandWid;
    	memcpy(&m_tVmpPlanCfg, &tRhs.m_tVmpPlanCfg, sizeof(m_tVmpPlanCfg));
 
		return *this;
	}
	
	void Clear()
	{
		m_wConfBitRate = CONF_HP_BITRATE;		//默认值全部改成2M
		m_wBpConfBitRate = CONF_HP_BITRATE;
		m_wHpDualBitRate = CONF_HP_BITRATE;
		m_wBpDualBitRate = CONF_HP_BITRATE;
		m_dwPersistenceTime = 0;
		m_tStartTime = 0;
		m_tEncrypt.Clear();
		m_tEncrypt.m_emEncryptModel = emTPEncryptTypeNone;		
	//	m_emTpAudioFormat = emTPAMpegAACLD;

		m_wDefaultChairMan = 0;
		
		m_achConfName[0] = '\0';
		m_achConfE164[0] = '\0';
		m_wMainNum = 1;
		m_wMinorNum = 1;
		m_wAudFmtNum = 1;

		m_wUpBandWid = 0;
		m_wDownBandWid = 0;
		m_tVmpPlanCfg.Clear();
		u16 wIndex = 0;
		for (wIndex = 0; wIndex < TP_CONF_MAX_MAIN_VIDEO_RES_NUM; ++wIndex)
		{
			m_atTpMainVideoRes[wIndex].Clear();
		}

		for (wIndex = 0; wIndex < TP_CONF_MAX_MINOR_VIDEO_RES_NUM; ++wIndex)
		{
			m_atTpMinorVideoRes[wIndex].Clear();
		}

		for (wIndex = 0; wIndex < TP_CONF_MAX_AUD_FMT_NUM; ++wIndex)
		{
			m_atAudFmt[wIndex].Clear();
			m_atAudFmt[wIndex].m_emFormat = emTPAEnd;
		}
 		m_atAudFmt[0].m_emFormat = emTPAMpegAACLD;
 
// 		m_atAudFmt[1].m_emFormat = emTPAMpegAACLC;
// 		m_atAudFmt[2].m_emFormat = emTPAG719;
// 		m_atAudFmt[3].m_emFormat = emTPAG7221;
	}
	
}TUmsConfBase;


//上级会议信息
typedef struct tagTChairConfInfo
{
	u16			m_wConfID;
	u32		    m_dwBeginTime;		//会议开始时间  平台不同time_t类型替换成u32
	TTPAlias	m_tConfName;		//会议名称
	TTPAlias	m_tChairName;		//主席名称
	tagTChairConfInfo()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_dwBeginTime = 0;
	}
	void Clear()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_dwBeginTime = 0;
		m_tConfName.Clear();
		m_tChairName.Clear();
	}
}TChairConfInfo;

//会场列表
typedef struct tagTEpAddrList
{
	u16	m_wNum;	
	TEpAddr	m_tCnsList[TP_CONF_MAX_EPNUM];		//与会端点
	tagTEpAddrList()
	{
		m_wNum = 0;
	}

	BOOL32 IsRepeat(TTpCallAddr tCallAddr)
	{
		for (u16 wIndex = 0; wIndex < m_wNum; ++wIndex)
		{
			if (tCallAddr.m_bAliasIP)
			{
				if (tCallAddr.m_dwIP == m_tCnsList[wIndex].m_tEpAddr.m_dwIP && 
					tCallAddr.m_tAlias == m_tCnsList[wIndex].m_tEpAddr.m_tAlias)
				{
					return TRUE;		
				}
			}
			else
			{
				if (tCallAddr.m_dwIP == m_tCnsList[wIndex].m_tEpAddr.m_dwIP && 
					tCallAddr.m_tE164 == m_tCnsList[wIndex].m_tEpAddr.m_tE164 &&
					tCallAddr.m_tAlias == m_tCnsList[wIndex].m_tEpAddr.m_tAlias)
				{
					return TRUE;
				}
			}
		
		}
		return FALSE;
	}

	EmConfAddEpRet Add(TTpCallAddr tCallAddr)
	{//新添加的会场既有323别名又有164号别名
		
		if (NULL == tCallAddr.m_tAlias.m_abyAlias && NULL == tCallAddr.m_tE164.m_abyAlias && 0 == tCallAddr.m_dwIP)
		{
			return TP_ConfAddEpRet_ParamError;
		}

		if (m_wNum >= TP_CONF_MAX_EPNUM)
		{
			return TP_ConfAddEpRet_MaxNum;
		}

		if (IsRepeat(tCallAddr))
		{
			return TP_ConfAddEpRet_AliasReapeat;
		}
		m_tCnsList[m_wNum].m_wEpID = m_wNum;
		m_tCnsList[m_wNum].m_tEpAddr.m_tAlias.SetAlias(tp_Alias_h323, tCallAddr.m_tAlias.m_abyAlias);
		m_tCnsList[m_wNum].m_tEpAddr.m_tE164.SetAlias(tp_Alias_e164, tCallAddr.m_tE164.m_abyAlias);
		m_tCnsList[m_wNum].m_tEpAddr.m_dwIP = tCallAddr.m_dwIP;

		++m_wNum;
		return TP_ConfAddEpRet_Success;
	}

// 	EmConfAddEpRet Add(EmTpAliasType emType, s8* pszEpAlias)
// 	{//新添加，只能加一个名字，323别名或者164别名
// 		if (pszEpAlias ==NULL)
// 		{
// 			return TP_ConfAddEpRet_ParamError;
// 		}
// 		if (m_wNum >= TP_CONF_MAX_EPNUM)
// 		{
// 			return TP_ConfAddEpRet_MaxNum;
// 		}
// 		
// 		if (emType != tp_Alias_h323 && emType != tp_Alias_e164)
// 		{
// 			return TP_ConfAddEpRet_ParamError;
// 		}
// 		
// 		if (IsRepeat(emType, pszEpAlias))
// 		{
// 			return TP_ConfAddEpRet_AliasReapeat;
// 		}
// 		
// 		m_tCnsList[m_wNum].m_wEpID = m_wNum;
// 		
// 		if (emType == tp_Alias_h323)
// 		{
// 			m_tCnsList[m_wNum].m_tAlias.SetAlias(emType, pszEpAlias);
// 		}
// 		else
// 		{
// 			m_tCnsList[m_wNum].m_tE164.SetAlias(emType, pszEpAlias);
// 		}
// 		++m_wNum;
// 		
// 		return TP_ConfAddEpRet_Success;
// 	}
// 	
	TEpAddr* FindEp(TTpCallAddr& tCallAddr)
	{
		for (u16 wIndex = 0; wIndex < m_wNum; ++wIndex)
		{
			if (tCallAddr.m_bAliasIP)
			{
				if (tCallAddr.m_dwIP == m_tCnsList[wIndex].m_tEpAddr.m_dwIP && 
					tCallAddr.m_tAlias == m_tCnsList[wIndex].m_tEpAddr.m_tAlias)
				{
					return &m_tCnsList[wIndex];			
				}
			}
			else
			{
				if (tCallAddr.m_dwIP == m_tCnsList[wIndex].m_tEpAddr.m_dwIP && 
					tCallAddr.m_tE164 == m_tCnsList[wIndex].m_tEpAddr.m_tE164 && 
					tCallAddr.m_tAlias == m_tCnsList[wIndex].m_tEpAddr.m_tAlias)
				{
					return &m_tCnsList[wIndex];			
				}	
			}
		}
		return NULL;
	}

}TEpAddrList, *PTEpAddrList;


//轮询列表
typedef struct tagTConfTurnList
{
	u16 m_wInterval;					//轮询间隔，单位秒
	u16	m_wNum;							//参与轮询数量
	BOOL32 m_bPollOn;                    //轮询开关状态，默认开启
	u16	m_awList[TP_CONF_MAX_TURNNUM];
	tagTConfTurnList()
	{
		Clear();
	}
	void SetInterval(u16 interval)	
	{
		if (interval < TP_CONF_TURN_MIN_INTERVAL)
		{
			interval = TP_CONF_TURN_MIN_INTERVAL;
		}
		m_wInterval = interval; 
	}
	void Clear()
	{
		m_wInterval = 20;
		m_wNum = 0;
		m_bPollOn = TRUE;
		for (u16 wIndex = 0; wIndex < TP_CONF_MAX_TURNNUM; wIndex++)
		{
			m_awList[wIndex] = TP_INVALID_INDEX;
		}
	}
}TConfTurnList, *PTConfTurnList;



typedef struct tagTTpVmpMemberCfgInd
{
	u16			m_wConfID;
	u16			m_wFlag;
	BOOL32		m_bRet;
	tagTTpVmpMemberCfgInd()
	{
		Clear();
	}
	void Clear()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_wFlag = TP_INVALID_INDEX;
		m_bRet = TRUE;
	}
}TTpVmpMemberCfgInd;

//ConfTemplate : 会议模板
typedef struct tagTTPConfTemplate : public TUmsConfBase
{
	u16				m_wID;					//模板ID
	u32				m_dwTimeID;				//模板计时器指针
	TEpAddrList		m_atEpList;
	TAuxMixList		m_atAuxMixList;
	TConfTurnList	m_tTurnList;

	tagTTPConfTemplate()
	{
		m_wID = TP_INVALID_INDEX;
		m_dwTimeID = 0;
	}

	tagTTPConfTemplate& operator = (const tagTTPConfTemplate& tRhs)
	{
		if(this == &tRhs)
            return *this;
        m_wID = tRhs.m_wID;
		m_dwTimeID = tRhs.m_dwTimeID;
		memcpy(&m_atEpList, &tRhs.m_atEpList, sizeof(m_atEpList));
		memcpy(&m_atAuxMixList, &tRhs.m_atAuxMixList, sizeof(m_atAuxMixList));
		memcpy(&m_tTurnList, &tRhs.m_tTurnList, sizeof(m_tTurnList));
         
		TUmsConfBase::operator = (tRhs);
		//static_cast<TTPConfBaseInfo&>(*this) = tRhs;
		return *this;
	}

	BOOL32 Invalid()	{ return !TP_VALID_HANDLE(m_wID); }
	BOOL32 operator == (const tagTTPConfTemplate& tRhs)
	{	
		return m_wID == tRhs.m_wID;
	}

	void Clear()
	{
		m_dwTimeID = 0;
		memset(&m_atEpList, 0, sizeof(m_atEpList));
		m_atAuxMixList.Clear();
		m_tTurnList.Clear();
		TUmsConfBase::Clear();
	}
	
}TTPConfTemplate;


//会议模板操作结果
typedef struct tagTOprConfTmpResult
{
	u16					m_wID;
	EmTpConfTemplateRet m_emReason;
	tagTOprConfTmpResult()
	{
		m_emReason = TP_ConfTemplate_UnKonw;
	}
}TOprConfTmpResult, *PTOprConfTmpResult;


//删除会议模板
typedef struct tagTDelRefreshConfTemplate
{
	u16 m_wRefreshNum;
	u16	m_awTmpList[TP_REFRESH_LIST_THREE];
	tagTDelRefreshConfTemplate()
	{
		m_wRefreshNum = 0;
	}
}TDelRefreshConfTemplate;

//ConfEpID : 
typedef struct tagTConfEpID
{
	u16	m_wConfID;
	u16	m_wEpID;
	tagTConfEpID()
	{
		Clear();
	}
	void Clear()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_wEpID = TP_INVALID_INDEX;
	}
}TConfEpID;


typedef struct tagTConfEpIDInfo
{
	u16	m_wConfID;
	u16	m_wEpID;
	TTPAlias	m_tAlias;
	tagTConfEpIDInfo()
	{
		Clear();
	}
	void Clear()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_wEpID = TP_INVALID_INDEX;
	}
}TConfEpIDInfo;

//会议中呼叫EP : 
typedef struct tagTConfCallEpAddr
{
	u16	m_wConfID;
	TTpCallAddr	m_tCallAddr;
	tagTConfCallEpAddr()
	{
		m_wConfID = TP_INVALID_INDEX;
	}
}TConfCallEpAddr;


//RoomInfo : CNS
typedef struct tagTCnsInfo
{
	u16	m_wEpID;							//会场ID
	u16	m_wParentEpID;						//父会场ID
	u16 m_wChildEpID;
	u16 m_wBrotherEpID;

	EmTPEndpointType m_emEpType;			//结点类型
	TTPAlias m_tCalledAddr;

	BOOL32	m_bOnline;			//在线状态
	EmCnsCallReason m_emCallReason; 
	s8	m_achRoomName[TP_MAX_ALIAS_LEN+1];	//会场名
	u16	m_wLevel;							//会场等级	保留

	BOOL32 m_bMute;
	BOOL32 m_bQuiet;
	
	BOOL32 m_bIsSpeaker;					//是否发言人 保留
	BOOL32 m_bIsChair;						//是否主席   保留

	u16 m_wSpeakerNum;						//会场屏数	
	s8	m_achSpeakerName[TP_MAX_STREAMNUM][TP_MAX_ALIAS_LEN+1];
	
	s8  m_achRoomE164[TP_MAX_ALIAS_LEN+1];  // umc显示会场列表需要164号和ip，cnc暂时不需要
	u32 m_dwRoomIp;

	tagTCnsInfo()
	{	
		Clear();
	}

	void Clear()
	{
		m_wEpID = TP_INVALID_INDEX;
		m_wParentEpID = TP_INVALID_INDEX;
		m_wChildEpID = TP_INVALID_INDEX;
		m_wBrotherEpID = TP_INVALID_INDEX;
		m_tCalledAddr.Clear();
		m_emEpType = emTPEndpointTypeUMS;

		m_bOnline = FALSE;
		m_achRoomName[0] = '\0';
		m_wLevel = TP_INVALID_INDEX;
		
		m_bMute = FALSE;
		m_bQuiet = FALSE;
		m_wSpeakerNum = TP_INVALID_INDEX;
		m_emCallReason = EmCnsCallReason_Local;

		m_achRoomE164[0] = '\0';
		m_dwRoomIp = 0;
	}

	BOOL32 operator == (const tagTCnsInfo& tRhs)
	{
		return this->m_wEpID == tRhs.m_wEpID;
	}
}TCnsInfo, *PTCnsInfo;

//会议信息
typedef struct tagTTPConfInfo : public TUmsConfBase
{
	u16	m_wConfID;
	u16	m_wSpeaker;		//会议发言人ID
	u16	m_wDual;		//发送双流ID
	tagTTPConfInfo()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_wSpeaker = TP_INVALID_INDEX;
		m_wDual = TP_INVALID_INDEX;
	}
	
	void SetBaseInfo(TUmsConfBase* ptBase)
	{
		*(TUmsConfBase*)this = *ptBase;
	}

	void Clear()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_wSpeaker = TP_INVALID_INDEX;
		m_wDual = TP_INVALID_INDEX;
		TUmsConfBase::Clear();
	}

}TTPConfInfo, *PTTPConfInfo;

//会议列表增加
typedef struct tagTAddConfList
{
	u16 m_wRefreshNum;
	TTPConfInfo	m_atTmpList[TP_REFRESH_LIST_THREE];
	tagTAddConfList()
	{
		m_wRefreshNum = 0;
	}
}TAddConfList;

//会议列表删除
typedef struct tagTDelConfList
{
	u16 m_wRefreshNum;
	u16	m_awConfIDList[TP_REFRESH_LIST_THREE];
	tagTDelConfList()
	{
		m_wRefreshNum = 0;
	}
}TDelConfList;

//会议召开结果
typedef struct tagTStartConfResult
{
	EmTpStartConfRet m_emReason;
	u16	m_wConfTemplateID;
	u16	m_wConfID;
	tagTStartConfResult()
	{
		m_emReason = TP_StartConf_UnKonw;
		m_wConfTemplateID = TP_INVALID_INDEX;
		m_wConfID = TP_INVALID_INDEX;
	}
}TStartConfResult, *PTStartConfResult;


//会议会场列表
typedef struct tagTConfCnsInfo
{
	EmTpOprType	m_emOpr;	
	BOOL32		m_bLastPack;
	u16			m_wConfID;

	u16			m_wNum;
	TCnsInfo	m_tConfCnsList[TP_REFRESH_LIST_THREE];
	tagTConfCnsInfo()
	{
		m_emOpr = tp_OprType_Add;
		m_wConfID = TP_INVALID_INDEX;
		m_wNum = 0;
		m_bLastPack = TRUE;
	}
}TConfCnsInfo;

//会议轮询列表
typedef struct tagTConfTurnInfo
{
	u16				m_wConfID;
	TConfTurnList	m_atTurnList;
	tagTConfTurnInfo()
	{
		m_wConfID = TP_INVALID_INDEX;
	}
}TConfTurnInfo;


//指定发言人结果
typedef struct tagTApplaySpeakRet
{
	TConfEpID	m_tID;
	EmTpApplySpeakRet	m_emReason;
	tagTApplaySpeakRet()
	{
		m_emReason = TP_ApplySpeak_UnKonw;
	}
}TApplaySpeakRet;

typedef struct tagTUmsConfStatus
{
	BOOL32	m_bIsStartAudMix;
	tagTUmsConfStatus()
	{
		m_bIsStartAudMix = FALSE;
	}
}TUmsConfStatus;

typedef struct tagTTPUmsReasonInd
{
	u16	m_wConfID;
	u16 m_wEpID;
	u32 m_dwReason;//tperror.h中的原因
	
	u32 m_dwReserve1;//保留
	u32 m_dwReserve2;
	u32 m_dwReserve3;
	
	tagTTPUmsReasonInd()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_wEpID = TP_INVALID_INDEX;

		m_dwReason = 0;

		m_dwReserve1 = 0;
		m_dwReserve2 = 0;
		m_dwReserve3 = 0;
	}
}TTPUmsReasonInd;

//============================下面为CNS使用结构体===================//
//视频编码参数
typedef struct tagTTPMtVideoEncodeParameter    
{
	EmTpVideoFormat      emVideoFormat; 
	u16                byMaxKeyFrameInterval; // I帧间最大P帧数目
    u8                 byMaxQuant;  //最大量化参数
	u8                 byMinQuant;  //最小量化参数
    BOOL               bUseFixedFrame; //是否使用固定帧率
	u8	               byFrameRate;  //帧率
	BOOL               bFramePerSecond;  //帧率单位 TRUE＝ 帧/秒  FALSE＝秒/帧 
	
    EmTpEncodeMode emEncodeMode;     //编码方式
	EmTpVideoResolution  emVideoResolution;
	u32                wChanMaxBitrate; // 单位 Kbps
	//以下数据只有在windows平台下有用
	//添加采集图像宽高
	u16	m_wWidth; //视频捕获图像宽度 仅Windows有效(default:640)
	u16	m_wHeight;//视频捕获图像高度 仅Windows有效(default:480)
	EmTpMediaType   emCapType;    //采集类型   (default:emMediaAV)
	EmTpPCCapFormat emPCCapFormat;//视频捕获帧格式 仅Windows有效(default:emCapPCFrameBMP)
	
	u32 m_dwAvgQpI;					/* 平均qp 默认0- 28*/
	u32 m_dwAvgQpP;
	u8  m_byLoopFilterMask;		    /*开启环路滤波 默认为0 不开启*/
	u32  m_dwProfile;				// 0 BaseLine | 1 HighProfile
	//追加编码器参数
	u32  m_dwCabacDisable;			/*是否开启CABAC*/
	u32  m_dwSilceMbCont;           /*slice的宏块数量，设零则为单slice*/
	u32  m_dwRateControlAlg;        /*码率控制算法，仅对m_byRcMode == 1 时有效*/
public:
	tagTTPMtVideoEncodeParameter(){ memset( this ,0 ,sizeof( struct  tagTTPMtVideoEncodeParameter ) );}	
}TTPMtVideoEncodeParameter ,*PTTPMtVideoEncodeParameter;


typedef struct tagTTpCodecComponent
{
	u16 wPos;
	EmTpCodecComponent emCope;
	tagTTpCodecComponent()
	{
		wPos = 0;
		emCope = emTPCodecComponentEnd;
	};

}TTpCodecComponent;

typedef struct tagTTPCnMediaTransPort
{
	//	NODEHANDLE	m_handle;
	TTPTransAddr m_tRtpPort;
	TTPTransAddr m_tRtcpPort;	
	TTPTransAddr m_tBackRtcpPort;
	
	void clear()
	{
		memset(this, 0, sizeof(tagTTPCnMediaTransPort));
	}
	tagTTPCnMediaTransPort()
	{
		clear();
	}
	tagTTPCnMediaTransPort& operator = (const tagTTPCnMediaTransPort& tRhs)
	{
		if (this == &tRhs)
		{
			return *this;
		}
		//	this->m_handle = tRhs.m_handle;
		this->m_tRtpPort = tRhs.m_tRtpPort;
		this->m_tRtcpPort = tRhs.m_tRtcpPort;
		this->m_tBackRtcpPort = tRhs.m_tBackRtcpPort;
		return *this;
	}
}TTPCnMediaTransPort;

typedef struct tagTMtMPAddr
{
	u16 wPos;
	EmTpCodecComponent emCope;
	TTPCnMediaTransPort m_tAddr;
	tagTMtMPAddr()
	{
		wPos = 0;
		emCope = emTPCodecComponentEnd;
	};
}TMtMPAddr;

typedef struct tagTMtMPParam
{
	u16 m_wMpType;	//此编解码的类型    1：发言人；2：全景摄像机；4：双流；8音频 0x0000为无效  注：1 2 4指视频
	TTPCnMediaTransPort m_tAddr;
	tagTMtMPParam()
	{
		m_wMpType = 0;
	};
}TMtMPParam;
typedef struct tagTMtTPEpParam
{
	u16					wLen;					//当前结构体长度（留作版本兼容使用）
	TMtMPParam m_tSndPrimarAddr;		//第一路发送
	TMtMPParam m_tRcvPrimarAddr;		//第一路接收
	
	TMtMPParam m_tSndSecondAddr;		//第二路发送
	TMtMPParam m_tRcvSecondAddr;		//第二路接收
	
	TMtMPParam m_tSndAudioAddr;		//音频发送
	TMtMPParam m_tRcvAudioAddr;		//音频接收

// 	TMtMPParam m_tRcvPrimarLeftAddr;
// 	TMtMPParam m_tRcvPrimarRightAddr;
	
	u16	m_wPosCount; //位置总数
	u16 m_wPos;		//终端在会场中的物理位置	1，2，3，4，5
	s8  achRoomName[TP_MAX_ALIAS_LEN + 1];	//终端所在会场的名字
	EmTPMtModel m_emTPMtModel;                //终端型号
	tagTMtTPEpParam()
	{
		wLen = 0;
		m_wPos = 0;
		m_wPosCount = 0;
		m_emTPMtModel = emTPUnknownMtModel;
		memset( this->achRoomName, 0, sizeof(this->achRoomName) );
	};
}TMtTPEpParam;


typedef struct tagTMtVDecParam
{
	EmTpCodecComponent		emComp;
	TTPCnMediaTransPort		tAddr;
	EmTpLostPackageRestore	emLost;
	EmTpVideoFormat			emFormat;
	EmTpVideoResolution		emRes;
	u8						byPayload;
	TTpEncryptKey				tEncryptKey;
	u16                     wPos;

	tagTMtVDecParam()
	{
		memset( this, 0, sizeof(tagTMtVDecParam) );
	};
}TMtVDecParam;

typedef struct tagTMtVEncParam
{
	EmTpCodecComponent	emComp;
	TTPCnMediaTransPort tAddr;
	
	TTPMtVideoEncodeParameter tVideoEncodeParameter;
	u8					byPayload;
	TTpEncryptKey			tEncryptKey;
	u16                 wPos;
	tagTMtVEncParam()
	{
		memset( this, 0, sizeof(tagTMtVEncParam) );
	};
}TMtVEncParam;

typedef struct tagTCnVideoParam
{
	EmTpCodecComponent	emComp;
	TTPCnMediaTransPort tAddr;
	
	EmTpVideoFormat			emFormat;
	EmTpVideoResolution		emRes;
	u8					byPayload;
	u32                wChanMaxBitrate; // 单位 Kbps
	u8				    byFrameRate;
	TTpEncryptKey			tEncryptKey;
	u32                 m_dwProfile;
	tagTCnVideoParam()
	{
		memset( this, 0, sizeof(tagTCnVideoParam) );
	};
}TCnVideoParam;

typedef struct tagTEpId
{
	u8 byCnNo;
	u8 byEpNo;
	
public:
	tagTEpId(){ memset( this ,0 ,sizeof( struct tagTEpId ) );	}
	
}TEpId ,*PTEpId;

//============================上面为CNS使用结构体===================//

typedef struct tagTTPRegName
{
	EmTPAddrType emPAAddrType;
	s8     achUserName[TP_MAX_H323ALIAS_LEN+1];     //注册名
	s8     achPassword[TP_MAX_PASSWORD_LEN+1]; //注册密码
	s8     achDisplayName[TP_MAX_H323ALIAS_LEN+1];  //显示名称
	tagTTPRegName()
	{
		memset( this, 0, sizeof(tagTTPRegName) );
	}
}TTPRegName,*PTTPRegName;

typedef struct tagTTPRegNameRepeatInfo
{
	u32 dwsize;
	TTPRegName atTPRegName[2];
	tagTTPRegNameRepeatInfo()
	{
		memset( this, 0, sizeof(tagTTPRegNameRepeatInfo) );
	}
}TTPRegNameRepeatInfo;

//SIP Register配置
typedef struct tagTTPSipRegistrarCfg
{
	BOOL   bUsed;   //是否注册
	u32_ip dwRegIP; //注册服务器IP地址
	u16    wRegPort;//注册服务器端口
	s8     achRegDomain[TP_MAX_PROXYSERVER_NAME_LEN];
	u16    wExpire;
	BOOL   bRegistered;//注册服务器是否成功
	
	TTPRegName atTPRegName[TP_REGNAME_SIZE];//注册别名支持多个
	s32		   nTPRegNameSize;//实际别名个数
	s8     achHostDomain[TP_MAX_PROXYSERVER_NAME_LEN];//自身域名
	u32_ip dwHostIP;
	u16    wHostPort;      
	EmTPEndpointType m_emEndType;  
	u32_ip		m_locolIP;                            //本地IP                   
	s8			m_softversion[TP_MAX_VERSION_LEN+1];  //软件版本号
	s8			m_compileTime[TP_MAX_VERSION_LEN+1];  //编译时间

public:
	tagTTPSipRegistrarCfg(){ memset( this, 0, sizeof(struct tagTTPSipRegistrarCfg) ); }

}TTPSipRegistrarCfg,*PTTPSipRegistrarCfg;

//Gk Register配置
typedef struct tagTTPGkRegistrarCfg
{
	BOOL   bUsed;   //是否注册
	u32_ip dwRegIP; //注册服务器IP地址
	u16    wRegPort;//注册服务器端口
	s8     achRegDomain[TP_MAX_PROXYSERVER_NAME_LEN];
	u16    wExpire;
	BOOL   bRegistered;//注册服务器是否成功
	
	TTPRegName atTPRegName[TP_REGNAME_SIZE];//注册别名支持多个
	s32		   nTPRegNameSize;//实际别名个数
	s8     achHostDomain[TP_MAX_PROXYSERVER_NAME_LEN];//自身域名
	u32_ip dwHostIP;
	u16    wHostPort;      
public:
	tagTTPGkRegistrarCfg(){ memset( this, 0, sizeof(struct tagTTPGkRegistrarCfg) ); }
}TTPGkRegistrarCfg;

typedef struct tagTTPGKCfg
{
	BOOL bUsed; //是否使用GK
	u32_ip  dwGKIP; //GK IP地址
	u16    wRegPort;//GK 端口
	u16	 wExpire;
	BOOL bRegistered;//注册服务器是否成功
    s8   achGkIpName[TP_MAX_H323ALIAS_LEN + 1]; //Gk域名地址	暂无意义
	s8   achGKPasswd[TP_MAX_PASSWORD_LEN + 1]; //Gk密码		暂无意义
public:
	tagTTPGKCfg(){ memset( this ,0 ,sizeof( struct  tagTTPGKCfg ) );}
}TTPGKCfg;



typedef struct tagTTPSipRegPackInfo
{
	u16 m_wPackSeq;       //包序号，从1开始，0为无效值
	u16 m_wTotalPackNum;  //包总数
	tagTTPSipRegPackInfo()
	{
		m_wPackSeq = 0;
		m_wTotalPackNum = 0;
	}
	tagTTPSipRegPackInfo& operator = ( const tagTTPSipRegPackInfo &tSipRegPackInfo )
	{
		if( this == &tSipRegPackInfo )
		{
			return *this;
		}
		m_wPackSeq = tSipRegPackInfo.m_wPackSeq;
		m_wTotalPackNum = tSipRegPackInfo.m_wTotalPackNum;

		return *this;

	}

	tagTTPSipRegPackInfo( const tagTTPSipRegPackInfo &tSipRegPackInfo )
	{
		if( this == &tSipRegPackInfo )
		{
			return;
		}

		m_wPackSeq = tSipRegPackInfo.m_wPackSeq;
		m_wTotalPackNum = tSipRegPackInfo.m_wTotalPackNum;
		
	}
}TTPSipRegPackInfo, *PTTPSipRegPackInfo;

//从SIP注册服务器得到全域信息
typedef struct tagTTPSipRegInfo
{
	u16				m_wAliasNum;
	TTPAlias		m_atAlias[TP_REGNAME_SIZE];                 //暂时定为最大值为64个名称为一波返回
	
	EmTPEndpointType	m_emSelfType;//注册方 的系统类型(UMS和CNS)				

	tagTTPSipRegInfo()
	{
		m_wAliasNum = 0;
		memset( m_atAlias, 0, sizeof( m_atAlias ) );
		m_emSelfType = emTPEndpointTypeUnknown;
	}

	tagTTPSipRegInfo& operator = ( const tagTTPSipRegInfo &tSipRegInfo )
	{
		if( this == &tSipRegInfo )
		{
			return *this;
		}
		m_wAliasNum = tSipRegInfo.m_wAliasNum;
		m_emSelfType = tSipRegInfo.m_emSelfType;
		memcpy( m_atAlias, tSipRegInfo.m_atAlias, sizeof( m_atAlias ) );
		
		return *this;
		
	}
	
	tagTTPSipRegInfo( const tagTTPSipRegInfo &tSipRegInfo )
	{
		if( this == &tSipRegInfo )
		{
			return;
		}
		m_wAliasNum = tSipRegInfo.m_wAliasNum;
		m_emSelfType = tSipRegInfo.m_emSelfType;
		memcpy( m_atAlias, tSipRegInfo.m_atAlias, sizeof( m_atAlias ) );
	}
}TTPSipRegInfo;


//CNS存储注册包的结构体
typedef struct tagTTPSipPack
{
	TTPSipRegPackInfo m_tSipRegPackInfo;
	TTPSipRegInfo m_tSipRegInfo;

	tagTTPSipPack()
	{
		memset( this, 0, sizeof( tagTTPSipPack ) );
	}
	
	tagTTPSipPack &operator=( const tagTTPSipPack &tSipPack )
	{
		if( this == &tSipPack )
		{
			return *this;
		}
		m_tSipRegPackInfo = tSipPack.m_tSipRegPackInfo;
		m_tSipRegInfo = tSipPack.m_tSipRegInfo;

		return *this;
	}

	tagTTPSipPack( const tagTTPSipPack &tSipPack )
	{
		if( this == &tSipPack )
		{
			return;
		}
		m_tSipRegPackInfo = tSipPack.m_tSipRegPackInfo;
		m_tSipRegInfo = tSipPack.m_tSipRegInfo;
		
	}
	
}TTPSipPack;


//全局地址通知用户列表项
typedef struct tagTTPAddrNtyUser
{
	u32 m_dwIID;               //APP+INS ID					   UMS时表示TLogUser Node
	u32 m_wUserData;           //USERDATA2  两者都必须大于0    UMS时表示TLogUser inst
	EmGetRegInfoType m_emType;
	
	tagTTPAddrNtyUser( u32 dwIID, u16 wUserData, EmGetRegInfoType emType)
	{
		if( 0 == dwIID || 0 == wUserData )
		{
			return;
		}
		m_dwIID = dwIID;
		m_wUserData = wUserData;
		m_emType = emType;
	}
	
	tagTTPAddrNtyUser( const tagTTPAddrNtyUser &tNtyUser )
	{
		if( this == &tNtyUser )
		{
			return;
		}

		m_dwIID = tNtyUser.m_dwIID;
		m_wUserData = tNtyUser.m_wUserData;
		m_emType = tNtyUser.m_emType;
	}

	tagTTPAddrNtyUser& operator = (const tagTTPAddrNtyUser &tNtyUser )
	{
		if( this == &tNtyUser )
		{
			return *this;
		}
		m_dwIID = tNtyUser.m_dwIID;
		m_wUserData = tNtyUser.m_wUserData;
		m_emType = tNtyUser.m_emType;
		return *this;
	}
	tagTTPAddrNtyUser()
	{
	}
	u16 GetInstID()
	{
		return (u16)m_dwIID;
	}
}TTPAddrNtyUser;







//UMS,CNS接收协议栈注册结果信息
typedef struct tagTUCSipRegResult
{
	EmTpCnsRegUms m_emTpCnsRegUms;        //注册结果
	TTPAlias m_atTPAlias[TP_CONFTEMPGROUP_MAXNUM];
	s32 m_nAliasNum;                     //实际别名数量

}TUCSipRegResult;


//终端地址
typedef struct tagTCnAddr
{
	EmTPAddrType	emType;							//地址类型
	u32_ip			 dwIP;						//终端IP地址
	u16          wPort;						//端口
	s8			 achAlias[TP_MAX_H323ALIAS_LEN+1];		//(别名)
	s8			 achE164[TP_MAX_H323ALIAS_LEN+1];		//(164号)
	BOOL         bCallByIPAndAlias;
public:
	tagTCnAddr(){memset( this ,0 ,sizeof( struct tagTCnAddr));	}
}TCnAddr;

typedef struct tagTTPSipNstHeader
{
	s8	m_achName[TP_SDP_ATTR_NAME_LEN];	/**< Param/header name.	    */
	s8	m_achValue[TP_SDP_ATTR_VALUE_LEN];	/**< Param/header value.    */
	
	void Clear()
	{
		memset(m_achName, 0, sizeof(m_achName));
		memset(m_achValue, 0, sizeof(m_achValue));
	}
	tagTTPSipNstHeader()
	{
		Clear();
	}
}TTPSipNstHeader;

//呼叫参数
typedef struct tagTTPDialParam
{
	EmTpConnectionType emTpConnectionType;  //信令连接方式 tcp udp default tcp
	EmTpCallMode   emCallType;			// 呼叫类型:JOIN|CREATE|INVITE
	EmTpConfProtocol emProtocol;          // 通信协议协议
	u16			 wCallRate;			    // 呼叫速率(kbps)	
	TCnAddr	     tCallingAddr;		    // 主叫地址(主叫时可不填)
	TCnAddr	     tCalledAddr;			// 被叫地址		
	
	EmTPEndpointType      m_emEndpointType;					  //终端类型  表示呼入终端的类型
	BOOL32			      m_bIsEncrypt;						//是否支持加密
	   
	s32					  m_nProductIdSize;
	u8					  m_abyProductId[TP_NAME_LEN_256];				//产品号
	s32					  m_nVerIdSize;
	u8					  m_abyVersionId[TP_NAME_LEN_256];				//版本号
	
	u32_ip		dwRegIP; //注册服务器IP地址
	u16		wRegPort;//注册服务器端口
	s8		achRegDomain[TP_MAX_PROXYSERVER_NAME_LEN];
	s8     achDisplayName[TP_MAX_NAME_LEN+1];  //别名
    s8     achUserName[TP_MAX_NAME_LEN+1];     //注册名
	s8     achPassword[TP_MAX_PASSWORD_LEN+1]; //注册密码
	s8     achHostDomain[TP_MAX_PROXYSERVER_NAME_LEN];//自身域名
	//////////////////////////////////////////////////////////////////////////
	//以下仅用于创建会议
	BOOL		bCreateConf;		//是否是创建会议
	TTPConfBaseInfo   tConfInfo;			//会议信息
	u8			byTerNum;			//被邀终端个数
	TCnAddr 	atList[TP_CONF_INVITE_MAX_CNS];	//被邀终端列表

	EmTPSipLevel m_emSipLevel;
	s32          m_nScreenNum;
	TTpEncryptKey tEncryptKey;
	TTpQtEncryptCfg tQtEncryptCfg;
	u8 m_byNonStdHdrNum;	//非标sip包头个数
	TTPSipNstHeader m_atNonStdHdr[TP_SIP_NONSTD_HEADER_NUM];	 //非标sip包头,KdNstd为sip协议栈内部标示,业务不需要填下来

public:
	tagTTPDialParam(){ memset( this ,0 ,sizeof( struct tagTTPDialParam ) );}
}TTPDialParam,*PTTPDialParam;


//网络信息数据结构
typedef struct tagTTPEthnetInfo
{
    BOOL bEnable;
    u32_ip  dwIP;          //IP
    u32_ip  dwMask;        //子网掩码
    u32_ip  dwGateWay;   //网关
public:
	tagTTPEthnetInfo(){ memset( this ,0 ,sizeof( tagTTPEthnetInfo ) );}
}TTPEthnetInfo;

//双网络信息数据结构
typedef struct tagTTPWEthnetInfo
{
    TTPEthnetInfo atTPEthnetInfo[2];
public:
	tagTTPWEthnetInfo(){ memset( this ,0 ,sizeof( tagTTPWEthnetInfo ) );}
}TTPWEthnetInfo;

typedef struct tagTTPCnsInfo
{		
	s8	m_achRoomName[TP_MAX_ALIAS_LEN+1];	//会场名	
	s8	m_achE164[TP_MAX_ALIAS_LEN+1];	    //E164号	
	u16 m_wScreenNum;						//会场屏数
	EmTPSipLevel	m_emLevel;							//会场等级
	u8  m_byDualPos;                       //是否有双流源 0xff为没有双流
	u32_ip m_adwIP[CNS_MAX_TER_NODE_NUM];        //会场ip
	public:
	tagTTPCnsInfo(){ memset( this ,0 ,sizeof( struct tagTTPCnsInfo ) );}
}TTPCnsInfo;

//时间结构重新定义
typedef struct tagTTPTime
{
    u16 		m_wYear;//年
    u8  		m_byMonth;//月
    u8  		m_byMDay;//日
    u8  		m_byHour;//时
	u8  		m_byMinute;//分
	u8  		m_bySecond;//秒
public:
    tagTTPTime(){ memset ( this ,0 ,sizeof( struct tagTTPTime) );}
	BOOL32 IsValid()	{ return m_wYear != 0 && m_byMonth != 0 && m_byMDay != 0;}
	BOOL32 operator < (const tagTTPTime& tRhs)
	{
		if (m_wYear < tRhs.m_wYear)	return TRUE;
		else if (m_wYear > tRhs.m_wYear)	return FALSE;
		else
		{
			if (m_byMonth < tRhs.m_byMonth) return TRUE;			
			if (m_byMonth > tRhs.m_byMonth) return FALSE;
			else
			{
				if (m_byMDay < tRhs.m_byMDay) return TRUE;			
				if (m_byMDay > tRhs.m_byMDay) return FALSE;
				else
				{
					if (m_byHour < tRhs.m_byHour) return TRUE;			
					if (m_byHour > tRhs.m_byHour) return FALSE;
					else
					{
						if (m_byMinute < tRhs.m_byMinute) return TRUE;			
						if (m_byMinute > tRhs.m_byMinute) return FALSE;
						else
						{
							if (m_bySecond < tRhs.m_bySecond) return TRUE;			
							if (m_bySecond > tRhs.m_bySecond) return FALSE;
							else
							{
								return FALSE;
							}		
						}	
					}	
				}
			}
		}
	}
}TTPTime, *PTTPTime;

typedef struct tagTTPCnsConfStatus
{		
	 EmCALLSTATE	emState;
	 u16			wConfID;//
	 s8				achConfName[TP_MAX_ALIAS_LEN+1];
	 //time_t         m_dwStartTime;    //会议开始时间
	 u32            m_dwStartTime;    //会议开始时间 modified by niulifu 由于time_t类型不跨平台，应用转换解析数据失败故修改为u32类型
	 EmCallType     m_emCallType;     //会议类型
	 BOOL32         m_bMixMotive;     //是否采用语音激励
	 //Add by tanxiaodong 2012-12-03.
	 EmTpConfProtocol m_emConfProtocal;//会议协议类型
	 TCnAddr	     tCalledAddr;
	 EmTPEncryptType m_emTPEncryptType;
	 TTpQtEncryptCfg m_tQtEncryptCfg;
	 //End to add.
	public:
	tagTTPCnsConfStatus(){ clear() ;};
	void clear()
	{ 
		memset( this ,0 ,sizeof( struct tagTTPCnsConfStatus ) ); 
		m_bMixMotive = 1;
		wConfID = 0xffff;

	};
}TTPCnsConfStatus;


typedef struct tagTTPDualInfo
{
	EmTPPayloadType m_emPayload;
	EmTpVideoResolution  m_emReslution;
	u16				m_wFrameRate;
	u16             m_wBitRate;
	s32 m_nScreenNo;
	s32 m_nEpId;
	s8  m_achCascade[TP_MAX_ALIAS_LEN+1];
	TTPTransAddr m_tRtp;
	TTPTransAddr m_tRtcp;
	TTPTransAddr m_tBackRtp;
	
	tagTTPDualInfo()
	{
		memset( this, 0, sizeof(tagTTPDualInfo) );
	}
	
}TTPDualInfo;

typedef struct tagTTPDualRequest
{
	s8 m_achCascade[ TP_MAX_ALIAS_LEN + 1 ];
	s32 m_nEpId;
	tagTTPDualRequest()
	{
		memset( this, 0, sizeof(tagTTPDualRequest) );
	}
}TTPDualRequest;

typedef struct tagTTPDualInfoAck
{
	BOOL    m_bAccept;
	TTPDualInfo m_tDualInfo;
	tagTTPDualInfoAck()
	{
		memset( this, 0, sizeof(tagTTPDualInfoAck) );
	}
}TTPDualInfoAck;

typedef struct tagTTPAudioInfo
{
	u8     m_byInputVolume;  //输入音量（编码音量）
	u8     m_byOutputVolume; //输出音量（解码音量）

	public:
	tagTTPAudioInfo()
	{
		memset( this, 0, sizeof(tagTTPAudioInfo) );
	}
}TTPAudioInfo;

typedef struct tagTTPHduRegInfo
{
	BOOL32		m_bIsOnline;	//HDU是否注册
	u32_ip   		m_dwIpAddr;		//外设IP地址	,   网络序
	u16 		m_wStartPort;	//外设起始接收端口, 主机序

	s8          m_achAlias[TP_MAX_ALIAS_LEN + 1];	//会场名字
	u16			m_dwChannelHandle;					//通道号

	u16         m_wScreenNum;      //屏号
	tagTTPHduRegInfo()
	{
		m_bIsOnline = FALSE;
		m_dwIpAddr = 0;
		m_wStartPort = 0;
		m_achAlias[0] = '\0';
		m_dwChannelHandle = TP_INVALID_INDEX;
		m_wScreenNum = TP_INVALID_INDEX;
	}
	void SetAlias(const s8* alias)
	{
		strncpy(m_achAlias, alias, TP_MAX_ALIAS_LEN);
		m_achAlias[TP_MAX_ALIAS_LEN] = '\0';
	}
}TTPHduRegInfo;

typedef struct tagTTPHduPlayReq
{
	EmViewEpType	m_emType;
	u16		m_wConfID;
	u16		m_wDstID;
	u16		m_wScreenNum;

	u16		m_wIndex;		//索引
	u8		m_bySubIndex;	//子索引
	BOOL32	m_bVmp;

	tagTTPHduPlayReq()
	{
		m_emType = EmEpType_Ter;
		m_wConfID = 0;
		m_wDstID = 0;
		m_wScreenNum = 0;
		m_wIndex = 0;
		m_bySubIndex = 0;
		m_bVmp = FALSE;
	}
}TTPHduPlayReq;

typedef struct tagTPHduBaseInfo
{
	u16		m_wIndex;
	u8		m_bySubIndex;

	tagTPHduBaseInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_wIndex = 0;
		m_bySubIndex = 0;
	}

}TPHduBaseInfo;

typedef struct tagTHduSetVolInfo
{
	TPHduBaseInfo	m_tInfo;
	u8		m_byVol;
	BOOL32	m_bMute;

	tagTHduSetVolInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_tInfo.Clear();
		m_byVol = 0;
		m_bMute = FALSE;
	}
}THduSetVolInfo;


typedef struct tagTTPCnLoginfo
{
	s32	nVersion;
public:
    tagTTPCnLoginfo(){ memset ( this ,0 ,sizeof( struct tagTTPCnLoginfo) );}
}TTPCnLoginfo;
//cns sp1 新结构定义
typedef struct tagTTPCn
{
	u8	byInsId;
	s8  achName[TP_MAX_ALIAS_LEN+1];
public:
    tagTTPCn(){ memset ( this ,0 ,sizeof( struct tagTTPCn) );}
}TTPCn;

typedef struct tagTTPCnList
{
	u16		wNum;
	TTPCn	tCn[CNS_MAX_CONF_NODE_NUM];
public:
    tagTTPCnList(){ memset ( this ,0 ,sizeof( struct tagTTPCnList) );}
}TTPCnList;
//end cns sp1
typedef struct tagTAudMixStat
{
	u16		m_wConfID;
	u16		m_wEpID;
	BOOL32	m_bIsStart;
	EmTpMixStatus	m_emMixStatus;
	tagTAudMixStat()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_wEpID = TP_INVALID_INDEX;
		m_bIsStart = FALSE;
		m_emMixStatus = emAudMixIdle;
	}
}TAudMixStat;

typedef struct tagTTPDisScreenStat
{
	BOOL32 m_bInDiscard;	//该会场是否在讨论中
	u16 m_wEpIDDst;			//UMS级联用
	
	u16 m_awScreenNum[TP_MAX_STREAMNUM]; //三个屏对应会场的屏数
	u16 m_awSpeakerIndx[TP_MAX_STREAMNUM];//三个屏对应会场的对应的发言坐席索引
	TTPAlias m_atAlias[TP_MAX_STREAMNUM];//三个屏对应的会场别名，无效值代表此处会场为空需看静态图片，单屏为中间
	EmTPDisOprType	m_emOprType;//操作类型
	
	tagTTPDisScreenStat()
	{
		memset( this, 0, sizeof(tagTTPDisScreenStat) );
	}
	
}TTPDisScreenStat;

typedef struct tagTTPGetRegInfo
{
	EmGetRegInfoType emType;
	u32    dwRegIP;         //注册服务器IP地址
	u16    wRegPort;        //注册服务器端口
	u32    dwLocalIP;       //本地ip
	u16    wLocalPort;           //本地端口
	
	tagTTPGetRegInfo()
	{
		memset( this, 0, sizeof(tagTTPGetRegInfo) );
	}
}TTPGetRegInfo;

typedef struct tagTTPAacCap : public TTPAudCap
{
	EmTPAACSampleFreq emPASampleFreq;
    EmTPAACChnlCfg    emPAChnlCfg;
public:
    tagTTPAacCap(){ memset ( this, 0, sizeof( struct tagTTPAacCap) );}
	
}TTPAacCap;

typedef struct tagTTPG7221Cap : public TTPAudCap
{
	u8  byBitRateType;         //encode bitrate
public:
	tagTTPG7221Cap()
		:TTPAudCap()
	{
		byBitRateType = emTPG7221Rate24;
	}
	
	void Clear()
	{
		TTPAudCap::Clear();
		byBitRateType = emTPG7221Rate24;
	};
	
    //设置rate
	void SetRateType( u8 byRateType )
	{
		byBitRateType = byRateType;
	}
	void OrRateType( EmTPG7221Rate emPARateType )
	{
		byBitRateType = (byBitRateType | emPARateType);
	}
	
	//获取rate
	u8 GetRateType()
	{
		return byBitRateType;
	}
	
	
	void SetBitRate( u32 dwBitRate )
	{
		byBitRateType = 0;
		if ( dwBitRate == 48000 )
			byBitRateType |= emTPG7221Rate48;
        else if ( dwBitRate == 32000 )
			byBitRateType |= emTPG7221Rate32;
        else
			byBitRateType |= emTPG7221Rate24;
	}
	
	u16 GetBitRate()
	{
		if( byBitRateType & emTPG7221Rate48 )
			return 48000;
		else if ( byBitRateType & emTPG7221Rate32 )
			return 32000;
		else 
			return 24000;
	}
	
}TTPG7221Cap;

typedef struct tagTTPMediaStream
{	
	BOOL32 bActive;
	EmTpMediaType emTPMediaType;
	
	TTPTransAddr	tLocalRtp[TP_MAX_STREAMNUM];
	TTPTransAddr	tRemPAoteRtp[TP_MAX_STREAMNUM];			
	
	TTPTransAddr	tSendRtcp[TP_MAX_STREAMNUM]; //  	
	TTPTransAddr	tRecvRtcp[TP_MAX_STREAMNUM]; //
	
	EmTPPayloadType aemTPMediaPT[20];
	u8 byMediaCount;
	
	
	//CPAH264VideoCap tH264Cap;
	TTPAudCap			tACap;
	TTPG7221Cap			tG7221;
	TTPAacCap		tAacCap;
	//视频能力
	TTPVideoCap tVidCap;
	
	EmTPPayloadType  emTPActivePT;
	
	EmTPEncryptType emTPEncryptType;	  //加密类型
	//TPAEncryptSync  m_tEncryptSync;       //master需设置此结构         
	s32 nBitRate;
	u32 dwLocalIp;
	
	s32 nScreenNo;                      //本地屏号， 组号
	s32 nPeerScreenNo;				  //对端屏号， 组号	
	EmTPCapSign m_emTPCapSign[TP_MAX_CAP_SIGN_NUM];            //标识大小码流, 能力发下来时一定要按照顺序， 左，中，右 
	
	BOOL32 bDual;                       //双流， 
	EmTPChanType emTPChanType;

	BOOL32 m_bAudMix;				//混音
	TTpEncryptKey			tEncryptKey;
	
public:
    tagTTPMediaStream(){ memset ( this ,0 ,sizeof( struct tagTTPMediaStream) );}
	
}TTPMediaStream;

typedef struct tagTTPCnStream
{	
	u16 wIndex;
	s32 nScreenNo;
	EmTPChanType   emChanType;
	EmTpMediaType  emMediaType;
	EmTPChanSubType	emChanSubType;
	
	TTPMediaTransAddr tTPMediaTransAddr[TP_MAX_CAP_SIGN_NUM];

	EmTPCapSign m_emTPCapSign[TP_MAX_CAP_SIGN_NUM];            //标识大小码流, 能力发下来时一定要按照顺序， 左，中，右 

public:
	tagTTPCnStream(){ memset ( this, 0, sizeof( struct tagTTPCnStream) );}

}TTPCnStream;

typedef struct tagTTPCnUnpackStream
{
	u16 wIndex;
	s32 nScreenNo;
	EmTPChanType   emChanType;
	EmTpMediaType  emMediaType;
	EmTPChanSubType	emChanSubType;
	
	TTPMediaTransAddr tTPMediaTransAddr;
	
	EmTPCapSign m_emTPCapSign[TP_MAX_CAP_SIGN_NUM];            //标识大小码流, 能力发下来时一定要按照顺序， 左，中，右
	
	u8 byMediaTransAddrIndex;//媒体流转换地址的索引，分为0，1，2
	
public:
	tagTTPCnUnpackStream(){ memset ( this, 0, sizeof( struct tagTTPCnUnpackStream) );}
	
}TTPCnUnpackStream;

typedef struct tagTTPDualCap 
{
	u16                 wDualVidCapNum;                 //双流视频能力个数
	TTPVideoCap			tVidCap[MAX__TP_MEDIA_CAP_NUM];						//视频能力
	TTPAacCap			tAacCap;						//aacld音频能力
	TTPAudCap			tG711a; 
	TTPAudCap			tG711u;  
	TTPAudCap			tG719;
	TTPG7221Cap			tG7221;
	TTPAudCap			tMP3;
	TTPAacCap			taaclc;
	EmTPPayloadType		aemTPMediaPT[20];				//按其优先进行排序
	TTPCnStream			tCnDualStream[CNS_Dual_MAX_CHANNEL];
public:
    tagTTPDualCap(){ memset ( this, 0, sizeof( struct tagTTPDualCap) );}
	
}TTPDualCap;


typedef struct tagTCnsCapset 
{	
	EmTPEncryptType		emEncryptBits;			//加密类型
 	u16					wFECBits;							//FEC类型
 	u16					wMaxBitRate;							//kbps， Node支持的总带宽
 	
 	TTPVideoCap			tVidCap;						//视频能力
 	TTPAacCap			tAacCap;						//aacld音频能力
 	TTPAudCap			tG711a; 
 	TTPAudCap			tG711u;  
 	TTPAudCap			tG719;
 	TTPG7221Cap			tG7221;
 	TTPAudCap			tMP3;
 	TTPAacCap			taaclc;
	EmTPPayloadType		aemTPMediaPT[20];				//按其优先进行排序

 	TTPCnStream			tCnStream[CNS_CALL_MAX_CHANNEL];
	u16					wChannelCount;
	u32					dwCnsIp;
public:
    tagTCnsCapset(){ memset ( this ,0 ,sizeof( struct tagTCnsCapset) );}

}TCnsCapset;

typedef struct tagTTPYouAreSeeing
{
	u32 m_dwVideoNum;	//视频发送数量
	u32 m_dwAudioNum;	//音频发送数量
	u16 m_CNSId;		//CNSID
	BOOL32 m_bExist;	//是否存在
	s8  m_achMeetingName[TP_MAX_ALIAS_LEN + 1];	//发言人会场名
	u16 m_wSpeakerIndex; 	
	tagTTPYouAreSeeing()
	{
		memset( this, 0, sizeof(tagTTPYouAreSeeing) );
	}
	
}TTPYouAreSeeing;

//终端编号参数
typedef struct tagTTPTerLabel
{
	u8 m_byMcuNo;
	u8 m_byTerNo;
	tagTTPTerLabel()
	{
		memset( this, 0, sizeof(tagTTPTerLabel) );
	}
	
}TTPTerLabel;

typedef struct tagTPModuleTerminalInfo
{
	u8 m_byMcuNo;   
	u8 m_byTerNo;
	u8 m_byConfNo;   //会议号码
	s8 m_achTerminalId[TP_MAX_NUM_CALLID+1];    //TerminalID
	BOOL32 m_bIsChair;   //是否是主席
	BOOL32 m_bIsFloor;   //是否是发言人
	
	BOOL32 m_bLastPack;  // 是否是最后一包
	BOOL32 m_bOnline;    // 是否在线
	
	tagTPModuleTerminalInfo()
	{
		memset( this, 0, sizeof(tagTPModuleTerminalInfo) );
	}
	

}TPModuleTerminalInfo;

typedef struct tagTTPPollDstName
{
	s8				m_abyAlias[TP_MAX_ALIAS_LEN + 1];
	u32             m_nScreenNum;
	tagTTPPollDstName()
	{
		memset( this, 0, sizeof(tagTTPPollDstName) );
	}
}TTPPollDstName;


typedef struct tagTMtADecParam
{
	EmTpCodecComponent emComp;
	TTPCnMediaTransPort tAddr;
	EmTpAudioFormat	emAudioFormat;
	u8				byPayload;
	TTpEncryptKey		tEncryptKey;
	
	TTPG7221Cap			tG7221;
	TTPAacCap			tAaclc;
	u16                 wPos;
	tagTMtADecParam()
	{
		emComp = emTPAudioDecoder;
		emAudioFormat = emTPAG711a;
		byPayload = 0;
	};
}TMtADecParam;

typedef struct tagTMtAEncParam
{
	EmTpCodecComponent	emComp;
	TTPCnMediaTransPort tAddr;
	EmTpAudioFormat		emAudioFormat;
	u8					byPayload;
	TTpEncryptKey			tEncryptKey;
	
	TTPG7221Cap			tG7221;
	TTPAacCap			tAaclc;
	u16                 wPos;
	tagTMtAEncParam()
	{
		emComp = emTPAudioEncoder;
		emAudioFormat = emTPAG711a;
		byPayload = 0;
	};
}TMtAEncParam;

typedef struct tagTTPChanSelecteCascadRes
{
    u32 nRes;
	s8  achName[TP_MAX_ALIAS_LEN+1];
	tagTTPChanSelecteCascadRes()
	{
		memset(this, 0, sizeof(tagTTPChanSelecteCascadRes));
	}
}TTPChanSelecteCascadRes;

typedef struct tagTTPChanSelecteCascadCancelRes
{
	s32 nPeerID;
    u32 nRes;
	tagTTPChanSelecteCascadCancelRes()
	{
		memset(this, 0, sizeof(tagTTPChanSelecteCascadCancelRes));
	}
}TTPChanSelecteCascadCancelRes;

typedef struct tagTTerminalLabel 
{
	u8 m_byMcuNo;
	u8 m_byTerNo;
}TTerminalLabel;

// typedef struct tagTTPDisListOpr
// {
// 	u16 m_wConfID;
//     u16 m_wEpID;
// 	u16 m_wIndex;//在CNC界面的位置 0-3
// 	EmDisListOprType m_emOprType;
// 	EmDisListOprReslt m_emOprReslt; //回复CNC时使用
// 	tagTTPDisListOpr()
// 	{
// 		m_wConfID = TP_INVALID_INDEX;
// 		m_wEpID = TP_INVALID_INDEX;
// 		m_wIndex = TP_INVALID_INDEX;
// 		m_emOprType = em_DisListOpr_Add;
// 		m_emOprReslt = em_DisListOpr_Sucess;
// 	}
// }TTPDisListOpr;

typedef struct tagTDiscussListOpr
{
	u16 m_wConfId;
	u16 m_wNum; // 添加或删除的数量
	u16 m_awEpId[TP_CONF_MAX_AUDMIXNUM];  // 添加or删除的会场成员
	EmDisListOprType  m_emOprType;   // 添加or删除
	
	EmDiscussOprRes m_aemRet[TP_CONF_MAX_AUDMIXNUM];   // 操作多个会场，回复每个会场的操作结果，与m_awEpId[TP_CONF_MAX_AUDMIXNUM]一一对应，用于ind消息

	tagTDiscussListOpr()
	{
		Clear();
	}
	void ResetOprRes()
	{
		for (u16 wIndex = 0; wIndex <TP_CONF_MAX_AUDMIXNUM; wIndex++)
		{
			m_aemRet[wIndex] = em_Discuss_OtherFail;
		}
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTDiscussListOpr));
	}

}TDiscussListOpr;


typedef struct tagTTPRegistReq
{
	s8 m_atH323Alias[TP_MAX_ALIAS_LEN+1];
	s8 m_atE164[TP_MAX_ALIAS_LEN+1];
	
	
	TTPTransAddr m_tLocalAddress;    //需要注册的地址
	TTPTransAddr m_tGKAddress;
	TTPTransAddr m_tRegAddress;      //sip regserver地址
	
	s32			m_nTimeToLive;      //秒
public:
	tagTTPRegistReq()
	{
		Clear();
	}
	void Clear()
	{
		memset( m_atE164 , 0 , sizeof(m_atE164) );
		memset( m_atH323Alias , 0 , sizeof(m_atH323Alias) );
		m_tLocalAddress.Clear();
		m_tGKAddress.Clear();
		m_tRegAddress.Clear();
		m_nTimeToLive = 60;
	}
}TTPRegistReq;

typedef struct tagTCnsAVCapset 
{	
	EmTPEncryptType		emEncryptBits;			//加密类型
	u16					wFECBits;							//FEC类型
	u16					wMaxBitRate;							//kbps， Node支持的总带宽
	
	u16 wVidCapNum;                                     //视频能力个数
	TTPVideoCap			atVidCap[MAX__TP_MEDIA_CAP_NUM];						//视频能力
	TTPAacCap			tAacCap;						//aacld音频能力
	TTPAudCap			tG711a; 
	TTPAudCap			tG711u;  
	TTPAudCap			tG719;
	TTPG7221Cap			tG7221;
	TTPAudCap			tMP3;
	TTPAacCap			taaclc;
	EmTPPayloadType		aemTPMediaPT[20];				//按其优先进行排序
	u32					dwCnsIp;
public:
    tagTCnsAVCapset(){ memset ( this ,0 ,sizeof( struct tagTCnsAVCapset) );}
	
}TCnsAVCapset;

typedef struct tagTCnsAddrCapset 
{		
	TTPCnStream			tCnStream[CNS_CALL_MAX_CHANNEL];
	u16					wChannelCount;
	u32					dwCnsIp;
public:
    tagTCnsAddrCapset(){ memset ( this ,0 ,sizeof( struct tagTCnsAddrCapset) );}
	
}TCnsAddrCapset;

 //Add by tanxiaodong 2012-07-17.
//VGA设备信息结构体
typedef struct tagTVgaInfo
{
	EmVgaType m_emVgaType;              //VGA设备类型
	s8 m_achAlias[TP_MAX_ALIAS_LEN + 1];//对应的设备别名
	tagTVgaInfo()
	{
		memset( this, 0, sizeof(tagTVgaInfo) );
	}

}TVgaInfo;

typedef struct tagTTPNatCfg
{
	BOOL bUsed; //是否使用静态NAT
	u32_ip  dwNatIP; //静态NAT IP地址
public:
	tagTTPNatCfg(){ memset( this ,0 ,sizeof( struct  tagTTPNatCfg ) );}
}TTPNatCfg;

typedef struct tagTUmsVersion
{
	s8		m_abSoftVersion[TP_TOOL_VERSION_LEN + 1];	//软件版本
	s8		m_abHardVersion[TP_TOOL_VERSION_LEN + 1];	//硬件版本

	public:
	tagTUmsVersion()
	{ 
		memset( this ,0 ,sizeof( struct  tagTUmsVersion ) );
	}

	void SetSoftVersion(s8* bVer)
	{
		if(bVer == NULL) 
		{
			return;
		}

        memset(m_abSoftVersion, 0, TP_TOOL_VERSION_LEN + 1);
        int length = (strlen(bVer) >= TP_TOOL_VERSION_LEN ? TP_TOOL_VERSION_LEN : strlen(bVer));
        memcpy(m_abSoftVersion, bVer, length);
        m_abSoftVersion[length] = '\0';
	}

	void SetHardVersion(s8* bVer)
	{
		if(bVer == NULL) 
		{
			return;
		}
		
        memset(m_abHardVersion, 0, TP_TOOL_VERSION_LEN + 1);
        int length = (strlen(bVer) >= TP_TOOL_VERSION_LEN ? TP_TOOL_VERSION_LEN : strlen(bVer));
        memcpy(m_abHardVersion, bVer, length);
        m_abHardVersion[length] = '\0';
	}
}TUmsVersion;


typedef struct tagTToolSysInfo
{
	u32			m_dwCpuRate;	//CPU使用率
	u32			m_dwMemRate;	//内存使用率
	public:
	tagTToolSysInfo()
	{ 
		memset( this ,0 ,sizeof(struct  tagTToolSysInfo));
	}
}TToolSysInfo;

typedef struct tagTHduChanInfo
{
	BOOL32			m_bVmp;		//是否配置为合成通道
	EmHduOutPort	m_emOutPortType;	//接口类型
    EmHduOutMode	m_emOutModeType;	//输出制式
	EmHduZoomRate	m_emZoomRate;		//缩放比列
	EmHduShowMode	m_emShowMode;		//输出比例

	tagTHduChanInfo()
	{
		Clear();
	}
	
	void Clear()
	{
		m_bVmp = FALSE;
		m_emOutPortType = em_hdu_outport_unknow;
		m_emOutModeType = em_hdu_outmode_unknow;
		m_emZoomRate    = em_hdu_zoomrate_unknow;
		m_emShowMode    = em_hdu_showmode_unknow;
	}

	tagTHduChanInfo& operator = (const tagTHduChanInfo& tChan)
	{
		if (this == &tChan)
		{
			return *this;
		}

		m_emOutPortType = tChan.m_emOutPortType;
		m_emOutModeType = tChan.m_emOutModeType;
		m_emShowMode = tChan.m_emShowMode;
		m_emZoomRate = tChan.m_emZoomRate;

		return *this;
	}

	BOOL32	IsValid()
	{
		return (m_emOutPortType != em_hdu_outport_unknow  &&
				m_emOutModeType != em_hdu_outmode_unknow  &&
				m_emZoomRate    != em_hdu_zoomrate_unknow &&
				m_emShowMode    != em_hdu_showmode_unknow
				);
	}

	void SetOutType(const EmHduOutPort& emType)
	{
		m_emOutPortType = emType;
	}

	EmHduOutPort GetOutType()
	{
		return m_emOutPortType;
	}

	void SetOutMode(const EmHduOutMode& emType)
	{
		m_emOutModeType = emType;
	}

	EmHduOutMode GetOutMode()
	{
		return m_emOutModeType;
	}

	void SetZoomRate(const EmHduZoomRate& emRate)
	{
		m_emZoomRate = emRate;
	}

	EmHduZoomRate GetZoomRate()
	{
		return m_emZoomRate;
	}

	void SetShowMode(const EmHduShowMode& emMode)
	{
		m_emShowMode = emMode;
	}

	EmHduShowMode GetShowMode()
	{
		return m_emShowMode;
	}
	
	BOOL32 GetVmp()
	{
		return m_bVmp;
	}

	void SetVmp(BOOL32 bVmp)
	{
		m_bVmp = bVmp;
	}

}THduChanInfo;

//电视墙信息
typedef struct tagTHduInfo
{
	u8			m_byLayer;		//层号
	u8			m_bySlot;		//槽号

	EMBrdType		m_emBrdType;
	THduChanInfo	m_atChanInfo[HDU_MAX_CHANNEL_NUM];
	TTPName			m_tName;

	tagTHduInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_byLayer = 0;
		m_bySlot  = 0;

		for (u16 wIndex = 0; wIndex < HDU_MAX_CHANNEL_NUM; ++wIndex)
		{
			m_atChanInfo[wIndex].Clear();
		}

		m_emBrdType = em_hdu2_brd;
	}
}THduInfo;

//电视墙配置信息
typedef struct tagTHduCfg
{	
	u8		m_byLayer;		//层号
	u8		m_bySlot;		//槽号
	u32_ip	m_dwIP;			//IP

	u8		m_byChanNum;	//配置的通道个数
	THduChanInfo	m_atChanInfo[HDU_MAX_CHANNEL_NUM];
	TTPName			m_tName;

	BOOL32			m_bBrdReg;	//板子是否注册
	BOOL32			m_bServiceReg;	//业务是否注册

	tagTHduCfg()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTHduCfg));

		m_byLayer = (u8)TP_INVALID_INDEX;
		m_bySlot = (u8)TP_INVALID_INDEX;
		for (u8 byIndex = 0; byIndex < HDU_MAX_CHANNEL_NUM; ++byIndex)
		{
			m_atChanInfo[byIndex].Clear();
		}
	}

	tagTHduCfg& operator =(const tagTHduCfg& tCfg)
	{
		if( this == &tCfg )
		{
			return *this;
		}

		m_byLayer = tCfg.m_byLayer;
		m_bySlot = tCfg.m_bySlot;
		m_dwIP = tCfg.m_dwIP;
		m_byChanNum = tCfg.m_byChanNum;

		for (u8 byIndex = 0; byIndex < HDU_MAX_CHANNEL_NUM; ++byIndex)
		{
			m_atChanInfo[byIndex] = tCfg.m_atChanInfo[byIndex];
		}
		m_tName.SetAlias(tCfg.m_tName.m_abyAlias);
		m_bBrdReg = tCfg.m_bBrdReg;
		m_bServiceReg = tCfg.m_bServiceReg;

		return *this;
	}

}THduCfg;

//电视墙风格单元格信息，针对维护工具
typedef struct tagTHduStyleUnit
{
	u8		m_byLayer;		//层号
	u8		m_bySlot;		//槽号
	u8		m_byChanIndex;	//通道号
	TTPName m_tName;        //配置名

	tagTHduStyleUnit()
	{
		Clear();
	}

	void Clear()
	{
		m_byLayer = HDU_MAX_LAYER;
		m_bySlot  = HDU_MAX_SLOT;
		m_byChanIndex = HDU_MAX_CHANNEL_NUM;
		m_tName.Clear();
	}
}THduStyleUnit;

typedef struct tagTHduStyleData
{
	u8		m_byRow;
	u8		m_byCol;
	
	THduStyleUnit m_atUnits[HDU_STYLE_MAX_NUM];

	tagTHduStyleData()
	{
		Clear();
	}

	void Clear()
	{
		m_byRow = 0;
		m_byCol = 0;

		for (u16 wIndex = 0; wIndex < HDU_STYLE_MAX_NUM; ++wIndex)
		{
			m_atUnits[wIndex].Clear();
		}
	}

}THduStyleData;

typedef struct tagTHduUnitPlayInfo
{
	u16		m_wConfID;		//会议ID
	u16		m_wDstID;
	u16		m_wScreenNum;	//屏号
	EmViewEpType		m_emType;
	EmTPHduRunStatus	m_emStatus;

	tagTHduUnitPlayInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_wConfID = 0;
		m_wDstID = 0;
		m_wScreenNum = 0;
		m_emType = EmEpType_Invalid;
		m_emStatus = emTPHduIdle;
	}

}THduUnitPlayInfo;

//电视墙预案，针对UMC
typedef struct tagTHduPlanUnit
{	
	BOOL32	m_bReged;	//在线状态
	u16		m_wIndex;	//索引
	TTPName	m_tHduName;	//HDU 配置名
	BOOL32	m_bVmp;
	u8		m_byVol;
	BOOL32	m_bMute;

	THduUnitPlayInfo	m_atPlayInfo[HDU_MAX_VMP_SUBCHAN];
	
	tagTHduPlanUnit()
	{
		Clear();
	}
	
	void Clear()
	{
		memset(this, 0, sizeof(tagTHduPlanUnit));
	}
}THduPlanUnit;

typedef struct tagTHduPlanData
{
	u8		m_byRow;
	u8		m_byCol;
	
	THduPlanUnit m_atUnits[HDU_STYLE_MAX_NUM];
	
	tagTHduPlanData()
	{
		Clear();
	}
	
	void Clear()
	{
		memset(this, 0, sizeof(tagTHduPlanData));
	}

}THduPlanData;

typedef struct tagTHduStyleInfo
{


	u8		m_byLayer;			//对应的层号
	u8		m_bySlot;			//对应的槽号
	u8		m_byChanIndex;		//通道号
	TTPName	m_tName;			//名称

	tagTHduStyleInfo()
	{
		Clear();
	}

	void Clear()
	{


		m_byLayer = HDU_MAX_LAYER;
		m_bySlot  = HDU_MAX_SLOT;
		m_byChanIndex = HDU_MAX_CHANNEL_NUM;
		
		m_tName.Clear();
	}
}THduStyleInfo;

//End to add.

//Added by meifang
//网管服务器配置信息
typedef struct tagTTPNMServerCfg
{

	BOOL32 bIsServerOn;
	u32_ip dwNMServerIP;   //告警主机地址
	u16    wNMGetSetPort;  //读写端口，默认为161
	u16    WNMTrapPort;    //发警告端口，默认为162
 	s8     achNMReadCommunity[MAX_COMMUNITY_LENGTH];  //默认为public
 	s8     achNMWriteCommunity[MAX_COMMUNITY_LENGTH];//默认为kdv123 
	u16    wNMServerNO;

	public:
	tagTTPNMServerCfg()
	{
		memset( this, 0, sizeof(struct tagTTPNMServerCfg) );
	}

}TTPNMServerCfg;
//End to add

//Add by tanxiaodong 2012-11-19.
//系统使用信息
typedef struct tagTTPSysInfo
{
	u8 m_byCpuRate;    //CPU使用率
	u32 m_dwTotalByte; //内存总量
	u32 m_dwAllocByte; //已使用内存

public:
	tagTTPSysInfo()
	{ 
		memset( this, 0, sizeof(struct  tagTTPSysInfo));
	}
}TTPSysInfo;

//TPad列表信息
typedef struct tagTTPTPadList
{
	u32_ip m_adwTPadIP[TPAD_MAX_NUM];
	u8  m_byTPadNum;
	u8  m_byUserId[TPAD_MAX_NUM];
	u32 m_dwTPadNode[TPAD_MAX_NUM];
	s8  m_aachTPadVersion[TPAD_MAX_NUM][MAX_DEVICEVER_LEN];

public:
	tagTTPTPadList()
	{ 
		memset( this, 0, sizeof(struct  tagTTPTPadList));
	}
}TTPTPadList;

//卡农麦克配置信息
typedef struct tagTTPSingleAudioPortCfg
{
	u8               byMicVolume;//增益
	BOOL             bIsSimplexPoweringOpened; //卡农麦克幻象供电开关
	u8               byAudioBNA;//背景噪声
	tagTTPSingleAudioPortCfg()
	{
		memset( this, 0, sizeof(struct tagTTPSingleAudioPortCfg) );
	}
}TTPSingleAudioPortCfg;

//音频接口配置信息
typedef struct tagTTpAudioPortInfo
{
	u8 m_byGroupIndex;   //音频接口的组索引号
	BOOL m_abAudioPort[AUDIO_PORT_NUM]; //是否选用音频接口
	u8 m_abyVolume[AUDIO_PORT_NUM];     //选中接口的音量
	TTPSingleAudioPortCfg m_atSingleAudioPortCfg[AUDIO_PORT_NUM];
public:
	tagTTpAudioPortInfo()
	{ 
		memset( this, 0, sizeof(struct  tagTTpAudioPortInfo));
	}
}TTpAudioPortInfo;


//视频接口配置信息
typedef struct tagTTPVideoPortInfo
{
	EmSwitchState emVideoState;   //视频状态
	EmTpVideoResolution m_emRes;  //分辨率
	u8 m_byFrameRate;             //帧率
	BOOL m_bIsHaveVideoSrcOutput; //是否有视频输出(用于视频输入接口的测试)
	u8 m_byVolum;                 //音量大小(用于演示源中的音频音量)

public:
	tagTTPVideoPortInfo()
	{ 
		memset( this, 0, sizeof(struct  tagTTPVideoPortInfo));
	}
}TTPVideoPortInfo;

//视频诊断接口结构体：
typedef struct tagTTPVideoDiagInfo
{
	//摄像机1,2,3视频接口输入信息
	TTPVideoPortInfo m_atPrimVideoInputPort[MAX_PRIM_VIDEO_INPUT_PORT_NUM];	

	//摄像机1,2,3视频接口输出信息
	TTPVideoPortInfo m_atPrimVideoOutputPort[MAX_PRIM_VIDEO_OUTPUT_PORT_NUM];

	u8 m_byInputDemoIndex;//选择输入演示源索引
	TTPVideoPortInfo m_tDemoVideoInputPort;//演示源输入接口信息

	u8 m_byOutputDemoIndex;//选择输出演示源索引
	TTPVideoPortInfo m_tDemoVideoOutputPort;//演示源输出接口信息

public:
	tagTTPVideoDiagInfo()
	{ 
		memset( this, 0, sizeof(struct  tagTTPVideoDiagInfo));
	}
}TTPVideoDiagInfo;

//音频诊断接口结构体：
typedef struct tagTTPAudioDiagInfo
{
	//3组音频输入接口信息
	TTpAudioPortInfo m_atPrimAudioInputPort[MAX_PRIM_AUDIO_INPUT_PORT_NUM];
	
	//3组音频输出接口信息
	TTpAudioPortInfo m_atPrimAudioOutputPort[MAX_PRIM_AUDIO_OUTPUT_PORT_NUM];

	//添加演示音频输入接口
	BOOL m_abDemoAudioPort[MAX_DEMO_AUDIO_PORT_NUM];
	
public:
	tagTTPAudioDiagInfo()
	{ 
		memset( this, 0, sizeof(struct  tagTTPAudioDiagInfo));
	}
}TTPAudioDiagInfo;

//上下行网络速率信息结构体
typedef struct tagTTPUpDownNetSpeedInfo
{
	u32 m_dwInputByteDvalue;//下行流入的字节数
    u32 m_dwOutputByteDvalue;//上行流出的字节数
	
public:
	tagTTPUpDownNetSpeedInfo()
	{ 
		memset( this, 0, sizeof(struct  tagTTPUpDownNetSpeedInfo));
	}
}TTPUpDownNetSpeedInfo;

//上下行网络速率结构体
typedef struct tagTTPUpDownSpeedInfo
{
	u16 m_wUpSpeed;  //上行速率
	u16 m_wDownSpeed;//下行速率

public:
	tagTTPUpDownSpeedInfo()
	{ 
		memset( this, 0, sizeof(struct  tagTTPUpDownSpeedInfo));
	}
}TTPUpDownSpeedInfo;

typedef struct tagTTPVgaMixInfo
{
	//当前选择演示源输入接口
	EmVgaType m_emCurrentType;

	//当前选择演示源输出接口
	EmDualOutputType m_emDualOutputType;

	//演示源输出接口名称
	s8 m_achVgaOutputFstName[MAX_ALIAS_LEN];
	s8 m_achVgaOutputSndName[MAX_ALIAS_LEN];

public:
	tagTTPVgaMixInfo()
	{ 
		memset( this, 0, sizeof(struct  tagTTPVgaMixInfo));
	}
}TTPVgaMixInfo;
//End to add.

//Add by zhangapei
//摄像机配置信息
typedef struct tagTCnCameraCfg
{
	//开启调用预置位1
	BOOL         bUsed; 
	EmCamType    emCamType;     //摄像机类型
	u8           byAddr;        //摄像机地址
	EmSerialType emSerialType;
	u32_ip       dwSerialServerIP; //串口服务器IP ,当该值为0时表示使用本地串口
    u16          wSerialServerPort; //串口服务器端口号  0

	//视野大小
 	u16             wZoom; 
  EmFocusMode     emFocusMode;//聚焦模式
	//在OSD上显示视野比例
    EmOSDShow       emOSDShow;
	//曝光模式
	EmExpMode       emExpMode;
	//手动曝光
	EmGain          emGain;//增益 
	EmShutSpd       emShutSpd; //快门
	EmBackLightType emBackLightType; //背光补偿
	u8              byMulti; //多点背光强度设置
	u8              byApt;//曝光光圈值
	//白平衡模式
	EmWBMode        emWBMode;
	//手动白平衡 
	u16             wRGain; //颜色R 值
    u16             wBGain; //颜色B 值
	//场景模式
	EmPicSceMode    emPicSceMode; 
	//手动场景模式
	EmGamma         emGamma; //场景Gamma值
	u8              byPicApt;//场景光圈值
	//图片调节
	u16             wContrast; //对比度
	u16             wHue;      //色度
	u16             wSaturat;  //饱和度
	u16             wBright;   //亮度
    EmStmClean      emStmClean; //降噪
	Em3DNR          em3DNR;     //机芯3D降噪设置

	BOOL            bStmClen;   //sony降噪开关
	u8				byLevel;    //sony降噪调节
	BOOL            bBackLight; //Sony背光补偿


	EmSensitivity	emFocusSensitivity;	//自动调焦灵敏度
	u8				byGainValue;		//增益 
	u8				byGainLimit;		//增益限制
	EmAntiFlicker	emAntiFlicker;		//抗闪烁
	EmSpotLighet	emSpotLighet;		//聚光灯
	u16				wSpotLighetX;		//聚光灯坐标
	u16				wSpotLighetY;		//聚光灯坐标
	u16				wExposureComp;		//曝光补偿
	u8				byBackLightLevel;	//背光等级
	EmWideDynamics	emWideDynamics;		//宽动态
	u8				byWideDynamicsLevel;//宽动态级别
	u8				byColorTemperature;	//固定色温
	EmPicEffect		emPicEffect;		//图片特效
	EmPicFlip		emPicFlip;			//图片翻转
	EmPicMode		emPicMode;			//画面模式
	u16				wPicSharpness;		//锐度
	u8				byPicGamma;			//伽马
	u8				by2DNRValue;		//2D降噪
	u8				by3DNRValue;		//3D降噪
	EmResolution	emOutputResolution;	//分辨率
	EmBaudRate		emBaudRate;			//波特率
	u32				dwIp;			//IP地址    
	u32				dwMask;			//子网掩码
	u32				dwGateWay;		//网关地址
    
	public:
		tagTCnCameraCfg()
		{
			memset( this, 0, sizeof(struct tagTCnCameraCfg) );
		}
		
}TCnCameraCfg;

/************************************************************************/
/* 相机网络配置                                               */
/************************************************************************/
typedef struct tagTCamNet
{
	u32  dwIp;			//IP地址    
	u32  dwMask;		//子网掩码
	u32  dwGateWay;		//网关地址
public:
	tagTCamNet(){memset(this , 0 ,sizeof( struct tagTCamNet) );	}
}TCamNet, *PTCamNet;

typedef struct tagTTPSerialInfo
{
	EmSerialType emSerialType;
	TSerialCfg   tSerialCfg;
}TTPSerialInfo;


typedef struct tagTTVAct
{
	u16         wEvent;   //电视机操作动作反馈消息
	u8          byemType; //操作类型
	u8          byTVIndx;
	time_t      ttime;    //
    
	public:
		tagTTVAct()
		{
			memset( this, 0, sizeof(struct tagTTVAct) );
		}
		
}TTVAct;

typedef struct tagTCenDevSleepInfo
{
	BOOL   bSleepUsed;      // 是否启用自动待机
	u32    wSleepWaitTime;  // 待机等待时间 (s)     
	public:
		tagTCenDevSleepInfo()
		{
			memset( this, 0, sizeof(struct tagTCenDevSleepInfo) );
		}
}TCenDevSleepInfo;

//窗帘名称
typedef struct tagTCentreCurName
{
    s8  achCurName[MAX_CURNAME_LEN];
	public:
		tagTCentreCurName()
		{
			memset( this, 0, sizeof(struct tagTCentreCurName) );
		}
		
}TCentreCurName;

//end to add

//Add by panhaiyang中控文档摄像头和施耐德电气配置信息

typedef struct tagTDCamPresetInfo
{
	u16               wZoom;			   //视野大小
	EmDCamAFMode      emDCamAFMode;        //文档摄像头自动聚焦状态
	EmExpMode		  emDCamExpMode;       //文档摄像机曝光
	EmDCamIris        emDCamIris;          //文档摄像机曝光--光圈
	EmDCamShutSpd     emDCamShutSpd;       //文档摄像机曝光--快门
	EmDCamGain        emDCamGain;          //文档摄像机曝光--增益
	EmDCamWBMode      emDCamWBMode;        //文档摄像头白平衡模式
	u16				  wRGain;
	u16				  wBGain;

	public:
	tagTDCamPresetInfo()
	{
		memset( this, 0, sizeof(struct tagTDCamPresetInfo) );
	}

}TDCamPresetInfo;


typedef struct tagTCentreDCamCfg
{
	BOOL              bDCamUsed;		   //是否有文档摄像机
	EmSerialType      emSerialType;        //文档摄像机连接串口类型
	EmDCamPower       emDCamPowerMode;     //文档摄像头开关状态 
	EmDCamRecallNum	  emDCamRecallNum;
	BOOL              bRecallPresetOne;    //开机是否自动调用预置位1
	TDCamPresetInfo   tDCamCurPresetInfo;  //当前的摄像机的信息
	TDCamPresetInfo   tDCamPresetInfo[MAX_DCAMPRESET_NUM];  //三个预置位信息
	EmDCamProType     emDcamProType;			//文档摄像机协议类型
    
	public:
		tagTCentreDCamCfg()
		{
			memset( this, 0, sizeof(struct tagTCentreDCamCfg) );
		}
		
}TCentreDCamCfg;

typedef struct tagTCentreSchCfg
{
	EmSchGatewayType  emCenSchGateType;    //施耐德网关类型
	EmSerialType      emSerialType;        //施耐德串口类型
	EmSchPower        emSchPower;          //会议室系统电源开关状态 
	EmSchLight        emSchLight;          //会议室灯光电源开关状态
	EmSchMidLight     emSchMidLight;       //会议室顶上灯光电源开关状态
    EmSchScrLight     emSchScrLight;       //会议室机柜面光灯电源开关状态
	u16               wSchTem;             //会议室室内温度
    
	public:
		tagTCentreSchCfg()
		{
			memset( this, 0, sizeof(struct tagTCentreSchCfg) );
		}
		
}TCentreSchCfg;

//End Add

//空调信息 add by zhangapei
typedef struct tagTCentreACCfg
{
	u8                byID;          //空调
	EmSerialType      emSerType;
	EmCentreACPower   emACPower;     //空调开关
	u8                bySetTemp;     //空调温度
	u8				  byCurTemp;     //实时温度
	EmCentreACAirVol  emACAirVol;    //新风风量
	EmCentreACMode    emACMode;      //空调模式
	
	public:
		tagTCentreACCfg()
		{
			memset( this, 0, sizeof(struct tagTCentreACCfg) );
		}
}TCentreACCfg;

typedef struct tagTCentreACInfo
{
	TCentreACCfg  tCentreACCfg[MAX_AC_NUM];		//空调具体配置
	u8            byACNum;					//空调台数 1、3
	BOOL          bACFlag[MAX_AC_NUM];		//空调标志位

	public:
		tagTCentreACInfo()
		{
			memset( this, 0, sizeof(struct tagTCentreACInfo) );
		}
}TCentreACInfo;


//end add


//单板操作结果
typedef struct tagTOprBoardResult
{
	u8					m_byBrdLayer; //单板层号
	u8                  m_byBrdSlot;  //单板槽位号
	EmTpBoardRet        m_emReason;
public:	
	tagTOprBoardResult()
	{
		memset(this, 0, sizeof(tagTOprBoardResult));
	}
}TOprBoardResult;
typedef struct tagTTPBrdPos
{
    EMBrdType	m_emBrdType;            /* 板子类型 */
    u8			m_byBrdLayer;           /* 板子所在层号 */
    u8			m_byBrdSlot;            /* 板子所在槽位号 */
	u32_ip		m_dwBrdIP;				/* 板子IP */
public:	
	tagTTPBrdPos(){Clear();}
	
	void Clear()
	{
		memset(this, 0, sizeof(tagTTPBrdPos));
		m_byBrdLayer = (u8)TP_INVALID_INDEX;
		m_byBrdSlot = (u8)TP_INVALID_INDEX;
	}
	
	BOOL32 operator == (const tagTTPBrdPos& tBrdPos)
	{
		return ( (m_emBrdType == tBrdPos.m_emBrdType) && (m_byBrdLayer == tBrdPos.m_byBrdLayer)
			&& (m_byBrdSlot == tBrdPos.m_byBrdSlot) && (m_dwBrdIP == tBrdPos.m_dwBrdIP) );
	}
	
}TTPBrdPos;

typedef struct tagTTPBrdCfg
{
	u8			m_byBrdID;				/*板子ID*/
	TTPBrdPos	m_tBrdPos;				/*板子位置*/
	
	tagTTPBrdCfg(){Clear();}
public:	
	tagTTPBrdCfg& operator = ( const tagTTPBrdCfg& tBrdCfg)
	{
		if ( &tBrdCfg == this )
		{
			return *this;
		}
		
		memcpy(this, &tBrdCfg, sizeof(tBrdCfg));
		
		return *this;
	}
	
	void Clear()
	{
		memset(this, 0, sizeof(tagTTPBrdCfg));
		m_tBrdPos.Clear();
	}
	
}TTPBrdCfg;

//单板模式信息
typedef struct tagTTPEqpCfg
{
	u8				m_byEqpID;			//ums分配 用来和mcu侧外设通信用 根据外设类型需要一个统一的分配算法
	EMEqpType		m_emEqpType;		// 外设类型
	EMEqpModleType	m_emEqpMdlType;		//外设模式 basic*2 或者 ehance
	s8				m_szEqpAlias[TP_MAXLEN_EQP_ALIAS];//外设别名
	
	u8				m_byBrdID;			//brdID
	u8              m_byBrdLayer;
	u8              m_byBrdSlot;
	//以下参数针对APU2板
	u8				m_byAudmixNum;      //记录混音器路数
	tagTTPEqpCfg(){Clear();}
	
	tagTTPEqpCfg& operator = ( const tagTTPEqpCfg& tEqpCfg)
	{
		if ( &tEqpCfg == this )
		{
			return *this;
		}
		
		memcpy(this, &tEqpCfg, sizeof(tEqpCfg));
		
		return *this;
	}
	
	void Clear()
	{
		memset(this, 0, sizeof(tagTTPEqpCfg));
	}
	
}TTPEqpCfg;

//单板模式配置
typedef struct tagTTPMdlCfg
{
	EMEqpType		m_emEqpType;		// 外设类型
	EMEqpModleType	m_emEqpMdlType;		//外设模式 basic*2 或者 ehance
	s8				m_szEqpAlias[TP_MAXLEN_EQP_ALIAS];//外设别名
	u16				m_wEqpId;
	
	//以下参数针对APU2板子模式
	u8				m_byAudmixNum;      //每个混音器最大混音路数
public:	
	tagTTPMdlCfg(){Clear();}
	
	void Clear()
	{
		memset(this, 0, sizeof(tagTTPMdlCfg));
	}
}TTPMdlCfg;

//单板信息
typedef struct tagTTPBrdInfo
{
	TTPBrdCfg m_tBrdCfg;  //板子信息
	TTPMdlCfg m_tBrdMode[TP_UMS_BRD_MAXNUM_EQP]; //板子模式信息
	BOOL32    m_bReg;     //板子是否注册
	BOOL32	  m_abEqpReg[TP_UMS_BRD_MAXNUM_EQP]; //外设是否注册
	BOOL32    m_bBrdUsed; //板子是否分配使用
public:
	tagTTPBrdInfo(){Clear();}
	void Clear()
	{
		memset(this, 0, sizeof(tagTTPBrdInfo));	
		m_tBrdCfg.Clear();
	}
	
}TTPBrdInfo;

typedef struct tagTTPBrdMdlInfo
{
	u8			m_byLayer;
	u8			m_bySlot;
	
	u8			m_byIndex;//板子外设数组索引
	TTPMdlCfg	m_atMdlCfg[TP_UMS_BRD_MAXNUM_EQP];
public:
	tagTTPBrdMdlInfo(){Clear();}
	
	void Clear()
	{
		m_byLayer = (u8)TP_INVALID_INDEX;
		m_bySlot = (u8)TP_INVALID_INDEX;
		for (u8 byIndex = 0; byIndex < TP_UMS_BRD_MAXNUM_EQP; byIndex++)
		{
			m_atMdlCfg[byIndex].Clear();
		}
	}
}TTPBrdMdlInfo;

//板子占用情况
typedef struct tagTTPBrdUsedInfo
{
	EMEqpType	m_emType;
	u16			m_wRegNum;  //注册数
	u16			m_wUsedNum; //使用数
public:
	tagTTPBrdUsedInfo(){Clear();}

	void Clear()
	{
		memset(this, 0, sizeof(tagTTPBrdUsedInfo));
	}
}TTPBrdUsedInfo;

//单板升级
typedef struct tagTTPBrdUpGrade
{
	u8 m_byLayer;
	u8 m_bySlot;
	s8 m_szFileName[TP_UPGRADE_FILENAME_LENGTH];
	tagTTPBrdUpGrade(){Clear();}
	void Clear()
	{
		m_byLayer = (u8)TP_INVALID_INDEX;
		m_bySlot = (u8)TP_INVALID_INDEX;
		memset(m_szFileName, 0, sizeof(TP_UPGRADE_FILENAME_LENGTH));
	}
}TTPBrdUpGrade;

//
typedef struct tagTTPAudPower
{
	u8 abyInput[emTPAudInDigit0];
	u32 adwOutput[TP_AUDIO_CODEC_NUM];
	tagTTPAudPower()
	{
		memset(this, 0, sizeof(tagTTPAudPower));
	}

}TTPAudPower;

typedef struct tagTTPHdAudioPort
{
	u8 abHdAudPortIn[emTPAudInEnd];
	u8 byPos;
public:
	tagTTPHdAudioPort(){ memset( this ,0 ,sizeof( struct  tagTTPHdAudioPort ) );}
	
}TTPHdAudioPort;

typedef struct tagTTPHdAudioOutPort
{
	u8 abHdAudPortOut[emTPAudOutEnd];
	u8 byPos;
public:
	tagTTPHdAudioOutPort(){ memset( this ,0 ,sizeof( struct  tagTTPHdAudioOutPort ) );}
	
}TTPHdAudioOutPort;

typedef struct tagTTPHdDualAudioPort
{
	u8 abHdAudPortIn[emTPDualAudInEnd];
	u8 byPos;
public:
	tagTTPHdDualAudioPort(){ memset( this ,0 ,sizeof( struct  tagTTPHdDualAudioPort ) );}
}TTPHdDualAudioPort;

//编解码器音频信息
typedef struct tagTTPMPAudioInfo
{
	BOOL                 m_bIsAECEnable;//是否启用回声抵消
	BOOL                 m_bIsAGCEnable;//是否启用自动增益
	BOOL                 m_bIsANSEnable; //是否启动自动噪音抑制
	EmTpAudioFormat      m_emAudioFormatPriorStrategy;//音频编码优先策略
	u8                   m_byInputVolume;//输入音量（编码音量）
	u8                   m_byOutputVolume;//输出音量（解码音量）
	EmTPLoudspeakerVal   m_emLoudspeakerVal; //扬声器音量值（T2版本）
	//维护工具上音频设置的音频输出增益 add by wangqichang
	u8                   m_abyOutputGain[emEndMPCodec - 1];
	//end

	
	public:
		tagTTPMPAudioInfo()
		{
			memset( this, 0, sizeof(tagTTPMPAudioInfo) );
		}
}TTPMPAudioInfo;

//高清输出模式帧率
typedef struct tagTTPVideoDisplayFrm
{
    u32 m_dw1080PFrm;
    u32 m_dw1080IFrm;
    u32 m_dwVGAFrm;
    u32 m_dw720PFrm;
    u32 m_dwSDFrm;
public:
	tagTTPVideoDisplayFrm()
	{
		memset( this, 0, sizeof( struct tagTTPVideoDisplayFrm ) );
    }
}TTPVideoDisplayFrm, *PTTPVideoDisplayFrm;

/************************************************************************/
/*视频参数体信息数据结构定义                                            */
/************************************************************************/
typedef struct tagTTPVideoParam 
{
    BOOL  bUseFixedFrame;    //使用固定帧 
    u8 byFrameRate;	///帧率
    EmTPFrameUnitType  emFrameUnit;	//帧率单位
    u8 byQualMaxValue;	//最小量化参数
    u8 byQualMinValue;	//最大量化参数
    u16 wIKeyRate;	//关键帧间隔
    EmTpEncodeMode emEncodeMode;     //编码方式
    EmTpLostPackageRestore emRestoreType; //丢包恢复方式
    u16 wH264IKeyRate;		//H264关键帧间隔
    u8  byH264QualMaxValue;	//H264最大量化参数
    u8  byH264QualMinValue;	//H264最小量化参数
	//以下参数只有在windows下才有用
	//添加采集图像宽高
	u16	wWidth; //视频捕获图像宽度 仅Windows有效(default:640)
	u16	wHeight;//视频捕获图像高度 仅Windows有效(default:480)
	EmTpMediaType   emCapType;    //采集类型   (default:emMediaAV)
	EmTpPCCapFormat emPCCapFormat;//视频捕获帧格式 仅Windows有效(default:emCapPCFrameBMP)
	//以下参数，针对高清终端, 
	u8 by720pFrameRate; //720p分辨率下帧率
	u8 byVgaFrameRate;  //双流vga下帧率
	//xjx_080612
	u8 byD1FrameRate; //D1分辨率下帧率
	
	//新添加成员
	u32 dwProfile;
	u32	dwAvgQpI;
	u32	dwAvgQpP;
	u16 wChanMaxBitrate; 
public:
	tagTTPVideoParam(){ memset( this ,0 ,sizeof( struct  tagTTPVideoParam ) );}	
}TTPVideoParam, *PTTPVideoParam;

//	图像调整参数
typedef struct tagTTPImageAdjustParam
{	 
	u8  wBrightness;//亮度  	 
	u8  wContrast;   //对比度  	
	u8  wSaturation; //色彩饱和度
	u8  byNoiseReduction; //降噪
	u8  byChroma;//图像色度

public:
	tagTTPImageAdjustParam(){ memset( this ,0 ,sizeof( struct  tagTTPImageAdjustParam ) );}
	
}TTPImageAdjustParam, *PTTPImageAdjustParam;

//视频信息
typedef struct tagTTPVideoInfo
{
	//修改成记录三路的,视频源信息则移到TTPVideoInfoTool中-----by wangqichang
	TTPImageAdjustParam    m_atImageAdjustParam[emEndMPCodec - 1];//视频图像调整参数
	//修改结束

	EmTpVideoFormat        m_emVideoFormatPriorStrategy;//视频编码优先策略
	EmTpVideoResolution    m_emVideoResolvePriorStrategy;//视频分辨率优先策略
	EmTPVideoStandard      m_emOutVideoStandard;//视频输出标准
	EmTPVideoStandard      m_emInVideoStandard;//视频输入标准
	//EmTPVideoPort         m_emVideoSource;//视频源
	public:
		tagTTPVideoInfo(){memset(this,0,sizeof(struct tagTTPVideoInfo));}
}TTPVideoInfo, *PTTPVideoInfo;

// TsymboPoint台标位置结构
typedef struct tagTTPSymboPoint
{
	u16 X;
	u16 Y;
public:
	tagTTPSymboPoint(){ memset( this, 0, sizeof( struct  tagTTPSymboPoint ) );}
}TTPSymboPoint;

/************************************************************************/
/*8010c配置vga输出参数                                               */
/************************************************************************/
typedef struct tagTTPVgaOutCfg
{
	BOOL bVgaOut; //8010c是否在vga上输出
	u16  wRefreshRate; //vga的刷新率
 public:
	 tagTTPVgaOutCfg(){memset(this, 0, sizeof( struct tagTTPVgaOutCfg) );	}
	 tagTTPVgaOutCfg( BOOL bOut, u16 wRate ){ bVgaOut = bOut; wRefreshRate = wRate; }
}TTPVgaOutCfg;

// FEC配置信息结构
typedef struct tagTTPFecInfo
{
	BOOL   m_bEnableFec;   //视频是否使用前向纠错
	u8     m_byAlgorithm;  //设置fec算法 0:NONE 1:RAID5 2:RAID6
	u16    m_wPackLen;     //设置fec的切包长度
	BOOL   m_bIntraFrame;  //是否帧内fec
	u32    m_dwDataPackNum; //设置fec的x包数据包
	u32    m_dwCrcPackNum;  //设置fec的y包冗余包
public:
	tagTTPFecInfo(){ memset( this, 0, sizeof( struct tagTTPFecInfo ) ); }
}TTPFecInfo, *PTTPFecInfo;

/************************************************************************/
/* 码流重传信息数据结构定义                                               */
/************************************************************************/
typedef struct tagTTPLostPackResend
{
	BOOL bUse;             //是否启用
	EmTPNetType emNetType;   //网络类型
	u8   byResendLevel;    //重传等级 0<低,重传一次> 1<中,重传两次> 2<高,重传三次>
	u16  wFirstTimeSpan;   //第一个重传检测点   default 40
	u16  wSecondTimeSpan;  //第二个重传检测点   default 80
	u16  wThirdTimeSpan;   //第三个重传检测点   default 160
	u16  wRejectTimeSpan;  //过期丢弃的时间跨度 default 200
	u16  wSendBufTimeSpan; //发送缓存           default 1000
	BOOL bUseSmoothSend;   //启用平滑发送
	BOOL bUseAdaptSend;  //双流视频适配是否设置重传参数
public:
	tagTTPLostPackResend(){ memset( this, 0, sizeof( struct  tagTTPLostPackResend ) );}
}TTPLostPackResend, *PTPTLostPackResend;

//丢包时自动降低码率配置
typedef struct tagTTPBitRateAdjust
{
	BOOL bEnable;   //是否启动
	u16  wInterval;  //时间间隔
	u16  wLostTimes; //丢包次数
	u16  wDescRatio; //降速比率
	u16  wLowDescRatio; //慢速降速码率
	u16  wDelayInterval;  //延迟时间
public:
	tagTTPBitRateAdjust(){ memset( this ,0 ,sizeof( struct  tagTTPBitRateAdjust ) );}
}TTPBitRateAdjust,*PTTPBitRateAdjust;


typedef struct tagTTPVideoStandard
{
	EmTPVideoType     emVideoType;
	BOOL            bIsInPort;    //是否为输入端口
	EmTPVideoStandard emStandard;
public:
	tagTTPVideoStandard(){ memset( this ,0 ,sizeof( struct  tagTTPVideoStandard ) );}	
}TTPVideoStandard ,*PTTPVideoStandard;

//视频端口
typedef struct tagTTPVideoPort
{
	u8 byIndex;
	EmTPMtVideoPort emTPMtVideoPort;//视频输入端口
	EmTPMtVideoOutPort emTPMtVideoOutPort; //视频输出端口
	EmTPDVIMode emTPDVIInMode;//输入视频类型
	EmTPDVIMode emTPDVIOutMode;//输出视频类型
	EmTPDVIMode emTPDVI5OutMode;//输出视频类型,dvi5专用
public:
	tagTTPVideoPort()
	{
		emTPDVIInMode = TP_DVI_MODE_DVI;
		emTPDVIOutMode = TP_DVI_MODE_INVALID;
		emTPDVI5OutMode = TP_DVI_MODE_INVALID;
		emTPMtVideoOutPort = emTPVidOutEnd;
		emTPMtVideoPort = emTPVidEnd;
	}
}TTPVideoPort;

// 接口测试结构
typedef struct tagTTPAutoTestMsg
{	
    // 测试类别
    EmTPAutoTestType m_emAutoTestType;
    // 开始测试标志位：TRUE，开始测试；FALSE，停止测试
    BOOL m_bAutoTestStart;
    // 视频类型
    EmTPVideoType m_emVideoType;
    // 视频端口	
	TTPVideoPort tTPVideoPort;

	TTPHdAudioPort tTPHdAudioPort;
	//双流音频
	TTPHdDualAudioPort tTPHdDualAudioPort;
	
	//音频输出
	TTPHdAudioOutPort tTPHdAudioOutPort;

	u8 byIndex;
	//编解码器总个数
	u8 byMPCodecNum; 
	
public:
	tagTTPAutoTestMsg(){ memset( this ,0 ,sizeof( struct  tagTTPAutoTestMsg ) );}
}TTPAutoTestMsg;

//均衡器设置
typedef struct tagTTPEqualizer
{	
//    EmTPEqualizerRate emTPEqualizerRate; //均衡器频率点
	s32 anEqualizerGain[EQUQLIZER_FREQUENCY_NUM]; //均衡器增益 
	BOOL bEqualizer;  //开启/关闭均衡器	
	u8 byIndex;
	
public:
	tagTTPEqualizer(){ memset( this ,0 ,sizeof( struct  tagTTPEqualizer ) );}
}TTPEqualizer;

//画中画设置
typedef struct tagTTPPIPMod
{	
    EmTPPIPMode emTPPIPMode;
	u8 byIndex;
	
public:
	tagTTPPIPMod()
	{
		Clear();		
	}

	void Clear()
	{
		byIndex = emEndMPCodec;
		emTPPIPMode = TP_VIDEO_PIPMODE_IDLE;
	}

}TTPPIPMod;


typedef struct tagTTPLostFrameRate
{
	u8 byLostFrameRate;//丢包率
	TTpCodecComponent tTpCodc;
	BOOL bvalid;//是否有效
public:
	tagTTPLostFrameRate()
	{
		memset( this ,0 ,sizeof( struct  tagTTPLostFrameRate ) );
		bvalid = FALSE;
	}
}TTPLostFrameRate;


typedef struct tagTTPVideoRecv
{
	u8  abyVEncRecv[emEndMPCodec]; //编码器有没有视频源输入
	u8  abyVDecRecv[emEndMPCodec]; 

public:
	tagTTPVideoRecv()
	{
		memset( this ,0 ,sizeof( struct  tagTTPVideoRecv ) );		 
	}
}TTPVideoRecv;


typedef struct tagTTPVideoEncDecRes
{
	EmTpVideoResolution enRes;//分辨率
	TTpCodecComponent tTpCodc;
	BOOL bvalid;//是否有效
public:
	tagTTPVideoEncDecRes()
	{
		memset( this ,0 ,sizeof( struct  tagTTPVideoEncDecRes ) );
		bvalid = FALSE;
	}
}TTPVideoEncDecRes;

//从编解码器获取实际分辨率
typedef struct tagTTPVideoEncDecResPack
{
	TTPVideoEncDecRes  atVideoRes[TP_MAX_VIDEO_RES_NUM];
	u8 byNum;
	
public:
	tagTTPVideoEncDecResPack()
	{
		memset( this ,0 ,sizeof( struct  tagTTPVideoEncDecResPack ) );		 
	}
}TTPVideoEncDecResPack;


typedef struct tagTTPVideoFrameRate
{
	u16 wFrameRate;//视频帧率
	TTpCodecComponent tTpCodc;
	BOOL bvalid;//是否有效
public:
	tagTTPVideoFrameRate()
	{
		memset( this ,0 ,sizeof( struct  tagTTPVideoFrameRate ) );
		bvalid = FALSE;
	}
}TTPVideoFrameRate;

//从编解码器获取实际帧率
typedef struct tagTTPVideoFrameRatePack
{
	TTPVideoFrameRate  atVideoFrameRate[TP_MAX_VIDEO_RES_NUM];
	u8 byNum;
	
public:
	tagTTPVideoFrameRatePack()
	{
		memset( this ,0 ,sizeof( struct  tagTTPVideoFrameRatePack ) );		 
	}
}TTPVideoFrameRatePack;



typedef struct tagTTPCodecPackStat
{
	TTPVideoFrameRatePack  tTPVideoFrameRatePack;//从编解码器获取实际帧率
	TTPVideoEncDecResPack  tTPVideoEncDecResPack;//从编解码器获取实际分辨率
	TTPVideoRecv           tTPVideoRecv;  //编码器有没有视频源输入
	TTPAudPower            tTPAudPower; //音频功率
	
public:
	tagTTPCodecPackStat()
	{
		memset( this ,0 ,sizeof( struct  tagTTPCodecPackStat ) );		 
	}
}TTPCodecPackStat;


typedef struct tagTTPCnDsData
{
	TTPTransAddr m_tRcvFromAddr;
	TTPTransAddr m_tSndToAddr;
	TTPTransAddr m_tMapedAddr;
	u32 m_dwType;

	void clear()
	{
		memset(this, 0, sizeof(tagTTPCnDsData));
	}
	tagTTPCnDsData()
	{
		clear();
	}
	tagTTPCnDsData& operator = (const tagTTPCnDsData& tRhs)
	{
		if (this == &tRhs)
		{
			return *this;
		}
		this->m_tRcvFromAddr = tRhs.m_tRcvFromAddr;
		this->m_tSndToAddr = tRhs.m_tSndToAddr;
		this->m_tMapedAddr = tRhs.m_tMapedAddr;
		this->m_dwType = tRhs.m_dwType;
		return *this;
	}
	BOOL operator == (const tagTTPCnDsData& tRhs)
	{
		if ( this->m_tSndToAddr.m_dwIP == tRhs.m_tSndToAddr.m_dwIP
			&&this->m_tRcvFromAddr.m_dwIP == tRhs.m_tRcvFromAddr.m_dwIP
			&&this->m_tSndToAddr.m_wPort == tRhs.m_tSndToAddr.m_wPort
			&&this->m_tRcvFromAddr.m_wPort == tRhs.m_tRcvFromAddr.m_wPort
			&&this->m_dwType == tRhs.m_dwType)
		{
			return TRUE;
		}
		return FALSE;
	}
}TTPCnDsData;

typedef struct tagTTPCnNetBufPara
{
	TTPTransAddr m_wSndAddr;			//发送RTP到接收端和发送RTCP到发送端的发送端口
	TTPTransAddr m_tRcvRtpAddr;			//netbuf接收RTP的端口
	TTPTransAddr m_tRcvRtcpAddr;		//netbuf接收RTCP的端口
	TTPTransAddr m_tRmtRtcpAddr;		//netbuf请求RTCP的远端端口
	TTPTransAddr m_tRmtRtpAddr;			//向netbuf发送rtp包的远端端口
	
	u32	 m_Handle;
	
	tagTTPCnNetBufPara()
	{
		memset(this, 0, sizeof(tagTTPCnNetBufPara));
	}
}TTPCnNetBufPara;
//重传设定
typedef struct tagTTPCnRSParam
{
    u16  m_wFirstTimeSpan;	 //第一个重传检测点(ms)
	u16  m_wSecondTimeSpan;  //第二个重传检测点(ms)
	u16  m_wThirdTimeSpan;   //第三个重传检测点(ms)
	u16  m_wRejectTimeSpan;  //过期丢弃的时间跨度(ms)
	
	tagTTPCnRSParam()
	{
		m_wFirstTimeSpan = 40;
		m_wSecondTimeSpan = 80;
		m_wThirdTimeSpan = 120;
		m_wRejectTimeSpan = 2000;
	}
}TTPCnRSParam;



typedef struct tagTTPAllConfCnsInfo
{
	TCnsInfo m_tCnsInfo[TP_CONF_MAX_CNSNUM];     //按对应EPID号存储，避免查找遍历损耗
	u16 m_wNum;     //有效个数
	
	tagTTPAllConfCnsInfo()
	{
		Clear();
	}
	
	void Clear()
	{
		for(u16 wIndex = 0; wIndex < TP_CONF_MAX_CNSNUM; ++wIndex)
		{
			m_tCnsInfo[wIndex].Clear();
		}
		
		m_wNum = 0;
	}
	
	//UMS限制，ADD和UPDATE不区分
	BOOL Add(TCnsInfo &tCnsInfo)
	{
		if( tCnsInfo.m_wEpID>=TP_CONF_MAX_CNSNUM )
		{
			return FALSE;
		}
		if( TP_INVALID_INDEX == m_tCnsInfo[tCnsInfo.m_wEpID].m_wEpID )
		{
			++m_wNum;
		}
		memcpy(&m_tCnsInfo[tCnsInfo.m_wEpID], &tCnsInfo, sizeof(TCnsInfo));

		return TRUE;
	}
	
	BOOL Update(TCnsInfo &tCnsInfo)
	{
		if( tCnsInfo.m_wEpID>=TP_CONF_MAX_CNSNUM )
		{
			return FALSE;
		}
		if( TP_INVALID_INDEX == m_tCnsInfo[tCnsInfo.m_wEpID].m_wEpID )
		{
			++m_wNum;
		}
		memcpy(&m_tCnsInfo[tCnsInfo.m_wEpID], &tCnsInfo, sizeof(TCnsInfo));

		return TRUE;
	}
	
	BOOL Del(TCnsInfo &tCnsInfo)
	{
		if(TP_INVALID_INDEX == m_tCnsInfo[tCnsInfo.m_wEpID].m_wEpID||tCnsInfo.m_wEpID>=TP_CONF_MAX_CNSNUM)
		{
			return FALSE;
		}
		else
		{
			m_tCnsInfo[tCnsInfo.m_wEpID].Clear();
			--m_wNum;
			return TRUE;
		}
	}

	BOOL UpdateOffline(TCnsInfo &tCnsInfo)
	{
		u32 dwIndex = 0;
		for (dwIndex = 0; dwIndex < TP_CONF_MAX_CNSNUM; dwIndex ++)
		{
			if ( m_tCnsInfo[dwIndex] == tCnsInfo)
			{
				m_tCnsInfo[dwIndex].m_bOnline = FALSE;
				return TRUE;
			}
		}
		return FALSE;
	}
}TTPAllConfCnsInfo, *PTTPAllConfCnsInfo;

typedef struct tagTCnDsType
{
	u32  dwHandle;
	u16  wDsType;
	u16  wSubDsType;
}TCnDsType;


//混音器的地址---huzilong
typedef struct tagTTPCnMixAddr
{
	TTPMediaTransAddr m_tRcv;		//接收地址
	TTPMediaTransAddr m_tSnd;		//发送地址(N-1)模式，CNS暂时不用

	tagTTPCnMixAddr()
	{
		memset( this, 0, sizeof( tagTTPCnMixAddr ) );
	}
}TTPCnMixAddr;





//混音通道结构体---huzilong
typedef struct tagTTPCnMixChan
{
	u16				m_wIndex;			//数组中的索引
	
	TTPCnMixAddr		m_tMixAddr;			//混音器的地址
	
	tagTTPCnMixChan()
	{
		memset( this, 0, sizeof( tagTTPCnMixChan ) );
		m_wIndex = INVALID_MIX_INDEX;
	}
	
}TTPCnMixChan;

//混音器参数----huzilong
typedef struct tagTTPCnMixParam
{

	u16             m_wCurSpeaker;                      //语音激励出当前的发言人通道号
	TTPCnMixChan		m_atAudMix[TP_CONF_MAX_AUDMIXNUM];	//混音列表,包含双流共4路
	
	TTPTransAddr	m_tNSndRtpAddr;			//N模式下混音器的发送RTP地址
	TTPTransAddr	m_tNSndMixBackRtcpAddr;	//N模式混音器的BACKRTCP地址
	
	TTPTransAddr	m_tNRcvRtpAddr;			//接收N模式RTP地址
	TTPTransAddr	m_tNRcvBackRtcpAddr;	//接收N模式RTCP地址
	
	tagTTPCnMixParam()
	{
		memset( this, 0, sizeof( tagTTPCnMixParam ) );
		m_wCurSpeaker = INVALID_MIX_INDEX;
	}

}TTPCnMixParam;

typedef struct tagTTPNetAddress
{
    u32   dwIp;     //Ip地址(网络序) 
	u16    wPort;    //端口号(网络序) 
}TTPNetAddress;

//混音通道
typedef struct tagTTPMixerChannelParam
{    
    TTPNetAddress m_tSrcNetAddr;     //通道源地址(接收对象)
    //通道源RTCP地址等于通道源地址的端口加一(接收对象)
    TTPNetAddress m_tRtcpBackAddr;   //通道RTCP回馈地址(接收对象)
	TTPNetAddress m_tRtcpLocalAddr;
    TTPNetAddress m_tLocalNetAddr;   //通道本地地址(发送对象)
    //通道本地RTCP地址等于通道本地地址的端口加一(发送对象)
    TTPNetAddress m_tLocalNetRtcpAddr;//本地发送
    TTPNetAddress m_tDstNetAddr;     //通道目的地址(发送对象)
}TTPMixerChannelParam;

// 待机描述
// typedef struct tagTTPSleepInfo
// {
// 	BOOL        m_bIsSleepEnable;//是否允许待机
// 	u32         m_dwSleepTimes;//待机时间
// public:
// 	tagTTPSleepInfo(){memset(this,0,sizeof(tagTTPSleepInfo));}
// }TTPSleepInfo,*PTTPSleepInfo;

//呼叫服务器配置
typedef struct tagTTPCallSerInfo
{
	u32_ip		dwCallServiceIP; //呼叫服务器IP地址

	public:
	tagTTPCallSerInfo()
	{ 
		memset( this ,0 ,sizeof( struct  tagTTPCallSerInfo ) );
	}

}TTPCallSerInfo;

//图像左右裁边
typedef struct tagTTPVidSrcCutLines
{
	u32 dwLCutLine; 
	u32 dwRCutline;
	u8  byPos;
	public:
		tagTTPVidSrcCutLines(){ memset( this ,0 ,sizeof( struct  tagTTPVidSrcCutLines ) );}
		
}TTPVidSrcCutLines;

typedef struct tagTVcrCfg
{
	s8		m_achName[MAX_VTR_NAME_LENGTH];  //VTR名称
	u8		m_byEqpID;	//编号
	u32_ip	m_dwIP;		//IP

	tagTVcrCfg()
	{
		Clear();
	}

	tagTVcrCfg& operator=(const tagTVcrCfg& tCfg)
	{
		if (this == &tCfg)
		{
			return *this;
		}

		memcpy(m_achName, tCfg.m_achName, MAX_VTR_NAME_LENGTH);
		m_byEqpID = tCfg.m_byEqpID;
		m_dwIP = tCfg.m_dwIP;

		return *this;
	}

	void Clear()
	{
		memset(m_achName, 0, MAX_VTR_NAME_LENGTH);
		m_byEqpID = 0;
		m_dwIP = 0;
	}

}TVcrCfg;

typedef struct tagTAdjustFrameRate
{
	u16  m_wEpID;
	u16	 m_wFrameRate;
	BOOL32 m_bReset;
	u16	m_wScreenIndx;
	tagTAdjustFrameRate()
	{
		m_wEpID = TP_INVALID_INDEX;
		m_wFrameRate = 0;
		m_bReset = FALSE;
		m_wScreenIndx = 0;
	}
}TAdjustFrameRate;

typedef struct tagTAdjustVidRes
{
	u16  m_wEpID;
	u32	 m_dwVidRes;
	BOOL32 m_bReset;
	u16	m_wScreenIndx;
	tagTAdjustVidRes()
	{
		m_wEpID = TP_INVALID_INDEX;
		m_dwVidRes = 0;
		m_bReset = FALSE;
		m_wScreenIndx = 0;
	}
}TAdjustVidRes;

//【滤波状态，相位时钟】两张一维表,16表示VGA分辨率,表示默认值
typedef struct tagTTPVGAInfo
{
	u32	 m_adwVGA_DF_PC[16];
	u32	m_adwVGA_DF_FS[16];
	public:
		tagTTPVGAInfo(){ memset( this, 0, sizeof(struct tagTTPVGAInfo) ); }
}TTPVGAInfo;

//Add by tanxiaodong 2013-03-15.
//台标Logo结构体定义，从媒控codecwrapperdef_hd.h中转换
typedef struct tagTTPBmpInfo
{
    u32 m_dwWidth;    //图片所对应的视频源制式宽度
    u32 m_dwHeight;  //图片所对应的视频源制式高度
//    u8  m_achBMP[CNMP_LOGO_MAX_LENGTH]; 
    u32 m_dwBmpLen;
	public:
        tagTTPBmpInfo()
		{
			memset(this, 0, sizeof(struct tagTTPBmpInfo));
		}
}TTPBmpInfo;


typedef struct tagTTPAddLogoPos
{
    u32 m_dwXPos;
    u32 m_dwYPos;
    public:
		tagTTPAddLogoPos()
		{
			memset(this, 0, sizeof(struct tagTTPAddLogoPos));
		}
}TTPAddLogoPos;

typedef struct tagTTPTranspDColor
{
	u8 m_byRColor;          //R背景
	u8 m_byGColor;          //G背景
	u8 m_byBColor;          //B背景	
	u8 m_byTransparency;    //透明度(0表示全透明，255表示不透明，1~254表示部分透明)
	public:
		tagTTPTranspDColor()
		{
			memset(this, 0, sizeof(struct tagTTPTranspDColor));
		}
}TTPTranspDColor;

typedef struct tagTTPAddLogoParam
{
    u32 m_dwXPos;
    u32 m_dwYPos;
    u32 m_dwLogoWidth;//logo宽
    u32 m_dwLogoHeight;//logo高
    TTPTranspDColor m_tBackBGDColor;
    public:
		tagTTPAddLogoParam()
		{
		  memset(this, 0, sizeof(struct tagTTPAddLogoParam));
		}
}TTPAddLogoParam;

typedef struct tagTTPFullLogoParam
{
    TTPBmpInfo m_tBmpInfo[3];
    TTPAddLogoParam m_tLogoParam[3];
	public:
		tagTTPFullLogoParam()
		{
			memset( this, 0, sizeof(struct tagTTPFullLogoParam) );
		}
}TTPFullLogoParam;
//End to add.

//add by niulifu
typedef struct tagTCnProduceTestMsg
{	
	// 版本号 
	u16  m_wVersionNum;
	// 测试类别
	EmProducetestType  m_emProduceTestType;
	// 开始测试标志位：TRUE，开始测试；FALSE，停止测试
	BOOL  m_bProduceTestStart;
	// 测试结果: 0，失败; 1，成功。
	BOOL  m_bProduceTestReult; 
	// 测试失败原因:1, 硬件测试结果失败; 2, 测试正在进行;  
	// 3, 不支持该项测试; 4,终端状态错误;5, 测试软件版本号错误; 
	// 其它附加返回信息
	u8  m_byErrorReason;
	
	//E1 本机地址
    u32_ip m_adwLocalIp[MT_MAX_E1UNIT_NUM];
    //E1 ping地址
    u32_ip m_adwDstIp[MT_MAX_E1UNIT_NUM];

	tagTCnProduceTestMsg ()
	{ 
		memset( this ,0 ,sizeof( struct  tagTCnProduceTestMsg) );
	}
}TCnProduceTestMsg, *PTCnProduceTestMsg;

typedef struct tagTRecBaseInfo
{
	s8		m_achName[MAX_VTR_NAME_LENGTH];	//名称
	u32		m_dwFreeSize;	//空闲空间
	u32		m_dwTotalSize;	//总空间
	
	tagTRecBaseInfo()
	{
		Clear();
	}

	void Clear()
	{
		memset(m_achName, 0, MAX_VTR_NAME_LENGTH);
		m_dwTotalSize = 0;
		m_dwFreeSize = 0;
	}
}TRecBaseInfo;

//录播服务器文件列表
typedef struct tagTRecFileListInfo
{	
	u8		m_byEqpID;	//设备ID
	u16		m_wTotalSize;	//总数
	u16		m_wCurSize;	//当前包数量
	s8		m_achFileName[TP_MAX_RECORDER_PACK_NUM][TP_REC_FILE_LEN];

	tagTRecFileListInfo()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTRecFileListInfo));
	}
}TRecFileListInfo;

typedef struct tagTRecFileInfo
{
	u8	m_byEqpID;	//设备ID
	s8	m_szFilelName[TP_REC_FILE_LEN];	//文件名

	tagTRecFileInfo()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTRecFileInfo));
	}
}TRecFileInfo;

//会议录制信息
typedef struct tagTRecorderConfInfo
{
	TUmsVidFormat	m_tConfFormat;	//会议格式

	tagTRecorderConfInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_tConfFormat.Clear();
	}

}TRecorderConfInfo;

//终端录制信息
typedef struct tagTRecorderMTInfo
{
	u16		m_wMtID;	//终端ID

	tagTRecorderMTInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_wMtID = 0;
	}
}TRecorderMTInfo;

//录制会议
typedef struct tagTRecConfInfo
{
	u8				m_byEqpID;	//设备ID
	u16				m_wConfID;	//会议ID
	EmRecorderType	m_emType;	//录制类型
	s8				m_achFileName[TP_REC_FILE_LEN];
	BOOL32			m_bRecDual;		//是否录制双流
	TUmsVidFormat	m_tDualFormat;	//双流格式

	TRecorderConfInfo	m_tConfRecInfo;	//会议录制信息
	TRecorderMTInfo		m_tMtRecInfo;	//终端录制信息

	tagTRecConfInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_byEqpID = 0;
		m_wConfID = 0;
		m_emType = em_rec_recorder_unknow;
		m_bRecDual = FALSE;
		m_tDualFormat.Clear();
		memset(m_achFileName, 0, TP_REC_FILE_LEN);
		m_tConfRecInfo.Clear();
		m_tMtRecInfo.Clear();
	}
}TRecConfInfo;

typedef struct tagTConRecState
{
	TRecConfInfo	m_tInfo;
	EmConfRecState	m_emState;
	u32				m_dwRecTime;	//已录制时间  秒

	tagTConRecState()
	{
		Clear();
	}

	void Clear()
	{
		m_tInfo.Clear();
		m_emState = em_rec_unknow;
		m_dwRecTime = 0;
	}
}TConRecState;


typedef struct tagTRecConfRes
{
	u8		m_byEqpID;
	u16		m_wConfID;
	EmRecorderType	m_emType;	//录制类型
	u16		m_wMtID;
	
	tagTRecConfRes()
	{
		Clear();
	}
	
	void Clear()
	{
		m_byEqpID = 0;
		m_wConfID = 0;
		m_emType = em_rec_recorder_unknow;
		m_wMtID = 0;
	}
}TRecConfRes;

//放像信息
typedef struct tagTRecPlayInfo
{
	u8				m_byEqpID;
	u16				m_wConfID;
	BOOL32			m_bPlayInDual;
	s8				m_szFileName[TP_REC_FILE_LEN];	//文件名

	TUmsVidFormat	m_tConfFormat;	//会议格式
	TUmsVidFormat	m_tDualFormat;	//双流格式

	tagTRecPlayInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_byEqpID = 0;
		m_wConfID = 0;
		m_bPlayInDual = FALSE;
		memset(m_szFileName, 0, TP_REC_FILE_LEN);
	}
}TRecPlayInfo;

//改变放像状态
typedef struct tagTPlayStatusMdyInfo
{
	u8		m_byEqpID;
	u16		m_wConfID;

	tagTPlayStatusMdyInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_byEqpID = 0;
		m_wConfID = 0;
	}
}TPlayStatusMdyInfo;

typedef struct tagTConfPlayStatus
{
	EmConfRecState	m_emState;
	TRecPlayInfo	m_tInfo;
	u32				m_dwTotalTime;	//总放像时间
	u32				m_dwCurTime;	//当前已放像时间
	
	tagTConfPlayStatus()
	{
		Clear();
	}
	
	void Clear()
	{
		m_emState = em_rec_unknow;
		m_dwTotalTime = 0;
		m_dwCurTime = 0;
		m_tInfo.Clear();
	}
	
}TConfPlayStatus;

typedef struct tagTTPUpgradeSer
{
	u32_ip dwSerIP;
public:
	tagTTPUpgradeSer()
	{ 
		memset(this, 0, sizeof(struct tagTTPUpgradeSer)); 
	}
}TTPUpgradeSer;

typedef struct tagTTPSnapInfo
{
	u8  byPos;
	s8  achSnapName[MT_MAX_FULLFILENAME_LEN];
	BOOL bShow;  //是否显示静态图片
public:
	tagTTPSnapInfo()
	{ 
		memset(this, 0, sizeof(struct tagTTPSnapInfo)); 
	}
}TTPSnapInfo;

//单路自环信息
typedef struct tagTTPSingleLoopInfo
{
	EmTpMediaType emMediaType;//媒体类型
	BOOL bLoop;//自环
	u8  byPos;
public:
	tagTTPSingleLoopInfo(){Clear();}
	
	void Clear()
	{
		emMediaType = emTPMediaAV;
		bLoop = FALSE;
		byPos = emEndMPCodec;
	}
	
}TTPSingleLoopInfo;

//自环信息
typedef struct tagTTPAllLoopInfo
{
	u8  byPos;
	TTPSingleLoopInfo tSingleLoopInfo[MEDIA_NUM];	
public:
	tagTTPAllLoopInfo(){Clear();}
	
	void Clear()
	{
		byPos = emEndMPCodec;
		tSingleLoopInfo[0].Clear();
		tSingleLoopInfo[1].Clear();
	}
}TTPAllLoopInfo;

typedef struct tagTTPMtTerminal
{
	u32_ip m_dwIp;
	TTPAlias m_atAlias[MAX_MT_ALIAS_NUM];
	EmTPEndpointType m_emType;

	tagTTPMtTerminal()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTTPMtTerminal));
	}

	tagTTPMtTerminal& operator=(const tagTTPMtTerminal& tInfo)
	{
		if (this == &tInfo)
		{
			return *this;
		}

		m_dwIp = tInfo.m_dwIp;
		for (u16 wIndex = 0; wIndex < MAX_MT_ALIAS_NUM; ++wIndex)
		{
			m_atAlias[wIndex] = tInfo.m_atAlias[wIndex];
		}
		m_emType = tInfo.m_emType;

		return *this;
	}
}TTPMtTerminal;

typedef struct tagTTPMtOnLineList
{
	u16 m_wListNum;
	TTPMtTerminal m_atTerminal[MAX_MT_ONLINE_LIST_NUM];
	BOOL32 m_bIsEnd;

	u32_ip	m_dwIP;	//MCU 使用

	tagTTPMtOnLineList()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTTPMtOnLineList));
	}
}TTPMtOnLineList;

typedef struct tagTTPMtRegInfo
{
	u16	m_wListNum;
	TTPMtTerminal m_atTerminal[MAX_MT_ONLINE_LIST_NUM];
	BOOL32 m_bIsEnd;

	tagTTPMtRegInfo()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTTPMtRegInfo));
	}

	tagTTPMtRegInfo& operator=(const tagTTPMtRegInfo& tInfo)
	{
		if (this == &tInfo)
		{
			return *this;
		}

		this->m_wListNum = tInfo.m_wListNum;
		this->m_bIsEnd = tInfo.m_bIsEnd;
		for (u16 wIndex = 0; wIndex < tInfo.m_wListNum; ++wIndex)
		{
			this->m_atTerminal[wIndex] = tInfo.m_atTerminal[wIndex];
		}

		return *this;
	}

}TTPMtRegInfo;

typedef struct tagTTPMcuRegInfo
{
	u16	m_wListNum;
	TTPAlias m_atAlias[MAX_MT_ALIAS_NUM];
	BOOL32 m_bIsEnd;
	u32_ip	m_dwIP;

	tagTTPMcuRegInfo()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTTPMcuRegInfo));
	}

	tagTTPMcuRegInfo& operator=(const tagTTPMcuRegInfo& tInfo)
	{
		if (this == &tInfo)
		{
			return *this;
		}

		this->m_wListNum = tInfo.m_wListNum;
		this->m_dwIP = tInfo.m_dwIP;
		this->m_bIsEnd = tInfo.m_bIsEnd;
		for (u16 wIndex = 0; wIndex < tInfo.m_wListNum; ++wIndex)
		{
			this->m_atAlias[wIndex] = tInfo.m_atAlias[wIndex];
		}

		return *this;
	}

}TTPMcuRegInfo;

typedef struct tagTRegPackInfoEx
{
	TTPSipRegPackInfo	m_tPackInfo;
	EmGetRegInfoType	m_emType;
	EmTPEndpointType	m_emEndpointType;

	tagTRegPackInfoEx()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTRegPackInfoEx));
	}
}TRegPackInfoEx;

typedef struct tagTUmsRegInfoEx
{
	u16					m_wAliasNum;
	TTPAlias			m_atAlias[TP_REGNAME_SIZE];					//暂时定为最大值为64个名称为一波返回
	TTPTransAddr		m_atContactAddr[TP_MAX_NUM_CONTACT_ADDR];	//注册地址
	u32					m_dwExpires;//超时时间,单位秒
	EmTPEndpointType	m_emEndpointType;    
	u32_ip				m_locolIP;                         
	s8					m_softversion[TP_MAX_VERSION_LEN+1];  
	s8					m_compileTime[TP_MAX_VERSION_LEN+1];  

	tagTUmsRegInfoEx()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTUmsRegInfoEx));
	}

	tagTUmsRegInfoEx& operator=(const tagTUmsRegInfoEx& tInfo)
	{
		if (this == &tInfo)
		{
			return *this;
		}
		
		this->m_wAliasNum = tInfo.m_wAliasNum;
		u16 wIndex = 0;
		
		for (wIndex = 0; wIndex < tInfo.m_wAliasNum; ++wIndex)
		{
			this->m_atAlias[wIndex] = tInfo.m_atAlias[wIndex];
		}
		
		for (wIndex = 0; wIndex < TP_MAX_NUM_CONTACT_ADDR; ++wIndex)
		{
			this->m_atContactAddr[wIndex] = tInfo.m_atContactAddr[wIndex];
		}
		
		this->m_dwExpires = tInfo.m_dwExpires;
		this->m_emEndpointType = tInfo.m_emEndpointType;
		this->m_locolIP = tInfo.m_locolIP;
		memcpy(this->m_softversion, tInfo.m_softversion, TP_MAX_VERSION_LEN);
		memcpy(this->m_compileTime, tInfo.m_compileTime, TP_MAX_VERSION_LEN);
		
		return *this;
	}

}TUmsRegInfoEx;

typedef struct tagTUmsRegPackEx
{
	u16				m_wSize;
	TUmsRegInfoEx	m_atRegInfo[TP_UMS_MAX_REG_DATA];
	BOOL32			m_bIsEnd;

	tagTUmsRegPackEx()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTUmsRegPackEx));
	}

	tagTUmsRegPackEx& operator=(const tagTUmsRegPackEx& tInfo)
	{
		if (this == &tInfo)
		{
			return *this;
		}
		
		this->m_wSize = tInfo.m_wSize;
		for (u16 wIndex = 0; wIndex < tInfo.m_wSize; ++wIndex)
		{
			this->m_atRegInfo[wIndex] = tInfo.m_atRegInfo[wIndex];
		}
		this->m_bIsEnd = tInfo.m_bIsEnd;
		
		return *this;
	}

}TUmsRegPackEx;

typedef struct tagTCnsRegInfoEx
{
	u16					m_wAliasNum;
	TTPAlias			m_atAlias[TP_CNS_ALIAS_REG_NUM];
	TTPTransAddr		m_atContactAddr[TP_MAX_NUM_CONTACT_ADDR];	//注册地址
	u32					m_dwExpires;//超时时间,单位秒
	EmTPEndpointType	m_emEndpointType;    
	u32_ip				m_locolIP;                         
	s8					m_softversion[TP_MAX_VERSION_LEN+1];  
	s8					m_compileTime[TP_MAX_VERSION_LEN+1];  
	
	tagTCnsRegInfoEx()
	{
		Clear();
	}
	
	void Clear()
	{
		memset(this, 0, sizeof(tagTCnsRegInfoEx));
	}

	tagTCnsRegInfoEx& operator=(const tagTCnsRegInfoEx& tInfo)
	{
		if (this == &tInfo)
		{
			return *this;
		}
		
		this->m_wAliasNum = tInfo.m_wAliasNum;
		u16 wIndex = 0;
		
		for (wIndex = 0; wIndex < tInfo.m_wAliasNum; ++wIndex)
		{
			this->m_atAlias[wIndex] = tInfo.m_atAlias[wIndex];
		}
		
		for (wIndex = 0; wIndex < TP_MAX_NUM_CONTACT_ADDR; ++wIndex)
		{
			this->m_atContactAddr[wIndex] = tInfo.m_atContactAddr[wIndex];
		}
		
		this->m_dwExpires = tInfo.m_dwExpires;
		this->m_emEndpointType = tInfo.m_emEndpointType;
		this->m_locolIP = tInfo.m_locolIP;
		memcpy(this->m_softversion, tInfo.m_softversion, TP_MAX_VERSION_LEN);
		memcpy(this->m_compileTime, tInfo.m_compileTime, TP_MAX_VERSION_LEN);
		
		return *this;
	}
	
}TCnsRegInfoEx;

typedef struct tagTCnsRegPackEx
{
	u16				m_wSize;
	TCnsRegInfoEx	m_atRegInfo[TP_CNS_MAX_REG_DATA];
	BOOL32			m_bIsEnd;
	
	tagTCnsRegPackEx()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTCnsRegPackEx));
	}

	tagTCnsRegPackEx& operator=(const tagTCnsRegPackEx& tInfo)
	{
		if (this == &tInfo)
		{
			return *this;
		}
		
		this->m_wSize = tInfo.m_wSize;
		this->m_bIsEnd = tInfo.m_bIsEnd;
		for (u16 wIndex = 0; wIndex < tInfo.m_wSize; ++wIndex)
		{
			this->m_atRegInfo[wIndex] = tInfo.m_atRegInfo[wIndex];
		}
		
		return *this;
	}

}TCnsRegPackEx;

//音频播放模式
typedef struct tagTTPAudPlayMode
{
	EmTPAudPlayMode emAudPlayMode;//音频播放模式
	u8 abChnID[emEndMPCodec];
	tagTTPAudPlayMode()
	{ 
		memset(this, 0, sizeof(struct tagTTPAudPlayMode)); 
	}
	
}TTPAudPlayMode;


//仅针对T300 abc三种风格
typedef struct tagTTPSmallPicRectInfo
{
	BOOL32 bUsrCfg;		//是否使用用户定义布局
	u32 dwMergeStyle;	//对应的画面风格 T300——A,B,C
	u32 dwPosIndex;		//子图像位置
	u32 dwScaleX;		//X坐标所占比例 百分比
	u32 dwScaleY;		//Y坐标所占比例
	u32 dwScaleW;		//宽度所占比例
	u32 dwScaleH;		//高度所占比例

	tagTTPSmallPicRectInfo()
	{ 
		memset(this, 0, sizeof(struct tagTTPSmallPicRectInfo)); 
	}

}TTPSmallPicRectInfo;

//录播请求的会场格式信息
typedef struct tagTTPRecMtFormat
{
	u16 m_wConfID;
	u16 m_wMtID;
	BOOL32 m_bValid;		//标识获取会场格式信息是否成功
	TUmsVidFormat m_tVidFormat;

	tagTTPRecMtFormat()
	{
		Clear();
	}

	void Clear()
	{
		m_wConfID = 0;
		m_wMtID = 0;
		m_bValid = FALSE;
		m_tVidFormat.Clear();
	}
}TTPRecMtFormat;

typedef struct tagTTPRebootTime
{
	BOOL bReboot;//是否重启
	u8   byHour;//时
	
	tagTTPRebootTime()
	{ 
		memset(this, 0, sizeof(struct tagTTPRebootTime)); 
	}
	
}TTPRebootTime;

typedef struct tagTTPVidForamt
{
	EmTpVideoQualityLevel emTpVideoQualityLevel;
	EmTpVideoResolution   emTpVideoResolution;
	u16                   wVidFrameRate;

	tagTTPVidForamt()
	{
		memset( this, 0, sizeof(struct tagTTPVidForamt) );
	}
}TTPVidForamt;

typedef struct tagTTPVidOffsetParam // 设置图像偏移 
{
	EmTPMtVideoPort emPort; //视频端口
	s32 nHoff;      // 负数，向左移动，正数，向右移动，0不移动。调整的范围为：[-15, +15]。默认值：0
	s32 nVoff;      // 负数，向上移动，正数，向下移动，0不移动。暂时不支持垂直方向的调节。
	tagTTPVidOffsetParam()
	{ 
		memset(this, 0, sizeof(struct tagTTPVidOffsetParam)); 
	}
}TTPVidOffsetParam;

typedef struct tagTTPAllVidOffsetParam // 设置图像偏移 
{
	TTPVidOffsetParam tVidOffsetParam[emTPVidEnd];
	BOOL bSetSingle; //设置单个采集口
	EmTPMtVideoPort emPort; //只设置单个采集口用到
	tagTTPAllVidOffsetParam()
	{ 
		memset(this, 0, sizeof(struct tagTTPAllVidOffsetParam)); 
	}
}TTPAllVidOffsetParam;

typedef struct tagTTPCnConfInfo
{
	TCnVideoParam    tCnVideoParam;
	EmTpAudioFormat  emTpAudioFormat;
	u16              wDualCallBit;

}TTPCnConfInfo;

typedef struct tagTTPDisplayType
{	
	EmTVInputSelect   emTPT300Type; //终端信号源类型
	EmTVInputSelect   emTPHduType; //电视墙信号源类型	

	tagTTPDisplayType()
	{
		memset(this, 0, sizeof(struct tagTTPDisplayType));
	}

}TTPDisplayType;

//for umc
typedef struct tagTChairSingleStreenInfo
{
	EMScreenLooked emScreenInfo;   //屏幕状态
	u16  wEpId;  //屏幕所看会场id(选看状态时用这个)
	
	tagTChairSingleStreenInfo()
	{
		Clear();
	}
	
	void Clear()
	{
		memset(this, 0, sizeof(tagTChairSingleStreenInfo));
	}
	
}TChairSingleStreenInfo;


//选看结果
typedef struct tagTChanViewRes
{
    EmTPViewResult	 m_emRes;
	TTPAlias		 m_tAlias;
	tagTChanViewRes()
	{
		memset(this, 0, sizeof(tagTChanViewRes));
	}
}TChanViewRes;

//for umc
typedef struct tagTChairStreenInfo
{
	TConfEpID tConfID;
	u16 wStreenNum;  //屏幕数量
	TChairSingleStreenInfo  tChairStreenInfo[TP_MAX_STREAMNUM];  
	
	tagTChairStreenInfo()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTChairStreenInfo));
	}

}TChairStreenInfo;

//////////////////////////////////////////////////////////////////////////
//mpu2tp

//业务注册信息
typedef struct tagTVmpRegistInfo
{
	u8		m_byLayer;		//板子层号
	u8		m_bySlot;		//板子槽号
	u16		m_wChanID;		//通道ID
	u16		m_dwStartPort;	//起始端口
	u16		m_wRcvChanNum;	//外设接收通道数
	u16		m_wSendChanNum;	//外设发送通道数

	tagTVmpRegistInfo()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTVmpRegistInfo));
	}

}TVmpRegistInfo;

//注册结果
typedef struct tagTVmpRegAck
{
	u32		m_dwRcvIP;	//接收IP
	u16		m_wRcvPort;	//接收起始端口

	tagTVmpRegAck()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTVmpRegAck));
	}

}TVmpRegAck;

//重传时间
typedef struct tagTVmpTimeSpan
{
    u16  m_wFirstTimeSpan;	  //第一个重传检测点
	u16  m_wSecondTimeSpan;   //第二个重传检测点
	u16  m_wThirdTimeSpan;    //第三个重传检测点
	u16  m_wRejectTimeSpan;   //过期丢弃的时间跨度

	tagTVmpTimeSpan()
	{
		Clear();
	}

	void Clear()
	{
		memset(this, 0, sizeof(tagTVmpTimeSpan));
	}

	tagTVmpTimeSpan(const tagTVmpTimeSpan& tInfo)
	{
		Copy(tInfo);
	}

	tagTVmpTimeSpan& operator=(const tagTVmpTimeSpan& tInfo)
	{
		if (this != &tInfo)
		{
			Copy(tInfo);
		}

		return *this;
	}

	void Copy(const tagTVmpTimeSpan& tInfo)
	{
		m_wFirstTimeSpan = tInfo.m_wFirstTimeSpan;
		m_wSecondTimeSpan = tInfo.m_wSecondTimeSpan;
		m_wThirdTimeSpan = tInfo.m_wSecondTimeSpan;
		m_wRejectTimeSpan = tInfo.m_wRejectTimeSpan;
	}

}TVmpTimeSpan;

//视频加密参数
// typedef struct tagTVmpEncrypt
// {
// 	EmVmpEncMode	m_emEncMode;	//加密模式
//     s32				m_nKeyLen;		//加密key的长度
// 	s8				m_abyEncKey[UMS_VMP_ENC_KEY_LEN]; //加密key
// 
// 	tagTVmpEncrypt()
// 	{
// 		Clear();
// 	}
// 
// 	tagTVmpEncrypt(const tagTVmpEncrypt& tInfo)
// 	{
// 		Copy(tInfo);
// 	}
// 
// 	tagTVmpEncrypt& operator=(const tagTVmpEncrypt& tInfo)
// 	{
// 		if (&tInfo != this)
// 		{
// 			Copy(tInfo);
// 		}
// 
// 		return *this;
// 	}
// 
// 	void Clear()
// 	{
// 		memset(this, 0, sizeof(tagTVmpEncrypt));
// 	}
// 
// private:
// 	void Copy(const tagTVmpEncrypt& tInfo)
// 	{
// 		m_emEncMode = tInfo.m_emEncMode;
// 		m_nKeyLen = tInfo.m_nKeyLen;
// 		memcpy(m_abyEncKey, tInfo.m_abyEncKey, UMS_VMP_ENC_KEY_LEN);
// 	}
// 
// }TVmpEncrypt;
// 
typedef struct tagTVmpMemberInfo
{
	BOOL32		m_bMerged;	//连续的为 TRUE 的合成成员，去掉中间的间隔线
	u32			m_dwHandle;	//标识每个成员的唯一性

	tagTVmpMemberInfo()
	{
		Clear();
	}

	tagTVmpMemberInfo(const tagTVmpMemberInfo& tInfo)
	{
		Copy(tInfo);
	}

	tagTVmpMemberInfo& operator=(const tagTVmpMemberInfo& tInfo)
	{
		if (this != &tInfo)
		{
			Copy(tInfo);
		}

		return *this;
	}

	void Clear()
	{
		m_bMerged = FALSE;
		m_dwHandle = 0;
	}

	BOOL32 Valid() const
	{
		return 0 != m_dwHandle;
	}

	void MakeHandle(u16 wHandleOne, u16 wHandleTwo)
	{
		m_dwHandle = wHandleOne;
		m_dwHandle = m_dwHandle << 16;
		m_dwHandle |= wHandleTwo;
	}
	
	u16 GetHandleOne() const	{ return u16(m_dwHandle >> 16); }
	u16 GetHandleTwo()   const	{ return u16(m_dwHandle << 16 >> 16); }

private:
	void Copy(const tagTVmpMemberInfo& tInfo)
	{
		m_bMerged = tInfo.m_bMerged;
		m_dwHandle = tInfo.m_dwHandle;
	}
	
}TVmpMemberInfo;

typedef struct tagTDBPayload
{
	u8  m_byRealPayload;    //原媒体格式
	u8  m_byActivePayload;  //活动媒体格式

    tagTDBPayload()
	{
		Clear();
	}

	tagTDBPayload& operator=(const tagTDBPayload& tInfo)
	{
		if (this != &tInfo)
		{
			m_byRealPayload = tInfo.m_byRealPayload;
			m_byActivePayload = tInfo.m_byActivePayload;
		}
		return *this;
	}

	void Clear()
	{
		m_byRealPayload = MEDIA_TYPE_NULL;
		m_byActivePayload = MEDIA_TYPE_NULL;
	}
	
}TDBPayload;

typedef struct tagTVmpStyleInfo
{
	EmUmsVmpStyle	m_emVmpStyle;	//合成风格
	EmVmpShowMode	m_emShowMode;	//
	u8				m_byMemberNum;	//合成成员数量
	TVmpMemberInfo	m_atMemberInfo[UMS_VMP_MAX_RCV];
	TDBPayload		m_atDoublePayload[UMS_VMP_MAX_RCV];

	tagTVmpStyleInfo()
	{
		Clear();
	}

	tagTVmpStyleInfo(const tagTVmpStyleInfo& tInfo)
	{
		Copy(tInfo);
	}

	tagTVmpStyleInfo& operator=(const tagTVmpStyleInfo& tInfo)
	{
		if (this != &tInfo)
		{
			Copy(tInfo);
		}

		return *this;
	}
	
	void Clear()
	{
		m_emVmpStyle = em_ums_vmp_invalid;
		m_emShowMode = ums_vmp_defaultpic_mode;
		m_byMemberNum = 0;
		
		u16 wIndex = 0;
		for (wIndex = 0; wIndex < UMS_VMP_MAX_RCV; ++wIndex)
		{
			m_atMemberInfo[wIndex].Clear();
			m_atDoublePayload[wIndex].Clear();
		}
	}

private:
	void Copy(const tagTVmpStyleInfo& tInfo)
	{
		m_emVmpStyle = tInfo.m_emVmpStyle;
		m_emShowMode = tInfo.m_emShowMode;
		m_byMemberNum = tInfo.m_byMemberNum;
		for (u8 byIndex = 0; byIndex < m_byMemberNum; ++byIndex)
		{
			m_atMemberInfo[byIndex] = tInfo.m_atMemberInfo[byIndex];
		}
	}
	
}TVmpStyleInfo;

typedef struct  tagTVmpEncParam
{
	u8    	        m_byEncType;		//图像编码类型
	u8    	        m_byProfileType;	//BP/HP
	u8				m_byFrameRate;		//帧率
	u16             m_wBitRate;			//编码比特率(Kbps)
	u16   	        m_wVideoWidth;		//图像宽度(default:720)
	u16   		    m_wVideoHeight;		//图像高度(default:576)
	
	tagTVmpEncParam()
	{
		Clear();
	}

	tagTVmpEncParam(const tagTVmpEncParam& tInfo)
	{
		Copy(tInfo);
	}

	tagTVmpEncParam& operator=(const tagTVmpEncParam& tInfo)
	{
		if (this != &tInfo)
		{
			Copy(tInfo);
		}

		return *this;
	}
	
	void Clear()
	{
		memset(this, 0, sizeof(tagTVmpEncParam));
	}

private:
	void Copy(const tagTVmpEncParam& tInfo)
	{
		memcpy(this, &tInfo, sizeof(tInfo));
	}
	
}TVmpEncParam;

typedef struct tagTVmpMdyInfo
{
	u16				m_wServiceID;
	TVmpStyleInfo	m_tStyleInfo;
	TVmpEncParam	m_tEncParam;
	
	tagTVmpMdyInfo()
	{
		Clear();
	}
	
	void Clear()
	{
		m_wServiceID = 0;
		m_tStyleInfo.Clear();
		m_tEncParam.Clear();
	}
	
}TVmpMdyInfo;

//合成参数
typedef struct tagTVmpStartParam
{
	u16				m_wChanID;
	TTPEncrypt		m_tEncrypt;
	TVmpStyleInfo	m_tStyleInfo;
	TVmpEncParam	m_tEncParam;

	tagTVmpStartParam()
	{
		Clear();
	}

	tagTVmpStartParam(const tagTVmpStartParam& tInfo)
	{
		Copy(tInfo);
	}

	tagTVmpStartParam& operator=(const tagTVmpStartParam& tInfo)
	{
		if (this != &tInfo)
		{
			Copy(tInfo);
		}

		return *this;
	}

	void Clear()
	{
		m_wChanID = 0;
		m_tStyleInfo.Clear();
		m_tEncrypt.Clear();
		m_tEncParam.Clear();
	}
	
private:
	void Copy(const tagTVmpStartParam& tInfo)
	{
		m_tEncParam = tInfo.m_tEncParam;
		m_tEncrypt = tInfo.m_tEncrypt;
		m_tStyleInfo = tInfo.m_tStyleInfo;
	}

}TVmpStartParam;

typedef struct tagTVmpStartRes
{
	EmVmpRes	m_emRes;
	u16			m_wChanID;

	tagTVmpStartRes()
	{
		Clear();
	}

	void Clear()
	{
		m_emRes = em_ums_vmp_success;
		m_wChanID = 0;
	}

}TVmpStartRes;

typedef struct tagTVmpMdyRes
{
	EmVmpRes	m_emRes;
	u16			m_wChanID;
	
	tagTVmpMdyRes()
	{
		Clear();
	}
	
	void Clear()
	{
		m_emRes = em_ums_vmp_success;
		m_wChanID = 0;
	}
	
}TVmpMdyRes;

typedef struct tagTVmpStopRes
{
	EmVmpRes	m_emRes;
	u16			m_wChanID;
	
	tagTVmpStopRes()
	{
		Clear();
	}
	
	void Clear()
	{
		m_emRes = em_ums_vmp_success;
		m_wChanID = 0;
	}
	
}TVmpStopRes;

typedef struct tagTVmpChanRes
{
	EmVmpRes	m_emRes;
	u16			m_wChanID;
	
	tagTVmpChanRes()
	{
		Clear();
	}
	
	void Clear()
	{
		m_emRes = em_ums_vmp_success;
		m_wChanID = 0;
	}
	
}TVmpChanRes;

typedef struct tagTVmpAskFrame
{
	u16		m_wChanID;
	u16		m_wMemberIndx;
	
	tagTVmpAskFrame()
	{
		Clear();
	}
	
	void Clear()
	{
		m_wMemberIndx = 0;
		m_wChanID = 0;
	}
	
}TVmpAskFrame;

typedef struct tagTVmpChanInfo
{
	u16		m_wChanIndex;

	tagTVmpChanInfo()
	{
		Clear();
	}

	void Clear()
	{
		m_wChanIndex = 0;
	}

}TVmpChanInfo;

typedef struct tagTTPAudPackCheckInfo
{
	u32 dwCheckTime;//音频包检测时间
	u32 dwLostNum; //音频包间隔数目
public:
	tagTTPAudPackCheckInfo()
	{ 
		dwCheckTime = TP_AUD_PACKET_TIMEOUT;
		dwLostNum = TP_LOST_AUD_PACKET_NUM;
	}
}TTPAudPackCheckInfo;

typedef struct tagTTPSelViewReq
{
	EmUIType m_emUIType;

	BOOL32	 m_bSel;
	u16		 m_wConfID;
	u16		 m_wEpID;
	u16		 m_wScreenIndx;// UI->ums的cmd消息：会场m_wEpID的m_wScreenIndx屏选看其他会场，m_wScreenIndx为3时，表示此会场选看其他会场
	// ums->UI的nfy消息：通知m_wEpID会场m_wScreenIndx（0,1,2）屏的选看状态
	
	EmViewEpType	m_emType;
	u16				m_wDstID;
	u16				m_wDstScrIndx; // B5新填字段：会场选看，此字段无意义；
	//UI->ums的cmd消息：m_wDstID为被选看会场id，m_wDstScrIndx为B5新填字段，会场选看时，此字段无意义
	// 屏选看时，m_wDstScrIndx为3表示选看发言坐席（存在合成资源的时候，为1大3小）否则为选看m_wDstScrIndx屏；
	// 被选看会场是一个单屏的时候，m_wDstScrIndx应该固定为1；
	// ums->UI的nfy消息：通知对应屏的选看状态，目标为m_wDstID会场的m_wDstScrIndx（0,1,2）屏；
	// m_wDstScrIndx为3，表示目标是三屏会场的发言坐席（存在合成资源的时候，为1大3小）

	tagTTPSelViewReq()
	{
		Clear();
	}
	void Clear()
	{
		memset(this, 0, sizeof(tagTTPSelViewReq));
		m_emUIType = EmUI_UMC;
		m_bSel = TRUE;
		m_wEpID = TP_INVALID_INDEX;
		m_wScreenIndx = TP_MAX_STREAMNUM;
		m_wDstID = 0;
		m_wDstScrIndx = TP_MAX_STREAMNUM;
	}
	BOOL32 IsValid()
	{
		return TP_VALID_HANDLE(m_wEpID);
	}
}TTPSelViewReq;

typedef struct tagTTPSelViewInd
{
	TTPSelViewReq m_tSelView;
	EmViewRetReason m_emRet;
	
	tagTTPSelViewInd()
	{
		Clear();
	}
	void Clear()
	{
		m_tSelView.Clear();
		m_emRet = EmViewRetReason_Success;
	}
	void SetView(TTPSelViewReq& tView)
	{
		memcpy(&m_tSelView, &tView, sizeof(m_tSelView));
	}
}TTPSelViewInd;

typedef struct tagTTPSelViewNtfy
{
	u16				m_wConfID;
	u16				m_wEpID;
	TTPSelViewReq	m_atSelView[TP_MAX_STREAMNUM];
	
	tagTTPSelViewNtfy()
	{
		Clear();
	}
	void Clear()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_wEpID = TP_INVALID_INDEX;
		for ( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
		{
			m_atSelView[wIndex].Clear();
		}
	}
	BOOL32 IsHaveValid()
	{
		for ( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
		{
			if ( 0 != m_atSelView[wIndex].m_wDstID )
			{
				return TRUE;
			}
		}
		return FALSE;
	}
}TTPSelViewNtfy;

typedef struct tagTEqpInfo
{
	u8			m_byEqpID;			//EqpID
	EMEqpType	m_emEqpType;		// 外设类型
	
	s8			m_szEqpAlias[TP_MAXLEN_EQP_ALIAS];//外设别名
	tagTEqpInfo()
	{
		Clear();
	}
	void Clear()
	{
		m_byEqpID = 0;
		m_emEqpType = em_unknow_mdl;
		memset(m_szEqpAlias, 0, sizeof(m_szEqpAlias));
	}
}TEqpInfo;

typedef struct tagTRersvesEqpReq
{
	u16			m_wConfID;
	BOOL32		m_bRersves;
	TEqpInfo	m_tEqp;
	tagTRersvesEqpReq()
	{
		Clear();
	}
	void Clear()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_bRersves = FALSE;
		m_tEqp.Clear();
	}
}TRersvesEqpReq;

typedef struct tagTRersvesEqpRsp
{
	u16				m_wConfID;
	EmRervesVmpRet	m_emRet;
	TRersvesEqpReq	m_tRersvesReq;
	tagTRersvesEqpRsp()
	{
		Clear();
	}
	void Clear()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_emRet = EmRervesVmpRet_Success;
		m_tRersvesReq.Clear();
	}
}TRersvesEqpRsp;

typedef struct tagTBrdVmpReq
{
	u16			m_wConfID;
	BOOL32		m_bBrd;
	TEqpInfo	m_tEqp;
	tagTBrdVmpReq()
	{
		Clear();
	}
	void Clear()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_bBrd = FALSE;
		m_tEqp.Clear();
	}
}TBrdVmpReq;

typedef struct tagTBrdVmpRsp
{
	u16			m_wConfID;
	TBrdVmpReq	m_tReq;
	EmBrdVmpRet m_emRet;
	tagTBrdVmpRsp()
	{
		Clear();
	}
	void Clear()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_tReq.Clear();
		m_emRet = EmBrdVmpRet_Succes;
	}
}TBrdVmpRsp;

typedef struct tagTBrdVmpChnl
{
	u16 m_wEpID;
	u16 m_wScrIndx;
	tagTBrdVmpChnl()
	{
		Clear();
	}
	
	void Clear()
	{
		m_wEpID = TP_INVALID_INDEX;
		m_wScrIndx = 0;
	}

	BOOL32 IsValid()
	{
		return TP_VALID_HANDLE(m_wEpID);
	}
}TBrdVmpChnl;

typedef struct tagTBrdVmpStyle
{
	EMVmpStyle	m_emVmpStyle;	//画面风格
	u16			m_wSpeakerIndx;//发言人跟随索引
	u16			m_wDualIndx;//双流跟随索引
	u16			m_wChnlNum;
	TBrdVmpChnl m_atVmpChnl[TP_VMP_MAX_IN_CHN_NUM];
	tagTBrdVmpStyle()
	{
		Clear();
	}

	void Clear()
	{
		m_wSpeakerIndx = TP_INVALID_INDEX;
		m_wDualIndx = TP_INVALID_INDEX;
		m_wChnlNum = 0;
		for ( u16 wIndex = 0; wIndex < TP_VMP_MAX_IN_CHN_NUM; wIndex ++ )
		{
			m_atVmpChnl[wIndex].Clear();
		}
	}

	BOOL32 IsAuto() { return m_emVmpStyle == tp_VmpStyle_DYNAMIC ? TRUE : FALSE; }
}TBrdVmpStyle;

typedef struct tagTSetVmpInfoReq
{
	u16				m_wConfID;
	TEqpInfo		m_tEqp;
	TBrdVmpStyle	m_tStyle;
	tagTSetVmpInfoReq()
	{
		Clear();
	}
	void Clear()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_tEqp.Clear();
		m_tStyle.Clear();
	}
}TSetVmpInfoReq;

typedef struct tagTSetVmpInfoRsp
{
	u16				m_wConfID;
	TSetVmpInfoReq	m_tReq;
	EmBrdVmpRet		m_emRet;
	tagTSetVmpInfoRsp()
	{
		Clear();
	}
	void Clear()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_tReq.Clear();
		m_emRet = EmBrdVmpRet_Succes;
	}
}TSetVmpInfoRsp;

typedef struct tagTVmpCasecadeNtfy
{
	BOOL32	m_bBrdVmp;
	BOOL32	m_bSpeakerVmp;
	s8		m_szBrdVmpAlias[TP_MAXLEN_EQP_ALIAS];
	tagTVmpCasecadeNtfy()
	{
		Clear();
	}
	void Clear()
	{
		memset(this, 0, sizeof(tagTVmpCasecadeNtfy));
	}
}TVmpCasecadeNtfy;

typedef struct tagTBrdVmpResNtfy
{
	u16				m_wConfID;
	BOOL32			m_bVmpAuto;
	EmBrdVmpStat	m_emStat;
	TEqpInfo		m_tEqpInfo;
	TBrdVmpStyle	m_tVmpStyle;
	EmTpOprType		m_emOpr;

	tagTBrdVmpResNtfy()
	{
		Clear();
	}

	void Clear()
	{
		m_emOpr = tp_OprType_Add;
		m_bVmpAuto = FALSE;
		m_wConfID = TP_INVALID_INDEX;
		m_tVmpStyle.Clear();
		m_tEqpInfo.Clear();
		m_emStat = EmBrdVmpStat_Invalid;
	}

	BOOL32 IsRersves(){ return TP_VALID_HANDLE(m_wConfID); }
}TBrdVmpResNtfy;

typedef struct tagTBrdVmpResArray
{
	u16				m_wNum;
	TBrdVmpResNtfy	m_atVmpNtfy[CNS_MAX_CONF_NODE_NUM];
	tagTBrdVmpResArray()
	{
		Clear();
	}
	
	void Clear()
	{
		m_wNum = 0;
		for(u16 wIndex = 0; wIndex < CNS_MAX_CONF_NODE_NUM; wIndex ++)
		{
			m_atVmpNtfy[wIndex].Clear();
		}
	}
}TBrdVmpResArray;

typedef struct tagTCasecadePollEpReq
{
	BOOL32				m_bCreate;
	u16					m_wEpID;
	TTPTransAddr		m_atPollAddr[TP_MAX_STREAMNUM];
	TTPTransAddr		m_atSmallAddr[TP_MAX_STREAMNUM];
	tagTCasecadePollEpReq()
	{
		Clear();
	}
	
	void Clear()
	{
		m_bCreate = TRUE;
		m_wEpID = TP_INVALID_INDEX;
		
		for ( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
		{
			m_atPollAddr[wIndex].Clear();
			m_atSmallAddr[wIndex].Clear();
		}
	}
	
}TCasecadePollEpReq;

typedef struct tagTCasecadePollEpRsp
{
	TCasecadePollEpReq	m_tReq;
	EmTPPollResult		m_emRes;
	
	tagTCasecadePollEpRsp()
	{
		Clear();
	}
	
	void Clear()
	{
		m_tReq.Clear();
		m_emRes = emPollSucceed;
	}
	
}TCasecadePollEpRsp;

typedef struct tagTTpPollListNtfy
{
	u16		m_wConfID;
	s32		m_nFlag;					//更新标识
	u16		m_wInterval;				//轮询间隔，单位秒
	u16		m_wTotalNum;				//总数量
	u16		m_wCurNum;					//本次携带数量
	u16		m_awList[TP_CONF_MAX_TURNNUM];
	tagTTpPollListNtfy()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_nFlag = 0;
		m_wInterval = TP_CONF_TURN_MIN_INTERVAL;
		m_wTotalNum = 0;
		m_wCurNum = 0;
		memset(m_awList, 0, sizeof(m_awList));
	}
}TTpPollListNtfy;

typedef struct tagTTpPollListInd
{
	u16		m_wConfID;
	s32		m_nFlag;					//更新标识
	u16		m_wRet;
	u16     m_wCurRcvNum;   // 当前已经接收完成的数量
	tagTTpPollListInd()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_nFlag = 0;
		m_wRet = TP_RET_OK;
	}
}TTpPollListInd;

typedef struct tagTTpPollStat
{
	u16			m_wConfID;
	EmPollStat	m_emStat;
	tagTTpPollStat()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_emStat = EmPollStat_Stop;
	}
}TTpPollStat;

typedef struct tagTTPDataConfInfo
{
	u32_ip dwSerIP;
public:
	tagTTPDataConfInfo()
	{ 
		memset(this, 0, sizeof(struct tagTTPDataConfInfo)); 
	}
}TTPDataConfInfo;

typedef struct tagTTPCallTypePri
{
	 EmTpCallLevel emTPIPLevel;
	 EmTpCallLevel emTPE164Level;
	 EmTpCallLevel emTPAliasLevel;
public:
	tagTTPCallTypePri()
	{
		memset(this, 0, sizeof(struct tagTTPCallTypePri));
	}
}TTPCallTypePri;

//Add by wangqichang 2014/12/11
//演示策略参数
typedef struct tagTTPDualDisplayParam
{
	BOOL m_bIsAutoDisPlay;
	BOOL m_abIsScreensDisPlay[emEndMPCodec - 1];
public:
	tagTTPDualDisplayParam()
	{
		memset(this, 0 , sizeof( tagTTPDualDisplayParam));
	}
}TTPDualDisplayParam;

//双流演示策略
typedef struct tagTTPDualDisplayStrategy
{
	TTPDualDisplayParam m_tOnIdle;
	TTPDualDisplayParam m_tOnConf;
public:
	tagTTPDualDisplayStrategy()
	{
		memset(this, 0 , sizeof( tagTTPDualDisplayStrategy ));
	}
}TTPDualDisplayStrategy ;
//end add

typedef struct tagTTpObj
{
	u16			m_wVidNum;
	u16			m_wAudNum;
	u16			m_wScrIndx;
	EMScreenObj m_emObj;
	TTPAlias	m_tAlias;
	

	tagTTpObj()
	{
		Clear();
	}

	void Clear()
	{
		m_wVidNum = 0;
		m_wAudNum = 0;
		m_wScrIndx = 0;		
		m_emObj = emObjSelf;
		m_tAlias.Clear();
	}
}TTpObj;

typedef struct tagTTpYouAreSeeing
{
	BOOL32		m_bSpeaker;
	u16			m_wVidNum;
	u16			m_wAudNum;
	TTpObj		m_atObj[TP_MAX_STREAMNUM];
	
	tagTTpYouAreSeeing()
	{
		m_wVidNum = 0;
		m_wAudNum = 0;
		m_bSpeaker = TRUE;	
		for ( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
		{
			m_atObj[wIndex].Clear();
		}
	}

	void SetVidAudNum()
	{
		m_wVidNum = 0;
		m_wAudNum = 0;
		for ( u16 wIndex = 0; wIndex < TP_MAX_STREAMNUM; wIndex ++ )
		{
			m_wVidNum += m_atObj[wIndex].m_wVidNum;
			m_wAudNum += m_atObj[wIndex].m_wAudNum;
		}
	}
}TTpYouAreSeeing;

typedef struct tagTTPAddBannerParam
{
	
	u32 dwXPos;
    u32 dwYPos;//显示区域的Y坐标
    u32 dwWidth;//显示区域的宽
    u32 dwHeight;//显示区域的高
    u32 dwBMPWight;//BMP图像宽
    u32 dwBMPHeight;//BMP图像高
    u32 dwBannerCharHeight;//字体高度－－主要用于上下滚动时，确定停顿的位置
    TTPTranspDColor tBackBGDColor;//背景色 
    u32 dwBGDClarity;//具体颜色透明度
    u32 dwPicClarity;//整幅图片透明度
    u32 dwRunMode;//滚动模式：上下or左右or静止（宏定义如上）
    u32 dwRunSpeed;//滚动速度 四个等级（宏定义如上）
    u32 dwRunTimes;//滚动次数 0为无限制滚动
	u32 bRunForever;//无限制滚动
	u32 dwHaltTime;//停顿时间(秒)，上下滚动时，每滚完一行字的停顿间隔：0始终停留（与静止等同） 
	tagTTPAddBannerParam()
	{
		dwXPos = 0;
		dwYPos = 0;
		dwWidth = 0;
		dwHeight = 0;
		dwBMPWight = 0;
		dwBMPHeight = 0;
		dwBannerCharHeight = 0;
		dwBGDClarity = 0;
		dwPicClarity = 0;
		dwRunMode = 0;
		dwRunSpeed = 0;
		dwRunTimes = 0;
		bRunForever = 0;
		dwHaltTime = 0;
	}
}TTPAddBannerParam;

typedef struct tagTTPBannerBmpInfo
{
    u32 dwWidth;    //图片所对应的视频源制式宽度
    u32 dwHeight;  //图片所对应的视频源制式高度/  
//	u8  achBMP[CNMP_BANNER_MAX_LENGTH]; 
    u32 dwBmpLen;
	public:
        tagTTPBannerBmpInfo()
		{
			memset(this, 0, sizeof(struct tagTTPBannerBmpInfo));
		}
}TTPBannerBmpInfo;

typedef struct tagTTPFullBannerParam
{
    TTPBannerBmpInfo tBmpInfo[3];//576i,720p,1080p三种制式
    TTPAddBannerParam tBannerParam[3];//576i,720p,1080p三种制式
    u32 Reserver;
	tagTTPFullBannerParam()
	{
		Reserver = 0;
	}
}TTPFullBannerParam;

typedef struct tagTTPBannerParam
{
	u8 byPos; //屏序号（0-2）
	BOOL bAddBanner;//是否设置banner
	EmTpBannerTransparency emTransparency;
	EmTpBannerType emBannerType;
	
	tagTTPBannerParam()
	{
		memset(this, 0, sizeof(struct tagTTPBannerParam));
		bAddBanner = FALSE;
	}
}TTPBannerParam;

typedef struct tagTTPLogoParam
{
	u8 byPos; //屏序号（0-2）
	BOOL bAddLogo; //是否设置logo
	BOOL bUsedInitialLogo; //是否使用kedacom台标
	EmTpLogoType emTpLogoType;
	
	tagTTPLogoParam()
	{
		memset(this, 0, sizeof(struct tagTTPLogoParam));
		bAddLogo = FALSE;
	}
}TTPLogoParam;

 
typedef struct tagTTPConfEpInfo
{
	u16 m_wConfID; 
	TTpCallAddr m_tCallAddr;

	u16 m_Index;
	BOOL32 m_bPermit;
	
	tagTTPConfEpInfo()
	{
		m_wConfID = TP_INVALID_INDEX;
		m_tCallAddr.Clear();
		m_Index = TP_INVALID_INDEX;
		m_bPermit = FALSE;
	}

}TTPConfEpInfo;

typedef struct tagTTpVidCutLine
{
	u8 byIndex;

	u32 m_dwLeft;
	u32 m_dwRight;
	u32 m_dwTop;	
	tagTTpVidCutLine()
	{
		memset(this, 0, sizeof(struct tagTTpVidCutLine));
	};
	
}TTpVidCutLine;

typedef struct tagTTpIconInfo
{	
	u8 byIndex;
	BOOL bOpen;
	u32 dwXPos;
	u32 dwYPos;
	u32 dwIconID; //EN_ICON_PACKLOST , EN_ICON_NetIssue etc
	//业务层不使用 pData 域
	//void* pprvData;
	tagTTpIconInfo()
	{
		memset(this, 0, sizeof(struct tagTTpIconInfo));
	};
}TTpIconInfo;



typedef struct tagTTpAudMix
{	
	BOOL abAudMix[AUD_MIX_NUM];
	tagTTpAudMix()
	{
		memset(this, 0, sizeof(struct tagTTpAudMix));
	};
}TTpAudMix;


//add by sam
#define UMS_MAX_VID_SOURCE_NUM   10// 视频源最大个数
#define UMS_MAX_VID_ALIAS_LEN	 16// 视频源别名最大长度
typedef struct tagTVidAliasInfo
{	
	u8	m_byIndex;	// 视频源索引	
	s8  m_abyAlias[UMS_MAX_VID_ALIAS_LEN];	// 视频源别名 [16]H.323会场最大视频源别名长度	
	tagTVidAliasInfo()	
	{		
		Clear();	
	}		
	void Clear()	
	{		
		memset(this, 0, sizeof(tagTVidAliasInfo));	
	}	
}TVidAliasInfo;
typedef struct tagTVidSourceInfo
{	
	u8	m_byNum;	
	TVidAliasInfo m_atVidInfo[UMS_MAX_VID_SOURCE_NUM]; // 视频源信息 [10]H.323会场最大视频源数	
	tagTVidSourceInfo()	
	{		
		Clear();	

	}		
	void Clear()	
	{		
		memset(this, 0, sizeof(tagTVidSourceInfo));	
	}		
	tagTVidSourceInfo& operator = (tagTVidSourceInfo& tInfo)	
	{		
		if (this != &tInfo)		
		{	
			m_byNum = tInfo.m_byNum;			
			for (u16 wIndex = 0; wIndex < m_byNum; ++wIndex)			
			{				
				m_atVidInfo[wIndex].m_byIndex = tInfo.m_atVidInfo[wIndex].m_byIndex;				
				memcpy(m_atVidInfo[wIndex].m_abyAlias, tInfo.m_atVidInfo[wIndex].m_abyAlias,					
						sizeof(tInfo.m_atVidInfo[wIndex].m_abyAlias));			
			}		
		}		
		return *this;	
	}
}TVidSourceInfo;

typedef struct tagTTPKedaManuProductTP
{
	u8	m_byAgentID; 				//暂定此非标内容长度为一个BYTE，用于存储渠道标识代号
	
	tagTTPKedaManuProductTP()
	{
		m_byAgentID = 0;
	}
	
}TTPKedaManuProductTP;


typedef struct tagTVidFeccInfo
{	
	u16	m_wEpID;	// 会场id	
	BOOL32 m_bAllowFecc; // 是否允许远遥	
	u8 m_byVidno;		 // 当前源索引	
	TVidSourceInfo m_tVidSourceInfo;	
	tagTVidFeccInfo()	
	{		
		Clear();	
	}		
	void Clear()	
	{		
		m_bAllowFecc = FALSE;		
		m_byVidno = 0;
		m_wEpID = TP_INVALID_INDEX;
		m_tVidSourceInfo.Clear();	
	}
}TVidFeccInfo;

typedef struct tagTConfVidFeccInfo
{	
	EmTpOprType		m_emOpr;		// 变更类型	
	BOOL32			m_bLastPack; 	// 是否最后一包	
	u16				m_wConfID;		// 会议ID		
	u16				m_wNum;			
	TVidFeccInfo	m_atVidFeccList[TP_REFRESH_LIST_THREE];	
	tagTConfVidFeccInfo()	
	{		
		m_emOpr = tp_OprType_Add;		
		m_wConfID = TP_INVALID_INDEX;		
		m_wNum = 0;		
		m_bLastPack = TRUE;		
		memset(m_atVidFeccList, 0, sizeof(m_atVidFeccList));	
	}	
	tagTConfVidFeccInfo& operator = (tagTConfVidFeccInfo& tInfo)	
	{		
		if (this != &tInfo)		
		{			
			m_emOpr = tInfo.m_emOpr;			
			m_bLastPack = tInfo.m_bLastPack;			
			m_wConfID = tInfo.m_wConfID;			
			m_wNum = tInfo.m_wNum;			
			for (u16 wIndex = 0; wIndex < m_wNum; ++wIndex)			
			{				
				m_atVidFeccList[wIndex].m_wEpID = tInfo.m_atVidFeccList[wIndex].m_wEpID;				
				m_atVidFeccList[wIndex].m_bAllowFecc = tInfo.m_atVidFeccList[wIndex].m_bAllowFecc;				
				m_atVidFeccList[wIndex].m_byVidno = tInfo.m_atVidFeccList[wIndex].m_byVidno;				
				m_atVidFeccList[wIndex].m_tVidSourceInfo = tInfo.m_atVidFeccList[wIndex].m_tVidSourceInfo;			
			}		
		}		
		return *this;	
	}
}TConfVidFeccInfo;
//end add

//矩阵服务器信息
typedef struct tagTTPMatrixServerInfo
{
	u32_ip m_dwSerIP;

	tagTTPMatrixServerInfo()
	{ 
		memset(this, 0, sizeof(struct tagTTPMatrixServerInfo)); 
	};
}TTPMatrixServerInfo;

//卡农麦克10配置信息
typedef struct tagTTpMic10Info
{
	EmAudGroupIndex m_emGroupIndex;   //音频接口的组索引号
	BOOL m_bAudioPort;     //是否选用音频接口
	u8   m_byVolume;       //选中接口的音量
public:
	tagTTpMic10Info()
	{ 
		memset( this, 0, sizeof(struct  tagTTpMic10Info));
	}
}TTpMic10Info;

typedef struct tagTTPTelnetInfo
{
	BOOL      bOpen;
	s8        achUserName[TP_MAX_ALIAS_LEN + 1];
	s8        achPassword[TP_MAX_ALIAS_LEN + 1];
	
	tagTTPTelnetInfo()
	{
		memset(this, 0 , sizeof( tagTTPTelnetInfo ));
	}
	
}TTPTelnetInfo;

typedef struct tagTTPFtpInfo
{
	BOOL      bOpen;
	s8        achUserName[TP_MAX_ALIAS_LEN + 1];
	s8        achPassword[TP_MAX_ALIAS_LEN + 1];
	
	tagTTPFtpInfo()
	{
		memset(this, 0 , sizeof( tagTTPFtpInfo ));
	}
	
}TTPFtpInfo;

typedef struct tagTTpMicState
{
	BOOL m_byMicState[TP_MIC_NUM];
	
	tagTTpMicState()
	{
		memset ( this, 0, sizeof( struct tagTTpMicState) );		
	}
	
}TTpMicState;

typedef struct tagTTpMicSingleState
{
	BOOL m_byMicState;
	
	tagTTpMicSingleState()
	{
		memset ( this, 0, sizeof( struct tagTTpMicSingleState) );		
	}
	
}TTpMicSingleState;

//单个路由参数结构 
typedef struct tagTTpNetIpRouteParam
{
    u32 m_byEthId;         // 网口id 
    u32 m_dwDesIpNet;      // 目的子网，网络字节序 
    u32 m_dwDesIpMask;     // 掩码，网络字节序 
    u32 m_dwGwIpAdrs;      // 网关ip地址，网络字节序 
    u32 m_dwRoutePri;      // 路由优先级(1-255)，默认为0 
public:
	tagTTpNetIpRouteParam()
	{ 
		memset( this, 0, sizeof(struct tagTTpNetIpRouteParam));
	}
}TTpNetIpRouteParam;

// 多个路由参数结构 
typedef struct tagTTpNetAllIpRouteInfo
{
    u32 m_dwIpRouteNum;    // 得到的实际路由个数 
    TTpNetIpRouteParam m_tNetIpRouteParam[TP_ROUTE_COUNT];
public:
	tagTTpNetAllIpRouteInfo()
	{ 
		memset( this, 0, sizeof(struct tagTTpNetAllIpRouteInfo));
	}
}TTpNetAllIpRouteInfo;

//add by youjx 2017.8.11
typedef struct tagTTPNtpSer
{
    u32_ip dwSerIP;
public:
    tagTTPNtpSer()
    { 
        memset(this, 0, sizeof(struct tagTTPNtpSer)); 
    }
}TTPNtpSer;
//add end

//用户密码输入次数
typedef struct tagTTpUserSafe
{
	s8	m_achname[MAX_CHARLENGTH+1]; //用户名
	u8  m_byNumber;                  //密码输入次数
	u32 m_dwTime;                    //当前时间
	BOOL m_bIsExist;                  //用户是否存在
public: 
	tagTTpUserSafe()
	{ 
		memset( this, 0, sizeof(struct tagTTpUserSafe));
	}
	void Clear()	
	{		
		memset( this, 0, sizeof(tagTTpUserSafe) );	
	}
}TTpUserSafe;

//密码周期性更新信息
typedef struct tagTTpPasswordUpdateInfo
{
	BOOL m_bOpen;                           //是否开启更新
	EmUpdateFrequency  m_emUpdateFrequency; //更新频率
	TTPTime m_tTime;                        //当前时间
public: 
	tagTTpPasswordUpdateInfo()
	{ 
		memset( this, 0, sizeof(struct tagTTpPasswordUpdateInfo));
	}
}TTpPasswordUpdateInfo;

//AUX OUT输出音量
typedef struct tagTTpAuxOutVolume
{
	u8 byOut1Vol;
	u8 byOut2Vol;
public:
	tagTTpAuxOutVolume()
	{
		memset( this, 0,sizeof(struct tagTTpAuxOutVolume));
	}
}TTpAuxOutVolume;

//Superadmin用户权限
typedef struct tagTTpSuperUser
{
	u8  m_byLockNumber;                  //密码锁定次数
	u32 m_dwLockTime;                    //密码锁定时间
public: 
	tagTTpSuperUser()
	{ 
		memset( this, 0, sizeof(struct tagTTpSuperUser) );
	}
	void Clear()	
	{		
		memset( this, 0, sizeof(tagTTpSuperUser) );	
	}
}TTpSuperUser;

typedef struct tagTTPSingleMatrixInfo
{
	BOOL   m_bHaveSrc;//是否有源
	s8	   m_achname[MAX_CHARLENGTH+1]; //演示源名字
	public: 
		tagTTPSingleMatrixInfo()
		{ 
			memset( this, 0, sizeof(struct tagTTPSingleMatrixInfo) );
		}
		void Clear()	
		{		
			memset( this, 0, sizeof(tagTTPSingleMatrixInfo) );	
		}
}TTPSingleMatrixInfo;

typedef struct tagTTPMatrixInfo
{	
	TTPSingleMatrixInfo	   m_tMatrixInfo[MAX_MATRIXLENGTH]; 
	public: 
		tagTTPMatrixInfo()
		{ 
			memset( this, 0, sizeof(struct tagTTPMatrixInfo) );
		}
		void Clear()	
		{		
			memset( this, 0, sizeof(tagTTPMatrixInfo) );
		}
}TTPMatrixInfo;

typedef struct tagTTPMatrixName
{
	u8   m_byPose;//源位置，范围0-10
	s8	 m_achname[MAX_CHARLENGTH+1]; //演示源名字
	public: 
		tagTTPMatrixName()
		{ 
			memset( this, 0, sizeof(struct tagTTPMatrixName) );
		}
		void Clear()	
		{		
			memset( this, 0, sizeof(tagTTPMatrixName) );	
		}
}TTPMatrixName;

typedef struct tagTTPSlectView
{
	u8   m_byPose;   //屏位置
	BOOL m_bIsLocal; //是本地回显还是本地双流回显
	BOOL m_bIsSet;   //设置和取消
	public: 
		tagTTPSlectView()
		{ 
			memset( this, 0, sizeof(struct tagTTPSlectView) );
		}
		void Clear()	
		{		
			memset( this, 0, sizeof(tagTTPSlectView) );	
		}

}TTPSlectView;

typedef struct tagTTPModulTerInfo
{
	BOOL m_bMute;
	BOOL m_bQuite;
	u8   m_byInputVolme;
	u8   m_byOutVolme;
	BOOL m_bPVHasVideo;
	BOOL m_bSVHasVideo;
	public: 
		tagTTPModulTerInfo()
		{ 
			memset( this, 0, sizeof(struct tagTTPModulTerInfo) );
		}
		void Clear()	
		{		
			memset( this, 0, sizeof(tagTTPModulTerInfo) );
		}
}TTPModulTerInfo;

typedef struct tagTRmMgrMtMPAddr 
{
public:
    tagTRmMgrMtMPAddr()
    {
        Clear();
    }

    void Clear()
    {
        memset(this, 0, sizeof(struct tagTRmMgrMtMPAddr));
    }

public:
    TMtMPAddr m_tMtMPAddr;
    BOOL m_bUsed;

}TRmMgrMtMPAddr;

//Ds交换附加结构
typedef struct tagTRmMgrDs 
{
public:
    tagTRmMgrDs()
    {
        Clear();
    }

    void Clear()
    {
        memset(this, 0, sizeof(struct tagTRmMgrDs));
    }

public:
    u16 m_wPos;
    //u8  m_byFlag；//0 发送， 1：接收 
    TTPTransAddr m_tSendPort; //相对Ds来讲
    BOOL m_bUsed;
}TRmMgrDs;

typedef struct tagTFtpFileInfo 
{
public:
    tagTFtpFileInfo()
    {
        Clear();
    }

    void Clear()
    {
        memset(this, 0, sizeof(struct tagTFtpFileInfo));
    }

public:
    u32 m_dwFtpServerIP;
    u16 m_wFtpServerPort;
    s8  m_achFtpUsrName[MP_FTP_SERVER_USR_LEN_MAX];
    s8  m_achFtpPwd[MP_FTP_SERVER_PWD_LEN_MAX];
    u8  m_byFtpFileNum; 
    s8  m_aachFtpFile[MP_FTP_SERVER_TRANSFILE_NUM_MAX][MP_FTP_SERVER_TRANSFILE_LEN_MAX];//文件列表
}TFtpFileInfo;

//云化平台IP配置
typedef struct tagTTPCloudPlatServerCfg 
{
public:
    tagTTPCloudPlatServerCfg()
    {
        Clear();
    }

    void Clear()
    {
        memset(this, 0, sizeof(struct tagTTPCloudPlatServerCfg));
    }

public:
    BOOL m_bEnable;
    s8  m_achServerIP[TP_ADDR_LEN_MAX];
    u16 m_wServerPort;
    s8  m_achUsrName[TP_PWD_LEN_MAX];
    s8  m_achPwd[TP_USR_LEN_MAX];   
}TTPCloudPlatServerCfg;

//会议密码信息
typedef struct tagTTPConfPassword
{
    TTPTerLabel m_tTer;
    s32         m_nPassLen;
    u8          m_abyPassword[TP_MAX_CONFPWD_LEN+1];
    tagTTPConfPassword()
    {
        memset( this, 0, sizeof(tagTTPConfPassword) );
    }
    void Clear()	
    {		
        memset( this, 0, sizeof(tagTTPConfPassword) );	
    }

}TTPConfPassword;

#endif // _h_tpcommonstruct_h__