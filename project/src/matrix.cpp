#include "matrix.h"
#include "exceptions.h"
#include <math.h>
#include <iomanip>

namespace prep {
    Matrix::Matrix(size_t rows, size_t cols): rows(rows), cols(cols) {
        for(size_t i = 0; i < rows; ++i) {
            std::vector<double> mat_vector;

            for(size_t j = 0; j < cols; ++j) {
                mat_vector.push_back(0);
            }

            matrix.push_back(mat_vector);
        }
    }
    std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
        for (size_t i = 0; i < matrix.rows; ++i) {
            for (size_t j = 0; j < matrix.cols; ++j) {
                os << std::setprecision(std::numeric_limits<double>::max_digits10);
                os << matrix.matrix[i][j];
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
        if (cols <= i || rows <= j) {
            throw OutOfRange(i,j, this);
        }

        return matrix[i][j];
    }

    double& Matrix::operator()(size_t i, size_t j) {
        if (cols <= i || rows <= j) {
            throw OutOfRange(i,j, this);
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
                sub_mat.matrix[i][j] = matrix[i][j] + rhs.matrix[i][j];
            }
        }

        return sub_mat;
    }

    Matrix Matrix::operator*(const Matrix& rhs) const {
        if (cols != rhs.rows) {
            throw DimensionMismatch(*this, rhs);
        }

        Matrix mul_mat(rhs.rows, cols);
        size_t mul_row = mul_mat.rows;
        size_t mul_col = mul_mat.cols;

        for (size_t i = 0; i < mul_row; ++i) {
            for (size_t j = 0; j < mul_col; ++j) {
                for (size_t k = 0; k < rhs.rows; ++k) {
                    mul_mat.matrix[i][j] += matrix[i][k] * rhs.matrix[k][j];
                }
            }
        }
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
}
