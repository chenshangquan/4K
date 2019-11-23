/*******************************************************************************
 * 模块名  : COMMON_MSG
 * 文件名  : rk100_msg.h
 * 相关文件:
 * 文件功能: RK100 TCP通信协议公用消息、数据结构定义
 * 作者      : 袁增兴
 * 版本      : 1.0
 * -----------------------------------------------------------------------------
 * 修改记录:
 * 日  期        版本       修改人                          修改内容
 * 2018/09/26  1.0      yuanzengxing@kedacom.com     创建
*******************************************************************************/
#ifndef __RK100_MSG_H
#define __RK100_MSG_H

#define SN_LENGTH                        36    //SN长度
#define ENCRYPT_LENGTH                   36    //密钥长度
#define RK100_LISTEN_PORT                8000

/* 消息事件ID定义 */
enum EMRK100EvtId
{
    /* 用户登录, 消息体:TRK100LoginInfo
     * 应答消息体:NULL */
    RK100_EVT_LOGIN                     =2500,
    RK100_EVT_LOGIN_ACK                 =2501,

    /* 设置密码, 消息体:TRK100LoginInfo
     * 应答消息体:NULL */
    RK100_EVT_SET_PASSWORD              =2502,
    RK100_EVT_SET_PASSWORD_ACK          =2503,

    /* 获取板级信息, 消息体:NULL
     * 应答消息体:TRK100BrdInfo */
    RK100_EVT_GET_BRD_INFO              =2504,
    RK100_EVT_GET_BRD_INFO_ACK          =2505,

    /* 设置板级信息, 消息体:TRK100BrdInfo
     * 应答消息体:NULL */
    RK100_EVT_SET_BRD_INFO              =2506,
    RK100_EVT_SET_BRD_INFO_ACK          =2507,

    /* 重启设备, 消息体:NULL
     * 应答消息体:NULL */
    RK100_EVT_REBOOT                    =2508,
    RK100_EVT_REBOOT_ACK                =2509,

    /* 发起单板TFTP升级, 消息体:TRK100TftpFwUpdate
     * 应答消息体:TRK100UpdateHead
     * 单板升级结束或者实际失败后发送, 服务器注意等待时间可能较长 */
    RK100_EVT_TFTP_UPDATE_FIRST         =2510,
    RK100_EVT_TFTP_UPDATE_FIRST_ACK     =2511,

    /* 发起单板TFTP升级, 消息体:TRK100TftpFwUpdate
     * 应答消息体:NULL
     * 单板升级结束或者实际失败后发送, 服务器注意等待时间可能较长 */
    RK100_EVT_TFTP_UPDATE_SECOND        =2512,
    RK100_EVT_TFTP_UPDATE_SECOND_ACK    =2513,

    /* 获取网络参数, 消息体:NULL
     * 应答消息体:TRK100NetParam */
    RK100_EVT_GET_NETPARAM              =2514,
    RK100_EVT_GET_NETPARAM_ACK          =2515,

    /* 设置网络参数, 消息体:TRK100NetParam
     * 应答消息体:NULL */
    RK100_EVT_SET_NETPARAM              =2516,
    RK100_EVT_SET_NETPARAM_ACK          =2517,

    /* 恢复出厂请求, 消息体:TRK100LoginInfo
     * 应答消息体:NULL */
    RK100_EVT_RESTORE                   =2518,
    RK100_EVT_RESTORE_ACK               =2519,

    /* 获取工作模式, 消息体:NULL
     * 应答消息体:TRK100WorkMode */
    RK100_EVT_GET_WORK_MODE             =2520,
    RK100_EVT_GET_WORK_MODE_ACK         =2521,

    /* 设置工作模式, 消息体:TRK100WorkMode
     * 应答消息体:NULL */
    RK100_EVT_SET_WORK_MODE             =2522,
    RK100_EVT_SET_WORK_MODE_ACK         =2523,

    /* 设置心跳, 消息体:NULL
     * 应答消息体:NULL */
    RK100_EVT_SET_HEART_BEAT            =2524,
    RK100_EVT_SET_HEART_BEAT_ACK        =2525,

