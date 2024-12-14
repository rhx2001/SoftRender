#pragma once
#include <cmath>
#include <stdexcept>
template<typename T, size_t R, size_t N>
class Matrix {
private:
	std::vector<std::vector<T>> data;
    size_t rows_;
    size_t cols_;
public:
	Matrix():data(R, std::vector<T>(N, T())), rows_(0), cols_(0) {}
    Matrix(size_t rows, size_t cols): data(rows, std::vector<T>(cols, T())), rows_(rows), cols_(cols) {}
    Matrix(size_t rows, size_t cols, T num) : data(rows, std::vector<T>(cols, T())), rows_(rows), cols_(cols) {
        for (int i = 0; i < R; i++) {
            data[i][i] = num;
        }
    }
    Matrix(std::initializer_list<std::initializer_list<T>> list) {
        rows_ = list.size();
        if (rows_ != R) {
            throw std::invalid_argument("Invalid number of rows");
        }

        data.reserve(rows_);
        cols_ = list.begin()->size();
        for (const auto& row : list) {
            if (row.size() != N) {
                throw std::invalid_argument("Invalid number of columns");
            }
            data.emplace_back(row);
        }
    }


    T& operator()(size_t row, size_t col) {
        return data[row][col];
    }

    const T& operator()(size_t row, size_t col) const {
        return data[row][col];
    }

