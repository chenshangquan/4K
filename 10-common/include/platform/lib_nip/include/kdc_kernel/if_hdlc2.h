
#ifndef _IF_HDLC2_H_
#define _IF_HDLC2_H_


#define FIOSDEBUGEVENT _IO('f',132)
#define FIOCDEBUGEVENT _IO('f',133)
#define FIOSDEBUGPACKET	_IO('f',134)
#define FIOCDEBUGPACKET	_IO('f',135)
#define FIOSDISCUP		_IOW('f',136,int)
/* 
use tty_fd
ioctl(ttyfd, FIOSDEBUGEVENT);
*/

/* discpline NUMBER */
#define K_HDLC 		17

#define IF_PROTO_SET_CISCO		0x200D

#endif
