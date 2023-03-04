//
// Created by Stepan on 04.03.2023.
//

#ifndef SLAU_LIB_CSR_SOLVER_H
#define SLAU_LIB_CSR_SOLVER_H
#include <vector>
#include "CSR_matrix.h"
#include "Vector.h"

template<typename T>
std::vector<T> FPI(csr_matrix<T> &A, std::vector<T> &b, std::vector<T> &x, T t, T tau) {
    std::vector x_1 = x;
    std::vector<T> ret = A * x - b;
    while (N(ret) > t) {
        x = x_1;
        for (int i = 0; i < x.size(); i++) {
            T sum = b[i] * tau + x[i];
            for (int j = 0; j < x.size(); j++) sum -= x[j] * A(i, j) * tau;
            x_1[i] = sum;
        }
        ret = A * x - b;

    }
    return x_1;
}


template<typename T>
int FPI_for_count(csr_matrix<T> &A, std::vector<T> &b, std::vector<T> x, T t, T tau) {
    std::vector x_1 = x;
    std::vector<T> ret = A * x - b;
    int counter = 0;
    while (N(ret) > t) {
        x = x_1;
        for (int i = 0; i < x.size(); i++) {
            T sum = b[i] * tau + x[i];
            for (int j = 0; j < x.size(); j++) sum -= x[j] * A(i, j) * tau;
            x_1[i] = sum;
        }
        ret = A * x - b;
        counter += 1;

    }
    return counter;
}


template<typename T>
std::vector<T> Jacobi(csr_matrix<T> &A, std::vector<T> &b, std::vector<T> &x, T t) {
    std::vector x_1 = x;
    std::vector<T> ret = A * x - b;
    while (N(ret) > t) {
        x = x_1;
        for (int i = 0; i < x.size(); i++) {
            T sum = b[i];
            for (int j = 0; j < x.size(); j++) if (j != i) sum -= x[j] * A(i, j);
            x_1[i] = sum / A(i, i);
        }
        ret = A * x - b;

    }
    return x;
}








template<typename T>
std::vector<T> Gaus_Zeidel(csr_matrix<T> &A, std::vector<T> &b, std::vector<T> &x, T t) {
    std::vector<T> ret = A * x - b;
    while (N(ret) > t) {
        for (int i = 0; i < x.size(); i++) {
            T sum = b[i];
            for (int j = 0; j < x.size(); j++) if (j != i) sum -= x[j] * A(i, j);
            x[i] = sum / A(i, i);
        }
        ret = A * x - b;
    }
    return x;
}




#endif //SLAU_LIB_CSR_SOLVER_H
