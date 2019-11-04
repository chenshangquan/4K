/*****************************************************************************
   模块名      : mcu
   文件名      : mcuconst.h
   相关文件    : 
   文件实现功能: MCU常量定义
   作者        : 胡昌威
   版本        : V3.0  Copyright(C) 2001-2002 KDC, All rights reserved.
-----------------------------------------------------------------------------
   修改记录:
   日  期      版本        修改人      修改内容
   2003/10/13  3.0         胡昌威       创建
   2005/02/19  3.6         万春雷       级联修改
******************************************************************************/
#ifndef __MCUCONST_H_
#define __MCUCONST_H_

#ifndef _EXCLUDE_VCCOMMON_H
#include "vccommon.h"
#endif

//OS类型
#define     OS_TYPE_VXWORKS                 1   //Vx
#define     OS_TYPE_LINUX                   2   //Linux
#define     OS_TYPE_WIN32                   3   //Windows

//设备子类定义---MCU类型定义
// 采用vccommon.h中的定义
// MCU_TYPE_KDV8000
// MCU_TYPE_KDV8000B
// MCU_TYPE_KDV8000C
// MCU_TYPE_WIN32

//设备子类定义---外设类型定义
#define		EQP_TYPE_MIXER                   1   //混音器
#define		EQP_TYPE_VMP                     2   //图像合成器
#define		EQP_TYPE_RECORDER                3   //录像机
#define		EQP_TYPE_BAS                     4   //码流适配器
#define		EQP_TYPE_TVWALL                  5   //电视墙
#define		EQP_TYPE_DCS                     6   //数据服务器
#define     EQP_TYPE_PRS                     7   //包重传
#define     EQP_TYPE_FILEENC                 8   //文件编码器
#define		EQP_TYPE_VMPTW                   9   //图像合成电视墙
//4.6版本 新加 jlb
#define		EQP_TYPE_HDU					10	 //高清数字电视墙// xliang [12/5/2008]

// 以下是外设子类型，内部使用
#define		TYPE_MPUSVMP				11	 //MPU-单VMP
#define		TYPE_MPUDVMP				12   //MPU-VMP
#define		TYPE_MPUBAS					13	 //MPU-BAS
#define		TYPE_EVPU					14	 //EVMP
#define		TYPE_EBAP					15   //EBAP

// mpu子类型定义---------xliang [12/5/2008] ----------
#define		VMP								(u8)0	//老vpu (默认值0)
#define		EVPU_SVMP						(u8)1	//EVPU-单VMP
#define		EVPU_DVMP						(u8)2	//EVPU-双VMP
#define		MPU_SVMP						(u8)3	//MPU-单VMP
#define		MPU_DVMP					    (u8)4	//MPU-双VMP
#define		MPU_BAS							(u8)5	//mpu-bas
#define		MPU_EBAP						(u8)6	//EBAP

//MPU board version
#define		MPU_BOARD_A128					(u8)0	//MPU A 板
#define		MPU_BOARD_B256					(u8)1	//MPU B 板

//VMP输出通道数目
#define		MAXNUM_MPU_OUTCHNNL				(u8)4	//MPU  4出
#define		MAXNUM_EVPU_OUTCHNNL			(u8)2	//EVPU 2出

//MPU高清前适配通道数目
#define		MAXNUM_SVMP_HDCHNNL				(u8)3	//SVMP前适配通道数：3   
#define		MAXNUM_DVMP_HDCHNNL				(u8)1	//DVMP前适配通道数：1
#define		MAXNUM_SVMPB_HDCHNNL			(u8)4	//SVMP B板前适配通道数: 4

//MPU承受非h264 CIF能力
#define		MAXNUM_SVMP_NON264CIFCHNNL		(u8)12	

//Resolutions that can be acceptable
#define		MAXNUM_ACCEPTABLE_RES			(u8)55

//设备子类定义---终端类型定义
#define		MT_TYPE_NONE                     0   //不接收也不发送
#define     MT_TYPE_MT                       3
#define		MT_TYPE_MMCU	                 4   //上级MCU
#define     MT_TYPE_SMCU                     5   //下级MCU

//传送图像声音参数模式
#define		MODE_NONE			             0	 //音视频都不传
#define		MODE_VIDEO						 1	 //只传视频
#define		MODE_AUDIO						 2	 //只传音频
#define		MODE_BOTH						 3   //音视频都传
#define     MODE_DATA                        4   //数据 
#define     MODE_SECVIDEO                    5   //第二路视频

//厂商编号定义
#define		MT_MANU_KDC                      1   //科达
#define		MT_MANU_NETMEETING               2   //Netmeeting
#define		MT_MANU_POLYCOM                  3   //PolyCom
#define		MT_MANU_HUAWEI                   4   //华为
#define		MT_MANU_TAIDE                    5   //泰德
#define		MT_MANU_SONY                     6   //SONY
#define		MT_MANU_VCON                     7   //VCON
#define		MT_MANU_RADVISION                8   //Radvision
#define     MT_MANU_KDCMCU                   9   //kedamcu
#define		MT_MANU_PENTEVIEW                10  //中泰
#define		MT_MANU_VTEL                     11  //VTEL
#define     MT_MANU_ZTE                      12  //中兴终端
#define     MT_MANU_ZTEMCU                   13  //中兴MCU
#define     MT_MANU_CODIAN                   14  //CodianMCU
#define		MT_MANU_OTHER                    15  //其它

//终端会议状态
#define     MT_STATUS_AUDIENCE               0   //观众  
#define     MT_STATUS_CHAIRMAN               1   //主席
#define     MT_STATUS_SPEAKER                2   //发言人

//TvWallOutputMode
#define     TW_OUTPUTMODE_NONE               0   //无输出模式
#define     TW_OUTPUTMODE_AUDIO              1   //音频输出模式
#define     TW_OUTPUTMODE_VIDEO              2   //视频输出模式
#define     TW_OUTPUTMODE_BOTH               3   //音视频输出模式

//HduOutputMode   jlb
#define     HDU_OUTPUTMODE_NONE               0   //无输出模式
#define     HDU_OUTPUTMODE_AUDIO              1   //音频输出模式
#define     HDU_OUTPUTMODE_VIDEO              2   //视频输出模式
#define     HDU_OUTPUTMODE_BOTH               3   //音视频输出模式
//终端离线原因
#define     MTLEFT_REASON_EXCEPT             1   //异常：网络或接入或转发
#define     MTLEFT_REASON_NORMAL             2   //正常挂断
#define     MTLEFT_REASON_RTD                3   //RTD超时
#define     MTLEFT_REASON_DRQ                4   //DRQ
#define     MTLEFT_REASON_UNMATCHTYPE        5   //类型不匹配
//终端未加入原因
#define     MTLEFT_REASON_BUSY               6   //终端忙
#define     MTLEFT_REASON_REJECTED           7   //终端主动挂断
#define     MTLEFT_REASON_UNREACHABLE        8   //终端不可达
#define     MTLEFT_REASON_LOCAL              9   //
#define     MTLEFT_REASON_BUSYEXT            10  //终端忙,带终端目前所在会议的级别及会议名称

#define     MTLEFT_REASON_UNKNOW             0xff   //未知错误

//级联调分辨率拒绝的原因
#define		CASCADE_ADJRESNACK_REASON_NONEKEDA	1		//非科达(不能下调)
#define		CASCADE_ADJRESNACK_REASON_INTVWALL	2		//在DEC5中（不能上调）【可考虑回ack】
#define		CASCADE_ADJRESNACK_REASON_INVMP		3		//在VMP中
#define		CASCADE_ADJRESNACK_REASON_UNKNOWN	0		//未知原因


//协议类型定义
#define		PROTOCOL_TYPE_H323				1  //H323
#define		PROTOCOL_TYPE_H320              2  //H320
#define		PROTOCOL_TYPE_SIP               3  //SIP

//MCU配置和业务常量定义
#define     MAXNUM_H225H245_MT              192 //底层协议栈呼叫最大个数
#define		MAXNUM_CONF_MT					192  //单个会议中最大MT数,牵涉到接口，8000B与8000维持不变 
#define		MAXNUM_CALL_CHANNEL             12   //每个呼叫中的最大通道数

