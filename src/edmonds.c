#include "edmonds.h"
#include "graph.h"
#include "list.h"
#include "vertex.h"

static int* _find_min_parents(const Graph* g, const Vertex* r);

List* edmonds(const Graph* g, const Vertex* r)
{
    int* min_parents = _find_min_parents(g, r);
}

static int* _find_min_parents(const Graph* g, const Vertex* r)
{
    Vertex* min_parents = (Vertex*)malloc(sizeof(Vertex) * (graph_v(g) + 1));

    for (ListElt* v = list_head(&g->_adjlists); v; v = list_next(v)) {
        AdjList* adj = (AdjList*)list_data(v);

        for (ListElt* w = list_head(&adj->_adj); w; w = list_next(w)) {
            Vertex* vertex = (Vertex*)list_data(w);

            if (min_parents[vertex_data(vertex)] == NULL) {
                min_parents[vertex_data(vertex)] = *(Vertex*)adj->_vertex;
            }
        }
    }
}