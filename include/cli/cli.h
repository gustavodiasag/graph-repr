#ifndef CLI_H
#define CLI_H

/// @brief Resolves the command line arguments provided.
/// @param argc amount of arguments
/// @param argv argument list
/// @return selected path to file
const char* parse_args(int argc, char** argv);

#endif