#include "test.h"

int main(void) {
    const char *file_to_read = "btests/record.dat.gold";
    const char *file_to_write = "test_file.dat";

    Data expected_data = {
    .number = 1,
    .name = "name_1",
    .surname = "surname_1",
    .address = "address_1",
    .tel_number = "tel_1",
    .indebtedness = 80.00,
    .credit_limit = 150.00,
    .cash_payments = 20.00 };
    test_write_to_file(file_to_write, &expected_data);

    Data got_data = {};
    test_read_from_file(file_to_read, &got_data);

    if (data_cmp(&expected_data, &got_data) == EXIT_SUCCESS) {
        printf("%s\n", "SUCCESS");
        return EXIT_SUCCESS;
    }
    printf("%s\n", "SOMETHING GOES WRONG");
    return EXIT_FAILURE;
}
