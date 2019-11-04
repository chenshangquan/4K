#ifndef _PART_ABI_H
#define _PART_ABI_H

#include "kdc_kernel/mtd/kdc_part.h"

extern int do_fdisk();
extern void fpga_update(char*, int);
extern void erase_fpga_space(void);
extern void fpga_set_flag(int);
extern void fpga_update(char *, int );
extern void get_fpga_info(int *, int *);
extern int fpga_cont_read(char *);
extern int get_mtd_info(char* , int* , int* );
extern int nip_do_fdisk(user_req_part_t *user_req);
extern int nip_get_part_info(user_req_part_t *user_req);

#endif
