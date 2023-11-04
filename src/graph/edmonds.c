#include <string.h>

#include "graph/edmonds.h"
#include "utils/stack.h"
#include "utils/vertex.h"

typedef struct _Replacement {
    size_t orig_
} Replacement;

/** FIXME: Describe function. */
static Vertex** _edmonds(const Graph* g);
/** FIXME: Describe function. */
static void _find_min_parents(const Graph* g, Vertex** parents);
/** FIXME: Describe function. */
static bool _is_min(size_t* weights, const Vertex* v);
/** FIXME: Describe function. */
static Vertex* _min_edge(const AdjList* parent, const Vertex* child);
/** FIXME: Describe function. */
static bool _find_cycle(Vertex** parents, size_t child, Stack* cycle);
/** FIXME: Describe function. */
static Graph* _contract_cycle(const Graph* g,
                              Vertex** parents,
                              const Stack* cycle);

void edmonds(const Graph* g)
{
    _edmonds(g);
}

static int int_match(const void* i, const void* j)
{
    return *(size_t*)i - *(size_t*)j;
}

static void int_print(const void* data)
{
    printf("%d", *(int*)data);
}

static Vertex** _edmonds(const Graph* g)
{
    graph_print(g, vertex_print);
    printf("\n\n");

    Vertex* parents[graph_v(g) + 1];
    memset(parents, NULL, sizeof(parents));

    _find_min_parents(g, parents);

    Stack cycle = stack_new(sizeof(size_t), int_match, NULL);

    for (size_t i = 1; i < (graph_v(g) + 1); i++) {
        if (_find_cycle(parents, i, &cycle)) {
            break;
        }
    }
    if (stack_is_empty(&cycle)) {
        return parents;
    }
    Graph* contracted = _contract_cycle(g, parents, &cycle);

    return _edmonds(contracted);
}

static void _find_min_parents(const Graph* g, Vertex** parents)
{
    size_t min_weights[graph_v(g) + 1];
    memset(min_weights, 0, sizeof(min_weights));

    for (ListElt* v = list_head(&g->_adjlists); v; v = list_next(v)) {
        const AdjList* adj = (AdjList*)list_data(v);

        for (ListElt* w = list_head(&adj->_adj); w; w = list_next(w)) {
            const Vertex* vertex = (Vertex*)list_data(w);
            
            if (_is_min(min_weights, vertex)) {
                min_weights[vertex_data(vertex)] = vertex_weight(vertex);
                parents[vertex_data(vertex)] = _min_edge(adj, vertex);
            }
        }
    }
}

static bool _is_min(size_t* weights, const Vertex* v)
{
    return weights[vertex_data(v)] == 0 ||
           vertex_weight(v) < weights[vertex_data(v)];
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
    stack_destroy(&aux);

    return false;
}

static Graph* _contract_cycle(const Graph* g,
                              Vertex** parents,
                              const Stack* cycle)
{
    Graph* contracted = (Graph*)malloc(sizeof(Graph));
    graph_init(contracted, graph_vsize(g), g->match, NULL);
    
    Vertex contracted_vertex = {._data = *(size_t*)(stack_peek(cycle)), ._weight = 0};

    for (ListElt* v = list_head(&g->_adjlists); v; v = list_next(v)) {
        const AdjList* adj = (AdjList*)list_data(v);

        for (ListElt* w = list_head(&adj->_adj); w; w = list_next(w)) {    
            const Vertex* vertex = (Vertex*)list_data(w);
            
            if (stack_contains(cycle, &vertex_data(adj->_vertex)) && stack_contains(cycle, &vertex_data(vertex))) {
                continue;
            } else if (stack_contains(cycle, &vertex_data(adj->_vertex))) {
                graph_ins_e(contracted, &contracted_vertex, vertex);
            } else if (stack_contains(cycle, &vertex_data(vertex))) {
                Vertex new = {._data = vertex_data(&contracted_vertex), ._weight = vertex_weight(vertex) - vertex_weight(parents[vertex_data(vertex)])};
                graph_ins_e(contracted, adj->_vertex, &new);
            } else {
                graph_ins_e(contracted, adj->_vertex, vertex);
            }
        }
    }
    return contracted;
}

static void _map_replacement()
{
}