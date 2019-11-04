#ifndef _h_tpsys_h__
#define _h_tpsys_h__

#include "osp.h"
#include "kdvdef.h"
#include "eventid.h"
#include "tptype.h"

#define UMS_ProductID	"UMSTPS"
#define UMS_VerID		"1.1.3.0.0"


#define UMS_B1			1
#define UMS_B2			2
#define CNS_B1			3
#define CNS_B2			4


/* Traversal Server 模块(291 - 320) */
#define AID_TS_BGN				AID_RTSP_END + 1
#define AID_TS_END				AID_TS_BGN + 29


/* TP  (321-360)*/
#define AID_TP_BGN				AID_TS_END + 1
#define AID_TP_END				AID_TP_BGN + 59

#define AID_TP_PROTOCOL_BEGIN        AID_TP_END + 1
#define AID_TP_PROTOCOL_END        AID_TP_END + 39



//aid define
 //ums aid 
#define AID_UMSDB_APP				AID_TP_BGN + 1
#define AID_UMSSERVER_APP			AID_TP_BGN + 2
#define AID_UMSSIP_APP				AID_TP_BGN + 3
#define AID_UMSCONFMGR				AID_TP_BGN + 4
#define AID_UMSUE_APP				AID_TP_BGN + 6
#define AID_UMSMEDIADS_APP			AID_TP_BGN + 7
#define AID_UMSEQP_APP				AID_TP_BGN + 8

#define AID_UMSSIPADAPTER_APP		AID_TP_BGN + 9
#define AID_UMSAUDIOMIX_APP			AID_TP_BGN + 10
#define AID_UMSMEDIATRANS_APP		AID_TP_BGN + 11
#define AID_UMSNETBUF_APP			AID_TP_BGN + 12
#define AID_UMSMPC_APP				AID_TP_BGN + 13
#define AID_UMSAGENT_APP			AID_TP_BGN + 14
#define AID_UMSGUARD_APP			AID_TP_BGN + 15
#define AID_UMSAPU2PPOWERPROC_APP	AID_TP_BGN + 26 //apu2语音能量更新APP


#define AID_UMSBRD_SSN_APP		78	//78 mcu侧外设板子业务处理App  需要与MCU同步
#define AID_UMSBRD_REG_APP		57  //57 mcu侧外设板子注册处理App  需要与MCU同步


//注册服务器协议栈
#define AID_REGSIPSTACKOUT_APP		AID_TP_BGN + 40
#define AID_REGSIPSTACKIN_APP		AID_TP_BGN + 41

//注册服务器APP
#define AID_REGSERVER_APP			AID_TP_BGN + 16

//升级服务器APP
#define AID_UPDATESERVER_APP        AID_TP_BGN + 45

#define AID_CMSUE_APP				AID_TP_BGN + 17

#define AID_SIPSERVICE_APP			AID_TP_PROTOCOL_BEGIN + 1
#define AID_SIPSTACKIN_APP			AID_TP_PROTOCOL_BEGIN + 2
#define AID_SIPSTACKOUT_APP			AID_TP_PROTOCOL_BEGIN + 3

//应用 aid
#define AID_CMS2UMS_APP             AID_TP_BGN + 18
#define AID_CNC2CNS_APP             AID_TP_BGN + 19
#define AID_CNCADDRBOOK_APP         AID_TP_BGN + 20
#define AID_LOADCMC_APP             AID_TP_BGN + 21
#define AID_UPDATECMC_APP           AID_TP_BGN + 22
#define AID_UMSTOOL2UMS_APP         AID_TP_BGN + 23
//Add by tanxiaodong 2012-11-12.
#define AID_CNSTOOL2CNS_APP         AID_TP_BGN + 24
//Add by wqq 2013-04-12
#define AID_PRODUCETEST_APP         AID_TP_BGN + 25

//End to add.

