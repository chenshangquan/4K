#ifndef _h_tpcommontype_h__
#define _h_tpcommontype_h__

//MTType begin.
#include "osp.h"

enum EmTPDevRegUpdateSer
{
	emDevInvalid = -1,
		emTPTPad_Win7,
		emTPTPad_Android,
		emTPTPad_IOS,
		emTPCns_T300A,
		emTPCns_T300B,
};

//升级类型
enum EmTPUpdateType  
{
	emTPUpdateForced,  //强制升级
		emTPUpdateSelected  //选择升级
};


/**********************************add enum begin**********************************/

enum EmWiFiLinkStat
{
	emWiFiIdle = 0,
	emWiFiConnecting,
    emWiFiConnectFailed,
    emWiFiConnected,
    emWiFiDisconnecting,
    emWiFiDisconnected
};

// enum EmWiFiLinkStatus
// {
// 	emWiFiIdle = 0,
//     emWiFiConnected,
//     emWiFiConnecting,
//     emWiFiConnectFailed,
//     emWiFiDisconnected,
//     emWiFiDisconnectFailed,
//     emWiFiDevicePullIn,
//     emWiFiDevicePullOut
// };

enum EmWiFiSelType
{
    emWiFiCfgSel = 0,
    emWiFiScanSel
};

enum EmWiFiNetType
{
    emWiFiAdHoc = 0,
    emWiFiInfra
};

enum EmWiFiEncryptType
{
    emWiFiEncryptNone = 0,
    emWiFiEncryptWep,
    emWiFiEncryptWpa,
    emWiFiEncryptWpa2
};

enum EmWiFiEncryptArithmetic
{
	emWiFiArithNone = 0,
	emWiFiArithWep40,
	emWiFiArithTkip ,
	emWiFiArithWrap,
	emWiFiArithAes,						/* aes */
	emWiFiArithWep104	
};

// VOD REJ Code 
//------------------------消息的REJ码-------------------------------------------
enum EmVODRejCode 
{	
	emVODNoReason = 0, // 未知错误
	emVODFileNotFound = 1, // 文件未找到
	emVODPalyNotStarted = 2, //播放未开始
	emVODMaxUser = 3, // 在线用户已达到最大允许数量
	emVODUserNotExist = 4, // 用户名不存在	
	emVODUserLogined = 5, // 该用户已经登录
	emVODInvalidedPassword = 6, // 密码错误
	emVODMEDIAVODInvalidedFileNameType = 7, // Client <-- Server ,文件名为空或不是ASF文件
	emVODPlayBusy = 9, // Client <-- Server ,正在发送上一次的码流请求
	emConnectFailed = 10,
	emDisconnect = 11 ,// 连接中断
	emVODNoError      //操作成功
};

//VOD 状态
enum EmVODState
{
	emVODIdle         ,//空闲
	emVODLogin        ,//正在登陆
	emVODFileListQuery,//正在获取文件列表
	emVODFileInfoQuery ,//正在查询播放文件信息
	emVODPlay  ,//正在播放
	emVODPause    ,//暂停
	emVODStop  ,   //停止
	emVODSeek  ,   //指定位置播放
	emVODActiveEnd
};

//横幅
enum EmTextAlign
{
	emAlignLeft = 0,//居左
	emAlignCenter,//居中
	emAlignRight//居右
};

enum EmRollMode
{
	emStatic = 0,
	emRight2Left,
	emDown2Up
};

enum EmRollSpeed
{
	emSlower = 0,
	emSlow,
	emNormal,
	emFast,
	emFaster
};

//串口停止位类型
enum EmStopBits
{
    em1StopBit =0,
    em1HalfStopBits=1,
    em2StopBits = 2
};



//串口校验位类型
enum EmParityCheck
{
    emNoCheck = 0 ,//无校验
    emOddCheck =1 ,//奇校验
    emEvenCheck =2,//偶校验
};

//串口类型
enum EmSerialType
{
    emRS232 = 0,
    emRS422 = 1,
    emRS485 = 2,
	emSerialTcpip =3,
	emRS422_1 = 4,
	emRS422_2 = 5,
	emRS422_3 = 6,
	emRSCom_1 = 7,
	emRSCom_2 = 8,
	emRSCom_3 = 9,
	emRSCom_4 = 10,
	emRSCom_5 = 11,
	emRSCom_6 = 12
};

//语言类型
enum EmLanguage
{
    emEnglish  = 0,
    emChineseSB = 1,
	emLangeEnd
};




//协议类型
enum EmConfProtocol
{
	emH323  = 0, 
	emH320  = 1,
	emSIP   = 2,
	emSat   = 3, 
	emInvalidConfProtocel
};

//编码方式
enum EmEncodeMode
{
    emQualityFirst  = 0, 
    emSpeedFirst    = 1,
    
};

//丢包恢复类型
enum EmLostPackageRestore
{
    emLPQualityFirst  = 0, 
    emLPSpeedSlow     = 1,
    emLPSpeedNormal   = 2,
    emLPSpeedFast     = 3,
};

//矩阵类型
enum EmMatrixType
{
	emMatrixInner   = 0, 
	emMatrixOuter   = 1,
	emMatrixVas     = 2,
};

//双流显示模式
enum EmDualVideoShowMode
{
    emDualVideoOnSigleScreen  =0,//单屏双显
    emEachVideoOwnScreen      =1,//双屏双显
	emTripleVideoOnSingleScn  =2 //单屏三显
};

//显示比例
enum EmDisplayRatio
{
	emDR4to3      = 0, //4:3
	emDR16to9     = 1, //16:9
	emDRAuto      = 2, //0:0
};

//视频类型
enum EmVideoType
{
   emPriomVideo = 0 ,//主视频
   emSecondVideo = 1//第二路视频
};


//视频制式类型
enum EmVideoStandard
{
    emPAL  =0 ,
    emNTSC = 1 ,
//    emSECAM = 2
};

//视频源类型
enum EmVideoInterface
{
    emVGA    = 0, 
    emSVideo = 1,
    emCVideo = 2,
};

//终端视频端口
enum EmMtVideoPort
{
	//hd2.0视频源定义
	emMtVGA   =0 , //VGA 
	emMtSVid    , //S 端子
	emMtPC      , //PC
	emMtC1Vid   ,  //C1端子   DVI 1
	emMtC2Vid   ,  //C2端子   DVI 2
	emMtC3Vid   ,  //C3端子   DVI 3
	emMtC4Vid   ,  //C4端子   c
	emMtC5Vid   ,  //C5端子   sdi 1
	emMtC6Vid   ,  //C6端子   sdi 2

	emMtExternalVid = 10,//外置矩阵映射基始值
	emMtVideoMaxCount = 74, //最多支持视频源个数
	emMtVidInvalid = 255 
};

//应答方式类型
enum EmTripMode
{
    emTripModeAuto      =0,  //自动
    emTripModeManu      =1,  //手动 
	emTripModeNegative  =2,   //拒绝、关闭
};

//台标类型
enum EmLabelType
{
    emLabelAuto    =0,   //自动
    emLabelUserDef =1,  //自定义
    emLabelOff     =2  //关闭
};

//E1链路检测类型
enum EmDLProtocol
{
    emPPP   = 0, 
    emHDLC  = 1,
    emPPPOE = 2,
    emMP    = 3
};

//E1验证类型
enum EmAuthenticationType
{
    emPAP  = 0,
    emCHAP = 1
};

//帧率单位类型
enum EmFrameUnitType
{
    emFrameSecond =0,
    emSecondFrame =1
};

// 媒体类型
enum EmMediaType
{
	emMediaVideo = 1, //视频
	emMediaAudio = 2, //音频
	emMediaAV    = 3, //音频和视频
};


//视频协议类型
enum EmVideoFormat
{
    emVH261     = 0,
    emVH262     = 1,//MPEG2
    emVH263     = 2,
    emVH263plus = 3,
    emVH264     = 4,
    emVMPEG4    = 5,

	emVEnd		
};

//音频协议类型
enum EmAudioFormat
{
    emAG711a  = 0,
    emAG711u  = 1,
    emAG722   = 2,
    emAG7231  = 3,
    emAG728   = 4,
    emAG729   = 5,
    emAMP3    = 6,
	emAG721   = 7,
	emAG7221  = 8,
	emAG719   = 9,
	emAMpegAACLC =10,
	emAMpegAACLD = 11,

	emAEnd	 
};


//分辨率类型
enum EmVideoResolution
{
    emVResolutionAuto     = 0,   //自动
    emVSQCIF              = 1,   //SQCIF88x72
	emVQCIF               = 2,   //QCIF176x144
    emVCIF                = 3,   //CIF352x288
    emV2CIF               = 4,   //2CIF352x576
    emV4CIF               = 5,   //4CIF704x576
    emV16CIF              = 6,   //16CIF1408x1152

	emVHD480i720x480      = 7,   //480i720x480
	emVHD480p720x480      = 8,   //480p720x480
	emVHD576i720x576      = 9,   //576i720x576
	emVHD576p720x576      = 10,  //576p720x576

	emVHD720p1280x720     = 11,  //720p1280x720
	emVHD1080i1920x1080   = 12,  //1080i1920x1080
	emVHD1080p1920x1080   = 13,  //1080p1920x1080
	
		
	emVGA352x240          = 14,  //352x240
	emVGA704x480          = 15,  //704x480
	emVGA640x480          = 16,  //VGA640x480
	emVGA800x600          = 17,  //SVGA800x600
	emVGA1024x768         = 18,  //XGA1024x768
	emVGA1280x768         = 19,  //WXGA1280x768
	emVGA1280x800         = 20,  //WXGA1280x800
	emVGA1366x768         = 21,  //WXGA1366x768
	emVGA1280x854         = 22,  //WSXGA1280x854
	emVGA1440x900         = 23,  //WSXGA1440x900
	emVGA1280x1024        = 24,  //SXGA1280x1024
	emVGA1680x1050        = 25,  //SXGA+1680x1050
	emVGA1600x1200        = 26,  //UXGA1600x1200
	emVGA1920x1200        = 27,  //WUXGA1920x1200

	emVSQCIF112x96        = 28,
	emVSQCIF96x80         = 29,
	emV320x192            = 30,
	emV432x240            = 31,
	emV480x272            = 32,
	emV640x368            = 33,
	emV864x480            = 34,
	emV960x544            = 35,
	emV1440x816           = 36,

	emVResEnd = 50,
};

//QOS类型服务
enum EmQoS
{
   emDiffServ  = 0,      //区分服务
   emIPPrecedence  = 1  //IP优先
};

//TOS 类型
enum EmTOS
{
	emTOSNone        = 0,//不使用
	emTOSMinCost     = 1,//最小开销
	emTOSMaxReliable = 2,//最高可靠性
	emTOSMaxThruput  = 3,//最大吞吐量
	emTOSMinDelay    = 4,//最小延迟
};


//位置
enum EmSite
{
    emLocal = 0,  //本地
    emRemote    //远端
};

//共计10个通道
enum EmChanType
{
	emChanSendAudio,
	emChanSendPrimoVideo,
	emChanSendSecondVideo,
	emChanSendFecc,
	emChanSendT120,

	//接收通道
	emChanRecvAudio,
	emChanRecvPrimoVideo,
	emChanRecvSecondVideo,
	emChanRecvFecc,
	emChanRecvT120,

	emChanTypeEnd	
};

//编解码器各个部件
enum EmCodecComponent
{
	emPriomVideoEncoder  =0,
	emPriomVideoDecoder  ,

	emSecondVideoEncoder ,
	emSecondVideoDecoder ,

	emAudioEncoder ,
	emAudioDecoder ,
	emCodecComponentEnd,
};

//终端型号
enum EmMtModel
{
	emUnknownMtModel=0,
	emPCMT  =1    ,//桌面终端
	em8010      ,
	em8010A     ,
	em8010Aplus ,//8010A+
	em8010C     ,
	em8010C1    ,//8010C1
	emIMT       ,
	em8220A     ,
	em8220B     ,
	em8220C     ,
	em8620A     ,
	emTS6610E   ,
	emTS6210    ,
	em8010A_2   ,
	em8010A_4   ,
	em8010A_8   ,
	em7210      ,
	em7610      ,
	emTS5610    ,
	emTS6610    ,
	em7810      ,
	em7910      ,
	em7620_A    ,
	em7620_B    ,
	em7820_A	,
	em7820_B	,
	em7920_A	,
	em7920_B	

};
// << 文件系统类型 >>
enum EmFileSys
{
	emRAWFS=1,//raw file system [ramdisk + rawblock + tffs]
	emTFFS  //tffs
};
//加密算法
enum EmEncryptArithmetic
{
	emEncryptNone = 0,
	emDES         = 1,
	emAES         = 2,
	emEncryptAuto = 3,

	emEncryptEnd
	
};

//操作
enum EmAction
{
    emActStart,
    emActStop,
    emActPause,
    emActResume,
};

//终端使能操作
enum EmOptRet
{
	emEnable,
	emDisable,
};


//会议模式
enum EmConfMode
{
	emP2PConf = 0,//点对点会议
	emMCCConf = 1 //多点会议
};


//地址类型
enum EmMtAddrType
{
	emIPAddr =0,
	emE164   ,
	emH323id ,
	emDialNum,
	emSipAddr	
};