#define     MAXNUM_MCU_VC                   16   //MCU支持同时连接的最大VCS数
#define		MAXNUM_MCU_MC			        16   //MCU连接会议控制台最大数
#define		MAXNUM_MCU_PERIEQP				140    //MCU下最多外设数, 新增28个HDU, 空闲位置16，须多加12个位置
//#define		MAXNUM_MCU_PERIEQP				(128+12)    //MCU下最多外设数, 新增28个HDU, 空闲位置16，须多加12个位置
#define		MAXNUM_CONF_SPY					128	 //一个会议最大spy数
#define     SPY_CHANNL_NULL                 65535 // 标示该级联多回传通道未分配
#define     DEFAULT_MAX_SENDSPY_BW          100000
#define     DEFAULT_MAX_RECVSPY_BW          100000

#define     MAXNUM_MC_CHANNL                16  // 会控台的最大监控通道数

// 设置MTU大小, zgc, 2007-04-02
#define		MAXNUM_MTU_SIZE					1468  //MTU最大长度
#define		MINNUM_MTU_SIZE					1308  //MTU最小长度
#define		DEFAULT_MTU_SIZE				MAXNUM_MTU_SIZE  //MTU默认长度

// 缺省的DSC和MCU8000外部IP和内部通信IP
#define DEFAULT_MCU_IP                          "192.168.2.1"
#define DEFAULT_DSC_IP                          "192.168.2.2"
#define DEFAULT_IPMASK        					"255.255.255.0"

#define DEFAULT_MCU_INNERIP                     "10.253.253.250"
#define DEFAULT_DSC_INNERIP                     "10.253.253.249"
#define DEFAULT_INNERIPMASK						"255.255.255.252"

#define ETH_IP_MAXNUM						    16
#define MAXNUM_MCSACCESSADDR					2

// MINIMCU所在的网络类型
#define	NETTYPE_INVALID						0
#define NETTYPE_LAN							1
#define NETTYPE_WAN							2
#define NETTYPE_MIXING_ALLPROXY				3
#define NETTYPE_MIXING_NOTALLPROXY			4

#ifdef _MINIMCU_    // 8000B 能力

// 首先是内部数据结构能力限制
#define     MAXNUM_MCU_MT                   (u16)128  //一个MCU支持最大终端数（同时在线的终端） 
#define		MAXNUM_MCU_CONF					64        //一个MCU内部可用的最大会议索引范围
#define     MAXNUM_MCU_TEMPLATE             32        //最大模板个数(总数16增加到32，其中16个分给VCS)
#define     MAXNUM_MCU_VCSTEMPLATE          16        //VCS可创建的模板数
#define     MAXNUM_MCU_MCSTEMPLATE          (MAXNUM_MCU_TEMPLATE - MAXNUM_MCU_VCSTEMPLATE)
#define		MAXNUM_DCS_CONF					16
#define		MAXNUM_DCS_CONFMT				16

#define     MAXNUM_MCU_VCCONF              16        //一个MCU上最大能召开的调度会议数 

#define		MAXNUM_DRI                      16        //DRI最大板数 
#define		MAXNUM_DRI_MT                   192       //DRI板上单个会议的最大终端数

// 下面是商业能力限制
#define     MAXLIMIT_MPC_MP                 (u16)32   // MPC 内置MP转发能力, MB
#define     MAXLIMIT_CRI_MP_MDSC            (u16)128  // CRI MP(MDSC) 转发能力, MB (32*2M*2direction)
#define     MAXLIMIT_CRI_MP_HDSC            (u16)512  // CRI MP(HDSC) 转发能力, MB (128*2M*2direction)
#define     MAXLIMIT_CRI_MP                 MAXLIMIT_CRI_MP_HDSC

#define     MAXLIMIT_MPC_MP_PMNUM           (u16)16   // MPC内置MP转发能力，PM(按码率和终端数的乘积计算，mcu业务对MP转发能力作出的上限限制。单位PM：一个1M的终端为一个PM)
#define     MAXLIMIT_CRI_MP_MDSC_PMNUM      (u16)64   // CRI MP(MDSC) 转发能力, PM
#define     MAXLIMIT_CRI_MP_HDSC_PMNUM      (u16)256  // CRI MP(HDSC) 转发能力, PM
#define     MAXLIMIT_CRI_MP_PMNUM           MAXLIMIT_CRI_MP_HDSC_PMNUM

#define		MAXHDLIMIT_MPC_MTADP			(u8)2	  //MPC 内置MtAdp接入HD MT能力
#define		MAXNUM_HDI_MT					(u16)48  //HDI上单个会议的最大终端数

#ifdef WIN32
#define     MAXLIMIT_MPC_MTADP              (u8)112   // MCU 内置MtAdp接入能力
#define     MAXLIMIT_MPC_MTADP_SMCU         (u8)28    // MCU 内置MtAdp SMCU接入能力	
#else
#define     MAXLIMIT_MPC_MTADP              (u8)8     // MCU 内置MtAdp接入能力
#define     MAXLIMIT_MPC_MTADP_SMCU         (u8)4     // MCU 内置MtAdp SMCU接入能力
#endif
#define     MAXLIMIT_CRI_MTADP              (u8)128   // HDSC/MDSC 接入能力
#define     MAXLIMIT_CRI_MTADP_SMCU         (u8)16    // HDSC/MDSC SMCU接入能力
#define     MAXLIMIT_HDI_MTADP              (u8)112     // HDI 接入能力(没有意义，仅方便编译)

#define     MAXLIMIT_MCU_CASCONF            (u8)4     // 最多级联会议个数
#define     MAXLIMIT_CONF_SMCU              (u8)4     // 单个会议最大 SMCU

#else               // 8000 能力

// 首先是内部数据结构能力限制
#define     MAXNUM_MCU_MT                   (u16)448  //MCU支持最大终端数 
#define		MAXNUM_MCU_CONF					64        //一个MCU内部可用的最大会议索引范围
#define     MAXNUM_MCU_TEMPLATE             64        //最大模板个数
#define     MAXNUM_MCU_VCSTEMPLATE          16        //VCS可创建的模板数
#define     MAXNUM_MCU_MCSTEMPLATE          (MAXNUM_MCU_TEMPLATE - MAXNUM_MCU_VCSTEMPLATE)
#define		MAXNUM_DCS_CONF					32
#define		MAXNUM_DCS_CONFMT				64

#define     MAXNUM_MCU_VCCONF              16        //一个MCU上最大能召开的调度会议数 

#define		MAXNUM_DRI                      64        //DRI最大板数 
#define		MAXNUM_DRI_MT                   192       //DRI板上单个会议的最大终端数

// 下面是商业能力限制
#define     MAXLIMIT_MPC_MP                 (u16)60   // MPC 内置MP转发能力, MB
#define     MAXLIMIT_CRI_MP                 (u16)120  // CRI MP 转发能力, MB(按码率计算，mplib作流量统计使用)

#define     MAXLIMIT_MPC_MP_PMNUM           (u16)30   // MPC 内置MP转发能力, PM(按码率和终端数的乘积计算，mcu业务对MP转发能力作出的上限限制。单位PM：一个1M的终端为一个PM)
#define     MAXLIMIT_CRI_MP_PMNUM           (u16)60   // CRI MP 转发能力

#define		MAXHDLIMIT_MPC_MTADP			(u8)2	  //MPC 内置MtAdp接入HD MT能力
#define		MAXNUM_HDI_MT					(u16)48  //HDI上单个会议的最大终端数
 
#ifdef WIN32
#define     MAXLIMIT_MPC_MTADP              (u8)112   // MPC 内置MtAdp接入能力
#define     MAXLIMIT_MPC_MTADP_SMCU         (u8)28    // MPC 内置MtAdp SMCU接入能力
#else
#define     MAXLIMIT_MPC_MTADP              (u8)24    // MPC 内置MtAdp接入能力
#define     MAXLIMIT_MPC_MTADP_SMCU         (u8)12    // MPC 内置MtAdp SMCU接入能力
#endif
#define     MAXLIMIT_CRI_MTADP              (u8)112   // CRI 接入能力
#define     MAXLIMIT_CRI_MTADP_SMCU         (u8)28    // CRI SMCU接入能力
#define     MAXLIMIT_HDI_MTADP              (u8)112     // HDI 接入能力

