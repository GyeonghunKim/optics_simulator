#pragma once
#include "lens.h"

auto test_lens1(){
    lens l1(0, 0, 10, -10, 5, 1.5, "spherical_convex");
    l1.print_spec();
}
