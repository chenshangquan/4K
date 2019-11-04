/*****************************************************************************
   模块名      : 卫星常量定义
   文件名      : satmtstrc.h
   相关文件    : satconst.h
   文件功能    : 
   作者        : 张斯红
   版本        : V1.0  Copyright(C) 2001-2002 KDC, All rights reserved.
-----------------------------------------------------------------------------
   修改记录:
   日  期      版本        修改人      修改内容
   2004/11/02  1.0         张明义      
******************************************************************************/

#ifndef _SAT_MCU_MT_STRUCT_H_
#define _SAT_MCU_MT_STRUCT_H_

#include "osp.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
#ifndef WIN32
#include <netinet/in.h>
#endif
#include "kdvsys.h"
#include "satconst.h"


#ifdef WIN32
#pragma comment( lib, "ws2_32.lib" ) 
#pragma pack( push )
#pragma pack( 1 )
#endif

#ifdef WIN32
#define PACKED 
#else
#define PACKED __attribute__((__packed__))	// 取消编译器的优化对齐
#endif // WIN32

#ifdef WIN32
	#define window( x )	x
#else
	#define window( x )
#endif
//消息封装
typedef struct tagITSatMessageHeader
{
	enum{
		emMCUID = 0x0000,
		emNMSID = 0xFFF0,
		emBROADCAST = 0xFFFF
	};
	protected:
		u16 m_wEventId; //消息ID
		u16 m_wMsgSN;   //消息流水号(1-65535)
		u8  m_byConfIdx; //会议索引(0xFF 表示向所有的会议广播消息)
		u16 m_wSrcId;   //消息发送者ID MCU应当天0 ,卫星网管系统应当天 0xFFF0 ,终端添相应的ID
		u16 m_wDstId;   //消息发送目的ID MCU应当天0 ,
		                //卫星网管系统应当天 0xFFF0 ,终端添相应的ID
		                //0xFFFF 表示广播消息 
		u8  m_byReserve;//保留字固定为零
	public:
		tagITSatMessageHeader()
		{
			m_wEventId = ntohs(0);
			m_wMsgSN   = ntohs(1);
			m_byConfIdx = 0xFF;
			m_wSrcId   = ntohs(emMCUID);
			m_wSrcId   = ntohs(emBROADCAST);
			m_byReserve = 0;
		}

		//获取消息ID
		u16 GetEventId()
		{
			return ntohs(m_wEventId);
		}
		//设置消息ID
		void SetEventId( u16 wEventId )
		{
			m_wEventId = htons(wEventId);
		}
		//获取消息流水号
		u16 GetMsgSN()
		{
			return ntohs(m_wMsgSN );
		}
		//设置消息流水号
		void SetMsgSN( u16 wMsgSN )
		{
			m_wMsgSN = ntohs(wMsgSN);
		}

		//获取会议索引号
		u8 GetConfIdx()
		{
			return m_byConfIdx;
		}
		//设置会议索引号
		void SetConfIdx( u8 byConfIdx)
		{
			m_byConfIdx = byConfIdx;
		}

		//获取消息发送源ID号
		u16 GetSrcId()
		{
			return ntohs(m_wSrcId);
		}
		//设置消息发送源ID号
		void SetSrcId( u16 wSrcId)
		{
			m_wSrcId = htons(wSrcId);
		}
        //获取消息发送目的ID号
		u16 GetDstId()
		{
			return ntohs(m_wDstId);
		}
        //设置消息发送目的ID号
		void SetDstId( u16 wDstId)
		{
			m_wDstId = htons(wDstId);
		}
}PACKED ITSatMsgHdr;


typedef struct tagTSatBitrate
{

	tagTSatBitrate(){memset(this,0,sizeof(tagTSatBitrate));	}
	protected:
		u8 m_byBitrate;
	public:
		//获取码率 (单位:Kbps)
		u16 Get()
		{
			return m_byBitrate*32;
		}

		//设置码率 (单位:Kbps )
		void Set( u16 wBitrate )
		{
			if( wBitrate >= 255*32 )
			{
				m_byBitrate = 255;
			}
			else
			{
				m_byBitrate = (u8)(wBitrate/32);
			}
		}
}PACKED ITSatBitrate;

