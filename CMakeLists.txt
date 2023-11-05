# To find the cmake version run `cmake --version`.
cmake_minimum_required(VERSION 3.16.3)

# Set the project name.
project(graph-repr C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_EXTENSIONS True)

# Add compile definitions for specific operating systems.
if(UNIX)
    add_compile_definitions(OS_UNIX_LIKE)    
    if(LINUX) 
        add_compile_definitions(OS_LINUX)
    elseif(APPLE) 
        add_compile_definitions(OS_MACOS)
    else()
        add_compile_definitions(OS_UNKNOWN_UNIX)
    endif()
elseif(WIN32)
    add_compile_definitions(OS_WINDOWS)
else()
    add_compile_definitions(OS_UNKNOWN)
endif()

# Determine compiler to provide specific optimizations
if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    add_compile_definitions(COMPILER_GCC)
elseif(CMAKE_C_COMPILER_ID STREQUAL "Clang")
    add_compile_definitions(COMPILER_CLANG)
elseif(CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    add_compile_definitions(COMPILER_MSVC)
elseif (CMAKE_C_COMPILER_ID STREQUAL "Intel")
    add_compile_definitions(COMPILER_INTEL)
else()
    add_compile_definitions(COMPILER_UNKNOWN)
endif()

if (MSVC)
    # Warning level 4
    add_compile_options(\W4)
else()
    # Additional warnings
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_subdirectory(src)

add_executable(${PROJECT_NAME} src/main.c)

target_link_libraries(${PROJECT_NAME} PRIVATE source)