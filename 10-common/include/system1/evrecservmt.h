/*****************************************************************************
   模块名      : 新方案业务
   文件名      : EvRecservMT.h
   相关文件    : 
   文件实现功能: REC SERVER和MT间接口消息定义
                 *_REQ: 需应答请求
				 *_ACK, *_NACK: 请求之答复
				 *_CMD: 不需应答命令
				 *_NOTIF: 状态通知
   作者        : mcu
   版本        : V0.9  Copyright(C) 2001-2002 KDC, All rights reserved.
-----------------------------------------------------------------------------
   修改记录:
   日  期      版本        修改人      修改内容
   2010/07/21  1.0         Liu Xu      从evmcueqp.h中分出来
******************************************************************************/
#ifndef _EV_RECSERVERMT_H_
#define _EV_RECSERVERMT_H_

#include "osp.h"
#include "eventid.h"
#include "vccommon.h"
#include "errorid.h"

#ifdef WIN32
#pragma comment( lib, "ws2_32.lib" ) 
#pragma pack( push )
#pragma pack( 1 )
#define window( x )	x
#else
#include <netinet/in.h>
#define window( x )
#endif

// Rec Server的App号, 临时定义，以后可能会被修改
#define RECSERV_APP_NO                  (AID_MCU_BGN + 49)
// Rec Server开启的端口号
#define RECSERV_TELNET_PORT             (u16)(2500)

/*MCU和REC间业务接口消息(26101-26300)*/
#define EV_MCUREC_BGN			EV_MCUEQP_BGN + 100
#define EV_MCUREC_END			EV_MCUREC_BGN + 199

//注：为保证程序正确运行，所有成功和失败应答比原消息号分别加1，2

/**********************************************************
 以下为REC服务器和终端之间业务接口 (26101-26300)
**********************************************************/

//录像机向MCU发出注册请求，REC->MCU，消息体为TPeriEqpRegReq结构
OSPEVENT( REC_MCU_REG_REQ,					EV_MCUREC_BGN );
//MCU接受应答，MCU->REC，消息体为消息体为TPeriEqpRegAck
OSPEVENT( MCU_REC_REG_ACK,					EV_MCUREC_BGN + 1 );
//MCU拒绝应答，MCU->REC，无消息体
OSPEVENT( MCU_REC_REG_NACK,					EV_MCUREC_BGN + 2 );

//MT请求获得REC SERVER状态请求, MT->REC SERVER，消息体为TEqp
OSPEVENT( MCU_REC_GETRECSTATUS_REQ,			EV_MCUREC_BGN + 5 );
//回馈REC SERVER状态，REC SERVER->MT，消息体TPeriEqpStatus
OSPEVENT( REC_MCU_GETRECSTATUS_ACK,			EV_MCUREC_BGN + 6 );
//拒绝回馈REC SERVER状态，REC SERVER->MT，消息体为TEqp
OSPEVENT( REC_MCU_GETRECSTATUS_NACK,		EV_MCUREC_BGN + 7 );
//REC SERVER状态通知，REC SERVER->MT，消息体为TPeriEqpStatus
OSPEVENT( REC_MCU_RECSTATUS_NOTIF,			EV_MCUREC_BGN + 8 );

/*
 *录像列表请求消息：
 *终端收到请求后分配发送录像文件通知，全部发送完毕后发送ACK消息
 *若终端拒绝发送列表，则仅发送NACK消息。
 */
//MT请求终端给出录像列表命令，MT->REC SERVER，消息体为TEqp
OSPEVENT( MCU_REC_LISTALLRECORD_REQ,		EV_MCUREC_BGN + 10 );
//REC SERVER列应答(完毕)消息，REC SERVER->MT,消息体为TEqp
OSPEVENT( REC_MCU_LISTALLRECORD_ACK,		EV_MCUREC_BGN + 11 );
//REC SERVER拒绝录像列表请求，REC SERVER->MT，消息体为TEqp
OSPEVENT( REC_MCU_LISTALLRECORD_NACK,		EV_MCUREC_BGN + 12 );
//录像机列表通知消息，REC SERVER->MT, 消息体为TEqp+TRecFileListNotify
OSPEVENT( REC_MCU_LISTALLRECORD_NOTIF,		EV_MCUREC_BGN + 13 );


