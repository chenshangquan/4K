#ifndef _VCCOMMON_040602_H_
#define _VCCOMMON_040602_H_

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "kdvtype.h"
#include "kdvdef.h"


#ifdef _LINUX_

#ifndef min
#define min(a,b) ((a)>(b)?(b):(a))
#endif
#ifndef max
#define max(a,b) ((a)>(b)?(a):(b))
#endif

#endif//!_LINUX_

///////////////////////////////// KDV 版本号 ///////////////////////////////////////
//
#define KDVVC_VERID                  (u8*)"9"
#define LEN_KDVVC_VERID              strlen((s8*)KDVVC_VERID)
//
////////////////////////////////////////////////////////////////////////////////////

//设备主类定义
#define		TYPE_MCU                     	 1   //MCU
#define		TYPE_MCUPERI                     2   //MCU外设
#define		TYPE_MT                          3   //终端

//MCU类型定义
#define		MCU_TYPE_KDV8000                 1   //MCU类型8000
#define		MCU_TYPE_KDV8000B                2   //MCU类型8000B
#define		MCU_TYPE_WIN32                   3   //MCU类型WIN32
#define		MCU_TYPE_KDV8000B_HD             4   //MCU类型8000B-HD
#define     MCU_TYPE_KDV8000C                101 //MCU类型8000C

//MCU产品名称
#define		PRODUCT_MCU_STANDARD            (s8*)"KDC MCU"
#define		PRODUCT_MCU_8000C				(s8*)"KDC MCU-8000C"

//视频格式定义
#define     VIDEO_FORMAT_INVALID            255
#define		VIDEO_FORMAT_SQCIF				1   //SQCIF(128*96)
#define		VIDEO_FORMAT_QCIF				2   //SCIF(176*144)
#define		VIDEO_FORMAT_CIF                3   //CIF(352*288)  - P制
#define     VIDEO_FORMAT_2CIF               4   //2CIF(352*576) - p
#define		VIDEO_FORMAT_4CIF               5   //4CIF(704*576) - P制(H264下此宏指代D1(720*576)   - P制（N制D1：720*480）)
#define		VIDEO_FORMAT_16CIF				6   //16CIF(1408*1152)
#define		VIDEO_FORMAT_AUTO				7   //自适应，仅用于MPEG4

#define		VIDEO_FORMAT_SIF                8   //SIF(352*240)  - N制
#define     VIDEO_FORMAT_2SIF               9   //2SIF
#define		VIDEO_FORMAT_4SIF               10  //4SIF(704*480) - N制

#define     VIDEO_FORMAT_VGA                11  //VGA(640*480)
#define		VIDEO_FORMAT_SVGA               12  //SVGA(800*600)
#define		VIDEO_FORMAT_XGA                13  //XGA(1024*768)
#define     VIDEO_FORMAT_WXGA               14  //WXGA(1280*768 | 1280*800)

                                                //仅用于终端分辨率改变
#define		VIDEO_FORMAT_SQCIF_112x96       21  //SQCIF(112*96)
#define		VIDEO_FORMAT_SQCIF_96x80        22  //SQCIF(96*80)

                                                // 高清分辨率
#define     VIDEO_FORMAT_W4CIF              31  //Wide 4CIF(1024*576)
#define     VIDEO_FORMAT_HD720              32  //720 1280*720
#define     VIDEO_FORMAT_SXGA               33  //SXGA 1280*1024
#define     VIDEO_FORMAT_UXGA               34  //UXGA 1600*1200
#define     VIDEO_FORMAT_HD1080             35  //1080  1920*1088(p) 1920*544(i)

                                                //非标分辨率（1080p底图）－用于终端分辨率改变
#define     VIDEO_FORMAT_1440x816           41  //1440×816(3/4)
#define     VIDEO_FORMAT_1280x720           42  //1280×720(2/3)
#define     VIDEO_FORMAT_960x544            43  // 960×544(1/2)
#define     VIDEO_FORMAT_640x368            44  // 640×368(1/3)
#define     VIDEO_FORMAT_480x272            45  // 480×272(1/4)

                                                //非标分辨率（720p底图） －用于终端分辨率改变
#define     VIDEO_FORMAT_720_960x544        51  //960×544(3/4)
#define     VIDEO_FORMAT_720_864x480        52  //864×480(2/3)
#define     VIDEO_FORMAT_720_640x368        53  //640×368(1/2)
#define     VIDEO_FORMAT_720_432x240        54  //432×240(1/3)
#define     VIDEO_FORMAT_720_320x192        55  //320×192(1/4)

//上层视频帧率定义(用于非H.264，H.264直接用VIDEO_FPS_USRDEFINED+数值表示帧率)
#define     VIDEO_FPS_2997_1                1   //30 帧/s
#define     VIDEO_FPS_25                    2   //25 帧/s(底层按30帧处理)
#define     VIDEO_FPS_2997_2                3   //15 帧/s
#define     VIDEO_FPS_2997_3                4   //10 帧/s
#define     VIDEO_FPS_2997_4                5   //7.5帧/s
#define     VIDEO_FPS_2997_5                6   //6  帧/s
#define     VIDEO_FPS_2997_6                7   //5  帧/s
#define     VIDEO_FPS_2997_30               8   //1  帧/s
#define     VIDEO_FPS_2997_7P5              9   //4  帧/s
#define     VIDEO_FPS_2997_10               10  //3  帧/s
#define     VIDEO_FPS_2997_15               11  //2  帧/s
#define     VIDEO_FPS_USRDEFINED            128 //自定义帧率(>=128,减去128即为实际帧率)

//视频双流类型定义
#define		VIDEO_DSTREAM_H263PLUS			0   //H263＋
#define		VIDEO_DSTREAM_MAIN				1   //与主视频格式一致
#define		VIDEO_DSTREAM_H263PLUS_H239     2   //H263＋的H239
#define		VIDEO_DSTREAM_H263_H239         3   //H263的H239
#define		VIDEO_DSTREAM_H264_H239         4   //H264的H239
#define     VIDEO_DSTREAM_H264              5   //H264
#define     VIDEO_DSTREAM_H264_H263PLUS_H239    6   //H264 & H263+ 的H239

//会议创建方式
#define		CONF_CREATE_MT                  201 //会议由终端创建
#define		CONF_CREATE_SCH                 202 //会议由预约会议创建
#define		CONF_CREATE_MCS                 0   //会议由会控创建
#define     CONF_CREATE_NPLUS               203 //会议由N+1备份创建，此标识在mcu创会时不保存到文件，即不进行会议恢复

//会议开放方式定义
#define		CONF_OPENMODE_CLOSED             0  //不开放,拒绝列表以外的终端
#define		CONF_OPENMODE_NEEDPWD            1  //根据密码加入
#define		CONF_OPENMODE_OPEN               2  //完全开放 

//会议加密方式定义
#define     CONF_ENCRYPTMODE_NONE            0 //不加密
#define     CONF_ENCRYPTMODE_DES             1 //des加密
#define     CONF_ENCRYPTMODE_AES             2 //aes加密

//会议码流转发时是否支持归一化整理方式定义, 与丢包重传方式以及加密方式互斥
#define     CONF_UNIFORMMODE_NONE            0 //不归一化重整
#define     CONF_UNIFORMMODE_VALID           1 //  归一化重整

#define     SWITCHCHANNEL_UNIFORMMODE_NONE   0 //不归一化重整
#define     SWITCHCHANNEL_UNIFORMMODE_VALID  1 //  归一化重整

#define     INVALID_PAYLOAD                  0xFF


//数据会议方式定义
#define		CONF_DATAMODE_VAONLY             0  //不包含数据的视音频会议
#define		CONF_DATAMODE_VAANDDATA          1  //包含数据的视音频会议
#define		CONF_DATAMODE_DATAONLY           2  //不包含视音频的数据会议

//会议结束方式定义
#define     CONF_RELEASEMODE_NONE            0  //不会自动结束
#define     CONF_RELEASEMODE_NOMT            1  //无终端时自动结束

//会议进行方式
#define     CONF_TAKEMODE_SCHEDULED          0  //预约会议
#define     CONF_TAKEMODE_ONGOING            1  //即时会议
#define     CONF_TAKEMODE_TEMPLATE           2  //会议模板

//会议保护方式
#define		CONF_LOCKMODE_NONE               0  //未保护
#define		CONF_LOCKMODE_NEEDPWD            1  //根据密码操作
#define		CONF_LOCKMODE_LOCK               2  //独享 

//发言人的源的定义
#define		CONF_SPEAKERSRC_SELF             0  //看自己
#define		CONF_SPEAKERSRC_CHAIR            1  //看主席
#define		CONF_SPEAKERSRC_LAST             2  //看上一次发言人

//呼叫终端方式定义
#define		CONF_CALLMODE_NONE               0  //手动呼叫
#define		CONF_CALLMODE_TIMER              2  //定时呼叫

//定时呼叫终端时间间隔定义
#define		DEFAULT_CONF_CALLINTERVAL        20 //缺省的定时呼叫间隔（秒）
#define		MIN_CONF_CALLINTERVAL            10 //最小的定时呼叫间隔（秒）

//定时呼叫终端呼叫次数定义
#define		DEFAULT_CONF_CALLTIMES           0  //无穷次定时呼叫次数
#define		MIN_CONF_CALLTIMES               2  //最小的定时呼叫次数

//画面合成方式定义
#define		CONF_VMPMODE_NONE                0  //不进行画面合成
#define		CONF_VMPMODE_CTRL                1  //会控或主席选择成员合成
#define		CONF_VMPMODE_AUTO                2  //MCU自动选择成员合成

//复合电视墙合成方式定义
#define		CONF_VMPTWMODE_NONE              0  //不进行画面合成
#define		CONF_VMPTWMODE_CTRL              1  //会控或主席选择成员合成
#define		CONF_VMPTWMODE_AUTO              2  //MCU自动选择成员合成

//会议录像方式定义 
#define		CONF_RECMODE_NONE                0  //不录像
#define		CONF_RECMODE_REC                 1  //录像
#define		CONF_RECMODE_PAUSE               2  //暂停

//会议放像方式定义
#define		CONF_PLAYMODE_NONE               0  //不放像
#define		CONF_PLAYMODE_PLAY               1  //放像
#define		CONF_PLAYMODE_PAUSE              2  //暂停
#define		CONF_PLAYMODE_FF                 3  //快进
#define		CONF_PLAYMODE_FB                 4  //快退
#define		CONF_PLAYMODE_PLAYREADY			 5	//准备放像

//会议轮询方式定义
#define		CONF_POLLMODE_NONE               0  //不轮询广播 
#define		CONF_POLLMODE_VIDEO              1  //仅图像轮询广播
#define		CONF_POLLMODE_SPEAKER            2  //轮流发言

//码率适配方式定义 -- modify bas 2
#define		CONF_BASMODE_NONE                0  //不进行码率适配
#define		CONF_BASMODE_AUD                 1  //音频适配
#define		CONF_BASMODE_VID                 2  //视频适配
#define		CONF_BASMODE_BR                  3  //码率适配
#define		CONF_BASMODE_CASDAUD             4  //级联回传音频适配
#define		CONF_BASMODE_CASDVID             5  //级联回传视频适配

//高清适配方式定义
#define		CONF_HDBASMODE_NONE                0  //不进行高清适配适配
#define		CONF_HDBASMODE_VID                 1  //高清主视频适配
#define		CONF_HDBASMODE_DOUBLEVID           2  //双流适配
#define		CONF_HDBASMODE_CASDVID             3  //级联回传视频适配

//会议混音方式的定义
#define     CONF_MIXMODE_NONE                0  //不混音
#define     CONF_MIXMODE_DISC                1  //全体混音
#define     CONF_MIXMODE_SPEC                2  //定制混音
#define     CONF_MIXMODE_VAC                 3  //语音激励

//会议双流发起方式定义
#define		CONF_DUALMODE_SPEAKERONLY		 0	//只能发言人发起
#define		CONF_DUALMODE_EACHMTATWILL		 1	//任意终端都能发起

//轮询状态定义
#define		POLL_STATE_NONE                  0  //未轮询 
#define		POLL_STATE_NORMAL                1  //轮询正常
#define		POLL_STATE_PAUSE                 2  //轮询暂停

//画面合成状态定义
#define     VMP_STATE_START                  1  //开始
#define     VMP_STATE_CHANGE                 2  //改变
#define     VMP_STATE_STOP                   3  //停止

//复合电视墙合成状态定义
#define     VMPTW_STATE_START                1  //开始
#define     VMPTW_STATE_CHANGE               2  //改变
#define     VMPTW_STATE_STOP                 3  //停止

//电视墙状态定义
#define     TW_STATE_START                  1  //开始
#define     TW_STATE_CHANGE                 2  //改变
#define     TW_STATE_STOP                   3  //停止

//电视墙成员类型定义
#define     TW_MEMBERTYPE_NULL               0  //VCS指定成员为空，不可用该通道
#define		TW_MEMBERTYPE_MCSSPEC            1  //会控指定 
#define		TW_MEMBERTYPE_SPEAKER            2  //发言人跟随
#define		TW_MEMBERTYPE_CHAIRMAN           3  //主席跟随
#define		TW_MEMBERTYPE_POLL               4  //轮询视频跟随
#define		TW_MEMBERTYPE_TWPOLL             5	//电视墙轮询
#define     TW_MEMBERTYPE_SWITCHVMP          6  //选看vmp
#define     TW_MEMBERTYPE_BATCHPOLL          7  //批量轮询
#define     TW_MEMBERTYPE_VCSAUTOSPEC        8  //VCS自动指定 

//画面合成成员类型定义
#define		VMP_MEMBERTYPE_MCSSPEC           1  //会控指定 
#define		VMP_MEMBERTYPE_SPEAKER           2  //发言人跟随
#define		VMP_MEMBERTYPE_CHAIRMAN          3  //主席跟随
#define		VMP_MEMBERTYPE_POLL              4  //轮询视频跟随
#define		VMP_MEMBERTYPE_VAC               5	//语音激励(会控不要用此类型)

//画面合成风格定义
#define		VMP_STYLE_DYNAMIC                0   //动态分屏(仅自动合成时有效)
#define		VMP_STYLE_ONE                    1   //一画面
#define		VMP_STYLE_VTWO                   2   //两画面：左右分 
#define		VMP_STYLE_HTWO                   3   //两画面: 一大一小
#define		VMP_STYLE_THREE                  4   //三画面
#define		VMP_STYLE_FOUR                   5   //四画面
#define		VMP_STYLE_SIX                    6   //六画面 
#define		VMP_STYLE_EIGHT                  7   //八画面
#define		VMP_STYLE_NINE                   8   //九画面
#define		VMP_STYLE_TEN                    9   //十画面
#define		VMP_STYLE_THIRTEEN               10  //十三画面
#define		VMP_STYLE_SIXTEEN                11  //十六画面
#define		VMP_STYLE_SPECFOUR               12  //特殊四画面 
#define		VMP_STYLE_SEVEN                  13  //七画面
#define		VMP_STYLE_TWENTY				 14  //二十画面
#define     VMP_STYLE_NONE                  0xff //不支持的格式

//复合电视墙合成成员类型定义
#define		VMPTW_MEMBERTYPE_MCSSPEC         1  //会控指定 
#define		VMPTW_MEMBERTYPE_SPEAKER         2  //发言人跟随
#define		VMPTW_MEMBERTYPE_CHAIRMAN        3  //主席跟随
#define		VMPTW_MEMBERTYPE_POLL            4  //轮询视频跟随
#define		VMPTW_MEMBERTYPE_VAC             5	//语音激励(会控不要用此类型)

//逻辑通道相关定义
#define      LOGCHL_VIDEO					1	//主视频逻辑通道
#define      LOGCHL_AUDIO					2	//音频逻辑通道
#define      LOGCHL_SECVIDEO				3	//第二视频逻辑通道
#define      LOGCHL_T120DATA				4	//T120数据逻辑通道
#define      LOGCHL_H224DATA				5	//H224数据逻辑通道
#define      LOGCHL_MMCUDATA                6   //级联数据逻辑通道
#define      LOGCHL_VIDEO_BOTH              7   //主视频+第二视频逻辑通道

#define		MAXLEN_ALIAS			        128  //MCU或终端假名最多127个字母，63个汉字
#define     VALIDLEN_ALIAS                  16   //有效别名它度
#define		MAXLEN_CONFNAME                 64   //会议名最大长度
#define		MAXLEN_PWD                      32   //最大密码长度  
 
#define		MAXLEN_E164                     16   //最大E164号码长度 
#define     MAXLEN_KEY                      16   //最大的加密key长度
#define     MAXLEN_SW_VER                   32   //最大软件版本号长度

//conf id len
#define     MAXLEN_CONFID                   16
#define     LOCAL_MCUID                     192  //本地MCU ID 

#define     MAXNUM_PERIEQP_CHNNL			16	//电视墙通道最大数
#define     MAXNUM_MIXER_DEPTH				10  //混音器最大混音深度
#define     MAXNUM_MIXER_DEPTH_8000B        8   //8000B混音器最大混音深度
#define     MAXNUM_MIXER_DEPTH_8000B_G729   4   //8000B G.729混音器最大混音深度
#define     MAXNUM_VMP_MEMBER				20  //最大画面合成成员数
#define     MAXNUM_SDVMP_MEMBER             16
#define     MAXNUM_MPUSVMP_MEMBER			20  //SVMP最大画面合成成员数(从16增加到20)
#define     MAXNUM_MPUDVMP_MEMBER			9 

//双流百分比最大最小值
#define     MAXNUM_DSTREAM_SCALE            90
#define     MINNUM_DSTREAM_SCALE            10
#define     DEF_DSTREAM_SCALE               30

//终端板类型
//注意：该部分定义永远只能增加，且必须保持行业/企业流一致
#define     MT_BOARD_UNKNOW                 255
#define     MT_BOARD_WIN                    0

// KDV系列终端：1-49
#define     MT_BOARD_8010                   1
#define     MT_BOARD_8010A                  2
#define     MT_BOARD_8018                   3
#define     MT_BOARD_IMT                    4
#define     MT_BOARD_8010C                  5

#define     MT_BOARD_8010A_2                7
#define     MT_BOARD_8010A_4                8
#define     MT_BOARD_8010A_8                9

#define     MT_BOARD_7210                   10
#define     MT_BOARD_7610                   11
#define     MT_BOARD_7810                   12
#define     MT_BOARD_7910                   13

#define		MT_BOARD_5610_KDV				14
#define		MT_BOARD_6610_KDV				15

//KDV-二代高清系列
// #define     MT_BOARD_7820_A                 18
// #define     MT_BOARD_7820_B                 19
// #define     MT_BOARD_7920_A                 20
// #define     MT_BOARD_7920_B                 21

#define     MT_BOARD_7820_A_NOSDI           18
#define     MT_BOARD_7820_B_NOSDI           19
#define     MT_BOARD_7920_A_NOSDI           20
#define     MT_BOARD_7920_B_NOSDI           21

#define     MT_BOARD_7820_A_SDIINOUT        22
#define     MT_BOARD_7820_B_SDIINOUT        23
#define     MT_BOARD_7920_A_SDIINOUT        24
#define     MT_BOARD_7920_B_SDIINOUT        25
#define     MT_BOARD_7820_A_SDIININ         26
#define     MT_BOARD_7820_B_SDIININ         27
#define     MT_BOARD_7920_A_SDIININ         28
#define     MT_BOARD_7920_B_SDIININ         29

#define     MT_BOARD_7920_L        30

//KDV-三代高清系列
#define     MT_BOARD_H600_LB				31
#define     MT_BOARD_H600_B					32
#define     MT_BOARD_H600_C					33
#define     MT_BOARD_H700_A					34
#define     MT_BOARD_H700_B					35
#define     MT_BOARD_H700_C					36
#define     MT_BOARD_H900_A_NOSDI			37
#define     MT_BOARD_H900_A_SDIINOUT        38
#define     MT_BOARD_H900_A_SDIININ         39
#define     MT_BOARD_H900_B_NOSDI			40
#define     MT_BOARD_H900_B_SDIINOUT        41
#define     MT_BOARD_H900_B_SDIININ         42
#define     MT_BOARD_H900_C_NOSDI			43
#define     MT_BOARD_H900_C_SDIINOUT        44
#define     MT_BOARD_H900_C_SDIININ         45
#define     MT_BOARD_H600_LC				46
#define     MT_BOARD_H800_A					47
#define     MT_BOARD_H800_B					48
#define     MT_BOARD_H800_C					49


#define     MT_BOARD_KDVx_END               50



//KDV-T3系列
#define     MT_BOARD_7620_A                 16
#define     MT_BOARD_7620_B                 17

#define     MT_BOARD_KDVx_END               50
// TS系列：在 51-99 范围中
#define     MT_BOARD_6610                   51
#define     MT_BOARD_6610E                  52
#define     MT_BOARD_6210                   53
#define     MT_BOARD_5210                   54
#define     MT_BOARD_3210                   55 
#define     MT_BOARD_V5                     56

#define     MT_BOARD_3610                   57
#define     MT_BOARD_5610                   58
#define     MT_BOARD_6210E                  59

#define     MT_BOARD_TSx_END                100

// 为保证兼容 V系列和TS系列并列定义
// V系列：在 101-150 范围中
// #define     MT_BOARD_V5                     101

#define     MT_BOARD_Vx_END                 150

// GK用户名和密码长度宏定义
#define     MAX_LEN_GK_USRNAME              (u8)16
#define     MAX_LEN_GK_PWD                  (u8)16

// 音量类型宏定义
#define     VOLUME_TYPE_OUT                 (u8)0   //终端输出音量
#define     VOLUME_TYPE_IN                  (u8)1   //终端输入音量

// MCU前向纠错能力集类型
#define		FECTYPE_NONE					(u8)(0x00)
#define		FECTYPE_RAID5					(u8)(0x01)
#define		FECTYPE_RAID6					(u8)(0x02)

//会议发起方类型
#define    MCS_CONF                         (u8)0   //MCS召开的会议
#define    VCS_CONF							(u8)1   //VCS召开的会议
#define    ALL_CONF							(u8)2   //所有发起方的会议

#define    MAX_VCSSOFTNAME_LEN          (u8)64

// 开关常量
enum SwitchConstant
{
	turn_on,		//开启
	turn_off		//关闭
};

// 轮询类型
enum PollType
{
	poll_none,		//没有轮询
	poll_vcb,		//轮流广播
	poll_vcs		//轮流选看
};

enum PollStatus
{
	poll_status_none,    //未轮询
	poll_status_normal,  //轮询进行中
	poll_status_pause    //轮询暂停
};

//操作类型宏定义
enum OprType
{
    opr_start,
    opr_stop
};

//MCU发向终端的自定义通知消息 消息体号定义
enum Mcu2MtNtfMsgType
{
    emNoneNtf           = 0,
    emBePolledNextNtf   = 1           //即将被轮询到 通知
};

enum emMtSpeakerStatus
{
    emBgn               = 0,
        emWaiting       = 1,        //等待同意；mcu不会发送此状态，终端在发起申请 到 成为发言人通知 到 之前，自动跳入该状态
        emAgreed        = 2,        //发言人；
        emDenid         = 3,        //申请被拒绝；
        enCanceled      = 4,        //被取消发言；
		enEnd
};

enum emConfSpeakMode
{
    emNormalSpeakMode   = 0,        //普通发言模式：主席指定/会控指定/一般的终端申请
		emAnswerInstantly   = 1         //抢答模式
};

#ifdef WIN32
    #pragma comment( lib, "ws2_32.lib" ) 
    #pragma pack( push )
    #pragma pack( 1 )
    #define window( x )	x
    #define PACKED 
#else
    #include <netinet/in.h>
    #define window( x )
#if defined(__ETI_linux__)
    #define PACKED
#else
    #define PACKED __attribute__((__packed__))	// 取消编译器的优化对齐
#endif
#endif

// 终端ID号定义
//////////////////////////////////////////////////////////////////////////
typedef struct tagMtLabel
{
	// 设置和获取终端ID号
	void SetMtLabel( u8 byMcuNum, u8 byMtNum )
	{
		byMcuNo = byMcuNum;
		byMtNo = byMtNum;
	}

	u8 GetMcuNo( void ) { return byMcuNo; }
	u8 GetMtNo( void ) { return byMtNo; }
	tagMtLabel() : byMcuNo( 0 ), byMtNo( 0 ) {}
private :
	u8 byMcuNo;
	u8 byMtNo;
}PACKED TMTLABEL,*PTMTLABEL;



// 终端滚动消息定义
//////////////////////////////////////////////////////////////////////////

// 滚动消息类型
#define ROLLMSG_TYPE_SMS		0	// 短消息
#define ROLLMSG_TYPE_PAGETITLE	1	// 翻页字幕
#define ROLLMSG_TYPE_ROLLTITLE	2	// 滚动字幕
#define ROLLMSG_TYPE_STATICTEXT	3	// 静态文本

// 滚动消息内容
#define MAX_ROLLMSG_LEN		2048	// 最大2K字节

// 滚动速度
#define ROLL_SPEED_1	1	// 最慢
#define ROLL_SPEED_2	2	// 稍慢
#define ROLL_SPEED_3	3	// 中速
#define ROLL_SPEED_4	4	// 稍快
#define ROLL_SPEED_5	5	// 最快

// 无限制滚动
#define ROLL_INFINIT	0xFF

// 消息头结构: 消息类型(1)+滚动次数(1)+滚动速度(1)+源终端(2)+目的终端个数(2)+滚动消息长度(2)+整个消息长度(2)
// 消息体: 用户给出的目的终端列表+滚动消息内容
#define ROLLMSG_MSGHEAD_LEN					11
#define ROLLMSG_MSGHEAD_ROLLTYPE_OFFSET		0
#define ROLLMSG_MSGHEAD_ROLLTYPE_LEN		1
#define ROLLMSG_MSGHEAD_ROLLTIME_OFFSET		(ROLLMSG_MSGHEAD_ROLLTYPE_OFFSET + ROLLMSG_MSGHEAD_ROLLTYPE_LEN)
#define ROLLMSG_MSGHEAD_ROLLTIME_LEN		1
#define ROLLMSG_MSGHEAD_ROLLRATE_OFFSET		(ROLLMSG_MSGHEAD_ROLLTIME_OFFSET + ROLLMSG_MSGHEAD_ROLLTIME_LEN)
#define ROLLMSG_MSGHEAD_ROLLRATE_LEN		1
#define ROLLMSG_MSGHEAD_SRCMT_OFFSET		(ROLLMSG_MSGHEAD_ROLLRATE_OFFSET + ROLLMSG_MSGHEAD_ROLLRATE_LEN)
#define ROLLMSG_MSGHEAD_SRCMT_LEN			2
#define ROLLMSG_MSGHEAD_DSTMTNUM_OFFSET		(ROLLMSG_MSGHEAD_SRCMT_OFFSET + ROLLMSG_MSGHEAD_SRCMT_LEN)
#define ROLLMSG_MSGHEAD_DSTMTNUM_LEN		2
#define ROLLMSG_MSGHEAD_ROLLMSGLEN_OFFSET	(ROLLMSG_MSGHEAD_DSTMTNUM_OFFSET + ROLLMSG_MSGHEAD_DSTMTNUM_LEN)
#define ROLLMSG_MSGHEAD_ROLLMSGLEN_LEN		2
#define ROLLMSG_MSGHEAD_MSGLEN_OFFSET		(ROLLMSG_MSGHEAD_ROLLMSGLEN_OFFSET + ROLLMSG_MSGHEAD_ROLLMSGLEN_LEN)
#define ROLLMSG_MSGHEAD_MSGLEN_LEN			2
#define ROLLMSG_MSGBODY_OFFSET				ROLLMSG_MSGHEAD_LEN
//
//  矩阵信息
//

// 滚动消息结构
class CRollMsg
{
public :
	CRollMsg()
	{
		memset( m_abyBuffer, 0, sizeof( m_abyBuffer ) );
		u16 wLen = ROLLMSG_MSGHEAD_LEN;
		wLen = htons( wLen );
		memcpy( m_abyBuffer + ROLLMSG_MSGHEAD_MSGLEN_OFFSET,
			&wLen, ROLLMSG_MSGHEAD_MSGLEN_LEN );
	}

	/*
	====================================================================
	功能        ：设置滚动消息类型
	输入参数说明：类型
	返回值说明  ：无
	====================================================================
	*/
	void SetType( u8 byMsgType ) 
	{
		if ( byMsgType != ROLLMSG_TYPE_SMS 
			&& byMsgType != ROLLMSG_TYPE_PAGETITLE 
			&& byMsgType != ROLLMSG_TYPE_ROLLTITLE
			&& byMsgType != ROLLMSG_TYPE_STATICTEXT )
			byMsgType = ROLLMSG_TYPE_SMS;

		*( m_abyBuffer + ROLLMSG_MSGHEAD_ROLLTYPE_OFFSET ) = byMsgType;
		return;
	}

	/*
	====================================================================
	功能        ：获取滚动消息类型
	输入参数说明：无
	返回值说明  ：类型
	====================================================================
	*/
	u8 GetType( void ) { return *( m_abyBuffer + ROLLMSG_MSGHEAD_ROLLTYPE_OFFSET ); }

	/*
	====================================================================
	功能        ：设置滚动次数
	输入参数说明：次数
	返回值说明  ：无
	====================================================================
	*/
	void SetRollTimes( u8 byTimes ) 
	{
		if ( byTimes == 0 )
			byTimes = 1;	// 保证至少滚动一次
		*( m_abyBuffer + ROLLMSG_MSGHEAD_ROLLTIME_OFFSET ) = byTimes; 
	}
	/*
	====================================================================
	功能        ：获取滚动次数
	输入参数说明：无
	返回值说明  ：次数
	====================================================================
	*/
	u8 GetRollTimes( void ) { return *( m_abyBuffer + ROLLMSG_MSGHEAD_ROLLTIME_OFFSET ); }

