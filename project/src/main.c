#include "utils.h"

int main(void) {
    int choice = 0;
    Data client_data = {0};
    Data transfer = {0};
    output_menu(main_menu);

    while (scanf("%d", &choice) != EOF) {
        switch (choice) {
            case 1: {
                FILE *ptr_master = fopen(filename_1, "w+");

                if (ptr_master == NULL) {
                    printf("%s%s file", not_acess, filename_1);
                    break;
                }

                master_write(ptr_master, client_data);
                fclose(ptr_master);
                break;
            }
            case 2: {
                FILE *ptr_transaction = fopen(filename_2, "w+");

                if (ptr_transaction == NULL) {
                    printf("%s%s file", not_acess, filename_2);
                    break;
                }

                transaction_write(ptr_transaction, transfer);
                fclose(ptr_transaction);
                break;
            }
            case 3: {
                FILE *ptr_master = fopen(filename_1, "r");
                FILE *ptr_transaction = fopen(filename_2, "r");
                FILE *ptr_black_record = fopen(filename_3, "w+");

                if (ptr_master == NULL || ptr_transaction == NULL || ptr_black_record == NULL) {
                    printf("%s%s, %s or %s files", not_acess, filename_1, filename_2, filename_3);
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
