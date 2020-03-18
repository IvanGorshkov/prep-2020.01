#include "matrix.h"


Matrix* create_matrix(size_t rows, size_t cols) {
    if (rows == 0 || cols == 0) {
        return NULL;
    }

    Matrix *matrix = calloc(1, sizeof(Matrix));

    if (matrix == NULL) {
        printf("%s", MERROR);
        return NULL;
    }

    matrix->rows = rows;
    matrix->cols = cols;
    matrix->matrix = calloc(rows*cols, sizeof(double));

    if (matrix->matrix == NULL) {
        free(matrix);
        printf("%s", MERROR);
        return NULL;
    }
    return matrix;
}

int free_matrix(Matrix *matrix) {
    if (matrix == NULL) {
        return EXIT_FAILURE;
    }

    free(matrix->matrix);
    free(matrix);

    return EXIT_SUCCESS;
}

int get_rows(const Matrix *matrix, size_t *rows) {
    if (matrix == NULL || rows == NULL) {
        return EXIT_FAILURE;
    }

    *rows = matrix->rows;
    return EXIT_SUCCESS;
}

int get_cols(const Matrix *matrix, size_t *cols) {
    if (matrix == NULL || cols == NULL) {
        return EXIT_FAILURE;
    }

    *cols = matrix->cols;
    return EXIT_SUCCESS;
}

int get_elem(const Matrix *matrix, size_t row, size_t col, double *val) {
    if (matrix == NULL || val == NULL) {
        return EXIT_FAILURE;
    }

    if (matrix->cols < col || matrix->rows < row) {
        return EXIT_FAILURE;
    }

    *val = matrix->matrix[(matrix->cols * row)+col];
    return EXIT_SUCCESS;
}

int set_elem(Matrix *matrix, size_t row, size_t col, double val) {
    if (matrix == NULL) {
        return EXIT_FAILURE;
    }

    if (matrix->cols < col || matrix->rows < row) {
        return EXIT_FAILURE;
    }

    matrix->matrix[(matrix->cols * row)+col] = val;
    return EXIT_SUCCESS;
}

Matrix* mul_scalar(const Matrix *matrix, double val) {
    if (matrix == NULL) {
        return NULL;
    }

    Matrix* mul_matrix = create_matrix(matrix->rows, matrix->cols);

    if (mul_matrix == NULL) {
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

Matrix* transp(const Matrix *matrix) {
    if (matrix == NULL) {
        return NULL;
    }

    Matrix *transp_matrix = create_matrix(matrix->cols, matrix->rows);

    if (transp_matrix == NULL) {
        return NULL;
    }

    int cols = transp_matrix->cols;
    int rows = transp_matrix->rows;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            transp_matrix->matrix[transp_matrix->cols * i+j] = matrix->matrix[matrix->cols * j+i];
        }
    }

    return transp_matrix;
}