//cns aid
#define	AID_CN_SYSAPI              AID_TP_BGN + 30
#define	AID_CN_SERVICE		       AID_TP_BGN + 31
#define AID_CN_TERAPI		       AID_TP_BGN + 32
#define AID_CN_UE				   AID_TP_BGN + 33
#define AID_CN_MEDIADS			   AID_TP_BGN + 34
#define AID_CN_DSMGR			   AID_TP_BGN + 35
#define AID_CN_AMix				   AID_TP_BGN + 36
#define	AID_CN_SUBROUTINEMGR	   AID_TP_BGN + 37
#define AID_CN_CALL				   AID_TP_BGN + 38
#define AID_CN_AGENT               AID_TP_BGN + 39
#define AID_CN_GUARD               AID_TP_BGN + 42
#define AID_CN_DEVCTRL             AID_TP_BGN + 43
#define AID_CN_UPDATE			   AID_TP_BGN + 44
#define AID_CN_PRODUCETEST         AID_TP_BGN + 45
#define AID_CN_TVCOMCTRL           AID_TP_BGN + 46

//moon add
#define MOON_LISTIONPORT_CP				60002

#define	AID_MOON_SYSAPI              AID_TP_BGN + 50
#define	AID_MOON_SERVICE		     AID_TP_BGN + 51
#define AID_MOON_UE				     AID_TP_BGN + 52
#define AID_MOON_PRODUCETEST         AID_TP_BGN + 53
#define AID_MOON_CAMERA              AID_TP_BGN + 54
//Add by wqq 2014-11-27
#define AID_MOONTOOL2CAM_APP         AID_TP_BGN + 55

#define MOON_MAX_NODE_NUM	1		//单一MOON接入实例最大数

#define MAX_THREECAMERA_NUM       3             //三眼摄像机摄像头个数
#define MAX_CAMERA_Pre_NUM        16            //三眼摄像机预置位个数
#define MAX_THREECAMERA_LEN       32             //三眼摄像机预置位描述


#define MOON_PRODUCT_ID		             "Moon90H"
#define MOON_VERSION_ID		             "2.1.1.4.0."
#define MOON_PRODUCT90_ID	             "Moon90"
#define MOON_VERSION90_ID	             "2.1.1.4.0."
#define TP_MAX_FILENAME_LEN              64
#define TTY_NAME_MAX_LEN                 20

//输出制式
#define MOON_1080P_WIDTH    1920
#define MOON_1080P_HEIGHT   1080
#define MOON_720P_WIDTH     1280
#define MOON_720P_HEIGHT     720

#define MOON_60_FRAMERATE      60
#define MOON_30_FRAMERATE      30
#define MOON_50_FRAMERATE      50
#define MOON_25_FRAMERATE      25

#define MOON_9600_BPS          9600
#define MOON_19200_BPS          19200
#define MOON_38400_BPS          38400
#define MOON_115200_BPS        115200

//ColorSpace = 0x80000000; // 目前使用的是内同步
#define MOON_COLORSPACE        0x0

#define MOON_MAX_DEVICEVER_LEN            38

