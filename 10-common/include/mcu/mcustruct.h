/*****************************************************************************
   模块名      : mcu
   文件名      : mcustruct.h
   相关文件    : 
   文件实现功能: MCU结构
   作者        : 胡昌威
   版本        : V3.0  Copyright(C) 2001-2002 KDC, All rights reserved.
-----------------------------------------------------------------------------
   修改记录:
   日  期      版本        修改人      修改内容
   2004/09/16  3.5         胡昌威      创建
   2005/02/19  3.6         万春雷      级联修改、与3.5版本合并
******************************************************************************/
#ifndef __MCUSTRUCT_H_
#define __MCUSTRUCT_H_

#include "osp.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "kdvsys.h"
#include "mcuconst.h"
#include "kdvdef.h"
#include "vccommon.h"
#include "ummessagestruct.h"
#include "vcsstruct.h"

#ifdef WIN32
    #pragma comment( lib, "ws2_32.lib" ) 
    #pragma pack( push )
    #pragma pack( 1 )
    #define window( x )	x
#else
    #include <netinet/in.h>
    #define window( x )
#endif

#ifdef _LINUX_

#ifndef min
#define min(a,b) ((a)>(b)?(b):(a))
#endif
#ifndef max
#define max(a,b) ((a)>(b)?(a):(b))
#endif

#ifndef VOID
#define VOID void 
#endif

#endif  /* end _LINUX_ */

//定义MCU结构
typedef TMt TMcu;

//终端扩展结构 (len:34)
struct TMtExt : public TMt
{
protected:
	u8    m_byManuId;          //厂商编号,参见厂商编号定义
	u8    m_byCallMode;        //呼叫终端方式：0-不呼叫终端，手动呼叫 1-呼叫一次 2-定时呼叫
	u16   m_wDialBitRate;      //呼叫终端速率（网络序）单位KBPS
	u32   m_dwCallLeftTimes;   //定时呼叫终端的剩余呼叫次数
	u32   m_dwIPAddr;          //IP地址（网络序）
	char  m_achAlias[VALIDLEN_ALIAS];	//MCU、终端或外设别名
    u8    m_byProtocolType;         // 终端的协议类型
public:
    TMtExt() : m_byManuId(0),
               m_byCallMode(0),
               m_wDialBitRate(0),
               m_dwCallLeftTimes(0),
               m_dwIPAddr(0),
               m_byProtocolType(0)
    {
        memset( m_achAlias, 0, sizeof(m_achAlias) );
    }
    void   SetManuId(u8   byManuId){ m_byManuId = byManuId;} 
    u8     GetManuId( void ) const { return m_byManuId; }
    void   SetCallMode(u8   byCallMode){ m_byCallMode = byCallMode;} 
    u8     GetCallMode( void ) const { return m_byCallMode; }
    void   SetDialBitRate(u16 wDialBitRate ){ m_wDialBitRate = htons(wDialBitRate);} 
    u16    GetDialBitRate( void ) const { return ntohs(m_wDialBitRate); }
    void   SetCallLeftTimes( u32 dwCallLeftTimes){ m_dwCallLeftTimes = dwCallLeftTimes;} 
    u32    GetCallLeftTimes( void ) const { return m_dwCallLeftTimes; }
    void   SetIPAddr(u32    dwIPAddr){ m_dwIPAddr = htonl(dwIPAddr); } 
    u32    GetIPAddr( void ) const { return ntohl(m_dwIPAddr); }
    void   SetProtocolType(u8 byProtocolType) { m_byProtocolType = byProtocolType;}
    u8     GetProtocolType(void) const { return m_byProtocolType;}
	char*  GetAlias( void ) const{ return (s8 *)m_achAlias; }
	void   SetAlias( char* pszAlias )
	{
        memset( m_achAlias, 0, sizeof( m_achAlias ) );
		if( pszAlias != NULL )
		{
			strncpy( m_achAlias, pszAlias, sizeof( m_achAlias ) - 1);
		}
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//终端信息二次扩展结构 len:38
struct TMtExt2 : public TMt
{
public:
    TMtExt2():m_byHWVerId(0)
    {
        memset(m_achSWVerId, 0, sizeof(m_achSWVerId));
    }
    void SetMt(TMt &tMt)
    {
        memcpy(this, &tMt, sizeof(TMt));
    }
    void SetHWVerId( u8 byVerId ) { m_byHWVerId = byVerId;    }
    u8   GetHWVerId( void ) const { return m_byHWVerId;    }
    void SetSWVerId( LPCSTR lpszSWVerId )
    {
        if ( lpszSWVerId == NULL )
        {
            return;
        }
        u16 wLen = min(strlen(lpszSWVerId), sizeof(m_achSWVerId)-1);
        strncpy(m_achSWVerId, lpszSWVerId, wLen);
        m_achSWVerId[sizeof(m_achSWVerId)-1] = '\0';
    }
    LPCSTR GetSWVerId( void ) const { return m_achSWVerId;    }

protected:
    u8  m_byHWVerId;                    //终端硬件版本号
    s8  m_achSWVerId[MAXLEN_SW_VER-1];  //终端软件版本号
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

#ifndef SETBITSTATUS
#define SETBITSTATUS(StatusValue, StatusMask, bStatus)  \
    if (bStatus)    StatusValue |= StatusMask;          \
    else            StatusValue &= ~StatusMask;

#define GETBITSTATUS(StatusValue, StatusMask)  (0 != (StatusValue&StatusMask))   
#endif
    
//向上级mcu上报本端的终端状态时所用的结构 (len:10)
struct TSMcuMtStatus : public TMt
{
    enum TSMcuMtStatusMask
    {
        Mask_Fecc    =  0x01,
        Mask_Mixing  =  0x02,
        Mask_VidLose  =  0x04,
		Mask_CallMode =  0x08,
        Mask_SendingVideo = 0x10,
        Mask_SendingAudio = 0x20,
        Mask_RcvingVideo = 0x40,
        Mask_RecvingAudio = 0x80		
    };

protected:
	u8  m_byIsStatus;     //0-bit是否能遥控摄像头,1-bit是否在混音,2-bit是否视频源丢失
	u8  m_byCurVideo;     //当前视频源(1)
	u8  m_byCurAudio;     //当前音频源(1)
	u8  m_byMtBoardType;  //终端的板卡类型(MT_BOARD_WIN-0, MT_BOARD_8010-1, MT_BOARD_8010A-2, MT_BOARD_8018-3, MT_BOARD_IMT-4,MT_BOARD_8010C-5)

public:
	TSMcuMtStatus( void )
	{ 
		memset( this, 0, sizeof(TSMcuMtStatus));
		SetIsEnableFECC(FALSE);
		SetCurVideo(1);
		SetCurAudio(1);
		SetIsAutoCallMode(FALSE);
	}
	void SetIsEnableFECC(BOOL bCamRCEnable){ SETBITSTATUS(m_byIsStatus, Mask_Fecc, bCamRCEnable) } 
	BOOL IsEnableFECC( void ) const { return GETBITSTATUS(m_byIsStatus, Mask_Fecc); }
    void SetIsMixing(BOOL bMixing) { SETBITSTATUS(m_byIsStatus, Mask_Mixing, bMixing) } 
    BOOL IsMixing(void) const { return GETBITSTATUS(m_byIsStatus, Mask_Mixing); }
    void SetVideoLose(BOOL bVidLose){ SETBITSTATUS(m_byIsStatus, Mask_VidLose, bVidLose) }
    BOOL IsVideoLose( void ) const { return GETBITSTATUS(m_byIsStatus, Mask_VidLose);    }
	void SetCurVideo(u8 byCurVideo){ m_byCurVideo = byCurVideo;} 
	u8   GetCurVideo( void ) const { return m_byCurVideo; }
	void SetCurAudio(u8 byCurAudio){ m_byCurAudio = byCurAudio;} 
	u8   GetCurAudio( void ) const { return m_byCurAudio; }
	void SetMtBoardType(u8 byType) { m_byMtBoardType = byType; }
	u8   GetMtBoardType() const {return m_byMtBoardType; }
	void SetIsAutoCallMode( BOOL byAutoMode )   { SETBITSTATUS(m_byIsStatus, Mask_CallMode, byAutoMode); }
	BOOL IsAutoCallMode( void )                 { return GETBITSTATUS(m_byIsStatus, Mask_CallMode); }
    void SetSendVideo(BOOL bSend) { SETBITSTATUS(m_byIsStatus, Mask_SendingVideo, bSend) } 
    BOOL IsSendVideo( void ) const { return GETBITSTATUS(m_byIsStatus, Mask_SendingVideo); }
    void SetSendAudio(BOOL bSend) { SETBITSTATUS(m_byIsStatus, Mask_SendingAudio, bSend) } 
    BOOL IsSendAudio( void ) const { return GETBITSTATUS(m_byIsStatus, Mask_SendingAudio); }
    void SetRecvVideo(BOOL bRecv) { SETBITSTATUS(m_byIsStatus, Mask_RcvingVideo, bRecv) } 
    BOOL IsRecvVideo( void ) const { return GETBITSTATUS(m_byIsStatus, Mask_RcvingVideo); }
    void SetRecvAudio(BOOL bRecv) { SETBITSTATUS(m_byIsStatus, Mask_RecvingAudio, bRecv) } 
    BOOL IsRecvAudio( void ) const { return GETBITSTATUS(m_byIsStatus, Mask_RecvingAudio); }	
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//向上级mcu上报本端的终端状态时所用的结构 (len:8)
struct TMcuToMcuMtStatus
{
    enum TMcuToMcuMtStatusMask
    {
        Mask_Fecc   =   0x01,
        Mask_Mixing =   0x02,
        Mask_VideoLose = 0x04,
		Mask_CallMode =  0x08,
        Mask_SendingVideo = 0x10,
        Mask_SendingAudio = 0x20,
        Mask_RcvingVideo = 0x40,
        Mask_RecvingAudio = 0x80
    };

protected:
	u8  m_byIsStatus;     //0-bit是否能遥控摄像头,1-bit是否在混音,2-bit是否视频源丢失
	u8  m_byCurVideo;     //当前视频源(1)
	u8  m_byCurAudio;     //当前音频源(1)
	u8  m_byMtBoardType;  //终端的板卡类型(MT_BOARD_WIN-0, MT_BOARD_8010-1, MT_BOARD_8010A-2, MT_BOARD_8018-3, MT_BOARD_IMT-4,MT_BOARD_8010C-5)
	u32 m_dwPartId;       //网络序
public:
	TMcuToMcuMtStatus( void )
	{ 
		memset( this, 0, sizeof(TMcuToMcuMtStatus));
		SetIsEnableFECC(FALSE);
        SetIsMixing(FALSE);
        SetIsVideoLose(FALSE);
		SetCurVideo(1);
		SetCurAudio(1);
		SetIsAutoCallMode(FALSE);
	}
	void SetIsEnableFECC(BOOL bCamRCEnable){ SETBITSTATUS(m_byIsStatus, Mask_Fecc, bCamRCEnable) } 
	BOOL IsEnableFECC( void ) const { return GETBITSTATUS(m_byIsStatus, Mask_Fecc); }
    void SetIsMixing(BOOL bMixing) { SETBITSTATUS(m_byIsStatus, Mask_Mixing, bMixing) } 
    BOOL IsMixing(void) const { return GETBITSTATUS(m_byIsStatus, Mask_Mixing); }
    void SetIsVideoLose(BOOL bVideoLose) { SETBITSTATUS(m_byIsStatus, Mask_VideoLose, bVideoLose) }
    BOOL IsVideoLose(void) const { return GETBITSTATUS(m_byIsStatus, Mask_VideoLose);    }
	void SetCurVideo(u8 byCurVideo){ m_byCurVideo = byCurVideo;} 
	u8   GetCurVideo( void ) const { return m_byCurVideo; }
	void SetCurAudio(u8 byCurAudio){ m_byCurAudio = byCurAudio;} 
	u8   GetCurAudio( void ) const { return m_byCurAudio; }
	void SetMtBoardType(u8 byType) { m_byMtBoardType = byType; }
	u8   GetMtBoardType() const {return m_byMtBoardType; }
	void SetPartId(u32 dwPartId){ m_dwPartId = htonl(dwPartId);} 
	u32  GetPartId( void ) const { return ntohl(m_dwPartId); }
	void SetIsAutoCallMode( BOOL byAutoMode )   { SETBITSTATUS(m_byIsStatus, Mask_CallMode, byAutoMode); }
	BOOL IsAutoCallMode( void )                 { return GETBITSTATUS(m_byIsStatus, Mask_CallMode); }
    void SetSendVideo(BOOL bSend) { SETBITSTATUS(m_byIsStatus, Mask_SendingVideo, bSend) } 
    BOOL IsSendVideo( void ) const { return GETBITSTATUS(m_byIsStatus, Mask_SendingVideo); }
    void SetSendAudio(BOOL bSend) { SETBITSTATUS(m_byIsStatus, Mask_SendingAudio, bSend) } 
    BOOL IsSendAudio( void ) const { return GETBITSTATUS(m_byIsStatus, Mask_SendingAudio); }
    void SetRecvVideo(BOOL bRecv) { SETBITSTATUS(m_byIsStatus, Mask_RcvingVideo, bRecv) } 
    BOOL IsRecvVideo( void ) const { return GETBITSTATUS(m_byIsStatus, Mask_RcvingVideo); }
    void SetRecvAudio(BOOL bRecv) { SETBITSTATUS(m_byIsStatus, Mask_RecvingAudio, bRecv) } 
    BOOL IsRecvAudio( void ) const { return GETBITSTATUS(m_byIsStatus, Mask_RecvingAudio); }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//用于其他适配板完成RRQ时的认证信息记录 GatekeeperID/EndpointID
//TH323TransportAddress结构应与radstack协议栈相应结构 cmTransportAddress 一致 (len:44)
struct TH323TransportAddress
{
    u16  m_wlength; /* length in bytes of route */
    u32  m_dwip;
    u16  m_wport;
    int  m_ntype;
    u32  m_adwroute[7];
    int  m_ndistribution;
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//(len:310)
struct TH323EPGKIDAlias
{
protected:
	int  m_ntype;        //网络序
    u16  m_wlength;      //网络序
    char m_szAlias[256];
    int  m_npnType;      //网络序 
    TH323TransportAddress m_transport;
public:
	void SetIDtype( int ntype ){ m_ntype = htonl(ntype); }
	int  GetIDtype( void ){ return ntohl(m_ntype); }
	void SetIDlength( u16 wlength ){ m_wlength = htons(wlength); }
	u16  GetIDlength( void ){ return ntohs(m_wlength); }
	void SetIDpnType( int npnType ){ m_npnType = htonl(npnType); }
	int  GetIDpnType( void ){ return ntohl(m_npnType); }
	void SetIDAlias( char *pszAlias ){ memcpy( m_szAlias, pszAlias, 256 ); }
	char*  GetIDAlias( void ){ return m_szAlias; }
	void SetIDtransport( TH323TransportAddress *ptransport ){ memcpy( (void*)&m_transport, (void*)ptransport, sizeof(TH323TransportAddress) ); }
	TH323TransportAddress*  GetIDtransport( void ){ return &m_transport; }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//TRASInfo用于N+1备份，主板的RAS信息同步到备板(len:622)
struct TRASInfo 
{
protected:
    u32 m_dwGKIp;                   // 主板的gk地址－网络序
    u32 m_dwRRQIp;                  // 主板的呼叫发起地址，calladdress－网络序
    TH323EPGKIDAlias m_tGKIDAlias;  // 主板的GKID
    TH323EPGKIDAlias m_tEPIDAlias;  // 主板的EPID
    s8  m_achE164Num[MAXLEN_E164+1];// 主板的E164

public:
    TRASInfo() : m_dwGKIp(0),
                 m_dwRRQIp(0)
    {
        memset( &m_tGKIDAlias, 0, sizeof(m_tGKIDAlias) );
        memset( &m_tEPIDAlias, 0, sizeof(m_tEPIDAlias) );
        memset( &m_achE164Num, 0, sizeof(m_achE164Num) );
    }
    void SetGKIp(u32 dwIp){ m_dwGKIp = htonl(dwIp);    }
    u32  GetGKIp(void) { return ntohl(m_dwGKIp);    }
    void SetRRQIp(u32 dwIp){ m_dwRRQIp = htonl(dwIp);    }
    u32  GetRRQIp(void) { return ntohl(m_dwRRQIp);    }
    TH323EPGKIDAlias *GetGKID(void) { return &m_tGKIDAlias;    }
    void SetGKID(TH323EPGKIDAlias *ptH323GKID){ memcpy( &m_tGKIDAlias, ptH323GKID, sizeof(TH323EPGKIDAlias));    }
    TH323EPGKIDAlias *GetEPID(void) { return &m_tEPIDAlias;    }
    void SetEPID(TH323EPGKIDAlias *ptH323EPID){ memcpy( &m_tEPIDAlias, ptH323EPID, sizeof(TH323EPGKIDAlias));    }
    LPCSTR GetMcuE164(void) { return m_achE164Num; }
    void SetMcuE164(LPCSTR lpszE164Alias) 
    {
        if ( NULL != lpszE164Alias )
        {
            memcpy( m_achE164Num, lpszE164Alias, sizeof(m_achE164Num));    
            m_achE164Num[sizeof(m_achE164Num)-1] = '\0';
        }
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//业务消息类，最大处理28K长度消息
class CServMsg
{
protected:
	u16     m_wSerialNO;            //流水号
	u8      m_bySrcDriId;           //源DRI板号
	u8      m_bySrcMtId;            //源终端号
	u8      m_bySrcSsnId;           //源会话号
	u8      m_byDstDriId;           //目的DRI板号
    u8      m_byDstMtId;            //目的终端号
	u8      m_byMcuId;              //MCU号
	u8      m_byChnIndex;           //通道索引号
    u8      m_byConfIdx;            //会议索引号
	CConfId m_cConfId;              //会议号
	u16		m_wEventId;             //事件号
	u16		m_wTimer;               //定时
	u16		m_wErrorCode;           //错误码
	u16		m_wMsgBodyLen;          //消息体长度
    u8      m_byTotalPktNum;        //总包数（用于需要切包发送的消息）
    u8      m_byCurPktIdx;          //当前包索引（从0开始）
	u8      m_abyReserverd[12];     //保留字节
	u8      m_abyMsgBody[SERV_MSG_LEN-SERV_MSGHEAD_LEN];    //消息体
public:
	void  SetSerialNO(u16  wSerialNO){ m_wSerialNO = htons(wSerialNO);} 
    u16   GetSerialNO( void ) const { return ntohs(m_wSerialNO); }
    void  SetSrcDriId(u8   bySrcDriId){ m_bySrcDriId = bySrcDriId;} 
    u8    GetSrcDriId( void ) const { return m_bySrcDriId; }
    void  SetSrcMtId(u8   bySrcMtId){ m_bySrcMtId = bySrcMtId;} 
    u8    GetSrcMtId( void ) const { return m_bySrcMtId; }
    void  SetSrcSsnId(u8   bySrcSsnId){ m_bySrcSsnId = bySrcSsnId;} 
    u8    GetSrcSsnId( void ) const { return m_bySrcSsnId; }
    void  SetDstDriId(u8   byDstDriId){ m_byDstDriId = byDstDriId;} 
    u8    GetDstDriId( void ) const { return m_byDstDriId; }  
    void  SetDstMtId(u8   byDstMtId){ m_byDstMtId = byDstMtId;} 
    u8    GetDstMtId( void ) const { return m_byDstMtId; }
    void  SetMcuId(u8   byMcuId){ m_byMcuId = byMcuId;} 
    u8    GetMcuId( void ) const { return m_byMcuId; }
    void  SetChnIndex(u8   byChnIndex){ m_byChnIndex = byChnIndex;} 
    u8    GetChnIndex( void ) const { return m_byChnIndex; }
    void  SetConfIdx(u8   byConfIdx){ m_byConfIdx = byConfIdx;} 
    u8    GetConfIdx( void ) const { return m_byConfIdx; } 
    void  SetEventId(u16  wEventId){ m_wEventId = htons(wEventId);} 
    u16   GetEventId( void ) const { return ntohs(m_wEventId); }
    void  SetTimer(u16  wTimer){ m_wTimer = htons(wTimer);} 
    u16   GetTimer( void ) const { return ntohs(m_wTimer); }
    void  SetErrorCode(u16  wErrorCode){ m_wErrorCode = htons(wErrorCode);} 
    u16   GetErrorCode( void ) const { return ntohs(m_wErrorCode); }
    void  SetTotalPktNum(u8 byPktNum) { m_byTotalPktNum = byPktNum; }
    u8    GetTotalPktNum( void ) { return m_byTotalPktNum; }
    void  SetCurPktIdx(u8 byPktIdx) { m_byCurPktIdx = byPktIdx; }
    u8    GetCurPktIdx( void ) { return m_byCurPktIdx; }

	void Init( void );
	void SetNoSrc(){ SetSrcSsnId( 0 ); }
	void SetMsgBodyLen( u16  wMsgBodyLen );
	CServMsg( void );//constructor
	CServMsg( u8   * const pbyMsg, u16  wMsgLen );//constructor
	~CServMsg( void );//distructor
	void ClearHdr( void );//消息头清零
	CConfId GetConfId( void ) const;//获取会议号信息
	void SetConfId( const CConfId & cConfId );//设置会议号信息
	void SetNullConfId( void );//设置会议号信息为空
	u16  GetMsgBodyLen( void ) const;//获取消息体长度信息
	u16  GetMsgBody( u8   * pbyMsgBodyBuf, u16  wBufLen ) const;//获取消息体，由用户申请BUFFER，如果过小做截断处理
	u8   * const GetMsgBody( void ) const;//获取消息体指针，用户不需提供BUFFER
	void SetMsgBody( u8   * const pbyMsgBody = NULL, u16  wLen = 0 );//设置消息体
	void CatMsgBody( u8   * const pbyMsgBody, u16  wLen );//添加消息体
	u16  GetServMsgLen( void ) const;//获取整个消息长度
	u16  GetServMsg( u8   * pbyMsgBuf, u16  wBufLen ) const;//获取整个消息，由用户申请BUFFER，如果过小做截断处理
	u8   * const GetServMsg( void ) const;//获取整个消息指针，用户不需提供BUFFER
	void SetServMsg( u8   * const pbyMsg, u16  wLen );//设置整个消息
	const CServMsg & operator= ( const CServMsg & cServMsg );//操作符重载
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//重传结构 (len:12)
struct TPrsParam
{
public:
	TTransportAddr   m_tLocalAddr;		//为本地接收RTP地址
	TTransportAddr	 m_tRemoteAddr;		//为远端接收RTCP地址
public:
    void   SetLocalAddr(TTransportAddr tLocalAddr){ memcpy(&m_tLocalAddr,&tLocalAddr,sizeof(TTransportAddr)); } 
    TTransportAddr GetLocalAddr( void ) const { return m_tLocalAddr; }
    void   SetRemoteAddr(TTransportAddr tRemoteAddr){ memcpy(&m_tRemoteAddr,&tRemoteAddr,sizeof(TTransportAddr)); } 
    TTransportAddr GetRemoteAddr( void ) const { return m_tRemoteAddr; }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//重传时间跨度结构 (len:16)
struct TPrsTimeSpan
{
    TPrsTimeSpan()
    {
        memset(this, 0, sizeof(TPrsTimeSpan));
    }
    u16  m_wFirstTimeSpan;	  //第一个重传检测点
	u16  m_wSecondTimeSpan;   //第二个重传检测点
	u16  m_wThirdTimeSpan;    //第三个重传检测点
	u16  m_wRejectTimeSpan;   //过期丢弃的时间跨度
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//重传设备状态 (len:3)
struct TPrsPerChStatus
{
public:
	u8  byUsed;         //0--未创建，1--创建
	u8	byCount;	    //多少个反馈端
	u8  byChlReserved;  //是否为保留通道
	u8  byConfIndex;		//记录通道服务的会议Idx, zgc, 2007/04/24
public:
    void   SetUsed( void ){ byUsed = 1; }
    void   SetIdle( void ){ byUsed = 0; }
    BOOL   IsUsed( void ){ return byUsed; }
    
    u8     GetFeedNum( void ){ return byCount; }
    void   FeedNumAdd( void ){ byCount++; }
    void   FeedNumDec( void ){ byCount--; }

	void   SetReserved( BOOL bReserved ){ byChlReserved = bReserved; }
	BOOL   IsReserved( void ){ return byChlReserved; }

	//记录通道服务的会议Idx, zgc, 2007/04/24
	void   SetConfIdx( u8 byConfIdx )
	{
		if( byConfIdx > MAXNUM_MCU_CONF )
		{
			OspPrintf( TRUE, FALSE, "The conf idx %d is error!\n", byConfIdx );
			return;
		}
		byConfIndex = byConfIdx; 
	}
	u8	   GetConfIdx( void ){ return byConfIndex; }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//重传结构
struct TPrsStatus
{
public:
	TPrsPerChStatus   m_tPerChStatus[MAXNUM_PRS_CHNNL];		//本地接收RTP/RTCP包的地址
	u8 GetIdleChlNum(void)
	{
		u8 nSum = 0;
		for(u8 byLp = 0; byLp < MAXNUM_PRS_CHNNL; byLp++)
		{
			if( !m_tPerChStatus[byLp].IsReserved() )
			{
				nSum++;
			}
		}
		return nSum;
	}

	//记录通道服务的会议Idx, zgc, 2007/04/24
	void SetChnConfIdx( u8 byChnIdx, u8 byConfIdx )
	{ 
		if( byChnIdx > MAXNUM_PRS_CHNNL || byConfIdx > MAXNUM_MCU_CONF )
		{
			OspPrintf( TRUE, FALSE, "The chn idx %d or conf idx %d is error!\n", byChnIdx, byConfIdx );
			return;
		}
		m_tPerChStatus[byChnIdx].SetConfIdx(byConfIdx); 
	}
	u8   GetChnConfIdx( u8 byChnIdx ){ return m_tPerChStatus[byChnIdx].GetConfIdx(); }
	
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//主备环境下，本端和对端外部模块主备同步情况(len: 2)
struct TMSSynState  
{
    //冲突类型
    enum EntityType
    {
        emNone      = 0,
        emMC        = 1,
        emMp        = 2,
        emMtAdp     = 3,
        emPeriEqp   = 4,
        emDcs       = 5,
        emMpc       = 0xFF
    };
    
protected:
    u8  m_byEntityType;       //未同步的实体类型
    u8  m_byEntityId;         //未同步的实体的ID
    
public:
    TMSSynState(void){ SetNull(); }
    
    void SetNull(void){ memset( this, 0, sizeof(TMSSynState) ); }
    
    void SetEntityType(u8 byEntityType){ m_byEntityType = byEntityType; }
    u8   GetEntityType( void ) const{ return m_byEntityType; }
    void SetEntityId(u8 byEntityId){ m_byEntityId = byEntityId; }
    u8   GetEntityId( void ) const { return m_byEntityId; }
    
    BOOL32 IsSynSucceed(void) const { return m_byEntityType == emNone ? TRUE : FALSE; }    
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//定义MCU状态结构 (len: 6+1 + 128*11 + 1+1*11 + 4 + 5 + 2 + 7 + 4 = 1449 )
struct TMcuStatus: public TMcu
{
	enum eMcuRunningStatusMask
    {
        Mask_Mp				=  0x00000004,
        Mask_Mtadp			=  0x00000008,
		Mask_HDSC			=  0x00000020,
		Mask_MDSC			=  0x00000040,
		Mask_DSC			=  0x00000080,
		Mask_McuRunOk		=  0x80000000
    };
	
	u8		m_byPeriEqpNum;	                        //外设数目
	TEqp	m_atPeriEqp[MAXNUM_MCU_PERIEQP];	    //外设数组
	u8      m_byEqpOnline[MAXNUM_MCU_PERIEQP];      //外设是否在线
	u32     m_dwPeriEqpIpAddr[MAXNUM_MCU_PERIEQP];  //外设Ip地址
    
    u8      m_byPeriDcsNum;                         //DCS数目
    TEqp    m_atPeriDcs[MAXNUM_MCU_DCS];            //DCS数组
    u8      m_byDcsOnline[MAXNUM_MCU_DCS];          //DCS是否在线
    u32     m_dwPeriDcsIpAddr[MAXNUM_MCU_DCS];      //DCS ip地址

    // xsl [8/26/2005] 
    u8      m_byOngoingConfNum;                     //mcu上即时会议个数
    u8      m_byScheduleConfNum;                    //mcu上预约会议个数
    u16     m_wAllJoinedMtNum;                      //mcu上所有与会终端个数
    
    // 顾振华 [5/29/2006]
    u8      m_byRegedGk;                            //是否成功注册GK。如果未配置或者注册失败，则为0
	u16     m_wLicenseNum;							//当前License数
    TMSSynState m_tMSSynState;                      //当前主备情况(主备环境下有效)
    
    // guzh [9/4/2006] 
    u8      m_byRegedMpNum;                         //当前已注册的Mp数量
    u8      m_byRegedMtAdpNum;                      //当前已注册的H323 MtAdp数量

    // guzh  [12/15/2006]
    u8      m_byNPlusState;                         //备份服务器工作状态(mcuconst.h NPLUS_BAKSERVER_IDLE 等)
    u32     m_dwNPlusReplacedMcuIp;                 //如果备份服务器处于接替工作，则接替的服务器IP

	//zgc [12/21/2006]
	u8      m_byMcuIsConfiged;						//MCU是否被配置过的标识
	//zgc [07/26/2007]
	u8		m_byMcuCfgLevel;						// MCU配置信息的可靠级别
	
	//zgc [07/25/2007]
	//[31…24 23…16 15…8 7…0]
	//bit 2: no mp? ([0]no; [1]yes)
	//bit 3: no mtadp? ([0]no; [1]yes)
	//bit 4: no HDCS module?  ([0]no; [1]yes)
	//bit 5: no MDCS module?  ([0]no; [1]yes)
	//bit 7: no DSC module? ([0]no; [1]yes)
	//bit 31: MCU当前是否正常工作? ([0]no; [1]yes)
	u32		m_dwMcuRunningState;					// MCU运行状态
	

protected:
    u32     m_dwPersistantRunningTime;              // MCU运行时间（单位:s, linux上限:497day，vx上限:828day）
public:
	// xliang [11/20/2008] 
	u16		m_wAllHdiAccessMtNum;					// HDI授权接入MT的总数量
	u16		m_wStdCriAccessMtNum;					// 标清接入能力（暂不支持，预留）
public:
	void SetIsExistMp( BOOL32 IsExistMp ) 
	{ 
		m_dwMcuRunningState = ntohl(m_dwMcuRunningState);
		SETBITSTATUS(m_dwMcuRunningState, Mask_Mp, IsExistMp) 
		m_dwMcuRunningState = htonl(m_dwMcuRunningState);
	}
	BOOL32 IsExistMp(void) const 
	{ 
		u32 dwMcuRunningState = ntohl(m_dwMcuRunningState);
		return GETBITSTATUS( dwMcuRunningState, Mask_Mp);
	}
	void SetIsExistMtadp( BOOL32 IsExistMtadp ) 
	{ 
		m_dwMcuRunningState = ntohl(m_dwMcuRunningState);
		SETBITSTATUS(m_dwMcuRunningState, Mask_Mtadp, IsExistMtadp)
		m_dwMcuRunningState = htonl(m_dwMcuRunningState);
	}
	BOOL32 IsExistMtadp(void) const 
	{ 
		u32 dwMcuRunningState = ntohl(m_dwMcuRunningState);
		return GETBITSTATUS( dwMcuRunningState, Mask_Mtadp);
	}
	void SetIsExistDSC( BOOL32 IsExistDSC ) 
	{
		m_dwMcuRunningState = ntohl(m_dwMcuRunningState);
		SETBITSTATUS(m_dwMcuRunningState, Mask_DSC, IsExistDSC)
		m_dwMcuRunningState = htonl(m_dwMcuRunningState);
	}
	BOOL32 IsExistDSC(void) const 
	{ 
		u32 dwMcuRunningState = ntohl(m_dwMcuRunningState);
		return GETBITSTATUS( dwMcuRunningState, Mask_DSC); 
	}
	void SetIsExistMDSC( BOOL32 IsExistDSC ) 
	{
		m_dwMcuRunningState = ntohl(m_dwMcuRunningState);
		SETBITSTATUS(m_dwMcuRunningState, Mask_MDSC, IsExistDSC)
		m_dwMcuRunningState = htonl(m_dwMcuRunningState);
	}
	BOOL32 IsExistMDSC(void) const 
	{ 
		u32 dwMcuRunningState = ntohl(m_dwMcuRunningState);
		return GETBITSTATUS( dwMcuRunningState, Mask_MDSC); 
	}
	void SetIsExistHDSC( BOOL32 IsExistDSC ) 
	{
		m_dwMcuRunningState = ntohl(m_dwMcuRunningState);
		SETBITSTATUS(m_dwMcuRunningState, Mask_HDSC, IsExistDSC)
		m_dwMcuRunningState = htonl(m_dwMcuRunningState);
	}
	BOOL32 IsExistHDSC(void) const 
	{ 
		u32 dwMcuRunningState = ntohl(m_dwMcuRunningState);
		return GETBITSTATUS( dwMcuRunningState, Mask_HDSC); 
	}
	void SetIsMcuRunOk( BOOL32 IsMcuRunOk ) 
	{
		m_dwMcuRunningState = ntohl(m_dwMcuRunningState);
		SETBITSTATUS(m_dwMcuRunningState, Mask_McuRunOk, IsMcuRunOk)
		m_dwMcuRunningState = htonl(m_dwMcuRunningState);
	}
	BOOL32 IsMcuRunOk(void) const 
	{ 
		u32 dwMcuRunningState = ntohl(m_dwMcuRunningState);
		return GETBITSTATUS( dwMcuRunningState, Mask_McuRunOk);
	}
    void SetPersistantRunningTime(u32 dwTime) { m_dwPersistantRunningTime = htonl(dwTime);    }
    u32  GetPersistantRunningTime(void) const { return ntohl(m_dwPersistantRunningTime);    }

    void Print(void) const
    {
        OspPrintf(TRUE, FALSE, "MCU Current Status: \n" );
        OspPrintf(TRUE, FALSE, "\tIs Run OK:%d\n", IsMcuRunOk() );
        OspPrintf(TRUE, FALSE, "\tExist mp: %d, Exist mtadp: %d, Exist dsc module<DSC.%d, MDSC.%d, HDSC.%d>\n",
				IsExistMp(), IsExistMtadp(), IsExistDSC(), IsExistMDSC(), IsExistHDSC());

        OspPrintf(TRUE, FALSE, "\tConfig file state: ");
        switch(m_byMcuCfgLevel) 
        {
        case MCUCFGINFO_LEVEL_NEWEST:
            OspPrintf(TRUE, FALSE, "Success\n");
            break;
        case MCUCFGINFO_LEVEL_PARTNEWEST:
            OspPrintf(TRUE, FALSE, "Partly success\n");
            break;
        case MCUCFGINFO_LEVEL_LAST:
            OspPrintf(TRUE, FALSE, "Read fail\n");
            break;
        case MCUCFGINFO_LEVEL_DEFAULT:
            OspPrintf(TRUE, FALSE, "No cfg file\n");
            break;
        default:
            OspPrintf(TRUE, FALSE, "level error!\n");
            break;
		}
        OspPrintf(TRUE, FALSE, "\tIs Mcu Configed: %d\n", m_byMcuIsConfiged);

        OspPrintf(TRUE, FALSE, "\tIsReggedGk:%d, Mp Num:%d, H323MtAdp Num:%d, PeirEqpNum:%d, DcsNum:%d\n", 
                  m_byRegedGk, m_byRegedMpNum, m_byRegedMtAdpNum, m_byPeriEqpNum, m_byPeriDcsNum);
        
        OspPrintf(TRUE, FALSE, "\tOngoingConf:%d, ScheduleConf:%d, AllJoinedMt:%d\n", 
                  m_byOngoingConfNum, m_byScheduleConfNum, ntohs(m_wAllJoinedMtNum));

        if ( m_byNPlusState != NPLUS_NONE )
        {
            OspPrintf(TRUE, FALSE, "\tNPlusState:%d, NPlus Replaced Mcu:0x%x\n", 
                m_byNPlusState, ntohl(m_dwNPlusReplacedMcuIp));
        }
        
        if (!m_tMSSynState.IsSynSucceed() )
        {
            OspPrintf(TRUE, FALSE, "\tMS conflict entity ID:%d, Type:%d\n", 
                      m_tMSSynState.GetEntityId(), m_tMSSynState.GetEntityType() );
        }
        {
            u32 dwPersistantTime = GetPersistantRunningTime();

            u32 dwCutOffTime = 0;
            u32 dwDay = dwPersistantTime/(3600*24);
            dwCutOffTime += (3600*24) * dwDay;
            u32 dwHour = (dwPersistantTime - dwCutOffTime)/3600;
            dwCutOffTime += 3600 * dwHour;
            u32 dwMinute = (dwPersistantTime - dwCutOffTime)/60;
            dwCutOffTime += 60 * dwMinute;
            u32 dwSecond = dwPersistantTime - dwCutOffTime;
            if ( 0 == dwDay )
            {
                OspPrintf(TRUE, FALSE, "\tPersistant running time: %d.h %d.m %d.s\n",
                                         dwHour, dwMinute, dwSecond );                
            }
            else
            {
                OspPrintf(TRUE, FALSE, "\tPersistant running time: %d.day %d.h %d.m %d.s\n",
                                         dwDay, dwHour, dwMinute, dwSecond );                
            }
        }
		// xliang [11/20/2008] HDI 接入终端数量
		OspPrintf(TRUE, FALSE, "\tHDI access Mt Num: %d\n", m_wAllJoinedMtNum);
	
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TRecState 
{
protected:	
	u8      m_byRecState;  //当前终端录像状态
							//bit3-4: 00:非录像 01:录像 10:录像暂停
							//bit0:   0:实时录像 1:抽帧录像
public:	
	BOOL IsNoRecording( void ) const	{ return( ( m_byRecState & 0x18 ) == 0x00 ? TRUE : FALSE ); }
	void SetNoRecording( void )	{ m_byRecState &= ~0x18; }
	BOOL IsRecording( void ) const	{ return( ( m_byRecState & 0x18 ) == 0x08 ? TRUE : FALSE ); }
	void SetRecording( void )	{ SetNoRecording(); m_byRecState |= 0x08; }
	BOOL IsRecPause( void ) const	{ return( ( m_byRecState & 0x18 ) == 0x10 ? TRUE : FALSE ); }
	void SetRecPause( void )	{ SetNoRecording(); m_byRecState |= 0x10; }
	//是否处于抽帧录像状态
	BOOL IsRecSkipFrame() const { return ( !IsNoRecording() && ( ( m_byRecState & 0x01 ) == 0x01 ) ); }
	void SetRecSkipFrame( BOOL bSkipFrame )      { if( bSkipFrame ) m_byRecState |= 0x01;else m_byRecState &= ~0x01;};
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//终端码率结构 len: 14
struct TMtBitrate : public TMt
{
protected:
    u16     m_wSendBitRate;              //终端发送码率(单位:Kbps,1K=1024)
    u16     m_wRecvBitRate;              //终端接收码率(单位:Kbps,1K=1024)
    u16     m_wH239SendBitRate;          //终端第二路视频发送码率(单位:Kbps,1K=1024)
    u16     m_wH239RecvBitRate;          //终端第二路视频接收码率(单位:Kbps,1K=1024)
    
public:
    TMtBitrate(void) { memset(this, 0, sizeof(TMtBitrate)); }
    void   SetSendBitRate(u16  wSendBitRate){ m_wSendBitRate = htons(wSendBitRate);} 
    u16    GetSendBitRate( void ) const { return ntohs(m_wSendBitRate); }
    void   SetRecvBitRate(u16  wRecvBitRate){ m_wRecvBitRate = htons(wRecvBitRate);} 
    u16    GetRecvBitRate( void ) const { return ntohs(m_wRecvBitRate); }
    void   SetH239SendBitRate(u16  wH239SendBitRate){ m_wH239SendBitRate = htons(wH239SendBitRate);} 
    u16    GetH239SendBitRate( void ) const { return ntohs(m_wH239SendBitRate); }
    void   SetH239RecvBitRate(u16  wH239RecvBitRate){ m_wH239RecvBitRate = htons(wH239RecvBitRate);} 
    u16    GetH239RecvBitRate( void ) const { return ntohs(m_wH239RecvBitRate); }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//终端状态结构(len:64)
struct TMtStatus : public TMtBitrate
{
protected:
    u8      m_byDecoderMute;             //是否解码静音
	u8      m_byCaptureMute;             //是否采集静音
    u8      m_byHasMatrix;               //是否有矩阵
	u8      m_byIsEnableFECC;            //是否能遥控摄像头
	u8      m_bySendAudio;               //是否正在传送音频
	u8      m_bySendVideo;               //是否正在传送视频
	u8      m_byReceiveVideo;            //是否正在接收视频
	u8      m_byReceiveAudio;            //是否正在接收音频
	u8      m_byRcvVideo2;				 //是否在接收第二视频
	u8      m_bySndVideo2;               //是否在发送第二视频
	u8      m_byInMixing;                //是否正在参加混音
	u8      m_byVideoFreeze;             //是否冻结图像
    // guzh [3/7/2007] 本字段从4.0R4开始取消，调整为是否视频源丢失
	//u8      m_bySelPolling;              //是否正在轮询选看
    u8      m_byVideoLose;               //是否视频源丢失
	u8      m_bySelByMcsDrag;            //是否是会控拖拉选看
    u8      m_byDecoderVolume;           //解码音量
	u8      m_byCaptureVolume;           //采集音量
	u8  	m_byCurVideo;	             //当前视频源(1)
	u8  	m_byCurAudio;	             //当前音频源(1)    
	u8      m_byH239VideoFormat;         //终端第二路视频分辨率
	u8      m_byMtBoardType;             //终端的板卡类型(MT_BOARD_WIN, MT_BOARD_8010 等)
    u8      m_byInTvWall;                //终端是否正在电视墙中
    u8      m_byInHdu;                   //终端是否正在HDU中   4.6 新加   jlb
    u8      m_byExVideoSourceNum;        //终端扩展视频源个数
	u8		m_byVideoMediaLoop;			 //终端远端环回状态
	u8		m_byAudioMediaLoop;			 //终端远端环回状态
    u8      m_byIsInMixGrp;              //是否在混音组内
public:
	TMt		m_tVideoMt;		             //当前接收的视频终端
	TMt		m_tAudioMt;		             //当前接收的音频终端
	TRecState m_tRecState;               //终端录像状态
protected:
    TMt     m_tLastSelectVidMt;          //选看的视频终端
	TMt	    m_tLastSelectAudMt;          //选看的音频终端
public:
	TMtStatus( void )
	{
        Clear();
    }

    void Clear()
    {
		memset( this,0,sizeof(TMtStatus));
		SetDecoderMute(FALSE);
		SetCaptureMute(FALSE);
		SetHasMatrix(TRUE);
		SetIsEnableFECC(FALSE);
		SetSendAudio(FALSE);
		SetSendVideo(FALSE);
		SetInMixing(FALSE);
		SetReceiveVideo(FALSE);
        SetReceiveAudio(FALSE);
		SetVideoFreeze(FALSE);
		//SetSelPolling(FALSE);
        SetVideoLose(FALSE);
		SetSelByMcsDrag(FALSE);
		SetDecoderVolume(16);
		SetCaptureVolume(16);
		SetCurVideo(1);
		SetCurAudio(1);		
		SetRcvVideo2(FALSE);
		SetSndVideo2(FALSE);
        SetInTvWall(FALSE);
        SetIsInMixGrp(FALSE);
        SetMtBoardType(MT_BOARD_UNKNOW);
	}

    void   SetDecoderMute(BOOL bDecoderMute){ m_byDecoderMute = GETBBYTE(bDecoderMute);} 
    BOOL   IsDecoderMute( void ) const { return ISTRUE(m_byDecoderMute); }
    void   SetCaptureMute(BOOL bCaptureMute){ m_byCaptureMute = GETBBYTE(bCaptureMute);} 
    BOOL   IsCaptureMute( void ) const { return ISTRUE(m_byCaptureMute); }
    void   SetHasMatrix(BOOL bHasMatrix){ m_byHasMatrix = GETBBYTE(bHasMatrix);} 
    BOOL   IsHasMatrix( void ) const { return ISTRUE(m_byHasMatrix); }
    void   SetIsEnableFECC(BOOL bCamRCEnable){ m_byIsEnableFECC = GETBBYTE(bCamRCEnable);} 
    BOOL   IsEnableFECC( void ) const { return ISTRUE(m_byIsEnableFECC); }
    void   SetSendAudio(BOOL bSendAudio){ m_bySendAudio = GETBBYTE(bSendAudio);} 
    BOOL   IsSendAudio( void ) const { return ISTRUE(m_bySendAudio); }
    void   SetSendVideo(BOOL bSendVideo){ m_bySendVideo = GETBBYTE(bSendVideo);} 
    BOOL   IsSendVideo( void ) const { return ISTRUE(m_bySendVideo); }
    void   SetInMixing(BOOL bInMixing){ m_byInMixing = GETBBYTE(bInMixing);} 
    BOOL   IsInMixing( void ) const { return ISTRUE(m_byInMixing); }
    void   SetReceiveAudio(BOOL bRcv) { m_byReceiveAudio = GETBBYTE(bRcv); }
    BOOL   IsReceiveAudio() const { return ISTRUE(m_byReceiveAudio); }
	void   SetReceiveVideo(BOOL bReceiveVideo){ m_byReceiveVideo = GETBBYTE(bReceiveVideo);} 
    BOOL   IsReceiveVideo( void ) const { return ISTRUE(m_byReceiveVideo); }
    void   SetVideoFreeze(BOOL bVideoFreeze){ m_byVideoFreeze = GETBBYTE(bVideoFreeze);} 
    BOOL   IsVideoFreeze( void ) const { return ISTRUE(m_byVideoFreeze); }
    /*
    void   SetSelPolling(BOOL bSelPolling){ m_bySelPolling = GETBBYTE(bSelPolling);} 
    BOOL   IsSelPolling( void ) const { return ISTRUE(m_bySelPolling); }
    */
    void   SetVideoLose(BOOL bIsLose){ m_byVideoLose = GETBBYTE(bIsLose);} 
    BOOL   IsVideoLose( void ) const { return ISTRUE(m_byVideoLose); }

    void   SetIsInMixGrp(BOOL bDiscuss) { m_byIsInMixGrp = GETBBYTE(bDiscuss); }
    BOOL   IsInMixGrp(void) const { return ISTRUE(m_byIsInMixGrp); }    
    void   SetSelByMcsDrag( u8 bySelMediaMode ){ m_bySelByMcsDrag = bySelMediaMode;} 
    u8     GetSelByMcsDragMode( void ) const { return m_bySelByMcsDrag; }
    void   SetDecoderVolume(u8   byDecoderVolume){ m_byDecoderVolume = byDecoderVolume;} 
    u8     GetDecoderVolume( void ) const { return m_byDecoderVolume; }
    void   SetCaptureVolume(u8   byCaptureVolume){ m_byCaptureVolume = byCaptureVolume;} 
    u8     GetCaptureVolume( void ) const { return m_byCaptureVolume; }
    void   SetCurVideo(u8   byCurVideo){ m_byCurVideo = byCurVideo;} 
    u8     GetCurVideo( void ) const { return m_byCurVideo; }
    void   SetCurAudio(u8   byCurAudio){ m_byCurAudio = byCurAudio;} 
    u8     GetCurAudio( void ) const { return m_byCurAudio; }    
    void   SetH239VideoFormat(u8 byH239VideoFormat){ m_byH239VideoFormat = byH239VideoFormat;} 
    u8     GetH239VideoFormat( void ) const { return m_byH239VideoFormat; }
    void   SetMtBoardType(u8 byType) { m_byMtBoardType = byType; }
	u8     GetMtBoardType() const {return m_byMtBoardType; }
	void   SetVideoMt(TMt tVideoMt){ m_tVideoMt = tVideoMt;} 
    TMt    GetVideoMt( void ) const { return m_tVideoMt; }
    void   SetAudioMt(TMt tAudioMt){ m_tAudioMt = tAudioMt;} 
    TMt    GetAudioMt( void ) const { return m_tAudioMt; }

    void	SetMediaLoop(u8 byMode, BOOL32 bOn) 
    { 
        if (MODE_VIDEO == byMode)
        {
            m_byVideoMediaLoop = GETBBYTE(bOn);
        }
        else if (MODE_AUDIO == byMode)
        {
            m_byAudioMediaLoop = GETBBYTE(bOn);
        }
    }
    BOOL    IsMediaLoop(u8 byMode)
    {
        if (MODE_VIDEO == byMode)
        {
            return ISTRUE(m_byVideoMediaLoop); 
        }
        else if (MODE_AUDIO == byMode)
        {
            return ISTRUE(m_byAudioMediaLoop); 
        }

        return FALSE;
    }
    // guzh [2/28/2007] 本变量为选看判别和恢复使用，请谨慎使用
	void   SetSelectMt(TMt tSeleteMt, u8 byMode ) 
    {
        if ( byMode == MODE_AUDIO || byMode == MODE_BOTH )
        {
            m_tLastSelectAudMt = tSeleteMt;
        }
        if ( byMode == MODE_VIDEO || byMode == MODE_BOTH )
        {
            m_tLastSelectVidMt = tSeleteMt;
        }        
    }
	TMt    GetSelectMt( u8 byMode ) const 
    { 
        if ( byMode == MODE_AUDIO )
        {
            return m_tLastSelectAudMt;
        }
        else if ( byMode == MODE_VIDEO )
        {
            return m_tLastSelectVidMt;
        }    
        else 
        {
            TMt tNullMt;
            tNullMt.SetNull();
            return tNullMt;
        }
    }

	void   SetRcvVideo2(BOOL bRcv) { m_byRcvVideo2 = GETBBYTE(bRcv);}
    BOOL   IsRcvVideo2() const {return ISTRUE(m_byRcvVideo2);}
    void   SetSndVideo2(BOOL bSend) { m_bySndVideo2 = GETBBYTE(bSend); }
	BOOL   IsSndVideo2() const { return ISTRUE(m_bySndVideo2); }
    void   SetExVideoSrcNum(u8 byNum) { m_byExVideoSourceNum = byNum; }
    u8     GetExVideoSrcNum(void) const { return m_byExVideoSourceNum; }

    void   SetInTvWall(BOOL bInTvWall){ m_byInTvWall = GETBBYTE(bInTvWall);} 
    BOOL   IsInTvWall( void ) const { return ISTRUE(m_byInTvWall); }
	//4.6 新加 jlb
	void   SetInHdu(BOOL bInHdu){ m_byInHdu = GETBBYTE(bInHdu);} 
    BOOL   IsInHdu( void ) const { return ISTRUE(m_byInHdu); }

	void  SetTMt( TMt tMt ){ memcpy( this, &tMt, sizeof(tMt) ); }
	const TMt & GetMt( void ) const; //获取终端结构
	void  AddSelByMcsMode( u8 byMode )
	{
		if( ( m_bySelByMcsDrag == MODE_VIDEO && byMode == MODE_AUDIO ) || 
			( m_bySelByMcsDrag == MODE_AUDIO && byMode == MODE_VIDEO ) || 
			m_bySelByMcsDrag == MODE_BOTH )
		{
			m_bySelByMcsDrag = MODE_BOTH;
		}
		else
		{
			m_bySelByMcsDrag = byMode;
		}
	}
	
	void RemoveSelByMcsMode( u8 byMode )
	{
		if( byMode == MODE_BOTH )
		{
			m_bySelByMcsDrag = MODE_NONE;
		}
		else if( byMode == MODE_AUDIO )
		{
			if( m_bySelByMcsDrag == MODE_BOTH )
			{
				m_bySelByMcsDrag = MODE_VIDEO;
			}
			else if( m_bySelByMcsDrag == MODE_AUDIO )
			{
				m_bySelByMcsDrag = MODE_NONE;
			}
		}
		else if( byMode == MODE_VIDEO )
		{
			if( m_bySelByMcsDrag == MODE_BOTH )
			{
				m_bySelByMcsDrag = MODE_AUDIO;
			}
			else if( m_bySelByMcsDrag == MODE_VIDEO )
			{
				m_bySelByMcsDrag = MODE_NONE;
			}
		}
	}

	void Print( void ) const
	{
		OspPrintf( TRUE, FALSE, "Mcu%dMt%d status:\n", GetMcuId(), GetMtId() ); 
        OspPrintf( TRUE, FALSE, "	m_byMtBoardType = %d\n", m_byMtBoardType ); 
		OspPrintf( TRUE, FALSE, "	m_byDecoderMute = %d\n", m_byDecoderMute ); 
		OspPrintf( TRUE, FALSE, "	m_byCaptureMute = %d\n", m_byCaptureMute );
		OspPrintf( TRUE, FALSE, "	m_byHasMatrix = %d\n", m_byHasMatrix );
        OspPrintf( TRUE, FALSE, "	m_byExVideoSourceNum = %d\n", m_byExVideoSourceNum );
		OspPrintf( TRUE, FALSE, "	m_byIsEnableFECC = %d\n", m_byIsEnableFECC );
		OspPrintf( TRUE, FALSE, "	m_bySendAudio = %d\n", m_bySendAudio );
		OspPrintf( TRUE, FALSE, "	m_bySendVideo = %d\n", m_bySendVideo );
        OspPrintf( TRUE, FALSE, "   m_byRecvAudio = %d\n", m_byReceiveAudio );
        OspPrintf( TRUE, FALSE, "   m_byRecvVideo = %d\n", m_byReceiveVideo );
		OspPrintf( TRUE, FALSE, "	m_byInMixing = %d\n", m_byInMixing );
        OspPrintf( TRUE, FALSE, "	m_byIsInMixGrp = %d\n", m_byIsInMixGrp );
		OspPrintf( TRUE, FALSE, "	m_byVideoLose = %d\n", m_byVideoLose );
		OspPrintf( TRUE, FALSE, "	m_bySelByMcsDrag = %d\n", m_bySelByMcsDrag );
		OspPrintf( TRUE, FALSE, "	m_byDecoderVolume = %d\n", m_byDecoderVolume );
		OspPrintf( TRUE, FALSE, "	m_byCurVideo = %d\n", m_byCurVideo );
        OspPrintf( TRUE, FALSE, "	m_byCurAudio = %d\n", m_byCurAudio );
		OspPrintf( TRUE, FALSE, "	m_wSendBitRate = %d\n", ntohs(m_wSendBitRate) );
		OspPrintf( TRUE, FALSE, "	m_wRecvBitRate = %d\n", ntohs(m_wRecvBitRate) );
		OspPrintf( TRUE, FALSE, "	m_wH239SendBitRate = %d\n", ntohs(m_wH239SendBitRate) );
		OspPrintf( TRUE, FALSE, "	m_wH239RecvBitRate = %d\n", ntohs(m_wH239RecvBitRate) );
		OspPrintf( TRUE, FALSE, "	m_byH239VideoFormat = %d\n", m_byH239VideoFormat );
        OspPrintf( TRUE, FALSE, "	m_byVideoMediaLoop = %d\n", m_byVideoMediaLoop );
        OspPrintf( TRUE, FALSE, "	m_byAudioMediaLoop = %d\n", m_byAudioMediaLoop );
		if( m_tVideoMt.GetType() == TYPE_MT )
		{
			OspPrintf( TRUE, FALSE, "	SrcVideo: mcu%dmt%d\n", m_tVideoMt.GetMcuId(), m_tVideoMt.GetMtId() );
		}
		else
		{
            if (m_tVideoMt.GetEqpId() != 0)
            {
                OspPrintf( TRUE, FALSE, "	SrcVideo: eqp%d\n", m_tVideoMt.GetEqpId() );
            }
            else
            {
                OspPrintf( TRUE, FALSE, "	SrcVideo: NULL\n" );
            }
			
		}

		if( m_tAudioMt.GetType() == TYPE_MT )
		{
			OspPrintf( TRUE, FALSE, "	SrcAudio: mcu%dmt%d\n", m_tAudioMt.GetMcuId(), m_tAudioMt.GetMtId() );
		}
		else
		{
            if (m_tAudioMt.GetEqpId() != 0)
            {
                OspPrintf( TRUE, FALSE, "	SrcAudio: eqp%d\n", m_tAudioMt.GetEqpId() );
            }
            else
            {
                OspPrintf( TRUE, FALSE, "	SrcAudio: NULL\n" );
            }			
		}

        if (!m_tLastSelectVidMt.IsNull())
        {   
            OspPrintf( TRUE, FALSE, "	Select Video MT: mcu%dmt%d\n", 
                m_tLastSelectVidMt.GetMcuId(), m_tLastSelectVidMt.GetMtId() );
        }
        else
        {
            OspPrintf( TRUE, FALSE, "	Select Video MT: NULL\n" );
        }
        if (!m_tLastSelectAudMt.IsNull())
        {   
            OspPrintf( TRUE, FALSE, "	Select Audio MT: mcu%dmt%d\n", 
                   m_tLastSelectAudMt.GetMcuId(), m_tLastSelectAudMt.GetMtId() );
        }
        else
        {
            OspPrintf( TRUE, FALSE, "	Select Audio MT: NULL\n" );
        }      
	}

}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TTWMember : public TMt
{
    u8  byMemberType;     //成员类型
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//HDU终端成员
struct THduMember:public TMt
{
    u8 byMemberType;
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;


//定义数字电视墙状态结构
struct TTvWallStatus
{
    u8        byOutputMode;  //TW_OUTPUTMODE_AUDIO : 只输出音频
                             //TW_OUTPUTMODE_VIDEO : 只输出视频
                             //TW_OUTPUTMODE_BOTH  : 同时输出音视频
    u8        byChnnlNum;    //信道数
    TTWMember atVideoMt[MAXNUM_PERIEQP_CHNNL]; //每个信道对应终端，MCU号为0表示无
}
#ifndef WIN32
__attribute__((packed))
#endif
;

/*----------------------------------------------------------------------
结构名：THduChnStatus
用途  ：
----------------------------------------------------------------------*/
struct THduChnStatus
{
    enum EHduChnStatus
    {
        eIDLE   = 0, //空闲
        eREADY  = 1, //准备
        eNORMAL = 2  //运行
    };

public:

    void   SetStatus( u8 byStatus ) { m_byStatus = byStatus; };
    u8     GetStatus( void ) { return m_byStatus; }
    
    BOOL32 IsNull( void ) const { return m_tHdu.IsNull(); }
    void   SetNull( void ) { m_tHdu.SetNull(); }
        
    void   SetChnIdx( u8 byChnIdx ) { m_byChnIdx = byChnIdx; }
    u8     GetChnIdx( void ) const { return m_byChnIdx; }
    
    void   SetEqp( TEqp tHdu ) { m_tHdu = tHdu; }
    TEqp   GetEqp( void ) const { return m_tHdu; }
    u8     GetEqpId( void ) const { return m_tHdu.GetEqpId(); }	

    void   SetSchemeIdx( u8 bySchemeIdx ) { m_bySchemeIdx = bySchemeIdx; };
    u8     GetSchemeIdx( void ) { return m_bySchemeIdx; }

	u8     GetVolume( void ){ return m_byVolume; }
	void   SetVolume( u8 byVolume ){ m_byVolume = byVolume; }

	BOOL32   GetIsMute( void ){ return m_byMute; }
	void   SetIsMute( BOOL32 byIsMute ){ m_byMute = GETBBYTE(byIsMute); }

private:
	u8 m_byStatus;	  // HduChnStatus
	u8 m_byChnIdx;
    u8 m_bySchemeIdx; // 正在被使用预案的索引号 
    u8 m_byVolume;
	u8 m_byMute;      // 是否静音
    TEqp m_tHdu;

} 
#ifndef WIN32
__attribute__ ((packed)) 
#endif
;


//HDU状态结构
struct THduStatus
{
    u8        byOutputMode;  //HDU_OUTPUTMODE_AUDIO : 只输出音频
	                         //HDU_OUTPUTMODE_VIDEO : 只输出视频
	                         //HDU_OUTPUTMODE_BOTH  : 同时输出音视频
    u8        byChnnlNum;    //信道数

    THduMember atVideoMt[MAXNUM_HDU_CHANNEL]; //每个信道对应终端，MCU号为0表示无 //???

	THduChnStatus atHduChnStatus[MAXNUM_HDU_CHANNEL];
}
#ifndef WIN32
__attribute__((packed))
#endif
;



//双载荷
struct TDoublePayload
{
protected:
	u8  m_byRealPayload;    //原媒体格式
	u8  m_byActivePayload;  //活动媒体格式
public:
    TDoublePayload()
	{
		Reset();
	}
	void Reset()
	{
		m_byRealPayload = MEDIA_TYPE_NULL;
		m_byActivePayload = MEDIA_TYPE_NULL;
	}
	void SetRealPayLoad(u8 byRealPayload)
	{
		m_byRealPayload = byRealPayload;
	}
	u8 GetRealPayLoad()
	{
		return m_byRealPayload;
	}

	void SetActivePayload(u8 byActivePayload)
	{
		m_byActivePayload = byActivePayload;
	}

	u8 GetActivePayload()
	{
		return m_byActivePayload;
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TTvWallStartPlay
{
protected:
    TMt m_tMt;
    TTransportAddr m_tRtcpBackAddr; //RTCP回馈地址
    u8  m_byNeedPrs;
    TMediaEncrypt m_tVideoEncrypt;

public:
    TTvWallStartPlay(void)
    {
        Reset();
    }

    void Reset(void)
    {
		m_byNeedPrs = 0;
		m_tRtcpBackAddr.SetNull();
        m_tMt.SetNull();
        m_tVideoEncrypt.Reset();
    }

    void SetMt(const TMt &tMt)
    {
        m_tMt  = tMt;
    }

    TMt& GetMt(void)
    {
        return m_tMt;
    }

    TMediaEncrypt& GetVideoEncrypt(void)
    {
        return m_tVideoEncrypt;
    }

    void SetVideoEncrypt(TMediaEncrypt& tMediaEncrypt)
    {
        memcpy(&m_tVideoEncrypt, &tMediaEncrypt, sizeof(tMediaEncrypt));
    }

    void SetIsNeedByPrs(BOOL bNeedPrs)
    {
        m_byNeedPrs = bNeedPrs==TRUE?1:0;
    }

    BOOL IsNeedByPrs(void)
    {
        return (m_byNeedPrs != 0);
    }

    void GetRtcpBackAddr(u32 & dwRtcpBackIp, u16 & wRtcpBackPort)
    {
        dwRtcpBackIp = m_tRtcpBackAddr.GetIpAddr();
        wRtcpBackPort = m_tRtcpBackAddr.GetPort();
        return;
    }

    void SetRtcpBackAddr(u32 dwRtcpBackIp, u16 wRtcpBackPort)
    {
        m_tRtcpBackAddr.SetIpAddr(dwRtcpBackIp);
        m_tRtcpBackAddr.SetPort(wRtcpBackPort);
    }
}
#ifndef WIN32
__attribute__ ((packed))
#endif
;

//4.6新加 版本 jlb
struct THduStartPlay: public TTvWallStartPlay
{
protected:
	u8 m_byMode;   // MODE_AUDIO, MODE_VIDEO, MODE_BOTH
	u8 m_byReserved;
public:
	THduStartPlay()
	{
		m_byMode = 0;
		m_byReserved = 0;
	}

	void SetMode( u8 byMode ){ m_byMode = byMode; }
    u8   GetMode( void ){ return m_byMode; }

}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TMixerStart
{
protected:
    u8 m_byMixGroupId; //混音组Id
    u8 m_byMixDepth;   //混音深度
    u8 m_byAudioMode;  //语音格式
    u8 m_byAudioMode2; //第二语音格式(若不为空则为双混音格式)
    u8 m_byIsAllMix;   //全体混音
    TMediaEncrypt m_tAudioEncrypt;	//加密参数
    u8 m_byNeedPrs;
public:
    TMixerStart(void)
    {
        Reset();
    }
    void Reset(void)
    {
        m_byMixGroupId = MIXER_INVALID_GRPID;
        m_byMixDepth = 0;
        m_byAudioMode = MEDIA_TYPE_NULL;
        m_byAudioMode2 = MEDIA_TYPE_NULL;
        m_byIsAllMix = 0;
        m_byNeedPrs = 0;
        m_tAudioEncrypt.Reset();
    }

    void SetMixGroupId(u8 byGroupID)
    {
        m_byMixGroupId = byGroupID;
    }
    u8 GetMixGroupId()
    {
        return m_byMixGroupId;
    }
    void SetMixDepth(u8 byDepth)
    {
        m_byMixDepth = byDepth;
    }
    u8 GetMixDepth()
    {
        return m_byMixDepth;
    }
    void SetAudioMode(u8 byAudioMode)
    {
        m_byAudioMode = byAudioMode;
    }
    u8  GetAudioMode()
    {
        return m_byAudioMode;
    }
    void SetSecAudioMode(u8 byAudioMode)
    {
        m_byAudioMode2 = byAudioMode;
    }
    u8  GetSecAudioMode()
    {
        return m_byAudioMode2;
    }

    void SetIsAllMix(BOOL32 bIsAllMix)
    {
        m_byIsAllMix = (bIsAllMix ? 1:0 );
    }
    BOOL32 IsAllMix()
    {
        return (m_byIsAllMix != 0);
    }
    TMediaEncrypt& GetAudioEncrypt()
    {
        return m_tAudioEncrypt;
    }

    void SetAudioEncrypt(TMediaEncrypt& tMediaEncrypt)
    {
        memcpy(&m_tAudioEncrypt, &tMediaEncrypt, sizeof(tMediaEncrypt));
    }

    void SetIsNeedByPrs(BOOL32 bNeedPrs)
    {
        m_byNeedPrs = (TRUE == bNeedPrs) ? 1 : 0;
    }

    BOOL32 IsNeedByPrs(void)
    {
        return (m_byNeedPrs != 0);
    }
}
#ifndef WIN32
__attribute__((packed))
#endif
;

//混音成员结构
struct TMixMember
{
    TMt m_tMember;
    u8  m_byVolume;                 //成员音量
    u8  m_byAudioType;              //媒体类型
    TTransportAddr m_tAddr;         //成员的传输地址
    TTransportAddr m_tRtcpBackAddr; //RTCP回馈地址
}
#ifndef WIN32
__attribute__((packed)) 
#endif
;

//混音组状态
struct TMixerGrpStatus
{
	enum EState 
	{ 
		IDLE   = 0,		//该混音组未使用 
		READY  = 1,		//该组创建,但未开始混音
		MIXING = 2,		//正在混音
        WAIT_BEGIN = 200,
        WAIT_START_SPECMIX = 201,   //等待回应状态
        WAIT_START_AUTOMIX = 202,
        WAIT_START_VAC = 203,
        WAIT_STOP = 204,
	};

	u8       m_byGrpId;		  //混音组ID(0-4)
	u8       m_byGrpState;	  //组状态
	u8       m_byGrpMixDepth; //混音深度
    u8       m_byConfId;      //会议ID
protected:
    u8       m_abyMixMmb[MAXNUM_CONF_MT>>3];//参与竞争混音成员列表
    u8       m_abyActiveMmb[MAXNUM_MIXER_DEPTH];//被选中的混音成员列表,0表示无效成员
public:
	//所有状态复位
	void Reset()
	{
		m_byGrpId       = 0xff;
		m_byGrpState    = IDLE;
		m_byGrpMixDepth = 0;
		memset( m_abyMixMmb ,0 ,sizeof(m_abyMixMmb) );
		memset( m_abyActiveMmb ,0 ,sizeof(m_abyActiveMmb) );
	}
    //添加参与竞争的混音成员
	// 若该成员ID合法返回TRUE,否则返回FALSE
    BOOL  AddMmb( u8   byMmbId)
	{
		u8   byByteIdx ,byBitIdx,byMask;
		if( byMmbId > MAXNUM_CONF_MT ||byMmbId==0)
			return FALSE;
		byMmbId--;
		byByteIdx = byMmbId>>3;
		byBitIdx  = byMmbId%8;
		byMask    = 1<<byBitIdx;

		m_abyMixMmb[byByteIdx] |= byMask;

		return TRUE;
	}

	//删除参与竞争的混音成员
	// 若该成员ID合法返回TRUE,否则返回FALSE
	BOOL  RemoveMmb( u8   byMmbId)
	{

		u8   byByteIdx ,byBitIdx,byMask;
		if( byMmbId > MAXNUM_CONF_MT ||byMmbId==0)
			return FALSE;
		byMmbId--;
		byByteIdx = byMmbId>>3;
		byBitIdx  = byMmbId%8;
		byMask    = 1<<byBitIdx;

		m_abyMixMmb[byByteIdx] &= ~byMask;

		return TRUE;
	}

	//检测某成员是否存在于参与竞争的表中，
	//如果存在返回TRUE ,否则返回FALSE
	BOOL  IsContain( u8   byMmbId )
	{
		
		u8   byByteIdx ,byBitIdx,byMask;
		if( byMmbId > MAXNUM_CONF_MT ||byMmbId==0)
			return FALSE;
		byMmbId--;
		byByteIdx = byMmbId>>3;
		byBitIdx  = byMmbId%8;
		byMask    = 1<<byBitIdx;
		
		return (m_abyMixMmb[byByteIdx]&byMask)==0 ? FALSE:TRUE;
	}

	//获得正在参与竞争参与混音的成员数量
	u8    GetMmbNum()
	{
		u8   byNum=0;
		for( u8   byByteIdx=0 ;byByteIdx<(MAXNUM_CONF_MT>>3) ;byByteIdx++ )
		{
			for( u8   byBitIdx =0 ;byBitIdx<8 ;byBitIdx++ )
			{
				byNum += (m_abyMixMmb[byByteIdx]>>byBitIdx)&0x1;
			}
		}
		return byNum;
	}

	//获得正在参与竞争的混音成员ID
	//输出 - abyMmb[] 用于存储参加混音的成员ID
	//输入 - bySize abyMmb[] 的大小
	//返回 参加混音的成员数
	u8    GetMixMmb( u8   abyMmb[] ,u8   bySize)
	{
		u8   byNum=0;
		for( u8   byByteIdx=0 ;byByteIdx<(MAXNUM_CONF_MT>>3) ;byByteIdx++ )
		{
			for( u8   byBitIdx =0 ;byBitIdx<8 ;byBitIdx++ )
			{
				if((m_abyMixMmb[byByteIdx]>>byBitIdx)&0x1 )
				{
					if( bySize <= byNum )
						return bySize;
					abyMmb[byNum]= byByteIdx*8+byBitIdx+1;
					byNum++;
				}
			}
		}
		return byNum;
	}
	
	//判断指定成员是否被选中混音
	BOOL IsActive( u8   byMmbId )
	{
		if( byMmbId ==0 )return FALSE;
		for( u8   byIdx =0 ;byIdx< MAXNUM_MIXER_DEPTH ;byIdx++ )
		{
			if( m_abyActiveMmb[byIdx]== byMmbId )
				return TRUE;
		}
		return FALSE;
	}
	
	//获得被选中混音成员个数
	u8   GetActiveMmbNum()
	{
		u8   byCount=0;
		for( u8   byIdx =0 ;byIdx< MAXNUM_MIXER_DEPTH ;byIdx++ )
			if( m_abyActiveMmb[byIdx] )byCount++;
		return byCount;
	}
	
	//获得被选中混音成员
	//输出: abyMmb[] - 存储被选中混音成员ID
	//输入: bySize   - abyMmb 大小
	//返回: abyMmb中有效成员个数
	u8   GetActiveMmb( u8   abyMmb[] ,u8   bySize )
	{
		u8   byCnt=0;
    	for( u8   byIdx =0 ;byIdx< min(bySize ,MAXNUM_MIXER_DEPTH) ;byIdx++ )
			if( m_abyActiveMmb[byIdx] )
			{
				abyMmb[byIdx] = m_abyActiveMmb[byIdx];
				byCnt++;
			}
			return byCnt;		
	}

	BOOL UpdateActiveMmb( u8   abyMmb[MAXNUM_MIXER_DEPTH] )
	{
		memcpy( m_abyActiveMmb ,abyMmb ,MAXNUM_MIXER_DEPTH);
		return TRUE;
	}
	
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;


//混音器状态
struct TMixerStatus
{
	u8 m_byGrpNum; //混音组数量
	TMixerGrpStatus	m_atGrpStatus[MAXNUM_MIXER_GROUP];
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//画面合成器状态
struct TVmpStatus
{
	enum EnumUseState 
	{ 
		IDLE,		//未被占用
	    RESERVE,    //预留
        WAIT_START, //等待开始回应
		START,      //正进行画面合成
		WAIT_STOP,  //等待结束回应
	};
public:	
	u8        m_byUseState;	    //使用状态 0-未使用 1-使用
	u8        m_byChlNum;       //通道数
#ifdef _ZGCDEBUG_
	u8		  m_byEncodeNum;	//编码路数, zgc, 2007-06-20
#endif
    TVMPParam m_tVMPParam;      //合成参数
	u8		  m_bySubType;		//vmp子类型，详见mcuconst.h中的定义// xliang [12/29/2008] 
	u8		  m_byBoardVer;		//表征MPU A板/B板
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// 画面合成成员结构(Mcu -- Vmp)
struct TVMPMemberEx : public TVMPMember
{
public:
	void  SetMember( TVMPMember& tMember )
	{
		memcpy(this, &tMember, sizeof(tMember));
	}

	BOOL  SetMbAlias( const s8 *pAlias ) 
    { 
        BOOL bRet = FALSE;
        if( NULL != pAlias )
        {
            memcpy(achMbAlias, pAlias, sizeof(achMbAlias));
            achMbAlias[VALIDLEN_ALIAS] = '\0';
            bRet = TRUE;
        }
        return bRet; 
    }
	const s8* GetMbAlias(void) { return achMbAlias; }

protected:
	s8   achMbAlias[VALIDLEN_ALIAS+1];
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//画面合成参数(MCU与VMP通讯用)
class CKDVVMPParam
{
public:
	u8              m_byVMPStyle;      //画面合成风格,参见mcuconst.h中画面合成风格定义
	u8    	        m_byEncType;       //图像编码类型
	u16             m_wBitRate;        //编码比特率(Kbps)
	u16   	        m_wVideoWidth;     //图像宽度(default:720)
	u16   		    m_wVideoHeight;    //图像高度(default:576)
  	u8      	    m_byMemberNum;     //参加视频复合的成员数量
	TVMPMemberEx    m_atMtMember[MAXNUM_VMP_MEMBER];    //视频复合成员，按照复合方式的逻辑编号顺序
	TMediaEncrypt   m_tVideoEncrypt[MAXNUM_VMP_MEMBER];     //视频加密参数
	TDoublePayload  m_tDoublePayload[MAXNUM_VMP_MEMBER];

public:
    void Print(void)
    {
        OspPrintf(TRUE, FALSE, "VmpStyle:%d, EncType:%d, Bitrate:0x%x, VidWidth:%d, VidHeight:%d, MemNum:%d\n",
                  m_byVMPStyle, m_byEncType, ntohs(m_wBitRate), m_wVideoWidth, m_wVideoHeight, m_byMemberNum);
        for(u8 byIndex = 0; byIndex < MAXNUM_VMP_MEMBER; byIndex++)
        {
            if(0 != m_atMtMember[byIndex].GetMcuId() && 0 != m_atMtMember[byIndex].GetMtId())
            {
                OspPrintf(TRUE, FALSE, "McuId:%d, MtId:%d, MemType:%d, MemStatus:%d, RealPayLoad:%d, ActPayLoad:%d, EncrptMode:%d\n", 
                        m_atMtMember[byIndex].GetMcuId(), m_atMtMember[byIndex].GetMtId(), 
                        m_atMtMember[byIndex].GetMemberType(), m_atMtMember[byIndex].GetMemStatus(),
                        m_tDoublePayload[byIndex].GetRealPayLoad(), m_tDoublePayload[byIndex].GetActivePayload(),
                        m_tVideoEncrypt[byIndex].GetEncryptMode());
            }            
        }        
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//画面合成参数(MCU与VMP通讯用)
class CKDVNewVMPParam
{
public:
	u8              m_byVMPStyle;      //画面合成风格,参见mcuconst.h中画面合成风格定义
	u8    	        m_byEncType;       //图像编码类型
	u8      	    m_byMemberNum;     //参加视频复合的成员数量
	TVMPMemberEx    m_atMtMember[MAXNUM_MPUSVMP_MEMBER];    //视频复合成员，按照复合方式的逻辑编号顺序
	TMediaEncrypt   m_tVideoEncrypt[MAXNUM_MPUSVMP_MEMBER];     //视频加密参数
	TDoublePayload  m_tDoublePayload[MAXNUM_MPUSVMP_MEMBER];

private:
	u16             m_wBitRate;        //编码比特率(Kbps)
	u16   	        m_wVideoWidth;     //图像宽度(default:720)
	u16   		    m_wVideoHeight;    //图像高度(default:576)

public:
	void SetBitRate( u16 wBitRate ) { m_wBitRate = htons( wBitRate); }
	u16  GetBitRate() { return ntohs(m_wBitRate); }
	void SetVideoWidth( u16 wVidWidth ) { m_wVideoWidth = htons(wVidWidth); }
	u16  GetVideoWidth() { return ntohs(m_wVideoWidth); }
	void SetVideoHeight( u16 wVidHeight ) { m_wVideoHeight = htons(wVidHeight); }
	u16	 GetVideoHeight() { return ntohs(m_wVideoHeight); }

    void Print(void)
    {
        OspPrintf(TRUE, FALSE, "\tVmpStyle:\t%d\n\tEncType:\t%d\n\tBitrate:\t%d\n\tVidWidth:\t%d\n\tVidHeight:\t%d\n\tMemNum:\t\t%d\n",
			m_byVMPStyle, m_byEncType, GetBitRate(), GetVideoWidth(), GetVideoHeight(), m_byMemberNum);

        OspPrintf(TRUE, FALSE, "\nMem as follows:\n");

        for(u8 byIndex = 0; byIndex < MAXNUM_MPUSVMP_MEMBER; byIndex++)
        {
            if(0 != m_atMtMember[byIndex].GetMcuId() && 0 != m_atMtMember[byIndex].GetMtId())
            {
                OspPrintf(TRUE, FALSE, "\tMemIdx[%d]:\n", byIndex);
                OspPrintf(TRUE, FALSE, "\t\tMcuId:\t\t%d\n\t\tMtId:\t\t%d\n\t\tMemType:\t%d\n\t\tMemStatus:\t%d\n\t\tRealPayLoad:\t%d\n\t\tActPayLoad:\t%d\n\t\tEncrptMode:\t%d\n", 
					m_atMtMember[byIndex].GetMcuId(), m_atMtMember[byIndex].GetMtId(), 
					m_atMtMember[byIndex].GetMemberType(), m_atMtMember[byIndex].GetMemStatus(),
					m_tDoublePayload[byIndex].GetRealPayLoad(), m_tDoublePayload[byIndex].GetActivePayload(),
					m_tVideoEncrypt[byIndex].GetEncryptMode());
            }            
        }        
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TRecRtcpBack
{
protected:
    u32  m_tVideoIp;      //视频RTCP回馈地址
    u16  m_tVideoPort;    //视频RTCP回馈端口
    u32  m_tAudioIp;      //音频RTCP回馈地址
    u16  m_tAudioPort;    //音频RTCP回馈端口
    u32  m_tDStreamIp;    //双流RTCP回馈地址
    u16  m_tDStreamPort;  //双流RTCP回馈端口

public:
    TRecRtcpBack(void)
	{
		Reset();
	}
	void Reset(void)
	{
		m_tVideoIp = 0xFFFFFFFF;
        m_tVideoPort = 0xFFFF;
        m_tAudioIp = 0xFFFFFFFF;
        m_tAudioPort = 0xFFFF;
        m_tDStreamIp = 0xFFFFFFFF;
        m_tDStreamPort = 0xFFFF;
	}

    void SetVideoAddr(u32 dwVideoIp, u16 wVideoPort)
    {
        m_tVideoIp = htonl(dwVideoIp);
        m_tVideoPort = htons(wVideoPort);
    }

    void GetVideoAddr(u32 &dwVideoIp, u16 &wVideoPort)
    {
        dwVideoIp = ntohl(m_tVideoIp);
        wVideoPort = ntohs(m_tVideoPort);
    }

    
    void SetAudioAddr(u32 dwAudioIp, u16 wAudioPort)
    {
        m_tAudioIp = htonl(dwAudioIp);
        m_tAudioPort = htons(wAudioPort);
    }

    void GetAudioAddr(u32 &dwAudioIp, u16 &wAudioPort)
    {
        dwAudioIp = ntohl(m_tAudioIp);
        wAudioPort = ntohs(m_tAudioPort);
    }

    
    void SetDStreamAddr(u32 dwDStreamIp, u16 wDStreamPort)
    {
        m_tDStreamIp = htonl(dwDStreamIp);
        m_tDStreamPort = htons(wDStreamPort);
    }

    void GetDStreamAddr(u32 &dwDStreamIp, u16 &wDStreamPort)
    {
        dwDStreamIp = ntohl(m_tDStreamIp);
        wDStreamPort = ntohs(m_tDStreamPort);
    }
}
#ifndef WIN32
__attribute__((packed))
#endif
;

//录像机信道状态
struct TRecChnnlStatus
{
	/*通道的状态*/
	enum ERecChnnlState
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
	enum ERecChnnlType
	{
		TYPE_UNUSE      =  0,	/*未始用的通道*/
		TYPE_RECORD     =  1,	/*录像通道  */   
		TYPE_PLAY       =  2	/*播放通道  */
	};

	//录像方式
	enum ERecMode
	{
		MODE_SKIPFRAME = 0,//抽帧录像
		MODE_REALTIME  = 1  //实时录像
	};
public:
	u8  		m_byType;		//通道类型：ERecChnnlType
	u8  		m_byState;		//通道状态：ERecChnnlState
	u8          m_byRecMode;    //录像方式:
	TRecProg	m_tProg;	//当前录像或放像进度
protected:
	char	m_achRecordName[MAXLEN_RECORD_NAME];//记录名
	
public:
	//获取记录名
	LPCSTR GetRecordName( void ) const	{ return m_achRecordName; }
	//设置记录名
	void SetRecordName( LPCSTR lpszName ) 
	{
		strncpy( m_achRecordName, lpszName, sizeof( m_achRecordName ) );
		m_achRecordName[sizeof( m_achRecordName ) - 1] ='\0';
	}
	
	LPCSTR GetStatusStr( u8 eStatus )
	{
		switch(eStatus) 
		{
		case STATE_IDLE:
			return "IDLE";
			break;
		case STATE_RECREADY:
			return "REC Ready";
			break;
		case STATE_RECORDING:
			return "Recording";
			break;
		case STATE_RECPAUSE:
			return "REC Pause";
			break;
		case STATE_PLAYREADY:
			return "PLAY Ready";
			break;
		case STATE_PLAYING:
			return "Playing";
			break;
		case STATE_PLAYPAUSE:
			return "Play Pause";
			break;
		case STATE_FF:
			return "Play FF";
			break;
		case STATE_FB:
			return "Play FB";
		default:
			return "UNKOWN";
		}
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//录像机状态, size = 2412
struct TRecStatus
{
protected:
	u8  	m_byRecChnnlNum;		//录像信道配置数
	u8  	m_byPlayChnnlNum;		//放像信道配置数
	u8      m_bSupportPublic;       // 是否支持发布(TRUE: 支持, FALSE:不支持)
	u8      m_byRemain;             // 保留
 	u32   	m_dwFreeSpace;        //录像机剩余磁盘空间(单位为MB)
	u32   	m_dwTotalSpace;		//录像机总磁盘空间(单位为MB)
	TRecChnnlStatus m_tChnnlStatus[MAXNUM_RECORDER_CHNNL];	//先录像信道后放像信道

public:
	//获取录像通道配置
	u8   GetRecChnnlNum( void ) const	{ return( m_byRecChnnlNum ); }
	//获取放像通道配置
	u8   GetPlayChnnlNum( void ) const	{ return( m_byPlayChnnlNum ); }
	//配置通道数，录像和放像通道总数必须不大于MAXNUM_RECORDER_CHNNL
	//失败返回FALSE
	BOOL SetChnnlNum( u8   byRecChnnlNum, u8   byPlayChnnlNum )
	{
		if( byRecChnnlNum + byPlayChnnlNum <= MAXNUM_RECORDER_CHNNL )
		{
			m_byRecChnnlNum = byRecChnnlNum;
			m_byPlayChnnlNum = byPlayChnnlNum;
			return( TRUE );
		}
		else
		{
			OspPrintf( TRUE, FALSE, "TRecStatus: Exception - Wrong recorder and play channel number: %u and %u!\n", 
				byRecChnnlNum, byPlayChnnlNum );
			return( FALSE );
		}
	}
		/*====================================================================
    功能        ：设置录像机剩余磁盘空间
    输入参数说明：u32    dwFreeSpace  - 剩余空间大小(单位 Mb)
    返回值说明  ：无
	====================================================================*/
	void SetFreeSpaceSize( u32    dwFreeSpace )
	{
		m_dwFreeSpace  = htonl(dwFreeSpace);
	}
	
	/*====================================================================
    功能        ：获取录像机剩余磁盘空间
    输入参数说明：无
    返回值说明  ：剩余空间大小(单位 MB)
	====================================================================*/
	u32    GetFreeSpaceSize( void ) const	{ return ntohl( m_dwFreeSpace ); }

		/*====================================================================
    功能        ：设置录像机总磁盘空间
    输入参数说明：u32    dwTotalSpace  - 总空间大小(单位 MB)
    返回值说明  ：无
	====================================================================*/
	void SetTotalSpaceSize( u32    dwTotalSpace )
	{
		m_dwTotalSpace  = htonl( dwTotalSpace );
	}
	// 是否支持发布
	BOOL IsSupportPublic() const { return m_bSupportPublic;}
    // 设置是否支持发布
	void SetPublicAttribute(BOOL bSupportPublic ) { m_bSupportPublic = bSupportPublic;}

	/*====================================================================
    功能        ：获取录像机总磁盘空间
    输入参数说明：无
    返回值说明  ：总空间大小(单位 MB)
	====================================================================*/
	u32    GetTotalSpaceSize( void ) const	{ return ntohl( m_dwTotalSpace ); }

	//设置录像机信道状态信息，必须先配置录放像信道数再调用此函数
	BOOL SetChnnlStatus( u8   byChnnlIndex, u8   byChnnlType, const TRecChnnlStatus * ptStatus );
	//设置录像机信道状态信息，必须先配置录放像信道数再调用此函数
	BOOL GetChnnlStatus( u8   byChnnlIndex, u8   byChnnlType, TRecChnnlStatus * ptStatus ) const;
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// 包体积应比较小，否则数组过大
#define RECLIST_PACKSIZE    (u8)16
struct TRecFileListNotify
{
	u16 wListSize;//录像机中文件总数
	u16 wStartIdx;//本通知中起始文件序号
	u16 wEndIdx;  //本通知中结束文件序号
    
	s8 achFileName[RECLIST_PACKSIZE][MAXLEN_CONFNAME+MAXLEN_RECORD_NAME+1];
	u8 abyStatus[RECLIST_PACKSIZE];
public:
	TRecFileListNotify()
	{
		wListSize = 0;
		wStartIdx = 0;
		wEndIdx   = 0;
		memset ( achFileName ,0,sizeof(achFileName) );
		memset( abyStatus ,0 ,sizeof(abyStatus) );
	}

	//获取录像机记录总数
	u16 GetListSize()
	{
		return ntohs(wListSize);
	}
	
	//获取本通知中起始文件序号
	u16 GetStartIdx()
	{
		return ntohs(wStartIdx);
	}

	//获取本通知中起始文件序号
	u16 GetEndIdx()
	{
		return ntohs(wEndIdx);
	}

	//获得指定序号的文件名,如不存在返回NULL
	char* GetFileName(u16 wIdx )
	{
		if( wIdx < GetStartIdx() || wIdx > GetEndIdx() )
			return NULL;
		return achFileName[wIdx - GetStartIdx()];
	}

	//判断指定序号的文件是否发布
	BOOL IsPublic(u16 wIdx)
	{
		if( wIdx < GetStartIdx() || wIdx > GetEndIdx() )
			return FALSE;
		return abyStatus[wIdx - GetStartIdx()]&0x1 ? TRUE:FALSE;
	}

	//设置指定序号的文件发布
	BOOL Public(u16 wIdx)
	{
		if( wIdx < GetStartIdx() || wIdx > GetEndIdx() )
			return FALSE;

		abyStatus[wIdx - GetStartIdx()] |=0x1;
		return TRUE;
	}

	/////////////////////////////////////////////
	//设置录像机记录总数
	void Reset()
	{
		wListSize = 0;
	    wStartIdx =0;
	    wEndIdx =0;
	    memset( achFileName,0,sizeof(achFileName) );
		memset( abyStatus , 0,sizeof(abyStatus) );
	}
	void SetListSize( u16 wSize)
	{
		wListSize = htons(wSize);
	}
	
	//设置本通知中起始文件序号
	void SetStartIdx( u16 wIdx)
	{
		wStartIdx = htons(wIdx);
	}

	//设置本通知中起始文件序号
	void SetEndIdx( u16 wIdx)
	{
		wEndIdx = htons(wIdx);
	}

	// 添加文件
	BOOL AddFile(char* filename ,BOOL bPublic = FALSE )
	{
		if ( IsFull() )
			return FALSE;

        u16 wIdx = GetEndIdx() - GetStartIdx();

		strncpy( achFileName[wIdx], filename ,sizeof(achFileName[wIdx]) - 1);
		achFileName[wIdx][sizeof(achFileName)-1]='\0';

		if ( bPublic ) 
        {
            abyStatus[wIdx] |=0x1;
        }
		else 
        {
            abyStatus[wIdx] &=~0x01;
        }

        // 序号自动增量
        SetEndIdx( GetEndIdx() + 1 );
		return TRUE;
	}

	//判断缓存是否已满
	BOOL32 IsFull()
	{
		u16 wSize = GetEndIdx() - GetStartIdx();
		if( wSize >= RECLIST_PACKSIZE )
			return TRUE;
		return FALSE;
	}

    BOOL32 IsEmpty()
    {
        return (GetEndIdx() == GetStartIdx());
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TPlayFileAttrib
{
protected:
    u8 m_byFileType;
    u8 m_byAudioType;
    u8 m_byVideoType;
    u8 m_byDVideoType;

public:
    TPlayFileAttrib(void)
    {
        m_byFileType = RECFILE_NORMAL;
        m_byAudioType = MEDIA_TYPE_NULL;
        m_byVideoType = MEDIA_TYPE_NULL;
        m_byDVideoType = MEDIA_TYPE_NULL;
    }

    BOOL32 IsDStreamFile(void) const
    {
        return (RECFILE_DSTREAM == m_byFileType) ? TRUE : FALSE;
    }
    u8 GetFileType(void) const
    {
        return m_byFileType;
    }
    void SetFileType(u8 byFileType)
    {
        m_byFileType = byFileType;
    }

    u8 GetAudioType(void) const
    {
        return m_byAudioType;
    }
    void SetAudioType(u8 byAudioType)
    {
        m_byAudioType = byAudioType;
    }

    u8 GetVideoType(void) const
    {
        return m_byVideoType;
    }
    void SetVideoType(u8 byVideoType)
    {
        m_byVideoType = byVideoType;
    }

    u8 GetDVideoType(void) const
    {
        return m_byDVideoType;
    }
    void SetDVideoType(u8 byDVideoType)
    {
        m_byDVideoType = byDVideoType;
    }
    
    void Print() const
    {
        OspPrintf(TRUE, FALSE, "m_byFileType: %d\n", m_byFileType);
        OspPrintf(TRUE, FALSE, "m_byAudioType: %d\n", m_byAudioType);
        OspPrintf(TRUE, FALSE, "m_byVideoType: %d\n", m_byVideoType);
        OspPrintf(TRUE, FALSE, "m_byDVideoType: %d\n", m_byDVideoType);
    }
}
#ifndef WIN32
__attribute__ ((packed))
#endif
;

// zgc, 2008-08-02, MCU的放像文件媒体信息
struct TPlayFileMediaInfo
{
    enum emStreamType
    {
        emAudio = 0,
        emVideo,
        emDVideo,
        emEnd
    };

private:
    //流的个数
    u8 m_byNum;
    //流的类型
    u8 m_abyMediaType[emEnd];
    u16	m_awWidth[emEnd];
	u16 m_awHeight[emEnd];

public:
    void clear( void )
    {
        m_byNum = 0;
        for ( u8 byLop = 0; byLop < emEnd; byLop++ )
        {
            m_abyMediaType[byLop] = MEDIA_TYPE_NULL;
            m_awWidth[byLop] = 0;
            m_awHeight[byLop] = 0;
        }
    }
    void SetStreamNum( u8 byNum ) { m_byNum = byNum; }
    u8   GetStreamNum( void ) const { return m_byNum; }
    void SetAudio( u8 byAudioType ) { m_abyMediaType[emAudio] = byAudioType; }
    u8   GetAudio( void ) const { return m_abyMediaType[emAudio]; }
    void SetVideo( u8 byVideoType, u16 wWidth, u16 wHeight ) 
    { 
        m_abyMediaType[emVideo] = byVideoType; 
        m_awWidth[emVideo] = htons(wWidth);
        m_awHeight[emVideo] = htons(wHeight);
        return;
    }
    void GetVideo( u8 &byVideoType, u16 &wWidth, u16 &wHeight ) const 
    { 
        byVideoType = m_abyMediaType[emVideo]; 
        wWidth = ntohs(m_awWidth[emVideo]);
        wHeight = ntohs(m_awHeight[emVideo]);
        return;
    }
    void SetDVideo( u8 byDVideoType, u16 wWidth, u16 wHeight ) 
    { 
        m_abyMediaType[emDVideo] = byDVideoType; 
        m_awWidth[emDVideo] = htons(wWidth);
        m_awHeight[emDVideo] = htons(wHeight);
        return;
    }
    void GetDVideo( u8 &byDVideoType, u16 &wWidth, u16 &wHeight ) const 
    { 
        byDVideoType = m_abyMediaType[emDVideo]; 
        wWidth = ntohs(m_awWidth[emDVideo]);
        wHeight = ntohs(m_awHeight[emDVideo]);
        return;
    }
}
#ifndef WIN32
__attribute__ ((packed))
#endif
;

struct TPlayEqpAttrib : public TPlayFileAttrib
{
protected:
    u8 m_byIsDStreamPlay;

public:
    TPlayEqpAttrib(void)
    {
        m_byIsDStreamPlay = 0;
    }

    void Reset()
    {
        m_byFileType = RECFILE_NORMAL;
        m_byAudioType = MEDIA_TYPE_NULL;
        m_byVideoType = MEDIA_TYPE_NULL;
        m_byDVideoType = MEDIA_TYPE_NULL;
        m_byIsDStreamPlay = 0;
    }

    BOOL32 IsDStreamPlay(void) const
    {
        return (m_byIsDStreamPlay == 1) ? TRUE : FALSE;
    }
    void SetDStreamPlay(u8 byIsDStreamPlay)
    {
        m_byIsDStreamPlay = byIsDStreamPlay;
    }

    void Print() const
    {
        TPlayFileAttrib::Print();
        OspPrintf(TRUE, FALSE, "m_byIsDStreamPlay: %d\n", m_byIsDStreamPlay);
    }    
}
#ifndef WIN32
__attribute__ ((packed))
#endif
;

/*----------------------------------------------------------------------
结构名：CConfVidTypeMgr
用途  ：码流接收类型管理
说明  ：接收对象目前仅包括终端和录象机
----------------------------------------------------------------------*/
/*
class CConfVidTypeMgr
{  
public:
    enum emMediaType
    {        
        emH264_1080 = 0,
        emH264_720,
        emH264_4CIF,
        emH264_CIF,
        emOther, // 主视频格式/双流同主视频格式

		emH239H264_UXGA,
        emH239H264_SXGA,
        emH239H264_XGA,
        emH239H264_SVGA,
        emH239H264_VGA,
        emDVidOther // 双流格式
    };
    
public:
    u8 m_abyMediaType[emOther+1];
    u8 m_abyDualMediaType[emDVidOther+1];     // 双流不考虑H264以外格式，Other仅作保存
    
public:
    CConfVidTypeMgr () 
    { 
        memset( m_abyMediaType, 0, sizeof(m_abyMediaType) ); 
        memset( m_abyDualMediaType, 0, sizeof(m_abyDualMediaType) );
    }

    void ConvertIn2Out( u8 emType, u8 &byOutType, u8 &byOutRes )
    {
        emMediaType emIntype = (emMediaType)emType;
        if ( emIntype == emOther ||
             emIntype == emDVidOther )
        {
            byOutType = MEDIA_TYPE_NULL;
            byOutRes = 0;
            return;
        }
        else
        {
            byOutType = MEDIA_TYPE_H264;
        }

        switch( emIntype )
        {
        case emH264_1080:
            byOutRes = VIDEO_FORMAT_HD1080;
            break;
        case emH264_720:
            byOutRes = VIDEO_FORMAT_HD720;
            break;
        case emH264_4CIF:
            byOutRes = VIDEO_FORMAT_4CIF;
            break;
        case emH264_CIF:
            byOutRes = VIDEO_FORMAT_CIF;
            break;
        case emH239H264_VGA:
            byOutRes = VIDEO_FORMAT_VGA;
            break;
        case emH239H264_SVGA:
            byOutRes = VIDEO_FORMAT_SVGA;
            break;
        case emH239H264_XGA:
            byOutRes = VIDEO_FORMAT_XGA;
            break;
        case emH239H264_SXGA:
            byOutRes = VIDEO_FORMAT_SXGA;
            break;
		case emH239H264_UXGA:
			byOutRes = VIDEO_FORMAT_UXGA;
			break;
        default:
            byOutType = MEDIA_TYPE_NULL;
            byOutRes = 0;
            break;
        }
        return;
    }
    
    u8 ConvertOut2In( u8 byOutType, u8 byOutRes, BOOL32 bDVid = FALSE )
    {
        emMediaType emIntype;
        switch( byOutType )
        {
        case MEDIA_TYPE_H264:
            {
                switch( byOutRes )
                {
                case VIDEO_FORMAT_CIF:
                    emIntype = emH264_CIF;
                    break;
                case VIDEO_FORMAT_4CIF:
                    emIntype = emH264_4CIF;
                    break;
                case VIDEO_FORMAT_HD720:
                    emIntype = emH264_720;
                    break;
                case VIDEO_FORMAT_HD1080:
                    emIntype = emH264_1080;
                    break;
                case VIDEO_FORMAT_VGA:
                    emIntype = emH239H264_VGA;
                    break;
                case VIDEO_FORMAT_SVGA:
                    emIntype = emH239H264_SVGA;
                    break;
                case VIDEO_FORMAT_XGA:
                    emIntype = emH239H264_XGA;
                    break;
                case VIDEO_FORMAT_SXGA:
                    emIntype = emH239H264_SXGA;
                    break;
				case VIDEO_FORMAT_UXGA:
					emIntype = emH239H264_UXGA;
					break;
                default:
                    emIntype = bDVid ? emDVidOther : emOther;
                    break;
                }
            }
            break;
        default:
            emIntype = bDVid ? emDVidOther : emOther;
            break;
        }
        return (u8)emIntype;
    }
    
    BOOL32 IsTypeExist( u8 emType, BOOL32 bDVid = FALSE )
    {
        if ( !bDVid )
        {
            if ( !IsVGAType(emType) )
            {
                return ( m_abyMediaType[(emMediaType)emType] > 0 );
            }
            else
            {
                return FALSE;
            }
        }
        else
        {
            return ( m_abyDualMediaType[(emMediaType)emType] > 0 );
        }
    }

    void AddType( u8 emType, BOOL32 bDVid = FALSE )
    {
        if ( !bDVid )
        {
            if ( !IsVGAType(emType) )
            {
                m_abyMediaType[(emMediaType)emType]++;
            }
        }
        else
        {
            m_abyDualMediaType[(emMediaType)emType]++;
        }
        return;
    }

    void DelType( u8 emType, BOOL32 bDVid = FALSE )
    {
        if ( IsTypeExist(emType, bDVid) )
        {
            if ( !bDVid )
            {
                m_abyMediaType[(emMediaType)emType]--;
            }
            else
            {
                m_abyDualMediaType[(emMediaType)emType]--;
            }
        }
        return;
    }
    
    u8 GetTypeNum(BOOL32 bDVid = FALSE)
    {
        u8 byNum = 0;
        if ( !bDVid )
        {          
            for( u8 byLop = 0; byLop < sizeof(m_abyMediaType); byLop++ )
            {
                if ( m_abyMediaType[(emMediaType)byLop] > 0 )
                {
                    byNum++;
                }
            }
        }
        else
        {
            for( u8 byLop = 0; byLop < sizeof(m_abyDualMediaType); byLop++ )
            {
                if ( m_abyDualMediaType[(emMediaType)byLop] > 0 )
                {
                    byNum++;
                }
            }
        }
        return byNum;
    }
    
    u8 GetH264TypeNum(BOOL32 bDVid = FALSE)
    {
        u8 byNum = 0;
        if ( !bDVid )
        {          
            for( u8 byLop = 0; byLop < sizeof(m_abyMediaType); byLop++ )
            {
                if ( m_abyMediaType[(emMediaType)byLop] > 0 && (emMediaType)byLop != emOther )
                {
                    byNum++;
                }
            }
        }
        else
        {
            for( u8 byLop = 0; byLop < sizeof(m_abyDualMediaType); byLop++ )
            {
                if ( m_abyDualMediaType[(emMediaType)byLop] > 0 &&
                     (emMediaType)byLop != emOther &&
                     (emMediaType)byLop != emDVidOther )
                {
                    byNum++;
                }
            }
        }
        return byNum;
    }

    u8 GetAdaptTypeNum( u8 bySrcOutType, u8 bySrcOutRes, BOOL32 bDVid = FALSE )
    {
        u8 emType = ConvertOut2In( bySrcOutType, bySrcOutRes, bDVid );
        u8 byRecvTypeNum = GetAdaptTypeNum( emType, bDVid );
        return byRecvTypeNum;
    }

    u8 GetAdaptTypeNum( u8 emSrcType, BOOL32 bDVid = FALSE )
    {
        u8 byRecvTypeNum = 0;
        if ( !bDVid )
        {
            for ( u8 byLop = (emMediaType)emSrcType+1; byLop < sizeof(m_abyMediaType); byLop++ )
            {
                if ( IsTypeExist(byLop, bDVid) )
                {
                    byRecvTypeNum++;
                }
            }
        }
        else
        {
            for ( u8 byLop = (emMediaType)emSrcType+1; byLop < sizeof(m_abyDualMediaType); byLop++ )
            {
                if ( IsTypeExist(byLop, bDVid) &&
                     // 适配目的应该和源的双流类型相同
                     IsVGAType(emSrcType) == IsVGAType(byLop) &&
                     byLop != emOther && byLop != emDVidOther )
                {
                    byRecvTypeNum++;
                }
                if ( IsVGAType(emSrcType) != IsVGAType(byLop) )
                {
                    break;
                }
            }
        }
        return byRecvTypeNum;
    }

    BOOL32 IsVGAType( u8 emType )
    {
        emMediaType emInType = (emMediaType)emType;
        return ( emInType <= emOther ) ? FALSE : TRUE;
    }

    u8  GetMinH264AdaptType( u8 emSrcType, BOOL32 bDVid = FALSE )
    {
        emMediaType emIntype = (emMediaType)emSrcType;
        emMediaType emMinType = emIntype;
        if ( !bDVid )
        {
            for ( u8 byLop = emIntype+1; byLop < emOther; byLop++ )
            {
                if ( IsTypeExist(byLop, bDVid) )
                {
                    emMinType = (emMediaType)byLop;
                }
            }
        }
        else
        {
            for ( u8 byLop = emIntype+1; byLop < emDVidOther; byLop++ )
            {
                if ( IsTypeExist(byLop, bDVid) && byLop != emOther )
                {
                    emMinType = (emMediaType)byLop;
                }
            }
        }

        return (u8)emMinType;
    }
	void Print( void )
	{
		u8 byType = 0;

		OspPrintf( TRUE, FALSE, "主流待适配的群组为：\n" );
		for(byType = emH264_1080; byType <= emOther; byType ++)
		{
			if (m_abyMediaType[byType] != 0)
			{
				OspPrintf( TRUE, FALSE, "\tType.%d, num.%d\n", byType, m_abyMediaType[byType] );
			}
		}
		OspPrintf( TRUE, FALSE, "\n" );

		OspPrintf( TRUE, FALSE, "双流待适配的群组为：\n" );
		for(byType = emH239H264_UXGA; byType <= emDVidOther; byType ++)
		{
			if (m_abyDualMediaType[byType] != 0)
			{
				OspPrintf( TRUE, FALSE, "\tType.%d, num.%d\n", byType, m_abyDualMediaType[byType] );
			}
		}
		OspPrintf( TRUE, FALSE, "\n" );
	}
}
#ifndef WIN32
__attribute__ ((packed))
#endif
;*/

//modify bas 2
//适配器启动参数结构
struct TAdaptParam
{
    enum EVideoType
    {
        vNONE  = MEDIA_TYPE_NULL,//视频不进行适配
        vMPEG4 = MEDIA_TYPE_MP4,
        vH261  = MEDIA_TYPE_H261,
        vH263  = MEDIA_TYPE_H263,
        vH264  = MEDIA_TYPE_H264,
    };
    enum EAudioType
    {
        aNONE  = MEDIA_TYPE_NULL,//音频不进行适配
        aMP3   = MEDIA_TYPE_MP3,
        aPCMA  = MEDIA_TYPE_PCMA,
        aPCMU  = MEDIA_TYPE_PCMU,
        aG7231 = MEDIA_TYPE_G7231,
        aG728  = MEDIA_TYPE_G728,
        aG729  = MEDIA_TYPE_G729,
    };

public:
    u16  GetWidth(void) const	{ return (ntohs(m_wWidth)); };
    u16  GetHeight(void) const	{ return (ntohs(m_wHeight)); };
    u16  GetBitrate(void) const { return (ntohs(m_wBitRate));};

    void SetResolution(u16 wWidth, u16 wHeight)
    {
        m_wWidth = htons(wWidth);
        m_wHeight = htons(wHeight);
    }
	
	void SetBitRate(u16 wBitrate)
	{
	    m_wBitRate = htons(wBitrate);
	}
	
	void SetVidType(u8 eType)
	{
		m_byVidCodeType = (u8)eType;
	}
	u8 GetVidType(void){ return m_byVidCodeType ;}
	
	void SetAudType(u8 eType)
	{
		m_byAudCodeType = (u8)eType;
	}
	u8 GetAudType(void){ return m_byAudCodeType; }

	void SetVidActiveType(u8 eType)
	{
		m_byVidActiveType = (u8)eType;
	}
	u8 GetVidActiveType(void){ return m_byVidActiveType; }
	
	void SetAudActiveType(u8 eType)
	{
		m_byAudActiveType = (u8)eType;
	}
	u8 GetAudActiveType(void){ return m_byAudActiveType; }

	void SetIsNeedByPrs(BOOL32 bNeedPrs)
	{
		m_byNeedPrs = (TRUE == bNeedPrs) ? 1 : 0;
	}

	BOOL32 IsNeedbyPrs(void)
	{
		return (0 != m_byNeedPrs);
	}

    BOOL32 IsNull(void) const
    {
        return (MEDIA_TYPE_NULL == m_byAudCodeType || 0 == m_byAudCodeType ) &&
               (MEDIA_TYPE_NULL == m_byVidCodeType || 0 == m_byVidCodeType );
    }
    void Clear(void)
    {
        m_byAudCodeType = MEDIA_TYPE_NULL;
        m_byVidCodeType = MEDIA_TYPE_NULL;
        m_byAudActiveType = MEDIA_TYPE_NULL;
        m_byVidActiveType = MEDIA_TYPE_NULL;
        m_wBitRate = 0;
        m_wWidth = 0;
        m_wHeight = 0;
        m_byNeedPrs = 0;
    }
    void Print(void) const
    {
        OspPrintf(TRUE, FALSE, "TAdpParam:\n");
        OspPrintf(TRUE, FALSE, "\tm_byAudCodeType:\t%d\n", m_byAudCodeType);
        OspPrintf(TRUE, FALSE, "\tm_byVidCodeType:\t%d\n", m_byVidCodeType);
        OspPrintf(TRUE, FALSE, "\tm_byAudActiveType:\t%d\n", m_byAudActiveType);
        OspPrintf(TRUE, FALSE, "\tm_byVidActiveType:\t%d\n", m_byVidActiveType);

        OspPrintf(TRUE, FALSE, "\tm_wBitRate:\t\t%d\n", GetBitrate());
        OspPrintf(TRUE, FALSE, "\tm_wWidth:\t\t%d\n", GetWidth());
        OspPrintf(TRUE, FALSE, "\tm_wHeight:\t\t%d\n", GetHeight());
        OspPrintf(TRUE, FALSE, "\tm_byNeedPrs:\t\t%d\n", m_byNeedPrs);
    }

private:
    u8         m_byAudCodeType;  //适配音频输出类型
    u8         m_byVidCodeType;  //适配视频输出类型
    u8         m_byAudActiveType;//适配音频输出动态载荷类型
    u8         m_byVidActiveType;//适配视频输出动态载荷类型
    
    u16 	   m_wBitRate;//发送码率
    u16 	   m_wWidth; //图像宽度
    u16 	   m_wHeight;//图像宽度
    
    u8         m_byNeedPrs;
}
#ifndef WIN32
__attribute__ ((packed)) 
#endif
;

/*----------------------------------------------------------------------
结构名：THDAdaptParam
用途  ：HD适配参数
----------------------------------------------------------------------*/
struct THDAdaptParam : public TAdaptParam
{
public:
    u8 GetFrameRate( void ) { return m_byFrameRate; }
    void SetFrameRate(u8 byFrameRate) { m_byFrameRate = byFrameRate; }

    void Reset(void)
    {
        Clear();
        m_byFrameRate = 0;
        m_byReserve1 = 0;
        m_byReserve2 = 0;
        m_byReserve3 = 0;
    }
    void PrintHd(void) const
    {
        //this->Print();
        OspPrintf(TRUE, FALSE, "\tm_byFrameRate:\t\t%d\n", m_byFrameRate);
    }
private:
    u8 m_byFrameRate;
    u8 m_byReserve1;
    u8 m_byReserve2;
    u8 m_byReserve3;
}
#ifndef WIN32
__attribute__ ((packed)) 
#endif
;

/*----------------------------------------------------------------------
结构名：THDBasChnStatus
用途  ：HDBas适配通道
----------------------------------------------------------------------*/
struct THDBasChnStatus
{
    enum EBasStatus
    {
        IDLE   = 0, //空闲
        READY  = 1, //准备适配
        RUNING = 2  //正在适配
    };

public:
    void   SetStatus( u8 byStatus ) { m_byStatus = byStatus; };
    u8     GetStatus( void ) { return m_byStatus; }
    
    BOOL32 IsNull( void ) const { return m_tBas.IsNull(); }
    void   SetNull( void ) { m_tBas.SetNull(); }
    
    u8     GetReservedType( void ) { return m_byIsReserved; }
    BOOL32 IsReserved ( void ) const { return ( 1 == m_byIsReserved ); }
    void   SetIsReserved ( BOOL32 bIsReserved ) { m_byIsReserved = bIsReserved ? 1 : 0; }
    BOOL32 IsTempReserved ( void ) const { return ( 2 == m_byIsReserved ); }
    void   SetIsTempReserved ( BOOL32 bIsTempReserved ) { m_byIsReserved = bIsTempReserved ? 2 : 0; } 
    void   UnReserved( void ) { m_byIsReserved = 0; }
    
    void   SetChnIdx( u8 byChnIdx ) { m_byChnIdx = byChnIdx; }
    u8     GetChnIdx( void ) const { return m_byChnIdx; }
    
    void   SetEqp( TEqp tBas ) { m_tBas = tBas; }
    TEqp   GetEqp( void ) const { return m_tBas; }
    u8     GetEqpId( void ) const { return m_tBas.GetEqpId(); }	
    void   SetType( u8 byType ) { m_byType = byType; };
    u8     GetType( void ) { return m_byType; }

    void   Print() const
    {
        OspPrintf(TRUE, FALSE, "TEqp:\n");
        OspPrintf(TRUE, FALSE, "\tMcuId:\t\t%d\n", m_tBas.GetMcuId());
        OspPrintf(TRUE, FALSE, "\tEqpId:\t\t%d\n", m_tBas.GetMtId());
        OspPrintf(TRUE, FALSE, "\tMainType:\t%d\n", m_tBas.GetType());
        OspPrintf(TRUE, FALSE, "\tSubType:\t%d\n", m_tBas.GetEqpType());
        OspPrintf(TRUE, FALSE, "\tConfIdx:\t%d\n", m_tBas.GetConfIdx());
        OspPrintf(TRUE, FALSE, "\tDriId:\t\t%d\n", m_tBas.GetDriId());

        OspPrintf(TRUE, FALSE, "Status:\n");
        OspPrintf(TRUE, FALSE, "\tStatus:\t\t%d\n", m_byStatus);
        OspPrintf(TRUE, FALSE, "\tReserved:\t%d\n", m_byIsReserved);
        OspPrintf(TRUE, FALSE, "\tChnIdx:\t\t%d\n", m_byChnIdx);
        OspPrintf(TRUE, FALSE, "\tType:\t\t%d\n", m_byType);
    }
private:
    TEqp m_tBas;
    u8 m_byStatus;	// EBasStatus
    u8 m_byIsReserved; // 0 -- not reserve, 1 -- reserve, 2 -- temply reserve
	u8 m_byChnIdx;
    u8 m_byType; // zw 20081114
}
#ifndef WIN32
__attribute__ ((packed)) 
#endif
;

/*----------------------------------------------------------------------
结构名：THDBasVidChnStatus
用途  ：HDBas视频通道记录状态
----------------------------------------------------------------------*/
struct THDBasVidChnStatus : public THDBasChnStatus //len:39
{
private:
	THDAdaptParam m_atOutputVidParam[MAXNUM_VOUTPUT];

public:	
    THDAdaptParam * GetOutputVidParam( u8 byChnIdx )
    {
        if ( byChnIdx < MAXNUM_VOUTPUT )
        {
            return &m_atOutputVidParam[byChnIdx]; 
        }
        else
        {
            return NULL;
        }
    }
    void SetOutputVidParam(THDAdaptParam &tVidParam, u8 byChnIdx )
    {
        if ( byChnIdx < MAXNUM_VOUTPUT )
        {
            m_atOutputVidParam[byChnIdx] = tVidParam;
        }
        return;
    }

	void ClrOutputVidParam()
	{
 		THDAdaptParam tNullAdpParam;
		tNullAdpParam.Reset();  
		for (u8 byChnlIdx = 0; byChnlIdx < MAXNUM_VOUTPUT; byChnlIdx++)
		{
			m_atOutputVidParam[byChnlIdx] = tNullAdpParam;
		}
	}
    void PrintInfo() const
    {
        OspPrintf(TRUE, FALSE, "\nHDBasVidChnStatus info as follows:\n\n");
        Print();
        for(u8 byIdx = 0; byIdx < MAXNUM_VOUTPUT; byIdx ++)
        {
            m_atOutputVidParam[byIdx].Print();
            m_atOutputVidParam[byIdx].PrintHd();
        }
    }
}
#ifndef WIN32
__attribute__ ((packed)) 
#endif
;

typedef THDBasVidChnStatus THDBasDVidChnStatus;

/*----------------------------------------------------------------------
结构名：TMauBasStatus
用途  ：MauBas状态类，加进TPeriEqpStatus
----------------------------------------------------------------------*/
class TMauBasStatus
{
public:
    void SetVidChnStatus (THDBasVidChnStatus &tVidChnStatus, u8 byChnIdx = 0)
    {
        if ( byChnIdx < MAXNUM_MAU_VCHN )
        {
            m_atVidChnStatus[byChnIdx] = tVidChnStatus;
        }
        return;
    }
	void SetDVidChnStatus (THDBasDVidChnStatus &tDVidChnStatus, u8 byChnIdx = 0)
    {
        if ( byChnIdx < MAXNUM_MAU_DVCHN )
        {
            m_atDVidChnStatus[byChnIdx] = tDVidChnStatus;
        }
        return;
    }
	THDBasVidChnStatus * GetVidChnStatus(u8 byChnIdx = 0)
    {
        if ( byChnIdx < MAXNUM_MAU_VCHN )
        {
            return &m_atVidChnStatus[byChnIdx];
        }
        else
        {
            return NULL;
        }
    }
	THDBasDVidChnStatus * GetDVidChnStatus(u8 byChnIdx = 0)
    {
        if ( byChnIdx < MAXNUM_MAU_DVCHN )
        {
            return &m_atDVidChnStatus[byChnIdx];
        }
        else
        {
            return NULL;
        }
    }
    void Print() const
    {
        OspPrintf(TRUE, FALSE, "TMauBasStatus is as follows:\n");
        u8 byIdx = 0;
        for(byIdx = 0; byIdx < MAXNUM_MAU_VCHN; byIdx++)
        {
            m_atVidChnStatus[byIdx].PrintInfo();
        }
        for(byIdx = 0; byIdx < MAXNUM_MAU_DVCHN; byIdx++)
        {
            m_atDVidChnStatus[byIdx].PrintInfo();
        }
    }
private:
    THDBasVidChnStatus m_atVidChnStatus[MAXNUM_MAU_VCHN];	
    THDBasDVidChnStatus m_atDVidChnStatus[MAXNUM_MAU_DVCHN];
}
#ifndef WIN32
__attribute__ ((packed)) 
#endif
;

/*----------------------------------------------------------------------
结构名：TMpuBasStatus
用途  ：MpuBas状态类，加进TPeriEqpStatus
----------------------------------------------------------------------*/
class TMpuBasStatus
{
public:
    void SetVidChnStatus (THDBasVidChnStatus &tVidChnStatus, u8 byChnIdx)
    {
        if ( byChnIdx < MAXNUM_MPU_CHN )
        {
            m_atVidChnStatus[byChnIdx] = tVidChnStatus;
        }
        return;
    }
	THDBasVidChnStatus * GetVidChnStatus(u8 byChnIdx)
    {
        if ( byChnIdx < MAXNUM_MPU_CHN )
        {
            return &m_atVidChnStatus[byChnIdx];
        }
        else
        {
            return NULL;
        }
    }
    void Print() const
    {
        OspPrintf(TRUE, FALSE, "TMpuBasStatus is as follows:\n");
        u8 byIdx = 0;
        for(byIdx = 0; byIdx < MAXNUM_MPU_VCHN; byIdx++)
        {
            m_atVidChnStatus[byIdx].PrintInfo();
        }
    }
private:
    THDBasVidChnStatus m_atVidChnStatus[MAXNUM_MPU_VCHN];
}
#ifndef WIN32
__attribute__ ((packed)) 
#endif
;


/*----------------------------------------------------------------------
结构名：TMpuBasStatus
用途  ：MpuBas状态类，加进TPeriEqpStatus
----------------------------------------------------------------------*/
class THdBasStatus
{
public:
    union
    {
        TMauBasStatus tMauBas;
        TMpuBasStatus tMpuBas;
    }tStatus;

public:
    void SetEqpType(u8 byType)
    {
        if (byType != TYPE_MPU &&
            byType != TYPE_MAU_NORMAL &&
            byType != TYPE_MAU_H263PLUS)
        {
            OspPrintf(TRUE, FALSE, "[THdBasStatus][SetType] unexpected type.%d\n", m_byType);
            return;
        }
        m_byType = byType;
        return;
    }
    u8   GetEqpType(void) const { return m_byType; }

public:
    u8 m_byType;
}
#ifndef WIN32
__attribute__ ((packed)) 
#endif
;

//适配器通道状态结构
struct TBasChnStatus : TAdaptParam
{
    enum EBasStatus
    {
        IDLE   = 0, //空闲
        READY  = 1, //准备适配
        RUNING = 2  //正在适配
    };

protected:
    u8 m_byStatus;
	u8 m_byReserved;    //是否为保留通道
    u8 m_byChanType;    //音频通道: 1(BAS_CHAN_AUDIO)  视频通道: 2(BAS_CHAN_VIDEO)

public:

    void SetStatus(u8 byStatus)
    {
        m_byStatus = byStatus;
    }

    u8 GetStatus(void)
    {
        return m_byStatus;
    }

    void SetReserved(BOOL32 bReserved)
    {
        m_byReserved = (TRUE == bReserved) ? 1 : 0;
    }

    BOOL32 IsReserved(void)
    {
        return (0 != m_byReserved);
    }

    u8 GetChannelType(void)
    {
        return m_byChanType;
    }

    void SetChannelType(u8 byBasChanType)
    {
        m_byChanType = byBasChanType;
    }
}
#ifndef WIN32
__attribute__ ((packed))
#endif
;

//适配器启动的模块
struct TBasCapSet
{
public:
    u8 m_bySupportAudio;
    u8 m_bySupportVideo;
    u8 m_bySupportBitrate;

public:
    void SetAudioCapSet(BOOL32 bSupportAudio)
    {
        if (TRUE == bSupportAudio)
        {
            m_bySupportAudio = 1;
        }
        else
        {
            m_bySupportAudio = 0;
        }
    }

    BOOL32 IsSupportAudio(void)
    {
        if (0 == m_bySupportAudio)
        {
            return FALSE;
        }
        return TRUE;
    }

    void SetVideoCapSet(BOOL32 bSupportVideo)
    {
        if (TRUE == bSupportVideo)
        {
            m_bySupportVideo = 1;
        }
        else
        {
            m_bySupportVideo = 0;
        }
    }

    BOOL32 IsSupportVideo(void)
    {
        if (0 == m_bySupportVideo)
        {
            return FALSE;
        }
        return TRUE;
    }

    void SetBitrateCapSet(BOOL32 bSupportBitrate)
    {
        if (TRUE == bSupportBitrate)
        {
            m_bySupportBitrate = 1;
        }
        else
        {
            m_bySupportBitrate = 0;
        }
    }

    BOOL32 IsSupportBitrate(void)
    {
        if (0 == m_bySupportBitrate)
        {
            return FALSE;
        }
        return TRUE;
    }
}
#ifndef WIN32
__attribute__((packed))
#endif
;

//适配器通道状态结构
struct TBasStatus
{
	u8            byChnNum;
    TBasCapSet    tBasCapSet;
    TBasChnStatus tChnnl[MAXNUM_BAS_CHNNL];
}
#ifndef WIN32
__attribute__((packed))
#endif
;


//定义DCS状态结构
struct TPeriDcsStatus : public TEqp
{
public:
	u8	m_byOnline;			//是否在线
protected:
	s8	m_achDcsAlias[MAXLEN_EQP_ALIAS];
public:
	TPeriDcsStatus()
	{
		memset( this, 0, sizeof(TPeriDcsStatus) );
	}

	//获取DCS别名
	const s8 * GetDcsAlias() const
	{
		return m_achDcsAlias;
	}
	//设置外设别名
	void SetDcsAlias( const s8 * lpszAlias )
	{
		strncpy( m_achDcsAlias, lpszAlias, sizeof(m_achDcsAlias) );
		m_achDcsAlias[MAXLEN_EQP_ALIAS - 1] = '\0';
	}
	//置空
	void SetNull()
	{
		memset( this, 0, sizeof(TPeriDcsStatus) );
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//定义外设状态结构, size = 2435(TRecStatus = 2412)
struct TPeriEqpStatus : public TEqp
{
public:
	u8  	m_byOnline;		//是否在线
	union UStatus
	{
		TTvWallStatus	tTvWall;
		TMixerStatus	tMixer;
		TVmpStatus      tVmp;
		TRecStatus		tRecorder;
		TBasStatus		tBas;
		TPrsStatus		tPrs;
        THdBasStatus    tHdBas;
		THduStatus      tHdu;

	} m_tStatus;
	
protected:
	char    m_achAlias[MAXLEN_EQP_ALIAS];
public:
	//constructor
	TPeriEqpStatus( void )
	{
		memset(this, 0, sizeof(TPeriEqpStatus));
	}

	//获取外设别名
	const s8 * GetAlias() const 
	{ 
		return m_achAlias;
	}

	//设置外设别名
	void SetAlias(const s8 * lpszAlias)
	{ 
		strncpy(m_achAlias, lpszAlias, sizeof(m_achAlias));
		m_achAlias[MAXLEN_EQP_ALIAS-1] = '\0';
	}

}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//定义要增加的终端信息
struct TAddMtInfo: public TMtAlias
{
	u8   m_byCallMode;
	u16  m_wDialBitRate;//（网络序）//单位Kbps
public:
	u16  GetCallBitRate() { return ntohs(m_wDialBitRate); }
	void SetCallBitRate(u16 wDialBitRate) { m_wDialBitRate = htons(wDialBitRate); }

    u8   GetCallMode() { return m_byCallMode; }
    void SetCallMode(u8 byCallMode) { m_byCallMode = byCallMode; }

}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//调试版，增加终端时mcs指定的能力级信息
struct TAddMtCapInfo
{
private:
	TVideoStreamCap  m_tMainVideoCap;
	TVideoStreamCap  m_tDStreamVideoCap;
public:
	TAddMtCapInfo()	{ clear(); }
	void clear()
	{
		m_tMainVideoCap.Clear();
		m_tDStreamVideoCap.Clear();		
	}
	const TVideoStreamCap& GetMainVideoCap() const    { return m_tMainVideoCap; }
	void SetMainVideoCap(TVideoStreamCap& tVideoSteamCap) 
	{
		memcpy( &m_tMainVideoCap, &tVideoSteamCap, sizeof(TVideoStreamCap) );
	}

	const TVideoStreamCap& GetDStreamVideoCap() const { return m_tDStreamVideoCap; }
	void SetDStreamVideoCap(TVideoStreamCap& tVideoSteamCap) 
	{
		memcpy( &m_tDStreamVideoCap, &tVideoSteamCap, sizeof(TVideoStreamCap) );
	}
	
	// 主视频能力
    void	SetMainMaxBitRate(u16 wMaxRate)  {  m_tMainVideoCap.SetMaxBitRate(wMaxRate); }	
    u16		GetMainMaxBitRate() const { return m_tMainVideoCap.GetMaxBitRate(); }
	
    void	SetMainMediaType(u8 byMediaType)  {  m_tMainVideoCap.SetMediaType(byMediaType); }	
    u8		GetMainMediaType() const { return m_tMainVideoCap.GetMediaType(); }
    
    void    SetMainResolution(u8 byRes) {   m_tMainVideoCap.SetResolution(byRes);    }
    u8      GetMainResolution(void) const   {   return m_tMainVideoCap.GetResolution();    }

    void    SetMainFrameRate(u8 byFrameRate)
    {
        if ( MEDIA_TYPE_H264 == m_tMainVideoCap.GetMediaType() )
        {
            OspPrintf( TRUE, FALSE, "Function has been preciated, try SetUserDefFrameRate\n" );
            return;
        }
        m_tMainVideoCap.SetFrameRate(byFrameRate);
		return;
    }
    u8      GetMainFrameRate(void) const
    {
        if ( MEDIA_TYPE_H264 == m_tMainVideoCap.GetMediaType() )
        {
            OspPrintf( TRUE, FALSE, "Function has been preciated, try GetUserDefFrameRate\n" );
            return 0;
        }
        return m_tMainVideoCap.GetFrameRate();
    }

    // 自定义帧率
    void    SetUserDefMainFrameRate(u8 byActFrameRate) { m_tMainVideoCap.SetUserDefFrameRate(byActFrameRate); }
    BOOL32  IsMainFrameRateUserDefined() const {return m_tMainVideoCap.IsFrameRateUserDefined(); }
    u8      GetUserDefMainFrameRate(void) const { return m_tMainVideoCap.GetUserDefFrameRate(); }

	// 双流能力
    void	SetDstreamMaxBitRate(u16 wMaxRate)  {  m_tDStreamVideoCap.SetMaxBitRate(wMaxRate); }	
    u16		GetDstreamMaxBitRate() const { return m_tDStreamVideoCap.GetMaxBitRate(); }

    void	SetDstreamMediaType(u8 byMediaType)  {  m_tDStreamVideoCap.SetMediaType(byMediaType); }	
    u8		GetDstreamMediaType() const { return m_tDStreamVideoCap.GetMediaType(); }
    
    void    SetDstreamResolution(u8 byRes) {   m_tDStreamVideoCap.SetResolution(byRes);    }
    u8      GetDstreamResolution(void) const   {   return m_tDStreamVideoCap.GetResolution();    }

    void    SetDstreamFrameRate(u8 byFrameRate)
    {
        if ( MEDIA_TYPE_H264 == m_tDStreamVideoCap.GetMediaType() )
        {
            OspPrintf( TRUE, FALSE, "Function has been preciated, try SetUserDefFrameRate\n" );
            return;
        }
        m_tDStreamVideoCap.SetFrameRate(byFrameRate);
		return;
    }
    u8      GetDstreamFrameRate(void) const
    {
        if ( MEDIA_TYPE_H264 == m_tDStreamVideoCap.GetMediaType() )
        {
            OspPrintf( TRUE, FALSE, "Function has been preciated, try GetUserDefFrameRate\n" );
            return 0;
        }
        return m_tDStreamVideoCap.GetFrameRate();
    }

    // 自定义帧率
    void    SetUserDefDstreamFrameRate(u8 byActFrameRate) { m_tDStreamVideoCap.SetUserDefFrameRate(byActFrameRate); }
    BOOL32  IsDstreamFrameRateUserDefined() const {return m_tDStreamVideoCap.IsFrameRateUserDefined(); }
    u8      GetUserDefDstreamFrameRate(void) const { return m_tDStreamVideoCap.GetUserDefFrameRate(); }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//调试版增加终端的信息，包含MCS指定的部分终端能力级
struct TAddMtInfoEx: public TAddMtInfo
{
private:
	TAddMtCapInfo m_tMtCapInfo;

public:
	TAddMtInfoEx()	{ clear(); }
	void clear()
	{
		m_tMtCapInfo.clear();
	}

	const TAddMtCapInfo& GetMtCapInfo() const    { return m_tMtCapInfo; }
	void SetMtCapInfo(TAddMtCapInfo& tMtCapInfo) 
	{
		memcpy( &m_tMtCapInfo, &tMtCapInfo, sizeof(TAddMtCapInfo) );
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;



//定义会议终端结构，该结构定义了参加会议的MCU和两个终端列表（受邀终端列表和实际
//与会终端列表），后者必须是前者的子集 
struct TConfMtInfo
{
protected:   
	u8      m_byMcuId;          //该MC所在的Mcu的Id号
    u8      m_byConfIdx;        //会议索引号 
	u8  	m_abyMt[MAXNUM_CONF_MT/8];	        //受邀终端列表
	u8  	m_abyJoinedMt[MAXNUM_CONF_MT/8];	//与会终端列表

public:
    void  SetMcuId(u8   byMcuId){ m_byMcuId = byMcuId; } 
    u8    GetMcuId( void ) const { return m_byMcuId; }
    void  SetConfIdx(u8   byConfIdx){ m_byConfIdx = byConfIdx; } 
    u8    GetConfIdx( void ) const { return m_byConfIdx; }

	TConfMtInfo( void );//constructor
	BOOL MtInConf( u8 byMtId ) const;//判断该MCU下某终端是否在受邀终端列表中
	BOOL MtJoinedConf( u8 byMtId ) const;//判断该MCU下某终端是否在与会终端列表中
	void AddMt( u8 byMtId );//增加该MCU下终端于会议终端列表中
	void AddJoinedMt( u8 byMtId );//增加该MCU下终端于与会终端列表中，该函数自动将该终端也
	void RemoveMt( u8 byMtId );//删除该MCU下终端于受邀终端列表中，该函数自动将该终端也
	void RemoveJoinedMt( u8 byMtId );//删除该MCU下终端于与会终端列表中
	void RemoveAllMt( void );//删除该MCU下所有终端于受邀终端列表中，该函数自动将所有终端也
	void RemoveAllJoinedMt( void );//删除该MCU下所有终端于与会终端列表中
	u8   GetAllMtNum( void ) const;//得到一个结构中所有受邀终端个数
	u8   GetAllJoinedMtNum( void ) const;//得到一个结构中所有与会终端个数
	u8   GetAllUnjoinedMtNum( void ) const;//得到一个结构中所有未与会终端个数
	u8	 GetMaxMtIdInConf( void ) const;	//得到一个结构中受邀终端中MtId最大的值// xliang [12/24/2008] 

	void SetNull( void )
	{
		m_byMcuId = 0;
		m_byConfIdx = 0;
	}
	BOOL IsNull( void ) const
	{
		if( m_byMcuId == 0 && m_byConfIdx == 0 )
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//会议所有终端信息 (len:3256)
struct TConfAllMtInfo
{
public:
	TConfMtInfo	m_tLocalMtInfo;
	TConfMtInfo	m_atOtherMcMtInfo[MAXNUM_SUB_MCU];
	TMt         m_tMMCU; //级联的上级MCU 

public:
    TConfAllMtInfo( void ){ Clear(); }

	void Clear() { memset( this, 0, sizeof(TConfAllMtInfo) ); }

    void   SetLocalMtInfo(TConfMtInfo tLocalMtInfo){ m_tLocalMtInfo = tLocalMtInfo; } 
    TConfMtInfo  GetLocalMtInfo( void ) const { return m_tLocalMtInfo; }

	BOOL AddMt( u8  byMtId );//会议中增加一个受邀终端  
	BOOL AddJoinedMt( u8  byMtId );//会议中增加一个与会终端，该函数自动将该终端也
	void RemoveMt( u8  byMtId );//会议中删除一个终端 
	void RemoveJoinedMt( u8  byMtId );//会议中删除一个与会终端
	void RemoveAllMt( void );//会议中删除一个MCU下所有受邀终端（不删除MCU），该函数
	void RemoveAllJoinedMt( void );//会议中删除一个MCU下所有与会终端（不删除MCU）
	BOOL MtInConf( u8  byMtId ) const;//判断终端是否在受邀终端列表中
	BOOL MtJoinedConf( u8  byMtId ) const;//判断终端是否在与会终端列表中
	// xliang [9/9/2009] FIXME
	BOOL MtJoinedConf( TMt tMt) const;	//可反映级联mcu下的mt是否与会
	u8   GetLocalMtNum( void ) const;//得到本地所有受邀终端个数 
	u8   GetLocalJoinedMtNum( void ) const;//得到本地所有与会终端个数
	u8   GetLocalUnjoinedMtNum( void ) const;//得到本地所有未与会终端个数

    void   SetMtInfo(TConfMtInfo tConfMtInfo );
    TConfMtInfo  GetMtInfo( u8 byMcuId ) const;
	TConfMtInfo* GetMtInfoPtr( u8 byMcuId);

	BOOL MtInConf( u8  byMcuId, u8  byMtId ) const;//判断终端是否在受邀终端列表中
	BOOL MtJoinedConf( u8  byMcuId, u8  byMtId ) const;//判断终端是否在与会终端列表中

	u16   GetAllMtNum( void ) const;//得到会议完整结构中所有受邀终端个数 
	u16   GetAllJoinedMtNum( void ) const;//得到会议完整结构中所有与会终端个数
	u8	GetMaxMtIdInConf( void )const;// xliang [12/24/2008]

	u8	GetCascadeMcuNum( void) const;

	BOOL AddMcuInfo( u8 byMcuId, u8 m_byConfIdx );   //会议中增加一个mcu信息，可能暂时没有终端
	BOOL RemoveMcuInfo( u8 byMcuId, u8 m_byConfIdx );//会议中移除一个mcu信息，同时清空所有所属终端信息

}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;


//定义电视墙设置结构，每个结构反映了一组终端号或MCU外设号和视频输出端口号的对应关系
struct TTVWallSetting
{
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//定义逻辑通道结构(len:47)
struct TLogicalChannel
{  
public:
	u8  m_byMediaType;      //媒体类型：MODE_VIDEO或MODE_AUDIO
	u8  m_byChannelType;    //信道类型：AUDIO_G711A、VIDEO_H261等
	u8  m_byVideoFormat;    //视频信道的分辩率
	u8  m_byH239DStream;    //信道类型是否是H239载荷
	u16 m_wFlowControl;     //信道流量(单位:Kbps,1K=1024)
    u16 m_wCurrFlowControl; //当前信道流量值
	TTransportAddr m_tRcvMediaChannel;     //接收端媒体信道
	TTransportAddr m_tRcvMediaCtrlChannel; //接收端媒体控制信道
	TTransportAddr m_tSndMediaCtrlChannel; //发送端媒体控制信道

	TMediaEncrypt  m_tMediaEncrypt;   //加密信息
	u8             m_byActivePayload; //动态载荷
	u8			   m_byFECType;		  //MCU前向纠错类型, zgc, 2007-10-10
    u8             m_byVidFPS;        //本通道码流的帧率 MODE_VIDEO下
public:
	TLogicalChannel(void)
	{ 
		Clear();
	}
    void Clear(void)
    {
        memset( this, 0, sizeof(TLogicalChannel));
		m_tMediaEncrypt.Reset();
		m_byChannelType = MEDIA_TYPE_NULL;
        m_wCurrFlowControl = 0xFFFF;
    }
    void SetMediaType(u8 byMediaType){ m_byMediaType = byMediaType;} 
    u8   GetMediaType( void ) const { return m_byMediaType; }
    void SetChannelType(u8 byChannelType){ m_byChannelType = byChannelType;} 
    u8   GetChannelType( void ) const { return m_byChannelType; }
    void SetSupportH239(BOOL32 bH239DStream){ m_byH239DStream = (bH239DStream ? 1:0);} 
    BOOL32   IsSupportH239( void ) const { return (m_byH239DStream == 0 ? FALSE : TRUE); }
    void SetVideoFormat(u8 byVideoFormat){ m_byVideoFormat = byVideoFormat;} 
    u8   GetVideoFormat( void ) const { return m_byVideoFormat; }
    void SetFlowControl(u16  wFlowControl){ m_wFlowControl = htons(wFlowControl);} 
    u16  GetFlowControl( void ) const { return ntohs(m_wFlowControl); }
    void SetCurrFlowControl(u16  wFlowControl){ m_wCurrFlowControl = htons(wFlowControl);} 
    u16  GetCurrFlowControl( void ) const { return ntohs(m_wCurrFlowControl); }
    void SetRcvMediaChannel(TTransportAddr tRcvMediaChannel){ m_tRcvMediaChannel = tRcvMediaChannel;} 
    TTransportAddr  GetRcvMediaChannel( void ) const { return m_tRcvMediaChannel; }
    void SetRcvMediaCtrlChannel(TTransportAddr tRcvMediaCtrlChannel){ m_tRcvMediaCtrlChannel = tRcvMediaCtrlChannel;} 
    TTransportAddr  GetRcvMediaCtrlChannel( void ) const { return m_tRcvMediaCtrlChannel; }
    void SetSndMediaCtrlChannel(TTransportAddr tSndMediaCtrlChannel){ m_tSndMediaCtrlChannel = tSndMediaCtrlChannel;} 
    TTransportAddr  GetSndMediaCtrlChannel( void ) const { return m_tSndMediaCtrlChannel; }
    BOOL IsOpened( void ) const { return m_byMediaType == 0 ? FALSE : TRUE; }

	void SetMediaEncrypt(TMediaEncrypt& tMediaEncrypt)
	{
		m_tMediaEncrypt = tMediaEncrypt;
	}
	TMediaEncrypt &GetMediaEncrypt()
	{
		return m_tMediaEncrypt;
	}

	void SetActivePayload(u8 byActivePayload)
	{
		m_byActivePayload = byActivePayload;
	}
	u8 GetActivePayload()
	{
		return m_byActivePayload;
	}

	void SetFECType( u8 byFECType ) { m_byFECType = byFECType; }
	u8	 GetFECType( void ) const { return m_byFECType; }
    void SetChanVidFPS( u8 byFPS ) { m_byVidFPS = byFPS;    }
    u8   GetChanVidFPS( void ) const { return m_byVidFPS;    }

}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//H239双流令牌拥有终端信息 (len:15)
typedef struct tagH239TokenInfo
{
    s32  m_nChannelId;   
    
    u8   m_bySymmetryBreaking;
	BOOL m_bIsResponseAck;

	//H239双流令牌拥有终端
	TMt  m_tH239TokenMt;   
    
    tagH239TokenInfo()
    {
        Clear();
    }

    void Clear()
    {
        m_nChannelId         = 0;
        m_bySymmetryBreaking = 0;
		m_bIsResponseAck     = FALSE;
        m_tH239TokenMt.SetNull();
    }

    void SetSymmetryBreaking(u8 bySymmetryBreaking)
    {
        m_bySymmetryBreaking = bySymmetryBreaking;
    }
    u8 GetSymmetryBreaking()
    {
        return m_bySymmetryBreaking;
    }

	void SetResponseAck(BOOL bIsResponseAck)
    {
        m_bIsResponseAck = bIsResponseAck;
    }
    BOOL IsResponseAck()
    {
        return m_bIsResponseAck;
    }

    void SetChannelId(s32 nChannelId)
    {
        m_nChannelId = nChannelId;
    }   
    s32 GetChannelId()
    {
        return m_nChannelId;
    }

	void SetTokenMt(TMt tH239TokenMt)
    {
        m_tH239TokenMt = tH239TokenMt;
    }   
    TMt GetTokenMt()
    {
        return m_tH239TokenMt;
    }
    
}TH239TokenInfo,*PTH239TokenInfo;
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif


//定义交换结构
struct TSwitchInfo
{
protected:
	TMt	  m_tDstMt;		  //交换目的终端
	TMt   m_tSrcMt;		  //交换源终端
	u8    m_byMode;		  //交换模式：MODE_VIDEO, MODE_AUDIO, MODE_BOTH
	u8    m_byDstChlIdx;  //目的通道索引
	u8    m_bySrcChlIdx;  //源通道索引号
public:
    void  SetDstMt(TMt tDstMt){ m_tDstMt = tDstMt;} 
    TMt   GetDstMt( void ) const { return m_tDstMt; }
    void  SetSrcMt(TMt tSrcMt){ m_tSrcMt = tSrcMt;} 
    TMt   GetSrcMt( void ) const { return m_tSrcMt; }
    void  SetMode(u8   byMode){ m_byMode = byMode;} 
    u8    GetMode( void ) const { return m_byMode; }
    void  SetDstChlIdx(u8   byDstChlIdx){ m_byDstChlIdx = byDstChlIdx;} 
    u8    GetDstChlIdx( void ) const { return m_byDstChlIdx; }
    void  SetSrcChlIdx(u8   bySrcChlIdx){ m_bySrcChlIdx = bySrcChlIdx;} 
    u8    GetSrcChlIdx( void ) const { return m_bySrcChlIdx; }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//定义电视墙交换结构
struct TTWSwitchInfo : public TSwitchInfo
{
protected:
	u8    m_bySrcMtType;  //电视墙源通道成员类型,参见mcuconst.h中电视墙成员类型定义
	u8    m_bySchemeIdx;  // 预案索引号
	u8    m_byReserved[3];
public:
    TTWSwitchInfo()
	{
		memset( this, 0x0, sizeof(TTWSwitchInfo) );
	}

	void  SetMemberType(u8   bySrcMtType ){ m_bySrcMtType = bySrcMtType; } 
    u8    GetMemberType( void ) const { return m_bySrcMtType; }

	void  SetSchemeIdx(u8   bySchemeIdx ){ m_bySchemeIdx = bySchemeIdx; } 
    u8    GetSchemeIdx( void ) const { return m_bySchemeIdx; }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//定义HDU交换结构
typedef TTWSwitchInfo THduSwitchInfo;   //4.6.1 新加  jlb

//设置hdu音量结构体  范围 0 -- 31
struct THduVolumeInfo:public TEqp
{
protected:
	u8  m_byChnlIdx;    // 通道索引号
	u8  m_byVolume;     // 音量大小
	u8  m_byIsMute;  // 是否静音  
	u8  m_byReserved[5];

public:
    THduVolumeInfo()
	{
        memset(this, 0x0, sizeof(THduVolumeInfo));
		m_byVolume = HDU_VOLUME_DEFAULT;
	}

	u8   GetChnlIdx( void ){ return m_byChnlIdx; }
	void SetChnlIdx( u8 byChnlIdx ){ m_byChnlIdx = byChnlIdx; }

	u8   GetVolume( void ){ return m_byVolume; }
	void SetVolume( u8 byVolume ){ m_byVolume = byVolume; }

	BOOL32   GetIsMute( void ){ return m_byIsMute; }
	void SetIsMute( BOOL32 byIsMute ){ m_byIsMute = GETBBYTE(byIsMute); }

}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//定义最大不对称结构
struct TMaxSkew
{
	u8    byChan1;	//信道1：MODE_VIDEO, MODE_AUDIO
	u8    byChan2;	//信道2：MODE_VIDEO, MODE_AUDIO
protected:
	u16 	wMaxSkew;	//最大不对称值：信道2比信道1的延迟处理量，单位（ms）

public:
	u16  GetMaxSkew( void ) const;//得到最大不对称值
	void SetMaxSkew( u16  wNewMaxSkew );//设置最大不对称值
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//外设注册请求消息类
struct TPeriEqpRegReq : public TEqp
{
protected:
	u32   		m_dwIpAddr;		//外设IP地址
	u16 		m_wStartPort;	//外设起始接收端口
	u8  		m_byChannlNum;	//外设接收信道数
	s8          m_achAlias[MAXLEN_EQP_ALIAS];
    //4.0R3扩展字段
    u16         m_wVersion;     //版本信息
    //4.5高清扩展字段
    BOOL        m_bHDEqp;       //是否高清外设

public:
    TPeriEqpRegReq(void) { memset(this, 0, sizeof(TPeriEqpRegReq)); }
    //设置外设IP地址
    //输入：IP地址(网络序)
	void SetPeriEqpIpAddr( const u32    &dwIpAddr )	{ m_dwIpAddr = dwIpAddr; }
    //获得外设IP地址
    //返回值：IP地址(网络序)
	u32    GetPeriEqpIpAddr() const	{ return m_dwIpAddr; }
	//设置外设接收起始端口
	void SetStartPort( const u16  & wStartPort )	{ m_wStartPort = htons(wStartPort); }
	//获得外设接收起始端口
	u16  GetStartPort() const	{ return ntohs( m_wStartPort ); }
	//设置外设接收信道数目
	void SetChnnlNum( const u8   & byChannlNum )	{ m_byChannlNum = byChannlNum; }
	//获得外设接收信道数目
	u8   GetChnnlNum() const	{ return m_byChannlNum; }

	void SetEqpAlias(char* szAlias)
	{
		strncpy( m_achAlias ,szAlias ,sizeof(m_achAlias) );
		m_achAlias[MAXLEN_EQP_ALIAS-1] ='\0';
	}

	LPCSTR GetEqpAlias()
	{
		return m_achAlias;
	}

    void SetVersion(u16 wVersion)
    {
        m_wVersion = htons(wVersion);
    }
    u16 GetVersion() const
    {
        return ntohs(m_wVersion);
    }
    void SetHDEqp(BOOL bHD)
    {
        m_bHDEqp = bHD;
    }

    BOOL IsHDEqp() const
    {
        return m_bHDEqp;
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//定义外设登记成功信息结构
struct TPeriEqpRegAck
{
protected:
	u32   		m_dwIpAddr;			//MCU接收地址
	u16 		m_wStartPort;		//MCU接收起始端口号
    u32         m_dwAnotherMpcIp;   //主备时：另外一块mpc板地址（用来对外设配置的备板mpc地址进行校验）
	u32         m_dwMsSSrc;         //主备时：用于标注一次系统运行，只要该值变化就说明发生过主备同时重启

public:
	//得到上级MCU交换接收数据IP地址
    u32    GetMcuIpAddr( void ) const { return ntohl(m_dwIpAddr); }

	//设置上级MCU交换接收数据IP地址
    void SetMcuIpAddr( u32    dwIpAddr ) { m_dwIpAddr = htonl(dwIpAddr); }

	//得到上级MCU交换接收数据端口号
    u16  GetMcuStartPort( void ) const { return ntohs(m_wStartPort); }

    //设置上级MCU交换接收数据端口号
    void SetMcuStartPort( u16  wPort ) { m_wStartPort = htons(wPort); }

    //另外一块mpc板地址
    u32  GetAnotherMpcIp( void ) const { return ntohl(m_dwAnotherMpcIp); }
    void SetAnotherMpcIp( u32 dwIpAddr ) { m_dwAnotherMpcIp = htonl(dwIpAddr); }

	void SetMSSsrc(u32 dwSSrc)
    {
        m_dwMsSSrc = htonl(dwSSrc);
    }
    u32 GetMSSsrc(void) const
    {
        return ntohl(m_dwMsSSrc);
    }

}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//会议控制台注册信息(len:77)
struct TMcsRegInfo
{
public:
	u32   		m_dwMcsIpAddr;	      //会议控制台的Ip地址（网络序）
	u8  		m_byVideoChnNum;	  //通道数目
	u16 		m_wStartPort;		  //视频通道的起始端口号（网络序）
	s8          m_achUser[MAXLEN_PWD];//用户名
	s8          m_achPwd[MAXLEN_PWD]; //用户密码
	u32   		m_dwMcsSSRC;	      //会议控制台的连接随机值，（网络序）
	                                  //应保障同一mcs连接同一mcu的主备mpc采用同一值，
	                                  //      不同mcs连接同一mcu采用不同值
    u16         m_wMcuMcsVer;         //mcu与mcs会话版本
public:
	TMcsRegInfo( void )
    { 
        memset( this, 0, sizeof(TMcsRegInfo) );
        SetMcuMcsVer();
    }
    void  SetMcsIpAddr(u32 dwMcsIpAddr){ m_dwMcsIpAddr = htonl(dwMcsIpAddr);}
    u32   GetMcsIpAddr( void ) const { return ntohl(m_dwMcsIpAddr); }
    void  SetVideoChnNum(u8 byVideoChnNum){ m_byVideoChnNum = byVideoChnNum;}
    u8    GetVideoChnNum( void ) const { return m_byVideoChnNum; }
    void  SetStartPort(u16 wStartPort){ m_wStartPort = htons(wStartPort);}
    u16   GetStartPort( void ) const { return ntohs(m_wStartPort); }
    void  SetMcsSSRC(u32 dwMcsSSRC){ m_dwMcsSSRC = htonl(dwMcsSSRC);} 
    u32   GetMcsSSRC( void ) const { return ntohl(m_dwMcsSSRC); }
    void  SetMcuMcsVer(void) { m_wMcuMcsVer = htons(MCUMCS_VER); }
    u16   GetMcuMcsVer(void) const { return ntohs(m_wMcuMcsVer); }
    void  SetUser( LPCSTR lpszUser )
	{
		memset(m_achUser, 0, sizeof(m_achUser));
		if (NULL != lpszUser)
		{
			strncpy(m_achUser, lpszUser, sizeof(m_achUser));
			m_achUser[sizeof(m_achUser)-1] = '\0';
		}
	}
	LPCSTR GetUser( void ) const{ return m_achUser; }
	BOOL IsEqualUser( LPCSTR lpszUser ) const
	{
		s8 achBuf[MAXLEN_PWD+1] = {0};
		strncpy( achBuf, lpszUser, sizeof( achBuf ) );
		achBuf[sizeof(achBuf)-1] = '\0';
		
		if(0 == strncmp(achBuf, lpszUser, MAXLEN_PWD))
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	void SetPwd( LPCSTR lpszPwd )
	{
		memset(m_achPwd, 0, sizeof(m_achPwd));
		if (NULL != lpszPwd)
		{
			strncpy(m_achPwd, lpszPwd, sizeof(m_achPwd));
			m_achPwd[sizeof(m_achPwd)-1] = '\0';
            // guzh [10/11/2007] 简单加密。在GetPwd之前要手动解密
            EncPwd();
		}
	}

	LPCSTR GetPwd( void ) const{ return m_achPwd; }
    
    // guzh [10/11/2007] 
    /*
	BOOL IsEqualPwd( LPCSTR lpszPwd ) const
	{
		s8 achBuf[MAXLEN_PWD+1] = {0};
		strncpy( achBuf, lpszPwd, sizeof( achBuf ) );
		achBuf[sizeof(achBuf)-1] = '\0';
		
		if(0 == strncmp(achBuf, lpszPwd, MAXLEN_PWD))
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
    */
	
	BOOL operator ==( TMcsRegInfo &tObj ) const
	{
		if (tObj.m_dwMcsIpAddr == m_dwMcsIpAddr && 
			tObj.m_dwMcsSSRC == m_dwMcsSSRC && 
			tObj.m_byVideoChnNum == m_byVideoChnNum && 
			IsEqualUser(tObj.m_achUser) && 
			/*IsEqualPwd(tObj.m_achPwd)&&*/ 
            tObj.m_wMcuMcsVer == m_wMcuMcsVer)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
        
    void DecPwd()
    {
        EncPwd();
    }
private:
    void EncPwd()
    {
        for (u8 byLoop=0; byLoop<strlen(m_achPwd); byLoop++)
        {
            m_achPwd[byLoop] ^= 0xa7;
        }
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//会议控制台注册回应(len:157)
struct TMcsRegRsp
{
protected:
    TMcu                m_tMcu;             // MCU 结构
    TMtAlias            m_tMcuAlias;        // MCU 别名
    u32                 m_dwRemoteMpcIp;    // 主备时对端的IP
    u8                  m_byLocalActive;    // 当前本MPC是否为主用板
    u8                  m_byUsrGrpId;       // 登陆用户的组ID
    u8                  m_byMcuOsType;      // MCU的操作系统类型
	u32					m_dwSysSSrc;		// 主备标识
public:
    void   SetMcu(u8 byMcuType, u8 byMcuId)
    {
        m_tMcu.SetMcu(byMcuId);
        m_tMcu.SetMcuType(byMcuType);
    }
    TMcu   GetMcu() const
    {
        return m_tMcu;
    }
    void   SetMcuAlias(const TMtAlias &tAlias)
    {
        m_tMcuAlias = tAlias;
    }
    TMtAlias GetMcuAlias() const
    {
        return m_tMcuAlias;
    }
    void   SetRemoteMpcIp(u32 dwIp)
    {
        m_dwRemoteMpcIp = htonl(dwIp);
    }
    u32    GetRemoteMpcIp() const
    {
        return ntohl(m_dwRemoteMpcIp);
    }
    void   SetLocalActive(BOOL32 bActive)
    {
        m_byLocalActive = GETBBYTE(bActive);
    }
    BOOL32 IsLocalActive() const
    {
        return ISTRUE(m_byLocalActive);
    }
    void   SetUsrGrpId(u8 byGrpId)
    {
        m_byUsrGrpId = byGrpId;
    }
    u8     GetUsrGrpId() const
    {
        return m_byUsrGrpId;
    }
    void   SetMcuOsType(u8 byOsType)
    {
        m_byMcuOsType = byOsType;
    }
    u8     GetMcuOsType() const
    {
        return m_byMcuOsType;
    }
	void   SetSysSSrc(u32 dwSysSSrc)
	{
		m_dwSysSSrc = htonl(dwSysSSrc);
	}
	u32    GetSysSSrc() const
	{
		return ntohl(m_dwSysSSrc);
	}

    void Print() const
    {
        OspPrintf(TRUE, FALSE, "Mcu: (%d, %d)\n", m_tMcu.GetMcuId(), m_tMcu.GetMcuType());
        OspPrintf(TRUE, FALSE, "Alias: %s, 0x%x\n", m_tMcuAlias.m_achAlias, m_tMcuAlias.m_tTransportAddr.GetIpAddr());
        OspPrintf(TRUE, FALSE, "Remote MpcIP: 0x%x\n", GetRemoteMpcIp());
        OspPrintf(TRUE, FALSE, "Local Active: %d\n", IsLocalActive());
        OspPrintf(TRUE, FALSE, "User Group Id: %d\n", GetUsrGrpId());
        OspPrintf(TRUE, FALSE, "OS Type: %d\n", GetMcuOsType());
		OspPrintf(TRUE, FALSE, "Local SSRC: %d\n", GetSysSSrc());
    }
    
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//会议表信息
struct TConfNameInfo
{
	CConfId		m_cConfId;          //会议号
	char		achConfName[MAXLEN_CONFNAME];   //会议名
public:
	TConfNameInfo( void )
	{
		m_cConfId.SetNull();
		memset( achConfName, 0, sizeof( achConfName ) );
	};
	void   SetConfName( LPCSTR lpszConfName )
	{
		if( lpszConfName != NULL )
		{
			strncpy( achConfName, lpszConfName, MAXLEN_CONFNAME );
		    achConfName[MAXLEN_CONFNAME - 1] = '\0';
		}
		else
		{
			memset(achConfName,0,sizeof(achConfName));
		}
	}
	LPCSTR GetConfName( void ) const { return achConfName; }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;



//定义交换通道结构 SrcIp->DisIp->RcvIp->DstIp, size=34
struct TSwitchChannel
{
    TSwitchChannel()
    {
        memset(this, 0, sizeof(TSwitchChannel));
    }
protected:
	TMt  m_tSrcMt;         //交换源终端
	u32  m_dwSrcIp;        //数据源Ip地址
	u32  m_dwDisIp;        //数据分发Ip地址
	u32  m_dwRcvIP;        //本地接收的IP地址(网络序),可以是组播(或广播)地址
	u16  m_wRcvPort;       //本地接收的端口 (机器序)
	u32  m_dwRcvBindIP;    //本地接收bind IP地址(网络序),本地地址
	u32  m_dwDstIP;        //将要发送的目标IP地址(网络序),可以是组播(或广播)地址
	u16  m_wDstPort;       //将要发送的目标端口 (机器序)
	u32  m_dwSndBindIP;    //发送目标接口IP地址.(网络序),本地地址

public:
	void SetSrcMt( TMt tMt ){ m_tSrcMt = tMt; }
	TMt  GetSrcMt( void ){ return m_tSrcMt; }
    void SetSrcIp(u32    dwSrcIp){ m_dwSrcIp = htonl(dwSrcIp);} 
    u32  GetSrcIp( void ) const { return ntohl(m_dwSrcIp); }
    void SetDisIp(u32    dwDisIp){ m_dwDisIp = htonl(dwDisIp);} 
    u32  GetDisIp( void ) const { return ntohl(m_dwDisIp); }
    void SetRcvIP(u32    dwRcvIP){ m_dwRcvIP = htonl(dwRcvIP);} 
    u32  GetRcvIP( void ) const { return ntohl(m_dwRcvIP); }
    void SetRcvPort(u16  wRcvPort){ m_wRcvPort = htons(wRcvPort);} 
    u16  GetRcvPort( void ) const { return ntohs(m_wRcvPort); }
    void SetRcvBindIP(u32    dwRcvBindIP){ m_dwRcvBindIP = htonl(dwRcvBindIP);} 
    u32  GetRcvBindIP( void ) const { return ntohl(m_dwRcvBindIP); }
    void SetDstIP(u32    dwDstIP){ m_dwDstIP = htonl(dwDstIP);} 
    u32  GetDstIP( void ) const { return ntohl(m_dwDstIP); }
    void SetDstPort(u16  wDstPort){ m_wDstPort = htons(wDstPort);} 
    u16  GetDstPort( void ) const { return ntohs(m_wDstPort); }
    void SetSndBindIP(u32    dwSndBindIP){ m_dwSndBindIP = htonl(dwSndBindIP);} 
    u32  GetSndBindIP( void ) const { return ntohl(m_dwSndBindIP); }
	BOOL IsNull( void ) const { return m_dwDstIP == 0 ? TRUE : FALSE; }
    BOOL IsSrcNull( void ) const { return m_dwSrcIp == 0 ? TRUE : FALSE; }
    BOOL IsRcvNull( void ) const { return m_dwRcvIP == 0 ? TRUE : FALSE; }
	void SetNull( ){ memset( this, 0, sizeof(TSwitchChannel) ); }
	BOOL operator ==( TSwitchChannel &tObj ) const
	{
		if( tObj.GetDstIP() == GetDstIP() && tObj.GetDstPort() == GetDstPort() )
		{
			return TRUE;
		}
        else
		{
			return FALSE;
		}
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//Mp信息
struct TMp
{
protected:
    u8   m_byMcuId;                   //MCU号
    u8   m_byMpId;                    //本Mp编号
    u8   m_byAttachMode;              //MP的附属方式
    u32  m_dwIpAddr;                  //Ip地址
    u8   m_byDoubleLink;              //双链
    u8   m_byIsMulticast;             //是否组播 0: 不组播 1：组播
    s8   m_abyMpAlias[MAXLEN_ALIAS];  //Mp别名	
	//4.0R4扩展字段
    u16  m_wVersion;			     //版本信息	ZGC	2007-10-10
public:
    void SetMcuId(u8 byMcuId) { m_byMcuId = byMcuId; }
    u8   GetMcuId(void) const { return m_byMcuId; }
    void SetMpId(u8 byMpId){ m_byMpId = byMpId; }
    u8   GetMpId(void) const { return m_byMpId; }
    void SetAttachMode(u8 byAttachMode) { m_byAttachMode = byAttachMode; }
    u8   GetAttachMode(void) const { return m_byAttachMode; }
    void SetIpAddr(u32 dwIP){ m_dwIpAddr = htonl(dwIP); }
    u32  GetIpAddr(void) { return ntohl(m_dwIpAddr); }
    void SetDoubleLink(u8 byDoubleLink) { m_byDoubleLink = byDoubleLink; }
    u8   GetDoubleLink(void) const { return m_byDoubleLink; }
    void SetMulticast(u8 byIsMulticast) { m_byIsMulticast = byIsMulticast; }
    u8   GetMulticast(void) const { return m_byIsMulticast; }
    const s8 * GetAlias(void) const { return m_abyMpAlias; }
    void SetAlias(s8 * pchAlias)
    {
        if (pchAlias != NULL)
        {
            strncpy(m_abyMpAlias, pchAlias, sizeof(m_abyMpAlias));
            m_abyMpAlias[sizeof(m_abyMpAlias) - 1] = '\0';
        }
        else
        {
            memset(m_abyMpAlias, 0, sizeof(m_abyMpAlias));
        }
    }
	u16 GetVersion(void) const { return ntohs(m_wVersion); }
	void SetVersion(u16 wVersion) { m_wVersion = htons(wVersion); }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//MtAdp注册信息
struct TMtAdpReg
{
protected:    
	u8      m_byDriId;         //本MtAdp编号
	u8      m_byAttachMode;    //MtAdp的附属方式
	u8      m_byProtocolType;  //适配的协议类型//H323、H320、SIP
	u8      m_byMaxMtNum;      //适配的支持最大终端数
	u32     m_dwIpAddr;        //Ip地址，网络序
	s8      m_achMtAdpAlias[MAXLEN_ALIAS];  //MtAdp别名
    u16     m_wQ931Port;
    u16     m_wRasPort;
	//4.0R4扩展字段
    u16     m_wVersion;     //版本信息	ZGC	2007-09-28
    //4.0R5
    u8      m_byIsSupportHD;  //是否支持高清接入

public:
	TMtAdpReg()
	{
		memset(this, 0, sizeof(TMtAdpReg)); 
		m_byProtocolType = PROTOCOL_TYPE_H323;
		m_byMaxMtNum = MAXNUM_DRI_MT;
	}
	
	VOID	SetDriId(u8 byDriId){ m_byDriId = byDriId;}
	u8  	GetDriId() const { return m_byDriId;}
	VOID	SetAttachMode(u8 byAttachMode){ m_byAttachMode = byAttachMode;} 
	u8  	GetAttachMode( void ) const { return m_byAttachMode; }
	VOID	SetIpAddr(u32 dwIp){m_dwIpAddr = htonl(dwIp);}
	u32   	GetIpAddr() const { return ntohl(m_dwIpAddr);}
	VOID	SetProtocolType(u8 byProtocolType){ m_byProtocolType = byProtocolType;}
	u8  	GetProtocolType() const { return m_byProtocolType;}
	VOID	SetMaxMtNum(u8 byMaxMtNum){ m_byMaxMtNum = byMaxMtNum;}
	u8  	GetMaxMtNum() const { return m_byMaxMtNum;}
    void    SetQ931Port(u16 wQ931Port){ m_wQ931Port = htons(wQ931Port);} 
    u16     GetQ931Port( void ) const { return ntohs(m_wQ931Port); }
    void    SetRasPort(u16 wRasPort){ m_wRasPort = htons(wRasPort);} 
    u16     GetRasPort( void ) const { return ntohs(m_wRasPort); }	

	VOID SetAlias(LPCSTR lpszAlias)
	{
		if(lpszAlias != NULL)
			strncpy(m_achMtAdpAlias, lpszAlias, MAXLEN_ALIAS - 1);
	}

	VOID GetAlias(s8 *pchBuf, u16  wBufLen)
	{
		if(pchBuf != NULL)
			strncpy(pchBuf, m_achMtAdpAlias, wBufLen);
	}

	u16 GetVersion(void) const { return ntohs(m_wVersion); }
	void SetVersion(u16 wVersion) { m_wVersion = htons(wVersion); }

    void SetSupportHD(BOOL bSupport = TRUE)
    {
        m_byIsSupportHD = bSupport ? 1 : 0;
    }

    BOOL IsSupportHD() const
    {
        return ISTRUE(m_byIsSupportHD);
    }

}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//MtAdp注册响应信息(len:148)
struct TMtAdpRegRsp 
{
protected:
	u32  m_dwVcIpAddr;                      //业务IP地址，网络序
	u32  m_dwGkIpAddr;                      //GK IP地址，网络序
	s8   m_achMcuAlias[MAXLEN_ALIAS];       //MCU别名
	u8   m_byMcuNetId;
	u16  m_wHeartBeatInterval;              //检测终端断链时间间隔(sec)
	u8   m_byHeartBeatFailTimes;            //终端断链次数
	u8	 m_byMtAdpMaster;					//是否为主适配 1:是, 0:不是
//	u16  m_wQ931Port;
//	u16  m_wRasPort;
	u16  m_wH225H245Port;                   //H225H245 的建链起始端口
	u16  m_wH225H245MtNum;                  //H225H245 的建链终端数
    u8   m_byGkCharge;                      //是否进行GK计费
	u8	 m_byMcuType;						//Mcu类型, zgc, 2007-04-03
    u8   m_byCascadeAliasType;              //级联时MCU在会议中别名的显示方式
    u8   m_byUseCallingMatch;               //呼叫遵循匹配约定

	u32  m_dwMsSSrc;                        //主备时：用于标注一次系统运行，只要该值变化就说明发生过主备同时重启
    s8   m_achMcuVersion[MAXLEN_ALIAS];     //MCU 版本号，用于初始化协议栈

public:
	TMtAdpRegRsp()
    {
        memset(this, 0, sizeof(TMtAdpRegRsp));
    }

	VOID	SetVcIp(u32    dwIp){m_dwVcIpAddr = htonl(dwIp);}
	u32   	GetVcIp() const {return ntohl(m_dwVcIpAddr);}

	VOID	SetGkIp(u32    dwIp){m_dwGkIpAddr = htonl(dwIp);}
	u32   	GetGkIp() const {return ntohl(m_dwGkIpAddr);}

	VOID	SetAlias(LPCSTR lpszAlias)
	{
		if(lpszAlias != NULL)
			strncpy(m_achMcuAlias, lpszAlias, MAXLEN_ALIAS - 1);
	}

	VOID	GetAlias(char *pchBuf, u16  wBufLen) const
	{
		if(pchBuf != NULL)
			strncpy(pchBuf, m_achMcuAlias, wBufLen);
	}

    // guzh [9/3/2007] MCU 版本号，填充H323Config
    VOID	SetMcuVersion(LPCSTR lpszAlias)
    {
        if(lpszAlias != NULL)
            strncpy(m_achMcuVersion, lpszAlias, MAXLEN_ALIAS - 1);
    }
    
    LPCSTR	GetMcuVersion() const
    {
        return m_achMcuVersion;
	}
	
    void   SetMcuNetId(u8 byMcuId)	{ m_byMcuNetId = byMcuId; }	
    u8     GetMcuNetId() const	{ return m_byMcuNetId; }    
	
	void   SetHeartBeatInterval( u16 wHeartBeatInterval ){ m_wHeartBeatInterval = htons(wHeartBeatInterval); } 
	u16     GetHeartBeatInterval( void ) const { return ntohs(m_wHeartBeatInterval); }
	void   SetHeartBeatFailTimes(u8 byHeartBeatFailTimes){ m_byHeartBeatFailTimes = byHeartBeatFailTimes; } 
	u8     GetHeartBeatFailTimes( void ) const { return m_byHeartBeatFailTimes; }
//	void   SetQ931Port(u16 wQ931Port){ m_wQ931Port = htons(wQ931Port);} 
//	u16    GetQ931Port( void ) const { return ntohs(m_wQ931Port); }
//	void   SetRasPort(u16 wRasPort){ m_wRasPort = htons(wRasPort);} 
//	u16    GetRasPort( void ) const { return ntohs(m_wRasPort); }
	void   SetH225H245Port(u16 wH225H245Port){ m_wH225H245Port = htons(wH225H245Port);} 
	u16    GetH225H245Port( void ) const { return ntohs(m_wH225H245Port); }
	void   SetH225H245MtNum(u16 wH225H245MtNum){ m_wH225H245MtNum = htons(wH225H245MtNum);} 
	u16    GetH225H245MtNum( void ) const { return ntohs(m_wH225H245MtNum); }
    void   SetMtAdpMaster( BOOL32 bMtAdpMaster ){ m_byMtAdpMaster = (bMtAdpMaster ? 1:0);}
    BOOL32 IsMtAdpMaster() const { return (1 == m_byMtAdpMaster) ? TRUE:FALSE;}
    void   SetIsGKCharge(BOOL32 bCharge) { m_byGkCharge = bCharge ? 1 : 0;    }
    BOOL32 GetIsGKCharge( void ) { return m_byGkCharge == 1 ? TRUE : FALSE;   }
	
	//Mcu类型, zgc, 2007-04-03
	void	SetMcuType( u8 byMcuType ) { m_byMcuType = byMcuType; }
	u8		GetMcuType( void ) { return m_byMcuType; }

    //MCU级联别名显示方式
    void    SetCasAliasType(u8 byType) { m_byCascadeAliasType = byType; }
    u8      GetCasAliasType() const {return m_byCascadeAliasType;}

    void    SetUseCallingMatch(u8 byUseMatch) { m_byUseCallingMatch = byUseMatch; }
    u8      GetUseCallingMatch( void ) const { return m_byUseCallingMatch;    }

	void SetMSSsrc(u32 dwSSrc)
    {
        m_dwMsSSrc = htonl(dwSSrc);
    }
    u32 GetMSSsrc(void) const
    {
        return ntohl(m_dwMsSSrc);
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//协议适配板配置信息(h323)
struct TMtAdpCfg 
{
protected:
    u16 m_wPartlistRefreshTime;             //级联时终端列表刷新时间间隔(s)
    u16 m_wAudInfoRefreshTime;              //级联时音频信息刷新时间间隔(s)
    u16 m_wVidInfoRefreshTime;              //级联时视频信息刷新时间间隔(s)

public:
    TMtAdpCfg(void) 
    {             
        SetPartListRefreshTime(PARTLIST_REFRESHTIME);  
        SetAudInfoRefreshTime(AUDINFO_REFRESHTIME);
        SetVidInfoRefreshTime(VIDINFO_REFRESHTIME);
    }    
    
    void    SetPartListRefreshTime(u16 wTime) { m_wPartlistRefreshTime = htons(wTime); }
    u16     GetPartListRefreshTime(void) { return ntohs(m_wPartlistRefreshTime); }
    void    SetAudInfoRefreshTime(u16 wTime) { m_wAudInfoRefreshTime = htons(wTime); }
    u16     GetAudInfoRefreshTime(void) { return ntohs(m_wAudInfoRefreshTime); }
    void    SetVidInfoRefreshTime(u16 wTime) { m_wVidInfoRefreshTime = htons(wTime); }
    u16     GetVidInfoRefreshTime(void) { return ntohs(m_wVidInfoRefreshTime); }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;


//////////////////////////////////////////////////
//      级联消息用到的结构
//////////////////////////////////////////////////

struct TMcuMcuReq
{
	s8 m_szUserName[MAXLEN_PWD];
	s8 m_szUserPwd[MAXLEN_PWD];
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TMtViewPos
{
    s32  m_nViewID;
    u8   m_bySubframeIndex;    
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TMtVideoInfo
{
    s32			m_nViewCount;                   
    TMtViewPos  m_atViewPos[MAXNUM_VIEWINCONF]; //终端在哪些视图里
    s32			m_nOutputLID;                   //终端接收哪个视图
    s32			m_nOutVideoSchemeID;           //输入到终端的视频方案ID(当一个会议支持两种会议格式)                        
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TMcuMcuMtInfo
{
    TMcuMcuMtInfo()
    {
        memset(this, 0, sizeof(TMcuMcuMtInfo));
    }
    TMt         m_tMt;
    s8 			m_szMtName[VALIDLEN_ALIAS];     
    u32			m_dwMtIp; 
    s8          m_szMtDesc[VALIDLEN_ALIAS];
    u8			m_byMtType;          // 上级、下级Mcu 或Mt 
    u8          m_byManuId;          //厂商编号,参见厂商编号定义
	u8			m_byVideoIn;       
    u8			m_byVideoOut;      
    u8			m_byVideo2In;     
    u8			m_byVideo2Out;     
    u8			m_byAudioIn;       
    u8			m_byAudioOut;      
    u8		    m_byIsDataMeeting;    
    u8		    m_byIsVideoMuteIn;    
    u8			m_byIsVideoMuteOut;   
    u8			m_byIsAudioMuteIn;    
    u8			m_byIsAudioMuteOut;   
    u8          m_byIsConnected;     
    u8			m_byIsFECCEnable;     
    u8          m_byProtocolType;
    TMtVideoInfo m_tPartVideoInfo;   
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TCSchemeInfo
{
    s32		m_nVideoSchemeID;   //视频输出方案ID
    u32		m_dwMaxRate;        //max rate (kbps)
    u32		m_dwMinRate;        //min rate (kbps)
    BOOL	m_bCanUpdateRate;   // whether or not enable update rate
    s32     m_nFrameRate;       // frame rate (30、25)
    u8		m_byMediaType;      //
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TCViewInfo
{
    s32				m_nViewId;							//会议视图 ID
    u8              m_byRes;							//会议视图图像的分辨率
    u8              m_byCurGeoIndex;					//会议视图当前正在使用(输出)的几何布局,以在几何布局列表中的索引来标明
    u8              m_byGeoCount;						//几何布局的数目
    u8              m_abyGeoInfo[MAXNUM_GEOINVIEW];		//几何布局列表
    u8              m_byMtCount;						//会议视图的视频源的数目
    TMt             m_atMts[MAXNUM_SUBFRAMEINGEO];		//视频源列表
    u8              m_byVSchemeCount;					//可选的视频输出方案数目
    TCSchemeInfo    m_atVSchemes[MAXNUM_VSCHEMEINVIEW]; //视频输出方案列表

    // guzh [7/19/2007]
    u8              m_byAutoSwitchStatus;               //自动轮询回传
    u8              m_byDynamic;
    s32             m_nAutoSwitchTime;                  //轮询回传时间间隔
    s32             m_nVideoRole;
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TCConfViewInfo
{
	u8          m_byDefViewIndex;			//默认会议视图索引
    u8          m_byViewCount;					//会议视图的数目
    TCViewInfo	m_atViewInfo[MAXNUM_VIEWINCONF];//会议视图列表
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//混音器信息，可能会有多个speaker，这里只是制定一个
struct TCMixerInfo
{
    s32    m_nMixerID;					//mixer ID
    TMt    m_tSpeaker;					//speaker Pid
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//MCU的混音器的信息
struct TCConfAudioInfo
{
    u8				m_byMixerCount;						//混音器数目
    u8				m_byDefMixerIndex;					//缺省混音器，以索引表示,它也是当前正在播音的混音器
    TCMixerInfo     m_tMixerList[MAXNUM_MIXERINCONF];	//混音器列表
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TCConfViewChangeNtf
{
	s32  m_nViewID;
    u8   m_bySubframeCount;    
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TMtMediaChanStatus
{
	TMt		m_tMt;
    u8		m_byMediaMode;        //媒体模式（MODE_VIDEO,MODE_AUDIO）
    u8		m_byIsDirectionIn;      //媒体流流动方向
    BOOL	m_bMute;              //true:切断该方向的流动，false:打开该方向的媒体流动
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TCAutoSwitchReq
{
    TCAutoSwitchReq(){ memset(this, 0, sizeof(TCAutoSwitchReq)); }

    s32     m_nSwitchLayerId;              
    s32     m_nSwitchSpaceTime;     //轮训时间间隔
    s32     m_nAutoSwitchLevel;     //轮询级别,详细含义未知,1：开启，0：停止
    BOOL32  m_bSwitchOn;            //轮询启停
    
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TSetInParam
{
	TMt m_tMt;
	s32 m_nViewId;
	u8  m_bySubFrameIndex;
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TCConfViewOutInfo
{    
	TMt m_tMt;
    s32 m_nOutViewID;         
    s32 m_nOutVideoSchemeID;  
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TSetOutParam 
{
    s32					m_nMtCount;           
    TCConfViewOutInfo   m_atConfViewOutInfo[MAXNUM_CONF_MT];
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;


//////////////////////////////////////////////////////////////////////////
//						配置界面化所用结构
//////////////////////////////////////////////////////////////////////////

//mcu IP地址、子网掩码、网关IP、层号、槽号
struct TMcuEqpCfg
{
protected:
    u32 m_dwMcuIpAddr;          //mcu Ip地址
    u32 m_dwMcuSubnetMask;      //mcu 子网掩码
    u32 m_dwGWIpAddr;           //网关 Ip地址
    u8	m_byLayer;              //层号
    u8  m_bySlotId;             //槽id
    u8  m_byInterface;          //前后网口
	u8  m_byRemain;				// save
public:
    TMcuEqpCfg(void) { memset(this, 0, sizeof(TMcuEqpCfg)); }
    
    void    SetMcuIpAddr(u32 dwIpAddr) { m_dwMcuIpAddr = htonl(dwIpAddr); }     //host order
    u32     GetMcuIpAddr(void)  { return ntohl(m_dwMcuIpAddr); }
    void    SetMcuSubNetMask(u32 dwMask) { m_dwMcuSubnetMask = htonl(dwMask); }
    u32     GetMcuSubNetMask(void) { return ntohl(m_dwMcuSubnetMask); }
    void    SetGWIpAddr(u32 dwGWIpAddr) { m_dwGWIpAddr = htonl(dwGWIpAddr); }   //host order
    u32     GetGWIpAddr(void) { return ntohl(m_dwGWIpAddr); }
    void    SetLayer(u8 byLayer) { m_byLayer = byLayer; }
    u8      GetLayer(void) { return m_byLayer; }   
    void    SetSlot(u8 bySlotId) { m_bySlotId = bySlotId; }
    u8      GetSlot(void) { return m_bySlotId; }   
	void    SetInterface(u8 byInterface){ m_byInterface = byInterface;}
	u8      GetInterface(void) const { return m_byInterface;}
	
    void    Print(void)
    {
        OspPrintf(TRUE, FALSE, "McuIpAddr:0x%x, McuSubnetMask:0x%x, GWIpAddr:0x%x, Layer:%d, SlotId:%d, Interface: %d\n",
                  GetMcuIpAddr(), GetMcuSubNetMask(), GetGWIpAddr(), GetLayer(), GetSlot(), GetInterface());
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//画面合成配置信息
struct TVmpStyleCfgInfo
{    
protected:
    u8  m_bySchemeId;                   //方案id，1－5
	u8	m_byRimEnabled;					//是否使用边框: 0-不使用(默认) 1-使用;
										//本字段目前只对方案0有效, 其他方案暂不涉及本字段的设置和判断
	u8	m_byReserved1;					//保留字段1
	u8	m_byReserved2;					//保留字段2
    u32 m_dwBackgroundColor;            //图像背景色
    u32 m_dwFrameColor;                 //图像边框色
    u32 m_dwSpeakerFrameColor;          //发言人边框色
    u32 m_dwChairFrameColor;            //主席边框色 
	u8  m_byFontType;                   // 合成主题字体
	u8  m_byFontSize;					// 合成主题字号
	u8  m_byAlignment;                  // 对齐方式
	u32  m_dwTextColor;                  // 合成主题文字颜色
	u32  m_dwTopicBkColor;               // 合成主题背景色
	u32  m_dwDiaphaneity;                // 合成主题透明度
    s8  m_achSchemeAlias[MAX_VMPSTYLE_ALIASLEN];  // 画面合成方案别名

public:
    TVmpStyleCfgInfo(void) { Clear();   }

	void	Clear(void)  { memset(this, 0, sizeof(TVmpStyleCfgInfo)); }
	void	SetNull(void) { Clear(); }
	BOOL32  IsNull(void) 
    { 
        TVmpStyleCfgInfo tInfo;
        return (0 == memcmp(this, &tInfo, sizeof(TVmpStyleCfgInfo)));
    }
    void    SetSchemeId(u8 bySchemeId) { m_bySchemeId = bySchemeId; }
    u8      GetSchemeId(void) { return m_bySchemeId; }    
    void    SetBackgroundColor(u32 dwColor) { m_dwBackgroundColor = htonl(dwColor); }
    u32     GetBackgroundColor(void) { return ntohl(m_dwBackgroundColor); }
    void    SetFrameColor(u32 dwColor) { m_dwFrameColor = htonl(dwColor); }
    u32     GetFrameColor(void) { return ntohl(m_dwFrameColor); }
    void    SetSpeakerFrameColor(u32 dwColor) { m_dwSpeakerFrameColor = htonl(dwColor); }
    u32     GetSpeakerFrameColor(void) { return ntohl(m_dwSpeakerFrameColor); }
    void    SetChairFrameColor(u32 dwColor) { m_dwChairFrameColor = htonl(dwColor); }
    u32     GetChairFrameColor(void) { return ntohl(m_dwChairFrameColor); }
	void	SetIsRimEnabled(BOOL32 bEnabled){ m_byRimEnabled = GETBBYTE(bEnabled); }
	BOOL32	GetIsRimEnabled(void) const { return m_byRimEnabled == 1 ? TRUE : FALSE; }
	void    SetFontType(u8 byFontType) { m_byFontType = byFontType;}
	u8      GetFontType(void) { return m_byFontType;}
	void    SetFontSize(u8 byFontSize ) { m_byFontSize = byFontSize;}
	u8      GetFontSize(void) { return m_byFontSize;}
	void    SetAlignment(u8 byValue ) { m_byAlignment = byValue;}
	u8      GetAlignment(void) { return m_byAlignment;}
	void    SetTextColor(u32 dwTextColor ) { m_dwTextColor = htonl(dwTextColor);}
	u32     GetTextColor(void) { return ntohl(m_dwTextColor);}
	void    SetTopicBkColor(u32 dwBkColor) { m_dwTopicBkColor = htonl(dwBkColor);}
	u32     GetTopicBkColor(void) { return ntohl(m_dwTopicBkColor);}
	void    SetDiaphaneity(u32 dwDiaphaneity ) { m_dwDiaphaneity = htonl(dwDiaphaneity); }
	u32     GetDiaphaneity(void) { return ntohl(m_dwDiaphaneity);}

    void    SetSchemeAlias(s8* pchSchemeAlias)
    {
        memcpy(m_achSchemeAlias, pchSchemeAlias, sizeof(m_achSchemeAlias));
        m_achSchemeAlias[MAX_VMPSTYLE_ALIASLEN-1] = '\0';
    }
    
    void    GetSchemeAlias(s8* pchSchemeAlias, u8 byBufferLen)
    {
        u8 byAliasLen = (byBufferLen < sizeof(m_achSchemeAlias) ) ? byBufferLen : sizeof(m_achSchemeAlias);
        memcpy(pchSchemeAlias, m_achSchemeAlias, byAliasLen);
    }
    
    void    ResetDefaultColor(void)
    {
        SetBackgroundColor(VMPSTYLE_DEFCOLOR);
        SetSpeakerFrameColor(VMPSTYLE_DEFCOLOR);
        SetChairFrameColor(VMPSTYLE_DEFCOLOR);
        SetFrameColor(VMPSTYLE_DEFCOLOR);
		SetFontType(FONT_SONG);
		SetFontSize(FONT_SIZE_24);
		SetAlignment(MIDDLE_ALIGN);
		SetTextColor(DEFAULT_TEXT_COLOR);
		SetTopicBkColor(DEFAULT_BACKGROUND_COLOR);
		SetDiaphaneity(DEFAULT_DIAPHANEITY);
    }

	inline BOOL operator == (const TVmpStyleCfgInfo& tVmpStyle )
	{
		BOOL bRet = TRUE;
		if( this == &tVmpStyle )
		{
			return bRet;
		}
		
		if ( 0 != memcmp(this, &tVmpStyle, sizeof(TVmpStyleCfgInfo)) )
		{
			bRet = FALSE;
		}
		return bRet;
	}

    void    Print(void)
    {	
		OspPrintf(TRUE, FALSE, "VmpStyleInfo(SchemeId:%d)\n BackColor:0x%x, AudienceColor:0x%x, SpeakerColor:0x%x, ChairColor:0x%x, IsRimEnabled:%d\n",
			GetSchemeId(), GetBackgroundColor(), GetFrameColor(), GetSpeakerFrameColor(), GetChairFrameColor(), GetIsRimEnabled() );
		OspPrintf(TRUE, FALSE, "VmpStyleInfo: \n FontType:%d, FontSize:%d, TextColor:0x%x, BkColor:0x%x, Diaphaneity:0x%x\n",
			GetFontType(), GetFontSize(), GetTextColor(), GetTopicBkColor(), GetDiaphaneity() );
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;
//预方案中通道所需配置资源结构   jlb
struct THduChnlCfgInfo
{
protected:
	u8   m_byChnlIdx;               //通道索引号
	u8   m_byEqpId;					//设备ID
	u8   m_byChnlVolumn;            //通道音量
	BOOL m_bIsChnlBeQuiet;          //通道静音
	s8   m_achEqpAlias[MAXLEN_EQP_ALIAS];   //外设别名
public:
	THduChnlCfgInfo(){ SetNull(); }
    void SetNull(void)
	{
        memset( this, 0, sizeof(THduChnlCfgInfo) );
	    return;
	}

	u8   GetChnlIdx(void) const { return m_byChnlIdx; }
	void SetChnlIdx(u8 val) { m_byChnlIdx = val; }

	u8   GetEqpId(void) const { return m_byEqpId; }
	void SetEqpId(u8 val) { m_byEqpId = val; }

	u8   GetChnlVolumn(void) const { return m_byChnlVolumn; }
	void SetChnlVolumn(u8 val) { m_byChnlVolumn = val; }

	BOOL GetIsChnlBeQuiet(void) const { return m_bIsChnlBeQuiet; }
	void SetIsChnlBeQuiet(BOOL val) { m_bIsChnlBeQuiet = val; }

	void SetEqpAlias(LPCSTR pchEqpAlias)
    {
		//fixme
        memcpy(m_achEqpAlias, pchEqpAlias, MAXLEN_EQP_ALIAS);
        m_achEqpAlias[sizeof(m_achEqpAlias) - 1] = '\0';
    }
	
	LPCSTR GetEqpAlias(void){ return m_achEqpAlias; }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
; 

//HDU预设方案结构   jlb
struct THduStyleCfgInfo 
{
protected:
	u8   m_byStyleIdx;          //方案Id；

	u8   m_byTotalChnlNum;      //方案需要的通道数，即界面中可配置的最大通道数
                                //根据不同的方案可为1、2、4、…、56，最大56个
	THduChnlCfgInfo m_atHduChnlCfgTable[MAXNUM_HDUCFG_CHNLNUM];  //各通道需要的配置资源
	//m_bywidth * m_byHeight <= 56
	u8   m_byWidth;             //界面配置的宽度
	u8   m_byHeight;            //界面配置的高度
    u8   m_byVolumn;            //所有通道统一音量大小
	BOOL m_bIsBeQuiet;          //所有通道是否统一静音
	s8  m_achSchemeAlias[MAX_HDUSTYLE_ALIASLEN];   //预方案别名
	
public:
    THduStyleCfgInfo(void) { SetNull(); }
	void	SetNull(void)  { memset(this, 0, sizeof(THduStyleCfgInfo)); }
	BOOL32  IsNull(void) 
    { 
        THduStyleCfgInfo tInfo;
        return (0 == memcmp(this, &tInfo, sizeof(THduStyleCfgInfo)));
    }
    
	//patHduChnlCfgTable  为数组指针，元素个数为MAXNUM_HDUCFG_CHNLNUM
	void GetHduChnlCfgTable(THduChnlCfgInfo *patHduChnlCfgTable)
	{
		memcpy(patHduChnlCfgTable, m_atHduChnlCfgTable, MAXNUM_HDUCFG_CHNLNUM*sizeof(THduChnlCfgInfo));
        return;
	}
	//patHduChnlCfgTable  为数组指针，元素个数为MAXNUM_HDUCFG_CHNLNUM
	BOOL32 SetHduChnlCfgTable(THduChnlCfgInfo *patHduChnlCfgTable)
	{
		BOOL32 bRet = TRUE;
		if (NULL == patHduChnlCfgTable)
		{
			bRet = FALSE;
			OspPrintf(TRUE, FALSE, "[mcustruct.h]:SetHduChnlCfgTable()-->patHduChnlCfgTable is NULL\n");
		}

		memcpy(m_atHduChnlCfgTable, patHduChnlCfgTable, MAXNUM_HDUCFG_CHNLNUM*sizeof(THduChnlCfgInfo));
		return bRet;
	}

	u8   GetStyleIdx(void) const { return m_byStyleIdx; }
	void SetStyleIdx(u8 val) { m_byStyleIdx = val; }

	u8   GetTotalChnlNum(void) const { return m_byTotalChnlNum; }
	void SetTotalChnlNum(u8 val) { m_byTotalChnlNum = val; }

	u8   GetWidth(void) const { return m_byWidth; }
	void SetWidth(u8 val) { m_byWidth = val; }

	u8   GetHeight(void) const { return m_byHeight; }
	void SetHeight(u8 val) { m_byHeight = val; }

	u8   GetVolumn(void) const { return m_byVolumn; }
	void SetVolumn(u8 val) { m_byVolumn = val; }

	BOOL GetIsBeQuiet(void) const { return m_bIsBeQuiet; }
	void SetIsBeQuiet(BOOL val) { m_bIsBeQuiet = val; }

	void SetSchemeAlias(LPCSTR pchSchemeAlias)
    {
        memcpy(m_achSchemeAlias, pchSchemeAlias, sizeof(m_achSchemeAlias));
        m_achSchemeAlias[MAX_HDUSTYLE_ALIASLEN-1] = '\0';
    }
    
	LPCSTR GetSchemeAlias(void){ return m_achSchemeAlias; }

	inline BOOL operator == (const THduStyleCfgInfo& tHduStyle )
	{
		BOOL bRet = TRUE;
		if( this == &tHduStyle )
		{
			return bRet;
		}
		
		if ( 0 != memcmp(this, &tHduStyle, sizeof(THduStyleCfgInfo)) )
		{
			bRet = FALSE;
		}
		return bRet;
	}

    void Print(void)
	{
		OspPrintf(TRUE, FALSE, "[THduStyleCfgInfo]: StyleIdx:%d, TotalChnlNum:%d, Width:%d, Height:%d, Volumn:%d, IsBeQuiet:%d\n",
			      GetStyleIdx(), GetTotalChnlNum(), GetWidth(), GetHeight(), GetVolumn(), GetIsBeQuiet());
		OspPrintf(TRUE, FALSE, "[THduStyleCfgInfo]: Hdu Scheme Alias is:%s \n",m_achSchemeAlias);
	    
		OspPrintf(TRUE, FALSE, "[THduStyleCfgInfo]:\n");
		u16 wIndex;
		for ( wIndex=0; wIndex<GetTotalChnlNum(); wIndex++)
	    {
			OspPrintf(TRUE, FALSE, "[%d]:  ChnlIdx:%d, EqpId:%d, ChnlVolumn:%d, IsChnlBeQuiet:%d\n",
				       m_atHduChnlCfgTable[wIndex].GetChnlIdx(),
					   m_atHduChnlCfgTable[wIndex].GetEqpId(),
					   m_atHduChnlCfgTable[wIndex].GetChnlVolumn(),
    				   m_atHduChnlCfgTable[wIndex].GetIsChnlBeQuiet());
	    }

		return;
	}

}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// hdu批量轮询预案信息
struct THduPollSchemeInfo 
{
protected:
	u32  m_dwKeepTime;                       // 轮询周期
	u8   m_byCycles;                         // 轮询周期次数
	u8   m_byStatus;                         // 当前批量轮询状态
	u8   m_byReserved1;
    u8   m_byReserved2;
public:
	THduStyleCfgInfo m_tHduStyleCfgInfo;     // 批量预案预案版面信息

public:
	THduPollSchemeInfo()
	{
        SetNull();
	}
	void SetNull( void )
	{
		m_dwKeepTime = 0;
		m_byCycles = 0;
		m_byStatus = POLL_STATE_NONE;
		m_byReserved1 = 0;
		m_byReserved2 = 0;
		
		m_tHduStyleCfgInfo.SetNull();
	}
	u32   GetKeepTime( void )
	{
		return ntohl(m_dwKeepTime);
	}
	void SetKeepTime( u32 dwKeepTime )
	{
		m_dwKeepTime = htonl(dwKeepTime);
	}

	u8   GetCycles( void )
	{
		return m_byCycles;
	}
	void SetCycles( u8 byCycles )
	{
		m_byCycles = byCycles;
	}

	u8   GetStatus( void )
	{
		return m_byStatus;
	}
	void SetStatus( u8 byStatus )
	{
		m_byStatus = byStatus;
	}

}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// 批量轮询前，预案中被占用通道信息
struct THduChnlInfoInUse
{
protected:
	u8    m_byConfIdx;       // 会议索引号
	u8    m_byEqpId;         // 外设ID
	u8    m_byChlIdx;        // 通道索引号
	u8    m_byResverd;       

public:
	THduChnlInfoInUse()
	{
		memset(this, 0x0, sizeof(THduChnlInfoInUse));
	}

	u8    GetConfIdx( void ){ return m_byConfIdx; }
	void  SetConfIdx( u8 byConfIdx ){ m_byConfIdx = byConfIdx; }

	u8    GetEqpId( void ){ return m_byEqpId; }
	void  SetEqpId( u8 byEqpId ){ m_byEqpId = byEqpId; }

	u8    GetChlIdx( void ){ return m_byChlIdx; }
	void  SetChlIdx( u8 byChlIdx ){ m_byChlIdx = byChlIdx; }

}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//外设配置基类
struct TEqpCfgInfo
{
protected:    
    s8  m_szAlias[MAXLEN_EQP_ALIAS];		//别名
    u16 m_wMcuStartPort;					//mcu接收起始端口号
    u16 m_wEqpStartPort;					//外设接收起始端口号    
    u8  m_byEqpId;							//设备ID
    u8  m_bySwitchBrdIndex;					//交换板索引     
    u8  m_byRunningBrdIndex;				//运行板索引
    u8  m_byMapCount;						//使用的MAP个数
    u8  m_abyMapId[MAXNUM_MAP];				//Map编号数组

public:
    TEqpCfgInfo(void) { memset(this, 0, sizeof(TEqpCfgInfo)); }

    void    SetEqpId(u8 byEqpId) { m_byEqpId = byEqpId; }
    u8      GetEqpId(void) { return m_byEqpId; }
    void    SetMcuStartPort(u16 wPort) { m_wMcuStartPort = htons(wPort); }
    u16     GetMcuStartPort(void)   { return ntohs(m_wMcuStartPort); } 
    void    SetEqpStartPort(u16 wPort) { m_wEqpStartPort = htons(wPort); }
    u16     GetEqpStartPort(void) { return ntohs(m_wEqpStartPort); }
    void    SetSwitchBrdIndex(u8 byIndex) { m_bySwitchBrdIndex = byIndex; }
    u8      GetSwitchBrdIndex(void) { return m_bySwitchBrdIndex; }
    void    SetRunningBrdIndex(u8 byIndex) { m_byRunningBrdIndex = byIndex; }
    u8      GetRunningBrdIndex(void)    { return m_byRunningBrdIndex; }

    //下列方法仅供子类高清MAU特殊处理用
protected:
    void    SetMapCount(u8 byCount) { m_byMapCount = byCount; }
    u8      GetMapCount(void) const { return m_byMapCount; }

public:
    void    SetAlias(LPCSTR lpszAlias)
    {
        if(NULL != lpszAlias)
        {
            strncpy(m_szAlias, lpszAlias, sizeof(m_szAlias));
            m_szAlias[sizeof(m_szAlias) - 1] = '\0';
        }        
    }
    const s8* GetAlias(void) { return m_szAlias; }

    BOOL32    SetMapId(u8 *pbyMapId, u8 byCount)
    {
        if(NULL == pbyMapId || byCount > MAXNUM_MAP)
            return FALSE;
        
        memcpy(m_abyMapId, pbyMapId, byCount);
        m_byMapCount = byCount;
        return TRUE;
    }
    BOOL32     GetMapId(u8 *pbyMapId, u8 &byCount)
    {
        if(NULL == pbyMapId)
            return FALSE;
        
        memcpy(pbyMapId, m_abyMapId, m_byMapCount);
        byCount = m_byMapCount;
        return TRUE;
    }

    void PrintMap(void)
    {
        OspPrintf(TRUE, FALSE, "MapCount: %d, MapId: %d,%d,%d,%d,%d\n", 
            m_byMapCount, m_abyMapId[0], m_abyMapId[1], m_abyMapId[2], m_abyMapId[3], m_abyMapId[4]);
        
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// 混音器信息
//设备id,别名,mcu起始端口,设备起始端口,交换板索引,运行板索引,每个map最大混音组数,map编号
struct TEqpMixerCfgInfo : public TEqpCfgInfo
{
protected:    
    u8  m_byMaxChnnlInGrp;					//混音组最大通道数
   
public:
    TEqpMixerCfgInfo(void):m_byMaxChnnlInGrp(MAXNUM_MIXER_CHNNL) {}
    
    void    SetMaxChnnlInGrp(u8 byChnnlNum) { m_byMaxChnnlInGrp = byChnnlNum; }
    u8      GetMaxChnnlInGrp(void)  { return m_byMaxChnnlInGrp; } 
    
    void    Print(void) 
    {
        OspPrintf(TRUE, FALSE, "\nMixer:%s\nEqpId:%d, SwitchBrd:%d, RunBrd:%d, McuPort:%d, MixerPort:%d, MaxChnnl:%d\n",
                  GetAlias(), GetEqpId(), GetSwitchBrdIndex(), GetRunningBrdIndex(), 
                  GetMcuStartPort(), GetEqpStartPort(), GetMaxChnnlInGrp());
        PrintMap();
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// 录像机信息
//设备id,别名,mcu起始端口,设备起始端口,交换板索引,录像机ip
struct TEqpRecCfgInfo : public TEqpCfgInfo
{
protected:
    u32 m_dwIpAddr;							//数字放象、录象机的Ip地址

public:
    TEqpRecCfgInfo(void):m_dwIpAddr(0) {}
  
    void    SetIpAddr(u32 dwIpAddr)  { m_dwIpAddr = htonl(dwIpAddr); }  //host order
    u32     GetIpAddr(void) { return ntohl(m_dwIpAddr); }

    void    Print(void)
    {
        OspPrintf(TRUE, FALSE, "\nRec:%s\nEqpId:%d, SwitchBrd:%d, McuPort:%d, RecPort:%d, RecIp:0x%x\n",
                  GetAlias(), GetEqpId(), GetSwitchBrdIndex(), GetMcuStartPort(), 
                  GetEqpStartPort(), GetIpAddr());
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// 高清bas板信息
//设备id,别名,mcu起始端口,设备起始端口,交换板索引,运行板索引,高清bas板ip
struct TEqpBasHDCfgInfo : public TEqpCfgInfo
{
protected:
    u32 m_dwIpAddr;							//Ip地址

public:
    TEqpBasHDCfgInfo(void):m_dwIpAddr(0) {}
  
    void    SetIpAddr(u32 dwIpAddr)  { m_dwIpAddr = htonl(dwIpAddr); }  //host order
    u32     GetIpAddr(void) { return ntohl(m_dwIpAddr); }
    void    SetType(u8 byType) { SetMapCount(byType); }
    u8      GetType(void) const { return GetMapCount(); }

    void    Print(void)
    {
        OspPrintf(TRUE, FALSE, "\nRec:%s\nEqpId:%d, SwitchBrd:%d, McuPort:%d, RecPort:%d, RecIp:0x%x, Type.%d\n",
                  GetAlias(), GetEqpId(), GetSwitchBrdIndex(), GetMcuStartPort(), 
                  GetEqpStartPort(), GetIpAddr(), GetType());
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// 电视墙信息
//设备id,别名,设备起始端口,交换板索引,map编号
struct TEqpTvWallCfgInfo : public TEqpCfgInfo
{     
    void    Print(void)
    {
        OspPrintf(TRUE, FALSE, "\nTvWall:%s\nEqpId:%d, RunBrd:%d, TWPort:%d\n",
                 GetAlias(), GetEqpId(), GetRunningBrdIndex(), GetEqpStartPort());
        PrintMap();
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;
struct THduChnlModePort
{
public:
	THduChnlModePort()
	{
		memset(this, 0x0, sizeof(THduChnlModePort));
	}
	u8 GetZoomRate() const { return byZoomRate; }
	void SetZoomRate(u8 val) { byZoomRate = val; }

    u8 GetOutPortType() const { return byOutPortType; }
    void SetOutPortType(u8 val) { byOutPortType = val; }
	
    u8 GetOutModeType() const { return byOutModeType; }
    void SetOutModeType(u8 val) { byOutModeType = val; }
private:
    u8 byOutPortType;
    u8 byOutModeType;
    u8 byZoomRate;
    u8 reserved;
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
; 

//Hdu信息  jlb
struct TEqpHduCfgInfo : public TEqpCfgInfo 
{
protected:
	
    THduChnlModePort atHduChnlModePort[MAXNUM_HDU_CHANNEL];    
	
public:
	TEqpHduCfgInfo()
	{
        memset(&atHduChnlModePort, 0X0, sizeof(atHduChnlModePort));
	}
	
	void GetHduChnlModePort( u8 byNum, THduChnlModePort &tHduChnModePort )
	{
		if (byNum == 0 || byNum == 1)
		{
			tHduChnModePort.SetOutModeType( atHduChnlModePort[byNum].GetOutModeType() );
			tHduChnModePort.SetOutPortType( atHduChnlModePort[byNum].GetOutPortType() );
		    tHduChnModePort.SetZoomRate( atHduChnlModePort[byNum].GetZoomRate() );	
		}
		else
		{
			OspPrintf(TRUE, FALSE, "[TEqpHduCfgInfo]:GetHduChnlModePort()'s byNum wrong!\n");
			return;			
		}
		
		return;
	}
	
    void SetHduChnlModePort( u8 byNum, THduChnlModePort &tHduChnModePort )
	{
		if (byNum == 0 || byNum == 1)
		{
			atHduChnlModePort[byNum].SetOutModeType( tHduChnModePort.GetOutModeType() );
 			atHduChnlModePort[byNum].SetOutPortType( tHduChnModePort.GetOutPortType() );
            atHduChnlModePort[byNum].SetZoomRate( tHduChnModePort.GetZoomRate() );			
		}
		else
		{
			OspPrintf(TRUE, FALSE, "[TEqpHduCfgInfo]:SetHduChnlModePort()'s byNum wrong!\n");
			return;	
		}
		
		return;
	}
	
	void Print(void)
	{
		OspPrintf(TRUE, FALSE, "\nHdu:%s\nEqpId:%d, RunBrd:%d, HduPort:%d\n,ZoomRate[0] = %d, ZoomRate[1] = %d\n HduOutPortType[0]:%d, HduOutModeType[0]:%d\n,HduOutPortType[1]:%d, HduOutModeType[1]%d:",
			GetAlias(), GetEqpId(), GetRunningBrdIndex(), GetEqpStartPort(), 
			atHduChnlModePort[0].GetZoomRate(), atHduChnlModePort[1].GetZoomRate(),
			atHduChnlModePort[0].GetOutPortType(), atHduChnlModePort[0].GetOutModeType(),
			atHduChnlModePort[1].GetOutPortType(), atHduChnlModePort[1].GetOutModeType());
	}
}
#ifndef WIN32
__attribute__ ( (packed) )
#endif
;

//svmp(单vmp模式)信息   jlb
struct TEqpSvmpCfgInfo : public TEqpCfgInfo
{
    void    Print(void)
    {
        OspPrintf(TRUE, FALSE, "\nDvmp:%s\nEqpId:%d, SwitchBrd:%d, RunBrd:%d, McuPort:%d, DvmpPort:%d\n",
			GetAlias(), GetEqpId(), GetSwitchBrdIndex(), GetRunningBrdIndex(),
			GetMcuStartPort(), GetEqpStartPort());
    }
}
#ifndef WIN32
__attribute__ ( (packed) )
#endif
;

//dvmp(双vmp模式)中单个vmp的信息   jlb
struct TEqpDvmpCfgBasicInfo : public TEqpCfgInfo
{

    void    Print(void)
    {
        OspPrintf(TRUE, FALSE, "\nDvmp:%s\nEqpId:%d, SwitchBrd:%d, RunBrd:%d, McuPort:%d, DvmpPort:%d\n",
			GetAlias(), GetEqpId(), GetSwitchBrdIndex(), GetRunningBrdIndex(),
			GetMcuStartPort(), GetEqpStartPort());
    }
}
#ifndef WIN32
__attribute__ ( (packed) )
#endif
;

//双vmp模式的配置信息   jlb
struct TEqpDvmpCfgInfo
{
public:
	TEqpDvmpCfgBasicInfo tEqpDvmpCfgBasicInfo[2];    //获得两个vmp的信息

public:
	TEqpDvmpCfgInfo()
	{
		memset( this, 0 ,sizeof(TEqpDvmpCfgInfo) );
	}
}
#ifndef WIN32
__attribute__ ( (packed) )
#endif
;

//MpuBas信息    jlb
struct TEqpMpuBasCfgInfo : public TEqpCfgInfo
{
	void Print(void)
	{
	    OspPrintf(TRUE, FALSE, "\nBas:%s\nEqpId:%d, SwitchBrd:%d, RunBrd:%d, McuPort:%d, BasPort:%d\n",
		    GetAlias(), GetEqpId(), GetSwitchBrdIndex(), GetRunningBrdIndex(),
		    GetMcuStartPort(), GetEqpStartPort());
        PrintMap();
	}
}
#ifndef WIN32
__attribute__ ( (packed) )
#endif
;

// Ebap 信息
//设备id,别名,mcu起始端口,设备起始端口,交换板索引,运行板索引,map编号
struct TEqpEbapCfgInfo : public TEqpCfgInfo
{
    void    Print(void)
    {
        OspPrintf(TRUE, FALSE, "\nEbap:%s\nEqpId:%d, SwitchBrd:%d, RunBrd:%d, McuPort:%d, EbapPort:%d\n",
			GetAlias(), GetEqpId(), GetSwitchBrdIndex(), GetRunningBrdIndex(),
			GetMcuStartPort(), GetEqpStartPort());
        PrintMap();
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// Evpu 信息
//设备id,别名,mcu起始端口,设备起始端口,交换板索引,运行板索引,map编号
struct TEqpEvpuCfgInfo : public TEqpCfgInfo
{
    void    Print(void)
    {
        OspPrintf(TRUE, FALSE, "\nVmp:%s\nEqpId:%d, SwitchBrd:%d, RunBrd:%d, McuPort:%d, VmpPort:%d\n",
            GetAlias(), GetEqpId(), GetSwitchBrdIndex(), GetRunningBrdIndex(),
            GetMcuStartPort(), GetEqpStartPort());
        PrintMap();
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;


// Bas 信息
//设备id,别名,mcu起始端口,设备起始端口,交换板索引,运行板索引,map编号
struct TEqpBasCfgInfo : public TEqpCfgInfo
{
    void    Print(void)
    {
        OspPrintf(TRUE, FALSE, "\nBas:%s\nEqpId:%d, SwitchBrd:%d, RunBrd:%d, McuPort:%d, BasPort:%d\n",
                GetAlias(), GetEqpId(), GetSwitchBrdIndex(), GetRunningBrdIndex(),
                GetMcuStartPort(), GetEqpStartPort());
        PrintMap();
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// Vmp 信息
//设备id,别名,mcu起始端口,设备起始端口,交换板索引,运行板索引,map编号,同时视频编码路数
struct TEqpVmpCfgInfo : public TEqpCfgInfo
{
protected:
    u8  m_byEncodeNum;						//同时支持的视频编码路数

public:
    TEqpVmpCfgInfo(void) :m_byEncodeNum(0) {}

    void    SetEncodeNum(u8 byEncodeNum) { m_byEncodeNum = byEncodeNum; }
    u8      GetEncodeNum(void)  { return m_byEncodeNum; }

    void    Print(void)
    {
        OspPrintf(TRUE, FALSE, "\nVmp:%s\nEqpId:%d, SwitchBrd:%d, RunBrd:%d, McuPort:%d, VmpPort:%d, EncodeNum:%d\n",
            GetAlias(), GetEqpId(), GetSwitchBrdIndex(), GetRunningBrdIndex(),
            GetMcuStartPort(), GetEqpStartPort(), GetEncodeNum());
        PrintMap();
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//Mtw复合电视墙信息
//设备id,别名,设备起始端口,交换板索引,map编号
struct TEqpMTvwallCfgInfo : public TEqpCfgInfo
{
    void    Print(void)
    {
        OspPrintf(TRUE, FALSE, "\nMTvwall:%s\nEqpId:%d, RunBrd:%d, MTWPort:%d\n",
            GetAlias(), GetEqpId(), GetRunningBrdIndex(), GetEqpStartPort());
        PrintMap();
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// Prs信息
//设备id,别名,mcu起始端口,设备起始端口,交换板索引,运行板索引,重传检测点1,2,3,过期丢弃时间
struct TPrsCfgInfo : public TEqpCfgInfo
{
protected:
    u16 m_wFirstTimeSpan;						//第一个重传检测点(ms)
    u16 m_wSecondTimeSpan;						//第二个重传检测点(ms)
    u16 m_wThirdTimeSpan;						//第三个重传检测点(ms)
    u16 m_wLoseTimeSpan;						//过期丢弃的时间跨度(ms)

public:
    TPrsCfgInfo(void)
    {
        SetFirstTimeSpan(DEF_FIRSTTIMESPAN_PRS);
        SetSecondTimeSpan(DEF_SECONDTIMESPAN_PRS);
        SetThirdTimeSpan(DEF_THIRDTIMESPAN_PRS);
        SetLoseTimeSpan(DEF_LOSETIMESPAN_PRS);
    }

    void    SetFirstTimeSpan(u16 wTimeSpan) { m_wFirstTimeSpan = htons(wTimeSpan); }
    u16     GetFirstTimeSpan(void)  { return ntohs(m_wFirstTimeSpan); }
    void    SetSecondTimeSpan(u16 wTimeSpan) { m_wSecondTimeSpan = htons(wTimeSpan); }
    u16     GetSecondTimeSpan(void) { return ntohs(m_wSecondTimeSpan); }
    void    SetThirdTimeSpan(u16 wTimeSpan) { m_wThirdTimeSpan = htons(wTimeSpan); }
    u16     GetThirdTimeSpan(void)  { return ntohs(m_wThirdTimeSpan); }
    void    SetLoseTimeSpan(u16 wTimeSpan) { m_wLoseTimeSpan = htons(wTimeSpan); }
    u16     GetLoseTimeSpan(void)   { return ntohs(m_wLoseTimeSpan); }

    void    Print(void)
    {
        OspPrintf(TRUE, FALSE, "\nPrs:%s\nEqpId:%d, SwitchBrd:%d, RunBrd:%d, McuPort:%d\nPrsPort:%d, FstTime:%d, SndTime:%d, ThdTime:%d, LoseTime:%d\n",
            GetAlias(), GetEqpId(), GetSwitchBrdIndex(), GetRunningBrdIndex(), 
            GetMcuStartPort(), GetEqpStartPort(), GetFirstTimeSpan(), 
            GetSecondTimeSpan(), GetThirdTimeSpan(), GetLoseTimeSpan());
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//单板配置信息
struct TBrdCfgInfo
{	
protected:
	u8				m_byIndex;					    // 索引号
    u8				m_byLayer;					    // 层号
    u8              m_bySlotId;                     //槽id
    u8              m_bySlotType;                   //槽类型
    u8				m_byType;					    // 类型
    u32				m_dwBrdIp;					    // 单板Ip
    u8				m_bySelNetPort;				    // 网口选择
    u8				m_bySelMulticast;			    // 组播选择   
    u8              m_byBrdState;                   // 单板状态
    u8              m_byOsType;                     // 单板的OS类型 OS_TYPE_WIN32 ...
    s8              m_szAlias[MAXLEN_BRDALIAS];     // 商用名，如 BRD_ALIAS_TUI
public:
    TBrdCfgInfo(void) { memset(this, 0, sizeof(TBrdCfgInfo)); }

    void    SetIndex(u8 byIndex) { m_byIndex = byIndex; }
    u8      GetIndex(void) const { return m_byIndex; }
    void    SetLayer(u8 byLayer) { m_byLayer = byLayer; }
    u8      GetLayer(void) const { return m_byLayer; }    
    void    SetType(u8 byType) { m_byType = byType; }
    u8      GetType(void) const { return m_byType; }
    void    SetIpAddr(u32 dwIpAddr) { m_dwBrdIp = htonl(dwIpAddr); }    //host order
    u32     GetIpAddr(void) const { return ntohl(m_dwBrdIp); }
    void    SetSelNetPort(u8 bySel) { m_bySelNetPort = bySel; }
    u8      GetSelNetPort(void) const { return m_bySelNetPort; }
    void    SetSelMulticast(u8 bySel) { m_bySelMulticast = bySel; }
    u8      GetSelMulticast(void) const{ return m_bySelMulticast; }
    u8      GetBrdState(void) const { return m_byBrdState;}
    void    SetBrdState(u8 byBrdState) { m_byBrdState = byBrdState;}
    u8      GetOsType(void) const { return m_byOsType; }
    void    SetOsType(u8 byOsType) { m_byOsType = byOsType; }

    void SetSlot(u8 bySlotId, u8 bySlotType)
    {
        m_bySlotType = bySlotType;
        m_bySlotId  = bySlotId;      
    }

    void GetSlot(u8 &bySlotId, u8 &bySlotType) const
    { 
        bySlotId = m_bySlotId;
        bySlotType = m_bySlotType;
    }    

    void SetAlias(const s8* pszAlias)
    {
        memset( m_szAlias, 0, sizeof(m_szAlias) );
        strncpy( m_szAlias, pszAlias,  sizeof(m_szAlias) - 1);
    }
    const s8* GetAlias() const
    {
        return m_szAlias;
    }

    void Print(void) const
    {
        u8 bySlotId;
        u8 bySlotType;
        GetSlot(bySlotId, bySlotType);
        OspPrintf(TRUE, FALSE, "Index:%d, Layer:%d, SlotId%d, SlotType%d, BrdType%d, Alias:%s, BrdIp:0x%x, EthInt:%d, Multi:%d, BrdState:%d, OsType:%d\n",
                  GetIndex(), GetLayer(), bySlotId, bySlotType, GetType(), GetAlias(), GetIpAddr(), GetSelNetPort(), GetSelMulticast(), GetBrdState(), GetOsType());
    }
}
#ifndef WIN32
__attribute__( (packed) )
#endif
;

// 单板状态
struct TBoardStatusNotify
{
public:
    TBoardStatusNotify()
    { 
        memset(this, 0, sizeof(TBoardStatusNotify));
        m_byBrdState = BOARD_OUTLINE;
    }

    u8 GetBrdLayer(void) {return m_byBrdLayer;}
    u8 GetBrdSlot(void) {return m_byBrdSlot;}
    u8 GetBrdType(void) {return m_byBrdType;}
    u8 GetBrdState(void) {return m_byBrdState;}
    u8 GetBrdOsType(void) {return m_byOsType;}

    void SetBrdLayer(u8 byLayer) { m_byBrdLayer = byLayer;}
    void SetBrdSlot(u8 bySlot) { m_byBrdSlot = bySlot;}
    void SetBrdType(u8 byType) { m_byBrdType = byType;}
    void SetBrdState(u8 byState) { m_byBrdState = byState;}
    void SetBrdOsType(u8 byType) { m_byOsType = byType; }

private: 
    u8 m_byBrdLayer;
    u8 m_byBrdSlot;
    u8 m_byBrdType;
    u8 m_byBrdState;
    u8 m_byOsType;
}
#ifndef WIN32
__attribute__( (packed) )
#endif
;

//N+1冷备份信息结构
struct TNPlusInfo
{
protected:
    u32 m_dwNPlusMcuIp;                     //若支持N+1且不是备份工作模式，需要配置N+1备份mcu的地址
    u16 m_wNPlusRtdTime;                    //N+1备份rtd时间(s)
    u16 m_wNPlusRtdNum;                     //N+1备份rtd次数
    u8  m_byNPlusRollBack;                  //是否支持故障恢复，默认支持
    u8  m_byNPlusMode;                      //是否支持N+1备份
    u8  m_byNPlusBackupMode;                //是否N+1备份工作模式
    u8  m_byReserved;                       //保留
    
public:
    TNPlusInfo() : m_dwNPlusMcuIp(0),
                   m_wNPlusRtdTime(0),
                   m_wNPlusRtdNum(0),
                   m_byNPlusRollBack(0),
                   m_byNPlusMode(0),
                   m_byNPlusBackupMode(0),
                   m_byReserved(0){}
    
    void    SetIsNPlusMode(BOOL32 bNPlus) { m_byNPlusMode = bNPlus ? 1 : 0; }   //是否支持N+1备份
    BOOL32  IsNPlusMode(void) const { return (1 == m_byNPlusMode ? TRUE : FALSE); }
    void    SetIsNPlusBackupMode(BOOL32 bBackupMode) { m_byNPlusBackupMode = bBackupMode ? 1 : 0; }
    BOOL32  IsNPlusBackupMode(void) const{ return (1 == m_byNPlusBackupMode ? TRUE : FALSE); } //是否N+1备份工作模式
    void    SetNPlusMcuIp(u32 dwIp) { m_dwNPlusMcuIp = htonl(dwIp); }   
    u32     GetNPlusMcuIp(void)const { return ntohl(m_dwNPlusMcuIp); } //N+1备份mcu的地址(host order)
    void    SetNPlusRtdTime(u16 wTime) { m_wNPlusRtdTime = htons(wTime); }
    u16     GetNPlusRtdTime(void) const{ return ntohs(m_wNPlusRtdTime); }
    void    SetNPlusRtdNum(u16 wNum) { m_wNPlusRtdNum = htons(wNum); }
    u16     GetNPlusRtdNum(void) const{ return ntohs(m_wNPlusRtdNum); }
    void    SetIsNPlusRollBack(BOOL32 bRollBack) { m_byNPlusRollBack = bRollBack ? 1 : 0; }
    BOOL32  GetIsNPlusRollBack(void) const{ return (1 == m_byNPlusRollBack ? TRUE : FALSE); }

    void    Print() const
    {
        OspPrintf(TRUE, FALSE, "\nNPlusInfo:\nNPlusMode:%d, backupMode:%d, mcuIp:0x%x, rtd:%d, Num:%d\n",
                                IsNPlusMode(), IsNPlusBackupMode(), GetNPlusMcuIp(), 
                                GetNPlusRtdTime(), GetNPlusRtdNum());
    }
}
#ifndef WIN32
__attribute__( (packed) )
#endif
;

//mcu本地配置信息
struct TMcuLocalCfgInfo
{    
protected:
    s8  m_szMcuAlias[MAXLEN_ALIAS];			// Mcu 别名
    s8  m_szMcuE164[MAXLEN_E164];			// E164号
    s8  m_szMcuHardVer[MAXLEN_ALIAS];		// Mcu 硬件版本号   
    s8  m_szMcuSoftVer[MAXLEN_ALIAS];		// Mcu 软件版本号
    
    u16 m_wDiscCheckTime;                   //终端断链检测时间(s)
    u16 m_wDiscCheckTimes;                  //终端断链检测次数
    u16 m_wPartlistRefreshTime;             //级联时终端列表刷新时间间隔(s)
    u16 m_wAudInfoRefreshTime;              //级联时音频信息刷新时间间隔(s)
    u16 m_wVidInfoRefreshTime;              //级联时视频信息刷新时间间隔(s)
    u8  m_bySaveBandWidth;                  //是否节省带宽(0-不节省，1-节省)
    u8  m_byReserved;                       //保留

    TNPlusInfo m_tNPlusInfo;

public:
    TMcuLocalCfgInfo() : m_wDiscCheckTime(DEF_DISCCHECKTIME),
                         m_wDiscCheckTimes(DEF_DISCCHECKTIMES),
                         m_wPartlistRefreshTime(PARTLIST_REFRESHTIME),
                         m_wAudInfoRefreshTime(AUDINFO_REFRESHTIME),
                         m_wVidInfoRefreshTime(VIDINFO_REFRESHTIME),
                         m_byReserved(0)
    { 
        memset(m_szMcuAlias, 0, sizeof(m_szMcuAlias));
        memset(m_szMcuE164, 0, sizeof(m_szMcuE164));
        memset(m_szMcuHardVer, 0, sizeof(m_szMcuHardVer));
        memset(m_szMcuSoftVer, 0, sizeof(m_szMcuSoftVer));
    }
    BOOL32  IsNull(void)
    {
        TMcuLocalCfgInfo tInfo;
        return (0 == memcmp(this, &tInfo, sizeof(TMcuLocalCfgInfo)));
    }

    void    SetIsSaveBandWidth(u8 bySave) { m_bySaveBandWidth = (0 == bySave) ? 0 : 1; }
    u8      GetIsSaveBandWidth(void) const { return m_bySaveBandWidth; }
    void    SetDiscCheckTime(u16 wTime) { m_wDiscCheckTime = htons(wTime); }
    u16     GetDiscCheckTime(void) const { return ntohs(m_wDiscCheckTime); }
    void    SetDiscCheckTimes(u16 wTimes) { m_wDiscCheckTimes = htons(wTimes); }
    u16     GetDiscCheckTimes(void) const { return ntohs(m_wDiscCheckTimes); }
    void    SetPartListRefreshTime(u16 wTime) { m_wPartlistRefreshTime = htons(wTime); }
    u16     GetPartListRefreshTime(void) const { return ntohs(m_wPartlistRefreshTime); }
    void    SetAudInfoRefreshTime(u16 wTime) { m_wAudInfoRefreshTime = htons(wTime); }
    u16     GetAudInfoRefreshTime(void) const { return ntohs(m_wAudInfoRefreshTime); }
    void    SetVidInfoRefreshTime(u16 wTime) { m_wVidInfoRefreshTime = htons(wTime); }
    u16     GetVidInfoRefreshTime(void) const { return ntohs(m_wVidInfoRefreshTime); }

    void    SetNPlusInfo(TNPlusInfo &tInfo) { m_tNPlusInfo = tInfo; }
    TNPlusInfo GetNPlusInfo() const {return m_tNPlusInfo;}
    void    SetIsNPlusMode(BOOL32 bNPlus) { m_tNPlusInfo.SetIsNPlusMode( bNPlus ); }   //是否支持N+1备份
    BOOL32  IsNPlusMode(void) const{ return m_tNPlusInfo.IsNPlusMode(); }
    void    SetIsNPlusBackupMode(BOOL32 bBackupMode) { m_tNPlusInfo.SetIsNPlusBackupMode(bBackupMode); }
    BOOL32  IsNPlusBackupMode(void) const{ return m_tNPlusInfo.IsNPlusBackupMode(); } //是否N+1备份工作模式
    void    SetNPlusMcuIp(u32 dwIp) { m_tNPlusInfo.SetNPlusMcuIp(dwIp); }   
    u32     GetNPlusMcuIp(void) const{ return m_tNPlusInfo.GetNPlusMcuIp(); } //N+1备份mcu的地址(host order)
    void    SetNPlusRtdTime(u16 wTime) { m_tNPlusInfo.SetNPlusRtdTime(wTime); }
    u16     GetNPlusRtdTime(void) const{ return m_tNPlusInfo.GetNPlusRtdTime(); }
    void    SetNPlusRtdNum(u16 wNum) { m_tNPlusInfo.SetNPlusRtdNum(wNum); }
    u16     GetNPlusRtdNum(void) const{ return m_tNPlusInfo.GetNPlusRtdNum(); }
    void    SetIsNPlusRollBack(BOOL32 bRollBack) { m_tNPlusInfo.SetIsNPlusRollBack(bRollBack); }
    BOOL32  GetIsNPlusRollBack(void) const{ return m_tNPlusInfo.GetIsNPlusRollBack(); }
    
    void SetMcuAlias(LPCSTR lpszAlias)
    {
        if(NULL != lpszAlias)
        {
            strncpy(m_szMcuAlias, lpszAlias, sizeof(m_szMcuAlias));
            m_szMcuAlias[sizeof(m_szMcuAlias) - 1] = '\0';
        }        
    }
    const s8* GetMcuAlias(void) const{ return m_szMcuAlias; }

    void SetMcuE164(LPCSTR lpszE164)
    {
        if(NULL != lpszE164)
        {
            strncpy(m_szMcuE164, lpszE164, sizeof(m_szMcuE164));
            m_szMcuE164[sizeof(m_szMcuE164) - 1] = '\0';
        }        
    }
    const s8* GetMcuE164(void) const{ return m_szMcuE164; }

    void SetMcuHardVer(LPCSTR lpszHardVer)          //mcu 内部使用
    {
        if(NULL != lpszHardVer)
        {
            strncpy(m_szMcuHardVer, lpszHardVer, sizeof(m_szMcuHardVer));
            m_szMcuHardVer[sizeof(m_szMcuHardVer) - 1] = '\0';
        }        
    }
    const s8* GetMcuHardVer(void) const{ return m_szMcuHardVer; }

    void SetMcuSoftVer(LPCSTR lpszSoftVer)          //mcu 内部使用
    {
        if(NULL != lpszSoftVer)
        {
            strncpy(m_szMcuSoftVer, lpszSoftVer, sizeof(m_szMcuSoftVer));
            m_szMcuSoftVer[sizeof(m_szMcuSoftVer) - 1] = '\0';
        }        
    }
    const s8* GetMcuSoftVer(void) const{ return m_szMcuSoftVer; }

    void    Print(void) const
    {
        OspPrintf(TRUE, FALSE, "\nLocalInfo:\nMcuAlias:%s, E164:%s \nHardVer:%s \nSoftVer:%s \nIsSaveBW:%d DiscTime:%d, PartList:%d, Aud:%d, Vid:%d \nNPlusMode:%d, backupMode:%d, mcuIp:0x%x, rtd:%d, Num:%d\n",
                  GetMcuAlias(), GetMcuE164(), GetMcuHardVer(), GetMcuSoftVer(), 
                  GetIsSaveBandWidth(), GetDiscCheckTime(), GetPartListRefreshTime(),
                  GetAudInfoRefreshTime(), GetVidInfoRefreshTime(),
                  IsNPlusMode(), IsNPlusBackupMode(), GetNPlusMcuIp(), 
                  GetNPlusRtdTime(), GetNPlusRtdNum());
    }    
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// Trap 信息
struct TTrapCfgInfo
{
protected:
    u32  m_dwTrapIp;							// Ip    
    u16  m_wReadWritePort;						// 读写端口
    u16  m_wSendTrapPort;						// 发Trap端口
    s8   m_szReadCom[MAXLEN_TRAP_COMMUNITY];	// 读共同体
    s8   m_szWriteCom[MAXLEN_TRAP_COMMUNITY];	// 写共同体

public:
    TTrapCfgInfo(void) 
    { 
        memset(this, 0, sizeof(TTrapCfgInfo)); 
        SetReadWritePort(DEF_READWRITE_TRAPPORT);
        SetSendTrapPort(DEF_SEND_TRAPPORT);
    }

    void    SetTrapIp(u32 dwIP) { m_dwTrapIp = htonl(dwIP); }
    u32     GetTrapIp(void) { return ntohl(m_dwTrapIp); }
    void    SetReadWritePort(u16 wPort) { m_wReadWritePort = htons(wPort); }
    u16     GetReadWritePort(void)  { return ntohs(m_wReadWritePort); }
    void    SetSendTrapPort(u16 wPort) { m_wSendTrapPort = htons(wPort); }
    u16     GetSendTrapPort(void)  { return ntohs(m_wSendTrapPort); }

    void SetReadCom(LPCSTR lpszReadCom)          
    {
        if(NULL != lpszReadCom)
        {
            strncpy(m_szReadCom, lpszReadCom, sizeof(m_szReadCom));
            m_szReadCom[sizeof(m_szReadCom) - 1] = '\0';
        }        
    }
    const s8* GetReadCom(void) { return m_szReadCom; }

    void SetWriteCom(LPCSTR lpszWriteCom)          
    {
        if(NULL != lpszWriteCom)
        {
            strncpy(m_szWriteCom, lpszWriteCom, sizeof(m_szWriteCom));
            m_szWriteCom[sizeof(m_szWriteCom) - 1] = '\0';
        }        
    }
    const s8* GetWriteCom(void) { return m_szWriteCom; }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// 网络配置信息 
struct TMcuNetCfgInfo
{	
protected:
    u32 m_dwGKIpAddr;                               // Gk 地址 (若为0表示不注册gk)
    u32 m_dwRRQMtadpIpAddr;                         // 注册gk的主协议适配板地址                      
    u32 m_dwMulticastIpAddr;                        // 组播地址
    u16 m_wuMulticastPort;                          // 组播端口
    u16 m_wRcvStartPort;                            // 接受起始端口
    u16 m_w225245StartPort;                         // 245端口
    u16 m_wMaxMtNum;                                // mcu 最大终端数
	u16 m_wMTUSize;									// MTU 大小, zgc, 2007-04-02
	u8	m_byMTUSetupMode;							// MTU设置模式, zgc, 2007-04-05
    u8  m_byUseMPCTransData;                        // 是否使用Mpc传数据
    u8  m_byUseMPCStack;                            // 是否使用Mpc内置协议栈

	u8  m_byTrapListNum;                            // trap 表长度
	TTrapCfgInfo m_tTrapInfoList[MAXNUM_TRAP_LIST]; // trap表信息
    u8  m_byGkCharge;                               // 是否进行GK计费

public:
	TMcuNetCfgInfo(void) 
    { 
        memset(this, 0, sizeof(TMcuNetCfgInfo)); 
        SetMaxMtNum(MAXNUM_H225H245_MT);
    }
    BOOL32 IsNull(void)
    {
        TMcuNetCfgInfo tInfo;
        return (0 == memcmp(this, &tInfo, sizeof(TMcuNetCfgInfo)));
    }

    void SetGkIpAddr(u32 dwIpAddr) { m_dwGKIpAddr = htonl(dwIpAddr); }
    u32  GetGkIpAddr(void) { return ntohl(m_dwGKIpAddr); }
    void SetRRQMtadpIp(u32 dwIpAddr) { m_dwRRQMtadpIpAddr = htonl(dwIpAddr); }
    u32  GetRRQMtadpIp(void) { return ntohl(m_dwRRQMtadpIpAddr); }
    void SetMultiIpAddr(u32 dwIpAddr) { m_dwMulticastIpAddr = htonl(dwIpAddr); }
    u32  GetMultiIpAddr(void) { return ntohl(m_dwMulticastIpAddr); }
    void SetMultiPort(u16 wPort) { m_wuMulticastPort = htons(wPort); }
    u16  GetMultiPort(void) { return ntohs(m_wuMulticastPort); }
    void SetRcvStartPort(u16 wPort) { m_wRcvStartPort = htons(wPort); }
    u16  GetRcvStartPort(void) { return ntohs(m_wRcvStartPort); }
    void Set225245StartPort(u16 wPort) { m_w225245StartPort = htons(wPort); }
    u16  Get225245StartPort(void) { return ntohs(m_w225245StartPort); }
    void SetMaxMtNum(u16 wNum) { m_wMaxMtNum = htons(wNum); }
    u16  GetMaxMtNum(void) { return ntohs(m_wMaxMtNum); }
	void SetMTUSize(u16 wMTUSize) { m_wMTUSize = htons(wMTUSize); } // 设置MTU大小, zgc, 2007-04-02
	u16  GetMTUSize(void) {return ntohs(m_wMTUSize); } // 获得MTU大小, zgc, 2007-04-02
	void SetMTUSetupMode( u8 byMode ) { m_byMTUSetupMode = byMode; }
	u8	 GetMTUSetupMode( void ) { return m_byMTUSetupMode; }
    void SetIsUseMpcTransData(u8 byUse) { m_byUseMPCTransData = byUse; }
    u8   GetIsUseMpcTransData(void) { return m_byUseMPCTransData; }
    void SetIsUseMpcStack(u8 byUse) { m_byUseMPCStack = byUse; }
    u8   GetIsUseMpcStack(void) { return m_byUseMPCStack; }
    void   SetIsGKCharge(BOOL32 bCharge) { m_byGkCharge = bCharge ? 1 : 0;  }
    BOOL32 GetIsGKCharge(void) { return m_byGkCharge == 1 ? TRUE : FALSE;   }

    BOOL32 SetTrapList(TTrapCfgInfo *ptTrapInfo, u8 byNum)
    {
        if(NULL == ptTrapInfo || byNum > MAXNUM_TRAP_LIST)
            return FALSE;
        m_byTrapListNum = byNum;
        memcpy((void *)m_tTrapInfoList, (void *)ptTrapInfo, byNum*sizeof(TTrapCfgInfo));
        return TRUE;
    }
    BOOL32 GetTrapList(TTrapCfgInfo *ptTrapInfo, u8 &byNum)
    {
        if(NULL == ptTrapInfo)
            return FALSE;
        byNum = m_byTrapListNum;
        memcpy((void *)ptTrapInfo, (void *)m_tTrapInfoList, byNum*sizeof(TTrapCfgInfo));
        return TRUE;
    }
    
    void Print(void)
    {
        OspPrintf(TRUE, FALSE, "\nNetCfg:\nGKIp:0x%x, RRQMtadpIp:0x%x, MultiIp:0x%x, MultiPort:%d\nRcvPort:%d, 225Port:%d, MaxMtNum:%d, IsMpcTrans:%d, IsMpcStack:%d, MTU size:%d, MTU mode:%d \n",
                                GetGkIpAddr(), GetRRQMtadpIp(), GetMultiIpAddr(), GetMultiPort(), GetRcvStartPort(),
                                Get225245StartPort(), GetMaxMtNum(), GetIsUseMpcTransData(), GetIsUseMpcStack(), GetMTUSize(), GetMTUSetupMode() );
        OspPrintf(TRUE, FALSE, "traplist count: %d\n", m_byTrapListNum);
        for(u8 byTrap = 0; byTrap < m_byTrapListNum; byTrap++)
        {
            OspPrintf(TRUE, FALSE, "%d. IpAddr:0x%x, ReadCom:%s, WriteCom:%s, RWPort:%u, SendPort:%u\n", byTrap,
                                    m_tTrapInfoList[byTrap].GetTrapIp(), m_tTrapInfoList[byTrap].GetReadCom(), 
                                    m_tTrapInfoList[byTrap].GetWriteCom(), m_tTrapInfoList[byTrap].GetReadWritePort(), 
                                    m_tTrapInfoList[byTrap].GetSendTrapPort());
        }
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// Qos 信息
struct TMcuQosCfgInfo
{	
protected:
    u8  m_byQosType;					// Qos 类型
    u8  m_byAudLevel;					// 音频等级
    u8  m_byVidLevel;					// 视频等级
    u8  m_byDataLevel;					// 数据等级
    u8  m_bySignalLevel;				// 信号等级
    u8  m_byIpServiceType;				// IP服务类型
	
public:
    TMcuQosCfgInfo(void) { memset(this, 0, sizeof(TMcuQosCfgInfo)); }
    BOOL32  IsNull(void) const
    {
        TMcuQosCfgInfo tInfo;
        return (0 == memcmp(this, &tInfo, sizeof(TMcuQosCfgInfo)));
    }

    void    SetQosType(u8 byType) { m_byQosType = byType; }
    u8      GetQosType(void) const { return m_byQosType; }
    void    SetAudLevel(u8 byLevel) { m_byAudLevel = byLevel; }
    u8      GetAudLevel(void) const { return m_byAudLevel; }
    void    SetVidLevel(u8 byLevel) { m_byVidLevel = byLevel; }
    u8      GetVidLevel(void) const { return m_byVidLevel; }
    void    SetDataLevel(u8 byLevel) { m_byDataLevel = byLevel; }
    u8      GetDataLevel(void) const { return m_byDataLevel; }
    void    SetSignalLevel(u8 byLevel) { m_bySignalLevel = byLevel; }
    u8      GetSignalLevel(void) const { return m_bySignalLevel; }
    void    SetIpServiceType(u8 byType) { m_byIpServiceType = byType; }
    u8      GetIpServiceType(void) const { return m_byIpServiceType; }

    void    Print(void) const
    {
        OspPrintf(TRUE, FALSE, "QosCfg:  QosType:%d, Aud:%d, Vid:%d, Data:%d, Signal:%d, IpServciType:%d\n",
            GetQosType(), GetAudLevel(), GetVidLevel(), GetDataLevel(), 
            GetSignalLevel(), GetIpServiceType());
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// 网同步信息
struct TMcuNetSynCfgInfo
{	
protected:
    u8	m_byNetSynMode;			    	//网同步模式
    u8	m_byNetSynDTSlot;				//网同步使用的DT板号 (0-14)
    u8	m_byNetSynE1Index;				//网同步DT板上的E1号 (0-7)
	
public:
    TMcuNetSynCfgInfo(void)   { memset(this, 0, sizeof(TMcuNetSynCfgInfo)); }
    BOOL32  IsNull(void)
    {
        TMcuNetSynCfgInfo tInfo;
        return (0 == memcmp(this, &tInfo, sizeof(TMcuNetSynCfgInfo)));
    }

    void    SetNetSynMode(u8 byMode) { m_byNetSynMode = byMode; }
    u8      GetNetSynMode(void) { return m_byNetSynMode; }
    void    SetNetSynDTSlot(u8 bySlot) { m_byNetSynDTSlot = bySlot; }
    u8      GetNetSynDTSlot(void) { return m_byNetSynDTSlot; }
    void    SetNetSynE1Index(u8 byIndex) { m_byNetSynE1Index = byIndex; }
    u8      GetNetSynE1Index(void) { return m_byNetSynE1Index; }

    void    Print(void)
    {
        OspPrintf(TRUE, FALSE, "\nNetSynCfg:\nSynMode:%d, SynDTSlot:%d, SynE1Index:%d\n",
            GetNetSynMode(), GetNetSynDTSlot(), GetNetSynE1Index());
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//数字会议服务器配置信息
struct TDCSCfgInfo
{
protected:
	u32	m_dwDcsEqpIp;					//数字会议服务器设备id

public:
    TDCSCfgInfo(void) : m_dwDcsEqpIp(0) {}
    BOOL32  IsNull(void)
    {
        TDCSCfgInfo tInfo;
        return (0 == memcmp(this, &tInfo, sizeof(TDCSCfgInfo)));
    }

    void    SetDcsEqpIp(u32 dwEqpIp) { m_dwDcsEqpIp = htonl(dwEqpIp); }
    u32      GetDcsEqpIp(void) { return ntohl(m_dwDcsEqpIp); }
    
    void    Print(void)
    {
        OspPrintf(TRUE, FALSE, "\nDcsEqpIp:0x%x\n", GetDcsEqpIp());
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TDscUpdateReqHead
{
	TDscUpdateReqHead()
	{
		memset( this, 0, sizeof(TDscUpdateReqHead) );
	}
	~TDscUpdateReqHead(){;}
public:
	s8 m_acFileName[MAXLEN_MCU_FILEPATH];	//升级文件名
	u8  m_byMark;			//最后一帧标记，0-不是最后一帧，1-最后一帧
private:
	u32 m_dwFileSize;		//文件总长度
	u32 m_dwFrmNum;			//文件总帧数
	u32 m_dwReqFrmSN;		//当前的升级帧号
	u32 m_dwFrmSize;		//当前的数据包长度
public:
	void SetFileSize(u32 dwFileSize) { m_dwFileSize = htonl(dwFileSize); }
	u32  GetFileSize(void) { return ntohl(m_dwFileSize); }
	void SetFrmNum(u32 dwFrmNum) { m_dwFrmNum = htonl(dwFrmNum); }
	u32  GetFrmNum(void) { return ntohl(m_dwFrmNum); }
	void SetReqFrmSN(u32 dwReqFrmSN) { m_dwReqFrmSN = htonl(dwReqFrmSN); } 
	u32  GetReqFrmSN(void) { return ntohl(m_dwReqFrmSN); }
	void SetFrmSize(u32 dwFrmSize) { m_dwFrmSize = htonl(dwFrmSize); }
	u32  GetFrmSize(void) { return ntohl(m_dwFrmSize); }

}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TDscUpdateRsp
{
	TDscUpdateRsp()
	{
		memset( this, 0, sizeof(TDscUpdateRsp) );
	}
	~TDscUpdateRsp(){;}
public:
	s8 m_acFileName[MAXLEN_MCU_FILEPATH];	//升级文件名

private:
	u32 m_dwRspFrmSN;		//请求的下一帧帧号

public:
	void SetRspFrmSN(u32 dwRspFrmSN) { m_dwRspFrmSN = htonl(dwRspFrmSN); }
	u32  GetRspFrmSN(void) { return ntohl(m_dwRspFrmSN); }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;



struct TMINIMCUNetParam
{
public:
    enum enNetworkType
    {
        enInvalid = 0,
            enWAN = 1,
            enLAN = 2
    };
protected:

	u32 m_dwIpAddr;		// 网络序
	u32 m_dwIpMask;		// 网络序
	u32 m_dwGatewayIp;  // 网络序
	s8  m_asServerAlias[MAXLEN_PWD]; // 运营商别名
    u8  m_byNetwordType;    // 网络地址类型，LAN or WAN    
public:
	TMINIMCUNetParam():m_dwIpAddr(0),
					   m_dwIpMask(0),
					   m_dwGatewayIp(0),
                       m_byNetwordType(enInvalid)
	{
		memset(	m_asServerAlias, 0, sizeof(m_asServerAlias) );
	}

public:
    // 设置为公网地址
    void SetWanParam( u32 dwIp, u32 dwIpMask, u32 dwGW, LPCSTR lpszAlias )
    {
        m_byNetwordType = enWAN;
        m_dwIpAddr = htonl(dwIp);
        m_dwIpMask = htonl(dwIpMask); 
        m_dwGatewayIp = htonl(dwGW);

        if (NULL != lpszAlias)
        {
            strncpy(m_asServerAlias, lpszAlias, MAXLEN_PWD-1);
            m_asServerAlias[MAXLEN_PWD-1] = 0;
        }
        else
        {
            memset(	m_asServerAlias, 0, sizeof(m_asServerAlias) );
        }
    }

    // 设置为局域网地址
    void SetLanParam( u32 dwIp, u32 dwMask, u32 dwGW )
    {
        m_byNetwordType = enLAN;
        m_dwIpAddr = htonl(dwIp);
        m_dwIpMask = htonl(dwMask);
        m_dwGatewayIp = htonl(dwGW);

        // 局域网不需要别名
        memset(	m_asServerAlias, 0, sizeof(m_asServerAlias) );
    }

    BOOL32 IsValid() const
    {
        if ( 0 == m_dwIpAddr || enInvalid == m_byNetwordType )
        {
            return FALSE;
        }
        return TRUE;
    }

    // 获取网络类型
    u8   GetNetworkType() const
    {
        return m_byNetwordType;
    }

    BOOL IsWan() const
    {
        return (m_byNetwordType == enWAN);
    }
    BOOL IsLan() const
    {
        return (m_byNetwordType == enLAN);
    }

    // 获取地址参数
    u32  GetIpAddr(void) const { return ntohl(m_dwIpAddr); }
	u32  GetIpMask(void) const{ return ntohl(m_dwIpMask); }
    u32  GetGatewayIp(void) const{ return ntohl(m_dwGatewayIp); }

    // 获取别名
    const s8 * GetServerAlias(void) const{ return m_asServerAlias; }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TMINIMCUNetParamAll
{
private:
	u8 m_byParamNum;
	TMINIMCUNetParam m_atMINIMCUNetParam[ETH_IP_MAXNUM];

public:
	TMINIMCUNetParamAll()
	{
		m_byParamNum = 0;
		memset( m_atMINIMCUNetParam, 0, sizeof(m_atMINIMCUNetParam) );
	}
	BOOL32 IsValid() const
	{
		return ( m_byParamNum != 0 );
	}
	u8 GetNetParamNum(void) const
	{
		return m_byParamNum;
	}
	u8 GetLANParamNum(void) const
	{
        u8 byNum = 0;
		for ( u8 byLop = 0; byLop < m_byParamNum; byLop++ )
		{
			if ( m_atMINIMCUNetParam[byLop].IsLan() )
			{
				byNum++;
			}
		}
		return byNum;
	}
	BOOL32 AddOneNetParam( const TMINIMCUNetParam &tNetParam )
	{
		if ( !tNetParam.IsValid() )
		{
			return FALSE;
		}
		u8 byIdx = 0;
		u8 byArrayLen = sizeof(m_atMINIMCUNetParam)/sizeof(TMINIMCUNetParam);
		for ( byIdx = 0; byIdx < byArrayLen; byIdx++ )
		{
			if( !m_atMINIMCUNetParam[byIdx].IsValid() )
			{
				memcpy( m_atMINIMCUNetParam+byIdx, &tNetParam, sizeof(TMINIMCUNetParam) );
				break;
			}
		}
		if ( byIdx == byArrayLen )
		{
			return FALSE;
		}
		m_byParamNum ++;
		return TRUE;
	}
	BOOL32 GetNetParambyIdx ( u8 byIdx, TMINIMCUNetParam &tNetParam ) const
	{
		memset( &tNetParam, 0, sizeof(TMINIMCUNetParam) );
		if ( byIdx >= m_byParamNum )
		{
			return FALSE;
		}
		if ( !m_atMINIMCUNetParam[byIdx].IsValid() )
		{
			return FALSE;
		}
		memcpy( &tNetParam, &m_atMINIMCUNetParam[byIdx], sizeof(TMINIMCUNetParam) );
		return TRUE;
	}
	BOOL32 DelNetParamByIdx(u8 byIdx)
	{
        if (m_byParamNum == 0)
        {
            return FALSE;
        }
		if ( byIdx >= m_byParamNum )
		{
			return FALSE;
		}
		u8 byLop = 0;
		for ( byLop = byIdx+1; byLop < m_byParamNum; byLop++ )
		{
			memcpy( &m_atMINIMCUNetParam[byLop-1], &m_atMINIMCUNetParam[byLop], sizeof(TMINIMCUNetParam) );
		}
		memset( &m_atMINIMCUNetParam[byLop-1], 0, sizeof(TMINIMCUNetParam) );
		m_byParamNum--;
		return TRUE;
	}
	BOOL32 IsEqualTo( const TMINIMCUNetParamAll &tMINIMCUNetParamAll )
	{
		return ( 0 == memcmp( &tMINIMCUNetParamAll, this, sizeof(TMINIMCUNetParamAll) ) ) ? TRUE : FALSE;
	}
	void Clear(void)
	{
		memset( this, 0, sizeof(TMINIMCUNetParamAll) );
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//MCU8000B 配置DSC运行模块
struct T8000BDscMod
{
protected:
    u32 m_dwMcuInnerIp;          // DSC 要连接的MCU内部IP 
    u32 m_dwDscInnerIp;		     // DSC 的内部IP
    u32 m_dwInnerIpMask;         // DSC 内部IP掩码
    u16 m_wMcuListenPort;		 // DSC 要连接的MCU端口,一般是60000
	
	u8  m_byNetType;			 // MCU所在的网络类型
	u8  m_byLanMtProxyIpPos;	 // 内网终端代理服务器IP的索引位置 
	TMINIMCUNetParamAll m_tDscParamAll;	// 呼叫地址（即DSC侧IP）
	TMINIMCUNetParamAll m_tMcuParamAll;	// 会控连接地址（即MCU侧0口IP）
	
    u8 m_byStartMp;
    u8 m_byStartMtAdp;
    u8 m_byStartGk;
    u8 m_byStartProxy;
    u8 m_byStartDcs;

public:
    T8000BDscMod():m_byStartMp(0),
                     m_byStartMtAdp(0),
                     m_byStartGk(0),
                     m_byStartProxy(0),
                     m_byStartDcs(0),
                     m_wMcuListenPort(MCU_LISTEN_PORT),
                     m_dwMcuInnerIp(0),
                     m_dwDscInnerIp(0),
                     m_dwInnerIpMask(0),
					 m_byNetType(NETTYPE_INVALID),
					 m_byLanMtProxyIpPos(0)
    {
		memset( &m_tDscParamAll, 0, sizeof(m_tDscParamAll) );
		memset( &m_tMcuParamAll, 0, sizeof(m_tMcuParamAll) );
	}
    
    void   SetMcuInnerIp(u32 dwIp) { m_dwMcuInnerIp = htonl(dwIp); }
    u32    GetMcuInnerIp() const { return ntohl(m_dwMcuInnerIp); }
    void   SetMcuPort(u16 wPort) { m_wMcuListenPort = htons(wPort); }
    u16    GetMcuPort() const { return ntohs(m_wMcuListenPort); }
    void   SetDscInnerIp(u32 dwIp) { m_dwDscInnerIp = htonl(dwIp); }
    u32    GetDscInnerIp() const { return ntohl(m_dwDscInnerIp); }
    void   SetInnerIpMask(u32 dwMask) { m_dwInnerIpMask = htonl(dwMask); }
    u32    GetInnerIpMask() const {return ntohl(m_dwInnerIpMask); }
	void   SetNetType(u8 byNetType) { m_byNetType = byNetType; }
	u8	   GetNetType(void) const { return m_byNetType; }
	void   SetLanMtProxyIpPos(u8 byLanMtProxyIpPos) { m_byLanMtProxyIpPos = byLanMtProxyIpPos; }
	u8	   GetLanMtProxyIpPos(void) const { return m_byLanMtProxyIpPos; }

	void SetCallAddrAll( TMINIMCUNetParamAll &tDscParamAll)
	{
		if ( tDscParamAll.IsValid() )
		{
			memcpy( &m_tDscParamAll, &tDscParamAll, sizeof(TMINIMCUNetParamAll) );
		}
	}
	void SetMcsAccessAddrAll( TMINIMCUNetParamAll &tMcuParamAll)
	{
		if ( tMcuParamAll.IsValid() )
		{
			memcpy( &m_tMcuParamAll, &tMcuParamAll, sizeof(TMINIMCUNetParamAll) );
		}
	}
	void GetCallAddrAll(TMINIMCUNetParamAll &tDscParamAll) const 
	{ 
		memcpy( &tDscParamAll, &m_tDscParamAll, sizeof(TMINIMCUNetParamAll) ); 
	}
	void GetMcsAccessAddrAll(TMINIMCUNetParamAll &tMcuParamAll) const 
	{ 
		memcpy( &tMcuParamAll, &m_tMcuParamAll, sizeof(TMINIMCUNetParamAll) ); 
	}
	u8 GetCallAddrNum(void) const 
    { 
        return m_tDscParamAll.GetNetParamNum(); 
    }
	u8 GetMcsAccessAddrNum(void) const 
    { 
        return m_tMcuParamAll.GetNetParamNum(); 
    }
    /*
    u8 GetLanCallAddrNum(void) const
    {
        return m_tDscParamAll.GetLANParamNum();
	}
	u8 GetLanMcsAccessAddrNum(void) const
	{
        return m_tMcuParamAll.GetLANParamNum();
	}
    */
   
    void   SetStartMp(BOOL32 bStart){ m_byStartMp = bStart ? 1 : 0;    }
    BOOL32 IsStartMp() const { return m_byStartMp == 1 ? TRUE : FALSE;    }
    void   SetStartMtAdp(BOOL32 bStart){ m_byStartMtAdp = bStart ? 1 : 0;    }
    BOOL32 IsStartMtAdp() const { return m_byStartMtAdp == 1 ? TRUE : FALSE;    }
    void   SetStartGk(BOOL32 bStart) { m_byStartGk = bStart ? 1 : 0; }
    BOOL32 IsStartGk() const { return m_byStartGk == 1 ? TRUE : FALSE; }
    void   SetStartProxy(BOOL32 bStart) { m_byStartProxy = bStart ? 1 : 0; }
    BOOL32 IsStartProxy() const { return m_byStartProxy == 1 ? TRUE : FALSE; }
    void   SetStartDcs(BOOL32 bStart) { m_byStartDcs = bStart ? 1 : 0; }
    BOOL32 IsStartDcs() const { return m_byStartDcs == 1 ? TRUE : FALSE; }

    void   Print() const
    {
        u8 byLop = 0;
        OspPrintf( TRUE, FALSE, "T8000BDscMod: DscInnerIp: 0x%x, McuInnerIp: 0x%x:%d, InnerMask: 0x%x. Module: Mp.%d, MtAdp.%d, GK.%d, Proxy.%d, Dcs.%d\n", 
            m_dwDscInnerIp, m_dwMcuInnerIp, m_wMcuListenPort, m_dwInnerIpMask,
            m_byStartMp, m_byStartMtAdp, m_byStartGk, m_byStartProxy, m_byStartDcs);
		OspPrintf( TRUE, FALSE, "Net Type: ");
		switch( m_byNetType )
		{
		case NETTYPE_INVALID:
			OspPrintf(TRUE, FALSE, "INVALID\n");
			break;
		case NETTYPE_LAN:
			OspPrintf(TRUE, FALSE, "LAN\n");
			break;
		case NETTYPE_WAN:
			OspPrintf(TRUE, FALSE, "WAN\n");
			break;
		case NETTYPE_MIXING_ALLPROXY:
			printf( "MIXING_ALLPROXY\n");
			break;
		case NETTYPE_MIXING_NOTALLPROXY:
			printf( "MIXING_NOTALLPROXY\n" );
			break;
		default:
			break;
		}
		OspPrintf( TRUE, FALSE, "LanMtProxyIpPos: %d\n", m_byLanMtProxyIpPos );
		OspPrintf( TRUE, FALSE, "T8000BDscMod: DSC NetParam--\n");
		TMINIMCUNetParam tTemp;
		for ( byLop = 0; byLop < m_tDscParamAll.GetNetParamNum(); byLop++ )
		{
			if ( m_tDscParamAll.GetNetParambyIdx(byLop, tTemp) )
			{
				if ( tTemp.IsValid() )
				{
					OspPrintf(TRUE, FALSE, "NetType:%s, Ip: 0x%x\tIpMask: 0x%x\tGateway: 0x%x\tServerAlias: %s\n",
                        tTemp.IsLan() ? "LAN" : "WAN",
						tTemp.GetIpAddr(), tTemp.GetIpMask(),
						tTemp.GetGatewayIp(), tTemp.GetServerAlias() );
				}
			}
		}
		OspPrintf( TRUE, FALSE, "T8000BDscMod: MCU NetParam--\n");
		for ( byLop = 0; byLop < ETH_IP_MAXNUM; byLop++ )
		{
			if ( m_tMcuParamAll.GetNetParambyIdx(byLop, tTemp) )
			{
				if ( tTemp.IsValid() )
				{
					OspPrintf(TRUE, FALSE, "NetType:%s, Ip: 0x%x\tIpMask: 0x%x\tGateway: 0x%x\tServerAlias: %s\n",
                        tTemp.IsLan() ? "LAN" : "WAN",
						tTemp.GetIpAddr(), tTemp.GetIpMask(),
						tTemp.GetGatewayIp(), tTemp.GetServerAlias() );
				}
			}
		}
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//Log info
struct TLoginInfo
{
public:
	s8  m_achUser[MAXLEN_PWD+1];//用户名
	s8  m_achPwd[MAXLEN_PWD+1]; //用户密码

public:
	TLoginInfo() { memset( this, 0, sizeof(TLoginInfo) ); }

	void  SetUser( LPCSTR lpszUser )
	{
		memset(m_achUser, 0, sizeof(m_achUser));
		if (NULL != lpszUser)
		{
			strncpy(m_achUser, lpszUser, sizeof(m_achUser));
			m_achUser[sizeof(m_achUser)-1] = '\0';
		}
	}

	LPCSTR GetUser( void ) const{ return m_achUser; }

	BOOL IsEqualUser( LPCSTR lpszUser ) const
	{
		s8 achBuf[MAXLEN_PWD+1] = {0};
		strncpy( achBuf, lpszUser, sizeof( achBuf ) );
		achBuf[sizeof(achBuf)-1] = '\0';
		
		if(0 == strncmp(achBuf, lpszUser, MAXLEN_PWD))
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}

	void SetPwd( LPCSTR lpszPwd )
	{
		memset(m_achPwd, 0, sizeof(m_achPwd));
		if (NULL != lpszPwd)
		{
			strncpy(m_achPwd, lpszPwd, sizeof(m_achPwd));
			m_achPwd[sizeof(m_achPwd)-1] = '\0';
            // 简单加密。在GetPwd之前要手动解密
            EncPwd();
		}
	}

	BOOL32 GetPwd( s8* pchPwd, u8 byLength )
	{
		if ( byLength < strlen(m_achPwd)+1 )
		{
			return FALSE;
		}
		DecPwd();
		strncpy( pchPwd, m_achPwd, byLength );
		pchPwd[byLength-1] = '\0';
		EncPwd();
		return TRUE; 
	}
        
    void DecPwd()
    {
        EncPwd();
    }

	void Print(void)
	{
		OspPrintf( TRUE, FALSE, "Username = %s\n", GetUser() );
		s8 achPwd[MAXLEN_PWD+1];
		memset(achPwd, 0, sizeof(achPwd));
		GetPwd(achPwd, sizeof(achPwd));
		OspPrintf( TRUE, FALSE, "Password = %s\n", achPwd );
	}

private:
    void EncPwd()
    {
        for (u8 byLoop=0; byLoop<strlen(m_achPwd); byLoop++)
        {
            m_achPwd[byLoop] ^= 0x5a;
        }
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//mcu general config info
struct TMcuGeneralCfg
{
    u8                  m_byVmpStyleNum;
    TVmpStyleCfgInfo    m_atVmpStyle[MAX_VMPSTYLE_NUM];
    TMcuLocalCfgInfo    m_tLocal;
    TMcuNetCfgInfo      m_tNet;
    TMcuQosCfgInfo      m_tQos;
    TMcuNetSynCfgInfo   m_tNetSyn;
    TDCSCfgInfo         m_tDcs;
    T8000BDscMod        m_tDscInfo;
	TLoginInfo			m_tLoginInfo;

public:
    void Print(void)
    {
        OspPrintf(TRUE, FALSE, "mcu generalcfg info:\n");
        for(u8 byIndex = 0; byIndex < m_byVmpStyleNum; byIndex++)
        {
            m_atVmpStyle[byIndex].Print();
        }        
        m_tLocal.Print();
        m_tNet.Print();
        m_tQos.Print();
        m_tNetSyn.Print();
        m_tDcs.Print();
        m_tDscInfo.Print();
		m_tLoginInfo.Print();
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//地址簿数据结构定义
//size: 143 byte, 若增加此结构的内容注意更新每包消息的条目个数(ADDRENTRYNUM_PERPKT)
struct TMcuAddrEntry
{
protected:
    u32     m_dwEntryIdx;                                   // 条目索引
    s8	    m_szEntryName[MAXLEN_ADDR_ENTRYNAME+1];		    // 条目名字
    s8	    m_szMtAlias[MAXLEN_ADDR_323ALIAS+1];	        // 呼叫别名
    u32	    m_dwMtIpAddr;							        // IP地址(网络序)
    s8	    m_szMtE164[MAXLEN_ADDR_E164NUM+1];	    	    // 呼叫号码
    u8      m_byMtProtocolType;                             // 0:H323终端; 非0:H320终端
    s8      m_szH320Id[MAXLEN_ADDR_320ID+1];                // H320ID
    u16	    m_wCallRate;							        // 呼叫速率

public:
    TMcuAddrEntry( void ) { memset(this, 0, sizeof(TMcuAddrEntry)); }
    
    void SetEntryIdx(u32 dwIndex) { m_dwEntryIdx = htonl(dwIndex); } 
    u32  GetEntryIdx( void ) { return ntohl(m_dwEntryIdx); }

    void SetEntryName(LPCSTR lpszEntryName)          
    {
        if(NULL != lpszEntryName)
        {
            strncpy(m_szEntryName, lpszEntryName, sizeof(m_szEntryName));
            m_szEntryName[sizeof(m_szEntryName) - 1] = '\0';
        }        
    }
    LPCSTR GetEntryName(void) { return m_szEntryName; }

    void SetMtAlias(LPCSTR lpszMtAlias)          
    {
        if(NULL != lpszMtAlias)
        {
            strncpy(m_szMtAlias, lpszMtAlias, sizeof(m_szMtAlias));
            m_szMtAlias[sizeof(m_szMtAlias) - 1] = '\0';
        }        
    }
    LPCSTR GetMtAlias(void) { return m_szMtAlias; }

    void SetMtIpAddr(u32 dwIp) { m_dwMtIpAddr = htonl(dwIp); }
    u32  GetMtIpAddr( void ) { return ntohl(m_dwMtIpAddr); }

    void SetMtE164(LPCSTR lpszMtE164)
    {
        if(NULL != lpszMtE164)
        {
            strncpy(m_szMtE164, lpszMtE164, sizeof(m_szMtE164));
            m_szMtE164[sizeof(m_szMtE164) - 1] = '\0';
        }
    }
    LPCSTR GetMtE164( void ) { return m_szMtE164; }

    void SetMtProtocolType(u8 byType) { m_byMtProtocolType = byType; }
    u8  GetMtProtocolType( void ) { return m_byMtProtocolType; }

    void SetH320Id(LPCSTR lpszH320Id)
    {
        if(NULL != lpszH320Id)
        {
            strncpy(m_szH320Id, lpszH320Id, sizeof(m_szH320Id));
            m_szH320Id[sizeof(m_szH320Id) - 1] = '\0';
        }
    }
    LPCSTR GetH320Id( void ) { return m_szH320Id; }

    void SetCallRate(u16 wCallRate) { m_wCallRate = htons(wCallRate); }
    u16  GetCallRate( void ) { return ntohs(m_wCallRate); }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//size: 809 byte, 若增加此结构的内容注意更新每包消息的条目组个数(ADDRGROUPNUM_PERPKT)
struct TMcuAddrGroup
{
protected:
    u32 m_dwEntryIdx;								// 条目索引
    u32 m_dwEntryNum;							    // 与会终端个数
    u32 m_adwEntryIdx[MAXNUM_CONF_MT];	            // 与会终端索引
    s8  m_szGroupName[MAXLEN_ADDR_ENTRYNAME + 1];	// 组名     

public:
    TMcuAddrGroup( void ) { memset(this, 0, sizeof(TMcuAddrGroup)); }

    void SetEntryIdx(u32 dwIndex) { m_dwEntryIdx = htonl(dwIndex); } 
    u32  GetEntryIdx( void ) { return ntohl(m_dwEntryIdx); }

    void SetEntryNum(u32 dwEntryNum) { m_dwEntryNum = htonl(dwEntryNum); }
    u32  GetEntryNum( void ) { return ntohl(m_dwEntryNum); }

    void GetAllEntryIdx(u32 *padwEntryIdx, u32 &dwNum)
    {
        if(NULL == padwEntryIdx) return;

        if(dwNum > GetEntryNum()) 
        {
            dwNum = GetEntryNum();
        }
        
        if(dwNum > MAXNUM_CONF_MT)
        {
            dwNum = MAXNUM_CONF_MT;
        }
        
        for(u32 dwIdx=0; dwIdx < dwNum; dwIdx++)
        {
            padwEntryIdx[dwIdx] = ntohl(m_adwEntryIdx[dwIdx]);
        }        
    }
    void SetAllEntryIdx(u32 *padwEntryIdx, u32 dwNum)
    {
        if(NULL == padwEntryIdx) return;

        if(dwNum > MAXNUM_CONF_MT)
        {
            dwNum = MAXNUM_CONF_MT;
        }

        for(u32 dwIdx=0; dwIdx < dwNum; dwIdx++)
        {
            m_adwEntryIdx[dwIdx] = htonl(padwEntryIdx[dwIdx]);
        }

        m_dwEntryNum = htonl(dwNum);
    }
    
    void SetGroupName(LPCSTR lpszName)
    {
        if(NULL != lpszName)
        {
            strncpy(m_szGroupName, lpszName, sizeof(m_szGroupName));
            m_szGroupName[sizeof(m_szGroupName)-1] = '\0';
        }
    }
    LPCSTR GetGroupName( void ) { return m_szGroupName; }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//mcu主备状态通知
struct TMcuMsStatus
{
protected:
    u8  m_byIsMsSwitchOK;

public:
    TMcuMsStatus(void) : m_byIsMsSwitchOK(0) {}

    void    SetMsSwitchOK(BOOL32 bSwitchOK) { m_byIsMsSwitchOK = bSwitchOK ? 1:0; }
    BOOL32  IsMsSwitchOK(void) { return (1==m_byIsMsSwitchOK); }

}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//MCU会议计费结构 len: 146
struct TConfChargeInfo
{
protected:
    s8  m_achGKUsrName[MAX_LEN_GK_USRNAME]; //GK用户名
    s8  m_achGKPwd[MAX_LEN_GK_PWD];         //GK密码

    s8  m_achConfName[MAXLEN_CONFNAME+1];   //会议名称
    s8  m_achConfE164[MAXLEN_E164+1];       //会议E164号
    
    u16 m_wBitRate;                         //会议码率
    u16 m_wTerNum;                          //终端数
    u8  m_byMixerNum;                       //混音数
    u8  m_byVMPNum;                         //多画面数
    u8  m_byBASNum;                         //码率适配数(不包含格式适配)
    u8  m_byUseCasd;                        //是否使用级联
    u8  m_byUseEncrypt;                     //是否使用加密
    u8  m_byUseDualVideo;                   //是否使用双流
    u8  m_byUseDataConf;                    //是否召开数据会议
    u8  m_byUseStreamBroadCast;             //是否使用流媒体组播
public:
    TConfChargeInfo() :m_wBitRate(0),
                       m_wTerNum(0),
                       m_byMixerNum(0),
                       m_byVMPNum(0),
                       m_byBASNum(0),
                       m_byUseCasd(0),
                       m_byUseEncrypt(0),
                       m_byUseDualVideo(0),
                       m_byUseDataConf(0),
                       m_byUseStreamBroadCast(0)
    {
        memset( &m_achGKUsrName, 0, sizeof(m_achGKUsrName) );
        memset( &m_achGKPwd,    0, sizeof(m_achGKPwd) );
        memset( &m_achConfName, 0, sizeof(m_achConfName) );
        memset( &m_achConfE164, 0, sizeof(m_achConfE164) );
    }
    void SetBitRate(u16 wBitRate) { m_wBitRate = htons(wBitRate);    }
    u16  GetBitRate(void) const { return ntohs(m_wBitRate);    }
    void SetTerNum(u16 wNum) { m_wTerNum = htons(wNum);    }
    u16  GetTerNum(void) const { return ntohs(m_wTerNum);    }
    void SetMixerNum(u8 byNum){ m_byMixerNum = byNum;    }
    u8   GetMixerNum(void) const { return m_byMixerNum;    }
    void SetVMPNum(u8 byVMPNum) { m_byVMPNum = byVMPNum;    }
    u8   GetVMPNum(void) const { return m_byVMPNum;    }
    void SetBasNum(u8 byBasNum) { m_byBASNum = byBasNum; }
    u8   GetBasNum(void) const { return m_byBASNum;    }
    void   SetIsUseCascade(BOOL32 bUse) { m_byUseCasd = bUse ? 1 : 0;    }
    BOOL32 GetIsUseCascade(void) const { return m_byUseCasd == 1 ? TRUE : FALSE;    }
    void   SetIsUseEncrypt(BOOL32 bUse) { m_byUseEncrypt = bUse ? 1 : 0;    }
    BOOL32 GetIsUseEncrypt(void) const { return m_byUseEncrypt == 1 ? TRUE : FALSE;    }
    void   SetIsUseDualVideo(BOOL32 bUse) { m_byUseDualVideo = bUse ? 1 : 0;    }
    BOOL32 GetIsUseDualVideo(void) const { return m_byUseDualVideo == 1 ? TRUE : FALSE;    }
    void   SetIsUseDataConf(BOOL32 bUse) { m_byUseDataConf = bUse ? 1 : 0;    }
    BOOL32 GetIsUseDataConf(void) const { return m_byUseDataConf == 1 ? TRUE : FALSE;    }
    void   SetIsUseStreamBroadCast(BOOL32 bUse) { m_byUseStreamBroadCast = bUse ? 1 : 0;    }
    BOOL32 GetIsUseStreamBroadCast(void) const { return m_byUseStreamBroadCast == 1 ? TRUE : FALSE;    }
    void SetGKUsrName(LPCSTR pszUsrName)
    {
        if ( pszUsrName != NULL )
        {
            u16 wLen = min(strlen(pszUsrName), MAX_LEN_GK_USRNAME-1);
            memcpy( m_achGKUsrName, pszUsrName, wLen );
            m_achGKUsrName[wLen] = '\0';
        }
        return;
    }
    LPCSTR GetGKUsrName(void) { return m_achGKUsrName;    }

    void SetGKPwd(LPCSTR pszPwd)
    {
        if ( pszPwd != NULL )
        {
            u16 wLen = min(strlen(pszPwd), MAX_LEN_GK_PWD-1);
            strncpy( m_achGKPwd, pszPwd, wLen );
            m_achGKPwd[wLen] = '\0';
        }
        return;
    }
    LPCSTR GetGKPwd(void) { return m_achGKPwd;    }
    
    void SetConfName(LPCSTR pszConfName)
    {
        if ( pszConfName != NULL )
        {
            u16 wLen = min(strlen(pszConfName), MAXLEN_CONFNAME);
            strncpy( m_achConfName, pszConfName, wLen );
            m_achConfName[wLen] = '\0';
        }
        return;
    }
    LPCSTR GetConfName(void) { return m_achConfName;    }

    void SetConfE164(LPCSTR pszConfE164)
    {
        if ( pszConfE164 != NULL )
        {
            u16 wLen = min(strlen(pszConfE164), MAXLEN_E164);
            strncpy( m_achConfE164, pszConfE164, wLen );
            m_achConfE164[wLen] = '\0';
        }
        return;
    }
    LPCSTR GetConfE164(void) { return m_achConfE164;    }
    
    BOOL32 IsNull(void) const { return (strlen(m_achGKUsrName) == 0 ? TRUE : FALSE); }

}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TMpuChn
{
public:
    TMpuChn():m_dwIpAddr(0),
              m_byChnId(0)
    {
    }
    void   SetIpAddr(u32 dwIp) { m_dwIpAddr = htonl(dwIp); }
    u32    GetIpAddr(void) { return ntohl(m_dwIpAddr);  }
    void   SetChnId(u8 byId) { m_byChnId = byId; }
    u8     GetChnId(void) { return m_byChnId; }
    BOOL32 IsNull()    {    return 0 == m_dwIpAddr;    }
private:
    u32 m_dwIpAddr;
    u8 m_byChnId;
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//mcu的mau使用状态
struct TMcuHdBasStatus
{
    TMcuHdBasStatus()
    {
        Clear();
    }

    //会控用
    BOOL32 GetConfMau(const CConfId &cConfId, 
                      u8 &byMauNum, u32 *pdwMau, u8 &byH263pMauNum, u32 *pdwH263pMau)
    {
        u8 byPos = 0xff;
        u8 byIdx = 0;

        if (!IsConfExist(cConfId, byPos))
        {
            return FALSE;
        }
        for(byIdx = 0; byIdx < MAXNUM_CONF_MAU; byIdx ++)
        {
            if (0 != m_aadwUsedMau[byPos][byIdx])
            {
                byMauNum++;
            }
        }

        if (!IsConfExist(cConfId, byPos))
        {
            return FALSE;
        }
        for(byIdx = 0; byIdx < MAXNUM_CONF_MAU; byIdx ++)
        {
            if (0 != m_aadwUsedH263pMau[byPos][byIdx])
            {
                byH263pMauNum++;
            }
        }
        return TRUE;
    }
    //会控用
    BOOL32 GetConfMpuChn(const CConfId &cConfId,
                         u8 &byChnNum, TMpuChn *ptMpuChn)
    {
        u8 byPos = 0xff;
        u8 byIdx = 0;
        
        if (!IsConfExist(cConfId, byPos))
        {
            return FALSE;
        }
        for(byIdx = 0; byIdx < MAXNUM_CONF_MPU; byIdx ++)
        {
            if (!m_aatUsedMpuChn[byPos][byIdx].IsNull())
            {
                byChnNum++;
            }
        }
        memcpy(ptMpuChn, m_aatUsedMpuChn, byChnNum*sizeof(TMpuChn));
        return TRUE;
    }

    //会控用
    BOOL32 GetIdleMau(u8 &byMauNum, u32 *pdwMau, u8 &byH263pMauNum, u32 *pdwH263pMau)
    {
        u8 byIdx = 0;

        for(byIdx = 0; byIdx < MAXNUM_PERIEQP; byIdx ++)
        {
            if (0 != m_adwIdleMau[byIdx])
            {
                byMauNum++;
            }
        }
        memcpy(pdwMau, &m_adwIdleMau, byMauNum);

        for(byIdx = 0; byIdx < MAXNUM_PERIEQP; byIdx ++)
        {
            if (0 != m_adwIdleH263pMau[byIdx])
            {
                byH263pMauNum++;
            }
        }
        memcpy(pdwMau, &m_adwIdleH263pMau, byH263pMauNum);

        return TRUE;
    }

    //会控用(注意: MPU的空闲资源以通道为单位描述)
    BOOL32 GetIdleMpuChn(u8 &byMpuChnNum, TMpuChn *ptMpuChn)
    {
        u8 byIdx = 0;
        
        for(byIdx = 0; byIdx < MAXNUM_PERIEQP*MAXNUM_MPU_CHN; byIdx ++)
        {
            if (!m_atIdleMpuChn[byIdx].IsNull())
            {
                byMpuChnNum++;
            }
        }
        memcpy(ptMpuChn, &m_atIdleMpuChn, byMpuChnNum);

        return TRUE;
    }

    //会控用（会议失败、模板警告/通知时 需求量这里获取）
    void GetCurMauNeeded(u8 &byMauNum, u8 &byH263pMauNum)
    {
        byMauNum = m_byCurMau;
        byH263pMauNum = m_byCurH263pMau;
        return;
    }

    //会控用（会议失败、模板警告/通知时 需求量这里获取）
    //注意: mpu资源需求程度以通道为单位描述，建议用户则以板卡为单位建议:4 chn/mpu
    void GetCurMpuChnNeeded(u8 &byChnNum)
    {
        byChnNum = m_byCurMpuChn;
        return;
    }

    //以下接口MCU使用

    void SetCurMauNeeded(u8 byMauNum, u8 byH263pMauNum)
    {
        m_byCurMau = byMauNum;
        m_byCurH263pMau = byH263pMauNum;
        return;
    }

    void SetCurMpuChnNeeded(u8 byMpuChn)
    {
        m_byCurMpuChn = byMpuChn;
        return;
    }

    void SetConfMau(const CConfId &cConfId, u32 dwMauIp, BOOL32 bH263p)
    {
        u8 byIdx = 0;
        u8 byPos = 0xff;
        u8 byFstIdlePos = 0xff;
        BOOL32 bExist = FALSE;
        BOOL32 bSet = FALSE;

        if (!bH263p)
        {
            if (IsConfExist(cConfId, byPos))
            {
                byFstIdlePos = 0xff;
                bExist = FALSE;
                for(; byIdx < MAXNUM_CONF_MAU; byIdx++)
                {
                    if (0 == m_aadwUsedMau[byPos][byIdx])
                    {
                        byFstIdlePos = byFstIdlePos == 0xff ? byIdx : byFstIdlePos;
                    }
                    if (dwMauIp == m_aadwUsedMau[byPos][byIdx])
                    {
                        bExist = TRUE;
                        break;
                    }
                }
                if (!bExist)
                {
                    if (0xff == byFstIdlePos)
                    {
                        OspPrintf(TRUE, FALSE, "[THdBasStatus][SetConfMau] no pos in ConfPos.%d\n", byPos);
                        return;
                    }
                    m_aadwUsedMau[byPos][byFstIdlePos] = dwMauIp;
                }
                return;
            }
            
            bSet = FALSE;
            for (byIdx = 0; byIdx < MAXNUM_ONGO_CONF; byIdx ++)
            {
                if (m_acConfId[byIdx].IsNull())
                {
                    m_acConfId[byIdx] = cConfId;
                    m_aadwUsedMau[byIdx][0] = dwMauIp;
                    bSet = TRUE;
                }
            }
            if (!bSet)
            {
                OspPrintf(TRUE, FALSE, "[THdBasStatus][SetConfMau] no pos for new conf!\n");
            }
            return;
        }

        //H263p相关
        if (IsConfExist(cConfId, byPos))
        {
            byFstIdlePos = 0xff;
            bExist = FALSE;
            for(; byIdx < MAXNUM_CONF_MAU; byIdx++)
            {
                if (0 == m_aadwUsedH263pMau[byPos][byIdx])
                {
                    byFstIdlePos = byFstIdlePos == 0xff ? byIdx : byFstIdlePos;
                }
                if (dwMauIp == m_aadwUsedH263pMau[byPos][byIdx])
                {
                    bExist = TRUE;
                    break;
                }
            }
            if (!bExist)
            {
                if (0xff == byFstIdlePos)
                {
                    OspPrintf(TRUE, FALSE, "[TMcuHdBasStatus][SetConfMau] no pos in ConfPos.%d(h263p)\n", byPos);
                    return;
                }
                m_aadwUsedH263pMau[byPos][byFstIdlePos] = dwMauIp;
            }
            return;
        }
        
        bSet = FALSE;
        for (byIdx = 0; byIdx < MAXNUM_ONGO_CONF; byIdx ++)
        {
            if (m_acConfId[byIdx].IsNull())
            {
                m_acConfId[byIdx] = cConfId;
                m_aadwUsedH263pMau[byIdx][0] = dwMauIp;
                bSet = TRUE;
            }
        }
        if (!bSet)
        {
            OspPrintf(TRUE, FALSE, "[TMcuHdBasStatus][SetConfMau] no pos for new conf(h263p)!\n");
        }
        return;
    }

    void SetConfMpuChn(const CConfId &cConfId, u32 dwMpuIp, u8 byChnId)
    {
        u8 byIdx = 0;
        u8 byPos = 0xff;
        u8 byFstIdlePos = 0xff;
        BOOL32 bExist = FALSE;

        if (IsConfExist(cConfId, byPos))
        {
            byFstIdlePos = 0xff;
            bExist = FALSE;
            for(; byIdx < MAXNUM_CONF_MPU; byIdx++)
            {
                if (m_aatUsedMpuChn[byPos][byIdx].IsNull())
                {
                    byFstIdlePos = byFstIdlePos == 0xff ? byIdx : byFstIdlePos;
                }
                if (dwMpuIp == m_aatUsedMpuChn[byPos][byIdx].GetIpAddr() &&
                    byChnId == m_aatUsedMpuChn[byPos][byIdx].GetChnId())
                {
                    bExist = TRUE;
                    break;
                }
            }
            if (!bExist)
            {
                if (0xff == byFstIdlePos)
                {
                    OspPrintf(TRUE, FALSE, "[TMcuHdBasStatus][SetConfMpuChn] no pos in ConfPos.%d\n", byPos);
                    return;
                }
                m_aatUsedMpuChn[byPos][byFstIdlePos].SetIpAddr(dwMpuIp);
                m_aatUsedMpuChn[byPos][byFstIdlePos].SetChnId(byChnId);
            }
            return;
        }

        BOOL32 bSet = FALSE;
        for (byIdx = 0; byIdx < MAXNUM_ONGO_CONF; byIdx ++)
        {
            if (m_acConfId[byIdx].IsNull())
            {
                m_acConfId[byIdx] = cConfId;
                m_aatUsedMpuChn[byIdx][0].SetIpAddr(dwMpuIp);
                m_aatUsedMpuChn[byIdx][0].SetChnId(byChnId);
                bSet = TRUE;
            }
        }
        if (!bSet)
        {
            OspPrintf(TRUE, FALSE, "[TMcuHdBasStatus][SetConfMpuChn] no pos for new conf!\n");
        }
        return;
    }

    void SetIdleMau(u32 dwMauIp, BOOL32 bH263p)
    {
        u8 byFstIdlePos = 0xff;
        BOOL32 bExist = FALSE;
        u8 byIdx = 0;
        if (!bH263p)
        {
            for(byIdx = 0; byIdx < MAXNUM_PERIEQP; byIdx++)
            {
                if (0 == m_adwIdleMau[byIdx])
                {
                    byFstIdlePos = byFstIdlePos == 0xff ? byIdx : byFstIdlePos;
                }
                if (dwMauIp == m_adwIdleMau[byIdx])
                {
                    bExist = TRUE;
                    break;
                }
            }
            if (!bExist)
            {
                if (0xff == byFstIdlePos)
                {
                    OspPrintf(TRUE, FALSE, "[TMcuHdBasStatus][SetIdleMau] no pos for new mau!\n");
                    return;
                }
                m_adwIdleMau[byFstIdlePos] = dwMauIp;
            }
            return;
        }
        
        byFstIdlePos = 0xff;
        bExist = FALSE;
        for(byIdx = 0; byIdx < MAXNUM_PERIEQP; byIdx++)
        {
            if (0 == m_adwIdleH263pMau[byIdx])
            {
                byFstIdlePos = byFstIdlePos == 0xff ? byIdx : byFstIdlePos;
            }
            if (dwMauIp == m_adwIdleH263pMau[byIdx])
            {
                bExist = TRUE;
                break;
            }
        }
        if (!bExist)
        {
            if (0xff == byFstIdlePos)
            {
                OspPrintf(TRUE, FALSE, "[TMcuHdBasStatus][SetIdleMau] no pos for new mau(H263p)!\n");
                return;
            }
            m_adwIdleH263pMau[byFstIdlePos] = dwMauIp;
        }
        return;
    }

    void SetIdleMpuChn(u32 dwMpuIp, u8 byChnId)
    {
        u8 byFstIdlePos = 0xff;
        BOOL32 bExist = FALSE;
        u8 byIdx = 0;

        for(byIdx = 0; byIdx < MAXNUM_PERIEQP*MAXNUM_MPU_CHN; byIdx++)
        {
            if (m_atIdleMpuChn[byIdx].IsNull())
            {
                byFstIdlePos = byFstIdlePos == 0xff ? byIdx : byFstIdlePos;
            }
            if (dwMpuIp == m_atIdleMpuChn[byIdx].GetIpAddr() &&
                byChnId == m_atIdleMpuChn[byIdx].GetChnId() )
            {
                bExist = TRUE;
                break;
            }
        }
        if (!bExist)
        {
            if (0xff == byFstIdlePos)
            {
                OspPrintf(TRUE, FALSE, "[TMcuHdBasStatus][SetIdleMpuChn] no pos for new mau!\n");
                return;
            }
            m_atIdleMpuChn[byFstIdlePos].SetIpAddr(dwMpuIp);
            m_atIdleMpuChn[byFstIdlePos].SetChnId(byChnId);
        }
        return;
    }


    void Clear(void)
    {
        memset(m_acConfId, 0, sizeof(m_acConfId));
        memset(m_aadwUsedMau, 0, sizeof(m_aadwUsedMau));
        memset(m_adwIdleMau, 0, sizeof(m_adwIdleMau));
        memset(m_aadwUsedH263pMau, 0, sizeof(m_aadwUsedH263pMau));
        memset(m_adwIdleH263pMau, 0, sizeof(m_adwIdleH263pMau));
        m_byCurMau = 0;
        m_byCurH263pMau = 0;
    }

private:
    BOOL32 IsConfExist(const CConfId &cConfId, u8 &byPos)
    {
        byPos = 0xff;
        BOOL32 bExist = FALSE;
        for(u8 byIdx = 0; byIdx < MAXNUM_ONGO_CONF; byIdx ++)
        {
            if (m_acConfId[byIdx].IsNull())
            {
                continue;
            }
            if (m_acConfId[byIdx] == cConfId)
            {
                bExist = TRUE;
                byPos = byIdx;
                break;
            }
        }
        return bExist;
    }

private:
    CConfId m_acConfId[MAXNUM_ONGO_CONF];

    u32     m_aadwUsedMau[MAXNUM_ONGO_CONF][MAXNUM_CONF_MAU];
    u32     m_aadwUsedH263pMau[MAXNUM_ONGO_CONF][MAXNUM_CONF_MAU];
    TMpuChn m_aatUsedMpuChn[MAXNUM_ONGO_CONF][MAXNUM_CONF_MPU];
    
    u32     m_adwIdleMau[MAXNUM_PERIEQP];
    u32     m_adwIdleH263pMau[MAXNUM_PERIEQP];
    TMpuChn m_atIdleMpuChn[MAXNUM_PERIEQP*MAXNUM_MPU_CHN];

    u8      m_byCurMau;
    u8      m_byCurH263pMau;
    u8      m_byCurMpuChn;
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

/*****************************************************************
 *
 *
 *                         用户管理扩展
 *
 *
 *****************************************************************/
class CExUsrInfo: public CUserFullInfo
{
public:
    CExUsrInfo() {};

    CExUsrInfo(const CExUsrInfo &newInfo)
    {
        memcpy( this, &newInfo, sizeof(CUserFullInfo) );
    }

    CExUsrInfo(const CUserFullInfo &newInfo)
    {
        memcpy( this, &newInfo, sizeof(CUserFullInfo) );
    }

    const CExUsrInfo& operator=(const CExUsrInfo& newInfo)
    {
        if (this == &newInfo)
        {
            return *this;
        }

        memcpy( this, &newInfo, sizeof(CExUsrInfo) );

        return (*this);
    }

    BOOL32 operator == (const CExUsrInfo& newInfo)
    {
        return ( memcmp(this, &newInfo, sizeof(CExUsrInfo)) == 0 );
    }

    // 重载的用户描述和组Id操作。MCS必须使用这里提供的方法

	//得到用户描述
	char* GetDiscription()
	{
		return (discription+1);
	}
	
	//设置用户描述
	void SetDiscription(char* buf)
	{
		if(buf == NULL)
        {
            return;
        }
        u8 byGrpId = discription[0];
		memset(discription, 0, 2 * MAX_CHARLENGTH);

        s32 length = (strlen(buf) >= 2*MAX_CHARLENGTH - 2 ? 2*MAX_CHARLENGTH - 2: strlen(buf));
		strncpy(discription+1, buf, length);

		discription[2*MAX_CHARLENGTH-1] = '\0';
        discription[0] = byGrpId;
	}
    void SetUsrGrpId( u8 byGrdId )
    {
        discription[0] = byGrdId;
    }
    u8 GetUsrGrpId()
    {
        return discription[0];
    }

    void Print( void )
    {
        OspPrintf(TRUE, FALSE, "name:%s actor:%d fullname:%s des:%s\n",
                  GetName(), GetActor(), GetFullName(), GetDiscription());
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;


// Ip地址段，网络序
struct TIpSeg
{    
public:
	u32 dwIpStart;
	u32 dwIpEnd;

    u8  byEnabled;

public:
    TIpSeg()
    {
        SetNull();
    }

    // 输入地址要求为网络序
    void SetSeg( u32 dwStart, u32 dwEnd)    
    {
        byEnabled = 1;
        dwIpStart = dwStart;
        dwIpEnd = dwEnd;
    }
    BOOL32 IsEnabled() const
    {
        return ( byEnabled == 1 ? TRUE : FALSE);
    }

    // 返回地址为网络序
    BOOL32 GetSeg ( u32& dwStart, u32& dwEnd ) const 
    {
        dwStart = dwIpStart;
        dwEnd   = dwIpEnd;
        return IsEnabled();
    }
    void SetNull()
    {
        memset(this, 0, sizeof(TIpSeg));
    }

    // 某个Ip是否在本段内。地址要求是网络序
    BOOL32 IsIpIn(u32 dwIp) const 
    {
        u32 dwMin = dwIpStart;
        u32 dwMax = dwIpEnd;
        u32 dwTmp = 0;
        if (dwMin > dwMax)
        {
            dwTmp = dwMin;
            dwMin = dwMax;
            dwMax = dwTmp;
        }
        if (dwIp >= dwMin && dwIp <= dwMax )    
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }

    // 另外一个Ip段是否在本段内
    BOOL32 IsIpSegIn( const TIpSeg tAnother ) const
    {
        return ( IsIpIn(tAnother.dwIpStart)  &&
                 IsIpIn(tAnother.dwIpEnd) );
    }
}

#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

/* add by wangliang 2006-12-20 for E164  start */
/*
// E164号码段
struct TE164Seg
{
public:
    s8 szE164Start[MAXLEN_E164+1];
    s8 szE164End[MAXLEN_E164+1];
    u8 byEnabled;

public:
    TE164Seg()
    {
        SetNull();
    }

    // 取得E164号码段
    void SetSeg(LPCSTR pszStart, LPCSTR pszEnd)
    {
        byEnabled = 1;
        if(pszStart != NULL && pszEnd != NULL)
        {
            memset(szE164Start, 0, sizeof(szE164Start));
            memset(szE164End, 0, sizeof(szE164End));
            strncpy(szE164Start, pszStart, MAXLEN_E164);
            strncpy(szE164End, pszEnd, MAXLEN_E164);
        }
        return;
    }

    BOOL32 IsEnabled() const
    {
        return (byEnabled == 1 ? TRUE : FALSE);
    }

    // 返回E164号码段
    BOOL32 GetSeg(s8 *pszStart, s8 *pszEnd) const 
    {
        strncpy(pszStart, szE164Start, MAXLEN_E164);
        strncpy(pszEnd, szE164End, MAXLEN_E164);
        return IsEnabled();
    }

    // 结构置空
    void SetNull()
    {
        memset(this, 0, sizeof(TE164Seg));
    }

    // E164号码是否在本E164号码段内
    // FIXME: 如果pszE164与szE164Start或szE164End长度不同，则不能够严格判断是否在段内
    BOOL32 IsE164In(LPCSTR pszE164) const
    {
        if(strncmp(szE164Start, szE164End, MAXLEN_E164) < 0)
        {
            if(strncmp(pszE164, szE164Start, MAXLEN_E164) >= 0 
                && strncmp(pszE164, szE164End, MAXLEN_E164) <= 0)
                return TRUE;
            else
                return FALSE;
        }
        else
        {
            if(strncmp(pszE164, szE164End, MAXLEN_E164) >= 0 
                && strncmp(pszE164, szE164Start, MAXLEN_E164) <= 0)
                return TRUE;
            else
                return FALSE;
        }  
    }
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;
*/
/* add by wangliang 2006-12-20 for E164  end */

// 用户组信息
struct TUsrGrpInfo
{
public:
    TUsrGrpInfo()
    {
        SetNull();
    }

public:
    void SetNull()
    {
        memset ( this, 0, sizeof(TUsrGrpInfo) );
        SetBanned(TRUE);    // 默认是禁止
    }
    // 判断本用户组是否为空
    BOOL32 IsFree() const
    {
        return (byGrpId == 0);
    }
    // 设置/获取用户组ID
    void SetUsrGrpId(u8 byId)
    {
        byGrpId = byId;
    }
    u8 GetUsrGrpId() const
    {
        return byGrpId;
    }
    // 设置/获取用户组名
    void SetUsrGrpName(LPCSTR lpszName)
    {
        memset(szName, 0, MAX_CHARLENGTH);
        strncpy(szName, lpszName, MAX_CHARLENGTH-1);
    }
    LPCSTR GetUsrGrpName() const
    {
        return szName;
    }
    // 设置/获取用户组描述
    void SetUsrGrpDesc(LPCSTR lpszDesc)
    {
        memset(szDesc, 0, 2*MAX_CHARLENGTH);
        strncpy(szDesc, lpszDesc, 2*MAX_CHARLENGTH-1);
    }
    LPCSTR GetUsrGrpDesc() const
    {
        return szDesc;
    }
    void SetMaxUsrNum(u8 byMaxNum)
    {
        byMaxUsrNum = byMaxNum;
    }
    u8 GetMaxUsrNum() const
    {
        return byMaxUsrNum;
    }
    void SetBanned(BOOL32 bIsBanned)
    {
        bBanned = bIsBanned ? 1 : 0;
    }
    BOOL32 IsBanned() const
    {
        return bBanned ? TRUE : FALSE;
    }

    // 判断终端IP是否在合法段内，
    // 输入地址是网络序
    inline BOOL32 IsMtIpInAllowSeg(u32 dwIp) const;

    void Print() const
    {
        if ( IsFree() )
        {            
            OspPrintf( TRUE, FALSE, "\tGroup ID: FREE\n" );
            return;
        }        
        OspPrintf( TRUE, FALSE, "\tGroup ID: %d\n", byGrpId );
        OspPrintf( TRUE, FALSE, "\tName: %s\n", szName);
        OspPrintf( TRUE, FALSE, "\tDesc: %s\n", szDesc);
        OspPrintf( TRUE, FALSE, "\tMax User: %d\n", byMaxUsrNum);

        OspPrintf( TRUE, FALSE, "\tIP Ranges: %s\n", bBanned ? "Banned" : "Allowed");
        for (s32 nLoop = 0; nLoop < MAXNUM_IPSEG; nLoop ++)
        {
            OspPrintf( TRUE, FALSE, "\t\tNo.%d: Enabled: %d IP: 0x%x -- 0x%x\n", 
                       nLoop,
                       atIpSeg[nLoop].IsEnabled(), 
                       atIpSeg[nLoop].dwIpStart, 
                       atIpSeg[nLoop].dwIpEnd );
        }        
    }

protected:
	u8      byGrpId;
	s8      szName[MAX_CHARLENGTH];
	s8      szDesc[2*MAX_CHARLENGTH];
	u8      byMaxUsrNum;
public:
    TIpSeg  atIpSeg[MAXNUM_IPSEG];  // 地址是网络序
    u8      bBanned;     // 0 - 表示指定段是允许, 1 - 表示是禁止
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// VCS用户信息，增加了操作调度席任务分配
class CVCSUsrInfo: public CExUsrInfo
{
public:
	CVCSUsrInfo()
	{
		SetNull();
	}

    ~CVCSUsrInfo() {};

    void SetNull()
	{
		m_wTaskNum = 0;
		memset(m_cTaskID, 0, sizeof(CConfId) * MAXNUM_MCU_VCCONF);
	}

	// 指定该用户的调度任务
	BOOL AssignTask(u16 wTaskNum, const CConfId* pConfID)
	{
		if (pConfID == NULL)
		{
			return FALSE;
		}

		SetNull();
		m_wTaskNum = htons(wTaskNum);
		memcpy(m_cTaskID, pConfID, sizeof(CConfId) * wTaskNum);
		return TRUE;
	}

	// 获取该用户的调度任务
	const CConfId* GetTask() const
	{
		return m_cTaskID;
	}
	u16 GetTaskNum() const
	{
		return ntohs(m_wTaskNum);
	}

	// 任务是否在指定任务范围类
	BOOL IsYourTask(CConfId cTaskID)
	{
		BOOL dwIsYourTask = FALSE;
		for (u16 wIndex = 0; wIndex < MAXNUM_MCU_VCCONF; wIndex++)
		{
			if (cTaskID == m_cTaskID[wIndex])
			{
				dwIsYourTask = TRUE;
				break;
			}
		}
		return dwIsYourTask;
	}

protected:
    u16     m_wTaskNum;
	CConfId m_cTaskID[ MAXNUM_MCU_VCCONF ];
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

/*-------------------------------------------------------------------
                               CServMsg                              
--------------------------------------------------------------------*/

/*====================================================================
    函数名      ：CServMsg
    功能        ：constructor
    算法实现    ：
    引用全局变量：
    输入参数说明：
    返回值说明  ：
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/15    1.0         LI Yi         创建
====================================================================*/
inline CServMsg::CServMsg( void )
{
	Init();
}

/*====================================================================
    函数名      ：CServMsg
    功能        ：constructor
    算法实现    ：
    引用全局变量：
    输入参数说明：u8 * const pbyMsg, 要赋值的消息指针
				  u16 wMsgLen, 要赋值的消息长度，必须大于等于 SERV_MSGHEAD_LEN
    返回值说明  ：
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/15    1.0         LI Yi         创建
====================================================================*/
inline CServMsg::CServMsg( u8 * const pbyMsg, u16 wMsgLen )
{
	Init();
	
	if( wMsgLen < SERV_MSGHEAD_LEN || pbyMsg == NULL )
		return;
	
	wMsgLen = min( wMsgLen, SERV_MSG_LEN );
	memcpy( this, pbyMsg, wMsgLen );
	
	//set length
	SetMsgBodyLen( wMsgLen - SERV_MSGHEAD_LEN );
}

/*====================================================================
    函数名      ：~CServMsg
    功能        ：distructor
    算法实现    ：
    引用全局变量：
    输入参数说明：
    返回值说明  ：
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/15    1.0         LI Yi         创建
====================================================================*/
inline CServMsg::~CServMsg( void )
{

}

/*====================================================================
    函数名      ：Init
    功能        ：BUFFER初始化
    算法实现    ：
    引用全局变量：
    输入参数说明：
    返回值说明  ：
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/15    1.0         LI Yi         创建
====================================================================*/
inline void CServMsg::Init( void )
{
	memset( this, 0, SERV_MSG_LEN );	//清零
}

/*====================================================================
    函数名      ：ClearHdr
    功能        ：消息头清零
    算法实现    ：
    引用全局变量：
    输入参数说明：
    返回值说明  ：
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/15    1.0         LI Yi         创建
====================================================================*/
inline void CServMsg::ClearHdr( void )
{
	u16		wBodyLen = GetMsgBodyLen();

	memset( this, 0, SERV_MSGHEAD_LEN );	//清零
	SetMsgBodyLen( wBodyLen );
}

/*====================================================================
    函数名      ：GetConfId
    功能        ：获取会议号信息
    算法实现    ：
    引用全局变量：
    输入参数说明：无
    返回值说明  ：会议号，全0表示创建
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/15    1.0         LI Yi         创建
    02/12/24    1.0         LI Yi         修改接口
====================================================================*/
inline CConfId CServMsg::GetConfId( void ) const
{
	return( m_cConfId );
}

/*====================================================================
    函数名      ：SetConfId
    功能        ：设置会议号信息
    算法实现    ：
    引用全局变量：
    输入参数说明：const CConfId & cConfId，会议号，全0表示创建
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/15    1.0         LI Yi         创建
    02/12/24    1.0         LI Yi         修改接口
====================================================================*/
inline void CServMsg::SetConfId( const CConfId & cConfId )
{
	m_cConfId = cConfId;
}

/*====================================================================
    函数名      ：SetNullConfId
    功能        ：设置会议号信息为空
    算法实现    ：
    引用全局变量：
    输入参数说明：无
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    03/06/06    1.0         LI Yi         创建
====================================================================*/
inline void CServMsg::SetNullConfId( void )
{
	CConfId		cConfId;
	
	cConfId.SetNull();
	SetConfId( cConfId );
}

/*====================================================================
    函数名      ：GetMsgBodyLen
    功能        ：获取消息体长度信息
    算法实现    ：
    引用全局变量：
    输入参数说明：无
    返回值说明  ：消息体长度
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/15    1.0         LI Yi         创建
====================================================================*/
inline u16 CServMsg::GetMsgBodyLen( void ) const
{
	return( ntohs( m_wMsgBodyLen ) );
}

/*====================================================================
    函数名      ：SetMsgBodyLen
    功能        ：设置消息体长度信息
    算法实现    ：
    引用全局变量：
    输入参数说明：u16 wMsgBodyLen, 消息体长度
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/15    1.0         LI Yi         创建
====================================================================*/
inline void CServMsg::SetMsgBodyLen( u16 wMsgBodyLen )
{
	m_wMsgBodyLen = htons( wMsgBodyLen );
}

/*====================================================================
    函数名      ：GetMsgBody
    功能        ：获取消息体指针，用户不需提供BUFFER
    算法实现    ：
    引用全局变量：
    输入参数说明：无
    返回值说明  ：u8 * const指针
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/15    1.0         LI Yi         创建
====================================================================*/
inline u8 * const CServMsg::GetMsgBody( void ) const
{
	return( ( u8 * const )m_abyMsgBody );
}

/*====================================================================
    函数名      ：GetMsgBodyLen
    功能        ：获取整个消息长度
    算法实现    ：
    引用全局变量：
    输入参数说明：无
    返回值说明  ：整个消息长度
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/26    1.0         LI Yi         创建
====================================================================*/
inline u16 CServMsg::GetServMsgLen( void ) const
{
	return( GetMsgBodyLen() + SERV_MSGHEAD_LEN );
}

/*====================================================================
    函数名      ：GetMsgBody
    功能        ：获取消息体，由用户申请BUFFER，如果过小做截断处理
    算法实现    ：
    引用全局变量：
    输入参数说明：u8 * pbyMsgBodyBuf, 返回的消息体
				  u16 wBufLen, BUFFER大小
    返回值说明  ：实际返回的消息体长度
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/15    1.0         LI Yi         创建
====================================================================*/
inline u16 CServMsg::GetMsgBody( u8 * pbyMsgBodyBuf, u16 wBufLen ) const
{
    u16 wActLen = min( GetMsgBodyLen(), wBufLen );
	memcpy( pbyMsgBodyBuf, m_abyMsgBody, wActLen );
	return wActLen;
}

/*====================================================================
    函数名      ：SetMsgBody
    功能        ：设置消息体
    算法实现    ：
    引用全局变量：
    输入参数说明：u8 * const pbyMsgBody, 传入的消息体，缺省为NULL
				  u16 wLen, 传入的消息体长度，缺省为0
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/15    1.0         LI Yi         创建
====================================================================*/
inline void CServMsg::SetMsgBody( u8 * const pbyMsgBody, u16 wLen )
{
    /*
    if (pbyMsgBody == NULL || wLen == 0)
    {
        SetMsgBodyLen( 0 );
        return;
    }
    */
	wLen = min( wLen, SERV_MSG_LEN - SERV_MSGHEAD_LEN );
	memcpy( m_abyMsgBody, pbyMsgBody, wLen );
	SetMsgBodyLen( wLen );
}

/*====================================================================
    函数名      ：CatMsgBody
    功能        ：添加消息体
    算法实现    ：
    引用全局变量：
    输入参数说明：u8 * const pbyMsgBody, 传入的消息体，缺省为NULL
				  u16 wLen, 传入的消息体长度，缺省为0
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/11/07    1.0         Liaoweijiang  创建
====================================================================*/
inline void CServMsg::CatMsgBody( u8 * const pbyMsgBody, u16 wLen )
{
    /*
    if (pbyMsgBody == NULL || wLen == 0)
    {
        return;
    }
    */
	wLen = min( wLen, SERV_MSG_LEN - SERV_MSGHEAD_LEN - GetMsgBodyLen() );
	memcpy( m_abyMsgBody + GetMsgBodyLen(), pbyMsgBody, wLen );
	SetMsgBodyLen( GetMsgBodyLen() + wLen );
}

/*====================================================================
    函数名      ：GetMsgBody
    功能        ：获取整个消息指针，用户不需提供BUFFER
    算法实现    ：
    引用全局变量：
    输入参数说明：无
    返回值说明  ：u8 * const指针
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/26    1.0         LI Yi         创建
====================================================================*/
inline u8 * const CServMsg::GetServMsg( void ) const
{
	return( ( u8 * const )( this ) );
}

/*====================================================================
    函数名      ：GetServMsg
    功能        ：获取整个消息，由用户申请BUFFER，如果过小做截断处理
    算法实现    ：
    引用全局变量：
    输入参数说明：u8 * pbyMsgBuf, 返回的消息
				  u16 wBufLen, BUFFER大小
    返回值说明  ：实际返回的消息长度
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/15    1.0         LI Yi         创建
====================================================================*/
inline u16 CServMsg::GetServMsg( u8 * pbyMsgBuf, u16 wBufLen ) const
{
	wBufLen = min(SERV_MSG_LEN,wBufLen);
	memcpy( pbyMsgBuf, this, wBufLen );
	return( min( GetMsgBodyLen() + SERV_MSGHEAD_LEN, wBufLen ) );
}

/*====================================================================
    函数名      ：SetServMsg
    功能        ：设置整个消息
    算法实现    ：
    引用全局变量：
    输入参数说明：u8 * const pbyMsg, 传入的整个消息
				  u16 wMsgLen, 传入的消息长度
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/15    1.0         LI Yi         创建
====================================================================*/
inline void CServMsg::SetServMsg( u8 * const pbyMsg, u16 wMsgLen )
{
	if( wMsgLen < SERV_MSGHEAD_LEN )
	{
		OspPrintf( TRUE, FALSE, "CServMsg: SetServMsg() Exception -- invalid MsgLen!\n" );
		return;
	}

	wMsgLen = min( wMsgLen, SERV_MSG_LEN );
	memcpy( this, pbyMsg, wMsgLen );
	SetMsgBodyLen( wMsgLen - SERV_MSGHEAD_LEN );
}

/*====================================================================
    函数名      ：operator=
    功能        ：操作符重载
    算法实现    ：
    引用全局变量：
    输入参数说明：CServMsg & cServMsg, 赋值的消息引用
    返回值说明  ：CServMsg对象应用
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/26    1.0         LI Yi         创建
====================================================================*/
inline const CServMsg & CServMsg::operator= ( const CServMsg & cServMsg )
{
	u16	wLen = cServMsg.GetServMsgLen();

	memcpy( this, cServMsg.GetServMsg(), wLen );
	return( *this );
}

/*-------------------------------------------------------------------
                               TConfMtInfo                           
--------------------------------------------------------------------*/

/*====================================================================
    函数名      ：TConfMtInfo
    功能        ：constructor
    算法实现    ：
    引用全局变量：
    输入参数说明：无
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/30    1.0         LI Yi         创建
====================================================================*/
inline TConfMtInfo::TConfMtInfo( void )
{
	memset( this, 0, sizeof( TConfMtInfo ) );
}

/*====================================================================
    函数名      ：MtInConf
    功能        ：判断该MCU下某终端是否在受邀终端列表中
    算法实现    ：
    引用全局变量：
    输入参数说明：u8 byMtId, 终端号
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/30    1.0         LI Yi         创建
====================================================================*/
inline BOOL TConfMtInfo::MtInConf( u8 byMtId ) const
{
	if( byMtId == 0 || byMtId > MAXNUM_CONF_MT)return FALSE;
	return ( ( m_abyMt[(byMtId-1) / 8] & ( 1 << ( (byMtId-1) % 8 ) ) ) != 0 );
}

/*====================================================================
    函数名      ：MtJoinedConf
    功能        ：判断该MCU下某终端是否在与会终端列表中
    算法实现    ：
    引用全局变量：
    输入参数说明：u8 byMtId, 终端号
    返回值说明  ：TRUE/FALSE
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/12/24    1.0         LI Yi         创建
====================================================================*/
inline BOOL TConfMtInfo::MtJoinedConf( u8 byMtId ) const
{
	if( byMtId == 0 || byMtId > MAXNUM_CONF_MT) return FALSE;
	return ( ( m_abyJoinedMt[(byMtId-1) / 8] & ( 1 << ( (byMtId-1) % 8 ) ) ) != 0 );
}

/*====================================================================
    函数名      ：AddMt
    功能        ：增加该MCU下终端于受邀终端列表中
    算法实现    ：
    引用全局变量：
    输入参数说明：u8 byMtId, 终端号
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/30    1.0         LI Yi         创建
====================================================================*/
inline void TConfMtInfo::AddMt( u8 byMtId )
{
	if( byMtId == 0 || byMtId > MAXNUM_CONF_MT)return;
	m_abyMt[(byMtId-1) / 8] |= 1 << ( (byMtId-1) % 8 );
}

/*====================================================================
    函数名      ：AddJoinedMt
    功能        ：增加该MCU下终端于与会终端列表中，该函数自动将该终端也
	              加入到受邀终端列表中
    算法实现    ：
    引用全局变量：
    输入参数说明：u8 byMtId, 终端号
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/12/25    1.0         LI Yi         创建
====================================================================*/
inline void TConfMtInfo::AddJoinedMt( u8 byMtId )
{
	if( byMtId == 0 || byMtId > MAXNUM_CONF_MT)return;
	m_abyJoinedMt[(byMtId-1) / 8] |= 1 << ( (byMtId-1) % 8 );
	m_abyMt[(byMtId-1) / 8] |= 1 << ( (byMtId-1) % 8 );
}

/*====================================================================
    函数名      ：RemoveMt
    功能        ：删除该MCU下终端于受邀终端列表中，该函数自动将该终端也
	              删除出与会终端列表中
    算法实现    ：
    引用全局变量：
    输入参数说明：u8 byMtId, 终端号
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/30    1.0         LI Yi         创建
====================================================================*/
inline void TConfMtInfo::RemoveMt( u8 byMtId )
{
	if( byMtId == 0 || byMtId > MAXNUM_CONF_MT)return;
	m_abyMt[(byMtId-1) / 8] &= ~( 1 << ( (byMtId-1) % 8 ) );
	m_abyJoinedMt[(byMtId-1) / 8] &= ~( 1 << ( (byMtId-1) % 8 ) );
}

/*====================================================================
    函数名      ：RemoveJoinedMt
    功能        ：删除该MCU下终端于与会终端列表中
    算法实现    ：
    引用全局变量：
    输入参数说明：u8 byMtId, 终端号
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/12/25    1.0         LI Yi         创建
====================================================================*/
inline void TConfMtInfo::RemoveJoinedMt( u8 byMtId )
{
	if( byMtId == 0 || byMtId > MAXNUM_CONF_MT)return;
	m_abyJoinedMt[(byMtId-1) / 8] &= ~( 1 << ( (byMtId-1) % 8 ) );
}

/*====================================================================
    函数名      ：RemoveAllMt
    功能        ：删除该MCU下所有终端于受邀终端列表中，该函数自动将所有终端也
	              删除出与会终端列表中
    算法实现    ：
    引用全局变量：
    输入参数说明：无
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/30    1.0         LI Yi         创建
====================================================================*/
inline void TConfMtInfo::RemoveAllMt( void )
{
	memset( m_abyMt, 0, sizeof( m_abyMt ) );
	memset( m_abyJoinedMt, 0, sizeof( m_abyMt ) );
}

/*====================================================================
    函数名      ：RemoveAllJoinedMt
    功能        ：删除该MCU下所有终端于与会终端列表中
    算法实现    ：
    引用全局变量：
    输入参数说明：无
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/12/25    1.0         LI Yi         创建
====================================================================*/
inline void TConfMtInfo::RemoveAllJoinedMt( void )
{
	memset( m_abyJoinedMt, 0, sizeof( m_abyMt ) );
}

/*====================================================================
    函数名      ：GetAllMtNum
    功能        ：得到一个结构中所有受邀终端个数
    算法实现    ：
    引用全局变量：
    输入参数说明：无
    返回值说明  ：会议中受邀终端个数
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/08/02    1.0         LI Yi         创建
====================================================================*/
inline u8 TConfMtInfo::GetAllMtNum( void ) const
{
	u8	byMtNum = 0;

	for( u8 byLoop = 0; byLoop < MAXNUM_CONF_MT; byLoop++ )
	{
		if( MtInConf( byLoop + 1 ) )
		{
			byMtNum++;
		}
	}

	return( byMtNum );
}

/*====================================================================
    函数名      ：GetLocalJoinedMtNum
    功能        ：得到一个结构中所有与会终端个数
    算法实现    ：
    引用全局变量：
    输入参数说明：无
    返回值说明  ：会议中与会终端个数
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/12/25    1.0         LI Yi         创建
====================================================================*/
inline u8 TConfMtInfo::GetAllJoinedMtNum( void ) const
{
	u8	byMtNum = 0;

	for( u8 byLoop = 0; byLoop < MAXNUM_CONF_MT; byLoop++ )
	{
		if( MtJoinedConf( byLoop + 1 ) )
		{
			byMtNum++;
		}
	}

	return( byMtNum );
}

/*====================================================================
    函数名      ：GetLocalUnjoinedMtNum
    功能        ：得到一个结构中所有未与会终端个数
    算法实现    ：
    引用全局变量：
    输入参数说明：无
    返回值说明  ：会议中未与会终端个数
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/12/25    1.0         LI Yi         创建
====================================================================*/
inline u8 TConfMtInfo::GetAllUnjoinedMtNum( void ) const
{
	return( GetAllMtNum() - GetAllJoinedMtNum() );
}

/*==============================================================================
函数名    :  GetMaxMtIdInConf
功能      :  得到一个结构中受邀终端中MTId最大的Id值
算法实现  :  
参数说明  :  
返回值说明:  
-------------------------------------------------------------------------------
修改记录  :  
日  期       版本          修改人          走读人          修改记录
2008-12-24					薛亮							创建
==============================================================================*/
inline u8 TConfMtInfo::GetMaxMtIdInConf( void ) const
{
	u8	byMaxMtId= 0;
	
	for( u8 byLoop = 0; byLoop < MAXNUM_CONF_MT; byLoop++ )
	{
		if( MtInConf( byLoop + 1 ) )
		{
			byMaxMtId = byLoop + 1;
		}
	}
	
	return( byMaxMtId );
}


/*-------------------------------------------------------------------
                           TConfAllMtInfo                          
--------------------------------------------------------------------*/

/*====================================================================
    函数名      ：AddMt
    功能        ：会议中增加一个受邀终端
    算法实现    ：
    引用全局变量：
    输入参数说明：u8 byMtId, 终端号
    返回值说明  ：成功返回TRUE，否则FALSE
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/31    1.0         LI Yi         创建
====================================================================*/
inline BOOL TConfAllMtInfo::AddMt(u8 byMtId )
{
	if(byMtId>=MAXNUM_CONF_MT)return FALSE;
	m_tLocalMtInfo.AddMt( byMtId );
	return TRUE;
}

/*====================================================================
    函数名      ：AddJoinedMt 
    功能        ：会议中增加一个与会终端，该函数自动将该终端也
	              加入到受邀终端列表中
    算法实现    ：
    引用全局变量：
    输入参数说明：u8 byMtId, 终端号
    返回值说明  ：成功返回TRUE，否则FALSE
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/12/30    1.0         LI Yi         创建
====================================================================*/
inline BOOL TConfAllMtInfo::AddJoinedMt(u8 byMtId )
{
    if(byMtId>=MAXNUM_CONF_MT)return FALSE;
	m_tLocalMtInfo.AddJoinedMt( byMtId );
	m_tLocalMtInfo.AddMt( byMtId );
	return TRUE;
}

/*====================================================================
    函数名      ：RemoveMt
    功能        ：会议中删除一个受邀终端，该函数自动将该终端也
	              删除出与会终端列表中
    算法实现    ：
    引用全局变量：
    输入参数说明：u8 byMtId, 终端号
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/31    1.0         LI Yi         创建
====================================================================*/
inline void TConfAllMtInfo::RemoveMt(u8 byMtId )
{
    if(byMtId>=MAXNUM_CONF_MT)return;	
	m_tLocalMtInfo.RemoveMt( byMtId );
	m_tLocalMtInfo.RemoveJoinedMt( byMtId );
}

/*====================================================================
    函数名      ：RemoveJoinedMt
    功能        ：会议中删除一个与会终端
    算法实现    ：
    引用全局变量：
    输入参数说明：u8 byMtId, 终端号
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/12/30    1.0         LI Yi         创建
====================================================================*/
inline void TConfAllMtInfo::RemoveJoinedMt( u8 byMtId )
{
	if(byMtId>=MAXNUM_CONF_MT)return;
	m_tLocalMtInfo.RemoveJoinedMt( byMtId );
}

/*====================================================================
    函数名      ：RemoveAllMt
    功能        ：会议中删除一个MCU下所有受邀终端（不删除MCU），该函数
	              自动将所有终端也删除出与会终端列表中
    算法实现    ：
    引用全局变量：
    输入参数说明：
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/31    1.0         LI Yi         创建
====================================================================*/
inline void TConfAllMtInfo::RemoveAllMt( void )
{
	m_tLocalMtInfo.RemoveAllMt();
	m_tLocalMtInfo.RemoveAllJoinedMt();
}

/*====================================================================
    函数名      ：RemoveAllJoinedMt
    功能        ：会议中删除一个MCU下所有与会终端（不删除MCU）
    算法实现    ：
    引用全局变量：
    输入参数说明：u16 wMcuId, MCU号
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/12/30    1.0         LI Yi         创建
====================================================================*/
inline void TConfAllMtInfo::RemoveAllJoinedMt( void )
{
	m_tLocalMtInfo.RemoveAllJoinedMt();
}

/*====================================================================
    函数名      ：MtInConf
    功能        ：判断终端是否在受邀终端列表中
    算法实现    ：
    引用全局变量：
    输入参数说明：u8 byMtId, 终端号
    返回值说明  ：TRUE/FALSE
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/08/01    1.0         LI Yi         创建
====================================================================*/
inline BOOL TConfAllMtInfo::MtInConf(u8 byMtId ) const
{
	return m_tLocalMtInfo.MtInConf( byMtId );
}

/*====================================================================
    函数名      ：MtJoinedConf
    功能        ：判断终端是否在与会终端列表中
    算法实现    ：
    引用全局变量：
    输入参数说明：u16 wMcuId, MCU号
				  u8 byMtId, 终端号
    返回值说明  ：TRUE/FALSE
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/12/30    1.0         LI Yi         创建
====================================================================*/
inline BOOL TConfAllMtInfo::MtJoinedConf(u8 byMtId ) const
{
	return m_tLocalMtInfo.MtJoinedConf( byMtId );
}

/*==============================================================================
函数名    : MtJoinedConf 
功能      : 判断终端是否在与会终端列表中(包括下级MCU下的某终端)
算法实现  :  
参数说明  :  TMt tMt
返回值说明:  BOOL
-------------------------------------------------------------------------------
修改记录  :  
日  期       版本          修改人          走读人          修改记录
2009-9-30                   薛亮
==============================================================================*/
inline BOOL TConfAllMtInfo::MtJoinedConf(TMt tMt ) const
{
	if(tMt.IsLocal())
	{
		return m_tLocalMtInfo.MtJoinedConf( tMt.GetMtId() );
	}
	else
	{
		u8 byMcuId = tMt.GetMcuId();
		u8 byMtId = tMt.GetMtId();
		if( m_tLocalMtInfo.MtJoinedConf( byMcuId ) )
		{
			return m_atOtherMcMtInfo[byMcuId-1].MtJoinedConf(byMtId);
		}
	}
	return FALSE;
}
/*====================================================================
    函数名      ：GetAllMtNum
    功能        ：得到会议完整结构中所有受邀终端个数
    算法实现    ：
    引用全局变量：
    输入参数说明：void
    返回值说明  ：返回的会议中所有受邀终端个数
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/08/02    1.0         LI Yi         创建
====================================================================*/
inline u8   TConfAllMtInfo::GetLocalMtNum( void ) const
{
	return m_tLocalMtInfo.GetAllMtNum();
}

/*====================================================================
    函数名      ：GetAllJoinedMtNum
    功能        ：得到会议完整结构中所有与会终端个数
    算法实现    ：
    引用全局变量：
    输入参数说明：void
    返回值说明  ：返回的会议中所有与会终端个数
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/12/30    1.0         LI Yi         创建
====================================================================*/
inline u8   TConfAllMtInfo::GetLocalJoinedMtNum( void ) const
{
	return m_tLocalMtInfo.GetAllJoinedMtNum();
}

/*====================================================================
    函数名      ：GetAllUnjoinedMtNum
    功能        ：得到会议完整结构中所有未与会终端个数 
    算法实现    ：
    引用全局变量：
    输入参数说明：void
    返回值说明  ：返回的会议中所有未与会终端个数
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/12/30    1.0         LI Yi         创建
====================================================================*/
inline u8   TConfAllMtInfo::GetLocalUnjoinedMtNum( void ) const
{
	return m_tLocalMtInfo.GetAllUnjoinedMtNum();
}

/*====================================================================
    函数名      ：SetMtInfo
    功能        ：设置某个Mc的终端信息
    算法实现    ：
    引用全局变量：
    输入参数说明：void
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    04/07/29    3.0         胡昌威         创建
====================================================================*/
inline void   TConfAllMtInfo::SetMtInfo(TConfMtInfo tConfMtInfo )
{

	u8 byLoop = 0;
	
	if( LOCAL_MCUID == tConfMtInfo.GetMcuId() )
	{
		m_tLocalMtInfo = tConfMtInfo;
		return;
	}

	//查找Mcu号
	while( byLoop < MAXNUM_SUB_MCU )
	{
		if( m_atOtherMcMtInfo[byLoop].GetMcuId() != tConfMtInfo.GetMcuId() )
		{
			byLoop ++;
		}
		else
		{
			//已存在
			m_atOtherMcMtInfo[byLoop] = tConfMtInfo;
			break;
		}
	}

	//不存在
	if( byLoop == MAXNUM_SUB_MCU )
	{
		byLoop = 0;
		while( byLoop < MAXNUM_SUB_MCU )
		{
			if( m_atOtherMcMtInfo[byLoop].IsNull() )
			{
				m_atOtherMcMtInfo[byLoop] = tConfMtInfo;
				break;
			}
			else
			{
				byLoop++;
			}
		}
	}
}

/*====================================================================
    函数名      ：GetMcMtInfo
    功能        ：得到某个Mc的终端信息
    算法实现    ：
    引用全局变量：
    输入参数说明：void
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    04/07/29    3.0         胡昌威         创建
====================================================================*/
inline TConfMtInfo  TConfAllMtInfo::GetMtInfo( u8 byMcuId ) const
{
	TConfMtInfo tConfMtInfo;

	if(byMcuId == m_tLocalMtInfo.GetMcuId())
	{
		return m_tLocalMtInfo;
	}
	u8 byLoop = 0;
	//查找Mcu号
	while( byLoop < MAXNUM_SUB_MCU )
	{
		if( m_atOtherMcMtInfo[byLoop].GetMcuId() != byMcuId )
		{
			byLoop ++;
		}
		else
		{
			tConfMtInfo = m_atOtherMcMtInfo[byLoop];
			break;
		}
	}

	return tConfMtInfo;
}

/*====================================================================
    函数名      ：GetMtInfoPtr
    功能        ：得到某个Mc的终端信息
    算法实现    ：
    引用全局变量：
    输入参数说明：void
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    04/07/29    3.0         胡昌威         创建
====================================================================*/
inline TConfMtInfo*  TConfAllMtInfo::GetMtInfoPtr( u8 byMcuId )
{
	TConfMtInfo *ptConfMtInfo = NULL;

	if(byMcuId == m_tLocalMtInfo.GetMcuId())
	{
		return &m_tLocalMtInfo;
	}
	u8 byLoop = 0;
	//查找Mcu号
	while( byLoop < MAXNUM_SUB_MCU )
	{
		if( m_atOtherMcMtInfo[byLoop].GetMcuId() != byMcuId )
		{
			byLoop ++;
		}
		else
		{
			ptConfMtInfo = &(m_atOtherMcMtInfo[byLoop]);
			break;
		}
	}

	return ptConfMtInfo;
}

/*====================================================================
    函数名      ：MtInConf
    功能        ：得到某个终端是否在受邀终端列表中的信息 
    算法实现    ：
    引用全局变量：
    输入参数说明：void
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    04/07/29    3.0         胡昌威         创建
====================================================================*/
inline BOOL TConfAllMtInfo::MtInConf( u8  byMcuId, u8  byMtId ) const//判断终端是否在受邀终端列表中
{
	TConfMtInfo tConfMtInfo = GetMtInfo( byMcuId );
	if( !tConfMtInfo.IsNull() )
	{
		return tConfMtInfo.MtInConf( byMtId );
	}
	else
	{
		return FALSE;
	}
}

/*====================================================================
    函数名      ：MtJoinedConf
    功能        ：得到某个终端是否入会的信息 
    算法实现    ：
    引用全局变量：
    输入参数说明：void
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    04/07/29    3.0         胡昌威         创建
====================================================================*/
inline BOOL TConfAllMtInfo::MtJoinedConf( u8  byMcuId, u8  byMtId ) const//判断终端是否在与会终端列表中
{
	if( m_tLocalMtInfo.GetMcuId() == byMcuId )
	{
		return MtJoinedConf( byMtId );
	}

	TConfMtInfo tConfMtInfo = GetMtInfo( byMcuId );
	if( !tConfMtInfo.IsNull() )
	{
		return tConfMtInfo.MtJoinedConf( byMtId );
	}
	else
	{
		return FALSE;
	}
}
/*====================================================================
    函数名      ：GetAllMtNum
    功能        ：得到会议完整结构中所有受邀终端个数
    算法实现    ：
    引用全局变量：
    输入参数说明：void
    返回值说明  ：得到会议中所有受邀终端数
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    04/07/29    3.0         胡昌威         创建
====================================================================*/
inline u16   TConfAllMtInfo::GetAllMtNum( void ) const 
{
	u8 byLoop = 0;
	u16 wMtNum = 0;
/*	
	TConfMtInfo tConfMtInfo;

	//查找Mc号
	while( byLoop < MAXNUM_SUB_MCU )
	{
		tConfMtInfo = m_atOtherMcMtInfo[byLoop];
		if( !tConfMtInfo.IsNull() )
		{
			wMtNum = wMtNum + m_atOtherMcMtInfo[byLoop].GetAllMtNum();
		}

		byLoop++;
	}
*/
	// 只返回本Mc的终端
	wMtNum = m_tLocalMtInfo.GetAllMtNum();

	return wMtNum;
}

/*==============================================================================
函数名    :  GetMaxMtIdInConf
功能      :  得到会议完整结构中所有受邀终端中ID最大的值
算法实现  :  
参数说明  :  
返回值说明:  u8 
-------------------------------------------------------------------------------
修改记录  :  
日  期       版本          修改人          走读人          修改记录
2008-12-24					薛亮							创建
==============================================================================*/
inline u8 TConfAllMtInfo::GetMaxMtIdInConf( void ) const
{
	// 只返回本Mc的
	u8 byMaxMtId = 0;
	byMaxMtId = m_tLocalMtInfo.GetMaxMtIdInConf();
	return byMaxMtId;
}

/*====================================================================
    函数名      ：GetCascadeMcuNum
    功能        ：得到级联的别的mcu个数
    算法实现    ：
    引用全局变量：
    输入参数说明：void
    返回值说明  ：下级Mc的个数
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    04/07/29    3.0         胡昌威         创建
====================================================================*/
inline u8  TConfAllMtInfo::GetCascadeMcuNum( void) const
{   

	u8 byMcNum = 0;
	for( u8 byLoop=0; byLoop < MAXNUM_SUB_MCU; byLoop++ )
	{
		if( !m_atOtherMcMtInfo[byLoop].IsNull() )
		{
			byMcNum++;
		}
	}

	return byMcNum;

}

/*=============================================================================
    函 数 名： AddMcuInfo
    功    能： 会议中增加一个mcu信息，可能暂时没有终端
    算法实现： 
    全局变量： 
    参    数： u8 byMcuId
	           u8 m_byConfIdx
    返 回 值： inline BOOL 
-----------------------------------------------------------------------------
    修改记录：
    日  期		版本		修改人		走读人    修改内容
    2005/04/22  3.6			万春雷                  创建
=============================================================================*/
inline BOOL TConfAllMtInfo::AddMcuInfo( u8 byMcuId, u8 m_byConfIdx )
{   
	u8 byLoop = 0;

	//查找Mcu号
	while( byLoop < MAXNUM_SUB_MCU )
	{
		//已存在，清空原有信息
		if( m_atOtherMcMtInfo[byLoop].GetMcuId() == byMcuId )
		{
			memset( &m_atOtherMcMtInfo[byLoop], 0, sizeof(TConfMtInfo) );
			m_atOtherMcMtInfo[byLoop].SetMcuId( byMcuId );
			m_atOtherMcMtInfo[byLoop].SetConfIdx( m_byConfIdx );
			return TRUE;
		}
		byLoop++;
	}

	//不存在,查找一个空位，进行放置
	if( byLoop == MAXNUM_SUB_MCU )
	{
		byLoop = 0;
		while( byLoop < MAXNUM_SUB_MCU )
		{
			if( m_atOtherMcMtInfo[byLoop].IsNull() )
			{
				TConfMtInfo tConfMtInfo;
				memset( &tConfMtInfo, 0, sizeof(TConfMtInfo) );
				tConfMtInfo.SetMcuId( byMcuId );
				tConfMtInfo.SetConfIdx( m_byConfIdx );
				m_atOtherMcMtInfo[byLoop] = tConfMtInfo;
				return TRUE;
			}
			byLoop++;
		}
	}

	return FALSE;
}

/*=============================================================================
    函 数 名： RemoveMcuInfo
    功    能： 会议中移除一个mcu信息，同时清空所有所属终端信息
    算法实现： 
    全局变量： 
    参    数： u8 byMcuId
	           u8 m_byConfIdx
    返 回 值： inline BOOL 
-----------------------------------------------------------------------------
    修改记录：
    日  期		版本		修改人		走读人    修改内容
    2005/04/22  3.6			万春雷                  创建
=============================================================================*/
inline BOOL TConfAllMtInfo::RemoveMcuInfo( u8 byMcuId, u8 m_byConfIdx )
{   
	u8 byLoop = 0;

	//查找Mcu号
	while( byLoop < MAXNUM_SUB_MCU )
	{
		//已存在，清空原有信息
		if( m_atOtherMcMtInfo[byLoop].GetMcuId() == byMcuId )
		{
			memset( &m_atOtherMcMtInfo[byLoop], 0, sizeof(TConfMtInfo) );
			return TRUE;
		}
		byLoop++;
	}

	return FALSE;

}

/*====================================================================
    函数名      ：GetAllJoinedMtNum
    功能        ：得到会议完整结构中所有与会终端个数
    算法实现    ：
    引用全局变量：
    输入参数说明：void
    返回值说明  ：所有加入会议的终端数
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    04/07/29    3.0         胡昌威         创建
====================================================================*/
inline u16   TConfAllMtInfo::GetAllJoinedMtNum( void ) const
{
	u8 byLoop = 0;
	u16 wMtNum = 0;

	TConfMtInfo tConfMtInfo;

	//查找Mc号
	while( byLoop < MAXNUM_SUB_MCU )
	{
		tConfMtInfo = m_atOtherMcMtInfo[byLoop];
		if( !tConfMtInfo.IsNull() )
		{
			wMtNum = wMtNum + m_atOtherMcMtInfo[byLoop].GetAllJoinedMtNum();
		}

		byLoop++;
	}

	//加上本Mc的终端
	wMtNum = wMtNum + m_tLocalMtInfo.GetAllJoinedMtNum();

	return wMtNum;
}

/*====================================================================
    函数名      ：SetChnnlStatus
    功能        ：设置录像机信道状态信息，必须先配置录放像信道数再调用此函数
    算法实现    ：
    引用全局变量：
    输入参数说明：u8 byChnnlIndex, 信道索引
				  u8 byChnnlType, 信道种类，TRecChnnlStatus::TYPE_RECORD或TYPE_PLAY
				  const TRecChnnlStatus * ptStatus, 信道状态，内含信道种类
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    03/06/11    1.0         LI Yi         创建
====================================================================*/
inline BOOL TRecStatus::SetChnnlStatus( u8 byChnnlIndex, u8 byChnnlType, const TRecChnnlStatus * ptStatus )
{
	//record channel
	if( byChnnlType == TRecChnnlStatus::TYPE_RECORD )
	{
		if( byChnnlIndex < m_byRecChnnlNum )
		{
			m_tChnnlStatus[byChnnlIndex] = *ptStatus;
			return( TRUE );
		}
		else
		{
			OspPrintf( TRUE, FALSE, "TRecStatus: Exception - Wrong record channel index%u\n", byChnnlIndex ); 
			return( FALSE );
		}
	}
	else if( byChnnlType == TRecChnnlStatus::TYPE_PLAY )	//放像信道
	{
		if( byChnnlIndex < m_byPlayChnnlNum )
		{
			m_tChnnlStatus[byChnnlIndex + m_byRecChnnlNum] = *ptStatus;
			return( TRUE );
		}
		else
		{
			OspPrintf( TRUE, FALSE, "TRecStatus: Exception - Wrong play channel index%u\n", byChnnlIndex ); 
			return( FALSE );
		}
	}
	else
	{
		OspPrintf( TRUE, FALSE, "TRecStatus: Exception - Wrong channel type%u\n", byChnnlType ); 
		return( FALSE );
	}
}

/*====================================================================
    函数名      ：SetChnnlStatus
    功能        ：设置录像机信道状态信息，必须先配置录放像信道数再调用此函数
    算法实现    ：
    引用全局变量：
    输入参数说明：u8 byChnnlIndex, 信道索引
				  u8 byChnnlType, 信道种类，TRecChnnlStatus::TYPE_RECORD或TYPE_PLAY
				  TRecChnnlStatus * ptStatus, 信道状态，内含信道种类
    返回值说明  ：TRUE/FALSE
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    03/06/11    1.0         LI Yi         创建
====================================================================*/
inline BOOL TRecStatus::GetChnnlStatus( u8 byChnnlIndex, u8 byChnnlType, TRecChnnlStatus * ptStatus ) const
{
	//record channel
	if( byChnnlType == TRecChnnlStatus::TYPE_RECORD )
	{
		if( byChnnlIndex < m_byRecChnnlNum )
		{
			*ptStatus = m_tChnnlStatus[byChnnlIndex];
			return( TRUE );
		}
		else
		{
			OspPrintf( TRUE, FALSE, "TRecStatus: Exception - Wrong record channel index%u\n", byChnnlIndex ); 
			return( FALSE );
		}
	}
	else if( byChnnlType == TRecChnnlStatus::TYPE_PLAY )	//放像信道
	{
		if( byChnnlIndex < m_byPlayChnnlNum )
		{
			*ptStatus = m_tChnnlStatus[byChnnlIndex + m_byRecChnnlNum];
			return( TRUE );
		}
		else
		{
			OspPrintf( TRUE, FALSE, "TRecStatus: Exception - Wrong play channel index%u\n", byChnnlIndex ); 
			return( FALSE );
		}
	}
	else
	{
		OspPrintf( TRUE, FALSE, "TRecStatus: Exception - Wrong channel type%u\n", byChnnlType ); 
		return( FALSE );
	}
}


/*====================================================================
    函数名      ：IsMtIpInAllowSeg
    功能        ：判断IP是否在合法段内
    算法实现    ：
    引用全局变量：
    输入参数说明：u32, IP 地址，网络序
    返回值说明  ：TRUE/FALSE
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    06/06/26    4.0         顾振华        创建
====================================================================*/
inline BOOL32 TUsrGrpInfo::IsMtIpInAllowSeg(u32 dwIp) const
{
/*
 *  以下代码用于 同时配置了允许和禁止段 
 *  目前只配置其中一种
 *  故暂时注释
    BOOL32 bNoAllowed = TRUE; // 是否配置了允许段

    for (u8 byLoop = 0; byLoop < MAXNUM_IPSEG; byLoop ++)
    {
        if ( atIpSegAllow[byLoop].IsEnabled() )
        {
            bNoAllowed = FALSE;
            break;
        }
    }

    // 如果没有配置允许段，检查一下所有的禁止段
    if (bNoAllowed)
    {
        for (byLoop = 0; byLoop < MAXNUM_IPSEG; byLoop ++)
        {
            if ( atIpSegBan[byLoop].IsEnabled() )
            {
                if ( atIpSegBan[byLoop].IsIpIn( dwIp ) )
                {
                    // 发现在禁止段
                    return FALSE;
                }
            }
        }
        // 不在禁止段，认为允许
        return TRUE;
    }
    
    // 如果配置了允许段，先检查是否在允许段
    for (byLoop = 0; byLoop < MAXNUM_IPSEG; byLoop ++)
    {
        if ( atIpSegAllow[byLoop].IsEnabled() )
        {
            if ( atIpSegAllow[byLoop].IsIpIn( dwIp ) )
            {
                // 在某个允许段，则再看是否用小的内部禁止段给禁止了
                for (u8 byLoop2 = 0; byLoop2 < MAXNUM_IPSEG; byLoop2 ++)
                {
                    if ( atIpSegBan[byLoop2].IsEnabled() )
                    {
                        if (atIpSegBan[byLoop2].IsIpIn( dwIp ))
                        {
                            // 确实禁止，看谁范围小谁生效
                            if ( atIpSegAllow[byLoop].IsIpSegIn( atIpSegBan[byLoop2] ) )
                            {
                                return FALSE;
                            }
                        }
                    }
                }
                // 没有禁止段规定
                return TRUE;
            }
        }
    }
*/

    if ( bBanned )
    {
        // 在地址段中查看是否在黑名单中
        for (u8 byLoop = 0; byLoop < MAXNUM_IPSEG; byLoop ++)
        {
            if ( atIpSeg[byLoop].IsEnabled() && atIpSeg[byLoop].IsIpIn( dwIp ) )
            {
                return FALSE;                    
            }
        }
        return TRUE;
    }
    else
    {
        // 在地址段中查看是否在白名单中
        for (u8 byLoop = 0; byLoop < MAXNUM_IPSEG; byLoop ++)
        {
            if ( atIpSeg[byLoop].IsEnabled() && atIpSeg[byLoop].IsIpIn( dwIp ) )
            {
                return TRUE;                    
            }
        }
        return FALSE;
    }

    return FALSE;
}

//终端视频限制（目前是分辨率，码率）
struct TMtVidLmt
{
public:
	void SetMtVidRes( u8 byRes)	{ m_byRes = byRes; }
	u8	 GetMtVidRes( void ){ return m_byRes;}	
	void SetMtVidBW( u16 wBandWidth){m_wBandWidth = wBandWidth;}
	u16	 GetMtVidBw( void ){ return m_wBandWidth;}

private:
	
	u16 m_wBandWidth;
	u8	m_byRes;
	u8  m_byReserve;

}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

/*==============================================================================
类名    :  CVmpMemVidLmt
功能    :  画面合成成员视频分辨率等能力限制
主要接口:  
备注    :  
-------------------------------------------------------------------------------
修改记录:  
日  期     版本          修改人          走读人          修改记录
2009-2-26
==============================================================================*/
class CVmpMemVidLmt
{
private:
	TMtVidLmt m_atMtVidLmtHd[VMP_STYLE_TWENTY +1][MAXNUM_MPUSVMP_MEMBER];  
 	TMtVidLmt m_atMtVidLmtStd[VMP_STYLE_TWENTY +1][MAXNUM_MPUSVMP_MEMBER];

public:
	CVmpMemVidLmt( void )
	{
		Init();
	}
	/*==============================================================================
	函数名    : GetMtVidLmtForHd 
	功能      : 得到终端参与VMP分辨率最高限制值（对于高清终端） 
	算法实现  :  
	参数说明  :  
	返回值说明:  
	-------------------------------------------------------------------------------
	修改记录  :  
	日  期       版本          修改人          走读人          修改记录
	2009-2-20	4.6				薛亮							create
	==============================================================================*/
	BOOL32 GetMtVidLmtForHd ( u8 byStyle, u8 byMemPos, u8 &byMtRes, u16 &wMtBandWidth)
	{
		BOOL32 bRet = TRUE;
		byMtRes = m_atMtVidLmtHd[byStyle][byMemPos].GetMtVidRes();
		wMtBandWidth = m_atMtVidLmtHd[byStyle][byMemPos].GetMtVidBw();
		if(byMtRes == 0 || wMtBandWidth == 0)
		{
			bRet = FALSE;
		}
		return bRet;
	}
	
	/*==============================================================================
	函数名    : GetMtVidLmtForStd 
	功能      : 得到终端参与VMP分辨率最高限制值（对于标清终端）
	算法实现  :  
	参数说明  :  
	返回值说明:  BOOL32
	-------------------------------------------------------------------------------
	修改记录  :  
	日  期       版本          修改人          走读人          修改记录
	2009-2-20	4.6				薛亮							create
	==============================================================================*/
	BOOL32 GetMtVidLmtForStd ( u8 byStyle, u8 byMemPos, u8 &byMtRes, u16 &wMtBandWidth)
	{
		BOOL32 bRet = TRUE;
		byMtRes = m_atMtVidLmtStd[byStyle][byMemPos].GetMtVidRes();
		wMtBandWidth = m_atMtVidLmtStd[byStyle][byMemPos].GetMtVidBw();
		if(byMtRes == 0 || wMtBandWidth == 0)
		{
			bRet = FALSE;
		}
		return bRet;
	}

	void Init( void )
	{
		u8 byStyle = 0;
		u8 byLoop = 0;
		memset( m_atMtVidLmtHd, 0, sizeof( m_atMtVidLmtHd ) );
		memset( m_atMtVidLmtStd, 0, sizeof( m_atMtVidLmtStd ) );
		const u16 wBW_8M = 8192;
		const u16 wBW_3M = 3072;
		const u16 wBW_1d5M = 1536;
		
		byStyle = VMP_STYLE_ONE;	//1画面
		m_atMtVidLmtHd[byStyle][0].SetMtVidRes(VIDEO_FORMAT_HD1080);
		m_atMtVidLmtHd[byStyle][0].SetMtVidBW(wBW_8M);
		
		m_atMtVidLmtStd[byStyle][0].SetMtVidRes(VIDEO_FORMAT_4SIF);
		m_atMtVidLmtStd[byStyle][0].SetMtVidBW(wBW_8M);

		byStyle = VMP_STYLE_VTWO;	//左右2画面
		for(byLoop = 0; byLoop < 2;byLoop ++)
		{
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_720_960x544);
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidBW(wBW_8M);

			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_4SIF);
			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidBW(wBW_8M);
		}

		
		byStyle = VMP_STYLE_HTWO;	//一大一小2画面
		m_atMtVidLmtHd[byStyle][0].SetMtVidRes(VIDEO_FORMAT_HD1080);
		m_atMtVidLmtHd[byStyle][0].SetMtVidBW(wBW_8M);
		m_atMtVidLmtHd[byStyle][1].SetMtVidRes(VIDEO_FORMAT_640x368);
		m_atMtVidLmtHd[byStyle][1].SetMtVidBW(wBW_3M);
		
		m_atMtVidLmtStd[byStyle][0].SetMtVidRes(VIDEO_FORMAT_4SIF);
		m_atMtVidLmtStd[byStyle][0].SetMtVidBW(wBW_8M);
		m_atMtVidLmtStd[byStyle][1].SetMtVidRes(VIDEO_FORMAT_CIF);
		m_atMtVidLmtStd[byStyle][1].SetMtVidBW(wBW_1d5M);

		byStyle = VMP_STYLE_THREE;	//3画面
		for(byLoop = 0; byLoop < 3; byLoop ++)
		{	
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_960x544);
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidBW(wBW_8M);

			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_4SIF);
			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidBW(wBW_8M);
		}
		
		
		byStyle = VMP_STYLE_FOUR;	//4画面
		for(byLoop = 0; byLoop < 4; byLoop ++)
		{	
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_960x544);
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidBW(wBW_8M);

			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_4SIF);
			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidBW(wBW_8M);
		}

		
		byStyle = VMP_STYLE_SIX;	//6画面
		m_atMtVidLmtHd[byStyle][0].SetMtVidRes(VIDEO_FORMAT_HD720);
		m_atMtVidLmtHd[byStyle][0].SetMtVidBW(wBW_8M);

		m_atMtVidLmtStd[byStyle][0].SetMtVidRes(VIDEO_FORMAT_4SIF);
		m_atMtVidLmtStd[byStyle][0].SetMtVidBW(wBW_8M);

		for(byLoop = 1; byLoop < 6; byLoop ++)
		{	
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_640x368);
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidBW(wBW_3M);

			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_CIF);
			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidBW(wBW_1d5M);
		}

		
		byStyle = VMP_STYLE_EIGHT;	//8画面
		m_atMtVidLmtHd[byStyle][0].SetMtVidRes(VIDEO_FORMAT_1440x816);
		m_atMtVidLmtHd[byStyle][0].SetMtVidBW(wBW_8M);

		m_atMtVidLmtStd[byStyle][0].SetMtVidRes(VIDEO_FORMAT_4SIF);
		m_atMtVidLmtStd[byStyle][0].SetMtVidBW(wBW_8M);

		for(byLoop = 1; byLoop < 8; byLoop ++)
		{	
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_480x272);
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidBW(wBW_1d5M);

 			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_CIF);
 			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidBW(wBW_1d5M);
		}

		
		byStyle = VMP_STYLE_NINE;	//9画面
		for(byLoop = 0; byLoop < 9; byLoop ++)
		{	
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_640x368);
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidBW(wBW_3M);

			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_CIF);
			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidBW(wBW_1d5M);
		}

				
		byStyle = VMP_STYLE_TEN;	//10画面
		m_atMtVidLmtHd[byStyle][0].SetMtVidRes(VIDEO_FORMAT_960x544);
		m_atMtVidLmtHd[byStyle][0].SetMtVidBW(wBW_8M);
		m_atMtVidLmtHd[byStyle][5].SetMtVidRes(VIDEO_FORMAT_960x544);
		m_atMtVidLmtHd[byStyle][5].SetMtVidBW(wBW_8M);

		m_atMtVidLmtStd[byStyle][0].SetMtVidRes(VIDEO_FORMAT_4SIF);
		m_atMtVidLmtStd[byStyle][0].SetMtVidBW(wBW_8M);
		m_atMtVidLmtStd[byStyle][5].SetMtVidRes(VIDEO_FORMAT_4SIF);
		m_atMtVidLmtStd[byStyle][5].SetMtVidBW(wBW_8M);

		for(byLoop = 1; byLoop < 5; byLoop ++)
		{	
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_480x272);
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidBW(wBW_1d5M);

			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_CIF);
			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidBW(wBW_1d5M);
		}
		for(byLoop = 6; byLoop < 10; byLoop ++)
		{	
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_480x272);
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidBW(wBW_1d5M);

			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_CIF);
			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidBW(wBW_1d5M);
		}
		
		byStyle = VMP_STYLE_THIRTEEN;//13画面
		m_atMtVidLmtHd[byStyle][0].SetMtVidRes(VIDEO_FORMAT_960x544);
		m_atMtVidLmtHd[byStyle][0].SetMtVidBW(wBW_8M);

		m_atMtVidLmtStd[byStyle][0].SetMtVidRes(VIDEO_FORMAT_4SIF);
		m_atMtVidLmtStd[byStyle][0].SetMtVidBW(wBW_8M);

		for(byLoop = 1; byLoop < 13; byLoop ++)
		{	
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_480x272);
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidBW(wBW_1d5M);

			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_CIF);
			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidBW(wBW_1d5M);
		}

				
		byStyle = VMP_STYLE_SIXTEEN;//16画面
		for(byLoop = 0; byLoop < 16; byLoop ++)
		{	
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_480x272);
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidBW(wBW_1d5M);

			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_CIF);
			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidBW(wBW_1d5M);
		}

		
		byStyle = VMP_STYLE_SPECFOUR;//特殊4画面
		m_atMtVidLmtHd[byStyle][0].SetMtVidRes(VIDEO_FORMAT_HD720);
		m_atMtVidLmtHd[byStyle][0].SetMtVidBW(wBW_8M);

		m_atMtVidLmtStd[byStyle][0].SetMtVidRes(VIDEO_FORMAT_4SIF);
		m_atMtVidLmtStd[byStyle][0].SetMtVidBW(wBW_8M);

		for(byLoop = 1; byLoop < 4; byLoop ++)
		{	
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_640x368);
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidBW(wBW_3M);

			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_CIF);
			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidBW(wBW_1d5M);
		}


		byStyle = VMP_STYLE_SEVEN;	//7画面
		for(byLoop = 0; byLoop < 3; byLoop ++)
		{	
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_960x544);
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidBW(wBW_8M);

			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_4SIF);
			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidBW(wBW_8M);
		}
		for(byLoop = 3; byLoop < 7; byLoop ++)
		{	
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_480x272);
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidBW(wBW_1d5M);

			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_CIF);
			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidBW(wBW_1d5M);
		}

	    
		byStyle = VMP_STYLE_TWENTY; //20画面
		for(byLoop = 0; byLoop < 20; byLoop ++)
		{	
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_480x272);
			m_atMtVidLmtHd[byStyle][byLoop].SetMtVidBW(wBW_1d5M);

			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidRes(VIDEO_FORMAT_CIF);
			m_atMtVidLmtStd[byStyle][byLoop].SetMtVidBW(wBW_1d5M);
		}
	}

};
// MCU 8000B 能力限制逻辑
// 使用静态类方法提供函数接口
// 要使用这些接口, 请包含且只包含 实现文件mcupfmlmt.h 头文件一次
// MCS 收到本结构后请自行保存,在MCU切换后调用 CMcuPfmLmt::SetFilter() 接口设置
struct TMcu8kbPfmFilter
{
    TMcu8kbPfmFilter()
    {
        byMaxNumMixSingleMp3   = MAXNUM_MIX_SINGLE_MP3;     
        byMaxNumMixMultiMp3    = MAXNUM_MIX_MULTI_MP3;
        byMaxNumMixSingleG729  = MAXNUM_MIX_SINGLE_G729;
        byMaxNumMixMultiG729   = MAXNUM_MIX_MULTI_G729;
        byMaxNumVacSingleMp3   = MAXNUM_VAC_SINGLE_MP3;
        byMaxNumVacMultiMp3    = MAXNUM_VAC_MULTI_MP3; 
        byMaxNumVacSingleG729  = MAXNUM_VAC_SINGLE_G729;
        byMaxNumVacMultiG729   = MAXNUM_VAC_MULTI_G729;

        byEnable               = 1; 
    }

    void Print() const
    {
        OspPrintf(TRUE, FALSE, "TMcu8kbPfmFilter:\n");
        OspPrintf(TRUE, FALSE, "\t IsEnable: %d\n", byEnable);
        OspPrintf(TRUE, FALSE, "\t byMaxNumMixSingleMp3: %d\n", byMaxNumMixSingleMp3);
        OspPrintf(TRUE, FALSE, "\t byMaxNumMixMultiMp3: %d\n", byMaxNumMixMultiMp3);
        OspPrintf(TRUE, FALSE, "\t byMaxNumMixSingleG729: %d\n", byMaxNumMixSingleG729);
        OspPrintf(TRUE, FALSE, "\t byMaxNumMixMultiG729: %d\n", byMaxNumMixMultiG729);
        OspPrintf(TRUE, FALSE, "\t byMaxNumVacSingleMp3: %d\n", byMaxNumVacSingleMp3);
        OspPrintf(TRUE, FALSE, "\t byMaxNumVacMultiMp3: %d\n", byMaxNumVacMultiMp3);
        OspPrintf(TRUE, FALSE, "\t byMaxNumVacSingleG729: %d\n", byMaxNumVacSingleG729);
        OspPrintf(TRUE, FALSE, "\t byMaxNumVacMultiG729: %d\n", byMaxNumVacMultiG729);
    }

    BOOL32 IsEnable() const
    {
        return (byEnable != 0 ? TRUE : FALSE);
    }

public:
    u8 byMaxNumMixSingleMp3; //MP3混音(定制和讨论)单开方数
    u8 byMaxNumMixMultiMp3;  //MP3混音(定制和讨论)和其他(VMP和BAS)混开方数
    u8 byMaxNumMixSingleG729;//G729混音(定制和讨论)单开方数;
    u8 byMaxNumMixMultiG729; //G729混音(定制和讨论)和其他(VMP和BAS)混开方数
    u8 byMaxNumVacSingleMp3; //MP3的VAC单开方数
    u8 byMaxNumVacMultiMp3;  //MP3的VAC和其他(BAS)混开方数
    u8 byMaxNumVacSingleG729;//G729的VAC单开方数;
    u8 byMaxNumVacMultiG729; //G729的VAC和其他(BAS)混开方数
private:
    u8 byEnable;             //是否启用

}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

class CMcuPfmLmt
{
public:
    /*=============================================================================
        函 数 名： GetMaxVmpStyle
        功    能： 判断当前VMP最多支持的画面合成路数
        算法实现： 
        全局变量： 
        参    数： TConfInfo &tConfInfo         [in]  会议基本信息
                   u8 byMtNum                   [in]  会议终端数量
                   u8 byMixingMtNum             [in]  正在参与混音(智能或定制)的终端数量
                   u16 &wError                  [out] 返回的错误码
        返 回 值： BOOL32
        ----------------------------------------------------------------------
        修改记录    ：
        日  期		版本		修改人		走读人    修改内容
        2007/01/29  4.0			顾振华                  创建
    =============================================================================*/
    static u8 GetMaxOprVmpStyle( const TConfInfo &tConfInfo, u8 byMtNum, u8 byMixingMtNum, u16 &wError );
	
    /*=============================================================================
        函 数 名： GetMaxOprMixNum
        功    能： 判断当前最多能设置的混音(包括定制和智能)终端数
        算法实现： 
        全局变量： 
        参    数： TConfInfo &tConfInfo     [in]  会议信息
        返 回 值： BOOL32
        ----------------------------------------------------------------------
        修改记录    ：
        日  期		版本		修改人		走读人    修改内容
        2007/01/29  4.0			顾振华                  创建
    =============================================================================*/
    static u8 GetMaxOprMixNum( const TConfInfo &tConfInfo, u16 &wError );

    /*=============================================================================
        函 数 名： GetMaxDynVmpStyle
        功    能： 获取当前能支持的动态合成风格
        算法实现： 
        全局变量： 
        参    数： TConfInfo &tConfInfo         [in]  会议基本信息
                   u8 byMtNum                   [in]  会议终端数量
                   u8 byMixingMtNum             [in]  正在参与混音(智能或定制)的终端数量
                   u16 &wError                  [out] 返回的错误码
        返 回 值： BOOL32
        说明    ： MCS不支持使用本方法
        ----------------------------------------------------------------------
        修改记录    ：
        日  期		版本		修改人		走读人    修改内容
        2007/01/31  4.0			顾振华                  创建
    =============================================================================*/    
    static u8 GetMaxDynVmpStyle( const TConfInfo &tConfInfo, u8 byMtNum, u8 byMixingMtNum, u16 &wError );
    
    /*=============================================================================
        函 数 名： IsVmpOprSupported
        功    能： 判断当前的VMP操作能否接受
        算法实现： 
        全局变量： 
        参    数： TConfInfo &tConfInfo         [in]  会议基本信息
                   u8 byNewStyle                [in]  新的VMP操作的风格
                   u8 byMtNum                   [in]  会议终端数量
                   u8 byMixingMtNum             [in]  正在参与混音(智能或定制)的终端数量
                   u16 &wError                  [out] 返回的错误码
        返 回 值： BOOL32
        ----------------------------------------------------------------------
        修改记录    ：
        日  期		版本		修改人		走读人    修改内容
        2007/01/25  4.0			张宝卿                  创建
    =============================================================================*/    
    static BOOL32 IsVmpOprSupported( const TConfInfo &tConfInfo, u8 byNewStyle, u8 byMtNum, u8 byMixingMtNum, u16 &wError );

    /*=============================================================================
        函 数 名： IsMixOprSupported
        功    能： 判断当前的定制混音操作能否接受
        算法实现： 
        全局变量： 
        参    数： TConfInfo &tConfInfo         [in]  会议信息
                   u8 byMixingMtNum             [in]  正在参与混音(智能或定制)的终端数量
                   u8 byAddNum                  [in]  要添加进混音的终端数量
                   u16 &wError                  [out] 返回的错误码
        返 回 值： BOOL32
        ----------------------------------------------------------------------
        修改记录    ：
        日  期		版本		修改人		走读人    修改内容
        2007/01/25  4.0			张宝卿                  创建
    =============================================================================*/
    static BOOL32 IsMixOprSupported( const TConfInfo &tConfInfo, u8 byMixingNum, u8 byAddNum, u16 &wError );

    /*=============================================================================
        函 数 名： IsVacOprSupported
        功    能： 判断开启VAC是否能被接受
        算法实现： 
        全局变量： 
        参    数： TConfInfo &tConfInfo   [in]  会议信息
                   u8        byMtNum      [in]  会议当前的所有在线终端数
                   u16 &wError            [out] 返回的错误码
        返 回 值： BOOL32
        ----------------------------------------------------------------------
        修改记录    ：
        日  期		版本		修改人		走读人    修改内容
        2007/01/30  4.0			顾振华                  创建
    =============================================================================*/    
    static BOOL32 IsVacOprSupported( const TConfInfo &tConfInfo, u8 byMtNum, u16 &wError );

    /*=============================================================================
        函 数 名： IsBasOprSupported
        功    能： 判断开启BAS是否能被接受
        算法实现： 
        全局变量： 
        参    数： TConfInfo &tConfInfo   [in]  会议信息
                   u8        byMixNum     [in]  会议当前的混音终端数
                   u16 &wError            [out] 返回的错误码
        返 回 值： BOOL32
        ----------------------------------------------------------------------
        修改记录    ：
        日  期		版本		修改人		走读人    修改内容
        2007/01/30  4.0			顾振华                  创建
    =============================================================================*/   
    static BOOL32 IsBasOprSupported( const TConfInfo &tConfInfo, u8 byMixNum, u16 &wError );
    
    /*=============================================================================
        函 数 名： IsMtOprSupported
        功    能： 判断当前的增加终端是否能被接受
        算法实现： 
        全局变量： 
        参    数： TConfInfo &tConfInfo   [in]  会议信息
                   u8        byMtNum      [in]  会议当前的所有在线终端数
                   u8        byMixNum     [in]  正在混音(智能、定制)终端数
                   u16 &wError            [out] 返回的错误码
        返 回 值： BOOL32
        ----------------------------------------------------------------------
        修改记录    ：
        日  期		版本		修改人		走读人    修改内容
        2007/01/26  4.0			张宝卿                  创建
    =============================================================================*/
    static BOOL32 IsMtOprSupported( const TConfInfo &tConfInfo, u8 byMtNum, u8 byMixNum, u16 &wError );

    /*=============================================================================
        函 数 名： SetFilter
        功    能： 设置性能限制的过滤参数
        算法实现： 
        全局变量： 
        参    数： TMcu8kbPfmFilter& tNewFilter   [in]  新的参数。如果用户不配置，用缺省构造即可
        返 回 值： 
        ----------------------------------------------------------------------
        修改记录    ：
        日  期		版本		修改人		走读人    修改内容
        2007/01/30  4.0			顾振华                  创建
    =============================================================================*/
    static void SetFilter(const TMcu8kbPfmFilter& tNewFilter)
    {
        m_tFilter = tNewFilter;
    }

	/*=============================================================================
        函 数 名： GetFilter
        功    能： 设置性能限制的过滤参数
        算法实现： 
        全局变量： 
        参    数： 无
        返 回 值： TMcu8kbPfmFilter
        ----------------------------------------------------------------------
        修改记录    ：
        日  期		版本		修改人		走读人    修改内容
        2007/02/07  4.0			周广程                  创建
    =============================================================================*/
    static TMcu8kbPfmFilter GetFilter()
    {
        return m_tFilter;
    }

    /* 以下函数用于MCU8000A, 不受过滤器约束 */
	/*=============================================================================
	函 数 名： IsVmpStyleSupport
	功    能： 判断某个画面合成（包括多画面电视墙）操作的目标风格是否能支持（MCU8000A）
	算法实现： 
	全局变量： 
	参    数： const TConfInfo &tConfInfo   [in] 会议信息
			   u8 byConfIdx                 [in] 会议ConfIdx信息
			   TPeriEqpStatus *ptVmpStatus  [in] 外设状态数组
			   u16 wLen                     [in] 外设状态数组长度
			   u8 byTargetStyle             [in] 指定的目标风格
			   u8 &bySelVmpId               [out] 返回符合条件的Vmp或VmpTw
	返 回 值： BOOL32 是否能支持
	----------------------------------------------------------------------
	修改记录    ：
	日  期		版本		修改人		走读人    修改内容
	2007/7/13   4.0			周广程      顾振华      创建
	=============================================================================*/
	static BOOL32 IsVmpStyleSupport( const TConfInfo &tConfInfo, u8 byConfIdx, 
							   	     TPeriEqpStatus *ptVmpStatus, u16 wLen, 
								     u8 byTargetStyle, u8 &bySelVmpId );

	/*=============================================================================
	函 数 名： GetSupportedVmpStyles
	功    能： 返回指定会议能够支持的所有画面合成风格
	算法实现： 
	全局变量： 
	参    数：   const TConfInfo &tConfInfo   [in] 会议信息
				 u8 byConfIdx                 [in] 会议ConfIdx信息
				 TPeriEqpStatus *ptVmpStatus  [in] 外设状态数组
				 u16 wLen                     [in] 外设状态数组长度
				 u8 *pabStyle                 [out] 返回的风格数组
				 u8 &byStyleSize              [I/O] 传入数组的大小，同时返回实际大小。
													如果实际返回值大于传入值，则说明空间不够，同时上面的数组没有进行填充
	返 回 值： void 
	----------------------------------------------------------------------
	修改记录    ：
	日  期		版本		修改人		走读人    修改内容
	2007/7/13   4.0			周广程      顾振华      创建
	=============================================================================*/
	static void GetSupportedVmpStyles( const TConfInfo &tConfInfo, u8 byConfIdx, 
										TPeriEqpStatus *ptVmpStatus, u16 wLen, 
										u8 *pabyStyle, u8 &byArraySize );

	/*=============================================================================
	函 数 名： GetMaxCapVMPByConfInfo
	功    能： 仅根据会议信息计算当前会议最多支持的画面合成或多画面电视墙路数（MCU8000A）		   
	算法实现： 
	全局变量： 
	参    数： const TConfInfo &tConfInfo
	返 回 值： BOOL32 
	----------------------------------------------------------------------
	修改记录    ：
	日  期		版本		修改人		走读人    修改内容
	2007/7/14   4.0			顾振华      　　　　　　创建
	=============================================================================*/
    static u8 GetMaxCapVMPByConfInfo( const TConfInfo &tConfInfo );

    /*=============================================================================
	函 数 名： IsConfFormatHD
	功    能： 本会议是否为高清会议，仅对H.264有效
	算法实现： 
	全局变量： 
    参    数： const TConfInfo &tConfInfo   [in] 会议信息
	返 回 值： BOOL32
	----------------------------------------------------------------------
	修改记录    ：
	日  期		版本		修改人		走读人    修改内容
	2007/12/19  4.0			张宝卿                  创建
	=============================================================================*/
    static BOOL32 IsConfFormatHD( const TConfInfo &tConfInfo );

    /*=============================================================================
	函 数 名： IsConfFormatOverCif
	功    能： 本会议是否为D1或者高清会议，仅对H.264有效
	算法实现： 
	全局变量： 
    参    数： const TConfInfo &tConfInfo   [in] 会议信息
	返 回 值： BOOL32 如果非H.264主格式会议均返回FALSE
	----------------------------------------------------------------------
	修改记录    ：
	日  期		版本		修改人		走读人    修改内容
	2008/03/11  4.5			顾振华                  创建
	=============================================================================*/
    static BOOL32 IsConfFormatOverCif( const TConfInfo &tConfInfo );

	/*=============================================================================
	函 数 名： IsConfPermitVmp
	功    能： 本会议是否允许画面合成
	算法实现： 
	全局变量： 
    参    数： const TConfInfo &tConfInfo   [in] 会议信息
	返 回 值： BOOL32 如果非H.264主格式会议均返回FALSE
	----------------------------------------------------------------------
	修改记录    ：
	日  期		版本		修改人		走读人    修改内容
	2008/03/11  4.5			顾振华                  创建
	=============================================================================*/
    static BOOL32 IsConfPermitVmp( const TConfInfo &tConfInfo );

    /*=============================================================================
	函 数 名： IsRollCallSupported
	功    能： 本会议是否支持会议点名
	算法实现： 
	全局变量： 
    参    数： const TConfInfo &tConfInfo   [in] 会议信息
	返 回 值： BOOL32
	----------------------------------------------------------------------
	修改记录    ：
	日  期		版本		修改人		走读人    修改内容
	2007/12/19  4.0			张宝卿                  创建
	=============================================================================*/
    static BOOL32 IsRollCallSupported( const TConfInfo &tConfInfo );

	/*=============================================================================
	函 数 名： IsVmpSupported
	功    能： 本会议是否支持画面合成器
	算法实现： 
	全局变量： 
    参    数： const TConfInfo &tConfInfo   [in] 会议信息
	返 回 值： BOOL32
	----------------------------------------------------------------------
	修改记录    ：
	日  期		版本		修改人		走读人    修改内容
	2007/12/19  4.0			张宝卿                  创建
	=============================================================================*/
    static BOOL32 IsVmpSupported( const TConfInfo &tConfInfo );
    
    /*=============================================================================
	函 数 名： IsMPWSupported
	功    能： 本会议是否支持多画面电视墙
	算法实现： 
	全局变量： 
    参    数： const TConfInfo &tConfInfo   [in] 会议信息
	返 回 值： BOOL32
	----------------------------------------------------------------------
	修改记录    ：
	日  期		版本		修改人		走读人    修改内容
	2007/12/19  4.0			张宝卿                  创建
	=============================================================================*/
    static BOOL32 IsMPWSupported( const TConfInfo &tConfInfo );
    
    /*=============================================================================
	函 数 名： IsTVWallSupported
	功    能： 本会议是否支持电视墙
	算法实现： 
	全局变量： 
    参    数： const TConfInfo &tConfInfo   [in] 会议信息
	返 回 值： BOOL32
	----------------------------------------------------------------------
	修改记录    ：
	日  期		版本		修改人		走读人    修改内容
	2007/12/19  4.0			张宝卿                  创建
	=============================================================================*/
    static BOOL32 IsTVWallSupported( const TConfInfo &tConfInfo );
    
    /*=============================================================================
	函 数 名： IsMultiVidStreamSupported
	功    能： 本会议是否支持视频多速多格式
	算法实现： 
	全局变量： 
    参    数： const TConfInfo &tConfInfo   [in] 会议信息
               u8 byMode = MODE_VIDEO       [in] 音频或视频,不支持MODE_BOTH
	返 回 值： BOOL32
	----------------------------------------------------------------------
	修改记录    ：
	日  期		版本		修改人		走读人    修改内容
	2007/12/19  4.0			张宝卿                  创建
	=============================================================================*/
    static BOOL32 IsMultiStreamSupported( const TConfInfo &tConfInfo, u8 byMode = MODE_VIDEO );

private:
	/*=============================================================================
	函 数 名： GetMaxCapVMP
	功    能： 计算当前会议最多支持的画面合成或多画面电视墙路数以及相应的设备ID（MCU8000A）			   
	算法实现： 
	全局变量： 
	参    数： const TConfInfo &tConfInfo
			   TPeriEqpStatus *ptVmpStatus : VMP/VMPTW 状态数组
			   u16 wlen : 状态数组长度
			   u8 &byVmpCapChnnlNum [OUT]: 
			   u8 &bySelVmpId[OUT]:
	返 回 值： BOOL32 
	----------------------------------------------------------------------
	修改记录    ：
	日  期		版本		修改人		走读人    修改内容
	2007/6/20   4.0			周广程      顾振华      创建
	=============================================================================*/
	static BOOL32 GetMaxCapVMP( const TConfInfo &tConfInfo, u8 byConfIdx, 
								TPeriEqpStatus *ptVmpStatus, u16 wLen, 
								u8 &byVmpCapChnnlNum, 
                                u8 &bySelVmpId, 
								u8 byTargetStyle = 0	//0表自动风格
								);

	/*=============================================================================
	函 数 名： GetSupportedVmpStyles
	功    能： 返回能够支持的所有画面合成风格（MCU8000A）
	算法实现： 
	全局变量： 
	参    数： const TConfInfo &tConfInfo
			   u8 byEqpType
			   u8 bySubType
			   u8 byCapChnnlNum             
			   u8 byVmpMaxChnnlNum
               u8 *pabyStyle                [out] 返回的风格数组
               u8 &byArraySize              [I/O] 传入数组的大小，同时返回实际大小。
                                                  如果实际返回值大于传入值，则说明空间不够，同时上面的数组没有进行填充
	返 回 值： void 
	----------------------------------------------------------------------
	修改记录    ：
	日  期		版本		修改人		走读人    修改内容
	2007/7/13   4.0			周广程      顾振华      创建
	2009/2/18	4.6			薛亮					增参数区分VMP种类；引入20风格
	=============================================================================*/
	static void GetSupportedVmpStyles( const TConfInfo &tConfInfo, u8 byEqpType, u8 bySubType,u8 byCapChnnlNum, u8 byVmpMaxChnnlNum, 
                                       u8 *pabyStyle, u8 &byArraySize );
	/*=============================================================================
	函 数 名： GetSelVmpCap
	功    能： 获取最接近会议能力的vmp id及其能力
	算法实现： 
	全局变量： 
	参    数： u8 abySelVmpIdx[]				[in] 
	TPeriEqpStatus *ptStatus		[in] 
	u8 bySelNum						[in]
	u8 byMaxChnlNumByConf			[in]
	u8 &byVmpCapChnnlNum			[out]
	u8 &bySelVmpId					[out]
	返 回 值： BOOL32
	----------------------------------------------------------------------
	修改记录    ：
	日  期		版本		修改人		走读人    修改内容
	12/9/2008				薛亮					
	=============================================================================*/
	static BOOL32 GetSelVmpCap(u8 abySelVmpIdx[], TPeriEqpStatus *ptStatus, u8 bySelNum, 
		u8 byMaxChnlNumByConf,u8 &byVmpCapChnnlNum, u8 &bySelVmpId);
	
	

private:
    static TMcu8kbPfmFilter m_tFilter;
};

// xliang [3/18/2009] VMP 占高清前适配通道和需要进高清前适配通道但未占成功的终端信息
struct TVmpHdChnnlMemInfo
{
public:
	TMt	tMtInHdChnnl[MAXNUM_SVMPB_HDCHNNL];
	TMt	tMtOutHdChnnl[MAXNUM_MPUSVMP_MEMBER];
public:
	TVmpHdChnnlMemInfo( void )
	{
		init();
	}
	void init()
	{
		memset(tMtInHdChnnl,0, sizeof(tMtInHdChnnl));
		memset(tMtOutHdChnnl,0,sizeof(tMtOutHdChnnl));
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

// xliang [11/28/2008]VMP 通道成员信息
struct TChnnlMemberInfo 
{
	enum EmChnnlPriMask
    {
        Mask_BeSelected		=   0x0001,
		Mask_NoneKeda		=   0x0002,
		Mask_Speaker		=   0x0004,
    };
public:
//	u8	m_byMtId;			//占该通道的MT ID
	TMt m_tSeizedMt;		//占该通道的MT
	u8	m_byVmpPRIAttr;		//优先级属性
	u8  m_byReserved1;		//预留
	u8  m_byReserved2;		//预留
public:
	TChnnlMemberInfo(void)
	{
		SetNull();
	}
	void SetNull()
	{
		//m_byMtId = 0;
		m_tSeizedMt.SetNull();
		m_byVmpPRIAttr = 0;
	}
	void SetAttrNull()
	{
		m_byVmpPRIAttr = 0;
	}
	void SetAttrSelected()
	{
		m_byVmpPRIAttr |= Mask_BeSelected;
	}
	void SetAttrNoneKeda()
	{
		m_byVmpPRIAttr |= Mask_NoneKeda;
	}
	void SetAttrSpeaker()
	{
		m_byVmpPRIAttr |= Mask_Speaker;
	}
	BOOL32 IsAttrSpeaker() const
	{
		return ( (m_byVmpPRIAttr & Mask_Speaker) != 0 );
	}
	BOOL32 IsAttrNoneKeda() const
	{
		return ( (m_byVmpPRIAttr & Mask_NoneKeda) != 0 );
	}
	BOOL32 IsAttrSelected() const
	{
		return ( (m_byVmpPRIAttr & Mask_BeSelected) != 0 );
	}
	
	u8 GetMtId( void ) const
	{
		return m_tSeizedMt.GetMtId();
	}
	TMt GetMt(void) const
	{
		return m_tSeizedMt;
	}
	void SetMt(TMt tMt)
	{
		m_tSeizedMt = tMt;
	}
}	
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;
//vmp各通道信息
struct TVmpChnnlInfo
{	
public:
	u8 m_byHDChnnlNum;		//高清通道被占数目
	u8 m_by4CifChnnlNum;
	u8 m_byCifChnnlNum;		//目前不用
	u8 m_byAllChnnlNum;		//所有被用的通道数，目前不用
	u8 m_byHdChnnlIdx;		//通道idx
	TChnnlMemberInfo	m_tHdChnnlInfo[MAXNUM_SVMPB_HDCHNNL];
//	TChnnlMemberInfo	t4CifChnnlInfo[MAX_SVMP_4CIFCHNNLNUM];
//	TChnnlMemberInfo	tCifChnnlInfo[MAX_SVMP_CIFCHNNLNUM];
public:
	TVmpChnnlInfo(void)
	{
		clear();
	}
	void clear()
	{
		SetHDChnnlNum(0);
		Set4CifChnnlNum(0);
		SetCifChnnlNum(0);
		SetAllChnnlNum(0);
		memset(m_tHdChnnlInfo,0,sizeof(m_tHdChnnlInfo));

	}
	void SetHDChnnlNum(u8 byHDChnnlNum){m_byHDChnnlNum = byHDChnnlNum;}
	u8	 GetHDChnnlNum( void ){ return m_byHDChnnlNum; }
	void Set4CifChnnlNum(u8 by4CifChnnlNum){m_by4CifChnnlNum = by4CifChnnlNum;}
	void SetCifChnnlNum(u8 byCifChnnlNum){m_byCifChnnlNum = byCifChnnlNum;}
	u8	 GetCifChnnlNum( void ){ return m_byCifChnnlNum; }
	void SetAllChnnlNum(u8 byAllChnnlNum){m_byAllChnnlNum = byAllChnnlNum;}
	
	void SetHdChnnlInfo(u8 byChnnlIdx,const TChnnlMemberInfo *ptChnnlMemberInfo)
	{
		m_tHdChnnlInfo[byChnnlIdx] = *ptChnnlMemberInfo;
	}
	void GetHdChnnlInfo(u8 byChnnlIdx,TChnnlMemberInfo *ptChnnlMemberInfo)
	{
		*ptChnnlMemberInfo = m_tHdChnnlInfo[byChnnlIdx];
	}
	
	//找到第一个空闲的通道,没有则返回-1
	s32 FindFreeHdChnnl()
	{
		for(u8 byLoop=0; byLoop< MAXNUM_SVMPB_HDCHNNL; byLoop++)
		{
			if(m_tHdChnnlInfo[byLoop].GetMt().IsNull())
			{
				return byLoop;
			}
		}
		return -1;
	}
	/*==============================================================================
	函数名    :  IsMtAlreadyInChnnl
	功能      :  获取某Mt在哪个HD通道里
	算法实现  :  
	参数说明  :  u8 byMtId		[in]
			 
	返回值说明:  通道号，若MT不存在各个通道，则返回-1
	-------------------------------------------------------------------------------
	修改记录  :  
	日  期       版本          修改人          走读人          修改记录
	2008-12-11					薛亮
	==============================================================================*/
	s32 GetChnnlIdxCtnMt(TMt tMt)
	{
		s32 nChnnlIdx = -1;
		if(tMt.IsNull())
		{
			return nChnnlIdx;
		}

		for(u8 byLoop =0; byLoop < MAXNUM_SVMPB_HDCHNNL; byLoop++)
		{
			if(m_tHdChnnlInfo[byLoop].GetMt() == tMt)
			{
				nChnnlIdx = byLoop;
				break;
			}
		}
		return nChnnlIdx;
	}
	/*==============================================================================
	函数名    :  AddInfoToHdChnnl
	功能      :  把信息加到空闲通道中，不允许相同的信息加到不同的通道
	算法实现  :  
	参数说明  :  u8 byMtId		[in]
			 
	返回值说明:  通道号
	-------------------------------------------------------------------------------
	修改记录  :  
	日  期       版本          修改人          走读人          修改记录
	2008-12-11					薛亮
	==============================================================================*/
	s32 AddInfoToHdChnnl(const TChnnlMemberInfo *ptChnnlMemberInfo)
	{
		//u8 byMtId = ptChnnlMemberInfo->GetMtId();
		TMt tMt = ptChnnlMemberInfo->GetMt();
		s32 nChnnlIdx = GetChnnlIdxCtnMt(tMt);
		if( nChnnlIdx != -1) 
		{
			OspPrintf(TRUE,FALSE,"Mt.%u is Already in the Hd Channel!\n",tMt.GetMtId());
			// xliang [4/1/2009] 刷新一下通道成员属性
			m_tHdChnnlInfo[nChnnlIdx].SetAttrNull();
			if(ptChnnlMemberInfo->IsAttrSpeaker())
			{
				m_tHdChnnlInfo[nChnnlIdx].SetAttrSpeaker();
			}
			if(ptChnnlMemberInfo->IsAttrSelected())
			{
				m_tHdChnnlInfo[nChnnlIdx].SetAttrSelected();
			}
			if(ptChnnlMemberInfo->IsAttrNoneKeda())
			{
				m_tHdChnnlInfo[nChnnlIdx].SetAttrNoneKeda();
			}
			return -1;
		}
		nChnnlIdx = FindFreeHdChnnl();
		if( nChnnlIdx!= -1)
		{
			m_tHdChnnlInfo[nChnnlIdx] = *ptChnnlMemberInfo;
			m_byHDChnnlNum ++;
			return nChnnlIdx;
		}
		else
		{
			return -1;
		}
	}
	/*==============================================================================
	函数名    :  ClearOneChnnl
	功能      :  清某MT对应的通道信息
	算法实现  :  
	参数说明  :  u8	byMtId		[in]
	返回值说明:  TRUE表清成功
	-------------------------------------------------------------------------------
	修改记录  :  
	日  期       版本          修改人          走读人          修改记录
	2008-12-15					薛亮
	==============================================================================*/
	BOOL32 ClearOneChnnl(TMt tMt)
	{
		s32 nChnnlIdx = GetChnnlIdxCtnMt(tMt);
		if(nChnnlIdx!=-1)
		{
			TChnnlMemberInfo tChnnlMemberInfo;
			tChnnlMemberInfo.SetNull();
			SetHdChnnlInfo((u8)nChnnlIdx,&tChnnlMemberInfo);
			m_byHDChnnlNum--;
			//m_byAllChnnlNum--;//没必要
			return TRUE;
		}
		else
		{
			OspPrintf(TRUE,FALSE,"[TVmpChnnlInfo] Mt.%u isn't in any Hd channel!\n",tMt.GetMtId());
			return FALSE;
		}
	}

	u8 GetHdChnnlMtId(u8 byChnnlIdx)	//获取某通道中的MT Id
	{
		return m_tHdChnnlInfo[byChnnlIdx].GetMtId();
	}


	void print(void)//FIXME
	{
		OspPrintf(TRUE, FALSE, "All Chnnl Num: %u\nHd Chnnl Num: %u\n4CIF Chnnl Num: %u\n\
			CIF Chnnl Num: %u\n", \
			m_byAllChnnlNum, m_byHDChnnlNum, m_by4CifChnnlNum, m_byCifChnnlNum);
		OspPrintf(TRUE, FALSE, "---------MtId info in Hd Channels------------\n");
		for(u8 byLoop = 0; byLoop < m_byHDChnnlNum; byLoop++)
		{
			OspPrintf(TRUE, FALSE, "Hd Channel[%u]-->Mt.%u\n",
				byLoop, m_tHdChnnlInfo[byLoop].GetMtId() );
		}

	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;
//终端执行的抢占选项操作
struct TSeizeChoice 
{
public:
//	u8	byMtId;
	TMt tSeizedMt;
	u8	byStopVmp;		//该MT是否停止VMP
	u8  byStopSelected;	//该MT是否停止被选看
	u8	byStopSpeaker;	//该MT是否取消发言人
public:
	TSeizeChoice(void)
	{
		init();
	}
	void init()
	{
		tSeizedMt.SetNull();
		byStopSelected = 0;
		byStopSpeaker  = 0;
		byStopVmp	   = 0;
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

//上次被临时替代的某通道中的VMP成员信息(发言人跟随策略中用)
struct TLastVmpchnnlMemInfo
{
public:
	u8 m_byLastVmpMemInChnnl;
	u8 m_byLastMemType;
public:
	TLastVmpchnnlMemInfo( void )
	{
		Init();
	}
	void Init()
	{
		m_byLastVmpMemInChnnl = ~0;
		m_byLastMemType = 0;
	}
	void SetLastVmpMemChnnl( u8 byMemChnnl ) { m_byLastVmpMemInChnnl = byMemChnnl; }
	u8	 GetLastVmpMemChnnl( void ) { return m_byLastVmpMemInChnnl; }
	void SetLastVmpMemType( u8 byMemType ) { m_byLastMemType = byMemType; }
	u8   GetLastVmpMemType (void ) { return m_byLastMemType; } 

};

struct TSpyVmpInfo
{
	u8		m_byRes;	//分辨率上限
	u8		m_byPos;	//通道位置
	u8		m_bKeepOrgRes;	//表明即使下级调不了分辨率(比如非keda的)，上级还是可以让其以全分辨率进

}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TSpySwitchInfo     // 选看相关的多回传初始信息
{
	u8    m_byMcInstId;   // 某个会控的id
	u8    m_byDstChlIdx;  // 目的通道索引
	u8    m_bySrcChlIdx;  // 源通道索引号
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TSpyHduInfo     // 进高清电视墙相关的多回传初始信息
{
	u8    m_bySrcMtType;  // 电视墙源通道成员类型
	u8    m_bySchemeIdx;  // 预案索引号
	u8    m_byDstChlIdx;  // HDU目的通道索引
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TSpyTVWallInfo     // 进电视墙相关的多回传初始信息
{
	u8    m_bySrcMtType;  // 电视墙源通道成员类型
	u8    m_bySchemeIdx;  // 预案索引号
	u8    m_byDstChlIdx;  // HDU目的通道索引
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TSpyPollInfo     // 进电视墙相关的多回传初始信息
{
	u16   m_wKeepTime;        //终端轮询的保留时间 单位:秒(s)
	u8    m_byPollingPos;        //终端轮询的次数
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TSpyRollCallInfo     // 多回传点名相关信息
{
	TMt m_tCaller;        // 点名人
	TMt m_tOldCaller;     // 老的点名人
	TMt m_tOldCallee;     // 老的被点名人 
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

union USpyInfo
{
	TSpySwitchInfo tSpySwitchInfo;   // 选看的相关信息
	TSpyHduInfo    tSpyHduInfo;      // 进高清电视墙的相关信息
	TSpyPollInfo   tSpyPollInfo;     // 轮询相关信息
	TSpyTVWallInfo tSpyTVWallInfo;   // 进电视墙的相关信息
	TSpyVmpInfo	   tSpyVmpInfo;		 // VMP相关额外信息
	TSpyRollCallInfo tSpyRollCallInfo;  // 点名相关信息

	// 混音的相关信息
	// 画面合成的相关信息
	// 电视墙的相关信息
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TPreSetInReq            // 回传初始信息
{
	TMt m_tSrc;        // 回传的源
	TMt m_tDest;       // 回传的目的端，比如选看，就填选看的目的终端，如果没有明确的目的终端，如回传到上级做发言人时，目的终端就填NULL，代表上级会议。
	u32 m_dwEvId;      // 记录在进行回传交互前，本来应该执行的消息（如改变发言人，终端选看等）
	u8  m_bySpyMode;   // 最初的回传模式
	
	// Dst能力 FIXME
// 	u8  m_byAdjResRequired;		// Is adjusting resolution required
// 	u8	m_byRes;				// Resolution value
// 	u8  m_byReserved;           // 保存字段
	TSimCapSet	m_tSimCapSet;   // 目的端得能力
// 	union USpyInfo             // 与回传各业务相关的一些必要的信息
// 	{
// 		TSpySwitchInfo tSpySwitchInfo;   // 选看的相关信息
// 		TSpyHduInfo    tSpyHduInfo;      // 进电视墙的相关信息
// 		TSpyPollInfo   tSpyPollInfo;     // 轮询相关信息
// 		// 混音的相关信息
// 		// 画面合成的相关信息
// 		// 电视墙的相关信息
// 	} m_tSpyInfo;
	USpyInfo m_tSpyInfo;

public:
	TPreSetInReq()
	{
		memset( this, 0, sizeof(TPreSetInReq) );
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

struct TPreSetInRsp            // PreSetIn 应答信息
{
	TMt m_tSrc;        // 回传的源
	TMt m_tDest;       // 回传的目的
	u32 m_dwEvId;      // 记录在进行回传交互前，本来应该执行的消息（如改变发言人，终端选看等）
	u8  m_bySpyMode;   // 回传模式(BOTH/V/A )
	u32	m_dwSpyBW;	   // 回传将占用多少带宽	
// 	u8  m_byAdjResRequired;		// Is adjusting resolution required
// 	u8	m_byRes;				// Resolution value
// 	u8  m_byReserved;           // 保存字段
	TSimCapSet	m_tSimCapSet;   // 目的端得能力

// 	union USpyInfo
// 	{
// 		TSpySwitchInfo tSpySwitchInfo;   // 选看的相关信息
// 		TSpyHduInfo    tSpyHduInfo;      // 进电视墙的相关信息
// 		TSpyPollInfo   tSpyPollInfo;     // 轮询相关信息
// 		// 混音的相关信息
// 		// 画面合成的相关信息
// 		// 电视墙的相关信息
// 	} m_tSpyInfo;
	USpyInfo m_tSpyInfo;
	
public:
	TPreSetInRsp()
	{
		memset( this, 0, sizeof(TPreSetInRsp) );
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;


struct TSpyResource         // 多回传基本信息
{
public:
	TMt		m_tSpy;		    // 可以是MT，也可能是EQP(如mixer)
    u16     m_wSpyStartPort;    // 记录SpyChnnl, 该值 * PORTSPAN + SPY_MCU_STARTPORT  对应MMCU 转发板上的回传port
	u32     m_dwTotalBW;    // 该Spy回传占用带宽
	u8		m_bySpyMode;	// AUDIO,VIDEO,BOTH
	
	u8		m_byOldSpyMode;   // 保留字段
	u32		m_dwReserved;

public:
	TSpyResource()
	{
		memset( this, 0, sizeof(TSpyResource) );
	}
}
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;



#undef SETBITSTATUS
#undef GETBITSTATUS

#ifdef WIN32
#pragma pack( pop )
#endif

#endif /* __MCUSTRUCT_H_ */




