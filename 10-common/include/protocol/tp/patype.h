#ifndef _PA_TYPE_H_
#define _PA_TYPE_H_
typedef u32 u32_ip;

enum EmBegin
{
	emBegin,
};

enum EmPAVendorID
{
	emPA_vendor_MICROSOFT_NETMEETING = 1,
	emPA_vendor_KEDA,
	emPA_vendor_KEDA_IPC,
	emPA_vendor_HUAWEI,
	emPA_vendor_POLYCOM,
	emPA_vendor_POLYCOM_MCU,
	emPA_vendor_TANDBERG,
	emPA_vendor_RADVISION,
	emPA_vendor_VCON,
	emPA_vendor_SONY,
	emPA_vendor_VTEL,
	emPA_vendor_ZTE,
	emPA_vendor_ZTE_MCU,
	emPA_vendor_CODIAN,
	emPA_vendor_AETHRA,
	emPA_vendor_CHAORAN,
	emPA_vendor_UNKNOWN,
	emPA_vendor_END
};

enum EmPAMediaType
{
	emPAMediaNone,
	emPAMediaAudio,
	emPAMediaVideo,
	emPAMediaH224,
	emPAMediaT120,
};

enum EmPAProfileMask
{
	emPAProfileBaseline = 64,
	emPAProfileMain = 32,
	emPAProfileExtend = 16,
	emPAProfileHigh = 8,
};

//视频协议类型
enum EmPAVideoFormat
{
    emPAVH261     = 0,
	emPAVH262     = 1,//MPEG2
	emPAVH263     = 2,
	emPAVH263plus = 3,
	emPAVH264     = 4,
	emPAVMPEG4    = 5,
		
	emPAVEnd		
};

//音频协议类型
enum EmPAAudioFormat
{
	emPAAG711a  = 0,
	emPAAG711u  = 1,
	emPAAG722   = 2,
	emPAAG7231  = 3,
	emPAAG728   = 4,
	emPAAG729   = 5,
	emPAAMP3    = 6,
	emPAAG721   = 7,
	emPAAG7221  = 8,
	emPAAG719   = 9,
	emPAAMpegAACLC =10,
	emPAAMpegAACLD = 11,
		
	emPAAEnd	 
};

enum  EmPAPayloadType 
{
	emPAPayloadTypeBegin = 0,
		//音频格式
	emPAAudioTypeBegin,
	emPAG711a,
	emPAG711u,
	emPAG722,
	emPAG7231,
	emPAG728,
	emPAG729,
	emPAMp3,  
	emPAG723,
	emPAG7221,
	emPAMpegaaclc,
	emPAMpegaacld,
	emPAG719,
	emPAAudioTypeEnd = 49,
		
		//视频格式
	emPAVideoTypeBegin = 50,	
	emPAH261,
	emPAH263,
	emPAH263plus,
	emPAH264,
	emPAH262,
	emPAMpeg4,
	emPAVideoTypeEnd = 99,
        
	emPADataTypeBegin = 100,	
	emPAT120,
	emPAH224,
	emPADataTypeEnd = 149,
		
	emPAPayloadTypeEnd = 255
};

//分辨率
enum EmPAResolution
{
    emPAResolutionBegin = 0,
	emPASQCIF,
	emPAQCIF,
	emPACIF,
	emPACIF2,
	emPACIF4,
	emPACIF16,
		
	emPASIF,
	emPASIF4,
	emPAVGA,
	emPASVGA,
	emPAXGA,
		
	emPAWCIF4,  //1024*576
	emPAHD720,  //1280*720
	emPASXGA,   //1280*1024
	emPAUXGA,   //1600*1200
	emPAHD1080, //1920*1080
	emPAAuto,
	emPAResolutionEnd
};

enum EmPAVideoResolution
{
    emPAVResolutionAuto     = 0,   //自动
	emPAVSQCIF              = 1,   //SQCIF88x72
	emPAVQCIF               = 2,   //QCIF176x144
	emPAVCIF                = 3,   //CIF352x288
	emPAV2CIF               = 4,   //2CIF352x576
	emPAV4CIF               = 5,   //4CIF704x576
	emPAV16CIF              = 6,   //16CIF1408x1152
		
	emPAVHD480i720x480      = 7,   //480i720x480
	emPAVHD480p720x480      = 8,   //480p720x480
	emPAVHD576i720x576      = 9,   //576i720x576
	emPAVHD576p720x576      = 10,  //576p720x576
		
