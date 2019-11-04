#ifndef _MOON_CONST_H
#define _MOON_CONST_H
#include "kdvdef.h"

//MT begin.
#include "kdvtype.h"                                                                                                                                                                        
enum EmDataFormat                                                                           
{                                                                                           
	emStr  ,                                                                            
	emHex  ,                                                                            
	emBin  ,                                                                            
//	emBOOL ,                                                                            
	emOct  ,                                                                            
	emIP   ,                                                                            
	emDec  ,                                                                            
	emDW                                                                                
};                                                                                          
                                                                                            
                                                                                            
#define CALLRATE_64_SEL        0x00000001                                                   
#define CALLRATE_128_SEL       0x00000002                                                   
#define CALLRATE_192_SEL       0x00000004                                                   
#define CALLRATE_256_SEL       0x00000008                                                   
#define CALLRATE_320_SEL       0x00000010                                                   
#define CALLRATE_384_SEL       0x00000020                                                   
#define CALLRATE_448_SEL       0x00000040                                                   
#define CALLRATE_512_SEL       0x00000080                                                   
#define CALLRATE_576_SEL       0x00000100                                                   
#define CALLRATE_640_SEL       0x00000200                                                   
#define CALLRATE_704_SEL       0x00000400                                                   
#define CALLRATE_768_SEL       0x00000800                                                   
#define CALLRATE_832_SEL       0x00001000                                                   
#define CALLRATE_896_SEL       0x00002000                                                   
#define CALLRATE_960_SEL       0x00004000                                                   
#define CALLRATE_1024_SEL      0x00008000                                                   
#define CALLRATE_MASK          0x0000FFFF                                                   
                                                                                            
                                                                                             
//
// VOD Limited Condition 
//
#define VOD_DIRECTORY_SEPARATOR ( ( s8* ) "\\" )

const int VOD_MAX_CLIENT = 32; // 最多能连接的客户端数
const int VOD_MAX_USER_NAME_LENGTH = 32; // 用户名长度
const int VOD_MAX_PASSWORD_LENGTH = 32; // 密码长度
const int VOD_MAX_PATH_FILE_NAME_LENGTH = 128;  // 带路径的文件名长度
const int VOD_MAX_DIRECTIRY_NAME_LENGTH = 128; // 路径名长度
const int VOD_MAX_FILE_NAME_LENGTH = 50; // 文件名长度 
const int VOD_MAX_FILE_NUMBER = 64; // 同一文件夹下最多文件数                                                                                        
                                                                                            
                                                                                            
// 长度定义   
const int    MT_MAX_H323ALIAS_LEN       =   64;            // 终端别名最大长度                                                                                 
const int    MT_MAX_NAME_LEN            =   MT_MAX_H323ALIAS_LEN;                                                          
const int    MT_MAX_E164NUM_LEN         =   16;            // 终端E164最大长度                 
const int    MT_MAX_PORTNAME_LEN        =   16;            // 视频矩阵端口名最大长度           
const int    MT_MAX_AVMATRIX_PORT_NUM   =   64;            // 视频矩阵最大端口个数            
const int    MT_MAX_AVMATRIX_MODEL_NAME =   16; 
const int    MT_MAXLEN_AVMATRIX_SCHEMENAME  = 16;          //矩阵方案别名最大长度
const int    MT_MAX_AVMATRIX_PORTNAME_LEN = 16;            //矩阵端口名最大长度
const int    MT_MAX_COMM_LEN            =   32;            // SNMP共同体名最大长度             
const int    MT_MAX_PPPOE_USERNAME_LEN  =   16;            // PPPOE用户名最大长度              
const int    MT_MAX_CHANNEL_NAME_LEN    =   16;            // 流媒体频道名最大长度             
const int    MT_MAX_PASSWORD_LEN        =   16;            // 秘密最大长度                     
const int    MT_MAX_FULLFILENAME_LEN    =   128;           // 完整文件名最大长度               
const int    MT_MAX_FILEPATH_LEN        =   128;           // 路径名最大长度                   
const int    MT_MAX_CAMERA_NUM          =   6;             // 摄像头最大个数 
const int    MT_MAX_CAMERA_EX_NUM       =   64;            // 最大扩展摄像头数                  
const int    MT_MAX_CAMERA_NAME_LEN     =   16;            // 摄像头名字最大长度               
const int    MT_MAX_ETHNET_NUM          =   4;             // 终端以太网口最大值               
const int    MT_MAX_E1_NAME_LEN         =   32;            // E1名最大长度                     
const int    MT_MAX_E1UNIT_NUM          =   4;             // E1模块最多E1数                   
const int    MT_MAX_ROUTE_NUM           =   16;            // 最多路由条目                     
const int    MT_MAX_SERIAL_NUM          =   3 ;            //最多串口条目
const int    MT_MAXNUM_MIX_MEMBER       =   10;            //参数混音坏成员数
const int    MT_MAX_VIDEO_NUM           =   2 ;            //最多视频路数
const int    MT_MAXNUM_VMP_MEMBER       =   20;            //画面合成成员数
const int    MT_MAXNUM_SMSDST           =   64;            //短消息发送目的成员最大值
const int    MT_MAXLEN_SMSTEXT          =   1024;          //短消息内容最大长度
const int    MT_MAX_IMAGEJUDGEPARAM_NUM =   2;             //画面调整参数表 
const int    MT_MAX_POLL_NUM		    =   16;    		   //最大轮询终端数
const int    MT_MAX_ADDRENTRY_NUM	    =   128;           //地址簿最大条目个数
const int    MT_MAX_ADDRMULTISET_NUM    =   16;            //地址簿最大组个数
const int    MT_MAX_NETSND_DEST_NUM     =   5 ;            //双流盒最大发送的目的地数
const int    MT_MAX_CALLSITE_TERNINAL   =   16;            //最大发起的会议个数
const int    MT_MAX_ADDRUSERDEF_LEN     =   1024;          //地址簿用户自定义字段长度
const int    MT_MAX_MTC_CAPSET_LEN      =   1024;          //MT和MTC握手的能力字符串长度

const int    MT_MAXNUM_VIDSOURCE        =   10;            //最大视频源数
const int    MT_MAXNUM_CALLADDR_RECORD  =   5;             //最大呼叫地址记录数

