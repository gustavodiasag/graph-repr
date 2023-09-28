#pragma once

#include <stdarg.h>

#define err_abort(error_kind, format, ...)       \
    error(format, ##__VA_ARGS__);   \
    exit(error_kind)

/// @brief Displays error message to `stderr`.
/// @param fmt message format
/// @param params format arguments
void error(const char* fmt, ...);