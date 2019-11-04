/**
*   COPYRIGHT NOTICE
*   Copyright (C) 2018, KeDaCom
*   All right reserved
*   
*   @file        kdv323common.h
*   @author      Sai
*   @version     V5.0_64bit
*   @date        2018-03-05
*   @brief       Common defined for H323 protocol 
*   @details     
*/

#ifndef _H323COMMON_H
#define _H323COMMON_H

#include "kdvcommon.h"

#define INVALID_NODEID      RV_PVT_INVALID_NODEID
#define TYPE_NONE           0         /**<表示为未定义地址*/
#define TYPE_IPV4           1         /**<表示支持IPv4地址*/
#define TYPE_IPV6           2         /**<表示支持IPv6地址*/

/**/////////////////////////////// 长度定义 ///////////////////////////////*/
#define LEN_H245_CONFID		(u16)32					/**<H245会议ID */
#define LEN_CONFNAME		(u16)256				/**<h323-id*/
#define LEN_NETADDR			sizeof(PFC_IPADDR)		/**<网路地址长度*/
//#define LEN_MTNUM_PERCONF	(u16)193				/**<每个会议中的最大呼叫数*/
#define LEN_OID				(u16)16					/**<OID长度*/
#define LEN_CALLADDR		sizeof(TAliasAddr)		/**<呼叫地址长度*/
#define LEN_CHANPARAM		sizeof(TCHANPARAM)		/**<信道参数长度*/
#define LEN_TERINFO			sizeof(TTERINFO)		/**<终端信息长度*/
#define LEN_CAP				sizeof(TKdv323CapSet)	/**<能力参数长度*/
#define LEN_H243PWD			(u16)32                 /**<密码长度*/
#define LEN_DISPLAY_MAX		(u16)82                 /**<显示信息的最大长度*/
#define LEN_DISPLAY_MIN		(u16)2                  /**<显示信息的最小长度*/

#define LEN_USERINFO_MAX    (u8)131					/**<UserInfor的最大长度*/
#define LEN_USERINFO_MIN	(u16)2                  /**<UserInfor的最小长度*/
#define TLCALLPORT			(u16)1760				/**<呼叫端口*/
#define CALLPORT			(u16)1720				/**<呼叫端口*/
#define RASPORT				(u16)1719				/**<RAS端口 */
#define MAXALIASNUM			(u16)128				/**<最大别名数*/
#define MAXSessionDescript	(u8)128                 /**<支持的最大SessionDescript*/
#define MAX_LEN_CONFNAME    (u16)64					/**<会议名字最大长度*/
#define PRODUCTSTRING_LESS_SIZE        (u16)32      /**<产品信息的长度,用于获取对方的产品信息*/
#define VERSIONSTRING_LESS_SIZE        (u16)32      /**<版本信息的长度,用于获取对方的版本信息*/
#define LEN_NONSTANDARD_MAX (u16)2048               /**<setup消息中非标数据的最大长度*/
#define MAX_CALL_NUM        (u16)1024
#define MIN_CALL_NUM        (u16)10
#define MAX_CHANNEL_NUM     (u16)20
#define MIN_CHANNEL_NUM     (u16)12
#define RequestMsg_BGN		(u16)101
#define RequestMsg_END		(u16)300
#define ResponseMsg_BGN		(u16)301
#define ResponseMsg_END		(u16)500
#define CommandMsg_BGN		(u16)501
#define CommandMsg_END		(u16)700
#define IndicationMsg_BGN	(u16)701
#define IndicationMsg_END	(u16)900
#define LEN_256				(u16)256
#define LEN_128				(u16)128
#define REG_NAME_LEN		(u16)64
#define REG_PWD_LEN			(u16)64
#define VALID_LEN_ALIAS      (u16)16   /**<有效别名它度*/  
#define RAS_RESPONSE_TIMEOUT (u32)20  

