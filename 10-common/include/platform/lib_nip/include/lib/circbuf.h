#ifndef _CircBuf_h
#define _CircBuf_h
#include "lib/vty.h"
struct CListNode
{
   struct CListNode*	next;
   char 				data[512+128];
};

struct clist
{
	struct CListNode * 	first;
	struct CListNode * 	current;
	struct CListNode * 	last;
	int 			   	count;
};

struct 	clist *clist_init();
void 	clist_free(struct clist * circList);
int 	clist_getlength(struct clist * circList);   							//get length of the Circle List
int 	clist_getcurpos(struct clist * circList);								//get current position
char * 	clist_getcurdata(struct clist * circList);  						//get current data
char * 	clist_getfirstdata(struct clist * circList);
char * 	clist_getlastdata(struct clist * circList);
void 	clist_getfirster(struct clist * circList);				    		//move pointer to head 
int 	clist_getnext(struct clist * circList);         						//pointer move Next
int 	clist_getprior(struct clist * circList);        						//pointer move Prior 
void 	clist_insert(struct clist * circList, const char *value, long MaxNum);    			//insert a node in curpos+1
int 	clist_remove(struct clist * circList);            					//delete current node,current pointer move next
void 	clist_showlist(struct clist * circList, struct vty *vty);

#endif
