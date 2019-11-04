#ifndef _KDVMEDIANET_0603_H_
#define _KDVMEDIANET_0603_H_

#include "osp.h"
#include "kdvdef.h"

/*for ios*/
#if (defined(__APPLE__) && defined(__MACH__)) || \
    (defined(macintosh) || defined(Macintosh)) || \
    defined(__MACOSX__)

/*for kdvmedianet64.h*/
# define _KDVMEDIANET_64_HEADER
#endif // for ios

#ifdef _KDVMEDIANET_64_HEADER
#include <kdvmedianet64.h>
#else

#if defined(_MSC_VER)
#include <Winsock2.h>
#include <ws2tcpip.h>
#if defined(_DLL_MEDIANET_)
#define MN_C_SYM    extern "C" __declspec(dllexport)
#define MN_CPP_SYM  __declspec(dllexport)
#else
#define MN_C_SYM    extern "C" __declspec(dllimport)
#define MN_CPP_SYM  __declspec(dllimport)
#endif
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#define MN_C_SYM    extern "C"
#define MN_CPP_SYM  __attribute__ ((visibility("default")))
#endif

#define  MEDIANET_NO_ERROR                  (u16)0//成功返回值
#define  ERROR_MEDIA_NET_BASE               (u16)16000
#define  ERROR_SND_PARAM                    (ERROR_MEDIA_NET_BASE+1)//设置发送模块参数出错
#define  ERROR_SND_NOCREATE                 (ERROR_MEDIA_NET_BASE+2)//发送模块没有创建
#define  ERROR_SND_MEMORY                   (ERROR_MEDIA_NET_BASE+3)//发送模块内存操作出错
#define  ERROR_SND_CREATE_SOCK              (ERROR_MEDIA_NET_BASE+4)//发送模块创建socket
#define  ERROR_RTP_SSRC                     (ERROR_MEDIA_NET_BASE+5)//RTP同步源错误.
#define  ERROR_LOOPBUF_CREATE               (ERROR_MEDIA_NET_BASE+6)//环状缓冲创建错误
#define  ERROR_RTP_NO_INIT                  (ERROR_MEDIA_NET_BASE+7)//RTP类有些对象没创建

#define  ERROR_RTCP_NO_INIT                 (ERROR_MEDIA_NET_BASE+8)//RTP类有些对象没创建
#define  ERROR_RTCP_SET_TIMER               (ERROR_MEDIA_NET_BASE+9)//RTCP设置定时器出错

#define  ERROR_RTP_SSRC_COLLISION           (ERROR_MEDIA_NET_BASE+10)//RTP 同步源出错


#define  ERROR_H261_PACK_NUM                (ERROR_MEDIA_NET_BASE+12)//H261的包数不合理
#define  ERROR_PACK_TOO_LEN                 (ERROR_MEDIA_NET_BASE+13)//G.711的数举包太长
#define  ERROR_H263_PACK_NUM                (ERROR_MEDIA_NET_BASE+14)//H263的包数不合理
#define  ERROR_H263_PACK_TOOMUCH            (ERROR_MEDIA_NET_BASE+15)//H263的数据包太长

#define  ERROR_SND_INVALID_SOCK             (ERROR_MEDIA_NET_BASE+16)//发送模块无效socket
#define  ERROR_SND_SEND_UDP                 (ERROR_MEDIA_NET_BASE+17)//发送模块数据包投递失败（目标可能不可达）
#define  ERROR_SND_FRAME                     (ERROR_MEDIA_NET_BASE+18)//发送模块帧拆包错误

#define  ERROR_NET_RCV_PARAM                (ERROR_MEDIA_NET_BASE+100)//设置接收模块参数出错
#define  ERROR_NET_RCV_NOCREATE             (ERROR_MEDIA_NET_BASE+101)//接收模块没有创建
#define  ERROR_NET_RCV_MEMORY               (ERROR_MEDIA_NET_BASE+102)//接收模块内存操作出错
#define  ERROR_RCV_RTP_CREATE               (ERROR_MEDIA_NET_BASE+103)//接收模块RTP创建失败
#define  ERROR_RCV_RTP_CALLBACK             (ERROR_MEDIA_NET_BASE+104)//接收模块设置RTP回调函数失败
#define  ERROR_RCV_RTP_SETREMOTEADDR        (ERROR_MEDIA_NET_BASE+105)//接收模块设置RTP远端地址失败
#define  ERROR_CREATE_LOOP_BUF              (ERROR_MEDIA_NET_BASE+106)//创建环状缓冲失败
#define  ERROR_RCV_NO_CREATE                (ERROR_MEDIA_NET_BASE+107)//接收模块接收对象没有创建

#define  ERROR_WSA_STARTUP                  (ERROR_MEDIA_NET_BASE+200)//wsastartup error
#define  ERROR_CREATE_SEMAPORE              (ERROR_MEDIA_NET_BASE+201)// create semapore error


#define  ERROR_SOCK_INIT                    (ERROR_MEDIA_NET_BASE+301)//socket 没有初始化
#define  ERROR_SOCK_CREATE                  (ERROR_MEDIA_NET_BASE+301)//socket 没有初始化
#define  ERROR_SOCKET_CALL                  (ERROR_MEDIA_NET_BASE+302)//调用socket() 函数出错
#define  ERROR_BIND_SOCKET                  (ERROR_MEDIA_NET_BASE+303)//socket 绑定出错
#define  ERROR_SOCK_ADDRINUSE               (ERROR_MEDIA_NET_BASE+304)//socket 端口已使用
#define  ERROR_SOCK_RTP_ADDRINUSE           (ERROR_MEDIA_NET_BASE+305)//socket RTP端口已使用
#define  ERROR_SOCK_RTCP_ADDRINUSE          (ERROR_MEDIA_NET_BASE+306)//socket RTCP端口已使用

#define  ERROR_ADDTO_CHECK_THREAD           (ERROR_MEDIA_NET_BASE+401)

#define  ERROR_SEND_BUFFMGR                 (ERROR_MEDIA_NET_BASE+411)
#define  ERROR_SEND_BUFF_FULL               (ERROR_MEDIA_NET_BASE+412)

#define  ERROR_RECV_BUFFMGR                 (ERROR_MEDIA_NET_BASE+451)
#define  ERROR_RECV_BUFF_FULL               (ERROR_MEDIA_NET_BASE+452)


#define  ERROR_RECV_FRAME_EMPTY             (ERROR_MEDIA_NET_BASE+461)
#define  ERROR_RECV_FRAME_WAITTIME          (ERROR_MEDIA_NET_BASE+462)
#define  ERROR_RECV_FRAME_FULL              (ERROR_MEDIA_NET_BASE+463)
#define  ERROR_RECV_RTP_CHECK               (ERROR_MEDIA_NET_BASE+464)

#define  ERROR_CREATE_THREAD                (ERROR_MEDIA_NET_BASE+204)//创建线程出错

#define  ERROR_LOOPBUF_FULL                 (ERROR_MEDIA_NET_BASE+205)//循环缓冲满
#define  ERROR_NULL_POINT                   (ERROR_MEDIA_NET_BASE+206)//空指针

#define  ERROR_SET_DECRYPTKEY               (ERROR_MEDIA_NET_BASE+210)//设置解密key失败
#define  ERROR_DECRYPT_FRAME                (ERROR_MEDIA_NET_BASE+212)//解密一帧失败
#define  ERROR_SET_ENCRYPTKEY               (ERROR_MEDIA_NET_BASE+213)//设置加密key失败
#define  ERROR_ENCRYPT_FRAME                (ERROR_MEDIA_NET_BASE+215)//加密一帧失败
#define  ERROR_SET_USERDATA                 (ERROR_MEDIA_NET_BASE+216)//加密一帧失败
#define  ERROR_SENDER_FEC_CRC               (ERROR_MEDIA_NET_BASE+217)//发送fec计算错误
#define  ERROR_RECEIVER_FEC_CRC             (ERROR_MEDIA_NET_BASE+218)//接收fec计算错误
#define  ERROR_RECEIVER_FEC_MODE_INVALID    (ERROR_MEDIA_NET_BASE+219)//接收fec模式错误
#define  ERROR_SENDER_FEC_INORDER           (ERROR_MEDIA_NET_BASE+220)//发送fec乱序
#define  ERROR_SENDER_FEC_INVALID_PARAM     (ERROR_MEDIA_NET_BASE+221)//发送fec错误参数
#define  ERROR_ARRAY_TOO_SMALL              (ERROR_MEDIA_NET_BASE+222)//数组太小

