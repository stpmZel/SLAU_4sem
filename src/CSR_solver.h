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
std::vector<T> sol_chebyshev_polynom(long int n){
    T Cos_b = std::cos(std::atan(1)*4 / (2 * static_cast<T>(n)));
    T Sin_b = std::sqrt(1 - std::pow(Cos_b, 2));
    T Sin_a = Cos_b * Sin_b * 2;
    T Cos_a = std::pow(Cos_b, 2) - std::pow(Sin_b, 2);
    std::vector<T> sol;
    sol.resize(n);
    sol[0] = Cos_b;
    for (auto i = 0ul; i + 1 < n; i++) {
        sol[i + 1] = sol[i] * Cos_a - Sin_b * Sin_a;
        Sin_b = sol[i] * Sin_a + Sin_b * Cos_a;
    }
    return sol;
}

std::vector<int> t_distribution(int n) {
    std::vector<int> ret(n);
    ret[0] = 1;
    for (int i = 1; i < n; i *= 2) {
        for (int j = 0; j < i; j+=1) {
            ret[n * (j * 2 + 1) / (2 * i)] = 2 * i  + 1 - ret[n * 2 * j / (2 * i)];
        }
    }
    return ret;
}

template<typename T>
std::vector<T> FPI(csr_matrix<T> &A, std::vector<T> &b, std::vector<T> &x, T t, T tau) {
    std::vector x_1 = x;
//    std::ofstream out;
//    std::ofstream out_2;
//    out.open("f1.txt");
//    out_2.open("n1.txt");
//    int counter = 0;
    std::vector<T> ret = A * x - b;
    while (N(ret) > t) {
        x = x_1;
        for (int i = 0; i < x.size(); i++) {
            T sum = b[i] * tau + x_1[i];
            for (int j = 0; j < x.size(); j++) sum -= x_1[j] * A(i, j) * tau;
            x_1[i] = sum;
        }
        ret = A * x_1 - b;
//        counter++;
//        out << N(ret) << std::endl;
//        out_2 << counter << std::endl;
    }
//    out.close();
//    out_2.close();
    return x_1;
}

template<typename T>
std::vector<T> FPI_cheb(std::vector<T>& s, std::vector<int>& o, T lam_max, T lam_min) {
    std::vector<T> ret(s.size());
    for(int i = 0; i < s.size(); i ++)
    {
        ret[i] = 2 / ((lam_max + lam_min) + (lam_max - lam_min) * s[o[i] - 1]);
    }
    return ret;
}


template<typename T>
std::vector<T> FPI_accelerated_ch(const csr_matrix<T> &A, const std::vector<T> &b, const std::vector<T> &x_0, T t, T lam_max,
                          T lam_min, int iterations) {

    std::vector<T> sol = sol_chebyshev_polynom<T>(iterations);
    std::vector<int> t_dist = t_distribution(iterations);
    std::vector<T> x = x_0;
    std::vector<T> x_1 = x;
    std::vector<T> ch_sol = MPI_Cheb_solutions(sol, t_dist, lam_max, lam_min);

    int count = 0;
    while (!stop_check(A, x_1, b, t)) {
        x = x_1;
        x_1 = x - (A * x - b) * ch_sol[count % iterations];
    }
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
