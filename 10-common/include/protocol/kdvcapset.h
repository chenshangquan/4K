#ifndef _H323CAPSET_H
#define _H323CAPSET_H
#include "kdvtype.h"
#include "protocolcommonpublic.h"
#include "kdvcommon.h"
#include "kdvsipcommon.h"

#define SIP_ADPT_AUDIO_DEFAUL_SAMPLERATE 8000       ///< sip audio default sample rate
#define SIP_ADPT_AUDIO_OPUS_DEFAUL_SAMPLERATE 48000       ///< sip audio opus default sample rate
#define SIP_ADPT_AUDIO_G7221_DEFAUL_SAMPLERATE 32000       ///< sip audio g7221 default sample rate
#define SIP_ADPT_AUDIO_DEFAULT_PACKTIME 30          ///< sip audio default pack time
#define SIP_ADPT_FECC_DEFAULT_BITRATE	64          ///< sip fecc default bitrate

#define SIP_ADPT_VIDEO_DEFAUL_SAMPLERATE 90000       ///< sip video default sample rate

#define MAX_CAPTABLE_SIZE	(u16)128					///< max 128 (in H245 standard document captable size should be 1~256 but now we only use 128)
#define MAX_ALTCAP_NUM      MAX_CAPTABLE_SIZE		///< max 64
#define MAX_SIMUCAP_NUM     (u16)16					///< max 16 (Codian为13)
#define MAX_DESCAP_NUM      (u16)5					///< max 5 (抓包发现都是1，很少有2以上)
#define MAXBITRATE_H261     (u16)19200				///< max bitrate of h261,unit is 100bps
#define MAXBITRATE_H263     (u32)192400				///< max bitrate of h263,unit is 100bps

#define MAX_AAC_CAP_NUM					2                       ///< MAX_AAC_CAP_NUM
#define MAX_FLOOR_NUM					5                       ///< MAX_FLOOR_NUM
#define MAX_MEDIA_NUM_PER_FLOOR			5                       ///< MAX_MEDIA_NUM_PER_FLOOR
#define MAX_RED_SECENC_NUM				3						///< max SecEncDynPayloadNum

#define SIP_MAX_AUDIO_STREAM_COUNT 4  ///< sip max audio stream audio
#define SIP_MAX_VIDEO_STREAM_COUNT 4  ///< sip max video stream audio

#define SIP_MAX_MEDIA_NUM (SIP_MAX_VIDEO_STREAM_COUNT*4 + SIP_MAX_AUDIO_STREAM_COUNT*4 +2)  ///< SIP_MAX_VIDEO_STREAM_COUNT + SIP_MAX_AUDIO_STREAM_COUNT + BFCP(1) + FECC(1) + DUAL AUDIO(1) + DUAL VIDEO(1)


#define INVERT_16_BYTES(A)       ((((u16)(A) & 0x00ff) << 8) | \
	(((u16)(A) & 0xff00) >> 8))

#define INVERT_32_BYTES(A)       ((((u32)(A) & 0x000000ff) << 24) | \
	(((u32)(A) & 0x0000ff00) << 8)  | \
	(((u32)(A) & 0x00ff0000) >> 8)  | \
	(((u32)(A) & 0xff000000) >> 24))

/// guzh [9/25/2007] 前向纠错类型
enum emFECType
{
    emFECNone		= 0x00,          ///< none
	emFECRaid5		= 0x01,          ///< raid5
	emFECRaid6		= 0x02,          ///< raid6
	emFECNonStd		= 0x04           ///< 公司自己的NsmFec, add by shigubin 20130228
};

/// roleLabel 值 [20140829]
enum emH239RoleLabel 
{
	H239Role_NotSupport				= 0,		///< Not support h239
	H239Role_Presentation			= 1,		///< Presentation
	H239Role_Live					= 2,		///< Live
	H239Role_LiveAndPresentation	= 3,		///< both live and Presentation
};

/// the capabilitiy's direction
enum EM_CAPDIRECTION
{
	emCapReceive	= 1,            ///< receive
	emCapTransmit	= 2,		    ///< transmit
	emCapReceiveAndTransmit=3	    ///< both receive and transmit
};

/// sip level
enum EmSipLevel
{
	emSipCounty,             ///< county
	emSipCity,               ///< city
	emSipProvince,           ///< province
	emSipUnKnown = 255,      ///< unknown
};

/// sip cap sign
enum EmSipCapSign
{
	emSipCapBig,                  ///< big
	emSipCapLeft,                 ///< left
	emSipCapSmall = emSipCapLeft, ///< small
	emSipCapRight,                ///< right
	emSipCapEnd = emSipCapRight,  ///< end 
};

/// sip msg type
enum EmSipMsgType
{
	emSipNone,                ///< none
	emSipInvite,              ///< invite
	emSip200OK,               ///< 200ok
	emSipAck,                 ///< ack
};

/// media type
enum EmSipMediaType
{
	emSipMediaNone,        ///< None
	emSipMediaAudio,       ///< Audio
	emSipMediaVideo,       ///< Video
	emSipMediaH224,        ///< H224
	emSipMediaT120,        ///< T120
	emSipMediaBfcp,        ///< Bfcp
};
/// send recv attr
typedef enum 
{
	emSendRecvBegin = 0,  ///< begin
	emSendOnly = 1,       ///< send only
	emRecvOnly = 2,       ///< recv only
	emSendRecv = 3        ///< send and recv
}emSendRecvAttr;

#ifdef WIN32
	#pragma comment( lib, "ws2_32.lib" ) 
	#pragma pack( push )
	#pragma pack( 1 )
	#define window( x )	x
	#ifndef PACKED
		#define PACKED
	#endif
#else
	#include <netinet/in.h>
	#define window( x )
	#if defined(__ETI_linux__)
		#define PACKED
	#else
		#ifdef PACKED
			#undef PACKED
		#endif
	#define PACKED __attribute__ ((packed))	// 取消编译器的优化对齐
	#endif
#endif

/// the base of capability set
struct PROTO_API TKdvCapSet
{
	u32			m_dwSampleRate;      ///< sample rate
	PayloadType	m_emPayloadType;	 ///< payload type
	u16			m_wStaticPayload;	 ///< static payload
	u16			m_wDynamicPayload;	 ///< dynamic payload

protected:
	EM_CAPDIRECTION m_emCapDirection;///< the capabilitiy's direction,not init
public:
	TKdvCapSet()
	{
		Clear();
	}

	void Clear()
	{
		m_emPayloadType		= emPayloadTypeBegin;
		m_dwSampleRate		= SIP_ADPT_AUDIO_DEFAUL_SAMPLERATE;
		m_wDynamicPayload	= 0;
		m_wStaticPayload	= 0;
	}

	/// the get/set PayloadType function
	void SetPayloadType( PayloadType emPt )
	{
        m_emPayloadType = emPt;
	}	
	PayloadType GetPayloadType()
	{
		return m_emPayloadType;
	}
	
	/// the get/set SampleRate function
	void SetSampleRate( u32 dwSampleRate )
	{
        m_dwSampleRate = dwSampleRate;
	}	
	u32 GetSampleRate()
	{
		return m_dwSampleRate;
	}
	
	/// the get/set StaticPayload function
	void SetStaticPayload( u16 wPt )
	{
		m_wStaticPayload = wPt;
	}
	u16 GetStaticPayload()
	{
		return m_wStaticPayload;
	}
	
	/// the get/set DynamicPayload function
	void SetDynamicPayload( u16 wDPt )
	{
		m_wDynamicPayload = wDPt;
	}
	u16 GetDynamicPayload()
	{
		return m_wDynamicPayload;
	}

	/// the get/set CapDirection function
	//Interfaces merged from H.323
    void SetCapDirection(EM_CAPDIRECTION emDirect)
    {
        m_emCapDirection = emDirect;
    }
    EM_CAPDIRECTION GetCapDirection() const
    {
        return m_emCapDirection;
	}
}PACKED;

/// the base of audio capbility set，exclude G.7231
struct PROTO_API TKdvAudioCap : public TKdvCapSet
{
	u8   m_byPackTime;     ///< 每一RTP包的最大时长,单位ms(1-256); 

public:
	TKdvAudioCap():TKdvCapSet()
	{
		m_byPackTime = SIP_ADPT_AUDIO_DEFAULT_PACKTIME;
	}

	void Clear()
	{
		m_byPackTime = SIP_ADPT_AUDIO_DEFAULT_PACKTIME;
		TKdvCapSet::Clear();
	};

	/// the get/set PackTime function
	void SetPackTime(u8 byPackTime)
	{
		m_byPackTime = byPackTime;
	}
	u8  GetPackTime()
	{
		return m_byPackTime;
	}

	/// interfaces of convert the member's order
	void host2net(BOOL32 bhton);
}PACKED;

/// the capbility of G7231
struct PROTO_API TKdvG7231Cap : public TKdvAudioCap
{
	u8				m_byMaxFrameNum;		///< 单包最大的帧数
	BOOL32			m_bSilenceSuppression;	///< 是否静音抑制

public:
	TKdvG7231Cap():TKdvAudioCap()
	{
		m_byMaxFrameNum  = 1;			    ///< 目前我们只支持单帧
		m_bSilenceSuppression = TRUE;
	}

	void Clear()
	{
		m_byMaxFrameNum  = 1;			    ///< 目前我们只支持单帧
		m_bSilenceSuppression = TRUE;	    ///< 我们默认支持静音抑制
		TKdvAudioCap::Clear();
	}

    /// 设置是否支持静音
    void SetIsSilenceSuppression(BOOL32 bSilenceSuppression)
    {
        m_bSilenceSuppression = bSilenceSuppression;
    }
    /// 是否支持静音
	BOOL32 IsSilenceSuppression()
	{
		return m_bSilenceSuppression;
	}
    
    /// 设置每包的最大帧数
	void SetMaxFrameNumPerPack(u8 byMaxFrameNum)
	{
		m_byMaxFrameNum = byMaxFrameNum;
	}
    /// 获取每包的最大帧数
	u8 GetMaxFrameNumPerPack()
	{
		return m_byMaxFrameNum;
	}

	/// interfaces of convert the member's order
	void host2net(BOOL32 bhton)
	{
		s32 nCapDirection = m_emCapDirection;
		if (bhton)
		{
			m_emCapDirection        = (EM_CAPDIRECTION)htonl(nCapDirection);
			m_bSilenceSuppression   = htonl(m_bSilenceSuppression);
		}
		else
		{
			m_emCapDirection        = (EM_CAPDIRECTION)ntohl(nCapDirection);
			m_bSilenceSuppression   = ntohl(m_bSilenceSuppression);
		}
	}
}PACKED;

/// the capbility of G7221
struct PROTO_API TKdvG7221Cap: public TKdvAudioCap
{
	u8  m_byBitRateType;         ///< encode bitrate
	enum emG7221Rate
	{
		emG7221RateNone =  0x00,
		emG7221Rate24   =  0x01,
		emG7221Rate32   =  0x02,
		emG7221Rate48   =  0x04
	};

public:
	TKdvG7221Cap():TKdvAudioCap()
	{
		m_byBitRateType = emG7221Rate24;
		m_dwSampleRate = SIP_ADPT_AUDIO_G7221_DEFAUL_SAMPLERATE;
	}
	
	void Clear()
	{
		TKdvAudioCap::Clear();
    	m_byBitRateType = emG7221Rate24;
		m_dwSampleRate = SIP_ADPT_AUDIO_G7221_DEFAUL_SAMPLERATE;
	};
	
    /// 设置rate
	void SetRateType( u8 byRateType )
	{
		m_byBitRateType = byRateType;
	}
	void OrRateType( emG7221Rate emRateType )
	{
	    m_byBitRateType = (m_byBitRateType | emRateType);
	}

	/// 获取rate
	u8 GetRateType()
	{
		return m_byBitRateType;
	}

	/// set/get bit rate
	void SetBitRate( u32 dwBitRate )
	{
		m_byBitRateType = 0;
		if ( dwBitRate == 48000 )
			m_byBitRateType = emG7221Rate48;
        else if ( dwBitRate == 32000 )
			m_byBitRateType = emG7221Rate32;
        else
			m_byBitRateType = emG7221Rate24;
	}
	u16 GetBitRate()
	{
		if( m_byBitRateType & emG7221Rate48 )
			return 48000;
		else if ( m_byBitRateType & emG7221Rate32 )
			return 32000;
		else 
			return 24000;
	}

	/// interfaces of convert the member's order
	void host2net(BOOL32 bhton)
	{
		/// XXX Why convert CapDirection only rather than all the variants??
		s32 nCapDirection = m_emCapDirection;
		if (bhton)
		{
			m_emCapDirection = (EM_CAPDIRECTION)htonl(nCapDirection);
		}
		else
		{
			m_emCapDirection = (EM_CAPDIRECTION)ntohl(nCapDirection);
		}
	}
}PACKED;

/**
Opus codec
---------------------------------------
supported features are:
  Bitrates from 6 kb/s to 510 kb/s
  Sampling rates from 8 kHz (narrowband) to 48 kHz (fullband)
  Frame sizes from 2.5 ms to 60 ms
  Support for both constant bitrate (CBR) and variable bitrate (VBR)
  Audio bandwidth from narrowband to fullband
  Support for speech and music
  Support for mono and stereo
  Support for up to 255 channels (multistream frames)
  Dynamically adjustable bitrate, audio bandwidth, and frame size
  Good loss robustness and packet loss concealment (PLC)
  Floating point and fixed-point implementation
*/
/// the opus capbility
struct PROTO_API TKdvOpusCap : public TKdvAudioCap
{
	u8              m_byVersion;				///<   version
	u16             m_wMaxPlaybackRate;		///<   a hint about the maximum output sampling rate that the receiver is capable of rendering in Hz.
	u16             m_wSpropMaxCaptureRate;	///<   a hint about the maximum input sampling rate that the sender is likely to produce.

public:
    TKdvOpusCap()
    {
        Clear();
    }
    
    void Clear()
	{
		m_byVersion   = 1;
		m_wMaxPlaybackRate = SIP_ADPT_AUDIO_OPUS_DEFAUL_SAMPLERATE;
		m_wSpropMaxCaptureRate = SIP_ADPT_AUDIO_OPUS_DEFAUL_SAMPLERATE;
		m_dwSampleRate = SIP_ADPT_AUDIO_OPUS_DEFAUL_SAMPLERATE;
	}
    
	/// interfaces of convert the member's order
    void host2net(BOOL32 bhton);


	void SetMaxPlaybackRate( u16 wSampleRate )
	{
		m_wMaxPlaybackRate = wSampleRate;
	}	
	u16 GetMaxPlaybackRate()
	{
		return m_wMaxPlaybackRate;
	}

	void SetSpropMaxCaptureRate( u16 wSampleRate )
	{
		m_wSpropMaxCaptureRate = wSampleRate;
	}	
	u16 GetSpropMaxCaptureRate()
	{
		return m_wSpropMaxCaptureRate;
	}

	/// set/get version
    void SetVersion(u8 byVersion) 
    {
        m_byVersion = byVersion;
    }	
    u8 GetVersion() const
    {
        return m_byVersion;
    }
}PACKED;

/*
telephone-event codec
---------------------------------------
according to RFC2833:
Event  encoding (decimal)
_________________________
0--9                0--9
*                     10
#                     11
A--D              12--15
*/
/// the telephone event capbility
struct PROTO_API TKdvTelephoneEventCap : public TKdvAudioCap
{
	s8 m_achEncoding[256];    ///< the encoding data of telephone event
public:
	TKdvTelephoneEventCap()
	{
		Clear();
		TKdvAudioCap::Clear();
	}

	void Clear()
	{
		memset(m_achEncoding,0,sizeof(m_achEncoding));
		m_dwSampleRate = SIP_ADPT_AUDIO_DEFAUL_SAMPLERATE;
	}
    
	/// set/get event encoding
	void SetEventEncoding(s8* pchEventEncoding)
	{
		if ( NULL != pchEventEncoding && 0 != strlen(pchEventEncoding))
		{
			MEMCPY_CAST(m_achEncoding,pchEventEncoding,strlen(pchEventEncoding));
		}
		
	}
	s8* GetEventEncoding( ) 
	{
		return m_achEncoding;
	}

}PACKED;

///<  red use
typedef struct tagKdvEncodeDescript
{
	PayloadType	m_emPayloadType;    ///< If the media format is less than 96, use the media format value,m_wDynamicPayload=0
	u16			m_wDynamicPayload;
	tagKdvEncodeDescript()
	{
		Clear();
	}
	void Clear()
	{
		m_emPayloadType = emAudioTypeEnd;
		m_wDynamicPayload = 0;
	}
} TKdvEncodeDescript;

///< Red capbility set
struct PROTO_API TKdvRedCap : public TKdvAudioCap
{
	///< channel config
	enum emRedChnlCfg                       
	{
		emChnlCust   = 0,
		emChnl1      = 1,
		emChnl2      = 2,
		emChnl3      = 3,
		emChnl4      = 4,
		emChnl5      = 5,
		emChnl5dot1  = 6,
		emChnl7dot1  = 7
	};
	emRedChnlCfg	m_emChnlCfg;										///< channel config
	u8				m_bySecEncodedNum;									///< the number of secondary encoding
	TKdvEncodeDescript m_tPriEncode;									///< primary encoding;
	TKdvEncodeDescript m_atSecEncode[MAX_RED_SECENC_NUM];				///< secondary encoding;

public:
	TKdvRedCap()
	{
		Clear();
	}

	void Clear()
	{
		m_emChnlCfg = emChnlCust;
		m_tPriEncode.Clear();
		for(u8 i=0;i<MAX_RED_SECENC_NUM;i++)
		{
			m_atSecEncode[i].Clear();
		}
		m_bySecEncodedNum = 0;
		TKdvAudioCap::Clear();
	}

	/// set/get m_emChnlCfg
	void SetChnl(emRedChnlCfg emChnl)
	{
		m_emChnlCfg = emChnl;
	}
	emRedChnlCfg GetChnl() const
	{
		return m_emChnlCfg;
	}

	/// set/get dynamic payload of primary encoding
	void SetPriEncDynPayload(u16 wPriEncDynPayload)
	{
		m_tPriEncode.m_wDynamicPayload = wPriEncDynPayload;
	}
	u16 GetPriEncDynPayload() const
	{
		return m_tPriEncode.m_wDynamicPayload;
	}

