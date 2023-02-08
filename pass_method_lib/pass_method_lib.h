//
// Created by Stepan on 08.02.2023.
//

#ifndef SLAU_LIB_PASS_METHOD_LIB_H
#define SLAU_LIB_PASS_METHOD_LIB_H


#include <vector>

template<typename T>
struct triple{
    T a;
    T b;
    T c;
};

template<typename T>
class triple_diag_matrix {
public:
    triple_diag_matrix(std::vector<triple<T>>& b);

    std::vector<triple<T>> &getBody(){
        return body;}

private:
    std::vector<triple<T>> body;
};





template<typename T>

std::vector<T> passage_method(triple_diag_matrix<T>& matrix, std::vector<T>& d){
    std::vector<std::pair<T,T>> pq(matrix.getBody().size());


    pq[0].first = -matrix.getBody()[0].c/matrix.getBody()[0].b;
    pq[0].second = d[0]/matrix.getBody()[0].b;
    for(int i = 1;i < matrix.getBody().size()-1;i++){
        pq[i].first = - matrix.getBody()[i].c / (matrix.getBody()[i].a * pq[i-1].first + matrix.getBody()[i].b);
        pq[i].second = (d[i] - matrix.getBody()[i].a * pq[i-1].second)/
                (matrix.getBody()[i].a*pq[i-1].first + matrix.getBody()[i].b);
    }
    pq[matrix.getBody().size()-1].first = 0;
    pq[matrix.getBody().size()-1].second = (d[matrix.getBody().size()-1] - matrix.getBody()[matrix.getBody().size()-1].a*
            pq[matrix.getBody().size()-2].second)/
                                      (matrix.getBody()[matrix.getBody().size()-1].a*
                                      pq[matrix.getBody().size()-2].first + matrix.getBody()[matrix.getBody().size()-1].b);

    std::vector<T> x(pq.size());
    x[pq.size()-1] = pq[pq.size()-1].second;
    for(int i = pq.size()-2;i>=0;i--){
        x[i] = pq[i].first*x[i+1] + pq[i].second;
    }
    return x;
}








//--------------------------------------------------------------------------------------
//---------------------------IMPLEMENTATION---------------------------------------------
//--------------------------------------------------------------------------------------




template<typename T>
triple_diag_matrix<T>::triple_diag_matrix(std::vector<triple<T>>& b) {
    body = b;
}




#endif //SLAU_LIB_PASS_METHOD_LIB_H
