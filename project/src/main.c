#include <stdio.h>
#include "matrix.h"

int main(void) {
    Matrix* matrix = create_matrix(10,10);
    size_t rows = 0;
    size_t cols = 0;
    get_rows(matrix, &rows);
    printf("%zu\n", rows);
    get_cols(matrix, &cols);
    printf("%zu\n", cols);
    set_elem(matrix, 1, 1, 1);
    set_elem(matrix, 1, 2, 2);
    set_elem(matrix, 1, 3, 3);
    double val;
    get_elem(matrix, 1, 3, &val);
    printf("%f\n", val);
    Matrix* mul_matrix = mul_scalar(matrix, 2);
    get_elem(mul_matrix, 1, 3, &val);
    printf("%f\n", val);
    return 0;
}