	/// set/get PayloadType of primary encoding
	void SetPriPayloadType(PayloadType emPriPayloadType)
	{
		m_tPriEncode.m_emPayloadType = emPriPayloadType;
	}
	PayloadType GetPriPayloadType() const
	{
		return m_tPriEncode.m_emPayloadType;
	}

	/// set/get dynamic payload of secondary encoding
	void SetSecEncDynPayload(u16 wSecEncDynPayload, u8 byIndex)
	{
		m_atSecEncode[byIndex].m_wDynamicPayload = wSecEncDynPayload;
	}
	u16 GetSecEncDynPayload(u8 byIndex) const
	{
		return m_atSecEncode[byIndex].m_wDynamicPayload;
	}

	/// set/get PayloadType of secondary encoding
	void SetSecPayloadType(PayloadType emSecPayloadType, u8 byIndex)
	{
		m_atSecEncode[byIndex].m_emPayloadType = emSecPayloadType;
	}
	PayloadType GetSecPayloadType(u8 byIndex) const
	{
		return m_atSecEncode[byIndex].m_emPayloadType;
	}

	void host2net(BOOL32 bhton);
}PACKED;



/// MPEG AAC capbility set
struct PROTO_API TKdvAACCap : public TKdvAudioCap
{
	/// sampling frequency
    enum emAACSampleFreq                    
    {
        emFs96000 = 0,
        emFs88200 = 1,
        emFs64000 = 2,
        emFs48000 = 3,
        emFs44100 = 4,
        emFs32000 = 5,
        emFs24000 = 6,
        emFs22050 = 7,
        emFs16000 = 8,
        emFs12000 = 9,
        emFs11025 = 10,
        emFs8000  = 11
    };
    
	/// channel config
    enum emAACChnlCfg                       
    {
        emChnlCust   = 0,
        emChnl1      = 1,                   ///< 单声道
        emChnl2      = 2,                   ///< 双声道
        emChnl3      = 3,					///< 单、双都支持
        emChnl4      = 4,
        emChnl5      = 5,
        emChnl5dot1  = 6,                   ///< 5.1声道
        emChnl7dot1  = 7                    ///< 7.1声道
    };

    emAACSampleFreq m_emSampleFreq;         ///< sampling frequency
    emAACChnlCfg    m_emChnlCfg;			///< channel config
    u16             m_wBitrate;				///< bit rate
    u8              m_byMaxFrameNum;        ///< max frame number

	u8              m_abySpecificConfig[2]; ///< AAC-LC直接设置用，临时修改
	u8              m_abyMuxConfig[7];      ///< AAC-LD直接设置用，临时修改
	BOOL32          m_bOldConfig; // is old config version (2B)

public:
    TKdvAACCap()
    {
        Clear();
    }
    
    void Clear()
    {
        m_emSampleFreq	= emFs32000;
        m_emChnlCfg		= emChnlCust;
        m_byMaxFrameNum = 1;			    ///< 目前我们只支持单帧
        m_wBitrate		= 96;               ///< kbps
		memset(m_abyMuxConfig,      0, sizeof(m_abyMuxConfig));
		memset(m_abySpecificConfig, 0, sizeof(m_abySpecificConfig));
		m_bOldConfig = FALSE;
		TKdvAudioCap::Clear();
    }
    
	/// set/get m_emSampleFreq
    void SetSampleFreq(emAACSampleFreq emFs)
    {
        m_emSampleFreq= emFs;
    }
    emAACSampleFreq GetSampleFreq() const
    {
        return m_emSampleFreq;
    }

	/// set/get m_emChnlCfg
    void SetChnl(emAACChnlCfg emChnl)
    {
        m_emChnlCfg = emChnl;
    }
    emAACChnlCfg GetChnl() const
    {
        return m_emChnlCfg;
    }

	/// set/get m_wBitrate
    void SetBitrate(u16 wBitrate) 
    {
        m_wBitrate = wBitrate;
    }
    u16 GetBitrate() const
    {
        return m_wBitrate;
    }

	// interfaces merged from H.323
	/// interfaces of convert the member's order
	void host2net(BOOL32 bhton);
}PACKED;

/// *********************关于帧率的设置******************
/// 1表示29.97, 2表示29.97/2, 3表示29.97/3,.....
/// H261：cif(1-4) qcif(1-4)
/// H263  sqcif,qcif,cif,4cif,16cif  (1-32)
/// ****************************************************/
///< the base video capbility set
struct PROTO_API TKdvVideoCap : public TKdvCapSet
{
	u16         m_wMaxBitRate;						///< maximum bit rate,单位kbps
	u8          m_abyResolution[emResolutionEnd];	///< resolution set 
    PayloadType	m_emPayloadType;                    ///< payload type,重复定义了

public:
	TKdvVideoCap()
	{
	    Clear();
	}

	void Clear();

	/// set/get m_wMaxBitRate, 单位kbps
	void SetBitRate(u16 wBitRate)
	{
		m_wMaxBitRate = wBitRate;		
	}
	u16 GetBitRate() const
	{
        return m_wMaxBitRate;
	}

	/**
    * \brief: 设置支持的分辨率、帧率
    * \param[in]:	emRes    :表示分辨率
	* \param[in]:	byMPI    :表示帧率
    * \return       TRUE or FALSE 
    */
	BOOL32 SetResolution(emResolution emRes, u8 byMPI);

	/**
    * \brief: 得到支持的分辨率、帧率
    * \param[in]:	emRes       :表示分辨率
	* \param[in]:	byMPI       :表示帧率
    * \return       帧率(0 表示不支持改分辨率) 
    */
	u8 GetResolution( emResolution emRes ) const;

	/// interfaces of convert the member's order
	void	host2net(BOOL32 bhton);

	/// merge the tVideoCap with member
	void	MergeVideoCap(const TKdvVideoCap &tVideoCap);

	/// toolkit: Res enum to width*height
	BOOL32	Res2WxH(emResolution emRes, u16 &wWidth, u16 &wHeight) const;

}PACKED;


/*********************关于帧率的设置******************
*1表示1fps, 60代表60fps，最大允许帧率可以达到理论值255
*****************************************************/
/// the capbility struct of h264
struct PROTO_API TKdvH264VideoCap:public TKdvVideoCap
{
protected:
    /// H.264 参数定义，参见 ITU H.241文档
    u8              m_byProfile;          ///< profile
    u8              m_byLevel;			  ///< level
    /// 以下2个字段，取 Custom 与Level值默认的 max(单位均为宏块)
    s32             m_nMaxMBPS;           ///< Max MBPS
    s32             m_nMaxFS;			  ///< Max FS
    /// 以下保存的是绝对 Custom 的字段（暂时不支持设置）
    s32             m_nMaxDPB;            ///< Max DPB
    s32             m_nMaxBRandCPB;		  ///< Max BRandCPB
    s32             m_nMaxStaticMBPS;     ///< Max StaticMBPS
										
	s32             m_nParaFlag;          ///< 标志字段,如果参数偏大相应位置位
	
	u8				m_byAdditionalModes;  ///< svc

	emH264NALMode   m_emH264NALMode;      ///< nal mode
	
public:
	BOOL32          m_bOld264Level;
	BOOL32			m_bUsed;

public:
    /// profile mask 
    enum  emH264ProfileMask
    {
        emProfileBaseline = 64,
        emProfileMain     = 32,
        emProfileExtend   = 16,
        emProfileHigh     = 8
    };

	/// additional modes of svc
	enum emAdditionalModes
	{
		emModeRCDO	= 64,		///< RCDO
		emModeSBP	= 32,		///< SCALABLE bp
		emModeSHP	= 16		///< SCALABLE hp
	};

    TKdvH264VideoCap();  
    void Clear();

	void host2net(BOOL32 bhton);

	/// 协议: 支持 emH264ProfileMask 各个参数和它们的逻辑与
    void SetSupportProfile(u8 byProfile)
	{
		m_byProfile = byProfile;
		//if(m_byProfile < 64)
		//	m_byProfile = 64;
	}

	/// is support profile
	BOOL32 IsSupportProfile(u8 byReqProfile) const
	{
		return ((m_byProfile&byReqProfile) == byReqProfile);
	}
	
	/// Get Profile Value
    u8   GetProfileValue() const
    {
        return m_byProfile;
    }
    
	/// 能力集操作
	/**
 	 *function: 获取特定分辨率下的帧率
	 *param:	u8 byRes                    分辨率：emResolution 或者 emResolutionHD
	 *return:   u8 帧率 frame/s
	 */
    u8   GetResolution(emResolution emRes) const;
    u8   GetResolution(u16 wWidth, u16 wHeight) const;

	/**
	 * \brief: 特定分辨率下，特定帧率(对于场模式，需要上层转化为帧率传入)是否支持  \
                至于对端是否支持场格式，要业务根据 IsSupportProfile 自行判断 
	 * \param[in]	u8 byRes       :分辨率：emResolution 或者 emResolutionHD
     * \param[in]   u8 byFps       :帧率frame/s
	 * \return      TRUE:supprot,FALSE:not support
	 */
    BOOL32 IsSupport(emResolution emRes, u8 byFps) const;
    BOOL32 IsSupport(u16 wWidth, u16 wHeight, u8 byFps) const;

	/**
	 * \brief: 设置支持某种分辨率和帧率(对于场模式，需要上层转化为帧率传入)。多种分辨率可以叠加设置
	 * \param[in]	u8 byRes       :分辨率：emResolution 或者 emResolutionHD
     * \param[in]   u8 byFps       :帧率frame/s
	 */
    void  SetResolution(emResolution emRes, u8 byFps);
    void  SetResolution(u16 wWidth, u16 wHeight, u8 byFps);

    /// set/get 内部使用函数
    void  SetMaxMBPS(s32 nMax)
    {
        m_nMaxMBPS = nMax;
    }
    s32   GetMaxMBPS() const
    {
        return m_nMaxMBPS;
    }
    void  SetMaxFS(s32 nMax)
    {
        m_nMaxFS = nMax;
    }
    s32   GetMaxFS() const
    {
        return m_nMaxFS;
    }
	void SetMaxStaticMBPs( s32 nStaticMBPs )
	{
		m_nMaxStaticMBPS = nStaticMBPs;
	}
	s32 GetMaxStaticMBPs() const
	{
		return m_nMaxStaticMBPS;
	}

	/// set/get m_nAdditionalModes
	void SetSupportAdditionalModes(u8 byAdditionalModes)
    {
        m_byAdditionalModes = byAdditionalModes;
    }	
    BOOL32 IsSupportAdditionalModes(u8 byAdditionalModes) const
    {
        return ((m_byAdditionalModes&byAdditionalModes) == byAdditionalModes);
    }	
    u8   GetAdditionalModes() const   
    {
        return m_byAdditionalModes;
	}

	/// set/get m_emH264NALMode
	void SetH264NALMode(emH264NALMode emNalMode)
	{
		m_emH264NALMode = emNalMode;
	}
	emH264NALMode GetH264NALMode() const   
	{
		return m_emH264NALMode;
	}

	/// set/get m_nMaxBRandCPB
	void  SetMaxBRandCPB(s32 nMaxBRandCPB)
	{
		m_nMaxBRandCPB = nMaxBRandCPB;
	}
	s32   GetMaxBRandCPB() const
	{
		return m_nMaxBRandCPB;
	}

    /// set/get Level，外部调用无效
    void SetLevel(u8 byLevel)
    {
        m_byLevel = byLevel;
    }
     u8 GetLevel() const
    {
        return m_byLevel;
    }

	/// set/get m_nParaFlag
	s32 GetParaFlag()
	{
		return m_nParaFlag;
	}
	void SetParaFlag(s32 nParaFlag)
    {
        m_nParaFlag = nParaFlag;
    }

	BOOL32 operator <= (const TKdvH264VideoCap& tH264VideoCap);
	void operator = (const TKdvH264VideoCap& tH264VideoCap);
	BOOL32 operator == (const TKdvH264VideoCap& tH264VideoCap);

	BOOL32 AdjustH264Cap();
}PACKED;

//////////////////////////////////////////////////////////////////////////
// H.265 video capability 
// You can refer to T-REC-H.265-201304-I from ITU/T for H.265 standards details
//////////////////////////////////////////////////////////////////////////
/// the capbility struct of h265
struct PROTO_API TKdvH265VideoCap : public TKdvVideoCap
{
protected:
	/// H.265 Level Limits, refer to ITU H.241 for more info
    u8		m_byProfile;
    u8		m_byLevel;
	u8		m_byTier;
	s32		m_nMaxLS;			///< Max LUMA sample rate (samples/sec,w*h*pfs) ,should be defined m_nMaxLumaSR
	s32		m_nMaxLumaPS;		///< Max LUMA picture size (samples,w*h): 
	/// H.265 capability related variants
	s32		m_nMaxDPB;			///< Max Decode Picture Buffer
	s32		m_nMaxBR;			///< Max Bit Rate
	s32		m_nMaxCPB;			///< Max Code Picture Buffer
	s32		m_nMaxSliceSegmentsPerPic;
	s32		m_nMaxTileRows;
	s32		m_nMaxTileCols;
	s32		m_nMinCbSizeY;
	
public:
	BOOL32	m_bUsed;

public:
	TKdvH265VideoCap();  

public:
	/// Refer document: T-REC-H.265-201304-I: Annex A
    enum emH265Profile
    {
        emProfileMain = 1,
        emProfileMain10,
        emProfileMainStill,
    };

	enum emH265Level
	{
		emLevel10 = 30,///<   1.0  1.0*30
		emLevel20 = 60,///<   2.0  2.0*30
		emLevel21 = 63,///<   2.1  2.1*30
		emLevel30 = 90,
		emLevel31 = 93,
		emLevel40 = 120,
		emLevel41 = 123,
		emLevel50 = 150,
		emLevel51 = 153,
		emLevel52 = 156,
		emLevel60 = 180,
		emLevel61 = 183,
		emLevel62 = 186,
	};

	enum emH265Tier
	{
		emHignTier,
		emMainTier,
	};

    void	Clear();

    /// 能力集操作
     /**
	 *function: 获取特定分辨率下的帧率
	 *param:	u8 byRes                    分辨率：emResolution 或者 emResolutionHD
     *return:   u8 帧率 frame/s
	 */
    u8		GetResolution(emResolution emRes) const;
    u8		GetResolution(u16 wWidth, u16 wHeight) const;

	/**
	 *function: 特定分辨率下，特定帧率(对于场模式，需要上层转化为帧率传入)是否支持
                至于对端是否支持场格式，要业务根据 IsSupportProfile 自行判断 
	 *param:	u8 byRes                    分辨率：emResolution 或者 emResolutionHD
                u8 byFps                    帧率frame/s
     *return:   TRUE/FALSE
	 */
    BOOL32	IsSupport(emResolution emRes, u8 byFps) const;
    BOOL32	IsSupport(u16 wWidth, u16 wHeight, u8 byFps) const;

	/**
	 *function: 设置支持某种分辨率和帧率(对于场模式，需要上层转化为帧率传入)。多种分辨率可以叠加设置
	 *param:	u8 byRes                    分辨率：emResolution 或者 emResolutionHD
                u8 byFps                    帧率frame/s
	 */
    void	SetResolution(emResolution emRes, u8 byFps) ;
    void	SetResolution(u16 wWidth, u16 wHeight, u8 byFps) ;

	
	/// 协议: 支持 emH265ProfileMask 各个参数和它们的逻辑与
    void SetSupportProfile(u8 byProfile)
	{
		m_byProfile = byProfile;
		//if(m_byProfile < 64)
		//	m_byProfile = 64;
	}
	BOOL IsSupportProfile(u8 byReqProfile) const
	{
		return ((m_byProfile&byReqProfile) == byReqProfile);
	}
    u8   GetProfileValue() const
    {
        return m_byProfile;
    }

    /// set/get Level
    void	SetLevel(u8 byLevel) { m_byLevel = byLevel; }
	u8		GetLevel() const { return m_byLevel; }

	/// set/get Profile
	void	SetProfile(u8 byProfile) { m_byProfile = byProfile; }
	u8		GetProfile() const {return m_byProfile;};

	/// set/get Tier
	void	SetTier(u8 byTier) {m_byTier = byTier;}
	u8		GetTier() const {return m_byTier;}

	/// Interfaces for internal use only
	s32		GetMaxLumaPS() const {return m_nMaxLumaPS;}
	void	SetMaxLumaPS(s32 nMaxLumaPs) {m_nMaxLumaPS = nMaxLumaPs;}
	s32		GetMaxCPB() const {return m_nMaxCPB;}
	void	SetMaxCPB(s32 nMaxCPB) {m_nMaxCPB = nMaxCPB;}
	s32		GetMaxSliceSegPerPic() const {return m_nMaxSliceSegmentsPerPic;}
	void	SetMaxSliceSegPerPic(s32 nMaxSliceSegPerPic) {m_nMaxSliceSegmentsPerPic = nMaxSliceSegPerPic;}
	s32		GetMaxTileRows() const {return m_nMaxTileRows;}
	void	SetMaxTileRows(s32 nMaxTileRows) {m_nMaxTileRows = nMaxTileRows;}
	s32		GetMaxTileCols() const {return m_nMaxTileCols;}
	void	SetMaxTileCols(s32 nMaxTileCols) {m_nMaxTileCols = nMaxTileCols;}
	s32		GetMaxLS() const {return m_nMaxLS;}
	void	SetMaxLS(s32 nMaxLS) {m_nMaxLS = nMaxLS;}
	s32		GetMaxDPB() const {return m_nMaxDPB;}
	void	SetMaxDPB(s32 nMaxDPB) {m_nMaxDPB = nMaxDPB;}
	s32		GetMaxBR() const {return m_nMaxBR;}
	void	SetMaxBR(s32 nMaxBR) {m_nMaxBR = nMaxBR;}

	BOOL32	operator <= (const TKdvH265VideoCap& tH265VideoCap);
	void	operator =  (const TKdvH265VideoCap& tH265VideoCap);
	BOOL32	operator == (const TKdvH265VideoCap& tH265VideoCap);