#define MIN_PRE_BUF_SIZE                    (s32)28// G.711需再加一字节

#define MAX_H261_HEADER_LEN      (s32)388//
#define MAX_H263_HEADER_LEN      (s32)3076//
#define MAX_H263PLUS_HEADER_LEN  (s32)3076//

#ifndef DES_ENCRYPT_MODE
#define DES_ENCRYPT_MODE         (u8)0      //DES加密模式
#define AES_ENCRYPT_MODE         (u8)1      //AES加密模式
#define ENCRYPT_KEY_SIZE         (u8)32     //密钥长度 取其中的较大值
#define DES_ENCRYPT_KEY_SIZE     (u8)8      //DES密钥长度
#define AES_ENCRYPT_KEY_SIZE_MODE_A (u8)16  //AES Mode-A 密钥长度
#define AES_ENCRYPT_KEY_SIZE_MODE_B (u8)24  //AES Mode-B 密钥长度
#define AES_ENCRYPT_KEY_SIZE_MODE_C (u8)32  //AES Mode-C 密钥长度
#endif

#ifndef  MAX_NETSND_DEST_NUM
#define  MAX_NET_DEST_NUM   5
#endif

#define MAX_USERDATA_LEN    16

//播放策略(必须与medianet.h定义保持同步)
#define MAX_DELAY_UNKNOWN        0
#define MAX_DELAY_QUALITY        1
#define MAX_DELAY_QUALITY_NOAVS  2
#define MAX_DELAY_SPEED          3
#define MAX_DELAY_BALANCE        4


//Frame Header Structure
typedef struct tagFrameHdr {
	u8     m_byMediaType; //媒体类型
	u8    *m_pData;       //数据缓冲
	u32    m_dwPreBufSize;//m_pData缓冲前预留了多少空间，用于加
	// RTP option的时候偏移指针一般为12+4+12
	// (FIXED HEADER + Extence option + Extence bit)
	u32    m_dwDataSize;  //m_pData指向的实际缓冲大小缓冲大小
	u8     m_byFrameRate; //发送帧率,用于接收端
	u32    m_dwFrameID;   //帧标识，用于接收端
	u32    m_dwTimeStamp; //时间戳, 用于接收端
    u64    m_qwCaptureMs; //采集时间
                          //发送时为IN参数,代表本地MONOTONIC时间,ms单位(0则采用发送时间作为采集时间)
                          //接收时为OUT参数,代表网络NTP时间,ms单位(0代表尚未收到SR信息,无法计算采集时间)
	u32    m_dwSSRC;      //同步源, 用于接收端
	union {
		struct {
			BOOL32    m_bKeyFrame;    //频帧类型（I or P）
			u16       m_wVideoWidth;  //视频帧宽
			u16       m_wVideoHeight; //视频帧宽
			BOOL32    m_bHighProfile; // H264 HP标识
		} m_tVideoParam;
		struct{
				   BOOL32    m_bIncludeAudioLevel; //是否包含audio level
				   BOOL32 	 m_bV; //是否为语音
				   u8		 m_byAudioLevel; // 音频能量级 0~127(-dBov)
				   u8        m_byAudioMode;
				   s32       m_nPacMs; //每帧时长
			  }m_tAudioParam;
	};

} FRAMEHDR, *PFRAMEHDR;

typedef struct tagNetSession {
	TOspNetAddr tRTPAddr;
	TOspNetAddr tRTCPAddr;
} TNetSession;

/*网络参数*/
typedef struct tagMnetNetParam {
	u8          m_byRemoteNum;                    //实际远端地址个数,发送可以
	//最多MAX_NET_DEST_NUM，接收暂时只支持1个
	TNetSession m_tLocalNet;                     //当地地址对
	TNetSession m_tRemoteNet[MAX_NET_DEST_NUM];  //远端地址对
} TMnetNetParam;

typedef struct tagFecParam {
	BOOL32      m_bUseFec;
	BOOL32      m_bIntraFrame;
	u8          m_nFecMode;
	s32         m_nFecPacklen;
	s32         m_nFecDataPackNum;
	s32         m_nFecCrcPackNum;
} TFecParam;

/*发送模块状态信息*/
typedef struct tagKdvSndStatus {
	u8           m_byMediaType;   //媒体类型
	u32          m_dwMaxFrameSize;//最大的帧大小
	u32          m_dwNetBand;     //发送带宽(bps)
	u32          m_dwFrameID;     //数据帧标识
	u8           m_byFrameRate;   //发送频率
	TMnetNetParam    m_tSendAddr;     //发送地址
	TFecParam    m_tFecParam;
	BOOL32       m_bReverseG7221c;
} TKdvSndStatus;

/*发送模块统计信息*/
typedef struct tagKdvSndStatistics {
	u32 m_dwPackSendNum; //已发送的包数
	u32 m_dwFrameNum;    //已发送的帧数
	u32 m_dwFrameLoseNum;//由于缓冲满等原因造成的发送的丢帧数
} TKdvSndStatistics;

/*发送scoket信息*/
typedef struct tagKdvSndSocketInfo {
	BOOL32 m_bUseRawSocket;
	u32    m_dwSrcIP;
	u32    m_wPort;
} TKdvSndSocketInfo;

/*接收模块状态信息*/
typedef struct tagKdvRcvStatus {
	BOOL32          m_bRcvStart;  //是否开始接收
	u32             m_dwFrameID;  //数据帧ID
	TMnetNetParam       m_tRcvAddr;   //接收当地地址
	u32             m_dwFecFrameId;
	BOOL32          m_bReverseG7221c;

	TFecParam       m_tFecPar;
} TKdvRcvStatus;

/*解码器统计信息*/
typedef struct tagKdvRcvStatistics {
	u32    m_dwPackNum;       //启用重传策略前收到的总包数
	u32    m_dwPackLose;      //启用重传策略后收到的总包数
	u32    m_dwPackIndexError;//包乱序数
	u32    m_dwFrameNum;      //已接收的帧数
	u32     m_dwPhysicalPackLose;//启用重传策略前的丢包总数
	//  u32    m_dwFrameLoseNum;  //由于数据源切换清空队列等原因造成的接收的丢帧数

	u32 m_dwFecPackNum;//所收到的fec包数
	u32 m_dwFecPackLose;//经fec纠错后还丢掉的包，组帧时真正所丢的包
	u32 m_dwFecRealFrameNum;//fec的帧数（即所收到的fec组数）
	u32 m_dwFecNeedRecovery;
	u32 m_dwFecRecoSucc;
	u32 m_dwFecRecoFail;
} TKdvRcvStatistics;

typedef struct tagRtpPack {
	u8   m_byMark;          //是否帧边界1表示最后一包
	u8   m_byExtence;       //是否有扩展信息
	u8   m_byPadNum;        //可能的padding长度
	u8   m_byPayload;       //载荷
	u32  m_dwSSRC;          //同步源
	u16  m_wSequence;       //序列号
	u32  m_dwTimeStamp;     //时间戳
	u8  *m_pExData;         //扩展数据
	s32  m_nExSize;         //扩展大小：sizeof(u32)的倍数；
	u8  *m_pRealData;       //媒体数据
	s32  m_nRealSize;       //数据大小
	s32  m_nPreBufSize;     //m_pRealData前预分配的空间;
    BOOL32 m_bIncludeAudioLevel; //是否包含audio level
	BOOL32 m_bV; //是否为语音
	u8	 m_byAudioLevel;    // 音频能量级 0~127(-dBov)
} TRtpPack;

typedef struct {
	u32 m_dwTotalBlock;
	u32 m_dwCurFreeBlock;
	u32 m_dwMinFreeBlock;

	u32 m_dwBitrate;        //单位kbps
	u32 m_dwRealBitrate;    //单位kbps

	BOOL32 m_bDirectSend;

	BOOL32 m_bFecEnable;

} TSendRtpStatus;

