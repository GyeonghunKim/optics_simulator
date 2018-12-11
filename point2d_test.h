#pragma once
#include "point2d.h"
#include <iostream>

// test functions for get_weight
auto test_get_weight1(){
    point2D<double> a(3.2, 4.6);
    auto b = a.get_near(0, 0, 1, 1);
    auto c = a.get_weight();
    std::cout << c[0] << "\t" << c[1] << "\t" << c[2] << "\t" << c[3] << std::endl;
}

auto test_get_weight2(){
    point2D<double> a(3, 4);
    auto b = a.get_near(0, 0, 1, 1);
    auto c = a.get_weight();
    std::cout << c[0] << "\t" << c[1] << "\t" << c[2] << "\t" << c[3] << std::endl;
}

auto get_theta_test(){
    point2D<double> a = {3, 4};
    point2D<double> b = {1, 1};
    auto t1 = a.get_theta(b);
    auto t2 = b.get_theta(a);
    std::cout << t1 << "\t" << t2 << std::endl;
}