	static BOOL32 GetH265LimitsByLevel(IN emH265Level emLevel, OUT s32 &nMaxLS, OUT s32 &nMxLumaPS);
	
	/// Judge Endian
	BOOL32	IsLittleEndian();

	///for little-endian sysytem，send only;
	///for big-endian system,convert to byte order(actually,little-endian)
	void    Convert2ByteOrder(BOOL32 bLittleEndian);
}PACKED;

/// the capbility struct of Data
struct PROTO_API TKdvDataCap : public TKdvCapSet
{
	u32   m_dwMaxBitRate;					///< maximum bit rate ,单位kbps; 
public:
	TKdvDataCap()
	{
		Clear();
	}

	void Clear()
	{
		TKdvCapSet::Clear();
		m_dwMaxBitRate = SIP_ADPT_FECC_DEFAULT_BITRATE;
		m_dwSampleRate = 0;
	}

	/// 单位kbps
	void SetBitRate(u32 dwBitRate)
	{
		m_dwMaxBitRate = dwBitRate;		
	}
	u32 GetBitRate()
	{
        return m_dwMaxBitRate;
	}

	/// Interfaces merged from H.323
	void host2net(BOOL32 bhton)
	{
		s32 nCapDirection = m_emCapDirection;
		if (bhton)
		{
			m_emCapDirection = (EM_CAPDIRECTION)htonl(nCapDirection);
			m_dwMaxBitRate   = htonl(m_dwMaxBitRate);
		}
		else
		{
			m_emCapDirection = (EM_CAPDIRECTION)ntohl(nCapDirection);
			m_dwMaxBitRate   = ntohl(m_dwMaxBitRate);
		}
	}
}PACKED;


/// 能力集结构
///< 目前的视频支持:h261,h263,h264,mpeg4,h263+,h262
///< 目前的音频支持:G711u(64k),G711a(64k),G722(64k),G7231,G728,G729,G7221C,MP3,MP2AAC,MP4AAC.
///< guzh [12/17/2007] 调整结构
///< guzh [04/03/2008] 调整结构
struct PROTO_API TKdv323CapSet
{
private:
	u16 m_awCapTable[MAX_CAPTABLE_SIZE];                                ///< PayloadType array
	u16 m_aaawCapDesc[MAX_DESCAP_NUM][MAX_SIMUCAP_NUM][MAX_ALTCAP_NUM]; ///< PayloadType array
    /// Video
	TKdvVideoCap      m_tH261Cap;
	TKdvVideoCap      m_tH263Cap;
	TKdvVideoCap      m_tH263plusCap;
	TKdvVideoCap      m_tMpeg4Cap;
    TKdvVideoCap      m_tH262Cap;
    /// Audio
	TKdvAudioCap      m_tG711u;   
	TKdvAudioCap      m_tG711a;   
	TKdvAudioCap      m_tG722;    
	TKdvAudioCap      m_tG728;	   
	TKdvAudioCap      m_tG729;
	TKdvAudioCap      m_tMP3;
    TKdvAACCap        m_tMpegAacLc;
    TKdvAACCap        m_tMpegAacLd;		
	TKdvG7231Cap      m_tG7231;
    /// Data
	TKdvDataCap       m_tT120;
	TKdvDataCap       m_tH224;

    /*载荷类型的内部转换:
    |<--------------加密和H239的载荷转换---------- >|<低字节为上层使用的类型>|
    ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    +  0  +  0  +  0  +  0  +  1  +  1  +  1  +  1  +  payloadType           +             
    ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            + H239+ AES + DES +NoEnc+   
    */
	u8                m_byEncryptBits;	        ///< enum emEncryptType
	emH239RoleLabel   m_nSupportH239Type;       ///< 支持H.239的类型
	BOOL32            m_bSupportRSVP;           ///< 是否支持RSVP功能
	BOOL32            m_bSupportActiveH263Plus; ///< 是否支持H.263+
    u8                m_byFECBits;              ///< 前向纠错
												

    /// H.264 能力
    TKdvH264VideoCap  m_atH264Cap[MAX_H264CAP_NUM];
	u8			      m_awH264ToSubId[MAX_CAPTABLE_SIZE]; ///< H264 payload id 到 sub id 映射表
	u8				  m_byH264SubId;
	u32               m_dwH264NALMode;                    ///< H264 mediaPacketization mode

	TKdvAudioCap	  m_tG719; 	
	TKdvOpusCap		  m_tOpusCap;	
	TKdvG7221Cap	  m_tG7221;		

	/// H.265
	TKdvH265VideoCap  m_atH265Cap[MAX_H265CAP_NUM];
	u8				  m_awH265ToSubId[MAX_CAPTABLE_SIZE]; ///< H265 payload id 到 sub id 映射表
	u8				  m_byH265SubId;

public:
	TKdv323CapSet()
	{
		Clear();
	}

	void Clear();

    void host2net(BOOL32 bhton);

    /// 设置支持RSVP功能
    void SetSupportRSVP(BOOL32 bSupportRSVP)
    {
        m_bSupportRSVP = bSupportRSVP;
    }
    /// 是否支持RSVP
    BOOL32 IsSupportRSVP()
    {
        return m_bSupportRSVP;
    }

	/// 设置支持RSVP功能
    void SetSupportActiveH263(BOOL32 bSupport)
    {
        m_bSupportActiveH263Plus = bSupport;
    }
    /// 是否支持RSVP
    BOOL32 IsSupportActiveH263()
    {
        return m_bSupportActiveH263Plus;
    }
    /// 设置前向纠错类型
    void SetFECType(u8 emType)
    {
        m_byFECBits = emType;
    }
    /// 获取前向纠错类型
    u8 GetFECType() const
    {
        return m_byFECBits;
    }
    /// 上层暂时不使用
    void SetSupportH239Type(s32 nSupporth239)
    {
        m_nSupportH239Type = (emH239RoleLabel)nSupporth239;
    }
    s32 GetSupportH239Type()
    {
        return m_nSupportH239Type;
    }

    //modified for h265 [20141124]
	/**
	* \brief             set payload to capbility descriptor
	* \note              如果是H.264或者H.265，则需额外传入SetH264VideoCap、SetH265VideoCap时对应的数组下标bySubId
	* \param[in]         byCapIndex      :Capability Descriptor index
	* \param[in]         bySimuIndex     :simultaneous Capabilitie index
	* \param[in]         byAltIndex      :Capability Table Entry index
	* \param[in]         wPayload        :payload
	* \param[in]         bySubId         :the subId of h264 or h265
	* \return            TRUE:if success,FALSE:failed
	*/
	BOOL32 SetCapDesc(u8 byCapIndex, u8 bySimuIndex, u8 byAltIndex, u16 wPayload, u8 bySubId = 0);
	
	/**
	* \brief             set descriptor id of capbility to aaawCapDesc
	* \param[in]         byCapIndex      :Capability Descriptor index
	* \param[in]         bySimuIndex     :simultaneous Capabilitie index
	* \param[in]         byAltIndex      :Capability Table Entry index
	* \param[in]         capId           :Capability id
	*/
	void SetCapDescId(u8 byCapIndex, u8 bySimuIndex, u8 byAltIndex, u16 capId);
      
	/**
	* \brief             get descriptor id of capbility from aaawCapDesc
	* \param[in]         byCapIndex      :Capability Descriptor index
	* \param[in]         bySimuIndex     :simultaneous Capabilitie index
	* \param[in]         byAltIndex      :Capability Table Entry index
	* \param[in]         capId           :Capability id
	* \return            the value of descriptor id
	*/
	u16 GetCapDescId(u8 byCapIndex, u8 bySimuIndex, u8 byAltIndex); ///< 得到能力级  
   
	/**
	* \brief             if exist simultaneous capbility,the parameters compared with members 
	* \param[in]         pwPayload      :array of payloads,which payloads do you want to compare
	* \param[in]         nNum           :the number of array of pwPayload
	* \param[in/out]     ptH264Cap      :in:all h264's capbility to compare,out:if exist it points member's cap
	* \param[in/out]     ptH265Cap      :in:all h265's capbility to compare,out:if exist it points member's cap
	* \param[in]         ptAacCap       :all aac's capbility to compare
	* \return            TRUE:if successed,FALSE:if failed
	*/
    BOOL32 IsExistsimultaneous(u16 *pwPayload, s32 nNum, TKdvH264VideoCap* ptH264Cap=NULL, TKdvH265VideoCap* ptH265Cap=NULL,TKdvAACCap *ptAacCap = NULL );
	
	/// get payload form capbility table
	u16 GetCapFromTable(u8 byCapIndex)
	{
		if(byCapIndex >= MAX_CAPTABLE_SIZE)
			return 0;
		return m_awCapTable[byCapIndex];
	}

	/// set payload to capbility table
	void SetCapToTable(u8 byCapIndex, u16 wPayload)
	{
		if(byCapIndex >= MAX_CAPTABLE_SIZE)
			return;
		m_awCapTable[byCapIndex] = wPayload;
	}

    /// 设置视频能力集.不包括H.264、H.265
	BOOL32 SetVideoCap(TKdvVideoCap &tVideoCap, u16 wPayload);

    /// 得到视频能力集.不包括H.264、H.265
    TKdvVideoCap* GetVideoCap(u16 wPayload);

    /// 设置H.264视频能力集,返回值是byH264SubId,调SetCapDesc时用
    u8 SetH264VideoCap(TKdvH264VideoCap &tVideoCap);

    /// 得到H.264视频能力集
    TKdvH264VideoCap* GetH264VideoCap(u8 bySubId);
  
    /// 得到H264个数
	u8 GetH264Num()
	{
		return m_byH264SubId;
	}

	/// 设置H.265视频能力集,返回值是byH265SubId,调SetCapDesc时用
    u8 SetH265VideoCap(TKdvH265VideoCap &tVideoCap);

	/// 得到H.265视频能力集
    TKdvH265VideoCap* GetH265VideoCap(u8 bySubId)
    {
        if (bySubId >= MAX_H265CAP_NUM)
        {
            return NULL;
        }
        return &(m_atH265Cap[bySubId]);
    }

	/// 得到H265个数
	u8 GetH265Num()
	{
		return m_byH265SubId;
	}

	/// 不包含G7231/AAC/opus
	TKdvAudioCap* GetAudioCap(u16 wPayload);

	/// 不包含G7231/AAC/opus/G7221
	BOOL32 SetAudioCap(TKdvAudioCap &tAudioCap, u16 wPayload);

	/// G7231
	TKdvG7231Cap* GetG7231Cap()
	{	
		return &m_tG7231;
	}
	/// G7231
	BOOL32 SetG7231Cap(TKdvG7231Cap &tG7231Cap)
	{
		m_tG7231 = tG7231Cap;
		return TRUE;
	}
    /// AAC
    TKdvAACCap* GetAACCap(u16 wPayload);

    /// AAC
    BOOL32 SetAACCap(TKdvAACCap &tAudioCap, u16 wPayload);
   	
	/// get Opus
	TKdvOpusCap* GetOpusCap()
	{	
		return &m_tOpusCap;
	}

	/// set Opus
	BOOL32 SetOpusCap(TKdvOpusCap &tOpusCap)
	{
		m_tOpusCap = tOpusCap;
		return TRUE;
	}
	/// get G7221
	TKdvG7221Cap* GetG7221Cap()
	{	
		return &m_tG7221;
	}

	/// set G7221
	BOOL32 SetG7221Cap(TKdvG7221Cap &tG7221Cap)
	{
		m_tG7221 = tG7221Cap;
		return TRUE;
	}

	/// get data cap,T120 H224
	TKdvDataCap* GetDataCap(u16 wPayload);

	/// set data cap,T120 H224
	BOOL32 SetDataCap(TKdvDataCap &tDataCap, u16 wPayload);

	/// 仅用于发送能力集时使用,表示同时支持的加密能力.如byEncryptBit=emEncryptTypeDES|emEncryptTypeAES;
	void SetEncryptBits( u8 byEncryptBits)
	{
		m_byEncryptBits = byEncryptBits;
	}
	u8 GetEncryptBits()
	{
		return m_byEncryptBits;
	}

	/// get the subid of h264
	u8 GetH264SubId(u8 byCapIdex)
	{
		return m_awH264ToSubId[byCapIdex];
	}

	//add by hong for H.265
	/// get the subid of h265
	u8 GetH265SubId(u8 byCapIndex)
	{
		return m_awH265ToSubId[byCapIndex];	
	}

	/// set nal mode of h264
	void SetH264NALMode(u32 dwNALMode)
	{
		m_dwH264NALMode = dwNALMode;
	}

	/// get nal mode of h264
	u32 GetH264NALMode()
	{
		return m_dwH264NALMode;
	}

	/// h265 capbility compared,if tH265A less or equal tH265B
	BOOL32 IsH265CapALessEqualB( const TKdvH265VideoCap & tH265A, const TKdvH265VideoCap & tH265B );

	/// h264 capbility compared,if tH264A less or equal tH264B
	BOOL32 IsH264CapALessEqualB( const TKdvH264VideoCap & tH264A, const TKdvH264VideoCap & tH264B );


	/**
	* \brief             返回某一分辨率下对端能力集所支持的最大帧率的TKdvH264VideoCap结构体
	* \param[in]         pwPayload          :array of payloads,which payloads do you want to compare
	* \param[in]         nNum               :the number of array of pwPayload
	* \param[out]        bStatic            :返回的TKdvH264VideoCap结构体中是否包含staticMaxBPS
	* \param[in]         nFirstPtIndex      :第一路视频在payload数组中的索引，若第一路非h264为-1
	* \param[in]         nSecondPtIndex     :第二路视频在payload数组中的索引，若无第二路为-1
	* \param[in/out]     ptH264Cap          :能力集数组
	* \note              1、参数TKdvH264VideoCap* ptH264Cap是INOUT类型，但是本算法中返回的ptH264Cap数组仅最后一个索引值有效，\
	                     因为只有在第一路成功发起的条件下才会尝试发送第二路，故数组ptH264Cap[2]中的ptH264Cap[0]的值已      \
	                     固定，是否改变不予参考，ptH264Cap[1]表示第二路匹配成功的值              \
	                     2、本函数仅对H264能力集支持                                 \
	                     3、建议在调用IsExistsimultaneous()失败的情况下调用本函数     \
	* \return            TRUE:匹配成功, FALSE:失败
	*/
	BOOL32 FindH264PeerBestSupport( u16 *pwPayload, s32 nNum, OUT BOOL32 &bStatic, s32 nFirstPtIndex = -1, s32 nSecondPtIndex = -1, INOUT TKdvH264VideoCap* ptH264Cap = NULL );
	
	/// like the FindH264PeerBestSupport
	BOOL32 FindH265PeerBestSupport( u16 *pwPayload, s32 nNum, s32 nFirstPtIndex = -1, s32 nSecondPtIndex = -1, INOUT TKdvH265VideoCap* ptH265Cap = NULL );
private:
	/// 往能力表添加能力项。如果为 H.264则需要传入TKdvH264VideoCap数组下标，返回值为payload在captable中的索引值
	///< bySubId 可以是h264的也可以是h265的，根据实际情况填入
	u16 AddCapToTable(u16 wPayload, u8 bySubId);

	BOOL32 IsInterExistsimultaneous( u16 *pwPayload, s32 nNum, TKdvH264VideoCap* ptH264Cap=NULL, s32 nH264Num=0, TKdvH265VideoCap* ptH265Cap=NULL, s32 nH265Num=0, TKdvAACCap* ptAacCap = NULL );

	/// if find tH264VideoCap in m_atH264Cap,return the SubId
    BOOL32 FindH264VideoCap(TKdvH264VideoCap& tH264VideoCap, u8& bySubId);

	/// if find tH265VideoCap in m_atH265Cap,return the SubId
	BOOL32 FindH265VideoCap(TKdvH265VideoCap& TKdvH265VideoCap, u8& bySubId);
}PACKED;


/// defined in rfc4796
enum EmSipContentAttr
{
	emSipContentNone = 0, ///< none
	emSipContentSlides,   ///< slides
	emSipContentSpeaker,  ///< speaker
	emSipContentSl,       ///< sl
	emSipContentMain,     ///< main
	emSipContentAlt,      ///< alt
};

/// defined in rfc4145
enum EmSipSetupAttr
{
	emSipSetupBegin = 0, ///< setup begin
	emSipActive = 1,     ///< active
	emSipPassive = 2,    ///< passive
	emSipActpass = 3,    ///< actpass
	emSipHoldconn = 4    ///< hold connection
};

/// defined in rfc4145
enum EmSipConnectionAttr
{
	emSipConnectionBegin = 0, ///< connection begin
	emSipNew = 1,             ///< sip new
	emSipExisting = 2,        ///< existing
};

/// defined in rfc4583
enum EmSipFloorcontrolAttr
{
	emSipFloorcontrolBegin = 0, ///< floor control begin
	emSipClientOnly = 1,        ///< sip client only  
	emSipServerOnly = 2,        ///< sip server only
	emSipClientServer = 3       ///< sip client and server
};
/// cap order
enum EmCapOrder
{
	emCapOrderBegin,            ///< order begin
	emMainAudio,                ///< main audio
	emMainVideo,                ///< main video
	emDualAudio,                ///< dual audio
	emDualVideo,                ///< dual video
	emBfcp,                     ///< bfcp
	emFecc,                     ///< fecc
	emCapOrderEnd               ///< order end
};

/// nfcp sdp attribute
enum EmSipBfcpSdpAttr
{
	emSipBfcpSdpBegin = 0,      ///< bfcp sdp begin
	emSipTcpBfcp,               ///< tcp
	emSipTcpTlsBfcp,            ///< tls
	emSipUdpBfcp,               ///< udp
	emSipUdpTlsBfcp,            ///< udp tls
};

/// bfcp floor info
typedef struct PROTO_API tagBfcpFloorInfo
{
	u16 m_wFloorId;                             ///< floor id
	s32 m_nLabelNum;                            ///< label number
	s32 m_anLabelList[MAX_MEDIA_NUM_PER_FLOOR]; ///< label list
	
	/**
    * \brief            tagBfcpFloorInfo init
    * \return           void.
    */
	void Clear()
	{
		m_wFloorId = 0;
		m_nLabelNum = 0;
		for (s32 i = 0; i < MAX_MEDIA_NUM_PER_FLOOR; i++)
		{
			m_anLabelList[i] = 0;
		}
	}
	/**
    * \brief            tagBfcpFloorInfo Constructor
    * \return           void.
    */
	tagBfcpFloorInfo()
	{
		Clear();
	}
}TBfcpFloorInfo;