    /* 获取功耗, 消息体:NULL
     * 应答消息体:TRK100PowerInfo */
    RK100_EVT_GET_POWER                 =2526,
    RK100_EVT_GET_POWER_ACK             =2527,

    /* 被抢登 */
    RK100_EVT_LOGIN_OTHER               =2528,

    /* 升级结束或者实际失败后发送,服务器注意等待时间可能较长 */
    RK100_EVT_TFTP_UPDATE_FIRST_NOTIFY  =2529,
    RK100_EVT_TFTP_UPDATE_SECOND_NOTIFY =2530,

    /* 设置调试模式, 消息体:TRK100DebugMode
     * 应答消息体:NULL */
    RK100_EVT_SET_DEBUG_MODE            =2531,
    RK100_EVT_SET_DEBUG_MODE_ACK        =2532,

    /* 获取调试模式, 消息体:NULL
     * 应答消息体:TRK100DebugMode */
    RK100_EVT_GET_DEBUG_MODE            =2533,
    RK100_EVT_GET_DEBUG_MODE_ACK        =2534,

    //新增部分
   /*=========================lpc1837控制sony机芯-xzy add========================*/
	/*一、聚焦,消息体：CamFocusAutoManualMode
	 *应答消息体：NULL*/
    RK100_EVT_SET_CAM_FOCUS             =2535,
    RK100_EVT_SET_CAM_FOCUS_ACK         =2536,
	/*二、ZOOM值调节，消息体：CamZoomVal
	 *应答消息体：NULL*/
	RK100_EVT_SET_CAM_ZOOM_VAL            =2537,
	RK100_EVT_SET_CAM_ZOOM_VAL_ACK        =2538,

    /*三、光圈调节，消息体：ApertureAutoMode
		 *应答消息体：NULL*/
	RK100_EVT_SET_CAM_IRIS            =2539,
	RK100_EVT_SET_CAM_IRIS_ACK        =2540,

	/*四、曝光设置，消息体：ExposAutoMode
	 *应答消息体：NULL*/
	RK100_EVT_SET_CAM_EXPOSURE            =2541,
	RK100_EVT_SET_CAM_EXPOSURE_ACK        =2542,

    /*五、白平衡调节，消息体：CamWBMode
		 *应答消息体：CamWBMode_Ack*/
	RK100_EVT_SET_CAM_WB                  =2543,
	RK100_EVT_SET_CAM_WB_ACK              =2544,

	 /*六、图像参数调节,消息体：CamImagParam
	  *应答消息体：NULL*/
	RK100_EVT_SET_CAM_ImagParam           =2545,
	RK100_EVT_SET_CAM_ImagParam_ACK       =2546,
	
	/*七、降噪调节，消息体：NULL
	 *应答消息体：NULL*/		
	RK100_EVT_SET_CAM_D2NR                  =2547,
	RK100_EVT_SET_CAM_D2NR_ACK              =2548,
	
	/*八、预置位，消息体：NULL
	 *应答消息体：NULL*/
	RK100_EVT_SET_CAM_Preset_PowOnRecall  =2549,
	RK100_EVT_SET_CAM_Preset_PowOnRecall_ACK  =2550,

	/*九、获取白平衡值，消息体：NULL
	 *应答消息体：CamWBMode_Ack*/
	RK100_EVT_GET_CAM_WB                =2551,
	RK100_EVT_GET_CAM_WB_ACK            =2552,

    /*零、输出制式，消息体：TPOutputFmt        //新增
	 *应答消息体：NULL*/ 
    RK100_EVT_SET_CAM_OUTPUT_FORMAT   =2553,
    RK100_EVT_SET_CAM_OUTPUT_FORMAT_ACK   =2554,

    /*十、预置位列表，消息体：NULL
	 *应答消息体：--- */
	RK100_EVT_SET_CAM_Preset_List            =2555,
	RK100_EVT_SET_CAM_Preset_List_ACK         =2556,

	/*十一、保存预置位，消息体：NULL
	 *应答消息体：--- */
	RK100_EVT_SET_CAM_Preset_Save             =2557,
	RK100_EVT_SET_CAM_Preset_Save_ACK         =2558,

	/*四.一、快门设置*/
	RK100_EVT_SET_CAM_SHUTTER                =2559,
	RK100_EVT_SET_CAM_SHUTTER_ACK            =2560,

