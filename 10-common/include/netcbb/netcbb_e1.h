#ifndef _NETCBB_E1_H_
#define _NETCBB_E1_H_
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* TBrdE1MultiLinkChanInfo结构体中dwProtocolType参数宏定义 */
#define INTERFACE_PROTOCOL_PPP           0  /* 接口协议PPP */
#define INTERFACE_PROTOCOL_HDLC          1  /* 接口协议HDLC */

/* TBrdE1MultiLinkChanInfo结构体中dwAuthenticationType参数宏定义 */
#define MP_AUTHENTICATION_NONE           0  /* 不设置验证方法 */
#define MP_AUTHENTICATION_PAP            1  /* PPP链接的验证方法PAP */
#define MP_AUTHENTICATION_CHAP           2  /* PPP链接的验证方法CHAP */

/* TBrdE1MultiLinkChanInfo结构体中dwFragMinPackageLen 参数范围宏定义 */
#define MP_FRAG_MIN_PACKAGE_LEN_MIN_VAL  20
#define MP_FRAG_MIN_PACKAGE_LEN_MAX_VAL  1500

#define E1_TS0_MASK        0x00000001


/* TBrdE1SerialInfo结构体中dwEchoInterval dwEchoMaxRetry 参数最大值宏定义 */
#define E1_SERIAL_ECHO_MAX_VAL           256

/* dwFragMinPackageLen dwSerialId dwE1ChanGroupId 参数自动设置宏定义 */
#define E1_PARAM_AUTO_CONFIG             0xffffffff

/* 参数 wBufLength 范围定义 */
#define E1_TRANS_BUF_MAX_LEN   (u32)8000 /* 缓冲区队列中最大BUF的长度,单位字节 */
#define E1_TRANS_BUF_MIN_LEN   (u32)800  /* 缓冲区队列中最小BUF的长度,单位字节 */
#define E1_TRANS_CHAN_MAX_NUM  (u8)16    /* 最多支持的E1透明传输通道的个数，一个通道仅对应于一条物理E1线路 */

/* E1模块返回值及错误码定义 */
#define E1_ERR_UNKNOWN                         (NET_E1_BASE_ERROR+0)  /* 未知错误 */
#define E1_ERR_PARAM_EXCEPTION                 (NET_E1_BASE_ERROR+1)  /* 参数异常 */
#define E1_ERR_SERIAL_ID_INVALID               (NET_E1_BASE_ERROR+2)  /* SERIAL同步接口号无效 */
#define E1_ERR_E1_ID_INVALID                   (NET_E1_BASE_ERROR+3)  /* E1接口号无效 */
#define E1_ERR_E1_TSMASK_INVALID               (NET_E1_BASE_ERROR+4)  /* E1时隙掩码无效 */
#define E1_ERR_E1_CHANGROUP_ID_INVALID         (NET_E1_BASE_ERROR+5)  /* E1时隙分配所在的编组号无效 */
#define E1_ERR_SERIAL_PROTOCOL_TYPE_INVALID    (NET_E1_BASE_ERROR+6)  /* 接口协议封装类型无效 */
#define E1_ERR_SERIAL_ECHO_INTERVAL_INVALID    (NET_E1_BASE_ERROR+7)  /* 同步接口的echo请求时间间隔无效 */
#define E1_ERR_SERIAL_ECHO_MAXRETRY_INVALID    (NET_E1_BASE_ERROR+8)  /* 同步接口的echo最大重发次数无效 */
#define E1_ERR_STRING_LEN_OVERFLOW             (NET_E1_BASE_ERROR+9)  /* 字符串长度溢出 */
#define E1_ERR_NIP_OPT_ERR                     (NET_E1_BASE_ERROR+10) /* nip接口调用失败 */
#define E1_ERR_CHAN_NOT_CONF                   (NET_E1_BASE_ERROR+11) /* 指定的通道号未打开使用 */
#define E1_ERR_CHAN_CONFLICT                   (NET_E1_BASE_ERROR+12) /* 通道号冲突，指定的通道号已被使用 */
#define E1_ERR_MP_AUTHEN_TYPE_INVALID          (NET_E1_BASE_ERROR+13) /* PPP链接的验证方法类型无效 */
#define E1_ERR_MP_FRAG_MIN_PACKAGE_LEN_INVALID (NET_E1_BASE_ERROR+14) /* 最小分片包长无效 */

#define E1_PARAM_CHECK_ERROR                   (NET_E1_BASE_ERROR +15)
#define E1_PARAM_CONFLICT                      (NET_E1_BASE_ERROR +16)




