#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

#include "cli/cli.h"
#include "common.h"
#include "error.h"

static const char* _default_paths[] = {
    ['l'] = "../large-sample.txt",
    ['s'] = "../small-sample.txt",
};

/** Displays usage and functionality to `stdout`. */
static void _help()
{
    fprintf(
        stderr,
        "usage: ./graph-repr [option] [path]\n\n"
        "-h         display usage and list available options\n"
        "-l         use large structure sample\n"
        "-s         use small structure sample\n\n"
        "Option and path are exclusive, either one or the other must be provided\n"
    );
}

const char* parse_args(int argc, char** argv)
{
    if (argc != 2) {
        fprintf(stderr, "Expected 2 arguments, received: %d. Try '-h'.", argc - 1);
        return NULL;
    }
    const int opt = getopt(argc, argv, "hls");

    switch (opt) {
    case 'h':
    case '?':
        // Unsupported argument errors are directly reported by `getop`.
        _help();
        return NULL;
    case 'l':
    case 's':
        return _default_paths[opt];
    case -1:
        return argv[optind];
    // No more options available.
    default:
        err_abort("Unknown error");
    }
}