	/*四.二、增益设置*/
	RK100_EVT_SET_CAM_GAIN                =2561,
	RK100_EVT_SET_CAM_GAIN_ACK            =2562,

    /*七.一、D3降噪调节，消息体：NULL
	 *应答消息体：NULL*/		
	RK100_EVT_SET_CAM_D3NR                  =2563,
	RK100_EVT_SET_CAM_D3NR_ACK              =2564,


    /*机芯同步功能*/
    RK100_EVT_SET_CAM_ID                  = 2567,
    RK100_EVT_SET_CAM_ID_ACK                  = 2568,

    //恢复默认
    RK100_EVT_RECOVERY_DEFAULT_SET           = 2569,
    RK100_EVT_RECOVERY_DEFAULT_SET_ACK       = 2570,

};

/* 事件处理返回值定义 */
enum EMRK100OptRtn
{
    RK100_OPT_RTN_OK                   = 0x0000, /* 操作成功*/

    RK100_OPT_ERR_EVT_ID               = 0x8000, /* 不支持的事件ID */
    RK100_OPT_ERR_USER                 = 0x8001, /* 用户名错误 */
    RK100_OPT_ERR_PASSWORD             = 0x8002, /* 密码错误 */
    RK100_OPT_ERR_NO_LOGIN             = 0x8003, /* 用户未登录 */
    RK100_OPT_ERR_PARAM                = 0x8004, /* 参数错误 */
    RK100_OPT_ERR_LEN                  = 0x8005, /* 长度错误 */
    RK100_OPT_ERR_NO_MEMORY            = 0x8006, /* 没有内存 */
    RK100_OPT_ERR_CHKSUM               = 0x8007, /* 校验和错误 */
    RK100_OPT_ERR_FUNC_FAILE           = 0x8008, /* 底层函数操作失败 */
    RK100_OPT_ERR_BUSY                 = 0x8009, /* 设备正忙 */
    RK100_OPT_ERR_FIRST_LOGIN          = 0x800A, /* 首次登录 */
    RK100_OPT_ERR_LOCKED               = 0x800B, /* 设备锁定 */
    RK100_OPT_ERR_UNKNOWN              = 0xFFFF, /* 未知错误 */
};

/* 设备运行状态定义 */
enum EMRK100DevStat
{
    RK100_DEV_STAT_RUN_OK              = 0x0000, /* 设备运行正常 */
    RK100_DEV_STAT_UPDATE              = 0x0001, /* 设备处于升级状态 */
    RK100_DEV_STAT_IN_BOOT             = 0x8001, /* 设备处于BOOT模式 */
    RK100_DEV_STAT_WAINING             = 0x8002, /* 设备有告警 */
    RK100_DEV_STAT_UNKNOWN             = 0xFFFF, /* 未知状态 */
};

/* 客户端和服务端之间通信的消息头部结构定义 */
typedef struct
{
    u32 dwHandle;             /* 消息令牌,透传 */
    u32 dwRsvd;               /* 备用 */
    u32 dwSerial;             /* 流水号 一个请求/应答中,该值保持不变 */
    u16 wExtLen;              /* 扩展头字节数,含填充字节 */
    u16 wReserved1;           /* 保留 */

    u32 dwProtocolVer;        /* 协议版本号, 由各单板自行定义,型如：1.1.1.1或0x01010101 */
    u32 dwEvent;              /* 事件,表示不同的操作码,见EMRK100EvtId定义 */
    s32 nArgv;                /* 设备处理函数返回的私有错误码或客户端传递的参数数据 */
    u16 wOptRtn;              /* 事件处理返回值。详见: EMRK100OptRtn */
    u16 wMsgLen;              /* 后续消息体长度 */
} TRK100MsgHead;

/* 登录校验 */
typedef struct
{
    char szUsr[64];
    char szPwd[64];
} TRK100LoginInfo;

/* 功耗信息 */
typedef struct
{
    u32 dwCurrent;            /* 外设的功率mW */
    u32 dwPower;              /* 外设的电流mA */
} TRK100PowerInfo;

