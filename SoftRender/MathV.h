#pragma once
#include <cmath>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <limits>

template <typename T, size_t N, template <typename, size_t> class Derived>
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

    Derived<T, N> operator+(const VectorBase& other) const {
        Derived<T, N> result;
        for (size_t i = 0; i < N; ++i) {
            result[i] = data[i] + other[i];
        }
        return result;
    }

    Derived<T, N> operator+(const T& other) const {
        Derived<T, N> result;
        for (size_t i = 0; i < N; ++i) {
            result[i] = data[i] + other;
        }
        return result;
    }

    Derived<T, N> operator-(const VectorBase& other) const {
        Derived<T, N> result;
        for (size_t i = 0; i < N; ++i) {
            result[i] = data[i] - other[i];
        }
        return result;
    }

    Derived<T, N> operator-(const T& other) const {
        Derived<T, N> result;
        for (size_t i = 0; i < N; ++i) {
            result[i] = data[i] - other;
        }
        return result;
    }

    Derived<T, N> operator*(const VectorBase& other) const {
        Derived<T, N> result;
        for (size_t i = 0; i < N; ++i) {
            result[i] = data[i] * other[i];
        }
        return result;
    }

    Derived<T, N> operator*(const T& other) const {
        Derived<T, N> result;
        for (size_t i = 0; i < N; ++i) {
            result[i] = data[i] * other;
        }
        return result;
    }

    Derived<T, N> operator/(const T& other) const {
        if (std::abs(other) < std::numeric_limits<T>::epsilon()) {
            throw std::invalid_argument("Division by zero is not allowed");
        }
        Derived<T, N> result;
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

    size_t size() const {
        return data.size();
    }

    friend std::ostream& operator<<(std::ostream& os, const VectorBase& v) {
        for (size_t i = 0; i < N; ++i) {
            os << (i == 0 ? "[" : "") << v.data[i] << (i < N - 1 ? ", " : "]");
        }
        return os;
    }
};

// Vector 类，使用 CRTP 使 VectorBase 了解派生类 Vector 的类型
template <typename T, size_t N>
class Vector : public VectorBase<T, N, Vector> {
public:
    using VectorBase<T, N, Vector>::VectorBase;
};

// 针对二维、三维和四维向量进行特化
template <typename T>
class Vector<T, 2> : public VectorBase<T, 2, Vector> {
public:
    T& x;
    T& y;

    // 在构造函数中初始化引用
    Vector() : VectorBase<T, 2, Vector>(), x((*this)[0]), y((*this)[1]) {}

    // 拷贝构造函数
    Vector(const Vector& other) :
        VectorBase<T, 2, Vector>(other),
        x((*this)[0]),
        y((*this)[1]) {}

    // 从初始化列表构造
    Vector(std::initializer_list<T> list) :
        VectorBase<T, 2, Vector>(list),
        x((*this)[0]),
        y((*this)[1]) {}

    // 拷贝赋值运算符
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            this->data = other.data;
        }
        return *this;
    }
};

template <typename T>
class Vector<T, 3> : public VectorBase<T, 3, Vector> {

public:
    T& x;
    T& y;
    T& z;

    // 在构造函数中初始化引用
    Vector() : VectorBase<T, 3, Vector>(), x((*this)[0]), y((*this)[1]), z((*this)[2]) {}

    // 拷贝构造函数
    Vector(const Vector& other) :
        VectorBase<T, 3, Vector>(other),
        x((*this)[0]),
        y((*this)[1]),
        z((*this)[1]) {}

    // 从初始化列表构造
    Vector(std::initializer_list<T> list) :
        VectorBase<T, 3, Vector>(list),
        x((*this)[0]),
        y((*this)[1]),
        z((*this)[1]) {}
    // 拷贝赋值运算符
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            this->data = other.data;
        }
        return *this;
    }
};

template <typename T>
class Vector<T, 4> : public VectorBase<T, 4, Vector> {

public:
    T& x;
    T& y;
    T& z;

    // 在构造函数中初始化引用
    Vector() : VectorBase<T, 4, Vector>(), x((*this)[0]), y((*this)[1]), z((*this)[2]), w((*this)[2]) {}

    // 拷贝构造函数
    Vector(const Vector& other) :
        VectorBase<T, 4, Vector>(other),
        x((*this)[0]),
        y((*this)[1]),
        z((*this)[1]),
        w((*this)[1]) {}

    // 从初始化列表构造
    Vector(std::initializer_list<T> list) :
        VectorBase<T, 4, Vector>(list),
        x((*this)[0]),
        y((*this)[1]),
        z((*this)[1]),
        w((*this)[1]) {}
    // 拷贝赋值运算符
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            this->data = other.data;
        }
        return *this;
    }
};