//发送端高级设置参数
typedef struct tagAdvancedSndInfo {
	s32      m_nMaxSendNum;      // 根据带块计算的最大发送次数;
	BOOL32   m_bRepeatSend;      // 对于 (mp4) 是否重发
	u16      m_wBufTimeSpan;
	BOOL32   m_bEncryption;      // 对于 (mp4/H.26X/Audio) 是否设置加密
	u8       m_byEncryptMode;    // 加密模式 Aes 或者 Des
	u16      m_wKeySize;         // 加密密钥长度
	s8       m_szKeyBuf[ENCRYPT_KEY_SIZE + 1]; // 加密密钥缓冲
	u8       m_byLocalActivePT;  // 动态载荷PT值
	s32      m_nResendTimes;  //重发次数
	s32      m_nResendSpan;   //重发间隔
} TAdvancedSndInfo;

//接收端高级设置参数
typedef struct tagAdvancedRcvInfo {
	BOOL32    m_bConfuedAdjust;  // 对于 (mp3) 是否做乱序调整
	BOOL32    m_bRepeatSend;     // 对于 (mp4) 是否重发
	BOOL32    m_bDecryption;     // 对于 (mp4/H.26X/Audio) 是否设置解密
	u8        m_byDecryptMode;   // 解密模式 Aes 或者 Des
	u16       m_wKeySize;        // 解密密钥长度
	s8        m_szKeyBuf[ENCRYPT_KEY_SIZE + 1]; // 解密密钥缓冲
	u8        m_byRmtActivePT;   // 接收到的动态载荷的Playload值
	u8        m_byRealPT;        // 该动态载荷实际代表的的Playload类型，同于发送时的PT约定
	u8          m_byLastFrameType;
} TAdvancedRcvInfo;

typedef struct {
	//block use info
	u32 m_dwTotalBlock;
	u32 m_dwCurFreeBlock;
	u32 m_dwMinFreeBlock;

	u32 m_dwRealBitrate;         //单位kbps

	//frame num
	u32 m_dwCurFrameNum;
	u32 m_dwMaxFrameNum;

	u32 m_dwFrameDuration;
	u32 m_dwDelayFrameNum;

	BOOL32 m_bDirectCallback;
	s32 m_nAudioDelayNum;

    BOOL32 m_bHasCompleteKeyFrame; // Buffer中是否已经收到完整的视频关键帧
                                   // 已经收到的话,可以立即停止请求关键帧
                                   // (无需等到回调关键帧后才停止请求)

	//丢包统计
	u32 m_dwRecvNum;
	u32 m_dwRealLostNum;
	u32 m_dwLostBackOkNum;

	u32 m_dwRegetNum;

	u32 m_dwCurMaxBuffTime;
	u32 m_dwLoopTime;        //loop time
	u32 m_dwCurLoopTime;

	u32 m_dwDisSortTime;

	//FEC
	BOOL32 m_bFecEnable;
	u32 m_dwFecPacket;
	u32 m_dwFecCorrect;
} TRecvRtpStatus;

//动态带宽检测结果(必须与medianet.h定义保持同步)
typedef struct {
    u32         m_dwSSRC;    //SSRC
    BOOL32      m_bEnabled;  //是否支持动态带宽调整
    u64         m_qwID;      //业务层ID
    u32         m_dwGroup;   //接收组ID
    u32         m_dwBitrate; //链路带宽(bps)
} TBweReceiver; // 接收通道

//Frame Rcv CallBack Function
typedef   void (*PFRAMEPROC)(PFRAMEHDR pFrmHdr, u32 dwContext);
//RTP PACK Call back
typedef   void (*PRTPCALLBACK)(TRtpPack *pRtpPack, u32 dwContext);

enum RTCPSTATUS {
    RTCP_OFF          = 0,
    RTCP_COMPOUND     = 1,
    RTCP_NONCOMPOUND  = 2,
};

#define MAX_MAP_NUM 20
typedef struct tagMapSet {
	u8 m_byMapNum; //最大MAX_MAP_NUM
	u8 m_abyMapType[MAX_MAP_NUM][2]; //[ ][0] for remote type, [ ][1] for real type
} TMapSet;

#ifndef MNET_SIZEOF_CRYPT_CFG_T
#define MNET_SIZEOF_CRYPT_CFG_T  256
#endif

typedef union {
    u8 data[MNET_SIZEOF_CRYPT_CFG_T];
    void* align;
} TMnetCryptCfg;

//必须与mnet_sec.h定义一致
typedef enum {
    MNET_CRYPT_DATA_NULL = 0,
    MNET_CRYPT_DATA_RTP,   //rtp通道
    MNET_CRYPT_DATA_RTCP,  //rtcp通道
    MNET_CRYPT_DATA_ALL,   //rtp&&rtcp通道共用秘钥
    MNET_CRYPT_DATA_MAX,
} TMnetCryptDataType;

//必须与mnet_sec.h定义一致
typedef enum {
    MNET_CRYPT_PKT_NULL = 0,
    MNET_CRYPT_PKT_H235,    //老的medianet都为此类型
    MNET_CRYPT_PKT_SRTP,    // srtp 封包
    MNET_CRYPT_PKT_DTLS,
    MNET_CRYPT_PKT_MAX,
} TMnetCryptPktType;

//必须与mnet_sec.h定义一致
typedef enum {
    MNET_CRYPT_KEY_NULL = 0,
    MNET_CRYPT_KEY_STATIC,    //老的加密 && srtp加密都为此类型
    MNET_CRYPT_KEY_QUANTUM,   //量子加密
    MNET_CRYPT_KEY_DTLS,
    MNET_CRYPT_KEY_MAX,
} TMnetCryptKeyType;

//必须与mnet_sec.h定义一致
typedef enum {
    MNET_CRYPT_ALGORITHM_NULL = 0,
    MNET_CRYPT_ALGORITHM_AES_CBC,
    MNET_CRYPT_ALGORITHM_AES_CM,
    MNET_CRYPT_ALGORITHM_AES_GCM,     //srtp cipher
    MNET_CRYPT_ALGORITHM_AES_ICM,     //srtp cipher
    MNET_CRYPT_ALGORITHM_SM4_CM,      //srtp cipher
    MNET_CRYPT_ALGORITHM_SM1_CM,      //srtp cipher
    MNET_CRYPT_ALGORITHM_HMAC_SHA1,   //srtp auth
    MNET_CRYPT_ALGORITHM_MAX,
} TMnetCryptAlgoType;

typedef enum {
    MNET_KEY_LEN_128 = 1, //128bit
    MNET_KEY_LEN_256,
} TMnetCrypKeyLen;

typedef enum {
    MNET_AUTH_TAG_LEN_0 = 1, //不认证
    MNET_AUTH_TAG_LEN_32,  //32bit
    MNET_AUTH_TAG_LEN_64,
    MNET_AUTH_TAG_LEN_80,
    MNET_AUTH_TAG_LEN_128,
} TMnetCryptTagLen;

/********************************************************************
 * 函数名：MnetCryptCfgInit
 *
 * 功能：初始化加密配置结构体
 * default:不加密
 *
 *  srtp rtp policy support now
 *  sm1_cm_128_hmac_sha1_80/sm1_cm_128_hmac_sha1_null
 *  sm4_cm_128_hmac_sha1_80/sm4_cm_128_hmac_sha1_null
 *  aes_icm_128_hmac_sha1_80/aes_icm_128_hmac_sha1_32/aes_icm_128_hmac_sha1_null
 *  aes_icm_256_hmac_sha1_80/aes_icm_256_hmac_sha1_32/aes_icm_256_hmac_sha1_null
 *  aes_gcm_128_hmac_sha1_128/aes_gcm_128_hmac_sha1_64
 *  aes_gcm_256_hmac_sha1_128/aes_gcm_256_hmac_sha1_64
 *
 *  srtp rtcp policy support now
 *  sm1_cm_128_hmac_sha1_80
 *  sm4_cm_128_hmac_sha1_80
 *  aes_icm_128_hmac_sha1_80/aes_icm_128_hmac_sha1_32
 *  aes_icm_256_hmac_sha1_80/aes_icm_256_hmac_sha1_32
 *  aes_gcm_128_hmac_sha1_128/aes_gcm_128_hmac_sha1_64
 *  aes_gcm_256_hmac_sha1_128/aes_gcm_256_hmac_sha1_64
 * 参数说明：
 * @param ptCfg        - 需要被初始化的配置结构体
 * @param send         - 是发送还是接收
 *
 * 返回值：
 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
 ********************************************************************/
