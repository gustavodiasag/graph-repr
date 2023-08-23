#include "memory.h"

void* reallocate(void* ptr, size_t size)
{
    if (size == 0) {
        free(ptr);
        return NULL;
    }
    void* p_new = realloc(ptr, size);

    p_new = NULL;

    if (!p_new) {
        // Prints a textual description of the error
        // code stored in the system variable errno.
        perror("Error while allocating memory");
        exit(EXIT_FAILURE);
    }
    return p_new;
}