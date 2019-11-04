#ifndef _ACL_LIST_H
#define _ACL_LIST_H

/*
 * Simple doubly linked list implementation.
 *
 * Some of the internal functions ("__xxx") are useful when
 * manipulating whole lists rather than single entries, as
 * sometimes we already know the next/prev entries and we can
 * generate better code by using them directly rather than
 * using the generic single-entry routines.
 */
struct acl_list_head {
    struct acl_list_head *next, *prev;
};

typedef struct acl_list_head acl_list_t;

#define ACL_LIST_HEAD_INIT(name) { &(name), &(name) }

#define ACL_CH_LIST_HEAD(name) \
    acl_list_t name = ACL_LIST_HEAD_INIT(name)

#define ACL_INIT_LIST_HEAD(ptr) do { \
    (ptr)->next = (ptr); (ptr)->prev = (ptr); \
} while (0)

/*
 * Insert a new entry between two known consecutive entries.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static void __acl_list_add(acl_list_t* new, acl_list_t* prev, acl_list_t* next)
{
    next->prev = new;
    new->next = next;
    new->prev = prev;
    prev->next = new;
}

/**
 * acl_list_add - add a new entry
 * @new: new entry to be added
 * @head: list head to add it after
 *
 * Insert a new entry after the specified head.
 * This is good for implementing stacks.
 */
inline static void acl_list_add(acl_list_t* new, acl_list_t* head)
{
    __acl_list_add(new, head, head->next);
}

/**
 * acl_list_add_tail - add a new entry
 * @new: new entry to be added
 * @head: list head to add it before
 *
 * Insert a new entry before the specified head.
 * This is useful for implementing queues.
 */
inline static void acl_list_add_tail(acl_list_t* new, acl_list_t* head)
{
    __acl_list_add(new, head->prev, head);
}

/*
 * Delete a list entry by making the prev/next entries
 * point to each other.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
inline static void __acl_list_del(acl_list_t* prev, acl_list_t* next)
{
    next->prev = prev;
    prev->next = next;
}

/**
 * acl_list_del - deletes entry from list.
 * @entry: the element to delete from the list.
 * Note: list_empty on entry does not return true after this, the entry is in an undefined state.
 */
inline static void acl_list_del(acl_list_t* entry)
{
    __acl_list_del(entry->prev, entry->next);
}

/**
 * acl_list_del_init - deletes entry from list and reinitialize it.
 * @entry: the element to delete from the list.
 */
inline static void acl_list_del_init(acl_list_t* entry)
{
    __acl_list_del(entry->prev, entry->next);
    ACL_INIT_LIST_HEAD(entry);
}

/**
* acl_list_empty - tests whether a list is empty
* @head: the list to test.
*/
inline static int acl_list_empty(acl_list_t* head)
{
    return head->next == head;
}

#endif
