#include <cmath>
#include <stdexcept>
template<typename T, size_t R, size_t N>
class Matrix {
private:
	std::vector<std::vector<T>> data;
public:
	Matrix():data(R, std::vector<T>(N, T())) {}
    Matrix(std::initializer_list<std::initializer_list<T>> list) {
        if (list.size() != R) {
            throw std::invalid_argument("Invalid number of rows");
        }
        data.reserve(R);
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
        size_t otherRow = other.rows();
        size_t otherCol = other.cols();
        if (N != otherRow) {
            throw std::invalid_argument("Matrix dimensions must match for multiplication");
        }
        Matrix<T, R, otherCol> result;
        for (size_t  i = 0; i < R; i++) {
            for (size_t  j = 0; j < otherRow; j++) {
                T sum=T();
                for (size_t k = 0; k < N; k++) {
                    sum += (*this)(i, k) + other(k, j);
                }
                result(i, j) = sum;
            }
        }
        return result;
    }

    size_t rows() const {
        return R;
    }

    size_t cols() const {
        return N;
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

};
