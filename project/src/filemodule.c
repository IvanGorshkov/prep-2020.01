#include "filemodule.h"

void master_write(FILE *of_ptr, Data client) {
    output_menu(menu_master);

    while (scanf(" %d%20s%20s%30s%15s%lf%lf%lf",
                 &client.number,
                 client.name,
                 client.surname,
                 client.address,
                 client.tel_number,
                 &client.indebtedness,
                 &client.credit_limit,
                 &client.cash_payments) != end_of_file) {
        write_to_file(of_ptr, client);
        output_menu(menu_master);
    }
}

void transaction_write(FILE *of_ptr, Data transfer) {
    output_menu(menu_transaction);

    while (scanf("%d %lf", &transfer.number, &transfer.cash_payments) != end_of_file) {
        fprintf(of_ptr, "%-3d%-6.2f\n", transfer.number, transfer.cash_payments);
        output_menu(menu_transaction);
    }
}

void black_record(FILE *of_ptr, FILE *of_ptr_2, FILE *blackrecord, Data client_data, Data transfer) {
    while (read_from_file(of_ptr, &client_data) != end_of_file) {
         while (fscanf(of_ptr_2, "%d %lf", &transfer.number, &transfer.cash_payments) != end_of_file) {
                if (client_data.number == transfer.number && transfer.cash_payments != 0) {
                    client_data.credit_limit += transfer.cash_payments;
                }
            }
        write_to_file(blackrecord, client_data);
        rewind(of_ptr_2);
    }
}

void write_to_file(FILE *of_ptr, Data client_data) {
    fprintf(of_ptr, "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n",
            client_data.number,
            client_data.name,
            client_data.surname,
            client_data.address,
            client_data.tel_number,
            client_data.indebtedness,
            client_data.credit_limit,
            client_data.cash_payments);
}

int read_from_file(FILE *of_ptr, Data *client_data) {
    return fscanf(of_ptr, "%d%20s%20s%20s%20s%lf%lf%lf",
                  &client_data->number,
                  client_data->name,
                  client_data->surname,
                  client_data->address,
                  client_data->tel_number,
                  &client_data->indebtedness,
                  &client_data->credit_limit,
                  &client_data->cash_payments);
}
