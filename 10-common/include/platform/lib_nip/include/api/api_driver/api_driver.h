/* api_driver.h -
 *
 * Copyright 2005-2008 suzhou Keda co.
 *
 * description :
 * -------------------------
 * Purpose: for nip api.
 *
 * modification history
 * -------------------------
 * 2006-1-10 zhangyan write first.
 */
#ifndef API_DRIVER_H
#define API_DRIVER_H

/* for IDE hard disk api */
#include "api/api_driver/api_hdisk.h"

/* for RS485 api */
int nip_driver_rs485_get_txsts(int fd, int * mode);
int nip_driver_rs485_set_rxtx(int fd, int mode);
int nip_driver_rs485_set_auto(int fd, int timer, int rate, int timeout);

/* for rawflash api */
#include "api/api_driver/api_rawflash.h"
#include "api/api_driver/part_abi.h"
int copy_to_app_part(char *src, char *dst);
int update_appimage(char *srcfile);
int update_appimage_from_tftpser(char* filename, char *ip_str);

int iosupdate(char* name);
int update_ios_from_tftpser(char* filename, char *ip_str);
int iosupdate_from_mem(char *buffer, int buflen);

/* for RTC api */
int nip_rtc_to_sys_clock(void);
int nip_rtc_from_sys_clock(void);



/* for hardware info api */
#define MAX_CPU_NAME 128
#define MAX_UBOOT_INFO 64
#define MAX_KERNEL_INFO 128
#define NIP_GET_HARDWARE_INFO		NIP_DRV_BASE + 1

struct hwinfo_getback{
	int  ret;

	char cpuinfo[MAX_CPU_NAME];
	char binfo[MAX_UBOOT_INFO];
	char kinfo[MAX_KERNEL_INFO];
	
	long memory_size;
	long flash_size;
	long cpu_frequency;
	long cpm_frequency;
	long bus_frequency;
	
	int eth_num;
  	int v35_num;
 	int e1_num;	
};

extern int nip_get_hwinfo(struct hwinfo_getback *);
extern void nip_api_info_register();

/* for e2prom: at24c02 */
#include "api/api_driver/api_at24c02.h"


/* For I2C */
extern int api_i2c_read(unsigned char chip_addr, unsigned reg_addr, char *buf, int len);
extern int api_i2c_write(unsigned char chip_addr, unsigned reg_addr, const char *buf, int len);


#endif	/* API_DRIVER_H */

