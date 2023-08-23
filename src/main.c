#include "cli.h"
#include "common.h"

int main(int argc, char* argv[])
{
    const char* path = parse_args(argc, argv);

    if (!path) {
        // No such file or directory.
        return ENOENT;
    }
}