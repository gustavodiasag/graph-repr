#include "utils/stack.h"

bool stack_push(Stack* s, const void* data)
{
    return list_ins_next(s, NULL, data);
}

bool stack_pop(Stack* s, void** data)
{
    return list_rm_next(s, NULL, data);
}