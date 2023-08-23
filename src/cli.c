#include "cli.h"
#include "common.h"

#ifdef DEBUG_CONFIG

#include <stdio.h>

#endif

static cli_config_t configs[] = {
    [OPT_NONE] = {.long_repr = NULL, .short_repr = NULL},
    [OPT_DICT] = {.long_repr = "--sample", .short_repr = "-s"},
    [OPT_HELP] = {.long_repr = "--help", .short_repr = "-h"},
};

void parse_args(int argc, char *argv[])
{
    if (argc > 3) {
        parse_err();
    }
}