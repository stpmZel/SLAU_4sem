//
// Created by Stepan on 08.04.2023.
//

#ifndef SLAU_LIB_GRADIENT_FALL_H
#define SLAU_LIB_GRADIENT_FALL_H

#include "CSR_matrix.h"
#include "Vector.h"


template<typename T>
std::vector<T> Gradient_descent_fast(const csr_matrix<T> &A, const std::vector<T> &b, const std::vector<T> &x0, T tolerance)
{
    std::vector<T> x = x0;
    std::vector<T> r = A * x - b;
    T a;

    std::ofstream out_5;
    std::ofstream out_6;
    out_5.open("x_y3.txt");
    out_6.open("n1.txt");
    int counter = 0;
    while(stop(A, x, b, tolerance))
    {
        a = scal(r, r) / scal(r, A * r);
        x = x - r * a;
        r = A * x - b;

        counter++;
        out_5 << x[0] << " " << x[3] << std::endl;
        out_6 << counter << std::endl;
    }
    return x;
}


#endif //SLAU_LIB_GRADIENT_FALL_H