/* 单板信息定义 */
typedef struct
{
    u8   abyMac[6];           /* MAC地址 */
    u16  wHid;                /* hid */
    u16  wPid;                /* pid */
    char szSoftVer[32];       /* 单板业务软件编译时间, 如: "Jan 9 2017 15:56:12" */
    char szSn[SN_LENGTH];     /* 序列号,只读 */
    u32  dwExt;               /* 扩展保留 */
} TRK100BrdInfo;

/* 通过TFTP进行升级 */
typedef struct
{
    u32  dwTftpSvrIp;         /* TFTP 服务器地址,网络序 */
    u32  dwFileSize;          /* 文件大小 */
    char szFwTypeName[64];    /* 固件类型名称 */
    char szFileFullName[260]; /* 下载文件名 */
    u8   byChkSumValid;       /* 版本数据校验和有效标志，非0时下面参数才有效 */
    u8   byChkSum;            /* 版本数据校验和，文件字节累加的值 */
    u8   byRsved;             /* 保留 */
} TRK100TftpFwUpdate;

 /* 网络参数 */
typedef struct {
    u8  byDhcpEn;             /* 1表示使用动态IP地址,以下参数在获取到地址信息后赋值 */
    u8  byRsved[1];           /* 预留字段 */
    u16 MqttPort;             /* mqtt端口 */
    u32 dwIP;                 /* IP地址 */
    u32 dwSubMask;            /* 子网掩码 */
    u32 dwGateway;            /* 网关 */
    u32 dwMqttIP;             /* mqtt地址 */
} TRK100NetParam;

/* 工作模式 */
typedef struct
{
    u8 AcFlag;                /* AC启动的标志 1:启动 0: 不启用 */
    u8 AcDelay;               /* AC上电以后的延时0~180s */
    u8 Uart0Flag;             /* uart0 开启标志 1: 启用 0: 不启用 */
    u8 Uart0SndDat[32];       /* uart0 发送的内容 */
    u8 Uart0RevDat[32];       /* uart0 接收的内容 */
    u8 Uart0SndLen;           /* uart0 发送的内容长度 */
    u8 Uart0RevLen;           /* uart0 接收的内容长度 */
    u8 Uart0Delay;            /* uart0 操作延时 */
    u8 Uart1Flag;             /* uart1 开启标志 1: 启用 0: 不启用 */
    u8 Uart1SndDat[32];       /* uart1 发送的内容 */
    u8 Uart1RevDat[32];       /* uart1 接收的内容 */
    u8 Uart1SndLen;           /* uart1 发送的内容长度 */
    u8 Uart1RevLen;           /* uart1 接收的内容长度 */
    u8 Uart1Delay;            /* uart1 操作延时 */
    u8 Uart2Flag;             /* uart2 开启标志 1: 启用 0: 不启用 */
    u8 Uart2SndDat[32];       /* uart2 发送的内容 */
    u8 Uart2RevDat[32];       /* uart2 接收的内容 */
    u8 Uart2SndLen;           /* uart2 发送的内容长度 */
    u8 Uart2RevLen;           /* uart2 接收的内容长度 */
    u8 Uart2Delay;            /* uart2 操作延时 */
    u8 Ir0Flag;               /* 红外发送0 开启标志 1: 启用 0: 不启用 */
    u8 Ir0Index;              /* 红外发送0的码形下标 CalcDate[Ir0Index] */
    u8 Ir0Delay;              /* 红外发送0延时 */
    u8 Ir1Flag;               /* 红外发送1 开启标志 1: 启用 0: 不启用 */
    u8 Ir1Index;              /* 红外发送1的码形下标 CalcDate[Ir1Index] */
    u8 Ir1Delay;              /* 红外发送1延时 */
    u8 RfFlag;                /* RF模块开启标志 1: 启用 0: 不启用 */
    u8 RfID[5][5];            /* RF模块ID号 RfID[0][0]:0x0 禁用 0x1:启用 RfID[0][1]..RfID[0][4]:RF开关的ID */
} TFuncMod;

/* 操作模式结构体 */
typedef struct
{
    TFuncMod FuncMod[4];      /* 4个操作模式 0:开机 1:关机 2:唤醒 3:待机 */
} TRK100WorkMode;

