cmake_minimum_required(VERSION 3.16.3)

project(graph-repr C CXX)

add_library(source
    cli.c
    graph.c
    memory.c
)

target_include_directories(source
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)