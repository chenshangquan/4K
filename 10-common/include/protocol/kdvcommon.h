/**
*   COPYRIGHT NOTICE
*   Copyright (C) 2018, KeDaCom
*   All right reserved
*   
*   @file        kdvcommon.h
*   @author      Sai
*   @version     V5.0_64bit
*   @date        2018-03-05
*   @brief       Common struct for H323 or Sip 
*   @details     
*/

#ifndef _KDVCOMMON_H
#define _KDVCOMMON_H

#include "protocolcommonpublic.h"
#include "kdvdef.h"
#include "pfc.h"

#define LEN_ALIAS			(u16)64				    //最大别名长度h323-id
#define LEN_TERID			(u16)128				//终端名字最大长度
#define MAX_CONF_NUM		(u16)32					//最大会议数
#define LEN_GUID			(u8)16					//GIUD长度
#define LEN_1				(u16)1
#define MAX_G7221CAP_NUM    (u8)8                  //G7221能力个数
#define MAX_H264CAP_NUM     (u8)8                  //H.264能力个数
#define MAX_H265CAP_NUM     (u8)8					//H.265能力个数
#define LEN_DES_KEY         (u8)8                   //DES的密钥长度
#define LEN_AES_KEY         (u8)16                  //AES的密钥长度
#define LEN_AES256_KEY      (u8)32                  //AES的密钥长度

#define ANNEXQ_DYNAMIC_PT	(u16)100				//h.281动态载荷
#define MAX_PRODUCTID_LEN	(u32)128				//最大productID、version长度
#define MAX_PRODUCTIDTYPE_LEN	(u32)32				//字符串形式的对端型号长度
#define MAX_FILE_PATH_LEN	256                     //文件载入路径最大长度

#define MAX_CERTICATE_NUM	3						//Max number of certificates for TLS
#define MAX_QT_ID_LEN	    128						//Max length of devid for qt

#ifdef _KDV_SRTP_SUPPORT_
/// about srtp 
#define MAX_CRYPTO_NUM     8    ///< crypto number
#define MAX_CRYPTO_KEY_LEN 50	///< length of crypto key
#define MAX_MKI_VALUE      50	///< mki value
#endif

//协议宏使用说明
//CBB_FOR_TPS		对于网呈做特殊化处理使用的宏，目前对TNsmInfo结构体有以此宏区分

#if (!defined(RV_DEBUG)) && (!defined(RV_RELEASE))
	#define RV_RELEASE
#endif

#ifndef TRUE_
	typedef int                  BOOL;
	#define TRUE                 1
	#define FALSE                0
	#define TRUE_
#endif

#ifdef _IOS_PLATFORM_
	#define BOOL32 BOOL
#endif //_IOS_PLATFORM_

#define LEN_MTNUM_PERCONF	(u16)192				//每个会议中的最大呼叫数

/// APPID ????
///< 协议应用号（591-620） -- kdvdef.h
///< #define AID_PROTOCOL_BGN                (AID_TP_END  + 1)
///< #define AID_PROTOCOL_END                (AID_PROTOCOL_BGN + 29)
#define APPID_DATANET_PINHOLE	 AID_PROTOCOL_BGN+1

/// Call Address Type
enum CallAddrType
{
	emcat_err	= -1,   ///< err type
	emcat_ip	= 1, 	///< IP 
	emcat_alias	= 2,   	///< alias
	emcat_e164	= 3,	///< E164
};

/// protocol type in conference list
enum emProtocolType
{
	emTypeInvalid,
	emTypeH323,
	emTypeSIP,
	emTypeALL,
};

/// Endpoint Type
typedef enum
{
	emEndpointTypeUnknown	= 0,
	emEndpointTypeMT		= 1,
	emEndpointTypeMCU		= 2,
	emEndPointTypeRegister	= 4,   ///< for sip
	emEndpointTypeGK		= 8,
	emEndpointTypeCNS       = 16,
	emEndpointTypeUMS       = 32,
	emEndpointTypeGateWay	= 64, 
	emEndpointTypeVRS	    = 128, 
}emEndpointType;


/// 设备子类定义---终端类型定义
enum EmSubMtType
{
	emMtTypeNone	= 0, ///< 不接收也不发送
	emMtTypeMt		= 3, ///< mt
	emMtTypeMmcu	= 4, ///< 上级MCU
	emMtTypeSmcu	= 5, ///< 下级MCU
	emMtTypePhone	= 6, ///< 电话终端
	emMtTypeSatd	= 7, ///< 卫星终端
};

