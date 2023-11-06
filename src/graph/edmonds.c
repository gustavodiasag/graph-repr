#include <string.h>

#include "graph/edmonds.h"
#include "utils/stack.h"
#include "utils/vertex.h"

/** 
 * Evaluates the range of vertices that can be stored in a graph specified by
 * `g`.
 */
#define VERTEX_RANGE(g) ((graph_v(g) + 1))

/**
 * Recursive version of `edmonds`. The `contracted` parameter is a graph with
 * a cycle contracted to a unique vertex, so that it can be used in further
 * contractions and expansions.
 */
static void _edmonds(const Graph* g, const Graph* contracted, Graph* a);

/**
 * For every vertex in a graph specified by `g`, identifies the parent vertex
 * containing the minimum edge towards it.
 * 
 * The `parents` parameter is a list of vertices inside which the minimum
 * parents are stored. The index of the list corresponds to the head of the
 * minimum edge and the value at that index, its tail.
 */
static void _find_min_parents(const Graph* g, Vertex** parents);

/**
 * Checks whether a vertex specified by `v` is the head of a minimum edge to
 * a determined position of minimum parents list specified by `parents`.
 * 
 * Returns true if the vertex is the head, or false otherwise.
 */
static bool _is_min(Vertex** parents, const Vertex* v);

/**
 * Generates a representation of a minimum edge that comes from the initial
 * vertex of an adjacency list specified by `parent` and goes to a vertex
 * specified by `child`.
 * 
 * Returns a pointer to the new representation. 
 */
static Vertex* _min_edge(const AdjList* parent, const Vertex* child);

/** 
 * Searches for a cycle given a list of minimum parents specified by `parents`
 * starting from a vertex identified by `child`, storing the resulting cycle
 * in a stack data structure specified by `cycle`.
 * 
 * Returns true if a cycle was found, or false otherwise.
 */
static bool _find_cycle(Vertex** parents, size_t child, Stack* cycle);

/**
 * Contracts a cycle from a graph specified by `g`, storing the resulting
 * contraction in a graph specified by `contracted`.
 * 
 * The `cycle` paramenter stores the vertices contained by the cycle.
 * 
 * The `parents` parameter stores the minimum incoming edges of each vertex
 * in the graph `g`.
 */
static void _contract_cycle(const Graph*    g,
                            Graph*          contracted,
                            Stack*          cycle,
                            Vertex**        parents);

/**
 * Expands a cycle from a graph specified by `g`, storing the resulting
 * expansion directly to a spanning arborescence specified by `a`..
 * 
 * The `cycle` paramenter stores the vertices contained by the cycle.
 * 
 * The `parents` parameter stores the minimum incoming edges of each vertex
 * in the graph `g`.
 */
static void _expand_cycle(const Graph*  g,
                          Graph*        a,
                          Stack*        cycle,
                          Vertex**      parents);

/** 
 * Checks if there is an edge going from `v` to `w` in a graph specified by
 * `g`.
 */
static bool search_edge(const Graph* g, const void* v, const void* w);

/** 
 * Helper function to compare two `size_t` integers specified by `i` and `j`.
 * 
 * Returns a negative number if `i` is lower than `j`, 0 if `i` is equal to `j`
 * or a positive number if `i` is greater than `j`.
 */
static int int_match(const void* i, const void* j);

void edmonds(const Graph* g, Graph* a)
{
    _edmonds(g, g, a);
}

static void _edmonds(const Graph* g, const Graph* contraction, Graph* a)
{
    Vertex* parents[VERTEX_RANGE(g)];
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
    _expand_cycle(g, a, &cycle, parents);
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
    size_t contracted_vertex = *(size_t*)stack_peek(cycle);

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

static void _expand_cycle(const Graph*  g,
                          Graph*        a,
                          Stack*        cycle,
                          Vertex**      parents)
{
    size_t* contracted_vertex = (size_t*)stack_peek(cycle);
    Vertex* cycle_breakpoint;

    bool visited[VERTEX_RANGE(g)];
    memset(visited, false, sizeof(visited));

    if (contracted_vertex) {
        cycle_breakpoint = parents[*contracted_vertex];
    }

    size_t src, dest;
    for (size_t i = 1; i < VERTEX_RANGE(g); i++) {
        dest = i;
        src = parents[dest] ? vertex_data(parents[dest]) : 0;
        
        while (src && !visited[dest]) {
            Vertex exp_src = {
                ._data = src,
                ._weight = parents[src] ? vertex_weight(parents[src]) : 0
            };
            Vertex exp_dest = {
                ._data = dest,
                ._weight = parents[dest] ? vertex_weight(parents[dest]) : 0
            };
            if (search_edge(g, &exp_src, &exp_dest)) {
                if (contracted_vertex) {
                    if (int_match(&vertex_data(cycle_breakpoint), &vertex_data(&exp_src)) &&
                        int_match(contracted_vertex, &vertex_data(&exp_dest)))
                    {
                        if (!search_edge(a, &exp_src, &exp_dest)) {
                            graph_ins_e(a, &exp_src, &exp_dest);
                        }
                    }
                } else {
                    if (!search_edge(a, &exp_src, &exp_dest)) {
                        graph_ins_e(a, &exp_src, &exp_dest);
                    }
                }
            }
            visited[dest] = true;
            dest = src;
            src = parents[dest] ? vertex_data(parents[dest]) : 0;
        }
        visited[dest] = true;
    }
}

static bool search_edge(const Graph* g, const void* v, const void* w)
{
    AdjList *adj = NULL;

    for (ListElt* e = list_head(&g->_adjlists); e; e = list_next(e)) {
        if (g->match(((AdjList*)list_data(e))->_vertex, v) == 0) {
            adj = (AdjList*)list_data(e);
            break;
        }
    }
    if (!adj) {
        return false;
    }
    for (ListElt* e = list_head(&adj->_adj); e; e = list_next(e)) {
        if (g->match(list_data(e), w) == 0) {
            ((Vertex*)w)->_weight = vertex_weight(list_data(e));
            return true;
        }
    }
    return false;
}

static int int_match(const void* i, const void* j)
{
    return *(size_t*)i - *(size_t*)j;
}

static void int_print(const void*i)
{
    printf("%zu", *(size_t*)i);
}