///  All right reserved
///  
///  @file        kdvsipcommon.h
///  @author      zgf
///  @version     1.0
///  @date        2018-3-1
///  @brief       kdvsipcommom
///  @details     sipcommon interfaces describe here what it is all about.
//////////////////////////////////////////////////////////////////////////

/************************************************************************/
/*  Start of kdvsipcommon                                       */
/************************************************************************/

/**
 * @defgroup    sipcommon
 * @brief       sipcommon interfaces describe here what it is all about.
 * @{
 */
#ifndef _SIPCOMMON_H
#define _SIPCOMMON_H

#include "kdvcommon.h"

#define MAX_MT_NUM_IN_CONF   			(u16)192				///< 每个会议中的最大呼叫数
#define MAX_USER_NAME_LEN               (u16)64            ///< max usernamen length
#define MAX_PASSWORD_LEN                (u16)16            ///< max password length
#define MAX_SIP_PARAM_NUM               (u16)10           ///< max sip parament number
#define MAX_DOMAIN_NAME_LEN    			(u16)64			    	///< 域名长度
#define SIP_CHAN_SPAN					10                      ///< SIP CHAN SPAN
#define SESSION_NAME_LEN				64                      ///< SESSION NAME LEN
#define SESSION_ID_LEN					64                      ///< SESSION ID LEN
#define SESSION_USERNAME_LEN			64                      ///< SESSION_USERNAME_LEN
#define SESSION_VERSION_LEN				64                      ///< SESSION_VERSION_LEN
#define SESSION_INFO_LEN				128                     ///< SESSION_INFO_LEN
#define MAX_LEN_SESSION_DESCRIPTION		1024*10                 ///< MAX_LEN_SESSION_DESCRIPTION
#define MAX_LEN_LANGUAGE_HEADER			32                      ///< MAX_LEN_LANGUAGE_HEADER
#define MAX_LEN_ENCODE_TYPE_HEADER		32                      ///< MAX_LEN_ENCODE_TYPE_HEADER
#define MAX_LEN_HEADER_NAME				64                      ///< MAX_LEN_HEADER_NAME
#define MAX_NUM_TRANC_PERCALL			64                      ///< MAX_NUM_TRANC_PERCALL
#define MAX_NUM_CALLID					128                     ///< MAX_NUM_CALLID
#define MAX_NUM_CONTACT_ADDR			5                       ///< MAX_NUM_CONTACT_ADDR
#define MAX_NUM_REGCLIENT				128                     ///< MAX_NUM_REGCLIENT
#define MAX_NUM_REGNAME_SIZE			64                      ///< MAX_NUM_REGNAME_SIZE
#define MAX_NUM_CHAN					20                      ///< MAX_NUM_CHAN
#define MAX_XML_LEN						65536                   ///< DEFAULT_BUFF_LEN
#define DEFAULT_BUFF_LEN				1024                    ///< DEFAULT_BUFF_LEN
#define MAX_AAC_CAP_NUM					2                       ///< MAX_AAC_CAP_NUM
#define MAX_SIP_REG_INFO_NUM			2                       ///< MAX_SIP_REG_INFO_NUM
#define MAX_FLOOR_NUM					5                       ///< MAX_FLOOR_NUM
#define MAX_MEDIA_NUM_PER_FLOOR			5                       ///< MAX_MEDIA_NUM_PER_FLOOR
#define MAX_TERMINAL_NUM				32                      ///< MAX_TERMINAL_NUM
#define MAX_SIP_REG_INFO_NUM_UMS		3                       ///< MAX_SIP_REG_INFO_NUM_UMS
#define MAX_SIP_REG_INFO_NUM_CNS		20                      ///< MAX_SIP_REG_INFO_NUM_CNS
#define SIP_CALL_ID_SIZE				128                     ///< SIP_CALL_ID_SIZE
#define MAX_NUM_REGNAME_SIZE_CNS		2                       ///< MAX_NUM_REGNAME_SIZE_CNS
#define MAX_SIP_CONF_ID_LEN				16                      ///< MAX_SIP_CONF_ID_LEN
#define MAX_SIP_CONF_NAME_LEN			96                      ///< MAX_SIP_CONF_NAME_LEN
#define MAX_SIP_CONF_E164_LEN			16                      ///< MAX_SIP_CONF_E164_LEN
#define MAX_SIP_PASSWORD_LEN			32                      ///< MAX_SIP_PASSWORD_LEN
#define MAX_SIP_TERMINAL_NUM			32                      ///< MAX_SIP_TERMINAL_NUM
#define MAX_SIP_CONF_AUDMIX_NUM_TP		4			            ///< 最大混音参与数量
#define SIP_INVALID_INDEX_TP			0xFFFF                  ///< SIP_INVALID_INDEX_TP

