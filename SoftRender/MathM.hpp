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

    Matrix dot(const Matrix& other) {
        const size_t otherRow = other.rows_;
        const size_t otherCol = other.cols_;
        if (N != otherRow) {
            throw std::invalid_argument("Matrix dimensions must match for multiplication");
        }
        Matrix result(rows_, otherCol) ;
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

    VectorBase<T, R> dot(const VectorBase<T,R>& other) const {
        const size_t otherRow = other.size();
        VectorBase<T, R> result;
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
