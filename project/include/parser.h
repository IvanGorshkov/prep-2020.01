#ifndef PROJECT_INCLUDE_PARSER_H_
#define PROJECT_INCLUDE_PARSER_H_

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    char *from;
    char *to;
    char *date;
    int part;
} data_t;

typedef enum {
    STATE_FROM,
    STATE_TO,
    STATE_DATE
} state_t;

data_t* parse(const char *path_to_eml);
void print_parser(data_t *data);
void free_data(data_t *data);
#endif  // PROJECT_INCLUDE_PARSER_H_
