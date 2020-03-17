#include "filemodule.h"

void master_write(FILE *ptr_master, Data client) {
    output_menu(MENU_MASTER);

    while (scanf(" %d%19s%19s%29s%14s%lf%lf%lf",
                 &client.number,
                 client.name,
                 client.surname,
                 client.address,
                 client.tel_number,
                 &client.indebtedness,
                 &client.credit_limit,
                 &client.cash_payments) != EOF) {
        write_to_file(ptr_master, client);
        output_menu(MENU_MASTER);
    }
}

void transaction_write(FILE *ptr_transaction, Data transfer) {
    output_menu(MENU_TRANSACTION);

    while (scanf("%d %lf", &transfer.number, &transfer.cash_payments) != EOF) {
        fprintf(ptr_transaction, "%-3d%-6.2f\n", transfer.number, transfer.cash_payments);
        output_menu(MENU_TRANSACTION);
    }
}

void black_record_write(FILE *ptr_master,
                        FILE *ptr_transaction,
                        FILE *ptr_black_record,
                        Data client_data,
                        Data transfer) {
    while (read_from_file(ptr_master, &client_data) != EOF) {
         while (fscanf(ptr_transaction, "%d %lf", &transfer.number, &transfer.cash_payments) != EOF) {
                if (client_data.number == transfer.number && transfer.cash_payments != 0) {
                    client_data.credit_limit += transfer.cash_payments;
                }
            }
        write_to_file(ptr_black_record, client_data);
        rewind(ptr_transaction);
    }
}

void write_to_file(FILE *ptr_file, Data client_data) {
    fprintf(ptr_file, "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n",
            client_data.number,
            client_data.name,
            client_data.surname,
            client_data.address,
            client_data.tel_number,
            client_data.indebtedness,
            client_data.credit_limit,
            client_data.cash_payments);
}

int read_from_file(FILE *ptr_file, Data *client_data) {
    return fscanf(ptr_file, "%d%19s%19s%29s%14s%lf%lf%lf",
                  &client_data->number,
                  client_data->name,
                  client_data->surname,
                  client_data->address,
                  client_data->tel_number,
                  &client_data->indebtedness,
                  &client_data->credit_limit,
                  &client_data->cash_payments);
}
