#ifndef MODEL_H
#define MODEL_H
struct Master_record{
  int number;
  char name[20];
  char surname[20];
  char addres[30];
  char tel_number[15];
  double indebtedness;
  double credit_limit;
  double cash_payments;
};
typedef struct Master_record Data;

#endif //MODEL_H
