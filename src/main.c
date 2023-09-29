#include <stdlib.h>

#include "cli.h"
#include "common.h"
#include "graph.h"
#include "error.h"

int
main(int argc, char** argv)
{
    const char* path = parse_args(argc, argv);

    if (!path) {
        // Error already reported in `parse_args`.
        exit(EXIT_FAILURE);
    }

    FILE *fp = fopen(path, "r");

    if (!fp) {
        err_abort("Could not open file \"%s\".", path);
    }

    Graph* graph;
    build_graph(graph, fp);

    fclose(fp);

    free_graph(graph);
}