#ifdef WIN32
#define     MAXLIMIT_MCU_CASCONF            (u8)2     // 最多级联会议个数
#define     MAXLIMIT_CONF_SMCU              (u8)4     // 单个会议最大 SMCU
#else
#define     MAXLIMIT_MCU_CASCONF            (u8)16    // 最多级联会议个数
#define     MAXLIMIT_CONF_SMCU              (u8)56    // 单个会议最大 SMCU
#endif
#endif

#define     MAXNUM_MCU_MODEM                (u16)16     //卫星会议最大modem数

//会议高清适配类型
#define     CHN_ADPMODE_NONE               (u8)0   //空
#define     CHN_ADPMODE_MVBRD              (u8)1   //主流广播适配
#define     CHN_ADPMODE_DSBRD              (u8)2   //双流广播适配
#define     CHN_ADPMODE_MVSEL              (u8)3   //主流选看适配
#define     CHN_ADPMODE_DSSEL              (u8)4   //双流选看适配

//高清适配通道类型定义
#define     TYPE_MAU_NORMAL                 (u8)0   //普通MAU
#define     TYPE_MAU_H263PLUS               (u8)1   //为H263plus定制的MAU
#define     TYPE_MPU                        (u8)2   //MPU

//MAU适配宏定义
#define		MAXNUM_VOUTPUT 					(u8)2   // 一路高清适配最大输出路数
#define		MAXNUM_MAU_VCHN				    (u8)1   // 一个MAU最大主流适配通道数
#define		MAXNUM_MAU_DVCHN				(u8)1   // 一个MAU最大双流适配通道数

//MPU适配宏定义
#define     MAXNUM_MPU_VCHN                 (u8)4   // 一个MPU最大适配通道数, 不区分主流双流

//高清适配通道宏定义
#define     HDBAS_CHNTYPE_MAU_MV            (u8)0
#define     HDBAS_CHNTYPE_MAU_DS            (u8)1
#define     HDBAS_CHNTYPE_MPU               (u8)2


#define MAXNUM_CONF_MVCHN                   (u8)3       //会议最到主流适配通道数
#define MAXNUM_CONF_DSCHN                   (u8)3       //会议最大双流适配通道数
    
#define MAXNUM_CONF_DUALMVCHN               (u8)1
#define MAXNUM_CONF_DUALDSCHN               (u8)2

#define MAXNUM_CONF_MAU                     (u8)4       //会议最大MAU数
#define MAXNUM_CONF_MPU                     (u8)MAXNUM_MPU_CHN       //会议最大MPU通道数

#define MAU_CHN_NONE                        (u8)0
#define MAU_CHN_NORMAL                      (u8)1       //HDBAS/MAU 通用适配通道
#define MAU_CHN_VGA                         (u8)2       //HDBAS/MAU 作VGA适配的通道
#define MAU_CHN_263TO264                    (u8)3       //HDBAS/MAU 作263到264适配的通道
#define MAU_CHN_264TO263                    (u8)4       //HDBAS/MAU 作264到263适配的通道
#define MPU_CHN_NORMAL                      (u8)5       //HDBAS/MPU 通用适配通道，通用性强过MAU_CHN_NORMAL

#define MAXNUM_MPU_CHN                      (u8)4


// 最大即时会议数(实测能力)
#ifdef _VXWORKS_
    #ifdef _MINIMCU_
    #define     MAXNUM_ONGO_CONF            32   
    #define     MAXNUM_ONGO_VCSCONF         16 // 允许同时召开的VCS会议数   
    #else
    #define     MAXNUM_ONGO_CONF            32  //mtadp 和 mp 都不内置时
    #define     MAXNUM_ONGO_VCSCONF         16 // 允许同时召开的VCS会议数 
    #endif 
#elif defined(_LINUX_)
    #ifdef _MINIMCU_
    #define     MAXNUM_ONGO_CONF            32 // 16个绝对没问题，无论是否启动其他业务
    #define     MAXNUM_ONGO_VCSCONF         16 // 允许同时召开的VCS会议数 
    #else    
    #define     MAXNUM_ONGO_CONF            32  //测试值36(共128M,MCU启动占18M,预留20M)
    #define     MAXNUM_ONGO_VCSCONF         16 // 允许同时召开的VCS会议数 
    #endif
#else   // WIN32
#define     MAXNUM_ONGO_CONF                32
#define     MAXNUM_ONGO_VCSCONF             16 // 允许同时召开的VCS会议数 
#endif

// 会议最大码率, 8000/8000B: 8M, 8000C: 4M
#ifdef _MINIMCU_
    #ifndef _MCU8000C_
        #define MAX_CONFBITRATE             8128
    #else
        #define MAX_CONFBITRATE             4096
    #endif
#else
    #define MAX_CONFBITRATE                 8128
#endif

#define     MAXNUM_VIEWINCONF				5    //每个会议的最大视图数
#define     MAXNUM_GEOINVIEW				5    //每个视图的最大几何布局数
#define		MAXNUM_SUBFRAMEINGEO            16   //每个几何布局的最大成员数
#define     MAXNUM_VSCHEMEINVIEW			4    //每个视图里的视频方案数
#define     MAXNUM_MIXERINCONF              16   //每个会议中的最大混音数  
#define     MAXNUM_ADDMT                    10   //一次增加的最大MT数   

#define     MAXNUM_NPLUS_MCU                16
 
//定义会议(模板)的confidx为会议map数组索引+1
#define MIN_CONFIDX                         1
#define MAX_CONFIDX                         (MAXNUM_MCU_CONF+MAXNUM_MCU_TEMPLATE)

//最大支持单板个数  
#define     MAXNUM_HDUBRD                   28   // 最大Hdu板子数目   4.6   jlb
#define     MAXNUM_OTHERBRD                 64   // 最大单板上的数目
#define     MAXNUM_BOARD       (MAXNUM_HDUBRD + MAXNUM_OTHERBRD)   // 64 + 28(hdu)
//同一种外设最大个数
#define     MAXNUM_PERIEQP                  16   //除了HDU
#define     MAXNUM_PERIHDU                  28   //4个tvs,每个7块HDU 
#define		MAXNUM_PERIDVMP					8	 //8个mpu-dvmp // xliang [12/10/2008] 	
#define		MAXLEN_EQP_ALIAS                16   //外设别名最大长度

//最大单板层号、槽号
#define     MAXNUM_LAYER                    4   //层号
#define     MAXNUM_SLOT                     14  //槽号  
#define     MAXNUM_TVSSLOT                  7   // TVS的槽位  jlb 4.6 
#define     MAXLEN_SLOT_ALIAS               16  //槽号最大长度

 // 非法的MapId
#define INVALID_MAP_ID	        		    (u8)255        

//槽类型
#define     SLOTTYPE_MC                     1   
#define     SLOTTYPE_EX                     2
#define     SLOTTYPE_TVSEX                    3 //TVS的槽类型 4.6 jlb 

#define     LEN_DES                         8	 //byte
#define     LEN_AES                         16	 //byte

//地址簿常量定义(参考地址簿头文件)
#define     MAXLEN_ADDR_ENTRYNAME           64  //改为64
#define     MAXLEN_ADDR_323ALIAS            32
#define     MAXLEN_ADDR_E164NUM             16
#define     MAXLEN_ADDR_320ID               48

#define     MAXNUM_ADDRGROUP                64
#define     MAXNUM_ADDRENTRY                1024

//级联相关常量定义
#define     MAXNUM_SUB_MCU                  56   //最大下级MCU个数
//#define     MASTER_MC_ID                    193  //主MC的ID号
#define		MAXNUM_ACCOMMODATE_SPY			(u16)512	 //MMCU最大允许容纳SMCU的spy数

#define		MCU_Q931_PORT					1720	//缺省Q931端口号
#define		MCU_RAS_PORT					1719	//缺省RAS端口号
#define		MCU_LISTEN_PORT					60000	//缺省外设/会控TCP侦听端口号(TCP,OSP)
#define		MCU_H225245_STARTPORT	        60002	//缺省MCU与MT建链的起始端口号(TCP) -- 60386(2*192)
//#define		MCU_RCVH224_PORT				2330	//接收终端H224数据端口号


//日志级别定义
#define     LOGLVL_EXCEPTION				0	//异常
#define     LOGLVL_IMPORTANT				1	//重要日志
#define     LOGLVL_DEBUG1					254 //一级调试信息
#define     LOGLVL_DEBUG2					255 //二级调试信息

