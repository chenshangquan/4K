/* api_webserver.h -
 *
 * Copyright 1997-2003 suzhou Keda co.
 *
 * description :
 * -------------------------
 * Purpose: for nip api.
 *
 * modification history
 * -------------------------
 * 2006-01-17 zhangyunping write first.
 */

#ifndef _API_WEBSERVER_H_
#define _API_WEBSERVER_H_
#include "api/nip_api.h"

struct api_set_webs{
	int errid;
	int opcode;
	int open_flag;
	int port;
	char  path[256];
};

#define NIP_WEBSERVER_SET    	NIP_WEBSERVER_BASE+1

#define API_WEBS_SET_ENABLE		1
#define API_WEBS_SET_AUTH			2
#define API_WEBS_SET_PATH			9
#define API_WEBS_SET_PORT			10
#define API_WEBS_SET_INSPECT			11

extern void nip_api_webserver_register();

extern int nip_set_webs_enable(int opcode);

extern int nip_set_webs_inspect(int opcode);

extern int  webs_setRootPath(char * root_path);

#endif  /* _API_WEBSERVER_H_ */