//MT请求获得REC SERVER录像通道状态请求, MT->REC SERVER, 消息体为TEqp，信道号位于消息头中
OSPEVENT( MCU_REC_GETRECORDCHNSTATUS_REQ,	EV_MCUREC_BGN + 15 );
//回馈REC SERVER信道状态，REC SERVER->MT，消息体TEqp+TRecChnnlStatus
OSPEVENT( REC_MCU_GETRECORDCHNSTATUS_ACK,	EV_MCUREC_BGN + 16 );
//拒绝回馈REC SERVER信道状态，REC SERVER->MT，消息体为TEqp
OSPEVENT( REC_MCU_GETRECORDCHNSTATUS_NACK,	EV_MCUREC_BGN + 17 );
//REC SERVER录像信道状态通知，REC SERVER->MT，消息体为TEqp+TRecChnnlStatus
OSPEVENT( REC_MCU_RECORDCHNSTATUS_NOTIF,	EV_MCUREC_BGN + 18 );

//MT请求获得REC SERVER放像通道状态请求, MT->REC SERVER, 消息体为TEqp，信道号位于消息头中
OSPEVENT( MCU_REC_GETPLAYCHNSTATUS_REQ,		EV_MCUREC_BGN + 20 );
//回馈REC SERVER信道状态，REC SERVER->MT，消息体TEqp+TRecChnnlStatus
OSPEVENT( REC_MCU_GETPLAYCHNSTATUS_ACK,		EV_MCUREC_BGN + 21 );
//拒绝回馈REC SERVER信道状态，REC SERVER->MT，消息体为TEqp
OSPEVENT( REC_MCU_GETPLAYCHNSTATUS_NACK,	EV_MCUREC_BGN + 22 );
//REC SERVER放像信道状态通知，REC SERVER->MT，消息体为TEqp+TRecChnnlStatus
OSPEVENT( REC_MCU_PLAYCHNSTATUS_NOTIF,		EV_MCUREC_BGN + 23 );


//获取录相进度，MT->REC SERVER, 消息体：无 (信道号位于消息头)
OSPEVENT( MCU_REC_GETRECPROG_CMD,           EV_MCUREC_BGN + 24 );
//MT当前录像进度通知消息，REC SERVER->MT，消息体为TEqp+TRecProg，信道号位于消息头
OSPEVENT( REC_MCU_RECORDPROG_NOTIF,			EV_MCUREC_BGN + 25 );

// MT获取放相进度，MT->REC SERVER，消息体：无 (信道号位于消息头)
OSPEVENT( MCU_REC_GETPLAYPROG_CMD,          EV_MCUREC_BGN + 26 );
//MT当前放像进度通知消息，REC SERVER->MT，消息体为TEqp+TRecProg，信道号位于消息头
OSPEVENT( REC_MCU_PLAYPROG_NOTIF,			EV_MCUREC_BGN + 27 );
//MT异常通知消息，REC SERVER->MT，消息体为TEqp，信道号和错误码位于消息头
OSPEVENT( REC_MCU_EXCPT_NOTIF,				EV_MCUREC_BGN + 28 );


////////////////
//录像消息
//消息体为TEqp(被录像的终端, 以下请求同)
// + TEqp( 所要使用得录像机) + TRecStartPara + TMediaEncrypt(video) +
//TDoublePayload(video) + TMediaEncrypt(audio) + TDoublePayload(video) +
//TMediaEncrypt(double video) + TDoublePayload(double video) + 录像名 + TCapSupportEx
// MT请求录像，MT->REC SERVER，消息体为TEqp
OSPEVENT( MCU_REC_STARTREC_REQ,				EV_MCUREC_BGN + 70 );
//REC SERVER同意MT录像请求应答，REC SERVER->MT，消息体为TEqp，返回的信道号位于消息头
OSPEVENT( REC_MCU_STARTREC_ACK,				EV_MCUREC_BGN + 71 );
//拒绝MT录像应答，REC SERVER->MT，消息体为TEqp
OSPEVENT( REC_MCU_STARTREC_NACK,			EV_MCUREC_BGN + 72 );

