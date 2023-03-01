#include "gtest/gtest.h"
#include "../src/Housholder.h"
#include <ctime>
#include <random>

TEST(HOUSEHOLDER, DECOMPOSITION_SMALL) {
    dnc_matrix<double> A(5, 3, {12, -51, 4, 6, 167, -68, -4, 24, -41, -1, 1, 0, 2, 0, 3});
    auto [Q, R] =  housholder(A);
    dnc_matrix<double> res_ = Q * R;
    for(int i = 0; i < 5; i ++)
    {
        for(int j = 0; j < 3; j ++) ASSERT_NEAR(res_(i, j), A(i, j), 1e-6);
    }
}


TEST(HOUSEHOLDER, DECOMPOSITION_BIG)
{
    dnc_matrix<double> A{100, 100};
    std::srand(std::time(nullptr));
    for(int i = 0; i < 100; i ++) for(int j = 0; j < 100; j ++) A(i, j) = rand();
    auto [Q, R] = housholder <double>(A);
    dnc_matrix<double> res_ = Q * R;
    for(int i = 0; i < 100; i ++)
    {
        for(int j = 0; j < 100; j ++) ASSERT_NEAR(res_(i, j), A(i, j), 1e-4);
    }
}




int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
