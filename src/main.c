#include <stdlib.h>

#include "cli.h"
#include "common.h"
#include "list.h"

int main(int argc, char** argv)
{
    const char* path = parse_args(argc, argv);

    List l = {0};
    list_init(&l, sizeof(int), NULL);

    
}