//所有业务APP号定义（按照kdvdef.h中范围进行统一定义）
#define     AID_MCONSOLE					AID_MCU_BGN	        //会议控制台
#define     AID_MCU_AGENT					AID_MCU_BGN + 5 	//MCU代理
#define     AID_MCU_BRDMGR					AID_MCU_BGN + 6 	//单板管理
#define		AID_MCU_BRDAGENT				AID_MCU_BGN + 7 	//单板代理
#define		AID_MCU_BRDGUARD				AID_MCU_BGN + 8	    //单板守卫
#define     AID_MCU_MTADP					AID_MCU_BGN + 9	    //MTADP
#define     AID_VMPTW                       AID_MCU_BGN + 10    //多画面复合电视墙
#define     AID_MIXER						AID_MCU_BGN + 11	//混音器
#define     AID_TVWALL						AID_MCU_BGN + 12	//电视墙
#define     AID_RECORDER					AID_MCU_BGN + 13	//录像机
#define     AID_DCS							AID_MCU_BGN + 14	//数据会议服务器
#define     AID_BAS							AID_MCU_BGN + 15	//码率适配服务器
#define     AID_MP							AID_MCU_BGN + 16	//MP
#define	    AID_VMP							AID_MCU_BGN + 17	//画面合成器
#define     AID_PRS							AID_MCU_BGN + 18    //包重发
#define		AID_PRS_GUARD					AID_MCU_BGN + 19	//prs守卫
#define     AID_HDU                         AID_MCU_BGN + 20    //HDU
#define		AID_MPU							AID_MCU_BGN + 21	//MPU
#define     AID_MCU_VC				        AID_MCU_BGN + 22    //MCU业务
#define     AID_MCU_GUARD					AID_MCU_BGN + 23	//MCU守卫
#define     AID_MCU_MCSSN					AID_MCU_BGN + 24	//MCU会议控制台会话
#define     AID_MCU_CONFIG					AID_MCU_BGN + 25	//MCU配置会话
#define     AID_MCU_MTADPSSN				AID_MCU_BGN + 26	//MCU的MTADP会话
#define     AID_MCU_PERIEQPSSN				AID_MCU_BGN + 27	//MCU外设会话
#define     AID_MCU_MPSSN					AID_MCU_BGN + 28	//MCU的MP会话
#define		AID_MCU_DCSSSN					AID_MCU_BGN + 29	//MCU的DCS会话
#define     AID_MCU_MSMANAGERSSN			AID_MCU_BGN + 30	//热备份会话模块
#define     AID_MCU_NPLUSMANAGER            AID_MCU_BGN + 31    //N+1备份管理模块
#define     AID_MCU_VCSSN					AID_MCU_BGN + 32	//VCS会议控制台会话

#define     AID_MCU_MTSSN                   AID_MCU_BGN + 33    //卫星平台协议适配会话
#define     AID_MCU_MODEMSSN                AID_MCU_BGN + 34    //卫星平台Modem会话
#define     AID_UDPDISPATCH                 AID_MCU_BGN + 35    //卫星平台终端信息的udp会话
#define     AID_UDPNMS                      22//AID_MCU_BGN + 36    //卫星平台NMS交互的udp会话


//CPPUNIT测试所需
#define     AID_TEST_MCAGT					AID_MCU_BGN + 40	//MC集成测试
#define     AID_UNIT_TEST_MCAGT				AID_MCU_BGN + 41	//MC单元测试
#define     AID_TEST_MTCAGT					AID_MCU_BGN + 42	//MTC集成测试
#define     AID_UNIT_TEST_MTCAGT			AID_MCU_BGN + 43	//MTC单元测试
#define     AID_TEST_NMCAGT					AID_MCU_BGN + 44	//NMC
#define     AID_UNIT_TEST_MCUAGT			AID_MCU_BGN + 45	//MCU单元测试
#define     AID_UNIT_TEST_MTAGT				AID_MCU_BGN + 46	//MT单元测试
#define     AID_UNIT_TEST_SIMUMT            AID_MCU_BGN + 47
#define     AID_HDUAUTO_TEST                AID_MCU_BGN + 48    //hdu自动检测

// 各个重要应用的优先级定义(特别是同一板上运行多个)
#define     APPPRI_MIXER                    80
#define     APPPRI_BAS                      80
#define     APPPRI_PRS                      80
#define     APPPRI_TVWALL                   80
#define     APPPRI_VMP                      80
#define     APPPRI_MPW                      80
#define     APPPRI_REC                      80
#define     APPPRI_HDU                      80
#define		APPPRI_MPU						80	
 
#define     APPPRI_HDUAUTO                  80   // HDU自动检测优先级

#define     APPPRI_PRS_GUARD	            75

#define     APPPRI_MTADP                    80
#define     APPPRI_MP                       90

#define     APPPRI_BRDGUARD                 90
#define     APPPRI_BRDAGENT                 100

#define     APPPRI_MCUGUARD                 75
#define     APPPRI_MCUVC                    80
#define     APPPRI_MCUMSMGR                 80
#define     APPPRI_MCUAGT                   80
#define     APPPRI_MSCONFIG                 80
#define     APPPRI_MCUSSN                   90
#define     APPPRI_MCUCONFIG                90
#define     APPPRI_MCUBRDGUARD              90
#define     APPPRI_MCUBRDMANAGER            100
#define     APPPRI_MCUNPLUS                 80

//MCU E1硬件配置
#define      MAXNUM_MCU_DTI					32  //MCU最大DTI数目
#define      MAXNUM_MCU_E1_PER_DTI			8	//每个DTI下最大E1数
#define      MAXNUM_MCU_MT64K				128 //MCU连接MT最大时隙数:8M
#define      MAXNUM_MCU_SMCU64K				512 //连接下级MCU最多时隙数:4*8M
 
//外设常量定义
#define		MAXNUM_BASGRP					5   //适配器最大组数，不包含RTP头组
#define     MAXNUM_PRS_CHNNL				16	//包重发的最大个数
#define     MAXNUM_BAS_CHNNL				32  //码流适配器最大通道数 
#define     MAXNUM_MIXER_GROUP				5	//混音器组最大数
#define     MAXNUM_MIXER_GRPCHNNL			192 //混音器组成员最大数
#define     MAXPORTSPAN_MIXER_GROUP			570 //混音器组单组端口范围(应保障>=单组最大通道数*PORTSPAN)
#define     MIXER_INVALID_GRPID				255 //无效混音组号
#define     MIXER_INVALID_CHNNLID			255 //无效混音信道号
#define     MAXNUM_RECORDER_CHNNL			32	//录像机最大通道个数(含录像和放像通道)
#define     MAX_VOD_FILES_LEN				1024//VOD文件名列表最大长度
#define     MAX_VOD_FNAME_LEN				155	//VOD文件名最大长度，和数据库一致
#define     MAX_VODFILEPATH_LEN				100	//VOD文件目录最大长度，和数据库一致
#define     MAXLEN_RECORD_NAME              64  //上报外设状态时录像文件名的长度
#define     DEFAULT_MIXER_VOLUME			250	//缺省的混音音量
#define		MAXNUM_MAP						5	//单板最大map数
#define		MAXLEN_TRAP_COMMUNITY			33	//trap community 最大长度(有效位32)
#define		MAXNUM_TRAP_LIST				16	//trap表最大长度
#define		MAXNUM_HDU_CHANNEL              2   //一个HDU的最大通道数
//最大HDU可配置通道数通道数   jlb
#define     MAXNUM_HDUCFG_CHNLNUM           56  //最大界面中HDU可配置通道数

// HDU预方案别名最大长度    jlb
#define		MAX_HDUSTYLE_ALIASLEN           32

//Mcu的DCS容量定义
#define		MAXNUM_MCU_DCS					1	//MCU集成DCS的能力, 目前只支持一个

//单板最多配置外设个数
#define		MAXNUM_BRD_EQP					5
#define		MAXNUM_HDUBRD_EQP					1