MN_C_SYM BOOL32 MnetCryptCfgInit(TMnetCryptCfg* ptCfg, BOOL32 send);

/********************************************************************
 * 函数名：MnetCryptCfgSetCipherAlgorithm
 *
 * 功能：设置加密用的加密算法
 *
 * 参数说明：
 * @param ptCfg        - 需要被设置的配置结构体
 * @param tDataType  - 设置哪个通道
 * @param tAlgorithm - 设置的加密算法
 *
 * 返回值：
 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
 ********************************************************************/
MN_C_SYM BOOL32 MnetCryptCfgSetCipherAlgorithm(TMnetCryptCfg* ptCfg,
                                          TMnetCryptDataType tDataType,
                                          TMnetCryptAlgoType tAlgorithm);

/********************************************************************
 * 函数名：MnetCryptCfgSetAuthAlgorithm
 *
 * 功能：设置认证用的加密算法
 *
 * 参数说明：
 * @param ptCfg        - 需要被设置的配置结构体
 * @param tDataType  - 设置哪个通道
 * @param tAlgorithm - 设置的加密算法
 *
 * 返回值：
 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
 ********************************************************************/
MN_C_SYM BOOL32 MnetCryptCfgSetAuthAlgorithm(TMnetCryptCfg* ptCfg,
                                          TMnetCryptDataType tDataType,
                                          TMnetCryptAlgoType tAlgorithm);

/********************************************************************
 * 函数名：MnetCryptCfgSetMasterKey
 *
 * 功能：设置秘钥类型和秘钥,本接口用于srtp
 *
 * 参数说明：
 * @param ptCfg        - 需要被设置的配置结构体
  * @param tDataType  - 设置哪个通道
 * @param tKeyType   - 设置的秘钥类型
 * @param wkeySize   - 秘钥的长度
 * @param bykey        - 秘钥
 * @parma tKeyLenAuch - 认证秘钥的长度
 * @param tKeyLenCipher - 加密秘钥的长度
 *
 * 返回值：
 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
 ********************************************************************/
MN_C_SYM BOOL32 MnetCryptCfgSetMasterKey(TMnetCryptCfg* ptCfg,
                                  TMnetCryptDataType tDataType,
                                  TMnetCryptKeyType tKeyType,
                                  u16 wKeySize, u8* byKey,
                                  TMnetCrypKeyLen tKeyLenAuch,
                                  TMnetCrypKeyLen tKeyLenCipher);

/********************************************************************
 * 函数名：MnetCryptCfgSetCipherKey
 *
 * 功能：设置加密用的某个通道的加密秘钥长度,用于H235加密,目前仅支持rtp aes加密
 *
 * 参数说明：
 * @param ptCfg        - 需要被设置的配置结构体
 * @param tDataType  - 设置哪个通道
 * @param wkeySize   - 秘钥的长度
 * @param bykey        - 秘钥
 *
 * 返回值：
 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
 ********************************************************************/
MN_C_SYM BOOL32 MnetCryptCfgSetCipherKey(TMnetCryptCfg* ptCfg,
                                  TMnetCryptDataType tDataType,
                                  u16 wKeySize, u8* byKey);

/********************************************************************
 * 函数名：MnetCryptCfgSetAuthKey
 *
 * 功能：设置加密用的某个通道的认证秘钥长度,用于H235,暂不支持认证
 *
 * 参数说明：
 * @param ptCfg        - 需要被设置的配置结构体
 * @param tDataType  - 设置哪个通道
 * @param wkeySize   - 秘钥的长度
 * @param bykey        - 秘钥
 *
 * 返回值：
 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
 ********************************************************************/
MN_C_SYM BOOL32 MnetCryptCfgSetAuthKey(TMnetCryptCfg* ptCfg,
                                  TMnetCryptDataType tDataType,
                                  u16 wKeySize, u8* byKey);

/********************************************************************
 * 函数名：MnetCryptCfgSetAuthTag
 *
 * 功能：设置加密用的某个通道的认证tag长度,用于srtp
 *
 * 参数说明：
 * @param ptCfg        - 需要被设置的配置结构体
 * @param tDataType  - 设置哪个通道
 * @param tTagLen     - 设置srtp rtp/rtcp 认证tag长度
 *
 * 返回值：
 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
 ********************************************************************/
MN_C_SYM BOOL32 MnetCryptCfgSetAuthTag(TMnetCryptCfg* ptCfg,
                                  TMnetCryptDataType tDataType,
                                  TMnetCryptTagLen tTagLen);

/********************************************************************
 * 函数名：MnetCryptCfgSetPkt
 *
 * 功能：设置通道的pkt类型
 *
 * 参数说明：
 * @param ptCfg        - 需要被设置的配置结构体
 * @param tDataType  - 设置哪个通道
 * @param tPktType  - 通道的pkt类型
 *
 * 返回值：
 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
 ********************************************************************/
MN_C_SYM BOOL32 MnetCryptCfgSetPkt(TMnetCryptCfg* ptCfg,
                                  TMnetCryptDataType tDataType,
                                  TMnetCryptPktType tPktType);

class MN_CPP_SYM CKdvMediaSnd
{
public:
	/********************************************************************
	 * 函数名：GetMediaSnd
	 *
	 * 功能：获得一个发送对象
	 *
	 * 实现说明：
	 * 接口类不允许上层new CKdvMediaSnd，要获得发送对象只能通过这个接口
	 *
	 *
	 * 参数说明：
	 * @param
	 *
	 * 返回值：
	 * @return NULL:表示失败  CKdvMediaSnd *:表示成功
	 ********************************************************************/
	static CKdvMediaSnd *GetMediaSnd();

	/********************************************************************
	 * 函数名：PutMediaSnd
	 *
	 * 功能：释放一个发送对象
	 *
	 * 实现说明：
	 * 释放由GetMeidaSnd获得的对象
	 *
	 *
	 * 参数说明：
	 * @param
	 *
	 * 返回值：
	 * @return
	 ********************************************************************/
	static void PutMediaSnd(CKdvMediaSnd *pCKdvMediaSnd);

	/********************************************************************
	 * 函数名：Create
	 *
	 * 功能：创建发送模块
	 *
	 * 实现说明：
	 *
	 * 参数说明：
	 * @param dwMaxFrameSize    - 最大的帧的大小
	 * @param dwNetBand         - 通道带宽(bps)(废弃不用,在SetSndInfo中设置)
	 * @param ucFramRate        - 发送的帧率(fps)
	 * @param ucMediaType       - 发送的媒体类型(如MEDIA_TYPE_H264)
	 * @param dwSSRC            - 发送的SSRC
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 ********************************************************************/
	virtual u16 Create(u32 dwMaxFrameSize, u32 dwNetBand, u8 ucFrameRate, u8 ucMediaType, u32 dwSSRC = 0) = 0;

	/********************************************************************
	 * 函数名：SetNetSndParam
	 *
	 * 功能：设置网络发送参数
	 *
	 * 实现说明：
	 * 进行底层套结子的创建，绑定端口,以及发送目标地址的设定等动作
	 * 如果参数一样重复设置直接返回，如果不一样，删除之前设置，重新创建
	 * NOTE:为了方便业务设置地址增加了地址相关宏(OSP_SET_NETADDR_ADDR)
	 *
	 * 参数说明：
	 * @param tNetParam    - 网络发送参数，具体见TNetParam
	 *                       网络地址和端口均为网络字节序
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 ********************************************************************/
	virtual u16 SetNetSndParam(TMnetNetParam tNetParam) = 0;

