#pragma once
#include "matrix.h"

auto test_matrix1(){
    matrix<double> m1(3, 4, 0.4);
    matrix<double> m2(3, 4, 0.2);
    m1.print();
    m2.print();
    (m1 + m2).print();

}
