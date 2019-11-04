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
 * 2006-8-25 luchen write first.
 */
#ifndef API_HDISK_H
#define API_HDISK_H

/* flag bitmap */
#define FROMATED 0x1

/* for IDE harddisk api */
#define MASTER	0   // master harddisk 
#define SLAVE	1   // slave harddisk 
#define MAX_HDISK_MODEL_LEN		64
#define MAX_HDISK_DEV_NAME_LEN	64
#define MAX_HDISK_PARTITION_NUM	4
#define MAX_MNT_DIRECTORY_PATH	64

struct hdisk_info{
	char exist; 	// hardisk exist flag: 1-valid, 0-unvalid
	char hdisk_model[MAX_HDISK_MODEL_LEN];			// harddisk model
	char hdisk_dev_name[MAX_HDISK_DEV_NAME_LEN];	// device name of harddisk  
	unsigned long hdisk_capacity;					// capacity of harddisk
};

struct single_partition_info{
	/* 
	 * flags bitmap, now reserved  
	 * bit 0: when equal to one means partition has been formated. 
	 */
	char flags;
	int sequence;								// the sequence of partition
	unsigned long hpart_capacity;				// capacity of harddisk partition
	char hpart_dev_name[MAX_HDISK_DEV_NAME_LEN];// device name of harddisk partition 
};

struct hd_part_info{
	/* 
	 * the number of disk partitions: 
	 * -1 means no partitions, 0 means 1 partition existed, etc.
	 */
	int partition_num; 
	/*
	 * information of every valid partition in the harddisk
	 */
	struct single_partition_info part_info[MAX_HDISK_PARTITION_NUM];
};

int nip_get_hdisk_info(int, int, struct hdisk_info *);
int nip_get_hdpart_info(char *, struct hd_part_info *);
int nip_mount_hdpart(char *, char *);
int nip_get_hdpart_fcapa(char *, unsigned long *);
int nip_umount_hdpart(char * hdpart_name);

#endif	/* API_HDISK_H */

