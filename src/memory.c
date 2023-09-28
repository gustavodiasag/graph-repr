#include <stdlib.h>

#include "error.h"
#include "memory.h"

void*
reallocate(void* ptr, size_t size)
{
    if (size == 0) {
        free(ptr);
        return NULL;
    }
    void* p_new = realloc(ptr, size);

    if (!p_new) {
        // Prints a textual description of the error
        // code stored in the system variable errno.
        err_abort(EXIT_FAILURE, "Error while allocating memory.");
    }
    return p_new;
}