const int    MT_PPPoE_MAX_USENAME_LEN     =  255;          //PPPOE拨号时使用的用户名的最大长度
const int    MT_PPPoE_MAX_PASSWORD_LEN    =  255;          //PPPOE拨号时使用的密码的最大长度
const int    MT_PPPoE_MAX_SERVERNAME_LEN  =  255;          //PPPOE拨号时使用的指定ISP服务商名字的最大长度
const int    MT_PPPoE_MAX_VERSION_LEN     =  255;          //PPPOE版本信息的最大长度
const int    MT_MAX_UPDATASERVER_NAME_LEN =  64;           //升级服务器的域名的最大长度
const int    MT_MAX_LDAPSERVER_NAME_LEN   =  100;          //LDAP服务器域名的最大长度
const int    MT_MAX_PROXYSERVER_NAME_LEN  =  255;          //代理防火墙域名的最大长度
const int    MT_MAX_H323GKSERVER_NAME_LEN =  255;          //H323注册Gk域名的最大长度
const int    MT_MAX_HDAUDIOPORT_LEN       =  15;           //音频端口个数最大值

//FILESRV: 升级服务器相关
const int    MT_MAX_FILESRV_BUG_REPORT_LEN   = 512;       //升级版本中的修复的bug描述0
const int    MT_MAX_FILESRV_FILENAME_LEN     = 64;        //最大的文件名长度
const int    MT_MAX_FILESRV_DEVFILE_NUM      = 4;         //最大的文件个数
const int    MT_MAX_FILESRV_SOFTWARE_VER_LEN = 32;        //软件版本号最大长度

const int    MT_MAX_PXYIP_NUM                =   5;            // 最多内置pxy支持的ip地址数   

//WiFi配置相关 
const int    MT_WIFI_MAX_NAME_LEN            =   32;
const int    MT_WIFI_MAX_PASSWORD_LEN        =   256;
const int    MT_WIFI_MAX_BSSIDCFG_NUM        =   16;  

//HD终端的视频输出口个数
const int    MT_HD_MAX_AV_OUTPORT_NUM  = 4;            //高清终端的最大视频输出口的个数

const int    MT_VIDEO_OUTPORT_NUM          = 4;    
const int    MT_INNERMATRIX_SCHEME_NUM     = 8;
const u32    MT_DVI_PORT_NUM               = 6;    

const u8     ExVideoMoudle_None = 0;
const u8     ExVideoMoudle_SDII = 1;
const u8     ExVideoMoudle_SDIO = 2;

const u8     DVI_MODE_HDMI  = 0;
const u8     DVI_MODE_DVI  = 1;
const u8     DVI_MODE_YPBPR = 2;
const u8     DVI_MODE_VGA   = 3;

//输出口的输入源定义
const u8     HD2G_VIDEO_IN_PVDEC   = 0;
const u8     HD2G_VIDEO_IN_SVDEC   = 1;
const u8     HD2G_VIDEO_IN_DVI1   = 2;
const u8     HD2G_VIDEO_IN_DVI2   = 3;
const u8     HD2G_VIDEO_IN_DVI3   = 4;
const u8     HD2G_VIDEO_IN_CVBS   = 5;
const u8     HD2G_VIDEO_IN_SDI1   = 6;
const u8     HD2G_VIDEO_IN_SDI2   = 7;
const u8     HD2G_VIDEO_IN_INVALID   = 255;


#define      MT_MAXNUM_MCTERMINAL        6    //终端MTC支持呼叫的最大终端数
#define      MT_MAXLEN_CAMERA_TYPE_NAME  32    //摄像头类型名最大长度                                                                                        
//==========================================================================================
//				任务相关常量定义                                            
//==========================================================================================
                                                                                            
////////////////////////////// 任务ID ////////////////////////////                          
const int    AID_MT_BEGIN        =   AID_MT_BGN;
const int    AID_MT_AGENT	     =   AID_MT_BEGIN + 1;    	//终端代理                          
const int    AID_MT_SERVICE      =   AID_MT_BEGIN + 2;        //终端业务应用ID                      
const int    AID_MT_GUARD	     = 	 AID_MT_BEGIN + 3;    	//终端守卫                          
const int    AID_MT_UE		     =	 AID_MT_BEGIN + 4;    	//业务接口实体                      
const int    AID_MT_STACKIN      =	 AID_MT_BEGIN + 5;    	//H323 协议栈输入                   
const int    AID_MT_STACKOUT	 =	 AID_MT_BEGIN + 6;    	//H323 协议栈输出                   
const int    AID_MT_RCP		     =	 AID_MT_BEGIN + 7;    	//MT RCP                            
const int    AID_MT_H320STACK    =   AID_MT_BEGIN + 8;        //H320 协议栈适配应用                    
const int    AID_MT_RCSIM        =	 AID_MT_BEGIN + 9;        //遥控器，模拟模块                  
const int    AID_MT_MC		     =	 AID_MT_BEGIN + 10;    	//MC                                
const int    AID_MT_SNMP	     =	 AID_MT_BEGIN + 11;        //SNMP                              
const int    AID_MT_CONFIG       =   AID_MT_BEGIN + 12;        //配置文件管理应用ID                  
const int    AID_MT_UI	         =	 AID_MT_BEGIN + 13;        //终端界面应用                
const int    AID_MT_DEVCTRL	     =	 AID_MT_BEGIN + 14;    	//设备控制                          
const int    AID_MT_CODEC	     =	 AID_MT_BEGIN + 15;    	//编解码                            
//const int    AID_ADDRBOOK	     =	 AID_MT_BEGIN + 16;    	//地址簿                            
const int    AID_MTCONSOLE	     =	 AID_MT_BEGIN + 17;    	//终端控制台 
const int    AID_MT_SYS          =   AID_MT_BEGIN + 18;        //终端系统应用ID                  
const int    AID_MT_H323SERVICE  =   AID_MT_BEGIN + 20;        //终端H323业务应用ID                  
const int    AID_MT_H320SERVICE  =   AID_MT_BEGIN + 21;        //终端H320业务应用ID                  
const int    AID_MT_SIPSERVICE   =   AID_MT_BEGIN + 22;        //终端SIP业务应用ID                                                                                            
const int    AID_MT_DVB          =   AID_MT_BEGIN + 23 ;        //终端双流盒业务应用ID
const int    AID_MT_DVBSSN       =   AID_MT_BEGIN + 24;        //双流盒会话应用
const int    AID_MT_VODCLIENT    =   AID_MT_BEGIN + 25;         //VOD客户端应用ID
const int    AID_MT_PCDUALVIDEO  =   AID_MT_BEGIN + 26;         //pc双流软件应用ID
const int    AID_MT_UPGRADE      =   AID_MT_BEGIN + 27;         //自动升级应用ID
const int    AID_MT_BATCHCONFIG  =   AID_MT_BEGIN + 28;         //配置文件批处理应用ID
const int    AID_MT_AUTOTEST     =   AID_MT_BEGIN + 29;         //终端硬件自动化测试应用ID   
const int    AID_MT_AUTOTESTCLIENT = AID_MT_BEGIN + 30;         // add by wangliang 2007-03-02
const int    AID_MT_REMOTESIM    =   AID_MT_BEGIN + 31;         // add by wangliang 2007-03-02
const int    AID_MT_THREADDETECT =   AID_MT_BEGIN + 32;         // add by qianshufeng 2008-01-07
const int	 AID_MT_LOG_RECV	 =   AID_MT_BEGIN + 33;			// 日志接收APP
const int	 AID_MT_LOG_IO		 =   AID_MT_BEGIN + 34;			// 日志IOAPP，此线程不接收外部消息
const int    AID_MT_SIPSTACK_IN  =   AID_MT_BEGIN + 35;
const int    AID_MT_SIPSTACK_OUT =   AID_MT_BEGIN + 36;
const int    AID_MT_SATINTERFACE =   AID_MT_BEGIN + 37;
const int	 AID_MT_SATSERVICE   =   AID_MT_BEGIN + 38;
const int	 AID_MT_TPREG   =   AID_MT_BEGIN + 40;
//End
#define AID_MT_CTRL     AID_MT_SERVICE