//呼叫模式
enum EmCallMode
{
	emJoin,
	emCreate,
	emInvite
};


//控制方向
enum EmDirection
{
	emUP   =0,
	emDown   ,
	emLeft   ,
	emRight 
};

//呼叫状态
enum EmCallState
{
	emCS_Idle  ,
	emCS_Calling ,      //正在发起呼叫
	emCS_P2P ,      //点对点会议
	emCS_MCC ,      //多点会议
	emCS_Hanup        //挂断
};


//呼叫状态
enum EmCallSiteState
{
	emCSS_IDLE,
	emCSS_Init ,
	emCSS_Waiting ,      //正在发起呼叫
	emCSS_Connected ,      //点对点会议
	emCSS_Failed
};

//传输模式
enum EmTransMode
{
	emUnicast,  //单播
	emBroadcast, //广播
	emMulticast //组播
};

//双流源类型
enum EmDualSrcType
{
    emDualVGA = 0,
	emDualVideo = 1,
	emDualPC = 2
};



enum EmMtInstType
{
	emMtService = 0 ,
	emMtUI          ,
	emMtConsole     ,
	emMtH323Service ,
	emMtH320Service ,
	emMtSipService  ,
	emMtH323StackIn ,
	emMtH323StackOut,
	emMtMP          ,
	emMtDevice      ,
	emMtAgent       ,
	emMtSipStackIn  ,
	emMtSipStackOut ,
};

//画面合成风格定义
enum EmVMPStyle
{
    emVMPDynamic       =   0 ,  //动态分屏(仅自动合成时有效)
    emVMPOne         =   1 ,  //一画面
    emVMPVTwo        =   2 ,  //两画面：左右分 
    emVMPHTwo        =   3 ,  //两画面: 一大一小
    emVMPThree       =   4 ,  //三画面
    emVMPFour        =   5 ,  //四画面
    emVMPSix         =   6 , //六画面 
    emVMPEight       =   7 ,  //八画面
    emVMPNine        =   8 ,  //九画面
    emVMPTen         =   9 ,  //十画面
    emVMPThirteen    =   10,  //十三画面
    emVMPSixteen     =   11,  //十六画面
    emVMPSpecFour    =   12,  //特殊四画面 
    emVMPSeven       =   13,  //七画面
	emVMPSpecThirteen  =   14,  //特殊十三画面（用于华为MCU）
	emVMPTwenty      =   15,  //高清MPU的二十画面（只用于高清MPU）
};


//画面合成成员类型定义
enum EmVMPMmbType
{
    emVMPMmbMCSspec    = 1,  //会控指定 
    emVMPMmbSpeaker    = 2,  //发言人跟随
    emVMPMmbChairman   = 3,  //主席跟随
    emVMPMmbPoll       = 4,  //轮询视频跟随
    emVMPMmbVAC        = 5,	//语音激励(会控不要用此类型)
};

//短消息业务类型
enum EmSMSType//MS
{
	emSMSSingleLine  = 0,  //短消息
	emSMSPageTitle   = 1,  // 翻页字幕
	emSMSRollTitle   = 2,  // 滚动字幕
	emSMSStaticTitle = 3,  // 静态字幕
};


enum EmMtFile
{
    emMtFileBegin  = 0,//终端文件类型开始
	emMtConfigFile   =1,//配置文件
	emMtOldConfigBakFile     ,//旧配置文件备份
	emMtDebugConfiFile, //调试配置文件
	emMtCameraCommandFile,//摄像头命令文件
	emMtCameraPresetPostionFile,//摄像头预置位保存文件
	emMtExternMaxtrixCommandFile,//外置矩阵命令问文件
	emMtExternMaxtrixPortNameFile,//外置矩阵端口名文件
	emMtInnerMaxtrixSchemeFile,//内置矩阵方案文件
	emMtStreamMediaHtmlFile,//流媒体网页文件
	emMtResourceFile,//终端资源文件
	emMtZipResourceFile,//压缩终端资源文件
	emMtSymbolFile,//终端台标图片文件
	emMtBannerFile,//终端横幅文件
	emMtStaticPicFile,//终端静态图片文件
	emMtResInBin,//Bin文件中的资源文件
	emMtAddressBookEx,//扩展地址薄文件
	emMtUpdateSysFile,//版本升级文件
	emMtMinitorFile, //监视文件
	emMtZipFile,//应用程序
	emMtHintFile,//界面显示资源文件
	emMtKeyFile, //mclicense文件
    emMtInnerPxyFile,//内置代理服务器配置文件
	emMtThreadBlockFile,//线程阻塞信息文件
	emMtLogFile,//日志文件
	emMtUserWordFile,//用户词库文件
	emMtKdvLog, //日志配置文件
	emMtFileEnd //终端文件类型结束
};
typedef u32   u32_ip;

enum EmCallRate
{
	emRaten64 = 0,							/*(0)64kbps*/
	emRaten2m64,							/*(1)2×64kbps*/
	emRaten3m64,							/*(2)3×64kbps*/
	emRaten4m64,							/*(3)4×64kbps*/
	emRaten5m64,							/*(4)5×64kbps*/
	emRaten6m64,							/*(5)6×64kbps*/
	emRater384,							/*(6)384kbps*/
	emRater1536,							/*(7)1536kbps*/
	emRater1920,							/*(8)1920kbps*/
	emRater128,							/*(9)128kbps*/
	emRater192,							/*(10)192kbps*/
	emRater256,							/*(11)256kbps*/
	emRater320,							/*(12)320kbps*/
	emRater512,							/*(13)512kbps*/
	emRater768,							/*(14)768kbps*/
	emRater1152,							/*(15)1152kbps*/
	emRater1472,							/*(16)1472kbps*/
	/*(注：V2.0版本中新增3M、4M、6M、8M速率)*/
	emRater3M,							/*(17)3M(2880kbps)*/
	emRater4M,							/*(18)4M(3840kbps)*/
	emRater6M,							/*(19)6M(5760kbps)*/
	emRater8M,							/*(20)8M(7680kbps)*/
	emRaterLastOne
};


//PC windows 采集格式
enum EmPCCapFormat
{
	emCapPCFrameBMP  = 0,//RGB24位图;
	emCapPCFrameUYUY = 1,//yuv4:2:2格式
	emCapPCFrameI420 = 2,//yuv4:2:0格式
};

//画中画显示模式
enum EmPiPMode
{
	emPiPClose   = 0,//画中画关闭
	emPiPRightBottom ,//画中画小画面显示在右下角
	emPiPLeftBottom  ,//画中画小画面显示在左下角
	emPiPLeftTop     ,//画中画小画面显示在左上角
	emPiPRightTop    ,//画中画小画面显示在右上角
};
// DVB Component
enum EmDVBComponent
{
	emDVBEncoder = 0,
	emDVBPriomVideoDecoder,
	emDVBSecondVideoDecoder
};
enum EmUIPosion
{
	emMT = 0,
	emMTC = 1
};
//呼叫挂断原因
enum EmCallDisconnectReason
{
	emDisconnect_Busy = 1   ,//对端忙
	emDisconnect_Normal     ,//正常挂断
	emDisconnect_Rejected   ,//对端拒绝
	emDisconnect_Unreachable ,//对端不可达
	emDisconnect_Local       ,//本地原因
	emDisconnect_Nnknown      //未知原因
};


//MC 的模式
enum EmMCMode
{
	emMcSpeech  ,//演讲模式
	emMcDiscuss ,//讨论模式
	emMcModeEnd
};


//内嵌mc的画面合成风格
enum EmInnerVMPStyle
{
    emInnerVMPAuto = 0,
	emInnerVMPOne,
	emInnerVMPTwo,
	emInnerVMPThree,
	emInnerVMPFour,
	emInnerVMPFive,
	emInnerVMPSix,
	emInnerVMPTwoBigLittle,
	emInnerVMPThreeBigLittle,
	emInnerVMPFourBigLittle,
	emInnerVMPEnd
};

//内嵌mc的解码器组件号
enum EmVMPComponent
{
	emVMPDecNull = 0,
	emVMPDec1th,
	emVMPDec2th,
	emVMPDec3th,
	emVMPDec4th,
	emVMPDec5th,
	emVMPDecLocal,
	emVMPEnd
};


//pcmt视频源类型
enum EmCapType
{
   emAudioOnly = 1, //
   emCameraOnly,
   emACBoth,
   emDesktopOnly,
   emADBoth,
   emFileAVBoth  
};
//pppoe状态
enum EmPPPoEState
{
	emFree,
	emLinking,
	emLinkup,
	emLinkdown,
	emUserError,
	emTimeOut,
	emAgentError
};

enum EmDhcpState
{
	emDhcpFree,
	emDhcpLinkup,
	emDhcpLinkdown,
};

enum EmAddrGroupOptType
{
    emCallIn,
	emCallOut,
	emUserDef,
	emTemplate,
	emSiteCall,
	emMissed,
	emUserDefExt0,
	emUserDefExt1,
	emUserDefExt2,
	emUserDefExt3,
	emUserDefExt4,
	emUserDefExt5,
	emInvalid
};

enum EmHotKeyType
{
	emApplySpeak,
	emApplyChair,
	emPrevPage,
	emNextPage,
	emBack,
	emLoop,
	emHotkeyEnd,
	emAEC,
	emDial,
};

enum EmMtOSType
{
	emWindows,
    emVxworks,
	emLinux
};

enum EmFxoState
{
    emFxoIdle,
    emFxoCalling, 
    emFxoConnect,
};

// 扬声器音量大小类型
enum EmMtLoudspeakerVal
{
	emLoudspeakerLow = 0,
	emLoudspeakerMiddle,
	emLoudspeakerHigh,
};

// 重传时所选择的网络类型
enum EmNetType
{
	emInternet = 0,
	emSpecial,
	emVPN,
};

//T2终端系统运行状态标志
enum EmSysRunSuccessFlag
{	
	emSysNoUpdateOperation = 0,
	emSysUpdateVersionRollBack,
	emSysUpdateVersionSuccess,
	emSysSetUpdateFlagFailed,
};

//mcu通知终端的信息类型  
enum EmMcuNtfMsgType
{
	emMsgNoneNtf =0,
	emMsgBePolledNextNtf,
	
};




struct TDATAINFO
{
	//数据类型
	int type ;
	//数据类型大小
	int size ;
	//数据个数
	int arraysize;
	//数据地址偏移量
	int offset;
	//成员变量名称
	char* member;
};

struct TENUMINFO
{
	char* descrip;
	int   val;
};

// 终端硬件自动化测试类型 add by wangliang 2007/02/05
enum EmAutoTestType 
{
    emAutoTestTypeBegin,            //测试类型开始
        
    emAutoTestEth0Func,             //网口0功能测试
	emAutoTestEth1Func,             //网口1功能测试
	emAutoTestE1Func,               //E1功能测试
    emAutoTestAudioLoopBackFunc,    //音频环回功能测试
    emAutoTestVideoLoopBackFunc,    //视频环回功能测试 - C端子  
	emAutoTestSDI1InAllOutFunc,     //输入输出测试：SDI1输入
	emAutoTestSDI2InAllOutFunc,     //输入输出测试：SDI2输入
	emAutoTestDVI1InAllOutFunc,     //输入输出测试：DVI1输入
	emAutoTestDVI2InAllOutFunc,     //输入输出测试：DVI2输入
	emAutoTestDVI3InAllOutFunc,     //输入输出测试：DVI3输入
	emAuotTestCInAllOutFunc,        //输入输出测试：C端子输入
	emAutoTestDVI1InAllOutFunc_YPbPr,    //输入输出测试：DVI1分量输入
	emAutoTestDVI1InAllOutFunc_OSDYPbPr, //开启OSD，分量输入DVI1
	emAutoTestBluerayHDMIFunc,		//蓝光DVD的输出接口接终端HDMI-1输入测试
	emAutoTestBluerayHDMI2Func,     //蓝光DVD的输出接口接终端HDMI-2输入测试
	emAutoTestBluerayHDMI3Func,     //蓝光DVD的输出接口接终端HDMI-3输入测试
	emAutoTestBluerayRCAFunc,       //蓝光DVD的输出接口接终端RCA左右声道输入测试
	emAutoTestCanonMICFunc,			//卡农MIC测试
	emAutoTestDigMICFunc,			//数字MIC测试
    emAutoTestLoudspeakerFunc,      //扬声器功能测试
    emAutoTestCameraRotaFor232Func, //232摄像头转动测试
	emAutoTestCameraRotaFor485Func, //485摄像头测试
    emAutoTestRTCFunc,              //RTC功能测试
    emAutoTestLightFunc,            //指示灯测试
    emAutoTestRemoteCtrlFunc,       //红外接口功能测试
    emAutoTestSetDefault,           //恢复测试标志默认值
	emAutoTestRebootSysFunc,		//重启终端测试

    emAutoTestTypeEnd               //测试类型结束
};

enum EmGKRegFailedReason
{
	emNone,
	emGKUnReachable,
	emInvalidAliase,
	emDupAlias,
	emInvalidCallAddress,
	emResourceUnavailable,
	emUnknown
};

enum EmSleepState
{
	emSleepFail, 
	emWaitSleeping,
	emSleeping, 
	emSleeped, 
	emWaking, 
	emWakeup, 
	emWaitWaking
};

