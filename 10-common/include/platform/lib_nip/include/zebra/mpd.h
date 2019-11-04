#ifndef __MP_D__
#define  __MP_D__

#include "lib/zipc.h"
#include "ppp/ppp_zebra.h"
#include "lib/aligned.h"


#define MULTILINK_DEBUG_NONE_FLAG	0x0
#define MULTILINK_DEBUG_ALL_FLAG		0xffffffff
#define MULTILINK_DEBUG_EVENT_FLAG	0x01			/* join/leave mutlilink*/
#define MULTILINK_DEBUG_ERROR_FLAG	0x02			/* sock/pipe open,close error */
#define MULTILINK_DEBUG_WARN_FLAG	0x04			/* bind/vir miss */


void mpd_main(void);
#endif


