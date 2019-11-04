/* Zebra thread library
 * Copyright (C) 1997, 98 Kunihiro Ishiguro
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
#ifndef _ZEBRA_THREAD_H
#define _ZEBRA_THREAD_H

#define DFT_TH_STACKSIZE    (1024 * 16)
#define TH_PRIOR_1          5
#define TH_PRIOR_2          4
#define TH_PRIOR_3          3
#define TH_PRIOR_4          2
#define TH_PRIOR_5          1

#define thread_sem_safe_wait(s)  \
        {  \
          int old_cancel_state;  \
          pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, &old_cancel_state);  \
	  pthread_cleanup_push((void*)sem_post, (void*)&s);  \
	  sem_wait(&s);  

#define thread_sem_safe_post(s)  \
          pthread_cleanup_pop(1);  \
	  pthread_setcanceltype(old_cancel_state, NULL);  \
	}
	  
 
typedef struct _thread_struc
{
  char *name;
  void (*proc)(void*);
  void *param;
  int policy;
  int priority;
}thread_struc;

/* Prototypes */
pthread_t thread_spawn(char* name, void (*proc)(void*), void *param, int stack_size, int policy, int priority);
void thread_yield();
void* thread_wait(int thread_id);
int thread_kill(int thread_id);
void thread_exit();
void thread_delay(int sec);
int thread_get_id();
int thread_get_priority(int thread_id);
int thread_adjust_priority(int thread_id, int priority);
void thread_set_cleanup(int thread_id, void (*proc)(void*), void *param);
void thread_sig_block(int signum);
void thread_sig_unblock(int signum);
void thread_sig_blockall();

#endif
