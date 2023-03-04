//
// Created by Stepan on 01.03.2023.
//

#ifndef SLAU_LIB_HOUSHOLDER_H
#define SLAU_LIB_HOUSHOLDER_H

#include "../src/DNC_matrix.h"


template<typename T>
std::tuple<dnc_matrix<T>, dnc_matrix<T>> housholder(const dnc_matrix<T> &matrix){
    dnc_matrix<T> Matrix = matrix;
    std::vector<dnc_matrix<T>> col_s;
    col_s.reserve(Matrix.get_width());
    std::vector<dnc_matrix<T>> normal_s;
    normal_s.reserve(Matrix.get_width());

    for(int i = 0; i < Matrix.get_width(); i++){
        col_s.push_back(Matrix.get_column(i));
    }

    for (int i = 0; i < Matrix.get_width(); i++) {

        normal_s.push_back(col_s[i].get_normal_v(i));
        for (int j = i; j < Matrix.get_width(); j++) {
            col_s[j] =  col_s[j] + normal_s[i] *
                    (-2 * col_s[j].scalar_v(normal_s[i]) / (normal_s[i].scalar_v(normal_s[i])));
        }
    }

    dnc_matrix<T> Q{Matrix.get_height(),Matrix.get_height()};
    for (int i = 0; i < Matrix.get_height(); i++) Q(i, i) = 1;
    Q = Q + normal_s[0] * normal_s[0].transposed_v() * (-2 / normal_s[0].scalar_v(normal_s[0]));

    std::vector<dnc_matrix<T>> col_s_Q;
    col_s_Q.reserve(Matrix.get_height());
    for (int i = 0; i < Matrix.get_height(); i++) col_s_Q.push_back(Q.get_column(i));

    for (int i = 1; i < Matrix.get_width(); i++) {
        for (int j = 0; j < Matrix.get_height(); j++) {
            col_s_Q[j] = col_s_Q[j] +
                    normal_s[i] *
                    (-2 * col_s_Q[j].scalar_v(normal_s[i]) / (normal_s[i].scalar_v(normal_s[i])));
        }
    }


    for (int i = 0; i < Matrix.get_height(); i++) {
        for (int j = 0; j < Matrix.get_height(); j++) Q(i, j) = col_s_Q[i](j, 0);
    }


    dnc_matrix<T> R{Matrix.get_height(), Matrix.get_width()};
    for (int i = 0; i < Matrix.get_height(); i++)
    {
        for(int j = 0; j < Matrix.get_width(); j ++) R(i, j) = col_s[j](i, 0);
    }
    return {Q, R};
}






#endif //SLAU_LIB_HOUSHOLDER_H
