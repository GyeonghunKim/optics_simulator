#pragma once
#include "scalar_field.h"
#include "matrix.h"

auto test_scalar_field1(){
    matrix<double> m1(3, 4, 0.1);
    std::cout << m1.get_N_col() << std::endl;
    scalarField<double> s1(m1);
    std::cout << "Hi" << std::endl;
    std::cout << s1.get_N_col() << std::endl;
    std::cout << s1.get_data().get_N_col() << std::endl;
}

double init_func1(int i, int j){
    return double(2 * i + j);
}
auto test_scalar_field2(){
    scalarField<double> s1(10, 10, init_func1);
    s1.print();
}


double init_func2(double x, double y){
    return 2 * x + y;
}
auto test_scalar_field3(){
    scalarField<double> s1(10, 10, init_func2, 0, 1, 0, 1);
    s1.print();
}

double init_func3(double x, double y){
    return 2 * x + y;
}
auto test_scalar_field4(){
    scalarField<double> s1(10, 10, 0, 0, init_func2, 0.1, 0.1);
    s1.print();
}

auto test_scalar_field5(){
    scalarField<double> s1(10, 10, 0, 0, init_func2, 0.1, 0.1);
    scalarField<double> s2(10 ,10, 1, 1, init_func2, 0.1, 0.1);

    s1.print();
    std::cout << std::endl;
    s2.print();
    std::cout << std::endl;
    auto s3 = s1 + s2;
    s3.print();
    std::cout << std::endl;
    auto s4 = s1 - s2;
    s4.print();
    std::cout << std::endl;
    auto s5 = s1 * s2;
    s5.print();
    std::cout << std::endl;

}

auto test_scalar_field6(){
    scalarField<double> s1(10, 10, 0, 0, init_func2, 0.1, 0.1);

    s1.print();
    std::cout << std::endl;

    auto s2 = s1 * 2;
    s2.print();
    std::cout << std::endl;


}



