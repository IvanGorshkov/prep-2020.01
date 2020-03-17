#include "test_func.h"


void test_write_to_file(const char *file_name, Data *data) {
    FILE *file_ptr_test = fopen(file_name, "w+");
    if (file_ptr_test == NULL) {
         printf("%s%s file", NOT_ACESS, file_name);
        return;
    }
    write_to_file(file_ptr_test, *data);
    fclose(file_ptr_test);
}

void test_read_from_file(const char *file_name, Data *data) {
    FILE *file_ptr_test = fopen(file_name, "r+");
    if (file_ptr_test == NULL) {
        printf("%s%s file", NOT_ACESS, file_name);
        return;
    }
    read_from_file(file_ptr_test, data);
    fclose(file_ptr_test);
}

int data_cmp(Data *got_data, Data *expected_data) {
    if (got_data->number == expected_data->number &&
        strcmp(got_data->name, expected_data->name) == 0 &&
        strcmp(got_data->surname, expected_data->surname) == 0 &&
        strcmp(got_data->address, expected_data->address) == 0 &&
        strcmp(got_data->tel_number, expected_data->tel_number) == 0 &&
        got_data->indebtedness == expected_data->indebtedness &&
        got_data->cash_payments == expected_data->cash_payments &&
        got_data->credit_limit == expected_data->credit_limit) {
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}