#define MP_STRING_MAX_LEN            NET_DEF_STR_LEN  /* TNetE1MultiLinkChanInfo结构体中字符串最大长度 */
/* E1线路NIP封装接口相关宏定义 */
#define E1_SINGLE_LINK_CHAN_MAX_NUM  8 /* 最大支持的E1单链路serial同步接口个数 */
#define E1_MULTI_LINK_CHAN_MAX_NUM   8 /* 最大支持的E1多链路捆绑连接通道(即virtual虚拟模板接口)个数 */

/* E1相关的结构定义 */
/* E1线路单个serial接口参数结构 */
typedef struct{
    u32 dwUsedFlag;       /* 当前serial同步接口使用标志,置1使用，下面参数有效；0不使用，下面参数无效 */
    u32 dwSerialId;       /* serial同步接口编号，e1链路从16开始，有效范围16~62,不可冲突 */
    u32 dwE1Id;           /* 该serial同步接口对应的e1编号，可配置范围0~E1_MAXNUM-1, E1_MAXNUM取决于相应硬件支持的e1个数,如kdv8010终端 #define BRD_MT_E1_MAXNUM 4 */
    u32 dwE1TSMask;       /* E1时隙分配说明,详见下 */
    u32 dwE1ChanGroupId;  /* E1时隙分配所在的编组号，可配置范围0~7,如果不拆分一个E1使用的话填0，如果拆分的话必须对每个时隙段进行依次编号 */
    u32 dwProtocolType;   /* 接口协议封装类型,如果是单E1连接可以指定PPP/HDLC，如果是多E1捆绑连接必须是PPP协议 */
    u32 dwEchoInterval;   /* 对应serial同步接口的echo请求时间间隔，秒为单位，有效范围0-256，填默认值2即可 */
    u32 dwEchoMaxRetry;   /* 对应serial同步接口的echo最大重发次数，有效范围0-256，填默认值5即可 */
}TNetE1SerialInfo;
/******************************************************************************
* dwE1TSMask时隙分配补充说明：
*    时晰分配的掩码，由Ts31 Ts30...Ts0构成32位掩码，TSx为1时表示使用该时隙，为0时不使用
* Ts0作为同步信号，用户不可使用, 0x0、0x1都是非法的参数，有效范围：0x2~0xfffffffe；
* 例: 使用TS1~TS5 5个时隙时dwE1TSMask = 0x0000003e,注意:Ts0=0; 此时带宽= 64x5 = 320kbit
      使用TS1~TS3,TS30~31 5个时隙时dwE1TSMask = 0xc000000e,注意:Ts0=0; 此时带宽= 64x5 = 320kbit
******************************************************************************/

/* 单E1链路连接通道参数结构 */
typedef struct{
    u32 dwUsedFlag;                  /* 当前E1单链路连接通道使用标志,置1使用，下面参数有效；0不使用，下面参数无效 */
    u32 dwIpAdrs;                    /* ip地址，网络序 */
    u32 dwIpMask;                    /* 掩码，网络序 */
    TNetE1SerialInfo tE1SerialInfo;  /* 相应serial同步接口链路参数 */
}TNetE1SingleLinkChanInfo;

/* 多E1链路捆绑连接通道参数结构 */
typedef struct{
    u32  dwUsedFlag;                       /* 当前E1多链路捆绑连接通道使用标志,置1使用，下面参数有效；0不使用，下面参数无效 */
    u32  dwIpAdrs;                         /* ip地址，网络序 */
    u32  dwIpMask;                         /* 掩码，网络序 */
    u32  dwAuthenticationType;             /* PPP链接的验证方法PAP/CHAP,默认填MP_AUTHENTICATION_PAP */
    u32  dwFragMinPackageLen;              /* 最小分片包长，字节为单位，范围20~1500，默认填20 */
    char chSvrUsrName[MP_STRING_MAX_LEN];  /* 服务端用户名称，用来验证对端的数据 */
    char chSvrUsrPwd[MP_STRING_MAX_LEN];   /* 服务端用户密码，用来验证对端的数据 */
    char chSentUsrName[MP_STRING_MAX_LEN]; /* 客户端用户名称，用来被对端验证 */
    char chSentUsrPwd[MP_STRING_MAX_LEN];  /* 客户端用户密码，用来被对端验证 */
    TNetE1SerialInfo tE1SerialInfo[E1_SINGLE_LINK_CHAN_MAX_NUM];/* 每个被捆绑的serial同步接口链路参数 */
}TNetE1MultiLinkChanInfo;

