#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static int _rand_between(int min, int max);

int main(int argc, char** argv) {

    if (argc < 4) {
        fprintf(stderr, "Usage: %s <num_nodes> <num_edges> <output_file>\n", argv[0]);
        exit(1);
    }

    int num_nodes = atoi(argv[1]);
    int num_edges = atoi(argv[2]);

    const char *file_name = argv[3];
    
    int weight;

    char output_file[255];

    strcat(output_file, file_name);
    FILE *f;

    srand(time(NULL));

    f = fopen(output_file, "w");
    if (!f) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }
    fprintf(f, "%d %d\n", num_nodes, num_edges);

    for (int i = 0; i < num_edges; i++) {
        int v1 = _rand_between(1, num_nodes);
        int v2 = _rand_between(1, num_nodes);
        
        weight = _rand_between(1, 100);
        fprintf(f, "%d %d %d\n", v1, v2, weight);
    }
    fclose(f);

    return 0;
}

static int _rand_between(int min, int max) {
    return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}