#define FLAG_H460FEATURESIGNALL			18			/**<460.18*/
#define FLAG_H460MEDIAFWSIGNALL			19			/**<460.19*/   

#define FLAG_H460SUPPORTMULTIPLEXDMEDIA	1			/**<支持端口复用*/
#define FLAG_H460MEDIATRAVESALSERVER	2			/**<本端为460服务器*/

/**非标消息错误号定义*/
enum
{	
	KDVP_NSM_SUCCESS		 						= 0,  
	KDVP_NSM_SER_DB_ERR  						    = 1,
	KDVP_NSM_TIMEOUT_ERR 						    = 2,		/**<平台内部超时*/
	KDVP_NSM_NOTE164_ERR 							= 3,				 
	KDVP_NSM_DATA_ERR 								= 4,        
	KDVP_NSM_MCU_NOIDLEVPU							= 5,        /**<没有足够能力的空闲媒体处理器*/
	KDVP_NSM_MCU_MINIMEDIACONFMTNUM					= 6,        /**<超过小型媒体会议入会终端限制*/
	KDVP_NSM_MCU_MAXCONFNUM							= 7,        /**<已达最大会议数*/
	KDVP_NSM_MCU_ENCRYPEERR							= 8,        /**<与会议加密模式不符*/
	KDVP_NSM_MCU_CONFNOTEXIST						= 9,        /**<会议不存在*/
	KDVP_NSM_MCU_MAXMTNUM							= 10,       /**<达到最大参会人员数*/
	KDVP_NSM_GK_MPCD_DISCONNECTED				    = 11,       /**<MPCD与GK断链    nu处理*/
	KDVP_NSM_MCU_CONFRESUMING						= 12,       /**<MCU真正恢复中*/
	KDVP_NSM_MCU_PASSERR							= 13,       /**<会议密码错误*/
	KDVP_NSM_MCU_NSATPMS							= 14,       /**<无卫星权限*/
	KDVP_NSM_MCU_NSATDADDR							= 15,       /**<没有组播地址*/
	KDVP_NSM_MCU_CONFE164REPEAT					    = 16,       /**<会议E164号重复*/
	KDVP_NSM_MCU_UNDEFINED							= 17,       
	KDVP_NSM_MCU_PEER_NODISTURB 			        = 18,       /**<会议免打扰拒绝*/
	KDVP_NSM_MCU_NOPERMISSION                       = 19,       /**<没有创会权限*/
};

/////////////////////////
#ifndef H323CASCADE_H_

#define CASCADE_USERNAME_MAXLEN     (s32)32
#define CASCADE_USERPASS_MAXLEN     (s32)32 

typedef struct tagRequest
{
    s32  m_nReqID;/**<流水号/系列号*/
	s8   m_aszUserName[CASCADE_USERNAME_MAXLEN];/**<帐号*/
	s8   m_aszUserPass[CASCADE_USERPASS_MAXLEN];/**<密码*/
	/**设置帐号和密码*/
	inline void SetUserNameAndPass(const s8 * aszUserName, const s8 *aszUserPass)
	{
		strncpy(m_aszUserName, aszUserName, sizeof(m_aszUserName) - 1);
		m_aszUserName[CASCADE_USERNAME_MAXLEN-1] = '\0';
		strncpy(m_aszUserPass, aszUserPass, sizeof(m_aszUserPass) - 1);
		m_aszUserPass[CASCADE_USERPASS_MAXLEN-1] = '\0';
	}

	tagRequest()
	{
		memset(this, 0, sizeof(*this));
	};
}TReq;


/**<请求进行会议级联的注册注销请求*/
typedef struct tagRegUnReg: public TReq     /**<向对端mcu注册注销的请求消息*/
{
    BOOL32 m_bReg;               /**<true:注册;false 注销*/
}TRegUnRegReq;

#endif
/////////////////////////

