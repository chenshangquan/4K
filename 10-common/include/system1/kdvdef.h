/*****************************************************************************
   模块名      : KDV define 
   文件名      : kdvdef.h
   相关文件    : 
   文件实现功能: KDV宏定义
   作者        : 魏治兵
   版本        : V3.0  Copyright(C) 2001-2002 KDC, All rights reserved.
-----------------------------------------------------------------------------
   修改记录:
   日  期      版本        修改人      修改内容
   2004/02/17  3.0         魏治兵        创建
******************************************************************************/

#ifndef _KDV_DEFINE_H_
#define _KDV_DEFINE_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*媒体类型定义*/
#define   MEDIA_TYPE_NULL                 (u8)255  /*媒体类型为空*/
	
/*音频*/
#define	  MEDIA_TYPE_MP3	              (u8)96  /*mp3 mode 0-4*/
#define   MEDIA_TYPE_G7221C	              (u8)98  /*G722.1.C Siren14*/
#define   MEDIA_TYPE_G719	              (u8)99  /*G719 non-standard of polycom serial 22*/
#define   MEDIA_TYPE_PCMA		          (u8)8   /*G.711 Alaw  mode 5*/
#define   MEDIA_TYPE_PCMU		          (u8)0   /*G.711 ulaw  mode 6*/
#define   MEDIA_TYPE_G721		          (u8)2   /*G.721*/
#define   MEDIA_TYPE_G722		          (u8)9   /*G.722*/
#define	  MEDIA_TYPE_G7231		          (u8)4   /*G.7231*/
#define   MEDIA_TYPE_ADPCM                (u8)5   /*DVI4 ADPCM*/
#define	  MEDIA_TYPE_G728		          (u8)15  /*G.728*/
#define	  MEDIA_TYPE_G729		          (u8)18  /*G.729*/
#define   MEDIA_TYPE_G7221                (u8)13  /*G.7221*/
#define   MEDIA_TYPE_AACLC                (u8)102 /*AAC LC*/
#define   MEDIA_TYPE_AACLD                (u8)103 /*AAC LD*/
#define   MEDIA_TYPE_ISAC_32              (u8)104
#define   MEDIA_TYPE_OPUS                 (u8)120
#define	  MEDIA_TYPE_RED		          (u8)127

/*视频*/
#define   MEDIA_TYPE_MP4	              (u8)97  /*MPEG-4*/
#define   MEDIA_TYPE_H261	              (u8)31  /*H.261*/
#define   MEDIA_TYPE_H262	              (u8)33  /*H.262 (MPEG-2)*/
#define   MEDIA_TYPE_H263	              (u8)34  /*H.263*/
#define   MEDIA_TYPE_H263PLUS             (u8)101 /*H.263+*/
#define   MEDIA_TYPE_H264	              (u8)106 /*H.264*/
#define   MEDIA_TYPE_H264_ForHuawei       (u8)105 /*H.264*/
#define	  MEDIA_TYPE_FEC				  (u8)107 /* fec custom define */
#define   MEDIA_TYPE_H265	              (u8)108 /*H.265*/

/*数据*/
#define   MEDIA_TYPE_H224	              (u8)100  /*H.224 Payload 暂定100*/
#define   MEDIA_TYPE_T120                 (u8)200  /*T.120媒体类型*/
#define   MEDIA_TYPE_H239                 (u8)239  /*H.239数据类型 */
#define   MEDIA_TYPE_MMCU                 (u8)220  /*级联数据通道 */

/*kdv约定的本地发送时使用的活动媒体类型 */
#define   ACTIVE_TYPE_PCMA		          (u8)110   /*G.711 Alaw  mode 5*/
#define   ACTIVE_TYPE_PCMU		          (u8)111   /*G.711 ulaw  mode 6*/
#define   ACTIVE_TYPE_G721		          (u8)112   /*G.721*/
#define   ACTIVE_TYPE_G722		          (u8)113   /*G.722*/
#define	  ACTIVE_TYPE_G7231		          (u8)114   /*G.7231*/
#define	  ACTIVE_TYPE_G728		          (u8)115   /*G.728*/
#define	  ACTIVE_TYPE_G729		          (u8)116   /*G.729*/
#define   ACTIVE_TYPE_G7221               (u8)117   /*G.7221*/
#define   ACTIVE_TYPE_H261	              (u8)118   /*H.261*/
#define   ACTIVE_TYPE_H262	              (u8)119   /*H.262 (MPEG-2)*/
#define   ACTIVE_TYPE_H263	              (u8)120   /*H.263*/
#define   ACTIVE_TYPE_G7221C			  (u8)121	/*G7221c*/
#define   ACTIVE_TYPE_ADPCM				  (u8)122	/*ADPCM*/	
#define   ACTIVE_TYPE_G719                (u8)123   /*G.719*/
#define   ACTIVE_TYPE_OPUS                (u8)127	/*OPUS*/

