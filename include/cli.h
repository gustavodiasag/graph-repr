#pragma once

typedef enum {
    OPT_HELP,
    OPT_DICT,
    OPT_NONE,
} opt_t;

typedef struct {
    const char* short_repr;
    const char* long_repr; 
} cli_config_t;

typedef struct {
    opt_t option;
    const char *file;
} cli_t;

void parse_args(int argc, char *argv[]);