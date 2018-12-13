#pragma once
#include "laser.h"
#include "lens.h"
#include "ior_field.h"

auto laser_test(){
    lens l1(0, 0, 1, -1, 0.1, 1.5, "spherical_convex");
    // l1.print_spec();
    ior_field field1(20, 20, -3 ,3, -3, 3, l1);
    // field1.print();
    // field1.get_data().print();
    point2D<double> loc = {-2, 2};
    point2D<double> dir = {1, 0};
    laser laser1(loc, dir, field1, 0.01);
    laser1.activation();
    laser1.get_loc().print();
}
