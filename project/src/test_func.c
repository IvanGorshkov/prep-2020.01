#include "test_func.h"


void test_write_to_file(const char *file_name, Data *data) {
    FILE *ptr = fopen(file_name, "w+");
    if (ptr == NULL) {
        puts("No access");
    } else {
        write_to_file(ptr, *data);
        fclose(ptr);
    }
}
void test_read_from_file(const char *file_name, Data *data) {
    FILE *ptr = fopen(file_name, "r+");
    if (ptr == NULL) {
        puts("No access");
    } else {
        read_from_file(ptr, data);
        fclose(ptr);
    }
}
int data_cmp(Data *got_data, Data *expected_data) {
    if (got_data->number == expected_data->number &&
        strcmp(got_data->name, expected_data->name) == 0 &&
        strcmp(got_data->surname, expected_data->surname) == 0 &&
        strcmp(got_data->addres, expected_data->addres) == 0 &&
        strcmp(got_data->tel_number, expected_data->tel_number) == 0 &&
        got_data->indebtedness == expected_data->indebtedness &&
        got_data->cash_payments == expected_data->cash_payments &&
        got_data->credit_limit == expected_data->credit_limit) {
        return 1;
    }

    return 0;
}

