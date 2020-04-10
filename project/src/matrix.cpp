#include <math.h>
#include <iomanip>
#include "matrix.h"
#include "exceptions.h"

namespace prep {
    Matrix::Matrix(size_t rows, size_t cols): rows(rows), cols(cols), matrix(rows, std::vector<double> (cols, 0)) {
    }


    Matrix::Matrix(std::istream& is) {
        rows = 0;
        cols = 0;

        is >> rows >> cols;

        if (!is) {
            throw InvalidMatrixStream();
        }

        std::vector<double> matVector(cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                double value = 0;
                is >> value;

                if (!is) {
                    throw InvalidMatrixStream();
                }

                matVector[j] = value;
            }

            matrix.push_back(matVector);
        }
    }

    std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
        os << matrix.rows << " " << matrix.cols << std::endl;
        for (size_t i = 0; i < matrix.rows; ++i) {
            for (size_t j = 0; j < matrix.cols; ++j) {
                os << std::setprecision(std::numeric_limits<double>::max_digits10) << matrix.matrix[i][j] << " ";
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

        Matrix sumMat(rows, cols);

        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                sumMat.matrix[i][j] = matrix[i][j] + rhs.matrix[i][j];
            }
        }

        return sumMat;
    }

    Matrix Matrix::operator-(const Matrix& rhs) const {
        if (rhs.cols != cols || rhs.rows != rows) {
            throw DimensionMismatch(*this, rhs);
        }

        Matrix subMat(rows, cols);

        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                subMat.matrix[i][j] = matrix[i][j] - rhs.matrix[i][j];
            }
        }

        return subMat;
    }

    Matrix Matrix::operator*(const Matrix& rhs) const {
        if (cols != rhs.rows) {
            throw DimensionMismatch(*this, rhs);
        }

        Matrix mulMatrix(rows, rhs.cols);
        size_t mulRow = mulMatrix.rows;
        size_t mulCol = mulMatrix.cols;
        for (size_t i = 0; i < mulRow; ++i) {
            for (size_t j = 0; j < mulCol; ++j) {
                for (size_t k = 0; k < rhs.rows; ++k) {
                    mulMatrix.matrix[i][j] += matrix[i][k] * rhs.matrix[k][j];
                }
            }
        }

        return  mulMatrix;
    }


    Matrix Matrix::transp() const {
        Matrix transpMat(cols, rows);

        for (size_t i = 0; i < cols; ++i) {
            for (size_t j = 0; j < rows; ++j) {
                transpMat.matrix[i][j] = matrix[j][i];
            }
        }

        return transpMat;
    }

    Matrix Matrix::operator*(double val) const {
        Matrix mulMatrix(rows, cols);

        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                mulMatrix.matrix[i][j] = matrix[i][j] * val;
            }
        }

        return mulMatrix;
    }

    Matrix operator*(double val, const Matrix& matrix) {
        Matrix mulMatrix(matrix.rows, matrix.cols);
        size_t mulRow = mulMatrix.rows;
        size_t mulCol = mulMatrix.cols;

        for (size_t i = 0; i < mulRow; ++i) {
            for (size_t j = 0; j < mulCol; ++j) {
                mulMatrix.matrix[i][j] = matrix.matrix[i][j] * val;
            }
        }
        return mulMatrix;
    }

    bool Matrix::operator==(const Matrix& rhs) const {
        if (rhs.rows != rows || rhs.cols != cols) {
            return false;
        }

        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                double val1 = abs(matrix[i][j] - rhs.matrix[i][j]);
                double  val2 = std::numeric_limits<double>::epsilon() * pow(10, 9);
                if (val1 > val2) {
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
                double val1 = abs(matrix[i][j] - rhs.matrix[i][j]);
                double  val2 = std::numeric_limits<double>::epsilon() * pow(10, 9);
                if (val1 > val2) {
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
            Matrix gaussMatrix = gaussMethod();

            for (size_t i = 0; i < rows; i++) {
                val *= gaussMatrix.matrix[i][i];
            }
        }
        return val;
    }

    Matrix Matrix::gaussMethod() const {
        Matrix gaussMatrix = *this;

        for (size_t col = 0; col < rows; ++col) {
            double elem = gaussMatrix(col, col);

            // Если elem главной диагонали = 0, то находим строку с ненулевым элементом
            if (elem == 0) {
                int changedRow = -1;

                for (size_t row = col; row < rows; row++) {
                    elem = gaussMatrix(row, col);

                    if (elem != 0) {
                        changedRow = row;
                        break;
                    }
                }

                if (changedRow == -1) {
                    break;
                }

                // Меняеем порядок
                for (size_t row = 0; row < rows; row++) {
                    elem = gaussMatrix(col, row);
                    gaussMatrix.matrix[col][row] = -gaussMatrix.matrix[changedRow][row];
                    gaussMatrix.matrix[changedRow][row] = elem;
                }
            }

            //Приводим элменты под главной диагонали к 0
            for (size_t row = col; row < rows - 1; row++) {
                double coeff = -gaussMatrix.matrix[row + 1][col] / gaussMatrix.matrix[col][col];
                for (size_t k = 0; k < rows; k++) {
                    gaussMatrix.matrix[row + 1][k] += gaussMatrix.matrix[col][k] * coeff;
                }
            }
        }

        return gaussMatrix;
    }

    Matrix Matrix::adj() const {
        if (rows != cols) {
            throw DimensionMismatch(*this);
        }

        Matrix adjMatrix(rows, cols);

        if (rows == 1) {
            adjMatrix(0, 0) = 1;
            return adjMatrix;
        }

        size_t row = 0;
        for (size_t i = 0; i < rows; ++i) {
            size_t col = 0;

            for (size_t j = 0; j < cols; ++j) {
                Matrix tmp_matrix = crossOut(row, col);
                // Находим определитель матрицы
                double val = tmp_matrix.det();
                val *= (i % 2 != 0 ? 1 : - 1);
                val *= (j % 2 != 0 ? 1 : - 1);
                // Добавляем значение присоединенной матрице
                adjMatrix(i, j) = val;
                col++;
            }
            row++;
        }

        return adjMatrix.transp();
    }

    Matrix Matrix::crossOut(size_t row, size_t col) const {
        size_t rowNewMatrix = 0;
        Matrix tmpMatrix(rows - 1, cols - 1);

        for (size_t iRow = 0; iRow < rows; ++iRow) {
            size_t colNewMatrix = 0;
            bool isSetMat = false;

            for (size_t jCol = 0; jCol < cols; ++jCol) {
                // Условие для вычеркивания строки и столбца
                if (row != iRow && col != jCol) {
                    isSetMat = true;
                    // Устанавливаем элемент матрицы
                    tmpMatrix(rowNewMatrix, colNewMatrix) = matrix[iRow][jCol];
                    // Переходим на следующий столбец
                    colNewMatrix++;
                }
            }

            if (isSetMat) {
                // Переходим на следующую строку
                rowNewMatrix++;
            }
        }

        return tmpMatrix;
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
