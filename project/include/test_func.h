#ifndef PROJECT_INCLUDE_TEST_FUNC_H_
#define PROJECT_INCLUDE_TEST_FUNC_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model.h"
#include "filemodule.h"

void test_write_to_file(const char *file_name, Data *data);
void test_read_from_file(const char *file_name, Data *data);
int data_cmp(Data *data1, Data *data2);

#endif  // PROJECT_INCLUDE_TEST_FUNC_H_