// MT请求暂停录像，MT->REC SERVER，消息体为TEqp
OSPEVENT( MCU_REC_PAUSEREC_REQ,				EV_MCUREC_BGN + 75 );
//REC SERVER同意暂停录像请求，REC SERVER->MT，消息体为TEqp
OSPEVENT( REC_MCU_PAUSEREC_ACK,				EV_MCUREC_BGN + 76 );
//REC SERVER拒绝暂停录像请求，REC SERVER->MT，消息体为TEqp
OSPEVENT( REC_MCU_PAUSEREC_NACK,			EV_MCUREC_BGN + 77 );

//继续录像请求，MT->REC SERVER，消息体为TEqp
OSPEVENT( MCU_REC_RESUMEREC_REQ,			EV_MCUREC_BGN + 80 );
//同意继续录像，REC SERVER->MT，消息体为TEqp
OSPEVENT( REC_MCU_RESUMEREC_ACK,			EV_MCUREC_BGN + 81 );
//拒绝继续录像,REC SERVER->MT，消息体为TEqp
OSPEVENT( REC_MCU_RESUMEREC_NACK,			EV_MCUREC_BGN + 82 );

//停止录像请求，MT->REC SERVER，消息体为TEqp
OSPEVENT( MCU_REC_STOPREC_REQ,				EV_MCUREC_BGN + 85 );
//同意停止录像应答，REC SERVER->MT，消息体为TEqp
OSPEVENT( REC_MCU_STOPREC_ACK,				EV_MCUREC_BGN + 86 );
//拒绝停止录像应答，REC SERVER->MT，消息体为TEqp
OSPEVENT( REC_MCU_STOPREC_NACK,				EV_MCUREC_BGN + 87 );


//改变录像模式请求, 消息体TEqp ＋ u8( REC_MODE_NORMAL, REC_MODE_SKIPFRAME )
OSPEVENT( MCU_REC_CHANGERECMODE_REQ,		EV_MCUREC_BGN + 90 );
//同意，REC SERVER->MT，消息体为 TEqp 
OSPEVENT( REC_MCU_CHANGERECMODE_ACK,		EV_MCUREC_BGN + 91 );
//反对，REC SERVER->MT，消息体为 TEqp 
OSPEVENT( REC_MCU_CHANGERECMODE_NACK,		EV_MCUREC_BGN + 92 );


//MT请求删除REC SERVER中的记录，MT->REC SERVER ,消息体为TEqp+记录名(0结尾字符串)
OSPEVENT( MCU_REC_DELETERECORD_REQ,			EV_MCUREC_BGN + 93 );
//REC SERVER同意并成功删除录像文件应答, REC SERVER->MT
//消息体为TEqp
OSPEVENT( REC_MCU_DELETERECORD_ACK,			EV_MCUREC_BGN + 94);
//REC SERVER拒绝删除录像 消息体TEqp
OSPEVENT( REC_MCU_DELETERECORD_NACK,		EV_MCUREC_BGN + 95 );


//MT请求更改REC SERVER记录文件, MT->REC SERVER
//消息体为TEqp + u8(旧记录名长度) + 旧记录名 + u8(新记录名长度) + 新记录名
OSPEVENT( MCU_REC_RENAMERECORD_REQ,			EV_MCUREC_BGN + 96 );
//同意，消息体为TEqp
OSPEVENT( REC_MCU_RENAMERECORD_ACK,			EV_MCUREC_BGN + 97 );
//反对，消息体为TEqp
OSPEVENT( REC_MCU_RENAMERECORD_NACK,		EV_MCUREC_BGN + 98 );

//发布录像请求 MT->REC SERVER，消息体为TEqp + u8(PUBLISH_LEVEL) + 录像名
OSPEVENT( MCU_REC_PUBLISHREC_REQ,			EV_MCUREC_BGN + 100 );
//同意，REC SERVER->MT，消息体为 TEqp
OSPEVENT( REC_MCU_PUBLISHREC_ACK,			EV_MCUREC_BGN + 101 );
//反对，REC SERVER->MT，消息体为 TEqp
OSPEVENT( REC_MCU_PUBLISHREC_NACK,			EV_MCUREC_BGN + 102 );

