#pragma once

#include <stdarg.h>

#define err_abort(format, ...)      \
    error(format, ##__VA_ARGS__);   \
    exit(EXIT_FAILURE)

/// @brief Displays error message to `stderr`.
/// @param fmt message format
/// @param params format arguments
void error(const char* fmt, ...);