	/*
	====================================================================
	功能        ：设置滚动速度
	输入参数说明：速度
	返回值说明  ：无
	====================================================================
	*/
	void SetRollRate( u8 byRate ) { *( m_abyBuffer + ROLLMSG_MSGHEAD_ROLLRATE_OFFSET ) = byRate; }
	/*
	====================================================================
	功能        ：获取滚动速度
	输入参数说明：无
	返回值说明  ：速度
	====================================================================
	*/
	u8 GetRollRate( void ) { return *( m_abyBuffer + ROLLMSG_MSGHEAD_ROLLRATE_OFFSET ); }

	/*
	====================================================================
	功能        ：设置消息发源终端
	输入参数说明：TMTLABEL
	返回值说明  ：无
	====================================================================
	*/
	void SetMsgSrcMtId( TMTLABEL tMtId ) {	SetMsgSrcMtId( tMtId.GetMcuNo(), tMtId.GetMtNo() ); }
	/*
	====================================================================
	功能        ：设置消息发源终端
	输入参数说明：<mcu,mt>
	返回值说明  ：无
	====================================================================
	*/
	void SetMsgSrcMtId( u8 byMcuNo, u8 byMtNo ) 
	{
		*( m_abyBuffer + ROLLMSG_MSGHEAD_SRCMT_OFFSET ) = byMcuNo;
		*( m_abyBuffer + ROLLMSG_MSGHEAD_SRCMT_OFFSET + 1 ) = byMtNo;
	}

	/*
	====================================================================
	功能        ：获取消息发源终端ID
	输入参数说明：无
	返回值说明  ：TMTLABEL
	====================================================================
	*/
	TMTLABEL GetMsgSrcMtId( void ) 
	{
		TMTLABEL tMsgSrc;
		u8 byMcuNo = *( m_abyBuffer + ROLLMSG_MSGHEAD_SRCMT_OFFSET );
		u8 byMtNo = *( m_abyBuffer + ROLLMSG_MSGHEAD_SRCMT_OFFSET + 1 );
		tMsgSrc.SetMtLabel( byMcuNo, byMtNo );
		return tMsgSrc; 
	}

	/*
	====================================================================
	功能        ：获取目的终端个数
	输入参数说明：无
	返回值说明  ：终端个数
	====================================================================
	*/
	u16  GetDstMtNum( void ) 
	{ 
		u16 wMtNum = 0;
		memcpy( &wMtNum, m_abyBuffer + ROLLMSG_MSGHEAD_DSTMTNUM_OFFSET,
			ROLLMSG_MSGHEAD_DSTMTNUM_LEN );
		return ntohs( wMtNum ); 
	}

	/*
	====================================================================
	功能        ：设置目的终端列表(将会重新更新终端列表)
	输入参数说明：列表首指针 + 目的终端个数
	返回值说明  ：无
	====================================================================
	*/
	void SetDstMtList( const TMTLABEL *ptMtList = NULL, u16 wDstMtNum = 0 )
	{
		if ( ptMtList == NULL || wDstMtNum == 0 )
			return;


		// 滚动消息长度
		u16 wRollMsgLen = GetRollMsgContentLen();
		if ( wRollMsgLen != 0 )
		{
			u8 abyRollMsg[ MAX_ROLLMSG_LEN ] = { 0 };
			u16 wOffSet = ROLLMSG_MSGBODY_OFFSET + wDstMtNum * sizeof( TMTLABEL );
			memcpy( abyRollMsg,
					m_abyBuffer + ROLLMSG_MSGBODY_OFFSET, 
					min( MAX_ROLLMSG_LEN, wRollMsgLen ) );
			memcpy( m_abyBuffer + wOffSet, abyRollMsg, min( MAX_ROLLMSG_LEN, wRollMsgLen ) );
		}
		memcpy( m_abyBuffer + ROLLMSG_MSGBODY_OFFSET, ptMtList, wDstMtNum * sizeof( TMTLABEL ) );

		// 总的消息长度
		u16 wMsgLen = wRollMsgLen + wDstMtNum * sizeof( TMTLABEL ) + ROLLMSG_MSGHEAD_LEN;
		wMsgLen = htons( wMsgLen );
		memcpy( m_abyBuffer + ROLLMSG_MSGHEAD_MSGLEN_OFFSET, &wMsgLen,
				ROLLMSG_MSGHEAD_MSGLEN_LEN );

		// 终端列表长度
		wDstMtNum = htons( wDstMtNum );
		memcpy( m_abyBuffer + ROLLMSG_MSGHEAD_DSTMTNUM_OFFSET, &wDstMtNum,
			ROLLMSG_MSGHEAD_DSTMTNUM_LEN );


	}

	/*
	====================================================================
	功能        ：向当前终端列表中增加一个终端
	输入参数说明：<mcu,mt>
	返回值说明  ：无
	====================================================================
	*/
	void AddDstMt( u8 byMcuNo, u8 byMtNo )
	{
		TMTLABEL tMt;
		tMt.SetMtLabel( byMcuNo, byMtNo );
		AddDstMt( tMt );
	}
	/*
	====================================================================
	功能        ：向当前终端列表中增加一个终端
	输入参数说明：TMTLABEL
	返回值说明  ：无
	====================================================================
	*/
	void AddDstMt( TMTLABEL tMt )
	{
		// 当前终端列表长度
		u16 wDstMtNum = GetDstMtNum();
		// 滚动消息长度
		u16 wRollMsgLen = GetRollMsgContentLen();

		// 总的消息长度
		u16 wMsgLen = wRollMsgLen + ( wDstMtNum + 1 )* sizeof( TMTLABEL ) + ROLLMSG_MSGHEAD_LEN;
		wMsgLen = htons( wMsgLen );
		memcpy( m_abyBuffer + ROLLMSG_MSGHEAD_MSGLEN_OFFSET, &wMsgLen,
			ROLLMSG_MSGHEAD_MSGLEN_LEN );

		// 增加终端
		u16 wOffSet = ROLLMSG_MSGBODY_OFFSET + wDstMtNum * sizeof( TMTLABEL );
		memmove( m_abyBuffer + wOffSet + sizeof( TMTLABEL ),
				m_abyBuffer + wOffSet,
				min( sizeof( m_abyBuffer ) - wOffSet - sizeof( TMTLABEL ), wRollMsgLen ) );
		*( m_abyBuffer + wOffSet ) = tMt.GetMcuNo();
		*( m_abyBuffer + wOffSet + 1 ) = tMt.GetMtNo();

		// 终端列表长度
		wDstMtNum = htons( wDstMtNum + 1 );
		memcpy( m_abyBuffer + ROLLMSG_MSGHEAD_DSTMTNUM_OFFSET, &wDstMtNum,
			ROLLMSG_MSGHEAD_DSTMTNUM_LEN );


	}

	/*
	====================================================================
	功能        ：获取当前目的终端列表首指针
	输入参数说明：无
	返回值说明  ：指向TMTLABEL的指针
	====================================================================
	*/
	TMTLABEL *GetDstMtList( void ) { return ( TMTLABEL* )( m_abyBuffer + ROLLMSG_MSGBODY_OFFSET ); }

	/*
	====================================================================
	功能        ：获取第一个目的终端
	输入参数说明：TMTLABEL*
	返回值说明  ：正确返回0,否则-1;
	====================================================================
	*/
	int GetFirstDstMt( TMTLABEL *ptMt = NULL ) 
	{
		if ( ptMt == NULL )
			return -1;

		if ( GetDstMtNum() != 0 )
		{
			ptMt->SetMtLabel( *( m_abyBuffer + ROLLMSG_MSGBODY_OFFSET ),
							*( m_abyBuffer + ROLLMSG_MSGBODY_OFFSET + 1 ) );
		}

		return 0;
	}

	/*
	====================================================================
	功能        ：获取下一个目的终端列表
	输入参数说明：当前终端索引 + TMTLABEL*
	返回值说明  ：正确返回下一个目的终端索引,否则-1
	====================================================================
	*/
	int GetNextDstMt( u16 wIndex, TMTLABEL *ptMt = NULL )
	{
		if ( ptMt == NULL || wIndex >= ( GetDstMtNum() - 1 ) )
			return -1;

		u16 wOffSet = ROLLMSG_MSGBODY_OFFSET + ( wIndex + 1 ) * sizeof( TMTLABEL );
		ptMt->SetMtLabel( *( m_abyBuffer + wOffSet ),
						  *( m_abyBuffer + wOffSet + 1 ) );

		return ( wIndex + 1 );
	}


	/*
	====================================================================
	功能        ：获取滚动消息内容长度
	输入参数说明：无
	返回值说明  ：长度
	====================================================================
	*/
	u16 GetRollMsgContentLen( void )
	{
		u16 wMsgLen = 0;
		memcpy( &wMsgLen, m_abyBuffer + ROLLMSG_MSGHEAD_ROLLMSGLEN_OFFSET,
				ROLLMSG_MSGHEAD_ROLLMSGLEN_LEN );
		return ntohs( wMsgLen );
	}

	/*
	====================================================================
	功能        ：设置滚动消息内容
	输入参数说明：消息内容 + 内容长度
	返回值说明  ：无
	====================================================================
	*/
	void SetRollMsgContent( const u8* pbyRollMsgContent = NULL, u16 wRollMsgLen = 0 )
	{
		if ( pbyRollMsgContent == NULL || wRollMsgLen == 0 )
			return;

		// 终端列表
		u16 wDstMtNum = GetDstMtNum();
		memcpy( m_abyBuffer + ROLLMSG_MSGBODY_OFFSET + wDstMtNum * sizeof( TMTLABEL ),
				pbyRollMsgContent, wRollMsgLen );

		// 总的消息长度
		u16 wMsgLen = wRollMsgLen + wDstMtNum * sizeof( TMTLABEL ) + ROLLMSG_MSGHEAD_LEN;
		wMsgLen = htons( wMsgLen );
		memcpy( m_abyBuffer + ROLLMSG_MSGHEAD_MSGLEN_OFFSET, &wMsgLen,
			ROLLMSG_MSGHEAD_MSGLEN_LEN );

		// 滚动消息长度
		wRollMsgLen = htons( wRollMsgLen );
		memcpy( m_abyBuffer + ROLLMSG_MSGHEAD_ROLLMSGLEN_OFFSET, &wRollMsgLen,
				ROLLMSG_MSGHEAD_ROLLMSGLEN_LEN );
	}

	/*
	====================================================================
	功能        ：获取当前滚动消息内容首指针
	输入参数说明：无
	返回值说明  ：首指针
	====================================================================
	*/
	u8* GetRollMsgContent( void ) 
	{
		u16 wDstMtNum = GetDstMtNum();
		return ( m_abyBuffer + ROLLMSG_MSGBODY_OFFSET + wDstMtNum * sizeof( TMTLABEL ) ); 
	}

	/*
	====================================================================
	功能        ：获取整个结构的实际长度
	输入参数说明：无
	返回值说明  ：长度
	====================================================================
	*/
	u16 GetTotalMsgLen( void ) 
	{ 
		u16 wMsgLen = 0;
		memcpy( &wMsgLen, m_abyBuffer + ROLLMSG_MSGHEAD_MSGLEN_OFFSET,
				ROLLMSG_MSGHEAD_MSGLEN_LEN );

		return ntohs( wMsgLen ); 
	} 

	/*
	====================================================================
	功能        ：设置当前结构
	输入参数说明：缓冲区首指针 + 缓冲区长度
	返回值说明  ：正确与否
	====================================================================
	*/
	BOOL SetRollMsg( const u8 *pbyMsg, u16 wMsgLen )
	{
		if ( wMsgLen < ROLLMSG_MSGHEAD_LEN )
			return FALSE;

		wMsgLen = min( wMsgLen, sizeof( m_abyBuffer ) );
		memcpy( m_abyBuffer, pbyMsg, wMsgLen );

		if ( GetTotalMsgLen() > sizeof( m_abyBuffer ) )
			return FALSE;


		return TRUE;
	}

	/*
	====================================================================
	功能        ：获取整个Buffer的头指针
	输入参数说明：无
	返回值说明  ：无
	====================================================================
	*/
	u8 *GetRollMsg( void ) { return m_abyBuffer; }


	/*
	====================================================================
	功能        ：重置当前结构
	输入参数说明：无
	返回值说明  ：无
	====================================================================
	*/
	void Reset( void ) 
	{
		memset( m_abyBuffer, 0, sizeof( m_abyBuffer ) );
		u16 wLen = ROLLMSG_MSGHEAD_LEN;
		wLen = htons( wLen );
		memcpy( m_abyBuffer + ROLLMSG_MSGHEAD_MSGLEN_OFFSET,
			    &wLen, ROLLMSG_MSGHEAD_MSGLEN_LEN );
	}


private :
	u8	m_abyBuffer[ 0x1000 ];			// buff
};

// 矩阵方案定义
//////////////////////////////////////////////////////////////////////////
// 方案名称
/*#define MAX_SCHEMENAME_LEN	32	
// 矩阵类型
#define MATRIX_AUDIO	1	// 音频矩阵
#define MATRIX_VIDEO	2	// 视频矩阵
#define MATRIX_AV		3	// 视音矩阵

// 矩阵方案结构
typedef struct tagMatrixScheme
{
	// 设置和获取矩阵类型
	void SetType( u8 byMatrixType )
	{
		if ( byMatrixType != MATRIX_VIDEO 
			&& byMatrixType != MATRIX_AUDIO
			&& byMatrixType != MATRIX_AV )
			byMatrixType = MATRIX_VIDEO;
		byType = byMatrixType;
	}

	u8 GetType( void ) { return byType; }

	// 设置和获取方案ID
	void SetIndex( u8 bySchemeId ) { byIndex = bySchemeId; }
	u8 GetIndex( void ) { return byIndex; }

	// 设置和获取视频矩阵方案名称
	void SetVideoName( const s8* pchSchemeName, u32 dwLen )
	{
		if ( pchSchemeName == NULL || dwLen == 0 )
			return;

		if ( dwLen > MAX_SCHEMENAME_LEN )
			dwLen = MAX_SCHEMENAME_LEN;

		memset( achVideoName, 0, sizeof( achVideoName ) );
		strncpy( achVideoName, pchSchemeName, dwLen );
		achVideoName[ MAX_SCHEMENAME_LEN ] = '\0';
	}
	
	void GetVideoName( s8* pchSchemeName, u32 dwLen )
	{
		if ( pchSchemeName == NULL || dwLen == 0 )
			return;
		memset( pchSchemeName, 0, dwLen );
		strncpy( pchSchemeName, achVideoName, dwLen );
		pchSchemeName[ dwLen - 1 ] = '\0';

	}

	// 设置和获取音频矩阵方案名称
	void SetAudioName( const s8* pchSchemeName, u32 dwLen )
	{
		if ( pchSchemeName == NULL || dwLen == 0 )
			return;

		if ( dwLen > MAX_SCHEMENAME_LEN )
			dwLen = MAX_SCHEMENAME_LEN;

		memset( achAudioName, 0, sizeof( achAudioName ) );
		strncpy( achAudioName, pchSchemeName, dwLen );
		achAudioName[ MAX_SCHEMENAME_LEN ] = '\0';
	}

	void GetAudioName( s8* pchSchemeName, u32 dwLen )
	{
		if ( pchSchemeName == NULL || dwLen == 0 )
			return;
		memset( pchSchemeName, 0, dwLen );
		strncpy( pchSchemeName, achAudioName, dwLen );
		pchSchemeName[ dwLen - 1 ] = '\0';

	}

	void Reset( void ) 
	{
		byType = MATRIX_VIDEO;
		byIndex = 0xFF;
		memset( achVideoName, 0, sizeof( achVideoName ) );
		memset( achAudioName, 0, sizeof( achAudioName ) );
	}

	tagMatrixScheme() : byType( MATRIX_VIDEO ), byIndex(0xFF)
	{
		memset( achVideoName, 0, sizeof( achVideoName ) );
		memset( achAudioName, 0, sizeof( achAudioName ) );
	}

private :
	u8 byType;									// 矩阵类型(视频,音频,视音频矩阵)
	u8 byIndex;									// 方案ID,当前共8套(0~7)
	s8 achVideoName[ MAX_SCHEMENAME_LEN + 1 ];	// 视频矩阵方案名称
	s8 achAudioName[ MAX_SCHEMENAME_LEN + 1 ];	// 音频矩阵方案名称
}PACKED TMATRIXSCHEME;


/************************************************************************/
/*     矩阵配置                                                         */
/************************************************************************/
/*#define MAXLEN_MATRIX_MODEL_NAME     16
#define MAXNUM_MATRIXPORT            64
#define MAXLEN_MATRIXPORTNAME        16
#define MAXLEN_MATRIXSCHEMENAME      16
	  
	  
	  
//矩阵配置
typedef struct tagITMatrixCfg
{   
protected:
	s8 m_abyModel[MAXLEN_MATRIX_MODEL_NAME+1]; //矩阵型号
    u8 m_byInPortNum;   //输入端口数
    u8 m_byOutPortNum; //输出端口数
    u8 m_byCtrlType;   //控制类型 0=RS232 1=RS485 2=RS422 3=tcpip
	u32 m_dwIP;
	u16 m_wPort;
public:
	//获取矩阵型号
	void GetModel( s8 abyModel[] ,u16 wLen)
	{
		strncpy( abyModel ,m_abyModel ,min(wLen ,MAXLEN_MATRIX_MODEL_NAME));
		abyModel[min(wLen ,MAXLEN_MATRIX_MODEL_NAME)]=0;
	}
	//设置矩阵型号
	void SetModel( s8 abyModel[])
	{
		strncpy( m_abyModel ,abyModel ,MAXLEN_MATRIX_MODEL_NAME);
		m_abyModel[MAXLEN_MATRIX_MODEL_NAME]=0;
	}

	//获取矩阵输入端口数
	u8 GetInPortNum()	{return m_byInPortNum;	}
	//设置矩阵输入端口数
	void SetInPortNum(u8 byPortNum ){ m_byInPortNum = byPortNum;	}

	//获取矩阵输出端口数
	u8 GetOutPortNum()	{return m_byOutPortNum;	}
	//设置矩阵输出端口数
	void SetOutPortNum(u8 byPortNum ){ m_byOutPortNum = byPortNum;	}

	//获取矩阵控制方式
	u8 GetCtrlType()	{return m_byCtrlType;	}
	//设置矩阵控制方式
	void SetCtrlType(u8 byType ){ m_byCtrlType = byType;	}

	//获取TCP/IP传输地址
	void GetIPAddr( u32& dwIP ,u16& wPort)
	{
		dwIP = m_dwIP;
		wPort = ntohs(m_wPort);
	}
	//设置TCP/IP传输地址
	void GetIPAddr( u32 dwIP ,u16 wPort)
	{
		m_dwIP = dwIP ;
		m_wPort = htons(wPort);
	}


}PACKED ITMatrixCfg;

//矩阵方案


struct ITMatrixScheme
{
protected:
	u8            m_byType;     //矩阵类型    0=内部 1=外部
	s8            m_abyName[MAXLEN_MATRIXSCHEMENAME];    //方案名
	u8            m_byIndex;                                   //方案索引
	u8            m_byInPortNum;//输入端口个数
	u8            m_byOutPortNum;//输出端口个数
	u8            m_abyPorts[MAXNUM_MATRIXPORT];//各个输出端口连接的输入端口
                                                       //输入端口名后为输出端口名
	s8            m_abyPortName[MAXNUM_MATRIXPORT][MAXLEN_MATRIXPORTNAME+1];
public:
	//获取矩阵类型
	u8 GettType(){ return m_byType;	}
	//设置矩阵类型
	void SetType(u8 byType){ m_byType =byType ;	}

	//获取方案索引
	u8 GetIndex(){return m_byIndex;	}
	void SetIndex(u8 byIndex){ m_byIndex = byIndex;	}

	//获取矩阵输入端口数
	u8 GetInPortNum()	{return m_byInPortNum;	}
	//设置矩阵输入端口数
	void SetInPortNum(u8 byPortNum ){ m_byInPortNum = byPortNum;	}

	//获取矩阵输出端口数
	u8 GetOutPortNum()	{return m_byOutPortNum;	}
	//设置矩阵输出端口数
	void SetOutPortNum(u8 byPortNum ){ m_byOutPortNum = byPortNum;	}

	//设置矩阵连接关系
	BOOL SetConnection(u8 byInPort ,u8 byOutPort )
	{ 
		if( byOutPort > MAXNUM_MATRIXPORT )
			return FALSE;
		m_abyPorts[byOutPort ] = byInPort;
	}
	//获取矩阵连接关系
	u8 GetConnection(u8 byOutPort )
	{ 
		if( byOutPort > MAXNUM_MATRIXPORT )
			return 0;
		return m_abyPorts[byOutPort ];
	}

	//获取指定输入端口名称
	BOOL GetInPortName( u8 byIndex ,s8 abyName[] ,u16 wLen )
	{
		if( byIndex > m_byInPortNum || byIndex >MAXNUM_MATRIXPORT )
		{
			memset(abyName ,0,wLen );
			return FALSE;
		}
		
		strncpy( abyName ,m_abyPortName[byIndex] ,min(wLen ,MAXLEN_MATRIXPORTNAME));
		abyName[min(wLen ,MAXLEN_MATRIXPORTNAME)]=0;
		return TRUE;
	}

	//设置指定输入端口名称
	BOOL SetInPortName( u8 byIndex ,s8 abyName[] )
	{
		if( byIndex > m_byOutPortNum ||	byIndex >MAXNUM_MATRIXPORT)
		{
			return FALSE;
		}
		
		strncpy(m_abyPortName[byIndex] , abyName ,MAXLEN_MATRIXPORTNAME);
		m_abyPortName[byIndex][MAXLEN_MATRIXPORTNAME]=0;
		return TRUE;
	}


	//获取指定输出端口名称
	BOOL GetOutPortName( u8 byIndex ,s8 abyName[] ,u16 wLen )
	{
		if( byIndex > m_byOutPortNum || 
			byIndex >MAXNUM_MATRIXPORT ||
			byIndex+m_byInPortNum >MAXNUM_MATRIXPORT)
		{
			memset(abyName ,0,wLen );
			return FALSE;
		}
		
		strncpy( abyName ,m_abyPortName[byIndex+m_byInPortNum] ,min(wLen ,MAXLEN_MATRIXPORTNAME));
		abyName[min(wLen ,MAXLEN_MATRIXPORTNAME)]=0;
		return TRUE;
	}

	//设置指定输出端口名称
	BOOL SetOutPortName( u8 byIndex ,s8 abyName[] )
	{
		if( byIndex > m_byOutPortNum || 
			byIndex >MAXNUM_MATRIXPORT||
			byIndex+m_byInPortNum > MAXNUM_MATRIXPORT)
		{
			return FALSE;
		}
		
		strncpy(m_abyPortName[byIndex+m_byInPortNum] , abyName ,MAXLEN_MATRIXPORTNAME);
		m_abyPortName[byIndex+m_byInPortNum][MAXLEN_MATRIXPORTNAME]=0;
		return TRUE;
	}


};*/
// 终端地址信息

// 地址类型
#define		ADDR_TYPE_IP		1
#define		ADDR_TYPE_ALIAS		2

// 别名类型
#define		ALIAS_H323ID		1
#define		ALIAS_E164			2
#define		ALIAS_EMAIL			3

typedef struct tagTerminalAddr
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

	u8 GetAliasType( void ) { return byAliasType; }
	s8* GetAliasName( void ) { return achAlias; }
	BOOL SetAlias( u8 byType, const s8* pchName, u8 byNameLen ) 
	{ 
		if ( pchName == NULL || byNameLen == 0 )
			return FALSE;

		byAliasType = byType; 
		memset( achAlias, 0, sizeof( achAlias ) );
		u8 byLen = min( byNameLen, VALIDLEN_ALIAS );
		memcpy( achAlias, pchName, byLen );
		achAlias[byLen] = '\0';
		return TRUE;
	}

	tagTerminalAddr() 
	{
		memset( this, 0, sizeof( tagTerminalAddr ) );
	}

	void Reset( void )
	{
		memset( this, 0, sizeof( tagTerminalAddr ) );
	}
	
private :
	u8	byAddrType;		// 地址类型
	u32 dwIp;			// IP(网络序)
	u16	wPort;			// 端口号
	u8	byAliasType;	// 别名类型
	s8 achAlias[ VALIDLEN_ALIAS + 1 ];
}PACKED TTERADDR,*PTTERADDR;





//视频协议类型
#define VIDEO_FORMAT_H261      0
#define VIDEO_FORMAT_H262      1//MPEG2
#define VIDEO_FORMAT_H263      2
#define VIDEO_FORMAT_H263plus  3
#define VIDEO_FORMAT_H264      4
#define VIDEO_FORMAT_MPEG4     5


//音频协议
#define AUTIO_FORMAT_G711a   0
#define AUTIO_FORMAT_G711u   1
#define AUTIO_FORMAT_G722    2
#define AUTIO_FORMAT_G7231   3
#define AUTIO_FORMAT_G728    4
#define AUTIO_FORMAT_G729    5
#define AUTIO_FORMAT_MP3     6



//视频分辨率分辨率类型
#define   VIDEO_RES_AUTO     0
#define   VIDEO_RES_VQCIF    1
#define   VIDEO_RES_VCIF     2
#define   VIDEO_RES_2CIF     3
#define   VIDEO_RES_4CIF     4
#define   VIDEO_RES_16CIF    5


//终端视频源
#define		VIDEO_SRC_S				0		//S端子
#define 	VIDEO_SRC_VGA			7		//VGA

//终端码率(由mcu主动请求获取)
typedef struct tagTerBitrate
{
protected:
    u16		m_awSendBitRate[2];			    //视频编码码率(单位:kbps)
    u16		m_awRecvBitRate[2];			    //视频解码码率(单位:kbps)
    u16		m_awSendAVBitRate[2];			//平均编码码率(单位:kbps)    
    u16		m_awRecvAVBitRate[2];			//平均解码码率(单位:kbps)

public:

    //获取发送码率
    void    GetSendBitRate(u16 &wPrimo, u16 &wSecond )
    {  
        wPrimo  = ntohs(m_awSendBitRate[0]);
        wSecond = ntohs(m_awSendBitRate[1]);
    }
    
    //设置发送码率
    void    SetSendBitRate(u16 wPrimo, u16 wSecond )
    {  
        m_awSendBitRate[0] = htons(wPrimo);
        m_awSendBitRate[1] = htons(wSecond);
    }
    
    //获取平均发送码率
    void    GetSendAverageBitRate(u16 &wPrimo, u16 &wSecond )
    {  
        wPrimo  = ntohs(m_awSendAVBitRate[0]);
        wSecond = ntohs(m_awSendAVBitRate[1]);
    }
    
    //设置平均发送码率
    void    SetSendAverageBitRate(u16 wPrimo, u16 wSecond )
    {  
        m_awSendAVBitRate[0] = htons(wPrimo);
        m_awSendAVBitRate[1] = htons(wSecond);
    }
    
    //获取接收码率
    void    GetRecvBitRate(u16 &wPrimo, u16 &wSecond )
    {  
        wPrimo  = ntohs(m_awRecvBitRate[0]);
        wSecond = ntohs(m_awRecvBitRate[1]);
    }
    
    //设置接收码率
    void    SetRecvBitRate(u16 wPrimo, u16 wSecond )
    {  
        m_awRecvBitRate[0] = htons(wPrimo);
        m_awRecvBitRate[1] = htons(wSecond);
    }
    
    //获取平均接收码率
    void    GetRecvAverageBitRate(u16 &wPrimo, u16 &wSecond )
    {  
        wPrimo  = ntohs(m_awRecvAVBitRate[0]);
        wSecond = ntohs(m_awRecvAVBitRate[1]);
    }
    
    //设置平均接收码率
    void    SetRecvAverageBitRate(u16 wPrimo, u16 wSecond )
    {  
        m_awRecvAVBitRate[0] = htons(wPrimo);
        m_awRecvAVBitRate[1] = htons(wSecond);
    }

}PACKED _TTERBITRATE;

