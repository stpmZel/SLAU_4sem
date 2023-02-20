//
// Created by Stepan on 21.02.2023.
//


#include <gtest/gtest.h>
#include "../src/CSR_matrix.h"
#include <vector>


TEST(CSR_MATRIX_TEST,multiplication_test){
    std::vector<std::vector<double>> matrix(4);

    matrix[0] = {0., 2., -1.};
    matrix[1] = {5., 0., 2.};
    matrix[2] = {0., -3., 0.};
    matrix[3] = {1., 0., 0.};

    std::vector<point<double>> body;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 3; j++){
            body.push_back({i,j,matrix[i][j]});
        }
    }

    std::vector<double> b = {0. , 1., 2.};

    csr_matrix<double> A = csr_matrix<double>(4, 3, body);

    std::vector<double> answ = {0., 4., -3., 0.};

    for(int i = 0; i < 4; i++){
        ASSERT_NEAR(answ[i], (A*b)[i], 0.0000001);
    }
}


TEST(CSR_MATRIX_TEST,get_element_test){
    std::vector<std::vector<double>> matrix(4);

    matrix[0] = {0., 2., -1.};
    matrix[1] = {5., 0., 2.};
    matrix[2] = {0., -3., 0.};
    matrix[3] = {1., 0., 0.};

    std::vector<point<double>> body;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 3; j++){
            body.push_back({i,j,matrix[i][j]});
        }
    }
    csr_matrix<double> A = csr_matrix<double>(4, 3, body);

    ASSERT_DOUBLE_EQ(A(1,2), matrix[1][2]);
    ASSERT_DOUBLE_EQ(A(0, 0), static_cast<double>(0));


//    std::vector<double> bad_vector = {1.};
//    std::vector<double> bad_answer = A*bad_vector;
}
