#include <stdio.h>
#include "matrix.h"

int main(void) {
    Matrix* matrix = create_matrix(4,4);

    set_elem(matrix, 1, 1, 6);
    set_elem(matrix, 1, 2, -5);
    set_elem(matrix, 1, 3, 8);
    set_elem(matrix, 1, 4, 4);
    printf("\n");
    set_elem(matrix, 2, 1, 9);
    set_elem(matrix, 2, 2, 7);
    set_elem(matrix, 2, 3, 5);
    set_elem(matrix, 2, 4, 2);
     printf("\n");
    set_elem(matrix, 3, 1, 7);
    set_elem(matrix, 3, 2, 5);
    set_elem(matrix, 3, 3, 3);
    set_elem(matrix, 3, 4, 7);
    printf("\n");
     set_elem(matrix, 4, 1, -4);
     set_elem(matrix, 4, 2, 8);
     set_elem(matrix, 4, 3, -8);
     set_elem(matrix, 4, 4, -3);
    
    double val;
    
    Matrix *muls = mul_scalar(matrix,2);
    get_elem(muls, 4, 3, &val);
    size_t count;
    get_rows(matrix, &count);
    get_cols(matrix, &count);
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
        
    Matrix *file = create_matrix_from_file("in.txt");
    get_cols(file, &count);
    Matrix *inv_matrix = inv(matrix);
    get_elem(inv_matrix, 2, 2, &val);
    return 0;
}

