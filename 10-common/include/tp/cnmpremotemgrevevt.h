#ifndef _CN_MPREMOTEMGR_EVENT_H
#define _CN_MPREMOTEMGR_EVENT_H
#include "kdvdef.h"
#include "osp.h"

//消息开始基数
#define ev_mprMsgbegin (OSP_USEREVENT_BASE + 1)

//注册消息
#define ev_mprRegCmd                    (u16)(ev_mprMsgbegin + 1) //参数：TRegInfo
//注册回应
#define ev_mprRegInd                    (u16)(ev_mprMsgbegin + 2) //参数：TRegInfo + s32返回值（参考CNMP_ERR_SUCCESS）

//X500接收码流
//X500码流接收地址, RTP, RTCP, 此时消息方向 X500-->T300E 
//X500码流发送RTCP地址, BackRTCP   此时消息方向 T300E--> X500
#define ev_mprRcvAddrCmd                (u16)(ev_mprMsgbegin + 3) //参数：TMtMPAddr

//X500发送码流
//X500码流发送地址, RTP, RTCP, 此时消息方向 T300E--> X500 
//X500码流接收RTCP地址, BackRTCP  此时消息方向 X500-->T300E
#define ev_mprSendAddrCmd               (u16)(ev_mprMsgbegin + 4) //参数：TMtMPAddr


//编解码功能函数
// 设置编码码参数
//ev_mprSetVEncParamCmd
#define ev_mprCodecVideoEncodeParamCmd  (u16)(ev_mprMsgbegin + 51) //参数：EmTpCodecComponent +  TTPMtVideoEncodeParameter 

//设置动态载荷 
#define ev_mprCodecDynamicPayloadCmd    (u16)(ev_mprMsgbegin + 52) //参数： EmTpCodecComponent ：编解码器类型  + u8 动态载荷值 

//设置秘钥
#define ev_mprCodecEncryptKeyCmd        (u16)(ev_mprMsgbegin + 53) //参数：EmTpCodecComponent + TTpEncryptKey

//设置解码参数
#define ev_mprCodecVideoDecodeParamCmd  (u16)(ev_mprMsgbegin + 54) //参数：EmTpCodecComponent +  EmTpLostPackageRestore + EmTpVideoFormat

//调整帧率
#define ev_mprAdjustFrameRate_Cmd	    (u16)(ev_mprMsgbegin + 55) //参数：EmTpCodecComponent + u8

//调整分辨率
#define ev_mprAdjustVidRes_Cmd          (u16)(ev_mprMsgbegin + 56) //参数：EmTpCodecComponent + u32 宽 + u32 高

//FlowCtrl
#define ev_mprFlowCtrl_Cmd              (u16)(ev_mprMsgbegin + 57) //参数：	TTpCodecComponent  + u16 码率

//设置码流发送地址
#define ev_mprSetSendAddrCmd            (u16)(ev_mprMsgbegin + 58) //参数： TTpCodecComponent + BOOL TRUE 添加新发送地址， FALSE删除发送地址 + TIPTransAddr RTP发送目的地址 + TIPTransAddr RTCP发送目的地址

//开始编解码
#define ev_mprCodecStartCmd	            (u16)(ev_mprMsgbegin + 59) //参数：TTpCodecComponent

//停止编解码
#define ev_mprCodecStopCmd              (u16)(ev_mprMsgbegin + 60) //参数：TTpCodecComponent

//Fec    
#define ev_mprSetFecInfoCmd             (u16)(ev_mprMsgbegin + 61) //参数：  TTPFecInfo

//请求关键帧
#define ev_mprFastUpdate_Cmd            (u16)(ev_mprMsgbegin + 62) //参数：  TTpCodecComponent

//设置网络MTU
#define ev_mprCfgSetMTUCmd              (u16)(ev_mprMsgbegin + 63) //参数：u32

//能力作假，超过1080 30则为1080 30    
#define ev_mprSetFakeCapacityCmd        (u16)(ev_mprMsgbegin + 64) //参数： BOOL bUseFakeCapacity

//图像切边
#define ev_mprSetVidSrcCutLinesCmd      (u16)(ev_mprMsgbegin + 65) //参数：TTPVidSrcCutLines 第三个参数未用

//编码加黑边，裁边，不等比缩放
#define ev_mprSetVidEncResizeModeCmd    (u16)(ev_mprMsgbegin + 66) //参数： EmVidEncResizeMode 