/// Payload Type
///< guzh [12/14/2007] ???í?????§???¨
///< guzh [03/27/2008] ?????ú?????ò??emAudioTypeEnd??emVideoTypeEnd?????§??×???????????????????
///< ???±?????? IsAudioType, IsAudioType, IsDataType??????
enum  PayloadType 
{
    emPayloadTypeBegin	= 0,
    /// ????????
    emAudioTypeBegin= 1,
    emG711a			= 2,
    emG711u			= 3,
    emG722			= 4,
    emG7231			= 5,
    emG728			= 6,
    emG729			= 7,
    emMp3			= 8,
    emG723			= 9,
    emG7221			= 10,	///< 代替emG7221c
    emMpegaaclc		= 11,
    emMpegaacld		= 12,
	emOpus			= 13,	///< 非标准能力的payloadType要和以前一样，同emMpeg4、emH262，否则会有兼容问题
	emG719			= 14,	
	emTelephoneEvent= 15,
	// 保持新老版本兼容
    emMpeg4			= 17,    
    emH262			= 18,
	emRedundant		= 19,

    emTypeGeneric	= 48,   // 内部使用
    emAudioTypeEnd	= 49,
        
    /// 视频格式
    emVideoTypeBegin= 50,	
    emH261			= 51,
    emH263			= 52,
    emH263plus		= 53,
    emH264			= 54,
	emH265			= 57,
    emVideoGeneric	= 97,
    emVideoExtended	= 98,
    emVideoTypeEnd	= 99,
        
    /// 数据格式
    emDataTypeBegin	= 100,	
    emT120			= 101,
    emH224			= 102,
    emDataTypeEnd	= 149,
        
    emTH235			= 150,		 //内部使用
    emTMmcu			= 151,       //级联通道
    emTNone			= 152,       //此通道不支持, 仅用于级联
    emTNonstandard	= 153,
    emTHuawei		= 154,
	
	/// add for huawei nostandrd [20130427]
	emTHuawei5		= 155,
	emTHuawei6		= 156,
	emTHuawei7		= 157,
		
	/// add for ZTE nostandrd [20130507]
	emTZTE8			= 158,	///< audio
	emTZTE10		= 159,	///< audio
	emTZTE11		= 160,	///< audio
	emTZTE13		= 161,	///< video 且未设入同时能力中
	emTZTE21		= 162,	///< video

	///add for Polycom Viavideo HDX 7000 HD GenericControlCapability
	emControlCapType= 163,
    
	emPayloadTypeEnd= 255
};

/// the enum of Resolution,使用企业头文件的定义，合并了emResolutionHD
typedef enum
{
	emResolutionBegin	= 0,
		emSQCIF			= 1,
		emQCIF			= 2,
		emCIF			= 3,
		emCIF2			= 4,
		emCIF4			= 5,
		emCIF16			= 6,
		
		emSIF			= 7,
		emSIF4			= 8,
		emVGA			= 9,
		emSVGA			= 10,
		emXGA			= 11,
		
		emAUTO			= 12,
		
		emEmpty			= 13,
		
		emW4CIF			= 14,			///< Wide4CIF 16:9 1024*576
		emHD720			= 15,			///< 720   1280*720
		emSXGA			= 16,			///< SXGA  1280*1024
		emUXGA			= 17,			///< UXGA  1600*1200
		emHD1080		= 18,			///< 1080  1920*1080
		
		em1280x800		= 19,
		em1280x768		= 20,
		em480x352		= 21,
		
		em1440x900		= 22,
		em1280x960		= 23,
		emWCIF			= 24,
		em1366x768		= 25,

		em1680x1050		= 26,			///< WSXGA+  1680*1050
		
		/// Resolutions supported by H.265, added by Jacky according to T-REC-H.265-201304-I!!PDF-E
		emResolution2Kx1K,				///< 2048 1024  2 097 152  - - - - - 31.8 63.7 
		emResolution2Kx1080,			///< 2048 1080  2 228 224  - - - - - 30.0 60.0 
		emResolution4XGA,				///< 2048 1536  3 145 728  - - - - - -  - 
		emResolution16VGA,				///< 2560 1920  4 915 200  - - - - - -  - 
		emResolution3616x1536,			///< (2.35:1)  3616  1536  5 603 328  - - - - - -  - 
		emResolution3672x1536,			///< (2.39:1)  3680  1536  5 701 632  - - - - - -  - 
		emResolution3840x2160,			///< (4*HD)  3840  2160  8 355 840 - - - - - -  - 
		emResolution4Kx2K,				///< 4096 2048  8 388 608  - - - - - -  - 
		emResolution4096x2160,			///< 4096 2160  8 912 896  - - - - - -  - 
		emResolution4096x2304,			///< (16:9)  4096  2304  9 437 184  - - - - - -  - 
		emResolution7680x4320,			///< 7680 4320  33 423 360  - - - - - -  - 
		emResolution8192x4096,			///< 8192 4096  33 554 432 - - - - - -  - 
		emResolution8192x4320,			///< 8192 4320  35 651 584 - - - - - -  - 
 
		emResolutionEnd					///< end
}emResolution;

