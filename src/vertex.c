#include "vertex.h"

int vertex_match(const void* v1, const void* v2)
{
    return vertex_data((Vertex*)v1) - vertex_data((Vertex*)v2);
}

void vertex_print(const void* v)
{
    printf("v: %d, w: %zu", vertex_data((Vertex*)v), vertex_weight((Vertex*)v));
}