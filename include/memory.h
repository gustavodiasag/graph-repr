#pragma once

#include "common.h"

#define alloc(type, size) \
    (type*)reallocate(NULL, sizeof(type) * size)

#define free_array(type, ptr) \
    reallocate(ptr, 0)

/// @brief Allocates, frees, shrinks and expands
/// the size of a dynamic allocation.
/// @param ptr pointer to the block of memory
/// @param new_size size to be allocated
/// @return pointer to the allocated memory
void* reallocate(void* ptr, size_t size);