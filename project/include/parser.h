#ifndef PROJECT_INCLUDE_PARSER_H_
#define PROJECT_INCLUDE_PARSER_H_

#include <stdlib.h>
#include <stdio.h>
#include "models.h"

data_t* parse(const char *path_to_eml);
int print_parser(data_t *data);

#endif  // PROJECT_INCLUDE_PARSER_H_
