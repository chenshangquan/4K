/* Zebra logging funcions.
 * Copyright (C) 1997, 1998, 1999 Kunihiro Ishiguro
 *
 * This file is part of GNU Zebra.
 *
 * GNU Zebra is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2, or (at your option) any
 * later version.
 *
 * GNU Zebra is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Zebra; see the file COPYING.  If not, write to the Free
 * Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.  
 */

#ifndef _ZEBRA_ZLOG_H
#define _ZEBRA_ZLOG_H

#define ZLOG_NOLOG              0x00
#define ZLOG_CONSOLE			0x01
#define ZLOG_BUFFERED			0x02
#define ZLOG_TERMINAL           0x04
#define ZLOG_SYSLOG             0x08
#define ZLOG_FILE             	0x12
#define ZLOG_ALL				0x13

#define ZLOG_DATAIPC_FILE		"/tmp/zlogdata.v"
#define ZLOG_CFGIPC_FILE		"/tmp/zlogcfg.v"

#define ZLOG_CFG_TYPE			0
#define ZLOG_LOGINFO_TYPE		1

#define ZLOG_MAX_DLEN			512

#define ZLOG_DEBUG				7
#define ZLOG_INFO				6
#define ZLOG_NOTIFY				5
#define ZLOG_WARN				4
#define ZLOG_ERROR				3
#define ZLOG_CRITICAL			2
#define ZLOG_ALERT				1
#define ZLOG_EMERGE				0

extern struct  zlog_s   		zlog_module_struct;

#define	get_zlog_global()		zlog_module_struct

#define get_zlog_sentd_fd()		zlog_module_struct.dpipefd

/*used to store the information about the external module*/
struct zlog_s
{
	const char *	ident;
	int				dpipefd;
};

/*used to store the log information */
struct zlMsg
{
	int 			level;
	char 			content[ZLOG_MAX_DLEN]; 
	char 			proto[32];
};

struct zlInfo
{
	int 			openflag;
	int 			zllevel;
};

/*used to store the user config the log information*/
struct zlOption
{
	struct	zlInfo	zl_con;
	struct	zlInfo 	zl_buf;
	struct	zlInfo 	zl_ter;
	struct	zlInfo	zl_file;
	int 			log_flag;
	int 			t_option;	//time_option
	int 			n_option;	//number_option
	int 			m_mask;	//module_mask used to separate the modules which will to log
	int				max_bufsize;
	FILE *			zlog_fp;
	char 			zlog_fname[256];
};


#define get_loginfo_num(bufsize) 	(int)(bufsize/(sizeof(struct CListNode)))

/* client called it to init the struct zlog_s*/
extern int zlog_module_init(char * zipc_name);
extern int zlog_init();

/* the other module called it to output the log message*/
extern int zlog_msg(const char * proto, int level, const char * fmt, ...);

extern void cmd_zlog_init();


#ifndef add_log
#include <syslog.h>
/*
#define ZLOG_NOLOG              0x00
#define ZLOG_FILE		0x01
#define ZLOG_SYSLOG		0x02
#define ZLOG_STDOUT             0x04
#define ZLOG_STDERR             0x08

#define ZLOG_NOLOG_INDEX        0
#define ZLOG_FILE_INDEX         1
#define ZLOG_SYSLOG_INDEX       2
#define ZLOG_STDOUT_INDEX       3
#define ZLOG_STDERR_INDEX       4
#define ZLOG_MAX_INDEX          5
*/
#define ZLOG_STDOUT             0x04
  



typedef enum 
{
  ZLOG_NONE,
  ZLOG_DEFAULT,
  ZLOG_ZEBRA,
  ZLOG_RIP,
  ZLOG_BGP,
  ZLOG_OSPF,
  ZLOG_RIPNG,  
  ZLOG_OSPF6,
  ZLOG_MASC
} zlog_proto_t;

struct zlog 
{
  const char *ident;
  zlog_proto_t protocol;
  int flags;
  FILE *fp;
  char *filename;
  int syslog;
  int stat;
  int connected;
  int maskpri;		/* as per syslog setlogmask */
  int priority;		/* as per syslog priority */
  int facility;		/* as per syslog facility */
  int record_priority;
};

