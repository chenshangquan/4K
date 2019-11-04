/*
 * Kedacom Hardware Abstract Level
 *
 * src/dspcci/pcie_fifo/pciefifo.h
 *
 * Communicate on pcie:
 * Support user to communicate by pcie...
 *
 * Copyright (C) 2013-2020, Kedacom, Inc.
 *
 * History:
 *   2016/10/20 - [yuanzengxing] Create
 *
 */
#ifndef __PCIEFIFO_EP_H
#define __PCIEFIFO_EP_H

#ifdef __cplusplus
extern "C" {
#endif


#include <stdlib.h>
#include "dspcci_common.h"

/* device info */
#define PCIE_FIFO_DEV_NAME       "/dev/pcie_fifo"

#define PCIE_FIFO_MAX_MSG_LEN    0x10000
#define PCIE_FIFO_MAX_BUF_LEN    0xA00000

#define PCIE_TYPE_RC             1
#define PCIE_TYPE_EP             2

/*
 * ioctl cmd defines
 */
#define PCIE_FIFO_EP_IOC             'S'
#define PCIE_FIFO_EP_IOC_WAIT_MSG    _IOW (PCIE_FIFO_EP_IOC, 0x1, u32)
#define PCIE_FIFO_EP_IOC_SET_IRQ     _IO  (PCIE_FIFO_EP_IOC, 0x2)
#define PCIE_FIFO_EP_IOC_GET_REGION  _IOR (PCIE_FIFO_EP_IOC, 0x3, struct pcie_region_info_s)

/*
 * region info
 */
struct pcie_region_info_s {
	u32 mamage_buf_len;
	u32 data_buf_len;
	u32 mem_base;
	u32 pcie_type;
};

/*
 * channle control info struct
 */
typedef struct{
	/* read pointer offset */
	volatile u32 dwReadPtr;
	/* write pointer offset */
	volatile u32 dwWritePtr;
	/* write message num */
	volatile u32 dwWriteNum;
	/* read message num */
	volatile u32 dwReadNum;
	/* next revice msg address */
	volatile u32 dwNextRcvMsgPtr;
	/* Rx/Tx message num */
	volatile u32 dwDspRxTxMsgs;
	/* Rx/Tx message num*/
	volatile u32 dwDspRxErrOrTxOkMsgs;
	/* Rx/Tx message Kbytes */
	volatile u32 dwDspRxTxKBytes;
	/* Rx/Tx message Bytes */
	volatile u32 dwDspRxTxBytes;
	/* inital management info */
	volatile u32 dwInitiFlags;
}
TPcieCciChnlInfo;

s32 PcieFifoOpen(void);
s32 PcieFifoClose(void);
s32 PcieFifoWriteMsg(u32 dwChnl, TDspCciMsgDesc *ptMsgDesc);
s32 PcieFifoReadMsg(u32 dwChnl, u8 *pbyBuf, u32 *pdwSize, s32 nTimeout);
s32 PcieFifoClearDnChnl(u32 dwChnl);
s32 PcieFifoGetRxMsgNum(u32 dwChnl, u32 *pdwMsgNum);
void PcieFifoDumpInfo(void);
void PcieFifoCleanChannel(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __PCIEFIFO_EP_H */
