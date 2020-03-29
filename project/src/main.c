#include <stdlib.h>
#include <stdio.h>
#include "parser.h"

int main(int argc, const char **argv) {
    if (argc != 2) {
        return -1;
    }

    const char *path_to_eml = argv[1];
    FILE *file = fopen(path_to_eml, "r");

    if (file == NULL) {
        return -1;
    }

    data_t *data = calloc(1, sizeof(data_t));

    if (data == NULL) {
        fclose(file);
        return -1;
    }

    if (parse(data, file) == -1) {
        free(data->to);
        free(data->from);
        free(data->date);
        free(data);
        fclose(file);
        return -1;
    }

    fclose(file);

    printf("%s|%s|%s|%d", data->from, data->to, data->date, data->part);

    free(data->to);
    free(data->from);
    free(data->date);
    free(data);
    return 0;
}
