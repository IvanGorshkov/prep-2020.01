#include "matrix.h"
#include <stdio.h>
#include <stdbool.h>
#include <math.h>


Matrix* create_matrix(size_t rows, size_t cols) {
    if (rows == 0 || cols == 0) {
        return NULL;
    }

    Matrix *matrix = calloc(1, sizeof(Matrix));

    if (matrix == NULL) {
        return NULL;
    }

    matrix->rows = rows;
    matrix->cols = cols;
    matrix->matrix = calloc(rows * cols, sizeof(double));

    if (matrix->matrix == NULL) {
        free_matrix(matrix);
        return NULL;
    }
    return matrix;
}

int free_matrix(Matrix *matrix) {
    if (matrix == NULL) {
        return EXIT_FAILURE;
    }

    if (matrix->matrix == NULL) {
        free(matrix);
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
    if (matrix == NULL || val == NULL || matrix->matrix == NULL) {
        return EXIT_FAILURE;
    }

    if (matrix->cols <= col || matrix->rows <= row) {
        return EXIT_FAILURE;
    }

    *val = matrix->matrix[(matrix->cols * row) + col];
    return EXIT_SUCCESS;
}

int set_elem(Matrix *matrix, size_t row, size_t col, double val) {
    if (matrix == NULL || matrix->matrix == NULL) {
        return EXIT_FAILURE;
    }

    if (matrix->cols <= col || matrix->rows <= row) {
        return EXIT_FAILURE;
    }

    matrix->matrix[(matrix->cols * row) + col] = val;
    return EXIT_SUCCESS;
}

Matrix* mul_scalar(const Matrix *matrix, double val) {
    if (matrix == NULL || matrix->matrix == NULL) {
        return NULL;
    }

    Matrix* mul_matrix = create_matrix(matrix->rows, matrix->cols);

    if (mul_matrix == NULL || mul_matrix->matrix == NULL) {
        free_matrix(mul_matrix);
        return NULL;
    }

    size_t cols = mul_matrix->cols;
    size_t rows = mul_matrix->rows;
    size_t c_r_mul = cols * rows;
    for (size_t i = 0; i < c_r_mul; ++i) {
        mul_matrix->matrix[i] = matrix->matrix[i] * val;
    }

    return mul_matrix;
}

Matrix* transp(const Matrix *matrix) {
    if (matrix == NULL || matrix->matrix == NULL) {
        return NULL;
    }

    Matrix *transp_matrix = create_matrix(matrix->cols, matrix->rows);

    if (transp_matrix == NULL || transp_matrix->matrix == NULL) {
        free_matrix(transp_matrix);
        return NULL;
    }

    size_t cols = transp_matrix->cols;
    size_t rows = transp_matrix->rows;

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            transp_matrix->matrix[transp_matrix->cols * i + j] = matrix->matrix[matrix->cols * j + i];
        }
    }

    return transp_matrix;
}

Matrix* sum(const Matrix *l, const Matrix *r) {
    if (l == NULL || r == NULL || r->matrix == NULL || l->matrix == NULL) {
        return NULL;
    }

    if (l->cols != r->cols || l->rows != r->rows) {
        return NULL;
    }

    Matrix *sum_matrix = create_matrix(l->rows, l->cols);

    if (sum_matrix == NULL || sum_matrix->matrix == NULL) {
        free_matrix(sum_matrix);
        return NULL;
    }

    size_t cols = sum_matrix->cols;
    size_t rows = sum_matrix->rows;

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            sum_matrix->matrix[cols * i + j] = l->matrix[cols * i + j] + r->matrix[cols * i + j];
        }
    }

    return sum_matrix;
}

Matrix* sub(const Matrix *l, const Matrix *r) {
    if (l == NULL || r == NULL || r->matrix == NULL || l->matrix == NULL) {
        return NULL;
    }

    if (l->cols != r->cols || l->rows != r->rows) {
        return NULL;
    }

    Matrix *sub_matrix = create_matrix(l->rows, l->cols);

    if (sub_matrix == NULL || sub_matrix->matrix == NULL) {
        free_matrix(sub_matrix);
        return NULL;
    }

    size_t cols = sub_matrix->cols;
    size_t rows = sub_matrix->rows;

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            double data = l->matrix[l->cols * i + j] - r->matrix[r->cols * i + j];
            sub_matrix->matrix[sub_matrix->cols * i + j] = data;
        }
    }

    return sub_matrix;
}

