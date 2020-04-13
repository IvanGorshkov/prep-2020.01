#include <stdlib.h>
#include <stdio.h>
#include "parser.h"

int main(int argc, const char **argv) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    const char *path_to_eml = argv[1];
    data_t *data = parse(path_to_eml);
    if (data == NULL) {
        return EXIT_FAILURE;
    }

    if (print_parser(data)) {
      return EXIT_FAILURE;
    }

    free_data(data);
    return 0;
}
