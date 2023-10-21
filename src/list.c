#include <string.h>

#include "list.h"

void list_init(List* l, size_t esize, void (*destroy)(void*))
{
    l->_head = NULL;
    l->_tail = NULL;
    l->_size = 0;
    l->_esize = esize;
    l->_destroy = destroy;
}

void list_destroy(List* l)
{
    void* data;
    while (list_size(l) > 0) {
        if (list_rm_next(l, NULL, (void**)&data) && l->_destroy) {
            l->_destroy(data);
        }
    }
    memset(l, 0, sizeof(List));
}

bool list_ins_next(List* l, ListElt* e, const void* data)
{
    ListElt* new = (ListElt*)malloc(sizeof(ListElt));
    assert(new);

    memcpy(new->_data, (void*)data, l->_esize);

    if (!e) {
        // Head insertion.
        if (!list_size(l)) {
            l->_tail = new;
        }
        new->_next = l->_head;
        l->_head = new;
    } else {
        if (!e->_next) {
            // Tail insertion.
            l->_tail = new;
        }
        new->_next = e->_next;
        e->_next = new;
    }
    l->_size++;

    return true;
}

bool list_rm_next(List* l, ListElt* e, void** data)
{
    ListElt* old;
    // Deletion is not allowed in a non-empty list.
    if (!list_size(l)) {
        return false;
    }
    if (!e) {
        // Head deletion.
        *data = l->_head->_data;
        old = l->_head;
        l->_head = l->_head->_next;

        if (!list_size(l)) {
            l->_tail = NULL;
        }
    } else {
        if (!e->_next) {
            return false;
        }
        *data = e->_next->_data;
        old = e->_next;
        e->_next = e->_next->_next;

        if (!e->_next) {
            l->_tail = e;
        }
    }
    free(old);
    l->_size--;

    return true;
}