#include <string.h>

#ifdef DEBUG_LOG

#include <stdio.h>

#endif

#include "graph.h"

/** FIXME: Describe function. */
static bool _graph_ins_v(Graph* g, const void* v);

void graph_init(Graph* g, size_t vsize,
                int (*match)(const void*, const void*),
                void (*destroy)(void*))
{
    g->_v = 0;
    g->_e = 0;
    g->_vsize = vsize;
    g->match = match;
    g->_destroy = destroy;
    // Initialize adjacency list.
    list_init(&g->_adjlists, sizeof(AdjList), NULL);
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

static AdjList* _adj_alloc(const Graph* g)
{
    AdjList* adj = (AdjList*)malloc(sizeof(AdjList));
    assert(adj);

    adj->_vertex = (void*)malloc(sizeof(graph_vsize(g)));
    assert(adj->_vertex);

    return adj;
}

static bool _graph_ins_v(Graph* g, const void* v)
{
    // Duplicate vertices are not allowed.
    for (ListElt* e = list_head(&g->_adjlists); e; e = list_next(e)) {
        if (g->match(v, ((AdjList*)list_data(e))->_vertex) == 0) {
#ifdef DEBUG_LOG
            printf("graph_ins_v: Vertex already in the graph.\n");
#endif      
            return false;
        }
    }
    AdjList* adj = _adj_alloc(g);
    
    memcpy(adj->_vertex, v, graph_vsize(g));
    set_init(&adj->_adj, graph_vsize(g), g->match, NULL);

    if (!list_ins_next(&g->_adjlists, list_tail(&g->_adjlists), adj)) {
#ifdef DEBUG_LOG
        printf("graph_ins_v: Error while inserting vertex.\n");
#endif
        return false;
    }
    g->_v++;
    
    return true;
}

bool graph_ins_e(Graph* g, const void* v, const void* w)
{
    _graph_ins_v(g, v);
    _graph_ins_v(g, w);

    ListElt* e;
    for (e = list_head(&g->_adjlists); e; e = list_next(e)) {
        if (g->match(v, ((AdjList*)list_data(e))->_vertex) == 0) {
#ifdef DEBUG_LOG
            printf("graph_ins_e: Edge's tail found in the graph.\n");
#endif
            break;
        }
    }
    assert(e);

    if (!set_ins(&((AdjList*)list_data(e))->_adj, w)) {
#ifdef DEBUG_LOG
        printf("graph_ins_e: Error while inserting edge.\n");
#endif
        return false;
    }
    g->_e++;
    
    return true;
}

void graph_print(const Graph* g, void (*f)(const void*))
{
    for (ListElt* e = list_head(&g->_adjlists); e; e = list_next(e)) {
        f(((AdjList*)list_data(e))->_vertex);
        printf("\t-> ");
        
        set_print(&((AdjList*)list_data(e))->_adj, f);
        printf("\n");
    }
}