/// H.264 NAL mode --> packetization mode
enum emH264NALMode
{
	emNALNode            = 0x00,       ///< invalid
	emNALSignal          = 0x01,       ///< Signal
	emNALSingle			 = emNALSignal,///< single,equal signal
	emNALNoneInterleaved = 0x02,       ///< not interleaved
	emNALInterleaved     = 0x04        ///< interleaved
};

/// H.265 NAL mode --> packetization mode
//enum emH265NALMode
//{
//	emNALNone            = 0x00,       ///< invalid
//	emNALSingleNal       = 0x01,       ///< single
//	emNALAggregation     = 0x02,       ///< Aggregation Packet (AP) 
//	emNALFragmentation   = 0x04        ///< Fragmentation Unit (FU) 
//};

/// 会议操作:请求-应答方式返回结果
enum CtrlResult 
{
	ctrl_err = -1,      ///< error  
	ctrl_granted,		///< granted
	ctrl_denied			///< denied
};

/// Product vendor ID(the value is same as EmModuleVendorID(modulecallstruct.h))
enum EmVendorProductId
{
	emMicrosoftNetmeeting	= 1,
	emKeda					= 2,
	emHuaWei				= 3,
	emPolycom				= 4,
	emPolycomMCU			= 5,
	emTandberg				= 6,
	emRadvision				= 7,
	emVcon					= 8,
	emSony					= 9,
	emVtel					= 10,
	emZTE					= 11,		///< ????
	emZTEMCU				= 12,
	emCodian				= 13,
	emAETHRA				= 14,
	emCHAORAN				= 15,
	emAVCON					= 16,		///< ????
	emDonJin				= 17,		///< ????GW
	emCisco				    = 18,		//cisco
    emYealink               = 19, 
	emSmartPhone            = 20,
	emUNKNOWN				= 21,
	emVendorEND				= 22
};

///< tls type
typedef enum
{
	emTlsNone= 0,
	emStdTls = 1,
	emGMTls  = 2,
	emQTTls  = 3
}EmTlsType;

#ifdef _KDV_SRTP_SUPPORT_
/// srtp mode
enum EmSrtpMode
{
	emSrtpModeNone,      ///< none
	emSrtpModeOptional,	 ///< optional
	emSrtpModeMandatory	 ///< mandatory
};

/// srtp type
enum EmSrtpType
{
	emSrtpTypeNone = 0x00,  ///< none
	emSrtpTypeSdes = 0x01,	///< SDES
	emSrtpTypeDtls = 0x02,	///< DTLS
	emSrtpTypeSdesDtls = (emSrtpTypeSdes | emSrtpTypeDtls) ///< SDES and DTLS
};

/// srtp crypto type
enum EmSrtpCryptoType
{
	emSrtpCryptoNone = 0,      ///< ??????
	emSrtpCryptoAES_CM_128,    
	emSrtpCryptoAES_CM_192,	   
	emSrtpCryptoAES_CM_256,	   
	emSrtpCryptoAES_GCM_128,   
	emSrtpCryptoAES_GCM_192,   
	emSrtpCryptoAES_GCM_256,   
	emSrtpCryptoSM4_CM_128,    // SM目前只有128的  
	emSrtpCryptoSM1_CM_128, 
};

/// srtp authentication type
enum EmSrtpAuthType
{
	emSrtpAuthNone = 0,     ///< none
	emSrtpAuthTag_8,		///< Tag_8
	emSrtpAuthTag_16,		///< Tag_16 
	emSrtpAuthTag_32,		///< Tag_32
	emSrtpAuthTag_80,		///< Tag_80
};

typedef struct PROTO_API tagMediaQuantumCrypto
{
	BOOL32 m_bUpdate;
	s8     m_achCryptoKey[MAX_CRYPTO_KEY_LEN];
	s8     m_achMkiValue[MAX_MKI_VALUE];
	u32    m_dwMkiLen;
	tagMediaQuantumCrypto()
	{
		Clear();
	}

	void Clear()
	{
		m_bUpdate  = FALSE;
		memset(m_achCryptoKey, 0, sizeof(m_achCryptoKey));
		memset(m_achMkiValue,  0, sizeof(m_achMkiValue));
		m_dwMkiLen = 0;
	}
}TMediaQuantumCrypto,*PTMediaQuantumCrypto;

/*====================================================================
函数名      : ApplyFeccQuantumKey
功能        : 获取量子秘钥功能回调函数
算法实现    : 无
引用全局变量: 无
输入参数说明: tQuantumCrypto- Quantum相关信息	
返回值说明  : 成功 - annexQOK
              失败 - annexQParamError
====================================================================*/
typedef s32 (PROTO_CALLBACK *CBApplyFeccQuantumKey)(IN OUT TMediaQuantumCrypto& tQuantumCrypto);