#define AID_ADDRBOOK    46
////////////////////////////// 任务优先级 ////////////////////////////                      
                                                                                            
	                                                                                    
//==========================================================================================
//			     会议相关常量定义                                               
//==========================================================================================
                                                                                            
////////////////////////////// 消息结构常量 ////////////////////////////                    
                                                                                         
                                                                                            
#define     MT_MAX_CONF_ID_LEN 			16        //会议ID长度                         
#define     MT_MAX_CONF_NAME_LEN		64	      //会议名字长度                       
#define     MT_MAX_CONF_E164_LEN	 	16	      //会议号码长度                      
#define     MT_CONF_CAPACITY			192		  //会议终端容量      
#define     MT_MAXNUM_INVITEMT			32        //创建会议邀请的最大终端数
#define		MT_MAX_CONF_NUM				16		  //最大会议数

#define     MT_CONFLIST_TO_MTC			35		  //会议终端列表发给mtc

#define     MT_MAXLEN_ENCRYPTKEY    64 

const int   MT_MAXLEN_MESSAGE       =   1024*24;  //终端消息最大长度16K                                                                                            

#define     MT_MAXLEN_CONFGUID          16		  //会议guid最大长度
#define     MT_MAXLEN_PASSWORD          32		  //密码最大长度
#define     MT_NAME_LEN                 16		  //终端别名长度                      
//#define		CTRL_TERLABEL_UPPER		193			//无效的终端编号    
//#define     CTRL_TERMID_LEN			128			//会议终端ID长度


// 日志级别
#define		MT_LOG_ERROR		0
#define		MT_LOG_VITAL		1
#define		MT_LOG_WARNING		10
#define		MT_LOG_HINT			100
#define		MT_LOG_DETAIL		200
#define		MT_LOG_MAX			255

//定义mtmp错误码
//[xujinxing-2006-05-15]

#define   MTMP_NO_ERROR     (u16)0
#define   MTMP_ERROR_BASE   (u16)5000
#define   ERROR_DECODER_SNAPSHOT_FAIL_H261  (u16)(MTMP_ERROR_BASE + 1)
#define   ERROR_ENCODER_SNAPSHOT_FAIL_H261  (u16)(MTMP_ERROR_BASE + 2)

//定义跟mc_license相关的宏 
//[xujinxing-2006-10-13]

// License控制
#define MT_KEY_FILENAME                "kedalicense.key" // "mt.key"
#define MT_KEDA_AES_KEY				  "kedacom200610101"
#define MT_KEDA_COPYRIGHT			  "Suzhou Keda Technology Co.,ltd. Tel:86-512-68418188, Fax: 86-512-68412699, http://www.kedacom.com"
// 加密内容的长度
#define MT_LEN_KEYFILE_CONT              (u16)512

//add by xujinxing, telnet authority
#define MT_TEL_USRNAME  "Keda_User"
#define MT_TEL_PWD      "Pwd_Change"

#define MT_TELNET_PWD_MAX_LEN 32

/************************************************************************/
/* 终端硬件自动化测试 wl 2007/02/06
/************************************************************************/

// 自动化测试软件版本号
#define MT_AUTOTEST_VER 0x0100

// 测试失败原因
#define AUTOTEST_NACK_REASON_OK          0  //测试结果成功
#define AUTOTEST_NACK_REASON_HDERR       1  //硬件测试失败
#define AUTOTEST_NACK_REASON_TESTING     2  //测试正在进行
#define AUTOTEST_NACK_REASON_UNSUPPORT   3  //硬件不支持
#define AUTOTEST_NACK_REASON_STATUSERROR 4  //终端状态错误
#define AUTOTEST_NACK_REASON_VERERROR    5  //版本号错误

/* 自动化测试接口函数参数常量定义 */

// VLYNQ功能和性能诊断参数: 工作频率+工作状态+测试方案
const u8 AUTOTEST_VLYNQFUNC_FREQ_76 = 0;  // VLYNQ工作频率: 76MHZ
const u8 AUTOTEST_VLYNQFUNC_FREQ_99 = 1;  // VLYNQ工作频率: 99MHZ 

const u8 AUTOTEST_VLYNQFUNC_STATE_0 = 0;  // VLYNQ工作状态: 主模式
const u8 AUTOTEST_VLYNQFUNC_STATE_1 = 1;  // VLYNQ工作状态: 从模式

const u8 AUTOTEST_VLYNQFUNC_MODE_1  = 1;  // VLYNQ测试方案: 向对方DSP地址写递增数据
const u8 AUTOTEST_VLYNQFUNC_MODE_2  = 2;  // VLYNQ测试方案: 向对方DSP地址写递减数据
const u8 AUTOTEST_VLYNQFUNC_MODE_3  = 3;  // VLYNQ测试方案: 向自己DSP地址写递增数据
const u8 AUTOTEST_VLYNQFUNC_MODE_4  = 4;  // VLYNQ测试方案: 向自己DSP地址写递减数据
const u8 AUTOTEST_VLYNQFUNC_MODE_5  = 5;  // VLYNQ测试方案: 向自己DSP地址读递增数据
const u8 AUTOTEST_VLYNQFUNC_MODE_6  = 6;  // VLYNQ测试方案: 向自己DSP地址读递减数据
const u8 AUTOTEST_VLYNQFUNC_MODE_7  = 7;  // VLYNQ测试方案: 向对方DSP地址读递增数据
const u8 AUTOTEST_VLYNQFUNC_MODE_8  = 8;  // VLYNQ测试方案: 向对方DSP地址读递减数据

