#ifndef PROJECT_INCLUDE_HEADER_WORK_H_
#define PROJECT_INCLUDE_HEADER_WORK_H_

#include <stdlib.h>
#include <stdio.h>
#include "models.h"

char* add_to_text(char *res, char c, int *flag, FILE* file);
void insert_to_data(data_t *data, char *text, int *flag, state_t state);
int insert_to_header(char *res_header, char *str, FILE *file
    , flags_t *flags, data_t *data, state_t state);
int check_header(const char *search, char *str, int *flag, FILE *file, char *res_header
    , data_t *data, state_t st);
int find_header(char *str, flags_t *flags, state_t *state_header
    , char **res_header, char c, FILE *file);

#endif  // PROJECT_INCLUDE_HEADER_WORK_H_
