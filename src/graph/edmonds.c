#include <string.h>

#include "graph/edmonds.h"
#include "utils/stack.h"
#include "utils/vertex.h"

/** FIXME: Describe function. */
static void _edmonds(const Graph* g, const Graph* contracted, Graph* a);
/** FIXME: Describe function. */
static void _find_min_parents(const Graph* g, Vertex** parents);
/** FIXME: Describe function. */
static bool _is_min(Vertex** parents, const Vertex* v);
/** FIXME: Describe function. */
static Vertex* _min_edge(const AdjList* parent, const Vertex* child);
/** FIXME: Describe function. */
static bool _find_cycle(Vertex** parents, size_t child, Stack* cycle);
/** FIXME: Describe function. */
static void _contract_cycle(const Graph*    g,
                            Graph*          contracted,
                            Stack*          cycle,
                            Vertex**        parents);
/** FIXME: Describe function. */
static int int_match(const void* i, const void* j);

static void int_print(const void *i);

void edmonds(const Graph* g, Graph* a)
{
    _edmonds(g, g, a);
}

static void _edmonds(const Graph* g, const Graph* contraction, Graph* a)
{   
    Vertex* parents[graph_v(g) + 1];
    memset(parents, NULL, sizeof(parents));

    _find_min_parents(contraction, parents);

    Stack cycle = stack_new(sizeof(size_t), int_match, NULL);

    for (size_t i = 1; i < (graph_v(g) + 1); i++) {
        if (_find_cycle(parents, i, &cycle)) {
            break;
        }
    }
    // The given graph contains at least one cycle.
    if (!stack_is_empty(&cycle)) {
        Graph contracted = graph_new(graph_vsize(g), g->match, NULL);

        _contract_cycle(contraction, &contracted, &cycle, parents);
        _edmonds(g, &contracted, a);
    }
    // expand_cycle(g, a, &cycle, parents);
}

static void _find_min_parents(const Graph* g, Vertex** parents)
{
    for (ListElt* v = list_head(&g->_adjlists); v; v = list_next(v)) {
        const AdjList* adj = (AdjList*)list_data(v);

        for (ListElt* w = list_head(&adj->_adj); w; w = list_next(w)) {
            const Vertex* vertex = (Vertex*)list_data(w);
            
            if (_is_min(parents, vertex)) {
                parents[vertex_data(vertex)] = _min_edge(adj, vertex);
            }
        }
    }
}

static bool _is_min(Vertex** parents, const Vertex* v)
{
    return parents[vertex_data(v)] == NULL ||
           vertex_weight(v) < vertex_weight(parents[vertex_data(v)]);
}

static Vertex* _min_edge(const AdjList* parent, const Vertex* child)
{
    Vertex* min = (Vertex*)malloc(sizeof(Vertex));
#ifdef DEBUG_LOG
    printf("_min_edge: (%zu, %zu).\n",
        vertex_data(parent->_vertex), vertex_weight(child));
#endif
    min->_data = vertex_data(parent->_vertex);
    min->_weight = vertex_weight(child);

    return min;
}

static bool _find_cycle(Vertex** parents, size_t child, Stack* cycle)
{
    Stack aux = stack_new(sizeof(size_t), int_match, NULL);
    stack_push(&aux, &child);
    
    Vertex* parent = parents[child];
    while (parent != 0) {
        if (!stack_contains(&aux, &vertex_data(parent))) {
            stack_push(&aux, &vertex_data(parent));
            parent = parents[vertex_data(parent)];
        } else {
            size_t* cycle_vertex;

            while (aux.match(stack_peek(&aux), &vertex_data(parent)) != 0) {
                stack_pop(&aux, (void**)&cycle_vertex);
                stack_push(cycle, cycle_vertex);
            }
            stack_push(cycle, &vertex_data(parent));

            return true;
        }
    }
    return false;
}

static void _contract_cycle(const Graph*    g,
                            Graph*          contracted,
                            Stack*          cycle,
                            Vertex**        parents)
{
    size_t contracted_vertex = *(size_t*)(stack_peek(cycle));

    for (ListElt* v = list_head(&g->_adjlists); v; v = list_next(v)) {
        const AdjList* src = (AdjList*)list_data(v);

        for (ListElt* w = list_head(&src->_adj); w; w = list_next(w)) {    
            const Vertex* dest = (Vertex*)list_data(w);
            
            if (stack_contains(cycle, &vertex_data(src->_vertex)) &&
                stack_contains(cycle, &vertex_data(dest)))
            {
                continue;
            } else {
                Vertex cont_src = {
                    ._data      = vertex_data(src->_vertex),
                    ._weight    = vertex_weight(src->_vertex)
                };
                Vertex cont_dest = {
                    ._data      = vertex_data(dest),
                    ._weight    = vertex_weight(dest) 
                };

                if (stack_contains(cycle, &vertex_data(src->_vertex)) &&
                    !stack_contains(cycle, &vertex_data(dest)))
                {
                    cont_src._data = contracted_vertex; 
                } else if (!stack_contains(cycle, &vertex_data(src->_vertex)) &&
                           stack_contains(cycle, &vertex_data(dest)))
                {
                    cont_dest._data = contracted_vertex;
                    cont_dest._weight =cont_dest._weight - vertex_weight(parents[vertex_data(dest)]);
                }
                graph_ins_e(contracted, &cont_src, &cont_dest);
            }
        }
    }
}

static int int_match(const void* i, const void* j)
{
    return *(size_t*)i - *(size_t*)j;
}

static void int_print(const void*i)
{
    printf("%zu", *(size_t*)i);
}