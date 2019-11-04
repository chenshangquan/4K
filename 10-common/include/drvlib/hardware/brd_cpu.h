/*
 * CPU Common Defines
 *
 * brd_cpu.h
 *
 * Copyright (C) 2013-2020, Kedacom, Inc.
 *
 * History:
 *   2013/05/07 - [zhangfm] Create
 *   2017/08/14 - [gulidong] Remove from klsp to here
 *
 */

#ifndef __CPU_DEFS_H
#define __CPU_DEFS_H


/*
 * cpu identify defines
 * use u32 type variable
 *   D[31:16]: CPU type
 *        |- D[31:25]: CPU vender, max 128
 *        |- D[24:16]: CPU device, max 512
 *   D[15: 8]: core number for each CPU type
 *   D[ 7: 0]: index for each CPU type
 */
#define CPU_NO_SHIFT          0
#define CPU_NO_MASK           0xff
#define CPU_NO(v)             (((v) >> CPU_NO_SHIFT) & CPU_NO_MASK)

#define CPU_CORE_SHIFT        8
#define CPU_CORE_MASK         0xff
#define CPU_CORE(v)           (((v) >> CPU_CORE_SHIFT) & CPU_CORE_MASK)

/* vender */
#define CPU_VEND_SHIFT        25
#define CPU_VEND_MASK         0x7f
#define CPU_VEND(v)           (((v) >> CPU_VEND_SHIFT) & CPU_VEND_MASK)

#define CPU_VEND_UNKNOWN      0x00 /* unknown */
#define CPU_VEND_NXP          0x01 /* NXP */
#define CPU_VEND_ATMEL        0x02 /* ATMEL */
#define CPU_VEND_FSC          0x03 /* freescale */
#define CPU_VEND_AMBA         0x04 /* Ambarella */
#define CPU_VEND_TI           0x05 /* Ti */
#define CPU_VEND_INTEL        0x06 /* INTEL */
#define CPU_VEND_HISI         0x07 /* hisilicon */

/* type */
#define CPU_TYPE_SHIFT        16
#define CPU_TYPE_MASK         0xffff
#define CPU_TYPE(v)           (((v) >> CPU_TYPE_SHIFT) & CPU_TYPE_MASK)

#define CPU_TYPE_NXP_UNKNOWN  (0x000 | (CPU_VEND_NXP << \
                                        (CPU_VEND_SHIFT - CPU_TYPE_SHIFT)))
#define CPU_TYPE_NXP_LPC2368  (0x001 | (CPU_VEND_NXP << \
                                        (CPU_VEND_SHIFT - CPU_TYPE_SHIFT)))

#define CPU_TYPE_FSC_UNKNOWN  (0x000 | (CPU_VEND_FSC << \
                                        (CPU_VEND_SHIFT - CPU_TYPE_SHIFT)))
#define CPU_TYPE_FSC_860      (0x001 | (CPU_VEND_FSC << \
                                        (CPU_VEND_SHIFT - CPU_TYPE_SHIFT)))
#define CPU_TYPE_FSC_8260     (0x002 | (CPU_VEND_FSC << \
                                        (CPU_VEND_SHIFT - CPU_TYPE_SHIFT)))
#define CPU_TYPE_FSC_P2020     (0x003 | (CPU_VEND_FSC << \
                                        (CPU_VEND_SHIFT - CPU_TYPE_SHIFT)))

#define CPU_TYPE_AMBA_UNKNOWN (0x000 | (CPU_VEND_AMBA << \
                                        (CPU_VEND_SHIFT - CPU_TYPE_SHIFT)))
#define CPU_TYPE_AMBA_A5S     (0x001 | (CPU_VEND_AMBA << \
                                        (CPU_VEND_SHIFT - CPU_TYPE_SHIFT)))
#define CPU_TYPE_AMBA_S2      (0x002 | (CPU_VEND_AMBA << \
                                        (CPU_VEND_SHIFT - CPU_TYPE_SHIFT)))
#define CPU_TYPE_AMBA_S2L     (0x003 | (CPU_VEND_AMBA << \
                                        (CPU_VEND_SHIFT - CPU_TYPE_SHIFT)))
