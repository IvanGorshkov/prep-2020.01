#include <string.h>
#include "parser.h"

static int append(char *s, char c) {
    int len = strlen(s);
    s[len] = c;
    s[len + 1] = '\0';
    return 0;
}

static void insert_to_data(data_t *data, char *text, int *flag, state_t state) {
    size_t len = strlen(text) + 1;
    switch (state) {
        case STATE_FROM:
                snprintf(data->from,  len, "%s", text);
            break;
        case STATE_TO:
                snprintf(data->to, len, "%s", text);
            break;
        case STATE_DATE:
                snprintf(data->date, len, "%s", text);
            break;
        default:
            break;
    }

    *flag = 1;
    text[0] = '\0';
}

static int add_to_text(char *res_header, char c, int *flag, FILE* file) {
    int i = 0;
    int space = 0;
    c = fgetc(file);
    fseek(file, -1, SEEK_CUR);

    if (c == ' ') {
        space = 1;
    }

    while (c != '\n' && c != '\r') {
        i++;
        c = fgetc(file);
    }

    fseek(file, -i + space - *flag, SEEK_CUR);

    char *buffer = calloc(i - space + *flag, sizeof(char));

    if (buffer == NULL) {
        return 0;
    }

    fgets(buffer, i - space + *flag, file);
    char *buffer_2 = calloc(strlen(res_header) + strlen(buffer) + space + 1, sizeof(char));

    if (buffer_2 == NULL) {
        free(buffer);
        return 0;
    }

    snprintf(buffer_2, strlen(res_header) + strlen(buffer) + space + 1, "%s%s", res_header, buffer);
    snprintf(res_header, strlen(buffer_2) + 1, "%s", buffer_2);
    *flag = 1;
    free(buffer);
    free(buffer_2);
    return 1;
}

static int alloc_mem_struct(data_t *data, const char *res_header, state_t state) {
    size_t alloc_mem_size = sizeof(char) * strlen(res_header) + 1;

    switch (state) {
           case STATE_FROM:
                free(data->from);
                data->from = calloc(alloc_mem_size, sizeof(char));

                if (data->from == NULL) {
                    return -1;
                }
                break;
           case STATE_TO:
                free(data->to);
                data->to = calloc(alloc_mem_size, sizeof(char));

                if (data->to == NULL) {
                    return -1;
                }
                break;
           case STATE_DATE:
                free(data->date);
                data->date = calloc(alloc_mem_size, sizeof(char));

                if (data->date == NULL) {
                    return -1;
                }
                break;
           default:
               break;
       }

    return 0;
}

