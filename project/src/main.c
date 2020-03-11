#include "utils.h"


int main(void) {
    int choice = 0;
    FILE *ptr_master = NULL;
    FILE *ptr_transaction = NULL;
    FILE *ptr_black_record = NULL;
    Data client_data = {0};
    Data transfer = {0};
    output_menu(main_menu);

    while (scanf("%d", &choice) != end_of_file) {
        switch (choice) {
            case 1: {
                ptr_master = fopen(filename_1, "w+");

                if (ptr_master == NULL) {
                    printf("Not acess");
                    break;
                }

                master_write(ptr_master, client_data);
                fclose(ptr_master);
                break;
            }
            case 2: {
                ptr_transaction = fopen(filename_2, "w+");

                if (ptr_transaction == NULL) {
                    printf("Not acess");
                    break;
                }

                transaction_write(ptr_transaction, transfer);
                fclose(ptr_transaction);
                break;
            }
            case 3: {
                ptr_master = fopen(filename_1, "r");
                ptr_transaction = fopen(filename_2, "r");
                ptr_black_record = fopen(filename_3, "w+");

                if (ptr_master == NULL || ptr_transaction == NULL) {
                    printf("don't exist %s or %s files", filename_1, filename_2);
                    break;
                }

                black_record(ptr_master, ptr_transaction, ptr_black_record, client_data,  transfer);
                fclose(ptr_master);
                fclose(ptr_transaction);
                fclose(ptr_black_record);
                break;
            }
            default:
                printf("no such action");
                break;
            }

        output_menu(main_menu);
    }

  return 0;
}
