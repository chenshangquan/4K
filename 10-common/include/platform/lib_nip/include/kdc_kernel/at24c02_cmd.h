#ifndef __AT24C02_HEAD_H__
#define __AT24C02_HEAD_H__

/* debug: */
typedef struct at24c02_info{
	int protect_flag;
	int device_type;
	int hardware_version;
	char device_serial[11];
	char product_date[9];
	char flow_code[7];
	int mac_total;
	char mac_address[6][6];
}at24c02_info_t;

int get_hw_info(struct at24c02_info  *info, u8 c_addr);
int get_hw_version(void);
int get_device_type(void);

#endif

