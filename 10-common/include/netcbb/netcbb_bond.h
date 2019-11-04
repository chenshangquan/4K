#ifndef _NETCBB_BOND_H_
#define _NETCBB_BOND_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "netcbb_def.h"

/* bond模式 */
#define BOND_MODE_ROUNDROBIN    0
#define BOND_MODE_ACTIVEBACKUP  1
#define BOND_MODE_XOR           2
#define BOND_MODE_BROADCAST     3
#define BOND_MODE_8023AD        4
#define BOND_MODE_TLB           5
#define BOND_MODE_ALB           6  /* TLB + RLB (receive load balancing) */



struct BondParam
{
	u32 adwBondId[MAX_NIC_NUM]; /* 需要绑定的网卡id列表 */
	u32 dwBondIdNum;            /* 需要绑定的网卡id个数 */
	u32 dwActiveId;             /* bond中优先使用的网卡id */
	char *pchBondPath;          /* bond.ko的路径，如/lib/module */
};

/************************************************************
 * 函数名 : NetBondStart
 *
 * 功能 : 开启bond模式
 *
 * 描述 :
 *     1.目前hisi仅支持BOND_MODE_ACTIVEBACKUP模式.
 *     2.如果成功，则系统总是有bond0虚拟接口，后续调用其他所有接口传入的id，
 *       均代表操作的bond0, 无法操作eth0.
 *
 *
 * 参数说明 :
 *          dwBondMode    - bond模式(BOND_MODE_ROUNDROBIN等)
 *          ptBondParam   - bond模式参数
 *
 *
 * 返回值 : ID    - 绑定的网卡ID
 *          ERROR - 失败
 *          NET_BOND_HAS_STARTED - bond已经启动(如果需要切换模式，请先stop)
 ***********************************************************/
s32 NetBondStart(u32 dwBondMode, struct BondParam *ptBondParam);

/************************************************************
 * 函数名 : NetBondStop
 *
 * 功能 : 停止bond模式
 *
 * 描述 :
 *
 * 参数说明 :
 *
 *
 * 返回值 : OK    - 成功
 *          ERROR - 失败
 ***********************************************************/
s32 NetBondStop();


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