	emPAVHD720p1280x720     = 11,  //720p1280x720
	emPAVHD1080i1920x1080   = 12,  //1080i1920x1080
	emPAVHD1080p1920x1080   = 13,  //1080p1920x1080
		
		
	emPAVGA352x240          = 14,  //352x240
	emPAVGA704x480          = 15,  //704x480
	emPAVGA640x480          = 16,  //VGA640x480
	emPAVGA800x600          = 17,  //SVGA800x600
	emPAVGA1024x768         = 18,  //XGA1024x768
	emPAVGA1280x768         = 19,  //WXGA1280x768
	emPAVGA1280x800         = 20,  //WXGA1280x800
	emPAVGA1366x768         = 21,  //WXGA1366x768
	emPAVGA1280x854         = 22,  //WSXGA1280x854
	emPAVGA1440x900         = 23,  //WSXGA1440x900
	emPAVGA1280x1024        = 24,  //SXGA1280x1024
	emPAVGA1680x1050        = 25,  //SXGA+1680x1050
	emPAVGA1600x1200        = 26,  //UXGA1600x1200
	emPAVGA1920x1200        = 27,  //WUXGA1920x1200
		
	emPAVSQCIF112x96        = 28,
	emPAVSQCIF96x80         = 29,
	emPAV320x192            = 30,
	emPAV432x240            = 31,
	emPAV480x272            = 32,
	emPAV640x368            = 33,
	emPAV864x480            = 34,
	emPAV960x544            = 35,
	emPAV1440x816           = 36,
		
	emPAVResEnd = 50,
};

enum EmDualReason
{
	emDualAccept,//接收
	emDualBusy,//忙
	emDualPreemptive,//抢发双流
	emDualPeerReject,//对端拒绝
	emDualPeerStop,//对端停止双流
	emDualNoVideo,//无双流视频源
    emDualLocalStop, //本地停止双流
};

enum EmPAOprType
{
	PA_OprType_Add,			//增加
	PA_OprType_Del,			//删除
	PA_OprType_Update,		//修改
	PA_OprType_Null         //清空
};

// enum EmPACnsCallReason	
// {
// 	    EmPACnsCallReason_success,
// 		EmPACnsCallReason_hungup,			//对端不接受或者主动挂断
// 		EmPACnsCallReason_Unreachable,	//对端不在线，无法呼叫
// 		EmPACnsCallReason_resourcefull,	//对端无可用资源
// 		EmPACnsCallReason_dstnotfind,		//目标不存在
// 		EmPACnsCallReason_Busy,			//对端忙
// 		EmPACnsCallReason_Local,			//本地原因
// 		EmPACnsCallReason_NoConf,			//会议不存在
// 		EmPACnsCallReason_Exist			//对端已在本会议中
// };
enum EmPATPEndpointType
{
	emPATPEndpointTypeUnknown    = 0,
	emPATPEndpointTypeCNS	     = 0x01,
	emPATPEndpointTypeUMS		 = 0x02,
	emPATPEndpointTypeRegister   = 0x04,

	emPATPEndpointH323MT,
	emPATPEndpointH323MCU,
	emPATPEndpointH323SingleMCU,
	emPATPEndpointH323G400,
	emPATPEndpointTypeVRS,	

};

enum EmPATpApplySpeakerRet
{
	emPA_ApplySpeaker_Success,  
	emPA_ApplySpeaker_ConfUnExist,   //会议不存在
	emPA_ApplySpeaker_EpIDError,     //会场不存在
	emPA_ApplySpeaker_EpStateError,  //会场未在线或通道不未建立
};

enum EmPATPDualReason
{
    emPATpDualAccept,
	emPATpDualBusy,
	emPATpDualPreemptive,
	emPATpDualPeerReject,
	emPATpDualPeerStop,
	emPATpDualNoVideo,
	emPATpDualLocalStop,
	emPATpDualSndFail,            //发送双流失败
};

enum EmPACnsCallReason	
{
	EmPACnsCallReason_success,
	EmPACnsCallReason_hungup,			//本地挂断
	EmPACnsCallReason_Unreachable,		//对端不在线，无法呼叫
	EmPACnsCallReason_resourcefull,		//对端无可用资源
	EmPACnsCallReason_dstnotfind,		//目标不存在
	EmPACnsCallReason_Busy,				//对端忙
	EmPACnsCallReason_Local,			//本地原因
	EmPACnsCallReason_NoConf,			//会议不存在
	EmPACnsCallReason_Exist,			//对端已在本会议中
	EmPACnsCallReason_Rejected,			//对端拒绝
	EmPACnsCallReason_peerhungup,		//对端挂断
	//	EmCnsCallReason_AlreadyDual,    //对端在双流
	EmPACnsCallReason_Abnormal,			//本地掉线挂断
	EmPACnsCallReason_PeerAbnormal,		//对端掉线挂断
	EmPACnsCallReason_unknown,   
};