/* Message structure. */
struct message
{
  int key;
  char *str;
};

/* Default logging strucutre. */
extern struct zlog *zlog_default;
extern const char *zlog_priority[];
extern const char *zlog_proto_names[];
/* Open zlog function */
struct zlog *openzlog (const char *, int, zlog_proto_t, int, int);

/* Close zlog function. */
//void closezlog (struct zlog *zl);

/* GCC have printf type attribute check.  */
#ifdef __GNUC__
#define PRINTF_ATTRIBUTE(a,b) __attribute__ ((__format__ (__printf__, a, b)))
#else
#define PRINTF_ATTRIBUTE(a,b)
#endif /* __GNUC__ */




/* Generic function for zlog. */
//void zlog (struct zlog *zl, int priority, const char *format, ...) PRINTF_ATTRIBUTE(3, 4);
#define zlog(zl,priority,format,args...) \
    if(zl == NULL)\
		zlog_msg((char *)NULL,priority,format,##args);\
    else\
		zlog_msg(zlog_proto_names[((struct zlog *)zl)->protocol],priority,format,##args)

/* Handy zlog functions. */
//void zlog_err (const char *format, ...) PRINTF_ATTRIBUTE(1, 2);
//void zlog_warn (const char *format, ...) PRINTF_ATTRIBUTE(1, 2);
//void zlog_info (const char *format, ...) PRINTF_ATTRIBUTE(1, 2);
//void zlog_notice (const char *format, ...) PRINTF_ATTRIBUTE(1, 2);
//void zlog_debug (const char *format, ...) PRINTF_ATTRIBUTE(1, 2);
#define zlog_err(format,args...)  zlog_msg((char*)NULL,ZLOG_ERROR,format,##args)
#define zlog_debug(format,args...)  zlog_msg((char*)NULL,ZLOG_DEBUG,format,##args)
#define zlog_notice(format,args...)  zlog_msg((char*)NULL,ZLOG_NOTIFY,format,##args)
#define zlog_info(format,args...)  zlog_msg((char*)NULL,ZLOG_INFO,format,##args)
#define zlog_warn(format,args...)  zlog_msg((char*)NULL,ZLOG_WARN,format,##args)
/* For bgpd's peer oriented log. */
//void plog_err (struct zlog *, const char *format, ...);
//void plog_warn (struct zlog *, const char *format, ...);
//void plog_info (struct zlog *, const char *format, ...);
//void plog_notice (struct zlog *, const char *format, ...);
//void plog_debug (struct zlog *, const char *format, ...);
#define plog_err(zl,format,args...)  zlog_msg(zlog_proto_names[((struct zlog *)zl)->protocol],ZLOG_ERROR,format,##args)
#define plog_debug(zl,format,args...)  zlog_msg(zlog_proto_names[((struct zlog *)zl)->protocol],ZLOG_DEBUG,format,##args)
#define plog_notice(zl,format,args...)  zlog_msg(zlog_proto_names[((struct zlog *)zl)->protocol],ZLOG_NOTIFY,format,##args)
#define plog_info(zl,format,args...)  zlog_msg(zlog_proto_names[((struct zlog *)zl)->protocol],ZLOG_INFO,format,##args)
#define plog_warn(zl,format,args...)  zlog_msg(zlog_proto_names[((struct zlog *)zl)->protocol],ZLOG_WARN,format,##args)
/* Set zlog flags. */
void zlog_set_flag (struct zlog *zl, int flags);
void zlog_reset_flag (struct zlog *zl, int flags);

/* Set zlog filename. */
int zlog_set_file (struct zlog *zl, int flags, char *filename);
int zlog_reset_file (struct zlog *zl);

/* Rotate log. */
int zlog_rotate ();

/* For hackey massage lookup and check */
#define LOOKUP(x, y) mes_lookup(x, x ## _max, y)

char *lookup (struct message *, int);
char *mes_lookup (struct message *meslist, int max, int index);


#endif

#endif /* _ZEBRA_LOG_H */

