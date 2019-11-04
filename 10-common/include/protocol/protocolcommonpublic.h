//////////////////////////////////////////////////////////////////////////
///  COPYRIGHT NOTICE
///  Copyright (C) 2014, KDC
///  All right reserved
///  
///  @file        protocolcommonpublic.h
///  @author      Jacky
///  @version     1.0
///  @date        2014
///  @brief       the common public data of protocol 
//////////////////////////////////////////////////////////////////////////

#ifndef _PROTOCOL_COMMON_PUBLIC_H_
#define _PROTOCOL_COMMON_PUBLIC_H_

#include <string.h>
#include <kdvtype.h>

typedef void* MemId;  ///< private type definition for protocol components (for 64-bit support)

#define MAX_MULTI_ADDR_NUM      (s8)2

/// the macro of IN,OUT,INOUT
#ifndef IN
	#define IN
#endif//!IN
#ifndef OUT
	#define OUT
#endif//!OUT
#ifndef INOUT
	#define INOUT
#endif

#if (defined(WIN32) || defined(_WIN32) ) && !defined(_PROTO_STATICLIB_)
	/// for Microsoft c++
	#define PROTO_EXTERN_API	extern "C"	__declspec(dllexport)
	#ifndef _PROTO_LIB_
		#define PROTO_API		__declspec(dllexport)
	#else
		#define PROTO_API		__declspec(dllimport)
	#endif
	#define PROTO_CALLBACK		__cdecl
#else
	/// for gcc
	#define PROTO_EXTERN_API	extern "C"
	#define PROTO_API
	#define PROTO_CALLBACK
#endif  // _MSC_VER


/// common macro definitions
#ifndef MEMCPY_CAST
    #define MEMCPY_CAST(dst, src, len) memcpy(static_cast<void*>(dst), static_cast<const void*>(src), len)
#endif

#ifndef MEMMOVE_CAST
	#define MEMMOVE_CAST(dst, src, len) memmove(static_cast<void*>(dst), static_cast<const void*>(src), len)
#endif

#ifndef MEMSET_CAST
   #define MEMSET_CAST(dst, val, len)  memset(static_cast<void*>(dst), val, len)
#endif

#ifndef MEMCMP_CAST
	#define MEMCMP_CAST(val1, val2, len) memcmp(static_cast<const void*>(val1), static_cast<const void*>(val2), len)
#endif

#ifndef STRCMP_CAST
    #define STRCMP_CAST(val1, val2)  strcmp(static_cast<const char*>(val1), static_cast<const char*>(val2))
#endif

#ifndef SAFE_DELETE
	#define SAFE_DELETE(p)		{ if(p) { delete (p); (p)=NULL; } }
#endif
#ifndef SAFE_DELETE_ARRAY
	#define SAFE_DELETE_ARRAY(p){ if(p) { delete[] (p); (p)=NULL; } }
#endif

/// ºÁÃë¼¶µÄsleep
#if defined(WIN32) || defined(_WIN32)
#define SLEEPMS(x) Sleep(x)
#elif defined(_UNIX_) || defined(_LINUX_)
#include <unistd.h>
#define SLEEPMS(x) usleep(((x)*1000))
#else
#define SLEEPMS(x)
#endif


/// be used to print IPv4
#define IPFORMAT      "%d.%d.%d.%d"
#define u32ToIP(ip)   (u8)(ntohl(ip)>>24), (u8)(ntohl(ip)>>16), (u8)(ntohl(ip)>>8), (u8)ntohl(ip)


/// common inline C++ functions
template <class T>
inline const T& Maximum(const T& a, const T&b)
{
    return a < b ? b : a;
}

template <class T>
//lint -e{1413}
inline const T Minimum(const T a, const T b)
{
    return a > b ? b : a;
}

template < class T >
T SAFE_COPY( T &t, u8 *pbyP )
{
	if (NULL == pbyP) return t;
	memcpy( &t, pbyP, sizeof( T ) );
	return t;
}

/*lint -e843 */
/*lint -e438 */


/// Add callback function for print
typedef void (*ALL_LOG_CALlBACK)(const s8* pchbuf, u32 dwLen);

