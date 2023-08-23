#pragma once

#include "common.h"
#include <stdlib.h>

#define ALLOC(type, size) \
    (type *)reallocate(NULL, sizeof(type) * size)

#define FREE(type, ptr) \
    reallocate(ptr, 0)

void* reallocate(void* ptr, size_t size);