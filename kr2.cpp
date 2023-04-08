//
// Created by Stepan on 08.04.2023.
//
#include "src/CSR_matrix.h"
#include "src/CSR_solver.h"
#include "src/bundeled_gradients.h"
#include <fstream>
#include <vector>
#include "src/Vector.h"
#include "src/gradient_fall.h"
#include "src/SOR_and_SSOR.h"
#include <chrono>
#include <cmath>


int main() {
//
//
//    std::vector<double> b(289);
//    for (auto i = 0u; i<289; i++) {
//        b[i] = 1;
//    }
//    std::vector<double> x(289);
//    for (auto i = 0u; i<289; i++) {
//        x[i] = 0;
//    }
//
//    std::vector<point<double>> points;
//    int counter = 0;
//    for(int i = 0; i<289; i++){
//        for(int j = 0; j<289; j++){
//            if(i == j) {
//                points.push_back({i, j, 64});
//                counter ++;}
//            if(i+1 == j or j+1 == i) {
//                points.push_back({i, j, 14});
//                counter++;}
//            if(i+17 == j or j+17 == i) {
//                points.push_back({i, j, 14});
//                counter++;}
//
//        }
//    }

//    csr_matrix<double> A(289, 289, points);
//
//    double c = 32.;
//    double a = 14.;
//    double l_max = (c + 2 * a * std::cos(M_PI / 18)) * (c + 2 * a * std::cos(M_PI / 18));
//    double l_min = (c + 2 * a * std::cos(17 * M_PI / 18)) * (c + 2 * a * std::cos(17 * M_PI / 18));
//    double l_max = 119.56833917554492;
//    double l_min = 8.43166082445513;
//
//
//    double t = 1/l_max;
//    std::vector<double> res1 = FPI(A, b, x, 1e-13,t  );


//    std::vector<double> res2 = FPI(A, b, x, 1e-13, 2/(l_max+l_min));


//
//    std::vector<double> res3 = FPI_accelerated_ch(A, b, x, 1e-13,l_max, l_min, 8);
//    std::vector<double> res4 = SSOR(A, b, x, 1e-13, 1.);
//
//
//    std::ofstream out;
//    out.open("time.txt");
//    std::ofstream out2;
//    out2.open("lam.txt");
//
//    std::cout << l_max << " -- " << l_min;
//
//    double i = 0;
//    while(i < 250)
//    {
//        auto start = std::chrono::high_resolution_clock::now();
//
//        std::vector<double> res_3 = FPI_accelerated_ch(A, b, x, t, 25. + i , l_min, 8);
//
//        auto stop = std::chrono::high_resolution_clock::now();
//        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
//        out << duration.count() << std::endl;
//        out2 << 900. + i - l_min << std::endl;
//
//        i += 10;
//    }


    ///task 2

    std::vector<point<double>> point_s;
    point_s.push_back({0,0, 17.});
    point_s.push_back({1,1, 19.});
    point_s.push_back({2,2, 22.});
    point_s.push_back({3,3, 25.5});

    std::vector<double> b = {4,4,4,4};
    std::vector<double> x = {0,0,0,0};

    csr_matrix<double> A(4,4,point_s);

    double t = 1e-13;

    double l_min = 17.;
    double l_max = 25.5;

    double c = 4.;



//    std::vector<double> r_1 = FPI(A, b, x, t, 1.8 / l_max);
//    double m_1 = scal(r_1, A * r_1) - scal(r_1, b) + c;
//    std::cout << m_1 << std::endl;
    std::vector<double> r_2 = FPI(A, b, x, t, 2 / (l_max + l_min));
    double m_2 = scal(r_2, A * r_2) - scal(r_2, b) + c;
    std::cout << m_2 << std::endl;
    std::vector<double> r_3 = Gradient_descent_fast(A, b, x, t);
    double m_3 = scal(r_3, A * r_3) - scal(r_3, b) + c;
    std::cout << m_3 << std::endl;
    std::vector<double> r_4 = FPI_accelerated_ch(A, b, x, t, l_max, l_min, 8);
    double m_4 = scal(r_4, A * r_4) - scal(r_4, b) + c;
    std::cout << m_4 << std::endl;
    std::vector<double> r_5 = Conjaguate_Gradient(A, b, x, t);
    double m_5 = scal(r_5, A * r_5) - scal(r_5, b) + c;
    std::cout << m_5 << std::endl;






}