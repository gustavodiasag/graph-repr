#include <string.h>

#include "graph.h"

void graph_init(Graph* g, size_t vsize,
                int (*match)(const void*, const void*),
                void (*destroy)(void*))
{
    g->_v = 0;
    g->_e = 0;
    g->_vsize = vsize;
    g->_match = match;
    g->_destroy = destroy;
    // Initialize adjacency list.
    set_init(&g->_adjlists, vsize, match, NULL);
}

void graph_destroy(Graph* g)
{
    AdjList* adj;
    // Remove each adjacency list.
    while (list_size(&g->_adjlists) > 0) {
        if (list_rm_next(&g->_adjlists, NULL, (void**)&adj)) {
            set_destroy(&adj->_adj);

            if (g->_destroy) {
                g->_destroy(adj->_vertex);
            }
            free(adj);
        }
    }
    list_destroy(&g->_adjlists);
    memset(g, 0, sizeof(Graph));
}

bool graph_ins_v(Graph* g, const void* data)
{
    // Insertion of duplicate vertices is not allowed.
    if (set_is_mem(&g->_adjlists, data)) {
        return false;
    }
    AdjList* adj = (AdjList*)malloc(sizeof(AdjList));
    assert(adj);

    memcpy(adj->_vertex, (void*)data, graph_vsize(g));
    set_init(&adj->_adj, g->_vsize, g->_match, NULL);

    if (!set_ins(&g->_adjlists, adj)) {
        return false;
    }
    g->_v++;

    return true;
}

bool graph_ins_e(Graph* e, const void* data1, const void* data2)
{
    if ()
}