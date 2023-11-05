#include <stdlib.h>

#include "common.h"
#include "graph/edmonds.h"
#include "graph/graph.h"
#include "utils/vertex.h"
#include "utils/list.h"

int main(int argc, char** argv)
{
    if (argc != 2) {
        err_abort("Input file was not provided.");
    }
    
    FILE *f = fopen(argv[1], "r");
    if (!f) {
        err_abort("Unable to open file.");
    }
    Graph g = {0};
    graph_init(&g, sizeof(Vertex), vertex_match, NULL);

    size_t vertices, edges;
    fscanf(f, "%zu %zu", &vertices, &edges);

    Vertex v, w;
    while (fscanf(f, "%zu %zu %zu", &v._data, &w._data, &w._weight) != EOF) {
        graph_ins_e(&g, &v, &w);
    }
    fclose(f);

    assert(vertices == graph_v(&g));
    assert(edges    == graph_e(&g));

    Graph arborescence = graph_new(graph_vsize(&g), g.match, NULL);

    edmonds(&g, &arborescence);

    graph_print(&arborescence, vertex_print);

    graph_destroy(&arborescence);
    graph_destroy(&g);

    return 0;
}