//将码率降低一个比率，debug配置项
#define ev_mprCodecBitRateDecsRatioCmd  (u16)(ev_mprMsgbegin + 67) //参数： u8 m_byBitRateDecsRatio + u8 m_byBitRateDecsRatioForIPHead

//只有亮度，对比，饱和，只有解码有效 ，目前非双流有效
#define ev_mprCodecImageAdjustParamCmd  (u16)(ev_mprMsgbegin + 68) //参数：TTPImageAdjustParam 

//自环测试
#define ev_mprLoopbackTestCmd           (u16)(ev_mprMsgbegin + 69) //参数：TTPInterFaceTestInfo

//质量增强
#define ev_mprSetEncQualityEnhanceCmd   (u16)(ev_mprMsgbegin + 70) //参数： BOOL

//非VGA类信号输出制式
#define ev_mprCfgHDResOutputInd         (u16)(ev_mprMsgbegin + 71) //参数：u32 参照宏定义 MT_HD_1080p_24

//VGA类信号输出制式
#define ev_mprCfgHDVideoFrmInd          (u16)(ev_mprMsgbegin + 72) //参数： u32 参照宏定义 MT_HD_VGA_60

//设置丢包重传
#define ev_mprCodecLostPackResendCmd    (u16)(ev_mprMsgbegin + 73) //参数： TTPLostPackResend 

//看本地远端，静态图片双流等
#define ev_mprSetPIPModCmd              (u16)(ev_mprMsgbegin + 74) //参数：	TTPPIPMod

//看本地
#define ev_mprViewLocalPIP_Cmd          (u16)(ev_mprMsgbegin + 75) //参数：BOOL 本地画中画是否开启

//编码器发送静态图片
#define ev_mprSendPictureCmd            (u16)(ev_mprMsgbegin + 76) //参数： BOOL bSend

//状态图标	
#define ev_mprSetIcon                   (u16)(ev_mprMsgbegin + 77) //参数：	TTpIconInfo

//ftp信息
#define ev_mprFtpInfoOpreateCmd         (u16)(ev_mprMsgbegin + 78) //参数：u8(0:台标 1：横幅) + TFtpFileInfo + u32 消息序号（同步用）

#define ev_mprFtpInfoOpreateInd         (u16)(ev_mprMsgbegin + 79) //参数：u8(0:台标 1：横幅) + u32 消息序号（同步用）+  s32返回值（参考CNMP_ERR_SUCCESS）

//台标
#define ev_mprSetLogo_Cmd               (u16)(ev_mprMsgbegin + 80) //参数：TTPLogoParam + BOOL(ftp是否启用下载) + TFtpFileInfo + u32 消息序号（同步用）

//横幅
#define ev_mprSetBanner_Cmd	            (u16)(ev_mprMsgbegin + 81) //参数：TTPBannerParam + BOOL(ftp是否启用下载) + TFtpFileInfo + u32 消息序号（同步用）

//快照
#define ev_mprSetSnapShotCmd            (u16)(ev_mprMsgbegin + 82) //参数：EmTpSnapShotType + u8 + u8 + TFtpFileInfo + u32 消息序号（同步用）

//快照返回通知 
#define ev_mprSetSnapShotInd            (u16)(ev_mprMsgbegin + 83) //参数：EmTpSnapShotType + u8 + u8 + BOOL(成功失败)+ u32 消息序号（同步用）

//选择视频源
#define ev_mprVideoSourceSelCmd         (u16)(ev_mprMsgbegin + 84) //参数： EmTPVideoType 视频类型 + EmTPMtVideoPort 视频端口 + u8 DVIMode（0:HDMI,1:Ypbpr,2:VGA）

//双流输入端口切换结果回应
#define ev_mprSelDualInputPort_Ind      (u16)(ev_mprMsgbegin + 85) //参数：BOOL 切换结果 + EmVgaType 切换后的演示源输入类型 + EmVgaSwitchResult切换结果

//检测视频源信号
#define ev_mprCodecVideoInputCmd        (u16)(ev_mprMsgbegin + 86) //参数：无，主要是检测编码器是否有视频源图像，启动定时检测，无图像时，发送静态图片图片

#define ev_mprCodecVideoInputInd        (u16)(ev_mprMsgbegin + 87) //参数：BOOL 编码器是否有信号

