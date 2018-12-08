#pragma once
#include "vector_field.h"

double init_func5(double x, double y){
    return 2 * x + y;
}

auto test_gradiend(){
    scalarField<double> s1(10, 10, init_func5, 0, 1, 0, 1);
    s1.print();
    auto v = get_gradient(s1);
    v.print();
}
