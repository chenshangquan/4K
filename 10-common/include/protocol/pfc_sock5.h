#ifdef _PFC_ENABLE_SOCK5_API_

#if defined(_MSC_VER) || defined(_LINUX_)

//sock5代理版本号
#define SOCK5_PROXY_VERSION         (u8)0x05
//客户端支持鉴权方法
#define SOCK5_PROXY_AUTHEN_NO_REQUIERD          (u8)0x00
#define SOCK5_PROXY_AUTHEN_USERNAME_PASSWORD    (u8)0x02
//操作结果
#define SOCK5_PROXY_SUCCESS                     (u8)0x00
#define SOCK5_PROXY_AUTHEN_NO_ACCEPTABLE        (u8)0xff
//请求命令
#define SOCK5_PROXY_CMD_TCP_CONNECT             (u8)0x01
#define SOCK5_PROXY_CMD_TCP_BIND                (u8)0x02
#define SOCK5_PROXY_CMD_UDP_ASSOCIATE           (u8)0x03
//保留字段
#define SOCK5_PROXY_RESERVED_DATA               (u8)0x00
//地址类型
#define SOCK5_PROXY_IPV4_ADDR                   (u8)0x01
#define SOCK5_PROXY_DOMAIN_NAME                 (u8)0x03
#define SOCK5_PROXY_IPV6_ADDR                   (u8)0x04


#define MAX_SOCK5PROXY_AUTHEN_NUM   (u8)0xff
#define MAX_SOCK5PROXY_NAME_PASS_LENGTH (u8)64
typedef struct {
	u32 m_dwProxyIP;
	u16 m_wProxyPort;
	u8 m_byAuthenNum;
	u8 m_abyAuthenMethod[MAX_SOCK5PROXY_AUTHEN_NUM];
	s8 m_achUseName[MAX_SOCK5PROXY_NAME_PASS_LENGTH + 1];
	s8 m_achPassword[MAX_SOCK5PROXY_NAME_PASS_LENGTH + 1];
} TPfcSock5Proxy;

/*=============================================================================
函 数 名：PfcConnectTcpNodeThroughSock5Proxy
功    能：TCP穿越sock5代理连接服务端（与PfcConnectTcpNode功能相同，上层不需要调用PfcConnectToSock5Proxy与代理建链）
注    意：
算法实现：
全局变量：
参    数：ptOspSock5Proxy : [in] 代理服务器信息结构;
          dwServerIP : [in] 服务器IP
          wServerPort : [in] 服务器端口
          wHb: [in] 断链检测周期(秒)
          byHbNum: [in] byHbNum次未到连接检测应答后认为链路已断开
          dwTimeoutMs : [in] 操作超时时间
          pdwLocalIP: [in,out] 本TCP链接使用的本地IP
返 回 值：失败返回INVALID_NODE；
          成功返回一个动态分配的结点号, 此后用户可借此与服务结点通信
          上层主动断链需调用PfcDisconnectTcpNode，所有与无代理时均无区别
-------------------------------------------------------------------------------
 修改纪录：
 日      期  版本  修改人  修改内容
 2006/08/21  4.0   王小月
=============================================================================*/
API int PfcConnectTcpNodeThroughSock5Proxy( TPfcSock5Proxy *ptOspSock5Proxy , u32 dwServerIP, u16 wServerPort,
		u16 wHb = 10, u8 byHbNum = 3 , u32 dwTimeoutMs = 0 , u32 *pdwLocalIP = NULL, u8 bySocksAuthVerion = SOCK5_PROXY_VERSION );

/*=============================================================================
函 数 名：PfcConnectToSock5Proxy
功    能：与sock5代理服务器建立TCP链路（UDP穿越sock5代理必须先建立一条TCP链路）
注    意：
算法实现：
全局变量：
参    数：ptOspSock5Proxy : [in] 代理服务器信息结构
          dwTimeoutMs : [in] 操作超时时间
返 回 值：失败返回INVALID_SOCKET；
          成功返回与代理通信的TCP Socket，可进一步调用PfcUdpAssociateThroughSock5Proxy建立UDP Associate；
          可复用，需要上层维护本TCP连接，链路段无效时，Udp Associate也应视为无效，
          主动断链请调用OspDisconnectFromSock5Proxy；
-------------------------------------------------------------------------------
 修改纪录：
 日      期  版本  修改人  修改内容
 2006/08/21  4.0   王小月
=============================================================================*/
API PFCSOCKHANDLE PfcConnectToSock5Proxy( TPfcSock5Proxy *ptOspSock5Proxy , u32 dwTimeoutMs = 0 , u8 bySocksAuthVerion = SOCK5_PROXY_VERSION);

/*=============================================================================
函 数 名：PfcUdpAssociateThroughSock5Proxy
功    能：UDP穿越sock5代理
注    意：
算法实现：
全局变量：
参    数：hSocket : [in] PfcConnectToSock5Proxy返回的socket(可复用);
          dwLocalIP : [in] 本地收发socket IP，以便代理服务器限制数据穿越（网络序）
          wLocaPort : [in] 本地收发socket 端口，以便代理服务器限制数据穿越（主机序）
          pdwProxyMapIP : [out] 代理服务器映射IP（网络序）
          pwProxyMapPort : [out] 代理服务器映射端口（主机序）
          dwTimeoutMs : [in] 操作超时时间
返 回 值：失败返回FALSE；
          成功返回TRUE
-------------------------------------------------------------------------------
 修改纪录：
 日      期  版本  修改人  修改内容
 2006/08/21  4.0   王小月
=============================================================================*/
API BOOL32 PfcUdpAssociateThroughSock5Proxy( PFCSOCKHANDLE hSocket , u32 dwLocalIP, u16 wLocalPort ,
		u32 *pdwProxyMapIP, u16 *pwProxyMapPort , u32 dwTimeoutMs = 0 );

/*=============================================================================
函 数 名：PfcDisConnectFromSock5Proxy
功    能：断开与sock5代理建立的用于UDP Associate的TCP连接
注    意：
算法实现：
全局变量：
参    数：hSocket : [in] PfcConnectToSock5Proxy返回的socket;
返 回 值：失败返回FALSE；
          成功返回TRUE
-------------------------------------------------------------------------------
 修改纪录：
 日      期  版本  修改人  修改内容
 2006/08/21  4.0   王小月
=============================================================================*/
API BOOL32 PfcDisConnectFromSock5Proxy( PFCSOCKHANDLE hSocket );

#endif //defined(_MSC_VER) || defined(_LINUX_)

#endif //#ifdef _ENABLE_SOCK5_API_
