#ifndef FILEMODULE_H
#define FILEMODULE_H

#include <stdio.h>
#include <stdlib.h>
#include "model.h"
#include "menu.h"

void masterWrite(FILE *of_ptr, Data Client);
void transactionWrite(FILE *of_ptr, Data transfer);
void blackRecord(FILE *of_ptr, FILE *of_ptr_2, FILE *blackrecord, Data client_data, Data transfer);
void output_menu(int num);

#endif //FILEMODULE_H
