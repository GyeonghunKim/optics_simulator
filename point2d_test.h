#pragma once
#include "point2d.h"
#include <iostream>

// test functions for get_weight
auto test_get_weight1(){
    point2D<double> a(3.2, 4.6);
    auto b = a.get_near();
    auto c = a.get_weight();
    std::cout << c[0] << "\t" << c[1] << "\t" << c[2] << "\t" << c[3] << std::endl;
}

auto test_get_weight2(){
    point2D<double> a(3, 4);
    auto b = a.get_near();
    auto c = a.get_weight();
    std::cout << c[0] << "\t" << c[1] << "\t" << c[2] << "\t" << c[3] << std::endl;
}

