#pragma once
#include <cmath>
#include <vector>
#include <iostream>
#include <stdexcept>

template <typename T, size_t N, size_t R>
class Matrix;//向前声明，让两个函数不相互引用

template <typename T, size_t N>
class VectorBase {
protected:
    std::vector<T> data;
public:
    VectorBase() : data(N, T()) {}
    VectorBase(std::initializer_list<T> list) : data(list) {}

    T& operator[](size_t index) {
        return data[index];
    }

    const T& operator[](size_t index) const {
        return data[index];
    }

    VectorBase operator+(const VectorBase& other) const {
        VectorBase result;
        for (size_t i = 0; i < N; ++i) {
            result[i] = data[i] + other[i];
        }
        return result;
    }

    VectorBase operator+(const T& other) const {
        VectorBase result;
        for (size_t i = 0; i < N; ++i) {
            result[i] = data[i] + other;
        }
        return result;
    }

    VectorBase operator-(const VectorBase& other) const {
        VectorBase result;
        for (size_t i = 0; i < N; ++i) {
            result[i] = data[i] - other[i];
        }
        return result;
    }

    VectorBase operator-(const T& other) const {
        VectorBase result;
        for (size_t i = 0; i < N; ++i) {
            result[i] = data[i] - other;
        }
        return result;
    }

    VectorBase operator*(const VectorBase& other) const {
        VectorBase result;
        for (size_t i = 0; i < N; ++i) {
            result[i] = data[i] * other[i];
        }
        return result;
    }

    VectorBase operator*(const T& other) const {
        VectorBase result;
        for (size_t i = 0; i < N; ++i) {
            result[i] = data[i] * other;
        }
        return result;
    }

    VectorBase operator/(const T& other) const {
        if (std::abs(other) < std::numeric_limits<T>::epsilon()) {
            throw std::invalid_argument("Division by zero is not allowed");
        }
        VectorBase result;
        for (size_t i = 0; i < N; ++i) {
            result[i] = data[i] / other;
        }
        return result;
    }

    T dot(const VectorBase& other) const {
        T sum = T();
        for (size_t i = 0; i < N; ++i) {
            sum += data[i] * other[i];
        }
        return sum;
    }

        template <size_t C>
        VectorBase<T, C> dot(const Matrix<T, N, C>& other) const { //让Matrix的C传入VectorBase中
            VectorBase<T, C> result;
            for (size_t i = 0; i < C; ++i) {
                T sum = T();
                for (size_t j = 0; j < N; ++j) {
                    sum += data[j] * other(j, i);
                }
                result[i] = sum;
            }
            return result;
        }



    size_t size() const {
        return size_t(data.size());
    }

    friend std::ostream& operator<<(std::ostream& os, const VectorBase& v) {
        for (size_t i = 0; i < N; ++i) {
            os << (i == 0 ? "[" : "") << v.data[i] << (i < N - 1 ? ", " : "]");
        }
        return os;
    }
};

template <typename T, size_t N>
class Vector : public VectorBase<T, N> {
public:
    using VectorBase<T, N>::VectorBase;
};

template <typename T>
class Vector<T, 2> : public VectorBase<T, 2> {
public:
    using VectorBase<T, 2>::VectorBase;
};

template <typename T>
class Vector<T, 3> : public VectorBase<T, 3> {
public:
    using VectorBase<T, 3>::VectorBase;
};

template <typename T>
class Vector<T, 4> : public VectorBase<T, 4> {
public:
    using VectorBase<T, 4>::VectorBase;
};
