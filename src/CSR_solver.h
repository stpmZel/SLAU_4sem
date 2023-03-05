//
// Created by Stepan on 04.03.2023.
//

#ifndef SLAU_LIB_CSR_SOLVER_H
#define SLAU_LIB_CSR_SOLVER_H
#include <vector>
#include "CSR_matrix.h"
#include "Vector.h"
#include <fstream>

template<typename T>
std::vector<T> FPI(csr_matrix<T> &A, std::vector<T> &b, std::vector<T> &x, T t, T tau) {
    std::vector x_1 = x;
    std::ofstream out;
    std::ofstream out_2;
    out.open("f1.txt");
    out_2.open("n1.txt");
    int counter = 0;
    std::vector<T> ret = A * x - b;
    while (N(ret) > t) {
        x = x_1;
        for (int i = 0; i < x.size(); i++) {
            T sum = b[i] * tau + x_1[i];
            for (int j = 0; j < x.size(); j++) sum -= x_1[j] * A(i, j) * tau;
            x_1[i] = sum;
        }
        ret = A * x_1 - b;
        counter++;
        out << N(ret) << std::endl;
        out_2 << counter << std::endl;
    }
    out.close();
    out_2.close();
    return x_1;
}

//
//template<typename T>
//int FPI_for_count(csr_matrix<T> &A, std::vector<T> &b, std::vector<T> x, T t, T tau) {
//    std::vector x_1 = x;
//    std::vector<T> ret = A * x - b;
//    int counter = 0;
//    while (N(ret) > t) {
//        x = x_1;
//        for (int i = 0; i < x.size(); i++) {
//            T sum = b[i] * tau + x[i];
//            for (int j = 0; j < x.size(); j++) sum -= x[j] * A(i, j) * tau;
//            x_1[i] = sum;
//        }
//        ret = A * x_1 - b;
//        counter += 1;
//
//    }
//    return counter;
//}


template<typename T>
std::vector<T> Jacobi(csr_matrix<T> &A, std::vector<T> &b, std::vector<T> &x, T t) {
    std::vector x_1 = x;
    std::ofstream out_3;
    std::ofstream out_4;
    out_3.open("f2.txt");
    out_4.open("n2.txt");
    int counter = 0;
    std::vector<T> ret = A * x - b;
    std::vector<T> x0 = x;
    while (N(ret) > t) {
        x0 = x_1;
        for (int i = 0; i < x.size(); i++) {
            T sum = b[i];
            for (int j = 0; j < x.size(); j++) if (j != i) sum -= x0[j] * A(i, j);
            x_1[i] = sum / A(i, i);
        }
        ret = A * x_1 - b;
        counter++;
        out_3 << N(ret) << std::endl;
        out_4 << counter << std::endl;

    }
    out_3.close();
    out_4.close();
    return x_1;
}








template<typename T>
std::vector<T> Gaus_Zeidel(csr_matrix<T> &A, std::vector<T> &b, std::vector<T> &x, T t) {
    std::vector x_1 = x;
    std::vector<T> ret = A * x - b;
    std::ofstream out_5;
    std::ofstream out_6;
    out_5.open("f3.txt");
    out_6.open("n3.txt");
    int counter = 0;
    while (N(ret) > t) {
        for (int i = 0; i < x.size(); i++) {
            T sum = b[i];
            for (int j = 0; j < x.size(); j++) if (j != i) sum -= x_1[j] * A(i, j);
            x_1[i] = sum / A(i, i);
        }
        ret = A * x_1 - b;
        counter++;
        out_5 << N(ret) << std::endl;
        out_6 << counter << std::endl;
    }
    out_5.close();
    out_6.close();
    return x_1;
}




#endif //SLAU_LIB_CSR_SOLVER_H
