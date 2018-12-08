#pragma once
#include "point2d_series.h"

auto test_point2d_series1(){
    point2D_series<int> a;
    point2D<int> b(3, 4);
    b.print();
    a.add_point(b);
    a.add_point(b);
    a.add_point(3 * b);
    a.print();
    auto c = a.get_last();
    c.set_x(3);
    c.print();
    a.print();

}

