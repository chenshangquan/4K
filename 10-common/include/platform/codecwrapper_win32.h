/* CodecLib.h - Codec API Header */ 

/* Copyright(C) 2001-2002 KDC, All rights reserved. 

*/

#ifndef __CODECWRAPPER_WIN32_H_
#define __CODECWRAPPER_WIN32_H_

#include "KdvDef.h"
#include "kdvtype.h"
#include "kdvmedianet.h"
#include <windows.h>
#include <vector>
using namespace std;
//////////////////////////////////////////////////////////////////////////
#define CODEC_NO_ERROR              (u16)0//无错
#define CODEC_ERROR_BASE            (u16)10000//
#define ERROR_CODEC_UNKNOWN	        (u16)10000//不知名的编解码器错误 
#define ERROR_CODEC_PARAM           (u16)(CODEC_ERROR_BASE + 1)//参数错误;  
#define ERROR_DEC_DRAW_HDC	        (u16)(CODEC_ERROR_BASE + 2)//解码器画图窗口DC错误
#define ERROR_DEC_DRAW_DIBOPEN      (u16)(CODEC_ERROR_BASE + 3)//解码器画图对象打开错误
#define ERROR_DEC_DRAW_DIBBEGIN     (u16)(CODEC_ERROR_BASE + 4)//解码器画图格式错误
#define ERROR_DEC_DRAW_CLEARWINDOW  (u16)(CODEC_ERROR_BASE + 5)//解码器清屏错误
#define ERROR_DEC_ICOPEN            (u16)(CODEC_ERROR_BASE + 6)//解码器打开解码驱动错误
#define ERROR_DEC_DECOMPRESSBEGIN   (u16)(CODEC_ERROR_BASE + 7)//解码器设置解码驱动格式错误
#define ERROR_DEC_SETTIMER          (u16)(CODEC_ERROR_BASE + 8)//解码器设置解码定时器错误
#define ERROR_DEC_NO_VIDEO          (u16)(CODEC_ERROR_BASE + 9)//解码器没有创建视频
#define ERROR_DEC_SOCKET_CALLBACK   (u16)(CODEC_ERROR_BASE + 10)//解码器设置网络事件回调错误
#define ERROR_DEC_SOCKET_CREATE     (u16)(CODEC_ERROR_BASE + 11)//解码器创建网络套接字错误
#define ERROR_DEC_NO_AUDIO          (u16)(CODEC_ERROR_BASE + 12)//解码器没有创建音频 
#define ERROR_DEC_WAVEOPEN          (u16)(CODEC_ERROR_BASE + 13)//解码器不能打开声卡*
#define ERROR_DEC_MIXEROPEN         (u16)(CODEC_ERROR_BASE + 14)//解码器不能打开声卡音量控制
#define ERROR_DEC_WAVEPREHEADER     (u16)(CODEC_ERROR_BASE + 15)//解码器不能设置音频播放头
#define ERROR_DEC_WAVEWRITE         (u16)(CODEC_ERROR_BASE + 16)//解码器不能向声卡写音频数据
#define ERROR_DEC_WAVE_ENCOPEN      (u16)(CODEC_ERROR_BASE + 17)//解码器不能打开音频解码器*
#define ERROR_DEC_WAVE_ENCPREHEADER (u16)(CODEC_ERROR_BASE + 18)//解码器不能设置音频解码头
#define ERROR_DEC_WAVE_ENCCONVERT   (u16)(CODEC_ERROR_BASE + 19)//解码器音频解码错误
#define ERROR_DEC_WAVESTART         (u16)(CODEC_ERROR_BASE + 20)//解码器开始音频播放错误
#define ERROR_DEC_WAVESTOP          (u16)(CODEC_ERROR_BASE + 21)//解码器停止音频播放错误
#define ERROR_DEC_MIXER_SETVOLUME   (u16)(CODEC_ERROR_BASE + 22)//解码器设置音量出错
#define ERROR_DEC_MIXER_GETVOLUME   (u16)(CODEC_ERROR_BASE + 23)//解码器获取音量出错
#define ERROR_DEC_MIXERMUTE         (u16)(CODEC_ERROR_BASE + 24)//解码器设置静音出错
#define ERROR_DEC_AUDIOOUT_EXIT     (u16)(CODEC_ERROR_BASE + 25)//解码器音频线程退出出错
#define ERROR_DEC_HARDCREATE        (u16)(CODEC_ERROR_BASE + 26)//解码器创建硬件解码器失败
#define ERROR_DEC_CREATE            (u16)(CODEC_ERROR_BASE + 27)//解码器创建出错 
#define ERROR_DEC_NEW               (u16)(CODEC_ERROR_BASE + 28)//对象生成出错
#define ERROR_DEC_SETAUDIO_ADDR     (u16)(CODEC_ERROR_BASE + 29)//解码器设置音频地址错误  
#define ERROR_DEC_AUDIO_LEN         (u16)(CODEC_ERROR_BASE + 30)//音频编解码的数据长度不正确
#define ERROR_DEC_NO_MASK           (u16)(CODEC_ERROR_BASE + 31)//既不是软件解码也不是硬件解码
#define ERROR_SOCKOBJ_NULL          (u16)(CODEC_ERROR_BASE + 32)//网络接收对象不存在
#define ERROR_DEC_NET_INVALIDPARAM  (u16)(CODEC_ERROR_BASE + 33)//无效的网络接收参数 
#define EROOR_DEC_NO_IMPLEMENT      (u16)(CODEC_ERROR_BASE + 34)//此功能还不支持 
#define ERROR_DEC_SETSTATE          (u16)(CODEC_ERROR_BASE + 35)//解码器设置解码驱动状态错误