#define CPU_TYPE_TI_UNKNOWN   (0x000 | (CPU_VEND_TI << \
                                        (CPU_VEND_SHIFT - CPU_TYPE_SHIFT)))
#define CPU_TYPE_TI_DM642     (0x001 | (CPU_VEND_TI << \
                                        (CPU_VEND_SHIFT - CPU_TYPE_SHIFT)))
#define CPU_TYPE_TI_DM647     (0x002 | (CPU_VEND_TI << \
                                        (CPU_VEND_SHIFT - CPU_TYPE_SHIFT)))
#define CPU_TYPE_TI_DM6437    (0x003 | (CPU_VEND_TI << \
                                        (CPU_VEND_SHIFT - CPU_TYPE_SHIFT)))
#define CPU_TYPE_TI_DM365     (0x004 | (CPU_VEND_TI << \
                                        (CPU_VEND_SHIFT - CPU_TYPE_SHIFT)))
#define CPU_TYPE_TI_DM368     (0x005 | (CPU_VEND_TI << \
                                        (CPU_VEND_SHIFT - CPU_TYPE_SHIFT)))
#define CPU_TYPE_TI_DM8168    (0x006 | (CPU_VEND_TI << \
                                        (CPU_VEND_SHIFT - CPU_TYPE_SHIFT)))
#define CPU_TYPE_TI_DM8148    (0x007 | (CPU_VEND_TI << \
                                        (CPU_VEND_SHIFT - CPU_TYPE_SHIFT)))
#define CPU_TYPE_TI_DM8127    (0x008 | (CPU_VEND_TI << \
                                        (CPU_VEND_SHIFT - CPU_TYPE_SHIFT)))
#define CPU_TYPE_TI_DM8107    (0x009 | (CPU_VEND_TI << \
                                        (CPU_VEND_SHIFT - CPU_TYPE_SHIFT)))
#define CPU_TYPE_TI_DM6678    (0x00a | (CPU_VEND_TI << \
                                        (CPU_VEND_SHIFT - CPU_TYPE_SHIFT)))
#define CPU_TYPE_TI_DM6672    (0x00b | (CPU_VEND_TI << \
                                        (CPU_VEND_SHIFT - CPU_TYPE_SHIFT)))
#define CPU_TYPE_TI_AM1808    (0x00c | (CPU_VEND_TI << \
                                        (CPU_VEND_SHIFT - CPU_TYPE_SHIFT)))
#define CPU_TYPE_TI_AM5728    (0x00d | (CPU_VEND_TI << \
											(CPU_VEND_SHIFT - CPU_TYPE_SHIFT)))

#define CPU_TYPE_INTEL_UNKNOWN (0x000 | (CPU_VEND_INTEL << \
                                        (CPU_VEND_SHIFT - CPU_TYPE_SHIFT)))
#define CPU_TYPE_INTEL_i7_3770 (0x001 | (CPU_VEND_INTEL << \
                                        (CPU_VEND_SHIFT - CPU_TYPE_SHIFT)))

#define CPU_TYPE_INTEL_BAYTRAIL (0x002 | (CPU_VEND_INTEL << \
                                        (CPU_VEND_SHIFT - CPU_TYPE_SHIFT)))

#define CPU_TYPE_HIS_UNKNOWN   (0x000 | (CPU_VEND_HISI << \
                                      (CPU_VEND_SHIFT - CPU_TYPE_SHIFT)))
#define CPU_TYPE_HIS_HI3520D   (0x001 | (CPU_VEND_HISI << \
                                      (CPU_VEND_SHIFT - CPU_TYPE_SHIFT)))
#define CPU_TYPE_HIS_HI3535     (0x002 | (CPU_VEND_HISI << \
                                      (CPU_VEND_SHIFT - CPU_TYPE_SHIFT)))
#define CPU_TYPE_HIS_HI3518    (0x003 | (CPU_VEND_HISI << \
                                      (CPU_VEND_SHIFT - CPU_TYPE_SHIFT)))
#define CPU_TYPE_HIS_HI3516A   (0x004 | (CPU_VEND_HISI << \
                                              (CPU_VEND_SHIFT - CPU_TYPE_SHIFT)))
