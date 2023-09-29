#include "common.h"
#include "graph.h"
#include "memory.h"

typedef struct _Graph {
    uint32_t* ptrs;
    uint32_t* dest;

    uint32_t _ptr_count;
    uint32_t _dest_count;
} Graph;

void
_alloc_graph(Graph* graph, uint32_t ptr_size, uint32_t dest_size)
{
    graph->ptrs = alloc(uint32_t, ptr_size);
    graph->dest = alloc(uint32_t, dest_size);
    // First position is ignored.
    graph->_ptr_count = 1;
    graph->_dest_count = 1;
}

void
free_graph(Graph* graph)
{
    free_array(uint32_t, graph->ptrs);
    free_array(uint32_t, graph->dest);
}

void
build_graph(Graph* graph, FILE* fp)
{
    uint32_t v = 0;
    uint32_t e = 0;

    fscanf(fp, "%u %u", &v, &e);
    // A graph is expected to have at least one vertex.
    assert(v);

    _alloc_graph(graph, (v + 2), (e + 1));

    uint32_t e_tail = 0;
    uint32_t e_head = 0;
    uint32_t prev_orig = 0;

    while (fscanf(fp, "%u %u", &e_tail, &e_head) != EOF) {

        while (e_tail > prev_orig) {
            prev_orig++;
            graph->ptrs[graph->_ptr_count++] = graph->_dest_count;
        }
        graph->dest[graph->_dest_count++] = e_head;
    }
    // Last position is used like a sentinel.
    graph->ptrs[graph->_ptr_count++] = graph->_dest_count;
}