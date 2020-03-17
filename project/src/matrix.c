#include "matrix.h"


Matrix* create_matrix(size_t rows, size_t cols) {
    if(rows = 0 || cols = 0) {
        return NULL;
    }

    Matrix* matrix = calloc(1, sizeof(Matrix));

    if(matrix == NULL) {
        printf("%s","Can not calloc memory");
        return NULL[;]
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
    if (matrix == NULL && rows == NULL) {
        return EXIT_FAILURE;
    }

    *rows = matrix->rows;
    return EXIT_SUCCESS;
}

int get_cols(const Matrix* matrix, size_t* cols) {
    if (matrix == NULL && cols == NULL) {
        return EXIT_FAILURE;
    }

    *cols = matrix->cols;
    return EXIT_SUCCESS;
}
