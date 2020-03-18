#ifndef PROJECT_INCLUDE_FILEMODULE_H_
#define PROJECT_INCLUDE_FILEMODULE_H_

#include <stdio.h>
#include <stdlib.h>
#include "model.h"
#include "menu.h"
#include "utils.h"

void master_write(FILE *ptr_master, Data client);
void transaction_write(FILE *ptr_transaction, Data transfer);
void black_record_write(FILE *ptr_master,
                        FILE *ptr_transaction,
                        FILE *ptr_black_record,
                        Data client_data,
                        Data transfer);
void output_menu(int num);
void write_to_file(FILE *ptr_file, Data client_data);
int read_from_file(FILE *ptr_file, Data *client_data);

#endif  // PROJECT_INCLUDE_FILEMODULE_H_
