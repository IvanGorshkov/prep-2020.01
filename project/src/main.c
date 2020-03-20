#include <stdio.h>
#include "matrix.h"


int main(void) {
    const char *file_ptr = "matrix.txt";
    Matrix *matrix = create_matrix_from_file(file_ptr);
    int myfunc(int count, ...);
    if (matrix == NULL) {
        return 1;
    }

    size_t size = 0;

    if (get_rows(matrix, &size)) {
        free_matrix(matrix);
        return 1;
    }

    printf("Count of rows: %zu\n", size);

    if (get_cols(matrix, &size)) {
        free_matrix(matrix);
        return 1;
    }

    printf("Count of cols: %zu\n", size);

    if (set_elem(matrix, 0, 0, 20.05)) {
        free_matrix(matrix);
        return 1;
    }

    double elem = 0;

    if (get_elem(matrix, 0, 0, &elem)) {
        free_matrix(matrix);
        return 1;
    }

    printf("matrix elem[0][0] = %f\n", elem);

    Matrix *mul_s_matrix = mul_scalar(matrix, 2.0);

    if (mul_s_matrix == NULL) {
        free_matrix(matrix);
        return 1;
    }

    get_elem(mul_s_matrix, 1, 0, &elem);
    
    if (get_elem(mul_s_matrix, 1, 0, &elem)) {
        free_matrix(mul_s_matrix);
        free_matrix(matrix);
        return 1;
    }
    
    printf("mul_s_matrix elem[1][0] = %f\n", elem);

    Matrix *transp_matrix =  transp(mul_s_matrix);

    if (transp_matrix == NULL) {
        free_matrix(mul_s_matrix);
        free_matrix(matrix);
        return 1;
    }

    if (get_elem(transp_matrix, 0, 1, &elem)) {
        free_matrix(transp_matrix);
        free_matrix(mul_s_matrix);
        free_matrix(matrix);
        return 1;
    }

    printf("transp_matrix elem[0][1] = %f\n", elem);

    Matrix *sum_matrix = sum(matrix, mul_s_matrix);

    if (sum_matrix == NULL) {
        free_matrix(transp_matrix);
        free_matrix(mul_s_matrix);
        free_matrix(matrix);
        return 1;
    }

    if (get_elem(sum_matrix, 0, 0, &elem)) {
        free_matrix(sum_matrix);
        free_matrix(transp_matrix);
        free_matrix(mul_s_matrix);
        free_matrix(matrix);
        return 1;
    }

    printf("sum_matrix elem[0][0] = %f\n", elem);

    Matrix *sub_matrix = sub(sum_matrix, mul_s_matrix);

    if (sub_matrix == NULL) {
        free_matrix(sum_matrix);
        free_matrix(transp_matrix);
        free_matrix(mul_s_matrix);
        free_matrix(matrix);
        return 1;
    }

    if (get_elem(sub_matrix, 0, 0, &elem)) {
        free_matrix(sub_matrix);
        free_matrix(sum_matrix);
        free_matrix(transp_matrix);
        free_matrix(mul_s_matrix);
        free_matrix(matrix);
        return 1;
    }

    printf("sub_matrix elem[0][0] = %f\n", elem);

    Matrix *mul_matrix = mul(sum_matrix, sub_matrix);

    if (mul_matrix == NULL) {
        free_matrix(sub_matrix);
        free_matrix(sum_matrix);
        free_matrix(transp_matrix);
        free_matrix(mul_s_matrix);
        free_matrix(matrix);
        return 1;
    }

    if (get_elem(mul_matrix, 0, 0, &elem)) {
        
        free_matrix(mul_matrix);
        free_matrix(sub_matrix);
        free_matrix(sum_matrix);
        free_matrix(transp_matrix);
        free_matrix(mul_s_matrix);
        free_matrix(matrix);
        return 1;
    }

    printf("mul_matrix elem[0][0] = %f\n", elem);

    double val = 0;
    
    if (det(matrix, &val)) {
        free_matrix(mul_matrix);
        free_matrix(sub_matrix);
        free_matrix(sum_matrix);
        free_matrix(transp_matrix);
        free_matrix(mul_s_matrix);
        free_matrix(matrix);
        return 1;
    }
    
    printf("det of matrix: %f\n", val);

    Matrix *adj_matrix = adj(matrix);

    if (adj_matrix == NULL) {
        free_matrix(mul_matrix);
        free_matrix(sub_matrix);
        free_matrix(sum_matrix);
        free_matrix(transp_matrix);
        free_matrix(mul_s_matrix);
        free_matrix(matrix);
        return 1;
    }

    if (get_elem(adj_matrix, 0, 0, &elem)) {
        free_matrix(adj_matrix);
        free_matrix(mul_matrix);
        free_matrix(sub_matrix);
        free_matrix(sum_matrix);
        free_matrix(transp_matrix);
        free_matrix(mul_s_matrix);
        free_matrix(matrix);
        return 1;
    }
    
    printf("adj_matrix elem[0][0] = %f\n", elem);

    Matrix *inv_matrix = inv(matrix);

    if (inv_matrix == NULL) {
        free_matrix(adj_matrix);
        free_matrix(mul_matrix);
        free_matrix(sub_matrix);
        free_matrix(sum_matrix);
        free_matrix(transp_matrix);
        free_matrix(mul_s_matrix);
        free_matrix(matrix);
        return 1;
    }

    
    if (get_elem(inv_matrix, 0, 0, &elem)) {
        free_matrix(inv_matrix);
        free_matrix(adj_matrix);
        free_matrix(mul_matrix);
        free_matrix(sub_matrix);
        free_matrix(sum_matrix);
        free_matrix(transp_matrix);
        free_matrix(mul_s_matrix);
        free_matrix(matrix);
        return 1;
    }
    
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