//终端状态(发生变化时终端主动上报)
typedef struct tagTerStatus
{
protected:		
	///////会议状态///////
    // guzh [3/7/2007] 本字段从4.0R4开始取消，调整为一个8bit状态参数
	// u8		m_byPollStat;					//轮询状态		(PollStatus)

    ///////设备状态///////
#ifndef SETBITSTATUS
#define SETBITSTATUS(StatusValue, StatusMask, bStatus)   if (bStatus) StatusValue |= StatusMask;   else StatusValue &= ~StatusMask;
#define GETBITSTATUS(StatusValue, StatusMask) (0 != (StatusValue&StatusMask))
#endif
    enum TTerStatusMask
    {
        Mask_VidLose    =   0x01            //是否视频源丢失信号
    };

    u8      m_byCommStatus;                 //终端状态参数
	
	u8		m_byMtBoardType;				//终端板卡类型	MT_BOARD_WIN, MT_BOARD_8010, ...
	u8		m_byMatrixStatus;				//矩阵状态		(1 ok 0 err)
	u8		m_byVideoSrc;				    //当前本地视频源(0:S端子,1-6:C端子)
	u8		m_bRemoteCtrl;				    //是否允许远遥	1 yes 0 no	
			
	u8		m_byEncVol;					    //当前编码音量(单位:等级)
    u8		m_byDecVol;					    //当前解码音量(单位:等级)
	u8		m_bMute;						//是否哑音	1 yes 0 no	
	u8		m_bQuiet;						//是否静音	1 yes 0 no
    u8      m_byExVideoSourceNum;           //终端扩展视频源 0表示没有
public:
    // 视频源丢失
    BOOL    IsVideoLose() const {return GETBITSTATUS(m_byCommStatus, Mask_VidLose); }
    void    SetVideoLose(BOOL bIsVideoLose) { SETBITSTATUS(m_byCommStatus, Mask_VidLose, bIsVideoLose)  }    
	
	// 获取终端类型(宏定义)
	u8      GetBoardType() const {return m_byMtBoardType;	}
	void    SetBoardType(u8 byType){ m_byMtBoardType = byType;	}

	//外部矩阵是否配置   (1 ok 0 err)
	u8    GetMatrixStatus() const { return m_byMatrixStatus;	}
	void    SetMatrixStatus(u8 byStatus ) { m_byMatrixStatus = byStatus;	}
	
	// 获取视频
	u8      GetVideoSrc() const	{ return m_byVideoSrc;	}
	void    SetVideoSrc( u8 bySrc ){ m_byVideoSrc = bySrc;	}

	//是否允许远摇
	BOOL    IsRemoteCtrlEnalbe() const {return  (0 != m_bRemoteCtrl);	}
    void    SetRemoteCtrlEnalbe( BOOL bEnable) { m_bRemoteCtrl = bEnable ? 1:0;	}
		
	//获取输入音量
	u8  GetInputVolume() const {return m_byEncVol;}
	void  SetInputVolume(u8 byInputVolume){  m_byEncVol = byInputVolume;}

	//获取输出音量
	u8  GetOutputVolume() const {return m_byDecVol;}
	void  SetOutputVolume(u8 byOutputVolume){  m_byDecVol = byOutputVolume;}

    //是否哑音
	BOOL IsMute() const {return (0 != m_bMute);}
	void SetMute(BOOL bMute ){ m_bMute = bMute ? 1:0;}
	
	//是否静音
	BOOL IsQuiet() const {return (0 != m_bQuiet);}
	void SetQuiet(BOOL bQuiet ){ m_bQuiet = bQuiet ? 1:0;}

	//扩展视频源
	u8   GetExVidSrcNum() const { return m_byExVideoSourceNum;	}
	void SetExVidSrcNum(u8 byNum) { m_byExVideoSourceNum = byNum ;}
	
}PACKED _TTERSTATUS;

#define MAXLEN_MATRIXPORTNAME        16
#define MAX_SCHEMENAME_LEN	32
#define MAXNUM_INNERMATRIXPORT 6
typedef struct tagITInnerMatrixScheme
{
		s8 achName[ MAX_SCHEMENAME_LEN + 1 ]; //方案名
		u8 byIndex; //方案索引
		//
		// 输出端口号( 1 - 6 )
		// 各个输出端口连接的输入端口
		//
		u8 abyOutPort2InPort[ MAXNUM_INNERMATRIXPORT ]; //输出端口对应的输入端口
		                           //注: abyOutPort2InPort[]=0 表示指定端口输出第一路视频
		                           //    abyOutPort2InPort[]=7 表示指定端口输出第二路视频
		                           //    abyOutPort2InPort[]=1~6 表示指定端口输出相应的C1～6

		//
		// 端口( 1- 6 )名字
		//
		s8 achOutPortName[MAXNUM_INNERMATRIXPORT][ MAX_SCHEMENAME_LEN + 1 ];
		s8 achInPortName [MAXNUM_INNERMATRIXPORT][ MAX_SCHEMENAME_LEN + 1 ];
}PACKED ITInnerMatrixScheme;

#define EX_VIDEOSOURCE_BASE     10    //扩展视频源基值

typedef struct tagITVideoSourceInfo
{
protected:
	u8 m_byIndex;
	s8 m_achName[MAXLEN_MATRIXPORTNAME+1];
public:
	u8  GetIndex(){ return m_byIndex;	}
	void  SetIndex(u8 byIndex){ m_byIndex = byIndex;	}

	void SetName( s8* achName)
	{ 
		strncpy( m_achName ,achName ,sizeof(m_achName));
		m_achName[sizeof(m_achName)-1]=0;
	}

	void GetName( s8* achName ,u16 wSize)
	{ 
		strncpy( achName,m_achName ,wSize);
		achName[wSize-1]=0;
	}

}PACKED ITVideoSourceInfo;



//定义简化MCU、终端或外设结构 (len:6)
struct TMt
{

protected:
    u8          m_byMainType;   //设备主类
    u8  		m_bySubType;	//设备子类
	u8  		m_byMcuId;		//MCU号
	u8  		m_byEqpId;	    //设备号	
	u8          m_byConfDriId;  //DRI板号
    u8          m_byConfIdx;    //会议索引号，即会议实例号 1 - MAXNUM_MCU_CONF

public:
	//操作所有类型函数
	void   SetType( u8   byType ){ m_byMainType = byType; }         //设置结构主类
	u8     GetType( void ) const { return m_byMainType; }           //得到结构主类
	void   SetMcuId( u8   byMcuId ){ m_byMcuId = byMcuId; }         //设置McuId
	u8     GetMcuId( void ) const { return m_byMcuId; }             //得到McuId
	BOOL   operator ==( const TMt & tObj ) const;                  //判断是否相等

	//操作MCU函数
	void   SetMcu( u8   byMcuId );                         //设置MCU
	void   SetMcuType( u8  byMcuType ){ m_byMainType = TYPE_MCU; m_bySubType = byMcuType; }
	u8     GetMcuType( void ) const { return m_bySubType; }

	//操作外设函数
	void   SetMcuEqp( u8   byMcuId, u8   byEqpId, u8   byEqpType );            //设置MCU外设
	void   SetEqpType( u8   byEqpType ){ m_byMainType = TYPE_MCUPERI; m_bySubType = byEqpType; }                                       //设置MCU外设类型
	u8     GetEqpType( void ) const { return m_bySubType; }
	void   SetEqpId( u8   byEqpId ){ m_byMainType = TYPE_MCUPERI; m_byEqpId = byEqpId; }
	u8     GetEqpId( void ) const { return m_byEqpId; }
	
	//操作终端函数
	void   SetMt( u8   byMcuId, u8   byMtId, u8   m_byDriId = 0, u8   m_byConfIdx = 0);
	void   SetMt( TMt tMt);
	void   SetMtId( u8   byMtId ){ m_byMainType = TYPE_MT; m_byEqpId = byMtId; }
	u8     GetMtId( void ) const { return m_byEqpId; }//设置终端
	void   SetMtType( u8   byMtType ) { m_byMainType = TYPE_MT; m_bySubType = byMtType; }
	u8     GetMtType( void ) const { return m_bySubType; }  	
    void   SetDriId(u8   byDriId){ m_byConfDriId = byDriId; }
    u8     GetDriId( void ) const { return m_byConfDriId; }
    void   SetConfIdx(u8   byConfIdx){ m_byConfIdx = byConfIdx; } 
    u8     GetConfIdx( void ) const { return m_byConfIdx; }
	void   SetNull( void ){ m_byMcuId = 0; m_byEqpId = 0; m_byConfDriId = 0; }
	BOOL   IsNull ( void ) const{ return m_byMcuId == 0 && m_byEqpId == 0; }
	BOOL   IsLocal() const {	return (m_byMcuId == LOCAL_MCUID );	}
}
/*
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
*/
PACKED
;

//定义终端结构
typedef TMt TEqp;

//终端轮询参数 (len:12)
struct TMtPollParam: public TMt
{
protected:
	u16   m_wKeepTime;        //终端轮询的保留时间 单位:秒(s)
    u32   m_dwPollNum;        //终端轮询的次数
public:
	void  SetKeepTime(u16 wKeepTime) { m_wKeepTime = htons(wKeepTime); } 
	u16   GetKeepTime(void) const { return ntohs(m_wKeepTime); }
    void  SetPollNum(u32 dwPollNum) { m_dwPollNum = htonl(dwPollNum); } 
	u32   GetPollNum(void) const { return ntohl(m_dwPollNum); }
	TMt   GetTMt(void) const { return *(TMt *)this; }
	void  SetTMt(TMt tMt) { memcpy( this, &tMt, sizeof(tMt) ); }
}
/*
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
*/
PACKED
;

//定义画面合成成员结构 (len:8)
struct TVMPMember: public TMt
{
protected:
    u8   m_byMemberType;     //画面合成成员类型,参见vccommon.h中画面合成成员类型定义
    u8   m_byMemStatus;      //成员状态(MT_STATUS_CHAIRMAN, MT_STATUS_SPEAKER, MT_STATUS_AUDIENCE)

public:
    void  SetMemberType(u8   byMemberType){ m_byMemberType = byMemberType;} 
    u8    GetMemberType( void ) const { return m_byMemberType; }
    void  SetMemStatus(u8 byStatus) { m_byMemStatus = byStatus; }
    u8    GetMemStatus(void) const { return m_byMemStatus; }
    void  SetMemberTMt( TMt tMt ){ memcpy( this, &tMt, sizeof(TMt) ); }
}
/*
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
*/
PACKED
;

//定义画面合成参数结构 (len:136 + 4*8 = 168)
struct TVMPParam
{
protected:
	u8      m_byVMPAuto;      //是否是自动画面合成 0-否 1-是
	u8      m_byVMPBrdst;     //合成图像是否向终端广播 0-否 1-是 
	u8      m_byVMPStyle;     //画面合成风格,参见mcuconst.h中画面合成风格定义
    u8      m_byVMPSchemeId;  //合成风格方案编号,最大支持5套方案,1-5
    u8      m_byVMPMode;      //图像复合方式: 0-不图像复合 1-会控或主席控制图像复合 2-自动图像复合(动态分屏与设置成员)
	u8		m_byRimEnabled;	  //是否使用边框: 0-不使用(默认) 1-使用;
							  //本字段目前只对方案0有效, 其他方案暂不涉及本字段的设置和判断
	//u8		m_byReserved1;	  //保留字段
	//u8		m_byReserved2;	  //保留字段
	u8		m_byVMPBatchPoll; // xliang [12/18/2008] 是否是批量轮询 0-否
	u8		m_byVMPSeeByChairman;	// 是否被主席MT选看	0-否
	TVMPMember  m_atVMPMember[MAXNUM_MPUSVMP_MEMBER]; //画面合成成员
public:
    void   SetVMPAuto(u8   byVMPAuto){ m_byVMPAuto = byVMPAuto;} 
    BOOL   IsVMPAuto( void ) const { return m_byVMPAuto == 0 ? FALSE : TRUE; }
    void   SetVMPBrdst(u8   byVMPBrdst){ m_byVMPBrdst = byVMPBrdst;} 
    BOOL   IsVMPBrdst( void ) const { return m_byVMPBrdst == 0 ? FALSE : TRUE; }
    void   SetVMPStyle(u8   byVMPStyle){ m_byVMPStyle = byVMPStyle;} 
    u8     GetVMPStyle( void ) const { return m_byVMPStyle; }
    void   SetVMPSchemeId(u8 bySchemeId) { m_byVMPSchemeId = bySchemeId; }
    u8     GetVMPSchemeId(void) const { return m_byVMPSchemeId; }
    void   SetVMPMode(u8   byVMPMode){ m_byVMPMode = byVMPMode;} 
    u8     GetVMPMode( void ) const { return m_byVMPMode; }
	void   SetIsRimEnabled(u8 byEnabled){ m_byRimEnabled = byEnabled; }
	BOOL32 GetIsRimEnabled(void) const { return m_byRimEnabled == 1 ? TRUE : FALSE; }
	void	SetVMPBatchPoll(u8 byVMPBatchPoll){m_byVMPBatchPoll = byVMPBatchPoll;} // xliang [12/22/2008] 
	BOOL	IsVMPBatchPoll( void ) const { return m_byVMPBatchPoll == 0 ? FALSE : TRUE;}
	void	SetVMPSeeByChairman(u8 byVMPSeeByMt) { m_byVMPSeeByChairman = byVMPSeeByMt;}
	BOOL	IsVMPSeeByChairman( void ) const {  return m_byVMPSeeByChairman == 0 ? FALSE : TRUE; }
    u8     GetMaxMemberNum( void ) const 
	{
		u8   byMaxMemNum = 1;

		switch( m_byVMPStyle ) 
		{
		case VMP_STYLE_ONE:
			byMaxMemNum = 1;
			break;
		case VMP_STYLE_VTWO:
		case VMP_STYLE_HTWO:
			byMaxMemNum = 2;
			break;
		case VMP_STYLE_THREE:
			byMaxMemNum = 3;
			break;
		case VMP_STYLE_FOUR:
			byMaxMemNum = 4;
			break;
		case VMP_STYLE_SIX:
			byMaxMemNum = 6;
			break;
		case VMP_STYLE_EIGHT:
			byMaxMemNum = 8;
			break;
		case VMP_STYLE_NINE:
			byMaxMemNum = 9;
			break;
		case VMP_STYLE_TEN:
			byMaxMemNum = 10;
			break;
		case VMP_STYLE_THIRTEEN:
			byMaxMemNum = 13;
			break;
		case VMP_STYLE_SIXTEEN:
			byMaxMemNum = 16;
			break;
		case VMP_STYLE_SPECFOUR:
			byMaxMemNum = 4;
			break;
		case VMP_STYLE_SEVEN:
			byMaxMemNum = 7;
			break;
		case VMP_STYLE_TWENTY:
			byMaxMemNum = 20;
			break;
		default:
			byMaxMemNum = 1;
			break;
		}
		return byMaxMemNum;
	}
	void   SetVmpMember( u8   byMemberId, TVMPMember tVMPMember )
	{
		if( byMemberId >= MAXNUM_MPUSVMP_MEMBER )return;
		m_atVMPMember[byMemberId] = tVMPMember;
	}
	void   ClearVmpMember( u8 byMemberId )
	{
		if( byMemberId >= MAXNUM_MPUSVMP_MEMBER )return;
		m_atVMPMember[byMemberId].SetNull();
        m_atVMPMember[byMemberId].SetMemberType(0);
	}
    TVMPMember *GetVmpMember( u8   byMemberId )
	{
		if( byMemberId >= MAXNUM_MPUSVMP_MEMBER )return NULL;
		return &m_atVMPMember[byMemberId];
	}
	BOOL IsMtInMember( TMt tMt )
	{
		u8 byLoop = 0;
		u8 byLoopCtrl = 0;
		while( byLoop < GetMaxMemberNum() && byLoopCtrl < MAXNUM_MPUSVMP_MEMBER )
		{
			if( tMt.GetMtId() == m_atVMPMember[byLoop].GetMtId() && 
				tMt.GetMcuId() == m_atVMPMember[byLoop].GetMcuId() )
			{
				return TRUE;
			}

			byLoop++;
			byLoopCtrl++;
		}

		return FALSE;
	}
    BOOL IsTypeInMember(u8 byType)
    {
        u8 byLoop = 0;
		while( byLoop < GetMaxMemberNum() )
		{
			if( byType == m_atVMPMember[byLoop].GetMemberType() )
			{
				return TRUE;
			}
			byLoop++;
		}

		return FALSE;
    }
	u8 GetChlOfMtInMember( TMt tMt )
	{
		u8 byLoop = 0;
		while( byLoop < GetMaxMemberNum() )
		{
//  [11/5/2009 pengjie] 级联多回传支持
// 			if (!m_atVMPMember[byLoop].IsLocal() &&
// 				tMt.GetMtId() == m_atVMPMember[byLoop].GetMcuId())
// 			{
// 				return byLoop;				 
// 			}
			if (!m_atVMPMember[byLoop].IsLocal() &&
				tMt.GetMtId() == m_atVMPMember[byLoop].GetMtId()&&
				tMt.GetMcuId() == m_atVMPMember[byLoop].GetMcuId() )
			{
				return byLoop;				 
			}
// endmodify
			if( tMt.GetMtId() == m_atVMPMember[byLoop].GetMtId() )
			{
				return byLoop;
			}
			byLoop++;
		}

		return MAXNUM_MPUSVMP_MEMBER;
	}
	u8 GetChlOfMemberType (u8 byMemberType) 
	{
		u8 byLoop = 0;
		while( byLoop < GetMaxMemberNum() )
		{
			if (byMemberType == m_atVMPMember[byLoop].GetMemberType())
			{
				return byLoop;
			}
			byLoop++;
		}

		return MAXNUM_MPUSVMP_MEMBER;
	}
	void   Print( void ) const
	{
		OspPrintf( TRUE, FALSE, "\nVMPParam:\n" );
		OspPrintf( TRUE, FALSE, "m_byVMPAuto: %d\n", m_byVMPAuto);
		OspPrintf( TRUE, FALSE, "m_byVMPBrdst: %d\n", m_byVMPBrdst);
		OspPrintf( TRUE, FALSE, "m_byVMPStyle: %d\n", m_byVMPStyle);
        OspPrintf( TRUE, FALSE, "m_byVmpSchemeId: %d\n", m_byVMPSchemeId );
		OspPrintf( TRUE, FALSE, "m_byRimEnabled: %d\n", m_byRimEnabled );
        OspPrintf( TRUE, FALSE, "m_byVMPMode: %d\n", m_byVMPMode );
		OspPrintf( TRUE, FALSE, "m_byVMPBatchPoll :%d\n", m_byVMPBatchPoll );
		OspPrintf( TRUE, FALSE, "m_byVMPSeeByChairman : %d\n", m_byVMPSeeByChairman);
		for( int i = 0; i < GetMaxMemberNum(); i ++ )
		{
			OspPrintf( TRUE, FALSE, "VMP member %d: MtId-%d, Type-%d\n", 
				i,  m_atVMPMember[i].GetMtId(), m_atVMPMember[i].GetMemberType() );            
		}
	}
}
/*
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
*/
PACKED
;

//会议号结构 (len:16)
struct CConfId
{
protected:
	u8  	m_abyConfId[MAXLEN_CONFID];

public:
	u8   GetConfId( u8   * pbyConfId, u8   byBufLen ) const; //获得会议号数组
	void CreateConfId( u8 byUsrGrpId );                               //创建会议号
	void GetConfIdString( LPSTR lpszConfId, u8   byBufLen ) const;//获得会议号字符串
	void SetConfId( const CConfId & cConfId );                  //设置会议号
	u8   SetConfId( const u8   * pbyConfId, u8   byBufLen );          //设置会议号数组
	u8   SetConfId( LPCSTR lpszConfId );                          //设置会议号数组	
	BOOL IsNull( void ) const;                                  //判断会议号是否为空
	void SetNull( void );                                       //设置会议号为空
	BOOL operator == ( const CConfId & cConfId ) const;         //操作符重载
    // 顾振华，在CConfId中内置用户组的信息
    u8   GetUsrGrpId() const 
    {
        return m_abyConfId[MAXLEN_CONFID-1];
    }
    void SetUsrGrpId(u8 byGrpId)
    {
        m_abyConfId[MAXLEN_CONFID-1] = byGrpId;
    }

	//fuxiuhua,增加会议发起方信息
	//会议ID的组成：MCU号(2Byte)/会议类型(1Byte)/会议索引值(1Byte)/会议号产生次数(4Byte)/
	//              未用(6Byte)/发起方类型(1Byte)/组号(1Byte)
	void SetConfSource( u8 byConfSource )
	{
		m_abyConfId[MAXLEN_CONFID - 2] = byConfSource;
	}
	u8   GetConfSource()
	{
		return m_abyConfId[MAXLEN_CONFID - 2];
	}

	void Print( void ) const
	{
		s8 achBuf[MAXLEN_CONFID*2+1];
		memset(achBuf, 0, sizeof(achBuf));
		GetConfIdString( achBuf, sizeof(achBuf) );
		OspPrintf( TRUE, FALSE, "%s\n", achBuf);
	}
}
/*
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
*/
PACKED
;

//定义传输地址结构(len:6)
struct TTransportAddr
{
public:
	u32   		m_dwIpAddr;		//IP地址, 网络序
	u16 		m_wPort;		//端口号, 网络序
public:
	void   SetNull(void)
	{
		m_dwIpAddr = 0;
		m_wPort = 0;
	}
    void   SetNetSeqIpAddr(u32    dwIpAddr){ m_dwIpAddr = dwIpAddr; } 
    u32    GetNetSeqIpAddr( void ) const { return m_dwIpAddr; }
    void   SetIpAddr(u32    dwIpAddr){ m_dwIpAddr = htonl(dwIpAddr); } 
    u32    GetIpAddr( void ) const { return ntohl(m_dwIpAddr); }
    void   SetPort(u16  wPort){ m_wPort = htons(wPort); } 
    u16    GetPort( void ) const { return ntohs(m_wPort); }
}
/*
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
*/
PACKED
;

//(len:22)
struct TMediaEncrypt
{
protected:
	u8  m_byEncryptMode;         //加密模式 : CONF_ENCRYPTMODE_NONE,CONF_ENCRYPTMODE_DES, CONF_ENCRYPT_AES
    s32 m_nKeyLen;               //加密key的长度
	u8  m_abyEncKey[MAXLEN_KEY]; //加密key
	u8  m_byReserve;             //保留
public:
	TMediaEncrypt()
	{
		Reset();
	}
	void Reset()
	{
        memset( &m_abyEncKey, 0, MAXLEN_KEY );
		m_byEncryptMode = CONF_ENCRYPTMODE_NONE;
		m_nKeyLen = 0;
	}

	void SetEncryptMode(u8 byEncMode)
	{
		m_byEncryptMode = byEncMode;
	}
    u8  GetEncryptMode()
	{
		return m_byEncryptMode;
	}
	void SetEncryptKey(u8 *pbyKey, s32 nLen)
	{
		m_nKeyLen = (nLen > MAXLEN_KEY ? MAXLEN_KEY : nLen);
		if(m_nKeyLen > 0)
			memcpy(m_abyEncKey, pbyKey, m_nKeyLen); 
		m_nKeyLen = htonl(m_nKeyLen);
	}
	
	void GetEncryptKey(u8 *pbyKey, s32* pnLen)
	{
		if(pnLen != NULL) *pnLen = ntohl(m_nKeyLen);
		if(pbyKey != NULL) memcpy(pbyKey, m_abyEncKey, ntohl(m_nKeyLen));
	}
}
/*
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
*/
PACKED
;

//记录录像或放像进度(单位:秒)
struct  TRecProg
{
protected:
	u32   		m_dwCurProg;	//当前进度
	u32   		m_dwTotalTime;	//总长度，仅在放像时有效

public:
	//设置当前进度位置（单位：秒）
	void SetCurProg( u32    dwCurProg )	{ m_dwCurProg = htonl( dwCurProg ); }
	//获取当前进度位置（单位：秒）
	u32    GetCurProg( void ) const	{ return ntohl( m_dwCurProg ); }
	//设置总长度，仅对放像有效（单位：秒）
	void SetTotalTime( u32    dwTotalTime )	{ m_dwTotalTime = htonl( dwTotalTime ); }
	//获取总长度，仅对放像有效（单位：秒）
	u32    GetTotalTime( void ) const	{ return ntohl( m_dwTotalTime ); }
}
/*
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
*/
PACKED
;

//时间结构重新定义
struct TKdvTime
{
protected:
	u16 		m_wYear;//年
	u8  		m_byMonth;//月
	u8  		m_byMDay;//日
	u8  		m_byHour;//时
	u8  		m_byMinute;//分
	u8  		m_bySecond;//秒

public:
    TKdvTime()
    {
        memset(this, 0, sizeof(TKdvTime));
    }
	void SetTime( const time_t * ptTime );//设置时间
	void GetTime( time_t & tTime ) const;//得到时间结构
	BOOL operator == ( const TKdvTime & tTime );//重载

	u16  GetYear( void ) const	{ return( ntohs( m_wYear ) ); }
	u8   GetMonth( void ) const	{ return( m_byMonth ); }
	u8   GetDay( void ) const	{ return( m_byMDay ); }
	u8   GetHour( void ) const	{ return( m_byHour ); }
	u8   GetMinute( void ) const	{ return( m_byMinute ); }
	u8   GetSecond( void ) const	{ return( m_bySecond ); }
	void SetYear( u16  wYear )	{ m_wYear = htons( wYear ); }
	void SetMonth( u8   byMonth )	{ m_byMonth = byMonth; }
	void SetDay( u8   byDay )	{ m_byMDay = byDay; }
	void SetHour( u8   byHour )	{ m_byHour = byHour; }
	void SetMinute( u8   byMinute )	{ m_byMinute = byMinute; }
	void SetSecond( u8   bySecond )	{ m_bySecond = bySecond; }
	void Print( void ) const
	{
		OspPrintf( TRUE, FALSE, "%d-%d-%d %d:%d:%d", ntohs(m_wYear),m_byMonth,m_byMDay,m_byHour,m_byMinute,m_bySecond );
	}
}
/*
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
*/
PACKED
;

//轮询信息(len: 18)
struct TPollInfo
{
protected:
    u8  m_byMediaMode;           //轮询模式 MODE_VIDEO 图像  MODE_BOTH 语音图像
    u8  m_byPollState;           //轮询状态，参见轮询状态定义
    u32 m_dwPollNum;             //终端轮询的次数，注：hdu批量轮询与电视墙轮询复用
    TMtPollParam m_tMtPollParam; //当前被轮询广播的终端及其参数
public:
    void SetMediaMode(u8 byMediaMode) { m_byMediaMode = byMediaMode; }
    u8   GetMediaMode(void) const { return m_byMediaMode; }
    void SetPollState(u8 byPollState) { m_byPollState = byPollState; }
    u8   GetPollState(void) const { return m_byPollState; }
    void SetPollNum(u32 dwPollNum) { m_dwPollNum = htonl(dwPollNum); }
    u32  GetPollNum(void) const { return ntohl(m_dwPollNum); }
    void SetMtPollParam(TMtPollParam tMtPollParam){ m_tMtPollParam = tMtPollParam; }
    TMtPollParam GetMtPollParam() const{ return m_tMtPollParam; }
    void Print(void) const
    {
        OspPrintf(TRUE, FALSE, "\nPollInfo:\n");
        OspPrintf(TRUE, FALSE, "m_byMediaMode: %d\n", m_byMediaMode);
        OspPrintf(TRUE, FALSE, "m_byPollState: %d\n", m_byPollState);
        OspPrintf(TRUE, FALSE, "m_dwPollNum: %d\n", m_dwPollNum);
        OspPrintf(TRUE, FALSE, "CurPollMt: %d,%d\n", m_tMtPollParam.GetMcuId(),m_tMtPollParam.GetMtId());
    }
}
/*
#ifndef WIN32
__attribute__((packed))
#endif
*/
PACKED
;

//电视墙轮询信息(len:32)
struct TTvWallPollInfo : public TPollInfo
{
protected:
    TEqp    m_tTvWall;
    u8      m_byTWChnnl;
	u32     m_byKeepTime;
	u8      m_bySchemeIdx;
	u8      m_byReserved[2];
    
public:
	TTvWallPollInfo(void){ memset( this, 0x0, sizeof( TTvWallPollInfo ) ); }

    void SetTvWall(TEqp tTvWall) { m_tTvWall = tTvWall; }
    TEqp GetTvWall(void) const{ return m_tTvWall; } 
    
	void SetTWChnnl(u8 byChnnl) { m_byTWChnnl = byChnnl; }
    u8   GetTWChnnl(void) const { return m_byTWChnnl; }
	
    void SetKeepTime( u32 byKeepTime ){ m_byKeepTime = htonl(byKeepTime); }
	u32  GetKeepTime( void ){ return ntohl(m_byKeepTime); } 

	void SetSchemeIdx(u8 bySchemeIdx) { m_bySchemeIdx = bySchemeIdx; }
    u8   GetSchemeIdx(void) const { return m_bySchemeIdx; }
}
/*
#ifndef WIN32
__attribute__((packed))
#endif
*/
PACKED
;

//HDU轮询信息(len: 32)
typedef TTvWallPollInfo THduPollInfo;


//定义终端别名枚举类型
typedef enum
{
	mtAliasTypeBegin = 0,
	mtAliasTypeTransportAddress = 1,  //终端别名类型: 传输地址
	mtAliasTypeE164,              //终端别名类型: E164号码
	mtAliasTypeH323ID,            //终端别名类型: H323 ID
	mtAliasTypeH320ID,            //终端别名类型: H320 ID类型
    mtAliasTypeH320Alias,         //终端别名类型: H320 别名类型, 不作呼叫信息
	mtAliasTypeOthers,            //终端别名类型: 其它
	puAliasTypeIPPlusAlias        //特殊PU呼叫信息:网管IP(u32网络序)+PU别名(11字节)
} mtAliasType;