//终端信息
typedef struct tagTInterfaceMtTopo
{
	enum EMMtType
	{
		emFULL    = 1,//全双工 直连终端
		emUPALLOC = 2,//回传通道分配（卫星终端）
	};
	enum EMModemType
	{
		emMODEM_70M_LBAND     = 1,            
		emMODEM_LBAND_70M     = 2,            
		emMODEM_LBAND_LBAND   = 3 
	};
	tagTInterfaceMtTopo(){memset(this,0,sizeof(tagTInterfaceMtTopo));}
protected:
	u16 m_wMtId;
	u8  m_byConnectType;
	char m_achAlias[MAXLEN_SATMTALIAS];
	u32 m_dwMtIp;
	u32  m_dwModemIp;
	u16  m_wModemPort;
	u8   m_byModemType;
	

	
public:
	void SetMtId( u16 wMtId )
	{
		m_wMtId = htons(wMtId);
	}
	u16 GetMtId(void)
	{
		return ntohs(m_wMtId);
	}
	
	void SetMtConnectType( u8 byMode )
	{
		m_byConnectType = byMode;
	}
	u8 GetMtConnectType(void)
	{
		return m_byConnectType;
	}
	
	void SetMtModemIp( u32 dwIp )
	{
		m_dwModemIp = dwIp;
	}
	u32 GetMtModemIp( void )
	{
		return m_dwModemIp;
	}
	
	void SetMtModemPort( u16 wPort )
	{
		m_wModemPort = htons(wPort);
	}
	u16 GetMtModemPort(void)
	{
		return ntohs(m_wModemPort);
	}
	
	void SetMtModemType( u8 byType )
	{
		m_byModemType = byType;
	}
	u8 GetMtModemType()
	{
		return m_byModemType;
	}
	
	void SetMtAlias( LPCSTR lpszAlias )
	{
		if( lpszAlias != NULL )
		{
			strncpy( m_achAlias, lpszAlias, sizeof( m_achAlias ) );
			m_achAlias[sizeof( m_achAlias ) - 1] = '\0';
		}
		else
		{
			memset( m_achAlias, 0, sizeof( m_achAlias ) );
		}
	}
	char* GetMtAlias()
	{
		return m_achAlias;
	}
	
	void SetMtIp( u32 dwIp )
	{
		m_dwMtIp = dwIp;
	}
	
	u32 GetMtIp()
	{
		return m_dwMtIp;
	}
}PACKED TInterfaceMtTopo ,ITSatMtInfo;

typedef struct tagTInterfaceConfList
{
	u8 m_byConfIdx;
	char m_achName[16];
	tagTInterfaceConfList()
	{
		memset(this,0,sizeof(tagTInterfaceConfList));
	}
public:
	void SetConfIdx( u8 byIndex )
	{
		m_byConfIdx = byIndex;
	}
	u8 GetConfIdx(void)
	{
		return m_byConfIdx;
	}
	
	void SetConfName( LPCSTR lpszAlias )
	{
		if( lpszAlias != NULL )
		{
			strncpy( m_achName, lpszAlias, sizeof( m_achName ) );
			m_achName[sizeof( m_achName ) - 1] = '\0';
		}
		else
		{
			memset( m_achName, 0, sizeof( m_achName ) );
		}
	}
	char* GetConfName()
	{
		return m_achName;
	}
	
}PACKED TInterfaceConfList ,ITSatConfList;

typedef struct tagTInterfaceList
{
	tagTInterfaceList()
	{
		memset(this,0,sizeof(tagTInterfaceList));
	}
public:
	u8 m_abyMemberList[MAXNUM_SATMT/8];
public:
	void SetMember( u16 wWhoId )
	{
		if( wWhoId > MAXNUM_SATMT || wWhoId==0 )
		{
			OspPrintf( TRUE,FALSE, "Mt Id out of range %d", wWhoId );
			return ;
		}
		wWhoId -=1;
		m_abyMemberList[wWhoId / 8] |= 1 << ( wWhoId % 8 );
		return;
	}
	void RemoveMember( u16 wWhoId )
	{
		if( wWhoId > MAXNUM_SATMT || wWhoId==0 )
		{
			OspPrintf(TRUE,FALSE,"Mt Id out of range %d", wWhoId );
			return ;
		}
		wWhoId -=1;
		m_abyMemberList[wWhoId / 8] &= ~( 1 << ( wWhoId % 8 ) );
		return;
	}

	BOOL IsInList( u16 wWhoId ) const
	{
		if( wWhoId > MAXNUM_SATMT || wWhoId==0 )
		{
			OspPrintf(TRUE,FALSE,"Mt Id out of range %d", wWhoId );
			return FALSE;
		}
		wWhoId -=1;
		return ( ( m_abyMemberList[wWhoId / 8] & ( 1 << ( wWhoId % 8 ) ) ) != 0 );
	}
}PACKED TInterfaceList ,ITSatMtList;

