/**************************************************************
*     Copyright (C) 2004-2005, KEDACOM
*
* 1.FILENAME    : cpl_list.h
* 2.COMPONENT   : Cross Platfrom Libaray Link-list
* 3.AUTHOR      : Zeng Zhaoming (SH)
* 4.DATE        : 2005-9-8 10:00
* 5.DESCRIPTION : link-list related defines
* 6 Changelog:
	2005-9-8 10:00: Zzm write init version
***************************************************************/
#ifndef _CPL_LIST_H_
#define _CPL_LIST_H_
#include <errno.h>

#include <cpl_def.h>
#include <cpl_debug.h>

/* list node */
typedef struct cpl_list_node {
	void* 	head;
	struct cpl_list_node* 	pre, *next;
	int	id;  //identify the item
} cplt_list_node;

/* list head */
typedef struct cpl_list_head {
	cplt_list_node*	pre, *next;
	int	id; //identify
//	cplt_lock*	lock;
} cplt_list_head;

#define cpl_list_empty(h) ((NULL == (h)->pre) && (NULL == (h)->next))

static inline int cpl_list_head_init(cplt_list_head* h, int id)
{
	CPL_D_ENTER();
	CPL_D_PARAM("parameters: h=%p, id=%d\n", h, id);

	if(!h)
		return (-EINVAL);
	h->pre = h->next = NULL;
	h->id = id;

	return 0;
}

static inline int cpl_list_add(cplt_list_head* h, cplt_list_node* n)
{

	CPL_D_ENTER();
	CPL_D_PARAM("parameters: h=%p, n=%p\n", h, n);

	if(!h || !n)
		return (-EINVAL);

	n->head = h;
	/* list is empty */
	if(!h->pre) {
		n->pre = n->next = n;
		h->pre = h->next =n;
		return 0;
	}
	n->pre = h->pre;
	n->next = h->pre->next;
	h->pre->next->pre = n;
	h->pre->next = n;
	h->pre = n;
	return 0;
}

static inline int cpl_list_clone(cplt_list_head* dst, cplt_list_head* src,
		int (*clone_item)(int* d, int s))
{
	cplt_list_node* n, **dstn, *tmp, *pre = NULL;

	CPL_D_ENTER();

	if(!dst || !src)
		return (-EINVAL);

	if(!src->next)
		return 0;
	
	n = src->next;
	dstn = &dst->next;
	do {
		tmp = cpl_malloc(sizeof(cplt_list_node));
		if(!tmp)
			return (-ENOMEM);
		tmp->head = dst;
		tmp->pre = pre;
		tmp->next = NULL;
		if (clone_item)
			clone_item(&tmp->id, n->id);
		else
			tmp->id = n->id;
		
		*dstn = tmp;
		pre = tmp;
		dstn = &(*dstn)->next;
		n = n->next;
	} while (n!=src->next);

	*dstn = dst->next;
	dst->pre = dst->next->pre = tmp;
	return 0;
}

static inline int cpl_list_append(cplt_list_head* h, cplt_list_node* n)
{
	CPL_D_ENTER();
	CPL_D_PARAM("parameters: h=%p, n=%p\n", h, n);

	if(!h || !n)
		return (-EINVAL);
	n->head = h;
	/* list is empty */
	if(!h->next) {
		n->pre = n->next = n;
		h->pre = h->next =n;
		return 0;
	}

	n->next = h->next;
	n->pre = h->next->pre;
	h->next->pre->next = n;
	h->next->pre = n;
	h->next = n;
	return 0;
}

static inline cplt_list_node* cpl_list_find(
		cplt_list_head* h, 
		int id, 
		int (*match)(int, int)
		)
{
	cplt_list_node* ret;

	CPL_D_ENTER();
	CPL_D_PARAM("parameters: h=%p, id=%d, match=%p\n", h, id, match);

	if(!h || !h->next)
		return NULL;
	ret = h->next;

	do {
		if (!match && ret->id == id)
			return ret;
		else if(match && !(*match)(ret->id, id))
			return ret;
		else
			ret = ret->next;
	} while(ret != h->next);
	CPL_D_EXIT();

	return NULL;
}

static inline int cpl_list_del(cplt_list_head* h, cplt_list_node* n)
{
	CPL_D_ENTER();
	CPL_D_PARAM("parameters: h=%p, n=%p\n", h, n);
	
	if(h != (cplt_list_head*)n->head) {
#ifdef CPL_D_DEBUG
		cpl_bug("del list node, node->head != h \n");
#endif
		return (-EINVAL);
	}
	
	if(!h || !h->next)
		return (-EINVAL);

	if(h->next == h->pre) {
		h->next = h->pre = NULL;
		return 0;
	}

	n->next->pre = n->pre;
	n->pre->next = n->next;

	if(h->next == n)
		h->next = n->next;

	else if(h->pre == n) 
		h->pre = n->pre;
	
	return 0;
}

/* cleanup all node in list */
static inline int cpl_list_cleanup(
	cplt_list_head* h, 
	int (*cleanup)(int)
	)
{
	cplt_list_node* n;
	
	if(!h)
		return (-EINVAL);

	n = h->next;

	while(n) {
		if(!cleanup || !(*cleanup)(n->id)) {
			cpl_list_del(h, n);
			cpl_free(n);
		}
		n = h->next;
	};
	
	return 0;
}
#endif