/// bfcp media stream
class  PROTO_API CBfcpMediaStream
{
public:
	/**
    * \brief            CBfcpMediaStream Constructor
    * \return           void.
    */
	CBfcpMediaStream();
	
	/**
    * \brief            CBfcpMediaStream init
    * \return           void.
    */
	void Clear();

	/**
    * \brief            CBfcpMediaStream operator =
    * \return           void.
    */
	void operator = (const CBfcpMediaStream& cCopyMedia);

	/**
	* \brief            Set bfcp  media port
	* \param[in]        wPort  :media port
	*/
	void SetBfcpMediaPort( u16 wPort )
	{
		m_wPort = wPort;
	}
	/**
    * \brief            get bfcp  media port
    * \return           u16.
    */
	u16 GetBfcpMediaPort()
	{
		return m_wPort;
	}
	/**
	* \brief            Set Bfcp Floor control Attr
	* \param[in]        EmSipFloorcontrolAttr  :Sip Floor control Attribute
	*/
	void SetBfcpFloorcontrolAttr( EmSipFloorcontrolAttr emFloorcontrolAttr )
	{
		m_emFloorcontrolAttr = emFloorcontrolAttr;
	}
	/**
    * \brief            Get Bfcp Floor control Attr
    * \return           EmSipFloorcontrolAttr.
    */
	EmSipFloorcontrolAttr GetBfcpFloorcontrolAttr()
	{
		return m_emFloorcontrolAttr;
	}
	/**
	* \brief            Set Bfcp Setup Attr
	* \param[in]        emSetupAttr  :Sip set up Attribute
	*/
	void SetBfcpSetupAttr( EmSipSetupAttr emSetupAttr )
	{
		m_emSetupAttr = emSetupAttr;
	}
	/**
    * \brief            Get Bfcp set up Attr
    * \return           EmSipSetupAttr.
    */
	EmSipSetupAttr GetBfcpSetupAttr()
	{
		return m_emSetupAttr;
	}
	/**
	* \brief            Set Bfcp connection Attr
	* \param[in]        EmSipConnectionAttr  :connection attribute
	*/
	void SetBfcpConnectionAttr( EmSipConnectionAttr emConnectionAttr )
	{
		m_emConnectionAttr = emConnectionAttr;
	}
	/**
    * \brief            Get Bfcp Connection Attr
    * \return           EmSipSetupAttr.
    */
	EmSipConnectionAttr GetBfcpConnectionAttr()
	{
		return m_emConnectionAttr;
	}
	/**
	* \brief            Set Bfcp Sdp Attr
	* \param[in]        EmSipConnectionAttr  :connection attribute
	*/
	void SetBfcpSdpAttr( EmSipBfcpSdpAttr emBfcpSdpAttr )
	{
		m_emBfcpSdpAttr = emBfcpSdpAttr;
	}
	/**
    * \brief            Get Bfcp sdp Attr
    * \return           EmSipBfcpSdpAttr.
    */
	EmSipBfcpSdpAttr GetBfcpSdpAttr()
	{
		return m_emBfcpSdpAttr;
	}
	/**
	* \brief            Set conf id
	* \param[in]        dwConfId  :conf id
	*/
	void SetConfId( u32 dwConfId )
	{
		m_dwConfId = dwConfId;
	}
	/**
    * \brief            Get conf id
    * \return           u32.
    */
	u32 GetConfId()
	{
		return m_dwConfId;
	}
	/**
	* \brief            Set user id
	* \param[in]        wUserId  :user id
	*/
	void SetUserId( u16 wUserId )
	{
		m_wUserId = wUserId;
	}
	/**
    * \brief            Get user id
    * \return           u16.
    */
	u16 GetUserId()
	{
		return m_wUserId;
	}
	/**
	* \brief            Set floor number
	* \param[in]        nNum  :number
	*/
	void SetFloorNum(s32 nNum)
	{
		m_nFloorNum = nNum;
	}
	/**
    * \brief            Get floor number
    * \return           s32.
    */
	s32 GetFloorNum()
	{
		return m_nFloorNum;
	}
	/**
	* \brief            Set floor info
	* \param[in]        nIndex  :floor index
	* \param[in]        ptInfo  :floor info
	*/
	void SetFloorInfo(s32 nIndex, TBfcpFloorInfo *ptInfo)
	{
		memcpy(&m_atBfcpFloor[nIndex], ptInfo, sizeof(TBfcpFloorInfo));
	}
	/**
    * \brief            Get floor info
    * \return           TBfcpFloorInfo.
    */
	TBfcpFloorInfo* GetFloorInfo(s32 nIndex)
	{
		return &m_atBfcpFloor[nIndex];
	}
	/**
	* \brief            Set floor id
	* \param[in]        nIndex    :floor index
	* \param[in]        wFloorId  :floor id
	*/
	void SetFloorId(s32 nIndex, u16 wFloorId)
	{
		m_atBfcpFloor[nIndex].m_wFloorId = wFloorId;
	}

	/**
	* \brief            Set Bfcp Media IP
	* \param[in]        dwIP    :ip
	*/
	void SetBfcpMediaIP(u32 dwIP)
	{
		m_dwBFCPMediaIP = dwIP;
	}
	/**
    * \brief            Get bfcp media ip
    * \return           u32.
    */
	u32 GetBfcpMediaIP()
	{
		return m_dwBFCPMediaIP;
	}
	/**
    * \brief            Set Bfcp Stand Tls
    * \param[in]        flag    :is standard tls
    */
	void SetBfcpTlsType(EmTlsType emTlsType)
	{
		m_emTlsType = emTlsType;
	}
	/**
    * \brief            is bfcp standard tls
    * \return           BOOL32, TRUE/FALSE
    */
	EmTlsType GetBfcpTlsType()
	{
		return m_emTlsType;
	}
private:		 
	u16 m_wPort;                                 ///< port
	EmSipFloorcontrolAttr m_emFloorcontrolAttr;  ///< floor control attribute
	EmSipSetupAttr m_emSetupAttr;                ///< set up attribute
	EmSipConnectionAttr m_emConnectionAttr;      ///< connection attribute
	EmSipBfcpSdpAttr m_emBfcpSdpAttr;            ///< bfco sdp attribute

	u32 m_dwConfId;                              ///< conf id
	u16 m_wUserId;                               ///< user id
	s32 m_nFloorNum;	                         ///< Floor Number
	TBfcpFloorInfo m_atBfcpFloor[MAX_FLOOR_NUM]; ///< Floor

	u32	m_dwBFCPMediaIP;                         ///< Independent Media IP settings for hole punching mechanism of SIP proxy

	EmTlsType m_emTlsType;                       ///< tls type
};

/// fecc media stream
class PROTO_API CFeccMediaStream
{
public:
	/**
    * \brief            CFeccMediaStream Constructor
    * \return           void.
    */
	CFeccMediaStream();
	
	/**
    * \brief            CFeccMediaStream init
    * \return           void.
    */
	void Clear();

	/**
    * \brief            CFeccMediaStream '='
    * \return           void.
    */
	void operator = (const CFeccMediaStream& cCopyMedia);

	/**
    * \brief            set connection attribute
	* \param[in]        emSendRecvAttr     ;send recv attribute
    * \return           void.
    */
	void SetConnectAttribute( emSendRecvAttr emConnectAttr )
	{
		m_emSendRecvAttr = emConnectAttr;
	}

	/**
    * \brief            get connection attribute
    * \return           emSendRecvAttr.
    */
	emSendRecvAttr GetConnectAttribute()
	{
		return m_emSendRecvAttr;
	}

	void SetLocalSendAddress( PFC_IPADDR* ptLocalSendAddr )
	{
		if (NULL != ptLocalSendAddr)
		{
			m_tLocalSendAddress = *ptLocalSendAddr;
		}		
	}
	/**
    * \brief            get local Send Address
    * \return           PFC_IPADDR.
    */
	PFC_IPADDR* GetLocalSendAddress()
	{
		return &m_tLocalSendAddress;
	}
	/**
    * \brief            set local Recv Address
	* \param[in]        ptLocalRecvAddr     :PFC_IPADDR
    * \return           void.
    */
	void SetLocalRecvAddress( PFC_IPADDR* ptLocalRecvAddr )
	{
		if (NULL != ptLocalRecvAddr)
		{
			m_tLocalRecvAddress = *ptLocalRecvAddr;
		}
	}
	/**
    * \brief            get local Recv Address
    * \return           PFC_IPADDR.
    */
	PFC_IPADDR* GetLocalRecvAddress()
	{
		return &m_tLocalRecvAddress;
	}

	void SetRemoteRecvAddress( PFC_IPADDR* ptRemoteRecvAddr)
	{
		if (NULL != ptRemoteRecvAddr)
		{
			m_tRemotRecvAddress = *ptRemoteRecvAddr;
		}
	}
	PFC_IPADDR* GetRemoteRecvAddress()
	{
		return &m_tRemotRecvAddress;
	}
	/**
    * \brief            set fecc sample rate
	* \param[in]        wSampleRate     ;sample rate
    * \return           void.
    */
	void SetFeccSampleRate( u16 wSampleRate )
	{
		m_wSampleRate = wSampleRate;
	}
	/**
    * \brief            get fecc sample rate
    * \return           void.
    */
	u16 GetFeccSampleRate()
	{
		return m_wSampleRate;
	}

	/**
    * \brief            Set Send Srtp Setting
	* \param[in]        tSendSrtpSetting     ;srtp setting
    * \return           void.
    */
#ifdef _KDV_SRTP_SUPPORT_
	void SetSendSrtpSetting( TSrtpMediaSetting tSendSrtpSetting )
	{
		m_tSendSrtpSetting = tSendSrtpSetting;
	}
	/**
    * \brief            get Srtp Setting
    * \return           TSrtpMediaSetting.
    */
	TSrtpMediaSetting* GetSendSrtpSetting()
	{
		return &m_tSendSrtpSetting;
	}
	/**
    * \brief            Set Recv Srtp Setting
	* \param[in]        tRecvSrtpSetting     ;srtp setting
    * \return           void.
    */
	void SetRecvSrtpSetting( TSrtpMediaSetting tRecvSrtpSetting )
	{
		m_tRecvSrtpSetting = tRecvSrtpSetting;
	}
	/**
    * \brief            get Srtp Setting
    * \return           TSrtpMediaSetting.
    */
	TSrtpMediaSetting* GetRecvSrtpSetting()
	{
		return &m_tRecvSrtpSetting;
	}
#endif

private:
	emSendRecvAttr m_emSendRecvAttr;        ///< send recv attribute

    /// sendAddr = [LocalSend,RemotRecv], recvAddr = [LocalRecv]
	PFC_IPADDR  m_tRemotRecvAddress;    ///< remote recv address
	PFC_IPADDR	m_tLocalSendAddress;    ///< local send address
	PFC_IPADDR	m_tLocalRecvAddress;    ///< local recv address
	u16 m_wSampleRate;                      ///< sample rate
#ifdef _KDV_SRTP_SUPPORT_
	TSrtpMediaSetting	m_tSendSrtpSetting; ///<send srtp setting
	TSrtpMediaSetting	m_tRecvSrtpSetting; ///<recv srtp setting
#endif
};

/// media line
typedef struct PROTO_API tagMediaLine
{
	emSendRecvAttr	m_emAttr;               ///< send recv attribute
	u8				m_bySndPos;             ///< send postion
	u8				m_byRcvPos;             ///< recv postion
	/**
    * \brief            tagMediaLine Constructor
    * \return           void.
    */
	tagMediaLine()
	{
		m_emAttr	= emSendRecvBegin;
		m_byRcvPos	= 0;
		m_bySndPos	= 0;
	}
}tMediaLine; 

/// rtcp feedback struct
typedef struct PROTO_API tagRtcpFeedbackParam
{
	BOOL32 m_bRtcpFbFir;     ///< cmm fir
	BOOL32 m_bRtcpFbTmmbr;   ///< cmm tmmbr
	BOOL32 m_bRtcpFbPli;     ///< nack pli

public:
	/**
    * \brief            tagRtcpFeedbackParam Constructor
    * \return           void.
    */
	tagRtcpFeedbackParam()
	{
		Clear();
	}
	/**
    * \brief            tagRtcpFeedbackParam init
    * \return           void.
    */
	void Clear()
	{
		m_bRtcpFbFir   = FALSE;   
		m_bRtcpFbTmmbr = FALSE;
		m_bRtcpFbPli   = FALSE;  
	}
}TRtcpFeedbackParam;

/// 信道参数
class PROTO_API CSipMediaStream 
{
public:
    enum { emAVCapNum = 20 };                        ///< av cap number

	/**
    * \brief            CSipMediaStream Constructor
    * \return           void.
    */
	CSipMediaStream();
	/**
    * \brief            CSipMediaStream Constructor
	* \param[in]        emMediaType    :media type
    * \return           void.
    */
	CSipMediaStream( EmSipMediaType emMediaType );
	/**
    * \brief            CSipMediaStream operator =
	* \param[in]        cCopyMedia    :media stream
    * \return           void.
    */
	void operator = (const CSipMediaStream& cCopyMedia);
	/**
    * \brief            CSipMediaStream init
    * \return           void.
    */
	void Clear();
	/**
    * \brief            CSipMediaStream init capset
    * \return           void.
    */
	void ClearCapset();

// 	/**
// 	* \brief            Set local ip type,ipv4 or ipv6
// 	* \param[in]        emIpType            :local ip type
// 	*/
// 	void SetLocalIpType( PFC_TRANSPORT_TYPE emIpType )
// 	{
// 		m_emLocalIpType = emIpType;
// 	}
// 	/**
// 	* \brief            Get local ip type
// 	* \return           PFC_TRANSPORT_TYPE
// 	*/
// 	PFC_TRANSPORT_TYPE GetLocalIpType()
// 	{
// 		return m_emLocalIpType;
// 	}
// 
// 	/**
// 	* \brief            Set local ip
// 	* \param[in]        dwIp                :local ip
// 	*/
// 	void SetLocalIp( u32 dwIp )
// 	{
// 		m_emLocalIpType = PFC_TRANSPORT_TYPE_IP;
// 		m_uLocalIP.m_tIPv4.m_dwIP = dwIp;
// 	}
// 	/**
// 	* \brief            Get local ip
// 	* \return           u32
// 	*/
// 	u32 GetLocalIp()
// 	{
// 		return m_uLocalIP.m_tIPv4.m_dwIP;
// 	}
// 	
// 	/**
// 	* \brief            set local ipv6
// 	* \return           void
// 	*/
// 	void SetLocalIpv6( u8 *pbyipv6 )
// 	{
// 		m_emLocalIpType = PFC_TRANSPORT_TYPE_IPV6;
// 		memcpy(m_uLocalIP.m_tIPv6.m_abyIP ,pbyipv6,PFC_IPV6_ADDR_SIZE);
// 	}
// 	/**
// 	* \brief            Get local ipv6
// 	* \return           u8*
// 	*/
// 	u8* GetLocalIpv6()
// 	{
// 		return m_uLocalIP.m_tIPv6.m_abyIP;
// 	}

	/**
    * \brief            set local rtcp
	* \param[in]        tRtp     :rtp ip,for ipv4 or ipv6
    * \return           void.
    */
	 void SetLocalRtp(PFC_IPADDR tRtp) 
	{
		m_tLocalRtp = tRtp;
	}

    /**
    * \brief            set local rtp
	* \param[in]        wPort    :rtp port
    * \return           void.
    */
	void SetLocalRtp( u32 dwIp, u16 wPort ) 
	{ 
		m_tLocalRtp.m_emType = PFC_TRANSPORT_TYPE_IP;
		m_tLocalRtp.m_tAddr.m_tIPv4.m_dwIP = dwIp;
		m_tLocalRtp.m_wPort	= wPort;
	}

     void SetLocalRtp6(u8 *pbyIpv6, u16 wPort ) 
	 { 
		 if ( NULL == pbyIpv6)
		 {
			 return;
		 }
		 m_tLocalRtp.m_emType = PFC_TRANSPORT_TYPE_IPV6;
		 memcpy(m_tLocalRtp.m_tAddr.m_tIPv6.m_abyIP, pbyIpv6, PFC_IPV6_ADDR_SIZE);
		 m_tLocalRtp.m_wPort = wPort;
	 }
    /**
    * \brief            get local rtp
    * \return           PFC_IPADDR.
    */
	 PFC_IPADDR& GetLocalRtp() 
	{
		return m_tLocalRtp; 
	}

    /**
    * \brief            set local rtcp
	* \param[in]        tRtcp     :rtcp ip,for ipv4 or ipv6
    * \return           void.
    */
	 void SetLocalRtcp(PFC_IPADDR tRtcp) 
	{
		m_tLocalRtcp = tRtcp;
	}

	 /**
    * \brief            set local rtcp
	* \param[in]        dwIP     :rtcp ip
	* \param[in]        wPort    :rtcp port
    * \return           void.
    */
	 void SetLocalRtcp(u32 dwIP, u16 wPort) 
	{
		m_tLocalRtcp.m_emType = PFC_TRANSPORT_TYPE_IP;
		m_tLocalRtcp.m_tAddr.m_tIPv4.m_dwIP = dwIP;
		m_tLocalRtcp.m_wPort	  = wPort;
	}

	
	///< 设置RTCP ipv6参数
	 void SetLocalRtcp6(u8 *pbyIpv6, u16 wPort) 
	 {
		 m_tLocalRtcp.m_emType = PFC_TRANSPORT_TYPE_IPV6;
		 memcpy(m_tLocalRtcp.m_tAddr.m_tIPv6.m_abyIP,pbyIpv6,PFC_IPV6_ADDR_SIZE);
		 m_tLocalRtcp.m_wPort  = wPort;
	 }

    /**
    * \brief            get local rtcp
    * \return           PFC_IPADDR.
    */
	 PFC_IPADDR& GetLocalRtcp() 
	{
		return m_tLocalRtcp; 
	}

