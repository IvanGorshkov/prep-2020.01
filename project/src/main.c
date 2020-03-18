#include "utils.h"

int main(void) {
    int choice = 0;
    Data client_data = {0};
    Data transfer = {0};
    output_menu(MAIN_MENU);

    while (scanf("%d", &choice) != EOF) {
        switch (choice) {
            case 1: {
                FILE *ptr_master = fopen(RECORD_FILENAME, "w+");

                if (ptr_master == NULL) {
                    printf("%s%s file", NOT_ACESS, RECORD_FILENAME);
                    break;
                }

                master_write(ptr_master, client_data);
                fclose(ptr_master);
                break;
            }
            case 2: {
                FILE *ptr_transaction = fopen(TRANSACTION_FILENAME, "w+");

                if (ptr_transaction == NULL) {
                    printf("%s%s file", NOT_ACESS, TRANSACTION_FILENAME);
                    break;
                }

                transaction_write(ptr_transaction, transfer);
                fclose(ptr_transaction);
                break;
            }
            case 3: {
                FILE *ptr_master = fopen(RECORD_FILENAME, "r");
                FILE *ptr_transaction = fopen(TRANSACTION_FILENAME, "r");
                FILE *ptr_black_record = fopen(BLACKRECORD_FILENAME, "w+");

                if (ptr_master == NULL || ptr_transaction == NULL || ptr_black_record == NULL) {
                    printf("%s%s, %s or %s files",
                           NOT_ACESS, RECORD_FILENAME,
                           TRANSACTION_FILENAME,
                           BLACKRECORD_FILENAME);

                    if (ptr_master != NULL) {
                        fclose(ptr_master);
                    }

                    if (ptr_transaction != NULL) {
                        fclose(ptr_transaction);
                    }

                    if (ptr_black_record != NULL) {
                        fclose(ptr_black_record);
                    }

                    break;
                }

                black_record_write(ptr_master, ptr_transaction, ptr_black_record, client_data,  transfer);
                fclose(ptr_master);
                fclose(ptr_transaction);
                fclose(ptr_black_record);
                break;
            }
            default:
                printf("no such action");
                break;
            }

        output_menu(MAIN_MENU);
    }

  return 0;
}