// EPLD寄存器读写诊断参数:  epld操作命令
const u8 AUTOTEST_EPLDFUNC_CMD_WRITECMD = 0;
const u8 AUTOTEST_EPLDFUNC_CMD_READCMD  = 1;

// 音频自环诊断参数: 采样率+音频数据格式
// 采样率使用时需要使用实际值
const u8 AUTOTEST_AUDIOFUNC_SAMPLERATE_8000  = 0; // 采样率: 8000
const u8 AUTOTEST_AUDIOFUNC_SAMPLERATE_32000 = 1; // 采样率: 32000
const u8 AUTOTEST_AUDIOFUNC_SAMPLERATE_44100 = 2; // 采样率: 44100
const u8 AUTOTEST_AUDIOFUNC_SAMPLERATE_48000 = 3; // 采样率: 48000

const u8 AUTOTEST_AUDIOFUNC_FORMAT_16 = 0; // 音频数据格式: S16_LE
const u8 AUTOTEST_AUDIOFUNC_FORMAT_32 = 1; // 音频数据格式: S32_LE

// 视频自环诊断参数: 输出格式+OSD显示+画中画显示

const u8 AUTOTEST_VIDEOFUNC_OUTPUT_0  = 0;  // 输出格式: D1
const u8 AUTOTEST_VIDEOFUNC_OUTPUT_1  = 1;  // 输出格式: CIF 
const u8 AUTOTEST_VIDEOFUNC_OUTPUT_2  = 2;  // 输出格式: ZOOM 
const u8 AUTOTEST_VIDEOFUNC_OUTPUT_3  = 3;  // 输出格式: VGA60 
const u8 AUTOTEST_VIDEOFUNC_OUTPUT_4  = 4;  // 输出格式: VGA75 
const u8 AUTOTEST_VIDEOFUNC_OUTPUT_5  = 5;  // 输出格式: VGA85
const u8 AUTOTEST_VIDEOFUNC_OUTPUT_6  = 6;  // 输出格式: SVGA60 
const u8 AUTOTEST_VIDEOFUNC_OUTPUT_7  = 7;  // 输出格式: SVGA75
const u8 AUTOTEST_VIDEOFUNC_OUTPUT_8  = 8;  // 输出格式: SVGA85
const u8 AUTOTEST_VIDEOFUNC_OUTPUT_9  = 9;  // 输出格式: XGA60 
const u8 AUTOTEST_VIDEOFUNC_OUTPUT_10 = 10; // 输出格式: XGA75

const u8 AUTOTEST_VIDEOFUNC_OSD_0 = 0; // OSD显示: 不支持
const u8 AUTOTEST_VIDEOFUNC_OSD_1 = 1; // OSD显示: 支持

const u8 AUTOTEST_VIDEOFUNC_PIP_0 = 0; // 画中画显示: 不支持
const u8 AUTOTEST_VIDEOFUNC_PIP_1 = 1; // 画中画显示: 支持

const u8 MAX_CHAIR_POLLSCHEME_NUM = 3; // 主席终端轮询方案数目

const u8 MAX_MTCBOX_SHORTCUT_CALL_NUM = 4; //MTC BOX 支持的最大快捷呼叫数目

//////////////////////////////////////////////////////////////////////
/*HD Macro definition BEGIN*/
#define HD_PATCH_VER_A              0
#define HD_PATCH_VER_B              1

#define HD_RESIZE_FILL              0 //加黑边
#define HD_RESIZE_CLIP              1 //裁边
#define HD_RESIZE_SCALE             2 //拉伸

#define HD_SCREENMODE_SIMPLE        0
#define HD_SCREENMODE_NORMAL        1
#define HD_SCREENMODE_ADVANCE       2


/*WIFI Macro definition BEGIN*/
#define WIFI_MAX_BSS_NUM            16
#define WIFI_MAX_KEY_LEN            64
#define WIFI_MAX_NAME_LEN           64

#define WIFI_MAX_CFG_NUM            16

#define WIFI_NET_TYPE_INFRA          0
#define WIFI_NET_TYPE_ADHOC          1

#define WIFI_AUTH_TYPE_OPEN          0
#define WIFI_AUTH_TYPE_SHARE         1
#define WIFI_AUTH_TYPE_WPA_PSK       2
#define WIFI_AUTH_TYPE_WPA2_PSK      3

#define WIFI_ENCRYTO_TYPE_WEP        0
#define WIFI_ENCRYTO_TYPE_AES        1
#define WIFI_ENCRYTO_TYPE_TKIP       2

//终端发言状态（对应MCU枚举emMtSpeakerStatus）
#define MT_SPEAK_STATUS_BGN      (u32)0
#define MT_SPEAK_STATUS_WAITING  (u32)1
#define MT_SPEAK_STATUS_AGREED   (u32)2
#define MT_SPEAK_STATUS_DENIED   (u32)3
#define MT_SPEAK_STATUS_CANCELED (u32)4

//mcu发言模式（对应mcu枚举emConfSpeakMode）
#define MT_SPEAK_MODE_NORMAL     (u32)0 //普通发言模式：主席指定/会控指定/一般的终端申请
#define MT_SPEAK_MODE_INSTANTLY  (u32)1 //抢答模式
#define MT_MAX_CNS_NAME_LEN		  (u16)256



#define MT_MEPG4AAC_CHAN_MONOPHONY     (u8)1               //单声道
#define MT_MEPG4AAC_CHAN_BINAURAL      (u8)2               //双声道
#define MT_MEPG4AAC_IDLE_CHAN_TYPE     MT_MEPG4AAC_CHAN_MONOPHONY

#define MT_HD_IMAGE_PARAM_COUNT         4      // 配置总数,不包括SDI
#define MT_HD_IMAGE_PARAM_YPbPr0    (u8)0      // 分量1的图像参数配置索引
#define MT_HD_IMAGE_PARAM_YPbPr1    (u8)1      // 分量2的图像参数配置索引
#define MT_HD_IMAGE_PARAM_YPbPr2    (u8)2      // 分量3的图像参数配置索引
#define MT_HD_IMAGE_PARAM_CVBS      (u8)3      // CVBS的图像参数配置索引

#define MT_HD_IMAGE_PARAM_SDI0		(u8)4      // SDI1的图像参数配置索引
#define MT_HD_IMAGE_PARAM_SDI1		(u8)5	   // SDI2的图像参数配置索引