/// transport type
typedef enum
{
	PFC_TRANSPORT_TYPE_NONE,                ///< invalid
    PFC_TRANSPORT_TYPE_IP,                  ///< No route
    PFC_TRANSPORT_TYPE_IP_STRICT_ROUTE,     ///< strict route
    PFC_TRANSPORT_TYPE_IP_LOOSE_ROUTE,      ///< loose route
    PFC_TRANSPORT_TYPE_NASP,                ///< NSAP
    PFC_TRANSPORT_TYPE_IPV6,                ///< IPv6
} PFC_TRANSPORT_TYPE;

/// distribution type
typedef enum
{
    PFC_DISTRIBUTION_UNICAST,               ///< Unicast
    PFC_DISTRIBUTION_MULTICAST,             ///< Multicast
	PFC_DISTRIBUTION_ERROR = 0xFF           ///< ERROR
} PFC_DISTRIBUTION_TYPE;

#define PFC_ROUTE_SIZE      (7)   ///< for luck
#define PFC_IPV6_ADDR_SIZE  16    ///< Size of IPV6 address
#define PFC_IPV6_STR_LEN    46    ///< string length of IPV6 address,(46 = 6*4 + 6 + 15 + 1),46 here is to support ipv4-mapped-on-ipv6
#define MAX_STATIC_NAT_NUM  10    ///< static NAT num

/// PFC IPv4 address
typedef struct
{
    u32        m_dwIP;                      ///< IPv4 address
    u16        m_wLength;                   ///< length in bytes of route
    u32        m_adwRoute[PFC_ROUTE_SIZE];  ///< route
} PFC_IPADDRv4;

/// PFC IPv6 address
typedef struct
{
    u8         m_abyIP[PFC_IPV6_ADDR_SIZE];     ///< 16 byte IP address, network format 
    u16        m_wScopeId;                      ///< scope
} PFC_IPADDRv6;

/// IP address union
typedef union
{
    PFC_IPADDRv4 m_tIPv4;                   ///< IPv4 address
    PFC_IPADDRv6 m_tIPv6;                   ///< IPv6 address
}PFC_IPADDR_UNION;

/// PFC IP address
#pragma pack(4)	
typedef struct PROTO_API tagPFC_IPADDR
{
    PFC_TRANSPORT_TYPE     m_emType;          ///< transport type
    PFC_IPADDR_UNION       m_tAddr;           ///< IP address
    u16                    m_wPort;           ///< 2 byte port number, host format
    PFC_DISTRIBUTION_TYPE  m_emDistribution;  ///< Distribution type of this address

	void Clear()
	{
		MEMSET_CAST(this, 0, sizeof(tagPFC_IPADDR) );
		m_emType = PFC_TRANSPORT_TYPE_IP;
	}

	tagPFC_IPADDR()
	{
		Clear();
	}
	/**
    * \brief            set ipv4 address
    * \param[in]        dwIp  :ipv4 value
	* \param[in]        wPort :ipv4 port
    * \return           void.
    */
	void SetIpAddr( u32 dwIp , u16 wPort ) 
	{
		if ( dwIp == 0 && wPort == 0)
		{
			return;
		}
		m_emType = PFC_TRANSPORT_TYPE_IP;
		m_tAddr.m_tIPv4.m_dwIP = dwIp;
		m_wPort = wPort;
	}

	/**
    * \brief            get ipv4 address
    * \param[out]       pdwIp  :ipv4 value return
	* \param[out]       pwPort :ipv4 port  return
    * \return           void.
    */
	void GetIpAddr( u32* pdwIp , u16* pwPort ) const
	{
		if ( NULL == pdwIp && NULL == pwPort )
		{
			return;
		}
		if ( PFC_TRANSPORT_TYPE_IP == m_emType )
		{
			*pdwIp	= m_tAddr.m_tIPv4.m_dwIP;
			*pwPort = m_wPort;
		}
		else
			return;
	}

	/**
    * \brief            set ipv6 address
    * \param[in]        abyIpv6 :ipv6 value
	* \param[in]        wPort   :ipv6 port
    * \return           void.
    */
	void SetIpv6Addr( u8 abyIpv6[] , u16 wPort=0 )
	{
		m_emType = PFC_TRANSPORT_TYPE_IPV6;
		memcpy( m_tAddr.m_tIPv6.m_abyIP , abyIpv6 , PFC_IPV6_ADDR_SIZE );
		m_wPort = wPort;
	}
	
	/**
    * \brief            get ipv6 address
    * \param[out]       pbyIpv6 :ipv6 value return
	* \param[out]       pwPort  :ipv6 port  return
    * \return           void.
    */
	void GetIpv6Addr( u8* pbyIpv6 , u16* pwPort ) const
	{
		if (NULL == pbyIpv6 && NULL == pwPort)
		{
			return;
		}
		if ( PFC_TRANSPORT_TYPE_IPV6 == m_emType )
		{
			memcpy( pbyIpv6 , m_tAddr.m_tIPv6.m_abyIP , PFC_IPV6_ADDR_SIZE );
			*pwPort = m_wPort;
		}
	}

	BOOL32 IsLegalIp()
	{
		u8  abyTempIpv6Addr[PFC_IPV6_ADDR_SIZE] = {0};
		if (PFC_TRANSPORT_TYPE_IP == m_emType &&  m_tAddr.m_tIPv4.m_dwIP != 0)
		{
			return TRUE;
		}
		else if (PFC_TRANSPORT_TYPE_IPV6 == m_emType && (MEMCMP_CAST(m_tAddr.m_tIPv6.m_abyIP, abyTempIpv6Addr, PFC_IPV6_ADDR_SIZE) != 0 ))
		{
			return TRUE;
		}
		return FALSE;
	}
}PFC_IPADDR,*PPFC_IPADDR;
#pragma pack()	