//取消发布录像请求 MT->REC SERVER，消息体为TEqp +  录像名
OSPEVENT( MCU_REC_CANCELPUBLISHREC_REQ,		EV_MCUREC_BGN + 105 );
//同意，REC SERVER->MT，消息体为 TEqp
OSPEVENT( REC_MCU_CANCELPUBLISHREC_ACK,		EV_MCUREC_BGN + 106 );
//反对，REC SERVER->MT，消息体为 TEqp
OSPEVENT( REC_MCU_CANCELPUBLISHREC_NACK,	EV_MCUREC_BGN + 107 );

//REC SERVER请求关键帧, REC SERVER->MT
OSPEVENT( REC_MCU_NEEDIFRAME_CMD,	        EV_MCUREC_BGN + 108 );


//终端向录像机服务器发出注册请求，MT->REC SERVER，消息体为TMtRegReq结构
OSPEVENT( MT_RECSERV_REG_REQ,			    EV_MCUREC_BGN  + 109);
//录像机服务器接受应答，REC SERVER->MT，消息体为消息体为TMtRegAck
OSPEVENT( RECSERV_MT_REG_ACK,				EV_MCUREC_BGN + 110 );
//录像机服务器拒绝应答，REC SERVER->MT，无消息体
OSPEVENT( RECSERV_MT_REG_NACK,				EV_MCUREC_BGN + 111 );


#define     MAXNUM_RECORDER_CHNNL			32	//录像机最大通道个数(含录像和放像通道)
#define		MAXLEN_EQP_ALIAS                16   //外设别名最大长度
#define     MAXLEN_RECORD_NAME              64  //上报外设状态时录像文件名的长度


// 录像机回复MT的ACK信息
struct TMtRegAck : public TEqp
{
protected:
	u32   		m_dwIpAddr;		//录像机IP地址
	u16 		m_wStartPort;	//录像机起始接收端口
	u8  		m_byChannlNum;	//录像机接收信道数
	s8          m_achAlias[MAXLEN_EQP_ALIAS];
    //4.0R3扩展字段
    u16         m_wVersion;     //版本信息
    //4.5高清扩展字段
    BOOL        m_bHDEqp;       //是否高清外设， 无效值

public:
    TMtRegAck(void) { memset(this, 0, sizeof(TMtRegAck)); }
    //录像机外设IP地址
    //输入：IP地址(网络序)
	void SetPeriEqpIpAddr( const u32    &dwIpAddr )	{ m_dwIpAddr = dwIpAddr; }
    //获得录像机IP地址
    //返回值：IP地址(网络序)
	u32    GetPeriEqpIpAddr() const	{ return m_dwIpAddr; }
	//设置录像机接收起始端口
	void SetStartPort( const u16  & wStartPort )	{ m_wStartPort = htons(wStartPort); }
	//获得录像机接收起始端口
	u16  GetStartPort() const	{ return ntohs( m_wStartPort ); }
	//设置录像机接收信道数目
	void SetChnnlNum( const u8   & byChannlNum )	{ m_byChannlNum = byChannlNum; }
	//获得录像机接收信道数目
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

//定义MT注册信息
struct TMtRegReq
{
protected:
	u32   		m_dwIpAddr;			//MT接收地址
	u16 		m_wStartPort;		//MT接收起始端口号
    u32         m_dwAnotherMpcIp;   //主备时：另外一块mpc板地址（用来对外设配置的备板mpc地址进行校验）
	u32         m_dwMsSSrc;         //主备时：用于标注一次系统运行，只要该值变化就说明发生过主备同时重启

public:
	//得到上级MT交换接收数据IP地址
    u32    GetMcuIpAddr( void ) const { return ntohl(m_dwIpAddr); }

	//设置上级MT交换接收数据IP地址
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

struct TMTRegInfo
{
    TMtRegReq m_tMtRegReq;
    s8        m_aliase[MAXLEN_RECORD_NAME+1];
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
    
