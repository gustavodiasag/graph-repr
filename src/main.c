#include <stdlib.h>

#include "cli.h"
#include "common.h"
#include "graph.h"

typedef struct _Vertex {
    int     data;
    int     weight;
} Vertex;

int vertex_match(const void* v1, const void* v2)
{
    return ((Vertex*)v1)->data - ((Vertex*)v2)->data;
}

void vertex_print(const void* data)
{
    const Vertex v = *(Vertex*)data;

    printf("%d", v.data);
}

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
    while (fscanf(f, "%d %d", &v.data, &w.data) != EOF) {
        printf("v: %d, %d\n", graph_ins_v(&g, &v), v.data);
        printf("w: %d, %d\n", graph_ins_v(&g, &w), w.data);
        graph_ins_e(&g, &v, &w);
    }
    fclose(f);

    graph_print(&g, vertex_print);

    graph_destroy(&g);

    return 0;
}