typedef TInterfaceList TMtList;
//定义画面复合
typedef struct tagTVMPParam
{
protected:
    u8      m_byVmpStyle;			//合成风格
    u8		m_byBrdcst;			//是否广播
    u16    	m_wMt[16];        		//成员ID
public:
	inline u8 GetVmpStyle( void ) const
	{
		return( m_byVmpStyle );
	}
	
	inline void SetVmpStyle( u8 byStyle )
	{
		m_byVmpStyle = byStyle;
	}
	
	inline void SetVmpBrd( BOOL bBroad )
	{
		if ( bBroad == TRUE )
			m_byBrdcst = 1;
		else
			m_byBrdcst = 0;
	}
	
	inline BOOL IsVmpBrd( ) const
	{
		return ( m_byBrdcst == 1 );
	}

	inline void SetMtId( u8 byPos , u16 wMtId )
	{
		if( byPos >16 )
			return;
		m_wMt[ byPos-1] = htons( wMtId );
	}

	inline u16 GetMtId( u8 byPos ) const
	{
		if ( byPos == 0 || byPos > 16 )
			return 0;
		return ntohs( m_wMt[byPos-1] );
	}

}PACKED ITSatVmpParam;


typedef struct tagTInterfaceConfInfo
{
	tagTInterfaceConfInfo()
	{
		memset(this,0,sizeof(tagTInterfaceConfInfo));
	}

protected:
	u16 m_wSpeakerId;
	u16 m_wChairId;
	u8  m_byLineNum;
	u8  m_bySwitchTime;
	char m_achName[32];
	u8  m_byAudioType;
	u8  m_byVideoType;   //视频频类型
	u8  m_byVidResolution;//视频分辨率
    ITSatBitrate m_tConfBitrate;
	/*--------------------------------*/
	u8  m_byState;//混音，
	/* 0x 0 0 0 0 0 x x x
		      |    | |_____混音状态
		      |    |_______画面复合状态
		      |____________加密信息
	*/
	u8  m_achKey[9];
public:
	TMtList m_tNonActiveMt;//受邀
	TMtList m_tActiveMt;//签到
	TMtList m_tCanSendMt;//可发送，上传(直连和占上传通路)
	
	TMtList m_tNearMuteMt; //静音
	TMtList m_tFarMuteMt; //哑音
	ITSatVmpParam m_tVmpMt; //画面复合

public:
	//获取会议视频格式
	u8 GetVideoType()
	{
		return m_byVideoType;
	}
	//设置会议视频格式
	void SetVideoType( u8 byType)
	{
		m_byVideoType = byType;
	}
	//获取会议视频分辨率
	u8 GetResolution()
	{
		return m_byVidResolution;
	}
	//设置会议视频分辨率
	void SetResolution( u8 byResolution)
	{
		m_byVidResolution = byResolution;
	}

	//设置会议音频分辨率
	void SetAudioType( u8 byType )
	{
		m_byAudioType = byType;
	}

	//设置会议音频分辨率
	u8 GetAudioType()
	{
		return m_byAudioType;
	}
	
	//设置会议码率 (单位64K)
	void SetBitrate( u16 wBitrate )
	{
		m_tConfBitrate.Set( wBitrate );
	}
	
	//获取会议会议码率 (单位64K)
	u16 GetBitrate()
	{
		return m_tConfBitrate.Get();
	}


	//发言人
	void SetSpeakerId( u16 wSpeakerId )
	{
		m_wSpeakerId = htons(wSpeakerId);
	}
	u16 GetSpeakerId(void)
	{
		return ntohs(m_wSpeakerId);
	}
	//主席
	void SetChairId( u16 wChairId )
	{
		m_wChairId = htons(wChairId);
	}
	u16 GetChairId(void)
	{
		return ntohs(m_wChairId);
	}
	//混音状态
	void SetMixing(void)
	{
		m_byState |= 1;
	}
	void SetNoMixing(void)
	{
		m_byState &=~1;
	}
	BOOL IsMixing(void)
	{
		return ( (m_byState & 1 ) != 0 );
	}
	//画面复合状态
	void SetVmping(void)
	{
		m_byState |= 0x2;
	}
	void SetNoVmping(void)
	{
		m_byState &= ~0x2;
	}
	BOOL IsVmping(void)
	{
		return ( (m_byState & 0x2 ) != 0 );
	}
	//画面复合广播状态
/*	void SetVmpBrdst(void)
	{
		m_byState |= 0x4;
	}
	void SetVmpNoBrdst(void)
	{
		m_byState &= ~0x4;
	}
	BOOL IsVmpBrdst(void)
	{
		return ( (m_byState & 0x4 ) != 0 );
	}*/
	/*会议是否加密,终端创建会议要进行设置
	*/
	void SetConfEncrypted( BOOL bEncrypt )
	{
		if ( bEncrypt )
			m_byState |= 0x08;
		else
			m_byState &= ~0x08;
	}
	
	BOOL IsConfEncrypted()
	{
		return ( (m_byState & 0x08 ) != 0 );
	}
	/*会议密码，终端创建会议时填写*/
	void SetConfKey( u8* buf, u8 len)
	{
		memcpy( m_achKey,buf,len);
		m_achKey[8] = '\0';
	}
	u8* GetConfKey( )
	{
		return m_achKey;
	}
	//会议线路
	void SetConfLineNum( u8 byNum )
	{
		m_byLineNum = byNum;
	}
	u8 GetConfLineNum(void) const
	{
		return m_byLineNum;
	}
	//切换间隔
	void SetConfSwitchTime( u8 byTime )
	{
		m_bySwitchTime = byTime;	
	}
	u8 GetConfSwitchTime(void) const
	{
		return m_bySwitchTime;
	}
	LPCSTR GetConfName( void ) const
	{
		return( ( LPCSTR )m_achName );
	}

	void SetConfName( LPCSTR lpszBuf )
	{
		strncpy( m_achName, lpszBuf, sizeof( m_achName ) );
		m_achName[ sizeof( m_achName ) - 1] = '\0';
	}
	
}PACKED TInterfaceConfInfo ,ITSatConfInfo;

