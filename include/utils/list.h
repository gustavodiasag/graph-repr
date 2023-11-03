#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

#include "common.h"

/** Structure representing a singly linked list element. */
typedef struct _ListElt
{
    void*               _data;
    struct _ListElt*    _next;
} ListElt;

/** Structure representing a singly linked list. */
typedef struct _List
{
    ListElt*            _head;
    ListElt*            _tail;
    size_t              _size;
    size_t              _dsize;

    int32_t             (*match)(const void*, const void*);
    void                (*_destroy)(void*);
} List;

/** 
 * Evaluates the element at the head of a singly linked list specified by
 * `l`.
 */
#define list_head(l) ((l)->_head)

/**
 * Evaluates the element at the tail of a singly linked list specified by
 * `l`.
 */
#define list_tail(l) ((l)->_tail)

/**
 * Evaluates the number of elements in a singly linked list list specified by
 * `l`.
 */
#define list_size(l) ((l)->_size)

/** 
 * Evaluates the size in byes of the data stored on each element of the list.
 */
#define list_dsize(l) ((l)->_dsize)

/**
 * Evaluates whether the element specified by `e` is the head of a linked list
 * specified by `l`.
 */
#define list_is_head(l, e) ((l)->_head == (e))

/**
 * Evaluates whether the element specified by `e` os the tail of a linked list
 * specified by `l`.
 */
#define list_is_tail(l, e) ((l)->_tail == (e))

/** Evaluates the data stored in the list element specified by `e`. */
#define list_data(e) ((e)->_data)

/** Evaluates the data stored in the list element specified by `e`. */
#define list_next(e) ((e)->_next)

/** FIXME: Describe function. */
List list_new(size_t dsize,
              int (*match)(const void*, const void*),
              void (*destroy)(void*));

/**
 * Initializes a singly linked-list specified by `list`. This operation must be
 * called for a list in order for it to be used in any context.
 * 
 * The `dsize` parameter provides the number of bytes necessary for the data to
 * be stored in each element of the list.
 * 
 * The `destroy` parameter must provide a way to free dynamic allocations in
 * the case where the list stores heap-allocated data. If the list elements do
 * no contain data that must be freed, `destroy` shall be set to NULL. 
 */
void list_init(List* l, size_t dsize,
               int (*match)(const void*, const void*),
               void (*destroy)(void*));

/**
 * Destroys a singly linked-list specified by `list`. No operation is allowed
 * to happen in a list after a call to it.
 * 
 * Removes all the elements from the singly linked-list calling the function
 * `destroy, defined in `list-init`.
 */
void list_destroy(List* l);

/**
 * Inserts the element right after the one specified by `e` from a singly
 * linked list specified by `l`. If `e` is NULL, the new element is inserted at
 * the head of the list. 
 * 
 * Returns true if the element is successfully inserted, or false otherwise.
 */
bool list_ins_next(List* l, ListElt* e, const void* data);

/**
 * Removes the element right after the one specified by `e` from a singly
 * linked linked list specified by `l`. If `e` is NULL, the element at the head
 * of the list is removed. Once finished, `data` points to the data stored in
 * the element removed.
 * 
 * Returns true if the element is successfully removed, or false otherwise.
 */
bool list_rm_next(List* l, ListElt* e, void** data);

/** FIXME: Describe function. */
bool list_is_empty(const List* l);

/** FIXME: Describe function. */
void list_print(const List* l, void (*f)(const void*));

#endif