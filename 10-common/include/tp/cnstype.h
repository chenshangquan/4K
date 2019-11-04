#ifndef _h_cnstype_h__
#define _h_cnstype_h__
#include "osp.h"

enum EmTpMcuSelView
{
	emTpMcuSelView_Idle,
		emTpMcuSelView_Req,
		emTpMcuSelView_Success
};

enum EmTpColor
{
	emRed,
	emBlue,
	emYellow,
	emBlack,
	emGreen
};

enum EmTpSize
{
	emBig,
	emMid,
	emlittle
};

enum EmTpLogoStyle
{
	emLeftUp,
	emLeftDown,
	emMidUp,
	emMidDown,
	emRightUp,
	emRightDown
};

enum EmTpStyle
{
	emStyleOne,
	emStyleTwo,
	emStyleThree,
	emStyleFour,
	emStyleFive
};

enum emTpTransparency
{
	emTransparent,
	emTranslucent,
	Opaque
};

//cndevice模块枚举类型 --add by zhangapei
//显示器型号：Sharp 70LCD-LX640A、sharp 70LX550A，默认sharp 70LX550A,B4 fix添加康冠电视机
enum EmTVModle
{
	emSharp70LCD_LX640A,
	emSharp70LX550A,
	emSharp70LX565A,
	emKangGuan70B17,
	emKeShi70GMO1A,
	emKeShi70GH01A, //add by xqs
    emKeShi70GM44A, // add by heweihang
};

enum EmPanCamBright
{
	emBrightUp = 0x02,
	emBrightDown,
};

//add end

enum EmTpWorkMode 
{
    emTpIdle = 0,          //当前处于空闲状态
	emTpSingleVideo = 1,   //处于单流状态
	emTpMiniVideoSend = 2,  //发送小码流状态
	emTpMergeVideoSnd =3    //画面合成状态
};

enum EmTpVEncCodecType 
{
	emTpVEncCodec1 = 1,  //编码器1
	emTpVEncCodec2 = 2  //编码器2
};

//channel handle
enum EmTpChannelHandle
{
	emTp_ChanHandle_Begin,
	emTp_ChanHandle_Pri_VidSnd_0,
	emTp_ChanHandle_Pri_VidSnd_1,
	emTp_ChanHandle_Pri_VidSnd_2,	

	emTp_ChanHandle_Pri_VidRcv_0,
	emTp_ChanHandle_Pri_VidRcv_1,
	emTp_ChanHandle_Pri_VidRcv_2,
	
	emTp_ChanHandle_Pri_AudSnd_0,
	emTp_ChanHandle_Pri_AudSnd_1,
	emTp_ChanHandle_Pri_AudSnd_2,
	
	emTp_ChanHandle_Pri_AudRcv_0,
	emTp_ChanHandle_Pri_AudRcv_1,
	emTp_ChanHandle_Pri_AudRcv_2,	

	emTp_ChanHandle_Mix_Snd,
	emTp_ChanHandle_Mix_Rcv,
	
	emTp_ChanHandle_Snd_VidSnd,	
	emTp_ChanHandle_Snd_VidRcv,
	emTp_ChanHandle_Snd_AudSnd,	
	emTp_ChanHandle_Snd_AudRcv,
		
	emTp_Channel_Handle_End	 =	300,
};

enum EmTpVideoLoopTest
{
    emTp_All_Loop = 0, //四路自环
		emTp_Single_Loop = 1,//单路自环
		emTp_Mini_Loop = 2,//小画面自环  
		emTp_Merge_Loop =3  //画面合成自环  
};

enum EmTpDualIdleReason
{
	emTpNoSource, //开启演示失败，无视频源
	emTpBussyNow, //开启演示失败，会场忙，在会议中
	emTpSuccess   //开启演示成功
};

enum EmTpPadMaxCap //适配给PAD的最大能力
{
	emTp_PadMaxCap_720p30 = 0,
	emTp_PadMaxCap_1080p5 = 1,
	emTp_PadMaxCap_4Cif30 = 2
};

enum EmTpIpNameNatSyn
{
	emSynInvalid,
	emTpIpAndName,
	emTpIpAndNat,
	emTpNameAndNat,
	emTpAll
};


// begin add for hdu
enum EmCnsHduRunStatus
{
	emCnsHdu_Idle,		//空闲状态
	emCnsHdu_Waiting,		//等待
	emCnsHdu_Playing,		//播放状态
	emCnsHdu_Unknow		//未知状态
};  

enum EmCnsHduPlayNackReason
{
	em_Cnshdu_play_success,
	em_CnsHdu_Invalid_Index,	//无效的位置索引
	em_CnsHdu_Invalid_ID,		//无效的ID
	em_CnsHdu_No_Reged,		//HDU未注册
		
	em_CnsHdu_Illegal,			//无效的hdu
	em_CnsAlias_Illegal,		//无效的别名
	em_CnsMonitor_Fail,		//上墙失败
	em_CnsHdu_PlayNack,		//电视墙服务器拒绝
	em_CnsSame_Alias,			//重名
	em_CnsSame_Info,			//相同的信息
	em_Cnsunknown				//未知的错误		
};

enum EmCnsHduSetVolRes
{
	em_Cnshdu_SetVol_Success,
	em_Cnshdu_SetVol_Invalid_Index,
	em_Cnshdu_SetVol_UnReg,    
	em_Cnshdu_SetVol_VmpChan  // 多画面合成模式不能调节音量
};

enum EmCnsHduChangeChanModeRes
{
	em_Cnshdu_change_mode_success = 0,
	em_Cnshdu_change_mode_error_index, // 无效的通道
	em_Cnshdu_change_mode_error_param, // vmp mode参数错误
	em_Cnshdu_change_mode_error_regstate, // 通道未注册
	em_Cnshdu_change_mode_error_onlyoneVmp, // 电视墙两个通道只能有一个是vmp模式
	em_Cnshdu_change_mode_error_workingstate, // 通道处于繁忙状态
	em_Cnshdu_change_mode_error_fromhdu   // hdu返回切换模式出错
		
};

enum EmEthState
{
	em_BackMode,
	em_DoubleMode
};
// end add for hdu


#endif // _h_cnstype_h__