#define ERROR_ENC_CAPWIN            (u16)(CODEC_ERROR_BASE + 100)//编码器创建捕获窗口出错
#define ERROR_ENC_CAPDRIVER         (u16)(CODEC_ERROR_BASE + 101)//编码器没有发现捕获卡
#define ERROR_ENC_DIBOPEN           (u16)(CODEC_ERROR_BASE + 102)//编码器画图对象打开错误
#define ERROR_ENC_DRAWHDC           (u16)(CODEC_ERROR_BASE + 103)//编码器画图窗口打不开
#define ERROR_ENC_ICOPEN            (u16)(CODEC_ERROR_BASE + 104)//编码器编码对象打开出错
#define ERROR_ENC_DRAWPOS           (u16)(CODEC_ERROR_BASE + 105)//编码器得到画图位置出错
#define ERROR_ENC_DIBBEGIN          (u16)(CODEC_ERROR_BASE + 106)//编码器设置画图格式出错
#define ERROR_ENC_GET_VIDEOBMP      (u16)(CODEC_ERROR_BASE + 107)//编码器得到图像格式出错
#define ERROR_ENC_SET_VIDEOBMP      (u16)(CODEC_ERROR_BASE + 108)//编码器设置图像格式出错
#define ERROR_ENC_GET_CAPSET        (u16)(CODEC_ERROR_BASE + 109)//编码器得到捕获设置出错
#define ERROR_ENC_SET_CAPSET        (u16)(CODEC_ERROR_BASE + 110)//编码器设置捕获设置出错
#define ERROR_ENC_SET_AUDIOFORMATE  (u16)(CODEC_ERROR_BASE + 111)//编码器设置音频捕获格式出错
#define ERROR_ENC_STREAMOPEN        (u16)(CODEC_ERROR_BASE + 112)//编码器打开音频编码对象出错
#define ERROR_ENC_PREHEADER         (u16)(CODEC_ERROR_BASE + 113)//编码器准备音频编码头出错
#define ERROR_ENC_MIXEROPEN         (u16)(CODEC_ERROR_BASE + 114)//编码器创建控制音量对象出错
#define ERROR_ENC_MIXER_SETVOLUME   (u16)(CODEC_ERROR_BASE + 115)//编码器设置音量出错
#define ERROR_ENC_MIXER_GETVOLUME   (u16)(CODEC_ERROR_BASE + 116)//编码器得到音量出错
#define ERROR_ENC_ALREADY           (u16)(CODEC_ERROR_BASE + 117)//编码器状态已经存在
#define ERROR_ENC_STOPCAP           (u16)(CODEC_ERROR_BASE + 118)//编码器无法停止捕获
#define ERROR_ENC_SETSTATE          (u16)(CODEC_ERROR_BASE + 119)//编码器设置编码参数出错
#define ERROR_ENC_ENCBEGIN          (u16)(CODEC_ERROR_BASE + 120)//编码器设置编码帧格式
#define ERROR_ENC_SETTIMER          (u16)(CODEC_ERROR_BASE + 121)//编码器设置定时器出错
#define ERROR_ENC_STOPVIDEOENC      (u16)(CODEC_ERROR_BASE + 122)//编码起停止视频编码出错
#define ERROR_ENC_NO_SETPARAM       (u16)(CODEC_ERROR_BASE + 123)//编码器没有设置参数
#define ERROR_ENC_STOPAUDIOENC      (u16)(CODEC_ERROR_BASE + 124)//编码器音频编码出错
#define ERROR_ENC_CREATESOCK        (u16)(CODEC_ERROR_BASE + 125)//编码器设置当地地址出错
#define ERROR_ENC_STOPSENDVIDEO     (u16)(CODEC_ERROR_BASE + 126)//编码器停止发送视频出错
#define ERROR_ENC_STOPSENDAUDIO     (u16)(CODEC_ERROR_BASE + 127)//编码器停止发送音频出错
#define ERROR_ENC_AUDIOENC          (u16)(CODEC_ERROR_BASE + 128)//编码器音频转换错误
#define ERROR_ENC_NO_CREATE         (u16)(CODEC_ERROR_BASE + 129)//编码器创建不成功  
#define ERROR_ENC_SOCK_INIT         (u16)(CODEC_ERROR_BASE + 130)//编码器网络套接字不是2.2版
#define ERROR_ENC_STARTCAP          (u16)(CODEC_ERROR_BASE + 131)//编码器无法开始捕获
#define ERROR_ENC_CAP_WIDTH         (u16)(CODEC_ERROR_BASE + 132)//编码器捕获帧太宽
#define ERROR_DRAW_FORMATE          (u16)(CODEC_ERROR_BASE + 133)//画图格式不支持
#define ERROR_HARDENC_FORMATE       (u16)(CODEC_ERROR_BASE + 134)//硬件不支持的画图格式
#define ERROR_ENC_CAP_FORMATE       (u16)(CODEC_ERROR_BASE + 135)//采集格式和编码格式不匹配
#define ERROR_ENC_NEW               (u16)(CODEC_ERROR_BASE + 136)//对象生成出错
#define ERROR_ENC_INVALID_PARAM     (u16)(CODEC_ERROR_BASE + 137)//无效的参数
#define ERROR_ENC_CREATE_EVENT      (u16)(CODEC_ERROR_BASE + 138)//不能创建事件 
#define EROOR_ENC_NO_IMPLEMENT      (u16)(CODEC_ERROR_BASE + 139)//此功能还不支持 
#define ERROR_ENC_GETSTATE          (u16)(CODEC_ERROR_BASE + 140)//编码器得到编码参数出错
#define ERROR_DECENC_CREATE_THREAD  (u16)(CODEC_ERROR_BASE + 141)//不能创建线程

#define ERROR_ENC_CAP_DESKTOP_FORMAT    (u16)(CODEC_ERROR_BASE + 142)//要求的编码器桌面捕获格式还不支持
#define ERROR_ENC_CREATE_DESKTOP_MEMDC  (u16)(CODEC_ERROR_BASE + 143)//创建桌面内存dc失败
#define ERROR_ENC_CAP_DESKTOP_WIDTH     (u16)(CODEC_ERROR_BASE + 144)//编码器捕获桌面分辨率高于当前桌面实际分辨率
#define ERROR_ENC_CAP_DESKTOP_BITCOUNT  (u16)(CODEC_ERROR_BASE + 145)//编码器捕获桌面位深高于当前桌面实际位深
#define ERROR_ENC_INVILAD_FILE      (u16)(CODEC_ERROR_BASE + 146)//提供的文件无效
#define ERROR_ENC_OPERATE_FILE     (u16)(CODEC_ERROR_BASE + 147)//文件编码器对指定的文件操作失败
/*=======================================常量、宏与结构的定义=================================*/

#ifdef _KDV_CODEC_DLL_
#define MEDIA_API _declspec(dllexport)
#else
#define MEDIA_API _declspec(dllimport)
#endif

#define 	CAMERAPARAM_HUE				0
#define 	CAMERAPARAM_WHITEBALANCE	1
#define 	CAMERAPARAM_CONTRAST		2
#define 	CAMERAPARAM_SATURATION		3
#define 	CAMERAPARAM_SHARPNESS		4

#define CAP_YUV_FORMAT_MJPG			(u8)0
#define CAP_YUV_FORMAT_I420			(u8)1
#define CAP_YUV_FORMAT_RGB24		(u8)2
#define CAP_YUV_FORMAT_YUV2			(u8)3

/*声音模式 mp3*/
#define	 AUDIO_MODE_WORST        (u8)0/*最差*/
#define	 AUDIO_MODE_BAD          (u8)1/*差  */
#define	 AUDIO_MODE_NORMAL       (u8)2/*一般*/
#define	 AUDIO_MODE_FINE         (u8)3/*好  */
#define	 AUDIO_MODE_BEST         (u8)4/*最好*/
//G.711
#define  AUDIO_MODE_PCMA         (u8)5//a law
#define  AUDIO_MODE_PCMU         (u8)6//u law 
//G.723
#define AUDIO_MODE_G723_6        (u8)7 
#define AUDIO_MODE_G723_5        (u8)8
//G.728
#define AUDIO_MODE_G728			 (u8)9 
//G.722
#define AUDIO_MODE_G722			 (u8)10 
//G.729
#define AUDIO_MODE_G729			 (u8)11 
//G.7221 24k
#define AUDIO_MODE_G7221_24		 (u8)12 
//adpcm
#define AUDIO_MODE_ADPCM		 (u8)13 
//aaclc
#define AUDIO_MODE_AACLC_32      (u8)14
#define AUDIO_MODE_AACLD_32_SINGLE      (u8)15
#define AUDIO_MODE_AACLC_32_SINGLE	(u8)16
//G.7221 32K
#define AUDIO_MODE_G7221_32			(u8)17
//G.7221 48k
#define AUDIO_MODE_G7221_48			(u8)18
#define AUDIO_MODE_G719				(u8)19

//ld 双声道？
#define AUDIO_MODE_AACLD_32_UNDEF	(u8)20
//iBLC
#define AUDIO_MODE_IBLC         (u8)21
//iSac
#define AUDIO_MODE_ISAC_16         (u8)22
#define AUDIO_MODE_ISAC_32         (u8)23
//OPUS
#define AUDIO_MODE_OPUS         (u8)24

#define  CAP_CAMERA_ONLY         (u8)0x02 //      CAMERA视频数据捕获
#define  CAP_DESKTOP_ONLY        (u8)0x04 //	    DESKTOP桌面视频数据捕获
#define  CAP_FILE_AV_BOTH		 (u8)0x08 //以指定文件（目前支持kdc录像机产生的asf文件）的
#define MAX_DEV_NAME_LEN		  256

