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

typedef struct {
  int flag;
  int flag_from;
  int flag_to;
  int flag_date;
  int flag_boundary;
  int been_flag;
  int end_flag;
} flags_t;

typedef enum {
    STATE_START,
    STATE_FROM,
    STATE_TO,
    STATE_DATE
} state_t;

data_t* parse(const char *path_to_eml);
int print_parser(data_t *data);
void free_data(data_t *data);
#endif  // PROJECT_INCLUDE_PARSER_H_
