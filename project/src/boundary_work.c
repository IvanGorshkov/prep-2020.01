#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "boundary_work.h"
#include "utils.h"

int create_boundary(char *boundary, char *res_boundary, char **boundary_end, flags_t *flags) {
  if (!strcasecmp("boundary=", boundary) && !flags->flag_boundary && flags->flag) {
    flags->flag_boundary = 1;
    size_t len = strlen(res_boundary) + 3;
    *boundary_end  = calloc(len, sizeof(char));

    if (*boundary_end == NULL) {
      return EXIT_FAILURE;
    }

    snprintf(*boundary_end, len, "%s--", res_boundary);
  }
  return EXIT_SUCCESS;
}

void find_boundary(char *buf, char *res_boundary
    , char *boundary_end, flags_t *flags, int *count) {
  if (strstr("\n", buf) != NULL) {
    ++flags->end_flag;
  } else {
    --flags->end_flag;
  }

  if (strstr(buf, res_boundary) != NULL && flags->flag_boundary) {
    ++(*count);
    flags->been_flag = 1;
  }

  if (boundary_end != NULL) {
    if (strstr(buf, boundary_end) != NULL && flags->flag_boundary) {
      --(*count);
    flags->been_flag = 1;
    }
  }
}

int header_boundary(char *boundary, flags_t *flags, char **res_boundary
                    , int *count_been, size_t *count_res_boundary, char c) {
  if (!strcasecmp("boundary=", boundary) && !flags->flag_boundary) {
    if (*count_been > 2) {
      return EXIT_SUCCESS;
    }

    if (alloc_mem_str(res_boundary, count_res_boundary)) {
      return EXIT_FAILURE;
    }

    append(*res_boundary, c);

    if (*res_boundary[0] == '=') {
      *res_boundary[0] = '\0';
      append(*res_boundary, '-');
      append(*res_boundary, '-');
    }

    if (c == '"' || c == ' ' || c == ';') {
      ++(*count_been);
      size_t len = strlen(*res_boundary) - 1;
      res_boundary[0][len] = '\0';
    }

    flags->flag = 1;
  }

  return EXIT_SUCCESS;
}