#define MOON_OUTFORMAT_DELAY    1000
#define MOON_CAMPARAM_DELAY     7000
#define MOON_CORRECTLEVEL_VAUEL 2048
#define MOON_STRETCHREGION_VAUEL 1024
#define MOON_STRETCHLOW_VAUEL   512
#define MOON_CORRECTLOW_VAUEL   1500
#define MOON_CORRECT_STEP        5
//add by youjx 2017.5.3
#define MOON_COLORCOEFF_LOW_VALUE        500            //RGB系数最小值，对应界面-0.5
#define MOON_COLORCOEFF_HIGH_VALUE       1500           //RGB系数最大值，对应界面0.5
#define MOON_COLORCOEFF_STEP             1              //RGB系数调整步进，对应界面0.001
#define MOON_MAX_RECT_REGION_NUM         4              //RGB矩形区域个数
#define MOON_COLOR_COEFF_NUM             9              //颜色一致性计算结果个数
#define MOON_DISTORT_VALUE_NUM           13             //梯形校正的个数
#define MOON_DISTORT_ROTATE_STEP         5              //对应界面的梯形校正旋转步进为0.05
#define MAX_MOON_DISTORT_ROTATE          300            //对应界面梯形校正旋转最大角度1.5
#define MIN_MOON_DISTORT_ROTATE          0              //对应界面梯形校正旋转最大角度-1.5
#define MOON_DISTORT_STRECH_STEP         1              //梯形校正拉伸步进
#define MAX_MOON_DISTORT_STRECH          200            //梯形校正拉伸最大值
#define MOON_COLORCOEFF_DECIMAL          1000           //RGB系数计算结果保留三位小数
#define MOON_COLORCOEFF_DECIMAL_BIT      10             //RGB系数计算结果中小数占10bit
#define DISTORT_ROTATE_FORWARD           1              //梯形校正正向旋转
#define DISTORT_ROTATE_REVERSE           0              //梯形校正反向旋转
#define DISTORT_HORIZON_STRECH           1              //梯形校正水平拉伸
#define DISTORT_VERTICAL_STRECH          2              //梯形校正垂直拉伸
//add end
//#define MOON_HORIZON_VALUE       1
//#define MOON_VERTICAL_VALUE      6
       

//moon end

#define TELNET_UMS_PORT				2500
#define TELNET_SIPADAPTE_PORT		2501

#define TELNET_MEDIATRANS_PORT		2500

#define TELNET_AUDIOMIX_PORT		2500

#define TELNET_REG_PORT				2500
#define TELNET_UPDATESERVICE_PORT	2501

//msg define

//time define
#define TP_INTERVAL_TIME_ONE_SECOND		1000
#define TP_INTERVAL_TIME_TWO_SECOND		2000
#define TP_INTERVAL_TIME_THREE_SECOND   4000
#define TP_INTERVAL_TIME_FIVE_SECOND	5000

#define TP_INTERVAL_TIME_SHANPING    	2000

//LISTIEN PORT
#define UMS_LISTIONPORT_CMS				60000
#define CNS_LISTIONPORT_CMS				60002
#define REGSERVER_LISTIONPORT			60000
#define UPDATE_SERVICE_LISTION		60005 //升级服务器监听端口
#define CNS_PRODUCETEST_LISTION   60010 //生产测试服务器监听端口

#define TP_DEFAULT_H225_PORT	1720
#define TP_DEFAULT_H245_PORT	1719

//#define UMS_SIP_STACK_LISTION_PORT			5080
#define CNS_SIP_STACK_LISTION_PORT			6000

//#define MAX_USER_NAME    					(u16)64		//用户名长度
//mac define
#define TP_REC_FILE_LEN						192 //录播文件名最大长度
#define TP_MAX_RECORDER_PACK_NUM			16	//录播文件列表每包最大数量

#define TP_UMS_SIP_LISTIEN_PORT	5060			//SIP协议栈监听端口
#define TP_MAX_CASECADE_NUM		10				//最大级联数量
#define TP_MAX_EPID_LEN			64				//级联时，ID最大字符串长度

#define TP_MAX_LEN_PRODUCT_ID   128				//产品ID最大长度 

#define TP_MAX_ALIAS_LEN_CNC	32				//别名最大长度 应用组用
#define TP_MAX_ALIAS_LEN		64				//别名最大长度
#define TP_MAX_STREAMNUM		3				//会场最大发言人数量

#define TP_MAX_SMALLSTREAMNUM	2				//每屏小码流个数
#define TP_STREAM_LEFT			0				//左小码流
#define TP_STRAEM_RIGHT			1				//右小码流
#define TP_MAX_CAP_SIGN_NUM     3               //码流左中右标识最大个数

#define TP_TOOL_VERSION_LEN		32				//版本信息长度


#define TP_ROUNDTRIP_TIME		30				//roundtrip

#define TP_MAX_NUM_CALLID		128				//SIP协议栈回调的CALLID最大长度

