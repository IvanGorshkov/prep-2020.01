#include <math.h>
#include <iomanip>
#include "matrix.h"
#include "exceptions.h"

namespace prep {
    Matrix::Matrix(size_t rows, size_t cols): rows(rows), cols(cols) {
        for (size_t i = 0; i < rows; ++i) {
            std::vector<double> mat_vector;

            for (size_t j = 0; j < cols; ++j) {
                mat_vector.push_back(0);
            }

            matrix.push_back(mat_vector);
        }
    }

    Matrix::Matrix(std::istream& is) {
        rows = 0;
        cols = 0;

        is >> rows >> cols;

        if (!is) {
            throw InvalidMatrixStream();
        }

        for (size_t i = 0; i < rows; ++i) {
            std::vector<double> mat_vector;

            for (size_t j = 0; j < cols; ++j) {
                double value = 0;
                is >> value;

                if (!is) {
                    throw InvalidMatrixStream();
                }

                mat_vector.push_back(value);
            }

            matrix.push_back(mat_vector);
        }
    }

    std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
        os << matrix.rows << " " << matrix.cols << std::endl;
        for (size_t i = 0; i < matrix.rows; ++i) {
            for (size_t j = 0; j < matrix.cols; ++j) {
                os << matrix.matrix[i][j];
                os << std::setprecision(7);
                os << " ";
            }
            os << std::endl;
        }
        return os;
    }

    size_t Matrix::getRows() const {
        return rows;
    }

    size_t Matrix::getCols() const {
        return cols;
    }

    double Matrix::operator()(size_t i, size_t j) const {
        if (cols <= j || rows <= i) {
            throw OutOfRange(i, j, this);
        }

        return matrix[i][j];
    }

    double& Matrix::operator()(size_t i, size_t j) {
        if (cols <= j || rows <= i) {
            throw OutOfRange(i, j, this);
        }

        return matrix[i][j];
    }

    Matrix Matrix::operator+(const Matrix& rhs) const {
        if (rhs.cols != cols || rhs.rows != rows) {
            throw DimensionMismatch(*this, rhs);
        }

        Matrix sum_mat(rows, cols);

        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                sum_mat.matrix[i][j] = matrix[i][j] + rhs.matrix[i][j];
            }
        }

        return sum_mat;
    }

    Matrix Matrix::operator-(const Matrix& rhs) const {
        if (rhs.cols != cols || rhs.rows != rows) {
            throw DimensionMismatch(*this, rhs);
        }

        Matrix sub_mat(rows, cols);

        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                sub_mat.matrix[i][j] = matrix[i][j] - rhs.matrix[i][j];
            }
        }

        return sub_mat;
    }

    Matrix Matrix::operator*(const Matrix& rhs) const {
        if (cols != rhs.rows) {
            throw DimensionMismatch(*this, rhs);
        }

        Matrix mul_matrix(rows, rhs.cols);
        size_t mul_row = mul_matrix.rows;
        size_t mul_col = mul_matrix.cols;
        for (size_t i = 0; i < mul_row; ++i) {
            for (size_t j = 0; j < mul_col; ++j) {
                for (size_t k = 0; k < rhs.rows; ++k) {
                    mul_matrix.matrix[i][j] += matrix[i][k] * rhs.matrix[k][j];
                }
            }
        }

        return  mul_matrix;
    }


    Matrix Matrix::transp() const {
        Matrix transp_mat(cols, rows);

        for (size_t i = 0; i < cols; ++i) {
            for (size_t j = 0; j < rows; ++j) {
                transp_mat.matrix[i][j] = matrix[j][i];
            }
        }

        return transp_mat;
    }

    Matrix Matrix::operator*(double val) const {
        Matrix mul_matrix(rows, cols);

        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                mul_matrix.matrix[i][j] = matrix[i][j] * val;
            }
        }

        return mul_matrix;
    }

    Matrix operator*(double val, const Matrix& matrix) {
        Matrix mul_matrix(matrix.rows, matrix.cols);
        size_t mul_row = mul_matrix.rows;
        size_t mul_col = mul_matrix.cols;

        for (size_t i = 0; i < mul_row; ++i) {
            for (size_t j = 0; j < mul_col; ++j) {
                mul_matrix.matrix[i][j] = matrix.matrix[i][j] * val;
            }
        }
        return mul_matrix;
    }

    bool Matrix::operator==(const Matrix& rhs) const {
        if (rhs.rows != rows || rhs.cols != cols) {
            return false;
        }

        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                if (abs(matrix[i][j] - rhs.matrix[i][j]) > std::numeric_limits<double>::epsilon() * pow(10, -7)) {
                    return false;
                }
            }
        }

        return true;
    }

    bool Matrix::operator!=(const Matrix& rhs) const {
        if (rhs.rows != rows || rhs.cols != cols) {
            return true;
        }

        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                if (abs(matrix[i][j] - rhs.matrix[i][j]) > std::numeric_limits<double>::epsilon() * pow(10, -7)) {
                    return true;
                }
            }
        }

        return false;
    }
    double Matrix::det() const {
        if (rows != cols) {
            throw DimensionMismatch(*this);
        }

        if (rows == 1) {
            return matrix[0][0];
        }

        if (rows == 2) {
            return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
        }
        double val = 1;
        if (rows > 2) {
            Matrix gauss_matrix = gauss_method();

            for (size_t i = 0; i < rows; i++) {
                val *= gauss_matrix.matrix[i][i];
            }
        }
        return val;
    }

    Matrix Matrix::gauss_method() const {
        Matrix gauss_matrix = *this;

        for (size_t col = 0; col < rows; ++col) {
            double elem = gauss_matrix(col, col);

            // Если elem главной диагонали = 0, то находим строку с ненулевым элементом
            if (elem == 0) {
                int changed_row = -1;

                for (size_t row = col; row < rows; row++) {
                    elem = gauss_matrix(row, col);

                    if (elem != 0) {
                        changed_row = row;
                        break;
                    }
                }

                if (changed_row == -1) {
                    break;
                }

                // Меняеем порядок
                for (size_t row = 0; row < rows; row++) {
                    elem = gauss_matrix(col, row);
                    gauss_matrix.matrix[col][row] = -gauss_matrix.matrix[changed_row][row];
                    gauss_matrix.matrix[changed_row][row] = elem;
                }
            }

            //Приводим элменты под главной диагонали к 0
            for (size_t row = col; row < rows - 1; row++) {
                double coeff = -gauss_matrix.matrix[row + 1][col] / gauss_matrix.matrix[col][col];
                for (size_t k = 0; k < rows; k++) {
                    gauss_matrix.matrix[row + 1][k] += gauss_matrix.matrix[col][k] * coeff;
                }
            }
        }

        return gauss_matrix;
    }

    Matrix Matrix::adj() const {
        if (rows != cols) {
            throw DimensionMismatch(*this);
        }

        Matrix adj_matrix(rows, cols);

        if (rows == 1) {
            adj_matrix(0, 0) = 1;
            return adj_matrix;
        }

        size_t row = 0;
        for (size_t i = 0; i < rows; ++i) {
            size_t col = 0;

            for (size_t j = 0; j < cols; ++j) {
                Matrix tmp_matrix = cross_out(row, col);
                // Находим определитель матрицы
                double val = tmp_matrix.det();
                val *= (i % 2 != 0 ? 1 : - 1);
                val *= (j % 2 != 0 ? 1 : - 1);
                // Добавляем значение присоединенной матрице
                adj_matrix(i, j) = val;
                col++;
            }
            row++;
        }

        return adj_matrix.transp();
    }

    Matrix Matrix::cross_out(size_t row, size_t col) const {
        size_t row_new_matrix = 0;
        Matrix tmp_matrix(rows - 1, cols - 1);

        for (size_t i_row = 0; i_row < rows; ++i_row) {
            size_t col_new_matrix = 0;
            bool is_set_mat = false;

            for (size_t j_col = 0; j_col < cols; ++j_col) {
                // Условие для вычеркивания строки и столбца
                if (row != i_row && col != j_col) {
                    is_set_mat = true;
                    // Устанавливаем элемент матрицы
                    tmp_matrix(row_new_matrix, col_new_matrix) = matrix[i_row][j_col];
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

    Matrix Matrix::inv() const {
        if (rows != cols) {
            throw DimensionMismatch(*this);
        }

        double val = det();
        if (abs(val) < 0.0001) {
            throw SingularMatrix();
        }

        return  adj() * (1 / val);
    }
}  // namespace prep
