#include <string.h>
#include "parser.h"
#include "header_work.h"
#include "utils.h"

static int append(char *s, char c) {
  int len = strlen(s);
  s[len] = c;
  s[len + 1] = '\0';
  return EXIT_SUCCESS;
}

static void free_mem(char *res_header, char *str, char *res_boundary,
    char *boundary_end, char *boundary, FILE *file) {
  if (boundary != NULL) {
    free(boundary);
  }

  if (str != NULL) {
    free(str);
  }

  if (res_header != NULL) {
    free(res_header);
  }

  if (res_boundary != NULL) {
    free(res_boundary);
  }
  if (boundary_end != NULL) {
    free(boundary_end);
  }
  if (file != NULL) {
    fclose(file);
  }
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

  flags_t flags = {0};
  char *res_header = NULL;
  char *str = NULL;
  char *res_boundary = NULL;
  char *boundary_end = NULL;
  char *boundary = NULL;
  int count = 0;
  int count_been = 0;
  size_t count_boundary = 2;
  size_t count_res_boundary = 3;
  size_t count_str = 2;
  state_t state_header = STATE_START;

  while (flags.end_flag != 2) {
    char c =  fgetc(file);

    if (c == '\n') {
      int check_err = insert_to_header(res_header, str, file, &flags, data, state_header);
      if (check_err == 1) {
        free_mem(res_header, str, res_boundary, boundary_end, boundary, file);
        free_data(data);
        return NULL;
      }

      if (check_err == 2) {
        continue;
      }

      if (!strcasecmp("boundary=", boundary) && !flags.flag_boundary && flags.flag) {
        flags.flag_boundary = 1;
        size_t len = strlen(res_boundary) + 3;
        boundary_end  = calloc(len, sizeof(char));

        if (boundary_end == NULL) {
          free_mem(res_header, str, res_boundary, boundary_end, boundary, file);
          free_data(data);
          return NULL;
        }

        snprintf(boundary_end, len, "%s--", res_boundary);
      }

      if (delete_str(&str, &count_str)) {
        free_mem(res_header, str, res_boundary, boundary_end, boundary, file);
        free_data(data);
        return NULL;
      }

      if (delete_str(&boundary, &count_boundary)) {
        free_mem(res_header, str, res_boundary, boundary_end, boundary, file);
        free_data(data);
        return NULL;
      }

      if (flags.flag) {
        free(res_header);
        res_header = calloc(2, sizeof(char));
        if (res_header == NULL) {
          free_mem(res_header, str, res_boundary, boundary_end, boundary, file);
          free_data(data);
          return NULL;
        }
      }

      flags.flag = 0;
      flags.end_flag++;
    } else if (c != '\r') {
      flags.end_flag = 0;
      if (!flags.flag) {
        if (alloc_mem_str(&boundary, &count_boundary)) {
          free_mem(res_header, str, res_boundary, boundary_end, boundary, file);
          free_data(data);
          return NULL;
        }

        if (c == ' ' || c == '\t' || c == ';') {
          if (delete_str(&boundary, &count_boundary)) {
            free_mem(res_header, str, res_boundary, boundary_end, boundary, file);
            free_data(data);
            return NULL;
          }
        } else {
          append(boundary, c);
        }

        if (alloc_mem_str(&str, &count_str)) {
          free_mem(res_header, str, res_boundary, boundary_end, boundary, file);
          free_data(data);
          return NULL;
        }

        append(str, c);
      }

      if (find_header(str, &flags, &state_header, &res_header, c, file)) {
        free_mem(res_header, str, res_boundary, boundary_end, boundary, file);
        free_data(data);
        return NULL;
      }

      if (!strcasecmp("boundary=", boundary) && !flags.flag_boundary) {
        if (count_been > 2) {
          continue;
        }

        if (alloc_mem_str(&res_boundary, &count_res_boundary)) {
          free_mem(res_header, str, res_boundary, boundary_end, boundary, file);
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

        flags.flag = 1;
      }
    }
  }

  if (res_boundary != NULL) {
    char buf[4096] = "";

    while (fgets(buf, sizeof(buf), file) != NULL) {
      buf[strlen(buf)] = '\0';
      if (strstr("\n", buf) != NULL) {
        ++flags.end_flag;
      } else {
        --flags.end_flag;
      }

      if (strstr(buf, res_boundary) != NULL && flags.flag_boundary) {
        ++count;
        flags.been_flag = 1;
      }

      if (boundary_end != NULL) {
        if (strstr(buf, boundary_end) != NULL && flags.flag_boundary) {
          --count;
          flags.been_flag = 1;
        }
      }
    }
  }

  if (!count && flags.end_flag <= 3 && !flags.been_flag) {
    count = 1;
  }

  data->part = count;

  free_mem(res_header, str, res_boundary, boundary_end, boundary, file);
  return data;
}

int print_parser(data_t *data) {
  if (data->to == NULL) {
    data->to = calloc(1, sizeof(char));
    if (data->to == NULL) {
      free(data);
      return EXIT_FAILURE;
    }
  }

  if (data->from == NULL) {
    data->from = calloc(1, sizeof(char));
    if (data->from == NULL) {
      free(data->to);
      free(data);
      return EXIT_FAILURE;
    }
  }

  if (data->date == NULL) {
    data->date = calloc(1, sizeof(char));
    if (data->date == NULL) {
      free(data->to);
      free(data->from);
      free(data);
      return EXIT_FAILURE;
    }
  }

  printf("%s|%s|%s|%d", data->from, data->to, data->date, data->part);
  return EXIT_SUCCESS;
}
