#include "menu.h"

void output_menu(int num) {
    switch (num) {
        case 1:
            printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n",
                   "1 Number account: ",
                   "2 Client name: ",
                   "3 Surname: ",
                   "4 Addres client: ",
                   "5 Client Telnum: ",
                   "6 Client indebtedness: ",
                   "7 Client credit limit: ",
                   "8 Client cash payments: ");
            break;
        case 2:
            printf("%s\n%s\n",
                   "1 Number account: ",
                   "2 Client cash payments: ");
            break;
        case 3:
            printf("%s\n%s\n%s\n%s\n",
                   "please enter action",
                   "1 enter data client:",
                   "2 enter data transaction:",
                   "3 update base");
            break;
        default:
            break;
    }
}
