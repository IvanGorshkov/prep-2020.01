#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "boundary_work.h"

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
