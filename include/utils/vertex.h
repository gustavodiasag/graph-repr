#ifndef VERTEX_H
#define VERTEX_H

#include <stdlib.h>

#include "common.h"

/** Structure representing a weighted vertex. */
typedef struct _Vertex
{
    size_t      _data;
    size_t      _weight;
} Vertex;

#define vertex_data(v) (((Vertex*)v)->_data)

#define vertex_weight(v) (((Vertex*)v)->_weight)

int vertex_match(const void* v1, const void* v2);

int vertex_compare(const void* v1, const void* v2);

void vertex_print(const void* v);

#endif