#define PIC_ENCODE_JPEG			 (u8)1     //抓取图片，可选保存的图片格式
#define PIC_ENCODE_BMP			 (u8)2     // 

#define MAX_FILE_PATH_LEN        256
/*编码器参数*/
typedef struct tagInitVidEncoder
{  
	HWND    m_hwVideoPreview;
	u32		m_dwCapType;	//CAP_CAMERA_ONLY or CAP_DESKTOP_ONLY
	s32		m_nCpuID;		  //默认0 不绑定 
}TInitVidEncoder;

/*视频解码器参数*/
typedef struct tagInitVidDecoder
{
	HWND    m_hwPlayVideo;
	s32		m_nCpuID;		  //默认0 不绑定 
	//默认的文件源 not impl yet
	wchar_t*	m_pchFileName;
	u8		m_byFileNameSize;
}TInitVidDecoder;

/*音频解码器参数*/
typedef struct tagInitAudDecoder
{
	s32		m_nCpuID;		   //默认0 不绑定 
	u32   m_dwReserved;         
}TInitAudDecoder;

typedef struct tagInitAudEncoder
{
	s32		m_nCpuID;		    //默认0 不绑定 
	u32		m_dwReserved;
}TInitAudEncoder;

/*视频编码参数*/
typedef struct VideoEncParam
{
	u8  m_byEncType;   /*图像编码类型*/
    u8  m_byRcMode;    /*图像压缩码率控制参数*/
    u16 m_byMaxKeyFrameInterval;/*I帧间最大P帧数目*/
    u8  m_byMaxQuant;  /*最大量化参数(1-31)*/
    u8  m_byMinQuant;  /*最小量化参数(1-31)*/
    u16 m_wBitRate;    /*编码比特率(Kbps,1K=1024)*/
	u32 m_dwSndNetBand;/*网络发送带宽(单位:Kbps)*/   
	u16 m_wEncVideoWidth;//编码设置图像宽
	u16 m_wEncVideoHeight;//编码设置图像高
	u8	m_byFrameRate;  /*帧率(default:25)*/
	u8  m_byEncLevel;	//编码能力级别 0:LV_QUALITY_PRIOR,1:LV_SPEED_PRIOR,2:LV_HPSINGLE_PRIOR,3:LV_HPMULTE_PRIOR
}TVideoEncParam;
typedef struct VideoCapParam
{
	u16	wVideoWidth; //视频捕获图像宽度(default:640)
	u16	wVideoHeight;//视频捕获图像高度(default:480)
	u8	byFrameRate; //视频捕获帧率(default:25)   若帧率>=1，则 m_byFrameRate ＝ fps, 若帧率<1，则 m_byFrameRate ＝ spf  
	BOOL32 bUseSpecifyFormat; //默认false，媒控默认使用mjpeg
	u8  byFormat;    // CAP_YUV_FORMAT_MJPG CAP_YUV_FORMAT_I420 等 
}TVideoCapParam;


typedef struct TDevNameInfo
{
	wchar_t m_achDevName[MAX_DEV_NAME_LEN];
	wchar_t m_achDevGUID[MAX_DEV_NAME_LEN];   //若重名，此字符串不一致
}TDevNameInfo;
/*编码器状态*/
typedef struct KdvEncStatus
{
	BOOL32 			m_bVideoSignal;			/*是否有视频信号*/
	BOOL32	        m_bVideoCapStart; /*是否开始视频捕获*/
	BOOL32			m_bAudioCapStart; /*是否开始音频捕获*/
	BOOL32			m_bVideoEncStart; /*是否开始视频编码*/
	BOOL32			m_bAudioEncStart; /*是否开始音频编码*/
	BOOL32			m_bNetSndVideoStart;/*是否开始视频发送*/
	BOOL32			m_bNetSndAudioStart;/*是否开始音频发送*/

	TVideoEncParam	m_tVideoEncParam; /*视频编码参数*/
	u8            m_byAudioEncParam;/*音频编码模式*/
	u8			  m_byAudEncMediaType; /*音频编码媒体类型*/	
	TMnetNetParam     m_tVideoSendAddr; /*视频发送地址*/
	TMnetNetParam     m_tAudioSendAddr; /*音频发送地址*/
	u32           m_dwSetEncParam; //设置硬件编码参数次数
	u32           m_dwVideoSend;   //已发送的视频包数
	u32           m_dwAudioSend;   //已发送的音频包数

}TKdvEncStatus;


/*编码器统计信息*/
typedef struct KdvEncStatis
{
    u8   m_byVideoFrameRate;/*视频帧率*/
    u32  m_dwVideoBitRate;  /*视频码流速度*/
    u32  m_dwAudioBitRate;  /*语音码流速度*/
    u32  m_dwVideoPackLose; /*视频丢帧数*/
    u32  m_dwVideoPackError;/*视频错帧数*/
    u32  m_dwAudioPackLose; /*语音丢帧数*/
    u32  m_dwAudioPackError;/*语音错帧数*/
	u32  m_wAvrVideoBitRate;   /*1分钟内视频编码平均码率*/
	u32	 m_wAvrAudioBitRate;   /*1分钟内语音编码平均码率*/
}TKdvEncStatis;


/*解码器状态*/
typedef struct KdvDecStatus
{
	BOOL32	m_bVideoDecStart;/*是否开始视频解码*/
	BOOL32	m_bAudioDecStart;/*是否开始音频解码*/
	BOOL32	m_bRcvVideoStart;/*是否开始视频接收*/
	BOOL32	m_bRcvAudioStart;/*是否开始音频接收*/
	TMnetNetParam   m_tAudioRcvAddr;/*音频当地地址*/
	TMnetNetParam   m_tVideoRcvAddr;/*视频当地地址*/
	BOOL32	m_bAudioOutThread;/*是否声音播放线程存活*/
	BOOL32	m_bVideoCodecThread;/*是否Video解码线程存活*/
	u32   m_dwAudioDecType;     //音频解码类型
	u32   m_dwVideoDecType;     //视频解码类型
}TKdvDecStatus;

/*解码器统计信息 */
typedef struct KdvDecStatis
{
	u8	  m_byVideoFrameRate;/*视频解码帧率*/
	u32	  m_dwVideoBitRate;   /*视频解码码率*/
	u32	  m_dwAudioBitRate;   /*语音解码码率*/
	u32   m_dwVideoRecvFrame;/*收到的视频帧数*/
	u32   m_dwAudioRecvFrame;/*收到的语音帧数*/
	u32   m_dwVideoLoseFrame;/*丢失的视频帧数*/
	u32   m_dwAudioLoseFrame;/*丢失的语音帧数*/
    u16   m_wVideoLoseRatio;//视频丢失率,单位是% 	
	u16   m_wAudioLoseRatio;//音频丢失率,单位是% 	
	u32   m_dwPackError;/*乱帧数*/ 
	u32   m_dwIndexLose;/*序号丢帧*/
	u32   m_dwSizeLose; /*大小丢帧*/
	u32   m_dwFullLose; /*满丢帧*/	
	u32   m_wAvrVideoBitRate;   /*1分钟内视频解码平均码率*/
	u32	  m_wAvrAudioBitRate;   /*1分钟内语音解码平均码率*/
	BOOL32 m_bVidCompellingIFrm;  /*视频强制请求I帧*/								  
	u32   m_dwDecdWidth;	/*码流的宽*/
	u32   m_dwDecdHeight;   /*码流的高*/
	u16   LastVideoBitRate; //上次统计的码率
    u32   GetDecoderStatisnum;//码率不变则该值递增
	u32	  m_dwVidPackLoseNum;//视频丢包数，080905
	u16   m_wVidPhyPackLoseRatio;//重传前的视频丢包率
	u16   m_wVidPackLoseRatio;//重传后的视频丢包率
	u16   m_wAudPhyPackLoseRatio;//重传前的音频丢包率
	u16   m_wAudPackLoseRatio;//重传后的音频丢包率	
	u32   m_dwTotalPackNum; //接收的总包数
}TKdvDecStatis; 


