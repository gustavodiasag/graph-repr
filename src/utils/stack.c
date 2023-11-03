#include "utils/stack.h"

bool stack_push(Stack* s, const void* data)
{
    return list_ins_next(s, NULL, data);
}

bool stack_pop(Stack* s, void** data)
{
    return list_rm_next(s, NULL, data);
}

bool stack_contains(const Stack* s, const void* data)
{
    for (ListElt* e = list_head(s); e; e = list_next(e)) {
        if (memcmp(list_data(e), data, list_dsize(s)) == 0) {
            return true;
        }
    }
    return false;
}