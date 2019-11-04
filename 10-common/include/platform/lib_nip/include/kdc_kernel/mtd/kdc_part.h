#ifndef _KDC_PART_H
#define _KDC_PART_H


#define FPGA_OFFSET (1024)

#define QUIT 	-2
#define EINPUT 	-1
#define ENFP 	-1		/*Not Found Partiton table*/
#define ERFT	-2		/*read partition table error*/

#define MAX_NAME_LEN 16
#define MAX_TYPE 3


/* define partition name */
#define BOOT_MTD_NAME	"BOOT"
#define IOS_MTD_NAME	"IOS"
#define APP_MTD_NAME	"APP"
#define PART_MTD_NAME	"PART_TABLE"
#define JFFS2_MTD_NAME	"JFFS2"
/* Notice: USER_NAME is USER0 USER1 ... */
#if 0
/* IOS head defines
 */
#define IOS_HEAD_LEN	0x40
/* ios head string format 
 *  "KERNEL_START:KERNEL_SIZE:RAMFS_START:RAMFS_SIZE"
 */
#define IOS_HEAD_STRING	"0x%x:0x%x:0x%x:0x%x"
#else
#define LINUX_IMAGE 0x80000000         
#define LINUX_UPDATE_FLAG  	"linux_updata"
#endif
/*-----------------------------------------------------------------------
*  kdc_part info
*/

/*define FDISK MAGIC*/
#define KDC_PART_MAGIC	 0x20060309

#define MAX_PART_NUM 0x8

/*-----------------------------------------------------------------------
*   filesystem type
*/
#define BINARY 	0x1
#define JFFS2	0x2

/*-----------------------------------------------------------------------
*   purpose type
*/
#define IOS			0x1
#define USER		0x2
#define JFFS  		0x4
#define BOOT		0x8
#define PART_TABLE	0x10
#define APP			0x20

/*-----------------------------------------------------------------------
*   parititon flag
*/
#define VISIBLE	0x1
#define USED 	0x2
#define CREATE	0x4


struct mtd_number_struct
{
	int number;
	int usr_num;
};


typedef struct part_head_struct 
{
	int magic;		/*partition table identifier*/
	short part_number;		/*partition number*/
	short usr_number;		/*user partition number*/
	int fpga;			/*fpga flags*/
	int fpga_start;   /*fpga start address*/
	int fpga_size;	/*fpga size*/
	char* fpga_buf;	/*fpga content*/
} __attribute__((aligned(32)))  part_head_t;

/*partitoin struct in disk*/
typedef struct d_part_entry_struct
{
	char type;			/*partition type J:jffs2 B:binary*/
	char purpose;			/*partition purpose IOS,USR*/
	short flag;			/*partition attribution*/
	int offset;			/*partition offset from head of flash*/
	int size;				/*partiton size*/
	int data_size;		/*size of content of partion*/
	char name[MAX_NAME_LEN];
}d_part_entry_t;

/*partiton struct in memory*/
typedef struct part_entry_struct
{
	unsigned char type;			/*partition type J:jffs2 B:binary*/
	unsigned char purpose;		
	short flag;			/*partition attribution*/
	int offset;			/*partition offset from head of flash*/
	int size;				/*partiton size*/
	int data_size;		/*size of content of partion*/
	char name[MAX_NAME_LEN];
	struct part_entry_struct* prev;
	struct part_entry_struct* next;
}part_entry_t;

/*partition table which modified by user*/
typedef struct part_struct
{
	part_head_t part_table_head;
	part_entry_t* part_entry_head;
	int purpose_mask;
	int free_space;
	int dirty; 	
	void (*erase)(part_entry_t*);			/*erase part routine*/
	int (*get_part_info)(struct part_struct*, part_entry_t*, int*);		/*get parition info accroding to name*/
	int (*get_usr_num)(struct part_struct*, int*);
	int (*set_part_info)(struct part_struct*, part_entry_t*, int);
	void (*erase_fpga_space)(struct part_struct*);
	void (*fpga_set_flag)(struct part_struct*, int size);
	int (*fpga_update)(struct part_struct*, char *, int);
	void (*get_fpga_info)(struct part_struct*, int *, int *);
	int (*fpga_cont_read)(struct part_struct*, char *);
	void* priv;
}part_t;


typedef struct kdc_part_info_s {
		part_head_t part_table_head;
		part_entry_t part_entry_head[MAX_PART_NUM];
}kdc_part_info_t;


typedef 	struct kdc_part_mtd_s {
		int number;
		part_entry_t* part_entry_head;
}kdc_part_mtd_t;

#define MEMCONST		_IOW('M', 13, part_entry_t*)
#define MEMDEFNUM		_IOW('M', 14, int*)
#define MEMDEFPART		_IOW('M', 15, kdc_part_mtd_t*)

#ifndef __KERNEL__
typedef struct cmd_node_struct
{
	char* name;
	int (*handle)(part_t*);		/*collect parmeters for current command*/
	char* info;			/*current command information*/
}cmd_node_t;

#define ALIGN(p, a) ((int)(((int)(p)+(a)-1) & ~((int)(a)-1)))

typedef struct req_part_s
{
	part_entry_t part_entry[MAX_PART_NUM];
	int def;
	int number;
}req_part_t;

typedef struct user_part_info {
	int part_type;
	int part_size;
	char part_name[MAX_NAME_LEN];
}user_part_info_t;

typedef struct user_req_part {
	int usedefcof;
	int ramdisk_size;
	user_part_info_t part_info[MAX_PART_NUM];
}user_req_part_t;

extern int load_partition_table(part_t*);
extern int unload_partition_table(part_t**);
extern int do_cmd(char*, part_t*);
extern int user_change_partition(part_t *, user_req_part_t *);
#endif

#endif