enum EmMtAppName
{
	emMtAgentApp = 0,
	emMtServiceApp,
	emMtGuardApp,
	emMtUEApp,
	emMtStackInApp,
	emMtStackOutApp,
	emMtRcpApp,
	emMtH320StackApp,
	emMtRcSimApp,
	emMtMcApp,
	emMtSnmpApp,
	emMtConfigApp,
	emMtUIApp,
	emMtDeviceApp,
	emMtCodecApp,
	emMtConsoleApp,
	emMtSysApp,
	emMtH323ServiceApp,
	emMtH320ServiceApp,
	emMtSipServiceApp,
	emMtDvbApp,
	emMtDvbssnApp,
	emMtVodClientApp,
	emMtPcdualvideoApp,
	emMtUpgradeApp,
	emMtbApp,
	emMtAutotestApp,
	emMtAutotestClientApp,
	emMtRemoteSimApp,
	emMtThreadDetectApp,
	emMtLogRecvApp,
	emMtLogIOApp,
	emMtProxyClientApp,
	emMtSipStackInApp,
	emMtSipStackOutApp,
	emMtSatServiceApp,
	emMtTpRegApp,
	emMtAppEnd = 49,
};

enum HD_PORT_MASK
{
	//PORT_HDMI =  0x01,
	//PORT_SDI =   0x02,
	PORT_SDI =  0x01,
	PORT_HDMI =   0x02,	
	PORT_YPrPb1 = 0x04,
	PORT_YPrPb2 = 0x08,	
	PORT_VGA = 0x10,
	PORT_C0 = 0x20,
};

enum EmHDAudPortIn
{
	emAudInCL  = 0,
	emAudInCR,
	emAudInCanonL,
	emAudInCanonR,
	emAudInHDMI1,
	emAudInHDMI2,
	emAudInHDMI3,
	emAudInMic1,
	emAudInMic2,
};
enum EmHDAudPortOut
{
	emAudOutCCanon  = 0,
	emAudOutHDMI1,
	emAudOutHDMI2,
	emAudOutHDMI3,
	emAudOutReproducer,
};

//日志是否打开
enum EmLogStatus
{
	emLogClose = 0,
		emLogOpen,
};

//日志导出结果
enum EmLogExportResult
{
	emLogExportFailed = 0,	//失败
	emLogExportSuccess,     //成功
	emLogExportNoDisk,		//没有插入"U"盘
	emLogExportNoFile,		//没有日志文件
	emLogExportTransing,	//有设备正在进行文件拷贝
};

enum EmFecModeType
{
	 emMTFECTYPENONE  =				0x00,
	 emMTFECTYPERAID5 =				0x01,
	 emMTFECTYPERAID5INTERLEAVE =	0x02,
	 emMTFECTYPERAID6 =				0x03,			//此项暂时不允许界面配置
};

enum EmLabelPosType
{ 
	emTopLeft      = 0,
	emTopRight     = 1,
	emBottomLeft   = 2,
	emBottomRight  = 3
};

enum EmMtcBoxCallIndex
{
    emShortCutCall1 = 0,
	emShortCutCall2 = 1,
	emShortCutCall3 = 2,
	emShortCutCall4 = 3 
};

enum EmSipRegFailedReason
{
	emLocalNormalUnreg = 0,
	emInvalidUserNameAndPassword,
	emRegistrarUnReachable,
	emInvalidAlias,
	emUnknownReason
};
/*通道的状态*/
enum EMtRecChnnlState
{
	STATE_IDLE       = 0,	  /*表明是一个未用通道*/
		
		STATE_RECREADY   = 11,	  /*准备录像状态  */
		STATE_RECORDING  = 12,	  /*正在录像  */
		STATE_RECPAUSE   = 13,	  /*暂停录像状态*/
		
		STATE_PLAYREADY  = 21,	  /*准备播放状态 */
		STATE_PLAYREADYPLAY = 22,   /*作好播放准备状态*/
		STATE_PLAYING    = 23,	  /*正在或播放*/
		STATE_PLAYPAUSE  = 24,	  /*暂停播放*/
		STATE_FF         = 25,	  /*快进(仅播放通道有效)*/
		STATE_FB         = 26	  /*快退(仅播放通道有效)*/
};

/*通道类型定义*/
enum EMtRecChnnlType
{
	TYPE_UNUSE      =  0,	/*未始用的通道*/
		TYPE_RECORD     =  1,	/*录像通道  */   
		TYPE_PLAY       =  2	/*播放通道  */
};

//录像方式
enum EMtRecMode
{
	MODE_SKIPFRAME = 0,//抽帧录像
		MODE_REALTIME  = 1  //实时录像
};

enum EMtRecEnum{
	MT_MAXNUM_RECORDER_CHNNL = 32,
		MT_MAXLEN_RECORD_NAME = 64,
		MT_MAXLEN_CONFNAME = 64,
		MT_RECLIST_PACKSIZE =16,
		MT_MAX_REC_NAME = 128
};
enum EmMtRegResult
{
	emMtRegSuccess = 1,
	emMtRegPosError,
	emMtRegTimeOut
};
//MTType end.

enum EmTpRet
{
	tp_Ret_FAILED,
	tp_Ret_Success
};


//HDU PLAY NACK的错误原因
enum EmTpHduPlayNackReason
{
	em_hdu_play_success,
	em_Hdu_Invalid_Index,	//无效的位置索引
	em_Hdu_Invalid_ID,		//无效的ID
	em_Hdu_No_Reged,		//HDU未注册

	em_Hdu_Illegal,			//无效的hdu
	em_Alias_Illegal,		//无效的别名
	em_Monitor_Fial,		//上墙失败
	em_Hdu_PlayNack,		//电视墙服务器拒绝
	em_Same_Alias,			//重名
	em_unknown,				//未知的错误


};

//登录信息
enum EmTpLoginUmsRet
{
	tp_LoginUms_sucess,
	tp_LoginUms_NameError,	//用户名错误
	tp_LoginUms_PwdError,	//密码错误
	tp_LoginUms_MaxLogin,	//达到用户登录上限
	tp_LoginUms_Logged,		//用户已经登录
	tp_LoginUms_SysIniting,	//系统正在初始化
	tp_LoginUms_steals_sucess, //抢断成功
	tp_LoginUms_steals_quit,    //抢断下线
};

//别名类型
enum EmTpAliasType
{
	tp_Alias_Unknow,
	tp_Alias_e164,
	tp_Alias_h323,
	tp_Alias_IP,
};

//操作类型
enum EmTpOprType
{
	tp_OprType_Add,			//增加
	tp_OprType_Del,			//删除
	tp_OprType_Update,		//修改
	tp_OprType_NULL,		//清空
};

//添加会议的会场
enum EmConfAddEpRet
{
	TP_ConfAddEpRet_Unknow,
	TP_ConfAddEpRet_Success,
	TP_ConfAddEpRet_MaxNum,
	TP_ConfAddEpRet_AliasReapeat,
	TP_ConfAddEpRet_ParamError,
	
};

//关键帧检测
enum EmTpIFrameCheckType
{
    TP_IFrameCheck_Speaker,				//检测发言人
	TP_IFrameCheck_SingleSpeaker,		//
	TP_IFrameCheck_Poll,				//轮询监测点
	TP_IFrameCheck_ChairWait,			//主席发言时，切换到其他发言人，主席的监测
};

//加密类型
enum EmTPEncryptType
{
    emTPEncryptTypeNone = 0,
	emTPEncryptTypeDES  = 1,
	emTPEncryptTypeAES  = 2,
};

//非对称屏时，接收端接收方案
enum EmTPRcvAlignType
{
	emTPRcvAlignTypeMidAlign,	//中间对齐
};
//呼叫结果
enum EmCnsCallReason	
{
	EmCnsCallReason_success,
	EmCnsCallReason_hungup,			//本地挂断
	EmCnsCallReason_Unreachable,	//对端不在线，无法呼叫
	EmCnsCallReason_resourcefull,	//对端无可用资源
	EmCnsCallReason_dstnotfind,		//目标不存在
	EmCnsCallReason_Busy,			//对端忙
	EmCnsCallReason_Local,			//本地原因
	EmCnsCallReason_NoConf,			//会议不存在
	EmCnsCallReason_Exist,			//对端已在本会议中
	EmCnsCallReason_Rejected,		//对端拒绝
	EmCnsCallReason_peerhungup,		//对端挂断
//	EmCnsCallReason_AlreadyDual,    //对端在双流
	EmCnsCallReason_Abnormal,       //本地掉线挂断
	EmCnsCallReason_PeerAbnormal,   //对端掉线挂断
	EmCnsCallReason_ConfOver,	//会议结束
	EmCnsCallReason_cncallexception,	//接入模块(cncall)掉线
	EmCnsCallReason_ConfExist,		//会议已存在
	EmCnsCallReason_unknown,  


};

enum EmTPChannelReason
{
	emTPChannelReasonBegin,
	emTPChannelDisconnectNormal,
	emTPDualOffLine,
	emTPForceStop,  //抢断双流
	emTPDualNotSend
};


//CNS类型：
enum EmTpCnsType
{
	tp_CnsType_Unkonw,
	tp_CnsType_FiveScreen_FiveSpeeker,
	tp_CnsType_FiveScreen_ThreeSpeeker,
	tp_CnsType_ThreeScreen_ThreeSpeeker,
	tp_CnsType_OneScreen_OneSpeeker,
};


//CNS注册UMS失败类型
enum EmTpCnsRegUms
{
	tp_CnsRegRet_Unknow,
	tp_CnsRegRet_Success,		//成功
	tp_CnsRegRet_MaxRegNum,		//注册满
	tp_CnsRegRet_MaxAliasNum,	//注册满
	tp_CnsRegRet_MsgError,		//注册消息错误
	tp_CnsRegRet_AliasRepeat,	//别名重复
	tp_CnsRegRet_UnReg,			//删除时，未找到删除记录
	tp_CnsRegRet_SysError,		//APP错误
	tp_CnsRegRet_NotFind,		//查找失败
	tp_CnsRegRet_Fail,          //其他失败
	tp_CnsRegRet_Unreachable,   //服务器不可达
	tp_CnsRegRet_UnRegister,    //未注册
	tp_CnsRegRet_E164Repeat,    //E164号重复
	tp_CnsRegRet_NameDup,       //别名或E164号码重复 
};



//会议模板操作结果
enum EmTpConfTemplateRet
{
	TP_ConfTemplate_UnKonw,
	TP_ConfTemplate_AddSuccess,
	TP_ConfTemplate_DelSuccess,
	TP_ConfTemplate_UpdateSuccess,
	TP_ConfTemplate_MaxNum,				//模板数量到达上限
	TP_ConfTemplate_E164Repeat,			//e164号码重复
	TP_ConfTemplate_UnFindConf,			//未找到条目
	TP_ConfTemplate_ParamInValid,		//参数错误
};


//开始会议结果
enum EmTpStartConfRet
{
	TP_StartConf_UnKonw,
	TP_StartConf_Success,
	TP_StartConf_ConfTemplateUnExist,	//会议模板不存在
	TP_StartConf_ConfFull,				//UMS会议满
	TP_StartConf_ConfExist,
	TP_StartConf_SipUnReg,				//未注册SIP服务器
	TP_StartConf_ResourceFull,          //无可用资源
};

enum EmTpApplySpeakerRet
{
	TP_ApplySpeaker_Success,		
	TP_ApplySpeaker_ConfUnExist,		//会议不存在
	TP_ApplySpeaker_EpIDError,			//会场不存在
	TP_ApplySpeaker_EpStateError,		//会场未在线或通道不未建立
};

//挂断会议结果
enum EmTpDropConfRet
{
	TP_DropConf_Success,
	TP_DropConf_ConfUnExit,	//会议模板不存在
};

//指定发言人结果
enum EmTpApplySpeakRet
{
	TP_ApplySpeak_UnKonw,
	TP_ApplySpeak_Success,
};

//会议中呼叫结点的在线状态
enum EmUmsConfNodeState
{
	ums_UmsConfNodeState_unused,		//未用
	ums_UmsConfNodeState_uncall,		//加入队列，但未开始呼叫
	ums_UmsConfNodeState_calling,		//正在呼叫中...
	ums_UmsConfNodeState_callfailed,	//呼叫失败
	ums_UmsConfNodeState_online,		//上线
	ums_UmsConfNodeState_stopcall,		//停止呼叫
};


enum EmFlowCtrlOpr	//flowctrl的操作
{
	emFlowCtrl_Speaker  = 1	,
	emFlowCtrl_Chair	= 2	,
	emFlowCtrl_Poll		= 4	,
	emFlowCtrl_TvWall	= 8	,
	emFlowCtrl_View		= 16,
};

//板子类型
enum EMBrdType
{
	em_unknow_brd,
	em_eapu_brd,
	em_mpc_brd,
	em_mpu2ecard_brd,
	em_hdu2_brd,
	em_is22_brd,
	em_cri2_brd,
};

//外设类型
enum EMEqpType
{
	em_unknow_mdl,
		em_adapter_mdl,
		em_dataswitch_mdl,
		em_netbuf_mdl,
		em_audmix_mdl,
		em_mpc_mdl,
		em_bas_mdl,
		em_vmp_mdl,
		em_hdu_mdl,
		em_regserver_mdl,
		em_recorder_mdl,

		em_max_mdl = 15,
};

