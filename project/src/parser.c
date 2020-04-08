#include <string.h>
#include "parser.h"

static int append(char *s, char c) {
    int len = strlen(s);
    s[len] = c;
    s[len + 1] = '\0';
    return EXIT_SUCCESS;
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
}

static char* add_to_text(char *res, char c, int *flag, FILE* file) {
    c = fgetc(file);
    fseek(file, -1, SEEK_CUR);
    int space = 0;

    if (c == ' ') {
        space = 1;
    }

    int i = 0;
    while (c != '\n' && c != '\r') {
        i++;
        c = fgetc(file);
    }

    fseek(file, -i + space - *flag, SEEK_CUR);

    char *buffer = calloc(i - space + *flag, sizeof(char));
    if (buffer == NULL) {
        return NULL;
    }

    fgets(buffer, i - space + *flag, file);
    char *buffer_2 = calloc(strlen(res) + strlen(buffer) + space + 1, sizeof(char));
    if (buffer_2 == NULL) {
        free(buffer);
        free(res);
        return NULL;
    }

    snprintf(buffer_2, strlen(res) + strlen(buffer) + space + 1, "%s%s", res, buffer);
    char *return_str = calloc(strlen(buffer_2) + 1, sizeof(char));

    if (return_str == NULL) {
        free(buffer);
        free(buffer_2);
        free(res);
        return NULL;
    }

    snprintf(return_str, strlen(buffer_2) + 1, "%s", buffer_2);
    *flag = 1;
    free(buffer);
    free(buffer_2);
    free(res);
    return return_str;
}

static int alloc_mem_struct(data_t *data, const char *res_header, state_t state) {
    size_t alloc_mem_size = sizeof(char) * strlen(res_header) + 1;

    switch (state) {
           case STATE_FROM:
                free(data->from);
                data->from = calloc(alloc_mem_size, sizeof(char));

                if (data->from == NULL) {
                    return EXIT_FAILURE;
                }
                break;
           case STATE_TO:
                free(data->to);
                data->to = calloc(alloc_mem_size, sizeof(char));

                if (data->to == NULL) {
                    return EXIT_FAILURE;
                }
                break;
           case STATE_DATE:
                free(data->date);
                data->date = calloc(alloc_mem_size, sizeof(char));

                if (data->date == NULL) {
                    return EXIT_FAILURE;
                }
                break;
           default:
               break;
       }

    return EXIT_SUCCESS;
}

static data_t* create_data() {
    data_t *data = calloc(1, sizeof(data_t));
    if (data == NULL) {
        return NULL;
    }

    data->to = calloc(1, sizeof(char));
    if (data->to == NULL) {
        free(data);
        return NULL;
    }

    data->from = calloc(1, sizeof(char));
    if (data->from == NULL) {
        free(data->to);
        free(data);
        return NULL;
    }

    data->date = calloc(1, sizeof(char));
    if (data->date == NULL) {
        free(data->to);
        free(data->from);
        free(data);
        return NULL;
    }

    return data;
}

void free_data(data_t *data) {
     free(data->to);
     free(data->from);
     free(data->date);
     free(data);
}

static int check_header(const char *search, char *str, int *flag,
                        int flag_enable, FILE *file, char *res_header,
                        data_t *data, state_t st) {
    if (flag_enable == 1) {
        if (strcasecmp(search, str) == 0 && *flag == 0) {
            char next_char = fgetc(file);
            fseek(file, -1, SEEK_CUR);

            if (next_char == ' ') {
                return 2;
            }

            if (alloc_mem_struct(data, res_header, st)) {
                return EXIT_FAILURE;
            }

            insert_to_data(data, res_header, flag, st);
        }
    }
    return EXIT_SUCCESS;
}

static int realloc_mem_str(char **str, size_t *count) {
    if (strlen(*str) + 1 >= *count) {
        *count *= 2;
        char *tmp_str = realloc(*str, *count * sizeof(char) + 1);

        if (tmp_str == NULL) {
            return EXIT_FAILURE;
        }

        *str = tmp_str;
    }

    return EXIT_SUCCESS;
}

