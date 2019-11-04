#ifndef  _ASF_TRANS_HELPMACRO_
#define _ASF_TRANS_HELPMACRO_


#include "vfw.h"

#define SAFE_DEL(p) { delete p; p = NULL; }
#define SAFE_ARR_DEL(p) { delete[] p; p = NULL; }

#define BEGIN_NAME_SPACE	\
	namespace CodeTrans{

#define END_NAME_SPACE }

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#define MAX_FRAME_WIDTH        (s32)1024//
#define MAX_FRAME_HEIGHT       (s32)768//

#define GUID_WMMEDIASUBTYPE_KDM4  {0x344D444B, 0x0000, 0x0010, {0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71}}
#define GUID_WMMEDIASUBTYPE_KDM2  {0x324D444B, 0x0000, 0x0010, {0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71}}
#define GUID_WMMEDIASUBTYPE_KDH1  {0x3148444B, 0x0000, 0x0010, {0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71}}
#define GUID_WMMEDIASUBTYPE_KDH3  {0x3348444B, 0x0000, 0x0010, {0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71}}
#define GUID_WMMEDIASUBTYPE_KDH4  {0x3448444B, 0x0000, 0x0010, {0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71}}

typedef struct tagFOURCC
{
	u32 dwFOURCC;
	u8  byBitCount;
}TFOURCC;

const TFOURCC g_tFrameFormat[3]=
{
	{ BI_RGB, 24 },
    { mmioFOURCC('U','Y','V','Y'), 16},
	{ mmioFOURCC('I','4','2','0'), 12},
};

const TFOURCC g_tEncType[5]=
{
	{ mmioFOURCC('k','d','m','4'), 24 },
    { mmioFOURCC('k','d','h','1'), 24},
	{ mmioFOURCC('k','d','h','3'), 24},
	{ mmioFOURCC('k','d','h','4'), 16},
	{ mmioFOURCC('k','d','m','2'), 24},
};


typedef struct tagVideoEncType
{
	u32  m_dwFOURCC;
	u8   m_byBitCount;
	GUID m_subtype;
}TVideoEncType;

const TVideoEncType g_tVideoEncTypeArr[5]=
{
	{ mmioFOURCC('K','D','M','4'), 24, GUID_WMMEDIASUBTYPE_KDM4},
	{ mmioFOURCC('K','D','H','1'), 24, GUID_WMMEDIASUBTYPE_KDH1},
	{ mmioFOURCC('K','D','H','3'), 24, GUID_WMMEDIASUBTYPE_KDH3},
	{ mmioFOURCC('K','D','H','4'), 24, GUID_WMMEDIASUBTYPE_KDH4},
	{ mmioFOURCC('K','D','M','2'), 24, GUID_WMMEDIASUBTYPE_KDM2},
};



BEGIN_NAME_SPACE

/*视频编码参数*/
typedef struct VideoEncParam
{
	u8  m_byEncType;   /*图像编码类型*/
    u8  m_byRcMode;    /*图像压缩码率控制参数*/
    u16  m_byMaxKeyFrameInterval;/*I帧间最大P帧数目*/
    u8  m_byMaxQuant;  /*最大量化参数(1-31)*/
    u8  m_byMinQuant;  /*最小量化参数(1-31)*/
    u8  m_byReserved1; /*保留*/
	u8  m_byQcMode; /*图像质量码率控制参数,质量优先或者速度优先*/
    u8  m_byQI;
    u8  m_byQP;
    u16  m_wBitRate;    /*编码比特率(Kbps)*/
    u16  m_wReserved4;  /*保留*/		

	public:
		VideoEncParam()
		{
			memset(this, 0, sizeof(VideoEncParam) );
		}
}TVideoEncParam;


//--comment: 以下结构摘自MediaSDK,详情请参阅相应的文档

//Video Encode Param
typedef struct tagEncParamVideo
{
	u8            m_byEncType;
	HIC			  m_hIC; 
	BITMAPINFO    m_bmpEnc;
	s32           m_nBufSize;
	u8*           m_pEncBuf;
    u8            m_byRcMode;    /*图像压缩码率控制参数*/
    u16           m_wMaxKeyFrameInterval;/*I帧间最大P帧数目*/
    u8            m_byMaxQuant;  /*最大量化参数(1-31)*/
    u8            m_byMinQuant;  /*最小量化参数(1-31)*/
    u8			  m_byQPMin;        // 最小量化步长(1-51)
    u8			  m_byQPMax;        // 最大量化步长(1-51)
    u16           m_wBitRate;    /*编码比特率(Kbps)*/
    u16           m_wReserved4;  /*保留*/
	public:
		tagEncParamVideo()
		{
			memset( this, 0, sizeof(tagEncParamVideo) );
		}
}TEncParamVideo;

//编码器参数结构
typedef struct
{
	s32 rc_mode;
	s32 bitrate;
	s32 quality;
	s32	quant;
	s32 rc_buffersize;
	s32 fourcc_used;
	s32 quant_type;
	s32 max_key_interval;
	s32 min_quant;
	s32 max_quant;
	s32 bidirectional;
	s32 deinterlacing;
	s32 adapt_quant;
	s32 cpu;
	s32 max_vbv_delay;
	s32 interlaced_coding;
	s32 top_field_first;
	s32 alternative_scan;
	s32 save;
} CONFIG_MP4V;

typedef struct {
    s32	FrameFormat;
    s32	BitRate;
    s32	IFramePeriod;
    s32	IntraFrame;
    s32	MinQUANT;
    s32	MaxQUANT;
    s32	HasRTPPacketInfo;
    s32 nFrameRate;
}TH261EncParam;


typedef struct
{
    u32 fccType;      //必须为小写"vidc"
    u32 fccHandler;   //必须为小写"kdh1"
    TH261EncParam EncParam;
}CONFIG_H261;      //叫State是为了同VfW的文档一致


typedef struct 
{
	s32 bRateControl;			// 编码器是否使用码率控制，1－采用，0－不采用，建议采用
	s32 BitsPerSecond;			// 码率，单位是bit/s，一般可以在100,000~1000,000之间
	
	s32 PRate;				 // I帧的间隔，一般为12
	
	s32 QI;                  // I帧的初始量化参数
	s32 QP;                  // P帧的初始量化参数
	
	s32 min_quantizer;
	s32 max_quantizer;	
	
	s32 sourceFormat;		 // 1 : sub_CIF; 2 : CIF; 3 : cif;  4 : 4cif 
	
}H263_CONFIG;


typedef struct 
{
	s32 rc_mode;			// 编码器是否使用码率控制，1－采用，0－不采用，建议采用
	s32 bitrate;			// 码率，单位是bit/s，一般可以在100,000~1000,000之间
	s32 quality;			// 1:质量优先， 0：速度优先,一般采用1
	
	s32 fourcc_used;
	
	s32 max_key_interval;    // I帧的间隔，一般为12或15，0表示只有第一帧是I帧
	
	s32 QPMin;                  // 最小量化步长(1-51)
	s32 QPMax;                  // 最大量化步长(1-51)
		
	s32 nCodecMode;			 // 0:RTP包编码方式（默认）   1:帧编码方式
	
}H264_CONFIG;

typedef struct 
{
	int BitsPerSecond;		// 码率，单位是bit/s，一般可以在100,000~1000,000之间
	
	int PRate;				// I帧的间隔，一般为12
	
	int min_quantizer;
	int max_quantizer;
	
}MPG2_CONFIG;

END_NAME_SPACE

#endif