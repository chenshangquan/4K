#ifndef __NIPDEBUG_KERNEL_H__
#define __NIPDEBUG_KERNEL_H__
/*
 * auth: wangyuantao@kedacom.com
 * date: Wed Oct 11 10:36:21 CST 2006
 */

#define DEBUGMISC_MINOR			199	/* for NIP Debug */

#define DEBUGMISC_FILENAME "/dev/debugmisc"	/* 设备文件名 */

#define KERNEL_DATA_MODE_INVALID	0
#define KERNEL_DATA_MODE_READ		1	/* 读取数据 */
#define KERNEL_DATA_MODE_WRITE		2	/* 写入数据 */

#define KERNEL_DATA_ATTR_INVALID	0
#define KERNEL_DATA_ATTR_PHYS		1	/* 物理地址 */
#define KERNEL_DATA_ATTR_VIRT		2	/* 虚拟地址 */
#define KERNEL_DATA_ATTR_REG		3	/* 寄存器地址 */

#define DEBUG_KERNEL_RWDATA		1	/* ioctl使用方式：修改查看内核数据 */
#define DEBUG_KERNEL_DATA_TYPE		2	/* 检查数据属性 */
#define DEBUG_KERNEL_CALL		3	/* 执行内核函数 */
#define DEBUG_KERNEL_BACKTRACE		4	/* 打印线程内核栈 */

typedef void (*func_param0)(void);
typedef void (*func_param1)(int t1);
typedef void (*func_param2)(int t1, int t2);

/* 需要调用内核函数时，传递给内核的数据结构 */
typedef struct kernelcall{
	int addr;				/* 函数地址 */
	int paramcount;				/* 参数个数，参数都是整形的 */
	int param1;				/* 参数1 */
	int param2;				/* 参数1 */
}kernelcall_t;

/*需要读取修改内核数据时，传递给内核的数据结构 */
typedef struct kerneldata{
	int mode;				/* 读取数据还是 修改数据 */
	int attribute;				/* 地址类型 */
	int addr;				/* 内核数据起始地址 */
	int len;				/* 数据长度 */
	char *buf;				/* 数据缓冲区 */
}kerneldata_t;

/* 打印线程的内核调用栈 */
typedef struct kernelstack{
	int pid;				/* 线程id */
}kernelstack_t;

/* 取得地址类型 */
typedef struct kerneldatatype{
	int addr;				/* 内核地址 */
	int type;				/* 返回的地址类型 */
	int virt_addr;				/* 返回的虚拟地址或物理地址 */
	int phy_addr;
}kerneldatatype_t;

#endif