//每个map最大混音通道数
#ifdef _MINIMCU_
#define     MAXNUM_MIXER_CHNNL              32
#else
#define     MAXNUM_MIXER_CHNNL              MAXNUM_MIXING_MEMBER
#endif
//卫星分散会议中最大定制混音个数
#define     MAXNUM_MIXERCHNNL_SATDCONF      4
//默认重传检测点时间
#define     DEF_FIRSTTIMESPAN_PRS           40
#define     DEF_SECONDTIMESPAN_PRS          120
#define     DEF_THIRDTIMESPAN_PRS           240
#define     DEF_LOSETIMESPAN_PRS            480
//默认trap端口
#define     DEF_READWRITE_TRAPPORT          161
#define     DEF_SEND_TRAPPORT               162
//默认终端断链检测时间和次数
#define     DEF_DISCCHECKTIME               10
#define     DEF_DISCCHECKTIMES              3
//终端最小断链检测时间和次数
#define     MIN_DISCCHECKTIME               5   //5s 
#define     MIN_DISCCHECKTIMES              1   //1次
//级联时终端列表刷新时间间隔
#define     PARTLIST_REFRESHTIME            (u16)600 //(单位：秒)
//级联时音频信息请求时间间隔
#define     AUDINFO_REFRESHTIME             (u16)600
//级联时视频信息请求时间间隔
#define     VIDINFO_REFRESHTIME             (u16)600
//级联信息请求的最大时间间隔(12hour)
#define     CASCADEINFO_MAX_REFRESHTIME     (u16)43200
//级联信息请求的最小时间间隔(30s)
#define     CASCADEINFO_MIN_REFRESHTIME     (u16)30

// 主备倒换正常性定时同步时间间隔 300″
#define MS_SYN_MAX_SPAN_TIMEOUT             (u32)300

// 单板代理osp断链检测默认心跳周期
#define     DEF_OSPDISC_HBTIME              (u16)10
// 单板代理osp断链检测默认心跳次数
#define     DEF_OSPDISC_HBNUM               (u8)3

//N+1备份RTD默认心跳周期
#define     DEF_NPLUSRTD_TIME               5

//N+1备份RTD默认心跳次数
#define     DEF_NPLUSRTD_NUM                3

//Qos type
#define     QOSTYPE_DIFFERENCE_SERVICE      1   //区分服务
#define     QOSTYPE_IP_PRIORITY             2   //ip优先
//qos 等级
#define     QOS_IP_MAXLEVEL                 7   //ip 优先服务等级（0－7）
#define     QOS_DIFF_MAXLEVEL               63  //区分服务等级（0－63）
//ip 服务类型
#define     IPSERVICETYPE_NONE              0   //全都不选
#define     IPSERVICETYPE_LOW_DELAY         1   //最小延迟
#define     IPSERVICETYPE_HIGH_THROUGHPUT   2   //最高吞吐量
#define     IPSERVICETYPE_HIGH_RELIABILITY  4   //最高可靠性
#define     IPSERVICETYPE_LOW_EXPENSE       8   //最低费用

//单板查询主备状态超时时间
#define     WAITING_MSSTATUS_TIMEOUT        (8*1000) // guzh [9/12/2006] 修改为8s

//画面合成风格默认RGB值
#define     VMPSTYLE_DEFCOLOR               (u32)(246|(246<<8)|(246<<16))// r|(g<<8)|(b<<16)
//画面合成最大方案个数
#define     MAX_VMPSTYLE_NUM                5
//HDU预案最大方案个数
#define   MAX_HDUSTYLE_NUM                  16
// 画面合成方案别名最大长度
#define  MAX_VMPSTYLE_ALIASLEN              32   
// 画面合成主题参数
// 字体
#define FONT_HEI    (u8)01 // 黑体
#define FONT_SONG   (u8)02 // 宋体 (默认)
#define FONT_KAI    (u8)03 // 楷体
// 字号
#define FONT_SIZE_24  24	// 24*24 (默认)
#define FONT_SIZE_32  32	// 32*32
// 对齐方式
#define LEFT_ALIGN    (u8)1  // 左
#define MIDDLE_ALIGN  (u8)2  // 中
#define RIGHT_ALIGN   (u8)3  // 右

// 画面合成主题默认文字颜色
#define DEFAULT_TEXT_COLOR  (u32)(44|(94<<8)|(180<<16))  // blue
// 画面合成主题默认背景色
#define DEFAULT_BACKGROUND_COLOR (u32)(255|(255<<8)|(255<<16)) // white
// 画面合成主题默认透明度
#define DEFAULT_DIAPHANEITY   0 // 
// 画面合成主题默认文本长度
#define DEFAULT_TEXT_LEN     (u8)32 
 // 画面合成主题默认高度
#define wDEFAULT_BMP_HEIGHT  (u16)50 
// BMP文件缓冲大小
#define  MAX_BMPFILE_SIZE   (u32)800*600  
// 最大BMP文件数据大小
#define  MAX_BMPDATA_BUFFER (u32)720*576  

// mcucfg.ini 配置文件的最大长度
#define    MAXLEN_MCUCFG_INI                8192
// mcuunproccfg.ini文件的最大长度
#define    MAXLEN_MCUUNPROCCFG_INI          8192

// 升级文件全路径名最大长度
#define	   MAXLEN_MCU_FILEPATH			128

//Read and save /conf file
#ifdef _VXWORKS_
#define DIR_CONFIG               ( LPCSTR )"/conf"
#define DIR_DATA                 ( LPCSTR )"/data"
#define DIR_FTP                  ( LPCSTR )"/ftp"
#define DIR_WEB                  ( LPCSTR )"/webfiles/doc"
#define DIR_LOG					 ( LPCSTR )"/log"
#endif

#ifdef _LINUX_
#ifdef _X86_  // Redhat
#define DIR_CONFIG               ( LPCSTR )"/usr/etc/conf"
#endif
#if defined(_PPC_) || defined(_ARM_)
#define DIR_CONFIG               ( LPCSTR )"/usr/etc/config/conf"	
#endif 

#define DIR_DATA                 ( LPCSTR )"/usr/etc/data"	
#define DIR_FTP                  ( LPCSTR )"/usr/ftp"	
#define DIR_WEB                  ( LPCSTR )"/usr/webroot"
#define DIR_LOG					 ( LPCSTR )"/usr/log"
#endif

#ifdef WIN32
#define DIR_CONFIG               ( LPCSTR )"./conf"	
#define DIR_DATA                 ( LPCSTR )"./data"	
#define DIR_FTP                  ( LPCSTR )"./ftp"	
#define DIR_WEB                  ( LPCSTR )"./webfiles/doc"	
#define DIR_LOG					 ( LPCSTR )"./log"
#endif

#define DIR_EXCLOG               ( LPCSTR )"/usr/log/exc.log"

#define FILE_BRDCFG_INI          ( LPCSTR )"brdcfg.ini"
#define FILE_BRDCFGDEBUG_INI     ( LPCSTR )"brdcfgdebug.ini"    //4.6  jlb
#define MCUCFGFILENAME           ( LPCSTR )"mcucfg.ini"
#define MCUDEBUGFILENAME         ( LPCSTR )"mcudebug.ini"
#define MCUCFGBAKFILENAME		 ( LPCSTR )"mcucfg.bak"
#define MCU_VCSUSER_FILENAME     ( LPCSTR )"vcslogin.usr"
#define MCUUNPROCCFGFILENAME     ( LPCSTR )"mcuunproccfg.ini" 
#define MCU_SAT_CFGFILENAME      ( LPCSTR )"mcusatcfg.ini"        

//linux下版本更新打包文件后缀
#define LINUXAPP_POSTFIX         ( LPCSTR )"image"
#define LINUXAPP_POSTFIX_BIN     ( LPCSTR )"bin"
//linux下版本OS文件后缀
#define LINUXOS_POSTFIX          ( LPCSTR )"linux"

// License控制
#define KEY_FILENAME                  "kedalicense.key"

//#define KEDA_AES_KEY				  "kedacom200606231"
//#define KEDA_COPYRIGHT			      "Suzhou Keda Technology Co.,ltd. Tel:86-512-68418188, Fax: 86-512-68412699, http://www.kedacom.com"

// 加密内容的长度
//#define LEN_KEYFILE_CONT              (u16)512

//MCU配置信息级别, zgc, 2007-03-16
#define		MCUCFGINFO_LEVEL_NEWEST			0	//当前最新的配置文件信息
#define		MCUCFGINFO_LEVEL_LAST			1	//最近一次成功读取的配置文件信息
#define		MCUCFGINFO_LEVEL_DEFAULT		2	//默认配置信息
#define		MCUCFGINFO_LEVEL_PARTNEWEST		3	//只有部分是最新的配置文件信息，
												//即有部分被修改为默认或最近一次成功读取的配置信息