	/********************************************************************
	 * 函数名：RemoveNetSndLocalParam
	 *
	 * 功能：移除网络发送本地地址参数
	 *
	 * 实现说明：
	 * 进行底层套结子的删除，释放端口等动作
	 *
	 * 参数说明：
	 * @param
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 ********************************************************************/
	virtual u16 RemoveNetSndLocalParam() = 0;

	/********************************************************************
	 * 函数名：SetActivePT
	 *
	 * 功能：设置码流载荷值和发送类型映射
	 *
	 * 实现说明：
	 *
	 * 参数说明：
	 * @param byLocalActivePT    - 码流的本地载荷值
	 * @param byRmtActivePT		 - 映射类型(默认MEDIA_TYPE_NULL，不映射)
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 ********************************************************************/
	virtual u16 SetActivePT(u8 byLocalActivePT, u8 byRmtActivePT = MEDIA_TYPE_NULL) = 0;

	/********************************************************************
	 * 函数名：SetEncryptKey
	 *
	 * 功能：码流加密
	 *
	 * 实现说明：!!!deprecated,调用EnableCrypt
	 *
	 * 参数说明：
	 * @param pszKeyBuf     - 秘钥，NULL表示不加密
	 * @param wKeySize      - 秘钥的长度
	 * @param byEncryptMode - 加密算法(AES or DES)
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 ********************************************************************/
	virtual u16 SetEncryptKey(s8 *pszKeyBuf, u16 wKeySize, u8 byEncryptMode = DES_ENCRYPT_MODE) = 0;

	/********************************************************************
	 * 函数名：ResetFrameId
	 *
	 * 功能：重置帧ID
	 *
	 * 实现说明：
	 *
	 * 参数说明：
	 * @param
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 ********************************************************************/
	virtual u16 ResetFrameId() = 0;

	/********************************************************************
	 * 函数名：ResetSSRC
	 *
	 * 功能：重置同步源SSRC
	 *
	 * 实现说明：
	 *
	 * 参数说明：
	 * @param dwSSRC    - 同步源
	 * @param bForce      - 是否强制使用dwSSRC,只用于与网呈对通,且ssrc只允许为非零偶数
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 ********************************************************************/
	virtual u16 ResetSSRC(u32 dwSSRC = 0, BOOL32 bForce = FALSE) = 0;

	/********************************************************************
	 * 函数名：ResetRSFlag
	 *
	 * 功能：重置发送端重传处理的开关
	 *
	 * 实现说明：
	 * 打开该开关发送端会对发送过的数据进行缓存，以备收到重传请求时重传
	 * 关闭该开关发送端将不会对发送过的数据缓存，这时即使收到重传请求，也
	 * 无法发送重传包
	 *
	 * 参数说明：
	 * @param bRepeatSnd    - 是否打开重传处理(默认值TRUE,打开)
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 ********************************************************************/
	virtual u16 ResetRSFlag(BOOL32 bRepeatSnd = FALSE) = 0;

	/********************************************************************
	 * 函数名：EnableQos
	 *
	 * 功能：qos开关
	 *
	 * 参数说明：
	 * @param bEnable    - 是否开启qos
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 ********************************************************************/
	virtual u16 EnableQos(BOOL32 bEnable) = 0;

	/********************************************************************
	 * 函数名：SetSndInfo
	 *
	 * 功能：设置通道带宽,编码帧率,编码码率
	 *
	 * 参数说明：
	 * @param dwNetBand    - 通道带宽(bps)
	 * @param ucFrameRate  - 编码帧率(fps)
            * @param dwBitRate    - 编码码率(bps)
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
     	 *
	 ********************************************************************/
	virtual u16 SetSndInfo(u32 dwNetBand, u8 ucFrameRate, u32 dwBitRate) = 0;

	/********************************************************************
	 * 函数名：GetTransportOverhead
	 *
	 * 功能：获取网络传输开销百分比
	 *
	 * 实现说明：获取网络传输开销
	 *
	 * 参数说明：

	 *@param byPercent 返回网络传输开销百分比
	 *
	 *  例:  byPercent返回20， 表示网络传输开销占用20%带宽，此时编码码率需控制在80%以下
	 *
	 * 返回值：
	 * @return  网络传输开销百分比
	 ********************************************************************/
	virtual u16 GetTransportOverhead(u8 *byPercent) = 0;


	/********************************************************************
	 * 函数名：SetTOS
	 *
	 * 功能：设置TOS
	 *
	 * 实现说明：设置发送RTP和RTCP包的TOS/DSCP
	 *
	 * 参数说明：
	 * @param byTOS    - type of service (IP TOS字段的值)
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 ********************************************************************/
	virtual u16 SetTOS(u8 byTOS) = 0;

	/********************************************************************
	 * 函数名：GetTOS
	 *
	 * 功能：获得TOS值
	 *
	 * 实现说明：
	 *
	 * 参数说明：
	 *
	 * 返回值：
	 * @return TOS值
	 ********************************************************************/
	virtual u16 GetTOS(u8 *byTOS) = 0;

	/********************************************************************
	 * 函数名：SetMTU
	 *
	 * 功能：设置发送的MTU
	 *
	 * 实现说明：
	 * 设置medianet发送包的最大值，不会设置网卡的MTU
	 *
	 * 参数说明：
	 * @param wMTU    - 最大的RTP包大小(默认值1300byte)
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 ********************************************************************/
	virtual u16 SetMTU(u16 wMTU) = 0;

	/********************************************************************
	 * 函数名: EnableVad
	 *
	 * 功能: 使能vad
	 * 实现说明:
	 *
	 * 参数说明:
	 * @param bEnable -是否使能vad
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 *******************************************************************/
	virtual u16 EnableVad(BOOL32 bEnable = FALSE) = 0;

	/********************************************************************
	 * 函数名：Send
	 *
	 * 功能：发送一帧数据
	 *
	 * 实现说明：
	 *
	 * 参数说明：
	 * @param pFrmHdr    - 帧结构体，具体见PFRAMEHDR
	 * @param bValid     - 是否有效(暂不支持)
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 ********************************************************************/
	virtual u16 Send(PFRAMEHDR pFrmHdr, BOOL32 bAvalid = TRUE) = 0;

	/********************************************************************
	 * 函数名：Send
	 *
	 * 功能：发送一个rtp包
	 *
	 * 实现说明：
	 *
	 * 参数说明：
	 * @param pRtpPack    - rtp包结构，具体见TRtpPack
	 * @param bTrans      - 是否转发(暂不支持)
	 * @param bValid      - 是否有效(暂不支持)
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 ********************************************************************/
	virtual u16 Send(TRtpPack *pRtpPack, BOOL32 bTrans = TRUE, BOOL32 bAvalid = TRUE) = 0;

	/********************************************************************
	 * 函数名：GetStatus
	 *
	 * 功能：获得发送状态
	 *
	 * 实现说明：
	 *
	 * 参数说明：
	 * @param tKdvSndStatus    - 状态信息，具体见TKdvSndStatus
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 ********************************************************************/
	virtual u16 GetStatus(TKdvSndStatus &tKdvSndStatus) = 0;

	/********************************************************************
	 * 函数名：GetStatistics
	 *
	 * 功能：获得发送统计信息
	 *
	 * 实现说明：
	 *
	 * 参数说明：
	 * @param tKdvSndStatistics    - 统计信息，具体见TKdvSndStatistics
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 ********************************************************************/
	virtual u16 GetStatistics(TKdvSndStatistics &tKdvSndStatistics) = 0;

	/********************************************************************
	 * 函数名：GetAdvancedSndInfo
	 *
	 * 功能：获得发送端设置的参数
	 *
	 * 实现说明：
	 *
	 * 参数说明：
	 * @param tAdvancedSndInfo    - 设置高级发送参数，具体见TAdvancedSndInfo
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 ********************************************************************/
	virtual u16 GetAdvancedSndInfo(TAdvancedSndInfo &tAdvancedSndInfo) = 0;

	/********************************************************************
	 * 函数名：GetNetSndParam
	 *
	 * 功能：获得发送网络参数
	 *
	 * 实现说明：
	 *
	 * 参数说明：
	 * @param ptNetSndParam    - 网络参数结构体，具体见TNetSndParam
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 ********************************************************************/
	virtual u16 GetNetSndParam(TMnetNetParam *ptNetSndParam) = 0;