//定义终端别名结构(len:135)
struct TMtAlias
{
public:
    u8				m_AliasType;               //别名类型
    s8			m_achAlias[MAXLEN_ALIAS];  //别名字符串
    TTransportAddr	m_tTransportAddr;          //传输地址
public:
	TMtAlias( void ){ memset( this, 0, sizeof(TMtAlias) ); }
	BOOL operator ==( const TMtAlias & tObj ) const;
	BOOL IsNull( void ) const { if( m_AliasType == 0 )return TRUE; return FALSE; }
	void SetNull( void ){ memset(this, 0, sizeof(TMtAlias)); }
	BOOL IsAliasNull( void ) const { return 0 == strlen(m_achAlias); }
	void SetE164Alias( LPCSTR lpzAlias )
	{
		if( lpzAlias != NULL )
		{
			m_AliasType = mtAliasTypeE164;
            memset( m_achAlias, 0, sizeof(m_achAlias));
			strncpy( m_achAlias, lpzAlias, MAXLEN_ALIAS-1 );
		}
	}
	void SetH323Alias( LPCSTR lpzAlias )
	{
		if( lpzAlias != NULL )
		{
			m_AliasType = mtAliasTypeH323ID;
            memset( m_achAlias, 0, sizeof(m_achAlias));
			strncpy( m_achAlias, lpzAlias, MAXLEN_ALIAS-1 );
		}
	}
	void SetH320Alias( u8 byLayer, u8 bySlot, u8 byChannel )
	{
		m_AliasType = mtAliasTypeH320ID;
		sprintf( m_achAlias, "层%d-槽%d-通道%d%c", byLayer, bySlot, byChannel, 0 );
	}
	BOOL GetH320Alias ( u8 &byLayer, u8 &bySlot, u8 &byChannel )
	{
		BOOL bRet = FALSE;
		byLayer   = 0;
		bySlot    = 0; 
		byChannel = 0; 
		if( mtAliasTypeH320ID != m_AliasType )
		{
			return bRet;
		}

		s8 *pachLayerPrefix   = "层";
		s8 *pachSlotPrefix    = "-槽";
		s8 *pachChannelPrefix = "-通道";
		s8 *pachAlias = m_achAlias;

		if( 0 == memcmp( pachAlias, pachLayerPrefix, strlen("层") ) )
		{
			s32  nPos = 0;
			s32  nMaxCHLen = 3; //一字节的最大字串长度
			s8 achLayer[4] = {0};

			//提取层号
			pachAlias += strlen("层");
			for( nPos = 0; nPos < nMaxCHLen; nPos++ )
			{
				if( '-' == pachAlias[nPos] )
				{
					break;
				}
				achLayer[nPos] = pachAlias[nPos];
			}
			if( 0 == nPos || nPos >= nMaxCHLen )
			{
				return bRet;
			}
			achLayer[nPos+1] = '\0';
			byLayer = atoi(achLayer);

			//提取槽号
			pachAlias += nPos;
			if( 0 == memcmp( pachAlias, pachSlotPrefix, strlen("-槽") ) )
			{
				pachAlias += strlen("-槽");
				for( nPos = 0; nPos < nMaxCHLen; nPos++ )
				{
					if( '-' == pachAlias[nPos] )
					{
						break;
					}
					achLayer[nPos] = pachAlias[nPos];
				}
				if( 0 == nPos || nPos >= nMaxCHLen )
				{
					return bRet;
				}
				achLayer[nPos+1] = '\0';
				bySlot = atoi(achLayer);
			
				//提取通道号
				pachAlias += nPos;
				if( 0 == memcmp( pachAlias, pachChannelPrefix, strlen("-通道") ) )
				{
					pachAlias += strlen("-通道");
					memcpy( achLayer, pachAlias, nMaxCHLen );
					achLayer[nMaxCHLen] = '\0';
					byChannel = atoi(achLayer);
					bRet = TRUE;
				}
			}
		}
		return bRet;
	}
	void Print( void ) const
	{
		if( m_AliasType == 0 )
		{
			OspPrintf( TRUE, FALSE, "null alias" );
		}
		else if( m_AliasType == mtAliasTypeTransportAddress )
		{
			OspPrintf( TRUE, FALSE, "IP: 0x%x:%d", 
				     m_tTransportAddr.GetIpAddr(), m_tTransportAddr.GetPort() );
		}		
		else if( m_AliasType == mtAliasTypeE164 )
		{
			OspPrintf( TRUE, FALSE, "E164: %s", m_achAlias ); 
		}
		else if( m_AliasType == mtAliasTypeH323ID )
		{
			OspPrintf( TRUE, FALSE, "H323ID: %s", m_achAlias ); 
		}
		else if( m_AliasType == mtAliasTypeH320ID )
		{
			OspPrintf( TRUE, FALSE, "H320ID: %s", m_achAlias ); 
		}
        else if( m_AliasType == mtAliasTypeH320Alias )
        {
            OspPrintf( TRUE, FALSE, "H320Alias: %s", m_achAlias );
        }
		else
		{
			OspPrintf( TRUE, FALSE, "Other type alias!" ); 
		}
		OspPrintf( TRUE, FALSE, "\n" );
	}
}
/* 
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
*/
PACKED
;

//定义混音模式
typedef enum
{
	mcuNoMix = 0,
	mcuWholeMix,
	mcuPartMix,
    mcuVacMix,
	mcuVacWholeMix,
	mcuVacPartMix   // 该字段已废弃（VAC与定制混音冲突）
} emMcuMixMode;

#define  MAXNUM_MIXING_MEMBER        64
struct TMixParam
{
public:
    TMixParam(void)
    {
        Clear();
    }
    void Clear(void){ memset(this, 0, sizeof(TMixParam));    }

    void SetMode(u8 byMixMode){ m_byMixMode = byMixMode;    }
    u8   GetMode(void) const { return m_byMixMode;    }

    u8   GetMemberNum() const
    {
        return m_byMtNum;
    }
    void AddMember(u8 byMtId)
    {
        if (byMtId == 0)
            return;
        
        if (m_byMtNum < MAXNUM_MIXING_MEMBER)
        {
            m_abyMtList[m_byMtNum++] = byMtId;
        }        
    }
    void DelMember(u8 byMtId)
    {
        if (byMtId == 0)
            return;

        for (u8 byLoop = 0; byLoop < m_byMtNum; byLoop ++ )
        {
            if (m_abyMtList[byLoop] == byMtId)
            {
                for ( u8 byMove = byLoop+1; byMove < m_byMtNum; byMove ++ )
                {
                    m_abyMtList[byMove-1] =  m_abyMtList[byMove];
                }
                m_byMtNum --;
                break;
            }
        }
    }

    void ClearAllMembers()
    {
        m_byMtNum = 0;
    }

    u8 GetMemberByIdx(u8 byIdx)
    {
        if ( byIdx < m_byMtNum )
            return m_abyMtList[byIdx];
        else
            return 0;
    }

    BOOL32 IsMtInMember(u8 byMtId) const
    {
        for (u8 byLoop = 0; byLoop < m_byMtNum; byLoop ++ )
        {
            if (m_abyMtList[byLoop] == byMtId)
            {
                return TRUE;
            }
        }
        return FALSE;
    }
    void SetMtMaxNum(u8 byMtMaxNum){ m_byMtMaxNum = byMtMaxNum;    }
    u8   GetMtMaxNum(void) const { return m_byMtMaxNum;    }
protected:
    u8  m_byMixMode;    //混音模式：mcuNoMix - 不混音
                        //          mcuWholeMix - 全体混音
                        //          mcuPartMix - 定制混音
                        //          mcuVacMix, - VAC 
                        //          mcuVacWholeMix - 带Vac的全体混音
    u8  m_byMtNum;
    u8  m_abyMtList[MAXNUM_MIXING_MEMBER];
    u8  m_byMtMaxNum;   //  记录使用的混音器最大成员数,恢复与启动备份时用到
private:
    u8  m_abyReserved[3];
}
PACKED
;

//录像方式定义
#define		 REC_MODE_NORMAL				0   /* 实时录像 */
#define	     REC_MODE_SKIPFRAME				1	/* 抽帧录像 */

//有关发布方式定义
#define      PUBLISH_MODE_NONE				0	//不发布
#define      PUBLISH_MODE_IMMED				1	//立即发布
#define      PUBLISH_MODE_FIN				2	//录像完毕之后发布

//发布级别
#define      PUBLISH_LEVEL_NORMAL			0	//正常发布
#define      PUBLISH_LEVEL_SECRET			1	//秘密发布

//录像文件类型
#define      RECFILE_NORMAL                 0   //单格式录像文件
#define      RECFILE_DSTREAM                1   //双格式录像文件

// size = 11
struct TRecStartPara
{
protected:
    u8   m_byRecMode;         //录像模式
    u8   m_byPublishMode;     //发布模式
    u8   m_byPublishLevel;    //发布层次
    u8   m_byIsRecLowStream;  //是否录低速码流
    u8   m_byIsRecMainVideo;  //是否录主格式视频码流
    u8   m_byIsRecMainAudio;  //是否录主格式音频码流
    u8   m_byIsRecDStream;    //是否录双流
	u16  m_wRecBitrate;       //录像码率
    u16  m_wRecBitrateSec;    //录像双流码率

public:
	TRecStartPara()
	{
		Reset();
	}
	void Reset(void)
	{
		m_byRecMode = REC_MODE_NORMAL;
		m_byPublishMode = PUBLISH_MODE_NONE;
		m_byPublishLevel = PUBLISH_LEVEL_NORMAL;
        m_byIsRecMainVideo = 1;
        m_byIsRecMainAudio = 1;
        m_byIsRecDStream   = 0;
        m_byIsRecLowStream = 0;
        m_wRecBitrate      = 0;
        m_wRecBitrateSec   = 0;
	}
	void SetRecMode(u8 byMode)
	{
		m_byRecMode = byMode;
	}
	u8 GetRecMode(void) const
	{
		return m_byRecMode;
	}
	void SetPublishMode(u8 byMode)
	{
		m_byPublishMode = byMode;
	}
	u8 GetPublishMode(void) const
	{
		return m_byPublishMode;
	}
    void SetPublishLevel(u8 byLevel)
	{
		m_byPublishLevel = byLevel;
	}
	u8  GetPublishLevel(void) const
	{
		return m_byPublishLevel;
	}
    void SetIsRecLowStream(BOOL32 bRecLowStream)
	{
		m_byIsRecLowStream = ( bRecLowStream ? 1:0);
	}
	BOOL32 IsRecLowStream(void) const 
	{
		return (m_byIsRecLowStream != 0);
	}

    void SetIsRecMainVideo(BOOL32 bRecMainVideo)
	{
		m_byIsRecMainVideo = (bRecMainVideo ? 1:0);
	}
	BOOL32 IsRecMainVideo(void) const
	{
		return (m_byIsRecMainVideo != 0);
	}

    void SetIsRecMainAudio(BOOL32 bRecMainAudio)
	{
		m_byIsRecMainAudio = (bRecMainAudio ? 1:0);
	}
	BOOL32 IsRecMainAudio(void) const
	{
		return (m_byIsRecMainAudio != 0);
	}

    void SetIsRecDStream(BOOL32 bRecDStream)
	{
		m_byIsRecDStream = (bRecDStream ? 1:0);
	}
	BOOL32 IsRecDStream(void) const
	{
		return (m_byIsRecDStream != 0);
	}

	void SetBitRate(u16 wBitRate)
	{
		m_wRecBitrate = htons(wBitRate);
	}
	u16 GetBitRate(void) const
	{
		return ntohs(m_wRecBitrate);
	}

    void SetSecBitRate(u16 wBitRate)
    {
        m_wRecBitrateSec = htons(wBitRate);
    }
    u16 GetSecBitRate(void) const
    {
        return ntohs(m_wRecBitrateSec);
    }

    void Print() const
    {
        
        OspPrintf(TRUE, FALSE, "m_byRecMode:        %d\n", GetRecMode());
        OspPrintf(TRUE, FALSE, "m_byPublishMode:    %d\n", GetPublishMode());
        OspPrintf(TRUE, FALSE, "m_byPublishLevel:   %d\n", GetPublishLevel());
        OspPrintf(TRUE, FALSE, "m_byIsRecMainVideo: %d\n", IsRecMainVideo());
        OspPrintf(TRUE, FALSE, "m_byIsRecMainAudio: %d\n", IsRecMainAudio());
        OspPrintf(TRUE, FALSE, "m_byIsRecLowStream: %d\n", IsRecLowStream());
        OspPrintf(TRUE, FALSE, "m_byIsRecDStream:   %d\n", IsRecDStream());
        OspPrintf(TRUE, FALSE, "m_wRecBitrate:      %d\n", GetBitRate());
        OspPrintf(TRUE, FALSE, "m_wSecRecBitrate:   %d\n", GetSecBitRate());

    }

}
/*
#ifndef WIN32
__attribute__((packed))
#endif
*/
PACKED
;


//定义会议属性结构(会议中不会改变), sizeof = 32
struct TConfAttrb
{
protected:
	u8     m_byOpenMode;        //会议开放方式: 0-不开放,拒绝列表以外的终端 1-根据密码加入 2-完全开放
	u8     m_byEncryptMode;     //会议加密模式: 0-不加密, 1-des加密,2-aes加密
	u8     m_byMulticastMode;   //组播会议方式: 0-不是组播会议 1-组播会议
	u8     m_byDataMode;        //数据会议方式: 0-不包含数据的视音频会议 1-包含数据的视音频会议 2-只有数据的会议
	u8     m_byReleaseMode;     //会议结束方式: 0-不会自动结束 1-无终端时自动结束
    u8     m_byVideoMode;       //会议视频模式: 0-速度优先 1-画质优先
	u8     m_byCascadeMode;     //会议级连方式: 0-不支持合并级联, 1-支持合并级联
	u8     m_byPrsMode;         //丢包重传方式: 0-不重传 1-重传
    u8     m_byHasTvWallModule; //电视墙模板:   0-无电视墙模板  1-有电视墙模板
	u8     m_byHasVmpModule;    //画面合成模板: 0-无画面合成模板  1-有画面合成模板
	u8     m_byDiscussConf;     //是否讨论会议: 0-不是讨论会议(演讲会议) 1-讨论会议 (这一字段仅用来控制会议开始后是否启动混音)
	u8     m_byUseAdapter;		//是否启用适配: 0-不启用任何适配 2-按需要进行(码流，码率)适配 
	u8     m_bySpeakerSrc;		//发言人的源:   0-看自己 1-看主席 2-看上一次发言人 
	u8     m_bySpeakerSrcMode;  //发言人的源的方式: 0-无效值 1-仅视频 2-仅音频 3-视音频
	u8     m_byMulcastLowStream;//是否组播低速码流: 0-不是组播低速码流(组播高速码流) 1-组播低速码流
	u8     m_byAllInitDumb;     //终端入会后是否初始哑音 0-不哑音 1-哑音
	u8	   m_byDualMode;		//会议的双流发起方式: 0-发言人 1-任意终端
	u8     m_byUniformMode;     //码流转发时是否支持归一化整理方式: CONF_UNIFORMMODE_NONE-不重整 CONF_UNIFORMMODE_valid-重整，
	                            //这个处理方式与丢包重传方式互斥
    u16    m_wMulticastPort;    //会议组播起始端口；如果配置是组播会议，需要填写组播地址
    u32    m_dwMulticastIp;     //会议组播地址；如果配置是组播会议，需要填写组播地址
    
    u32    m_dwSatDCastIp;      //卫星分散会议Ip地址
    u16    m_wSatDCastPort;     //卫星分散会议端口
    u8     m_bySatDCastMode;    //是否支持卫星分散会议：0-不支持，1-支持
    u8     m_byEncKeyManual;    //会议密钥模式: 0-自动密钥, 1-手动密钥    

public:
	TConfAttrb( void )
	{
		memset( this, 0, sizeof(TConfAttrb) );
		m_byOpenMode = CONF_OPENMODE_OPEN;
	}

    void   SetOpenMode(u8   byOpenMode){ m_byOpenMode = byOpenMode;} 
    u8     GetOpenMode( void ) const { return m_byOpenMode; }
	void   SetEncryptMode(u8   byEncryptMode){ m_byEncryptMode = byEncryptMode;} 
    u8     GetEncryptMode( void ) const { return m_byEncryptMode; }
    void   SetEncKeyManual(BOOL  bEncKeyManual){ m_byEncKeyManual = bEncKeyManual; }
    BOOL   IsEncKeyManual( void ) const { return m_byEncKeyManual == 0 ? FALSE : TRUE; }
    void   SetMulticastMode(BOOL bMulticastMode){ m_byMulticastMode = bMulticastMode;} 
    BOOL   IsMulticastMode( void ) const { return m_byMulticastMode == 0 ? FALSE : TRUE; }
    void   SetDataMode(u8   byDataMode){ m_byDataMode = byDataMode;} 
    u8     GetDataMode( void ) const { return m_byDataMode; }
    void   SetReleaseMode(BOOL bReleaseMode){ m_byReleaseMode = bReleaseMode;} 
    BOOL   IsReleaseNoMt( void ) const { return m_byReleaseMode == 0 ? FALSE : TRUE; }
    void   SetQualityPri(BOOL bQualityPri){ m_byVideoMode = bQualityPri;} 
    BOOL   IsQualityPri( void ) const { return m_byVideoMode == 0 ? FALSE : TRUE; }
	void   SetSupportCascade(BOOL bCascadeMode){ m_byCascadeMode = (bCascadeMode==TRUE?1:0); }
	BOOL   IsSupportCascade( void ) const { return (m_byCascadeMode != 0 );}
	void   SetPrsMode( BOOL bResendPack ){ m_byPrsMode = bResendPack; }
	BOOL   IsResendLosePack( void ){ return m_byPrsMode == 0 ? FALSE : TRUE; }
	void   SetHasTvWallModule( BOOL bHasTvWallModule ){ m_byHasTvWallModule = bHasTvWallModule; }
	BOOL   IsHasTvWallModule( void ){ return m_byHasTvWallModule == 0 ? FALSE : TRUE; }
	void   SetHasVmpModule( BOOL bHasVmpModule ){ m_byHasVmpModule = bHasVmpModule; }
	BOOL   IsHasVmpModule( void ){ return m_byHasVmpModule == 0 ? FALSE : TRUE; }
	void   SetDiscussConf( BOOL bDiscussConf ){ m_byDiscussConf = bDiscussConf; }
	BOOL   IsDiscussConf( void ){ return m_byDiscussConf == 0 ? FALSE : TRUE; }
    void   SetUseAdapter( BOOL bUseAdapter ){ m_byUseAdapter = bUseAdapter; } 
    BOOL   IsUseAdapter( void ) const { return m_byUseAdapter == 0 ? FALSE : TRUE; }
    void   SetSpeakerSrc( u8 bySpeakerSrc ){ m_bySpeakerSrc = bySpeakerSrc;} 
    u8     GetSpeakerSrc( void ) const { return m_bySpeakerSrc; }
    void   SetSpeakerSrcMode( u8 bySpeakerSrcMode ){ m_bySpeakerSrcMode = bySpeakerSrcMode;} 
    u8     GetSpeakerSrcMode( void ) const { return m_bySpeakerSrcMode; }
	void   SetMulcastLowStream( BOOL bMulcastLowStream ){ m_byMulcastLowStream = bMulcastLowStream;} 
    BOOL   IsMulcastLowStream( void ) const { return m_byMulcastLowStream == 0 ? FALSE : TRUE; }
	void   SetAllInitDumb( BOOL bAllInitDumb ){ m_byAllInitDumb = bAllInitDumb;} 
    BOOL   IsAllInitDumb( void ) const { return m_byAllInitDumb == 0 ? FALSE : TRUE; }
	void   SetUniformMode( BOOL bUniformMode ){ m_byUniformMode = bUniformMode; }
	u8     IsAdjustUniformPack( void ){ return m_byUniformMode; }
	void   SetDualMode(	u8 byDualMode ){ m_byDualMode = byDualMode;	}
	u8	   GetDualMode( void ) const { return m_byDualMode;	}
    void   SetMulticastIp (u32 dwIp) { m_dwMulticastIp = htonl(dwIp); }
    u32    GetMulticastIp ( void ) const { return ntohl(m_dwMulticastIp); }
    void   SetMulticastPort ( u16 wPort) { m_wMulticastPort = htons(wPort); }
    u16    GetMulticastPort ( void ) const { return ntohs(m_wMulticastPort); }
    void   SetSatDCastMode ( BOOL bSatDCastMode ) { m_bySatDCastMode = bSatDCastMode; }
    BOOL   IsSatDCastMode () const { return m_bySatDCastMode == 0 ? FALSE : TRUE;    }
    void   SetSatDCastIp (u32 dwIp) { m_dwSatDCastIp = htonl(dwIp); }
    u32    GetSatDCastIp () const { return ntohl(m_dwSatDCastIp) ; }
    void   SetSatDCastPort (u16 wPort) { m_wSatDCastPort = htons(wPort); }
    u16    GetSatDCastPort () const { return ntohs(m_wSatDCastPort); }

    void   Print( void ) const
	{
		OspPrintf( TRUE, FALSE, "\nConfAttrb:\n" );
		OspPrintf( TRUE, FALSE, "m_byOpenMode: %d\n",   m_byOpenMode);
		OspPrintf( TRUE, FALSE, "m_byEncryptMode: %d\n", m_byEncryptMode);
		OspPrintf( TRUE, FALSE, "m_byMulticastMode: %d\n", m_byMulticastMode);
        OspPrintf( TRUE, FALSE, "m_dwMulticastIp: 0x%x\n", GetMulticastIp());
        OspPrintf( TRUE, FALSE, "m_wMulticastPort: %d\n", GetMulticastPort());
		OspPrintf( TRUE, FALSE, "m_byDataMode: %d\n", m_byDataMode);
		OspPrintf( TRUE, FALSE, "m_byReleaseMode: %d\n", m_byReleaseMode);
		OspPrintf( TRUE, FALSE, "m_byVideoMode: %d\n", m_byVideoMode);
		OspPrintf( TRUE, FALSE, "m_byCascadeMode: %d\n", m_byCascadeMode);
		OspPrintf( TRUE, FALSE, "m_byPrsMode: %d\n", m_byPrsMode);
		OspPrintf( TRUE, FALSE, "m_byHasTvWallModule: %d\n", m_byHasTvWallModule);
		OspPrintf( TRUE, FALSE, "m_byHasVmpModule: %d\n", m_byHasVmpModule);	
		OspPrintf( TRUE, FALSE, "m_byDiscussConf: %d\n", m_byDiscussConf);
		OspPrintf( TRUE, FALSE, "m_byUseAdapter: %d\n", m_byUseAdapter);
		OspPrintf( TRUE, FALSE, "m_bySpeakerSrc: %d\n", m_bySpeakerSrc);
		OspPrintf( TRUE, FALSE, "m_bySpeakerSrcMode: %d\n", m_bySpeakerSrcMode);
		OspPrintf( TRUE, FALSE, "m_byMulcastLowStream: %d\n", m_byMulcastLowStream);
		OspPrintf( TRUE, FALSE, "m_byAllInitDumb: %d\n", m_byAllInitDumb);
		OspPrintf( TRUE, FALSE, "m_byUniformMode: %d\n", m_byUniformMode);
		OspPrintf( TRUE, FALSE, "m_byDualMode: %d\n", m_byDualMode);
        OspPrintf( TRUE, FALSE, "m_bySatDCastMode: %d\n", m_bySatDCastMode);
        OspPrintf( TRUE, FALSE, "m_dwSatDCastIp: 0x%x\n", GetSatDCastIp());
        OspPrintf( TRUE, FALSE, "m_wSatDCastPort: %d\n", GetSatDCastPort());
	}
}
/*
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
*/
PACKED
;


// 创会时自动录像属性，不能调用memset清空，请用Reset()接口, size = 28
struct TConfAutoRecAttrb
{    
protected:
    u8     m_byAutoRec;         //是否会议开始自动录像：0-不支持，1-支持
    u8     m_byRecEqpId;    //自动录像的录像机id        

    // 开始时间和结束时间都不支持跨天，结束时间必须在开始时间之后
    TKdvTime m_tTimeStart;      //开始录像的启动时间.只关心 时/分/秒，year设置为0即不需要设置时间，会议开始后自动开始
    TKdvTime m_tTimeEnd;        //自动录像结束的时间.只关心 时/分/秒，year设置为0即不需要设置时间，需要用户手动停止

public:    
    TRecStartPara m_tRecParam;  //自动录像参数

protected:
    u8     m_byWeekdays;        //开始录像的日期类型，bit0(Sunday)-6(Sat)置1表示当天需要录像

public:
    TConfAutoRecAttrb()
    {
        Reset();
    }

    void   Reset()
    {
        memset(this, 0, sizeof(TConfAutoRecAttrb));

        m_tRecParam.Reset();
        m_tRecParam.SetIsRecDStream(TRUE);  // 默认录双流
        m_tRecParam.SetPublishMode(PUBLISH_MODE_IMMED); // 默认立即发布
        SetRecAnyDay(); // 默认每天都录
    }
    
    void     SetAutoRec(BOOL32 bEnableAuto) { m_byAutoRec = bEnableAuto ?  1 : 0; }
    BOOL32   IsAutoRec() const { return (m_byAutoRec == 1); }
    void     SetRecEqp(u8 byRecId) { m_byRecEqpId = byRecId; }
    u8       GetRecEqp() const { return m_byRecEqpId; }

    void     SetRecAnyDay()   //设置每天都录像
    {
        m_byWeekdays = 0x7F;
    }
    void     SetRecNoDay()    //设置每天都不录,注意：如果指定了m_byAutoRec=1则m_byWeekdays = 0是不合法的,仅用于临时清空
    {
        m_byWeekdays = 0;
    }
    void     SetRecWeekDay(u8 byDay, BOOL32 bEnable)  // 指定某天录像 0 - Sunday, 1 - Monday,  6- Satday
    {
        if (bEnable)
            m_byWeekdays |= (1<<byDay);
        else
            m_byWeekdays &= ~(1<<byDay);
    }
    BOOL32 IsRecAnyDay() const  // 是否每天都录像
    {
        return (m_byWeekdays == 0x7F);
    }
    BOOL32 IsRecNoDay() const   // 是否每天都不录
    {
        return (m_byWeekdays == 0);
    }
    BOOL32 IsRecWeekDay(u8 byDay) const //是否特定天录像
    {
        return  ((m_byWeekdays & (1<<byDay)) >> byDay) ? TRUE : FALSE;
    }

    void     SetStartTime(const TKdvTime &tStartTime) { m_tTimeStart = tStartTime; }
    TKdvTime GetStartTime() const { return m_tTimeStart; }
    void     SetEndTime(const TKdvTime &tEndTime) { m_tTimeEnd = tEndTime; }
    TKdvTime GetEndTime() const { return m_tTimeEnd; }
    void     SetRecParam(const TRecStartPara &tParam) { m_tRecParam = tParam; }
    TRecStartPara GetRecParam() const { return m_tRecParam; }

    void     Print() const
    {   
        OspPrintf( TRUE, FALSE, "Conf Auto Rec Attrib:\n");
        OspPrintf( TRUE, FALSE, "m_byAutoRec: %d\n", IsAutoRec());
        if (IsAutoRec())
        {
            OspPrintf( TRUE, FALSE, "m_byRecEqpId: %d\n", m_byRecEqpId);
            OspPrintf( TRUE, FALSE, "m_byWeekdays: 0x%x\n", m_byWeekdays);        
            OspPrintf( TRUE, FALSE, "m_tTimeStart: ");
            m_tTimeStart.Print();
            OspPrintf( TRUE, FALSE, "\n");        
            OspPrintf( TRUE, FALSE, "m_tTimeEnd: ");
            m_tTimeEnd.Print();
            OspPrintf( TRUE, FALSE, "\n");
            //        OspPrintf( TRUE, FALSE, "m_szRecName: %s\n", GetRecName());
            OspPrintf( TRUE, FALSE, "m_tRecParam: \n");
            m_tRecParam.Print(); 
        }
    }
}
/*
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
*/
PACKED
;

// 创会时会议属性，4.0R3扩展, size = 76
struct TConfAttrbEx
{
    enum emMaskResEx
    {
        emRes1080 = 0x01,   //暂时不用，留作扩展
        emRes720p = 0x02,
        emRes4Cif = 0x04,
        emResCif  = 0x08
    };

protected:
    u8                m_bySatDCastChnl;             //卫星会议上传允许的通道数
    TConfAutoRecAttrb m_tAutoRecAttrb;              //自动录像属性
    u8                m_byVmpAutoAdapte;            //画面合成自动调整分辨率
    s8                m_achGKUsrName[MAX_LEN_GK_USRNAME];         //GK用户名
    s8                m_achGKPwd[MAX_LEN_GK_PWD];                 //GK密码
    u8                m_byOverrunPolicy;            //8000B专用。若会议讨论与VMP/BAS同时使用，当会议终端增加到超过讨论能力，是否自动停止。 1-自动停止，0-切换到定制混音
    u8                m_byMainResEx;                //会议支持的主视频分辨率扩展
	u8                m_bySchemeIdxInBatchPoll;     //正在hdu批量轮询的预案索引号
	u8                m_byConfLevel;                //会议级别0-255
    u8                m_byRealSatConf;              //是否为真正的卫星会议

private:
    u8                m_abyReserved[9];            //保留字段

public:
    TConfAttrbEx()
    {
        Reset();
    }
    void Reset()
    {
        memset(this, 0, sizeof(TConfAttrbEx));
        m_tAutoRecAttrb.Reset();
	    m_byConfLevel = 255;
    }

    void   SetSchemeIdxInBatchPoll(u8 bySchemeIdxInBatchPoll) { m_bySchemeIdxInBatchPoll = bySchemeIdxInBatchPoll; }
    u8     GetSchemeIdxInBatchPoll() const { return m_bySchemeIdxInBatchPoll; }


    void   SetSatDCastChnlNum(u8 byNum) { m_bySatDCastChnl = byNum; }
    u8     GetSatDCastChnlNum() const { return m_bySatDCastChnl; }

    void   SetAutoRecAttrb(const TConfAutoRecAttrb& tAttrb ) { m_tAutoRecAttrb = tAttrb; }
    TConfAutoRecAttrb GetAutoRecAttrb() const { return m_tAutoRecAttrb; }

    void   SetVmpAutoAdapt(BOOL32 bAutoAdapt) { m_byVmpAutoAdapte = bAutoAdapt ? 1 : 0; }
    BOOL32 IsVmpAutoAdapt() const { return m_byVmpAutoAdapte == 1 ? TRUE : FALSE;}

    void SetGKUsrName(LPCSTR pszName)
    {
        if ( pszName != NULL )
        {
            u16 wLen = min( MAX_LEN_GK_USRNAME-1, strlen(pszName) );
            strncpy( m_achGKUsrName, pszName, wLen );
            m_achGKUsrName[wLen] = '\0';
        }
        return;
    }
    LPCSTR GetGKUsrName() const { return m_achGKUsrName; }
    
    void SetGKPwd(LPCSTR pszPwd)
    {
        if ( pszPwd != NULL )
        {
            u16 wLen = min( MAX_LEN_GK_PWD-1, strlen(pszPwd) );
            strncpy( m_achGKPwd, pszPwd, wLen );
            m_achGKPwd[wLen] = '\0';
        }
        return;
    }
    LPCSTR GetGKPwd(void) const { return m_achGKPwd; }

