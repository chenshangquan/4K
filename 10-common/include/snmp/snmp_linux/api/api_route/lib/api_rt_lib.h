
/* api_rt_lib.h -
 *
 * Copyright 1997-2003 suzhou Keda co.
 *
 * description :
 * -------------------------
 * Purpose: for nip api.
 *
 * modification history
 * -------------------------
 * 2005-11-30 zhuzhenming write first.
 */
 
extern u_char api_ip_masklen (struct in_addr netmask);
extern int api_check_prefix (char *str, struct prefix_ipv4 *p);

