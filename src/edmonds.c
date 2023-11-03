#include "edmonds.h"
#include "vertex.h"

/** FIXME: Describe function. */
static void _edmonds(const Graph* g, Graph* a);
/** FIXME: Describe function. */
static void _find_min_parents(const Graph* g, Graph* a);

List* edmonds(const Graph* g)
{
    Graph a = {0};
    graph_init(&a, graph_vsize(g), g->match, NULL);

    _edmonds(g, &a);

    graph_print(&a, vertex_print);

    graph_destroy(&a);
}

static void _edmonds(const Graph* g, Graph* a)
{
    _find_min_parents(g, a);    
}

static void _find_min_parents(const Graph* g, Graph* a)
{
    for (ListElt* v = list_head(&g->_adjlists); v; v = list_next(v)) {
        const AdjList*  tail = (AdjList*)list_data(v);
        Vertex*         head = NULL;

        for (ListElt* w = list_head(&tail->_adj); w; w = list_next(w)) {
            if (!head) {
                head = list_data(w);
            } else if (vertex_compare(list_data(w), head) < 0) {
                head = list_data(w);
            }
        }
        if (head) {
            graph_ins_e(a, tail->_vertex, head);
        }
    }
}