    void Print() const
    {
        OspPrintf(TRUE, FALSE, "m_byRealPayload is %d, m_byActivePayload is %d\n",
            m_byRealPayload, m_byActivePayload);
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

//定义外设状态结构, size = 2435(TRecStatus = 2412)
struct TPeriEqpStatus : public TEqp
{
public:
    u8  	m_byOnline;		//是否在线
    union UStatus
    {
        TRecStatus		tRecorder;
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

#define MAX_REC_FILE_NAME 128
typedef struct tagTRecStartParam
{
public:
	//TEqp			TEqp;
    // 新加的
    TRecRtcpBack    tRecRtcpBack;
    // 新加的
    u8              byNeedPrs;          //是否重传
	
	TRecStartPara	tRecStartPara;
	TMediaEncrypt	tPriVideoEncrypt;
	TMediaEncrypt	tSecVideoEncrypt;
	TMediaEncrypt	tAudVideoEncrypt;
	TDoublePayload	tPriPayload;
	TDoublePayload	tSecPayload;
	TDoublePayload	tAudPayload;
	s8				achFileName[MAX_REC_FILE_NAME+1];
	TCapSupportEx	tCapSupportEx;
public:
    tagTRecStartParam()
    {
        memset( this->achFileName, 0, MAX_REC_FILE_NAME+1 );
    };
}TRecStartRaram
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

typedef struct tagErrInfo
{
protected:
    u16 m_wErrCode;                      // Nack发生时的错误码
public:
    //获取错误码
    u16   GetErrorCode( void ) const	{ return ntohs( m_wErrCode ); }
    //设置错误码
    void  SetErrorCode(u16 wError) 	{ m_wErrCode = htons( wError ); }
}TErrorInfo
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
;

#define ERR_REC_NOERROR         ERR_REC_BGN + 0        //没有错误
#define ERR_REC_NORECORD        ERR_REC_BGN + 1        //没有记录
#define ERR_REC_OPENRECORD      ERR_REC_BGN + 2        //打开记录失败
#define ERR_REC_UMMATCHCMD      ERR_REC_BGN + 3        //不匹配的命令！例如让一个播放设备开始录像
#define ERR_REC_VALIDCHN        ERR_REC_BGN + 4        //无效的通道
#define ERR_REC_RECORDING       ERR_REC_BGN + 5        //正在录像
#define ERR_REC_PLAYING         ERR_REC_BGN + 6        //正在播放
#define ERR_REC_NOTPLAY         ERR_REC_BGN + 7        //播放通道没在播放 
#define ERR_REC_NOTRECORD       ERR_REC_BGN + 8        //录像通道没在录像
#define ERR_REC_ACTFAIL         ERR_REC_BGN + 9        //执行指定的请求动作失败
#define ERR_REC_CURDOING        ERR_REC_BGN + 10       //请求的动作当前正在执行
#define ERR_REC_RCMD_TO_PCHN    ERR_REC_BGN + 11       //一条播放通道命令发到录像通道
#define ERR_REC_PCMD_TO_RCHN    ERR_REC_BGN + 12       //一条录像通道命令发到播放通道
#define ERR_REC_DISKFULL        ERR_REC_BGN + 13       //磁盘满
#define ERR_REC_FILEDAMAGE      ERR_REC_BGN + 14       //文件损坏
#define ERR_REC_FILEEMPTY       ERR_REC_BGN + 15       //空文件
#define ERR_REC_FILEUSING       ERR_REC_BGN + 16       //指定文件正在被操作
#define ERR_REC_FILENOTEXIST    ERR_REC_BGN + 17       //指定文件不存在
#define ERR_REC_PUBLICFAILED    ERR_REC_BGN + 18       //发布失败
#define ERR_REC_RENAMEFILE      ERR_REC_BGN + 19       //文件名冲突,更改文件名失败
#define ERR_REC_FILEEXISTED     ERR_REC_BGN + 20       //文件名冲突,无法录像
#define ERR_REC_PLAYERRPAYLOAD  ERR_REC_BGN + 21       //放像文件媒体载荷类型与会议不匹配
#define ERR_REC_CALLLIBFAILED   ERR_REC_BGN + 22       //调用录像库失败,建议重新安装
#define ERR_REC_SETMOTHODFAILED ERR_REC_BGN + 23       //录像方式设置失败
#define ERR_REC_PALYFILERES		ERR_REC_BGN + 24	   //录像文件分辨率偏大
#define ERR_REC_FILENAMETOOLONG ERR_REC_BGN + 25       //输入文件名过长, add by jlb  081026
#define ERR_REC_SERVER_BUSY     ERR_REC_BGN + 27       //输入文件名过长, add by liuxu 100725

#endif