typedef struct
{
	u32 dwErrorId;
}TErrorDescription;


struct TDecoderRef
{
	HWND			m_hwPlayVideo;
	s32				m_nVideoCpuId;
	s32				m_nAudioCpuId;
	TErrorDescription	m_tErrorDescription;
};

struct TDecoderStatus
{
	KdvDecStatus	m_kdsDecoderStatus;
	KdvDecStatis	m_kdsDecoderStatics;	
};

struct TEncoderRef
{
	HWND			m_hPreWnd;
	s32				m_nVideoCpuId;
	s32				m_nAudioCpuId;
	TErrorDescription	m_tErrorDescription;
};

struct TEncoderStatus
{
	KdvEncStatus	m_kdsEncStatus;
	KdvEncStatis	m_kdsEncStatics;
};

//XXX 韦国华　callback encoded audio/video frames for recording purpose
typedef void (*PVIDEOCALLBACK)(u8* pMp4Data, s32 nMp4Data, s32 nCodecID, s16 nWidth, s16 nHeight, u32 dwContext);
typedef void (*PVIDEOI420CALLBACK)(u8* pData, s32 nData, s16 nWidth, s16 nHeight, u32 dwContext);
typedef void (*PAUDIOCALLBACK)(u8 buAudioMode, const u8 *pBuf, s32 nSize, u32 dwContext);
typedef void (*PAUDIOPCMCALLBACK)(u8 *pBuf, s32 nSize, u32 dwSampleRate, u32 dwBitWidth, u32 dwChannel, u32 dwContext);
typedef void (*PAUDIOCAPERRCALLBACK)(void* pParam);
typedef void (*PAUDIOCAPDEVICECHANGE)(u32 dwContext, const vector<TDevNameInfo>& vecInsertlist, const vector<TDevNameInfo>& vecRemoveList);
typedef void (*PVOICECHECK)(CHAR cMode, u32 dwContext);
typedef void (*PDRAWCALLBACK)(HDC hDrawDC, u32 dwContext);
typedef void (*PSTATICPICCALLBACK)(u8 *pBuf, u32 dwSize, BITMAPINFOHEADER* pHead, u32 dwParam);


typedef struct tagVoiceCheck
{
	s32			m_nBGTime;
	s32			m_nThreshold;
	PVOICECHECK	m_pCallBack;
	u32         m_dwContext;
}TVoiceCheck;

typedef void (*PGETAUDIOPOWER)(u8 byAudioPower, u32 dwContext);
typedef void (*PVIDEODEVICECHECK)(u32 dwContext, const vector<TDevNameInfo>& vecInsertlist, const vector<TDevNameInfo>& vecRemoveList);
typedef void (*PGETDISKCHECK)(u8 byAlarmLevel, u32 dwContext);


//台标融入码流的相关信息设置
typedef struct tagTranspDColor
{
	u8 RColor;          //R背景
	u8 GColor;          //G背景
	u8 BColor;          //B背景	
	u8 u8Transparency;  //透明度(0表示全透明，255表示不透明，1~254表示部分透明)
}TTranspColor;

typedef struct tagAddLogoParam
{
    float fXPosRate;		//宽度比例，xpos = 底图宽*fXPosRate
    float fYPosRate;		//高度比例，ypos = 底图宽*fYPosRate
    u32   dwLogoBgWidth;	//参考底图的宽
    u32   dwLogoBgHeight;	//参考底图的高
    TTranspColor tBackBGDColor;    
}TAddLogoParam;

typedef struct
{
    wchar_t aLogoBmpPath[MAX_FILE_PATH_LEN];	
	u32     dwLogoPathLen;
    TAddLogoParam tLogoParam;
}TFullLogoParam;

typedef struct MediaSDKEnvirVar
{
    u32 m_dwProductVer;     //MediaSDK运行环境的产品的版本信息，默认为V1R2环境(T2_V1R2),可选HD
    u32 m_dwProductInfo;    //MediaSDK运行环境的特殊版本信息
    u32 m_dwOSVer;          //操作系统版本号
    u32 m_dwRservered;      //保留字段
	
}TMediaSDKEnvirVar;

enum enZoomMode
{
	EN_ZOOM_FILLBLACK = 0,//加黑边
	EN_ZOOM_CUT,//裁边
	EN_ZOOM_SCALE//不等比拉伸
};

//mediasdk 全局初始化
MEDIA_API u16 MediaSDKInitial();
//mediasdk 全局析构在所有encoder decoder 释放后调用
MEDIA_API u16 MediaSDKUninitial();
//mediasdk 设置配置文件路径
MEDIA_API u16 SetMediaSdkConfigPath(wchar_t* pszConfigPath);
class	CVidEncWrapper;
class	CAudEncWrapper;
class	CVidDecWrapper;
class	CAudDecWrapper;
class MEDIA_API CKdvEncoder

{
public:
    CKdvEncoder();
    virtual ~CKdvEncoder();
public:
	
    //初始化音视屏模块，如果不调用，默认后面的相关接口都无效
	u16		InitialVideoEncoder(const TInitVidEncoder& tEncoderInitParam);
	u16		InitialAudioEncoder(const TInitAudEncoder& tEncoderInitParam);
	u16		GetEncoderStatus(TKdvEncStatus &tKdvEncStatus);/*获取编码器状态*/ 		
	u16		GetEncoderStatis(TKdvEncStatis &tKdvEncStatis );/*获取编码器的统计信息*/

	//////////////////////////////////////////////////////////////////////////audio
	//获取采集设备名 + 数量
	void    RefreshVidCapDevList(vector<TDevNameInfo>& tOutDevList, u32& dwDevNum);

