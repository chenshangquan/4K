#ifndef QT_STRUCT_H_
#define QT_STRUCT_H_
#include "kdvtype.h"
#include <string.h>


#define QT_MT_LISTEN_PORT	6001	//量子终端监听端口
const u8 Auth[] = "KDVCOM";

// 密钥长度
#define QT_KEY_LEN_16 16
//获取秘钥的最大的长度
#define QT_KEY_MAX_LEN	1024
//码流秘钥
#define QT_MAX_MEDIA_KEY	1024

// 认证信息长度
#define KDV_AUTH_INFO_LEN 32
//别名长度
#define QT_ALIAS_MAX_LEN	64

//呼叫ID长度 协议用
#define QT_UNIQUE_ID_MAX_LEN	64

#define QTIN
#define QTOUT

typedef u32 QTCALLHANDLE;		//ConfId+EpId
typedef u32 QTBFCPHANDLE;		//ConfId+EpId
typedef u64 QTKEYHANDLE;		//ReqKeyFlag+SectionIndex
typedef u32	QTMediaKeyHandle;

// qt库所用到的APPID
#define APPID_QTLIB_BEGIN   60000
#define APPID_QTLIB_SEVER   APPID_QTLIB_BEGIN+1
#define APPID_QTLIB_CLIENT  APPID_QTLIB_SEVER+1

//返回原因
enum EmQtRetReason
{
	EmQtRetReason_Idle = 0,
	EmQtRetReason_Success,
		
	//本地原因
	EmQtRetReason_Local,
		
	//断链和未握手
	EmQtRetReason_DisConnect,
	EmQtRetReason_ShakeFail,
		
	//申请失败
	EmQtRetReason_ReqFail,
		
	//获取失败
	EmQtRetReason_GetFail,
		
	//对端视频终端 失败
	EmQtRetReason_PeerUnreach,//不可达
	EmQtRetReason_PeerGetFail,//获取失败
		
	//清除失败
	EmQtRetReason_ClearFail,
	EmQtRetReason_TimeOut,

	//密钥不匹配
	EmQtRetReason_NotMatch,

	//InitMediaKey失败后 需要挂断呼叫
	EmQtRetReason_MediaKeyFail,
	//平台侧已存在码流秘钥
	EmQtRetReason_PlatMediaKeyExist,
};

enum EmQtMTState
{
	EmQTState_Idle = 0,
	EmQTState_Shaked,
	EmQTState_Disconnect, 
};

//别名类型 
enum EmQtAliasType
{
	EmQtAliasType_Alias,
	EmQtAliasType_E164,
	EmQtAliasType_H323ID,
	EmQtAliasType_Email,
	EmQtAliasType_EpID,
	EmQtAliasType_GKID,
	EmQtAliasType_PartyNumber,
	EmQtAliasType_Others,
};

enum EmQtKeyFrequency
{
	EmQtFrequencyEverySeconds,	//每秒一次
	EmQtFrequencyEveryMinutes,	//每分钟一次
	EmQtFrequencyEveryConf,		//每个会议一个秘钥
};

//回调qt的状态
typedef void (* QtCBQtMTState)( EmQtMTState emQtMtState, void* wParam);

//回调码流秘钥给上层
typedef void(*QtCBMediaKey)(u32 dwConfID, QTMediaKeyHandle hMediaHandle, s8 szAlias[QT_ALIAS_MAX_LEN+1], u8 acMediaKey[QT_MAX_MEDIA_KEY+1], u32 dwKeyLen, EmQtKeyFrequency emKeyFrequency, u32 wQtFlag, u16 wConverIndex);
typedef void(*QtCBMediaKeyDstMT)(u32 dwConfID, s8 szAlias[QT_ALIAS_MAX_LEN+1]);
//回调callhandle
typedef void(*QtCBCallHandle)(u32 dwPeerMtIp, u32 dwPeerQtID, s8 szAlias[QT_ALIAS_MAX_LEN+1], EmQtAliasType emAliasType,  QTCALLHANDLE hCallHandle, u8 szCallID[QT_UNIQUE_ID_MAX_LEN+1], BOOL32 bDel);
//回调mediahanle
typedef void(*QtCBMediaHandle)(u32 dwPeerMtIp, u32 dwPeerQtID, s8 szAlias[QT_ALIAS_MAX_LEN+1], EmQtAliasType emAliasType, QTMediaKeyHandle hMediaHandle);

