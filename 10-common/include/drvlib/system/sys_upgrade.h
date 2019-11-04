/*
 * Kedacom Hardware Abstract Level
 *
 * sys_upgrade.h
 *
 * Copyright (C) 2013-2020, Kedacom, Inc.
 *
 * History:
 *   2013/09/22 - [xuliqin] Create
 *
 */

#ifndef _SYS_UPGRADE_H
#define _SYS_UPGRADE_H

#include <drvlib_def.h>

#ifdef __cplusplus
extern "C" {
#endif

#define UGR_CHECK_ONLY  0x1  /* do package validity check only */
#define UGR_REBOOT_AUTO 0x2  /* auto reboot after upgrade */

/*
 * Master system upgrade calls
 */

int SysUpgradeDev(const char *szFileName, u32 nFlags);
int SysUpgradeCleanEnv(void);
int SysUpgradeReport(u32 *pdwReport);
int SysUpgradeGetVerbose(const char *szFileName, u8 *pchVerbose);
int SysSwitchSystem(int nSysId);
int SysUpgradeScm(u32 dwDevId, const char *szFileName);
int SysUpgradeCam(u32 devId, const char *fileName);

/*
 * FPGAs calls
 */

int SysLoadFpga(int nForce, const char *szFilenName);
int SysProgramFpga(const char *byData, int nLength, int nInProgress);

/*
 * For backup system
 */

/*
 * backup part.
 */
#define BACKUP_IOS	0x1	/* update.linux or zImage+ramdisk */
#define BACKUP_APP	0x2	/* app.img */
#define BACKUP_ALL	0x3	/* IOS+APP */

int SysBackUp(u32 part);

#define NORMAL		(0)
#define ABNORMAL	(-1)

/*
*Get the pair partition stat
*Return Vaule:
*     NORMAL(0) the pair partition's version is ok,it can run.
*     ABNORMAL(-1) the pair parition's version is fail,it can't run.
*
*/
int SysGetPPStat(void);

/*
*Disable the Backup capability.

*the system will not backup if the system can't run
*Return Value:
	0:	Succ
	-1:	Fail
*/

int SysDisableBackUp(void);

/*
 * Enable the recover capability.
 * 	the system will not recover if the system can't run when disable.
 * 	Default is enable in system.
 *
 * @param:
 * 	0 : disable
 * 	1 : enable
 *
 * @Return Value:
 *	0:	Succ
 *	-1:	Fail
 */

int SysEnableRecover(int enable);

#ifdef __cplusplus
}
#endif

#endif
