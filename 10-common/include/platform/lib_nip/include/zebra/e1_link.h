/*	Copyright(C) 2005 KEDACOM 
*
*	filename	: e1_link.h
*	createdate	: 2005-9-21 9:24
*	function	: for nip e1 config.
*	modify		: 
*/

#include <semaphore.h>

#define FIRST_CHANNEL -1

int debug_flag = 0;

#define debugf(fmt,args...)  \
	if(debug_flag) 	printf(fmt ,##args)

struct e1_node{
	int e1;				
	int channel;				
	int serial;	
	struct e1_node * next;
};

static sem_t e1_lock ;

#define lock_init(e1_lock)		sem_init(&e1_lock, 0, 1)
#define rlock(e1_lock) 			sem_wait(&e1_lock)
#define runlock(e1_lock)  		sem_post(&e1_lock)
#define wlock(e1_lock)    		sem_wait(&e1_lock)
#define wunlock(e1_lock)    	sem_post(&e1_lock)
#define lock_release(e1_lock)  	sem_destroy(&e1_lock)


static struct e1_node *e1_base = NULL;


static int e1_node_new(int e1, int channel, int serial)
{
	struct e1_node **head = &e1_base;;
	struct e1_node *prev = NULL; 
	struct e1_node *next = NULL; 	
	struct e1_node *new = NULL;
	
	debugf("%s e1 %d channel %d serial %d\n", __func__, e1, channel, serial);
	
	new = (struct e1_node* )malloc(sizeof(struct e1_node));
	debugf("%s 1\n", __func__); 
	if(new == NULL)
		return -1;
	debugf("%s 2\n", __func__); 
	/*initialize the node*/
	new->e1		= e1;		   
	new->channel	= channel;		
	new->serial	= serial;    
	new->next   = NULL;   	

	debugf("%s 3\n", __func__); 
	/*e1_lock the list*/
	wlock(e1_lock);
	debugf("%s 4\n", __func__); 
	/* add to phy config list */		

	if(*head == NULL){
		*head = new;
		/*unlock the list*/
		wunlock(e1_lock);
		debugf("%s ok\n", __func__);
		return 0;
	}
	debugf("%s 5\n", __func__); 
	prev = next = *head;
	while(next){
		if(next->e1 > new->e1){
			new->next = next;
			if(next == *head)				
				*head = new;			/* inset at the head of list */
			else				
				prev->next = new;		/*inset at the middile of the list */		
			break;
		}			
		prev = next;
		next = next->next;
	}
	debugf("%s 6\n", __func__); 		
	if (!next)
		prev->next = new;			/* inset at the tail of the list */
	/*unlock the list*/
	wunlock(e1_lock);
	debugf("%s ok\n", __func__);
	return 0;
}

struct e1_node *get_node(int serial)
{
	struct e1_node **head = &e1_base;;
	struct e1_node* next = NULL;	

	/*lock the list*/
	rlock(e1_lock);
	
	next = *head;
	
	while(next){
		if(next->serial == serial){
			runlock(e1_lock);
			return next;
		}
		next = next->next;
	}
	runlock(e1_lock);	
	return NULL;
}

void e1_node_delete(int serial)
{
	struct e1_node **head = &e1_base;;
	struct e1_node* next = NULL;	
	struct e1_node *node = get_node(serial);

	if(node == NULL)
		return;
	
	/*lock the list*/
	wlock(e1_lock);
	
	next = *head;

	if(*head == node){
		*head = node->next;
	}
	else{
		while(next->next != node){
			next = next->next;
		}
		next->next = node->next;	
	}
	free((void *)node);
	node = NULL;	
	/*unlock the list*/
	wunlock(e1_lock);	
}

void e1_node_modify(int e1, int channel, int serial)
{
	struct e1_node* next = e1_base;	
	
	/*lock the list*/
	wlock(e1_lock);
	
	while(next){
		if(next->e1 == e1 && next->channel == channel && next->serial != serial ){
			next->serial = serial;
			runlock(e1_lock);
			return ;
		}
		next = next->next;
	}
	wunlock(e1_lock);	
}


int get_e1(int serial)
{
	struct e1_node *node = get_node(serial);
	
	if(node == NULL)
		return -1;
	else	
		return node->e1;
}

int get_channel(int serial)
{
	struct e1_node *node = get_node(serial);
	
	if(node == NULL)
		return -1;
	else	
		return node->channel;
}

int get_serial(int e1, int channel)
{
	struct e1_node* next = e1_base;	

	/*lock the list*/
	rlock(e1_lock);	
	
	while(next){
		if(next->e1 == e1 && channel == FIRST_CHANNEL){
			runlock(e1_lock);
			return next->serial;
		}
		if(next->e1 == e1 && next->channel == channel){
			runlock(e1_lock);
			return next->serial;
		}
		next = next->next;
	}
	runlock(e1_lock);	
	return -1;
}