    void SetDiscussAutoStop()
    {
        m_byOverrunPolicy = 1;
    }
    void SetDiscussAutoSwitch2Mix()
    {
        m_byOverrunPolicy = 0;
    }
    BOOL32 IsDiscussAutoStop() const
    {
        return (m_byOverrunPolicy == 1 ? TRUE : FALSE );
    }
    void SetResEx1080(BOOL32 bIsAdd = TRUE)
    {
        SETBITSTATUS(m_byMainResEx, emRes1080, bIsAdd)
    }
    BOOL32 IsResEx1080(void) const
    {
        return GETBITSTATUS(m_byMainResEx, emRes1080);
    }
    void SetResEx720(BOOL32 bIsAdd = TRUE)
    {
        SETBITSTATUS(m_byMainResEx, emRes720p, bIsAdd)
    }
    BOOL32 IsResEx720(void) const
    {
        return GETBITSTATUS(m_byMainResEx, emRes720p);
    }
    void SetResEx4Cif(BOOL32 bIsAdd = TRUE)
    {
        SETBITSTATUS(m_byMainResEx, emRes4Cif, bIsAdd)
    }
    BOOL32 IsResEx4Cif(void) const
    {
        return GETBITSTATUS(m_byMainResEx, emRes4Cif);
    }
    void SetResExCif(BOOL32 bIsAdd = TRUE)
    {
        SETBITSTATUS(m_byMainResEx, emResCif, bIsAdd)
    }
    BOOL32 IsResExCif(void) const
    {
        return GETBITSTATUS(m_byMainResEx, emResCif);
    }
	void SetConfLevel(u8 byLevel)
	{
		m_byConfLevel = byLevel;
	}
	u8   GetConfLevel()
	{
		return m_byConfLevel;
	}
    void SetConfRealSat(BOOL32 bSat)
    {
        m_byRealSatConf = bSat ? 1 : 0;
    }
    BOOL32 IsConfRealSat(void) const
    {
        return m_byRealSatConf == 0 ? FALSE : TRUE;
    }
    void Print() const
    {
        OspPrintf( TRUE, FALSE, "m_bySatDCastChnl: %d\n", GetSatDCastChnlNum());
        m_tAutoRecAttrb.Print();
        OspPrintf( TRUE, FALSE, "m_byVmpAutoAdapte:  %d\n", IsVmpAutoAdapt());        
        OspPrintf( TRUE, FALSE, "m_byOverrunPolicy:  %s\n", IsDiscussAutoStop() ? "Auto Stop" : "Switch to Mix");
        OspPrintf( TRUE, FALSE, "GK Charge User Name: %s, Pwd: %s\n", m_achGKUsrName, m_achGKPwd );
        OspPrintf( TRUE, FALSE, "ConfMainResEx: <1080:%d, 720:%d, 4Cif.%d, Cif.%d>\n", IsResEx1080(), IsResEx720(), IsResEx4Cif(), IsResExCif());
		OspPrintf( TRUE, FALSE, "m_byConfLevel:      %d\n", m_byConfLevel);
		OspPrintf( TRUE, FALSE, "m_byRealSatConf:    %d\n", m_byRealSatConf );
    }
}
PACKED
;



/*电视墙模板结构和画面合成模板结构说明:
目前创会时的消息体: TConfInfo + 2 byte(TMtAlias数组打包长度,即下面的n)
                  + n byte(TMtAlias数组打包) + TMultiTvWallModule(可选) + TVmpModule(可选) */
//电视墙模板结构
struct TTvWallModule
{
	TEqp m_tTvWall;                                     //会控指定的电视墙
    u8   m_abyTvWallMember[MAXNUM_PERIEQP_CHNNL];       //会控指定的电视墙成员索引（即创会时TMtAlias数组索引+1）
    u8   m_abyMemberType[MAXNUM_PERIEQP_CHNNL];         //电视墙成员跟随类型,TW_MEMBERTYPE_MCSSPEC,TW_MEMBERTYPE_SPEAKER...
  
public:
    TTvWallModule(void) { memset(this, 0, sizeof(TTvWallModule)); }

    TEqp GetTvEqp(void) const
    {
        return m_tTvWall;
    }
    
    void SetTvEqp(TEqp tTvWall)
    {
        m_tTvWall = tTvWall;
    }
    
    void EmptyTvMember(void)
    {
        memset((void*)m_abyTvWallMember, 0, sizeof(m_abyTvWallMember));
        memset((void*)m_abyMemberType, 0, sizeof(m_abyMemberType));
    }

    void SetTvChannel(u8 byTvChl, u8 byMtIdx, u8 byMemberType) // 设置指定通道
    {
        if(byTvChl < MAXNUM_PERIEQP_CHNNL)
        {
            m_abyTvWallMember[byTvChl] = byMtIdx;
            m_abyMemberType[byTvChl] = byMemberType;
        }
    }
    
    void RemoveTvMember(u8 byTvChl) // 移除电视墙指定通道
    {
        if(byTvChl < MAXNUM_PERIEQP_CHNNL)
        {
            m_abyTvWallMember[byTvChl] = 0;
            m_abyMemberType[byTvChl] = 0;
        }
    }
    
    void RemoveMtInTvMember(u8 byMtIdx) // 移除电视墙中所有该终端
    {
        for(u8 byTvChlLp = 0; byTvChlLp < MAXNUM_PERIEQP_CHNNL; byTvChlLp++)
        {
            if(m_abyTvWallMember[byTvChlLp] == byMtIdx)
            {
                m_abyTvWallMember[byTvChlLp] = 0;
				// 对于TW_MEMBERTYPE_VCSAUTOSPEC类型标识含义为自动模式下该通道可用，所以对其不清空
				if (m_abyMemberType[byTvChlLp] != TW_MEMBERTYPE_VCSAUTOSPEC)
				{
					m_abyMemberType[byTvChlLp] = 0;
				}
                
            }
        }
    }

    void Clear(void)
    {
        memset(&m_tTvWall, 0, sizeof(m_tTvWall));
        memset(m_abyTvWallMember, 0, sizeof(m_abyTvWallMember) );
        memset(m_abyMemberType, 0, sizeof(m_abyMemberType));
    }
}
/*
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
*/
PACKED
;

// 会议模板中支持多电视墙结构
struct TMultiTvWallModule
{
    u8 m_byTvModuleNum; // 电视墙数目
    TTvWallModule  m_atTvWallModule[MAXNUM_PERIEQP_CHNNL];

public:

    TMultiTvWallModule(void){ memset(this, 0, sizeof(TMultiTvWallModule));}

    void SetTvModuleNum( u8 byTvModuleNum ) { m_byTvModuleNum = (byTvModuleNum <= MAXNUM_PERIEQP_CHNNL) ? byTvModuleNum : m_byTvModuleNum;}
    u8     GetTvModuleNum( void ) const { return m_byTvModuleNum; }
    BOOL32 SetTvModule(u8 byTvModueIdx, TTvWallModule m_tTvWallModule)
    {
        BOOL32 bRet = TRUE;
        if( byTvModueIdx < MAXNUM_PERIEQP_CHNNL )
        {
            m_atTvWallModule[byTvModueIdx] = m_tTvWallModule;
        }
        else
        {
            bRet = FALSE;
        }
        return bRet;
    }

    BOOL32  GetTvModuleByIdx(u8 byTvIdx, TTvWallModule& tTvWallModule) const // 按序号取电视墙模板
    {
        BOOL32 bRet = TRUE;
        if( 0 != m_byTvModuleNum && byTvIdx < MAXNUM_PERIEQP_CHNNL)
        {
            tTvWallModule = m_atTvWallModule[byTvIdx];
        }
        else
        {
            bRet = FALSE;
        }
        return bRet;
    }

    BOOL32  GetTvModuleByTvId(u8 byTvId, TTvWallModule& tTvWallModule) const
    {
        BOOL32 bRet = TRUE;
        if( 0 != m_byTvModuleNum )
        {
            for(u8 byTvLp = 0; byTvLp < MAXNUM_PERIEQP_CHNNL; byTvLp++)
            {
                if( byTvId == m_atTvWallModule[byTvLp].m_tTvWall.GetEqpId() )
                {
                    tTvWallModule = m_atTvWallModule[byTvLp];
                    break;
                }
            }
        }
        else
        {
            bRet = FALSE;
        }
        return bRet;
    }

    void SetTvWallMember(u8 byTvId, u8 byTvChl, u8 byMtIdx, u8 byMemberType)
    {
        for(u8 byTvLp = 0; byTvLp < MAXNUM_PERIEQP_CHNNL; byTvLp++)
        {
            if(m_atTvWallModule[byTvLp].GetTvEqp().GetEqpId() == byTvId)
            {
                m_atTvWallModule[byTvLp].SetTvChannel(byTvChl, byMtIdx, byMemberType);
                break;
            }
        }
    }

    void RemoveMtByTvId(u8 byTvId, u8 byMtIdx )
    {
        for(u8 byTvLp = 0; byTvLp < MAXNUM_PERIEQP_CHNNL; byTvLp++)
        {
            if(m_atTvWallModule[byTvLp].GetTvEqp().GetEqpId() == byTvId)
            {
                m_atTvWallModule[byTvLp].RemoveMtInTvMember(byMtIdx);
                break;
            }
        }
    }

    void Clear(void)
    {
        m_byTvModuleNum = 0;
        memset(m_atTvWallModule, 0, sizeof(m_atTvWallModule) );
    }

}
/*
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
*/
PACKED
;

//画面合成模板结构 
struct TVmpModule
{                        
	TVMPParam m_tVMPParam;                              //会控指定的画面合成参数
	u8        m_abyVmpMember[MAXNUM_MPUSVMP_MEMBER];        //会控指定的画面合成成员索引（即创会时TMtAlias数组索引+1）
    u8        m_abyMemberType[MAXNUM_MPUSVMP_MEMBER];       //画面合成成员的跟随方式, VMP_MEMBERTYPE_MCSSPEC, VMP_MEMBERTYPE_SPEAKER...

    TVmpModule(void) { EmptyMember(); }

    // 清空所有成员
    void EmptyMember()
    {
        memset(this, 0, sizeof(TVmpModule));    
    }

    // 设置某个通道
    void SetVmpMember(u8 byChnlIdx, u8 byMtIdx, u8 byMemberType)
    {
        if (byChnlIdx < MAXNUM_VMP_MEMBER)
        {
            m_abyVmpMember[byChnlIdx]  = byMtIdx;
            m_abyMemberType[byChnlIdx] = byMemberType;
        }
    }

    // 移除某个通道
    void RemoveVmpMember(u8 byChnlIdx) 
    {
        if(byChnlIdx < MAXNUM_VMP_MEMBER)
        {
            m_abyVmpMember[byChnlIdx]  = 0;
            m_abyMemberType[byChnlIdx] = 0;
        }
    }

    // 设置合成参数
    void SetVmpParam(const TVMPParam &tParam)
    {
        m_tVMPParam = tParam;
    }

    // 取得合成参数
    TVMPParam GetVmpParam()
    {
        return m_tVMPParam;
    }
}
/*
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
*/
PACKED
;

//会议信息基本结构
struct TBasicConfInfo
{
    TMt m_tSpeaker;
	TMt m_tChairMan;

public:
    TBasicConfInfo(void) { memset(this, 0, sizeof(TBasicConfInfo)); }
    void    SetSpeaker(const TMt & tSpeaker) { m_tSpeaker = tSpeaker; }
    TMt     GetSpeaker(void) const { return m_tSpeaker; }
    void    SetChairman(const TMt & tChair) { m_tChairMan = tChair; }
    TMt     GetChairman(void) const { return m_tChairMan; }
}
/*
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
*/
PACKED
;

//简化的会议信息结构
struct TSimConfInfo : public TBasicConfInfo
{
//[20100526]fxh 与R6-SP3对齐，仅单变量可实现混音状态的通告
protected:
// 	u8  m_byVACMode;
// 	u8  m_byDiscussMode;
	u8  m_byReserved1;
	u8  m_byMixMode;
//[20100526]
	u8  m_byVMPMode;
	u8  m_byReserved;
public:
// 	void   SetVACMode(BOOL bVACMode){ m_byVACMode = bVACMode;} 
// 	BOOL   IsVACMode( void ) const { return m_byVACMode == 0 ? FALSE : TRUE; }
// 	void   SetDiscussMode(u8   byDiscussMode){ m_byDiscussMode = byDiscussMode;} 
// 	BOOL   IsDiscussMode( void ) const { return m_byDiscussMode == 0 ? FALSE : TRUE; }
	//设置的是混音模式
	void   SetMixMode(u8   byMixMode){ m_byMixMode = byMixMode;} 
	u8     GetMixerMode() const { return m_byMixMode; }

	//判断是不是语音激励
	BOOL   IsVACMode( void ) const { return (m_byMixMode == mcuVacMix) || (m_byMixMode == mcuVacWholeMix) || (m_byMixMode == mcuVacPartMix) ? TRUE : FALSE; }
	//判断是不是会议讨论
	BOOL   IsDiscussMode( void ) const { return (m_byMixMode == mcuWholeMix) || (m_byMixMode == mcuVacWholeMix) ? TRUE : FALSE; }
	//判断时候是定制混音
	BOOL   IsSpecMix( void ) const {return (m_byMixMode == mcuPartMix) || (m_byMixMode == mcuVacPartMix) ? TRUE : FALSE; }

	void   SetVMPMode(u8   byVMPMode){ m_byVMPMode = byVMPMode;} 
	u8     GetVMPMode( void ) const { return m_byVMPMode; }
}
/*
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
*/
PACKED
;


//定义会议方式结构(会议中会改变), sizeof = 24
struct TConfMode
{
protected:
	u8     m_byTakeMode;        //会议举行方式: 0-预约 1-即时 2-会议模板 
	u8     m_byLockMode;        //会议锁定方式: 0-不锁定,所有会控可见可操作 1-根据密码操作此会议 2-某个会议控制台锁定
    u8     m_byCallMode;        //呼叫终端方式: 0-不呼叫终端，手动呼叫 1-呼叫一次 2-定时呼叫未与会终端
    u8     m_byRollCallMode;    //会议点名方式：0-非点名模式；1-VMP点名模式；2-点名人点名模式；3-被点名人点名模式.
    u8     m_byHduInBatchPoll;  //会议中hdu预案是否在批量轮询 0-会议没有进行hdu批量轮询；1-正在hdu批量轮询；2-暂停批量轮询

	//u8     m_byVACMode;       //语音激励方式: 0-不启用语音激励控制发言(导演控制发言) 1-启用语音激励控制发言
	//u8     m_byAudioMixMode;  //混音方式:     0-不混音 1-正在进行某种混音
	u8     m_byRecordMode;      //会议录像方式: (BIT:0-6)0-不录像 1-录像 2-录像暂停; BIT7 = 0 实时 1抽帧录像
	u8     m_byPlayMode;        //会议放像方式: 0-不放像 1-放像 2-放像暂停 3-快进 4-快退
	u8     m_byBasMode;         //码率适配方式: BIT0-是否RTP头适配 BIT1-是否码率适配 BIT2-是否类型适配
	u8     m_byPollMode;        //会议轮询方式: 0-不轮询广播 1-仅图像轮询广播 2-轮流发言
    u8     m_byHDBasMode;       //高清适配方式: BIT0-是否高清主视频适配 BIT1-是否双流适配 BIT2-是否高清级联适配 // zgc, 2008-08-21
	//u8     m_byDiscussMode;   //会议讨论模式: 0-非讨论模式(演讲模式) 1-讨论模式(定制或者智能)
	u8     m_byForceRcvSpeaker; //强制收看发言: 0-不强制收看发言人 1-强制收看发言人
	u8     m_byNoChairMode;     //会议主席模式: 0-不是无主席方式 1-无主席方式
	u8     m_byRegToGK;         //会议注册GK情况: 0-会议未在GK上注册 1-会议在GK上成功注册
    u8     m_byReserved6;
	//u8     m_byMixSpecMt;		//是否指定终端混音: 0-不是定制混音(智能混音) 1-指定终端混音
	u8	   m_byGkCharge;		//gk计费认证是否通过 1－通过，0－认证失败
	u8	   m_byReserved2;		//保留字段
	u32    m_dwCallInterval;    //定时呼叫时的呼叫间隔：(单位：秒，最小为5秒)（网络序）
	u32    m_dwCallTimes;       //定时呼叫时的呼叫次数（网络序）
	
public:
	TConfMode( void ){ memset( this, 0, sizeof(TConfMode) ); }
    void   SetTakeMode(u8 byTakeMode){ m_byTakeMode = byTakeMode | (m_byTakeMode&0x80); } 
    u8     GetTakeMode( void ) const { return (m_byTakeMode&0x0F); }

	u8     GetHduInBatchPoll( void ){ return m_byHduInBatchPoll; }
	void   SetHduInBatchPoll( u8 byHduInBatchPoll ){ m_byHduInBatchPoll = byHduInBatchPoll; }

    void   SetTakeFromFile(BOOL32 bFromFile) // MCU 内部使用
    {
        if (bFromFile)
            m_byTakeMode |= 0x80;
        else
            m_byTakeMode &= 0x0F;
    }
    BOOL32 IsTakeFromFile(void) const
    {
        return ((m_byTakeMode&0x80)==0x80);
    }
    void   SetLockMode(u8   byLockMode){ m_byLockMode = byLockMode;} 
    u8     GetLockMode( void ) const { return m_byLockMode; }
    void   SetCallMode(u8   byCallMode){ m_byCallMode = byCallMode;} 
    u8     GetCallMode( void ) const { return m_byCallMode; }
    void   SetRollCallMode( u8 byMode ) { m_byRollCallMode = byMode;    }
    u8     GetRollCallMode( void ) const { return m_byRollCallMode;    }
	void   SetCallInterval(u32 dwCallInterval){ m_dwCallInterval = htonl(dwCallInterval);} 
    u32    GetCallInterval( void ) const { return ntohl(m_dwCallInterval); }
	void   SetCallTimes(u32 dwCallTimes){ m_dwCallTimes = htonl(dwCallTimes);} 
    u32    GetCallTimes( void ) const { return ntohl(m_dwCallTimes); }
    //void   SetVACMode(BOOL bVACMode){ m_byVACMode = bVACMode;} 
    //BOOL   IsVACMode( void ) const { return m_byVACMode == 0 ? FALSE : TRUE; }
    //void   SetAudioMixMode(BOOL bAudioMixMode){ m_byAudioMixMode = bAudioMixMode;} 
    //BOOL   IsAudioMixMode( void ) const { return m_byAudioMixMode == 0 ? FALSE : TRUE; }
	void   SetRegToGK( BOOL bRegToGK ){ m_byRegToGK = bRegToGK; }
	BOOL   IsRegToGK( void ) const { return m_byRegToGK == 0 ? FALSE : TRUE; }
    void   SetGkCharge( BOOL bCharge ) { m_byGkCharge = bCharge ? 1 : 0; }
    BOOL   IsGkCharge( void ) const { return (1 == m_byGkCharge ? TRUE : FALSE); }
    void   SetRecordMode(u8   byRecordMode)
	{   byRecordMode   &= 0x7f ;
		m_byRecordMode &= 0x80 ;
		m_byRecordMode |= byRecordMode;
	} 
    u8     GetRecordMode( void ) const { return m_byRecordMode&0x7f; }
	
	//判断当前是否在抽帧录像，若是返回TRUE否则返回FALSE
	BOOL   IsRecSkipFrame() const{ return m_byRecordMode&0x80 ? TRUE:FALSE;}
	//bSkipFrame = TRUE 设置当前为抽帧录像,否则实时录像
	void   SetRecSkipFrame(BOOL bSkipFrame)
	{
		if(bSkipFrame)
			m_byRecordMode |=0x80;
		else 
			m_byRecordMode &=0x7f;
	}
    void   SetPlayMode( u8  byPlayMode ){ m_byPlayMode = byPlayMode;} 
    u8     GetPlayMode( void ) const { return m_byPlayMode; }
    void   SetBasMode( u8  byBasMode, BOOL32 bHasBasMode )
	{ 
		if( bHasBasMode )
		{
			m_byBasMode |= (1<<(byBasMode-1)) ;
		}
		else
		{
			m_byBasMode &= ~(1<<(byBasMode-1));
		}
	} 
    BOOL   GetBasMode( u8  byBasMode ) const 
	{
        if ( CONF_BASMODE_NONE == byBasMode )
            return FALSE;
        else
		    return m_byBasMode & (1<<(byBasMode-1));
	}
    u8     GetBasModeValue() const
    {
        return m_byBasMode;
    }
    void   SetHDBasMode( u8  byHDBasMode, BOOL32 bHasHDBasMode )
    { 
        if( bHasHDBasMode )
        {
            m_byHDBasMode |= (1<<(byHDBasMode-1)) ;
        }
        else
        {
            m_byHDBasMode &= ~(1<<(byHDBasMode-1));
        }
    } 
    BOOL   GetHDBasMode( u8  byHDBasMode ) const 
    {
        if ( CONF_HDBASMODE_NONE == byHDBasMode )
            return FALSE;
        else
            return m_byHDBasMode & (1<<(byHDBasMode-1));
    }
    u8     GetHDBasModeValue() const
    {
        return m_byHDBasMode;
    }
    void   SetPollMode(u8   byPollMode){ m_byPollMode = byPollMode;} 
    u8     GetPollMode( void ) const { return m_byPollMode; }
    //void   SetDiscussMode(u8   byDiscussMode){ m_byDiscussMode = byDiscussMode;} 
    //BOOL   IsDiscussMode( void ) const { return m_byDiscussMode == 0 ? FALSE : TRUE; }  
    void   SetForceRcvSpeaker(u8   byForceRcvSpeaker){ m_byForceRcvSpeaker = byForceRcvSpeaker;} 
    BOOL   IsForceRcvSpeaker( void ) const { return m_byForceRcvSpeaker == 0 ? FALSE : TRUE; }
    void   SetNoChairMode(u8   byNoChairMode){ m_byNoChairMode = byNoChairMode;} 
    BOOL   IsNoChairMode( void ) const { return m_byNoChairMode == 0 ? FALSE : TRUE; }
    //void   SetMixSpecMt( BOOL bMixSpecMt ){ m_byMixSpecMt = bMixSpecMt;} 
    //BOOL   IsMixSpecMt( void ) const { return m_byMixSpecMt == 0 ? FALSE : TRUE; }
	void   Print( void ) const
	{
		OspPrintf( TRUE, FALSE, "\nConfMode:\n" );
		OspPrintf( TRUE, FALSE, "m_byTakeMode: %d\n", m_byTakeMode);
		OspPrintf( TRUE, FALSE, "m_byLockMode: %d\n", m_byLockMode);
		OspPrintf( TRUE, FALSE, "m_byCallMode: %d\n", m_byCallMode);
		OspPrintf( TRUE, FALSE, "m_dwCallInterval: %d\n", GetCallInterval());
		OspPrintf( TRUE, FALSE, "m_dwCallTimes: %d\n", GetCallTimes());
		//OspPrintf( TRUE, FALSE, "m_byVACMode: %d\n", m_byVACMode);
		//OspPrintf( TRUE, FALSE, "m_byAudioMixMode: %d\n", m_byAudioMixMode);
		OspPrintf( TRUE, FALSE, "m_byRecordMode: %d\n", m_byRecordMode);
		OspPrintf( TRUE, FALSE, "m_byPlayMode: %d\n", m_byPlayMode);
		OspPrintf( TRUE, FALSE, "m_byBasMode: %d\n", m_byBasMode);
        OspPrintf( TRUE, FALSE, "m_byHDBasMode: %d\n", m_byHDBasMode);
		OspPrintf( TRUE, FALSE, "m_byPollMode: %d\n", m_byPollMode);
		//OspPrintf( TRUE, FALSE, "m_byDiscussMode: %d\n", m_byDiscussMode);
		OspPrintf( TRUE, FALSE, "m_byForceRcvSpeaker: %d\n", m_byForceRcvSpeaker);
		OspPrintf( TRUE, FALSE, "m_byNoChairMode: %d\n", m_byNoChairMode);
		OspPrintf( TRUE, FALSE, "m_byRegToGK: %d\n", m_byRegToGK);
        OspPrintf( TRUE, FALSE, "m_byGkCharge: %d\n", m_byGkCharge );
		//OspPrintf( TRUE, FALSE, "m_byMixSpecMt: %d\n", m_byMixSpecMt);
		OspPrintf( TRUE, FALSE, "m_byRollCallMode: %d\n", m_byRollCallMode );
	}
}
/*
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
*/
PACKED
;

//定义会议状态结构, sizeof = 430
struct TConfStatus
{
public:
    TMt 	      m_tChairman;	      //主席终端，MCU号为0表示无主席
    TMt		      m_tSpeaker;		  //发言终端，MCU号为0表示无发言人
    TConfMode     m_tConfMode;        //会议方式
    TRecProg	  m_tRecProg;		  //当前录像进程,仅录像状态时有效
    TRecProg	  m_tPlayProg;	      //当前放像进程,仅放像状态时有效
    TPollInfo     m_tPollInfo;        //会议轮询参数,仅轮询时有较
    TTvWallPollInfo     m_tTvWallPollInfo;  //电视墙当前轮询参数，仅轮询时有效
	THduPollInfo  m_tHduPollInfo;     //hdu当前轮询参数，仅轮询时有效
    TMixParam     m_tMixParam;        //当前混音参数
    TVMPParam     m_tVMPParam;        //当前视频复合参数，仅视频复合时有效
    TVMPParam     m_tVmpTwParam;      //当前VMPTW参数
    u8            m_byPrs;            //当前包重传状态


public:
    BOOL   HasChairman(void) const { return m_tChairman.GetMtId()==0 ? FALSE : TRUE; }	
	TMt    GetChairman(void) const { return m_tChairman; }
	void   SetNoChairman(void) { memset( &m_tChairman, 0, sizeof( TMt ) ); }
	void   SetChairman(TMt tChairman) { m_tChairman = tChairman; }
	BOOL   HasSpeaker(void) const { return m_tSpeaker.GetMtId()==0 ? FALSE : TRUE; }
    TMt    GetSpeaker(void) const { return m_tSpeaker; }
	void   SetNoSpeaker(void) { memset( &m_tSpeaker, 0, sizeof( TMt ) ); }
	void   SetSpeaker(TMt tSpeaker) { m_tSpeaker = tSpeaker; }
    void          SetConfMode(TConfMode tConfMode) { m_tConfMode = tConfMode; } 
    TConfMode     GetConfMode(void) const { return m_tConfMode; }
    void          SetRecProg(TRecProg tRecProg){ m_tRecProg = tRecProg; } 
    TRecProg      GetRecProg(void) const { return m_tRecProg; }
    void          SetPlayProg(TRecProg tPlayProg){ m_tPlayProg = tPlayProg; } 
    TRecProg      GetPlayProg(void) const { return m_tPlayProg; }
    void          SetVmpParam(TVMPParam tVMPParam){ m_tVMPParam = tVMPParam;} 
    TVMPParam     GetVmpParam(void) const { return m_tVMPParam; }

	//会议进行状态
	BOOL IsScheduled( void ) const { return m_tConfMode.GetTakeMode() == CONF_TAKEMODE_SCHEDULED ? TRUE : FALSE; }
	void SetScheduled( void ){ m_tConfMode.SetTakeMode( CONF_TAKEMODE_SCHEDULED ); }
	BOOL IsOngoing( void ) const { return m_tConfMode.GetTakeMode() == CONF_TAKEMODE_ONGOING ? TRUE : FALSE; }
	void SetOngoing( void ){ m_tConfMode.SetTakeMode( CONF_TAKEMODE_ONGOING ); }
	BOOL IsTemplate( void ) const { return m_tConfMode.GetTakeMode() == CONF_TAKEMODE_TEMPLATE ? TRUE : FALSE; }
	void SetTemplate( void ){ m_tConfMode.SetTakeMode( CONF_TAKEMODE_TEMPLATE ); }
	u8   GetTakeMode( void ) const{ return m_tConfMode.GetTakeMode();	}
	void SetTakeMode( u8 byTakeMode ){ m_tConfMode.SetTakeMode( byTakeMode ); }
    void SetTakeFromFile(BOOL32 bTakeFromFile) { m_tConfMode.SetTakeFromFile(bTakeFromFile); }  // MCU 内部使用
    BOOL IsTakeFromFile(void) const{ return m_tConfMode.IsTakeFromFile(); }

	//会议保护状态
	u8   GetProtectMode( void ) const { return m_tConfMode.GetLockMode(); }
    void SetProtectMode( u8   byProtectMode ) { m_tConfMode.SetLockMode( byProtectMode ); }
	
	//会议呼叫策略
	u8   GetCallMode( void ) const { return m_tConfMode.GetCallMode(); }
	void SetCallMode( u8   byCallMode ){ m_tConfMode.SetCallMode( byCallMode ); }
	void SetCallInterval(u32 dwCallInterval){ m_tConfMode.SetCallInterval( dwCallInterval ); } 
    u32  GetCallInterval( void ) const { return m_tConfMode.GetCallInterval( ); }
	void SetCallTimes(u32 dwCallTimes){ m_tConfMode.SetCallTimes( dwCallTimes ); } 
    u32  GetCallTimes( void ) const { return m_tConfMode.GetCallTimes( ); }

    //会议点名模式
    u8   GetRollCallMode( void ) const { return m_tConfMode.GetRollCallMode();    }
    void SetRollCallMode( u8 byMode ) { m_tConfMode.SetRollCallMode(byMode);    }
    
    //混音器状态(标识是否在使用混音器，无论是智能混音、定制混音还是语音激励)    

    //直接获取混音器状态参数
    u8     GetMixerMode(void) const { return m_tMixParam.GetMode(); }
    void   SetMixerMode(u8 byMixMode) { m_tMixParam.SetMode(byMixMode); }
    
    TMixParam GetMixerParam(void) const { return m_tMixParam; }
    void   SetMixerParam(TMixParam tAudMixParam){ m_tMixParam = tAudMixParam; }     
    