enum EmPATpMixStatus
{
	emPAAudMixIdle,
	emPAAudMixAssignChan_Fail,
	emPAAudMixAssignChan_Success,
		
	emPAAudMixOpenChan_Fail,		//创建语音激励通道失败
	emPAAudMixOpenChan_Success,     //创建语音激励通道成功
		
	emPAAudMixDisConnect,			//混音板断链
		
	emPAAudOpenChan_Fail,			//打开语音通道失败
	emPAAudOpenChan_Success			//打开语音通道成功
};

enum EmPAAliasType
{
	emPA_Alias_Unknow,
	emPA_Alias_e164,
	emPA_Alias_h323,
	emPA_Alias_IP,
};

enum EmPADisListOprType
{
	emPA_DisListOpr_Add,
	emPA_DisListOpr_Del,
};

enum EmPADisListOprReslt
{
	emPA_DisListOpr_Sucess,
	emPA_DisListOpr_Fail,
	emPA_DisListOpr_Reject,
		
};


enum EmPAAACSampleFreq                    //sampling frequency
{
	emPAFs96000 = 0,
    emPAFs88200 = 1,
    emPAFs64000 = 2,
    emPAFs48000 = 3,
    emPAFs44100 = 4,
    emPAFs32000 = 5,
    emPAFs24000 = 6,
    emPAFs22050 = 7,
    emPAFs16000 = 8,
    emPAFs12000 = 9,
    emPAFs11025 = 10,
    emPAFs8000  = 11
};

enum EmPAAACChnlCfg                       //channel config
{
	emPAChnlCust   = 0,
    emPAChnl1      = 1,                   //单声道
    emPAChnl2      = 2,                   //双声道
    emPAChnl3      = 3,
    emPAChnl4      = 4,
    emPAChnl5      = 5,
    emPAChnl5dot1  = 6,                   //5.1声道
    emPAChnl7dot1  = 7                    //7.1声道
};

enum EmPATPVMPStyle
{		
	emPAVmpStyle_DYNAMIC = 0,	//动态分屏(仅自动合成时有效)	0
	emPAVmpStyle_ONE,			//一画面						1
	emPAVmpStyle_VTWO,			//两画面：左右分				2
	emPAVmpStyle_HTWO,			//两画面: 一大一小				3
	emPAVmpStyle_THREE,			//三画面						4
	emPAVmpStyle_FOUR,			//四画面						5
	emPAVmpStyle_SIX,			//六画面						6
	emPAVmpStyle_EIGHT,			//八画面						7
	emPAVmpStyle_NINE,			//九画面						8
		
	emPAVmpStyle_TEN,			//十画面						9
	emPAVmpStyle_THIRTEEN,		//十三画面						10
	emPAVmpStyle_SIXTEEN,		//十六画面						11
	emPAVmpStyle_SPECFOUR,		//特殊四画面					12
	emPAVmpStyle_SEVEN,			//七画面						13
	emPAVmpStyle_TWENTY,		//二十画面						14
	emPAVmpStyle_TEN_H,			//水平分割的十画面(上2下8)		15
	emPAVmpStyle_SIX_L2UP_S4DOWN,	//特殊六画面(上2下4)		16
	emPAVmpStyle_FOURTEEN,			
	//十四画面					17
	emPAVmpStyle_TEN_M,				//十画面(上4中2下4)			18
	emPAVmpStyle_THIRTEEN_M,		//十三画面(一大在中间)		19
	emPAVmpStyle_FIFTEEN,			//十五画面					20
	emPAVmpStyle_SIX_DIVIDE,		//六画面(等分)				21
	emPAVmpStyle_leftBig,			//三画面，2个小的在底部靠右	22
	emPAVmpStyle_MidBig,			//三画面，2个小的在底部两边	23
	emPAVmpStyle_RightBig,			//三画面，2个小的在底部靠左	24
	emPAVmpStyle_3VERTICAL,			//
	//三画面，垂直等大			25
	emPAVmpStyle_FOUR_3BOTTOMMIDDLE,	//四画面，3个在底部中央		26
	emPAVmpStyle_TWENTYFIVE,			//二十五画面				27
		
};

enum EmPATPVMPType
{
	emPATPVMP_Room,  //会场名
	emPATPVMP_Speaker, //发言人跟随
	emPATPVMP_Dual     //双流跟随
};

enum EmPAViewEpType
{
	EmPAEpType_Ter,
	EmPAEpType_Eqp,
};


enum EmPAUIType
{
	EmPAUI_CNC = 1,
	EmPAUI_UMC = 2,
	EmPAUI_Tools = 4
};


