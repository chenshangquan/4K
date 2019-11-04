
/*
 *  ======== IpcSupport.h ========
 *
 */

/* coreId */
#define IPC_CORE_DSP            0
#define IPC_CORE_M3_VIDEO       1
#define IPC_CORE_M3_HDVPSS      2
#define IPC_CORE_A8             3
#define IPC_CORE_MAX            4


int NetraProcOpen( unsigned short coreId, char *filePath);
int NetraProcClose(unsigned short coreId);