static int delete_str(char **str, size_t *count) {
    free(*str);
    *count = 2;
    *str = calloc(*count, sizeof(char));
    if (*str == NULL) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

data_t* parse(const char *path_to_eml) {
    FILE *file = fopen(path_to_eml, "r");

    if (file == NULL) {
        return NULL;
    }

    data_t *data = create_data();
    if (data == NULL) {
        fclose(file);
        return NULL;
    }

    char *str = calloc(2, sizeof(char));

    if (str == NULL) {
        free_data(data);
        fclose(file);
        return NULL;
    }

    char *res_header = calloc(2, sizeof(char));

    if (res_header == NULL) {
        free(str);
        free_data(data);
        fclose(file);
        return NULL;
    }

    char *res_boundary = calloc(3, sizeof(char));

    if (res_boundary == NULL) {
        free(str);
        free(res_header);
        free_data(data);
        fclose(file);
        return NULL;
    }

    char *boundary_end = calloc(1, sizeof(char));

    if (boundary_end == NULL) {
        free(str);
        free(res_header);
        free(res_boundary);
        free_data(data);
        fclose(file);
        return NULL;
    }

    char *boundary = calloc(2, sizeof(char));

    if (boundary == NULL) {
        free(str);
        free(res_header);
        free(res_boundary);
        free(boundary_end);
        free_data(data);
        fclose(file);
        return NULL;
    }

    int flag = 0;
    int flag_from = 0;
    int flag_to = 0;
    int flag_date = 0;
    int flag_boundary = 0;
    int been_flag = 0;
    int end_flag = 0;
    int count = 0;
    int count_been = 0;
    size_t count_boundary = 2;
    size_t count_res_boundary = 3;
    size_t count_str = 2;
    while (!feof(file)) {
        char c =  fgetc(file);
        if (feof(file)) {
            break;
        }

        if (c == '\n') {
            int check_err = check_header("From:", str, &flag_from, flag, file, res_header, data, STATE_FROM);
            if (check_err == 1) {
                free(str);
                free(res_header);
                free(res_boundary);
                free(boundary_end);
                free(boundary);
                free_data(data);
                fclose(file);
                return NULL;
            }

            if (check_err == 2) {
                continue;
            }

            check_err = check_header("To:", str, &flag_to, flag, file, res_header, data, STATE_TO);
            if (check_err == 1) {
                free(str);
                free(res_header);
                free(res_boundary);
                free(boundary_end);
                free(boundary);
                free_data(data);
                fclose(file);
                return NULL;
            }

            if (check_err == 2) {
                continue;
            }

            check_err = check_header("Date:", str, &flag_date, flag, file, res_header, data, STATE_DATE);
            if (check_err == 1) {
                free(str);
                free(res_header);
                free(res_boundary);
                free(boundary_end);
                free(boundary);
                free_data(data);
                fclose(file);
                return NULL;
            }

            if (check_err == 2) {
                continue;
            }


            if (!strcasecmp("boundary=", boundary) && !flag_boundary && flag) {
                flag_boundary = 1;
                size_t len = strlen(res_boundary) + 3;
                free(boundary_end);
                boundary_end  = calloc(len, sizeof(char));

                if (boundary_end == NULL) {
                    free(str);
                    free(boundary);
                    free(res_boundary);
                    free(res_header);
                    free_data(data);
                    fclose(file);
                    return NULL;
                }

                snprintf(boundary_end, len, "%s--", res_boundary);
            }

            if (strstr(str, res_boundary) != NULL && flag_boundary) {
                ++count;
                been_flag = 1;
            }

            if (strstr(str, boundary_end) != NULL && flag_boundary) {
                --count;
                been_flag = 1;
            }

            if (delete_str(&str, &count_str)) {
                free(boundary);
                free(res_header);
                free(res_boundary);
                free(boundary_end);
                free_data(data);
                fclose(file);
                return NULL;
            }

            if (delete_str(&boundary, &count_boundary)) {
                free(str);
                free(res_header);
                free(res_boundary);
                free(boundary_end);
                free_data(data);
                fclose(file);
                return NULL;
            }

            if (flag) {
                free(res_header);
                res_header = calloc(2, sizeof(char));
                if (res_header == NULL) {
                    free(str);
                    free(boundary);
                    free(res_boundary);
                    free(boundary_end);
                    free_data(data);
                    fclose(file);
                    return NULL;
                }
            }

            flag = 0;
            end_flag++;
        } else if (c != '\r') {
            end_flag = 0;
            if (!flag) {
                if (realloc_mem_str(&boundary, &count_boundary)){
                    free(boundary);
                    free(str);
                    free(res_header);
                    free(res_boundary);
                    free(boundary_end);
                    fclose(file);
                    free_data(data);
                    return NULL;
                }

                if (c == ' ' || c == '\t' || c == ';') {
                    if (delete_str(&boundary, &count_boundary)) {
                        free(boundary);
                        free(res_header);
                        free(res_boundary);
                        free(boundary_end);
                        free_data(data);
                        fclose(file);
                        return NULL;
                    }
                } else {
                    append(boundary, c);
                }

                if (realloc_mem_str(&str, &count_str)){
                    free(boundary);
                    free(str);
                    free(res_header);
                    free(res_boundary);
                    free(boundary_end);
                    fclose(file);
                    free_data(data);
                    return NULL;
                }

                append(str, c);
            }


            if (!strcasecmp("From:", str) && !flag_from) {
                res_header = add_to_text(res_header, c, &flag, file);

                if (res_header == NULL) {
                    free(str);
                    free(res_boundary);
                    free(boundary_end);
                    free(boundary);
                    free_data(data);
                    fclose(file);
                    return NULL;
                }

                continue;
            }

            if (!strcasecmp("To:", str) && !flag_to) {
                res_header = add_to_text(res_header, c, &flag, file);

                if (res_header == NULL) {
                    free(str);
                    free(res_boundary);
                    free(boundary_end);
                    free(boundary);
                    fclose(file);
                    return NULL;
                }

                continue;
            }

            if (!strcasecmp("Date:", str) && !flag_date) {
                res_header = add_to_text(res_header, c, &flag, file);
                if (res_header == NULL) {
                    free(str);
                    free(res_boundary);
                    free(boundary_end);
                    free(boundary);
                    free_data(data);
                    fclose(file);
                    return NULL;
                }

                continue;
            }

            if (!strcasecmp("boundary=", boundary) && !flag_boundary) {
                if (count_been > 2) {
                    continue;
                }

                if (realloc_mem_str(&res_boundary, &count_res_boundary)){
                    free(boundary);
                    free(str);
                    free(res_header);
                    free(res_boundary);
                    free(boundary_end);
                    fclose(file);
                    free_data(data);
                    return NULL;
                }

                append(res_boundary, c);

                if (res_boundary[0] == '=') {
                    res_boundary[0] = '\0';
                    append(res_boundary, '-');
                    append(res_boundary, '-');
                }

                if (c == '"' || c == ' ' || c == ';') {
                    ++count_been;
                    size_t len = strlen(res_boundary) - 1;
                    res_boundary[len] = '\0';
                }

                flag = 1;
            }
        }
    }

    if (strstr(str, res_boundary) != NULL && flag_boundary) {
        ++count;
        been_flag = 1;
    }

    if (strstr(str, boundary_end) != NULL && flag_boundary) {
        --count;
        been_flag = 1;
    }

    if (!count && end_flag < 3 && !been_flag) {
        count = 1;
    }

    data->part = count;

    free(str);
    free(res_header);
    free(res_boundary);
    free(boundary_end);
    free(boundary);
    fclose(file);
    return data;
}

void print_parser(data_t *data) {
    printf("%s|%s|%s|%d", data->from, data->to, data->date, data->part);
}
