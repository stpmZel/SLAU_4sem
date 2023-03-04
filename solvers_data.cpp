//
// Created by Stepan on 04.03.2023.
//
#include "src/CSR_matrix.h"
#include "src/CSR_solver.h"
#include <fstream>



int main(){
    std::vector<point<double>> DOK;
    DOK.push_back({0,0,10});
    DOK.push_back({0, 1, 1});
    DOK.push_back({0,2,0});
    DOK.push_back({1,0,1});
    DOK.push_back({1, 1, 7});
    DOK.push_back({1, 2, 0});
    DOK.push_back({2, 0, 0});
    DOK.push_back({2,1 , 0.1});
    DOK.push_back({2,2,1});

    std::vector<double> b{20, 30, 1};
    std::vector<double> x{0, 0, 0};
    csr_matrix<double> A(3, 3, DOK);

    double t_step = 2./(10.302*10000000.);
    double current_t = 0.00001 + t_step*1000;

    std::ofstream out;          // поток для записи
    out.open("hello2.txt"); // окрываем файл для записи


    for(int i = 1000; i < 1500; i++){
            out << FPI_for_count(A, b , x, std::pow(10, -12),  current_t) << std::endl;
        current_t += t_step;
    }
}