	 /**
    * \brief            set local rtcp
	* \param[in]        tRtp     :remote rtp ip,for ipv4 or ipv6
    * \return           void.
    */
	 void SetRemoteRtp(PFC_IPADDR tRtp) 
	{
		m_tRemoteRtp = tRtp;
	}

    /**
    * \brief            set remote rtp
	* \param[in]        dwIp     :rtp ip
	* \param[in]        wPort    :rtp port
    * \return           void.
    */
	 void SetRemoteRtp( u32 dwIp, u16 wPort ) 
	{ 
		m_tRemoteRtp.m_emType = PFC_TRANSPORT_TYPE_IP;
		m_tRemoteRtp.m_tAddr.m_tIPv4.m_dwIP		= dwIp;
		m_tRemoteRtp.m_wPort	                = wPort;
	}

	 ///< 设置RTCP ipv6参数
	 void SetRemoteRtp6(u8 *pbyIpv6, u16 wPort) 
	 {
		 m_tRemoteRtp.m_emType = PFC_TRANSPORT_TYPE_IPV6;
		 memcpy(m_tRemoteRtp.m_tAddr.m_tIPv6.m_abyIP,pbyIpv6,PFC_IPV6_ADDR_SIZE);
		 m_tRemoteRtp.m_wPort  = wPort;
	 }
	 /**
    * \brief            get remote rtp
    * \return           PFC_IPADDR.
    */
	 PFC_IPADDR& GetRemoteRtp() 
	{
		return m_tRemoteRtp; 
	};


    /**
    * \brief            Set Encrypt Type
	* \param[in]        emType     :encrypt type
    * \return           void.
    */
     void SetEncryptType(emEncryptType emType)
	{
		m_emEncryptType = emType; 
	}
     /**
    * \brief            get Encrypt Type
    * \return           emEncryptType.
    */
	 emEncryptType GetEncryptType()
	{
		return m_emEncryptType;
	}
	/**
    * \brief            Set Active PT
	* \param[in]        emActivePT     :Payload Type
    * \return           void.
    */
	 void SetActivePT( PayloadType  emActivePT )
	{
		m_emActivePT = emActivePT;
	}
	/**
    * \brief            Get Active PT
    * \return           PayloadType.
    */
	 PayloadType GetActivePT()
	{
		return m_emActivePT;
	}
	/**
    * \brief            Set Media Type
	* \param[in]        emMediaType     :Media Type
    * \return           void.
    */
	 void SetMediaType( EmSipMediaType emMediaType )
	{
		m_emMediaType = emMediaType;
	}
	/**
    * \brief            Get Media Type
    * \return           EmSipMediaType.
    */
	 EmSipMediaType GetMediaType()
	{
		return m_emMediaType;
	}
	/**
	* \brief            add media
	* \param[in]        emPayloadType          :payload type
	* \param[in]        ptCap                  :cap set
	* \return           BOOL32, TRUE/FALSE
	*/
	 BOOL32 AddMedia( PayloadType emPayloadType, TKdvCapSet *ptCap );
	/**
	* \brief            get media
	* \param[in]        emPayloadType          :payload type
	* \param[in]        ptCap                  :cap set
	* \param[in]        byIndex                :cap set index
	* \return           BOOL32, TRUE/FALSE
	*/
	 BOOL32 GetMedia( PayloadType emPayloadType, TKdvCapSet **ptCap, u8 byIndex = 0);
	 /**
	* \brief            remove all media
	* \return           void.
	*/
	 void RemoveAllMedia();
	/**
	* \brief            remove media
	* \param[in]        emPayloadType          :payload type
	* \param[in]        byIndex                :cap set index
	* \return           BOOL32, TRUE/FALSE
	*/
	 BOOL32 RemoveMedia(PayloadType emPayloadType, u8 byIndex = 0xFF);
	/**
	* \brief            media negotiate
	* \param[in]        emPayloadType          :payload type
	* \param[in]        ptCap                  :cap set 
	* \param[in]        nIndex                 :cap set index
	* \param[in]        pnH26XOrder            :media order
	* \param[in]        bStrictMatch           :is strict match
	* \return           BOOL32, TRUE/FALSE
	*/
	 BOOL32 IsSupport( PayloadType emPayloadType, TKdvCapSet *ptCap, s32 nIndex = -1, s32 *pnH26XOrder = NULL,BOOL32 bStrictMatch=FALSE);
	/**
	* \brief            Get Media PT
	* \param[in]        byIndex                :media index
	* \return           PayloadType
	*/
	 PayloadType GetMediaPT( u8 byIndex )
	{
        if ( byIndex < m_byMediaCount )
			return m_aemMediaPT[byIndex];
		else
			return emPayloadTypeEnd;
	}
	/**
	* \brief            Get Media Count
	* \return           u8
	*/
	u8 GetMediaCount() 
	{
		return m_byMediaCount;
	}
    /**
	* \brief            Set Encrypt Sync
	* \param[in]        tSync                :encrypt sync
	* \return           void
	*/
	void SetEncryptSync( TEncryptSync &tSync)
	{ 
		m_tEncryptSync = tSync; 
	}
    /**
	* \brief            Get Encrypt Sync
	* \return           TEncryptSync
	*/
	TEncryptSync &GetEncryptSync() 
	{ 
		return m_tEncryptSync; 
	} 
	/**
	* \brief            Set Bit Rate
	* \param[in]        nRate                :bit rate
	*/
	void SetBitRate( s32 nRate )
	{
		m_nBitRate = nRate;
		m_tH261Cap.SetBitRate( nRate );
		m_tH263Cap.SetBitRate( nRate );
		m_tH263plusCap.SetBitRate( nRate );
		m_tMpeg4Cap.SetBitRate( nRate );
		m_tH262Cap.SetBitRate( nRate ); 
		u8 i = 0;
		for (i = 0; i < MAX_H264CAP_NUM; i++)
		{
			if (m_atH264Cap[i].GetBitRate() == 0)
			{
				m_atH264Cap[i].SetBitRate(nRate);
			}
		}
		for (i = 0; i < MAX_H265CAP_NUM; i++)
		{
			if (m_atH265Cap[i].GetBitRate() == 0)
			{
				m_atH265Cap[i].SetBitRate(nRate);
			}
		}
	}
	/**
	* \brief            Get Bit Rate
	* \return           s32
	*/
	s32 GetBitRate()
	{
		return m_nBitRate;
	}
	
	/**
	* \brief            is active
	* \return           BOOL32, TRUE/FALSE
	*/
	BOOL32 IsActive()
	{
        return m_bActive;
	}
	/**
	* \brief            Set Active
	* \param[in]        bActive                :flag
	*/
	void SetActive( BOOL32 bActive )
	{
		m_bActive = bActive;
	}
	/**
	* \brief            Set Media PT Array
	* \param[in]        nPos                :postion
	* \param[in]        emSipPT             :payload type
	*/
	void SetMediaPTArray( s32 nPos, PayloadType emSipPT )
	{
		if ( nPos < m_byMediaCount )
		{
			BOOL32 bFind = FALSE;
			for ( s32 i = 0; i< emAVCapNum; ++i )
			{
				if( m_aemMediaPT[i] == emSipPT && emSipPT != emH264 )
				{
					bFind = TRUE;
				}
				else
					continue;
			}
			if ( !bFind )
			{
				m_aemMediaPT[nPos] = emSipPT;
			}
		}
	}
	/**
	* \brief            Set Media Count
	* \param[in]        nCount                :media count
	*/
	void SetMediaCount( s32 nCount )
	{
		m_byMediaCount = nCount;
	}
	/**
	* \brief            Get Screen No
	* \return           s32
	*/
	s32 GetScreenNo()
	{
		return m_nScreenNum;
	}
	/**
	* \brief            Set Screen No
	* \param[in]        nScreenNo                :screen no
	*/
	void SetScreenNo( s32 nScreenNo )
	{
		m_nScreenNum = nScreenNo;
	}
	/**
	* \brief            Get Cap Sign Num
	* \return           s32
	*/
	s32 GetCapSignNum()
	{
		return m_nCapSignNum;
	}
	/**
	* \brief            Set Cap Sign Num
	* \param[in]        nCapSignNum                :cap sign number
	*/
	void SetCapSignNum( s32 nCapSignNum )
	{
		m_nCapSignNum = nCapSignNum;
	}
	/**
	* \brief            Get Cap Sign 
	* \param[in]        nIndex                :cap sign index
	* \return           EmSipCapSign
	*/
	EmSipCapSign GetCapSign( s32 nIndex = 0 )
	{
		return m_aemSipCapSign[nIndex];
	}
	/**
	* \brief            Set Cap Sign 
	* \param[in]        emCapSign                :cap sign type
	* \param[in]        nIndex                   :cap sign index
	*/
	void SetCapSign( EmSipCapSign emCapSign, s32 nIndex = 0 )
	{
		m_aemSipCapSign[nIndex] = emCapSign;
	}
	/**
	* \brief            Set Audio Mix 
	* \param[in]        bAudMix                :flag
	*/
	void SetAudMix(BOOL32 bAudMix)
	{
		m_bAudMix = bAudMix;
	}
	/**
	* \brief            is audio mix
	* \return           BOOL32, TRUE/FALSE
	*/
	BOOL32 IsAudMix()
	{
		return m_bAudMix;
	}

	/**
	* \brief            Set Tp Rtp Address 
	* \param[in]        nIndex                :rtp index
	* \param[in]        tRtpAddr              :rtp address
	*/
	void SetTpRtpAddress( s32 nIndex, PFC_IPADDR tRtpAddr ) 
	{ 
		m_atTpRtpAddr[nIndex] = tRtpAddr;
	}

	/**
	* \brief            Set Tp Rtp Address 
	* \param[in]        nIndex                :rtp index
	* \param[in]        dwIP                  :rtp ip
	* \param[in]        wPort                 :rtp port
	*/
	void SetTpRtpAddress( s32 nIndex, u32 dwIP, u16 wPort ) 
	{ 
		m_atTpRtpAddr[nIndex].m_tAddr.m_tIPv4.m_dwIP = dwIP;
		m_atTpRtpAddr[nIndex].m_wPort = wPort;
	}
	/**
	* \brief            Get Tp Rtp Address 
	* \param[in]        nIndex                :rtp index
	* \return           PFC_IPADDR
	*/
	PFC_IPADDR& GetTpRtpAddress( s32 nIndex ) 
	{
		return m_atTpRtpAddr[nIndex]; 
	}

	/**
	* \brief            Set Tp Rtcp Address 
	* \param[in]        nIndex                :rtcp index
	* \param[in]        tRtcpAddr             :rtcp address
	*/
	void SetTpRtcpAddress( s32 nIndex, PFC_IPADDR tRtcpAddr ) 
	{ 
		m_atTpRtcpAddr[nIndex] = tRtcpAddr;
	}

	/**
	* \brief            Set Tp Rtcp Address 
	* \param[in]        nIndex                :rtp index
	* \param[in]        dwIP                  :rtp ip
	* \param[in]        wPort                 :rtp port
	*/
	void SetTpRtcpAddress( s32 nIndex, u32 dwIP, u16 wPort ) 
	{ 
		m_atTpRtcpAddr[nIndex].m_tAddr.m_tIPv4.m_dwIP = dwIP;
		m_atTpRtcpAddr[nIndex].m_wPort = wPort;
	}
	/**
	* \brief            Get Tp Rtcp Address 
	* \param[in]        nIndex                :rtp index
	* \return           PFC_IPADDR
	*/
	PFC_IPADDR& GetTpRtcpAddress( s32 nIndex ) 
	{
		return m_atTpRtcpAddr[nIndex]; 
	}
	/**
	* \brief            Set Sip Content Attr 
	* \param[in]        emSipContentAttr                :sip content attribute
	*/
	void SetSipContentAttr( EmSipContentAttr emSipContentAttr)
	{
		m_emSipContent = emSipContentAttr;
	}
	/**
	* \brief            Get Sip Content Attr 
	* \return           EmSipContentAttr                
	*/
	EmSipContentAttr GetSipContentAttr()
	{
		return m_emSipContent;
	}
	/**
	* \brief            Set Sip Media Label
	* \param[in]        nSipMediaLabel                :sip media label
	*/
	void SetSipMediaLabel( s32 nSipMediaLabel )
	{
		m_nSipMediaLabel = nSipMediaLabel;
	}
	/**
	* \brief            Get Sip Media Label 
	* \return           s32                
	*/
	s32 GetSipMediaLabel()
	{
		return m_nSipMediaLabel;
	}
	/**
	* \brief            Set H264 Capset Number
	* \param[in]        byNum                :number
	*/
	void SetH264CapsetNumber( u8 byNum )
	{
		m_byH264CapNum = byNum;
	}
	/**
	* \brief            Set H264 Capset Number 
	* \return           u8                
	*/
	u8 GetH264CapsetNumber()
	{
		return m_byH264CapNum;
	}
	/**
	* \brief            Add H264Capset Number
	*/
	void AddH264CapsetNumber()
	{
		m_byH264CapNum++;
	}
	/**
	* \brief            Set H264 Capset Order
	* \param[in]        nIndex                :H264 capset index
	* \param[in]        byOrder               :H264 capset order
	*/
	void SetH264CapsetOrder( s32 nIndex, u8 byOrder )
	{
		m_abyH264CapOrder[nIndex] = byOrder;
	}
	/**
	* \brief            Get H264 Capset Order 
	* \param[in]        nIndex                :H264 capset index
	* \return           u8                
	*/
	u8 GetH264CapsetOrder( s32 nIndex )
	{
		return m_abyH264CapOrder[nIndex+1];
	}
	/**
	* \brief            Set Extmap Audio Level
	* \param[in]        emDirect           :send recv attribute
	* \param[in]        byId               :audio level
	* \param[in]        bVadOn             :audio level vad on
	*/
	void SetExtmapAudioLevel(emSendRecvAttr emDirect, u8 byId, BOOL32 bVadOn)
	{
		m_emAudLvlDirect = emDirect;
		m_byAudLvlId = byId;
		m_bAudLvlVadOn = bVadOn;
	}
	/**
	* \brief            Get Extmap Audio Level
	* \param[in]        emDirect           :send recv attribute
	* \param[in]        byId               :audio level
	* \param[in]        bVadOn             :audio level vad on
	*/
	void GetExtmapAudioLevel(emSendRecvAttr &emDirect, u8 &byId, BOOL32 &bVadOn)
	{
		emDirect = m_emAudLvlDirect;
		byId = m_byAudLvlId;
		bVadOn = m_bAudLvlVadOn;
	}

	/**
	* \brief            Set H265 Capset Number
	* \param[in]        byNum                :number
	*/
	void	SetH265CapsetNumber(u8 byNum){ m_byH265CapNum = byNum;}
	/**
	* \brief            Get H265 Capset Number 
	* \return           u8                
	*/
	u8		GetH265CapsetNumber(){return m_byH265CapNum;}
	/**
	* \brief            Add H265Capset Number
	*/
	void	AddH265CapsetNumber(){m_byH265CapNum++;}
	/**
	* \brief            Set H265 Capset Order
	* \param[in]        nIndex                :H264 capset index
	* \param[in]        byOrder               :H264 capset order
	*/
	void	SetH265CapsetOrder(s32 nIndex, u8 byOrder){m_abyH265CapOrder[nIndex] = byOrder;}
	/**
	* \brief            Get H265 Capset Order 
	* \param[in]        nIndex                :H264 capset index
	* \return           u8                
	*/
	u8		GetH265CapsetOrder(s32 nIndex){return m_abyH265CapOrder[nIndex];}
	/**
	* \brief            Set Bitrate Percent
	* \param[in]        byPercent                :bitrate percent
	*/
	void SetBitratePercent(u8 byPercent){ m_byBitratePercent = byPercent; }
	/**
	* \brief            Get Bitrate Percent 
	* \return           u8                
	*/
	u8 GetBitratePercent(){ return m_byBitratePercent; }

#ifdef _KDV_SRTP_SUPPORT_
	/**
	* \brief            Set Srtp Media Setting
	* \param[in]        ptSetting                :Srtp Media Setting
	*/
	void SetSrtpMediaSetting(TSrtpMediaSetting *ptSetting)
	{
		m_tSrtpSetting = *ptSetting;
	}
	/**
	* \brief            Get Srtp Media Setting
	* \return           TSrtpMediaSetting                
	*/
	TSrtpMediaSetting *GetSrtpMediaSetting()
	{
		return &m_tSrtpSetting;
	}
#endif
	/**
	* \brief            rtcp feedback mode set function
	* \param[in]        ptRtcpFb                :Rtcp Feedback Param
	*/
	void SetFeedbackParam(const TRtcpFeedbackParam* ptRtcpFb)
	{
		MEMCPY_CAST(&m_tRtcpFb, ptRtcpFb, sizeof(TRtcpFeedbackParam));
	}
	/**
	* \brief            rtcp feedback mode get function
	* \return           TRtcpFeedbackParam    
	*/
	TRtcpFeedbackParam* GetFeedbackParam()
	{
		return &m_tRtcpFb;
	}

	void SetRtcpMux(BOOL32 bRtcpMux)
    {
    m_bRtcpMux = bRtcpMux;
    }
    /**
    * \brief            get rtcp mux state
    * \return           BOOL32 :if set Rtcp MUX
    */
    BOOL32 GetRtcpMux()
    {
    return m_bRtcpMux;
    }

private:
	BOOL32				m_bActive;                         ///< is active
	EmSipMediaType		m_emMediaType;                     ///< media type
  
	//local ip 去掉，
//	PFC_TRANSPORT_TYPE  m_emLocalIpType;               ///< local ip type
//	PFC_IPADDR_UNION    m_uLocalIP;                    ///< local ip,for ipv4 and ipv6

	PFC_IPADDR		    m_tLocalRtp;                       ///< local rtp,for ipv4 and ipv6
	PFC_IPADDR		    m_tLocalRtcp;		               ///< combine m_tSendRtcp with m_tRecvRtcp into a new TTransAddress m_tLocalRtcp, double checked with Lijing
	PFC_IPADDR		    m_tRemoteRtp;                      ///< remote rtp,for ipv4 and ipv6