#define TP_UMS_MAX_REGNUM		512				//UMS最大注册CNS数量
#define TP_UMS_MAX_REGALIAS		4096			//UMS最大注册的别名数量

#define TP_UMS_CHAN_BITRATE		3072
#define TP_UMS_MAX_CONFNUM		16				//UMS最多同时支持的会议
#define TP_CONF_MAX_EPNUM		64				//单个会议中最大呼叫数量
#define TP_CONF_MAX_CNSNUM		256			    //单个会议中最大CNS数量，包括级联
#define TP_CONF_INVITE_MAX_CNS	64				//单个会议中邀请的最大CNS数量，不包括级联

#define TP_UMS_MAX_CALLNUM		192				//UMS最大呼叫接入数量
#define TP_UMS_MAX_CHANNUM		192				//UMS最大接入屏数
#define TP_UMS_MAX_CASCADECHANNUM 192			//最大级联通道数量

#define TP_EAPU_PROTECTTIME_MAX		255			//语音激励最大保护时间
#define TP_EAPU_PROTECTTIME_MIN		1			//语音激励最小保护时间
#define TP_EAPU_PROTECTTIME_DEFAULT	4			//语音激励默认保护时间

#define TP_UMS_AUDMIX_POWER_MAX	32
#define TP_UMS_AUDMIX_POWER_MIX	0
#define TP_UMS_AUDMIX_POWER		0				//语音激励敏感度

#define TP_AUDMIX_MAX_CHANNUM	224				//混音板业务层最大通道数量
#define TP_MAX_AUD_MIX_CHAN		224				//混音板媒体层最大支持通道数量
#define TP_APU2_MAX_CHAN_NUM	64				//每个混音版支持的最大通道数量
#define TP_CONF_MAX_AUDMIXNUM	4				//最大混音参与数量 b1和b2 B3版本为讨论成员最大数量

#define TP_CONF_MAX_TURNNUM		64				//会议最大轮询数量
#define TP_CONF_TURN_MIN_INTERVAL	5			//会议轮询间隔最小值

#define TP_CONF_MAX_MAIN_VIDEO_RES_NUM  6           //最大主视频分辨率数量
#define TP_CONF_MAX_MINOR_VIDEO_RES_NUM 6          //最大辅视频分辨率数量

#define TP_CONFTEMPLATE_MAXNUM	128				//最大会议模板数量
#define TP_CONFTEMP_ALIAS_NUM	256				//模板别名数量，每个模板一个323ID，一个164号
#define TP_CONFTEMPGROUP_MAXNUM 64              //模版别名最大以64个为一组向注册服务器注册
#define TP_TEMPGROUP_MAXNUM     4               //模版最多4组注册
#define TP_TEMPNUM_PERGROUP     32              //模版32各分为一组

#define TP_MAX_NMSERVER			2				//最多网管服务器个数
#define TP_MAX_VCR				2
#define TP_MAX_HDU_NUM			5
#define MAX_LOG_USE_NUM			5

#define TP_KEEPALIVE_TIME		30				//keeplive
#define TP_KEYFRAME_STATIS		5				//关键帧请求的最大统计次数

#define TP_REFRESH_LIST_THREE	3
#define TP_REFRESH_LIST_FIVE	5

#define	TP_MAX_CONF_ID_LEN      16
#define	TP_MAX_CONF_E164_LEN	16
#define	TP_MAXLEN_PASSWORD      32

//画面合成相关
#define TP_VMP_SCHEME_CFG_NUM		5	//画面合成预设方案最大数量
#define TP_VMP_SCHEME_CFG_ALIAS		32	//画面合成参数配置方案别名长度

#define TP_VMP_BASIC_IN_CHN_NUM		4	//basic模式前适配4路
#define TP_VMP_EHANCE_IN_CHN_NUM	20	//ehance模式前适配20路
#define TP_VMP_MAX_IN_CHN_NUM		20	//mpu2画面合成前适配最大数量
#define TP_VMP_MAX_OUT_CHN_NUM		9	//mpu2画面合成后适配最大数量

