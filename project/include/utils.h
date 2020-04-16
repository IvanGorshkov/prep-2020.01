#ifndef PROJECT_INCLUDE_UTILS_H_
#define PROJECT_INCLUDE_UTILS_H_

#include <stdlib.h>
#include <stdio.h>
#include "models.h"

int alloc_mem_struct(data_t *data, const char *res_header, state_t state);
int alloc_mem_str(char **str, size_t *count);
int delete_str(char **str, size_t *count);
data_t* create_data();
void free_data(data_t *data);
void free_mem(char *res_header, char *str, char *res_boundary
              , char *boundary_end, char *boundary, FILE *file);
int append(char *s, char c);
#endif  // PROJECT_INCLUDE_UTILS_H_
