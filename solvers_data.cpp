//
// Created by Stepan on 04.03.2023.
//
#include "src/CSR_matrix.h"
#include "src/CSR_solver.h"
#include <fstream>
#include <vector>
#include "src/Vector.h"



int main(){
//    std::vector<point<double>> DOK;
//    DOK.push_back({0,0,10});
//    DOK.push_back({0, 1, 1});
//    DOK.push_back({0,2,0});
//    DOK.push_back({1,0,1});
//    DOK.push_back({1, 1, 7});
//    DOK.push_back({1, 2, 0});
//    DOK.push_back({2, 0, 0});
//    DOK.push_back({2,1 , 0.1});
//    DOK.push_back({2,2,1});
//
//    std::vector<double> b{20, 30, 1};
//    std::vector<double> x{0, 0, 0};
//    csr_matrix<double> A(3, 3, DOK);
//
//    double t_step = 2./(10.302*10000000.);
//    double current_t = 0.000000000001 + t_step*100000;
//
//    std::ofstream out;          // поток для записи
//    out.open("hello2.txt"); // окрываем файл для записи
//
//
//    for(int i = 0; i < 100; i++){
//            out << FPI_for_count(A, b , x, std::pow(10, -12),  current_t) << std::endl;
//        current_t += t_step;
//    }

    std::vector<point<double>> DOK;
    DOK.push_back({0, 0, 12});
    DOK.push_back({0, 1, 17});
    DOK.push_back({0, 2, 3});
    DOK.push_back({1, 0, 17});
    DOK.push_back({1, 1, 15825});
    DOK.push_back({1, 2, 28});
    DOK.push_back({2, 0, 3});
    DOK.push_back({2, 1, 28});
    DOK.push_back({2, 2, 238});

    std::vector<double> b{1, 2, 3};
    std::vector<double> x{1, 1, 1};
    double tau = 1e-5;
    double t = 1e-30;

    csr_matrix<double> A(3, 3, DOK);
//
//    std::vector<double> answ_1 = FPI(A, b, x, t, tau);

    std::vector<double> answ_2 = Jacobi(A, b, x, t);

    std::vector<double> answ_3 = Gaus_Zeidel(A, b, x, t);

    //хз чето тут по С, вроде как ошибка и это не вектор

//    std::cout << "Minimum 1 = " << scal(answ_1, A * answ_1) * 0.5 - scal(b, answ_1) <<std::endl;
    std::cout << "Minimum 2 = " << scal(answ_2, A * answ_2) * 0.5 - scal(b, answ_2) <<std::endl;
    std::cout << "Minimum 3 = " << scal(answ_3, A * answ_3) * 0.5 - scal(b, answ_3) <<std::endl;

}