	PayloadType			m_aemMediaPT[emAVCapNum];          ///< media payload type
	u8					m_byMediaCount;                    ///< media count

	TKdvVideoCap		m_tH261Cap;                        ///< H261 cap
	TKdvVideoCap		m_tH263Cap;                        ///< H263 cap
	TKdvVideoCap		m_tH263plusCap;                    ///< H263 plus cap
	TKdvVideoCap		m_tMpeg4Cap;                       ///< mpeg4 cap
	TKdvVideoCap		m_tH262Cap;                        ///< H262 cap
	u8					m_byH264CapNum;	                   ///< H264 cap number 
	u8					m_abyH264CapOrder[MAX_H264CAP_NUM];///< H264 cap order
	TKdvH264VideoCap	m_atH264Cap[MAX_H264CAP_NUM];      ///< H264 cap array

	TKdvAudioCap		m_tG711u;                          ///< G711u audio cap
	TKdvAudioCap		m_tG711a;                          ///< G711a audio cap
	TKdvAudioCap		m_tG722;                           ///< G722 audio cap
	TKdvAudioCap		m_tG728;                           ///< G728 audio cap
	TKdvAudioCap		m_tG729;                           ///< G729 audio cap
	TKdvAudioCap		m_tMP3;                            ///< mp3 audio cap
	TKdvAudioCap		m_tG723;                           ///< G723 audio cap
 	TKdvAudioCap		m_tG719;                           ///< G719 audio cap
	TKdvTelephoneEventCap		m_tTelephoneEvent;         ///< telephone event cap
	TKdvG7231Cap		m_tG7231;                          ///< G7231 cap
	 
	TKdvG7221Cap		m_atG7221[MAX_G7221CAP_NUM];       ///< G7221 cap
	u8					m_abyG7221MediaToCap[emAVCapNum];  ///< G7221 media to cap
	u8					m_byG7221CapNum;                   ///< G7221 cap set number 

	TKdvOpusCap			m_tOpus;                           ///< opus cap

	TKdvAACCap			m_atAaclc[MAX_AAC_CAP_NUM];		   ///< aaclc数组
	u8					m_bylcNum;						   ///< 数组大小
	u8					m_abylcMediaToCap[emAVCapNum];	   ///< 是当前m_byMediaCount的索引 对应到aaclc数组的索引
	TKdvAACCap			m_atAacld[MAX_AAC_CAP_NUM];        ///< aacld array
	u8					m_byldNum;                         ///< aacld number
	u8					m_abyldMediaToCap[emAVCapNum];     ///< av cap number

	TKdvRedCap			m_tRed;			///< Red cap
 

	// H.265 video capabilties
	TKdvH265VideoCap	m_atH265Cap[MAX_H265CAP_NUM];      ///< H265 cap
	u8					m_byH265CapNum;                    ///< H265 capset number
	u8					m_abyH265CapOrder[MAX_H265CAP_NUM];///< H265 capset order

	//TODO:no needed,delete it
	PayloadType			m_emActivePT;                      ///< acive payload type

	emEncryptType		m_emEncryptType;	               ///< 加密类型
	TEncryptSync		m_tEncryptSync;		               ///< master需设置此结构
	s32					m_nBitRate;                        ///< bit rate

	/// 用于网真
	s32					m_nScreenNum;                      ///< screen number
	s32					m_nCapSignNum;                     ///< cap sign number
	BOOL32				m_bAudMix;			               ///< 是否混音
	EmSipCapSign		m_aemSipCapSign[emSipCapEnd];      ///< cap sign
	PFC_IPADDR		    m_atTpRtpAddr[emSipCapEnd];        ///< rtp address
	PFC_IPADDR		    m_atTpRtcpAddr[emSipCapEnd];       ///< rtcp address

	/// 用于BFCP，添加content和label属性
	EmSipContentAttr    m_emSipContent;                    ///< sip content attribute
	s32                 m_nSipMediaLabel;                  ///< sip media label

	/// extmap扩展（audio-level）
	emSendRecvAttr m_emAudLvlDirect;                       ///< send recv attribute
	u8             m_byAudLvlId;                           ///< audio level id
	BOOL32         m_bAudLvlVadOn;                         ///< audio level vadon
	
	/// 终端平台对通非标（带宽比率）
	u8 m_byBitratePercent;                                 ///< bitrate percent
#ifdef _KDV_SRTP_SUPPORT_
	TSrtpMediaSetting	m_tSrtpSetting;                    ///< srtp settting
#endif
	
	TRtcpFeedbackParam  m_tRtcpFb;                         ///< rtcp feedback mode
	BOOL32              m_bRtcpMux;                        ///< rtcp port mux
};

/// audio video capset
class PROTO_API CAudVidCapSet
{
public:
	/**
    * \brief            CAudVidCapSet Constructor
    * \return           void.
    */
	CAudVidCapSet();

public:
	/**
    * \brief            CAudVidCapSet init
	* \param[in]        bOnlyComCap                :only common cap
    * \return           void.
    */
	void Clear( BOOL32 bOnlyComCap = FALSE );

	/**
    * \brief            whether media support some format
	* \param[in]        emPayloadType                :payload type
	* \param[in]        ptSupportCapset              :support cap set
	* \param[in]        bRecv                        :is recv 
	* \param[in]        nVideoSequence               :video sequence
    * \return           BOOL32, TRUE/FALSE
    */
	BOOL32 IsSupportCapset( PayloadType emPayloadType, TKdvCapSet *ptSupportCapset, BOOL32 bRecv, s32 nVideoSequence=0 );
	/**
    * \brief            add one format to a media
	* \param[in]        emPayloadType                :payload type
	* \param[in]        ptCap                        :support cap set
	* \param[in]        bRecv                        :is recv 
	* \param[in]        nVideoSequence               :video sequence
    */
	void AddCapSetToMedia( PayloadType emPayloadType, TKdvCapSet *ptCap, BOOL32 bRecv, int nVideoSequence = 0 );

	/**
    * \brief            determine which payload to be transmitted
	* \param[in]        emPayloadType                :payload type
	* \param[in]        bRecv                        :is recv 
	* \param[in]        nVideoSequence               :video sequence
    */
	void SetMediaActivePT( PayloadType emPayloadType, BOOL32 bRecv, int nVideoSequence = 0  );
	/**
    * \brief            Get Video Send Stream Count
    * \return           s32
    */
	s32 GetVideoSendStreamCount(){ return m_nVideoSendStreamCount;	}
	/**
    * \brief            Get Video Recv Stream Count
    * \return           s32
    */
	s32 GetVideoRecvStreamCount(){ return m_nVideoRecvStreamCount;	}
	/**
    * \brief            Set Video Recv Stream Count
	* \param[in]        nCount                :video recv stream count
    */
	void SetVideoRecvStreamCount( s32 nCount )
	{
		if ( nCount > SIP_MAX_VIDEO_STREAM_COUNT )
		{
			m_nVideoRecvStreamCount = SIP_MAX_VIDEO_STREAM_COUNT;
			return;
		}
		m_nVideoRecvStreamCount = nCount;
	}
	/**
    * \brief            Set Video Send Stream Count
	* \param[in]        nCount                :video send stream count
    */
	void SetVideoSendStreamCount( s32 nCount )
	{
		if ( nCount > SIP_MAX_VIDEO_STREAM_COUNT )
		{
			m_nVideoSendStreamCount = SIP_MAX_VIDEO_STREAM_COUNT;
			return;
		}
		m_nVideoSendStreamCount = nCount;
	}
	/**
    * \brief            Increasing Send Video Stream
    */
	void IncreasingSendVideoStream()
	{ 
		if ( m_nVideoSendStreamCount + 1 <= SIP_MAX_VIDEO_STREAM_COUNT )
		{
			m_nVideoSendStreamCount++; 
		}
	}
	/**
    * \brief            Increasing Recv Video Stream
    */
	void IncreasingRecvVideoStream()
	{ 
		if ( m_nVideoRecvStreamCount + 1 <= SIP_MAX_VIDEO_STREAM_COUNT )
		{
			m_nVideoRecvStreamCount++; 
		}
	}
	/**
    * \brief            Get Audio Send Stream Count
    * \return           s32
    */
	s32 GetAudioSendStreamCount(){ return m_nAudioSendStreamCount;}
	/**
    * \brief            Get Audio Recv Stream Count
    * \return           s32
    */
	s32 GetAudioRecvStreamCount(){ return m_nAudioRecvStreamCount;}
	/**
    * \brief            Set Audio Recv Stream Count
	* \param[in]        nCount                :Audio Recv Stream Count
    */
	void SetAudioRecvStreamCount( s32 nCount )
	{
		if ( nCount > SIP_MAX_AUDIO_STREAM_COUNT )
		{
			m_nAudioRecvStreamCount = SIP_MAX_AUDIO_STREAM_COUNT;
			return;
		}
		m_nAudioRecvStreamCount = nCount;
	}
	/**
    * \brief            Set Audio Send Stream Count
	* \param[in]        nCount                :Audio Send Stream Count
    */
	void SetAudioSendStreamCount( s32 nCount )
	{
		if ( nCount > SIP_MAX_AUDIO_STREAM_COUNT )
		{
			m_nAudioSendStreamCount = SIP_MAX_AUDIO_STREAM_COUNT;
			return;
		}
		m_nAudioSendStreamCount = nCount;
	}
	/**
    * \brief            Increasing Send Audio Stream
    */
	void IncreasingSendAudioStream()
	{ 
		if ( m_nAudioSendStreamCount + 1 <= SIP_MAX_AUDIO_STREAM_COUNT )
		{
			m_nAudioSendStreamCount++; 
		}
	}
	/**
    * \brief            Increasing Recv Audio Stream
    */
	void IncreasingRecvAudioStream()
	{ 
		if ( m_nAudioRecvStreamCount + 1 <= SIP_MAX_AUDIO_STREAM_COUNT )
		{
			m_nAudioRecvStreamCount++; 
		}
	}
	/**
    * \brief            Get Media Line Pos by Send Pos
	* \param[in]        bySndPos                :send postion
	* \param[in]        bVideo                  :is video
    * \return           u32
    */
	s32 GetMediaLinePosbySendPos(u8 bySndPos, BOOL32 bVideo = TRUE)
	{
		if(bVideo)
		{
			for(u32 dwIndex = 0; dwIndex< m_dwVideoNum; dwIndex++)
			{
				if(m_atVidSndRcv[dwIndex].m_emAttr == emSendOnly || m_atVidSndRcv[dwIndex].m_emAttr == emSendRecv)
				{
					if(bySndPos == m_atVidSndRcv[dwIndex].m_bySndPos )
						return dwIndex;	
				}
			}
		}
		else
		{
			for(u32 dwIndex = 0; dwIndex< m_dwAudioNum; dwIndex++)
			{
				if(m_atAudSndRcv[dwIndex].m_emAttr == emSendOnly || m_atAudSndRcv[dwIndex].m_emAttr == emSendRecv)
				{
					if(bySndPos == m_atAudSndRcv[dwIndex].m_bySndPos )
						return dwIndex;	
				}
			}
		}

		return -1;
	}
	/**
    * \brief            Get Media Line Pos by Recv Pos
	* \param[in]        byRecvPos               :Recv  postion
	* \param[in]        bVideo                  :is video
    * \return           u32
    */
	s32 GetMediaLinePosbyRecvPos(u8 byRecvPos, BOOL32 bVideo = TRUE)
	{
		if(bVideo)
		{
			for(u32 dwIndex = 0; dwIndex < m_dwVideoNum; dwIndex++)
			{
				if(m_atVidSndRcv[dwIndex].m_emAttr == emRecvOnly || m_atVidSndRcv[dwIndex].m_emAttr == emSendRecv)
				{
					if(byRecvPos == m_atVidSndRcv[dwIndex].m_byRcvPos )
						return dwIndex;	
				}
			}
		}
		else 
		{
			for(u32 dwIndex = 0; dwIndex< m_dwAudioNum; dwIndex++)
			{
				if(m_atAudSndRcv[dwIndex].m_emAttr == emRecvOnly || m_atAudSndRcv[dwIndex].m_emAttr == emSendRecv)
				{
					if(byRecvPos == m_atAudSndRcv[dwIndex].m_byRcvPos )
						return dwIndex;	
				}
			}
		}

		return -1;
	}
	/**
    * \brief            Get Media Line
	* \param[in]        dwCount               :video count
	* \param[in]        bIfVideo              :is video
    * \return           tMediaLine
    */
	tMediaLine* GetMediaLine( u32 dwCount, BOOL32 bIfVideo = FALSE )
	{
		if ( bIfVideo)
		{
			if ( dwCount >= SIP_MAX_VIDEO_STREAM_COUNT * 2 )
				return NULL;
			else
				return &(m_atVidSndRcv[dwCount]);
		}
		else
		{
			if ( dwCount >= SIP_MAX_AUDIO_STREAM_COUNT * 2 )
				return NULL;
			else
				return &(m_atAudSndRcv[dwCount]);
		}
	}
	/**
	* \brief            Set Media Line
	* \param[in]        dwCount     :media count
	* \param[in]        emAttr      :media attribute
	* \param[in]        bySndPos    :media send position
	* \param[in]        byRcvPos    :media recv position
	* \param[in]        bIfVideo    :is video
	* \return           BOOL32, TRUE/FALSE
	*/
	BOOL32 SetMediaLine( u32 dwCount, emSendRecvAttr emAttr, u8 bySndPos, u8 byRcvPos, BOOL32 bIfVideo = FALSE )
	{
		if ( bIfVideo)
		{
			if ( dwCount >= SIP_MAX_VIDEO_STREAM_COUNT * 2 )
				return FALSE;
			else
			{
				m_atVidSndRcv[dwCount].m_emAttr = emAttr;
				m_atVidSndRcv[dwCount].m_bySndPos = bySndPos;
				m_atVidSndRcv[dwCount].m_byRcvPos = byRcvPos;
			}
		}
		else
		{
			if ( dwCount >= SIP_MAX_AUDIO_STREAM_COUNT*2 )
				return FALSE;
			else
			{
				m_atAudSndRcv[dwCount].m_emAttr = emAttr;
				m_atAudSndRcv[dwCount].m_bySndPos = bySndPos;
				m_atAudSndRcv[dwCount].m_byRcvPos = byRcvPos;
			}
		}

		return TRUE;
	}
	/**
	* \brief            Set audio number
	* \param[in]        AudioNum     :audio count
	* \return           BOOL32, TRUE/FALSE
	*/
	BOOL32 SetAudioNum(u32 AudioNum)
	{
		if ( AudioNum > SIP_MAX_AUDIO_STREAM_COUNT * 2 )
			return FALSE;
		m_dwAudioNum = AudioNum;

		return TRUE;
	}
	/**
	* \brief            Get audio number
	* \return           u32
	*/
	u32 GetAudioNum()
	{
		return m_dwAudioNum;
	}
	/**
	* \brief            Set Video number
	* \param[in]        VideoNum     :Video count
	* \return           BOOL32, TRUE/FALSE
	*/
	BOOL32 SetVideoNum(u32 VideoNum)
	{
		if ( VideoNum > SIP_MAX_VIDEO_STREAM_COUNT * 2 )
			return FALSE;
		m_dwVideoNum = VideoNum;
			return TRUE;
	}
	/**
	* \brief            Get Video number
	* \return           u32
	*/
	u32 GetVideoNum()
	{
		return m_dwVideoNum;
	}

	/**
	* \brief            get some media stream of a dialog
	* \param[in]        emMediaType     :media type
	* \param[in]        nSequence       :media sequence
	* \return           CSipMediaStream
	*/
	CSipMediaStream* GetSendMediaStream( EmSipMediaType emMediaType, s32 nSequence = 0);
	/**
	* \brief            get some media stream of a dialog
	* \param[in]        emMediaType     :media type
	* \param[in]        nSequence       :media sequence
	* \return           CSipMediaStream
	*/
	CSipMediaStream* GetRecvMediaStream( EmSipMediaType emMediaType, s32 nSequence = 0);
	/**
	* \brief            Set Local Vedio IP
	* \param[in]        tIp           :ip
	* \param[in]        nSequence     :Video sequence
	* \return           BOOL32, TRUE/FALSE
	*/
	BOOL32 SetLocalVedioRtp( PFC_IPADDR tIp, s32 nSequence );
	/**
	* \brief            Set Local Audio IP
	* \param[in]        tIp           :ip
	* \param[in]        nSequence     :Audio sequence
	* \return           BOOL32, TRUE/FALSE
	*/
	BOOL32 SetLocalAudioRtp( PFC_IPADDR tIp, s32 nSequence );

private:
	
	CSipMediaStream		m_acAudioSendStream[SIP_MAX_AUDIO_STREAM_COUNT]; ///< Audio Send Stream
	s32					m_nAudioSendStreamCount;                         ///< Audio Send Stream Count
	CSipMediaStream		m_acAudioRecvStream[SIP_MAX_AUDIO_STREAM_COUNT]; ///< Audio Recv Stream
	s32					m_nAudioRecvStreamCount;                         ///< Audio Recv Stream Count
	tMediaLine			m_atAudSndRcv[SIP_MAX_AUDIO_STREAM_COUNT * 2];   ///< Audio send and recv Stream
	u32					m_dwAudioNum;                                    ///< Audio Snumber

	CSipMediaStream		m_acVideoSendStream[SIP_MAX_VIDEO_STREAM_COUNT]; ///< Video Send Stream
	s32					m_nVideoSendStreamCount;                         ///< Video Send Stream Count          
	CSipMediaStream		m_acVideoRecvStream[SIP_MAX_VIDEO_STREAM_COUNT]; ///< Video Recv Stream
	s32					m_nVideoRecvStreamCount;                         ///< Video Recv Stream Count
	tMediaLine			m_atVidSndRcv[SIP_MAX_VIDEO_STREAM_COUNT * 2];   ///< Video send and recv Stream
	u32					m_dwVideoNum;                                    ///< Video Snumber
};

