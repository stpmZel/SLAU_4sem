//
// Created by Stepan on 28.02.2023.

#include "gtest/gtest.h"
#include "../src/DNC_matrix.h"

TEST(DENSE, MULTIPLICATION) {
    dnc_matrix<double> matrix_{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    dnc_matrix<double> false_{3, 1, {1, 2, 3}};
    dnc_matrix<double> vec_{4, 2, {1, 5, 2, 6, 3, 7, 4, 8}};
    dnc_matrix<double> res_ = matrix_ * vec_;
    std::vector<double> answ_{30, 70, 70, 174, 110, 278};
    for (int i = 0; i < 3; i++) for (int j = 0; j < 2; j++) {
        std::cout << res_(i, j) << " " << answ_[i * 2 + j] << std::endl;
        ASSERT_TRUE(res_(i, j) == answ_[i * 2 + j]);


    }

}

TEST(DENSE, ADDITION) {
    dnc_matrix<double> mat_1_{3, 2, {1, 2, 3, 4, 5, 6}};
    dnc_matrix<double> mat_2_{3, 2, {6, 5, 4, 3, 2, 1}};
    dnc_matrix<double> res_ = mat_1_ + mat_2_;
    for (int i = 0; i < 3; i++) for (int j = 0; j < 2; j++) ASSERT_TRUE(res_(i, j) == 7);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


//