#define     MAX_FILESTREAM_NUM                  3   //媒体文件最大媒体流数, zgc, 2008-08-02

//网同步类型
#define     NETSYNTYPE_VIBRATION            1   //自由振荡
#define     NETSYNTYPE_TRACE                2   //跟踪
#define     NETSYN_MAX_DTNUM                14  //最大DT板号
#define     NETSYN_MAX_E1NUM                7   //最大E1号

//会议常量定义 
#define     MAXNUM_MC_CHANNL   				16	//会议控制台最大通道数
#define     MAXNUM_MT_CHANNL   				16	//终端监控最大通道数

#define     EQP_CHANNO_INVALID              0xFF //无效外设通道号

//码流适配类型定义
#define     ADAPT_TYPE_NONE                 0   //不需码流适配
#define     ADAPT_TYPE_AUD                  1   //音频类型适配
#define     ADAPT_TYPE_VID                  2   //视频类型适配
#define     ADAPT_TYPE_BR                   3   //码率适配
#define     ADAPT_TYPE_CASDAUD              4   //音频类型适配
#define     ADAPT_TYPE_CASDVID              5   //视频类型适配

//码流适配通道类型定义
#define     BAS_CHAN_AUDIO                  1   //音频适配通道
#define     BAS_CHAN_VIDEO                  2   //视频适配通道

//cppunit测试结果
#define		CPPTEST_OK						0	//成功

//发言人码流源设置渠道, zgc, 2008-04-14
#define		SPEAKER_SRC_NOTSEL				(u8)0		// 发言人非选看
#define		SPEAKER_SRC_MCSDRAGSEL			(u8)1		// 会控拖拉选看
#define		SPEAKER_SRC_CONFSEL				(u8)2		// 会议内部逻辑选看

enum emChangeSpeakerSrcReason
{
	emReasonUnkown = 0,
	emReasonChangeSpeaker,
	emReasonChangeChairman,
	emReasonChangeBrdSrc
};


//摄像头控制参数定义
#define     CAMERA_CTRL_UP					1   //上
#define     CAMERA_CTRL_DOWN				2   //下
#define     CAMERA_CTRL_LEFT				3   //左
#define     CAMERA_CTRL_RIGHT				4   //右
#define     CAMERA_CTRL_UPLEFT				5   //上左
#define     CAMERA_CTRL_UPRIGHT				6   //上右
#define     CAMERA_CTRL_DOWNLEFT			7   //下左
#define     CAMERA_CTRL_DOWNRIGHT			8   //下右
#define     CAMERA_CTRL_ZOOMIN				9   //视野小
#define     CAMERA_CTRL_ZOOMOUT				10  //视野大
#define     CAMERA_CTRL_FOCUSIN				11  //调焦短
#define     CAMERA_CTRL_FOCUSOUT			12  //调焦长
#define     CAMERA_CTRL_BRIGHTUP			13  //亮度加
#define     CAMERA_CTRL_BRIGHTDOWN			14  //亮度减
#define     CAMERA_CTRL_AUTOFOCUS			15  //自动调焦

// 视频源个数
#define      MAX_OUTPUTNUM					7
#define      MATRIX_MAXPORT					16	

// 使能视频源输出
#define      VIDEO_OUTPUT_CLOSE				0xfb
#define      VIDEO_OUTPUT_OPEN				0xfc

//MP 相关常量
#ifdef _MINIMCU_
#define      MAX_SWITCH_CHANNEL				500
#else
#define      MAX_SWITCH_CHANNEL				500
#endif
#define      MAX_IP_NUM						2

//交换方式
// guzh [2/13/2007] 说明：关于交换方式在4.0R3以前主要用于两点
// 一是 H.320 区分码流类型
// 二是 业务区分交换码流时是否要建桥，如果是 SWITCH_MODE_SELECT 则不作建桥
// 
// R4优化后，第一点作用保留
// 第二点由于目前逻辑始终对终端跨MP交换建桥，所以本字段不再有意义
// 对于外设转发来说，则依旧保留跨MP交换建桥的逻辑
// 同时增加改为标识通知MP的交换消息类型（意义完全改变）
// MP根据本类型来决定是通过内部中转节点（每个会议音视频各一路中转）转发还是直接转发码流
#define      SWITCH_MODE_NONE               0   //无效的选看方式
#define      SWITCH_MODE_BROADCAST			1	//广播交换方式
#define      SWITCH_MODE_SELECT				2	//选看交换方式


//缺省呼叫端口
#define      DEFAULT_Q931_PORT				MCU_Q931_PORT

//消息长度相关
#define      SERV_MSG_LEN					0x7000  //消息长度
#define      SERV_MSGHEAD_LEN				0x30    //消息头长度


//视频矩阵类型
#define      MATRIXTYPE_INNER				1	//内部视频矩阵
#define      MATRIXTYPE_VAS					2	//VAS板
#define      MATRIXTYPE_EXTRON				3	//Extron视频交换矩阵

#define      MATRIXPORT_IN					1	//输入端口
#define      MATRIXPORT_OUT					2	//输出端口

#define      MATRIXPORT_SVIDEO				0	//S端子
#define      MATRIXPORT_ENCODER				1	//编码器端口
#define      MATRIXPORT_DECODER				1	//解码器端口

#define      PRSCHANMODE_FIRST              1   //第一视频通道
#define      PRSCHANMODE_SECOND             2   //第二视频通道
#define		 PRSCHANMODE_BOTH               3   //两个视频通道
#define      PRSCHANMODE_AUDIO              4   //音频通道
#define      PRSCHANMODE_AUDBAS             5   //需适配的音频重传通道
#define      PRSCHANMODE_VIDBAS             6   //需媒体适配的视频重传通道
#define      PRSCHANMODE_BRBAS              7   //需码率适配的视频重传通道
#define      PRSCHANMODE_VMP2               8   //VMP第二路码流的丢包重传通道

// 增加高清PRS通道, zgc, 2008-08-13
#define      PRSCHANMODE_HDBAS_VID          9   //高清BAS主视频的丢包重传通道
#define      PRSCHANMODE_HDBAS_DVID         10  //高清BAS双流的丢包重传通道

// xliang [4/30/2009]  多路输出类的广播源(如MPU) PRS通道
#define      PRSCHANMODE_VMPOUT1			11	//1080出
#define      PRSCHANMODE_VMPOUT2				12  //720出
#define		 PRSCHANMODE_VMPOUT3			13	//4CIF
#define		 PRSCHANMODE_VMPOUT4		14	//CIF/other

#define      AP_MIN                         96  //动态载荷最小值
#define      AP_MAX                         126 //动态载荷最小值

/*定义MPC的单板槽位号*/
#define		 MCU_BOARD_MPC					16
#define      MCU_BOARD_MPCD                 8

#define      BOARD_INLINE                   (u8)1     // 单板在线
#define      BOARD_OUTLINE                  (u8)2     // 单板不在线
#define      BOARD_UNKNOW                   (u8)3     // 单板未知
#define      BOARD_CFGCONFLICT              (u8)4     // 单板配置冲突(暂时未使用)

//单板类型定义
#define		BRD_TYPE_MPC					0
#define		BRD_TYPE_DTI					1
#define		BRD_TYPE_DIC					2
#define		BRD_TYPE_CRI					3
#define		BRD_TYPE_VAS					4
#define		BRD_TYPE_MMP					5
#define		BRD_TYPE_DRI					6
#define		BRD_TYPE_IMT					7
#define		BRD_TYPE_APU					8
#define		BRD_TYPE_DSI					9
#define		BRD_TYPE_VPU					10
#define		BRD_TYPE_DEC5					11
#define     BRD_TYPE_DSC                    13
#define     BRD_TYPE_MDSC                   0x10
#define     BRD_TYPE_16E1                   0x11
#define     BRD_TYPE_HDSC                   0x14
//4.6版本新增板类型 jlb
#define     BRD_TYPE_HDU                    0x15
#define     BRD_TYPE_MPU                    0x16
#define     BRD_TYPE_EBAP                   0x17
#define     BRD_TYPE_EVPU                   0x18
#define		BRD_TYPE_UNKNOW					0xff