/*APP ID*/
#define AID_KDV_BASE                      (u16)0 
/*网管客户端内部应用号（1-10）*/
#define AID_NMC_BGN            (AID_KDV_BASE + 1)
#define AID_NMC_END            (AID_NMC_BGN + 9)

/*网管服务器内部应用号（11-20）*/
#define AID_NMS_BGN            (AID_NMC_END + 1)
#define AID_NMS_END            (AID_NMS_BGN + 9)	

/*终端控制台内部应用号（21-30）*/
#define AID_MTC_BGN            (AID_NMS_END + 1)
#define AID_MTC_END            (AID_MTC_BGN + 9)

/*网管接入服务器内部应用号（31-40）*/
#define AID_NMSAC_BGN          (AID_MTC_END + 1)
#define AID_NMSAC_END          (AID_NMSAC_BGN + 9)

/*魔云NMS内部应用号（31-40） 注意：与网管接入服务器内部应用号区间冲突*/
#define AID_TNMS_BGN           (AID_MTC_END + 1)
#define AID_TNMS_END           (AID_TNMS_BGN + 9) 

/*代理内部应用号（41-50）*/
#define AID_AGT_BGN            (AID_NMSAC_END + 1)
#define AID_AGT_END            (AID_AGT_BGN + 9)

/*MCU内部应用号（51-100）*/
#define AID_MCU_BGN            (AID_AGT_END + 1)
#define AID_MCU_END            (AID_MCU_BGN + 49)

/*MT内部应用号（101-150）*/
#define AID_MT_BGN             (AID_MCU_END + 1)
#define AID_MT_END             (AID_MT_BGN + 49)

/*RECORDER内部应用号（151-160）*/
#define AID_REC_BGN            (AID_MT_END + 1)
#define AID_REC_END            (AID_REC_BGN + 9)

/*混音器内部应用号（161-170）*/
#define AID_MIXER_BGN          (AID_REC_END + 1)
#define AID_MIXER_END          (AID_MIXER_BGN + 9)

/*电视墙内部应用号（171-181）*/
#define AID_TVWALL_BGN         (AID_MIXER_END + 1)
#define AID_TVWALL_END         (AID_TVWALL_BGN + 9)

/*T.120服务器内部应用号（181-200）*/
#define AID_DCS_BGN            (AID_TVWALL_END + 1)
#define AID_DCS_END            (AID_DCS_BGN + 19)

/*T.120控制台内部应用号（201-210）*/
#define AID_DCC_BGN            (AID_DCS_END + 1)
#define AID_DCC_END            (AID_DCC_BGN + 9)

/*码率适配服务器内部应用号（211-220）*/
#define AID_BAS_BGN            (AID_DCC_END + 1)
#define AID_BAS_END            (AID_BAS_BGN + 9)

/*GK服务器内部应用号(221 - 230)*/
#define AID_GKS_BGN            (AID_BAS_END + 1)
#define AID_GKS_END            (AID_GKS_BGN + 9)

/*GK控制台内部应用号(231 - 235)*/
#define AID_GKC_BGN            (AID_GKS_END + 1)
#define AID_GKC_END            (AID_GKC_BGN + 4)

/*用户管理内部应用号(236 - 240)*/
#define AID_UM_BGN             (AID_GKC_END + 1)
#define AID_UM_END             (AID_UM_BGN + 4)

/*地址簿内部应用号(241 - 250)*/
#define AID_ADDRBOOK_BGN       (AID_UM_END + 1)
#define AID_ADDRBOOK_END       (AID_ADDRBOOK_BGN + 9)

/*数据会议终端内部应用号(251 - 260)*/
#define AID_DCMT_BGN           (AID_ADDRBOOK_END + 1)
#define AID_DCMT_END           (AID_DCMT_BGN + 9)

/*mdsc hdsc watchdog 模块(261-265) hualiang add*/
#define AID_DSC_BGN            (AID_DCMT_END + 1) 
#define AID_DSC_END            (AID_DSC_BGN + 4)

/* radius 计费 模块(266-275) guozhongjun add*/
#define  AID_RS_BGN            (AID_DSC_END + 1)
#define  AID_RS_END            (AID_RS_BGN + 9)

/* 文件升级服务器 模块(276 - 283) wanghao 2007/1/4 */
#define AID_SUS_BGN            (AID_RS_END + 1)
#define AID_SUS_END            (AID_SUS_BGN + 7)

