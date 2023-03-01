//
// Created by Stepan on 28.02.2023.
//

#ifndef SLAU_LIB_DNC_MATRIX_H
#define SLAU_LIB_DNC_MATRIX_H


#include <iostream>
#include <vector>
#include <cmath>


template<typename T>
class dnc_matrix {
private:
    std::vector<T> body;
    int height;
    int width;
public:
    dnc_matrix(int Height, int Width, const std::vector<T>& Body): height(Height), width(Width), body(Body){};

    dnc_matrix(int Height, int Width): height(Height), width(Width){
        body.resize(height*width);
    };

    T operator()(int i, int j) const { return body[i * width + j]; }
    T &operator()(int i, int j) { return body[i * width + j]; }

    int get_height() const { return height; }

    int get_width() const { return width; }

    dnc_matrix<T> operator*(const dnc_matrix<T> &rhs) {
        std::vector<T> result;
        result.reserve(height * rhs.get_width());

        for (int i = 0; i < height; i++) {
            for(int k = 0; k < rhs.get_width(); k++)
            {
                T sum = 0;
                for (int j = 0; j < width; j++) {
                    sum += body[i * width + j] * rhs(j, k);
                }
                result.push_back(sum);
            }
        }
        return dnc_matrix<T>{height, rhs.width, result};
    }

    dnc_matrix<T> operator*(T rhs) {
        std::vector<T> ret;
        ret.reserve(height * width);
        for (int i = 0; i < height; i++) for (int j = 0; j < width; j++) ret.push_back(body[i * width + j] * rhs);
        return dnc_matrix<T>{height, width, ret};
    }

    dnc_matrix<T> operator+(const dnc_matrix<T> &rhs) const {
        std::vector<T> result;
        result.reserve(width * height);
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) result.push_back(body[i * width + j] + rhs(i, j));
        }
        return dnc_matrix<T>{height, width, result};
    }

    dnc_matrix<T> get_column(int n) const {
        std::vector<T> column;
        column.reserve(height);
        for(int i = 0; i < height; i++){
            column.push_back(body[i * width + n]);
        }
        return dnc_matrix<T>{height, 1, column};
    }

    /// only for columns
    T get_module_v() const {
        T sum = 0;
        for(auto & element: body){
            sum+=element*element;
        }
        return std::sqrt(sum);
    }

    dnc_matrix<T> get_normal_v(int i) {
        dnc_matrix<T> ret{height, 1, body};
        for(int l = 0; l<i; l++){
            ret(l,0) = 0;
        }
        if(ret(i,0)>=0){
            ret(i,0) += ret.get_module_v();
        }
        else{
            ret(i,0) -= ret.get_module_v();
        }
        T module = ret.get_module_v();
        for (int k = i; k < height; k++) ret(k, 0) /= module;
        return ret;
    }

    dnc_matrix<T> transposed_v(){
        dnc_matrix<T> new_m = dnc_matrix<T>(width, height, body);
        return new_m;
    }

    T scalar_v(const dnc_matrix<T> &rhs){
        T sum = 0;
        for(int i = 0; i < rhs.get_height(); i++){
            sum+= body[i]*rhs(i,0);
        }
        return sum;
    }

    friend std::ostream &operator<<(std::ostream &out, const dnc_matrix<T> &output_) {
        for (int i = 0; i < output_.height; i++) {
            for (int j = 0; j < output_.width; j++) out << output_.body[i * output_.get_width() + j] << " ";
            out << "\n";
        }
        return out;
    }
};



#endif //SLAU_LIB_DNC_MATRIX_H
