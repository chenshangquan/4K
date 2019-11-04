/*
 * Kedacom Hardware Abstract Level
 *
 * brd_info.h
 *
 * Copyright (C) 2013-2020, Kedacom, Inc.
 *
 * History:
 *   2013/09/22 - [xuliqin] Create
 *
 */

#ifndef _BRD_PRD_H
#define _BRD_PRD_H

#ifdef __cplusplus
extern "C" {
#endif

#include <drvlib_def.h>

#ifndef USE_KLSP_DEFINES
/*
 * Product firmware infomation definition
 */
#define PINFO_USERDATA_LEN      64
#define PINFO_ISPDATA_LEN       4096
/* Flag0 defines */
#define PINFO_FLAG0_TEST        0x00000001 /* Test flag */
#define PINFO_FLAG0_TESTIP      0x00000002 /* Test IP address exist flag */
/* Flag1 defines */
#define PINFO_FLAG1_CMODE       0x00000001 /* 0-PAL, 1-NTSC */
#define PINFO_FLAG1_VOUT        0x00000006
#define PINFO_FLAG1_VOUT_PAL    0x00000002 /* Output PAL */
#define PINFO_FLAG1_VOUT_NTSC   0x00000004 /* Output NTSC */
#define PINFO_FLAG1_VOUT_VGA    0x00000006 /* Output VGA */

#ifndef BRD_INFO_DUMP	
#define BRD_INFO_DUMP(s) { \
	printf("board[%s] config info:\n", s.achName); \
 \
	printf(" |- brd_id     : 0x%x\n", s.dwBrdId); \
	printf(" |- brd_ver    : 0x%x\n", s.dwBrdVer); \
	printf(" |- pld_ver    : 0x%08x\n", s.dwPldVer); \
	printf(" |- fpga_ver   : 0x%08x\n", s.dwFpgaVer); \
	printf(" |- layer      : %d\n", s.nLayer); \
	printf(" |- slot       : %d\n", s.nSlot); \
 \
	printf(" |- cpu_num    : %d\n", s.dwCpuNum); \
	printf(" |- cpu_self_no: %d\n", s.dwCpuSelfNo); \
 \
	printf(" |- pld_num    : %d\n", s.dwPldNum); \
	printf(" |- fpga_num   : %d\n", s.dwFpgaNum); \
	printf(" |- rtc_num    : %d\n", s.wRtcNum); \
	printf(" |- eth_num    : %d\n", s.wEthNum); \
	printf(" |- e1_num     : %d\n", s.wE1Num); \
	printf(" |- v35_num    : %d\n", s.wV35Num); \
	printf(" |- serial_num : %d\n", s.wSerialNum); \
	printf(" |- fan_num    : %d\n", s.wFanNum); \
	printf(" |- led_num    : %d\n", s.wLedNum); \
	printf(" |- hwmon_num  : %d\n", s.wHwmonNum); \
}
#endif

#ifndef CPU_INFO_DUMP
#define CPU_INFO_DUMP(s) { \
	printf("cpu%d [%s] info:\n", s.dwNo, s.achName); \
	printf(" |- id        : 0x%x\n", s.dwId); \
	printf(" |- cpu_freq  : %dMHz\n", s.dwCpuFreq); \
	printf(" |- cab       : 0x%x\n", s.dwCab); \
	printf(" |- host_intf : 0x%x\n", s.dwHostIntf); \
	printf(" |- mem_size  : %dKB\n", s.dwMemSize); \
	printf(" |- mem_freq  : %dMHz\n", s.dwMemFreq); \
	printf(" |- nand_size : %dKB\n", s.dwNandSize); \
	printf(" |- nand_width: %d\n", s.dwNandWidth); \
	printf(" |- nor_size  : %dKB\n", s.dwNorSize); \
	printf(" |- nor_width : %d\n", s.dwNorWidth); \
}
#endif

#ifndef RTC_INFO_DUMP
#define RTC_INFO_DUMP(s) { \
	printf("rtc%d [%s] info:\n", s.no, s.achName); \
	printf(" |-  cab: 0x%x\n", s.dwCab); \
}
#endif

#ifndef ETH_INFO_DUMP
#define ETH_INFO_DUMP(s) { \
	printf("eth%d [%s] info:\n", s.dwNo, s.achName); \
	printf(" |- type: 0x%x\n", s.dwType); \
	printf(" |- mac : %02x:%02x:%02x:%02x:%02x:%02x\n", \
		s.abyMac[0], s.abyMac[1], \
		s.abyMac[2], s.abyMac[3], \
		s.abyMac[4], s.abyMac[5]); \
}
#endif

#ifndef SERIAL_INFO_DUMP
#define SERIAL_INFO_DUMP(s) { \
	printf("serial%d [%s] info:\n", s.dwNo, s.achName); \
	printf(" |- type  : 0x%x\n", s.dwType); \
	printf(" |- usage : 0x%x\n", s.dwUsage); \
}
#endif

#else
/* refer to kernel/driver/klsp */
#include <base/product_info.h>
#endif /* USE_KLSP_DEFINES */

/* flag operation code */
#define FL0_TST_QUERY        0x01
#define FL0_TST_SET          0x02
#define FL0_TST_CLEAR        0x03

#define FL1_OMODE_GET        0x01
#define FL1_OMODE_SET        0x02
#define FL1_VMODE_GET        0X03
#define FL1_VMODE_SET        0X04

/* product info
 * NOTE : Don`t change the struct element order. TLV format no care it, 
 *        however, ARRAY format care it.
 */
