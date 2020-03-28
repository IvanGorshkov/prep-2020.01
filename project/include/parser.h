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
    STATE_FROM = 0,
    STATE_TO,
    STATE_DATE
} state_t;

int parse(data_t *data, FILE *file);

#endif  // PROJECT_INCLUDE_PARSER_H_
