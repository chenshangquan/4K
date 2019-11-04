#ifndef __ipc_msgh
#define __ipc_msgh

#ifdef __cplusplus
extern "C" {
#endif

#define     MSG_MAX_BUF     1024

typedef struct msgBuf {
    long mtype;
    long mlen;
    char mtext[MSG_MAX_BUF];
}MSGBUF;

extern int ipc_msgCreate(char *pathname);
extern void ipc_msgDestroy(char *pathname);
extern int ipc_msgAttach(char *pathname);
extern int ipc_msgDetach(int fd);
extern int ipc_msgRecv(int fd, void *ptr,long *type, int flag);
extern int ipc_msgSend(int fd, const void *ptr, long bytes, long type, int flag);


#ifdef __cplusplus
}
#endif

#endif