#define MT_HD_IMAGE_PARAM_INVALID   (u8)0xFF   // 无效索引
#define GetHdParamImageIndex( emMtVideoPort )\
( emMtVideoPort == emMtC1Vid ? MT_HD_IMAGE_PARAM_YPbPr0 : \
( emMtVideoPort == emMtC2Vid ? MT_HD_IMAGE_PARAM_YPbPr1 : \
( emMtVideoPort == emMtC3Vid ? MT_HD_IMAGE_PARAM_YPbPr2 : \
( emMtVideoPort == emMtC4Vid ? MT_HD_IMAGE_PARAM_CVBS : MT_HD_IMAGE_PARAM_INVALID ) ) ) )

#define MT_AACLC_IDLE_CHAN_TYPE     (u8)1


// --------------- 组合键相关宏定义 --------------- 
#define MT_COMBINED_HELP_RED      0   // HELP(3s) + Red
#define MT_COMBINED_HELP_YLW      1   // HELP(3s) + YLW
#define MT_COMBINED_HELP_GRN      2   // HELP(3s) + GRN

// --------------- 网口模式宏定义 --------------- 
#define ETH_MODE_AUTO           (u32)0
#define ETH_MODE_10M_FULL       (u32)1
#define ETH_MODE_10M_HALF       (u32)2
#define ETH_MODE_100M_FULL      (u32)3
#define ETH_MODE_100M_HALF      (u32)4

// --------------- 高清制式宏定义 --------------- 
#define MT_HD_IMAGE_AUTOADJUST           (u32)0
#define MT_HD_IMAGE_ORIGINSIZE           (u32)1

// --------------- 图像参数调整的操作类型 ------------------
#define MT_SCALE_BRIGHTNESS     (u32)0 /* 设置亮度，  C | YPbPr */
#define MT_SCALE_CONTRAST       (u32)1 /* 设置对比度，C | YPbPr */
#define MT_SCALE_HUE            (u32)2 /* 设置色度，  C */
#define MT_SCALE_SATURATION     (u32)3 /* 设置饱和度，C | YPbPr */

// --------------- 远端近端操作类型 --------------- 
#define MT_DIALOG_PA           (u32)0 /*参数调节*/
#define MT_DIALOG_MC           (u32)1 /*移动摄像头*/
#define MT_DIALOG_CP           (u32)2 /*调整摄像头*/

// --------------- PCMT视频编解码方式设置 --------------- 
#define PCMT_VCODEC_SOFTWARE           (u8)0 /*软件编解码*/
#define PCMT_VCODEC_HARDWARE           (u8)1 /*硬件显卡编解码*/
#define PCMT_VENCODE                   (u8)0 /*编码*/
#define PCMT_VDECODE                   (u8)1 /*解码*/

// --------------- 高清1080P/i,720--帧率类型 --------------- 
#define MT_HD_ORIGIN					 (u32)0
#define MT_HD_1080p_24                   (u32)1
#define MT_HD_1080p_25                   (u32)2
#define MT_HD_1080p_30                   (u32)3
#define MT_HD_1080p_50					 (u32)4
#define MT_HD_1080p_60					 (u32)5
#define MT_HD_1080i_50                   (u32)6
#define MT_HD_1080i_60                   (u32)7
#define MT_HD_720p_50				     (u32)8
#define MT_HD_720p_60					 (u32)9
#define MT_576i_50						 (u32)10
#define MT_HD_1080p_29					 (u32)11
#define MT_HD_1080p_59					 (u32)12


// --------------- VGA--频率类型 --------------- 
#define MT_HD_VGA_60                     (u32)0
#define MT_HD_VGA_75                     (u32)1
#define MT_HD_SVGA_60					 (u32)2
#define MT_HD_SVGA_75					 (u32)3
#define MT_HD_XGA_60					 (u32)4
#define MT_HD_XGA_75					 (u32)5
#define MT_HD_SXGA_60					 (u32)6
#define MT_HD_WSXGA_60					 (u32)7
#define MT_HD_WXGA1280x768_60			 (u32)8
#define MT_HD_WXGA1280x768_75			 (u32)9
#define MT_HD_WXGA1280x800_60			 (u32)10
#define MT_HD_WXGA1280x800_75			 (u32)11
#define MT_HD_WXGA1360x768_60			 (u32)12
#define MT_HD_UXGA_60					 (u32)13
#define MT_HD_SXGAPLUS_60				 (u32)14


//-----------------蓝屏或上一帧------------------
#define MT_HD_LastFrame					 (u32)0
#define MT_HD_BlueScreen                 (u32)1

//-----------------是否弹出"申请发言"的控制框------------------
#define MT_UNPOP_CHAIRCONTROLDLG         (u32)0
#define MT_POP_CHAIRCONTROLDLG			 (u32)1

//mtcbox
#define SERIAL_232 (u8)0
#define SERIAL_485 (u8)1

//终端额外配置命令的类型部分定义
const u32 type_MtExtCfgCmdTypeBase = 0;
const u32 type_FullFrameMode       = type_MtExtCfgCmdTypeBase + 1;
const u32 type_MtVersion		   = type_MtExtCfgCmdTypeBase + 2;
const u32 type_VGAError			   = type_MtExtCfgCmdTypeBase + 3;
const u32 type_LastBlue			   = type_MtExtCfgCmdTypeBase + 4;//无视频源显示蓝屏或上一帧
//终端版本号，主要用于修改了某些结构体后Mtc无法兼容老终端
const u32 g_dwMtVersion = 1;
/*WIFI Macro definition END*/
//MT end.

/////////////////////////////////////////////////////////////////////////////
//////////////////////////用于cnagent模块////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
#define KDV_READ_COMMUNITYSTRING            	(LPCSTR)"public"
#define KDV_WRITE_COMMUNITYSTRING           	(LPCSTR)"kdv123"

#define	CN_TRAP_PORT                            162
#define	CN_GETSET_PORT                          161    

//CPU和内存检测参数
#define CN_GUARD_CPUADNMEM_TIMER                    6000
#define CN_GUARD_STATISTIC_TIMER                    6000
#define CN_CPU_MAX_VALUE                            100
#define CN_MEMORY_MAX_VALUE                         100
#define CN_MEMORY_SHIFT_VALUE                       16
#define CN_LOW16_MAX_VALUE                          0xFFFF
#define CN_MEMORY_UNIT                              1024

// 内存使用状态改变
// 使用率超过80%报警
const u32 CNMEMORYUESDCRITVAL = 80;

// cpu使用状态改变
// 使用率超过85%报警
const u32 CNCPUUSEDCRITVAL = 85;


//////////////////////////告警信息///////////////////////////////////////////
//系统状态
const u32  CNSYSSTATE_RUNNING   = 1;//系统运行
const u32  CNSYSSTATE_REBOOT	= 2;//系统重起
const u32  CNSYSSTATE_DOWN   = 3;//系统断电

