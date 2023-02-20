//
// Created by Stepan on 19.02.2023.
//

#ifndef SLAU_LIB_CSR_MATRIX_H
#define SLAU_LIB_CSR_MATRIX_H

#include <vector>
#include <algorithm>
#include <stdexcept>

template<typename T>
struct point{
    int i;
    int j;
    T value;

    bool operator<(point rhs){
        if(this->i != rhs.i){
            return this->i < rhs.i;
        }
        else return this->j < rhs.j;
    }
};



template<typename T>
class csr_matrix{
public:

csr_matrix(int Height, int Width, const std::vector<point<T>>& DOK);

T operator()(int i,int j);

std::vector<T> operator*(const std::vector<T> &b);

    int height;
    int width;
private:

    std::vector<int> str_sum;
    std::vector<int> col;
    std::vector<T> values;
};




//--------------------------------------------------------------------------------------
//---------------------------IMPLEMENTATION---------------------------------------------
//--------------------------------------------------------------------------------------




template<typename T>
csr_matrix<T>::csr_matrix(int Height, int Width, const std::vector<point<T>> &DOK) {
    height = Height;
    width = Width;

    this->values.resize(DOK.size());
    this->col.resize(DOK.size());
    this->str_sum.resize(height+1);

    for(int i =0;i<DOK.size();i++){
        this->values[i] = DOK[i].value;
        this->col[i] = DOK[i].j;
    }

    int sum = 0;
    for(int i = 0; i< height+1; i++){
        this->str_sum[i] = sum;
        sum += std::count_if(DOK.begin(), DOK.end(), [i](point<T> item){
            return item.i == i;
        });
    }
}

template<typename T>
T csr_matrix<T>::operator()(int i,int j){
    for(int l = str_sum[i]; l < str_sum[i+1]; l++){
        if(col[l] == j){
            return values[l];
        }
    }
    return static_cast<double>(static_cast<T>(0));
}


template<typename T>
std::vector<T> csr_matrix<T>::operator*(const std::vector<T> &b){
    if(b.size() != width) {
        throw std::logic_error("size of matrix != vector size (* operation error)");
    }
    std::vector<T> x(width);
    for(int i = 0; i< width;i++){
        x[i] = static_cast<T>(0);
        if(!b[i]){
            continue;
        }
        else{
            for(int l = str_sum[i];l < str_sum[i+1]; l++){
                x[i] += values[l] * b[col[l]];
            }
        }
    }
    return x;
}






#endif //SLAU_LIB_CSR_MATRIX_H
