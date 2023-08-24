#include "cli.h"
#include "common.h"

#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

/// @brief Optional structures supported.
static const char* default_paths[] = {
    ['l'] = "large-sample.txt",
    ['s'] = "small-sample.txt",
};

/// @brief Displays error message to `stderr`.
/// @param fmt message format
/// @param params format arguments
static void parse_err(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fputs("\n", stderr);
}

/// @brief Displays usage and functionality to `stdout`.
static void help()
{
    const char* msg =
        "usage: ./graph-repr [option] [path]\n\n"
        "-h         display usage and list available options\n"
        "-l         use large structure sample\n"
        "-s         use small structure sample\n\n"
        "Options and path are exclusive, either one or the other must be provided\n";

    fputs(msg, stdout);
}

/// @brief Resolves the command line arguments given in the shell command.
/// @param argc amount of arguments
/// @param argv argument list
/// @return path to the file determined by the user
const char* parse_args(int argc, char** argv)
{
    if (argc != 2) {
        parse_err("Expected 2 arguments, received: %d. Try '-h'.", argc - 1);
        return NULL;
    }
    int opt = getopt(argc, argv, "hls");

    switch (opt) {
    case 'h':
    case '?':
        // Unsupported argument errors are directly reported by `getop`.
        help();
        break;
    case 'l':
    case 's':
        return default_paths[opt];
    // No more options available.
    case -1:
        return argv[optind];
    default:
        parse_err("Unknown error");
    }
}