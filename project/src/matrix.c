#include "matrix.h"


Matrix* create_matrix(size_t rows, size_t cols) {
    if(rows == 0 || cols == 0) {
        return NULL;
    }

    Matrix* matrix = calloc(1, sizeof(Matrix));

    if(matrix == NULL) {
        printf("%s","Can not calloc memory");
        return NULL;
    }

    matrix->rows = rows;
    matrix->cols = cols;
    matrix->matrix = calloc(rows*cols, sizeof(double));

    if(matrix->matrix == NULL) {
        printf("%s","Can not calloc memory");
        return NULL;
    }
    return matrix;
}

int free_matrix(Matrix* matrix) {
    if (matrix == NULL) {
        return EXIT_FAILURE;
    }

    free(matrix->matrix);
    free(matrix);

    if (matrix == NULL && matrix->matrix == NULL) {
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

int get_rows(const Matrix* matrix, size_t* rows) {
    if (matrix == NULL || rows == NULL) {
        return EXIT_FAILURE;
    }

    *rows = matrix->rows;
    return EXIT_SUCCESS;
}

int get_cols(const Matrix* matrix, size_t* cols) {
    if (matrix == NULL || cols == NULL) {
        return EXIT_FAILURE;
    }

    *cols = matrix->cols;
    return EXIT_SUCCESS;
}

int get_elem(const Matrix* matrix, size_t row, size_t col, double* val) {
    if (matrix == NULL || val == NULL || row <= 0 || col <= 0) {
        return EXIT_FAILURE;
    }

    if (matrix->cols < col || matrix->rows < row) {
        return EXIT_FAILURE;
    }

    *val = matrix->matrix[(matrix->cols * (row-1))+col-1];
    return EXIT_SUCCESS;
}

int set_elem(Matrix* matrix, size_t row, size_t col, double val) {
    if (matrix == NULL || row <= 0 || col <= 0) {
        return EXIT_FAILURE;
    }
    
    if (matrix->cols < col || matrix->rows < row) {
        return EXIT_FAILURE;
    }
    matrix->matrix[(matrix->cols * (row-1))+col-1] = val;
    return EXIT_SUCCESS;
}

Matrix* mul_scalar(const Matrix* matrix, double val) {
    if(matrix == NULL) {
        return NULL;
    }
    
    Matrix* mul_matrix = create_matrix(matrix->rows, matrix->cols);
    
    if(mul_matrix == NULL) {
        return NULL;
    }
    
    int cols = mul_matrix->cols;
    int rows = mul_matrix->rows;
    
    for (int i = 0; i < cols*rows; i++) {
            double data = matrix->matrix[i] * val;
            mul_matrix->matrix[i] = data;
    }
    return mul_matrix;
}

Matrix* transp(const Matrix* matrix) {
    if(matrix == NULL) {
        return NULL;
    }
    
    Matrix* transp_matrix = create_matrix(matrix->cols, matrix->rows);
    
    if(transp_matrix == NULL) {
        return NULL;
    }
    
    int cols = transp_matrix->cols;
    int rows = transp_matrix->rows;
    printf("%i\n",cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            transp_matrix->matrix[transp_matrix->cols * i+j] = matrix->matrix[matrix->cols * j+i];
        }
    }
    return transp_matrix;
}

Matrix* sum(const Matrix* l, const Matrix* r) {
    if(l == NULL || r == NULL) {
        return NULL;
    }
    
    if(l->cols != r->cols && l->rows != r->rows) {
        return NULL;
    }
    
    Matrix* sum_matrix = create_matrix(l->rows, l->cols);
    
    if(sum_matrix == NULL) {
        return NULL;
    }
    
    int cols = sum_matrix->cols;
    int rows = sum_matrix->rows;
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            double data = l->matrix[l->cols * i+j] + r->matrix[r->cols * i+j];
            sum_matrix->matrix[sum_matrix->cols * i+j] = data;
            
        }
    }
    
    return sum_matrix;
}
Matrix* sub(const Matrix* l, const Matrix* r){
    if(l == NULL || r == NULL) {
           return NULL;
       }
       
       if(l->cols != r->cols && l->rows != r->rows) {
           return NULL;
       }
       
       Matrix* sub_matrix = create_matrix(l->rows, l->cols);
       
       if(sub_matrix == NULL) {
           return NULL;
       }
       
       int cols = sub_matrix->cols;
       int rows = sub_matrix->rows;
       
       for (int i = 0; i < rows; i++) {
           for (int j = 0; j < cols; j++) {
               double data = l->matrix[l->cols * i+j] - r->matrix[r->cols * i+j];
               sub_matrix->matrix[sub_matrix->cols * i+j] = data;
               
           }
       }
       
       return sub_matrix;
}