	void	RefreshAudCapDevList(vector<TDevNameInfo>& tOutDevList, u32& dwDevNum);	
    u16		SetVoiceCheck(BOOL32 bCheck,const TVoiceCheck *ptVoiceCheck);/*语音功率监测*/	
	u16		StartAudioCap();
	u16		StopAudioCap();
	u16		StartAudioEnc();/*开始压缩语音*/
	u16		StopAudioEnc(); /*停止压缩语音*/
	u16		SetAudioEncParam(u8 byAudioMode, 
							 u16 wAudioDuration = 0); /*设置语音压缩参数*/
	u16		GetAudioEncParam(u8& byAudioEncParam, 
							 u16& wAudioDuration);/*得到语音压缩参数*/
	u16		SetAudioCallBack(PAUDIOCALLBACK pAudioCallBack, u32 dwContext);
	u16		SetAudioCapCallBack(PAUDIOCAPERRCALLBACK pAudioCallBack, u32 dwContext); //音频采集设备打开失败时回调
	u16		SetAudioCaptureDeviceChangeCB(PAUDIOCAPDEVICECHANGE pAudCapDevChangeCB, u32 dwContext); // 设置音频输入热插拔检测的回调
	// 设置 获取输入音频功率 的回调
	u16		SetInputAudioPowerCB(PGETAUDIOPOWER pGetInputAudioPowerCB, u32 dwContext);
	u16		GetAudioMute( BOOL32& bMute );     // 是否哑音 [zhuyr][4/20/2005]
	u16		SetAudioMute( BOOL32 bMute );     //设置是否静音
	//设置自动增益
	//bEnable：TRUE表示开启自动增益，FALSE关闭。返回值0表示设置成功，其他失败
	u16		SetAudioCapAutoGain(BOOL32 bEnable);
	//bEnable：TRUE表示开启自动增益，FALSE关闭。返回值0表示获取成功，其他失败
	u16		GetAudioCapAutoGain(BOOL32 &bEnable);
	u16		SetAudioCapTest(BOOL32 bActive); //音频采集诊断 ---taoz
	u16		SetAudioSoftVolume(u8 byVolume ); /*设置采集音量 非系统*/	
	u16		GetAudioSoftVolume(u8 &byVolume );/*获取采集音量*/
	u16		SetAudioVolume(u8 byVolume ); /*设置采集音量 系统*/	
	u16		GetAudioVolume(u8 &byVolume );/*获取采集音量*/
	//////////////////////////////////////////////////////////////////////////video
    u16		SetPreviewHwnd( HWND hPrevWnd );
	u16		SetDeskDrawHwnd( HWND hDeskDrawWnd );
	//选择视频源 byDeviceID 为摄像头重名后的ID区分号
    u16		SelectVideoSource(const TVideoCapParam  *ptVideoCapParam, const wchar_t *pszDevName = NULL, const wchar_t *pszDevGUID = NULL);//选择视频源
	u16     GetCurVidCapDev(TDevNameInfo &tDevNameInfo);/*获取当前视频采集设备信息*/
	// byCamParamType 为
	//0-----CAMERAPARAM_Hue;1-----CAMERAPARAM_WhiteBalance;2-----CAMERAPARAM_Brightness;3-----CAMERAPARAM_Contrast;4-----CAMERAPARAM_Saturation；5-----CAMERAPARAM_Sharpness
	//bAuto 为TRUE时使用驱动自动调节
	u16		ChangeCameraParam(u8 byCamParamType, u32 dwVal, BOOL32 bAuto = FALSE);
	u16		GetCameraParam(u8 byCamParamType, u32& dwVal, BOOL32& bAuto);
	u16		GetDefaultCameraParam(u8 byCamParamType, u32& dwMin, u32& dwMax, u32& dwDefaultVal, u32& dwStep);
	u16		SelectAudioSource(const wchar_t *pszDevName = NULL, const wchar_t *pszGUIDName = NULL);//选择音频源
	u16     GetCurAudCapDev(TDevNameInfo &tDevNameInfo);/*获取当前音频采集设备信息*/
    u16		SetVideoIcon( BOOL32 bEnable );//bEnable,TRUE为设置，FALSE不设。
    u16		SaveAsPic(const wchar_t* pszFileName, u8 byEncodeMode);
	// 设置视频插拔检测的回调
	u16		SetVideoDeviceCheckCB(PVIDEODEVICECHECK pVideoDeviceCheckCB, u32 dwContext);
	// 设置 台标融入码流 的开关
	u16		SetAddLogoIntoEncStream(TFullLogoParam *ptLogoSetting);
	// 设置 编码器的本地预览 的开关
	u16		ShowPreview(BOOL32 bPreview);
    u16		StartVideoCap();/*开始采集图像*/
    u16		StopVideoCap(); /*停止采集图像*/
    u16		SetVideoEncParam(const TVideoEncParam *ptVideoEncParam );/*设置视频编码参数*/
    u16		GetVideoEncParam(TVideoEncParam &tVideoEncParam );       /*得到视频编码参数*/
	//设置采集到编码缩放策略
	u16     SetVidCapToEncZoomPolicy(enZoomMode emZoomMode);
    u16		StartVideoEnc();/*开始压缩图像*/
    u16		StopVideoEnc(); /*停止压缩图像*/
	u16		SetFastUpdate(BOOL32 bIsNeedProtect = TRUE);     /*设置FastUpdate，MediaCtrl在75帧内编一个I帧发送*/
	u16		SendStaticPicture(BOOL32 bSend, wchar_t* pszFileName);
	void	GrabPic(HWND hWnd);
	//////////////////////////////////////////////////////////////////////////medianet
	/*设置图像的网络重传参数*/
	u16		SetNetFeedbackVideoParam(u16 wBufTimeSpan, BOOL32 bRepeatSnd = FALSE);
	u16		SetNetFeedbackAudioParam(u16 wBufTimeSpan, BOOL32 bRepeatSnd = FALSE);
	//该功能需要把发送重传打开, 如果没打开，将自动打开。
	u16		SetNetAudioResend(BOOL32 bReSend);
	u16     SetAudNetSndBand(u32 dwNetBand);//设置音频发送带宽
	u16		SetNetSndVideoParam(const TMnetNetParam *ptNetSndParam);/*设置图像的网络传送参数*/	
	u16		SetNetSndAudioParam(const TMnetNetParam *ptNetSndParam);/*设置语音的网络传送参数*/
	
	//设置音频参数
	//pszEndPointId - 终端的id, 当前仅支持e164号 dwparam IdLen - 终端id的长度 dwStreamId - 流id
	u16     SetAudioSendId(const s8* pszEndPointId, u32 dwIdLen, u32 dwStreamId);//设置发送端的id
	u16     GetAudioSendId(s8* pszEndPointId, u32* pdwIdLen, u32* pdwStreamId);//获取发送端的id
	//1.使能打洞功能并设置用于打洞的网络发送参数 2.停止打洞功能并删除相应网络参数
	u16     AudioSendEnableKeepAlive(BOOL32 bEnable, const TMnetNetParam *ptKeepAliveParam);
	//设置RTCP状态
	u16     SetAudioRtcpStatus(RTCPSTATUS status);
	//是否剥掉音频RTP扩展头
	u16     AudioEnableRtpExStrip(BOOL32 bEnable);

	//设置视频参数
	//pszEndPointId - 终端的id, 当前仅支持e164号 dwparam IdLen - 终端id的长度 dwStreamId - 流id
	u16     SetVideoSendId(const s8* pszEndPointId, u32 dwIdLen, u32 dwStreamId);//设置发送端的id
	u16     GetVideoSendId(s8* pszEndPointId, u32* pdwIdLen, u32* pdwStreamId);//获取发送端的id
	//1.使能打洞功能并设置用于打洞的网络发送参数 2.停止打洞功能并删除相应网络参数
	u16     VideoSendEnableKeepAlive(BOOL32 bEnable, const TMnetNetParam *ptKeepAliveParam);
	//设置RTCP状态
	u16     SetVideoRtcpStatus(RTCPSTATUS status);
	//是否剥掉视频RTP扩展头
	u16     VideoEnableRtpExStrip(BOOL32 bEnable);
	//使能/关闭动态带宽检测 dwMaxRate:最大编码码率(单位kbps) dwMinRate:最小编码码率 dwStartRate：初始编码码率
	u16		ResetBwe(BOOL32 bEnable, u32 dwMaxRate, u32 dwMinRate, u32 dwStartRate);
	//获取动态带宽检测结果 pNumber:接收者个数 pReceivers:带宽检测结果 pRevision:接收组版本
	u16		GetBweStatus(u32* pNumber, TBweReceiver* pReceivers, u32* pRevision);
    u16		StartSendVideo(int  dwSSRC = 0);/*开始发送图像*/	
    u16		StopSendVideo(); /*停止发送图像*/
    u16		StartSendAudio(int  dwSSRC = 0);/*开始发送语音*/	
    u16		StopSendAudio(); /*停止发送语音*/	
	//视频是否使用前向纠错
	u16		SetVidFecEnable(BOOL32 bEnableFec);
	//设置fec的切包长度
	u16		SetVidFecPackLen(u16 wPackLen);
	//是否帧内fec
	u16		SetVidFecIntraFrame(BOOL32 bIntraFrame);
	//设置fec算法 FEC_MODE_RAID5
	u16		SetVidFecMode(u8 byAlgorithm);
	//设置fec的x包数据包 + y包冗余包
	u16		SetVidFecXY(s32 nDataPackNum, s32 nCrcPackNum);