    //是否在混音(智能或定制)
    BOOL32 IsNoMixing(void) const { return mcuNoMix == GetMixerMode() || mcuVacMix == GetMixerMode(); }
    BOOL32 IsMixing(void) const { return !IsNoMixing(); }
    void   SetNoMixing(void) { SetMixerMode( IsVACing() ? mcuVacMix :mcuNoMix );  }

    //是否智能混音
    BOOL32 IsAutoMixing(void) const 
    {
        return (mcuVacWholeMix == GetMixerMode() || mcuWholeMix == GetMixerMode());
    }
    void   SetAutoMixing(BOOL bAutoMix = TRUE)
    {
        u8 byMixMode = mcuNoMix;
        if ( bAutoMix )
        {
            byMixMode = IsVACing() ? mcuVacWholeMix : mcuWholeMix;
        }
        else
        {
            byMixMode = IsVACing() ? mcuVacMix : mcuNoMix;
        }
        SetMixerMode(byMixMode);
        return;
    }
    
    //是否在定制混音
    BOOL32 IsSpecMixing(void) const
    {
        return (mcuVacPartMix == GetMixerMode() || mcuPartMix == GetMixerMode());
    }
    void   SetSpecMixing(BOOL bMixSpecMt = TRUE)
    {
        u8 byMixMode = mcuNoMix;
        if ( bMixSpecMt )
        {
            byMixMode = IsVACing() ? mcuVacPartMix : mcuPartMix;
        }
        else
        {
            byMixMode = IsVACing() ? mcuVacMix : mcuNoMix;
        }
        SetMixerMode(byMixMode);
    }
    
    //是否在语音激励
    BOOL32 IsVACing(void) const
    {
        return ( mcuVacMix == GetMixerMode() ||
                 mcuVacPartMix == GetMixerMode() || 
                 mcuVacWholeMix == GetMixerMode() );
    }
    void   SetVACing(BOOL bVACMode = TRUE)
    {
        u8 byMixMode = mcuNoMix;
        if ( bVACMode )
        {
            switch(GetMixerMode())
            {
            case mcuNoMix:      byMixMode = mcuVacMix;      break;
            case mcuPartMix:    byMixMode = mcuVacPartMix;  break;
            case mcuWholeMix:   byMixMode = mcuVacWholeMix; break;
            default:            byMixMode = GetMixerMode();   break;
            }
        }
        else
        {
            switch(GetMixerMode())
            {
            case mcuVacMix:         byMixMode = mcuNoMix;       break;
            case mcuVacPartMix:     byMixMode = mcuPartMix;     break;
            case mcuVacWholeMix:    byMixMode = mcuWholeMix;    break;
            default:                byMixMode = GetMixerMode();   break;
            }
        }
        SetMixerMode(byMixMode);
        return;
    }
    
    //画面合成方式
	void   SetVMPMode(u8   byVMPMode){ m_tVMPParam.SetVMPMode(byVMPMode); } 
    u8     GetVMPMode( void ) const { return m_tVMPParam.GetVMPMode(); }
	BOOL   IsBrdstVMP( void ) const { return m_tVMPParam.GetVMPMode() != CONF_VMPMODE_NONE && m_tVMPParam.IsVMPBrdst(); }
	void   SetVmpBrdst( BOOL bBrdst ){ m_tVMPParam.SetVMPBrdst( bBrdst ); }
	u8     GetVmpStyle( void ){ return m_tVMPParam.GetVMPStyle(); }
	void   SetVmpStyle( u8 byVMPStyle ){ m_tVMPParam.SetVMPStyle( byVMPStyle ); }
	void   SetVmpSeebyChairman( BOOL bSeebyChair){ m_tVMPParam.SetVMPSeeByChairman(bSeebyChair); }
	BOOL   IsVmpSeeByChairman( void ) const {return m_tVMPParam.IsVMPSeeByChairman();}
    //vmp tvwall    
	void      SetVmpTwMode(u8 byVmpTwMode){ m_tVmpTwParam.SetVMPMode(byVmpTwMode); }
    u8        GetVmpTwMode(void) const { return m_tVmpTwParam.GetVMPMode(); }
    void      SetVmpTwParam(TVMPParam tVmpTwParam) { m_tVmpTwParam = tVmpTwParam; }
    TVMPParam GetVmpTwParam(void) const { return m_tVmpTwParam; }
    u8        GetVmpTwStyle(void) { return m_tVmpTwParam.GetVMPStyle(); }
	void      SetVmpTwStyle(u8 byVmpTwStyle) { m_tVmpTwParam.SetVMPStyle(byVmpTwStyle); }

	//强制广播(跟原来强制发言人的概念不同，接口名称暂时不修改)
	BOOL IsMustSeeSpeaker(void) const { return m_tConfMode.IsForceRcvSpeaker(); }
	void SetMustSeeSpeaker(BOOL bMustSeeSpeaker) { m_tConfMode.SetForceRcvSpeaker( bMustSeeSpeaker ); }

	//码率适配状态 -- modify bas 2
    BOOL32 IsConfAdapting(void) const { return CONF_BASMODE_NONE != m_tConfMode.GetBasModeValue(); } 
    BOOL32 IsAudAdapting(void) const { return m_tConfMode.GetBasMode(CONF_BASMODE_AUD); }
    BOOL32 IsVidAdapting(void) const { return m_tConfMode.GetBasMode(CONF_BASMODE_VID); }
    BOOL32 IsBrAdapting(void) const { return m_tConfMode.GetBasMode(CONF_BASMODE_BR); }
    BOOL32 IsCasdAudAdapting(void) const { return m_tConfMode.GetBasMode(CONF_BASMODE_CASDAUD); }
    BOOL32 IsCasdVidAdapting(void) const { return m_tConfMode.GetBasMode(CONF_BASMODE_CASDVID); }
    void SetAdaptMode(u8 byBasMode, BOOL32 bAdapt)
    { 
        m_tConfMode.SetBasMode(byBasMode, bAdapt);
    }
    // 高清适配状态
	BOOL32 IsConfHDAdapting(void) const { return CONF_HDBASMODE_NONE != m_tConfMode.GetHDBasModeValue(); }
    BOOL32 IsHdVidAdapting(void) const { return m_tConfMode.GetHDBasMode(CONF_HDBASMODE_VID); }
    BOOL32 IsHDDoubleVidAdapting(void) const { return m_tConfMode.GetHDBasMode( CONF_HDBASMODE_DOUBLEVID ) ;}
    BOOL32 IsHdCasdVidAdapting(void) const { return m_tConfMode.GetHDBasMode(CONF_HDBASMODE_CASDVID); }
    void SetHDAdaptMode(u8 byHDBasMode, BOOL32 bAdapt)
    { 
        m_tConfMode.SetHDBasMode(byHDBasMode, bAdapt);
    }

	//会议主席状态
	BOOL IsNoChairMode( void ) const { return m_tConfMode.IsNoChairMode(); }
    void SetNoChairMode( BOOL bNoChairMode ) { m_tConfMode.SetNoChairMode( bNoChairMode ); }

	//轮询方式
	void   SetPollMode(u8   byPollMode){ m_tConfMode.SetPollMode( byPollMode ); } 
    u8     GetPollMode(){ return m_tConfMode.GetPollMode(); }
	
	//轮询参数
    void   SetPollInfo(const TPollInfo &tPollInfo){ m_tPollInfo = tPollInfo;} 
    TPollInfo  *GetPollInfo( void ) { return &m_tPollInfo; }
	void   SetPollMedia(u8   byMediaMode){ m_tPollInfo.SetMediaMode( byMediaMode ); } 
    u8     GetPollMedia( void ) const{ return m_tPollInfo.GetMediaMode(); }
	void   SetPollState(u8   byPollState){ m_tPollInfo.SetPollState( byPollState );} 
    u8     GetPollState( void ) const { return m_tPollInfo.GetPollState(); }
    void   SetMtPollParam(TMtPollParam tMtPollParam){ m_tPollInfo.SetMtPollParam( tMtPollParam ); } 
    TMtPollParam  GetMtPollParam() const{ return m_tPollInfo.GetMtPollParam(); }

    //电视墙轮询参数
    void   SetTvWallPollInfo(const TTvWallPollInfo &tPollInfo){ m_tTvWallPollInfo = tPollInfo;} 
    TTvWallPollInfo  *GetTvWallPollInfo( void ) { return &m_tTvWallPollInfo; }    
    void   SetTvWallPollState(u8   byPollState){ m_tTvWallPollInfo.SetPollState( byPollState );} 
    u8     GetTvWallPollState( void ) const { return m_tTvWallPollInfo.GetPollState(); }
    void   SetTvWallMtPollParam(TMtPollParam tMtPollParam){ m_tTvWallPollInfo.SetMtPollParam( tMtPollParam ); } 
    TMtPollParam  GetTvWallMtPollParam(){ return m_tTvWallPollInfo.GetMtPollParam(); }

	//hdu轮询参数
    void   SetHduPollInfo(const THduPollInfo &tPollInfo){ m_tHduPollInfo = tPollInfo; }
    THduPollInfo  *GetHduPollInfo( void ) { return &m_tHduPollInfo; }    
    void   SetHduPollState(u8   byPollState){ m_tHduPollInfo.SetPollState( byPollState ); } 
    u8     GethduPollState( void ) const { return m_tHduPollInfo.GetPollState(); }
    void   SetHduMtPollParam(TMtPollParam tMtPollParam){ m_tHduPollInfo.SetMtPollParam( tMtPollParam ); } 
    TMtPollParam  GetHduMtPollParam(){ return m_tHduPollInfo.GetMtPollParam(); }

	//会议录像状态	
	BOOL IsNoRecording( void ) const{ return m_tConfMode.GetRecordMode() == CONF_RECMODE_NONE ? TRUE : FALSE; }
	void SetNoRecording( void ){ m_tConfMode.SetRecordMode( CONF_RECMODE_NONE ); }
	BOOL IsRecording( void ) const{ return m_tConfMode.GetRecordMode() == CONF_RECMODE_REC ? TRUE : FALSE; }
	void SetRecording( void ){ m_tConfMode.SetRecordMode( CONF_RECMODE_REC ); }
	BOOL IsRecPause( void ) const{ return m_tConfMode.GetRecordMode() == CONF_RECMODE_PAUSE ? TRUE : FALSE; }
	void SetRecPause( void ){ m_tConfMode.SetRecordMode( CONF_RECMODE_PAUSE ); }

	//会议放像状态
	BOOL IsNoPlaying( void ) const{ return m_tConfMode.GetPlayMode() == CONF_PLAYMODE_NONE ? TRUE : FALSE; }
	void SetNoPlaying( void ){ m_tConfMode.SetPlayMode( CONF_PLAYMODE_NONE ); }
	BOOL IsPlaying( void ) const { return m_tConfMode.GetPlayMode() == CONF_PLAYMODE_PLAY ? TRUE : FALSE; }
	void SetPlaying( void ){ m_tConfMode.SetPlayMode( CONF_PLAYMODE_PLAY ); }
	BOOL IsPlayPause( void )const { return m_tConfMode.GetPlayMode() == CONF_PLAYMODE_PAUSE ? TRUE : FALSE; }
	void SetPlayPause( void ){ m_tConfMode.SetPlayMode( CONF_PLAYMODE_PAUSE ); }
	BOOL IsPlayFF( void )const { return m_tConfMode.GetPlayMode() == CONF_PLAYMODE_FF ? TRUE : FALSE; }
	void SetPlayFF( void ) { m_tConfMode.SetPlayMode( CONF_PLAYMODE_FF ); }
	BOOL IsPlayFB( void )const { return m_tConfMode.GetPlayMode() == CONF_PLAYMODE_FB ? TRUE : FALSE; }
	void SetPlayFB( void ){ m_tConfMode.SetPlayMode( CONF_PLAYMODE_FB ); }
	// zgc, 2007-02-27, 会议放像关键帧延迟问题
	BOOL IsPlayReady( void ) const{ return m_tConfMode.GetPlayMode() == CONF_PLAYMODE_PLAYREADY ? TRUE : FALSE; }
	void SetPlayReady( void ){ m_tConfMode.SetPlayMode( CONF_PLAYMODE_PLAYREADY ); }
	// zgc, 2007-02-27, end

	//包重传状态
	void SetPrsing( BOOL bPrs ){ m_byPrs = bPrs; }
	BOOL IsPrsing( void ){ return m_byPrs; }

	//注册GK情况
	void SetRegToGK( BOOL bRegToGK ){ m_tConfMode.SetRegToGK( bRegToGK ); }
	BOOL IsRegToGK( void ) const{ return m_tConfMode.IsRegToGK(); }

    // xsl [11/16/2006] GK计费情况
    void SetGkCharge( BOOL bCharge ) { m_tConfMode.SetGkCharge( bCharge ); }
    BOOL IsGkCharge( void ) const { return m_tConfMode.IsGkCharge(); }

	void Print( void ) const
	{
		OspPrintf( TRUE, FALSE, "\nConfStatus:\n" );
        if(m_tChairman.IsNull())  
            OspPrintf( TRUE, FALSE, "Chairman: Null\n" );
        else 
            OspPrintf( TRUE, FALSE, "Chairman: Mcu%dMt%d\n", m_tChairman.GetMcuId(), m_tChairman.GetMtId() );
        if(m_tSpeaker.IsNull())
            OspPrintf( TRUE, FALSE, "Speaker: Null\n" );
        else
		    if (m_tSpeaker.GetType() == TYPE_MT)
                OspPrintf( TRUE, FALSE, "Speaker: Mcu%dMt%d\n", m_tSpeaker.GetMcuId(), m_tSpeaker.GetMtId() );
            else
                OspPrintf( TRUE, FALSE, "Speaker: Mcu%dEqp%d\n", m_tSpeaker.GetMcuId(), m_tSpeaker.GetEqpId() );
        OspPrintf( TRUE, FALSE, "VmpMode: %d\n", m_tVMPParam.GetVMPMode() );
        OspPrintf( TRUE, FALSE, "TWVmpMode: %d\n", m_tVmpTwParam.GetVMPMode() );
        OspPrintf( TRUE, FALSE, "MixerMode: %d\n", GetMixerMode() );
	}
}
/*
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
*/
PACKED
;

// zw [06/27/2008] 将m_byAudioMediaType封装为TAudioStreamCap，并且作为TAudAACCap父类
//定义音频媒体格式的属性(len:1)
struct TAudioStreamCap
{
protected:
	u8 m_byAudioMediaType;

public:
	TAudioStreamCap() { Clear(); }

	void Clear(void)
    {
        m_byAudioMediaType = MEDIA_TYPE_NULL;
    }

    void SetMediaType(u8 byAudioMediaType) { m_byAudioMediaType = byAudioMediaType; }	
    u8	 GetMediaType() const { return m_byAudioMediaType; }
}
PACKED
;

struct TAudAACCap : public TAudioStreamCap
{
protected:
	u8  m_bySampleFreq;
    u8  m_byChnlType ;
    u16 m_wBitrate;
    u8  m_byMaxFrameNum;        

public:
    TAudAACCap() { Clear(); }

	void Clear(void)
    {
        m_bySampleFreq  = 0;
        m_byChnlType    = 0;
        m_wBitrate      = 0;
        m_byMaxFrameNum = 0;
    }

    void	SetSampleFreq(u8 bySampleFreq)  { m_bySampleFreq = bySampleFreq; }	
    u8		GetSampleFreq() const { return m_bySampleFreq; } 
    
    void	SetChnlType(u8 byChnlType)  { m_byChnlType = byChnlType; }	
    u8		GetChnlType() const { return m_byChnlType; } 

    void	SetBitrate(u16 wBitrate)  { m_wBitrate = htons(wBitrate); }	
    u16		GetBitrate() const { return ntohs(m_wBitrate); } 

    void	SetMaxFrameNum(u8 byMaxFrameNum)  { m_byMaxFrameNum = byMaxFrameNum; }	
    u8		GetMaxFrameNum() const { return m_byMaxFrameNum; } 
}
PACKED
;

//定义视频媒体格式的属性(len:5)
struct TVideoStreamCap
{
protected:
    u16		m_wMaxBitRate;   
    u8		m_byMediaType;   
    u8      m_byResolution;	//分辨率 VIDEO_FORMAT_AUTO, ...
	u8      m_byFrameRate;  //帧率 MPI，对于 H.264 则是 FPS
    
public:
    TVideoStreamCap() { Clear(); }
    
    void    Clear(void)
    {
        m_wMaxBitRate = 0;
        m_byFrameRate = 0;
        m_byMediaType = MEDIA_TYPE_NULL;
        m_byResolution = VIDEO_FORMAT_CIF;
    }   
    
    void	SetMediaType(u8 byMediaType)  {  m_byMediaType = byMediaType; }	
    u8		GetMediaType() const { return m_byMediaType; }
    
    void    SetResolution(u8 byRes) {   m_byResolution = byRes;    }
    u8      GetResolution(void) const   {   return m_byResolution;    }

    void    SetFrameRate(u8 byFrameRate)
    {
        if ( MEDIA_TYPE_H264 == m_byMediaType )
        {
            OspPrintf( TRUE, FALSE, "Function has been preciated, try SetUserDefFrameRate\n" );
            return;
        }
        m_byFrameRate = byFrameRate;
    }
    u8      GetFrameRate(void) const
    {
        if ( MEDIA_TYPE_H264 == m_byMediaType )
        {
            OspPrintf( TRUE, FALSE, "Function has been preciated, try GetUserDefFrameRate\n" );
            return 0;
        }
        return m_byFrameRate;
    }

    // guzh [12/1/2007] 自定义帧率的保存/获取
    void    SetUserDefFrameRate(u8 byActFrameRate) { m_byFrameRate = VIDEO_FPS_USRDEFINED+byActFrameRate; }
    BOOL32  IsFrameRateUserDefined() const {return (m_byFrameRate>VIDEO_FPS_USRDEFINED); }
    u8      GetUserDefFrameRate(void) const { return IsFrameRateUserDefined() ? m_byFrameRate-VIDEO_FPS_USRDEFINED : m_byFrameRate; }
    
    void	SetMaxBitRate(u16 wMaxRate) {m_wMaxBitRate = htons(wMaxRate); }
    u16		GetMaxBitRate() const { return ntohs(m_wMaxBitRate); }


    BOOL32 IsResLower(u8 bySrcRes, u8 byDstRes)
    {
        if (!IsResMatched(bySrcRes, byDstRes))
        {
            return FALSE;
        }
        u16 wSrcWidth = 0;
        u16 wDstWidth = 0;
        u16 wSrcHeight = 0;
        u16 wDstHeight = 0;

        GetWHByRes(bySrcRes, wSrcWidth, wSrcHeight);
        GetWHByRes(byDstRes, wDstWidth, wDstHeight);
        
        if (wSrcWidth < wDstWidth &&
            wSrcHeight < wDstHeight)
        {
            return TRUE;
        }
        return FALSE;
    }

private:
    void GetWHByRes(u8 byRes, u16 &wWidth, u16 &wHeight)
    {
        wWidth = 0;
        wHeight = 0;
    
        switch(byRes)
        {
        case VIDEO_FORMAT_SQCIF_112x96:
            wWidth = 112;
            wHeight = 96;
            break;
        
        case VIDEO_FORMAT_SQCIF_96x80:
            wWidth = 96;
            wHeight = 80;
            break;
        
        case VIDEO_FORMAT_SQCIF:
            wWidth = 128;
            wHeight = 96;
            break;
        
        case VIDEO_FORMAT_QCIF:
            wWidth = 176;
            wHeight = 144;
            break;
        
        case VIDEO_FORMAT_CIF:
            wWidth = 352;
            wHeight = 288;
            break;
        
        case VIDEO_FORMAT_2CIF:
            wWidth = 352;
            wHeight = 576;
            break;
        
        case VIDEO_FORMAT_4CIF:
        
            //基于尽可能播放考虑，这里取大值
            wWidth = 704;
            wHeight = 576;
            break;
        
        case VIDEO_FORMAT_16CIF:
            wWidth = 1048;
            wHeight = 1152;
            break;
        
        case VIDEO_FORMAT_AUTO:
            //不解析
            break;
        
        case VIDEO_FORMAT_SIF:
            wWidth = 352;
            wHeight = 240;
            break;
        
        case VIDEO_FORMAT_2SIF:
            wWidth = 352;
            wHeight = 480;
            break;
        
        case VIDEO_FORMAT_4SIF:
            wWidth = 704;
            wHeight = 480;
            break;
        
        case VIDEO_FORMAT_VGA:
            wWidth = 640;
            wHeight = 480;
            break;
        
        case VIDEO_FORMAT_SVGA:
            wWidth = 800;
            wHeight = 600;
            break;
        
        case VIDEO_FORMAT_XGA:
            wWidth = 1024;
            wHeight = 768;
            break;

        case VIDEO_FORMAT_W4CIF:
            wWidth = 1024;
            wHeight = 576;
            break;

        case VIDEO_FORMAT_HD720:
            wWidth = 1280;
            wHeight = 720;
            break;

        case VIDEO_FORMAT_SXGA:
            wWidth = 1280;
            wHeight = 1024;
            break;

        case VIDEO_FORMAT_UXGA:
            wWidth = 1600;
            wHeight = 1200;
            break;

        case VIDEO_FORMAT_HD1080:
            wWidth = 1920;
            wHeight = 1088;
            break;
        default:
            break;
        }
        if ( 0 == wHeight || 0 == wWidth )
        {
            OspPrintf( TRUE, FALSE, "[TVideoStreamCap::GetWHByRes] unexpected res.%d, ignore it\n", byRes );
        }
        return;
    }

    BOOL32 IsResMatched(u8 bySrcRes, u8 byDstRes)
    {
        BOOL32 bMatched = FALSE;
        if (IsResPresentation(bySrcRes) && IsResPresentation(byDstRes))
        {
            bMatched = TRUE;
        }
        else if (IsResLive(bySrcRes) && IsResLive(byDstRes))
        {
            bMatched = TRUE;
        }
        return bMatched;
    }
    
    BOOL32 IsResPresentation(u8 byRes)
    {
        BOOL32 bPresentation = FALSE;
        
        switch(byRes)
        {
        case VIDEO_FORMAT_VGA:
        case VIDEO_FORMAT_SVGA:
        case VIDEO_FORMAT_XGA:
        case VIDEO_FORMAT_SXGA:
        case VIDEO_FORMAT_UXGA:
            bPresentation = TRUE;
            break;
        default:
            break;
        }
        return bPresentation;
    }
    
    BOOL32 IsResLive(u8 byRes)
    {
        BOOL32 bLive = FALSE;
        
        switch(byRes)
        {
        case VIDEO_FORMAT_CIF:
        case VIDEO_FORMAT_2CIF:
        case VIDEO_FORMAT_4CIF:
        case VIDEO_FORMAT_16CIF:
            
        case VIDEO_FORMAT_SIF:
        case VIDEO_FORMAT_2SIF:
        case VIDEO_FORMAT_4SIF:
            
        case VIDEO_FORMAT_W4CIF:
        case VIDEO_FORMAT_HD720:
        case VIDEO_FORMAT_HD1080:
            bLive = TRUE;
            break;
        //不解析以下
        case VIDEO_FORMAT_AUTO:
        case VIDEO_FORMAT_SQCIF_112x96:
        case VIDEO_FORMAT_SQCIF_96x80:
            break;
        default:
            break;
        }
        return bLive;
    }
}
/*
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
*/
PACKED
;

//双流能力类型(len:6)
struct TDStreamCap : public TVideoStreamCap
{
protected:
    u8  m_byIsH239Type;    

public:
    TDStreamCap() { Reset(); }

    void SetSupportH239(BOOL32 bSupport) { m_byIsH239Type = (bSupport ? 1:0); }
    BOOL32   IsSupportH239(void) const { return (0 != m_byIsH239Type); }

    void Reset(void)
    {
        Clear();
        m_byIsH239Type = 0;
    }

    BOOL32 IsResolutionLower(u8 bySrcRes, u8 byDstRes)
    {
        return IsResLower(bySrcRes, byDstRes);
    }
    BOOL32 operator < (const TDStreamCap &tDsCap)
    {
        if (tDsCap.GetMediaType() != GetMediaType())
        {
            //基于适配：不匹配认为小于
            return TRUE;
        }
        
        u8 bySrcFrmRate = MEDIA_TYPE_H264 == GetMediaType() ? GetUserDefFrameRate() : GetFrameRate();
        u8 byDstFrmRate = MEDIA_TYPE_H264 == tDsCap.GetMediaType() ? tDsCap.GetUserDefFrameRate() : tDsCap.GetFrameRate(); 
        
        if (IsResLower(GetResolution(), tDsCap.GetResolution()) ||
            GetMaxBitRate() < tDsCap.GetMaxBitRate() ||
            bySrcFrmRate < byDstFrmRate)
        {
            return TRUE;
        }
        return FALSE;
    }

    BOOL32 operator != (const TDStreamCap &tDsCap)
    {
        if (tDsCap.GetMediaType() != GetMediaType())
        {
            return TRUE;
        }
        
        u8 bySrcFrmRate = MEDIA_TYPE_H264 == GetMediaType() ? GetUserDefFrameRate() : GetFrameRate();
        u8 byDstFrmRate = MEDIA_TYPE_H264 == tDsCap.GetMediaType() ? tDsCap.GetUserDefFrameRate() : tDsCap.GetFrameRate(); 
        
        if (IsResLower(GetResolution(), tDsCap.GetResolution()) ||
            GetMaxBitRate() != tDsCap.GetMaxBitRate() ||
            bySrcFrmRate != byDstFrmRate)
        {
            return TRUE;
        }
        return FALSE;
    }
    BOOL32 IsNull()
    {
        return MEDIA_TYPE_NULL == GetMediaType();
    }
};

//同时能力集结构(len:6)
struct TSimCapSet
{
protected:
	TVideoStreamCap  m_tVideoCap;
    TAudioStreamCap  m_tAudioCap;
//	u8  m_byAudioMediaType;  

public:
    TSimCapSet( void )	{ Clear(); }

	void SetVideoMediaType( u8 byMediaType ) { m_tVideoCap.SetMediaType(byMediaType); }
    u8   GetVideoMediaType( void ) const { return m_tVideoCap.GetMediaType(); }

	void SetVideoResolution( u8 byRes ) { m_tVideoCap.SetResolution(byRes); }
    u8   GetVideoResolution( void ) const { return m_tVideoCap.GetResolution(); }

	void SetVideoMaxBitRate( u16 wMaxRate ) { m_tVideoCap.SetMaxBitRate(wMaxRate); }
	u16  GetVideoMaxBitRate( void ) const { return m_tVideoCap.GetMaxBitRate(); }

    void SetVideoFrameRate(u8 byFrameRate) { m_tVideoCap.SetFrameRate(byFrameRate); }
    u8   GetVideoFrameRate(void) const { return m_tVideoCap.GetFrameRate(); }

    // guzh [12/1/2007] 自定义帧率的保存/获取
    void SetUserDefFrameRate(u8 byActFrameRate) { m_tVideoCap.SetUserDefFrameRate(byActFrameRate); }
    BOOL32 IsFrameRateUserDefined() const {return m_tVideoCap.IsFrameRateUserDefined(); }
    u8   GetUserDefFrameRate(void) const { return m_tVideoCap.GetUserDefFrameRate(); }
    
    void SetAudioMediaType( u8 byAudioMediaType ) { m_tAudioCap.SetMediaType(byAudioMediaType);}
    u8   GetAudioMediaType( void ) const { return m_tAudioCap.GetMediaType(); }

    void SetVideoCap( TVideoStreamCap &tVidCap ){ memcpy(&m_tVideoCap, &tVidCap, sizeof(TVideoStreamCap)); }
    TVideoStreamCap   GetVideoCap( void ) const { return m_tVideoCap; }

	BOOL32   operator ==( const TSimCapSet & tSimCapSet ) const  //判断是否相等(只判断语音图像)
	{
		if( GetVideoMediaType() == tSimCapSet.GetVideoMediaType() && 
			GetAudioMediaType() == tSimCapSet.GetAudioMediaType() &&
            GetVideoMediaType() != MEDIA_TYPE_NULL && 
            GetAudioMediaType() != MEDIA_TYPE_NULL)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
    
    BOOL32 operator < (const TSimCapSet &tSimCapSet) //判断小于
    {
        if (tSimCapSet.IsNull())
        {
            return FALSE;
        }
        if (GetVideoMediaType() != tSimCapSet.GetVideoMediaType() /*&& 
			GetAudioMediaType() != tSimCapSet.GetAudioMediaType()*/)
        {
            //基于适配：不匹配认为小于
            return TRUE;
        }
        
        u8 bySrcFrmRate = MEDIA_TYPE_H264 == GetVideoMediaType() ? GetUserDefFrameRate() : GetVideoFrameRate();
        u8 byDstFrmRate = MEDIA_TYPE_H264 == tSimCapSet.GetVideoMediaType() ? tSimCapSet.GetUserDefFrameRate() : tSimCapSet.GetVideoFrameRate(); 
        if (m_tVideoCap.IsResLower(GetVideoResolution(), tSimCapSet.GetVideoResolution()) ||
            GetVideoMaxBitRate() < tSimCapSet.GetVideoMaxBitRate())
        {
            return TRUE;
        }

        if((abs(bySrcFrmRate-byDstFrmRate) == 5) &&
            (bySrcFrmRate == 30 || byDstFrmRate == 30))
        {
            return FALSE;
        }

        if (bySrcFrmRate < byDstFrmRate)
        {
            return TRUE;
        }
        
        return FALSE;
    }
    
    BOOL32 operator != (const TSimCapSet &tSim)
    {
        if(tSim.IsNull())
        {
            return FALSE;
        }
        if(GetVideoMediaType() != tSim.GetVideoMediaType())
        {
            return TRUE;
        }
        if(m_tVideoCap.IsResLower(GetVideoResolution(), tSim.GetVideoResolution()) ||
           GetVideoMaxBitRate() < tSim.GetVideoMaxBitRate())
        {
            return TRUE;
        }
        u8 bySrcFrmRate = MEDIA_TYPE_H264 == GetVideoMediaType() ? GetUserDefFrameRate() : GetVideoFrameRate();
        u8 byDstFrmRate = MEDIA_TYPE_H264 == tSim.GetVideoMediaType() ? tSim.GetUserDefFrameRate() : tSim.GetVideoFrameRate(); 
        
        if((abs(bySrcFrmRate-byDstFrmRate) == 5) &&
           (bySrcFrmRate == 30 || byDstFrmRate == 30))
        {
            return FALSE;
        }
        if(bySrcFrmRate != byDstFrmRate)
        {
            return TRUE;
        }
        return FALSE;
    }
    
	BOOL32   IsNull( void ) const
	{
		if(	GetVideoMediaType() == MEDIA_TYPE_NULL && GetAudioMediaType() == MEDIA_TYPE_NULL )
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}

	void  Clear( void )
	{
        m_tVideoCap.Clear();
        SetAudioMediaType(MEDIA_TYPE_NULL);
	}
}
/*
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
*/
PACKED
;

//能力集结构(len:23)
struct TCapSupport
{
protected:		
	u8          m_bySupportMMcu;        //是否支持合并级联
    u8          m_bySupportH224;	    //是否支持H224
    u8          m_bySupportT120;	    //是否支持T120  
    u8          m_byEncryptMode;        //加密模式CONF_ENCRYPTMODE_NONE, CONF_ENCRYPTMODE_DES, CONF_ENCRYPTMODE_AES
    u8          m_byDStreamType;        //VIDEO_DSTREAM_H263PLUS,...