#define		MAXLEN_E164                     16			/**<最大E164号码长度*/
#define		MAX_STACK_BUFFER_SIZE           (u32)5120	/**<协议栈的最大发送缓冲*/




#define KDV_NSM_MAX_LEN        (s32)(1024*10)  
/**别名类型*/
enum AliasType
{
	type_aliastype,
	type_e164 = 0x1,
	type_h323ID,
	type_email,
	type_epID,
	type_GKID,
	type_partyNumber,
	type_others
};

/**IP地址类型*/
enum TransportAddrType 
{
	addr_uca,		/**<unicast*/
	addr_mca,		/**<multicast*/
	addr_err = 0xff
};

/**函数执行结果*/
enum ActResult 
{
    act_err = -1,
	act_ok
};


/**别名地址*/
#pragma pack(4)		/**<[20141022]王金鑫需求-给此结构体以四字节做内存对齐*/
typedef struct PROTO_API tagALIASADDR
{
	AliasType  m_emType;
	s8		   m_achAlias[LEN_ALIAS+2];			/**<h323-Id 别名后两位为空*/
	
	tagALIASADDR()
	{
		Clear();
	}
	
	void Clear()
	{
		m_emType = type_aliastype;
		memset( m_achAlias, 0, sizeof(m_achAlias) );
	}
	
	/**设置别名*/
	BOOL32 SetAliasAddr( AliasType aliasType, const char* pAlias )
	{
		if ( aliasType <= type_aliastype || aliasType >= type_others ||
			pAlias == NULL ) 
			return FALSE;
		
		memset( m_achAlias, 0, sizeof(m_achAlias) );
		
		m_emType = aliasType;
		
		s32 nLen = Minimum( (s32)strlen(pAlias), (s32)LEN_ALIAS );
		strncpy( m_achAlias, pAlias, nLen );
		m_achAlias[nLen] = '\0';
		
		return TRUE;
	}	
	/**获得type*/
	AliasType GetAliasType()
	{
		return m_emType;
	}
	
	void SetAliasType(AliasType emType)
	{
		m_emType = emType;
	}
	/**获得别名*/
	s8* GetAliasName()  
	{
		return m_achAlias;	
	}
}TALIASADDR,*PTALIASADDR;
#pragma pack()


/**transport地址*/
#pragma pack(4)		/**<[20141022]王金鑫需求-给此结构体以四字节做内存对齐*/
typedef struct PROTO_API tagTransportAddress
{
    //add by yj for ipv6
	u8          m_byIPType;                                 /**<支持的 IP地址类型*/
	u8          m_dwIP_ipv6[PFC_IPV6_STR_LEN];			        /**<协议栈运行IP(ipv6)，非网络序;*/
    //end
	u32 m_dwIP;
	u16 m_wPort;
	u8	m_byType;
	
	tagTransportAddress()
	{
		Clear();
	}
	
	void Clear()
	{
		m_dwIP	 = 0;
		m_wPort  = 0;
		m_byType = addr_uca;
		//add by yj for ipv6
		m_byIPType = TYPE_NONE;   
		memset(m_dwIP_ipv6, 0, sizeof(m_dwIP_ipv6));
        //end
	}
	
    void host2net(BOOL32 bhton)
    {
        if (bhton)
        {
            m_dwIP  = htonl(m_dwIP);
            m_wPort = htons(m_wPort);
        }
        else
        {
            m_dwIP  = ntohl(m_dwIP);
            m_wPort = ntohs(m_wPort);
        }
    }
	
	/**设置transport地址*/
	void SetNetAddress(u32 dwIPAddr, u16 wIPPort, u8 byAddrType=addr_uca)
	{
		m_dwIP   = dwIPAddr;
		m_wPort  = wIPPort;
		m_byType = byAddrType;
		m_byIPType = TYPE_IPV4;
	}
	//add by yj for ipv6
	/**设置ip地址类型*/
	void SetIPAddr_Type(u8 byIPType)
	{
		m_byIPType = byIPType;
	}
	u8 GetIPAddr_Type( )
	{
		return	m_byIPType;
	}
	void SetNetAddress_Ipv6(u8* dwIPAddr_ipv6, u16 wIPPort, u8 byAddrType=addr_uca)
	{
		memcpy(m_dwIP_ipv6, dwIPAddr_ipv6, sizeof(m_dwIP_ipv6));
		m_wPort  = wIPPort;
		m_byType = byAddrType;
		m_byIPType = TYPE_IPV6;
		
	}
	
	u8 *GetIPAddr_Ipv6()
	{
		return m_dwIP_ipv6;
	}
	
	/**获取IP地址*/
	u32 GetIPAddr()
	{
		return m_dwIP;
	}
	/**获取端口*/
	u16 GetIPPort()
	{
		return m_wPort;
	}
	/**获取类型*/
	u8 GetNetAddrType()
	{
		return m_byType;
	}

	void SetIPAddr(u32 dwIP)
    {
        m_dwIP = dwIP;
		m_byIPType = TYPE_IPV4;
    }

	void SetIPPort(u16 wPort)
	{
		m_wPort = wPort;
	}

}TNETADDR,*PTNETADDR;
#pragma pack()

