#ifndef GRAPH_H
#define GRAPH_H

#include "common.h"
#include "set.h"

/** Structure representing an adjacency list. */
typedef struct _AdjList {
    void*       _vertex;
    Set         _adj;
} AdjList;

/** Structure representing a graph. */
typedef struct _Graph {
    Set         _adjlists;
    size_t      _vsize;
    size_t      _v;
    size_t      _e;

    int         (*_match)(const void*, const void*);
    void        (*_destroy)(void*);
} Graph;

/**
 * Evaluates the list of adjacency list structures of a graph specified by `g`.
 */
#define graph_adjlists(g) ((g)->_adjlists)

/**
 * Evaluates the size in bytes of the data stored in each vertex of a graph
 * specified by `g`.
 */
#define graph_vsize(g) ((g)->_vsize)

/** Evaluates the number of vertices in a graph specified by `g`. */
#define graph_v(g) ((g)->_v)

/** Evaluates the number of edges in a graph specified by `g`. */
#define graph_e(g) ((g)->_e)

/**
 * Initializes a graph specified by `g`. This operation must be called for
 * a graph in order for it to be used in any context.
 * 
 * The `vsize` parameter provides the number of bytes necessary for the data to
 * be stored in each element of the graph's vertices.
 * 
 * The `match` parameter is a function used by graph operations to compare if
 * two vertices match. This function should return 1 if `key1 > key2`, 0 if
 * `key1 == key2` or -1 if `key1 < key2`.
 * 
 * The `destroy` parameter must provide a way to free dynamic allocations in
 * the case where the graph's vertices store heap-allocated data. If the graph
 * elements do not contain data that must be freed, `destroy` must be set to
 * NULL.
 */
void graph_init(Graph* g, size_t vsize,
                int (*match)(const void*, const void*),
                void (*destroy)(void*));

/**
 * Destroys a graph specified by `g`. No operation is allowed to happen in the
 * graph after a call to it.
 */
void graph_destroy(Graph* g);

/**
 * Inserts a vertex that contains a pointer to `data` into a graph specified by
 * `g`.
 * 
 * Returns true is inserting the vertex is successfull, or false otherwise.
 */
bool graph_ins_v(Graph* g, const void* data);

/**
 * Inserts an edge from a vertex specified by `data1` to a vertex specified by
 * `data2` into a graph specified by `g`. Both vertices must have been inserted
 * previously using `graph_ins_v`.
 * 
 * Returns true if inserting the edge is successfull, or false otherwise.
 */
bool graph_ins_e(Graph* g, const void* data1, const void* data2);

/**
 * Removes a vertex matching `data` from a graph specified by `g`. Once
 * finished, `data` points to the data stored in the vertex that was removed.
 * 
 * Returns true if removing the vertex is successfull, or false otherwise.
 */
bool graph_rm_v(Graph* g, void** data);

/**
 * Removes an edge from `data1` to `data2` from a graph specified by `g`. Once
 * finished, `data2` points to the data stored in the adjacency list of the
 * vertex specified by `data1`.
 * 
 * Returns true if removing the edge is successfull, or false otherwise.
 */
bool graph_rm_e(Graph* g, void** data1, void** data2);

/**
 * Retrieves all the vertices that are adjacent to the vertex specified by
 * `data` in a graph specified by `g`. The adjacent vertices are returned in an
 * adjacent list specified by `adjt`.
 * 
 * Returns true if retrieving the adjacent list is successfull, or false
 * otherwise.
 */
bool graph_adjlist(const Graph* g, const void* data, AdjList** adj);

/**
 * Determines whether a vertex specified by `data2` is adjacent to a vertex
 * specified by `data1` in a graph specified by `g`.
 * 
 * Returns true if the second vertex is adjacent to the first, or false
 * otherwise.
 */
bool graph_is_adj(const Graph* g, const void* data1, const void* data2);

#endif