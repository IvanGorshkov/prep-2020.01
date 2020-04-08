#include <stdlib.h>
#include <stdio.h>
#include "parser.h"

int main(int argc, const char **argv) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    const char *path_to_eml = argv[1];

    if (parse(path_to_eml)) {
        return EXIT_FAILURE;
    }

    return 0;
}