    //双流能力
    TDStreamCap   m_tDStreamCap; 

	//同时能力集
	TSimCapSet  m_tMainSimCapSet;    //主的同时能力集
	TSimCapSet  m_tSecondSimCapSet;  //辅的同时能力集

public:
	//构造函数
    TCapSupport( void ) { Clear(); }
           
	void    SetSupportMMcu( BOOL32 bMMcu) { m_bySupportMMcu = (bMMcu ? 1:0); }
	BOOL32  IsSupportMMcu() const { return (0 != m_bySupportMMcu); }

    void    SetEncryptMode(u8 byMode) { m_byEncryptMode = byMode; }
    u8      GetEncryptMode(void) const { return m_byEncryptMode; }
    
    void    SetSupportH224(BOOL32  bSupportH224){ m_bySupportH224 = (bSupportH224 ? 1:0); } 
    BOOL32  IsSupportH224( void ) const { return (0 != m_bySupportH224); }  
    
    void    SetSupportT120(BOOL32   bSupportT120) { m_bySupportT120 = (bSupportT120 ? 1:0);} 
    BOOL32  IsSupportT120(void) const { return (0 != m_bySupportT120); }   

	void    SetMainVideoType( u8 byMediaType ) { m_tMainSimCapSet.SetVideoMediaType(byMediaType);    }
    u8      GetMainVideoType(void) const { return m_tMainSimCapSet.GetVideoMediaType();    }
    u8      GetMainAudioType(void) const { return m_tMainSimCapSet.GetAudioMediaType();    }
    u8      GetSecVideoType(void) const { return m_tSecondSimCapSet.GetVideoMediaType();   }
	void    SetSecVideoType(u8 byType) { m_tSecondSimCapSet.SetVideoMediaType(byType); }
    u8      GetSecAudioType(void) const { return m_tSecondSimCapSet.GetAudioMediaType();   }

    void    SetMainVideoResolution(u8 byRes) { m_tMainSimCapSet.SetVideoResolution(byRes);    }
    u8      GetMainVideoResolution(void) const { return m_tMainSimCapSet.GetVideoResolution();    }

    void    SetSecVideoResolution(u8 byRes) { m_tSecondSimCapSet.SetVideoResolution(byRes);    }
    u8      GetSecVideoResolution(void) const { return m_tSecondSimCapSet.GetVideoResolution();    }

	//第二路视频（双流）能力集设置
	void    SetDStreamResolution(u8 byRes) { m_tDStreamCap.SetResolution(byRes); }
	u8      GetDStreamResolution(void) const { return m_tDStreamCap.GetResolution(); }

    //帧率
    void    SetMainVidFrmRate(u8 byMPI) { m_tMainSimCapSet.SetVideoFrameRate(byMPI); }
    u8      GetMainVidFrmRate(void) const { return m_tMainSimCapSet.GetVideoFrameRate();    }

    void    SetSecVidFrmRate(u8 byMPI) { m_tSecondSimCapSet.SetVideoFrameRate(byMPI);    }
    u8      GetSecVidFrmRate(void) const { return m_tSecondSimCapSet.GetVideoFrameRate();    }

    void    SetDStreamFrmRate(u8 byMPI) { m_tDStreamCap.SetFrameRate(byMPI);    }
    u8      GetDStreamFrmRate(void) const { return m_tDStreamCap.GetFrameRate();    }

    //H264自定义帧率
    void    SetMainVidUsrDefFPS(u8 byFPS) { m_tMainSimCapSet.SetUserDefFrameRate(byFPS);    }
    u8      GetMainVidUsrDefFPS(void) const { return m_tMainSimCapSet.GetUserDefFrameRate();    }
    BOOL32  IsMainVidUsrDefFPS(void) const { return m_tMainSimCapSet.IsFrameRateUserDefined();    }

    void    SetSecVidUsrDefFPS(u8 byFPS) { m_tSecondSimCapSet.SetUserDefFrameRate(byFPS);    }
    u8      GetSecVidUsrDefFPS(void) const { return m_tSecondSimCapSet.GetUserDefFrameRate();    }
    BOOL32  IsSecVidUsrDefFPS(void) const { return m_tSecondSimCapSet.IsFrameRateUserDefined();    }

    void    SetDStreamUsrDefFPS(u8 byFPS) { m_tDStreamCap.SetUserDefFrameRate(byFPS);    }
    u8      GetDStreamUsrDefFPS(void) const { return m_tDStreamCap.GetUserDefFrameRate();    }
    BOOL32  IsDStreamUsrDefFPS(void) const { return m_tDStreamCap.IsFrameRateUserDefined();    }
	
    //暂时不用
	void    SetDStreamMaxBitRate(u16 wMaxRate) { m_tDStreamCap.SetMaxBitRate(wMaxRate); }
	u16     GetDStreamMaxBitRate(void) const { return m_tDStreamCap.GetMaxBitRate(); }

    void    SetDStreamFrameRate(u8 byFrameRate) { m_tDStreamCap.SetFrameRate(byFrameRate); }
    u8      GetDStreamFrameRate(void) const { return m_tDStreamCap.GetFrameRate(); }

    void    SetDStreamType( u8 byDStreamType ); //仅会控使用    
    u8      GetDStreamType( void ) const { return m_byDStreamType; } //仅会控使用

	void    SetDStreamSupportH239( BOOL32 bSupport ) { m_tDStreamCap.SetSupportH239(bSupport); } //仅MCU内部使用
    BOOL32  IsDStreamSupportH239( void ) const { return m_tDStreamCap.IsSupportH239(); } //第二路视频是否支持H239

    void    SetDStreamMediaType( u8 byMediaType ) { m_tDStreamCap.SetMediaType(byMediaType); } //仅MCU内部使用
    u8      GetDStreamMediaType( void ) const { return m_tDStreamCap.GetMediaType(); }	

    TDStreamCap GetDStreamCapSet( void ) const { return m_tDStreamCap; }
	void    SetDStreamCapSet(TDStreamCap &tStreamCap) { m_tDStreamCap = tStreamCap;	}

	//第一路音视频能力集设置
    void    SetMainSimCapSet( TSimCapSet &tSimCapSet ) { memcpy(&m_tMainSimCapSet, &tSimCapSet, sizeof(TSimCapSet)); }    
    TSimCapSet  GetMainSimCapSet( void ) const { return m_tMainSimCapSet; }

    void    SetSecondSimCapSet( TSimCapSet &tSimCapSet ) { memcpy(&m_tSecondSimCapSet, &tSimCapSet, sizeof(TSimCapSet)); }
    TSimCapSet  GetSecondSimCapSet( void ) const { return m_tSecondSimCapSet; }
   
	BOOL32  IsSupportMediaType( u8 byMediaType ) const; //第一路音视频是否支持某种媒体类型	

	void Clear( void )
	{
        m_bySupportMMcu = 0;
        m_bySupportH224 = 0;
        m_bySupportT120 = 0;
        m_byEncryptMode = CONF_ENCRYPTMODE_NONE;
        m_byDStreamType = VIDEO_DSTREAM_MAIN;
        m_tMainSimCapSet.Clear(); 
        m_tSecondSimCapSet.Clear(); 
        m_tDStreamCap.Reset();
	}
	
	void Print( void ) const
	{
        OspPrintf( TRUE, FALSE, "Main simul support:\n");
        OspPrintf( TRUE, FALSE, "\tVideo\n\t\tType\t:%d\n\t\tRes\t:%d\n\t\tFps\t:%d\n\t\tMaxRate\t:%d\n", 
                                 m_tMainSimCapSet.GetVideoMediaType(),
                                 m_tMainSimCapSet.GetVideoResolution(),
                                 MEDIA_TYPE_H264 != m_tMainSimCapSet.GetVideoMediaType() ? m_tMainSimCapSet.GetVideoFrameRate() : m_tMainSimCapSet.GetUserDefFrameRate(),
                                 m_tMainSimCapSet.GetVideoMaxBitRate() );
        OspPrintf( TRUE, FALSE, "\tAudio\n\t\tType\t:%d\n", m_tMainSimCapSet.GetAudioMediaType() );
        OspPrintf( TRUE, FALSE, "Second simul support:\n");
        OspPrintf( TRUE, FALSE, "\tVideo\n\t\tType\t:%d\n\t\tRes\t:%d\n\t\tFps\t:%d\n\t\tMaxRate\t:%d\n",
                                 m_tSecondSimCapSet.GetVideoMediaType(),
                                 m_tSecondSimCapSet.GetVideoResolution(),
                                 MEDIA_TYPE_H264 != m_tSecondSimCapSet.GetVideoMediaType() ? m_tSecondSimCapSet.GetVideoFrameRate() : m_tSecondSimCapSet.GetUserDefFrameRate(),
                                 m_tSecondSimCapSet.GetVideoMaxBitRate() );
        OspPrintf( TRUE, FALSE, "\tAudio\n\t\tType\t:%d\n", m_tSecondSimCapSet.GetAudioMediaType() );
        OspPrintf( TRUE, FALSE, "Double stream support:\n" );
        OspPrintf( TRUE, FALSE, "\tVideo\n\t\tType\t:%d\n\t\tRes\t:%d\n\t\tFps\t:%d\n\t\tH.239\t:%d\n",
                                 m_tDStreamCap.GetMediaType(),
                                 m_tDStreamCap.GetResolution(),
                                 MEDIA_TYPE_H264 != m_tDStreamCap.GetMediaType() ? m_tDStreamCap.GetFrameRate() : m_tDStreamCap.GetUserDefFrameRate(),
                                 m_tDStreamCap.IsSupportH239() );
        OspPrintf( TRUE, FALSE, "Other feather support:\n" );
        OspPrintf( TRUE, FALSE, "\tMMcu\t\t:%d\n\tT120\t\t:%d\n\tH224\t\t:%d\n\tEncrypt\t\t:%d\n", 
                                 m_bySupportMMcu, m_bySupportT120, m_bySupportH224, m_byEncryptMode );        
        OspPrintf( TRUE, FALSE, "\n" );
	}
}
/*
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
*/
PACKED
;

//能力集扩展结构
struct TCapSupportEx
{
protected:
	u8 m_byVideoFECType;
	u8 m_byAudioFECType;
	u8 m_byDVideoFECType;
    TVideoStreamCap tSecDSCap;      //第二双流能力的H239属性向第一双流能力对齐
	
public:
    TCapSupportEx(): m_byVideoFECType(FECTYPE_NONE),
                     m_byAudioFECType(FECTYPE_NONE),
                     m_byDVideoFECType(FECTYPE_NONE)
	{
        tSecDSCap.Clear();
	}

public: //会控使用；终端适配在面向终端的时候模糊程度等同于会控，也用该接口.
	void	SetFECType(u8 byFECType)
	{
		m_byVideoFECType = byFECType; 
		m_byAudioFECType = FECTYPE_NONE;
		m_byDVideoFECType = byFECType;
	}

public: //MCU使用
	BOOL32	IsNoSupportFEC(void) const 
	        { return ( (FECTYPE_NONE == m_byVideoFECType) &&
                       (FECTYPE_NONE == m_byAudioFECType) &&
                       (FECTYPE_NONE == m_byDVideoFECType) ); }
	BOOL32	IsVideoSupportFEC(void) const { return ( FECTYPE_NONE != m_byVideoFECType ); }
	BOOL32	IsAudioSupportFEC(void) const { return ( FECTYPE_NONE != m_byAudioFECType ); }
	BOOL32	IsDVideoSupportFEC(void) const { return ( FECTYPE_NONE != m_byDVideoFECType ); }
	u8		GetVideoFECType(void) const { return m_byVideoFECType; }
	void	SetVideoFECType(u8 byFECType) { m_byVideoFECType = byFECType; }
	u8		GetAudioFECType(void) const { return m_byAudioFECType; }
	void	SetAudioFECType(u8 byFECType) { m_byAudioFECType = byFECType; }
	u8		GetDVideoFECType(void) const { return m_byDVideoFECType; }
	void	SetDVideoFECType(u8 byFECType) { m_byDVideoFECType = byFECType; }

public:
    void    SetSecDSType(u8 byType){ tSecDSCap.SetMediaType(byType); }
    u8      GetSecDSType(void) const { return tSecDSCap.GetMediaType(); };
    void    SetSecDSRes(u8 byRes) { tSecDSCap.SetResolution(byRes); }
    u8      GetSecDSRes(void) const { return tSecDSCap.GetResolution(); }
    void    SetSecDSBitRate(u16 wBitRate) { tSecDSCap.SetMaxBitRate(wBitRate);  }
    u16     GetSecDSBitRate(void) const { return tSecDSCap.GetMaxBitRate(); }

	BOOL32  IsDDStreamCap( void )const { return (MEDIA_TYPE_NULL != tSecDSCap.GetMediaType() && 0 != tSecDSCap.GetMediaType());  }

    void    SetSecDSFrmRate(u8 byFrmRate)
    {
        if (MEDIA_TYPE_H264 != tSecDSCap.GetMediaType())
        {
            tSecDSCap.SetFrameRate(byFrmRate);
        }
        else
        {
            tSecDSCap.SetUserDefFrameRate(byFrmRate);
        }
    }
    u8      GetSecDSFrmRate(void) const
    {
        if (MEDIA_TYPE_H264 != tSecDSCap.GetMediaType())
        {
            return tSecDSCap.GetFrameRate();
        }
        else
        {
            return tSecDSCap.GetUserDefFrameRate();
        }
    }

    void	FECType2Str( u8 byFECType, s8* pchStr ) const
	{
		switch( byFECType )
		{
		case FECTYPE_NONE:
			memcpy(pchStr, "NONE", sizeof("NONE"));
			break;
		case FECTYPE_RAID5:
			memcpy(pchStr, "RAID5", sizeof("RAID5"));
			break;
		case FECTYPE_RAID6:
			memcpy(pchStr, "RAID6", sizeof("RAID6"));
			break;
		default:
			sprintf(pchStr, "WRONG VALUE<%d>", byFECType );
			break;
		}
	}
	void	Print(void) const
	{
        OspPrintf(TRUE, FALSE, "FECType:\n" );
		s8 achStr[32];
		OspPrintf(TRUE, FALSE, "\tVideo\t\t:");
		memset(achStr, 0, sizeof(achStr));
		FECType2Str( m_byVideoFECType, achStr );
		OspPrintf( TRUE, FALSE, "%s\n", achStr );

		OspPrintf(TRUE, FALSE, "\tAudio\t\t:");
		memset(achStr, 0, sizeof(achStr));
		FECType2Str( m_byAudioFECType, achStr );
		OspPrintf(TRUE, FALSE, "%s\n", achStr );

		OspPrintf(TRUE, FALSE, "\tDVideo\t\t:");
		memset(achStr, 0, sizeof(achStr));
		FECType2Str( m_byDVideoFECType, achStr );
		OspPrintf(TRUE, FALSE, "%s\n", achStr );

        OspPrintf(TRUE, FALSE, "TSecDSCap:\n");
        OspPrintf(TRUE, FALSE, "\tMediaType\t:%d\n", GetSecDSType());
        OspPrintf(TRUE, FALSE, "\tBitRate\t\t:%d\n", GetSecDSBitRate());
        OspPrintf(TRUE, FALSE, "\tResolution\t:%d\n", GetSecDSRes());
        OspPrintf(TRUE, FALSE, "\tFrameRate\t:%d\n", GetSecDSFrmRate());

        OspPrintf(TRUE, FALSE, "\n");
	}
}
PACKED
;

//定义会议信息结构,该结构定义了会议基本信息和状态 (len:1004)
//由于给会议文件增加了文件头，其中包括TConfInfo的结构体长度，
//因此今后给TConfInfo添加数据成员变量必须添加在所有数据成员的末尾，否则会导致读取会议文件出错
//周广程，2007-06-27
struct TConfInfo
{
protected:
    CConfId       m_cConfId;                        //会议号，全网唯一
    TKdvTime      m_tStartTime;                     //开始时间，控制台填0为立即开始
    u16           m_wDuration;                      //持续时间(分钟)，0表示不自动停止
    u16           m_wBitRate;                       //会议码率(单位:Kbps,1K=1024)
    u16           m_wSecBitRate;                    //双速会议的第2码率(单位:Kbps,为0表示是单速会议)
	u16			  m_wDcsBitRate;					//数据会议码率(单位:Kbps,为0表示不支持数据会议)
    u8            m_byDStreamScale;                 //双流百分比
    u8            m_byUsrGrpId;                     //用户组
    u8            m_byTalkHoldTime;                 //最小发言持续时间(单位:秒)
    u16            m_wMixDelayTime;                 //混音延时时间
    TCapSupport   m_tCapSupport;                    //会议支持的媒体
    s8            m_achConfPwd[MAXLEN_PWD+1];       //会议密码
    s8            m_achConfName[MAXLEN_CONFNAME+1]; //会议名
    s8            m_achConfE164[MAXLEN_E164+1];     //会议的E164号码
    TMtAlias      m_tChairAlias;                    //会议中主席的别名
    TMtAlias      m_tSpeakerAlias;                  //会议中发言人的别名
    TConfAttrb    m_tConfAttrb;                     //会议属性

    TMediaEncrypt m_tMediaKey;                      //第一版本所有密钥一样，不支持更新    
public:
    TConfStatus   m_tStatus;                        //会议状态

    // 4.0R3 版本扩展字段
protected:
    TConfAttrbEx  m_tConfAttrbEx;                   //会议扩展属性
	TCapSupportEx m_tCapSupportEx;					//会议能力集扩展属性
    
public:	
    TConfInfo( void )
    { 
		Reset();
    }
    void Reset()
	{
        memset( this, 0, sizeof( TConfInfo ) ); 
        m_tCapSupport.Clear(); 
        m_tConfAttrbEx.Reset(); 
	}
    CConfId GetConfId( void ) const { return m_cConfId; }
    void    SetConfId( CConfId cConfId ){ m_cConfId = cConfId; }
    void    SetUsrGrpId(u8 byGrpId) { m_byUsrGrpId = byGrpId; }
    u8      GetUsrGrpId( void ) const { return m_byUsrGrpId; }
    TKdvTime GetKdvStartTime( void ) const { return( m_tStartTime ); }
    void   SetKdvStartTime( TKdvTime tStartTime ){ m_tStartTime = tStartTime; }
    void   SetDuration(u16  wDuration){ m_wDuration = htons(wDuration);} 
    u16    GetDuration( void ) const { return ntohs(m_wDuration); }
    void   SetBitRate(u16  wBitRate){ m_wBitRate = htons(wBitRate);} 
    u16    GetBitRate( void ) const { return ntohs(m_wBitRate); }
    void   SetSecBitRate(u16 wSecBitRate){ m_wSecBitRate = htons(wSecBitRate);} 
    u16    GetSecBitRate( void ) const { return ntohs(m_wSecBitRate); }
	void   SetDcsBitRate(u16 wDcsBitRate){ m_wDcsBitRate = htons(wDcsBitRate); }
	u16	   GetDcsBitRate( void ) const { return ntohs(m_wDcsBitRate); }

	// fuxiuhua设置该配置信息的配置源(目前只有MCS_CONF, VCS_CONF)
	void   SetConfSource( u8 byConfSource )
	{
		m_cConfId.SetConfSource( byConfSource );
	}
	// fuxiuhua获取该配置信息的配置源
	u8     GetConfSource()
	{
		return m_cConfId.GetConfSource();
	}

    void   SetMainVideoFormat(u8 byVideoFormat)
    { 
        TSimCapSet tSim = m_tCapSupport.GetMainSimCapSet();
        tSim.SetVideoResolution(byVideoFormat); 
        m_tCapSupport.SetMainSimCapSet(tSim);
    } 
    u8     GetMainVideoFormat( void ) const { return m_tCapSupport.GetMainSimCapSet().GetVideoResolution(); }
    void   SetSecVideoFormat(u8 byVideoFormat)
    { 
        TSimCapSet tSim = m_tCapSupport.GetSecondSimCapSet();
        tSim.SetVideoResolution(byVideoFormat);
        m_tCapSupport.SetSecondSimCapSet(tSim); 
    } 
    u8     GetSecVideoFormat(void) const { return m_tCapSupport.GetSecondSimCapSet().GetVideoResolution(); }
    void   SetDoubleVideoFormat(u8 byVideoFormat) { m_tCapSupport.SetDStreamResolution(byVideoFormat); } 
    u8     GetDoubleVideoFormat(void) const { return m_tCapSupport.GetDStreamResolution(); }
    u8     GetVideoFormat(u8 byVideoType, u8 byChanNo = LOGCHL_VIDEO);
    u8     GetDStreamScale(void) const 
    { 
        u8 byScale = m_byDStreamScale;
        if (byScale > MAXNUM_DSTREAM_SCALE || byScale < MINNUM_DSTREAM_SCALE)
        {
            byScale = DEF_DSTREAM_SCALE;
        }       
        
        return byScale; 
    }
    void   SetDStreamScale(u8 byDStreamScale) { m_byDStreamScale = byDStreamScale; }

    void   SetMixDelayTime(u16 wDelayTime) { m_wMixDelayTime = htons(wDelayTime); }
    u16    GetMixDelayTime(void) { return ntohs(m_wMixDelayTime); }
    void   SetTalkHoldTime(u8   byTalkHoldTime){ m_byTalkHoldTime = byTalkHoldTime;} 
    u8     GetTalkHoldTime( void ) const { return m_byTalkHoldTime; }
    void   SetCapSupport(TCapSupport tCapSupport){ m_tCapSupport = tCapSupport;} 
    TCapSupport GetCapSupport( void ) const { return m_tCapSupport; }
    void   SetConfPwd( LPCSTR lpszConfPwd );
    LPCSTR GetConfPwd( void ) const { return m_achConfPwd; }
    void   SetConfName( LPCSTR lpszConfName );
    LPCSTR GetConfName( void ) const { return m_achConfName; }
    void   SetConfE164( LPCSTR lpszConfE164 );
    LPCSTR GetConfE164( void ) const { return m_achConfE164; }
    void   SetChairAlias(TMtAlias tChairAlias){ m_tChairAlias = tChairAlias;} 
    TMtAlias  GetChairAlias( void ) const { return m_tChairAlias; }
    void   SetSpeakerAlias(TMtAlias tSpeakerAlias){ m_tSpeakerAlias = tSpeakerAlias;} 
    TMtAlias  GetSpeakerAlias( void ) const { return m_tSpeakerAlias; }
    void   SetConfAttrb(TConfAttrb tConfAttrb){ m_tConfAttrb = tConfAttrb;} 
    TConfAttrb  GetConfAttrb( void ) const { return m_tConfAttrb; }
    void   SetStatus(TConfStatus tStatus){ m_tStatus = tStatus;} 
    TConfStatus  GetStatus( void ) const { return m_tStatus; }	

    void    SetHasVmpModule(BOOL32 bHas) { m_tConfAttrb.SetHasVmpModule(bHas); }
    void    SetHasTvwallModule(BOOL32 bHas) { m_tConfAttrb.SetHasTvWallModule(bHas); }

	TMediaEncrypt& GetMediaKey(void) { return m_tMediaKey; };
	void SetMediaKey(TMediaEncrypt& tMediaEncrypt){ memcpy(&m_tMediaKey, &tMediaEncrypt, sizeof(tMediaEncrypt));}

	void   GetVideoScale(u8 byVideoType, u16 &wVideoWidth, u16 &wVideoHeight, u8* pbyVideoResolution = NULL);
	BOOL   HasChairman( void ) const{ if(m_tStatus.m_tChairman.GetMtId()==0)return FALSE; return TRUE; }	
	TMt    GetChairman( void ) const{ return m_tStatus.m_tChairman; }
	void   SetNoChairman( void ){ memset( &m_tStatus.m_tChairman, 0, sizeof( TMt ) ); }
	void   SetChairman( TMt tChairman ){ m_tStatus.m_tChairman = tChairman; }
	BOOL   HasSpeaker( void ) const{ if(m_tStatus.m_tSpeaker.GetMtId()==0)return FALSE; return TRUE; }
    TMt    GetSpeaker( void ) const{ return m_tStatus.m_tSpeaker; }
	void   SetNoSpeaker( void ){ memset( &m_tStatus.m_tSpeaker, 0, sizeof( TMt ) ); }
	void   SetSpeaker( TMt tSpeaker ){ m_tStatus.m_tSpeaker = tSpeaker; }
	time_t GetStartTime( void ) const;	
	void   SetStartTime( time_t dwStartTime );

    u8     GetMainVideoMediaType( void ) const { return m_tCapSupport.GetMainVideoType();   }
    u8     GetMainAudioMediaType( void ) const { return m_tCapSupport.GetMainAudioType();   }
    u8     GetSecVideoMediaType( void ) const { return m_tCapSupport.GetSecVideoType(); }
    u8     GetSecAudioMediaType( void ) const { return m_tCapSupport.GetSecAudioType(); }
    u8     GetDStreamMediaType( void ) const { return m_tCapSupport.GetDStreamMediaType(); }

    //帧率
    void   SetMainVidFrameRate(u8 byMPI) { m_tCapSupport.SetMainVidFrmRate(byMPI);    }
    u8     GetMainVidFrameRate(void) const { return m_tCapSupport.GetMainVidFrmRate();    }
    void   SetSecVidFrameRate(u8 byMPI) { m_tCapSupport.SetSecVidFrmRate(byMPI);    }
    u8     GetSecVidFrameRate(void) const { return m_tCapSupport.GetSecVidFrmRate();    }
    void   SetDStreamFrameRate(u8 byMPI) { m_tCapSupport.SetDStreamFrmRate(byMPI);    }
    u8     GetDStreamFrameRate(void) const { return m_tCapSupport.GetDStreamFrameRate();    }

    //H264 自定义帧率
    void   SetMainVidUsrDefFPS(u8 byFPS) { m_tCapSupport.SetMainVidUsrDefFPS(byFPS);    }
    u8     GetMainVidUsrDefFPS(void) const { return m_tCapSupport.GetMainVidUsrDefFPS();    }
    BOOL32 IsMainVidUsrDefFPS(void) const { return m_tCapSupport.IsMainVidUsrDefFPS();    }
    void   SetSecVidUsrDefFPS(u8 byFPS) { m_tCapSupport.SetSecVidUsrDefFPS(byFPS);    }
    u8     GetSecVidUsrDefFPS(void) const { return m_tCapSupport.GetSecVidUsrDefFPS();    }
    BOOL32 IsSecVidUsrDefFPS(void) const { return m_tCapSupport.IsSecVidUsrDefFPS();    }
    void   SetDStreamUsrDefFPS(u8 byFPS) { m_tCapSupport.SetDStreamUsrDefFPS(byFPS);    }
    u8     GetDStreamUsrDefFPS(void) const { return m_tCapSupport.GetDStreamUsrDefFPS();    }
    BOOL32 IsDStreamUsrDefFPS(void) const { return m_tCapSupport.IsDStreamUsrDefFPS();    }

    void         SetConfAttrbEx(TConfAttrbEx tAttrbEx) { m_tConfAttrbEx = tAttrbEx; }
    TConfAttrbEx GetConfAttrbEx() const {return m_tConfAttrbEx; }
    void   SetSatDCastChnlNum(u8 byNum) { m_tConfAttrbEx.SetSatDCastChnlNum(byNum); }
    u8     GetSatDCastChnlNum() const { return m_tConfAttrbEx.GetSatDCastChnlNum(); }
    void   SetAutoRecAttrb(const TConfAutoRecAttrb& tAttrb ) { m_tConfAttrbEx.SetAutoRecAttrb(tAttrb); }
    TConfAutoRecAttrb GetAutoRecAttrb() const { return m_tConfAttrbEx.GetAutoRecAttrb(); }
    void   SetVmpAutoAdapt(BOOL32 bAutoAdapt) { m_tConfAttrbEx.SetVmpAutoAdapt(bAutoAdapt); }
    BOOL   IsVmpAutoAdapt() const { return m_tConfAttrbEx.IsVmpAutoAdapt(); }
    BOOL   IsSupportGkCharge(void) const { return ( strlen(m_tConfAttrbEx.GetGKUsrName()) > 0 ? TRUE : FALSE ); }
    void   SetDiscussAutoStop() { m_tConfAttrbEx.SetDiscussAutoStop(); }
    void   SetDiscussAutoSwitch2Mix() { m_tConfAttrbEx.SetDiscussAutoSwitch2Mix(); }
    BOOL   IsDiscussAutoStop() const { return m_tConfAttrbEx.IsDiscussAutoStop(); }