typedef void(*QtQueryAlias)(u16 wIndex, s8 szAlias[QT_ALIAS_MAX_LEN]);

//加密会议中回调失败原因给上层业务
typedef void (*QtCBQtRetReason)(EmQtRetReason emQtRetReason, void* wParam);

//码流秘钥取得失败时回调
typedef void(*QtCBMediaKeyFail)(u32 dwPeerMtIp, s8 szLocalAlias[QT_ALIAS_MAX_LEN+1], s8 szPeerAlias[QT_ALIAS_MAX_LEN+1]);

//回调bfcphandle
typedef void(*QtCBBfcpHandle)(u32 dwPeerMtIp, QTBFCPHANDLE hBfcpHandle, s8 szBfcpID[QT_UNIQUE_ID_MAX_LEN+1]);

enum EmQtProtocol
{
	EmQtProtocol_H323,
	EmQtProtocol_SIP,
	EmQtProtocol_End,
};

typedef struct tagTQTQueryInfo
{
	u16		m_wIndex;
	s8		m_szAlias[QT_ALIAS_MAX_LEN+1];
	tagTQTQueryInfo()
	{
		memset(this, 0, sizeof(tagTQTQueryInfo));
	}
}TQTQueryInfo;

typedef struct tagTQtInitParam
{
	u32								m_dwQtListenIp;								//本地量子终端的ip
	u32								m_dwQtMtId;									//本地量子终端的id  例如：340100001
	u16								m_wQtListenPort;							//量子终端的监听端口  固定：6001
	s8								m_acAuth[KDV_AUTH_INFO_LEN+1];				//认证信息  固定：KDVCOM
	 
	QtCBQtMTState					m_pfCBState;								//回调qtmt的状态(掉线)，上层清理秘钥
	QtCBMediaKey					m_pfCBMediaKey;								//回调由秘钥机生成的码流秘钥
	QtCBCallHandle					m_pfCBCallHandle;							//被叫端回调callhandle
	QtCBMediaHandle					m_pfCBMediaHandle;							//被叫端回调mediahandle
	QtQueryAlias					m_pcCBQueryAlias;							//平台侧量子库使用，用来查询呼叫别名的加密等级
	QtCBQtRetReason					m_pfCBRetReason;							//加密会议中返回QT密钥相关错误原因

	BOOL32							m_bEncryption;								//是否开启加密，终端使用
	EmQtKeyFrequency				m_emKeyFrequency;							//加密等级，终端使用
	BOOL32							m_bPlatform;								//使用该库的业务类型，TRUE 为平台，FALSE 为终端
	EmQtProtocol					m_emProtocol;
	BOOL32							m_bG400;									//使用该库的业务类型，TRUE为G400， FALSE为其他
	
	QtCBBfcpHandle					m_pfCbBfcpHandle;							//bfcp的被端回调bfcphandle

	tagTQtInitParam()
	{
		memset(this, 0, sizeof(tagTQtInitParam));
		m_wQtListenPort = QT_MT_LISTEN_PORT;
		memcpy(m_acAuth, Auth, strlen((s8*)Auth));
		m_bEncryption = FALSE;
		m_emProtocol = EmQtProtocol_SIP;
	}
	
}TQtInitParam;

typedef struct tagTQtCallParam
{
	EmQtKeyFrequency				m_emKeyFrequency;							//本端加密等级
	u32								m_dwConfID;									//会议ID，用来回调码流秘钥
	u32								m_dwPeerQtId;								//对端量子终端ID
	u32								m_dwPeerMtIp;								//对端视频终端IP
	EmQtAliasType					m_emAliasType;								//对端别名类型, G400 使用
	s8								m_szLocalAlias[QT_ALIAS_MAX_LEN + 1];		//本端别名，QTLIB G400区分本端ipc使用
	s8								m_szPeerAlias[QT_ALIAS_MAX_LEN + 1];		//对端别名
	BOOL32							m_bCallEncryption;							//本端是否加密,协议使用	
	u8								m_achUniqueId[QT_UNIQUE_ID_MAX_LEN + 1];
	tagTQtCallParam()
	{
		memset(this, 0, sizeof(tagTQtCallParam));
		m_emKeyFrequency = EmQtFrequencyEveryConf;
		m_bCallEncryption = FALSE;
	}

}TQtCallParam;


#endif