//单板商用名定义
// DRI 可以作为: DRI / TUI
// VPU 可以作为: VPU / BAP
// CRI 可以作为: CRI / PRS / TUI / HDI
#define     BRD_ALIAS_MPC                   "MPC"
#define     BRD_ALIAS_CRI                   "CRI"
#define     BRD_ALIAS_DRI                   "DRI"
#define     BRD_ALIAS_APU                   "APU"
#define     BRD_ALIAS_VPU                   "VPU"
#define     BRD_ALIAS_DEC5                  "DEC5"
#define     BRD_ALIAS_DSC                   "DSC"
#define     BRD_ALIAS_MDSC                  "MDSC"
#define     BRD_ALIAS_HDSC                  "HDSC"
#define     BRD_ALIAS_TUI                   "TUI"
#define     BRD_ALIAS_HDI                   "HDI"
#define     BRD_ALIAS_PRS                   "PRS"
#define     BRD_ALIAS_BAP                   "BAP"
#define     BRD_ALIAS_MMP                   "MMP"
//4.6版本新增板子商用名定义 jlb
#define     BRD_ALIAS_MPU                   "MPU"
#define     BRD_ALIAS_HDU                   "HDU"
#define     BRD_ALIAS_EBAP                  "EBAP"
#define     BRD_ALIAS_EVPU                  "EVPU"

#define     MAXLEN_BRDALIAS                 8   // 有效长度7

#define      DISABLE						0	//无效
#define      ENABLE							1	//有效

#define		ISTRUE(b)						((b)!=0) 
#define		GETBBYTE(b)						((b)?1:0)
#define		kmax(a,b)						(((a) > (b)) ? (a) : (b))
#define		kmin(a,b)						(((a) < (b)) ? (a) : (b))
#define		astrncpy(a, b, al, bl)  { s32 l = min(al, bl); strncpy((s8 *)a, b, l); a[l-1] = 0;}

#define		arraynum(a)						(sizeof(a)/sizeof(a[0]))

enum emDisconnectReason
{
	emDisconnectReasonDRQ = 1,      // DRQ from GK
	emDisconnectReasonRtd,          // roundtripdelay timeout
	emDisconnectReasonBusy,
	emDisconnectReasonNormal,
	emDisconnectReasonRejected,
	emDisconnectReasonUnreachable,
	emDisconnectReasonLocal,
    emDisconnectReasonUnmatched,    // 本原因基于业务定义，与协议栈无关。不适配。
	emDisconnectReasonUnknown,
	emDisconnectReasonBysyExt
};

#define  ADDMTMODE_MCS                  1   //终端是被MCS邀请的
#define  ADDMTMODE_CHAIRMAN             2   //终端是被主席邀请的
//#define  ADDMTMODE_MTSELF               3   //终端是自己加入的

#define  MIXERID_MIN                    1
#define  MIXERID_MAX                    16
#define  RECORDERID_MIN                 17
#define  RECORDERID_MAX                 32
#define  TVWALLID_MIN                   33
#define  TVWALLID_MAX                   48
#define  BASID_MIN                      49
#define  BASID_MAX                      64
#define  VMPID_MIN                      65
#define  VMPID_MAX                      80
#define  VMPTWID_MIN                    81
#define  VMPTWID_MAX                    96
#define  PRSID_MIN                      97
#define  PRSID_MAX                      112
#define  HDUID_MIN                      113
#define  HDUID_MAX                      140

#define  DEFAULT_PRS_CHANNELS           (u8)3       // 默认需要的Prs通道数
#define  MAX_TIMES_CREATE_CONF			(u8)5       // 最大尝试创会次数
#define  LEN_WAIT_TIME					(u32)5000   // 等待时间步长
#define  MAXNUM_CHECK_CAS_TIMES         (u8)3

#define  PORTSPAN                       (u16)10     // 端口的间隔

//UDP 端口分配，使用范围：30000--65500

#define CASCADE_SPY_STARTPORT			(u16)30000	// 30000～37000 上级接纳回传源端口：10 * 512 = 5120; 空闲 1880 
#define CASCADE_BRD_STARTPORT			(u16)38000	// 37000～39000	下级接纳上级广播端口：10 * 128 = 1280; 空闲 720

//外设mcu侧默认起始端口 (VMP)
#define VMP_MCU_STARTPORT               (u16)39000  // 39000～40000 分配给VMP: 30  * 16 = 480;    空闲端口: 520

//外设默认起始端口
//外设BAS/VMP/MIX/PRS会运行在MCU8000B上，故不能和主机侧端口冲突
#define MIXER_EQP_STARTPORT             (u16)40000  // 40000～40600 分配给一个MIX: 空闲端口: 30
#define BAS_EQP_STARTPORT               (u16)40600  // 40600～40700 分配给一个BAS: 空闲端口: 50
#define VMP_EQP_STARTPORT               (u16)40700  // 40700～40900 分配给一个VMP: 空闲端口: 40
#define PRS_EQP_STARTPORT               (u16)40900  // 40900～41000 分配给一个PRS: 空闲端口: 40
#define TVWALL_EQP_STARTPORT            (u16)41000  // 41000～41500 分配给一个TW:  空闲端口: xxx
#define MTW_EQP_STARTPORT               (u16)41500  // 不考虑和MCU侧的其他起始端口冲突
#define HDU_EQP_STARTPORT				(u16)42000	// 42000～42100 分配给一个HDU: 空闲端口: 80
#define REC_EQP_STARTPORT               (u16)7200   // 考虑到穿防火墙情况（在录像机侧配置）

//外设mcu侧默认起始端口
#define REC_MCU_STARTPORT               (u16)41500  // 41500～46700 分配给REC: 320 * 16 = 5120;   空闲端口: 80
#define BAS_MCU_STARTPORT               (u16)46700  // 46700～48000 分配给BAS: 80  * 16 = 1280;    空闲端口: 20
// xliang [12/22/2008]  vmp移至前面
// 48000～53000 为防火墙代理占用端口(运行在xDSC上，不能与PRS/MT接入端口冲突);
#define MIXER_MCU_STARTPORT             (u16)50000  // 50000～58000 分配给MIX: 570 * 14 = 8980;   空闲端口: 20
#define PRS_MCU_STARTPORT               (u16)58000  // 58000～59000 分配给PRS: 60  * 16 = 960;    空闲端口: 40
#define RESV_MCU_STARTPORT              (u16)59000  // 59000～61000 为MCU内部广播默认端口: 10 * 128 = 1280;   空闲端口: 720
													// 61000～65530 分配给终端: 10 * 448 = 4480;  空闲端口: 50
//终端mcu侧默认起始端口
#define MT_MCU_STARTPORT                (u16)61000
//#define MT_MCU_STARTPORT                (u16)21000

//外设mcu侧端口分配间隔
#define BAS_MCU_PORTSPAN               (u16)(8 * PORTSPAN)/*(5 * PORTSPAN)*/
#define VMP_MCU_PORTSPAN               (u16)(4 * PORTSPAN)/*(2 * PORTSPAN)*/
#define MPW_MCU_PORTSPAN               (u16)(2 * PORTSPAN)
#define PRS_MCU_PORTSPAN               (u16)(6 * PORTSPAN)   
#define MIXER_MCU_PORTSPAN             (u16)(57 * PORTSPAN)
#define REC_MCU_PORTSPAN               (u16)(32 * PORTSPAN)
#define HDU_MCU_PORTSPAN               (u16)(2 * PORTSPAN)

// 组播地址中起始/结束IP段
#define MULTICAST_IP_START              ntohl(inet_addr("225.0.0.0"))
#define MULTICAST_IP_END                ntohl(inet_addr("239.255.255.255"))
// 组播地址中需要保留的IP段
#define MULTICAST_IP_RESV_START         ntohl(inet_addr("231.255.255.255"))
#define MULTICAST_IP_RESV_END           ntohl(inet_addr("233.0.0.0"))
// 默认组播端口
#define MULTICAST_DEFPORT               (u16)60100

#define MAXBITRATE_MTSEND_INVMP         (u16)4032   //画面合成时终端最大发送码率(4096-64)

//单板telnet端口定义
#define BRD_TELNET_PORT                 2500

//mcu telnet 端口定义
#define MCU_TELNET_PORT                 2500

