#pragma once
#include"MathV.hpp"
#include"MathM.hpp"
constexpr auto MY_PI = 3.1415926f;

typedef Matrix<float, 3, 3> Matrix3f;
typedef Matrix<float, 4, 4> Matrix4f;
typedef Matrix<int, 3, 3> Matrix3i;
typedef Matrix<int, 4, 4> Matrix4i;
typedef Vector<float, 4> Vector4f;
typedef Vector<float, 3> Vector3f;
typedef Vector<int, 3> Vector3i;
typedef Vector<int, 4> Vector4i;




template<typename T, size_t R, size_t N>
Matrix<T, R, N> operator+(const T a, const Matrix<T, R, N> b) {
    Matrix<T, R, N> result;
    for (size_t i = 0; i < R; ++i) {
        for (size_t j = 0; j < N; ++j) {
            result(i, j) = b(i, j) + a;
        }
    }
    return result;
}

template<typename T, size_t R, size_t N>
Matrix<T, R, N> operator-(const T a, const Matrix<T, R, N> b) {
    Matrix<T, R, N> result;
    for (size_t i = 0; i < R; ++i) {
        for (size_t j = 0; j < N; ++j) {
            result(i, j) = b(i, j) - a;
        }
    }
    return result;
}

template<typename T, size_t R, size_t N> 
Matrix<T, R, N> operator*(const T a, const Matrix<T, R, N> b) {
    Matrix<T, R, N> result;
    for (size_t i = 0; i < R; ++i) {
        for (size_t j = 0; j < N; ++j) {
            result(i, j) = b(i, j) * a;
        }
    }
    return result;
}

template<typename T, size_t N>
VectorBase<T, N> operator-(const T& other, const VectorBase<T, N>& b) {
    VectorBase<T, N> result;
    for (size_t i = 0; i < N; ++i) {
        result[i] = b[i] - other;
    }
    return result;
}

template<typename T, size_t N>
VectorBase<T, N> operator+(const T& other, const VectorBase<T, N>& b) {
    VectorBase<T, N> result;
    for (size_t i = 0; i < N; ++i) {
        result[i] = b[i] + other;
    }
    return result;
}

template<typename T, size_t N>
VectorBase<T, N> operator*(const T& other, const VectorBase<T, N>& b) {
    VectorBase<T, N> result;
    for (size_t i = 0; i < N; ++i) {
        result[i] = b[i] * other;
    }
    return result;
}
