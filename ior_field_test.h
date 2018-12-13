#pragma once
#include "ior_field.h"
#include "lens.h"

auto ior_field_test(){
    lens l1(0, 0, 1, -1, 1, 0, 1.5, "spherical_convex");
    l1.print_spec();
    ior_field field1(20, 20, -5 ,5, -5, 5, l1);
    field1.print();

}