/// the information of srtp,include crypto type,auty type, crypto key, mki 
typedef struct PROTO_API tagMediaSrtpCrypto
{
	s32              m_nTag;                              ///< tag value
	EmSrtpCryptoType m_emCryptoType;                      ///< enum of crypto type
	EmSrtpAuthType   m_emAuthType;						  ///< enum of auth type
	s8               m_achCryptoKey[MAX_CRYPTO_KEY_LEN];  ///< array of crypto key,maximum length is MAX_CRYPTO_KEY_LEN
	s8               m_achMkiValue[MAX_MKI_VALUE];        ///< array of MKI vlaue,maximum length is MAX_MKI_VALUE
	u32              m_dwMkiLen;		                  ///< MKI length
	CBApplyFeccQuantumKey m_pApplyFeccQuantumKey;
	tagMediaSrtpCrypto()								 
	{
		Clear();
	}
	void Clear()
	{
		m_nTag         = 0;
		m_emCryptoType = emSrtpCryptoNone;
		m_emAuthType   = emSrtpAuthNone;
		memset(m_achCryptoKey, 0, sizeof(m_achCryptoKey));
		memset(m_achMkiValue,  0, sizeof(m_achMkiValue));
		m_dwMkiLen     = 0;
		m_pApplyFeccQuantumKey = NULL;
	}
	void Print()
	{
		PfcPrintf(TRUE, FALSE, "Tag        = %d\n", m_nTag);
		PfcPrintf(TRUE, FALSE, "CryptoType = %d\n", m_emCryptoType);
		PfcPrintf(TRUE, FALSE, "AuthType   = %d\n", m_emAuthType);
		PfcPrintf(TRUE, FALSE, "CryptoKey  = %s\n", m_achCryptoKey);
		PfcPrintf(TRUE, FALSE, "MkiValue   = %s\n", m_achMkiValue);
		PfcPrintf(TRUE, FALSE, "MkiLen     = %d\n", m_dwMkiLen);
	}
	BOOL32 IsSupport(tagMediaSrtpCrypto tSrtpCrypto)
	{
		if((m_nTag == tSrtpCrypto.m_nTag) && (m_emCryptoType == tSrtpCrypto.m_emCryptoType) && (m_emAuthType == tSrtpCrypto.m_emAuthType))
		{
			return TRUE;
		}
		return FALSE;
	}
} TMediaSrtpCrypto;

/// srtp setting,include srtp mode,crypto count and array of TMediaSrtpCrypto struct
typedef struct PROTO_API tagSrtpMediaSetting
{
	EmSrtpMode       m_emSrtpMode;                       ///< enum of srtp mode
	u32              m_dwCryptoCount;					 ///< crypto count
	TMediaSrtpCrypto m_atSrtpCrypto[MAX_CRYPTO_NUM];	 ///< array of crypto setting

	tagSrtpMediaSetting()
	{
		Clear();
	}
	void Clear()
	{
		m_emSrtpMode = emSrtpModeNone;
		m_dwCryptoCount = 0;
		for (s32 i = 0; i < sizeof(m_atSrtpCrypto)/sizeof(m_atSrtpCrypto[0]); i++)
		{
			m_atSrtpCrypto[i].Clear();
		}
	}

	void Print()
	{
		PfcPrintf(TRUE, FALSE, "SrtpMode    = %d\n", m_emSrtpMode);
		PfcPrintf(TRUE, FALSE, "CryptoCount = %d\n", m_dwCryptoCount);
		for (u32 i=0; i<m_dwCryptoCount; i++ )
		{
			PfcPrintf(TRUE, FALSE, "[%d] ", i);
			m_atSrtpCrypto[i].Print();
		}
	}

	BOOL32 GetSrtpCrypto(s32 nCryptoNum, TMediaSrtpCrypto &tSrtpCrypto)
	{
		if (0 <= nCryptoNum && nCryptoNum < MAX_CRYPTO_NUM)
		{
			tSrtpCrypto = m_atSrtpCrypto[nCryptoNum];
			return TRUE;
		}
		return FALSE;
	}

	BOOL32 IsSupportSrtp(tagSrtpMediaSetting* ptInSrtp,tagSrtpMediaSetting &tOutSrtp,BOOL32 bUseInSrtp)
	{
		if (NULL == ptInSrtp)
		{
			return FALSE;
		}
		s32 nCryptoNum = 0;
		if ((emSrtpModeNone != m_emSrtpMode) && (emSrtpModeNone != ptInSrtp->m_emSrtpMode))
		{
			for ( u32 dwCount = 0; dwCount < m_dwCryptoCount; ++dwCount )
			{
				for ( u32 dwInCount = 0; dwInCount < ptInSrtp->m_dwCryptoCount; ++dwInCount )
				{
					TMediaSrtpCrypto tInSrtpCrypto,tSrtpCrypto;
					GetSrtpCrypto(dwCount,tSrtpCrypto);
					ptInSrtp->GetSrtpCrypto(dwInCount,tInSrtpCrypto);
					if (m_atSrtpCrypto[dwCount].IsSupport(tInSrtpCrypto))
					{
						tOutSrtp.m_dwCryptoCount = 1;
						if(!bUseInSrtp)
						{
							tOutSrtp.m_emSrtpMode = m_emSrtpMode;
							tOutSrtp.m_atSrtpCrypto[0] = tSrtpCrypto;
						}
						else
						{
							tOutSrtp.m_emSrtpMode = ptInSrtp->m_emSrtpMode;
							tOutSrtp.m_atSrtpCrypto[0] = tInSrtpCrypto;
						}
						nCryptoNum++;
						break;
					}
				}
				if ( 0 != nCryptoNum)
				{
					break;
				}
			}
		}
		if (nCryptoNum)
		{
			return TRUE ;
		}
		return FALSE;
	}
} TSrtpMediaSetting;
#endif