//请求编解码信息
#define ev_mprCodecPackStatCmd          (u16)(ev_mprMsgbegin + 88) //参数：u32 消息序号（同步用）

//请求编解码器统计信息
#define ev_mprCodecPackStatInd          (u16)(ev_mprMsgbegin + 89) //参数：TMPCodecPackStat(音频功率不用填写，T300E自己填写音频功率) + u32 消息序号（同步用）

//丢包等统计
#define ev_mprCodecLostPackCmd	        (u16)(ev_mprMsgbegin + 90) //参数： BOOL m_bSetLostTimer

//丢包状态通知
#define ev_mprCodecLostPackInd          (u16)(ev_mprMsgbegin + 91) //参数：u32  丢包数 + u32  包总数

//时间同步
#define ev_mprTimeSyncCmd               (u16)(ev_mprMsgbegin + 92) //参数：TOspTimeInfo

//文件出传输
#define ev_mprFileTransCmd              (u16)(ev_mprMsgbegin + 93) //参数：u8(0:台标 1：横幅) + TMPFileTransInfo


//以下消息暂时不用
//设置码流发送地址
//#define ev_mprCodecSendAddrCmd          (u16)(ev_mprMsgbegin + 77) //参数：EmTpCodecComponent + TIPTransAddr RTP发送目的地址  + TIPTransAddr RTCP发送目的地址 + TIPTransAddr RTCP接收地址

//设置自还地址
//#define ev_mprCodecLoopAddrCmd          (u16)(ev_mprMsgbegin + 76) //参数： TTpCodecComponent + TTPCnMediaTransPort  接收地址  + BOOL   TRUE 添加地址，FALSE 删除地址

//修改码流接收地址
//#define ev_mprModifyRecvAddrCmd         (u16)(ev_mprMsgbegin + 81) //参数： EmTpCodecComponent + TIPTransAddr RTP接收地址 + TIPTransAddr RTCP接收地址 + TIPTransAddr RTCP发送目的地址

//设置码流接收地址
//#define ev_mprCodecRecvAddrCmd          (u16)(ev_mprMsgbegin + 82) //参数：EmTpCodecComponent + TIPTransAddr RTP接收地址 + TIPTransAddr RTCP接收地址 + TIPTransAddr RTCP发送目的地址

//设置本地转发地址
//#define ev_mprCodecLocalAddrCmd         (u16)(ev_mprMsgbegin + 83) //参数：TTpCodecComponent + TTPCnMediaTransPort

//待机			
//#define ev_mprCodecDspSleepCmd          (u16)(ev_mprMsgbegin + 90) //参数：

//唤醒
//#define ev_mprCodecDspWakeupCmd         (u16)(ev_mprMsgbegin + 91) //参数：   

// 待机状态
//#define ev_mprCodecDspSleepStateInd     (u16)(ev_mprMsgbegin + 95) //参数： BOOL
  
//编码器发送静态图片通知回应， bSend为TRUE，主要用来关闭打开的ftp服务
//#define ev_mprSendPictureInd            (u16)(ev_mprMsgbegin + 71) //参数： BOOL bSend + TFtpFileInfo + u32 消息序号（同步用）+ s32返回值（参考CNMP_ERR_SUCCESS）

//发送关键帧
//#define ev_mprSndKeyFrameReq           (u16)(ev_mprMsgbegin + 72) //参数：TTpCodecComponent

//台标
//#define ev_mprSetLogo_Ind               (u16)(ev_mprMsgbegin + 99) //参数：TTPLogoParam + TFtpFileInfo + u32 消息序号（同步用） + s32返回值（参考CNMP_ERR_SUCCESS）

//横幅
//#define ev_mprSetBanner_Ind	            (u16)(ev_mprMsgbegin + 100) //参数：TTPBannerParam + TFtpFileInfo + u32 消息序号（同步用）+ s32返回值（参考CNMP_ERR_SUCCESS）

//编码器视频源状态
//#define ev_mprGetVidSrcStatusCmd        (u16)(ev_mprMsgbegin + 63) CNS业务已经不触发此消息了 //参数：EmTpCodecComponent + BOOL 是否正在切换视频源

//#define ev_mprGetVidSrcStatusInd        (u16)(ev_mprMsgbegin + 102) //参数：EmTpCodecComponent + BOOL 是否正在切换视频源 + BOOL 编码器是否有信号


#endif // _CN_MPREMOTEMGR_EVENT_H