	//会议能力集扩展属性, zgc, 2007-09-26
	BOOL32	IsSupportFEC(void) const { return !m_tCapSupportEx.IsNoSupportFEC(); }
	TCapSupportEx GetCapSupportEx(void) const { return m_tCapSupportEx; }
	void	SetCapSupportEx(TCapSupportEx tCapSupportEx) { m_tCapSupportEx = tCapSupportEx; }

	// fxh VCS设置会议的调度级别
	void SetConfLevel(u8 byLevel)  { m_tConfAttrbEx.SetConfLevel(byLevel); }
	u8   GetConfLevel()            { return m_tConfAttrbEx.GetConfLevel(); }

	void SetConfRealSat(BOOL32 bSat) { m_tConfAttrbEx.SetConfRealSat(bSat);	}
	BOOL IsConfRealSat(void) {	return m_tConfAttrbEx.IsConfRealSat();	};

	void Print( void ) const
	{
		OspPrintf( TRUE, FALSE, "\nConfInfo:\n" );
		OspPrintf( TRUE, FALSE, "m_cConfId: " );
		m_cConfId.Print();
        OspPrintf( TRUE, FALSE, "m_byUsrGrpId: %d\n", GetUsrGrpId());
		OspPrintf( TRUE, FALSE, "\nm_tStartTime: " );
        m_tStartTime.Print();
		OspPrintf( TRUE, FALSE, "\nm_wDuration: %d\n", ntohs(m_wDuration) );
		OspPrintf( TRUE, FALSE, "m_wBitRate: %d\n", ntohs(m_wBitRate) );
        OspPrintf( TRUE, FALSE, "m_wSecBitRate: %d\n", ntohs(m_wSecBitRate) );
		OspPrintf( TRUE, FALSE, "m_wDcsBitRate: %d\n", ntohs(m_wDcsBitRate) );
		OspPrintf( TRUE, FALSE, "m_byVideoFormat: %d\n", GetMainVideoFormat() );
		OspPrintf( TRUE, FALSE, "m_byTalkHoldTime: %d\n", m_byTalkHoldTime );
        OspPrintf( TRUE, FALSE, "m_byDStreamScale: %d\n", m_byDStreamScale );
		OspPrintf( TRUE, FALSE, "m_tCapSupport:\n" );
	    m_tCapSupport.Print();
        OspPrintf( TRUE, FALSE, "m_tCapSupportEx: \n" );
        m_tCapSupportEx.Print();
		OspPrintf( TRUE, FALSE, "m_achConfName: %s\n", m_achConfName );
		OspPrintf( TRUE, FALSE, "m_achConfE164: %s\n", m_achConfE164 );
        OspPrintf( TRUE, FALSE, "m_achConfPwd: %s\n", m_achConfPwd );
        OspPrintf( TRUE, FALSE, "m_tChairAlias:" );
        m_tChairAlias.Print();
        OspPrintf( TRUE, FALSE, "m_tSpeakerAlias:" );
        m_tSpeakerAlias.Print();
		OspPrintf( TRUE, FALSE, "\n" );
        OspPrintf( TRUE, FALSE, "m_tConfAttrbEx: \n" );
        m_tConfAttrbEx.Print();
	}
}
/*
#ifndef WIN32
__attribute__ ( (packed) ) 
#endif
*/
PACKED
;

/*-------------------------------------------------------------------
                               TMt                                  
--------------------------------------------------------------------*/

/*====================================================================
    函数名      ：operator==
    功能        ：根据ID判断是否相等
    算法实现    ：
    引用全局变量：
    输入参数说明：const TMt & tObj, 判断对象
    返回值说明  ：TRUE/FALSE
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    03/01/02    1.0         LI Yi         创建
	04/06/28    3.0         胡昌威        修改
====================================================================*/
inline BOOL TMt::operator ==( const TMt & tObj ) const
{
	if( tObj.GetType() != GetType() )
	{
		return FALSE;
	}

	switch( tObj.GetType() ) 
	{
	case TYPE_MCU:
		if( tObj.GetMcuId() == GetMcuId() ) 
		{
			return TRUE;
		}
		break;
	case TYPE_MCUPERI:
		if( tObj.GetMcuId() == GetMcuId() && tObj.GetEqpType() == GetEqpType() 
			&& tObj.GetEqpId() ==  GetEqpId() )
		{
			return TRUE;
		}
		break;
	case TYPE_MT:
        if( tObj.GetMcuId() == GetMcuId() && tObj.GetMtId() ==  GetMtId() 
			&& tObj.GetConfIdx() == GetConfIdx() )
		{
			return TRUE;
		}
		break;
	default:
		break;
	}

	return FALSE;
}

/*====================================================================
    函数名      ：SetMcu
    功能        ：设置MCU
    算法实现    ：
    引用全局变量：
    输入参数说明：u8 byMcuId, MCU号
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    2002/07/26  1.0         LI Yi         创建
    2003/10/28  3.0         胡昌威        修改  
====================================================================*/
inline void TMt::SetMcu( u8 byMcuId )
{
	m_byMainType = TYPE_MCU;
	m_bySubType = 0;
	m_byMcuId = byMcuId;
	m_byEqpId = 0;	
	m_byConfDriId = 0;  
    m_byConfIdx = 0;    
}

/*====================================================================
    函数名      ：SetMcuEqp
    功能        ：设置MCU外设
    算法实现    ：
    引用全局变量：
    输入参数说明：u8 byMcuId, MCU号
				  u8 byEqpId, 外设号
				  u8 byEqpType, 外设类型
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    2002/07/26  1.0         LI Yi         创建
    2003/06/06  1.0         LI Yi         增加外设类型参数
    2003/10/28  3.0         胡昌威        修改  
====================================================================*/
inline void TMt::SetMcuEqp( u8 byMcuId, u8 byEqpId, u8 byEqpType )
{
	m_byMainType = TYPE_MCUPERI;
	m_bySubType = byEqpType;
	m_byMcuId = byMcuId;
	m_byEqpId = byEqpId;	
	m_byConfDriId = 0;  
    m_byConfIdx = 0; 
}

/*====================================================================
    函数名      ：SetMt
    功能        ：设置终端
    算法实现    ：
    引用全局变量：
    输入参数说明：u8 byMcuId, MCU号
				  u8 byMtId, 终端号
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    2002/07/26  1.0         LI Yi         创建
    2003/10/28  3.0         胡昌威        修改  
====================================================================*/
inline void TMt::SetMt( u8 byMcuId, u8 byMtId, u8 byDriId, u8 byConfIdx )
{
	m_byMainType = TYPE_MT;
	m_bySubType = 0;
	m_byMcuId = byMcuId;
	m_byEqpId = byMtId;	
	m_byConfDriId = byDriId;  
    m_byConfIdx = byConfIdx; 
}

/*====================================================================
    函数名      ：SetMt
    功能        ：设置终端
    算法实现    ：
    引用全局变量：
    输入参数说明：TMt tMt 
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    2005/01/24  3.6         魏治兵        创建
====================================================================*/
inline void TMt::SetMt( TMt tMt )
{
	SetMt(tMt.GetMcuId(), tMt.GetMtId(), tMt.GetDriId(), tMt.GetConfIdx());
}

/*-------------------------------------------------------------------
                               CConfId                                  
--------------------------------------------------------------------*/

/*====================================================================
    函数名      ：GetConfId
    功能        ：获得会议号数组
    算法实现    ：
    引用全局变量：
    输入参数说明：u8 * pbyConfId, 传入的BUFFER数组指针，用来返回会议号
			      u8 byBufLen, BUFFER大小
    返回值说明  ：实际返回数组大小
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/12/31    1.0         LI Yi         创建
====================================================================*/
inline u8 CConfId::GetConfId( u8 * pbyConfId, u8 byBufLen ) const
{
	u8	byLen = min( sizeof( m_abyConfId ), byBufLen );
	memcpy( pbyConfId, m_abyConfId, byLen );

	return( byLen );
}

/*====================================================================
    函数名      ：GetConfIdString
    功能        ：获得会议号字符串
    算法实现    ：
    引用全局变量：
    输入参数说明：LPSTR lpszConfId, 传入的字符串BUFFER数组指针，用来
	                   返回0结尾会议号字符串
			      u8 byBufLen, BUFFER大小
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/12/31    1.0         LI Yi         创建
====================================================================*/
inline void CConfId::GetConfIdString( LPSTR lpszConfId, u8 byBufLen ) const
{
	u8	byLoop;

	for( byLoop = 0; byLoop < sizeof( m_abyConfId ) && byLoop < ( byBufLen - 1 ) / 2; byLoop++ )
	{
		sprintf( lpszConfId + byLoop * 2, "%.2x", m_abyConfId[byLoop] );
	}
	lpszConfId[byLoop * 2] = '\0';
}

/*====================================================================
    函数名      ：SetConfId
    功能        ：设置会议号数组
    算法实现    ：
    引用全局变量：
    输入参数说明：const CConfId & cConfId, 输入会议号
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/12/31    1.0         LI Yi         创建
====================================================================*/
inline void CConfId::SetConfId( const CConfId & cConfId )
{
	cConfId.GetConfId( m_abyConfId, sizeof( m_abyConfId ) );
}

/*====================================================================
    函数名      ：SetConfId
    功能        ：设置会议号数组
    算法实现    ：
    引用全局变量：
    输入参数说明：const u8 * pbyConfId, 传入的数组指针
			      u8 byBufLen, BUFFER大小
    返回值说明  ：实际设置数组大小
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/12/31    1.0         LI Yi         创建
====================================================================*/
inline u8 CConfId::SetConfId( const u8 * pbyConfId, u8 byBufLen )
{
	u8	bySize = min( byBufLen, sizeof( m_abyConfId ) );
	
	memset( m_abyConfId, 0, sizeof( m_abyConfId ) );
	memcpy( m_abyConfId, pbyConfId, bySize );

	return( bySize );
}
	
/*====================================================================
    函数名      ：SetConfId
    功能        ：设置会议号数组
    算法实现    ：
    引用全局变量：
    输入参数说明：LPCSTR lpszConfId, 传入的会议号字符串
    返回值说明  ：实际设置数组大小
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/12/31    1.0         LI Yi         创建
====================================================================*/
inline u8 CConfId::SetConfId( LPCSTR lpszConfId )
{
	LPCSTR	lpszTemp = lpszConfId;
	s8	achTemp[3], *lpszStop;
	u8	byCount = 0;

	memset( m_abyConfId, 0, sizeof( m_abyConfId ) );
	while( lpszTemp != NULL && lpszTemp + 1 != NULL && byCount < sizeof( m_abyConfId ) )
	{
		memcpy( achTemp, lpszTemp, 2 );
		achTemp[2] = '\0';
		m_abyConfId[byCount] = ( u8 )strtoul( achTemp, &lpszStop, 16 );
		byCount++;
		lpszTemp += 2;
	}

	return( byCount );
}

/*====================================================================
    函数名      ：CreateConfId
    功能        ：创建会议号
    算法实现    ：根据当前时间和随机值
    引用全局变量：
    输入参数说明：无
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    03/06/06    1.0         LI Yi         创建
====================================================================*/
inline void CConfId::CreateConfId( u8 byUsrGrpId )
{
	struct tm	*ptmCurTime;
	time_t		tCurTime = time( NULL );
	u8	byTemp;
	u16	wTemp;

	memset( m_abyConfId, 0, sizeof( m_abyConfId ) );
	
	//get current time
	ptmCurTime = localtime( &tCurTime );
	//year
	wTemp = ptmCurTime->tm_year + 1900;
	memcpy( m_abyConfId, &wTemp, sizeof( u16 ) );
	//month
	byTemp = ptmCurTime->tm_mon + 1;
	memcpy( m_abyConfId + 2, &byTemp, sizeof( u8 ) );
	//day
	byTemp = ptmCurTime->tm_mday;
	memcpy( m_abyConfId + 3, &byTemp, sizeof( u8 ) );
	//hour
	byTemp = ptmCurTime->tm_hour;
	memcpy( m_abyConfId + 4, &byTemp, sizeof( u8 ) );
	//minute
	byTemp = ptmCurTime->tm_min;
	memcpy( m_abyConfId + 5, &byTemp, sizeof( u8 ) );
	//second
	byTemp = ptmCurTime->tm_sec;
	memcpy( m_abyConfId + 6, &byTemp, sizeof( u8 ) );
	//msec
	wTemp = 0;
	memcpy( m_abyConfId + 7, &wTemp, sizeof( u16 ) );

	//rand
	wTemp = rand();
	memcpy( m_abyConfId + 9, &wTemp, sizeof( u16 ) );

    // 顾振华 [6/21/2006]
    // 最低位表示组ID
    SetUsrGrpId( byUsrGrpId );
}

/*====================================================================
    函数名      ：IsNull
    功能        ：判断会议号是否为空
    算法实现    ：
    引用全局变量：
    输入参数说明：无
    返回值说明  ：TRUE/FALSE
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    03/03/31    1.0         LI Yi         创建
====================================================================*/
inline BOOL CConfId::IsNull( void ) const
{
	u8	abyNull[sizeof( m_abyConfId )];

	memset( abyNull, 0, sizeof( abyNull ) );
	if( memcmp( m_abyConfId, abyNull, sizeof( m_abyConfId ) ) == 0 )
		return( TRUE );
	else
		return( FALSE );
}

/*====================================================================
    函数名      ：SetNull
    功能        ：设置会议号为空
    算法实现    ：
    引用全局变量：
    输入参数说明：无
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    03/03/31    1.0         LI Yi         创建
====================================================================*/
inline void CConfId::SetNull( void )
{
	memset( m_abyConfId, 0, sizeof( m_abyConfId ) );
}

/*====================================================================
    函数名      ：operator==
    功能        ：操作符重载
    算法实现    ：
    引用全局变量：
    输入参数说明：const CConfId & cConfId, 输入会议号
    返回值说明  ：相等返回TRUE，否则返回FALSE
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/12/31    1.0         LI Yi         创建
====================================================================*/
inline BOOL CConfId::operator == ( const CConfId & cConfId ) const
{
	u8	abyTemp[sizeof( m_abyConfId )];

	cConfId.GetConfId( abyTemp, sizeof( abyTemp ) );
	if( memcmp( abyTemp, m_abyConfId, sizeof( m_abyConfId ) ) == 0 )
		return( TRUE );
	else
		return( FALSE );
}

/*-------------------------------------------------------------------
                               TCapSupport                             
--------------------------------------------------------------------*/
/*=============================================================================
  函 数 名： SetDStreamType
  功    能： 设置双流参数
  算法实现： 
  全局变量： 
  参    数： u8 byDStreamType
  返 回 值： inline void 
=============================================================================*/
inline void TCapSupport::SetDStreamType( u8 byDStreamType ) 
{ 
    m_byDStreamType = byDStreamType;
    
    switch(byDStreamType)
    {
    case VIDEO_DSTREAM_MAIN:
        m_tDStreamCap.SetMediaType(m_tMainSimCapSet.GetVideoMediaType());
        m_tDStreamCap.SetSupportH239(FALSE);
        break;
    case VIDEO_DSTREAM_H263PLUS:
        m_tDStreamCap.SetMediaType(MEDIA_TYPE_H263PLUS);
        m_tDStreamCap.SetSupportH239(FALSE);
        break;
    case VIDEO_DSTREAM_H263PLUS_H239:
        m_tDStreamCap.SetMediaType(MEDIA_TYPE_H263PLUS);
        m_tDStreamCap.SetSupportH239(TRUE);
        break;
    case VIDEO_DSTREAM_H263_H239:
        m_tDStreamCap.SetMediaType(MEDIA_TYPE_H263);
        m_tDStreamCap.SetSupportH239(TRUE);
        break;
    case VIDEO_DSTREAM_H264_H239:
        m_tDStreamCap.SetMediaType(MEDIA_TYPE_H264);
        m_tDStreamCap.SetSupportH239(TRUE);
        break;
    case VIDEO_DSTREAM_H264:
        m_tDStreamCap.SetMediaType(MEDIA_TYPE_H264);
        m_tDStreamCap.SetSupportH239(FALSE);
        break;
    case VIDEO_DSTREAM_H264_H263PLUS_H239:
        m_tDStreamCap.SetMediaType(MEDIA_TYPE_H264);
        m_tDStreamCap.SetSupportH239(TRUE);
        break;
    default:
        break;
    }
}

/*====================================================================
    函数名      ：IsSupportMediaType
    功能        ：判断第一路音视频是否支持某种媒体类型
    算法实现    ：
    引用全局变量：
    输入参数说明：u8   byMediaType 媒体类型       
    返回值说明  ：
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    04/03/18    3.0         胡昌威          创建             
====================================================================*/
inline BOOL32  TCapSupport::IsSupportMediaType( u8 byMediaType ) const
{
    BOOL32  bSupport = FALSE;
	switch( byMediaType ) 
	{
	case MEDIA_TYPE_H261:		
	case MEDIA_TYPE_H262:		
	case MEDIA_TYPE_H263:
	case MEDIA_TYPE_H264:		
	case MEDIA_TYPE_MP4:
//  case MEDIA_TYPE_H263PLUS:	
        bSupport = (m_tMainSimCapSet.GetVideoMediaType() == byMediaType ||
                    m_tSecondSimCapSet.GetVideoMediaType() == byMediaType);
        break;   
		
	case MEDIA_TYPE_PCMA:	
	case MEDIA_TYPE_PCMU:	
	case MEDIA_TYPE_G722:	
	case MEDIA_TYPE_G7231:	
	case MEDIA_TYPE_G728:	
	case MEDIA_TYPE_G729:	
	case MEDIA_TYPE_MP3:
    case MEDIA_TYPE_G7221C:
    case MEDIA_TYPE_AACLC:
    case MEDIA_TYPE_AACLD:
        bSupport = (m_tMainSimCapSet.GetAudioMediaType() == byMediaType ||
                    m_tSecondSimCapSet.GetAudioMediaType() == byMediaType);
        break;
    default:
        break;	
	}

	return bSupport;
}

/*-------------------------------------------------------------------
                               TConfInfo                             
--------------------------------------------------------------------*/

/*====================================================================
    函数名      ：GetVideoFormat
    功能        ：获取图像的分辨率
    算法实现    ：
    引用全局变量：
    输入参数说明：u8 byVideoType,
                  u8 byChanNo
    返回值说明  ：图像的分辨率
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    05/09/21    4.0         libo          创建
====================================================================*/
inline u8 TConfInfo::GetVideoFormat(u8 byVideoType, u8 byChanNo)
{
    if (LOGCHL_VIDEO == byChanNo)
    {
        if (m_tCapSupport.GetMainSimCapSet().GetVideoMediaType() == byVideoType)
        {
            return m_tCapSupport.GetMainSimCapSet().GetVideoResolution();
        }
        else
        {
            return m_tCapSupport.GetSecondSimCapSet().GetVideoResolution();
        }
    }
    else
    {
        return m_tCapSupport.GetDStreamResolution();
    }
}

/*====================================================================
    函数名      ：GetVideoScale
    功能        ：得到视频规模
    算法实现    ：
    引用全局变量：
    输入参数说明：u16 &wVideoWidth 视频宽度
                  u16 &wVideoHeight 视频高度	
                  强制指定计算某种分辨率
    返回值说明  ：
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    03/12/05    3.0         胡昌威          创建             
====================================================================*/
inline void  TConfInfo::GetVideoScale(u8 byVideoType, u16 &wVideoWidth, u16 &wVideoHeight, u8* pbyVideoResolution/* = NULL */)
{
   
    u8 byVideoFormat;
    if (m_tCapSupport.GetMainSimCapSet().GetVideoMediaType() == byVideoType)
    {
        byVideoFormat = m_tCapSupport.GetMainSimCapSet().GetVideoResolution();
    }
    else
    {
        byVideoFormat = m_tCapSupport.GetSecondSimCapSet().GetVideoResolution();
    }
    if( NULL != pbyVideoResolution )
    {
        byVideoFormat = *pbyVideoResolution;
    }
    
    //  [4/24/2006] mpeg4 16cif 按auto处理
    if (MEDIA_TYPE_MP4 == byVideoType && VIDEO_FORMAT_16CIF == byVideoFormat)
    {
        byVideoFormat = VIDEO_FORMAT_AUTO;
    }

    switch (byVideoFormat)
	{
    case VIDEO_FORMAT_SQCIF_112x96:
        wVideoWidth = 112;
        wVideoHeight = 96;
        break;
        
    case VIDEO_FORMAT_SQCIF_96x80:
        wVideoWidth = 96;
        wVideoHeight = 80;
        break;

    case VIDEO_FORMAT_SQCIF:
		wVideoWidth = 128;
        wVideoHeight = 96;
    	break;
		
    case VIDEO_FORMAT_QCIF:
		wVideoWidth = 176;
        wVideoHeight = 144;
    	break;

    case VIDEO_FORMAT_CIF:
		wVideoWidth = 352;
        wVideoHeight = 288;
    	break;

    case VIDEO_FORMAT_2CIF:
        wVideoWidth = 352;
        wVideoHeight = 576;
        break;

	case VIDEO_FORMAT_4CIF:
        // 4CIF统一为704*576, zgc, 2008-09-05
        /*
        if ( MEDIA_TYPE_H264 == byVideoType)
        {
		    wVideoWidth = 720;
        }
        else*/
        {
            wVideoWidth = 704;
        }
        wVideoHeight = 576;
		break;

	case VIDEO_FORMAT_16CIF:
		wVideoWidth = 1408;
        wVideoHeight = 1152;
		break;

    case VIDEO_FORMAT_SIF:
        wVideoWidth = 352;
        wVideoHeight = 240;
        break;

    case VIDEO_FORMAT_4SIF:
        wVideoWidth = 704;
        wVideoHeight = 480;
        break;

    case VIDEO_FORMAT_VGA:
        wVideoWidth = 640;
        wVideoHeight = 480;
        break;

    case VIDEO_FORMAT_SVGA:
        wVideoWidth = 800;
        wVideoHeight = 600;
        break;

    case VIDEO_FORMAT_XGA:
        wVideoWidth = 1024;
        wVideoHeight = 768;
        break;        

    case VIDEO_FORMAT_W4CIF:
        wVideoWidth = 1024;
        wVideoHeight = 576;
        break;

    case VIDEO_FORMAT_HD720:
        wVideoWidth = 1280;
        wVideoHeight = 720;
        break;

    case VIDEO_FORMAT_SXGA:
        wVideoWidth = 1280;
        wVideoHeight = 1024;
        break;

    case VIDEO_FORMAT_UXGA:
        wVideoWidth = 1600;
        wVideoHeight = 1200;
        break;

    case VIDEO_FORMAT_HD1080:
        wVideoWidth = 1920;
        wVideoHeight = 1088;
        break;

	default:
		wVideoWidth = 352;
        wVideoHeight = 288;
		break;
    }

}

/*====================================================================
    函数名      ：GetStartTime
    功能        ：获得该会议开始时间
    算法实现    ：
    引用全局变量：
    输入参数说明：无
    返回值说明  ：time_t类型时间（local Time），控制台填0为立即开始
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/30    1.0         LI Yi         创建
    02/08/23    1.0         LI Yi         将time_t型时间转换为字符串型保存
====================================================================*/
inline time_t TConfInfo::GetStartTime( void ) const
{
	time_t	dwStartTime;
	
	if( m_tStartTime.GetYear() != 0 )	//不是即时会议
		m_tStartTime.GetTime( dwStartTime );
	else
		dwStartTime = 0;

	return( dwStartTime );
}

/*====================================================================
    函数名      ：SetStartTime
    功能        ：设置该会议开始时间
    算法实现    ：
    引用全局变量：
    输入参数说明：time_t dwStartTime, 开始时间，0为立即开始
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/31    1.0         LI Yi         创建
    02/08/23    1.0         LI Yi         将time_t型时间转换为字符串型保存
====================================================================*/
inline void TConfInfo::SetStartTime( time_t dwStartTime )
{
	if( dwStartTime != 0 )	//不是即时会议
		m_tStartTime.SetTime( &dwStartTime );
	else
		memset( &m_tStartTime, 0, sizeof( TKdvTime ) );
}


/*====================================================================
    函数名      ：SetConfPwd
    功能        ：设置别名
    算法实现    ：
    引用全局变量：
    输入参数说明：LPCSTR lpszConfPwd, 别名
    返回值说明  ：字符串指针
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/26    1.0         LI Yi         创建
====================================================================*/
inline void TConfInfo::SetConfPwd( LPCSTR lpszConfPwd )
{
	if( lpszConfPwd != NULL )
	{
		strncpy( m_achConfPwd, lpszConfPwd, sizeof( m_achConfPwd ) );
		m_achConfPwd[sizeof( m_achConfPwd ) - 1] = '\0';
	}
	else
	{
		memset( m_achConfPwd, 0, sizeof( m_achConfPwd ) );
	}
}

/*====================================================================
    函数名      ：SetConfName
    功能        ：设置别名
    算法实现    ：
    引用全局变量：
    输入参数说明：LPCSTR lpszConfName, 别名
    返回值说明  ：字符串指针
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/26    1.0         LI Yi         创建
====================================================================*/
inline void TConfInfo::SetConfName( LPCSTR lpszConfName )
{
	if( lpszConfName != NULL )
	{
		strncpy( m_achConfName, lpszConfName, sizeof( m_achConfName ) );
		m_achConfName[sizeof( m_achConfName ) - 1] = '\0';
	}
	else
	{
		memset( m_achConfName, 0, sizeof( m_achConfName ) );
	}
}

/*====================================================================
    函数名      ：SetConfE164
    功能        ：设置别名
    算法实现    ：
    引用全局变量：
    输入参数说明：LPCSTR lpszConfE164, 别名
    返回值说明  ：字符串指针
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    02/07/26    1.0         LI Yi         创建
====================================================================*/
inline void TConfInfo::SetConfE164( LPCSTR lpszConfE164 )
{
	if( lpszConfE164 != NULL )
	{
		strncpy( m_achConfE164, lpszConfE164, sizeof( m_achConfE164 ) );
		m_achConfE164[sizeof( m_achConfE164 ) - 1] = '\0';
	}
	else
	{
		memset( m_achConfE164, 0, sizeof( m_achConfE164 ) );
	}
}

/*-------------------------------------------------------------------
                               TMtAlias                             
--------------------------------------------------------------------*/
/*====================================================================
    函数名      ：operator ==
    功能        ：比较两个终端别名是否相等 
    算法实现    ：
    引用全局变量：
    输入参数说明：void
    返回值说明  ：TRUE - 相等 FALSE - 不相等
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    2003/11/13  3.0         胡昌威         创建
====================================================================*/
inline  BOOL   TMtAlias::operator ==( const TMtAlias & tObj ) const
{
    if( tObj.m_AliasType == 0 || tObj.m_AliasType != m_AliasType ) 
	{
		return FALSE ;
	}

	if( tObj.m_AliasType == mtAliasTypeTransportAddress )
	{
		if( (tObj.m_tTransportAddr.GetIpAddr() == m_tTransportAddr.GetIpAddr()) && 
			(tObj.m_tTransportAddr.GetPort() == m_tTransportAddr.GetPort()) && 
			(tObj.m_tTransportAddr.GetIpAddr() != 0 ))
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		if( (memcmp( tObj.m_achAlias, m_achAlias, sizeof( m_achAlias ) ) == 0) && 
			(m_achAlias[0] != 0) )
		{
            return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
}

/*====================================================================
    函数名      ：SetTime
    功能        ：设置时间
    算法实现    ：
    引用全局变量：
    输入参数说明：const time_t * ptTime, 要设置的时间
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    03/02/07    1.0         秦重军         创建
====================================================================*/
inline void TKdvTime::SetTime( const time_t * ptTime )
{
	tm *ptLocalTime;
	
	ptLocalTime = ::localtime( ptTime );

	m_wYear = htons( (u16)ptLocalTime->tm_year + 1900 );
	m_byMonth = (u8)ptLocalTime->tm_mon + 1;
	m_byMDay = (u8)ptLocalTime->tm_mday;
	m_byHour = (u8)ptLocalTime->tm_hour;
	m_byMinute = (u8)ptLocalTime->tm_min;
	m_bySecond = (u8)ptLocalTime->tm_sec;
}

/*====================================================================
    函数名      ：GetTime
    功能        ：得到时间结构
    算法实现    ：
    引用全局变量：
    输入参数说明：time_t & tTime, 返回的时间
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    03/02/07    1.0         秦重军         创建
====================================================================*/
inline void TKdvTime::GetTime( time_t & tTime ) const
{
	tm tTmCurTime;

	tTmCurTime.tm_year = ntohs( m_wYear ) - 1900;
	tTmCurTime.tm_mon = m_byMonth - 1;
	tTmCurTime.tm_mday = m_byMDay;
	tTmCurTime.tm_hour = m_byHour;
	tTmCurTime.tm_min = m_byMinute;
	tTmCurTime.tm_sec = m_bySecond;

	tTime = ::mktime( &tTmCurTime );
}

/*====================================================================
    函数名      ：operator ==
    功能        ：==重载
    算法实现    ：
    引用全局变量：
    输入参数说明：const TKdvTime & tTime, 比较的时间
    返回值说明  ：无
----------------------------------------------------------------------
    修改记录    ：
    日  期      版本        修改人        修改内容
    03/06/07    1.0         李屹          创建
====================================================================*/
inline BOOL TKdvTime::operator == ( const TKdvTime & tTime )
{
	if( memcmp( this, &tTime, sizeof( TKdvTime ) ) == 0 )
		return( TRUE );
	else
		return( FALSE );
}

#ifdef WIN32
#pragma pack( pop )
#endif

#undef SETBITSTATUS
#undef GETBITSTATUS

#endif //_VCCOMMON_040602_H_


 