//////////////////////////cns告警码///////////////////////////////////////////
#define ALARM_CN_BASE							10000L
#define ALARM_CN_CPUERROR						(ALARM_CN_BASE+1003L)   /*cpu出错*/
#define ALARM_CN_MEMORYERROR                    (ALARM_CN_BASE+1001L)   /*内存错误*/


/* MT告警对象类型 */
#define ALARMOBJ_CN_MAX                         4
#define ALARMOBJ_CN_BASE				        (u8)128
#define ALARMOBJ_CN                             (u8)(ALARMOBJ_CN_BASE + 1)

/////////////////////////////////////////////////////////////////////////////
//////////////////////////End////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
//////////////////////////用于cnconfig模块///////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

const int    CN_MAX_VIDEO_NUM           =   2 ;            //最多视频路数

//音频信息默认值
#define CN_DEFAULT_AUDIO_INPUTVOLUME                           16
#define CN_DEFAULT_AUDIO_OUTPUTVOLUME                           16

#define  CN_MAX_PRIOMVIDEO_1080P_FRAMERATE             60     //第一路视频对1080p最大帧率
#define  CN_MIN_VIDEO_1080P_FRAMERATE                  1      //视频对1080p最小帧率
#define  CN_DEFAULT_PRIOMVIDEO_7920_A_1080P_FRAMERATE  60     //第一路高清视频对1080p默认帧率
#define  CN_DEFAULT_PRIOMVIDEO_7920_A_720P_FRAMERATE   60     //第一路高清视频对720p默认帧率
#define  CN_DEFAULT_PRIOMVIDEO_1080P_FRAMERATE         25     //第一路视频对1080p默认帧率
#define  CN_DEFAULT_PRIOMVIDEO_720P_FRAMERATE          50     //第一路视频对720p默认帧率

#define	 CN_PRIMOVIVEO_H264IKEYRATE	     			   3000   //第一路视频H264关键帧间隔

#define  CN_MAX_SECONDVIDEO_1080P_FRAMERATE             31     //第二路视频对1080p最大帧率
#define  CN_DEFAULT_SECONDVIDEO_1080P_FRAMERATE  25     //第二路高清视频对1080p默认帧率
#define  CN_DEFAULT_SECONDVIDEO_720P_FRAMERATE   30     //第二路高清视频对720p默认帧率
// #define  CN_DEFAULT_SECONDVIDEO_1080P_FRAMERATE         25     //第二路视频对1080p默认帧率
// #define  CN_DEFAULT_SECONDVIDEO_720P_FRAMERATE          30     //第二路视频对720p默认帧率
#define	 CN_SECONDVIVEO_H264IKEYRATE				   2000    //第二路视频H264关键帧间隔

#define  CN_DEFAULT_VIDEO_VGA_FRAMERATE					20     //视频对VGA默认帧率
#define  CN_DEFAULT_VIDEO_D1_FRAMERATE					30     //视频对D1默认帧率

#define  CN_MIN_VIDEO_QUAL							   2      //最小量化参数
#define  CN_MAX_VIDEO_QUAL							   31      //最大量化参数
#define  CN_VIDEO_IKEYRATE                             300    //关键帧间隔

//图像调整参数
#define CN_DEFAULT_PRIOM_ADJUSTIMAGE_BRIGHTNESS           128    //亮度
#define CN_DEFAULT_PRIOM_ADJUSTIMAGE_CONTRAST             128    //对比度
#define CN_DEFAULT_PRIOM_ADJUSTIMAGE_SATURATION           128    //色彩饱和度

// #define CN_DEFAULT_PRIOM_ADJUSTIMAGE_BRIGHTNESS              128    //亮度
// #define CN_DEFAULT_PRIOM_ADJUSTIMAGE_CONTRAST                64    //对比度
// #define CN_DEFAULT_PRIOM_ADJUSTIMAGE_SATURATION              64    //色彩饱和度

#define CN_DEFAULT_SECOND_ADJUSTIMAGE_BRIGHTNESS              128    //亮度
#define CN_DEFAULT_SECOND_ADJUSTIMAGE_CONTRAST                128    //对比度
#define CN_DEFAULT_SECOND_ADJUSTIMAGE_SATURATION              128    //色彩饱和度


// --------------- 高清1080P/i,720--帧率类型 --------------- 
#define CN_HD_ORIGIN					 (u32)0
#define CN_HD_1080p_24                   (u32)1
#define CN_HD_1080p_25                   (u32)2
#define CN_HD_1080p_30                   (u32)3
#define CN_HD_1080p_50					 (u32)4//默认
#define CN_HD_1080p_60					 (u32)5
#define CN_HD_1080i_50                   (u32)6
#define CN_HD_1080i_60                   (u32)7
#define CN_HD_720p_50				     (u32)8
#define CN_HD_720p_60					 (u32)9
#define CN_576i_50						 (u32)10
#define CN_HD_1080p_29					 (u32)11
#define CN_HD_1080p_59					 (u32)12  
#define CN_HD_1080p_29_97				 (u32)13 //1080p 29.97fps
#define CN_HD_1080p_59_94				 (u32)14 //1080p 59.94fps

// --------------- VGA--频率类型 ---------------                
#define CN_HD_VGA_60                     (u32)0                 
#define CN_HD_VGA_75                     (u32)1                 
#define CN_HD_SVGA_60					 (u32)2 
#define CN_HD_SVGA_75					 (u32)3 
#define CN_HD_XGA_60					 (u32)4 
#define CN_HD_XGA_75					 (u32)5 
#define CN_HD_SXGA_60					 (u32)6 
#define CN_HD_WSXGA_60					 (u32)7 
#define CN_HD_WXGA1280x768_60			 (u32)8         
#define CN_HD_WXGA1280x768_75			 (u32)9         
#define CN_HD_WXGA1280x800_60			 (u32)10        
#define CN_HD_WXGA1280x800_75			 (u32)11        
#define CN_HD_WXGA1360x768_60			 (u32)12                                        
#define CN_HD_UXGA_60					 (u32)13                                
#define CN_HD_SXGAPLUS_60				 (u32)14
#define CN_HD_WXGA1366x768_60			 (u32)15  

//HD终端的视频输出口个数
const int    CN_HD_MAX_AV_OUTPORT_NUM  = 4;            //高清终端的最大视频输出口的个数

const int    CN_VIDEO_OUTPORT_NUM          = 4;    
const int    CN_INNERMATRIX_SCHEME_NUM     = 8;
const u32    CN_DVI_PORT_NUM               = 6;    

const u8     CN_ExVideoMoudle_None = 0;
const u8     CN_ExVideoMoudle_SDII = 1;
const u8     CN_ExVideoMoudle_SDIO = 2;

