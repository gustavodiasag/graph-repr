#include "vertex.h"

int vertex_match(const void* v1, const void* v2)
{
    return vertex_data((Vertex*)v1) - vertex_data((Vertex*)v2);
}

int vertex_compare(const void* v1, const void* v2)
{
#ifdef DEBUG_LOG
    printf("vertex_compare: v1(%d, %zu), v2(%d, %zu).\n",
        vertex_data((Vertex*)v1), vertex_weight((Vertex*)v1),
        vertex_data((Vertex*)v2), vertex_weight((Vertex*)v2));
#endif
    return vertex_weight((Vertex*)v1) - vertex_weight((Vertex*)v2);
}

void vertex_print(const void* v)
{
    printf("v: %d, w: %zu", vertex_data((Vertex*)v), vertex_weight((Vertex*)v));
}