//外设模式
enum EMEqpModleType
{
	em_unknow_eqp_mdl,
	em_bas_basic_eqp_mdl,
	em_bas_enhanced_eqp_mdl,
	em_vmp_basic_eqp_mdl,
	em_vmp_enhanced_eqp_mdl,
};

//系统类型
enum EMOsType
{
	em_unknow_OsType,
	em_Win32_OsType,
	em_Linux_OsType,
	em_82xx_OsType,
	em_85xx_OsType,
};

enum EMVmpStyle
{
	tp_VmpStyle_DYNAMIC = 0,	//动态分屏(仅自动合成时有效)	0
	tp_VmpStyle_ONE,			//一画面						1
	tp_VmpStyle_VTWO,			//两画面：左右分				2
	tp_VmpStyle_HTWO,			//两画面: 一大一小				3
	tp_VmpStyle_THREE,			//三画面						4
	tp_VmpStyle_FOUR,			//四画面						5
	tp_VmpStyle_SIX,			//六画面						6
	tp_VmpStyle_EIGHT,			//八画面						7
	tp_VmpStyle_NINE,			//九画面						8
	tp_VmpStyle_TEN,			//十画面						9
	tp_VmpStyle_THIRTEEN,		//十三画面						10
	tp_VmpStyle_SIXTEEN,		//十六画面						11
	tp_VmpStyle_SPECFOUR,		//特殊四画面					12
	tp_VmpStyle_SEVEN,			//七画面						13
	tp_VmpStyle_TWENTY,			//二十画面						14
	tp_VmpStyle_TEN_H,			//水平分割的十画面(上2下8)		15
	tp_VmpStyle_SIX_L2UP_S4DOWN,	//特殊六画面(上2下4)		16
	tp_VmpStyle_FOURTEEN,			//十四画面					17
	tp_VmpStyle_TEN_M,				//十画面(上4中2下4)			18
	tp_VmpStyle_THIRTEEN_M,			//十三画面(一大在中间)		19
	tp_VmpStyle_FIFTEEN,			//十五画面					20
	tp_VmpStyle_SIX_DIVIDE,			//六画面(等分)				21
	tp_VmpStyle_leftBig,			//三画面，2个小的在底部靠右	22
	tp_VmpStyle_MidBig,				//三画面，2个小的在底部两边	23
	tp_VmpStyle_RightBig,			//三画面，2个小的在底部靠左	24
	tp_VmpStyle_3VERTICAL,			//三画面，垂直等大			25
	tp_VmpStyle_FOUR_3BOTTOMMIDDLE,	//四画面，3个在底部中央		26
	tp_VmpStyle_TWENTYFIVE,			//二十五画面				27
};


//==============以下为CNS使用type==============//


//视频协议类型
enum EmTpVideoFormat
{
    emTPVH261     = 0,
		emTPVH262     = 1,//MPEG2
		emTPVH263     = 2,
		emTPVH263plus = 3,
		emTPVH264     = 4,
		emTPVMPEG4    = 5,
		
		emTPVEnd		
};
//编码方式
enum EmTpEncodeMode
{
    emTPQualityFirst  = 0, 
		emTPSpeedFirst    = 1,
		
};

//H.264格式画质级别
enum EmTpVideoQualityLevel
{
	emTPH264BP = 0,  //BP级别
	emTPH264HP = 1,  //HP级别
};

//分辨率类型
enum EmTpVideoResolution
{
    emTPVResolutionAuto     = 0,   //自动
		emTPVSQCIF              = 1,   //SQCIF88x72
		emTPVQCIF               = 2,   //QCIF176x144
		emTPVCIF                = 3,   //CIF352x288
		emTPV2CIF               = 4,   //2CIF352x576
		emTPV4CIF               = 5,   //4CIF704x576
		emTPV16CIF              = 6,   //16CIF1408x1152
		
		emTPVHD480i720x480      = 7,   //480i720x480
		emTPVHD480p720x480      = 8,   //480p720x480
		emTPVHD576i720x576      = 9,   //576i720x576
		emTPVHD576p720x576      = 10,  //576p720x576
		
		emTPVHD720p1280x720     = 11,  //720p1280x720
		emTPVHD1080i1920x1080   = 12,  //1080i1920x1080
		emTPVHD1080p1920x1080   = 13,  //1080p1920x1080
		
		
		emTPVGA352x240          = 14,  //352x240
		emTPVGA704x480          = 15,  //704x480
		emTPVGA640x480          = 16,  //VGA640x480
		emTPVGA800x600          = 17,  //SVGA800x600
		emTPVGA1024x768         = 18,  //XGA1024x768
		emTPVGA1280x768         = 19,  //WXGA1280x768
		emTPVGA1280x800         = 20,  //WXGA1280x800
		emTPVGA1366x768         = 21,  //WXGA1366x768
		emTPVGA1280x854         = 22,  //WSXGA1280x854
		emTPVGA1440x900         = 23,  //WSXGA1440x900
		emTPVGA1280x1024        = 24,  //SXGA1280x1024
		emTPVGA1680x1050        = 25,  //SXGA+1680x1050
		emTPVGA1600x1200        = 26,  //UXGA1600x1200
		emTPVGA1920x1200        = 27,  //WUXGA1920x1200
		
		emTPVSQCIF112x96        = 28,
		emTPVSQCIF96x80         = 29,
		emTPV320x192            = 30,
		emTPV432x240            = 31,
		emTPV480x272            = 32,
		emTPV640x368            = 33,
		emTPV864x480            = 34,
		emTPV960x544            = 35,
		emTPV1440x816           = 36,
		
		emTPVResEnd = 50,
};

// 媒体类型
enum EmTpMediaType
{
	emTPMediaVideo = 1, //视频
	emTPMediaAudio = 2, //音频
	emTPMediaAV    = 3 //音频和视频
};

//PC windows 采集格式
enum EmTpPCCapFormat
{
	emTPCapPCFrameBMP  = 0,//RGB24位图;
		emTPCapPCFrameUYUY = 1,//yuv4:2:2格式
		emTPCapPCFrameI420 = 2,//yuv4:2:0格式
};

//编解码器各个部件
enum EmTpCodecComponent
{
	emTPPriomVideoEncoder  =0,
		emTPPriomVideoDecoder  ,
		
		emTPSecondVideoEncoder ,
		emTPSecondVideoDecoder ,
		
		emTPAudioEncoder ,
		emTPAudioDecoder ,

		emTPSecondAudioEncoder ,
		emTPSecondAudioDecoder ,

		emTPPriomLeftVideoDecoder,
		emTPPriomRightVideoDecoder,

		emTPCodecComponentEnd,

};

//音频协议类型
enum EmTpAudioFormat
{
    emTPAG711a  = 0,
		emTPAG711u  = 1,
		emTPAG722   = 2,
		emTPAG7231  = 3,
		emTPAG728   = 4,
		emTPAG729   = 5,
		emTPAMP3    = 6,
		emTPAG721   = 7,
		emTPAG7221  = 8,
		emTPAG719   = 9,
		emTPAMpegAACLC =10,
		emTPAMpegAACLD = 11,
		
		emTPAEnd	 
};
//丢包恢复类型
enum EmTpLostPackageRestore
{
    emTPLPQualityFirst  = 0, 
		emTPLPSpeedSlow     = 1,
		emTPLPSpeedNormal   = 2,
		emTPLPSpeedFast     = 3,
};
enum EmTpCallMode
{
	emTpJoin,
		emTpCreate,
		emTpInvite
};
enum EmTpConnectionType
{
	emTPConnectionBegin = 0,
	emTPTCPConnection,
	emTPUDPConnection,
};
enum EmTpConfProtocol
{
	emTpInvalidConfProtocel = 0,
	emTpH323, 
	emTpH320,
	emTpSIP,
	emTpSat
};


enum EmTPAddrType
{
	emTpUnknown =0,
	emTpIPAddr, 
	emTpDomain,
	emTpAlias,
	emTpE164Num,
	emTpIP6Addr,
};
enum EmTPEndpointType
{
	emTPEndpointTypeUnknown  = 0,
	emTPEndpointTypeCNS	     = 0x01,
	emTPEndpointTypeUMS		 = 0x02,
	emTPEndpointTypeRegister,
	emTPEndpointH323MT,
	emTPEndpointH323MCU,
	emTPEndpointH323SingleMCU,
	emTPEndpointH323G400,
};
enum EmTPSipLevel
{
	emTPSipCounty,
	emTPSipCity,
	emTPSipProvince,
	emTPSipUnKnown = 255,
};

//呼叫状态
enum EmCALLSTATE
{
	em_CALL_IDLE    = 0,  
	em_CALL_CALLING,
	em_CALL_CONNECTED
};

//会议类型，CNS通知CMC
enum EmCallType
{
	emCallType_Invalid = 0,
	emCallType_P2P,
	emCallType_Conf
};

enum EmTPVideoType
{
	emTpPriomVideo = 0 ,//主视频
	emTpMiniVideo = 1 //小码流
};


//终端视频端口
enum EmTPVideoPort
{
	//hd2.0视频源定义
	emTpVGA   =0 , //VGA 
	emTpSVid    , //S 端子
	emTpPC      , //PC
	emTpC1Vid   ,  //C1端子   DVI 1
	emTpC2Vid   ,  //C2端子   DVI 2
	emTpC3Vid   ,  //C3端子   DVI 3
	emTpC4Vid   ,  //C4端子   c
	emTpC5Vid   ,  //C5端子   sdi 1
	emTpC6Vid   ,  //C6端子   sdi 2
		
	emTpExternalVid = 10,//外置矩阵映射基始值
	emTpVideoMaxCount = 74, //最多支持视频源个数
	emTpVidInvalid = 255 
};

enum EmTPCNSInfoRst
{
	emTPCNSInfoSuccess = 1,			//成功
	emTPCNSRepeatE164,				//E164重名
	emTPCNSRepeatAliasName,			//会场名重复

};


enum EmTPRegResult
{
	emTPRegResultBegin = 0,
	emTPRegResultReg,
	emTPRegResultUnReg
};

enum EmCnMtRegResult
{
	emCnMtSuccess = 1,
	emCnMtPosError,
	emCnMtTimeOut
};

//Add摄像机相关type
//终端型号
enum EmCnModel
{
	emUnknownCnModel=0,
	em7920,	
	T300,
	Moon90	
};

//聚焦模式
enum EmFocusMode
{
	emFocusAuto,
	emFocusManuel
};

//聚焦
enum EmFocus
{
	emFar ,
    emNear
};

//视野
enum EmZoom
{
	emTele,
    emWide
};

//操作
enum EmCnAction
{
    emCnStart,
	emCnStop,
};

//摄像机 OSD 显示
enum EmOSDShow
{
	emOSDOff = 0x00,
	emOSDOn ,
};

//白平衡模式
enum EmWBMode
{
	emWBAuto = 0x00,
	emWBManual,
	emOnePush
};

//曝光模式
enum EmExpMode
{
	emExpAuto = 0x00,
	emExpManuel
};

//摄像机 曝光--增益
enum EmGain
{
	em0dB = 0x00,
	em3dB = 0x01,
	em6dB = 0x02,
	em9dB  ,
	em12dB ,
	em15dB ,
	em18dB ,
	em21dB ,
	em24dB ,
	em27dB ,
	em30dB ,
	em33dB ,
	em36dB ,
	em39dB ,
	em42dB = 0x0e,
};

//摄像机  曝光--快门
enum EmShutSpd
{
	emShutSpd0  = 0x00,  // 1/60
	emShutSpd1  = 0x01,  // 1/120
	emShutSpd2  = 0x02,  // 1/250
	emShutSpd3 ,         // 1/500
	emShutSpd4 ,         // 1/1000
	emShutSpd5 ,         // 1/2000
	emShutSpd6 ,         // 1/4000
	emShutSpd7 ,         // 1/10000
};

//摄像机 曝光--背光
enum EmBackLightType
{
	emBLOff    = 0x00,
	emBLmulti,
	emBLcenter,
	emBLfacedetect,
		
	emBLAuto,
};

//摄像机 场景模式
enum EmPicSceMode
{
	emLamp   = 0x00,  
	emSun    = 0x01,  
	emManuel = 0x02,
};

//摄像机 手动模式 GAMMA
enum EmGamma
{
	emGammaOff  = 0x00,
	emGammaOn   = 0x01,
	emSmart1,
	emSmart2,
};

//降噪 ——噪点过滤 范围
enum EmStmClean
{
    emNRoff  = 0x00,
	emNRlow  ,
	emNRmid  ,
	emNRhigh
};

enum Em3DNR
{
	em3DNROff  = 0x00,
	em3DNROn
};

enum EmCamPowerMode
{
	emCamPowerOn,   //上电
	emCamPowerOff,  //待机
	emCamPowerDowm, //断电
};

enum EmCenSchMode
{
	emSchSleep,   //待机
	emSchWakeup,  //唤醒
};

//end


//中控模块
//电视机电源模式
enum EmTvPowerMode
{
	emTVPowerOFF,
	emTVPowerON,
	emTVPowerDown
};

//电视机断电前电源模式
enum EmTvSrcPowerMode
{
	emTVSrcPowerOFF,
		emTVSrcPowerON,
};

//电视机视听模式
enum EmTVAudVisMode
{
	emTVAVStandardMode = 0,   //标准
		emTVAVMovieMode,          //电影
		emTVAVUserMode,           //用户
		emTVAVComputerMode        //电脑
};


