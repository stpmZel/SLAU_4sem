//
// Created by Stepan on 04.03.2023.
//

#ifndef SLAU_LIB_VECTOR_H
#define SLAU_LIB_VECTOR_H

#include <iostream>
#include <vector>
#include <cmath>

template<typename T>
T scal(const std::vector<T> &lhs, const std::vector<T> &rhs)
{
    T sum = 0;
    for(int i = 0; i < lhs.size(); i ++) sum += lhs[i] * rhs[i];
    return sum;
}


template<typename T>
std::vector<T> operator+(const std::vector<T> &lhs, const std::vector<T> &rhs) {
    std::vector<T> res_;
    res_.reserve(lhs.size());
    for (int i = 0; i < lhs.size(); i++) res_.push_back(lhs[i] + rhs[i]);
    return res_;
}

template<typename T>
std::vector<T> operator*(const std::vector<T> &lhs, const double &rhs) {
    std::vector<T> res_;
    res_.reserve(lhs.size());
    for (int i = 0; i < lhs.size(); i++) res_.push_back(lhs[i] * rhs);
    return res_;
}

template<typename T>
std::vector<T> operator-(const std::vector<T> &lhs, const std::vector<T> &rhs) {
    std::vector<T> res_;
    res_.reserve(lhs.size());
    for (int i = 0; i < lhs.size(); i++) res_.push_back(lhs[i] - rhs[i]);
    return res_;
}

template<typename T>
T N(const std::vector<T> &item) {
    T res_ = 0;
    for (int i = 0; i < item.size(); i++) res_ += item[i] * item[i];
    return res_;
}

template<typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> &matrix) {

    for (int j = 0; j < matrix.size(); j++) out << matrix[j] << " ";
    return out;
}

#endif //SLAU_LIB_VECTOR_H