enum EmPAGetVidType
{
	em_PAGetVid_Invalid,
	em_PAGetVid_View,		//选看
	em_PAGetVid_Poll,		//轮训
	em_PAGetVid_Vmp,		//画面合成
	em_PAGetVid_Hdu,		//电视前
	em_PAGetVid_Dis,		//讨论

	// 以下两个枚举定义新增
	em_PAGetVid_ViewEp,	//会场选看
	em_PAGetVid_OnlyAud,    // 只调音频
};

enum EmPAGetVidRes
{
	em_PAGetVid_Success,
	em_PAGitVid_No_Resource,	//无资源
};

enum EmPAPollStat
{
	emPAPollStat_Error,
	emPAPollStat_Stop,
	emPAPollStat_Start,
	emPAPollStat_Suspend,
};

enum EMPAScreenObj
{
	emPAObjSelf,		//无效屏幕
	emPAObjSpeaker,		//看发言人
	emPAObjChair,		//看主席
	emPAObjPoll,		//看选看
	emPAObjView,		//选看
	emPAObjDiscard,		//看讨论图像
	emPAObjVmpBrd,		//广播合成	
	emPAObjLookedEnd,	//主席屏状态的种类数目
};
enum EmPADiscussRspRet
{
	// 开启讨论的结果，注：关闭讨论，只回复Ok或者OtherFail
	emPADiscussOprRsp_Ok,	
	emPAStart_AssginVmpFail,		// 合成资源不足，开启讨论失败
	emPAStart_AssignMixFail,		// 混音资源不足，开启讨论失败
	emPAStart_AssignBasFail,		// 适配资源不足，开启讨论失败
	emPAStart_OtherFail,       
	emPADiscussOprRsp_End = 1000,	
};
enum EmPADiscussOprRes
{
    // 添加会场进讨论的结果，注：从讨论中删除会场，只回复Successed或者OtherFail
    emPADisucss_Opr_Successed,
        
    emPADiscuss_Invalid_Ep,      // 无效会场
    emPADiscuss_Screen_Full,     // 屏数不足
    emPADisccuss_GetVid_Error,   // 调码流出错
    emPADiscuss_No_BandWith,     // 级联间宽带不足
    emPADiscuss_AssignAudChan_Error,   // 给下级会场分配下传音频通道失败
    emPADiscuss_No_MixChan,      // 混音通道不足
    emPADiscuss_OtherFail,     
    emPADisccuss_Opr_End = 1000,
};
// begin add for hdu
enum EmPAHduRunStatus
{
	emPAHdu_Idle,		//空闲状态
	emPAHdu_Waiting,		//等待
	emPAHdu_Playing,		//播放状态
	emPAHdu_Unknow,		//未知状态
};
enum EmPAHduPlayNackReason
{
	em_PAhdu_play_success,
	em_PAHdu_Invalid_Index,	//无效的位置索引
	em_PAHdu_Invalid_ID,		//无效的ID
	em_PAHdu_No_Reged,		//HDU未注册

	em_PAHdu_Illegal,			//无效的hdu
	em_PAAlias_Illegal,		//无效的别名
	em_PAMonitor_Fail,		//上墙失败
	em_PAHdu_PlayNack,		//电视墙服务器拒绝
	em_PASame_Alias,			//重名
	em_PASame_Info,			//相同的信息
	em_PAunknown,				//未知的错误

};
enum EmPAHduSetVolRes
{
	em_PAhdu_SetVol_Success,
	em_PAhdu_SetVol_Invalid_Index,
	em_PAhdu_SetVol_UnReg,    
	em_PAhdu_SetVol_VmpChan,  // 多画面合成模式不能调节音量
};
enum EmPAHduChangeChanModeRes
{
	em_PAhdu_change_mode_success = 0,
	em_PAhdu_change_mode_error_index, // 无效的通道
	em_PAhdu_change_mode_error_param, // vmp mode参数错误
	em_PAhdu_change_mode_error_regstate, // 通道未注册
	em_PAhdu_change_mode_error_onlyoneVmp, // 电视墙两个通道只能有一个是vmp模式
	em_PAhdu_change_mode_error_workingstate, // 通道处于繁忙状态
	em_PAhdu_change_mode_error_fromhdu,   // hdu返回切换模式出错

};
enum EmPAModuleOperateType
{
	emPAModuleOperateType_NULL,       //空操作
	emPAModuleOperateType_Add,        //增加操作
	emPAModuleOperateType_Del,        //删除操作
	emPAModuleOperateType_Update      //修改操作
};

enum EmPAProtocolType
{
	emProtocolTypeInvalid = 0,
	emProtocolTypeH323  = 1, 
	emProtocolTypeSip   = 2, 
	emProtocolTypeAll   = 3,
};
// end add for hdu
#endif

