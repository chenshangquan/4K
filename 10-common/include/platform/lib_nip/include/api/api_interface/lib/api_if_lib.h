
/* api_if_lib.h -
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

extern char * zebra_get_if_name (char *name, enum if_type iftype, int ifunit);
extern int if_get_type_and_unit_by_name (char *name, enum if_type *type, int *unit);