Matrix* sum(const Matrix *l, const Matrix *r) {
    if (l == NULL || r == NULL) {
        return NULL;
    }

    if (l->cols != r->cols && l->rows != r->rows) {
        return NULL;
    }

    Matrix *sum_matrix = create_matrix(l->rows, l->cols);

    if (sum_matrix == NULL) {
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

Matrix* sub(const Matrix *l, const Matrix *r) {
    if (l == NULL || r == NULL) {
        return NULL;
    }

    if (l->cols != r->cols && l->rows != r->rows) {
        return NULL;
    }

    Matrix *sub_matrix = create_matrix(l->rows, l->cols);

    if (sub_matrix == NULL) {
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

Matrix* mul(const Matrix *l, const Matrix *r) {
    if (l == NULL || r == NULL) {
        return NULL;
    }

    if (l->cols != r->rows && l->rows != r->cols) {
        return NULL;
    }

    Matrix* mul_matrix = create_matrix(r->cols, l->rows);

    if (mul_matrix == NULL) {
        return NULL;
    }

    int rows = mul_matrix->rows;
    int cols = mul_matrix->cols;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            for (size_t k = 0; k < r->rows; k++) {
                double data = l->matrix[l->cols * i+k] * r->matrix[r->cols * k+j];
                mul_matrix->matrix[cols * i+j] += data;
            }
        }
    }

    return mul_matrix;
}



int det(const Matrix *matrix, double *val) {
    if (matrix == NULL || val == NULL) {
        return EXIT_FAILURE;
    }

    int rows = matrix->rows;
    int cols = matrix->cols;

    if (rows != cols) {
        return EXIT_FAILURE;
    }

    if (rows == 1) {
        *val = matrix->matrix[0];
    }

    if (rows == 2) {
        *val = matrix->matrix[0] * matrix->matrix[3] - matrix->matrix[1] * matrix->matrix[2];
    }

    int k = 1;

    if (rows > 2) {
        Matrix *matrix_det = create_matrix(matrix->rows-1, matrix->cols-1);

        if (matrix_det == NULL) {
            return 1;
        }

        int n = matrix->cols;
        int col = 0;
        double res = 0;

        for (int row = 0; row < n; row++) {
            double val1;
            get_elem(matrix, row, col, &val1);
            int y = 0;
            for (int d_row = 0; d_row < n; d_row++) {
                int x = 0;
                int true_bool = 0;

                for (int d_col = 0; d_col < n; d_col++) {
                    if (d_row != row && d_col != 0) {
                        double val2;
                        get_elem(matrix, d_row, d_col, &val2);
                        set_elem(matrix_det, y, x, val2);
                        x++;
                        true_bool = 1;
                    }
                }

                if (true_bool == 1) {
                    y++;
                }
            }

            double val3;
            det(matrix_det, &val3);
            res += val1*k*val3;
            k = -k;
        }

        *val = res;
        free(matrix_det);
    }

    return EXIT_SUCCESS;
}

Matrix* adj(const Matrix *matrix) {
    if (matrix == NULL) {
        return NULL;
    }

    if (matrix->rows != matrix->cols) {
        return NULL;
    }

    int rows = matrix->rows;
    int cols = matrix->cols;
    Matrix *adj_matrix = create_matrix(rows, cols);

    if (adj_matrix == NULL) {
        return NULL;
    }

    int r = 0;
    for (int i = 0; i < rows; i++) {
        int c = 0;
        for (int j = 0; j < cols; j++) {
            int y = 0;

            Matrix *tmp_matrix = create_matrix(rows-1, cols-1);

            for (int k = 0; k < rows; k++) {
                int x = 0;
                int true_bool = 0;

                for (int z = 0; z < cols; z++) {
                    if (r != k && c != z) {
                        true_bool = 1;
                        set_elem(tmp_matrix, y, x, matrix->matrix[cols * k+z]);
                        x++;
                    }
                }

                if (true_bool == 1) {
                    y++;
                }
            }

            c++;
            double val;
            det(tmp_matrix, &val);

            if (i%2 != 0) {
                val *= -1;
            }

            if (j%2 != 0) {
                val *= -1;
            }

            set_elem(adj_matrix, i, j, val);
            free_matrix(tmp_matrix);
        }
        r++;
    }
    Matrix *return_matrix = transp(adj_matrix);
    free_matrix(adj_matrix);
    return return_matrix;
}
Matrix* inv(const Matrix *matrix) {
    if (matrix == NULL) {
        return NULL;
    }

    if (matrix->rows != matrix->cols) {
        return NULL;
    }

    double val;
    det(matrix, &val);

    if (matrix->rows == 1) {
        Matrix *return_1_1 = create_matrix(1, 1);
        set_elem(return_1_1, 0, 0, (1/val));
        return return_1_1;
    }

    Matrix *adj_matrix = adj(matrix);
    Matrix *return_matrix = mul_scalar(adj_matrix, (1/val));

    return return_matrix;
}

Matrix* create_matrix_from_file(const char *path_file) {
    if (strlen(path_file) == 0) {
        return NULL;
    }

    FILE *file_ptr = fopen(path_file, "r");
    Matrix *matrix = NULL;

    if (file_ptr == NULL) {
        return NULL;
    }

    int rows = 0;
    int cols = 0;

    if (fscanf(file_ptr, "%d %d", &rows, &cols) != 2) {
        fclose(file_ptr);
        return NULL;
    }

    matrix = create_matrix(rows, cols);

    if (matrix == NULL) {
        fclose(file_ptr);
        return NULL;
    }

    for (int i = 0; i < rows*cols; i++) {
        if (fscanf(file_ptr, "%le", &matrix->matrix[i]) != 1) {
            free_matrix(matrix);
            fclose(file_ptr);
            return NULL;
        }
    }

    fclose(file_ptr);
    return matrix;
}