//电视机显示模式
enum EmTVDisplayMode
{
	emTVDisFullScrMode  = 0,  //全屏
		emTVDisPanoramaMode,      //全景
		emTVDisPointMode,         //逐点
		emTVDisStandardMode       //标准
};

//电视机输入选择 
enum EmTVInputSelect
{
	emTVHDMI1  = 0,
		emTVHDMI2,
		emTVHDMI3,
		emTVHDMI4,
		emTVYpbPr,
		emTVCVBS1,
		emTVCVBS2,
		emTVComputer
};

//文档摄像头白平衡模式 
enum EmDCamWBMode
{
	emDcamWBAuto = 0x00,
	emDCamWBManual,
	emDCamOnePush,
	emDCamWBInvalid
};

//文档摄像头自动聚焦模式
enum EmDCamAFMode
{
	emDcamAFOff = 0x00,
	emDCamAFOn,
	emDCamAFToggle,
	emDCamAFInvalid
};

//文档摄像头待机唤醒
enum EmDCamPower
{
	emDCamPowerOff = 0x00,
	emDCamPowerOn,
	emDCamPowerToggle,
	emDCamPowerDown,
	emDCamPowerInvalid
};

//文档摄像头视野调节
enum EmDCamZoom
{
    emDCamZoomWide = 0x00,
	emDCamZoomTele,
	emDCamZoomInvalid
};

//保存文档摄像头预置位编号
enum EmDCamPresetNum
{
	emDCamPresetOne = 0x00,
	emDCamPresetTwo,
	emDCamPresetThree,
	emDCamPresetInvalid
};

//调度文档摄像头预置位编号
enum EmDCamRecallNum
{
	emDCamRecallOne = 0x00,
	emDCamRecallTwo,
	emDCamRecallThree,
	emDCamRecallInvalid
};

//会议室系统电源开关
enum EmSchPower
{
	emSchPowerOff = 0x00,
	emSchPowerOn,
	emSchPowerToggle,
	emSchPowerInvalid
};

//会议室灯光电源开关
enum EmSchLight
{
	emSchLightOff = 0x00,
	emSchLightOn,
	emSchLightInvalid
};

//会议室顶上灯光电源开关
enum EmSchMidLight
{
	emSchMidLightOff = 0x00,
	emSchMidLightOn,
	emSchMidLightInvalid
};

//会议室机柜灯光电源开关
enum EmSchScrLight
{
	emSchScrLightOff = 0x00,
	emSchScrLightOn,
	emSchScrLightInvalid
};



//会议室人体感应器锁定与解锁
enum EmSchArgus
{
	emSchArgusUnlock = 0x00,
	emSchArgusLock,
	emSchArgusInvalid
};

//中控空调模式 add by zhangapei
enum EmCentreACPower
{
	emCenACPowerOff,
	emCenACPowerOn,
};

//空调新风风量
enum EmCentreACAirVol
{
	emCenACVolAuto,  //自动
	emCenACVol1,    
	emCenACVol2,     
	emCenACVol3,    
	emCenACVol4,  
	emCenACVol5,     
};

//空调模式
enum EmCentreACMode
{
	emCenACBlowIn,  //送风
	emCenACheat,    //制热
	emCenAcref,     //制冷
	emCenACAuto,    //自动
	emCenACChaAir,  //换气
	emCenACdeh,     //除湿
};


//窗帘动作类型
enum EmCurAction
{
	emCurUp,
	emCurDown,
	emCurStop,
};

//窗帘控制通路模式
enum EmCurChannelMode
{
	emCurChanFirst = 1,
	emCurChanSecond,
	emCurChanFirASec,
	emCurChanThird,
	emCurChanFirAThi,
	emCurChanSecAThi,
};

enum EmSchGatewayType
{
	emGatewayOld,
	emGatewayNew,
};

//end add

//中控 end

//==============以上为CNS使用type==============//

enum EmTpMixStatus
{
	emAudMixIdle,
	emAudOpenChan_Fail,		//打开语音通道失败
	emAudOpenChan_Success    //打开语音通道成功
};

enum EmTPDualReason
{
	emTpDualAccept,
		emTpDualBusy,
		emTpDualPreemptive,
		emTpDualPeerReject,
		emTpDualPeerStop,
		emTpDualNoVideo,
		emTpDualLocalStop,
		emTpDualSndFail,       //发送双流失败
		emTpDualInit           //双流初始化中
};

enum  EmTPPayloadType 
{
	emTpPayloadTypeBegin = 0,
		//音频格式
		emTpAudioTypeBegin,
		emTpG711a,
		emTpG711u,
		emTpG722,
		emTpG7231,
		emTpG728,
		emTpG729,
		emTpMp3,  
		emTpG723,
		emTpG7221,
		emTpMpegaaclc,
		emTpMpegaacld,
		emTpG719,
		emTpAudioTypeEnd = 49,
		
		//视频格式
		emTpVideoTypeBegin = 50,	
		emTpH261,
		emTpH263,
		emTpH263plus,
		emTpH264,
		emTpH262,
		emTpMpeg4,
		emTpVideoTypeEnd = 99,
        
		emTpDataTypeBegin = 100,	
		emTpT120,
		emTpH224,
		emTpDataTypeEnd = 149,
		
		emTpPayloadTypeEnd = 255
};

enum EmTPPosStatus
{
	emPosInAcitve = 0,
	emPosAcitve
};

enum EmTPPollResult
{
	emPollSucceed = 0,
	emPollFailUnKown = 1,
	emPollInvalidEp = 2,	//无有效轮训会场
};

enum EmTPViewResult
{
	emViewSucceed = 0,
	emViewFailUnKown,
	emViewFailStatusError,
	emViewFailOffline,			//对端不在线
	emViewFailNotChair,			//请求这不是主会场
	emViewFailNoResource,		//没有资源
	emViewFailDstNoVid,			//目标无视频
	emViewRequesting,			//请求中，请等待
};


enum EmTPViewLocalResult
{
	emViewLocalSucceed = 0,
	emViewLocalFailUnKown,
	emViewLocalFailStatusError,       //状态错误，取消时表示当前屏不在VIEW LOCAL，选看时表示已在看本地状态
	emViewLocalFailOffline,
	emViewLocalFailIllegalPos
};

enum EmTPDisOprType
{
	emDisOprType_Idle,
	emDisOprType_StartAll,
	emDisOprType_AddChnl,
	emDisOprType_ChangeSeat,
	emDisOprType_RemoveChnl,
	emDisOprType_DisConnectChnl
};

enum EMPosPic
{
	emPic_Invalid = 0,
		emPic_Local,				//本地
		emPic_Static,				//静态图片
		emPic_Speaker,				//发言人
		emPic_Dual,					//双流
		emPic_Poll,					//轮询
		emPic_SelView,              //选看远端 
		emPic_SelDual,              //选看双流
		emPic_SelLocal,             //选看本地
		emPic_Discuss,             //讨论
		emPic_SelTVS               //选看电视墙
};

enum EMDSCREATETYPE
{
	emDS_CreateType_Invalid = 0,
	emDS_CreateType_SndBoundary,
	emDS_CreateType_RcvBoundary,
	emDS_CreateType_SndAndRcvBoundary,
	emDS_CreateType_NotBoundary,
};

enum EmTPAddDualRcvResult
{
	emAddDualRcvSucceed = 0,
	emAddDualRcvFailNoDual,       //没有收双流
	emAddDualRcvFailIllegalPos,   //非法位置
	emAddDualRcvFailNoPos,        //没有空闲位置了
	emAddDualRcvFailStatusError,  //当前已经是双流状态了
	emAddDualRcvFailUnKown,
};

enum EmTPDeleteDualRcvResult
{
	emDeleteDualRcvSucceed = 0,
	emDeleteDualRcvFailNoDual,       //没有收双流
	emDeleteDualRcvFailIllegalPos,   //非法位置
	emDeleteDualRcvFailUnKown,
};

enum EmTPMtModel
{
	emTPUnknownMtModel=0,
		emTPPCMT  =1    ,//桌面终端
		emTP8010      ,
		emTP8010A     ,
		emTP8010Aplus ,//8010A+
		emTP8010C     ,
		emTP8010C1    ,//8010C1
		emTPIMT       ,
		emTP8220A     ,
		emTP8220B     ,
		emTP8220C     ,
		emTP8620A     ,
		emTPTS6610E   ,
		emTPTS6210    ,
		emTP8010A_2   ,
		emTP8010A_4   ,
		emTP8010A_8   ,
		emTP7210      ,
		emTP7610      ,
		emTPTS5610    ,
		emTPTS6610    ,
		emTP7810      ,
		emTP7910      ,
		emTP7620_A    ,
		emTP7620_B    ,
		emTP7820_A	,
		emTP7820_B	,
		emTP7920_A	,
		emTP7920_B	
		
};

enum EmDsType
{
	em_DsType_Invalid = 0,

		
		//协议 外部端口
		em_Ds_Remote_ASnd_0 ,
		em_Ds_Remote_ASnd_1,
		em_Ds_Remote_ASnd_2,
		
		em_Ds_Remote_ARcv_0,
		em_Ds_Remote_ARcv_1,
		em_Ds_Remote_ARcv_2,
		
		em_Ds_Remote_VSnd_0,
		em_Ds_Remote_VSnd_1,
		em_Ds_Remote_VSnd_2,
		
		em_Ds_Remote_VRcv_0,
		em_Ds_Remote_VRcv_1,
		em_Ds_Remote_VRcv_2,
		
		em_Ds_Remote_VSnd_0_Mini_0,
		em_Ds_Remote_VSnd_1_Mini_0,
		em_Ds_Remote_VSnd_2_Mini_0,
		
		em_Ds_Remote_VRcv_0_Mini_0,
		em_Ds_Remote_VRcv_0_Mini_1,
		em_Ds_Remote_VRcv_1_Mini_0,
		em_Ds_Remote_VRcv_1_Mini_1,
		em_Ds_Remote_VRcv_2_Mini_0,
		em_Ds_Remote_VRcv_2_Mini_1,
		
		
		em_Ds_Remote_Mix_Snd,
		em_Ds_Remote_Mix_Rcv,

		em_Ds_RemoteDual_ASnd,
		em_Ds_RemoteDual_VSnd,
		
		em_Ds_RemoteDual_ARcv,
		em_Ds_RemoteDual_VRcv,


		//用于与协议栈交互
		em_Ds_VirRemote_ASnd_0 ,
		em_Ds_VirRemote_ASnd_1,
		em_Ds_VirRemote_ASnd_2,
		
		em_Ds_VirRemote_ARcv_0,
		em_Ds_VirRemote_ARcv_1,
		em_Ds_VirRemote_ARcv_2,
		
		em_Ds_VirRemote_VSnd_0,
		em_Ds_VirRemote_VSnd_1,
		em_Ds_VirRemote_VSnd_2,
		
		em_Ds_VirRemote_VRcv_0,
		em_Ds_VirRemote_VRcv_1,
		em_Ds_VirRemote_VRcv_2,

		em_Ds_VirRemote_VSnd_0_Mini_0,
		em_Ds_VirRemote_VSnd_1_Mini_0,
		em_Ds_VirRemote_VSnd_2_Mini_0,
		
		em_Ds_VirRemote_VRcv_0_Mini_0,
		em_Ds_VirRemote_VRcv_0_Mini_1,
		em_Ds_VirRemote_VRcv_1_Mini_0,
		em_Ds_VirRemote_VRcv_1_Mini_1,
		em_Ds_VirRemote_VRcv_2_Mini_0,
		em_Ds_VirRemote_VRcv_2_Mini_1,

		
		em_Ds_VirRemote_Mix_Snd,
		em_Ds_VirRemote_Mix_Rcv,
		
		em_Ds_VirRemote_End = 100,

		em_Ds_MT_ASnd_0,
		em_Ds_MT_ASnd_1,
		em_Ds_MT_ASnd_2,
		em_Ds_MT_ASnd_3,
		
		em_Ds_MT_ARcv_0,
		em_Ds_MT_ARcv_1,
		em_Ds_MT_ARcv_2,
		em_Ds_MT_ARcv_3,
		
		em_Ds_MT_VSnd_0,
		em_Ds_MT_VSnd_1,
		em_Ds_MT_VSnd_2,
		em_Ds_MT_VSnd_3,
		
		em_Ds_MT_VRcv_0,
		em_Ds_MT_VRcv_1,
		em_Ds_MT_VRcv_2,
		em_Ds_MT_VRcv_3,
		
		em_Ds_MT_VSnd_0_Mini_0,
		em_Ds_MT_VSnd_1_Mini_0,
		em_Ds_MT_VSnd_2_Mini_0,
		
		em_Ds_MT_VRcv_0_Mini_0,
		em_Ds_MT_VRcv_0_Mini_1,
		em_Ds_MT_VRcv_1_Mini_0,
		em_Ds_MT_VRcv_1_Mini_1,
		em_Ds_MT_VRcv_2_Mini_0,
		em_Ds_MT_VRcv_2_Mini_1,
		
		em_Ds_Mt_Mix_ASnd,//mt混音端口

		//用于和终端交互  目前无使用
		em_Ds_VirMt_ASnd_0,
		em_Ds_VirMt_ASnd_1,
		em_Ds_VirMt_ASnd_2,
		