	//音频是否使用前向纠错
	u16		SetAudFecEnable(BOOL32 bEnableFec);
	//设置fec的切包长度
	u16		SetAudFecPackLen(u16 wPackLen);
	//是否帧内fec
	u16		SetAudFecIntraFrame(BOOL32 bIntraFrame);
	//设置fec算法 FEC_MODE_RAID5
	u16		SetAudFecMode(u8 byAlgorithm);
	//设置fec的x包数据包 + y包冗余包
	u16		SetAudFecXY(s32 nDataPackNum, s32 nCrcPackNum);
	//视频动态载荷的PT值的设定
	u16		SetAudioActivePT(u8 byLocalActivePT, u8 byRemoteActivePT = MEDIA_TYPE_NULL);
	//音频动态载荷的PT值的设定
	u16		SetVideoActivePT(u8 byLocalActivePT, u8 byRemoteActivePT = MEDIA_TYPE_NULL );
	//设置音频编码加密key字串、加密的载荷PT值 以及 解密模式 Aes or Des
	u16		SetAudEncryptKey( s8 *pszKeyBuf, u16 wKeySize, u8 byEncryptMode );
	//设置视频编码加密key字串、加密的载荷PT值 以及 解密模式 Aes or Des
	u16		SetVidEncryptKey( s8 *pszKeyBuf, u16 wKeySize, u8 byEncryptMode ); 
	u16		SetReverseG7221c(BOOL32 bReverse);

	/**************Video*******************/
	//使能加密
	u16     SetVidEnableCrypt( BOOL32 bEnableCrypt, TMnetCryptCfg *ptMnetCryptCfg);
	//初始化加密配置结构体
	u16     SetVidMnetCryptCfgInit(TMnetCryptCfg* ptCfg, BOOL32 send);
	//设置加密用的加密算法
	u16     SetVidMnetCryptCfgSetCipherAlgorithm(TMnetCryptCfg* ptCfg, TMnetCryptDataType tDataType, TMnetCryptAlgoType tAlgorithm);
	//设置认证用的加密算法
	u16     SetVidMnetCryptCfgSetAuthAlgorithm(TMnetCryptCfg* ptCfg, TMnetCryptDataType tDataType, TMnetCryptAlgoType tAlgorithm);
	//设置秘钥类型和秘钥,本接口用于srtp
	u16     SetVidMnetCryptCfgSetMasterKey(TMnetCryptCfg* ptCfg, TMnetCryptDataType tDataType, TMnetCryptKeyType tKeyType, u16 wKeySize, \
		u8* byKey, TMnetCrypKeyLen tKeyLenAuch, TMnetCrypKeyLen tKeyLenCipher);
	//设置加密用的某个通道的加密秘钥长度,用于H235加密,目前仅支持rtp aes加密
	u16     SetVidMnetCryptCfgSetCipherKey(TMnetCryptCfg* ptCfg, TMnetCryptDataType tDataType, u16 wKeySize, u8* byKey);
	//设置加密用的某个通道的认证秘钥长度,用于H235,暂不支持认证
	u16     SetVidMnetCryptCfgSetAuthKey(TMnetCryptCfg* ptCfg, TMnetCryptDataType tDataType, u16 wKeySize, u8* byKey);
	//设置通道的pkt类型
	u16     SetVidMnetCryptCfgSetPkt(TMnetCryptCfg* ptCfg, TMnetCryptDataType tDataType, TMnetCryptPktType tPktType);
	//设置加密用的某个通道的认证tag长度,用于srtp
	u16		SetVidMnetCryptCfgSetAuthTag(TMnetCryptCfg* ptCfg, TMnetCryptDataType tDataType, TMnetCryptTagLen tTagLen);
	//获取视频网络传输开销百分比
	u16     GetVidTransportOverhead(u8 *byPercent);
	//是否启用单线程编码，单slice，解决与部分外厂商对通多slice不能解码问题
	u16     EnableSingleSlice(BOOL32 bEnableSingleSlice);

	/**************Audio******************/
	//使能加密
	u16     SetAudEnableCrypt( BOOL32 bEnableCrypt, TMnetCryptCfg *ptMnetCryptCfg);
	//初始化加密配置结构体
	u16     SetAudMnetCryptCfgInit(TMnetCryptCfg* ptCfg, BOOL32 send);
	//设置加密用的加密算法
	u16     SetAudMnetCryptCfgSetCipherAlgorithm(TMnetCryptCfg* ptCfg, TMnetCryptDataType tDataType, TMnetCryptAlgoType tAlgorithm);
	//设置认证用的加密算法
	u16     SetAudMnetCryptCfgSetAuthAlgorithm(TMnetCryptCfg* ptCfg, TMnetCryptDataType tDataType, TMnetCryptAlgoType tAlgorithm);
	//设置秘钥类型和秘钥,本接口用于srtp
	u16     SetAudMnetCryptCfgSetMasterKey(TMnetCryptCfg* ptCfg, TMnetCryptDataType tDataType, TMnetCryptKeyType tKeyType, u16 wKeySize, \
		u8* byKey, TMnetCrypKeyLen tKeyLenAuch, TMnetCrypKeyLen tKeyLenCipher);
	//设置加密用的某个通道的加密秘钥长度,用于H235加密,目前仅支持rtp aes加密
	u16     SetAudMnetCryptCfgSetCipherKey(TMnetCryptCfg* ptCfg, TMnetCryptDataType tDataType, u16 wKeySize, u8* byKey);
	//设置加密用的某个通道的认证秘钥长度,用于H235,暂不支持认证
	u16     SetAudMnetCryptCfgSetAuthKey(TMnetCryptCfg* ptCfg, TMnetCryptDataType tDataType, u16 wKeySize, u8* byKey);
	//设置通道的pkt类型
	u16     SetAudMnetCryptCfgSetPkt(TMnetCryptCfg* ptCfg, TMnetCryptDataType tDataType, TMnetCryptPktType tPktType);
	//设置加密用的某个通道的认证tag长度,用于srtp
	u16		SetAudMnetCryptCfgSetAuthTag(TMnetCryptCfg* ptCfg, TMnetCryptDataType tDataType, TMnetCryptTagLen tTagLen);
	
protected:
	void	DestroyVideoEncoder();
	void	DestroyAudioEncoder();
    CVidEncWrapper*	m_pcKdvVideoEncoder;
	CAudEncWrapper*	m_pcKdvAudioEncoder;
    TEncoderRef*	m_ptRef;
    TEncoderStatus*	m_ptStatus;	
};





class CKdvVideoDec;
class CKdvAudioDec;
struct TDecoderRef;
struct TDecoderStatus;


typedef struct tagNetRSParam
{
    u16  m_wFirstTimeSpan;	  //第一个重传检测点
	u16  m_wSecondTimeSpan;  //第二个重传检测点
	u16  m_wThirdTimeSpan;   //第三个重传检测点
	u16  m_wRejectTimeSpan;  //过期丢弃的时间跨度
} TNetRSParam;

class MEDIA_API CKdvDecoder