/**呼叫时的别名地址*/
typedef struct PROTO_API tagAliasAddr
{
	CallAddrType    m_emType;		/**<呼叫类型*/
	PFC_IPADDR		m_tNetAddr;		/**<IP呼叫时使用*/		
	TALIASADDR		m_tAlias;		/**<别名呼叫使用*/

	tagAliasAddr()
	{
		m_emType = emcat_err;
	}

	void Clear()
	{
		m_emType = emcat_err;
		m_tNetAddr.Clear();
		m_tAlias.Clear();
	}

	/**设置为IP地址呼叫*/
	void SetIPCallAddr( PFC_IPADDR *ptIPAddr )
	{
		if ( NULL != ptIPAddr )
		{
			m_emType = emcat_ip;
			memcpy( &m_tNetAddr, ptIPAddr, sizeof(PFC_IPADDR) );
		}		
	}

	//add by yj for ipv6
	/**获取ip地址类型*/
	u8 GetIPAddr_Type( )
	{
		if (m_emType == emcat_ip) 
		{
			return	m_tNetAddr.m_emType;
		}
		return TYPE_NONE;
	}
	/**获取呼叫的IP(ipv6)地址*/
	u8* GetIPAddr_Ipv6()
	{
		if (m_emType == emcat_ip) 
		{
			if (m_tNetAddr.m_emType == PFC_TRANSPORT_TYPE_IPV6)
			{
				return m_tNetAddr.m_tAddr.m_tIPv6.m_abyIP;
			}
		}
		return 0;
	}
//	s16 GetIPAddr_Ipv6_ScopeId()
//	{
//		if (m_emType == emcat_ip) 
//		{
//			if (m_tNetAddr.m_byIPType == TYPE_IPV6)
//			{
//				return m_tNetAddr.GetIPAddr_Ipv6_ScopeId();
//			}
//		}
//		return -1;
//	}

	//end

	/**获取呼叫的IP地址*/
	u32 GetIPAddr()
	{
		if (m_emType == emcat_ip) 
		{
			//add by yj
			if (m_tNetAddr.m_emType == PFC_TRANSPORT_TYPE_IP)
			{
				return m_tNetAddr.m_tAddr.m_tIPv4.m_dwIP;
			}
		    //end
		}
		return 0;
	}

	/**获取呼叫的端口*/
	u16 GetIPPort()
	{
		if (m_emType == emcat_ip) 
		{
			return m_tNetAddr.m_wPort;
		}
		return 0;
	}
	/**设置为别名地址呼叫*/
	void SetIPCallAddr( TALIASADDR *pAliasAddr )
	{
		if ( pAliasAddr != NULL )
		{
			m_emType = emcat_alias;
			memcpy( &m_tAlias, pAliasAddr, sizeof(m_tAlias) );
		}		
	}
	/**获取别名类型*/
	AliasType GetAliasType()
	{
		if (m_emType == emcat_alias)
		{
			return m_tAlias.GetAliasType();
		}
		return type_aliastype;
	}
	/**获取别名*/
	s8* GetAliasName()
	{
		if (m_emType == emcat_alias)
		{
			return m_tAlias.GetAliasName();
		}
		return NULL;
	}
	/**获取呼叫类型*/
	CallAddrType GetCallAddrType()
	{
		return m_emType;
	}
}TAliasAddr,*PTAliasAddr;