	/********************************************************************
	 * 函数名：SetAudioResend
	 *
	 * 功能：对音频设置多倍发送
	 *
	 * 实现说明：
	 * 新的medianet只允许上层设置是否多倍发送，至于发送几份由medianet根据
	 * 网络情况决定
	 *
	 * 参数说明：
	 * @param bReSend    - 是否启用音频多倍发送(默认值TRUE,开启)
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 ********************************************************************/
	virtual u16 SetAudioResend(BOOL32 bReSend) = 0;

	/********************************************************************
	 * 函数名：SetReverseG7221c
	 *
	 * 功能：实现对G7221.c码流的翻转
	 *
	 * 实现说明：
	 * 对码流数据实现奇偶位翻转
	 * before: 123456789
	 * after : 214365879
	 *
	 * 参数说明：
	 * @param bReverse      - 是否翻转(默认值FALSE,不翻转)
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 ********************************************************************/
	virtual u16 SetReverseG7221c( BOOL32 bReverse ) = 0;

	/********************************************************************
	 * 函数名：ResetBwe
	 *
	 * 功能：使能/关闭动态带宽检测
	 *
	 * 实现说明：
	 * 使用方法如下
	 * 1. 使能动态带宽检测: ResetBwe
	 * 2. 周期获取动态带宽检测结果: GetBweStatus
	 * 3. 根据带宽设置编码码率(升速/降速
	 * 4. 根据带宽设置编码码率: SetSndInfo
	 *
	 * 参数说明：
	 * @param bEnable          - 使能/关闭
	 * @param dwMaxRate        - 最大编码码率(单位bps)
	 * @param dwMinRate        - 最小编码码率(单位bps)
	 * @param dwStartRate      - 初始编码码率(单位bps)
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 ********************************************************************/
    virtual u16 ResetBwe(BOOL32 bEnable, u32 dwMaxRate, u32 dwMinRate, u32 dwStartRate) = 0;

	/********************************************************************
	 * 函数名：GetBweStatus
	 *
	 * 功能：获取动态带宽检测结果
	 *
	 * 实现说明：
     * 参见ResetBwe
	 *
	 * 参数说明：
	 * @param pNumber          - 接收者个数(输入数组长度,输出实际接收者个数)
	 * @param pReceivers       - 带宽检测结果(每个接收者的动态带宽信息)
	 * @param pRevision        - 接收组版本(用于匹配不同发送通道间的接收组)
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
     *         (其中ERROR_ARRAY_TOO_SMALL表示输入数组过小,pNumber中包含实际接收者个数)
	 ********************************************************************/
    virtual u16 GetBweStatus(u32* pNumber, TBweReceiver* pReceivers, u32* pRevision) = 0;

	/********************************************************************
     * 函数名：SetId
     *
     * 功能：设置发送端的id
     *
     * 参数说明：
     * @param EndPointId    - 终端的id, 当前仅支持e164号
     * @param IdLen         - 终端id的长度
     * @param StreamId      - 流id
     *
     * 返回值：
     * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
     ********************************************************************/
    virtual u16 SetId(const char* EndPointId, u32 IdLen, u32 StreamId) = 0;

    /********************************************************************
     * 函数名：GetId
     *
     * 功能：获取发送端的id
     *
     * 参数说明：
     * @param EndPointId    - 终端的id, 当前仅支持e164号
     * @param IdLen         - 终端id的长度, 同时作为输入和输出
     * @param StreamId      - 流id
     *
     * 返回值：
     * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
     ********************************************************************/
    virtual u16 GetId(char* EndPointId, u32* IdLen, u32* StreamId) = 0;

	/********************************************************************
     * 函数名：EnableRtpExStrip
     *
     * 功能：是否剥掉RTP扩展头
     *
     * 参数说明：
     * @param enable        - 是否启用
     *
     * 返回值：
     * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
     ********************************************************************/
    virtual u16 EnableRtpExStrip(BOOL32 enable) = 0;

	/********************************************************************
	 * 函数名：EnableKeepAlive
	 *
	 * 功能：1. 使能打洞功能并设置用于打洞的网络发送参数
	 *       2. 停止打洞功能并删除相应网络参数
	 *
	 * 参数说明：
	 * @param tKeepAliveParam    - 网络发送参数，具体见TNetParam
	 *                             网络地址和端口均为网络字节序
	 * @param enable             - 是否使能打洞功能
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 ********************************************************************/
	virtual u16 EnableKeepAlive(BOOL32 enable, TMnetNetParam tKeepAliveParam) = 0;

	/********************************************************************
	 * 函数名：SetRtcpStatus
	 *
	 * 功能：设置RTCP状态
	 *
	 * 参数说明：
	 * @param status    - RTCP组包方法
	 *                     RTCP_OFF          = 0, 不启用RTCP
   	 *					   RTCP_COMPOUND     = 1, 发送RTCP复合包
     *					   RTCP_NONCOMPOUND  = 2, 不发送RTCP复合包
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 ********************************************************************/

    virtual u16 SetRtcpStatus(RTCPSTATUS status) = 0;

	/********************************************************************
	 * 函数名：EnableFEC
	 *
	 * 功能：使能FEC
	 *
	 * 参数说明：
	 * @param bEnableFec    - 是否启用FEC
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 ********************************************************************/
	virtual	u16 EnableFEC( BOOL32 bEnableFec ) = 0;

    /********************************************************************
	 * 函数名：EnableCrypt
	 *
	 * 功能：使能加密
	 *
	 * 参数说明：
	 * @param bEnableCrypt    - 是否启用加密
	 * @param TMnetCryptCfg    - 可用MnetCryptCfgInit 初始化等函数配置
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 ********************************************************************/
	virtual	u16 EnableCrypt( BOOL32 bEnableCrypt, TMnetCryptCfg *ptMnetCryptCfg) = 0;
protected:
	CKdvMediaSnd() {}
    virtual ~CKdvMediaSnd() {}

private:
	CKdvMediaSnd(CKdvMediaSnd &);
	void operator=(const CKdvMediaSnd &);
};

class MN_CPP_SYM CKdvMediaRcv
{
public:
	/********************************************************************
	 * 函数名：GetMediaRcv
	 *
	 * 功能：获得一个接收对象
	 *
	 * 实现说明：
	 * 接口类不允许上层new CKdvMediaRcv，要获得接收对象只能通过这个接口
	 *
	 * 参数说明：
	 * @param
	 *
	 * 返回值：
	 * @return NULL:表示失败  CKdvMediaRcv *:表示成功
	 ********************************************************************/
	static CKdvMediaRcv *GetMediaRcv();

	/********************************************************************
	 * 函数名：PetMediaRcv
	 *
	 * 功能：释放一个接收对象
	 *
	 * 实现说明：
	 * 释放GetMediaRcv接口获得的接收对象
	 *
	 *
	 * 参数说明：
	 * @param
	 *
	 * 返回值：
	 * @return NULL:表示失败  CKdvMediaRcv *:表示成功
	 ********************************************************************/
	static void PutMediaRcv(CKdvMediaRcv *pCKdvMediaRcv);

	/********************************************************************
	 * 函数名：Create
	 *
	 * 功能：创建接收模块
	 *
	 * 实现说明：
	 *
	 * 参数说明：
	 * @param dwMaxFrameSize     - 允许接收的最大帧大小
	 * @param pFrameCallBackProc - 帧回调函数
	 * @param dwContext          - 帧回调函数入参
	 * @param dwSSRC             - 接收码流的SSRC
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 ********************************************************************/
	virtual u16 Create(u32 dwMaxFrameSize, PFRAMEPROC pFrameCallBackProc, u32 dwContext, u32 dwSSRC = 0) = 0;

	/********************************************************************
	 * 函数名：Create
	 *
	 * 功能：创建接收模块
	 *
	 * 实现说明：
	 *
	 * 参数说明：
	 * @param dwMaxFrameSize     - 允许接收的最大帧大小
	 * @param PRtpCallBackProc   - RTP包回调函数
	 * @param dwContext          - RTP包回调函数入参
	 * @param dwSSRC             - 接收码流的SSRC
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 ********************************************************************/