//UMS板子相关参数
#define TP_UMS_BRD_MAXNUM_EQP	3	//每个板子中允许设置的最大外设数量
#define	MAXLEN_EQP_ALIAS        16   //单板模式名最大长度
#define TP_BOARD_VERSION_LEN    32  //单板版本信息长度
#define TP_BOARD_MAX_NUM        68   //最大单板数量
#define TP_BOARD_MAX_LAYER      4     //单板最多有4层
#define TP_BOARD_MAX_SLOT       17    //单板最多有17个槽位号
#define TP_UPGRADE_FILENAME_LENGTH   32 //单板升级文件名最大长度

#define TP_MAX_NUM_CONTACT_ADDR  5			//注册给注册服务器的接入地址数量
#define TP_UPLOAD_FILE_NAME_LENGTH	 32		//导入模板文件的文件名最大长度

#define TP_RET_ERROR 0xFFFF
#define TP_RET_OK	0
#define TP_AUDIO_CODEC_NUM      4  //音频编解码数
#define TP_VIDEO_CODEC_NUM      4 //视频编解码数

#define TP_MAX_LOSTPACK_NUM     14 //最大丢包路数
#define TP_MAX_VIDEO_RES_NUM     8 //最大视频编解码数

#define TP_MAX_CNS_REG_ALIAS	2
#define TP_MAX_UMS_REG_ALIAS	64

//双流终端位默认放最后
#define TP_DUAL_POS                    CNS_MAX_TER_NODE_NUM - 1

#define TPOUT	//出参
#define TPIN	//入参

#define TPIPFORMAT     "%d.%d.%d.%d"
#define Tpu32ToIP( ip )   (u8)(ntohl(ip)>>24),\
						(u8)(ntohl(ip)>>16),\
						(u8)(ntohl(ip)>>8), \
                        (u8)ntohl(ip) 

#define TP_INVALID_INDEX		0xFFFF
#define TP_VALID_HANDLE(handle)	(TP_INVALID_INDEX != u16(handle))

//参数为TTPTransAddr
#define ADDRNET(addr) \
	((unsigned char *)&addr.m_dwIP)[0], \
    ((unsigned char *)&addr.m_dwIP)[1], \
    ((unsigned char *)&addr.m_dwIP)[2], \
	((unsigned char *)&addr.m_dwIP)[3], \
	addr.m_wPort

#define ADDRPORT(addr, port) \
    ((unsigned char *)&addr)[0], \
    ((unsigned char *)&addr)[1], \
    ((unsigned char *)&addr)[2], \
	((unsigned char *)&addr)[3], \
	port
#define ADDRPORT_FORMAT	 " %3d.%3d.%3d.%3d:%5d "

                      
#define     TP_MAX_PROXYSERVER_NAME_LEN	255			//代理防火墙域名的最大长度
#define		TP_MAX_H323ALIAS_LEN        64            // 终端别名最大长度 
#define     TP_MAX_NAME_LEN             TP_MAX_H323ALIAS_LEN
#define     TP_MAX_PASSWORD_LEN			16           // 密码最大长度   
#define		TP_NAME_LEN_256				(u16)256
#define		TP_REGNAME_SIZE			64
#define		TP_MAX_VERSION_LEN				64


template < class T >
T TP_SAFE_CAST( T &t, u8 *p )
{
	if (NULL == p) return t;
	memcpy( &t, p, sizeof( T ) );
	return t;
}

#define TP_SAFE_DEL(p) if(NULL != p){ delete p; p = NULL;}

typedef u32   u32_ip;

//CNS Define
#define CNS_MAX_TER_NODE_NUM		4		//单一会场接入终端最大数组
#define CNS_MAX_CONF_NODE_NUM	3		//单一Cns接入会场最大数
#define CNS_MAX_CHANNEL_NUM 40

