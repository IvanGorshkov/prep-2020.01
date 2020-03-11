#ifndef PROJECT_INCLUDE_FILEMODULE_H_
#define PROJECT_INCLUDE_FILEMODULE_H_

#include <stdio.h>
#include <stdlib.h>
#include "model.h"
#include "menu.h"
#include "utils.h"


void master_write(FILE *of_ptr, Data Client);
void transaction_write(FILE *of_ptr, Data transfer);
void black_record(FILE *of_ptr, FILE *of_ptr_2, FILE *blackrecord, Data client_data, Data transfer);
void output_menu(int num);
void write_to_file(FILE *of_ptr, Data client_data);
int read_from_file(FILE *of_ptr, Data *client_data);

#endif  // PROJECT_INCLUDE_FILEMODULE_H_
