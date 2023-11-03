#include <string.h>

#include "utils/list.h"

/** FIXME: Describe function. */
static ListElt* _elt_alloc(const List* l);

List list_new(size_t dsize, int (*match)(const void*, const void*),
              void (*destroy)(void*))
{
    List l = {0};
    list_init(&l, dsize, match, destroy);

    return l;
}

void list_init(List* l, size_t dsize,
               int (*match)(const void*, const void*),
               void (*destroy)(void*))
{
    l->_head = NULL;
    l->_tail = NULL;
    l->_size = 0;
    l->_dsize = dsize;
    l->match = match;
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
    ListElt* new = _elt_alloc(l);
    memcpy(new->_data, data, list_dsize(l));

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

static ListElt* _elt_alloc(const List* l)
{
    ListElt* e = (ListElt*)malloc(sizeof(ListElt));
    assert(e);

    e->_data = (void*)malloc(list_dsize(l));
    assert(e->_data);

    return e;
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

bool list_is_empty(const List* l)
{
    return list_head(l) == list_tail(l);
}

void list_print(const List* l, void (*f)(const void*))
{
    printf("[");

    ListElt* e;
    for (e = list_head(l); e != list_tail(l); e = list_next(e)) {
        f(e->_data);
        printf(", ");
    }
    if (e) {
        f(e->_data);
    }
    printf("]\n");
}