#define SIP_ADPT_INVALID_ARRAY_INDEX	-1                      ///< SIP_ADPT_INVALID_ARRAY_INDEX

#define MAX_SIP_ENCRYPT_KEY_LEN			(u8)128                 ///< MAX_SIP_ENCRYPT_KEY_LEN
#define MAX_SDP_ATTR_NAME_LEN           50                      ///< MAX_SDP_ATTR_NAME_LEN
#define MAX_SDP_ATTR_VALUE_LEN          300                     ///< MAX_SDP_ATTR_VALUE_LEN
#define MAX_SIP_NONSTD_HEADER_NUM       10                      ///< MAX_SIP_NONSTD_HEADER_NUM
#define MAX_SIP_ATTR_NUM                10                      ///< MAX_SIP_ATTR_NUM
#define MAX_HOST_LEN                    300                     ///< MAX_HOST_LEN

#define DEFAULT_TLS_CA_NAME             "tls-cacert.pem"        ///< DEFAULT_TLS_CA_NAME
#define DEFAULT_TLS_CERT_NAME           "tls-cert.pem"          ///< DEFAULT_TLS_CERT_NAME
#define DEFAULT_TLS_KEY_NAME            "tls-key.pem"           ///< DEFAULT_TLS_KEY_NAME

#define KDV_PORTRANGE_DEFAULT_START		15000                   ///< KDV_PORTRANGE_DEFAULT_START
#define KDV_PORTRANGE_DEFAULT_FINISH	65535                   ///< KDV_PORTRANGE_DEFAULT_FINISH

#define MAX_ADDR_STR_LEN  15                                    ///< MAX ADDR STR LEN

#define SIP_NONSTD_PRE_HEAD             "KdNstd-"               ///< SIP_NONSTD_PRE_HEAD

#define MAX_SIP_ATTR_NAME_LEN 50       ///< max sip attribute name length
#define MAX_SIP_ATTR_VALUE_LEN 300     ///< max sip attribute value length

///< log filter
enum EmLogFilter
{
	emLogNull	= 0,								///< log null
	emLogTelnet	= 0x01,								///< log telnet 
	emLogStdout	= 0x02,								///< log std out
	emLogAll		= emLogTelnet | emLogStdout,	///< log all
};

/// host address
typedef struct tagHostAddress
{
	s8 m_achHost[MAX_HOST_LEN];	///< 主机名
	u16 m_wPort;	            ///< 端口   
	/**
    * \brief            tagHostAddress  init
    * \return           void.
    */
	void Clear()
	{
		memset(this, 0, sizeof(tagHostAddress));
	}
	/**
    * \brief            tagHostAddress  Constructor
    * \return           void.
    */
	tagHostAddress()
	{
		Clear();
	}
}THostAddress;

/// sip Param/header name and value
typedef struct PROTO_API tagSipParam
{
	s8	m_achName[MAX_SIP_ATTR_NAME_LEN];	    ///< Param/header name.	    
	s8	m_achValue[MAX_SIP_ATTR_VALUE_LEN];	    ///< Param/header value.    

	/**
    * \brief            tagSipParam init
    * \return           void.
    */
	void Clear()
	{
		memset(m_achName,  0, sizeof(m_achName));
		memset(m_achValue, 0, sizeof(m_achValue));
	}
	/**
    * \brief            tagSipParam Constructor
    * \return           void.
    */
	tagSipParam()
	{
		Clear();
	}
} TSipParam;