/*载荷类型的内部转换:
|<--------------加密和H239的载荷转换---------- >|<低字节为上层使用的类型>|
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+  0  +  0  +  0  + 0  +  1  +  1  +  1  +  1  +  payloadType           +             
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                       + H239+ AES + DES +NoEnc+   
*/
/// Encrypt Type
typedef enum
{
	emEncryptTypeNone = 1,    ///< none,00000001
	emEncryptTypeDES  = 2,    ///< DES,00000010
	emEncryptTypeAES  = 4,    ///< AES,00000100
	emEncryptTypeH239 = 8,    ///< H239,00001000
	emEncryptTypeAES256  = 16,///< AES256,00010000						  
}emEncryptType;

/// Terminal Label 
typedef struct PROTO_API tagTerminalLabel 
{
	u8 m_byMcuNo; ///< MCU number
	u8 m_byTerNo; ///< MT  number

	tagTerminalLabel()
	{
		Clear();		
	}

	void Clear()
	{
		m_byMcuNo = 0xff;
		m_byTerNo = 0xff;
	}

	bool operator ==(tagTerminalLabel& tLabel)
	{
		if (m_byMcuNo == tLabel.m_byMcuNo && m_byTerNo == tLabel.m_byTerNo)
			return true;
		else
			return false;
	}

	bool operator !=(tagTerminalLabel& tLabel)
	{
		if (m_byMcuNo != tLabel.m_byMcuNo || m_byTerNo != tLabel.m_byTerNo)
			return true;
		else
			return false;
	}

	/**
	* \brief             Valid check
	* \return            true:valid,false:invalid
	*/
	bool IsValid()
	{
		return ( m_byMcuNo <= LEN_MTNUM_PERCONF && m_byTerNo <= LEN_MTNUM_PERCONF);
	}
    
    /**
	* \brief              set Terminal Label
	* \param[in]         byMcuNo     :the mcu number
	* \param[in]         byTerNo     :the terminal number
	* \return            TRUE:if success,FALSE:failed
	*/
	BOOL32 SetTerminalLabel( u8 byMcuNo, u8 byTerNo )
	{
		if( byMcuNo <= LEN_MTNUM_PERCONF && byTerNo <= LEN_MTNUM_PERCONF )
		{
			m_byMcuNo = byMcuNo;
			m_byTerNo = byTerNo;
            return TRUE;
		}
        return FALSE;
	}

	/**
	* \brief              Get Terminal Label
	* \param[out]         pMcuNo     :to get the mcu number
	* \param[out]         pMcuNo     :to get the terminal number
	*/
	void GetTerminalLabel( u8 *pMcuNo, u8 *pTerNo )
	{
		*pMcuNo = m_byMcuNo;
		*pTerNo = m_byTerNo;
	}

	/**
	* \brief             get the mcu number
	* \return            the mcu number
	*/
	u8 GetMcuNo()
	{
		return m_byMcuNo;
	}
    
	/**
	* \brief             get the terminal number
	* \return            the mt number
	*/
	u8 GetTerNo()
	{
		return  m_byTerNo;
	}
}TTERLABEL,*PTTERLABEL;




#define LOG_MAXBUFFER_LENGTH	65536
#define LOG_LOGPATH_LENGTH	256