//Add by tanxiaodong 2012-07-17.
#define CNS_VGA_TYPE_NUM     7         //VGA类型数
#define TPAD_MAX_NUM         16            //TPad最大个数
#define MAX_DISPLAY_NUM      3             //显示器个数
#define MAX_LIGHT_NUM        8             //灯光个数
#define MAX_CAMERA_NUM       3             //摄像机个数
#define AUDIO_PORT_NUM       4             //每组中音频接口个数
#define MAX_PRIM_VIDEO_INPUT_PORT_NUM  3   //第一路视频输入端口个数
#define MAX_PRIM_VIDEO_OUTPUT_PORT_NUM 3   //第一路视频输出端口个数
#define MAX_PRIM_AUDIO_INPUT_PORT_NUM  3   //第一路音频输入端口个数
#define MAX_PRIM_AUDIO_OUTPUT_PORT_NUM 3   //第一路音频输出端口个数
#define MAX_DEMO_AUDIO_PORT_NUM        6   //双流演示音频输入端口个数
#define CPU_MAX_USE_RATE     100           //CPU最大使用率
#define EQUQLIZER_FREQUENCY_NUM        10   //均衡器频率点个数
#define MAX__TP_MEDIA_CAP_NUM          10  //每个通道中携带的能力最大个数 
//End to add.

#define CANNON_DEFAULT_VALUE           10  //卡农麦克恢复默认值
#define MIXAUDIO_SINGLEDEFAULT_VALUE   1   //混音单路恢复默认值
#define MIXAUDIO_DEFAULT_VALUE         3   //混音配置恢复默认值

#define MAX_AUDIO_PORT_NUM     10         //音频接口的最大个数

#define CNS_PRODUCT_ID		"CNSTPS"
#define CNS_VERSION_ID		"1.1.3.0.0."
#define	CNS_VERSION_ID_TEMP "2."
#define CNS_CALL_PORT		CNS_SIP_STACK_LISTION_PORT
#define CNS_VIDEO_CHAN_BAND 4096
#define CNS_AUDIO_CHAN_BAND 96
#define CNS_DUAL_BAND		4096
#define CNS_PRI_FRAMERATE	50
#define CNS_DUAL_FRAMERATE	50
#define CNS_GK_PORT			1719
#define CNS_H225_PORT		1720


#define CNS_CALL_MAX_CHANNEL			14
#define CNS_Dual_MAX_CHANNEL			4

	//POS TYPE
#define SPEAKER_MASK					0x0001
#define FULLVIEW_MASK					0x0002
#define DUAL_MASK						0x0004
#define AUDIO_MASK						0x0008


#define TP_MAXLEN_ENCRYPTKEY			64

#define node_ui							0x001
#define node_cnc						0x002       //CNS控制台
#define node_ums						0x004 
#define node_cncall						0x008
#define node_cnds						0x020
#define node_amix						0x021   

//Add by tanxiaodong 2012-11-12.
#define node_cnstool2cns             0x010      //维护工具
//End to add.

#define HOME_STACK						((u8)0x01)
#define HOME_SERVICE					((u8)0x02)

#define ins_each						0xff

//cns编解码器使用的端口
#define MT_AUDIO_SND_RTP				10001  
#define MT_AUDIO_SND_RTCP				10002  
#define MT_AUDIO_SND_BRTCP				10003  

#define MT_AUDIO_RCV_RTP				10004  
#define MT_AUDIO_RCV_RTCP				10005  
#define MT_AUDIO_RCV_BRTCP				10006  

#define MT_PRIVIDEO_SND_RTP				10031  
#define MT_PRIVIDEO_SND_RTCP			10032  
#define MT_PRIVIDEO_SND_BRTCP			10033  

#define MT_PRIVIDEO_RCV_RTP				10034  
#define MT_PRIVIDEO_RCV_RTCP			10035  
#define MT_PRIVIDEO_RCV_BRTCP			10036  

#define MT_SECVIDEO_SND_RTP				10051  
#define MT_SECVIDEO_SND_RTCP			10052  
#define MT_SECVIDEO_SND_BRTCP			10053 

