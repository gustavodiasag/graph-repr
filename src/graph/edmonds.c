#include <string.h>

#include "graph/edmonds.h"
#include "utils/stack.h"
#include "utils/vertex.h"

/** FIXME: Describe function. */
static void _edmonds(const Graph* g);
/** FIXME: Describe function. */
static void _find_min_parents(const Graph* g, size_t* parents);
/** FIXME: Describe function. */
static bool _find_cycle(const size_t* parents, size_t child, Stack* cycle);

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

static void _edmonds(const Graph* g)
{
    size_t parents[graph_v(g) + 1];
    memset(parents, 0, sizeof(parents));

    _find_min_parents(g, parents);

    Stack cycle = stack_new(sizeof(size_t), int_match, NULL);

    for (size_t i = 1; i < (graph_v(g) + 1); i++) {
        if (_find_cycle(parents, i, &cycle)) {
            break;
        }
    }
    if (stack_is_empty(&cycle)) {
        return;
    }
}

static void _find_min_parents(const Graph* g, size_t* parents)
{
    size_t min_weights[graph_v(g) + 1];
    memset(min_weights, 0, sizeof(min_weights));

    for (ListElt* v = list_head(&g->_adjlists); v; v = list_next(v)) {
        const AdjList* adj = (AdjList*)list_data(v);

        for (ListElt* w = list_head(&adj->_adj); w; w = list_next(w)) {
            const Vertex* vertex = (Vertex*)list_data(w);
            
            if (!min_weights[vertex_data(vertex)] ||
                (min_weights[vertex_data(vertex)] &&
                    vertex_weight(vertex) < min_weights[vertex_data(vertex)]))
            {
                min_weights[vertex_data(vertex)] = vertex_weight(vertex);
                parents[vertex_data(vertex)] = vertex_data((Vertex*)adj->_vertex);
            }
        }
    }
}

static bool _find_cycle(const size_t* parents, size_t child, Stack* cycle)
{
    Stack aux = stack_new(sizeof(size_t), int_match, NULL);
    stack_push(&aux, &child);
    
    size_t parent = parents[child];
    while (parent != 0) {
        if (!stack_contains(&aux, &parent)) {
            stack_push(&aux, &parent);
#ifdef DEBUG_LOG
            stack_print(&aux, vertex_print);
#endif
            parent = parents[parent];
        } else {
            size_t* cycle_vertex;

            while (aux.match(stack_peek(&aux), &parent) != 0) {
                stack_pop(&aux, (void**)&cycle_vertex);
                stack_push(cycle, cycle_vertex);
            }
            stack_push(cycle, &parent);

            return true;
        }
    }
    stack_destroy(&aux);

    return false;
}