{
public:
    CKdvDecoder();
    virtual ~CKdvDecoder();
	
public:
	u16    InitialVideoDecoder(const TInitVidDecoder& tVidInitParam);
	u16	   InitialAudioDecoder(const TInitAudDecoder& tAudInitParam);
    u16    GetVidDecoderStatus(TKdvDecStatus &tKdvDecStatus );/*获取视频解码器状态*/
	u16    GetAudDecoderStatus(TKdvDecStatus &tKdvDecStatus );/*获取音频解码器状态*/
    u16    GetVidDecoderStatis(TKdvDecStatis &tKdvDecStatis );/*获取视频解码器的统计信息*/	
	u16    GetAudDecoderStatis(TKdvDecStatis &tKdvDecStatis );/*获取音频解码器的统计信息*/	

//////////////////////////////////////////////////////////////////////////audio
	void   RefreshPlayDevList(vector<TDevNameInfo>& tOutDevList, u32& dwDevNum);
	u16	   SelectAudioPlayDev(const wchar_t *pszDevName = NULL, const wchar_t *pszDevGUID = NULL);//选择音频源
	u16    GetCurAudPlyDev(TDevNameInfo &tDevNameInfo);/*获取当前音频播放设备信息*/
	u16    SetAudioSoftVolume(u8 byVolume );  /*设置输出声音算法软条幅音量*/	
	u16    GetAudioSoftVolume(u8 &pbyVolume );/*得到输出声音算法软条幅音量*/
	u16    SetAudioVolume(u8 byVolume );  /*设置输出系统声音音量*/	
	u16    GetAudioVolume(u8 &pbyVolume );/*得到输出系统声音音量*/
	u16    SetAudioMute(BOOL32 bMute);/*设置静音 -- taoz */
	u16    GetAudioMute(BOOL32& bMute);
	u16    SetAudioDecType(u8 byType,u32 dwAudioMode); /*设置声音解码器类型, 只有在开始解码前调用才有效*/
	u16    StartAudioDec();/*开始声音解码*/	
	u16    StopAudioDec(); /*停止声音解码*/	
	u16    SetAudioCallBack(PAUDIOCALLBACK pAudioCallBack, u32 dwContext);//解码前音频数据回调
	u16    SetAudioDecPCMCallBack(PAUDIOPCMCALLBACK pAudioCallBack, u32 dwContext);//解码后音频PCM数据回调
	// 设置 获取输出音频功率 的回调
	u16    SetOutputAudioPowerCB(PGETAUDIOPOWER pGetOutputAudioPowerCB, u32 dwContext);
	//设置aac解码参数 dwSamplePerSecond为采样率 如48000， 32000. dwChannels为单双声道 填 如1, 2
	u16    SetAudioDecParam(u32 dwSamplePerSecond, u32 dwChannels);//音频解码参数设置
	//音频播放测试
	u16    SetAuditoPlyTest(BOOL32 bActive);
	//////////////////////////////////////////////////////////////////////////video
    u16    StartVideoDec();/*开始图像解码*/
    u16    StopVideoDec(); /*停止图像解码*/
	u16    ClearWindow();  /*清屏*/
	u16    FreezeVideo();  /*视频冻结*/
	u16    UnFreezeVideo();/*取消视频冻结*/
	u16    SetVideoDecI420CallBack(PVIDEOI420CALLBACK pVideoI420CallBack, u32 dwContext);//解码后视频I420数据回调
	//设置解码作图后调用的回调函数  [zhuyr][4/25/2005]
	u16    SetDrawCallBack(PDRAWCALLBACK pFun, u32 dwParam);
	u16    SetPlayHwnd( HWND hPlayWnd, BOOL32 bSaveLastFrame = FALSE);
	/*当pDrawWnd无效时，重调此接口，参数为空.*/
    u16	   SaveAsPic(const wchar_t* pszFileName, u8 byEncodeMode);
	//设置是否只解关键帧 TRUE为设置，FALSE为取消
	u16    SetOnlyKeyFrame(BOOL32 bKeyFrame);
	/////////////////////////////////////////////////////////////////////////medianet
    u16    StartRcvVideo();/*开始网络接收图像*/
    u16    StopRcvVideo(); /*停止网络接收图像*/
    u16    StartRcvAudio();/*开始网络接收声音*/	
    u16    StopRcvAudio(); /*停止网络接收声音*/	
	u16    SetVideoNetRcvParam(const TMnetNetParam *ptLocalNetParam );/*设置图像的网络接收参数*/	
	u16    SetAudioNetRcvParam(const TMnetNetParam *ptLocalNetParam );/*设置语音的网络接收参数*/

	//视频是否使用前向纠错
	u16	   SetVidFecEnable(BOOL32 bEnableFec);

	//设置音频参数
	//pszEndPointId - 终端的id, 当前仅支持e164号 dwparam IdLen - 终端id的长度 dwStreamId - 流id
	u16    SetAudioRcvId(const s8* pszEndPointId, u32 dwIdLen, u32 dwStreamId);//设置接收端的id
	u16    GetAudioRcvId(s8* pszEndPointId, u32* pdwIdLen, u32* pdwStreamId);  //获取接收端的id
	//1.使能打洞功能并设置用于打洞的网络发送参数 2.停止打洞功能并删除相应网络参数
	u16    AudioRcvEnableKeepAlive(BOOL32 bEnable, const TMnetNetParam *ptKeepAliveParam);
	//设置RTCP状态
	u16    SetAudioRtcpStatus(RTCPSTATUS status);
	//设置视频参数
	//pszEndPointId - 终端的id, 当前仅支持e164号 dwparam IdLen - 终端id的长度 dwStreamId - 流id
	u16    SetVideoRcvId(const s8* pszEndPointId, u32 dwIdLen, u32 dwStreamId);//设置接收端的id
	u16    GetVideoRcvId(s8* pszEndPointId, u32* pdwIdLen, u32* pdwStreamId);//获取接收端的id
	//1.使能打洞功能并设置用于打洞的网络发送参数 2.停止打洞功能并删除相应网络参数
	u16    VideoRcvEnableKeepAlive(BOOL32 bEnable, const TMnetNetParam *ptKeepAliveParam);
	//设置RTCP状态
	u16    SetVideoRtcpStatus(RTCPSTATUS status);
	u16    ResetBwe(BOOL32 bEnable);//使能/关闭动态带宽检测
	u16    SetMaxDelay(u8 policy, u32 softlimit, u32 hardlimit);//设置最大接收延迟及播放策略
	/*设置图像的网络重传参数*/
	u16    SetNetFeedbackVideoParam(BOOL32 bRepeatSnd = FALSE);
	u16    SetNetFeedbackAudioParam(BOOL32 bRepeatSnd = FALSE);
	
	/*解码器发送两路码流，一路发往Map或者win32解码绘制，一路发往网络, 参数NULL,则关闭后一路，并作相应套节子释放*/
	u16    SetVidDecDblSend(const TMnetNetParam *ptNetSndVideoParam, u16 wBitRate = 4<<10);
	u16    SetAudDecDblSend(const TMnetNetParam *ptNetSndAudioParam); 
	//设置 H.263+/H.264 等动态视频载荷的 Playload值
	u16    SetVideoActivePT( u8 byRmtActivePT, u8 byRealPT );
	//设置 视频解码key字串 以及 解密模式 Aes or Des
    u16    SetVidDecryptKey(s8 *pszKeyBuf, u16 wKeySize, u8 byDecryptMode); 
	//设置 动态音频载荷的 Playload值
	u16    SetAudioActivePT( u8 byRmtActivePT, u8 byRealPT );

	u16	   SetVideoActivePT( TMapSet tMapSet );
	u16	   SetAudioActivePT( TMapSet tMapSet );