#define MT_SECVIDEO_RCV_RTP				10054  
#define MT_SECVIDEO_RCV_RTCP			10055  
#define MT_SECVIDEO_RCV_BRTCP			10056 

//cns转发模块起始端口
#define CN_DS_BASE_PORT					25000
#define CN_DS_MAX_NUM					10000
#define CN_DS_INS_OFFSET				100

#define CN_MAX_USER_NUM					20


//cns 发言座席特殊标识
#define CN_INNERSPEAKER_ALL				0xff
#define CN_INNERSPEAKER_NONE			0xf0


#define ADDR_MAX_USER_NAME_LENGTH		32
#define CN_HBPARAM_HB					30
#define CN_HBPARAM_HBNUM				3

#define CN_DUAL_MULTICAST_IP            "224.0.5.000"
#define MAX_COMMUNITY_LENGTH            32  // SNMP共同体名最大长度
#define MAX_CNS_SNMP_NUM                2  //单一CNS中添加网管服务器的最大数量

#define MAX_CAMERA_NAME_LEN             256
#define MAX_CNCAMERA_NUM                3  //摄像机数量
#define MAX_CENTRETV_NUM                3  //电视机数量
#define MAX_AC_NUM                      3  //最大空调数
#define MAX_CURTAIN_NUM                 6  //最大窗帘数
#define MAX_CURNAME_LEN                 64 //

#define INVALID_MIX_INDEX               0xFFFF
#define INVALID_VCR_HANDLE				0XFFFF

//本地升级文件目录
#define	FLASHFILE_PATH_NAME             "/usr/"
#define UPDATEFILE_PATH_NAME            "/ramdisk/"
#define UPDATEFILE_PATH_FROM_UPDATESER  "/ramdisk/sysfile/"
#define LOGO_UPLOAD_PATH                "/usr/conf/" 

//设备版本号最大长度
#define MAX_DEVICEVER_LEN            38
#define PRE_DEVICEVER_LEN            12
#define MAX_REG_DEVICE_NUM            6
#define MAX_DEVICE_NUM                20
#define MAX_FTP_NAME_LEN               16
const int TP_MAX_FILESRV_FILENAME_LEN  = 32;        //最大的文件名长度


#define MAX_VTR_NAME_LENGTH				32

#define MAX_MT_ONLINE_LIST_NUM			64	//
#define MAX_MT_ALIAS_NUM				2

#define TP_CNS_ALIAS_REG_NUM	2
#define TP_UMS_MAX_REG_DATA		3
#define TP_CNS_MAX_REG_DATA		20

//台标路径
#define CNMP_LOGO720P_PATH      "usr/conf/confname720.bmp"
#define CNMP_LOGO1080P_PATH     "usr/conf/confname1080.bmp"

#define CNMP_LOGO720P_INITIALPATH      "usr/bin/confname720.bmp"
#define CNMP_LOGO1080P_INITIALPATH     "usr/bin/confname1080.bmp"

//台标图片占用最大长度  支持200K文件传输
#define CNMP_LOGO_MAX_LENGTH    184320

// #define LEVEL_PROVINCE		0x0001
// #define LEVEL_CITY			0x0002
// #define LEVEL_COUNTY		0x0003

#define CONF_HP_BITRATE					2048		//双速会议主视频为HP会议码率为2Mbps
#define CONF_BP_BITRATE					4096		//双速会议主视频为BP会议码率为4Mbps

#define VRS_ProductID               	"KDCVRS2000"
#define VRS_ProductID_E               	"KDCVRS2000E"
#define TP_VIDEO_TIME_SPAN             40
#define TP_VIDEO_TIMESTAMP_SPAN        90
#define TP_AUD_REC_BUFF                20  //音频接收缓存
#define TP_LOST_AUD_PACKET_NUM         10   //音频包间隔数
#define TP_AUD_PACKET_TIMEOUT         1000   //音频包超时时间

#endif // _h_tpsys_h__








