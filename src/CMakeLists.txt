cmake_minimum_required(VERSION 3.16.3)

project(graph-repr C CXX)

add_library(source
    cli/cli.c
    error.c
    graph/edmonds.c
    utils/graph.c
    utils/list.c
    utils/set.c
    utils/stack.c
    utils/vertex.c
)

target_include_directories(source
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)