/* 文件升级客户端 模块(284 - 285) wanghao 2007/1/4 */
#define AID_SUC_BGN            (AID_SUS_END + 1)
#define AID_SUC_END            (AID_SUC_BGN + 1)

/* 文件升级服务器终端 模块(286 - 287) wy 2011/09/07 */
#define AID_CONNSUS_BGN        (AID_SUC_END + 1)
#define AID_CONNSUS_END        (AID_CONNSUS_BGN + 1)

/*wuyuelong 以下范围行业实际未使用
// RTSP server 模块(286 - 290) xsl add 
//#define AID_RTSP_BGN			AID_CONNSUS_END +1
//#define AID_RTSP_END			AID_RTSP_BGN +5


// Traversal Server 模块(291 - 320) 
//#define AID_TS_BGN				AID_RTSP_END + 1
//#define AID_TS_END				AID_TS_BGN + 29
*/


/* 文件传输LIB(433-444) */ //从云视讯移植(20130924 wuyuelong)
//#define AID_FILETRANS_BGN	  ( 432 + 1 )
//#define AID_FILETRANS_END	  ( AID_FILETRANS_BGN + 12 )

/* MPCD服务器 模块(288 - 297) */ //chenwc[2012/02/01]
#define AID_MPCD_BGN		   (AID_CONNSUS_END + 1)
#define AID_MPCD_END		   (AID_MPCD_BGN + 9)

/* Fireproxy 内部模块(301 - 320) */
#define AID_FPXY_BGN		   (AID_CONNSUS_END + 14)
#define AID_FPXY_END		   (AID_FPXY_BGN + 19)

/* Traversal Server 模块(321 - 350) */
#define AID_TS_BGN			   (AID_FPXY_END + 1)
#define AID_TS_END			   (AID_TS_BGN + 29)

/* 8000E及KDVP 新增模块(351-380) */
#define AID_8000E_BGN          (AID_TS_END + 1)
#define AID_8000E_END          (AID_8000E_BGN + 29)

/* KDVP 新增模块(351-380) */
// KDVP don't permit work with 8000E,zgc,2011-07-29
#define AID_KDVP_BGN           (AID_8000E_BGN)
#define AID_KDVP_END           (AID_8000E_END)

/* 全球认证服务(381-382) */
#define AID_GLOBALAUTHSERVER   (AID_8000E_END + 1)
#define AID_GLOBALAUTHCLIENT   (AID_GLOBALAUTHSERVER + 1)

/* SA服务器模块(383-390) */
#define AID_SA_BGN           ( AID_GLOBALAUTHCLIENT + 1 )
#define AID_SA_END           ( AID_SA_BGN + 7 )

/* LGS服务器模块(391-412) */
#define AID_LGS_BGN           ( AID_SA_END + 1 )
#define AID_LGS_END           ( AID_LGS_BGN + 21 )

/* ULS服务器模块(413-427) */ //chenwc[2011/08/20] 预留一定的APP号考虑后续做负载均衡
#define AID_ULS_BGN			  ( AID_LGS_END + 1 )
#define AID_ULS_END			  ( AID_ULS_BGN + 14 )

/* MMPU服务器模块(428-432) */
#define AID_MMPU_BGN          ( AID_ULS_END + 1 )
#define AID_MMPU_END          ( AID_MMPU_BGN + 4 )

/* 文件传输LIB(433-444) */ //chenwc[2011/10/08]
#define AID_FILETRANS_BGN	  ( AID_MMPU_END + 1 )
#define AID_FILETRANS_END	  ( AID_FILETRANS_BGN + 12 )

/* ULS性能测试(445-449) */ //wy[2012/03/20]
#define AID_ULS_PFM_BGN       ( AID_FILETRANS_END + 1 )
#define AID_ULS_PFM_END       ( AID_ULS_PFM_BGN + 4 )

//APP ID
#define AID_KDM_BASE                    (u16)450    

/*3AC内部应用号（451-460）*/
#define AID_3AC_BGN                     ( AID_KDM_BASE +1 )
#define AID_3AC_END                     ( AID_3AC_BGN + 9 )

/*3AS内部应用号（461-470）*/
#define AID_3AS_BGN                     ( AID_3AC_END + 1 )
#define AID_3AS_END                     ( AID_3AS_BGN + 29 )

/*NTS内部应用号（491-500）*/
#define AID_NTS_BEG                     ( AID_3AS_END + 1 )
#define AID_NTS_END                     ( AID_NTS_BEG + 9 )

/*CPADAPT内部应用号（501-510）*/
#define AID_CPADAPT_BEG                 ( AID_NTS_END + 1 )
#define AID_CPADAPT_END                 ( AID_CPADAPT_BEG + 9 )