typedef struct
{
    u32 Magic;
    u8  FileCrc;
    u8  Version[64];
    u8  TftpCount;
} TRK100UpdateHead;

typedef struct
{
    u8  DebugSW;              /* 1:开启串口 0:关闭串口 */
} TRK100DebugMode;
#endif


/*=======================xzy add=======================*/
//摄像机输出60/30fps  曝光--快门
typedef struct 
{
	u8 SixtyFpsModeFlag;
	u8 ThirtyFpsModeFlag;
	u8 Shutter_30Sp ;         // 1/30
    u8 Shutter_50Sp ;         // 1/50
	u8 Shutter_60Sp ;         // 1/60
	u8 Shutter_90Sp ;         // 1/90
	u8 Shutter_100Sp;         // 1/100(默认)
	u8 Shutter_125Sp;         // 1/125
	u8 Shutter_180Sp;         // 1/180
	u8 Shutter_250Sp;         // 1/250
	u8 Shutter_350Sp;         // 1/350
	u8 Shutter_500Sp;         // 1/500
	u8 Shutter_725Sp;         // 1/725
	u8 Shutter_1000Sp;        // 1/1000
	u8 Shutter_1500Sp;        // 1/1500
	u8 Shutter_2000Sp;        // 1/2000
	u8 Shutter_3000Sp;        // 1/3000
	u8 Shutter_4000Sp;        // 1/4000
	u8 Shutter_6000Sp;        // 1/6000
	u8 Shutter_10000Sp;        // 1/10000
}TPSOrThShutter;//xzy 

//摄像机输出50/25fps  曝光--快门
typedef struct  
{
	u8 FiftyFpsModeFlag;
	u8 TenwFifFpsModeFlag;
	u8 Shutter_25Spd ;         // 1/25
    u8 Shutter_30Spd ;         // 1/30
	u8 Shutter_50Spd ;         // 1/50
	u8 Shutter_60Spd ;         // 1/60
	u8 Shutter_100Spd;         // 1/100(默认)
	u8 Shutter_120Spd;         // 1/120
	u8 Shutter_150Spd;         // 1/150
	u8 Shutter_215Spd;         // 1/215
	u8 Shutter_300Spd;         // 1/300
	u8 Shutter_425Spd;         // 1/425
	u8 Shutter_600Spd;         // 1/600
	u8 Shutter_1000Spd;        // 1/1000
	u8 Shutter_1250Spd;        // 1/1250
	u8 Shutter_1750Spd;        // 1/1750
	u8 Shutter_2500Spd;        // 1/2500
	u8 Shutter_3500Spd;        // 1/3500
	u8 Shutter_6000Spd;        // 1/6000
	u8 Shutter_10000Spd;        // 1/10000
}TPFOrTwShutter;//xzy


typedef struct
{
    u8 AutoModeFlag;      /* 1:开启自动模式 0:关闭开启自动模式，开启手动模式 */
	u8 ManualModeFlag;
    u8 focusFarFlag;
    u8 focusNearFlag;
    u8 FarNearStopFlag;
} TCamFocusAutoManualMode;

typedef struct
{
    u32 InputVal;  //界面输入的精确Zoom值
    u8 InputPreciseValFlag;   /* 输入精确值。1:开启自动模式 0:关闭开启自动模式，开启手动模式 */
	u8 ZoomUpFlag;  //Zoom+
	u8 ZoomDownFlag;  //Zoom-
	u8 ZoomUpDownStopFlag;
} TCamZoomVal; 


typedef struct
{
	u8 IrisAutoFlag;
	u8 IrisBackCompFlag;  //背光补偿
    u8 IrisManuFlag;  
	u8 optIrisF4_4Flag;
	u8 optIrisF4_0Flag;
	u8 optIrisF3_7Flag;
	u8 optIrisF3_4Flag;
	u8 optIrisF3_1Flag;
    u8 optIrisF2_8Flag;
} TIrisAutoManuMode;    //光圈

typedef struct
{
    u8 ExposAutoModeFlag;    /* 1:开启自动模式 0:关闭开启自动模式，开启手动模式 */
} TExposAutoMode;  

