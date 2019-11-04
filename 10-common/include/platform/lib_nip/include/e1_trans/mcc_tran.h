#ifndef _MCC_TRAN_H_
#define _MCC_TRAN_H_
#define TRAN_CH_START 0xfe

/* command: e1<0-3> channel-group <0-7> timeslots <0-31> serial <16-62>  mtu <0-65535>*/	
int open_e1_trans(int e1, int channel, char *timeslot,int mtu);
/* 
switch (return value)
case >0 : fd;
case -1 : e1 config error
case -2 : open tty error
case -3 : set DISC error 
*/

void close_e1_trans(int e1, int channel ,int fd);
int get_e1_in_use_slot(int fd);
extern int nip_e1_in_transparent_mode(int e1 , int *result);

#endif
