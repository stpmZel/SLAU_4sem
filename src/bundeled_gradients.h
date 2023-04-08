//
// Created by Stepan on 08.04.2023.
//

#ifndef SLAU_LIB_BUNDELED_GRADIENTS_H
#define SLAU_LIB_BUNDELED_GRADIENTS_H
#include "CSR_matrix.h"


template<typename T>
std::vector<T> Conjaguate_Gradient(const csr_matrix<T> &A, const std::vector<T> &b, const std::vector<T> &x0, T t)
{
    std::vector<T> x = x0;
    std::vector<T> r = A * x - b, r1;
    std::vector<T> d = r;
    T a, beta;


    while(stop(A, x, b, t))
    {
        a = scal(d, r) / scal(d, A * d);
        x = x - d * a;
        r1 = A * x - b;
        beta = scal(r1, r1) / scal(r, r);
        r = r1;
        d = r1 + d * beta;
    }
    return x;
}


#endif //SLAU_LIB_BUNDELED_GRADIENTS_H