/// TSipAttr
typedef TSipParam TSipHead;
typedef TSipParam TSdpAttr;

/// sip connection(transport) type
enum EmSipConnection
{
	emSipConnUndefined = 0, ///< connection type
	emSipTcpConnection,      ///< tcp
	emSipUdpConnection,      ///< udp
	emSipSCTPConnection,     ///< sctp
	emSipTLSConnection,      ///< tls

	emSipConnectionLoop,	                                        ///< Loopback (stream, reliable) 
	emSipConnectionLoopDgram,	                                    ///< Loopback (datagram, unreliable) 
	emSipConnectionStartOther,	                                    ///< Start of user defined transport 
	emSipConnectionIpv6 = 128,	                                    ///< Start of IPv6 transports 
	emSipConnectionUdp6 = emSipUdpConnection + emSipConnectionIpv6,	///< UDP over IPv6 
	emSipConnectionTcp6 = emSipTcpConnection + emSipConnectionIpv6,	///< TCP over IPv6 
	emSipConnectionTls6 = emSipTLSConnection + emSipConnectionIpv6,	///< TLS over IPv6 
};

/// 主机名类型
enum EmHostNameType
{
	emUrlIP,                      ///< ip
//	emUrlIpv6,                    ///< ipv6
	emUrlDomain,                  ///< domain
	emUrlAlias,                   ///< alias
	emUrlE164Num,                 ///< E164
    emUrlNone,                    ///< none
};


/// host name
typedef struct PROTO_API tagHostName
{
	EmHostNameType   m_emType;                            ///< 主机名类型
	s8				 m_achDomainName[MAX_DOMAIN_NAME_LEN + 1]; ///< 域名
	PFC_IPADDR       m_tHostAddr;                         ///< ipv4 or ipv6 address

	/**
    * \brief            tagHostName init
    * \return           void.
    */
	void Clear()
	{
		memset(this, 0, sizeof(tagHostName));
		m_tHostAddr.m_wPort = 5060;
	}
	/**
    * \brief            tagHostName Constructor
    * \return           void.
    */
	tagHostName()
	{
		Clear();
	}
}THostName;

/// sip url
typedef struct PROTO_API tagSipUrl
{
	s8			m_achDisplayName[MAX_USER_NAME_LEN + 1];    ///< displayname
	s8			m_achUserName[MAX_USER_NAME_LEN + 1];	   ///< 别名   
	s8			m_achPassword[MAX_PASSWORD_LEN + 1];	   ///< 密码
	s8  		m_achAuthUser[MAX_USER_NAME_LEN+1];		   ///< Username for digest authorization process
    THostName	m_tHostName;						   ///< 主机名
	u32			m_nParamNum;                          ///< parament number
	TSipParam	m_atParam[MAX_SIP_PARAM_NUM];///< parament array

public:
	/**
    * \brief            tagSipUrl Constructor
    * \return           void.
    */
	tagSipUrl()
	{
		memset( this, 0, sizeof(tagSipUrl) );
	}
}TSipUrl;

/// sip uri
typedef struct tagSipUri
{
	s8 m_achDisplayName[MAX_USER_NAME_LEN];	///< displayname ahead of sip uri
	s8 m_achUserName[MAX_USER_NAME_LEN];	///< E164 in sip uri
	s8 m_achPassword[MAX_PASSWORD_LEN];	    ///< password
	THostAddress m_tHostAddr;               ///< host address
	s32 m_nParamNum;                        ///< para number
	TSipParam m_atParam[MAX_SIP_PARAM_NUM]; ///< para array

	/**
    * \brief            tagSipUri init
    * \return           void.
    */
	void Clear()
	{
		memset(m_achDisplayName, 0, sizeof(m_achDisplayName));
		memset(m_achUserName, 0, sizeof(m_achUserName));
		memset(m_achPassword, 0, sizeof(m_achPassword));
		m_tHostAddr.Clear();
		m_nParamNum = 0;
		for (u8 i = 0; i < MAX_SIP_PARAM_NUM; i++)
		{
			m_atParam[i].Clear();
		}
	}
	/**
    * \brief            tagSipUri Constructor
    * \return           void.
    */
	tagSipUri()
	{
		Clear();
	}
} TSipUri;


