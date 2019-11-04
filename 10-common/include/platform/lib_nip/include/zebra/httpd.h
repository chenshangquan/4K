#ifndef _CFG_HTTPD_H
#define _CFG_HTTPD_H

#include "lib/zipc.h"

#define DEF_WEBFILES_PATH			"/usr/webroot"
#define ZMSG_HTTPD_SIG		 		ZMSG_HTTP_BASE+1
#define	ZIPC_HTTPD_ID				"httpd"
#define HTTP_MAX_PATH_LEN			128
#define HTTP_DEFAULT_PORT 			80
#define   HTTP_THREAD_MAX_SIZE      1024*80


#define HTTP_CONTROL_SHUTDOWN		1
#define HTTP_CONTROL_UPDATE			2
#define HTTP_CONTROL_RESTART		4
#define HTTP_CONTROL_OTHER			8

struct http_msg{
	int port;
	int auth_flag;
	int ctrl;
	char path[HTTP_MAX_PATH_LEN];
};


extern 	pthread_mutex_t http_mutex_lock;
extern 	pthread_cond_t http_cond_ok;

extern  int http_ctl_fd;
extern 	int http_ctl_has_data;

extern 	int  http_user_auth_flag;

extern 	void httpd_init();

int http_set_enable(void);
int http_set_disable(void);
int http_set_inspect_enable(void);
int http_set_inspect_disable(void);
int http_reset_webpath();
int http_set_webpath(char * root_path);

#endif
