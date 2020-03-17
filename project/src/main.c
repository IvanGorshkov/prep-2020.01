#include <stdio.h>
#include "matrix.h"

int main(void) {
    Matrix* matrix = create_matrix(3,3);

    set_elem(matrix, 1, 1, 6);
    set_elem(matrix, 1, 2, 7);
    set_elem(matrix, 1, 3, 3);
    printf("\n");
    set_elem(matrix, 2, 1, 22);
    set_elem(matrix, 2, 2, 3);
    set_elem(matrix, 2, 3, 4);
     printf("\n");
    set_elem(matrix, 3, 1, 6);
    set_elem(matrix, 3, 2, 76);
    set_elem(matrix, 3, 3, 6);
     printf("\n");
    
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
    det(matrix, &val);
   // printf("%f\n", val);
    return 0;
}