///Static NAT Addr Pairs
typedef struct PROTO_API tagNATAddrPairs
{
	PFC_IPADDR m_tLocalAddr;         ///< Local Addr
	PFC_IPADDR m_tStaticNATAddr;     ///< NAT   Addr

	tagNATAddrPairs()
	{
		Clear();
	}

	void Clear()
	{
		m_tLocalAddr.Clear();
		m_tStaticNATAddr.Clear();
	}

}TNATAddrPairs,*PTNATAddrPairs;

///Static NAT Addr struct
typedef struct PROTO_API tagStaticNATAddr
{
	BOOL32        m_bUseStaticNAT;                          ///< Used NAT,or not
	TNATAddrPairs m_atNATAddrPairs[MAX_STATIC_NAT_NUM];     ///< NAT Addr Pairs Struct

	tagStaticNATAddr()
	{
		Clear();
	}

	void Clear()
	{
		m_bUseStaticNAT = FALSE;
		for (s32 i = 0;i<MAX_STATIC_NAT_NUM;i++)
		{
			m_atNATAddrPairs[i].Clear();
		}
	}
	/**
    * \brief           Set NAT Address Pairs
    * \param[in]       tNATAddrPairs     : NAT Address Pairs
	* \param[in]       dwNATAddrPairsNo  :Num of NAT Address Pairs
    * \return           void.
    */
	void SetNATAddrPairs(TNATAddrPairs &tNATAddrPairs,u32 dwNATAddrPairsNo = 0 )
	{
		if (MAX_STATIC_NAT_NUM <= dwNATAddrPairsNo)
		{
			return;
		}
		m_atNATAddrPairs[dwNATAddrPairsNo] = tNATAddrPairs;
	}

	/**
    * \brief           Get NAT Address Pairs
	* \param[in]       dwNATAddrPairsNo  :Num of NAT Address Pairs
    * \return          PTNATAddrPairsd   :The pointer to  NAT Address Pairs
    */
	PTNATAddrPairs GetNATAddrPairs(u32 dwNATAddrPairsNo)
	{
		if (MAX_STATIC_NAT_NUM <= dwNATAddrPairsNo)
		{
			return NULL;
		}
		return &(m_atNATAddrPairs[dwNATAddrPairsNo]);
	}

}TStaticNATAddr,*PTStaticNATAddr;

#endif
