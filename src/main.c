/**
 * Copyright (c) 2023 Gustavo Dias de Aguiar

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "cli.h"
#include "common.h"
#include "graph.h"

int main(int argc, char** argv)
{
    const char* path = parse_args(argc, argv);

    if (!path) {
        // Error already reported in `parse_args`.
        exit(ENOENT);
    }

    graph_t graph;
    init_graph(&graph);

    FILE *fp = fopen(path, "r");

    if (!fp) {
        fprintf(stderr, "Could not open file \"%s\".\n", path);
        // I.O. error.
        exit(EIO);
    }

    build_graph(&graph, fp);
    fclose(fp);
}