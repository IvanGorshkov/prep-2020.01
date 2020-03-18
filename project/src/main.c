#include <stdio.h>
#include "matrix.h"

int main(void) {
    char *file_ptr = "matrix.txt";
    Matrix *matrix = create_matrix_from_file(file_ptr);

    size_t size;
    get_rows(matrix, &size);
    printf("Count of rows: %zu\n", size);
    get_cols(matrix, &size);
    printf("Count of cols: %zu\n", size);

    set_elem(matrix, 0, 0, 20.05);
    double elem;
    get_elem(matrix, 0, 0, &elem);
    printf("matrix elem[0][0] = %f\n", elem);

    Matrix *mul_s_matrix = mul_scalar(matrix, 2.0);
    get_elem(mul_s_matrix, 1, 0, &elem);
    printf("mul_s_matrix elem[1][0] = %f\n", elem);

    Matrix *transp_matrix =  transp(mul_s_matrix);
    get_elem(transp_matrix, 0, 1, &elem);
    printf("transp_matrix elem[0][1] = %f\n", elem);

    Matrix *sum_matrix = sum(matrix, mul_s_matrix);
    get_elem(sum_matrix, 0, 0, &elem);
    printf("sum_matrix elem[0][0] = %f\n", elem);

    Matrix *sub_matrix = sub(sum_matrix, mul_s_matrix);
    get_elem(sub_matrix, 0, 0, &elem);
    printf("sub_matrix elem[0][0] = %f\n", elem);

    Matrix *mul_matrix = mul(sum_matrix, sub_matrix);
    get_elem(mul_matrix, 0, 0, &elem);
    printf("mul_matrix elem[0][0] = %f\n", elem);

    double val;
    det(matrix, &val);
    printf("det of matrix: %f\n", val);

    Matrix *adj_matrix = adj(matrix);
    get_elem(adj_matrix, 0, 0, &elem);
    printf("adj_matrix elem[0][0] = %f\n", elem);

    Matrix *inv_matrix = inv(matrix);
    get_elem(inv_matrix, 0, 0, &elem);
    printf("inv_matrix elem[0][0] = %f\n", elem);

    free_matrix(inv_matrix);
    free_matrix(adj_matrix);
    free_matrix(mul_matrix);
    free_matrix(sub_matrix);
    free_matrix(sum_matrix);
    free_matrix(transp_matrix);
    free_matrix(mul_s_matrix);
    free_matrix(matrix);
    return 0;
}