	//设置 音频解码key字串 以及 解密模式 Aes or Des
    u16    SetAudDecryptKey(s8 *pszKeyBuf, u16 wKeySize, u8 byDecryptMode); 
	u16    SetReverseG7221c(BOOL32 bReverse );//设置g7221c反转
	void   GrabPic(HWND hWnd);

	//音频是否使用前向纠错
	u16	   SetAudFecEnable(BOOL32 bEnableFec);

	//设置解码显示缩放策略
	u16    SetVidDecZoomPolicy(enZoomMode emZoomMode);

	/***********Video**************/
	//使能加密
	u16     SetVidEnableCrypt( BOOL32 bEnableCrypt, TMnetCryptCfg *ptMnetCryptCfg);
	//初始化加密配置结构体
	u16     SetVidMnetCryptCfgInit(TMnetCryptCfg* ptCfg, BOOL32 send);
	//设置加密用的加密算法
	u16     SetVidMnetCryptCfgSetCipherAlgorithm(TMnetCryptCfg* ptCfg, TMnetCryptDataType tDataType, TMnetCryptAlgoType tAlgorithm);
	//设置认证用的加密算法
	u16     SetVidMnetCryptCfgSetAuthAlgorithm(TMnetCryptCfg* ptCfg, TMnetCryptDataType tDataType, TMnetCryptAlgoType tAlgorithm);
	//设置秘钥类型和秘钥,本接口用于srtp
	u16     SetVidMnetCryptCfgSetMasterKey(TMnetCryptCfg* ptCfg, TMnetCryptDataType tDataType, TMnetCryptKeyType tKeyType, u16 wKeySize, \
		u8* byKey, TMnetCrypKeyLen tKeyLenAuch, TMnetCrypKeyLen tKeyLenCipher);
	//设置加密用的某个通道的加密秘钥长度,用于H235加密,目前仅支持rtp aes加密
	u16     SetVidMnetCryptCfgSetCipherKey(TMnetCryptCfg* ptCfg, TMnetCryptDataType tDataType, u16 wKeySize, u8* byKey);
	//设置加密用的某个通道的认证秘钥长度,用于H235,暂不支持认证
	u16     SetVidMnetCryptCfgSetAuthKey(TMnetCryptCfg* ptCfg, TMnetCryptDataType tDataType, u16 wKeySize, u8* byKey);
	//设置通道的pkt类型
	u16     SetVidMnetCryptCfgSetPkt(TMnetCryptCfg* ptCfg, TMnetCryptDataType tDataType, TMnetCryptPktType tPktType);
	//设置加密用的某个通道的认证tag长度,用于srtp
	u16		SetVidMnetCryptCfgSetAuthTag(TMnetCryptCfg* ptCfg, TMnetCryptDataType tDataType, TMnetCryptTagLen tTagLen);

	/*****************Audio**************/
	//使能加密
	u16     SetAudEnableCrypt( BOOL32 bEnableCrypt, TMnetCryptCfg *ptMnetCryptCfg);
	//初始化加密配置结构体
	u16     SetAudMnetCryptCfgInit(TMnetCryptCfg* ptCfg, BOOL32 send);
	//设置加密用的加密算法
	u16     SetAudMnetCryptCfgSetCipherAlgorithm(TMnetCryptCfg* ptCfg, TMnetCryptDataType tDataType, TMnetCryptAlgoType tAlgorithm);
	//设置认证用的加密算法
	u16     SetAudMnetCryptCfgSetAuthAlgorithm(TMnetCryptCfg* ptCfg, TMnetCryptDataType tDataType, TMnetCryptAlgoType tAlgorithm);
	//设置秘钥类型和秘钥,本接口用于srtp
	u16     SetAudMnetCryptCfgSetMasterKey(TMnetCryptCfg* ptCfg, TMnetCryptDataType tDataType, TMnetCryptKeyType tKeyType, u16 wKeySize, \
		u8* byKey, TMnetCrypKeyLen tKeyLenAuch, TMnetCrypKeyLen tKeyLenCipher);
	//设置加密用的某个通道的加密秘钥长度,用于H235加密,目前仅支持rtp aes加密
	u16     SetAudMnetCryptCfgSetCipherKey(TMnetCryptCfg* ptCfg, TMnetCryptDataType tDataType, u16 wKeySize, u8* byKey);
	//设置加密用的某个通道的认证秘钥长度,用于H235,暂不支持认证
	u16     SetAudMnetCryptCfgSetAuthKey(TMnetCryptCfg* ptCfg, TMnetCryptDataType tDataType, u16 wKeySize, u8* byKey);
	//设置通道的pkt类型
	u16     SetAudMnetCryptCfgSetPkt(TMnetCryptCfg* ptCfg, TMnetCryptDataType tDataType, TMnetCryptPktType tPktType);
	//设置加密用的某个通道的认证tag长度,用于srtp
	u16		SetAudMnetCryptCfgSetAuthTag(TMnetCryptCfg* ptCfg, TMnetCryptDataType tDataType, TMnetCryptTagLen tTagLen);

protected:
	void   DestroyVideoDecoder();
	void   DestroyAudioDecoder();
	CVidDecWrapper*		m_pcKdvVideoDecoder;
	CAudDecWrapper*		m_pcKdvAudioDecoder;
	TDecoderRef*		m_ptDecRef;
	TDecoderStatus*		m_ptDecStatus;
};

class CAVCapabilityList;

class MEDIA_API CAVCapCheck

{
public:
    CAVCapCheck();
    ~CAVCapCheck();
public:
	BOOL32 CheckAudInCap();
	BOOL32 CheckVidInCap();
	BOOL32 CheckAudOutCap();
	BOOL32 CheckVidOutCap();
	BOOL32 CheckAudEncCap(u8 byMediaType);
	BOOL32 CheckVidEncCap(u8 byMediaType);
	BOOL32 CheckAudDecCap(u8 byMediaType);
	BOOL32 CheckVidDecCap(u8 byMediaType);	

private:
	CAVCapabilityList *m_ptCAVCapList;
};

typedef struct tagRecoderParam
{
	wchar_t m_aFilePath[MAX_FILE_PATH_LEN];
	u32	   m_dwFilePathLen;
	BOOL32 m_bIsLocal;
	BOOL32 m_bHasAudio;
	BOOL32 m_bHasAuxVideo; //仅对远端录像有用
	BOOL32 m_bRecreate;    //默认设为TRUE
	BOOL32 m_bStartAfterCreated;
	u32	   m_dwReserved;
}TRecoderParam;



//设置媒体TOS值 nType类型0:全部 1:音频 2:视频 3: 数据
MEDIA_API	int SetMediaTOS(int nTOS, int nType);
MEDIA_API	int GetMediaTOS(int nType);

//录像机
MEDIA_API void*	CreateRecorder(const TRecoderParam& tRecoderParam);
MEDIA_API u16	CloseRecorder(void* pRecorderInst);
MEDIA_API u16	PauseRecoder(void* pRecorderInst);
MEDIA_API u16	ResumRecoder(void* pRecorderInst);
MEDIA_API u16   GetRecorderFilePath(void* pRecorderInst, wchar_t* pszPath, s32 nPath);
MEDIA_API u16   SetRecoderDiskCheckCB(PGETDISKCHECK pGetDiskCheckCB, u32 dwContext); 
//设置录像空间检测磁盘告警监控的分区参数 *pszPartition 分区名 dwAlarmLevel1  一级告警值 dwAlarmLevel2  二级告警值
MEDIA_API u16   SetRecoderDiskCheckPartitionAlarm(const wchar_t *pszPartition, u32 dwAlarmLevel1, u32 dwAlarmLevel2);

#endif /*__CODECLIB_H*/
