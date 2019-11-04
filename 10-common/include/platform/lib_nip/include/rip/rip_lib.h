
#ifndef _RIP_LIB_H_
#define _RIP_LIB_H_

extern void rip_debug_init();
extern int rip_interface_new_hook (struct interface *ifp);
extern int rip_interface_delete_hook (struct interface *ifp);

#endif