const u8     CN_DVI_MODE_HDMI  = 0;
const u8     CN_DVI_MODE_DVI  = 1;
const u8     CN_DVI_MODE_YPBPR = 2;
const u8     CN_DVI_MODE_VGA   = 3;

//显示信息
#define	CN_WIN32_DEFAULT_SYMBOLPOINT_X                 20   //台标的X位置
#define	CN_WIN32_DEFAULT_SYMBOLPOINT_Y                 10   //台标的Y位置

#define	CN_LINUX_DEFAULT_SYMBOLPOINT_X                 76   //台标的X位置
#define	CN_LINUX_DEFAULT_SYMBOLPOINT_Y                 56   //台标的Y位置

#define CN_VGAOUTCFG_REFRESHRATE                       75   //8010c输出到vga或者video,及刷新率

//FEC配置
#define CN_FEC_CRCPACKNUM                              1  //fec的y包冗余包
#define CN_FEC_DATAPACKNUM                             6  //fec的x包数据包
#define CN_FEC_PACKLEN                                1408  //fec的切包长度

//-----------------蓝屏或上一帧------------------
#define CN_HD_LastFrame					 (u32)0
#define CN_HD_BlueScreen                 (u32)1

#define CN_HD_BLUESCREEN_WAITTIME         5

//丢包重传参数
//T2版本
// #define	CN_INTERNET_LOSTPACKRESEND_FIRSTTIMESPAN    40       //第一个重传检测点   default 40
// #define CN_INTERNET_LOSTPACKRESEND_REJECTTIMESPAN   480         //过期丢弃的时间跨度 
// #define CN_INTERNET_LOSTPACKRESEND_SECONDTIMESPAN   120         //第二个重传检测点
// #define CN_INTERNET_LOSTPACKRESEND_THIRDTIMESPAN    240         //第三个重传检测点
// #define CN_INTERNET_LOSTPACKRESEND_SENDBUFTIMESPAN  1500        //发送缓存

#define	CN_LOSTPACKRESEND_FIRSTTIMESPAN    40       //第一个重传检测点   default 40
#define CN_LOSTPACKRESEND_REJECTTIMESPAN   480         //过期丢弃的时间跨度 
#define CN_LOSTPACKRESEND_SECONDTIMESPAN   120         //第二个重传检测点
#define CN_LOSTPACKRESEND_THIRDTIMESPAN    240         //第三个重传检测点
#define CN_LOSTPACKRESEND_SENDBUFTIMESPAN  1500        //发送缓存

#define	CN_DEFAULT_AUDIO_FILTERRATE         20         //音频的低通、高通的滤波

//长度定义
const int    CN_MAX_LDAPSERVER_NAME_LEN   =  100;          //LDAP服务器域名的最大长度
const int    CN_MAX_H323ALIAS_LEN       =   64;            // 终端别名最大长度
const int    CN_MAX_E164NUM_LEN         =   16;            // 终端E164最大长度
const int    CN_MAX_UPDATASERVER_NAME_LEN =  64;           //升级服务器的域名的最大长度
const int    CN_MAXNUM_CALLADDR_RECORD  =   5;             //最大呼叫地址记录数

//卡农麦克的数量
#define  CN_MIC_CANONIN_NUM                  10



//Add by tanxiaodong 2012-12-22
//维护工具中获取网络上下行速率宏定义
#define NETINFO_PATH_IN_LINUX "/proc/net/dev"
#define NET_INFO_MAX_NUM     256
#define NET_ELEMENT_NUM      20
#define TRANSFER_BASE_NUM    10
#define NET_INFO_LINE_NUM    4

//维护工具中演示源输出接口的宏定义
#define DEMO_OUTPUT_NAME_FST     "演示屏1"
#define DEMO_OUTPUT_NAME_SND     "演示屏2"
//End to add.
                        
const int    AID_CNMP_BEGIN        =   AID_MT_BGN;                        
const int    AID_CNMP_UE		     =	 AID_CNMP_BEGIN + 4;    	//业务接口实体    


//定义最大的用户数目
#define MAX_USERNUM		128
#define MAX_CHARLENGTH		32

//Modified by tanxiaodong 2012-11-29.
//CNS连接的TPad个数现在最多为16个
//#define MAX_CNC_USER 16

//设置台标时的固定参数值

#define BANNER_BPM576_WIDTH    720  
#define BANNER_BPM576_HEIGHT   576

#define BANNER_BPM720_WIDTH    1280  
#define BANNER_BPM720_HEIGHT   720
#define BANNER_LOGO720_XPOS    67
#define BANNER_LOGO720_YPOS    50

#define BANNER_BPM1080_WIDTH   1920  
#define BANNER_BPM1080_HEIGHT  1080
#define BANNER_LOGO1080_XPOS    102
#define BANNER_LOGO1080_YPOS    76

#define BANNER_LOGO_BCOLOR  0
#define BANNER_LOGO_RCOLOR  255
#define BANNER_LOGO_GCOLOR  235
#define BANNER_LOGO_TRANSPARENCY  255
//上下行速率的字节计数值
#define NET_SPEED_BYTE_BASE_NUM  2048

//End of the modification.

//终端型号
const u32  TPSYSHARDWARETYPE_UNKNOWNMTMODEL   = 0;//(u32)emUnknownMtModel ;
const u32  TPSYSHARDWARETYPE_7920           = 27;//(u32)em7920_A ;  


// --------------- 视频默认参数--------------- 
const u32 TP_VIDEO_PRIOME_FRAMERATE_DEFAULT = 60; //视频帧率
const u32 TP_VIDEO_MINI_FRAMERATE_DEFAULT = 30;
const u32 TP_VIDEO_MAX_KEYFRAMEINTERVER_DEFAULT = 3000; 
const u32 TP_VIDEO_PRIOM_MAX_CHANBITRATE = 8192;
const u32 TP_VIDEO_MINI_MAX_CHANBITRATE = 4096;
const u32 TP_VIDEO_MAX_QUANT_DEFAULT = 40;
const u32 TP_VIDEO_MIN_QUANT_DEFAULT = 20;
const u32 TP_VIDEO_WIDTH_DEFAULT = 1920;   
const u32 TP_VIDEO_HEIGHT_DEFAULT = 1080;
const u32 TP_VIDEO_PROFILE_DEFAULT = 1;
const u32 TP_VIEDO_AVGQPI_DEFAULT = 28;
const u32 TP_VIEDO_AVGQPP_DEFAULT = 28;
const u32 TP_VIDEO_DUAL_MAX_CHANBITRATE = 4096;
const u32 TP_VIDEO_DUAL_FRAMERATE_DEFAULT = 60;
const u32 TP_VIDEO_PRIOM_CAPEMRES_DEFAULT = 13;
const u32 TP_VIDEO_PRIOM_WXGACAPRES_DEFAULT = 20;
const u32 TP_VIDEO_DUAL_CAPEMRES_DEFAULT = 13;
const u32 TP_VIDEO_DUAL_WXGACAPRES_DEFAULT = 20;
const u32 TP_PADKEYFRAME_TIMER_DEFAULT = 30;
const u32 TP_PIPTIMER_DEFAULT = 6;
const u32 TP_VIDEO_PRIOM_DEFAULT_CHANBITRATE_HP = 2048;
const u32 TP_VIDEO_PRIOM_DEFAULT_CHANBITRATE = 2048;
const u32 TP_VIDEO_DUAL_DEFAULT_CHANBITRATE = 2048;

