#include <stdio.h>
#include "matrix.h"

int main(void) {
    Matrix* matrix = create_matrix(4,3);

    set_elem(matrix, 1, 1, 1);
    set_elem(matrix, 1, 2, 2);
    set_elem(matrix, 1, 3, 3);
    printf("\n");
    set_elem(matrix, 2, 1, 4);
    set_elem(matrix, 2, 2, 5);
    set_elem(matrix, 2, 3, 6);
     printf("\n");
    set_elem(matrix, 3, 1, 7);
    set_elem(matrix, 3, 2, 8);
    set_elem(matrix, 3, 3, 9);
     printf("\n");
    set_elem(matrix, 4, 1, 10);
    set_elem(matrix, 4, 2, 11);
    set_elem(matrix, 4, 3, 12);
    
    double val;
    
    Matrix *muls = mul_scalar(matrix,2);
    get_elem(muls, 4, 3, &val);
   // printf("%f\n", val);
    Matrix *trans = transp(matrix);
    Matrix *summatrix = sum(muls, matrix);
    get_elem(summatrix, 4, 3, &val);
     //  printf("%f\n", val);
    Matrix *submatrix = sub(summatrix, matrix);
    get_elem(submatrix, 4, 3, &val);
     //  printf("%f\n", val);
    Matrix *mul_matrix = mul(matrix, trans);
    get_elem(mul_matrix, 2, 2, &val);
   // printf("%f\n", val);
    return 0;
}

