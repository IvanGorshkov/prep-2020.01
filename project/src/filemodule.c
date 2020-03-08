#include "filemodule.h"

void masterWrite(FILE *of_ptr, Data client) {
    output_menu(1);

    while(scanf(" %d%s%s%s%s%lf%lf%lf",&client.number, client.name, client.surname, client.addres, client.tel_number, &client.indebtedness, &client.credit_limit,	&client.cash_payments) != -1) {
        int a = 0;

        fprintf(of_ptr, "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n", client.number, client.name, client.surname, client.addres, client.tel_number, client.indebtedness, client.credit_limit, client.cash_payments);

            puts("continue?\n 1 - yes\n 2- no");
            if (scanf("%d",&a) != -1 && a == 2) {
                break;
           }

   output_menu(1);
    }
}

void transactionWrite(FILE *of_ptr,Data transfer) {
        output_menu(2);

        while(scanf("%d %lf", &transfer.number, &transfer.cash_payments) != -1) {
            int a = 0;

            fprintf(of_ptr, "%-3d%-6.2f\n", transfer.number, transfer.cash_payments);

            puts("continue?\n 1 - yes\n 2- no");

            if (scanf("%d",&a) != -1 && a == 2) {
                break;
            }

        output_menu(2);
        }
}

void blackRecord(FILE *of_ptr, FILE *of_ptr_2, FILE *blackrecord, Data client_data, Data transfer) {
	while(fscanf(of_ptr ,"%d%s%s%s%s%lf%lf%lf",&client_data.number, client_data.name, client_data.surname, client_data.addres, client_data.tel_number, &client_data.indebtedness, &client_data.credit_limit, &client_data.cash_payments) != -1) {

            while (fscanf(of_ptr_2, "%d %lf", &transfer.number, &transfer.cash_payments) != -1) {
					if(client_data.number == transfer.number && transfer.cash_payments != 0) {
						client_data.credit_limit += transfer.cash_payments;
					} 
				}

            fprintf(blackrecord, "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n", client_data.number, client_data.name, client_data.surname, client_data.addres, client_data.tel_number, client_data.indebtedness, client_data.credit_limit, client_data.cash_payments);

			rewind(of_ptr_2);
    }
}
