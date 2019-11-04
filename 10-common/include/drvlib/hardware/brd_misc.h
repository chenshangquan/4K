/*
 * Kedacom Hardware Abstract Level
 *
 * brd_misc.h
 *
 * Copyright (C) 2013-2020, Kedacom, Inc.
 *
 * History:
 *   2013/09/22 - [xuliqin] Create
 *
 */

#ifndef _BRD_MISC_H
#define _BRD_MISC_H

#include <drvlib_def.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * FXO Defines
 */
#define FXO_SET_HANGUP           0x00
#define FXO_SET_PICKUP2CALL      0x01
#define FXO_SET_TALK             0x02
#define FXO_SET_RCV_RING         0x03
#define FXO_EN_REMOTE_SPEAK      0x04
#define FXO_DIS_REMOTE_SPEAK     0x05
#define FXO_EN_REMOTE_LISTEN     0x06
#define FXO_DIS_REMOTE_LISTEN    0x07
#define FXO_SET_RING_VOLUME_IN   0x09
#define FXO_SET_RING_VOLUME_OUT  0x0a
#define FXO_GET_STATE            0x80

#define FXO_STATE_RING     0x00
#define FXO_STATE_PICKUP   0x01
#define FXO_STATE_HANGUP   0x02
/* -------------------------------------------------------------------------- */

/*
 * FPAG Defines
 */
#define FPGA_PROGRAM_PROGRESS   0
#define FPGA_PROGRAM_START      1
#define FPGA_PROGRAM_END        2
/* -------------------------------------------------------------------------- */
/*
 * Switcher control defines
 */

/* cmd defines */
enum
{
	SW_SPK_ENABLE = 0,
	SW_SPK_DISABLE,
	SW_SDI_GET,
	SW_BRD_SHUTDOWN,
	SW_EXTERN_RESET,
	SW_BURN_START_ENABLE,
	SW_BURN_START_DISABLE,
	SW_BURN_STOP_ENABLE,
	SW_BURN_STOP_DISABLE,
	SW_REPLAY_ENABLE,
	SW_REPLAY_DISABLE,
	SW_LCD_BACKLIGHT_ENABLE,
	SW_LCD_BACKLIGHT_DISABLE,
	SW_SOFT_RESET_ENABLE,
	SW_SOFT_RESET_DISABLE,
};

#define COM_REG_READ            0 /* read register */
#define COM_REG_WRITE           1 /* write register */

/* common device register read/write struct */
typedef struct{
	u32 id;           /* device id, such as: PLD_DEV_ID(0) */
	u32 rw;           /* see also COM_REG_READ */
	u32 reg;          /* register offset address */
	u32 val;          /* register value */
}fpga_rw_param;

/* -------------------------------------------------------------------------- */

int BrdSleep(int nSleep);
int BrdSetSpeakerMode(int nMode);
int BrdSetBurnStart(int nMode);
int BrdSetBurnStop(int nMode);
int BrdSetReplay(int nMode);
int BrdSetLcdBacklight(int nMode);
int BrdSetSoftReset(int nMode);
int BrdSetShutdown(void);
int BrdSetExtReset(void);
int BrdFxoCtrl(int nDevId, int nCmd, void *pArgs);

int BrdSwitcherCtrl(int nCmd);
/*
 * \brief :
 *      set gpio extend card work mode
 * \param : 
 *      @dev_id : extend card id
 *      @dir    : extend card gpio direction controls . 0 = input; 1 = output
 *                Bit[31:0] = GPIO[31:0]
 *      @default_val : set io default value . 1 = high ; 0 = low
 * \return :
 *      0 -- success
 */
int BrdGpioExtCardConfig(int dev_id, int dir, int default_val);

/*
 * \brief :
 *      get gpio extend card input value .
 * \param :
 *      @dev_id    : extend card id
 *      @input_num : want get input IO number
 *      @value     : return input IO value
 * \return :
 *      0 -- success
 */
int BrdGpioExtCardGetInput(int dev_id, int input_num, int *value);
/*
 * \brief : 
 *      set gpio extend card output value .
 * \param :
 *      @dev_id     : extend card id
 *      @output_num : want set output IO number
 *      @value      : output IO value
 * \return : 
 *      0 -- success
 */
int BrdGpioExtCardSetoutput(int dev_id, int output_num, int value);

/*
 * read/write IC(FPGA) register 
 */
int BrdRwLogIC(fpga_rw_param *param);

/*
*check usb port
*/
int BrdUSBCheckPort(void);

/*
 * \brief : 
 *      get battery power level
 * \param :
 *      @level     : 0 ~ 100
 * \return : 
 *      0 - success, else: failed
 */
int BrdGetBatteryLevel(int *level);

/*
 * \brief : 
 *      get charged state
 * \param :
 *      @state     : 0 - uncharge, 1 - charged
 * \return : 
 *      0 - success, else: failed
 */
int BrdGetChargeState(int *state);

/*
 * \brief :
 *      get optocoupler state
 * \param :
 *      @state     : 0 - unreached, 1 - reached position
 * \return :
 *      0 - success, else: failed
 */
int BrdGetOptoCouplerState(int *state);

/*
 * \brief :
 *      Set optocoupler status
 * \param :
 *      @enable     : 0 - disable, 1 - enable
 * \return :
 *      0 - success, else: failed
 */
int BrdSetOptoCoupler(int enable);

/*
 * \brief :
 * MSP430 burn
 * \param :
 *      @state     : 0 - stop, 1 - start
 * \return :
 *      0 - success, else: failed
 */
int BrdMCUBurn(int state);

/*
 * \brief :
 * camera reset
 * \param :
 *      @dev_id     : camera id 
 * \return :
 *      0 - success, else: failed
  */
int BrdRstCamra(u32 devId);

#ifdef __cplusplus
}
#endif

#endif
