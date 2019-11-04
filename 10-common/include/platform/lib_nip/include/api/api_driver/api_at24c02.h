#ifndef __AT24C02_HEAD_H__
#define __AT24C02_HEAD_H__

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

int nip_read_at24c02(struct at24c02_info *pinfo);
int nip_write_at24c02(const char *filename);

#endif

