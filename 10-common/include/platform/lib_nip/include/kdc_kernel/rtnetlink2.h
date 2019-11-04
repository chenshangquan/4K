#ifndef _ZEBRA_RTNETLINK2_H
#define _ZEBRA_RTNETLINK2_H

#include <linux/rtnetlink.h>

enum{
	IFLA_BANDWIDTH = IFLA_MAX +1,
	__IFLA_NEW_MAX,
};
#define IFLA_NEW_MAX (__IFLA_NEW_MAX -1)


#endif
