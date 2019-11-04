
/* interface_loop.h -
 *
 * Copyright 1997-2003 suzhou Keda co.
 *
 * description :
 * -------------------------
 * Purpose: support config loopback interface.
 *
 * modification history
 * -------------------------
 * 2006-3-1 zhuzhenming write first.
 */

#ifndef _INTERFACE_LOOP_H_
#define _INTERFACE_LOOP_H_

int loop_register (struct interface *ifp);
int loop_unregister (struct interface *ifp);

#endif  /* _INTERFACE_LOOP_H_ */

