#include <string.h>
#include "parser.h"
#include <ctype.h>

static int append(char *s, char c) {
    int len = strlen(s);
    s[len] = c;
    s[len + 1] = '\0';
    return 0;
}
static void to_low_case(char *s) {
    for (int i = 0; i < s[i]; i++) {
        s[i] = tolower(s[i]);
    }
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

static void add_to_text(char *text, char c, int *flag) {
    append(text, c);

    if (text[0] == ' ' || text[0] == ':') {
        text[0] = '\0';
    }

    *flag = 1;
}

static int alloc_mem_struct(data_t *data, const char *res_header, state_t state) {
    size_t alloc_mem_size = sizeof(char) * strlen(res_header) + 1;

    char *tmp_ptr = NULL;
    switch (state) {
            case STATE_FROM:
                if ((tmp_ptr = realloc(data->from, alloc_mem_size * sizeof(char))) == NULL) {
                    return -1;
                }

                data->from = tmp_ptr;
                break;
            case STATE_TO:
                if ((tmp_ptr = realloc(data->to, alloc_mem_size * sizeof(char))) == NULL) {
                    return -1;
                }

                data->to = tmp_ptr;
                break;
            case STATE_DATE:
                if ((tmp_ptr = realloc(data->date, alloc_mem_size * sizeof(char))) == NULL) {
                    return -1;
                }

                data->date = tmp_ptr;
                break;
            default:
                break;
    }
    return 0;
}

int parse(data_t *data, FILE *file) {
    data->to = calloc(2, sizeof(char));

    if (data->to == NULL) {
        return -1;
    }

    data->from = calloc(2, sizeof(char));

    if (data->from == NULL) {
        return -1;
    }

    data->date = calloc(2, sizeof(char));

    if (data->date == NULL) {
        return -1;
    }

    char *s = calloc(2, sizeof(char));

    if (s == NULL) {
        return -1;
    }

    char *res_header = calloc(2500000, sizeof(char));

    if (res_header == NULL) {
        free(s);
        return -1;
    }

    char *res4 = calloc(2, sizeof(char));

    if (res4 == NULL) {
        free(s);
        free(res_header);
        return -1;
    }

    char *res_end = calloc(2, sizeof(char));

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
    int bin_flag = 0;
    int end_flag = 0;
    size_t count_res4 = 2;
    size_t count_s = 2;
    size_t count_boundary = 2;
    while (!feof(file)) {
        char c =  fgetc(file);

        if (feof(file)) {
            break;
        }

        if (c == '\n') {
            if (flag) {
                to_low_case(s);

                if (!strncmp(s, "from:", strlen(s)) && !flag_from) {
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

                if (!strncmp(s, "to:", strlen(s))  && !flag_to) {
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

                if (!strncmp(s, "date:", strlen(s))  && !flag_date) {
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

                to_low_case(boundary);

                if (!strncmp(boundary, "boundary=", strlen(boundary)) && !flag_boundary) {
                    flag_boundary = 1;
                    size_t len = strlen(res4) + 1;
                    char *tmp_res_end = NULL;

                    if ((tmp_res_end = realloc(res_end, len + 3)) == NULL) {
                        free(s);
                        free(res_header);
                        free(res4);
                        free(res_end);
                        free(boundary);
                        return -1;
                    }

                    res_end = tmp_res_end;
                   snprintf(res_end, len, "%s", res4);
                    append(res_end, '-');
                    append(res_end, '-');
                }
            }

            to_low_case(res4);
            if (strstr(s, res4) && flag_boundary) {
                ++count;
                bin_flag = 1;
            }

            to_low_case(res_end);
            if (strstr(s, res_end) && flag_boundary) {
                --count;
                bin_flag = 1;
            }

            count_s = 2;
            free(s);
            s = calloc(count_s, sizeof(char));
            if (s == NULL) {
                free(res_header);
                free(res4);
                free(res_end);
                free(boundary);
                return -1;
            }

            count_boundary = 2;
            free(boundary);
            boundary = calloc(count_boundary, sizeof(char));
            if (boundary == NULL) {
                free(res_header);
                free(res4);
                free(res_end);
                free(s);
                return -1;
            }
            flag = 0;
            ++end_flag;
        } else {
            if (c != '\r') {
                end_flag = 0;
                if (!flag) {
                    if (count_res4 == 2) {
                        if (c == ' ' || c == '\t' || c == ';') {
                            count_boundary = 2;
                            free(boundary);
                            boundary = calloc(count_boundary, sizeof(char));
                            if (boundary == NULL) {
                                free(res_header);
                                free(res4);
                                free(res_end);
                                free(s);
                                return -1;
                            }
                        } else {
                                size_t len_boundary = strlen(boundary);

                                if (len_boundary == count_boundary) {
                                    count_boundary *= 2 + 1;
                                    char *tmp_boundary = NULL;

                                    if ((tmp_boundary = realloc(boundary, count_boundary)) == NULL) {
                                        free(s);
                                        free(res_header);
                                        free(res4);
                                        free(res_end);
                                        free(boundary);
                                        return -1;
                                    }

                                    boundary = tmp_boundary;
                                }

                                append(boundary, c);
                            }
                        }

                    size_t len_s = strlen(s);

                    if (len_s == count_s) {
                        count_s *= 2 + 1;
                        char *tmp_s = NULL;

                        if ((tmp_s = realloc(s, count_s)) == NULL) {
                            free(s);
                            free(res_header);
                            free(res4);
                            free(res_end);
                            free(boundary);
                            return -1;
                        }

                        s = tmp_s;
                    }

                    append(s, c);
                }
                to_low_case(s);

                if (!strncmp(s, "from:", 5) && !flag_from) {
                    add_to_text(res_header, c, &flag);
                    continue;
                }

                if (!strncmp(s, "to:", 3) && !flag_to) {
                    add_to_text(res_header, c, &flag);
                    continue;
                }

                if (!strncmp(s, "date:", 5) && !flag_date) {
                    add_to_text(res_header, c, &flag);
                    continue;
                }

                to_low_case(boundary);

                if (!strncmp(boundary, "boundary=", 9) && !flag_boundary) {
                    if (count_bin > 2) {
                        continue;
                    }

                    size_t len_res4 = strlen(res4);

                    if (len_res4 == count_res4) {
                        count_res4 *= 2 + 1;
                        char *tmp_res4 = NULL;

                        if ((tmp_res4 = realloc(res4, count_res4)) == NULL) {
                            free(s);
                            free(res_header);
                            free(res4);
                            free(res_end);
                            free(boundary);
                            return -1;
                        }

                        res4 = tmp_res4;
                    }

                    append(res4, c);

                    if (res4[0] == '=') {
                        count_res4 = 2;
                        free(res4);
                        res4 = calloc(count_res4, sizeof(char));
                        if (res4 == NULL) {
                            free(res_header);
                            free(res4);
                            free(res_end);
                            free(s);
                            return -1;
                        }

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

    if (strstr(s, res4) && flag_boundary) {
        ++count;
        bin_flag = 1;
    }

    if (strstr(s, res_end) && flag_boundary) {
        --count;
        bin_flag = 1;
    }

    if (!count && end_flag < 3 && !bin_flag) {
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