	virtual u16 Create(u32 dwMaxFrameSize, PRTPCALLBACK PRtpCallBackProc, u32 dwContext, u32 dwSSRC = 0) = 0;

	/********************************************************************
	 * 函数名：SetNetRcvLocalParam
	 *
	 * 功能：设置接收地址参数
	 *
	 * 实现说明：
	 * 进行底层套结子的创建，绑定端口等动作
	 * 网络参数相同重复设置直接返回，参数不同会关闭之前的socket重新创建
	 * 如果端口复用，必须提供远端地址和端口，以便medianet查找回调
	 * 如果端口不复用，远端地址和端口可以填0
	 * 注意目前接收的远端地址目前只支持一个
	 * NOTE:为了方便业务设置地址增加了地址相关宏(OSP_SET_NETADDR_ADDR)
	 *
	 * 参数说明：
	 * @param tNetParam    - 网络参数结构体，具体见TNetParam
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 ********************************************************************/
	virtual u16 SetNetRcvLocalParam(TMnetNetParam tNetParam) = 0;

	/********************************************************************
	 * 函数名：RemoveNetRcvLocalParam
	 *
	 * 功能：移除接收地址参数
	 *
	 * 实现说明：
	 * 进行底层套结子的删除，释放端口等动作
	 *
	 * 参数说明：
	 * @param ptNetSndParam    - 网络参数结构体，具体见TNetSndParam
	 *                           网络地址和端口均为网络字节序
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 ********************************************************************/
	virtual u16 RemoveNetRcvLocalParam() = 0;

	/********************************************************************
	 * 函数名：SetActivePT
	 *
	 * 功能：(1)设置一对类型映射
	 *	        (2)byRmtActivePT=MEDIA_TYPE_ANY可设置任意远端类型映射至byRealPT
	 *	        (3)byRmtActivePT==byRealPT 可用于清除映射配置并设置码流载荷
	 *
	 * 实现说明：
	 * 码流是H264的它里面的载荷是105(比如华为)，但是我们的H264用106表示，
	 * 通过SetActivePT(105, 106)就可以按H264组帧回调
	 * SetActivePT(MEDIA_TYPE_ANY, 106) 不管远端什么pt值都按H264组帧回调
	 *
	 * 参数说明：
	 * @param byRmtActivePT    - 远端码流的载荷值
	 * @param byRealPT         - 本地实际载荷值
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 ********************************************************************/
	virtual u16 SetActivePT(u8 byRmtActivePT, u8 byRealPT) = 0;

	/********************************************************************
	 * 函数名：SetActivePT
	 *
	 * 功能：设置码流的类型映射集合
	 *
	 * 实现说明：
	 * 		映射集合元素个数为0时清除配置
	 *
	 * 参数说明：
	 * @param  tMapSet -类型映射集合
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 ********************************************************************/
	virtual u16 SetActivePT(TMapSet tMapSet) = 0;


	/********************************************************************
	 * 函数名：ResetRSFlag
	 *
	 * 功能：重置接收端重传处理的开关
	 *
	 * 实现说明：
	 * 接收端不再让业务设置重传请求的间隔，只允许设置是否启用，即在接收丢包
	 * 后是否发送重传请求，这需要发送端也把重传功能打开。
	 *
	 * 参数说明：
	 * @param bRepeatSnd    - 是否打开接收端重传请求功能(默认值是TRUE)
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 ********************************************************************/
	virtual u16 ResetRSFlag(BOOL32 bRepeatSnd = FALSE) = 0;

	/********************************************************************
	 * 函数名：ResetRtpCalllback
	 *
	 * 功能：重置RTP回调
	 *
	 * 实现说明：
	 *
	 * 参数说明：
	 * @param pRtpCallBackProc    - 回调函数
	 * @param dwContext           - 回调入参
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 ********************************************************************/
	virtual u16 ResetRtpCalllback(PRTPCALLBACK pRtpCallBackProc, u32 dwContext) = 0;

	/********************************************************************
	 * 函数名：SetDecryptKey
	 *
	 * 功能：码流解密
	 *
	 * 实现说明：!!!deprected,调用EnableCrypt
	 *
	 * 参数说明：
	 * @param pszKeyBuf     - 秘钥，NULL表示不加密
	 * @param wKeySize      - 秘钥的长度
	 * @param byEncryptMode - 加密算法(AES or DES)
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 ********************************************************************/
	virtual u16 SetDecryptKey(s8 *pszKeyBuf, u16 wKeySize, u8 byDecryptMode = DES_ENCRYPT_MODE) = 0;

	/********************************************************************
	 * 函数名: EnableVad
	 *
	 * 功能: 使能vad
	 * 实现说明:
	 *
	 * 参数说明:
	 * @param bEnable -是否使能vad
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 *******************************************************************/
	virtual u16 EnableVad(BOOL32 bEnable = FALSE) = 0;

	/********************************************************************
	 * 函数名：StartRcv
	 *
	 * 功能：开始接收
	 *
	 * 实现说明：
	 *
	 * 参数说明：
	 * @param
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 ********************************************************************/
	virtual u16 StartRcv() = 0;

	/********************************************************************
	 * 函数名：StopRcv
	 *
	 * 功能：停止接收
	 *
	 * 实现说明：
	 *
	 * 参数说明：
	 * @param
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 ********************************************************************/
	virtual u16 StopRcv() = 0;

	enum H264ProcessFlag {
		H264_DEL_SEI       = 0x1 << 0, //删除H264SEI信息
		H264_DEL_MULTI_PPS = 0x1 << 1, //删除H264多余PPS，保留第一个PPS
		H264_NALU_ALIGN    = 0x1 << 2, //H264 NALU按四字节对齐
	};
	/********************************************************************
	 * 函数名：SetH264Flag
	 *
	 * 功能：设置H264回调前是否处理标志位
	 *
	 * 实现说明：
	 * 会造成多一次拷贝，慎用!!!
	 * 可以同时打开关闭多个开关，支持或运算
	 *
	 * 参数说明：
	 * @param wH264Flag    - 处理标志位，见enum H264ProcessFlag
	                         (默认值0，不做处理)
	 * @param bOpen        - TRUE:表示打开 FALSE:表示关闭
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 ********************************************************************/
	virtual u16 SetH264Flag(u16 wH264Flag, BOOL32 bOpen) = 0;

	/********************************************************************
	 * 函数名：GetH264Flag
	 *
	 * 功能：获得H264处理标志位
	 *
	 * 实现说明：
	 *
	 * 参数说明：
	 * @param
	 *
	 * 返回值：
	 * @return enum H264ProcessFlag
	 ********************************************************************/
	virtual u16 GetH264Flag() = 0;

	/********************************************************************
	 * 函数名：GetStatus
	 *
	 * 功能：获得状态信息
	 *
	 * 实现说明：
	 *
	 * 参数说明：
	 * @param tKdvRcvStatus    - 状态信息，具体见TKdvRcvStatus
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 ********************************************************************/
	virtual u16 GetStatus(TKdvRcvStatus &tKdvRcvStatus) = 0;

	/********************************************************************
	 * 函数名：GetStatistics
	 *
	 * 功能：获得统计信息
	 *
	 * 实现说明：
	 *
	 * 参数说明：
	 * @param tKdvRcvStatistics    - 统计信息，具体见TKdvRcvStatistics
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 ********************************************************************/
	virtual u16 GetStatistics(TKdvRcvStatistics &tKdvRcvStatistics) = 0;

	/********************************************************************
	 * 函数名：GetAdvancedRcvInfo
	 *
	 * 功能：获得接收端设置的参数
	 *
	 * 实现说明：
	 *
	 * 参数说明：
	 * @param tAdvancedRcvInfo    - 设置高级发送参数，具体见TAdvancedRcvInfo
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 ********************************************************************/
	virtual u16 GetAdvancedRcvInfo(TAdvancedRcvInfo &tAdvancedRcvInfo) = 0;

