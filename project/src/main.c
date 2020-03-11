#include "utils.h"


int main(void) {
    int choice = 0;
    FILE *ptr, *ptr_2, *ptr_3;
    Data client_data = {0};
    Data transfer = {0};
    output_menu(3);

    while (scanf("%d", &choice) != -1) {
        switch (choice) {
            case 1:
                ptr = fopen(filename_1, "w+");

                if (ptr == NULL) {
                    puts("Not acess");
                } else {
                    master_write(ptr, client_data);
                    fclose(ptr);
                }

                break;
            case 2:
                ptr = fopen(filename_2, "w+");

                if (ptr == NULL) {
                    puts("Not acess");
                } else {
                    transaction_write(ptr, transfer);
                    fclose(ptr);
                }

                break;
            case 3:
                ptr = fopen(filename_1, "r");
                ptr_2 = fopen(filename_2, "r");
                ptr_3 = fopen(filename_3, "w");

                if (ptr == NULL || ptr_2 == NULL || ptr_3 == NULL) {
                    puts("exit");
                } else {
                    black_record(ptr, ptr_2, ptr_3, client_data,  transfer);
                    fclose(ptr);
                    fclose(ptr_2);
                    fclose(ptr_3);
                }

                break;
            default:
                puts("error");
                break;
            }

        output_menu(3);
    }

  return 0;
}