    Matrix<T, N, R> TT() const {
        Matrix<T, N, R> result(N, R);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < R; j++) {
                result(i, j) = (*this)(j, i);
            }
        }
        return result;
    }

    Matrix operator+(const Matrix& other) const {
        if (R != other.rows() || N != other.cols()) {
            throw std::invalid_argument("Matrix dimensions must match for addition");
        }

        Matrix result;
        for (size_t i = 0; i < R; ++i) {
            for (size_t j = 0; j < N; ++j) {
                result(i, j) = (*this)(i, j) + other(i, j);
            }
        }
        return result;
    }

    Matrix operator+(const T& other) const {

        Matrix result;
        for (size_t i = 0; i < R; ++i) {
            for (size_t j = 0; j < N; ++j) {
                result(i, j) = (*this)(i, j) + other;
            }
        }
        return result;
    }

    Matrix operator-(const T& other) const {

        Matrix result;
        for (size_t i = 0; i < R; ++i) {
            for (size_t j = 0; j < N; ++j) {
                result(i, j) = (*this)(i, j) - other;
            }
        }
        return result;
    }

    Matrix operator-(const Matrix& other) const {
        if (R != other.rows() || N != other.cols()) {
            throw std::invalid_argument("Matrix dimensions must match for addition");
        }

        Matrix result;
        for (size_t i = 0; i < R; ++i) {
            for (size_t j = 0; j < N; ++j) {
                result(i, j) = (*this)(i, j) - other(i, j);
            }
        }
        return result;
    }

    Matrix operator*(const Matrix& other) const {
        if (R != other.rows() || N != other.cols()) {
            throw std::invalid_argument("Matrix dimensions must match for addition");
        }
        Matrix result;
        for (size_t i = 0; i < R; ++i) {
            for (size_t j = 0; j < N; ++j) {
                result(i, j) = (*this)(i, j) * other(i, j);
            }
        }
        return result;
    }


    Matrix operator*(const T& other) const {
        Matrix result;
        for (size_t i = 0; i < R; ++i) {
            for (size_t j = 0; j < N; ++j) {
                result(i, j) = (*this)(i, j) * other;
            }
        }
        return result;
    }

    Matrix operator/(const T& other) const {
        if (std::abs(other) < std::numeric_limits<T>::epsilon()) {
            throw std::invalid_argument("Division by zero is not allowed");
        }

        Matrix result;
        for (size_t i = 0; i < R; ++i) {
            for (size_t j = 0; j < N; ++j) {
                result(i, j) = (*this)(i, j) / other;
            }
        }
        return result;
    }

    template<typename T, size_t C, size_t Q>
    Matrix<T,R,Q> dot(const Matrix<T, C, Q>& other) {
        const size_t otherRow = other.rows_;
        const size_t otherCol = other.cols_;
        if (N != otherRow) {
            throw std::invalid_argument("Matrix dimensions must match for multiplication");
        }
        Matrix<T, R, Q> result ;
        for (size_t  i = 0; i < rows_; i++) {
            for (size_t  j = 0; j < otherRow; j++) {
                T sum=T();
                for (size_t k = 0; k < N; k++) {
                    sum += (*this)(i, k) * other(k, j);
                }
                result(i, j) = sum;
            }
        }
        return result;
    }

    Matrix dot(const Matrix& other) const {
        const size_t otherRow = other.rows_;
        const size_t otherCol = other.cols_;
        if (N != otherRow) {
            throw std::invalid_argument("Matrix dimensions must match for multiplication");
        }
        Matrix result(rows_, otherCol);
        for (size_t i = 0; i < rows_; i++) {
            for (size_t j = 0; j < otherRow; j++) {
                T sum = T();
                for (size_t k = 0; k < N; k++) {
                    sum += (*this)(i, k) * other(k, j);
                }
                result(i, j) = sum;
            }
        }
        return result;
    }

    Matrix det() const {
        Matrix result;
    }

    void lu_decomposition(Matrix<T, R, R>& L, Matrix<T, R, R>& U) const {
        if (R != N) {
            throw std::invalid_argument("Matrix must be square for LU decomposition");
        }

        // 初始化L和U矩阵
        L = Matrix<T, R, R>(R, R, 0);  // L初始化为0矩阵
        U = Matrix<T, R, R>(*this);    // U初始化为当前矩阵的副本

        // L的对角线元素设为1
        for (size_t i = 0; i < R; i++) {
            L(i, i) = 1;
        }

        // 执行LU分解
        for (size_t k = 0; k < R - 1; k++) {
            for (size_t i = k + 1; i < R; i++) {
                if (std::abs(U(k, k)) < std::numeric_limits<T>::epsilon()) {
                    throw std::runtime_error("Matrix is singular or nearly singular");
                }

                T factor = U(i, k) / U(k, k);
                L(i, k) = factor;

                for (size_t j = k; j < R; j++) {
                    U(i, j) -= factor * U(k, j);
                }
            }
        }
    }

    // 前向替换求解Ly = b
    Vector<T, R> forward_substitution(const Matrix<T, R, R>& L, const Vector<T, R>& b) const {
        Vector<T, R> y;
        for (size_t i = 0; i < R; i++) {
            T sum = 0;
            for (size_t j = 0; j < i; j++) {
                sum += L(i, j) * y[j];
            }
            y[i] = (b[i] - sum) / L(i, i);
        }
        return y;
    }

    // 后向替换求解Ux = y
    Vector<T, R> backward_substitution(const Matrix<T, R, R>& U, const Vector<T, R>& y) const {
        Vector<T, R> x;
        for (int i = R - 1; i >= 0; i--) {
            T sum = 0;
            for (size_t j = i + 1; j < R; j++) {
                sum += U(i, j) * x[j];
            }
            if (std::abs(U(i, i)) < std::numeric_limits<T>::epsilon()) {
                throw std::runtime_error("Matrix is singular");
            }
            x[i] = (y[i] - sum) / U(i, i);
        }
        return x;
    }

    // 矩阵求逆方法
    Matrix<T, R, R> inverse() const {
        if (R != N) {
            throw std::invalid_argument("Matrix must be square for inverse");
        }

        // 创建L和U矩阵
        Matrix<T, R, R> L, U;
        lu_decomposition(L, U);

        // 创建单位矩阵I
        Matrix<T, R, R> I(R, R, 0);
        for (size_t i = 0; i < R; i++) {
            I(i, i) = 1;
        }

        // 求解逆矩阵
        Matrix<T, R, R> inverse_matrix(R, R);
        for (size_t i = 0; i < R; i++) {
            // 构造单位矩阵的第i列
            Vector<T, R> b;
            for (size_t j = 0; j < R; j++) {
                b[j] = I(j, i);
            }

            // 解方程LUx = b
            Vector<T, R> y = forward_substitution(L, b);
            Vector<T, R> x = backward_substitution(U, y);

            // 将结果放入逆矩阵的第i列
            for (size_t j = 0; j < R; j++) {
                inverse_matrix(j, i) = x[j];
            }
        }

        return inverse_matrix;
    }

    Vector<T, R> dot(const Vector<T,R>& other) const {
        const size_t otherRow = other.size();
        Vector<T, R> result;
        for (size_t i = 0; i < rows_; i++) {
            T sum = T();
            for (size_t j = 0; j < otherRow; j++) {
                sum += (*this)(i, j) * other[j];
                
            }
            result[i] = sum;
        }
        return result;
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix& mat) {
        for (size_t i = 0; i < R; ++i) {
            for (size_t j = 0; j < N; ++j) {
                os << mat(i, j) << " ";
            }
            os << std::endl;
        }
        return os;
    }


    size_t rows() const {
        return rows_;
    }

    size_t cols() const {
        return cols_;
    }



};