/**begin with added by wangxiaoyi for facility with non-strandard conflist message on 5 August 2010*/
typedef struct tagFacilityConfList_NSM
{
protected:
	u8   m_abyConfId[LEN_GUID+1];	/**<会议ID*/
	u16  m_wListIdx;				/**< 在TCONFERENCES结构中的存放位置索引，网络序*/

	/**新增非标内容*/
	s8	 m_sConfE164[LEN_ALIAS+1];	/**< 会议E164号码*/
	u8	 m_byMtNum;					/**< 入会终端数*/
	u16  m_wRemainTime;				/**< 会议剩余时间, 单位是分钟*/
	u32  m_dwReserved1;
	u32  m_dwIsContinue;

	BOOL32         m_bConfListNonStandard;/**< whether contains non-standard information or not when facilityreason is conferenceListChoice*/

	////////
public:
	tagFacilityConfList_NSM()
	{
		Clear();
	}
	
	void Clear()
	{
		memset(m_abyConfId,0,sizeof(m_abyConfId));
		SetListIdx(0);
		SetConfE164( NULL, 0 );
		SetMtNum( 0 );
		SetRemainTime( 0 );
		SetConfListNonStandard( FALSE );
	}
	/**设置会议ID*/
	void SetConfId( u8 *pbyConfId, u32 dwLen )
	{
		if ( pbyConfId == NULL )
			return;
		
		u32 realLen = Minimum(dwLen, (u32)LEN_GUID);
		memcpy( m_abyConfId, pbyConfId, realLen );
		m_abyConfId[realLen] = '\0';
	}
	/**获取会议ID*/
	u8* GetConfId()
	{
		return m_abyConfId;
	}
	/**设置存放位置索引*/
	void SetListIdx( u16 wListIdx )
	{
		m_wListIdx = htons(wListIdx);
	}
	/**获取存放位置索引*/
	u16 GetListIdx()
	{
		return ntohs(m_wListIdx);
	}
	/**设置会议E164号码*/
	void SetConfE164( s8 * psConfE164, u8 byLen )
	{
		memset( m_sConfE164, 0, sizeof(m_sConfE164) );
		if ( NULL == psConfE164 || 0 == byLen )
		{
			return;
		}
		u8 byRealLen = Minimum( byLen, (u8)LEN_ALIAS );
		memcpy( m_sConfE164, psConfE164, byRealLen );
		return;
	}
	/**获取会议E164号码*/
	s8 * GetConfE164( void )
	{
		return m_sConfE164;
	}
	/**设置入会终端数*/
	void SetMtNum( u8 byMtNum )
	{
		m_byMtNum = byMtNum;
	}
	/**获取入会终端数*/
	u8   GetMtNum( void )
	{
		return m_byMtNum;
	}
	/**设置会议剩余时间*/
	void SetRemainTime( u16 wRemainTime )
	{
		m_wRemainTime = htons(wRemainTime);
	}
	/**获取会议剩余时间*/
	u16  GetRemainTime( void )
	{
		return ntohs(m_wRemainTime);
	}
	BOOL32 IsIdleConf(void)
	{
		return ( GetMtNum() == 0 ) ? TRUE : FALSE;
	}

    void SetContinueFlag( BOOL32 bIsContinue )
    {
        m_dwIsContinue = bIsContinue ? htonl(1) : htonl(0);
    }
    BOOL32 IsContinue( void )
    {
        return ( ntohl(m_dwIsContinue) == 1 ) ? TRUE : FALSE;
    }
	void SetConfListNonStandard( BOOL32 bConfListNonStandard )
	{
		m_bConfListNonStandard = htonl(bConfListNonStandard);
	}
	BOOL32 IsConfListNonStandard()
	{
		return ntohl(m_bConfListNonStandard);
	}
	void SetReserved1( u32 dwReserved )
	{
		m_dwReserved1 = htonl( dwReserved );
	}
	u32 GetReserved1( void )
	{
		return ntohl( m_dwReserved1 );
	} 
}
TFacilityConfList_NSM,*PTFaclilityConfList_NSM;
/**end with added by wangxiaoyi for facility with non-strandard conflist message on 5 August 2010*/





