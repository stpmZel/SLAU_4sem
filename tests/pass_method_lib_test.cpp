#include <gtest/gtest.h>
#include "../src/pass_method_lib.h"


TEST(PassageSimpleTest,_3x3_test){

    std::vector<triple<double>> m_body(3);

    m_body[0] = {0., 2., -1.};
    m_body[1] = {5., 4., 2.};
    m_body[2] = {1., -3., 0.};

    triple_diag_matrix<double> Matrix(m_body);

    std::vector<double> d = {3., 6., 2.};

    std::vector<double> x = passage_method<double>(Matrix, d);

    std::vector<double> constant = {1.49, -0.02, -0.68};

    for(int i = 0; i<x.size();i++){
    ASSERT_NEAR(x[i], constant[i] , 0.001);
    }
}