#define CPU_TYPE_HIS_HI3536   (0x005 | (CPU_VEND_HISI << \
                                              (CPU_VEND_SHIFT - CPU_TYPE_SHIFT)))
#define CPU_TYPE_HIS_HI3519   (0x006 | (CPU_VEND_HISI << \
                                              (CPU_VEND_SHIFT - CPU_TYPE_SHIFT)))
#define CPU_TYPE_HIS_HI3516C   (0x007 | (CPU_VEND_HISI << \
                                              (CPU_VEND_SHIFT - CPU_TYPE_SHIFT)))
#define CPU_TYPE_HIS_HI3516D   (0x008 | (CPU_VEND_HISI << \
                                    (CPU_VEND_SHIFT - CPU_TYPE_SHIFT)))

#define CPU_NAME_NXP_UNKNOWN  "NXP_UNKNOWN"
#define CPU_NAME_NXP_LPC2368  "NXP_LPC2368"

#define CPU_NAME_FSC_UNKNOWN  "FSC_UNKNOWN"
#define CPU_NAME_FSC_860      "FSC_860"
#define CPU_NAME_FSC_8260     "FSC_8260"
#define CPU_NAME_FSC_P2020	"FSC_P2020"

#define CPU_NAME_AMBA_UNKNOWN "AMBA_UNKNOWN"
#define CPU_NAME_AMBA_A5S     "AMBA_A5S"
#define CPU_NAME_AMBA_S2      "AMBA_S2"

#define CPU_NAME_TI_UNKNOWN   "TI_UNKNOWN"
#define CPU_NAME_TI_DM642     "TI_DM642"
#define CPU_NAME_TI_DM647     "TI_DM647"
#define CPU_NAME_TI_DM6437    "TI_DM6437"
#define CPU_NAME_TI_DM365     "TI_DM365"
#define CPU_NAME_TI_DM368     "TI_DM368"
#define CPU_NAME_TI_DM8168    "TI_DM8168"
#define CPU_NAME_TI_DM8148    "TI_DM8148"
#define CPU_NAME_TI_DM8127    "TI_DM8127"
#define CPU_NAME_TI_DM8107    "TI_DM8107"
#define CPU_NAME_TI_DM6678    "TI_DM6678"
#define CPU_NAME_TI_DM6672    "TI_DM6672"
#define CPU_NAME_TI_AM1808	  "TI_AM1808"
#define CPU_NAME_TI_AM5728	  "TI_AM5728"

#define CPU_NAME_INTEL_UNKNOWN "INTEL_UNKNOWN"
#define CPU_NAME_INTEL_i7_3770 "i7-3770"
#define CPU_NAME_INTEL_BAYTRAIL "INTEL_BAYTRAIL"

#define CPU_NAME_HIS_HI3518   "HI3518"
#define CPU_NAME_HIS_HI3520D  "HI3520D"
#define CPU_NAME_HIS_HI3535   "HI3535"
#define CPU_NAME_HIS_HI3516A  "HI3516A"
#define CPU_NAME_HIS_HI3536   "HI3536"
#define CPU_NAME_HIS_HI3519   "HI3519V101"
#define CPU_NAME_HIS_HI3516C   "HI3516CV300"
/* ID defines */
#define CPU_ID(type, core, no) \
	(((type) << CPU_TYPE_SHIFT) | \
	 ((core) << CPU_CORE_SHIFT) | \
	 ((no)   << CPU_NO_SHIFT))

#define CPU_ID_NXP_LPC2368(n)    CPU_ID(CPU_TYPE_NXP_LPC2368, 1, n)

#define CPU_ID_FSC_860(n)        CPU_ID(CPU_TYPE_FSC_860, 1, n)
#define CPU_ID_FSC_8260(n)       CPU_ID(CPU_TYPE_FSC_8260, 1, n)

#define CPU_ID_AMBA_A5S(n)       CPU_ID(CPU_TYPE_AMBA_A5S, 1, n)
#define CPU_ID_AMBA_S2(n)        CPU_ID(CPU_TYPE_AMBA_S2, 2, n)
#define CPU_ID_AMBA_S2L(n)       CPU_ID(CPU_TYPE_AMBA_S2L, 3, n)