#ifdef WIN32
#pragma pack(1)
#define PACKED 
#endif // WIN32


/**终端地址信息*/

/**地址类型*/
#define		ADDR_TYPE_IP		1
#define		ADDR_TYPE_ALIAS		2
// // 
/**别名类型*/
#define		ALIAS_H323ID		1
#define		ALIAS_E164			2
#define		ALIAS_EMAIL			3

typedef struct tagTerAddr
{
public :
	u8 GetAddrType( void ) { return byAddrType; }
	void SetAddrType( u8 byType ) { byAddrType = byType; }
	
	void SetIpAddr( u32 ip, u16 port )
	{
		dwIp = ip;
		wPort = htons( port );
	}
	u32 GetIpAddr( void ) { return dwIp; }
	u16 GetIpPort( void ) { return ntohs( wPort ); }

	//add by yj for ipv6
	void SetIpAddr_Ipv6( u8* ipv6, u16 port, s16 scopeID)
	{
		memcpy(dwIp_ipv6, ipv6, sizeof(dwIp_ipv6));
		wPort = htons( port );
        swScopeId = scopeID;
	}
	u8* GetIpAddr_Ipv6( void ) { return dwIp_ipv6; }
	s16 GetScopeId( void ) { return swScopeId; }
	//end

	u8 GetAliasType( void ) { return byAliasType; }
	s8* GetAliasName( void ) { return achAlias; }
	BOOL32 SetAlias( u8 byType, const s8* pchName, u8 byNameLen ) 
	{ 
		if ( pchName == NULL || byNameLen == 0 )
			return FALSE;
		
		byAliasType = byType; 
		memset( achAlias, 0, sizeof( achAlias ) );
		u8 byLen = Minimum( byNameLen, (u8)VALID_LEN_ALIAS );
		memcpy( achAlias, pchName, byLen );
		achAlias[byLen] = '\0';
		return TRUE;
	}
	
	tagTerAddr() 
	{
		memset( this, 0, sizeof( tagTerAddr ) );
	}
	
	void Reset( void )
	{
		memset( this, 0, sizeof( tagTerAddr ) );
	}
	
private :
	u8	byAddrType;		/**<地址类型*/
	u32 dwIp;			/**<IP(网络序)*/
	u16	wPort;			/**<端口号*/
	u8	byAliasType;	/**<别名类型*/
	s8 achAlias[ VALID_LEN_ALIAS + 1 ];

	//add by yj for ipv6
    u8	byAddrIpType;		/**<P地址类型*/
    u8 dwIp_ipv6[PFC_IPV6_STR_LEN];			/**<IPv6地址(非网络序)*/
	s16 swScopeId;
	//end
}





#if defined(_VXWORKS_) || (defined(_LINUX_) && !defined(_EQUATOR_))
__attribute__ ((packed)) 
#endif
TTERADDRESS,*PTTERADDRESS;

#ifdef WIN32
#pragma pack()
#endif

#endif
