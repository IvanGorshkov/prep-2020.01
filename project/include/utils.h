#define UTILS_H
#ifndef UTILS_H

#include <stdio.h>
#include <stdlib.h>
#define filename "transaction.dat"

void masterWrite(FILE *ofPTR, Data Client);
void transactionWrite(FILE *ofPTR, Data transfer);
void blackRecord(FILE *ofPTR, FILE *ofPTR_2, FILE *blackrecord, Data client_data, Data transfer);
#endif //UTILS_H