typedef struct
{
	u32 dwProtect;        /* user defined write protect flag */
	u32 dwHwId;           /* product hardware ID */
	u32 dwPid;            /* product ID */
	u32 dwHwVer;          /* product hardware version */
	u32 dwHwSubVer;       /* product hardware sub version */
	u32 dwMdate;          /* product manufacture date, such as 20131215 */
	u32 dwFlag0;          /* see also PINFO_FLAG0_TEST */
	u32 dwFlag1;          /* see also PINFO_FLAG1_CMODE */
	u32 dwTestIp;         /* Test IP address */
	u8 abyFlowid[32];     /* product pipeline coding */
	u8 abyDevsq[32];      /* device serial number */
	u8 aabyMacAddr[4][6]; /* Eth MAC Address */
	u8 abyUserData[PINFO_USERDATA_LEN + 1]; /* user defined data */
	u8 byMacNum;       /* Eth MAC number */
} TPrdInfo;

int BrdPinfoQuery(TPrdInfo *ptInfo);
int BrdPinfoClean(void);
int BrdPinfoUpdate(const TPrdInfo *info);
int BrdPinfoSetHwver(u32 hwver);
int BrdPinfoSetHwSubver(u32 dwSubVer);
int BrdPinfoSetHWID(u32 dwHwid);
int BrdPinfoSetPID(u32 dwPid);
int BrdPinfoFlag0Ops(int nOps, u32 dwArg);
int BrdPinfoFlag1Ops(int nOps, u32 dwArg);
int BrdPinfoSetUserdata(u8 *byData, int nLength);
int BrdPinfoSetIspdata(u8 *udata, int offset, int count);
int BrdPinfoGetIspdata(u8 *udata, int offset, int count);
int BrdPinfoGetHsver(u32 *data);
int BrdPinfoSetHsver(u32 hsver);
int BrdPinfoGetAccId(u32 *data);
int BrdPinfoSetAccId(u32 accid);
int BrdPinfoGetCPU(u32 *data);
int BrdPinfoSetCPU(u32 cpu);
int BrdPinfoGetSID(u32 *data);
int BrdPinfoSetSID(u32 sid);
int BrdPinfoGetHver(u32 *data);
int BrdPinfoSetHver(u32 hver);

/* board info: globle <struct brd_info board_cfg;> */
typedef struct
{
	char  achName[DRVLIB_NAME_MAX_LEN];   /* board name */

	u32   dwBrdId;     /* board id, may be = hwid of product info */
	u32   dwBrdVer;    /* board version, may be = hwver of product info */
	u32   dwPldVer;    /* EPLD/CPLD ver:D[31:24]= pld3 ... D[7:0]=pld3 */
	u32   dwFpgaVer;   /* FPGA version: D[31:24]=fpga3 ... D[7:0]=fpga0 */
	s32   nLayer;      /* < 0: no support; 0 - Max: layer ID stackable */
	s32   nSlot;       /* < 0: no support; 0 - Max: slot  ID inserted */

	u32   dwCpuNum;    /* total cpu number on board, include MCU */
	u32   dwCpuSelfNo; /* index for self-cpu: host-cpu must be 0 */

	u32   dwPldNum;    /* EPLD/CPLD number */
	u32   dwFpgaNum;   /* FPGA number */
	u16   wRtcNum;     /* Rtc number */
	u16   wEthNum;     /* Ethernet number, include Wifi */
	u16   wE1Num;      /* E1  net Interface number */
	u16   wV35Num;     /* V35 net Interface number */
	u16   wSerialNum;  /* serial number */
	u16   wFanNum;     /* Fan number */
	u16   wLedNum;     /* led number */
	u16   wButtonNum;  /* button number */
	u16   wHwmonNum;   /* hardware monitor obj number, such as temperature voltage */
	u16	  wOledNum;	 /* oled screen number */
} TBrdInfo;

/* cpu info: globle <struct cpu_info board_cpus[CFG_CPU_NUM];> */
typedef struct
{
	u32   dwNo;          /* Input: 0 ~ cpu_num-1 */
	u32   dwId;          /* see also: CPU_ID_AMBA_A5S */
	u32   dwCpuFreq;    /* in MHz */
	u32   dwCab;         /* see also: CPU_CAB_HOST_LOAD_FW */
	u32   dwHostIntf;   /* see also: CPU_HOST_INTF_LBUS */

	u32   dwMemSize;    /* such as DDR3 size, in KB */
	u32   dwMemFreq;    /* such as DDR3 freq, in MHz */

	u32   dwNandSize;   /* nand flash size, in KB; 0 = no nand */
	u32   dwNandWidth;  /* nand flash width: 8 16 32 */

	u32   dwNorSize;    /* nor flash size, in KB; 0 = no nor */
	u32   dwNorWidth;   /* nor flash width: 8 16 32 */

	char  achName[DRVLIB_NAME_MAX_LEN];
} TCpuInfo;

int BrdInfoQuery(TBrdInfo *ptInfo);
int BrdCpuInfoQuery(TCpuInfo *ptInfo);

/*
 * system infomation
 */

typedef struct
{
	u32 dwUpDays;
	u8 byUpHours;
	u8 byUpMins;
	u8 abyLoadsInt[3]; /* 1, 5, and 15 minute load averages (int portion)*/
	u8 abyLoadsFrac[3]; /* 1, 5, and 15 minute load averages (frac portion) */
	u32 dwTotalRam;
	u32 dwFreeRam;
	u32 dwProcs;
	u32 dwCached; /*cache*/
} TBrdSysInfo;

int BrdGetSysInfo(TBrdSysInfo *tInfo);

u8 BrdExtModuleIdentify(void);

#ifdef __cplusplus
}
#endif

#endif
