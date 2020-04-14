#include <string.h>
#include "utils.h"

data_t* create_data() {
  data_t *data = calloc(1, sizeof(data_t));
  if (data == NULL) {
    return NULL;
  }
  return data;
}

int append(char *s, char c) {
  int len = strlen(s);
  s[len] = c;
  s[len + 1] = '\0';
  return EXIT_SUCCESS;
}

int alloc_mem_struct(data_t *data, const char *res_header, state_t state) {
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

int alloc_mem_str(char **str, size_t *count) {
  if (*str == NULL) {
    *str = calloc(*count, sizeof(char));
    if (*str == NULL) {
      return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
  }

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

int delete_str(char **str, size_t *count) {
  free(*str);
  *count = 2;
  *str = calloc(*count, sizeof(char));
  if (*str == NULL) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

void free_data(data_t *data) {
  free(data->to);
  free(data->from);
  free(data->date);
  free(data);
}

void free_mem(char *res_header, char *str, char *res_boundary,
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