		em_Ds_VirMt_ARcv_0,
		em_Ds_VirMt_ARcv_1,
		em_Ds_VirMt_ARcv_2,
		
		em_Ds_VirMt_VSnd_0,
		em_Ds_VirMt_VSnd_1,
		em_Ds_VirMt_VSnd_2,
		
		em_Ds_VirMt_VRcv_0,
		em_Ds_VirMt_VRcv_1,
		em_Ds_VirMt_VRcv_2,

		em_Ds_VirMt_VSnd_0_Mini_0,
		em_Ds_VirMt_VSnd_0_Mini_1,
		em_Ds_VirMt_VSnd_1_Mini_0,
		em_Ds_VirMt_VSnd_1_Mini_1,
		em_Ds_VirMt_VSnd_2_Mini_0,
		em_Ds_VirMt_VSnd_2_Mini_1,
		
		em_Ds_VirMt_VRcv_0_Mini_0,
		em_Ds_VirMt_VRcv_0_Mini_1,
		em_Ds_VirMt_VRcv_1_Mini_0,
		em_Ds_VirMt_VRcv_1_Mini_1,
		em_Ds_VirMt_VRcv_2_Mini_0,
		em_Ds_VirMt_VRcv_2_Mini_1,

		em_Ds_VirMt_Mix_ASnd,
	

		em_Ds_Mt_End = 200,


		em_Ds_Innerspeaker_ASnd,
		em_Ds_Innerspeaker_VSnd,
		
		em_Ds_Innerspeaker_End = 210 ,
		
		em_Ds_VirDual_ASnd,
		em_Ds_VirDual_VSnd,
		
		em_Ds_VirDual_ARcv,//双流仅为单向，暂不使用
		em_Ds_VirDual_VRcv,//双流仅为单向，暂不使用
		
		//适配地址
		em_Ds_VirDual_Adapter_VSnd,
		em_Ds_MtDual_Adapter,		

		em_Ds_Dual_End = 250,

		em_Ds_Addr_Type_End = 300,


		//以下不需要分配端口
		em_DsOtherType_Begin,
		
		em_Ds_VirMtToInnerspeaker_ASnd_0,
		em_Ds_VirMtToInnerspeaker_ASnd_1,
		em_Ds_VirMtToInnerspeaker_ASnd_2,
		
		em_Ds_VirMtToInnerspeaker_VSnd_0,
		em_Ds_VirMtToInnerspeaker_VSnd_1,
		em_Ds_VirMtToInnerspeaker_VSnd_2,
		
		em_Ds_DualRcvToVirMt_Rcv_0,
		em_Ds_DualRcvToVirMt_Rcv_1,
		em_Ds_DualRcvToVirMt_Rcv_2,

		em_Ds_VirRemoteToVirMt_ASnd_0,
		em_Ds_VirRemoteToVirMt_ASnd_1,
		em_Ds_VirRemoteToVirMt_ASnd_2,

		em_Ds_VirRemoteToVirMt_VSnd_0,
		em_Ds_VirRemoteToVirMt_VSnd_1,
		em_Ds_VirRemoteToVirMt_VSnd_2,

		em_Ds_VirRemoteToVirMt_ARcv_0,
		em_Ds_VirRemoteToVirMt_ARcv_1,
		em_Ds_VirRemoteToVirMt_ARcv_2,
		
		em_Ds_VirRemoteToVirMt_VRcv_0,
		em_Ds_VirRemoteToVirMt_VRcv_1,
		em_Ds_VirRemoteToVirMt_VRcv_2,

		em_Ds_VirDualNB_VRcv,
		em_Ds_VirDualNB_VSnd,

		em_Ds_VirDualNB_ARcv,
		em_Ds_VirDualNB_ASnd,

		em_Ds_VirRemoteToVirMt_VRcv_0_Mini_0,
		em_Ds_VirRemoteToVirMt_VRcv_0_Mini_1,
		em_Ds_VirRemoteToVirMt_VRcv_1_Mini_0,
		em_Ds_VirRemoteToVirMt_VRcv_1_Mini_1,
		em_Ds_VirRemoteToVirMt_VRcv_2_Mini_0,
		em_Ds_VirRemoteToVirMt_VRcv_2_Mini_1,

		em_Ds_VirRemoteToVirMt_Mix_ASnd,
		
		em_Ds_VirRemoteToPad_VSnd,
		em_Ds_VirRemoteToPad_ASnd,

		em_Ds_VirDual_ARcv_Pad_Begin = em_DsOtherType_Begin+1000,
		em_Ds_VirDual_ARcv_Pad_End = em_Ds_VirDual_ARcv_Pad_Begin+20,
		em_Ds_VirDual_VRcv_Pad_Begin,
		em_Ds_VirDual_VRcv_Pad_End = em_Ds_VirDual_VRcv_Pad_Begin+20,

		em_Ds_VirDual_VSnd_Pad,
		

		em_Ds_Debug = 1010,
		
};

enum EmCnAudioMixID
{
	emCnAMix_INVALID,
	emCnAMix_Speaker,    //3对1屏发言人混音器
	emCnAMix_Dual,       //双流混音器
};

enum EmGetRegInfoType
{
	emGetRegInfoType_CNS = 0,
	emGetRegInfoType_UMS,
	emGetRegInfoType_ALL,
	emGetRegInfoType_MT,
	emGetRefInfoType_MCU,
};

enum EmGetRegInfoOpr
{
	emGetRegInfoOpr_Update = 0,//刷新
	emGetRegInfoOpr_Add,//增加
};

enum EmTPChanType
{
	emTPChanNone,
	emTPChanRecv,
	emTPChanSend,
	emTPChanSendRecv,
	emTPChanTypeEnd = 10,
};

enum EmTPAACSampleFreq                    //sampling frequency
{
	emTPFs96000 = 0,
        emTPFs88200 = 1,
        emTPFs64000 = 2,
        emTPFs48000 = 3,
        emTPFs44100 = 4,
        emTPFs32000 = 5,
        emTPFs24000 = 6,
        emTPFs22050 = 7,
        emTPFs16000 = 8,
        emTPFs12000 = 9,
        emTPFs11025 = 10,
        emTPFs8000  = 11
};

enum EmTPG7221Rate
{
	emTPG7221Rate24   =  0x01,
	emTPG7221Rate32   =  0x02,
	emTPG7221Rate48   =  0x04
};


enum EmTPAACChnlCfg                       //channel config
{
	emTPChnlCust   = 0,
        emTPChnl1      = 1,                   //单声道
        emTPChnl2      = 2,                   //双声道
        emTPChnl3      = 3,
        emTPChnl4      = 4,
        emTPChnl5      = 5,
        emTPChnl5dot1  = 6,                   //5.1声道
        emTPChnl7dot1  = 7                    //7.1声道
};

enum EmTPTpApplySpeakerRet
{
	emTP_ApplySpeaker_Success,  
	emTP_ApplySpeaker_ConfUnExist,   //会议不存在
	emTP_ApplySpeaker_EpIDError,     //会场不存在
	emTP_ApplySpeaker_EpStateError,  //会场未在线或通道不未建立
};


enum EmTPChanSubType
{
	EmTPChanSubType_Normal, 
	EmTPChanSubType_Mini,
	EmTPChanSubType_Dual,   
	EmTPChanSubType_AMix,       
};

enum EmMakeCallType
{
	em_sip_call_type,
	em_323_call_type,
};

enum EmTpRegType
{
	em_sip_reg,
	em_323_reg,
};

enum EmDisListOprType
{
	em_DisListOpr_Add,
	em_DisListOpr_Del,
};

enum EmDisListOprReslt
{
	em_DisListOpr_Sucess,
	em_DisListOpr_Fail,
	em_DisListOpr_Reject,
};

//Add by tanxiaodong 2012-07-17.
//VGA类型
enum EmVgaType
{
	//CNC双流演示源的选择类型
	emVgaTypeDocCamera = 0,//文档摄像机
	emVgaType001,
	emVgaType002,
	emVgaType003,
	emVgaType004,
	emVgaType005,
	emVgaType006,
	emVgaTypeInValid//无效值
};

//双流演示源输入接口类型
enum EmDualInputType
{
   emDualInputDocCamera = 0,//文档摄像机
   emDualInput001,//演示源1
   emDualInput002,//演示源2
   emDualInput003,//演示源3
   emDualInput004,//演示源4
   emDualInput005,//演示源5
   emDualInput006,//演示源6
   emDualInputInvalid//无效值

};

//双流演示源输出接口类型
enum EmDualOutputType
{
	emDualOutputInvalid = 0,
	emDualOutput001,//演示屏1
    emDualOutput002 //演示屏2
};
//End to add.

//Added by meifang
enum EmVgaSwitchResult
{
	em_VgaSwitchInvalid,      //无效值
	em_VgaSwitchFail = 1,     //切换失败
	em_VgaSwitchSucc,         //切换成功	
	em_CurVgaNoSignal,        //切换成功，但当前演示源无输入
	em_TpNoDual,              //没有接双流终端
	em_VgaBusying,            //演示源正忙，拒绝切换
};

//演示源切换原因
enum EmVgaSwitchReason
{
	em_SwitchVgaInvalid,
		em_SwitchDemoVga = 1, //会议外切换默认演示源
		em_SwitchCurVga,      //会议中切换当前演示源
		em_ResetVga,          //结会时重置为默认演示源
};

//会场状态
enum EmCnState
{
	emCnsRunning, //正常运行
	emCnsSleep,   //待机
	emCnsPoweroff, //关机
};
//End to add

enum EmTPCapSign    //能力标识， 大，左，右
{
	emTPCapBig,  
	emTPCapLeft,
	emTPCapRight,
};

//Add by tanxiaodong 2012-11-22.
enum EmSwitchState
{
	emStateON = 1,   //开机
	emStateOFF,      //关机
	emStateStandby,  //待机
};
//End to add.

//单板操作结果
enum EmTpBoardRet
{
	emTP_Board_UnKonw,                //单板未知
	emTP_Board_AddSuccess,            //单板添加成功
	emTP_Board_DelSuccess,            //单板删除成功
	emTP_Board_ModifySuccess,         //单板修改成功
	emTP_Board_MaxNum,				  //单板数量达到最大值
	emTP_Board_Mode_AddSuccess,       //单板模式添加成功
	emTP_Board_Mode_DelSuccess,       //单板模式删除成功
	emTP_Board_Mode_ModifySuccess,    //单板模式修改成功
	emTP_Board_UnFind,			      //未找到条目
	emTP_Board_UnKnowLoc,             //单板层号槽号未知
	emTP_Board_Repeat,                //单板重复
	emTP_BrdType_NotMatch_EqpType,    //单板类型与外设类型不匹配
	emTP_BrdMode_Repeat,              //要修改的模式与原模式相同
	emTP_BrdMode_MaxNum,              //单板模式达到最大值
	emTP_BrdMode_NoConfig,			  //单板未配置模式
	emTp_BrdMode_Resource_Full,		  //模式分配eqpid时资源占满
	emTp_BrdMode_AudMix_MaxNum,       //达到最大混音器混音路数
};

//hdu 输出端口类型
enum EmHduOutPort
{
	em_hdu_outport_YPbPr = 0,
	em_hdu_outport_VGA   = 1,
	em_hdu_outport_DVI   = 2,
	em_hdu_outport_HDMI  = 3,

	em_hdu_outport_unknow,
};

//HDU 缩放比列
enum EmHduZoomRate
{
	em_hdu_zoomrate_4_3  = 0,
	em_hdu_zoomrate_16_9 = 1,

	em_hdu_zoomrate_unknow,
};

//HDU 输出制式
enum EmHduOutMode
{
	em_hdu_outmode_YPbPr_1080P_24fps = 0,
	em_hdu_outmode_YPbPr_1080P_25fps = 1,
	em_hdu_outmode_YPbPr_1080P_30fps = 2,
	em_hdu_outmode_YPbPr_1080P_50fps = 3,
	em_hdu_outmode_YPbPr_1080P_60fps = 4,
	em_hdu_outmode_YPbPr_1080i_50HZ  = 5,    //(默认)
	em_hdu_outmode_YPbPr_1080i_60HZ  = 6,
	em_hdu_outmode_YPbPr_720P_60fps  = 7,
	em_hdu_outmode_YPbPr_576i_50HZ   = 8,
	em_hdu_outmode_YPbPr_480i_60HZ   = 9,
		
	
	em_hdu_outmode_VGA_SXGA_60HZ     = 10,
	em_hdu_outmode_VGA_XGA_60HZ      = 11,     //(默认)
	em_hdu_outmode_VGA_XGA_75HZ      = 12,
	em_hdu_outmode_VGA_SVGA_60HZ     = 13,
	em_hdu_outmode_VGA_SVGA_75HZ     = 14,
	em_hdu_outmode_VGA_VGA_60HZ      = 15,
	em_hdu_outmode_VGA_VGA_75HZ      = 16,
	em_hdu_outmode_VGA_SXGA_75HZ     = 17,
	em_hdu_outmode_YPbPr_720P_50fps  = 18,  //zjl[20091216]新加hdu输出制式
	em_hdu_outmode_VGA_WXGA_1280_768_60HZ = 19,
	em_hdu_outmode_VGA_WXGA_1280_800_60HZ = 20,
	em_hdu_outmode_VGA_WSXGA_60HZ    = 21,
	em_hdu_outmode_VGA_SXGAPlus_60HZ = 22,
	em_hdu_outmode_VGA_UXGA_60HZ     = 23,
	em_hdu_outmode_YPbPr_1080P_29970HZ = 24,
	em_hdu_outmode_YPbPr_1080P_59940HZ = 25,
	em_hdu_outmode_WXGA_1280_800_75HZ  = 26,

