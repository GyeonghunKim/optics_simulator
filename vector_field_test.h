#pragma once
#include "vector_field.h"

double init_func5(double x, double y){
    return 2 * x + y;
}

auto test_gradiend(){
    scalarField<double> s1(10, 10, init_func5, 0, 1, 0, 1);
    s1.print();
    auto v = get_gradient(s1);
    v.print_type2();
}

double init_func6(double x, double y){
    if(x * x + y * y < 10){
        return 1.5;
    }
    else{
        return 1;
    }
}

auto test_gradiend2(){
    scalarField<double> s1(100, 100, init_func6, -20, 20, -20, 20);
    s1.print();
    auto v = get_gradient(s1);
    v.print_matlab();
}

