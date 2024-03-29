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
    std::vector<T> solutions_(n);
    T sina = std::sin(M_PI / static_cast<T>(n));
    T cosa = std::cos(M_PI / static_cast<T>(n));
    T sinb = std::sin(M_PI / (2 * static_cast<T>(n)));

    solutions_[0] = std::cos(M_PI / (2 * static_cast<T>(n)));
    for (int i = 1; i < n; i++) {
        solutions_[i] = solutions_[i - 1] * cosa - sinb * sina;
        sinb = solutions_[i - 1] * sina + sinb * cosa;
    }
    return solutions_;
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
std::vector<T> FPI(csr_matrix<T> &A, std::vector<T> &b, std::vector<T> &x0, T t, T tau) {
    std::vector<T> x = x0;
    std::vector<T> x_1 = x;
    std::ofstream out;
    std::ofstream out_2;
    out.open("x_y2.txt");
    out_2.open("n1.txt");
    int counter = 0;
    std::vector<T> ret = A * x - b;
    while (stop(A, x, b, t)) {
        x = x_1;
        for (int i = 0; i < x.size(); i++) {
            T sum = b[i] * tau + x_1[i];
            for (int j = 0; j < x.size(); j++) sum -= x_1[j] * A(i, j) * tau;
            x_1[i] = sum;
        }
        ret = A * x_1 - b;
        counter++;
        out << x_1[0] << " " << x_1[3] << std::endl;
        out_2 << counter << std::endl;
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
    std::vector<T> ch_sol = FPI_cheb(sol, t_dist, lam_max, lam_min);



    std::ofstream out_8;
    std::ofstream out_9;
    out_8.open("3.txt");
    out_9.open("n3.txt");
    int counter = 0;


    int count = 0;
    while (stop(A, x_1, b, t)) {
        x = x_1;
        x_1 = x - (A * x - b) * ch_sol[count % iterations];
        count++;

        counter++;
        out_8 << N(A * x - b) << std::endl;
        out_9 << counter << std::endl;
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
//    std::ofstream out_3;
//    std::ofstream out_4;
//    out_3.open("f2.txt");
//    out_4.open("n2.txt");
//    int counter = 0;
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
//        counter++;
//        out_3 << N(ret) << std::endl;
//        out_4 << counter << std::endl;

    }
//    out_3.close();
//    out_4.close();
    return x_1;
}








template<typename T>
std::vector<T> Gaus_Zeidel(csr_matrix<T> &A, std::vector<T> &b, std::vector<T> &x, T t) {
    std::vector<T> x_1 = x;
    std::vector<T> ret = A * x - b;
//    std::ofstream out_5;
//    std::ofstream out_6;
//    out_5.open("f3.txt");
//    out_6.open("n3.txt");
//    int counter = 0;
    while (N(ret) > t) {
        for (int i = 0; i < x.size(); i++) {
            T sum = b[i];
            for (int j = 0; j < x.size(); j++) if (j != i) sum -= x_1[j] * A(i, j);
            x_1[i] = sum / A(i, i);
        }
        ret = A * x_1 - b;
//        counter++;
//        out_5 << N(ret) << std::endl;
//        out_6 << counter << std::endl;
    }
//    out_5.close();
//    out_6.close();
    return x_1;
}

template<typename T>
std::vector<T> Sym_Gaus_Zeidel(const csr_matrix<T> &A, const std::vector<T> &b, const std::vector<T> &x_0, T t) {
    std::vector<T> x = x_0;

    std::ofstream out_3;
    std::ofstream out_4;
    out_3.open("Sym.txt");
    out_4.open("n4.txt");
    int counter = 0;

    while (stop(A, x, b, t)) {
        for (int i = 0; i < x.size(); i++) {
            T sum = b[i];

            for (int j = 0; j < A.get_row(i + 1) - A.get_row(i); j++)
                if (i != j)
                    sum -= A.get_value(A.get_row(i) + j) * x[A.get_col(A.get_row(i) + j)];
            x[i] = sum / A(i, i);
        }

        for (int i = x.size() - 1; i > 0; i--) {
            T sum = b[i];
            for (int j = 0; j < A.get_row(i + 1) - A.get_row(i); j++)
                if (i != j)
                    sum -= A.get_value(A.get_row(i) + j) * x[A.get_col(A.get_row(i) + j)];
            x[i] = sum / A(i, i);
        }

        counter++;
        out_3 << N(A*x - b) << std::endl;
        out_4 << counter << std::endl;

    }
    return x;
}


template<typename T>
std::vector<T> Gaus_Zeidel_Sym_it(const csr_matrix<T> &A, const std::vector<T> &b, const std::vector<T> x_0) {
    std::vector<T> x = x_0;
    for (int i = 0; i < x.size(); i++) {
        T sum = b[i];

        for (int j = 0; j < A.get_row(i + 1) - A.get_row(i); j++)
            if (i != j)
                sum -= A.get_value(A.get_row(i) + j) * x[A.get_col(A.get_row(i) + j)];
        x[i] = sum / A(i, i);
    }

    for (int i = x.size() - 1; i >= 0; i--) {
        T sum = b[i];
        for (int j = 0; j < A.get_row(i + 1) - A.get_row(i); j++)
            if (i != j)
                sum -= A.get_value(A.get_row(i) + j) * x[A.get_col(A.get_row(i) + j)];
        x[i] = sum / A(i, i);
    }
    return x;
}

template<typename T>
std::vector<T> Gaus_Zeidel_accelerated(const csr_matrix<T> &A, const std::vector<T> &b, const std::vector<T> &x, T r, T t) {
    std::vector<T> x0 = x;
    std::vector<T> x1 = Gaus_Zeidel_Sym_it(A, b, x0);
    std::vector<T> x2 = Gaus_Zeidel_Sym_it(A, b, x1);
    x1 = x2;

    T m0 = 1;
    T m1 = 1 / r;
    T m2 = 2 * m1 / r - m0;
    int count = 0;

    while (stop(A, x2, b, t)) {
        x2 = x1 * (2 * m1 / (r * m2)) - x0 * (m0 / m2);
        x0 = x1;
        x1 = Gaus_Zeidel_Sym_it(A, b, x2);
        m0 = m1;
        m1 = m2;
        m2 = 2 * m1 / r - m0;
        count++;
    }

    return x2;

}








#endif //SLAU_LIB_CSR_SOLVER_H
