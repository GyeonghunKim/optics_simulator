#include "lens.h"
double lens_function(double x, double y, lens l, std::string lens_type){
    if(lens_type == "spherical_convex"){
        double r1 = std::sqrt((x - l.d1 * l.align.get_x() - l.center_x) * (x - l.d1 * l.align.get_x() - l.center_x)
                              + (y - l.d1 * l.align.get_y() - l.center_y) * (y - l.d1 * l.align.get_y() - l.center_y));
        double r2 = std::sqrt((x - l.d2 * l.align.get_x() - l.center_x) * (x - l.d2 * l.align.get_x() - l.center_x)
                              + (y - l.d2 * l.align.get_y() - l.center_y) * (y - l.d2 * l.align.get_y() - l.center_y));
        if (r1 < std::abs(l.param1) && r2 < std::abs(l.param2)){
            return l.n;
        }
        else{
            return 1;
        }
    }
    else if(lens_type == "parabolic_convex"){

        double lhs1 = (y - l.d1 * l.align.get_y() - l.center_y) * (y - l.d1 * l.align.get_y() - l.center_y);
        double lhs2 = (y - l.d2 * l.align.get_y() - l.center_y) * (y - l.d2 * l.align.get_y() - l.center_y);
        double rhs1 = 4 * l.param1 * (x + l.d1 * l.align.get_x() + l.center_x);
        double rhs2 = -4 * l.param2 * (x - l.d2 * l.align.get_x() - l.center_x);

        if (lhs1 < rhs1 && lhs2 < rhs2){
            return l.n;
        }
        else{
            return 1;
        }
    }
}