/// sip capset
class PROTO_API CSipCapSet
{
public:
	/**
    * \brief            CSipCapSet Constructor
    * \return           void.
    */
	CSipCapSet();

public:
	/**
    * \brief            CSipCapSet init
    * \return           void.
    */
	void Clear();
	/**
	* \brief            Set Main Capset
	* \param[in]        ptCap          :audio and video capset
	*/
	void SetMainCapset(CAudVidCapSet *ptCap);
	/**
	* \brief            Get Main Capset
	* \return           CAudVidCapSet.
	*/
	CAudVidCapSet *GetMainCapset();
	/**
	* \brief            Set Dual Capset
	* \param[in]        ptCap          :audio and video dual capset
	*/
	void SetDualCapset(CAudVidCapSet *ptCap);
	/**
	* \brief            Get Dual Capset
	* \return           CAudVidCapSet.
	*/
	CAudVidCapSet *GetDualCapset();
	/**
	* \brief            Set Bfcp Media
	* \param[in]        ptBfcpMedia          :Set Bfcp Media
	*/
	void SetBfcpMedia(CBfcpMediaStream *ptBfcpMedia);
	/**
	* \brief            Get Bfcp Media
	* \return           CBfcpMediaStream.
	*/
	CBfcpMediaStream* GetBfcpMedia	();
	/**
	* \brief            Set fecc Media
	* \param[in]        ptFeccMedia          :Set fecc Media
	*/
	void SetFeccMedia(CFeccMediaStream *ptFeccMedia);
	/**
	* \brief            Get Bfecc Media
	* \return           CFeccMediaStream.
	*/
	CFeccMediaStream* GetFeccMedia();
	/**
	* \brief            Set Sip Msg Type
	* \param[in]        emType          :Set message type
	*/
	void SetSipMsgType( EmSipMsgType emType );
	/**
	* \brief            Set Sip Msg Type
	* \return           EmSipMsgType.
	*/
	EmSipMsgType GetSipMsgType();

	/**
	* \brief            set dialog bandwidth
	* \param[in]        nBandWidth          :dialog bandwidth
	*/
	void SetBandwidth( s32 nBandWidth );
	/**
	* \brief            get dialog bandwidth
	* \return           s32.
	*/
	s32  GetBandwidth();

	/**
	* \brief            Set Local Ip type
	* \param[in]        emIpType          :local ip type
	*/
	void SetLocalIpType( PFC_TRANSPORT_TYPE emIpType );
	/**
	* \brief            get local ip type
	* \return           u32.
	*/
	PFC_TRANSPORT_TYPE  GetLocalIpType();

	/**
	* \brief            Set Local Ip addr(Reserved interface, temporarily not used)
	* \param[in]        uLocalIpAddr         :local ip,for ipv4 or ipv6
	*/
	void SetLocalIpAddr( PFC_IPADDR_UNION uLocalIpAddr );

	/**
	* \brief            Get Local Ip addr
	* \return           PFC_IPADDR_UNION         :local ip,for ipv4 or ipv6
	*/
	PFC_IPADDR_UNION GetLocalIpAddr();

	/**
	* \brief            Set Local Ipv4 and type_ipv4 (Set Local ipv4 to use this function)
	* \param[in]        dwIp          :local ip
	*/
	void SetLocalIp( u32 dwIp );

	/**
	* \brief            get local ip
	* \return           u32.
	*/
	u32  GetLocalIp();
	
	/**
	* \brief            Set Local Ipv6 and type_ipv6(Set Local ipv6 to use this function)
	* \param[in]        dwIp          :local ipv6
	*/
	void SetLocalIpv6( u8* pbyIp);

	/**
	* \brief            get local ipv6
	* \return           u8* .
	*/
	u8*  GetLocalIpv6();
		/**
	* \brief        natIp : static natip
	* \return           void
	*/
	void SetLocalIp(PFC_IPADDR tIp);

	/**
	* \brief            Set Cap Order
	* \param[in]        nIndex          :cap index 
	* \param[in]        emOrder         :cap order
	*/
	void SetCapOrder(s32 nIndex, EmCapOrder emOrder);
	/**
	* \brief            Get Cap Order
	* \return           EmCapOrder.
	*/
	EmCapOrder GetCapOrder(s32 nIndex);
	/**
	* \brief            Set Nat Type
	* \param[in]        nNatType          :nat type
	*/
	void SetNatType(s32 nNatType);
	/**
	* \brief            get Nat Type
	* \return           s32.
	*/
	s32 GetNatType();

	/**
	* \brief            Set Peer Vendor Id
	* \param[in]        emVendorId          :Vendor Id 
	*/
	void SetPeerVendorId(EmVendorProductId emVendorId);
	/**
	* \brief            Get Peer Vendor Id
	* \return           EmVendorProductId.
	*/
	EmVendorProductId GetPeerVendorId();
	/**
	* \brief            Set Sip Dual Media Label
	* \param[in]        nDualMediaLabel          :Dual Media Label
	*/
	void SetSipDualMediaLabel(s32 nDualMediaLabel);
	/**
	* \brief            Get Sip Dual Media Label
	* \return           s32.
	*/
	s32  GetSipDualMediaLabel();

private:
	
	CAudVidCapSet		m_cMainCapset;   ///< Main Stream	
	CAudVidCapSet		m_cDualCapset;   ///< Slide Stream
	CBfcpMediaStream	m_cBfcpStream;   ///< BFCP Stream
	CFeccMediaStream	m_cFeccStream;   ///< FECC Stream
	
	EmSipMsgType		m_emSipType;     ///< SIP Message type(invite/200OK/ack)

	s32					m_nBandWidth;   ///< band width

	PFC_TRANSPORT_TYPE  m_emLocalIpType;      ///< transport type
	PFC_IPADDR_UNION    m_uLocalIpAddr;       ///< IP address,for ipv4 or ipv6

	s32					m_nNatType;     ///< nat type
	EmCapOrder			m_aemOrders[SIP_MAX_MEDIA_NUM]; ///< media number
	EmVendorProductId   m_emPeerVendorId;               ///< peer vendor id
	s32                 m_nDualMediaLabel;              ///< dual media label
	
};

class PROTO_API CSipAudioAlterCap 
{
public:
	enum { emAudioCapNum = 20 };                        ///< audio cap number

	CSipAudioAlterCap()
	{
		Clear();
	}

	void Clear();

	void operator = (const CSipAudioAlterCap& cCopyCap);

	/**
	* \brief            add media
	* \param[in]        emPayloadType          :payload type
	* \param[in]        ptCap                  :cap set
	* \return           BOOL32, TRUE/FALSE
	*/
	 BOOL32 AddMedia( PayloadType emPayloadType, TKdvCapSet *ptCap );
	/**
	* \brief            get media
	* \param[in]        emPayloadType          :payload type
	* \param[in]        ptCap                  :cap set
	* \param[in]        byIndex                :cap set index
	* \return           BOOL32, TRUE/FALSE
	*/
	 BOOL32 GetMedia( PayloadType emPayloadType, TKdvCapSet **ptCap, u8 byIndex = 0);
	 /**
	* \brief            remove all media
	* \return           void.
	*/
	 void RemoveAllMedia();
	/**
	* \brief            remove media
	* \param[in]        emPayloadType          :payload type
	* \param[in]        byIndex                :cap set index
	* \return           BOOL32, TRUE/FALSE
	*/
	 BOOL32 RemoveMedia(PayloadType emPayloadType, u8 byIndex = 0xFF);
	/**
	* \brief            media negotiate
	* \param[in]        emPayloadType          :payload type
	* \param[in]        ptCap                  :cap set 
	* \param[in]        nIndex                 :cap set index
	* \param[in]        pnH26XOrder            :media order
	* \param[in]        bStrictMatch           :is strict match
	* \return           BOOL32, TRUE/FALSE
	*/
	 BOOL32 IsSupport( PayloadType emPayloadType, TKdvCapSet *ptCap);
	/**
	* \brief            Get Media PT
	* \param[in]        byIndex                :media index
	* \return           PayloadType
	*/
	 PayloadType GetMediaPT( u8 byIndex )
	{
        if ( byIndex < m_byMediaCount )
			return m_aemMediaPT[byIndex];
		else
			return emPayloadTypeEnd;
	}
	/**
	* \brief            Get Media Count
	* \return           u8
	*/
	u8 GetMediaCount() 
	{
		return m_byMediaCount;
	}
	
	/**
	* \brief            Set Media PT Array
	* \param[in]        nPos                :postion
	* \param[in]        emSipPT             :payload type
	*/
	void SetMediaPTArray( s32 nPos, PayloadType emSipPT )
	{
		if ( nPos < m_byMediaCount )
		{
			BOOL32 bFind = FALSE;
			for ( s32 i = 0; i< emAudioCapNum; ++i )
			{
				if( m_aemMediaPT[i] == emSipPT && emSipPT != emH264 )
				{
					bFind = TRUE;
				}
				else
					continue;
			}
			if ( !bFind )
			{
				m_aemMediaPT[nPos] = emSipPT;
			}
		}
	}
	/**
	* \brief            Set Media Count
	* \param[in]        nCount                :media count
	*/
	void SetMediaCount( s32 nCount )
	{
		m_byMediaCount = nCount;
	}


private:
	PayloadType			m_aemMediaPT[emAudioCapNum];          ///< media payload type
	u8					m_byMediaCount;                    ///< media count

	TKdvAudioCap		m_tG711u;                          ///< G711u audio cap
	TKdvAudioCap		m_tG711a;                          ///< G711a audio cap
	TKdvAudioCap		m_tG722;                           ///< G722 audio cap
	TKdvAudioCap		m_tG728;                           ///< G728 audio cap
	TKdvAudioCap		m_tG729;                           ///< G729 audio cap
	TKdvAudioCap		m_tMP3;                            ///< mp3 audio cap
	TKdvAudioCap		m_tG723;                           ///< G723 audio cap
	TKdvAudioCap		m_tG719;                           ///< G719 audio cap
	TKdvTelephoneEventCap		m_tTelephoneEvent;         ///< telephone event cap
	TKdvG7231Cap		m_tG7231;                          ///< G7231 cap

	TKdvG7221Cap		m_atG7221[MAX_G7221CAP_NUM];       ///< G7221 cap
	u8					m_abyG7221MediaToCap[emAudioCapNum];  ///< G7221 media to cap
	u8					m_byG7221CapNum;                   ///< G7221 cap set number 

	TKdvOpusCap			m_tOpus;                           ///< opus cap

	TKdvAACCap			m_atAaclc[MAX_AAC_CAP_NUM];		   ///< aaclc数组
	u8					m_bylcNum;						   ///< 数组大小
	u8					m_abylcMediaToCap[emAudioCapNum];	   ///< 是当前m_byMediaCount的索引 对应到aaclc数组的索引
	TKdvAACCap			m_atAacld[MAX_AAC_CAP_NUM];        ///< aacld array
	u8					m_byldNum;                         ///< aacld number
	u8					m_abyldMediaToCap[emAudioCapNum];     ///< av cap number
	TKdvRedCap			m_tRed;

}PACKED;

class PROTO_API CSipAVStreamCommon
{
public:
	CSipAVStreamCommon()
	{
		Clear();
	}

	/**
    * \brief            CSipMediaStream init
    * \return           void.
    */
	void Clear();
	/**
	* \brief            is active
	* \return           BOOL32, TRUE/FALSE
	*/
	BOOL32 IsActive()
	{
        return m_bActive;
	}
	/**
	* \brief            Set Active
	* \param[in]        bActive                :flag
	*/
	void SetActive( BOOL32 bActive )
	{
		m_bActive = bActive;
	}

	/**
    * \brief            set local rtcp
	* \param[in]        tRtp     :rtp ip,for ipv4 or ipv6
    * \return           void.
    */
	 void SetLocalRtp(PFC_IPADDR tRtp) 
	{
		m_tLocalRtp = tRtp;
	}

    /**
    * \brief            set local rtp
	* \param[in]        wPort    :rtp port
    * \return           void.
    */
	void SetLocalRtp( u32 dwIp, u16 wPort ) 
	{ 
		m_tLocalRtp.m_emType = PFC_TRANSPORT_TYPE_IP;
		m_tLocalRtp.m_tAddr.m_tIPv4.m_dwIP = dwIp;
		m_tLocalRtp.m_wPort	= wPort;
	}

     void SetLocalRtp6(u8 *pbyIpv6, u16 wPort ) 
	 { 
		 if ( NULL == pbyIpv6)
		 {
			 return;
		 }
		 m_tLocalRtp.m_emType = PFC_TRANSPORT_TYPE_IPV6;
		 memcpy(m_tLocalRtp.m_tAddr.m_tIPv6.m_abyIP, pbyIpv6, PFC_IPV6_ADDR_SIZE);
		 m_tLocalRtp.m_wPort = wPort;
	 }
    /**
    * \brief            get local rtp
    * \return           TIPTransAddress.
    */
	 PFC_IPADDR& GetLocalRtp() 
	{
		return m_tLocalRtp; 
	}

    /**
    * \brief            set local rtcp
	* \param[in]        tRtcp     :rtcp ip,for ipv4 or ipv6
    * \return           void.
    */
	 void SetLocalRtcp(PFC_IPADDR tRtcp) 
	{
		m_tLocalRtcp = tRtcp;
	}

	 /**
    * \brief            set local rtcp
	* \param[in]        dwIP     :rtcp ip
	* \param[in]        wPort    :rtcp port
    * \return           void.
    */
	 void SetLocalRtcp(u32 dwIP, u16 wPort) 
	{
		m_tLocalRtcp.m_emType = PFC_TRANSPORT_TYPE_IP;
		m_tLocalRtcp.m_tAddr.m_tIPv4.m_dwIP = dwIP;
		m_tLocalRtcp.m_wPort	  = wPort;
	}

	
	///< 设置RTCP ipv6参数
	 void SetLocalRtcp6(u8 *pbyIpv6, u16 wPort) 
	 {
		 m_tLocalRtcp.m_emType = PFC_TRANSPORT_TYPE_IPV6;
		 memcpy(m_tLocalRtcp.m_tAddr.m_tIPv6.m_abyIP,pbyIpv6,PFC_IPV6_ADDR_SIZE);
		 m_tLocalRtcp.m_wPort  = wPort;
	 }

    /**
    * \brief            get local rtcp
    * \return           TIPTransAddress.
    */
	 PFC_IPADDR& GetLocalRtcp() 
	{
		return m_tLocalRtcp; 
	}

	 /**
    * \brief            set local rtcp
	* \param[in]        tRtp     :remote rtp ip,for ipv4 or ipv6
    * \return           void.
    */
	 void SetRemoteRtp(PFC_IPADDR tRtp) 
	{
		m_tRemoteRtp = tRtp;
	}

    /**
    * \brief            set remote rtp
	* \param[in]        dwIp     :rtp ip
	* \param[in]        wPort    :rtp port
    * \return           void.
    */
	 void SetRemoteRtp( u32 dwIp, u16 wPort ) 
	{ 
		m_tRemoteRtp.m_emType = PFC_TRANSPORT_TYPE_IP;
		m_tRemoteRtp.m_tAddr.m_tIPv4.m_dwIP		= dwIp;
		m_tRemoteRtp.m_wPort	                = wPort;
	}

	 ///< 设置RTCP ipv6参数
	 void SetRemoteRtp6(u8 *pbyIpv6, u16 wPort) 
	 {
		 m_tRemoteRtp.m_emType = PFC_TRANSPORT_TYPE_IPV6;
		 memcpy(m_tRemoteRtp.m_tAddr.m_tIPv6.m_abyIP,pbyIpv6,PFC_IPV6_ADDR_SIZE);
		 m_tRemoteRtp.m_wPort  = wPort;
	 }
	 /**
    * \brief            get remote rtp
    * \return           TIPTransAddress.
    */
	 PFC_IPADDR& GetRemoteRtp() 
	{
		return m_tRemoteRtp; 
	}


    /**
    * \brief            Set Encrypt Type
	* \param[in]        emType     :encrypt type
    * \return           void.
    */
     void SetEncryptType(emEncryptType emType)
	{
		m_emEncryptType = emType; 
	}
     /**
    * \brief            get Encrypt Type
    * \return           emEncryptType.
    */
	 emEncryptType GetEncryptType()
	{
		return m_emEncryptType;
	}
	
	
	 /**
	* \brief            Set Encrypt Sync
	* \param[in]        tSync                :encrypt sync
	* \return           void
	*/
	void SetEncryptSync( TEncryptSync &tSync)
	{ 
		m_tEncryptSync = tSync; 
	}
    /**
	* \brief            Get Encrypt Sync
	* \return           TEncryptSync
	*/
	TEncryptSync &GetEncryptSync() 
	{ 
		return m_tEncryptSync; 
	} 

	/**
	* \brief            Set Bit Rate
	* \param[in]        nRate                :bit rate
	*/
	void SetBitRate( s32 nRate )
	{
		m_nBitRate = nRate;
	}
	
	/**
	* \brief            Get Bit Rate
	* \return           s32
	*/
	s32 GetBitRate()
	{
		return m_nBitRate;
	}
		
	/**
	* \brief            Set Sip Content Attr 
	* \param[in]        emSipContentAttr                :sip content attribute
	*/
	void SetSipContentAttr( EmSipContentAttr emSipContentAttr)
	{
		m_emSipContent = emSipContentAttr;
	}
	/**
	* \brief            Get Sip Content Attr 
	* \return           EmSipContentAttr                
	*/
	EmSipContentAttr GetSipContentAttr()
	{
		return m_emSipContent;
	}

	/**
	* \brief            Set Sip Media Label
	* \param[in]        nSipMediaLabel                :sip media label
	*/
	void SetSipMediaLabel( s32 nSipMediaLabel )
	{
		m_nSipMediaLabel = nSipMediaLabel;
	}
	/**
	* \brief            Get Sip Media Label 
	* \return           s32                
	*/
	s32 GetSipMediaLabel()
	{
		return m_nSipMediaLabel;
	}

	/**
	* \brief            Get Screen No
	* \return           s32
	*/
	s32 GetScreenNo()
	{
		return m_nScreenNum;
	}
	/**
	* \brief            Set Screen No
	* \param[in]        nScreenNo                :screen no
	*/
	void SetScreenNo( s32 nScreenNo )
	{
		m_nScreenNum = nScreenNo;
	}
	