typedef struct tagTInterfaceMtKey
{
	tagTInterfaceMtKey()
	{
		memset(this,0,sizeof(tagTInterfaceMtKey));
	}
protected:
	u16 m_wMtId;
	char szDesKey[16];
public:
	void SetMtKey( u16 MtId,  char* key )
	{
		m_wMtId = htons( MtId );
		for ( u8 byLoop = 0 ; byLoop < 16 ; byLoop ++)
			szDesKey[byLoop] = key[byLoop];
	}
	//可能不含结束符，请直接拷贝16个字节
	char* GetMtKey()
	{
		return szDesKey;
	}
	//获取密钥的MT ID
	u16 GetMtId()
	{
		return ntohs(m_wMtId);
	}
	//设置密钥的MT ID
	void SetMtId( u16 wMtId )
	{
		m_wMtId = ntohs(wMtId);
	}
}PACKED TInterfaceMtKey,ITSatMtKey;

typedef struct tagTInterfaceMtCamera
{
	u8 m_byCmd;
	u8 m_byCmdVal;
public:
	void SetCameraCmd( u8 byNewCmd )
	{
		m_byCmd = byNewCmd;
	}
	u8 GetCameraCmd(void)
	{
		return m_byCmd;
	}
	
	void SetCmdVal( u8 byNewVal )
	{
		m_byCmdVal = byNewVal;
	}
	u8 GetCmdVal(void)
	{
		return m_byCmdVal;
	}
}PACKED ITSatCamCmd;

typedef struct tagTInterfaceMtAddr
{
	tagTInterfaceMtAddr(){memset(this,0,sizeof(tagTInterfaceMtAddr));}
protected:
	u32 m_dwIpAddr;
	u16 m_wPort;
public:
	void SetIpAddr( u32 dwIp )
	{
		m_dwIpAddr =  htonl(dwIp) ;
	}
	u32 GetIpAddr(void)
	{
		return ntohl(m_dwIpAddr);
	}
	
	void SetPort( u16 wPort )
	{
		m_wPort = htons( wPort );
	}
	u16 GetPort(void)
	{
		return ntohs( m_wPort );
	}
}PACKED TInterfaceMtAddr,ITSatTransAddr;


typedef struct tagTSatMtBitrateList
{
	
protected:
	ITSatBitrate m_atBitrate[MAXNUM_SATMT];
public:
	
	u16 GetBitrate( u16 wMtId )
	{
		if( wMtId == 0 || wMtId > MAXNUM_SATMT )
		{
			OspPrintf(TRUE,FALSE,"Get Mt.%d bitrate out of range!\n",wMtId );
			return 0;
		}
		return m_atBitrate[wMtId-1].Get();
	}

	void SetBitrate( u16 wMtId ,u16 wBitrate )
	{
		if( wMtId == 0 || wMtId > MAXNUM_SATMT )
		{
			OspPrintf(TRUE,FALSE,"Set Mt.%d bitrate out of range!\n",wMtId );
			return ;
		}
		m_atBitrate[wMtId-1].Set(wBitrate);
	}

}PACKED ITSatMtBitrateList;