Matrix* mul(const Matrix *l, const Matrix *r) {
    if (l == NULL || r == NULL || r->matrix == NULL || l->matrix == NULL) {
        return NULL;
    }

    if (l->cols != r->rows) {
        return NULL;
    }

    Matrix* mul_matrix = create_matrix(r->cols, l->rows);

    if (mul_matrix == NULL || mul_matrix->matrix == NULL) {
        free_matrix(mul_matrix);
        return NULL;
    }

    size_t rows = mul_matrix->rows;
    size_t cols = mul_matrix->cols;

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            for (size_t k = 0; k < r->rows; ++k) {
                double data = l->matrix[l->cols * i + k] * r->matrix[r->cols * k + j];
                mul_matrix->matrix[cols * i + j] += data;
            }
        }
    }

    return mul_matrix;
}

int det(const Matrix *matrix, double *val) {
    if (matrix == NULL || val == NULL || matrix->matrix == NULL) {
        return EXIT_FAILURE;
    }

    size_t rows = matrix->rows;
    size_t cols = matrix->cols;

    if (rows != cols) {
        return EXIT_FAILURE;
    }

    if (rows == 1) {
        *val = matrix->matrix[0];
    }

    if (rows == 2) {
        *val = matrix->matrix[0] * matrix->matrix[3] - matrix->matrix[1] * matrix->matrix[2];
    }

    if (rows > 2) {
        Matrix *gauss_matrix = gauss_method(matrix);

        if (gauss_matrix == NULL || gauss_matrix->matrix == NULL) {
            return EXIT_FAILURE;
        }

        *val = 1;

        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                if (i == j) {
                    *val *= gauss_matrix->matrix[cols * i + j];
                }
            }
        }

        free_matrix(gauss_matrix);
    }

    return EXIT_SUCCESS;
}

Matrix* gauss_method(const Matrix *matrix) {
    size_t rows = matrix->rows;
    size_t cols = matrix->cols;
    Matrix *gauss_matrix = create_matrix(rows, rows);

    for (size_t row = 0; row < rows; ++row) {
        for (size_t col = 0; col < rows; ++col) {
            gauss_matrix->matrix[cols * row + col] = matrix->matrix[cols * row + col];
        }
    }

    for (size_t col = 0; col < rows; ++col) {
        double elem = 0;
        get_elem(gauss_matrix, col, col, &elem);

        // Если elem главной диагонали = 0, то находим строку с ненулевым элементом
        if (elem == 0) {
            int changed_row = -1;

            for (size_t row = col; row < rows; row++) {
                get_elem(gauss_matrix, row, col, &elem);
                if (elem != 0) {
                    changed_row = row;
                    break;
                }
            }

            if (changed_row == -1) {
                free_matrix(gauss_matrix);
                return NULL;
            }

            // Меняеем порядок
            for (size_t row = 0; row < rows; row++) {
                get_elem(gauss_matrix, col, row, &elem);
                gauss_matrix->matrix[cols * col + row] = -gauss_matrix->matrix[cols * changed_row + row];
                gauss_matrix->matrix[cols * changed_row + row] = elem;
            }
        }

    //Приводим элменты под главной диагонали к 0
    for (size_t row = col; row < rows - 1; row++) {
        double coeff = -gauss_matrix->matrix[cols * (row + 1) + col]/gauss_matrix->matrix[cols * col + col];
            for (size_t k = 0; k < rows; k++) {
                gauss_matrix->matrix[cols * (row + 1) + k] += gauss_matrix->matrix[cols * col + k] * coeff;
            }
        }
    }

    return gauss_matrix;
}