/*
typedef struct tagTLogInfo
{
	FILE* pLogFile;								///< file descriptor, LogFile
	FILE* pLogRecord;							///< file descriptor, used to record the current log number
	s32 nCurFileNum;							///< Current log number
	s32 nMaxFileNum;							///< Maximum log number
	s8 achLogRecord[LOG_FILENAME_LENGTH];		///< name and storage path, used to record the current log number
	s8 achLogName[LOG_FILENAME_LENGTH];			///< Log name and storage path
	s32 nFileMaxSize;							///< the size of every logfile(M)

	void Clear()
	{
		pLogFile = NULL;
		pLogRecord = NULL;
		nCurFileNum = 0;
		nMaxFileNum = 50;
		memset(achLogRecord, 0, LOG_FILENAME_LENGTH);
		memset(achLogName, 0, LOG_FILENAME_LENGTH);
		nFileMaxSize = 60;///< 60M
	}

	tagTLogInfo()
	{
		Clear();
	}
} TLogInfo;
*/

/// ------------------------------function--------------------------------------------
/**
* \brief             Set sipLog default info
* \param[in]         ptLogInfo				:log information:pLogRecord,pLogFile,nMaxFileNum
* \param[in]         pFilePath				:log storage path
* \param[in]         pFilePath				:log name
* \param[in]         nFileMaxNum			:maximum log number
* \param[in]         nFlieMaxSize			:the size of every logfile(M)
* \return            void
*/
//PROTO_API void SetSipLogInfo(TLogInfo* ptLogInfo, s8 *pFilePath, s8 *pLogName, s32 nFileMaxNum, s32 nFlieMaxSize);

/**
* \brief             Write log to file
* \param[in]         pLogFile			:file descriptor, LogFile
* \param[in]         pLogRecord			:file descriptor, used to record the current log number
* \param[in]         nCurFileNum		:Current log number
* \param[in]         nMaxFileNum		:Maximum log number
* \param[in]         pchMcuLogRecord	:name and storage path, used to record the current log number
* \param[in]         pchMcuLogName		:Log name and storage path
* \param[in]         achBuf				:printf buf
* \param[in]         dwLen				:buflen
* \return            void
*/
//PROTO_API void WriteLogToFile(TLogInfo *ptLogInfo, s8* achBuf, u32 dwLen);

/**
* \brief             Get Product Name
* \param[in]         nProductId     :Product ID
* \return            is a string,the name of product
*/
PROTO_API const s8 *GetProductName(EmVendorProductId emProductId);

/**
* \brief             according to the name of product to retrieve its vendor id
* \param[in]         nProductId        :product name
* \param[in]         nProductId        :the length of product name
* \return            emUNKNOWN:if error occured,ProductID:if successed
*/
PROTO_API EmVendorProductId RetrieveVendor(const s8* pszProductId, u32 nProductIdSize);

namespace KDV
{
	namespace utils
	{
		/**
		* \brief             Make the input string lowercased and return
		* \param[in]         pchStr        :product name
		* \param[out]        pchStr        :the lowercased of product name
		* \return            NULL:if the input string is null, the lowercased string:successed
		*/
		PROTO_API s8*		strlcase(INOUT s8* pchStr);

		/**
		* \brief             Make the input string uppercased and return
		* \param[in]         pchStr        :product name
		* \param[out]        pchStr        :the uppercased of product name
		* \return            NULL:if the input string is null, the uppercased string:successed
		*/
		PROTO_API s8*		strucase(INOUT s8* pchStr);

		/**
		* \brief             Convert IPv4 address to a string 
		* \note              parameter pchIP must pre-allocated before calling this interface
		* \param[in]         dwIpAddr        :the IPv4 address
		* \param[out]        pchIP           :the string of IPv4
		* \param[in]         nMaxSize        :no use
		* \return            NULL:if the pchIP is null, the string:successed
		*/
		PROTO_API s8*		ConvertIpToStr(IN u32 dwIpAddr, OUT s8* pchIP, IN s32 nMaxSize);

		/**
		* \brief             Get a random u32 number, used to generate CallID, EPID, Session, etc.
		* \return            the random number
		*/
		PROTO_API u32		GetRandomNumber(void);

		/// about CID
		typedef struct PROTO_API uCID
		{
			u8		m_abyMacAddress[6];
			u8		m_abyTime[8];
			BOOL32	m_bClock_seq_change;
		} uCID;
		
		/// storage the local cid
		typedef struct PROTO_API cidLocalStorage
		{
			u32		m_dwStartTime;
			u32		m_dwStartMilliTime;
			u32		m_dwOldMilliTime;
			u8		m_abyLastTime[8];
			BOOL32	m_bNotStart;
			BOOL32	m_bGenerated;
			uCID	m_tUCID;
			u8  	m_abyCid[16];
			u8  	m_abyOldCid[16];
			u16     m_wClock_seq;
		} cidLocalStorage;
		