typedef struct tagTSatMtId
{
protected:
	u16 m_wMtId;
public:
	
	void Set( u16 wMtId )
	{
		m_wMtId = htons( wMtId );
	}
	u16 Get(void)
	{
		return ntohs( m_wMtId );
	}
}PACKED ITSatMtId;

//卫星会议地址信息
typedef struct tagTSatConfAddrInfo
{
	tagTSatConfAddrInfo(){ memset( this,0,sizeof(tagTSatConfAddrInfo));}
public:
	ITSatMtId      tAudMulticastSrcId;// 音频组播码流视频源ID
	ITSatMtId      tVidMulticastSrcId;// 视频组播码流视频源ID
	ITSatMtId      tAudUnitcastSrcId; // 音频单播码流视频源ID
	ITSatMtId      tVidUnitcastSrcId; // 视频单播码流视频源ID

	ITSatTransAddr tMcuRcvMediaAddr;     // MCU接收码流(交换板)地址 ,视频起始端口号
    ITSatTransAddr tAudMulticastAddr;    // 音频组播地址信息 
    ITSatTransAddr tVidMulticastAddr;    // 音频组播地址信息 
	ITSatTransAddr tAudUnitcastAddr;     // 视频单播地址信息-该地址仅进端口号有效
	ITSatTransAddr tVidUnitcastAddr;     // 视频单播地址信息-该地址仅进端口号有效

	ITSatMtList    tAudMulticastMmbList; // 音频组播接收成员列表 
	ITSatMtList    tVidMulticastMmbList; // 视频组播接收成员列表 
	ITSatMtList    tAudUnitcastMmbList;  // 音频单播接收成员列表 
    ITSatMtList    tVidUnitcastMmbList;  // 视频单播接收成员列表

	//双流支持（暂不考虑双流单播，即双流选看）
	ITSatMtId      tDSMulticastSrcId;	// 双流组播码流视频源ID
	ITSatTransAddr tDSMulticastAddr;	// 双流组播地址信息
	ITSatMtList    tDSMulticastMmbList; // 双流组播接收成员列表 
}PACKED ITSatConfAddrInfo;

//定义短消息结构
typedef struct tagTShortMessageInfo
{
protected:
    u8          m_byTimes;			//显示次数
    char        m_achMsgBuf[0x400];	//短消息BUFFER，最多1024字符
public:
	tagTShortMessageInfo(){memset(this,0,sizeof(tagTShortMessageInfo));}
	
	inline LPCSTR GetMessage( void ) const
	{
		return( m_achMsgBuf );
	}

	inline void SetMessage( LPCSTR lpszMsg )
	{
		strncpy( m_achMsgBuf, lpszMsg, sizeof( m_achMsgBuf ) );
		m_achMsgBuf[ sizeof( m_achMsgBuf ) - 1] = '\0';
	}

	inline u8 GetTimes( void ) const
	{
		return( m_byTimes );
	}

	inline void SetTimes( u8 byTimes )
	{
		m_byTimes = byTimes;
	}
}PACKED ITSatShortMsg;

//定义短消息结构
typedef struct tagTMultiPackHeader
{
protected:
    u8          m_byTotalNum;		//包的总个数
    u8        m_byCurrNum;	//当前包的序号
    u8        m_byContentNum;   //当前包内容个数
public:
	inline u8 GetTotalNum( void ) const
	{
		return m_byTotalNum;
	}

	inline void SetTotalNum( u8 byNum )
	{
		m_byTotalNum = byNum;
	}

	inline u8 GetCurrNum( void ) const
	{
		return m_byCurrNum;
	}

	inline void SetCurrNum( u8 byNum )
	{
		m_byCurrNum = byNum;
	}
	
	inline u8 GetContentNum( void ) const
	{
		return m_byContentNum;
	}

	inline void SetContentNum( u8 byNum )
	{
		m_byContentNum = byNum;
	}
}PACKED ITSatMultiPackHeader;

#ifdef WIN32
#pragma pack( pop )
#endif

#endif//!_SAT_MT_STRUCT_H_