int parse(data_t *data, FILE *file) {
    data->to = calloc(1, sizeof(char));

    if (data->to == NULL) {
        return -1;
    }

    data->from = calloc(1, sizeof(char));

    if (data->from == NULL) {
        return -1;
    }

    data->date = calloc(1, sizeof(char));

    if (data->date == NULL) {
        return -1;
    }

    char *s = calloc(10000, sizeof(char));

    if (s == NULL) {
        return -1;
    }

    char *res_header = calloc(2500000, sizeof(char));

    if (res_header == NULL) {
        free(s);
        return -1;
    }

    char *res4 = calloc(1000, sizeof(char));

    if (res4 == NULL) {
        free(s);
        free(res_header);
        return -1;
    }

    char *res_end = calloc(1, sizeof(char));

    if (res_end == NULL) {
        free(s);
        free(res_header);
        free(res4);
        return -1;
    }

    char *boundary = calloc(2, sizeof(char));

    if (boundary == NULL) {
        free(s);
        free(res_header);
        free(res4);
        free(res_end);
        return -1;
    }

    int flag = 0;
    int flag_from = 0;
    int flag_to = 0;
    int flag_date = 0;
    int flag_boundary = 0;
    int count = 0;
    int count_bin = 0;
    size_t count_boundary = 2;
    int bin_flag = 0;
    int end_flag = 0;
    while (!feof(file)) {
        char c =  fgetc(file);

        if (feof(file)) {
            break;
        }

        if (c == '\n') {
            if (flag == 1) {
                if (strcasecmp("From:", s) == 0 && flag_from == 0) {
                    char next_char = fgetc(file);
                    fseek(file, -1, SEEK_CUR);

                    if (next_char == ' ') {
                        continue;
                    }

                    if (alloc_mem_struct(data, res_header, STATE_FROM) == -1) {
                        free(s);
                        free(res_header);
                        free(res4);
                        free(res_end);
                        free(boundary);
                        return -1;
                    }

                    insert_to_data(data, res_header, &flag_from, STATE_FROM);
                }

                if (strcasecmp("To:", s) == 0  && flag_to == 0) {
                    char next_char = fgetc(file);
                    fseek(file, -1, SEEK_CUR);

                    if (next_char == ' ') {
                        continue;
                    }

                    if (alloc_mem_struct(data, res_header, STATE_TO) == -1) {
                        free(s);
                        free(res_header);
                        free(res4);
                        free(res_end);
                        free(boundary);
                        return -1;
                    }

                    insert_to_data(data, res_header, &flag_to, STATE_TO);
                }

                if (strcasecmp("Date:", s) == 0  && flag_date == 0) {
                    if (alloc_mem_struct(data, res_header, STATE_DATE) == -1) {
                        free(s);
                        free(res_header);
                        free(res4);
                        free(res_end);
                        free(boundary);
                        return -1;
                    }

                    insert_to_data(data, res_header, &flag_date, STATE_DATE);
                }

                if (strcasecmp("boundary=", boundary) == 0 && flag_boundary == 0) {
                    flag_boundary = 1;
                    size_t len = strlen(res4) + 3;
                    free(res_end);
                    res_end  = calloc(len, sizeof(char));
                    snprintf(res_end, len, "%s", res4);
                    append(res_end, '-');
                    append(res_end, '-');
                }
            }

            if (strstr(s, res4) != NULL && flag_boundary == 1) {
                ++count;
                bin_flag = 1;
            }

            if (strstr(s, res_end) != NULL && flag_boundary == 1) {
                --count;
                bin_flag = 1;
            }

            s[0] = '\0';
            free(boundary);
            boundary = calloc(2, sizeof(char));

            if (boundary == NULL) {
                   free(s);
                   free(res_header);
                   free(res4);
                   free(res_end);
                   return -1;
            }

            count_boundary = 2;
            flag = 0;
            end_flag++;
        } else {
            if (c != '\r') {
                end_flag = 0;
                if (flag == 0) {
                    if (flag_boundary == 0) {
                        if (strlen(boundary) + 1 >= count_boundary) {
                            count_boundary *= 2;
                            char *tmp_boundary = realloc(boundary, count_boundary*sizeof(char));

                            if (tmp_boundary == NULL) {
                                free(boundary);
                                free(s);
                                free(res_header);
                                free(res4);
                                free(res_end);
                                return -1;
                            }
                            boundary = tmp_boundary;
                        }
                        if (c == ' ' || c == '\t' || c == ';') {
                            free(boundary);
                            boundary = calloc(2, sizeof(char));
                            count_boundary = 2;

                            if (boundary == NULL) {
                                free(s);
                                free(res_header);
                                free(res4);
                                free(res_end);
                                return -1;
                            }
                        } else {
                            append(boundary, c);
                        }
                    }

                    append(s, c);
                }

                if (strcasecmp("From:", s) == 0 && flag_from == 0) {
                    if (!add_to_text(res_header, c, &flag, file)) {
                        free(s);
                        free(res_header);
                        free(res4);
                        free(res_end);
                        free(boundary);
                        return -1;
                    }

                    continue;
                }

                if (strcasecmp("To:", s) == 0 && flag_to == 0) {
                    if (!add_to_text(res_header, c, &flag, file)) {
                        free(s);
                        free(res_header);
                        free(res4);
                        free(res_end);
                        free(boundary);
                        return -1;
                    }

                    continue;
                }

                if (strcasecmp("Date:", s) == 0 && flag_date == 0) {
                    if (!add_to_text(res_header, c, &flag, file)) {
                        free(s);
                        free(res_header);
                        free(res4);
                        free(res_end);
                        free(boundary);
                        return -1;
                    }

                    continue;
                }

                if (strcasecmp("boundary=", boundary) == 0 && flag_boundary == 0) {
                    if (count_bin > 2) {
                        continue;
                    }

                    append(res4, c);

                    if (res4[0] == '=') {
                        res4[0] = '\0';
                        append(res4, '-');
                        append(res4, '-');
                    }

                    if (c == '"' || c == ' ' || c == ';') {
                        ++count_bin;
                        size_t len = strlen(res4) - 1;
                        res4[len] = '\0';
                    }

                    flag = 1;
                }
            }
        }
    }

    if (strstr(s, res4) != NULL && flag_boundary == 1) {
        ++count;
        bin_flag = 1;
    }

    if (strstr(s, res_end) != NULL && flag_boundary == 1) {
        --count;
        bin_flag = 1;
    }

    if (count == 0 && end_flag < 3 && bin_flag == 0) {
        count = 1;
    }

    data->part = count;

    free(s);
    free(res_header);
    free(res4);
    free(res_end);
    free(boundary);
    return 0;
}
