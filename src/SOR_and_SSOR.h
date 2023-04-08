//
// Created by Stepan on 07.04.2023.
//

#ifndef SLAU_LIB_SOR_AND_SSOR_H
#define SLAU_LIB_SOR_AND_SSOR_H

#include "CSR_matrix.h"

template<typename T>
std::vector<T> SOR(const csr_matrix<T> &A, const std::vector<T> &b, const std::vector<T> &x0, T tolerance, T w) {
    std::vector<T> x = x0;
    while (!stop_check(A, x, b, tolerance)) {
        for (int i = 0; i < x.size(); i++) {
            T sum = b[i];
            for (int j = 0; j < A.get_row(i + 1) - A.get_row(i); j++)
                if (i != A.get_col(A.get_row(i)+j))
                    sum -= A.get_value(A.get_row(i) + j) * x[A.get_col(A.get_row(i) + j)];
            x[i] = (1 - w) * x[i] + w * sum / A(i, i);
        }
    }
    return x;
}

template<typename T>
std::vector<T> SSOR(const csr_matrix<T> &A, const std::vector<T> &b, const std::vector<T> &x0, T tolerance, T w) {
    std::vector<T> x = x0;

    //
    std::ofstream out_3;
    std::ofstream out_4;
    out_3.open("Sym.txt");
    out_4.open("n4.txt");
    int counter = 0;
    //

    while (stop(A, x, b, tolerance)) {
        for (int i = 0; i < x.size(); i++) {
            T sum = b[i];
            for (int j = 0; j < A.get_row(i + 1) - A.get_row(i); j++)
                if (i != A.get_col(A.get_row(i)+j))
                    sum -= A.get_value(A.get_row(i) + j) * x[A.get_col(A.get_row(i) + j)];
            x[i] = (1 - w) * x[i] + w * sum / A(i, i);
        }

        for (int i = x.size() - 1; i > 0; i--) {
            T sum = b[i];
            for (int j = 0; j < A.get_row(i + 1) - A.get_row(i); j++)
                if (i != A.get_col(A.get_row(i)+j))
                    sum -= A.get_value(A.get_row(i) + j) * x[A.get_col(A.get_row(i) + j)];
            x[i] = (1 - w) * x[i] + w * sum / A(i, i);
        }

        //
        counter++;
        out_3 << N(A*x - b) << std::endl;
        out_4 << counter << std::endl;
        //

    }
    return x;
}


template<typename T>
std::vector<T> SSOR_step(const csr_matrix<T> &A, const std::vector<T> &b, const std::vector<T> &x0, T w) {
    std::vector<T> x = x0;
    for (int i = 0; i < x.size(); i++) {
        T sum = b[i];
        for (int j = 0; j < A.get_row(i + 1) - A.get_row(i); j++)
            if (i != j)
                sum -= A.get_value(A.get_row(i) + j) * x[A.get_col(A.get_row(i) + j)];
        x[i] = (1 - w) * x[i] + w * sum / A(i, i);
    }

    for (int i = x.size() - 1; i > 0; i--) {
        T sum = b[i];
        for (int j = 0; j < A.get_row(i + 1) - A.get_row(i); j++)
            if (i != j)
                sum -= A.get_value(A.get_row(i) + j) * x[A.get_col(A.get_row(i) + j)];
        x[i] = (1 - w) * x[i] + w * sum / A(i, i);
    }

    return x;
}







#endif //SLAU_LIB_SOR_AND_SSOR_H
