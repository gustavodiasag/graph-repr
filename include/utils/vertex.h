#ifndef VERTEX_H
#define VERTEX_H

#include <stdlib.h>

#include "common.h"

typedef struct _Vertex
{
    int         _data;
    size_t      _weight;
} Vertex;

#define vertex_data(v) ((v)->_data)

#define vertex_weight(v) ((v)->_weight)

int vertex_match(const void* v1, const void* v2);

int vertex_compare(const void* v1, const void* v2);

void vertex_print(const void* v);

#endif