#ifndef _RAW_FLASH_H
#define _RAW_FLASH_H

#include "kdc_kernel/mtd/mtd-user.h"
#include "kdc_kernel/mtd/mtd-abi.h"
#include "kdc_kernel/mtd/kdc_part.h"


#ifdef DEBUG
#define debug(fmt,args...)      printf (fmt ,##args)
#else
#define debug(fmt,args...)
#endif

/*flash operator command*/
#define MTD_LOCK 0
#define MTD_UNLOCK 1
#define MTD_UPDATE 2
#define MTD_READ 3
#define MTD_ERASE 4
#define MTD_WRITE 5

#define MTD_CMD_NUM 6

#define LOCK 0
#define UNLOCK 1

extern int read_flash(char*,char*,int);
extern int update_flash(char*,char*);
extern int lock_flash(int,char*);
extern int erase_flash(char*);
extern int write_flash(char*, char*, int, int);
extern int get_default_partnum(int*, int*);
extern int get_default_part(part_entry_t*, int);
extern int mnt_mtd(part_t*);
extern int erase_flash(char*);
extern int update_write(char*,char*);
extern int get_mtd_info_user(struct mtd_info_user *mtd_info);
extern int get_mtd_index_by_name(char *name, int *mtd);
extern void mark_jffs2_magic(char *mtdname);
#endif