	em_hdu_outmode_unknow,
};

//输出比列
enum EmHduShowMode
{
	em_hdu_showmode_NONGEOMETRIC   = 1,      //不等比缩放
	em_hdu_showmode_CUTEDGEGEOME   = 2,      //裁边等比缩放
	em_hdu_showmode_BLACKEDGEGEOME = 3,      //加黑边等比缩放

	em_hdu_showmode_unknow,
};

enum EmModifyNMServerRet
{
	em_nmserver_modify_success,		//修改(添加，修改，删除)成功
	em_nmserver_resource_full,		//服务器已满
	em_nmserver_invalid_handle,		//无效的句柄
};

enum EmModifyVcrRet
{
	em_vcr_modify_success,	//修改成功
	em_vcr_invalid,	//无效的录像机
	em_vcr_full,	//录像机已满
	em_vcr_no_exist,	//不存在
	em_vcr_exist,		//录像机已存在
};

enum EmModifyHduRet
{
	em_hdu_modify_success,	//修改成功
	em_hdu_invalid_index,	//无效的索引
	em_hdu_brd_no_cfg,		//板子未配置
};

enum EmUpdateHduRet
{
	em_hdu_update_success,	//升级成功
	em_hdu_update_ing,		//正在升级
	em_hdu_update_unreg,	//板子未注册
	em_hdu_update_unknow,	//未知原因
};

enum EmMPCodec
{
	emMPCodec1,
	emMPCodec2,
	emMPCodec3,
	emMPDualCodec,
	emEndMPCodec
};

enum EmTPHDAudPortIn
{
	emTPAudInCanon1,
	emTPAudInCanon2,
	emTPAudInCanon3,
	emTPAudInCanon4,
	emTPAudInCanon5,
	emTPAudInCanon6,
	emTPAudInCanon7,
	emTPAudInCanon8,
	emTPAudInCanon9,
	emTPAudInCanon10,
	emTPAudInDigit0,
	emTPAudInDigit1,
	emTPAudInDigit2,
	emTPAudInEnd
};

enum EmTPHDDualAudPortIn
{	
	emTPAudInTrs1, //TRS（3.5mm）线性输入（双流PC输入）
	emTPAudInTrs2,
	emTPAudInTrs3,
	emTPAudInTrs4,
	emTPAudInRcaL,// RCA（L/R) 线性输入（双流DVD输入）
	emTPAudInRcaR,
	emTPDualAudInEnd
};

enum EmTPHDAudPortOut
{
	emTPAudOutCCanon1  ,
	emTPAudOutCCanon2,
	emTPAudOutCCanon3,
	emTPAudOutCCanon4,
	emTPAudOutCCanon5,
	emTPAudOutReproducer,//内置扬声器
	emTPAudOutEnd
};

//终端视频输入端口
enum EmTPMtVideoPort
{
	emTPC1Vid   ,  //C1端子   DVI 1
	emTPC2Vid   ,  //C2端子   DVI 2
	emTPC3Vid   ,  //C3端子   DVI 3
	emTPC4Vid   ,  //C4端子   SUB IN 1
	emTPC5Vid   ,  //C5端子   SUB IN 2
	emTPC6Vid   ,  //C6端子   AUX IN 1
	emTPC7Vid   ,  //C7端子	  AUX IN 2
	emTPC8Vid   ,  //C8端子	  AUX IN 3
	emTPC9Vid   ,  //C9端子   AUX IN 4
	emTPC10Vid   ,  //C10端子 AUX IN 5
	emTPC11Vid   ,  //C11端子 AUX IN 6  
	emTPVidEnd
};


enum EmTPMtVideoOutPort
{
	emTPC1OutVid   ,  //C1端子   DVI 1
		emTPC2OutVid   ,  //C2端子   DVI 2
		emTPC3OutVid   ,  //C3端子   DVI 3
		emTPC4OutVid   ,  //C4端子   
		emTPC5OutVid   ,  //C5端子   
		emTPVidOutEnd
};

enum EmTPAutoTestType // 测试类别
{
    emTPAutoTestBegin,            //测试开始
	emTPAutoTestAudioLoopBackFunc,    //音频环回功能测试
	emTPAutoTestPriomVideoLoopBackFunc,    //主视频环回功能测试（主视屏）
	emTPAutoTestSecondVideoLoopBackFunc, //双流
	emTPAutoTestEnd               //测试结束
};

enum EmTPHduRunStatus
{
	emTPHduIdle,		//空闲状态
	emTPHduWaiting,		//等待
	emTPHduPlaying,		//播放状态
	emTPHduUnknow,		//未知状态
};

// 扬声器音量大小类型
enum EmTPLoudspeakerVal
{
	emTPLoudspeakerLow = 0,
		emTPLoudspeakerMiddle,
		emTPLoudspeakerHigh,
};
//帧率单位类型
enum EmTPFrameUnitType
{
    emTPFrameSecond =0,
		emTPSecondFrame =1
};

//视频制式类型
enum EmTPVideoStandard
{
    emTPPAL  =0 ,
		emTPNTSC = 1 ,
		//    emTPSECAM = 2
};

//台标类型
enum EmTPLabelType
{
    emTPLabelAuto    =0,   //自动
		emTPLabelUserDef =1,  //自定义
		emTPLabelOff     =2  //关闭
};

//台标位置类型
enum EmTPLabelPosType
{ 
	emTPTopLeft      = 0,
		emTPTopRight     = 1,
		emTPBottomLeft   = 2,
		emTPBottomRight  = 3
};

//双流显示模式
enum EmTPDualVideoShowMode
{
    emTPDualVideoOnSigleScreen  =0,//单屏双显
		emTPEachVideoOwnScreen      =1,//双屏双显
		emTPTripleVideoOnSingleScn  =2 //单屏三显
};

//显示比例
enum EmTPDisplayRatio
{
	emTPDR4to3      = 0, //4:3
		emTPDR16to9     = 1, //16:9
		emTPDRAuto      = 2, //0:0
};

//FEC算法类型
enum EmTPFecModeType
{
	emTPFECTYPENONE  =				0x00,
		emTPFECTYPERAID5 =				0x01,
		emTPFECTYPERAID5INTERLEAVE =	0x02,
		emTPFECTYPERAID6 =				0x03,			//此项暂时不允许界面配置
};

// 重传时所选择的网络类型
enum EmTPNetType
{
	emTPInternet = 0,
		emTPSpecial,
		emTPVPN,
};

//均衡器频率点
enum EmTPEqualizerRate
{
	emTPRate100,
	emTPRate200,
	emTPRate400,
	emTPRate600,
	emTPRate1k,
	emTPRate3k,
	emTPRate6k,
	emTPRate12k,
	emTPRate14k,
	emTPRate16k,
	emTPRateend
};

enum  EmTPPIPMode
{
	TP_VIDEO_PIPMODE_IDLE = 0,              //空闲
	TP_VIDEO_PIPMODE_LOOP,                 //自环
	TP_VIDEO_PIPMODE_ONE_LOCAL,             //单画面看本地
	TP_VIDEO_PIPMODE_ONE_OTHER,             //单画面看远端
	TP_VIDEO_PIPMODE_THREE_L_ONEBIG,         //三画面，左边大二小
	TP_VIDEO_PIPMODE_THREE_M_ONEBIG,         //三画面，中间大二小
	TP_VIDEO_PIPMODE_THREE_R_ONEBIG,         //三画面，右边大二小
	TP_VIDEO_PIPMODE_ONE_AUX_LOCAL         //单画面看本地双流        
};

enum EmTPDVIMode
{
	TP_DVI_MODE_HDMI,
	TP_DVI_MODE_VGA,
	TP_DVI_MODE_DVI,
	TP_DVI_MODE_Ypbpr,
	TP_DVI_MODE_INVALID
};	

//MC 的模式
enum EmTPMCMode
{
	emTPMcSpeech  ,//演讲模式
		emTPMcDiscuss ,//讨论模式
		emTPMcModeEnd
};

//cns升级状态
enum EmCnsUpdateState
{
	emCnsIdle,
		emCnsDownloading,
		emCnsDownloaded,
		emCnsUpdating,
};

//cn登录升级服务器的结果
enum EmTPCnLoginUpdateRet
{
	emTPCnLoginUpdateInvalid,
	emTPCnLoginUpdateFail,
	emTPCnLoginUpdateSuccess,
};

//服务器使用过的所有版本号
enum EmTPFileSrvUsedVersion
{
    emTPFileSrvUsedVersion1     = 1,
		emTPFileSrvUsedVersion2     = 2
};

//文件类型
enum EmTPFileSrvFileType
{
    emTPFileSrvFileTypeUnknown      = 0,//未知
		emTPFileSrvFileTypeService      = 1,//业务文件
		emTPFileSrvFileTypeConsole      = 2//控制台文件
};

enum EmTPOSType
{
	emTPWindows,
	emTPLinux
};

enum EmMPAudEncCodec
{
	emMPAudEncCodec1,
	emMPAudEncCodec2,
	emMPAudEncCodec3,
	emMPAudEncDualCodec,
	emMPAudEncMixCodec,
	emEndMPAudEncCodec
};

enum EmToolType
{
	emMainTerabceTool,//维护工具
	emProTestTool  //生产测试工具
};

//add by niulifu
enum EmProducetestType
{
	emProducetestTypeBegin,
	emTestVideoMAIN1InOut,
	emTestVideoMAIN2InOut,
	emTestVideoMAIN3InOut,
	emTestVideoSUB1InMAIN3AUX12Out,
	emTestDualSUB2InTurnHDMIAUX1Out,
	emTestDualAUX1InTurnHDMIAUX1Out,
	emTestDualAUX2InTurnHDMIAUX1Out,
	emTestDualAUX3InTurnHDMIAUX1Out,
	emTestDualAUX4InTurnHDMIAUX2Out,
	emTestDualAUX5InTurnHDMIAUX2Out,
	emTestDualAUX6InTurnHDMIAUX2Out,
	emTestDualSUB2InTurnVGAAUX1Out,
	emTestDualAUX1InTurnVGAAUX1Out,
	emTestDualAUX2InTurnVGAAUX1Out,
	emTestDualAUX3InTurnVGAAUX1Out,
	emTestDualAUX4InTurnVGAAUX2Out,
	emTestDualAUX5InTurnVGAAUX2Out,
	emTestDualAUX6InTurnVGAAUX2Out,
	emTestAudioMIC1InMAIN1Out,
	emTestAudioMIC2InMAIN2Out,
	emTestAudioMIC3InMAIN3Out,
	emTestAudioCANNON1InMAIN1Out,
	emTestAudioCANNON2InMAIN1Out,
	emTestAudioCANNON3InMAIN1Out,
	emTestAudioCANNON4InMAIN2Out,
	emTestAudioCANNON5InMAIN2Out,
	emTestAudioCANNON6InMAIN2Out,
	emTestAudioCANNON7InMAIN3Out,
	emTestAudioCANNON8InMAIN3Out,
	emTestAudioCANNON9InMAIN3Out,
	emTestAudioCANNON10InMAIN2Out,
	emTestAudioAUX1InAUX1Out,
	emTestAudioAUX2InAUX1Out,
	emTestAudioAUX3InAUX1Out,
	emTestAudioAUX4InAUX2Out,
	emTestAudioAUX5InAUX2Out,
	emTestAudioAUX6InAUX2Out,
	emTestUSB1Func,
	emTestUSB2Func,
	emTestRTCFunc,
	emTestLightFunc,
	emTestLAN1Func,
	emTestLAN2Func,
	emTestRS232LoopbackFunc,
	emTestRS422LoopbackFunc,
	emTestRS485LoopbackFunc,
	emTestRS232ANDCOM1LoopbackFunc,
	emTestRS422ANDCOM2LoopbackFunc,
	emTestCOM3ANDCOM4LoopbackFunc,
	emTestCOM5ANDCOM6LoopbackFunc,
	emTestInfraredRecFunc,
	emTestInfraredSendFunc,
	emTestALMLoopBackFunc,
	
	//主音频输入一致性测试项——同一个输出接口与不同输入接口环回
    emTestAudioInMain1OutCannon1In,
	emTestAudioInMain1OutCannon2In,
	emTestAudioInMain1OutCannon3In,
	emTestAudioInMain1OutCannon4In,
	emTestAudioInMain1OutCannon5In,
	emTestAudioInMain1OutCannon6In,
	emTestAudioInMain1OutCannon7In,
	emTestAudioInMain1OutCannon8In,
	emTestAudioInMain1OutCannon9In,
	emTestAudioInMain1OutCannon10In, //以上10项为一个测试项

	//输出一致性测试项——不同输出接口与同一个输入接口环回
	emTestAudioOutMainL1OutCannon1In,
	emTestAudioOutMainR1OutCannon1In,
	emTestAudioOutMainL2OutCannon1In,
	emTestAudioOutMainR2OutCannon1In,
	emTestAudioOutMainL3OutCannon1In,
	emTestAudioOutMainR3OutCannon1In, //以上6项为一个测试项
	emProducetestTypeEnd
};