Matrix* adj(const Matrix *matrix) {
    if (matrix == NULL || matrix->matrix == NULL) {
        return NULL;
    }

    size_t rows = matrix->rows;
    size_t cols = matrix->cols;

    if (rows != cols) {
        return NULL;
    }

    Matrix *adj_matrix = create_matrix(rows, cols);

    if (rows == 1) {
        set_elem(adj_matrix, 0, 0, 1);
        return adj_matrix;
    }

    if (adj_matrix == NULL || adj_matrix->matrix == NULL) {
        free_matrix(adj_matrix);
        return NULL;
    }

    size_t row = 0;
    for (size_t i = 0; i < rows; ++i) {
        size_t col = 0;
        for (size_t j = 0; j < cols; ++j) {
            Matrix *tmp_matrix = cross_out(matrix, row, col);

            if (tmp_matrix == NULL || tmp_matrix->matrix == NULL) {
                free_matrix(adj_matrix);
                free_matrix(tmp_matrix);
                return NULL;
            }

            double val = 0;
            // Находим определитель матрицы
            det(tmp_matrix, &val);
            val *= (i % 2 != 0 ? 1 : - 1);
            val *= (j % 2 != 0 ? 1 : - 1);
            // Добавляем значение присоединенной матрице
            set_elem(adj_matrix, i, j, val);
            free_matrix(tmp_matrix);
            col++;
        }
        row++;
    }

    // Транспонируем матрицу
    Matrix *transp_matrix = transp(adj_matrix);
    free_matrix(adj_matrix);

    if (transp_matrix == NULL || transp_matrix->matrix == NULL) {
        free_matrix(transp_matrix);
        return NULL;
    }

    return transp_matrix;
}
Matrix* cross_out(const Matrix *matrix, size_t row, size_t col) {
    size_t rows = matrix->rows;
    size_t cols = matrix->cols;
    size_t row_new_matrix = 0;
    Matrix *tmp_matrix = create_matrix(rows - 1, cols - 1);

    for (size_t i_row = 0; i_row < rows; ++i_row) {
        size_t col_new_matrix = 0;
        bool is_set_mat = false;

        for (size_t j_col = 0; j_col < cols; ++j_col) {
            // Условие для вычеркивания строки и столбца
            if (row != i_row && col != j_col) {
                is_set_mat = true;
                // Устанавливаем элемент матрицы
                set_elem(tmp_matrix,
                         row_new_matrix,
                         col_new_matrix,
                         matrix->matrix[cols * i_row + j_col]);
                // Переходим на следующий столбец
                col_new_matrix++;
            }
        }

        if (is_set_mat) {
            // Переходим на следующую строку
            row_new_matrix++;
        }
    }
    return tmp_matrix;
}

Matrix* inv(const Matrix *matrix) {
    if (matrix == NULL || matrix->matrix == NULL) {
        return NULL;
    }

    if (matrix->rows != matrix->cols) {
        return NULL;
    }

    double val = 0;
    det(matrix, &val);
    if (fabs(val - 0) < 0.0001) {
        return NULL;
    }

    Matrix *adj_matrix = adj(matrix);

    if (adj_matrix == NULL || adj_matrix->matrix == NULL) {
        free_matrix(adj_matrix);
        return NULL;
    }

    Matrix *return_matrix = mul_scalar(adj_matrix, (1 / val));
    free_matrix(adj_matrix);

    if (return_matrix == NULL || return_matrix->matrix == NULL) {
        free_matrix(return_matrix);
        return NULL;
    }

    return return_matrix;
}

Matrix* create_matrix_from_file(const char *path_file) {
    FILE *file_ptr = fopen(path_file, "r");

    if (file_ptr == NULL) {
        return NULL;
    }

    size_t rows = 0;
    size_t cols = 0;

    if (fscanf(file_ptr, "%zu %zu", &rows, &cols) != 2) {
        fclose(file_ptr);
        return NULL;
    }

    Matrix *matrix = create_matrix(rows, cols);

    if (matrix == NULL || matrix->matrix == NULL) {
        fclose(file_ptr);
        return NULL;
    }

    size_t c_r_mul = cols * rows;
    for (size_t i = 0; i < c_r_mul; ++i) {
        if (fscanf(file_ptr, "%le", &matrix->matrix[i]) != 1) {
            free_matrix(matrix);
            fclose(file_ptr);
            return NULL;
        }
    }

    fclose(file_ptr);
    return matrix;
}
