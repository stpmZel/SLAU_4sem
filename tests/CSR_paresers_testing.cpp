//
// Created by Stepan on 04.03.2023.
//

#include "gtest/gtest.h"
#include "../src/CSR_matrix.h"
#include "../src/CSR_solver.h"


TEST(ITTERATIONS, GAUS_ZEIDEL) {

    std::vector<point<double>> DOK;
    DOK.push_back({0, 0, 16});
    DOK.push_back({0, 1, 3});
    DOK.push_back({1, 0, 7});
    DOK.push_back({1, 1, -11});
    std::vector<double> b{11, 13};
    std::vector<double> x{1, 1};
    csr_matrix<double> A(2, 2, DOK);
    double t = 1e-7;
    std::vector<double> res_ = Gaus_Zeidel(A, b, x, t);
    std::vector<double> diff_ = A * res_ - b;
    for(int i = 0; i < 2; i ++) ASSERT_NEAR(diff_[i], 0, 1e-3);
}

TEST(ITTERATIONS, JACOBI) {

    std::vector<point<double>> DOK;
    DOK.push_back({0, 0, 16});
    DOK.push_back({0, 1, 3});
    DOK.push_back({1, 0, 7});
    DOK.push_back({1, 1, -11});
    std::vector<double> b{11, 13};
    std::vector<double> x{1, 1};
    csr_matrix<double> A(2, 2, DOK);
    double t = 1e-7;
    std::vector<double> res_ = Jacobi(A, b, x, t);
    std::vector<double> diff_ = A * res_ - b;
    for(int i = 0; i < 2; i ++) ASSERT_NEAR(diff_[i], 0, 1e-3);
}

TEST(ITTERATIONS, FPI) {

    std::vector<point<double>> DOK;
    DOK.push_back({0, 0, 10});
    DOK.push_back({0, 1, -0.5});
    DOK.push_back({1, 0, -0.5});
    DOK.push_back({1, 1, 10});
    std::vector<double> b{1, 3};
    std::vector<double> x{1, 1};
    csr_matrix<double> A(2, 2, DOK);
    double t = 1e-7;
    double tau = 1e-2;
    std::vector<double> res_ = FPI(A, b, x, t, tau);
    std::vector<double> diff_ = A * res_ - b;
    for (int i = 0; i < 2; i++) ASSERT_NEAR(diff_[i], 0, 1e-3);
}




int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}