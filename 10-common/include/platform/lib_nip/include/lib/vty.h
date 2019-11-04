/* Virtual terminal [aka TeletYpe] interface routine
   Copyright (C) 1997 Kunihiro Ishiguro

This file is part of GNU Zebra.

GNU Zebra is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2, or (at your option) any
later version.

GNU Zebra is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU Zebra; see the file COPYING.  If not, write to the Free
Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
02111-1307, USA.  */

#ifndef _ZEBRA_VTY_H
#define _ZEBRA_VTY_H

#define VTY_BUFSIZ 512
#define VTY_MAXHIST 20

#include "lib/sockunion.h"

//added by fxp 2005-11-3
#include <pthread.h>
#include <semaphore.h>

#include <termios.h>
#include "lib/timer.h"

#define 	VTY_TIMEOUT		10 //sec

/* VTY struct. */
struct vty
{
  /* File descripter of this vty. */
  int fd;

  /* the string pointer of telnet user */
  char * username;

  /* Is this vty connect to file or not */
  enum {VTY_TERM, VTY_FILE, VTY_SHELL, VTY_SHELL_SERV} type;

  /* Node status of this vty */
  int node;

  /* What address is this vty comming from. */
  char *address;

  /* Failure count */
  int fail;

  /* Output buffer. */
  struct buffer *obuf;

  /* Command input buffer */
  char *buf;

  /* Command cursor point */
  int cp;

  /* Command length */
  int length;

  /* Command max length. */
  int max;

  /* Histry of command */
  char *hist[VTY_MAXHIST];

  /* History lookup current point */
  int hp;

  /* History insert end point */
  int hindex;

  /* For current referencing point of interface, route-map,
     access-list etc... */
  void *index;

  /* For multiple level index treatment such as key chain and key. */
  void *index_sub;

  /* For escape character. */
  unsigned char escape;

  /* Current vty status. */
  enum {VTY_NORMAL, VTY_CLOSE, VTY_MORE, VTY_MORELINE,
        VTY_START, VTY_CONTINUE} status;

  /* IAC handling */
  unsigned char iac;

  /* IAC SB handling */
  unsigned char iac_sb_in_progress;
  struct buffer *sb_buffer;

  /* Window width/height. */
  int width;
  int height;

  int scroll_one;

  /* Configure lines. */
  int lines;

  /* Current executing function pointer. */
  int (*func) (struct vty *, void *arg);

  /* Terminal monitor. */
  int monitor;

  /* In configure mode. */
  int config;

  int startup;

  pthread_t read_tid;
  pthread_t write_tid;

  sem_t sem_obuf;
  sem_t sem_write;

  timer_handle* timer;

  /* Timeout seconds and thread. */
  unsigned long v_timeout;

  /* Output data pointer. */
  int (*output_func) (struct vty *, int);
  void (*output_clean) (struct vty *);
  void *output_rn;
  unsigned long output_count;
  int output_type;
  void *output_arg;
  //div_screen data --add by sg 06/05/26
  int line;//record the current linenum
  enum{DISP_BEGIN,DISP_ONLINE,DISP_BLOCK,DISP_END} dispStat;
  int dScreenFlag;//the flag of screen-division
  char endlineflag;
};

/* Integrated configuration file. */
#define INTEGRATE_DEFAULT_CONFIG "Zebra.conf"

/* Small macro to determine newline is newline only or linefeed needed. */
#define VTY_NEWLINE  ((vty->type == VTY_TERM) ? "\r\n" : "\n")

/* Default time out value */
#define VTY_TIMEOUT_DEFAULT 180

/* Vty read buffer size. */
#define VTY_READ_BUFSIZ 512

/* Directory separator. */
#ifndef DIRECTORY_SEP
#define DIRECTORY_SEP '/'
#endif /* DIRECTORY_SEP */

#ifndef IS_DIRECTORY_SEP
#define IS_DIRECTORY_SEP(c) ((c) == DIRECTORY_SEP)
#endif

/* GCC have printf type attribute check.  */
#ifdef __GNUC__
#define PRINTF_ATTRIBUTE(a,b) __attribute__ ((__format__ (__printf__, a, b)))
#else
#define PRINTF_ATTRIBUTE(a,b)
#endif /* __GNUC__ */

/* Utility macro to convert VTY argument to unsigned integer.  */
#define VTY_GET_INTEGER(NAME,V,STR)                              \
{                                                                \
  char *endptr = NULL;                                           \
  (V) = strtoul ((STR), &endptr, 10);                            \
  if ((V) == ULONG_MAX || *endptr != '\0')                       \
    {                                                            \
      vty_out (vty, "%% Invalid %s value%s", NAME, VTY_NEWLINE); \
      return CMD_WARNING;                                        \
    }                                                            \
}

#define VTY_GET_INTEGER_RANGE(NAME,V,STR,MIN,MAX)                \
{                                                                \
  char *endptr = NULL;                                           \
  (V) = strtoul ((STR), &endptr, 10);                            \
  if ((V) == ULONG_MAX || *endptr != '\0'                        \
      || (V) < (MIN) || (V) > (MAX))                             \
    {                                                            \
      vty_out (vty, "%% Invalid %s value%s", NAME, VTY_NEWLINE); \
      return CMD_WARNING;                                        \
    }                                                            \
}

/* Exported variables */
extern char integrate_default[];

/* Prototypes. */
void vty_init (void);
void vty_reset (void);
void vty_finish (void);
struct vty *vty_new (void);
int vty_out (struct vty *, const char *, ...) PRINTF_ATTRIBUTE(2, 3);
void vty_read_config (char *, char *, char *);
struct vty *vty_create (int vty_sock, union sockunion *su);
void vty_close (struct vty *);
char *vty_get_cwd (void);
void vty_log (const char *, const char *, va_list);
int vty_shell (struct vty *);
void vty_hello (struct vty *);
//added by swp
int vty_read (struct vty *);
int vty_flush (struct vty *);

//added by zhzs
char *vty_node_type_str(int t);

//added by fxp
int vty_advanced_read(struct vty*,char *,char *);

int vty_term_echo_off(int fd);
int vty_term_echo_on(int fd);

int netport_check(int newport, int named_port);

int printf2(const char * fmt1,const char *	fmt2,...);

int vty_out2
	(
	struct vty *vty, 	
	const char *fmt1, 
	const char *fmt2, 	
 	... 				
	);

char * get_cmd_help_language_string(char * help_string );
#ifndef DIV_SCREEN
void vty_consol_sigint();
#endif
#endif /* _ZEBRA_VTY_H */