	/**
	* \brief            Get Cap Sign Num
	* \return           s32
	*/
	s32 GetCapSignNum()
	{
		return m_nCapSignNum;
	}
	/**
	* \brief            Set Cap Sign Num
	* \param[in]        nCapSignNum                :cap sign number
	*/
	void SetCapSignNum( s32 nCapSignNum )
	{
		m_nCapSignNum = nCapSignNum;
	}

#ifdef _KDV_SRTP_SUPPORT_
	/**
	* \brief            Set Srtp Media Setting
	* \param[in]        ptSetting                :Srtp Media Setting
	*/
	void SetSrtpMediaSetting(TSrtpMediaSetting *ptSetting)
	{
		m_tSrtpSetting = *ptSetting;
	}
	/**
	* \brief            Get Srtp Media Setting
	* \return           TSrtpMediaSetting                
	*/
	TSrtpMediaSetting *GetSrtpMediaSetting()
	{
		return &m_tSrtpSetting;
	}
#endif

	/**
	* \brief            set if use rtcp mux
	* \param[in]        bRtcpMux  :set Rtcp mux valve,TRUE is use rtcp-mux,FALSE is not use.
	*/
	void SetRtcpMux(BOOL32 bRtcpMux)
	{
		m_bRtcpMux = bRtcpMux;
	}
	/**
	* \brief            get rtcp mux state
	* \return           BOOL32 :if set Rtcp MUX
	*/
	BOOL32 GetRtcpMux()
	{
		return m_bRtcpMux;
	}

private:
	BOOL32				m_bActive;                         ///< is active

	PFC_IPADDR	        m_tLocalRtp;                       ///< local rtp,for ipv4 and ipv6
	PFC_IPADDR	        m_tLocalRtcp;		               ///< combine m_tSendRtcp with m_tRecvRtcp into a new TTransAddress m_tLocalRtcp, double checked with Lijing
	PFC_IPADDR	        m_tRemoteRtp;                      ///< remote rtp,for ipv4 and ipv6

	emEncryptType		m_emEncryptType;	               ///< 加密类型
	TEncryptSync		m_tEncryptSync;		               ///< master需设置此结构
	s32					m_nBitRate;                        ///< bit rate

	/// 用于BFCP，添加content和label属性,does audio need those?
	EmSipContentAttr    m_emSipContent;                    ///< sip content attribute
	s32                 m_nSipMediaLabel;                  ///< sip media label

	/// 用于网真
	s32					m_nScreenNum;                      ///< screen number
	s32					m_nCapSignNum;                     ///< cap sign number

#ifdef _KDV_SRTP_SUPPORT_
	TSrtpMediaSetting	m_tSrtpSetting;                    ///< srtp settting
#endif

	BOOL32              m_bRtcpMux;                        ///< rtcp port mux
};

class PROTO_API CSipAudioStream 
{
public:
	CSipAudioStream()
	{
		Clear();
	}

	/**
    * \brief            CSipMediaStream init
    * \return           void.
    */
	void Clear();
	/**
    * \brief            CSipMediaStream init capset
    * \return           void.
    */
	void ClearCapset();

	/**
    * \brief            CSipMediaStream operator =
	* \param[in]        cCopyMedia    :media stream
    * \return           void.
    */
	void operator = (const CSipAudioStream& cCopyMedia);
	
	void SetAudioAlterCap(CSipAudioAlterCap* tAudioAlterCap)
	{
		m_cAudioAlterCap = *tAudioAlterCap;
	}

	CSipAudioAlterCap* GetAudioAlterCap()
	{
		return &m_cAudioAlterCap;
	};

	/**
	* \brief            Set Extmap Audio Level
	* \param[in]        emDirect           :send recv attribute
	* \param[in]        byId               :audio level
	* \param[in]        bVadOn             :audio level vad on
	*/
	void SetExtmapAudioLevel(emSendRecvAttr emDirect, u8 byId, BOOL32 bVadOn)
	{
		m_emAudLvlDirect = emDirect;
		m_byAudLvlId = byId;
		m_bAudLvlVadOn = bVadOn;
	}
	/**
	* \brief            Get Extmap Audio Level
	* \param[in]        emDirect           :send recv attribute
	* \param[in]        byId               :audio level
	* \param[in]        bVadOn             :audio level vad on
	*/
	void GetExtmapAudioLevel(emSendRecvAttr &emDirect, u8 &byId, BOOL32 &bVadOn)
	{
		emDirect = m_emAudLvlDirect;
		byId = m_byAudLvlId;
		bVadOn = m_bAudLvlVadOn;
	}

	/**
	* \brief            Set Audio Mix 
	* \param[in]        bAudMix                :flag
	*/
	void SetAudMix(BOOL32 bAudMix)
	{
		m_bAudMix = bAudMix;
	}
	/**
	* \brief            is audio mix
	* \return           BOOL32, TRUE/FALSE
	*/
	BOOL32 IsAudMix()
	{
		return m_bAudMix;
	}

private:
	CSipAVStreamCommon     m_cAVStreamCommon;    ///< audio and video stream common attribute

	CSipAudioAlterCap      m_cAudioAlterCap;	 ///< audio capability set

	/// extmap扩展（audio-level）
	emSendRecvAttr         m_emAudLvlDirect;     ///< send recv attribute
	u8                     m_byAudLvlId;         ///< audio level id
	BOOL32                 m_bAudLvlVadOn;       ///< audio level vadon

	/// 用于网真
	BOOL32				   m_bAudMix;			 ///< 是否混音
}PACKED;

class PROTO_API CSipVideoAlterCap 
{
public:
	enum { emVideoCapNum = 20 };                        ///< audio cap number

	CSipVideoAlterCap()
	{
		Clear();
	}

	void Clear();

	void operator = (const CSipVideoAlterCap& cCopyCap);

	/**
	* \brief            add media
	* \param[in]        emPayloadType          :payload type
	* \param[in]        ptCap                  :cap set
	* \return           BOOL32, TRUE/FALSE
	*/
	 BOOL32 AddMedia( PayloadType emPayloadType, TKdvCapSet *ptCap );
	/**
	* \brief            get media
	* \param[in]        emPayloadType          :payload type
	* \param[in]        ptCap                  :cap set
	* \param[in]        byIndex                :cap set index
	* \return           BOOL32, TRUE/FALSE
	*/
	 BOOL32 GetMedia( PayloadType emPayloadType, TKdvCapSet **ptCap, u8 byIndex = 0);
	 /**
	* \brief            remove all media
	* \return           void.
	*/
	 void RemoveAllMedia();
	/**
	* \brief            remove media
	* \param[in]        emPayloadType          :payload type
	* \param[in]        byIndex                :cap set index
	* \return           BOOL32, TRUE/FALSE
	*/
	 BOOL32 RemoveMedia(PayloadType emPayloadType, u8 byIndex = 0xFF);
	/**
	* \brief            media negotiate
	* \param[in]        emPayloadType          :payload type
	* \param[in]        ptCap                  :cap set 
	* \param[in]        nIndex                 :cap set index
	* \param[in]        pnH26XOrder            :media order
	* \param[in]        bStrictMatch           :is strict match
	* \return           BOOL32, TRUE/FALSE
	*/
	 BOOL32 IsSupport( PayloadType emPayloadType, TKdvCapSet *ptCap, s32 nIndex = -1, s32 *pnH26XOrder = NULL,BOOL32 bStrictMatch=FALSE);
	/**
	* \brief            Get Media PT
	* \param[in]        byIndex                :media index
	* \return           PayloadType
	*/
	 PayloadType GetMediaPT( u8 byIndex )
	{
        if ( byIndex < m_byMediaCount )
			return m_aemMediaPT[byIndex];
		else
			return emPayloadTypeEnd;
	}
	/**
	* \brief            Get Media Count
	* \return           u8
	*/
	u8 GetMediaCount() 
	{
		return m_byMediaCount;
	}
	
	/**
	* \brief            Set Media PT Array
	* \param[in]        nPos                :postion
	* \param[in]        emSipPT             :payload type
	*/
	void SetMediaPTArray( s32 nPos, PayloadType emSipPT )
	{
		if ( nPos < m_byMediaCount )
		{
			BOOL32 bFind = FALSE;
			for ( s32 i = 0; i< emVideoCapNum; ++i )
			{
				if( m_aemMediaPT[i] == emSipPT && emSipPT != emH264 )
				{
					bFind = TRUE;
				}
				else
					continue;
			}
			if ( !bFind )
			{
				m_aemMediaPT[nPos] = emSipPT;
			}
		}
	}
	/**
	* \brief            Set Media Count
	* \param[in]        nCount                :media count
	*/
	void SetMediaCount( s32 nCount )
	{
		m_byMediaCount = nCount;
	}

	/**
	* \brief            Set H264 Capset Number
	* \param[in]        byNum                :number
	*/
	void SetH264CapsetNumber( u8 byNum )
	{
		m_byH264CapNum = byNum;
	}
	/**
	* \brief            Set H264 Capset Number 
	* \return           u8                
	*/
	u8 GetH264CapsetNumber()
	{
		return m_byH264CapNum;
	}
	/**
	* \brief            Add H264Capset Number
	*/
	void AddH264CapsetNumber()
	{
		m_byH264CapNum++;
	}
	/**
	* \brief            Set H264 Capset Order
	* \param[in]        nIndex                :H264 capset index
	* \param[in]        byOrder               :H264 capset order
	*/
	void SetH264CapsetOrder( s32 nIndex, u8 byOrder )
	{
		m_abyH264CapOrder[nIndex] = byOrder;
	}
	/**
	* \brief            Get H264 Capset Order 
	* \param[in]        nIndex                :H264 capset index
	* \return           u8                
	*/
	u8 GetH264CapsetOrder( s32 nIndex )
	{
		return m_abyH264CapOrder[nIndex+1];
	}
	
	/**
	* \brief            Set H265 Capset Number
	* \param[in]        byNum                :number
	*/
	void	SetH265CapsetNumber(u8 byNum){ m_byH265CapNum = byNum;}
	/**
	* \brief            Get H265 Capset Number 
	* \return           u8                
	*/
	u8		GetH265CapsetNumber(){return m_byH265CapNum;}
	/**
	* \brief            Add H265Capset Number
	*/
	void	AddH265CapsetNumber(){m_byH265CapNum++;}
	/**
	* \brief            Set H265 Capset Order
	* \param[in]        nIndex                :H264 capset index
	* \param[in]        byOrder               :H264 capset order
	*/
	void	SetH265CapsetOrder(s32 nIndex, u8 byOrder){m_abyH265CapOrder[nIndex] = byOrder;}
	/**
	* \brief            Get H265 Capset Order 
	* \param[in]        nIndex                :H264 capset index
	* \return           u8                
	*/
	u8		GetH265CapsetOrder(s32 nIndex){return m_abyH265CapOrder[nIndex];}
	
private:
	PayloadType			m_aemMediaPT[emVideoCapNum];          ///< media payload type
	u8					m_byMediaCount;                            ///< media count

	TKdvVideoCap		m_tH261Cap;                        ///< H261 cap
	TKdvVideoCap		m_tH263Cap;                        ///< H263 cap
	TKdvVideoCap		m_tH263plusCap;                    ///< H263 plus cap
	TKdvVideoCap		m_tMpeg4Cap;                       ///< mpeg4 cap
	TKdvVideoCap		m_tH262Cap;                        ///< H262 cap

	u8					m_byH264CapNum;	                   ///< H264 cap number 
	u8					m_abyH264CapOrder[MAX_H264CAP_NUM];///< H264 cap order
	TKdvH264VideoCap	m_atH264Cap[MAX_H264CAP_NUM];      ///< H264 cap array

	// H.265 video capabilties
	u8					m_byH265CapNum;                    ///< H265 capset number
	u8					m_abyH265CapOrder[MAX_H265CAP_NUM];///< H265 capset order
	TKdvH265VideoCap	m_atH265Cap[MAX_H265CAP_NUM];      ///< H265 cap
}PACKED;

class PROTO_API CSipVideoStream 
{
public:
	CSipVideoStream()
	{
		Clear();
	}

	/**
    * \brief            CSipMediaStream init
    * \return           void.
    */
	void Clear();
	/**
    * \brief            CSipMediaStream init capset
    * \return           void.
    */
	void ClearCapset();

	/**
    * \brief            CSipMediaStream operator =
	* \param[in]        cCopyMedia    :media stream
    * \return           void.
    */
	void operator = (const CSipVideoStream& cCopyMedia);

	void SetVideoAlterCap(CSipVideoAlterCap* tVideoAlterCap)
	{
		m_cVideoAlterCap = *tVideoAlterCap;
	}

	CSipVideoAlterCap* GetVideoAlterCap()
	{
		return &m_cVideoAlterCap;
	};

	/**
	* \brief            Get Cap Sign 
	* \param[in]        nIndex                :cap sign index
	* \return           EmSipCapSign
	*/
	EmSipCapSign GetCapSign( s32 nIndex = 0 )
	{
		return m_aemSipCapSign[nIndex];
	}
	/**
	* \brief            Set Cap Sign 
	* \param[in]        emCapSign                :cap sign type
	* \param[in]        nIndex                   :cap sign index
	*/
	void SetCapSign( EmSipCapSign emCapSign, s32 nIndex = 0 )
	{
		m_aemSipCapSign[nIndex] = emCapSign;
	}

	/**
	* \brief            Set Tp Rtp Address 
	* \param[in]        nIndex                :rtp index
	* \param[in]        tRtpAddr              :rtp address
	*/
	void SetTpRtpAddress( s32 nIndex, PFC_IPADDR tRtpAddr ) 
	{ 
		m_atTpRtpAddr[nIndex] = tRtpAddr;
	}

	/**
	* \brief            Set Tp Rtp Address 
	* \param[in]        nIndex                :rtp index
	* \param[in]        dwIP                  :rtp ip
	* \param[in]        wPort                 :rtp port
	*/
	void SetTpRtpAddress( s32 nIndex, u32 dwIP, u16 wPort ) 
	{ 
		m_atTpRtpAddr[nIndex].m_tAddr.m_tIPv4.m_dwIP = dwIP;
		m_atTpRtpAddr[nIndex].m_wPort = wPort;
	}
	/**
	* \brief            Get Tp Rtp Address 
	* \param[in]        nIndex                :rtp index
	* \return           TIPTransAddress
	*/
	PFC_IPADDR& GetTpRtpAddress( s32 nIndex ) 
	{
		return m_atTpRtpAddr[nIndex]; 
	}

	/**
	* \brief            Set Tp Rtcp Address 
	* \param[in]        nIndex                :rtcp index
	* \param[in]        tRtcpAddr             :rtcp address
	*/
	void SetTpRtcpAddress( s32 nIndex, PFC_IPADDR tRtcpAddr ) 
	{ 
		m_atTpRtcpAddr[nIndex] = tRtcpAddr;
	}

	/**
	* \brief            Set Tp Rtcp Address 
	* \param[in]        nIndex                :rtp index
	* \param[in]        dwIP                  :rtp ip
	* \param[in]        wPort                 :rtp port
	*/
	void SetTpRtcpAddress( s32 nIndex, u32 dwIP, u16 wPort ) 
	{ 
		m_atTpRtcpAddr[nIndex].m_tAddr.m_tIPv4.m_dwIP = dwIP;
		m_atTpRtcpAddr[nIndex].m_wPort = wPort;
	}
	/**
	* \brief            Get Tp Rtcp Address 
	* \param[in]        nIndex                :rtp index
	* \return           TIPTransAddress
	*/
	PFC_IPADDR& GetTpRtcpAddress( s32 nIndex ) 
	{
		return m_atTpRtcpAddr[nIndex]; 
	}

	/**
	* \brief            Set Bitrate Percent
	* \param[in]        byPercent                :bitrate percent
	*/
	void SetBitratePercent(u8 byPercent){ m_byBitratePercent = byPercent; }
	/**
	* \brief            Get Bitrate Percent 
	* \return           u8                
	*/
	u8 GetBitratePercent(){ return m_byBitratePercent; }

	/**
	* \brief            rtcp feedback mode set function
	* \param[in]        ptRtcpFb                :Rtcp Feedback Param
	*/
	void SetFeedbackParam(const TRtcpFeedbackParam* ptRtcpFb)
	{
		MEMCPY_CAST(&m_tRtcpFb, ptRtcpFb, sizeof(TRtcpFeedbackParam));
	}
	/**
	* \brief            rtcp feedback mode get function
	* \return           TRtcpFeedbackParam    
	*/
	TRtcpFeedbackParam* GetFeedbackParam()
	{
		return &m_tRtcpFb;
	}
	

private:	
    CSipAVStreamCommon  m_cMediaStreamCommon;
	CSipVideoAlterCap   m_cVideoAlterCap;

	/// 用于网真
	EmSipCapSign		m_aemSipCapSign[emSipCapEnd];      ///< cap sign
	PFC_IPADDR	        m_atTpRtpAddr[emSipCapEnd];        ///< rtp address
	PFC_IPADDR   	    m_atTpRtcpAddr[emSipCapEnd];       ///< rtcp address

	/// 终端平台对通非标（带宽比率）
	u8 m_byBitratePercent;                                 ///< bitrate percent

	TRtcpFeedbackParam  m_tRtcpFb;                         ///< rtcp feedback mode
}PACKED;

#ifdef WIN32
#pragma pack( pop )
#endif

/**
* \brief             普通载荷类型转换成带加密信息的载荷类型
* \param[in]         wType          :待转换的载荷类型
* \param[in]         byEBits        :the number of array of pwPayload
* \param[out]        bStatic        :按位的加密位，如 emEncryptTypeDES|emEncryptTypeAES
* \return            转换后的载荷类型
*/
PROTO_EXTERN_API u16	GetEType	( IN u16 wType, IN u8 byEBits);

/// transform the wType to h239 type,use emEncryptTypeH239
PROTO_EXTERN_API u16	GetH239Type	( IN u16 wType );

/// if the wType is a h239 tpye
PROTO_EXTERN_API BOOL32	IsH239Type	( IN u16 wType );

PROTO_API void RegProtocommonFunLinux(); ///< For register debug command of kdvprotocommon module


s8* GetMediaName(PayloadType emPayLoadType);

PayloadType GetPayloadByName(s8 *pStrName);

emResolution GetResolutionByName(s8 *pStrName);

s8* GetResolutionName(emResolution emResType);


#endif