// 由于Linux在inet_addr时保护 "0"认为是错误地址，所以需要保护一下
// 建议所有Linux相关的地址转换使用本宏。
// 本宏要求字符串以\0结尾
#define INET_ADDR( szAddr )   ( strncmp(szAddr, "0", strlen(szAddr)) == 0 ? 0 : inet_addr(szAddr) )

//用户组扩展
#define MAXNUM_USRGRP                   32
#define MAXNUM_GRPUSRNUM                MAX_USERNUM
#define MAXNUM_IPSEG                    3

//最大用户个数
#define MAXNUM_USRNUM                   MAX_USERNUM

// 合法的组ID是 1 - MAXNUM_USRGRP，以及 USRGRPID_SADMIN
#define USRGRPID_INVALID                (u8)0
#define USRGRPID_SADMIN                 (u8)0xFF

//MCU所有应用OSP初始授权定义
#define MCU_TEL_USRNAME                 "admin"
#define MCU_TEL_PWD                     "admin"


//NPlus给Mcs定义的宏，为了错开其他值
#define NPLUS_NONE                      (u8)200    //非NPlus模式

#define NPLUS_BAKCLIENT_IDLE            (u8)201     //N端 - 空闲状态
#define NPLUS_BAKCLIENT_MSGLEN_ERR      (u8)202     //N端 - 连接备份端失败：消息体错误：显示为未知错误
#define NPLUS_BAKCLIENT_CAP_ERR         (u8)203     //N端 - 连接备份端失败：备份端能力集不支持
#define NPLUS_BAKCLIENT_OVERLOAD        (u8)204     //N端 - 连接备份端失败：备份端备份能力饱和
#define NPLUS_BAKCLIENT_ENV_UNMATCHED   (u8)205     //N端 - 连接备份端失败：备份端为8000B，不支持对本端KDV8000的备份; 或 备份端为8000C 或 本端为8000C 或 二者均为8000C，不能构成备份
#define NPLUS_BAKCLIENT_CONNECT_MASTER  (u8)206     //N端 - 连接备份端失败：备份端为主用MCU 或 非N+1模式的MCU
#define NPLUS_BAKCLIENT_CONNECT         (u8)210     //N端 - 已连接服务器

#define NPLUS_BAKSERVER_IDLE            (u8)211     //备份端 - 空闲状态
#define NPLUS_BAKSERVER_SWITCHED        (u8)212     //备份端 - 已切换
#define NPLUS_BAKSERVER_SWITCHERR       (u8)213     //备份端 - 切换失败

//8000B能力限制特殊处理 宏定义
#define MAXNUM_MIX_SINGLE_MP3           (u8)32      //MP3混音(定制和讨论)单开方数
#define MAXNUM_MIX_MULTI_MP3            (u8)8       //MP3混音(定制和讨论)和其他(VMP和BAS)混开方数
#define MAXNUM_MIX_SINGLE_G729          (u8)10      //G729混音(定制和讨论)单开方数
#define MAXNUM_MIX_MULTI_G729           (u8)4       //G729混音(定制和讨论)和其他(VMP和BAS)混开方数
#define MAXNUM_VAC_SINGLE_MP3           (u8)32      //MP3的VAC单开方数
#define MAXNUM_VAC_MULTI_MP3            (u8)16      //MP3的VAC和其他(BAS)混开方数
#define MAXNUM_VAC_SINGLE_G729          (u8)16      //G729的VAC单开方数
#define MAXNUM_VAC_MULTI_G729           (u8)4       //G729的VAC和其他(BAS)混开方数

//点名模式宏定义
#define ROLLCALL_MODE_NONE              (u8)0       //非点名状态
#define ROLLCALL_MODE_VMP               (u8)1       //VMP模式：点名人被点名人互看，其他人看它们的VMP
#define ROLLCALL_MODE_CALLER            (u8)2       //CALLER模式：点名人看被点名人，其他人看点名人
#define ROLLCALL_MODE_CALLEE            (u8)3       //CALLEE模式：被点名人看点名人，其他人看被点名人

//mcu与mcs会话版本，用户会控连接时验证，修改数据结构影响mcs与mcu交互时此值加1（45代表4.0R5版本，01代表每次修改版本）
#define MCUMCS_VER                      (u16)46005  //temperary

// zw [06/27/2008] AAC LC参数
#define AAC_SAMPLE_FRQ_8                (u8)1
#define AAC_SAMPLE_FRQ_11               (u8)2
#define AAC_SAMPLE_FRQ_12               (u8)3
#define AAC_SAMPLE_FRQ_16               (u8)4
#define AAC_SAMPLE_FRQ_22               (u8)5
#define AAC_SAMPLE_FRQ_24               (u8)6
#define AAC_SAMPLE_FRQ_32               (u8)7
#define AAC_SAMPLE_FRQ_44               (u8)8
#define AAC_SAMPLE_FRQ_48               (u8)9
#define AAC_SAMPLE_FRQ_64               (u8)10
#define AAC_SAMPLE_FRQ_88               (u8)11
#define AAC_SAMPLE_FRQ_96               (u8)12

#define AAC_CHNL_TYPE_CUST              (u8)11
#define AAC_CHNL_TYPE_SINGLE            (u8)1
#define AAC_CHNL_TYPE_DOUBLE            (u8)2
#define AAC_CHNL_TYPE_3                 (u8)3
#define AAC_CHNL_TYPE_4                 (u8)4
#define AAC_CHNL_TYPE_5                 (u8)5
#define AAC_CHNL_TYPE_5P1               (u8)51
#define AAC_CHNL_TYPE_7P1               (u8)71

#define AAC_MAX_FRM_NUM                 1


// xliang [11/28/2008] vmp通道数目 FIXME
#define MAX_SVMP_HDCHNNLNUM				(u8)3		//
#define MAX_SVMP_4CIFCHNNLNUM			(u8)16
#define MAX_SVMP_CIFCHNNLNUM			(u8)12

// xliang [11/28/2008] vmp 成员涉及优先级的属性 -暂不用
#define VMPMEMBER_NORMAL				(u8)1	//普通MT
#define VMPMEMBER_BESELECTED			(u8)2	//被选看
#define VMPMEMBER_NONEKEDA				(u8)3	//非科达
#define VMPMEMBER_SPEAKER				(u8)4	//发言人

// xliang [12/23/2008] vmp批量轮询时间T上下限
#define VMP_BATCHPOLL_TMAX				(u32)(300*1000)
#define VMP_BATCHPOLL_TMIN				(u32)(60*1000)

//4.6新加版本  jlb
//HDU 输出接口
#define HDU_OUTPUT_YPbPr   (u8)0    
#define HDU_OUTPUT_VGA     (u8)1 

#define HDU_VOLUME_DEFAULT (u8)24

//缩放比率
#define HDU_ZOOMRATE_4_3   (u8)0  
#define HDU_ZOOMRATE_16_9  (u8)1

//HDU 输出制式
#define HDU_YPbPr_1080P_24fps         (u8)0
#define HDU_YPbPr_1080P_25fps         (u8)1
#define HDU_YPbPr_1080P_30fps         (u8)2
#define HDU_YPbPr_1080P_50fps         (u8)3
#define HDU_YPbPr_1080P_60fps         (u8)4
#define HDU_YPbPr_1080i_50HZ          (u8)5    //(默认)
#define HDU_YPbPr_1080i_60HZ          (u8)6
#define HDU_YPbPr_720P_60fps          (u8)7
#define HDU_YPbPr_576i_50HZ           (u8)8
#define HDU_YPbPr_480i_60HZ           (u8)9

#define HDU_VGA_SXGA_60HZ            (u8)10
#define HDU_VGA_XGA_60HZ             (u8)11     //(默认)
#define HDU_VGA_XGA_75HZ             (u8)12
#define HDU_VGA_SVGA_60HZ            (u8)13
#define HDU_VGA_SVGA_75HZ            (u8)14
#define HDU_VGA_VGA_60HZ             (u8)15
#define HDU_VGA_VGA_75HZ             (u8)16
#define HDU_VGA_SXGA_75HZ            (u8)17


//组播建立方式
#define CAST_UNI					 (u8)1
#define CAST_FST				     (u8)2
#define CAST_SEC				     (u8)3
#define CAST_DST				     (u8)4

//VCS支持配置的最大用户数
#define MAXNUM_VCSUSERNUM               MAX_USERNUM

#define MAXNUM_SAT_MODEM			 (u8)16
#endif