#define MEDIA_NUM                   2

#define TP_MAX_LOGOBMP_SIZE                153600 


const u16 TP_SERVER_PORT_DEFAULT = 5060;

//add for vcs
const u8 TP_MAX_VOLUME = 32;
const u8 TP_MCU_MAX_VOLUME = 248;
//end

#define TP_SAFE_DELETE( p ) if ( p != NULL ) { delete p; p = NULL; }
#define TP_SAFE_DELETE_ARRAY( p ) if ( p != NULL ) { delete []p; p = NULL; }

//t300默认会场名
#define TP_MAINROOM_DEFAULT           "KEDACOM"
#define TP_ETHNET_IP_DEFAULT          "192.169.0.1"
#define TP_ETHNET_MAST_DEFAULT        "255.0.0.0"
#define TP_ETHNET_GATEWAY_DEFAULT     "0.0.0.0"


// --------------- 会议参数--------------- 
const u16 TP_CONF_POLLEXPIRE = 20; //会议轮询间隔

#define TP_PRIMCHANNEL_CONNECT_DELAY_TIME 500

#define TP_CREATE_VIDEO_CODEC_DELAY_TIME  100

//moon

//moon连接的三眼摄像机控制台个数现在最多为1个
#define MAX_CNC_USER 1

//默认ip信息设置
#define TP_ETHNET_MOONIP_DEFAULT          "192.169.0.100"
#define TP_ETHNET_MOONMAST_DEFAULT        "255.255.0.0"
#define TP_ETHNET_MOONGATEWAY_DEFAULT     "0.0.0.0"

const u16 TP_MOON_ZOOM_VALUE = 300;
const u16 TP_MOON_WHITEBALANCE_RVALUE = 195;
const u16 TP_MOON_WHITEBALANCE_BVALUE = 190;
const u16 TP_MOON_IMAGE_VALUE = 100;
const u16 TP_MOON_CORRECT = 2048;
const u16 TP_MOON_90HSTRETCH = 1024;
const u16 TP_MOON_90STRETCH = 0;
const u32 TP_MOON_HORIZON_VALUE = 5;
const u32 TP_MOON_VERTICAL_RVALUE = 6;
const u32 TP_MOON_VERTICAL_LVALUE = 2;

//add by youjx 2016.11.7
const u16 TP_MOON_H650_ZOOM_VALUE = 340;
const u16 TP_MOON_H650_ZOOMPOS = 4570;
const u16 TP_MOON_H650_WHITEBALANCE_RVALUE = 115;
const u16 TP_MOON_H650_WHITEBALANCE_BVALUE = 135;
const u16 TP_MOON_BRIGHT_VALUE = 100;
const u16 TP_MOON_CONTRAST_VALUE = 100;
const u16 TP_MOON_SATURAT_VALUE = 100;
const u16 TP_MOON_SHARP_VALUE = 100;
const u32 MOON_H650_BAUD_RATE_DEFAULT = 115200;
const u32 MOON_SONY_BAUD_RATE_DEFAULT = 9600;
const u32 TP_MOON_RED_COEFF = 1000;
const u32 TP_MOON_BLUE_COEFF = 1000;
const u32 TP_MOON_GREEN_COEFF = 1000;
/********第一个矩形区域默认位置***************/
const u32 MOON_0RECT_DEFAULT_X_COORDINATE = 1758;       //1080p对应界面293
const u32 MOON_0RECT_DEFAULT_Y_COORDINATE = 72;         //1080p对应界面12

const u32 MOON_0RECT_DEFAULT_X_COORDINATE_720P = 1172;  //720p对应界面293
const u32 MOON_0RECT_DEFAULT_Y_COORDINATE_720P = 48;    //720p对应界面12
/********第二个矩形区域默认位置***************/
const u32 MOON_1RECT_DEFAULT_X_COORDINATE = 66;         //1080p对应界面11
const u32 MOON_1RECT_DEFAULT_Y_COORDINATE = 72;         //1080p对应界面12

const u32 MOON_1RECT_DEFAULT_X_COORDINATE_720P = 44;    //720p对应界面11
const u32 MOON_1RECT_DEFAULT_Y_COORDINATE_720P = 48;    //720p对应界面12
/********第三个矩形区域默认位置***************/
const u32 MOON_2RECT_DEFAULT_X_COORDINATE = 1758;       //1080p对应界面293
const u32 MOON_2RECT_DEFAULT_Y_COORDINATE = 72;         //1080p对应界面12

const u32 MOON_2RECT_DEFAULT_X_COORDINATE_720P = 1172;  //720p对应界面293
const u32 MOON_2RECT_DEFAULT_Y_COORDINATE_720P = 48;    //720p对应界面12
/********第四个矩形区域默认位置***************/
const u32 MOON_3RECT_DEFAULT_X_COORDINATE = 66;         //1080p对应界面11
const u32 MOON_3RECT_DEFAULT_Y_COORDINATE = 72;         //1080p对应界面12

const u32 MOON_3RECT_DEFAULT_X_COORDINATE_720P = 44;    //720p对应界面11
const u32 MOON_3RECT_DEFAULT_Y_COORDINATE_720P = 48;    //720p对应界面12
/********矩形区域默认长和宽*******************/
const u32 MOON_RECT_DEFAULT_LENGTH = 96;                //1080p对应界面16
const u32 MOON_RECT_DEFAULT_WIDTH = 96;                 //1080p对应界面16

const u32 MOON_RECT_DEFAULT_LENGTH_720P = 64;           //720p对应界面16
const u32 MOON_RECT_DEFAULT_WIDTH_720P = 64;            //720p对应界面16

const u32 MOON_DISTORT_DEFAULT_STRECH = 0;
const u32 MOON_DISTORT_DEFAULT_ROTATE = 150;
//add end

//end
#endif