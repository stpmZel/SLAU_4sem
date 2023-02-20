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
    triple_diag_matrix(const std::vector<triple<T>>& b);

    [[nodiscard]] const triple<T> &getStr(int i) const{
        return body[i];}

    [[nodiscard]] int getSize() const{
        return body.size();
    }

private:
    std::vector<triple<T>> body;
};





template<typename T>

std::vector<T> passage_method(const triple_diag_matrix<T>& matrix,const std::vector<T>& d){
    std::vector<std::pair<T,T>> pq(matrix.getSize());


    pq[0].first = -matrix.getStr(0).c/matrix.getStr(0).b;
    pq[0].second = d[0]/matrix.getStr(0).b;
    for(int i = 1;i < matrix.getSize()-1;i++){
        pq[i].first = - matrix.getStr(i).c / (matrix.getStr(i).a * pq[i-1].first + matrix.getStr(i).b);
        pq[i].second = (d[i] - matrix.getStr(i).a * pq[i-1].second)/
                (matrix.getStr(i).a*pq[i-1].first + matrix.getStr(i).b);
    }
    pq[matrix.getSize()-1].first = 0;
    pq[matrix.getSize()-1].second = (d[matrix.getSize()-1] - matrix.getStr(matrix.getSize()-1).a*
            pq[matrix.getSize()-2].second)/
                                      (matrix.getStr(matrix.getSize()-1).a*
                                      pq[matrix.getSize()-2].first + matrix.getStr(matrix.getSize()-1).b);

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
triple_diag_matrix<T>::triple_diag_matrix(const std::vector<triple<T>>& b) {
    body = b;
}




#endif //SLAU_LIB_PASS_METHOD_LIB_H
