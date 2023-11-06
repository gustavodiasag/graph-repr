# graph-repr

[![CMake on multiple platforms](https://github.com/gustavodiasag/graph-repr/actions/workflows/cmake-multi-platform.yml/badge.svg)](https://github.com/gustavodiasag/graph-repr/actions/workflows/cmake-multi-platform.yml)

This initial version of the project is composed of one representation for directed graphs and the chu-liu-edmonds algorithm for finding the minimum spanning tree for a given digraph.

The chosen representation is an adaptation derived from a somewhat generic graph implementation provided by Kyle Loudon on his book [Mastering Algorithms in C](https://everythingcomputerscience.com/books/Mastering-Algorithms-with-C-Loudon.pdf), which defines an adjacency list  where each of its elements is structured as an origin vertex and a set of the vertices that the origin contains an edge to.

The algorithm for finding a directed MST is derived from Jack Edmonds' paper [Optimum Branchings](https://nvlpubs.nist.gov/nistpubs/jres/71B/jresv71Bn4p233_A1b.pdf), along with a list of other sources, such as:

- [Edmonds' algorithm](https://en.wikipedia.org/wiki/Edmonds%27_algorithm).

* [Graph-based Dependency Parsing](https://courses.cs.washington.edu/courses/cse490u/17wi/slides/CLE.pdf).

- [danieldk/chu-liu-edmonds](https://github.com/danieldk/chu-liu-edmonds/blob/main/src/lib.rs).

# Build

In order to build and compile the project, CMake must be installed. After setting it up, build the project as follows:

```bash
git clone https://github.com/gustavodiasag/graph-repr.git

cd graph-repr/

mkdir build
cd build

cmake ..
cmake --build .
```

# License

This project is licensed under the [MIT License](LICENSE).