#define CPU_ID_TI_DM642(n)       CPU_ID(CPU_TYPE_TI_DM642, 1, n)
#define CPU_ID_TI_DM647(n)       CPU_ID(CPU_TYPE_TI_DM647, 1, n)
#define CPU_ID_TI_DM6437(n)      CPU_ID(CPU_TYPE_TI_DM6437, 1, n)
#define CPU_ID_TI_DM365(n)       CPU_ID(CPU_TYPE_TI_DM365, 1, n)
#define CPU_ID_TI_DM368(n)       CPU_ID(CPU_TYPE_TI_DM368, 1, n)
#define CPU_ID_TI_DM8168(n)      CPU_ID(CPU_TYPE_TI_DM8168, 1, n)
#define CPU_ID_TI_DM8148(n)      CPU_ID(CPU_TYPE_TI_DM8148, 1, n)
#define CPU_ID_TI_DM8127(n)      CPU_ID(CPU_TYPE_TI_DM8127, 1, n)
#define CPU_ID_TI_DM8107(n)      CPU_ID(CPU_TYPE_TI_DM8107, 1, n)
#define CPU_ID_TI_DM6678(n)      CPU_ID(CPU_TYPE_TI_DM6678, 8, n)
#define CPU_ID_TI_DM6672(n)      CPU_ID(CPU_TYPE_TI_DM6672, 2, n)
#define CPU_ID_TI_AM1808(n)    	 CPU_ID(CPU_TYPE_TI_AM1808, 1, n)
#define CPU_ID_TI_AM5728(n)    	 CPU_ID(CPU_TYPE_TI_AM5728, 2, n)

#define CPU_ID_INTEL_i7_3770(n)  CPU_ID(CPU_TYPE_INTEL_i7_3770, 8, n)
#define CPU_ID_INTEL_BAYTRAIL(n)  CPU_ID(CPU_TYPE_INTEL_BAYTRAIL, 4, n)

#define CPU_ID_HIS_HI3518(n)     CPU_ID(CPU_TYPE_HIS_HI3518, 1, n)
#define CPU_ID_HIS_HI3520D(n)    CPU_ID(CPU_TYPE_HIS_HI3520D, 1, n)
#define CPU_ID_HIS_HI3535(n)     CPU_ID(CPU_TYPE_HIS_HI3535, 2, n)
#define CPU_ID_HIS_HI3516A(n)    CPU_ID(CPU_TYPE_HIS_HI3516A, 1, n)
#define CPU_ID_HIS_HI3516D(n)    CPU_ID(CPU_TYPE_HIS_HI3516D, 1, n)
#define CPU_ID_HIS_HI3536(n)     CPU_ID(CPU_TYPE_HIS_HI3536, 4, n)
#define CPU_ID_HIS_HI3519(n)     CPU_ID(CPU_TYPE_HIS_HI3519, 4, n)
#define CPU_ID_HIS_HI3516C(n)     CPU_ID(CPU_TYPE_HIS_HI3516C, 1, n)
/* cpu capability mask */
#define CPU_CAB_HOST_LOAD_FW  0x00000001 /* firmware can be load by host-cpu */

/* connect with host-cpu interface: bus + driver */
#define CPU_HOST_INTF_BUS_MASK      0x000000ff
#define CPU_HOST_INTF_NONE          0x00000000
#define CPU_HOST_INTF_UART          0x00000001
#define CPU_HOST_INTF_PCI           0x00000002
#define CPU_HOST_INTF_HPI           0x00000003
#define CPU_HOST_INTF_SPI           0x00000004
#define CPU_HOST_INTF_IIC           0x00000005
#define CPU_HOST_INTF_LBUS          0x00000006 /* local bus */
#define CPU_HOST_INTF_FPGA_FIFO     0x00000007 /* host <-> fpga(fifo) <-> dsp */

#define CPU_HOST_INTF_DRV_MASK      0x00ff0000
#define CPU_HOST_INTF_DRV_DSPCCI    0x00010000 /* use dspcci driver */

#endif /* #ifndef __CPU_DEFS_H */