	/********************************************************************
	 * 函数名：SetReverseG7221c
	 *
	 * 功能：实现对G7221.c码流的翻转
	 *
	 * 实现说明：
	 * 对码流数据实现奇偶位翻转
	 * before: 123456789
	 * after : 214365879
	 *
	 * 参数说明：
	 * @param bReverse      - 是否翻转(默认值为FALSE，不翻转)
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 ********************************************************************/
	virtual u16 SetReverseG7221c(BOOL32 bReverse) = 0;

	enum H264BuildFrameFlag {
		H264_DEPENDON_MARKER = 0,         //按marker位判断帧边界
		H264_DEPENDON_TIMESTAMP = 1,      //按时间错判断帧边界
	};
	/********************************************************************
	 * 函数名：SetH264BuildFrameFlag
	 *
	 * 功能：设置H264组帧时根据什么判断帧边界
	 *
	 * 实现说明：
	 * NOTE:暂时没实现
	 *
	 * 参数说明：
	 * @param tFalg    - 组帧时判断真边界的标志(默认值为H264_DEPENDON_TIMESTAMP)
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 ********************************************************************/
	virtual u16 SetH264BuildFrameFlag(H264BuildFrameFlag tFalg) = 0;

	/********************************************************************
	 * 函数名：SetH264HDFlag
	 *
	 * 功能：设置HD标志，用于标志回调的H264是否是HD
	 *
	 * HD 码流回调帧数据结构如下:
	 * ---------------------------------------------------------------------------
	 * | Len0 | Len1 | Len2 | ... | Len511 | NALU0 | NALU1 | NALU2 | ... | NALUx |
	 * ---------------------------------------------------------------------------
	 * 非HD码流回调帧数据结构如下:
	 * ---------------------------------------------------------------------------
	 * | 0001 | NALU0 | 0001 | NALU2  | 0001| NALU3 | 0001| NALU4 |0001 | .......|
	 * ---------------------------------------------------------------------------
	 *
	 * 实现说明：
	 * NOTE:暂时没实现
	 *
	 *
	 * 参数说明：
	 * @param bHdFlag    - 码流回调时是否按高清结构回调(默认值为0，按非HD回调)
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 ********************************************************************/
	virtual u16 SetH264HDFlag(BOOL32 bHdFlag) = 0;

	/********************************************************************
	 * 函数名：SetRtpPublicAddr
	 *
	 * 功能：设置本机的rtp接收端口对应的公网地址
	 *
	 * 实现说明：
	 * NOTE:暂时没实现
	 * 重传过nat时，设置本机的rtp接收端口对应的公网地址,
	 * 目的为使重传时不用广播
	 *
	 * 参数说明：
	 * @param dwRtpPublicIp    - 本地接收rtp对应的公网ip
	 * @param wRtpPublicPort   - 本地接收rtp对应的公网port
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 ********************************************************************/
	virtual u16 SetRtpPublicAddr(u32 dwRtpPublicIp, u16 wRtpPublicPort) = 0;

	/********************************************************************
	 * 函数名：SetMaxDelay
	 *
	 * 功能：设置最大接收延迟及播放策略
	 *
	 * 实现说明：
     * 接收延迟:
	 *  网络+播放延迟,单位ms,分为softlimit,hardlimit两种类型
     *
     * 播放策略:
     *  MAX_DELAY_QUALITY       - 质量优先(不关心softlimit,hardlimit)
     *  MAX_DELAY_SPEED         - 速度优先.设置hardlimit(不关心softlimit)
     *  MAX_DELAY_BALANCE       - 质量速度平衡.设置softlimit(不关心hardlimit)
     *
     * 默认采用质量优先策略
     *
	 * 参数说明：
	 * @param ucPolicy          - 播放策略
	 * @param dwSoftlimit       - 软上限
	 * @param dwHardlimit       - 硬上限
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 ********************************************************************/
	virtual u16 SetMaxDelay(u8 ucPolicy, u32 dwSoftlimit, u32 dwHardlimit) = 0;

	/********************************************************************
	 * 函数名：ResetBwe
	 *
	 * 功能：使能/关闭动态带宽检测
	 *
	 * 实现说明：
	 *
	 * 参数说明：
	 * @param bEnable          - 使能/关闭
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 ********************************************************************/
    virtual u16 ResetBwe(BOOL32 bEnable) = 0;

	/********************************************************************
     * 函数名：SetId
     *
     * 功能：设置接收端的id
     *
     * 参数说明：
     * @param EndPointId    - 终端的id, 当前仅支持e164号
     * @param IdLen         - 终端id的长度
     * @param StreamId      - 流id
     *
     * 返回值：
     * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
     ********************************************************************/
    virtual u16 SetId(const char* EndPointId, u32 IdLen, u32 StreamId) = 0;

    /********************************************************************
     * 函数名：GetId
     *
     * 功能：获取接收端的id
     *
     * 参数说明：
     * @param EndPointId    - 终端的id, 当前仅支持e164号
     * @param IdLen         - 终端id的长度
     * @param StreamId      - 流id
     *
     * 返回值：
     * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
     ********************************************************************/
    virtual u16 GetId(char* EndPointId, u32* IdLen, u32* StreamId) = 0;

	/********************************************************************
	 * 函数名：SetTOS
	 *
	 * 功能：设置TOS
	 *
	 * 实现说明：设置接收端发送RTCP包的TOS/DSCP
	 *
	 * 参数说明：
	 * @param byTOS    - type of service (IP TOS字段的值)
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 ********************************************************************/
	virtual u16 SetTOS(u8 byTOS) = 0;

	/********************************************************************
	 * 函数名：GetTOS
	 *
	 * 功能：获得TOS值
	 *
	 * 实现说明：
	 *
	 * 参数说明：
	 *
	 * 返回值：
	 * @return TOS值
	 ********************************************************************/
	virtual u16 GetTOS(u8 *byTOS) = 0;

	/********************************************************************
	 * 函数名：EnableKeepAlive
	 *
	 * 功能：1. 使能打洞功能并设置相应的网络发送参数
	 *       2. 停止打洞功能并删除相应网络参数
	 *
	 * 参数说明：
	 * @param tKeepAliveParam    - 网络发送参数，具体见TNetParam
	 *                             网络地址和端口均为网络字节序
	 * @param enable             - 是否使能打洞功能
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 ********************************************************************/
	virtual u16 EnableKeepAlive(BOOL32 enable, TMnetNetParam tKeepAliveParam) = 0;

	/********************************************************************
	 * 函数名：SetRtcpStatus
	 *
	 * 功能：设置RTCP状态
	 *
	 * 参数说明：
	 * @param status    - RTCP组包方法
	 *                     RTCP_OFF          = 0, 不启用RTCP
   	 *					   RTCP_COMPOUND     = 1, 发送RTCP复合包
     *					   RTCP_NONCOMPOUND  = 2, 不发送RTCP复合包
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 ********************************************************************/
	virtual u16 SetRtcpStatus(RTCPSTATUS status) = 0;

	/********************************************************************
	 * 函数名：EnableFEC
	 *
	 * 功能：使能FEC
	 *
	 * 参数说明：
	 * @param bEnableFec    - 是否启用FEC
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 ********************************************************************/
	virtual	u16 EnableFEC( BOOL32 bEnableFec ) = 0;

    /********************************************************************
	 * 函数名：EnableCrypt
	 *
	 * 功能：使能解密
	 *
	 * 参数说明：
	 * @param bEnableCrypt    - 是否启用加密
	 * @param ptMnetCryptCfg    - 可用MnetCryptCfgInit 初始化等函数配置
	 *
	 * 返回值：
	 * @return MEDIANET_NO_ERROR:表示成功 否则表示失败
	 ********************************************************************/
	virtual	u16 EnableCrypt( BOOL32 bEnableCrypt, TMnetCryptCfg *ptMnetCryptCfg ) = 0;

protected:
	CKdvMediaRcv() {}
    virtual ~CKdvMediaRcv() {}

private:
	CKdvMediaRcv(CKdvMediaRcv &);
	void operator=(const CKdvMediaRcv &);
};

#endif // for _KDVMEDIANET_64_HEADER

#endif  //_KDVMEDIANET_0603_H_