/// cert config
typedef struct tagCertCfg
{
	s8      m_achCACertFile[MAX_FILE_PATH_LEN]; ///< 载入的CA证书文件，如果启用校验，CACertFile和CACertPath有一个即可。
	s8      m_achCACertPath[MAX_FILE_PATH_LEN]; ///< 载入的CA证书目录，如果启用校验，CACertFile和CACertPath有一个即可。
	s8      m_achCertFile[MAX_FILE_PATH_LEN];   ///< 载入的证书文件，服务端需设置，客户端选择性设置。
	s8      m_achKeyFile[MAX_FILE_PATH_LEN];    ///< private key，服务端需设置，客户端选择性设置。
	s8		m_achPassword[MAX_SIP_PASSWORD_LEN];///< Password to open private key.
}TCertCfg;

/// tls config
typedef struct tagTlsCfg
{
	TCertCfg m_atCertCfg[MAX_CERTICATE_NUM];    ///< cert config array
	u16      m_wLocalTlsPort;		            ///< 本地tls侦听端口,defult：5061
	s8       m_achDevId[MAX_QT_ID_LEN];         ///< devid for qt tls
	u32      m_dwTlsTimeOut;                    ///< tls time out,millisecond.if it is 0 means no timeout mechanism
    /**
    * \brief            tagTlsCfg Constructor
    * \return           void.
    */
	tagTlsCfg()
	{
		Clear();
	}
	/**
    * \brief            tagTlsCfg init
    * \return           void.
    */
	void Clear()
	{
		memset(this , 0 , sizeof(tagTlsCfg) );
		cbCertForVerify        = NULL;
		cbCertLoadFailedStatus = NULL;
		cbCreateQTSession      = NULL;
		cbDestroyQTSession     = NULL;
		cbGetQTKey             = NULL;
		m_wLocalTlsPort        = 5061;
		m_dwTlsTimeOut         = 0;
	}
	
	/**
	* \brief            siapdpater tls verify callback
	* \param[in]        bVerifyServer  :TRUE -> vertify server,FALSE -> vertify client
	* \param[in]        nVerifyStatus  :vertify status
	* \param[in]        Cert           :cert string
	* \param[in]        dwCertLen      :cert string length
	* \return           BOOL32, TRUE/FALSE
	*/
	BOOL32 (PROTO_CALLBACK* cbCertForVerify)(BOOL32 bVerifyServer, s32 nVerifyStatus, const s8 *Cert, u32 dwCertLen);

	/**
	* \brief            Cert Load Failed Status
	* \param[in]        nStatus  :cert load failed status
	* \return           BOOL32, TRUE/FALSE
	*/
	BOOL32 (PROTO_CALLBACK* cbCertLoadFailedStatus)(s32 nStatus);

	/**
	* \brief            call back to notify upper to create a qt session
	* \param[in]        pSession  :The session's handle after be created
	                    args:some args to create session
	* \return           s32, status code
	*/
	s32 (PROTO_CALLBACK* cbCreateQTSession)(void *args, void** pSession);

	/**
	* \brief            call back to notify upper to Destroy a qt session
	* \param[in]        pSession  :The session's handle after be created
	                    args:some args to Destroy session
	* \return           s32, status code
	*/
	s32 (PROTO_CALLBACK* cbDestroyQTSession)(void *args, void* pSession);

	/**
	* \brief            call back to upper to get qt key
	* \param[in]        pSession  :The session's handle after be created
	                    pLocalDevId:local devid
						pPeerDevId:peer devid
						qk:INOUT,qt key
	* \return           s32, qt key len if success
	*/
	s32 (PROTO_CALLBACK* cbGetQTKey)(void* pSession, const s8* pLocalDevId, const s8 *pPeerDevId, u8* pbyQtKey, u32 dwMaxQTKeyLen, BOOL32 isClient);
}TTlsCfg;

/**
* @}
*/
#endif