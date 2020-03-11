#ifndef PROJECT_INCLUDE_MODEL_H_
#define PROJECT_INCLUDE_MODEL_H_

typedef struct master_record {
  int number;
  char name[20];
  char surname[20];
  char address[30];
  char tel_number[15];
  double indebtedness;
  double credit_limit;
  double cash_payments;
} Data;

#endif  // PROJECT_INCLUDE_MODEL_H_
