#pragma once

typedef struct _Graph Graph;

/// @brief Instantiates a directed graph given
/// a set of vertices and edges.
/// @param graph pointer to a graph object.
/// @param fp file with the graph template.
void build_graph(Graph* graph, FILE* fp);

/// @brief Deallocates memory from a graph.
/// @param graph pointer to a graph object.
void free_graph(Graph* graph);

/// @brief Prints out the edges of the given
/// graph to stdout.
/// @param graph pointer to a graph object.
void print_graph(Graph* graph);