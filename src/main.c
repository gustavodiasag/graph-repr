#include <stdlib.h>
#include <time.h>

#include "common.h"
#include "graph/edmonds.h"
#include "utils/graph.h"
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
    Graph g = graph_new(sizeof(Vertex), vertex_match, NULL);

    size_t vertices, edges;
    fscanf(f, "%zu %zu", &vertices, &edges);

    Vertex v, w;
    while (fscanf(f, "%zu %zu %zu", &v._data, &w._data, &w._weight) != EOF) {
        graph_ins_e(&g, &v, &w);
    }
    fclose(f);

    Graph arborescence = graph_new(graph_vsize(&g), g.match, NULL);

    clock_t start, end;
    start = clock();

    edmonds(&g, &arborescence);

    end = clock();
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("CPU time used: %f seconds.\n", cpu_time_used);

    return 0;
}