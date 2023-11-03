#include <string.h>

#include "utils/set.h"

void set_init(Set* s, size_t dsize,
              int (*match)(const void*, const void*),
              void (*destroy)(void*))
{
    list_init(s, dsize, destroy);
    s->_match = match;
}

bool set_ins(Set* s, const void* data)
{
    // Duplicates are not allowed.
    if (set_is_mem(s, data)) {
        return false;
    }
    return list_ins_next(s, list_tail(s), data);
}

bool set_rm(Set* s, void** data)
{
    ListElt* prev;
    ListElt* mem;
    for (mem = list_head(s); mem; mem = list_next(mem)) {
        if (s->_match(*data, list_data(mem))) {
            break;
        }
        prev = mem;
    }
    if (!mem) {
        return false;
    }
    return list_rm_next(s, prev, data);
}

bool set_union(Set* s_u, const Set* s1, const Set* s2)
{
    set_init(s_u, s1->_dsize, s1->_match, NULL);
    
    void* data;
    for (ListElt* mem = list_head(s1); mem; mem = list_next(mem)) {
        data = list_data(mem);

        if (!list_ins_next(s_u, list_tail(s_u), data)) {
            set_destroy(s_u);
            return false;
        }
    }
    for (ListElt* mem = list_head(s2); mem; mem = list_next(mem)) {
        if (set_is_mem(s1, list_data(mem))) {
            continue;
        } else {
            data = list_data(mem);

            if (!list_ins_next(s_u, list_tail(s_u), data)) {
                set_destroy(s_u);
                return false;
            }
        }
    }
    return true;
}

bool set_insertec(Set* s_i, const Set* s1, const Set* s2)
{
    set_init(s_i, s1->_dsize, s1->_match, NULL);

    void* data;
    for (ListElt* mem = list_head(s1); mem; mem = list_next(mem)) {
        if (set_is_mem(s2, list_data(mem))) {
            data = list_data(mem);

            if (!list_ins_next(s_i, list_tail(s_i), data)) {
                set_destroy(s_i);
                return false;
            }
        }
    }
    return true;
}

bool set_diff(Set* s_d, const Set* s1, const Set* s2)
{
    set_init(s_d, s1->_dsize, s1->_match, NULL);

    void* data;
    for (ListElt* mem = list_head(s1); mem; mem = list_next(mem)) {
        if (!set_is_mem(s2, list_data(mem))) {
            data = list_data(mem);

            if (!list_ins_next(s_d, list_tail(s_d), data)) {
                set_destroy(s_d);
                return false;
            }
        }
    }
    return true;
}

bool set_is_mem(const Set* s, const void* data)
{
    for (ListElt* mem = list_head(s); mem; mem = list_next(mem)) {
        if (s->_match(data, list_data(mem)) == 0) {
            return true;
        }
    }
    return false;
}

bool set_is_sub(const Set* s1, const Set* s2)
{
    if (list_size(s1) > list_size(s2)) {
        return false;
    }

    for (ListElt* mem = list_head(s1); mem; mem = list_next(mem)) {
        if (!set_is_mem(s2, list_data(mem))) {
            return false;
        }
    }
    return true;
}

bool set_is_eq(const Set* s1, const Set* s2)
{
    if (set_size(s1) != set_size(s2)) {
        return false;
    }
    // Sets of the same size are equal if they are subsets.
    return set_is_sub(s1, s2);
}

void set_print(const Set* s, void(*f)(const void*))
{
    ListElt* mem;
    for (mem = list_head(s); mem != list_tail(s); mem = list_next(mem)) {
        f(mem->_data);
        printf("\t->");
    }
    if (mem) {
        f(mem->_data);
    }
}