typedef struct
{
     /* 1:开启自动模式 0:关闭开启自动模式，开启手动模式 */
	  //u8 ExposManuModeFlag;  
      TPSOrThShutter SixtyOrThirtyMode;  //
      TPFOrTwShutter FiftyOrTwentyMode;  //
} TShutterMode;  

typedef struct
{
    u8 CAMGainCmdUpFlag;
    u8 CAMGainCmdDownFlag;
    //u8 CAMGainEnterPrecisValFlag;
    u8 GainInputVal;
} TGainMode;

typedef struct
{
    u8 CamWBAutoModeFlag; 
	u8 CamWBManuModeFlag;
   	u8 RGainVal; //
    u8 BGainVal;  //
} TCamWBMode; 

typedef struct
{
   u8 BrightVal; //亮度
   u8 ColorHueVal;//色度
   u8 ColorGainVal;//饱和度
   u8 Gamma_opt_1_flag;// /* 1:开启自动模式 0:关闭开启自动模式，开启手动模式 */
   u8 Gamma_opt_2_flag;//
   u8 Gamma_opt_3_flag;//
   
} TCamImagParam;  

typedef struct
{
    u8 D2NROnFlag;
    u8 D2NROffFlag;
    u8 D2NR_level_1_Flag;
    u8 D2NR_level_2_Flag;
    u8 D2NR_level_3_Flag;
    u8 D2NR_level_4_Flag;
    u8 D2NR_level_5_Flag;
} TCamD2NRMode; //

typedef struct
{
    u8 D3NROnFlag;
    u8 D3NROffFlag;
    u8 D3NR_level_1_Flag;
    u8 D3NR_level_2_Flag;
    u8 D3NR_level_3_Flag;
    u8 D3NR_level_4_Flag;
    u8 D3NR_level_5_Flag;
} TCamD3NRMode;  //

typedef struct
{
    u8 RVal;
	  u8 BVal;
}TCamWBMode_Ack;

typedef struct
{
    u8 FMT4K_30fps_flag;
    u8 FMT4K_25fps_flag;
    u8 FMT1080_60fps_flag;
    u8 FMT1080_50fps_flag;
    u8 FMT1080_30fps_flag;
    u8 FMT1080_25fps_flag;
    u8 FMT720_60fps_flag;
    u8 FMT720_50fps_flag;
}TPOutputFmt;//输出制式，新增

typedef struct
{
    u8 PresetNumber1;
    u8 PresetNumber2;
    u8 PresetNumber3;
    u8 PresetNumber4;
    u8 PresetNumber5;
    u8 PresetNumber6;
    u8 PresetNumber7;
    u8 PresetNumber8;
}TCamPresetNumberList;


typedef struct
{
    u8 PresetSaveFlge;
    u8 PresetRecallFlag;
    TCamPresetNumberList SelctPresetNumberFlag;  //
    u8 PresetDelFlag;
    u8 PresetModifyFlag;
    u8 PresetNumber;  //预置位编号
}TCamPresetSave;

typedef struct
{
    u8 CamNum1Flag;  //机芯1
    u8 CamNum2Flag;
    u8 CamNum3Flag;  
    u8 SyncFlag;  //同步
}TCamID;

typedef struct tagTTPMoonCamInfo
{
    //u8                 byIndex;//相机标识：机芯1、2、3
    TCamID       TCamIDIndex;//相机标识：机芯1、2、3
    TPOutputFmt       OutputFmt;
    u32                dwZoomPos;         //实际设置到机芯里视野的zoom数值-xzy
    //	BOOL               bIsUsed; //预留位置是否启用
    //	BOOL               bIsPreUsed;//启动是否调用预置位1
    
    TCamFocusAutoManualMode       FocusMode;//聚焦模式-xzy
    //	u32                dwFocusValue;//聚焦值
    TIrisAutoManuMode       IrisMode;//光圈模式-xzy
    TExposAutoMode       ExpMode;//曝光模式-xzy 
    TShutterMode    ShutterMode; //快门
    TGainMode        GainMode;//增益
    TCamWBMode         WBMode;//白平衡模式：手动、自动-xzy
    TCamImagParam    CamImagParam;
    TCamD2NRMode     CamD2NRMode;
    TCamD3NRMode     CamD3NRMode;
}TTPMoonCamInfo;