		/**
		* \brief             GetTime 
		* \note              Parameter pbyTime and clockSeqChange must pre-allocated before calling this interface
		* \param[out]        pbyTime                  :array of time
		* \param[out]        clockSeqChange           :if clock's sequence changed
		* \return            cidLocalStorage* ,storage the local cid
		*/
		PROTO_API cidLocalStorage *GetTime(OUT u8 *pbyTime, OUT BOOL32 *clockSeqChange);

		/**
		* \brief             Generate a GUID
		* \return            the string of the guid
		*/
		PROTO_API u8*		GetGUID(void);
	}
	namespace NET
	{
		/**
		* \brief             Get MAC address 
		* \note              parameter pbyMAC must pre-allocated before calling this interface
		* \note              ????????
		* \param[out]        pbyMAC                  :array of MAC
		*/
		PROTO_API void	GetMACaddress(OUT u8* pbyMAC);
		//s32	GetLocalAddress(s8* pchIPAddr, s8* ETH_NAME /* = "eth0" */);
		//s32	GetLocalMac(u8* pbyVMac, s8* ETH_NAME /* = "eth0" */);
	}

	namespace SYS
	{
		//////////////////////////////////////////////////////////////////////////
		/// System - Date time
		//////////////////////////////////////////////////////////////////////////
		PROTO_API u32		timerGetTimeInMilliseconds(void);
		PROTO_API u32		timerGetTimeInSeconds(void);

		//////////////////////////////////////////////////////////////////////////
		/// File System - Directory operations
		//////////////////////////////////////////////////////////////////////////
		PROTO_API BOOL32	isDirectoryExisting	(IN const char* strFolder);
		PROTO_API BOOL32	CreateDirectory		(IN const char* strFolder, IN void* pAttr);
		PROTO_API BOOL32	RemoveDirectory		(IN const char* strFolder);
		PROTO_API BOOL32	isDirEmpty			(IN const char* strFolder);
		PROTO_API BOOL32	isDirectory			(IN const char* strFolder);
		PROTO_API BOOL32	IsDiskFull			(IN const char* strPath);

		//////////////////////////////////////////////////////////////////////////
		/// File System - File operations
		//////////////////////////////////////////////////////////////////////////
		PROTO_API BOOL32	IsFileExisted		(IN const char* strFileName);
		PROTO_API u64		getFileSize			(IN const char* strFileName);
		PROTO_API BOOL32	DeleteFile			(IN const char* strFileName);
		PROTO_API s8*		getModifiedTime		(IN const char* strFileName);
		PROTO_API s8*		getCreateTime		(IN const char* strFileName);

		//////////////////////////////////////////////////////////////////////////
		/// Endian type
		//////////////////////////////////////////////////////////////////////////
		PROTO_API BOOL32	IsLitttleEndian		();

        PROTO_API u64 htonll2(u64 host);	// host long 64 to network
        PROTO_API u64 ntohll2(u64 host);	//network to host long 64
        
	}

	namespace algorithm
	{
		/// Diffie¨CHellman key exchange
		namespace DH
		{
#define LEN_DHKEY_MAX		(u16)256                ///< dhkey max length
#define LEN_DH_X			(u16)8                  ///< dh中的随机数长度
#define LEN_DHKEY			(u16)64                 ///< dhkey的长度
#define LEN_H235KEY_MAX		(u16)64					///< (1-65535)  
#define FREEVLONG(vl)		{if(vl != 0) {KDV::algorithm::DH::vlongFree(&vl);}}
			
			typedef long*  verylong;
			
			PROTO_API void vlongFree(verylong *x);
			
			/// m_abyHalfKey = g^x mod n -->[ A = g^a mod p (B = g^b mod p) ==> K = B^a mod p (K = A^b mod p) ]
			typedef struct PROTO_API tagDHSet
			{
				u8	m_abyHalfKey[LEN_DHKEY_MAX];
				u8	m_abyModSize[LEN_DHKEY_MAX];
				u8	m_abyGenerator[LEN_DHKEY_MAX];
				s32 m_nHalfKeyBits;
				s32 m_nModSizeBits;
				s32 m_nGenBits;
				
				verylong n;
				verylong g;
				verylong x;
				
				tagDHSet();
				~tagDHSet();
				void Reset();
				u8* GetHalfKey();
				s32 GetHalfKeyBits();
				s32 SetHalfKeyBits(s32 nBits);
				s32 SetHalfKey(u8 *pbyHalfKey, s32 nBits);
				
				u8* GetModSize();
				s32 GetModSizeBits();
				s32 SetModSizeBits(s32 nBits); 
				s32 SetModeSize(u8 *pbyModSize, s32 nBits);
				
				u8* GetGenerator();
				s32 GetGenBits();
				s32 SetGenBits(s32 nBits); 
				s32 SetGenerator(u8 *pbyGenerator, s32 nBits);
			}TDHSet;
		} // End of namespace DH