/*电子白板内部应用号（511-520）*/
#define AID_WHITE_BOARD_BEG             ( AID_CPADAPT_END + 1 )
#define AID_WHITE_BOARD_END             ( AID_WHITE_BOARD_BEG + 9 ) 

//网呈应用号（521-600）
#define AID_TP_BGN                      ( AID_WHITE_BOARD_END + 1 )
#define AID_TP_END                      ( AID_TP_BGN + 79 )

//协议应用号（601-620）
#define AID_PROTOCOL_BGN                ( AID_TP_END  + 1 )
#define AID_PROTOCOL_END                ( AID_PROTOCOL_BGN + 29 )

// 监控产品各模块的监听端口
const u16 PORT_TNMS             = 60000;
const u16 PORT_TNMC             = 60000;
const u16 PORT_3AS              = 60000;
const u16 PORT_3AC              = 60000;

/*2004/07/15 不同类型音频码率定义*/
#define AUDIO_BITRATE_G711A		64
#define AUDIO_BITRATE_G711U		64
#define AUDIO_BITRATE_G7231		6
#define AUDIO_BITRATE_MP3		48
#define AUDIO_BITRATE_G728		16
#define AUDIO_BITRATE_G729		8/*暂不支持*/
#define AUDIO_BITRATE_G722		64
#define AUDIO_BITRATE_G7221C	24
#define AUDIO_BITRATE_G719		24  //lukunpeng [2010/04/15]
#define AUDIO_BITRATE_AAC		96  /* guzh [01/18/2008] */
#define AUDIO_BITRATE_DEFAULT	64 //qianlin 20130314
#define AUDIO_BITRATE_MAXOPUS	56
#define AUDIO_BITRATE_MINOPUS	8

#define	MIN_BITRATE_4CIF		256
#define MIN_BITRATE_720P		384

/*视频会议产品各模块的监听端口*/
const u16 PORT_NMS				= 60000;
const u16 PORT_NMC				= 60000;
const u16 PORT_MCU				= 60000;
const u16 PORT_MCS				= 60000;
const u16 PORT_MT				= 60000;
const u16 PORT_MTC				= 60000;
const u16 PORT_TVWALL			= 60000;
const u16 PORT_DIGITALMIXER		= 60000;
const u16 PORT_RECORDER        	= 60000;
const u16 PORT_DCS				= 61000;
const u16 PORT_GK              	= 60000;
const u16 PORT_GKC        		= 60000; 
const u16 PORT_RS               = 61000;
const u16 PORT_GK_8000E         = 62000;

//add by zhanghb For kdvp2.0
const u16 PORT_TS1_KDVP         = 61000;
const u16 PORT_TS2_KDVP         = 62000;
//end add

/*视频会议产品各产品类型定义*/
const u16 MT_TYPE_KDV7620_B    = 0x042D;
const u16 MT_TYPE_KDV7620_A    = 0x042E;

const u16 MT_TYPE_KDV7820_A    = 0x0431;
const u16 MT_TYPE_KDV7920_A    = 0x0432;

const u16 MT_TYPE_KDV7820_B    = 0x043B;
const u16 MT_TYPE_KDV7920_B    = 0x043C;


//产品pid
#define BRD_PID_KDM200_HDU				0x043A
#define BRD_PID_KDM200_HDU_L		    0x0444
#define BRD_PID_KDM200_HDU_D			0x0445 
#define BRD_PID_KDV_EAPU		        0x0443
#define BRD_PID_KDV_MPU					0x0436
#define BRD_PID_KDV_MAU					0x0439	
#define BRD_PID_KDV8000A_MPC2		    0x043D
#define BRD_PID_KDV8000A_CRI2			0x043E
#define BRD_PID_KDV8000A_DRI2   		0x043F
#define BRD_PID_KDV8000A_IS21   		0x0440
#define BRD_PID_KDV8000A_IS22  			0x0441 
#define KDV8000E						0x0442
//4.7新版卡  [2/2/2012 chendaiwei]
#define BRD_PID_KDV8000A_HDU2			0x0450
#define BRD_PID_KDV8000A_MPU2			0x044F
#define BRD_PID_KDV8000A_APU2			0x0451
#define BRD_PID_KDV8000A_HDU2_L			0x0460
#define BRD_PID_KDV8000A_HDU2_S			0x0464

//4.8新板卡
#define BRD_PID_KDV10000A_CEU			0x046C
#define BRD_PID_KDV10000A_SMU			0x046D

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif /* _KDV_def_H_ */

/* end of file kdvdef.h */