//针对录像机文件操作的结果
enum EmMdyRecFileRes
{
	em_rec_file_unknow,
	em_rec_file_success,
	em_rec_file_longnamesize,	//过长的文件名
	em_rec_file_inuse,			//文件正在被操作
	em_rec_file_nameexist,		//文件名已存在
	em_rec_file_invalidrecorder,	//无效的录像机
	em_rec_file_noregisted,		//未注册
	em_rec_file_invalid_info,	
};


//开始录像的结果
enum EmUseReccorderRes
{
	em_rec_success,				//成功
	em_rec_invalid,				//无效的录像机
	em_rec_unregisted,			//未注册
	em_rec_no_resource,			//无可用资源
	em_rec_invalid_conf,		//无效的会议
	em_rec_invalid_format,		//无效的格式
	em_rec_unknow_rectype,		//未知的录制类型
	em_rec_invalid_mt,			//无效的会场
	em_rec_recordering,			//正在录像
	em_rec_playing,				//正在放像
	em_rec_chair_playing,		//上级正在进行放像
	em_rec_server_reject,		//录播服务器拒绝
	em_rec_invalid_rec_info,	//未找到对应的录制信息
	em_rec_invalid_play_info,	//未找到对应的播放信息
	em_rec_no_in_pause,			//会议不处于暂停状态
	em_rec_mt_offline,			//会场掉线
	em_rec_name_hasunderline,	//名字中包含下划线
	em_rec_longnamesize,		//过长的文件名
	em_rec_fileexist,			//文件已经存在
	em_rec_fileinuse,			//文件正在被操作
	em_rec_loadlib_failed,		//录播服务器调用lib库失败
	em_rec_setrecmode_failed,	//设置录像方式失败
	em_rec_publicfailed,		//发布失败
	em_rec_inrequesting,		//正在请求
	em_rec_req_failed,			//请求失败
	em_rec_norecord,			//未录像
	em_rec_file_damange,		//文件损坏
	em_rec_in_stopping,			//录像正在被停止
	em_rec_in_pausing,			//录像处于处于暂停状态
	em_rec_no_in_working,		//不处于工作状态
	em_rec_invalid_channel,		//无效的通道
	em_rec_unmatch_format,		//格式未匹配
	em_rec_unknow_reason,				//未知错误
};

//录像类型
enum EmRecorderType
{
	em_rec_recorder_unknow,
	em_rec_recorder_conf,	//录制会议
	em_rec_recorder_mt,		//录制终端
};

//录像状态
enum EmConfRecState
{
	em_rec_unknow,
	em_rec_init,		//初始化
	em_rec_working,		//正在录像
	em_rec_pause,		//处于暂停状态
	em_rec_finish,		//完成
};

//End Add


//add
//add
enum EmTpProfile
{
	emTpProfileBaseline = 64,
	emTpProfileMain = 32,
	emTpProfileExtend = 16,
	emTpProfileHigh = 8
};

enum EmTPHandleCfgType
{
	emTPShowCfg, //显示配置信息
	emTPSetCfg,  //设置配置信息
	emTPPostCfg  //发送配置信息
};

//编解码类型
enum EmTpCodecType
{
	emTpVEnc = 0,
		emTpVDec,
		emTpAEnc,
		emTpADec,
};

//维护工具状态
enum EmToolState
{
	em_Tool_IDLE = 0,
	em_Tool_READY
};

//音频播放模式
enum EmTPAudPlayMode
{
    emTP_PLAY_FULL = 0,     //3路播放
    emTP_PLAY_SINGLE        //单路播放	
};

//双流音频输入端口模式
enum EmTPAudDualInMode
{
    emTP_AUD_DUAL_AUTO = 0,     //自动     
	emTP_AUD_DUAL_HDMI,        //设置hdmi
    emTP_AUD_DUAL_LINEIN,      //设置RCA，TRS
};

enum EmTPDualType
{
	emTP_TPad_DUAL_VEDIO = 0,  // pc daul vedio from TPad
	emTP_DV_DUAL_VEDIO,   
	emTP_NONE_DUAL_VEDIO
};


enum EmTPDsNode
{
	emTp_Ds = 0,
	emTp_Node = 1
};

enum EMScreenLooked
{
	emScreenInvalid	=	0,		//无效屏幕
	emScreenSelf	=	1,		//空闲
	emScreenSpeaker =	2,		//看发言人
	emScreenPoll	=	3,		//看轮询
	emScreenView	=   4,		//选看
	emScreenDiscard	=   5,		//看讨论图像
	emScreenRecPlay =   6,		//看放像
		
	emScreenLookedEnd = 7,		//主席屏状态的种类数目
};

//moon add
//dvi 支持类型
enum EmTPDVIOutPortType
{
	TPMOON_DVI_MODE_HDMI,
	TPMOON_DVI_MODE_DVI,
	TPMOON_DVI_MODE_INVALID
};

//Moon 支持切换的输出制式
enum EmTPMOONOutMode
{
	em_MoonOutMode_720P_60fps,
	em_MoonOutMode_720P_50fps,
	em_MoonOutMode_1080P_25fps,
    em_MoonOutMode_1080P_30fps,
    em_MoonOutMode_1080P_50fps,
	em_MoonOutMode_1080P_60fps,
    em_MoonOutMode_4K_25fps,
    em_MoonOutMode_4K_30fps,//(默认)
	em_MoonOutMode_Unknown
};

//图像调节
enum EmTPImageAdjust
{
	emClosed,
	emVertTurn,
	emflatTurn
};
//聚焦、曝光、白平衡模式
enum EmTPMOOMMode
{
	emAuto,
	emManual
};

//手动聚焦
enum EmTPManualMode
{
	emFarth,
	emNearth
};

//视野
enum EmTPZOOM
{
	emEnlarge,
	emReduce
};

//摄像机 曝光--增益
enum EmTPExpGain
{
	em_Gain_Nega10_5dB = 0x00,
	em_Gain_Nega9dB          ,
	em_Gain_Nega7_5dB        ,
	em_Gain_Nega6dB          ,
	em_Gain_Nega4_5dB        ,
	em_Gain_Nega3dB          ,
	em_Gain_Nega1_5dB        ,
	em_Gain_ZerodB               ,
	em_Gain_Posi1_5dB        ,
	em_Gain_Posi3dB          ,
	em_Gain_Posi4_5dB        ,
	em_Gain_Posi6dB          ,
	em_Gain_Posi7_5dB        ,
	em_Gain_Posi9dB          ,
	em_Gain_Posi10_5dB 
};

//摄像机输出60/30fps  曝光--快门
enum EmTPSOrThShutter
{
	em_Shutter_1Sp  = 0x00,   // 1/1
	em_Shutter_2Sp ,          // 1/12
	em_Shutter_4Sp ,          // 1/4
	em_Shutter_8Sp ,          // 1/8
	em_Shutter_15Sp ,         // 1/15
	em_Shutter_30Sp ,         // 1/30
	em_Shutter_60Sp ,         // 1/60
	em_Shutter_90Sp ,         // 1/90
	em_Shutter_100Sp,         // 1/100(默认)
	em_Shutter_125Sp,         // 1/125
	em_Shutter_180Sp,         // 1/180
	em_Shutter_250Sp,         // 1/250
	em_Shutter_350Sp,         // 1/350
	em_Shutter_500Sp,         // 1/500
	em_Shutter_725Sp,         // 1/725
	em_Shutter_1000Sp,        // 1/1000
	em_Shutter_1500Sp,        // 1/1500
	em_Shutter_2000Sp,        // 1/2000
	em_Shutter_3000Sp,        // 1/3000
	em_Shutter_4000Sp,        // 1/4000
	em_Shutter_6000Sp,        // 1/6000
	em_Shutter_10000Sp        // 1/10000
};

//摄像机输出50/25fps  曝光--快门
enum EmTPFOrTwShutter
{
	em_Shutter_1Spd  = 0x00,   // 1/1
	em_Shutter_2Spd ,          // 1/12
	em_Shutter_3Spd ,          // 1/3
	em_Shutter_6Spd ,          // 1/6
	em_Shutter_12Spd ,         // 1/12
	em_Shutter_25Spd ,         // 1/25
	em_Shutter_50Spd ,         // 1/50
	em_Shutter_60Spd ,         // 1/60
	em_Shutter_75Spd ,         // 1/75
	em_Shutter_100Spd,         // 1/100(默认)
	em_Shutter_120Spd,         // 1/120
	em_Shutter_150Spd,         // 1/150
	em_Shutter_215Spd,         // 1/215
	em_Shutter_300Spd,         // 1/300
	em_Shutter_425Spd,         // 1/425
	em_Shutter_600Spd,         // 1/600
	em_Shutter_1000Spd,        // 1/1000
	em_Shutter_1250Spd,        // 1/1250
	em_Shutter_1750Spd,        // 1/1750
	em_Shutter_2500Spd,        // 1/2500
	em_Shutter_3500Spd,        // 1/3500
	em_Shutter_6000Spd,        // 1/6000
	em_Shutter_10000Spd        // 1/10000
};

//摄像机 曝光--光圈
enum EmTPAperture
{
	em_Aperture_OFF  = 0x00,
    em_Aperture_F14 = 0x05,
    em_Aperture_F11,
	em_Aperture_F9_6,
	em_Aperture_F8,
	em_Aperture_F6_8,
	em_Aperture_F5_6,
	em_Aperture_F4_8,
	em_Aperture_F4,
	em_Aperture_F3_4,
	em_Aperture_F2_8,
	em_Aperture_F2_4,
	em_Aperture_F2,
	em_Aperture_F1_8 //(默认)
};

enum EmTPReduNoise
{
	emClose,
	emLevelFist,
	emLevelSecond,
	emLevelThird,
	emLevelFourth,
	emLeVelFifth
};

enum EmTPImagePara
{
	emBlight,    //亮度
	emContrast,  //对比度
	emSharp,     //锐度
	emSaturat,   //饱和度
    emHue,       //色调
    emGama       //伽马
};

//图像拼接
enum EmImageMosaicType
{
    em_Mosaic_Cut,           //裁剪
	em_Mosaic_Stretch,       //拉伸
	em_Mosaic_Adjust,        //梯形校正调整
	em_Mosaic_Redunoise      //降噪
};
//降噪
enum EmTPFpgaReduNoise
{
	emFpgaClose,
	emFpgaLow,
	emFpgaMid,
	emFpgaHight
};

enum EmMOONProductTestType
{
	emProducetestBegin,
	emTestDVI1_HDMI,
	emTestDVI2_HDMI,
	emTestDVI3_HDMI,
	emTestEth,
	emTestRS232,
	emTestGreenRedLight,
	emTestGreenLight,
	emTestZoom_DVI1_HDMI,
	emTestZoom_DVI2_HDMI,
	emTestZoom_DVI3_HDMI,
	emTestThreeSnapShot,
	emTestCAM1_LvdsBaud,
	emTestCAM2_LvdsBaud,
	emTestCAM3_LvdsBaud,
	emProducetestEnd
};
//LVDS 波特率
enum EmTPLVDSBaud
{
	em_LVDSBaud_9600bps,//(默认)
	em_LVDSBaud_19200bps,
	em_LVDSBaud_38400bps,
	em_LVDSBaud_115200bps,
	em_LVDSBaud_Unknown
};
//梯形校正
enum EmTPCorrect
{
	em_HorizonCorrect,
	em_HorizonStretch,
	em_VerticalCorrect,
	em_VerticalStretch
};

//版本号
enum EmTpVer
{
	tp_Ver_MOON90,
	tp_Ver_MOON90H
};


enum EmTPCorrectChange
{
	emCorrectEnlarge,//增加
	emCorrectReduce//减小
};

enum EmTPCamNoiseLevel
{
	emNoiseClose,
	emNoiseLevel1,
	emNoiseLevel2,
	emNoiseLevel3,
	emNoiseLevel4,
	emNoiseLevel5
};

//add by youjx 2016.11.21
enum EmTPMechanism
{
    emH650 = 0,
    emSony = 1,
    emSonyFCBCS8230 = 2
};

enum EmH650Gamma
{
    emGamma1 = 0x00,
    emGamma2,
    emGamma3,
    emGamma4
};
//颜色一致性RGB类型
enum EmTPColorConsistency
{
    emColorRed,
    emColorBlue,
    emColorGreen
};
//梯形校正的位置
enum EmTPDistortPosition
{
    emUperLeftHorizon,       //左上角顶点左右拉伸
    emUperLeftVertical,      //左上角顶点上下拉伸
    emUperRightHorizon,      //右上角顶点左右拉伸
    emUperRightVertical,     //右上角顶点上下拉伸
    emLowerRightHorizon,     //右下角顶点左右拉伸
    emLowerRightVertical,    //右下角顶点上下拉伸
    emLowerLeftHorizon,      //左下角顶点左右拉伸
    emLowerLeftVertical,     //左下角顶点上下拉伸
    emLeftSide,              //左边拉伸
    emRightSide,             //右边拉伸
    emTopSide,               //上边拉伸
    emBottomSide,            //下边拉伸
    emCenterRotate,          //中心旋转
};

//add end

//moon end
#endif // _h_tpcommontype_h__