/************************************************************
 * 函数名 : NetGetE1Bandwidth
 *
 * 功能 : 获取指定E1接口带宽
 *
 * 描述 : 无
 *
 * 参数说明 :
 *     ifname - 网卡Id
 *     ifunit - 指定接口号

 * 返回值 : 成功:dwBandWidth/失败:0
 ***********************************************************/
u32 NetGetE1Bandwidth(char* ifname, int ifunit);

/************************************************************
 * 函数名 : NetSetE1Clock
 *
 * 功能 : 添加dce或者dte
 *
 * 描述 : 无
 *
 * 参数说明 :
 *     e1    - e1为E1接口号
 *     clock - clock为("dce"或"dte")
 *
 * 返回值 : OK    - 成功
 *          ERROR - 失败
 ***********************************************************/
s32 NetSetE1Clock(int e1, char* clock);

/************************************************************
 * 函数名 : NetOpenE1SingleLinkChan
 *
 * 功能 : 创建一个E1单链路连接通道
 *
 * 描述 : 无
 *
 * 参数说明 :
 *     dwChanID    - 单链路连接通道号，范围0~ E1_SINGLE_LINK_CHAN_MAX_NUM -1，
 *                   该ID具有唯一性，用来标识每个单链路连接通道，不可冲突
 *                   一个通道不可重复打开，必须先关闭
 *     ptChanParam:单链路连接通道参数结构指针
 *
 * 返回值 : E1_RETURN_OK/ERRCODE
 ***********************************************************/
s32 NetOpenE1SingleLinkChan(u32 dwChanID, TNetE1SingleLinkChanInfo* ptChanParam);

/************************************************************
 * 函数名 : NetCloseE1SingleLinkChan
 *
 * 功能 : 关闭指定的E1单链路连接通道
 *
 * 描述 : 无
 *
 * 参数说明 :
 *     dwChanID    - 单链路连接通道号，范围0~ E1_SINGLE_LINK_CHAN_MAX_NUM -1，
 *                   该ID具有唯一性，用来标识每个单链路连接通道，不可冲突
 *                   该通道必须是已经打开成功的，如果未打开则返回E1_ERR_CHAN_NOT_CONF;
 *
 * 返回值 : E1_RETURN_OK/ERRCODE
 ***********************************************************/
s32 NetCloseE1SingleLinkChan(u32 dwChanID);

/************************************************************
 * 函数名 : NetOpenE1MultiLinkChan
 *
 * 功能 : 创建一个E1多链路捆绑连接通道
 *
 * 描述 : 调用路由组提供的nip模块的接口
 *
 * 参数说明 :
 *     dwChanID    - 单链路连接通道号，范围0~ E1_SINGLE_LINK_CHAN_MAX_NUM -1，
 *                   该ID具有唯一性，用来标识每个单链路连接通道，不可冲突
 *                   一个通道不可重复打开，必须先关闭
 *     ptChanParam - 多链路捆绑连接通道参数结构指针
 
 * 返回值 : E1_RETURN_OK/ERRCODE
 ***********************************************************/
s32 NetOpenE1MultiLinkChan(u32 dwChanID, TNetE1MultiLinkChanInfo* ptMpParam);

/************************************************************
 * 函数名 : NetCloseE1MultiLinkChan
 *
 * 功能 : 关闭指定的E1多链路捆绑连接通道
 *
 * 描述 : 调用路由组提供的nip模块的接口
 *
 * 参数说明 :
 *     dwChanID    - 单链路连接通道号，范围0~ E1_SINGLE_LINK_CHAN_MAX_NUM -1，
 *                   该ID具有唯一性，用来标识每个单链路连接通道，不可冲突
 *                   该通道必须是已经打开成功的，如果未打开则返回E1_ERR_CHAN_NOT_CONF
 
 * 返回值 : E1_RETURN_OK/ERRCODE
 ***********************************************************/
s32 NetCloseE1MultiLinkChan(u32 dwChanID);

/************************************************************
 * 函数名 : NetGetE1Remoteip
 *
 * 功能 : 获取指定E1接口远端ip
 *
 * 描述 : 调用路由组提供的nip模块的接口
 *
 * 参数说明 :
 *     ifname    - 指定接口类型
 *     ifunit    - 指定接口号
 *
 * 返回值 : OK    - 成功
 *          ERROR - 失败
 ***********************************************************/
u32 NetGetE1Remoteip(char* ifname , int ifunit);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif

