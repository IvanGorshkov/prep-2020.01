#include <stdlib.h>
#include <stdio.h>
#include "parser.h"

int main(int argc, const char **argv) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    const char *path_to_eml = argv[1];
    FILE *file = fopen(path_to_eml, "r");

    if (file == NULL) {
        return EXIT_FAILURE;
    }

    data_t *data = calloc(1, sizeof(data_t));

    if (data == NULL) {
        fclose(file);
        return EXIT_FAILURE;
    }

    if (parse(data, file)) {
        free(data->to);
        free(data->from);
        free(data->date);
        free(data);
        fclose(file);
        return EXIT_FAILURE;
    }

    fclose(file);

    printf("%s|%s|%s|%d", data->from, data->to, data->date, data->part);

    free(data->to);
    free(data->from);
    free(data->date);
    free(data);
    return 0;
}