		namespace BASE64
		{
			/// 暂未实现: Code to be merged/combined 
			PROTO_API BOOL32 base64_encode(const u8* pbyInput, u32 dwInLen, u8* pbyOutput, u32 &dwOutLen);
			PROTO_API BOOL32 base64_decode(const u8* pbyInput, u32 dwInLen, u8* pbyOutput, u32 &dwOutLen);
		} // End of namespace BASE64

		namespace MD5
		{
			// 暂未实现: Code to be merged/combined, CBB5.0/20-cbb/kdvsipadapter/source/md5.cpp
			/* MD5 context. */
			/*==========================================================*/
			/* GLOBAL.H - RSAREF types and constants
			*/
			/* PROTOTYPES should be set to one if and only if the compiler supports
				function argument prototyping.
				The following makes PROTOTYPES default to 0 if it has not already
				been defined with C compiler flags.
			*/
#ifndef PROTOTYPES
	#define PROTOTYPES 1
#endif

typedef u8 *POINTER; ///< POINTER defines a generic pointer type

/** 
*PROTO_LIST is defined depending on how PROTOTYPES is defined above.
*If using PROTOTYPES, then PROTO_LIST returns the list, otherwise it
*  returns an empty list.
*/
#if PROTOTYPES
	#define PROTO_LIST(list) list
#else
	#define PROTO_LIST(list) ()
#endif
/*================================================================*/
			typedef struct PROTO_API MD5_CTX
			{
				u32 state[4];        ///< state (ABCD) 
				u32 count[2];        ///< number of bits, modulo 2^64 (lsb first) 
				u8 buffer[64];       ///< input buffer 
			} MD5_CTX;

			/// MD5 functions
			PROTO_API void MD5Init (MD5_CTX *);
			PROTO_API void MD5Update (MD5_CTX *, u8 *, u32);
			PROTO_API void MD5Final (u8 [16], MD5_CTX *);
			PROTO_API void MD5toString(u8 *digest, s8* buff);
		} // End of namespace MD5

		namespace SHA1
		{
			// ????????: Code to be merged/combined 

		} // End of namespace SHA1

	} // End of namespace algorithm

} // End of namespace KDV

/// 加密同步结构 TEncryptSync 
typedef struct PROTO_API tagEncryptSync
{
	s32			  m_nSynchFlag;			         ///< shall be the Dynamic PayloadType for H.323
	u8			  m_abyH235Key[LEN_H235KEY_MAX]; ///< H.235 encoded value(1-65535)
	s32           m_nH235KeyLen;				 ///< H.235 key length

	tagEncryptSync()
	{
		Reset();
	}

	void Reset()
	{
		m_nSynchFlag  = 0;
		m_nH235KeyLen = 0;
		memset( m_abyH235Key, 0, sizeof(m_abyH235Key) );
	}

	/**
	* \brief             Convert members order,host order or network order.
	* \param[in]         bhton                  :TRUE: from host order to network, FALSE:from network order to host order
	*/
	void host2net(BOOL32 bhton)
	{
		if (bhton)
		{
			m_nSynchFlag  = htonl(m_nSynchFlag);
			m_nH235KeyLen = htonl(m_nH235KeyLen);
		}
		else
		{
			m_nSynchFlag  = ntohl(m_nSynchFlag);
			m_nH235KeyLen = ntohl(m_nH235KeyLen);
		}
	}

	/**
	* \brief             set SynchFlag 
	* \param[in]         nFlag                  :the SynchFlag value
	*/
	void SetSynchFlag(s32 nFlag)
	{ 
		m_nSynchFlag = nFlag; 
	}

	/**
	* \brief             get SynchFlag 
	* \return            the SynchFlag
	*/
	s32  GetSynchFlag() 
	{
		return m_nSynchFlag; 
	}


	/**
	* \brief             set H235Key 
	* \param[in]         pBuf           :the buffer of the H235Key 
	* \param[in]         nLen           :the buffer length
	* \return            H235KeyLen
	*/
	s32 SetH235Key(u8 *pBuf, s32 nLen)
	{
		m_nH235KeyLen = Minimum(Maximum(0, nLen), (s32)LEN_H235KEY_MAX);
		memcpy(m_abyH235Key, pBuf, m_nH235KeyLen);
		return m_nH235KeyLen;
	}	

	/**
	* \brief             get H235KeyLen 
	* \return            H235KeyLen
	*/
	s32 GetH235KeyLen() 
	{
		return m_nH235KeyLen; 
	}

	/**
	* \brief             get H235Key 
	* \return            the array of H235Key
	*/
	u8* GetH235Key()
	{
		return m_abyH235Key;
	}
}TEncryptSync;



#endif
