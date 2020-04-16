#ifndef PROJECT_INCLUDE_BOUNDARY_WORK_H_
#define PROJECT_INCLUDE_BOUNDARY_WORK_H_

#include "models.h"

int create_boundary(char *boundary, char *res_boundary, char **boundary_end, flags_t *flags);
void find_boundary(char *buf, char *res_boundary, char *boundary_end, flags_t *flags, int *count);
int header_boundary(char *boundary, flags_t *flags, char **res_boundary
                   , int *count_been, size_t *count_res_boundary, char c);
#endif  // PROJECT_INCLUDE_BOUNDARY_WORK_H_
